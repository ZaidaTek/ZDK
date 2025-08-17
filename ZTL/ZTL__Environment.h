/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL__ENVIRONMENT_H_INCLUDED
#define ZTL__ENVIRONMENT_H_INCLUDED

#if defined(ZTM__OS__WINDOWS)
#define ZTL__OS__WINDOWS
#elif defined(ZTM__OS__LINUX)
#define ZTL__OS__LINUX
#else
#define ZTL__OS__UNKNOWN
#endif // ZTL__OS__

#endif //ZTL__ENVIRONMENT_H_INCLUDED
