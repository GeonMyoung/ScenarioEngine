#ifndef LIST_CTRL_COLUMNS_LIST_H
#define LIST_CTRL_COLUMNS_LIST_H

#include "ListCtrlDz1.h"
#include <Dz1CodeGenDef.h>

class CListCtrlColumnList : public CListCtrlRefDz1
{
public:
	CListCtrlColumnList();
	~CListCtrlColumnList();

	BOOL InitControl();
	void CleanupData();

	BOOL Load(Dz1CodeGenListColumnList *list);
	BOOL LoadToCtrl(Dz1CodeGenListColumn *p);

	Dz1CodeGenListColumn *GetMyItemData(int idx);
	Dz1CodeGenListColumn *Find(u32_t order);
	BOOL Insert(Dz1CodeGenListColumn *column);
private:
	Dz1CodeGenListColumnList *m_list;
};

#endif