#include "mod.hpp"
#include "logger.hpp"

#include <map>
#include <regex>
#include <fstream>
#include <filesystem>

namespace chalchiu
{
    namespace fs = std::filesystem;

    struct mod::impl
    {
        sol::environment env;

      public:
        std::string name;
        std::string author;
        std::string version;
        std::string description;
    };

    mod::mod() : m_impl(std::make_unique<impl>()) {}

    mod::~mod() = default;

    mod::mod(mod &&other) noexcept : m_impl(std::move(other.m_impl))
    {
        other.m_impl = nullptr;
    }

    std::string mod::name() const
    {
        return m_impl->name;
    }

    std::string mod::author() const
    {
        return m_impl->author;
    }

    std::string mod::version() const
    {
        return m_impl->version;
    }

    std::string mod::description() const
    {
        return m_impl->description;
    }

    std::unique_ptr<mod> mod::load(const fs::path &file, sol::state_view &state)
    {
        if (!fs::exists(file))
        {
            logger::get()->warn("[mod] '{}' does not exist", file.string());
            return nullptr;
        }

        if (!fs::is_regular_file(file))
        {
            logger::get()->warn("[mod] '{}' is not a regular file", file.string());
            return nullptr;
        }

        auto rtn = std::unique_ptr<mod>(new mod);
        auto folder_name = file.parent_path().filename().string();

        rtn->m_impl->env = sol::environment{state, sol::create, state.globals()};

        //? Expose write access to globals
        rtn->m_impl->env["globals"] = state.globals();

        //? Expose "detour" as non namespaced function
        rtn->m_impl->env["detour"] = rtn->m_impl->env["chalchiu"]["detour"];

        //? Overwrite hooks, so that the mod name is passed as the callee
        rtn->m_impl->env["hooks"] = state.create_table();
        rtn->m_impl->env["hooks"]["add"] = [=, impl = rtn->m_impl.get()](const sol::variadic_args &args) {
            return impl->env["chalchiu"]["hooks"]["add"](sol::as_args(args), folder_name);
        };

        //? Overwrite "require" so that we can properly load files in the same mod folder
        static std::map<fs::path, sol::object> loaded;

        rtn->m_impl->env["require"] = [=, impl = rtn->m_impl.get()](const std::string &name) mutable {
            const auto mod_folder = fs::absolute(file.parent_path());
            const auto target_path = fmt::format("{}.lua", std::regex_replace(name, std::regex{"\\."}, "/"));

            const auto target = fs::weakly_canonical(mod_folder / target_path);

            if (!target.string().starts_with(mod_folder.string()) || !fs::exists(target))
            {
                logger::get()->error("[mod] [{}] [require] Bad file: '{}'", folder_name, target.string());

                auto error = std::system_error(std::make_error_code(std::errc::no_such_file_or_directory));
                return sol::make_object(state, sol::error(error.what()));
            }

            if (loaded.contains(target))
            {
                logger::get()->debug("[mod] [{}] [require] Reusing '{}' ", folder_name, target.string());
                return loaded.at(target);
            }

            logger::get()->debug("[mod] [{}] [require] Loading '{}'", folder_name, target.string());
            auto result = state.script_file(target.string(), impl->env);

            if (!result.valid())
            {
                auto error = result.get<sol::error>();
                logger::get()->error("[mod] [{}] [require] {}", folder_name, error.what());

                return sol::make_object(state, error.what());
            }

            auto rtn = result.get<sol::object>();
            loaded.emplace(target, rtn);

            return rtn;
        };

        auto mod = state.script_file(file.string(), rtn->m_impl->env);

        if (!mod.valid())
        {
            auto error = mod.get<sol::error>();
            logger::get()->error("[mod] Failed to load '{}': {}", file.string(), error.what());

            return nullptr;
        }

        auto info = mod.get<sol::table>();

        rtn->m_impl->name = info["name"].get_or(folder_name);
        rtn->m_impl->author = info["author"].get_or<std::string>("<unknown>");
        rtn->m_impl->version = info["version"].get_or<std::string>("<unknown>");
        rtn->m_impl->description = info["description"].get_or<std::string>("<unknown>");

        logger::get()->info("[mod] Finished loading '{}' ({}) [made by {}]", rtn->m_impl->name, rtn->m_impl->version,
                            rtn->m_impl->author);

        return rtn;
    }
} // namespace chalchiu