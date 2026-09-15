#include <dz1_codec.h>
#include <dz1_str.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>

#include <Dz1TdcInfoModule.h>

#include "Dz1TdcInfoFunc.h"
#include "Dz1TdcInfoObject.h"

// instance taken pointer not clone
FunctionArg *FunctionArg_new(struct ObjectInfo *argType, s32_t argForward, s32_t argPtrCnt, str_t instance, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionArg *ret = (FunctionArg *)Dz1Calloc(sizeof(FunctionArg), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->argType = argType;
		ret->argForward = argForward;
		ret->argPtrCnt = argPtrCnt;
		ret->instance = instance;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void FunctionArg_del(FunctionArg *p)
{
	if (!p) return;
	if (p->instance) Dz1Str_del(p->instance);
	Dz1Free(p);
}

void FunctionArg_dump(FunctionArg *p, int tab)
{
	if (!p) return;
	if (p->argType) ObjectInfo_dump(p->argType, tab);
	else Dz1Thread_tprintf(tab, "type = NULL\n");
	Dz1Thread_tprintf(tab, "Forward Type = %d\n", p->argForward);
	Dz1Thread_tprintf(tab, "Ptr Count = %d\n", p->argPtrCnt);
	if (p->instance) Dz1Thread_tprintf(tab, "Instance = %s\n", p->instance);
	else Dz1Thread_tprintf(tab, "Instance = NULL\n");
}


////////////////////////////////////////////////////////////////////////////////
// FunctionArg CODEC
static FunctionArg *FunctionArg_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionArg *ret = FunctionArg_new(NULL, 0, 0, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static ssize_t FunctionArg_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionArg *src = (FunctionArg *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->argType->name, errp), errp);
		DZ1_ENCODE4(cp, size, src->argForward, errp, ret);
		DZ1_ENCODE4(cp, size, src->argPtrCnt, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->instance, errp), errp);
	}
	return ret;
}

static ssize_t FunctionArg_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionArg *dst = (FunctionArg *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		str_t objName = NULL;
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &objName, errp), errp);
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
		if ((dst->argType = module->findObject(module, objName)) == NULL)
		{
			if ((dst->argType = module->regUnknownObject(module, objName, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);
		if (errp->code != 0) DZ1_CODEC_ERR_RET(errp);

		DZ1_DECODE4((u32_t *)&dst->argForward, cp, size, errp, ret);
		DZ1_DECODE4((u32_t *)&dst->argPtrCnt, cp, size, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->instance, errp), errp);
	}
	return ret;
}
// FunctionArg CODEC
////////////////////////////////////////////////////////////////////////////////





static Dz1Error FunctionArgs_insert(FunctionArgs *list, FunctionArg *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1Fifo_push(list->list, (void *)e)).code) ERR_OUT(&err);
	return err;
}

static Dz1Error FunctionArgs_add(FunctionArgs *list, struct ObjectInfo *argType, s32_t argForward, s32_t argPtrCnt, str_t instance)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	FunctionArg *e = FunctionArg_new(argType, argForward, argPtrCnt, instance, &err);
	if (e == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(FunctionArg_delAndSetNull, (void *)&e);

		if ((err = Dz1Fifo_push(list->list, (void *)e)).code) ERR_OUT(&err);
		else e = NULL;

		pthread_cleanup_pop(1); // (FunctionArg_delAndSetNull, (void *)&e);
	}
	return err;
}

static u32_t FunctionArgs_count(FunctionArgs *list)
{
	u32_t ret = Dz1Fifo_count(list->list);
//	Dz1Thread_printf("FunctionArgs_count() : ret = %u\n", ret);
	return ret;
}

static Dz1Error FunctionArgs_travel(FunctionArgs *p, Dz1Error (*func)(void *ptr, FunctionArg *p), void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1Fifo_travel(p->list, (Dz1FifoTravelFunc)func, ptr)).code) ERR_OUT(errp);
	return err;
}

FunctionArgs *FunctionArgs_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionArgs *ret = (FunctionArgs *)Dz1Calloc(sizeof(FunctionArgs), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(FunctionArgs_delAndSetNull, (void *)&ret);

		if ((ret->list = Dz1Fifo_new((Dz1DelFunc)FunctionArg_del, (Dz1DumpFunc)FunctionArg_dump, 0, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = FunctionArgs_add;
			ret->insert = FunctionArgs_insert;
			ret->count = FunctionArgs_count;
			ret->travel = FunctionArgs_travel;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (FunctionArgs_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void FunctionArgs_del(FunctionArgs *p)
{
	if (!p) return;
	if (p->list) Dz1Fifo_del(p->list);
	Dz1Free(p);
}

void FunctionArgs_dump(FunctionArgs *p, int tab)
{
	if (!p) return;
	if (p->list) Dz1Fifo_dump(p->list, tab);
}



////////////////////////////////////////////////////////////////////////////////
// FunctionArgs CODEC
static __inline__ FunctionArgs *FunctionArgs_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionArgs *ret = FunctionArgs_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static Dz1Error _FunctionArgs_enc(void *ptr, FunctionArg *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = FunctionArg_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t FunctionArgs_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionArgs *src = (FunctionArgs *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _FunctionArgs_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t FunctionArgs_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionArgs *dst = (FunctionArgs *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		FunctionArg *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = FunctionArg_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(FunctionArg_delAndSetNull, (void *)&node);
				if ((status = FunctionArg_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->insert(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (FunctionArg_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// FunctionArgs CODEC
////////////////////////////////////////////////////////////////////////////////






FunctionInfo *FunctionInfo_new(struct ObjectInfo *retType, bool_t retIsPointer, s32_t retForward, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionInfo *ret = (FunctionInfo *)Dz1Calloc(sizeof(FunctionInfo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(FunctionInfo_delAndSetNull, (void *)&ret);
		if ((ret->args = FunctionArgs_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->retType = retType;
			ret->retIsPointer = retIsPointer;
			ret->retForward = retForward;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (FunctionInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void FunctionInfo_del(FunctionInfo *p)
{
	if (!p) return;
	if (p->args) FunctionArgs_del(p->args);
	Dz1Free(p);
}

void FunctionInfo_dump(FunctionInfo *p, int tab)
{
	if (!p) return;
	if (p->retType) ObjectInfo_dump(p->retType, tab);
	Dz1Thread_printf("Return is Pointer = %s\n", p->retIsPointer ? "Yes" : "No");
	Dz1Thread_printf("Forward Type = %d\n", p->retForward);
	if (p->args) FunctionArgs_dump(p->args, tab + 1);
}

////////////////////////////////////////////////////////////////////////////////
// FunctionInfo CODEC
FunctionInfo *FunctionInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionInfo *ret = FunctionInfo_new(NULL, FALSE, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t FunctionInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionInfo *src = (FunctionInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->retType->name, errp), errp);
		DZ1_ENCODE1(cp, size, (u8_t)(src->retIsPointer ? 1 : 0), errp, ret);
		DZ1_ENCODE4(cp, size, src->retForward, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, FunctionArgs_enc(cp, size, src->args, param, errp), errp);
	}
	return ret;
}

ssize_t FunctionInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FunctionInfo *dst = (FunctionInfo *)_dst;
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		str_t objName = NULL;
		u8_t *cp = src, v;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &objName, errp), errp);
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
		if ((dst->retType = module->findObject(module, objName)) == NULL)
		{
			if ((dst->retType = module->regUnknownObject(module, objName, errp)) == NULL) ERR_OUT(errp);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);
		if (errp->code != 0) DZ1_CODEC_ERR_RET(errp);

		DZ1_DECODE1(&v, cp, size, errp, ret); dst->retIsPointer = v ? TRUE : FALSE;
		DZ1_DECODE4((u32_t *)&dst->retForward, cp, size, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, FunctionArgs_dec(dst->args, cp, size, param, errp), errp);
	}
	return ret;
}
// FunctionInfo CODEC
////////////////////////////////////////////////////////////////////////////////

