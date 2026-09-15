#include <dz1_codec.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_str.h>
#include <dz1_fifo.h>

#include "Dz1TdcInfoBits.h"

///////////////////////////////////////////////////////////////////////////////
// Bits Entry
BitsEntry *BitsEntry_new(str_t name, u32_t bit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	BitsEntry *ret = (BitsEntry *)Dz1Calloc(sizeof(BitsEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(BitsEntry_delAndSetNull, (void *)&ret);

		if (name && (ret->name = Dz1Str_dup(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->bit = bit;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (BitsEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void BitsEntry_del(BitsEntry *p)
{
	if (!p) return;
	if (p->name) Dz1Free(p->name);
	Dz1Free(p);
}

void BitsEntry_dump(BitsEntry *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "%s(%u)\n", p->name, p->bit);
}
// Bits Entry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// BitsEntry CODEC API
static void *BitsEntry_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	BitsEntry *ret = BitsEntry_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static ssize_t BitsEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	BitsEntry *src = (BitsEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->name, errp), errp);
		DZ1_ENCODE4(cp, size, src->bit, errp, ret);
	}
	return ret;
}

static ssize_t BitsEntry_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	BitsEntry *dst = (BitsEntry *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->name, errp), errp);
		DZ1_DECODE4(&dst->bit, cp, size, errp, ret);
	}
	return ret;
}
// BitsEntry CODEC API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Bits List
static Dz1Error BitsList_append(BitsList *dst, BitsEntry *node)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if ((*errp = Dz1Fifo_push(dst->fifo, node)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1Error BitsList_add(BitsList *p, str_t name, u32_t bit)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	BitsEntry *e = BitsEntry_new(name, bit, &err);
	if (e == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)BitsEntry_del, (void *)e);

		if ((*errp = BitsList_append(p, e)).code) ERR_OUT(errp);
		else
		{
			e = NULL;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)BitsEntry_del, (void *)e);
	}
	return err;
}

static u32_t BitsList_count(BitsList *p)
{
	return Dz1Fifo_count(p->fifo);
}

static Dz1Error BitsList_travel(BitsList *p, Dz1Error (*func)(void *ptr, BitsEntry *p), void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = NULL;
	if ((*errp = Dz1Fifo_travelForward(p->fifo, (Dz1FifoTravelFunc)func, ptr)).code) ERR_OUT(errp);
	return err;
}

BitsList *BitsList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	BitsList *ret = (BitsList *)Dz1Calloc(sizeof(BitsList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(BitsList_delAndSetNull, (void *)&ret);

		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)BitsEntry_del, (Dz1DumpFunc)BitsEntry_dump, 0, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = BitsList_add;
			ret->append = BitsList_append;
			ret->count = BitsList_count;
			ret->travel = BitsList_travel;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (BitsList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void BitsList_del(BitsList *p)
{
	if (!p) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	Dz1Free(p);
}

void BitsList_dump(BitsList *p, int tab)
{
	if (!p) return;
	Dz1Fifo_dump(p->fifo, tab);
}
// Bits List
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Bits Info
BitsInfo *BitsInfo_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	BitsInfo *ret = (BitsInfo *)Dz1Calloc(sizeof(BitsInfo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(BitsInfo_delAndSetNull, (void *)&ret);

		if ((ret->bits = BitsList_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (BitsInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void BitsInfo_del(BitsInfo *p)
{
	if (!p) return;
	if (p->bits) BitsList_del(p->bits);
	Dz1Free(p);
}

void BitsInfo_dump(BitsInfo *p, int tab)
{
	if (!p) return;
	BitsList_dump(p->bits, tab);
}
// Bits Info
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// BitsInfo CODEC API
void *BitsInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	BitsInfo *ret = BitsInfo_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static Dz1Error _BitsInfo_enc(void *ptr, BitsEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = BitsEntry_enc(arg->cp, arg->size, p, NULL, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

ssize_t BitsInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	BitsInfo *src = (BitsInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		BitsList *info = src->bits;
		u32_t cnt = info->count(info);
		Dz1ListCodecArg arg;

		DZ1_ENCODE4(cp, size, cnt, errp, ret);

		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = info->travel(info, _BitsInfo_enc, &arg)).code) ERR_OUT(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

ssize_t BitsInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	BitsInfo *dst = (BitsInfo *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		BitsList *list = dst->bits;
		BitsEntry *node = NULL;
		u8_t *cp = src;
		u32_t cnt = 0, i;
		DZ1_DECODE4(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = BitsEntry_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(BitsEntry_delAndSetNull, (void *)&node);
				if ((status = BitsEntry_dec(node, cp, size, NULL, errp)) < 0) ERR_OUT(errp);
				else if ((*errp = list->append(list, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (BitsEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// BitsInfo CODEC API
///////////////////////////////////////////////////////////////////////////////
