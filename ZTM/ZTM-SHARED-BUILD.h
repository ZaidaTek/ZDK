/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_SHARED_BUILD_H_INCLUDED
#define ZTM_SHARED_BUILD_H_INCLUDED

#if   defined(__AVR)
	#define ZTM_BUILD_WIDTH 8
#elif defined(__x86_64__)
	#define ZTM_BUILD_WIDTH 64
#elif defined(__i386__)
	#define ZTM_BUILD_WIDTH 32
#else // ZTM_BUILD_WIDTH
	#define ZTM_BUILD_WIDTH 32
	#warning "ZTM-BUILD-WARNING: 'ZTM_BUILD_WIDTH' defaulting to 32"
#endif // ZTM_BUILD_WIDTH

#if   defined(__AVR)
	#define ZTM_BUILD_AVR 0x1
	#ifndef ZTM_BUILD_EMBED
		#define ZTM_BUILD_EMBED 0x1
	#endif // ZTM_BUILD_EMBED
#elif defined(__WIN64) || defined(_WIN64) || defined(WIN64)
	#define ZTM_BUILD_WINDOWS 0x1
#elif defined(__WIN32) || defined(_WIN32) || defined(WIN32)
	#define ZTM_BUILD_WINDOWS 0x1
#elif defined(__MACH__) || defined(__APPLE__)
	#define ZTM_BUILD_APPLE
#elif defined(__linux__)
	#define ZTM_BUILD_LINUX 0x1
#else // ZTM_BUILD_UNKNOWN
	#define ZTM_BUILD_UNKNOWN 0x1
	#warning "ZTM-BUILD-WARNING: 'ZTM_BUILD_UNKNOWN' is defined"
#endif // ZTM_BUILD_OS

#endif // ZTM_SHARED_BUILD_H_INCLUDED
