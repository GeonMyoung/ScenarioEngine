#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_tdc_info_test_ref.h"

////////////////////////////////////////////////////////////////////////////////
// TestExternalType API
TestExternalType *TestExternalType_new(int a, int b, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestExternalType *ret = (TestExternalType *)Dz1Calloc(sizeof(TestExternalType), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestExternalType_delAndSetNull, (void *)&ret);

		ret->a = a;
		ret->b = b;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestExternalType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t TestExternalType_copy(TestExternalType *dst, TestExternalType *src, Dz1Error *err)
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

TestExternalType *TestExternalType_clone(TestExternalType *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestExternalType *ret = (TestExternalType *)Dz1Calloc(sizeof(TestExternalType), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestExternalType_delAndSetNull, (void *)&ret);

		// Additional clone code here
		if (TestExternalType_copy(ret, src, errp) == FALSE) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestExternalType_delAndSetNull, (void *)&ret);
	}

	return ret;
}

void TestExternalType_purge(TestExternalType *p)
{
}

void TestExternalType_del(TestExternalType *p)
{
	if (!p) return;
	// Additional delete code here
	TestExternalType_purge(p);
	Dz1Free(p);
}

void TestExternalTypeA_dump(TestExternalType *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("{ a = %d, b = %s }\n", p->a, p->b);
}

void TestExternalTypeA_fdump(FILE *fp, TestExternalType *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "{ a = %d, b = %s }\n", p->a, p->b);
}
#ifndef UNIX_SYSTEM
void TestExternalTypeW_dump(TestExternalType *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"{ a = %d, b = %s }\n", p->a, p->b);
}

void TestExternalTypeW_fdump(FILE *fp, TestExternalType *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadW_fprintf(fp, L"{ a = %d, b = %s }\n", p->a, p->b);
}
#endif
int TestExternalType_cmp(TestExternalType *a, TestExternalType *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if ((ret = (int)(a->a - b->a)) != 0) { }
	else if ((ret = (int)(a->b - b->b)) != 0) { }
	else ret = 0;
	return ret;
}
// TestExternalType API
////////////////////////////////////////////////////////////////////////////////


