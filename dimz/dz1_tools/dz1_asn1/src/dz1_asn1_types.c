#include "dz1_asn1_codec.h"
#include "dz1_asn1_types.h"

///////////////////////////////////////////////////////////////////////////////
// TDC Support
int Dz1Asn1MetaDataRange_cmp(Dz1Asn1MetaDataRange *a, Dz1Asn1MetaDataRange *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else
	{
		int status = 0;
		if ((status = Dz1Asn1Int_cmp(&a->low, &b->low)) != 0) return status;
		else if ((status = Dz1Asn1Int_cmp(&a->high, &b->high)) != 0) return status;
		return status;
	}
}

int Dz1Asn1MetaDataRealRange_cmp(Dz1Asn1MetaDataRealRange *a, Dz1Asn1MetaDataRealRange *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else
	{
		int status = 0;
		if ((status = Dz1Asn1Real_cmp(&a->low, &b->low)) != 0) return status;
		else if ((status = Dz1Asn1Real_cmp(&a->high, &b->high)) != 0) return status;
		return status;
	}
}
// TDC Support
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Tag dump
typedef struct Dz1Asn1TagClassShortStrMapA
{
	Dz1Asn1TagClass			cls;
	str_t						str;
} Dz1Asn1TagClassShortStrMapA;
static Dz1Asn1TagClassShortStrMapA dz1Asn1BerTagClassShortStrMapA[] =
{
	{ Dz1Asn1TagClass_universal,			"UNI" },
	{ Dz1Asn1TagClass_application,		"APP" },
	{ Dz1Asn1TagClass_context_specific,	"CTX" },
	{ Dz1Asn1TagClass_privated,			"PVT" },
	{ Dz1Asn1TagClass_max,				"???" },
};

static str_t Dz1Asn1TagClassShortStrA(Dz1Asn1TagClass v)
{
	if (v >= 0 && v < Dz1Asn1TagClass_max) return dz1Asn1BerTagClassShortStrMapA[v].str;
	else return dz1Asn1BerTagClassShortStrMapA[Dz1Asn1TagClass_max].str;
}

str_t Dz1Asn1TagA_printable(Dz1Asn1Tag *p, char *buf, size_t buf_sz)
{
	if (p == NULL) strncpy(buf, "NULL", buf_sz);
	else if (Dz1Asn1Tag_isVoid(p)) strncpy(buf, "Undefined", buf_sz);
	else
	{
		ssize_t sz = snprintf(buf, buf_sz, "%s-%s-" DZ1_FMT64_A, Dz1Asn1TagClassShortStrA(p->cls), Dz1Asn1TagFlagStrA(p->flag), p->numb);
		if (sz >= buf_sz) buf[buf_sz - 1] = 0;
	}
	return buf;
}

void Dz1Asn1TagA_dump(Dz1Asn1Tag *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	else if (Dz1Asn1Tag_isVoid(p)) Dz1ThreadA_printf("Undefined\n");
	else Dz1ThreadA_printf("%s-%s-" DZ1_FMT64_A "\n", Dz1Asn1TagClassShortStrA(p->cls), Dz1Asn1TagFlagStrA(p->flag), p->numb);
}

void Dz1Asn1TagA_fdump(FILE *fp, Dz1Asn1Tag *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	else if (Dz1Asn1Tag_isVoid(p)) Dz1ThreadA_fprintf(fp, "Undefined\n");
	else Dz1ThreadA_fprintf(fp, "%s-%s-" DZ1_FMT64_A "\n", Dz1Asn1TagClassShortStrA(p->cls), Dz1Asn1TagFlagStrA(p->flag), p->numb);
}

#ifndef UNIX_SYSTEM
typedef struct Dz1Asn1TagClassShortStrMapW
{
	Dz1Asn1TagClass			cls;
	wstr_t						str;
} Dz1Asn1TagClassShortStrMapW;
static Dz1Asn1TagClassShortStrMapW dz1Asn1BerTagClassShortStrMapW[] =
{
	{ Dz1Asn1TagClass_universal,			L"UNI" },
	{ Dz1Asn1TagClass_application,		L"APP" },
	{ Dz1Asn1TagClass_context_specific,	L"CTX" },
	{ Dz1Asn1TagClass_privated,			L"PVT" },
	{ Dz1Asn1TagClass_max,				NULL },
};

static wstr_t Dz1Asn1TagClassShortStrW(Dz1Asn1TagClass v)
{
	if (v >= 0 && v < Dz1Asn1TagClass_max) return dz1Asn1BerTagClassShortStrMapW[v].str;
	else return dz1Asn1BerTagClassShortStrMapW[Dz1Asn1TagClass_max].str;
}

wstr_t Dz1Asn1TagW_printable(Dz1Asn1Tag *p, wchar_t *buf, size_t buf_sz)
{
	if (p == NULL) wcsncpy(buf, L"NULL", buf_sz);
	else if (Dz1Asn1Tag_isVoid) wcsncpy(buf, L"Undefined", buf_sz);
	else
	{
		ssize_t sz = _snwprintf(buf, buf_sz, L"%s-%s-" DZ1_FMT64_W, Dz1Asn1TagClassShortStrW(p->cls), Dz1Asn1TagFlagStrW(p->flag), p->numb);
		if (sz >= buf_sz) buf[buf_sz - 1] = 0;
	}
	return buf;
}

void Dz1Asn1TagW_dump(Dz1Asn1Tag *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	else if (Dz1Asn1Tag_isVoid(p)) Dz1ThreadW_printf(L"Undefined\n");
	else Dz1ThreadW_printf(L"%s-%s-" DZ1_FMT64_W L"\n", Dz1Asn1TagClassShortStrW(p->cls), Dz1Asn1TagFlagStrW(p->flag), p->numb);
}

void Dz1Asn1TagW_fdump(FILE *fp, Dz1Asn1Tag *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	else if (Dz1Asn1Tag_isVoid(p)) Dz1ThreadW_fprintf(fp, L"Undefined\n");
	else Dz1ThreadW_fprintf(fp, L"%s-%s-" DZ1_FMT64_W L"\n", Dz1Asn1TagClassShortStrW(p->cls), Dz1Asn1TagFlagStrW(p->flag), p->numb);
}
#endif
// Dz1Asn1Tag dump
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Tag Utility
bool_t Dz1Asn1Tag_isVoid(Dz1Asn1Tag *p)
{
	bool_t ret = TRUE;
	if (p != NULL)
	{
		if (p->cls != Dz1Asn1TagClass_max &&
			p->flag != Dz1Asn1TagFlag_max &&
			p->numb != (u64_t)-1) ret = FALSE;
	}
	return ret;
}

bool_t Dz1Asn1Tag_isEndOfContents(Dz1Asn1Tag *tag)
{
	bool_t ret = FALSE;
	if (tag != NULL)
	{
		if (tag->cls == Dz1Asn1TagClass_universal && tag->flag == Dz1Asn1TagFlag_primitive && tag->numb == Dz1Asn1Type_eoc) ret = TRUE;
	}
	return ret;
}

bool_t Dz1Asn1Tag_isCompatible(Dz1Asn1Tag *a, Dz1Asn1Tag *b)
{
	bool_t ret = FALSE;
	if (a != NULL && b != NULL && a->cls == b->cls && a->numb == b->numb) ret = TRUE;
	return ret;
}
// Dz1Asn1Tag Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenTypeList Utility
bool_t _Dz1Asn1WipOpenTypeList_addOpenType(Dz1Asn1WipOpenTypeList *dst, u32_t order, Dz1Asn1WipOpenType **_data, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1WipOpenTypeEntry *node = NULL;
	if (dst == NULL || _data == NULL || *_data == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((node = Dz1Asn1WipOpenTypeEntry_new(order, *_data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOpenTypeEntry_delAndSetNull, (void *)&node);
		*_data = NULL;

		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1WipOpenTypeEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1WipOpenTypeList_addOpenType(Dz1Asn1WipOpenTypeList *dst, Dz1Asn1WipOpenType **_data, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1WipOpenTypeEntry *node = NULL;
	if (dst == NULL || _data == NULL || *_data == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u32_t order = dst->count(dst);
		if (_Dz1Asn1WipOpenTypeList_addOpenType(dst, order, _data, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1Asn1WipOpenTypeList Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOid Utility
bool_t Dz1Asn1WipOid_append(Dz1Asn1WipOid *dst, u32_t arc, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1WipOidArc *node = NULL;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1Asn1WipOidArc_new(dst->count(dst), arc, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOidArc_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1WipOidArc_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Asn1_encOidArc(Dz1ElasticBuf *dst, u64_t v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	u8_t buf[9] = { 0, }, *cp = NULL;
	size_t buf_sz = sizeof(buf);
	int idx = (int)buf_sz - 1, cnt = 0;

	buf[idx--] = (u8_t)(v & 0x7F);
	v >>= 7;
	cnt++;

	while(idx >= 0 && v & 0x7F)
	{
		buf[idx--] = 0x80 | (u8_t)(v & 0x7F);
		v >>= 7;
		cnt++;
	}

	cp = &buf[buf_sz - cnt];

	if (_Dz1ElasticBuf_push(dst, cp, cnt, errp) == FALSE) ERR_OUT(errp);
	else 
	{
		ret = cnt;
		Dz1Error_set(errp, 0);
	}

	return errp->code == 0 ? ret : -1;
}
// Dz1Asn1WipOid Utility
///////////////////////////////////////////////////////////////////////////////

Dz1Asn1Tag dz1Asn1BerTagSequence	= BerTagValueDz1Asn1Sequence; // { Dz1Asn1TagClass_universal, TRUE, Dz1Asn1Type_seq };
Dz1Asn1Tag dz1Asn1BerTagSequenceOf	= BerTagValueDz1Asn1Sequence; // { Dz1Asn1TagClass_universal, TRUE, Dz1Asn1Type_seq };

Dz1Asn1Tag dz1Asn1BerTagSet			= BerTagValueDz1Asn1Set; // { Dz1Asn1TagClass_universal, TRUE, Dz1Asn1Type_seq };
Dz1Asn1Tag dz1Asn1BerTagSetOf		= BerTagValueDz1Asn1Set; // { Dz1Asn1TagClass_universal, TRUE, Dz1Asn1Type_seq };

///////////////////////////////////////////////////////////////////////////////
// Type API
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1Any);				// USER API

Dz1Asn1TypeAPI_declare_trk(Dz1Asn1Bool);			// 1
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1Int);				// 2
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1BitStr);			// 3
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1OctetStr);		// 4
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1Null);			// 5
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1OID);				// 6
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1ObjDescr);		// 7
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1External);		// 8
Dz1Asn1TypeAPI_declare(Dz1Asn1InstanceOf);			// 8
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1Real);			// 9
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1Enum);			// 10
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1EmbPdv);			// 11
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1UTF8Str);			// 12
													// 13 : Relative-OID = OID
													// 14 : TIME = UTF8Str
													// 15 : Reserved
													// 16 : Sequence, Sequence-Of
													// 17 : Set, Set-Of
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1DigitStr);		// 18
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1PrintStr);		// 19
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1TeletexStr);		// 20
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1VideotexStr);		// 21
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1IA5Str);			// 22
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1UTCTime);			// 23
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1GeneralTime);		// 24
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1GraphicStr);		// 25
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1VisibleStr);		// 26
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1GeneralStr);		// 27
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1UniversalStr);	// 28
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1CharStr);			// 29
Dz1Asn1TypeAPI_declare_trk(Dz1Asn1BMPStr);			// 30
													// 31 : DATE		= UTF8Str
													// 32 : TimeOfDay	= UTF8Str
													// 33 : DateTime	= UTF8Str
													// 34 : Duration	= UTF8Str
// Type API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1OID_initFromWIP
typedef struct OidCollectArg
{
	u32_t *arr;
	u32_t idx;
} OidCollectArg;

static Dz1Error _oid_collect(void *ptr, Dz1Asn1WipOidArc *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	OidCollectArg *arg = (OidCollectArg *)ptr;
	arg->arr[arg->idx++] = p->num;

	return err;
}

static void Dz1Asn1OID_contentsDel(void *ptr)
{
	Dz1Asn1OID *dst = (Dz1Asn1OID *)ptr;
	if (dst != NULL)
	{
		if (dst->data != NULL) Dz1Free(dst->data);
		dst->data = NULL;

		dst->cnt = 0;
	}
}

bool_t Dz1Asn1OID_initFromWIP(Dz1Asn1OID *dst, Dz1Asn1WipOid *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t cnt = 0;
	if (dst->data != NULL || dst->cnt != 0) ERR_SET_OUT(errp, EINVAL);
	else if ((cnt = src->count(src)) == 0) ERR_SET_OUT(errp, ENOENT);
	else if ((dst->data = (u32_t *)Dz1Calloc(sizeof(u32_t), (dst->cnt = cnt), errp)) == NULL) ERR_OUT(errp);
	else
	{
		OidCollectArg arg = { dst->data, 0 };
		pthread_cleanup_push(Dz1Asn1OID_contentsDel, (void *)dst);

		if ((*errp = src->travel(src, _oid_collect, (void *)&arg)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Asn1OID_contentsDel, (void *)dst);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1Asn1OID_initFromWIP
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Prefixed Utility
bool_t Dz1Asn1Prefixed_apply(Dz1Asn1WipValue *dst_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *src_data, u32_t order, Dz1Error *errp)
{	// decode path, parent_data = Dz1Asn1WipCst, change to proper WipValue
	if (dst_data == NULL || my_descr == NULL || src_data == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst_data->present != Dz1Asn1WipValuePresent_max) ERR_SET_OUT(errp, EFAULT);
	else
	{	// toss to destination
		dst_data->present = src_data->present;
		dst_data->x.__ptr__ = src_data->x.__ptr__;
		src_data->x.__ptr__ = NULL;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

void *Dz1Asn1Prefixed_getChild(void *_src, Dz1Asn1TypeDescr **opt_ret_descr)
{	// encode path, _src is original type
	void *ret = _src;
	if (opt_ret_descr) *opt_ret_descr = NULL;
	return ret;
}
// Dz1Asn1Prefixed Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1MetaDataRange API
bool_t Dz1Asn1MetaDataRange_match(Dz1Asn1MetaDataRange *p, Dz1Asn1Int v)
{
	bool_t ret = FALSE;
	if (p != NULL)
	{
		if (p->low <= v && v <= p->high) ret = TRUE;
	}
	return ret;
}

int Dz1Asn1MetaDataRange_test(Dz1Asn1MetaDataRange *p, Dz1Asn1Int v)
{
	int ret = 0;
	if (p != NULL)
	{
		if (v < p->low) ret = -1;
		else if (v > p->high) ret = 1;
	}
	return ret;
}
// Dz1Asn1MetaDataRange API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// REAL Range Entry
bool_t Dz1Asn1MetaDataRealRange_match(Dz1Asn1MetaDataRealRange *p, Dz1Asn1Real v)
{
	bool_t ret = FALSE;
	if (p != NULL)
	{
		if (p->low <= v && v <= p->high) ret = TRUE;
	}
	return ret;
}
// REAL Range Entry
///////////////////////////////////////////////////////////////////////////////

