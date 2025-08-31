/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL__RUNTIME_H_INCLUDED
#define ZTL__RUNTIME_H_INCLUDED

#include <ZTM__Runtime.h>
#include "ZTL.h"

#define ZTL_FLAG_QPC_INIT 0x1
#define ZTL_FLAG_QPC_SUPPORTED 0x2

#define ZTL_FLAG_SELECT_INIT 0x1
#define ZTL_FLAG_SELECT_SAVE 0x2
#define ZTL_FLAG_SELECT_MULTI 0x4

#define ZTL_BUFFER_PATH 8192 // expose this, and make it OS-dependent?
#define ZTL_BUFFER_PIPE 1024 // expose this, and make it OS-dependent?

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
    void* mutex;
    ZT_FLAG(* exec)(void*);
    void* args;
    union {ZT_FLAG id; ZT_FLAG state;};
    ZT_FLAG ret;
} rZT_THREAD;

#if defined(ZTL__OS__WINDOWS)
#include <windows.h>
#include <commdlg.h>
#define ZTL_SERIAL_GRACE 3000
typedef HANDLE rZT_SERIAL;
typedef OPENFILENAME rZT_SELECT;
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
#define ZTL_RuntimeShellExec(COMMAND) ZTL_ShellOpen(COMMAND, ZTL_EXECUTE_OPEN)
#define ZTL_RuntimeScreenWidth() GetSystemMetrics(SM_CXFULLSCREEN)
#define ZTL_RuntimeScreenHeight() GetSystemMetrics(SM_CYFULLSCREEN)
#define ZTL_RuntimeSelectInit(RUNTIME)\
    ZTM8_Zero((RUNTIME), sizeof(rZT_SELECT));\
    (RUNTIME)->lStructSize = sizeof(rZT_SELECT);\
    (RUNTIME)->lpstrFilter = (LPCTSTR)rZTL__SELECT_TYPE;\
    (RUNTIME)->nFilterIndex = 1;\
    (RUNTIME)->lpstrFile = (LPTSTR)rZTL__SELECT_PATH;\
    (RUNTIME)->nMaxFile = ZTL_BUFFER_PATH;\
    (RUNTIME)->lpstrInitialDir = (LPCTSTR)rZTL__SELECT_DIR;\
    (RUNTIME)->Flags = OFN_EXPLORER
//#define ZTL_RuntimeSelectDialog() ({rZTL__SELECT_FLAG & ZTL_FLAG_SELECT_SAVE ? GetSaveFileName(rZTL__SELECT_RUNTIME) : GetOpenFileName(rZTL__SELECT_RUNTIME);})
#elif defined(ZTL__OS__LINUX)
#define _GNU_SOURCE
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#include <asm/termbits.h>
#define ZTL_SERIAL_GRACE 3000
typedef int rZT_SERIAL;
typedef struct {const ZT_CHAR* title;} rZT_SELECT;
#define ZTL_RuntimeThreadNew(THREAD,FUNCTION,ARGUMENT) \
    static pthread_attr_t lAttr;\
    void* lEntryPoint(void* iiThread) {\
        rZT_THREAD* llThread = iiThread;\
        pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);/*TODO FIXME PTHREAD_CANCEL_DEFERRED << shouldn't this be immediate again?*/\
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);\
        llThread->ret = (*(llThread->exec))(llThread->args);\
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);\
        pthread_mutex_lock(llThread->mutex);\
        llThread->state = ZTL_THREAD_FINISH;\
        pthread_mutex_unlock(llThread->mutex);\
        return NULL;\
    }\
    ((rZT_THREAD*)(THREAD))->state = ZTL_THREAD_RUNNING;\
    ((rZT_THREAD*)(THREAD))->mutex = ZTM8_New(sizeof(pthread_mutex_t));\
    pthread_mutex_init(((rZT_THREAD*)(THREAD))->mutex, NULL);\
    pthread_attr_init(&lAttr);\
    pthread_attr_setdetachstate(&lAttr, PTHREAD_CREATE_DETACHED);\
    pthread_create((pthread_t*)&(((rZT_THREAD*)(THREAD))->runtime), &lAttr, &lEntryPoint, (THREAD));
#define ZTL_RuntimeThreadWait(THREAD) ({\
    ZT_BOOL mWait = ZT_TRUE;\
    rZT_THREAD* mThread = (THREAD);\
    if (!pthread_mutex_trylock(mThread->mutex)) {mWait = mThread->state != ZTL_THREAD_FINISH; pthread_mutex_unlock(mThread->mutex);}\
    mWait;\
})
#define ZTL_RuntimeThreadReturn(THREAD,ORETURN) *(ORETURN) = ((rZT_THREAD*)(THREAD))->ret
#define ZTL_RuntimeThreadKill(THREAD,RETURN) pthread_cancel((pthread_t)((rZT_THREAD*)(THREAD))->runtime); ((rZT_THREAD*)(THREAD))->ret = (RETURN)
#define ZTL_RuntimeThreadFree(THREAD) ZTM8_Free(((rZT_THREAD*)(THREAD))->mutex)
#define ZTL_RuntimeSleep(LENGTH) \
    static struct timespec lCache;\
    static struct timespec lDummy;\
    lCache.tv_sec = LENGTH / 1000;\
    lCache.tv_nsec = (LENGTH % 1000) * 1000000;\
    nanosleep(&lCache, &lDummy)
#define ZTL_RuntimeTickResolutionStart(RESOLUTION) // NOT NEEDED IN POSIX; DO NOTHING
#define ZTL_RuntimeTickResolutionStop(RESOLUTION) // NOT NEEDED IN POSIX; DO NOTHING
#define ZTL_RuntimeTick() ({\
    static struct timespec mCACHE;\
    clock_gettime(CLOCK_REALTIME, &mCACHE);\
    ((ZT_U64)mCACHE.tv_sec * (ZT_U64)1000 + (ZT_U64)mCACHE.tv_nsec / (ZT_U64)1000000) & 0xffffffff;\
})
#define ZTL_RuntimeTickMicro() ({\
    static struct timespec mCACHE;\
    clock_gettime(CLOCK_REALTIME, &mCACHE);\
    ((ZT_U64)mCACHE.tv_sec * (ZT_U64)1000000 + (ZT_U64)mCACHE.tv_nsec / (ZT_U64)1000) & 0xffffffff;\
})
#define ZTL_RuntimeClock(OCLOCK) ({\
    static struct timespec mCACHE;\
    clock_gettime(CLOCK_REALTIME, &mCACHE);\
    *(OCLOCK) = (ZT_U64)mCACHE.tv_sec * (ZT_U64)1000000000 + (ZT_U64)mCACHE.tv_nsec;\
})
#define ZTL_RuntimeClockRate(ORATE) ({\
    static struct timespec mZTL_RUNTIMECLOCKRATE;\
    clock_getres(CLOCK_REALTIME, &mZTL_RUNTIMECLOCKRATE);\
    *(ORATE) = (ZT_U64)1000000000 / ((ZT_U64)mZTL_RUNTIMECLOCKRATE.tv_sec * (ZT_U64)1000000000 + (ZT_U64)mZTL_RUNTIMECLOCKRATE.tv_nsec);\
    ZT_TRUE;\
})
#define ZTL_RuntimeShellExec(COMMAND) ((ZT_FLAG)system((const char*)(COMMAND)))
#define ZTL_RuntimeScreenWidth() 0
#define ZTL_RuntimeScreenHeight() 0
#define ZTL_RuntimeSelectInit(RUNTIME) ZTM8_Zero((RUNTIME), sizeof(rZT_SELECT))
#else
#define ZTL_SERIAL_GRACE 0
typedef ZT_FLAG rZT_SELECT;
typedef void rZT_SERIAL;
// TODO ADD BACK UNKNOWN DEFAULTS!
#define ZTL_RuntimeScreenWidth() 0
#define ZTL_RuntimeScreenHeight() 0
#define ZTL_RuntimeSelectFileOpen() ZT_FALSE
#define ZTL_RuntimeSelectFileSave() ZT_FALSE
#endif // ZTM__OS__

void ZTL_SelectInit(void);
ZT_INDEX ZTL_RuntimeSelectDialog(void);

extern ZT_U64              rZTL__QPC_RATE;
extern ZT_FLAG             rZTL__QPC_FLAG;
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

