#include "stdafx.h"
#include "ListCtrlTdoUnknown.h"

CListCtrlTdoUnknown::CListCtrlTdoUnknown()
{
	m_list = NULL;
}

CListCtrlTdoUnknown::~CListCtrlTdoUnknown()
{
	CleanupData();
}

BOOL CListCtrlTdoUnknown::InitControl(void)
{
	CListCtrlStyledColumnDesign _design[] =
	{
		{ _T("Name"), LVCFMT_LEFT, CLIST_COLUMN_WITH(37, 8) },
		{ NULL }
	};

	int idx;

	m_list = NULL;

	this->SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);

	LV_COLUMN lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	CListCtrlStyledColumnDesign *i;
	for (idx = 0, i = _design; i->name != NULL; idx++, i++)
	{
		lvColumn.pszText = i->name;
		lvColumn.fmt = i->fmt;
		lvColumn.cx = i->cx;
		this->InsertColumn(idx, &lvColumn);
	}
	
	return TRUE;
}

void CListCtrlTdoUnknown::CleanupData(void)
{
	m_list = NULL;
}

static Dz1Error _LoadToCtrl(void *ptr, void *_p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	CListCtrlTdoUnknown *dlg = (CListCtrlTdoUnknown *)ptr;
	ObjectInfo *p = (ObjectInfo *)_p;

	if (dlg->LoadToCtrl(p) == FALSE) ERR_SET_OUT(errp, EFAULT);

	return err;
}

BOOL CListCtrlTdoUnknown::Load(Dz1AATree *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	m_list = list;

	this->DeleteAllItems();

	if ((*errp = Dz1AATree_travel(m_list, _LoadToCtrl, (void *)this)).code) ERR_DLG_OUT(errp);

	return errp->code == 0 ? TRUE : FALSE;
}

BOOL CListCtrlTdoUnknown::LoadToCtrl(ObjectInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	int nRow = this->GetItemCount();

	char temp[1024] = { 0, };
	CString str;
	LVITEM itemData;

	char *ptr = NULL;

	itemData.lParam		= 1;
	itemData.iIndent	= 0;
	itemData.state		= LVIS_SELECTED;
	itemData.stateMask	= LVIS_SELECTED;

	itemData.iSubItem	= 0;

	itemData.iItem		= nRow;

	// groupName
	itemData.iImage		= 0;
	itemData.pszText	= p->name;
	itemData.cchTextMax = (u32_t)strlen(p->name);
	itemData.mask		= LVIF_TEXT | LVIF_PARAM;
	nRow = this->InsertItem(&itemData);

	this->SetItemData(nRow, (DWORD)(DWORD_PTR)p);

	return TRUE;
}


ObjectInfo *CListCtrlTdoUnknown::GetMyItemData(int idx)
{
	ObjectInfo *ret = (ObjectInfo *)(DWORD_PTR)this->GetItemData(idx);
	return ret;
}

ObjectInfo *CListCtrlTdoUnknown::Find(str_t name)
{
	ObjectInfo key = { ObjectType_max, name };
	return (ObjectInfo *)Dz1AATree_find(m_list, (void *)&key);
}
