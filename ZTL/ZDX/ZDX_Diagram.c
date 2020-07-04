/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_DIAGRAM_C_INCLUDED
#define ZDX_DIAGRAM_C_INCLUDED

#include "ZDX_Diagram.h"

ZT_COLOR ZDX_DiagramColor(ZT_INDEX iChannel) {
    switch (iChannel % ZDX_DIAGRAM_COLOR_PLOTS) {
        default: return 0x0;
        case 0: return ZDX_DIAGRAM_COLOR_PLOT_1;
        case 1: return ZDX_DIAGRAM_COLOR_PLOT_2;
        case 2: return ZDX_DIAGRAM_COLOR_PLOT_3;
        case 3: return ZDX_DIAGRAM_COLOR_PLOT_4;
        case 4: return ZDX_DIAGRAM_COLOR_PLOT_5;
        case 5: return ZDX_DIAGRAM_COLOR_PLOT_6;
        case 6: return ZDX_DIAGRAM_COLOR_PLOT_7;
        case 7: return ZDX_DIAGRAM_COLOR_PLOT_8;
    }
}
ZDX_DIAGRAM* ZDX_DiagramNew(ZT_FLAG iType) {
	ZDX_DIAGRAM* lDiagram = NULL;
	if ((lDiagram = ZTM8_New(sizeof(ZDX_DIAGRAM))) != NULL) {
		lDiagram->flag = ZDX_DIAGRAM_DEFAULT_FLAG;
		lDiagram->type = iType;
		lDiagram->grid.major = NULL;
		lDiagram->grid.minor = NULL;
		lDiagram->data.trigger = NULL;
		lDiagram->data.offset = NULL;
		lDiagram->color.background = NULL;//ZDX_DIAGRAM_COLOR_BACKGROUND;
		lDiagram->color.trigger = NULL;//ZDX_DIAGRAM_COLOR_TRIGGER;
		lDiagram->color.cursor = NULL;//ZDX_DIAGRAM_COLOR_CURSOR;
		lDiagram->color.plot = NULL;
		lDiagram->color.grid.major = NULL;//ZDX_DIAGRAM_COLOR_GRID_MAJOR;
		lDiagram->color.grid.minor = NULL;//ZDX_DIAGRAM_COLOR_GRID_MINOR;
	}
	return lDiagram;
}
void ZDX_DiagramFree(ZDX_DIAGRAM* iDiagram) {
	if (iDiagram != NULL) {
		ZTM8_Free(iDiagram);
	}
}
void ZDX_DiagramRender(ZDX_DIAGRAM* iDiagram, ZDX_DATA* iData, ZT_SURFACE* oSurface) {
	if (iDiagram != NULL && oSurface != NULL) {
        ZT_INDEX lImageHeight;
        if ((lImageHeight = oSurface->block.yU) > 0) {
            ZT_INDEX lImageX = 0;
            ZT_INDEX lImageWidth = oSurface->block.xU;
            ZT_COLOR lColorBackground = (iDiagram->color.background != NULL) ? *(iDiagram->color.background) : ZDX_DIAGRAM_COLOR_BACKGROUND;
            ZT_COLOR lColorTrigger = (iDiagram->color.trigger != NULL) ? *(iDiagram->color.trigger) : ZDX_DIAGRAM_COLOR_TRIGGER;
            ZT_COLOR lColorCursor = (iDiagram->color.cursor != NULL) ? *(iDiagram->color.cursor) : ZDX_DIAGRAM_COLOR_CURSOR;
            ZT_COLOR lColorGridMajor = (iDiagram->color.grid.major != NULL) ? *(iDiagram->color.grid.major) : ZDX_DIAGRAM_COLOR_GRID_MAJOR;
            ZT_COLOR lColorGridMinor = (iDiagram->color.grid.minor != NULL) ? *(iDiagram->color.grid.minor) : ZDX_DIAGRAM_COLOR_GRID_MINOR;
            ZT_INDEX lDataCursor = 0;
            ZT_INDEX lDataChannels = 0;
            ZT_INDEX lDataWidth = 0;
            ZT_INDEX lDataOffset = 0;
            ZT_INDEX lDataIndex = 0;
            ZT_INDEX lDataIndexPrev = 0;
            ZT_INDEX* lGridX = &lImageX;
            ZT_INDEX* lGridWidth = &lImageWidth;
            if (iData != NULL) {
                lDataChannels = iData->block.xU;
                lDataWidth = iData->block.yU;
                lDataCursor = iData->cursor;
                if (iDiagram->data.offset != NULL) {lDataOffset = iDiagram->data.offset->xU % lDataWidth;}
                if (iDiagram->flag & ZDX_DIAGRAM_FLAG_GRIDREF_DATA) {
                    lGridX = &lDataIndex;
                    lGridWidth = &lDataWidth;
                }
            }
            //lDataIndex = lDataOffset;
            ZT_FLAG lPlotData = 0x1;
            for (; lImageX < lImageWidth; lImageX++) {
                ZT_COLOR lBackground = lColorBackground;
                if (iData != NULL) {
                    //lDataIndexPrev = lDataIndex;
                    lDataIndex = (lImageX + lDataOffset) % lDataWidth;
                    lDataIndexPrev = (lDataIndex ? lDataIndex : lDataWidth) - 1;
                }
                if (iDiagram->flag & ZDX_DIAGRAM_FLAG_GRID) {
                    if (iDiagram->grid.major != NULL) {
                        if (iDiagram->grid.major->xU) {
                            if ((*lGridX) > 0) {
                                ZT_DBL lFactor = (ZT_DBL)*lGridX / (ZT_DBL)*lGridWidth;
                                ZT_INDEX lStartMajor = lFactor * (ZT_DBL)iDiagram->grid.major->xU;
                                ZT_INDEX lMajor = (lStartMajor + 1) * (*lGridWidth) / iDiagram->grid.major->xU;
                                if ((((*lGridX) + 1)/* % (*lGridWidth)*/) == lMajor) {
                                    lBackground = lColorGridMajor;
                                } else {
                                    if (iDiagram->grid.minor != NULL) {
                                        ZT_INDEX lMajorPrev = lStartMajor * (*lGridWidth) / iDiagram->grid.major->xU;
                                        ZT_INDEX lStartMinor = (ZT_INDEX)(lFactor * (ZT_DBL)(iDiagram->grid.major->xU * iDiagram->grid.minor->xU)) % iDiagram->grid.minor->xU;
                                        if ((((*lGridX) + 1)/* % (*lGridWidth)*/) == lMajorPrev + ((lStartMinor + 1) * (lMajor - lMajorPrev)) / iDiagram->grid.minor->xU) {
                                            lBackground = lColorGridMinor;
                                        }
                                    }
                                }
                            } else {
                                lBackground = lColorGridMajor;
                            }
                        }
                    }
                }
                for (ZT_INDEX y = 0; y < lImageHeight; y++) {oSurface->pixels[lImageX + y * lImageWidth] = lBackground;}
                if (iDiagram->flag & ZDX_DIAGRAM_FLAG_GRID) {
                    if (iDiagram->grid.major != NULL) {
                        if (iDiagram->grid.major->y && (lBackground != lColorGridMajor)) {
                            oSurface->pixels[lImageX] = lColorGridMajor;
                            oSurface->pixels[lImageX + (lImageHeight - 1) * lImageWidth] = lColorGridMajor;
                            for (ZT_INDEX i = 0; i < iDiagram->grid.major->yU; i++) {
                                ZT_U lMajorPrev = i * lImageHeight / iDiagram->grid.major->yU;
                                ZT_U lMajor = (i + 1) * lImageHeight / iDiagram->grid.major->yU;
                                if (iDiagram->grid.minor != NULL) {
                                    for (ZT_INDEX ii = 1; ii < iDiagram->grid.minor->yU; ii++) {
                                        ZT_U lMinor = lMajorPrev + (ii * (lMajor - lMajorPrev) / iDiagram->grid.minor->yU);
                                        oSurface->pixels[lImageX + (lMinor ? (lMinor - 1) : 0) * lImageWidth] = lColorGridMinor;
                                    }
                                }
                                oSurface->pixels[lImageX + (lMajor ? (lMajor - 1) : 0) * lImageWidth] = lColorGridMajor;
                            }
                        }
                    }
                }
                if (iData != NULL) {
                    if (iDiagram->flag & ZDX_DIAGRAM_FLAG_TRIGGER) {
                        if (iDiagram->data.trigger != NULL) {
                            if (lPlotData && lDataIndex == iDiagram->data.trigger->xU) {for (ZT_INDEX y = 1; y < lImageHeight; y += 2) {oSurface->pixels[lImageX + y * lImageWidth] = lColorTrigger;}}
                            if (lImageX % 2) {oSurface->pixels[lImageX + (lImageHeight - (1 + ((iDiagram->data.trigger->yU * lImageHeight) >> iData->resolution))) * lImageWidth] = lColorTrigger;}
                        }
                    }
                    if (lPlotData) {
                        for (ZT_INDEX lChannel = 0; lChannel < lDataChannels; lChannel++) {
                            ZT_COLOR lColorPlot = (iDiagram->color.plot != NULL) ? iDiagram->color.plot[lChannel] : ZDX_DiagramColor(lChannel);
                            ZT_INDEX lPlot = lImageHeight - (1 + ((iData->data[lDataIndex * lDataChannels + lChannel] * lImageHeight) >> iData->resolution));
                            ZT_INDEX lPlotPrev = lImageHeight - (1 + ((iData->data[lDataIndexPrev * lDataChannels + lChannel] * lImageHeight) >> iData->resolution));
                            ZT_INDEX lStart = lPlotPrev;
                            ZT_INDEX lStop = lPlot + ((lPlot == lPlotPrev) ? 1 : 0);
                            if (lPlot < lPlotPrev) {
                                lStart = lPlot;
                                lStop = lPlotPrev;
                            }
                            for (ZT_INDEX y = lStart; y < lStop; y++) {oSurface->pixels[lImageX + y * lImageWidth] = lColorPlot;}
                        }
                    }
                    if (lDataIndex == lDataCursor) {
                        //lPlotData = 0x0;
                        if (iDiagram->flag & ZDX_DIAGRAM_FLAG_CURSOR) {for (ZT_INDEX y = 0; y < lImageHeight; y++) {oSurface->pixels[lImageX + y * lImageWidth] = lColorCursor;}}
                    }
                }
            }
        }
	}
}

#endif // ZDX_DIAGRAM_C_INCLUDED