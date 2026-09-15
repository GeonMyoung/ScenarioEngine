#include <codeconv.h>
#include <dz1_stdio.h>
#include <dz1_str.h>
#include <dz1_malloc.h>
#include "../kernel/dz1_thread_stdio.h"
#include "dz1_file_buf_stream.h"
#include "dz1_static_buf_stream.h"
#include "dz1_elastic_buf_stream.h"

bool_t Dz1IoStream_isPossibleSize(size_t s)
{
	switch(s)
	{
	case 8: case 4: case 2: case 1: return TRUE;
	default: return FALSE;
	}
}

void Dz1Stream_close(Dz1Stream *p)
{
	if (p == NULL) return;
	if (p->stream_id != (u32_t)-1 && p->stream_release)
	{
		p->stream_release(p->storage, p->stream_id);
		p->stream_id = -1;
	}
	if (p->storage && p->storage_del)
	{
		p->storage_del(p->storage);
		p->storage = NULL;
	}
	Dz1Free(p);
}

static __inline__ void _pos64A_dump(void *ptr, int tab)
{
	u64_t *v = (u64_t *)ptr;
	if (v == NULL) Dz1ThreadA_printf("(null)");
	else Dz1ThreadA_printf(DZ1_FMT64_A, (*v));
}

void Dz1StreamA_dump(Dz1Stream *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		s64_t pos = p->tell(p->storage, p->stream_id, NULL);
		if (pos < 0) Dz1ThreadA_printf("Internal fault(tell)\n");
		else Dz1ThreadA_printf("Read Postion = " DZ1_FMT64_A "\n", pos);
	}
}
#ifndef UNIX_SYSTEM
static __inline__ void _pos64W_dump(void *ptr, int tab)
{
	u64_t *v = (u64_t *)ptr;
	if (v == NULL) Dz1ThreadW_printf(L"(null)");
	else Dz1ThreadW_printf(DZ1_FMT64_W, (*v));
}

void Dz1StreamW_dump(Dz1Stream *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		s64_t pos = p->tell(p->storage, p->stream_id, NULL);
		if (pos < 0) Dz1ThreadW_printf(L"Internal fault(tell)\n");
		else Dz1ThreadW_printf(L"Read Postion = " DZ1_FMT64_W L"\n", pos);
	}
}
#endif
typedef struct PosRestoreArg
{
	Dz1Stream *p;
	s64_t pos;
} PosRestoreArg;

static void PosRestore(void *ptr)
{
	PosRestoreArg *arg = (PosRestoreArg *)ptr;
	Dz1Stream *p = arg->p;
	arg->p->seek(p->storage, p->stream_id, arg->pos, SEEK_SET);
}

#define COMPARE_SIZE			256
int Dz1Stream_cmp(Dz1Stream *a, Dz1Stream *b)
{
	int ret = 0;
	DZ1_ERROR_SAFE_VAR(errp, err);

	u8_t *pool = NULL;
	s64_t pos_a, pos_b;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL && b != NULL) ret = -1;
	else if (a != NULL && b == NULL) ret = 1;
	else if ((pos_a = a->tell(a->storage, a->stream_id, NULL)) < 0) ret = -1;
	else if ((*errp = a->seek(a->storage, a->stream_id, 0, SEEK_SET)).code) ret = -1;
	else
	{
		PosRestoreArg arg_a = { a, pos_a };
		pthread_cleanup_push(PosRestore, (void *)&arg_a);

		if ((pos_b = b->tell(b->storage, b->stream_id, NULL)) < 0) ret = 1;
		else if ((*errp = b->seek(b->storage, b->stream_id, 0, SEEK_SET)).code) ret = 1;
		else
		{
			PosRestoreArg arg_b = { b, pos_b };
			pthread_cleanup_push(PosRestore, (void *)&arg_b);

			if ((pool = (u8_t *)Dz1Malloc(COMPARE_SIZE + COMPARE_SIZE, errp)) == NULL) return -1;
			else
			{
				bool_t done = FALSE;
				u8_t *buf_a = pool, *buf_b = pool + COMPARE_SIZE;
				ssize_t len_a, len_b;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)pool);
				while(done == FALSE)
				{
					len_a = a->read(a->storage, a->stream_id, buf_a, COMPARE_SIZE, NULL);
					len_b = b->read(b->storage, b->stream_id, buf_b, COMPARE_SIZE, NULL);

					// Error 인 경우
					if		(len_a  < 0 && len_b <  0) done = TRUE;
					// 한쪽이 Error인 경우
					else if (len_a  < 0 && len_b >= 0) { ret = -1; done = TRUE; }
					else if (len_a >= 0 && len_b <  0) { ret = 1; done = TRUE; }

					// 0 바이트만 읽은 경우
					else if	(len_a == 0 && len_b == 0) done = TRUE;
					// 한쪽이 0바이트만 읽은 경우
					else if	(len_a == 0 && len_b > 0) { ret = -1; done = TRUE; }
					else if (len_a  > 0 && len_b == 0) { ret = 1; done = TRUE; }

					else if ((ret = (int)(len_a - len_b)) != 0) done = TRUE;
					else if ((ret = memcmp(buf_a, buf_b, len_a)) != 0) done = TRUE;
				}
				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)pool);
			}
			pthread_cleanup_pop(1); // (PosRestore, (void *)&arg_b);
		}
		pthread_cleanup_pop(1); // (PosRestore, (void *)&arg_a);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1Stream with FILE
static Dz1Error _file_buf_stream_init_api(Dz1Stream *ret, bool_t storage_isRef)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1FileBufStream *storage = (Dz1FileBufStream *)ret->storage;

	ret->storage_isRef = storage_isRef;
	ret->storage_del = (Dz1DelFunc)Dz1FileBufStream_del;
	ret->storage_dump = NULL;

	if ((ret->stream_id = Dz1FileBufStream_getCursor(storage, errp)) == (u32_t)-1) ERR_OUT(errp);
	else
	{
		ret->stream_release = (Dz1StreamReleaseF)Dz1FileBufStream_putCursor;
		ret->read = (Dz1StreamReadF)Dz1FileBufStream_read;
		ret->write = (Dz1StreamWriteF)Dz1FileBufStream_write;
		ret->seek = (Dz1StreamSeekF)Dz1FileBufStream_seek;
		ret->tell = (Dz1StreamTellF)Dz1FileBufStream_tell;
		ret->is_eof = (Dz1StreamIsEofF)Dz1FileBufStream_isEOF;
		ret->drain = (Dz1StreamDrainF)Dz1FileBufStream_drain;

		Dz1Error_set(errp, 0);
	}
	return err;
}

static void _file_api_mode_fix(Dz1Stream *dst, Dz1StreamFileMode mode)
{
	switch(mode)
	{
	case Dz1StreamFileMode_RD:			// 읽기만						"rb"
		dst->write = NULL;
		break;
	case Dz1StreamFileMode_WR:			// 쓰기만	(기존 데이터 삭제)	"wb"
	case Dz1StreamFileMode_WRO:			// 쓰기만	(기존 데이터 유지)	"ab"
	case Dz1StreamFileMode_WRA:			// 쓰기만	(기존 데이터 유지)	"ab"
		dst->read = NULL;
		break;
	default:
	case Dz1StreamFileMode_RW:			// 읽고 쓰기(기존 데이터 삭제)	"w+b"
	case Dz1StreamFileMode_RWO:
	case Dz1StreamFileMode_RWA:
		break;
	}
}

Dz1Stream *Dz1StreamA_openFile(str_t fn, Dz1StreamFileMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1FileBufStreamA_open(fn, mode, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _file_buf_stream_init_api(ret, FALSE)).code) ERR_OUT(errp);
		else
		{
			_file_api_mode_fix(ret, mode);
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1Stream *Dz1StreamW_openFile(wstr_t fn, Dz1StreamFileMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1FileBufStreamW_open(fn, mode, errp)) == NULL) { }
		else if ((*errp = _file_buf_stream_init_api(ret, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif

Dz1Stream *Dz1StreamA_openFile2(str_t path, str_t name,	Dz1StreamFileMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1FileBufStreamA_open2(path, name, mode, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _file_buf_stream_init_api(ret, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1Stream *Dz1StreamW_openFile2(wstr_t path, wstr_t name, Dz1StreamFileMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1FileBufStreamW_open2(path, name, mode, errp)) == NULL) { }
		else if ((*errp = _file_buf_stream_init_api(ret, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif

Dz1Stream *Dz1StreamA_openFile3(str_t path, str_t name,	str_t ext, Dz1StreamFileMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1FileBufStreamA_open3(path, name, ext, mode, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _file_buf_stream_init_api(ret, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1Stream *Dz1StreamW_openFile3(wstr_t path, wstr_t name, wstr_t ext, Dz1StreamFileMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1FileBufStreamW_open3(path, name, ext, mode, errp)) == NULL) { }
		else if ((*errp = _file_buf_stream_init_api(ret, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif

#ifndef UNIX_SYSTEM
// Dz1Stream *Dz1StreamW_refFile(Dz1FileBufStream *file_stream, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);
// 		ret->storage = file_stream;
// 		if ((*errp = _file_buf_stream_init_api(ret, TRUE)).code) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
// 		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
// 	}
// 	return ret;
// }
#endif
// Dz1Stream with FILE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Stream with static size buffer
static Dz1Error _static_buf_api_setup(Dz1Stream *ret, bool_t storage_isRef)
{
	Dz1StaticBufStream *storage = (Dz1StaticBufStream *)ret->storage;
	DZ1_ERROR_SAFE_VAR(errp, err);

	ret->storage_isRef = storage_isRef;
	ret->storage_del =(Dz1DelFunc)Dz1StaticBufStream_del;
	ret->storage_dump = (Dz1DumpFunc)Dz1StaticBufStream_dump;

	ret->stream_release = (Dz1StreamReleaseF)Dz1StaticBufStream_putCursor;
	ret->read = (Dz1StreamReadF)Dz1StaticBufStream_read;
	ret->write = (Dz1StreamWriteF)Dz1StaticBufStream_write;
	ret->seek = (Dz1StreamSeekF)Dz1StaticBufStream_seek;
	ret->tell = (Dz1StreamTellF)Dz1StaticBufStream_tell;
	ret->is_eof = (Dz1StreamIsEofF)Dz1StaticBufStream_isEOF;
	ret->drain = (Dz1StreamDrainF)Dz1StaticBufStream_drain;

	if ((ret->stream_id = Dz1StaticBufStream_getCursor(storage, errp)) == (u32_t)-1) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

Dz1Stream *Dz1Stream_refStaticBuf(Dz1StaticBufStream *storage, Dz1Error *err)	// reference buf ptr
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		ret->storage = storage;
		if ((*errp = _static_buf_api_setup(ret, TRUE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1Stream_attachStaticBuf(Dz1Stream *dst, Dz1StaticBufStream **storage)	// reference buf ptr
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (dst == NULL || storage == NULL || (*storage) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->storage != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		dst->storage = (*storage);
		if ((*errp = _static_buf_api_setup(dst, FALSE)).code) ERR_OUT(errp);
		else
		{
			(*storage) = NULL;
			Dz1Error_set(errp, 0);
		}
	}

	return err;
}

Dz1Stream *Dz1Stream_createStaticBuf(size_t size, Dz1Error *err)	// create & copy buf
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1StaticBufStream_new(NULL, size, FALSE, 0, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _static_buf_api_setup(ret, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Stream *Dz1Stream_openStaticBuf(u8_t *buf, size_t size, bool_t buf_isRef, size_t data_filled, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1StaticBufStream_new(buf, size, buf_isRef, (u32_t)data_filled, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _static_buf_api_setup(ret, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1Stream with static size buffer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Stream with dynamic size buffer
static Dz1Error _elastic_buf_api_setup(Dz1Stream *ret, bool_t storage_isRef)
{
	Dz1ElasticBufStream *storage = (Dz1ElasticBufStream *)ret->storage;
	DZ1_ERROR_SAFE_VAR(errp, err);

	ret->storage_isRef = storage_isRef;
	ret->storage_del = (Dz1DelFunc)Dz1ElasticBufStream_del;
	ret->storage_dump = (Dz1DumpFunc)Dz1ElasticBufStream_dump;

	ret->stream_release = (Dz1StreamReleaseF)Dz1ElasticBufStream_putCursor;
	ret->read = (Dz1StreamReadF)Dz1ElasticBufStream_read;
	ret->write = (Dz1StreamWriteF)Dz1ElasticBufStream_write;
	ret->seek = (Dz1StreamSeekF)Dz1ElasticBufStream_seek;
	ret->tell = (Dz1StreamTellF)Dz1ElasticBufStream_tell;
	ret->is_eof = (Dz1StreamIsEofF)Dz1ElasticBufStream_isEOF;
	ret->drain = (Dz1StreamDrainF)Dz1ElasticBufStream_drain;

	if ((ret->stream_id = Dz1ElasticBufStream_getCursor(storage, errp)) == (u32_t)-1) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}


Dz1Stream *Dz1Stream_refElasticBufStream(Dz1ElasticBufStream *buf, Dz1Error *err)		// reference elastic buffer
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = NULL;
	
	if (buf == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		ret->storage = buf;
		if ((*errp = _elastic_buf_api_setup(ret, TRUE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1Stream_attachElasticBufStream(Dz1Stream *dst, Dz1ElasticBufStream **buf)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (dst == NULL || buf == NULL || (*buf) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->storage != NULL) ERR_SET_OUT(errp, EEXIST);
	else 
	{
		dst->storage = (*buf);
		if ((*errp = _elastic_buf_api_setup(dst, FALSE)).code) ERR_OUT(errp);
		else
		{
			(*buf) = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

Dz1Stream *Dz1Stream_createElasticBufStream(size_t unit_size, Dz1Error *err)		// create elastic buffer
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = NULL;
	
	if (unit_size < 8) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ElasticBufStream *st = NULL;
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = st = Dz1ElasticBufStream_new(NULL, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((st->elastic = Dz1ElasticBuf_new((u32_t)unit_size, TRUE, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _elastic_buf_api_setup(ret, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Stream *Dz1Stream_openRefElasticBuf(Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = NULL;
	
	if (buf == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1ElasticBufStream_new(buf, TRUE, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _elastic_buf_api_setup(ret, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Stream *Dz1Stream_openAttachedElasticBuf(Dz1ElasticBuf **buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = NULL;
	
	if (buf == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1ElasticBufStream_new( (*buf), FALSE, errp)) == NULL) ERR_OUT(errp);
		else
		{
			(*buf) = NULL;
			if ((*errp = _elastic_buf_api_setup(ret, FALSE)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

// Dz1Stream with dynamic size buffer
///////////////////////////////////////////////////////////////////////////////

void Dz1Stream_release(Dz1Stream *src)
{
	if (src != NULL)
	{
		if (src->stream_id != (u32_t)-1 && src->stream_release != NULL)
		{
			src->stream_release(src->storage, src->stream_id);
			src->stream_id = -1;
		}
		if (src->storage && src->storage_del) src->storage_del(src->storage);
		memset(src, 0, sizeof(Dz1Stream));
	}
}

///////////////////////////////////////////////////////////////////////////////
// Dz1Stream Functions
ssize_t Dz1Stream_read(Dz1Stream *src, u8_t *buf, size_t size, Dz1Error *err)	// copy data from src to buf and move position
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (src == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (src->storage == NULL) ERR_SETOUT_RET(errp, ENOSYS, -1);
	else if (src->read == NULL) ERR_SETOUT_RET(errp, EPERM, -1);
	else if ((ret = src->read(src->storage, src->stream_id, buf, size, errp)) < 0)
	{
		if (errp->code != EPIPE) ERR_OUT(errp);
	}
	else if (ret == 0) Dz1Error_set(errp, EPIPE);
	else Dz1Error_set(errp, 0);
	return ret;
}

static void _endian_fix_big2host(void *ptr, size_t size)
{
	u16_t *v16 = (u16_t *)ptr;
	u32_t *v32 = (u32_t *)ptr;
	u64_t *v64 = (u64_t *)ptr;
	switch(size)
	{
	default:
	case 1: break;
	case 2: (*v16) = Dz1Endian2_big2host(*v16); break;
	case 4: (*v32) = Dz1Endian4_big2host(*v32); break;
	case 8: (*v64) = Dz1Endian8_big2host(*v64); break;
	}
}

static void _endian_fix_little2host(void *ptr, size_t size)
{
	u16_t *v16 = (u16_t *)ptr;
	u32_t *v32 = (u32_t *)ptr;
	u64_t *v64 = (u64_t *)ptr;
	switch(size)
	{
	default:
	case 1: break;
	case 2: (*v16) = Dz1Endian2_little2host(*v16); break;
	case 4: (*v32) = Dz1Endian4_little2host(*v32); break;
	case 8: (*v64) = Dz1Endian8_little2host(*v64); break;
	}
}

static Dz1Error _endian_fix2host(void *ptr, size_t size, Dz1IOStreamEndian ed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	switch(ed)
	{
	case Dz1IOStreamEndian_big:
		_endian_fix_big2host(ptr, size);
		break;
	case Dz1IOStreamEndian_little:
		_endian_fix_little2host(ptr, size);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return err;
}

ssize_t Dz1Stream_read1(Dz1Stream *src, u8_t  *v, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (src == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (src->storage == NULL) ERR_SETOUT_RET(errp, ENOSYS, -1);
	else if ((ret = Dz1Stream_read(src, (u8_t *)v, 1, errp)) < 0)
	{
		if (errp->code != EPIPE) ERR_OUT(errp);
		ret = -1;
	}
	else Dz1Error_set(errp, 0);

	return ret;
}

static ssize_t _Dz1Stream_readV(Dz1Stream *src, void *v, size_t size, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (src == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (src->storage == NULL) ERR_SETOUT_RET(errp, ENOSYS, -1);
	else if (Dz1IoStream_isPossibleSize(size) == FALSE) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((ret = Dz1Stream_read(src, (u8_t *)v, size, errp)) < 0) ERR_OUT_RET(errp, -1);
	else if (ret == 0) { /* EOF */ }
	else if (ret != (ssize_t)size)
	{
		Dz1Stream_seek(src, -ret, SEEK_CUR);
		Dz1Error_set(errp, EAGAIN);													// can't read -> EAGAIN
		ret = -1;
	}
	else if ((*errp = _endian_fix2host(v, size, ed)).code) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}

ssize_t Dz1Stream_read2(Dz1Stream *src, u16_t *v, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((ret = _Dz1Stream_readV(src, v, 2, ed, errp)) < 0) { if (errp->code != EAGAIN) ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return ret;
}

ssize_t Dz1Stream_read4(Dz1Stream *src, u32_t *v, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((ret = _Dz1Stream_readV(src, v, 4, ed, errp)) < 0) { if (errp->code != EAGAIN) ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return ret;
}

ssize_t Dz1Stream_read8(Dz1Stream *src, u64_t *v, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((ret = _Dz1Stream_readV(src, v, 8, ed, errp)) < 0) { if (errp->code != EAGAIN) ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return ret;
}

typedef union PadVar
{
	u64_t v64;
	u32_t v32;
	u16_t v16;
	u8_t v8;
} PadVar;

ssize_t Dz1Stream_readPad(Dz1Stream *src, u32_t padding, Dz1Error *err)
{
	ssize_t ret = 0, sz = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	PadVar v;
	while(padding)
	{
		if (padding >= 8)
		{
			if ((sz = Dz1Stream_read8(src, &v.v64, Dz1IOStreamEndian_big, errp)) < 0) ERR_OUT_RET(errp, -1);
			else { padding -= (u32_t)sz; ret += sz; }
		}
		else if (padding >= 4)
		{
			if ((sz = Dz1Stream_read4(src, &v.v32, Dz1IOStreamEndian_big, errp)) < 0) ERR_OUT_RET(errp, -1);
			else { padding -= (u32_t)sz; ret += sz; }
		}
		else if (padding >= 2)
		{
			if ((sz = Dz1Stream_read2(src, &v.v16, Dz1IOStreamEndian_big, errp)) < 0) ERR_OUT_RET(errp, -1);
			else { padding -= (u32_t)sz; ret += sz; }
		}
		else if ((sz = Dz1Stream_read1(src, &v.v8, errp)) < 0) ERR_OUT_RET(errp, -1);
		else { padding -= (u32_t)sz; ret += sz; }
	}
	return ret;
}

ssize_t Dz1Stream_readConst(Dz1Stream *src, u32_t size, u8_t *const_data, Dz1Error *err)
{
	ssize_t ret = 0, sz = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	u8_t *buf = (u8_t *)Dz1Calloc(sizeof(u8_t), size, errp);
	if (buf == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
		if ((sz = Dz1Stream_read(src, buf, size, errp)) < 0) ERR_OUT(errp);
		else if (sz != (ssize_t)size) Dz1Error_set(errp, EPIPE);
		else if (memcmp(buf, const_data, size) != 0) Dz1Error_set(errp, EINVAL);
		else
		{
			ret = sz;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)readed);
	}

	return errp->code == 0 ? ret : -1;
}

ssize_t Dz1Stream_peek(Dz1Stream *src, u8_t *buf, size_t peek_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if ((ret = Dz1Stream_read(src, buf, peek_size, errp)) < 0) ERR_OUT_RET(errp, -1);
	else if ((*errp = Dz1Stream_seek(src, -ret, SEEK_CUR)).code) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);
	return ret;
}

ssize_t Dz1Stream_peek1(Dz1Stream *src, u8_t  *v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if ((ret = Dz1Stream_read1(src, v, errp)) < 0) ERR_OUT_RET(errp, -1);
	else if ((*errp = Dz1Stream_seek(src, -ret, SEEK_CUR)).code) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);
	return ret;
}

ssize_t Dz1Stream_peek2(Dz1Stream *src, u16_t *v, Dz1IOStreamEndian ed, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if ((ret = _Dz1Stream_readV(src, v, 2, ed, errp)) < 0) 
	{
		ERR_OUT_RET(errp, -1);
	}
	else if ((*errp = Dz1Stream_seek(src, -ret, SEEK_CUR)).code) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);
	return ret;
}

ssize_t Dz1Stream_peek4(Dz1Stream *src, u32_t *v, Dz1IOStreamEndian ed, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if ((ret = _Dz1Stream_readV(src, v, 4, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else if ((*errp = Dz1Stream_seek(src, -ret, SEEK_CUR)).code) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);
	return ret;
}

ssize_t Dz1Stream_peek8(Dz1Stream *src, u64_t *v, Dz1IOStreamEndian ed, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if ((ret = _Dz1Stream_readV(src, v, 8, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else if ((*errp = Dz1Stream_seek(src, -ret, SEEK_CUR)).code) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);
	return ret;
}

ssize_t Dz1Stream_write(Dz1Stream *dst, u8_t *data, size_t data_size, Dz1Error *err)	// copy data from buf to dst and move position
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (dst->storage == NULL) ERR_SETOUT_RET(errp, ENOSYS, -1);
	else if (dst->write == NULL) ERR_SETOUT_RET(errp, EPERM, -1);
	else if ((ret = dst->write(dst->storage, dst->stream_id, data, data_size, errp)) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

static void _endian_fix_host2big(void *ptr, size_t size)
{
	u16_t *v16 = (u16_t *)ptr;
	u32_t *v32 = (u32_t *)ptr;
	u64_t *v64 = (u64_t *)ptr;
	switch(size)
	{
	default:
	case 1: break;
	case 2: (*v16) = Dz1Endian2_host2big(*v16); break;
	case 4: (*v32) = Dz1Endian4_host2big(*v32); break;
	case 8: (*v64) = Dz1Endian8_host2big(*v64); break;
	}
}

static void _endian_fix_host2little(void *ptr, size_t size)
{
	u16_t *v16 = (u16_t *)ptr;
	u32_t *v32 = (u32_t *)ptr;
	u64_t *v64 = (u64_t *)ptr;
	switch(size)
	{
	default:
	case 1: break;
	case 2: (*v16) = Dz1Endian2_host2little(*v16); break;
	case 4: (*v32) = Dz1Endian4_host2little(*v32); break;
	case 8: (*v64) = Dz1Endian8_host2little(*v64); break;
	}
}

static Dz1Error _endian_fix2stream(void *ptr, size_t size, Dz1IOStreamEndian ed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	switch(ed)
	{
	case Dz1IOStreamEndian_big:
		_endian_fix_host2big(ptr, size);
		break;
	case Dz1IOStreamEndian_little:
		_endian_fix_host2little(ptr, size);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return err;
}

ssize_t Dz1Stream_write1(Dz1Stream *dst, u8_t  v, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (dst->storage == NULL) ERR_SETOUT_RET(errp, ENOSYS, -1);
	else if ((ret = Dz1Stream_write(dst, (u8_t *)&v, 1, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}

static ssize_t _Dz1Stream_writeV(Dz1Stream *dst, void *v, size_t size, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (dst->storage == NULL) ERR_SETOUT_RET(errp, ENOSYS, -1);
	else if (Dz1IoStream_isPossibleSize(size) == FALSE) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t temp[8];
		memcpy(temp, v, size);

		if ((*errp = _endian_fix2stream(temp, size, ed)).code) ERR_OUT_RET(errp, -1);
		else if ((ret = Dz1Stream_write(dst, temp, size, errp)) < 0) ERR_OUT_RET(errp, -1);
		else if (ret != (ssize_t)size) ERR_SET_OUT_RET(errp, EPIPE, -1);									// can't write -> EPIPE
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

ssize_t Dz1Stream_write2(Dz1Stream *dst, u16_t v, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((ret = _Dz1Stream_writeV(dst, &v, 2, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}

ssize_t Dz1Stream_write4(Dz1Stream *dst, u32_t v, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((ret = _Dz1Stream_writeV(dst, &v, 4, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}

ssize_t Dz1Stream_write8(Dz1Stream *dst, u64_t v, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((ret = _Dz1Stream_writeV(dst, &v, 8, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}

ssize_t Dz1Stream_writePad(Dz1Stream *dst, u32_t padding, Dz1Error *err)
{
	ssize_t ret = 0, sz;
	DZ1_ERROR_SAFE_PTR(errp, err);

	PadVar v; v.v64 = 0;

	while(padding)
	{
		if (padding >= 8)
		{
			if ((sz = Dz1Stream_write8(dst, v.v64, Dz1IOStreamEndian_big, errp)) < 0) ERR_OUT_RET(errp, -1);
			else { padding -= (u32_t)sz; ret += sz; }
		}
		else if (padding >= 4)
		{
			if ((sz = Dz1Stream_write4(dst, v.v32, Dz1IOStreamEndian_big, errp)) < 0) ERR_OUT_RET(errp, -1);
			else { padding -= (u32_t)sz; ret += sz; }
		}
		else if (padding >= 2)
		{
			if ((sz = Dz1Stream_write2(dst, v.v16, Dz1IOStreamEndian_big, errp)) < 0) ERR_OUT_RET(errp, -1);
			else { padding -= (u32_t)sz; ret += sz; }
		}
		else if ((sz = Dz1Stream_write1(dst, v.v8, errp)) < 0) ERR_OUT_RET(errp, -1);
		else { padding -= (u32_t)sz; ret += sz; }
	}

	return ret;
}

Dz1Error Dz1Stream_seek(Dz1Stream *src, s64_t diff, int mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->storage == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (src->seek == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((*errp = src->seek(src->storage, src->stream_id, diff, mode)).code) { }
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1Stream_skip(Dz1Stream *src, size_t skip_len)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1Stream_seek(src, skip_len, SEEK_CUR)).code) ERR_OUT(errp);
	return err;
}

s64_t Dz1Stream_tell(Dz1Stream *src)
{
	s64_t ret = -1;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->storage == NULL) ERR_SETOUT_RET(errp, ENOSYS, -1);
	else if (src->tell == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((ret = src->tell(src->storage, src->stream_id, errp)) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

bool_t Dz1Stream_eof(Dz1Stream *src)
{
	bool_t ret = TRUE;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->storage == NULL) ERR_SETOUT_RET(errp, ENOSYS, -1);
	else ret = src->is_eof(src->storage, src->stream_id);
	return ret;
}

ssize_t Dz1Stream_drain(Dz1Stream *src, size_t drain_size, u8_t *opt_drain_buf, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (src == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (src->storage == NULL) ERR_SETOUT_RET(errp, ENOSYS, -1);
	else if (src->drain == NULL) ERR_SET_OUT_RET(errp, ENOSYS, -1);
	else 
	{
		if ((ret = src->drain(src->storage, drain_size, opt_drain_buf, errp)) < 0) ERR_OUT_RET(errp, -1);
		else Dz1Error_set(errp, 0);
//		Dz1Thread_eprintf("Dz1Stream_drain() : sz = %d, ret = %d\n", drain_size, ret);
	}

	return ret;
}

ssize_t Dz1StreamA_TextLoadLine(Dz1Stream *st, u8_t *buf64K, Dz1Error *errp)
{
	ssize_t ret = 0, status;
	u8_t *cp = buf64K;
	while(ret < 65535 && (status = Dz1Stream_read1(st, cp, errp)) == 1)
	{
		if (*cp == 0x0D) continue;
		else if (*cp == 0x0A) break;
		else { cp++; ret++; }
	}
	*cp = 0;
	return ret;
}

ssize_t Dz1StreamW_TextLoadLine(Dz1Stream *st, u8_t *buf64K, Dz1Error *errp)
{
	ssize_t ret = 0, status;
	wchar_t *cp = (wchar_t *)buf64K;
	while(ret < 32767 && (status = Dz1Stream_read2(st, (u16_t *)cp, Dz1IOStreamEndian_little, errp)) == 1)
	{
		if (*cp == 0xD) continue;
		else if (*cp == 0xA) break;
		else { cp++; ret++; }
	}
	*cp = 0;
	return ret;
}

// Dz1Stream Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Load /Save Helper
bool_t Dz1StreamA_loadHelper(void *dst, str_t path, str_t name, Dz1StreamReadFunc st_read, Dz1IOStreamEndian ed, void *read_param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;
	if ((bin = Dz1BinFileA_load2(path, name, errp)) == NULL) Dz1Error_set(errp, 0); // ignore fail
	else 
	{
		Dz1Stream *st = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((st = Dz1Stream_openStaticBuf(bin->data, bin->size, TRUE, bin->size, errp)) == NULL) Dz1Error_set(errp, 0); // ignore fail
		else
		{
			pthread_cleanup_push(Dz1Stream_delAndSetNull, (void *)&st);
			if (st_read(dst, st, ed, read_param, errp) < 0) Dz1Error_set(errp, 0); // ignore fail
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void *)&st);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

void *Dz1StreamA_genLoadHelper(str_t path, str_t name, Dz1GenFunc gen, Dz1CancelFunc del_and_setnull, Dz1StreamReadFunc st_read, Dz1IOStreamEndian ed, void *read_param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(del_and_setnull, (void *)&ret);
		if (Dz1StreamA_loadHelper(ret, path, name, st_read, ed, read_param, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (del_and_setnull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1StreamA_saveHelper(str_t path, str_t name, void *src, Dz1StreamWriteFunc st_write, Dz1IOStreamEndian ed, void *wr_param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *buf = NULL;
	if ((buf = Dz1ElasticBuf_new(64, FALSE, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		Dz1Stream *st = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&buf);
		if ((st = Dz1Stream_openRefElasticBuf(buf, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *bin = NULL;
			pthread_cleanup_push(Dz1Stream_delAndSetNull, (void *)&st);
			if (st_write(st, src, ed, wr_param, errp) < 0) ERR_OUT(errp);
			else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(buf, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = Dz1BinFileA_save2((str_t)".", name, bin)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void *)&st);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&buf);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
// UNICODE
bool_t Dz1StreamW_loadHelper(void *dst, wstr_t path, wstr_t name, Dz1StreamReadFunc st_read, Dz1IOStreamEndian ed, void *read_param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;
	if ((bin = Dz1BinFileW_load2(path, name, errp)) == NULL) Dz1Error_set(errp, 0); // ignore fail
	else 
	{
		Dz1Stream *st = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((st = Dz1Stream_openStaticBuf(bin->data, bin->size, TRUE, bin->size, errp)) == NULL) Dz1Error_set(errp, 0); // ignore fail
		else
		{
			pthread_cleanup_push(Dz1Stream_delAndSetNull, (void *)&st);
			if (st_read(dst, st, ed, read_param, errp) < 0) Dz1Error_set(errp, 0); // ignore fail
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void *)&st);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

void *Dz1StreamW_genLoadHelper(wstr_t path, wstr_t name, Dz1GenFunc gen, Dz1CancelFunc del_and_setnull, Dz1StreamReadFunc st_read, Dz1IOStreamEndian ed, void *read_param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(del_and_setnull, (void *)&ret);
		if (Dz1StreamW_loadHelper(ret, path, name, st_read, ed, read_param, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (del_and_setnull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1StreamW_saveHelper(wstr_t path, wstr_t name, void *src, Dz1StreamWriteFunc st_write, Dz1IOStreamEndian ed, void *wr_param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *buf = NULL;
	if ((buf = Dz1ElasticBuf_new(64, FALSE, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		Dz1Stream *st = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&buf);
		if ((st = Dz1Stream_openRefElasticBuf(buf, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *bin = NULL;
			pthread_cleanup_push(Dz1Stream_delAndSetNull, (void *)&st);
			if (st_write(st, src, ed, wr_param, errp) < 0) ERR_OUT(errp);
			else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(buf, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = Dz1BinFileW_save2((wstr_t)L".", name, bin)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void *)&st);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&buf);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif
// Load /Save Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Primitive Support
///////////////////////////////////////
// 8bit
ssize_t u8_write(Dz1Stream *dst, void *u8_t_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || u8_t_src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t *src = (u8_t *)u8_t_src;
		DZ1_STREAM_WRITE1(dst, (*src), errp, ret);
	}
	return ret;
}

ssize_t u8_read(void *u8_t_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || u8_t_dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t *dst = (u8_t *)u8_t_dst;
		DZ1_STREAM_READ1(dst, src, errp, ret);
	}
	return ret;
}

ssize_t Dz1u8_write(Dz1Stream *dst, void *u8_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u8_write(dst, u8_t_src, param, errp);
}

ssize_t Dz1u8_read(void *u8_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u8_read(u8_t_dst, src, param, errp);
}

ssize_t Dz1u8Bcd_read(void *u8_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (u8_t_dst == NULL || src == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		u8_t v8h, v8l, v8, t;
		DZ1_STREAM_READ1(&v8, src, errp, ret);
		v8h = (t = (v8 >> 4) & 0xF) > 9 ? 9 : t;
		v8l = (t = v8 & 0xF) > 9 ? 9 : t;
		v8 = v8h * 10 + v8l;
		*(u8_t *)u8_t_dst = v8;
	}
	return ret;
}

static u8_t _ascii_bcd2var(char c)
{
	u8_t ret = 0;
	if (c >= '0' && c <= '9') ret = (u8_t)(c - '0');
	return ret;
}

static u8_t _ascii_hex2var(char c)
{
	u8_t ret = 0;
	if (c >= 'A' && c <= 'F') ret = (u8_t)(c - 'A');
	else if (c >= 'a' && c <= 'f') ret = (u8_t)(c - 'a');
	else ret = _ascii_bcd2var(c);
	return ret;
}

ssize_t Dz1u8Ascii_read(void *u8_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{	// result 0 ~ 9, 10 ~ 11
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (u8_t_dst == NULL || src == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		u8_t v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret);
		v8 = _ascii_hex2var(v8);
		*(u8_t *)u8_t_dst = v8;
	}
	return ret;
}

ssize_t Dz1u8Bcd_write(Dz1Stream *dst, void *u8_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{	// 0~99 -> 0x00~0x99
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || u8_t_src == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		u8_t v = *(u8_t *)u8_t_src;
		if (v > 99) ERR_SET_OUT_RET(errp, EINVAL, -1);
		else
		{
			u8_t v8 = (v / 10 << 4) + (v % 10);
			DZ1_STREAM_WRITE1(dst, v8, errp, ret);
		}
	}
	return ret;
}

/*
static char _ascii_var2bcd(u8_t v)
{
	char ret = '0' + (v % 10);
	return ret;
}
*/

static u8_t _ascii_var2hex(u8_t v)
{
	if (v >= 10 && v <= 15)	return 'A' + (v - 10);
	else if (v < 10) return '0' + v;
	else return 0;
}

ssize_t Dz1u8Ascii_write(Dz1Stream *dst, void *u8_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || u8_t_src == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		u8_t v = *(u8_t *)u8_t_src;
		if (v > 15) ERR_SET_OUT_RET(errp, EINVAL, -1);
		v = _ascii_var2hex(v);
		DZ1_STREAM_WRITE1(dst, v, errp, ret);
	}
	return ret;
}
// 8bit
///////////////////////////////////////

///////////////////////////////////////
// 16bit
static ssize_t u16_write(Dz1Stream *dst, u16_t *src, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((ret = _Dz1Stream_writeV(dst, src, 2, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}

static ssize_t u16_read(Dz1Stream *src, u16_t *dst, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((ret = _Dz1Stream_readV(src, dst, 2, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}

ssize_t u16_b_write(Dz1Stream *dst, void *u16_t_src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u16_write(dst, (u16_t *)u16_t_src, Dz1IOStreamEndian_big, errp);
}

ssize_t u16_b_read(void *u16_t_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u16_read(src, (u16_t *)u16_t_dst, Dz1IOStreamEndian_big, errp);
}

ssize_t u16_l_write(Dz1Stream *dst, void *u16_t_src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u16_write(dst, (u16_t *)u16_t_src, Dz1IOStreamEndian_little, errp);
}

ssize_t u16_l_read(void *u16_t_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u16_read(src, (u16_t *)u16_t_dst, Dz1IOStreamEndian_little, errp);
}

ssize_t Dz1u16_write(Dz1Stream *dst, void *u16_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u16_write(dst, (u16_t *)u16_t_src, ed, errp);
}

ssize_t Dz1u16_read(void *u16_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u16_read(src, (u16_t *)u16_t_dst, ed, errp);
}
// 16bit
///////////////////////////////////////

///////////////////////////////////////
// 32bit
static ssize_t u32_write(Dz1Stream *dst, u32_t *src, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((ret = _Dz1Stream_writeV(dst, src, 4, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}

static ssize_t u32_read(Dz1Stream *src, u32_t *dst, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((ret = _Dz1Stream_readV(src, dst, 4, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}


ssize_t u32_b_write(Dz1Stream *dst, void *u32_t_src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u32_write(dst, (u32_t *)u32_t_src, Dz1IOStreamEndian_big, errp);
}

ssize_t u32_b_read(void *u32_t_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u32_read(src, (u32_t *)u32_t_dst, Dz1IOStreamEndian_big, errp);
}

ssize_t u32_l_write(Dz1Stream *dst, void *u32_t_src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u32_write(dst, (u32_t *)u32_t_src, Dz1IOStreamEndian_little, errp);
}

ssize_t u32_l_read(void *u32_t_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u32_read(src, (u32_t *)u32_t_dst, Dz1IOStreamEndian_little, errp);
}

ssize_t Dz1u32_write(Dz1Stream *dst, void *u32_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u32_write(dst, (u32_t *)u32_t_src, ed, errp);
}

ssize_t Dz1u32_read(void *u32_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u32_read(src, (u32_t *)u32_t_dst, ed, errp);
}
// 32bit
///////////////////////////////////////

static ssize_t u64_write(Dz1Stream *dst, u64_t *src, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((ret = _Dz1Stream_writeV(dst, src, 8, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}

static ssize_t u64_read(Dz1Stream *src, u64_t *dst, Dz1IOStreamEndian ed, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((ret = _Dz1Stream_readV(src, dst, 8, ed, errp)) < 0) ERR_OUT_RET(errp, -1);
	else Dz1Error_set(errp, 0);

	return ret;
}
ssize_t Dz1u64_write(Dz1Stream *dst, void *u64_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u64_write(dst, (u64_t *)u64_t_src, ed, errp);
}

ssize_t Dz1u64_read(void *u64_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return u64_read(src, (u64_t *)u64_t_dst, ed, errp);
}

// Primitive Support
///////////////////////////////////////////////////////////////////////////////

Dz1StreamIoMap *Dz1StreamIoMap_findByPresent(Dz1StreamIoMap *table, int present)
{
	Dz1StreamIoMap *i;
	for (i = table; i->present != -1; i++)
		if (i->present == present) return i;
	return NULL;
}

Dz1StreamIoMap *Dz1StreamIoMap_findByOpCode(Dz1StreamIoMap *table, u32_t opcode)
{
	Dz1StreamIoMap *i;
	for (i = table; i->present != -1; i++)
		if (i->opcode == opcode) return i;
	return NULL;
}

typedef enum Dz1UnionPtrPresent
{
	unknown
} Dz1UnionPtrPresent;

typedef struct Dz1UnionPtrMask
{
	Dz1UnionPtrPresent	present;
	union {
		void				*__ptr__;
		u8_t				varAddr[0];
	} x;
} Dz1UnionPtrMask;

static ssize_t _write_opcode(Dz1Stream *dst, u32_t opCode, u32_t opLen, Dz1IOStreamEndian ed, Dz1Error *errp)
{
	ssize_t ret = 0;
	switch(opLen)
	{
	case 1:
		DZ1_STREAM_WRITE1(dst, (u8_t)(opCode & 0xFF), errp, ret);
		break;
	case 2:
		DZ1_STREAM_WRITE2(dst, (u16_t)(opCode & 0xFFFF), ed, errp, ret);
		break;
	case 4:
		DZ1_STREAM_WRITE4(dst, (u32_t)opCode, ed, errp, ret);
		break;
	default:
		ERR_SET_OUT_RET(errp, EINVAL, -1);
		break;
	}
	return ret;
}

static ssize_t _read_opcode(u32_t *opCode, u32_t opLen, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t v8; u16_t v16; u32_t v32;
	switch(opLen)
	{
	case 1:
		DZ1_STREAM_READ1(&v8, src, errp, ret); (*opCode) = v8;
		break;
	case 2:
		DZ1_STREAM_READ2(&v16, src, ed, errp, ret); (*opCode) = v16;
		break;
	case 4:
		DZ1_STREAM_READ4(&v32, src, ed, errp, ret); (*opCode) = v32;
		break;
	default:
		ERR_SET_OUT_RET(errp, EINVAL, -1);
		break;
	}
	return ret;
}

static ssize_t _Dz1StreamUnion_write(Dz1Stream *dst, Dz1UnionPtrMask *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *api, Dz1Error *errp)
{
	ssize_t ret = 0;

	if (api->gen == NULL)
	{	// static variable type
		if (api->write) DZ1_IO_STREAM_FUNC(ret, api->write(dst, (void *)src->x.varAddr, ed, param, errp), errp);
	}
	else if (api->gen == (Dz1GenFunc)-1)
	{
		if (api->write) DZ1_IO_STREAM_FUNC(ret, api->write(dst, src->x.__ptr__, ed, param, errp), errp);
	}
	else
	{	// structure pointer type
		if (api->write) DZ1_IO_STREAM_FUNC(ret, api->write(dst, src->x.__ptr__, ed, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1StreamUnion_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, size_t opLen, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1StreamIoMap *api = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1UnionPtrMask *src = (Dz1UnionPtrMask *)_src;
	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else if ((api = Dz1StreamIoMap_findByPresent(table, (int)src->present)) == NULL) ERR_SET_RET(errp, ENOSYS, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, _write_opcode(dst, api->opcode, (u32_t)opLen, ed, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, _Dz1StreamUnion_write(dst, src, ed, param, api, errp), errp);
	}
	return ret;
}

ssize_t Dz1StreamUnion_writeB(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1StreamIoMap *api = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1UnionPtrMask *src = (Dz1UnionPtrMask *)_src;
	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else if ((api = Dz1StreamIoMap_findByPresent(table, (int)src->present)) == NULL) ERR_SET_RET(errp, ENOSYS, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, _Dz1StreamUnion_write(dst, src, ed, param, api, errp), errp);
	}
	return ret;
}

static ssize_t _Dz1StreamUnion_read(Dz1UnionPtrMask *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *api, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (api->gen == NULL)
	{	// static variable type
		if (api->read) DZ1_IO_STREAM_FUNC(ret, api->read(dst->x.varAddr, src, ed, param, errp), errp);
	}
	else if (api->gen == (Dz1GenFunc)-1)
	{	// static pointer variable
		if (api->read) DZ1_IO_STREAM_FUNC(ret, api->read(&dst->x.__ptr__, src, ed, param, errp), errp);
	}
	else
	{	// structure pointer type
		if (api->gen != NULL && (dst->x.__ptr__ = api->gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else if (api->read) DZ1_IO_STREAM_FUNC(ret, api->read(dst->x.__ptr__, src, ed, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1StreamUnion_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, size_t opLen, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionPtrMask *dst = (Dz1UnionPtrMask *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		u32_t opcode;
		Dz1StreamIoMap *api = NULL;
		DZ1_IO_STREAM_FUNC(ret, _read_opcode(&opcode, (u32_t)opLen, src, ed, errp), errp);
		if ((api = Dz1StreamIoMap_findByOpCode(table, opcode)) == NULL)
		{
			Dz1Thread_eprintf("!!! Unknown OPCode = %08X\n", opcode);
			ERR_SET_RET(errp, ENOSYS, -1);
		}
		else
		{
			dst->present = (Dz1UnionPtrPresent)api->present;
			DZ1_IO_STREAM_FUNC(ret, _Dz1StreamUnion_read(dst, src, ed, param, api, errp), errp);
		}
	}
	return ret;
}

ssize_t Dz1StreamUnion_readB(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionPtrMask *dst = (Dz1UnionPtrMask *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamIoMap *api = NULL;
		if ((api = Dz1StreamIoMap_findByPresent(table, dst->present)) == NULL)
		{
			ERR_SET_RET(errp, ENOSYS, -1);
		}
		else DZ1_IO_STREAM_FUNC(ret, _Dz1StreamUnion_read(dst, src, ed, param, api, errp), errp);
	}
	return ret;
}













typedef struct Dz1UnionPtrMask64
{
	Dz1UnionPtrPresent	present;
	union {
		void			*__ptr__;
		unsigned char	 b1[1];
		unsigned char	 b2[2];
		unsigned char	 b4[4];
		unsigned char	 b8[8];
		u8_t			 varAddr[0];  
		u64_t			 val64;
	} x;
} Dz1UnionPtrMask64;


// 64bit Write
static ssize_t _Dz1StreamUnion64_write(Dz1Stream *dst, Dz1UnionPtrMask64 *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *api, Dz1Error *errp)
{
	ssize_t ret = 0;

	if (api->gen == NULL)
	{	// static variable type
		if (api->write) DZ1_IO_STREAM_FUNC(ret, api->write(dst, (void *)src->x.varAddr, ed, param, errp), errp);
	}
	else
	{	// structure pointer type
		if (api->write) DZ1_IO_STREAM_FUNC(ret, api->write(dst, src->x.__ptr__, ed, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1StreamUnion64_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, size_t opLen, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1StreamIoMap *api = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1UnionPtrMask64 *src = (Dz1UnionPtrMask64 *)_src;
	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else if ((api = Dz1StreamIoMap_findByPresent(table, (int)src->present)) == NULL) ERR_SET_RET(errp, ENOSYS, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, _write_opcode(dst, api->opcode, (u32_t)opLen, ed, errp), errp);
		DZ1_IO_STREAM_FUNC(ret, _Dz1StreamUnion64_write(dst, src, ed, param, api, errp), errp);
	}
	return ret;
}

ssize_t Dz1StreamUnion64_writeB(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1StreamIoMap *api = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1UnionPtrMask64 *src = (Dz1UnionPtrMask64 *)_src;
	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else if ((api = Dz1StreamIoMap_findByPresent(table, (int)src->present)) == NULL) ERR_SET_RET(errp, ENOSYS, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, _Dz1StreamUnion64_write(dst, src, ed, param, api, errp), errp);
	}
	return ret;
}

// 64bit Read
static ssize_t _Dz1StreamUnion64_read(Dz1UnionPtrMask64 *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *api, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (api->gen == NULL)
	{	// static variable type
		if (api->read) DZ1_IO_STREAM_FUNC(ret, api->read(dst->x.varAddr, src, ed, param, errp), errp);
	}
	else
	{	// structure pointer type
		if (api->gen != NULL && (dst->x.__ptr__ = api->gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else if (api->read) DZ1_IO_STREAM_FUNC(ret, api->read(dst->x.__ptr__, src, ed, param, errp), errp);
	}
	return ret;
}

ssize_t Dz1StreamUnion64_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, size_t opLen, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionPtrMask64 *dst = (Dz1UnionPtrMask64 *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		u32_t opcode;
		Dz1StreamIoMap *api = NULL;
		DZ1_IO_STREAM_FUNC(ret, _read_opcode(&opcode, (u32_t)opLen, src, ed, errp), errp);
		if ((api = Dz1StreamIoMap_findByOpCode(table, opcode)) == NULL) ERR_SET_RET(errp, ENOSYS, -1);
		else
		{
			dst->present = (Dz1UnionPtrPresent)api->present;
			DZ1_IO_STREAM_FUNC(ret, _Dz1StreamUnion64_read(dst, src, ed, param, api, errp), errp);
		}
	}
	return ret;
}

ssize_t Dz1StreamUnion64_readB(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UnionPtrMask64 *dst = (Dz1UnionPtrMask64 *)_dst;
	if (dst == NULL || src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		Dz1StreamIoMap *api = NULL;
		if ((api = Dz1StreamIoMap_findByPresent(table, dst->present)) == NULL)
		{
			ERR_SET_RET(errp, ENOSYS, -1);
		}
		else DZ1_IO_STREAM_FUNC(ret, _Dz1StreamUnion64_read(dst, src, ed, param, api, errp), errp);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1StrW Stream
static ssize_t _Dz1StrW_write(Dz1Stream *dst, wstr_t src, size_t len, Dz1IOStreamEndian ed, Dz1Error *errp)
{
	ssize_t ret = 0;
	wchar_t *cp = src;
	while(len)
	{
		DZ1_STREAM_WRITE2(dst, *cp, ed, errp, ret);
		cp++;
		len--;
	}
	return ret;
}

static ssize_t _Dz1StrW_read(wstr_t *dst, size_t len, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (( (*dst) = (wstr_t)Dz1Calloc(sizeof(wchar_t), len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		wchar_t *cp = (*dst);
		while(len)
		{
			DZ1_STREAM_READ2((u16_t *)cp, src, ed, errp, ret);
			cp++;
			len--;
		}
	}
	return ret;
}

ssize_t Dz1StrW8_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	size_t len;
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src == NULL || (len = wcslen(src)) == 0)
	{
		DZ1_STREAM_WRITE1(dst, 0, errp, ret);
	}
	else if (len & 0xFFFFFF00) ERR_SET_OUT_RET(errp, ENOMEM, -1);
	else
	{
		DZ1_STREAM_WRITE1(dst, 1, errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(len & 0xFF), errp, ret);
		DZ1_IO_STREAM_FUNC(ret, _Dz1StrW_write(dst, src, len, ed, errp), errp);
	}
	return ret;
}

ssize_t Dz1StrW8_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t flag = 0;
		DZ1_STREAM_READ1(&flag, src, errp, ret);
		if (flag)
		{
			u8_t len;
			DZ1_STREAM_READ1(&len, src, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, _Dz1StrW_read(dst, len, src, ed, errp), errp);
		}
		else Dz1StrW_delAndSetNull(dst);
	}
	return ret;
}

ssize_t Dz1StrW16_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	size_t len;
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src == NULL || (len = wcslen(src)) == 0)
	{
		DZ1_STREAM_WRITE1(dst, 0, errp, ret);
	}
	else if (len & 0xFFFF0000) ERR_SET_OUT_RET(errp, ENOMEM, -1);
	else
	{
		DZ1_STREAM_WRITE1(dst, 1, errp, ret);
		DZ1_STREAM_WRITE2(dst, (u16_t)(len & 0xFFFF), ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, _Dz1StrW_write(dst, src, len, ed, errp), errp);
	}
	return ret;
}

ssize_t Dz1StrW16_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t flag = 0;
		DZ1_STREAM_READ1(&flag, src, errp, ret);
		if (flag)
		{
			u16_t len;
			DZ1_STREAM_READ2(&len, src, ed, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, _Dz1StrW_read(dst, len, src, ed,errp), errp);
		}
		else Dz1StrW_delAndSetNull(dst);
	}
	return ret;
}

ssize_t Dz1StrW32_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	size_t len;
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src == NULL || (len = wcslen(src)) == 0)
	{
		DZ1_STREAM_WRITE1(dst, 0, errp, ret);
	}
	else
	{
		DZ1_STREAM_WRITE1(dst, 1, errp, ret);
		DZ1_STREAM_WRITE4(dst, (u32_t)len, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, _Dz1StrW_write(dst, src, len, ed, errp), errp);
	}
	return ret;
}

ssize_t Dz1StrW32_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t flag = 0;
		DZ1_STREAM_READ1(&flag, src, errp, ret);
		if (flag)
		{
			u32_t len;
			DZ1_STREAM_READ4(&len, src, ed, errp, ret);
			DZ1_IO_STREAM_FUNC(ret, _Dz1StrW_read(dst, len, src, ed, errp), errp);
		}
		else Dz1StrW_delAndSetNull(dst);
	}
	return ret;
}

ssize_t Dz1StrWN32_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		size_t len = src == NULL ? 0 : wcslen(src);
		DZ1_STREAM_WRITE4(dst, (u32_t)len, ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, _Dz1StrW_write(dst, src, len, ed, errp), errp);
	}
	return ret;
}

ssize_t Dz1StrWN32_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u32_t len;
		Dz1StrW_delAndSetNull(dst);
		DZ1_STREAM_READ4(&len, src, ed, errp, ret);
		if (len > 0)
		{
			if (( *dst = (wstr_t)Dz1Calloc(sizeof(wchar_t), len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, _Dz1StrW_read(dst, len, src, ed, errp), errp);
		}
	}
	return ret;
}

ssize_t Dz1StrWX_read(wstr_t *dst, Dz1Stream *src, size_t fixed_byte_len, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	wstr_t temp = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || fixed_byte_len == 0) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		size_t unsz = sizeof(wchar_t);
		size_t char_len = (fixed_byte_len / unsz) + ((fixed_byte_len % unsz) ? 1 : 0);
		if ((temp = (wstr_t)Dz1Calloc(sizeof(wchar_t), char_len + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			wchar_t *dp = temp;
			ssize_t sz = 0;
			PadVar v = { 0 };
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&temp);
			while(errp->code == 0 && fixed_byte_len >= unsz)
			{
				switch(unsz)
				{
				case 2:
					if ((sz = Dz1Stream_read2(src, &v.v16, ed, errp)) < 0) { ERR_OUT(errp); ret = -1; }
					else
					{
						*dp++ = v.v16;
						ret += sz;
						fixed_byte_len -= sz;
					}
					break;
				case 4:
					if ((sz = Dz1Stream_read4(src, &v.v32, ed, errp)) < 0) { ERR_OUT(errp); ret = -1; }
					else
					{
						*dp++ = v.v32;
						ret += sz;
						fixed_byte_len -= sz;
					}
					break;
				default:
					ERR_SET_OUT(errp, EFAULT);
					ret = -1;
					break;
				}
			}
			*dp = 0;

			if (errp->code == 0)
			{
				if ((sz = Dz1Stream_readPad(src, (u32_t)fixed_byte_len, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else
				{
					ret += sz;
					fixed_byte_len -= sz;

					if (( (*dst) = Dz1StrW_dup(temp, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
					else Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&temp);
		}
	}
	return ret;
}

ssize_t Dz1StrWX_write(Dz1Stream *dst, wstr_t src, size_t fixed_len, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		size_t unsz = sizeof(wchar_t);

		size_t len = (src == NULL || src[0] == 0) ? 0 : wcslen(src);
		size_t len_byte = len * unsz;

		size_t write_len = fixed_len < len_byte ? fixed_len : len;
		if (write_len)
		{
			ssize_t sz;
			wchar_t *sp = src;
			while(errp->code == 0 && write_len >= unsz && *sp)
			{
				switch(unsz)
				{
				case 2:
					if ((sz = Dz1Stream_write2(dst, *sp, Dz1IOStreamEndian_little, errp)) < 0) { ERR_OUT(errp); ret = -1; }
					else
					{
						sp++;
						write_len -= sz;
						ret += sz;
					}
					break;
				case 4:
					if ((sz = Dz1Stream_write4(dst, *sp, Dz1IOStreamEndian_little, errp)) < 0) { ERR_OUT(errp); ret = -1; }
					else
					{
						sp++;
						write_len -= sz;
						ret += sz;
					}
					break;
				default:
					ERR_SET_OUT(errp, EFAULT);
					ret = -1;
					break;
				}
			}

			if (errp->code == 0)
			{
				if ((sz = Dz1Stream_writePad(dst, (u32_t)write_len, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else
				{
					write_len -= sz;
					ret += sz;
				}
			}
		}
		DZ1_IO_STREAM_FUNC(ret, Dz1Stream_writePad(dst, (u32_t)write_len, errp), errp);
	}
	return ret;
}
// Dz1StrW Stream
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StrW?UTF8_read
static ssize_t _Dz1StrWUTF8_read(wstr_t *dst, Dz1Stream *src, u32_t len, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t *utf8 = NULL;
	if ((utf8 = (u8_t *)Dz1Calloc(sizeof(u8_t), len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if ((sz = Dz1Stream_read(src, utf8, len, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else if ((*dst = (wstr_t)Dz1String_conv(utf8, len, "UTF-8", WINDOWS_UNICODE, NULL)) == NULL) { ERR_SET_OUT(errp, EFAULT); ret = -1; }
		else
		{
			ret += sz;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return ret;
}

ssize_t Dz1StrW16UTF8_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u16_t len;
		ssize_t sz = 0;

		Dz1StrW_delAndSetNull(dst);					// init
		DZ1_STREAM_READ2(&len, src, ed, errp, ret);	// read length 2
		if (len) DZ1_IO_STREAM_FUNC(ret, _Dz1StrWUTF8_read(dst, src, len, errp), errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

ssize_t Dz1StrW32UTF8_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u32_t len;
		ssize_t sz = 0;

		Dz1StrW_delAndSetNull(dst);					// init
		DZ1_STREAM_READ4(&len, src, ed, errp, ret);	// read length 4
		if (len) DZ1_IO_STREAM_FUNC(ret, _Dz1StrWUTF8_read(dst, src, len, errp), errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}
// Dz1StrW?UTF8_read
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StrW?UTF8_write
ssize_t Dz1StrW16UTF8_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	u8_t *utf8 = NULL;
	size_t utf8_size = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src == NULL || src[0] == 0) DZ1_STREAM_WRITE4(dst, 0, ed, errp, ret);	// 0 length
	else if ((utf8 = (u8_t *)Dz1String_conv(src, wcslen(src) * sizeof(wchar_t), WINDOWS_UNICODE, "UTF-8", &utf8_size)) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if (utf8_size > 0xFFFF) { ERR_SET_OUT(errp, E2BIG); ret = -1; }
		else if ((sz = Dz1Stream_write2(dst, (u16_t)(utf8_size & 0xFFFF), ed, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else
		{
			ret += sz;
			if ((sz = Dz1Stream_write(dst, utf8, utf8_size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				ret += sz;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return ret;
}

ssize_t Dz1StrW32UTF8_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	u8_t *utf8 = NULL;
	size_t utf8_size = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src == NULL || src[0] == 0) DZ1_STREAM_WRITE4(dst, 0, ed, errp, ret);	// 0 length
	else if ((utf8 = (u8_t *)Dz1String_conv(src, wcslen(src) * sizeof(wchar_t), WINDOWS_UNICODE, "UTF-8", &utf8_size)) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if ((sz = Dz1Stream_write4(dst, (u32_t)utf8_size, ed, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else
		{
			ret += sz;
			if ((sz = Dz1Stream_write(dst, utf8, utf8_size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				ret += sz;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return ret;
}
// Dz1StrW?UTF8_write
////////////////////////////////////////////////////////////////////////////////
#endif

///////////////////////////////////////////////////////////////////////////////
// Dz1StrA Stream
ssize_t Dz1StrA8_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t flag;
		DZ1_STREAM_READ1(&flag, src, errp, ret);
		if (flag)
		{
			u8_t len;
			Dz1StrA_delAndSetNull(dst);
			DZ1_STREAM_READ1(&len, src, errp, ret);
			if (( (*dst) = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
			DZ1_STREAM_READ( (u8_t *)(*dst), len, src, errp, ret);
		}
		else
		{
			Dz1StrA_delAndSetNull(dst);
			(*dst) = NULL;
		}
	}
	return ret;
}

ssize_t Dz1StrA8_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		size_t len = 0;
		u8_t flag = (src == NULL || (len = strlen(src)) == 0) ? 0 : 1;

		if (len & 0xFFFFFF00) ERR_SET_OUT_RET(errp, ENOMEM, -1);

		DZ1_STREAM_WRITE1(dst, flag, errp, ret);
		if (flag)
		{
			DZ1_STREAM_WRITE1(dst, (u8_t)(len & 0xFF), errp, ret);
			DZ1_STREAM_WRITE(dst, (u8_t *)src, len, errp, ret);
		}
	}
	return ret;
}


ssize_t Dz1StrA16_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t flag;
		DZ1_STREAM_READ1(&flag, src, errp, ret);
		if (flag)
		{
			u16_t len;
			Dz1StrA_delAndSetNull(dst);
			DZ1_STREAM_READ2(&len, src, ed, errp, ret);
			if (( (*dst) = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
			DZ1_STREAM_READ( (u8_t *)(*dst), len, src, errp, ret);
		}
		else
		{
			Dz1StrA_delAndSetNull(dst);
			(*dst) = NULL;
		}
	}
	return ret;
}

ssize_t Dz1StrA16_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		size_t len = 0;
		u8_t flag = (src == NULL || (len = strlen(src)) == 0) ? 0 : 1;

		if (len & 0xFFFF0000) ERR_SET_OUT_RET(errp, ENOMEM, -1);

		DZ1_STREAM_WRITE1(dst, flag, errp, ret);
		if (flag)
		{
			DZ1_STREAM_WRITE2(dst, (u16_t)(len & 0xFFFF), ed, errp, ret);
			DZ1_STREAM_WRITE(dst, (u8_t *)src, len, errp, ret);
		}
	}
	return ret;
}

ssize_t Dz1StrA32_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t flag;
		DZ1_STREAM_READ1(&flag, src, errp, ret);
		if (flag)
		{
			str_t temp = NULL;
			u32_t len;
			Dz1StrA_delAndSetNull(dst);
			DZ1_STREAM_READ4(&len, src, ed, errp, ret);
			if (( (*dst) = temp = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
			DZ1_STREAM_READ( (u8_t *)temp, len, src, errp, ret);
		}
		else
		{
			Dz1StrA_delAndSetNull(dst);
			(*dst) = NULL;
		}
	}
	return ret;
}

ssize_t Dz1StrA32_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		size_t len = 0;
		u8_t flag = (src == NULL || (len = strlen(src)) == 0) ? 0 : 1;

		DZ1_STREAM_WRITE1(dst, flag, errp, ret);
		if (flag)
		{
			DZ1_STREAM_WRITE4(dst, (u32_t)len, ed, errp, ret);
			DZ1_STREAM_WRITE(dst, (u8_t *)src, len, errp, ret);
		}
	}
	return ret;
}

ssize_t Dz1StrAN32_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		str_t temp = NULL;
		u32_t len;
		Dz1StrA_delAndSetNull(dst);
		DZ1_STREAM_READ4(&len, src, ed, errp, ret);
		if (len > 0)
		{
			if (( (*dst) = temp = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
			DZ1_STREAM_READ((u8_t *)temp, len, src, errp, ret);
		}
	}
	return ret;
}

ssize_t Dz1StrAN32_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		size_t len = src == NULL ? 0 : strlen(src);

		DZ1_STREAM_WRITE4(dst, (u32_t)len, ed, errp, ret);
		DZ1_STREAM_WRITE(dst, (u8_t *)src, len, errp, ret);
	}
	return ret;
}

ssize_t Dz1StrAX_read(str_t *dst, Dz1Stream *src, size_t fixed_len, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	str_t temp = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || fixed_len == 0) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((temp = (str_t)Dz1Calloc(sizeof(char), fixed_len + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&temp);

		if ((sz = Dz1Stream_read(src, (u8_t *)temp, fixed_len, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else
		{
			Dz1StrA_delAndSetNull(dst);
			if (( (*dst) = Dz1Str_dup(temp, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
			else 
			{
				ret += sz;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&temp);
	}
	return ret;
}

ssize_t Dz1StrAX_write(Dz1Stream *dst, str_t src, size_t fixed_len, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		size_t len = (src == NULL || src[0] == 0) ? 0 : strlen(src);

		size_t write_len = fixed_len < len ? fixed_len : len;
		size_t pad_len = fixed_len - write_len;

		if (write_len) DZ1_STREAM_WRITE(dst, (u8_t *)src, write_len, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, Dz1Stream_writePad(dst, (u32_t)pad_len, errp), errp);
	}
	return ret;
}
// Dz1StrA Stream
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1StrA?UTF8_read
static ssize_t _Dz1StrAUTF8_read(str_t *dst, Dz1Stream *src, u32_t len, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t *utf8 = NULL;
	if ((utf8 = (u8_t *)Dz1Calloc(sizeof(u8_t), len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if ((sz = Dz1Stream_read(src, utf8, len, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else if ((*dst = (str_t)Dz1String_conv(utf8, len, "UTF-8", "EUC-KR", NULL)) == NULL) { ERR_SET_OUT(errp, EFAULT); ret = -1; }
		else
		{
			ret += sz;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return ret;
}

ssize_t Dz1StrA16UTF8_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u16_t len;
		ssize_t sz = 0;

		Dz1StrA_delAndSetNull(dst);					// init
		DZ1_STREAM_READ2(&len, src, ed, errp, ret);	// read length 2
		if (len) DZ1_IO_STREAM_FUNC(ret, _Dz1StrAUTF8_read(dst, src, (u32_t)len, errp), errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

ssize_t Dz1StrA32UTF8_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u32_t len;
		ssize_t sz = 0;

		Dz1StrA_delAndSetNull(dst);					// init
		DZ1_STREAM_READ4(&len, src, ed, errp, ret);	// read length 4
		if (len) DZ1_IO_STREAM_FUNC(ret, _Dz1StrAUTF8_read(dst, src, len, errp), errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}
// Dz1StrA?UTF8_read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1StrA?UTF8_write
ssize_t Dz1StrA16UTF8_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	u8_t *utf8 = NULL;
	size_t utf8_size = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src == NULL || src[0] == 0) DZ1_STREAM_WRITE4(dst, 0, ed, errp, ret);	// 0 length
	else if ((utf8 = (u8_t *)Dz1String_conv(src, strlen(src) * sizeof(char), "EUC-KR", "UTF-8", &utf8_size)) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if (utf8_size > 0xFFFF) { ERR_SET_OUT(errp, E2BIG); ret = -1; }
		else if ((sz = Dz1Stream_write2(dst, (u16_t)utf8_size, ed, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else
		{
			ret += sz;
			if ((sz = Dz1Stream_write(dst, utf8, utf8_size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				ret += sz;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return ret;
}

ssize_t Dz1StrA32UTF8_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	u8_t *utf8 = NULL;
	size_t utf8_size = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src == NULL || src[0] == 0) DZ1_STREAM_WRITE4(dst, 0, ed, errp, ret);	// 0 length
	else if ((utf8 = (u8_t *)Dz1String_conv(src, strlen(src) * sizeof(char), "EUC-KR", "UTF-8", &utf8_size)) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if ((sz = Dz1Stream_write4(dst, (u32_t)utf8_size, ed, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else
		{
			ret += sz;
			if ((sz = Dz1Stream_write(dst, utf8, utf8_size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				ret += sz;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return ret;
}
// Dz1StrA?UTF8_write
///////////////////////////////////////////////////////////////////////////////

ssize_t Dz1Time_writeB(Dz1Stream *dst, time_t *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		struct tm *tm_p = localtime(src);
		if (tm_p == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
		else
		{
			struct tm tmSrc = *tm_p;
			DZ1_IO_STREAM_FUNC(ret, Dz1TM_writeB(dst, &tmSrc, errp), errp);
		}
	}
	return ret;
}

ssize_t Dz1Time_writeL(Dz1Stream *dst, time_t *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		struct tm *tm_p = localtime(src);
		if (tm_p == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
		else
		{
			struct tm tmSrc = *tm_p;
			DZ1_IO_STREAM_FUNC(ret, Dz1TM_writeL(dst, &tmSrc, errp), errp);
		}
	}
	return ret;
}


ssize_t Dz1Time_readB(time_t *dst, Dz1Stream *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		struct tm tmStamp;
		DZ1_IO_STREAM_FUNC(ret, Dz1TM_readB(&tmStamp, src, errp), errp);
		(*dst) = mktime(&tmStamp);
	}
	return ret;
}

ssize_t Dz1Time_readL(time_t *dst, Dz1Stream *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		struct tm tmStamp;
		DZ1_IO_STREAM_FUNC(ret, Dz1TM_readL(&tmStamp, src, errp), errp);
		(*dst) = mktime(&tmStamp);
	}
	return ret;
}

ssize_t Dz1TM_writeB(Dz1Stream *dst, struct tm *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE2(dst, (u16_t)(src->tm_year & 0xFFFF), Dz1IOStreamEndian_big, errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_mon & 0xFF), errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_mday & 0xFF), errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_hour & 0xFF), errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_min & 0xFF), errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_sec & 0xFF), errp, ret);
	}
	return ret;
}

ssize_t Dz1TM_writeL(Dz1Stream *dst, struct tm *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE2(dst, (u16_t)(src->tm_year & 0xFFFF), Dz1IOStreamEndian_little, errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_mon & 0xFF), errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_mday & 0xFF), errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_hour & 0xFF), errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_min & 0xFF), errp, ret);
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->tm_sec & 0xFF), errp, ret);
	}
	return ret;
}

ssize_t Dz1TM_readB(struct tm *dst, Dz1Stream *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u16_t v16; u8_t v8;
		DZ1_STREAM_READ2(&v16, src, Dz1IOStreamEndian_big, errp, ret); dst->tm_year = (int)v16;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_mon = (int)v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_mday = (int)v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_hour = (int)v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_min = (int)v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_sec = (int)v8;
	}
	return ret;
}

ssize_t Dz1TM_readL(struct tm *dst, Dz1Stream *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u16_t v16; u8_t v8;
		DZ1_STREAM_READ2(&v16, src, Dz1IOStreamEndian_little, errp, ret); dst->tm_year = (int)v16;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_mon = (int)v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_mday = (int)v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_hour = (int)v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_min = (int)v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret); dst->tm_sec = (int)v8;
	}
	return ret;
}

