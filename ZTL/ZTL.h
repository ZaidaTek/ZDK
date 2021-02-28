/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL_H_INCLUDED
#define ZTL_H_INCLUDED

#include "../ZTM/ZTM.h"
#include "ZTL_Define.h"

#define ZTL_Tickout(TIMESTAMP,TIMEOUT) ZTM_Timeout(ZTL_Tick(), TIMESTAMP, TIMEOUT)
#define ZTL_TickoutReset(PTRTIMESTAMP,TIMEOUT) ZTM_TimeoutReset(ZTL_Tick(), PTRTIMESTAMP, TIMEOUT)
#define ZTL_Open(PATH) ZTL_Execute(PATH, ZTL_EXECUTE_OPEN)
#define ZTL_OpenDiscrete(PATH) ZTL_Execute(PATH, ZTL_EXECUTE_OPEN | ZTL_EXECUTE_HIDE)
#define ZTL_Edit(PATH) ZTL_Execute(PATH, ZTL_EXECUTE_EDIT)
#define ZTL_Print(PATH) ZTL_Execute(PATH, ZTL_EXECUTE_PRINT)
#define ZTL_Hyperlink(ADDRESS) ZTL_Execute(ADDRESS, ZTL_EXECUTE_OPEN)
#define ZTL_HyperlinkDiscrete(ADDRESS) ZTL_Execute(ADDRESS, ZTL_EXECUTE_OPEN | ZTL_EXECUTE_HIDE)

typedef void ZT_TIMER;
typedef void ZT_THREAD;
typedef void ZT_SERIAL;
typedef void ZT_LIBRARY;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTL_LibraryFree(ZT_LIBRARY* iLibrary);
ZT_LIBRARY* ZTL_LibraryLoad(const ZT_CHAR* iPath);
void* ZTL_LibraryFunction(ZT_LIBRARY* iLibrary, const ZT_CHAR* iName);

ZT_CHAR* ZTL_SerialAddress(ZT_INDEX iPort);
ZT_INDEX ZTL_SerialPort(const ZT_CHAR* iAddress);
ZT_SERIAL* ZTL_SerialNew(const ZT_CHAR* iAddress, ZT_INDEX iBaud, ZT_SIZE iBufferIn, ZT_SIZE iBufferOut);
void ZTL_SerialFree(ZT_SERIAL* iDevice);
void ZTL_SerialFlush(ZT_SERIAL* iDevice);
ZT_SIZE ZTL_SerialQueue(ZT_SERIAL* iDevice);
ZT_SIZE ZTL_SerialRead(ZT_SERIAL* iDevice, ZT_U8* oBuffer, ZT_SIZE iLength);
ZT_SIZE ZTL_SerialWrite(ZT_SERIAL* iDevice, const ZT_U8* iBuffer, ZT_SIZE iLength);

ZT_THREAD* ZTL_ThreadNew(ZT_FLAG (*iFunction)(void*), void* iArgument);
ZT_FLAG ZTL_ThreadState(ZT_THREAD* iThread, ZT_FLAG* oReturn);
void ZTL_ThreadKill(ZT_THREAD* iThread, ZT_FLAG iReturn);
void ZTL_ThreadFree(ZT_THREAD* iThread);
void ZTL_Sleep(ZT_TIME iLength);
void ZTL_Execute(const ZT_CHAR* iPath, ZT_FLAG iMode);
void ZTL_Clock(ZT_U64* oClock);
ZT_BOOL ZTL_ClockRate(ZT_U64* oRate);
void ZTL_TickResolution(ZT_TIME iResolution);
ZT_TIME ZTL_Tick(void);
ZT_TIME ZTL_TickMicro(void);
ZT_TIMER* ZTL_TimerNew(ZT_INDEX iFrequency);
ZT_BOOL ZTL_Timer(ZT_TIMER* iTimer);
void ZTL_TimerFree(ZT_TIMER* iTimer);
ZT_BOOL ZTL_DirectoryCreate(const ZT_CHAR* iPath);
ZT_FLAG ZTL_FileFlags(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileExists(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsReadOnly(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsHidden(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsSystem(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsDirectory(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsArchive(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsCompressed(const ZT_CHAR* iPath);
ZT_BOOL ZTL_FileIsEncrypted(const ZT_CHAR* iPath);
ZT_I ZTL_ScreenWidth(void);
ZT_I ZTL_ScreenHeight(void);
void ZTL_ScreenSize(ZT_POINT* oSize);
ZT_INDEX ZTL_SelectPoll(ZT_CHAR* oPath);
void ZTL_SelectTitle(const ZT_CHAR* iTitle);
void ZTL_SelectDirectory(const ZT_CHAR* iPath);
void ZTL_SelectFilename(const ZT_CHAR* iName);
void ZTL_SelectFiletype(const ZT_CHAR** iPattern, const ZT_CHAR** iLabel, ZT_INDEX iCount, ZT_INDEX iSelected);
ZT_FLAG ZTL_SelectFileSave(void);
ZT_FLAG ZTL_SelectFileOpen(void);
ZT_FLAG ZTL_SelectFileOpenMulti(void);
void ZTL_SelectThreadedFileSave(void);
void ZTL_SelectThreadedFileOpen(void);
void ZTL_SelectThreadedFileOpenMulti(void);
ZT_FLAG ZTL_SelectThreadedState(void);
ZT_BOOL ZTL_SelectThreadedWait(ZT_FLAG* oResult);
#ifdef __cplusplus
extern "C" }
#endif // __cplusplus

#endif // ZTL_H_INCLUDED
