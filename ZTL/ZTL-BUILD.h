/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL_BUILD_H_INCLUDED
#define ZTL_BUILD_H_INCLUDED

#if !defined(ZTM_BUILD_WIDTH) || !(ZTM_BUILD_WIDTH)
	#define ZTL_BUILD_WIDTH 32
#else // ZTM_BUILD_WIDTH
	#define ZTL_BUILD_WIDTH ZTM_BUILD_WIDTH
#endif // ZTM_BUILD_WIDTH

#if defined(ZTM_BUILD_WINDOWS)
	#define ZTL__OS__WINDOWS
#elif defined(ZTM_BUILD_LINUX)
	#define ZTL__OS__LINUX
#else
	#define ZTL__OS__UNKNOWN
#endif // ZTL__OS__

#endif //ZTL_BUILD_H_INCLUDED
