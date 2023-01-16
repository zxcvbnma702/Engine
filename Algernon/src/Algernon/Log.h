#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Algernon {
	class ALGERNON_API Log
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

// Core log macros
#define AL_CORE_TRACE(...)    ::Algernon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AL_CORE_INFO(...)     ::Algernon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AL_CORE_WARN(...)     ::Algernon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AL_CORE_ERROR(...)    ::Algernon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AL_CORE_FATAL(...)    ::Algernon::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define AL_TRACE(...)	      ::Algernon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AL_INFO(...)	      ::Algernon::Log::GetClientLogger()->info(__VA_ARGS__)
#define AL_WARN(...)	      ::Algernon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AL_ERROR(...)	      ::Algernon::Log::GetClientLogger()->error(__VA_ARGS__)
#define AL_FATAL(...)	      ::Algernon::Log::GetClientLogger()->fatal(__VA_ARGS__)