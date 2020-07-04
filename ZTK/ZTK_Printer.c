/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_PRINTER_C_INCLUDED
#define ZTK_PRINTER_C_INCLUDED

#include "ZTK/ZTK__RuntimePrinter.h"

ZT_PNT_HOST* gZT_Printer = NULL;

void ZTK_Print(const void* iText, ...) {
    if (gZT_Printer != NULL && iText != NULL) {
        va_list lList;
        va_start(lList, (const char*)iText);
        vsnprintf((char*)gZT_Printer->print.buffer, ZTK_PRINTER_BUFFER, (const char*)iText, lList);
        va_end(lList);
        gZT_Printer->print.buffer[(ZTK_PRINTER_BUFFER - 1)] = ZTM_CHAR_NT;
        ZTK_PrinterPipe(NULL);
    }
}
void ZTK_PrintBufferLoad(const void* iText, ...) {
    if (gZT_Printer != NULL && iText != NULL) {
        va_list lList;
        va_start(lList, (const char*)iText);
        vsnprintf((char*)gZT_Printer->print.buffer, ZTK_PRINTER_BUFFER, (const char*)iText, lList);
        va_end(lList);
        gZT_Printer->print.buffer[(ZTK_PRINTER_BUFFER - 1)] = ZTM_CHAR_NT;
    }
}
void ZTK_PrintBufferGetSize(ZT_RECT* oSize) {
    if (gZT_Printer != NULL) {
        gZT_Printer->flag |= ZTK_PRINTER_FLAG_SIZE;
        ZTK_PrinterPipe(&(gZT_Printer->user));
        if (oSize != NULL) {*oSize = gZT_Printer->print.rect;}
        gZT_Printer->flag &= ~ZTK_PRINTER_FLAG_SIZE;
    }
}
void ZTK_PrintBuffer(void) {
    if (gZT_Printer != NULL) {
        ZTK_PrinterPipe(&(gZT_Printer->user));
    }
}
void ZTK_PrintBufferGetCustomSize(ZT_FONT* iFont, const ZT_POINT* iCursor, const ZT_RECT* iBounds, ZT_RECT* oSize) {
    if (gZT_Printer != NULL) {
        ZT_PNT_HOST_PARAMS lPrint;
        lPrint.font = (iFont != NULL) ? iFont : gZT_Printer->user.font;
        lPrint.cursor = (iCursor != NULL) ? *iCursor : gZT_Printer->user.cursor;
        lPrint.bounds = (iBounds != NULL) ? *iBounds : gZT_Printer->user.bounds;
        gZT_Printer->flag |= ZTK_PRINTER_FLAG_SIZE;
        ZTK_PrinterPipe(&lPrint);
        if (oSize != NULL) {*oSize = gZT_Printer->print.rect;}
        gZT_Printer->flag &= ~ZTK_PRINTER_FLAG_SIZE;
    }
}
void ZTK_PrintBufferCustom(ZT_FONT* iFont, const ZT_POINT* iCursor, const ZT_RECT* iBounds) {
    if (gZT_Printer != NULL) {
        ZT_PNT_HOST_PARAMS lPrint;
        lPrint.font = (iFont != NULL) ? iFont : gZT_Printer->user.font;
        lPrint.cursor = (iCursor != NULL) ? *iCursor : gZT_Printer->user.cursor;
        lPrint.bounds = (iBounds != NULL) ? *iBounds : gZT_Printer->user.bounds;
        ZTK_PrinterPipe(&lPrint);
    }
}
void ZTK_PrinterInit(ZT_FONT* iFont) {
    if (gZT_Printer == NULL && gZT_Window != NULL) {
        if ((gZT_Printer = (ZT_PNT_HOST*)ZTM8_New(sizeof(ZT_PNT_HOST))) != NULL) {
            if ((gZT_Printer->print.buffer = (ZT_CHAR*)ZTM8_New(ZTK_PRINTER_BUFFER * sizeof(ZT_CHAR))) != NULL) {
                gZT_Printer->flag = ZTK_DEFAULT_PRINTER_FLAG;
                gZT_Printer->type = ZTK_PRINTER_TYPE_SPRITE;
            } else {
                ZTM8_Free(gZT_Printer);
                gZT_Printer = NULL;
            }
        }
    }
    ZTK_PrinterSet(iFont);
    ZTK_PrinterSetBounds(NULL);
}
void ZTK_PrinterQuit(void) {
    if (gZT_Printer != NULL) {
        ZTM8_Free(gZT_Printer->print.buffer);
        ZTM8_Free(gZT_Printer);
        gZT_Printer = NULL;
    }
}
void ZTK_PrinterSet(ZT_FONT* iFont) {
    if (gZT_Printer != NULL){
        gZT_Printer->user.font = (iFont != NULL) ? iFont : gZT_Window->user.font;
        if (gZT_Printer->user.font->charset == NULL) {ZTK_FontCharsetNew(gZT_Printer->user.font);}
    }
}
void ZTK_PrinterSetBounds(const ZT_RECT* iBounds) {
    if (gZT_Printer != NULL) {
        if (iBounds != NULL) {
            ZTM_RectCopy(iBounds, &(gZT_Printer->user.bounds));
        } else {
            ZTM_RectZeroPos(&(gZT_Printer->user.bounds));
            ZTM_RectCopySize(&(gZT_Window->rect), &(gZT_Printer->user.bounds));
        }
        ZTK_PrinterSetCursor(NULL);
    }
}
void ZTK_PrinterSetCursor(const ZT_POINT* iPosition) {
    if (gZT_Printer != NULL) {
        if (iPosition != NULL) {ZTM_PointCopy(iPosition, &(gZT_Printer->user.cursor));} else {ZTM_PointZero(&(gZT_Printer->user.cursor));}
    }
}
void ZTK_PrintPos(const ZT_POINT* iPos) {
    if (gZT_Printer != NULL) {
        if (iPos != NULL) {
            gZT_Printer->user.cursor.x = iPos->x;
            gZT_Printer->user.cursor.y = iPos->y;
        } else {
            gZT_Printer->user.cursor.x = 0;
            gZT_Printer->user.cursor.y = 0;
        }
    }
}
void ZTK_PrintPosFromInteger(ZT_I iX, ZT_I iY) {
    if (gZT_Printer != NULL) {
        gZT_Printer->user.cursor.x = iX;
        gZT_Printer->user.cursor.y = iY;
    }
}
void ZTK_PrintPosX(ZT_I iX) {
    if (gZT_Printer != NULL) {
        gZT_Printer->user.cursor.x = iX;
    }
}
void ZTK_PrintPosY(ZT_I iY) {
    if (gZT_Printer != NULL) {
        gZT_Printer->user.cursor.y = iY;
    }
}
void ZTK_PrintPosRelative(ZT_DBL iX, ZT_DBL iY) {
    if (gZT_Printer != NULL) {
        gZT_Printer->user.cursor.x = iX * gZT_Printer->user.bounds.w;
        gZT_Printer->user.cursor.y = iY * gZT_Printer->user.bounds.h;
    }
}
void ZTK_PrintPosXRelative(ZT_DBL iX) {
    if (gZT_Printer != NULL) {
        gZT_Printer->user.cursor.x = iX * gZT_Printer->user.bounds.w;
    }
}
void ZTK_PrintPosYRelative(ZT_DBL iY) {
    if (gZT_Printer != NULL) {
        gZT_Printer->user.cursor.y = iY * gZT_Printer->user.bounds.h;
    }
}
void ZTK_PrinterPipe(ZT_PNT_HOST_PARAMS* iUser) {
    if (gZT_Printer != NULL) {
        if (gZT_Printer->print.buffer != NULL) {
            ZT_PNT_HOST_PARAMS lCopy;
            ZT_PNT_HOST_PARAMS* lPrint = (iUser != NULL) ? iUser : &(gZT_Printer->user);
            switch (gZT_Printer->type) {
                case ZTK_PRINTER_TYPE_SPRITE:
                case ZTK_PRINTER_TYPE_SYSTEM:
                    if (gZT_Printer->flag & ZTK_PRINTER_FLAG_SIZE) {
                        ZTM_RectZero(&(gZT_Printer->print.rect));
                        lCopy = *lPrint;
                        lPrint = &lCopy;
                    } else {
                        gZT_Printer->print.rect.x = lPrint->bounds.x + lPrint->cursor.x;
                        gZT_Printer->print.rect.y = lPrint->bounds.y + lPrint->cursor.y;
                        ZTM_RectZeroSize(&(gZT_Printer->print.rect));
                    }
                    ZTK_PrinterPipeLoop(lPrint, gZT_Printer->print.buffer);
                    return;
                default:
                    printf((const char*)gZT_Printer->print.buffer);
                    return;
            }
        }
    }
}
void ZTK_PrinterPipeLoop(ZT_PNT_HOST_PARAMS* iUser, ZT_CHAR* iText) {
    if (gZT_Printer != NULL && iText != NULL) {
        ZT_INDEX lLine = 0;
        ZT_INDEX lIndex = (~0);
        while (((++lIndex) < ZTK_PRINTER_BUFFER) && (iText[lIndex] != ZTM_CHAR_NT)) {
            if (iText[lIndex] == ZTM_CHAR_LF) {
                if (lIndex - lLine) {ZTK_PrinterPipeLine(iUser, &(iText[lLine]), (lIndex - lLine));}
                ZTK_PrinterPipeFeed(iUser);
                lLine = lIndex;
            }
        }
        if (lIndex - lLine) {ZTK_PrinterPipeLine(iUser, &(iText[lLine]), (lIndex - lLine));}
    }
}
void ZTK_PrinterPipeLine(ZT_PNT_HOST_PARAMS* iUser, ZT_CHAR* iText, ZT_INDEX iLength) {
    if (gZT_Printer != NULL && iUser != NULL && iText != NULL) {
        ZT_RECT lRect;
        ZT_INDEX lLength = iLength ? iLength : ZTC8_GetLength(iText);
        if (lLength) {
            switch (gZT_Printer->type) {
                case ZTK_PRINTER_TYPE_SPRITE:
                    if (iUser->font->charset != NULL) {
                        gZT_Printer->print.rect.h += iUser->font->height;
                        lRect.x = iUser->bounds.x + iUser->cursor.x;
                        lRect.y = iUser->bounds.y + iUser->cursor.y;
                        ZT_INDEX lIndex = (~0);
                        while (++lIndex < lLength) {
                            ZT_SPRITE* lSprite = ((ZT_SPRITE**)iUser->font->charset)[(iText[lIndex] & ZTM_CHAR_MASK)];
                            if (lSprite != NULL) {
                                lRect.w = lSprite->block.x;
                                lRect.h = lSprite->block.y;
                                if (!(gZT_Printer->flag & ZTK_PRINTER_FLAG_SIZE)) {ZTK_DrawSprite(lSprite, &lRect);}
                                lRect.x += lRect.w;
                            }
                        }
                        if ((lRect.x - (iUser->bounds.x + iUser->cursor.x)) > gZT_Printer->print.rect.w) {gZT_Printer->print.rect.w = lRect.x - (iUser->bounds.x + iUser->cursor.x);}
                        iUser->cursor.x = lRect.x - iUser->bounds.x;
                    }
                    return;
                case ZTK_PRINTER_TYPE_SYSTEM: {
                        ZT_CHAR* lCopy = NULL;
                        if ((lCopy = ZTC8_CopyLength(iText, lLength)) != NULL) {
                            ZTK_GetDrawTextSize(lCopy, ((ZT_POINT*)&(lRect.w)));
                            lRect.x = iUser->cursor.x + iUser->bounds.x;
                            lRect.y = iUser->cursor.y + iUser->bounds.y;
                            if (lRect.w > iUser->bounds.w) {lRect.w = iUser->bounds.w;}
                            if (lRect.h > iUser->bounds.h) {lRect.h = iUser->bounds.h;}
                            ZTK_DrawText(lCopy, &lRect);
                            iUser->cursor.x += lRect.w;
                            ZTM8_Free(lCopy);
                        }
                    }
                    return;
                default:
                    return;
            }
        }
    }
}
void ZTK_PrinterPipeFeed(ZT_PNT_HOST_PARAMS* iUser) {
    if (gZT_Printer != NULL && iUser != NULL) {
        switch (gZT_Printer->type) {
            case ZTK_PRINTER_TYPE_SPRITE:
                iUser->cursor.y += iUser->font->height;
                if (gZT_Printer->flag & ZTK_PRINTER_FLAG_OVERFLOW) {if (iUser->cursor.y > iUser->bounds.h) {iUser->cursor.y = 0;}}
                iUser->cursor.x = 0;
                return;
            case ZTK_PRINTER_TYPE_SYSTEM:
                iUser->cursor.y += gZT_Window->user.font->height;
                if (gZT_Printer->flag & ZTK_PRINTER_FLAG_OVERFLOW) {if (iUser->cursor.y > iUser->bounds.h) {iUser->cursor.y = 0;}}
                iUser->cursor.x = 0;
                return;
            default:
                return;
        }
    }
}

#endif // ZTK_PRINTER_C_INCLUDED
