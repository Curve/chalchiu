#include "logger.hpp"

#include <lua.hpp>
#include <windows.h>
#include <lime/hooks/detour.hpp>

lua_State *lua_state = nullptr;
std::unique_ptr<lime::detour> o_newstate;

lua_State *hk_new_state(void *alloc, void *user_data)
{
    auto *original = o_newstate->get_original<decltype(hk_new_state) *>()(alloc, user_data);

    if (!lua_state)
    {
        chalchiu::logger::get()->info("[lua_newstate] state: {}", reinterpret_cast<std::uintptr_t>(original));
        lua_state = original;
    }

    return original;
}

extern "C" __declspec(dllexport) bool CoronaWin32RuntimeRun(int param, HWND *hwnd)
{
    static auto *lua = LoadLibrary("lua.dll");
    static auto *lib = LoadLibrary("orig.dll");

    // clang-format off
    static auto original = reinterpret_cast<decltype(CoronaWin32RuntimeRun) *>(GetProcAddress(lib, "CoronaWin32RuntimeRun")); 
    static auto new_state = reinterpret_cast<decltype(hk_new_state) *>(GetProcAddress(lua, "lua_newstate"));
    // clang-format on

    chalchiu::logger::get()->info("[CoronaWin32RuntimeRun] new_state: {}", reinterpret_cast<std::uintptr_t>(new_state));

    o_newstate = lime::detour::create(new_state, hk_new_state);
    auto rtn = original(param, hwnd);
    o_newstate.reset();

    chalchiu::lua::init(lua_state);

    return rtn;
}