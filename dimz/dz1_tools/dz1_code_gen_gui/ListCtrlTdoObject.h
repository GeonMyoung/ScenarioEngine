#ifndef LIST_CTRL_TDO_OBJECT_H
#define LIST_CTRL_TDO_OBJECT_H

#include "ListCtrlDz1.h"
#include <Dz1TdcInfoModule.h>

class CListCtrlTdoObject : public CListCtrlRefDz1
{
public:
	CListCtrlTdoObject();
	~CListCtrlTdoObject();

	BOOL InitControl();
	void CleanupData();

	BOOL Load(Dz1Fifo *list);
	BOOL LoadToCtrl(ObjectInfo *p);

	ObjectInfo *GetMyItemData(int idx);
	ObjectInfo *Find(str_t name);
private:
	Dz1Fifo *m_list;
};

#endif