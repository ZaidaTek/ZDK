/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTMIO_C_INCLUDED
#define ZTMIO_C_INCLUDED

#include "ZTMIO.h"

#include <stdio.h>

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

ZT_SIZE ZIO_PipedScan(const ZT_CHAR* iPath) {return ZIO_PipedRead(iPath, NULL, NULL);}
ZT_SIZE ZIO_PipedRead(const ZT_CHAR* iPath, void* oDestination, ZT_SIZE* oLength) {
	ZT_SIZE lRead = 0;
	if (iPath != NULL) {
		FILE* lFile = fopen((const char*)iPath, "rb");
		if (lFile != NULL) {
			if (ferror(lFile)) {clearerr(lFile);}
			rewind(lFile);
			fseek(lFile, 0, SEEK_END);
			lRead = ftell(lFile);
			if (oLength != NULL) {*oLength = lRead;}
			if (oDestination != NULL) {
				rewind(lFile);
				lRead = fread(oDestination, 1, lRead, lFile);
			}
			fclose(lFile);
		}
	}
	return lRead;
}
ZT_SIZE ZIO_PipedWrite(const ZT_CHAR* iPath, const void* iSource, ZT_SIZE iLength) {
	ZT_SIZE lWrite = 0;
	if (iLength && iSource != NULL && iPath != NULL) {
		FILE* lFile = fopen((const char*)iPath, "wb");
		if (lFile != NULL) {
			if (ferror(lFile)) {clearerr(lFile);}
			rewind(lFile);
			lWrite = fwrite(iSource, 1, iLength, lFile);
			fclose(lFile);
		}
	}
	return lWrite;
}
ZT_SIZE ZIO_PipedAppend(const ZT_CHAR* iPath, const void* iSource, ZT_SIZE iLength) {
	ZT_SIZE lAppend = 0;
	if (iLength && iSource != NULL && iPath != NULL) {
		FILE* lFile = fopen((const char*)iPath, "ab");
		if (lFile != NULL) {
			if (ferror(lFile)) {clearerr(lFile);}
			lAppend = fwrite(iSource, 1, iLength, lFile);
			fclose(lFile);
		}
	}
	return lAppend;
}
void ZIO_PathClear(ZIO_FILE* iFile) {
    if (iFile != NULL) {
		ZTM8_Free(iFile->path);
		iFile->path = NULL;
    }
}
void ZIO_HandleClose(ZIO_FILE* iFile) {
	if (iFile != NULL) {
		if (iFile->handle != NULL) {
			fclose((FILE*)iFile->handle);
			iFile->handle = NULL;
		}
	}
}
void ZIO_BufferFree(ZIO_FILE* iFile) {
	if (iFile != NULL) {
		ZTM8_Free(iFile->data.byte);
		iFile->data.byte = NULL;
	}
}
void ZIO_Free(ZIO_FILE* iFile) {
	if (iFile != NULL) {
        ZIO_PathClear(iFile);
		ZIO_HandleClose(iFile);
		ZIO_BufferFree(iFile);
		ZTM8_Free(iFile);
	}
}
void ZIO_Path(ZIO_FILE* iFile, const ZT_CHAR* iPath) {
    if (iFile != NULL && iPath != NULL) {
        if (iFile->path != NULL) {ZIO_PathClear(iFile);}
        iFile->path = ZTC8_Copy(iPath);
    }
}
void* ZIO_HandleOpen(ZIO_FILE* iFile, ZT_FLAG iMode) {
    if (iFile != NULL) {
        if (iFile->path != NULL) {
            if (iFile->handle != NULL) {ZIO_HandleClose(iFile);}
            const char* lMode = "rb";
            iFile->mode = ZIO_MODE_READ;
            if (iMode & ZIO_MODE_APPEND) {
                iFile->mode |= ZIO_MODE_APPEND;
                if (iMode & ZIO_MODE_WRITE) {
                    lMode = "wb";
                    iFile->mode |= ZIO_MODE_WRITE;
                } else {
                    lMode = "ab";
                }
            }
            return (iFile->handle = (void*)fopen((const char*)iFile->path, lMode));
        }
    }
	return NULL;
}
void ZIO_Terminate(ZIO_FILE* iFile) {
    if (iFile != NULL) {
        if (iFile->data.byte != NULL) {
			#ifdef ZIO_APPEND_EOF
            iFile->data.byte[iFile->data.length] = rEOF;
			#endif // ZIO_APPEND_EOF
        }
    }
}
void ZIO_BufferCreate(ZIO_FILE* iFile) {
	if (iFile != NULL) {
        if (iFile->data.length) {
            ZIO_BufferFree(iFile);
            iFile->data.byte = ZTM8_New(iFile->data.length + ((rAppendEOF) ? 2 : 1));
            if (rAppendEOF) {ZIO_Terminate(iFile);}
        }
	}
}
ZIO_FILE* ZIO_New(const ZT_CHAR* iPath) {
    if (iPath != NULL) {
		ZIO_FILE* lFile;
		if ((lFile = ZTM8_Init(sizeof(ZIO_FILE), 0x0)) != NULL) {if ((lFile->path = ZTC8_Copy(iPath)) != NULL) {return lFile;}}
		ZTM8_Free(lFile);
    }
	return NULL;
}
ZT_SIZE ZIO_Scan(ZIO_FILE* iFile) {
    ZT_SIZE lLength = 0;
    if (iFile != NULL) {
		if (ZIO_HandleOpen(iFile, ZIO_MODE_READ) != NULL) {
			if (ferror((FILE*)iFile->handle)) {clearerr((FILE*)iFile->handle);}
			rewind((FILE*)iFile->handle);
			fseek((FILE*)iFile->handle , 0 , SEEK_END);
			lLength = ftell((FILE*)iFile->handle);
			if (iFile->data.length != lLength) {
				ZIO_BufferFree(iFile);
				iFile->data.length = lLength;
			}
            if (rCloseHandle) {ZIO_HandleClose(iFile);}
		}
    }
	return lLength;
}
ZT_SIZE ZIO_Load(ZIO_FILE* iFile) {
    ZT_SIZE lLength = 0;
	if (iFile != NULL) {
        if (ZIO_Scan(iFile)) {
			if (ZIO_HandleOpen(iFile, ZIO_MODE_READ) != NULL) {
				if ((!(iFile->mode & ZIO_MODE_CHANGE))) {
					if (iFile->data.byte == NULL) {ZIO_BufferCreate(iFile);}
					if (iFile->data.byte != NULL) {
						if (ferror((FILE*)iFile->handle)) {clearerr((FILE*)iFile->handle);}
						rewind((FILE*)iFile->handle);
						lLength = fread((char*)iFile->data.byte, 1, iFile->data.length, (FILE*)iFile->handle);
					}
					if (rCloseHandle) {ZIO_HandleClose(iFile);}
				}
			}
		}
	}
	return lLength;
}
ZT_SIZE ZIO_Save(ZIO_FILE* iFile) {
    ZT_SIZE lLength = 0;
	if (iFile != NULL) {
		if (iFile->data.length && iFile->data.byte != NULL) {
			if (ZIO_HandleOpen(iFile, ZIO_MODE_CHANGE) != NULL) {
				if (iFile->mode == ZIO_MODE_CHANGE) {
					lLength = fwrite((char*)iFile->data.byte, 1, iFile->data.length, (FILE*)iFile->handle);
					if (rCloseHandle) {ZIO_HandleClose(iFile);}
				}
			}
		}
	}
	return lLength;
}
void ZIO_Set(ZIO_FILE* iFile, ZT_U8* iData, ZT_SIZE iLength) {
	if (iFile != NULL) {
		ZIO_BufferFree(iFile);
		iFile->data.byte = iData;
		iFile->data.length = iLength;
	}
}
void ZIO_Append(ZIO_FILE* iFile, ZT_U8* iData, ZT_SIZE iLength) {
	if (iFile != NULL) {
		iFile->data.byte = ZTM8_Resize(iFile->data.byte, iFile->data.length + iLength);
		if (iData != NULL) {ZTM8_Copy(iData, &(iFile->data.byte[iFile->data.length]), iLength);}
		iFile->data.length += iLength;
	}
}

#endif //ZTMIO_C_INCLUDED
