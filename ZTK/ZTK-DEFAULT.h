/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTK_DEFAULT_H_INCLUDED
#define ZTK_DEFAULT_H_INCLUDED

#define ZTK_DEFAULT_OPENGL_ENABLED 0x1

#define ZTK_DEFAULT_TITLE "Default ZTK Engine Window Title"
#define ZTK_DEFAULT_PALETTE_USER ZTM_PALETTE_RGBA
#define ZTK_DEFAULT_BACKGROUND 0x000000ff
#define ZTK_DEFAULT_POS_X 64
#define ZTK_DEFAULT_POS_Y 64
#define ZTK_DEFAULT_WIDTH 256
#define ZTK_DEFAULT_HEIGHT 128
#define ZTK_DEFAULT_FONT_STYLE ZTK_FONT_STYLE_NORMAL
#define ZTK_DEFAULT_FONT_SIZE 18
#define ZTK_DEFAULT_FONT_COLOR 0xffffffff

#if defined(ZTK_BUILD_WINDOWS) && (ZTK_BUILD_WINDOWS)
	#define ZTK_DEFAULT_FONT_SOURCE NULL
	#define ZTK_DEFAULT_FONT "MS Sans Serif"
#else // ZTK_BUILD_WINDOWS
	#define ZTK_DEFAULT_FONT_SOURCE "OpenSans/OpenSans-Regular.ttf"
	#define ZTK_DEFAULT_FONT "Open Sans"
#endif // ZTK_BUILD_WINDOWS

#endif // ZTK_DEFAULT_H_INCLUDED
