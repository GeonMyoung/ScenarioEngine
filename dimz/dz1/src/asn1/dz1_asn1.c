#include <dz1_asn1.h>

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Type
static struct Dz1Asn1TypeMapA
{
	str_t str;
	Dz1Asn1Type v;
} Dz1Asn1TypeMapA[] =
{
	{ (char *)"eoc", Dz1Asn1Type_eoc },
	{ (char *)"boolean", Dz1Asn1Type_boolean },
	{ (char *)"integer", Dz1Asn1Type_integer },
	{ (char *)"bit_str", Dz1Asn1Type_bit_str },
	{ (char *)"octet_str", Dz1Asn1Type_octet_str },
	{ (char *)"nul", Dz1Asn1Type_nul },
	{ (char *)"oid", Dz1Asn1Type_oid },
	{ (char *)"obj_descr", Dz1Asn1Type_obj_descr },
	{ (char *)"external", Dz1Asn1Type_external },
	{ (char *)"realnum", Dz1Asn1Type_realnum },
	{ (char *)"enumerated", Dz1Asn1Type_enumerated },
	{ (char *)"embPDV", Dz1Asn1Type_embPDV },
	{ (char *)"utf8str", Dz1Asn1Type_utf8str },
	{ (char *)"reloid", Dz1Asn1Type_reloid },
	{ (char *)"time", Dz1Asn1Type_time },
	{ (char *)"seq", Dz1Asn1Type_seq },
	{ (char *)"set", Dz1Asn1Type_set },
	{ (char *)"digit_str", Dz1Asn1Type_digit_str },
	{ (char *)"print_str", Dz1Asn1Type_print_str },
	{ (char *)"teletex_str", Dz1Asn1Type_teletex_str },
	{ (char *)"videotex_str", Dz1Asn1Type_videotex_str },
	{ (char *)"ia5_str", Dz1Asn1Type_ia5_str },
	{ (char *)"utc_time", Dz1Asn1Type_utc_time },
	{ (char *)"general_time", Dz1Asn1Type_general_time },
	{ (char *)"graphic_str", Dz1Asn1Type_graphic_str },
	{ (char *)"visible_str", Dz1Asn1Type_visible_str },
	{ (char *)"general_str", Dz1Asn1Type_general_str },
	{ (char *)"uni_str", Dz1Asn1Type_uni_str },
	{ (char *)"char_str", Dz1Asn1Type_char_str },
	{ (char *)"bmp_str", Dz1Asn1Type_bmp_str },
	{ (char *)"date", Dz1Asn1Type_date },
	{ (char *)"time_of_day", Dz1Asn1Type_time_of_day },
	{ (char *)"date_time", Dz1Asn1Type_date_time },
	{ (char *)"duration", Dz1Asn1Type_duration },
	{ NULL, Dz1Asn1Type_max }
};

str_t Dz1Asn1TypeStrA(Dz1Asn1Type v)
{
	struct Dz1Asn1TypeMapA *i = NULL;
	for (i = Dz1Asn1TypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1Type Dz1Asn1TypeFromStrA(str_t str)
{
	struct Dz1Asn1TypeMapA *i = NULL;
	for (i = Dz1Asn1TypeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1Asn1Type_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1TypeMapW
{
	wstr_t str;
	Dz1Asn1Type v;
} Dz1Asn1TypeMapW[] =
{
	{ (wchar_t *)L"eoc", Dz1Asn1Type_eoc },
	{ (wchar_t *)L"boolean", Dz1Asn1Type_boolean },
	{ (wchar_t *)L"integer", Dz1Asn1Type_integer },
	{ (wchar_t *)L"bit_str", Dz1Asn1Type_bit_str },
	{ (wchar_t *)L"octet_str", Dz1Asn1Type_octet_str },
	{ (wchar_t *)L"nul", Dz1Asn1Type_nul },
	{ (wchar_t *)L"oid", Dz1Asn1Type_oid },
	{ (wchar_t *)L"obj_descr", Dz1Asn1Type_obj_descr },
	{ (wchar_t *)L"external", Dz1Asn1Type_external },
	{ (wchar_t *)L"realnum", Dz1Asn1Type_realnum },
	{ (wchar_t *)L"enumerated", Dz1Asn1Type_enumerated },
	{ (wchar_t *)L"embPDV", Dz1Asn1Type_embPDV },
	{ (wchar_t *)L"utf8str", Dz1Asn1Type_utf8str },
	{ (wchar_t *)L"reloid", Dz1Asn1Type_reloid },
	{ (wchar_t *)L"time", Dz1Asn1Type_time },
	{ (wchar_t *)L"seq", Dz1Asn1Type_seq },
	{ (wchar_t *)L"set", Dz1Asn1Type_set },
	{ (wchar_t *)L"digit_str", Dz1Asn1Type_digit_str },
	{ (wchar_t *)L"print_str", Dz1Asn1Type_print_str },
	{ (wchar_t *)L"teletex_str", Dz1Asn1Type_teletex_str },
	{ (wchar_t *)L"videotex_str", Dz1Asn1Type_videotex_str },
	{ (wchar_t *)L"ia5_str", Dz1Asn1Type_ia5_str },
	{ (wchar_t *)L"utc_time", Dz1Asn1Type_utc_time },
	{ (wchar_t *)L"general_time", Dz1Asn1Type_general_time },
	{ (wchar_t *)L"graphic_str", Dz1Asn1Type_graphic_str },
	{ (wchar_t *)L"visible_str", Dz1Asn1Type_visible_str },
	{ (wchar_t *)L"general_str", Dz1Asn1Type_general_str },
	{ (wchar_t *)L"uni_str", Dz1Asn1Type_uni_str },
	{ (wchar_t *)L"char_str", Dz1Asn1Type_char_str },
	{ (wchar_t *)L"bmp_str", Dz1Asn1Type_bmp_str },
	{ (wchar_t *)L"date", Dz1Asn1Type_date },
	{ (wchar_t *)L"time_of_day", Dz1Asn1Type_time_of_day },
	{ (wchar_t *)L"date_time", Dz1Asn1Type_date_time },
	{ (wchar_t *)L"duration", Dz1Asn1Type_duration },
	{ NULL, Dz1Asn1Type_max }
};

wstr_t Dz1Asn1TypeStrW(Dz1Asn1Type v)
{
	struct Dz1Asn1TypeMapW *i = NULL;
	for (i = Dz1Asn1TypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1Type Dz1Asn1TypeFromStrW(wstr_t str)
{
	struct Dz1Asn1TypeMapW *i = NULL;
	for (i = Dz1Asn1TypeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1Asn1Type_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1Type *Dz1Asn1Type_new(Dz1Asn1Type *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1Type *__internal_ret = (Dz1Asn1Type *)Dz1Calloc(sizeof(Dz1Asn1Type), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1Asn1TypeA_dump(Dz1Asn1Type *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1TypeStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1TypeW_dump(Dz1Asn1Type *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1TypeStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1Asn1Type
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Primitive API
static bool_t _is_primitive_size(size_t sz)
{
	switch(sz)
	{
	case 1: case 2: case 4: case 8: return TRUE;
	default: return FALSE;
	}
}

void *Dz1Asn1Primitive_gen(size_t sz, Dz1Error *err, const char *__file, int __line)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	if (_is_primitive_size(sz) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = _Dz1Calloc(sz, 1, errp, __file, __line)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void *Dz1Asn1Primitive_clone(void *ptr, size_t sz, Dz1Error *err, const char *__file, int __line)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	if (ptr == NULL || _is_primitive_size(sz) == FALSE)
		ERR_SET_OUT(errp, EINVAL);
	else if ((ret = _Dz1Calloc(sz, 1, errp, __file, __line)) == NULL) ERR_OUT(errp);
	else
	{
		memcpy(ret, ptr, sz);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static int Dz1Asn1Primitive_s_cmp(void *a, void *b, size_t sz)
{
	switch(sz)
	{
	case 1: return Dz1s8_cmp((s8_t *)a, (s8_t *)b);
	case 2: return Dz1s16_cmp((s16_t *)a, (s16_t *)b);
	case 4: return Dz1s32_cmp((s32_t *)a, (s32_t *)b);
	case 8: return Dz1s64_cmp((s64_t *)a, (s64_t *)b);
	default:
		if (a == NULL && b == NULL) return 0;
		else if (a == NULL) return -1;
		else if (b == NULL) return 1;
		else return memcmp(a, b, sz);
	}
}

static int Dz1Asn1Primitive_r_cmp(void *a, void *b, size_t sz)
{
	switch(sz)
	{
	case 4: return Dz1Real32_cmp((real32_t *)a, (real32_t *)b);
	case 8: return Dz1Real64_cmp((real64_t *)a, (real64_t *)b);
	default:
		if (a == NULL && b == NULL) return 0;
		else if (a == NULL) return -1;
		else if (b == NULL) return 1;
		else return memcmp(a, b, sz);
	}
}
/*
static int Dz1Asn1Primitive_u_cmp(void *a, void *b, size_t sz)
{
	switch(sz)
	{
	case 1: return Dz1u8_cmp((u8_t *)a,	  (u8_t *)b);
	case 2: return Dz1u16_cmp((u16_t *)a, (u16_t *)b);
	case 4: return Dz1u32_cmp((u32_t *)a, (u32_t *)b);
	case 8: return Dz1u64_cmp((u64_t *)a, (u64_t *)b);
	default: return -1;
	}
}
*/

int Dz1Asn1Primitive_cmp(void *a, void *b, size_t sz, bool_t is_real)
{
	if (is_real) return Dz1Asn1Primitive_r_cmp(a, b, sz);
	else return Dz1Asn1Primitive_s_cmp(a, b, sz);
}
// Primitive API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// REAL
void Dz1Asn1RealA_dump(Dz1Asn1Real *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		u64_t temp = *(u64_t *)p;
		int sign = temp & DZ1UINT64(0x8000000000000000) ? 1 : 0;
		s32_t exponent = (s32_t)((temp >> 52) & 0x7FF) - 1023;
		u64_t fraction = temp & DZ1UINT64(0xFFFFFFFFFFFFF);

		Dz1ThreadA_printf("%lf(%d)(%c"DZ1_FMT64XF_A(013)")\n", *p, exponent, sign ? '-' : '+', fraction);
	}
}

void Dz1Asn1RealA_fdump(FILE *fp, Dz1Asn1Real *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		u64_t temp = *(u64_t *)p;
		int sign = temp & DZ1UINT64(0x8000000000000000) ? 1 : 0;
		s32_t exponent = (s32_t)((temp >> 52) & 0x7FF) - 1023;
		u64_t fraction = temp & DZ1UINT64(0xFFFFFFFFFFFFF);

		Dz1ThreadA_fprintf(fp, "%lf(%d)(%c"DZ1_FMT64XF_A(013)")\n", *p, exponent, sign ? '-' : '+', fraction);
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1RealW_dump(Dz1Asn1Real *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		u64_t temp = *(u64_t *)p;
		int sign = temp & DZ1UINT64(0x8000000000000000) ? 1 : 0;
		s32_t exponent = (s32_t)((temp >> 52) & 0x7FF) - 1023;
		u64_t fraction = temp & DZ1UINT64(0xFFFFFFFFFFFFF);

		Dz1ThreadW_printf(L"%lf(%d)(%c" DZ1_FMT64XF_W(013) L")\n", *p, exponent, sign ? L'-' : L'+', fraction);
	}
}

void Dz1Asn1RealW_fdump(FILE *fp, Dz1Asn1Real *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		u64_t temp = *(u64_t *)p;
		int sign = temp & DZ1UINT64(0x8000000000000000) ? 1 : 0;
		s32_t exponent = (s32_t)((temp >> 52) & 0x7FF) - 1023;
		u64_t fraction = temp & DZ1UINT64(0xFFFFFFFFFFFFF);

		Dz1ThreadW_fprintf(fp, L"%lf(%d)(%c" DZ1_FMT64XF_W(013) L")\n", *p, exponent, sign ? L'-' : L'+', fraction);
	}
}
#endif
// REAL
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Custom Data Handling Structure
Dz1Asn1Custom *__Dz1Asn1Custom_new(void *data, Dz1CloneFunc _clone, Dz1DelFunc _del, 
									Dz1DumpFunc _dumpA, Dz1FDumpFunc _fdumpA,
#ifndef UNIX_SYSTEM
									Dz1DumpFunc _dumpW, Dz1FDumpFunc _fdumpW,
#endif
									Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Custom *ret = NULL;
	if ((ret = (Dz1Asn1Custom *)Dz1Calloc(sizeof(Dz1Asn1Custom), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ret->data = data;
		ret->data_clone = _clone;
		ret->data_del = _del;

		ret->data_dumpA = _dumpA;
		ret->data_fdumpA = _fdumpA;
#ifndef UNIX_SYSTEM // modified by gm 20230601 - case wide character
		ret->data_dumpW = _dumpW;
		ret->data_fdumpW = _fdumpW;
#endif // UNIX_SYSTEM
		Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1Asn1Custom *Dz1Asn1Custom_clone(Dz1Asn1Custom *src, Dz1Error *err)
{
	Dz1Asn1Custom *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1Asn1Custom *)Dz1Calloc(sizeof(Dz1Asn1Custom), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1Custom_delAndSetNull, (void *)&ret);

		ret->data_del = src->data_del;
		ret->data_clone = src->data_clone;
		ret->data_dumpA = src->data_dumpA;
		ret->data_fdumpA = src->data_fdumpA;
		ret->data_dumpW = src->data_dumpW;
		ret->data_fdumpW = src->data_fdumpW;

		if (ret->data_clone != NULL)
		{
			if (src->data != NULL && (ret->data = ret->data_clone(src->data, errp)) == NULL) ERR_OUT(errp);
			else ERR_CLEAR(errp);
		}
		else
		{
			ret->data = src->data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1Custom_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1Custom_del(Dz1Asn1Custom *p)
{
	if (p == NULL) return;
	if (p->data_del != NULL && p->data != NULL) p->data_del(p->data);
	p->data = NULL;
	Dz1Free(p);
}

void Dz1Asn1CustomA_dump(Dz1Asn1Custom *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("{\n"); tab++;

	if (p->data == NULL) Dz1ThreadA_tprintf(tab, "data = NULL\n");
	else if (p->data_dumpA == NULL) Dz1ThreadA_tprintf(tab, "data = %p\n", p->data);
	else { Dz1ThreadA_tprintf(tab, "data = "); p->data_dumpA(p->data, tab); }

	Dz1ThreadA_tprintf(--tab, "}\n");
}
void Dz1Asn1CustomA_fdump(FILE *fp, Dz1Asn1Custom *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	Dz1ThreadA_fprintf(fp, "{\n"); tab++;

	if (p->data == NULL) Dz1ThreadA_ftprintf(fp, tab, "data = NULL\n");
	else if (p->data_fdumpA == NULL) Dz1ThreadA_ftprintf(fp, tab, "data = %p\n", p->data);
	else { Dz1ThreadA_ftprintf(fp, tab, "data = "); p->data_fdumpA(fp, p->data, tab); }

	Dz1ThreadA_ftprintf(fp, --tab, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1Asn1CustomW_dump(Dz1Asn1Custom *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"{\n"); tab++;

	if (p->data == NULL) Dz1ThreadW_tprintf(tab, L"data = NULL\n");
	else if (p->data_dumpW == NULL) Dz1ThreadW_tprintf(tab, L"data = %p\n", p->data);
	else { Dz1ThreadW_tprintf(tab, L"data = "); p->data_dumpW(p->data, tab); }

	Dz1ThreadW_tprintf(--tab, L"}\n");
}
void Dz1Asn1CustomW_fdump(FILE *fp, Dz1Asn1Custom *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	Dz1ThreadW_fprintf(fp, L"{\n"); tab++;

	if (p->data == NULL) Dz1ThreadW_ftprintf(fp, tab, L"data = NULL\n");
	else if (p->data_fdumpW == NULL) Dz1ThreadW_ftprintf(fp, tab, L"data = %p\n", p->data);
	else { Dz1ThreadW_ftprintf(fp, tab, L"data = "); p->data_fdumpW(fp, p->data, tab); }

	Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
}
#endif // UNIX_SYSTEM
// ASN.1 Custom Data Handling Structure
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 CODEC
static struct Codec2OIDMAP
{
	Dz1Asn1Codec codec;
	str_t		 strOID;
} Codec2OIDMAP[] = 
{
	{ Dz1Asn1Codec_ber, (str_t)"2.1.1" },
	{ Dz1Asn1Codec_aper, (str_t)"2.1.3.0.0" },
	{ Dz1Asn1Codec_uper, (str_t)"2.1.3.0.1" },
	{ Dz1Asn1Codec_xer, (str_t)"2.1.5.0" },
	{ Dz1Asn1Codec_cxer, (str_t)"2.1.5.1" },
	{ Dz1Asn1Codec_unknown, NULL }
};

Dz1Asn1OID *Dz1Asn1Codec2OID(Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1OID *ret = NULL;
	str_t strOID = NULL;

	struct Codec2OIDMAP *i;
	for (i = Codec2OIDMAP; i->strOID; i++) if (codec == i->codec) strOID = i->strOID;

	if (strOID == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1Asn1OIDA_newFromStr(strOID, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static struct CodecStrMapA
{
	str_t name;
	Dz1Asn1Codec codec;
} CodecStrMapA[] =
{
	{ (str_t)"BER", Dz1Asn1Codec_ber },
	{ (str_t)"APER", Dz1Asn1Codec_aper },
	{ (str_t)"UPER", Dz1Asn1Codec_uper },
	{ (str_t)"XER", Dz1Asn1Codec_xer },
	{ (str_t)"CXER", Dz1Asn1Codec_cxer },
	{ (str_t)"UNKNOWN", Dz1Asn1Codec_unknown }
};

static struct CodecStrMapW
{
	wstr_t name;
	Dz1Asn1Codec codec;
} CodecStrMapW[] =
{
	{ (wstr_t)L"BER", Dz1Asn1Codec_ber },
	{ (wstr_t)L"APER", Dz1Asn1Codec_aper },
	{ (wstr_t)L"UPER", Dz1Asn1Codec_uper },
	{ (wstr_t)L"XER", Dz1Asn1Codec_xer },
	{ (wstr_t)L"CXER", Dz1Asn1Codec_cxer },
	{ (wstr_t)L"UNKNOWN", Dz1Asn1Codec_unknown }
};

str_t Dz1Asn1CodecStrA(Dz1Asn1Codec codec)
{
	struct CodecStrMapA *i;
	for (i = CodecStrMapA; i->codec != Dz1Asn1Codec_unknown; i++)
		if (codec == i->codec) break;
	return i->name;
}

wstr_t Dz1Asn1CodecStrW(Dz1Asn1Codec codec)
{
	struct CodecStrMapW *i;
	for (i = CodecStrMapW; i->codec != Dz1Asn1Codec_unknown; i++)
		if (codec == i->codec) break;
	return i->name;
}

Dz1Asn1Codec Dz1Asn1CodecFromStrA(str_t n)
{
	struct CodecStrMapA *i;
	for (i = CodecStrMapA; i->codec != Dz1Asn1Codec_unknown; i++)
		if (strcmp(i->name, n) == 0) break;
	return i->codec;
}

Dz1Asn1Codec Dz1Asn1CodecFromStrW(wstr_t n)
{
	struct CodecStrMapW *i;
	for (i = CodecStrMapW; i->codec != Dz1Asn1Codec_unknown; i++)
		if (wcscmp(i->name, n) == 0) break;
	return i->codec;
}
// ASN.1 CODEC
///////////////////////////////////////////////////////////////////////////////

