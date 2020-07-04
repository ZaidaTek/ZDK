/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_LIST_C_INCLUDED
#define ZT_LIST_C_INCLUDED

#include "ZTM__Runtime.h"
#include ZTM__INCL__LIST

ZT_LIST* ZTM_ListPointersFree(ZT_LIST* iList) {
	if (iList != NULL) {
		if (iList->items != NULL) {
			ZTM8_Free(iList->items);
			iList->items = NULL;
		}
	}
	return iList;
}
ZT_LIST* ZTM_ListPointersCreate(ZT_LIST* iList) {
	if (iList != NULL) {
        ZTM_ListPointersFree(iList);
		if (iList->length) {
			iList->items = ZTM8_New(sizeof(void*) * iList->length);
		}
	}
	return iList;
}
ZT_LIST* ZTM_ListClear(ZT_LIST* iList) {
	if (iList != NULL) {
		if (iList->items != NULL) {
			for (ZT_INDEX i = 0; i < iList->length; i++) {(iList->items)[i] = NULL;}
		}
	}
	return iList;
}
ZT_LIST* ZTM_ListCopy(const ZT_LIST* iSource, ZT_LIST* oTarget) {
	if (iSource != NULL && oTarget != NULL) {
		if ((iSource->items != NULL) && (oTarget->items != NULL)) {
            ZT_INDEX lLengthCopy = ((oTarget->length < iSource->length) ? oTarget->length : iSource->length);
            for (ZT_INDEX i = 0; i < lLengthCopy; i++) {(oTarget->items)[i] = (iSource->items)[i];}
		}
	}
	return oTarget;
}
ZT_LIST* ZTM_ListCopySpecific(const ZT_LIST* iSource, ZT_LIST* oTarget, ZT_INDEX iOffsetSource, ZT_INDEX iOffsetTarget, ZT_INDEX iLength) {
	if (iSource != NULL && oTarget != NULL) {
		if ((iSource->items != NULL) && (oTarget->items != NULL)) {
            if (!((iOffsetSource + iLength) > iSource->length) && !((iOffsetTarget + iLength) > oTarget->length)){
                for (ZT_INDEX i = 0; i < iLength; i++) {(oTarget->items)[i + iOffsetTarget] = (iSource->items)[i + iOffsetSource];}
            }
		}
	}
	return oTarget;
}

void ZTM_ListFree(ZT_LIST* iList) {
	if (iList != NULL) {
		ZTM_ListPointersFree(iList);
		ZTM8_Free(iList);
	}
}
ZT_LIST* ZTM_ListNew(ZT_INDEX iLength) {
	ZT_LIST* lList = NULL;
    if ((lList = ZTM8_New(sizeof(ZT_LIST))) != NULL) {
        lList->items = NULL;
        if ((lList->length = iLength)) {
            ZTM_ListPointersCreate(lList);
        }
    }
	return lList;
}
ZT_LIST* ZTM_ListNewDuplicate(const ZT_LIST* iList) {
    ZT_LIST* lList = NULL;
    if (iList != NULL) {
        if ((lList = ZTM_ListNew(iList->length)) != NULL) {
            if (iList->items != NULL) {
                ZTM_ListPointersCreate(lList);
                ZTM_ListCopy(iList, lList);
            }
        }
    }
    return lList;
}
ZT_LIST* ZTM_ListLength(ZT_LIST* iList, ZT_INDEX iLength) {
	if (iList != NULL) {
        if (iList->length != iLength) {
			if (iLength) {
				iList->items = ZTM8_Resize(iList->items, iLength * sizeof(void*));
				for (ZT_INDEX i = iList->length; i < iLength; i++) {iList->items[i] = NULL;}
			} else {
				ZTM_ListPointersFree(iList);
			}
			iList->length = iLength;
        }
    }
	return iList;
}
ZT_LIST* ZTM_ListDrop(ZT_LIST* iList, ZT_INDEX iIndex) {
	if (iList != NULL) {
        if (iIndex < iList->length) {
            for (ZT_INDEX i = iIndex; (i + 1) < iList->length; i++) {(iList->items)[i] = (iList->items)[i + 1];}
            (iList->items)[iList->length - 1] = NULL;
        }
	}
	return iList;
}
ZT_LIST* ZTM_ListDeserialize(ZT_LIST* iList, const ZT_CHAR* iDelimiter, const ZT_CHAR* iString) {
    if (iList != NULL && iDelimiter != NULL && iString != NULL) {
        ZT_INDEX lLine = 0;
        ZT_INDEX lIndex = -1;
        ZT_FLAG lEscape = 0x0;
        while (iString[++lIndex] != ZTM_CHAR_NT) {
			ZTC8_Escape(lEscape, iString[lIndex]);
			if (ZTC8_Match(&iString[lIndex], iDelimiter) && (lLine < lIndex) && !lEscape) {
				ZTM_ListAppend(iList, ZTC8_CopyLength(&iString[lLine], lIndex - lLine));
				lLine = lIndex + ZTC8_GetLength(iDelimiter);
			}
        }
        if (lIndex > lLine) {
            ZTM_ListAppend(iList, ZTC8_CopyLength(&iString[lLine], lIndex - lLine));
            lLine = lIndex;
        }
    }
    return iList;
}
void* ZTM_ListFirstValidItem(ZT_LIST* iList) {
    if (iList != NULL) {if (iList->length) {for (ZT_INDEX i = 0; i < iList->length; i++) {if (iList->items[i] != NULL) {return iList->items[i];}}}}
    return NULL;
}
void* ZTM_ListLastValidItem(ZT_LIST* iList) {
    if (iList != NULL) {ZT_INDEX lLength; if ((lLength = iList->length)) {--lLength; for (ZT_INDEX i = 0; i < iList->length; i++) {if (iList->items[lLength - i] != NULL) {return iList->items[i];}}}}
    return NULL;
}
void* ZTM_ListItem(ZT_LIST* iList, ZT_INDEX iIndex) {
    if (iList != NULL) {
        if (iIndex < iList->length) {
            return iList->items[iIndex];
        }
    }
    return NULL;
}
ZT_LIST* ZTM_ListAppend(ZT_LIST* iList, void* iItem) {
	if (iList != NULL) {
		iList->items = ZTM8_Resize(iList->items, (++iList->length) * sizeof(void*));
        iList->items[iList->length - 1] = iItem;
	}
	return iList;
}
ZT_INDEX ZTM_ListCount(ZT_LIST* iList, void* iItem) {
    ZT_INDEX lCount = 0;
    if (iList != NULL) {
        ZT_INDEX lIndex = -1;
        while ((++lIndex) < iList->length) {if (iList->items[lIndex] == iItem) {lCount++;}}
    }
    return lCount;
}
ZT_BOOL ZTM_ListContains(ZT_LIST* iList, void* iItem) {
    if (iList != NULL) {
        ZT_INDEX lIndex = -1;
        while ((++lIndex) < iList->length) {if (iList->items[lIndex] == iItem) {return ZT_TRUE;}}
    }
	return ZT_FALSE;
}
ZT_BOOL ZTM_ListFindVacant(ZT_LIST* iList, ZT_BOOL iBackwards, ZT_INDEX* oIndex) {
    if (iList != NULL) {
        if (iList->length) {
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
        }
    }
    return ZT_FALSE;
}
ZT_BOOL ZTM_ListFind(ZT_LIST* iList, void* iItem, ZT_BOOL iBackwards, ZT_INDEX* oIndex) {
    if (iList != NULL) {
        if (iList->length) {
            ZT_INDEX lCount = -1;
            ZT_INDEX lIndex = 0;
            while ((++lCount) < iList->length) {
                lIndex = (iBackwards) ? (iList->length - (lCount + 1)) : lCount;
                if (iList->items[lIndex] == iItem) {
                    if (oIndex != NULL) {*oIndex = lIndex;}
                    return ZT_TRUE;
                }
            }
        }
    }
    return ZT_FALSE;
}
void ZTM_ListSort(ZT_LIST* iList, ZT_FLAG (*iComparator)(const void**, const void**)) {
	if (iList != NULL && iComparator != NULL) {
		qsort(iList->items, iList->length, sizeof(*(iList->items)), (int (*)(const void*, const void*))iComparator);
	}
}
// ZT_QLIST
// INTERNAL-ONLY FUNCTIONS
void ZTM_QListAdvanceData(ZT_QLIST* iQList) {if (iQList != NULL) {++iQList->data; iQList->data %= iQList->length;}}//{iQList->data = ((iQList->data + 1) < iQList->length) ? (iQList->data + 1) : 0;}}
void ZTM_QListAdvanceUser(ZT_QLIST* iQList) {if (iQList != NULL) {++iQList->user; iQList->user %= iQList->length;}}//{iQList->user = ((iQList->user + 1) < iQList->length) ? (iQList->user + 1) : 0;}}
void ZTM_QListRevertData(ZT_QLIST* iQList) {if (iQList != NULL) {if (iQList->data) {--iQList->data;} else {iQList->data = iQList->length ? (iQList->length - 1) : 0;}}}//{iQList->data = (iQList->data) ? (iQList->data - 1) : (iQList->length ? (iQList->length - 1) : iQList->length);}}
void ZTM_QListRevertUser(ZT_QLIST* iQList) {if (iQList != NULL) {if (iQList->user) {--iQList->user;} else {iQList->user = iQList->length ? (iQList->length - 1) : 0;}}}//{iQList->user = (iQList->user) ? (iQList->user - 1) : (iQList->length ? (iQList->length - 1) : iQList->length);}}
ZT_QLIST* ZTM_QListPointersFree(ZT_QLIST* iQList) {
    if (iQList != NULL) {
        if (iQList->items != NULL) {
            ZTM8_Free(iQList->items);
            iQList->items = NULL;
        }
    }
    return iQList;
}
ZT_QLIST* ZTM_QListPointersCreate(ZT_QLIST* iQList) {
    if (iQList != NULL) {
        ZTM_QListPointersFree(iQList);
		if (iQList->length) {
			iQList->items = ZTM8_New(sizeof(void*) * iQList->length);
		}
    }
    return iQList;
}
// PUBLIC FUNCTIONS
void ZTM_QListFree(ZT_QLIST* iQList) {
    if (iQList != NULL) {
        ZTM_QListPointersFree(iQList);
        ZTM8_Free(iQList);
    }
}
ZT_QLIST* ZTM_QListNew(ZT_INDEX iLength) {
    ZT_QLIST* lQList = NULL;
    if ((lQList = (ZTM8_New(sizeof(ZT_QLIST)))) != NULL) {
        lQList->items = NULL;
        lQList->data = 0;
        lQList->user = 0;
        if ((lQList->length = iLength)) {ZTM_QListPointersCreate(lQList);}
    }
    return lQList;
}
ZT_INDEX ZTM_QListQueueItem(ZT_QLIST* iQList, void* iItem) {
    if (iQList != NULL) {
        if (iQList->items != NULL) {
            iQList->items[iQList->data] = iItem;
            ZTM_QListAdvanceData(iQList);
			return iQList->data;
        }
    }
    return 0;
}
ZT_INDEX ZTM_QListPoll(ZT_QLIST* iQList, void** oItems) {
    ZT_INDEX lLength = 0;
    if ((lLength = ZTM_QListQueued(iQList))) {
        if (oItems != NULL) {*oItems = (iQList->items)[iQList->user];}
        ZTM_QListAdvanceUser(iQList);
    }
    return lLength;
}
ZT_INDEX ZTM_QListQueued(ZT_QLIST* iQList) {
    ZT_INDEX lQueue = 0;
    if (iQList != NULL) {lQueue = (iQList->data < iQList->user) ? ((iQList->length - iQList->user) + iQList->data) : (iQList->data - iQList->user);}
    return lQueue;
}
ZT_INDEX ZTM_QListFlush(ZT_QLIST* iQList) {
    ZT_INDEX lSkip = 0;
    if (iQList != NULL) {
        lSkip = ZTM_QListQueued(iQList);
        iQList->user = iQList->data;
    }
    return lSkip;
}
void* ZTM_QListAdvanceItem(ZT_QLIST* iQList) {
    void* lLast = NULL;
    if (iQList != NULL) {
        lLast = (void*)(iQList->items)[iQList->data];
        ZTM_QListAdvanceData(iQList);
    }
    return lLast;
}

#endif // ZT_LIST_C_INCLUDED
