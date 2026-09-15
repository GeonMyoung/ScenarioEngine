#include "stdafx.h"
#include "Dz1MfcListCtrlTemplate.h"
BEGIN_MESSAGE_MAP(CDz1ListCtrl, CListCtrlStyled)
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(HDN_ITEMCLICKA, 0, &CDz1ListCtrl::OnHdnItemclick)
	ON_NOTIFY(HDN_ITEMCLICKW, 0, &CDz1ListCtrl::OnHdnItemclick)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// Message Handler
void CDz1ListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_get_focus_on_mose_over)
	{
		if (GetFocus() != this) SetFocus();
	}
	CListCtrlStyled::OnMouseMove(nFlags, point);
}

void CDz1ListCtrl::OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	if (m_sort_col == -1 || m_sort_col != phdr->iItem)
	{	// 처음 클릭 또는 다른 column 클릭
		if (m_sort_col != -1) RestoreColumnName();			// Column 이름 복구

		m_sort_col = phdr->iItem;							// Sort Column 변경
		m_sort_dir = 1;										// Sort 방향 설정

		SaveColumnName();									// Column 이름 저장
		SetColumnName();									// Column 이름 변경

		SortTableGen();										// 정렬 테이블 생성
		ReloadControl();
	}
	else
	{	// 정렬중인 Column에 클릭
		if (m_sort_dir == 1)
		{
			m_sort_dir = -1;								// 정방향이면 역방향으로
			SetColumnName();								// Column 이름 변경

			ReloadControl();								// 방향만 바꿨음으로 리로드만
		}
		else if (m_sort_dir == -1)							// 역방향이면 기본으로
		{
			RestoreColumnName();							// Column 이름 복구

			m_sort_col = -1;								// Sort Column 해제
			m_sort_dir = 0;									// Sort 방향 해제

			Dz1QuickSrotTable_delAndSetNull(&m_tbl);		// 정렬 테이블 삭제

			ReloadControl();
		}
	}
}
// Message Handler
///////////////////////////////////////////////////////////////////////////////

// int CALLBACK CDz1ListCtrl::SortCmp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
// {
// 	CDz1ListCtrl *list = (CDz1ListCtrl *)lParamSort;
// 	LVFINDINFO A, B;
// 
// 	A.flags = LVFI_PARAM;
// 	A.lParam = lParam1;
// 
// 	B.flags = LVFI_PARAM;
// 	B.lParam = lParam2;
// 
// 	int a = list->FindItem(&A, -1);
// 	int b = list->FindItem(&B, -1);
// 
// 	CString strA = list->GetItemText(a, list->m_sort_col);
// 	CString strB = list->GetItemText(b, list->m_sort_col);
// 
// 	int lenA = strA.GetLength();
// 	int lenB = strB.GetLength();
// 
// 	int ret = 0;
// 	if (lenA == lenB) ret = Dz1STRCMP(strA.GetBuffer(), strB.GetBuffer());
// 	else ret = lenA - lenB;
// 
// 	if (ret != 0 && list->m_sort_dir < 0) ret = -ret;
// 
// 
// 	return ret;
// }

///////////////////////////////////////////////////////////////////////////////
// Sort Column Name Helper
void CDz1ListCtrl::SaveColumnName(void)
{
	if (m_sort_col != -1)
	{
		LVCOLUMN col;
		col.mask = LVCF_TEXT;
		col.pszText = m_sort_name;
		col.cchTextMax = 1023;
		memset(m_sort_name, 0, sizeof(TCHAR) * 1024);
		GetColumn(m_sort_col, &col);
	}
}

void CDz1ListCtrl::RestoreColumnName(void)
{
	if (m_sort_col != -1)
	{
		LVCOLUMN col;
		col.mask = LVCF_TEXT;
		col.pszText = m_sort_name;
		SetColumn(m_sort_col, &col);
	}
}

void CDz1ListCtrl::SetColumnName(void)
{
	if (m_sort_col != -1)
	{
		CString str;
		if (m_sort_dir > 0) str = _T("+");
		else if (m_sort_dir < 0) str = _T("-");
		str += m_sort_name;

		LVCOLUMN col;
		col.mask = LVCF_TEXT;
		col.pszText = str.GetBuffer();
		SetColumn(m_sort_col, &col);
	}
}
// Sort Column Name Helper
///////////////////////////////////////////////////////////////////////////////

static int _ListColCmpFunc(void *keyA, void *keyB)
{
	if (keyA == NULL && keyB == NULL) return 0;
	else if (keyA == NULL) return -1;
	else if (keyB == NULL) return 1;
	else
	{
		Dz1Str a = (Dz1Str)keyA;
		Dz1Str b = (Dz1Str)keyB;
		return Dz1STRCMP(a, b);
	}
}

static Dz1QuickSrotTable *_gen_sort_tbl(CDz1ListCtrl *ctrl, int sort_col_idx, Dz1Error *errp)
{
	int cnt = ctrl->GetItemCount();
	Dz1QuickSrotTable *tbl = Dz1QuickSrotTable_new(cnt, (Dz1DelFunc)Dz1Str_del, _ListColCmpFunc, errp);
	if (tbl == NULL) ERR_OUT(errp);
	else
	{
		int i;
		CString str;
		Dz1Str key = NULL;
		void *body = NULL;
		pthread_cleanup_push(Dz1QuickSrotTable_delAndSetNull, (void *)&tbl);

		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			str = ctrl->GetItemText(i, sort_col_idx);
			body = (void *)(LONG_PTR)ctrl->GetItemData(i);
			if ((key = Dz1Str_dup(str.GetBuffer(), errp)) == NULL) ERR_OUT(errp);
			else if (Dz1QuickSrotTable_addEntry(tbl, i, key, body, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		Dz1QuickSort(tbl);

		pthread_cleanup_pop(errp->code); // (Dz1QuickSrotTable_delAndSetNull, (void *)&tbl);
	}
	return tbl;
}

BOOL CDz1ListCtrl::SortTableGen(void)
{
	BOOL ret = FALSE;
	if (m_sort_col != -1 && m_sort_dir != 0)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		Dz1QuickSrotTable *tbl = _gen_sort_tbl(this, m_sort_col, errp);
		if (tbl == NULL) ERR_OUT(errp);
		else
		{
			Dz1QuickSrotTable_delAndSetNull(&m_tbl);
			m_tbl = tbl;
			ret = TRUE;
		}
	}
	return ret;
}

void CDz1ListCtrl::SortTableReset(void)
{
	if (m_sort_col != -1)
	{	// 정렬중인 Column이 있음
		RestoreColumnName();

		m_sort_col = -1;
		m_sort_dir = 0;
	}
	Dz1QuickSrotTable_delAndSetNull(&m_tbl);
}