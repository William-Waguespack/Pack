#pragma once


#ifdef PACK_PLATFORM_WINDOWS
	#ifdef PACK_BUILD_DLL
		#define PACK_API __declspec(dllexport)
	#else
		#define PACK_API __declspec(dllimport)
	#endif
#else
	#error Pack only Supprots Windows!
#endif

#define BIT(x) (1 << x)

#ifdef PACK_DEBUG
 #define PACK_ENABLE_ASSERTS
#endif

#ifdef PACK_ENABLE_ASSERTS
	#define PACK_ASSERT(x, ...) {if (!(x)) {PACK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define PACK_CORE_ASSERT(x, ...) {if (!(x)) {PACK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define PACK_ASSERT(x, ...)
	#define PACK_CORE_ASSERT(x, ...)
#endif

#define PACK_BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)