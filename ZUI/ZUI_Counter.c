/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_COUNTER_C_INCLUDED
#define ZUI_COUNTER_C_INCLUDED

#include "ZUI__Runtime.h"

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
} bpZUI_COUNTER;
static bpZUI_COUNTER bpRINT;
ZUI_COUNTER* bpZUI_COUNTER_Build(void) {
    rZUI_ELEMENT* lElement = ZUI_ElementNew(bpRINT.SID, ZUI_ELEMENT_TYPE_COUNTER, bpRINT.rect);
    lElement->UI.font = *rZUI_RTime.system.fontUser;
    if (bpRINT.captions != NULL) {
        if ((ZT_INDEX)bpRINT.data.maximum > ZUI_UIS_LENGTH_MAX) {bpRINT.data.maximum = (void*)ZUI_UIS_LENGTH_MAX;}
        lElement->UI.type = ZUI_UI_TYPE_PRINT_LIST;
        lElement->UI.draw = (((ZT_INDEX)bpRINT.data.maximum << ZUI_UIS_SHIFT_INDEX) | ZUI_UI_DRAW_NONINTERACTIVE);
        lElement->UI.sources = bpRINT.captions;
        ZUI_UISpritesNew(lElement);
    } else {
        lElement->UI.type = ZUI_UI_TYPE_PRINT_DATA;
        lElement->UI.draw = (((bpRINT.trunk.precision << 4) | ((bpRINT.trunk.number >> 1) & 0xf)) << ZUI_UIS_SHIFT_INDEX) | ZUI_UI_DRAW_NONINTERACTIVE;
    }
    lElement->trunk = ZUI_ElementTrunkNew(bpRINT.trunk.number, bpRINT.trunk.flag, ZUI_ELEMENT_TRUNK_TYPE_NONE);
    for (ZT_INDEX i = 0; i < lElement->trunk->number; i++) {lElement->trunk->branch[i] = ZUI_ButtonNew(i, NULL, bpRINT.label[i & 0x1]);}
    ZUI_ElementTrunkRoot(lElement->trunk, lElement);
    lElement->data = ZUI_ElementDataNew(bpRINT.data.flag, bpRINT.data.type, bpRINT.data.minimum, bpRINT.data.maximum, bpRINT.data.unit, bpRINT.data.value);
    return (ZUI_COUNTER*)lElement;
}
void bpZUI_COUNTER_Base(ZT_INDEX iSID, const ZT_RECT* iRect) {
	bpRINT.SID = iSID;
	bpRINT.rect = iRect;
	bpRINT.captions = NULL;
	bpRINT.label[0] = (const ZT_CHAR*)"-";
	bpRINT.label[1] = (const ZT_CHAR*)"+";
	bpRINT.data.flag = ZUI_ELEMENT_DATA_FLAG_NONE;
	bpRINT.data.type = ZUI_ELEMENT_DATA_TYPE_UINT;
	bpRINT.data.minimum = (void*)(ZT_INDEX)0;
	bpRINT.data.maximum = (void*)(ZT_INDEX)0;
	bpRINT.data.value = (void*)(ZT_INDEX)0;
	bpRINT.data.unit = (void*)(ZT_INDEX)1;
	bpRINT.trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_NONE;
	bpRINT.trunk.number = 2;
	bpRINT.trunk.precision = 0;
}

ZUI_INCREMENT* ZUI_IncrementNew(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit) {
    bpZUI_COUNTER_Base(iSID, iRect);
    bpRINT.data.type = ZUI_ELEMENT_DATA_TYPE_INT;
    bpRINT.data.minimum = (void*)iMin;
    bpRINT.data.maximum = (void*)iMax;
    bpRINT.data.value = (void*)iInit;
    return (ZUI_INCREMENT*)bpZUI_COUNTER_Build();
}
ZUI_INCREMENT* ZUI_IncrementNewVertical(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit) {
    bpZUI_COUNTER_Base(iSID, iRect);
    bpRINT.data.type = ZUI_ELEMENT_DATA_TYPE_INT;
    bpRINT.data.minimum = (void*)iMin;
    bpRINT.data.maximum = (void*)iMax;
    bpRINT.data.value = (void*)iInit;
    bpRINT.trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_VERTICAL | ZUI_ELEMENT_TRUNK_FLAG_FLIP;
    return (ZUI_INCREMENT*)bpZUI_COUNTER_Build();
}
ZUI_INCREMENT* ZUI_IncrementNewDigital(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit) {
    bpZUI_COUNTER_Base(iSID, iRect);
    bpRINT.data.type = ZUI_ELEMENT_DATA_TYPE_INT;
    bpRINT.data.minimum = (void*)iMin;
    bpRINT.data.maximum = (void*)iMax;
    bpRINT.data.value = (void*)iInit;
    bpRINT.trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_VERTICAL | ZUI_ELEMENT_TRUNK_FLAG_FLIP;
    ZT_I lMagMin = ZTM_MagnitudeSigned(iMin);
    ZT_I lMagMax = ZTM_MagnitudeSigned(iMax);
    bpRINT.trunk.number = 2 * (((lMagMin > lMagMax) ? lMagMin : lMagMax) + 1);
    return (ZUI_INCREMENT*)bpZUI_COUNTER_Build();
}
ZUI_INCREMENT* ZUI_IncrementNewPrecision(ZT_FLAG iSID, const ZT_RECT* iRect, ZT_I iMin, ZT_I iMax, ZT_I iInit, ZT_INDEX iPrecision) {
    bpZUI_COUNTER_Base(iSID, iRect);
    bpRINT.data.type = ZUI_ELEMENT_DATA_TYPE_INT;
    bpRINT.data.minimum = (void*)iMin;
    bpRINT.data.maximum = (void*)iMax;
    bpRINT.data.value = (void*)iInit;
    bpRINT.trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_VERTICAL | ZUI_ELEMENT_TRUNK_FLAG_FLIP;
    ZT_I lMagMin = ZTM_MagnitudeSigned(iMin);
    ZT_I lMagMax = ZTM_MagnitudeSigned(iMax);
    ZT_INDEX lDigits = (((lMagMin > lMagMax) ? lMagMin : lMagMax) + 1);
    bpRINT.trunk.number = 2 * lDigits;
    bpRINT.trunk.precision = (iPrecision < lDigits) ? iPrecision : (lDigits - 1);
    return (ZUI_INCREMENT*)bpZUI_COUNTER_Build();
}
ZUI_CYCLE* ZUI_CycleNew(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR** iCaptions, ZT_INDEX iLength) {
    bpZUI_COUNTER_Base(iSID, iRect);
    bpRINT.captions = (const void**)iCaptions;
    bpRINT.data.flag = ZUI_ELEMENT_DATA_FLAG_OVERFLOW;
    bpRINT.data.maximum = (void*)(iLength ? (iLength - 1) : 0);
    bpRINT.label[0] = (const ZT_CHAR*)"<";
    bpRINT.label[1] = (const ZT_CHAR*)">";
    return (ZUI_INCREMENT*)bpZUI_COUNTER_Build();
}
ZUI_CYCLE* ZUI_CycleNewVertical(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR** iCaptions, ZT_INDEX iLength) {
    bpZUI_COUNTER_Base(iSID, iRect);
    bpRINT.captions = (const void**)iCaptions;
    bpRINT.data.flag = ZUI_ELEMENT_DATA_FLAG_OVERFLOW;
    bpRINT.data.maximum = (void*)(iLength ? (iLength - 1) : 0);
    bpRINT.trunk.flag = (iCaptions != NULL) ? ZUI_ELEMENT_TRUNK_FLAG_VERTICAL : (ZUI_ELEMENT_TRUNK_FLAG_VERTICAL | ZUI_ELEMENT_TRUNK_FLAG_FLIP);
    bpRINT.label[0] = (iCaptions != NULL) ? (const ZT_CHAR*)"/\\" : (const ZT_CHAR*)"\\/";
    bpRINT.label[1] = (iCaptions != NULL) ? (const ZT_CHAR*)"\\/" : (const ZT_CHAR*)"/\\";
    return (ZUI_INCREMENT*)bpZUI_COUNTER_Build();
}
rZUI_ELEMENT* ZUI_CounterSize(rZUI_ELEMENT* iElement, const ZT_POINT* iSize) {
    ZT_INDEX lPairs = iElement->trunk->number >> 1;
    ZT_POINT lCursor;
    ZT_RECT lBounds;
    ZT_RECT lSize;
    ZTM_PointZero(&lCursor);
    ZTM_RectZeroPos(&lBounds);
    ZTM_RectSizeFromIntegers(&lBounds, *rZUI_RTime.system.w, *rZUI_RTime.system.h);
    ZT_I lLengthMax = 0;
    ZT_I lHeightMax = 0;
    ZTK_PrintBufferLoad("  ");
    ZTK_PrintBufferGetCustomSize(iElement->UI.font, &lCursor, &lBounds, &lSize);
    ZT_I lMargin = lSize.w;
    if (iElement->UI.type == ZUI_UI_TYPE_PRINT_DATA) {
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
    } else {
        for (ZT_INDEX i = 0; i < iElement->UI.draw >> 24; i++) {
            ZTK_PrintBufferLoad(iElement->UI.sources[i]);
            ZTM_PointZero(&lCursor);
            ZTK_PrintBufferGetCustomSize(iElement->UI.font, &lCursor, &lBounds, &lSize);
            if (lSize.w > lLengthMax) {lLengthMax = lSize.w;}
            if (lSize.h > lHeightMax) {lHeightMax = lSize.h;}
        }
    }
    lLengthMax += lMargin << 1;
    lHeightMax += lMargin << 1;
    if (iSize != NULL) {
        ZTM_RectSize(&(iElement->rect), iSize);
    } else if (iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_VERTICAL) {
        iElement->rect.w = iElement->UI.font->height * lPairs;
        iElement->rect.h = 2 * iElement->UI.font->height + lHeightMax;
    } else {
        iElement->rect.h = iElement->UI.font->height;
        iElement->rect.w = 2 * lPairs * iElement->UI.font->height + lLengthMax;
    }
    ZT_RECT lRect;
    ZT_INDEX lFirst = (iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_FLIP) ? 1 : 0;
    ZT_INDEX lSecond = (iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_FLIP) ? 0 : 1;
    if (iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_VERTICAL) {
        ZT_I lButtonHeightMax = (iElement->rect.h - iElement->UI.font->height) / 2;
        if (lButtonHeightMax < 1) {lButtonHeightMax = 1;}
        ZT_I lButtonHeight = ((iElement->rect.w / (ZT_I)lPairs) > lButtonHeightMax) ? lButtonHeightMax : (iElement->rect.w / (ZT_I)lPairs);
        for (ZT_INDEX i = 0; i < lPairs; i++) {
            lRect.x = iElement->rect.x + (iElement->rect.w / lPairs) * (lPairs - (i + 1)); // is this right?
            lRect.y = iElement->rect.y; // is this right?
            ZTM_RectSizeFromIntegers(&lRect, (iElement->rect.w / lPairs), lButtonHeight);
            ZUI_Rect(iElement->trunk->branch[lFirst + 2 * i], &lRect);
            lRect.y = (iElement->rect.y + iElement->rect.h - lButtonHeight); // is this right?
            ZUI_Rect(iElement->trunk->branch[lSecond + 2 * i], &lRect);
        }
    } else {
        ZT_I lButtonWidth = (iElement->rect.h > (iElement->rect.w / (2 * (ZT_I)lPairs))) ? (iElement->rect.w / (2 * (ZT_I)lPairs)) : iElement->rect.h;
        lRect.y = iElement->rect.y;
        ZTM_RectSizeFromIntegers(&lRect, lButtonWidth, iElement->rect.h);
        for (ZT_INDEX i = 0; i < lPairs; i++) {
            lRect.x = iElement->rect.x + lButtonWidth * (lPairs - (i + 1));
            ZUI_Rect(iElement->trunk->branch[lFirst + 2 * i], &lRect);
            lRect.x = (iElement->rect.x + iElement->rect.w - lButtonWidth * (lPairs - i));
            ZUI_Rect(iElement->trunk->branch[lSecond + 2 * i], &lRect);
        }
    }
    ZUI_UISpritesReload(iElement);
    return iElement;
}

#endif // ZUI_COUNTER_C_INCLUDED
