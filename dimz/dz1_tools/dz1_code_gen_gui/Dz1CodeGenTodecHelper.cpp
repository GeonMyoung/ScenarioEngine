#include "stdafx.h"
#include "Dz1CodeGenTodecHelper.h"

////////////////////////////////////////////////////////////////////////////////
// CListCtrlConstructObject
BOOL CListCtrlConstructObject::OnInitControl()
{
	CListCtrlStyledColumnDesign _design[] =
	{
		{ _T("Name"), LVCFMT_LEFT, CLIST_COLUMN_WITH(37, 8) },
		{ _T("Type"), LVCFMT_CENTER, CLIST_COLUMN_WITH(12, 8) },
		{ NULL, 0, 0 }
	};
	u32_t cnt = sizeof(_design) / sizeof(CListCtrlStyledColumnDesign);
	return CDz1ListCtrlRO::OnInitControl(_design, cnt);
}

void CListCtrlConstructObject::GetFirstColumn(CString &str, ConstructObjectEntry *node)
{
	if (node == NULL) str = _T("(null)");
	else str = node->obj_name;
}

void CListCtrlConstructObject::RefreshRow(int nRow)
{
	ConstructObjectEntry *node = GetElement(nRow);
	if (node != NULL) SetItemTexts(nRow, node);
}

BOOL CListCtrlConstructObject::SetItemTexts(int nRow, ConstructObjectEntry *node)
{
	int nSub = 0;
	CString str;

	// name
	GetFirstColumn(str, node);
	SetItemText(nRow, nSub++, str);

	// type
	ObjectInfo *obj = node->obj;
	if (obj == NULL) str = _T("#Unresolved");
	else str = ObjectTypeStr(obj->type);

	SetItemText(nRow, nSub++, str);

	// Row Color
	if (node->codecs->count(node->codecs) > 0)
	{
		SetRowTxtColor(nRow, RGB(0, 0, 255), FALSE);
		SetRowStyle(nRow, LIS_TXTCOLOR, FALSE);
		SetRowSelectedTxtColor(nRow, RGB(0, 255, 255), FALSE);
		SetRowSelectedStyle(nRow, LIS_TXTCOLOR);
	}
	else
	{
		SetRowStyle(nRow, LIS_NO_ROW_STYLE, FALSE);
		SetRowSelectedStyle(nRow, LIS_NO_ROW_STYLE, TRUE);
	}
	return TRUE;
}
// CListCtrlConstructObject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CListCtrlConstructMemberCodec
BOOL CListCtrlConstructCodec::OnInitControl()
{
	CListCtrlStyledColumnDesign _design[] =
	{
		{ _T("Name"), LVCFMT_LEFT, CLIST_COLUMN_WITH(37, 8) },
		{ _T("API"), LVCFMT_CENTER, CLIST_COLUMN_WITH(12, 8) },
		{ NULL, 0, 0 }
	};
	u32_t cnt = sizeof(_design) / sizeof(CListCtrlStyledColumnDesign);
	return CDz1ListCtrlRW::OnInitControl(_design, cnt);
}

void CListCtrlConstructCodec::GetFirstColumn(CString &str, ConstructCodecEntry *node)
{
	ObjectInfo *obj = NULL;
	if (node == NULL) str = _T("(null)");
	else if ((obj = node->parent_obj) == NULL)
	{
		if (node->opt_suffix == NULL) str.Format(_T("#unresolved_RW"));
		else str.Format(_T("#unresolved%s_RW"), node->opt_suffix);
	}
	else
	{
		if (node->opt_suffix == NULL) str.Format(_T("%s_RW"), obj->name);
		else str.Format(_T("%s%s_RW"), obj->name, node->opt_suffix);
	}
}

BOOL CListCtrlConstructCodec::SetItemTexts(int nRow, ConstructCodecEntry *node)
{
	//Dz1Error err = DZ1_ERROR_INITIALIZER;
	//Dz1Str ptr = NULL;
	int nSub = 0;
	CString str;

	// Name
	GetFirstColumn(str, node);
	SetItemText(nRow, nSub++, str);

	// type
	str = ConstructCodecModeStr(node->mode);
	SetItemText(nRow, nSub++, str);

	return TRUE;
}
// CListCtrlConstructCodec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CListCtrlConstructMemberCodec
BOOL CListCtrlConstructMemberCodec::OnInitControl()
{
	CListCtrlStyledColumnDesign _design[] =
	{
		{ _T("Order"), LVCFMT_RIGHT, CLIST_COLUMN_WITH(5, 8) },
		{ _T("Instance"), LVCFMT_LEFT, CLIST_COLUMN_WITH(22, 8) },
		{ _T("Type"), LVCFMT_LEFT, CLIST_COLUMN_WITH(37, 8) },
		{ _T("CODEC"), LVCFMT_CENTER, CLIST_COLUMN_WITH(15, 8) },
		{ NULL, 0, 0 }
	};
	u32_t cnt = sizeof(_design) / sizeof(CListCtrlStyledColumnDesign);
	return CDz1ListCtrlRW::OnInitControl(_design, cnt);
}

ConstructMemberCodecEntry *CListCtrlConstructMemberCodec::FindName(Dz1Str name)
{
	ConstructMemberCodecEntry *node = NULL;
	int i, cnt = GetItemCount();
	for (i = 0; i < cnt; i++)
	{
		if ((node = GetElement(i, NULL)) != NULL)
		{
			if (Dz1STRCMP(node->instance_name, name) == 0) return node;
		}
	}
	return NULL;
}

void CListCtrlConstructMemberCodec::GetFirstColumn(CString &str, ConstructMemberCodecEntry *node)
{
	if (node == NULL) str = _T("(null)");
	else str.Format(_T("%u"), node->order);
}

static void GetStructureMemberTypeStr(CString &dst, ObjectInfo *struct_obj, str_t instance_name)
{
	StructureInfo *info = (StructureInfo *)struct_obj->info;
	StructMemberList *list = info->members;
	StructMemberEntry *node = list->find(list, instance_name);
	if (node == NULL) dst = _T("#unknown");
	else
	{
		ObjectInfo *obj = node->type;
		dst.Format(_T("%s%s"), obj->name, node->isPointer ? _T(" *") : _T(""));
	}
}

static void GetUnionMemberTypeStr(CString &dst, ObjectInfo *struct_obj, str_t instance_name)
{
	UnionInfo *info = (UnionInfo *)struct_obj->info;
	UnionMemberList *list = info->members;
	UnionMemberEntry *node = list->find(list, instance_name);
	if (node == NULL) dst = _T("#unknown");
	else
	{
		ObjectInfo *obj = node->type;
		dst.Format(_T("%s%s"), obj->name, node->isPointer ? _T(" *") : _T(""));
	}
}

BOOL CListCtrlConstructMemberCodec::SetItemTexts(int nRow, ConstructMemberCodecEntry *node)
{
	//Dz1Error err = DZ1_ERROR_INITIALIZER;
	//Dz1Str ptr = NULL;
	int nSub = 0;
	CString str;

	// order
	GetFirstColumn(str, node);
	SetItemText(nRow, nSub++, str);

	// instance
	if (node->instance_name == NULL) str = _T("#invalid");
	else str = node->instance_name;
	SetItemText(nRow, nSub++, str);

	// Object Type
	if (node->instance_name[0] == Dz1Text('@'))
	{
		if (strcmp(node->instance_name, INSTANCE_NAME_PRESENT) == 0)
		{
			ConstructCodecEntry *parent = node->parent;
			ObjectInfo *pObj = parent->parent_obj;
			if (ObjectInfo_typeOf(pObj) == ObjectType_union)
				str.Format(_T("%sPresent"), pObj->name);
			else  str = Dz1Text("#invalid");
		}
		else if (strcmp(node->instance_name, INSTANCE_NAME_COUNT) == 0)
		{
			ConstructCodecEntry *parent = node->parent;
			ObjectInfo *pObj = parent->parent_obj;
			if (ObjectInfo_typeOf(pObj) == ObjectType_array)
				str = _T("u32_t");
			else  str = Dz1Text("#invalid");
		}
		else if (strcmp(node->instance_name, INSTANCE_NAME_ELEMENT) == 0)
		{
			ConstructCodecEntry *parent = node->parent;
			ObjectInfo *pObj = parent->parent_obj;
			if (ObjectInfo_typeOf(pObj) == ObjectType_array)
			{
				ObjectInfo *obj = node->obj;
				if (obj == NULL) str = Dz1Text("#unresolved");
				else if (ObjectInfo_typeOf(obj) == ObjectType_primitive)
					str.Format(_T("%s"), obj->name);
				else str.Format(_T("%s *"), obj->name);
			}
			else  str = Dz1Text("#invalid");
		}
		else if (strcmp(node->instance_name, INSTANCE_NAME_PAD) == 0)
		{
			ConstructCodecEntry *parent = node->parent;
			ObjectInfo *pObj = parent->parent_obj;
			if (ObjectInfo_typeOf(pObj) == ObjectType_structure)
				str = _T("Padding");
			else  str = Dz1Text("#invalid");
		}
		else str = _T("Unknown");
	}
	else
	{
		ObjectInfo *obj = node->obj;
		if (obj == NULL) str = Dz1Text("#unresolved");
		else
		{
			ConstructCodecEntry *parent = node->parent;
			ObjectInfo *pObj = parent->parent_obj;
			ObjectType type = ObjectInfo_typeOf(pObj);
			switch(type)
			{
			case ObjectType_structure:
				GetStructureMemberTypeStr(str, pObj, node->instance_name);
				break;
			case ObjectType_union:
				GetUnionMemberTypeStr(str, pObj, node->instance_name);
				break;
			default:
				str = _T("#unacceptable");
				break;
			}
		}
	}
	SetItemText(nRow, nSub++, str);

	// CODEC
	ConstructMemberCodecInfo *info = node->info;
	if (info == NULL) str = _T("default");
	else str = ConstructMemberCodecInfoPresentStr(info->present);
	SetItemText(nRow, nSub++, str);

	return TRUE;
}
// CListCtrlConstructMemberCodec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CComboTdcInfoStructMembers
bool_t CComboTdcInfoStructMembers::ToString(StructMemberEntry *src, CString &dst)
{
	bool_t ret = FALSE;
	dst = src->instance;
	return ret;
}
// CComboTdcInfoStructMembers
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CListCtrlConstructCodecInclude
BOOL CListCtrlConstructCodecInclude::OnInitControl()
{
	CListCtrlStyledColumnDesign _design[] =
	{
		{ _T("Include"), LVCFMT_LEFT, CLIST_COLUMN_WITH(37, 8) },
		{ NULL, 0, 0 }
	};
	u32_t cnt = sizeof(_design) / sizeof(CListCtrlStyledColumnDesign);
	return CDz1ListCtrlRW::OnInitControl(_design, cnt);
}

void CListCtrlConstructCodecInclude::GetFirstColumn(CString &str, ConstructCodecIncludeEntry *node)
{
	if (node == NULL) str = _T("(null)");
	else if (node->filename_ext == NULL || node->filename_ext[0] == 0) str = _T("null");
	else if (node->use_codate) str.Format(_T("\"%s\""), node->filename_ext);
	else str.Format(_T("<%s>"), node->filename_ext);
}

BOOL CListCtrlConstructCodecInclude::SetItemTexts(int nRow, ConstructCodecIncludeEntry *node)
{
	//Dz1Error err = DZ1_ERROR_INITIALIZER;
	//Dz1Str ptr = NULL;
	int nSub = 0;
	CString str;

	// column 0
	GetFirstColumn(str, node);
	SetItemText(nRow, nSub++, str);

	return TRUE;
}
// CListCtrlConstructCodecInclude
////////////////////////////////////////////////////////////////////////////////
