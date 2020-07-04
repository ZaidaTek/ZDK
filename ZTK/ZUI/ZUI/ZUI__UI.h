/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI__UI_H_INCLUDED
#define ZUI__UI_H_INCLUDED

#include "ZUI__Runtime.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZUI_UINew(ZUI_HOST_ELEMENT* iElement, const void* iSource);
void ZUI_UIFree(ZUI_HOST_ELEMENT* iElement);
void ZUI_UIZero(ZUI_HOST_ELEMENT* iElement);
void ZUI_UIState(ZUI_HOST_ELEMENT* iElement);
void ZUI_UIColor(ZUI_HOST_ELEMENT* iElement, ZT_FLAG iUIS, const ZUI_COLOR* iColor);
void ZUI_UISource(ZUI_HOST_ELEMENT* iElement, ZT_FLAG iUIS, const ZT_CHAR* iSource);
void ZUI_UISourcesFree(ZUI_HOST_ELEMENT* iElement);
void ZUI_UISourcesNew(ZUI_HOST_ELEMENT* iElement);
void ZUI_UIColorsFree(ZUI_HOST_ELEMENT* iElement);
void ZUI_UIColorsNew(ZUI_HOST_ELEMENT* iElement);
void ZUI_UISpritesFree(ZUI_HOST_ELEMENT* iElement);
void ZUI_UISpritesNew(ZUI_HOST_ELEMENT* iElement);

void ZUI_UIGenericState(ZUI_HOST_ELEMENT* iElement);
ZT_INDEX ZUI_UIGenericGetStateIndex(const ZUI_HOST_ELEMENT_UI* iUI, ZT_FLAG iUIS);
void ZUI_UIGenericColor(ZUI_HOST_ELEMENT_UI* iUI, ZT_FLAG iUIS, const ZUI_COLOR* iColor);
void ZUI_UIGenericSource(ZUI_HOST_ELEMENT_UI* iUI, ZT_FLAG iUIS, const ZT_CHAR* iSource);
void ZUI_UIGenericSourcesNew(ZUI_HOST_ELEMENT_UI* iUI);
void ZUI_UIGenericSourcesFree(ZUI_HOST_ELEMENT_UI* iUI);
void ZUI_UIGenericSpritesNew(ZUI_HOST_ELEMENT_UI* iUI, const ZT_RECT* iRect);
void ZUI_UIGenericSpritesFree(ZUI_HOST_ELEMENT_UI* iUI);
void ZUI_UIGenericColorsNew(ZUI_HOST_ELEMENT_UI* iUI);
void ZUI_UIGenericColorsFree(ZUI_HOST_ELEMENT_UI* iUI);

void ZUI_UIPrintListState(ZUI_HOST_ELEMENT* iElement);
void ZUI_UIPrintListSpritesNew(ZUI_HOST_ELEMENT_UI* iUI, const ZT_RECT* iRect);
void ZUI_UIPrintListSpritesFree(ZUI_HOST_ELEMENT_UI* iUI);

void ZUI_UIDraw(const ZUI_HOST_ELEMENT* iElement);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZUI__UI_H_INCLUDED
