/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32_TIMER_C_INCLUDED
#define ZTW32_TIMER_C_INCLUDED

#include "ZTW32/ZTW32__Runtime.h"

static ZT_INDEX gZTW32_TimerLastResolution = (~0);

#define ZTW32_W32_TimerKill(TIMERID) if (gZTW32_RTime->window.handle != NULL) {KillTimer(gZTW32_RTime->window.handle, (UINT)TIMERID);}
#define ZTW32_W32_TimerSet(TIMERID,DELAY) if (gZTW32_RTime->window.handle != NULL) {SetTimer(gZTW32_RTime->window.handle, (UINT)TIMERID, (UINT)DELAY, NULL);}
// PUBLIC FUNCTIONS
void ZTW32_TimerResolution() {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->window.handle != NULL) {
			if (gZTW32_RTime->owner->system.timer.resolution) {
				ZTW32_TimerResolutionReset();
				gZTW32_TimerLastResolution = gZTW32_RTime->owner->system.timer.resolution;
				timeBeginPeriod(gZTW32_TimerLastResolution);
			}
		}
	}
}
void ZTW32_TimerResolutionReset() {
	if (gZTW32_RTime != NULL) {
		if (gZTW32_RTime->window.handle != NULL) {
			if (gZTW32_TimerLastResolution != (ZT_INDEX)(~0)) {
				timeEndPeriod(gZTW32_TimerLastResolution);
			}
		}
	}
}
void ZTW32_TimerHeartbeatStop(void) {
	if (gZTW32_RTime != NULL) {
        ZTW32_W32_TimerKill(ZTK_SID_TIMER_HEARTBEAT);
	}
}
void ZTW32_TimerHeartbeat(void) {
	if (gZTW32_RTime != NULL) {
        if (gZTW32_RTime->owner->system.timer.heartbeat) {
            ZTW32_W32_TimerSet(ZTK_SID_TIMER_HEARTBEAT, gZTW32_RTime->owner->system.timer.heartbeat);
        }
    }
}
void ZTW32_TimerWakeStop(void) {
	if (gZTW32_RTime != NULL) {
        ZTW32_W32_TimerKill(ZTK_SID_TIMER_WAKE);
	}
}
void ZTW32_TimerWake(ZT_TIME iDelay) {
	if (gZTW32_RTime != NULL) {
        ZTW32_W32_TimerSet(ZTK_SID_TIMER_WAKE, iDelay);
	}
}
void ZTW32_TimerFree(void) {
	if (gZTW32_RTime != NULL) {
        ZTW32_W32_TimerKill(ZTK_SID_TIMER_WAKE);
        ZTW32_W32_TimerKill(ZTK_SID_TIMER_HEARTBEAT);
	}
}

#endif // ZTW32_TIMER_C_INCLUDED
