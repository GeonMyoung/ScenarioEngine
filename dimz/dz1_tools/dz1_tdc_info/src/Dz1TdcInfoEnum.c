#include <dz1_codec.h>

#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_str.h>

#include <dz1_fifo.h>

#include "Dz1TdcInfoEnum.h"

EnumEntry *EnumEntry_new(str_t name, str_t valStr, s32_t value, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumEntry *ret = (EnumEntry *)Dz1Calloc(sizeof(EnumEntry), 1, errp);
	if (ret == NULL) { }
	else
	{
		pthread_cleanup_push(EnumEntry_delAndSetNull, (void *)&ret);

		if (name && (ret->name = Dz1Str_dup(name, errp)) == NULL) { }
		else if (valStr && (ret->valStr = Dz1Str_dup(valStr, errp)) == NULL) { }
		else
		{
			ret->value = value;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (EnumEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

EnumEntry *EnumEntry_clone(EnumEntry *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	EnumEntry *ret = EnumEntry_new(src->name, src->valStr, src->value, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

void EnumEntry_del(EnumEntry *p)
{
	if (!p) return;
	if (p->name) Dz1Free(p->name);
	if (p->valStr) Dz1Free(p->valStr);
	Dz1Free(p);
}

static int isNumbericStr(str_t src)
{
	char *cp = src;
	while(*cp)
	{
		if (*cp < '0' || *cp > '9') return 0;
		cp++;
	}
	return 1;
}

void EnumEntry_dump(EnumEntry *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "%s", p->name);
	if (p->valStr)
	{
		if (isNumbericStr(p->valStr))
			Dz1Thread_printf(" = %s\n", p->valStr);
		else
			Dz1Thread_printf(" = %s(%d)\n", p->valStr, p->value);
	}
	else Dz1Thread_printf("\n");
}




///////////////////////////////////////////////////////////////////////////////
// EnumEntry CODEC API
static void *EnumEntry_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumEntry *ret = EnumEntry_new(NULL, NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static ssize_t EnumEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumEntry *src = (EnumEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->name, errp), errp);
		DZ1_ENCODE1(cp, size, src->valStr == NULL ? 0 : 1, errp, ret);
		if (src->valStr)
		{
			DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->valStr, errp), errp);
		}
		DZ1_ENCODE4(cp, size, (u32_t)src->value, errp, ret);
	}
	return ret;
}

static ssize_t EnumEntry_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumEntry *dst = (EnumEntry *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->name, errp), errp);
		DZ1_DECODE1(&v, cp, size, errp, ret);
		dst->valStr = NULL;
		if (v)
		{
			DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->valStr, errp), errp);
		}
		DZ1_DECODE4((u32_t *)&dst->value, cp, size, errp, ret);
	}
	return ret;
}
// EnumEntry CODEC API
///////////////////////////////////////////////////////////////////////////////

static EnumEntry *_EnumList_add(EnumList *p, str_t name, str_t valStr, s32_t *value, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumEntry *ret = NULL;
	if (valStr && value)
	{	// valStr == ?   , value == ?		-> add
		if ((ret = EnumEntry_new(name, valStr, *value, errp)) == NULL) { ERR_OUT(errp); }
	}
	else // if (valStr == NULL || value == NULL)
	{	// valStr == NULL, value == NULL	-> value automatic generate
		s32_t val = 0;
		EnumEntry *e = (EnumEntry *)Dz1Fifo_getLast(p->fifo);
		if (e)
		{	// Get Next Value
			val = e->value + 1;
		}
		if ((ret = EnumEntry_new(name, valStr, val, errp)) == NULL) { ERR_OUT(errp); }
	}
	return ret;
}

// valStr == NULL, value == NULL	-> value automatic generate
// valStr == NULL, value == ?		-> value automatic generate
// valStr == ?   , value == NULL	-> Exception
// valStr == ?   , value == ?		-> add
static Dz1Error EnumList_add(EnumList *p, str_t name, str_t valStr, s32_t *value)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	EnumEntry *e = _EnumList_add(p, name, valStr, value, &err);
	if (e == NULL) { }
	else
	{
		pthread_cleanup_push((Dz1DelFunc)EnumEntry_del, (void *)e);

		if ((err = Dz1Fifo_push(p->fifo, e)).code) { }

		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)EnumEntry_del, (void *)e);
	}
	return err;
}

static EnumEntry *EnumList_findByName(EnumList *p, str_t name)
{
	EnumEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			e = (EnumEntry *)Dz1FifoCursor_data(c);
			if (strcmp(e->name, name) == 0) return e;
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return NULL;
}

static EnumEntry *EnumList_findByVal(EnumList *p, s32_t value)
{
	EnumEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			e = (EnumEntry *)Dz1FifoCursor_data(c);
			if (e->value == value) return e;
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return NULL;
}

static Dz1Error EnumList_append(EnumList *dst, EnumEntry *node)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1Fifo_push(dst->fifo, node)).code) ERR_OUT(errp);
	return err;
}

static u32_t EnumList_count(EnumList *p)
{
	return Dz1Fifo_count(p->fifo);
}

static Dz1Error EnumList_travel(EnumList *list, Dz1Error (*func)(void *ptr, EnumEntry *p), void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1Fifo_travel(list->fifo, (Dz1FifoTravelFunc)func, ptr)).code) ERR_OUT(errp);
	return err;
}

EnumList *EnumList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumList *ret = (EnumList *)Dz1Malloc(sizeof(EnumList), errp);
	if (ret == NULL) { }
	else
	{
		memset(ret, 0, sizeof(EnumList));
		pthread_cleanup_push(EnumList_delAndSetNull, (void *)&ret);

		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)EnumEntry_del, (Dz1DumpFunc)EnumEntry_dump, 0, errp)) == NULL) { }
		else
		{
			ret->add = EnumList_add;
			ret->append = EnumList_append;
			ret->findByName = EnumList_findByName;
			ret->findByVal = EnumList_findByVal;
			ret->count = EnumList_count;
			ret->travel = EnumList_travel;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (EnumList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void EnumList_del(EnumList *p)
{
	if (!p) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	Dz1Free(p);
}

void EnumList_dump(EnumList *p, int tab)
{
	if (!p)
	{
		Dz1Thread_printf("EnumList_dump() : NULL\n");
		return;
	}
	Dz1Fifo_dump(p->fifo, tab);
}


////////////////////////////////////////////////////////////////////////////////
// EnumList CDEC
static __inline__ EnumList *EnumList_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumList *ret = EnumList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static Dz1Error _EnumList_enc(void *ptr, EnumEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = EnumEntry_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t EnumList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumList *src = (EnumList *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _EnumList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t EnumList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumList *dst = (EnumList *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		EnumEntry *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = EnumEntry_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(EnumEntry_delAndSetNull, (void *)&node);
				if ((status = EnumEntry_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->append(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (EnumEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// EnumList CODEC
////////////////////////////////////////////////////////////////////////////////


EnumInfo *EnumInfo_new(bool_t isGenerated, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumInfo *ret = (EnumInfo *)Dz1Malloc(sizeof(EnumInfo), errp);
	if (ret == NULL) { }
	else
	{
		memset(ret, 0, sizeof(EnumInfo));
		pthread_cleanup_push(EnumInfo_delAndSetNull, (void *)&ret);

		ret->isGenerated = isGenerated;
		if ((ret->enums = EnumList_new(errp)) == NULL) { }
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (EnumInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _enum_clone(void *ptr, EnumEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	EnumList *dst = (EnumList *)ptr;
	EnumEntry *node = EnumEntry_clone(p, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(EnumEntry_delAndSetNull, (void *)&node);
		if ((*errp = dst->append(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (EnumEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

EnumInfo *EnumInfo_clone(EnumInfo *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	EnumInfo *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = EnumInfo_new(src->isGenerated, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(EnumInfo_delAndSetNull, (void *)&ret);
		if ((*errp = src->enums->travel(src->enums, _enum_clone, (void *)ret->enums)).code) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (EnumInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}


void EnumInfo_del(EnumInfo *p)
{
	if (!p) return;
	if (p->enums) EnumList_del(p->enums);
	Dz1Free(p);
}

void EnumInfo_dump(EnumInfo *p, int tab)
{
	if (!p)
	{
		Dz1Thread_printf("EnumInfo_dump() : NULL\n");
		return;
	}
	EnumList_dump(p->enums, tab);
}

///////////////////////////////////////////////////////////////////////////////
// EnumInfo CODEC API
void *EnumInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumInfo *ret = EnumInfo_new(FALSE, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t EnumInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumInfo *src = (EnumInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, (u8_t)(src->isGenerated & 0xFF), errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, EnumList_enc(cp, size, src->enums, param, errp), errp);
	}
	return ret;
}

ssize_t EnumInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	EnumInfo *dst = (EnumInfo *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v8;
		DZ1_DECODE1(&v8, cp, size, errp, ret); dst->isGenerated = (bool_t)v8;
		DZ1_CODEC_FUNC(cp, size, ret, EnumList_dec(dst->enums, cp, size, param, errp), errp);
	}
	return ret;
}
// EnumInfo CODEC API
///////////////////////////////////////////////////////////////////////////////

