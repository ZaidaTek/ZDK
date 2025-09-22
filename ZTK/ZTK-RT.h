/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_RT_H_INCLUDED
#define ZTK_RT_H_INCLUDED

#include "ZTK.h"

// #include "ZTK__Defines.h"
// 25256, from ZTK__Defines: ///"export all this to __runtime, and delete this file"
#define ZTK_FLAG_NONE 0x0
#define ZTK_KEY_SIZE_LENGTH 0x100
#define ZTK_KEY_SIZE_SHIFT 5
#define ZTK_KEY_SIZE_UNIT 32
#define ZTK_KEY_SIZE_UNITS (ZTK_KEY_SIZE_LENGTH / ZTK_KEY_SIZE_UNIT)
#define ZTK_BLENDMODE_BLOT 0x0
#define ZTK_BLENDMODE_ALPHA 0x1
#define ZTK_DRAW_FLAG_NONE ZTK_FLAG_NONE
#define ZTK_DRAW_FLAG_ENABLED 0x1
#define ZTK_DRAW_FLAG_UNBUFFERED 0x10
#define ZTK_DRAW_TYPE_SPRITE 0x1
#define ZTK_DRAW_TYPE_SURFACE 0x2
#define ZTK_DRAW_TYPE_TEXT 0x4
#define ZTK_DRAW_TYPE_TEXTCOPY 0x8
#define ZTK_WINDOW_INPUT_CHAR 0x1
#define ZTK_BUFFER_EVENT 16384
#define ZTK_BUFFER_DRAW 8192
#define ZTK_BUFFER_INPUT_TEXT 4
#define ZTK_DEFAULT_RENDERER ZTK_RENDERER_SYSTEM
#define ZTK_DEFAULT_EVENT_ENABLED ZTK_HID_ALL
#define ZTK_DEFAULT_EVENT_PUMP (ZTK_HID_MOUSE | ZTK_HID_KEY)
#define ZTK_DEFAULT_EVENT_FLAG ZTK_FLAG_NONE //(ZTK_EVENT_FLAG_SIMPLE)
//#define ZTK_DEFAULT_DRAW_FLAG (ZTK_DRAW_FLAG_ENABLED | ZTK_DRAW_FLAG_UNBUFFERED)
#define ZTK_DEFAULT_DRAW_FLAG ZTK_DRAW_FLAG_ENABLED
#define ZTK_DEFAULT_TIMER_RESOLUTION 1
#define ZTK_DEFAULT_TIMER_PUMP 5
#define ZTK_DEFAULT_INPUT_FLAG ZTK_FLAG_NONE
// /#include "ZTK__Defines.h"

typedef struct {
    void* data;
    void* dummy; //alignment
    ZT_POINT block;
    ZT_FLAG type;
    ZT_FLAG palette;
} rZT_SPRITE;
typedef struct {
    void* runtime;
    void** charset;
    void* source;
    ZT_CHAR* name;
	ZT_FLAG type;
	ZT_FLAG flag;
	ZT_FLAG style;
	ZT_INDEX height;
	ZT_COLOR color;
	ZT_COLOR colorBk;
} rZT_FONT;
typedef struct {
	ZT_POINT pos;
	ZT_FLAG state;
	ZT_INDEX wheel;
} rZTK_MOUSE;
typedef struct {
	#if (ZTK_KEY_SIZE_UNIT > 16)
	ZT_U32 state[ZTK_KEY_SIZE_UNITS];
	#elif (ZTK_KEY_SIZE_UNIT > 8)
	ZT_U16 state[ZTK_KEY_SIZE_UNITS];
	#else
	ZT_U8 state[ZTK_KEY_SIZE_UNITS];
	#endif
} rZTK_KEYBOARD;
typedef struct {
	ZT_FLAG flag;
	ZT_FLAG text;
	rZTK_MOUSE mouse;
	rZTK_KEYBOARD keyboard;
} rZTK_INPUT;
typedef struct {
    const void* source;
    const void* dummy; //alignment
    ZT_RECT dest;
    ZT_FLAG flag;
    ZT_FLAG type;
} rZTK_DRAW;
typedef struct {
    void (*loop)(void);
    //void* runtime;
    void* dummy; //alignment
    struct {
        ZT_QLIST* event;
        ZT_QLIST* draw;
        rZTK_INPUT input;
        ZT_RECT rect;
        ZT_FLAG flag;
        ZT_FLAG state;
    } buffer;
    ZT_RECT rect;
	struct {
        struct {
            ZT_TIME loop;
            ZT_TIME event;
            ZT_TIME repeat;
            ZT_TIME dummy; // alignment
        } last;
        struct {
            ZT_TIME resolution;
            ZT_TIME event;
        } timer;
        struct {
            ZT_FLAG draw;
            ZT_FLAG event;
        } flag;
        struct {
            ZT_FLAG enabled;
            ZT_FLAG pump;
        } events;
        rZTK_INPUT input;
        ZT_FLAG renderer;
        ZT_FLAG palette;
        ZT_FLAG state;
        ZT_FLAG type;
        ZT_FLAG style;
        rZT_FONT* font;
    } system;
	struct {
        ZT_FLAG options;
        ZT_FLAG palette;
        ZT_COLOR background;
        ZT_CHAR* title;
        ZT_CHAR* icon;
        rZT_FONT* font;
    } user;
} rZTK_HOST;

extern rZTK_HOST rZTK_Host;

#if defined(ZTK_BUILD_WINDOWS) && (ZTK_BUILD_WINDOWS)

	#if (ZTK_BUILD_WIDTH > 32)
		#define ZTK_TYPE_COMPILED ZTK_TYPE_WIN64
	#else
		#define ZTK_TYPE_COMPILED ZTK_TYPE_WIN32
	#endif
	#define ZTK_PALETTE_SYSTEM ZTM_PALETTE_ARGB
	#define ZTK_PALETTE_OPENGL ZTM_PALETTE_ABGR // I guess? Note: Apparently, endianess plays a roll in this
	#define ZTK_PALETTE_BRUSH ZTM_PALETTE_ABGR
	
	#include "ZTWIN.h"
	#define ZTK_RuntimeQuit() ZTW32_Quit()
	#define ZTK_RuntimeLoop() ZTW32_Loop()
	#define ZTK_RuntimeKeyReload(STATE_OUT) ZTW32_KeyLoad(STATE_OUT)
	#define ZTK_RuntimeLoad() ZTW32_New()
	#define ZTK_RuntimeFree() ZTW32_Free()
	#define ZTK_RuntimeRectLoad() ZTW32_RectLoad()
	#define ZTK_RuntimeRectApply() ZTW32_RectLoad(); ZTW32_RectApply()
	#define ZTK_RuntimeFontSourceFree(FONT) ZTW32_FontFreeSource(FONT)
	#define ZTK_RuntimeFontSourceLoad(FONT) ZTW32_FontLoadSource(FONT)
	#define ZTK_RuntimeFontRuntimeFree(FONT) ZTW32_FontFreeRuntime(FONT)
	#define ZTK_RuntimeFontRuntimeLoad(FONT) ZTW32_FontLoadRuntime(FONT)
	#define ZTK_RuntimeFontWindow() ZTW32_DrawFontLoad()
	#define ZTK_RuntimeOpen() ZTW32_Open()
	#define ZTK_RuntimeProcess() ZTW32_Process()
	#define ZTK_RuntimeDrawReload() ZTW32_DrawSize()
	#define ZTK_RuntimeDrawClear() ZTW32_DrawClear()
	#define ZTK_RuntimeDrawPresent() ZTW32_DrawPresent()
	#define ZTK_RuntimeDrawClearColor(COLOR) ZTW32_DrawClearColor(COLOR)
	#define ZTK_RuntimeDrawSurface(SURFACE,RECT) ZTW32_DrawSurface(SURFACE, RECT, ZTK_BLENDMODE_ALPHA)
	#define ZTK_RuntimeDrawSprite(SPRITE,RECT) ZTW32_DrawSprite(SPRITE, RECT, ZTK_BLENDMODE_ALPHA)
	#define ZTK_RuntimeDrawText(TEXT,RECT) ZTW32_DrawText(TEXT,RECT)
	#define ZTK_RuntimeGetDrawTextSize(TEXT,SIZE_OUT) ZTW32_DrawTextSize(TEXT, SIZE_OUT)
	#define ZTK_RuntimeSpriteFree(SPRITE) ZTW32_SpriteFree(SPRITE)
	#define ZTK_RuntimeSprite(SOURCE,BLOCK,PALLETE) ZTW32_Sprite(SOURCE,BLOCK,PALLETE)
	#define ZTK_RuntimeSurfaceFromFont(TEXT,FONT,PALETTE_OUT) ZTW32_SurfaceFromFont(TEXT, FONT, PALETTE_OUT)
	#define ZTK_RuntimeSizeFromFont(TEXT,FONT,SIZE_OUT) ZTW32_SizeFromFont(TEXT, FONT, SIZE_OUT)

#elif defined(ZTK_BUILD_LINUX) && (ZTK_BUILD_LINUX)

	#if (ZTK_BUILD_WIDTH > 32)
		#define ZTK_TYPE_COMPILED ZTK_TYPE_LNX64
	#else
		#define ZTK_TYPE_COMPILED ZTK_TYPE_LNX32
	#endif
	#define ZTK_PALETTE_SYSTEM ZTM_PALETTE_RGBA
	#define ZTK_PALETTE_OPENGL ZTM_PALETTE_RGBA
	#define ZTK_PALETTE_BRUSH ZTM_PALETTE_RGBA
	
	#if defined(ZTK_BUILD_XCB) && (ZTK_BUILD_XCB)
		#include "ZTXCB.h"
		#define ZTK_RuntimeQuit() ZTXCB_Quit()
		#define ZTK_RuntimeLoop() ZTXCB_Loop()
		#define ZTK_RuntimeKeyReload(STATE_OUT) ZTXCB_KeyLoad(STATE_OUT)
		#define ZTK_RuntimeLoad() ZTXCB_New()
		#define ZTK_RuntimeFree() ZTXCB_Free()
		#define ZTK_RuntimeRectLoad() ZTXCB_RectLoad()
		#define ZTK_RuntimeRectApply() ZTXCB_RectLoad(); ZTXCB_RectApply()
		#define ZTK_RuntimeFontSourceFree(FONT) ZTXCB_FontFreeSource(FONT)
		#define ZTK_RuntimeFontSourceLoad(FONT) ZTXCB_FontLoadSource(FONT)
		#define ZTK_RuntimeFontRuntimeFree(FONT) ZTXCB_FontFreeRuntime(FONT)
		#define ZTK_RuntimeFontRuntimeLoad(FONT) ZTXCB_FontLoadRuntime(FONT)
		#define ZTK_RuntimeFontWindow() ZTXCB_DrawFontLoad()
		#define ZTK_RuntimeOpen() ZTXCB_Open()
		#define ZTK_RuntimeProcess() ZTXCB_Process()
		#define ZTK_RuntimeDrawReload() ZTXCB_DrawSize()
		#define ZTK_RuntimeDrawClear() ZTXCB_DrawClear()
		#define ZTK_RuntimeDrawPresent() ZTXCB_DrawPresent()
		#define ZTK_RuntimeDrawClearColor(COLOR) ZTXCB_DrawClearColor(COLOR)
		#define ZTK_RuntimeDrawSurface(SURFACE,RECT) ZTXCB_DrawSurface(SURFACE, RECT, ZTK_BLENDMODE_ALPHA)
		#define ZTK_RuntimeDrawSprite(SPRITE,RECT) ZTXCB_DrawSprite(SPRITE, RECT, ZTK_BLENDMODE_ALPHA)
		#define ZTK_RuntimeDrawText(TEXT,RECT) ZTXCB_DrawText(TEXT,RECT)
		#define ZTK_RuntimeGetDrawTextSize(TEXT,SIZE_OUT) ZTXCB_DrawTextSize(TEXT, SIZE_OUT)
		#define ZTK_RuntimeSpriteFree(SPRITE) ZTXCB_SpriteFree(SPRITE)
		#define ZTK_RuntimeSprite(SOURCE,BLOCK,PALLETE) ZTXCB_Sprite(SOURCE,BLOCK,PALLETE)
		#define ZTK_RuntimeSurfaceFromFont(TEXT,FONT,PALETTE_OUT) ZTXCB_SurfaceFromFont(TEXT, FONT, PALETTE_OUT)
		#define ZTK_RuntimeSizeFromFont(TEXT,FONT,SIZE_OUT) ZTXCB_SizeFromFont(TEXT, FONT, SIZE_OUT)
	#else // ZTK_BUILD_XCB
		#define ZTK_BUILD_X11 0x1 // TODO into ZTK-BUILD.h
		#include "ZTX11.h"
		#define ZTK_RuntimeQuit() ZTX11_Quit()
		#define ZTK_RuntimeLoop() ZTX11_Loop()
		#define ZTK_RuntimeKeyReload(STATE_OUT) ZTX11_KeyLoad(STATE_OUT)
		#define ZTK_RuntimeLoad() ZTX11_New()
		#define ZTK_RuntimeFree() ZTX11_Free()
		#define ZTK_RuntimeRectLoad() ZTX11_RectLoad()
		#define ZTK_RuntimeRectApply() ZTX11_RectLoad(); ZTX11_RectApply()
		#define ZTK_RuntimeFontSourceFree(FONT) ZTX11_FontFreeSource(FONT)
		#define ZTK_RuntimeFontSourceLoad(FONT) ZTX11_FontLoadSource(FONT)
		#define ZTK_RuntimeFontRuntimeFree(FONT) ZTX11_FontFreeRuntime(FONT)
		#define ZTK_RuntimeFontRuntimeLoad(FONT) ZTX11_FontLoadRuntime(FONT)
		#define ZTK_RuntimeFontWindow() ZTX11_DrawFontLoad()
		#define ZTK_RuntimeOpen() ZTX11_Open()
		#define ZTK_RuntimeProcess() ZTX11_Process()
		#define ZTK_RuntimeDrawReload() ZTX11_DrawSize()
		#define ZTK_RuntimeDrawClear() ZTX11_DrawClear()
		#define ZTK_RuntimeDrawPresent() ZTX11_DrawPresent()
		#define ZTK_RuntimeDrawClearColor(COLOR) ZTX11_DrawClearColor(COLOR)
		#define ZTK_RuntimeDrawSurface(SURFACE,RECT) ZTX11_DrawSurface(SURFACE, RECT, ZTK_BLENDMODE_ALPHA)
		#define ZTK_RuntimeDrawSprite(SPRITE,RECT) ZTX11_DrawSprite(SPRITE, RECT, ZTK_BLENDMODE_ALPHA)
		#define ZTK_RuntimeDrawText(TEXT,RECT) ZTX11_DrawText(TEXT,RECT)
		#define ZTK_RuntimeGetDrawTextSize(TEXT,SIZE_OUT) ZTX11_DrawTextSize(TEXT, SIZE_OUT)
		#define ZTK_RuntimeSpriteFree(SPRITE) ZTX11_SpriteFree(SPRITE)
		#define ZTK_RuntimeSprite(SOURCE,BLOCK,PALLETE) ZTX11_Sprite(SOURCE,BLOCK,PALLETE)
		#define ZTK_RuntimeSurfaceFromFont(TEXT,FONT,PALETTE_OUT) ZTX11_SurfaceFromFont(TEXT, FONT, PALETTE_OUT)
		#define ZTK_RuntimeSizeFromFont(TEXT,FONT,SIZE_OUT) ZTX11_SizeFromFont(TEXT, FONT, SIZE_OUT)
	#endif // ZTK_BUILD_XCB

#else

	#if (ZTK_BUILD_WIDTH > 32)
		#define ZTK_TYPE_COMPILED ZTK_TYPE_UNK64
	#else
		#define ZTK_TYPE_COMPILED ZTK_TYPE_UNK32
	#endif
	#define ZTK_PALETTE_SYSTEM ZTM_PALETTE_RGBA
	#define ZTK_PALETTE_OPENGL ZTM_PALETTE_RGBA
	#define ZTK_PALETTE_BRUSH ZTM_PALETTE_RGBA

#endif // ZTK_BUILD_OS

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTK_DrawSize(void);
void ZTK_Process(void);
void ZTK_User(void);
void ZTK_TitleFree(void);
void ZTK_EventBufferCreate(void);
void ZTK_DrawBufferCreate(void);
void ZTK_EventBufferFree(void);
void ZTK_DrawBufferFree(void);
void ZTK_DrawBufferAdd(const void* iSource, ZT_FLAG iType, const ZT_RECT* iDest);
void ZTK_DrawBufferItem(rZTK_DRAW* iObject);
void ZTK_DrawBuffer(void);
const ZT_RECT* ZTK_InternalRect(void);
const ZT_POINT* ZTK_InternalPos(void);
const ZT_POINT* ZTK_InternalSize(void);
const ZT_I* ZTK_InternalX(void);
const ZT_I* ZTK_InternalY(void);
const ZT_I* ZTK_InternalWidth(void);
const ZT_I* ZTK_InternalHeight(void);
const ZT_TIME* ZTK_InternalTick(void);
const ZT_FLAG* ZTK_InternalPalette(void);
const ZT_FLAG* ZTK_InternalPaletteSystem(void);
const ZT_POINT* ZTK_InternalMousePos(void);
const ZT_FLAG* ZTK_InternalMouseState(void);
const ZT_COLOR* ZTK_InternalBackground(void);
rZT_FONT** ZTK_InternalFont(void);
rZT_FONT** ZTK_InternalFontSystem(void);
#ifdef __cplusplus
}
#endif // __cplusplus

#include "ZTK-RT-EVENT.h"
#include "ZTK-RT-MSG.h"

#include "ZTK-RT-Font.h"
#include "ZTK-RT-Printer.h"

#if defined(ZTK_BUILD_OPENGL) && (ZTK_BUILD_OPENGL)
#include "ZTGL.h"
#endif // ZTK_BUILD_OPENGL

#endif // ZTK_RT_H_INCLUDED
