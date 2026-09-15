#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_logics_type.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicStringRefArr API
Dz1LogicStringRefArrA *Dz1LogicStringRefArrA_new(size_t arr_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1LogicStringRefArrA *ret = (Dz1LogicStringRefArrA *)Dz1Calloc(sizeof(Dz1LogicStringRefArrA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicStringRefArrA_delAndSetNull, (void *)&ret);

		ret->filled_cnt = 0;
		if (0) { }
		else if ((ret->arr = (str_t *)Dz1Calloc(sizeof(str_t), (ret->alloc_cnt = arr_cnt) + 1, errp)) == NULL) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1LogicStringRefArrA *Dz1LogicStringRefArrA_clone(Dz1LogicStringRefArrA *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1LogicStringRefArrA *ret = (Dz1LogicStringRefArrA *)Dz1Calloc(sizeof(Dz1LogicStringRefArrA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicStringRefArrA_delAndSetNull, (void *)&ret);

		if (0) { }
		// additional clone code here
		else if ((ret->arr = (str_t *)Dz1Calloc(sizeof(str_t), src->alloc_cnt + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			size_t i;
			for (i = 0; errp->code == 0 && i < src->filled_cnt; i++) ret->arr[i] = src->arr[i];
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LogicStringRefArrA_del(Dz1LogicStringRefArrA *p)
{
	if (!p) return;
	// Additional delete code here
	if (p->arr) Dz1Free(p->arr);
	p->arr = NULL;
	Dz1Free(p);
}

void Dz1LogicStringRefArrA_dump(Dz1LogicStringRefArrA *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	else
	{
		size_t i;
		Dz1ThreadA_printf("{\n"); tab++;
		// Additional print code here
		for (i = 0; i < p->filled_cnt; i++)
		{
			Dz1ThreadA_tprintf(tab, "[%u]", i);
			Dz1StrA_dump(p->arr[i], tab);
		}
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}

void Dz1LogicStringRefArrA_fdump(FILE *fp, Dz1LogicStringRefArrA *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	else
	{
		size_t i;
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		// Additional print code here
		for (i = 0; i < p->filled_cnt; i++)
		{
			Dz1ThreadA_ftprintf(fp, tab, "[%u]", i);
			Dz1StrA_fdump(fp, p->arr[i], tab);
		}
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}

Dz1LogicStringRefArrA *Dz1LogicStringRefArrA_build(str_t src[], size_t src_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1LogicStringRefArrA *ret = Dz1LogicStringRefArrA_new(src_cnt, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicStringRefArrA_delAndSetNull, (void *)&ret);
		if (src != NULL || src_cnt > 0)
		{
			for (ret->filled_cnt = 0; ret->filled_cnt < ret->alloc_cnt; ret->filled_cnt++)
				ret->arr[ret->filled_cnt] = src[ret->filled_cnt];
		}
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1LogicStringRefArrA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1LogicStringRefArrW *Dz1LogicStringRefArrW_new(size_t arr_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1LogicStringRefArrW *ret = (Dz1LogicStringRefArrW *)Dz1Calloc(sizeof(Dz1LogicStringRefArrW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicStringRefArrW_delAndSetNull, (void *)&ret);

		ret->filled_cnt = 0;
		if (0) { }
		else if ((ret->arr = (wstr_t *)Dz1Calloc(sizeof(wstr_t), (ret->alloc_cnt = arr_cnt) + 1, errp)) == NULL) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1LogicStringRefArrW *Dz1LogicStringRefArrW_clone(Dz1LogicStringRefArrW *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1LogicStringRefArrW *ret = (Dz1LogicStringRefArrW *)Dz1Calloc(sizeof(Dz1LogicStringRefArrW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicStringRefArrW_delAndSetNull, (void *)&ret);

		if (0) { }
		// additional clone code here
		else if ((ret->arr = (wstr_t *)Dz1Calloc(sizeof(wstr_t), src->alloc_cnt + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			size_t i;
			for (i = 0; errp->code == 0 && i < src->filled_cnt; i++) ret->arr[i] = src->arr[i];
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LogicStringRefArrW_del(Dz1LogicStringRefArrW *p)
{
	if (!p) return;
	// Additional delete code here
	if (p->arr) Dz1Free(p->arr);
	p->arr = NULL;
	Dz1Free(p);
}

void Dz1LogicStringRefArrW_dump(Dz1LogicStringRefArrW *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	else
	{
		size_t i;
		Dz1ThreadW_printf(L"{\n"); tab++;
		// Additional print code here
		for (i = 0; i < p->filled_cnt; i++)
		{
			Dz1ThreadW_tprintf(tab, L"[%u]", i);
			Dz1StrW_dump(p->arr[i], tab);
		}
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}

void Dz1LogicStringRefArrW_fdump(FILE *fp, Dz1LogicStringRefArrW *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	else
	{
		size_t i;
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		// Additional print code here
		for (i = 0; i < p->filled_cnt; i++)
		{
			Dz1ThreadW_ftprintf(fp, tab, L"[%u]", i);
			Dz1StrW_fdump(fp, p->arr[i], tab);
		}
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}

Dz1LogicStringRefArrW *Dz1LogicStringRefArrW_build(wstr_t src[], size_t src_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1LogicStringRefArrW *ret = Dz1LogicStringRefArrW_new(src_cnt, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicStringRefArrW_delAndSetNull, (void *)&ret);
		if (src != NULL || src_cnt > 0)
		{
			for (ret->filled_cnt = 0; ret->filled_cnt < ret->alloc_cnt; ret->filled_cnt++)
				ret->arr[ret->filled_cnt] = src[ret->filled_cnt];
		}
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1LogicStringRefArrW_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif
// Dz1LogicStringRefArr API
////////////////////////////////////////////////////////////////////////////////

