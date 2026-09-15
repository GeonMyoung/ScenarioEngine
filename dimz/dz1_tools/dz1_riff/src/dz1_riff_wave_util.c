#include <dz1_str.h>
#include <dz1_codec.h>
#include <dz1_riff_wave_util.h>

///////////////////////////////////////////////////////////////////////////////
// Wave Format Chunk
///////////////////////////////////////////////////////////////////////////////
static void *_Dz1RiffWaveFmt_gen(str_t id, Dz1Error *errp)
{
	Dz1RiffWaveFmt *ret = Dz1RiffWaveFmt_new(0, 0, 0, 0, 0, 0, NULL, errp);
	if (ret == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0);
	return ret;
}

static ssize_t Dz1RiffWaveFmt_enc(u8_t *dst, size_t size, Dz1RiffWaveFmt *src, Dz1Error *errp)
{
	if (!src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0;
		u32_t _size = 16 + ((src->extra == NULL) ? 0 : src->extra->size);
		u8_t *cp = dst;

		DZ1_ENCODE4(cp, size, Dz1Endian4_host2big(_size), errp, ret);

		DZ1_ENCODE2(cp, size, Dz1Endian2_host2big(src->audioFormat), errp, ret);
		DZ1_ENCODE2(cp, size, Dz1Endian2_host2big(src->numOfChannel), errp, ret);
		DZ1_ENCODE4(cp, size, Dz1Endian4_host2big(src->sampleRate), errp, ret);
		DZ1_ENCODE4(cp, size, Dz1Endian4_host2big(src->byteRate), errp, ret);
		DZ1_ENCODE2(cp, size, Dz1Endian2_host2big(src->blockAlign), errp, ret);
		DZ1_ENCODE2(cp, size, Dz1Endian2_host2big(src->bitPerSample), errp, ret);

		if (src->extra) DZ1_ENCODE(cp, size, src->extra->data, src->extra->size, errp, ret);

		return ret;
	}
}

static ssize_t Dz1RiffWaveFmt_dec(Dz1RiffWaveFmt *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (!src || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0, status;
		u32_t _size, extraSize;
		u8_t *cp = src;

		DZ1_DECODE4(&_size, cp, size, errp, ret);
		_size = Dz1Endian4_big2host(_size);

		DZ1_DECODE2(&dst->audioFormat, cp, size, errp, ret);
		dst->audioFormat = Dz1Endian2_big2host(dst->audioFormat);

		DZ1_DECODE2(&dst->numOfChannel, cp, size, errp, ret);
		dst->numOfChannel = Dz1Endian2_big2host(dst->numOfChannel);

		DZ1_DECODE4(&dst->sampleRate, cp, size, errp, ret);
		dst->sampleRate = Dz1Endian4_big2host(dst->sampleRate);

		DZ1_DECODE4(&dst->byteRate, cp, size, errp, ret);
		dst->byteRate = Dz1Endian4_big2host(dst->byteRate);

		DZ1_DECODE2(&dst->blockAlign, cp, size, errp, ret);
		dst->blockAlign = Dz1Endian2_big2host(dst->blockAlign);

		DZ1_DECODE2(&dst->bitPerSample, cp, size, errp, ret);
		dst->bitPerSample = Dz1Endian2_big2host(dst->bitPerSample);


		if ((extraSize = _size - 16) > 0)
		{
			if ((dst->extra = Dz1Binary_new(NULL, extraSize, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&dst->extra);
				if ((dst->extra->data = (u8_t *)Dz1Malloc(dst->extra->size, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
				else if ((status = _getByte(cp, size, dst->extra->data, dst->extra->size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else
				{
					DZ1_CODEC_APPLY(cp, size, status, ret);
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&dst->extra);
			}
		}

		return ret;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Wave Data Chunk
///////////////////////////////////////////////////////////////////////////////
static void *_Dz1RiffWaveData_gen(str_t id, Dz1Error *errp)
{
	Dz1RiffWaveData *ret = Dz1RiffWaveData_new(NULL, errp);
	if (ret == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0);
	return ret;
}

static ssize_t Dz1RiffWaveData_enc(u8_t *dst, size_t size, Dz1RiffWaveData *_src, Dz1Error *errp)
{
	if (!_src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		Dz1Binary *src = _src->data;
		ssize_t ret = 0;
		u8_t *cp = dst;

		DZ1_ENCODE4(cp, size, Dz1Endian4_host2big(src->size), errp, ret);

		if (src->size > 0)
			DZ1_ENCODE(cp, size, src->data, src->size, errp, ret);

		return ret;
	}
}

static ssize_t Dz1RiffWaveData_dec(Dz1RiffWaveData *_dst, u8_t *src, size_t size, Dz1Error *errp)
{
	Dz1Binary *dst = NULL;
	if (!src || !_dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	if ((dst = _dst->data = Dz1Binary_new(NULL, 0, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
	else
	{
		ssize_t ret = 0, status;
		u8_t *cp = src;

		DZ1_DECODE4(&dst->size, cp, size, errp, ret);
		dst->size = Dz1Endian4_big2host(dst->size);

		if (dst->size)
		{
			if ((dst->data = (u8_t *)Dz1Malloc(dst->size, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&dst->data);
				if ((status = _getByte(cp, size, dst->data, dst->size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else
				{
					DZ1_CODEC_APPLY(cp, size, status, ret);
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&dst->data);
			}
		}
		return ret;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Wave Unknown Chunk
///////////////////////////////////////////////////////////////////////////////
static void *_Dz1RiffWaveUnknown_gen(str_t id, Dz1Error *errp)
{
	Dz1RiffWaveUnknown *ret = Dz1RiffWaveUnknown_new(id, NULL, errp);
	if (ret == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0);
	return ret;
}

static ssize_t Dz1RiffWaveUnknown_enc(u8_t *dst, size_t size, Dz1RiffWaveUnknown *src, Dz1Error *errp)
{
	if (!src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0;
		u8_t *cp = dst;

		char id[5] = { 0, };
		strcpy(id, src->id);
		DZ1_ENCODE(cp, size, (u8_t *)id, 4, errp, ret);

		if (src->chunk)
		{
			DZ1_ENCODE4(cp, size, Dz1Endian4_host2big(src->chunk->size), errp, ret);
			DZ1_ENCODE(cp, size, src->chunk->data, src->chunk->size, errp, ret);
		}
		else
		{
			u32_t temp = 0;
			DZ1_ENCODE4(cp, size, temp, errp, ret);
		}
		return ret;
	}
}

static ssize_t Dz1RiffWaveUnknown_dec(Dz1RiffWaveUnknown *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (!src || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0, status;
		u8_t *cp = src;
		u32_t temp;

		DZ1_DECODE4(&temp, cp, size, errp, ret);
		temp = Dz1Endian2_big2host(temp);

		if (temp > 0)
		{
			if ((dst->chunk = Dz1Binary_new(NULL, temp, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&dst->chunk);
				if ((dst->chunk->data = (u8_t *)Dz1Malloc(dst->chunk->size, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
				else if ((status = _getByte(cp, size, dst->chunk->data, dst->chunk->size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else
				{
					DZ1_CODEC_APPLY(cp, size, status, ret);
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&dst->chunk);
			}
		}
		return ret;
	}
}

typedef ssize_t (*enc_cast)(u8_t *dst, size_t size, void *src, Dz1Error *err);
typedef ssize_t (*dec_cast)(void *dst, u8_t *src, size_t size, Dz1Error *err);
struct Dz1RiffWaveChunkAPI
{
	Dz1RiffWaveChunkPresent present;
	str_t id;
	ssize_t (*enc)(u8_t *dst, size_t size, void *src, Dz1Error *err);
	ssize_t (*dec)(void *dst, u8_t *src, size_t size, Dz1Error *err);
	void *(*gen)(str_t id, Dz1Error *errp);
};

static struct Dz1RiffWaveChunkAPI Dz1RiffWaveChunkAPI[] =
{
	{ Dz1RiffWaveChunkPresent_fmt, "fmt ", (enc_cast)Dz1RiffWaveFmt_enc, (dec_cast)Dz1RiffWaveFmt_dec, _Dz1RiffWaveFmt_gen },
	{ Dz1RiffWaveChunkPresent_data, "data", (enc_cast)Dz1RiffWaveData_enc, (dec_cast)Dz1RiffWaveData_dec, _Dz1RiffWaveData_gen },
	{ Dz1RiffWaveChunkPresent_unknown, "", (enc_cast)Dz1RiffWaveUnknown_enc, (dec_cast)Dz1RiffWaveUnknown_dec, _Dz1RiffWaveUnknown_gen },
	{ Dz1RiffWaveChunkPresent_max }
};

static struct Dz1RiffWaveChunkAPI *Dz1RiffWaveChunkAPI_findByPresent(Dz1RiffWaveChunkPresent present)
{
	struct Dz1RiffWaveChunkAPI *i;
	for (i = Dz1RiffWaveChunkAPI; i->present != Dz1RiffWaveChunkPresent_max; i++)
		if (i->present == present) return i;
	return NULL;
}

static struct Dz1RiffWaveChunkAPI *Dz1RiffWaveChunkAPI_findByID(str_t id)
{
	struct Dz1RiffWaveChunkAPI *i;
	for (i = Dz1RiffWaveChunkAPI; i->present != Dz1RiffWaveChunkPresent_unknown; i++)
		if (strcmp(i->id, id) == 0) return i;
	return NULL;
}

static Dz1Error _Dz1RiffWave_enc(void *ptr, Dz1RiffWaveChunk *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1ListEncArg *arg = (Dz1ListEncArg *)ptr;
	struct Dz1RiffWaveChunkAPI *api = Dz1RiffWaveChunkAPI_findByPresent(p->present);
	ssize_t status;

	if (api == NULL) ERR_SET_OUT(&err, ESRCH);
	else if (api->present == Dz1RiffWaveChunkPresent_unknown)
	{
		if ((status = api->enc(arg->cp, arg->size, p->x.__ptr__, &err)) < 0) ERR_OUT(&err);
		else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	}
	else
	{
		char id[5] = { 0, };
		strcpy(id, api->id);
		if ((status = _putByte(arg->cp, arg->size, (u8_t *)api->id, 4, &err)) < 0) ERR_OUT(&err);
		else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);

		if ((status = api->enc(arg->cp, arg->size, p->x.__ptr__, &err)) < 0) ERR_OUT(&err);
		else DZ1_CODEC_APPLY(arg->cp, arg->size, status, arg->ret);
	}

	return err;
}

static ssize_t _Dz1RiffWave_dec(Dz1RiffWave *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0, status;
		u8_t *cp = src;
		struct Dz1RiffWaveChunkAPI *api = NULL;
		Dz1RiffWaveChunk *node = NULL;
		char id[5] = { 0, };

		DZ1_DECODE((u8_t *)id, 4, cp, size, errp, ret);

		if ((api = Dz1RiffWaveChunkAPI_findByID(id)) == NULL) DZ1_CODEC_ERRSET_RET(errp, ESRCH);
		else if ((node = Dz1RiffWaveChunk_new(api->present, NULL, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else
		{
			pthread_cleanup_push(Dz1RiffWaveChunk_delAndSetNull, (void *)&node);
			if ((node->x.__ptr__ = api->gen(id, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
			else if ((status = api->dec(node->x.__ptr__, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
			else
			{
				node = NULL;
				DZ1_CODEC_APPLY(cp, size, status, ret);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1RiffWaveChunk_delAndSetNull, (void *)&node);
		}
		return ret;
	}
}

ssize_t Dz1RiffWave_enc(u8_t *dst, size_t size, Dz1RiffWave *src, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0;
		u8_t *cp = dst;
		Dz1ListEncArg arg = { cp, size, 0, NULL };

		if ((*errp = src->travel(src, _Dz1RiffWave_enc, (void *)&arg)).code) DZ1_CODEC_ERR_RET(errp); 
		else DZ1_CODEC_APPLY(cp, size, arg.ret, ret);

		return ret;
	}
}

ssize_t Dz1RiffWave_dec(Dz1RiffWave *dst, u8_t *src, size_t size, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0, status;
		u8_t *cp = src;

		while(errp->code == 0 && size)
		{
			if ((status = _Dz1RiffWave_dec(dst, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				DZ1_CODEC_APPLY(cp, size, status, ret);
				Dz1Error_set(errp, 0);
			}
		}
		return ret;
	}
}

// void *Dz1RiffWave_gen(Dz1Error *err)
// {
// 	Dz1Error _err, *errp = err ? err : &_err;
// 	Dz1RiffWave *ret = Dz1RiffWave_new(errp);
// 	if (ret == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0);
// 	return ret;
// }
