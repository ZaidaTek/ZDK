/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_LABEL_C_INCLUDED
#define ZUI_LABEL_C_INCLUDED

#include "ZUI__Runtime.h"

void ZUI_LabelColors(rZUI_ELEMENT* iLabel, ZT_COLOR iColor) {
    ZUI_COLOR lColor;
    lColor.background = ZUI_COLOR_TRANSPARENT;
    lColor.foreground = iColor;
    lColor.border = ZUI_COLOR_TRANSPARENT;
    ZUI_UIColor(iLabel, iLabel->UI.draw, &lColor);
}
ZUI_LABEL* ZUI_LabelNewFromFont(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iText, ZT_FONT* iFont) {
    rZUI_ELEMENT* lElement = ZUI_ElementNew(iSID, ZUI_ELEMENT_TYPE_LABEL, iRect);
    lElement->UI.type = ZUI_UI_TYPE_GENERIC;
    lElement->UI.draw = ZUI_UI_DRAW_NONINTERACTIVE;
    lElement->UI.border = ZUI_DEFAULT_LABEL_BORDER_SIZE;
    lElement->UI.font = iFont;
    ZUI_UINew(lElement, iText);
    ZUI_LabelColors(lElement, lElement->UI.font->color);
    ZUI_UISpritesNew(lElement);
    return (ZUI_LABEL*)lElement;
}
ZUI_LABEL* ZUI_LabelNew(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iText) {return ZUI_LabelNewFromFont(iSID, iRect, iText, *rZUI_RTime.system.fontUser);}

#endif // ZUI_LABEL_C_INCLUDED
