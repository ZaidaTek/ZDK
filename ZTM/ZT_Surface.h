/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_SURFACE_H_INCLUDED
#define ZT_SURFACE_H_INCLUDED

#include "ZTM.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTM_SurfaceFree(ZT_SURFACE* iSurface);
ZT_SURFACE* ZTM_SurfaceNew(const ZT_POINT* iDimensions, const ZT_COLOR* iPixels);
ZT_SURFACE* ZTM_SurfaceNewFromIntegers(ZT_INDEX iX, ZT_INDEX iY, const ZT_COLOR* iPixels);
ZT_SURFACE* ZTM_SurfaceNewEmpty(void);
ZT_SURFACE* ZTM_SurfaceNewDuplicate(const ZT_SURFACE* iSurface);
ZT_SURFACE* ZTM_SurfaceNewFill(const ZT_POINT* iDimensions, ZT_COLOR iColor);
ZT_SURFACE* ZTM_SurfaceNewFillFromIntegers(ZT_INDEX iX, ZT_INDEX iY, ZT_COLOR iColor);
ZT_SURFACE* ZTM_SurfacePixelsAlphaBlend(ZT_SURFACE* iSurface, ZT_FLAG iPalette);
ZT_SURFACE* ZTM_SurfacePixelsOpacity(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_INDEX iOpacity);
ZT_SURFACE* ZTM_SurfacePixelsOpacityFromColor(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_INDEX iOpacity, ZT_COLOR iTransparent);
ZT_SURFACE* ZTM_SurfaceBlend(const ZT_SURFACE* iSurface, ZT_SURFACE* oSurface, const ZT_RECT* iRectSrc, const ZT_RECT* iRectDst, ZT_FLAG iPalette);
ZT_SURFACE* ZTM_SurfacePixelsReplaceColor(ZT_SURFACE* iSurface, ZT_COLOR iSearch, ZT_COLOR iReplace, ZT_FLAG iTolerance);
ZT_SURFACE* ZTM_SurfacePixelsReplaceOpaqueColors(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_COLOR iReplace, ZT_INDEX iMinimumOpacity);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_SURFACE_H_INCLUDED
