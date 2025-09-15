/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_FONT_H_INCLUDED
#define ZTK_FONT_H_INCLUDED

#define ZTK_FONT_STYLE_NORMAL ZTM_TEXT_STYLE_NORMAL
#define ZTK_FONT_STYLE_BOLD ZTM_TEXT_STYLE_BOLD
#define ZTK_FONT_STYLE_ITALIC ZTM_TEXT_STYLE_ITALIC
#define ZTK_FONT_STYLE_UNDERLINE ZTM_TEXT_STYLE_UNDERLINE
#define ZTK_FONT_STYLE_STRIKEOUT ZTM_TEXT_STYLE_STRIKEOUT
#define ZTK_FONT_STYLE_ALIGN_RIGHT ZTM_TEXT_STYLE_ALIGN_RIGHT
#define ZTK_FONT_STYLE_ALIGN_CENTER ZTM_TEXT_STYLE_ALIGN_CENTER
#define ZTK_FONT_STYLE_VALIGN_BOTTOM ZTM_TEXT_STYLE_VALIGN_BOTTOM
#define ZTK_FONT_STYLE_VALIGN_CENTER ZTM_TEXT_STYLE_VALIGN_CENTER
#define ZTK_FONT_STYLE_SINGLE_LINE ZTM_TEXT_STYLE_SINGLE_LINE
#define ZTK_FONT_STYLE_BREAK_WORDS ZTM_TEXT_STYLE_BREAK_WORDS
#define ZTK_FONT_STYLE_OPAQUE ZTM_TEXT_STYLE_OPAQUE
#define ZTK_FONT_STYLE_CLIP ZTM_TEXT_STYLE_CLIP

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTK_FontFree(ZT_FONT* iFont);
ZT_FONT* ZTK_FontNew(const ZT_CHAR* iSource, const ZT_CHAR* iName, ZT_I iHeight, ZT_FLAG iStyle, ZT_COLOR iColor);
void ZTK_FontSet(ZT_FONT* iFont);
void ZTK_FontColor(ZT_FONT* iFont, ZT_COLOR iColor);
void ZTK_FontColorBk(ZT_FONT* iFont, ZT_COLOR iColor);
void ZTK_FontSize(ZT_FONT* iFont, ZT_INDEX iSize);
void ZTK_FontStyle(ZT_FONT* iFont, ZT_FLAG iStyle);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZTK_FONT_H_INCLUDED
