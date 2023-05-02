#include <windows.h>
#include <lime/module.hpp>
#include <lime/hooks/detour.hpp>

#include "lua.hpp"
#include "logger.hpp"
#include "constants.hpp"

using chalchiu::logger;

lua_State *lua_state;
std::unique_ptr<lime::detour> detour_new_state;
std::unique_ptr<lime::detour> detour_corona_init;

lua_State *hk_new_state(lua_Alloc alloc, void *user_data)
{
    auto *original = detour_new_state->get_original<decltype(hk_new_state) *>()(alloc, user_data);
    static bool once = false;

    if (!once)
    {
        logger::get()->info("LuaState is 0x{}", reinterpret_cast<std::uintptr_t>(original));
        lua_state = original;
        once = true;
    }

    return original;
}

bool hk_corona_init(int param, HWND *hwnd)
{
    auto original = detour_corona_init->get_original<decltype(hk_corona_init) *>()(param, hwnd);

    logger::get()->debug("Cleaning up hooks");
    detour_corona_init.reset();
    detour_new_state.reset();

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
    auto lua = lime::module::get("lua.dll");

    if (!corona || !lua)
    {
        logger::get()->warn("No CoronaSDK [{}] or Lua [{}] found ({})", corona.has_value(), lua.has_value(), file);
        return TRUE;
    }

    logger::get()->info("Loading Chalchiu (v{}) [{}]", chalchiu::version, file);
    logger::get()->info("Found CoronaSDK at 0x{}", corona->get_start(), file);
    logger::get()->info("Found Lua at 0x{}", lua->get_start(), file);

    static auto corona_init = corona->get_symbol("CoronaWin32RuntimeRun");
    static auto new_state = lua->get_symbol("lua_newstate");

    if (!corona_init || !new_state)
    {
        logger::get()->error("No 'CoronaWin32RuntimeRun' [{}] or 'lua_newstate' [{}] found", corona_init, new_state);
        return TRUE;
    }

    logger::get()->info("Found 'CoronaWin32RuntimeRun' at 0x{}", corona_init);
    logger::get()->info("Found 'lua_newstate' at 0x{}", new_state);

    detour_corona_init = lime::detour::create(corona_init, hk_corona_init);
    detour_new_state = lime::detour::create(new_state, hk_new_state);

    return TRUE;
}