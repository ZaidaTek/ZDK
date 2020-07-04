/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_TIME_C_INCLUDED
#define ZT_TIME_C_INCLUDED

#include "ZTM__Runtime.h"
#include ZTM__INCL__TIME

ZT_TIME ZTM_TimeGet(const ZT_DATE* iDate) {
    ZT_TIME lTime = 0;
	if (iDate == NULL && rZTM_TIME__ZONE_INIT) {
	    lTime = time(NULL) + rZTM_TIME__ZONE;
	} else if (iDate != NULL) {
		// year > 1969 : assume YYYY-input, else assume YY-input
		ZT_TIME lYear = (iDate->year > 1969) ? (iDate->year - 1970) : ((iDate->year < 70) ? (iDate->year + 30) : (iDate->year - 70));
		ZT_TIME lLeap = (lYear / 4); // calculate leap years since 1970 ('72 was leap)
		switch(lYear % 4) { // do the remaining years contain a leap year?
			default: case 0: case 1: break;
			case 2: if (iDate->month > 2) {++lLeap;} break; // is it before or after feb 29?
			case 3: ++lLeap; break;
		}
		lTime = -1; // start with -1, to offset that day is human friendly starting with 1
		for (ZT_INDEX i = 1; i < iDate->month; i++) {lTime += rZTM_TIME__DAYSPERMONTH[i - 1];} // lTime now contains days of ***preceding*** months of current year
		lTime += iDate->day; // add current day to day-count
		lTime += lLeap; // add leap days
		lTime += (lYear * 365); // add days of preceding years, cast as unsigned long to prevent wraparound
		lTime *= 24; // *24 for hours til now
		lTime += iDate->hour;
		lTime *= 60; // *60 for minutes til now
		lTime += iDate->minute ;
		lTime *= 60; // *60 for seconds til now
		lTime += iDate->second;
	} else {
		time_t lNow = time(NULL);
		struct tm* lDate = gmtime(&lNow);
		lDate->tm_isdst = -1;
		time_t lNowLocal = mktime(lDate);
		rZTM_TIME__ZONE = ((time_t)(lNow - lNowLocal));
		rZTM_TIME__ZONE_INIT |= 0x1;
		lTime = lNowLocal;
	}
	return lTime;
}
ZT_DATE* ZTM_DateGet(ZT_TIME iTime) {return ZTM_DateRead(iTime, ZTM8_New(sizeof(ZT_DATE)));}
ZT_DATE* ZTM_DateRead(ZT_TIME iTime, ZT_DATE* oDate) {
	if (oDate != NULL) {
		ZT_TIME lUnixtime = iTime;
		oDate->second = lUnixtime % 60;
		lUnixtime /= 60;
		oDate->minute = lUnixtime % 60;
		lUnixtime /= 60;
		oDate->hour = lUnixtime % 24;
		lUnixtime /= 24;
		ZT_U8 lYear = lUnixtime / (4 * 365 + 1);
		lYear *= 4;
		lUnixtime %= (4 * 365 + 1);
		ZT_U8 lLeap = 0;
		while (lUnixtime >= 365) {
			if (lLeap == 2) {if (lUnixtime > 365) {lUnixtime--;} else {break;}}
			lLeap++;
			lUnixtime -= 365;
		}
		lYear += lLeap;
		oDate->year = lYear + 1970;
		ZT_U8 lMonthIndex = 0;
		while (lMonthIndex < 12) {
			ZT_U8 lDaysInMonth = rZTM_TIME__DAYSPERMONTH[lMonthIndex];
			if (lLeap == 2 && lMonthIndex == 1) {lDaysInMonth++;}
			lMonthIndex++;
			if (lDaysInMonth > lUnixtime) {break;} else {lUnixtime -= lDaysInMonth;}
		}
		oDate->month = lMonthIndex;
		oDate->day = lUnixtime + 1;
	}
	return oDate;
}
ZT_INDEX ZTM_WeekDay(ZT_INDEX iTime) {
	return (((iTime / 86400) + 4) % 7);
}
ZT_DATE_EXTRA* ZTM_DateExtraGet(ZT_TIME iTime) {return ZTM_DateExtraRead(ZTM8_New(sizeof(ZT_DATE_EXTRA)), iTime);}
ZT_DATE_EXTRA* ZTM_DateExtraRead(ZT_DATE_EXTRA* oDate, ZT_TIME iTime) {
	if (oDate != NULL) {
		ZTM_DateRead((oDate->extra.timestamp = iTime), (ZT_DATE*)oDate);
		ZT_INDEX lIndex = -1;
		oDate->extra.ordinal = oDate->day;
		while (++lIndex < ((ZT_INDEX)oDate->month - 1)) {oDate->extra.ordinal += rZTM_TIME__DAYSPERMONTH[lIndex];}
		if (!(oDate->year % 4) && (oDate->month > 2)) {++oDate->extra.ordinal;}
		oDate->extra.weekday = ZTM_WeekDay(oDate->extra.timestamp);
		oDate->extra.week = 1 + (oDate->extra.ordinal + ZTM_WeekDay(oDate->extra.timestamp - ((oDate->extra.ordinal - 1) * 86400))) / 7;
		oDate->extra.timezone = rZTM_TIME__ZONE;
	}
	return oDate;
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
