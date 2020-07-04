/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_TIME_H_INCLUDED
#define ZT_TIME_H_INCLUDED

// 2019-06-10 *thoroughly* re-test this
// retested, removed milliseconds, want to make year four digits, compatibility conflicts with present two digits undetermined
// 2020-02-21 changed to 4-digit year on ZCW, yet to check compat with others
#include "ZTM.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_TIME ZTM_TimeGet(const ZT_DATE* iDate);
ZT_INDEX ZTM_WeekDay(ZT_INDEX iTime);
ZT_DATE* ZTM_DateGet(ZT_TIME iTime);
ZT_DATE* ZTM_DateRead(ZT_TIME iTime, ZT_DATE* oDate);
ZT_DATE_EXTRA* ZTM_DateExtraGet(ZT_TIME iTime);
ZT_DATE_EXTRA* ZTM_DateExtraRead(ZT_DATE_EXTRA* oDate, ZT_TIME iTime);
//ZT_FLAG ZTM_DateValid(const ZT_DATE* iDate); // need to be updated after conversion to 4-digit year system
//ZT_FLAG ZTM_DateCoerce(ZT_DATE* iDate);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_TIME_H_INCLUDED
