/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI__ELEMENT_C_INCLUDED
#define ZUI__ELEMENT_C_INCLUDED

#include "ZUI__Runtime.h"

ZT_FLAG ZUI_ElementFlagGetMask(ZT_FLAG iType) {
    switch(iType) {
        case ZUI_ELEMENT_TYPE_BOX: return ZUI_ELEMENT_FLAG_BOX;
        case ZUI_ELEMENT_TYPE_BUTTON: return ZUI_ELEMENT_FLAG_BUTTON;
        case ZUI_ELEMENT_TYPE_LABEL: return ZUI_ELEMENT_FLAG_LABEL;
        case ZUI_ELEMENT_TYPE_COUNTER: return ZUI_ELEMENT_FLAG_COUNTER;
        case ZUI_ELEMENT_TYPE_SWITCH: return ZUI_ELEMENT_FLAG_SWITCH;
        default: return ZUI_ELEMENT_FLAG_NONE;
    }
}
void ZUI_ElementFlagAppend(ZUI_HOST_ELEMENT* iElement, ZT_FLAG iFlag) {
    if (iElement != NULL) {
        if (iElement->trunk != NULL) {
            if (iElement->trunk->branch != NULL) {
                for (ZT_INDEX i = 0; i < iElement->trunk->number; i++) {
                    ZUI_ElementFlagAppend(iElement->trunk->branch[i], iFlag);
                }
            }
        }
        if (iElement->root != NULL) {
            switch (iElement->root->type) {
                case ZUI_ELEMENT_TYPE_SWITCH: if (((0x1 << (iElement->id.S >> 1)) & ((ZT_INDEX)iElement->root->data->value ^ ((iElement->id.S & 0x1) << (iElement->id.S >> 1))))) {return;} else {break;}
                default: break;
            }
        }
        iElement->flag |= iFlag & ZUI_ElementFlagGetMask(iElement->type);
    }
}
void ZUI_ElementFlagRemove(ZUI_HOST_ELEMENT* iElement, ZT_FLAG iFlag) {
    if (iElement != NULL) {
        if (iElement->trunk != NULL) {
            if (iElement->trunk->branch != NULL) {
                for (ZT_INDEX i = 0; i < iElement->trunk->number; i++) {
                    ZUI_ElementFlagRemove(iElement->trunk->branch[i], iFlag);
                }
            }
        }
        iElement->flag &= ~(iFlag & ZUI_ElementFlagGetMask(iElement->type));
    }
}
void ZUI_ElementEvent(ZUI_HOST_ELEMENT* iElement) {
    if (gZUI_RTime != NULL && iElement != NULL) {
        if (iElement->flag & ZUI_ELEMENT_FLAG_COLLIDE) {
            ZT_FLAG lAID = ZTK_AID_NONE;
            ZT_FLAG lEID = ZTK_EID_NONE;
            if (ZTM_PointWithinRect(&(gZT_Window->system.input.mouse.pos), &(iElement->rect))) {
                ZT_BOOL lMouseDown = ((gZT_Window->system.input.mouse.state & ZTK_SID_MOUSE_LBUTTON) ? ZT_TRUE : ZT_FALSE);
                if (gZUI_RTime->element.focus == iElement) {
                        lAID |= ZTK_AID_MOVE;
                        lAID |= ZTK_AID_Press(((iElement->id.A & ZTK_AID_PRESS) ? ZT_TRUE : ZT_FALSE), lMouseDown);
                } else {
                    if (!lMouseDown) {lAID |= ZTK_AID_MOVE;}
                }
                if ((lAID & ZTK_AID_CLICK) || ((lAID ^ iElement->id.A) & ZTK_AID_CLICK)) {
                    if (lAID & ZTK_AID_RELEASE) {
                        lEID = ZTK_EID_GUI_RELEASE;
                    } else if (lAID & ZTK_AID_DOUBLE) {
                        lEID = ZTK_EID_GUI_DOUBLE;
                    } else if (lAID & ZTK_AID_STRIKE) {
                        lEID = ZTK_EID_GUI_STRIKE;
                    } else if (lAID & ZTK_AID_PRESS) {
                        lEID = ZTK_EID_GUI_PRESS;
                    }
                } else if (lAID & ZTK_AID_MOVE) {
                    lEID = ZTK_EID_GUI_HOVER_ON;
                }
            } else if (iElement->id.A & ZTK_AID_MOVE) {
                lEID = ZTK_EID_GUI_HOVER_OFF;
            }
            iElement->id.A = lAID;
            if ((iElement->id.E = lEID)) {
                ZT_FLAG lHS = iElement->id.device;
                if (iElement->root != NULL) {
                    lHS = iElement->root->id.device;
                    if (lAID & ZTK_AID_RELEASE) {
                        switch(iElement->root->type) {
                            case ZUI_ELEMENT_TYPE_COUNTER:
                                if (iElement->id.S & 0x1) {
                                    ZUI_ElementDataIncrement(iElement->root->data, ZTM_Exp(iElement->id.S >> 1));
                                } else {
                                    ZUI_ElementDataDecrement(iElement->root->data, ZTM_Exp(iElement->id.S >> 1));
                                }
                                break;
                            case ZUI_ELEMENT_TYPE_SWITCH:
                                ZUI_Bury(iElement);
                                if (iElement->id.S & 0x1) {
                                    ZUI_ElementDataDecrement(iElement->root->data, 0x1 << (iElement->id.S >> 1));
                                    ZUI_Restore(iElement->root->trunk->branch[iElement->id.S & ~0x1]);
                                } else {
                                    ZUI_ElementDataIncrement(iElement->root->data, 0x1 << (iElement->id.S >> 1));
                                    ZUI_Restore(iElement->root->trunk->branch[iElement->id.S | 0x1]);
                                }
                                break;
                            default: break;
                        }
                    }
                }
                ZT_EVENT* lEvent = ZTM_QListAdvanceItem(gZUI_RTime->event.buffer);
                lEvent->id.device = lHS;
                lEvent->id.A = lAID;
                lEvent->id.E = lEID;
                lEvent->data.d0 = gZT_Window->system.input.mouse.pos.x;
                lEvent->data.d1 = gZT_Window->system.input.mouse.pos.y;
            }
        }
    }
}
void ZUI_ElementFree(ZUI_HOST_ELEMENT* iElement) {
	if (iElement != NULL) {
		switch (iElement->type) {
			default: break;
		}
		ZUI_UIFree(iElement);
		ZUI_ElementDataFree(iElement->data);
		ZUI_ElementTrunkFree(iElement->trunk);
		ZTM8_Free(iElement);
	}
}
ZUI_HOST_ELEMENT* ZUI_ElementZero(ZUI_HOST_ELEMENT* iElement) {
    if (iElement != NULL) {
		iElement->id.H = ZTK_HID_GUI;
		iElement->id.S = ZTK_SID_NONE;
		iElement->id.A = ZTK_AID_NONE;
		iElement->id.E = ZTK_EID_NONE;
		iElement->data = NULL;
		iElement->root = NULL;
		iElement->trunk = NULL;
		iElement->flag = ZUI_ELEMENT_FLAG_NONE;
		iElement->type = ZUI_ELEMENT_TYPE_NONE;
		iElement->style = ZUI_ELEMENT_STYLE_NONE;
		ZTM_RectZero(&(iElement->rect));
		ZUI_UIZero(iElement);
    }
    return iElement;
}
ZUI_HOST_ELEMENT* ZUI_ElementNew(ZT_FLAG iSID, ZT_FLAG iType, const ZT_RECT* iRect) {
    ZUI_HOST_ELEMENT* lElement = NULL;
    if ((lElement = ZUI_ElementZero((ZUI_HOST_ELEMENT*)ZTM8_New(sizeof(ZUI_HOST_ELEMENT)))) != NULL) {
        if (ZUI_HostRegister(lElement)) {
            lElement->id.S = iSID;
            lElement->type = iType;
            lElement->style = ZUI_DEFAULT_STYLE;
            ZUI_ElementFlagAppend(lElement, ZUI_DEFAULT_ELEMENT_FLAG);
            if (iRect != NULL) {ZTM_RectCopy(iRect, &(lElement->rect));}
            return lElement;
        }
        ZTM8_Free(lElement);
    }
	return NULL;
}
void ZUI_ElementDraw(ZUI_HOST_ELEMENT* iElement) {
	if (iElement != NULL) {
	    if (iElement->flag & ZUI_ELEMENT_FLAG_SHOW) {
            ZUI_UIState(iElement);
            ZUI_UIDraw(iElement);
	    }
	}
}
void ZUI_ElementTrunkFree(ZUI_HOST_ELEMENT_TRUNK* iTrunk) {
    if (iTrunk != NULL) {
        if (iTrunk->branch != NULL) {ZTM8_Free(iTrunk->branch);}
        ZTM8_Free(iTrunk);
    }
}
ZUI_HOST_ELEMENT_TRUNK* ZUI_ElementTrunkZero(ZUI_HOST_ELEMENT_TRUNK* iTrunk) {
    if (iTrunk != NULL) {
        iTrunk->branch = NULL;
        iTrunk->number = 0;
        iTrunk->flag = ZUI_ELEMENT_TRUNK_FLAG_NONE;
        iTrunk->type = ZUI_ELEMENT_TRUNK_TYPE_NONE;
    }
    return iTrunk;
}
ZUI_HOST_ELEMENT_TRUNK* ZUI_ElementTrunkNewZero(void) {
    return ZUI_ElementTrunkZero((ZUI_HOST_ELEMENT_TRUNK*)ZTM8_New(sizeof(ZUI_HOST_ELEMENT_TRUNK)));
}
ZUI_HOST_ELEMENT_TRUNK* ZUI_ElementTrunkNew(ZT_INDEX iBranches, ZT_FLAG iFlags, ZT_FLAG iType) {
    ZUI_HOST_ELEMENT_TRUNK* lTrunk = NULL;
    if ((lTrunk = ZUI_ElementTrunkNewZero()) != NULL) {
        if ((lTrunk->number = iBranches)) {
            if ((lTrunk->branch = (ZUI_HOST_ELEMENT**)ZTM8_New(sizeof(ZUI_HOST_ELEMENT*) * lTrunk->number)) != NULL) {
                for (ZT_INDEX i = 0; i < lTrunk->number; i++) {lTrunk->branch[i] = NULL;}
                lTrunk->flag = iFlags;
                lTrunk->type = iType;
                return lTrunk;
            }
            ZTM8_Free(lTrunk->branch);
        }
        ZTM8_Free(lTrunk);
    }
    return NULL;
}
ZUI_HOST_ELEMENT_TRUNK* ZUI_ElementTrunkRoot(ZUI_HOST_ELEMENT_TRUNK* iTrunk, ZUI_HOST_ELEMENT* iRoot) {
    if (iTrunk != NULL) {
        if (iTrunk->branch != NULL) {
            for (ZT_INDEX i = 0; i < iTrunk->number; i++) {if (iTrunk->branch[i] != NULL) {iTrunk->branch[i]->root = iRoot;}}
        }
    }
    return iTrunk;
}
void ZUI_ElementDataFree(ZUI_HOST_ELEMENT_DATA* iData) {
    if (iData != NULL) {
        ZTM8_Free(iData);
    }
}
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataZero(ZUI_HOST_ELEMENT_DATA* iData) {
    if (iData != NULL) {
        iData->value = NULL;
        iData->unit = NULL;
        iData->minimum = NULL;
        iData->maximum = NULL;
        iData->flag = ZUI_ELEMENT_DATA_FLAG_NONE;
        iData->type = ZUI_ELEMENT_DATA_TYPE_NONE;
    }
    return iData;
}
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataNewZero(void) {
    return ZUI_ElementDataZero((ZUI_HOST_ELEMENT_DATA*)ZTM8_New(sizeof(ZUI_HOST_ELEMENT_DATA)));
}
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataNew(ZT_FLAG iFlags, ZT_FLAG iType, void* iMin, void* iMax, void* iUnit, void* iValue) {
    ZUI_HOST_ELEMENT_DATA* lData;
    if ((lData = ZUI_ElementDataNewZero()) != NULL) {
        lData->flag = iFlags;
        switch((lData->type = iType)) {
            case ZUI_ELEMENT_DATA_TYPE_INT: {
                    lData->unit = iUnit;
                    ZT_I lMin = (ZT_I)(lData->minimum = iMin);
                    ZT_I lMax = (ZT_I)(lData->maximum = iMax);
                    ZT_I lVal = (ZT_I)iValue;
                    if (lVal > lMax) {lVal = lMax;} else if (lVal < lMin) {lVal = lMin;}
                    lData->value = (void*)lVal;
                }
                break;
            case ZUI_ELEMENT_DATA_TYPE_UINT: {
                    lData->unit = iUnit;
                    ZT_U lMin = (ZT_U)(lData->minimum = iMin);
                    ZT_U lMax = (ZT_U)(lData->maximum = iMax);
                    ZT_U lVal = (ZT_U)iValue;
                    if (lVal > lMax) {lVal = lMax;} else if (lVal < lMin) {lVal = lMin;}
                    lData->value = (void*)lVal;
                }
                break;
            default:
                lData->maximum = iMax;
                lData->minimum = iMin;
                lData->unit = iUnit;
                lData->value = iValue;
                break;
        }
    }
    return lData;
}
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataValue(ZUI_HOST_ELEMENT_DATA* iData, ZT_FLAG iValue) {
    if (iData != NULL) {
        switch(iData->type) {
            case ZUI_ELEMENT_DATA_TYPE_INT: {
                    ZT_I lMax = (ZT_I)iData->maximum;
                    ZT_I lMin = (ZT_I)iData->minimum;
                    ZT_I lVal = (ZT_I)iValue;
                    if (lVal > lMax) {lVal = lMax;} else if (lVal < lMin) {lVal = lMin;}
                    iData->value = (void*)lVal;
                }
                break;
            case ZUI_ELEMENT_DATA_TYPE_UINT: {
                    ZT_U lMax = (ZT_U)iData->maximum;
                    ZT_U lMin = (ZT_U)iData->minimum;
                    ZT_U lVal = (ZT_U)iValue;
                    if (lVal > lMax) {lVal = lMax;} else if (lVal < lMin) {lVal = lMin;}
                    iData->value = (void*)lVal;
                }
                break;
            default: break;
        }
    }
    return iData;
}
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataMaximum(ZUI_HOST_ELEMENT_DATA* iData, ZT_FLAG iMaximum) {
    if (iData != NULL) {
        switch(iData->type) {
            case ZUI_ELEMENT_DATA_TYPE_INT: {
                    ZT_I lMax = (ZT_I)iMaximum;
                    ZT_I lVal = (ZT_I)iData->value;
                    if (lVal > lMax) {iData->value = (void*)(ZT_I)iMaximum;}
                }
                break;
            case ZUI_ELEMENT_DATA_TYPE_UINT: {
                    ZT_U lMax = (ZT_U)iMaximum;
                    ZT_U lVal = (ZT_U)iData->value;
                    if (lVal > lMax) {iData->value = (void*)(ZT_U)iMaximum;}
                }
                break;
            default: break;
        }
        iData->maximum = (void*)iMaximum;
    }
    return iData;
}
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataMinimum(ZUI_HOST_ELEMENT_DATA* iData, ZT_FLAG iMinimum) {
    if (iData != NULL) {
        switch(iData->type) {
            case ZUI_ELEMENT_DATA_TYPE_INT: {
                    ZT_I lMin = (ZT_I)iMinimum;
                    ZT_I lVal = (ZT_I)iData->value;
                    if (lVal < lMin) {iData->value = (void*)(ZT_I)iMinimum;}
                }
                break;
            case ZUI_ELEMENT_DATA_TYPE_UINT: {
                    ZT_U lMin = (ZT_U)iMinimum;
                    ZT_U lVal = (ZT_U)iData->value;
                    if (lVal < lMin) {iData->value = (void*)(ZT_U)iMinimum;}
                }
                break;
            default: break;
        }
        iData->minimum = (void*)iMinimum;
    }
    return iData;
}
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataUnit(ZUI_HOST_ELEMENT_DATA* iData, ZT_FLAG iUnit) {
    if (iData != NULL) {
        iData->unit = (void*)iUnit;
    }
    return iData;
}
/*ZT_FLAG ZUI_ElementDataGetValue(ZUI_HOST_ELEMENT_DATA* iData) {
    if (iData != NULL) {
        return (ZT_FLAG)iData->value;
    }
    return 0x0;
}
ZT_FLAG ZUI_ElementDataGetMaximum(ZUI_HOST_ELEMENT_DATA* iData) {
    if (iData != NULL) {
        return (ZT_FLAG)iData->maximum;
    }
    return 0x0;
}
ZT_FLAG ZUI_ElementDataGetMinimum(ZUI_HOST_ELEMENT_DATA* iData) {
    if (iData != NULL) {
        return (ZT_FLAG)iData->minimum;
    }
    return 0x0;
}
ZT_FLAG ZUI_ElementDataGetUnit(ZUI_HOST_ELEMENT_DATA* iData) {
    if (iData != NULL) {
        return (ZT_FLAG)iData->unit;
    }
    return 0x0;
}*/
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataIncrement(ZUI_HOST_ELEMENT_DATA* iData, ZT_INDEX iAmount) {
    if (iData != NULL) {
        switch (iData->type) {
            case ZUI_ELEMENT_DATA_TYPE_UINT: {
                    ZT_U lMin = (ZT_U)iData->minimum;
                    ZT_U lMax = (ZT_U)iData->maximum;
                    ZT_U lAmount = ((ZT_U)iData->unit * (ZT_U)iAmount) % (1 + lMax - lMin);
                    ZT_U lValue = (ZT_U)iData->value;
                    if (lValue + lAmount > lMax) {
                        if (iData->flag & ZUI_ELEMENT_DATA_FLAG_OVERFLOW) {
                            lValue = lMin + (lAmount - (lMax - lValue) - 1);
                        } else {
                            lValue = lMax;
                        }
                    } else {
                        lValue += lAmount;
                    }
                    iData->value = (void*)lValue;
                }
                break;
            case ZUI_ELEMENT_DATA_TYPE_INT: {
                    ZT_I lMin = (ZT_I)iData->minimum;
                    ZT_I lMax = (ZT_I)iData->maximum;
                    ZT_I lAmount = (ZT_I)iData->unit * (ZT_I)iAmount;
                    ZT_U lRange = ((lMax < lMin) ? (lMin - lMax) : (lMax - lMin)) + 1;
                    if (lAmount < 0) {lAmount *= -1; lAmount %= lRange; lAmount *= -1;} else {lAmount %= lRange;}
                    ZT_I lValue = (ZT_I)iData->value;
                    if (lValue + lAmount > lMax) {
                        if (iData->flag & ZUI_ELEMENT_DATA_FLAG_OVERFLOW) {
                            lValue = lMin + (lAmount - (lMax - lValue) - 1);
                        } else {
                            lValue = lMax;
                        }
                    } else {
                        lValue += lAmount;
                    }
                    iData->value = (void*)lValue;
                }
                break;
            default:
                break;
        }
    }
    return iData;
}
ZUI_HOST_ELEMENT_DATA* ZUI_ElementDataDecrement(ZUI_HOST_ELEMENT_DATA* iData, ZT_INDEX iAmount) {
    if (iData != NULL) {
        switch (iData->type) {
            case ZUI_ELEMENT_DATA_TYPE_UINT: {
                    ZT_U lMin = (ZT_U)iData->minimum;
                    ZT_U lMax = (ZT_U)iData->maximum;
                    ZT_U lAmount = ((ZT_U)iData->unit * (ZT_U)iAmount) % (1 + lMax - lMin);
                    ZT_U lValue = (ZT_U)iData->value;
                    if (lValue < lAmount || (lValue - lAmount) < lMin) {
                        if (iData->flag & ZUI_ELEMENT_DATA_FLAG_OVERFLOW) {
                            lValue = lMax - (lAmount - (lValue - lMin) - 1);
                        } else {
                            lValue = lMin;
                        }
                    } else {
                        lValue -= lAmount;
                    }
                    iData->value = (void*)lValue;
                }
                break;
            case ZUI_ELEMENT_DATA_TYPE_INT: {
                    ZT_I lMin = (ZT_I)iData->minimum;
                    ZT_I lMax = (ZT_I)iData->maximum;
                    ZT_I lAmount = (ZT_I)iData->unit * (ZT_I)iAmount;
                    ZT_U lRange = ((lMax < lMin) ? (lMin - lMax) : (lMax - lMin)) + 1;
                    if (lAmount < 0) {lAmount *= -1; lAmount %= lRange; lAmount *= -1;} else {lAmount %= lRange;}
                    ZT_I lValue = (ZT_I)iData->value;
                    if ((lValue - lAmount) < lMin) {
                        if (iData->flag & ZUI_ELEMENT_DATA_FLAG_OVERFLOW) {
                            lValue = lMax - (lAmount - (lValue - lMin) - 1);
                        } else {
                            lValue = lMin;
                        }
                    } else {
                        lValue -= lAmount;
                    }
                    iData->value = (void*)lValue;
                }
                break;
            default:
                break;
        }
    }
    return iData;
}

#endif // ZUI__ELEMENT_C_INCLUDED
