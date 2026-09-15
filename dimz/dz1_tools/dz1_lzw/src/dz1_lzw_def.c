////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_lzw_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictData
Dz1LzwDictData *Dz1LzwDictData_new(u32_t code, Dz1Binary *bin, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictData *__internal_ret = (Dz1LzwDictData *)Dz1Calloc(sizeof(Dz1LzwDictData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LzwDictData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->code = code;
		__internal_ret->bin = bin;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1LzwDictData_purge(Dz1LzwDictData *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->bin);
}

void Dz1LzwDictData_del(Dz1LzwDictData *p)
{
	if (p == NULL) return;
	Dz1LzwDictData_purge(p);
	Dz1Free(p);
}

void Dz1LzwDictData_dump(Dz1LzwDictData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("code = ")); Dz1u32_dump(&p->code, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("bin = ")); Dz1Binary_dump(p->bin, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1LzwDictData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictDataArray
static Dz1Error Dz1LzwDictDataArray_add(Dz1LzwDictDataArray *p, Dz1LzwDictData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1LzwDictDataArrayMkArrArg
{
	Dz1LzwDictData **arr;
	unsigned int idx;
} Dz1LzwDictDataArrayMkArrArg;

static Dz1Error _Dz1LzwDictDataArray_get_array(void *ptr, Dz1LzwDictData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LzwDictDataArrayMkArrArg *arg = (Dz1LzwDictDataArrayMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1LzwDictData **Dz1LzwDictDataArray_get_array(Dz1LzwDictDataArray *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1LzwDictData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1LzwDictData **)Dz1Calloc(sizeof(Dz1LzwDictData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1LzwDictDataArrayMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1LzwDictDataArray_get_array, (void *)&arg);
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

static Dz1Error Dz1LzwDictDataArray_travelForward(Dz1LzwDictDataArray *p, Dz1Error (*func)(void *ptr, Dz1LzwDictData *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1LzwDictDataArray_travelBackward(Dz1LzwDictDataArray *p, Dz1Error (*func)(void *ptr, Dz1LzwDictData *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1LzwDictDataArray_count(Dz1LzwDictDataArray *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1LzwDictDataArray *Dz1LzwDictDataArray_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictDataArray *ret = (Dz1LzwDictDataArray *)Dz1Calloc(sizeof(Dz1LzwDictDataArray), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LzwDictDataArray_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1LzwDictData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1LzwDictDataArray_count;
			ret->travel = Dz1LzwDictDataArray_travelForward;
			ret->travelForward = Dz1LzwDictDataArray_travelForward;
			ret->travelBackward = Dz1LzwDictDataArray_travelBackward;
			ret->get_array = Dz1LzwDictDataArray_get_array;
			ret->add = Dz1LzwDictDataArray_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictDataArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LzwDictDataArray_purge(Dz1LzwDictDataArray *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1LzwDictDataArray_del(Dz1LzwDictDataArray *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1LzwDictDataArray_dump(void *ptr, Dz1LzwDictData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1LzwDictData_dump(p, tab);
	return err;
}

void Dz1LzwDictDataArray_dump(Dz1LzwDictDataArray *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1LzwDictDataArray_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1LzwDictDataArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictWord
Dz1LzwDictWord *Dz1LzwDictWord_new(u32_t code, Dz1Binary *bin, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictWord *__internal_ret = (Dz1LzwDictWord *)Dz1Calloc(sizeof(Dz1LzwDictWord), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LzwDictWord_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->code = code;
		__internal_ret->bin = bin;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictWord_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1LzwDictWord_purge(Dz1LzwDictWord *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->bin);
}

void Dz1LzwDictWord_del(Dz1LzwDictWord *p)
{
	if (p == NULL) return;
	Dz1LzwDictWord_purge(p);
	Dz1Free(p);
}

void Dz1LzwDictWord_dump(Dz1LzwDictWord *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("code = ")); Dz1u32_dump(&p->code, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("bin = ")); Dz1Binary_dump(p->bin, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1LzwDictWord_cmp(Dz1LzwDictWord *a, Dz1LzwDictWord *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->bin == NULL && b->bin == NULL) ret = 0;
	else if (a->bin == NULL /*&& b->bin != NULL*/) ret = -1;
	else if (/*a->bin != NULL &&*/ b->bin == NULL) ret = 1;
	else if ((ret = Dz1Binary_cmp(a->bin, b->bin)) != 0) { }
	return ret;
}
// Dz1LzwDictWord
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictWordList
static Dz1Error Dz1LzwDictWordList_add(Dz1LzwDictWordList *p, Dz1LzwDictWord *data)
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

static bool_t Dz1LzwDictWordList_remove(Dz1LzwDictWordList *p, Dz1LzwDictWord *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1LzwDictWord *Dz1LzwDictWordList_extract(Dz1LzwDictWordList *p, Dz1LzwDictWord *key)
{
	return (Dz1LzwDictWord *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1LzwDictWordListMkArrArg
{
	Dz1LzwDictWord **arr;
	unsigned int idx;
} Dz1LzwDictWordListMkArrArg;

static Dz1Error _Dz1LzwDictWordList_get_array(void *ptr, Dz1LzwDictWord *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LzwDictWordListMkArrArg *arg = (Dz1LzwDictWordListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1LzwDictWord **Dz1LzwDictWordList_get_array(Dz1LzwDictWordList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1LzwDictWord **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1LzwDictWord **)Dz1Calloc(sizeof(Dz1LzwDictWord *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1LzwDictWordListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1LzwDictWordList_get_array, (void *)&arg);
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

static Dz1Error Dz1LzwDictWordList_travelForward(Dz1LzwDictWordList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictWord *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1LzwDictWordList_travelBackward(Dz1LzwDictWordList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictWord *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1LzwDictWord *Dz1LzwDictWordList_find(Dz1LzwDictWordList *p, Dz1LzwDictWord *key)
{
	return (Dz1LzwDictWord *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1LzwDictWordList_count(Dz1LzwDictWordList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1LzwDictWordList *Dz1LzwDictWordList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictWordList *ret = (Dz1LzwDictWordList *)Dz1Calloc(sizeof(Dz1LzwDictWordList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LzwDictWordList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1LzwDictWord_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1LzwDictWordList_count;
			ret->travel = Dz1LzwDictWordList_travelForward;
			ret->travelForward = Dz1LzwDictWordList_travelForward;
			ret->travelBackward = Dz1LzwDictWordList_travelBackward;
			ret->get_array = Dz1LzwDictWordList_get_array;
			ret->add = Dz1LzwDictWordList_add;
			ret->remove = Dz1LzwDictWordList_remove;
			ret->find = Dz1LzwDictWordList_find;
			ret->extract = Dz1LzwDictWordList_extract;
			ret->cmp = Dz1LzwDictWord_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictWordList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1LzwDictWordList_clone(void *ptr, Dz1LzwDictWord *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LzwDictWordList *p = (Dz1LzwDictWordList *)ptr;
	Dz1LzwDictWord *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1LzwDictWordList *Dz1LzwDictWordList_clone(Dz1LzwDictWordList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictWordList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1LzwDictWordList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LzwDictWordList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1LzwDictWordList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictWordList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LzwDictWordList_purge(Dz1LzwDictWordList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1LzwDictWordList_del(Dz1LzwDictWordList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1LzwDictWordList_dump(void *ptr, Dz1LzwDictWord *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1LzwDictWord_dump(p, tab);
	return err;
}

void Dz1LzwDictWordList_dump(Dz1LzwDictWordList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1LzwDictWordList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1LzwDictWordList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictSizeNode
Dz1LzwDictSizeNode *Dz1LzwDictSizeNode_new(u32_t size, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictSizeNode *__internal_ret = (Dz1LzwDictSizeNode *)Dz1Calloc(sizeof(Dz1LzwDictSizeNode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LzwDictSizeNode_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->list = Dz1LzwDictWordList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->size = size;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictSizeNode_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1LzwDictSizeNode_purge(Dz1LzwDictSizeNode *p)
{
	if (p == NULL) return;
	Dz1LzwDictWordList_del(p->list);
}

void Dz1LzwDictSizeNode_del(Dz1LzwDictSizeNode *p)
{
	if (p == NULL) return;
	Dz1LzwDictSizeNode_purge(p);
	Dz1Free(p);
}

void Dz1LzwDictSizeNode_dump(Dz1LzwDictSizeNode *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("size = ")); Dz1u32_dump(&p->size, tab); 
		Dz1Thread_tprintf(tab, Dz1T("list = ")); Dz1LzwDictWordList_dump(p->list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1LzwDictSizeNode_cmp(Dz1LzwDictSizeNode *a, Dz1LzwDictSizeNode *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->size, &b->size)) != 0) { }
	return ret;
}
// Dz1LzwDictSizeNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictSizeTable
static Dz1Error Dz1LzwDictSizeTable_add(Dz1LzwDictSizeTable *p, Dz1LzwDictSizeNode *data)
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

static bool_t Dz1LzwDictSizeTable_remove(Dz1LzwDictSizeTable *p, Dz1LzwDictSizeNode *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1LzwDictSizeNode *Dz1LzwDictSizeTable_extract(Dz1LzwDictSizeTable *p, Dz1LzwDictSizeNode *key)
{
	return (Dz1LzwDictSizeNode *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1LzwDictSizeTableMkArrArg
{
	Dz1LzwDictSizeNode **arr;
	unsigned int idx;
} Dz1LzwDictSizeTableMkArrArg;

static Dz1Error _Dz1LzwDictSizeTable_get_array(void *ptr, Dz1LzwDictSizeNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LzwDictSizeTableMkArrArg *arg = (Dz1LzwDictSizeTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1LzwDictSizeNode **Dz1LzwDictSizeTable_get_array(Dz1LzwDictSizeTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1LzwDictSizeNode **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1LzwDictSizeNode **)Dz1Calloc(sizeof(Dz1LzwDictSizeNode *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1LzwDictSizeTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1LzwDictSizeTable_get_array, (void *)&arg);
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

static Dz1Error Dz1LzwDictSizeTable_travelForward(Dz1LzwDictSizeTable *p, Dz1Error (*func)(void *ptr, Dz1LzwDictSizeNode *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1LzwDictSizeTable_travelBackward(Dz1LzwDictSizeTable *p, Dz1Error (*func)(void *ptr, Dz1LzwDictSizeNode *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1LzwDictSizeNode *Dz1LzwDictSizeTable_find(Dz1LzwDictSizeTable *p, Dz1LzwDictSizeNode *key)
{
	return (Dz1LzwDictSizeNode *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1LzwDictSizeTable_count(Dz1LzwDictSizeTable *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1LzwDictSizeTable *Dz1LzwDictSizeTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictSizeTable *ret = (Dz1LzwDictSizeTable *)Dz1Calloc(sizeof(Dz1LzwDictSizeTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LzwDictSizeTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1LzwDictSizeNode_cmp,
				(Dz1DelFunc)Dz1LzwDictSizeNode_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1LzwDictSizeTable_count;
			ret->travel = Dz1LzwDictSizeTable_travelForward;
			ret->travelForward = Dz1LzwDictSizeTable_travelForward;
			ret->travelBackward = Dz1LzwDictSizeTable_travelBackward;
			ret->get_array = Dz1LzwDictSizeTable_get_array;
			ret->add = Dz1LzwDictSizeTable_add;
			ret->remove = Dz1LzwDictSizeTable_remove;
			ret->find = Dz1LzwDictSizeTable_find;
			ret->extract = Dz1LzwDictSizeTable_extract;
			ret->cmp = Dz1LzwDictSizeNode_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictSizeTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LzwDictSizeTable_purge(Dz1LzwDictSizeTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1LzwDictSizeTable_del(Dz1LzwDictSizeTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1LzwDictSizeTable_dump(void *ptr, Dz1LzwDictSizeNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1LzwDictSizeNode_dump(p, tab);
	return err;
}

void Dz1LzwDictSizeTable_dump(Dz1LzwDictSizeTable *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1LzwDictSizeTable_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1LzwDictSizeTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictCode
Dz1LzwDictCode *Dz1LzwDictCode_new(u32_t code, Dz1Binary *bin, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictCode *__internal_ret = (Dz1LzwDictCode *)Dz1Calloc(sizeof(Dz1LzwDictCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LzwDictCode_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->code = code;
		__internal_ret->bin = bin;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictCode_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1LzwDictCode_purge(Dz1LzwDictCode *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->bin);
}

void Dz1LzwDictCode_del(Dz1LzwDictCode *p)
{
	if (p == NULL) return;
	Dz1LzwDictCode_purge(p);
	Dz1Free(p);
}

void Dz1LzwDictCode_dump(Dz1LzwDictCode *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("code = ")); Dz1u32_dump(&p->code, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("bin = ")); Dz1Binary_dump(p->bin, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1LzwDictCode_cmp(Dz1LzwDictCode *a, Dz1LzwDictCode *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->code, &b->code)) != 0) { }
	return ret;
}
// Dz1LzwDictCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictCodeList
static Dz1Error Dz1LzwDictCodeList_add(Dz1LzwDictCodeList *p, Dz1LzwDictCode *data)
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

static bool_t Dz1LzwDictCodeList_remove(Dz1LzwDictCodeList *p, Dz1LzwDictCode *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1LzwDictCode *Dz1LzwDictCodeList_extract(Dz1LzwDictCodeList *p, Dz1LzwDictCode *key)
{
	return (Dz1LzwDictCode *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1LzwDictCodeListMkArrArg
{
	Dz1LzwDictCode **arr;
	unsigned int idx;
} Dz1LzwDictCodeListMkArrArg;

static Dz1Error _Dz1LzwDictCodeList_get_array(void *ptr, Dz1LzwDictCode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LzwDictCodeListMkArrArg *arg = (Dz1LzwDictCodeListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1LzwDictCode **Dz1LzwDictCodeList_get_array(Dz1LzwDictCodeList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1LzwDictCode **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1LzwDictCode **)Dz1Calloc(sizeof(Dz1LzwDictCode *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1LzwDictCodeListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1LzwDictCodeList_get_array, (void *)&arg);
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

static Dz1Error Dz1LzwDictCodeList_travelForward(Dz1LzwDictCodeList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictCode *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1LzwDictCodeList_travelBackward(Dz1LzwDictCodeList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictCode *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1LzwDictCode *Dz1LzwDictCodeList_find(Dz1LzwDictCodeList *p, Dz1LzwDictCode *key)
{
	return (Dz1LzwDictCode *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1LzwDictCodeList_count(Dz1LzwDictCodeList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1LzwDictCodeList *Dz1LzwDictCodeList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictCodeList *ret = (Dz1LzwDictCodeList *)Dz1Calloc(sizeof(Dz1LzwDictCodeList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LzwDictCodeList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1LzwDictCode_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1LzwDictCodeList_count;
			ret->travel = Dz1LzwDictCodeList_travelForward;
			ret->travelForward = Dz1LzwDictCodeList_travelForward;
			ret->travelBackward = Dz1LzwDictCodeList_travelBackward;
			ret->get_array = Dz1LzwDictCodeList_get_array;
			ret->add = Dz1LzwDictCodeList_add;
			ret->remove = Dz1LzwDictCodeList_remove;
			ret->find = Dz1LzwDictCodeList_find;
			ret->extract = Dz1LzwDictCodeList_extract;
			ret->cmp = Dz1LzwDictCode_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictCodeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1LzwDictCodeList_clone(void *ptr, Dz1LzwDictCode *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LzwDictCodeList *p = (Dz1LzwDictCodeList *)ptr;
	Dz1LzwDictCode *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1LzwDictCodeList *Dz1LzwDictCodeList_clone(Dz1LzwDictCodeList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictCodeList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1LzwDictCodeList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LzwDictCodeList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1LzwDictCodeList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictCodeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LzwDictCodeList_purge(Dz1LzwDictCodeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1LzwDictCodeList_del(Dz1LzwDictCodeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1LzwDictCodeList_dump(void *ptr, Dz1LzwDictCode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1LzwDictCode_dump(p, tab);
	return err;
}

void Dz1LzwDictCodeList_dump(Dz1LzwDictCodeList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1LzwDictCodeList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1LzwDictCodeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictionary
Dz1LzwDictionary *Dz1LzwDictionary_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LzwDictionary *__internal_ret = (Dz1LzwDictionary *)Dz1Calloc(sizeof(Dz1LzwDictionary), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LzwDictionary_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->arr = Dz1LzwDictDataArray_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->sizes = Dz1LzwDictSizeTable_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->codes = Dz1LzwDictCodeList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LzwDictionary_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1LzwDictionary_purge(Dz1LzwDictionary *p)
{
	if (p == NULL) return;
	Dz1LzwDictDataArray_del(p->arr);
	Dz1LzwDictSizeTable_del(p->sizes);
	Dz1LzwDictCodeList_del(p->codes);
}

void Dz1LzwDictionary_del(Dz1LzwDictionary *p)
{
	if (p == NULL) return;
	Dz1LzwDictionary_purge(p);
	Dz1Free(p);
}

void Dz1LzwDictionary_dump(Dz1LzwDictionary *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("code_bits = ")); Dz1u32_dump(&p->code_bits, tab); 
		Dz1Thread_tprintf(tab, Dz1T("base_code_max = ")); Dz1u32_dump(&p->base_code_max, tab); 
		Dz1Thread_tprintf(tab, Dz1T("curr_code_max = ")); Dz1u32_dump(&p->curr_code_max, tab); 
		Dz1Thread_tprintf(tab, Dz1T("alloc_code = ")); Dz1u32_dump(&p->alloc_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("arr = ")); Dz1LzwDictDataArray_dump(p->arr, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1LzwDictionary
////////////////////////////////////////////////////////////////////////////////

