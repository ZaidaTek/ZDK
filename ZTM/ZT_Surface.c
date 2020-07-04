/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_SURFACE_C_INCLUDED
#define ZT_SURFACE_C_INCLUDED

#include "ZTM__Runtime.h"

ZT_SURFACE* ZTM_SurfaceBlock(ZT_SURFACE* iSurface, const ZT_POINT* iDimensions) {
    if (iSurface != NULL && iDimensions != NULL) {
        iSurface->block.x = iDimensions->x;
        iSurface->block.y = iDimensions->y;
    }
    return iSurface;
}

ZT_SURFACE* ZTM_SurfacePixelsFree(ZT_SURFACE* iSurface) {
    if (iSurface != NULL) {
        if (iSurface->pixels != NULL) {ZTM32_Free(iSurface->pixels); iSurface->pixels = NULL;}
    }
    return iSurface;
}
ZT_SURFACE* ZTM_SurfacePixelsNew(ZT_SURFACE* iSurface) {
    if (iSurface != NULL) {
        ZTM_SurfacePixelsFree(iSurface);
        iSurface->pixels = ZTM32_NewBlock(&(iSurface->block));
    }
    return iSurface;
}
ZT_SURFACE* ZTM_SurfacePixelsCopy(ZT_SURFACE* iSurface, const ZT_COLOR* iPixels) {
    if (iSurface != NULL) {
        if (iPixels != NULL) {
            iSurface->pixels = ZTM32_CopyBlock(iPixels, (iSurface->pixels != NULL) ? iSurface->pixels : ZTM32_NewBlock(&(iSurface->block)), &(iSurface->block));
        } else {
            iSurface->pixels = NULL;
        }
    }
    return iSurface;
}
ZT_SURFACE* ZTM_SurfacePixelsFill(ZT_SURFACE* iSurface, ZT_COLOR iColor) {
    if (iSurface != NULL) {
        if (!(iSurface->pixels != NULL)) {ZTM_SurfacePixelsNew(iSurface);}
        ZTM32_SetBlock(iSurface->pixels, iColor, &(iSurface->block));
    }
    return iSurface;
}
void ZTM_SurfaceFree(ZT_SURFACE* iSurface) {
    if (iSurface != NULL) {
        ZTM_SurfacePixelsFree(iSurface);
        ZTM8_Free(iSurface);
    }
}
ZT_SURFACE* ZTM_SurfaceNew(const ZT_POINT* iDimensions, const ZT_COLOR* iPixels) {return ZTM_SurfacePixelsCopy(ZTM_SurfaceBlock((ZT_SURFACE*)ZTM8_Init(sizeof(ZT_SURFACE), 0x0), iDimensions), iPixels);}
ZT_SURFACE* ZTM_SurfaceNewFromIntegers(ZT_INDEX iX, ZT_INDEX iY, const ZT_COLOR* iPixels) {ZT_POINT lPoint; ZTM_Point(&lPoint, iX, iY); return ZTM_SurfaceNew(&lPoint, iPixels);}
ZT_SURFACE* ZTM_SurfaceNewEmpty(void) {return ZTM_SurfaceNew(NULL, NULL);}
ZT_SURFACE* ZTM_SurfaceNewDuplicate(const ZT_SURFACE* iSurface) {return (iSurface != NULL) ? ZTM_SurfaceNew(&(iSurface->block), iSurface->pixels) : NULL;}
ZT_SURFACE* ZTM_SurfaceNewFill(const ZT_POINT* iDimensions, ZT_COLOR iColor) {return ZTM_SurfacePixelsFill(ZTM_SurfaceNew(iDimensions, NULL), iColor);}
ZT_SURFACE* ZTM_SurfaceNewFillFromIntegers(ZT_INDEX iX, ZT_INDEX iY, ZT_COLOR iColor) {return ZTM_SurfacePixelsFill(ZTM_SurfaceNewFromIntegers(iX, iY, NULL), iColor);}

ZT_SURFACE* ZTM_SurfacePixelsAlphaBlend(ZT_SURFACE* iSurface, ZT_FLAG iPalette) {if (iSurface != NULL) {ZTM_PixelsBlendWithAlpha(iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iPalette);} return iSurface;}
ZT_SURFACE* ZTM_SurfacePixelsOpacity(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_INDEX iOpacity) {
    if (iSurface != NULL) {ZTM_PixelsOpacity(iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iPalette, iOpacity);}
    return iSurface;
}
ZT_SURFACE* ZTM_SurfacePixelsOpacityFromColor(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_INDEX iOpacity, ZT_COLOR iTransparent) {
    if (iSurface != NULL) {ZTM_PixelsOpacityFromColor(iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iPalette, iOpacity, iTransparent);}
    return iSurface;
}

ZT_SURFACE* ZTM_SurfacePixelsReplaceColor(ZT_SURFACE* iSurface, ZT_COLOR iSearch, ZT_COLOR iReplace, ZT_FLAG iTolerance) {
    if (iSurface != NULL) {ZTM_PixelsReplaceColor(iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iSearch, iReplace, iTolerance);}
    return iSurface;
}
ZT_SURFACE* ZTM_SurfacePixelsReplaceOpaqueColors(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_COLOR iReplace, ZT_INDEX iMinimumOpacity)  {
    if (iSurface != NULL) {ZTM_PixelsReplaceOpaqueColors(iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iPalette, iReplace, iMinimumOpacity);}
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceBlend(const ZT_SURFACE* iSurface, ZT_SURFACE* oSurface, const ZT_RECT* iRectSrc, const ZT_RECT* iRectDst, ZT_FLAG iPalette) {
    if (iSurface != NULL && oSurface != NULL) {
        if (iSurface->pixels != NULL && oSurface->pixels != NULL) {
            ZT_POINT lOffset;
            ZT_RECT lTarget;
            ZT_RECT lSource;
            ZT_RECT lDest;
			if ((iRectDst != NULL) && (iRectSrc != NULL)) {
				lSource = *iRectSrc;
				ZTM_RectClipFromOriginToPoint(&lSource, &(iSurface->block));
				lDest = *iRectDst;
				ZTM_RectClipFromOriginToPoint(&lDest, &(oSurface->block));
				lTarget.x = lDest.x;
				lTarget.y = lDest.y;
				lTarget.w = (lDest.w < lSource.w) ? lDest.w : lSource.w;
				lTarget.h = (lDest.h < lSource.h) ? lDest.h : lSource.h;
				lOffset.x = lTarget.x - lSource.x;
				lOffset.y = lTarget.y - lSource.y;
			} else if ((iRectDst != NULL) && (iRectSrc == NULL)) {
				lDest = *iRectDst;
				ZTM_RectClipFromOriginToPoint(&lDest, &(oSurface->block));
				lTarget.x = lDest.x;
				lTarget.y = lDest.y;
				lTarget.w = (lDest.w < iSurface->block.x) ? lDest.w : iSurface->block.x;
				lTarget.h = (lDest.h < iSurface->block.y) ? lDest.h : iSurface->block.y;
				lOffset.x = lTarget.x - ((iSurface->block.x - lTarget.w) >> 1);
				lOffset.y = lTarget.y - ((iSurface->block.y - lTarget.h) >> 1);
			} else if ((iRectDst == NULL) && (iRectSrc == NULL)) {
				lTarget.w = (iSurface->block.x < oSurface->block.x) ? iSurface->block.x : oSurface->block.x;
				lTarget.h = (iSurface->block.y < oSurface->block.y) ? iSurface->block.y : oSurface->block.y;
				lTarget.x = (oSurface->block.x - lTarget.w) >> 1;
				lTarget.y = (oSurface->block.y - lTarget.h) >> 1;
				lOffset.x = lTarget.x - ((iSurface->block.x - lTarget.w) >> 1);
				lOffset.y = lTarget.y - ((iSurface->block.y - lTarget.h) >> 1);
			} else if ((iRectDst == NULL) && (iRectSrc != NULL)) {
				lSource = *iRectSrc;
				ZTM_RectClipFromOriginToPoint(&lSource, &(iSurface->block));
				lTarget.w = (lSource.w < oSurface->block.x) ? lSource.w : oSurface->block.x;
				lTarget.h = (lSource.h < oSurface->block.y) ? lSource.h : oSurface->block.y;
				lTarget.x = ((oSurface->block.x - lTarget.w) >> 1);
				lTarget.y = ((oSurface->block.y - lTarget.h) >> 1);
				lOffset.x = lTarget.x - lSource.x;
				lOffset.y = lTarget.y - lSource.y;
			}
            for (ZT_I y = lTarget.y; y < lTarget.y + lTarget.h; y++) {
                for (ZT_I x = lTarget.x; x < lTarget.x + lTarget.w; x++) {
                    ZT_I indexOffsetDst = x + y * oSurface->block.x;
                    ZT_COLOR colorSrc = iSurface->pixels[(x - lOffset.x) + ((y - lOffset.y) * iSurface->block.x)];
                    ZT_COLOR colorDst = oSurface->pixels[indexOffsetDst];
                    oSurface->pixels[indexOffsetDst] = ZTM_PixelBlend(colorSrc, colorDst, iPalette);
                }
            }
        }
    }
	return oSurface;
}

#endif // ZT_SURFACE_C_INCLUDED
