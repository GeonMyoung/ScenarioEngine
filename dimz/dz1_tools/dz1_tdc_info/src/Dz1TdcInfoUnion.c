#include <dz1_codec.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_str.h>

#include <Dz1TdcInfoModule.h>

#include "Dz1TdcInfoObject.h"
#include "Dz1TdcInfoUnion.h"

UnionMemberEntry *UnionMemberEntry_new(int isForwarded, struct ObjectInfo *type, str_t presentStr,
									   str_t srcType, int isPointer, str_t instance,
									   u32_t memb_flags, MemberDumpMode dumpMode, str_t end_of_arr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionMemberEntry *ret = (UnionMemberEntry *)Dz1Calloc(sizeof(UnionMemberEntry), 1, errp);
	if (ret == NULL) { }
	else
	{
		pthread_cleanup_push(UnionMemberList_delAndSetNull, (void *)&ret);
		if (instance && (ret->instance = Dz1Str_dup(instance,  errp)) == NULL) { }
		else if (srcType && (ret->srcType = Dz1Str_dup(srcType,  errp)) == NULL) { }
		else if (presentStr && (ret->presentStr = Dz1Str_dup(presentStr,  errp)) == NULL) { }
		else if (end_of_arr && (ret->end_of_arr = Dz1Str_dup(end_of_arr,  errp)) == NULL) { }
		else
		{
			ret->isForwarded = isForwarded;
			ret->type = type;
			ret->isPointer = isPointer;
			ret->memb_flags = memb_flags;
			ret->dumpMode = dumpMode;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (UnionMemberList_delAndSetNull, (void *)&ret);
	}
	return ret;

}

UnionMemberEntry *UnionMemberEntry_clone(UnionMemberEntry *src, Dz1Error *err)
{
	UnionMemberEntry *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((ret = UnionMemberEntry_new(src->isForwarded, src->type, src->presentStr, 
									src->srcType, src->isPointer, src->instance, 
									src->memb_flags, src->dumpMode, src->end_of_arr, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

static void _UnionMemberEntry_purge(UnionMemberEntry *p)
{
	p->isForwarded = FALSE;
	p->isPointer = FALSE;
	Dz1StrA_delAndSetNull(&p->instance);
	Dz1StrA_delAndSetNull(&p->srcType);
	Dz1StrA_delAndSetNull(&p->presentStr);
	p->instance = NULL;
	p->memb_flags = 0;
	p->dumpMode = MemberDumpMode_normal;
	Dz1StrA_delAndSetNull(&p->end_of_arr);
}

void UnionMemberEntry_purge(UnionMemberEntry *p)
{
	if (!p) return;
	_UnionMemberEntry_purge(p);
}

void UnionMemberEntry_del(UnionMemberEntry *p)
{
	if (!p) return;
	_UnionMemberEntry_purge(p);
	Dz1Free(p);
}

void UnionMemberEntry_dump(UnionMemberEntry *p, int tab)
{
	char array_str[256] = "";
	if (!p) return;

	if (UnionMemberEntry_isArray(p))
		_std_snprintfA(array_str, sizeof(array_str), "[%s%s]", p->end_of_arr, UnionMemberEntry_isArrayElemRef(p) ? ", ref" : "");

	Dz1Thread_tprintf(tab,	"%s %s%s%s\n", p->type ? p->type->name : "(none)", 
							p->isPointer ? "*" : "", 
							p->instance, array_str);
}

////////////////////////////////////////////////////////////////////////////////
// UnionMemberEntry CODEC
static UnionMemberEntry *UnionMemberEntry_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionMemberEntry *ret = UnionMemberEntry_new(0, NULL, NULL, NULL, 0, NULL, 0, 0, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static ssize_t UnionMemberEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionMemberEntry *src = (UnionMemberEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u32_t v32 = 0;
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, 0xCAFE0000, errp, ret);															// structure version [+]

		v32 = (u32_t)src->isForwarded;
		DZ1_ENCODE4(cp, size, v32, errp, ret);																	// isForwarded
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->type->name, errp), errp);						// type->name

		DZ1_ENCODE1(cp, size, src->presentStr ? 1 : 0, errp, ret);												// presentStr Flag
		if (src->presentStr) DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->presentStr, errp), errp);	// presentStr

		DZ1_ENCODE1(cp, size, src->srcType ? 1 : 0, errp, ret);													// srcType Flag
		if (src->srcType) DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->srcType, errp), errp);			// srcType

		DZ1_ENCODE1(cp, size, src->end_of_arr ? 1 : 0, errp, ret);												// end_of_arr Flag	[+]
		if (src->end_of_arr) DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->end_of_arr, errp), errp);	// end_of_arr		[+]

		DZ1_ENCODE4(cp, size, src->isPointer, errp, ret);														// isPointer
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->instance, errp), errp);							// instance
		DZ1_ENCODE4(cp, size, src->memb_flags, errp, ret);														// member flags		[*]
//		DZ1_ENCODE4(cp, size, src->isReferenced, errp, ret);													// isReferenced		[*]
		DZ1_ENCODE1(cp, size, (u8_t)(src->dumpMode & 0xFF), errp, ret);											// dumpMode
	}
	return ret;
}

static ssize_t UnionMemberEntry_decVer0(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{	// previously decoded "Structure Version"
	ssize_t ret = 0;
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionMemberEntry *dst = (UnionMemberEntry *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		str_t objName = NULL;
		u8_t *cp = src, v8;
		u32_t v32 = 0;
		DZ1_DECODE4(&v32, cp, size, errp, ret); dst->isForwarded = (FORWARD_TYPE)v32;						// isForwarded
		
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &objName, errp), errp);							// type->name
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
		if ((dst->type = module->findObject(module, objName)) == NULL)
		{
			if ((dst->type = module->regUnknownObject(module, objName, errp)) == NULL) ERR_OUT(errp);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);
		if (errp->code != 0) DZ1_CODEC_ERR_RET(errp);

		DZ1_DECODE1(&v8, cp, size, errp, ret);																// presentStr flag
		if (v8) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->presentStr, errp), errp);			// presentStr

		DZ1_DECODE1(&v8, cp, size, errp, ret);																// srcType flag
		if (v8) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->srcType, errp), errp);				// srcType

		DZ1_DECODE1(&v8, cp, size, errp, ret);																// end_of_arr flag	[+]
		if (v8) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->end_of_arr, errp), errp);			// end_of_arr		[+]

		DZ1_DECODE4((u32_t *)&dst->isPointer, cp, size, errp, ret);											// isPointer
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->instance, errp), errp);						// instance
		DZ1_DECODE4(&dst->memb_flags, cp, size, errp, ret);													// memb_flags		[*]
//		DZ1_DECODE4((u32_t *)&dst->isReferenced, cp, size, errp, ret);										// isReferenced		[*]
		DZ1_DECODE1(&v8, cp, size, errp, ret); dst->dumpMode = (MemberDumpMode)v8;							// dumpMode
	}
	return ret;
}

static ssize_t UnionMemberEntry_decOld(UnionMemberEntry *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{	// previously decoded "isForwarded"
	ssize_t ret = 0;
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u32_t v32 = 0;
	str_t objName = NULL;
	u8_t *cp = src, v;

	DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &objName, errp), errp);								// type->name
	pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
	if ((dst->type = module->findObject(module, objName)) == NULL)
	{
		if ((dst->type = module->regUnknownObject(module, objName, errp)) == NULL) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);
	if (errp->code != 0) DZ1_CODEC_ERR_RET(errp);

	DZ1_DECODE1(&v, cp, size, errp, ret);																	// presentStr flag
	if (v) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->presentStr, errp), errp);				// presentStr

	DZ1_DECODE1(&v, cp, size, errp, ret);																	// srcType flag
	if (v) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->srcType, errp), errp);					// srcType

	DZ1_DECODE4((u32_t *)&dst->isPointer, cp, size, errp, ret);												// isPointer
	DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->instance, errp), errp);							// instance

	DZ1_DECODE4(&v32, cp, size, errp, ret);																	// isReferenced
	if (v32) dst->memb_flags |= MEMBER_FLAG_IS_REFERENCED;

	DZ1_DECODE1(&v, cp, size, errp, ret); dst->dumpMode = (MemberDumpMode)v;								// dumpMode

	return ret;
}

typedef ssize_t (*UnionMemberEntryDecF)(UnionMemberEntry *dst, u8_t *src, size_t size, void *param, Dz1Error *err);
static UnionMemberEntryDecF unionMemberEntryDecF[] =
{
	UnionMemberEntry_decVer0,
	NULL
};
static size_t unionMemberEntryDecFCnt = sizeof(unionMemberEntryDecF) / sizeof(UnionMemberEntryDecF) - 1;

static ssize_t UnionMemberEntry_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{	// previously decoded "Structure Version"
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionMemberEntry *dst = (UnionMemberEntry *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u32_t v32 = 0;
		u8_t *cp = src;
		DZ1_DECODE4(&v32, cp, size, errp, ret);											// isForwarded ? structure version
		if (v32 & 0xFFFF0000)
		{
			u16_t ver = (u16_t)(v32 & 0xFFFF);
			if (ver >= unionMemberEntryDecFCnt) DZ1_CODEC_ERRSET_RET(errp, ENOSYS);
			else DZ1_CODEC_FUNC(cp, size, ret, unionMemberEntryDecF[ver](dst, cp, size, param, errp), errp);
		}
		else
		{
			dst->isForwarded = (FORWARD_TYPE)v32;
			DZ1_CODEC_FUNC(cp, size, ret, UnionMemberEntry_decOld(dst, cp, size, param, errp), errp);
		}
	}
	return ret;
}
// UnionMemberEntry CODEC
////////////////////////////////////////////////////////////////////////////////






static Dz1Error UnionMemberList_insert(UnionMemberList *p, UnionMemberEntry *e)
{
	return Dz1Fifo_push(p->fifo, e);
}

static Dz1Error UnionMemberList_add(UnionMemberList *p,
									int isForwarded, ObjectInfo *type, str_t presentStr,
									str_t srcType, int isPointer, str_t instance,
									u32_t memb_flags, MemberDumpMode dumpMode, str_t end_of_arr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	UnionMemberEntry *e = UnionMemberEntry_new(isForwarded, type, presentStr, srcType, isPointer, instance, memb_flags, dumpMode, end_of_arr, &err);
	if (e == NULL) { }
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)UnionMemberEntry_del, (void *)e);

		if ((err = Dz1Fifo_push(p->fifo, e)).code) { }

		pthread_cleanup_pop(err.code); // ((Dz1CancelFunc)UnionMemberEntry_del, (void *)e);
	}
	return err;
}

static UnionMemberEntry *UnionMemberList_find(UnionMemberList *p, str_t instance)
{
	UnionMemberEntry *e = NULL, *ret = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (strcmp(e->instance, instance) == 0)
				{
					ret = e;
					break;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}

static int UnionMemberList_nonScalarExist(UnionMemberList *p)
{
	int ret = FALSE;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		UnionMemberEntry *e = NULL;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (e->isPointer || !ObjectInfo_isStaticSize(e->type))
				{
					ret = TRUE;
					break;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}

static int UnionMemberList_comparable(UnionMemberList *p, PublishSpec *sp)
{
	int ret = TRUE;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		UnionMemberEntry *e = NULL;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (!(ObjectInfo_apiOf(e->type, sp) & OBJECT_API_CMP)) { ret = FALSE; break; }
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}

static u32_t UnionMemberList_count(UnionMemberList *p)
{
	return Dz1Fifo_count(p->fifo);
}

static Dz1Error UnionMemberList_travel(UnionMemberList *p, Dz1Error (*func)(void *ptr, UnionMemberEntry *p), void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1Fifo_travel(p->fifo, (Dz1FifoTravelFunc)func, ptr)).code) ERR_OUT(errp);
	return err;
}

typedef struct UnionMemberArrayArg
{
	UnionMemberEntry		**arr;
	u32_t					 idx;
} UnionMemberArrayArg;

static Dz1Error _UnionMemberList_getArray(void *ptr, UnionMemberEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	UnionMemberArrayArg *arg = (UnionMemberArrayArg *)ptr;
	arg->arr[arg->idx++] = p;
	Dz1Error_set(errp, 0);
	return err;
}

static UnionMemberEntry **UnionMemberList_getArray(UnionMemberList *list, u32_t *ret_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	UnionMemberEntry **ret = NULL;
	u32_t cnt = list->count(list);
	if (cnt == 0) ERR_SET_OUT(errp, ENOENT);
	else if ((ret = (UnionMemberEntry **)Dz1Calloc(sizeof(UnionMemberEntry *), cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		UnionMemberArrayArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
		if ((*errp = list->travel(list, _UnionMemberList_getArray, (void *)&arg)).code) ERR_OUT(errp);
		else
		{
			if (ret_cnt != NULL) *ret_cnt = cnt;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
	}
	return ret;
}


UnionMemberList *UnionMemberList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionMemberList *ret = (UnionMemberList *)Dz1Malloc(sizeof(UnionMemberList), errp);
	if (ret == NULL) { }
	else
	{
		memset(ret, 0, sizeof(UnionMemberList));
		pthread_cleanup_push(UnionMemberList_delAndSetNull, (void *)&ret);
		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)UnionMemberEntry_del,
									 (Dz1DumpFunc)UnionMemberEntry_dump, 0, errp)) == NULL) { }
		else
		{
			ret->insert = UnionMemberList_insert;
			ret->add = UnionMemberList_add;
			ret->find = UnionMemberList_find;
			ret->count = UnionMemberList_count;
			ret->travel = UnionMemberList_travel;
			ret->get_array = UnionMemberList_getArray;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (UnionMemberList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void UnionMemberList_del(UnionMemberList *p)
{
	if (!p) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	Dz1Free(p);
}

void UnionMemberList_dump(UnionMemberList *p, int tab)
{
	if (!p) return;
	Dz1Fifo_dump(p->fifo, tab);
}

static Dz1Error _MemberList_merge(void *ptr, UnionMemberEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	UnionMemberList *dst = (UnionMemberList *)ptr;
	if ((p = UnionMemberEntry_clone(p, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = dst->insert(dst, p)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error UnionMemberList_merge(UnionMemberList *dst, UnionMemberList *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = src->travel(src, _MemberList_merge, (void *)dst)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

////////////////////////////////////////////////////////////////////////////////
// UnionMemberList CODEC
static __inline__ UnionMemberList *UnionMemberList_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionMemberList *ret = UnionMemberList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static Dz1Error _UnionMemberList_enc(void *ptr, UnionMemberEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = UnionMemberEntry_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t UnionMemberList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionMemberList *src = (UnionMemberList *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _UnionMemberList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t UnionMemberList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionMemberList *dst = (UnionMemberList *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		UnionMemberEntry *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = UnionMemberEntry_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(UnionMemberEntry_delAndSetNull, (void *)&node);
				if ((status = UnionMemberEntry_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->insert(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (UnionMemberEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// UnionMemberList CODEC
////////////////////////////////////////////////////////////////////////////////






UnionInfo *UnionInfo_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionInfo *ret = (UnionInfo *)Dz1Malloc(sizeof(UnionInfo), errp);
	if (ret == NULL) { }
	else
	{
		memset(ret, 0, sizeof(UnionInfo));
		pthread_cleanup_push(UnionInfo_delAndSetNull, (void *)&ret);
		if ((ret->members = UnionMemberList_new(errp)) == NULL) { }
		else
		{
			ret->comparePresentOnly = FALSE;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (UnionInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void UnionInfo_del(UnionInfo *p)
{
	if (!p) return;
	if (p->members) UnionMemberList_del(p->members);
	Dz1Free(p);
}

void UnionInfo_dump(UnionInfo *p, int tab)
{
	if (!p) return;
	UnionMemberList_dump(p->members, tab);
}

int UnionInfo_isStaticSize(UnionInfo *p) { return UnionMemberList_nonScalarExist(p->members) ? FALSE : TRUE; }
int UnionInfo_comparable(UnionInfo *p, PublishSpec *sp) { return UnionMemberList_comparable(p->members, sp); }

////////////////////////////////////////////////////////////////////////////////
// UnionInfo CODEC
UnionInfo *UnionInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionInfo *ret = UnionInfo_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t UnionInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionInfo *src = (UnionInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, UnionMemberList_enc(cp, size, src->members, param, errp), errp);
		DZ1_ENCODE1(cp, size, src->comparePresentOnly ? 1 : 0, errp, ret);
	}
	return ret;
}

ssize_t UnionInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	UnionInfo *dst = (UnionInfo *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_CODEC_FUNC(cp, size, ret, UnionMemberList_dec(dst->members, cp, size, param, errp), errp);
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->comparePresentOnly = v ? TRUE : FALSE;
	}
	return ret;
}
// UnionInfo CODEC
////////////////////////////////////////////////////////////////////////////////

