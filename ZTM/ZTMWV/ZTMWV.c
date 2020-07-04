/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTMWV_C_INCLUDED
#define ZTMWV_C_INCLUDED

#include "ZTMWV.h"

ZT_WEAVE* rTarget = NULL;

ZT_WEAVE* ZWV_New(ZT_SIZE iLength) {
    if (iLength < ZWV__LENGTH_MAX) {
		ZT_WEAVE* lWeave = (ZT_WEAVE*)ZTM8_New(sizeof(ZT_WEAVE));
		if (lWeave != NULL) {
			lWeave->extend = ZWV__DEFAULT_EXTEND;
			lWeave->data.payload = NULL;
			lWeave->data.length = 0;
			ZT_SIZE lLength = ZTM_CoerceIfNotZeroAndLess(iLength, ZWV__LENGTH_MIN);
			if (ZWV_Length(lWeave, lLength) ? lLength : !lLength) {
				if (lWeave->capacity) {((ZT_U8*)lWeave->data.payload)[0] = ZTM_CHAR_NT;}
				return lWeave;
			}
            ZWV_Free(lWeave);
		}
    }
    return NULL;
}
void ZWV_ShrinkCoercion(ZT_WEAVE* iWeave) {
    if (iWeave != NULL) {
		if (!(iWeave->data.length < iWeave->capacity)) {
			((ZT_U8*)iWeave->data.payload)[(iWeave->data.length = iWeave->capacity)] = ZTM_CHAR_NT;
		}
	}
}
ZT_SIZE ZWV_Length(ZT_WEAVE* iWeave, ZT_SIZE iLength) {
    if (iWeave != NULL) {
		if ((iWeave->capacity = iLength)) {
			iWeave->data.payload = ZTM8_Resize(iWeave->data.payload, iWeave->capacity + 1);
			ZWV_ShrinkCoercion(iWeave);
		} else {
			ZTM_FreeNull(iWeave->data.payload);
		}
		return iWeave->capacity;
    }
	return 0;
}
ZT_SIZE ZWV_Fit(ZT_WEAVE* iWeave, ZT_SIZE iLength) {
    if (iWeave != NULL) {
        ZT_SIZE lBytesRemain = iWeave->capacity - iWeave->data.length;
        if (lBytesRemain < iLength) {ZWV_Length(iWeave, iWeave->capacity + (iLength - lBytesRemain));}
		return iWeave->capacity;
    }
	return 0;
}
void ZWV_Free(ZT_WEAVE* iWeave) {if (iWeave != NULL) {if (iWeave == rTarget) {rTarget = NULL;} ZTM8_Free(iWeave->data.payload); ZTM8_Free(iWeave);}}
ZT_WEAVE* ZWV_Get(void) {return rTarget;}
ZT_WEAVE* ZWV_Set(ZT_WEAVE* iWeave) {if (iWeave != NULL) {if (iWeave->data.payload != NULL) {return (rTarget = iWeave);}} return NULL;}
#define ZWV_EMPTY(TARGET) if ((TARGET) != NULL) {((ZT_U8*)(TARGET)->data.payload)[((TARGET)->data.length = 0)] = ZTM_CHAR_NT;}
void ZWV_Empty(void) {ZWV_EMPTY(rTarget);}
#define ZWV_ADD(TARGET,CONDITION) \
    if (((TARGET) != NULL) && (iData != NULL)) {\
        ZT_CHAR* lData = ((TARGET)->data.payload);\
        const ZT_CHAR* lAppend = iData;\
        ZT_SIZE lRead = -1;\
        ((TARGET)->data.length)--;\
        while ((++((TARGET)->data.length) < ((TARGET)->capacity)) ? (CONDITION) : 0x0) {lData[((TARGET)->data.length)] = lAppend[lRead];}\
        lData[((TARGET)->data.length)] = ZTM_CHAR_NT;\
    }
void ZWV_Add(const void* iData) {ZWV_ADD(rTarget, (lAppend[++lRead] != ZTM_CHAR_NT));}
void ZWV_AddVerbatim(const void* iData, ZT_SIZE iLength) {ZWV_ADD(rTarget, (++lRead < iLength));}
#define ZWV_ADDNUMBER(NUMBER,FORMAT) ZT_U8* lNumber = FORMAT(NUMBER); ZWV_Add(lNumber); ZTM8_Free(lNumber)
void ZWV_AddDiscard(void* iData) {ZWV_Add(iData); ZTM8_Free(iData);}
void ZWV_AddVerbatimDiscard(void* iData, ZT_SIZE iLength) {ZWV_AddVerbatim(iData, iLength); ZTM8_Free(iData);}
void ZWV_AddInteger(ZT_I iInteger) {ZWV_ADDNUMBER(iInteger, ZTC8_Integer);}
void ZWV_AddUnsigned(ZT_U iInteger) {ZWV_ADDNUMBER(iInteger, ZTC8_Unsigned);}
void ZWV_AddHex(ZT_U iInteger) {ZWV_ADDNUMBER(iInteger, ZTC8_Hex);}
void ZWV_AddBin(ZT_U iInteger) {ZWV_ADDNUMBER(iInteger, ZTC8_Binary);}

void ZWVX_Empty(ZT_WEAVE* iTarget) {ZWV_EMPTY(iTarget);}
void ZWVX_Add(ZT_WEAVE* iTarget, const void* iData) {ZWV_ADD(iTarget, (lAppend[++lRead] != ZTM_CHAR_NT));}
void ZWVX_AddVerbatim(ZT_WEAVE* iTarget, const void* iData, ZT_SIZE iLength) {ZWV_ADD(iTarget, (++lRead < iLength));}
#define ZWVX_ADDNUMBER(TARGET,NUMBER,FORMAT) ZT_U8* lNumber = FORMAT(NUMBER); ZWVX_Add((TARGET),lNumber); ZTM8_Free(lNumber)
void ZWVX_AddDiscard(ZT_WEAVE* iTarget, void* iData) {ZWVX_Add(iTarget, iData); ZTM8_Free(iData);}
void ZWVX_AddVerbatimDiscard(ZT_WEAVE* iTarget, void* iData, ZT_SIZE iLength) {ZWVX_AddVerbatim(iTarget, iData, iLength); ZTM8_Free(iData);}
void ZWVX_AddInteger(ZT_WEAVE* iTarget, ZT_I iInteger) {ZWVX_ADDNUMBER(iTarget, iInteger, ZTC8_Integer);}
void ZWVX_AddUnsigned(ZT_WEAVE* iTarget, ZT_U iInteger) {ZWVX_ADDNUMBER(iTarget, iInteger, ZTC8_Unsigned);}
void ZWVX_AddHex(ZT_WEAVE* iTarget, ZT_U iInteger) {ZWVX_ADDNUMBER(iTarget, iInteger, ZTC8_Hex);}
void ZWVX_AddBin(ZT_WEAVE* iTarget, ZT_U iInteger) {ZWVX_ADDNUMBER(iTarget, iInteger, ZTC8_Binary);}

#endif // ZTMWV_C_INCLUDED
