/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_PIXEL_C_INCLUDED
#define ZT_PIXEL_C_INCLUDED

#include "ZTM__Runtime.h"

void ZTM_PixelsOpacity(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_INDEX iOpacity) {
    if (iPixels != NULL && iLength) {
        ZT_COLOR lAlphaMask = ((iOpacity < 0xff) ? iOpacity : 0xff) << ZTM_ColorAlphaShift(iPalette);
        for (ZT_INDEX i = 0; i < iLength; i++) {iPixels[i] &= ~lAlphaMask; iPixels[i] |= lAlphaMask;}
    }
}
void ZTM_PixelsOpacityFromColor(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_INDEX iOpacity, ZT_COLOR iTransparent) {
    if (iPixels != NULL && iLength) {
        ZT_COLOR lMaskC = ZTM_ColorMask(iPalette);
        ZT_COLOR lOpacityMask = ((iOpacity < 0xff) ? iOpacity : 0xff) << ZTM_ColorAlphaShift(iPalette);
        ZT_COLOR lTransparent = iTransparent & lMaskC;
        for (ZT_INDEX i = 0; i < iLength; i++) {
            if ((iPixels[i] & lMaskC) == lTransparent) {
                iPixels[i] &= lMaskC;
            } else {
                iPixels[i] |= lOpacityMask;
            }
        }
    }
}
void ZTM_PixelsBlendWithAlpha(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPalette) {
    if (iPixels != NULL && iLength) {
        ZT_INDEX lShiftA = ZTM_ColorAlphaShift(iPalette);
        ZT_INDEX lShiftR = ZTM_ColorRedShift(iPalette);
        ZT_INDEX lShiftG = ZTM_ColorGreenShift(iPalette);
        ZT_INDEX lShiftB = ZTM_ColorBlueShift(iPalette);
        for (ZT_INDEX i = 0; i < iLength; i++) {
            ZT_INDEX lA = ZTM_ColorAlpha(iPixels[i], iPalette);
            ZT_INDEX lR = ZTM_ColorRed(iPixels[i], iPalette) * lA / 0xff;
            ZT_INDEX lG = ZTM_ColorGreen(iPixels[i], iPalette) * lA / 0xff;
            ZT_INDEX lB = ZTM_ColorBlue(iPixels[i], iPalette) * lA / 0xff;
            iPixels[i] = ((lA << lShiftA) | (lR << lShiftR) | (lG << lShiftG) | (lB << lShiftB));
        }
    }
}
void ZTM_PixelsReplaceColor(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_COLOR iSearch, ZT_COLOR iReplace, ZT_FLAG iTolerance) {
    if (iPixels != NULL && iLength) {
        ZT_INDEX lIndex = ~0;
        if (iTolerance) {
            while (++lIndex < iLength) {
                if (ZTM_ByteLessEqual(ZTM_ByteOffset(iPixels[lIndex], iSearch), iTolerance) == 0x01010101) {
                    iPixels[lIndex] = iReplace;
                }
            }
        } else {
            while (++lIndex < iLength) {
                if (iPixels[lIndex] == iSearch) {
                    iPixels[lIndex] = iReplace;
                }
            }
        }
    }
}
void ZTM_PixelsReplaceOpaqueColors(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_COLOR iReplace, ZT_INDEX iMinimumOpacity) {
    if (iPixels != NULL && iLength) {
        ZT_COLOR lMaskC = ZTM_ColorMask(iPalette);
        ZT_COLOR lMaskA = ZTM_ColorAlphaMask(iPalette);
        ZT_INDEX lIndex = ~0;
        if (iMinimumOpacity) {
            while (++lIndex < iLength) {if ((iPixels[lIndex] & lMaskA) >= iMinimumOpacity) {iPixels[lIndex] = ((iReplace & lMaskC) | (iPixels[lIndex] & lMaskA));}}
        } else {
            while (++lIndex < iLength) {if (iPixels[lIndex] & lMaskA) {iPixels[lIndex] = iReplace;}}
        }
    }
}
void ZTM_PixelsPaletteConvertFromABGRToARGB(ZT_COLOR* iPixels, ZT_INDEX iLength) {
    if (iPixels != NULL) {
        for (ZT_INDEX i = 0; i < iLength; i++) {
            iPixels[i] = ((iPixels[i] & 0xff00ff00) | ((iPixels[i] & 0xff0000) >> 16) | ((iPixels[i] & 0xff) << 16));
        }
    }
}
void ZTM_PixelsPaletteConvertFromABGRToRGBA(ZT_COLOR* iPixels, ZT_INDEX iLength) {
    if (iPixels != NULL) {
        for (ZT_INDEX i = 0; i < iLength; i++) {
            iPixels[i] = ((iPixels[i] << 24) | (iPixels[i] >> 24) | ((iPixels[i] & 0xff0000) >> 8) | ((iPixels[i] & 0xff00) << 8));
        }
    }
}
void ZTM_PixelsPaletteConvertFromARGBToRGBA(ZT_COLOR* iPixels, ZT_INDEX iLength) {
    if (iPixels != NULL) {
        for (ZT_INDEX i = 0; i < iLength; i++) {
            iPixels[i] = ((iPixels[i] >> 24) | (iPixels[i] << 8));
        }
    }
}
void ZTM_PixelsPaletteConvertFromARGBToABGR(ZT_COLOR* iPixels, ZT_INDEX iLength) {
    if (iPixels != NULL) {
        for (ZT_INDEX i = 0; i < iLength; i++) {
            iPixels[i] = ((iPixels[i] & 0xff00ff00) | ((iPixels[i] >> 16) & 0xff) | ((iPixels[i] & 0xff) << 16));
        }
    }
}
void ZTM_PixelsPaletteConvertFromRGBAToARGB(ZT_COLOR* iPixels, ZT_INDEX iLength) {
    if (iPixels != NULL) {
        for (ZT_INDEX i = 0; i < iLength; i++) {
            iPixels[i] = ((iPixels[i] << 24) | (iPixels[i] >> 8));
        }
    }
}
void ZTM_PixelsPaletteConvertFromRGBAToABGR(ZT_COLOR* iPixels, ZT_INDEX iLength) {
    if (iPixels != NULL) {
        for (ZT_INDEX i = 0; i < iLength; i++) {
            iPixels[i] = ((iPixels[i] << 24) | (iPixels[i] >> 24) | ((iPixels[i] >> 8) & 0xff00) | ((iPixels[i] & 0xff00) << 8));
        }
    }
}
void ZTM_PixelsPaletteConversion(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPaletteSource, ZT_FLAG iPaletteTarget) {
    if (iPixels != NULL && iLength) {
        switch (iPaletteSource) {
            case ZTM_PALETTE_ABGR:
                switch (iPaletteTarget) {
                    default: case ZTM_PALETTE_ABGR: break;
                    case ZTM_PALETTE_ARGB: ZTM_PixelsPaletteConvertFromABGRToARGB(iPixels, iLength); break;
                    case ZTM_PALETTE_RGBA: ZTM_PixelsPaletteConvertFromABGRToRGBA(iPixels, iLength); break;
                }
                break;
            case ZTM_PALETTE_ARGB:
                switch (iPaletteTarget) {
                    case ZTM_PALETTE_ABGR: ZTM_PixelsPaletteConvertFromARGBToABGR(iPixels, iLength); break;
                    default: case ZTM_PALETTE_ARGB: break;
                    case ZTM_PALETTE_RGBA: ZTM_PixelsPaletteConvertFromARGBToRGBA(iPixels, iLength); break;
                }
                break;
            default:
            case ZTM_PALETTE_RGBA:
                switch (iPaletteTarget) {
                    case ZTM_PALETTE_ABGR: ZTM_PixelsPaletteConvertFromRGBAToABGR(iPixels, iLength); break;
                    case ZTM_PALETTE_ARGB: ZTM_PixelsPaletteConvertFromRGBAToARGB(iPixels, iLength); break;
                    default: case ZTM_PALETTE_RGBA: break;
                }
                break;
        }
    }
}

#endif // ZT_PIXEL_C_INCLUDED
