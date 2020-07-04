/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__RUNTIMEPRINTER_H_INCLUDED
#define ZTK__RUNTIMEPRINTER_H_INCLUDED

#include "ZTK__Runtime.h"
#include "../ZTK_Printer.h"

#include <stdio.h>
#include <stdarg.h>

#define ZTK_PRINTER_BUFFER 8192
#define ZTK_PRINTER_FLAG_NONE ZTK_FLAG_NONE
#define ZTK_PRINTER_FLAG_OVERFLOW 0x1
#define ZTK_PRINTER_FLAG_SIZE 0x10
#define ZTK_DEFAULT_PRINTER_FLAG (ZTK_PRINTER_FLAG_OVERFLOW)

typedef struct {
    ZT_FONT* font;
    ZT_POINT cursor;
    ZT_RECT bounds;
} ZT_PNT_HOST_PARAMS;

typedef struct {
    struct {
        ZT_CHAR* buffer;
        ZT_RECT rect;
    } print;
    ZT_FLAG flag;
    ZT_FLAG type;
    ZT_PNT_HOST_PARAMS user;
} ZT_PNT_HOST;

ZT_PNT_HOST* gZT_Printer;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTK_PrinterPipe(ZT_PNT_HOST_PARAMS* iUser);
void ZTK_PrinterPipeLoop(ZT_PNT_HOST_PARAMS* iUser, ZT_CHAR* iText);
void ZTK_PrinterPipeLine(ZT_PNT_HOST_PARAMS* iUser, ZT_CHAR* iText, ZT_INDEX iLength);
void ZTK_PrinterPipeFeed(ZT_PNT_HOST_PARAMS* iUser);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ZTK__RUNTIMEPRINTER_H_INCLUDED
