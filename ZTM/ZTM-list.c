/*** Copyright (C) 2019-2025 ZaidaTek, Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZTM_LIST_C_INCLUDED
#define ZTM_LIST_C_INCLUDED

#include "ZTM-RT.h"
#include ZTM__INCL__LIST

ZT_LIST* ZTM_ListPointersFree(ZT_LIST* iList) {
	ZTM8_Free(iList->items);
	return iList;
}
ZT_LIST* ZTM_ListPointersCreate(ZT_LIST* iList) {
	iList->items = ZTM8_New(sizeof(void*) * iList->length);
	return iList;
}
ZT_LIST* ZTM_ListClear(ZT_LIST* iList) {
	for (ZT_INDEX i = 0; i < iList->length; i++) {iList->items[i] = NULL;}
	return iList;
}
ZT_LIST* ZTM_ListCopy(const ZT_LIST* iSource, ZT_LIST* oTarget) {
	for (ZT_INDEX i = 0; i < iSource->length; i++) {oTarget->items[i] = iSource->items[i];}
	return oTarget;
}
ZT_LIST* ZTM_ListCopySpecific(const ZT_LIST* iSource, ZT_LIST* oTarget, ZT_INDEX iOffsetSource, ZT_INDEX iOffsetTarget, ZT_INDEX iLength) {
	for (ZT_INDEX i = 0; i < iLength; i++) {oTarget->items[iOffsetTarget + i] = iSource->items[iOffsetSource + i];}
	return oTarget;
}

void ZTM_ListFree(ZT_LIST* iList) {
	ZTM8_Free(ZTM_ListPointersFree(iList));
}
ZT_LIST* ZTM_ListNew(ZT_INDEX iLength) {
	ZT_LIST* lList = ZTM8_New(sizeof(ZT_LIST));
	lList->length = iLength;
	return ZTM_ListPointersCreate(lList);
}
ZT_LIST* ZTM_ListNewDuplicate(const ZT_LIST* iList) {
	return ZTM_ListCopy(iList, ZTM_ListNew(iList->length));
}
ZT_LIST* ZTM_ListLength(ZT_LIST* iList, ZT_INDEX iLength) {
	iList->items = ZTM8_Resize(iList->items, (iList->length = iLength) * sizeof(void*));
	return iList;
}
ZT_LIST* ZTM_ListDrop(ZT_LIST* iList, ZT_INDEX iIndex) {
	for (ZT_INDEX i = iIndex + 1; i < iList->length; i++) {iList->items[i - 1] = iList->items[i];}
	///iList->items[iList->length - 1] = NULL; //previously
	iList->items = ZTM8_Resize(iList->items, (--iList->length) * sizeof(void*));
	return iList;
}
ZT_LIST* ZTM_ListAppend(ZT_LIST* iList, void* iItem) {
	iList->items = ZTM8_Resize(iList->items, (++iList->length) * sizeof(void*));
	iList->items[iList->length - 1] = iItem;
	return iList;
}
ZT_LIST* ZTM_ListDeserialize(ZT_LIST* iList, const ZT_CHAR* iDelimiter, const ZT_CHAR* iString) {
	ZT_INDEX lLine = 0;
	ZT_INDEX lIndex = -1;
	ZT_FLAG lEscape = 0x0;
	while (iString[++lIndex] != ZTM_CHAR_NT) {
		ZTC8_Escape(lEscape, iString[lIndex]);
		if (!lEscape && (lLine < lIndex) && ZTC8_Match(&iString[lIndex], iDelimiter)) {
			ZTM_ListAppend(iList, ZTC8_CopyLength(&iString[lLine], lIndex - lLine));
			lLine = lIndex + ZTC8_GetLength(iDelimiter);
		}
	}
	if (lIndex > lLine) {
		ZTM_ListAppend(iList, ZTC8_CopyLength(&iString[lLine], lIndex - lLine));
		lLine = lIndex;
	}
	return iList;
}
void* ZTM_ListFirstValidItem(ZT_LIST* iList) {
	if (iList->length) {for (ZT_INDEX i = 0; i < iList->length; i++) {if (iList->items[i] != NULL) {return iList->items[i];}}}
	return NULL;
}
void* ZTM_ListLastValidItem(ZT_LIST* iList) {
	ZT_INDEX lLength; if ((lLength = iList->length)) {--lLength; for (ZT_INDEX i = 0; i < iList->length; i++) {if (iList->items[lLength - i] != NULL) {return iList->items[i];}}}
	return NULL;
}
void* ZTM_ListItem(ZT_LIST* iList, ZT_INDEX iIndex) {
	return iList->items[iIndex];
}
ZT_INDEX ZTM_ListCount(ZT_LIST* iList, void* iItem) {
	ZT_INDEX lCount = 0;
	ZT_INDEX lIndex = -1;
	while (++lIndex < iList->length) {if (iList->items[lIndex] == iItem) {++lCount;}}
	return lCount;
}
ZT_BOOL ZTM_ListContains(ZT_LIST* iList, void* iItem) {
	ZT_INDEX lIndex = -1;
	while (++lIndex < iList->length) {if (iList->items[lIndex] == iItem) {return ZT_TRUE;}}
	return ZT_FALSE;
}
ZT_BOOL ZTM_ListFindVacant(ZT_LIST* iList, ZT_BOOL iBackwards, ZT_INDEX* oIndex) {
	ZT_INDEX lCount = -1;
	ZT_INDEX lIndex = 0;
	while ((++lCount) < iList->length) {
		if (iList->items[(lIndex = (iBackwards) ? (iList->length - (lCount + 1)) : lCount)] == NULL) {
			if ((iBackwards) && lIndex) {  // if backwards, returns left aligned NULL
				if (iList->items[(lIndex - 1)] != NULL) {
					if (oIndex != NULL) {*oIndex = lIndex;}
					return ZT_TRUE;
				}
			} else {
				if (oIndex != NULL) {*oIndex = lIndex;}
				return ZT_TRUE;
			}
		}
	}
	return ZT_FALSE;
}
ZT_BOOL ZTM_ListFind(ZT_LIST* iList, void* iItem, ZT_BOOL iBackwards, ZT_INDEX* oIndex) {
	ZT_INDEX lCount = -1;
	ZT_INDEX lIndex = 0;
	while ((++lCount) < iList->length) {
		lIndex = (iBackwards) ? (iList->length - (lCount + 1)) : lCount;
		if (iList->items[lIndex] == iItem) {
			if (oIndex != NULL) {*oIndex = lIndex;}
			return ZT_TRUE;
		}
	}
	return ZT_FALSE;
}
void ZTM_ListSort(ZT_LIST* iList, ZT_FLAG (*iComparator)(const void**, const void**)) {
	qsort(iList->items, iList->length, sizeof(*(iList->items)), (int (*)(const void*, const void*))iComparator);
}
// ZT_QLIST
// INTERNAL-ONLY FUNCTIONS
void ZTM_QListAdvanceData(ZT_QLIST* iQList) {++iQList->data; iQList->data %= iQList->length;}
void ZTM_QListAdvanceUser(ZT_QLIST* iQList) {++iQList->user; iQList->user %= iQList->length;} // TODO revert checks for zero length
void ZTM_QListRevertData(ZT_QLIST* iQList) {if (iQList->data) {--iQList->data;} else {iQList->data = iQList->length ? (iQList->length - 1) : 0;}}
void ZTM_QListRevertUser(ZT_QLIST* iQList) {if (iQList->user) {--iQList->user;} else {iQList->user = iQList->length ? (iQList->length - 1) : 0;}}
// PUBLIC FUNCTIONS
void ZTM_QListFree(ZT_QLIST* iQList) {
	ZTM8_Free(iQList);
}
ZT_QLIST* ZTM_QListNew(ZT_INDEX iLength) {
	ZT_SIZE lSize = (sizeof(ZT_QLIST) % 8) ? (sizeof(ZT_QLIST) + (8 - (sizeof(ZT_QLIST) % 8))) : sizeof(ZT_QLIST);
	ZT_QLIST* lQList = ZTM8_New(lSize + sizeof(void*) * iLength);
	lQList->items = (void*)lQList + lSize;
	lQList->length = iLength;
	lQList->user = (lQList->data = 0);
	return lQList;
}
ZT_INDEX ZTM_QListQueueItem(ZT_QLIST* iQList, void* iItem) {
	iQList->items[iQList->data] = iItem;
	ZTM_QListAdvanceData(iQList);
	return iQList->data;
}
ZT_INDEX ZTM_QListPoll(ZT_QLIST* iQList, void** oItems) {
	ZT_INDEX lLength;
	if ((lLength = ZTM_QListQueued(iQList))) {
		if (oItems != NULL) {*oItems = (iQList->items)[iQList->user];}
		ZTM_QListAdvanceUser(iQList);
	}
	return lLength;
}
ZT_INDEX ZTM_QListQueued(ZT_QLIST* iQList) {
	return (iQList->data < iQList->user) ? ((iQList->length - iQList->user) + iQList->data) : (iQList->data - iQList->user);
}
ZT_INDEX ZTM_QListFlush(ZT_QLIST* iQList) {
	ZT_INDEX lSkip = ZTM_QListQueued(iQList);
	iQList->user = iQList->data;
	return lSkip;
}
void* ZTM_QListAdvanceItem(ZT_QLIST* iQList) {
	void* lLast = iQList->items[iQList->data];
	ZTM_QListAdvanceData(iQList);
	return lLast;
}

#endif // ZTM_LIST_C_INCLUDED
