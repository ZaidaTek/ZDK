/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTL_RT_LINUX_C_INCLUDED
#define ZTL_RT_LINUX_C_INCLUDED

#include "ZTL-RT.h"
#include <stdio.h>
#if defined(ZTL_BUILD_LINUX) && (ZTL_BUILD_LINUX)
void ZTL_LibraryFree(ZT_LIBRARY* iLibrary) {
    dlclose(iLibrary);
}
ZT_LIBRARY* ZTL_LibraryLoad(const ZT_CHAR* iPath) {
    return dlopen((const char*)iPath, RTLD_LAZY);
}
void* ZTL_LibraryFunction(ZT_LIBRARY* iLibrary, const ZT_CHAR* iName) {
    return dlsym(iLibrary, (const char*)iName);
}
ZT_CHAR* ZTL_SerialAddress(ZT_INDEX iPort) {
    #define mZTL_SERIAL_ADDRESS_PORT(TARGET,OFFSET,PORT) \
    if ((PORT) < 10) {\
        (TARGET)[(OFFSET)] = (PORT) + 0x30;\
        (TARGET)[(OFFSET) + 1] = 0x0;\
    } else if ((PORT) < 100) {\
        (TARGET)[(OFFSET)] = ((PORT) / 10) + 0x30;\
        (TARGET)[(OFFSET) + 1] = ((PORT) % 10) + 0x30;\
        (TARGET)[(OFFSET) + 2] = 0x0;\
    } else if ((PORT) < 0x100) {\
        (TARGET)[(OFFSET)] = ((PORT) / 100) + 0x30;\
        (TARGET)[(OFFSET) + 1] = (((PORT) / 10) % 10) + 0x30;\
        (TARGET)[(OFFSET) + 2] = ((PORT) % 10) + 0x30;\
        (TARGET)[(OFFSET) + 3] = 0x0;\
    } else {\
        (TARGET)[(OFFSET)] = 0x0;\
    }
    ZT_CHAR* lAddress = ZTM8_New(sizeof(ZT_CHAR) * 16);
    lAddress[ 0] = '/';
    lAddress[ 1] = 'd';
    lAddress[ 2] = 'e';
    lAddress[ 3] = 'v';
    lAddress[ 4] = '/';
    lAddress[ 5] = 't';
    lAddress[ 6] = 't';
    lAddress[ 7] = 'y';
    lAddress[ 8] = 'U';
    lAddress[ 9] = 'S';
    lAddress[10] = 'B';
    mZTL_SERIAL_ADDRESS_PORT(lAddress, 11, iPort);
    return lAddress;
    #undef mZTL_SERIAL_ADDRESS_PORT
}
ZT_SERIAL* ZTL_SerialNew(const ZT_CHAR* iAddress, ZT_INDEX iBaud, ZT_SIZE iBufferIn, ZT_SIZE iBufferOut) {
    (void)iBufferIn; (void)iBufferOut; // not needed in Linux?
    rZT_SERIAL* lDevice = ZTM8_New(sizeof(rZT_SERIAL));
    if ((*lDevice = open((const char*)iAddress, O_RDWR/* | O_DIRECT*/)) >= 0) {
        if (!ioctl(*lDevice, TIOCEXCL, NULL)) {
            static struct termios2 lTTY;
            if (!ioctl(*lDevice, TCGETS2, &lTTY)) {
                lTTY.c_cflag &= ~(CRTSCTS | CBAUD | CSIZE | CSTOPB | PARENB); // disable RTS/CTS flow ctrl, clear all baud rate, clear all packet sizes, clear two-bit stop (=use only one), disable parity
                lTTY.c_oflag &= ~(OPOST); // disable output processing
                lTTY.c_lflag &= ~(ICANON | ISIG | IEXTEN); // use non-canonical (raw) mode and set other related bits for raw mode, see also cfmakeraw()
                lTTY.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ECHOCTL | ECHOPRT | ECHOKE); // turn off all echoing to be safe
                lTTY.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP| INLCR | IGNCR | ICRNL | IXON); // more bits to clear for raw mode
                lTTY.c_cflag |= CREAD | CLOCAL | CS8 | BOTHER; // enable RX, ignore modem lines, 8-bit packets, arbitrary baud
                lTTY.c_cc[VMIN] = (lTTY.c_cc[VTIME] = 0); // set both to 0 to enable non-blocking read in noncanonical mode
                lTTY.c_ospeed = (lTTY.c_ispeed = iBaud);
                if (!ioctl(*lDevice, TCSETS2, &lTTY)) {
                    //static struct serial_struct lExtra; // FIXME doesn't work, set flag is discarded; find error or if has been deprecated
                    //if (!ioctl(*lDevice, TIOCGSERIAL, &lExtra)) {lExtra.flags |= ASYNC_LOW_LATENCY; ioctl(*lDevice, TIOCSSERIAL, &lExtra);}
                    ZTL_Sleep(ZTL_SERIAL_GRACE);
                    ZTL_SerialFlush(lDevice);
                    return lDevice;
                }
            }
        }
        close(*lDevice);
    }
    ZTM8_Free(lDevice);
    return NULL;
}
void ZTL_SerialFree(ZT_SERIAL* iDevice) {
    ioctl(*(rZT_SERIAL*)iDevice, TIOCNXCL, NULL);
    close(*(rZT_SERIAL*)iDevice);
    ZTM8_Free(iDevice);
}
void ZTL_SerialFlush(ZT_SERIAL* iDevice) {
    ioctl(*(rZT_SERIAL*)iDevice, TCFLSH, TCIOFLUSH);
}
ZT_SIZE ZTL_SerialQueue(ZT_SERIAL* iDevice) {
    ZT_SIZE lBytes = 0x0;
    ioctl(*(rZT_SERIAL*)iDevice, FIONREAD, &lBytes);
    return lBytes;
}
ZT_SIZE ZTL_SerialRead(ZT_SERIAL* iDevice, ZT_U8* oBuffer, ZT_SIZE iLength) {
    return read(*(rZT_SERIAL*)iDevice, oBuffer, iLength);
}
ZT_SIZE ZTL_SerialWrite(ZT_SERIAL* iDevice, const ZT_U8* iBuffer, ZT_SIZE iLength) {
    return write(*(rZT_SERIAL*)iDevice, iBuffer, iLength);
}
/*
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
*/
ZT_CHAR* ZTL_ShellPipeInTarget(const ZT_CHAR* iCommand, ZT_CHAR* oTarget, ZT_SIZE iCapacity) {
    ZT_FLAG lMode = oTarget != NULL ? 0x1 : 0x0;
    ZT_CHAR* lBuffer = lMode ? oTarget : ZTM8_New(sizeof(ZT_CHAR) * ZTL_BUFFER_PIPE);
    ZT_SIZE lCapacity = lMode ? iCapacity : ZTL_BUFFER_PIPE;
    ZT_SIZE lRead = 0;
    FILE* lPipe = popen((const char*)iCommand, "r");
    while (0x1) {
        lRead = fread(lBuffer, 1, lCapacity, lPipe);
        if (lRead != lCapacity || lMode) {break;}
        lBuffer = ZTM8_Resize(lBuffer, sizeof(ZT_CHAR) * (lRead / lCapacity + 1) * lCapacity);
    }
    pclose(lPipe);
    return lBuffer;
}
ZT_FLAG ZTL_ShellOpen(const ZT_CHAR* iPath, ZT_FLAG iMode) {
    (void)iMode; // FIXME find out if these can be used in Linux
    return ZTL_ShellExec((const ZT_CHAR*)"xdg-open \"%s\"", iPath);
}
ZT_BOOL ZTL_DirectoryCreate(const ZT_CHAR* iPath) {
    return ZTL_ShellExec((const ZT_CHAR*)"mkdir -p \"%s\" > /dev/null 2>/dev/null", iPath) ? ZT_FALSE : ZT_TRUE;
}
void ZTL_NodeInfoTarget(const ZT_CHAR* iPath, ZT_META_FILE* oTarget) {
    ZTM8_Zero(oTarget, sizeof(ZT_META_FILE));
    static struct statx lBuffer;
    if (!statx(AT_FDCWD, (const char*)iPath, AT_EMPTY_PATH, STATX_BASIC_STATS | STATX_BTIME, &lBuffer)) {
        oTarget->handle = NULL;
        oTarget->path = iPath;
        oTarget->length = lBuffer.stx_size;
        oTarget->alloc = lBuffer.stx_blocks << 9;
        oTarget->id = lBuffer.stx_ino;
        oTarget->owner = lBuffer.stx_uid;
        oTarget->group = lBuffer.stx_gid;
        oTarget->type = (
            (((lBuffer.stx_mode & S_IFREG)  == S_IFREG)  ? ZTL_FILE_TYPE_REG  : 0x0) |
            (((lBuffer.stx_mode & S_IFDIR)  == S_IFDIR)  ? ZTL_FILE_TYPE_DIR  : 0x0) |
            (((lBuffer.stx_mode & S_IFLNK)  == S_IFLNK)  ? ZTL_FILE_TYPE_SYM  : 0x0) |
            (((lBuffer.stx_mode & S_IFBLK)  == S_IFBLK)  ? ZTL_FILE_TYPE_BLK  : 0x0) |
            (((lBuffer.stx_mode & S_IFCHR)  == S_IFCHR)  ? ZTL_FILE_TYPE_CHAR : 0x0) |
            (((lBuffer.stx_mode & S_IFIFO)  == S_IFIFO)  ? ZTL_FILE_TYPE_FIFO : 0x0) |
            (((lBuffer.stx_mode & S_IFSOCK) == S_IFSOCK) ? ZTL_FILE_TYPE_SKT  : 0x0)
        );
        oTarget->perm = (
            ((lBuffer.stx_mode &  0x7000) << 15) |
            ((lBuffer.stx_mode & S_IRWXO) << 16) |
            ((lBuffer.stx_mode & S_IRWXG) <<  5) |
            ((lBuffer.stx_mode & S_IRWXU) >>  6)
        );
        ZT_FLAG lAttr = lBuffer.stx_attributes & lBuffer.stx_attributes_mask;
        oTarget->attr = (
            (((lAttr & STATX_ATTR_COMPRESSED) == STATX_ATTR_COMPRESSED) ? ZTL_FILE_COMPRESSED : 0x0) |
            (((lAttr & STATX_ATTR_ENCRYPTED) == STATX_ATTR_ENCRYPTED) ? ZTL_FILE_ENCRYPTED : 0x0)
        );
        oTarget->time.meta_a = -1;
        oTarget->time.meta_b = -1;
        oTarget->time.meta_m = lBuffer.stx_ctime.tv_sec;
        oTarget->time.file_a = lBuffer.stx_atime.tv_sec;
        oTarget->time.file_b = lBuffer.stx_btime.tv_sec;
        oTarget->time.file_m = lBuffer.stx_mtime.tv_sec;
    }
}
void ZTL_SelectDialogTitle(const ZT_CHAR* iTitle) {
    ZTL_SelectInit();
    rZTL__SELECT_RUNTIME.title = iTitle;
}
void ZTL_SelectDialogFiletype(const ZT_CHAR** iPattern, const ZT_CHAR** iLabel, ZT_INDEX iCount, ZT_INDEX iSelected) {
    ZTL_SelectInit();
    const ZT_CHAR** lLabel = (iLabel != NULL) ? iLabel : iPattern;
    ZT_INDEX lIndex = 0;
    ZT_INDEX lLimit = ZTL_BUFFER_PATH - 3;
    for (ZT_INDEX n = 0; n < iCount; ++n) {
        ZT_INDEX i = n ? (n > iSelected ? n : n - 1) : iSelected;
        ZT_INDEX lIndexLabel = -1;
        ZT_INDEX lIndexPattern = -1;
        while ((lIndex < lLimit) && (rZTL__SELECT_TYPE[lIndex++] = lLabel[i][++lIndexLabel]));
        while ((lIndex < lLimit) && (rZTL__SELECT_TYPE[lIndex++] = iPattern[i][++lIndexPattern]));
    }
    rZTL__SELECT_TYPE[lIndex++] = 0x0;
    rZTL__SELECT_TYPE[lIndex++] = 0x0;
}
ZT_INDEX ZTL_RuntimeSelectDialog() {
    #define lFNC_APPEND(ARGS...) ({lCache = lAvailable; ZTC8_FormatTarget(lCursor, &lCache, ARGS); lCursor += lCache; lAvailable -= lCache;})
    ZTL_SelectInit();
    rZTL__SELECT_COUNT = 0;
    ZT_CHAR* lCursor = rZTL__SELECT_PATH;
    ZT_SIZE lAvailable = ZTL_BUFFER_PATH;
    ZT_SIZE lCache;
    ZT_SIZE lLengthDir = ZTC8_GetLength(rZTL__SELECT_DIR);
    ZT_SIZE lLengthFile = ZTC8_GetLength(rZTL__SELECT_FILE);
    lFNC_APPEND((const ZT_CHAR*)"zenity --file-selection");
    if (rZTL__SELECT_RUNTIME.title != NULL) {lFNC_APPEND((const ZT_CHAR*)" --title=\"%s\"", rZTL__SELECT_RUNTIME.title);}
    if (rZTL__SELECT_FLAG & ZTL_FLAG_SELECT_SAVE) {lFNC_APPEND((const ZT_CHAR*)" --save --confirm-overwrite");}
    if (rZTL__SELECT_FLAG & ZTL_FLAG_SELECT_MULTI) {lFNC_APPEND((const ZT_CHAR*)" --multiple");}
    if (lLengthDir || lLengthFile) {
        lFNC_APPEND(
            (const ZT_CHAR*)" --filename=\"%s%s%s\"",
            lLengthDir ? rZTL__SELECT_DIR : (const ZT_CHAR*)"",
            lLengthDir && rZTL__SELECT_DIR[lLengthDir - 1] != ZTM_CHAR_PATH ? ZTM_TEXT_PATH : (const ZT_CHAR*)"",
            lLengthFile ? rZTL__SELECT_FILE : (const ZT_CHAR*)""
        );
    }
    ZT_SIZE i = 0;
    while (rZTL__SELECT_TYPE[i]) {
        const ZT_CHAR* lLabel = &rZTL__SELECT_TYPE[i];
        i += ZTC8_GetLength(&rZTL__SELECT_TYPE[i]) + 1;
        const ZT_CHAR* lPattern = &rZTL__SELECT_TYPE[i];
        i += ZTC8_GetLength(&rZTL__SELECT_TYPE[i]) + 1;
        lFNC_APPEND((const ZT_CHAR*)" --file-filter=\"%s|%s\"", lLabel, lPattern);
    }
    ZTL_ShellPipeInTarget(rZTL__SELECT_PATH, rZTL__SELECT_FILE, ZTL_BUFFER_PATH);
    rZTL__SELECT_DIR[0] = ZTM_CHAR_NT; // not needed in result processing in Linux
    ZT_CHAR lChar;
    i = -1;
    while ((lChar = (rZTL__SELECT_FILE[++i]))) {if (lChar == '|' || lChar == '\n') {rZTL__SELECT_FILE[i] = ZTM_CHAR_NT; ++rZTL__SELECT_COUNT;}}
    return rZTL__SELECT_COUNT;
    #undef lFNC_APPEND
}
#endif // ZTL_BUILD_LINUX

#endif // ZTL_RT_LINUX_C_INCLUDED
