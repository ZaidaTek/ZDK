/*** Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZDX_TYPES_H_INCLUDED
#define ZDX_TYPES_H_INCLUDED

typedef struct {
	ZT_FLAG flag;
	ZT_FLAG type;
	struct {
		const ZT_UPOINT* major;
		const ZT_UPOINT* minor;
	} grid;
    struct {
        const ZT_UPOINT* trigger;
        const ZT_UPOINT* offset;
        struct {
            const ZT_UPOINT* horizontal;
            const ZT_UPOINT* vertical;
        } cursor;
    } data;
	struct {
		struct {
			const ZT_COLOR* major;
			const ZT_COLOR* minor;
		} grid;
	    struct {
            const ZT_COLOR* data;
	        const ZT_COLOR* first;
	        const ZT_COLOR* second;
	    } cursor;
		const ZT_COLOR* background;
		const ZT_COLOR* trigger;
		const ZT_COLOR* plot;
	} color;
} ZDX_DIAGRAM;

typedef struct {
	ZT_UPOINT block;
    ZT_INDEX cursor;
    ZT_INDEX resolution;
	ZT_U* data;
} ZDX_DATA;

typedef struct {
    ZT_UPOINT level;
    ZT_INDEX cursor;
    ZT_FLAG type;
} ZDX_TRIGGER;

typedef struct {
	struct {
        void* runtime;
        void* dummy;//alignment
        struct {
            void* in;
            void* out;
            ZT_FLAG cache;
            ZT_FLAG dummy;//alignment
        } buffer;
        ZT_FLAG flag;//alignment
        ZT_FLAG type;
    } interface;
	struct {
        ZT_FLAG flag;//alignment
        ZT_FLAG type;
        ZT_FLAG speed;
        ZT_FLAG config;
        ZT_INDEX number;
        ZT_INDEX resolution;
        struct {
            ZT_INDEX sample;
            ZT_INDEX line;
            struct {
                ZT_INDEX header;
                ZT_INDEX payload;
                ZT_INDEX sanity;
                ZT_INDEX unknown;
            } error;
            ZT_INDEX total;
            ZT_INDEX dummy; //alignment
        } counter;
    } task;
	ZT_FLAG flag;
	ZT_FLAG type;
	ZT_CHAR* address;
} ZDX_DEVICE;

#endif // ZDX_TYPES_H_INCLUDED
