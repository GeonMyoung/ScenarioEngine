#include "sample_stream.h"
#include "sample_test.h"

typedef ssize_t (*DecF)(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
typedef ssize_t (*EncF)(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
typedef struct CodecTestApi
{
	str_t				 name;
	void				*(*def)(Dz1Error *err);
	Dz1GenFunc			 gen;
	Dz1DelFunc			 delAndSetNull;
	Dz1DumpFunc			 dump;
	EncF				 enc;
	DecF				 dec;
} CodecTestApi;
#define CodecTestApi_NULL		{ NULL, NULL, NULL }
#define CodecTestApi_isNULL(p)	Dz1Str_isVoid(p->name)
#define CodecTestApi_entry(name)	{ #name, name##_default, name##_gen, name##_delAndSetNull, name##_dump, name##_write, name##_read }

///////////////////////////////////////////////////////////////////////////////
// MyData
static MyData *MyData_generate(u32_t data1, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyData *ret = MyData_new(data1, 50, 250, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

static void *MyData_default(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyData *ret = MyData_generate(100, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
// MyData
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// StructSample
static StructSample *StructSample_generate(u32_t data1, u32_t *data5_data1, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StructSample *ret = StructSample_new(data1, 50, 250, EnumSample_value1, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else if (data5_data1 == NULL) Dz1Error_set(errp, 0);
	else
	{
		pthread_cleanup_push(StructSample_delAndSetNull, (void *)&ret);
		if ((ret->data5 = (MyData *)MyData_generate(*data5_data1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (StructSample_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void *StructSample_default(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t data5_data1 = 100;
	StructSample *ret = StructSample_generate(100, &data5_data1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
// StructSample
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// StructSampleList
static bool_t StructSampleList_append(StructSampleList *dst, u32_t data1, u32_t *data5_data1, Dz1Error *errp)
{
	StructSample *node = StructSample_generate(data1, data5_data1, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StructSample_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (StructSample_delAndSetNull, (void *)&node);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t StructSampleList_init(StructSampleList *dst, Dz1Error *errp)
{
	u32_t data5_data1 = 101;
	if (0) { }
	else if (StructSampleList_append(dst, 1, &data5_data1, errp) == FALSE) ERR_OUT(errp);
	else if (StructSampleList_append(dst, 2, &data5_data1, errp) == FALSE) ERR_OUT(errp);
	else if (StructSampleList_append(dst, 3, NULL, errp) == FALSE) ERR_OUT(errp);
	else if (StructSampleList_append(dst, 4, &data5_data1, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static void *StructSampleList_default(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StructSampleList *ret = StructSampleList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StructSampleList_delAndSetNull, (void *)&ret);
		if (StructSampleList_init(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (StructSampleList_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// StructSampleList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UnionSample
typedef struct UnionSampleAPI
{
	UnionSamplePresent	present;
	bool_t				(*init)(UnionSample *dst, u64_t v, Dz1Error *errp);
} UnionSampleAPI;
#define UnionSampleAPI_NULL				{ UnionSamplePresent_max, NULL }
#define UnionSampleAPI_isNULL(p)		((p)->present == UnionSamplePresent_max)

static bool_t UnionSample_data1_init(UnionSample *dst, u64_t v, Dz1Error *errp)
{
	if (dst->present != UnionSamplePresent_data1) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->x.data1 = (u32_t)(v & 0xFFFFFFFF);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t UnionSample_data2_init(UnionSample *dst, u64_t v, Dz1Error *errp)
{
	if (dst->present != UnionSamplePresent_data2) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->x.data2 = (u16_t)(v & 0xFFFF);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t UnionSample_data3_init(UnionSample *dst, u64_t v, Dz1Error *errp)
{
	if (dst->present != UnionSamplePresent_data3) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->x.data3 = (u8_t)(v & 0xFF);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t UnionSample_data4_init(UnionSample *dst, u64_t v, Dz1Error *errp)
{
	if (dst->present != UnionSamplePresent_data4) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->x.data4 = (EnumSample)v;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t UnionSample_data5_init(UnionSample *dst, u64_t v, Dz1Error *errp)
{
	if (dst->present != UnionSamplePresent_data5) ERR_SET_OUT(errp, EINVAL);
	else
	{
#if (__WORDSIZE == 32)
		MyData *data5 = (MyData *)(v & 0xFFFFFFFF);
#elif (__WORDSIZE == 64)
		MyData *data5 = (MyData *)v;
#else
#error Unknown __WORDSIZE
#endif
		if (data5 != NULL && (dst->x.data5 = MyData_clone(data5, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static UnionSampleAPI unionSampleAPI[] =
{
	{ UnionSamplePresent_data1, UnionSample_data1_init },
    { UnionSamplePresent_data2, UnionSample_data2_init },
    { UnionSamplePresent_data3, UnionSample_data3_init },
    { UnionSamplePresent_data4, UnionSample_data4_init },
    { UnionSamplePresent_data5, UnionSample_data5_init },
	UnionSampleAPI_NULL
};

static UnionSampleAPI *UnionSampleAPI_find(UnionSamplePresent present)
{
	UnionSampleAPI *i;
	for (i = unionSampleAPI; UnionSampleAPI_isNULL(i) == FALSE; i++)
		if (i->present == present) return i;
	return NULL;
}

static UnionSample *UnionSample_generate(UnionSamplePresent present, u64_t v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSample *ret = NULL;
	UnionSampleAPI *api = UnionSampleAPI_find(present);
	if (api == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((ret = UnionSample_new(present, NULL, errp)) == NULL) ERR_OUT(errp);
	else if (api->init == NULL) Dz1Error_set(errp, 0);
	else
	{
		pthread_cleanup_push(StructSampleList_delAndSetNull, (void *)&ret);
		if (api->init(ret, v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (StructSampleList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void *UnionSample_default(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSample *ret = UnionSample_generate(UnionSamplePresent_data2, 33, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
// UnionSample
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UnionSampleList
static bool_t UnionSampleList_append(UnionSampleList *dst, UnionSamplePresent present, u64_t v, Dz1Error *errp)
{
	UnionSample *node = UnionSample_generate(present, v, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(UnionSample_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (UnionSample_delAndSetNull, (void *)&node);
	}
	return ERR_IS_SUCCESS(errp);
}

static MyData samepl_data5 = { 1, 2, 3 };
static bool_t UnionSampleList_init(UnionSampleList *dst, Dz1Error *errp)
{
	if (0) { }
	else if (UnionSampleList_append(dst, UnionSamplePresent_data1, 101,						 errp) == FALSE) ERR_OUT(errp);
	else if (UnionSampleList_append(dst, UnionSamplePresent_data2, 102,						 errp) == FALSE) ERR_OUT(errp);
	else if (UnionSampleList_append(dst, UnionSamplePresent_data3, 103,						 errp) == FALSE) ERR_OUT(errp);
	else if (UnionSampleList_append(dst, UnionSamplePresent_data4, (u64_t)EnumSample_value2, errp) == FALSE) ERR_OUT(errp);
	else if (UnionSampleList_append(dst, UnionSamplePresent_data5, 0,						 errp) == FALSE) ERR_OUT(errp);
	else if (UnionSampleList_append(dst, UnionSamplePresent_data5, (u64_t)&samepl_data5,	 errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static void *UnionSampleList_default(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSampleList *ret = UnionSampleList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(UnionSampleList_delAndSetNull, (void *)&ret);
		if (UnionSampleList_init(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (UnionSampleList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

// UnionSampleList
///////////////////////////////////////////////////////////////////////////////
static CodecTestApi codecTestApi[] =
{
	CodecTestApi_entry(MyData),
	CodecTestApi_entry(StructSample),
	CodecTestApi_entry(StructSampleList),
	CodecTestApi_entry(UnionSample),
	CodecTestApi_entry(UnionSampleList),
	CodecTestApi_NULL
};

static CodecTestApi *CodecTestApi_findByName(str_t st_name)
{
	CodecTestApi *i;
	for (i = codecTestApi; CodecTestApi_isNULL(i) == FALSE; i++)
		if (strcmp(i->name, st_name) == 0) return i;
	return NULL;
}

static CodecTestApi *CodecTestApi_findByIdx(u32_t idx)
{
	u32_t sz = (sizeof(codecTestApi) / sizeof(CodecTestApi)) - 1;
	if (idx < sz) return &codecTestApi[idx];
	else return NULL;
}

static void CodecTestApi_dump(int tab)
{
	u32_t idx;
	CodecTestApi *i;
	for (idx = 1, i = codecTestApi; CodecTestApi_isNULL(i) == FALSE; i++, idx++)
		Dz1Thread_tprintf(tab, Dz1T("[%d] %s\n"), idx, i->name);
}

static Dz1Binary *sample_enc(CodecTestApi *api, bool_t verbose, Dz1Error *errp)
{
	Dz1Binary *ret = NULL;
	Dz1ElasticBuf *elb = NULL;
	if ((elb = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Stream *st = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		if ((st = Dz1Stream_openRefElasticBuf(elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			void *src = NULL;
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&st);
			if ((src = api->def(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz = 0;
				pthread_cleanup_push(api->delAndSetNull, (void *)&src);

				if (verbose) { Dz1Thread_printf(Dz1T("Srouce = ")); api->dump(src, 0); }

				if ((sz = api->enc(st, src, Dz1IOStreamEndian_big, NULL, errp)) < 0) ERR_OUT(errp);
				else if ((ret = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
				else
				{
					Dz1Error_set(errp, 0);
					if (verbose) { Dz1Thread_printf(Dz1T("Encoded = ")); Dz1Binary_dump(ret, 0); }
				}
				pthread_cleanup_pop(1); // (api->delAndSetNull, (void *)&src);
			}
			pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void *)&st);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return ret;
}

static void *sample_dec(Dz1Binary *src, CodecTestApi *api, bool_t verbose, Dz1Error *errp)
{
	void *ret = NULL;
	Dz1Stream *st = Dz1Stream_openStaticBuf(src->data, src->size, TRUE, src->size, errp);
	if (st == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&st);
		if ((ret = api->gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(api->delAndSetNull, (void *)&ret);
			if ((sz = api->dec(ret, st, Dz1IOStreamEndian_big, NULL, errp)) < 0) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				if (verbose)
				{
					Dz1Thread_printf(Dz1T("Decoded = ")); api->dump(ret, 0);
					if (src->size != (u32_t)sz) Dz1Thread_printf(Dz1T("decode size different : src = %u, consume = %d\n"), src->size, sz);
				}
			}
			pthread_cleanup_pop(errp->code); // (api->delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void *)&st);
	}
	return ret;
}

static bool_t sample_test(CodecTestApi *api, bool_t verbose, Dz1Error *errp)
{
	Dz1Binary *bin = NULL;
	if (verbose)
	{
		Dz1Thread_printf(Dz1T("================================================================================\n"));
		Dz1Thread_printf(Dz1T("=== %s Test\n"), api->name);
		Dz1Thread_printf(Dz1T("================================================================================\n"));
	}

	if ((bin = sample_enc(api, verbose, errp)) == NULL) ERR_OUT(errp);
	else
	{
		void *v = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		if ((v = sample_dec(bin, api, verbose, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(api->delAndSetNull, (void *)&v);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (api->delAndSetNull, (void *)&v);
		}

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}

	if (verbose)
		Dz1Thread_printf(Dz1T("================================================================================\n\n"));
	return ERR_IS_SUCCESS(errp);
}

bool_t sample_test_by_name(str_t name, bool_t verbose, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecTestApi *api = NULL;
	if (Dz1Str_isVoid(name)) ERR_SET_OUT(errp, EINVAL);
	else if ((api = CodecTestApi_findByName(name)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (sample_test(api, verbose, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

bool_t sample_test_by_idx(u32_t idx, bool_t verbose, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecTestApi *api = NULL;
	if ((api = CodecTestApi_findByIdx(idx)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (sample_test(api, verbose, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

void sample_test_dump(int tab) { CodecTestApi_dump(tab); }
