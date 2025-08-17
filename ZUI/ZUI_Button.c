/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_BUTTON_C_INCLUDED
#define ZUI_BUTTON_C_INCLUDED

#include "ZUI__Runtime.h"

void ZUI_ButtonColors(rZUI_ELEMENT* iButton, ZT_BOOL iInvert) {
    ZUI_COLOR lColor;
    for (ZT_FLAG lUIS = 0x1; lUIS & ZUI_UIS_ALL; lUIS <<= 1) {
        switch (lUIS) {
            case ZUI_UIS_FOCUS:
                lColor.background = ZUI_DEFAULT_UI_COLOR_FOCUS_BACK;
                lColor.foreground = ZUI_DEFAULT_UI_COLOR_FOCUS_FRONT;
                lColor.border = ZUI_DEFAULT_UI_COLOR_FOCUS_BORDER;
                break;
            case ZUI_UIS_RELEASE:
                lColor.background = ZUI_DEFAULT_UI_COLOR_RELEASE_BACK;
                lColor.foreground = ZUI_DEFAULT_UI_COLOR_RELEASE_FRONT;
                lColor.border = ZUI_DEFAULT_UI_COLOR_RELEASE_BORDER;
                break;
            case ZUI_UIS_PRESS:
                lColor.background = (iInvert != ZT_FALSE) ? ZUI_DEFAULT_UI_COLOR_NORMAL_BACK : ZUI_DEFAULT_UI_COLOR_PRESS_BACK;
                lColor.foreground = (iInvert != ZT_FALSE) ? ZUI_DEFAULT_UI_COLOR_NORMAL_FRONT : ZUI_DEFAULT_UI_COLOR_PRESS_FRONT;
                lColor.border = ZUI_DEFAULT_UI_COLOR_PRESS_BORDER;
                break;
            case ZUI_UIS_HOVER:
                lColor.background = ZUI_DEFAULT_UI_COLOR_HOVER_BACK;
                lColor.foreground = ZUI_DEFAULT_UI_COLOR_HOVER_FRONT;
                lColor.border = ZUI_DEFAULT_UI_COLOR_HOVER_BORDER;
                break;
            case ZUI_UIS_NORMAL:
                lColor.background = (iInvert != ZT_FALSE) ? ZUI_DEFAULT_UI_COLOR_PRESS_BACK : ZUI_DEFAULT_UI_COLOR_NORMAL_BACK;
                lColor.foreground = (iInvert != ZT_FALSE) ? ZUI_DEFAULT_UI_COLOR_PRESS_FRONT : ZUI_DEFAULT_UI_COLOR_NORMAL_FRONT;
                lColor.border = ZUI_DEFAULT_UI_COLOR_NORMAL_BORDER;
                break;
            case ZUI_UIS_DISABLED:
                lColor.background = ZUI_DEFAULT_UI_COLOR_DISABLED_BACK;
                lColor.foreground = ZUI_DEFAULT_UI_COLOR_DISABLED_FRONT;
                lColor.border = ZUI_DEFAULT_UI_COLOR_DISABLED_BORDER;
                break;
            default:
                break;
        }
        ZUI_UIColor(iButton, lUIS, &lColor);
    }
}

typedef struct {
    ZT_FLAG SID;
    const ZT_RECT* rect;
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
    } trunk;
} bpZUI_SWITCH;
static bpZUI_SWITCH bpRINT;
ZUI_SWITCH* bpZUI_SWITCH_Build(void) {
    rZUI_ELEMENT* lSwitch = ZUI_ElementNew(bpRINT.SID, ZUI_ELEMENT_TYPE_SWITCH, bpRINT.rect);
    lSwitch->UI.type = ZUI_UI_TYPE_NONE;
    lSwitch->UI.draw = ZUI_UI_DRAW_NONINTERACTIVE;
    lSwitch->UI.border  = 0;
    lSwitch->UI.font = NULL;
    lSwitch->trunk = ZUI_ElementTrunkNew(bpRINT.trunk.number, bpRINT.trunk.flag, ZUI_ELEMENT_TRUNK_TYPE_NONE);
    for (ZT_INDEX i = 0; i < lSwitch->trunk->number; i++) {
        rZUI_ELEMENT* lButton = ZUI_ElementNew(i, ZUI_ELEMENT_TYPE_BUTTON, NULL);
        lButton->UI.type = ZUI_UI_TYPE_GENERIC;
        lButton->UI.draw = ZUI_UI_DRAW_INTERACTIVE;
        lButton->UI.border = ZUI_DEFAULT_BUTTON_BORDER_SIZE;
        lButton->UI.font = *rZUI_RTime.system.fontUser;
        ZUI_UINew(lButton, bpRINT.label[i & 0x1]);
        ZUI_ButtonColors(lButton, (i & 0x1) ? ZT_TRUE : ZT_FALSE);
        ZUI_UISpritesNew(lButton);
        if (i & 0x1) {ZUI_Bury(lButton);}
        lSwitch->trunk->branch[i] = lButton;
    }
    ZUI_ElementTrunkRoot(lSwitch->trunk, lSwitch);
    lSwitch->data = ZUI_ElementDataNew(bpRINT.data.flag, bpRINT.data.type, bpRINT.data.minimum, bpRINT.data.maximum/*(void*)(0x1 << (lSwitch->trunk->number >> 1))*/, bpRINT.data.unit, bpRINT.data.value);
    return (ZUI_SWITCH*)lSwitch;
}

ZUI_BUTTON* ZUI_ButtonNew(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iLabel) {
    rZUI_ELEMENT* lElement = ZUI_ElementNew(iSID, ZUI_ELEMENT_TYPE_BUTTON, iRect);
    lElement->UI.type = ZUI_UI_TYPE_GENERIC;
    lElement->UI.draw = ZUI_UI_DRAW_INTERACTIVE;
    lElement->UI.border = ZUI_DEFAULT_BUTTON_BORDER_SIZE;
    lElement->UI.font = *rZUI_RTime.system.fontUser;
    ZUI_UINew(lElement, iLabel);
    ZUI_ButtonColors(lElement, ZT_FALSE);
    ZUI_UISpritesNew(lElement);
    return (ZUI_BUTTON*)lElement;
}
ZUI_SWITCH* ZUI_SwitchNew(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iLabelOff, const ZT_CHAR* iLabelOn) {
    return ZUI_SwitchNewArray(iSID, iRect, iLabelOff, iLabelOn, 1);
}
ZUI_SWITCH* ZUI_SwitchNewArray(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iLabelOff, const ZT_CHAR* iLabelOn, ZT_INDEX iLength) {
    bpRINT.SID = iSID;
    bpRINT.rect = iRect;
    bpRINT.label[0] = iLabelOff;
    bpRINT.label[1] = iLabelOn;
    bpRINT.data.type = ZUI_ELEMENT_DATA_TYPE_UINT;
    bpRINT.data.flag = ZUI_ELEMENT_DATA_FLAG_NONE;
    bpRINT.data.minimum = (void*)0x0;
    bpRINT.data.maximum = (void*)((0x1 << iLength) - 1);
    bpRINT.data.value = (void*)0x0;
    bpRINT.data.unit = (void*)0x1;
    bpRINT.trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_NONE;
    bpRINT.trunk.number = 2 * iLength;
    return bpZUI_SWITCH_Build();
}
ZUI_SWITCH* ZUI_SwitchNewArrayVertical(ZT_FLAG iSID, const ZT_RECT* iRect, const ZT_CHAR* iLabelOff, const ZT_CHAR* iLabelOn, ZT_INDEX iLength) {
    bpRINT.SID = iSID;
    bpRINT.rect = iRect;
    bpRINT.label[0] = iLabelOff;
    bpRINT.label[1] = iLabelOn;
    bpRINT.data.type = ZUI_ELEMENT_DATA_TYPE_UINT;
    bpRINT.data.flag = ZUI_ELEMENT_DATA_FLAG_NONE;
    bpRINT.data.minimum = (void*)0x0;
    bpRINT.data.maximum = (void*)((0x1 << iLength) - 1);
    bpRINT.data.value = (void*)0x0;
    bpRINT.data.unit = (void*)0x1;
    bpRINT.trunk.flag = ZUI_ELEMENT_TRUNK_FLAG_VERTICAL;
    bpRINT.trunk.number = 2 * iLength;
    return bpZUI_SWITCH_Build();
}
rZUI_ELEMENT* ZUI_SwitchSize(rZUI_ELEMENT* iElement, const ZT_POINT* iSize) {
    ZT_POINT lSize;
    if (iSize != NULL) {
        if (iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_VERTICAL) {
            lSize.x = iSize->x;
            lSize.y = iSize->y / (iElement->trunk->number >> 1);
        } else {
            lSize.x = iSize->x / (iElement->trunk->number >> 1);
            lSize.y = iSize->y;
        }
    } else {
        ZT_I lWidthMax = 0;
        ZT_I lHeightMax = 0;
        for (ZT_INDEX i = 0; i < iElement->trunk->number; i++) {
            ZUI_Size(iElement->trunk->branch[i], NULL);
            if (iElement->trunk->branch[i]->rect.w > lWidthMax) {lWidthMax = iElement->trunk->branch[i]->rect.w;}
            if (iElement->trunk->branch[i]->rect.h > lHeightMax) {lHeightMax = iElement->trunk->branch[i]->rect.h;}
        }
        lSize.x = lWidthMax;
        lSize.y = lHeightMax;
    }
    for (ZT_INDEX i = 0; i < iElement->trunk->number; i++) {
        ZUI_Size(iElement->trunk->branch[i], &lSize);
        if (iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_VERTICAL) {
            ZUI_PosFromInteger(iElement->trunk->branch[i], iElement->rect.x, iElement->rect.y  + ((iElement->trunk->number >> 1) - ((i >> 1) + 1)) * lSize.y);
        } else {
            ZUI_PosFromInteger(iElement->trunk->branch[i], iElement->rect.x + ((iElement->trunk->number >> 1) - ((i >> 1) + 1)) * lSize.x, iElement->rect.y);
        }
    }
    if (iElement->trunk->flag & ZUI_ELEMENT_TRUNK_FLAG_VERTICAL) {
        lSize.y *= (iElement->trunk->number >> 1);
    } else {
        lSize.x *= (iElement->trunk->number >> 1);
    }
    ZTM_RectSize(&(iElement->rect), &lSize);
    return iElement;
}

#endif // ZUI_BUTTON_C_INCLUDED
