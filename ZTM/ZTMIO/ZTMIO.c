/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTMIO_C_INCLUDED
#define ZTMIO_C_INCLUDED

#include "ZTMIO.h"
#include <stdio.h>
/*
#ifdef ZIO_APPEND_EOF
ZT_FLAG rAppendEOF = 0x1;
ZT_CHAR rEOF = ZIO_EOF;
#else
ZT_FLAG rAppendEOF = 0x0;
#endif // ZIO_APPEND_EOF
#ifdef ZIO_KEEP_ALIVE
ZT_FLAG rCloseHandle = 0x0;
#else
ZT_FLAG rCloseHandle = 0x1;
#endif // ZIO_KEEP_ALIVE
*/
#define ZIO_Open(HANDLE,PATH,MODE) (((HANDLE) = fopen((const char*)(PATH), (MODE))) != NULL)
//#define ZIO_Size(HANDLE) ({fseek((FILE*)(HANDLE) , 0 , SEEK_END); ftell((FILE*)(HANDLE));})
ZT_SIZE ZIO_PipedScan(const ZT_CHAR* iPath) {
	ZT_SIZE lSize = 0;
    FILE* lFile;
    if (ZIO_Open(lFile, iPath, "rb")) {
        fseek(lFile, 0, SEEK_END);
        lSize = ftell(lFile);
        fclose(lFile);
    }
	return lSize;
}
ZT_SIZE ZIO_PipedRead(const ZT_CHAR* iPath, ZT_U8* oDestination, ZT_SIZE iLength, ZT_SIZE iOffset) {
	ZT_SIZE lRead = 0;
    FILE* lFile;
    if (ZIO_Open(lFile, iPath, "rb")) {
        fseek(lFile, iOffset, SEEK_SET);
        lRead = fread(oDestination, 1, iLength, lFile);
        fclose(lFile);
    }
	return lRead;
}
ZT_SIZE ZIO_PipedWrite(const ZT_CHAR* iPath, const ZT_U8* iSource, ZT_SIZE iLength, ZT_SIZE iOffset) {
	ZT_SIZE lWrite = 0;
    FILE* lFile;
    if (ZIO_Open(lFile, iPath, "wb")) {
        fseek(lFile, iOffset, SEEK_SET);
        lWrite = fwrite(iSource, 1, iLength, lFile);
        fclose(lFile);
    }
	return lWrite;
}
ZT_SIZE ZIO_PipedAppend(const ZT_CHAR* iPath, const ZT_U8* iSource, ZT_SIZE iLength) {
	ZT_SIZE lAppend = 0;
    FILE* lFile;
    if (ZIO_Open(lFile, iPath, "ab")) {
        lAppend = fwrite(iSource, 1, iLength, lFile);
        fclose(lFile);
    }
	return lAppend;
}
/*
#define ZIO_HandleClose(ZIOFILE) if ((ZIOFILE)->handle != NULL) {fclose((FILE*)(ZIOFILE)->handle); (ZIOFILE)->handle = NULL;}
#define ZIO_BufferFree(ZIOFILE) ZTM8_Free((ZIOFILE)->data.byte); (ZIOFILE)->data.byte = NULL
#define ZIO_PathFree(ZIOFILE) ZTM8_Free((ZIOFILE)->path)
void ZIO_Free(ZIO_FILE* iFile) {
    ZIO_HandleClose(iFile);
    ZIO_BufferFree(iFile);
    ZIO_PathFree(iFile);
    ZTM8_Free(iFile);
}
void ZIO_Path(ZIO_FILE* iFile, const ZT_CHAR* iPath) {
    ZIO_PathFree(iFile);
    iFile->path = ZTC8_Copy(iPath);
}
ZT_BOOL ZIO_HandleOpen(ZIO_FILE* iFile, ZT_FLAG iMode) {
    if (iFile->handle != NULL) {ZIO_HandleClose(iFile);}
    const char* lMode;
    if (iMode & ZIO_MODE_WRITE) {
        lMode = "wb";
        iFile->mode = ZIO_MODE_WRITE;
    } else if (iMode & ZIO_MODE_APPEND) {
        lMode = "ab";
        iFile->mode = ZIO_MODE_APPEND;
    } else {
        lMode = "rb";
        iFile->mode = ZIO_MODE_READ;
    }
    return (((iFile->handle = fopen((const char*)iFile->path, lMode)) != NULL) ? ZT_TRUE : ZT_FALSE);
}
void ZIO_Terminate(ZIO_FILE* iFile) {
    if (iFile->data.byte != NULL) {
        #ifdef ZIO_APPEND_EOF
        iFile->data.byte[iFile->data.length] = rEOF; // shouldn't this be length - 1?
        #endif // ZIO_APPEND_EOF
    }
}
void ZIO_BufferCreate(ZIO_FILE* iFile) {
    if (iFile->data.length) {
        ZIO_BufferFree(iFile);
         // sometime between 20200221 and 20200307 this went from 1:0 to 2:1 because in Linux it otherwise kept crashing
        iFile->data.byte = ZTM8_New(iFile->data.length + ((rAppendEOF) ? 2 : 1));
        if (rAppendEOF) {ZIO_Terminate(iFile);}
    }
}
ZIO_FILE* ZIO_New(const ZT_CHAR* iPath) {
    ZIO_FILE* lFile = ZTM8_New(sizeof(ZIO_FILE));
    lFile->handle = NULL;
    lFile->path = ZTC8_Copy(iPath);
    lFile->data.ptr = NULL;
    lFile->data.length = 0;
    lFile->flag = 0x0;
    lFile->mode = 0x0;
    return lFile;
}
ZT_SIZE ZIO_Scan(ZIO_FILE* iFile) {
    ZT_SIZE lLength = 0;
    if (ZIO_HandleOpen(iFile, ZIO_MODE_READ)) {
        lLength = ZIO_Size(iFile->handle);
        if (iFile->data.length != lLength) {
            ZIO_BufferFree(iFile);
            iFile->data.length = lLength;
        }
        if (rCloseHandle) {ZIO_HandleClose(iFile);}
    }
	return lLength;
}
ZT_SIZE ZIO_Load(ZIO_FILE* iFile) {
    ZT_SIZE lLength = 0;
    if (ZIO_Scan(iFile)) {
        if (ZIO_HandleOpen(iFile, ZIO_MODE_READ)) {
            if (iFile->data.byte == NULL) {ZIO_BufferCreate(iFile);}
            if (ferror((FILE*)iFile->handle)) {clearerr((FILE*)iFile->handle);}
            rewind((FILE*)iFile->handle);
            lLength = fread(iFile->data.byte, 1, iFile->data.length, (FILE*)iFile->handle);
            if (rCloseHandle) {ZIO_HandleClose(iFile);}
        }
    }
	return lLength;
}
ZT_SIZE ZIO_Save(ZIO_FILE* iFile) {
    ZT_SIZE lLength = 0;
    if (ZIO_HandleOpen(iFile, ZIO_MODE_WRITE)) {
        lLength = fwrite(iFile->data.byte, 1, iFile->data.length, (FILE*)iFile->handle);
        if (rCloseHandle) {ZIO_HandleClose(iFile);}
    }
	return lLength;
}
void ZIO_Set(ZIO_FILE* iFile, ZT_U8* iData, ZT_SIZE iLength) {
    ZIO_BufferFree(iFile);
    iFile->data.byte = iData;
    iFile->data.length = iLength;
}
void ZIO_Append(ZIO_FILE* iFile, ZT_U8* iData, ZT_SIZE iLength) {
    iFile->data.byte = ZTM8_Resize(iFile->data.byte, iFile->data.length + iLength);
    ZTM8_Copy(iData, &(iFile->data.byte[iFile->data.length]), iLength);
    iFile->data.length += iLength;
}
*/
#endif //ZTMIO_C_INCLUDED
