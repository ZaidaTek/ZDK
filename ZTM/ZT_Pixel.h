/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_PIXEL_H_INCLUDED
#define ZT_PIXEL_H_INCLUDED

#include "ZTM.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTM_PixelsFlipHorizontal(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensions);
void ZTM_PixelsFlipVertical(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensions);
void ZTM_PixelsExtract(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensionsSource, const ZT_RECT* iDimensionsTarget);
void ZTM_PixelsScaleUp(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensionsSource, ZT_INDEX iBitshiftLeft); ///not implemented: oTarget == iSource
void ZTM_PixelsScaleDown(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensionsSource, ZT_INDEX iBitshiftRight); ///not implemented: oTarget == iSource
void ZTM_PixelsNegative(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette);
void ZTM_PixelsOpacity(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_INDEX iOpacity);
void ZTM_PixelsOpacityFromColor(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_COLOR iTransparent, ZT_INDEX iOpacityTransparent, ZT_INDEX iOpacityOther);
void ZTM_PixelsReplaceColor(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_COLOR iSearch, ZT_COLOR iReplace);
void ZTM_PixelsReplaceColorTolerance(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_COLOR iSearch, ZT_COLOR iReplace, ZT_COLOR iTolerance);
void ZTM_PixelsReplaceOpaqueColors(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_COLOR iReplace, ZT_INDEX iMinimumOpacity);
void ZTM_PixelsBlend(const ZT_COLOR* iForeground, const ZT_COLOR* iBackground, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette);
void ZTM_PixelsBlendAlpha(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette);
void ZTM_PixelsConvertABGRToARGB(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength);
void ZTM_PixelsConvertABGRToRGBA(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength);
void ZTM_PixelsConvertARGBToABGR(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength);
void ZTM_PixelsConvertARGBToRGBA(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength);
void ZTM_PixelsConvertRGBAToABGR(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength);
void ZTM_PixelsConvertRGBAToARGB(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength);
void ZTM_PixelsConvert(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPaletteSource, ZT_FLAG iPaletteTarget);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_PIXEL_H_INCLUDED
