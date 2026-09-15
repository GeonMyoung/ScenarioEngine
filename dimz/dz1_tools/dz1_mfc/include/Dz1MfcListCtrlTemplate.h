#ifndef DZ1_MFC_LIST_CTRL_TEMPLATE_H
#define DZ1_MFC_LIST_CTRL_TEMPLATE_H

#include <dz1_error.h>
#include <dz1_mfc.h>
#include <dz1_logics.h>
#include <Dz1MfcDef.h>
#ifdef __cplusplus
#include "ListCtrlStyled.h"

static __inline__ void _lvis_state_dumpA(UINT state, bool_t nl)
{
	Dz1ThreadA_printf("(");
	if (state & LVIS_ACTIVATING) Dz1ThreadA_printf(" A");
	if (state & LVIS_CUT) Dz1ThreadA_printf(" C");
	if (state & LVIS_DROPHILITED) Dz1ThreadA_printf(" D");
	if (state & LVIS_FOCUSED) Dz1ThreadA_printf(" FOCUS");
	if (state & LVIS_OVERLAYMASK) Dz1ThreadA_printf(" O");
	if (state & LVIS_SELECTED) Dz1ThreadA_printf(" SEL");
	if (state & LVIS_STATEIMAGEMASK) Dz1ThreadA_printf(" SMASK");
	if (nl) Dz1ThreadA_printf(" )\n"); else Dz1ThreadA_printf(" )");
}

#ifndef UNIX_SYSTEM
static __inline__ void _lvis_state_dumpW(UINT state, bool_t nl)
{
	Dz1ThreadW_printf(L"(");
	if (state & LVIS_ACTIVATING) Dz1ThreadW_printf(L" A");
	if (state & LVIS_CUT) Dz1ThreadW_printf(L" C");
	if (state & LVIS_DROPHILITED) Dz1ThreadW_printf(L" D");
	if (state & LVIS_FOCUSED) Dz1ThreadW_printf(L" FOCUS");
	if (state & LVIS_OVERLAYMASK) Dz1ThreadW_printf(L" O");
	if (state & LVIS_SELECTED) Dz1ThreadW_printf(L" SEL");
	if (state & LVIS_STATEIMAGEMASK) Dz1ThreadW_printf(L" SMASK");
	if (nl) Dz1ThreadW_printf(L" )\n"); else Dz1ThreadW_printf(L" )");
}
#ifdef	UNICODE
#define _lvis_state_dump			_lvis_state_dumpW
#else	// UNICODE
#define _lvis_state_dump			_lvis_state_dumpA
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define _lvis_state_dump			_lvis_state_dumpA
#endif	// UNIX_SYSTEM

class CDz1ListCtrl : public CListCtrlStyled
{
public:
	CDz1ListCtrl() : CListCtrlStyled()
	{
		m_get_focus_on_mose_over = FALSE;
		m_sort_col = -1;
		m_sort_dir = 0;
		m_sort_name[0] = 0;
		m_tbl = NULL;
	};

	virtual ~CDz1ListCtrl()
	{
		Dz1QuickSrotTable_delAndSetNull(&m_tbl);
		CListCtrlStyled::~CListCtrlStyled();
	}

	void SetFocusOnMouseOver(bool_t v) { m_get_focus_on_mose_over = v; }
private:
	bool_t				 m_get_focus_on_mose_over;
	int					 m_sort_col;
	TCHAR				 m_sort_name[1024];
	void				 SaveColumnName(void);
	void				 RestoreColumnName(void);
	void				 SetColumnName(void);
protected:
	bool_t				 m_sort_dir;
	Dz1QuickSrotTable	*m_tbl;
	bool_t				 SortTableGen(void);
	void				 SortTableReset(void);
	virtual BOOL		 ReloadControl(bool_t redraw_ctrl = TRUE) = 0;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult);
};

///////////////////////////////////////////////////////////////////////////////
// Read-Only List Ctrl
template <typename T_List, typename T_Element>
class CDz1ListCtrlRO : public CDz1ListCtrl
{
public:
	T_List *m_list;																		// Structure처럼 사용하기 위해 맨 처음에
public:
	CDz1ListCtrlRO() : CDz1ListCtrl()
	{
		m_list = NULL;
		m_list_del = NULL;
		m_filters = Dz1MfcListFilterList_new(NULL); ASSERT(m_filters != NULL);
		m_filter_match = NULL;
		m_filter_arr = NULL;

	}
	virtual ~CDz1ListCtrlRO()
	{
		if (m_list_del != NULL) m_list_del(m_list);
		m_list = NULL;

		Dz1MfcListFilterList_delAndSetNull(&m_filters);
		if (m_filter_arr) Dz1Free(m_filter_arr);
		CDz1ListCtrl::~CDz1ListCtrl();
	}

	virtual BOOL OnInitControl(CListCtrlStyledColumnDesign column_fmt[], int numOfCol);

	void Load(T_List *list, void (*list_del)(T_List *p) = NULL)
	{
		if (m_list_del != NULL) m_list_del(m_list);

		m_list = list; ASSERT(m_list != NULL);
		m_list_del = list_del;

		SetRedraw(FALSE);
		Dz1QuickSrotTable_delAndSetNull(&m_tbl);
		ReloadControl(FALSE);
		if (SortTableGen()) ReloadControl(FALSE);
		SetRedraw(TRUE);
	}

	virtual void Unload(void)
	{
		if (m_list_del != NULL) m_list_del(m_list);
		m_list = NULL;

		SetRedraw(FALSE);

		DeleteAllItems();
		Dz1QuickSrotTable_delAndSetNull(&m_tbl);

		SetRedraw(TRUE);
	}

	T_List *GetList(Dz1Error *err);
	T_Element *GetElement(int idx, Dz1Error *err = NULL);

	void SetFilterFunc(Dz1Error (*filter_match)(T_Element *src, Dz1MfcListFilterEntry *match, bool_t *ret_status) ) { m_filter_match = filter_match; }
	void ClrFilterFunc(void) { m_filter_match = NULL; }

	Dz1Error SetFilter(int col, Dz1LogicMatchType mode, s64_t sNum, bool_t redrow = TRUE);
	Dz1Error SetFilter(int col, Dz1LogicMatchType mode, u64_t uNum, bool_t redrow = TRUE);
	Dz1Error SetFilter(int col, Dz1LogicMatchType mode, s64_t low, s64_t high, bool_t redrow = TRUE);
	Dz1Error SetFilter(int col, Dz1LogicMatchType mode, u64_t low, u64_t high, bool_t redrow = TRUE);
	Dz1Error SetFilter(int col, Dz1LogicMatchType mode, Dz1Str text, bool_t redrow = TRUE);
	Dz1Error SetFilter(int col, Dz1LogicMatchType mode, Dz1Str text[], size_t text_cnt, bool_t redrow = TRUE);
	Dz1Error SetFilter(int col, Dz1LogicMatchType mode, Dz1MfcListFilterValue *value, bool_t redrow = TRUE);

	Dz1Error ClrFilter(int col, bool_t redrow = TRUE);

// 	void	 SetExclude(T_List *excl, bool_t redrow = TRUE) { m_exclude = excl; if (redrow) ReloadControl(); };
// 	void	 ClrExclude(bool_t redrow = TRUE) { SetExclude(NULL, redrow); }

	virtual int GetCurSelIdx(void)
	{
		int ret = -1;
		if (GetSelectedCount() == 1)
		{
			POSITION pos = GetFirstSelectedItemPosition();
			ret = GetNextSelectedItem(pos);
		}
		return ret;
	}

	virtual bool_t SelectItemByIdx(int idx)
	{
		bool_t ret = FALSE;
		int i, cnt = GetItemCount();
		for (i = 0; i < cnt; i++)
		{
			if (i == idx)
			{
				SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
				EnsureVisible(i, FALSE);
				ret = TRUE;
			}
			else SetItemState(i, 0, LVIS_FOCUSED | LVIS_SELECTED);
		}
		return ret;
	}
	virtual T_Element *FindByKey(T_Element *key, int *ret_idx = NULL)
	{
		T_Element *ret = m_list->find(m_list, key);
		if (ret_idx != NULL)
		{
			int i;
			for (i = 0; i < GetItemCount(); i++)
			{
				if (GetElement(i, NULL) == ret)
				{
					*ret_idx = i;
					break;
				}
			}
		}
		return ret;
	}
	virtual bool_t SelectItemByPtr(T_Element *p)
	{
		bool_t ret = FALSE;
		int i, cnt = GetItemCount();
		T_Element *exist = NULL;
		for (i = 0; i < cnt; i++)
		{
			exist = (T_Element *)(LONG_PTR)GetItemData(i);
			if (exist == p)
			{
				SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
				EnsureVisible(i, FALSE);
				ret = TRUE;
			}
			else SetItemState(i, 0, LVIS_FOCUSED | LVIS_SELECTED);
		}
		return ret;
	}
	virtual void TravelItem(bool_t (*travel_func)(void *user_ptr, T_Element *p, bool_t is_selected), void *user_ptr)
	{
		int i, cnt = GetItemCount();
		UINT state = 0;
		T_Element *node = NULL;
		for (i = 0; i < cnt; i++)
		{
			if ((node = GetElement(i, NULL)) != NULL)
			{
				state = GetItemState(i, LVIS_SELECTED);
				if (travel_func(user_ptr, node, state ? TRUE : FALSE) == FALSE) break;
			}
		}
	}
private:
	void (*m_list_del)(T_List *p);

	Dz1MfcListFilterList *m_filters;
	Dz1MfcListFilterEntry **m_filter_arr;
	Dz1Error (*m_filter_match)(T_Element *src, Dz1MfcListFilterEntry *match, bool_t *ret_status);

	Dz1Error SetFilter(Dz1MfcListFilterEntry **entry, bool_t redrow = TRUE);
	bool_t CheckMatch(T_Element *node);
//	T_List *m_exclude;
protected:
	virtual int		 AddToControl(T_Element *node);											// 출력창에 추가
	virtual void	 GetFirstColumn(CString &str, T_Element *node) = 0;						// <--- pure virtual : 사용자가 출력할 문자열 생성
	virtual BOOL	 SetItemTexts(int nRow, T_Element *node) = 0;							// <--- pure virtual : 사용자가 출력할 문자열 생성
	virtual BOOL	 ReloadControl(bool_t redraw_ctrl = TRUE);								// 모든 출력내용 삭제 후 재 추가
};

// Column설정
template <typename T_List, typename T_Element>
BOOL CDz1ListCtrlRO<T_List, T_Element>::OnInitControl(CListCtrlStyledColumnDesign column_fmt[], int numOfCol)
{
	BOOL ret = TRUE;
	int idx, cnt;

	SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);

	LV_COLUMN lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvColumn.pszText = _T("Dummy");
	lvColumn.fmt = 0;
	lvColumn.cx = 10;
	lvColumn.iSubItem = 0;
	InsertColumn(0, &lvColumn);

	CListCtrlStyledColumnDesign *i;
	for (idx = 1, cnt = 0, i = column_fmt; i->name != NULL && cnt < numOfCol; idx++, cnt++, i++)
	{
		lvColumn.pszText = i->name;
		lvColumn.fmt = i->fmt;
		lvColumn.cx = i->cx;
		lvColumn.iSubItem = idx;
		InsertColumn(idx, &lvColumn);
	}

	DeleteColumn(0);

	return ret;
}

template <typename T_List, typename T_Element>
T_List *CDz1ListCtrlRO<T_List, T_Element>::GetList(Dz1Error *err)
{
	T_List *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (m_list == NULL) Dz1Error_set(errp, ENOENT);
	else ret = m_list;
	return ret;
}

template <typename T_List, typename T_Element>
T_Element *CDz1ListCtrlRO<T_List, T_Element>::GetElement(int idx, Dz1Error *err)
{
	T_Element *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (m_list == NULL)
		ERR_SET_OUT(errp, ENOENT);
	else if (idx < 0)
	{
		Dz1Error_set(errp, EINVAL);
	}
	else ret = (T_Element *)(LONG_PTR)GetItemData(idx);
	return ret;
}

template <typename T_List, typename T_Element>
int CDz1ListCtrlRO<T_List, T_Element>::AddToControl(T_Element *node)
{
	bool_t status = TRUE;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (m_list == NULL) return -1;
//	else if (m_exclude != NULL && m_exclude->find(m_exclude, node) != NULL) return -1;
	else if (CheckMatch(node) == FALSE) return -1;
	else
	{
		int nRow = this->GetItemCount();
		CString str;
		GetFirstColumn(str, node);
		nRow = InsertItem(LVIF_PARAM, nRow, str, 0, 0, 0, (LPARAM)(LONG_PTR)node);
		SetItemTexts(nRow, node);
		return nRow;
	}
}

template <typename T_List, typename T_Element>
BOOL CDz1ListCtrlRO<T_List, T_Element>::ReloadControl(bool_t redraw_ctrl)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (m_list != NULL)
	{
		if (redraw_ctrl) SetRedraw(FALSE);
		DeleteAllItems();

		if (m_tbl != NULL)
		{
			int i;
			if (m_sort_dir > 0)
			{	// Ascending
				for (i = 0; i < m_tbl->arr_cnt; i++) AddToControl((T_Element *)m_tbl->arr[i]->body);
			}
			else
			{	// Desending
				for (i = m_tbl->arr_cnt; i > 0; i--) AddToControl((T_Element *)m_tbl->arr[i-1]->body);
			}
		}
		else
		{
			u32_t cnt = 0;
			T_Element **arr = m_list->get_array(m_list, &cnt, errp);
			if (arr == NULL) ERR_OUT(errp);
			else
			{
				size_t i;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);

				for (i = 0; i < cnt; i++) AddToControl(arr[i]);

				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
			}
		}
		if (redraw_ctrl) SetRedraw(TRUE);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRO<T_List, T_Element>::SetFilter(int col, Dz1LogicMatchType mode, s64_t sNum, bool_t redrow)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LVCOLUMN vCol;
	if (GetColumn(col, &vCol) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MfcListFilterEntry key = { col }, *node = m_filters->find(m_filters, &key);
		if (node != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MfcListFilterEntry_new(col, mode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MfcListFilterValue *p = NULL;
			pthread_cleanup_push(Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
			if ((node->value = p = Dz1MfcListFilterValue_new(Dz1MfcListFilterValuePresent_sNum, &sNum, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = SetFilter(&node, redrow)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRO<T_List, T_Element>::SetFilter(int col, Dz1LogicMatchType mode, u64_t uNum, bool_t redrow)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LVCOLUMN vCol;
	if (GetColumn(col, &vCol) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MfcListFilterEntry key = { col }, *node = m_filters->find(m_filters, &key);
		if (node != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MfcListFilterEntry_new(col, mode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MfcListFilterValue *p = NULL;
			pthread_cleanup_push(Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
			if ((node->value = p = Dz1MfcListFilterValue_new(Dz1MfcListFilterValuePresent_uNum, &uNum, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = SetFilter(&node, redrow)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRO<T_List, T_Element>::SetFilter(int col, Dz1LogicMatchType mode, s64_t low, s64_t high, bool_t redrow)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LVCOLUMN vCol;
	if (GetColumn(col, &vCol) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MfcListFilterEntry key = { col }, *node = m_filters->find(m_filters, &key);
		if (node != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MfcListFilterEntry_new(col, mode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MfcListFilterValue *p = NULL;
			pthread_cleanup_push(Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
			if ((node->value = p = Dz1MfcListFilterValue_new(Dz1MfcListFilterValuePresent_sRange, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((p->x.sRange = Dz1MfcListFilterValueRangeSigned_new(low, high, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = SetFilter(&node, redrow)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRO<T_List, T_Element>::SetFilter(int col, Dz1LogicMatchType mode, u64_t low, u64_t high, bool_t redrow)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LVCOLUMN vCol;
	if (GetColumn(col, &vCol) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MfcListFilterEntry key = { col }, *node = m_filters->find(m_filters, &key);
		if (node != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MfcListFilterEntry_new(col, mode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MfcListFilterValue *p = NULL;
			pthread_cleanup_push(Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
			if ((node->value = p = Dz1MfcListFilterValue_new(Dz1MfcListFilterValuePresent_uRange, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((p->x.uRange = Dz1MfcListFilterValueRangeUnsigned_new(low, high, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = SetFilter(&node, redrow)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRO<T_List, T_Element>::SetFilter(int col, Dz1LogicMatchType mode, Dz1Str text, bool_t redrow)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LVCOLUMN vCol;
	if (GetColumn(col, &vCol) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MfcListFilterEntry key = { col }, *node = m_filters->find(m_filters, &key);
		if (node != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MfcListFilterEntry_new(col, mode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MfcListFilterValue *p = NULL;
			pthread_cleanup_push(Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
			if ((node->value = p = Dz1MfcListFilterValue_new(Dz1MfcListFilterValuePresent_txtValue, text, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = SetFilter(&node, redrow)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRO<T_List, T_Element>::SetFilter(int col, Dz1LogicMatchType mode, Dz1Str text[], size_t text_cnt, bool_t redrow)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LVCOLUMN vCol;
	if (GetColumn(col, &vCol) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MfcListFilterEntry key = { col }, *node = m_filters->find(m_filters, &key);
		if (node != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MfcListFilterEntry_new(col, mode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MfcListFilterValue *p = NULL;
			pthread_cleanup_push(Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
			if ((node->value = p = Dz1MfcListFilterValue_new(Dz1MfcListFilterValuePresent_txtList, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((p->x.txtList = Dz1LogicStringArr_build(text, text_cnt, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = SetFilter(&node, redrow)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRO<T_List, T_Element>::SetFilter(int col, Dz1LogicMatchType mode, Dz1MfcListFilterValue *value, bool_t redrow)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LVCOLUMN vCol;
	if (GetColumn(col, &vCol) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MfcListFilterEntry key = { col }, *node = m_filters->find(m_filters, &key);
		if (node != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MfcListFilterEntry_new(col, mode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MfcListFilterValue *p = NULL;
			pthread_cleanup_push(Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
			if ((node->value = Dz1MfcListFilterValue_clone(value, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = SetFilter(&node, redrow)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1MfcListFilterEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRO<T_List, T_Element>::ClrFilter(int col, bool_t redrow)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LVCOLUMN vCol;
	if (GetColumn(col, &vCol) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MfcListFilterEntry key = { col };
		m_filters->remove(m_filters, &key);

		if (m_filter_arr) Dz1Free(m_filter_arr);
		m_filter_arr = m_filters->get_array(m_filters, NULL, NULL); ASSERT(m_filter_arr != NULL);

		if (redrow) ReloadControl();
	}
	return err;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRO<T_List, T_Element>::SetFilter(Dz1MfcListFilterEntry **value, bool_t redrow)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (value == NULL || (*value) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = m_filters->add(m_filters, (*value) )).code) ERR_OUT(errp);
	else
	{
		(*value) = NULL;

		if (m_filter_arr) Dz1Free(m_filter_arr);
		m_filter_arr = m_filters->get_array(m_filters, NULL, NULL); ASSERT(m_filter_arr != NULL);

		if (redrow) ReloadControl();
	}
	return err;
}

template <typename T_List, typename T_Element>
bool_t CDz1ListCtrlRO<T_List, T_Element>::CheckMatch(T_Element *node)
{
	bool_t ret = TRUE;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (m_filter_match == NULL) { }
	else if (m_filter_arr == NULL) ret = FALSE;
	else
	{
		Dz1MfcListFilterEntry **i, *match;
		for (i = m_filter_arr; errp->code == 0 && ret == TRUE && (*i) != NULL; i++)
		{
			match = (*i);
			if ((*errp = m_filter_match(node, match, &ret)).code) ret = FALSE;
		}
	}
	return ret;
}

// Read-Only List Ctrl
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Read-Write List Ctrl
template <typename T_List, typename T_Element>
class CDz1ListCtrlRW : public CDz1ListCtrlRO<T_List, T_Element>
{
public:
	CDz1ListCtrlRW(T_Element *(*clone_element)(T_Element *src, Dz1Error *err),
				   void (*delete_element)(T_Element *ptr) ) : CDz1ListCtrlRO<T_List, T_Element>()
	{
		m_list_dirty_local = FALSE;
		m_list_dirty = &m_list_dirty_local;
		m_clone_element = clone_element;
		m_delete_element = delete_element;
		m_exclude = NULL;
	}
	virtual ~CDz1ListCtrlRW()
	{
		m_exclude = NULL;
		CDz1ListCtrlRO::~CDz1ListCtrlRO();
	}

	virtual void Load(T_List *list, bool_t *list_dirty, void (*m_list_del)(T_List *p) = NULL) { CDz1ListCtrlRO::Load(list, m_list_del); m_list_dirty = list_dirty; }
	virtual void Unload(void) { CDz1ListCtrlRO::Unload(); m_list_dirty = &m_list_dirty_local; m_list_dirty_local = FALSE; }

	virtual Dz1Error AddRow(T_Element *src, int *ret_idx = NULL);							// copy and insert
	virtual Dz1Error InsertRow(T_Element **node, int *ret_idx = NULL);						// insert and set null
	virtual void RemoveRow(int idx);
	virtual void RefreshRow(int idx);
	virtual void RefreshAll(void)
	{
		int i, cnt = GetItemCount();
		SetRedraw(FALSE);
		for (i = 0; i < cnt; i++) RefreshRow(i);
		SetRedraw(TRUE);
	}

	virtual void TravelSelectedItem(bool_t (*travel_func)(void *user_ptr, T_Element *p, bool_t &refresh), void *user_ptr)
	{
		T_Element *node = NULL;
		POSITION pos = GetFirstSelectedItemPosition();
		int idx; bool_t refresh;
		while((idx = GetNextSelectedItem(pos)) >= 0)
		{
			if ((node = GetElement(idx, NULL)) != NULL)
			{
				bool_t stop = travel_func(user_ptr, node, refresh);
				if (refresh) RefreshRow(idx);
				if (stop) break;
			}
		}
	}
	void	 SetExclude(T_List *excl, bool_t redrow = TRUE) { m_exclude = excl; if (redrow) ReloadControl(); };
	void	 ClrExclude(bool_t redrow = TRUE) { SetExclude(NULL, redrow); }
protected:
	virtual int	AddToControl(T_Element *node);											// 출력창에 추가
	void SetDirty(void);
	void ClrDirty(void);
	bool_t GetDirty(void) { return (*m_list_dirty); }
	T_Element *(*m_clone_element)(T_Element *src, Dz1Error *err);
	void (*m_delete_element)(T_Element *ptr);
private:
	T_List *m_exclude;
	bool_t *m_list_dirty;
	bool_t m_list_dirty_local;
};

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRW<T_List, T_Element>::AddRow(T_Element *src, int *ret_idx)
{
	T_Element *node = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (m_list == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((node = m_clone_element(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)m_delete_element, (void *)node);
		if ((*errp = InsertRow(&node, ret_idx)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // ((Dz1DelFunc)m_delete_element, (void *)node);
	}
	return err;
}

template <typename T_List, typename T_Element>
Dz1Error CDz1ListCtrlRW<T_List, T_Element>::InsertRow(T_Element **node, int *ret_idx)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (m_list == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (node == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ( (*node) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = m_list->add(m_list, (*node) )).code) ERR_OUT(errp);
	else
	{
		int idx = AddToControl( (*node) );
		if (m_list_dirty) (*m_list_dirty) = TRUE;
		(*node) = NULL;
		if (ret_idx != NULL) (*ret_idx) = idx;
		Dz1Error_set(errp, 0);
	}
	return err;
}

template <typename T_List, typename T_Element>
void CDz1ListCtrlRW<T_List, T_Element>::RemoveRow(int idx)
{
	T_Element *node = NULL;
	if (idx >= 0 && (node = (T_Element *)(LONG_PTR)GetItemData(idx)) != NULL)
	{
		DeleteItem(idx);
		m_list->remove(m_list, node);
		if (m_list_dirty) (*m_list_dirty) = TRUE;
	}
}

template <typename T_List, typename T_Element>
void CDz1ListCtrlRW<T_List, T_Element>::RefreshRow(int idx)
{
	T_Element *node = NULL;
	if (idx >= 0 && (node = (T_Element *)(LONG_PTR)GetItemData(idx)) != NULL)
		SetItemTexts(idx, node);
}

template <typename T_List, typename T_Element>
int CDz1ListCtrlRW<T_List, T_Element>::AddToControl(T_Element *node)
{
	bool_t status = TRUE;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (m_list == NULL) return -1;
	else if (m_exclude != NULL && m_exclude->find(m_exclude, node) != NULL) return -1;
	else return CDz1ListCtrlRO::AddToControl(node);

// 	else if (CheckMatch(node) == FALSE) return -1;
// 	else
// 	{
// 		int nRow = this->GetItemCount();
// 		CString str;
// 		GetFirstColumn(str, node);
// 		nRow = InsertItem(LVIF_PARAM, nRow, str, 0, 0, 0, (LPARAM)(LONG_PTR)node);
// 		SetItemTexts(nRow, node);
// 		return nRow;
// 	}
}

template <typename T_List, typename T_Element>
void CDz1ListCtrlRW<T_List, T_Element>::SetDirty(void)
{
	if (m_list_dirty != NULL) (*m_list_dirty) = TRUE;
}

template <typename T_List, typename T_Element>
void CDz1ListCtrlRW<T_List, T_Element>::ClrDirty(void)
{
	if (m_list_dirty != NULL) (*m_list_dirty) = FALSE;
}

// Read-Write List Ctrl
///////////////////////////////////////////////////////////////////////////////
#endif

#endif