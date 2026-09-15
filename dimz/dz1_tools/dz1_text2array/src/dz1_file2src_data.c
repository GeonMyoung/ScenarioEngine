////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_file2src_data.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1File2SrcDataEntry
Dz1File2SrcDataEntry *Dz1File2SrcDataEntry_new(Dz1Binary *block, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1File2SrcDataEntry *__internal_ret = (Dz1File2SrcDataEntry *)Dz1Calloc(sizeof(Dz1File2SrcDataEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1File2SrcDataEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->block = block;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1File2SrcDataEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1File2SrcDataEntry_purge(Dz1File2SrcDataEntry *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->block);
}

void Dz1File2SrcDataEntry_del(Dz1File2SrcDataEntry *p)
{
	if (p == NULL) return;
	Dz1File2SrcDataEntry_purge(p);
	Dz1Free(p);
}

void Dz1File2SrcDataEntry_dump(Dz1File2SrcDataEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_printf(Dz1T("block = ")); Dz1Binary_dump(p->block, tab); 
	}
}
// Dz1File2SrcDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1File2SrcDataList
static Dz1Error Dz1File2SrcDataList_add(Dz1File2SrcDataList *p, Dz1File2SrcDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1File2SrcDataListMkArrArg
{
	Dz1File2SrcDataEntry **arr;
	unsigned int idx;
} Dz1File2SrcDataListMkArrArg;

static Dz1Error _Dz1File2SrcDataList_get_array(void *ptr, Dz1File2SrcDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1File2SrcDataListMkArrArg *arg = (Dz1File2SrcDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1File2SrcDataEntry **Dz1File2SrcDataList_get_array(Dz1File2SrcDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1File2SrcDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1File2SrcDataEntry **)Dz1Calloc(sizeof(Dz1File2SrcDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1File2SrcDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1File2SrcDataList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error Dz1File2SrcDataList_travelForward(Dz1File2SrcDataList *p, Dz1Error (*func)(void *ptr, Dz1File2SrcDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1File2SrcDataList_travelBackward(Dz1File2SrcDataList *p, Dz1Error (*func)(void *ptr, Dz1File2SrcDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1File2SrcDataEntry *Dz1File2SrcDataList_getHead(Dz1File2SrcDataList *p)
{
	return (Dz1File2SrcDataEntry *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int Dz1File2SrcDataList_count(Dz1File2SrcDataList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1File2SrcDataList *Dz1File2SrcDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1File2SrcDataList *ret = (Dz1File2SrcDataList *)Dz1Calloc(sizeof(Dz1File2SrcDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1File2SrcDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1File2SrcDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1File2SrcDataList_count;
			ret->travel = Dz1File2SrcDataList_travelForward;
			ret->travelForward = Dz1File2SrcDataList_travelForward;
			ret->travelBackward = Dz1File2SrcDataList_travelBackward;
			ret->get_array = Dz1File2SrcDataList_get_array;
			ret->add = Dz1File2SrcDataList_add;
			ret->getHead = Dz1File2SrcDataList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1File2SrcDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1File2SrcDataList_purge(Dz1File2SrcDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1File2SrcDataList_del(Dz1File2SrcDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1File2SrcDataList_dump(void *ptr, Dz1File2SrcDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1File2SrcDataEntry_dump(p, tab);
	return err;
}

void Dz1File2SrcDataList_dump(Dz1File2SrcDataList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1File2SrcDataList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1File2SrcDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1File2SrcData
Dz1File2SrcData *Dz1File2SrcData_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1File2SrcData *__internal_ret = (Dz1File2SrcData *)Dz1Calloc(sizeof(Dz1File2SrcData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1File2SrcData_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->list = Dz1File2SrcDataList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1File2SrcData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1File2SrcData_purge(Dz1File2SrcData *p)
{
	if (p == NULL) return;
	Dz1File2SrcDataList_del(p->list);
}

void Dz1File2SrcData_del(Dz1File2SrcData *p)
{
	if (p == NULL) return;
	Dz1File2SrcData_purge(p);
	Dz1Free(p);
}

void Dz1File2SrcData_dump(Dz1File2SrcData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("list = ")); Dz1File2SrcDataList_dump(p->list, tab); 
	}
}
// Dz1File2SrcData
////////////////////////////////////////////////////////////////////////////////

