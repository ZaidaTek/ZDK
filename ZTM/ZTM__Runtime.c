/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM__RUNTIME_C_INCLUDED
#define ZTM__RUNTIME_C_INCLUDED

#include "ZTM__Runtime.h"

ZT_U32			rZTM__SEED = 0x1;
ZT_FLAG			rZTM_COLOR__PALLETE = 0x0;
ZT_COLOR		rZTM_COLOR__SHIFT[3] = {0x0};
const ZT_TIME	rZTM_TIME__DAYSPERMONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
ZT_TIME			rZTM_TIME__ZONE = 0;
ZT_FLAG			rZTM_TIME__ZONE_INIT = 0x0;

ZT_U8			rZTC8__ISO8601__[20] = {ZTM_CHAR_NT};
const ZT_U8*	rZTC8__DAY[7] = {(const ZT_U8*)"Sun", (const ZT_U8*)"Mon", (const ZT_U8*)"Tue", (const ZT_U8*)"Wed", (const ZT_U8*)"Thu", (const ZT_U8*)"Fri", (const ZT_U8*)"Sat",};
const ZT_U8*	rZTC8__MONTH[12] = {(const ZT_U8*)"Jan", (const ZT_U8*)"Feb", (const ZT_U8*)"Mar", (const ZT_U8*)"Apr", (const ZT_U8*)"May", (const ZT_U8*)"Jun", (const ZT_U8*)"Jul", (const ZT_U8*)"Aug", (const ZT_U8*)"Sep", (const ZT_U8*)"Oct", (const ZT_U8*)"Nov", (const ZT_U8*)"Dec",};

#endif // ZTM__RUNTIME_C_INCLUDED
