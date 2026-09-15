#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_tdc_info_test_types.h"

////////////////////////////////////////////////////////////////////////////////
// TestTypeInfo API
TestTypeInfo *TestTypeInfo_new(int a, int b, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestTypeInfo *ret = (TestTypeInfo *)Dz1Calloc(sizeof(TestTypeInfo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestTypeInfo_delAndSetNull, (void *)&ret);

		ret->a = a;
		ret->b = b;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestTypeInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t TestTypeInfo_copy(TestTypeInfo *dst, TestTypeInfo *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->a = src->a;
		dst->b = src->b;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

TestTypeInfo *TestTypeInfo_clone(TestTypeInfo *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestTypeInfo *ret = (TestTypeInfo *)Dz1Calloc(sizeof(TestTypeInfo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestTypeInfo_delAndSetNull, (void *)&ret);

		// Additional clone code here
		if (TestTypeInfo_copy(ret, src, errp) == FALSE) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestTypeInfo_delAndSetNull, (void *)&ret);
	}

	return ret;
}

void TestTypeInfo_purge(TestTypeInfo *p)
{
	return;
}

void TestTypeInfo_del(TestTypeInfo *p)
{
	if (!p) return;
	// Additional delete code here
	TestTypeInfo_purge(p);
	Dz1Free(p);
}

void TestTypeInfoA_dump(TestTypeInfo *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("{ a = %d, b = %d }\n", p->a, p->b);
}

void TestTypeInfoA_fdump(FILE *fp, TestTypeInfo *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "{ a = %d, b = %d }\n", p->a, p->b);
}
#ifndef UNIX_SYSTEM
void TestTypeInfoW_dump(TestTypeInfo *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"{ a = %d, b = %d }\n", p->a, p->b);
}

void TestTypeInfoW_fdump(FILE *fp, TestTypeInfo *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"{ a = %d, b = %d }\n", p->a, p->b);
}
#endif // UNIX_SYSTEM

int TestTypeInfo_cmp(TestTypeInfo *a, TestTypeInfo *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if ((ret = (int)(a->a - b->b)) != 0) { }
	else if ((ret = (int)(a->b - b->b)) != 0) { }
	else ret = 0;
	return ret;
}
// TestTypeInfo API
////////////////////////////////////////////////////////////////////////////////

