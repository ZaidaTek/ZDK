/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_FONT_C_INCLUDED
#define ZTK_FONT_C_INCLUDED

#include "ZTK-RT.h"

#define mZTK_FONTPROPERTY(FONT,PROPERTY,VALUE) rZT_FONT* lFont = ZTK_FONTGET(FONT); lFont->PROPERTY = (VALUE); ZTK_FontReload(lFont)
void ZTK_FontColor(ZT_FONT* iFont, ZT_COLOR iColor) {mZTK_FONTPROPERTY(iFont, color, iColor);}
void ZTK_FontColorBk(ZT_FONT* iFont, ZT_COLOR iColor) {mZTK_FONTPROPERTY(iFont, colorBk, iColor);}
void ZTK_FontSize(ZT_FONT* iFont, ZT_INDEX iSize) {mZTK_FONTPROPERTY(iFont, height, iSize);}
void ZTK_FontStyle(ZT_FONT* iFont, ZT_FLAG iStyle) {mZTK_FONTPROPERTY(iFont, style, iStyle);}
#undef mZTK_FONTPROPERTY
ZT_FONT* ZTK_FontNew(const ZT_CHAR* iSource, const ZT_CHAR* iName, ZT_I iHeight, ZT_FLAG iStyle, ZT_COLOR iColor) {
    rZT_FONT* lFont = ZTM8_New(sizeof(rZT_FONT));
    lFont->flag = ZTK_FLAG_NONE;
    lFont->type = ((lFont->source = (iSource != NULL) ? ZTC8_Copy(iSource) : NULL) != NULL) ? ZTK_FONT_TYPE_TTF : ZTK_FONT_TYPE_NONE;
    lFont->name = (iName != NULL) ? ZTC8_Copy(iName) : NULL;
    lFont->height = iHeight;
    lFont->style = iStyle;
    lFont->color = iColor;
    lFont->colorBk = ZTM_ColorComplementary(iColor);
    lFont->runtime = NULL;
    lFont->charset = NULL;
    return lFont;
}
void ZTK_FontSet(ZT_FONT* iFont) {
    rZTK_Host.user.font = (iFont != NULL) ? iFont : rZTK_Host.system.font;
    ZTK_RuntimeFontWindow();
}
void ZTK_FontSourceFree(rZT_FONT* iFont) {
    if (iFont->flag & ZTK_FONT_FLAG_HAVE_SOURCE) {
        ZTK_RuntimeFontSourceFree(iFont);
        iFont->flag &= ~ZTK_FONT_FLAG_HAVE_SOURCE;
    }
}
void ZTK_FontRuntimeFree(rZT_FONT* iFont) {
    if (iFont->flag & ZTK_FONT_FLAG_HAVE_RUNTIME) {
        ZTK_RuntimeFontRuntimeFree(iFont);
        iFont->flag &= ~ZTK_FONT_FLAG_HAVE_RUNTIME;
    }
}
void ZTK_FontCharsetFree(rZT_FONT* iFont) {
    if (iFont->flag & ZTK_FONT_FLAG_HAVE_CHARSET) {
        for (ZT_INDEX i = 0; i < ZTK_CHARSET_LENGTH; i++) {ZTK_SpriteFree(iFont->charset[i]);}
        ZTM8_Free(iFont->charset);
        iFont->flag &= ~ZTK_FONT_FLAG_HAVE_CHARSET;
    }
}
void ZTK_FontSourceLoad(rZT_FONT* iFont) {
    ZTK_RuntimeFontSourceLoad(iFont);
    iFont->flag |= ZTK_FONT_FLAG_HAVE_SOURCE;
}
void ZTK_FontRuntimeLoad(rZT_FONT* iFont) {
    ZTK_RuntimeFontRuntimeLoad(iFont);
    iFont->flag |= ZTK_FONT_FLAG_HAVE_RUNTIME;
}
void ZTK_FontCharsetLoad(rZT_FONT* iFont) {
    iFont->charset = (void**)ZTM8_New(sizeof(ZT_SPRITE*) * ZTK_CHARSET_LENGTH);
    ZT_CHAR lChar[2];
    lChar[1] = ZTM_CHAR_NT;
    for (ZT_INDEX i = 0; i < ZTK_CHARSET_LENGTH; i++) {
        lChar[0] = i & ZTK_CHARSET_MASK;
        iFont->charset[i] = ZTK_SpriteFromFont(lChar, iFont);
    }
    iFont->flag |= ZTK_FONT_FLAG_HAVE_CHARSET;
}
void ZTK_FontLoad(rZT_FONT* iFont) {
    if (!(iFont->flag & ZTK_FONT_FLAG_HAVE_SOURCE)) {ZTK_FontSourceLoad(iFont);}
    if (!(iFont->flag & ZTK_FONT_FLAG_HAVE_RUNTIME)) {ZTK_FontRuntimeLoad(iFont);}
}
void ZTK_FontReload(rZT_FONT* iFont) {
    ZTK_FontRuntimeFree(iFont);
    if (iFont->flag & ZTK_FONT_FLAG_HAVE_CHARSET) {ZTK_FontCharsetFree(iFont); ZTK_FontCharsetLoad(iFont);}
}
void ZTK_FontCharset(rZT_FONT* iFont) {
    if (!(iFont->flag & ZTK_FONT_FLAG_HAVE_CHARSET)) {ZTK_FontCharsetLoad(iFont);}
}
void ZTK_FontFree(ZT_FONT* iFont) {
    rZT_FONT* lFont = iFont;
    ZTK_FontCharsetFree(lFont);
    ZTK_FontRuntimeFree(lFont);
    ZTK_FontSourceFree(lFont);
    ZTM8_Free(lFont->name);
    ZTM8_Free(lFont->source);
    ZTM8_Free(lFont);
}
#endif // ZTK_FONT_C_INCLUDED
