/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_PRINTER_H_INCLUDED
#define ZTK_PRINTER_H_INCLUDED

#include "ZTK.h"

//#define ZTK_PRINTER_FALLBACK_STDIO

#define ZTK_PRINTER_TYPE_NONE 0x0
#define ZTK_PRINTER_TYPE_SYSTEM 0x1
#define ZTK_PRINTER_TYPE_SPRITE 0x2

typedef void ZT_PRINTER;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTK_Print(const void* iText, ...);
void ZTK_PrintBufferLoad(const void* iText, ...);
void ZTK_PrintBufferGetSize(ZT_RECT* oSize);
void ZTK_PrintBuffer(void);
void ZTK_PrintBufferGetCustomSize(ZT_FONT* iFont, const ZT_POINT* iCursor, const ZT_RECT* iBounds, ZT_RECT* oSize);
void ZTK_PrintBufferCustom(ZT_FONT* iFont, const ZT_POINT* iCursor, const ZT_RECT* iBounds);
void ZTK_PrinterInit(ZT_FONT* iFont);
void ZTK_PrinterQuit(void);
void ZTK_PrinterSet(ZT_FONT* iFont);
void ZTK_PrinterSetBounds(const ZT_RECT* iBounds);
void ZTK_PrinterSetCursor(const ZT_POINT* iPosition);
void ZTK_PrintPos(const ZT_POINT* iPos);
void ZTK_PrintPosFromInteger(ZT_I iX, ZT_I iY);
void ZTK_PrintPosX(ZT_I iX);
void ZTK_PrintPosY(ZT_I iY);
void ZTK_PrintPosRelative(ZT_DBL iX, ZT_DBL iY);
void ZTK_PrintPosXRelative(ZT_DBL iX);
void ZTK_PrintPosYRelative(ZT_DBL iY);
#ifdef __cplusplus
}
#endif // __cplusplus


#endif // ZTK_PRINTER_H_INCLUDED
