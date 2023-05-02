#include "lua.hpp"
#include "mod.hpp"
#include "logger.hpp"
#include "constants.hpp"

#include <map>
#include <ranges>
#include <filesystem>
#include <string_view>

namespace chalchiu
{
    namespace fs = std::filesystem;

    struct lua::impl
    {
        fs::path mod_dir;
        sol::state_view state;

      public:
        std::vector<std::unique_ptr<mod>> mods;
        std::multimap<std::string, std::function<void(const sol::object &)>> hooks;
    };

    std::unique_ptr<lua> lua::m_instance;

    lua::lua(lua_State *state)
        : m_impl(std::make_unique<impl>(
              impl{.mod_dir = fs::absolute(fs::current_path() / "mods"), .state = state, .mods = {}, .hooks = {}}))
    {
        if (!fs::exists(m_impl->mod_dir))
        {
            fs::create_directories(m_impl->mod_dir);
        }

        logger::get()->info("[lua] Starting initialization, mod directory is '{}'", m_impl->mod_dir.string());

        setup_handlers();
        setup_hooks();

        logger::get()->info("[lua] Handlers and Hooks setup!");

        setup_mods();

        std::string old_title = m_impl->state["native"]["getProperty"]("windowTitleText");
        auto new_title = fmt::format("{} | chalchiu v{} | {} mod(s) loaded", old_title, version, m_impl->mods.size());

        m_impl->state["native"]["setProperty"]("windowTitleText", new_title);

        logger::get()->info("[lua] Finished initialization");
    }

    lua::~lua() = default;

    void lua::setup_handlers()
    {
        using exception_t = sol::optional<const std::exception &>;

        m_impl->state.set_exception_handler([](auto *state, exception_t exception, sol::string_view description) {
            const auto error = exception ? exception->what() : description;
            logger::get()->error("[exception] An exception occurred: '{}'", error);
            return sol::stack::push(state, description);
        });

        auto panic = [](const sol::optional<std::string> &message) {
            logger::get()->error("[panic] Panic: '{}'", message.value_or("<unknown>"));
        };

        m_impl->state.set_panic(sol::c_call<decltype(panic), panic>);
    }

    void lua::setup_hooks()
    {
        m_impl->state["hooks"] = m_impl->state.create_table();
        m_impl->state["hooks"]["add"] = [this](const std::string &module, const sol::function &callback,
                                               const sol::optional<std::string> &callee) {
            logger::get()->info("[hooks] '{}' registered hook for '{}'", callee.value_or("<unknown>"), module);
            m_impl->hooks.emplace(module, callback.as<std::function<void(const sol::object &)>>());
        };

        m_impl->state.do_string(R"lua(
            function detour(table, func, detour)
                local original = table[func]
                
                table[func] = function(...)
                    return detour(original, ...)
                end
            end
        )lua");

        auto print = m_impl->state["print"].get<std::function<void(const sol::variadic_args &)>>();
        m_impl->state["print"] = [print, this](const sol::variadic_args &args) {
            using std::views::transform;

            auto to_string = m_impl->state["tostring"];
            auto str_args = args | transform([&](const auto &x) { return to_string(x); });

            std::vector<std::string> to_print{str_args.begin(), str_args.end()};
            logger::get()->info("[print] {}", fmt::join(to_print, ", "));

            return print(args);
        };

        auto require = m_impl->state["require"].get<std::function<sol::object(const std::string &)>>();
        m_impl->state["require"] = [require, this](const std::string &module) {
            auto rtn = require(module);

            if (!m_impl->hooks.contains(module))
            {
                return rtn;
            }

            using std::views::filter;
            auto hooks = m_impl->hooks | filter([&](auto &x) { return x.first == module; });

            logger::get()->debug("[require] Invoking {} hook(s) registered for '{}'",
                                 std::distance(hooks.begin(), hooks.end()), module);

            for (const auto &[_, hook] : hooks)
            {
                hook(rtn);
            }

            return rtn;
        };
    }

    void lua::setup_mods()
    {
        auto dir = fs::recursive_directory_iterator(m_impl->mod_dir);

        for (const auto &file : dir)
        {
            if (!file.is_regular_file())
                continue;

            const auto &path = file.path();

            if (path.filename() != "init.lua")
                continue;

            logger::get()->info("[mods] Loading '{}'", path.string());
            auto mod = mod::load(path, m_impl->state);

            if (!mod)
            {
                logger::get()->info("[mods] Failed to load '{}'", path.string());
                continue;
            }

            m_impl->mods.emplace_back(std::move(mod));
        }

        logger::get()->info("[mods] Loaded {} mod(s)", m_impl->mods.size());
    }

    void lua::init(lua_State *state)
    {
        if (m_instance)
        {
            return;
        }

        m_instance = std::unique_ptr<lua>(new lua{state});
    }
} // namespace chalchiu