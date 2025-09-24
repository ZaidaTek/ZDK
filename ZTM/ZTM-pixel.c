/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_PIXEL_C_INCLUDED
#define ZTM_PIXEL_C_INCLUDED

#include "ZTM-RT.h"

void ZTM_PixelsNegative(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette) {
	ZT_COLOR lMaskA = ZTM_ColorMaskA(iPalette);
	ZT_COLOR lMaskR = ZTM_ColorMaskR(iPalette);
	ZT_COLOR lMaskG = ZTM_ColorMaskG(iPalette);
	ZT_COLOR lMaskB = ZTM_ColorMaskB(iPalette);
	ZT_INDEX i = -1;
	while (++i < iLength) {
		ZT_COLOR lColor = iSource[i];
		oTarget[i] = (lColor & lMaskA) | (lMaskR - (lColor & lMaskR)) | (lMaskG - (lColor & lMaskG)) | (lMaskB - (lColor & lMaskB));
	}
}
void ZTM_PixelsOpacity(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_INDEX iOpacity) {
	ZT_COLOR lMaskC = ZTM_ColorMaskC(iPalette);
	ZT_COLOR lAlpha = ((iOpacity < 0xff) ? iOpacity : 0xff) << ZTM_ColorShiftA(iPalette);
	ZT_INDEX i = -1;
	while (++i < iLength) {oTarget[i] = (iSource[i] & lMaskC) | lAlpha;}
}
void ZTM_PixelsOpacityFromColor(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_COLOR iTransparent, ZT_INDEX iOpacityTransparent, ZT_INDEX iOpacityOther) {
	ZT_COLOR lAlphaOther = ((iOpacityOther < 0xff) ? iOpacityOther : 0xff) << ZTM_ColorShiftA(iPalette);
	ZT_COLOR lAlphaTransparent = ((iOpacityTransparent < 0xff) ? iOpacityTransparent : 0xff) << ZTM_ColorShiftA(iPalette);
	ZT_COLOR lMaskC = ZTM_ColorMaskC(iPalette);
	ZT_COLOR lColorTransparent = iTransparent & lMaskC;
	ZT_COLOR lColor;
	ZT_INDEX i = -1;
	while (++i < iLength) {if ((lColor = iSource[i] & lMaskC) == lColorTransparent) {oTarget[i] = lColor | lAlphaTransparent;} else {oTarget[i] = lColor | lAlphaOther;}}
}
void ZTM_PixelsReplaceColor(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_COLOR iSearch, ZT_COLOR iReplace) {
	ZT_INDEX i = -1;
	if (iSource != oTarget) {
		ZT_COLOR lColor;
		while (++i < iLength) {if ((lColor = iSource[i]) == iSearch) {oTarget[i] = iReplace;} else {oTarget[i] = lColor;}}
	} else {
		while (++i < iLength) {if (iSource[i] == iSearch) {oTarget[i] = iReplace;}}
	}
}
void ZTM_PixelsReplaceColorTolerance(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_COLOR iSearch, ZT_COLOR iReplace, ZT_COLOR iTolerance) {
	ZT_INDEX i = -1;
	if (iSource != oTarget) {
		ZT_COLOR lColor;
		while (++i < iLength) {if (ZTM_ByteLessEqual(ZTM_ByteOffset((lColor = iSource[i]), iSearch), iTolerance) == 0x01010101) {oTarget[i] = iReplace;} else {oTarget[i] = lColor;}}
	} else {
		while (++i < iLength) {if (ZTM_ByteLessEqual(ZTM_ByteOffset(iSource[i], iSearch), iTolerance) == 0x01010101) {oTarget[i] = iReplace;}}
	}
}
void ZTM_PixelsReplaceOpaqueColors(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette, ZT_COLOR iReplace, ZT_INDEX iMinimumOpacity) {
	ZT_COLOR lMaskA = ZTM_ColorMaskA(iPalette);
	ZT_COLOR lThreshold = iMinimumOpacity << ZTM_ColorShiftA(iPalette);
	ZT_INDEX i = -1;
	if (iSource != oTarget) {
		ZT_COLOR lColor;
		while (++i < iLength) {if (((lColor = iSource[i]) & lMaskA) >= lThreshold) {oTarget[i] = iReplace;} else {oTarget[i] = lColor;}}
	} else {
		while (++i < iLength) {if ((iSource[i] & lMaskA) >= lThreshold) {oTarget[i] = iReplace;}}
	}
}
void ZTM_PixelsBlend(const ZT_COLOR* iForeground, const ZT_COLOR* iBackground, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette) { // needs to be retested
	ZT_INDEX lShiftR = ZTM_ColorShiftR(iPalette);
	ZT_INDEX lShiftG = ZTM_ColorShiftG(iPalette);
	ZT_INDEX lShiftB = ZTM_ColorShiftB(iPalette);
	ZT_INDEX lShiftA = ZTM_ColorShiftA(iPalette);
	ZT_INDEX i = -1;
	while (++i < iLength) {
		ZT_COLOR lColorFg = iForeground[i];
		ZT_COLOR lColorBg = iBackground[i];
		ZT_INDEX lAlphaFg = (lColorFg >> lShiftA) & 0xff;
		ZT_INDEX lAlphaBg = (lColorBg >> lShiftA) & 0xff;
		ZT_COLOR lMaskR = ZTM_ColorBlend((lColorFg >> lShiftR) & 0xff, (lColorBg >> lShiftR) & 0xff, lAlphaFg) << lShiftR;
		ZT_COLOR lMaskG = ZTM_ColorBlend((lColorFg >> lShiftG) & 0xff, (lColorBg >> lShiftG) & 0xff, lAlphaFg) << lShiftG;
		ZT_COLOR lMaskB = ZTM_ColorBlend((lColorFg >> lShiftB) & 0xff, (lColorBg >> lShiftB) & 0xff, lAlphaFg) << lShiftB;
		ZT_COLOR lMaskA = ((lAlphaFg + ((lAlphaBg * (0xff - lAlphaFg) + 0xff) >> 8)) & 0xff) << lShiftA;
		oTarget[i] = lMaskR | lMaskG | lMaskB | lMaskA;
	}
}
void ZTM_PixelsBlendAlpha(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPalette) {
	ZT_INDEX lShiftR = ZTM_ColorShiftR(iPalette);
	ZT_INDEX lShiftG = ZTM_ColorShiftG(iPalette);
	ZT_INDEX lShiftB = ZTM_ColorShiftB(iPalette);
	ZT_INDEX lShiftA = ZTM_ColorShiftA(iPalette);
	ZT_COLOR lMaskA = ZTM_ColorMaskA(iPalette);
	ZT_INDEX i = -1;
	while (++i < iLength) {
		ZT_COLOR lColor = iSource[i];
		ZT_INDEX lA = (lColor >> lShiftA) & 0xff;
		//ZT_COLOR lR = (((lColor >> lShiftR) & 0xff) * lA / 0xff) << lShiftR;
		//ZT_COLOR lG = (((lColor >> lShiftG) & 0xff) * lA / 0xff) << lShiftG;
		//ZT_COLOR lB = (((lColor >> lShiftB) & 0xff) * lA / 0xff) << lShiftB;
		ZT_COLOR lR = ((((lColor >> lShiftR) & 0xff) * lA + 0xff) >> 8) << lShiftR;
		ZT_COLOR lG = ((((lColor >> lShiftG) & 0xff) * lA + 0xff) >> 8) << lShiftG;
		ZT_COLOR lB = ((((lColor >> lShiftB) & 0xff) * lA + 0xff) >> 8) << lShiftB;
		oTarget[i] = (lColor & lMaskA) | lR | lG | lB;
	}
}
void ZTM_PixelsConvertABGRToARGB(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength) {
	ZT_INDEX i = -1;
	while (++i < iLength) {oTarget[i] = ((iSource[i] & 0xff00ff00) | ((iSource[i] & 0xff0000) >> 16) | ((iSource[i] & 0xff) << 16));}
}
void ZTM_PixelsConvertABGRToRGBA(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength) {
	ZT_INDEX i = -1;
	while (++i < iLength) {oTarget[i] = ((iSource[i] << 24) | (iSource[i] >> 24) | ((iSource[i] & 0xff0000) >> 8) | ((iSource[i] & 0xff00) << 8));}
}
void ZTM_PixelsConvertARGBToABGR(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength) {
	ZT_INDEX i = -1;
	while (++i < iLength) {oTarget[i] = ((iSource[i] & 0xff00ff00) | ((iSource[i] >> 16) & 0xff) | ((iSource[i] & 0xff) << 16));}
}
void ZTM_PixelsConvertARGBToRGBA(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength) {
	ZT_INDEX i = -1;
	while (++i < iLength) {oTarget[i] = ((iSource[i] >> 24) | (iSource[i] << 8));}
}
void ZTM_PixelsConvertRGBAToABGR(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength) {
	ZT_INDEX i = -1;
	while (++i < iLength) {oTarget[i] = ((iSource[i] << 24) | (iSource[i] >> 24) | ((iSource[i] >> 8) & 0xff00) | ((iSource[i] & 0xff00) << 8));}
}
void ZTM_PixelsConvertRGBAToARGB(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength) {
	ZT_INDEX i = -1;
	while (++i < iLength) {oTarget[i] = ((iSource[i] << 24) | (iSource[i] >> 8));}
}
void ZTM_PixelsConvert(const ZT_COLOR* iSource, ZT_COLOR* oTarget, ZT_INDEX iLength, ZT_FLAG iPaletteSource, ZT_FLAG iPaletteTarget) {
	switch (iPaletteSource) {
		case ZTM_PALETTE_ABGR:
			switch (iPaletteTarget) {
				case ZTM_PALETTE_ARGB: ZTM_PixelsConvertABGRToARGB(iSource, oTarget, iLength); return;
				case ZTM_PALETTE_RGBA: ZTM_PixelsConvertABGRToRGBA(iSource, oTarget, iLength); return;
				case ZTM_PALETTE_ABGR: break;
				default: return;
			}
			break;
		case ZTM_PALETTE_ARGB:
			switch (iPaletteTarget) {
				case ZTM_PALETTE_ABGR: ZTM_PixelsConvertARGBToABGR(iSource, oTarget, iLength); return;
				case ZTM_PALETTE_RGBA: ZTM_PixelsConvertARGBToRGBA(iSource, oTarget, iLength); return;
				case ZTM_PALETTE_ARGB: break;
				default: return;
			}
			break;
		case ZTM_PALETTE_RGBA:
			switch (iPaletteTarget) {
				case ZTM_PALETTE_ABGR: ZTM_PixelsConvertRGBAToABGR(iSource, oTarget, iLength); return;
				case ZTM_PALETTE_ARGB: ZTM_PixelsConvertRGBAToARGB(iSource, oTarget, iLength); return;
				case ZTM_PALETTE_RGBA: break;
				default: return;
			}
			break;
		default:
			return;
	}
	if (iSource != oTarget) {ZTM32_Copy(iSource, oTarget, iLength);}
}
void ZTM_PixelsFlipHorizontal(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensions) {
	ZT_I y = -1;
	if (oTarget != iSource) {
		while (++y < iDimensions->y) {
			ZT_I x = -1;
			ZT_I lOffsetTarget = y * iDimensions->x;
			ZT_I lOffsetSource = (y + 1) * iDimensions->x - 1;
			while (++x < iDimensions->x) {oTarget[lOffsetTarget + x] = iSource[lOffsetSource - x];}
		}
	} else {
		ZT_I lHalfX = (iDimensions->x >> 1);
		while (++y < iDimensions->y) {
			ZT_I x = -1;
			ZT_I lOffsetTarget = y * iDimensions->x;
			ZT_I lOffsetSource = (y + 1) * iDimensions->x - 1;
			while (++x < lHalfX) {
				ZT_COLOR lCache = oTarget[lOffsetTarget + x];
				oTarget[lOffsetTarget + x] = oTarget[lOffsetSource - x];
				oTarget[lOffsetSource - x] = lCache; ///is this maybe faster if read is in reverse, rather than write?
			}
		}
	}
}
void ZTM_PixelsFlipVertical(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensions) {
	ZT_I y = -1;
	if (oTarget != iSource) {
		while (++y < iDimensions->y) {ZTM32_Copy(&iSource[iDimensions->x * y], &oTarget[iDimensions->x * (iDimensions->y - 1 - y)], iDimensions->x);}
	} else {
		ZT_COLOR* lCache = ZTM8_New(sizeof(ZT_COLOR) * iDimensions->x);
		while (++y < iDimensions->y) {
			ZTM32_Copy(&oTarget[iDimensions->x * y], lCache, iDimensions->x);
			ZTM32_Copy(&oTarget[iDimensions->x * (iDimensions->y - 1 - y)], &oTarget[iDimensions->x * y], iDimensions->x);
			ZTM32_Copy(lCache, &oTarget[iDimensions->x * (iDimensions->y - 1 - y)], iDimensions->x);
		}
		ZTM8_Free(lCache);
	}
}
void ZTM_PixelsExtract(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensionsSource, const ZT_RECT* iDimensionsTarget) {
	for (ZT_I y = 0; y < iDimensionsTarget->h; y++) {
		ZT_I lOffsetTarget = iDimensionsTarget->w * y;
		ZT_I lOffsetSource = iDimensionsSource->x * (y + iDimensionsTarget->y) + iDimensionsTarget->x;
		for (ZT_I x = 0; x < iDimensionsTarget->w; x++) {
			oTarget[lOffsetTarget + x] = iSource[lOffsetSource + x];
		}
	}
}
void ZTM_PixelsScaleUp(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensionsSource, ZT_INDEX iBitshiftLeft) {
	ZT_POINT lSizeTarget;
	lSizeTarget.x = iDimensionsSource->x << iBitshiftLeft;
	lSizeTarget.y = iDimensionsSource->y << iBitshiftLeft;
	for (ZT_I y = 0; y < lSizeTarget.y; y++) {
		ZT_I lOffset = y * lSizeTarget.x;
		ZT_I lOffsetSource = (y >> iBitshiftLeft) * iDimensionsSource->x;
		for (ZT_I x = 0; x < lSizeTarget.x; x++) {
			oTarget[lOffset + x] = iSource[lOffsetSource + (x >> iBitshiftLeft)];
		}
	}
}
void ZTM_PixelsScaleDown(const ZT_COLOR* iSource, ZT_COLOR* oTarget, const ZT_POINT* iDimensionsSource, ZT_INDEX iBitshiftRight) {
	ZT_POINT lSizeTarget;
	lSizeTarget.x = iDimensionsSource->x >> iBitshiftRight;
	lSizeTarget.y = iDimensionsSource->y >> iBitshiftRight;
	for (ZT_I y = 0; y < lSizeTarget.y; y++) {
		ZT_I lOffset = y * lSizeTarget.x;
		ZT_I lOffsetSource = (y << iBitshiftRight) * iDimensionsSource->x;
		for (ZT_I x = 0; x < lSizeTarget.x; x++) {
			oTarget[lOffset + x] = iSource[lOffsetSource + (x << iBitshiftRight)];
		}
	}
}

#endif // ZTM_PIXEL_C_INCLUDED
