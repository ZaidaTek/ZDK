/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_COUNTER_C_INCLUDED
#define ZUI_COUNTER_C_INCLUDED

#include "ZUI/ZUI__Runtime.h"

typedef struct {
    ZT_FLAG SID;
    const ZT_RECT* rect;
    const void** captions;
    const ZT_CHAR* label[2];
    struct {
        ZT_FLAG type;
        ZT_FLAG flag;
        void* minimum;
        void* maximum;
        void* value;
        void* unit;
    } data;
    struct {
        ZT_FLAG flag;
        ZT_INDEX number;
        ZT_INDEX precision;
    } trunk;
} ZUI_COUNTER_BUILDER;

static ZUI_COUNTER_BUILDER gBuilder;

ZUI_COUNTER* ZUI_CounterBuilder(ZUI_COUNTER_BUILDER* iBuilder);
ZUI_COUNTER* ZUI_CounterBuilderZero(ZUI_COUNTER_BUILDER* iBuilder, ZT_INDEX iSID, const ZT_RECT* iRect) {
    if (iBuilder != NULL) {
        iBuilder->SID = iSID;
        iBuilder->rect = iRect;
        iBuilder->captions = NULL;
        iBuilder->label[0] = (const ZT_CHAR*)"-";
        iBuilder->label[1] = (const ZT_CHAR*)"+";
        iBuilder->data.flag = ZUI_ELEMENT_DATA_FLAG_NONE;
        iBuilder->data.type = ZUI_ELEMENT_DATA_TYPE_UINT;
        iBuilder->data.minimum = (void*)(ZT_INDEX)0;
        iBuilder->data.maximum = (void*)(ZT_INDEX)0;
        iBuilder->data.value = (void*)(ZT_INDEX)0;
        iBuilder->data.unit = (void*)(ZT_INDEX)1;
        iBuilder->trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_NONE;
        iBuilder->trunk.number = 2;
        iBuilder->trunk.precision = 0;
    }
    return iBuilder;
}

ZUI_INCREMENT* ZUI_IncrementNew(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit) {
    ZUI_CounterBuilderZero(&gBuilder, iSID, iRect);
    gBuilder.data.type = ZUI_ELEMENT_DATA_TYPE_INT;
    gBuilder.data.minimum = (void*)iMin;
    gBuilder.data.maximum = (void*)iMax;
    gBuilder.data.value = (void*)iInit;
    return (ZUI_INCREMENT*)ZUI_CounterBuilder(&gBuilder);
}
ZUI_INCREMENT* ZUI_IncrementNewVertical(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit) {
    ZUI_CounterBuilderZero(&gBuilder, iSID, iRect);
    gBuilder.data.type = ZUI_ELEMENT_DATA_TYPE_INT;
    gBuilder.data.minimum = (void*)iMin;
    gBuilder.data.maximum = (void*)iMax;
    gBuilder.data.value = (void*)iInit;
    gBuilder.trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_VERTICAL | ZUI_ELEMENT_TRUNK_FLAG_FLIP;
    return (ZUI_INCREMENT*)ZUI_CounterBuilder(&gBuilder);
}
ZUI_INCREMENT* ZUI_IncrementNewDigital(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit) {
    ZUI_CounterBuilderZero(&gBuilder, iSID, iRect);
    gBuilder.data.type = ZUI_ELEMENT_DATA_TYPE_INT;
    gBuilder.data.minimum = (void*)iMin;
    gBuilder.data.maximum = (void*)iMax;
    gBuilder.data.value = (void*)iInit;
    gBuilder.trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_VERTICAL | ZUI_ELEMENT_TRUNK_FLAG_FLIP;
    ZT_I lMagMin = ZTM_MagnitudeSigned(iMin);
    ZT_I lMagMax = ZTM_MagnitudeSigned(iMax);
    gBuilder.trunk.number = 2 * (((lMagMin > lMagMax) ? lMagMin : lMagMax) + 1);
    return (ZUI_INCREMENT*)ZUI_CounterBuilder(&gBuilder);
}
ZUI_INCREMENT* ZUI_IncrementNewPrecision(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit, ZT_INDEX iPrecision) {
    ZUI_CounterBuilderZero(&gBuilder, iSID, iRect);
    gBuilder.data.type = ZUI_ELEMENT_DATA_TYPE_INT;
    gBuilder.data.minimum = (void*)iMin;
    gBuilder.data.maximum = (void*)iMax;
    gBuilder.data.value = (void*)iInit;
    gBuilder.trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_VERTICAL | ZUI_ELEMENT_TRUNK_FLAG_FLIP;
    ZT_I lMagMin = ZTM_MagnitudeSigned(iMin);
    ZT_I lMagMax = ZTM_MagnitudeSigned(iMax);
    ZT_INDEX lDigits = (((lMagMin > lMagMax) ? lMagMin : lMagMax) + 1);
    gBuilder.trunk.number = 2 * lDigits;
    gBuilder.trunk.precision = (iPrecision < lDigits) ? iPrecision : (lDigits - 1);
    return (ZUI_INCREMENT*)ZUI_CounterBuilder(&gBuilder);
}
ZUI_CYCLE* ZUI_CycleNew(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR** iCaptions, ZT_INDEX iLength) {
    ZUI_CounterBuilderZero(&gBuilder, iSID, iRect);
    gBuilder.captions = (const void**)iCaptions;
    gBuilder.data.flag = ZUI_ELEMENT_DATA_FLAG_OVERFLOW;
    gBuilder.data.maximum = (void*)(iLength ? (iLength - 1) : 0);
    gBuilder.label[0] = (const ZT_CHAR*)"<";
    gBuilder.label[1] = (const ZT_CHAR*)">";
    return (ZUI_INCREMENT*)ZUI_CounterBuilder(&gBuilder);
}
ZUI_CYCLE* ZUI_CycleNewVertical(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR** iCaptions, ZT_INDEX iLength) {
    ZUI_CounterBuilderZero(&gBuilder, iSID, iRect);
    gBuilder.captions = (const void**)iCaptions;
    gBuilder.data.flag = ZUI_ELEMENT_DATA_FLAG_OVERFLOW;
    gBuilder.data.maximum = (void*)(iLength ? (iLength - 1) : 0);
    gBuilder.trunk.flag = (iCaptions != NULL) ? ZUI_ELEMENT_TRUNK_FLAG_VERTICAL : (ZUI_ELEMENT_TRUNK_FLAG_VERTICAL | ZUI_ELEMENT_TRUNK_FLAG_FLIP);
    gBuilder.label[0] = (iCaptions != NULL) ? (const ZT_CHAR*)"/\\" : (const ZT_CHAR*)"\\/";
    gBuilder.label[1] = (iCaptions != NULL) ? (const ZT_CHAR*)"\\/" : (const ZT_CHAR*)"/\\";
    return (ZUI_INCREMENT*)ZUI_CounterBuilder(&gBuilder);
}
ZUI_COUNTER* ZUI_CounterBuilder(ZUI_COUNTER_BUILDER* iBuilder) {
    ZUI_HOST_ELEMENT* lElement = NULL;
    if (gZUI_RTime != NULL && iBuilder != NULL) {
        if ((lElement = ZUI_ElementNew(iBuilder->SID, ZUI_ELEMENT_TYPE_COUNTER, iBuilder->rect)) != NULL) {
            lElement->UI.font = gZT_Window->user.font;
            if (iBuilder->captions != NULL) {
                if ((ZT_INDEX)iBuilder->data.maximum > ZUI_UIS_LENGTH_MAX) {iBuilder->data.maximum = (void*)ZUI_UIS_LENGTH_MAX;}
                lElement->UI.type = ZUI_UI_TYPE_PRINT_LIST;
                lElement->UI.draw = (((ZT_INDEX)iBuilder->data.maximum << ZUI_UIS_SHIFT_INDEX) | ZUI_UI_DRAW_NONINTERACTIVE);
                lElement->UI.sources = iBuilder->captions;
                ZUI_UISpritesNew(lElement);
            } else {
                lElement->UI.type = ZUI_UI_TYPE_PRINT_DATA;
                lElement->UI.draw = (((iBuilder->trunk.precision << 4) | ((iBuilder->trunk.number >> 1) & 0xf)) << ZUI_UIS_SHIFT_INDEX) | ZUI_UI_DRAW_NONINTERACTIVE;
            }
            if ((lElement->trunk = ZUI_ElementTrunkNew(iBuilder->trunk.number, iBuilder->trunk.flag, ZUI_ELEMENT_TRUNK_TYPE_NONE)) != NULL) {
                ZT_INDEX lBranchesOK = 0;
                //for (ZT_INDEX i = 0; i < lElement->trunk->number; i++) {if ((lElement->trunk->branch[i] = ZUI_ButtonNew(i, iBuilder->label[i & 0x1], NULL)) != NULL) {lBranchesOK++;}}
                for (ZT_INDEX i = 0; i < lElement->trunk->number; i++) {if ((lElement->trunk->branch[i] = ZUI_ButtonNew(i, NULL, iBuilder->label[i & 0x1])) != NULL) {lBranchesOK++;}}
                ZUI_ElementTrunkRoot(lElement->trunk, lElement);
                if (lBranchesOK == lElement->trunk->number) {
                    if ((lElement->data = ZUI_ElementDataNew(iBuilder->data.flag, iBuilder->data.type, iBuilder->data.minimum, iBuilder->data.maximum, iBuilder->data.unit, iBuilder->data.value)) != NULL) {
                        return (ZUI_COUNTER*)lElement;
                    }
                    // fail - remove branches - need to implement removing individual items from host
                }
                // fail - remove trunk
            }
            // fail - remove element - need to implement removing individual items from host
        }
    }
    return NULL;
}
ZUI_HOST_ELEMENT* ZUI_CounterSize(ZUI_HOST_ELEMENT* iElement, const ZT_POINT* iSize) {
    if (iElement != NULL) {
        if ((iElement->type & ZUI_ELEMENT_TYPE_COUNTER) && iElement->trunk != NULL) {
            ZT_INDEX lPairs = iElement->trunk->number >> 1;
            ZT_POINT lCursor;
            ZT_RECT lBounds;
            ZT_RECT lSize;
            ZTM_PointZero(&lCursor);
            ZTM_RectZeroPos(&lBounds);
            ZTM_RectSizeFromIntegers(&lBounds, gZT_Window->rect.w, gZT_Window->rect.h);
            ZT_I lLengthMax = 0;
            ZT_I lHeightMax = 0;
            ZTK_PrintBufferLoad("  ");
            ZTK_PrintBufferGetCustomSize(iElement->UI.font, &lCursor, &lBounds, &lSize);
            ZT_I lMargin = lSize.w;
            if (iElement->UI.type == ZUI_UI_TYPE_PRINT_DATA) {
                if (iElement->data != NULL) {
                    for (ZT_INDEX i = 0; i < 2; i++) {
                        switch (iElement->data->type) {
                            case ZUI_ELEMENT_DATA_TYPE_UINT: ZTK_PrintBufferLoad("%u", (ZT_U)(i ? iElement->data->minimum : iElement->data->maximum)); break;
                            case ZUI_ELEMENT_DATA_TYPE_INT: ZTK_PrintBufferLoad("%d", (ZT_I)(i ? iElement->data->minimum : iElement->data->maximum)); break;
                            default: ZTK_PrintBufferLoad(""); break;
                        }
                        ZTM_PointZero(&lCursor);
                        ZTK_PrintBufferGetCustomSize(iElement->UI.font, &lCursor, &lBounds, &lSize);
                        if (lSize.w > lLengthMax) {lLengthMax = lSize.w;}
                        if (lSize.h > lHeightMax) {lHeightMax = lSize.h;}
                    }
                }
            } else {
                if (iElement->UI.sources != NULL) {
                    for (ZT_INDEX i = 0; i < iElement->UI.draw >> 24; i++) {
                        ZTK_PrintBufferLoad(iElement->UI.sources[i]);
                        ZTM_PointZero(&lCursor);
                        ZTK_PrintBufferGetCustomSize(iElement->UI.font, &lCursor, &lBounds, &lSize);
                        if (lSize.w > lLengthMax) {lLengthMax = lSize.w;}
                        if (lSize.h > lHeightMax) {lHeightMax = lSize.h;}
                    }
                }
            }
            lLengthMax += 2 * lMargin;
            lHeightMax += 2 * lMargin;
            if (iSize != NULL) {
                ZTM_RectSize(&(iElement->rect), iSize);
            } else {
                if (iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_VERTICAL) {
                    iElement->rect.w = iElement->UI.font->height * lPairs;
                    iElement->rect.h = 2 * iElement->UI.font->height + lHeightMax;
                } else {
                    iElement->rect.h = iElement->UI.font->height;
                    iElement->rect.w = 2 * lPairs * iElement->UI.font->height + lLengthMax;
                }
            }
            if (iElement->trunk->branch != NULL) {
                ZT_RECT lRect;
                if (iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_VERTICAL) {
                    ZT_I lButtonHeightMax = (iElement->rect.h - iElement->UI.font->height) / 2;
                    if (lButtonHeightMax < 1) {lButtonHeightMax = 1;}
                    ZT_I lButtonHeight = ((iElement->rect.w / (ZT_I)lPairs) > lButtonHeightMax) ? lButtonHeightMax : (iElement->rect.w / (ZT_I)lPairs);
                    for (ZT_INDEX i = 0; i < lPairs; i++) {
                        //ZT_I lButtonHeight = ((iElement->rect.w / (ZT_I)lPairs) > (iElement->rect.h / 2)) ? (iElement->rect.h / 2) : (iElement->rect.w / (ZT_I)lPairs);
                        lRect.x = iElement->rect.x + (iElement->rect.w / lPairs) * (lPairs - (i + 1));
                        lRect.y = iElement->rect.y;
                        ZTM_RectSizeFromIntegers(&lRect, (iElement->rect.w / lPairs), lButtonHeight);
                        ZUI_Rect(iElement->trunk->branch[((iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_FLIP) ? 1 : 0) + 2 * i], &lRect);
                        lRect.y = (iElement->rect.y + iElement->rect.h - lButtonHeight);
                        ZUI_Rect(iElement->trunk->branch[((iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_FLIP) ? 0 : 1) + 2 * i], &lRect);
                        //ZUI_UISpritesNew(iElement);
                    }
                } else {
                    ZT_I lButtonWidth = (iElement->rect.h > (iElement->rect.w / (2 * (ZT_I)lPairs))) ? (iElement->rect.w / (2 * (ZT_I)lPairs)) : iElement->rect.h;
                    for (ZT_INDEX i = 0; i < lPairs; i++) {
                        //ZT_I lButtonWidth = (iElement->rect.h > (iElement->rect.w / (2 * (ZT_I)lPairs))) ? (iElement->rect.w / (2 * (ZT_I)lPairs)) : iElement->rect.h;
                        lRect.x = iElement->rect.x + lButtonWidth * (lPairs - (i + 1));
                        lRect.y = iElement->rect.y;
                        ZTM_RectSizeFromIntegers(&lRect, lButtonWidth, iElement->rect.h);
                        ZUI_Rect(iElement->trunk->branch[((iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_FLIP) ? 1 : 0) + 2 * i], &lRect);
                        lRect.x = (iElement->rect.x + iElement->rect.w - lButtonWidth * (lPairs - i));
                        ZUI_Rect(iElement->trunk->branch[((iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_FLIP) ? 0 : 1) + 2 * i], &lRect);
                        //ZUI_UISpritesNew(iElement);
                    }
                }
            }
            ZUI_UISpritesNew(iElement);
        }
    }
    return iElement;
}

#endif // ZUI_COUNTER_C_INCLUDED
