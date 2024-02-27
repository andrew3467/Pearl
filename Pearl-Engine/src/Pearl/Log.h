//
// Created by Andrew Graser on 2/7/2024.
//

#ifndef PEARL_LOG_H
#define PEARL_LOG_H


#include <memory>
#include "spdlog/spdlog.h"
#include "Core.h"

namespace Pearl {
    class Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return sCoreLogger; }

        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return sClientLogger; }

    private:
        static Ref<spdlog::logger> sCoreLogger;
        static Ref<spdlog::logger> sClientLogger;
    };
}


//TODO only include with release
#define PRL_CORE_TRACE(...)    ::Pearl::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PRL_CORE_INFO(...)     ::Pearl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PRL_CORE_WARN(...)     ::Pearl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PRL_CORE_ERROR(...)    ::Pearl::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PRL_CORE_FATAL(...)    ::Pearl::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define PRL_TRACE(...)    ::Pearl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PRL_INFO(...)     ::Pearl::Log::GetClientLogger()->info(__VA_ARGS__)
#define PRL_WARN(...)     ::Pearl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PRL_ERROR(...)    ::Pearl::Log::GetClientLogger()->error(__VA_ARGS__)
#define PRL_FATAL(...)    ::Pearl::Log::GetClientLogger()->critical(__VA_ARGS__)


#endif //PEARL_LOG_H
