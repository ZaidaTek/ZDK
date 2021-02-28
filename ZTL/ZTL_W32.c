/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL_W32_C_INCLUDED
#define ZTL_W32_C_INCLUDED

#include "ZTL__Runtime.h"
//#define ZTL__OS__WINDOWS // REMOVE ME!!!!
#ifdef ZTL__OS__WINDOWS
void ZTL_LibraryFree(ZT_LIBRARY* iLibrary) {
    FreeLibrary((HMODULE)iLibrary);
}
ZT_LIBRARY* ZTL_LibraryLoad(const ZT_CHAR* iPath) {
    return LoadLibrary((LPCSTR)iPath);
}
void* ZTL_LibraryFunction(ZT_LIBRARY* iLibrary, const ZT_CHAR* iName) {
    return GetProcAddress((HINSTANCE)iLibrary, (LPCSTR)iName);
}
ZT_CHAR* ZTL_SerialAddress(ZT_INDEX iPort) {
    #define ZTL_SERIALADDRESS(TEXT) (TEXT)[0] = '\\'; (TEXT)[1] = '\\'; (TEXT)[2] = '.'; (TEXT)[3] = '\\'; (TEXT)[4] = 'C'; (TEXT)[5] = 'O'; (TEXT)[6] = 'M'
    ZT_CHAR* lAddress;
    if (iPort < 10) {
        lAddress = ZTM8_New(sizeof(ZT_CHAR) * 9);
        ZTL_SERIALADDRESS(lAddress);
        lAddress[7] = iPort + 0x30;
        lAddress[8] = 0x0;
    } else if (iPort < 100) {
        lAddress = ZTM8_New(sizeof(ZT_CHAR) * 10);
        ZTL_SERIALADDRESS(lAddress);
        lAddress[7] = (iPort / 10) + 0x30;
        lAddress[8] = (iPort % 10) + 0x30;
        lAddress[9] = 0x0;
    } else if (iPort < 0x100) {
        lAddress = ZTM8_New(sizeof(ZT_CHAR) * 11);
        ZTL_SERIALADDRESS(lAddress);
        lAddress[7] = (iPort / 100) + 0x30;
        lAddress[8] = ((iPort / 10) % 10) + 0x30;
        lAddress[9] = (iPort % 10) + 0x30;
        lAddress[10] = 0x0;
    } else {
        lAddress = ZTM8_New(sizeof(ZT_CHAR) * 8);
        ZTL_SERIALADDRESS(lAddress);
        lAddress[7] = 0x0;
    }
    return lAddress;
    #undef ZTL_SERIALADDRESS
}
ZT_INDEX ZTL_SerialPort(const ZT_CHAR* iAddress) {
    ZT_INDEX lPort = 0;
    ZT_INDEX lLength = ZTC8_GetLength(iAddress);
    if (lLength < 9) {
        lPort += iAddress[7] - 0x30;
    } else if (lLength < 10) {
        lPort += (iAddress[7] - 0x30) * 10;
        lPort += iAddress[8] - 0x30;
    } else if (lLength < 11) {
        lPort += (iAddress[7] - 0x30) * 100;
        lPort += (iAddress[8] - 0x30) * 10;
        lPort += iAddress[9] - 0x30;
    }
    return lPort;
}
ZT_SERIAL* ZTL_SerialNew(const ZT_CHAR* iAddress, ZT_INDEX iBaud, ZT_SIZE iBufferIn, ZT_SIZE iBufferOut) {
    ZT_SERIAL* lDevice;
    if ((lDevice = CreateFileA((LPCTSTR)iAddress, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE) {
        DCB lDCB;
        if (SetupComm(lDevice, iBufferIn, iBufferOut) && GetCommState(lDevice, &lDCB)) {
            lDCB.BaudRate = (DWORD)iBaud;
            lDCB.ByteSize = 8;
            lDCB.StopBits = ONESTOPBIT;
            lDCB.Parity = NOPARITY;
            lDCB.fDtrControl = DTR_CONTROL_ENABLE;
            if (SetCommState(lDevice, &lDCB)) {
                ZTL_Sleep(ZTL_SERIAL_GRACE);
                ZTL_SerialFlush(lDevice);
                return lDevice;
            }
        }
        CloseHandle(lDevice);
    }
    return NULL;
}
void ZTL_SerialFree(ZT_SERIAL* iDevice) {
    CloseHandle(iDevice);
}
void ZTL_SerialFlush(ZT_SERIAL* iDevice) {
    PurgeComm(iDevice, PURGE_RXCLEAR | PURGE_TXCLEAR);
}
ZT_SIZE ZTL_SerialQueue(ZT_SERIAL* iDevice) {
    ZT_U32 lError = 0x0;
    COMSTAT lStatus; // static?
    ClearCommError(iDevice, (DWORD*)&lError, &lStatus);
    return lStatus.cbInQue;
}
ZT_SIZE ZTL_SerialRead(ZT_SERIAL* iDevice, ZT_U8* oBuffer, ZT_SIZE iLength) {
    ZT_U32 lRead;
    ReadFile(iDevice, (void*)oBuffer, (DWORD)iLength, (DWORD*)&lRead, NULL);
    return lRead;
}
ZT_SIZE ZTL_SerialWrite(ZT_SERIAL* iDevice, const ZT_U8* iBuffer, ZT_SIZE iLength) {
    ZT_U32 lWrite;
    WriteFile(iDevice, (void*)iBuffer, (DWORD)iLength, (DWORD*)&lWrite, NULL);
    return lWrite;
}
void ZTL_Execute(const ZT_CHAR* iPath, ZT_FLAG iMode) {
    LPCTSTR lType;
    switch (iMode & ~ZTL_EXECUTE_HIDE) {
        case ZTL_EXECUTE_OPEN: lType = "open"; break;
        case ZTL_EXECUTE_ADMIN: lType = "runas"; break;
        case ZTL_EXECUTE_EDIT: lType = "edit"; break;
        case ZTL_EXECUTE_PRINT: lType = "print"; break;
        default: lType = NULL; break;
    }
    ShellExecute(NULL, lType, (LPCTSTR)iPath, NULL, NULL, (iMode & ZTL_EXECUTE_HIDE) ? SW_SHOWMINNOACTIVE : SW_SHOW);
}
ZT_BOOL ZTL_DirectoryCreate(const ZT_CHAR* iPath) {
    BOOL lCreated = CreateDirectory((LPCTSTR)iPath, NULL);
    return (lCreated ? ZT_TRUE : ((GetLastError() == ERROR_ALREADY_EXISTS) ? (ZT_TRUE + 1) : ZT_FALSE));
}
ZT_FLAG ZTL_FileFlags(const ZT_CHAR* iPath) {
    ZT_FLAG lFlag = ZTL_FILE_NONE;
    DWORD lFlag_W32 = GetFileAttributes((LPCTSTR)iPath);
    if (lFlag_W32 != INVALID_FILE_ATTRIBUTES) {
        lFlag |= ZTL_FILE_VALID;
        if (lFlag_W32 & FILE_ATTRIBUTE_READONLY) {lFlag |= ZTL_FILE_READONLY;}
        if (lFlag_W32 & FILE_ATTRIBUTE_HIDDEN) {lFlag |= ZTL_FILE_HIDDEN;}
        if (lFlag_W32 & FILE_ATTRIBUTE_SYSTEM) {lFlag |= ZTL_FILE_SYSTEM;}
        if (lFlag_W32 & FILE_ATTRIBUTE_DIRECTORY) {lFlag |= ZTL_FILE_DIRECTORY;}
        if (lFlag_W32 & FILE_ATTRIBUTE_ARCHIVE) {lFlag |= ZTL_FILE_ARCHIVE;}
        if (lFlag_W32 & FILE_ATTRIBUTE_COMPRESSED) {lFlag |= ZTL_FILE_COMPRESSED;}
        if (lFlag_W32 & FILE_ATTRIBUTE_ENCRYPTED) {lFlag |= ZTL_FILE_ENCRYPTED;}
    }
    return lFlag;
}
ZT_BOOL ZTL_FileExists(const ZT_CHAR* iPath) {return (GetFileAttributes((LPCTSTR)iPath) != INVALID_FILE_ATTRIBUTES) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZTL_FileIsReadOnly(const ZT_CHAR* iPath) {return (GetFileAttributes((LPCTSTR)iPath) & FILE_ATTRIBUTE_READONLY) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZTL_FileIsHidden(const ZT_CHAR* iPath) {return (GetFileAttributes((LPCTSTR)iPath) & FILE_ATTRIBUTE_HIDDEN) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZTL_FileIsSystem(const ZT_CHAR* iPath) {return (GetFileAttributes((LPCTSTR)iPath) & FILE_ATTRIBUTE_SYSTEM) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZTL_FileIsDirectory(const ZT_CHAR* iPath) {return (GetFileAttributes((LPCTSTR)iPath) & FILE_ATTRIBUTE_DIRECTORY) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZTL_FileIsArchive(const ZT_CHAR* iPath) {return (GetFileAttributes((LPCTSTR)iPath) & FILE_ATTRIBUTE_ARCHIVE) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZTL_FileIsCompressed(const ZT_CHAR* iPath) {return (GetFileAttributes((LPCTSTR)iPath) & FILE_ATTRIBUTE_COMPRESSED) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZTL_FileIsEncrypted(const ZT_CHAR* iPath) {return (GetFileAttributes((LPCTSTR)iPath) & FILE_ATTRIBUTE_ENCRYPTED) ? ZT_TRUE : ZT_FALSE;}
void ZTL_SelectInit(void) {
    if (rZTL__SELECT_FLAG & ZTL_FLAG_SELECT_INIT) {
        rZTL__SELECT_FLAG &= ~ZTL_FLAG_SELECT_INIT;
        ZTM8_Zero(&rZTL__SELECT_RUNTIME, sizeof(OPENFILENAME));
        rZTL__SELECT_RUNTIME.lStructSize = sizeof(OPENFILENAME);
        rZTL__SELECT_RUNTIME.lpstrFilter = (LPCTSTR)rZTL__SELECT_TYPE;
        rZTL__SELECT_RUNTIME.nFilterIndex = 1;
        rZTL__SELECT_RUNTIME.lpstrFile = (LPTSTR)rZTL__SELECT_PATH;
        rZTL__SELECT_RUNTIME.nMaxFile = ZTL_BUFFER_PATH;
        rZTL__SELECT_RUNTIME.lpstrInitialDir = (LPCTSTR)rZTL__SELECT_DIR;
        rZTL__SELECT_RUNTIME.Flags = OFN_EXPLORER;
    }
}
void ZTL_SelectTitle(const ZT_CHAR* iTitle) {
    ZTL_SelectInit();
    rZTL__SELECT_RUNTIME.lpstrTitle = (LPCTSTR)iTitle;
}
void ZTL_SelectFiletype(const ZT_CHAR** iPattern, const ZT_CHAR** iLabel, ZT_INDEX iCount, ZT_INDEX iSelected) {
    ZTL_SelectInit();
    const ZT_CHAR** lLabel = (iLabel != NULL) ? iLabel : iPattern;
    ZT_INDEX lIndex = 0;
    ZT_INDEX lLimit = ZTL_BUFFER_PATH - 3;
    for (ZT_INDEX i = 0; i < iCount; i++) {
        ZT_INDEX lIndexLabel = -1;
        ZT_INDEX lIndexPattern = -1;
        while ((lIndex < lLimit) && (rZTL__SELECT_TYPE[lIndex++] = lLabel[i][++lIndexLabel]));
        while ((lIndex < lLimit) && (rZTL__SELECT_TYPE[lIndex++] = iPattern[i][++lIndexPattern]));
    }
    rZTL__SELECT_TYPE[lIndex++] = 0x0;
    rZTL__SELECT_TYPE[lIndex++] = 0x0;
    rZTL__SELECT_TYPE[lIndex++] = 0x0;
    rZTL__SELECT_RUNTIME.nFilterIndex = iSelected + 1;
}
void ZTL_SelectSetup(void) {
    ZTL_SelectInit();
    if (rZTL__SELECT_FLAG & ZTL_FLAG_SELECT_SAVE) {
        rZTL__SELECT_RUNTIME.Flags |= OFN_OVERWRITEPROMPT;
        rZTL__SELECT_RUNTIME.Flags &= ~OFN_FILEMUSTEXIST;
        rZTL__SELECT_RUNTIME.Flags &= ~OFN_ALLOWMULTISELECT;
    } else {
        rZTL__SELECT_RUNTIME.Flags &= ~OFN_OVERWRITEPROMPT;
        rZTL__SELECT_RUNTIME.Flags |= OFN_FILEMUSTEXIST;
        if (rZTL__SELECT_FLAG & ZTL_FLAG_SELECT_MULTI) {rZTL__SELECT_RUNTIME.Flags |= OFN_ALLOWMULTISELECT;} else {rZTL__SELECT_RUNTIME.Flags &= ~OFN_ALLOWMULTISELECT;}
    }
    ZTC8_CopyTarget(rZTL__SELECT_FILE, rZTL__SELECT_PATH);
    rZTL__SELECT_COUNT = 0;
}
void ZTL_SelectProcess(void) {
    rZTL__SELECT_COUNT = 1;
    ZT_INDEX lIndexFile = rZTL__SELECT_RUNTIME.nFileOffset - 1;
    ZTC8_CopyTargetLength(rZTL__SELECT_PATH, rZTL__SELECT_DIR, lIndexFile);
    rZTL__SELECT_DIR[lIndexFile] = ZTM_CHAR_PATH;
    if (rZTL__SELECT_PATH[lIndexFile]) {
        ZTC8_CopyTarget(&rZTL__SELECT_PATH[lIndexFile + 1], rZTL__SELECT_FILE);
    } else {
        ZT_INDEX lIndex = -1;
        while ((rZTL__SELECT_PATH[++lIndexFile + 1] || rZTL__SELECT_PATH[lIndexFile])) {
            if (!(rZTL__SELECT_FILE[++lIndex] = rZTL__SELECT_PATH[lIndexFile])) {++rZTL__SELECT_COUNT;}
        }
    }
}
#endif // ZTL__OS__WINDOWS

#endif // ZTL_W32_C_INCLUDED
