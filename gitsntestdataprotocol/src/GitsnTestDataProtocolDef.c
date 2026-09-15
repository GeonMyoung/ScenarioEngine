////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnTestDataProtocolDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnTestDataFrame
GitsnTestDataFrame *GitsnTestDataFrame_new(u16_t preamble, 
										   u16_t sequence, 
										   u8_t frameType, 
										   u16_t size, 
										   u8_t channelNum, 
										   Dz1Binary *payload, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnTestDataFrame *__internal_ret = (GitsnTestDataFrame *)Dz1Calloc(sizeof(GitsnTestDataFrame), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnTestDataFrame_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->preamble = preamble;
		__internal_ret->sequence = sequence;
		__internal_ret->frameType = frameType;
		__internal_ret->size = size;
		__internal_ret->channelNum = channelNum;
		__internal_ret->payload = payload;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnTestDataFrame_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnTestDataFrame_copy(GitsnTestDataFrame *dst, GitsnTestDataFrame *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->payload && (dst->payload = Dz1Binary_clone(src->payload, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->preamble = src->preamble;
		dst->sequence = src->sequence;
		dst->frameType = src->frameType;
		dst->size = src->size;
		dst->channelNum = src->channelNum;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnTestDataFrame *GitsnTestDataFrame_clone(GitsnTestDataFrame *src, Dz1Error *err)
{
	GitsnTestDataFrame *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnTestDataFrame *)Dz1Calloc(sizeof(GitsnTestDataFrame), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnTestDataFrame_delAndSetNull, (void *)&dst);
		if (GitsnTestDataFrame_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnTestDataFrame_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnTestDataFrame_purge(GitsnTestDataFrame *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->payload);
}

void GitsnTestDataFrame_del(GitsnTestDataFrame *p)
{
	if (p == NULL) return;
	GitsnTestDataFrame_purge(p);
	Dz1Free(p);
}

void GitsnTestDataFrame_dump(GitsnTestDataFrame *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("preamble = ")); Dz1u16_dump(&p->preamble, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sequence = ")); Dz1u16_dump(&p->sequence, tab); 
		Dz1Thread_tprintf(tab, Dz1T("frameType = ")); Dz1u8_dump(&p->frameType, tab); 
		Dz1Thread_tprintf(tab, Dz1T("size = ")); Dz1u16_dump(&p->size, tab); 
		Dz1Thread_tprintf(tab, Dz1T("channelNum = ")); Dz1u8_dump(&p->channelNum, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("payload = ")); Dz1Binary_dump(p->payload, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnTestDataFrame
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnTestDataFrames
static Dz1Error GitsnTestDataFrames_add(GitsnTestDataFrames *p, GitsnTestDataFrame *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static GitsnTestDataFrame *GitsnTestDataFrames_extract(GitsnTestDataFrames *p, GitsnTestDataFrame *ptr)
{
	return (GitsnTestDataFrame *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct GitsnTestDataFramesMkArrArg
{
	GitsnTestDataFrame **arr;
	unsigned int idx;
} GitsnTestDataFramesMkArrArg;

static Dz1Error _GitsnTestDataFrames_get_array(void *ptr, GitsnTestDataFrame *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GitsnTestDataFramesMkArrArg *arg = (GitsnTestDataFramesMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static GitsnTestDataFrame **GitsnTestDataFrames_get_array(GitsnTestDataFrames *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	GitsnTestDataFrame **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (GitsnTestDataFrame **)Dz1Calloc(sizeof(GitsnTestDataFrame *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnTestDataFramesMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _GitsnTestDataFrames_get_array, (void *)&arg);
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

static Dz1Error GitsnTestDataFrames_travelForward(GitsnTestDataFrames *p, Dz1Error (*func)(void *ptr, GitsnTestDataFrame *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error GitsnTestDataFrames_travelBackward(GitsnTestDataFrames *p, Dz1Error (*func)(void *ptr, GitsnTestDataFrame *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static GitsnTestDataFrame *GitsnTestDataFrames_getHead(GitsnTestDataFrames *p)
{
	return (GitsnTestDataFrame *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int GitsnTestDataFrames_count(GitsnTestDataFrames *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

GitsnTestDataFrames *GitsnTestDataFrames_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnTestDataFrames *ret = (GitsnTestDataFrames *)Dz1Calloc(sizeof(GitsnTestDataFrames), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnTestDataFrames_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)GitsnTestDataFrame_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = GitsnTestDataFrames_count;
			ret->travel = GitsnTestDataFrames_travelForward;
			ret->travelForward = GitsnTestDataFrames_travelForward;
			ret->travelBackward = GitsnTestDataFrames_travelBackward;
			ret->get_array = GitsnTestDataFrames_get_array;
			ret->add = GitsnTestDataFrames_add;
			ret->extract = GitsnTestDataFrames_extract;
			ret->getHead = GitsnTestDataFrames_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnTestDataFrames_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _GitsnTestDataFrames_clone(void *ptr, GitsnTestDataFrame *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GitsnTestDataFrames *p = (GitsnTestDataFrames *)ptr;
	GitsnTestDataFrame *cloned = GitsnTestDataFrame_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

GitsnTestDataFrames *GitsnTestDataFrames_clone(GitsnTestDataFrames *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnTestDataFrames *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnTestDataFrames_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnTestDataFrames_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_GitsnTestDataFrames_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnTestDataFrames_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GitsnTestDataFrames_purge(GitsnTestDataFrames *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void GitsnTestDataFrames_del(GitsnTestDataFrames *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _GitsnTestDataFrames_dump(void *ptr, GitsnTestDataFrame *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); GitsnTestDataFrame_dump(p, tab);
	return err;
}

void GitsnTestDataFrames_dump(GitsnTestDataFrames *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _GitsnTestDataFrames_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnTestDataFrames
////////////////////////////////////////////////////////////////////////////////

