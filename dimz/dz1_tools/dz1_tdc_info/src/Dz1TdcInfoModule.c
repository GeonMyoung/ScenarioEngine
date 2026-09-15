#include <dz1_stdio.h>
#include <dz1_codec.h>

#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>

#include "Dz1TdcInfoModule.h"

typedef struct Dz1MdefcModuleAddObjectCancelParam
{
	void *tree;
	ObjectInfo *o;
} Dz1MdefcModuleAddObjectCancelParam;

static EnumEntry *Dz1MdefcModule_findEnum(Dz1MdefcModule *p, str_t _name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	EnumEntry *ret = NULL;

	void *c = NULL;
	char nmp[128];
	strcpy(nmp, _name);
	if ((c = Dz1FifoCursor_new(p->objFifo, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t o_len;
		ObjectInfo *o = NULL;
		pthread_cleanup_push(Dz1FifoCursor_del, (void *)c);

		for(Dz1FifoCursorForward(c))
		{
			o = (ObjectInfo *)Dz1FifoCursor_data(c);
			if (o->type == ObjectType_enumerate && strncmp(nmp, o->name, (o_len = (u32_t)strlen(o->name))) == 0)
			{
				char *cp = nmp + o_len;
				if (*cp++ == '_' && *cp != 0)
				{
					EnumInfo *info = (EnumInfo *)o->info;
					if ((ret = info->enums->findByName(info->enums, cp)) != NULL) break;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, (void *)c);
	}
	return ret;
}

static Dz1Error Dz1MdefcModule_addModule(Dz1MdefcModule *p, Dz1MdefcModule *m)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1AATree_insert(p->moduleTree, m)).code) ERR_OUT(&err);
	return err;
}

typedef struct Dz1MdefcModuleFindModuleArg
{
	str_t name;
	Dz1MdefcModule *ret;
} Dz1MdefcModuleFindModuleArg;

static Dz1Error _Dz1MdefcModule_findModule(void *ptr, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1MdefcModule *p = (Dz1MdefcModule *)data;
	Dz1MdefcModuleFindModuleArg *arg = (Dz1MdefcModuleFindModuleArg *)ptr;

	if ((arg->ret = p->findModule(p, arg->name)) != NULL) 
	{
		Dz1Thread_printf("Module not found : %s\n", arg->name);
		Dz1Error_set(&err, EEXIST);
	}

	return err;
}

static Dz1MdefcModule *Dz1MdefcModule_findModule(Dz1MdefcModule *p, str_t name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcModule key, *ret = NULL;
	key.name = name;
	if ((ret = (Dz1MdefcModule *)Dz1AATree_find(p->moduleTree, &key)) == NULL)
	{
		Dz1MdefcModuleFindModuleArg arg = { NULL, NULL };
		arg.name = name;
		if ((err = Dz1AATree_travel(p->moduleTree, _Dz1MdefcModule_findModule, (void *)&arg)).code == EEXIST) ret = arg.ret;
	}
	return ret;
}

static void Dz1MdefcModule_addObjectCancel(void *ptr)
{
	Dz1MdefcModuleAddObjectCancelParam *p = (Dz1MdefcModuleAddObjectCancelParam *)ptr;
	Dz1AATree_remove(p->tree, p->o);
}

static Dz1Error Dz1MdefcModule_addObject(Dz1MdefcModule *p, ObjectInfo *o)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((err = Dz1AATree_insert(p->objTree, o)).code) ERR_OUT(&err);
	else
	{
		Dz1MdefcModuleAddObjectCancelParam cp;
		cp.tree = p->objTree;
		cp.o = o;
		pthread_cleanup_push(Dz1MdefcModule_addObjectCancel, (void *)&cp);

		if((err = Dz1Fifo_push(p->objFifo, o)).code) ERR_OUT(&err);

		pthread_cleanup_pop(err.code); // (Dz1MdefcModule_addObjectCancel, (void *)&cp);
	}
	return err;
}

typedef struct Dz1MdefcModuleFindObjectArg
{
	str_t name;
	ObjectInfo *ret;
} Dz1MdefcModuleFindObjectArg;

static __inline__ Dz1Error _Dz1MdefcModule_findObject(void *ptr, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1MdefcModule *p = (Dz1MdefcModule *)data;
	Dz1MdefcModuleFindObjectArg *arg = (Dz1MdefcModuleFindObjectArg *)ptr;

	if ((arg->ret = p->findObject(p, arg->name)) != NULL) Dz1Error_set(&err, EEXIST);

	return err;
}

static ObjectInfo *Dz1MdefcModule_findObject(Dz1MdefcModule *p, str_t name)
{

	ObjectInfo key, *ret = NULL;
	key.type = ObjectType_max;
	key.name = name;
	if ((ret = (ObjectInfo *)Dz1AATree_find(p->objTree, &key)) == NULL)
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		Dz1MdefcModuleFindObjectArg arg = { NULL, NULL };
		arg.name = name;
		if ((err = Dz1AATree_travel(p->moduleTree, _Dz1MdefcModule_findObject, (Dz1MdefcModuleFindObjectArg *)&arg)).code == EEXIST) ret = arg.ret;
	}
	return ret;
}

static Dz1Error __RegPrimitiveList(void *ptr, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1MdefcModule *p = (Dz1MdefcModule *)ptr;
	NativeTypeSpec *prim = (NativeTypeSpec *)data;
	ObjectInfo *o = NULL;

	if ((o = ObjectInfo_new(ObjectType_primitive, prim->name, NULL, PRIMITIVE_TYPE_API, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)ObjectInfo_del, (void *)o);

		if ((o->info = PrimitiveInfo_new(prim->native, prim->storage, prim->prefix, &err)) == NULL) ERR_OUT(&err);
		else if ((err = p->addObject(p, o)).code) ERR_OUT(&err);

		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)ObjectInfo_del, (void *)o);
	}
	return err;
}

static Dz1Error _RegPrimitiveList(Dz1MdefcModule *p, void *primitives)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((err = Dz1AATree_travel(primitives, __RegPrimitiveList, (void *)p)).code) ERR_OUT(&err);

	return err;
}

//static int Dz1MdefcModule_cmp(Dz1MdefcModule *a, Dz1MdefcModule *b) { return strcmp(a->name, b->name); }

static ObjectInfo *Dz1MdefcModule_regUnknownObject(Dz1MdefcModule *p, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	ObjectInfo key, *ret = NULL;
	key.name = name;
	if ((ret = (ObjectInfo *)Dz1AATree_find(p->objUnknown, &key)) == NULL)
	{
		if ((ret = ObjectInfo_new(ObjectType_max, name, NULL, OBJECT_API_TDC_FULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ObjectInfo_delAndSetNull, (void *)&ret);

			if ((*errp = Dz1AATree_insert(p->objUnknown, ret)).code) ERR_OUT(errp);

			pthread_cleanup_pop(errp->code);
		}
	}
	return ret;
}

static ObjectInfo *Dz1MdefcModule_findUnknownObject(Dz1MdefcModule *p, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ObjectInfo key, *ret = NULL;
	key.name = name;
	if ((ret = (ObjectInfo *)Dz1AATree_find(p->objUnknown, &key)) == NULL) Dz1Error_set(errp, ENOENT);
	return ret;
}

static ObjectInfo *Dz1MdefcModule_extractUnknownObject(Dz1MdefcModule *p, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ObjectInfo key, *ret = NULL;
	key.name = name;
	if ((ret = (ObjectInfo *)Dz1AATree_extract(p->objUnknown, &key)) == NULL) Dz1Error_set(errp, ENOENT);
	return ret;
}

static void ObjectInfo_d(ObjectInfo *p, int tab)
{
	if (p == NULL) Dz1Thread_tprintf(tab, "NULL\n");
	else Dz1Thread_tprintf(tab, "%s\n", p->name);
}

Dz1MdefcModule *Dz1MdefcModule_new(str_t name, str_t ext, PublishSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MdefcModule *ret = (Dz1MdefcModule *)Dz1Calloc(sizeof(Dz1MdefcModule), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MdefcModule_delAndSetNull, (void *)&ret);
//		ret->is_loaded = FALSE;

		ret->findEnum = Dz1MdefcModule_findEnum;

		ret->addModule = Dz1MdefcModule_addModule;
		ret->findModule = Dz1MdefcModule_findModule;

		ret->addObject = Dz1MdefcModule_addObject;
		ret->findObject = Dz1MdefcModule_findObject;

		ret->regUnknownObject = Dz1MdefcModule_regUnknownObject;
		ret->findUnknownObject = Dz1MdefcModule_findUnknownObject;
		ret->extractUnknownObject = Dz1MdefcModule_extractUnknownObject;

		if (name != NULL && (ret->name = Dz1Str_dup(name, errp)) == NULL) ERR_OUT(errp);
		else if (ext != NULL && (ret->ext = Dz1Str_dup(ext, errp)) == NULL) ERR_OUT(errp);

		else if ((ret->moduleTree = Dz1AATree_new((Dz1CmpFunc)Dz1MdefcModule_cmp, (Dz1DelFunc)Dz1MdefcModule_del, (Dz1DumpFunc)Dz1MdefcModule_dump, errp)) == NULL) ERR_OUT(errp);

		else if ((ret->objFifo = Dz1Fifo_new((Dz1DelFunc)ObjectInfo_del, (Dz1DumpFunc)ObjectInfo_dump, 0, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->objTree = Dz1AATree_new((Dz1CmpFunc)ObjectInfo_cmp, NULL, (Dz1DumpFunc)ObjectInfo_dump, errp)) == NULL) ERR_OUT(errp);

		else if ((ret->objUnknown = Dz1AATree_new((Dz1CmpFunc)ObjectInfo_cmp, (Dz1DelFunc)ObjectInfo_del, (Dz1DumpFunc)ObjectInfo_d, errp)) == NULL) ERR_OUT(errp);

		else if (spec != NULL && (*errp = _RegPrimitiveList(ret, spec->primitives)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MdefcModule_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MdefcModule_del(Dz1MdefcModule *p)
{
	if (!p) return;
	if (p->name) Dz1Str_del(p->name);
	if (p->ext) Dz1Str_del(p->ext);
	if (p->moduleTree) Dz1AATree_del(p->moduleTree);
	if (p->objFifo) Dz1Fifo_del(p->objFifo);
	if (p->objTree) Dz1AATree_del(p->objTree);
	if (p->objUnknown) Dz1AATree_del(p->objUnknown);
	Dz1Free(p);
}

void Dz1MdefcModule_dump(Dz1MdefcModule *p, int tab)
{
	if (!p) return;
	if (p->includeStatus == ModuleIncludeStatus_included)
	{
		Dz1Thread_tprintf(tab++, "%s.%s = {\n", p->name, p->ext);
		Dz1Thread_tprintf(tab++, "included = {\n");
		Dz1AATree_dump(p->moduleTree, tab);
		Dz1Thread_tprintf(--tab, "}\n");

		Dz1Thread_tprintf(tab++, "Objects = {\n");
		Dz1Fifo_dump(p->objFifo, tab);
		Dz1Thread_tprintf(--tab, "}\n");

		Dz1Thread_tprintf(tab++, "Unknown Objects = {\n");
		Dz1AATree_dump(p->objUnknown, tab);
		Dz1Thread_tprintf(--tab, "}\n");
		Dz1Thread_tprintf(--tab, "}\n");
	}
	else if (p->includeStatus == ModuleIncludeStatus_natived)
		Dz1Thread_tprintf(tab, "%s.%s for native types\n", p->name, p->ext);
	else if (p->includeStatus == ModuleIncludeStatus_referenced)
		Dz1Thread_tprintf(tab, "%s.%s for reference types\n", p->name, p->ext);
	else Dz1Thread_tprintf(tab, "%s.%s unknown reason\n", p->name, p->ext);
}

int Dz1MdefcModule_cmp(Dz1MdefcModule *a, Dz1MdefcModule *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (b != NULL) return 1;
	else if (a != NULL) return -1;
	else if (a->name == NULL && b->name == NULL) return 0;
	else if (b->name != NULL) return 1;
	else if (a->name != NULL) return -1;
	else return strcmp(a->name, b->name);
}

static ssize_t Dz1MdefcModule_encBody(u8_t *dst, size_t size, Dz1MdefcModule *src, void *param, Dz1Error *err);
static ssize_t Dz1MdefcModule_decBody(Dz1MdefcModule *dst, u8_t *src, size_t size, void *param, Dz1Error *err);
////////////////////////////////////////////////////////////////////////////////
// Included module CODEC
static ssize_t _include_module_enc(u8_t *dst, size_t size, Dz1MdefcModule *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		// Dz1Thread_printf("save sub module = %s, %s, %d\n", src->name, src->ext, src->includeStatus);
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->name, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->ext, errp), errp);
		DZ1_ENCODE1(cp, size, (u8_t)(src->includeStatus & 0xFF), errp, ret);
		if (src->includeStatus == ModuleIncludeStatus_included)
			DZ1_CODEC_FUNC(cp, size, ret, Dz1MdefcModule_encBody(cp, size, src, param, errp), errp);
	}
	return ret;
}

static ssize_t _include_module_dec(Dz1MdefcModule *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->name, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->ext, errp), errp);
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->includeStatus = (ModuleIncludeStatus)v;
		// Dz1Thread_printf("load sub module = %s, %s, %d\n", dst->name, dst->ext, dst->includeStatus);
		if (dst->includeStatus == ModuleIncludeStatus_included)
			DZ1_CODEC_FUNC(cp, size, ret, Dz1MdefcModule_decBody(dst, cp, size, param, errp), errp);
	}
	return ret;
}
// Included module CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Included module tree CODEC
static Dz1Error __include_module_tree_enc(void *ptr, void *_p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	Dz1MdefcModule *p = (Dz1MdefcModule *)_p;
	ssize_t status = _include_module_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t _include_module_tree_enc(u8_t *dst, size_t size, Dz1AATree *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		Dz1ListCodecArg arg;
		u8_t *cp = dst;
		u32_t cnt = Dz1AATree_count(src);
		DZ1_ENCODE4(cp, size, cnt, errp, ret);

		Dz1ListCodecArg_init(&arg, cp, size, param);
		if ((*errp = Dz1AATree_travel(src, __include_module_tree_enc, &arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t _include_module_tree_dec(Dz1AATree *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u32_t cnt, i;
		Dz1MdefcModule *node = NULL;
		DZ1_DECODE4(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = Dz1MdefcModule_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1MdefcModule_delAndSetNull, (void *)&node);
				if ((status = _include_module_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = Dz1AATree_insert(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (Dz1MdefcModule_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Included module tree CODEC
////////////////////////////////////////////////////////////////////////////////

static ssize_t _unknown_object_enc(u8_t *dst, size_t size, ObjectInfo *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->name, errp), errp);

	}
	return ret;
}

static ssize_t _unknown_object_dec(ObjectInfo *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		dst->type = ObjectType_max;
		dst->api = OBJECT_API_TDC_FULL;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->name, errp), errp);
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
// Unknown Object tree CODEC
static Dz1Error __unknown_object_tree_enc(void *ptr, void *_p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ObjectInfo *p = (ObjectInfo *)_p;
	ssize_t status = _unknown_object_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	return err;
}

static ssize_t _unknown_object_tree_enc(u8_t *dst, size_t size, Dz1AATree *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		Dz1ListCodecArg arg;
		u8_t *cp = dst;
		u32_t cnt = Dz1AATree_count(src);
		DZ1_ENCODE4(cp, size, cnt, errp, ret);

		Dz1ListCodecArg_init(&arg, cp, size, param);
		if ((*errp = Dz1AATree_travel(src, __unknown_object_tree_enc, &arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t _unknown_object_tree_dec(Dz1AATree *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u32_t cnt, i;
		ObjectInfo *node = NULL;
		DZ1_DECODE4(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = ObjectInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(ObjectInfo_delAndSetNull, (void *)&node);
				if ((status = _unknown_object_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = Dz1AATree_insert(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (ObjectInfo_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Unknown Object tree CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// object fifo CODEC
static Dz1Error _object_enc(void *ptr, void *_p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	ObjectInfo *p = (ObjectInfo *)_p;
	Dz1ListCodecArg *arg = (Dz1ListCodecArg *)ptr;
	ssize_t status = ObjectInfo_enc(arg->cp, arg->size, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);

	return  err;
}

static ssize_t _object_fifo_enc(u8_t *dst, size_t size, Dz1AATree *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		Dz1ListCodecArg arg;
		u8_t *cp = dst;
		u32_t cnt = Dz1Fifo_count(src);
		DZ1_ENCODE4(cp, size, cnt, errp, ret);

		Dz1ListCodecArg_init(&arg, cp, size, param);
		if ((*errp = Dz1Fifo_travel(src, _object_enc, &arg)).code) DZ1_CODEC_ERR_RET(errp);
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);
	}
	return ret;
}

static ssize_t _object_fifo_dec(Dz1AATree *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		u32_t cnt, i;
		ObjectInfo *node = NULL;
		DZ1_DECODE4(&cnt, cp, size, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = ObjectInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(ObjectInfo_delAndSetNull, (void *)&node);
				if ((status = ObjectInfo_dec(node, cp, size, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else
				{
					ObjectInfo *unk = NULL;
					//Dz1Thread_printf("@@@ [%d] Object %s ok\n", i, node->name);
					if ((unk = module->extractUnknownObject(module, node->name, errp)) == NULL)
					{	// just add to module
						//Dz1Thread_printf("@@@ [%d] Object %s is fresh\n", i, node->name);
						if ((*errp = module->addObject(module, node)).code)
						{
							if (node->type == ObjectType_primitive) Dz1Error_set(errp, 0);
							else ERR_OUT(errp);
						}
						else
						{
							node = NULL;
							Dz1Error_set(errp, 0);
						}
					}
					else
					{
						//Dz1Thread_printf("@@@ [%d] Object %s update\n", i, node->name);
						unk->type = node->type;
						if (node->srcName != NULL && strlen(node->srcName) > 0)
						{
							Dz1Str_delAndSetNull(&unk->srcName);
							unk->srcName = node->srcName;
							node->srcName = NULL;
						}
						unk->api = node->api;
						unk->info = node->info;
						node->info = NULL;

						if ((*errp = module->addObject(module, unk)).code)
						{
							if (node->type == ObjectType_primitive) Dz1Error_set(errp, 0);
							else ERR_OUT(errp);
						}
					}

					if (errp->code == 0) DZ1_CODEC_APPLY(cp, size, status, ret);
				}
				pthread_cleanup_pop(1); // (ObjectInfo_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// object fifo CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MdefcModule Body CODEC
static ssize_t Dz1MdefcModule_encBody(u8_t *dst, size_t size, Dz1MdefcModule *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		// Dz1Thread_printf("save embedded module >>>\n");
		DZ1_CODEC_FUNC(cp, size, ret, _include_module_tree_enc(cp, size, src->moduleTree, param, errp), errp);
		// Dz1Thread_printf("save embedded module <<< %s.%s\n", src->name, src->ext);
		DZ1_CODEC_FUNC(cp, size, ret, _unknown_object_tree_enc(cp, size, src->objUnknown, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _object_fifo_enc(cp, size, src->objFifo, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MdefcModule_decBody(Dz1MdefcModule *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		//Dz1Thread_printf("load embedded module >>>\n");
		DZ1_CODEC_FUNC(cp, size, ret, _include_module_tree_dec(dst->moduleTree, cp, size, param, errp), errp);
		//Dz1Thread_printf("load embedded module <<< %s.%s\n", dst->name, dst->ext);
		DZ1_CODEC_FUNC(cp, size, ret, _unknown_object_tree_dec(dst->objUnknown, cp, size, param, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _object_fifo_dec(dst->objFifo, cp, size, dst, errp), errp);
//		dst->is_loaded = TRUE;
	}
	return ret;
}
// Dz1MdefcModule Body CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MdefcModule CODEC
Dz1MdefcModule *Dz1MdefcModule_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MdefcModule *ret = Dz1MdefcModule_new(NULL, NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t Dz1MdefcModule_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MdefcModule *src = (Dz1MdefcModule *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->name, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->ext, errp), errp);
		DZ1_ENCODE1(cp, size, (u8_t)(src->includeStatus & 0xFF), errp, ret);

		DZ1_CODEC_FUNC(cp, size, ret, Dz1MdefcModule_encBody(cp, size, src, param, errp), errp);
// 		DZ1_CODEC_FUNC(cp, size, ret, _include_module_tree_enc(cp, size, src->moduleTree, param, errp), errp);
// 		DZ1_CODEC_FUNC(cp, size, ret, _unknown_object_tree_enc(cp, size, src->objUnknown, param, errp), errp);
// 		DZ1_CODEC_FUNC(cp, size, ret, _object_fifo_enc(cp, size, src->objFifo, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1MdefcModule_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MdefcModule *dst = (Dz1MdefcModule *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->name, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->ext, errp), errp);
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->includeStatus = (ModuleIncludeStatus)v;

		DZ1_CODEC_FUNC(cp, size, ret, Dz1MdefcModule_decBody(dst, cp, size, param, errp), errp);

	}
	return ret;
}
// Dz1MdefcModule CODEC
////////////////////////////////////////////////////////////////////////////////

static Dz1MdefcModule *_Dz1MdefcModule_load(Dz1Binary *bin, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MdefcModule *ret = NULL;
	if ((ret = Dz1MdefcModule_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		ssize_t status = 0;
		pthread_cleanup_push(Dz1MdefcModule_delAndSetNull, (void *)&ret);

		if ((status = Dz1MdefcModule_dec(ret, bin->data, bin->size, ret, errp)) < 0)
		{
			Dz1Thread_printf("!!! Module = "); Dz1MdefcModule_dump(ret, 0);
			ERR_OUT(errp);
		}
		else if (status != bin->size)
		{
			Dz1Thread_printf("!!! Module = "); Dz1MdefcModule_dump(ret, 0);
			ERR_SET_OUT(errp, EFAULT);
		}
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1MdefcModule_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1MdefcModule *Dz1MdefcModule_load1(str_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MdefcModule *ret = NULL;

	Dz1Binary *bin = NULL;
	if ((bin = Dz1BinFileA_load(fn, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		if ((ret = _Dz1MdefcModule_load(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

Dz1MdefcModule *Dz1MdefcModule_load2(str_t path, str_t name_ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MdefcModule *ret = NULL;

	Dz1Binary *bin = NULL;
	if ((bin = Dz1BinFileA_load2(path, name_ext, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		if ((ret = _Dz1MdefcModule_load(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

Dz1MdefcModule *Dz1MdefcModule_load3(str_t path, str_t name, str_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MdefcModule *ret = NULL;

	Dz1Binary *bin = NULL;
	if ((bin = Dz1BinFileA_load3(path, name, ext, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		if ((ret = _Dz1MdefcModule_load(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

Dz1MdefcModule *Dz1MdefcModule_iload(str_t path[], u32_t cnt, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MdefcModule *ret = NULL;

	Dz1Binary *bin = NULL;
	if ((bin = Dz1BinFileA_iload(path, cnt, name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		if ((ret = _Dz1MdefcModule_load(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

Dz1Error Dz1MdefcModule_save(Dz1MdefcModule *module, str_t path, str_t name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	FILE *fp = NULL;
	char fn[4096];
	if ((*errp = Dz1FileName_mkFullName(fn, Dz1ArrElCnt(char, fn), path, name)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf("module object = %s\n", fn);
		if ((fp = Dz1FileStream_open(fn, "wb", errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *bin = NULL;
			pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

			if ((bin = Dz1Binary_new(NULL, 0, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t size = 0;
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

				if ((size = Dz1MdefcModule_enc(NULL, -1, module, module, errp)) < 0) ERR_OUT(errp);
				else if ((bin->data = (u8_t *)Dz1Malloc((bin->size = (u32_t)size), errp)) == NULL) ERR_OUT(errp);
				else
				{
					Dz1Thread_printf("==[ Actual Write ]=====================\n");
					if ((size = Dz1MdefcModule_enc(bin->data, bin->size, module, module, errp)) < 0) ERR_OUT(errp);
					else if (size != bin->size) ERR_SET_OUT(errp, EFAULT);
					else
					{
						Dz1Thread_printf("bin size = %u\n", bin->size);
						if ((*errp = Dz1BinFile_savef(bin, fp)).code) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
			}
			pthread_cleanup_pop(1); // ((Dz1DelFunc)fclose, (void *)fp);
		}
	}
	return err;
}

bool_t Dz1MdefcModule_isUnknownExist(Dz1MdefcModule *p)
{
	bool_t ret = FALSE;
	if (Dz1AATree_count(p->objUnknown) > 0) return TRUE;
	return ret;
}

static bool_t isTdcExt(str_t ext)
{
	bool_t ret = TRUE;

	if (ext[0] != 0 && ext[1] != 0 && ext[2] != 0 && ext[3] == 0)
	{	// 세글자면?
		if (ext[0] != 'T' && ext[0] != 't') ret = FALSE;
		else if (ext[1] != 'D' && ext[1] != 'd') ret = FALSE;
		else if (ext[2] != 'C' && ext[2] != 'c') ret = FALSE;
	}
	else ret = FALSE;
	return ret;
}

static Dz1Error chk_struct_member(void *ptr, StructMemberEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *origin = ObjectInfo_getOrigin(p->type);
	if (origin->type == ObjectType_array)
	{
		Dz1MdefcModule *module = (Dz1MdefcModule *)ptr;
		if (isTdcExt(module->ext) == TRUE)
		{	// TDC이면?
			// Dz1Thread_printf("@@@ TDC Structure member %s is Array(arg=%d, ref=%d, ao=%u)\n",
			//				p->instance, p->argInvolve, p->isReferenced, p->isAsnOptional);
			// if (p->argInvolve == FALSE && p->isReferenced == TRUE)
//			if (p->argInvolve == FALSE && StructMemberEntry_isReferenced(p) == TRUE)
			if (StructMemberEntry_isArgInvolve(p) == FALSE && StructMemberEntry_isReferenced(p) == TRUE)
			{	// notarg, ref
				// Dz1Thread_printf("@@@ TDC Structure member set ASN_OPTIONAL to %s\n", p->instance);
//				p->isAsnOptional = TRUE;
				p->memb_flags |= MEMBER_FLAG_ASN_OPTIONAL;
			}
		}
	}
	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _findDefinedAndFixupEnum(void *ptr, void *_p)
{
	Dz1MdefcModule *module = (Dz1MdefcModule *)ptr;

	ObjectInfo *p = (ObjectInfo *)_p;
	DZ1_ERROR_SAFE_VAR(errp, err);

	ObjectInfo *origin = ObjectInfo_getOrigin(p);
	if (p->type == ObjectType_defined && origin->type == ObjectType_enumerate)
	{
//		DefinedInfo *defined = (DefinedInfo *)p->info;
//		p->info = NULL;
		EnumInfo *enum_info = EnumInfo_clone(origin->info, errp);
		if (enum_info == NULL) ERR_OUT(errp);
		else
		{
			p->api = origin->api;
			DefinedInfo_delAndSetNull(&p->info);
			p->info = enum_info;
			p->type = origin->type;
		}
	}
	else if (origin->type == ObjectType_structure)
	{
		StructureInfo *struct_info = (StructureInfo *)origin->info;
		if ((*errp = struct_info->members->travel(struct_info->members, chk_struct_member, (void *)module)).code) ERR_OUT(errp);
	}
	return err;
}

Dz1Error Dz1MdefcModule_fixupDefinedEnums(Dz1MdefcModule *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1AATree_travel(p->objTree, _findDefinedAndFixupEnum, (void *)p)).code) ERR_OUT(errp);
	return err;
}





















static void _print_include(FILE *fp, Dz1MdefcModule *p, bool_t flag)
{
	if (p->includeStatus == ModuleIncludeStatus_included)
		Dz1Thread_ftprintf(fp, 1, "include %s;\n", p->name);
}

static Dz1Error _Dz1MdefcModule_tdcInclude(void *ptr, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_print_include((FILE *)ptr, (Dz1MdefcModule *)data, FALSE);
	return err;
}

/*
#define OBJECT_API_DUMP						0x08000000
#define OBJECT_API_FDUMP					0x01000000
#define OBJECT_API_USER_DUMP				0x00800000
#define OBJECT_API_USER_FDUMP				0x00400000
#define OBJECT_API_CMP						0x04000000
#define OBJECT_API_CLONE					0x10000000
#define OBJECT_API_CODEC					0x02000000
*/

typedef struct ApiNameMap
{
	u32_t v;
	str_t name;
} ApiNameMap;
static ApiNameMap apiNameMap [] = 
{
	{ OBJECT_API_DUMP, "dump" },
	{ OBJECT_API_FDUMP, "fdump" },
	{ OBJECT_API_USER_DUMP, "userdump" },
	{ OBJECT_API_USER_FDUMP, "userfdump" },
	{ OBJECT_API_CMP, "compare" },
	{ OBJECT_API_CLONE, "clone" },
#ifdef USE_CODEC
	{ OBJECT_API_CODEC, "codec" },
#endif
	{ OBJECT_API_NONE }
};

#define API_BASE_STRING	"\t// with api "
static ssize_t _getApiStr(char buf[1024], u32_t api)
{
	char *cp = buf;
	if (api != OBJECT_API_NONE)
	{
		bool_t prev = FALSE;
		ApiNameMap *i;
		strcpy(cp, API_BASE_STRING);
		cp += strlen(API_BASE_STRING);
		for (i = apiNameMap; i->v != OBJECT_API_NONE; i++)
		{
			if (api & i->v)
			{
				if (prev)
				{
					*cp++ = ',';
					*cp++ = ' ';
				} else prev = TRUE;
				strcpy(cp, i->name);
				cp += strlen(i->name);
			}
		}
	}
	*cp = '\0';
	return (ssize_t)(cp - buf);
}

static void DefinedInfo_tdc(FILE *fp, ObjectInfo *p, PublishSpec *sp, int tab)
{
	DefinedInfo *info = (DefinedInfo *)p->info;
	ObjectInfo *origin = info->origin;
	char apiStr[1024];
	u32_t api = p->api == OBJECT_API_NONE ? ObjectInfo_apiOf(p, sp) : p->api;
	_getApiStr(apiStr, api);

	Dz1Thread_ftprintf(fp, tab, "typedef %s%s %s;%s\n\n", info->isForwarded ? "struct " : "", origin->name, p->name, apiStr);
}

static void EnumEntry_tdc(FILE *fp, str_t prefix, EnumEntry *p, bool_t isLast, int tab)
{
	//                           1 2 3 4
	Dz1Thread_ftprintf(fp, tab, "%s%s%s%s\n",
					p->name,
					p->valStr ? " = " : "",
					p->valStr ? p->valStr : "",
					isLast ? "" : ",");
}

static void EnumList_tdc(FILE *fp, str_t prefix, EnumList *p, int tab)
{
	EnumEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			e = (EnumEntry *)Dz1FifoCursor_data(c);
			EnumEntry_tdc(fp, prefix, e, Dz1FifoCursor_isLast(c), tab);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}

static void EnumInfo_tdc(FILE *fp, ObjectInfo *p, PublishSpec *sp, int tab)
{
	EnumInfo *info = (EnumInfo *)p->info;

	if (info->isGenerated == FALSE)
	{
		char apiStr[1024];
		u32_t api = p->api == OBJECT_API_NONE ? ObjectInfo_apiOf(p, sp) : p->api;
		_getApiStr(apiStr, api);

		Dz1Thread_ftprintf(fp, tab, "typedef enum %s\n", p->name);
		Dz1Thread_ftprintf(fp, tab++, "{\n");
		EnumList_tdc(fp, p->name, info->enums, tab);
		Dz1Thread_ftprintf(fp, --tab, "} %s;%s\n\n", p->name, apiStr);
	}
}

static __inline__ str_t tdcForwardCaster(int type)
{
	if (type == FORWARD_TYPE_NONE) return "";
	else if (type == FORWARD_TYPE_STRUCT) return "struct ";
	else if (type == FORWARD_TYPE_UNION) return "union ";
	else if (type == FORWARD_TYPE_ENUM) return "enum ";
	else
	{
		printf("forwardCaster() : type = %d\n", type);
		return "#error !!forwardCaster!! ";
	}
}

#define OPT_STR_BASE	"\t// is "
#define OPT_STR_CHK_BASE(base, cp)		do { if ((base) == FALSE) { strcpy(cp, OPT_STR_BASE); cp += strlen(OPT_STR_BASE); (base) = TRUE; } } while(0)
#define STR_CAT_AND_MOVE(cp, str, prev)			do { if ((prev) == FALSE) (prev) = TRUE; else { *cp++ = ','; *cp++ = ' '; } strcpy(cp, str); cp += strlen(str); } while(0)

static ssize_t _getStructMemberOptStr(char buf[1024], StructMemberEntry *p)
{
	char *cp = buf;
	bool_t base = FALSE;
	bool_t prev = FALSE;

	buf[0] = '\0';

//	if (p->argInvolve == FALSE)			// TRUE="", FALSE="notarg"
	if (StructMemberEntry_isArgInvolve(p) == FALSE)	// TRUE="", FALSE="notarg"
	{
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "notarg", prev);
	}

//	if (p->isIndex)				// TRUE="key", FALSE=""
	if (StructMemberEntry_isIndex(p))				// TRUE="key", FALSE=""
	{
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "key", prev);
	}
	
//	if (p->isReferenced)		// TRUE="ref", FALSE=""
	if (StructMemberEntry_isReferenced(p))
	{
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "ref", prev);
	}

	switch(p->dumpMode)
	{
	case MemberDumpMode_normal:
		break;
	case MemberDumpMode_value:
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "valdump", prev);
		break;
	case MemberDumpMode_omit:
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "nodump", prev);
		break;
	case MemberDumpMode_cascade:
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "cascadedump", prev);
		break;
	default:
		break;
	}

	prev = FALSE;
//	if (p->isAsnOptional)		// TRUE="-- ASN OPTIONAL", FALSE=""
	if (StructMemberEntry_isAsnOptional(p))	// TRUE="-- ASN OPTIONAL", FALSE=""
	{
		STR_CAT_AND_MOVE(cp, "\t-- ASN OPTIONAL", prev);
	}

	return (ssize_t)(cp - buf);
}

static void StructureMemberEntry_size(StructMemberEntry *p, size_t *type_len, size_t *instance_len)
{
	char temp[1024];
	size_t _tl;
	size_t _il = strlen(p->instance) + 1;

	sprintf(temp, "%s%s", tdcForwardCaster(p->isForwarded), p->type->name);
	_tl = strlen(temp);

	(*type_len) = (_tl > (*type_len) ? _tl : *type_len);
	(*instance_len) = (_il > (*instance_len) ? _il : *instance_len);
}

static void StructureMemberEntry_tdc(FILE *fp, str_t name, StructMemberEntry *p, size_t type_len, size_t instance_len, int tab)
{
	char optStr[1024], type[1024], fmt[1024];
	size_t _il = strlen(p->instance) + 1, pad = instance_len - _il;
	_getStructMemberOptStr(optStr, p);

	sprintf(type, "%s%s",tdcForwardCaster(p->isForwarded), p->type->name);

	// "%-14s %s%s"
	sprintf(fmt, "%%-%us %%s%%s;", (u32_t)type_len); // type, pointer, name
	TP(fp, tab); fprintf(fp, fmt, type, p->isPointer ? "*" : " ", p->instance);
	if (optStr[0] != '\0')
	{
		while(pad--) fprintf(fp, " ");
		fprintf(fp, "%s\n", optStr);
	}
	else fprintf(fp, "\n");
}

static void StructureMemberList_size(StructMemberList *p, size_t *tl, size_t *il)
{
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				StructureMemberEntry_size(e, tl, il);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}

static void StructureMemberList_tdc(FILE *fp, str_t name, StructMemberList *p, size_t tl, size_t il, int tab)
{
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				StructureMemberEntry_tdc(fp, name, e, tl, il, tab);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}

void StructureInfo_tdc(FILE *fp, u32_t api, str_t name, StructureInfo *p, int tab)
{
	bool_t printed = FALSE;

	size_t tl = 0, il = 0;

	char apiStr[1024];
	_getApiStr(apiStr, api);

	// Declare Structure
	TP(fp, tab); fprintf(fp, "typedef struct %s\n", name);
	TP(fp, tab++); fprintf(fp, "{\n");
	StructureMemberList_size(p->members, &tl, &il);
	StructureMemberList_tdc(fp, name, p->members, tl, il, tab);
	TP(fp, --tab); fprintf(fp, "} %s;%s\n\n", name, apiStr);

	// Declare New(M)

	if (printed) fprintf(fp, "\n");
}

///////////////////////////////////////////////////////////////////////////////
// Union Member Opt
static ssize_t _getUnionMemberOptStr(char buf[1024], UnionMemberEntry *p)
{
	char *cp = buf;
	bool_t base = FALSE;
	bool_t prev = FALSE;

//	if (p->isReferenced)						// TRUE="ref", FALSE=""
	if (UnionMemberEntry_isReferenced(p))		// TRUE="ref", FALSE=""
	{
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "ref", prev);
	}

	switch(p->dumpMode)
	{
	case MemberDumpMode_normal:
		break;
	case MemberDumpMode_value:
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "valdump", prev);
		break;
	case MemberDumpMode_omit:
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "nodump", prev);
		break;
	case MemberDumpMode_cascade:
		OPT_STR_CHK_BASE(base, cp);
		STR_CAT_AND_MOVE(cp, "cascadedump", prev);
		break;
	default:
		break;
	}
	*cp = '\0';
	return (ssize_t)(cp - buf);
}
// Union Member Opt
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member Present
static bool_t _needCotate(str_t str)
{
	bool_t found = FALSE;
	char *cp = str;
	while(*cp)
	{
		if (*cp == ' ')
		{
			found = TRUE;
			break;
		}
		cp++;
	}

	if (found)
	{
		cp++;
		if (*cp && *cp != ' ') return TRUE;
	}
	return FALSE;
}

static void _getUnionMemberPresentStr(char dst[1024], UnionMemberEntry *p)
{
	char *cp = dst;
	if (p->presentStr != NULL && p->presentStr[0] != 0)
	{
		*cp++ = '[';
		if (_needCotate(p->presentStr))
		{
			*cp++ = '\"';
			strcpy(cp, p->presentStr); cp += strlen(p->presentStr);
			*cp++ = '\"';
		}
		else strcpy(cp, p->presentStr);
		*cp++ = ']';
	}
	*cp = 0;
}
// Union Member Present
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member
static void UnionMemberEntry_tdc(FILE *fp, UnionMemberEntry *p, size_t type_len, size_t present_len, size_t instance_len, int tab)
{
	char presentStr[1024];
	char optStr[1024], type[1024], fmt[1024];

	size_t _il = strlen(p->instance) + 1, pad = instance_len - _il;

	sprintf(type, "%s%s",tdcForwardCaster(p->isForwarded), p->type->name);
	_getUnionMemberOptStr(optStr, p);

	if (present_len == 0)
	{
		// "%-14s %s%s"
		sprintf(fmt, "%%-%us %%s%%s;", (u32_t)type_len); // type, pointer, name
		TP(fp, tab); fprintf(fp, fmt, type, p->isPointer ? "*" : " ", p->instance);
	}
	else
	{
		_getUnionMemberPresentStr(presentStr, p);

		// "%-14s %s%s"
		sprintf(fmt, "%%-%us %%-%us %%s%%s;", (u32_t)type_len, (u32_t)present_len); // type, present, pointer, name
		TP(fp, tab); fprintf(fp, fmt, type, presentStr, p->isPointer ? "*" : " ", p->instance);

		//                        1 2 3 4 5  6
// 		TP(fp, tab); fprintf(fp, "%s%s%s%s%s;%s\n",
// 							tdcForwardCaster(p->isForwarded),			// 1. struct | union
// 							p->type->name,								// 2. typename
// 							presentStr,									// 3. " [xxx..]" | ""
// 							p->isPointer ? " *" : " ",					// 4. pointer
// 							p->instance, optStr);						// 5. instance name + 6. opt
	}
	if (optStr[0] != '\0')
	{
		while(pad--) fprintf(fp, " ");
		fprintf(fp, "%s\n", optStr);
	}
	else fprintf(fp, "\n");
}

static void UnionMemberList_loop(FILE *fp, UnionMemberList *p,
								 size_t type_len, size_t present_len, size_t instance_len, int tab,
								 void (*func)(FILE *fp, UnionMemberEntry *p, size_t type_len, size_t present_len, size_t instance_len, int tab))
{
	UnionMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				func(fp, e, type_len, present_len, instance_len, tab);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}
// Union Member
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member Size Calculate
static void UnionMemberEntry_size(UnionMemberEntry *p, size_t *type_len, size_t *present_len, size_t *instance_len)
{
	char temp[1024];
	size_t _tl;
	size_t _pl = 0;
	size_t _il = strlen(p->instance) + 1;

	sprintf(temp, "%s%s", tdcForwardCaster(p->isForwarded), p->type->name);
	_tl = strlen(temp);

	_getUnionMemberPresentStr(temp, p);
	_pl = strlen(temp);

	(*type_len) = (_tl > (*type_len) ? _tl : *type_len);
	(*present_len) = (_pl > (*present_len) ? _pl : *present_len);
	(*instance_len) = (_il > (*instance_len) ? _il : *instance_len);
}

static void UnionMemberList_size(UnionMemberList *p, size_t *type_len, size_t *present_len, size_t *instance_len)
{
	UnionMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				UnionMemberEntry_size(e, type_len, present_len, instance_len);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}
// Union Member Size Calculate
///////////////////////////////////////////////////////////////////////////////


static void UnionMemberList_tdc(FILE *fp, UnionMemberList *p, int tab)
{
	size_t type_len = 0, present_len = 0, instance_len = 0;
	UnionMemberList_size(p, &type_len, &present_len, &instance_len);
	UnionMemberList_loop(fp, p, type_len, present_len, instance_len, tab, UnionMemberEntry_tdc);
}

static void UnionInfo_tdc(FILE *fp, u32_t api, str_t name, UnionInfo *p, int tab)
{
	char apiStr[1024];
	_getApiStr(apiStr, api);

	TP(fp, tab); fprintf(fp, "typedef union %s\n", name);
	TP(fp, tab++); fprintf(fp, "{\n");
	UnionMemberList_tdc(fp, p->members, tab);
	TP(fp, --tab); fprintf(fp, "} %s;%s\n\n", name, apiStr);
}

static str_t _getArrayModeStr(ArrayType type)
{
	str_t ret = NULL;
	switch(type)
	{
	default:
	case ArrayType_normal:
		ret = "array";
		break;
	case ArrayType_ordered:
		ret = "ordered table";
		break;
	case ArrayType_unique:
		ret = "unique table";
		break;
	}
	return ret;
}

typedef struct ArrApiMap
{
	u32_t v;
	str_t name;
} ArrApiMap;
static ArrApiMap arrApiMap[] =
{
	{ ARRAY_API_REMOVE, "remove" },
	{ ARRAY_API_EXTRACT, "extract" },
	{ ARRAY_API_FIND, "find" },
	{ ARRAY_API_GETHEAD, "gethead" },
	{ ARRAY_API_GETTAIL, "gettail" },
	{ ARRAY_API_COUNT, "count" },
	{ 0 }
};

static ssize_t _getArrayApiStr(char buf[1024], u32_t api)
{
	char *cp = buf;
	bool_t prev = FALSE;
	ArrApiMap *i;
	if (api & 0x3Fffffff)
	{
		*cp++ = '(';
		for (i = arrApiMap; i->v != 0; i++)
		{
			if (api & i->v)
			{
				if (prev)
				{
					*cp++ = ',';
					*cp++ = ' ';
				}
				else prev = TRUE;
				strcpy(cp, i->name); cp += strlen(i->name);
			}
		}
		*cp++ = ')';
	}
	*cp = '\0';
	return (ssize_t)(cp - buf);
}

void ArrayInfo_tdc(FILE *fp, u32_t api, str_t name, ArrayInfo *p, int tab)
{
	char arrayApiStr[1024];
	_getArrayApiStr(arrayApiStr, p->arrayApi);
	// Structure Declare              1  2 3   4 5
	TP(fp, tab); fprintf(fp, "typedef %s %s%s [%s%s%s];\n\n",
						_getArrayModeStr(p->type),
						name,
						arrayApiStr,				// (find, extract, ...)
						p->isReferenced ? "&" : "",
						tdcForwardCaster(p->isForward),
						p->entry->name);
}

static void ExternInfo_tdc(FILE *fp, u32_t api, str_t name, ExternInfo *info, int tab)
{
	char nativePrefixStr[1024];
	char apiStr[1024];
	_getApiStr(apiStr, api);

	if (info->prefix != NULL)
		sprintf(nativePrefixStr, " with prefix %s", info->prefix);
	else nativePrefixStr[0] = '\0';

	//                                          1 2 3       4  5
	Dz1Thread_ftprintf(fp, tab, "typedef native %s%s%s from %s;%s\n\n",
		info->isStatic ? "static " : "",
		name,
		nativePrefixStr,
		info->module_name,
		apiStr);
}

static void Reference_tdc(FILE *fp, u32_t api, str_t name, ExternInfo *info, int tab)
{
	char nativePrefixStr[1024];
	char apiStr[1024];
	_getApiStr(apiStr, api);

	if (info->prefix != NULL)
		sprintf(nativePrefixStr, " with prefix %s", info->prefix);
	else nativePrefixStr[0] = '\0';

	//                                             1 2 3       4  5
	Dz1Thread_ftprintf(fp, tab, "typedef reference %s%s%s from %s;%s\n\n",
		info->isStatic ? "static " : "",
		name,
		nativePrefixStr,
		info->module_name,
		apiStr);
}

static void FunctionInfoArg_tdc(FILE *fp, FunctionArg *p, bool_t isFirst, bool_t nl, int tab)
{
	if (!isFirst) fprintf(fp, ", ");
	if (nl) { fprintf(fp, "\n"); TP(fp, tab); }
	fprintf(fp, "%s%s ", tdcForwardCaster(p->argForward),
						p->argType->name);
	if (p->argPtrCnt)
	{
		int cnt = p->argPtrCnt;
		while(cnt--) fprintf(fp, "*");
	}
	if (p->instance) fprintf(fp, "%s", p->instance);
}

static void FunctionArgs_tdc(FILE *fp, FunctionArgs *args, int tab)
{
	bool_t isFirst = FALSE;
	bool_t nl = FALSE;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	FunctionArg *arg = NULL;
	void *cursor = Dz1FifoCursor_new(args->list, &err);

	if (args->count(args) > 3) nl = TRUE;

	for (Dz1FifoCursorForward(cursor))
	{
		if ((arg = (FunctionArg *)Dz1FifoCursor_data(cursor)) == NULL) ERR_SET_OUT(&err, EFAULT);
		else FunctionInfoArg_tdc(fp, arg, isFirst, nl, tab + 5);
		isFirst = FALSE;
	}
}

static void FunctionInfo_tdc(FILE *fp, u32_t api, str_t name, FunctionInfo *info, int tab)
{
	//                                        1 2  3 4
	Dz1Thread_ftprintf(fp, tab, "typedef func %s%s %s%s(",
						tdcForwardCaster(info->retForward),
						info->retType->name,
						info->retIsPointer ? "*" : "",
						name);
	FunctionArgs_tdc(fp, info->args, tab);
	Dz1Thread_fprintf(fp, ");\n\n");
}

static void ObjectInfo_tdc(FILE *fp, ObjectInfo *p, PublishSpec *sp, int tab)
{
	switch(p->type)
	{
		case ObjectType_defined:
			DefinedInfo_tdc(fp, p, sp, tab);
			break;
		case ObjectType_enumerate:
			EnumInfo_tdc(fp, p, sp, tab);
			break;
#if 0
		case ObjectType_bits:
			BitsInfo_header(fp, spec, ObjectInfo_apiOf(p), p->name, (BitsInfo *)p->info, tab);
			break;
#endif
		case ObjectType_structure:
			StructureInfo_tdc(fp, ObjectInfo_apiOf(p, sp), p->name, (StructureInfo *)p->info, tab);
			break;
		case ObjectType_union:
			UnionInfo_tdc(fp, ObjectInfo_apiOf(p, sp), p->name, (UnionInfo *)p->info, tab);
			break;
		case ObjectType_array:
			ArrayInfo_tdc(fp, ObjectInfo_apiOf(p, sp), p->name, (ArrayInfo *)p->info, tab);
			break;
		case ObjectType_extern:
			ExternInfo_tdc(fp, ObjectInfo_apiOf(p, sp), p->name, (ExternInfo *)p->info, tab);
			break;
		case ObjectType_reference:
			Reference_tdc(fp, ObjectInfo_apiOf(p, sp), p->name, (ExternInfo *)p->info, tab);
			break;
		case ObjectType_declare:
			TP(fp, tab); fprintf(fp, "struct %s;\n\n", p->name);
			break;
		case ObjectType_func:
			FunctionInfo_tdc(fp, OBJECT_API_NONE, p->name, (FunctionInfo *)p->info, tab);
			break;
		default:
			break;
	}
}

static void ObjectInfoList_emit(FILE *fp, void *fifo, PublishSpec *sp, void (*emit)(FILE *fp, ObjectInfo *p, PublishSpec *sp, int tab))
{
	ObjectInfo *e = NULL;
	void *c = Dz1FifoCursor_new(fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (ObjectInfo *)Dz1FifoCursor_data(c)) != NULL)
				emit(fp, e, sp, 1);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}

static void ObjectInfoList_tdc(FILE *fp, void *fifo, PublishSpec *sp) { ObjectInfoList_emit(fp, fifo, sp, ObjectInfo_tdc); }

static str_t mkBaseName(char dst[1024], char *src)
{
	int len = (int)strlen(src), size = 0;
	char *cp = src + len - 1;
	if (*cp == DIR_SEP) cp--;
	while(cp >= src && *cp != DIR_SEP) { cp--; size++; }
	cp++;
	memcpy(dst, cp, size);
	dst[size] = '\0';
	return dst;
}

void Dz1MdefcModule_tdc(FILE *fp, Dz1MdefcModule *module, PublishSpec *sp)
{
	char basename[1024];
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	mkBaseName(basename, module->name);

	fprintf(fp, "message set definition {\n");

	if ((err = Dz1AATree_travel(module->moduleTree, _Dz1MdefcModule_tdcInclude, (void *)fp)).code) ERR_OUT(&err);

	fprintf(fp, "\n");

	ObjectInfoList_tdc(fp, module->objFifo, sp);

	fprintf(fp, "}\n");
}

