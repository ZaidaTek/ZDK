/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_TIME_C_INCLUDED
#define ZT_TIME_C_INCLUDED

#include "ZTM__Runtime.h"
#include ZTM__INCL__TIME
#define ZTM_CLOCK_RATE CLOCKS_PER_SEC
#define ZTM_CLOCK() clock()
ZT_TIME ZTM_Clock(void) {return ZTM_CLOCK();}
ZT_TIME ZTM_ClockRate(void) {return ZTM_CLOCK_RATE;}
ZT_TIME ZTM_Tick(void) {return ZTM_CLOCK() / (ZTM_CLOCK_RATE / 1000);}
void ZTM_TimeInit(void) {
	const time_t lFixed = 864000;
	struct tm* lUTC = gmtime(&lFixed); // changes time value if time() returns local
	rZTM_TIME__ZONE = lFixed - (ZT_TIME)mktime(lUTC); // changes time value if time() returns UTC
	struct tm lFixedDate = {0x0};
	lFixedDate.tm_year = 70;
	lFixedDate.tm_mday = 11;
	rZTM_TIME__UTC = ((rZTM_TIME__LOCAL = lFixed - (ZT_TIME)mktime(&lFixedDate))) ? 0 : -rZTM_TIME__ZONE; // rZTM_TIME__LOCAL should be zero if time() returns local
	rZTM_TIME__INIT = 0x0;
}
ZT_TIME ZTM_Time(void) {
	if (rZTM_TIME__INIT) {ZTM_TimeInit();}
	return (time(NULL) + rZTM_TIME__LOCAL);
}
ZT_TIME ZTM_TimeUTC(void) {
	if (rZTM_TIME__INIT) {ZTM_TimeInit();}
	return (time(NULL) + rZTM_TIME__UTC);
}
ZT_TIME ZTM_TimeDate(const ZT_DATE* iDate) {
    ///year > 1969 : assume YYYY-input, else assume YY-input
    ZT_TIME lYear = (iDate->year > 1969) ? (iDate->year - 1970) : ((iDate->year < 70) ? (iDate->year + 30) : (iDate->year - 70));
    ZT_TIME lLeap = lYear >> 2;
    switch(lYear & 0x3) {
        default: case 0: case 1: break;
        case 2: if (iDate->month > 2) {++lLeap;} break;
        case 3: ++lLeap; break;
    }
    ZT_TIME lTime = -1;
    for (ZT_INDEX i = 0; i < (ZT_INDEX)(iDate->month - 1); i++) {lTime += rZTM_TIME__DAYSPERMONTH[i];}
    lTime += iDate->day;
    lTime += lLeap;
    lTime += (lYear * 365);
    lTime *= 24;
    lTime += iDate->hour;
    lTime *= 60;
    lTime += iDate->minute ;
    lTime *= 60;
    lTime += iDate->second;
    return lTime;
}
ZT_TIME ZTM_TimeZone(void) {return rZTM_TIME__ZONE;}
ZT_INDEX ZTM_TimeWeekday(ZT_INDEX iTime) {return (((iTime / 86400) + 4) % 7);}
void ZTM_Date(ZT_TIME iTime, ZT_DATE* oDate) {
    oDate->second = iTime % 60;
    oDate->minute = (iTime /= 60) % 60;
    oDate->hour = (iTime /= 60) % 24;
    ZT_U16 lYear = ((iTime /= 24) / 1461) << 2;
    iTime %= 1461;
    ZT_U16 lLeap = 0;
    while (iTime >= 365) {
        if (lLeap == 2) {if (iTime > 365) {iTime--;} else {break;}}
        lLeap++;
        iTime -= 365;
    }
    lYear += lLeap;
    oDate->year = lYear + 1970;
    ZT_U8 lMonthIndex = 0;
    ZT_TIME lDaysInMonth;
    while (lMonthIndex < 12) {
        lDaysInMonth = rZTM_TIME__DAYSPERMONTH[lMonthIndex];
        if (lLeap == 2 && lMonthIndex == 1) {lDaysInMonth++;}
        lMonthIndex++;
        if (lDaysInMonth > iTime) {break;} else {iTime -= lDaysInMonth;}
    }
    oDate->month = lMonthIndex;
    oDate->day = iTime + 1;
}
void ZTM_DateExtra(ZT_TIME iTime, ZT_DATE_EXTRA* oDate) {
    ZTM_Date((oDate->extra.timestamp = iTime), (ZT_DATE*)oDate);
    ZT_INDEX lIndex = -1;
    oDate->extra.ordinal = oDate->day;
    while (++lIndex < ((ZT_INDEX)oDate->month - 1)) {oDate->extra.ordinal += rZTM_TIME__DAYSPERMONTH[lIndex];}
    if (!(oDate->year & 0x3) && (oDate->month > 2)) {++oDate->extra.ordinal;}
    oDate->extra.weekday = ZTM_TimeWeekday(oDate->extra.timestamp);
    oDate->extra.week = 1 + (oDate->extra.ordinal + ZTM_TimeWeekday(oDate->extra.timestamp - ((oDate->extra.ordinal - 1) * 86400))) / 7;
    oDate->extra.timezone = rZTM_TIME__ZONE;
}
ZT_DATE* ZTM_DateNew(ZT_TIME iTime) {
	ZT_DATE* lDate = ZTM8_New(sizeof(ZT_DATE));
	ZTM_Date(iTime, lDate);
	return lDate;
}
ZT_DATE_EXTRA* ZTM_DateExtraNew(ZT_TIME iTime) {
	ZT_DATE_EXTRA* lDateExtra = ZTM8_New(sizeof(ZT_DATE_EXTRA));
	ZTM_DateExtra(iTime, lDateExtra);
	return lDateExtra;
}
/*
ZT_FLAG ZTM_DateValid(const ZT_DATE* iDate) {
	if (iDate != NULL) {
		return 0x0;
	} else if (iDate->year > 99) {
		return 0x0;
	} else if (!(iDate->month) || (iDate->month > 12) {
		return 0x0;
	} else if (!(iDate->day)) {
		return 0x0;
	} else if ((iDate->month != 2) && (iDate->day > rZTM_TIME__DAYSPERMONTH[iDate->month - 1])) {
		return 0x0;
	} else if ((iDate->year %  4) ? (iDate->day > rZTM_TIME__DAYSPERMONTH[iDate->month - 1]) : (iDate->day > (rZTM_TIME__DAYSPERMONTH[iDate->month - 1] + 1))) {
		return 0x0;
	} else if (iDate->hour > 23) {
		return 0x0;
	} else if (iDate->minute > 59) {
		return 0x0;
	} else if (iDate->second > 59) {
		return 0x0;
	}
	return 0x1;
}
ZT_FLAG ZTM_DateCoerce(ZT_DATE* iDate) {
	if (iDate != NULL) {
		if (ZTM_DateValid) {
			return 0x1;
		} else {
			if (iDate->year > 99) {iDate->year = 99;}
			if (!(iDate->month)) {iDate->month = 1;} else if (iDate->month > 12) {iDate->month = 12;}
			if (!(iDate->day)) {
				iDate->day = 1;
			}  else if ((iDate->month != 2) && (iDate->day > rZTM_TIME__DAYSPERMONTH[iDate->month - 1])) {
				iDate->day = rZTM_TIME__DAYSPERMONTH[iDate->month - 1];
			} else if ((iDate->year %  4) ? (iDate->day > rZTM_TIME__DAYSPERMONTH[iDate->month - 1]) : (iDate->day > (rZTM_TIME__DAYSPERMONTH[iDate->month - 1] + 1))) {
				iDate->day = (iDate->year %  4) ? rZTM_TIME__DAYSPERMONTH[iDate->month - 1] : (rZTM_TIME__DAYSPERMONTH[iDate->month - 1] + 1);
			}
			if (iDate->hour > 23) {iDate->hour = 23}
			if (iDate->minute > 59) {iDate->minute = 59;}
			if (iDate->second > 59) {iDate->second = 59;}
			return 0x0;
		}
	}
	return 0x0;
}
*/

#endif // ZT_TIME_C_INCLUDED
