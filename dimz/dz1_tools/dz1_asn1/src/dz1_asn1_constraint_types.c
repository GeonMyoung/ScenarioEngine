#include "dz1_asn1_constraint_types.h"

///////////////////////////////////////////////////////////////////////////////
// Range Array
Dz1Asn1MetaDataRangeInfo *Dz1Asn1MetaDataRangeInfo_new(Dz1Asn1MetaDataRange *arr, u32_t cnt, bool_t extensible, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1MetaDataRangeInfo *ret = NULL;
	if ((ret = (Dz1Asn1MetaDataRangeInfo *)Dz1Calloc(sizeof(Dz1Asn1MetaDataRangeInfo), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1MetaDataRangeInfo_delAndSetNull, (void *)&ret);
		_array_clone(Dz1Asn1MetaDataRange, ret, arr, cnt, arr, cnt, err);
		ret->extensible = extensible;
		pthread_cleanup_pop(errp->code); // (Dz1Asn1MetaDataRangeInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1MetaDataRangeInfo_del(Dz1Asn1MetaDataRangeInfo *p)
{
	if (p == NULL) return;
	if (p->arr)
	{
		Dz1Free(p->arr);
		p->arr = NULL;
		p->cnt = 0;
	}
	Dz1Free(p);
}

void Dz1Asn1MetaDataRangeInfoA_dump(Dz1Asn1MetaDataRangeInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1MetaDataRange *r;
		Dz1ThreadA_printf("{ ");
		for (i = 0, r = p->arr; i < p->cnt; i++, r++)
		{
			if (r->low == r->high)
				Dz1ThreadA_printf("%s" DZ1_FMT64_A, i == 0 ? "" : ", ", r->low);
			else Dz1ThreadA_printf("%s" DZ1_FMT64_A "~" DZ1_FMT64_A, i == 0 ? "" : ", ", r->low, r->high);
		}
		Dz1ThreadA_printf("}\n");
	}
}
void Dz1Asn1MetaDataRangeInfoA_fdump(FILE *fp, Dz1Asn1MetaDataRangeInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1MetaDataRange *r;
		Dz1ThreadA_fprintf(fp, "{ ");
		for (i = 0, r = p->arr; i < p->cnt; i++, r++)
		{
			if (r->low == r->high)
				Dz1ThreadA_fprintf(fp, "%s" DZ1_FMT64_A, i == 0 ? "" : ", ", r->low);
			else Dz1ThreadA_fprintf(fp, "%s" DZ1_FMT64_A "~" DZ1_FMT64_A, i == 0 ? "" : ", ", r->low, r->high);
		}
		Dz1ThreadA_fprintf(fp, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1MetaDataRangeInfoW_dump(Dz1Asn1MetaDataRangeInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1MetaDataRange *r;
		Dz1ThreadW_printf(L"{ ");
		for (i = 0, r = p->arr; i < p->cnt; i++, r++)
		{
			if (r->low == r->high)
				Dz1ThreadW_printf(L"%s" DZ1_FMT64_W, i == 0 ? L"" : L", ", r->low);
			else Dz1ThreadW_printf(L"%s" DZ1_FMT64_W L"~" DZ1_FMT64_W, i == 0 ? L"" : L", ", r->low, r->high);
		}
		Dz1ThreadW_printf(L"}\n");
	}
}
void Dz1Asn1MetaDataRangeInfoW_fdump(FILE *fp, Dz1Asn1MetaDataRangeInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1MetaDataRange *r;
		Dz1ThreadW_fprintf(fp, L"{ ");
		for (i = 0, r = p->arr; i < p->cnt; i++, r++)
		{
			if (r->low == r->high)
				Dz1ThreadW_fprintf(fp, L"%s" DZ1_FMT64_W, i == 0 ? L"" : L", ", r->low);
			else Dz1ThreadW_fprintf(fp, L"%s" DZ1_FMT64_W L"~" DZ1_FMT64_W, i == 0 ? L"" : L", ", r->low, r->high);
		}
		Dz1ThreadW_fprintf(fp, L"}\n");
	}
}
#endif

bool_t Dz1Asn1MetaDataRangeInfo_match(Dz1Asn1MetaDataRangeInfo *p, Dz1Asn1Int v, bool_t *ret_is_ext)
{
	bool_t ret = FALSE;
	if (p != NULL)
	{
		u32_t i;
		for (i = 0; i < p->cnt; i++)
			if ((ret = Dz1Asn1MetaDataRange_match(&p->arr[i], v)) == TRUE) break;

		if (ret == FALSE && p->extensible)
		{
			ret = TRUE;
			if (ret_is_ext) *ret_is_ext = TRUE;
		}
	}
	return ret;
}
// Range Array
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// REAL Range Array
Dz1Asn1MetaDataRealRangeInfo *Dz1Asn1MetaDataRealRangeInfo_new(Dz1Asn1MetaDataRealRange *arr, u32_t cnt, bool_t extensible, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1MetaDataRealRangeInfo *ret = NULL;
	if ((ret = (Dz1Asn1MetaDataRealRangeInfo *)Dz1Calloc(sizeof(Dz1Asn1MetaDataRealRangeInfo), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1MetaDataRealRangeInfo_delAndSetNull, (void *)&ret);
		_array_clone(Dz1Asn1MetaDataRealRange, ret, arr, cnt, arr, cnt, err);
		ret->extensible = extensible;
		pthread_cleanup_pop(errp->code); // (Dz1Asn1MetaDataRealRangeInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1MetaDataRealRangeInfo_del(Dz1Asn1MetaDataRealRangeInfo *p)
{
	if (p == NULL) return;
	if (p->arr)
	{
		Dz1Free(p->arr);
		p->arr = NULL;
		p->cnt = 0;
	}
	Dz1Free(p);
}

void Dz1Asn1MetaDataRealRangeInfoA_dump(Dz1Asn1MetaDataRealRangeInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1MetaDataRealRange *r;
		Dz1ThreadA_printf("{ ");
		for (i = 0, r = p->arr; i < p->cnt; i++, r++)
		{
			if (r->low == r->high)
				Dz1ThreadA_printf("%s%f", i == 0 ? "" : ", ", r->low);
			else Dz1ThreadA_printf("%s%f~%f", i == 0 ? "" : ", ", r->low, r->high);
		}
		Dz1ThreadA_printf("}\n");
	}
}
void Dz1Asn1MetaDataRealRangeInfoA_fdump(FILE *fp, Dz1Asn1MetaDataRealRangeInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1MetaDataRealRange *r;
		Dz1ThreadA_fprintf(fp, "{ ");
		for (i = 0, r = p->arr; i < p->cnt; i++, r++)
		{
			if (r->low == r->high)
				Dz1ThreadA_fprintf(fp, "%s%f", i == 0 ? "" : ", ", r->low);
			else Dz1ThreadA_fprintf(fp, "%s%f~%f", i == 0 ? "" : ", ", r->low, r->high);
		}
		Dz1ThreadA_fprintf(fp, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1MetaDataRealRangeInfoW_dump(Dz1Asn1MetaDataRealRangeInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1MetaDataRealRange *r;
		Dz1ThreadW_printf(L"{ ");
		for (i = 0, r = p->arr; i < p->cnt; i++, r++)
		{
			if (r->low == r->high)
				Dz1ThreadW_printf(L"%s%f", i == 0 ? L"" : L", ", r->low);
			else Dz1ThreadW_printf(L"%s%f~%f", i == 0 ? L"" : L", ", r->low, r->high);
		}
		Dz1ThreadW_printf(L"}\n");
	}
}

void Dz1Asn1MetaDataRealRangeInfoW_fdump(FILE *fp, Dz1Asn1MetaDataRealRangeInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1MetaDataRealRange *r;
		Dz1ThreadW_fprintf(fp, L"{ ");
		for (i = 0, r = p->arr; i < p->cnt; i++, r++)
		{
			if (r->low == r->high)
				Dz1ThreadW_fprintf(fp, L"%s%f", i == 0 ? L"" : L", ", r->low);
			else Dz1ThreadW_fprintf(fp, L"%s%f~%f", i == 0 ? L"" : L", ", r->low, r->high);
		}
		Dz1ThreadW_fprintf(fp, L"}\n");
	}
}
#endif

bool_t Dz1Asn1MetaDataRealRangeInfo_match(Dz1Asn1MetaDataRealRangeInfo *p, Dz1Asn1Real v, bool_t *ret_is_ext)
{
	bool_t ret = FALSE;
	if (p != NULL)
	{
		u32_t i;
		for (i = 0; i < p->cnt; i++)
			if ((ret = Dz1Asn1MetaDataRealRange_match(&p->arr[i], v)) == TRUE) break;
	}

	if (ret == FALSE && p->extensible)
	{
		ret = TRUE;
		if (ret_is_ext) *ret_is_ext = TRUE;
	}
	return ret;
}
// Range Array
///////////////////////////////////////////////////////////////////////////////

