/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI__DEFINES_H_INCLUDED
#define ZUI__DEFINES_H_INCLUDED

#define ZUI_BUFFER_ELEMENT 128
#define ZUI_BUFFER_EVENTS 1024

#define ZUI_FLAG_NONE 0x0
#define ZUI_FLAG_FLUSH 0x1

#define ZUI_CURSOR_PERIOD 500

#define ZUI_COLOR_MOD_MIN 63
#define ZUI_COLOR_MOD_MAX 224
#define ZUI_COLOR_MOD_PERIOD 4000
#define ZUI_COLOR_MOD_SEED 0x0 // 0 to seed time
#define ZUI_COLOR_NONE ZTM_COLOR_TRANSPARENT
#define ZUI_COLOR_TRANSPARENT ZUI_COLOR_NONE
#define ZUI_COLOR_BLACK ZTM_COLOR_BLACK
#define ZUI_COLOR_RED ZTM_COLOR_RED
#define ZUI_COLOR_YELLOW ZTM_COLOR_YELLOW
#define ZUI_COLOR_GRAY ZTM_COLOR_GRAY
#define ZUI_COLOR_LIGHT_GRAY ZTM_COLOR_LIGHT_GRAY
#define ZUI_COLOR_WHITE ZTM_COLOR_WHITE
#define ZUI_COLOR_MEDIUM_GRAY 0xa0a0a0ff
#define ZUI_COLOR_CURSOR ZUI_COLOR_RED

#define ZUI_ELEMENT_FLAG_NONE ZUI_FLAG_NONE
#define ZUI_ELEMENT_FLAG_DISABLE 0x1
#define ZUI_ELEMENT_FLAG_SHOW 0x2
#define ZUI_ELEMENT_FLAG_COLLIDE 0x4
#define ZUI_ELEMENT_FLAG_INTERACTIVE (ZUI_ELEMENT_FLAG_DISABLE | ZUI_ELEMENT_FLAG_SHOW | ZUI_ELEMENT_FLAG_COLLIDE)
#define ZUI_ELEMENT_FLAG_NONINTERACTIVE (ZUI_ELEMENT_FLAG_DISABLE | ZUI_ELEMENT_FLAG_SHOW)

#define ZUI_ELEMENT_STYLE_NONE ZUI_FLAG_NONE

#define ZUI_UIS_LENGTH_MAX 0xff
#define ZUI_UIS_MASK 0xffff
#define ZUI_UIS_MASK_INDEX 0xff000000
#define ZUI_UIS_SHIFT 0
#define ZUI_UIS_SHIFT_INDEX 24
#define ZUI_UIS_FOCUS 0x20
#define ZUI_UIS_RELEASE 0x10
#define ZUI_UIS_PRESS 0x8
#define ZUI_UIS_HOVER 0x4
#define ZUI_UIS_NORMAL 0x2
#define ZUI_UIS_DISABLED 0x1
#define ZUI_UIS_NONE 0x0
#define ZUI_UIS_ALL ((ZUI_UIS_DISABLED | ZUI_UIS_NORMAL | ZUI_UIS_HOVER | ZUI_UIS_PRESS | ZUI_UIS_RELEASE | ZUI_UIS_FOCUS) & ZUI_UIS_MASK)

#define ZUI_ELEMENT_TYPE_NONE 0x0
#define ZUI_ELEMENT_TYPE_BUTTON 0x1
#define ZUI_ELEMENT_TYPE_BOX 0x2
#define ZUI_ELEMENT_TYPE_LABEL 0x4
#define ZUI_ELEMENT_TYPE_COUNTER 0x100
#define ZUI_ELEMENT_TYPE_SWITCH 0x200

#define ZUI_UI_TYPE_NONE 0x0
#define ZUI_UI_TYPE_GENERIC 0x1
#define ZUI_UI_TYPE_PRINT_DATA 0x2
#define ZUI_UI_TYPE_PRINT_LIST 0x4

#define ZUI_UI_DRAW_INTERACTIVE (ZUI_UIS_DISABLED | ZUI_UIS_NORMAL | ZUI_UIS_PRESS | ZUI_UIS_HOVER | ZUI_UIS_FOCUS)
#define ZUI_UI_DRAW_NONINTERACTIVE (ZUI_UIS_DISABLED | ZUI_UIS_NORMAL)

#define ZUI_ELEMENT_DATA_FLAG_NONE ZUI_FLAG_NONE
#define ZUI_ELEMENT_DATA_FLAG_OVERFLOW 0x1

#define ZUI_ELEMENT_DATA_TYPE_NONE ZUI_FLAG_NONE
#define ZUI_ELEMENT_DATA_TYPE_UINT 0x0
#define ZUI_ELEMENT_DATA_TYPE_INT 0x1
#define ZUI_ELEMENT_DATA_TYPE_BOOL 0x10

#define ZUI_ELEMENT_TRUNK_FLAG_NONE ZUI_FLAG_NONE
#define ZUI_ELEMENT_TRUNK_FLAG_VERTICAL 0x1
#define ZUI_ELEMENT_TRUNK_FLAG_FLIP 0x2
#define ZUI_ELEMENT_TRUNK_TYPE_NONE ZUI_FLAG_NONE

#define ZUI_ELEMENT_FLAG_BUTTON ZUI_ELEMENT_FLAG_INTERACTIVE
#define ZUI_ELEMENT_FLAG_BOX ZUI_ELEMENT_FLAG_INTERACTIVE
#define ZUI_ELEMENT_FLAG_LABEL ZUI_ELEMENT_FLAG_NONINTERACTIVE
#define ZUI_ELEMENT_FLAG_COUNTER ZUI_ELEMENT_FLAG_NONINTERACTIVE
#define ZUI_ELEMENT_FLAG_SWITCH ZUI_ELEMENT_FLAG_NONINTERACTIVE

#endif // ZUI__DEFINES_H_INCLUDED
