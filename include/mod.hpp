#pragma once
#include <string>
#include <memory>
#include <filesystem>
#include <sol/sol.hpp>

namespace chalchiu
{
    class mod
    {
        struct impl;

      private:
        std::unique_ptr<impl> m_impl;

      private:
        mod();

      public:
        ~mod();

      public:
        mod(mod &&) noexcept;

      public:
        [[nodiscard]] std::string name() const;
        [[nodiscard]] std::string author() const;
        [[nodiscard]] std::string version() const;
        [[nodiscard]] std::string description() const;

      public:
        static std::unique_ptr<mod> load(const std::filesystem::path &, sol::state_view &);
    };
} // namespace chalchiu