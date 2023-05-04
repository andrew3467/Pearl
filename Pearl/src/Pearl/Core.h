#pragma once

#ifdef PRL_PLATFORM_WINDOWS
	#ifdef PRL_BUILD_DLL
		#define PRL_API __declspec(dllexport)
	#else
		#define PRL_API __declspec(dllimport)
	#endif
#else
	#error Pearl Only Supports Windows!
#endif
