/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM__ENVIRONMENT_H_INCLUDED
#define ZTM__ENVIRONMENT_H_INCLUDED

#if defined(__WIN32) || defined(_WIN32) || defined(WIN32)
#define ZTM_ARCH__WIN
#define ZTM_ARCH__BIT 32
#elif defined(__WIN64) || defined(_WIN64) || defined(WIN64)
#define ZTM_ARCH__WIN
#define ZTM_ARCH__BIT 32
#elif defined(__MACH__) || defined(__APPLE__)
#define ZTM_ARCH__MAC
#define ZTM_ARCH__BIT 32
#else
#define ZTM_ARCH__LIN
#define ZTM_ARCH__BIT 32
#endif // ZTM_ARCH__

#define ZTM__INCL__MAIN <stdlib.h> // malloc(), realloc(), free()
#define ZTM__INCL__TIME <time.h> // clock(), time(), gmtime(), mktime(), struct tm, time_t
#define ZTM__INCL__LIST <stdlib.h> // qsort()

#endif // ZTM__ENVIRONMENT_H_INCLUDED
