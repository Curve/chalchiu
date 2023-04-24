#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <filesystem>
#include <sol/sol.hpp>

namespace chalchiu
{
    struct mod
    {
        std::string name;
        std::string description;
    };

    struct script : public mod
    {
        std::function<void()> callback;
    };

    struct hook : public mod
    {
        std::string target;
        std::function<void(const sol::object &)> callback;
    };

    class lua
    {
        static std::unique_ptr<lua> m_instance;

      private:
        static const std::string init_code;
        static const std::string done_code;

      private:
        sol::state_view m_state;
        std::filesystem::path m_mod_dir;

      private:
        std::vector<std::shared_ptr<const mod>> m_mods;
        std::multimap<std::string, std::shared_ptr<const hook>> m_hooks;

      private:
        lua(lua_State *);

      public:
        sol::object req(const std::string &);
        void print(const sol::variadic_args &);
        void intercept(const std::string &, const sol::object &);

      public:
        void load_mods();

      public:
        static void init(lua_State *);
    };
} // namespace chalchiu