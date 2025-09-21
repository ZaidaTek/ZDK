/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_C_INCLUDED
#define ZTK_C_INCLUDED

#include "ZTK-RT.h"

// MAIN FUNCTIONS
void ZTK_Quit(void) {ZTK_RuntimeQuit();}
void ZTK_New(void (*iMainFunction)(void), const ZT_CHAR* iTitle, const ZT_RECT* iRect, const ZT_CHAR* iIcon) {
    ZTM8_Zero(&rZTK_Host, sizeof(rZTK_Host));
    ZTK_EventBufferCreate();
    ZTK_DrawBufferCreate();
    rZTK_Host.loop = iMainFunction;
    rZTK_Host.system.renderer = ZTK_DEFAULT_RENDERER;
    rZTK_Host.system.palette = ZTK_PALETTE_SYSTEM;
    rZTK_Host.system.state = ZTK_STATE_NONE;
    rZTK_Host.system.type = ZTK_TYPE_COMPILED;
    ZTL_TickResolution(rZTK_Host.system.timer.resolution = ZTK_DEFAULT_TIMER_RESOLUTION);
    rZTK_Host.system.timer.event = ZTK_DEFAULT_TIMER_PUMP;
    rZTK_Host.system.input.flag = ZTK_DEFAULT_INPUT_FLAG;
    rZTK_Host.system.font = ZTK_FontNew((const ZT_CHAR*)ZTK_DEFAULT_FONT_SOURCE, (const ZT_CHAR*)ZTK_DEFAULT_FONT, ZTK_DEFAULT_FONT_SIZE, ZTK_DEFAULT_FONT_STYLE, ZTK_DEFAULT_FONT_COLOR);
    ZTK_Title(iTitle != NULL ? iTitle : (const ZT_CHAR*)ZTK_DEFAULT_TITLE);
    rZTK_Host.user.options = ZTK_FLAG_NONE;
    rZTK_Host.user.icon = (ZT_CHAR*)iIcon;//(ZT_CHAR*)ZTK_DEFAULT_WINDOW_ICON;
    rZTK_Host.user.palette = ZTK_DEFAULT_PALETTE_USER;
    rZTK_Host.user.background = ZTK_DEFAULT_BACKGROUND;
    rZTK_Host.user.font = rZTK_Host.system.font;
    if (iRect != NULL) {
        ZTM_RectCopy(iRect, &(rZTK_Host.rect));
    } else {
        ZTM_Rect(&(rZTK_Host.rect), ZTK_DEFAULT_POS_X, ZTK_DEFAULT_POS_Y, ZTK_DEFAULT_WIDTH, ZTK_DEFAULT_HEIGHT);
    }
    rZTK_Host.buffer.rect = rZTK_Host.rect;
    ZTK_RuntimeLoad();
    ZTK_RuntimeKeyReload(rZTK_Host.system.input.keyboard.state);
}
ZT_BOOL ZTK_Main(void) {
    ZTK_RuntimeProcess();
    ZTK_RuntimeLoop();
    return (rZTK_Host.system.state & ZTK_STATE_EXITING) ? ZT_FALSE : ZT_TRUE;
}
void ZTK_Process(void) {
    rZTK_Host.system.last.loop = ZTL_Tick();
    ZT_FLAG lPump = ZTK_TimeoutReset(&(rZTK_Host.system.last.event), rZTK_Host.system.timer.event);
    for (ZT_FLAG lHID = ZTK_HID_FIRST; lHID & ZTK_HID_ALL; lHID <<= 1) {
        if (rZTK_Host.system.events.enabled & lHID) {
            if (rZTK_Host.buffer.flag & lHID) {
                rZTK_Host.buffer.flag &= ~lHID;
                switch (lHID) {
                    case ZTK_HID_WINDOW:
                        ZTK_EventCacheWindowState(&(rZTK_Host.system.state), &(rZTK_Host.buffer.state));
                        if (ZTK_EventCacheWindowRect(&(rZTK_Host.rect), &(rZTK_Host.buffer.rect))) {ZTK_DrawSize();}
                        break;
                    case ZTK_HID_MOUSE: ZTK_EventCacheMouse(&(rZTK_Host.system.input.mouse), &(rZTK_Host.buffer.input.mouse)); break;
                    case ZTK_HID_KEY: ZTK_EventCacheKeyboard(&(rZTK_Host.system.input.keyboard), &(rZTK_Host.buffer.input.keyboard)); break;
                    default: break;
                }
            } else if (lPump && (rZTK_Host.system.events.pump & lHID)) {
                switch (lHID) {
                    case ZTK_HID_WINDOW: break; // to be implemented, i.e. constant event submission window_active, etc...
                    case ZTK_HID_MOUSE: ZTK_EventPumpMouse(&(rZTK_Host.system.input.mouse)); break;
                    case ZTK_HID_KEY: ZTK_EventPumpKeyboard(&(rZTK_Host.system.input.keyboard)); break;
                    default: break;
                }
            }
        }
    }
}
ZT_BOOL ZTK_Timeout(ZT_TIME iLast, ZT_TIME iTimeout) {return ZTM_Timeout(rZTK_Host.system.last.loop, iLast, iTimeout);}
ZT_BOOL ZTK_TimeoutReset(ZT_TIME* ioLast, ZT_TIME iTimeout) {return ZTM_TimeoutReset(rZTK_Host.system.last.loop, ioLast, iTimeout);}
ZT_BOOL ZTK_Repeat(ZT_TIME iTimeout) {return ZTK_TimeoutReset(&(rZTK_Host.system.last.repeat), iTimeout);}
//ZT_BOOL ZTK_Exiting(void) {return (rZTK_Host.system.state & ZTK_STATE_EXITING) ? ZT_TRUE : ZT_FALSE;}

// GET FUNCTIONS
ZT_TIME ZTK_GetTicks(void) {return rZTK_Host.system.last.loop;}
ZT_FLAG ZTK_GetStatus(void) {return rZTK_Host.system.state;}
ZT_FLAG ZTK_GetType(void) {return rZTK_Host.system.type;}
ZT_FLAG ZTK_GetStyle(void) {return rZTK_Host.system.style;}
const ZT_CHAR* ZTK_GetTitle(void) {return (const ZT_CHAR*)rZTK_Host.user.title;}
ZT_CHAR ZTK_GetInputText(void) {return (rZTK_Host.system.input.text & (~((ZT_CHAR)0x0)));}
ZT_I ZTK_GetPosX(void) {return rZTK_Host.rect.x;}
ZT_I ZTK_GetPosY(void) {return rZTK_Host.rect.y;}
ZT_I ZTK_GetWidth(void) {return rZTK_Host.rect.w;}
ZT_I ZTK_GetHeight(void) {return rZTK_Host.rect.h;}
ZT_COLOR ZTK_GetBackground(void) {return rZTK_Host.user.background;}
ZT_FLAG ZTK_GetMouseState(void) {return rZTK_Host.system.input.mouse.state;}
ZT_I ZTK_GetMousePosX(void) {return rZTK_Host.system.input.mouse.pos.x;}
ZT_I ZTK_GetMousePosY(void) {return rZTK_Host.system.input.mouse.pos.y;}
void ZTK_GetMousePos(ZT_POINT* oPosition) {ZTM_PointCopy(&(rZTK_Host.system.input.mouse.pos), oPosition);}
void ZTK_GetPosition(ZT_POINT* oPosition) {ZTM_RectPosIntoPoint(&(rZTK_Host.rect), oPosition);}
void ZTK_GetSize(ZT_POINT* oSize) {ZTM_RectSizeIntoPoint(&(rZTK_Host.rect), oSize);}
void ZTK_GetRect(ZT_RECT* oRect) {ZTM_RectCopy(&(rZTK_Host.rect), oRect);}
ZT_FLAG ZTK_GetPalette(void) {return rZTK_Host.user.palette;}
ZT_FLAG ZTK_GetPaletteSystem(void) {return rZTK_Host.system.palette;}
ZT_FLAG ZTK_GetRendererType(void) {return rZTK_Host.system.renderer;}
void ZTK_GetDrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize) {ZTK_RuntimeGetDrawTextSize(iText, oTextSize);}
void ZTK_GetSizeFromText(const ZT_CHAR* iText, ZT_POINT* oSize) {ZTK_RuntimeSizeFromFont(iText, NULL, oSize);}
void ZTK_GetSizeFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_POINT* oSize) {ZTK_RuntimeSizeFromFont(iText, iFont, oSize);}
// SET FUNCTIONS
void ZTK_RendererInit(void) {
    switch (rZTK_Host.system.renderer) {
        case ZTK_RENDERER_SYSTEM: ZTK_RuntimeDrawReload(); return;
        #if defined(ZTK_BUILD_OPENGL) && (ZTK_BUILD_OPENGL)
        case ZTK_RENDERER_OPENGL: ZTGL_Init(); ZTGL_Size(); return;
        #endif // ZTK_BUILD_OPENGL
        default: return;
    }
}
void ZTK_RendererExit(void) {
    switch (rZTK_Host.system.renderer) {
        #if defined(ZTK_BUILD_OPENGL) && (ZTK_BUILD_OPENGL)
        case ZTK_RENDERER_OPENGL: ZTGL_Exit(); return;
        #endif // ZTK_BUILD_OPENGL
        default: return;
    }
}
void ZTK_Renderer(ZT_FLAG iType) {
    ZT_FLAG lRenderer;
    ZT_FLAG lPalette;
    switch (iType) {
        case ZTK_RENDERER_SYSTEM: lRenderer = ZTK_RENDERER_SYSTEM; lPalette = ZTK_PALETTE_SYSTEM; break;
        #if defined(ZTK_BUILD_OPENGL) && (ZTK_BUILD_OPENGL)
        case ZTK_RENDERER_OPENGL: lRenderer = ZTK_RENDERER_OPENGL; lPalette = ZTK_PALETTE_OPENGL; break;
        #endif // ZTK_BUILD_OPENGL
        default: lRenderer = ZTK_RENDERER_NONE; break;
    }
    if (lRenderer != ZTK_RENDERER_NONE) {
        ZTK_RendererExit();
        rZTK_Host.system.palette = lPalette;
        rZTK_Host.system.renderer = lRenderer;
        ZTK_RendererInit();
    }
}
void ZTK_InputTextCapture(ZT_BOOL iEnable) {
    if (iEnable) {
        rZTK_Host.system.input.flag |= ZTK_WINDOW_INPUT_CHAR;
    } else {
        rZTK_Host.system.input.flag &= (~ZTK_WINDOW_INPUT_CHAR);
    }
}
void ZTK_Title(const ZT_CHAR* iTitle) {ZTK_TitleFree(); rZTK_Host.user.title = ZTC8_Copy(iTitle);}
void ZTK_PaletteUser(ZT_FLAG iPalette) {rZTK_Host.user.palette = iPalette;}
void ZTK_PosX(ZT_I iX) {rZTK_Host.rect.x = iX; ZTK_RuntimeRectApply();}
void ZTK_PosY(ZT_I iY) {rZTK_Host.rect.y = iY; ZTK_RuntimeRectApply();}
void ZTK_Width(ZT_I iWidth) {rZTK_Host.rect.w = iWidth; ZTK_RuntimeRectApply();}
void ZTK_Height(ZT_I iHeight) {rZTK_Host.rect.h = iHeight; ZTK_RuntimeRectApply();}
void ZTK_Pos(const ZT_POINT* iPos) {rZTK_Host.rect.x = iPos->x; rZTK_Host.rect.y = iPos->y; ZTK_RuntimeRectApply();}
void ZTK_PosFromIntegers(ZT_I iX, ZT_I iY) {rZTK_Host.rect.x = iX; rZTK_Host.rect.y = iY; ZTK_RuntimeRectApply();}
void ZTK_Size(const ZT_POINT* iSize) {rZTK_Host.rect.w = iSize->x; rZTK_Host.rect.h = iSize->y; ZTK_RuntimeRectApply();}
void ZTK_SizeFromIntegers(ZT_I iWidth, ZT_I iHeight) {rZTK_Host.rect.w = iWidth; rZTK_Host.rect.h = iHeight; ZTK_RuntimeRectApply();}
void ZTK_Rect(const ZT_RECT* iRect) {ZTM_RectCopy(iRect, &(rZTK_Host.rect)); ZTK_RuntimeRectApply();}
void ZTK_RectFromIntegers(ZT_I iX, ZT_I iY, ZT_I iWidth, ZT_I iHeight) {rZTK_Host.rect.x = iX; rZTK_Host.rect.y = iY; rZTK_Host.rect.w = iWidth; rZTK_Host.rect.h = iHeight; ZTK_RuntimeRectApply();}
void ZTK_BackgroundColor(ZT_COLOR iColor) {
    rZTK_Host.user.background = iColor;
    switch (rZTK_Host.system.renderer) {
        case ZTK_RENDERER_SYSTEM: ZTK_RuntimeDrawClearColor(iColor); return;
        #if defined(ZTK_BUILD_OPENGL) && (ZTK_BUILD_OPENGL)
        case ZTK_RENDERER_OPENGL: ZTGL_ClearColor(iColor); return;
        #endif // ZTK_BUILD_OPENGL
        default: return;
    }
}
// INTERNAL-ONLY FUNCTIONS
void ZTK_TitleFree(void) {ZTM8_Free(rZTK_Host.user.title);}
void ZTK_EventBufferFree(void) {ZTM8_Free(rZTK_Host.buffer.event->items[0]); ZTM_QListFree(rZTK_Host.buffer.event);}
void ZTK_EventBufferCreate(void) {
    rZTK_Host.system.flag.event = ZTK_DEFAULT_EVENT_FLAG;
    rZTK_Host.system.events.enabled = ZTK_DEFAULT_EVENT_ENABLED;
    rZTK_Host.system.events.pump = ZTK_DEFAULT_EVENT_PUMP;
    rZTK_Host.buffer.event = ZTM_QListNew(ZTK_BUFFER_EVENT);
    ZTM8_NewArray(ZTK_BUFFER_EVENT, sizeof(ZT_EVENT), 8, rZTK_Host.buffer.event->items);
}
void ZTK_DrawBufferFree(void) {
    for (ZT_INDEX i = 0; i < rZTK_Host.buffer.draw->length; i++) {
        rZTK_DRAW* lItem = rZTK_Host.buffer.draw->items[i];
        if (lItem->type == ZTK_DRAW_TYPE_TEXTCOPY && lItem->source != NULL) {ZTM8_Free((ZT_CHAR*)lItem->source);};
    }
    ZTM8_Free(rZTK_Host.buffer.draw->items[0]);
    ZTM_QListFree(rZTK_Host.buffer.draw);
}
void ZTK_DrawBufferCreate(void) {
    rZTK_Host.system.flag.draw = ZTK_DEFAULT_DRAW_FLAG;
    rZTK_Host.buffer.draw = ZTM_QListNew(ZTK_BUFFER_DRAW);
    ZTM8_NewArray(ZTK_BUFFER_DRAW, sizeof(rZTK_DRAW), 8, rZTK_Host.buffer.draw->items);
}
void ZTK_Free(void) {
    ZTK_FontFree(rZTK_Host.system.font);
    ZTK_RendererExit();
    ZTK_RuntimeFree();
    ZTK_DrawBufferFree();
    ZTK_EventBufferFree();
    ZTK_TitleFree();
    ZTL_TickResolution(0);
}
void ZTK_Open(void) {ZTK_RuntimeOpen();}
void ZTK_DrawClear(void) {
    switch (rZTK_Host.system.renderer) {
        case ZTK_RENDERER_SYSTEM: ZTK_RuntimeDrawClear(); return;
        #if defined(ZTK_BUILD_OPENGL) && (ZTK_BUILD_OPENGL)
        case ZTK_RENDERER_OPENGL: ZTGL_Clear(); return;
        #endif // ZTK_BUILD_OPENGL
        default: return;
    }
}
void ZTK_DrawSize(void) {
    ZTK_RuntimeRectLoad();
    switch (rZTK_Host.system.renderer) {
        case ZTK_RENDERER_SYSTEM: ZTK_RuntimeDrawReload(); return;
        #if defined(ZTK_BUILD_OPENGL) && (ZTK_BUILD_OPENGL)
        case ZTK_RENDERER_OPENGL: ZTGL_Size(); return;
        #endif // ZTK_BUILD_OPENGL
        default: return;
    }
}
void ZTK_DrawBufferItem(rZTK_DRAW* iObject) {
    switch (rZTK_Host.system.renderer) {
        case ZTK_RENDERER_SYSTEM:
            switch (iObject->type) {
                case ZTK_DRAW_TYPE_SPRITE: ZTK_RuntimeDrawSprite(iObject->source, &(iObject->dest)); break;
                case ZTK_DRAW_TYPE_SURFACE: ZTK_RuntimeDrawSurface(iObject->source, &(iObject->dest)); break;
                case ZTK_DRAW_TYPE_TEXT: ZTK_RuntimeDrawText(iObject->source, &(iObject->dest)); break;
                case ZTK_DRAW_TYPE_TEXTCOPY: ZTK_RuntimeDrawText(iObject->source, &(iObject->dest)); ZTM8_Free((ZT_CHAR*)iObject->source); iObject->source = NULL; break;
                default: break;
            }
            break;
        #if defined(ZTK_BUILD_OPENGL) && (ZTK_BUILD_OPENGL)
        case ZTK_RENDERER_OPENGL:
            switch (iObject->type) {
                case ZTK_DRAW_TYPE_SPRITE: ZTGL_DrawSprite(iObject->source, &(iObject->dest)); break;
                case ZTK_DRAW_TYPE_SURFACE: ZTGL_DrawSurface(iObject->source, &(iObject->dest)); break;
                case ZTK_DRAW_TYPE_TEXT: break;
                case ZTK_DRAW_TYPE_TEXTCOPY: ZTM8_Free((ZT_CHAR*)iObject->source); iObject->source = NULL; break;
                default: break;
            }
            break;
        #endif // ZTK_BUILD_OPENGL
        default: break;
    }
}
void ZTK_DrawBufferAdd(const void* iSource, ZT_FLAG iType, const ZT_RECT* iDest) {
    if (rZTK_Host.system.flag.draw & ZTK_DRAW_FLAG_ENABLED) {
        rZTK_DRAW lUnbuffered;
        rZTK_DRAW* lDraw;
        if (rZTK_Host.system.flag.draw & ZTK_DRAW_FLAG_UNBUFFERED) {lDraw = &lUnbuffered;} else {lDraw = ZTM_QListAdvanceItem(rZTK_Host.buffer.draw);}
        lDraw->flag = ZTK_DRAW_FLAG_NONE;
        lDraw->type = iType;
        lDraw->source = iSource;
        if (iDest != NULL) {
            ZTM_RectCopy(iDest, &(lDraw->dest));
        } else {
            lDraw->dest.x = 0;
            lDraw->dest.y = 0;
            lDraw->dest.w = rZTK_Host.rect.w;
            lDraw->dest.h = rZTK_Host.rect.h;
        }
        if (rZTK_Host.system.flag.draw & ZTK_DRAW_FLAG_UNBUFFERED) {ZTK_DrawBufferItem(lDraw);}
    }
}
void ZTK_DrawPresent(void) {
    if (!(rZTK_Host.system.flag.draw & ZTK_DRAW_FLAG_UNBUFFERED)) {
        rZTK_DRAW* lDraw;
        while (ZTM_QListPoll(rZTK_Host.buffer.draw, (void**)&lDraw)) {ZTK_DrawBufferItem(lDraw);}
    }
    switch (rZTK_Host.system.renderer) {
        case ZTK_RENDERER_SYSTEM: ZTK_RuntimeDrawPresent(); return;
        #if defined(ZTK_BUILD_OPENGL) && (ZTK_BUILD_OPENGL)
        case ZTK_RENDERER_OPENGL: ZTGL_Present(); return;
        #endif // ZTK_BUILD_OPENGL
        default: return;
    }
}
void ZTK_DrawSprite(ZT_SPRITE* iSprite, const ZT_RECT* iTarget) {ZTK_DrawBufferAdd(iSprite, ZTK_DRAW_TYPE_SPRITE, iTarget);}
void ZTK_DrawSurface(ZT_SURFACE* iSurface, const ZT_RECT* iTarget) {ZTK_DrawBufferAdd(iSurface, ZTK_DRAW_TYPE_SURFACE, iTarget);}
void ZTK_DrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox) {ZTK_DrawBufferAdd((ZT_CHAR*)iText, ZTK_DRAW_TYPE_TEXT, iTextBox);}
void ZTK_DrawTextDelete(ZT_CHAR* iText, const ZT_RECT* iTextBox) {ZTK_DrawBufferAdd((ZT_CHAR*)iText, ZTK_DRAW_TYPE_TEXTCOPY, iTextBox);}
ZT_INDEX ZTK_PollMessages(ZT_EVENT** iEvent) {return ZTM_QListPoll(rZTK_Host.buffer.event, (void**)iEvent);}
ZT_SURFACE* ZTK_SurfaceFromText(const ZT_CHAR* iText, ZT_FLAG* oPalette) {return ZTK_RuntimeSurfaceFromFont(iText, NULL, oPalette);}
ZT_SURFACE* ZTK_SurfaceFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_FLAG* oPalette) {return ZTK_RuntimeSurfaceFromFont(iText, iFont, oPalette);}

#endif // ZTK_C_INCLUDED
