/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_LABEL_H_INCLUDED
#define ZUI_LABEL_H_INCLUDED

#include "ZUI.h"

typedef ZUI_ELEMENT ZUI_LABEL;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
ZUI_LABEL* ZUI_LabelNew(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iText);
ZUI_LABEL* ZUI_LabelNewFromFont(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iText, ZT_FONT* iFont);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZUI_LABEL_H_INCLUDED
