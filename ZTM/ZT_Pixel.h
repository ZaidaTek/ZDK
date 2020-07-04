/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_PIXEL_H_INCLUDED
#define ZT_PIXEL_H_INCLUDED

#include "ZTM.h"

//typedef ZT_PIXELS ZT_COLOR*;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTM_PixelsOpacity(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_INDEX iOpacity);
void ZTM_PixelsOpacityFromColor(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_INDEX iOpacity, ZT_COLOR iTransparent);
void ZTM_PixelsBlendWithAlpha(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPalette);
void ZTM_PixelsReplaceColor(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_COLOR iSearch, ZT_COLOR iReplace, ZT_FLAG iTolerance);
void ZTM_PixelsReplaceOpaqueColors(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_COLOR iReplace, ZT_INDEX iMinimumOpacity);
void ZTM_PixelsPaletteConvertFromABGRToARGB(ZT_COLOR* iPixels, ZT_INDEX iLength);
void ZTM_PixelsPaletteConvertFromABGRToRGBA(ZT_COLOR* iPixels, ZT_INDEX iLength);
void ZTM_PixelsPaletteConvertFromARGBToABGR(ZT_COLOR* iPixels, ZT_INDEX iLength);
void ZTM_PixelsPaletteConvertFromARGBToRGBA(ZT_COLOR* iPixels, ZT_INDEX iLength);
void ZTM_PixelsPaletteConvertFromRGBAToABGR(ZT_COLOR* iPixels, ZT_INDEX iLength);
void ZTM_PixelsPaletteConvertFromRGBAToARGB(ZT_COLOR* iPixels, ZT_INDEX iLength);
void ZTM_PixelsPaletteConversion(ZT_COLOR* iPixels, ZT_INDEX iLength, ZT_FLAG iPaletteSource, ZT_FLAG iPaletteTarget);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_PIXEL_H_INCLUDED
