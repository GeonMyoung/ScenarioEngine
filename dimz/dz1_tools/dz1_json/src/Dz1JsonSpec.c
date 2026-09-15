#include <dz1_thread_stdio.h>
//#include <dz1_codec.h>
#include <dz1_base64.h>
#include <Dz1Json.h>
#include "Dz1JsonSpec.h"

static void _primitive_t_del(void *ptr)
{
	if (ptr != NULL) Dz1Free(ptr);
}

/*
static void *_primitive_t_gen(size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	if ((ret = Dz1Calloc(sz, 1, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
*/

static void *_primitive_clone(void *ptr, size_t sz, Dz1Error *errp)
{
	void *ret;
	if ((ret = Dz1Memory_clone(ptr, sz, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

static Dz1Str str_nul = Dz1Text("null");
static Dz1Str str_cotate = Dz1Text("\"");
bool_t Dz1JsonUtil_stringify_null(Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (_Dz1ElasticBuf_push(elb, (u8_t *)str_nul, sizeof(TCHAR) * 4, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _put_string(Dz1ElasticBuf *elb, Dz1Str v, Dz1Error *errp)
{
	TCHAR *cp = v;
	Dz1Str rslash = Dz1T("\\\\");
	Dz1Str tab = Dz1T("\\t");
	Dz1Str cr = Dz1T("\\n");
	Dz1Str lf = Dz1T("\\r");
	while(errp->code == 0 && *cp)
	{
		switch(*cp)
		{
		case Dz1T('\\'): if (_Dz1ElasticBuf_push(elb, (u8_t *)rslash, sizeof(TCHAR) * 2, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
		case Dz1T('\t'): if (_Dz1ElasticBuf_push(elb, (u8_t *)tab, sizeof(TCHAR) * 3, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
		case Dz1T('\n'): if (_Dz1ElasticBuf_push(elb, (u8_t *)cr, sizeof(TCHAR) * 3, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
		case Dz1T('\r'): if (_Dz1ElasticBuf_push(elb, (u8_t *)lf, sizeof(TCHAR) * 3, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
		default: if (_Dz1ElasticBuf_push(elb, (u8_t *)cp, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
		// modified by gm 20231020		-- type casting to second param in func-_Dz1ElasticBuf_push()
		}
		cp++;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1JsonUtil_stringify_quotstr(Dz1ElasticBuf *elb, Dz1Str v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) { }
	else if (_Dz1ElasticBuf_push(elb, (u8_t *)str_cotate, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp);
//	else if (_Dz1ElasticBuf_push(elb, (u8_t *)v, sizeof(TCHAR) * Dz1STRLEN(v), errp) == FALSE) ERR_OUT(errp);
	else if (_put_string(elb, v, errp) == FALSE) ERR_OUT(errp);
	else if (_Dz1ElasticBuf_push(elb, (u8_t *)str_cotate, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1JsonUtil_stringify_s32(Dz1ElasticBuf *elb, s32_t v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	TCHAR temp[64];
	Dz1SNPRINTF(temp, 63, Dz1Text("%d"), v);

	if (_Dz1ElasticBuf_push(elb, (u8_t *)temp, sizeof(TCHAR) * Dz1STRLEN(temp), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1JsonUtil_stringify_u32(Dz1ElasticBuf *elb, u32_t v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	TCHAR temp[64];
	Dz1SNPRINTF(temp, 63, Dz1Text("%u"), v);

	if (_Dz1ElasticBuf_push(elb, (u8_t *)temp, sizeof(TCHAR) * Dz1STRLEN(temp), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
///////////////////////////////////////////////////////////////////////////////
// real64_t
// static void *real64_t_gen(Dz1Error *err) { return _primitive_t_gen(sizeof(real64_t), err); }
bool_t Dz1Json_real64_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	real64_t v = Dz1Real64FromStr(tok->v);
	if ((dst->data = _primitive_clone(&v, sizeof(real64_t), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_real64_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		real64_t v = *(real64_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, Dz1Text("%.9f"), v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// real64_t
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// real32_t
// static void *real32_t_gen(Dz1Error *err) { return _primitive_t_gen(sizeof(real32_t), err); }
bool_t Dz1Json_real32_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	real32_t v = Dz1Real32FromStr(tok->v);
	if ((dst->data = _primitive_clone(&v, sizeof(real64_t), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_real32_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		real32_t v = *(real32_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, Dz1Text("%f"), v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_float_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	return Dz1Json_real32_t_load(dst, tok, err);
}

bool_t Dz1Json_float_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	return Dz1Json_real32_t_stringify(obj, elb, err);
}
// real32_t
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// u64_t
//static void *Dz1Json_u64_t_gen(Dz1Error *err) { return _primitive_t_gen(sizeof(u64_t), err); }
bool_t Dz1Json_u64_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u64_t v = Dz1StrTo64(tok->v);
	if ((dst->data = _primitive_clone(&v, sizeof(u64_t), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_u64_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		u64_t v = *(u64_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, DZ1_FMT64U, v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_s64_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		s64_t v = *(s64_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, DZ1_FMT64, v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// u64_t
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// u32_t
//static void *Dz1Json_u32_t_gen(Dz1Error *err) { return _primitive_t_gen(sizeof(u32_t), err); }
bool_t Dz1Json_u32_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t v = Dz1StrTo32(tok->v);
	if ((dst->data = _primitive_clone(&v, sizeof(u32_t), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_u32_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		u32_t v = *(u32_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, Dz1Text("%u"), v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_s32_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		s32_t v = *(s32_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, Dz1Text("%d"), v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// u32_t
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// u16_t
//static void *Dz1Json_u16_t_gen(Dz1Error *err) { return _primitive_t_gen(sizeof(u16_t), err); }
bool_t Dz1Json_u16_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u16_t v = (u16_t)(Dz1StrTo32(tok->v) & 0xFFFF);
	if ((dst->data = _primitive_clone(&v, sizeof(u16_t), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_u16_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		u16_t v = *(u16_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, Dz1Text("%u"), v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_s16_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		s16_t v = *(s16_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, Dz1Text("%d"), v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// u16_t
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// u8_t
//static void *Dz1Json_u8_t_gen(Dz1Error *err) { return _primitive_t_gen(sizeof(u8_t), err); }
bool_t Dz1Json_u8_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u8_t v = (u8_t)(Dz1StrTo32(tok->v) & 0xFF);
	if ((dst->data = _primitive_clone(&v, sizeof(u8_t), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_u8_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		u8_t v = *(u8_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, Dz1Text("%u"), v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_s8_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		s8_t v = *(s8_t *)obj;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, Dz1Text("%d"), v);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// u8_t
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// bool_t
bool_t Dz1Json_bool_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	bool_t v;
	if (Dz1STRCMP(tok->v, Dz1Text("true")) == 0) v = TRUE;
	else if (Dz1STRCMP(tok->v, Dz1Text("false")) == 0) v = FALSE;
	else ERR_SET_OUT(errp, EINVAL);

	if (errp->code == 0)
	{
		if ((dst->data = _primitive_clone(&v, sizeof(bool_t), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_bool_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		bool_t val = *(bool_t *)obj;
		Dz1Str str = val ? Dz1Text("true") : Dz1Text("false");
		size_t len = val ? 4 : 5;
		if (_Dz1ElasticBuf_push(elb, (u8_t *)str, sizeof(TCHAR) * len, errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// bool_t
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// time_t
static time_t Dz1Time_parse(Dz1Str str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	time_t ret = 0;
	ERR_SET_OUT(errp, ENOSYS);

	return ret;
}

bool_t Dz1Json_time_t_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	time_t v;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (time_t)Dz1StrTo64(tok->v);
		Dz1Error_set(errp, 0);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Dz1Time_parse(tok->v, errp)) == 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	case Dz1JsonTokenType_nul:
		v = 0;
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}

	if (errp->code == 0)
	{
		if ((dst->data = _primitive_clone(&v, sizeof(time_t), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_time_t_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	time_t val;
	if (obj == NULL || (val = *(time_t *)obj) == 0)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		s64_t val64 = (s64_t)val;
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, DZ1_FMT64, val64);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// time_t
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// void
bool_t Dz1Json_void_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	dst->data = NULL;

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_void_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// void
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1IPv4
static u8_t _str_to_8(TCHAR *startp, TCHAR *limitp)
{
	TCHAR temp[8] = { 0, }, *dp = temp;
	while(startp < limitp)
		*dp++ = *startp++;
	return (u8_t)(Dz1StrTo32(temp) & 0xFF);
}

static bool_t _Dz1IPv4_load(Dz1IPv4 *dst, Dz1JsonToken *tok, Dz1Error *errp)
{
	if (tok->t == Dz1JsonTokenType_string)
	{	// ipstring:"192.168.1.1"
		Dz1IPv4 temp = 0;
		u32_t cnt = 0;
		TCHAR *cp = tok->v, *np = tok->v;
		while(Dz1STRCHR(cp, Dz1Text('.')) != NULL)
		{	// np~cp
			cnt++;
			temp = (temp << 8) | _str_to_8(np, cp);
			cp++;
			np = cp;
		}
		if (cnt != 3) ERR_SET_OUT(errp, EPERM);
		else temp = (temp << 8) | _str_to_8(np, cp);
		(*dst) = temp;
	}
	else if (tok->t == Dz1JsonTokenType_number)
	{
		(*dst) =Dz1StrTo32(tok->v);
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_Dz1IPv4_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1IPv4 temp = 0;
	if (_Dz1IPv4_load(&temp, tok, errp) == FALSE) ERR_OUT(errp);
	else if ((dst->data = _primitive_clone(&temp, sizeof(Dz1IPv4), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
bool_t Dz1Json_Dz1IPv4_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Dz1IPv4 v = *(Dz1IPv4 *)obj;
		u8_t a = (u8_t)((v >> 24) & 0xFF);
		u8_t b = (u8_t)((v >> 16) & 0xFF);
		u8_t c = (u8_t)((v >> 8) & 0xFF);
		u8_t d = (u8_t)((v >> 0) & 0xFF);
		TCHAR buf[64];
		Dz1SNPRINTF(buf, 64, Dz1Text("\"%d.%d.%d.%d\""), a,b,c,d);
		if (_Dz1ElasticBuf_push(elb, (u8_t *)buf, sizeof(TCHAR) * Dz1STRLEN(buf), errp) == FALSE) ERR_OUT(errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1IPv4
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Str
bool_t Dz1Json_Dz1Str_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{	// processed escape letter by lexer
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (tok->t == Dz1JsonTokenType_string)
	{
		if (tok->v != NULL || tok->v[0] != 0)
		{
			dst->data = tok->v;
			tok->v = NULL;
		}
		Dz1Error_set(errp, 0);
	}
	else if (tok->t == Dz1JsonTokenType_nul)
	{
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;;
}

bool_t Dz1Json_Dz1Str_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Dz1Str v = (Dz1Str)obj;
		if (Dz1JsonUtil_stringify_quotstr(elb, v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1Str
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Binary
bool_t Dz1Json_Dz1Binary_load(Dz1JsonVarBind *dst, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (tok->t == Dz1JsonTokenType_string)
	{
#ifndef UNIX_SYSTEM
#ifdef UNICODE
		if ((dst->data = Dz1Base64_decW(tok->v, -1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
#else
		if ((dst->data = Dz1Base64_decA(tok->v, -1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
#endif
#else
		if ((dst->data = Dz1Base64_decA(tok->v, -1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
#endif
	}
	else if (tok->t == Dz1JsonTokenType_nul)
	{
		dst->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;;
}

static bool_t _stringify_binary(Dz1Str dst, size_t dst_sz, u8_t *src, size_t src_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t sz;
	TCHAR *dp = dst;
	while(errp->code == 0 && src_size)
	{
		if ((sz = Dz1Base64_encBlock(dp, dst_sz, src, src_size, errp)) < 0) ERR_OUT(errp);
		else
		{
			dp += 4;
			dst_sz -= 4;

			src += sz;
			src_size -= sz;
		}
	}
	*dp = 0;
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_Dz1Binary_stringify(void *obj, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Dz1Binary *bin = (Dz1Binary *)obj;
		size_t len = Dz1Base64_getEncSize(bin->size);
		Dz1Str str = Dz1Calloc(sizeof(TCHAR), len + 1, errp);
		if (str == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&str);
			if (_stringify_binary(str, len, bin->data, bin->size, errp) == FALSE) ERR_OUT(errp);
			else if (Dz1JsonUtil_stringify_quotstr(elb, str, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&str);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1Binary
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1JsonSpec_add_primitive(Dz1JsonSpec *dst, Dz1Str name, Dz1JsonObjGenF genf, Dz1JsonObjDelF delf, 
								   Dz1JsonSpecPrimitiveLoaderF loadf, Dz1JsonSpecPrimitiveStringifyF stringifyf)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1JsonSpecEntry *node = Dz1JsonSpecEntry_new(name, genf, delf, NULL, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonSpecData *d = NULL;
		pthread_cleanup_push(Dz1JsonSpecEntry_delAndSetNull, (void **)&node);
		if (0) { }
		else if ((node->data = d = Dz1JsonSpecData_new(Dz1JsonSpecDataPresent_pr, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((d->x.pr = Dz1JsonSpecPrimitive_new(node, loadf, stringifyf, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->types->add(dst->types, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1JsonSpecEntry_delAndSetNull, (void **)&node);
	}
	return err;
}

// not use del ,use name => gdN
#define _spec_api_primitive_gdN(name)			Dz1Text(#name), \
												NULL, \
												(Dz1JsonObjDelF)_primitive_t_del, \
												Dz1Json_##name##_load, \
												Dz1Json_##name##_stringify

// not use del, use prefix = GdP
#define _spec_api_primitive_gdP(name, prefix)	Dz1Text(#name), \
												NULL, \
												(Dz1JsonObjDelF)_primitive_t_del, \
												prefix##_load, \
												prefix##_stringify
// use del ,use name => gDN
#define _spec_api_primitive_gDN(name)			Dz1Text(#name), \
												NULL, \
												(Dz1JsonObjDelF)name##_del, \
												Dz1Json_##name##_load, \
												Dz1Json_##name##_stringify

// use del, use prefix = GDP
#define _spec_api_primitive_gDP(name, prefix)	Dz1Text(#name), \
												NULL, \
												(Dz1JsonObjDelF)name##_del, \
												prefix##_load, \
												prefix##_stringify
static Dz1Error _construct_child_init(Dz1JsonSpecConstruct *dst, Dz1JsonSpecChild *arr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1JsonSpecChilds *list = dst->childs;
	Dz1JsonSpecChild *p = NULL, *node = NULL;
	for (p = arr; errp->code == 0 && p->name != NULL; p++)
	{
		if ((node = Dz1JsonSpecChild_clone(p, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1JsonSpecChild_delAndSetNull, (void *)&node);
			if ((*errp = list->add(list, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1JsonSpecChild_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

Dz1Error Dz1JSonSpec_add_construct(Dz1JsonSpec *dst, Dz1Str name, Dz1JsonObjGenF genf, Dz1JsonObjDelF delf, 
								   Dz1JsonConstructSetChildF scf, Dz1JsonConstructGetChildF gcf, 
								   Dz1JsonSpecChild *arr, Dz1JsonConstructType type)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1JsonSpecEntry *node = Dz1JsonSpecEntry_new(name, genf, delf, NULL, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonSpecData *d = NULL;
		Dz1JsonSpecConstruct *cst = NULL;
		pthread_cleanup_push(Dz1JsonSpecEntry_delAndSetNull, (void **)&node);
		if (0) { }
		else if ((node->data = d = Dz1JsonSpecData_new(Dz1JsonSpecDataPresent_cst, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((d->x.cst = cst = Dz1JsonSpecConstruct_new(node, type, scf, gcf, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _construct_child_init(cst, arr)).code) ERR_OUT(errp);
		else if ((*errp = dst->types->add(dst->types, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1JsonSpecEntry_delAndSetNull, (void **)&node);
	}
	return err;
}

Dz1Error Dz1JSonSpec_add_array(Dz1JsonSpec *dst, Dz1Str name, Dz1JsonObjGenF genf, Dz1JsonObjDelF delf, 
							   Dz1JsonArrayAppendF apnd, Dz1JsonArrayCountF cntf, 
							   Dz1JsonArrayTravelF travelf, Dz1Str memb_type)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1JsonSpecEntry *node = Dz1JsonSpecEntry_new(name, genf, delf, NULL, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonSpecData *d = NULL;
		pthread_cleanup_push(Dz1JsonSpecEntry_delAndSetNull, (void **)&node);
		if (0) { }
		else if ((node->data = d = Dz1JsonSpecData_new(Dz1JsonSpecDataPresent_ar, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((d->x.ar = Dz1JsonSpecArray_new(node, memb_type, apnd, cntf, travelf, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->types->add(dst->types, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1JsonSpecEntry_delAndSetNull, (void **)&node);
	}
	return err;
}


static Dz1Error _spec_append_basis(Dz1JsonSpec *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (0) { }
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(u64_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(u32_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(u16_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(u8_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(real64_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(real32_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(float))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(bool_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(time_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(void))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdN(Dz1IPv4))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gDN(Dz1Str))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("TString"), NULL, (Dz1DelFunc)Dz1Str_del, Dz1Json_Dz1Str_load, Dz1Json_Dz1Str_stringify)).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gDN(Dz1Binary))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdP(s64_t, Dz1Json_u64_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdP(s32_t, Dz1Json_u32_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdP(s16_t, Dz1Json_u16_t))).code) ERR_OUT(errp);
	else if ((*errp = Dz1JsonSpec_add_primitive(dst, _spec_api_primitive_gdP(s8_t,  Dz1Json_u8_t))).code) ERR_OUT(errp);

	return err;
}

Dz1JsonSpec *Dz1JsonSpec_generate(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);
		if ((*errp = _spec_append_basis(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
