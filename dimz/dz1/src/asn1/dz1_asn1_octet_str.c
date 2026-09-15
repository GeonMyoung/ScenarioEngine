#include <dz1_codec.h>
#include <dz1_malloc.h>
#include <dz1_stdio.h>
#include <dz1_thread_stdio.h>
#include <dz1_asn1.h>

Dz1Asn1OctetStr	*_Dz1Asn1OctetStr_new(u8_t *data, uint32_t byte_size, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1OctetStr *ret = (Dz1Asn1OctetStr *)_Dz1Calloc(sizeof(Dz1Asn1OctetStr), 1, errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OctetStr_delAndSetNull, (void *)&ret);

		ret->size = byte_size;
		if (byte_size > 0)
		{
			if (data == (u8_t *)-1)
			{
				if ((ret->data = (u8_t *)Dz1Malloc(ret->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			else if (data != NULL)
			{
				if ((ret->data = (u8_t *)_Dz1Memory_clone(data, byte_size, errp,__file__, __line__)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1OctetStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

/*
Dz1Asn1OctetStr *_Dz1Asn1OctetStrA_newFromStr(str_t src, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
//	Dz1Asn1OctetStr *ret = _Dz1Asn1OctetStr_new((u8_t *)src, (strlen(src) + 1) * sizeof(char), errp, __file__, __line__);
	Dz1Asn1OctetStr *ret = _Dz1Asn1OctetStr_new((u8_t *)src, strlen(src) * sizeof(char), errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1Asn1OctetStr *_Dz1Asn1OctetStrW_newFromStr(wstr_t src, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
//	Dz1Asn1OctetStr *ret = _Dz1Asn1OctetStr_new((u8_t *)src, (wcslen(src) + 1) * sizeof(wchar_t), errp, __file__, __line__);
	Dz1Asn1OctetStr *ret = _Dz1Asn1OctetStr_new((u8_t *)src, wcslen(src) * sizeof(wchar_t), errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}
#endif
*/

static Dz1Asn1OctetStr *__Dz1Asn1OctetStrA_newFromFile(str_t fn, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Asn1OctetStr *ret = _Dz1Asn1OctetStr_new(NULL, 0, errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		FILE *fp = NULL;
		pthread_cleanup_push(Dz1Asn1OctetStr_delAndSetNull, (void *)&ret);
		if ((fp = Dz1FileStreamA_open(fn, "r+b", errp)) == NULL) { }
		else
		{
            ssize_t sz;
			pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

			if (fseek(fp, 0, SEEK_END) < 0) ERR_SET_OUT(errp, errno);
			else if ((sz = (size_t)ftell(fp)) < 0) ERR_SET_OUT(errp, errno);
			else
			{
				ret->size = (u32_t)sz;
				if (fseek(fp, 0, SEEK_SET) < 0) ERR_SET_OUT(errp, errno);
				else if ((ret->data = (u8_t *)_Dz1Calloc(sizeof(u8_t), ret->size, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
				else if (fread(ret->data, sizeof(u8_t), ret->size, fp) != ret->size) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1OctetStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Asn1OctetStr *_Dz1Asn1OctetStrA_newFromFile(str_t path, str_t name, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Asn1OctetStr *ret = NULL;
	char fn[4096];

	if (name == NULL || strlen(name) == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (path != NULL && strlen(path) > 0)
			sprintf(fn, "%s" DIR_SEPRATOR_A "%s", path, name);
		else strcpy(fn, name);

		if ((ret = __Dz1Asn1OctetStrA_newFromFile(fn, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
static Dz1Asn1OctetStr *__Dz1Asn1OctetStrW_newFromFile(wstr_t fn, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Asn1OctetStr *ret = _Dz1Asn1OctetStr_new(NULL, 0, errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		FILE *fp = NULL;
		pthread_cleanup_push(Dz1Asn1OctetStr_delAndSetNull, (void *)&ret);
		if ((fp = Dz1FileStreamW_open(fn, L"r+b", errp)) == NULL) { }
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

			if (fseek(fp, 0, SEEK_END) < 0) ERR_SET_OUT(errp, errno);
			else if ((sz = (size_t)ftell(fp)) < 0) ERR_SET_OUT(errp, errno);
			else
			{
				ret->size = (u32_t)sz;
				if (fseek(fp, 0, SEEK_SET) < 0) ERR_SET_OUT(errp, errno);
				else if ((ret->data = (u8_t *)_Dz1Calloc(sizeof(u8_t), ret->size, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
				else if (fread(ret->data, sizeof(u8_t), ret->size, fp) != ret->size) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1OctetStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Asn1OctetStr *_Dz1Asn1OctetStrW_newFromFile(wstr_t path, wstr_t name, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Asn1OctetStr *ret = NULL;
	wchar_t fn[4096];

	if (name == NULL || wcslen(name) == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (path != NULL && wcslen(path) > 0)
			swprintf(fn, 4095, L"%s" DIR_SEPRATOR_W L"%s", path, name);
		else wcscpy(fn, name);

		if ((ret = __Dz1Asn1OctetStrW_newFromFile(fn, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
	}
	return ret;
}
#endif

bool_t _Dz1Asn1OctetStr_copy(Dz1Asn1OctetStr *dst, Dz1Asn1OctetStr *src, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->data != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		dst->size = src->size;
		if (src->data != NULL && (dst->data = _Dz1Memory_clone(src->data, src->size, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

Dz1Asn1OctetStr *_Dz1Asn1OctetStr_clone(Dz1Asn1OctetStr *src, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL)
	{
		ERR_SET_OUT(errp, EINVAL);
		return NULL;
	}
	else return _Dz1Asn1OctetStr_new(src->data, src->size, errp, __file__, __line__);
}

static void _Dz1Asn1OctetStr_purge(Dz1Asn1OctetStr *p)
{
	if (p->data != NULL)
	{
		Dz1Free(p->data);
		p->data = NULL;
	}
	p->size = 0;
}

void Dz1Asn1OctetStr_purge(Dz1Asn1OctetStr *p)
{
	if (!p) return;
	else _Dz1Asn1OctetStr_purge(p);
}

void Dz1Asn1OctetStr_del(Dz1Asn1OctetStr *p)
{
	if (!p) return;
	else
	{
		_Dz1Asn1OctetStr_purge(p);
		Dz1Free(p);
	}
}

void Dz1Asn1OctetStrA_dump(Dz1Asn1OctetStr *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		if (p->size > 128)
		{
			Dz1ThreadA_tprintb(tab, p->data, 128, 16, TRUE);
			Dz1ThreadA_tprintf(tab, "and more data to %u bytes\n", p->size);
		}
		else Dz1ThreadA_tprintb(tab, p->data, p->size, 16, TRUE);
		Dz1ThreadA_tprintf(--tab,  "}\n");
	}
}

void Dz1Asn1OctetStrA_fdump(FILE *fp, Dz1Asn1OctetStr *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n");tab++;
		Dz1ThreadA_ftprintb(fp, tab, p->data, p->size, 16);
		Dz1ThreadA_ftprintf(fp, --tab,  "}\n");
	}
}

#ifndef UNIX_SYSTEM
void Dz1Asn1OctetStrW_dump(Dz1Asn1OctetStr *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n");tab++;
		if (p->size > 128)
		{
			Dz1ThreadW_tprintb(tab, p->data, 128, 16, TRUE);
			Dz1ThreadW_tprintf(tab, L"and more data to %u bytes\n", p->size);
		}
		else Dz1ThreadW_tprintb(tab, p->data, p->size, 16, TRUE);
		Dz1ThreadW_tprintf(--tab,  L"}\n");
	}
}

void Dz1Asn1OctetStrW_fdump(FILE *fp, Dz1Asn1OctetStr *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n");tab++;
		Dz1ThreadW_ftprintb(fp, tab, p->data, p->size, 16);
		Dz1ThreadW_ftprintf(fp, --tab,  L"}\n");
	}
}
#endif

int Dz1Asn1OctetStr_cmp(Dz1Asn1OctetStr *a, Dz1Asn1OctetStr *b)
{
	if		(a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (a->size < b->size) return -1;
	else if (a->size > b->size) return 1;
	else return memcmp(a->data, b->data, a->size);
}

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1OctetStr CODEC
ssize_t Dz1Asn1OctetStr_enc(u8_t *dst, size_t size, Dz1Asn1OctetStr *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		u16_t sz = (u16_t)(src->size & 0xFFFF);
		DZ1_ENCODE2(cp, size, sz, errp, ret);
		DZ1_ENCODE(cp, size, src->data, sz, errp, ret);
	}
	return ret;
}

ssize_t Dz1Asn1OctetStr_dec(Dz1Asn1OctetStr *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t sz = 0;
		DZ1_DECODE2(&sz, cp, size, errp, ret);
		if ((dst->data = (u8_t *)Dz1Malloc(sz, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else DZ1_DECODE(dst->data, (dst->size = sz), cp, size, errp, ret);
	}
	return ret;
}
// Dz1Asn1OctetStr CODEC
////////////////////////////////////////////////////////////////////////////////
