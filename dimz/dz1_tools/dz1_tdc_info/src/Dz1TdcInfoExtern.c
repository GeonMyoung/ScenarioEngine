#include <dz1_codec.h>
#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>

#include "Dz1TdcInfoExtern.h"

ExternInfo *ExternInfo_new(ExternInfoStatic isStatic, str_t prefix, str_t publish_name, str_t module_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ExternInfo *ret = (ExternInfo *)Dz1Calloc(sizeof(ExternInfo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ExternInfo_delAndSetNull, (void *)&ret);
		if		(prefix && (ret->prefix = Dz1Str_dup(prefix, errp)) == NULL) ERR_OUT(errp);
		else if (publish_name && (ret->publish_name = Dz1Str_dup(publish_name, errp)) == NULL) ERR_OUT(errp);
		else if (module_name && (ret->module_name = Dz1Str_dup(module_name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->isStatic = isStatic;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (ExternInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ExternInfo_del(ExternInfo *p)
{
	if (!p) return;
	Dz1Str_delAndSetNull(&p->prefix);
	Dz1Str_delAndSetNull(&p->publish_name);
	Dz1Str_delAndSetNull(&p->module_name);
	Dz1Free(p);
}

typedef struct ExternInfoStaticStrMapA
{
	ExternInfoStatic type;
	str_t name;
} ExternInfoStaticStrMapA;

static ExternInfoStaticStrMapA externInfoStaticStrMapA[] =
{
	{ ExternInfoStatic_primitive,		"simple" },
	{ ExternInfoStatic_primitive_ptr,	"simple" },
	{ ExternInfoStatic_typical_union,	"construct(union)" },
	{ ExternInfoStatic_construct,		"construct" },
	{ -1,								"unknown" }
};

static str_t ExternInfoStaticStrMapStrA(ExternInfoStatic v)
{
	ExternInfoStaticStrMapA *i;
	for (i = externInfoStaticStrMapA; i->type != (ExternInfoStatic)-1; i++)
		if (i->type == v) break;
	return i->name;
}

// typedef struct ExternInfoStaticStrMapW
// {
// 	ExternInfoStatic type;
// 	wstr_t name;
// } ExternInfoStaticStrMapW;
// 
// static ExternInfoStaticStrMapW externInfoStaticStrMapW[] =
// {
// 	{ ExternInfoStatic_primitive,		L"simple" },
// 	{ ExternInfoStatic_primitive_ptr,	L"simple" },
// 	{ ExternInfoStatic_typical_union,	L"construct(union)" },
// 	{ ExternInfoStatic_construct,		L"construct" },
// 	{ -1, NULL }
// };
// 
// static wstr_t ExternInfoStaticStrMapStrW(ExternInfoStatic v)
// {
// 	ExternInfoStaticStrMapW *i;
// 	for (i = externInfoStaticStrMapA; i->type != (ExternInfoStatic)-1; i++)
// 		if (i->type == v) break;
// 	return i->name;
// }

void ExternInfo_dump(ExternInfo *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "%s, Prefix = %s from %s\n", ExternInfoStaticStrMapStrA((ExternInfoStatic)p->isStatic), p->prefix, p->module_name);
}

////////////////////////////////////////////////////////////////////////////////
// ExternInfo CODEC
ExternInfo *ExternInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ExternInfo *ret = ExternInfo_new(FALSE, NULL, NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t ExternInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ExternInfo *src = (ExternInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE1(cp, size, (u8_t)(src->isStatic & 0xFF), errp, ret);

		DZ1_ENCODE1(cp, size, src->prefix ? 1 : 0, errp, ret);
		if (src->prefix) DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->prefix, errp), errp);

		DZ1_ENCODE1(cp, size, src->publish_name ? 1 : 0, errp, ret);
		if (src->publish_name) DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->publish_name, errp), errp);

		DZ1_ENCODE1(cp, size, src->module_name? 1 : 0, errp, ret);
		if (src->module_name) DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->module_name, errp), errp);
	}
	return ret;
}

ssize_t ExternInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ExternInfo *dst = (ExternInfo *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src, v;
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->isStatic = (ExternInfoStatic)v;

		DZ1_DECODE1(&v, cp, size, errp, ret);
		if (v) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->prefix, errp), errp);

		DZ1_DECODE1(&v, cp, size, errp, ret);
		if (v) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->publish_name, errp), errp);

		DZ1_DECODE1(&v, cp, size, errp, ret);
		if (v) DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->module_name, errp), errp);
	}
	return ret;
}
// ExternInfo CODEC
////////////////////////////////////////////////////////////////////////////////

