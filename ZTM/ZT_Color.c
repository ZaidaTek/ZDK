/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_COLOR_C_INCLUDED
#define ZT_COLOR_C_INCLUDED

#include "ZTM__Runtime.h"

ZT_COLOR ZTM_ColorPaletteConvert(ZT_COLOR iColor, ZT_FLAG iPaletteSource, ZT_FLAG iPaletteTarget) {
    ZT_COLOR lColor = iColor;
    ZTM_PixelsPaletteConversion(&lColor, 1, iPaletteSource, iPaletteTarget);
    return lColor;
}
ZT_BOOL ZTM_ColorPalette(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_0RGB: return ZT_TRUE;
        case ZTM_PALETTE_ARGB: return ZT_TRUE;
        case ZTM_PALETTE_RGBA: return ZT_TRUE;
        case ZTM_PALETTE_ABGR: return ZT_TRUE;
        default: return ZT_FALSE;
    }
}
ZT_COLOR ZTM_ColorComplementary(ZT_COLOR iColor) {
    ZT_COLOR lComp = (((iColor & 0xff) + 0x80) % 0x100);
    lComp |= (((((iColor >> 8) & 0xff) + 0x80) % 0x100) << 8);
    lComp |= (((((iColor >> 16) & 0xff) + 0x80) % 0x100) << 16);
    lComp |= ((((iColor >> 24) + 0x80) % 0x100) << 24);
    return lComp;
}
ZT_COLOR ZTM_ColorMask(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKC;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKC;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKC;
        default: return 0x0;
    }
}
ZT_INDEX ZTM_ColorShift(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTC;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTC;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTC;
        default: return 0;
    }
}
ZT_COLOR ZTM_ColorAlphaMask(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKA;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKA;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKA;
        default: return 0x0;
    }
}
ZT_COLOR ZTM_ColorRedMask(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKR;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKR;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKR;
        default: return 0x0;
    }
}
ZT_COLOR ZTM_ColorGreenMask(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKG;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKG;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKG;
        default: return 0x0;
    }
}
ZT_COLOR ZTM_ColorBlueMask(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKB;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKB;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKB;
        default: return 0x0;
    }
}
ZT_INDEX ZTM_ColorAlphaShift(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTA;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTA;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTA;
        default: return 32;
    }
}
ZT_INDEX ZTM_ColorRedShift(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTR;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTR;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTR;
        default: return 32;
    }
}
ZT_INDEX ZTM_ColorGreenShift(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTG;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTG;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTG;
        default: return 32;
    }
}
ZT_INDEX ZTM_ColorBlueShift(ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTB;
        case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTB;
        case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTB;
        default: return 32;
    }
}
ZT_INDEX ZTM_ColorAlpha(ZT_COLOR iColor, ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return (iColor >> ZTM_PALETTE_ABGR_SHIFTA) & 0xff;
        case ZTM_PALETTE_ARGB: return (iColor >> ZTM_PALETTE_ARGB_SHIFTA) & 0xff;
        case ZTM_PALETTE_RGBA: return (iColor >> ZTM_PALETTE_RGBA_SHIFTA) & 0xff;
        default: return 0x100;
    }
}
ZT_INDEX ZTM_ColorRed(ZT_COLOR iColor, ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return (iColor >> ZTM_PALETTE_ABGR_SHIFTR) & 0xff;
        case ZTM_PALETTE_ARGB: return (iColor >> ZTM_PALETTE_ARGB_SHIFTR) & 0xff;
        case ZTM_PALETTE_RGBA: return (iColor >> ZTM_PALETTE_RGBA_SHIFTR) & 0xff;
        default: return 0x100;
    }
}
ZT_INDEX ZTM_ColorGreen(ZT_COLOR iColor, ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return (iColor >> ZTM_PALETTE_ABGR_SHIFTG) & 0xff;
        case ZTM_PALETTE_ARGB: return (iColor >> ZTM_PALETTE_ARGB_SHIFTG) & 0xff;
        case ZTM_PALETTE_RGBA: return (iColor >> ZTM_PALETTE_RGBA_SHIFTG) & 0xff;
        default: return 0x100;
    }
}
ZT_INDEX ZTM_ColorBlue(ZT_COLOR iColor, ZT_FLAG iPalette) {
    switch (iPalette) {
        case ZTM_PALETTE_ABGR: return (iColor >> ZTM_PALETTE_ABGR_SHIFTB) & 0xff;
        case ZTM_PALETTE_ARGB: return (iColor >> ZTM_PALETTE_ARGB_SHIFTB) & 0xff;
        case ZTM_PALETTE_RGBA: return (iColor >> ZTM_PALETTE_RGBA_SHIFTB) & 0xff;
        default: return 0x100;
    }
}
ZT_INDEX ZTM_ColorBlend(ZT_INDEX iColor, ZT_INDEX iBase, ZT_INDEX iAlpha) {
	return ((iColor * iAlpha + iBase * (0xff - iAlpha) + 0xff) >> 8);
}
ZT_COLOR ZTM_PixelBlend(ZT_COLOR iColor, ZT_COLOR iBase, ZT_FLAG iPalette) {
	if (rZTM_COLOR__PALLETE != iPalette) {
		rZTM_COLOR__SHIFT[0] = ZTM_ColorRedShift(iPalette);
		rZTM_COLOR__SHIFT[1] = ZTM_ColorGreenShift(iPalette);
		rZTM_COLOR__SHIFT[2] = ZTM_ColorBlueShift(iPalette);
		rZTM_COLOR__PALLETE = iPalette;
	}
	ZT_INDEX lAlphaColor = ZTM_ColorAlpha(iColor, iPalette);
    ZT_COLOR lBlend[4];
	lBlend[0] = (ZTM_ColorBlend((iColor >> rZTM_COLOR__SHIFT[0]) & 0xff, (iBase >> rZTM_COLOR__SHIFT[0]) & 0xff, lAlphaColor) << rZTM_COLOR__SHIFT[0]);
	lBlend[1] = (ZTM_ColorBlend((iColor >> rZTM_COLOR__SHIFT[1]) & 0xff, (iBase >> rZTM_COLOR__SHIFT[1]) & 0xff, lAlphaColor) << rZTM_COLOR__SHIFT[1]);
	lBlend[2] = (ZTM_ColorBlend((iColor >> rZTM_COLOR__SHIFT[2]) & 0xff, (iBase >> rZTM_COLOR__SHIFT[2]) & 0xff, lAlphaColor) << rZTM_COLOR__SHIFT[2]);
	lBlend[3] = (lAlphaColor + ((ZTM_ColorAlpha(iBase, iPalette) * (0xff - lAlphaColor) + 0xff) >> 8)) & 0xff;
	return (lBlend[0] | lBlend[1] | lBlend[2] | lBlend[3]);
}

#endif // ZT_COLOR_C_INCLUDED
