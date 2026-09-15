#include <dz1_codec.h>

#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_str.h>

#include <dz1_fifo.h>

#include <Dz1TdcInfoModule.h>

#include "Dz1TdcInfoObject.h"
#include "Dz1TdcInfoStructure.h"

StructMemberEntry *StructMemberEntry_new(FORWARD_TYPE isForwarded, ObjectInfo *type_ref, str_t srcType, int isPointer, str_t instance,
										 u32_t memb_flags, MemberDumpMode dumpMode, str_t arr_cnt_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructMemberEntry *ret = (StructMemberEntry *)Dz1Calloc(sizeof(StructMemberEntry), 1, errp);
	if (ret == NULL) { }
	else
	{
		pthread_cleanup_push(StructMemberList_delAndSetNull, (void *)&ret);
		if (0) { }
		else if (Dz1Str_isVoid(instance)	 == FALSE && (ret->instance		= Dz1Str_dup(instance,		errp)) == NULL) { }
		else if (Dz1Str_isVoid(srcType)		 == FALSE && (ret->srcType		= Dz1Str_dup(srcType,		errp)) == NULL) { }
		else if (Dz1Str_isVoid(arr_cnt_name) == FALSE && (ret->arr_cnt_name = Dz1Str_dup(arr_cnt_name,	errp)) == NULL) { }
		else
		{
			ret->isForwarded = isForwarded;
			ret->type = type_ref;
			ret->isPointer = isPointer;
			ret->memb_flags = memb_flags;
			ret->dumpMode = dumpMode;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (StructMemberList_delAndSetNull, (void *)&ret);
	}
	return ret;

}

void StructMemberEntry_del(StructMemberEntry *p)
{
	if (!p) return;
	if (p->instance)		{ Dz1Free(p->instance); p->instance = NULL; }
	if (p->srcType)			{ Dz1Free(p->srcType); p->srcType = NULL; }
	if (p->arr_cnt_name)	{ Dz1Free(p->arr_cnt_name); p->arr_cnt_name = NULL; }
	Dz1Free(p);
}

static int StructMemberEntry_cmp(StructMemberEntry *a, StructMemberEntry *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a != NULL && b == NULL) return 1;
	else if (a == NULL && b != NULL) return -1;
	else if (a->instance == NULL && b->instance == NULL) return 0;
	else if (a->instance != NULL && b->instance == NULL) return 1;
	else if (a->instance == NULL && b->instance != NULL) return -1;
	else return strcmp(a->instance, b->instance);
}

void StructMemberEntry_dump(StructMemberEntry *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "%s %s%s", p->type ? p->type->name : "(none)", p->isPointer ? "*" : "", p->instance);
	if (StructMemberEntry_isArgInvolve(p) || StructMemberEntry_isIndex(p))
	{
		int printed = 0;
		Dz1Thread_printf("(");
		if (StructMemberEntry_isArgInvolve(p)) { Dz1Thread_printf("arg"); printed = 1; }
		if (StructMemberEntry_isIndex(p)) { Dz1Thread_printf("%sidx", printed ? ", " : ""); }
		Dz1Thread_printf(")\n");
	}
	else Dz1Thread_printf("\n");
}

////////////////////////////////////////////////////////////////////////////////
// StructMemberEntry CODEC
static StructMemberEntry *StructMemberEntry_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructMemberEntry *ret = StructMemberEntry_new(FORWARD_TYPE_NONE, NULL, NULL, 0, NULL, 0,  0, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static ssize_t StructMemberEntry_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructMemberEntry *src = (StructMemberEntry *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		u32_t v32 = 0;
		DZ1_ENCODE4(cp, size, 0xCAFE0000, errp, ret);					// write version

		v32 = (u32_t)src->isForwarded;
		DZ1_ENCODE4(cp, size, v32, errp, ret);

		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->type->name, errp), errp);

		DZ1_ENCODE1(cp, size, src->srcType ? 1 : 0, errp, ret);
		if (src->srcType) DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->srcType, errp), errp);

		DZ1_ENCODE4(cp, size, src->isPointer, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->instance, errp), errp);
//		DZ1_ENCODE4(cp, size, src->isReferenced, errp, ret);
		DZ1_ENCODE4(cp, size, src->memb_flags, errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->dumpMode & 0xFF), errp, ret);
//		DZ1_ENCODE4(cp, size, src->argInvolve, errp, ret);
//		DZ1_ENCODE4(cp, size, src->isIndex, errp, ret);
//		DZ1_ENCODE1(cp, size, (u8_t)(src->isAsnOptional ? 1 : 0), errp, ret);

		if (StructMemberEntry_isArray(src))
		{
			if (Dz1Str_isVoid(src->arr_cnt_name))
				DZ1_ENCODE1(cp, size, 0, errp, ret);
			else
			{
				DZ1_ENCODE1(cp, size, 1, errp, ret);
				DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->arr_cnt_name, errp), errp);
			}
		}
	}
	return ret;
}

static ssize_t StructMemberEntry_dec_NewVer0(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{	// new version 0 reader
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	ssize_t ret = 0;

	StructMemberEntry *dst = (StructMemberEntry *)_dst;
	u32_t v32 = 0;
	u8_t *cp = src, v8;
	str_t objName = NULL;

	Dz1MdefcModule *module = (Dz1MdefcModule *)param;

	DZ1_DECODE4(&v32, cp, size, errp, ret);
	dst->isForwarded = (FORWARD_TYPE)v32;

	DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &objName, errp), errp);
	pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
	if ((dst->type = module->findObject(module, objName)) == NULL)
	{
		if ((dst->type = module->regUnknownObject(module, objName, errp)) == NULL) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);
	if (errp->code != 0) DZ1_CODEC_ERR_RET(errp);

	DZ1_DECODE1(&v8, cp, size, errp, ret);
	if (v8) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->srcType, errp), errp);

	DZ1_DECODE4((u32_t *)&dst->isPointer, cp, size, errp, ret);
	DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->instance, errp), errp);
	DZ1_DECODE4(&dst->memb_flags, cp, size, errp, ret);
	DZ1_DECODE1(&v8, cp, size, errp, ret); dst->dumpMode = (MemberDumpMode)v8;
// 	DZ1_DECODE4((u32_t *)&dst->argInvolve, cp, size, errp, ret);
// 	DZ1_DECODE4((u32_t *)&dst->isIndex, cp, size, errp, ret);
//	DZ1_DECODE1(&v, cp, size, errp, ret); dst->isAsnOptional = v ? TRUE : FALSE;
	if (StructMemberEntry_isArray(dst))
	{
		DZ1_DECODE1(&v8, cp, size, errp, ret);
		if (v8) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->arr_cnt_name, errp), errp);
	}
	return ret;
}

typedef ssize_t (*StructMembDecoderF)(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);
static StructMembDecoderF StructMembDecApi[] =
{
	StructMemberEntry_dec_NewVer0,
	NULL
};
static u32_t StructMembDecApiCnt = sizeof(StructMembDecApi) / sizeof(StructMembDecoderF) - 1;

static ssize_t StructMemberEntry_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructMemberEntry *dst = (StructMemberEntry *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		str_t objName = NULL;
		u8_t *cp = src, v8;
		u32_t v32 = 0;

		DZ1_DECODE4(&v32, cp, size, errp, ret);	// decode Version or isForward

		if (v32 & 0xFFFF0000)
		{	// new version stream
			u32_t version = v32 & 0xFFFF;
			if (version >= StructMembDecApiCnt) DZ1_CODEC_ERRSET_RET(errp, EPERM);
			else
			{	// switch to proper version decoder
				StructMembDecoderF decoder= StructMembDecApi[version];
				DZ1_CODEC_FUNC(cp, size, ret, decoder(dst, cp, size, param, errp), errp);
			}
		}
		else
		{	// original version reader
			dst->isForwarded = (FORWARD_TYPE)v32;

			DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &objName, errp), errp);
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
			if ((dst->type = module->findObject(module, objName)) == NULL)
			{
				if ((dst->type = module->regUnknownObject(module, objName, errp)) == NULL) ERR_OUT(errp);
			}
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);
			if (errp->code != 0) DZ1_CODEC_ERR_RET(errp);

			DZ1_DECODE1(&v8, cp, size, errp, ret);
			if (v8) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->srcType, errp), errp);

			DZ1_DECODE4((u32_t *)&dst->isPointer, cp, size, errp, ret);
			DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->instance, errp), errp);

// 			DZ1_DECODE4((u32_t *)&dst->isReferenced, cp, size, errp, ret);
			DZ1_DECODE4(&dst->memb_flags, cp, size, errp, ret);

			DZ1_DECODE1(&v8, cp, size, errp, ret); dst->dumpMode = (MemberDumpMode)v8;

// 			DZ1_DECODE4((u32_t *)&dst->argInvolve, cp, size, errp, ret);
// 			DZ1_DECODE4((u32_t *)&dst->isIndex, cp, size, errp, ret);
// 			DZ1_DECODE1(&v, cp, size, errp, ret); dst->isAsnOptional = v ? TRUE : FALSE;
			DZ1_DECODE4(&v32, cp, size, errp, ret); dst->memb_flags |= (v32 ? MEMBER_FLAG_ARG_INVOLVE : 0); //dst->argInvolve
			DZ1_DECODE4(&v32, cp, size, errp, ret); dst->memb_flags |= (v32 ? MEMBER_FLAG_IS_INDEX : 0); // dst->isIndex
			DZ1_DECODE1(&v8, cp, size, errp, ret); dst->memb_flags |= (v32 ? MEMBER_FLAG_ASN_OPTIONAL : 0);// dst->isAsnOptional = v8 ? TRUE : FALSE;
		}
	}
	return ret;
}
// StructMemberEntry CODEC
////////////////////////////////////////////////////////////////////////////////

// typedef struct StructMemberListFindInstanceArg
// {
// 	StructMemberEntry			*ret;
// 	str_t						 instance;
// } StructMemberListFindInstanceArg;
// 
// static Dz1Error _StructMemberList_findInstance(void *ptr, void *ep)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	StructMemberListFindInstanceArg *arg = (StructMemberListFindInstanceArg *)ptr;
// 	StructMemberEntry *p = (StructMemberEntry *)ep;
// 	if (strcmp(p->instance, arg->instance) == 0)
// 	{
// 		arg->ret = p;
// 		Dz1Error_set(errp, EEXIST);
// 	}
// 	return err;
// }
// 
// static StructMemberEntry *StructMemberList_findInstance(StructMemberList *p, str_t instance)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	StructMemberEntry *ret = NULL;
// 	StructMemberListFindInstanceArg arg = { NULL, instance };
// 	if ((*errp = Dz1Fifo_travel(p->fifo, _StructMemberList_findInstance, (void *)&arg)).code == EEXIST) ret = arg.ret;
// 	return ret;
// }

static Dz1Error StructMemberList_insert(StructMemberList *p, StructMemberEntry *e)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (e->type->type == ObjectType_array && !e->isPointer) ERR_SET_OUT(errp, EINVAL);
	else if (p->find(p, e->instance) != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((*errp = Dz1Fifo_push(p->fifo, e)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error StructMemberList_append(StructMemberList *p, FORWARD_TYPE isForwarded, ObjectInfo *type, str_t srcType, int isPointer, str_t instance,
									u32_t memb_flags, MemberDumpMode dump_mode, str_t arr_cnt_name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StructMemberEntry *e = StructMemberEntry_new(isForwarded, type, srcType, isPointer, instance, memb_flags, dump_mode, arr_cnt_name, &err);
	if (e == NULL)
	{
		ERR_OUT(&err);
	}
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)StructMemberEntry_del, (void *)e);

		if ((err = StructMemberList_insert(p, e)).code)
		{
			ERR_OUT(&err);
		}

		pthread_cleanup_pop(err.code); // ((Dz1CancelFunc)StructMemberEntry_del, (void *)e);
	}
	return err;
}

StructMemberEntry *StructMemberList_find(StructMemberList *p, str_t instance)
{
	int found = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (strcmp(e->instance, instance) == 0) { found = TRUE; break; }
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return found ? e : NULL;
}

static u32_t StructureMemberList_count(StructMemberList *p)
{
	return Dz1Fifo_count(p->fifo);
}

static Dz1Error StructMemberList_travel(StructMemberList *p, Dz1Error (*func)(void *ptr, StructMemberEntry *p), void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1Fifo_travel(p->fifo, (Dz1FifoTravelFunc)func, ptr)).code) ERR_OUT(errp);
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// StructMemberList Get Array
typedef struct StructMemberListMkArrArg
{
	StructMemberEntry **arr;
	u32_t idx;
} StructMemberListMkArrArg;

static Dz1Error _StructMemberList_get_array(void *ptr, StructMemberEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StructMemberListMkArrArg *arg = (StructMemberListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static StructMemberEntry **StructMemberList_get_array(StructMemberList *p, u32_t *ret_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StructMemberEntry **ret = NULL;
	u32_t cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (StructMemberEntry **)Dz1Calloc(sizeof(StructMemberEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		StructMemberListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);

		*errp = p->travel(p, _StructMemberList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
	}
	return ret;
}
// StructMemberList Get Array
///////////////////////////////////////////////////////////////////////////////

StructMemberList *StructMemberList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructMemberList *ret = (StructMemberList *)Dz1Malloc(sizeof(StructMemberList), errp);
	if (ret == NULL) { }
	else
	{
		memset(ret, 0, sizeof(StructMemberList));
		pthread_cleanup_push(StructMemberList_delAndSetNull, (void *)&ret);
		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)StructMemberEntry_del, (Dz1DumpFunc)StructMemberEntry_dump, 0, errp)) == NULL) { }
		else
		{
			ret->add = StructMemberList_insert;
			ret->append = StructMemberList_append;
			ret->find = StructMemberList_find;
			ret->count = StructureMemberList_count;
			ret->travel = StructMemberList_travel;
			ret->get_array = StructMemberList_get_array;
			ret->cmp = StructMemberEntry_cmp;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (StructMemberList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StructMemberList_del(StructMemberList *p)
{
	if (!p) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	Dz1Free(p);
}

void StructMemberList_dump(StructMemberList *p, int tab)
{
	if (!p) return;
	Dz1Fifo_dump(p->fifo, tab);
}

static int StructureMemberList_comaprable(StructMemberList *p, PublishSpec *sp)
{
	int cmp = TRUE, keyExist = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
//			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL && e->isIndex == TRUE)
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL && StructMemberEntry_isIndex(e))
			{
				ObjectInfo *e_ori = ObjectInfo_getOrigin(e->type);
				keyExist = TRUE;
				if (ObjectInfo_isPrimitive(e_ori) == FALSE && !(ObjectInfo_apiOf(e_ori, sp) & OBJECT_API_CMP))
				{
					Dz1Thread_printf("e_ori = "); ObjectInfo_dump(e_ori, 0);
					Dz1Thread_printf("StructureMemberList_comaprable() : %s %s isn't have compare api\n", e->type->name, e->instance);
					cmp = FALSE;
					break;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return keyExist && cmp ? TRUE : FALSE;
}

static int StructureMemberList_nonScalarExist(StructMemberList *p)
{
	int ret = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
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





////////////////////////////////////////////////////////////////////////////////
// StructMemberList CODEC
static __inline__ StructMemberList *StructMemberList_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructMemberList *ret = StructMemberList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static Dz1Error _StructMemberList_enc(void *ptr, StructMemberEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = StructMemberEntry_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t StructMemberList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructMemberList *src = (StructMemberList *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		Dz1ListCodecArg arg;
		u16_t cnt = src->count(src);
		DZ1_ENCODE2(cp, size, cnt, errp, ret);
		Dz1ListCodecArg_init(&arg, cp, size, NULL);
		if ((*errp = src->travel(src, _StructMemberList_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t StructMemberList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructMemberList *dst = (StructMemberList *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u16_t cnt, i;
		StructMemberEntry *node = NULL;
		DZ1_DECODE2(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = StructMemberEntry_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(StructMemberEntry_delAndSetNull, (void *)&node);
				if ((status = StructMemberEntry_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (StructMemberEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// StructMemberList CODEC
////////////////////////////////////////////////////////////////////////////////











StructureInfo *StructureInfo_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructureInfo *ret = (StructureInfo *)Dz1Calloc(sizeof(StructureInfo), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StructureInfo_delAndSetNull, (void *)&ret);

		if ((ret->members = StructMemberList_new(errp)) == NULL) { }
		else
		{
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (StructureInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StructureInfo_del(StructureInfo *p)
{
	if (!p) return;
	if (p->members) StructMemberList_del(p->members);
	Dz1Free(p);
}

void StructureInfo_dump(StructureInfo *p, int tab)
{
	if (!p) return;
	StructMemberList_dump(p->members, tab);
}

int StructureInfo_comparable(StructureInfo *p, PublishSpec *sp)
{
	return StructureMemberList_comaprable(p->members, sp);
}

int StructureInfo_isStaticSize(StructureInfo *p)
{
	return StructureMemberList_nonScalarExist(p->members) ? FALSE : TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// StructureInfo CODEC
StructureInfo *StructureInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructureInfo *ret = StructureInfo_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t StructureInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructureInfo *src = (StructureInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, StructMemberList_enc(cp, size, src->members, param, errp), errp);
	}
	return ret;
}

ssize_t StructureInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	StructureInfo *dst = (StructureInfo *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_CODEC_FUNC(cp, size, ret, StructMemberList_dec(dst->members, cp, size, param, errp), errp);
	}
	return ret;
}
// StructureInfo CODEC
////////////////////////////////////////////////////////////////////////////////

