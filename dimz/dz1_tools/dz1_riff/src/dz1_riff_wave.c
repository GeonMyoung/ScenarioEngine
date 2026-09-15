////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_riff_wave.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveUnknown
Dz1RiffWaveUnknown *Dz1RiffWaveUnknown_new(str_t id, Dz1Binary *chunk, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1RiffWaveUnknown *__internal_ret = (Dz1RiffWaveUnknown *)Dz1Calloc(sizeof(Dz1RiffWaveUnknown), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1RiffWaveUnknown_delAndSetNull, (void *)&__internal_ret);
		
		if (id && (__internal_ret->id = dz1_built_in_str_clone(id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->chunk = chunk;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWaveUnknown_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1RiffWaveUnknown_copy(Dz1RiffWaveUnknown *dst, Dz1RiffWaveUnknown *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->id && (dst->id = dz1_built_in_str_clone(src->id, errp)) == NULL) ERR_OUT(errp);
	else if (src->chunk && (dst->chunk = Dz1Binary_clone(src->chunk, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1RiffWaveUnknown *Dz1RiffWaveUnknown_clone(Dz1RiffWaveUnknown *src, Dz1Error *err)
{
	Dz1RiffWaveUnknown *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1RiffWaveUnknown *)Dz1Calloc(sizeof(Dz1RiffWaveUnknown), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1RiffWaveUnknown_delAndSetNull, (void *)&dst);
		if (Dz1RiffWaveUnknown_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWaveUnknown_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1RiffWaveUnknown_purge(Dz1RiffWaveUnknown *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->id);
	Dz1Binary_del(p->chunk);
}

void Dz1RiffWaveUnknown_del(Dz1RiffWaveUnknown *p)
{
	if (p == NULL) return;
	Dz1RiffWaveUnknown_purge(p);
	Dz1Free(p);
}

void Dz1RiffWaveUnknown_dump(Dz1RiffWaveUnknown *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("id = ")); dz1_built_in_str_dump(p->id, tab); 
	}
}
// Dz1RiffWaveUnknown
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveFmt
Dz1RiffWaveFmt *Dz1RiffWaveFmt_new(u16_t audioFormat, 
								   u16_t numOfChannel, 
								   u32_t sampleRate, 
								   u32_t byteRate, 
								   u16_t blockAlign, 
								   u16_t bitPerSample, 
								   Dz1Binary *extra, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1RiffWaveFmt *__internal_ret = (Dz1RiffWaveFmt *)Dz1Calloc(sizeof(Dz1RiffWaveFmt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1RiffWaveFmt_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->audioFormat = audioFormat;
		__internal_ret->numOfChannel = numOfChannel;
		__internal_ret->sampleRate = sampleRate;
		__internal_ret->byteRate = byteRate;
		__internal_ret->blockAlign = blockAlign;
		__internal_ret->bitPerSample = bitPerSample;
		__internal_ret->extra = extra;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWaveFmt_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1RiffWaveFmt_copy(Dz1RiffWaveFmt *dst, Dz1RiffWaveFmt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->extra && (dst->extra = Dz1Binary_clone(src->extra, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->audioFormat = src->audioFormat;
		dst->numOfChannel = src->numOfChannel;
		dst->sampleRate = src->sampleRate;
		dst->byteRate = src->byteRate;
		dst->blockAlign = src->blockAlign;
		dst->bitPerSample = src->bitPerSample;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1RiffWaveFmt *Dz1RiffWaveFmt_clone(Dz1RiffWaveFmt *src, Dz1Error *err)
{
	Dz1RiffWaveFmt *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1RiffWaveFmt *)Dz1Calloc(sizeof(Dz1RiffWaveFmt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1RiffWaveFmt_delAndSetNull, (void *)&dst);
		if (Dz1RiffWaveFmt_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWaveFmt_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1RiffWaveFmt_purge(Dz1RiffWaveFmt *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->extra);
}

void Dz1RiffWaveFmt_del(Dz1RiffWaveFmt *p)
{
	if (p == NULL) return;
	Dz1RiffWaveFmt_purge(p);
	Dz1Free(p);
}

void Dz1RiffWaveFmt_dump(Dz1RiffWaveFmt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("audioFormat = ")); Dz1u16_dump(&p->audioFormat, tab); 
		Dz1Thread_tprintf(tab, Dz1T("numOfChannel = ")); Dz1u16_dump(&p->numOfChannel, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sampleRate = ")); Dz1u32_dump(&p->sampleRate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("byteRate = ")); Dz1u32_dump(&p->byteRate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("blockAlign = ")); Dz1u16_dump(&p->blockAlign, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bitPerSample = ")); Dz1u16_dump(&p->bitPerSample, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("extra = ")); Dz1Binary_dump(p->extra, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1RiffWaveFmt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveData
Dz1RiffWaveData *Dz1RiffWaveData_new(Dz1Binary *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1RiffWaveData *__internal_ret = (Dz1RiffWaveData *)Dz1Calloc(sizeof(Dz1RiffWaveData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1RiffWaveData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWaveData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1RiffWaveData_copy(Dz1RiffWaveData *dst, Dz1RiffWaveData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->data && (dst->data = Dz1Binary_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1RiffWaveData *Dz1RiffWaveData_clone(Dz1RiffWaveData *src, Dz1Error *err)
{
	Dz1RiffWaveData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1RiffWaveData *)Dz1Calloc(sizeof(Dz1RiffWaveData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1RiffWaveData_delAndSetNull, (void *)&dst);
		if (Dz1RiffWaveData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWaveData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1RiffWaveData_purge(Dz1RiffWaveData *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->data);
}

void Dz1RiffWaveData_del(Dz1RiffWaveData *p)
{
	if (p == NULL) return;
	Dz1RiffWaveData_purge(p);
	Dz1Free(p);
}

void Dz1RiffWaveData_dump(Dz1RiffWaveData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		// Dz1RiffWaveData has no dump element(s)
		Dz1Thread_printf(Dz1T("{ }\n"));	}
}
// Dz1RiffWaveData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveChunkPresent
static struct Dz1RiffWaveChunkPresentMapA
{
	str_t str;
	Dz1RiffWaveChunkPresent v;
} Dz1RiffWaveChunkPresentMapA[] =
{
	{ (char *)"fmt", Dz1RiffWaveChunkPresent_fmt },
	{ (char *)"data", Dz1RiffWaveChunkPresent_data },
	{ (char *)"unknown", Dz1RiffWaveChunkPresent_unknown },
	{ NULL, Dz1RiffWaveChunkPresent_max }
};

str_t Dz1RiffWaveChunkPresentStrA(Dz1RiffWaveChunkPresent v)
{
	struct Dz1RiffWaveChunkPresentMapA *i = NULL;
	for (i = Dz1RiffWaveChunkPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1RiffWaveChunkPresent Dz1RiffWaveChunkPresentFromStrA(str_t str)
{
	struct Dz1RiffWaveChunkPresentMapA *i = NULL;
	for (i = Dz1RiffWaveChunkPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1RiffWaveChunkPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1RiffWaveChunkPresentMapW
{
	wstr_t str;
	Dz1RiffWaveChunkPresent v;
} Dz1RiffWaveChunkPresentMapW[] =
{
	{ (wchar_t *)L"fmt", Dz1RiffWaveChunkPresent_fmt },
	{ (wchar_t *)L"data", Dz1RiffWaveChunkPresent_data },
	{ (wchar_t *)L"unknown", Dz1RiffWaveChunkPresent_unknown },
	{ NULL, Dz1RiffWaveChunkPresent_max }
};

wstr_t Dz1RiffWaveChunkPresentStrW(Dz1RiffWaveChunkPresent v)
{
	struct Dz1RiffWaveChunkPresentMapW *i = NULL;
	for (i = Dz1RiffWaveChunkPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1RiffWaveChunkPresent Dz1RiffWaveChunkPresentFromStrW(wstr_t str)
{
	struct Dz1RiffWaveChunkPresentMapW *i = NULL;
	for (i = Dz1RiffWaveChunkPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1RiffWaveChunkPresent_max;
}
#endif // UNIX_SYSTEM

Dz1RiffWaveChunkPresent *Dz1RiffWaveChunkPresent_new(Dz1RiffWaveChunkPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1RiffWaveChunkPresent *__internal_ret = (Dz1RiffWaveChunkPresent *)Dz1Calloc(sizeof(Dz1RiffWaveChunkPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1RiffWaveChunkPresent_dump(Dz1RiffWaveChunkPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1RiffWaveChunkPresentStr(*v));
}
// Dz1RiffWaveChunkPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveChunk
Dz1RiffWaveChunk *Dz1RiffWaveChunk_new(Dz1RiffWaveChunkPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1RiffWaveChunk *ret = (Dz1RiffWaveChunk *)Dz1Calloc(sizeof(Dz1RiffWaveChunk), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1RiffWaveChunk_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1RiffWaveChunkPresent_fmt:
			// _U_cst_clone
			if (ptr != NULL) ret->x.fmt = (Dz1RiffWaveFmt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1RiffWaveChunkPresent_data:
			// _U_cst_clone
			if (ptr != NULL) ret->x.data = (Dz1RiffWaveData *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1RiffWaveChunkPresent_unknown:
			// _U_cst_clone
			if (ptr != NULL) ret->x.unknown = (Dz1RiffWaveUnknown *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1RiffWaveChunkPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWaveChunk_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1RiffWaveChunk_copy(Dz1RiffWaveChunk *ret, Dz1RiffWaveChunk *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1RiffWaveChunkPresent_fmt:
			// _U_cst_clone
			if (src->x.fmt && (ret->x.fmt = Dz1RiffWaveFmt_clone(src->x.fmt, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1RiffWaveChunkPresent_data:
			// _U_cst_clone
			if (src->x.data && (ret->x.data = Dz1RiffWaveData_clone(src->x.data, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1RiffWaveChunkPresent_unknown:
			// _U_cst_clone
			if (src->x.unknown && (ret->x.unknown = Dz1RiffWaveUnknown_clone(src->x.unknown, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1RiffWaveChunk *Dz1RiffWaveChunk_clone(Dz1RiffWaveChunk *src, Dz1Error *err)
{
	Dz1RiffWaveChunk *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1RiffWaveChunk *)Dz1Calloc(sizeof(Dz1RiffWaveChunk), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1RiffWaveChunk_delAndSetNull, (void *)&ret);
		if (Dz1RiffWaveChunk_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWaveChunk_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1RiffWaveChunk_purge(Dz1RiffWaveChunk *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1RiffWaveChunkPresent_fmt:
		Dz1RiffWaveFmt_del(p->x.fmt);
		break;
	case Dz1RiffWaveChunkPresent_data:
		Dz1RiffWaveData_del(p->x.data);
		break;
	case Dz1RiffWaveChunkPresent_unknown:
		Dz1RiffWaveUnknown_del(p->x.unknown);
		break;
	default:
		break;
	}
}

void Dz1RiffWaveChunk_del(Dz1RiffWaveChunk *p)
{
	if (!p) return;
	Dz1RiffWaveChunk_purge(p);
	Dz1Free(p);
}

void Dz1RiffWaveChunk_dump(Dz1RiffWaveChunk *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1RiffWaveChunkPresent_fmt:
		Dz1Thread_printf(Dz1T("fmt = ")); Dz1RiffWaveFmt_dump(p->x.fmt, tab); 
		break;
	case Dz1RiffWaveChunkPresent_data:
		Dz1Thread_printf(Dz1T("data = ")); Dz1RiffWaveData_dump(p->x.data, tab); 
		break;
	case Dz1RiffWaveChunkPresent_unknown:
		Dz1Thread_printf(Dz1T("unknown = ")); Dz1RiffWaveUnknown_dump(p->x.unknown, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1RiffWaveChunk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWave
static Dz1Error Dz1RiffWave_add(Dz1RiffWave *p, Dz1RiffWaveChunk *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1RiffWaveMkArrArg
{
	Dz1RiffWaveChunk **arr;
	unsigned int idx;
} Dz1RiffWaveMkArrArg;

static Dz1Error _Dz1RiffWave_get_array(void *ptr, Dz1RiffWaveChunk *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1RiffWaveMkArrArg *arg = (Dz1RiffWaveMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1RiffWaveChunk **Dz1RiffWave_get_array(Dz1RiffWave *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1RiffWaveChunk **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1RiffWaveChunk **)Dz1Calloc(sizeof(Dz1RiffWaveChunk *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1RiffWaveMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1RiffWave_get_array, (void *)&arg);
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

static Dz1Error Dz1RiffWave_travelForward(Dz1RiffWave *p, Dz1Error (*func)(void *ptr, Dz1RiffWaveChunk *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1RiffWave_travelBackward(Dz1RiffWave *p, Dz1Error (*func)(void *ptr, Dz1RiffWaveChunk *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1RiffWave_count(Dz1RiffWave *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1RiffWave *Dz1RiffWave_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1RiffWave *ret = (Dz1RiffWave *)Dz1Calloc(sizeof(Dz1RiffWave), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1RiffWave_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1RiffWaveChunk_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1RiffWave_count;
			ret->travel = Dz1RiffWave_travelForward;
			ret->travelForward = Dz1RiffWave_travelForward;
			ret->travelBackward = Dz1RiffWave_travelBackward;
			ret->get_array = Dz1RiffWave_get_array;
			ret->add = Dz1RiffWave_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWave_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1RiffWave_clone(void *ptr, Dz1RiffWaveChunk *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1RiffWave *p = (Dz1RiffWave *)ptr;
	Dz1RiffWaveChunk *cloned = Dz1RiffWaveChunk_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1RiffWave *Dz1RiffWave_clone(Dz1RiffWave *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1RiffWave *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1RiffWave_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1RiffWave_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1RiffWave_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffWave_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1RiffWave_purge(Dz1RiffWave *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1RiffWave_del(Dz1RiffWave *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1RiffWave_dump(void *ptr, Dz1RiffWaveChunk *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1RiffWaveChunk_dump(p, tab);
	return err;
}

void Dz1RiffWave_dump(Dz1RiffWave *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1RiffWave_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1RiffWave
////////////////////////////////////////////////////////////////////////////////

