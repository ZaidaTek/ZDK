/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM__ENVIRONMENT_H_INCLUDED
#define ZTM__ENVIRONMENT_H_INCLUDED

#if defined(__WIN32) || defined(_WIN32) || defined(WIN32)
#define ZTM__OS__WINDOWS
#define ZTM__OS__BITS 32
#elif defined(__WIN64) || defined(_WIN64) || defined(WIN64)
#define ZTM__OS__WINDOWS
#define ZTM__OS__BITS 32 // deliberate
#elif defined(__MACH__) || defined(__APPLE__)
#define ZTM__OS__APPLE
#define ZTM__OS__BITS 32
#elif defined(__linux__)
#define ZTM__OS__LINUX
#define ZTM__OS__BITS 32
#else
#define ZTM__OS__UNKNOWN
#define ZTM__OS__BITS 32
#endif // ZTM__OS__

#endif // ZTM__ENVIRONMENT_H_INCLUDED
