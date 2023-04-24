#include "lua.hpp"
#include "logger.hpp"
#include "constants.hpp"

#include <ranges>
#include <filesystem>
#include <sol/forward.hpp>

namespace fs = std::filesystem;

namespace chalchiu
{
    const std::string lua::init_code = R"lua(
        local original = require

        require = function(module)
            local rtn = original(module)
            intercept(module, rtn)
            return rtn
        end
    )lua";

    const std::string lua::done_code = R"lua(
        local old_title = native.getProperty("windowTitleText")
        native.setProperty("windowTitleText", old_title .. " | chalchiu [v{}], {} mod(s) loaded")
    )lua";

    std::unique_ptr<lua> lua::m_instance;

    lua::lua(lua_State *state) : m_state(state), m_mod_dir(fs::absolute(fs::current_path() / "mods"))
    {
        if (!fs::exists(m_mod_dir))
        {
            fs::create_directories(m_mod_dir);
        }

        m_state.set_function("intercept", &lua::intercept, std::ref(*this));
        m_state.set_function("print", &lua::print, std::ref(*this));
        m_state.set_function("req", &lua::req, std::ref(*this));

        m_state.do_string(init_code);
        load_mods();

        m_state.do_string(fmt::vformat(done_code, fmt::make_format_args(version, m_mods.size())));
    }

    sol::object lua::req(const std::string &module)
    {
        std::optional<fs::path> file;

        for (const auto &entry : fs::recursive_directory_iterator(m_mod_dir))
        {
            if (!entry.is_regular_file())
                continue;

            if (entry.path().filename() != (module + ".lua"))
                continue;

            file = entry.path();
            break;
        }

        if (!file)
        {
            logger::get()->error("[req] Could not find module '{}'", module);
            return {};
        }

        logger::get()->debug("[req] Loading Module '{}' ['{}']", module, file->string());
        return m_state.require_file(module, file->string(), false);
    }

    void lua::print(const sol::variadic_args &args)
    {
        std::vector<std::string> to_print;

        for (const auto &arg : args)
        {
            to_print.emplace_back(m_state["tostring"](arg));
        }

        logger::get()->debug("[print] {}", fmt::join(to_print, " "));
    }

    void lua::intercept(const std::string &module, const sol::object &table)
    {
        if (!m_hooks.contains(module))
        {
            return;
        }

        logger::get()->info("[intercept] {} mods(s) with hook: '{}'", m_hooks.count(module), module);

        for (const auto &[_, hook] : m_hooks | std::views::filter([&](const auto &x) { return x.first == module; }))
        {
            logger::get()->debug("[hooks] Calling: '{}'", hook->name);
            hook->callback(table);
        }
    }

    void lua::load_mods()
    {
        auto dir = fs::recursive_directory_iterator(m_mod_dir);

        for (const auto &file : dir)
        {
            if (!file.is_regular_file())
                continue;

            if (!file.path().has_extension())
                continue;

            auto filename = file.path().filename().string();

            if (!filename.ends_with(".mod.lua"))
                continue;

            logger::get()->info("[mods] Loading: '{}'", filename);

            auto path = fs::absolute(file.path());
            auto info = m_state.do_file(path.string()).get<sol::table>();

            auto name = info["name"].get<std::string>();
            auto description = info["description"].get<std::string>();

            if (info["target"].valid())
            {
                auto target = info["target"].get<std::string>();
                auto callback = info["hook"].get<std::function<void(const sol::object &)>>();

                auto mod = std::make_shared<const hook>(hook{{name, description}, target, callback});

                m_mods.emplace_back(mod);
                m_hooks.emplace(target, mod);

                logger::get()->info("[mods] Loaded: '{}' [Hook: '{}']", name, target);

                continue;
            }

            auto callback = info["script"].get<std::function<void()>>();

            auto mod = std::make_shared<const script>(script{{name, description}, callback});
            m_mods.emplace_back(mod);

            mod->callback();
            logger::get()->info("[mods] Loaded: '{}'", name);
        }

        logger::get()->info("[mods] Finished ({} mod(s) loaded)", m_mods.size());
    }

    void lua::init(lua_State *state)
    {
        if (m_instance)
        {
            return;
        }

        m_instance = std::unique_ptr<lua>(new lua{state});
        logger::get()->info("[lua] initialized (0x{})", reinterpret_cast<std::uintptr_t>(state));
    }
} // namespace chalchiu