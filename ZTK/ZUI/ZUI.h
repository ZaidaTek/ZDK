/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_H_INCLUDED
#define ZUI_H_INCLUDED

#include "../ZTK.h"

#include "ZUI/ZUI__Defines.h"
#include "ZUI/ZUI__Defaults.h"

typedef struct {
    ZT_COLOR background;
	ZT_COLOR foreground;
	ZT_COLOR border;
} ZUI_COLOR;

typedef void ZUI_ELEMENT;

#include "ZUI_Button.h"
#include "ZUI_Box.h"
#include "ZUI_Label.h"
#include "ZUI_Counter.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZUI_HostFree(void);
void ZUI_HostNew(void);
void ZUI_HostDraw(void);
ZT_INDEX ZUI_HostPoll(const ZT_EVENT* iEvent, ZT_EVENT** oGUIEvent);

ZT_COLOR ZUI_HostGetRandomColor(void);
ZT_COLOR ZUI_HostGetJuicyColor(void);

ZT_BOOL ZUI_IsEnabled(ZUI_ELEMENT* iElement);
ZT_BOOL ZUI_IsDisabled(ZUI_ELEMENT* iElement);
ZT_BOOL ZUI_IsVisible(ZUI_ELEMENT* iElement);
ZT_BOOL ZUI_IsHidden(ZUI_ELEMENT* iElement);
ZT_BOOL ZUI_IsIgnored(ZUI_ELEMENT* iElement);
ZT_BOOL ZUI_IsIncluded(ZUI_ELEMENT* iElement);
ZT_BOOL ZUI_IsBuried(ZUI_ELEMENT* iElement);
ZT_BOOL ZUI_IsRestored(ZUI_ELEMENT* iElement);

void ZUI_Enable(ZUI_ELEMENT* iElement);
void ZUI_Disable(ZUI_ELEMENT* iElement); // visible, but doesn't generate click events
void ZUI_Show(ZUI_ELEMENT* iElement);
void ZUI_Hide(ZUI_ELEMENT* iElement); // invisible, but generates all events
void ZUI_Ignore(ZUI_ELEMENT* iElement); // visible, but no events generated
void ZUI_Include(ZUI_ELEMENT* iElement);
void ZUI_Bury(ZUI_ELEMENT* iElement); // both invisible and event-less
void ZUI_Restore(ZUI_ELEMENT* iElement);

void ZUI_Update(ZUI_ELEMENT* iElement); // TEMPORARY workaround to hide/show ZUI element to reflect changes to data/etc...

ZT_INDEX ZUI_GetBorderSize(ZUI_ELEMENT* iElement);
ZT_I ZUI_GetX(ZUI_ELEMENT* iElement);
ZT_I ZUI_GetY(ZUI_ELEMENT* iElement);
ZT_I ZUI_GetXCenter(ZUI_ELEMENT* iElement);
ZT_I ZUI_GetYCenter(ZUI_ELEMENT* iElement);
ZT_I ZUI_GetXRight(ZUI_ELEMENT* iElement);
ZT_I ZUI_GetYBottom(ZUI_ELEMENT* iElement);
ZT_I ZUI_GetWidth(ZUI_ELEMENT* iElement);
ZT_I ZUI_GetHeight(ZUI_ELEMENT* iElement);
const ZT_RECT* ZUI_GetRect(ZUI_ELEMENT* iElement);
const ZT_FONT* ZUI_GetFont(ZUI_ELEMENT* iElement);
const ZUI_COLOR* ZUI_GetColor(ZUI_ELEMENT* iElement, ZT_FLAG iUIS);
const void* ZUI_GetSource(ZUI_ELEMENT* iElement, ZT_FLAG iUIS);
ZT_FLAG ZUI_GetDataValue(ZUI_ELEMENT* iElement);

ZUI_ELEMENT* ZUI_DataValue(ZUI_ELEMENT* iElement, ZT_FLAG iValue);
ZUI_ELEMENT* ZUI_DataMaximum(ZUI_ELEMENT* iElement, ZT_FLAG iMaximum);
ZUI_ELEMENT* ZUI_DataMinimum(ZUI_ELEMENT* iElement, ZT_FLAG iMinimum);
ZUI_ELEMENT* ZUI_DataUnit(ZUI_ELEMENT* iElement, ZT_FLAG iUnit);

ZUI_ELEMENT* ZUI_X(ZUI_ELEMENT* iElement, ZT_I iX);
ZUI_ELEMENT* ZUI_Y(ZUI_ELEMENT* iElement, ZT_I iY);
ZUI_ELEMENT* ZUI_Pos(ZUI_ELEMENT* iElement, const ZT_POINT* iPos);
ZUI_ELEMENT* ZUI_PosFromInteger(ZUI_ELEMENT* iElement, ZT_I iX, ZT_I iY);
ZUI_ELEMENT* ZUI_XCenter(ZUI_ELEMENT* iElement, ZT_I iX);
ZUI_ELEMENT* ZUI_YCenter(ZUI_ELEMENT* iElement, ZT_I iY);
ZUI_ELEMENT* ZUI_PosCenter(ZUI_ELEMENT* iElement, const ZT_POINT* iPos);
ZUI_ELEMENT* ZUI_PosCenterFromInteger(ZUI_ELEMENT* iElement, ZT_I iX, ZT_I iY);
ZUI_ELEMENT* ZUI_Width(ZUI_ELEMENT* iElement, ZT_I iWidth);
ZUI_ELEMENT* ZUI_Height(ZUI_ELEMENT* iElement, ZT_I iHeight);
ZUI_ELEMENT* ZUI_Size(ZUI_ELEMENT* iElement, const ZT_POINT* iSize);
ZUI_ELEMENT* ZUI_SizeFromInteger(ZUI_ELEMENT* iElement, ZT_I iWidth, ZT_I iHeight);
ZUI_ELEMENT* ZUI_Rect(ZUI_ELEMENT* iElement, const ZT_RECT* iRect);

ZUI_ELEMENT* ZUI_XRelative(ZUI_ELEMENT* iElement, ZT_DBL iX);
ZUI_ELEMENT* ZUI_YRelative(ZUI_ELEMENT* iElement, ZT_DBL iY);
ZUI_ELEMENT* ZUI_PosRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY);
ZUI_ELEMENT* ZUI_XCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iX);
ZUI_ELEMENT* ZUI_YCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iY);
ZUI_ELEMENT* ZUI_PosCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY);
ZUI_ELEMENT* ZUI_WidthRelative(ZUI_ELEMENT* iElement, ZT_DBL iWidth);
ZUI_ELEMENT* ZUI_HeightRelative(ZUI_ELEMENT* iElement, ZT_DBL iHeight);
ZUI_ELEMENT* ZUI_SizeRelative(ZUI_ELEMENT* iElement, ZT_DBL iWidth, ZT_DBL iHeight);
ZUI_ELEMENT* ZUI_RectRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY, ZT_DBL iWidth, ZT_DBL iHeight);
ZUI_ELEMENT* ZUI_RectCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY, ZT_DBL iWidth, ZT_DBL iHeight);

ZUI_ELEMENT* ZUI_Font(ZUI_ELEMENT* iElement, ZT_FONT* iFont); // TODO: shouldn't this recreate sprites?
ZUI_ELEMENT* ZUI_BorderSize(ZUI_ELEMENT* iElement, ZT_INDEX iBorderSize); // TODO: shouldn't this recreate sprites?
ZUI_ELEMENT* ZUI_Source(ZUI_ELEMENT* iElement, ZT_FLAG iUIS, const void* iSource);
ZUI_ELEMENT* ZUI_Color(ZUI_ELEMENT* iElement, ZT_FLAG iUIS, const ZUI_COLOR* iColor);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZUI_H_INCLUDED
