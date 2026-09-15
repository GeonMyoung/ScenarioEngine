////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1MfcFileUtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileEntry
Dz1MfcFileEntry *Dz1MfcFileEntry_new(Dz1Str name_ext, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileEntry *__internal_ret = (Dz1MfcFileEntry *)Dz1Calloc(sizeof(Dz1MfcFileEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (name_ext && (__internal_ret->name_ext = Dz1Str_clone(name_ext, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcFileEntry_copy(Dz1MfcFileEntry *dst, Dz1MfcFileEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name_ext && (dst->name_ext = Dz1Str_clone(src->name_ext, errp)) == NULL) ERR_OUT(errp);
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->ext && (dst->ext = Dz1Str_clone(src->ext, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFileEntry *Dz1MfcFileEntry_clone(Dz1MfcFileEntry *src, Dz1Error *err)
{
	Dz1MfcFileEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcFileEntry *)Dz1Calloc(sizeof(Dz1MfcFileEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileEntry_delAndSetNull, (void *)&dst);
		if (Dz1MfcFileEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcFileEntry_purge(Dz1MfcFileEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name_ext);
	Dz1Str_del(p->name);
	Dz1Str_del(p->ext);
}

void Dz1MfcFileEntry_del(Dz1MfcFileEntry *p)
{
	if (p == NULL) return;
	Dz1MfcFileEntry_purge(p);
	Dz1Free(p);
}

void Dz1MfcFileEntry_dump(Dz1MfcFileEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("name_ext = ")); Dz1Str_dump(p->name_ext, tab); 
	}
}
int Dz1MfcFileEntry_cmp(Dz1MfcFileEntry *a, Dz1MfcFileEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name_ext == NULL && b->name_ext == NULL) ret = 0;
	else if (a->name_ext == NULL /*&& b->name_ext != NULL*/) ret = -1;
	else if (/*a->name_ext != NULL &&*/ b->name_ext == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->name_ext, b->name_ext)) != 0) { }
	return ret;
}
// Dz1MfcFileEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileList
static Dz1Error Dz1MfcFileList_add(Dz1MfcFileList *p, Dz1MfcFileEntry *data)
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

static bool_t Dz1MfcFileList_remove(Dz1MfcFileList *p, Dz1MfcFileEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFileEntry *Dz1MfcFileList_extract(Dz1MfcFileList *p, Dz1MfcFileEntry *key)
{
	return (Dz1MfcFileEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFileListMkArrArg
{
	Dz1MfcFileEntry **arr;
	unsigned int idx;
} Dz1MfcFileListMkArrArg;

static Dz1Error _Dz1MfcFileList_get_array(void *ptr, Dz1MfcFileEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileListMkArrArg *arg = (Dz1MfcFileListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFileEntry **Dz1MfcFileList_get_array(Dz1MfcFileList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFileEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFileEntry **)Dz1Calloc(sizeof(Dz1MfcFileEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFileListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFileList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFileList_travelForward(Dz1MfcFileList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFileList_travelBackward(Dz1MfcFileList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFileEntry *Dz1MfcFileList_find(Dz1MfcFileList *p, Dz1MfcFileEntry *key)
{
	return (Dz1MfcFileEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFileList_count(Dz1MfcFileList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFileList *Dz1MfcFileList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileList *ret = (Dz1MfcFileList *)Dz1Calloc(sizeof(Dz1MfcFileList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFileEntry_cmp,
				(Dz1DelFunc)Dz1MfcFileEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFileList_count;
			ret->travel = Dz1MfcFileList_travelForward;
			ret->travelForward = Dz1MfcFileList_travelForward;
			ret->travelBackward = Dz1MfcFileList_travelBackward;
			ret->get_array = Dz1MfcFileList_get_array;
			ret->add = Dz1MfcFileList_add;
			ret->remove = Dz1MfcFileList_remove;
			ret->find = Dz1MfcFileList_find;
			ret->extract = Dz1MfcFileList_extract;
			ret->cmp = Dz1MfcFileEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFileList_clone(void *ptr, Dz1MfcFileEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileList *p = (Dz1MfcFileList *)ptr;
	Dz1MfcFileEntry *cloned = Dz1MfcFileEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFileList *Dz1MfcFileList_clone(Dz1MfcFileList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFileList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFileList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFileList_purge(Dz1MfcFileList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFileList_del(Dz1MfcFileList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFileList_dump(void *ptr, Dz1MfcFileEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFileEntry_dump(p, tab);
	return err;
}

void Dz1MfcFileList_dump(Dz1MfcFileList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFileList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperState
static struct Dz1MfcFileOperStateMapA
{
	str_t str;
	Dz1MfcFileOperState v;
} Dz1MfcFileOperStateMapA[] =
{
	{ (char *)"initial", Dz1MfcFileOperState_initial },
	{ (char *)"prepared", Dz1MfcFileOperState_prepared },
	{ (char *)"success", Dz1MfcFileOperState_success },
	{ (char *)"fail", Dz1MfcFileOperState_fail },
	{ NULL, Dz1MfcFileOperState_max }
};

str_t Dz1MfcFileOperStateStrA(Dz1MfcFileOperState v)
{
	struct Dz1MfcFileOperStateMapA *i = NULL;
	for (i = Dz1MfcFileOperStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcFileOperState Dz1MfcFileOperStateFromStrA(str_t str)
{
	struct Dz1MfcFileOperStateMapA *i = NULL;
	for (i = Dz1MfcFileOperStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcFileOperState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MfcFileOperStateMapW
{
	wstr_t str;
	Dz1MfcFileOperState v;
} Dz1MfcFileOperStateMapW[] =
{
	{ (wchar_t *)L"initial", Dz1MfcFileOperState_initial },
	{ (wchar_t *)L"prepared", Dz1MfcFileOperState_prepared },
	{ (wchar_t *)L"success", Dz1MfcFileOperState_success },
	{ (wchar_t *)L"fail", Dz1MfcFileOperState_fail },
	{ NULL, Dz1MfcFileOperState_max }
};

wstr_t Dz1MfcFileOperStateStrW(Dz1MfcFileOperState v)
{
	struct Dz1MfcFileOperStateMapW *i = NULL;
	for (i = Dz1MfcFileOperStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcFileOperState Dz1MfcFileOperStateFromStrW(wstr_t str)
{
	struct Dz1MfcFileOperStateMapW *i = NULL;
	for (i = Dz1MfcFileOperStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcFileOperState_max;
}
#endif // UNIX_SYSTEM

Dz1MfcFileOperState *Dz1MfcFileOperState_new(Dz1MfcFileOperState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperState *__internal_ret = (Dz1MfcFileOperState *)Dz1Calloc(sizeof(Dz1MfcFileOperState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1MfcFileOperState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperDeleteEntry
Dz1MfcFileOperDeleteEntry *Dz1MfcFileOperDeleteEntry_new(Dz1Str path, 
														 Dz1MfcFileEntry *file, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperDeleteEntry *__internal_ret = (Dz1MfcFileOperDeleteEntry *)Dz1Calloc(sizeof(Dz1MfcFileOperDeleteEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperDeleteEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (path && (__internal_ret->path = Dz1Str_clone(path, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->file = file;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperDeleteEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcFileOperDeleteEntry_copy(Dz1MfcFileOperDeleteEntry *dst, Dz1MfcFileOperDeleteEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->path && (dst->path = Dz1Str_clone(src->path, errp)) == NULL) ERR_OUT(errp);
	else if (src->file && (dst->file = Dz1MfcFileEntry_clone(src->file, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->state = src->state;
		dst->fail_code = src->fail_code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFileOperDeleteEntry *Dz1MfcFileOperDeleteEntry_clone(Dz1MfcFileOperDeleteEntry *src, Dz1Error *err)
{
	Dz1MfcFileOperDeleteEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcFileOperDeleteEntry *)Dz1Calloc(sizeof(Dz1MfcFileOperDeleteEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperDeleteEntry_delAndSetNull, (void *)&dst);
		if (Dz1MfcFileOperDeleteEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperDeleteEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcFileOperDeleteEntry_purge(Dz1MfcFileOperDeleteEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->path);
	Dz1MfcFileEntry_del(p->file);
}

void Dz1MfcFileOperDeleteEntry_del(Dz1MfcFileOperDeleteEntry *p)
{
	if (p == NULL) return;
	Dz1MfcFileOperDeleteEntry_purge(p);
	Dz1Free(p);
}

void Dz1MfcFileOperDeleteEntry_dump(Dz1MfcFileOperDeleteEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("path = ")); Dz1Str_dump(p->path, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("file = ")); Dz1MfcFileEntry_dump(p->file, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), Dz1MfcFileOperStateStr(p->state), p->state);
		Dz1Thread_tprintf(tab, Dz1T("fail_code = ")); Dz1s32_dump(&p->fail_code, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcFileOperDeleteEntry_cmp(Dz1MfcFileOperDeleteEntry *a, Dz1MfcFileOperDeleteEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->path == NULL && b->path == NULL) ret = 0;
	else if (a->path == NULL /*&& b->path != NULL*/) ret = -1;
	else if (/*a->path != NULL &&*/ b->path == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->path, b->path)) != 0) { }
	else if (a->file == NULL && b->file == NULL) ret = 0;
	else if (a->file == NULL /*&& b->file != NULL*/) ret = -1;
	else if (/*a->file != NULL &&*/ b->file == NULL) ret = 1;
	else if ((ret = Dz1MfcFileEntry_cmp(a->file, b->file)) != 0) { }
	return ret;
}
// Dz1MfcFileOperDeleteEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperDeleteList
static Dz1Error Dz1MfcFileOperDeleteList_add(Dz1MfcFileOperDeleteList *p, Dz1MfcFileOperDeleteEntry *data)
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

static bool_t Dz1MfcFileOperDeleteList_remove(Dz1MfcFileOperDeleteList *p, Dz1MfcFileOperDeleteEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFileOperDeleteEntry *Dz1MfcFileOperDeleteList_extract(Dz1MfcFileOperDeleteList *p, Dz1MfcFileOperDeleteEntry *key)
{
	return (Dz1MfcFileOperDeleteEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFileOperDeleteListMkArrArg
{
	Dz1MfcFileOperDeleteEntry **arr;
	unsigned int idx;
} Dz1MfcFileOperDeleteListMkArrArg;

static Dz1Error _Dz1MfcFileOperDeleteList_get_array(void *ptr, Dz1MfcFileOperDeleteEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperDeleteListMkArrArg *arg = (Dz1MfcFileOperDeleteListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFileOperDeleteEntry **Dz1MfcFileOperDeleteList_get_array(Dz1MfcFileOperDeleteList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFileOperDeleteEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFileOperDeleteEntry **)Dz1Calloc(sizeof(Dz1MfcFileOperDeleteEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFileOperDeleteListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFileOperDeleteList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFileOperDeleteList_travelForward(Dz1MfcFileOperDeleteList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFileOperDeleteList_travelBackward(Dz1MfcFileOperDeleteList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFileOperDeleteEntry *Dz1MfcFileOperDeleteList_find(Dz1MfcFileOperDeleteList *p, Dz1MfcFileOperDeleteEntry *key)
{
	return (Dz1MfcFileOperDeleteEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFileOperDeleteList_count(Dz1MfcFileOperDeleteList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFileOperDeleteList *Dz1MfcFileOperDeleteList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperDeleteList *ret = (Dz1MfcFileOperDeleteList *)Dz1Calloc(sizeof(Dz1MfcFileOperDeleteList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperDeleteList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFileOperDeleteEntry_cmp,
				(Dz1DelFunc)Dz1MfcFileOperDeleteEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFileOperDeleteList_count;
			ret->travel = Dz1MfcFileOperDeleteList_travelForward;
			ret->travelForward = Dz1MfcFileOperDeleteList_travelForward;
			ret->travelBackward = Dz1MfcFileOperDeleteList_travelBackward;
			ret->get_array = Dz1MfcFileOperDeleteList_get_array;
			ret->add = Dz1MfcFileOperDeleteList_add;
			ret->remove = Dz1MfcFileOperDeleteList_remove;
			ret->find = Dz1MfcFileOperDeleteList_find;
			ret->extract = Dz1MfcFileOperDeleteList_extract;
			ret->cmp = Dz1MfcFileOperDeleteEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperDeleteList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFileOperDeleteList_clone(void *ptr, Dz1MfcFileOperDeleteEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperDeleteList *p = (Dz1MfcFileOperDeleteList *)ptr;
	Dz1MfcFileOperDeleteEntry *cloned = Dz1MfcFileOperDeleteEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFileOperDeleteList *Dz1MfcFileOperDeleteList_clone(Dz1MfcFileOperDeleteList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperDeleteList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFileOperDeleteList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperDeleteList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFileOperDeleteList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperDeleteList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFileOperDeleteList_purge(Dz1MfcFileOperDeleteList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFileOperDeleteList_del(Dz1MfcFileOperDeleteList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFileOperDeleteList_dump(void *ptr, Dz1MfcFileOperDeleteEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFileOperDeleteEntry_dump(p, tab);
	return err;
}

void Dz1MfcFileOperDeleteList_dump(Dz1MfcFileOperDeleteList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFileOperDeleteList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperDeleteList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperDelRefList
static Dz1Error Dz1MfcFileOperDelRefList_add(Dz1MfcFileOperDelRefList *p, Dz1MfcFileOperDeleteEntry *data)
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

static bool_t Dz1MfcFileOperDelRefList_remove(Dz1MfcFileOperDelRefList *p, Dz1MfcFileOperDeleteEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFileOperDeleteEntry *Dz1MfcFileOperDelRefList_extract(Dz1MfcFileOperDelRefList *p, Dz1MfcFileOperDeleteEntry *key)
{
	return (Dz1MfcFileOperDeleteEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFileOperDelRefListMkArrArg
{
	Dz1MfcFileOperDeleteEntry **arr;
	unsigned int idx;
} Dz1MfcFileOperDelRefListMkArrArg;

static Dz1Error _Dz1MfcFileOperDelRefList_get_array(void *ptr, Dz1MfcFileOperDeleteEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperDelRefListMkArrArg *arg = (Dz1MfcFileOperDelRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFileOperDeleteEntry **Dz1MfcFileOperDelRefList_get_array(Dz1MfcFileOperDelRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFileOperDeleteEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFileOperDeleteEntry **)Dz1Calloc(sizeof(Dz1MfcFileOperDeleteEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFileOperDelRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFileOperDelRefList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFileOperDelRefList_travelForward(Dz1MfcFileOperDelRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFileOperDelRefList_travelBackward(Dz1MfcFileOperDelRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFileOperDeleteEntry *Dz1MfcFileOperDelRefList_find(Dz1MfcFileOperDelRefList *p, Dz1MfcFileOperDeleteEntry *key)
{
	return (Dz1MfcFileOperDeleteEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFileOperDelRefList_count(Dz1MfcFileOperDelRefList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFileOperDelRefList *Dz1MfcFileOperDelRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperDelRefList *ret = (Dz1MfcFileOperDelRefList *)Dz1Calloc(sizeof(Dz1MfcFileOperDelRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperDelRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFileOperDeleteEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFileOperDelRefList_count;
			ret->travel = Dz1MfcFileOperDelRefList_travelForward;
			ret->travelForward = Dz1MfcFileOperDelRefList_travelForward;
			ret->travelBackward = Dz1MfcFileOperDelRefList_travelBackward;
			ret->get_array = Dz1MfcFileOperDelRefList_get_array;
			ret->add = Dz1MfcFileOperDelRefList_add;
			ret->remove = Dz1MfcFileOperDelRefList_remove;
			ret->find = Dz1MfcFileOperDelRefList_find;
			ret->extract = Dz1MfcFileOperDelRefList_extract;
			ret->cmp = Dz1MfcFileOperDeleteEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperDelRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFileOperDelRefList_clone(void *ptr, Dz1MfcFileOperDeleteEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperDelRefList *p = (Dz1MfcFileOperDelRefList *)ptr;
	Dz1MfcFileOperDeleteEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFileOperDelRefList *Dz1MfcFileOperDelRefList_clone(Dz1MfcFileOperDelRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperDelRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFileOperDelRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperDelRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFileOperDelRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperDelRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFileOperDelRefList_purge(Dz1MfcFileOperDelRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFileOperDelRefList_del(Dz1MfcFileOperDelRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFileOperDelRefList_dump(void *ptr, Dz1MfcFileOperDeleteEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFileOperDeleteEntry_dump(p, tab);
	return err;
}

void Dz1MfcFileOperDelRefList_dump(Dz1MfcFileOperDelRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFileOperDelRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperDelRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperDeleteData
Dz1MfcFileOperDeleteData *Dz1MfcFileOperDeleteData_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperDeleteData *__internal_ret = (Dz1MfcFileOperDeleteData *)Dz1Calloc(sizeof(Dz1MfcFileOperDeleteData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperDeleteData_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->list = Dz1MfcFileOperDeleteList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->failed = Dz1MfcFileOperDelRefList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperDeleteData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcFileOperDeleteData_copy(Dz1MfcFileOperDeleteData *dst, Dz1MfcFileOperDeleteData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->list && (dst->list = Dz1MfcFileOperDeleteList_clone(src->list, errp)) == NULL) ERR_OUT(errp);
	else if (src->failed && (dst->failed = Dz1MfcFileOperDelRefList_clone(src->failed, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFileOperDeleteData *Dz1MfcFileOperDeleteData_clone(Dz1MfcFileOperDeleteData *src, Dz1Error *err)
{
	Dz1MfcFileOperDeleteData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcFileOperDeleteData *)Dz1Calloc(sizeof(Dz1MfcFileOperDeleteData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperDeleteData_delAndSetNull, (void *)&dst);
		if (Dz1MfcFileOperDeleteData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperDeleteData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcFileOperDeleteData_purge(Dz1MfcFileOperDeleteData *p)
{
	if (p == NULL) return;
	Dz1MfcFileOperDeleteList_del(p->list);
	Dz1MfcFileOperDelRefList_del(p->failed);
}

void Dz1MfcFileOperDeleteData_del(Dz1MfcFileOperDeleteData *p)
{
	if (p == NULL) return;
	Dz1MfcFileOperDeleteData_purge(p);
	Dz1Free(p);
}

void Dz1MfcFileOperDeleteData_dump(Dz1MfcFileOperDeleteData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("list = ")); Dz1MfcFileOperDeleteList_dump(p->list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("failed = ")); Dz1MfcFileOperDelRefList_dump(p->failed, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperDeleteData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenameEntry
Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameEntry_new(Dz1MfcFileEntry *src, 
														 Dz1MfcFileEntry *dst, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperRenameEntry *__internal_ret = (Dz1MfcFileOperRenameEntry *)Dz1Calloc(sizeof(Dz1MfcFileOperRenameEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenameEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->src = src;
		__internal_ret->dst = dst;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenameEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcFileOperRenameEntry_copy(Dz1MfcFileOperRenameEntry *dst, Dz1MfcFileOperRenameEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->src && (dst->src = Dz1MfcFileEntry_clone(src->src, errp)) == NULL) ERR_OUT(errp);
	else if (src->dst && (dst->dst = Dz1MfcFileEntry_clone(src->dst, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->state = src->state;
		dst->fail_code = src->fail_code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameEntry_clone(Dz1MfcFileOperRenameEntry *src, Dz1Error *err)
{
	Dz1MfcFileOperRenameEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcFileOperRenameEntry *)Dz1Calloc(sizeof(Dz1MfcFileOperRenameEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenameEntry_delAndSetNull, (void *)&dst);
		if (Dz1MfcFileOperRenameEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenameEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcFileOperRenameEntry_purge(Dz1MfcFileOperRenameEntry *p)
{
	if (p == NULL) return;
	Dz1MfcFileEntry_del(p->src);
	Dz1MfcFileEntry_del(p->dst);
}

void Dz1MfcFileOperRenameEntry_del(Dz1MfcFileOperRenameEntry *p)
{
	if (p == NULL) return;
	Dz1MfcFileOperRenameEntry_purge(p);
	Dz1Free(p);
}

void Dz1MfcFileOperRenameEntry_dump(Dz1MfcFileOperRenameEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("src = ")); Dz1MfcFileEntry_dump(p->src, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("dst = ")); Dz1MfcFileEntry_dump(p->dst, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), Dz1MfcFileOperStateStr(p->state), p->state);
		Dz1Thread_tprintf(tab, Dz1T("fail_code = ")); Dz1s32_dump(&p->fail_code, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcFileOperRenameEntry_cmp(Dz1MfcFileOperRenameEntry *a, Dz1MfcFileOperRenameEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->src == NULL && b->src == NULL) ret = 0;
	else if (a->src == NULL /*&& b->src != NULL*/) ret = -1;
	else if (/*a->src != NULL &&*/ b->src == NULL) ret = 1;
	else if ((ret = Dz1MfcFileEntry_cmp(a->src, b->src)) != 0) { }
	return ret;
}
// Dz1MfcFileOperRenameEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenameList
static Dz1Error Dz1MfcFileOperRenameList_add(Dz1MfcFileOperRenameList *p, Dz1MfcFileOperRenameEntry *data)
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

static bool_t Dz1MfcFileOperRenameList_remove(Dz1MfcFileOperRenameList *p, Dz1MfcFileOperRenameEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameList_extract(Dz1MfcFileOperRenameList *p, Dz1MfcFileOperRenameEntry *key)
{
	return (Dz1MfcFileOperRenameEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFileOperRenameListMkArrArg
{
	Dz1MfcFileOperRenameEntry **arr;
	unsigned int idx;
} Dz1MfcFileOperRenameListMkArrArg;

static Dz1Error _Dz1MfcFileOperRenameList_get_array(void *ptr, Dz1MfcFileOperRenameEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperRenameListMkArrArg *arg = (Dz1MfcFileOperRenameListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFileOperRenameEntry **Dz1MfcFileOperRenameList_get_array(Dz1MfcFileOperRenameList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFileOperRenameEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFileOperRenameEntry **)Dz1Calloc(sizeof(Dz1MfcFileOperRenameEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFileOperRenameListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFileOperRenameList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFileOperRenameList_travelForward(Dz1MfcFileOperRenameList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFileOperRenameList_travelBackward(Dz1MfcFileOperRenameList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameList_find(Dz1MfcFileOperRenameList *p, Dz1MfcFileOperRenameEntry *key)
{
	return (Dz1MfcFileOperRenameEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFileOperRenameList_count(Dz1MfcFileOperRenameList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFileOperRenameList *Dz1MfcFileOperRenameList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperRenameList *ret = (Dz1MfcFileOperRenameList *)Dz1Calloc(sizeof(Dz1MfcFileOperRenameList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenameList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFileOperRenameEntry_cmp,
				(Dz1DelFunc)Dz1MfcFileOperRenameEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFileOperRenameList_count;
			ret->travel = Dz1MfcFileOperRenameList_travelForward;
			ret->travelForward = Dz1MfcFileOperRenameList_travelForward;
			ret->travelBackward = Dz1MfcFileOperRenameList_travelBackward;
			ret->get_array = Dz1MfcFileOperRenameList_get_array;
			ret->add = Dz1MfcFileOperRenameList_add;
			ret->remove = Dz1MfcFileOperRenameList_remove;
			ret->find = Dz1MfcFileOperRenameList_find;
			ret->extract = Dz1MfcFileOperRenameList_extract;
			ret->cmp = Dz1MfcFileOperRenameEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenameList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFileOperRenameList_clone(void *ptr, Dz1MfcFileOperRenameEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperRenameList *p = (Dz1MfcFileOperRenameList *)ptr;
	Dz1MfcFileOperRenameEntry *cloned = Dz1MfcFileOperRenameEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFileOperRenameList *Dz1MfcFileOperRenameList_clone(Dz1MfcFileOperRenameList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperRenameList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFileOperRenameList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenameList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFileOperRenameList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenameList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFileOperRenameList_purge(Dz1MfcFileOperRenameList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFileOperRenameList_del(Dz1MfcFileOperRenameList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFileOperRenameList_dump(void *ptr, Dz1MfcFileOperRenameEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFileOperRenameEntry_dump(p, tab);
	return err;
}

void Dz1MfcFileOperRenameList_dump(Dz1MfcFileOperRenameList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFileOperRenameList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperRenameList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenRefList
static Dz1Error Dz1MfcFileOperRenRefList_add(Dz1MfcFileOperRenRefList *p, Dz1MfcFileOperRenameEntry *data)
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

static bool_t Dz1MfcFileOperRenRefList_remove(Dz1MfcFileOperRenRefList *p, Dz1MfcFileOperRenameEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenRefList_extract(Dz1MfcFileOperRenRefList *p, Dz1MfcFileOperRenameEntry *key)
{
	return (Dz1MfcFileOperRenameEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFileOperRenRefListMkArrArg
{
	Dz1MfcFileOperRenameEntry **arr;
	unsigned int idx;
} Dz1MfcFileOperRenRefListMkArrArg;

static Dz1Error _Dz1MfcFileOperRenRefList_get_array(void *ptr, Dz1MfcFileOperRenameEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperRenRefListMkArrArg *arg = (Dz1MfcFileOperRenRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFileOperRenameEntry **Dz1MfcFileOperRenRefList_get_array(Dz1MfcFileOperRenRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFileOperRenameEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFileOperRenameEntry **)Dz1Calloc(sizeof(Dz1MfcFileOperRenameEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFileOperRenRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFileOperRenRefList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFileOperRenRefList_travelForward(Dz1MfcFileOperRenRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFileOperRenRefList_travelBackward(Dz1MfcFileOperRenRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenRefList_find(Dz1MfcFileOperRenRefList *p, Dz1MfcFileOperRenameEntry *key)
{
	return (Dz1MfcFileOperRenameEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFileOperRenRefList_count(Dz1MfcFileOperRenRefList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFileOperRenRefList *Dz1MfcFileOperRenRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperRenRefList *ret = (Dz1MfcFileOperRenRefList *)Dz1Calloc(sizeof(Dz1MfcFileOperRenRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFileOperRenameEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFileOperRenRefList_count;
			ret->travel = Dz1MfcFileOperRenRefList_travelForward;
			ret->travelForward = Dz1MfcFileOperRenRefList_travelForward;
			ret->travelBackward = Dz1MfcFileOperRenRefList_travelBackward;
			ret->get_array = Dz1MfcFileOperRenRefList_get_array;
			ret->add = Dz1MfcFileOperRenRefList_add;
			ret->remove = Dz1MfcFileOperRenRefList_remove;
			ret->find = Dz1MfcFileOperRenRefList_find;
			ret->extract = Dz1MfcFileOperRenRefList_extract;
			ret->cmp = Dz1MfcFileOperRenameEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFileOperRenRefList_clone(void *ptr, Dz1MfcFileOperRenameEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperRenRefList *p = (Dz1MfcFileOperRenRefList *)ptr;
	Dz1MfcFileOperRenameEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFileOperRenRefList *Dz1MfcFileOperRenRefList_clone(Dz1MfcFileOperRenRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperRenRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFileOperRenRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFileOperRenRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFileOperRenRefList_purge(Dz1MfcFileOperRenRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFileOperRenRefList_del(Dz1MfcFileOperRenRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFileOperRenRefList_dump(void *ptr, Dz1MfcFileOperRenameEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFileOperRenameEntry_dump(p, tab);
	return err;
}

void Dz1MfcFileOperRenRefList_dump(Dz1MfcFileOperRenRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFileOperRenRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperRenRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenameDstIndex
static Dz1Error Dz1MfcFileOperRenameDstIndex_add(Dz1MfcFileOperRenameDstIndex *p, Dz1MfcFileOperRenameEntry *data)
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

static bool_t Dz1MfcFileOperRenameDstIndex_remove(Dz1MfcFileOperRenameDstIndex *p, Dz1MfcFileOperRenameEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameDstIndex_extract(Dz1MfcFileOperRenameDstIndex *p, Dz1MfcFileOperRenameEntry *key)
{
	return (Dz1MfcFileOperRenameEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFileOperRenameDstIndexMkArrArg
{
	Dz1MfcFileOperRenameEntry **arr;
	unsigned int idx;
} Dz1MfcFileOperRenameDstIndexMkArrArg;

static Dz1Error _Dz1MfcFileOperRenameDstIndex_get_array(void *ptr, Dz1MfcFileOperRenameEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperRenameDstIndexMkArrArg *arg = (Dz1MfcFileOperRenameDstIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFileOperRenameEntry **Dz1MfcFileOperRenameDstIndex_get_array(Dz1MfcFileOperRenameDstIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFileOperRenameEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFileOperRenameEntry **)Dz1Calloc(sizeof(Dz1MfcFileOperRenameEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFileOperRenameDstIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFileOperRenameDstIndex_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFileOperRenameDstIndex_travelForward(Dz1MfcFileOperRenameDstIndex *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFileOperRenameDstIndex_travelBackward(Dz1MfcFileOperRenameDstIndex *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameDstIndex_find(Dz1MfcFileOperRenameDstIndex *p, Dz1MfcFileOperRenameEntry *key)
{
	return (Dz1MfcFileOperRenameEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFileOperRenameDstIndex_count(Dz1MfcFileOperRenameDstIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _Dz1MfcFileOperRenameDstIndex_cmp(Dz1MfcFileOperRenameEntry *a, Dz1MfcFileOperRenameEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->dst == NULL && b->dst == NULL) ret = 0;
	else if (a->dst == NULL /*&& b->dst != NULL*/) ret = -1;
	else if (/*a->dst != NULL &&*/ b->dst == NULL) ret = 1;
	else if ((ret = Dz1MfcFileEntry_cmp(a->dst, b->dst)) != 0) { }
	return ret;
}

Dz1MfcFileOperRenameDstIndex *Dz1MfcFileOperRenameDstIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperRenameDstIndex *ret = (Dz1MfcFileOperRenameDstIndex *)Dz1Calloc(sizeof(Dz1MfcFileOperRenameDstIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenameDstIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_Dz1MfcFileOperRenameDstIndex_cmp, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFileOperRenameDstIndex_count;
			ret->travel = Dz1MfcFileOperRenameDstIndex_travelForward;
			ret->travelForward = Dz1MfcFileOperRenameDstIndex_travelForward;
			ret->travelBackward = Dz1MfcFileOperRenameDstIndex_travelBackward;
			ret->get_array = Dz1MfcFileOperRenameDstIndex_get_array;
			ret->add = Dz1MfcFileOperRenameDstIndex_add;
			ret->remove = Dz1MfcFileOperRenameDstIndex_remove;
			ret->find = Dz1MfcFileOperRenameDstIndex_find;
			ret->extract = Dz1MfcFileOperRenameDstIndex_extract;
			ret->cmp = _Dz1MfcFileOperRenameDstIndex_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenameDstIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFileOperRenameDstIndex_clone(void *ptr, Dz1MfcFileOperRenameEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperRenameDstIndex *p = (Dz1MfcFileOperRenameDstIndex *)ptr;
	Dz1MfcFileOperRenameEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFileOperRenameDstIndex *Dz1MfcFileOperRenameDstIndex_clone(Dz1MfcFileOperRenameDstIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperRenameDstIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFileOperRenameDstIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenameDstIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFileOperRenameDstIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenameDstIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFileOperRenameDstIndex_purge(Dz1MfcFileOperRenameDstIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFileOperRenameDstIndex_del(Dz1MfcFileOperRenameDstIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFileOperRenameDstIndex_dump(void *ptr, Dz1MfcFileOperRenameEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFileOperRenameEntry_dump(p, tab);
	return err;
}

void Dz1MfcFileOperRenameDstIndex_dump(Dz1MfcFileOperRenameDstIndex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFileOperRenameDstIndex_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperRenameDstIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenameData
Dz1MfcFileOperRenameData *Dz1MfcFileOperRenameData_new(Dz1Str path, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperRenameData *__internal_ret = (Dz1MfcFileOperRenameData *)Dz1Calloc(sizeof(Dz1MfcFileOperRenameData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenameData_delAndSetNull, (void *)&__internal_ret);
		
		if (path && (__internal_ret->path = Dz1Str_clone(path, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->list = Dz1MfcFileOperRenameList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->index = Dz1MfcFileOperRenameDstIndex_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->failed = Dz1MfcFileOperRenRefList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenameData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcFileOperRenameData_copy(Dz1MfcFileOperRenameData *dst, Dz1MfcFileOperRenameData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->path && (dst->path = Dz1Str_clone(src->path, errp)) == NULL) ERR_OUT(errp);
	else if (src->list && (dst->list = Dz1MfcFileOperRenameList_clone(src->list, errp)) == NULL) ERR_OUT(errp);
	else if (src->index && (dst->index = Dz1MfcFileOperRenameDstIndex_clone(src->index, errp)) == NULL) ERR_OUT(errp);
	else if (src->failed && (dst->failed = Dz1MfcFileOperRenRefList_clone(src->failed, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFileOperRenameData *Dz1MfcFileOperRenameData_clone(Dz1MfcFileOperRenameData *src, Dz1Error *err)
{
	Dz1MfcFileOperRenameData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcFileOperRenameData *)Dz1Calloc(sizeof(Dz1MfcFileOperRenameData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperRenameData_delAndSetNull, (void *)&dst);
		if (Dz1MfcFileOperRenameData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperRenameData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcFileOperRenameData_purge(Dz1MfcFileOperRenameData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->path);
	Dz1MfcFileOperRenameList_del(p->list);
	Dz1MfcFileOperRenameDstIndex_del(p->index);
	Dz1MfcFileOperRenRefList_del(p->failed);
}

void Dz1MfcFileOperRenameData_del(Dz1MfcFileOperRenameData *p)
{
	if (p == NULL) return;
	Dz1MfcFileOperRenameData_purge(p);
	Dz1Free(p);
}

void Dz1MfcFileOperRenameData_dump(Dz1MfcFileOperRenameData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("path = ")); Dz1Str_dump(p->path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("list = ")); Dz1MfcFileOperRenameList_dump(p->list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("index = ")); Dz1MfcFileOperRenameDstIndex_dump(p->index, tab); 
		Dz1Thread_tprintf(tab, Dz1T("failed = ")); Dz1MfcFileOperRenRefList_dump(p->failed, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperRenameData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyOptPresent
static struct Dz1MfcFileOperCopyOptPresentMapA
{
	str_t str;
	Dz1MfcFileOperCopyOptPresent v;
} Dz1MfcFileOperCopyOptPresentMapA[] =
{
	{ (char *)"rename", Dz1MfcFileOperCopyOptPresent_rename },
	{ (char *)"overwirte", Dz1MfcFileOperCopyOptPresent_overwirte },
	{ (char *)"skip", Dz1MfcFileOperCopyOptPresent_skip },
	{ NULL, Dz1MfcFileOperCopyOptPresent_max }
};

str_t Dz1MfcFileOperCopyOptPresentStrA(Dz1MfcFileOperCopyOptPresent v)
{
	struct Dz1MfcFileOperCopyOptPresentMapA *i = NULL;
	for (i = Dz1MfcFileOperCopyOptPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcFileOperCopyOptPresent Dz1MfcFileOperCopyOptPresentFromStrA(str_t str)
{
	struct Dz1MfcFileOperCopyOptPresentMapA *i = NULL;
	for (i = Dz1MfcFileOperCopyOptPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcFileOperCopyOptPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MfcFileOperCopyOptPresentMapW
{
	wstr_t str;
	Dz1MfcFileOperCopyOptPresent v;
} Dz1MfcFileOperCopyOptPresentMapW[] =
{
	{ (wchar_t *)L"rename", Dz1MfcFileOperCopyOptPresent_rename },
	{ (wchar_t *)L"overwirte", Dz1MfcFileOperCopyOptPresent_overwirte },
	{ (wchar_t *)L"skip", Dz1MfcFileOperCopyOptPresent_skip },
	{ NULL, Dz1MfcFileOperCopyOptPresent_max }
};

wstr_t Dz1MfcFileOperCopyOptPresentStrW(Dz1MfcFileOperCopyOptPresent v)
{
	struct Dz1MfcFileOperCopyOptPresentMapW *i = NULL;
	for (i = Dz1MfcFileOperCopyOptPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcFileOperCopyOptPresent Dz1MfcFileOperCopyOptPresentFromStrW(wstr_t str)
{
	struct Dz1MfcFileOperCopyOptPresentMapW *i = NULL;
	for (i = Dz1MfcFileOperCopyOptPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcFileOperCopyOptPresent_max;
}
#endif // UNIX_SYSTEM

Dz1MfcFileOperCopyOptPresent *Dz1MfcFileOperCopyOptPresent_new(Dz1MfcFileOperCopyOptPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperCopyOptPresent *__internal_ret = (Dz1MfcFileOperCopyOptPresent *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyOptPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1MfcFileOperCopyOptPresent_dump(Dz1MfcFileOperCopyOptPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1MfcFileOperCopyOptPresentStr(*v));
}
// Dz1MfcFileOperCopyOptPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyOpt
Dz1MfcFileOperCopyOpt *Dz1MfcFileOperCopyOpt_new(Dz1MfcFileOperCopyOptPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperCopyOpt *ret = (Dz1MfcFileOperCopyOpt *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyOpt), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyOpt_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1MfcFileOperCopyOptPresent_rename:
			// _U_prim_clone
			if (ptr && (ret->x.rename = Dz1Str_clone((Dz1Str)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1MfcFileOperCopyOptPresent_overwirte:
			// _U_prim_clone
			if (ptr != NULL) ret->x.overwirte = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MfcFileOperCopyOptPresent_skip:
			// _U_prim_clone
			if (ptr != NULL) ret->x.skip = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MfcFileOperCopyOptPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyOpt_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1MfcFileOperCopyOpt_copy(Dz1MfcFileOperCopyOpt *ret, Dz1MfcFileOperCopyOpt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1MfcFileOperCopyOptPresent_rename:
			// _U_prim_clone
			if (src->x.rename && (ret->x.rename = Dz1Str_clone(src->x.rename, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1MfcFileOperCopyOptPresent_overwirte:
			// _U_prim_clone
			if (src->x.overwirte && (ret->x.overwirte = Dz1u32_clone(src->x.overwirte, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1MfcFileOperCopyOptPresent_skip:
			// _U_prim_clone
			if (src->x.skip && (ret->x.skip = Dz1u32_clone(src->x.skip, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFileOperCopyOpt *Dz1MfcFileOperCopyOpt_clone(Dz1MfcFileOperCopyOpt *src, Dz1Error *err)
{
	Dz1MfcFileOperCopyOpt *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1MfcFileOperCopyOpt *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyOpt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyOpt_delAndSetNull, (void *)&ret);
		if (Dz1MfcFileOperCopyOpt_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyOpt_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFileOperCopyOpt_purge(Dz1MfcFileOperCopyOpt *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1MfcFileOperCopyOptPresent_rename:
		Dz1Str_del(p->x.rename);
		break;
	case Dz1MfcFileOperCopyOptPresent_overwirte:
		Dz1u32_del(p->x.overwirte);
		break;
	case Dz1MfcFileOperCopyOptPresent_skip:
		Dz1u32_del(p->x.skip);
		break;
	default:
		break;
	}
}

void Dz1MfcFileOperCopyOpt_del(Dz1MfcFileOperCopyOpt *p)
{
	if (!p) return;
	Dz1MfcFileOperCopyOpt_purge(p);
	Dz1Free(p);
}

void Dz1MfcFileOperCopyOpt_dump(Dz1MfcFileOperCopyOpt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1MfcFileOperCopyOptPresent_rename:
		Dz1Thread_printf(Dz1T("rename = ")); Dz1Str_dump(p->x.rename, tab); 
		break;
	case Dz1MfcFileOperCopyOptPresent_overwirte:
		Dz1Thread_printf(Dz1T("overwirte = ")); Dz1u32_dump(p->x.overwirte, tab); 
		break;
	case Dz1MfcFileOperCopyOptPresent_skip:
		Dz1Thread_printf(Dz1T("skip = ")); Dz1u32_dump(p->x.skip, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1MfcFileOperCopyOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyCollision
Dz1MfcFileOperCopyCollision *Dz1MfcFileOperCopyCollision_new(u64_t src_size, 
															 u64_t dst_size, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperCopyCollision *__internal_ret = (Dz1MfcFileOperCopyCollision *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyCollision), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyCollision_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->src_size = src_size;
		__internal_ret->dst_size = dst_size;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyCollision_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcFileOperCopyCollision_copy(Dz1MfcFileOperCopyCollision *dst, Dz1MfcFileOperCopyCollision *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->src_size = src->src_size;
		dst->dst_size = src->dst_size;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFileOperCopyCollision *Dz1MfcFileOperCopyCollision_clone(Dz1MfcFileOperCopyCollision *src, Dz1Error *err)
{
	Dz1MfcFileOperCopyCollision *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcFileOperCopyCollision *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyCollision), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyCollision_delAndSetNull, (void *)&dst);
		if (Dz1MfcFileOperCopyCollision_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyCollision_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcFileOperCopyCollision_purge(Dz1MfcFileOperCopyCollision *p)
{
	if (p == NULL) return;
}

void Dz1MfcFileOperCopyCollision_del(Dz1MfcFileOperCopyCollision *p)
{
	if (p == NULL) return;
	Dz1MfcFileOperCopyCollision_purge(p);
	Dz1Free(p);
}

void Dz1MfcFileOperCopyCollision_dump(Dz1MfcFileOperCopyCollision *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("src_size = ")); Dz1u64_dump(&p->src_size, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dst_size = ")); Dz1u64_dump(&p->dst_size, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperCopyCollision
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyEntry
Dz1MfcFileOperCopyEntry *Dz1MfcFileOperCopyEntry_new(Dz1MfcFileEntry *file, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperCopyEntry *__internal_ret = (Dz1MfcFileOperCopyEntry *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->file = file;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcFileOperCopyEntry_copy(Dz1MfcFileOperCopyEntry *dst, Dz1MfcFileOperCopyEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->file && (dst->file = Dz1MfcFileEntry_clone(src->file, errp)) == NULL) ERR_OUT(errp);
	else if (src->opt && (dst->opt = Dz1MfcFileOperCopyOpt_clone(src->opt, errp)) == NULL) ERR_OUT(errp);
	else if (src->collision && (dst->collision = Dz1MfcFileOperCopyCollision_clone(src->collision, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->state = src->state;
		dst->fail_code = src->fail_code;
		dst->copied = src->copied;
		dst->total = src->total;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFileOperCopyEntry *Dz1MfcFileOperCopyEntry_clone(Dz1MfcFileOperCopyEntry *src, Dz1Error *err)
{
	Dz1MfcFileOperCopyEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcFileOperCopyEntry *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyEntry_delAndSetNull, (void *)&dst);
		if (Dz1MfcFileOperCopyEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcFileOperCopyEntry_purge(Dz1MfcFileOperCopyEntry *p)
{
	if (p == NULL) return;
	Dz1MfcFileEntry_del(p->file);
	Dz1MfcFileOperCopyOpt_del(p->opt);
	Dz1MfcFileOperCopyCollision_del(p->collision);
}

void Dz1MfcFileOperCopyEntry_del(Dz1MfcFileOperCopyEntry *p)
{
	if (p == NULL) return;
	Dz1MfcFileOperCopyEntry_purge(p);
	Dz1Free(p);
}

void Dz1MfcFileOperCopyEntry_dump(Dz1MfcFileOperCopyEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("file = ")); Dz1MfcFileEntry_dump(p->file, tab); 
		Dz1Thread_tprintf(tab, Dz1T("opt.")); Dz1MfcFileOperCopyOpt_dump(p->opt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), Dz1MfcFileOperStateStr(p->state), p->state);
		Dz1Thread_tprintf(tab, Dz1T("fail_code = ")); Dz1s32_dump(&p->fail_code, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("collision = ")); Dz1MfcFileOperCopyCollision_dump(p->collision, tab); 
		Dz1Thread_tprintf(tab, Dz1T("copied = ")); Dz1s64_dump(&p->copied, tab); 
		Dz1Thread_tprintf(tab, Dz1T("total = ")); Dz1s64_dump(&p->total, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcFileOperCopyEntry_cmp(Dz1MfcFileOperCopyEntry *a, Dz1MfcFileOperCopyEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->file == NULL && b->file == NULL) ret = 0;
	else if (a->file == NULL /*&& b->file != NULL*/) ret = -1;
	else if (/*a->file != NULL &&*/ b->file == NULL) ret = 1;
	else if ((ret = Dz1MfcFileEntry_cmp(a->file, b->file)) != 0) { }
	return ret;
}
// Dz1MfcFileOperCopyEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyList
static Dz1Error Dz1MfcFileOperCopyList_add(Dz1MfcFileOperCopyList *p, Dz1MfcFileOperCopyEntry *data)
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

static bool_t Dz1MfcFileOperCopyList_remove(Dz1MfcFileOperCopyList *p, Dz1MfcFileOperCopyEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFileOperCopyEntry *Dz1MfcFileOperCopyList_extract(Dz1MfcFileOperCopyList *p, Dz1MfcFileOperCopyEntry *key)
{
	return (Dz1MfcFileOperCopyEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFileOperCopyListMkArrArg
{
	Dz1MfcFileOperCopyEntry **arr;
	unsigned int idx;
} Dz1MfcFileOperCopyListMkArrArg;

static Dz1Error _Dz1MfcFileOperCopyList_get_array(void *ptr, Dz1MfcFileOperCopyEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperCopyListMkArrArg *arg = (Dz1MfcFileOperCopyListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFileOperCopyEntry **Dz1MfcFileOperCopyList_get_array(Dz1MfcFileOperCopyList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFileOperCopyEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFileOperCopyEntry **)Dz1Calloc(sizeof(Dz1MfcFileOperCopyEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFileOperCopyListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFileOperCopyList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFileOperCopyList_travelForward(Dz1MfcFileOperCopyList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFileOperCopyList_travelBackward(Dz1MfcFileOperCopyList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFileOperCopyEntry *Dz1MfcFileOperCopyList_find(Dz1MfcFileOperCopyList *p, Dz1MfcFileOperCopyEntry *key)
{
	return (Dz1MfcFileOperCopyEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFileOperCopyList_count(Dz1MfcFileOperCopyList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFileOperCopyList *Dz1MfcFileOperCopyList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperCopyList *ret = (Dz1MfcFileOperCopyList *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFileOperCopyEntry_cmp,
				(Dz1DelFunc)Dz1MfcFileOperCopyEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFileOperCopyList_count;
			ret->travel = Dz1MfcFileOperCopyList_travelForward;
			ret->travelForward = Dz1MfcFileOperCopyList_travelForward;
			ret->travelBackward = Dz1MfcFileOperCopyList_travelBackward;
			ret->get_array = Dz1MfcFileOperCopyList_get_array;
			ret->add = Dz1MfcFileOperCopyList_add;
			ret->remove = Dz1MfcFileOperCopyList_remove;
			ret->find = Dz1MfcFileOperCopyList_find;
			ret->extract = Dz1MfcFileOperCopyList_extract;
			ret->cmp = Dz1MfcFileOperCopyEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFileOperCopyList_clone(void *ptr, Dz1MfcFileOperCopyEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperCopyList *p = (Dz1MfcFileOperCopyList *)ptr;
	Dz1MfcFileOperCopyEntry *cloned = Dz1MfcFileOperCopyEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFileOperCopyList *Dz1MfcFileOperCopyList_clone(Dz1MfcFileOperCopyList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperCopyList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFileOperCopyList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFileOperCopyList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFileOperCopyList_purge(Dz1MfcFileOperCopyList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFileOperCopyList_del(Dz1MfcFileOperCopyList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFileOperCopyList_dump(void *ptr, Dz1MfcFileOperCopyEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFileOperCopyEntry_dump(p, tab);
	return err;
}

void Dz1MfcFileOperCopyList_dump(Dz1MfcFileOperCopyList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFileOperCopyList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperCopyList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyRefList
static Dz1Error Dz1MfcFileOperCopyRefList_add(Dz1MfcFileOperCopyRefList *p, Dz1MfcFileOperCopyEntry *data)
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

static bool_t Dz1MfcFileOperCopyRefList_remove(Dz1MfcFileOperCopyRefList *p, Dz1MfcFileOperCopyEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFileOperCopyEntry *Dz1MfcFileOperCopyRefList_extract(Dz1MfcFileOperCopyRefList *p, Dz1MfcFileOperCopyEntry *key)
{
	return (Dz1MfcFileOperCopyEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFileOperCopyRefListMkArrArg
{
	Dz1MfcFileOperCopyEntry **arr;
	unsigned int idx;
} Dz1MfcFileOperCopyRefListMkArrArg;

static Dz1Error _Dz1MfcFileOperCopyRefList_get_array(void *ptr, Dz1MfcFileOperCopyEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperCopyRefListMkArrArg *arg = (Dz1MfcFileOperCopyRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFileOperCopyEntry **Dz1MfcFileOperCopyRefList_get_array(Dz1MfcFileOperCopyRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFileOperCopyEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFileOperCopyEntry **)Dz1Calloc(sizeof(Dz1MfcFileOperCopyEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFileOperCopyRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFileOperCopyRefList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFileOperCopyRefList_travelForward(Dz1MfcFileOperCopyRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFileOperCopyRefList_travelBackward(Dz1MfcFileOperCopyRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFileOperCopyEntry *Dz1MfcFileOperCopyRefList_find(Dz1MfcFileOperCopyRefList *p, Dz1MfcFileOperCopyEntry *key)
{
	return (Dz1MfcFileOperCopyEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFileOperCopyRefList_count(Dz1MfcFileOperCopyRefList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFileOperCopyRefList *Dz1MfcFileOperCopyRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperCopyRefList *ret = (Dz1MfcFileOperCopyRefList *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFileOperCopyEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFileOperCopyRefList_count;
			ret->travel = Dz1MfcFileOperCopyRefList_travelForward;
			ret->travelForward = Dz1MfcFileOperCopyRefList_travelForward;
			ret->travelBackward = Dz1MfcFileOperCopyRefList_travelBackward;
			ret->get_array = Dz1MfcFileOperCopyRefList_get_array;
			ret->add = Dz1MfcFileOperCopyRefList_add;
			ret->remove = Dz1MfcFileOperCopyRefList_remove;
			ret->find = Dz1MfcFileOperCopyRefList_find;
			ret->extract = Dz1MfcFileOperCopyRefList_extract;
			ret->cmp = Dz1MfcFileOperCopyEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFileOperCopyRefList_clone(void *ptr, Dz1MfcFileOperCopyEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFileOperCopyRefList *p = (Dz1MfcFileOperCopyRefList *)ptr;
	Dz1MfcFileOperCopyEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFileOperCopyRefList *Dz1MfcFileOperCopyRefList_clone(Dz1MfcFileOperCopyRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperCopyRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFileOperCopyRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFileOperCopyRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFileOperCopyRefList_purge(Dz1MfcFileOperCopyRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFileOperCopyRefList_del(Dz1MfcFileOperCopyRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFileOperCopyRefList_dump(void *ptr, Dz1MfcFileOperCopyEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFileOperCopyEntry_dump(p, tab);
	return err;
}

void Dz1MfcFileOperCopyRefList_dump(Dz1MfcFileOperCopyRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFileOperCopyRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperCopyRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyData
Dz1MfcFileOperCopyData *Dz1MfcFileOperCopyData_new(Dz1Str src_path, 
												   Dz1Str dst_path, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFileOperCopyData *__internal_ret = (Dz1MfcFileOperCopyData *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyData_delAndSetNull, (void *)&__internal_ret);
		
		if (src_path && (__internal_ret->src_path = Dz1Str_clone(src_path, errp)) == NULL) ERR_OUT(errp);
		else if (dst_path && (__internal_ret->dst_path = Dz1Str_clone(dst_path, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->files = Dz1MfcFileOperCopyList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->failed = Dz1MfcFileOperCopyRefList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcFileOperCopyData_copy(Dz1MfcFileOperCopyData *dst, Dz1MfcFileOperCopyData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->src_path && (dst->src_path = Dz1Str_clone(src->src_path, errp)) == NULL) ERR_OUT(errp);
	else if (src->dst_path && (dst->dst_path = Dz1Str_clone(src->dst_path, errp)) == NULL) ERR_OUT(errp);
	else if (src->files && (dst->files = Dz1MfcFileOperCopyList_clone(src->files, errp)) == NULL) ERR_OUT(errp);
	else if (src->failed && (dst->failed = Dz1MfcFileOperCopyRefList_clone(src->failed, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->copied = src->copied;
		dst->total = src->total;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcFileOperCopyData *Dz1MfcFileOperCopyData_clone(Dz1MfcFileOperCopyData *src, Dz1Error *err)
{
	Dz1MfcFileOperCopyData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcFileOperCopyData *)Dz1Calloc(sizeof(Dz1MfcFileOperCopyData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyData_delAndSetNull, (void *)&dst);
		if (Dz1MfcFileOperCopyData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFileOperCopyData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcFileOperCopyData_purge(Dz1MfcFileOperCopyData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->src_path);
	Dz1Str_del(p->dst_path);
	Dz1MfcFileOperCopyList_del(p->files);
	Dz1MfcFileOperCopyRefList_del(p->failed);
}

void Dz1MfcFileOperCopyData_del(Dz1MfcFileOperCopyData *p)
{
	if (p == NULL) return;
	Dz1MfcFileOperCopyData_purge(p);
	Dz1Free(p);
}

void Dz1MfcFileOperCopyData_dump(Dz1MfcFileOperCopyData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("src_path = ")); Dz1Str_dump(p->src_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dst_path = ")); Dz1Str_dump(p->dst_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("files = ")); Dz1MfcFileOperCopyList_dump(p->files, tab); 
		Dz1Thread_tprintf(tab, Dz1T("copied = ")); Dz1s64_dump(&p->copied, tab); 
		Dz1Thread_tprintf(tab, Dz1T("total = ")); Dz1s64_dump(&p->total, tab); 
		Dz1Thread_tprintf(tab, Dz1T("failed = ")); Dz1MfcFileOperCopyRefList_dump(p->failed, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFileOperCopyData
////////////////////////////////////////////////////////////////////////////////

