/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL_BUILD_H_INCLUDED
#define ZTL_BUILD_H_INCLUDED

#if defined(ZTM_BUILD_WIDTH)
	#define ZTL_BUILD_WIDTH ZTM_BUILD_WIDTH
#else // ZTM_BUILD_WIDTH
	#define ZTL_BUILD_WIDTH 32
	#warning "ZTL-BUILD-WARNING: 'ZTM_BUILD_WIDTH' is not defined"
#endif // ZTM_BUILD_WIDTH

#if defined(ZTM_BUILD_WINDOWS) && (ZTM_BUILD_WINDOWS)
	#define ZTL_BUILD_WINDOWS 0x1
#elif defined(ZTM_BUILD_APPLE) && (ZTM_BUILD_APPLE)
	#define ZTL_BUILD_APPLE 0x1
#elif defined(ZTM_BUILD_LINUX) && (ZTM_BUILD_LINUX)
	#define ZTL_BUILD_LINUX 0x1
#elif defined(ZTM_BUILD_AVR) && (ZTM_BUILD_AVR)
	#define ZTL_BUILD_AVR 0x1
#else
	#define ZTL_BUILD_UNKNOWN 0x1
	#warning "ZTL-BUILD-WARNING: 'ZTL_BUILD_UNKNOWN' is defined"
#endif // ZTL_BUILD_OS

#endif //ZTL_BUILD_H_INCLUDED
