#include "Dz1CodeGen_list.h"

static Dz1CodeGenSetupEntry listAddNodeArgSetup[] =
{
	{ "List Type", FALSE },
	{ "List 변수명", TRUE },
	{ "원소의 Type", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry listCodecArgSetup[] =
{
	{ "List Type", TRUE },
	{ "List 변수명", FALSE },
	{ "원소의 Type", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry listStreamArgSetup[] =
{
	{ "List Type", TRUE },
	{ "List 변수명", FALSE },
	{ "원소의 Type", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry listMfcListCtrlCPPArgSetup[] =
{
	{ "List Type", FALSE },
	{ "List 변수명", FALSE },
	{ "원소의 Type", TRUE },
	{ "class 명", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry listMfcListCtrlHArgSetup[] =
{
	{ "List Type", TRUE },
	{ "List 변수명", FALSE },
	{ "원소의 Type", TRUE },
	{ "class 명", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry listMfcListCtrlBaseMethod[] =
{
	{ "List Type", FALSE },
	{ "List 변수명", TRUE },		// list_var
	{ "Method Prefix", TRUE },		// method prefix
	{ "소속 class 명", TRUE },		// class name
	{ NULL }
};

static Dz1CodeGenSetupEntry listMfcListCtrlChanged[] =
{
	{ "List Type", FALSE },
	{ "List 변수명", TRUE },		// list_var
	{ "Method Prefix", TRUE },		// method prefix
	{ "소속 class 명", FALSE },		// class name
	{ NULL }
};

/*
static Dz1CodeGenSetupEntry listMfcListCtrlKeyDown[] =
{
	{ "List Type", FALSE },
	{ "List 변수명", TRUE },		// list_var
	{ "Method Prefix", FALSE },		// method prefix
	{ "소속 class 명", FALSE },		// class name
	{ NULL }
};
*/

static Dz1CodeGenSetupEntry listMfcListCtrlClicked[] =
{
	{ "List Type", FALSE },
	{ "List 변수명", FALSE },		// list_var
	{ "Method Prefix", TRUE },		// method prefix
	{ "소속 class 명", FALSE },		// class name
	{ NULL }
};

Dz1CodeGenSetupTable listCodeGenSetupTable[] =
{
	{ Dz1CodeGenListType_addNode, listAddNodeArgSetup },
	{ Dz1CodeGenListType_codec, listCodecArgSetup },
	{ Dz1CodeGenListType_stream, listStreamArgSetup },
	{ Dz1CodeGenListType_mfc_list_h, listMfcListCtrlHArgSetup },
	{ Dz1CodeGenListType_mfc_list_cpp, listMfcListCtrlCPPArgSetup },
	{ Dz1CodeGenListType_mfc_list_base, listMfcListCtrlBaseMethod },
	{ Dz1CodeGenListType_mfc_list_changed, listMfcListCtrlChanged},
// 	{ Dz1CodeGenListType_mfc_list_keydown, listMfcListCtrlKeyDown},
 	{ Dz1CodeGenListType_mfc_list_clicked, listMfcListCtrlClicked},
	{ Dz1CodeGenListType_max, NULL }
};

static Dz1Error _listGen_addNode(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"\tDZ1_ERROR_SAFE_VAR(errp, err);"_CRLF,
		"\t$element_type$ *node = $element_type$_new(errp);" _CRLF,
		"\tif (node == NULL) ERR_OUT(errp);" _CRLF,
		"\telse" _CRLF,
		"\t{" _CRLF,
		"\t	pthread_cleanup_push($element_type$_delAndSetNull, (void **)&node);"_CRLF,
		"\t	if (0) { }"_CRLF,
		"\t	else if ((*errp = $list_var$->add($list_var$, node)).code) ERR_OUT(errp);"_CRLF,
		"\t	else"_CRLF,
		"\t	{"_CRLF,
		"\t		node = NULL;"_CRLF,
		"\t		Dz1Error_set(errp, 0);"_CRLF,
		"\t	}"_CRLF,
		"\t	pthread_cleanup_pop(1); // ($element_type$_delAndSetNull, (void **)&node);"_CRLF,
		"\t}" _CRLF,
		"\t//return err;" _CRLF,
		NULL
	};
	str_t list_type = va_arg(ap, str_t);
	str_t list_var = va_arg(ap, str_t);
	str_t element_type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		{ "element_type", element_type },
		{ "list_var", list_var },
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);

	list_type = list_type;

	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _listGen_codec(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $list_type$ CODEC"_CRLF,
		"static $list_type$ *$list_type$_gen(Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_DECLARE(errp, err);"_CRLF,
		"	$list_type$ *ret = $list_type$_new(errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static Dz1Error _$list_type$_enc(void *ptr, $element_type$ *p)"_CRLF,
		"{"_CRLF,
		"	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;"_CRLF,
		"	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;"_CRLF,
		"	ssize_t status = $element_type$_enc(arg->cp, arg->size, p, arg->option, errp);"_CRLF,
		"	if (status < 0) ERR_OUT(errp);"_CRLF,
		"	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);"_CRLF,
		"	return err;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $list_type$_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_DECLARE(errp, err);"_CRLF,
		"	$list_type$ *src = ($list_type$ *)_src;"_CRLF,
		"	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		u8_t *cp = dst;"_CRLF,
		"		Dz1ListCodecArg arg;"_CRLF,
		"		u16_t cnt = src->count(src);"_CRLF,
		"		DZ1_ENCODE2(cp, size, cnt, errp, ret);"_CRLF,
		"		Dz1ListCodecArg_init(&arg, cp, size, NULL);"_CRLF,
		"		if ((*errp = src->travel(src, _$list_type$_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);"_CRLF,
		"		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $list_type$_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_DECLARE(errp, err);"_CRLF,
		"	$list_type$ *dst = ($list_type$ *)_dst;"_CRLF,
		"	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		u8_t *cp = src;"_CRLF,
		"		u16_t cnt, i;"_CRLF,
		"		$element_type$ *node = NULL;"_CRLF,
		"		DZ1_DECODE2(&cnt, cp, size, errp, ret);"_CRLF,
		"		for (i = 0; errp->code == 0 && i < cnt; i++)"_CRLF,
		"		{"_CRLF,
		"			if ((node = $element_type$_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);"_CRLF,
		"			else"_CRLF,
		"			{"_CRLF,
		"				ssize_t status = 0;"_CRLF,
		"				pthread_cleanup_push($element_type$_delAndSetNull, (void *)&node);"_CRLF,
		"				if ((status = $element_type$_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }"_CRLF,
		"				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }"_CRLF,
		"				else"_CRLF,
		"				{"_CRLF,
		"					node = NULL;"_CRLF,
		"					Dz1Error_set(errp, 0);"_CRLF,
		"					DZ1_CODEC_APPLY(cp, size, status, ret);"_CRLF,
		"				}"_CRLF,
		"				pthread_cleanup_pop(1); // ($element_type$_delAndSetNull, (void *)&node);"_CRLF,
		"			}"_CRLF,
		"		}"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $list_type$ CODEC"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t list_type = va_arg(ap, str_t);
	str_t list_var = va_arg(ap, str_t);
	str_t element_type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(element_type),
		Dz1CodeGenReplaceEntry(list_type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);

	list_var = list_var;

	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _listGen_stream(str_t *dst, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $list_type$ Stream Read/Write"_CRLF,
		"static $list_type$ *$list_type$_gen(Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_DECLARE(errp, err);"_CRLF,
		"	$list_type$ *ret = $list_type$_new(errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"static Dz1Error _$list_type$_write(void *ptr, $element_type$ *p)"_CRLF,
		"{"_CRLF,
		"	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;"_CRLF,
		"	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;"_CRLF,
		"	ssize_t status = $element_type$_write(arg->stream, p, arg->option, errp);"_CRLF,
		"	if (status < 0) ERR_OUT(errp);"_CRLF,
		"	else arg->ret += status;"_CRLF,
		"	return err;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $list_type$_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_DECLARE(errp, err);"_CRLF,
		"	$list_type$ *src = ($list_type$ *)_src;"_CRLF,
		"	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		Dz1ListStreamArg arg = { dst, 0, param };"_CRLF,
		"		u16_t cnt = src->count(src);"_CRLF,
		"		DZ1_STREAM_WRITE2(dst, cnt, Dz1IOStreamEndian_big, errp, ret);"_CRLF,
		"		if ((*errp = src->travel(src, _$list_type$_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);"_CRLF,
		"		else ret += arg.ret;"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $list_type$_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_DECLARE(errp, err);"_CRLF,
		"	$list_type$ *dst = ($list_type$ *)_dst;"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		u16_t cnt, i;"_CRLF,
		"		$element_type$ *node = NULL;"_CRLF,
		"		DZ1_STREAM_READ2(&cnt, src, Dz1IOStreamEndian_big, errp, ret);"_CRLF,
		"		for (i = 0; errp->code == 0 && i < cnt; i++)"_CRLF,
		"		{"_CRLF,
		"			if ((node = $element_type$_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);"_CRLF,
		"			else"_CRLF,
		"			{"_CRLF,
		"				ssize_t status = 0;"_CRLF,
		"				pthread_cleanup_push($element_type$_delAndSetNull, (void *)&node);"_CRLF,
		"				if ((status = $element_type$_read(node, src, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }"_CRLF,
		"				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }"_CRLF,
		"				else"_CRLF,
		"				{"_CRLF,
		"					node = NULL;"_CRLF,
		"					Dz1Error_set(errp, 0);"_CRLF,
		"					ret += status;"_CRLF,
		"				}"_CRLF,
		"				pthread_cleanup_pop(1); // ($element_type$_delAndSetNull, (void *)&node);"_CRLF,
		"			}"_CRLF,
		"		}"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $list_type$ Stream Read/Write"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t list_type = va_arg(ap, str_t);
	str_t list_var = va_arg(ap, str_t);
	str_t element_type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(element_type),
		Dz1CodeGenReplaceEntry(list_type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);

	list_var = list_var;

	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _listGen_mfcListCPP(str_t *dst, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $class_type$"_CRLF,
		"BOOL $class_type$::OnInitControl()"_CRLF,
		"{"_CRLF,
		"	CListCtrlStyledColumnDesign _design[] ="_CRLF,
		"	{"_CRLF,
		"		//{ _T(\"\"), LVCFMT_RIGHT, CLIST_COLUMN_WITH(1, 8) },"_CRLF,
		"		{ NULL, 0, 0 }"_CRLF,
		"	};"_CRLF,
		"	u32_t cnt = sizeof(_design) / sizeof(CListCtrlStyledColumnDesign);"_CRLF,
		"	return CDz1ListCtrlRW::OnInitControl(_design, cnt);"_CRLF,
		"}"_CRLF,
		_CRLF,
		"void $class_type$::GetFirstColumn(CString &str, $element_type$ *node)"_CRLF,
		"{"_CRLF,
		"	if (node == NULL) str = _T(\"(null)\");"_CRLF,
		"	//else str = node->__string__;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"BOOL $class_type$::SetItemTexts(int nRow, $element_type$ *node)"_CRLF,
		"{"_CRLF,
		"	//Dz1Error err = DZ1_ERROR_INITIALIZER;"_CRLF,
		"	//Dz1Str ptr = NULL;"_CRLF,
		"	int nSub = 0;"_CRLF,
		"	CString str;"_CRLF,
		_CRLF,
		"	// column 0"_CRLF,
		"	GetFirstColumn(str, node);"_CRLF,
		"	SetItemText(nRow, nSub++, str);"_CRLF,

		"	// column 1"_CRLF,
		"	// set str to some data"_CRLF,
		"	// SetItemText(nRow, nSub++, str);"_CRLF,
		_CRLF,
		"	return TRUE;"_CRLF,
		"}"_CRLF,
		"// $class_type$"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		NULL
	};
	str_t list_type = va_arg(ap, str_t);
	str_t list_var = va_arg(ap, str_t);
	str_t element_type = va_arg(ap, str_t);
	str_t class_type = va_arg(ap, str_t);

	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(element_type),
		Dz1CodeGenReplaceEntry(class_type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);

	list_type = list_type;
	list_var = list_var;

	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _listGen_mfcListH(str_t *dst, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $class_type$"_CRLF,
		"class $class_type$ : public CDz1ListCtrlRW<$list_type$, $element_type$>"_CRLF,
		"{"_CRLF,
		"public:"_CRLF,
		"	$class_type$() : CDz1ListCtrlRW<$list_type$, $element_type$>($element_type$_clone, $element_type$_del) { }"_CRLF,
		"	~$class_type$() { CDz1ListCtrlRW::~CDz1ListCtrlRW(); }"_CRLF,
		"	BOOL OnInitControl();"_CRLF,
		_CRLF,
		"protected:"_CRLF,
		"	virtual void	 GetFirstColumn(CString &str, $element_type$ *node);"_CRLF,
		"	virtual BOOL	 SetItemTexts(int nRow, $element_type$ *node);"_CRLF,
		"};"_CRLF,
		"// $class_type$"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		NULL
	};
	str_t list_type = va_arg(ap, str_t);
	str_t list_var = va_arg(ap, str_t);
	str_t element_type = va_arg(ap, str_t);
	str_t class_type = va_arg(ap, str_t);


	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(list_type),
		Dz1CodeGenReplaceEntry(element_type),
		Dz1CodeGenReplaceEntry(class_type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);

	list_var = list_var;

	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _listGen_mfcListBaseMethod(str_t *dst, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $method_prefix$"_CRLF,
		"void $class_name$::$method_prefix$Event(int *_idx, int *_cnt)"_CRLF,
		"{"_CRLF,
		"	int cnt;"_CRLF,
		"	if (_cnt != NULL) cnt = *_cnt;"_CRLF,
		"	else cnt = $list_var$.GetSelectedCount();"_CRLF,
		_CRLF,
		"	int idx;"_CRLF,
		"	if (_idx != NULL) idx = *_idx;"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		POSITION pos = $list_var$.GetFirstSelectedItemPosition();"_CRLF,
		"		idx = $list_var$.GetNextSelectedItem(pos);"_CRLF,
		"	}"_CRLF,
		_CRLF,
		"	if (cnt == 0)"_CRLF,
		"	{"_CRLF,
		"		if (idx != -1) $method_prefix$SelOne(idx);"_CRLF,
		"		else $method_prefix$SelNone();"_CRLF,
		"	}"_CRLF,
		"	else if (cnt == 1) $method_prefix$SelOne(idx);"_CRLF,
		"	else $method_prefix$SelMany(idx, cnt);"_CRLF,
		"}"_CRLF,
		_CRLF,
		"void $class_name$::$method_prefix$SelNone()"_CRLF,
		"{"_CRLF,
		"	// no item Selected Implementation"_CRLF,
		"}"_CRLF,
		_CRLF,
		"void $class_name$::$method_prefix$SelOne(int idx)"_CRLF,
		"{"_CRLF,
		"	// Only one item Selected Implementation"_CRLF,
		"}"_CRLF,
		_CRLF,
		"void $class_name$::$method_prefix$SelMany(int idx, int cnt)"_CRLF,
		"{"_CRLF,
		"	// many item Selected Implementation"_CRLF,
		"}"_CRLF,
		"// $method_prefix$"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		NULL
	};

	str_t arg_dummy = va_arg(ap, str_t);
	str_t list_var = va_arg(ap, str_t);
	str_t method_prefix = va_arg(ap, str_t);
	str_t class_name = va_arg(ap, str_t);

	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(list_var),
		Dz1CodeGenReplaceEntry(method_prefix),
		Dz1CodeGenReplaceEntry(class_name),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);

	arg_dummy = arg_dummy;

	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _listGen_mfcListChanged(str_t *dst, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t base_code[] =
	{
		"	if ((pNMLV->uNewState & (LVIS_FOCUSED | LVIS_SELECTED)) == (LVIS_FOCUSED | LVIS_SELECTED))"_CRLF,
		"		$method_prefix$Event(&pNMLV->iItem);"_CRLF,
		NULL
	};

	str_t arg_dummy0 = va_arg(ap, str_t);
	str_t list_var = va_arg(ap, str_t);
	str_t method_prefix = va_arg(ap, str_t);
	str_t arg_dummy1 = va_arg(ap, str_t);

	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(list_var),
		Dz1CodeGenReplaceEntry(method_prefix),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);

	arg_dummy0 = arg_dummy0;
	arg_dummy1 = arg_dummy1;

	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

// static Dz1Error _listGen_mfcListKeyDown(str_t *dst, va_list ap)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	str_t base_code[] =
// 	{
// 		"	POSITION pos;"_CRLF,
// 		"	switch(pLVKeyDow->wVKey)"_CRLF,
// 		"	{"_CRLF,
// 		"	case VK_UP:"_CRLF,
// 		"	case VK_DOWN:"_CRLF,
// 		"		pos = $list_var$.GetFirstSelectedItemPosition();"_CRLF,
// 		"		$list_var$_idx = $list_var$.GetNextSelectedItem(pos);"_CRLF,
// 		"		$list_var$_key = TRUE;"_CRLF,
// 		"		break;"_CRLF,
// 		"	// Other key code handling here"_CRLF,
// 		"	}"_CRLF,
// 		NULL
// 	};
// 
// 	str_t arg_dummy0 = va_arg(ap, str_t);
// 	str_t list_var = va_arg(ap, str_t);
// 	str_t arg_dummy1 = va_arg(ap, str_t);
// 	str_t arg_dummy2 = va_arg(ap, str_t);
// 
// 	Dz1CodeGenReplaceEnt arr[] =
// 	{
// 		Dz1CodeGenReplaceEntry(list_var),
// 		Dz1CodeGenReplaceEnt_last
// 	};
// 
// 	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_gen(arr, errp);
// 	if (list == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
// 		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
// 		pthread_cleanup_pop(1);(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
// 	}
// 	return *errp;
// }

static Dz1Error _listGen_mfcListClicked(str_t *dst, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t base_code[] =
	{
		"	if (pNMItemActivate->iItem == -1) $mothod_prefix$SelNone();"_CRLF,
		NULL
	};

	str_t arg_dummy0 = va_arg(ap, str_t);
	str_t arg_dummy1 = va_arg(ap, str_t);
	str_t mothod_prefix = va_arg(ap, str_t);
	str_t arg_dummy2 = va_arg(ap, str_t);

	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(mothod_prefix),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);

	arg_dummy0 = arg_dummy0;
	arg_dummy1 = arg_dummy1;
	arg_dummy2 = arg_dummy2;

	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

Dz1Error Dz1CodeGen_listGen(str_t *dst, Dz1CodeGenListType type, ...)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	va_list ap;
	va_start(ap, type);

	switch(type)
	{
	case Dz1CodeGenListType_addNode:
		if ((*errp = _listGen_addNode(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenListType_codec:
		if ((*errp = _listGen_codec(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenListType_stream:
		if ((*errp = _listGen_stream(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenListType_mfc_list_cpp:
		if ((*errp = _listGen_mfcListCPP(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenListType_mfc_list_h:
		if ((*errp = _listGen_mfcListH(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenListType_mfc_list_base:
		if ((*errp = _listGen_mfcListBaseMethod(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenListType_mfc_list_changed:
		if ((*errp = _listGen_mfcListChanged(dst, ap)).code) ERR_OUT(errp);
		break;
// 	case Dz1CodeGenListType_mfc_list_keydown:
// 		if ((*errp = _listGen_mfcListKeyDown(dst, ap)).code) ERR_OUT(errp);
// 		break;
	case Dz1CodeGenListType_mfc_list_clicked:
		if ((*errp = _listGen_mfcListClicked(dst, ap)).code) ERR_OUT(errp);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return *errp;

	va_end(ap);
}

