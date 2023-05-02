#pragma once
#include <memory>
#include <sol/sol.hpp>

namespace chalchiu
{
    class lua
    {
        struct impl;

      private:
        static std::unique_ptr<lua> m_instance;

      private:
        std::unique_ptr<impl> m_impl;

      private:
        lua(lua_State *);

      public:
        ~lua();

      public:
        void setup_handlers();
        void setup_hooks();
        void setup_mods();

      public:
        static void init(lua_State *state);
    };
} // namespace chalchiu