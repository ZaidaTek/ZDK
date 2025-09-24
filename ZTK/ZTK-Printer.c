/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_PRINTER_C_INCLUDED
#define ZTK_PRINTER_C_INCLUDED

#include "ZTK-RT.h"
#include <stdio.h>
#include <stdarg.h>

void ZTK_Print(const void* iText, ...) {
	va_list lList;
	va_start(lList, (const char*)iText);
	vsnprintf((char*)rZTK_PrinterHost.print.buffer, ZTK_PRINTER_BUFFER - 1, (const char*)iText, lList);
	va_end(lList);
	ZTK_PrinterPipe(&(rZTK_PrinterHost.user));
}
void ZTK_PrintBufferLoad(const void* iText, ...) {
	va_list lList;
	va_start(lList, (const char*)iText);
	vsnprintf((char*)rZTK_PrinterHost.print.buffer, ZTK_PRINTER_BUFFER - 1, (const char*)iText, lList);
	va_end(lList);
}
void ZTK_PrintBufferGetSize(ZT_RECT* oSize) {
	rZTK_PrinterHost.flag |= ZTK_PRINTER_FLAG_SIZE;
	ZTK_PrinterPipe(&(rZTK_PrinterHost.user));
	if (oSize != NULL) {*oSize = rZTK_PrinterHost.print.rect;}
	rZTK_PrinterHost.flag &= ~ZTK_PRINTER_FLAG_SIZE;
}
void ZTK_PrintBuffer(void) {ZTK_PrinterPipe(&(rZTK_PrinterHost.user));}
void ZTK_PrintBufferGetCustomSize(ZT_FONT* iFont, const ZT_POINT* iCursor, const ZT_RECT* iBounds, ZT_RECT* oSize) {
	rZTK_PRINTER lPrint;
	lPrint.font = (iFont != NULL) ? iFont : rZTK_PrinterHost.user.font;
	lPrint.cursor = (iCursor != NULL) ? *iCursor : rZTK_PrinterHost.user.cursor;
	lPrint.bounds = (iBounds != NULL) ? *iBounds : rZTK_PrinterHost.user.bounds;
	rZTK_PrinterHost.flag |= ZTK_PRINTER_FLAG_SIZE;
	ZTK_PrinterPipe(&lPrint);
	if (oSize != NULL) {*oSize = rZTK_PrinterHost.print.rect;}
	rZTK_PrinterHost.flag &= ~ZTK_PRINTER_FLAG_SIZE;
}
void ZTK_PrintBufferCustom(ZT_FONT* iFont, const ZT_POINT* iCursor, const ZT_RECT* iBounds) {
	rZTK_PRINTER lPrint;
	lPrint.font = (iFont != NULL) ? iFont : rZTK_PrinterHost.user.font;
	lPrint.cursor = (iCursor != NULL) ? *iCursor : rZTK_PrinterHost.user.cursor;
	lPrint.bounds = (iBounds != NULL) ? *iBounds : rZTK_PrinterHost.user.bounds;
	ZTK_PrinterPipe(&lPrint);
}
void ZTK_PrinterInit(ZT_FONT* iFont) {
	rZTK_PrinterHost.flag = ZTK_DEFAULT_PRINTER_FLAG;
	rZTK_PrinterHost.type = ZTK_PRINTER_TYPE_SPRITE;
	rZTK_PrinterHost.print.buffer[ZTK_PRINTER_BUFFER - 1] = ZTM_CHAR_NT;
	ZTK_PrinterSet(iFont);
	ZTK_PrinterSetBounds(NULL);
}
void ZTK_PrinterQuit(void) {}
void ZTK_PrinterSet(ZT_FONT* iFont) {
	ZTK_FontCharset(rZTK_PrinterHost.user.font = ZTK_FONTGET(iFont));
}
void ZTK_PrinterSetBounds(const ZT_RECT* iBounds) {
	if (iBounds != NULL) {
		ZTM_RectCopy(iBounds, &(rZTK_PrinterHost.user.bounds));
	} else {
		ZTM_RectZeroPos(&(rZTK_PrinterHost.user.bounds));
		ZTM_RectCopySize(&(rZTK_Host.rect), &(rZTK_PrinterHost.user.bounds));
	}
	ZTK_PrinterSetCursor(NULL);
}
void ZTK_PrinterSetCursor(const ZT_POINT* iPosition) {
	if (iPosition != NULL) {ZTM_PointCopy(iPosition, &(rZTK_PrinterHost.user.cursor));} else {ZTM_PointZero(&(rZTK_PrinterHost.user.cursor));}
}
void ZTK_PrintPos(const ZT_POINT* iPos) {
	if (iPos != NULL) {
		rZTK_PrinterHost.user.cursor.x = iPos->x;
		rZTK_PrinterHost.user.cursor.y = iPos->y;
	} else {
		rZTK_PrinterHost.user.cursor.x = 0;
		rZTK_PrinterHost.user.cursor.y = 0;
	}
}
void ZTK_PrintPosFromInteger(ZT_I iX, ZT_I iY) {
	rZTK_PrinterHost.user.cursor.x = iX;
	rZTK_PrinterHost.user.cursor.y = iY;
}
void ZTK_PrintPosX(ZT_I iX) {rZTK_PrinterHost.user.cursor.x = iX;}
void ZTK_PrintPosY(ZT_I iY) {rZTK_PrinterHost.user.cursor.y = iY;}
void ZTK_PrintPosRelative(ZT_DBL iX, ZT_DBL iY) {
	rZTK_PrinterHost.user.cursor.x = iX * rZTK_PrinterHost.user.bounds.w;
	rZTK_PrinterHost.user.cursor.y = iY * rZTK_PrinterHost.user.bounds.h;
}
void ZTK_PrintPosXRelative(ZT_DBL iX) {rZTK_PrinterHost.user.cursor.x = iX * rZTK_PrinterHost.user.bounds.w;}
void ZTK_PrintPosYRelative(ZT_DBL iY) {rZTK_PrinterHost.user.cursor.y = iY * rZTK_PrinterHost.user.bounds.h;}
void ZTK_PrinterPipe(rZTK_PRINTER* iUser) {
	rZTK_PRINTER lCopy;
	switch (rZTK_PrinterHost.type) {
		case ZTK_PRINTER_TYPE_SPRITE:
		case ZTK_PRINTER_TYPE_SYSTEM:
			if (rZTK_PrinterHost.flag & ZTK_PRINTER_FLAG_SIZE) {
				ZTM_RectZero(&(rZTK_PrinterHost.print.rect));
				lCopy = *iUser;
				iUser = &lCopy;
			} else {
				rZTK_PrinterHost.print.rect.x = iUser->bounds.x + iUser->cursor.x;
				rZTK_PrinterHost.print.rect.y = iUser->bounds.y + iUser->cursor.y;
				ZTM_RectZeroSize(&(rZTK_PrinterHost.print.rect));
			}
			ZTK_PrinterPipeLoop(iUser, rZTK_PrinterHost.print.buffer);
			return;
		default:
			printf((const char*)rZTK_PrinterHost.print.buffer);
			return;
	}
}
void ZTK_PrinterPipeLoop(rZTK_PRINTER* iUser, ZT_CHAR* iText) {
	ZT_INDEX lLine = 0;
	ZT_INDEX lIndex = -1;
	while (((++lIndex) < ZTK_PRINTER_BUFFER) && (iText[lIndex] != ZTM_CHAR_NT)) {
		if (iText[lIndex] == ZTM_CHAR_LF) {
			if (lIndex - lLine) {ZTK_PrinterPipeLine(iUser, &(iText[lLine]), (lIndex - lLine));}
			ZTK_PrinterPipeFeed(iUser);
			lLine = lIndex;
		}
	}
	if (lIndex - lLine) {ZTK_PrinterPipeLine(iUser, &(iText[lLine]), (lIndex - lLine));}
}
void ZTK_PrinterPipeLine(rZTK_PRINTER* iUser, ZT_CHAR* iText, ZT_INDEX iLength) {
	ZT_RECT lRect;
	ZT_INDEX lLength = iLength ? iLength : ZTC8_GetLength(iText);
	if (lLength) {
		switch (rZTK_PrinterHost.type) {
			case ZTK_PRINTER_TYPE_SPRITE: {
					rZTK_PrinterHost.print.rect.h += iUser->font->height;
					lRect.x = iUser->bounds.x + iUser->cursor.x;
					lRect.y = iUser->bounds.y + iUser->cursor.y;
					ZT_INDEX lIndex = -1;
					while (++lIndex < lLength) {
						rZT_SPRITE* lSprite = ((ZT_SPRITE**)iUser->font->charset)[(iText[lIndex] & ZTK_CHARSET_MASK)];
						if (lSprite != NULL) {
							lRect.w = lSprite->block.x;
							lRect.h = lSprite->block.y;
							if (!(rZTK_PrinterHost.flag & ZTK_PRINTER_FLAG_SIZE)) {ZTK_DrawSprite(lSprite, &lRect);}
							lRect.x += lRect.w;
						}
					}
					if ((lRect.x - (iUser->bounds.x + iUser->cursor.x)) > rZTK_PrinterHost.print.rect.w) {rZTK_PrinterHost.print.rect.w = lRect.x - (iUser->bounds.x + iUser->cursor.x);}
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
						ZTK_DrawTextDelete(lCopy, &lRect);
						iUser->cursor.x += lRect.w;
					}
				}
				return;
			default:
				return;
		}
	}
}
void ZTK_PrinterPipeFeed(rZTK_PRINTER* iUser) {
	switch (rZTK_PrinterHost.type) {
		case ZTK_PRINTER_TYPE_SPRITE:
			iUser->cursor.y += iUser->font->height;
			if (rZTK_PrinterHost.flag & ZTK_PRINTER_FLAG_OVERFLOW) {if (iUser->cursor.y > iUser->bounds.h) {iUser->cursor.y = 0;}}
			iUser->cursor.x = 0;
			return;
		case ZTK_PRINTER_TYPE_SYSTEM:
			iUser->cursor.y += rZTK_Host.user.font->height;
			if (rZTK_PrinterHost.flag & ZTK_PRINTER_FLAG_OVERFLOW) {if (iUser->cursor.y > iUser->bounds.h) {iUser->cursor.y = 0;}}
			iUser->cursor.x = 0;
			return;
		default:
			return;
	}
}

#endif // ZTK_PRINTER_C_INCLUDED
