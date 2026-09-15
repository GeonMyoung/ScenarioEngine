#include <dz1_codec.h>
#include <dz1_riff_wave_util.h>
#include <dz1_riff_util.h>

typedef ssize_t (*enc_cast)(u8_t *dst, size_t size, void *src, Dz1Error *err);
typedef ssize_t (*dec_cast)(void *dst, u8_t *src, size_t size, Dz1Error *err);
struct Dz1RiffDataPresentMap
{
	Dz1RiffDataPresent present;
	str_t riffID;
	ssize_t (*enc)(u8_t *dst, size_t size, void *src, Dz1Error *err);
	ssize_t (*dec)(void *dst, u8_t *src, size_t size, Dz1Error *err);
	void *(*gen)(Dz1Error *errp);
	void (*delAndSetNull)(void *ptr);
};

static struct Dz1RiffDataPresentMap Dz1RiffDataPresentMap[] =
{
	{ Dz1RiffDataPresent_wave, "WAVE", (enc_cast)Dz1RiffWave_enc, (dec_cast)Dz1RiffWave_dec, (Dz1GenFunc)Dz1RiffWave_gen, Dz1RiffWave_delAndSetNull },
	{ Dz1RiffDataPresent_max }
};

static struct Dz1RiffDataPresentMap *Dz1RiffDataPresentMap_findByPresent(Dz1RiffDataPresent present)
{
	struct Dz1RiffDataPresentMap *i;
	for (i = Dz1RiffDataPresentMap; i->present != Dz1RiffDataPresent_max; i++)
		if (i->present == present) return i;
	return NULL;
}

static struct Dz1RiffDataPresentMap *Dz1RiffDataPresentMap_findByRiffID(str_t riffID)
{
	struct Dz1RiffDataPresentMap *i;
	for (i = Dz1RiffDataPresentMap; i->present != Dz1RiffDataPresent_max; i++)
		if (strcmp(i->riffID ,riffID) == 0) return i;
	return NULL;
}

static ssize_t Dz1RiffData_enc(u8_t *dst, size_t size, Dz1RiffData *src, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	if (!src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0, status;
		u8_t *cp = dst;
		struct Dz1RiffDataPresentMap *api = Dz1RiffDataPresentMap_findByPresent(src->present);
		if (api == NULL) DZ1_CODEC_ERRSET_RET(errp, ESRCH);
		
		DZ1_ENCODE(cp, size, (u8_t *)api->riffID, 4, errp, ret);

		if ((status = api->enc(cp, size, src->x.__ptr__, errp)) < 0) { DZ1_CODEC_ERR_RET(errp); DZ1_CODEC_APPLY(cp, size, status, ret); } // modified by gm 20230602

		return ret;
	}
}

static ssize_t Dz1RiffData_dec(Dz1RiffData *dst, u8_t *src, size_t size, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	if (!src || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0, status;
		u8_t *cp = src;
		struct Dz1RiffDataPresentMap *api = NULL;
		char temp[5] = { 0, };

		DZ1_DECODE((u8_t *)temp, 4, cp, size, errp, ret);

		if ((api = Dz1RiffDataPresentMap_findByRiffID(temp)) == NULL) DZ1_CODEC_ERRSET_RET(errp, ESRCH);

		if ((dst->x.__ptr__ = api->gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
		else
		{
			pthread_cleanup_push(api->delAndSetNull, (void *)&dst->x.__ptr__);

			if ((status = api->dec(dst->x.__ptr__, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				DZ1_CODEC_APPLY(cp, size, status, ret);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (api->delAndSetNull, (void *)&dst->x.__ptr__);
		}
		return ret;
	}
}

ssize_t Dz1Riff_enc(u8_t *dst, size_t size, Dz1Riff *src, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	if (!src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0, status;
		u8_t *cp = dst;

		DZ1_ENCODE(cp, size, (u8_t *)"RIFF", 4, errp, ret);

		DZ1_ENCODE4(cp, size, Dz1Endian4_host2big((u32_t)(size-4)), errp, ret);

		if ((status = Dz1RiffData_enc(cp, size, src->data, errp)) < 0) DZ1_CODEC_ERR_RET(errp); else DZ1_CODEC_APPLY(cp, size, status, ret);

		return ret;
	}
}

ssize_t Dz1Riff_dec(Dz1Riff *dst, u8_t *src, size_t size, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	if (!src || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0, status;
		u8_t *cp = src;
		char RIFF[5] = { 0, };

		DZ1_DECODE((u8_t *)RIFF, 4, cp, size, errp, ret);
		if (strcmp(RIFF, "RIFF") != 0) DZ1_CODEC_ERRSET_RET(errp, EFAULT);
		else
		{
			u32_t _size;
			DZ1_DECODE4(&_size, cp, size, errp, ret);
			_size = Dz1Endian4_big2host(_size);

			if (_size > size) DZ1_CODEC_ERRSET_RET(errp, E2BIG);
			else if ((dst->data = Dz1RiffData_new(0, NULL, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else
			{
				pthread_cleanup_push(Dz1RiffData_delAndSetNull, (void *)&dst->data);
				size = _size;
				if ((status = Dz1RiffData_dec(dst->data, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else
				{
					DZ1_CODEC_APPLY(cp, size, status, ret);
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(errp->code); // (Dz1RiffData_delAndSetNull, (void *)&dst->data);
			}
		}

		return ret;
	}
}

ssize_t Dz1Riff_load(Dz1Riff *dst, FILE *fp, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	if (!fp || !dst) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		ssize_t ret = 0, status;
		size_t size;
		u32_t _size;
		u8_t *data = NULL;
		char RIFF[5] = { 0, };
		if ((status = _readByte(fp, (u8_t *)RIFF, 4, errp)) < 0) { ERR_OUT(errp); return -1; } else ret += status;

		if (strcmp(RIFF, "RIFF") != 0) { ERR_SET_OUT(errp, EINVAL); return -1; }

		if ((status = _read4Byte(fp, &_size, errp)) < 0) { ERR_OUT(errp); return -1; } else ret += status;
		size = (size_t)Dz1Endian4_big2host(_size);

		if ((data = (u8_t *)Dz1Malloc(size, errp)) == NULL) { ERR_OUT(errp); return -1; }
		else
		{
			pthread_cleanup_push(Dz1Memory_cancel, (void *)data);

			if (dst->data != NULL) Dz1RiffData_del(dst->data);
			dst->data = NULL;
			
			if ((status = _readByte(fp, data, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				ret += status;

				if ((dst->data = Dz1RiffData_new(0, NULL, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
				else if ((status = Dz1RiffData_dec(dst->data, data, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else
				{
					ret += status;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)data);
		}
		return ret;
	}
}

ssize_t Dz1Riff_save(FILE *fp, Dz1Riff *src, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	ssize_t size = 0;
	u8_t *data = NULL;
	if (!fp || !src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else if ((size = Dz1Riff_enc(NULL, -1, src, errp)) < 0) { ERR_OUT(errp); return -1; }
	else if ((data = (u8_t *)Dz1Malloc(size, errp)) == NULL) { ERR_OUT(errp); return -1; }
	else
	{
		ssize_t ret = 0, status;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)data);

		if ((status = Dz1Riff_enc(data, size, src, errp)) < 0) ERR_OUT(errp);
		else if (status != size) ERR_SET_OUT(errp, EFAULT);
		else if ((ret = (ssize_t)fwrite(data, sizeof(u8_t), size, fp)) != size) { ERR_SET_OUT(errp, EFAULT); ret = -1; }

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);

		return ret;
	}
}
