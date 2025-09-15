/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTGL_RT_C_INCLUDED
#define ZTGL_RT_C_INCLUDED

#include "ZTGL-RT.h"

ZT_FLAG rZTGL__FLAG = ZTGL_FLAG_INIT;
rZTGL_HOST rZTGL_Host;

#if defined(ZTK_BUILD_WINDOWS) && (ZTK_BUILD_WINDOWS)
	#include "ZTW32-RT.h"
	#define ZTGL_RuntimeInit() ({\
		PIXELFORMATDESCRIPTOR lPFD;\
		ZTM8_Zero(&lPFD, sizeof(lPFD));\
		lPFD.nSize = sizeof(lPFD);\
		lPFD.nVersion = 1;\
		lPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;\
		lPFD.iPixelType = PFD_TYPE_RGBA;\
		lPFD.cColorBits = 24;\
		SetPixelFormat(rZTW32_Host.dc.main, ChoosePixelFormat(rZTW32_Host.dc.main, &lPFD), &lPFD);\
		wglMakeCurrent(rZTW32_Host.dc.main, (rZTGL_Host.runtime = wglCreateContext(rZTW32_Host.dc.main)));\
	})
	#define ZTGL_RuntimeExit() wglDeleteContext(rZTGL_Host.runtime)
	#define ZTGL_RuntimePresent() SwapBuffers(rZTW32_Host.dc.main)
#endif // ZTK_BUILD_WINDOWS

void ZTGL_Init(void) {
    if (rZTGL__FLAG & ZTGL_FLAG_INIT) {
        rZTGL__FLAG &= ~ZTGL_FLAG_INIT;
        ZTM8_Zero(&rZTGL_Host, sizeof(rZTGL_Host));
        ZTGL_RuntimeInit();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glEnable(GL_TEXTURE_2D);
    }
}
void ZTGL_Exit(void) {
    if (!(rZTGL__FLAG & ZTGL_FLAG_INIT)) {
        ZTGL_RuntimeExit();
        rZTGL__FLAG |= ZTGL_FLAG_INIT;
    }
}
void ZTGL_Present(void) {
    ZTGL_RuntimePresent();
}

#endif // ZTGL_RT_C_INCLUDED
