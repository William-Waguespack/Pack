#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace Pack
{
	class PACK_API Log
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



//Core log Macros
#define PACK_CORE_ERROR(...) ::Pack::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PACK_CORE_WARN(...)  ::Pack::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PACK_CORE_INFO(...)  ::Pack::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PACK_CORE_TRACE(...) ::Pack::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PACK_CORE_FATAL(...) ::Pack::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log Macros
#define PACK_ERROR(...) ::Pack::Log::GetClientLogger()->error(__VA_ARGS__)
#define PACK_WARN(...)  ::Pack::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PACK_INFO(...)  ::Pack::Log::GetClientLogger()->info(__VA_ARGS__)
#define PACK_TRACE(...) ::Pack::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PACK_FATAL(...) ::Pack::Log::GetClientLogger()->fatal(__VA_ARGS__)

