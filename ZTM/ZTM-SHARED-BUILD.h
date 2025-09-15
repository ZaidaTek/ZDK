/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_SHARED_BUILD_H_INCLUDED
#define ZTM_SHARED_BUILD_H_INCLUDED

#if defined(__WIN64) || defined(_WIN64) || defined(WIN64)
	#define ZTM_BUILD_WIDTH 32 // deliberate
	#define ZTM_BUILD_WINDOWS
#elif defined(__WIN32) || defined(_WIN32) || defined(WIN32)
	#define ZTM_BUILD_WIDTH 32
	#define ZTM_BUILD_WINDOWS
#elif defined(__MACH__) || defined(__APPLE__)
	#define ZTM_BUILD_WIDTH 32
	#define ZTM_BUILD_APPLE
#elif defined(__linux__)
	#define ZTM_BUILD_WIDTH 32
	#define ZTM_BUILD_LINUX
#elif defined(__AVR)
	#ifndef ZTM_BUILD_EMBED
		#define ZTM_BUILD_EMBED 0x1
	#endif // ZTM_BUILD_EMBED
	#define ZTM_BUILD_WIDTH 8
	#define ZTM_BUILD_AVR
#else
	#define ZTM_BUILD_WIDTH 32
	#define ZTM_BUILD_UNKNOWN
	#warning "ZTM-BUILD-WARNING: 'ZTM_BUILD_UNKNOWN' is defined"
#endif // ZTM_BUILD_OS

#endif // ZTM_SHARED_BUILD_H_INCLUDED
