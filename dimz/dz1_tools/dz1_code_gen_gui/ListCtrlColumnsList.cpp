#include "stdafx.h"
#include "ListCtrlColumnsList.h"

CListCtrlColumnList::CListCtrlColumnList()
{
	m_list = NULL;
}

CListCtrlColumnList::~CListCtrlColumnList()
{
	CleanupData();
}

BOOL CListCtrlColumnList::InitControl(void)
{
	CListCtrlStyledColumnDesign _design[] =
	{
		{ _T("Order"), LVCFMT_LEFT, CLIST_COLUMN_WITH(5, 8) },
		{ _T("Name"), LVCFMT_CENTER, CLIST_COLUMN_WITH(15, 8) },
		{ _T("Type"), LVCFMT_CENTER, CLIST_COLUMN_WITH(15, 8) },
		{ _T("Variable"), LVCFMT_CENTER, CLIST_COLUMN_WITH(35, 8) },
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
		lvColumn.iSubItem = idx;
		this->InsertColumn(idx, &lvColumn);
	}
	
	return TRUE;
}

void CListCtrlColumnList::CleanupData(void)
{
	m_list = NULL;
}

static Dz1Error _LoadToCtrl(void *ptr, Dz1CodeGenListColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	CListCtrlColumnList *dlg = (CListCtrlColumnList *)ptr;

	if (dlg->LoadToCtrl(p) == FALSE) ERR_SET_OUT(errp, EFAULT);

	return err;
}

BOOL CListCtrlColumnList::Load(Dz1CodeGenListColumnList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	m_list = list;

	this->DeleteAllItems();

	if ((*errp = m_list->travel(m_list, _LoadToCtrl, (void *)this)).code) ERR_DLG_OUT(errp);

	return errp->code == 0 ? TRUE : FALSE;
}

BOOL CListCtrlColumnList::LoadToCtrl(Dz1CodeGenListColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	int nRow = this->GetItemCount(), nSub = 0;

	char temp[1024] = { 0, };
	CString str;
	LVITEM itemData;

	char *ptr = NULL;

	itemData.lParam		= 1;
	itemData.iIndent	= 0;
	itemData.state		= LVIS_SELECTED;
	itemData.stateMask	= LVIS_SELECTED;

	itemData.iImage		= 0;

	itemData.iItem		= nRow;

	// order
	sprintf(temp, "%03u", p->order);

	itemData.iSubItem	= nSub++;
	itemData.pszText	= temp;
	itemData.cchTextMax = (u32_t)strlen(temp);
	itemData.mask		= LVIF_TEXT | LVIF_PARAM;
	nRow = this->InsertItem(&itemData);

	// Name
	itemData.iSubItem	= nSub++;
	itemData.pszText	= p->name;
	itemData.cchTextMax = (u32_t)strlen(p->name);
	itemData.mask		= LVIF_TEXT;
	this->SetItem(&itemData);

	// Type
	itemData.iSubItem	= nSub++;
	itemData.pszText	= p->type->name;
	itemData.cchTextMax = (u32_t)strlen(p->type->name);
	itemData.mask		= LVIF_TEXT;
	this->SetItem(&itemData);

	// Instance
	itemData.iSubItem	= nSub++;
	itemData.pszText	= p->instance;
	itemData.cchTextMax = (u32_t)strlen(p->instance);
	itemData.mask		= LVIF_TEXT;
	this->SetItem(&itemData);

	this->SetItemData(nRow, (DWORD)(DWORD_PTR)p);

	return TRUE;
}


Dz1CodeGenListColumn *CListCtrlColumnList::GetMyItemData(int idx)
{
	Dz1CodeGenListColumn *ret = (Dz1CodeGenListColumn *)(DWORD_PTR)this->GetItemData(idx);
	return ret;
}

Dz1CodeGenListColumn *CListCtrlColumnList::Find(u32_t order)
{
	Dz1CodeGenListColumn key = { order };
	return m_list->find(m_list, &key);
}

BOOL CListCtrlColumnList::Insert(Dz1CodeGenListColumn *column)
{
	BOOL ret = FALSE;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (m_list == NULL) ERR_DLG_SET_OUT(errp, ENOSYS);
	else
	{
		if ((*errp = m_list->add(m_list, column)).code) ERR_DLG_OUT(errp);
		else
		{
			LoadToCtrl(column);
			ret = TRUE;
		}
	}
	return ret;
}
