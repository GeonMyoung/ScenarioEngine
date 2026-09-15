#include <dz1_asn1.h>

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ExternalEncodingPresent
static struct Dz1Asn1ExternalEncodingPresentMapA
{
	str_t str;
	Dz1Asn1ExternalEncodingPresent v;
} Dz1Asn1ExternalEncodingPresentMapA[] =
{
	{ (char *)"single_ASN1_type", Dz1Asn1ExternalEncodingPresent_single_ASN1_type },
	{ (char *)"octet_aligned", Dz1Asn1ExternalEncodingPresent_octet_aligned },
	{ (char *)"arbitrary", Dz1Asn1ExternalEncodingPresent_arbitrary },
	{ NULL, Dz1Asn1ExternalEncodingPresent_max }
};

str_t Dz1Asn1ExternalEncodingPresentStrA(Dz1Asn1ExternalEncodingPresent v)
{
	struct Dz1Asn1ExternalEncodingPresentMapA *i = NULL;
	for (i = Dz1Asn1ExternalEncodingPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1ExternalEncodingPresent Dz1Asn1ExternalEncodingPresentFromStrA(str_t str)
{
	struct Dz1Asn1ExternalEncodingPresentMapA *i = NULL;
	for (i = Dz1Asn1ExternalEncodingPresentMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1Asn1ExternalEncodingPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1ExternalEncodingPresentMapW
{
	wstr_t str;
	Dz1Asn1ExternalEncodingPresent v;
} Dz1Asn1ExternalEncodingPresentMapW[] =
{
	{ (wchar_t *)L"single_ASN1_type", Dz1Asn1ExternalEncodingPresent_single_ASN1_type },
	{ (wchar_t *)L"octet_aligned", Dz1Asn1ExternalEncodingPresent_octet_aligned },
	{ (wchar_t *)L"arbitrary", Dz1Asn1ExternalEncodingPresent_arbitrary },
	{ NULL, Dz1Asn1ExternalEncodingPresent_max }
};

wstr_t Dz1Asn1ExternalEncodingPresentStrW(Dz1Asn1ExternalEncodingPresent v)
{
	struct Dz1Asn1ExternalEncodingPresentMapW *i = NULL;
	for (i = Dz1Asn1ExternalEncodingPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1ExternalEncodingPresent Dz1Asn1ExternalEncodingPresentFromStrW(wstr_t str)
{
	struct Dz1Asn1ExternalEncodingPresentMapW *i = NULL;
	for (i = Dz1Asn1ExternalEncodingPresentMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1Asn1ExternalEncodingPresent_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1ExternalEncodingPresent *Dz1Asn1ExternalEncodingPresent_new(Dz1Asn1ExternalEncodingPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1ExternalEncodingPresent *__internal_ret = (Dz1Asn1ExternalEncodingPresent *)Dz1Calloc(sizeof(Dz1Asn1ExternalEncodingPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1Asn1ExternalEncodingPresentA_dump(Dz1Asn1ExternalEncodingPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1ExternalEncodingPresentStrA(*v));
}
void Dz1Asn1ExternalEncodingPresentA_fdump(FILE *fp, Dz1Asn1ExternalEncodingPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", Dz1Asn1ExternalEncodingPresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ExternalEncodingPresentW_dump(Dz1Asn1ExternalEncodingPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1ExternalEncodingPresentStrW(*v));
}
void Dz1Asn1ExternalEncodingPresentW_fdump(FILE *fp, Dz1Asn1ExternalEncodingPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", Dz1Asn1ExternalEncodingPresentStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1Asn1ExternalEncodingPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ExternalEncoding
Dz1Asn1ExternalEncoding *Dz1Asn1ExternalEncoding_new(Dz1Asn1ExternalEncodingPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1ExternalEncoding *ret = (Dz1Asn1ExternalEncoding *)Dz1Calloc(sizeof(Dz1Asn1ExternalEncoding), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1ExternalEncoding_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
			case Dz1Asn1ExternalEncodingPresent_single_ASN1_type:
				ret->x.single_ASN1_type = (Dz1Asn1Any *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1Asn1ExternalEncodingPresent_octet_aligned:
				ret->x.octet_aligned = (Dz1Asn1OctetStr *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1Asn1ExternalEncodingPresent_arbitrary:
				ret->x.arbitrary = (Dz1Asn1BitStr *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1Asn1ExternalEncodingPresent_max:
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1ExternalEncoding_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Asn1ExternalEncoding *Dz1Asn1ExternalEncoding_clone(Dz1Asn1ExternalEncoding *src, Dz1Error *err)
{
	Dz1Asn1ExternalEncoding *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1Asn1ExternalEncoding *)Dz1Calloc(sizeof(Dz1Asn1ExternalEncoding), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1ExternalEncoding_delAndSetNull, (void *)&ret);

		ret->present = src->present;
		switch(ret->present)
		{
			case Dz1Asn1ExternalEncodingPresent_single_ASN1_type:
				if (src->x.single_ASN1_type && (ret->x.single_ASN1_type = Dz1Asn1Any_clone(src->x.single_ASN1_type, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1Asn1ExternalEncodingPresent_octet_aligned:
				if (src->x.octet_aligned && (ret->x.octet_aligned = Dz1Asn1OctetStr_clone(src->x.octet_aligned, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1Asn1ExternalEncodingPresent_arbitrary:
				if (src->x.arbitrary && (ret->x.arbitrary = Dz1Asn1BitStr_clone(src->x.arbitrary, errp)) == NULL) { ERR_OUT(errp); }
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1ExternalEncoding_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1ExternalEncoding_del(Dz1Asn1ExternalEncoding *p)
{
	if (!p) return;
	switch(p->present)
	{
		case Dz1Asn1ExternalEncodingPresent_single_ASN1_type:
			if (p->x.single_ASN1_type) Dz1Asn1Any_del(p->x.single_ASN1_type);
			break;
		case Dz1Asn1ExternalEncodingPresent_octet_aligned:
			if (p->x.octet_aligned) Dz1Asn1OctetStr_del(p->x.octet_aligned);
			break;
		case Dz1Asn1ExternalEncodingPresent_arbitrary:
			if (p->x.arbitrary) Dz1Asn1BitStr_del(p->x.arbitrary);
			break;
		default:
			break;
	}
	Dz1Free(p);
}

/*
typedef struct Dz1Asn1ExternalEncoding
{
	Dz1Asn1ExternalEncodingPresent	 present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1Any		*single_ASN1_type;
		Dz1Asn1OctetStr *octet_aligned;
		Dz1Asn1BitStr	*arbitrary;
	} x;
} Dz1Asn1ExternalEncoding;
*/
int Dz1Asn1ExternalEncoding_cmp(Dz1Asn1ExternalEncoding *a, Dz1Asn1ExternalEncoding *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if (a->present < b->present) ret = -1;
	else if (a->present > b->present) ret = 1;
	else
	{
		switch(a->present)
		{
		case Dz1Asn1ExternalEncodingPresent_single_ASN1_type: ret = Dz1Asn1Any_cmp(a->x.single_ASN1_type, b->x.single_ASN1_type); break;
		case Dz1Asn1ExternalEncodingPresent_octet_aligned: ret = Dz1Asn1OctetStr_cmp(a->x.octet_aligned, b->x.octet_aligned); break;
		case Dz1Asn1ExternalEncodingPresent_arbitrary: ret = Dz1Asn1BitStr_cmp(a->x.arbitrary, b->x.arbitrary); break;
		default: ret = 0; break;
		}
	}
	return ret;
}

void Dz1Asn1ExternalEncodingA_dump(Dz1Asn1ExternalEncoding *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	switch(p->present)
	{
		case Dz1Asn1ExternalEncodingPresent_single_ASN1_type:
			if (p->x.single_ASN1_type == NULL) Dz1ThreadA_tprintf(tab, "single_ASN1_type = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "single_ASN1_type = "); Dz1Asn1AnyA_dump(p->x.single_ASN1_type, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1ExternalEncodingPresent_octet_aligned:
			if (p->x.octet_aligned == NULL) Dz1ThreadA_tprintf(tab, "octet_aligned = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "octet_aligned = "); Dz1Asn1OctetStrA_dump(p->x.octet_aligned, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1ExternalEncodingPresent_arbitrary:
			if (p->x.arbitrary == NULL) Dz1ThreadA_tprintf(tab, "arbitrary = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "arbitrary = "); Dz1Asn1BitStrA_dump(p->x.arbitrary, tab); } // Pointer Construct with DUMP API
			break;
		default:
			Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
			break;
	}
}
void Dz1Asn1ExternalEncodingA_fdump(FILE *fp, Dz1Asn1ExternalEncoding *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	switch(p->present)
	{
		case Dz1Asn1ExternalEncodingPresent_single_ASN1_type:
			if (p->x.single_ASN1_type == NULL) Dz1ThreadA_fprintf(fp, "single_ASN1_type = NULL\n");
			else { Dz1ThreadA_fprintf(fp, "single_ASN1_type = "); Dz1Asn1AnyA_fdump(fp, p->x.single_ASN1_type, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1ExternalEncodingPresent_octet_aligned:
			if (p->x.octet_aligned == NULL) Dz1ThreadA_fprintf(fp, "octet_aligned = NULL\n");
			else { Dz1ThreadA_fprintf(fp, "octet_aligned = "); Dz1Asn1OctetStrA_fdump(fp, p->x.octet_aligned, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1ExternalEncodingPresent_arbitrary:
			if (p->x.arbitrary == NULL) Dz1ThreadA_fprintf(fp, "arbitrary = NULL\n");
			else { Dz1ThreadA_fprintf(fp, "arbitrary = "); Dz1Asn1BitStrA_fdump(fp, p->x.arbitrary, tab); } // Pointer Construct with DUMP API
			break;
		default:
			Dz1ThreadA_ftprintf(fp, tab, "??? = %d\n", p->present);
			break;
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ExternalEncodingW_dump(Dz1Asn1ExternalEncoding *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	switch(p->present)
	{
		case Dz1Asn1ExternalEncodingPresent_single_ASN1_type:
			if (p->x.single_ASN1_type == NULL) Dz1ThreadW_tprintf(tab, L"single_ASN1_type = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"single_ASN1_type = "); Dz1Asn1AnyW_dump(p->x.single_ASN1_type, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1ExternalEncodingPresent_octet_aligned:
			if (p->x.octet_aligned == NULL) Dz1ThreadW_tprintf(tab, L"octet_aligned = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"octet_aligned = "); Dz1Asn1OctetStrW_dump(p->x.octet_aligned, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1ExternalEncodingPresent_arbitrary:
			if (p->x.arbitrary == NULL) Dz1ThreadW_tprintf(tab, L"arbitrary = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"arbitrary = "); Dz1Asn1BitStrW_dump(p->x.arbitrary, tab); } // Pointer Construct with DUMP API
			break;
		default:
			Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
			break;
	}
}
void Dz1Asn1ExternalEncodingW_fdump(FILE *fp, Dz1Asn1ExternalEncoding *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	switch(p->present)
	{
		case Dz1Asn1ExternalEncodingPresent_single_ASN1_type:
			if (p->x.single_ASN1_type == NULL) Dz1ThreadW_fprintf(fp, L"single_ASN1_type = NULL\n");
			else { Dz1ThreadW_fprintf(fp, L"single_ASN1_type = "); Dz1Asn1AnyW_fdump(fp, p->x.single_ASN1_type, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1ExternalEncodingPresent_octet_aligned:
			if (p->x.octet_aligned == NULL) Dz1ThreadW_fprintf(fp, L"octet_aligned = NULL\n");
			else { Dz1ThreadW_fprintf(fp, L"octet_aligned = "); Dz1Asn1OctetStrW_fdump(fp, p->x.octet_aligned, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1ExternalEncodingPresent_arbitrary:
			if (p->x.arbitrary == NULL) Dz1ThreadW_fprintf(fp, L"arbitrary = NULL\n");
			else { Dz1ThreadW_fprintf(fp, L"arbitrary = "); Dz1Asn1BitStrW_fdump(fp, p->x.arbitrary, tab); } // Pointer Construct with DUMP API
			break;
		default:
			Dz1ThreadW_ftprintf(fp, tab, L"??? = %d\n", p->present);
			break;
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1ExternalEncoding
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1External
Dz1Asn1External *_Dz1Asn1External_new(Dz1Asn1ExternalEncoding *encoding, Dz1Error *err, const char *__file, int __line)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1External *__internal_ret = (Dz1Asn1External *)_Dz1Calloc(sizeof(Dz1Asn1External), 1, errp, __file, __line);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1External_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->encoding = encoding;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1External_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1Asn1External *_Dz1Asn1External_clone(Dz1Asn1External *src, Dz1Error *err, const char *__file, int __line)
{
	Dz1Asn1External *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1Asn1External *)_Dz1Calloc(sizeof(Dz1Asn1External), 1, errp, __file, __line)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1External_delAndSetNull, (void *)&ret);

		if (src->direct_reference && (ret->direct_reference = _Dz1Asn1OID_clone(src->direct_reference, errp, __file, __line)) == NULL) ERR_OUT(errp);
		else if (src->indirect_reference && (ret->indirect_reference = (Dz1Asn1Int *)_Dz1Calloc(sizeof(Dz1Asn1Int), 1, errp, __file, __line)) == NULL) { ERR_OUT(errp); }
		else if (src->data_value_descriptor && (ret->data_value_descriptor = _Dz1Asn1ObjDescr_clone(src->data_value_descriptor, errp, __file, __line)) == NULL) ERR_OUT(errp);
		else if (src->encoding && (ret->encoding = Dz1Asn1ExternalEncoding_clone(src->encoding, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->indirect_reference != NULL && ret->indirect_reference != NULL) *ret->indirect_reference = *src->indirect_reference;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1External_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1External_del(Dz1Asn1External *p)
{
	if (p == NULL) return;
	if (p->direct_reference) Dz1Asn1OID_del(p->direct_reference);
	if (p->indirect_reference) Dz1Free(p->indirect_reference);
	if (p->data_value_descriptor) Dz1Asn1ObjDescr_del(p->data_value_descriptor);
	if (p->encoding) Dz1Asn1ExternalEncoding_del(p->encoding);
	Dz1Free(p);
}

int Dz1Asn1External_cmp(Dz1Asn1External *a, Dz1Asn1External *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if ((ret = Dz1Asn1OID_cmp(a->direct_reference, b->direct_reference)) != 0) {}
	else if ((ret = Dz1Asn1Int_cmp(a->indirect_reference, b->indirect_reference)) != 0) {}
	else if ((ret = Dz1Asn1ObjDescr_cmp(a->data_value_descriptor, b->data_value_descriptor)) != 0) {}
	else if ((ret = Dz1Asn1ExternalEncoding_cmp(a->encoding, b->encoding)) != 0) {}
	return ret;
}

void Dz1Asn1ExternalA_dump(Dz1Asn1External *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("{\n"); tab++;

	if (p->direct_reference == NULL) Dz1ThreadA_tprintf(tab, "direct_reference = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "direct_reference = "); Dz1Asn1OIDA_dump(p->direct_reference, tab); /* using dump func */ }

	if (p->indirect_reference == NULL) Dz1ThreadA_tprintf(tab, "indirect_reference = NULL\n");
	else {Dz1ThreadA_tprintf(tab, "indirect_reference = "); Dz1Asn1IntA_dump(p->indirect_reference, tab); }

	if (p->data_value_descriptor == NULL) Dz1ThreadA_tprintf(tab, "data_value_descriptor = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "data_value_descriptor = "); Dz1Asn1ObjDescrA_dump(p->data_value_descriptor, tab); /* using dump func */ }

	if (p->encoding == NULL) Dz1ThreadA_tprintf(tab, "encoding = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "encoding."); Dz1Asn1ExternalEncodingA_dump(p->encoding, tab); /* using dump func */ }

	Dz1ThreadA_tprintf(--tab, "}\n");
}
void Dz1Asn1ExternalA_fdump(FILE *fp, Dz1Asn1External *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	Dz1ThreadA_fprintf(fp, "{\n");tab++;

	if (p->direct_reference == NULL) Dz1ThreadA_ftprintf(fp, tab, "direct_reference = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "direct_reference = "); Dz1Asn1OIDA_fdump(fp, p->direct_reference, tab); }

	if (p->indirect_reference == NULL) Dz1ThreadA_ftprintf(fp, tab, "indirect_reference = NULL\n");
	else {Dz1ThreadA_ftprintf(fp, tab, "indirect_reference = "); Dz1Asn1IntA_fdump(fp, p->indirect_reference, tab); }

	if (p->data_value_descriptor == NULL) Dz1ThreadA_ftprintf(fp, tab, "data_value_descriptor = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "data_value_descriptor = "); Dz1Asn1ObjDescrA_fdump(fp, p->data_value_descriptor, tab); }

	if (p->encoding == NULL) Dz1ThreadA_ftprintf(fp, tab, "encoding = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "encoding."); Dz1Asn1ExternalEncodingA_fdump(fp, p->encoding, tab); }

	Dz1ThreadA_ftprintf(fp, --tab, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ExternalW_dump(Dz1Asn1External *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"{\n"); tab++;

	if (p->direct_reference == NULL) Dz1ThreadW_tprintf(tab, L"direct_reference = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"direct_reference = "); Dz1Asn1OIDW_dump(p->direct_reference, tab); /* using dump func */ }

	if (p->indirect_reference == NULL) Dz1ThreadW_tprintf(tab, L"indirect_reference = NULL\n");
	else {Dz1ThreadW_tprintf(tab, L"indirect_reference = "); Dz1Asn1IntW_dump(p->indirect_reference, tab); }

	if (p->data_value_descriptor == NULL) Dz1ThreadW_tprintf(tab, L"data_value_descriptor = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"data_value_descriptor = "); Dz1Asn1ObjDescrW_dump(p->data_value_descriptor, tab); /* using dump func */ }

	if (p->encoding == NULL) Dz1ThreadW_tprintf(tab, L"encoding = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"encoding."); Dz1Asn1ExternalEncodingW_dump(p->encoding, tab); /* using dump func */ }

	Dz1ThreadW_tprintf(--tab, L"}\n");
}
void Dz1Asn1ExternalW_fdump(FILE *fp, Dz1Asn1External *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	Dz1ThreadW_fprintf(fp, L"{\n");tab++;

	if (p->direct_reference == NULL) Dz1ThreadW_ftprintf(fp, tab, L"direct_reference = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"direct_reference = "); Dz1Asn1OIDW_fdump(fp, p->direct_reference, tab); }

	if (p->indirect_reference == NULL) Dz1ThreadW_ftprintf(fp, tab, L"indirect_reference = NULL\n");
	else {Dz1ThreadW_ftprintf(fp, tab, L"indirect_reference = "); Dz1Asn1IntW_fdump(fp, p->indirect_reference, tab); }

	if (p->data_value_descriptor == NULL) Dz1ThreadW_ftprintf(fp, tab, L"data_value_descriptor = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"data_value_descriptor = "); Dz1Asn1ObjDescrW_fdump(fp, p->data_value_descriptor, tab); }

	if (p->encoding == NULL) Dz1ThreadW_ftprintf(fp, tab, L"encoding = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"encoding."); Dz1Asn1ExternalEncodingW_fdump(fp, p->encoding, tab); }

	Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
}
#endif // UNIX_SYSTEM
// Dz1Asn1External
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1InstanceOf
Dz1Asn1InstanceOf *Dz1Asn1InstanceOf_new(Dz1Asn1OID *type_id, Dz1Asn1Any *value, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1InstanceOf *__internal_ret = (Dz1Asn1InstanceOf *)Dz1Calloc(sizeof(Dz1Asn1InstanceOf), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1InstanceOf_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->type_id = type_id;
		__internal_ret->value = value;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1InstanceOf_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1Asn1InstanceOf *Dz1Asn1InstanceOf_clone(Dz1Asn1InstanceOf *src, Dz1Error *err)
{
	Dz1Asn1InstanceOf *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1Asn1InstanceOf *)Dz1Calloc(sizeof(Dz1Asn1InstanceOf), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1InstanceOf_delAndSetNull, (void *)&ret);

		if (src->type_id && (ret->type_id = Dz1Asn1OID_clone(src->type_id, errp)) == NULL) ERR_OUT(errp);
		else if (src->value && (ret->value = Dz1Asn1Any_clone(src->value, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1InstanceOf_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1InstanceOf_del(Dz1Asn1InstanceOf *p)
{
	if (p == NULL) return;
	if (p->type_id) Dz1Asn1OID_del(p->type_id);
	if (p->value) Dz1Asn1Any_del(p->value);
	Dz1Free(p);
}

int Dz1Asn1InstanceOf_cmp(Dz1Asn1InstanceOf *a, Dz1Asn1InstanceOf *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if ((ret = Dz1Asn1OID_cmp(a->type_id, b->type_id)) != 0) { }
	else if ((ret = Dz1Asn1Any_cmp(a->value, b->value)) != 0) { }
	return ret;
}

void Dz1Asn1InstanceOfA_dump(Dz1Asn1InstanceOf *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("{\n"); tab++;

	if (p->type_id == NULL) Dz1ThreadA_tprintf(tab, "type_id = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "type_id = "); Dz1Asn1OIDA_dump(p->type_id, tab); /* using dump func */ }

	if (p->value == NULL) Dz1ThreadA_tprintf(tab, "value = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "value = "); Dz1Asn1AnyA_dump(p->value, tab); /* using dump func */ }

	Dz1ThreadA_tprintf(--tab, "}\n");
}
void Dz1Asn1InstanceOfA_fdump(FILE *fp, Dz1Asn1InstanceOf *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	Dz1ThreadA_fprintf(fp, "{\n");tab++;

	if (p->type_id == NULL) Dz1ThreadA_ftprintf(fp, tab, "type_id = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "type_id = "); Dz1Asn1OIDA_fdump(fp, p->type_id, tab); }

	if (p->value == NULL) Dz1ThreadA_ftprintf(fp, tab, "value = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "value = "); Dz1Asn1AnyA_fdump(fp, p->value, tab); }

	Dz1ThreadA_ftprintf(fp, --tab, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1Asn1InstanceOfW_dump(Dz1Asn1InstanceOf *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"{\n"); tab++;

	if (p->type_id == NULL) Dz1ThreadW_tprintf(tab, L"type_id = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"type_id = "); Dz1Asn1OIDW_dump(p->type_id, tab); /* using dump func */ }

	if (p->value == NULL) Dz1ThreadW_tprintf(tab, L"value = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"value = "); Dz1Asn1AnyW_dump(p->value, tab); /* using dump func */ }

	Dz1ThreadW_tprintf(--tab, L"}\n");
}
void Dz1Asn1InstanceOfW_fdump(FILE *fp, Dz1Asn1InstanceOf *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	Dz1ThreadW_fprintf(fp, L"{\n");tab++;

	if (p->type_id == NULL) Dz1ThreadW_ftprintf(fp, tab, L"type_id = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"type_id = "); Dz1Asn1OIDW_fdump(fp, p->type_id, tab); }

	if (p->value == NULL) Dz1ThreadW_ftprintf(fp, tab, L"value = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"value = "); Dz1Asn1AnyW_fdump(fp, p->value, tab); }

	Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
}
#endif // UNIX_SYSTEM
// Dz1Asn1InstanceOf
////////////////////////////////////////////////////////////////////////////////

