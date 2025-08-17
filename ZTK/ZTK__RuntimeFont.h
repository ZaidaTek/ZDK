/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__RUNTIMEFONT_H_INCLUDED
#define ZTK__RUNTIMEFONT_H_INCLUDED

#include "ZTK__Runtime.h"

#define ZTK_CHARSET_MASK ((ZT_CHAR)~0x0)
#define ZTK_CHARSET_LENGTH (((ZT_INDEX)ZTK_CHARSET_MASK) + 1)

#define ZTK_FONT_FLAG_HAVE_SOURCE 0x1
#define ZTK_FONT_FLAG_HAVE_RUNTIME 0x2
#define ZTK_FONT_FLAG_HAVE_CHARSET 0x4

#define ZTK_FONT_TYPE_NONE 0x0
#define ZTK_FONT_TYPE_TTF 0x1

#define ZTK_FONTGET(FONT) (((FONT) != NULL) ? (FONT) : rZTK_Host.user.font)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTK_FontCharset(rZT_FONT* iFont);
void ZTK_FontReload(rZT_FONT *iFont);
void ZTK_FontLoad(rZT_FONT *iFont);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ZTK__RUNTIMEFONT_H_INCLUDED
