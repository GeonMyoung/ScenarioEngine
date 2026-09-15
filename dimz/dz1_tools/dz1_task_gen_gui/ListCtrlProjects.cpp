#include "stdafx.h"
#include <dz1_task_gen.h>
#include "ListCtrlProjects.h"

BOOL CListCtrlProjects::OnInitControl(void)
{
	CListCtrlStyledColumnDesign _design[] =
	{
		{ _T("Ver"), LVCFMT_LEFT, CLIST_COLUMN_WITH(6, 8) },
		{ _T("path"), LVCFMT_LEFT, CLIST_COLUMN_WITH(16, 8) },
		{ _T("Name"), LVCFMT_LEFT, CLIST_COLUMN_WITH(16, 8) },
		{ _T("GUID"), LVCFMT_LEFT, CLIST_COLUMN_WITH(32, 8) },
		{ NULL }
	};

	return CDz1ListCtrlRW::OnInitControl(_design, sizeof(_design) / sizeof(CListCtrlStyledColumnDesign));
}

BOOL CListCtrlProjects::AddRow(GenArgs2VisualStudioVer ver, Dz1Str lib_root_abs, Dz1Str middle_path, Dz1Str proj_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenArgs2VisualStudioEntry *node = NULL;
	TCHAR proj_guid[40];

	if (_load_proj_guid(proj_guid, lib_root_abs, middle_path, proj_name, ver, errp) == FALSE) ERR_OUT(errp);
	else if ((node = GenArgs2VisualStudioEntry_new(ver, middle_path, proj_name, proj_guid, errp)) == NULL) ERR_DLG_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2VisualStudioEntry_delAndSetNull, (void *)&node);

		if ((*errp = InsertRow(&node)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (GenArgs2VisualStudioEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

void CListCtrlProjects::GetFirstColumn(CString &str, GenArgs2VisualStudioEntry *node)
{
	if (node == NULL) str = _T("#error");
	else str = GenArgs2VisualStudioVerStr(node->ver);
}

BOOL CListCtrlProjects::SetItemTexts(int nRow, GenArgs2VisualStudioEntry *node)
{
	BOOL ret = TRUE;

	int nCol = 0;
	CString str;
	GetFirstColumn(str, node);
	if (SetItemText(nRow, nCol++, str) == FALSE) ret = FALSE;

	str = node->middle_path;
	if (SetItemText(nRow, nCol++, str) == FALSE) ret = FALSE;

	str = node->proj_file_name;
	if (SetItemText(nRow, nCol++, str) == FALSE) ret = FALSE;

	str = node->proj_guid;
	if (SetItemText(nRow, nCol++, str) == FALSE) ret = FALSE;

	return ret;
}

