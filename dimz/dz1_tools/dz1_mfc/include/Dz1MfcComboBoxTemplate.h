#ifndef DZ1_MFC_COMBO_CTRL_TEMPLATE_H
#define DZ1_MFC_COMBO_CTRL_TEMPLATE_H

#include <dz1_str.h>

#ifdef __cplusplus
#ifdef WIN32

///////////////////////////////////////////////////////////////////////////////
// Enumerate to Combo Box
template <typename T_Enumerate>
class CDz1ComboCtrl : public CComboBox
{
public:
	T_Enumerate m_data;
	T_Enumerate m_data_max;

	CDz1ComboCtrl(T_Enumerate data_max, Dz1Str (*ToString)(T_Enumerate v) ) : CComboBox()
	{
		m_data = m_data_max = data_max;
		m_ToString = ToString;
		ASSERT(m_ToString != NULL);
	}
	virtual ~CDz1ComboCtrl() { CComboBox::~CComboBox(); }

	virtual BOOL OnInitControl();
	T_Enumerate	 GetCurSelValue(void);
	BOOL		 SetCurValue(T_Enumerate v);
	BOOL		 DeleteValue(T_Enumerate v);
protected:
	Dz1Str			(*m_ToString)(T_Enumerate v);
};

template <typename T_Enumerate>
BOOL CDz1ComboCtrl<T_Enumerate>::OnInitControl()
{
	BOOL ret = TRUE;

	int i, idx;
	CString str;
	for (i = 0; i < (int)m_data_max; i++)
	{
		str = m_ToString((T_Enumerate)i);
		if ((idx = AddString(str)) != CB_ERR)
		{
			SetItemData(idx, (DWORD_PTR)i);
		}
	}
	SetCurSel(-1);

	return ret;
}

template <typename T_Enumerate>
T_Enumerate CDz1ComboCtrl<T_Enumerate>::GetCurSelValue()
{
	T_Enumerate ret = m_data_max;
	int idx = GetCurSel();
	if (idx != CB_ERR)
		ret = (T_Enumerate)GetItemData(idx);
	return ret;
}

template <typename T_Enumerate>
BOOL CDz1ComboCtrl<T_Enumerate>::SetCurValue(T_Enumerate v)
{
	BOOL ret = FALSE;
	T_Enumerate my;
	int i, cnt = this->GetCount();
	for (i = 0; i < cnt; i++)
	{
		my = (T_Enumerate)this->GetItemData(i);
		if (my == v)
		{
			this->SetCurSel(i);
			ret = TRUE;
			break;
		}
	}
	return ret;
}

template <typename T_Enumerate>
BOOL CDz1ComboCtrl<T_Enumerate>::DeleteValue(T_Enumerate v)
{
	BOOL ret = FALSE;
	T_Enumerate my;
	int i, cnt = this->GetCount();
	for (i = 0; i < cnt; i++)
	{
		my = (T_Enumerate)this->GetItemData(i);
		if (my == v)
		{
			this->DeleteString(i);
			ret = TRUE;
			break;
		}
	}
	return ret;
}
// Enumerate to Combo Box
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Index to Combo Box
template <typename T_Index, typename T_Member>
class CDz1IndexComboCtrl : public CComboBox
{
public:
	T_Index *m_data;

//	CDz1IndexComboCtrl(bool_t (*ToString)(T_Member *src, CString &dst) ) : CComboBox()
	CDz1IndexComboCtrl(void) : CComboBox()
	{
		m_data = NULL;
// 		m_ToString = ToString;
// 		ASSERT(m_ToString != NULL);
	}
	virtual ~CDz1IndexComboCtrl() { CComboBox::~CComboBox(); }

	virtual BOOL	 OnInitControl(T_Index *data);
	BOOL			 Load(T_Index *data);
	BOOL			 Reload(void);
	T_Member		*GetCurSelValue(void);
	BOOL			 SetCurValue(T_Member *key);
	BOOL			 SetCurSelStr(CString &str) { return SetCurSelStr(str.GetBuffer()); }
	BOOL			 SetCurSelStr(Dz1Str str);
	T_Member		*ExtractValue(T_Member *key);
	int				 AddValue(T_Member **v);
protected:
	virtual bool_t	 ToString(T_Member *src, CString &dst) = 0;
};

template <typename T_Index, typename T_Member>
BOOL CDz1IndexComboCtrl<T_Index, T_Member>::OnInitControl(T_Index *data)
{
	BOOL ret = TRUE;

	ret = Load(data);

	return ret;
}

template <typename T_Index, typename T_Member>
BOOL CDz1IndexComboCtrl<T_Index, T_Member>::Load(T_Index *data)
{
	BOOL ret = TRUE;
	CString str;

	GetWindowText(str);

	m_data = data; ASSERT(m_data != NULL);
	ret = Reload();

	if (str.IsEmpty() == FALSE) SetCurSelStr(str);
	else SetCurSel(-1);

	return ret;
}

template <typename T_Index, typename T_Member>
BOOL CDz1IndexComboCtrl<T_Index, T_Member>::Reload(void)
{
	BOOL ret = FALSE;
	if (m_data != NULL)
	{
		CString str;

		int idx;
		u32_t i, cnt;
		this->ResetContent();

		T_Member **arr = m_data->get_array(m_data, &cnt, NULL); ASSERT(arr != NULL);
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&arr);
		for (i = 0; i < cnt; i++)
		{
			if (ToString(arr[i], str) == FALSE) { }
			else if ((idx = AddString(str)) == CB_ERR) { }
			else SetItemDataPtr(idx, arr[i]);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&arr);
		ret = TRUE;
	}
	return ret;
}

template <typename T_Index, typename T_Member>
T_Member *CDz1IndexComboCtrl<T_Index, T_Member>::GetCurSelValue()
{
	T_Member *ret = NULL;
	if (m_data != NULL)
	{
		int idx = GetCurSel();
		if (idx != CB_ERR)
			ret = (T_Member *)GetItemDataPtr(idx);
	}
	return ret;
}

template <typename T_Index, typename T_Member>
BOOL CDz1IndexComboCtrl<T_Index, T_Member>::SetCurValue(T_Member *key)
{
	BOOL ret = FALSE;
	if (m_data != NULL)
	{
		int i, cnt = GetCount();
		T_Member *my = NULL;
		for (i = 0; i < cnt; i++)
		{
			my = (T_Member *)GetItemDataPtr(i);
			if (m_data->cmp(my, key) == 0)
			{
				SetCurSel(i);
				ret = TRUE;
				break;
			}
		}
	}
	return ret;
}

template <typename T_Index, typename T_Member>
BOOL CDz1IndexComboCtrl<T_Index, T_Member>::SetCurSelStr(Dz1Str str)
{
	BOOL ret = FALSE;
	if (m_data != NULL)
	{
		int idx = FindString(-1, str);
		if (idx != -1) 
		{
			SetCurSel(idx);
			ret = TRUE;
		}
	}
	return ret;
}

template <typename T_Index, typename T_Member>
T_Member *CDz1IndexComboCtrl<T_Index, T_Member>::ExtractValue(T_Member *key)
{
	T_Member *ret = NULL;
	if (m_data != NULL)
	{
		T_Member *my = NULL;
		int i, cnt = GetCount(), curr = GetCurSel();
		for (i = 0; i < cnt; i++)
		{
			my = (T_Member *)GetItemDataPtr(i);
			if (m_data->cmp(my, key) == 0)
			{
				m_data->extract(m_data, my);
				DeleteString(i);
				ret = my;
				if (i == curr) SetCurSel(-1);
				break;
			}
		}
	}
	return ret;
}

template <typename T_Index, typename T_Member>
int CDz1IndexComboCtrl<T_Index, T_Member>::AddValue(T_Member **v)
{
	int idx = CB_ERR;
	if (m_data != NULL)
	{
		CString str;
//		if (m_ToString((*v), str) == FALSE) { }
		if (ToString((*v), str) == FALSE) { }
		else if ((idx = AddString(str)) != CB_ERR)
		{
			DZ1_ERROR_SAFE_VAR(errp, err);
			if ((*errp = m_data->add(m_data, (*v) )).code)
			{
				DeleteString(idx);
				idx = -1;
			}
			else
			{
				SetItemDataPtr(idx, (*v));
				(*v) = NULL;
			}
		}
	}
	return idx;
}
// Index to Combo Box
///////////////////////////////////////////////////////////////////////////////

#endif	// WIN32
#endif	// __cplusplus

#endif