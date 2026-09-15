#include "Dz1CodeGenTodecStream.h"

//static ConstructMemberCodecLimitedInfo *ConstructMemberCodecLimitedInfo_gen(Dz1Error *err);
static ssize_t ConstructMemberCodecLimitedInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
static ssize_t ConstructMemberCodecLimitedInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

////////////////////////////////////////////////////////////////////////////////
// CodecOneOfConstruct CODEC
// static CodecOneOfConstruct *CodecOneOfConstruct_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	CodecOneOfConstruct *ret = CodecOneOfConstruct_new(NULL, NULL, NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t CodecOneOfConstruct_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecOneOfConstruct *src = (CodecOneOfConstruct *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_write(dst, src->instance_name, ed, param, errp), errp);
		if (src->info == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, ConstructMemberCodecLimitedInfo_write(dst, src->info, ed, param, errp), errp);
		}
	}
	return ret;
}

static ssize_t CodecOneOfConstruct_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecOneOfConstruct *dst = (CodecOneOfConstruct *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		u8_t v8 = 0;
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_read(&dst->instance_name, src, ed, param, errp), errp);
		DZ1_STREAM_READ1(&v8, src, errp, ret);
		if (v8)
		{
			if ((dst->info = ConstructMemberCodecLimitedInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);		
			else DZ1_IO_STREAM_FUNC(ret, ConstructMemberCodecLimitedInfo_read(dst->info, src, ed, param, errp), errp);
		}
	}
	return ret;
}
// CodecOneOfConstruct CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CodecPrimitiveByte CODEC
// static CodecPrimitiveByte *CodecPrimitiveByte_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	CodecPrimitiveByte *ret = CodecPrimitiveByte_new(NULL, -1, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t CodecPrimitiveByte_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecPrimitiveByte *src = (CodecPrimitiveByte *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, src->byte_len, ed, errp, ret);
		DZ1_STREAM_WRITE4(dst, src->byte_sft, ed, errp, ret);
	}
	return ret;
}

static ssize_t CodecPrimitiveByte_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecPrimitiveByte *dst = (CodecPrimitiveByte *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		DZ1_STREAM_READ4(&dst->byte_len, src, ed, errp, ret);
		DZ1_STREAM_READ4(&dst->byte_sft, src, ed, errp, ret);
	}
	return ret;
}
// CodecPrimitiveByte CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CodecPrimitiveBits CODEC
// static CodecPrimitiveBits *CodecPrimitiveBits_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	CodecPrimitiveBits *ret = CodecPrimitiveBits_new(NULL, -1, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t CodecPrimitiveBits_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecPrimitiveBits *src = (CodecPrimitiveBits *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, src->bit_len, ed, errp, ret);
		DZ1_STREAM_WRITE4(dst, src->bit_sft, ed, errp, ret);
	}
	return ret;
}

static ssize_t CodecPrimitiveBits_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecPrimitiveBits *dst = (CodecPrimitiveBits *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		DZ1_STREAM_READ4(&dst->bit_len, src, ed, errp, ret);
		DZ1_STREAM_READ4(&dst->bit_sft, src, ed, errp, ret);
	}
	return ret;
}
// CodecPrimitiveBits CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CodecPadding CODEC
// static CodecPadding *CodecPadding_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	CodecPadding *ret = CodecPadding_new(NULL, 0, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t CodecPadding_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecPadding *src = (CodecPadding *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, src->bit_len, ed, errp, ret);
	}
	return ret;
}

static ssize_t CodecPadding_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecPadding *dst = (CodecPadding *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		DZ1_STREAM_READ4(&dst->bit_len, src, ed, errp, ret);
	}
	return ret;
}
// CodecPadding CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructMemberCodecInfo CODEC
// static ConstructMemberCodecInfo *ConstructMemberCodecInfo_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	ConstructMemberCodecInfo *ret = ConstructMemberCodecInfo_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

// Union Member API Map ---------------------
static Dz1StreamIoMap ConstructMemberCodecInfoCodecMap[] = {
	//Dz1StreamIoMap_STRUCT(ConstructMemberCodecInfo, __opcode__, __member_type__, __member_name__),
	//Dz1StreamIoMap_VAR(ConstructMemberCodecInfo, __opcode__, __api_prefix__, __member_name__),
	//Dz1StreamIoMap_VOID(ConstructMemberCodecInfo, __opcode__, __member_name__),
	Dz1StreamIoMap_STRUCT(ConstructMemberCodecInfo, ConstructMemberCodecInfoPresent_one_of_structure,	CodecOneOfConstruct,  one_of_structure),
	Dz1StreamIoMap_STRUCT(ConstructMemberCodecInfo, ConstructMemberCodecInfoPresent_byte_of_primitive,	CodecPrimitiveByte,	  byte_of_primitive),
	Dz1StreamIoMap_STRUCT(ConstructMemberCodecInfo, ConstructMemberCodecInfoPresent_bits_of_primitive,	CodecPrimitiveBits,   bits_of_primitive),
	Dz1StreamIoMap_VOID(  ConstructMemberCodecInfo, ConstructMemberCodecInfoPresent_void_member,							  void_member),
	Dz1StreamIoMap_PVAR(  ConstructMemberCodecInfo, ConstructMemberCodecInfoPresent_alternate,			Dz1Str,				  alternate),
	//Dz1StreamIoMap_STRUCT(ConstructMemberCodecInfo, ConstructMemberCodecInfoPresent_nested_construct,	Dz1Str,				  nested_construct),
	Dz1StreamIoMap_STRUCT(ConstructMemberCodecInfo, ConstructMemberCodecInfoPresent_padding,			CodecPadding,		  padding),
	Dz1StreamIoMapEntry_last
};

static ssize_t ConstructMemberCodecInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructMemberCodecInfo *src = (ConstructMemberCodecInfo *)_src;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_write(dst, src, ed, param, ConstructMemberCodecInfoCodecMap, 4, errp), errp);
	}
	return ret;
}

static ssize_t ConstructMemberCodecInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructMemberCodecInfo *dst = (ConstructMemberCodecInfo *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_read(dst, src, ed, param, ConstructMemberCodecInfoCodecMap, 4, errp), errp);
	}
	return ret;
}
// ConstructMemberCodecInfo CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructMemberCodecLimitedInfo CODEC
// static ConstructMemberCodecLimitedInfo *ConstructMemberCodecLimitedInfo_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	ConstructMemberCodecLimitedInfo *ret = ConstructMemberCodecLimitedInfo_new(0, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

// Union Member API Map ---------------------
static Dz1StreamIoMap ConstructMemberCodecLimitedInfoCodecMap[] = {
	Dz1StreamIoMap_STRUCT(ConstructMemberCodecLimitedInfo, ConstructMemberCodecLimitedInfoPresent_byte_of_primitive,CodecPrimitiveByte,	  byte_of_primitive),
	Dz1StreamIoMap_STRUCT(ConstructMemberCodecLimitedInfo, ConstructMemberCodecLimitedInfoPresent_bits_of_primitive,CodecPrimitiveBits, bits_of_primitive),
	Dz1StreamIoMap_VAR(   ConstructMemberCodecLimitedInfo, ConstructMemberCodecLimitedInfoPresent_alternate,		Dz1Str,				  alternate),
	Dz1StreamIoMapEntry_last
};

static ssize_t ConstructMemberCodecLimitedInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructMemberCodecLimitedInfo *src = (ConstructMemberCodecLimitedInfo *)_src;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_write(dst, src, ed, param, ConstructMemberCodecLimitedInfoCodecMap, 4, errp), errp);
	}
	return ret;
}

static ssize_t ConstructMemberCodecLimitedInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructMemberCodecLimitedInfo *dst = (ConstructMemberCodecLimitedInfo *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_read(dst, src, ed, param, ConstructMemberCodecLimitedInfoCodecMap, 4, errp), errp);
	}
	return ret;
}
// ConstructMemberCodecLimitedInfo CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructMemberCodecEntry CODEC
static ConstructMemberCodecEntry *ConstructMemberCodecEntry_generate(ConstructCodecEntry *parent, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructMemberCodecEntry *ret = ConstructMemberCodecEntry_new(parent, 0, NULL, NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static ssize_t ConstructMemberCodecEntry_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructMemberCodecEntry *src = (ConstructMemberCodecEntry *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		// DZ1_STREAM_WRITE(dst, src->some_ptr, len, errp, ret);
		DZ1_STREAM_WRITE4(dst, src->order, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_write(dst, src->instance_name, ed, param, errp), errp);
		if (src->info == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, ConstructMemberCodecInfo_write(dst, src->info, ed, param, errp), errp);
		}
	}
	return ret;
}

static ssize_t ConstructMemberCodecEntry_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructMemberCodecEntry *dst = (ConstructMemberCodecEntry *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		u8_t v8 = 0;
		DZ1_STREAM_READ4(&dst->order, src, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_read(&dst->instance_name, src, ed, param, errp), errp);
		DZ1_STREAM_READ1(&v8, src, errp, ret);
		if (v8)
		{
			if ((dst->info = ConstructMemberCodecInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);		
			else
			{
				DZ1_IO_STREAM_FUNC(ret, ConstructMemberCodecInfo_read(dst->info, src, ed, param, errp), errp);
				ConstructMemberCodecInfo_setParent(dst->info, dst);
			}
		}
	}
	return ret;
}
// ConstructMemberCodecEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructMemberCodecList Stream Read/Write
// static ConstructMemberCodecList *ConstructMemberCodecList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	ConstructMemberCodecList *ret = ConstructMemberCodecList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _ConstructMemberCodecList_write(void *ptr, ConstructMemberCodecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	ssize_t status = ConstructMemberCodecEntry_write(arg->stream, p, arg->ed, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else arg->ret += status;
	return err;
}

static ssize_t ConstructMemberCodecList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructMemberCodecList *src = (ConstructMemberCodecList *)_src;
	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u16_t cnt = src->count(src);
		DZ1_STREAM_WRITE2(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _ConstructMemberCodecList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else ret += arg.ret;
	}
	return ret;
}

static ssize_t ConstructMemberCodecList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructCodecEntry *entry = (ConstructCodecEntry *)param;
	ConstructMemberCodecList *dst = (ConstructMemberCodecList *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		u16_t cnt, i;
		ConstructMemberCodecEntry *node = NULL;
		DZ1_STREAM_READ2(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = ConstructMemberCodecEntry_generate(entry, errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(ConstructMemberCodecEntry_delAndSetNull, (void *)&node);
				if ((status = ConstructMemberCodecEntry_read(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					ret += status;
				}
				pthread_cleanup_pop(1); // (ConstructMemberCodecEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// ConstructMemberCodecList Stream Read/Write
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructCodecEntry CODEC
// static ConstructCodecEntry *ConstructCodecEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	ConstructCodecEntry *ret = ConstructCodecEntry_new(NULL, NULL, FALSE, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t ConstructCodecEntry_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructCodecEntry *src = (ConstructCodecEntry *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if (src->opt_suffix && src->opt_suffix[0] != 0)
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, Dz1Str_write(dst, src->opt_suffix, ed, param, errp), errp);
		}
		else DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->mode & 0xFF), errp, ret);
		DZ1_IO_STREAM_FUNC(ret, ConstructMemberCodecList_write(dst, src->member_codec, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t ConstructCodecEntry_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructCodecEntry *dst = (ConstructCodecEntry *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		u8_t v8;
//		DZ1_IO_STREAM_FUNC(ret, Dz1Str_read(&dst->obj_name, src, param, errp), errp);

		DZ1_STREAM_READ1(&v8, src, errp, ret);
		if (v8) DZ1_IO_STREAM_FUNC(ret, Dz1Str_read(&dst->opt_suffix, src, ed, param, errp), errp);

		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->mode = (ConstructCodecMode)v8;

		DZ1_IO_STREAM_FUNC_(ret, ConstructMemberCodecList_read(dst->member_codec, src, ed, dst, errp), errp);
	}
	return ret;
}
// ConstructCodecEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructCodecList Stream Read/Write
// static ConstructCodecList *ConstructCodecList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	ConstructCodecList *ret = ConstructCodecList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _ConstructCodecList_write(void *ptr, ConstructCodecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	ssize_t status = ConstructCodecEntry_write(arg->stream, p, arg->ed, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else arg->ret += status;
	return err;
}

static ssize_t ConstructCodecList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructCodecList *src = (ConstructCodecList *)_src;
	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u16_t cnt = src->count(src);
		DZ1_STREAM_WRITE2(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _ConstructCodecList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else ret += arg.ret;
	}
	return ret;
}

static ssize_t ConstructCodecList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructCodecList *dst = (ConstructCodecList *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		u16_t cnt, i;
		ConstructCodecEntry *node = NULL;
		DZ1_STREAM_READ2(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = ConstructCodecEntry_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(ConstructCodecEntry_delAndSetNull, (void *)&node);
				if ((status = ConstructCodecEntry_read(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					ret += status;
				}
				pthread_cleanup_pop(1); // (ConstructCodecEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// ConstructCodecList Stream Read/Write
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructObjectEntry CODEC
// static ConstructObjectEntry *ConstructObjectEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	ConstructObjectEntry *ret = ConstructObjectEntry_new(NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t ConstructObjectEntry_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructObjectEntry *src = (ConstructObjectEntry *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_write(dst, src->obj_name, ed, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, ConstructCodecList_write(dst, src->codecs, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t ConstructObjectEntry_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructObjectEntry *dst = (ConstructObjectEntry *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		// DZ1_STREAM_READ(dst->some_ptr, len, src, errp, ret);
		// DZ1_STREAM_READ4(dst->some_ptr, src, Dz1IoStreamEndian_big, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_read(&dst->obj_name, src, ed, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, ConstructCodecList_read(dst->codecs, src, ed, param, errp), errp);
	}
	return ret;
}
// ConstructObjectEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructObjectList Stream Read/Write
// static ConstructObjectList *ConstructObjectList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	ConstructObjectList *ret = ConstructObjectList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _ConstructObjectList_write(void *ptr, ConstructObjectEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	ssize_t status = ConstructObjectEntry_write(arg->stream, p, arg->ed, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else arg->ret += status;
	return err;
}

static ssize_t ConstructObjectList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructObjectList *src = (ConstructObjectList *)_src;
	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u16_t cnt = src->count(src);
		DZ1_STREAM_WRITE2(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _ConstructObjectList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else ret += arg.ret;
	}
	return ret;
}

static ssize_t ConstructObjectList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructObjectList *dst = (ConstructObjectList *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		u16_t cnt, i;
		ConstructObjectEntry *node = NULL;
		DZ1_STREAM_READ2(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = ConstructObjectEntry_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(ConstructObjectEntry_delAndSetNull, (void *)&node);
				if ((status = ConstructObjectEntry_read(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					ret += status;
				}
				pthread_cleanup_pop(1); // (ConstructObjectEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// ConstructObjectList Stream Read/Write
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructCodecIncludeEntry CODEC
// static ConstructCodecIncludeEntry *ConstructCodecIncludeEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	ConstructCodecIncludeEntry *ret = ConstructCodecIncludeEntry_new(NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t ConstructCodecIncludeEntry_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructCodecIncludeEntry *src = (ConstructCodecIncludeEntry *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		// DZ1_STREAM_WRITE(dst, src->some_ptr, len, errp, ret);
		// DZ1_STREAM_WRITE4(dst, src->some_ptr, Dz1IoStreamEndian_big, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_write(dst, src->filename_ext, ed, param, errp), errp);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->use_codate & 0xFF), errp, ret);
	}
	return ret;
}

static ssize_t ConstructCodecIncludeEntry_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructCodecIncludeEntry *dst = (ConstructCodecIncludeEntry *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		u8_t v8;
		// DZ1_STREAM_READ(dst->some_ptr, len, src, errp, ret);
		// DZ1_STREAM_READ4(dst->some_ptr, src, Dz1IoStreamEndian_big, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_read(&dst->filename_ext, src, ed, param, errp), errp);
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->use_codate = (bool_t)v8;
	}
	return ret;
}
// ConstructCodecIncludeEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructCodecIncludeList Stream Read/Write
// static ConstructCodecIncludeList *ConstructCodecIncludeList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	ConstructCodecIncludeList *ret = ConstructCodecIncludeList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _ConstructCodecIncludeList_write(void *ptr, ConstructCodecIncludeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	ssize_t status = ConstructCodecIncludeEntry_write(arg->stream, p, arg->ed, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else arg->ret += status;
	return err;
}

static ssize_t ConstructCodecIncludeList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructCodecIncludeList *src = (ConstructCodecIncludeList *)_src;
	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u16_t cnt = src->count(src);
		DZ1_STREAM_WRITE2(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _ConstructCodecIncludeList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else ret += arg.ret;
	}
	return ret;
}

static ssize_t ConstructCodecIncludeList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructCodecIncludeList *dst = (ConstructCodecIncludeList *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		u16_t cnt, i;
		ConstructCodecIncludeEntry *node = NULL;
		DZ1_STREAM_READ2(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = ConstructCodecIncludeEntry_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(ConstructCodecIncludeEntry_delAndSetNull, (void *)&node);
				if ((status = ConstructCodecIncludeEntry_read(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					ret += status;
				}
				pthread_cleanup_pop(1); // (ConstructCodecIncludeEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// ConstructCodecIncludeList Stream Read/Write
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructCodec CODEC
// static ConstructCodec *ConstructCodec_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	ConstructCodec *ret = ConstructCodec_new(NULL, NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

ssize_t ConstructCodec_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructCodec *src = (ConstructCodec *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src->tdo_name == NULL || src->tdo_name[0] == 0) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src->objs == NULL) ERR_SET_OUT_RET(errp, ENOENT, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_write(dst, src->tdo_name, ed, param, errp), errp);			// tdo_name

		if (src->tdo_path != NULL && src->tdo_path[0] != 0)										// tdo_path
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, Dz1Str_write(dst, src->tdo_path, ed, param, errp), errp);
		}
		else DZ1_STREAM_WRITE1(dst, 0, errp, ret);

		DZ1_IO_STREAM_FUNC(ret, Dz1Str_write(dst, src->endian, ed, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, ConstructCodecIncludeList_write(dst, src->includes, ed, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, ConstructObjectList_write(dst, src->objs, ed, param, errp), errp);	// CODEC Info

		src->is_dirty = FALSE;
	}
	return ret;
}

ssize_t ConstructCodec_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructCodec *dst = (ConstructCodec *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		u8_t v8;
		DZ1_IO_STREAM_FUNC_(ret, Dz1Str_read(&dst->tdo_name, src, ed, param, errp), errp);

		DZ1_STREAM_READ1(&v8, src, errp, ret);
		if (v8) DZ1_IO_STREAM_FUNC(ret, Dz1Str_read(&dst->tdo_path, src, ed, param, errp), errp);

		DZ1_IO_STREAM_FUNC(ret, Dz1Str_read(&dst->endian, src, ed, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, ConstructCodecIncludeList_read(dst->includes, src, ed, param, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, ConstructObjectList_read(dst->objs, src, ed, param, errp), errp);

		dst->is_dirty = FALSE;
	}
	return ret;
}
// ConstructCodec CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConstructCodec Convert Utility
Dz1Error ConstructCodec_toStream(ConstructCodec *src, Dz1Stream *dst, Dz1IOStreamEndian ed, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ssize_t sz = 0;
		if ((sz = ConstructCodec_write(dst, src, ed, param, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

ConstructCodec *ConstructCodec_fromStream(Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructCodec *ret = ConstructCodec_gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(ConstructCodec_delAndSetNull, (void *)&ret);

		if ((sz = ConstructCodec_read(ret, src, ed, param, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ConstructCodec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// ConstructCodec Convert Utility
////////////////////////////////////////////////////////////////////////////////

Dz1Error ConstructCodec_save(ConstructCodec *src, str_t path, str_t name, Dz1IOStreamEndian ed, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Stream *st = Dz1Stream_openFile3(path, name, Dz1Text("todeo"), Dz1StreamFileMode_WR, errp);
	if (st == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_delAndSetNull, (void *)&st);
		if ((*errp = ConstructCodec_toStream(src, st, ed, param)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void *)&st);
	}
	return err;
}

ConstructCodec *ConstructCodec_load(str_t path, str_t name, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
//Dz1Error		 ConstructCodec_load(ConstructCodec *dst, str_t path, str_t name, void *param)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ConstructCodec *ret = NULL;
	Dz1Stream *st = Dz1Stream_openFile2(path, name, Dz1StreamFileMode_RD, errp);
	if (st == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_delAndSetNull, (void *)&st);
		if ((ret = ConstructCodec_fromStream(st, ed, param, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void *)&st);
	}
	return ret;
}

