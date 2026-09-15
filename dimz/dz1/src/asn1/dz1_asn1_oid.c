#include <ctype.h>
#include <dz1_str.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_asn1.h>

static u32_t _oid_ber[] = { 1, 1 };
Dz1Asn1OID dz1Asn1OID_value_BER = { _oid_ber, sizeof(_oid_ber) / sizeof(u32_t) };

static u32_t _oid_der[] = { 1, 2, 0 };
Dz1Asn1OID dz1Asn1OID_value_DER = { _oid_der, sizeof(_oid_der) / sizeof(u32_t) };

static u32_t _oid_cer[] = { 1, 2, 1 };
Dz1Asn1OID dz1Asn1OID_value_CER = { _oid_cer, sizeof(_oid_cer) / sizeof(u32_t) };

static u32_t _oid_baper[] = { 1, 3, 0, 0 };
Dz1Asn1OID dz1Asn1OID_value_BAPER = { _oid_baper, sizeof(_oid_baper) / sizeof(u32_t) };

static u32_t _oid_buper[] = { 1, 3, 0, 1 };
Dz1Asn1OID dz1Asn1OID_value_BUPER = { _oid_buper, sizeof(_oid_buper) / sizeof(u32_t) };

static u32_t _oid_caper[] = { 1, 3, 1, 0 };
Dz1Asn1OID dz1Asn1OID_value_CAPER = { _oid_caper, sizeof(_oid_caper) / sizeof(u32_t) };

static u32_t _oid_cuper[] = { 1, 3, 1, 1 };
Dz1Asn1OID dz1Asn1OID_value_CUPER = { _oid_cuper, sizeof(_oid_cuper) / sizeof(u32_t) };


Dz1Asn1OID *_Dz1Asn1OID_new(u32_t *arg_arr, size_t cnt, Dz1Error *err, const char *__file, int __line)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1OID *ret = NULL;
	if (arg_arr != NULL && cnt == 0) ERR_SET_OUT(errp, EINVAL);
	if ((ret = (Dz1Asn1OID *)_Dz1Calloc(sizeof(Dz1Asn1OID), 1, errp, __file, __line)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&ret);
		if (cnt > 0)
		{
			if ((ret->data = (u32_t *)_Dz1Calloc(sizeof(u32_t), (ret->cnt = cnt), errp, __file, __line)) == NULL) ERR_OUT(errp);
			else if (arg_arr != NULL)
			{
				u32_t i;
				for (i = 0; i < cnt; i++)
					ret->data[i] = arg_arr[i];
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1OID_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Asn1OID *Dz1Asn1OID_newFromData(u8_t *data, size_t unitSize, size_t cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1OID *ret = NULL;
	if (unitSize != 1 && unitSize != 2 && unitSize != 4) ERR_SET_OUT(errp, EINVAL);
	else if (data != NULL || cnt == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1Asn1OID_new(NULL, cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		size_t i;
		u16_t *v2;
		u32_t *v4;
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&ret);

		switch(unitSize)
		{
			case 1:
				for (i = 0; i < cnt; i++)
					ret->data[i] = (u32_t)(data[i]);
				break;
			case 2:
				v2 = (u16_t *)data;
				for (i = 0; i < cnt; i++)
					ret->data[i] = (u32_t)(v2[i]);
				break;
			case 4:
				v4 = (u32_t *)data;
				for (i = 0; i < cnt; i++)
					ret->data[i] = v4[i];
				break;
		}
		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Asn1OID_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Asn1OID *_Dz1Asn1OID_clone(Dz1Asn1OID *src, Dz1Error *err, const char *__file, int __line)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1OID *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->data != NULL && src->cnt > 0)
	{
		if ((ret = _Dz1Asn1OID_new(src->data, src->cnt, errp, __file, __line)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((ret = Dz1Asn1OID_gen(errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

Dz1Asn1OID *Dz1Asn1OIDA_newFromStr(str_t strOid, Dz1Error *err)
{
	Dz1Asn1OID *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	size_t cnt = 0;
	char *cp = strOid;
	if (*cp == '.') { ERR_SET_OUT(errp, EINVAL); return NULL; }
	while(*cp)
	{
		if (isdigit((int)(*cp)))
		{
			while(*cp && isdigit((int)(*cp))) cp++;
			if (*cp != '\0' && *cp != '.') { ERR_SET_OUT(errp, EINVAL); return NULL; }
			cnt++;
		} else cp++;
	}

	if ((ret = (Dz1Asn1OID *)Dz1Malloc(sizeof(Dz1Asn1OID), errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&ret);
		if ((ret->data = (u32_t *)Dz1Malloc(sizeof(u32_t) * (ret->cnt = cnt), errp)) == NULL) ERR_OUT(errp);
		else
		{
			cnt = 0;
			cp = strOid;
			while(*cp)
			{
				if (isdigit((int)(*cp)))
				{
					char buf[32], *dp = buf;
					while(*cp && isdigit((int)(*cp)))
						*dp++ = *cp++;
					*dp = '\0';
					if (*cp == '.') cp++; // pass '.'
					ret->data[cnt++] = Dz1Ato32(buf);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1OID_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
Dz1Asn1OID *Dz1Asn1OIDW_newFromStr(wstr_t strOid, Dz1Error *err)
{
	Dz1Asn1OID *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	size_t cnt = 0;
	wchar_t *cp = strOid;
	if (*cp == L'.') { ERR_SET_OUT(errp, EINVAL); return NULL; }
	while(*cp)
	{
		if (iswdigit((int)(*cp)))
		{
			while(*cp && iswdigit((int)(*cp))) cp++;
			if (*cp != L'\0' && *cp != L'.') { ERR_SET_OUT(errp, EINVAL); return NULL; }
			cnt++;
		} else cp++;
	}

	if ((ret = (Dz1Asn1OID *)Dz1Malloc(sizeof(Dz1Asn1OID), errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&ret);
		if ((ret->data = (u32_t *)Dz1Malloc(sizeof(u32_t) * (ret->cnt = cnt), errp)) == NULL) ERR_OUT(errp);
		else
		{
			cnt = 0;
			cp = strOid;
			while(*cp)
			{
				if (iswdigit((int)(*cp)))
				{
					wchar_t buf[32], *dp = buf;
					while(*cp && iswdigit((int)(*cp)))
						*dp++ = *cp++;
					*dp = 0;
					if (*cp == L'.') cp++; // pass '.'
					ret->data[cnt++] = Dz1Wto32(buf);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1OID_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif
void Dz1Asn1OID_del(Dz1Asn1OID *p)
{
	if (!p) return;
	if (p->data) Dz1Free(p->data);
	p->data = NULL;
	Dz1Free(p);
}

void Dz1Asn1OIDA_dump(Dz1Asn1OID *p, int tab)
{
	size_t i;
	Dz1ThreadA_tprintf(tab, "{ ");
	for (i = 0; i < p->cnt; i++)
	{
		if (i) Dz1ThreadA_printf(".%d", p->data[i]);
		else Dz1ThreadA_printf("%d", p->data[i]);
	}
	Dz1ThreadA_tprintf(tab, " }\n");
}

void Dz1Asn1OIDA_fdump(FILE *fp, Dz1Asn1OID *p, int tab)
{
	size_t i;
	Dz1ThreadA_ftprintf(fp, tab, "{ ");
	for (i = 0; i < p->cnt; i++)
	{
		if (i) Dz1ThreadA_fprintf(fp, ".%d", p->data[i]);
		else Dz1ThreadA_fprintf(fp, "%d", p->data[i]);
	}
	Dz1ThreadA_ftprintf(fp, tab, " }\n");
}
#ifndef UNIX_SYSTEM
void Dz1Asn1OIDW_dump(Dz1Asn1OID *p, int tab)
{
	size_t i;
	Dz1ThreadW_tprintf(tab, L"{ ");
	for (i = 0; i < p->cnt; i++)
	{
		if (i) Dz1ThreadW_printf(L".%d", p->data[i]);
		else Dz1ThreadW_printf(L"%d", p->data[i]);
	}
	Dz1ThreadW_tprintf(tab, L" }\n");
}

void Dz1Asn1OIDW_fdump(FILE *fp, Dz1Asn1OID *p, int tab)
{
	size_t i;
	Dz1ThreadW_ftprintf(fp, tab, L"{ ");
	for (i = 0; i < p->cnt; i++)
	{
		if (i) Dz1ThreadW_fprintf(fp, L".%d", p->data[i]);
		else Dz1ThreadW_fprintf(fp, L"%d", p->data[i]);
	}
	Dz1ThreadW_ftprintf(fp, tab, L" }\n");
}
#endif
int Dz1Asn1OID_cmp(Dz1Asn1OID *a, Dz1Asn1OID *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else
	{
		int ret = (int)(a->cnt - b->cnt);
		if (ret == 0)
		{
			size_t i;
			for (i = 0; i < a->cnt; i++)
				if ((ret = a->data[i] - b->data[i]) != 0) break;
		}
		return ret;
	}
}

ssize_t Dz1Asn1OIDA_printable(Dz1Asn1OID *oid, char *dst, size_t dstSize, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	size_t i;
	ssize_t status, ret = 0;
	char *cp = dst;
	char temp[16];
	for (i = 0; errp->code == 0 && i < oid->cnt; i++)
	{
		if (i)
		{
			if (dstSize > 0)
			{
				if (cp != NULL) *cp++ = '.';
				dstSize--;
				ret++;
			}
			else
			{
				Dz1Error_set(errp, E2BIG);
				break;
			}
		}

		if ((status = sprintf(temp, "%d", oid->data[i])) < 0) Dz1Error_set(errp, E2BIG);
		else if ((size_t)status > dstSize) Dz1Error_set(errp, E2BIG);
		else
		{
			if (cp != NULL) 
			{
				strncpy(cp, temp, status);
				cp += status;
			}
			dstSize -= status;
			ret += status;
		}
	}

	if (errp->code == 0)
	{
		if (dstSize)
		{
			*cp = 0;
			dstSize--;
			ret++;
		}
		else Dz1Error_set(errp, E2BIG);
	}
	return errp->code == 0 ? ret : -1;
}
#ifndef UNIX_SYSTEM
ssize_t Dz1Asn1OIDW_printable(Dz1Asn1OID *oid, wchar_t *dst, size_t dstSize, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	size_t i;
	ssize_t status, ret = 0;
	wchar_t *cp = dst;
	wchar_t temp[16];
	for (i = 0; errp->code == 0 && i < oid->cnt; i++)
	{
		if (i)
		{
			if (dstSize > 0)
			{
				if (cp != NULL) *cp++ = L'.';
				dstSize--;
				ret++;
			}
			else
			{
				Dz1Error_set(errp, E2BIG);
				break;
			}
		}

		if ((status = swprintf(temp, 16, L"%d", oid->data[i])) < 0) Dz1Error_set(errp, E2BIG);
		else if ((size_t)status > dstSize) Dz1Error_set(errp, E2BIG);
		else
		{
			if (cp != NULL) 
			{
				wcsncpy(cp, temp, status);
				cp += status;
			}
			dstSize -= status;
			ret += status;
		}
	}

	if (errp->code == 0)
	{
		if (dstSize)
		{
			*cp = 0;
			dstSize--;
			ret++;
		}
		else Dz1Error_set(errp, E2BIG);
	}
	return errp->code == 0 ? ret : -1;
}
#endif