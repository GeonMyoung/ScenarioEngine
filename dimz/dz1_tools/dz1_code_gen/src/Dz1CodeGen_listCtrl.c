#include <dz1_aatree.h>
#include "Dz1CodeGen_listCtrl.h"

// $tdc_name$
// $parent_class$ == CListCtrl or CListCtrlStyled
// $entry_type$
// $list_type$

#define CONTINUE_LETTER			-1
#define UNTYPED_LETTER			 0
#define UPPER_LETTER			 1
#define LOWER_LETTER			 2
#define NUMBER_LETTER			 3
static int _get_letter_type(char c)
{
	if (c == '_') return CONTINUE_LETTER;
	else if (c >= 'A' && c <= 'Z') return UPPER_LETTER;
	else if (c >= 'a' && c <= 'z') return LOWER_LETTER;
	else if (c >= '0' && c <= '9') return NUMBER_LETTER;
	else return UNTYPED_LETTER;
}

static str_t _mk_define_name(char buf[1024], str_t tdc_name)
{
	int prev_type = -1, this_type;
	char *cp = tdc_name, *dp = buf;
	while(*cp)
	{
		if (prev_type == -1)
		{
			prev_type = _get_letter_type(*cp);
			*dp++ = *cp;
		}
		else
		{
			this_type = _get_letter_type(*cp);
			if (this_type != -1 && prev_type != this_type)
			{
				*dp++ = '_';
				*dp++ = *cp;
				prev_type = this_type;
			}
			else *dp++ = *cp;
		}
		cp++;
	}
	*dp++ = 0;
	return buf;
}

static Dz1Error _publish_header(FILE *dst, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	str_t hdr_base[] = {
		"#ifndef $def_name$"_CRLF,
		"#define $def_name$"_CRLF,
		_CRLF,
		"#include \"ListCtrlStyled.h\""_CRLF,
		"#include \"$tdc_name$.h\""_CRLF,
		""_CRLF,
		"class CListCtrl$list_type$ : public $parent_class$"_CRLF,
		"{"_CRLF,
		"public:"_CRLF,
		"	CListCtrl$list_type$();"_CRLF,
		"	~CListCtrl$list_type$();"_CRLF,
		""_CRLF,
		"	BOOL InitControl();"_CRLF,
		"	void CleanupData();"_CRLF,
		""_CRLF,
		"	BOOL Load(Dz1Fifo *list);"_CRLF,
		"	BOOL ShowToCtrl($entry_type$ *p);"_CRLF,
		""_CRLF,
		"	$entry_type$ *GetMyItemData(int idx);"_CRLF,
		"	$entry_type$ *Find($entry_type$ *key);"_CRLF,
		"private:"_CRLF,
		"	$list_type$ *m_list;"_CRLF,
		"};"_CRLF,
		""_CRLF,
		"#endif"_CRLF,
		NULL
	};
	if ((*errp = Dz1CodeGen_replacef(dst, hdr_base, list)).code) ERR_OUT(errp);
	return *errp;
}

static Dz1Error Dz1CodeGenListCtrlHeader_gen(str_t path, str_t _name, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	FILE *fp = NULL;
	char name[1024];
	char fn[4096];

	sprintf(name, "%s.h", _name);

	if ((*errp = Dz1FileName_mkFullName(fn, Dz1ArrElCnt(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((fp = fopen(fn, "wb")) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if		((*errp = _publish_header(fp, list)).code) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

static Dz1Error _publish_source_front(FILE *dst, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	// list_type
	str_t src_front[] = {
		"#include \"stdafx.h\""_CRLF,
		"#include \"ListCtrl$list_type$.h\""_CRLF,
		""_CRLF,
		"CListCtrl$list_type$::CListCtrl$list_type$()"_CRLF,
		"{"_CRLF,
		"	m_list = NULL;"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"CListCtrl$list_type$::~CListCtrl$list_type$()"_CRLF,
		"{"_CRLF,
		"	CleanupData();"_CRLF,
		"}"_CRLF,
		_CRLF,
		NULL
	};
	if ((*errp = Dz1CodeGen_replacef(dst, src_front, list)).code) ERR_OUT(errp);
	return *errp;
}

static Dz1Error _publish_init_control(FILE *fp, str_t list_type, Dz1CodeGenListColumnList *columns)
{
	int tab = 0;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = NULL;
	Dz1AATreeCursor *c = Dz1AATreeCursor_init(columns->storage, errp);
	if (c == NULL) ERR_OUT(errp);
	else
	{
		// Dz1CodeGenListColumn *e = NULL;

		pthread_cleanup_push(Dz1AATreeCursor_delAndSetNull, (void *)&c);
		Dz1Thread_ftprintf(fp, tab, "BOOL CListCtrl%s::InitControl(void)"_CRLF, list_type);
		Dz1Thread_ftprintf(fp, tab++, "{"_CRLF);
		Dz1Thread_ftprintf(fp, tab, "CListCtrlStyledColumnDesign _design[] ="_CRLF);
		Dz1Thread_ftprintf(fp, tab++, "{"_CRLF);

		while(Dz1AATreeCursor_cond(c))
		{
			// e = (Dz1CodeGenListColumn *)Dz1AATreeCursor_data(c);
			Dz1Thread_ftprintf(fp, tab, "{ _T(\"%s\"), LVCFMT_LEFT, CLIST_COLUMN_WITH(37, 8) },"_CRLF);
			c = Dz1AATreeCursor_next(c);
		}

		Dz1Thread_ftprintf(fp, tab, "{ NULL }"_CRLF);
		Dz1Thread_ftprintf(fp, --tab, "}"_CRLF);

		Dz1Thread_ftprintf(fp, tab, "int idx;"_CRLF);
		Dz1Thread_fprintf(fp, _CRLF);
		Dz1Thread_ftprintf(fp, tab, "m_list = NULL;"_CRLF);
		Dz1Thread_fprintf(fp, _CRLF);
		Dz1Thread_ftprintf(fp, tab, "this->SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);"_CRLF);
		Dz1Thread_fprintf(fp, _CRLF);
		Dz1Thread_ftprintf(fp, tab, "LV_COLUMN lvColumn;"_CRLF);
		Dz1Thread_ftprintf(fp, tab, "lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;"_CRLF);
		Dz1Thread_fprintf(fp, _CRLF);
		Dz1Thread_ftprintf(fp, tab, "CListCtrlStyledColumnDesign *i;"_CRLF);
		Dz1Thread_ftprintf(fp, tab, "for (idx = 0, i = _design; i->name != NULL; idx++, i++)"_CRLF);
		Dz1Thread_ftprintf(fp, tab++, "{"_CRLF);
		Dz1Thread_ftprintf(fp, tab, "lvColumn.pszText = i->name;"_CRLF);
		Dz1Thread_ftprintf(fp, tab, "lvColumn.fmt = i->fmt;"_CRLF);
		Dz1Thread_ftprintf(fp, tab, "lvColumn.cx = i->cx;"_CRLF);
		Dz1Thread_ftprintf(fp, tab, "lvColumn.iSubItem = idx;"_CRLF);
		Dz1Thread_ftprintf(fp, tab, "this->InsertColumn(idx, &lvColumn);"_CRLF);
		Dz1Thread_ftprintf(fp, --tab, "}"_CRLF);
		Dz1Thread_ftprintf(fp, tab, "return TRUE;"_CRLF);
		Dz1Thread_ftprintf(fp, --tab, "}"_CRLF);
		Dz1Thread_fprintf(fp, _CRLF);
		pthread_cleanup_pop(1); // (Dz1AATreeCursor_delAndSetNull, (void *)&c);
	}
	return err;
}

static Dz1Error _publish_source_show_to_ctrl_helper(FILE *dst, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t src_show_to_ctrl_helper[] = {
		"static Dz1Error _ShowToCtrl(void *ptr, $entry_type$ *p)"_CRLF,
		"{"_CRLF,
		"	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;"_CRLF,
		"	CListCtrl$list_type$ *dlg = (CListCtrl$list_type$ *)ptr;"_CRLF,
		""_CRLF,
		"	if (dlg->ShowToCtrl(p) == FALSE) ERR_SET_OUT(errp, EFAULT);"_CRLF,
		""_CRLF,
		"	return err;"_CRLF,
		"}"_CRLF,
		NULL
	};
	if ((*errp = Dz1CodeGen_replacef(dst, src_show_to_ctrl_helper, list)).code) ERR_OUT(errp);
	return *errp;
}

///////////////////////////////////////////////////////////////////////////////
// Cleanup and Load
static Dz1Error _publish_source_cleanup_data_ref(FILE *dst, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	// list_type
	str_t src_cleanup_data_ref[] = {
		"void CListCtrl$list_type$::CleanupData(void)"_CRLF,
		"{"_CRLF,
		"	m_list = NULL;"_CRLF,
		"}"_CRLF,
		NULL
	};
	if ((*errp = Dz1CodeGen_replacef(dst, src_cleanup_data_ref, list)).code) ERR_OUT(errp);

	return *errp;
}

static Dz1Error _publish_source_load_ref(FILE *dst, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t src_load_ref[] ={
		"BOOL CListCtrlTdoObject::Load($list_type$ *list)"_CRLF,
		"{"_CRLF,
		"	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;"_CRLF,
		""_CRLF,
		"	m_list = list;"_CRLF,
		""_CRLF,
		"	this->DeleteAllItems();"_CRLF,
		"	if ((*errp = m_list->travel(m_list, _ShowToCtrl, (void *)this)).code) ERR_DLG_OUT(errp);"_CRLF,
		""_CRLF,
		"	return errp->code == 0 ? TRUE : FALSE;"_CRLF,
		"}"_CRLF,
		NULL
	};
	if ((*errp = Dz1CodeGen_replacef(dst, src_load_ref, list)).code) ERR_OUT(errp);
	return *errp;
}

static Dz1Error _publish_source_cleanup_data_sto(FILE *dst, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t src_cleanup_data_sto[] = {
		"void CListCtrl$list_type$::CleanupData(void)"_CRLF,
		"{"_CRLF,
		"	$list_type$_delAndSetNull(&m_list);"_CRLF,
		"}"_CRLF,
		NULL
	};
	if ((*errp = Dz1CodeGen_replacef(dst, src_cleanup_data_sto, list)).code) ERR_OUT(errp);
	return *errp;
}

static Dz1Error _publish_source_load_sto(FILE *dst, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t src_load_sto[] = {
		"BOOL CListCtrlTdoObject::Load($list_type$ *list)"_CRLF,
		"{"_CRLF,
		"	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;"_CRLF,
		""_CRLF,
		"	if ((m_list = $list_type$_clone(list, errp)) == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		pthread_cleanup_push($list_type$_delAndSetNull, (void *)&m_list);"_CRLF,
		"		this->DeleteAllItems();"_CRLF,
		"		if ((*errp = Dz1Fifo_travel(m_list, _ShowToCtrl, (void *)this)).code) ERR_DLG_OUT(errp);"_CRLF,
		"		pthread_cleanup_pop(errp->code); // ($list_type$_delAndSetNull, (void *)&m_list);"_CRLF,
		"	}"_CRLF,
		"	return errp->code == 0 ? TRUE : FALSE;"_CRLF,
		"}"_CRLF,
		NULL
	};
	if ((*errp = Dz1CodeGen_replacef(dst, src_load_sto, list)).code) ERR_OUT(errp);
	return *errp;
}

static Dz1Error _publish_source_cleanup_data_and_load(FILE *dst, Dz1CodeGenReplaceList *list, bool_t isRefList)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (isRefList)
	{
		if ((*errp = _publish_source_cleanup_data_ref(dst, list)).code) ERR_OUT(errp);
		else if ((*errp = _publish_source_load_ref(dst, list)).code) ERR_OUT(errp);
	}
	else
	{
		if ((*errp = _publish_source_cleanup_data_sto(dst, list)).code) ERR_OUT(errp);
		else if ((*errp = _publish_source_load_sto(dst, list)).code) ERR_OUT(errp);
	}
	return err;
}
// Cleanup and Load
///////////////////////////////////////////////////////////////////////////////

static Dz1Error _publish_source_show_to_control(FILE *dst, str_t list_type, str_t entry_type, Dz1CodeGenListColumnList *columns, bool_t useUnicode)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	int tab = 0;
	Dz1AATreeCursor *cur = NULL;
	Dz1Thread_ftprintf(dst, tab, "BOOL CListCtrl%s::ShowToCtrl(%s *p)"_CRLF, list_type, entry_type);
	Dz1Thread_ftprintf(dst, tab++, "{"_CRLF);
	Dz1Thread_ftprintf(dst, tab, "Dz1Error err = DZ1_ERROR_INITIALIZER;"_CRLF);
	Dz1Thread_fprintf(dst, _CRLF);
	Dz1Thread_ftprintf(dst, tab, "int nRow = this->GetItemCount();"_CRLF);
	Dz1Thread_fprintf(dst, _CRLF);
	Dz1Thread_ftprintf(dst, tab, "TCHAR temp[1024] = { 0, }, *ptr = NULL;"_CRLF);
	Dz1Thread_ftprintf(dst, tab, "CString str;"_CRLF);
	Dz1Thread_ftprintf(dst, tab, "LVITEM itemData;"_CRLF);
	Dz1Thread_fprintf(dst, _CRLF);
	Dz1Thread_ftprintf(dst, tab, "itemData.lParam		= 1;"_CRLF);
	Dz1Thread_ftprintf(dst, tab, "itemData.iIndent	= 0;"_CRLF);
	Dz1Thread_ftprintf(dst, tab, "itemData.state		= LVIS_SELECTED;"_CRLF);
	Dz1Thread_ftprintf(dst, tab, "itemData.stateMask	= LVIS_SELECTED;"_CRLF);
	Dz1Thread_fprintf(dst, _CRLF);
	Dz1Thread_ftprintf(dst, tab, "itemData.iItem		= nRow;"_CRLF);
	Dz1Thread_ftprintf(dst, tab, "itemData.iImage		= 0;"_CRLF);
	Dz1Thread_fprintf(dst, _CRLF);

	if ((cur = Dz1AATreeCursor_init(columns->storage, errp)) == NULL) ERR_OUT(errp);
	else
	{
		int idx = 0;
		pthread_cleanup_push(Dz1AATreeCursor_delAndSetNull, (void *)&cur);
		if (Dz1AATreeCursor_cond(cur))
		{
			Dz1CodeGenListColumn *member = (Dz1CodeGenListColumn *)Dz1AATreeCursor_data(cur);

			Dz1Thread_ftprintf(dst, tab, "// %s"_CRLF, member->name);
			Dz1Thread_ftprintf(dst, tab, "itemData.iSubItem	= %d;"_CRLF, idx++);
			Dz1Thread_ftprintf(dst, tab, "itemData.mask		= LVIF_TEXT | LVIF_PARAM;"_CRLF);
			Dz1Thread_ftprintf(dst, tab, "// convert variable to temp here"_CRLF);
			Dz1Thread_ftprintf(dst, tab, "itemData.pszText	= temp;"_CRLF);
			Dz1Thread_ftprintf(dst, tab, "itemData.cchTextMax = (u32_t)%s(temp);"_CRLF, useUnicode ? "wcslen" : "strlen");
			Dz1Thread_ftprintf(dst, tab, "nRow = this->InsertItem(&itemData);"_CRLF);
			Dz1Thread_fprintf(dst, _CRLF);

			cur = Dz1AATreeCursor_next(cur);
			while(Dz1AATreeCursor_cond(cur))
			{
				Dz1Thread_ftprintf(dst, tab, "// %s"_CRLF, member->name);
				Dz1Thread_ftprintf(dst, tab, "itemData.iSubItem	= %d;"_CRLF, idx++);
				Dz1Thread_ftprintf(dst, tab, "// convert variable to temp here"_CRLF);
				Dz1Thread_ftprintf(dst, tab, "itemData.pszText	= temp;"_CRLF);
				Dz1Thread_ftprintf(dst, tab, "itemData.cchTextMax = (u32_t)%s(temp);"_CRLF, useUnicode ? "wcslen" : "strlen");
				Dz1Thread_ftprintf(dst, tab, "itemData.mask		= LVIF_TEXT;"_CRLF);
				Dz1Thread_ftprintf(dst, tab, "this->SetItem(&itemData);"_CRLF);
				Dz1Thread_fprintf(dst, _CRLF);

				cur = Dz1AATreeCursor_next(cur);
			}
		}
		pthread_cleanup_pop(1); // (Dz1AATreeCursor_delAndSetNull, (void *)&cur);
	}
	Dz1Thread_ftprintf(dst, tab, "this->SetItemData(nRow, (DWORD)(DWORD_PTR)p);"_CRLF);
	Dz1Thread_fprintf(dst, _CRLF);
	Dz1Thread_ftprintf(dst, tab, "return TRUE;"_CRLF);
	Dz1Thread_ftprintf(dst, --tab, "}"_CRLF);

	return err;
}

static Dz1Error _publish_source_tail(FILE *dst, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t src_tail[] ={
		"$entry_type$ *CListCtrl$list_type$::GetMyItemData(int idx)"_CRLF,
		"{"_CRLF,
		"	$entry_type$ *ret = ($entry_type$ *)(DWORD_PTR)this->GetItemData(idx);"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"$entry_type$ *CListCtrl$list_type$::Find($entry_type$ *key)"_CRLF,
		"{"_CRLF,
		"	return m_list->find(m_list, key);"_CRLF,
		"}"_CRLF,
		NULL
	};
	if ((*errp = Dz1CodeGen_replacef(dst, src_tail, list)).code) ERR_OUT(errp);
	return *errp;
}

static Dz1Error Dz1CodeGenListCtrlSource_gen(str_t path, str_t _name, bool_t isRefList, bool_t useUnicode, Dz1CodeGenReplaceList *list, Dz1CodeGenListColumnList *columns)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	FILE *fp = NULL;
	char name[1024];
	char fn[4096];

	sprintf(name, "%s.c", _name);

	if ((*errp = Dz1FileName_mkFullName(fn, Dz1ArrElCnt(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((fp = fopen(fn, "wb")) == NULL) ERR_OUT(errp);
	else
	{
		str_t list_type = NULL, entry_type = NULL;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if		((list_type = Dz1CodeGenReplaceList_getStr(list, "list_type")) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((entry_type = Dz1CodeGenReplaceList_getStr(list, "entry_type")) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((*errp = _publish_source_front(fp, list)).code) ERR_OUT(errp);
		else if ((*errp = _publish_init_control(fp, list_type, columns)).code) ERR_OUT(errp);
		else if ((*errp = _publish_source_show_to_ctrl_helper(fp, list)).code) ERR_OUT(errp);
		else if ((*errp = _publish_source_cleanup_data_and_load(fp, list, isRefList)).code) ERR_OUT(errp);
		else if ((*errp = _publish_source_show_to_control(fp, list_type, entry_type, columns, useUnicode)).code) ERR_OUT(errp);
		else if ((*errp = _publish_source_tail(fp, list)).code) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

Dz1Error Dz1CodeGenListCtrl_gen(str_t path, str_t _name, bool_t isRefList, bool_t useUnicode,
								str_t list_type, str_t entry_type, str_t tdc_name, str_t parent_class,
								Dz1CodeGenListColumnList *columns)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	char _def_name[1024], *def_name = _mk_define_name(_def_name, tdc_name);

	Dz1CodeGenReplaceEnt arr[] =
	{
		{ "tdc_name", tdc_name },
		{ "def_name", def_name },
		{ "parent_class", parent_class },
		{ "list_type", list_type },
		{ "entry_type", entry_type },
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = NULL;
	
	if ((list = Dz1CodeGenReplaceList_generate(arr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);

		if ((*errp = Dz1CodeGenListCtrlHeader_gen(path, _name, list)).code) ERR_OUT(errp);
		else if ((*errp = Dz1CodeGenListCtrlSource_gen(path, _name, isRefList, useUnicode, list, columns)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return err;
}
