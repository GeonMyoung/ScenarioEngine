#ifndef LIST_CTRL_TDO_UNKNOWN
#define LIST_CTRL_TDO_UNKNOWN

#include "ListCtrlDz1.h"
#include <Dz1TdcInfoModule.h>

class CListCtrlTdoUnknown : public CListCtrlRefDz1
{
public:
	CListCtrlTdoUnknown();
	~CListCtrlTdoUnknown();

	BOOL InitControl();
	void CleanupData();

	BOOL Load(Dz1AATree *list);
	BOOL LoadToCtrl(ObjectInfo *p);

	ObjectInfo *GetMyItemData(int idx);
	ObjectInfo *Find(str_t name);
private:
	Dz1AATree *m_list;
};

#endif