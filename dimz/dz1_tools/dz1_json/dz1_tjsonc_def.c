////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tjsonc_def.h"

////////////////////////////////////////////////////////////////////////////////
// ObjectInfoIndex
static Dz1Error ObjectInfoIndex_add(ObjectInfoIndex *p, ObjectInfo *data)
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

static bool_t ObjectInfoIndex_remove(ObjectInfoIndex *p, ObjectInfo *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ObjectInfo *ObjectInfoIndex_extract(ObjectInfoIndex *p, ObjectInfo *key)
{
	return (ObjectInfo *)Dz1AATree_extract(p->storage, key);
}

typedef struct ObjectInfoIndexMkArrArg
{
	ObjectInfo **arr;
	unsigned int idx;
} ObjectInfoIndexMkArrArg;

static Dz1Error _ObjectInfoIndex_get_array(void *ptr, ObjectInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ObjectInfoIndexMkArrArg *arg = (ObjectInfoIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ObjectInfo **ObjectInfoIndex_get_array(ObjectInfoIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ObjectInfo **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ObjectInfo **)Dz1Calloc(sizeof(ObjectInfo *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ObjectInfoIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ObjectInfoIndex_get_array, (void *)&arg);
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

static Dz1Error ObjectInfoIndex_travelForward(ObjectInfoIndex *p, Dz1Error (*func)(void *ptr, ObjectInfo *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ObjectInfoIndex_travelBackward(ObjectInfoIndex *p, Dz1Error (*func)(void *ptr, ObjectInfo *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ObjectInfo *ObjectInfoIndex_find(ObjectInfoIndex *p, ObjectInfo *key)
{
	return (ObjectInfo *)Dz1AATree_find(p->storage, key);
}

static unsigned int ObjectInfoIndex_count(ObjectInfoIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ObjectInfoIndex *ObjectInfoIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ObjectInfoIndex *ret = (ObjectInfoIndex *)Dz1Calloc(sizeof(ObjectInfoIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ObjectInfoIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ObjectInfo_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ObjectInfoIndex_count;
			ret->travel = ObjectInfoIndex_travelForward;
			ret->travelForward = ObjectInfoIndex_travelForward;
			ret->travelBackward = ObjectInfoIndex_travelBackward;
			ret->get_array = ObjectInfoIndex_get_array;
			ret->add = ObjectInfoIndex_add;
			ret->remove = ObjectInfoIndex_remove;
			ret->find = ObjectInfoIndex_find;
			ret->extract = ObjectInfoIndex_extract;
			ret->cmp = ObjectInfo_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ObjectInfoIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _ObjectInfoIndex_clone(void *ptr, ObjectInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ObjectInfoIndex *p = (ObjectInfoIndex *)ptr;
	ObjectInfo *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

ObjectInfoIndex *ObjectInfoIndex_clone(ObjectInfoIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ObjectInfoIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ObjectInfoIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ObjectInfoIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_ObjectInfoIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (ObjectInfoIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ObjectInfoIndex_purge(ObjectInfoIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ObjectInfoIndex_del(ObjectInfoIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ObjectInfoIndex_dump(void *ptr, ObjectInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ObjectInfo_dump(p, tab);
	return err;
}

void ObjectInfoIndex_dump(ObjectInfoIndex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ObjectInfoIndex_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ObjectInfoIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ObjectInfoSeq
static Dz1Error ObjectInfoSeq_add(ObjectInfoSeq *p, ObjectInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct ObjectInfoSeqMkArrArg
{
	ObjectInfo **arr;
	unsigned int idx;
} ObjectInfoSeqMkArrArg;

static Dz1Error _ObjectInfoSeq_get_array(void *ptr, ObjectInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ObjectInfoSeqMkArrArg *arg = (ObjectInfoSeqMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ObjectInfo **ObjectInfoSeq_get_array(ObjectInfoSeq *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ObjectInfo **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ObjectInfo **)Dz1Calloc(sizeof(ObjectInfo *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ObjectInfoSeqMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ObjectInfoSeq_get_array, (void *)&arg);
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

static Dz1Error ObjectInfoSeq_travelForward(ObjectInfoSeq *p, Dz1Error (*func)(void *ptr, ObjectInfo *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error ObjectInfoSeq_travelBackward(ObjectInfoSeq *p, Dz1Error (*func)(void *ptr, ObjectInfo *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int ObjectInfoSeq_count(ObjectInfoSeq *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

ObjectInfoSeq *ObjectInfoSeq_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ObjectInfoSeq *ret = (ObjectInfoSeq *)Dz1Calloc(sizeof(ObjectInfoSeq), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ObjectInfoSeq_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ObjectInfoSeq_count;
			ret->travel = ObjectInfoSeq_travelForward;
			ret->travelForward = ObjectInfoSeq_travelForward;
			ret->travelBackward = ObjectInfoSeq_travelBackward;
			ret->get_array = ObjectInfoSeq_get_array;
			ret->add = ObjectInfoSeq_add;
			ret->cmp = ObjectInfo_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ObjectInfoSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _ObjectInfoSeq_clone(void *ptr, ObjectInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ObjectInfoSeq *p = (ObjectInfoSeq *)ptr;
	ObjectInfo *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

ObjectInfoSeq *ObjectInfoSeq_clone(ObjectInfoSeq *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ObjectInfoSeq *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ObjectInfoSeq_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ObjectInfoSeq_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_ObjectInfoSeq_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (ObjectInfoSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ObjectInfoSeq_purge(ObjectInfoSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void ObjectInfoSeq_del(ObjectInfoSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ObjectInfoSeq_dump(void *ptr, ObjectInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ObjectInfo_dump(p, tab);
	return err;
}

void ObjectInfoSeq_dump(ObjectInfoSeq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ObjectInfoSeq_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ObjectInfoSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonTargetObjects
Dz1JsonTargetObjects *Dz1JsonTargetObjects_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonTargetObjects *__internal_ret = (Dz1JsonTargetObjects *)Dz1Calloc(sizeof(Dz1JsonTargetObjects), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonTargetObjects_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->index = ObjectInfoIndex_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->seq = ObjectInfoSeq_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonTargetObjects_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonTargetObjects_purge(Dz1JsonTargetObjects *p)
{
	if (p == NULL) return;
	ObjectInfoIndex_del(p->index);
	ObjectInfoSeq_del(p->seq);
}

void Dz1JsonTargetObjects_del(Dz1JsonTargetObjects *p)
{
	if (p == NULL) return;
	Dz1JsonTargetObjects_purge(p);
	Dz1Free(p);
}

void Dz1JsonTargetObjects_dump(Dz1JsonTargetObjects *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("seq = ")); ObjectInfoSeq_dump(p->seq, tab); 
	}
}
// Dz1JsonTargetObjects
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonCompileIncIndex
static Dz1Error Dz1JsonCompileIncIndex_add(Dz1JsonCompileIncIndex *p, Dz1Str data)
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

static bool_t Dz1JsonCompileIncIndex_remove(Dz1JsonCompileIncIndex *p, Dz1Str key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1Str Dz1JsonCompileIncIndex_extract(Dz1JsonCompileIncIndex *p, Dz1Str key)
{
	return (Dz1Str )Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1JsonCompileIncIndexMkArrArg
{
	Dz1Str *arr;
	unsigned int idx;
} Dz1JsonCompileIncIndexMkArrArg;

static Dz1Error _Dz1JsonCompileIncIndex_get_array(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonCompileIncIndexMkArrArg *arg = (Dz1JsonCompileIncIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1Str *Dz1JsonCompileIncIndex_get_array(Dz1JsonCompileIncIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1Str *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Str *)Dz1Calloc(sizeof(Dz1Str *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonCompileIncIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1JsonCompileIncIndex_get_array, (void *)&arg);
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

static Dz1Error Dz1JsonCompileIncIndex_travelForward(Dz1JsonCompileIncIndex *p, Dz1Error (*func)(void *ptr, Dz1Str data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1JsonCompileIncIndex_travelBackward(Dz1JsonCompileIncIndex *p, Dz1Error (*func)(void *ptr, Dz1Str data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Str Dz1JsonCompileIncIndex_find(Dz1JsonCompileIncIndex *p, Dz1Str key)
{
	return (Dz1Str )Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1JsonCompileIncIndex_count(Dz1JsonCompileIncIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1JsonCompileIncIndex *Dz1JsonCompileIncIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonCompileIncIndex *ret = (Dz1JsonCompileIncIndex *)Dz1Calloc(sizeof(Dz1JsonCompileIncIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonCompileIncIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1Str_cmp,
				(Dz1DelFunc)Dz1Str_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1JsonCompileIncIndex_count;
			ret->travel = Dz1JsonCompileIncIndex_travelForward;
			ret->travelForward = Dz1JsonCompileIncIndex_travelForward;
			ret->travelBackward = Dz1JsonCompileIncIndex_travelBackward;
			ret->get_array = Dz1JsonCompileIncIndex_get_array;
			ret->add = Dz1JsonCompileIncIndex_add;
			ret->remove = Dz1JsonCompileIncIndex_remove;
			ret->find = Dz1JsonCompileIncIndex_find;
			ret->extract = Dz1JsonCompileIncIndex_extract;
			ret->cmp = Dz1Str_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonCompileIncIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1JsonCompileIncIndex_clone(void *ptr, Dz1Str data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonCompileIncIndex *p = (Dz1JsonCompileIncIndex *)ptr;
	Dz1Str cloned = Dz1Str_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1JsonCompileIncIndex *Dz1JsonCompileIncIndex_clone(Dz1JsonCompileIncIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonCompileIncIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1JsonCompileIncIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonCompileIncIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1JsonCompileIncIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonCompileIncIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1JsonCompileIncIndex_purge(Dz1JsonCompileIncIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1JsonCompileIncIndex_del(Dz1JsonCompileIncIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1JsonCompileIncIndex_dump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1Str_dump(p, tab);
	return err;
}

void Dz1JsonCompileIncIndex_dump(Dz1JsonCompileIncIndex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1JsonCompileIncIndex_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _Dz1JsonCompileIncIndex_fdump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); Dz1Str_fdump(arg->fp, p, tab);
	return err;
}

void Dz1JsonCompileIncIndex_fdump(FILE *fp, Dz1JsonCompileIncIndex *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1JsonCompileIncIndex_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// Dz1JsonCompileIncIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonCompileIncSeq
static Dz1Error Dz1JsonCompileIncSeq_add(Dz1JsonCompileIncSeq *p, Dz1Str data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1JsonCompileIncSeqMkArrArg
{
	Dz1Str *arr;
	unsigned int idx;
} Dz1JsonCompileIncSeqMkArrArg;

static Dz1Error _Dz1JsonCompileIncSeq_get_array(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonCompileIncSeqMkArrArg *arg = (Dz1JsonCompileIncSeqMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1Str *Dz1JsonCompileIncSeq_get_array(Dz1JsonCompileIncSeq *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1Str *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Str *)Dz1Calloc(sizeof(Dz1Str *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonCompileIncSeqMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1JsonCompileIncSeq_get_array, (void *)&arg);
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

static Dz1Error Dz1JsonCompileIncSeq_travelForward(Dz1JsonCompileIncSeq *p, Dz1Error (*func)(void *ptr, Dz1Str data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1JsonCompileIncSeq_travelBackward(Dz1JsonCompileIncSeq *p, Dz1Error (*func)(void *ptr, Dz1Str data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1JsonCompileIncSeq_count(Dz1JsonCompileIncSeq *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1JsonCompileIncSeq *Dz1JsonCompileIncSeq_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonCompileIncSeq *ret = (Dz1JsonCompileIncSeq *)Dz1Calloc(sizeof(Dz1JsonCompileIncSeq), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonCompileIncSeq_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1JsonCompileIncSeq_count;
			ret->travel = Dz1JsonCompileIncSeq_travelForward;
			ret->travelForward = Dz1JsonCompileIncSeq_travelForward;
			ret->travelBackward = Dz1JsonCompileIncSeq_travelBackward;
			ret->get_array = Dz1JsonCompileIncSeq_get_array;
			ret->add = Dz1JsonCompileIncSeq_add;
			ret->cmp = Dz1Str_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonCompileIncSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1JsonCompileIncSeq_clone(void *ptr, Dz1Str data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonCompileIncSeq *p = (Dz1JsonCompileIncSeq *)ptr;
	Dz1Str cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1JsonCompileIncSeq *Dz1JsonCompileIncSeq_clone(Dz1JsonCompileIncSeq *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonCompileIncSeq *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1JsonCompileIncSeq_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonCompileIncSeq_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1JsonCompileIncSeq_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonCompileIncSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1JsonCompileIncSeq_purge(Dz1JsonCompileIncSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1JsonCompileIncSeq_del(Dz1JsonCompileIncSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1JsonCompileIncSeq_dump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1Str_dump(p, tab);
	return err;
}

void Dz1JsonCompileIncSeq_dump(Dz1JsonCompileIncSeq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1JsonCompileIncSeq_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _Dz1JsonCompileIncSeq_fdump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); Dz1Str_fdump(arg->fp, p, tab);
	return err;
}

void Dz1JsonCompileIncSeq_fdump(FILE *fp, Dz1JsonCompileIncSeq *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1JsonCompileIncSeq_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// Dz1JsonCompileIncSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonCompileIncs
Dz1JsonCompileIncs *Dz1JsonCompileIncs_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonCompileIncs *__internal_ret = (Dz1JsonCompileIncs *)Dz1Calloc(sizeof(Dz1JsonCompileIncs), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonCompileIncs_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->index = Dz1JsonCompileIncIndex_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->seq = Dz1JsonCompileIncSeq_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonCompileIncs_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonCompileIncs_purge(Dz1JsonCompileIncs *p)
{
	if (p == NULL) return;
	Dz1JsonCompileIncIndex_del(p->index);
	Dz1JsonCompileIncSeq_del(p->seq);
}

void Dz1JsonCompileIncs_del(Dz1JsonCompileIncs *p)
{
	if (p == NULL) return;
	Dz1JsonCompileIncs_purge(p);
	Dz1Free(p);
}

void Dz1JsonCompileIncs_dump(Dz1JsonCompileIncs *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("seq = ")); Dz1JsonCompileIncSeq_dump(p->seq, tab); 
	}
}
// Dz1JsonCompileIncs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonCompilerArg
Dz1JsonCompilerArg *Dz1JsonCompilerArg_new(Dz1JsonCompileIncs *src_module_inc, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonCompilerArg *__internal_ret = (Dz1JsonCompilerArg *)Dz1Calloc(sizeof(Dz1JsonCompilerArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonCompilerArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->src_module_inc = src_module_inc;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonCompilerArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonCompilerArg_purge(Dz1JsonCompilerArg *p)
{
	if (p == NULL) return;
	Dz1JsonCompileIncs_del(p->src_module_inc);
	Dz1Str_del(p->src_out_path);
	Dz1Str_del(p->hdr_out_path);
	Dz1Str_del(p->suffix);
	Dz1Str_del(p->tgt_fn);
	Dz1Str_del(p->tgt_path);
	Dz1Str_del(p->tgt_name);
	Dz1Str_del(p->tgt_ext);
	Dz1Str_del(p->output_name);
}

void Dz1JsonCompilerArg_del(Dz1JsonCompilerArg *p)
{
	if (p == NULL) return;
	Dz1JsonCompilerArg_purge(p);
	Dz1Free(p);
}

void Dz1JsonCompilerArg_dump(Dz1JsonCompilerArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("src_module_inc = ")); Dz1JsonCompileIncs_dump(p->src_module_inc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("src_out_path = ")); Dz1Str_dump(p->src_out_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hdr_out_path = ")); Dz1Str_dump(p->hdr_out_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("src_out = ")); Dz1Bool_dump(&p->src_out, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hdr_out = ")); Dz1Bool_dump(&p->hdr_out, tab); 
		Dz1Thread_tprintf(tab, Dz1T("suffix = ")); Dz1Str_dump(p->suffix, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tgt_fn = ")); Dz1Str_dump(p->tgt_fn, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tgt_path = ")); Dz1Str_dump(p->tgt_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tgt_name = ")); Dz1Str_dump(p->tgt_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tgt_ext = ")); Dz1Str_dump(p->tgt_ext, tab); 
		Dz1Thread_tprintf(tab, Dz1T("output_name = ")); Dz1Str_dump(p->output_name, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonCompilerArg
////////////////////////////////////////////////////////////////////////////////

