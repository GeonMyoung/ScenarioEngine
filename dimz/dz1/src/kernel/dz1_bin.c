#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_bin.h>

static Dz1Error _Dz1Binary_data(Dz1Binary *ret, u8_t *data, u32_t size, const char *__file__, int __line__)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (data == DZ1_BIN_DATA_ALLOC)
	{
		if ((ret->data = (u8_t *)_Dz1Malloc(size, &err, __file__, __line__)) == NULL) ERR_OUT(&err);
	}
	else if (data != NULL)
	{
		if ((ret->data = (u8_t *)_Dz1Memory_clone(data, size, &err, __file__, __line__)) == NULL) ERR_OUT(&err);
	}
	return err;
}

Dz1Binary *_Dz1Binary_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Binary *ret = (Dz1Binary *)_Dz1Calloc(sizeof(Dz1Binary), 1, errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
		ret->size = size;
		Dz1Error_set(errp, 0);

		if (size > 0 && (*errp = _Dz1Binary_data(ret, data, size, __file__, __line__)).code) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void *Dz1Binary_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

bool_t _Dz1Binary_copy(Dz1Binary *dst, Dz1Binary *src, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->data != NULL) ERR_SET_OUT(errp, EEXIST);
	else if (src->data == NULL || src->size == 0) ERR_SET_OUT(errp, ENOENT);
	else if ((dst->data = _Dz1Memory_clone(src->data, (dst->size = src->size), errp, __file__, __line__)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

Dz1Binary *_Dz1Binary_clone(Dz1Binary *src, Dz1Error *err, const char *__file__, int __line__)
{ 
	return _Dz1Binary_new(src->data, src->size, err, __file__, __line__);
}

static void _Dz1Binary_purge(Dz1Binary *p)
{
	if (p->data != NULL)
	{
		Dz1Free(p->data);
		p->data = NULL;
	}
	p->size = 0;
}

void Dz1Binary_purge(Dz1Binary *p)
{
	if (p != NULL) _Dz1Binary_purge(p);
}

void Dz1Binary_del(Dz1Binary *p)
{
	if (p != NULL)
	{
		_Dz1Binary_purge(p);
		Dz1Free(p);
	}
}

void Dz1BinaryA_dump(Dz1Binary *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else if (p->data == NULL) Dz1ThreadA_printf("Data NULL\n");
	else if (p->size == 0) Dz1ThreadA_printf("Empty\n");
	else
	{
		Dz1ThreadA_printf("{ %u Byte\n", p->size);
		Dz1ThreadA_tprintb(tab + 1, p->data, p->size, 16, TRUE);
		Dz1ThreadA_tprintf(tab, "}\n");
	}
}

void Dz1BinaryA_dumpPartial(Dz1Binary *p, int tab, size_t dump_size)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else if (p->data == NULL) Dz1ThreadA_printf("Data NULL\n");
	else if (p->size == 0) Dz1ThreadA_printf("Empty\n");
	else
	{
		dump_size = p->size < dump_size ? p->size : dump_size;

		Dz1ThreadA_printf("{ %u Byte\n", p->size);
		Dz1ThreadA_tprintb(tab + 1, p->data, dump_size, 16, TRUE);
		Dz1ThreadA_tprintf(tab, "}\n");
	}
}

void Dz1BinaryA_fdump(FILE *fp, Dz1Binary *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else if (p->data == NULL) Dz1ThreadA_printf("Data NULL\n");
	else if (p->size == 0) Dz1ThreadA_fprintf(fp, "Empty\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n");
		Dz1ThreadA_ftprintb(fp, tab + 1, p->data, p->size, 16);
		Dz1ThreadA_ftprintf(fp, tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1BinaryW_dump(Dz1Binary *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else if (p->data == NULL) Dz1ThreadW_printf(L"Data NULL\n");
	else if (p->size == 0) Dz1ThreadW_printf(L"Empty\n");
	else
	{
		Dz1ThreadW_printf(L"{ %u Byte\n", p->size);
		Dz1ThreadW_tprintb(tab + 1, p->data, p->size, 16, TRUE);
		Dz1ThreadW_tprintf(tab, L"}\n");
	}
}

void Dz1BinaryW_dumpPartial(Dz1Binary *p, int tab, size_t dump_size)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else if (p->data == NULL) Dz1ThreadW_printf(L"Data NULL\n");
	else if (p->size == 0) Dz1ThreadW_printf(L"Empty\n");
	else
	{
		dump_size = p->size < dump_size ? p->size : dump_size;

		Dz1ThreadW_printf(L"{ %u Byte\n", p->size);
		Dz1ThreadW_tprintb(tab + 1, p->data, dump_size, 16, TRUE);
		Dz1ThreadW_tprintf(tab, L"}\n");
	}
}

void Dz1BinaryW_fdump(FILE *fp, Dz1Binary *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else if (p->data == NULL) Dz1ThreadW_printf(L"Data NULL\n");
	else if (p->size == 0) Dz1ThreadW_fprintf(fp, L"Empty\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n");
		Dz1ThreadW_ftprintb(fp, tab + 1, p->data, p->size, 16);
		Dz1ThreadW_ftprintf(fp, tab, L"}\n");
	}
}
#endif
int Dz1Binary_cmp(Dz1Binary *a, Dz1Binary *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /*&& b != NULL*/) ret = -1;
	else if (/*a != NULL &&*/ b == NULL) ret = 1;
	else if (a->size < b->size) ret = -1;
	else if (a->size > b->size) ret = 1;
	else if (a->data == NULL && b->data == NULL) ret = 0;
	else if (a->data == NULL /*&& b->data != NULL*/) ret = -1;
	else if (/*a->data != NULL &&*/ b->data == NULL) ret = 1;
	else ret = memcmp(a->data, b->data, a->size);
	return ret;
}

