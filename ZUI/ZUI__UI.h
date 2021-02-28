/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI__UI_H_INCLUDED
#define ZUI__UI_H_INCLUDED

#include "ZUI__Runtime.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZUI_UINew(rZUI_ELEMENT* iElement, const void* iSource);
void ZUI_UIFree(rZUI_ELEMENT* iElement);
void ZUI_UIZero(rZUI_ELEMENT* iElement);
void ZUI_UIState(rZUI_ELEMENT* iElement);
void ZUI_UIColor(rZUI_ELEMENT* iElement, ZT_FLAG iUIS, const ZUI_COLOR* iColor);
void ZUI_UISource(rZUI_ELEMENT* iElement, ZT_FLAG iUIS, const ZT_CHAR* iSource);
void ZUI_UISourcesFree(rZUI_ELEMENT* iElement);
void ZUI_UISourcesNew(rZUI_ELEMENT* iElement);
void ZUI_UIColorsFree(rZUI_ELEMENT* iElement);
void ZUI_UIColorsNew(rZUI_ELEMENT* iElement);
void ZUI_UISpritesFree(rZUI_ELEMENT* iElement);
void ZUI_UISpritesNew(rZUI_ELEMENT* iElement);
void ZUI_UISpritesReload(rZUI_ELEMENT* iElement);

void ZUI_UIGenericState(rZUI_ELEMENT* iElement);
ZT_INDEX ZUI_UIGenericGetStateIndex(const rZUI_UI* iUI, ZT_FLAG iUIS);
void ZUI_UIGenericColor(rZUI_UI* iUI, ZT_FLAG iUIS, const ZUI_COLOR* iColor);
void ZUI_UIGenericSource(rZUI_UI* iUI, ZT_FLAG iUIS, const ZT_CHAR* iSource);
void ZUI_UIGenericSourcesNew(rZUI_UI* iUI);
void ZUI_UIGenericSourcesFree(rZUI_UI* iUI);
void ZUI_UIGenericSpritesNew(rZUI_UI* iUI, const ZT_RECT* iRect);
void ZUI_UIGenericSpritesFree(rZUI_UI* iUI);
void ZUI_UIGenericColorsNew(rZUI_UI* iUI);
void ZUI_UIGenericColorsFree(rZUI_UI* iUI);

void ZUI_UIPrintListState(rZUI_ELEMENT* iElement);
void ZUI_UIPrintListSpritesNew(rZUI_UI* iUI, const ZT_RECT* iRect);
void ZUI_UIPrintListSpritesFree(rZUI_UI* iUI);

void ZUI_UIDraw(const rZUI_ELEMENT* iElement);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZUI__UI_H_INCLUDED
