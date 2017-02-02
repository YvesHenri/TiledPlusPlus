#ifndef TPP_MACROS_EXPORTER_H_
#define TPP_MACROS_EXPORTER_H_

#include "OS.h"

// If TILEDPP_STATIC is defined as a "Preprocessor Definition", static libs are created instead (does not require .dll)
#if !defined(TILEDPP_STATIC)
	// Windows
	#if defined(TILEDPP_OS_WINDOWS)
		#define TILEDPP_API __declspec(dllexport)
		#define TILEDPP_API_IMPORT __declspec(dllimport)

		// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
		#ifdef _MSC_VER
			#pragma warning(disable: 4251)
		#endif
	// Linux, FreeBSD, Mac OS X
	#else
		#if __GNUC__ >= 4
			// GCC 4 has special keywords for showing/hidding symbols, the same keyword is used for both importing and exporting
			#define TILEDPP_API __attribute__ ((__visibility__ ("default")))
			#define TILEDPP_API_IMPORT __attribute__ ((__visibility__ ("default")))
		#else
			// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
			#define TILEDPP_API
			#define TILEDPP_API_IMPORT
		#endif // __GNUC__ >= 4
	#endif // defined(TILEDPP_OS_WINDOWS)
#else
	// Static build doesn't need import/export macros
	#define TILEDPP_API
	#define TILEDPP_API_IMPORT
#endif // !defined(TILEDPP_STATIC)

#endif // ifndef TPP_MACROS_EXPORTER_H_
