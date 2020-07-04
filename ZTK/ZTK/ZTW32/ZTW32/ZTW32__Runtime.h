/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTW32__RUNTIME_H_INCLUDED
#define ZTW32__RUNTIME_H_INCLUDED

#include "../ZTW32.h"

typedef struct {
	ZT_WINDOW* owner;
	HINSTANCE instance;
	struct {
        HWND handle;
        MSG message;
        DWORD style;
        RECT rect;
        RECT dimensions;
        ZT_LIST* fontsLoaded;
    } window;
	struct {
        HDC main;
        HDC buffer;
        HDC pipe;
        HDC font;
    } dc;
} ZTW32_RUNTIME;

ZTW32_RUNTIME* gZTW32_RTime;

void ZTW32_HostRegister(void);
void ZTW32_HostLoadResources(void);
void ZTW32_HostFreeResources(void);
void ZTW32_HostRect(RECT* oRect, const ZT_RECT* iRect);
void ZTW32_HostRectFromIntegers(RECT* oRect, ZT_I iX, ZT_I iY, ZT_I iWidth, ZT_I iHeight);
void ZTW32_HostCommand(ZT_FLAG iWParam);
/*#define ZTW32_HostPoll() ({\
    ZT_BOOL rHOSTPOLL_m = 0x0;\
	if (gZTW32_RTime != NULL) {\
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_TIMER << 16) | PM_REMOVE) > 0) {rHOSTPOLL_m = 0x1;}\
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_MOUSEMOVE << 16) | PM_REMOVE) > 0) {rHOSTPOLL_m = 0x1;}\
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_MOUSEBUTTON << 16) | PM_REMOVE) > 0) {rHOSTPOLL_m = 0x1;}\
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_MOUSE << 16) | PM_REMOVE) > 0) {rHOSTPOLL_m = 0x1;}\
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, (QS_INPUT << 16) | PM_REMOVE) > 0) {rHOSTPOLL_m = 0x1;}\
        if (PeekMessage(&(gZTW32_RTime->window.message), NULL, 0, 0, PM_REMOVE) > 0) {rHOSTPOLL_m = 0x1;}\
	}\
	rHOSTPOLL_m;\
})*/ // that didn't work out too well...
ZT_BOOL ZTW32_HostPoll(void);
void ZTW32_HostLoop(void);
LRESULT CALLBACK ZTW32_HostMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ZTW32_HostCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void ZTW32_DrawColor(ZT_COLOR iColor);
ZT_FLAG ZTW32_DrawPaletteFromBitmap_W32(BITMAPINFO* iBitmapinfo);
void ZTW32_DrawBitmap_W32(HBITMAP iBitmap, const ZT_POINT* iBitmapSize, const ZT_RECT* iTarget, ZT_FLAG iBlendmode);
ZT_SURFACE* ZTW32_SurfaceFromBitmap_W32(HBITMAP iBitmap, ZT_FLAG* oPalette);

void ZTW32_W32_TimerKill(ZT_INDEX iID);
void ZTW32_W32_TimerSet(ZT_INDEX iID, ZT_TIME iDelay);

#include "ZTW32__Debug.h"

#endif // ZTW32__RUNTIME_H_INCLUDED
