/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL_H_INCLUDED
#define ZTL_H_INCLUDED

#include <ZTM.h>
#include "ZTL__Environment.h"
#include "ZTL_Define.h"
#include "ZTL_Types.h"

#define ZTL_Tickout(TIMESTAMP,TIMEOUT) ZTM_Timeout(ZTL_Tick(), TIMESTAMP, TIMEOUT)
#define ZTL_TickoutReset(PTRTIMESTAMP,TIMEOUT) ZTM_TimeoutReset(ZTL_Tick(), PTRTIMESTAMP, TIMEOUT)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZT_BOOL ZTL_ClockRate(ZT_U64* oRate);
void ZTL_Clock(ZT_U64* oClock);
void ZTL_TickResolution(ZT_TIME iResolution);
ZT_TIME ZTL_Tick(void);
ZT_TIME ZTL_TickMicro(void);
void ZTL_TimerFree(ZT_TIMER* iTimer);
ZT_TIMER* ZTL_TimerNew(ZT_INDEX iFrequency);
ZT_BOOL ZTL_Timer(ZT_TIMER* iTimer);
void ZTL_Sleep(ZT_TIME iLength);
ZT_THREAD* ZTL_ThreadNew(ZT_FLAG (*iFunction)(void*), void* iArgument);
ZT_FLAG ZTL_ThreadState(ZT_THREAD* iThread, ZT_FLAG* oReturn);
void ZTL_ThreadKill(ZT_THREAD* iThread, ZT_FLAG iReturn);
void ZTL_ThreadFree(ZT_THREAD* iThread);

ZT_FLAG ZTL_ShellExec(const ZT_CHAR* iCommand, ...);
ZT_CHAR* ZTL_ShellPipeInTarget(const ZT_CHAR* iCommand, ZT_CHAR* oTarget, ZT_SIZE iCapacity);
#define ZTL_ShellPipeInNew(COMMAND) ZTL_ShellPipeInTarget((COMMAND), NULL, 0)
void ZTL_ShellOpen(const ZT_CHAR* iPath, ZT_FLAG iMode);
#if defined(ZTL__OS__LINUX)
#define ZTL_Open(PATH) ZTL_ShellOpen(PATH, ZTL_EXECUTE_OPEN)
#define ZTL_OpenDiscrete(PATH) ZTL_ShellOpen(PATH, ZTL_EXECUTE_OPEN | ZTL_EXECUTE_HIDE)
#define ZTL_Edit(PATH) ZTL_ShellOpen(PATH, ZTL_EXECUTE_EDIT)
#define ZTL_Print(PATH) ZTL_ShellOpen(PATH, ZTL_EXECUTE_PRINT)
#define ZTL_Hyperlink(ADDRESS) ZTL_ShellOpen(ADDRESS, ZTL_EXECUTE_OPEN)
#define ZTL_HyperlinkDiscrete(ADDRESS) ZTL_Hyperlink(ADDRESS, ZTL_EXECUTE_OPEN | ZTL_EXECUTE_HIDE)
#else
#define ZTL_Open(PATH) ZTL_ShellOpen(PATH, ZTL_EXECUTE_OPEN)
#define ZTL_OpenDiscrete(PATH) ZTL_ShellOpen(PATH, ZTL_EXECUTE_OPEN | ZTL_EXECUTE_HIDE)
#define ZTL_Edit(PATH) ZTL_ShellOpen(PATH, ZTL_EXECUTE_EDIT)
#define ZTL_Print(PATH) ZTL_ShellOpen(PATH, ZTL_EXECUTE_PRINT)
#define ZTL_Hyperlink(ADDRESS) ZTL_ShellOpen(ADDRESS, ZTL_EXECUTE_OPEN)
#define ZTL_HyperlinkDiscrete(ADDRESS) ZTL_ShellOpen(ADDRESS, ZTL_EXECUTE_OPEN | ZTL_EXECUTE_HIDE)
#endif // ZTL__OS__
void ZTL_LibraryFree(ZT_LIBRARY* iLibrary);
ZT_LIBRARY* ZTL_LibraryLoad(const ZT_CHAR* iPath);
void* ZTL_LibraryFunction(ZT_LIBRARY* iLibrary, const ZT_CHAR* iName);

void ZTL_NodeInfoTarget(const ZT_CHAR* iPath, ZT_META_FILE* oTarget);
const ZT_META_FILE* ZTL_NodeInfo(const ZT_CHAR* iPath);
#define ZTL_DirectoryInfo(PATH) ZTL_NodeInfo(PATH)
#define ZTL_DirectoryInfoTarget(PATH,TGT) ZTL_NodeInfoTarget(PATH, TGT)
ZT_BOOL ZTL_DirectoryCreate(const ZT_CHAR* iPath);
#define ZTL_FileInfo(PATH) ZTL_NodeInfo(PATH)
#define ZTL_FileInfoTarget(PATH,TGT) ZTL_NodeInfoTarget(PATH, TGT)
/*
ZT_FLAG ZTL_FileFlags(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileExists(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsReadOnly(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsHidden(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsSystem(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsDirectory(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsArchive(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsCompressed(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsEncrypted(const ZT_CHAR* iPath);
*/
ZT_CHAR* ZTL_SerialAddress(ZT_INDEX iPort);
ZT_INDEX ZTL_SerialPort(const ZT_CHAR* iAddress);
ZT_SERIAL* ZTL_SerialNew(const ZT_CHAR* iAddress, ZT_INDEX iBaud, ZT_SIZE iBufferIn, ZT_SIZE iBufferOut);
void ZTL_SerialFree(ZT_SERIAL* iDevice);
void ZTL_SerialFlush(ZT_SERIAL* iDevice);
ZT_SIZE ZTL_SerialQueue(ZT_SERIAL* iDevice);
ZT_SIZE ZTL_SerialRead(ZT_SERIAL* iDevice, ZT_U8* oBuffer, ZT_SIZE iLength);
ZT_SIZE ZTL_SerialWrite(ZT_SERIAL* iDevice, const ZT_U8* iBuffer, ZT_SIZE iLength);

ZT_I ZTL_ScreenWidth(void);
ZT_I ZTL_ScreenHeight(void);
void ZTL_ScreenSize(ZT_POINT* oSize);

void ZTL_SelectDialogTitle(const ZT_CHAR* iTitle);
void ZTL_SelectDialogDirectory(const ZT_CHAR* iPath);
void ZTL_SelectDialogFilename(const ZT_CHAR* iName);
void ZTL_SelectDialogFiletype(const ZT_CHAR** iPattern, const ZT_CHAR** iLabel, ZT_INDEX iCount, ZT_INDEX iSelected);
ZT_INDEX ZTL_SelectPoll(ZT_CHAR* oPath);
ZT_FLAG ZTL_SelectSave(void);
ZT_FLAG ZTL_SelectOpen(void);
ZT_FLAG ZTL_SelectOpenMulti(void);
void ZTL_SelectThreadedSave(void);
void ZTL_SelectThreadedOpen(void);
void ZTL_SelectThreadedOpenMulti(void);
ZT_FLAG ZTL_SelectThreadedState(ZT_FLAG* oResult);
ZT_BOOL ZTL_SelectThreadedWait(ZT_FLAG* oResult);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTL_H_INCLUDED
