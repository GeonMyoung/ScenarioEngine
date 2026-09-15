////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_code_gen_struct.h"

////////////////////////////////////////////////////////////////////////////////
// ListControlGenList
static Dz1Error ListControlGenList_add(ListControlGenList *p, ListControlGenNode *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static ListControlGenNode *ListControlGenList_extract(ListControlGenList *p, ListControlGenNode *ptr)
{
	return (ListControlGenNode *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct ListControlGenListMkArrArg
{
	ListControlGenNode **arr;
	unsigned int idx;
} ListControlGenListMkArrArg;

static Dz1Error _ListControlGenList_get_array(void *ptr, ListControlGenNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ListControlGenListMkArrArg *arg = (ListControlGenListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ListControlGenNode **ListControlGenList_get_array(ListControlGenList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ListControlGenNode **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ListControlGenNode **)Dz1Calloc(sizeof(ListControlGenNode *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ListControlGenListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ListControlGenList_get_array, (void *)&arg);
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

static Dz1Error ListControlGenList_travelForward(ListControlGenList *p, Dz1Error (*func)(void *ptr, ListControlGenNode *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error ListControlGenList_travelBackward(ListControlGenList *p, Dz1Error (*func)(void *ptr, ListControlGenNode *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct ListControlGenListFindArg
{
	ListControlGenNode *key;
	ListControlGenNode *ret;
	int (*cmp)(ListControlGenNode *a, ListControlGenNode *b);
} ListControlGenListFindArg;

static Dz1Error _ListControlGenList_find(void *ptr, ListControlGenNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	ListControlGenListFindArg *arg = (ListControlGenListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static ListControlGenNode *ListControlGenList_find(ListControlGenList *p, ListControlGenNode *key)
{
	ListControlGenListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _ListControlGenList_find, (void *)&arg);
	return arg.ret;
}

static unsigned int ListControlGenList_count(ListControlGenList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

ListControlGenList *ListControlGenList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ListControlGenList *ret = (ListControlGenList *)Dz1Calloc(sizeof(ListControlGenList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ListControlGenList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)ListControlGenNode_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ListControlGenList_count;
			ret->travel = ListControlGenList_travelForward;
			ret->travelForward = ListControlGenList_travelForward;
			ret->travelBackward = ListControlGenList_travelBackward;
			ret->get_array = ListControlGenList_get_array;
			ret->add = ListControlGenList_add;
			ret->find = ListControlGenList_find;
			ret->extract = ListControlGenList_extract;
			ret->cmp = ListControlGenNode_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ListControlGenList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _ListControlGenList_clone(void *ptr, ListControlGenNode *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ListControlGenList *p = (ListControlGenList *)ptr;
	ListControlGenNode *cloned = ListControlGenNode_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

ListControlGenList *ListControlGenList_clone(ListControlGenList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ListControlGenList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ListControlGenList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ListControlGenList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_ListControlGenList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (ListControlGenList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ListControlGenList_purge(ListControlGenList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void ListControlGenList_del(ListControlGenList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ListControlGenList_dump(void *ptr, ListControlGenNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ListControlGenNode_dump(p, tab);
	return err;
}

void ListControlGenList_dump(ListControlGenList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ListControlGenList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ListControlGenList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ListControlGenNode
ListControlGenNode *ListControlGenNode_new(str_t name, 
										   ObjectInfo *obj/*_ref*/, 
										   bool_t isItem, 
										   ListControlGenNode *parent, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ListControlGenNode *__internal_ret = (ListControlGenNode *)Dz1Calloc(sizeof(ListControlGenNode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ListControlGenNode_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = dz1_built_in_str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->childs = ListControlGenList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->obj = obj;
			__internal_ret->isItem = isItem;
			__internal_ret->parent = parent;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ListControlGenNode_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ListControlGenNode_copy(ListControlGenNode *dst, ListControlGenNode *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = dz1_built_in_str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->parent && (dst->parent = ListControlGenNode_clone(src->parent, errp)) == NULL) ERR_OUT(errp);
	else if (src->childs && (dst->childs = ListControlGenList_clone(src->childs, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->obj = src->obj;
		dst->isItem = src->isItem;
		dst->hTreeItem = src->hTreeItem;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ListControlGenNode *ListControlGenNode_clone(ListControlGenNode *src, Dz1Error *err)
{
	ListControlGenNode *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ListControlGenNode *)Dz1Calloc(sizeof(ListControlGenNode), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ListControlGenNode_delAndSetNull, (void *)&dst);
		if (ListControlGenNode_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ListControlGenNode_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ListControlGenNode_purge(ListControlGenNode *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->name);
	ListControlGenNode_del(p->parent);
	ListControlGenList_del(p->childs);
}

void ListControlGenNode_del(ListControlGenNode *p)
{
	if (p == NULL) return;
	ListControlGenNode_purge(p);
	Dz1Free(p);
}

void ListControlGenNode_dump(ListControlGenNode *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); dz1_built_in_str_dump(p->name, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("obj = ")); ObjectInfo_dump(p->obj, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isItem = ")); Dz1Bool_dump(&p->isItem, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1Thread_tprintf(tab, Dz1T("parent = %p\n"), p->parent);
		Dz1Thread_tprintf(tab, Dz1T("childs = ")); ListControlGenList_dump(p->childs, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hTreeItem = %p\n"), p->hTreeItem);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ListControlGenNode_cmp(ListControlGenNode *a, ListControlGenNode *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->name, b->name)) != 0) { }
	return ret;
}
// ListControlGenNode
////////////////////////////////////////////////////////////////////////////////

