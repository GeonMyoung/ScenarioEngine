////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_storage_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageChunkEntry
Dz1StorageChunkEntry *Dz1StorageChunkEntry_new(u32_t idx, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StorageChunkEntry *__internal_ret = (Dz1StorageChunkEntry *)Dz1Calloc(sizeof(Dz1StorageChunkEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1StorageChunkEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->idx = idx;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1StorageChunkEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1StorageChunkEntry_purge(Dz1StorageChunkEntry *p)
{
	if (p == NULL) return;
}

void Dz1StorageChunkEntry_del(Dz1StorageChunkEntry *p)
{
	if (p == NULL) return;
	Dz1StorageChunkEntry_purge(p);
	Dz1Free(p);
}

void Dz1StorageChunkEntry_dump(Dz1StorageChunkEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("idx = ")); Dz1u32_dump(&p->idx, tab); 
	}
}
int Dz1StorageChunkEntry_cmp(Dz1StorageChunkEntry *a, Dz1StorageChunkEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->idx, &b->idx)) != 0) { }
	return ret;
}
// Dz1StorageChunkEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageChunkList
static Dz1Error Dz1StorageChunkList_add(Dz1StorageChunkList *p, Dz1StorageChunkEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t Dz1StorageChunkList_remove(Dz1StorageChunkList *p, Dz1StorageChunkEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1StorageChunkEntry *Dz1StorageChunkList_extract(Dz1StorageChunkList *p, Dz1StorageChunkEntry *key)
{
	return (Dz1StorageChunkEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1StorageChunkListMkArrArg
{
	Dz1StorageChunkEntry **arr;
	unsigned int idx;
} Dz1StorageChunkListMkArrArg;

static Dz1Error _Dz1StorageChunkList_get_array(void *ptr, Dz1StorageChunkEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1StorageChunkListMkArrArg *arg = (Dz1StorageChunkListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1StorageChunkEntry **Dz1StorageChunkList_get_array(Dz1StorageChunkList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1StorageChunkEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1StorageChunkEntry **)Dz1Calloc(sizeof(Dz1StorageChunkEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1StorageChunkListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1StorageChunkList_get_array, (void *)&arg);
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

static Dz1Error Dz1StorageChunkList_travelForward(Dz1StorageChunkList *p, Dz1Error (*func)(void *ptr, Dz1StorageChunkEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1StorageChunkList_travelBackward(Dz1StorageChunkList *p, Dz1Error (*func)(void *ptr, Dz1StorageChunkEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1StorageChunkEntry *Dz1StorageChunkList_find(Dz1StorageChunkList *p, Dz1StorageChunkEntry *key)
{
	return (Dz1StorageChunkEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1StorageChunkList_count(Dz1StorageChunkList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1StorageChunkList *Dz1StorageChunkList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StorageChunkList *ret = (Dz1StorageChunkList *)Dz1Calloc(sizeof(Dz1StorageChunkList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageChunkList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1StorageChunkEntry_cmp,
				(Dz1DelFunc)Dz1StorageChunkEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1StorageChunkList_count;
			ret->travel = Dz1StorageChunkList_travelForward;
			ret->travelForward = Dz1StorageChunkList_travelForward;
			ret->travelBackward = Dz1StorageChunkList_travelBackward;
			ret->get_array = Dz1StorageChunkList_get_array;
			ret->add = Dz1StorageChunkList_add;
			ret->remove = Dz1StorageChunkList_remove;
			ret->find = Dz1StorageChunkList_find;
			ret->extract = Dz1StorageChunkList_extract;
			ret->cmp = Dz1StorageChunkEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1StorageChunkList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1StorageChunkList_purge(Dz1StorageChunkList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1StorageChunkList_del(Dz1StorageChunkList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1StorageChunkList_dump(void *ptr, Dz1StorageChunkEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1StorageChunkEntry_dump(p, tab);
	return err;
}

void Dz1StorageChunkList_dump(Dz1StorageChunkList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1StorageChunkList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1StorageChunkList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageBlock
Dz1StorageBlock *Dz1StorageBlock_new(u32_t idx, 
									 u32_t prev_idx, 
									 u32_t next_idx, 
									 u32_t flag, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StorageBlock *__internal_ret = (Dz1StorageBlock *)Dz1Calloc(sizeof(Dz1StorageBlock), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1StorageBlock_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->idx = idx;
		__internal_ret->prev_idx = prev_idx;
		__internal_ret->next_idx = next_idx;
		__internal_ret->flag = flag;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1StorageBlock_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1StorageBlock_purge(Dz1StorageBlock *p)
{
	if (p == NULL) return;
}

void Dz1StorageBlock_del(Dz1StorageBlock *p)
{
	if (p == NULL) return;
	Dz1StorageBlock_purge(p);
	Dz1Free(p);
}

int Dz1StorageBlock_cmp(Dz1StorageBlock *a, Dz1StorageBlock *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->idx, &b->idx)) != 0) { }
	return ret;
}
// Dz1StorageBlock
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageBlockList
static Dz1Error Dz1StorageBlockList_add(Dz1StorageBlockList *p, Dz1StorageBlock *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t Dz1StorageBlockList_remove(Dz1StorageBlockList *p, Dz1StorageBlock *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1StorageBlock *Dz1StorageBlockList_extract(Dz1StorageBlockList *p, Dz1StorageBlock *key)
{
	return (Dz1StorageBlock *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1StorageBlockListMkArrArg
{
	Dz1StorageBlock **arr;
	unsigned int idx;
} Dz1StorageBlockListMkArrArg;

static Dz1Error _Dz1StorageBlockList_get_array(void *ptr, Dz1StorageBlock *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1StorageBlockListMkArrArg *arg = (Dz1StorageBlockListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1StorageBlock **Dz1StorageBlockList_get_array(Dz1StorageBlockList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1StorageBlock **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1StorageBlock **)Dz1Calloc(sizeof(Dz1StorageBlock *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1StorageBlockListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1StorageBlockList_get_array, (void *)&arg);
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

static Dz1Error Dz1StorageBlockList_travelForward(Dz1StorageBlockList *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1StorageBlockList_travelBackward(Dz1StorageBlockList *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1StorageBlock *Dz1StorageBlockList_find(Dz1StorageBlockList *p, Dz1StorageBlock *key)
{
	return (Dz1StorageBlock *)Dz1AATree_find(p->storage, key);
}

static Dz1StorageBlock *Dz1StorageBlockList_getHead(Dz1StorageBlockList *p)
{
	return (Dz1StorageBlock *)Dz1AATree_getHead(p->storage);
}

static unsigned int Dz1StorageBlockList_count(Dz1StorageBlockList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1StorageBlockList *Dz1StorageBlockList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StorageBlockList *ret = (Dz1StorageBlockList *)Dz1Calloc(sizeof(Dz1StorageBlockList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageBlockList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1StorageBlock_cmp,
				(Dz1DelFunc)Dz1StorageBlock_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1StorageBlockList_count;
			ret->travel = Dz1StorageBlockList_travelForward;
			ret->travelForward = Dz1StorageBlockList_travelForward;
			ret->travelBackward = Dz1StorageBlockList_travelBackward;
			ret->get_array = Dz1StorageBlockList_get_array;
			ret->add = Dz1StorageBlockList_add;
			ret->remove = Dz1StorageBlockList_remove;
			ret->find = Dz1StorageBlockList_find;
			ret->extract = Dz1StorageBlockList_extract;
			ret->getHead = Dz1StorageBlockList_getHead;
			ret->cmp = Dz1StorageBlock_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1StorageBlockList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1StorageBlockList_purge(Dz1StorageBlockList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1StorageBlockList_del(Dz1StorageBlockList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1StorageBlockList_dump(void *ptr, Dz1StorageBlock *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1StorageBlock_dump(p, tab);
	return err;
}

void Dz1StorageBlockList_dump(Dz1StorageBlockList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1StorageBlockList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1StorageBlockList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageBlockArray
static Dz1Error Dz1StorageBlockArray_add(Dz1StorageBlockArray *p, Dz1StorageBlock *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1StorageBlockArrayMkArrArg
{
	Dz1StorageBlock **arr;
	unsigned int idx;
} Dz1StorageBlockArrayMkArrArg;

static Dz1Error _Dz1StorageBlockArray_get_array(void *ptr, Dz1StorageBlock *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1StorageBlockArrayMkArrArg *arg = (Dz1StorageBlockArrayMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1StorageBlock **Dz1StorageBlockArray_get_array(Dz1StorageBlockArray *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1StorageBlock **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1StorageBlock **)Dz1Calloc(sizeof(Dz1StorageBlock *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1StorageBlockArrayMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1StorageBlockArray_get_array, (void *)&arg);
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

static Dz1Error Dz1StorageBlockArray_travelForward(Dz1StorageBlockArray *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1StorageBlockArray_travelBackward(Dz1StorageBlockArray *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1StorageBlockArray_count(Dz1StorageBlockArray *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1StorageBlockArray *Dz1StorageBlockArray_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StorageBlockArray *ret = (Dz1StorageBlockArray *)Dz1Calloc(sizeof(Dz1StorageBlockArray), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageBlockArray_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1StorageBlockArray_count;
			ret->travel = Dz1StorageBlockArray_travelForward;
			ret->travelForward = Dz1StorageBlockArray_travelForward;
			ret->travelBackward = Dz1StorageBlockArray_travelBackward;
			ret->get_array = Dz1StorageBlockArray_get_array;
			ret->add = Dz1StorageBlockArray_add;
			ret->cmp = Dz1StorageBlock_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1StorageBlockArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1StorageBlockArray_clone(void *ptr, Dz1StorageBlock *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1StorageBlockArray *p = (Dz1StorageBlockArray *)ptr;
	Dz1StorageBlock *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1StorageBlockArray *Dz1StorageBlockArray_clone(Dz1StorageBlockArray *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StorageBlockArray *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1StorageBlockArray_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageBlockArray_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1StorageBlockArray_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1StorageBlockArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1StorageBlockArray_purge(Dz1StorageBlockArray *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1StorageBlockArray_del(Dz1StorageBlockArray *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1StorageBlockArray_dump(void *ptr, Dz1StorageBlock *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1StorageBlock_dump(p, tab);
	return err;
}

void Dz1StorageBlockArray_dump(Dz1StorageBlockArray *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1StorageBlockArray_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1StorageBlockArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageArchive
Dz1StorageArchive *Dz1StorageArchive_new(u32_t entry_idx, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StorageArchive *__internal_ret = (Dz1StorageArchive *)Dz1Calloc(sizeof(Dz1StorageArchive), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1StorageArchive_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->blocks = Dz1StorageBlockArray_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->entry_idx = entry_idx;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1StorageArchive_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1StorageArchive_purge(Dz1StorageArchive *p)
{
	if (p == NULL) return;
	Dz1StorageBlockArray_del(p->blocks);
}

void Dz1StorageArchive_del(Dz1StorageArchive *p)
{
	if (p == NULL) return;
	Dz1StorageArchive_purge(p);
	Dz1Free(p);
}

void Dz1StorageArchive_dump(Dz1StorageArchive *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("entry_idx = ")); Dz1u32_dump(&p->entry_idx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("blocks = ")); Dz1StorageBlockArray_dump(p->blocks, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1StorageArchive_cmp(Dz1StorageArchive *a, Dz1StorageArchive *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->entry_idx, &b->entry_idx)) != 0) { }
	return ret;
}
// Dz1StorageArchive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageArchiveList
static Dz1Error Dz1StorageArchiveList_add(Dz1StorageArchiveList *p, Dz1StorageArchive *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t Dz1StorageArchiveList_remove(Dz1StorageArchiveList *p, Dz1StorageArchive *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1StorageArchive *Dz1StorageArchiveList_extract(Dz1StorageArchiveList *p, Dz1StorageArchive *key)
{
	return (Dz1StorageArchive *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1StorageArchiveListMkArrArg
{
	Dz1StorageArchive **arr;
	unsigned int idx;
} Dz1StorageArchiveListMkArrArg;

static Dz1Error _Dz1StorageArchiveList_get_array(void *ptr, Dz1StorageArchive *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1StorageArchiveListMkArrArg *arg = (Dz1StorageArchiveListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1StorageArchive **Dz1StorageArchiveList_get_array(Dz1StorageArchiveList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1StorageArchive **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1StorageArchive **)Dz1Calloc(sizeof(Dz1StorageArchive *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1StorageArchiveListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1StorageArchiveList_get_array, (void *)&arg);
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

static Dz1Error Dz1StorageArchiveList_travelForward(Dz1StorageArchiveList *p, Dz1Error (*func)(void *ptr, Dz1StorageArchive *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1StorageArchiveList_travelBackward(Dz1StorageArchiveList *p, Dz1Error (*func)(void *ptr, Dz1StorageArchive *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1StorageArchive *Dz1StorageArchiveList_find(Dz1StorageArchiveList *p, Dz1StorageArchive *key)
{
	return (Dz1StorageArchive *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1StorageArchiveList_count(Dz1StorageArchiveList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1StorageArchiveList *Dz1StorageArchiveList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StorageArchiveList *ret = (Dz1StorageArchiveList *)Dz1Calloc(sizeof(Dz1StorageArchiveList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageArchiveList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1StorageArchive_cmp,
				(Dz1DelFunc)Dz1StorageArchive_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1StorageArchiveList_count;
			ret->travel = Dz1StorageArchiveList_travelForward;
			ret->travelForward = Dz1StorageArchiveList_travelForward;
			ret->travelBackward = Dz1StorageArchiveList_travelBackward;
			ret->get_array = Dz1StorageArchiveList_get_array;
			ret->add = Dz1StorageArchiveList_add;
			ret->remove = Dz1StorageArchiveList_remove;
			ret->find = Dz1StorageArchiveList_find;
			ret->extract = Dz1StorageArchiveList_extract;
			ret->cmp = Dz1StorageArchive_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1StorageArchiveList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1StorageArchiveList_purge(Dz1StorageArchiveList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1StorageArchiveList_del(Dz1StorageArchiveList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1StorageArchiveList_dump(void *ptr, Dz1StorageArchive *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1StorageArchive_dump(p, tab);
	return err;
}

void Dz1StorageArchiveList_dump(Dz1StorageArchiveList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1StorageArchiveList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1StorageArchiveList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageInfo
Dz1StorageInfo *Dz1StorageInfo_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StorageInfo *__internal_ret = (Dz1StorageInfo *)Dz1Calloc(sizeof(Dz1StorageInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1StorageInfo_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->blocks = Dz1StorageBlockList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->spaces = Dz1StorageBlockArray_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->archives = Dz1StorageArchiveList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->missings = Dz1StorageBlockArray_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->collisions = Dz1StorageBlockArray_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1StorageInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1StorageInfo_purge(Dz1StorageInfo *p)
{
	if (p == NULL) return;
	Dz1StorageBlockList_del(p->blocks);
	Dz1StorageBlockArray_del(p->spaces);
	Dz1StorageArchiveList_del(p->archives);
	Dz1StorageBlockArray_del(p->missings);
	Dz1StorageBlockArray_del(p->collisions);
}

void Dz1StorageInfo_del(Dz1StorageInfo *p)
{
	if (p == NULL) return;
	Dz1StorageInfo_purge(p);
	Dz1Free(p);
}

void Dz1StorageInfo_dump(Dz1StorageInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("blocks = ")); Dz1StorageBlockList_dump(p->blocks, tab); 
		Dz1Thread_tprintf(tab, Dz1T("spaces = ")); Dz1StorageBlockArray_dump(p->spaces, tab); 
		Dz1Thread_tprintf(tab, Dz1T("archives = ")); Dz1StorageArchiveList_dump(p->archives, tab); 
		Dz1Thread_tprintf(tab, Dz1T("missings = ")); Dz1StorageBlockArray_dump(p->missings, tab); 
		Dz1Thread_tprintf(tab, Dz1T("collisions = ")); Dz1StorageBlockArray_dump(p->collisions, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1StorageInfo
////////////////////////////////////////////////////////////////////////////////

