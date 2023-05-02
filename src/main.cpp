#include <exception>
#include <windows.h>
#include <lime/module.hpp>
#include <lime/hooks/detour.hpp>

#include "lua.hpp"
#include "logger.hpp"
#include "constants.hpp"

using chalchiu::logger;

lua_State *lua_state;
std::unique_ptr<lime::detour> detour_corona_init;
std::unique_ptr<lime::detour> detour_module_loader;

void hk_module_loader(lua_State *state, void *param_2, int param_3, unsigned int param_4)
{
    logger::get()->debug("[module_loader] 0x{}", reinterpret_cast<std::uintptr_t>(state));

    if (!lua_state)
    {
        lua_state = state;
    }

    return detour_module_loader->get_original<decltype(hk_module_loader) *>()(state, param_2, param_3, param_4);
}

bool hk_corona_init(int param, HWND *hwnd)
{
    auto original = detour_corona_init->get_original<decltype(hk_corona_init) *>()(param, hwnd);

    detour_corona_init.reset();
    detour_module_loader.reset();

    chalchiu::lua::init(lua_state);
    return original;
}

extern "C" BOOL APIENTRY DllMain(HANDLE, DWORD reason, LPVOID)
{
    if (reason != DLL_PROCESS_ATTACH)
    {
        return TRUE;
    }

    CHAR file[MAX_PATH];
    GetModuleFileNameA(nullptr, file, MAX_PATH);

    auto corona = lime::module::get("CoronaLabs.Corona.Native.dll");

    if (!corona)
    {
        logger::get()->warn("No CoronaSDK [{}] found ({})", corona.has_value(), file);
        return TRUE;
    }

    logger::get()->info("Loading Chalchiu (v{}) [{}]", chalchiu::version, file);
    logger::get()->info("Found CoronaSDK at 0x{}", corona->get_start(), file);

    auto module_loader = corona->get_symbol("CoronaLuaRegisterModuleLoader");
    auto corona_init = corona->get_symbol("CoronaWin32RuntimeRun");

    if (!module_loader || !corona_init)
    {
        logger::get()->error("No 'CoronaWin32RuntimeRun' [{}] or 'CoronaLuaRegisterModuleLoader' [{}] found",
                             corona_init, module_loader);

        return TRUE;
    }

    logger::get()->info("Found 'CoronaLuaRegisterModuleLoader' at 0x{}", module_loader);

    std::set_terminate([] {
        logger::get()->error("[crash] Unhandled exception!");

        try
        {
            std::rethrow_exception(std::current_exception());
        }
        catch (const std::exception &e)
        {
            logger::get()->error("[crash] [{}] {}", typeid(e).name(), e.what());
        }
        catch (...)
        {
            logger::get()->error("[crash] Unknown exception '{}'", typeid(std::current_exception()).name());
        }

        std::abort();
    });

    detour_module_loader = lime::detour::create(module_loader, hk_module_loader);
    detour_corona_init = lime::detour::create(corona_init, hk_corona_init);

    return TRUE;
}