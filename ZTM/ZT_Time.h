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
ZT_TIME ZTM_Tick(void); // return millisecond-timer

ZT_TIME ZTM_Time(void); // return local unix time
ZT_TIME ZTM_TimeUTC(void); // return UTC unix time
ZT_TIME ZTM_TimeDate(const ZT_DATE* iDate); // return iDate unix time

ZT_TIME ZTM_TimeZone(void); // return time-zone in seconds
ZT_INDEX ZTM_TimeWeekday(ZT_INDEX iTime);

void ZTM_Date(ZT_TIME iTime, ZT_DATE* oDate);
void ZTM_DateExtra(ZT_TIME iTime, ZT_DATE_EXTRA* oDate);

ZT_DATE* ZTM_DateNew(ZT_TIME iTime);
ZT_DATE_EXTRA* ZTM_DateExtraNew(ZT_TIME iTime);
//ZT_FLAG ZTM_DateValid(const ZT_DATE* iDate); // need to be updated after conversion to 4-digit year system
//ZT_FLAG ZTM_DateCoerce(ZT_DATE* iDate);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_TIME_H_INCLUDED
