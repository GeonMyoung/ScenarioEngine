#include "stdafx.h"
#include <dz1_task_gen.h>
#include "ListCtrlLibraries.h"

BOOL CListCtrlLibraries::OnInitControl(void)
{
	CListCtrlStyledColumnDesign _design[] =
	{
		{ _T("Name"), LVCFMT_LEFT, CLIST_COLUMN_WITH(25, 8) },
		{ _T("Seq"), LVCFMT_RIGHT, CLIST_COLUMN_WITH(5, 8) },
		{ _T("Path"), LVCFMT_LEFT, CLIST_COLUMN_WITH(40, 8) },
		{ _T("Include"), LVCFMT_LEFT, CLIST_COLUMN_WITH(16, 8) },
		{ _T("Library"), LVCFMT_LEFT, CLIST_COLUMN_WITH(16, 8) },
		{ NULL }
	};

	return CDz1ListCtrlRO::OnInitControl(_design, sizeof(_design) / sizeof(CListCtrlStyledColumnDesign));
}

void CListCtrlLibraries::SetBiasPath(TCHAR *bias)
{
	if (bias != NULL && bias[0] != 0)
	{
		Dz1STRCPY(m_bias_path, bias);
		if (m_list != NULL) ReloadControl();
	}
	else m_bias_path[0] = 0;
}

Dz1Error CListCtrlLibraries::InsertRow(GenArgs2LibraryEntry **_node, int *ret_idx /* = NULL */)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	GenArgs2LibraryEntry *node = NULL;
	if (_node == NULL || (node = *_node) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (node->order == 0)
			node->order = (u32_t)GetItemCount() + 1;

		if ((*errp = CDz1ListCtrlRW::InsertRow(_node, ret_idx)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

void CListCtrlLibraries::GetFirstColumn(CString &str, GenArgs2LibraryEntry *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (node == NULL || Dz1Str_isVoid(node->name)) str = Dz1T("#error");
	else str = node->name;
}

static Dz1Error _append_vs_type(void *ptr, GenArgs2VisualStudioEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CString *dst = (CString *)ptr;
	Dz1Str str_type = GenArgs2VisualStudioVerStr(p->ver);
	if (!dst->IsEmpty()) *dst += Dz1T(", ");
	*dst += str_type;
	return err;
}

BOOL CListCtrlLibraries::SetItemTexts(int nRow, GenArgs2LibraryEntry *node)
{
	BOOL ret = TRUE;

	int nCol = 0;
	CString str;
	// Name
	GetFirstColumn(str, node);
	if (SetItemText(nRow, nCol++, str) == FALSE) ret = FALSE;

	// Seq
	str.Format(_T("%u"), node->order);
	if (SetItemText(nRow, nCol++, str) == FALSE) ret = FALSE;

	// Path
	TCHAR temp[4096];
	if (Dz1Str_isVoid(m_bias_path) || _get_relative_path(temp, 4096, m_bias_path, node->path_root_abs, NULL) == FALSE) str = _T("#error");
	else str = temp;
	if (SetItemText(nRow, nCol++, str) == FALSE) ret = FALSE;

	// Include
	str = node->root2inc_path;
	if (SetItemText(nRow, nCol++, str) == FALSE) ret = FALSE;

	// Library
	str = node->root2lib_path;
	if (SetItemText(nRow, nCol++, str) == FALSE) ret = FALSE;

	return ret;
}

bool_t CListCtrlLibraries::SwitchOrder(int idx_a, int idx_b, Dz1Error *err /* = NULL */)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	GenArgs2LibraryEntry *node_a = GetElement(idx_a);
	UINT idx_a_state = GetItemState(idx_a, LVIS_SELECTED | LVIS_FOCUSED);
	if (node_a == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		GenArgs2LibraryEntry *node_b = GetElement(idx_b);
		UINT idx_b_state = GetItemState(idx_b, LVIS_SELECTED | LVIS_FOCUSED);
		if (node_b == NULL) ERR_SET_OUT(errp, ENOENT);
		else
		{
			u32_t temp;

			m_list->extract(m_list, node_a);
			m_list->extract(m_list, node_b);

			temp = node_a->order;
			node_a->order = node_b->order;
			node_b->order = temp;

			m_list->add(m_list, node_a);
			m_list->add(m_list, node_b);

			SetItemData(idx_a, (LPARAM)node_b);
			SetItemState(idx_a, idx_b_state, LVIS_SELECTED | LVIS_FOCUSED);

			SetItemData(idx_b, (LPARAM)node_a);
			SetItemState(idx_b, idx_a_state, LVIS_SELECTED | LVIS_FOCUSED);

			RefreshRow(idx_a);
			RefreshRow(idx_b);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t CListCtrlLibraries::Reordering(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	u32_t cnt = 0;
	GenArgs2LibraryEntry **arr = NULL;
	GenArgs2LibraryInfo *list = GetList(errp);
	if (list == NULL) ERR_OUT(errp);
	else if ((arr = list->get_array(list, &cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		bool_t do_refresh = FALSE;
		u32_t i, seq = 0;
		GenArgs2LibraryEntry *node = NULL;
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = arr[i]) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (seq == 0) seq = node->order;
			else
			{
				seq++;
				if (seq != node->order)
				{
					GenArgs2LibraryEntry *temp = list->inorder->extract(list->inorder, node);
					if (temp == NULL || temp != node) ERR_SET_OUT(errp, EFAULT);
					else
					{
						node->order = seq;
						if ((*errp = list->inorder->add(list->inorder, node)).code) ERR_OUT(errp);
						else
						{
							do_refresh = TRUE;
							Dz1Error_set(errp, 0);
						}
					}
				}
			}
		}

		if (do_refresh) ReloadControl();
	}
	return errp->code == 0 ? TRUE : FALSE;
}
