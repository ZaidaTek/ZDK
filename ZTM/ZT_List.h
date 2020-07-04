/*** Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl
**** This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License
**** For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
***/
#ifndef ZT_LIST_H_INCLUDED
#define ZT_LIST_H_INCLUDED

#include "ZTM.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZTM_ListFree(ZT_LIST* iList);
ZT_LIST* ZTM_ListNew(ZT_INDEX iLength);
ZT_LIST* ZTM_ListNewEmpty(void);
ZT_LIST* ZTM_ListNewDuplicate(const ZT_LIST* iList);
ZT_LIST* ZTM_ListLength(ZT_LIST* iList, ZT_INDEX iLength);
#define ZTM_ListNull(LIST) ZTM_ListClear(LIST)
ZT_LIST* ZTM_ListClear(ZT_LIST* iList);
ZT_LIST* ZTM_ListCopy(const ZT_LIST* iSource, ZT_LIST* oTarget);
ZT_LIST* ZTM_ListCopySpecific(const ZT_LIST* iSource, ZT_LIST* oTarget, ZT_INDEX iOffsetSource, ZT_INDEX iOffsetTarget, ZT_INDEX iLength);
ZT_LIST* ZTM_ListDrop(ZT_LIST* iList, ZT_INDEX iIndex);
ZT_LIST* ZTM_ListAppend(ZT_LIST* iList, void* iItem);
ZT_LIST* ZTM_ListInsert(ZT_LIST* iList, ZT_INDEX iIndex, void* iItem);

ZT_LIST* ZTM_ListDeserialize(ZT_LIST* iList, const ZT_CHAR* iDelimiter, const ZT_CHAR* iString);
void* ZTM_ListFirstValidItem(ZT_LIST* iList);
void* ZTM_ListLastValidItem(ZT_LIST* iList);
void* ZTM_ListItem(ZT_LIST* iList, ZT_INDEX iIndex);

ZT_INDEX ZTM_ListCount(ZT_LIST* iList, void* iItem);
ZT_BOOL ZTM_ListContains(ZT_LIST* iList, void* iItem);
ZT_BOOL ZTM_ListFindVacant(ZT_LIST* iList, ZT_BOOL iBackwards, ZT_INDEX* oIndex);
ZT_BOOL ZTM_ListFind(ZT_LIST* iList, void* iItem, ZT_BOOL iBackwards, ZT_INDEX* oIndex);

void ZTM_ListSort(ZT_LIST* iList, ZT_FLAG (*iComparator)(const void**, const void**));

void ZTM_QListFree(ZT_QLIST* iQList);
ZT_QLIST* ZTM_QListNew(ZT_INDEX iLength);
ZT_INDEX ZTM_QListQueued(ZT_QLIST* iQList);
void ZTM_QListAdvanceData(ZT_QLIST* iQList);
void ZTM_QListAdvanceUser(ZT_QLIST* iQList);
void ZTM_QListRevertData(ZT_QLIST* iQList);
void ZTM_QListRevertUser(ZT_QLIST* iQList);
void* ZTM_QListAdvanceItem(ZT_QLIST* iQList);
ZT_INDEX ZTM_QListQueueItem(ZT_QLIST* iQList, void* IItem);
ZT_INDEX ZTM_QListPoll(ZT_QLIST* iQList, void** oItems);
ZT_INDEX ZTM_QListFlush(ZT_QLIST* iQList);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZT_LIST_H_INCLUDED
