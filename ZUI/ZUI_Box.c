/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_BOX_C_INCLUDED
#define ZUI_BOX_C_INCLUDED

#include "ZUI__Runtime.h"

void ZUI_BoxColors(rZUI_ELEMENT* iBox, ZT_COLOR iFill, ZT_COLOR iBorder) {
	ZUI_COLOR lColor;
	lColor.background = iFill;
	lColor.foreground = ZUI_COLOR_TRANSPARENT;
	lColor.border = iBorder;
	ZUI_UIColor(iBox, iBox->UI.draw, &lColor);
}
ZUI_BOX* ZUI_BoxNew(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_COLOR iFill, ZT_COLOR iBorder) {
    rZUI_ELEMENT* lElement = ZUI_ElementNew(iSID, ZUI_ELEMENT_TYPE_BOX, iRect);
    lElement->UI.type = ZUI_UI_TYPE_GENERIC;
    lElement->UI.draw = ZUI_UI_DRAW_NONINTERACTIVE;
    lElement->UI.border = ZUI_DEFAULT_BOX_BORDER_SIZE;
    lElement->UI.font = *rZUI_RTime.system.fontUser;
    ZUI_UINew(lElement, NULL);
    ZUI_BoxColors(lElement, iFill, iBorder);
    ZUI_UISpritesNew(lElement);
    return (ZUI_BOX*)lElement;
}

#endif // ZUI_BOX_C_INCLUDED
