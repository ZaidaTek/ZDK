/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL__RUNTIME_H_INCLUDED
#define ZTL__RUNTIME_H_INCLUDED

//#include "../ZTM/ZTM__Runtime.h"
#include "ZTL.h"

#define ZTL_FLAG_QPC_INIT 0x1
#define ZTL_FLAG_QPC_SUPPORTED 0x2

#define ZTL_FLAG_SELECT_INIT 0x1
#define ZTL_FLAG_SELECT_SAVE 0x2
#define ZTL_FLAG_SELECT_MULTI 0x4
#define ZTL_BUFFER_PATH 2048 // expose this, and make it OS-dependent?

typedef struct {
    ZT_U64 timestamp;
    ZT_U64 delay;
    ZT_INDEX length;
    ZT_INDEX remainder;
    ZT_INDEX counter;
    ZT_INDEX bump;
} rZT_TIMER;
typedef struct {
    void* runtime;
    ZT_FLAG id;
} rZT_THREAD;

#ifdef ZTM__OS__WINDOWS
#define ZTL__OS__WINDOWS
//#define WINVER 0x0501 // so that AlphaBlend function is included
#include <windows.h>
#include <commdlg.h>
#define ZTL_SERIAL_GRACE 3000
#define ZTL_RuntimeThreadNew(THREAD,FUNCTION,ARGUMENT) ((rZT_THREAD*)(THREAD))->runtime = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(FUNCTION), (ARGUMENT), 0, (LPDWORD)&(((rZT_THREAD*)(THREAD))->id))
#define ZTL_RuntimeThreadWait(THREAD) (WaitForSingleObject(((rZT_THREAD*)(THREAD))->runtime, 0) == WAIT_TIMEOUT)
#define ZTL_RuntimeThreadReturn(THREAD,ORETURN) GetExitCodeThread(((rZT_THREAD*)(THREAD))->runtime, (LPDWORD)(ORETURN))
#define ZTL_RuntimeThreadKill(THREAD,RETURN) TerminateThread(((rZT_THREAD*)(THREAD))->runtime, (RETURN))
#define ZTL_RuntimeThreadFree(THREAD) CloseHandle(((rZT_THREAD*)(THREAD))->runtime)
#define ZTL_RuntimeSleep(LENGTH) Sleep(LENGTH)
#define ZTL_RuntimeTickResolutionStart(RESOLUTION) timeBeginPeriod(RESOLUTION)
#define ZTL_RuntimeTickResolutionStop(RESOLUTION) timeEndPeriod(RESOLUTION)
#define ZTL_RuntimeTick() timeGetTime()
#define ZTL_RuntimeClock(OCLOCK) QueryPerformanceCounter((LARGE_INTEGER*)OCLOCK)
#define ZTL_RuntimeClockRate(ORATE) QueryPerformanceFrequency((LARGE_INTEGER*)ORATE)
#define ZTL_RuntimeScreenWidth() GetSystemMetrics(SM_CXFULLSCREEN)
#define ZTL_RuntimeScreenHeight() GetSystemMetrics(SM_CYFULLSCREEN)
#define ZTL_RuntimeSelectFileOpen() GetOpenFileName(&rZTL__SELECT_RUNTIME)
#define ZTL_RuntimeSelectFileSave() GetSaveFileName(&rZTL__SELECT_RUNTIME)
typedef OPENFILENAME rZT_SELECT;
typedef HANDLE rZT_SERIAL;
#else
#define ZTL__OS__UNKNOWN
#define ZTL_SERIAL_GRACE 0
#define ZTL_RuntimeThreadNew(THREAD,FUNCTION,ARGUMENT)
#define ZTL_RuntimeThreadWait(THREAD) ZT_FALSE
#define ZTL_RuntimeThreadReturn(THREAD,ORETURN) *(ORETURN) = 0x0
#define ZTL_RuntimeThreadKill(THREAD,RETURN)
#define ZTL_RuntimeThreadFree(THREAD)
#define ZTL_RuntimeSleep(LENGTH)
#define ZTL_RuntimeTickResolutionStart(RESOLUTION)
#define ZTL_RuntimeTickResolutionStop(RESOLUTION)
#define ZTL_RuntimeTick() ZTM_Tick()
#define ZTL_RuntimeClock(OCLOCK) (*(OCLOCK) = ZTM_Clock())
#define ZTL_RuntimeClockRate(ORATE) ({*(ORATE) = ZTM_ClockRate(); ZT_FALSE;})
#define ZTL_RuntimeScreenWidth() 0
#define ZTL_RuntimeScreenHeight() 0
#define ZTL_RuntimeSelectFileOpen() ZT_FALSE
#define ZTL_RuntimeSelectFileSave() ZT_FALSE
typedef ZT_FLAG rZT_SELECT;
typedef void rZT_SERIAL;
#endif // ZTM__OS__

void ZTL_SelectSetup(void);
void ZTL_SelectProcess(void);

extern ZT_FLAG             rZTL__QPC_FLAG;
extern ZT_U64              rZTL__QPC_RATE;
extern ZT_TIME             rZTL__TICK_RES;
extern ZT_FLAG             rZTL__SELECT_FLAG;
extern ZT_INDEX            rZTL__SELECT_COUNT;
extern rZT_SELECT          rZTL__SELECT_RUNTIME;
extern rZT_THREAD*         rZTL__SELECT_THREAD;
extern ZT_CHAR             rZTL__SELECT_PATH[ZTL_BUFFER_PATH];
extern ZT_CHAR             rZTL__SELECT_DIR[ZTL_BUFFER_PATH];
extern ZT_CHAR             rZTL__SELECT_FILE[ZTL_BUFFER_PATH];
extern ZT_CHAR             rZTL__SELECT_TYPE[ZTL_BUFFER_PATH];

#endif // ZTL__RUNTIME_H_INCLUDED

