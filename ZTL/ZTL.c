/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL_C_INCLUDED
#define ZTL_C_INCLUDED

#include "ZTL-RT.h"

#ifdef ZTL_BUILD_UNKNOWN
/*
ZT_FLAG ZTL_FileFlags(const ZT_CHAR* iPath) {return ZTL_FILE_NONE;}
ZT_BOOL ZTL_FileExists(const ZT_CHAR* iPath) {return ZT_FALSE;}
ZT_BOOL ZTL_FileIsReadOnly(const ZT_CHAR* iPath) {return ZT_FALSE;}
ZT_BOOL ZTL_FileIsHidden(const ZT_CHAR* iPath) {return ZT_FALSE;}
ZT_BOOL ZTL_FileIsSystem(const ZT_CHAR* iPath) {return ZT_FALSE;}
ZT_BOOL ZTL_FileIsDirectory(const ZT_CHAR* iPath) {return ZT_FALSE;}
ZT_BOOL ZTL_FileIsArchive(const ZT_CHAR* iPath) {return ZT_FALSE;}
ZT_BOOL ZTL_FileIsCompressed(const ZT_CHAR* iPath) {return ZT_FALSE;}
ZT_BOOL ZTL_FileIsEncrypted(const ZT_CHAR* iPath) {return ZT_FALSE;}
ZT_BOOL ZTL_DirectoryCreate(const ZT_CHAR* iPath) {return ZT_FALSE;}
*/
#endif // ZTL_BUILD_UNKNOWN
ZT_THREAD* ZTL_ThreadNew(ZT_FLAG (*iFunction)(void*), void* iArgument) {
    rZT_THREAD* lThread = ZTM8_New(sizeof(rZT_THREAD));
    lThread->exec = iFunction;
    lThread->args = iArgument;
    ZTL_RuntimeThreadNew(lThread, iFunction, iArgument);
    return lThread;
}
ZT_FLAG ZTL_ThreadState(ZT_THREAD* iThread, ZT_FLAG* oReturn) {
    if (ZTL_RuntimeThreadWait(iThread)) {
        return ZTL_THREAD_RUNNING;
    } else {
        if (oReturn != NULL) {ZTL_RuntimeThreadReturn(iThread, oReturn);}
        return ZTL_THREAD_FINISH;
    }
}
void ZTL_ThreadKill(ZT_THREAD* iThread, ZT_FLAG iReturn) {ZTL_RuntimeThreadKill(iThread, iReturn);}
void ZTL_ThreadFree(ZT_THREAD* iThread) {ZTL_RuntimeThreadFree(iThread); ZTM8_Free(iThread);}
void ZTL_Sleep(ZT_TIME iLength) {if (iLength) {ZTL_RuntimeSleep(iLength);}}
void ZTL_ClockInit(void) {
    if (ZTL_RuntimeClockRate(&rZTL__QPC_RATE)) {rZTL__QPC_FLAG |= ZTL_FLAG_QPC_SUPPORTED;};
    rZTL__QPC_FLAG &= ~ZTL_FLAG_QPC_INIT;
}
void ZTL_Clock(ZT_U64* oClock) {ZTL_RuntimeClock(oClock);}
ZT_BOOL ZTL_ClockRate(ZT_U64* oRate) {return ZTL_RuntimeClockRate(oRate);}
void ZTL_TickResolution(ZT_TIME iResolution) {
    if (rZTL__TICK_RES) {ZTL_RuntimeTickResolutionStop(rZTL__TICK_RES);}
    if ((rZTL__TICK_RES = iResolution)) {ZTL_RuntimeTickResolutionStart(rZTL__TICK_RES);}
}
ZT_TIME ZTL_Tick(void) {return ZTL_RuntimeTick();}
#ifdef ZTL_RuntimeTickMicro
ZT_TIME ZTL_TickMicro(void) {return ZTL_RuntimeTickMicro();}
#else
ZT_TIME ZTL_TickMicro(void) {
    if (rZTL__QPC_FLAG & ZTL_FLAG_QPC_INIT) {ZTL_ClockInit();}
    ZT_U64 lPC;
    ZTL_RuntimeClock(&lPC);
    return ((ZT_U64)1000000 * lPC / rZTL__QPC_RATE);
}
#endif // ZTL_RuntimeTickMicro
void ZTL_TimerFree(ZT_TIMER* iTimer) {ZTM8_Free(iTimer);}
ZT_TIMER* ZTL_TimerNew(ZT_INDEX iFrequency) {
    if (rZTL__QPC_FLAG & ZTL_FLAG_QPC_INIT) {ZTL_ClockInit();}
    rZT_TIMER* lTimer = NULL;
    if (iFrequency && ((lTimer = ZTM8_New(sizeof(rZT_TIMER))) != NULL)) {
        if ((lTimer->remainder = rZTL__QPC_RATE % (ZT_U64)(lTimer->length = iFrequency))) {
            lTimer->delay = rZTL__QPC_RATE / (ZT_U64)iFrequency + 1;
            lTimer->bump = 1;
        } else {
            lTimer->delay = rZTL__QPC_RATE / (ZT_U64)iFrequency;
            lTimer->bump = 0;
        }
        lTimer->timestamp = 0;
        lTimer->counter = 0;
        return lTimer;
    }
    return lTimer;
}
ZT_BOOL ZTL_Timer(ZT_TIMER* iTimer) {
    rZT_TIMER* lTimer = iTimer;
    ZT_U64 lDelta;
    ZT_U64 lNow;
    ZTL_RuntimeClock(&lNow);
    ZT_FLAG lSynchronize = 0x0;
    ZT_BOOL lTimedOut = ZT_FALSE;
    do {
        if (rZTL__QPC_FLAG & ZTL_FLAG_QPC_SUPPORTED) {lDelta = lNow - lTimer->timestamp;} else {lDelta = (lNow - lTimer->timestamp) & ((ZT_TIME)-1);}
        if ((lSynchronize = !(lDelta < lTimer->delay))) {
            lTimer->timestamp = lNow - ((lNow - lTimer->timestamp) % lTimer->delay);
            lTimer->counter = (lTimer->counter + 1) % lTimer->length;
            if (lTimer->remainder && (lTimer->counter == lTimer->bump * lTimer->length / lTimer->remainder)) {
                lTimer->bump = (lTimer->bump + 1) % lTimer->remainder;
                lTimer->delay = rZTL__QPC_RATE / (ZT_U64)lTimer->length + 1;
            } else {
                lTimer->delay = rZTL__QPC_RATE / (ZT_U64)lTimer->length;
            }
            lTimedOut |= ZT_TRUE;
        }
    } while (lSynchronize);
    return lTimedOut;
}
ZT_FLAG ZTL_ShellExec(const ZT_CHAR* iCommand, ...) {
    #define lBUFFERSIZE ((ZT_SIZE)(ZTL_BUFFER_PATH << 1))
    static ZT_CHAR lBuffer[lBUFFERSIZE];
    va_list lList;
    va_start(lList, iCommand);
    ZT_SIZE lLength = ZTC8_RuntimeFormat(lBuffer, lBUFFERSIZE, iCommand, &lList);
    va_end(lList);
    return lLength < lBUFFERSIZE ? ZTL_RuntimeShellExec(lBuffer) : (ZT_FLAG)-1;
    #undef lBUFFERSIZE
}
const ZT_META_FILE* ZTL_NodeInfo(const ZT_CHAR* iPath) {
    static ZT_META_FILE lBuffer;
    if (iPath != NULL) {ZTL_NodeInfoTarget(iPath, &lBuffer);}
    return &lBuffer;
}
ZT_I ZTL_ScreenWidth(void) {return ZTL_RuntimeScreenWidth();}
ZT_I ZTL_ScreenHeight(void) {return ZTL_RuntimeScreenHeight();}
void ZTL_ScreenSize(ZT_POINT* oSize) {ZTM_Point(oSize, ZTL_RuntimeScreenWidth(), ZTL_RuntimeScreenHeight());}

void ZTL_SelectDialogDirectory(const ZT_CHAR* iPath) {if (iPath != NULL) {ZTC8_CopyTargetLength(iPath, rZTL__SELECT_DIR, ZTL_BUFFER_PATH);} else {rZTL__SELECT_DIR[0] = 0x0;}}
void ZTL_SelectDialogFilename(const ZT_CHAR* iName) {if (iName != NULL) {ZTC8_CopyTargetLength(iName, rZTL__SELECT_FILE, ZTL_BUFFER_PATH);} else {rZTL__SELECT_FILE[0] = 0x0;}}
ZT_INDEX ZTL_SelectPoll(ZT_CHAR* oPath) {
    static ZT_INDEX lCount = 0;
    static ZT_INDEX lLengthPath = 0;
    static ZT_INDEX i = 0;
    if (lCount) {--lCount;} else if ((lCount = rZTL__SELECT_COUNT)) {
        lLengthPath = ZTC8_GetLength(rZTL__SELECT_DIR);
        i = 0;
    }
    if (lCount) {
        ZTC8_CopyTarget(rZTL__SELECT_DIR, oPath);
        ZTC8_CopyTarget(&rZTL__SELECT_FILE[i], &oPath[lLengthPath]);
        i += ZTC8_GetLength(&rZTL__SELECT_FILE[i]) + 1;
    }
    return lCount;
}
void ZTL_SelectInit(void) {
    if (rZTL__SELECT_FLAG & ZTL_FLAG_SELECT_INIT) {
        rZTL__SELECT_FLAG &= ~ZTL_FLAG_SELECT_INIT;
        ZTL_RuntimeSelectInit(&rZTL__SELECT_RUNTIME);
    }
}
#define ZTL_SelectDialog() ({ZTL_RuntimeSelectDialog() ? ZTL_SELECT_READY : ZTL_SELECT_CANCEL;})
ZT_FLAG ZTL_SelectThreadedEntry(void* iArgs) {(void)iArgs; return ZTL_SelectDialog();}
ZT_FLAG ZTL_SelectThreadedState(ZT_FLAG* oResult) {
    ZT_FLAG lReturn;
    if (ZTL_ThreadState(rZTL__SELECT_THREAD, oResult != NULL ? oResult : &lReturn) == ZTL_THREAD_FINISH) {
        ZTM_DoNull(ZTL_ThreadFree, rZTL__SELECT_THREAD);
        return oResult != NULL ? *oResult : lReturn;
    } else {
        return ZTL_SELECT_WAIT;
    }
}
ZT_BOOL ZTL_SelectThreadedWait(ZT_FLAG* oResult) {
    ZT_FLAG lState;
    if ((lState = ZTL_SelectThreadedState(NULL)) == ZTL_SELECT_WAIT) {
        return ZT_TRUE;
    } else {
        if (oResult != NULL) {*oResult = lState;}
        return ZT_FALSE;
    }
}
#define ZTL_SelectModeSave() ({rZTL__SELECT_FLAG &= ~ZTL_FLAG_SELECT_MULTI; rZTL__SELECT_FLAG |= ZTL_FLAG_SELECT_SAVE;})
#define ZTL_SelectModeOpen() ({rZTL__SELECT_FLAG &= ~ZTL_FLAG_SELECT_SAVE; rZTL__SELECT_FLAG &= ~ZTL_FLAG_SELECT_MULTI;})
#define ZTL_SelectModeOpenMulti() ({rZTL__SELECT_FLAG &= ~ZTL_FLAG_SELECT_SAVE; rZTL__SELECT_FLAG |= ZTL_FLAG_SELECT_MULTI;})
ZT_FLAG ZTL_SelectSave(void) {ZTL_SelectModeSave(); return ZTL_SelectDialog();}
ZT_FLAG ZTL_SelectOpen(void) {ZTL_SelectModeOpen(); return ZTL_SelectDialog();}
ZT_FLAG ZTL_SelectOpenMulti(void) {ZTL_SelectModeOpenMulti(); return ZTL_SelectDialog();}
void ZTL_SelectThreadedSave(void) {ZTL_SelectModeSave(); rZTL__SELECT_THREAD = ZTL_ThreadNew(&ZTL_SelectThreadedEntry, NULL);}
void ZTL_SelectThreadedOpen(void) {ZTL_SelectModeOpen(); rZTL__SELECT_THREAD = ZTL_ThreadNew(&ZTL_SelectThreadedEntry, NULL);}
void ZTL_SelectThreadedOpenMulti(void) {ZTL_SelectModeOpenMulti(); rZTL__SELECT_THREAD = ZTL_ThreadNew(&ZTL_SelectThreadedEntry, NULL);}
#endif // ZTL_C_INCLUDED
