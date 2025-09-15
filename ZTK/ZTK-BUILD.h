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

#if defined(ZTL_BUILD_WINDOWS) && (ZTL_BUILD_WINDOWS)
	#define ZTK_BUILD_WINDOWS 0x1
#elif defined(ZTL_BUILD_APPLE) && (ZTL_BUILD_APPLE)
	#define ZTK_BUILD_APPLE 0x1
#elif defined(ZTL_BUILD_LINUX) && (ZTL_BUILD_LINUX)
	#define ZTK_BUILD_LINUX 0x1
#elif defined(ZTL_BUILD_AVR) && (ZTL_BUILD_AVR)
	#define ZTK_BUILD_AVR 0x1
#else
	#define ZTK_BUILD_UNKNOWN 0x1
	#warning "ZTK-BUILD-WARNING: 'ZTK_BUILD_UNKNOWN' is defined"
#endif // ZTK_BUILD_OS

#endif // ZTK_BUILD_H_INCLUDED
