#include "logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace chalchiu
{
    std::unique_ptr<logger> logger::m_instance;

    logger::logger()
    {
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("chalchiu.txt");
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        m_logger = std::make_unique<spdlog::logger>("chalchiu", spdlog::sinks_init_list{console_sink, file_sink});

        m_logger->set_level(spdlog::level::trace);
        m_logger->flush_on(spdlog::level::trace);
    }

    spdlog::logger *logger::operator->()
    {
        return m_logger.get();
    }

    logger &logger::get()
    {
        if (!m_instance)
        {
            m_instance = std::unique_ptr<logger>(new logger);
        }

        return *m_instance;
    }
} // namespace chalchiu