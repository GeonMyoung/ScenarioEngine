#include "sample_util.h"
#include "sample_stream.h"

ssize_t MyData_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyData *dst = (MyData *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		DZ1_STREAM_READ4(&dst->data1, src, ed, errp, ret);
		DZ1_STREAM_READ2(&dst->data2, src, ed, errp, ret);
		DZ1_STREAM_READ1(&dst->data3, src, errp, ret);
	}
	return ret;
}

ssize_t MyData_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyData *src = (MyData *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, src->data1, ed, errp, ret);
		DZ1_STREAM_WRITE2(dst, src->data2, ed, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->data3, errp, ret);
	}
	return ret;
}

ssize_t StructSample_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	StructSample *dst = (StructSample *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_STREAM_READ4(&dst->data1, src, ed, errp, ret);
		DZ1_STREAM_READ2(&dst->data2, src, ed, errp, ret);
		DZ1_STREAM_READ1(&dst->data3, src, errp, ret);
		if (u8_t_aaaa(&dst->data3, param, errp) == FALSE) ERR_OUT_RET(errp, -1);
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->data4 = (EnumSample)(v8 & 0xFF);
		DZ1_STREAM_READ1(&v8, src, errp, ret); // Flag
		if (v8)
		{
			if (dst->data5 == NULL && (dst->data5 = MyData_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, MyData_read(dst->data5, src, ed, param, errp), errp);
			if (MyData_check(dst->data5, param, errp) == FALSE) ERR_OUT_RET(errp, -1);
		}
		if (StructSample_check(dst, param, errp) == FALSE) ERR_OUT(errp); // use postfix
	}
	return ret;
}

ssize_t StructSample_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	StructSample *src = (StructSample *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, src->data1, ed, errp, ret);
		DZ1_STREAM_WRITE2(dst, src->data2, ed, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->data3, errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->data4 & 0xFF), errp, ret);
		if (src->data5 == NULL) DZ1_STREAM_WRITE1(dst, 0, errp, ret);
		else
		{
			DZ1_STREAM_WRITE1(dst, 1, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, MyData_write(dst, src->data5, ed, param, errp), errp);
		}
	}
	return ret;
}

ssize_t StructSampleOther_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	StructSample *dst = (StructSample *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_STREAM_READ4(&dst->data1, src, ed, errp, ret);
		DZ1_STREAM_READ1(&dst->data3, src, errp, ret);
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->data4 = (EnumSample)(v8 & 0xFF);
		if (dst->data1 == 0)
		{
			if (dst->data5 == NULL && (dst->data5 = MyData_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, MyData_read(dst->data5, src, ed, param, errp), errp);
			if (MyData_check(dst->data5, param, errp) == FALSE) ERR_OUT_RET(errp, -1);
		}

		if (StructSample_check(dst, param, errp) == FALSE) ERR_OUT(errp); // use postfix
	}
	return ret;
}

ssize_t StructSampleOther_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	StructSample *src = (StructSample *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, src->data1, ed, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->data3, errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->data4 & 0xFF), errp, ret);
		if (src->data1 == 0)
		{
			if (src->data5 == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, MyData_write(dst, src->data5, ed, param, errp), errp);
		}

	}
	return ret;
}

static Dz1Error _StructSampleList_write(void *ptr, StructSample *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = StructSample_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t StructSampleList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	StructSampleList *dst = (StructSampleList *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		StructSample *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = StructSample_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(StructSample_delAndSetNull, (void *)&node);
				if ((sz = StructSample_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if (Entry_fix(node, param, errp) == FALSE) ERR_OUT(errp); // use func name
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (StructSample_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t StructSampleList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	StructSampleList *src = (StructSampleList *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _StructSampleList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

ssize_t UnionSample_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSample *dst = (UnionSample *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; u16_t v16; u32_t v32; 

		DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->present = (UnionSamplePresent)v32;
		switch(dst->present)
		{
		case UnionSamplePresent_data1:
			DZ1_STREAM_READ4(&dst->x.data1, src, ed, errp, ret);
			break;
		case UnionSamplePresent_data2:
			DZ1_STREAM_READ2(&dst->x.data2, src, ed, errp, ret);
			break;
		case UnionSamplePresent_data3:
			DZ1_STREAM_READ1(&dst->x.data3, src, errp, ret);
			break;
		case UnionSamplePresent_data4:
			DZ1_STREAM_READ1(&v8, src, errp, ret); dst->x.data4 = (EnumSample)(v8 & 0xFF);
			break;
		case UnionSamplePresent_data5:
			DZ1_STREAM_READ2(&v16, src, ed, errp, ret); // Flag
			if (v16)
			{
				if (dst->x.data5 == NULL && (dst->x.data5 = MyData_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
				else DZ1_IO_STREAM_FUNC(ret, MyData_read(dst->x.data5, src, ed, param, errp), errp);
			}
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
	}
	return ret;
}

ssize_t UnionSample_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSample *src = (UnionSample *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, (u32_t)src->present, ed, errp, ret);
		switch(src->present)
		{
		case UnionSamplePresent_data1:
			DZ1_STREAM_WRITE4(dst, src->x.data1, ed, errp, ret);
			break;
		case UnionSamplePresent_data2:
			DZ1_STREAM_WRITE2(dst, src->x.data2, ed, errp, ret);
			break;
		case UnionSamplePresent_data3:
			DZ1_STREAM_WRITE1(dst, src->x.data3, errp, ret);
			break;
		case UnionSamplePresent_data4:
			DZ1_STREAM_WRITE1(dst, (u8_t)(src->x.data4 & 0xFF), errp, ret);
			break;
		case UnionSamplePresent_data5:
			if (src->x.data5 == NULL) DZ1_STREAM_WRITE2(dst, 0, ed, errp, ret);
			else
			{
				DZ1_STREAM_WRITE2(dst, 1, ed, errp, ret);
				DZ1_IO_STREAM_FUNC(ret, MyData_write(dst, src->x.data5, ed, param, errp), errp);
			}
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
	}
	return ret;
}

ssize_t UnionSampleIndication_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSample *dst = (UnionSample *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t v32; 

		DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->present = (UnionSamplePresent)v32;
		switch(dst->present)
		{
		case UnionSamplePresent_data1:
			DZ1_STREAM_READ4(&dst->x.data1, src, ed, errp, ret);
			break;
		case UnionSamplePresent_data2:
			DZ1_STREAM_READ2(&dst->x.data2, src, ed, errp, ret);
			break;
		case UnionSamplePresent_data3:
			DZ1_STREAM_READ1(&dst->x.data3, src, errp, ret);
			break;
		case UnionSamplePresent_data4:
			DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->x.data4 = (EnumSample)v32;
			break;
		case UnionSamplePresent_data5:
			if (dst->x.data5 == NULL && (dst->x.data5 = MyData_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, MyData_read(dst->x.data5, src, ed, param, errp), errp);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
		if (UnionSample_Indication(dst, param, errp) == FALSE) ERR_OUT(errp); // use postfix
	}
	return ret;
}

ssize_t UnionSampleIndication_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSample *src = (UnionSample *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE4(dst, (u32_t)src->present, ed, errp, ret);
		switch(src->present)
		{
		case UnionSamplePresent_data1:
			DZ1_STREAM_WRITE4(dst, src->x.data1, ed, errp, ret);
			break;
		case UnionSamplePresent_data2:
			DZ1_STREAM_WRITE2(dst, src->x.data2, ed, errp, ret);
			break;
		case UnionSamplePresent_data3:
			DZ1_STREAM_WRITE1(dst, src->x.data3, errp, ret);
			break;
		case UnionSamplePresent_data4:
			DZ1_STREAM_WRITE4(dst, (u32_t)src->x.data4, ed, errp, ret);
			break;
		case UnionSamplePresent_data5:
			if (src->x.data5 == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, MyData_write(dst, src->x.data5, ed, param, errp), errp);
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
	}
	return ret;
}

ssize_t UnionSampleOther_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSample *dst = (UnionSample *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u8_t v8; 

		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->present = (UnionSamplePresent)(v8 & 0xFF);
		switch(dst->present)
		{
		case UnionSamplePresent_data1:
			DZ1_IO_STREAM_FUNC(ret, OtherInt_read(&dst->x.data1, src, ed, param, errp), errp);
			break;
		case UnionSamplePresent_data2: break;
		case UnionSamplePresent_data3:
			DZ1_STREAM_READ1(&dst->x.data3, src, errp, ret);
			if (u8_t_aaaa(&dst->x.data3, param, errp) == FALSE) ERR_OUT_RET(errp, -1);
			break;
		case UnionSamplePresent_data4:
			DZ1_STREAM_READ1(&v8, src, errp, ret); dst->x.data4 = (EnumSample)(v8 & 0xFF);
			break;
		case UnionSamplePresent_data5: break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
		if (UnionSample_Indication(dst, param, errp) == FALSE) ERR_OUT(errp); // use postfix
	}
	return ret;
}

ssize_t UnionSampleOther_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSample *src = (UnionSample *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->present & 0xFF), errp, ret);
		switch(src->present)
		{
		case UnionSamplePresent_data1:
			DZ1_IO_STREAM_FUNC(ret, OtherInt_write(dst, &src->x.data1, ed, param, errp), errp);
			break;
		case UnionSamplePresent_data2: break;
		case UnionSamplePresent_data3:
			DZ1_STREAM_WRITE1(dst, src->x.data3, errp, ret);
			break;
		case UnionSamplePresent_data4:
			DZ1_STREAM_WRITE1(dst, (u8_t)(src->x.data4 & 0xFF), errp, ret);
			break;
		case UnionSamplePresent_data5: break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
		}
	}
	return ret;
}

static Dz1Error _UnionSampleList_write(void *ptr, UnionSample *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	Dz1Stream *dst = arg->stream;
	Dz1IOStreamEndian ed = arg->ed;
	void *param = arg->option;
	ssize_t sz = 0;
	if ((sz = UnionSample_write(dst, node, ed, param, errp)) < 0) ERR_OUT(errp);
	else
	{
		arg->ret += sz;
		Dz1Error_set(errp, 0);
	}
	return err;
}
ssize_t UnionSampleList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_parent, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSampleList *dst = (UnionSampleList *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;
		u32_t i, cnt = 0;
		UnionSample *node = NULL;
		DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = UnionSample_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(UnionSample_delAndSetNull, (void *)&node);
				if ((sz = UnionSample_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);
				else if (UnionSampleList_fixNode(node, param, errp) == FALSE) ERR_OUT(errp); // use postfix
				else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					ret += sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (UnionSample_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

ssize_t UnionSampleList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	UnionSampleList *src = (UnionSampleList *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u32_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _UnionSampleList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else { Dz1Error_set(errp, 0); ret += arg.ret; }
	}
	return ret;
}

