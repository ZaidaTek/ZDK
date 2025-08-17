/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_C_INCLUDED
#define ZUI_C_INCLUDED

#include "ZUI__Runtime.h"

void ZUI_WorkaroundForSwitchUpdating(ZUI_ELEMENT* iElement) {
    rZUI_ELEMENT* lElement = iElement;
    if (lElement->type == ZUI_ELEMENT_TYPE_SWITCH) {
        ZUI_Hide(iElement);
        ZUI_Show(iElement);
    }
}

void ZUI_HostElementsPurge(void) {
    for (ZT_INDEX i = 0; i < rZUI_RTime.element.length; i++) {ZUI_ElementFree(rZUI_RTime.element.registry->items[i]);}
    rZUI_RTime.element.length = 0;
}
void ZUI_HostElementsFree(void) {
    ZUI_HostElementsPurge();
    ZTM_ListFree(rZUI_RTime.element.registry);
    rZUI_RTime.element.registry = NULL;
}
void ZUI_HostElementsCreate(ZT_INDEX iSize) {
	ZT_LIST* lNew = ZTM_ListNew(iSize);
    ZT_INDEX lLength = rZUI_RTime.element.length;
    if (rZUI_RTime.element.registry != NULL) {
        ZTM_ListCopy(rZUI_RTime.element.registry, lNew);
        //ZUI_HostElementsFree(); // this is probably unintended - it would free the elements as well!
        ZTM_ListFree(rZUI_RTime.element.registry); // this was likely the intention
    }
    rZUI_RTime.element.registry = lNew;
    rZUI_RTime.element.length = lLength;
}
void ZUI_HostEventsFree(void) {
    ZTM8_Free(rZUI_RTime.event.buffer->items);
    ZTM_QListFree(rZUI_RTime.event.buffer);
}
void ZUI_HostEventsCreate(ZT_INDEX iSize) {
    rZUI_RTime.event.buffer = ZTM_QListNew(iSize);
	ZTM8_NewArray(iSize, sizeof(ZT_EVENT), 8, rZUI_RTime.event.buffer->items);
    //ZT_INDEX lSize = sizeof(ZT_EVENT);
    //if (lSize % 8) {lSize += 8 - (lSize % 8);}
    //void* lMemBlock = ZTM8_New(lSize * iSize);
    //for (ZT_INDEX i = 0; i < iSize; i++) {(rZUI_RTime.event.buffer->items)[i] = (lMemBlock + i * lSize);}
}
const rZUI_ELEMENT* ZUI_HostFocusMouse(void) {
    for (ZT_INDEX i = (rZUI_RTime.element.length - 1); i < rZUI_RTime.element.length; i--) { // overflow intended!
        const rZUI_ELEMENT* lElement = rZUI_RTime.element.registry->items[i];
        if (lElement->flag & ZUI_ELEMENT_FLAG_COLLIDE && !(lElement->flag & ZUI_ELEMENT_FLAG_DISABLE) && ZTM_PointWithinRect(rZUI_RTime.system.mousePos, &(lElement->rect))) {
            return lElement;
        }
    }
    return NULL;
}
void ZUI_HostEventsPump(const ZT_EVENT* iEvent) {
	if (rZUI_RTime.event.last != iEvent) {
		rZUI_RTime.event.last = iEvent;
		switch (iEvent->id.H) {
			case ZTK_HID_MOUSE: if ((iEvent->id.S == ZTK_SID_MOUSE_LBUTTON) && (iEvent->id.A & ZTK_AID_STRIKE)) {rZUI_RTime.element.focus = ZUI_HostFocusMouse();} break;
			default: return;
		}
		for (ZT_INDEX i = 0; i < rZUI_RTime.element.length; i++) {
			rZUI_ELEMENT* lElement = (rZUI_ELEMENT*)(rZUI_RTime.element.registry->items)[i];
			ZUI_ElementEvent(lElement);
		}
	}
}
ZT_INDEX ZUI_HostPoll(const ZT_EVENT* iEvent, ZT_EVENT** oGUIEvent) {
	if (rZUI_RTime.flag & ZUI_FLAG_FLUSH) {ZUI_HostEventsPump(iEvent); rZUI_RTime.flag &= ~ZUI_FLAG_FLUSH;}
	if (ZTM_QListQueued(rZUI_RTime.event.buffer)) {return ZTM_QListPoll(rZUI_RTime.event.buffer, (void**)oGUIEvent);} else {rZUI_RTime.flag |= ZUI_FLAG_FLUSH;}
    return 0;
}
void ZUI_HostFree(void) {
	ZUI_HostElementsFree();
	ZUI_HostEventsFree();
}
void ZUI_HostNew(void) {
	ZTM8_Zero(&rZUI_RTime, sizeof(rZUI_RTime));
	rZUI_RTime.event.buffer = NULL;
	rZUI_RTime.event.last = NULL;
	rZUI_RTime.element.registry = NULL;
	rZUI_RTime.element.length = 0;
	rZUI_RTime.element.focus = NULL;
	rZUI_RTime.system.rect = ZTK_InternalRect();
	rZUI_RTime.system.pos = ZTK_InternalPos();
	rZUI_RTime.system.size = ZTK_InternalSize();
	rZUI_RTime.system.x = ZTK_InternalX();
	rZUI_RTime.system.y = ZTK_InternalY();
	rZUI_RTime.system.w = ZTK_InternalWidth();
	rZUI_RTime.system.h = ZTK_InternalHeight();
	rZUI_RTime.system.paletteUser = ZTK_InternalPalette();
	rZUI_RTime.system.paletteSys = ZTK_InternalPaletteSystem();
	rZUI_RTime.system.tick = ZTK_InternalTick();
	rZUI_RTime.system.mousePos = ZTK_InternalMousePos();
	rZUI_RTime.system.mouseState = ZTK_InternalMouseState();
	rZUI_RTime.system.fontUser = ZTK_InternalFont();
	rZUI_RTime.system.fontSys = ZTK_InternalFontSystem();
	rZUI_RTime.flag = ZUI_DEFAULT_FLAG; // shouldn't this have the flush flag included?
	#if ZUI_COLOR_MOD_SEED > 0
	rZUI_RTime.seed = ZUI_COLOR_MOD_SEED;
	#else
	rZUI_RTime.seed = ZTM_Time();
	#endif // ZUI_COLOR_MOD_SEED
	rZUI_RTime.timestamp.cursor = (rZUI_RTime.timestamp.modulator = *rZUI_RTime.system.tick);
	rZUI_RTime.timeout.modulator = ZUI_COLOR_MOD_PERIOD;
	rZUI_RTime.timeout.cursor = ZUI_CURSOR_PERIOD;
	rZUI_RTime.color.modulator0 = ZUI_HostGetRandomColor();
	rZUI_RTime.color.modulator1 = ZUI_HostGetRandomColor();
	rZUI_RTime.color.cursor = ZUI_COLOR_CURSOR;
	ZUI_HostEventsCreate(ZUI_BUFFER_EVENTS);
}
void ZUI_HostDraw(void) {for (ZT_INDEX i = 0; i < rZUI_RTime.element.length; i++) {ZUI_ElementDraw(rZUI_RTime.element.registry->items[i]);}}
ZT_BOOL ZUI_HostRegister(rZUI_ELEMENT* iElement) {
    if (rZUI_RTime.element.registry != NULL) {
        if (!((rZUI_RTime.element.length + 1) < rZUI_RTime.element.registry->length)) {
            ZUI_HostElementsCreate(rZUI_RTime.element.registry->length + ZUI_BUFFER_ELEMENT); // buffer too small - increase size
        }
    } else {
        ZUI_HostElementsCreate(ZUI_BUFFER_ELEMENT); // buffer not present - create buffer
    }
    if (rZUI_RTime.element.registry != NULL && ((rZUI_RTime.element.length + 1) < rZUI_RTime.element.registry->length)) {
        rZUI_RTime.element.registry->items[rZUI_RTime.element.length] = iElement;
        (rZUI_RTime.element.length)++;
        return ((rZUI_RTime.element.registry->items[rZUI_RTime.element.length - 1] != iElement) ? ZT_FALSE : ZT_TRUE);
    }
	return ZT_FALSE;
}
ZT_COLOR ZUI_HostGetRandomColor(void) {
    ZT_FLAG lSource = ZTM_Randomize_32(&rZUI_RTime.seed, 0);
    ZT_INDEX lRandom;
    ZT_COLOR lColor = ZUI_COLOR_NONE;
	while (lSource >>= 8) {
		lColor <<= 8;
		if ((lRandom = lSource & 0xff) < ZUI_COLOR_MOD_MIN) {
            lRandom = ZUI_COLOR_MOD_MAX - (ZUI_COLOR_MOD_MIN - lRandom);
		} else if (lRandom > ZUI_COLOR_MOD_MAX) {
		    lRandom = ZUI_COLOR_MOD_MIN + (lRandom - ZUI_COLOR_MOD_MAX);
		}
		lColor |= lRandom;
	}
	lColor <<= ZTM_ColorShiftC(*rZUI_RTime.system.paletteUser);
	lColor |= ZTM_ColorMaskA(*rZUI_RTime.system.paletteUser);
    return lColor;
}
ZT_COLOR ZUI_HostGetJuicyColor(void) {
    ZT_TIME lNow = *rZUI_RTime.system.tick;
	while (!((lNow - rZUI_RTime.timestamp.modulator) < rZUI_RTime.timeout.modulator)) {
		rZUI_RTime.color.modulator0 = rZUI_RTime.color.modulator1;
		rZUI_RTime.color.modulator1 = ZUI_HostGetRandomColor();
		rZUI_RTime.timestamp.modulator += rZUI_RTime.timeout.modulator;
	}
	ZT_INDEX lTimeDelta = (lNow - rZUI_RTime.timestamp.modulator);
	ZT_INDEX lOffsetC = ZTM_ColorShiftC(*rZUI_RTime.system.paletteUser);
    ZT_INDEX lChannelLast;
    ZT_INDEX lChannelTarget;
    ZT_COLOR lJuicy = ZUI_COLOR_NONE;
	for (ZT_INDEX i = lOffsetC; i < (24 + lOffsetC); i += 8) {
		lJuicy <<= 8;
		if ((lChannelLast = (rZUI_RTime.color.modulator0 >> i) & 0xff) > (lChannelTarget = (rZUI_RTime.color.modulator1 >> i) & 0xff)) {
            lJuicy |= lChannelLast - ((lChannelLast - lChannelTarget) * lTimeDelta) / rZUI_RTime.timeout.modulator;
		} else {
		    lJuicy |= lChannelLast + ((lChannelTarget - lChannelLast) * lTimeDelta) / rZUI_RTime.timeout.modulator;
		}
	}
	lJuicy <<= lOffsetC;
	lJuicy |= ZTM_ColorMaskA(*rZUI_RTime.system.paletteUser);
    return lJuicy;
}

ZT_BOOL ZUI_IsEnabled(ZUI_ELEMENT* iElement) {return (((rZUI_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_DISABLE) ? ZT_FALSE : ZT_TRUE;}
ZT_BOOL ZUI_IsVisible(ZUI_ELEMENT* iElement) {return (((rZUI_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_SHOW) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZUI_IsIncluded(ZUI_ELEMENT* iElement) {return (((rZUI_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_COLLIDE) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZUI_IsRestored(ZUI_ELEMENT* iElement) {return (ZUI_IsIncluded(iElement) && ZUI_IsVisible(iElement)) ? ZT_TRUE : ZT_FALSE;}

ZT_BOOL ZUI_IsDisabled(ZUI_ELEMENT* iElement) {return (((rZUI_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_DISABLE) ? ZT_TRUE : ZT_FALSE;}
ZT_BOOL ZUI_IsHidden(ZUI_ELEMENT* iElement) {return (((rZUI_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_SHOW) ? ZT_FALSE : ZT_TRUE;}
ZT_BOOL ZUI_IsIgnored(ZUI_ELEMENT* iElement) {return (((rZUI_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_COLLIDE) ? ZT_FALSE : ZT_TRUE;}
ZT_BOOL ZUI_IsBuried(ZUI_ELEMENT* iElement) {return (ZUI_IsIgnored(iElement) && ZUI_IsHidden(iElement)) ? ZT_TRUE : ZT_FALSE;}

void ZUI_Enable(ZUI_ELEMENT* iElement) {ZUI_ElementFlagRemove(iElement, ZUI_ELEMENT_FLAG_DISABLE);}
void ZUI_Show(ZUI_ELEMENT* iElement) {ZUI_ElementFlagAppend(iElement, ZUI_ELEMENT_FLAG_SHOW);}
void ZUI_Include(ZUI_ELEMENT* iElement) {ZUI_ElementFlagAppend(iElement, ZUI_ELEMENT_FLAG_COLLIDE); ((rZUI_ELEMENT*)iElement)->id.A = ZTK_AID_NONE;} // clear previous action
void ZUI_Restore(ZUI_ELEMENT* iElement) {ZUI_Include(iElement); ZUI_Show(iElement);}

void ZUI_Disable(ZUI_ELEMENT* iElement) {ZUI_ElementFlagAppend(iElement, ZUI_ELEMENT_FLAG_DISABLE);}
void ZUI_Hide(ZUI_ELEMENT* iElement) {ZUI_ElementFlagRemove(iElement, ZUI_ELEMENT_FLAG_SHOW);}
void ZUI_Ignore(ZUI_ELEMENT* iElement) {ZUI_ElementFlagRemove(iElement, ZUI_ELEMENT_FLAG_COLLIDE);}
void ZUI_Bury(ZUI_ELEMENT* iElement) {ZUI_ElementFlagRemove(iElement, ZUI_ELEMENT_FLAG_SHOW | ZUI_ELEMENT_FLAG_COLLIDE);}

ZT_INDEX ZUI_GetBorderSize(ZUI_ELEMENT* iElement) {return ((rZUI_ELEMENT*)iElement)->UI.border;}
ZT_I ZUI_GetX(ZUI_ELEMENT* iElement) {return ((rZUI_ELEMENT*)iElement)->rect.x;}
ZT_I ZUI_GetY(ZUI_ELEMENT* iElement) {return ((rZUI_ELEMENT*)iElement)->rect.y;}
ZT_I ZUI_GetXCenter(ZUI_ELEMENT* iElement) {return ((rZUI_ELEMENT*)iElement)->rect.x + ((((rZUI_ELEMENT*)iElement)->rect.w) >> 1);}
ZT_I ZUI_GetYCenter(ZUI_ELEMENT* iElement) {return ((rZUI_ELEMENT*)iElement)->rect.y + ((((rZUI_ELEMENT*)iElement)->rect.h) >> 1);}
ZT_I ZUI_GetXRight(ZUI_ELEMENT* iElement) {return ((rZUI_ELEMENT*)iElement)->rect.x + ((rZUI_ELEMENT*)iElement)->rect.w;}
ZT_I ZUI_GetYBottom(ZUI_ELEMENT* iElement) {return ((rZUI_ELEMENT*)iElement)->rect.y + ((rZUI_ELEMENT*)iElement)->rect.h;}
ZT_I ZUI_GetWidth(ZUI_ELEMENT* iElement) {return ((rZUI_ELEMENT*)iElement)->rect.w;}
ZT_I ZUI_GetHeight(ZUI_ELEMENT* iElement) {return ((rZUI_ELEMENT*)iElement)->rect.h;}
const ZT_RECT* ZUI_GetRect(ZUI_ELEMENT* iElement) {return &(((rZUI_ELEMENT*)iElement)->rect);}
const ZT_FONT* ZUI_GetFont(ZUI_ELEMENT* iElement) {return (((rZUI_ELEMENT*)iElement)->UI.font);}

const ZUI_COLOR* ZUI_GetColor(ZUI_ELEMENT* iElement, ZT_FLAG iUIS) {
    rZUI_ELEMENT* lElement = iElement;
    if (lElement->UI.type == ZUI_UI_TYPE_GENERIC) {
        ZT_INDEX lIndex = ZUI_UIGenericGetStateIndex(&lElement->UI, iUIS);
        if (lIndex < ZTM_BitCount(lElement->UI.draw & ZUI_UIS_MASK)) {return &(lElement->UI.colors[lIndex]);}
    }
    return NULL;
}
const void* ZUI_GetSource(ZUI_ELEMENT* iElement, ZT_FLAG iUIS) {
    rZUI_ELEMENT* lElement = iElement;
    if (lElement->UI.type == ZUI_UI_TYPE_GENERIC) {
        ZT_INDEX lIndex = ZUI_UIGenericGetStateIndex(&lElement->UI, iUIS);
        if (lIndex < ZTM_BitCount(lElement->UI.draw & ZUI_UIS_MASK)) {return lElement->UI.sources[lIndex];}
    }
    return NULL;
}
ZT_FLAG ZUI_GetDataValue(ZUI_ELEMENT* iElement) {
    return (ZT_FLAG)((rZUI_ELEMENT*)iElement)->data->value;
}
ZUI_ELEMENT* ZUI_DataValue(ZUI_ELEMENT* iElement, ZT_FLAG iValue) {
    ZUI_ElementDataValue(((rZUI_ELEMENT*)iElement)->data, iValue);
    ZUI_WorkaroundForSwitchUpdating(iElement);
    return iElement;
}
ZUI_ELEMENT* ZUI_DataMaximum(ZUI_ELEMENT* iElement, ZT_FLAG iMaximum) {
    ZUI_ElementDataMaximum(((rZUI_ELEMENT*)iElement)->data, iMaximum);
    ZUI_WorkaroundForSwitchUpdating(iElement);
    return iElement;
}
ZUI_ELEMENT* ZUI_DataMinimum(ZUI_ELEMENT* iElement, ZT_FLAG iMinimum) {
    ZUI_ElementDataMinimum(((rZUI_ELEMENT*)iElement)->data, iMinimum);
    ZUI_WorkaroundForSwitchUpdating(iElement);
    return iElement;
}
ZUI_ELEMENT* ZUI_DataUnit(ZUI_ELEMENT* iElement, ZT_FLAG iUnit) {
    ZUI_ElementDataUnit(((rZUI_ELEMENT*)iElement)->data, iUnit);
    ZUI_WorkaroundForSwitchUpdating(iElement);
    return iElement;
}
ZUI_ELEMENT* ZUI_X(ZUI_ELEMENT* iElement, ZT_I iX) {
    return ZUI_PosFromInteger(iElement, iX, ((rZUI_ELEMENT*)iElement)->rect.y);
}
ZUI_ELEMENT* ZUI_Y(ZUI_ELEMENT* iElement, ZT_I iY) {
    return ZUI_PosFromInteger(iElement, ((rZUI_ELEMENT*)iElement)->rect.x, iY);
}
ZUI_ELEMENT* ZUI_Pos(ZUI_ELEMENT* iElement, const ZT_POINT* iPos) {
    return ZUI_PosFromInteger(iElement, iPos->x, iPos->y);
}
ZUI_ELEMENT* ZUI_PosFromInteger(ZUI_ELEMENT* iElement, ZT_I iX, ZT_I iY) {
    rZUI_ELEMENT* lElement = iElement;
    if (lElement->trunk != NULL) {
        ZT_I lDeltaX = iX - lElement->rect.x;
        ZT_I lDeltaY = iY - lElement->rect.y;
        lElement->rect.x += lDeltaX;
        lElement->rect.y += lDeltaY;
        for (ZT_INDEX i = 0; i < lElement->trunk->number; i++) {
            lElement->trunk->branch[i]->rect.x += lDeltaX;
            lElement->trunk->branch[i]->rect.y += lDeltaY;
        }
    } else {
        lElement->rect.x = iX;
        lElement->rect.y = iY;
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_XCenter(ZUI_ELEMENT* iElement, ZT_I iX) {
    rZUI_ELEMENT* lElement = iElement;
    return ZUI_PosFromInteger(lElement, iX - (lElement->rect.w >> 1), lElement->rect.y);
}
ZUI_ELEMENT* ZUI_YCenter(ZUI_ELEMENT* iElement, ZT_I iY) {
    rZUI_ELEMENT* lElement = iElement;
    return ZUI_PosFromInteger(lElement, lElement->rect.x, iY - (lElement->rect.h >> 1));
}
ZUI_ELEMENT* ZUI_PosCenter(ZUI_ELEMENT* iElement, const ZT_POINT* iPos) {
    rZUI_ELEMENT* lElement = iElement;
    return ZUI_PosFromInteger(lElement, iPos->x - (lElement->rect.w >> 1), iPos->y - (lElement->rect.h >> 1));
}
ZUI_ELEMENT* ZUI_PosCenterFromInteger(ZUI_ELEMENT* iElement, ZT_I iX, ZT_I iY) {
    rZUI_ELEMENT* lElement = iElement;
    return ZUI_PosFromInteger(lElement, iX - (lElement->rect.w >> 1), iY - (lElement->rect.h >> 1));
}

ZUI_ELEMENT* ZUI_Width(ZUI_ELEMENT* iElement, ZT_I iWidth) {
    return ZUI_SizeFromInteger(iElement, iWidth, ((rZUI_ELEMENT*)iElement)->rect.h);
}
ZUI_ELEMENT* ZUI_Height(ZUI_ELEMENT* iElement, ZT_I iHeight) {
    return ZUI_SizeFromInteger(iElement, ((rZUI_ELEMENT*)iElement)->rect.w, iHeight);
}
ZUI_ELEMENT* ZUI_Size(ZUI_ELEMENT* iElement, const ZT_POINT* iSize) {
    rZUI_ELEMENT* lElement = iElement;
    ZT_POINT lSize;
    if (iSize == NULL) {
        switch (lElement->type) {
            case ZUI_ELEMENT_TYPE_BOX:
                iSize = rZUI_RTime.system.size;
                break;
            case ZUI_ELEMENT_TYPE_BUTTON:
            case ZUI_ELEMENT_TYPE_LABEL: {
                    ZT_INDEX lState = ZUI_UIGenericGetStateIndex(&lElement->UI, ZUI_UIS_NORMAL);
                    ZTK_GetSizeFromFont((const ZT_CHAR*)lElement->UI.sources[lState], lElement->UI.font, &lSize);
                    iSize = (const ZT_POINT*)&lSize;
                }
                break;
            case ZUI_ELEMENT_TYPE_COUNTER:
                return ZUI_CounterSize(lElement, NULL);
            case ZUI_ELEMENT_TYPE_SWITCH:
                return ZUI_SwitchSize(lElement, NULL);
            default:
                return iElement;
        }
    }
    return ZUI_SizeFromInteger(iElement, iSize->x, iSize->y);
}
ZUI_ELEMENT* ZUI_SizeFromInteger(ZUI_ELEMENT* iElement, ZT_I iWidth, ZT_I iHeight) {
    rZUI_ELEMENT* lElement = iElement;
    ZT_POINT lSize;
    if ((lElement->rect.w != iWidth) || (lElement->rect.h != iHeight))  {
        //if (lElement->trunk != NULL) {
        switch (lElement->type) {
            case ZUI_ELEMENT_TYPE_COUNTER:
                lSize.x = iWidth;
                lSize.y = iHeight;
                return ZUI_CounterSize(lElement, &lSize);
            case ZUI_ELEMENT_TYPE_SWITCH:
                lSize.x = iWidth;
                lSize.y = iHeight;
                return ZUI_SwitchSize(lElement, &lSize);
            default:
                lElement->rect.w = iWidth;
                lElement->rect.h = iHeight;
                ZUI_UISpritesReload(lElement);
                break;
        }
        //} else {
        //}
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_Rect(ZUI_ELEMENT* iElement, const ZT_RECT* iRect) {
    if (iRect != NULL) {
        ZUI_Pos(iElement, &iRect->pos);
        return ZUI_Size(iElement, &iRect->size);
    } else {
        return ZUI_Size(iElement, NULL);
    }
    //return iElement;
}
ZUI_ELEMENT* ZUI_XRelative(ZUI_ELEMENT* iElement, ZT_DBL iX) {return ZUI_X(iElement, iX * *rZUI_RTime.system.w);}
ZUI_ELEMENT* ZUI_YRelative(ZUI_ELEMENT* iElement, ZT_DBL iY) {return ZUI_Y(iElement, iY * *rZUI_RTime.system.h);}
ZUI_ELEMENT* ZUI_PosRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY) {return ZUI_PosFromInteger(iElement, iX * *rZUI_RTime.system.w, iY * *rZUI_RTime.system.h);}
ZUI_ELEMENT* ZUI_XCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iX) {return ZUI_XCenter(iElement, iX * *rZUI_RTime.system.w);}
ZUI_ELEMENT* ZUI_YCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iY) {return ZUI_YCenter(iElement, iY * *rZUI_RTime.system.h);}
ZUI_ELEMENT* ZUI_PosCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY) {return ZUI_PosCenterFromInteger(iElement, iX * *rZUI_RTime.system.w, iY * *rZUI_RTime.system.h);}
ZUI_ELEMENT* ZUI_WidthRelative(ZUI_ELEMENT* iElement, ZT_DBL iWidth) {return ZUI_Width(iElement, iWidth * *rZUI_RTime.system.w);}
ZUI_ELEMENT* ZUI_HeightRelative(ZUI_ELEMENT* iElement, ZT_DBL iHeight) {return ZUI_Height(iElement, iHeight * *rZUI_RTime.system.h);}
ZUI_ELEMENT* ZUI_SizeRelative(ZUI_ELEMENT* iElement, ZT_DBL iWidth, ZT_DBL iHeight) {return ZUI_SizeFromInteger(iElement, iWidth * *rZUI_RTime.system.w, iHeight * *rZUI_RTime.system.h);}
ZUI_ELEMENT* ZUI_RectRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY, ZT_DBL iWidth, ZT_DBL iHeight) {
	ZUI_SizeFromInteger(iElement, iWidth * *rZUI_RTime.system.w, iHeight * *rZUI_RTime.system.h);
	return ZUI_PosFromInteger(iElement, iX * *rZUI_RTime.system.w, iY * *rZUI_RTime.system.h);
}
ZUI_ELEMENT* ZUI_RectCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY, ZT_DBL iWidth, ZT_DBL iHeight) {
	ZUI_SizeFromInteger(iElement, iWidth * *rZUI_RTime.system.w, iHeight * *rZUI_RTime.system.h);
	return ZUI_PosCenterFromInteger(iElement, iX * *rZUI_RTime.system.w, iY * *rZUI_RTime.system.h);
}
ZUI_ELEMENT* ZUI_Font(ZUI_ELEMENT* iElement, ZT_FONT* iFont) {((rZUI_ELEMENT*)iElement)->UI.font = iFont; return iElement;}
ZUI_ELEMENT* ZUI_BorderSize(ZUI_ELEMENT* iElement, ZT_INDEX iBorderSize) {((rZUI_ELEMENT*)iElement)->UI.border = iBorderSize; return iElement;}
ZUI_ELEMENT* ZUI_Source(ZUI_ELEMENT* iElement, ZT_FLAG iUIS, const void* iSource) {ZUI_UISource(iElement, iUIS, iSource); return iElement;}
ZUI_ELEMENT* ZUI_Color(ZUI_ELEMENT* iElement, ZT_FLAG iUIS, const ZUI_COLOR* iColor) {ZUI_UIColor(iElement, iUIS, iColor); return iElement;}

#endif // ZUI_C_INCLUDED
