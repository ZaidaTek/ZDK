/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM__RUNTIME_H_INCLUDED
#define ZTM__RUNTIME_H_INCLUDED

#include <stdarg.h>
#include "ZTM.h"

#define ZTM__INCL__MAIN <stdlib.h> // malloc(), realloc(), free()
#define ZTM__INCL__CHAR <stdio.h> // vsnprintf(), etc.
#define ZTM__INCL__TIME <time.h> // clock(), time(), gmtime(), mktime(), struct tm, time_t
#define ZTM__INCL__LIST <stdlib.h> // qsort()

extern ZT_U32			rZTM__SEED_32;
extern ZT_U64			rZTM__SEED_64;
extern const ZT_TIME	rZTM_TIME__DAYSPERMONTH[12];
extern ZT_FLAG			rZTM_TIME__INIT;
extern ZT_TIME			rZTM_TIME__ZONE;
extern ZT_TIME			rZTM_TIME__UTC;
extern ZT_TIME			rZTM_TIME__LOCAL;

extern ZT_U8			rZTC8__ISO8601__[20];
extern const ZT_U8*	rZTC8__DAY[7];
extern const ZT_U8*	rZTC8__MONTH[12];

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_SIZE ZTC8_RuntimeFormat(ZT_CHAR* oTarget, ZT_SIZE iCapacity, const ZT_CHAR* iFormatText, va_list* iArgs);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTM__RUNTIME_H_INCLUDED
