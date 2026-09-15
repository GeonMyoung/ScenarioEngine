#include "ToviDataBasicStream.h"
#include "ToviDataValueStream.h"
#include "ToviDataInstanceStream.h"
#include "ToviDataType.h"

ssize_t TovisTypeEnumMemb_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumMemb *dst = (TovisTypeEnumMemb *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_STREAM_READ2(&dst->order, src, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_read(&dst->name, src, ed, param, errp), errp);
		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->value_opt == NULL && (dst->value_opt = TovisValueSimple_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisValueSimple_read(dst->value_opt, src, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeEnumMemb_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumMemb *src = (TovisTypeEnumMemb *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE2(dst, src->order, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_write(dst, src->name, ed, param, errp), errp);
		if (src->value_opt == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisValueSimple_write(dst, src->value_opt, ed, param, errp), errp);
		}
	}
	return ret;
}

static Dz1Error _TovisTypeEnumMembList_write(void *ptr, TovisTypeEnumMemb *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = TovisTypeEnumMemb_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t TovisTypeEnumMembList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumMembList *dst = (TovisTypeEnumMembList *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		TovisTypeEnumMemb *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = TovisTypeEnumMemb_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(TovisTypeEnumMemb_delAndSetNull, (void *)&node);
				if ((sz = TovisTypeEnumMemb_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if (TovisTypeEnumMembList_regToIndex(node, param, errp) == FALSE) ERR_OUT(errp); // use postfix
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TovisTypeEnumMemb_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t TovisTypeEnumMembList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumMembList *src = (TovisTypeEnumMembList *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _TovisTypeEnumMembList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

ssize_t TovisTypeEnumMembInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumMembInfo *dst = (TovisTypeEnumMembInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		if (dst->ordered == NULL && (dst->ordered = TovisTypeEnumMembList_new(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisTypeEnumMembList_read(dst->ordered, src, ed, param, errp), errp);

	}
	return ret;
}

ssize_t TovisTypeEnumMembInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumMembInfo *src = (TovisTypeEnumMembInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if (src->ordered == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisTypeEnumMembList_write(dst, src->ordered, ed, param, errp), errp);

	}
	return ret;
}

ssize_t TovisTypeEnumInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumInfo *dst = (TovisTypeEnumInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_read(&dst->name, src, ed, param, errp), errp);
		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->members == NULL && (dst->members = TovisTypeEnumMembInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeEnumMembInfo_read(dst->members, src, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeEnumInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumInfo *src = (TovisTypeEnumInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_write(dst, src->name, ed, param, errp), errp);
		if (src->members == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisTypeEnumMembInfo_write(dst, src->members, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeEnumInfoIndicator_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumInfo *dst = (TovisTypeEnumInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_read(&dst->name, src, ed, param, errp), errp);
	}
	return ret;
}

ssize_t TovisTypeEnumInfoIndicator_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeEnumInfo *src = (TovisTypeEnumInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_write(dst, src->name, ed, param, errp), errp);
	}
	return ret;
}

ssize_t TovisTypeStructMemb_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeStructMemb *dst = (TovisTypeStructMemb *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_STREAM_READ2(&dst->order, src, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_read(&dst->name, src, ed, param, errp), errp);
		if (dst->type == NULL && (dst->type = TovisDataInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisDataInfoIndicator_read(dst->type, src, ed, param, errp), errp);

		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->attr == NULL && (dst->attr = TovisVariableAttr_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisVariableAttr_read(dst->attr, src, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeStructMemb_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeStructMemb *src = (TovisTypeStructMemb *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE2(dst, src->order, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_write(dst, src->name, ed, param, errp), errp);
		if (src->type == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisDataInfoIndicator_write(dst, src->type, ed, param, errp), errp);

		if (src->attr == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisVariableAttr_write(dst, src->attr, ed, param, errp), errp);
		}
	}
	return ret;
}

static Dz1Error _TovisTypeStructMembList_write(void *ptr, TovisTypeStructMemb *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = TovisTypeStructMemb_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t TovisTypeStructMembList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeStructMembList *dst = (TovisTypeStructMembList *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		TovisTypeStructMemb *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = TovisTypeStructMemb_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(TovisTypeStructMemb_delAndSetNull, (void *)&node);
				if ((sz = TovisTypeStructMemb_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TovisTypeStructMemb_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t TovisTypeStructMembList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeStructMembList *src = (TovisTypeStructMembList *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _TovisTypeStructMembList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

ssize_t TovisTypeStructMembInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeStructMembInfo *dst = (TovisTypeStructMembInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		if (dst->ordered == NULL && (dst->ordered = TovisTypeStructMembList_new(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisTypeStructMembList_read(dst->ordered, src, ed, param, errp), errp);

	}
	return ret;
}

ssize_t TovisTypeStructMembInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeStructMembInfo *src = (TovisTypeStructMembInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if (src->ordered == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisTypeStructMembList_write(dst, src->ordered, ed, param, errp), errp);

	}
	return ret;
}

ssize_t TovisTypeStructInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeStructInfo *dst = (TovisTypeStructInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_read(&dst->name, src, ed, param, errp), errp);
		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->members == NULL && (dst->members = TovisTypeStructMembInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeStructMembInfo_read(dst->members, src, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeStructInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeStructInfo *src = (TovisTypeStructInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_write(dst, src->name, ed, param, errp), errp);
		if (src->members == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisTypeStructMembInfo_write(dst, src->members, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeUnionMemb_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionMemb *dst = (TovisTypeUnionMemb *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_STREAM_READ2(&dst->order, src, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_read(&dst->name, src, ed, param, errp), errp);
		if (dst->type == NULL && (dst->type = TovisDataInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisDataInfoIndicator_read(dst->type, src, ed, param, errp), errp);

		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->attr == NULL && (dst->attr = TovisVariableAttr_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisVariableAttr_read(dst->attr, src, ed, param, errp), errp);
		}
		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->present_opt == NULL && (dst->present_opt = TovisValueSimple_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisValueSimple_read(dst->present_opt, src, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeUnionMemb_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionMemb *src = (TovisTypeUnionMemb *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE2(dst, src->order, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_write(dst, src->name, ed, param, errp), errp);
		if (src->type == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisDataInfoIndicator_write(dst, src->type, ed, param, errp), errp);

		if (src->attr == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisVariableAttr_write(dst, src->attr, ed, param, errp), errp);
		}
		if (src->present_opt == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisValueSimple_write(dst, src->present_opt, ed, param, errp), errp);
		}
	}
	return ret;
}

static Dz1Error _TovisTypeUnionMembList_write(void *ptr, TovisTypeUnionMemb *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = TovisTypeUnionMemb_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t TovisTypeUnionMembList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionMembList *dst = (TovisTypeUnionMembList *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		TovisTypeUnionMemb *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = TovisTypeUnionMemb_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(TovisTypeUnionMemb_delAndSetNull, (void *)&node);
				if ((sz = TovisTypeUnionMemb_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TovisTypeUnionMemb_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t TovisTypeUnionMembList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionMembList *src = (TovisTypeUnionMembList *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _TovisTypeUnionMembList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

ssize_t TovisTypeUnionMembInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionMembInfo *dst = (TovisTypeUnionMembInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		if (dst->ordered == NULL && (dst->ordered = TovisTypeUnionMembList_new(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisTypeUnionMembList_read(dst->ordered, src, ed, param, errp), errp);

	}
	return ret;
}

ssize_t TovisTypeUnionMembInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionMembInfo *src = (TovisTypeUnionMembInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if (src->ordered == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisTypeUnionMembList_write(dst, src->ordered, ed, param, errp), errp);

	}
	return ret;
}

ssize_t TovisTypeUnionInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionInfo *dst = (TovisTypeUnionInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_read(&dst->name, src, ed, param, errp), errp);
		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->members == NULL && (dst->members = TovisTypeUnionMembInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeUnionMembInfo_read(dst->members, src, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeUnionInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionInfo *src = (TovisTypeUnionInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_write(dst, src->name, ed, param, errp), errp);
		if (src->members == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisTypeUnionMembInfo_write(dst, src->members, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeUnionInfoIndicator_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionInfo *dst = (TovisTypeUnionInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_read(&dst->name, src, ed, param, errp), errp);
	}
	return ret;
}

ssize_t TovisTypeUnionInfoIndicator_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeUnionInfo *src = (TovisTypeUnionInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_write(dst, src->name, ed, param, errp), errp);
	}
	return ret;
}

ssize_t TovisTypeArrayCmpInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeArrayCmpInfo *dst = (TovisTypeArrayCmpInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t v32; 

		DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->present = (TovisTypeArrayCmpInfoPresent)v32;
		switch(dst->present)
		{
		case TovisTypeArrayCmpInfoPresent_specific:
			DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_read(&dst->x.specific, src, ed, param, errp), errp);
			break;
		case TovisTypeArrayCmpInfoPresent_memb_ref:
			if (dst->x.memb_ref == NULL && (dst->x.memb_ref = TovisReference_new(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisReference_read(dst->x.memb_ref, src, ed, param, errp), errp);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
	}
	return ret;
}

ssize_t TovisTypeArrayCmpInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeArrayCmpInfo *src = (TovisTypeArrayCmpInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, (u32_t)src->present, ed, errp, ret);
		switch(src->present)
		{
		case TovisTypeArrayCmpInfoPresent_specific:
			DZ1_IO_STREAM_FUNC(ret, Dz1A16UTF8_write(dst, src->x.specific, ed, param, errp), errp);
			break;
		case TovisTypeArrayCmpInfoPresent_memb_ref:
			if (src->x.memb_ref == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisReference_write(dst, src->x.memb_ref, ed, param, errp), errp);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
	}
	return ret;
}

ssize_t TovisTypeArrayElement_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeArrayElement *dst = (TovisTypeArrayElement *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; u32_t v32; 

		if (dst->elem_type == NULL && (dst->elem_type = TovisDataInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisDataInfoIndicator_read(dst->elem_type, src, ed, param, errp), errp);

		DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->elem_attr = (TovisTypeArrayAttr)v32;
		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->cmp_info == NULL && (dst->cmp_info = TovisTypeArrayCmpInfo_new(TovisTypeArrayCmpInfoPresent_max, NULL, errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayCmpInfo_read(dst->cmp_info, src, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeArrayElement_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeArrayElement *src = (TovisTypeArrayElement *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if (src->elem_type == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisDataInfoIndicator_write(dst, src->elem_type, ed, param, errp), errp);

		DZ1_STREAM_WRITE4(dst, (u32_t)src->elem_attr, ed, errp, ret);
		if (src->cmp_info == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayCmpInfo_write(dst, src->cmp_info, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeArrayInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeArrayInfo *dst = (TovisTypeArrayInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_read(&dst->name, src, ed, param, errp), errp);
		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->element == NULL && (dst->element = TovisTypeArrayElement_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayElement_read(dst->element, src, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeArrayInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeArrayInfo *src = (TovisTypeArrayInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_write(dst, src->name, ed, param, errp), errp);
		if (src->element == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayElement_write(dst, src->element, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeArrayInfoIndicator_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeArrayInfo *dst = (TovisTypeArrayInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_read(&dst->name, src, ed, param, errp), errp);
		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->element == NULL && (dst->element = TovisTypeArrayElement_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayElement_read(dst->element, src, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeArrayInfoIndicator_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeArrayInfo *src = (TovisTypeArrayInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_write(dst, src->name, ed, param, errp), errp);
		if (src->element == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayElement_write(dst, src->element, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t TovisTypeNamedInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeNamedInfo *dst = (TovisTypeNamedInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_read(&dst->src, src, ed, param, errp), errp);
	}
	return ret;
}

ssize_t TovisTypeNamedInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeNamedInfo *src = (TovisTypeNamedInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_write(dst, src->src, ed, param, errp), errp);
	}
	return ret;
}

ssize_t TovisTypeNamedInfoIndicator_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeNamedInfo *dst = (TovisTypeNamedInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_read(&dst->src, src, ed, param, errp), errp);
	}
	return ret;
}

ssize_t TovisTypeNamedInfoIndicator_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisTypeNamedInfo *src = (TovisTypeNamedInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA16UTF8_write(dst, src->src, ed, param, errp), errp);
	}
	return ret;
}

ssize_t TovisDataInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataInfo *dst = (TovisDataInfo *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t v32; 

		DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->present = (TovisDataInfoPresent)v32;
		switch(dst->present)
		{
		case TovisDataInfoPresent_nul:
			break;
		case TovisDataInfoPresent_primitive:
			DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->x.primitive = (ToviDataPrimitive)v32;
			break;
		case TovisDataInfoPresent_enumerate:
			if (dst->x.enumerate == NULL && (dst->x.enumerate = TovisTypeEnumInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeEnumInfo_read(dst->x.enumerate, src, ed, param, errp), errp);
			break;
		case TovisDataInfoPresent_structure:
			if (dst->x.structure == NULL && (dst->x.structure = TovisTypeStructInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeStructInfo_read(dst->x.structure, src, ed, param, errp), errp);
			break;
		case TovisDataInfoPresent_unified:
			if (dst->x.unified == NULL && (dst->x.unified = TovisTypeUnionInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeUnionInfo_read(dst->x.unified, src, ed, param, errp), errp);
			break;
		case TovisDataInfoPresent_table:
			if (dst->x.table == NULL && (dst->x.table = TovisTypeArrayInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayInfo_read(dst->x.table, src, ed, param, errp), errp);
			break;
		case TovisDataInfoPresent_named:
			if (dst->x.named == NULL && (dst->x.named = TovisTypeNamedInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeNamedInfo_read(dst->x.named, src, ed, param, errp), errp);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
		if (Indication(dst, param, errp) == FALSE) ERR_OUT(errp); // use func name
	}
	return ret;
}

ssize_t TovisDataInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataInfo *src = (TovisDataInfo *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, (u32_t)src->present, ed, errp, ret);
		switch(src->present)
		{
		case TovisDataInfoPresent_nul:
			break;
		case TovisDataInfoPresent_primitive:
			DZ1_STREAM_WRITE4(dst, (u32_t)src->x.primitive, ed, errp, ret);
			break;
		case TovisDataInfoPresent_enumerate:
			if (src->x.enumerate == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeEnumInfo_write(dst, src->x.enumerate, ed, param, errp), errp);
			break;
		case TovisDataInfoPresent_structure:
			if (src->x.structure == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeStructInfo_write(dst, src->x.structure, ed, param, errp), errp);
			break;
		case TovisDataInfoPresent_unified:
			if (src->x.unified == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeUnionInfo_write(dst, src->x.unified, ed, param, errp), errp);
			break;
		case TovisDataInfoPresent_table:
			if (src->x.table == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayInfo_write(dst, src->x.table, ed, param, errp), errp);
			break;
		case TovisDataInfoPresent_named:
			if (src->x.named == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeNamedInfo_write(dst, src->x.named, ed, param, errp), errp);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
	}
	return ret;
}

ssize_t TovisDataType_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataType *dst = (TovisDataType *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA_read(&dst->name, src, ed, param, errp), errp);
		if (dst->data == NULL && (dst->data = TovisDataInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisDataInfoIndicator_read(dst->data, src, ed, param, errp), errp);

	}
	return ret;
}

ssize_t TovisDataType_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataType *src = (TovisDataType *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1StrA_write(dst, src->name, ed, param, errp), errp);
		if (src->data == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, TovisDataInfoIndicator_write(dst, src->data, ed, param, errp), errp);

	}
	return ret;
}

static Dz1Error _TovisDataTypeList_write(void *ptr, TovisDataType *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = TovisDataType_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t TovisDataTypeList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataTypeList *dst = (TovisDataTypeList *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		TovisDataType *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = TovisDataType_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(TovisDataType_delAndSetNull, (void *)&node);
				if ((sz = TovisDataType_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TovisDataType_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t TovisDataTypeList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataTypeList *src = (TovisDataTypeList *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _TovisDataTypeList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

static Dz1Error _TovisDataTypeRefList_write(void *ptr, TovisDataType *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = TovisDataType_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t TovisDataTypeRefList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataTypeRefList *dst = (TovisDataTypeRefList *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		TovisDataType *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = TovisDataType_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(TovisDataType_delAndSetNull, (void *)&node);
				if ((sz = TovisDataType_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TovisDataType_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t TovisDataTypeRefList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataTypeRefList *src = (TovisDataTypeRefList *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _TovisDataTypeRefList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

static Dz1Error _TovisDataTypeSeq_write(void *ptr, TovisDataType *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = TovisDataType_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t TovisDataTypeSeq_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataTypeSeq *dst = (TovisDataTypeSeq *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		TovisDataType *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = TovisDataType_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(TovisDataType_delAndSetNull, (void *)&node);
				if ((sz = TovisDataType_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TovisDataType_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t TovisDataTypeSeq_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataTypeSeq *src = (TovisDataTypeSeq *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _TovisDataTypeSeq_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

ssize_t TovisDataObject_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataObject *dst = (TovisDataObject *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t v32; 

		DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->present = (TovisDataObjectPresent)v32;
		switch(dst->present)
		{
		case TovisDataObjectPresent_enumerate:
			if (dst->x.enumerate == NULL && (dst->x.enumerate = TovisTypeEnumInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeEnumInfo_read(dst->x.enumerate, src, ed, param, errp), errp);
			break;
		case TovisDataObjectPresent_structure:
			if (dst->x.structure == NULL && (dst->x.structure = TovisTypeStructInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeStructInfo_read(dst->x.structure, src, ed, param, errp), errp);
			break;
		case TovisDataObjectPresent_unified:
			if (dst->x.unified == NULL && (dst->x.unified = TovisTypeUnionInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeUnionInfo_read(dst->x.unified, src, ed, param, errp), errp);
			break;
		case TovisDataObjectPresent_table:
			if (dst->x.table == NULL && (dst->x.table = TovisTypeArrayInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayInfo_read(dst->x.table, src, ed, param, errp), errp);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
	}
	return ret;
}

ssize_t TovisDataObject_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataObject *src = (TovisDataObject *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, (u32_t)src->present, ed, errp, ret);
		switch(src->present)
		{
		case TovisDataObjectPresent_enumerate:
			if (src->x.enumerate == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeEnumInfo_write(dst, src->x.enumerate, ed, param, errp), errp);
			break;
		case TovisDataObjectPresent_structure:
			if (src->x.structure == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeStructInfo_write(dst, src->x.structure, ed, param, errp), errp);
			break;
		case TovisDataObjectPresent_unified:
			if (src->x.unified == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeUnionInfo_write(dst, src->x.unified, ed, param, errp), errp);
			break;
		case TovisDataObjectPresent_table:
			if (src->x.table == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, TovisTypeArrayInfo_write(dst, src->x.table, ed, param, errp), errp);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
	}
	return ret;
}

static Dz1Error _TovisDataObjects_write(void *ptr, TovisDataObject *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = TovisDataObject_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t TovisDataObjects_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataObjects *dst = (TovisDataObjects *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		TovisDataObject *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = TovisDataObject_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(TovisDataObject_delAndSetNull, (void *)&node);
				if ((sz = TovisDataObject_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TovisDataObject_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t TovisDataObjects_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataObjects *src = (TovisDataObjects *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _TovisDataObjects_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

static Dz1Error _TovisDataObjectsRef_write(void *ptr, TovisDataObject *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = TovisDataObject_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t TovisDataObjectsRef_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataObjectsRef *dst = (TovisDataObjectsRef *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		TovisDataObject *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = TovisDataObject_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(TovisDataObject_delAndSetNull, (void *)&node);
				if ((sz = TovisDataObject_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TovisDataObject_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t TovisDataObjectsRef_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TovisDataObjectsRef *src = (TovisDataObjectsRef *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _TovisDataObjectsRef_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

