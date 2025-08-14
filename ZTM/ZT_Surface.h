/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
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
ZT_SURFACE* ZTM_SurfaceNewDuplicate(const ZT_SURFACE* iSurface);
ZT_SURFACE* ZTM_SurfaceNewFill(const ZT_POINT* iDimensions, ZT_COLOR iColor);
ZT_SURFACE* ZTM_SurfaceNewFillFromIntegers(ZT_INDEX iX, ZT_INDEX iY, ZT_COLOR iColor);
ZT_SURFACE* ZTM_SurfaceNewExtract(const ZT_SURFACE* iSource, const ZT_RECT* iDimensions);
ZT_SURFACE* ZTM_SurfaceNewFromBitmapFile(const ZT_CHAR* iPath, ZT_FLAG iPalette);
#define ZTM_SurfaceFromBitmap(PATH,PALETTE) ZTM_SurfaceNewFromBitmapFile(PATH,PALETTE) ///compatibility, to be removed
ZT_SIZE ZTM_SurfaceSaveToBitmapFile(const ZT_SURFACE* iSurface, const ZT_CHAR* iPath, ZT_FLAG iPalette);

ZT_SURFACE* ZTM_SurfaceConvert(ZT_SURFACE* iSurface, ZT_FLAG iPaletteSource, ZT_FLAG iPaletteTarget);
ZT_SURFACE* ZTM_SurfaceBlendAlpha(ZT_SURFACE* iSurface, ZT_FLAG iPalette);

///needs to be retested, is/was actually being used in ZUI O.o
ZT_SURFACE* ZTM_SurfaceBlend(const ZT_SURFACE* iSurface, ZT_SURFACE* oSurface, const ZT_RECT* iRectSrc, const ZT_RECT* iRectDst, ZT_FLAG iPalette);

ZT_SURFACE* ZTM_SurfaceOpacity(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_INDEX iOpacity);
ZT_SURFACE* ZTM_SurfaceOpacityFromColor(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_COLOR iTransparent, ZT_INDEX iOpacityTransparent, ZT_INDEX iOpacityOther);
ZT_SURFACE* ZTM_SurfaceReplaceColor(ZT_SURFACE* iSurface, ZT_COLOR iSearch, ZT_COLOR iReplace);
ZT_SURFACE* ZTM_SurfaceReplaceColorTolerance(ZT_SURFACE* iSurface, ZT_COLOR iSearch, ZT_COLOR iReplace, ZT_COLOR iTolerance);
ZT_SURFACE* ZTM_SurfaceReplaceOpaqueColors(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_COLOR iReplace, ZT_INDEX iMinimumOpacity);

//ZT_SURFACE** ZTM_SurfacesFromSurface(const ZT_SURFACE* iSource, const ZT_POINT* iSubdivide); ///make this void, and pass ** as param!
void ZTM_SurfacesFromSurface(const ZT_SURFACE* iSource, const ZT_POINT* iSubdivide, ZT_SURFACE** oSurfaces);
ZT_SURFACE* ZTM_SurfaceScaleUp(ZT_SURFACE* iSurface, ZT_INDEX iBitshiftLeft);
ZT_SURFACE* ZTM_SurfaceScaleDown(ZT_SURFACE* iSurface, ZT_INDEX iBitshiftRight);
ZT_SURFACE* ZTM_SurfaceFlipHorizontal(ZT_SURFACE* iSurface);
ZT_SURFACE* ZTM_SurfaceFlipVertical(ZT_SURFACE* iSurface);
ZT_SURFACE* ZTM_SurfaceNegative(ZT_SURFACE* iSurface, ZT_FLAG iPalette);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_SURFACE_H_INCLUDED
