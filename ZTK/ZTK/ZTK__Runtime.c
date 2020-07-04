/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK__RUNTIME_C_INCLUDED
#define ZTK__RUNTIME_C_INCLUDED


#include "ZTK__Runtime.h"

#ifndef ZTK_MACRO
#ifdef ZTM_ARCH__WIN
ZT_TIME ZTK_RuntimeTicks(void) {return ZTW32_Ticks();}
ZT_I ZTK_RuntimeGetScreenWidth(void) {return ZTW32_ScreenWidth();}
ZT_I ZTK_RuntimeGetScreenHeight(void) {return ZTW32_ScreenHeight();}
void ZTK_RuntimeLoop(void) {ZTW32_HostLoop();}
void ZTK_RuntimeKeyReload(ZT_U8* oTarget) {ZTW32_HostLoadKey(oTarget);}
void ZTK_RuntimeLoad(void) {ZTW32_New(gZT_Window);}
void ZTK_RuntimeFree(void) {ZTW32_Free();}
void ZTK_RuntimeRectReload(void) {ZTW32_RectReload();}
void ZTK_RuntimeRectApply(void) {ZTW32_RectApply();}
void ZTK_RuntimeWindowReload(void) {ZTW32_RectReload(); ZTW32_RectApply();}
void ZTK_RuntimeFontFree(ZT_FONT* iFont) {ZTW32_HostFreeFont(iFont);}
void ZTK_RuntimeFontLoad(ZT_FONT* iFont) {ZTW32_HostLoadFont(iFont);}
void ZTK_RuntimeFontWindow(void) {ZTW32_DrawLoadFont();}
void ZTK_RuntimeDrawColorsReload(void) {ZTW32_DrawLoadColors();}
void ZTK_RuntimeHeartbeat(void) {ZTW32_TimerHeartbeat();}
void ZTK_RuntimeHeartbeatStop(void) {ZTW32_TimerHeartbeatStop();}
void ZTK_RuntimeWake(ZT_TIME iDelay) {ZTW32_TimerWake(iDelay);}
void ZTK_RuntimeWakeStop(void) {ZTW32_TimerWakeStop();}
void ZTK_RuntimeWait(void) {ZTW32_HostWait();}
void ZTK_RuntimeWindowDestroy(void) {ZTW32_WindowDestroy();}
void ZTK_RuntimeWindowOpen(void) {ZTW32_WindowOpen();}
void ZTK_RuntimeProcess(void) {ZTW32_HostProcess();}
void ZTK_RuntimeDrawReload(void) {ZTW32_DrawReset();}
void ZTK_RuntimeDrawClear(void) {ZTW32_DrawClear();}
void ZTK_RuntimeDrawPresent(void) {ZTW32_DrawPresent();}
void ZTK_RuntimeDrawBackground(void)  {ZTW32_DrawBackground();}
void ZTK_RuntimeDrawSurface(ZT_SURFACE* iSurface, const ZT_RECT* iTarget) {ZTW32_DrawSurface(iSurface, iTarget, ZTK_WINDOW_BLENDMODE_ALPHA);}
void ZTK_RuntimeDrawSprite(ZT_SPRITE* iSprite, const ZT_RECT* iTarget) {ZTW32_DrawSprite(iSprite, iTarget, ZTK_WINDOW_BLENDMODE_ALPHA);}
void ZTK_RuntimeDrawText(const ZT_CHAR* iText, const ZT_RECT* iTextBox) {ZTW32_DrawText(iText, iTextBox);}
void ZTK_RuntimeGetDrawTextSize(const ZT_CHAR* iText, ZT_POINT* oTextSize) {ZTW32_GetDrawTextSize(iText, oTextSize);}
void ZTK_RuntimeSpriteFree(ZT_SPRITE* iSprite) {ZTW32_SpriteFree_W32(iSprite);}
ZT_SPRITE* ZTK_RuntimeSpriteOptimize(ZT_SPRITE* iSprite, const void* iSource, const ZT_POINT* iBlock, ZT_FLAG iType, ZT_FLAG iPalette) {return ZTW32_Sprite_W32(iSprite, iSource, iBlock, iType, iPalette);}
ZT_INDEX ZTK_RuntimeMessages(void) {return ZTW32_HostMessages();}
ZT_SURFACE* ZTK_RuntimeSurfaceFromBitmap(const ZT_CHAR* iPath, ZT_COLOR iTransparent, ZT_INDEX iOpacity, ZT_FLAG* oPalette) {return ZTW32_SurfaceFromBitmapFile(iPath, iTransparent, iOpacity, oPalette);}
ZT_SURFACE* ZTK_RuntimeSurfaceFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_FLAG* oPalette) {return ZTW32_SurfaceFromFont(iText, iFont, oPalette);}
void ZTK_RuntimeSizeFromFont(const ZT_CHAR* iText, ZT_FONT* iFont, ZT_POINT* oSize) {ZTW32_SizeFromFont(iText, iFont, oSize);}
#endif // ZTM_ARCH__WIN
#endif // ZTK_MACRO


#endif // ZTK__RUNTIME_C_INCLUDED
