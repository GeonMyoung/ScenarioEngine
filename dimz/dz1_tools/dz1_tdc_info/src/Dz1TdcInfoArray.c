#include <dz1_codec.h>

#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>

#include "Dz1TdcInfoModule.h"
#include "Dz1TdcInfoObject.h"
#include "Dz1TdcInfoArray.h"

ArrayInfo *ArrayInfo_new(u32_t arrayApi, ObjectInfo *entry, str_t entrySrcType, bool_t isReferenced, FORWARD_TYPE isForward, ArrayType type, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ArrayInfo *ret = (ArrayInfo *)Dz1Calloc(sizeof(ArrayInfo), 1, errp);
	if (ret == NULL) { }
	else
	{
		pthread_cleanup_push(ArrayInfo_delAndSetNull, (void *)&ret);
		if (entrySrcType && (ret->entrySrcType = Dz1Str_dup(entrySrcType, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->arrayApi = arrayApi;
			ret->entry = entry;
			ret->isReferenced = isReferenced;
			ret->isForward = isForward;
			ret->type = type;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (ArrayInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ArrayInfo_del(ArrayInfo *p)
{
	if (!p) return;
	Dz1Str_delAndSetNull(&p->entrySrcType);
	Dz1Str_delAndSetNull(&p->dumpPrefix);
	Dz1Free(p);
}

static struct ArrayTypeMap
{
	ArrayType type;
	str_t name;
} ArrayTypeMap[] =
{
	{ ArrayType_normal, "Normal" },
	{ ArrayType_ordered, "Ordered" },
	{ ArrayType_ordered, "Unique" },
	{ (ArrayType)-1, "Unknown" }
};

str_t ArrayTypeStr(ArrayType type)
{
	struct ArrayTypeMap *i;
	for (i = ArrayTypeMap; i->type != -1; i++)
		if (i->type == type) break;
	return i->name;
}

void ArrayInfo_dump(ArrayInfo *p, int tab)
{
	if (!p) return;
	else
	{
		str_t dumpPrefix = Dz1Str_isVoid(p->dumpPrefix) ? "" : p->dumpPrefix;
		Dz1Thread_tprintf(tab, "(%08X) [%s%s%s] <%s> \"%s\"\n",
								p->arrayApi,
								p->isReferenced ? "&" : "",
								p->isForward ? "struct " : "",
								p->entry ? p->entry->name : "(none)",
								ArrayTypeStr(p->type), dumpPrefix);
	}
}

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo CODEC API
void *ArrayInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ArrayInfo *ret = ArrayInfo_new(0, NULL, NULL, FALSE, FALSE, (ArrayType)0, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t ArrayInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ArrayInfo *src = (ArrayInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, 0x00CAFE01, errp, ret);				// ArrayInfo Version
		DZ1_ENCODE4(cp, size, src->arrayApi, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, _put8str(cp, size, src->entry->name, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _put8str(cp, size, src->entrySrcType, errp), errp);
		DZ1_ENCODE1(cp, size, (u8_t)(src->isReferenced & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->isForward & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->type & 0xFF), errp, ret);
		if (src->dumpPrefix == NULL)
			DZ1_ENCODE1(cp, size, 0, errp, ret);
		else
		{
			DZ1_ENCODE1(cp, size, 1, errp, ret);
			DZ1_CODEC_FUNC(cp, size, ret, _put8str(cp, size, src->dumpPrefix, errp), errp);
		}
	}
	return ret;
}

typedef ssize_t (*ArrayInfoDecFunc)(ArrayInfo *dst, u8_t *src, size_t size, void *param, Dz1Error *err);
static ssize_t ArrayInfo_decV1(ArrayInfo *dst, u8_t *cp, size_t size, void *param, Dz1Error *errp)
{
	ssize_t ret = 0;

	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	str_t objName = NULL;
	u8_t v8;

	DZ1_DECODE4(&dst->arrayApi, cp, size, errp, ret);
	DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &objName, errp), errp);
	pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
	if ((dst->entry = module->findObject(module, objName)) == NULL)
	{
		if ((dst->entry = module->regUnknownObject(module, objName, errp)) == NULL) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);

	DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &dst->entrySrcType, errp), errp);
	DZ1_DECODE1(&v8, cp, size, errp, ret); dst->isReferenced = v8 ? TRUE : FALSE;
	DZ1_DECODE1(&v8, cp, size, errp, ret); dst->isForward= (FORWARD_TYPE)v8;
	DZ1_DECODE1(&v8, cp, size, errp, ret); dst->type = (ArrayType)v8;
	DZ1_DECODE1(&v8, cp, size, errp, ret);
	if (v8)
	{
		DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &dst->dumpPrefix, errp), errp);
		if (dst->dumpPrefix == NULL && (dst->dumpPrefix = Dz1Calloc(sizeof(char), 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
	}

	return ret;
}

static ArrayInfoDecFunc ArrayInfoDec[] =
{
	ArrayInfo_decV1
};
static u32_t ArrayInfoVer_max = sizeof(ArrayInfoDec) / sizeof(ArrayInfoDecFunc);

ssize_t ArrayInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ArrayInfo *dst = (ArrayInfo *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u32_t v32 = 0;
		u8_t *cp = src, v;
		DZ1_DECODE4(&v32, cp, size, errp, ret);
		if ((v32 & 0xFFFFFF00) == 0x00CAFE00)
		{	// version mode 
			u32_t ver = v32 & 0xFF;
			ArrayInfoDecFunc decoder = NULL;
			if (0 == ver || ver > ArrayInfoVer_max) ERR_SET_OUT_RET(errp, EFAULT, -1);
			else if ((decoder = ArrayInfoDec[ver - 1]) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
			else DZ1_CODEC_FUNC(cp, size, ret, decoder(dst, cp, size, param, errp), errp);
		}
		else
		{	// original version
			str_t objName = NULL;
			dst->arrayApi = v32;
			// Object
			DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &objName, errp), errp);
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
			if ((dst->entry = module->findObject(module, objName)) == NULL)
			{
				if ((dst->entry = module->regUnknownObject(module, objName, errp)) == NULL) ERR_OUT(errp);
			}
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);

			DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &dst->entrySrcType, errp), errp);
			DZ1_DECODE1(&v, cp, size, errp, ret); dst->isReferenced = v ? TRUE : FALSE;
			DZ1_DECODE1(&v, cp, size, errp, ret); dst->isForward= (FORWARD_TYPE)v;
			DZ1_DECODE1(&v, cp, size, errp, ret); dst->type = (ArrayType)v;
		}
	}
	return ret;
}
// ArrayInfo CODEC API
///////////////////////////////////////////////////////////////////////////////

Dz1Error IndexInfoKey_appendName(IndexInfoKey *p, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->valid < 64)
	{
		if ((p->names[p->valid] = Dz1StrA_dup(name, errp)) == NULL) ERR_OUT(errp);
		else p->valid++;
	}
	else ERR_SET_OUT(errp, ENOMEM);
	return err;
}

void IndexInfoKey_clear(IndexInfoKey *p)
{
	int i;
	for (i = 0; i < p->valid; i++)
	{
		Dz1StrA_del(p->names[i]);
		p->names[i] = 0;
	}
	p->valid = 0;
}

////////////////////////////////////////////////////////////////////////////////
// IndexInfo API
IndexInfo *IndexInfo_new(u32_t indexApi, ObjectInfo *entry, str_t entrySrcType,
						 bool_t isReferenced, FORWARD_TYPE isForward, bool_t indexUnique,
						 Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	IndexInfo *ret = (IndexInfo *)Dz1Calloc(sizeof(IndexInfo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IndexInfo_delAndSetNull, (void *)&ret);

		if (entrySrcType && (ret->entrySrcType = Dz1Str_dup(entrySrcType, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->indexApi = indexApi;
			ret->entry = entry;
			ret->isReferenced = isReferenced;
			ret->isForward = isForward;
			ret->indexUnique = indexUnique;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void IndexInfo_del(IndexInfo *p)
{
	if (!p) return;
	// Additional delete code here
	Dz1StrA_delAndSetNull(&p->entrySrcType);
	IndexInfoKey_clear(&p->keys);
	Dz1StrA_delAndSetNull(&p->dumpPrefix);
	Dz1Free(p);
}

void IndexInfo_dump(IndexInfo *p, int tab)
{
	if (!p) Dz1Thread_printf("NULL\n");
	else 
	{
		str_t prefix = p->dumpPrefix != NULL ? p->dumpPrefix : "entry = ";
		if (p->keys.valid == 0)
			//                        1     2  3 4 5     6
			Dz1Thread_tprintf(tab, "(%08X) %s[%s%s%s] \"%s\"\n",
									p->indexApi,							// 1
									p->indexUnique ? "unique" : "",			// 2
									p->isReferenced ? "&" : "",				// 3
									p->isForward ? "struct " : "",			// 4
									p->entry ? p->entry->name : "(none)",	// 5
									prefix);								// 6
		else
		{
			int i;
			IndexInfoKey *keys = &p->keys;
			Dz1Thread_tprintf(tab, "(%08X) %s[%s%s%s](",
									p->indexApi,							// 1
									p->indexUnique ? "unique" : "",			// 2
									p->isReferenced ? "&" : "",				// 3
									p->isForward ? "struct " : "",			// 4
									p->entry ? p->entry->name : "(none)");	// 5
			for (i = 0; i < keys->valid; i++)
			{
				if (i == 0) Dz1Thread_printf("%s", keys->names[i]);
				else Dz1Thread_printf(", %s", keys->names[i]);
			}
			Dz1Thread_printf(") \"%s\"\n", prefix);
		}
	}
}
// IndexInfo API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IndexInfoKey CODEC
static ssize_t IndexInfoKey_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	IndexInfoKey *src = (IndexInfoKey *)_src;
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		int i;
		u8_t *cp = dst;
		DZ1_ENCODE2(cp, size, src->valid & 0xFFFF, errp, ret);
		for (i = 0; i < src->valid; i++)
			DZ1_CODEC_FUNC(cp, size, ret, _put8str(cp, size, src->names[i], errp), errp);

	}
	return ret;
}

static ssize_t IndexInfoKey_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	IndexInfoKey *dst = (IndexInfoKey *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		int i;
		u8_t *cp = src;
		u16_t v16 = 0;
		DZ1_DECODE2(&v16, cp, size, errp, ret); dst->valid = (int)v16;
		for (i = 0; i < dst->valid; i++)
			DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &dst->names[i], errp), errp);
	}
	return ret;
}
// IndexInfoKey CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IndexInfo CODEC
IndexInfo *IndexInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	IndexInfo *ret = IndexInfo_new(0, NULL, NULL, FALSE, FALSE, FALSE, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t IndexInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	IndexInfo *src = (IndexInfo *)_src;
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, 0x00CAFE01, errp, ret);				// IndexInfo Version
		DZ1_ENCODE4(cp, size, src->indexApi, errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, _put8str(cp, size, src->entry->name, errp), errp);
		DZ1_CODEC_FUNC(cp, size, ret, _put8str(cp, size, src->entrySrcType, errp), errp);
		DZ1_ENCODE1(cp, size, (u8_t)(src->isReferenced & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->isForward & 0xFF), errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)(src->indexUnique & 0xFF), errp, ret);
		DZ1_CODEC_FUNC(cp, size, ret, IndexInfoKey_enc(cp, size, &src->keys, NULL, errp), errp);
		if (src->dumpPrefix == NULL)
			DZ1_ENCODE1(cp, size, 0, errp, ret);
		else
		{
			DZ1_ENCODE1(cp, size, 1, errp, ret);
			DZ1_CODEC_FUNC(cp, size, ret, _put8str(cp, size, src->dumpPrefix, errp), errp);
		}
	}
	return ret;
}

typedef ssize_t (*IndexInfoDecFunc)(IndexInfo *dst, u8_t *src, size_t size, void *param, Dz1Error *err);
static ssize_t IndexInfo_decV1(IndexInfo *dst, u8_t *cp, size_t size, void *param, Dz1Error *errp)
{
	ssize_t ret = 0;

	u8_t v8;
	str_t objName = NULL;
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;

	DZ1_DECODE4(&dst->indexApi, cp, size, errp, ret);
	// Object
	DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &objName, errp), errp);
	pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
	if ((dst->entry = module->findObject(module, objName)) == NULL)
	{
		if ((dst->entry = module->regUnknownObject(module, objName, errp)) == NULL) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);

	DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &dst->entrySrcType, errp), errp);
	DZ1_DECODE1(&v8, cp, size, errp, ret); dst->isReferenced = v8 ? TRUE : FALSE;
	DZ1_DECODE1(&v8, cp, size, errp, ret); dst->isForward= (FORWARD_TYPE)v8;
	DZ1_DECODE1(&v8, cp, size, errp, ret); dst->indexUnique = (ArrayType)v8;
	DZ1_CODEC_FUNC(cp, size, ret, IndexInfoKey_dec(&dst->keys, cp, size, NULL, errp), errp);
	DZ1_DECODE1(&v8, cp, size, errp, ret);
	if (v8)
	{
		DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &dst->dumpPrefix, errp), errp);
		if (dst->dumpPrefix == NULL && (dst->dumpPrefix = Dz1Calloc(sizeof(char), 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
	}
	return ret;
}

static IndexInfoDecFunc IndexInfoDec[] =
{
	IndexInfo_decV1
};
static u32_t IndexInfoVer_max = sizeof(IndexInfoDec) / sizeof(IndexInfoDecFunc);

ssize_t IndexInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	IndexInfo *dst = (IndexInfo *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u32_t v32 = 0;
		u8_t *cp = src, v;
		DZ1_DECODE4(&v32, cp, size, errp, ret);
		if ((v32 & 0xFFFFFF00) == 0x00CAFE00)
		{	// version mode 
			u32_t ver = v32 & 0xFF;
			IndexInfoDecFunc decoder = NULL;
			if (0 == ver || ver > IndexInfoVer_max) ERR_SET_OUT_RET(errp, EFAULT, -1);
			else if ((decoder = IndexInfoDec[ver - 1]) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
			else DZ1_CODEC_FUNC(cp, size, ret, decoder(dst, cp, size, param, errp), errp);
		}
		else
		{	// original version
			str_t objName = NULL;
			dst->indexApi = v32;
			// Object
			DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &objName, errp), errp);
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&objName);
			if ((dst->entry = module->findObject(module, objName)) == NULL)
			{
				if ((dst->entry = module->regUnknownObject(module, objName, errp)) == NULL) ERR_OUT(errp);
			}
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&objName);

			DZ1_CODEC_FUNC(cp, size, ret, _get8str(cp, size, &dst->entrySrcType, errp), errp);
			DZ1_DECODE1(&v, cp, size, errp, ret); dst->isReferenced = v ? TRUE : FALSE;
			DZ1_DECODE1(&v, cp, size, errp, ret); dst->isForward= (FORWARD_TYPE)v;
			DZ1_DECODE1(&v, cp, size, errp, ret); dst->indexUnique = (ArrayType)v;
			DZ1_CODEC_FUNC(cp, size, ret, IndexInfoKey_dec(&dst->keys, cp, size, NULL, errp), errp);
		}
	}
	return ret;
}
// IndexInfo CODEC
////////////////////////////////////////////////////////////////////////////////

