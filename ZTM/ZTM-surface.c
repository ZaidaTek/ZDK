/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_SURFACE_C_INCLUDED
#define ZTM_SURFACE_C_INCLUDED

#include "ZTM-RT.h"

ZT_SURFACE* ZTM_SurfaceBlock(ZT_SURFACE* iSurface, const ZT_POINT* iDimensions) {
	iSurface->block.x = iDimensions->x;
	iSurface->block.y = iDimensions->y;
    return iSurface;
}

ZT_SURFACE* ZTM_SurfacePixelsFree(ZT_SURFACE* iSurface) {
	ZTM32_Free(iSurface->pixels);
    return iSurface;
}
ZT_SURFACE* ZTM_SurfacePixelsNew(ZT_SURFACE* iSurface) {
	iSurface->pixels = ZTM32_NewBlock(&(iSurface->block));
    return iSurface;
}
ZT_SURFACE* ZTM_SurfacePixelsCopy(ZT_SURFACE* iSurface, const ZT_COLOR* iPixels) {
	ZTM32_CopyBlock(iPixels, iSurface->pixels, &(iSurface->block));
    return iSurface;
}
ZT_SURFACE* ZTM_SurfacePixelsFill(ZT_SURFACE* iSurface, ZT_COLOR iColor) {
	ZTM32_SetBlock(iSurface->pixels, iColor, &(iSurface->block));
    return iSurface;
}
void ZTM_SurfaceFree(ZT_SURFACE* iSurface) {
	ZTM_SurfacePixelsFree(iSurface);
	ZTM8_Free(iSurface);
}
ZT_SURFACE* ZTM_SurfaceNew(const ZT_POINT* iDimensions, const ZT_COLOR* iPixels) {
	ZT_SURFACE* lSurface = ZTM_SurfaceBlock(ZTM8_New(sizeof(ZT_SURFACE)), iDimensions);
	if (iPixels != NULL) {
		return ZTM_SurfacePixelsCopy(ZTM_SurfacePixelsNew(lSurface), iPixels);
	} else {
		return ZTM_SurfacePixelsNew(lSurface);
	}
}
ZT_SURFACE* ZTM_SurfaceNewFromIntegers(ZT_INDEX iX, ZT_INDEX iY, const ZT_COLOR* iPixels) {
	ZT_POINT lPoint;
	ZTM_Point(&lPoint, iX, iY);
	return ZTM_SurfaceNew(&lPoint, iPixels);
}
ZT_SURFACE* ZTM_SurfaceNewDuplicate(const ZT_SURFACE* iSurface) {
	return ZTM_SurfaceNew(&(iSurface->block), iSurface->pixels);
}
ZT_SURFACE* ZTM_SurfaceNewFill(const ZT_POINT* iDimensions, ZT_COLOR iColor) {
	return ZTM_SurfacePixelsFill(ZTM_SurfaceNew(iDimensions, NULL), iColor);
}
ZT_SURFACE* ZTM_SurfaceNewFillFromIntegers(ZT_INDEX iX, ZT_INDEX iY, ZT_COLOR iColor) {
	return ZTM_SurfacePixelsFill(ZTM_SurfaceNewFromIntegers(iX, iY, NULL), iColor);
}
ZT_SURFACE* ZTM_SurfaceNewExtract(const ZT_SURFACE* iSource, const ZT_RECT* iDimensions) {
    ZT_SURFACE* lSurface = ZTM_SurfaceNew(&iDimensions->size, NULL);
    ZTM_PixelsExtract(iSource->pixels, lSurface->pixels, &iSource->block, iDimensions);
    return lSurface;
}
ZT_SURFACE* ZTM_SurfacePixelsFromBitmap_24(ZT_SURFACE* iSurface, const ZT_U8* iSource, ZT_FLAG iPalette, ZT_BOOL iTopDown) {
    ZT_I lWidthPixel = iSurface->block.x * 3;
    ZT_I lWidthData = (lWidthPixel & 0x3) ? lWidthPixel + (4 - (lWidthPixel & 0x3)) : lWidthPixel;
    ZT_I lOffsetPixel;
    ZT_I lOffsetData;
    ZT_I lIndexData;
    ZT_COLOR lAlpha = 0xff << ZTM_ColorShiftA(iPalette);
    ZT_INDEX lShiftR = ZTM_ColorShiftR(iPalette);
    ZT_INDEX lShiftG = ZTM_ColorShiftG(iPalette);
    ZT_INDEX lShiftB = ZTM_ColorShiftB(iPalette);
    for (ZT_I y = 0; y < iSurface->block.y; y++) {
        lOffsetPixel = (iTopDown ? y : iSurface->block.y - 1 - y) * iSurface->block.x;
        lIndexData = (lOffsetData = y * lWidthData);
        for (ZT_I x = 0; x < iSurface->block.x; x++) {
            iSurface->pixels[lOffsetPixel + x] = lAlpha | (iSource[lIndexData] << lShiftB) | (iSource[lIndexData + 1] << lShiftG) | (iSource[lIndexData + 2] << lShiftR);
            lIndexData += 3;
        }
    }
    return iSurface;
}
ZT_U8* ZTM_SurfacePixelsToBitmap_24(const ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_BOOL iTopDown, ZT_POINT* oSize) {
    ZT_I lWidthPixel = iSurface->block.x * 3;
    ZT_I lWidthData = (lWidthPixel & 0x3) ? lWidthPixel + (4 - (lWidthPixel & 0x3)) : lWidthPixel;
    ZT_U8* lTarget = ZTM8_New(3 * iSurface->block.y * lWidthData);
    ZT_I lOffsetPixel;
    ZT_I lOffsetData;
    ZT_I lIndexData;
    ZT_INDEX lShiftR = ZTM_ColorShiftR(iPalette);
    ZT_INDEX lShiftG = ZTM_ColorShiftG(iPalette);
    ZT_INDEX lShiftB = ZTM_ColorShiftB(iPalette);
    for (ZT_I y = 0; y < iSurface->block.y; y++) {
        lOffsetPixel = (iTopDown ? y : iSurface->block.y - 1 - y) * iSurface->block.x;
        lIndexData = (lOffsetData = y * lWidthData);
        for (ZT_I x = 0; x < iSurface->block.x; x++) {
            ZT_COLOR lColor = iSurface->pixels[lOffsetPixel + x];
            lTarget[lIndexData] = lColor >> lShiftB;
            lTarget[lIndexData + 1] = lColor >> lShiftG;
            lTarget[lIndexData + 2] = lColor >> lShiftR;
            lIndexData += 3;
        }
        while (lIndexData < lOffsetData + lWidthData) {lTarget[lIndexData] = 0x0; ++lIndexData;}
    }
    if (oSize != NULL) {oSize->x = lWidthData; oSize->y = iSurface->block.y;}
    return lTarget;
}
ZT_SIZE ZTM_SurfaceSaveToBitmapFile(const ZT_SURFACE* iSurface, const ZT_CHAR* iPath, ZT_FLAG iPalette) {
    ZT_POINT lBitmapDimensions;
    ZT_U8* lBitmap = ZTM_SurfacePixelsToBitmap_24(iSurface, iPalette, ZT_FALSE, &lBitmapDimensions);
    ZT_SIZE lBitmapSize = ZTM_PointArea(&lBitmapDimensions);
    ZT_U8 lHeader[256];
    ZTM8_Zero(&lHeader, sizeof(lHeader));
    ZTM_U16LE(&lHeader[2], 0x4d42);
    ZTM_U16LE(&lHeader[4], lBitmapSize + 54);
    ZTM_U32LE(&lHeader[12], 54);
    ZTM_U32LE(&lHeader[16], 40);
    ZTM_U32LE(&lHeader[20], iSurface->block.x);
    ZTM_U32LE(&lHeader[24], iSurface->block.y);
    ZTM_U16LE(&lHeader[28], 1);
    ZTM_U16LE(&lHeader[30], 24);
    ZTM_U16LE(&lHeader[32], 0x0);
    ZTM_U16LE(&lHeader[36], lBitmapSize);
    ZT_SIZE lWritten = ZIO_PipedWrite(iPath, &lHeader[2], 54, 0);
    lWritten += ZIO_PipedAppend(iPath, lBitmap, lBitmapSize); // couldn't use pipedwrite twice, with offset - find out why!
    return lWritten;
}
ZT_SURFACE* ZTM_SurfaceNewFromBitmapFile(const ZT_CHAR* iPath, ZT_FLAG iPalette) {
    ZT_SURFACE* lSurface = NULL;
    ZT_U8 lHeader[256];
    if (ZIO_PipedRead(iPath, &lHeader[2], 18, 0) == 18) {
        ZT_FLAG lSignature = ZTM_GetU16LE(&lHeader[2]);
        ZT_SIZE lOffsetBitmap = ZTM_GetU32LE(&lHeader[12]);
        ZT_SIZE lSizeInfo = ZTM_GetU32LE(&lHeader[16]);
        if ((lSignature == 0x4d42) && (ZIO_PipedRead(iPath, &lHeader[20], lSizeInfo - 4, 18) == (lSizeInfo - 4))) {
            ZT_I lWidth = ZTM_GetU32LE(&lHeader[20]);
            ZT_I lHeight = ZTM_GetU32LE(&lHeader[24]); // "ImageHeight is expressed as a negative number for top-down images"
            ZT_INDEX lPlanes = ZTM_GetU16LE(&lHeader[28]);
            ZT_INDEX lDepthBit = ZTM_GetU16LE(&lHeader[30]);
            ZT_FLAG lCompression = ZTM_GetU32LE(&lHeader[32]);
            if ((lPlanes == 1) && (lCompression == 0x0) && (lDepthBit == 24)) {
                ZT_BOOL lTopDown;
                if ((lTopDown = (lHeight < 0) ? ZT_TRUE : ZT_FALSE)) {lHeight = -lHeight;}
                ZT_I lDepthByte = lDepthBit >> 3;
                ZT_I lWidthPixel = lWidth * lDepthByte;
                ZT_I lWidthData = (lWidthPixel & 0x3) ? lWidthPixel + (4 - (lWidthPixel & 0x3)) : lWidthPixel;
                ZT_SIZE lSizeBitmap = lHeight * lWidthData;
                ZT_U8* lBitmap = ZTM8_New(lSizeBitmap);
                if (ZIO_PipedRead(iPath, lBitmap, lSizeBitmap, lOffsetBitmap) == lSizeBitmap) {
                    lSurface = ZTM_SurfaceNewFromIntegers(lWidth, lHeight, NULL);
                    ///attempts to nest the following result in function working the first call, but not on the second
                    ///not sure as to why, suspect something with optimization
                    ZTM_SurfacePixelsFromBitmap_24(lSurface, lBitmap, iPalette, lTopDown);
                    #if 0
                    ZT_I lOffsetPixel;
                    ZT_I lOffsetData;
                    ZT_I lIndexData;
                    ZT_COLOR lAlpha = 0xff << ZTM_ColorShiftA(iPalette);
                    ZT_INDEX lShiftR = ZTM_ColorShiftR(iPalette);
                    ZT_INDEX lShiftG = ZTM_ColorShiftG(iPalette);
                    ZT_INDEX lShiftB = ZTM_ColorShiftB(iPalette);
                    for (ZT_I y = 0; y < lHeight; y++) {
                        lOffsetPixel = (lTopDown ? y : lHeight - 1 - y) * lWidth;
                        lOffsetData = y * lWidthData;
                        for (ZT_I x = 0; x < lWidth; x++) {
                            lIndexData = lOffsetData + x * 3;
                            lSurface->pixels[lOffsetPixel + x] = lAlpha | (lBitmap[lIndexData] << lShiftB) | (lBitmap[lIndexData + 1] << lShiftG) | (lBitmap[lIndexData + 2] << lShiftR);
                        }
                    }
                    #endif // 0
                }
                ZTM8_Free(lBitmap);
            }
        }
    }
    return lSurface;
}
ZT_SURFACE* ZTM_SurfaceConvert(ZT_SURFACE* iSurface, ZT_FLAG iPaletteSource, ZT_FLAG iPaletteTarget) {
    ZTM_PixelsConvert(iSurface->pixels, iSurface->pixels, ZTM_PointArea(&iSurface->block), iPaletteSource, iPaletteTarget);
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceBlendAlpha(ZT_SURFACE* iSurface, ZT_FLAG iPalette) {
	ZTM_PixelsBlendAlpha(iSurface->pixels, iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iPalette);
	return iSurface;
}
ZT_SURFACE* ZTM_SurfaceOpacity(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_INDEX iOpacity) {
	ZTM_PixelsOpacity(iSurface->pixels, iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iPalette, iOpacity);
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceOpacityFromColor(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_COLOR iTransparent, ZT_INDEX iOpacityTransparent, ZT_INDEX iOpacityOther) {
	ZTM_PixelsOpacityFromColor(iSurface->pixels, iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iPalette, iTransparent, iOpacityTransparent, iOpacityOther);
    return iSurface;
}

ZT_SURFACE* ZTM_SurfaceReplaceColor(ZT_SURFACE* iSurface, ZT_COLOR iSearch, ZT_COLOR iReplace) {
	ZTM_PixelsReplaceColor(iSurface->pixels, iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iSearch, iReplace);
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceReplaceColorTolerance(ZT_SURFACE* iSurface, ZT_COLOR iSearch, ZT_COLOR iReplace, ZT_COLOR iTolerance) {
	ZTM_PixelsReplaceColorTolerance(iSurface->pixels, iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iSearch, iReplace, iTolerance);
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceReplaceOpaqueColors(ZT_SURFACE* iSurface, ZT_FLAG iPalette, ZT_COLOR iReplace, ZT_INDEX iMinimumOpacity)  {
	ZTM_PixelsReplaceOpaqueColors(iSurface->pixels, iSurface->pixels, ZTM_PointArea(&(iSurface->block)), iPalette, iReplace, iMinimumOpacity);
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceBlend(const ZT_SURFACE* iSurface, ZT_SURFACE* oSurface, const ZT_RECT* iRectSrc, const ZT_RECT* iRectDst, ZT_FLAG iPalette) { // needs to be retested
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
	} else {//if ((iRectDst == NULL) && (iRectSrc != NULL)) { //-wmaybe-uninitialized
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
		ZT_INDEX lIndexSrc = (y - lOffset.y) * iSurface->block.x + lTarget.x - lOffset.x;
		ZT_INDEX lIndexDst = y * oSurface->block.x + lTarget.x;
		ZTM_PixelsBlend(&iSurface->pixels[lIndexSrc], &oSurface->pixels[lIndexDst], &oSurface->pixels[lIndexDst], lTarget.w, iPalette);
	}
	return oSurface;
}
void ZTM_SurfacesFromSurface(const ZT_SURFACE* iSource, const ZT_POINT* iSubdivide, ZT_SURFACE** oSurfaces) {
    ZT_RECT lExtract;
    lExtract.x = 0;
    lExtract.y = 0;
    lExtract.w = iSource->block.x / iSubdivide->x;
    lExtract.h = iSource->block.y / iSubdivide->y;
    for (ZT_I y = 0; y < iSubdivide->y; y++) {
        lExtract.x = 0;
        ZT_I lOffset = y * iSubdivide->x;
        for (ZT_I x = 0; x < iSubdivide->x; x++) {
            oSurfaces[lOffset + x] = ZTM_SurfaceNewExtract(iSource, &lExtract);
            lExtract.x += lExtract.w;
        }
        lExtract.y += lExtract.h;
    }
}
// TODO shouldn't following two functions be creating dimension point on heap as well?
ZT_SURFACE* ZTM_SurfaceScaleUp(ZT_SURFACE* iSurface, ZT_INDEX iBitshiftLeft) {
    ZT_POINT lSizeTarget;
    lSizeTarget.x = iSurface->block.x << iBitshiftLeft;
    lSizeTarget.y = iSurface->block.y << iBitshiftLeft;
    ZT_COLOR* lTarget = ZTM32_NewBlock(&lSizeTarget);
    ZTM_PixelsScaleUp(iSurface->pixels, lTarget, &iSurface->block, iBitshiftLeft);
    ZTM32_Free(iSurface->pixels);
    iSurface->pixels = lTarget;
    iSurface->block = lSizeTarget;
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceScaleDown(ZT_SURFACE* iSurface, ZT_INDEX iBitshiftRight) {
    ZT_POINT lSizeTarget;
    lSizeTarget.x = iSurface->block.x >> iBitshiftRight;
    lSizeTarget.y = iSurface->block.y >> iBitshiftRight;
    ZT_COLOR* lTarget = ZTM32_NewBlock(&lSizeTarget);
    ZTM_PixelsScaleDown(iSurface->pixels, lTarget, &iSurface->block, iBitshiftRight);
    ZTM32_Free(iSurface->pixels);
    iSurface->pixels = lTarget;
    iSurface->block = lSizeTarget;
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceFlipHorizontal(ZT_SURFACE* iSurface) {
    ZTM_PixelsFlipHorizontal(iSurface->pixels, iSurface->pixels, &iSurface->block);
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceFlipVertical(ZT_SURFACE* iSurface) {
    ZTM_PixelsFlipVertical(iSurface->pixels, iSurface->pixels, &iSurface->block);
    return iSurface;
}
ZT_SURFACE* ZTM_SurfaceNegative(ZT_SURFACE* iSurface, ZT_FLAG iPalette) {
    ZTM_PixelsNegative(iSurface->pixels, iSurface->pixels, ZTM_UPointArea(&iSurface->block), iPalette);
    return iSurface;
}

#endif // ZTM_SURFACE_C_INCLUDED
