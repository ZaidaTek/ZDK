/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTMIO_H_INCLUDED
#define ZTMIO_H_INCLUDED

#include "../ZTM.h"

//#define ZIO_APPEND_EOF
//#define ZIO_KEEP_ALIVE
//#define ZIO_EOF ZTM_CHAR_NT
#define ZIO_MODE_READ 0x0
#define ZIO_MODE_APPEND 0x1
#define ZIO_MODE_WRITE 0x2
#define ZIO_MODE_CHANGE (ZIO_MODE_APPEND | ZIO_MODE_WRITE)

typedef struct {
	ZT_DATA_U8 data;
	void* handle;
	ZT_CHAR* path;
    ZT_FLAG flag;
    ZT_FLAG mode;
} ZIO_FILE;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZIO_Free(ZIO_FILE* iFile);
ZIO_FILE* ZIO_New(const ZT_CHAR* iPath);
ZT_SIZE ZIO_Scan(ZIO_FILE* iFile);
ZT_SIZE ZIO_Load(ZIO_FILE* iFile);
ZT_SIZE ZIO_Save(ZIO_FILE* iFile);

void ZIO_Set(ZIO_FILE* iFile, ZT_U8* iData, ZT_SIZE iLength);
void ZIO_Append(ZIO_FILE* iFile, ZT_U8* iData, ZT_SIZE iLength);
#define ZIO_PScan(PATH) ZIO_PipedScan(PATH)
#define ZIO_PRead(PATH,DEST,LENGTH) ZIO_PipedRead(PATH,DEST,LENGTH)
#define ZIO_PWrite(PATH,SOURCE,LENGTH) ZIO_PipedWrite(PATH,SOURCE,LENGTH)
#define ZIO_PAppend(PATH,SOURCE,LENGTH) ZIO_PipedAppend(PATH,SOURCE,LENGTH)
ZT_SIZE ZIO_PipedScan(const ZT_CHAR* iPath);
ZT_SIZE ZIO_PipedRead(const ZT_CHAR* iPath, void* oDestination, ZT_SIZE* oLength);
ZT_SIZE ZIO_PipedWrite(const ZT_CHAR* iPath, const void* iSource, ZT_SIZE iLength);
ZT_SIZE ZIO_PipedAppend(const ZT_CHAR* iPath, const void* iSource, ZT_SIZE iLength);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ZTMIO_H_INCLUDED
