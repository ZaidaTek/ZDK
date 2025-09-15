/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_BUILD_H_INCLUDED
#define ZTK_BUILD_H_INCLUDED

#if defined(ZTL_BUILD_WIDTH)
	#define ZTK_BUILD_WIDTH ZTL_BUILD_WIDTH
#else // ZTL_BUILD_WIDTH
	#define ZTK_BUILD_WIDTH 32
	#warning "ZTK-BUILD-WARNING: 'ZTL_BUILD_WIDTH' is not defined"
#endif // ZTL_BUILD_WIDTH

#if defined(ZTL_BUILD_WINDOWS)
	#define ZTK_BUILD_WINDOWS
#elif defined(ZTL_BUILD_LINUX)
	#define ZTK_BUILD_LINUX
#elif defined(ZTK_BUILD_AVR)
	#define ZTK_BUILD_AVR
#else
	#define ZTK_BUILD_UNKNOWN
	#warning "ZTK-BUILD-WARNING: 'ZTK_BUILD_UNKNOWN' is defined"
#endif // ZTK_BUILD_OS

#endif // ZTK_BUILD_H_INCLUDED
