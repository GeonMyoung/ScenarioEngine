#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_tdq_types.h"

Dz1TdqPageSpec *Dz1TdqPageSpec_new(u32_t pg_size, u32_t pg_num, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqPageSpec *ret = (Dz1TdqPageSpec *)Dz1Calloc(sizeof(Dz1TdqPageSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->pg_size = pg_size;
		ret->pg_num = pg_num;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1TdqPageSpec *Dz1TdqPageSpec_clone(Dz1TdqPageSpec *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqPageSpec *ret = Dz1TdqPageSpec_new(src->pg_size, src->pg_num, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1TdqPageSpec_del(Dz1TdqPageSpec *p)
{
	if (p != NULL) Dz1Free(p);
}

void Dz1TdqPageSpec_dump(Dz1TdqPageSpec *p, int tab)
{
	if (p == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("(%u/%u)\n"), p->pg_num, p->pg_size);
}

