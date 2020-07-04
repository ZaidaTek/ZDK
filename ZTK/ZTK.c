/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_C_INCLUDED
#define ZTK_C_INCLUDED

#include "ZTK/ZTK__Runtime.h"

ZT_WINDOW* gZT_Window = NULL;

// PUBLIC FUNCTIONS
ZT_BOOL ZTK_HostTimeout(const ZT_TIME* iLast, ZT_TIME iNow, ZT_TIME iTimeout) {
    return ((iLast != NULL) ? (((iNow - *iLast) > iTimeout) ? ZT_TRUE : ZT_FALSE) : ZT_FALSE);
}
void ZTK_HostTimeoutReset(ZT_TIME* iLast, ZT_TIME iNow, ZT_TIME iTimeout) {
    if (iLast != NULL) {
        *iLast = iNow - ((iNow - *iLast) % (iTimeout + 1));
    }
}
ZT_BOOL ZTK_Timeout(const ZT_TIME* iLast, ZT_TIME iTimeout) {
    return ZTK_HostTimeout(iLast, gZT_Window->system.timer.loopNow, iTimeout);
}
void ZTK_TimeoutReset(ZT_TIME* iLast, ZT_TIME iTimeout) {
    ZTK_HostTimeoutReset(iLast, gZT_Window->system.timer.loopNow, iTimeout);
}
ZT_TIME ZTK_GetTicks(void) {
    if (gZT_Window != NULL) {return gZT_Window->system.timer.loopNow;} else {return 0;}
}
ZT_BOOL ZTK_Repeat(ZT_TIME iTimeout) {
    if (gZT_Window != NULL) {
        if (ZTK_Timeout(&(gZT_Window->system.timer.repeater), iTimeout)) {
            ZTK_TimeoutReset(&(gZT_Window->system.timer.repeater), iTimeout);
            return ZT_TRUE;
        }
    }
    return ZT_FALSE;
}
// MAIN FUNCTIONS
void ZTK_Close(void) {
	if (gZT_Window != NULL) {
		if (gZT_Window->system.state & ZTK_WINDOW_STATE_EXITING) {
            ZTK_Destroy();
		}
	}
}
void ZTK_Quit(void) {
	if (gZT_Window != NULL) {
		ZTK_MSG_Close();
	}
}
void ZTK_New(const ZT_CHAR* iTitle, const ZT_RECT* iRect, const ZT_CHAR* iIcon) {
	if (!(gZT_Window != NULL)) {
		if ((gZT_Window = (ZT_WINDOW*)ZTM8_Init(sizeof(ZT_WINDOW), 0x0)) != NULL) {
			ZTK_EventBufferCreate();
			ZTK_DrawBufferCreate();
			gZT_Window->system.loop = NULL;
			gZT_Window->system.runtime = NULL;
			gZT_Window->system.state = ZTK_WINDOW_STATE_NONE;
			gZT_Window->system.type = ZTK_WINDOW_TYPE_COMPILED;
			gZT_Window->system.timer.flag = ZTK_DEFAULT_WINDOW_IDLE_FLAG;
			gZT_Window->system.timer.resolution = ZTK_DEFAULT_WINDOW_TIME_RESOLUTION;
			gZT_Window->system.timer.heartbeat = ZTK_DEFAULT_WINDOW_IDLE_HOLDOFF;
			gZT_Window->system.timer.idleHoldoff = ZTK_DEFAULT_WINDOW_IDLE_HOLDOFF;
			gZT_Window->system.timer.eventMin = ZTK_DEFAULT_WINDOW_TIME_BASE;
			gZT_Window->system.input.flag = ZTK_DEFAULT_WINDOW_INPUT_FLAG;
			gZT_Window->system.font.window.runtime = NULL;
			gZT_Window->system.font.window.source = ZTK_DEFAULT_WINDOW_TEXT_FONT_SOURCE;
			gZT_Window->system.font.window.name = (ZT_CHAR*)ZTK_DEFAULT_WINDOW_TEXT_FONT;
			gZT_Window->system.font.window.type = ZTK_DEFAULT_WINDOW_TEXT_FONT_TYPE;
			gZT_Window->system.font.window.flag = ZTK_DEFAULT_WINDOW_TEXT_FLAG;
			gZT_Window->system.font.window.height = ZTK_DEFAULT_WINDOW_TEXT_SIZE;
			gZT_Window->system.font.window.style = ZTK_DEFAULT_WINDOW_TEXT_STYLE;
			gZT_Window->system.font.window.color = ZTK_DEFAULT_WINDOW_TEXT_COLOR;
			gZT_Window->system.font.window.colorBk = ZTM_ColorComplementary(ZTK_DEFAULT_WINDOW_TEXT_COLOR); // add alpha full-channel, not sure if system or system_input macro...
			ZTK_Title(iTitle);
			gZT_Window->user.options = ZTK_DEFAULT_WINDOW_BACKGROUND_FLAG;
			gZT_Window->user.icon = (ZT_CHAR*)iIcon;//(ZT_CHAR*)ZTK_DEFAULT_WINDOW_ICON;
			gZT_Window->user.palette = ZTK_DEFAULT_PALETTE_USER;
			gZT_Window->user.background = ZTK_DEFAULT_WINDOW_BACKGROUND_COLOR;
			gZT_Window->user.font = NULL;//&(gZT_Window->system.font.window);
			if (iRect != NULL) {
				ZTM_RectCopy(iRect, &(gZT_Window->rect));
			} else {
				ZTM_Rect(&(gZT_Window->rect), ZTK_DEFAULT_WINDOW_POS_X, ZTK_DEFAULT_WINDOW_POS_Y, ZTK_DEFAULT_WINDOW_WIDTH, ZTK_DEFAULT_WINDOW_HEIGHT);
			}
			gZT_Window->system.cache.rect = gZT_Window->rect;
			ZTK_RuntimeLoad();
			#ifdef ZTK_LOAD_RANDOM_SEED
			ZTM_SRand(ZTM_TimeGet(NULL));
			#endif // ZTK_LOAD_RANDOM_SEED
			ZTK_RuntimeKeyReload(gZT_Window->system.input.keyboard.state);
		}
	}
}
ZT_BOOL ZTK_Main(void (*iLoop)(void)) {
    if (gZT_Window != NULL) {
        gZT_Window->system.loop = iLoop;
        if (!(gZT_Window->system.state & ZTK_WINDOW_STATE_DESTROYED)) {
            ZTK_HostProcess();
            if (!(gZT_Window->system.events.flag  & ZTK_EVENT_FLAG_FAST)) {ZTK_Process();}
            ZTK_Now();
            if (!(gZT_Window->system.state & ZTK_WINDOW_STATE_EXITING)) {
                if (ZTK_Timeout((&gZT_Window->system.timer.loopLast), gZT_Window->system.timer.resolution)) {
                    ZTK_TimeoutReset(&(gZT_Window->system.timer.loopLast), gZT_Window->system.timer.resolution);
                    ZTK_RuntimeLoop();
                }
                return ZT_TRUE;
            }
        }
    }
    return ZT_FALSE;
}
void ZTK_User(void) {
    if (gZT_Window != NULL) {
        if (!(gZT_Window->system.state & ZTK_WINDOW_STATE_DESTROYED)) {
            if (!(gZT_Window->system.events.flag & ZTK_EVENT_FLAG_FAST)) {ZTK_Process();}
            ZTK_Now();
            if ((gZT_Window->system.state & ZTK_WINDOW_STATE_RUNNING) && (gZT_Window->system.loop != NULL)) {
                (*gZT_Window->system.loop)();
            }
        }
    }
}
void ZTK_Now(void) {
    if (gZT_Window != NULL) {
        gZT_Window->system.timer.loopNow = ZTK_HostGetTicks();
    }
}
void ZTK_Process(void) {
    if (gZT_Window != NULL) {
        if (ZTK_Timeout(&(gZT_Window->system.timer.eventLast), gZT_Window->system.timer.eventMin)) {
            ZT_FLAG lAction = 0x0;
            for (ZT_FLAG lHID = 0x1; lHID & ZTK_HID_ALL; lHID <<= 1) {
                if (gZT_Window->system.events.enabled & lHID) {
                    if (gZT_Window->system.cache.flag & lHID) {
                        gZT_Window->system.cache.flag &= (~lHID);
                        switch (lHID) {
                            case ZTK_HID_WINDOW:
                                ZTK_EventCacheWindowState(&(gZT_Window->system.state), &(gZT_Window->system.cache.state));
                                if ((lAction = ZTK_EventCacheWindowRect(&(gZT_Window->rect), &(gZT_Window->system.cache.rect)))) {
                                    ZTK_RuntimeRectReload();
                                    ZTK_RuntimeDrawReload();
                                }
                                break;
                            case ZTK_HID_TIMER: break; // submits event immediately on ZTK_MSG_TIMER() call
                            case ZTK_HID_MOUSE: ZTK_EventCacheMouse(&(gZT_Window->system.input.mouse), &(gZT_Window->system.cache.input.mouse)); break;
                            case ZTK_HID_KEY: ZTK_EventCacheKeyboard(&(gZT_Window->system.input.keyboard), &(gZT_Window->system.cache.input.keyboard)); break;
                            default: break;
                        }
                    } else {
                        if (gZT_Window->system.events.pump & lHID) {
                            switch (lHID) {
                                case ZTK_HID_WINDOW: break; // to be implemented, i.e. constant event submission window_active, etc...
                                case ZTK_HID_TIMER: break; // submits event immediately on ZTK_MSG_TIMER() call
                                case ZTK_HID_MOUSE: ZTK_EventPumpMouse(&(gZT_Window->system.input.mouse)); break;
                                case ZTK_HID_KEY: ZTK_EventPumpKeyboard(&(gZT_Window->system.input.keyboard)); break;
                                default: break;
                            }

                        }
                    }
                }
            }
            ZTK_TimeoutReset(&(gZT_Window->system.timer.eventLast), gZT_Window->system.timer.eventMin);
        }
    }
}
ZT_BOOL ZTK_Exiting(void) {
    if (gZT_Window != NULL) {
        if (gZT_Window->system.state & ZTK_WINDOW_STATE_EXITING) {
            return ZT_TRUE;
        }
    }
    return ZT_FALSE;
}

// GET FUNCTIONS
ZT_FLAG ZTK_GetStatus(void) {if (gZT_Window != NULL) {return gZT_Window->system.state;} return 0x0;}
ZT_FLAG ZTK_GetType(void) {if (gZT_Window != NULL) {return gZT_Window->system.type;} return 0x0;}
ZT_FLAG ZTK_GetStyle(void) {if (gZT_Window != NULL) {return gZT_Window->system.style;} return 0x0;}
const ZT_CHAR* ZTK_GetTitle(void) {if (gZT_Window != NULL) {return (const ZT_CHAR*)gZT_Window->user.title;} return NULL;}
ZT_CHAR ZTK_GetInputText(void) {if (gZT_Window != NULL) {return (gZT_Window->system.input.text & (~((ZT_CHAR)0x0)));} return ZTM_CHAR_NT;}
ZT_I ZTK_GetPosX(void) {if (gZT_Window != NULL) {return gZT_Window->rect.x;} return 0;}
ZT_I ZTK_GetPosY(void) {if (gZT_Window != NULL) {return gZT_Window->rect.y;} return 0;}
ZT_I ZTK_GetWidth(void) {if (gZT_Window != NULL) {return gZT_Window->rect.w;} return 0;}
ZT_I ZTK_GetHeight(void) {if (gZT_Window != NULL) {return gZT_Window->rect.h;} return 0;}
ZT_COLOR ZTK_GetBackground(void) {if (gZT_Window != NULL) {return gZT_Window->user.background;} return 0x0;}
ZT_FLAG ZTK_GetMouseState(void) {if (gZT_Window != NULL) {return gZT_Window->system.input.mouse.state;} return 0x0;}
ZT_I ZTK_GetMousePosX(void) {if (gZT_Window != NULL) {return gZT_Window->system.input.mouse.pos.x;} return 0;}
ZT_I ZTK_GetMousePosY(void) {if (gZT_Window != NULL) {return gZT_Window->system.input.mouse.pos.y;} return 0;}
void ZTK_GetMousePos(ZT_POINT* oPosition) {if (gZT_Window != NULL && oPosition != NULL) {ZTM_PointCopy(&(gZT_Window->system.input.mouse.pos), oPosition);}}
void ZTK_GetPosition(ZT_POINT* oPosition) {if (gZT_Window != NULL && oPosition != NULL) {ZTM_RectPosIntoPoint(&(gZT_Window->rect), oPosition);}}
void ZTK_GetSize(ZT_POINT* oSize) {if (gZT_Window != NULL && oSize != NULL) {ZTM_RectSizeIntoPoint(&(gZT_Window->rect), oSize);}}
void ZTK_GetRect(ZT_RECT* oRect) {if (gZT_Window != NULL && oRect != NULL) {ZTM_RectCopy(&(gZT_Window->rect), oRect);}}
ZT_FLAG ZTK_GetPalette(void) {if (gZT_Window != NULL) {return gZT_Window->user.palette;} else {return ZTM_PALETTE_UNKNOWN;}}

// SET FUNCTIONS
void ZTK_InputTextCapture(ZT_BOOL iEnable) {
	if (gZT_Window != NULL) {
        if (iEnable) {
            gZT_Window->system.input.flag |= ZTK_WINDOW_INPUT_CHAR;
        } else {
            gZT_Window->system.input.flag &= (~ZTK_WINDOW_INPUT_CHAR);
        }
	}
}
void ZTK_Title(const ZT_U8* iTitle) {
	if (gZT_Window != NULL) {
        ZTK_TitleFree();
        gZT_Window->user.title = (iTitle != NULL) ? ZTC8_Copy(iTitle) : (ZT_U8*)ZTK_DEFAULT_WINDOW_TITLE;
	}
}
void ZTK_IdleHoldOff(ZT_TIME iDelay) {
    if (gZT_Window != NULL) {
        if (iDelay) {
            gZT_Window->system.timer.idleHoldoff = iDelay;
            gZT_Window->system.timer.flag |= ZTK_WINDOW_IDLE_HOLDOFF;
        } else {
            gZT_Window->system.timer.flag &= ~ZTK_WINDOW_IDLE_HOLDOFF;
        }
    }
}
void ZTK_IdleForbid(ZT_BOOL iForbid) {
    if (gZT_Window != NULL) {
        if (iForbid) {
            gZT_Window->system.timer.flag &= ~ZTK_WINDOW_IDLE_ALLOWED;
        } else {
            gZT_Window->system.timer.flag |= ZTK_WINDOW_IDLE_ALLOWED;
        }
    }
}
void ZTK_IdleAuto(ZT_BOOL iEnabled) {
    if (gZT_Window != NULL) {
        if (iEnabled) {
            gZT_Window->system.timer.flag |= ZTK_WINDOW_IDLE_AUTOMATIC;
        } else {
            gZT_Window->system.timer.flag &= ~ZTK_WINDOW_IDLE_AUTOMATIC;
        }
    }
}

void ZTK_PaletteUser(ZT_FLAG iPalette) {if (gZT_Window != NULL) {gZT_Window->user.palette = iPalette;}}
void ZTK_PosX(ZT_I iX) {
    if (gZT_Window != NULL) {
        if (gZT_Window->rect.x != iX) {
            gZT_Window->rect.x = iX;
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_PosY(ZT_I iY) {
    if (gZT_Window != NULL) {
        if (gZT_Window->rect.y != iY) {
            gZT_Window->rect.y = iY;
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_Width(ZT_I iWidth) {
    if (gZT_Window != NULL) {
        if (gZT_Window->rect.w != iWidth) {
            gZT_Window->rect.w = iWidth;
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_Height(ZT_I iHeight) {
    if (gZT_Window != NULL) {
        if (gZT_Window->rect.h != iHeight) {
            gZT_Window->rect.h = iHeight;
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_Pos(const ZT_POINT* iPos) {
    if (gZT_Window != NULL && iPos != NULL) {
        if ((gZT_Window->rect.x != iPos->x) || (gZT_Window->rect.y != iPos->y)) {
            gZT_Window->rect.x = iPos->x;
            gZT_Window->rect.y = iPos->y;
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_PosFromIntegers(ZT_I iX, ZT_I iY) {
    if (gZT_Window != NULL) {
        if ((gZT_Window->rect.x != iX) || (gZT_Window->rect.y != iY)) {
            gZT_Window->rect.x = iX;
            gZT_Window->rect.y = iY;
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_Size(const ZT_POINT* iSize) {
    if (gZT_Window != NULL && iSize != NULL) {
        if ((gZT_Window->rect.w != iSize->x) || (gZT_Window->rect.h != iSize->y)) {
            gZT_Window->rect.w = iSize->x;
            gZT_Window->rect.h = iSize->y;
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_SizeFromIntegers(ZT_I iWidth, ZT_I iHeight) {
    if (gZT_Window != NULL) {
        if ((gZT_Window->rect.w != iWidth) || (gZT_Window->rect.h != iHeight)) {
            gZT_Window->rect.w = iWidth;
            gZT_Window->rect.h = iHeight;
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_Rect(const ZT_RECT* iRect) {
    if (gZT_Window != NULL && iRect != NULL) {
        if (!(ZTM8_Match(&(gZT_Window->rect), iRect, sizeof(ZT_RECT)))) {
            ZTM_RectCopy(iRect, &(gZT_Window->rect));
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_RectFromIntegers(ZT_I iX, ZT_I iY, ZT_I iWidth, ZT_I iHeight) {
    if (gZT_Window != NULL) {
        gZT_Window->rect.x = iX;
        gZT_Window->rect.y = iY;
        if ((gZT_Window->rect.w != iWidth) || (gZT_Window->rect.h != iHeight)) {
            gZT_Window->rect.w = iWidth;
            gZT_Window->rect.h = iHeight;
            if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowReload();}
        }
    }
}
void ZTK_Background(ZT_BOOL iEnabled) {if (gZT_Window != NULL) {if (iEnabled) {gZT_Window->user.options |= ZTK_WINDOW_BACKGROUND_ENABLED;} else {gZT_Window->user.options &= ~ZTK_WINDOW_BACKGROUND_ENABLED;} if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeDrawColorsReload();}}}
void ZTK_BackgroundAuto(ZT_BOOL iEnabled) {if (gZT_Window != NULL) {if (iEnabled) {gZT_Window->user.options |= ZTK_WINDOW_BACKGROUND_AUTO;} else {gZT_Window->user.options &= ~ZTK_WINDOW_BACKGROUND_AUTO;}}}
void ZTK_BackgroundColor(ZT_COLOR iColor) {if (gZT_Window != NULL) {gZT_Window->user.background = iColor; if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeDrawColorsReload();}}}
void ZTK_FontColor(ZT_FONT* iFont, ZT_COLOR iColor) {if (gZT_Window != NULL) {ZT_FONT* lFont = (iFont != NULL) ? iFont : &(gZT_Window->system.font.window); lFont->color = iColor; ZTK_FontReload(lFont);}}
void ZTK_FontColorBk(ZT_FONT* iFont, ZT_COLOR iColor) {if (gZT_Window != NULL) {ZT_FONT* lFont = (iFont != NULL) ? iFont : &(gZT_Window->system.font.window); lFont->colorBk = iColor; ZTK_FontReload(lFont);}}
void ZTK_FontSize(ZT_FONT* iFont, ZT_INDEX iSize) {if (gZT_Window != NULL) {ZT_FONT* lFont = (iFont != NULL) ? iFont : &(gZT_Window->system.font.window); lFont->height = iSize; ZTK_FontReload(lFont);}}
void ZTK_FontStyle(ZT_FONT* iFont, ZT_FLAG iStyle) {if (gZT_Window != NULL) {ZT_FONT* lFont = (iFont != NULL) ? iFont : &(gZT_Window->system.font.window); lFont->style = iStyle; ZTK_FontReload(lFont);}}

// INTERNAL-ONLY FUNCTIONS
void ZTK_Wake(void) {
	if (gZT_Window != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            if (gZT_Window->system.timer.flag & ZTK_WINDOW_IDLE_ENABLED) {
                gZT_Window->system.timer.idleLast = ZTK_HostGetTicks();
                gZT_Window->system.timer.flag &= ~ZTK_WINDOW_IDLE_ENABLED;
            }
        }
    }
}
void ZTK_TitleFree(void) {if (gZT_Window != NULL) {if (gZT_Window->user.title != NULL) {ZTM8_Free(gZT_Window->user.title); gZT_Window->user.title = NULL;}}}
void ZTK_EventBufferFree(void) {
	if (gZT_Window != NULL) {
		if (gZT_Window->system.events.buffer != NULL) {
            if ((gZT_Window->system.events.buffer->items)[0] != NULL) {
                ZTM8_Free((gZT_Window->system.events.buffer->items)[0]);
                (gZT_Window->system.events.buffer->items)[0] = NULL;
            }
            ZTM_QListFree(gZT_Window->system.events.buffer);
            gZT_Window->system.events.buffer = NULL;
		}

    }
}
void ZTK_EventBufferCreate(void) {
	if (gZT_Window != NULL) {
        ZTK_EventBufferFree();
        gZT_Window->system.events.flag = ZTK_DEFAULT_EVENT_FLAG;
        gZT_Window->system.events.disabled = ZTK_DEFAULT_EVENT_DISABLED;
        gZT_Window->system.events.enabled = ZTK_DEFAULT_EVENT_ENABLED;
        gZT_Window->system.events.capture = ZTK_DEFAULT_EVENT_CAPTURE;
        gZT_Window->system.events.pump = ZTK_DEFAULT_EVENT_PUMP;
        gZT_Window->system.events.raw = ZTK_DEFAULT_EVENT_RAW;
        if ((gZT_Window->system.events.buffer = ZTM_QListNew(ZTK_DEFAULT_BUFFER_EVENTS)) != NULL) {
            ZT_INDEX lSize = sizeof(ZT_EVENT);
            if (lSize % 8) {lSize += 8 - (lSize % 8);}
            void* lMemBlock = (void*)ZTM8_New(lSize * gZT_Window->system.events.buffer->length);
            if (lMemBlock != NULL) {for (ZT_INDEX i = 0; i < gZT_Window->system.events.buffer->length; i++) {(gZT_Window->system.events.buffer->items)[i] = (lMemBlock + i * lSize);}}
        }
	}
}
void ZTK_DrawBufferCreate(void) {
	if (gZT_Window != NULL) {
        ZTK_DrawBufferFree(); gZT_Window->system.draw.flag = ZTK_DEFAULT_DRAW_FLAG;
        if ((gZT_Window->system.draw.buffer = ZTM_QListNew(ZTK_DEFAULT_BUFFER_DRAWS_SINGLE)) != NULL) {
            ZT_INDEX lSize = sizeof(ZT_DRAW);
            if (lSize % 8) {lSize += 8 - (lSize % 8);}
            void* lMemBlock = (void*)ZTM8_New(lSize * gZT_Window->system.draw.buffer->length);
            if (lMemBlock != NULL) {for (ZT_INDEX i = 0; i < gZT_Window->system.draw.buffer->length; i++) {(gZT_Window->system.draw.buffer->items)[i] = (lMemBlock + i * lSize);}}
        }
	}
}
void ZTK_DrawBufferFree(void) {if (gZT_Window != NULL) {if (gZT_Window->system.draw.buffer != NULL) {
            if ((gZT_Window->system.draw.buffer->items)[0] != NULL) {ZTM8_Free((gZT_Window->system.draw.buffer->items)[0]); (gZT_Window->system.draw.buffer->items)[0] = NULL;}
            ZTM_QListFree(gZT_Window->system.draw.buffer); gZT_Window->system.draw.buffer = NULL;
}}}

// RUNTIME-DEPENDENT
ZT_I ZTK_HostGetScreenWidth(void) {return ZTK_RuntimeGetScreenWidth();}
ZT_I ZTK_HostGetScreenHeight(void) {return ZTK_RuntimeGetScreenHeight();}
ZT_TIME ZTK_HostGetTicks(void) {if (gZT_Window != NULL) {if (gZT_Window->system.runtime != NULL) {return ZTK_RuntimeTicks();}} return 0;}
void ZTK_FontCharsetFree(ZT_FONT* iFont) {if (iFont != NULL && gZT_Window != NULL) {if (iFont->charset != NULL) {
            for (ZT_INDEX i = 0; i < ZTM_CHAR_SET; i++) {if (iFont->charset[i] != NULL) {ZTK_SpriteFree(iFont->charset[i]);}}
            ZTM8_Free(iFont->charset); iFont->charset = NULL;
}}}
void ZTK_FontCharsetNew(ZT_FONT* iFont) {
    if (iFont != NULL && gZT_Window != NULL) {
        ZTK_FontCharsetFree(iFont);
        if (iFont->charset == NULL) {
            if ((iFont->charset = (void**)ZTM8_New(sizeof(ZT_SPRITE*) * ZTM_CHAR_SET)) != NULL) {
                iFont->charset[0] = NULL;
                ZT_CHAR lChar[2] = {ZTM_CHAR_NT, ZTM_CHAR_NT};
                for (ZT_INDEX i = 0x1; i < ZTM_CHAR_SET; i++) {
                    lChar[0] = i & ZTM_CHAR_MASK;
                    iFont->charset[i] = ZTK_SpriteFromFont(lChar, iFont);
                }
            }
        }
    }
}
void ZTK_FontFree(ZT_FONT* iFont) {
    if (iFont != NULL) {
        ZTK_FontCharsetFree(iFont);
        if (iFont->runtime != NULL) {if (gZT_Window != NULL) {ZTK_RuntimeFontFree(iFont);}}
        if (iFont->flag & ZTM_FONT_FLAG_COPIED_NAME && iFont->name != NULL) {ZTM8_Free(iFont->name);}
        if (iFont->flag & ZTM_FONT_FLAG_COPIED_SOURCE && iFont->source != NULL) {ZTM8_Free(iFont->source);}
        ZTM8_Free(iFont);
    }
}
ZT_FONT* ZTK_FontNew(const ZT_CHAR* iSource, const ZT_CHAR* iName, ZT_I iHeight, ZT_FLAG iStyle, ZT_COLOR iColor) {
    ZT_FONT* lFont = NULL;
    if (iSource != NULL || iName != NULL) {
        if ((lFont = (ZT_FONT*)ZTM8_New(sizeof(ZT_FONT))) != NULL) {
            lFont->flag = ZTM_FONT_FLAG_RELOAD;
            if (iSource != NULL) {lFont->source = ZTC8_Copy(iSource); lFont->flag |= ZTM_FONT_FLAG_COPIED_SOURCE; lFont->type = ZTM_FONT_TYPE_TTF;} else {lFont->source = NULL; lFont->type = ZTM_FONT_TYPE_NONE;}
            if (iName != NULL) {lFont->name = ZTC8_Copy(iName); lFont->flag |= ZTM_FONT_FLAG_COPIED_NAME;} else {lFont->name = NULL;}
            lFont->height = iHeight;
            lFont->style = iStyle;
            lFont->color = iColor;
            lFont->colorBk = ZTM_ColorComplementary(iColor);
            lFont->runtime = NULL;
            lFont->charset = NULL;
        }
    }
    return lFont;
}
void ZTK_FontReload(ZT_FONT *iFont) {
    ZT_FONT* lFont = (iFont != NULL) ? iFont : &(gZT_Window->system.font.window);
    lFont->flag |= ZTM_FONT_FLAG_RELOAD;
    if (lFont->charset != NULL) {ZTK_FontCharsetNew(lFont);}
}
void ZTK_FontSet(ZT_FONT* iFont) {
    if (gZT_Window != NULL) {
        gZT_Window->user.font = (iFont != NULL) ? iFont : &(gZT_Window->system.font.window);
        ZTK_RuntimeFontWindow();
    }
}
void ZTK_Free(void) {
	if (gZT_Window != NULL) {
        if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowDestroy();}
		if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeFree();}
		ZTK_DrawBufferFree();
		ZTK_EventBufferFree();
		ZTK_TitleFree();
		ZTM8_Free(gZT_Window);
	}
	gZT_Window = NULL;
}
void ZTK_Destroy(void) {
	if (gZT_Window != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            ZTK_RuntimeWindowDestroy();
        }
    }
}
void ZTK_DrawReload(void) {
	if (gZT_Window != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            ZTK_RuntimeDrawReload();
        }
    }
}
void ZTK_DrawBufferAdd(const void* iSource, ZT_FLAG iType, const ZT_RECT* iDest) {
    if (gZT_Window != NULL) {
        ZT_DRAW* lDraw = ZTM_QListAdvanceItem(gZT_Window->system.draw.buffer);
        lDraw->type = iType;
        switch (lDraw->type) {
            case ZTK_DRAW_TYPE_TEXT: lDraw->source = ZTC8_Copy(iSource); break;
            default: lDraw->source = iSource; break;
        }
        lDraw->flag = ZTK_DRAW_FLAG_NONE;
        if (iDest != NULL) {ZTM_RectCopy(iDest, &(lDraw->dest));} else {lDraw->flag |= ZTK_DRAW_FLAG_NULLDEST; ZTM_RectZero(&(lDraw->dest));}
    }
}
void ZTK_DrawBufferItem(const ZT_DRAW* iObject) {
    if (gZT_Window != NULL && iObject != NULL) {
        if ((gZT_Window->system.draw.flag & ZTK_DRAW_FLAG_ENABLED) && iObject->source != NULL) {
            const void* lObject = iObject->source;
            const ZT_RECT* lDest = (iObject->flag & ZTK_DRAW_FLAG_NULLDEST) ? NULL : &(iObject->dest);
            switch (iObject->type) {
                case ZTK_DRAW_TYPE_SPRITE: ZTK_RuntimeDrawSprite((ZT_SPRITE*)lObject, lDest); break;
                case ZTK_DRAW_TYPE_SURFACE: ZTK_RuntimeDrawSurface((ZT_SURFACE*)lObject, lDest); break;
                case ZTK_DRAW_TYPE_TEXT: ZTK_RuntimeDrawText(lObject, lDest); ZTM8_Free((ZT_CHAR*)lObject); break;
                default: break;
            }
        }
    }
}
void ZTK_DrawBuffer(void) {
    if (gZT_Window != NULL) {
        ZT_DRAW* lDraw = NULL;
        while (ZTM_QListPoll(gZT_Window->system.draw.buffer, (void**)&lDraw)) {
            if (!(gZT_Window->system.state & ZTK_WINDOW_STATE_MINIMIZED)) {ZTK_DrawBufferItem(lDraw);}
        }
    }
}
void ZTK_DrawPresent(void) {
    if (gZT_Window != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            if (!(gZT_Window->system.draw.flag & ZTK_DRAW_FLAG_UNBUFFERED)) {ZTK_DrawBuffer();}
            ZTK_RuntimeDrawPresent();
        }
    }
}
void ZTK_DrawSprite(ZT_SPRITE* iSprite, const ZT_RECT* iTarget) {
    if (gZT_Window != NULL && iSprite != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            if (gZT_Window->system.draw.flag & ZTK_DRAW_FLAG_UNBUFFERED) {
                if (gZT_Window->system.draw.flag & ZTK_DRAW_FLAG_ENABLED) {ZTK_RuntimeDrawSprite(iSprite, iTarget);}
            } else {
                ZTK_DrawBufferAdd(iSprite, ZTK_DRAW_TYPE_SPRITE, iTarget);
            }
        }
    }
}
void ZTK_DrawSurface(ZT_SURFACE* iSurface, const ZT_RECT* iTarget) {
    if (gZT_Window != NULL && iSurface != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            if (gZT_Window->system.draw.flag & ZTK_DRAW_FLAG_UNBUFFERED) {
                if (gZT_Window->system.draw.flag & ZTK_DRAW_FLAG_ENABLED) {ZTK_RuntimeDrawSurface(iSurface, iTarget);}
            } else {
                ZTK_DrawBufferAdd(iSurface, ZTK_DRAW_TYPE_SURFACE, iTarget);
            }
        }
    }
}
void ZTK_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox) {
    if (gZT_Window != NULL && iText != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            if (gZT_Window->system.draw.flag & ZTK_DRAW_FLAG_UNBUFFERED) {
                ZTK_RuntimeDrawText(iText, iTextBox);
            } else {
                if (gZT_Window->system.draw.flag & ZTK_DRAW_FLAG_ENABLED) {ZTK_DrawBufferAdd((ZT_CHAR*)iText, ZTK_DRAW_TYPE_TEXT, iTextBox);}
            }
        }
    }
}
void ZTK_GetDrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize) {
    if (gZT_Window != NULL && iText != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            ZTK_RuntimeGetDrawTextSize(iText, oTextSize);
        }
    }
}
void ZTK_DrawBackground(void) {if (gZT_Window != NULL) {if ((gZT_Window->system.runtime != NULL) && (gZT_Window->user.options & ZTK_WINDOW_BACKGROUND_ENABLED)) {ZTK_RuntimeDrawBackground();}}}
void ZTK_DrawClear(void) {if (gZT_Window != NULL) {if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeDrawClear();}}}
void ZTK_Heartbeat(ZT_TIME iDelay) {
    if (gZT_Window != NULL) {
        gZT_Window->system.timer.heartbeat = iDelay;
        if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeHeartbeat();}
    }
}
void ZTK_Idle(ZT_TIME iWake) {
	if (gZT_Window != NULL) {
        if (!(gZT_Window->system.state & ZTK_WINDOW_STATE_EXITING) && (gZT_Window->system.timer.flag & ZTK_WINDOW_IDLE_ALLOWED)) {
            if  (((!(gZT_Window->system.timer.flag & ZTK_WINDOW_IDLE_HOLDOFF)) ? ZT_TRUE : ((ZTK_HostGetTicks() - gZT_Window->system.timer.idleLast) > gZT_Window->system.timer.idleHoldoff))) {
                gZT_Window->system.timer.flag |= ZTK_WINDOW_IDLE_ENABLED;
                if (iWake && gZT_Window->system.runtime != NULL) {
                    ZTK_RuntimeWake(iWake);
                }
            }
        }
	}
}
void ZTK_Open(void) {if (gZT_Window != NULL) {if (gZT_Window->system.runtime != NULL) {ZTK_RuntimeWindowOpen();}}}
void ZTK_HostProcess(void) {
	if (gZT_Window != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            ZTK_RuntimeProcess();
        }
    }
}

ZT_INDEX ZTK_PollMessages(ZT_EVENT** iEvent) {
	if (gZT_Window != NULL) {
        if (gZT_Window->system.runtime != NULL) {
            if (!(ZTM_QListQueued(gZT_Window->system.events.buffer))) {
                if (gZT_Window->system.timer.flag & ZTK_WINDOW_IDLE_AUTOMATIC) {ZTK_Idle(0);}
                if (gZT_Window->system.timer.flag & ZTK_WINDOW_IDLE_ENABLED) {if (!ZTK_RuntimeMessages()) {ZTK_RuntimeWait();}}
            }
            return ZTM_QListPoll(gZT_Window->system.events.buffer, (void**)iEvent);
        }
    }
    return 0;
}

ZT_SURFACE* ZTK_SurfaceFromBitmap(const ZT_CHAR* iPath, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = NULL;
	if (gZT_Window != NULL && iPath != NULL) {
        lSurface = ZTK_RuntimeSurfaceFromBitmap(iPath, 0x0, 0xff, oPalette);
	}
	return lSurface;
}
ZT_SURFACE* ZTK_SurfaceFromBitmapWithOpacity(const ZT_CHAR* iPath, ZT_INDEX iOpacity, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = NULL;
	if (gZT_Window != NULL && iPath != NULL) {
        lSurface = ZTK_RuntimeSurfaceFromBitmap(iPath, 0x0, iOpacity, oPalette);
	}
	return lSurface;
}
ZT_SURFACE* ZTK_SurfaceFromBitmapWithTransparent(const ZT_CHAR* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacity, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = NULL;
	if (gZT_Window != NULL && iPath != NULL) {
        lSurface = ZTK_RuntimeSurfaceFromBitmap(iPath, iTransparent, iOpacity, oPalette);
	}
	return lSurface;
}
ZT_SURFACE* ZTK_SurfaceFromText(const ZT_CHAR* iText, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = NULL;
	if (gZT_Window != NULL && iText != NULL) {
        lSurface = ZTK_RuntimeSurfaceFromFont(iText, NULL, oPalette);
	}
	return lSurface;
}
ZT_SURFACE* ZTK_SurfaceFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_FLAG* oPalette) {
    ZT_SURFACE* lSurface = NULL;
	if (gZT_Window != NULL && iText != NULL) {
        lSurface = ZTK_RuntimeSurfaceFromFont(iText, iFont, oPalette);
	}
	return lSurface;
}
void ZTK_GetSizeFromText(const ZT_CHAR* iText, ZT_POINT* oSize) {
	if (gZT_Window != NULL && iText != NULL && oSize != NULL) {
        ZTK_RuntimeSizeFromFont(iText, NULL, oSize);
	}
}
void ZTK_GetSizeFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_POINT* oSize) {
	if (gZT_Window != NULL && iText != NULL && oSize != NULL) {
        ZTK_RuntimeSizeFromFont(iText, iFont, oSize);
	}
}
#endif // ZTK_C_INCLUDED
