/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__RUNTIME_H_INCLUDED
#define ZTK__RUNTIME_H_INCLUDED

#include "../ZTK.h"

/*
typedef struct {
    ZT_TIME last;
    ZT_TIME delay;
    ZT_TIME* now;
} ZT_TIMESTAMP; // implement me!
*/
typedef struct {
	ZT_POINT pos;
	ZT_FLAG state;
	ZT_INDEX wheel;
} ZT_MOUSE;
typedef struct {
	#if (ZTK_KEY_SIZE_UNIT > 16)
	ZT_U32 state[ZTK_KEY_SIZE_UNITS];
	#elif (ZTK_KEY_SIZE_UNIT > 8)
	ZT_U16 state[ZTK_KEY_SIZE_UNITS];
	#else
	ZT_U8 state[ZTK_KEY_SIZE_UNITS];
	#endif
} ZT_KEYBOARD;
typedef struct {
	ZT_FLAG flag;
	ZT_FLAG text;
	ZT_MOUSE mouse;
	ZT_KEYBOARD keyboard;
} ZT_INPUT;
typedef struct {
    const void* source;
    ZT_FLAG flag;
    ZT_FLAG type;
    ZT_RECT dest;
} ZT_DRAW;
typedef struct {
	struct {
        void (*loop)(void);
        void* runtime;
        struct {
            ZT_INPUT input;
            ZT_RECT rect;
            ZT_FLAG flag;
            ZT_FLAG state;
        } cache;
        ZT_INPUT input;
        ZT_FLAG flag;
        ZT_FLAG state;
        ZT_FLAG type;
        ZT_FLAG style;
        struct {
            ZT_FLAG flag;
            ZT_TIME resolution;
            ZT_TIME heartbeat;
            ZT_INDEX heartbeatCount;
            ZT_TIME idleLast;
            ZT_TIME idleHoldoff;
            ZT_TIME loopLast;
            ZT_TIME loopNow;
            ZT_TIME eventLast;
            ZT_TIME eventMin;
            ZT_TIME repeater;
        } timer;
        struct {
            ZT_FLAG flag;
            ZT_FLAG enabled;
            ZT_FLAG disabled;
            ZT_FLAG capture;
            ZT_FLAG pump;
            ZT_FLAG raw;
            ZT_QLIST* buffer;
        } events;
        struct {
            ZT_FONT window;
        } font;
        struct {
            ZT_FLAG flag;
            ZT_QLIST* buffer;
        } draw;
    } system;
	struct {
        ZT_FLAG options;
        ZT_FLAG palette;
        ZT_COLOR background;
        ZT_CHAR* title;
        ZT_CHAR* icon;
        ZT_FONT* font;
    } user;
    ZT_RECT rect;
} ZT_WINDOW;

ZT_WINDOW* gZT_Window;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
// INTERNAL-ONLY FUNCTION PROTOTYPES
void ZTK_Now(void);
void ZTK_Close(void);
void ZTK_Destroy(void);
void ZTK_HostProcess(void);
void ZTK_Process(void);
void ZTK_Wake(void);
void ZTK_User(void);
void ZTK_TitleFree(void);
void ZTK_EventBufferCreate(void);
void ZTK_DrawBufferCreate(void);
void ZTK_EventBufferFree(void);
void ZTK_DrawBufferFree(void);
void ZTK_DrawBufferAdd(const void* iSource, ZT_FLAG iType, const ZT_RECT* iDest);
void ZTK_DrawBufferItem(const ZT_DRAW* iObject);
void ZTK_DrawBuffer(void);
void ZTK_FontCharsetFree(ZT_FONT* iFont);
void ZTK_FontCharsetNew(ZT_FONT* iFont);

#ifdef __cplusplus
}
#endif // __cplusplus
#ifdef ZTM_ARCH__WIN
#if (ZTM_ARCH__BIT > 32)
#define ZTK_WINDOW_TYPE_COMPILED ZTK_WINDOW_TYPE_WIN64
#else
#define ZTK_WINDOW_TYPE_COMPILED ZTK_WINDOW_TYPE_WIN32
#endif
#define ZTK_DEFAULT_PALETTE_SYSTEM ZTM_PALETTE_ARGB
#define ZTK_DEFAULT_PALETTE_SYSTEM_INPUT ZTM_PALETTE_ABGR
#include "ZTW32/ZTW32.h"
#ifdef ZTK_MACRO
#define ZTK_RuntimeTicks() ZTW32_Ticks()
#define ZTK_RuntimeGetScreenWidth() ZTW32_ScreenWidth()
#define ZTK_RuntimeGetScreenHeight() ZTW32_ScreenHeight()
#define ZTK_RuntimeLoop() ZTW32_HostLoop()
#define ZTK_RuntimeKeyReload(STATE_OUT) ZTW32_HostLoadKey(STATE_OUT)
#define ZTK_RuntimeLoad() ZTW32_New(gZT_Window)
#define ZTK_RuntimeFree() ZTW32_Free()
#define ZTK_RuntimeRectReload() ZTW32_RectReload()
#define ZTK_RuntimeRectApply() ZTW32_RectApply()
#define ZTK_RuntimeWindowReload() ZTW32_RectReload(); ZTW32_RectApply()
#define ZTK_RuntimeFontFree(FONT) ZTW32_HostFreeFont(FONT)
#define ZTK_RuntimeFontLoad(FONT) ZTW32_HostLoadFont(FONT)
#define ZTK_RuntimeFontWindow() ZTW32_DrawLoadFont()
#define ZTK_RuntimeDrawColorsReload() ZTW32_DrawLoadColors()
#define ZTK_RuntimeHeartbeat() ZTW32_TimerHeartbeat()
#define ZTK_RuntimeHeartbeatStop() ZTW32_TimerHeartbeatStop()
#define ZTK_RuntimeWake(DELAY) ZTW32_TimerWake(DELAY)
#define ZTK_RuntimeWakeStop() ZTW32_TimerWakeStop()
#define ZTK_RuntimeWait() ZTW32_HostWait()
#define ZTK_RuntimeWindowDestroy() ZTW32_WindowDestroy()
#define ZTK_RuntimeWindowOpen() ZTW32_WindowOpen()
#define ZTK_RuntimeProcess() ZTW32_HostProcess()
#define ZTK_RuntimeDrawReload() ZTW32_DrawReset()
#define ZTK_RuntimeDrawClear() ZTW32_DrawClear()
#define ZTK_RuntimeDrawPresent() ZTW32_DrawPresent()
#define ZTK_RuntimeDrawBackground()  ZTW32_DrawBackground()
#define ZTK_RuntimeDrawSurface(SURFACE,RECT) ZTW32_DrawSurface(SURFACE, RECT, ZTK_WINDOW_BLENDMODE_ALPHA)
#define ZTK_RuntimeDrawSprite(SPRITE,RECT) ZTW32_DrawSprite(SPRITE, RECT, ZTK_WINDOW_BLENDMODE_ALPHA)
#define ZTK_RuntimeDrawText(TEXT,RECT) ZTW32_DrawText(TEXT,RECT)
#define ZTK_RuntimeGetDrawTextSize(TEXT,SIZE_OUT) ZTW32_GetDrawTextSize(TEXT, SIZE_OUT)
#define ZTK_RuntimeSpriteFree(SPRITE) ZTW32_SpriteFree_W32(SPRITE)
#define ZTK_RuntimeSpriteOptimize(SPRITE,SOURCE,BLOCK,TYPE,PALLETE) ZTW32_Sprite_W32(SPRITE,SOURCE,BLOCK,TYPE,PALLETE)
#define ZTK_RuntimeMessages() ZTW32_HostMessages()
#define ZTK_RuntimeSurfaceFromBitmap(PATH,TPCOLOR,OPACITY,PALETTE_OUT) ZTW32_SurfaceFromBitmapFile(PATH, TPCOLOR, OPACITY, PALETTE_OUT)
#define ZTK_RuntimeSurfaceFromFont(TEXT,FONT,PALETTE_OUT) ZTW32_SurfaceFromFont(TEXT, FONT, PALETTE_OUT)
#define ZTK_RuntimeSizeFromFont(TEXT,FONT,SIZE_OUT) ZTW32_SizeFromFont(TEXT, FONT, SIZE_OUT)
#else
ZT_I ZTK_RuntimeGetScreenWidth(void);
ZT_I ZTK_RuntimeGetScreenHeight(void);
void ZTK_RuntimeLoop(void);
ZT_TIME ZTK_RuntimeTicks(void);
void ZTK_RuntimeKeyReload(ZT_U8* oTarget);
void ZTK_RuntimeLoad(void);
void ZTK_RuntimeFree(void);
void ZTK_RuntimeRectReload(void);
void ZTK_RuntimeRectApply(void);
void ZTK_RuntimeWindowReload(void);
void ZTK_RuntimeFontFree(ZT_FONT* iFont);
void ZTK_RuntimeFontLoad(ZT_FONT* iFont);
void ZTK_RuntimeFontWindow(void);
void ZTK_RuntimeDrawColorsReload(void);
void ZTK_RuntimeHeartbeat(void);
void ZTK_RuntimeHeartbeatStop(void);
void ZTK_RuntimeWake(ZT_TIME iDelay);
void ZTK_RuntimeWakeStop(void);
void ZTK_RuntimeWait(void);
void ZTK_RuntimeWindowDestroy(void);
void ZTK_RuntimeWindowOpen(void);
void ZTK_RuntimeProcess(void);
void ZTK_RuntimeDrawReload(void);
void ZTK_RuntimeDrawClear(void);
void ZTK_RuntimeDrawPresent(void);
void ZTK_RuntimeDrawBackground(void);
void ZTK_RuntimeDrawSurface(ZT_SURFACE* iSurface, const ZT_RECT* iTarget);
void ZTK_RuntimeDrawSprite(ZT_SPRITE* iSprite, const ZT_RECT* iTarget);
void ZTK_RuntimeDrawText(const ZT_U8* iText, const ZT_RECT* iTextBox);
void ZTK_RuntimeGetDrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize);
void ZTK_RuntimeSpriteFree(ZT_SPRITE* iSprite);
void ZTK_RuntimeSpriteOptimize(ZT_SPRITE* iSprite, const void* iSource, const ZT_POINT* iBlock, ZT_FLAG iType, ZT_FLAG iPalette);
ZT_INDEX ZTK_RuntimeMessages(void);
ZT_SURFACE* ZTK_RuntimeSurfaceFromBitmap(const ZT_CHAR* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacity, ZT_FLAG* oPalette);
ZT_SURFACE* ZTK_RuntimeSurfaceFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_FLAG* oPalette);
void ZTK_RuntimeSizeFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_POINT* oSize);
#endif // ZTK_MACRO
#else
#define ZTK_WINDOW_TYPE_COMPILED ZTK_WINDOW_TYPE_UNKNOWN
#define ZTK_DEFAULT_PALETTE_SYSTEM ZTM_PALETTE_RGBA
#define ZTK_DEFAULT_PALETTE_SYSTEM_INPUT ZTM_PALETTE_RGBA
#endif // ZTM_ARCH__

#include "ZTK__Event.h"
#include "ZTK__MSG.h"

#endif // ZTK__RUNTIME_H_INCLUDED
