#include "Dz1CodeGen_stub.h"

static Dz1CodeGenSetupEntry stubCodeGenDefault[] =
{
	{ "Type", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry stubCodeGenCodecStream[] =
{
	{ "Type", TRUE },
	{ "Endian", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry stubCodecArgTestGen[] =
{
	{ "Type", TRUE },
	{ "Sub Name", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry stubCodecArgTestUnionGen[] =
{
	{ "Type", TRUE },
	{ "Member Type", TRUE },
	{ "Member Name", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry stubCodecArgMfcEnumComboH[] =
{
	{ "Enum Type", TRUE },
	{ "Not Use", FALSE },
	{ "Not Use", FALSE },
	{ "Class Name", TRUE},
	{ NULL }
};

Dz1CodeGenSetupTable stubCodeGenSetupTable[] =
{
	{ Dz1CodeGenStubType_creation,			stubCodeGenDefault },
	{ Dz1CodeGenStubType_s_api,				stubCodeGenDefault },
	{ Dz1CodeGenStubType_s_codec,			stubCodeGenDefault },
	{ Dz1CodeGenStubType_u_codec,			stubCodeGenDefault },
	{ Dz1CodeGenStubType_v_codec,			stubCodeGenDefault },
	{ Dz1CodeGenStubType_codec_conv,		stubCodeGenDefault },
	{ Dz1CodeGenStubType_codec_test,		stubCodeGenDefault },
	{ Dz1CodeGenStubType_s_stream,			stubCodeGenCodecStream },
	{ Dz1CodeGenStubType_u_stream,			stubCodeGenCodecStream },
	{ Dz1CodeGenStubType_v_stream,			stubCodeGenCodecStream },
	{ Dz1CodeGenStubType_stream_conv,		stubCodeGenDefault },
	{ Dz1CodeGenStubType_stream_test,		stubCodeGenDefault },
	{ Dz1CodeGenStubType_test_gen,			stubCodecArgTestGen },
	{ Dz1CodeGenStubType_test_ugen,			stubCodecArgTestUnionGen },
	{ Dz1CodeGenStubType_mfc_enum_combo_h,	stubCodecArgMfcEnumComboH},
	{ Dz1CodeGenListType_max, NULL }
};

static Dz1Error _stubGen_creation(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = $type$_new(/* args */ errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		pthread_cleanup_push($type$_delAndSetNull, (void *)&ret);"_CRLF,
		""_CRLF,
		"		if (0) { }"_CRLF,
		"		// additional initialize code here"_CRLF,
		"		else ERR_CLEAR(errp);"_CRLF,
		""_CRLF,
		"		pthread_cleanup_pop(errp->code); // ($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_s_api(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ API"_CRLF,
		"$type$ *$type$_new(/* arguments */ Dz1Error *err)"_CRLF,									// New
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = ($type$ *)Dz1Calloc(sizeof($type$), 1, errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		pthread_cleanup_push($type$_delAndSetNull, (void *)&ret);"_CRLF,
		""_CRLF,
		"		if (0) { }"_CRLF,
		"		// additional initialize code here"_CRLF,
		"		else ERR_CLEAR(errp);"_CRLF,
		""_CRLF,
		"		pthread_cleanup_pop(errp->code); // ($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"$type$ *$type$_gen(Dz1Error *err)"_CRLF,													// Gen
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = $type$_new(/* arguments */ errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else ERR_CLEAR(errp);"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"bool_t $type$_copy($type$ *dst, $type$ *src, Dz1Error *err)"_CRLF,							// Copy
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		// Additional copy code here"_CRLF,
		"		ERR_CLEAR(errp);"_CRLF,
		"	}"_CRLF,
		""_CRLF,
		"	return ERR_IS_SUCCESS(errp);"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"$type$ *$type$_clone($type$ *src, Dz1Error *err)"_CRLF,									// Clone
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = ($type$ *)Dz1Calloc(sizeof($type$), 1, errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		pthread_cleanup_push($type$_delAndSetNull, (void *)&ret);"_CRLF,
		""_CRLF,
		"		if ($type$_copy(ret, src, errp) == FALSE) ERR_OUT(errp);"_CRLF,
		"		else ERR_CLEAR(errp);"_CRLF,
		""_CRLF,
		"		pthread_cleanup_pop(errp->code); // ($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"	}"_CRLF,
		""_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"void $type$_purge($type$ *p)"_CRLF,														// Purge
		"{"_CRLF,
		"	if (!p) return;"_CRLF,
		"	// Additional purge code here"_CRLF,
		"}"_CRLF,
		"void $type$_del($type$ *p)"_CRLF,															// Del
		"{"_CRLF,
		"	if (!p) return;"_CRLF,
		"	$type$_purge(p);"_CRLF,
		"	Dz1Free(p);"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"void $type$A_dump($type$ *p, int tab)"_CRLF,												// dumpA
		"{"_CRLF,
		"	if (!p) Dz1ThreadA_printf(\"NULL\\n\");"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		Dz1ThreadA_printf(\"{\\n\"); tab++;"_CRLF,
		"		// Additional print code here"_CRLF,
		"		Dz1ThreadA_tprintf(--tab, \"}\\n\");"_CRLF,
		"	}"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"void $type$A_fdump(FILE *fp, $type$ *p, int tab)"_CRLF,									// fdumpA
		"{"_CRLF,
		"	if (!p) Dz1ThreadA_fprintf(fp, \"NULL\\n\");"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		Dz1ThreadA_fprintf(fp, \"{\\n\"); tab++;"_CRLF,
		"		// Additional print code here"_CRLF,
		"		Dz1ThreadA_ftprintf(fp, --tab, \"}\\n\");"_CRLF,
		"	}"_CRLF,
		"}"_CRLF,
		"#ifndef UNIX_SYSTEM"_CRLF,
		"void $type$W_dump($type$ *p, int tab)"_CRLF,												// dumpW
		"{"_CRLF,
		"	if (!p) Dz1ThreadW_printf(L\"NULL\\n\");"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		Dz1ThreadW_printf(L\"{\\n\"); tab++;"_CRLF,
		"		// Additional print code here"_CRLF,
		"		Dz1ThreadW_tprintf(--tab, L\"}\\n\");"_CRLF,
		"	}"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"void $type$W_fdump(FILE *fp, $type$ *p, int tab)"_CRLF,									// fdumpW
		"{"_CRLF,
		"	if (!p) Dz1ThreadW_fprintf(fp, L\"NULL\\n\");"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		Dz1ThreadW_fprintf(fp, L\"{\\n\"); tab++;"_CRLF,
		"		// Additional print code here"_CRLF,
		"		Dz1ThreadW_ftprintf(fp, --tab, L\"}\\n\");"_CRLF,
		"	}"_CRLF,
		"}"_CRLF,
		"#endif // UNIX_SYSTEM"_CRLF,
		"int $type$_cmp($type$ *a, $type$ *b)"_CRLF,												// cmp
		"{"_CRLF,
		"	int ret = 0;"_CRLF,
		"	if (a == NULL && b == NULL) ret = 0;"_CRLF,
		"	else if (a == NULL) ret = -1;"_CRLF,
		"	else if (b == NULL) ret = 1;"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		// Additional compare code here"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ API"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_s_codec(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ CODEC"_CRLF,
		"static ssize_t $type$_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *src = ($type$ *)_src;"_CRLF,
		"	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		u8_t *cp = dst;"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $type$_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *dst = ($type$ *)_dst;"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		u8_t *cp = src;"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ CODEC"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}


static Dz1Error _stubGen_s_stream(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ CODEC"_CRLF,
		"static ssize_t $type$_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *src = ($type$ *)_src;"_CRLF,
		"	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		// DZ1_STREAM_WRITE(dst, src->some_ptr, len, errp, ret);"_CRLF,
		"		// DZ1_STREAM_WRITE4(dst, src->some_ptr, $endian$, errp, ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $type$_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *dst = ($type$ *)_dst;"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		// DZ1_STREAM_READ(dst->some_ptr, len, src, errp, ret);"_CRLF,
		"		// DZ1_STREAM_READ4(dst->some_ptr, src, $endian$, errp, ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ CODEC"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	str_t endian = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEntry(endian),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}


static Dz1Error _stubGen_u_codec(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ CODEC"_CRLF,
		"// Union Member API Map ---------------------"_CRLF,
		"static Dz1CodecApiMap $type$CodecMap[] = {"_CRLF,
		"//	Dz1CodecApi_STRUCT($type$, __opcode__, __member_type__, __member_name__),"_CRLF,
		"//	Dz1CodecApi_VAR($type$, __opcode__, __api_prefix__, __member_name__),"_CRLF,
		"//	Dz1CodecApi_VOID($type$, __opcode__, __member_name__),"_CRLF,
		"	Dz1CodecApiMapEntry_last"_CRLF,
		"};"_CRLF,
		_CRLF,
		"static ssize_t $type$_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *src = ($type$ *)_src;"_CRLF,
		"	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		u8_t *cp = dst;"_CRLF,
		"		DZ1_CODEC_FUNC(cp, size, ret, Dz1UnionCodec_enc(cp, size, src, param, $type$CodecMap, __op_size__, TRUE, errp), errp);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $type$_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *dst = ($type$ *)_dst;"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		u8_t *cp = src;"_CRLF,
		"		DZ1_CODEC_FUNC(cp, size, ret, Dz1UnionCodec_dec(dst, cp, size, param, $type$CodecMap, __op_size__, TRUE, errp), errp);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ CODEC"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_u_stream(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ CODEC"_CRLF,
		"// Union Member API Map ---------------------"_CRLF,
		"static Dz1StreamIoMap $type$CodecMap[] = {"_CRLF,
		"\t//Dz1StreamIoMap_STRUCT($type$, __opcode__, __member_type__, __member_name__),"_CRLF,
		"\t//Dz1StreamIoMap_VAR($type$, __opcode__, __api_prefix__, __member_name__),"_CRLF,
		"\t//Dz1StreamIoMap_VOID($type$, __opcode__, __member_name__),"_CRLF,
		"	Dz1StreamIoMapEntry_last"_CRLF,
		"};"_CRLF,
		_CRLF,
		"static ssize_t $type$_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *src = ($type$ *)_src;"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_write(dst, src, param, $type$CodecMap, __op_size__, $endian$, errp), errp);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $type$_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *dst = ($type$ *)_dst;"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_read(dst, src, param, $type$CodecMap, __op_size__, $endian$, errp), errp);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ CODEC"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	str_t endian = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEntry(endian),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_v_codec(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ CODEC"_CRLF,
		"static ssize_t $type$_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	if (_src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		$type$ *src = ($type$ *)_src;"_CRLF,
		"		u8_t *cp = dst;"_CRLF,
		"		// value encode code here"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $type$_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *dst = ($type$ *)_dst;"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		u8_t *cp = src;"_CRLF,
		"		// value decode code here"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ CODEC"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_v_stream(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ CODEC"_CRLF,
		"static ssize_t $type$_write(Dz1Stream *dst, void *_src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	if (_src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		$type$ *src = ($type$ *)_src;"_CRLF,
		"		// DZ1_STREAM_WRITE4(dst, (*src), $endian$, errp, ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		_CRLF,
		"static ssize_t $type$_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	ssize_t ret = 0;"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *dst = ($type$ *)_dst;"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		// DZ1_STREAM_READ1(dst, src, $endian$, errp, ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ CODEC"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	str_t endian = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEntry(endian),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_codec_conv(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ Convert Utility"_CRLF,
		"Dz1Binary *$type$_toStream($type$ *src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		ssize_t sz = 0;"_CRLF,
		"		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);"_CRLF,
		"		if ((sz = $type$_enc(NULL, -1, src, param, errp)) < 0) ERR_OUT(errp);"_CRLF,
		"		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = sz), errp)) == NULL) ERR_OUT(errp);"_CRLF,
		"		else if ((sz = $type$_enc(ret->data, ret->size, src, param, errp)) < 0) ERR_OUT(errp);"_CRLF,
		"		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);"_CRLF,
		"		else Dz1Error_set(errp, 0);"_CRLF,
		"		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"$type$ *$type$_toStruct(Dz1Binary *src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = $type$_gen(errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		ssize_t sz = 0;"_CRLF,
		"		pthread_cleanup_push($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"		if ((sz = $type$_dec(ret, src->data, src->size, param, errp)) < 0) ERR_OUT(errp);"_CRLF,
		"		else"_CRLF,
		"		{"_CRLF,
		"			Dz1Error_set(errp, 0);"_CRLF,
		"		}"_CRLF,
		"		pthread_cleanup_pop(errp->code); // ($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ Convert Utility"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_stream_conv(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ Convert Utility"_CRLF,
		"Dz1Error $type$_toStream($type$ *src, Dz1Stream *dst, void *param)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_VAR(errp, err);"_CRLF,
		"	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		ssize_t sz = 0;"_CRLF,
		"		if ((sz = $type$_write(dst, src, param, errp)) < 0) ERR_OUT(errp);"_CRLF,
		"		else Dz1Error_set(errp, 0);"_CRLF,
		"	}"_CRLF,
		"	return err;"_CRLF,
		"}"_CRLF,
		""_CRLF,
		"$type$ *$type$_fromStream(Dz1Stream *src, void *param, Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = $type$_gen(errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		ssize_t sz = 0;"_CRLF,
		"		pthread_cleanup_push($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"		if ((sz = $type$_read(ret, src, param, errp)) < 0) ERR_OUT(errp);"_CRLF,
		"		else Dz1Error_set(errp, 0);"_CRLF,
		"		pthread_cleanup_pop(errp->code); // ($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ Convert Utility"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_codec_test(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ CODEC Test"_CRLF,
		"Dz1Error $type$Codec_test($type$ *src, bool_t verbose)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_VAR(errp, err);"_CRLF,
		""_CRLF,
		"	Dz1Binary *bin = NULL;"_CRLF,
		""_CRLF,
		"	if (verbose)"_CRLF,
		"	{"_CRLF,
		"		Dz1Thread_printf(Dz1Text(\"============================================================\\n\"));"_CRLF,
		"		Dz1Thread_printf(Dz1Text(\"SOURCE =\")); $type$_dump(src, 0);"_CRLF,
		"	}"_CRLF,
		""_CRLF,
		"	if ((bin = $type$_toStream(src, NULL, errp)) == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		$type$ *dec = NULL;"_CRLF,
		"		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);"_CRLF,
		"		if (verbose)"_CRLF,
		"		{"_CRLF,
		"			Dz1Thread_printf(Dz1Text(\"============================================================\\n\"));"_CRLF,
		"			Dz1Thread_printf(Dz1Text(\"STREAM\\n\"));"_CRLF,
		"			Dz1Thread_tprintb(1, bin->data, bin->size, 16);"_CRLF,
		"		}"_CRLF,
		""_CRLF,
		"		if ((dec = $type$_toStruct(bin, NULL, errp)) == NULL) ERR_OUT(errp);"_CRLF,
		"		else"_CRLF,
		"		{"_CRLF,
		"			Dz1Binary *chk = NULL;"_CRLF,
		"			pthread_cleanup_push($type$_delAndSetNull, (void *)&dec);"_CRLF,
		"			if (verbose)"_CRLF,
		"			{"_CRLF,
		"				Dz1Thread_printf(Dz1Text(\"============================================================\\n\"));"_CRLF,
		"				Dz1Thread_printf(Dz1Text(\"DECODED =\")); $type$_dump(dec, 0);"_CRLF,
		"			}"_CRLF,
		""_CRLF,
		"			if ((chk = $type$_toStream(dec, NULL, errp)) == NULL) ERR_OUT(errp);"_CRLF,
		"			else"_CRLF,
		"			{"_CRLF,
		"				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&chk);"_CRLF,
		"				if (bin->size != chk->size)"_CRLF,
		"				{"_CRLF,
		"					Dz1Thread_printf(Dz1Text(\"!!! Different Size\\n\"));"_CRLF,
		"					ERR_SET_OUT(errp, EFAULT);"_CRLF,
		"				}"_CRLF,
		"				else if (memcmp(bin->data, chk->data, bin->size) != 0)"_CRLF,
		"				{"_CRLF,
		"					Dz1Thread_printf(Dz1Text(\"!!! Different Data\\n\"));"_CRLF,
		"					ERR_SET_OUT(errp, EFAULT);"_CRLF,
		"				}"_CRLF,
		"				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&chk);"_CRLF,
		"			}"_CRLF,
		"			pthread_cleanup_pop(1); // ($type$_delAndSetNull, (void *)&dec);"_CRLF,
		"		}"_CRLF,
		"		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);"_CRLF,
		"	}"_CRLF,
		"	return err;"_CRLF,
		"}"_CRLF,
		"// $type$ CODEC Test"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_stream_test(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ CODEC Test"_CRLF,
		"Dz1Error $type$Stream_test($type$ *src, bool_t verbose)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_VAR(errp, err);"_CRLF,
		""_CRLF,
		"	Dz1Stream *stream = Dz1Stream_createElasticBufStream(1024, errp);"_CRLF,
		"	if (stream == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&stream);"_CRLF,
		""_CRLF,
		"		if (verbose)"_CRLF,
		"		{"_CRLF,
		"			Dz1Thread_printf(Dz1Text(\"============================================================\\n\"));"_CRLF,
		"			Dz1Thread_printf(Dz1Text(\"SOURCE = \")); $type$_dump(src, 0);"_CRLF,
		"		}"_CRLF,
		""_CRLF,
		"		if ((*errp = $type$_toStream(src, stream, NULL)).code) ERR_OUT(errp);"_CRLF,
		"		else"_CRLF,
		"		{"_CRLF,
		"			$type$ *dec = NULL;"_CRLF,
		"			if (verbose)"_CRLF,
		"			{"_CRLF,
		"				Dz1Thread_printf(Dz1Text(\"============================================================\\n\"));"_CRLF,
		"				Dz1Thread_printf(Dz1Text(\"STREAM = \"));"_CRLF,
		"				Dz1Stream_dump(stream, 0);"_CRLF,
		"			}"_CRLF,
		""_CRLF,
		"			if ((*errp = Dz1Stream_seek(stream, 0, SEEK_SET)).code) ERR_OUT(errp);" _CRLF,
		"			else if ((dec = $type$_fromStream(stream, NULL, errp)) == NULL) ERR_OUT(errp);"_CRLF
		"			else"_CRLF,
		"			{"_CRLF,
		"				Dz1Stream *chk_stream = NULL;"_CRLF,
		"				$type$ *chk = NULL;"_CRLF,
		"				pthread_cleanup_push($type$_delAndSetNull, (void *)&dec);"_CRLF,
		"				if (verbose)"_CRLF,
		"				{"_CRLF,
		"					Dz1Thread_printf(Dz1Text(\"============================================================\\n\"));"_CRLF,
		"					Dz1Thread_printf(Dz1Text(\"DECODED = \")); $type$_dump(dec, 0);"_CRLF,
		"				}"_CRLF,
		""_CRLF,
		"				if ((chk_stream = Dz1Stream_createElasticBufStream(1024, errp)) == NULL) ERR_OUT(errp);"_CRLF,
		"				else"_CRLF,
		"				{"_CRLF,
		"					pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&chk_stream);"_CRLF,
		"					if ((*errp = $type$_toStream(dec, chk_stream, NULL)).code) ERR_OUT(errp);"_CRLF,
		"					else"_CRLF,
		"					{"_CRLF,
		"						if (Dz1Stream_cmp(stream, chk_stream) != 0)"_CRLF,
		"						{"_CRLF,
		"							Dz1Thread_printf(Dz1Text(\"!!! [Different Data\\n\"));"_CRLF,
		"							ERR_SET_OUT(errp, EFAULT);"_CRLF,
		"						}"_CRLF,
		"					}"_CRLF,
		"					pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void *)&chk_stream);"_CRLF,
		"				}"_CRLF,
		"				pthread_cleanup_pop(1); // ($type$_delAndSetNull, (void *)&dec);"_CRLF,
		"			}"_CRLF,
		"		}"_CRLF,
		"		pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void *)&stream);"_CRLF,
		"	}"_CRLF,
		"	return err;"_CRLF,
		"}"_CRLF,
		"// $type$ CODEC Test"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_test_gen(str_t *dst, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$ Test Gen"_CRLF,
		"static $type$ *$type$_$subname$_gen(Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = $type$_new(/* arguments */ errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		pthread_cleanup_push($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"		if (0) { }"_CRLF,
		"		// generation detail here"_CRLF,
		"		else Dz1Error_set(errp, 0);"_CRLF,
		"		pthread_cleanup_pop(errp->code); // ($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$ Test Gen"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};

	str_t type = va_arg(ap, str_t);
	str_t subname = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEntry(subname),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_test_ugen(str_t *dst, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t base_code[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$.$member_name$ Test Gen"_CRLF,
		"static $type$ *$type$_$member_name$_gen(Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = $type$_new($type$Present_$member_name$, NULL, errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		$member_type$ *p = NULL;"_CRLF,
		"		pthread_cleanup_push($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"		if ((ret->x.$member_name$ = p = $member_type$_new(/* _args_, */ errp)) == NULL) ERR_OUT(errp);"_CRLF,
		"		// generation detail here"_CRLF,
		"		else Dz1Error_set(errp, 0);"_CRLF,
		"		pthread_cleanup_pop(errp->code); // ($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$.$member_name$ Test Gen"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};

	str_t base_code1[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$.$member_name$ Test Gen"_CRLF,
		"static $type$ *$type$_$member_name$_gen(Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = $type$_new($type$Present_$member_name$, NULL, errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else Dz1Error_set(errp, 0);"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$.$member_name$ Test Gen"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};

	str_t base_code2[] =
	{
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		"// $type$.$member_name$ Test Gen"_CRLF,
		"static $type$ *$type$_$member_name$_gen(Dz1Error *err)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_PTR(errp, err);"_CRLF,
		"	$type$ *ret = $type$_new($type$Present_$member_name$, NULL, errp);"_CRLF,
		"	if (ret == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		pthread_cleanup_push($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"		if ((ret->x.$member_name$ = __redirect_func(errp)) == NULL) ERR_OUT(errp);"_CRLF,
		"		else Dz1Error_set(errp, 0);"_CRLF,
		"		pthread_cleanup_pop(errp->code); // ($type$_delAndSetNull, (void *)&ret);"_CRLF,
		"	}"_CRLF,
		"	return ret;"_CRLF,
		"}"_CRLF,
		"// $type$.$member_name$ Test Gen"_CRLF,
		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
		_CRLF,
		NULL
	};
	str_t type = va_arg(ap, str_t);
	str_t member_type = va_arg(ap, str_t);
	str_t member_name = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(type),
		Dz1CodeGenReplaceEntry(member_type),
		Dz1CodeGenReplaceEntry(member_name),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		str_t *syntax = base_code;
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);

		if (strcmp(member_type, "void") == 0) syntax = base_code1;
		else if (strcmp(member_type, "redirect") == 0) syntax = base_code2;

		if (( (*dst) = Dz1CodeGen_replace(syntax, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

static Dz1Error _stubGen_mfc_enum_combo_h(str_t *dst, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t base_code[] =
	{
		"class $class_name$ : public CDz1ComboCtrl<$enum_type$>"_CRLF,
		"{"_CRLF,
		"public:"_CRLF,
		"	$class_name$() : CDz1ComboCtrl($enum_type$_max, $enum_type$Str) { }"_CRLF,
		"	virtual ~$class_name$() { CDz1ComboCtrl::~CDz1ComboCtrl(); }"_CRLF,
		"};"_CRLF,
		NULL
	};
	str_t enum_type = va_arg(ap, str_t);
	str_t dummy1 = va_arg(ap, str_t);
	str_t dummy2 = va_arg(ap, str_t);
	str_t class_name = va_arg(ap, str_t);

	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(enum_type),
		Dz1CodeGenReplaceEntry(class_name),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);

	dummy1 = dummy1;
	dummy2 = dummy2;

	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

Dz1Error Dz1CodeGen_stubGen(str_t *dst, Dz1CodeGenStubType type, ...)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	va_list ap;
	va_start(ap, type);

	switch(type)
	{
	case Dz1CodeGenStubType_creation:
		if ((*errp = _stubGen_creation(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_s_api:
		if ((*errp = _stubGen_s_api(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_s_codec:
		if ((*errp = _stubGen_s_codec(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_u_codec:
		if ((*errp = _stubGen_u_codec(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_v_codec:
		if ((*errp = _stubGen_v_codec(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_codec_conv:
		if ((*errp = _stubGen_codec_conv(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_codec_test:
		if ((*errp = _stubGen_codec_test(dst, ap)).code) ERR_OUT(errp);
		break;

	case Dz1CodeGenStubType_s_stream:
		if ((*errp = _stubGen_s_stream(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_u_stream:
		if ((*errp = _stubGen_u_stream(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_v_stream:
		if ((*errp = _stubGen_v_stream(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_stream_conv:
		if ((*errp = _stubGen_stream_conv(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_stream_test:
		if ((*errp = _stubGen_stream_test(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_test_gen:
		if ((*errp = _stubGen_test_gen(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_test_ugen:
		if ((*errp = _stubGen_test_ugen(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenStubType_mfc_enum_combo_h:
		if ((*errp = _stubGen_mfc_enum_combo_h(dst, ap)).code) ERR_OUT(errp);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return *errp;

	va_end(ap);
}

