#include <GitsnTestDataProtocol.h>

// implement library functions here




GitsnTestDataFrames* GitsnTestDataProtocol_convertToDataFrames(Dz1Binary* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnTestDataFrames* ret = NULL;
	if (src == NULL) ERR_OUT(errp);
	else if ((ret = GitsnTestDataFrames_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnTestDataFrame* e = NULL;
		pthread_cleanup_push(GitsnTestDataFrames_delAndSetNull, (void*)&ret);
		int sz = (src->size + 1016) / 1017;
		u8_t* p = src->data;
		for (int i = 1; i <= sz; i++)
		{
			if ((e = GitsnTestDataFrame_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(GitsnTestDataFrame_delAndSetNull, (void*)&e);
				if (0) {}
				else
				{
					e->preamble = 0xAA55;
					e->sequence = i-1;
					e->channelNum = 2;
					if (i == sz && sz != 1)
					{
						// last frame
						e->frameType = 0b10;
						e->size = (u16_t)(src->data + src->size - p);
					}
					else if (i == sz && sz == 1)
					{
						// normal frame
						e->frameType = 0b00;
						e->size = src->size;
					}
					else
					{
						// fragmented
						e->frameType = 0b11;
						e->size = 1017;
					}
					if ((e->payload = Dz1Binary_new(p, e->size, errp)) == NULL) ERR_OUT(errp);
					else if ((*errp = ret->add(ret, e)).code) ERR_OUT(errp);
					else
					{
						e = NULL;
						p += 1017;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (GitsnTestDataFrame_delAndSetNull, (void*)&e);
			}
		}
		GitsnTestDataFrames_dump(ret, 0);
		pthread_cleanup_pop(errp->code); // (GitsnTestDataFrames_delAndSetNull, (void*)&ret);
	}
	return ret;
}


Dz1Binary* GitsnTestDataProtocol_getPayloadFromDataFrames(GitsnTestDataFrames* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;
	Dz1ElasticBuf* elb = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((elb = Dz1ElasticBuf_new(4096, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnTestDataFrames_dump(src, 0);
		Dz1Stream* st = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void*)&elb);
		if ((st = Dz1Stream_openRefElasticBuf(elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			GitsnTestDataFrame* src_entry = NULL;
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void*)&st);
			while ((src_entry = src->getHead(src)) != NULL && errp->code == 0)
			{
				src->extract(src, src_entry);
				DZ1_STREAM_WRITE(st, src_entry->payload->data, src_entry->payload->size, errp, sz);
			}

			if (errp->code == 0 && sz > 0)
			{
				if ((ret = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
				else {
					Dz1Binary_dump(ret, 0);
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1);// (Dz1Stream_closeAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void*)&elb);
	}
	return ret;
}


static ssize_t GitsnTestDataFrame_write(Dz1Stream* dst, GitsnTestDataFrame *src, Dz1IOStreamEndian ed, Dz1Error* errp)
{
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1024] = { 0, };
		ssize_t sz = ret;

		u8_t* dp = data;
		*dp = 0x00;

		// preamble 0xAA55
		*dp++ = 0xAA;
		*dp++ = 0x55;

		// sequence
		*dp++ = (u8_t)((src->sequence >> 8) & 0xFF);
		*dp++ = (u8_t)((src->sequence >> 0) & 0xFF);

		// 2bit frameType, 14bit size
		*dp = 0x00;
		*dp |= (u8_t)((src->frameType & 0x03) << 6);
		*dp |= (u8_t)((src->size >> 8) & 0x3F);
		dp++;
		*dp = 0x00;
		*dp |= (u8_t)((src->size >> 0) & 0xFF);
		dp++;

		*dp++ = src->channelNum;

		memcpy(dp, src->payload->data, src->payload->size);
		dp += src->payload->size;
	
		sz = dp - data;

		DZ1_STREAM_WRITE(dst, data, sz, errp, ret);
	}
	return ret;
}

Dz1Binary* GitsnTestDataFrame_encode(GitsnTestDataFrame* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;

	if (src == NULL) ERR_OUT(errp);
	else if ((ret = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, 1024, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Stream* st = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&ret);
		if ((st = Dz1Stream_openStaticBuf(ret->data, ret->size, TRUE, 0, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void*)&st);
			if ((sz = GitsnTestDataFrame_write(st, src, Dz1IOStreamEndian_big, errp)) < 0) ERR_OUT(errp);
			else
			{
				ret->size = ((u32_t)sz & 0xFFFF);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void*)&ret);
	}

	return ret;
}


static bool_t _decode(GitsnTestDataFrame* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || src == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary* payload = NULL;

		u8_t* dp = src;
		dst->preamble = 0;
		dst->preamble = (dst->preamble << 8) | ((u16_t)*dp & 0xFF); dp++;
		dst->preamble = (dst->preamble << 8) | ((u16_t)*dp & 0xFF); dp++;

		dst->sequence = (dst->sequence << 8) | ((u16_t)*dp & 0xFF); dp++;
		dst->sequence= (dst->sequence<< 8) | ((u16_t)*dp & 0xFF); dp++;

		dst->frameType = (*dp >> 6) & 0x03;
		
		dst->size = (dst->size << 8) | ((u16_t)*dp & 0x3F); dp++;
		dst->size = (dst->size << 8) | ((u16_t)*dp & 0xFF); dp++;

		dst->channelNum = *dp++;
		
		if ((dst->payload = payload = Dz1Binary_new(dp, dst->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary_dump(dst->payload, 0);
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static ssize_t GitsnTestDataFrame_read(GitsnTestDataFrame* dst, Dz1Stream* src, u32_t src_size, Dz1IOStreamEndian ed, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t* data = NULL;
		if ((data = Dz1Calloc(1, src_size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1u8_delAndSetNull, (void*)&data);
			DZ1_STREAM_READ(data, src_size, src, errp, ret);
			if (_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1u8_delAndSetNull, (void*)&data);
		}
	}
	return ret;
}

GitsnTestDataFrame* GitsnTestDataFrame_decode(Dz1Binary* src, Dz1Error* err)
{

	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnTestDataFrame* ret = NULL;
	if (src == NULL) ERR_OUT(errp);
	else if ((ret = GitsnTestDataFrame_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Stream* st = NULL;
		pthread_cleanup_push(GitsnTestDataFrame_delAndSetNull, (void*)&ret);
		if ((st = Dz1Stream_openStaticBuf(src->data, src->size, TRUE, src->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(Dz1Stream_delAndSetNull, (void*)&st);
			if ((sz = GitsnTestDataFrame_read(ret, st, src->size, Dz1IOStreamEndian_big, errp)) < 0) ERR_OUT(errp);
			// else if (sz != (ssize_t)src->size) ERR_SET_OUT(errp, EFAULT);			// size를 어케할지... 20250519 gm
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(errp->code); (GitsnTestDataFrame_delAndSetNull, (void*)&ret);
	}
	return ret;
}

/*
1. uper encoding <- payload

2. payload를 통해서 data frame 생성

3. 2.의 결과로 data frame의 리스트가 생성

4. 각각을 binary(size가 1024) 로 인코딩

5. send to peer

*/