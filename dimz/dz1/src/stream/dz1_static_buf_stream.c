#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_static_buf_stream.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1StaticBufPos API
Dz1StaticBufPos *Dz1StaticBufPos_new(u32_t id, u32_t pos, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1StaticBufPos *ret = (Dz1StaticBufPos *)Dz1Calloc(sizeof(Dz1StaticBufPos), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->id = id;
		ret->pos = pos;
		ERR_CLEAR(errp);
	}
	return ret;
}

Dz1StaticBufPos *Dz1StaticBufPos_clone(Dz1StaticBufPos *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1StaticBufPos *ret = (Dz1StaticBufPos *)Dz1Calloc(sizeof(Dz1StaticBufPos), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StaticBufPos_delAndSetNull, (void *)&ret);

		ret->id = src->id;
		ret->pos = src->pos;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1StaticBufPos_del(Dz1StaticBufPos *p)
{
	if (!p) return;
	// Additional delete code here
	Dz1Free(p);
}

void Dz1StaticBufPosA_dump(Dz1StaticBufPos *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%08X=%u\n", p->id, p->pos);
}

void Dz1StaticBufPosA_fdump(FILE *fp, Dz1StaticBufPos *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%08X=%u\n", p->id, p->pos);
}
#ifndef UNIX_SYSTEM
void Dz1StaticBufPosW_dump(Dz1StaticBufPos *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%08X=%u\n", p->id, p->pos);
}

void Dz1StaticBufPosW_fdump(FILE *fp, Dz1StaticBufPos *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%08X=%u\n", p->id, p->pos);
}
#endif
int Dz1StaticBufPos_cmp(Dz1StaticBufPos *a, Dz1StaticBufPos *b)
{
	int ret = 0;
	if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else
	{
		// Additional compare code here
		ret = a->id - b->id;
	}
	return ret;
}
// Dz1StaticBufPos API
////////////////////////////////////////////////////////////////////////////////

Dz1StaticBufStream *Dz1StaticBufStream_new(u8_t *buf, size_t size, bool_t buf_is_ref, u32_t buf_filled, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1StaticBufStream *ret = NULL;
	if (buf_is_ref == TRUE && (buf == NULL || size == 0)) ERR_SET_OUT(errp, EINVAL);
	else if (buf_is_ref == FALSE && buf != NULL && size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1StaticBufStream *)Dz1Calloc(sizeof(Dz1StaticBufStream), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StaticBufStream_delAndSetNull, (void *)&ret);

		ret->buf_is_ref = buf_is_ref;
		ret->buf_size = size;
		ret->buf_filled = buf_filled == (u32_t)-1 ? (u32_t)size : buf_filled;
		ret->alloc_id = 0;
		if ((ret->user_cursors = Dz1AATree_new((Dz1CmpFunc)Dz1StaticBufPos_cmp,
											   (Dz1DelFunc)Dz1StaticBufPos_del,
											   (Dz1DumpFunc)Dz1StaticBufPos_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (buf_is_ref)
				ret->buf = buf;
			else
			{	// not references
				if (buf == NULL)
				{	// size will 0 or more
					if (size > 0)
					{	// buf가 NULL이면서 size가 0이 아니면 Malloc
						if ((ret->buf = (u8_t *)Dz1Malloc(size, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					// size == 0
					else Dz1Error_set(errp, 0);
				}
				else // if (buf != NULL)
				{	// size will not zero
					if ((ret->buf = (u8_t *)Dz1Malloc(size, errp)) == NULL) ERR_OUT(errp);
					else
					{
						memcpy(ret->buf, buf, buf_filled);
						Dz1Error_set(errp, 0);
					}
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1StaticBufStream_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1StaticBufStream_del(Dz1StaticBufStream *p)
{
	if (p == NULL) return;
	if (p->buf_is_ref == FALSE) Dz1Memory_freeAndSetNull(&p->buf);
	if (p->user_cursors != NULL) Dz1AATree_delAndSetNull(&p->user_cursors);
	Dz1Free(p);
}

void Dz1StaticBufStreamA_dump(Dz1StaticBufStream *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%u/%u\n", p->buf_filled, p->buf_size);
}
#ifndef UNIX_SYSTEM
void Dz1StaticBufStreamW_dump(Dz1StaticBufStream *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%u/%u\n", p->buf_filled, p->buf_size);
}
#endif
static u32_t alloc_seq = 0;
u32_t Dz1StaticBufStream_getCursor(Dz1StaticBufStream *p, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t alloc_h = (alloc_seq++ << 16) & 0xFFFF0000;
		u32_t alloc_id = alloc_h | (p->alloc_id & 0xFFFF);
		Dz1StaticBufPos *pos = Dz1StaticBufPos_new(alloc_id, 0, errp);
		if (pos == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1StaticBufPos_delAndSetNull, (void *)&pos);
			if ((*errp = Dz1AATree_insert(p->user_cursors, (void *)pos)).code) ERR_OUT(errp);
			else
			{
				pos = NULL;
				p->alloc_id++;
				Dz1Error_set(errp, 0);
				ret = alloc_id;
			}
			pthread_cleanup_pop(1); // (Dz1StaticBufPos_delAndSetNull, (void *)&pos);
		}
	}
	return ret;
}

void Dz1StaticBufStream_putCursor(Dz1StaticBufStream *p, u32_t stream_id)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1StaticBufPos key = { stream_id }, *node = NULL;
		if ((node = (Dz1StaticBufPos *)Dz1AATree_extract(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else
		{
			pthread_cleanup_push(Dz1StaticBufPos_delAndSetNull, (void *)&node);
//			Dz1Thread_eprintf("Dz1StaticBufStream_putCursor() : put cursor = %08X\n", node->id);
			pthread_cleanup_pop(1); // (Dz1StaticBufPos_delAndSetNull, (void *)&node);
		}
	}
}

ssize_t Dz1StaticBufStream_read(Dz1StaticBufStream *p, u32_t stream_id, u8_t *dst, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1StaticBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL || dst == NULL) 
		ERR_SETOUT_RET(errp, EINVAL, -1);
	else if ((cursor = (Dz1StaticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SETOUT_RET(errp, ENOENT, -1);
	else
	{
		u32_t left_size = p->buf_filled - cursor->pos;			// 남아있는 Data는 buffer_filled - pos
		u32_t copy_size = size < left_size ? (u32_t)size : left_size;
		if (copy_size == 0) Dz1Error_set(errp, EPIPE);
		else
		{
			u8_t *cp = p->buf + cursor->pos;
			memcpy(dst, cp, copy_size);
			cursor->pos += copy_size;
			ret += copy_size;
		}
	}
	return ret;
}

ssize_t Dz1StaticBufStream_write(Dz1StaticBufStream *p, u32_t stream_id, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1StaticBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL || src == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if ((cursor = (Dz1StaticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT_RET(errp, ENOENT, -1);
	else
	{
		u32_t left_size = (u32_t)(p->buf_size - cursor->pos);		// 남아있는 Space는 buffer_size - pos
		u32_t copy_size = size < left_size ? (u32_t)size : left_size;
		if (copy_size == 0) Dz1Error_set(errp, EPIPE);
		else
		{
			u8_t *cp = p->buf + cursor->pos;
			memcpy(cp, src, copy_size);
			cursor->pos += copy_size;

			if (p->buf_filled < cursor->pos) p->buf_filled = cursor->pos;

			ret += copy_size;
		}
	}
	return ret;
}

static Dz1Error _seek_forward(Dz1StaticBufStream *p, Dz1StaticBufPos *cursor, s64_t movement)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u32_t left_size = p->buf_filled - cursor->pos;		// 전진 가능 길이는 buf_filled - pos
	u64_t move_size;

	if (movement < 0) movement = -movement;
	move_size = movement;

	if (move_size > left_size) ERR_SET_OUT(errp, EPIPE);
	else cursor->pos += (u32_t)(move_size & 0xFFFFFFFF);

	return err;
}

static Dz1Error _seek_backward(Dz1StaticBufStream *p, Dz1StaticBufPos *cursor, s64_t movement)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u32_t left_size = cursor->pos;
	u64_t move_size;

	if (movement < 0) movement = -movement;
	move_size = movement;

	if (move_size > left_size) ERR_SET_OUT(errp, EPIPE);
	else cursor->pos -= (u32_t)(move_size & 0xFFFFFFFF);

	return err;
}

typedef struct SeekCancelArg
{
	Dz1StaticBufPos *p;
	u32_t old_pos;
} SeekCancelArg;

static void _seek_cancel(void *ptr)
{
	SeekCancelArg *arg = (SeekCancelArg *)ptr;
	arg->p->pos = arg->old_pos;
}

Dz1Error Dz1StaticBufStream_seek(Dz1StaticBufStream *p, u32_t stream_id, s64_t movement, int origin)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StaticBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((cursor = (Dz1StaticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		SeekCancelArg arg = { cursor, cursor->pos };
		switch(origin)
		{
		case SEEK_SET:
			cursor->pos = 0;
			pthread_cleanup_push(_seek_cancel, (void *)&arg);
			if ((*errp = _seek_forward(p, cursor, movement)).code) ERR_OUT(errp);
			pthread_cleanup_pop(errp->code); // (_seek_cancel, (void *)&arg);
			break;
		case SEEK_CUR:
			if (movement < 0)
			{
				if ((*errp = _seek_backward(p, cursor, -movement)).code) ERR_OUT(errp);
			}
			else
			{
				if ((*errp = _seek_forward(p, cursor, movement)).code) ERR_OUT(errp);
			}
			break;
		case SEEK_END:
			cursor->pos = p->buf_filled;
			pthread_cleanup_push(_seek_cancel, (void *)&arg);
			if ((*errp = _seek_backward(p, cursor, movement)).code) ERR_OUT(errp);
			pthread_cleanup_pop(errp->code); // (_seek_cancel, (void *)&arg);
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return err;
}

s64_t Dz1StaticBufStream_tell(Dz1StaticBufStream *p, u32_t stream_id, Dz1Error *err)
{
	s64_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1StaticBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((cursor = (Dz1StaticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT_RET(errp, ENOENT, -1);
	else ret = (s64_t)cursor->pos;
	return ret;
}

static Dz1Error _cursor_drain(void *ptr, void *entry)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u32_t fit_size = *(u32_t *)ptr;
	Dz1StaticBufPos *cursor = (Dz1StaticBufPos *)entry;
	if (cursor == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (cursor->pos >= fit_size) cursor->pos -= fit_size;
		else cursor->pos = 0;
	}
	return err;
}

bool_t Dz1StaticBufStream_isEOF(Dz1StaticBufStream *p, u32_t stream_id)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StaticBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL) ERR_SET_OUT_RET(errp, EINVAL, TRUE);
	else if ((cursor = (Dz1StaticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT_RET(errp, ENOENT, TRUE);
	else
	{
		u32_t left_size = p->buf_filled - cursor->pos;
		ret = left_size == 0 ? TRUE : FALSE;
	}
	return ret;
}

ssize_t Dz1StaticBufStream_drain(Dz1StaticBufStream *p, size_t drain_size, u8_t *opt_drain_buf, Dz1Error *err)
{
	ssize_t ret = 0;
	u8_t *src = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	size_t fit_size = p->buf_filled < drain_size ? p->buf_filled : drain_size;
	size_t copy_size = p->buf_filled - fit_size;

	if (opt_drain_buf != NULL) memcpy(opt_drain_buf, p->buf, fit_size);

	src = &p->buf[fit_size];
	memcpy(p->buf, src, copy_size);
	p->buf_filled = (u32_t)copy_size;

	Dz1AATree_travel(p->user_cursors, _cursor_drain, (void *)&fit_size);

	Dz1Error_set(errp, 0);

	return ret;
}

