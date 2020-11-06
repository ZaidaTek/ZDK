/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZUI__RUNTIME_H_INCLUDED
#define ZUI__RUNTIME_H_INCLUDED

#include "../../ZTK/ZTK__Runtime.h"
#include "../ZUI.h"

typedef struct {
	ZT_FLAG S;
	ZT_FLAG type;
	ZT_FLAG draw;
	ZT_INDEX border;
    ZT_FONT* font;
	const void** sources;
	ZUI_COLOR* colors;
	ZT_SPRITE** sprites;
} ZUI_HOST_ELEMENT_UI;

typedef struct {
	void* value;
	void* unit;
	void* minimum;
	void* maximum;
	ZT_FLAG flag;
	ZT_FLAG type;
} ZUI_HOST_ELEMENT_DATA;

typedef struct {
	struct pstruct_ZUI_HOST_ELEMENT** branch;
	ZT_INDEX number;
	ZT_FLAG flag;
	ZT_FLAG type;
} ZUI_HOST_ELEMENT_TRUNK;

typedef struct pstruct_ZUI_HOST_ELEMENT{
	ZT_ID id;
	ZT_FLAG flag;
	ZT_FLAG type;
	ZT_FLAG style;
	ZT_RECT rect;
	ZUI_HOST_ELEMENT_UI UI;
	struct pstruct_ZUI_HOST_ELEMENT* root;
	ZUI_HOST_ELEMENT_TRUNK* trunk;
	ZUI_HOST_ELEMENT_DATA* data;
} ZUI_HOST_ELEMENT;

typedef struct {
    struct {
        ZT_QLIST* buffer;
        const ZT_EVENT* last;
    } event;
    struct {
        ZT_LIST* registry;
        ZT_INDEX length;
        const ZUI_HOST_ELEMENT* focus;
    } element;
	ZT_FLAG flag;
	ZT_U32 seed;
	struct {
	    ZT_TIME now;
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
	} color;
} ZUI_HOST;

ZUI_HOST* gZUI_RTime;

ZT_BOOL ZUI_HostRegister(ZUI_HOST_ELEMENT* iElement);

ZUI_HOST_ELEMENT* ZUI_SwitchSize(ZUI_HOST_ELEMENT* iElement, const ZT_POINT* iSize);
ZUI_HOST_ELEMENT* ZUI_CounterSize(ZUI_HOST_ELEMENT* iElement, const ZT_POINT* iSize);

#include "ZUI__Element.h"
#include "ZUI__UI.h"

#endif // ZUI__RUNTIME_H_INCLUDED
