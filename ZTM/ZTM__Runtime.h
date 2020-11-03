/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM__RUNTIME_H_INCLUDED
#define ZTM__RUNTIME_H_INCLUDED

#include "ZTM.h"

ZT_U32			rZTM__SEED;
ZT_FLAG			rZTM_COLOR__PALLETE;
ZT_COLOR		rZTM_COLOR__SHIFT[3];
const ZT_TIME	rZTM_TIME__DAYSPERMONTH[12];
ZT_TIME			rZTM_TIME__ZONE;
ZT_FLAG			rZTM_TIME__ZONE_INIT;

ZT_U8			rZTC8__ISO8601__[20];
const ZT_U8*	rZTC8__DAY[7];
const ZT_U8*	rZTC8__MONTH[12];

#endif // ZTM__RUNTIME_H_INCLUDED
