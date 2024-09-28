#pragma once

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
	#define _CRT_SECURE_NO_WARNINGS
#endif

#if defined(WIN32) || defined(_WIN32)
	#include <winapifamily.h>
#endif

#if defined(_MSC_VER) || defined(__MINGW32__)
	#define TINYFD_DLLEXPORT __declspec(dllexport)
#elif defined(__GNUC__) || defined(__clang__)
	#define TINYFD_DLLEXPORT __attribute__ ((visibility("default")))
#else
	#define TINYFD_DLLEXPORT
#endif