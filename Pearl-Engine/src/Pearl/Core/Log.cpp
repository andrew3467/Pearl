//
// Created by Andrew Graser on 2/7/2024.
//

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Pearl {

    std::shared_ptr<spdlog::logger> Log::sCoreLogger;
    std::shared_ptr<spdlog::logger> Log::sClientLogger;

    void Pearl::Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        sCoreLogger = spdlog::stdout_color_mt("PEARL");
        sCoreLogger->set_level(spdlog::level::trace);


        sClientLogger = spdlog::stdout_color_mt("APP");
        sClientLogger->set_level(spdlog::level::trace);
    }
}
