////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1MfcDefLocal.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFolderTreeChilds
static Dz1Error Dz1MfcFolderTreeChilds_add(Dz1MfcFolderTreeChilds *p, Dz1MfcFolderTreeNode *data)
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

static bool_t Dz1MfcFolderTreeChilds_remove(Dz1MfcFolderTreeChilds *p, Dz1MfcFolderTreeNode *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFolderTreeNode *Dz1MfcFolderTreeChilds_extract(Dz1MfcFolderTreeChilds *p, Dz1MfcFolderTreeNode *key)
{
	return (Dz1MfcFolderTreeNode *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFolderTreeChildsMkArrArg
{
	Dz1MfcFolderTreeNode **arr;
	unsigned int idx;
} Dz1MfcFolderTreeChildsMkArrArg;

static Dz1Error _Dz1MfcFolderTreeChilds_get_array(void *ptr, Dz1MfcFolderTreeNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFolderTreeChildsMkArrArg *arg = (Dz1MfcFolderTreeChildsMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFolderTreeNode **Dz1MfcFolderTreeChilds_get_array(Dz1MfcFolderTreeChilds *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFolderTreeNode **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFolderTreeNode **)Dz1Calloc(sizeof(Dz1MfcFolderTreeNode *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFolderTreeChildsMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFolderTreeChilds_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFolderTreeChilds_travelForward(Dz1MfcFolderTreeChilds *p, Dz1Error (*func)(void *ptr, Dz1MfcFolderTreeNode *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFolderTreeChilds_travelBackward(Dz1MfcFolderTreeChilds *p, Dz1Error (*func)(void *ptr, Dz1MfcFolderTreeNode *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFolderTreeNode *Dz1MfcFolderTreeChilds_find(Dz1MfcFolderTreeChilds *p, Dz1MfcFolderTreeNode *key)
{
	return (Dz1MfcFolderTreeNode *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFolderTreeChilds_count(Dz1MfcFolderTreeChilds *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFolderTreeChilds *Dz1MfcFolderTreeChilds_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFolderTreeChilds *ret = (Dz1MfcFolderTreeChilds *)Dz1Calloc(sizeof(Dz1MfcFolderTreeChilds), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFolderTreeChilds_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFolderTreeNode_cmp,
				(Dz1DelFunc)Dz1MfcFolderTreeNode_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFolderTreeChilds_count;
			ret->travel = Dz1MfcFolderTreeChilds_travelForward;
			ret->travelForward = Dz1MfcFolderTreeChilds_travelForward;
			ret->travelBackward = Dz1MfcFolderTreeChilds_travelBackward;
			ret->get_array = Dz1MfcFolderTreeChilds_get_array;
			ret->add = Dz1MfcFolderTreeChilds_add;
			ret->remove = Dz1MfcFolderTreeChilds_remove;
			ret->find = Dz1MfcFolderTreeChilds_find;
			ret->extract = Dz1MfcFolderTreeChilds_extract;
			ret->cmp = Dz1MfcFolderTreeNode_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFolderTreeChilds_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFolderTreeChilds_clone(void *ptr, Dz1MfcFolderTreeNode *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFolderTreeChilds *p = (Dz1MfcFolderTreeChilds *)ptr;
	Dz1MfcFolderTreeNode *cloned = Dz1MfcFolderTreeNode_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFolderTreeChilds *Dz1MfcFolderTreeChilds_clone(Dz1MfcFolderTreeChilds *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFolderTreeChilds *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFolderTreeChilds_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFolderTreeChilds_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFolderTreeChilds_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFolderTreeChilds_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFolderTreeChilds_purge(Dz1MfcFolderTreeChilds *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFolderTreeChilds_del(Dz1MfcFolderTreeChilds *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFolderTreeChilds_dump(void *ptr, Dz1MfcFolderTreeNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFolderTreeNode_dump(p, tab);
	return err;
}

void Dz1MfcFolderTreeChilds_dump(Dz1MfcFolderTreeChilds *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFolderTreeChilds_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFolderTreeChilds
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFolderTreeNode
Dz1MfcFolderTreeNode *Dz1MfcFolderTreeNode_new(Dz1Str name, 
											   time_t stamp, 
											   Dz1MfcFolderTreeNode *parent, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFolderTreeNode *__internal_ret = (Dz1MfcFolderTreeNode *)Dz1Calloc(sizeof(Dz1MfcFolderTreeNode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFolderTreeNode_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->childs = Dz1MfcFolderTreeChilds_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->stamp = stamp;
			__internal_ret->parent = parent;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFolderTreeNode_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcFolderTreeNode_copy(Dz1MfcFolderTreeNode *dst, Dz1MfcFolderTreeNode *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->full_path && (dst->full_path = Dz1Str_clone(src->full_path, errp)) == NULL) ERR_OUT(errp);
	else if (src->parent && (dst->parent = Dz1MfcFolderTreeNode_clone(src->parent, errp)) == NULL) ERR_OUT(errp);
	else if (src->childs && (dst->childs = Dz1MfcFolderTreeChilds_clone(src->childs, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->stamp = src->stamp;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFolderTreeNode *Dz1MfcFolderTreeNode_clone(Dz1MfcFolderTreeNode *src, Dz1Error *err)
{
	Dz1MfcFolderTreeNode *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcFolderTreeNode *)Dz1Calloc(sizeof(Dz1MfcFolderTreeNode), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFolderTreeNode_delAndSetNull, (void *)&dst);
		if (Dz1MfcFolderTreeNode_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFolderTreeNode_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcFolderTreeNode_purge(Dz1MfcFolderTreeNode *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1Str_del(p->full_path);
	Dz1MfcFolderTreeNode_del(p->parent);
	Dz1MfcFolderTreeChilds_del(p->childs);
}

void Dz1MfcFolderTreeNode_del(Dz1MfcFolderTreeNode *p)
{
	if (p == NULL) return;
	Dz1MfcFolderTreeNode_purge(p);
	Dz1Free(p);
}

void Dz1MfcFolderTreeNode_dump(Dz1MfcFolderTreeNode *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("full_path = ")); Dz1Str_dump(p->full_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("stamp = ")); time_dump(&p->stamp, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1Thread_tprintf(tab, Dz1T("parent = %p\n"), p->parent);
		Dz1Thread_tprintf(tab, Dz1T("childs = ")); Dz1MfcFolderTreeChilds_dump(p->childs, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcFolderTreeNode_cmp(Dz1MfcFolderTreeNode *a, Dz1MfcFolderTreeNode *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->name, b->name)) != 0) { }
	return ret;
}
// Dz1MfcFolderTreeNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFolderTreeRefChilds
static Dz1Error Dz1MfcFolderTreeRefChilds_add(Dz1MfcFolderTreeRefChilds *p, Dz1MfcFolderTreeNode *data)
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

static bool_t Dz1MfcFolderTreeRefChilds_remove(Dz1MfcFolderTreeRefChilds *p, Dz1MfcFolderTreeNode *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFolderTreeNode *Dz1MfcFolderTreeRefChilds_extract(Dz1MfcFolderTreeRefChilds *p, Dz1MfcFolderTreeNode *key)
{
	return (Dz1MfcFolderTreeNode *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFolderTreeRefChildsMkArrArg
{
	Dz1MfcFolderTreeNode **arr;
	unsigned int idx;
} Dz1MfcFolderTreeRefChildsMkArrArg;

static Dz1Error _Dz1MfcFolderTreeRefChilds_get_array(void *ptr, Dz1MfcFolderTreeNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFolderTreeRefChildsMkArrArg *arg = (Dz1MfcFolderTreeRefChildsMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFolderTreeNode **Dz1MfcFolderTreeRefChilds_get_array(Dz1MfcFolderTreeRefChilds *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFolderTreeNode **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFolderTreeNode **)Dz1Calloc(sizeof(Dz1MfcFolderTreeNode *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFolderTreeRefChildsMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFolderTreeRefChilds_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFolderTreeRefChilds_travelForward(Dz1MfcFolderTreeRefChilds *p, Dz1Error (*func)(void *ptr, Dz1MfcFolderTreeNode *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFolderTreeRefChilds_travelBackward(Dz1MfcFolderTreeRefChilds *p, Dz1Error (*func)(void *ptr, Dz1MfcFolderTreeNode *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFolderTreeNode *Dz1MfcFolderTreeRefChilds_find(Dz1MfcFolderTreeRefChilds *p, Dz1MfcFolderTreeNode *key)
{
	return (Dz1MfcFolderTreeNode *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFolderTreeRefChilds_count(Dz1MfcFolderTreeRefChilds *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFolderTreeRefChilds *Dz1MfcFolderTreeRefChilds_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFolderTreeRefChilds *ret = (Dz1MfcFolderTreeRefChilds *)Dz1Calloc(sizeof(Dz1MfcFolderTreeRefChilds), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFolderTreeRefChilds_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFolderTreeNode_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFolderTreeRefChilds_count;
			ret->travel = Dz1MfcFolderTreeRefChilds_travelForward;
			ret->travelForward = Dz1MfcFolderTreeRefChilds_travelForward;
			ret->travelBackward = Dz1MfcFolderTreeRefChilds_travelBackward;
			ret->get_array = Dz1MfcFolderTreeRefChilds_get_array;
			ret->add = Dz1MfcFolderTreeRefChilds_add;
			ret->remove = Dz1MfcFolderTreeRefChilds_remove;
			ret->find = Dz1MfcFolderTreeRefChilds_find;
			ret->extract = Dz1MfcFolderTreeRefChilds_extract;
			ret->cmp = Dz1MfcFolderTreeNode_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFolderTreeRefChilds_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFolderTreeRefChilds_clone(void *ptr, Dz1MfcFolderTreeNode *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFolderTreeRefChilds *p = (Dz1MfcFolderTreeRefChilds *)ptr;
	Dz1MfcFolderTreeNode *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFolderTreeRefChilds *Dz1MfcFolderTreeRefChilds_clone(Dz1MfcFolderTreeRefChilds *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFolderTreeRefChilds *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFolderTreeRefChilds_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFolderTreeRefChilds_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFolderTreeRefChilds_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFolderTreeRefChilds_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFolderTreeRefChilds_purge(Dz1MfcFolderTreeRefChilds *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFolderTreeRefChilds_del(Dz1MfcFolderTreeRefChilds *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFolderTreeRefChilds_dump(void *ptr, Dz1MfcFolderTreeNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFolderTreeNode_dump(p, tab);
	return err;
}

void Dz1MfcFolderTreeRefChilds_dump(Dz1MfcFolderTreeRefChilds *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFolderTreeRefChilds_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFolderTreeRefChilds
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFolderTree
Dz1MfcFolderTree *Dz1MfcFolderTree_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFolderTree *__internal_ret = (Dz1MfcFolderTree *)Dz1Calloc(sizeof(Dz1MfcFolderTree), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFolderTree_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->hdd_roots = Dz1MfcFolderTreeChilds_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->share_roots = Dz1MfcFolderTreeChilds_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFolderTree_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MfcFolderTree_purge(Dz1MfcFolderTree *p)
{
	if (p == NULL) return;
	Dz1MfcFolderTreeChilds_del(p->hdd_roots);
	Dz1MfcFolderTreeChilds_del(p->share_roots);
}

void Dz1MfcFolderTree_del(Dz1MfcFolderTree *p)
{
	if (p == NULL) return;
	Dz1MfcFolderTree_purge(p);
	Dz1Free(p);
}

void Dz1MfcFolderTree_dump(Dz1MfcFolderTree *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("hdd_roots = ")); Dz1MfcFolderTreeChilds_dump(p->hdd_roots, tab); 
		Dz1Thread_tprintf(tab, Dz1T("share_roots = ")); Dz1MfcFolderTreeChilds_dump(p->share_roots, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFolderTree
////////////////////////////////////////////////////////////////////////////////

