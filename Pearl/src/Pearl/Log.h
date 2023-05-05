#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <memory>

namespace Pearl {
	class PRL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


//Core log macros
#define PRL_CORE_TRACE(...)		::Pearl::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PRL_CORE_INFO(...)		::Pearl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PRL_CORE_WARN(...)		::Pearl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PRL_CORE_ERROR(...)		::Pearl::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PRL_CORE_FATAL(...)		::Pearl::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define PRL_TRACE(...)			::Pearl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PRL_INFO(...)			::Pearl::Log::GetClientLogger()->info(__VA_ARGS__)
#define PRL_WARN(...)			::Pearl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PRL_ERROR(...)			::Pearl::Log::GetClientLogger()->error(__VA_ARGS__)
#define PRL_FATAL(...)			::Pearl::Log::GetClientLogger()->fatal(__VA_ARGS__)


+
