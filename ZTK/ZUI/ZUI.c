/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_C_INCLUDED
#define ZUI_C_INCLUDED

#include "ZUI/ZUI__Runtime.h"

ZUI_HOST* gZUI_RTime = NULL;

void ZUI_HostElementsPurge(void) {
	if (gZUI_RTime != NULL) {
		if (gZUI_RTime->element.registry != NULL) {
            for (ZT_INDEX i = 0; i < gZUI_RTime->element.length; i++) {
                if (gZUI_RTime->element.registry->items[i] != NULL) {
                    ZUI_ElementFree((ZUI_HOST_ELEMENT*)(gZUI_RTime->element.registry->items[i]));
                    gZUI_RTime->element.registry->items[i] = NULL;
                }
            }
            gZUI_RTime->element.length = 0;
		}
    }
}
void ZUI_HostElementsFree(void) {
	if (gZUI_RTime != NULL) {
		if (gZUI_RTime->element.registry != NULL) {
            ZUI_HostElementsPurge();
			ZTM_ListFree(gZUI_RTime->element.registry);
			gZUI_RTime->element.registry = NULL;
		}
	}
}
void ZUI_HostElementsCreate(ZT_INDEX iSize) {
	if (gZUI_RTime != NULL) {
		ZT_LIST* lNew = NULL;
		if ((lNew = ZTM_ListNew(iSize)) != NULL) {
            ZT_INDEX lLength = gZUI_RTime->element.length;
			if (gZUI_RTime->element.registry != NULL) {
				ZTM_ListCopy(gZUI_RTime->element.registry, lNew);
				ZUI_HostElementsFree();
			}
			gZUI_RTime->element.registry = lNew;
            gZUI_RTime->element.length = lLength;
		}
	}
}
void ZUI_HostEventsFree(void) {
	if (gZUI_RTime != NULL) {
		if (gZUI_RTime->event.buffer != NULL) {
            if ((gZUI_RTime->event.buffer->items)[0] != NULL) {
                ZTM8_Free((gZUI_RTime->event.buffer->items)[0]);
            }
			ZTM_QListFree(gZUI_RTime->event.buffer);
			gZUI_RTime->event.buffer = NULL;
			gZUI_RTime->event.last = NULL;
		}
	}
}
void ZUI_HostEventsCreate(ZT_INDEX iSize) {
	if (gZUI_RTime != NULL) {
        ZUI_HostEventsFree();
		if ((gZUI_RTime->event.buffer = ZTM_QListNew(iSize)) != NULL) {
            ZT_INDEX lSize = sizeof(ZT_EVENT);
            if (lSize % 8) {lSize += 8 - (lSize % 8);}
            void* lMemBlock = (void*)ZTM8_New(lSize * gZUI_RTime->event.buffer->length);
            if (lMemBlock != NULL) {for (ZT_INDEX i = 0; i < gZUI_RTime->event.buffer->length; i++) {(gZUI_RTime->event.buffer->items)[i] = (lMemBlock + i * lSize);}}
		}
	}
}
const ZUI_HOST_ELEMENT* ZUI_HostFocusMouse(void) {
    if (gZUI_RTime != NULL) {
        for (ZT_INDEX i = (gZUI_RTime->element.length - 1); i < gZUI_RTime->element.length; i--) {
            const ZUI_HOST_ELEMENT* lElement = gZUI_RTime->element.registry->items[i];
            if (lElement->flag & ZUI_ELEMENT_FLAG_COLLIDE) {
                if (!(lElement->flag & ZUI_ELEMENT_FLAG_DISABLE)) {
                    if (ZTM_PointWithinRect(&(gZT_Window->system.input.mouse.pos), &(lElement->rect))) {
                        return lElement;
                    }
                }
            }
        }
    }
    return NULL;
}
void ZUI_HostEventsPump(const ZT_EVENT* iEvent) {
    if (gZUI_RTime != NULL && iEvent != NULL) {
        if (gZUI_RTime->event.last != iEvent) {
            gZUI_RTime->event.last = iEvent;
            switch (iEvent->id.H) {
                case ZTK_HID_MOUSE: if ((iEvent->id.S == ZTK_SID_MOUSE_LBUTTON) && (iEvent->id.A & ZTK_AID_STRIKE)) {gZUI_RTime->element.focus = ZUI_HostFocusMouse();} break;
                default: return;
            }
            for (ZT_INDEX i = 0; i < gZUI_RTime->element.length; i++) {
                ZUI_HOST_ELEMENT* lElement = (ZUI_HOST_ELEMENT*)(gZUI_RTime->element.registry->items)[i];
                ZUI_ElementEvent(lElement);
            }
        }
    }
}
ZT_INDEX ZUI_HostPoll(const ZT_EVENT* iEvent, ZT_EVENT** oGUIEvent) {
    if (gZUI_RTime != NULL) {
        gZUI_RTime->timestamp.now = ZTK_GetTicks();
        if (gZUI_RTime->flag & ZUI_FLAG_FLUSH) {
            ZUI_HostEventsPump(iEvent);
            gZUI_RTime->flag &= (~ZUI_FLAG_FLUSH);
        }
        if (ZTM_QListQueued(gZUI_RTime->event.buffer)) {
            return ZTM_QListPoll(gZUI_RTime->event.buffer, (void**)oGUIEvent);
        } else {
            gZUI_RTime->flag |= ZUI_FLAG_FLUSH;
        }
    }
    return 0;
}
void ZUI_HostFree(void) {
	if (gZUI_RTime != NULL) {
        ZUI_HostEventsFree();
		ZUI_HostElementsFree();
		ZTM8_Free(gZUI_RTime);
		gZUI_RTime = NULL;
	}
}
void ZUI_HostNew(void) {
	if (gZUI_RTime == NULL && gZT_Window != NULL) {
		if ((gZUI_RTime = (ZUI_HOST*)ZTM8_New(sizeof(ZUI_HOST))) != NULL) {
			gZUI_RTime->event.buffer = NULL;
			gZUI_RTime->event.last = NULL;
			gZUI_RTime->element.registry = NULL;
			gZUI_RTime->element.length = 0;
			gZUI_RTime->element.focus = NULL;
			gZUI_RTime->flag = ZUI_DEFAULT_FLAG;
            #if ZUI_COLOR_MOD_SEED > 0
			gZUI_RTime->seed = ZUI_COLOR_MOD_SEED;
            #else
			gZUI_RTime->seed = ZTM_Time();
			#endif // ZUI_COLOR_MOD_SEED
			gZUI_RTime->timestamp.now = ZTK_GetTicks();
			gZUI_RTime->timestamp.modulator = gZUI_RTime->timestamp.now;
			gZUI_RTime->timestamp.cursor = gZUI_RTime->timestamp.now;
			gZUI_RTime->timeout.modulator = ZUI_COLOR_MOD_PERIOD;
			gZUI_RTime->timeout.cursor = ZUI_CURSOR_PERIOD;
			gZUI_RTime->color.modulator0 = ZUI_HostGetRandomColor();
			gZUI_RTime->color.modulator1 = ZUI_HostGetRandomColor();
			gZUI_RTime->color.cursor = ZUI_COLOR_CURSOR;
			ZUI_HostEventsCreate(ZUI_BUFFER_EVENTS);
		}
	}
}
void ZUI_HostDraw(void) {
	if (gZUI_RTime != NULL) {
		for (ZT_INDEX i = 0; i < gZUI_RTime->element.length; i++) {
            ZUI_ElementDraw(gZUI_RTime->element.registry->items[i]);
		}
	}
}
ZT_BOOL ZUI_HostRegister(ZUI_HOST_ELEMENT* iElement) {
	if ((gZUI_RTime != NULL) && (iElement != NULL)) {
        if (gZUI_RTime->element.registry != NULL) {
            if (!((gZUI_RTime->element.length + 1) < gZUI_RTime->element.registry->length)) {
                ZUI_HostElementsCreate(gZUI_RTime->element.registry->length + ZUI_BUFFER_ELEMENT); // buffer too small - increase size
            }
        } else {
            ZUI_HostElementsCreate(ZUI_BUFFER_ELEMENT); // buffer not present - create buffer
        }
        if (gZUI_RTime->element.registry != NULL && ((gZUI_RTime->element.length + 1) < gZUI_RTime->element.registry->length)) {
            gZUI_RTime->element.registry->items[gZUI_RTime->element.length] = iElement;
            (gZUI_RTime->element.length)++;
            return ((gZUI_RTime->element.registry->items[gZUI_RTime->element.length - 1] != iElement) ? ZT_FALSE : ZT_TRUE);
        }
	}
	return ZT_FALSE;
}
ZT_COLOR ZUI_HostGetRandomColor(void) {
    ZT_COLOR lColor = ZUI_COLOR_NONE;
    if (gZUI_RTime != NULL) {
        for (ZT_INDEX i = 0; i < 3; i++) {
            lColor <<= 8;
            ZT_INDEX lRandom = ZTM_Randomize_32(&gZUI_RTime->seed, 0x100);
            lRandom = (lRandom < ZUI_COLOR_MOD_MIN) ? (ZUI_COLOR_MOD_MAX - (ZUI_COLOR_MOD_MIN - lRandom)) : (lRandom > ZUI_COLOR_MOD_MAX) ? (ZUI_COLOR_MOD_MIN + (lRandom - ZUI_COLOR_MOD_MAX)) : lRandom;
            lColor |= (lRandom & 0xff);
        }
        lColor <<= ZTM_ColorShift(gZT_Window->user.palette);
        lColor |= (0xff << ZTM_ColorAlphaShift(gZT_Window->user.palette));
    }
    return lColor;
}
ZT_COLOR ZUI_HostGetJuicyColor(void) {
    ZT_COLOR lJuicy = ZUI_COLOR_NONE;
    if (gZUI_RTime != NULL) {
        while (!((gZUI_RTime->timestamp.now - gZUI_RTime->timestamp.modulator) < gZUI_RTime->timeout.modulator)) {
            gZUI_RTime->color.modulator0 = gZUI_RTime->color.modulator1;
            gZUI_RTime->color.modulator1 = ZUI_HostGetRandomColor();
            gZUI_RTime->timestamp.modulator += gZUI_RTime->timeout.modulator;
        }
        ZT_I lTimeDelta = (gZUI_RTime->timestamp.now - gZUI_RTime->timestamp.modulator);
        for (ZT_INDEX i = 0; i < 3; i++) {
            lJuicy <<= 8;
            ZT_I lChannelLast = (gZUI_RTime->color.modulator0 >> (i * 8 + 8)) & 0xff;
            ZT_I lChannelTarget = (gZUI_RTime->color.modulator1 >> (i * 8 + 8)) & 0xff;
            ZT_I lChannelNow = lChannelLast + (((lChannelTarget - lChannelLast) * lTimeDelta) / (ZT_I)gZUI_RTime->timeout.modulator); // Must use INT
            lJuicy |= (lChannelNow & 0xff);
        }
        lJuicy <<= ZTM_ColorShift(gZT_Window->user.palette);
        lJuicy |= (0xff << ZTM_ColorAlphaShift(gZT_Window->user.palette));
    }
    return lJuicy;
}

ZT_BOOL ZUI_IsEnabled(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return (((ZUI_HOST_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_DISABLE) ? ZT_FALSE : ZT_TRUE;} return ZT_FALSE;}
ZT_BOOL ZUI_IsVisible(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return (((ZUI_HOST_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_SHOW) ? ZT_TRUE : ZT_FALSE;} return ZT_FALSE;}
ZT_BOOL ZUI_IsIncluded(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return (((ZUI_HOST_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_COLLIDE) ? ZT_TRUE : ZT_FALSE;} return ZT_FALSE;}
ZT_BOOL ZUI_IsRestored(ZUI_ELEMENT* iElement) {return (ZUI_IsIncluded(iElement) && ZUI_IsVisible(iElement)) ? ZT_TRUE : ZT_FALSE;}

ZT_BOOL ZUI_IsDisabled(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return (((ZUI_HOST_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_DISABLE) ? ZT_TRUE : ZT_FALSE;} return ZT_FALSE;}
ZT_BOOL ZUI_IsHidden(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return (((ZUI_HOST_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_SHOW) ? ZT_FALSE : ZT_TRUE;} return ZT_FALSE;}
ZT_BOOL ZUI_IsIgnored(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return (((ZUI_HOST_ELEMENT*)iElement)->flag & ZUI_ELEMENT_FLAG_COLLIDE) ? ZT_FALSE : ZT_TRUE;} return ZT_FALSE;}
ZT_BOOL ZUI_IsBuried(ZUI_ELEMENT* iElement) {return (ZUI_IsIgnored(iElement) && ZUI_IsHidden(iElement)) ? ZT_TRUE : ZT_FALSE;}

void ZUI_Enable(ZUI_ELEMENT* iElement) {ZUI_ElementFlagRemove(iElement, ZUI_ELEMENT_FLAG_DISABLE);}
void ZUI_Show(ZUI_ELEMENT* iElement) {ZUI_ElementFlagAppend(iElement, ZUI_ELEMENT_FLAG_SHOW);}
void ZUI_Include(ZUI_ELEMENT* iElement) {ZUI_ElementFlagAppend(iElement, ZUI_ELEMENT_FLAG_COLLIDE); if (iElement != NULL) {((ZUI_HOST_ELEMENT*)iElement)->id.A = ZTK_AID_NONE;}} // clear previous action
void ZUI_Restore(ZUI_ELEMENT* iElement) {ZUI_Include(iElement); ZUI_Show(iElement);}

void ZUI_Disable(ZUI_ELEMENT* iElement) {ZUI_ElementFlagAppend(iElement, ZUI_ELEMENT_FLAG_DISABLE);}
void ZUI_Hide(ZUI_ELEMENT* iElement) {ZUI_ElementFlagRemove(iElement, ZUI_ELEMENT_FLAG_SHOW);}
void ZUI_Ignore(ZUI_ELEMENT* iElement) {ZUI_ElementFlagRemove(iElement, ZUI_ELEMENT_FLAG_COLLIDE);}
void ZUI_Bury(ZUI_ELEMENT* iElement) {ZUI_ElementFlagRemove(iElement, ZUI_ELEMENT_FLAG_SHOW | ZUI_ELEMENT_FLAG_COLLIDE);}

void ZUI_Update(ZUI_ELEMENT* iElement) {ZUI_Hide(iElement); ZUI_Show(iElement);}

ZT_INDEX ZUI_GetBorderSize(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return ((ZUI_HOST_ELEMENT*)iElement)->UI.border;} return 0;}
ZT_I ZUI_GetX(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return ((ZUI_HOST_ELEMENT*)iElement)->rect.x;} return 0;}
ZT_I ZUI_GetY(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return ((ZUI_HOST_ELEMENT*)iElement)->rect.y;} return 0;}
ZT_I ZUI_GetXCenter(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return ((ZUI_HOST_ELEMENT*)iElement)->rect.x + ((((ZUI_HOST_ELEMENT*)iElement)->rect.w) >> 1);} return 0;}
ZT_I ZUI_GetYCenter(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return ((ZUI_HOST_ELEMENT*)iElement)->rect.y + ((((ZUI_HOST_ELEMENT*)iElement)->rect.h) >> 1);} return 0;}
ZT_I ZUI_GetXRight(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return ((ZUI_HOST_ELEMENT*)iElement)->rect.x + ((ZUI_HOST_ELEMENT*)iElement)->rect.w;} return 0;}
ZT_I ZUI_GetYBottom(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return ((ZUI_HOST_ELEMENT*)iElement)->rect.y + ((ZUI_HOST_ELEMENT*)iElement)->rect.h;} return 0;}
ZT_I ZUI_GetWidth(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return ((ZUI_HOST_ELEMENT*)iElement)->rect.w;} return 0;}
ZT_I ZUI_GetHeight(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return ((ZUI_HOST_ELEMENT*)iElement)->rect.h;} return 0;}
const ZT_RECT* ZUI_GetRect(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return &(((ZUI_HOST_ELEMENT*)iElement)->rect);} return NULL;}
const ZT_FONT* ZUI_GetFont(ZUI_ELEMENT* iElement) {if (iElement != NULL) {return (((ZUI_HOST_ELEMENT*)iElement)->UI.font);} return NULL;}
const ZUI_COLOR* ZUI_GetColor(ZUI_ELEMENT* iElement, ZT_FLAG iUIS) {
    if (iElement != NULL) {
        if (((ZUI_HOST_ELEMENT*)iElement)->UI.type == ZUI_UI_TYPE_GENERIC) {
            ZT_INDEX lIndex = ZUI_UIGenericGetStateIndex(&(((ZUI_HOST_ELEMENT*)iElement)->UI), iUIS);
            if (lIndex < ZTM_BitCount(((ZUI_HOST_ELEMENT*)iElement)->UI.draw & ZUI_UIS_MASK)) {return &(((ZUI_HOST_ELEMENT*)iElement)->UI.colors[lIndex]);}
        }
    }
    return NULL;
}
const void* ZUI_GetSource(ZUI_ELEMENT* iElement, ZT_FLAG iUIS) {
    if (iElement != NULL) {
        if (((ZUI_HOST_ELEMENT*)iElement)->UI.type == ZUI_UI_TYPE_GENERIC) {
            ZT_INDEX lIndex = ZUI_UIGenericGetStateIndex(&(((ZUI_HOST_ELEMENT*)iElement)->UI), iUIS);
            if (lIndex < ZTM_BitCount(((ZUI_HOST_ELEMENT*)iElement)->UI.draw & ZUI_UIS_MASK)) {return ((ZUI_HOST_ELEMENT*)iElement)->UI.sources[lIndex];}
        }
    }
    return NULL;
}
ZT_FLAG ZUI_GetDataValue(ZUI_ELEMENT* iElement) {
    if (iElement != NULL) {
        if (((ZUI_HOST_ELEMENT*)iElement)->data != NULL) {
            return (ZT_FLAG)((ZUI_HOST_ELEMENT*)iElement)->data->value;
        }
    }
    return 0x0;
}
ZUI_ELEMENT* ZUI_DataValue(ZUI_ELEMENT* iElement, ZT_FLAG iValue) {
    if (iElement != NULL) {
        ZUI_ElementDataValue(((ZUI_HOST_ELEMENT*)iElement)->data, iValue);
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_DataMaximum(ZUI_ELEMENT* iElement, ZT_FLAG iMaximum) {
    if (iElement != NULL) {
        ZUI_ElementDataMaximum(((ZUI_HOST_ELEMENT*)iElement)->data, iMaximum);
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_DataMinimum(ZUI_ELEMENT* iElement, ZT_FLAG iMinimum) {
    if (iElement != NULL) {
        ZUI_ElementDataMinimum(((ZUI_HOST_ELEMENT*)iElement)->data, iMinimum);
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_DataUnit(ZUI_ELEMENT* iElement, ZT_FLAG iUnit) {
    if (iElement != NULL) {
        ZUI_ElementDataUnit(((ZUI_HOST_ELEMENT*)iElement)->data, iUnit);
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_X(ZUI_ELEMENT* iElement, ZT_I iX) {
    if (iElement != NULL) {return ZUI_PosFromInteger(iElement, iX, ((ZUI_HOST_ELEMENT*)iElement)->rect.y);}
    return iElement;
}
ZUI_ELEMENT* ZUI_Y(ZUI_ELEMENT* iElement, ZT_I iY) {
    if (iElement != NULL) {return ZUI_PosFromInteger(iElement, ((ZUI_HOST_ELEMENT*)iElement)->rect.x, iY);}
    return iElement;
}
ZUI_ELEMENT* ZUI_Pos(ZUI_ELEMENT* iElement, const ZT_POINT* iPos) {
    if (iPos != NULL) {return ZUI_PosFromInteger(iElement, iPos->x, iPos->y);}
    return iElement;
}
ZUI_ELEMENT* ZUI_PosFromInteger(ZUI_ELEMENT* iElement, ZT_I iX, ZT_I iY) {
    ZUI_HOST_ELEMENT* lElement = (ZUI_HOST_ELEMENT*)iElement;
    if (lElement != NULL) {
        if (lElement->trunk != NULL) {
            if (lElement->trunk->branch != NULL) {
                ZT_I lDeltaX = iX - lElement->rect.x;
                ZT_I lDeltaY = iY - lElement->rect.y;
                lElement->rect.x += lDeltaX;
                lElement->rect.y += lDeltaY;
                for (ZT_INDEX i = 0; i < lElement->trunk->number; i++) {
                    lElement->trunk->branch[i]->rect.x += lDeltaX;
                    lElement->trunk->branch[i]->rect.y += lDeltaY;
                }
            }
        } else {
            lElement->rect.x = iX;
            lElement->rect.y = iY;
        }
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_XCenter(ZUI_ELEMENT* iElement, ZT_I iX) {
    ZUI_HOST_ELEMENT* lElement = iElement;
    if (lElement != NULL) {return ZUI_PosFromInteger(lElement, iX - (lElement->rect.w >> 1), lElement->rect.y);}
    return iElement;
}
ZUI_ELEMENT* ZUI_YCenter(ZUI_ELEMENT* iElement, ZT_I iY) {
    ZUI_HOST_ELEMENT* lElement = iElement;
    if (lElement != NULL) {return ZUI_PosFromInteger(lElement, lElement->rect.x, iY - (lElement->rect.h >> 1));}
    return iElement;
}
ZUI_ELEMENT* ZUI_PosCenter(ZUI_ELEMENT* iElement, const ZT_POINT* iPos) {
    ZUI_HOST_ELEMENT* lElement = iElement;
    if (lElement != NULL && iPos != NULL) {return ZUI_PosFromInteger(lElement, iPos->x - (lElement->rect.w >> 1), iPos->y - (lElement->rect.h >> 1));}
    return iElement;
}
ZUI_ELEMENT* ZUI_PosCenterFromInteger(ZUI_ELEMENT* iElement, ZT_I iX, ZT_I iY) {
    ZUI_HOST_ELEMENT* lElement = iElement;
    if (lElement != NULL) {return ZUI_PosFromInteger(lElement, iX - (lElement->rect.w >> 1), iY - (lElement->rect.h >> 1));}
    return iElement;
}

ZUI_ELEMENT* ZUI_Width(ZUI_ELEMENT* iElement, ZT_I iWidth) {
    if (iElement != NULL) {return ZUI_SizeFromInteger(iElement, iWidth, ((ZUI_HOST_ELEMENT*)iElement)->rect.h);}
    return iElement;
}
ZUI_ELEMENT* ZUI_Height(ZUI_ELEMENT* iElement, ZT_I iHeight) {
    if (iElement != NULL) {return ZUI_SizeFromInteger(iElement, ((ZUI_HOST_ELEMENT*)iElement)->rect.w, iHeight);}
    return iElement;
}
ZUI_ELEMENT* ZUI_Size(ZUI_ELEMENT* iElement, const ZT_POINT* iSize) {
    if (iElement != NULL) {
        ZUI_HOST_ELEMENT* lElement = (ZUI_HOST_ELEMENT*)iElement;
        ZT_POINT lSize;
        if (iSize == NULL) {
            switch (lElement->type) {
                case ZUI_ELEMENT_TYPE_BOX:
                    if (gZT_Window != NULL) {iSize = (const ZT_POINT*)&(gZT_Window->rect.w);}
                    break;
                case ZUI_ELEMENT_TYPE_BUTTON:
                case ZUI_ELEMENT_TYPE_LABEL:
                    if (gZT_Window != NULL) {
                        ZT_INDEX lState = ZUI_UIGenericGetStateIndex(&(lElement->UI), ZUI_UIS_NORMAL);
                        if (lElement->UI.sources != NULL && lState < ZTM_BitCount(ZUI_UIS_ALL)) {
                            if (lElement->UI.sources[lState] != NULL) {
                                ZTK_GetSizeFromFont((const ZT_CHAR*)lElement->UI.sources[lState], lElement->UI.font, &lSize);
                                iSize = (const ZT_POINT*)&lSize;
                            }
                        }
                    }
                    break;
                case ZUI_ELEMENT_TYPE_COUNTER:
                    return ZUI_CounterSize(lElement, NULL);
                case ZUI_ELEMENT_TYPE_SWITCH:
                    return ZUI_SwitchSize(lElement, NULL);
                default:
                    break;
            }
        }
        if (iSize != NULL) {return ZUI_SizeFromInteger(iElement, iSize->x, iSize->y);}
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_SizeFromInteger(ZUI_ELEMENT* iElement, ZT_I iWidth, ZT_I iHeight) {
    if (iElement != NULL) {
        ZUI_HOST_ELEMENT* lElement = (ZUI_HOST_ELEMENT*)iElement;
        ZT_POINT lSize;
        if ((lElement->rect.w != iWidth) || (lElement->rect.h != iHeight))  {
            if (lElement->trunk != NULL) {
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
                        break;
                }
            } else {
                lElement->rect.w = iWidth;
                lElement->rect.h = iHeight;
                ZUI_UISpritesNew(lElement);
            }
        }
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_Rect(ZUI_ELEMENT* iElement, const ZT_RECT* iRect) {
    if (iRect != NULL) {
        ZUI_Pos(iElement, (const ZT_POINT*)&(iRect->x));
        ZUI_Size(iElement, (const ZT_POINT*)&(iRect->w));
    } else {
        ZUI_Size(iElement, NULL);
    }
    return iElement;
}

ZUI_ELEMENT* ZUI_XRelative(ZUI_ELEMENT* iElement, ZT_DBL iX) {
    if (gZT_Window != NULL) {return ZUI_X(iElement, iX * gZT_Window->rect.w);}
    return iElement;
}
ZUI_ELEMENT* ZUI_YRelative(ZUI_ELEMENT* iElement, ZT_DBL iY) {
    if (gZT_Window != NULL) {return ZUI_Y(iElement, iY * gZT_Window->rect.h);}
    return iElement;
}
ZUI_ELEMENT* ZUI_PosRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY) {
    if (gZT_Window != NULL) {return ZUI_PosFromInteger(iElement, iX * gZT_Window->rect.w, iY * gZT_Window->rect.h);}
    return iElement;
}
ZUI_ELEMENT* ZUI_XCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iX) {
    if (gZT_Window != NULL) {return ZUI_XCenter(iElement, iX * gZT_Window->rect.w);}
    return iElement;
}
ZUI_ELEMENT* ZUI_YCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iY) {
    if (gZT_Window != NULL) {return ZUI_YCenter(iElement, iY * gZT_Window->rect.h);}
    return iElement;
}
ZUI_ELEMENT* ZUI_PosCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY) {
    if (gZT_Window != NULL) {return ZUI_PosCenterFromInteger(iElement, iX * gZT_Window->rect.w, iY * gZT_Window->rect.h);}
    return iElement;
}
ZUI_ELEMENT* ZUI_WidthRelative(ZUI_ELEMENT* iElement, ZT_DBL iWidth) {
    if (gZT_Window != NULL) {return ZUI_Width(iElement, iWidth * gZT_Window->rect.w);}
    return iElement;
}
ZUI_ELEMENT* ZUI_HeightRelative(ZUI_ELEMENT* iElement, ZT_DBL iHeight) {
    if (gZT_Window != NULL) {return ZUI_Height(iElement, iHeight * gZT_Window->rect.h);}
    return iElement;
}
ZUI_ELEMENT* ZUI_SizeRelative(ZUI_ELEMENT* iElement, ZT_DBL iWidth, ZT_DBL iHeight) {
    if (gZT_Window != NULL) {return ZUI_SizeFromInteger(iElement, iWidth * gZT_Window->rect.w, iHeight * gZT_Window->rect.h);}
    return iElement;
}
ZUI_ELEMENT* ZUI_RectRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY, ZT_DBL iWidth, ZT_DBL iHeight) {
    if (gZT_Window != NULL) {
        ZUI_SizeFromInteger(iElement, iWidth * gZT_Window->rect.w, iHeight * gZT_Window->rect.h);
        return ZUI_PosFromInteger(iElement, iX * gZT_Window->rect.w, iY * gZT_Window->rect.h);
    }
    return iElement;
}
ZUI_ELEMENT* ZUI_RectCenterRelative(ZUI_ELEMENT* iElement, ZT_DBL iX, ZT_DBL iY, ZT_DBL iWidth, ZT_DBL iHeight) {
    if (gZT_Window != NULL) {
        ZUI_SizeFromInteger(iElement, iWidth * gZT_Window->rect.w, iHeight * gZT_Window->rect.h);
        return ZUI_PosCenterFromInteger(iElement, iX * gZT_Window->rect.w, iY * gZT_Window->rect.h);
    }
    return iElement;
}

ZUI_ELEMENT* ZUI_Font(ZUI_ELEMENT* iElement, ZT_FONT* iFont) {if (iElement != NULL) {((ZUI_HOST_ELEMENT*)iElement)->UI.font = iFont;} return iElement;}
ZUI_ELEMENT* ZUI_BorderSize(ZUI_ELEMENT* iElement, ZT_INDEX iBorderSize) {if (iElement != NULL) {((ZUI_HOST_ELEMENT*)iElement)->UI.border = iBorderSize;} return iElement;}
ZUI_ELEMENT* ZUI_Source(ZUI_ELEMENT* iElement, ZT_FLAG iUIS, const void* iSource) {ZUI_UISource((ZUI_HOST_ELEMENT*)iElement, iUIS, iSource); return iElement;}
ZUI_ELEMENT* ZUI_Color(ZUI_ELEMENT* iElement, ZT_FLAG iUIS, const ZUI_COLOR* iColor) {ZUI_UIColor((ZUI_HOST_ELEMENT*)iElement, iUIS, iColor); return iElement;}

#endif // ZUI_C_INCLUDED
