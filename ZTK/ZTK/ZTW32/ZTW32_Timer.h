/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32_TIMER_H_INCLUDED
#define ZTW32_TIMER_H_INCLUDED

#include "ZTW32.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTW32_TimerResolution(void);
void ZTW32_TimerResolutionReset(void);
void ZTW32_TimerFree(void);
void ZTW32_TimerHeartbeatStop(void);
void ZTW32_TimerHeartbeat(void);
void ZTW32_TimerWakeStop(void);
void ZTW32_TimerWake(ZT_TIME iDelay);
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ZTW32_TIMER_H_INCLUDED
