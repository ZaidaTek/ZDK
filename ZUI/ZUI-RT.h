/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI_RT_H_INCLUDED
#define ZUI_RT_H_INCLUDED

#include <ZTK-RT.h>
#include "ZUI.h"

typedef struct {
	ZT_FLAG S;
	ZT_FLAG type;
	ZT_FLAG draw;
	ZT_INDEX border;
    rZT_FONT* font;
	const void** sources;
	ZUI_COLOR* colors;
	ZT_SPRITE** sprites;
} rZUI_UI;

typedef struct {
	void* value;
	void* unit;
	void* minimum;
	void* maximum;
	ZT_FLAG flag;
	ZT_FLAG type;
} rZUI_DATA;

typedef struct {
	struct rZUI_ELEMENT** branch;
	ZT_INDEX number;
	ZT_FLAG flag;
	ZT_FLAG type;
} rZUI_TRUNK;

typedef struct rZUI_ELEMENT {
	ZT_ID id;
	ZT_FLAG flag;
	ZT_FLAG type;
	ZT_FLAG style;
	ZT_RECT rect;
	rZUI_UI UI;
	struct rZUI_ELEMENT* root;
	rZUI_TRUNK* trunk;
	rZUI_DATA* data;
} rZUI_ELEMENT;

typedef struct {
    struct {
        ZT_QLIST* buffer;
        const ZT_EVENT* last;
    } event;
    struct {
        ZT_LIST* registry;
        const rZUI_ELEMENT* focus;
        ZT_INDEX length;
        ZT_INDEX dummy; //alignment
    } element;
    struct {
        const ZT_RECT* rect;
        const ZT_POINT* pos;
        const ZT_POINT* size;
        const ZT_I* x;
        const ZT_I* y;
        const ZT_I* w;
        const ZT_I* h;
        const ZT_TIME* tick;
        const ZT_FLAG* paletteUser;
        const ZT_FLAG* paletteSys;
        const ZT_POINT* mousePos;
        const ZT_FLAG* mouseState;
        rZT_FONT** fontUser;
        rZT_FONT** fontSys;
    } system;
	ZT_FLAG flag;
	ZT_U32 seed;
	struct {
	    //ZT_TIME now;
	    ZT_TIME modulator;
	    ZT_TIME cursor;
	} timestamp;
	struct {
	    ZT_TIME modulator;
	    ZT_TIME cursor;
	} timeout;
	struct {
	    ZT_COLOR modulator0;
	    ZT_COLOR modulator1;
	    ZT_COLOR cursor;
	    ZT_COLOR dummy; // alignment
	} color;
} rZUI_HOST;

extern rZUI_HOST rZUI_RTime;

ZT_BOOL ZUI_HostRegister(rZUI_ELEMENT* iElement);

rZUI_ELEMENT* ZUI_SwitchSize(rZUI_ELEMENT* iElement, const ZT_POINT* iSize);
rZUI_ELEMENT* ZUI_CounterSize(rZUI_ELEMENT* iElement, const ZT_POINT* iSize);

#include "ZUI-RT-ELEMENT.h"
#include "ZUI-RT-UI.h"

#endif // ZUI_RT_H_INCLUDED
