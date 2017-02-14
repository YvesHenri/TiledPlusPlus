#ifndef TPP_MACROS_OS_H
#define TPP_MACROS_OS_H

////////////////////////////////////////////////////////////
// Identify the operating system
// see http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
////////////////////////////////////////////////////////////
#if defined(_WIN32)

	// Windows
	#define TILEDPP_OS_WINDOWS

#elif defined(__APPLE__) && defined(__MACH__)

	#include "TargetConditionals.h" // Requires "Command Line Tools for Xcode" package

	// Apple platform, see which one it is
	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		#define TILEDPP_OS_IOS
	#elif TARGET_OS_MAC
		#define TILEDPP_OS_MACOS
	#else
		#error This Apple operating system is not supported by SFML library
	#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

#elif defined(__unix__)

	// UNIX system, see which one it is
	#if defined(__ANDROID__)
		#define TILEDPP_OS_ANDROID
	#elif defined(__linux__)
		#define TILEDPP_OS_LINUX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		#define TILEDPP_OS_FREEBSD
	#else
		#error This UNIX operating system is not supported by SFML library
	#endif // defined(__ANDROID__)

#else

	#error This operating system is not supported by SFML library

#endif // defined(_WIN32)

#endif // ifndef TPP_MACROS_OS_H
