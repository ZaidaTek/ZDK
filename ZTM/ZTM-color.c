/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_COLOR_C_INCLUDED
#define ZTM_COLOR_C_INCLUDED

#include "ZTM-RT.h"

#define ZTM_COLOR_SHIFT_INVALID 0
#define ZTM_COLOR_MASK_INVALID 0xffffffff
#define ZTM_COLOR_CHANNEL_INVALID 255

ZT_COLOR ZTM_ColorConvert(ZT_COLOR iColor, ZT_FLAG iPaletteSource, ZT_FLAG iPaletteTarget) {
	ZT_COLOR lColor = iColor;
	ZTM_PixelsConvert(&lColor, &lColor, 1, iPaletteSource, iPaletteTarget);
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
ZT_COLOR ZTM_ColorMaskC(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKC;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKC;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKC;
		default: return ZTM_COLOR_MASK_INVALID;
	}
}
ZT_COLOR ZTM_ColorMaskA(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKA;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKA;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKA;
		default: return ZTM_COLOR_MASK_INVALID;
	}
}
ZT_COLOR ZTM_ColorMaskR(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKR;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKR;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKR;
		default: return ZTM_COLOR_MASK_INVALID;
	}
}
ZT_COLOR ZTM_ColorMaskG(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKG;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKG;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKG;
		default: return ZTM_COLOR_MASK_INVALID;
	}
}
ZT_COLOR ZTM_ColorMaskB(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_MASKB;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_MASKB;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_MASKB;
		default: return ZTM_COLOR_MASK_INVALID;
	}
}
ZT_INDEX ZTM_ColorShiftC(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTC;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTC;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTC;
		default: return ZTM_COLOR_SHIFT_INVALID;
	}
}
ZT_INDEX ZTM_ColorShiftA(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTA;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTA;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTA;
		default: return ZTM_COLOR_SHIFT_INVALID;
	}
}
ZT_INDEX ZTM_ColorShiftR(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTR;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTR;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTR;
		default: return ZTM_COLOR_SHIFT_INVALID;
	}
}
ZT_INDEX ZTM_ColorShiftG(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTG;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTG;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTG;
		default: return ZTM_COLOR_SHIFT_INVALID;
	}
}
ZT_INDEX ZTM_ColorShiftB(ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return ZTM_PALETTE_ABGR_SHIFTB;
		case ZTM_PALETTE_ARGB: return ZTM_PALETTE_ARGB_SHIFTB;
		case ZTM_PALETTE_RGBA: return ZTM_PALETTE_RGBA_SHIFTB;
		default: return ZTM_COLOR_SHIFT_INVALID;
	}
}
ZT_INDEX ZTM_ColorA(ZT_COLOR iColor, ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return (iColor >> ZTM_PALETTE_ABGR_SHIFTA) & 0xff;
		case ZTM_PALETTE_ARGB: return (iColor >> ZTM_PALETTE_ARGB_SHIFTA) & 0xff;
		case ZTM_PALETTE_RGBA: return (iColor >> ZTM_PALETTE_RGBA_SHIFTA) & 0xff;
		default: return ZTM_COLOR_CHANNEL_INVALID;
	}
}
ZT_INDEX ZTM_ColorR(ZT_COLOR iColor, ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return (iColor >> ZTM_PALETTE_ABGR_SHIFTR) & 0xff;
		case ZTM_PALETTE_ARGB: return (iColor >> ZTM_PALETTE_ARGB_SHIFTR) & 0xff;
		case ZTM_PALETTE_RGBA: return (iColor >> ZTM_PALETTE_RGBA_SHIFTR) & 0xff;
		default: return ZTM_COLOR_CHANNEL_INVALID;
	}
}
ZT_INDEX ZTM_ColorG(ZT_COLOR iColor, ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return (iColor >> ZTM_PALETTE_ABGR_SHIFTG) & 0xff;
		case ZTM_PALETTE_ARGB: return (iColor >> ZTM_PALETTE_ARGB_SHIFTG) & 0xff;
		case ZTM_PALETTE_RGBA: return (iColor >> ZTM_PALETTE_RGBA_SHIFTG) & 0xff;
		default: return ZTM_COLOR_CHANNEL_INVALID;
	}
}
ZT_INDEX ZTM_ColorB(ZT_COLOR iColor, ZT_FLAG iPalette) {
	switch (iPalette) {
		case ZTM_PALETTE_ABGR: return (iColor >> ZTM_PALETTE_ABGR_SHIFTB) & 0xff;
		case ZTM_PALETTE_ARGB: return (iColor >> ZTM_PALETTE_ARGB_SHIFTB) & 0xff;
		case ZTM_PALETTE_RGBA: return (iColor >> ZTM_PALETTE_RGBA_SHIFTB) & 0xff;
		default: return ZTM_COLOR_CHANNEL_INVALID;
	}
}
ZT_INDEX ZTM_ColorBlend(ZT_INDEX iColor, ZT_INDEX iBase, ZT_INDEX iAlpha) { ///macro this?
	return (iColor * iAlpha + iBase * (0xff - iAlpha) + 0xff) >> 8;
}

#endif // ZTM_COLOR_C_INCLUDED
