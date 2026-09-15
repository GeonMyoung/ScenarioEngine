#include "stdafx.h"
#include "Dz1MfcListCtrlLanManPath.h"
#include "Dz1MfcStringUtil.h"
BOOL CDz1MfcListCtrlLanManPath::OnInitControl()
{
	CListCtrlStyledColumnDesign _design[] =
	{
		{ _T("Network Share Folter"), LVCFMT_LEFT, CLIST_COLUMN_WITH(40, 8) },
		{ NULL, 0, 0 }
	};
	u32_t cnt = sizeof(_design) / sizeof(CListCtrlStyledColumnDesign);
	return OnInitControl(_design, cnt);
}

BOOL CDz1MfcListCtrlLanManPath::OnInitControl(CListCtrlStyledColumnDesign column_fmt[], int numOfCol)
{
	return CDz1ListCtrlRW::OnInitControl(column_fmt, numOfCol);
}

void CDz1MfcListCtrlLanManPath::GetFirstColumn(CString &str, Dz1MfcLanManPathEntry *node)
{
	if (node == NULL) str = _T("(null)");
	else str = node->name;
}

BOOL CDz1MfcListCtrlLanManPath::SetItemTexts(int nRow, Dz1MfcLanManPathEntry *node)
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

Dz1Error CDz1MfcListCtrlLanManPath::AddLanManPath(CString &str, int *ret_idx)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MfcLanManPathEntry *node = NULL;
	if (Dz1Dir_isExist(str.GetBuffer()) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else if ((node  = Dz1MfcLanManPathEntry_new(str.GetBuffer(), errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcLanManPathEntry_delAndSetNull, (void *)&node);
		if ((*errp = InsertRow(&node, ret_idx)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MfcLanManPathEntry_delAndSetNull, (void *)&node);
	}
	return err;
}