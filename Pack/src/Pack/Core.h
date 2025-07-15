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