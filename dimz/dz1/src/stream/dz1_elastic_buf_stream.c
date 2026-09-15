#include <dz1_int.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>

#include "../kernel/dz1_thread_stdio.h"
#include "../struct/dz1_elastic_buf.h"
#include "dz1_elastic_buf_stream.h"

///////////////////////////////////////////////////////////////////////////////
// Position of Elastic Buffer Stream
Dz1ElasticBufPos *Dz1ElasticBufPos_new(u32_t id, Dz1ElasticBufEntry *entry, u32_t pos, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBufPos *ret = (Dz1ElasticBufPos *)Dz1Calloc(sizeof(Dz1ElasticBufPos), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->id = id;
		ret->entry = entry;
		ret->pos = pos;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1ElasticBufPos_del(Dz1ElasticBufPos *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1ElasticBufPos_dump(Dz1ElasticBufPos *p, int tab)
{
	if (p == NULL) Dz1Thread_eprintf("NULL\n");
	else
	{
		Dz1Thread_eprintf("{\n"); tab++;
		Dz1Thread_etprintf(tab, "id = %u\n", p->id);
		Dz1Thread_etprintf(tab, "entry = %p\n", p->entry);
		Dz1Thread_etprintf(tab, "pos = %u\n", p->pos);
		Dz1Thread_etprintf(--tab, "}\n");
	}
}

int Dz1ElasticBufPos_cmp(Dz1ElasticBufPos *a, Dz1ElasticBufPos *b)
{
	int ret = 0;
	if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else ret = a->id - b->id;
	return ret;
}

// Position of Elastic Buffer Stream
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Elastic Buffer Stream
Dz1ElasticBufStream *Dz1ElasticBufStream_new(Dz1ElasticBuf *elastic, bool_t elastic_is_ref, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1ElasticBufStream *__internal_ret = (Dz1ElasticBufStream *)Dz1Calloc(sizeof(Dz1ElasticBufStream), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1ElasticBufStream_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->user_cursors = Dz1AATree_new((Dz1CmpFunc)Dz1ElasticBufPos_cmp,
														  (Dz1DelFunc)Dz1ElasticBufPos_del,
														  (Dz1DumpFunc)Dz1ElasticBufPos_dump, errp)) == NULL) ERR_OUT(errp);
		__internal_ret->elastic = elastic;
		__internal_ret->elastic_is_ref = elastic_is_ref;
		__internal_ret->alloc_id = 0;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ElasticBufStream_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1ElasticBufStream_del(Dz1ElasticBufStream *p)
{
	if (p == NULL) return;
	if (p->elastic)
	{
		if (p->elastic_is_ref == FALSE)
			Dz1ElasticBuf_del(p->elastic);
	}
	Dz1AATree_delAndSetNull(&p->user_cursors);
	Dz1Free(p);
}

void Dz1ElasticBufStream_dump(Dz1ElasticBufStream *p, int tab)
{
	if (!p) { Dz1Thread_eprintf("NULL\n"); return; }
	Dz1Thread_eprintf("{\n"); tab++;

	if (p->elastic == NULL) Dz1Thread_etprintf(tab, "elastic = NULL\n");
	else { Dz1Thread_etprintf(tab, "elastic = "); Dz1ElasticBuf_dump(p->elastic, tab); }

	Dz1Thread_etprintf(tab, "elastic_is_ref = "); Dz1Bool_dump(&p->elastic_is_ref, tab);

	Dz1Thread_etprintf(tab, "alloc_id = %u\n", p->alloc_id);
	if (p->user_cursors == NULL) Dz1Thread_etprintf(tab, "user_cursors = NULL\n");
	else { Dz1Thread_etprintf(tab, "user_cursors = "); Dz1AATree_dump(p->user_cursors, tab); }

	Dz1Thread_etprintf(--tab, "}\n");
}
// Elastic Buffer Stream
///////////////////////////////////////////////////////////////////////////////

// static Dz1Error _initial_io_setup(Dz1ElasticBufStream *p)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	if (p->curr.entry == NULL)
// 	{	// 작업 위치가 정해지지 않음 -> 무조건 맨 처음으로 설정
// 		Dz1ElasticBuf *buf = p->elastic;
// 		if (buf == NULL) ERR_SET_OUT(errp, EINVAL);
// 		else if (buf->head == NULL)
// 		{	// 비어있는 Buffer
// 			if ((p->curr.entry = Dz1ElasticBuf_alloc(buf, Dz1ElasticBufAppendSide_toTail, errp)) == NULL) ERR_OUT(errp);
// 			else
// 			{
// 				p->curr.pos = 0;
// 				Dz1Error_set(errp, 0);
// 			}
// 		}
// 		else
// 		{	// 처음으로 설정
// 			p->curr.entry = buf->head;
// 			p->curr.pos = 0;
// 		}
// 	}
// 	return err;
// }

static u32_t alloc_seq = 0;
u32_t Dz1ElasticBufStream_getCursor(Dz1ElasticBufStream *p, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t alloc_h = (alloc_seq++ << 16) & 0xFFFF0000;
		u32_t alloc_id = alloc_h | (p->alloc_id & 0xFFFF);
		Dz1ElasticBufPos *pos = Dz1ElasticBufPos_new(alloc_id, NULL, 0, errp);
		if (pos == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1ElasticBufPos_delAndSetNull, (void *)&pos);
			if ((*errp = Dz1AATree_insert(p->user_cursors, (void *)pos)).code) ERR_OUT(errp);
			else
			{
				p->alloc_id++;
				pos = NULL;
				Dz1Error_set(errp, 0);
				ret = alloc_id;
			}
			pthread_cleanup_pop(1); // (Dz1ElasticBufPos_delAndSetNull, (void *)&pos);
		}
	}
	return ret;
}

void Dz1ElasticBufStream_putCursor(Dz1ElasticBufStream *p, u32_t stream_id)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1ElasticBufPos key = { stream_id }, *node = NULL;
		if ((node = (Dz1ElasticBufPos *)Dz1AATree_extract(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else
		{
			pthread_cleanup_push(Dz1ElasticBufPos_delAndSetNull, (void *)&node);
			// Dz1Thread_eprintf("Dz1ElasticBufStream_putCursor() : put cursor = %08X\n", node->id);
			pthread_cleanup_pop(1); // (Dz1ElasticBufPos_delAndSetNull, (void *)&node);
		}
	}
}

static bool_t _pos_read_init(Dz1ElasticBufStream *p, Dz1ElasticBufPos *cursor)
{
	bool_t ret = FALSE;
	Dz1ElasticBuf *eb = p->elastic;
	if (cursor->entry == NULL)
	{	// 초기화 된 적이 없음
		if (eb->head != NULL)
		{
			cursor->entry = eb->head;
			cursor->pos = 0;
			ret = TRUE;
		}
		else
		{
			cursor->entry = NULL;
			cursor->pos = 0;
			ret = FALSE;
		}
	}
	else ret = TRUE;
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Elastic Buffer Stream Read
ssize_t Dz1ElasticBufStream_read(Dz1ElasticBufStream *p, u32_t stream_id, u8_t *dst, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL || dst == NULL || size == 0) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (p->elastic == NULL) ERR_SETOUT_RET(errp, EFAULT, -1);
	else if ((cursor = (Dz1ElasticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT_RET(errp, ENOENT, -1);
	else if (_pos_read_init(p, cursor) == FALSE) Dz1Error_set(errp, EPIPE);
	else
	{
		u8_t *dp = dst;

		Dz1ElasticBufEntry *i = cursor->entry;
		u32_t pos = i->data_start > cursor->pos ? i->data_start : cursor->pos;

		// Dz1Thread_eprintf("### Cursor = %p, entry = %p, pos = %u, ds = %u, size = %u\n", cursor, i, pos, i->data_start, i->data_end - pos);

		while(size)
		{
			if (i != NULL)
			{
				size_t readable_size = i->data_end - pos;
				size_t copy_size = size < readable_size ? size : readable_size;

				Dz1Binary *bin = i->buf;
				u8_t *sp = bin->data + pos;
				memcpy(dp, sp, copy_size);

				dp += copy_size;
				pos += (u32_t)copy_size;	// move position

				size -= copy_size;			// decrease total amount
				ret += (ssize_t)copy_size;	// increase work size

				readable_size -= copy_size;	// decrease readable size
				if (readable_size == 0)
				{	// no more data in this node
					if (i->next == NULL)
						break;	// no more next mode
					else
					{	// move to next node & init offset
						i = i->next;
						pos = i->data_start;
					}
				}
			}
			else break;
		}
		cursor->entry = i;
		cursor->pos = pos;

//		Dz1Thread_eprintf("Dz1ElasticBufStream_read() : %d\n", ret);
		if (ret == 0) Dz1Error_set(errp, EPIPE);
	}
	return ret;
}
// Elastic Buffer Stream Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Elastic Buffer Stream Write
typedef struct Dz1ElasticBufSource
{
	u8_t *data;
	size_t size;
} Dz1ElasticBufSource;

static ssize_t Dz1ElasticBufStream_writeAppend(Dz1ElasticBufStream *p, Dz1ElasticBufPos *cursor, Dz1ElasticBufSource *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1ElasticBufEntry *i = cursor->entry;
	u32_t pos = i->data_start > cursor->pos ? i->data_start : cursor->pos;

	Dz1Binary *bin = NULL;
	size_t writable_size = 0, copy_size = 0;

	while(src->size)
	{
		bin = i->buf;
		writable_size = bin->size - pos; // 다음 노드가 없는경우 해당 Node의 Buffer끝 까지
		if (writable_size > 0)
		{
			u8_t *dp = bin->data + pos;
			copy_size = src->size < writable_size ? src->size : writable_size;
			memcpy(dp, src->data, copy_size);
			src->data += copy_size;
			pos += (u32_t)copy_size;

			src->size -= copy_size;
			ret += (ssize_t)copy_size;

			writable_size -= copy_size;
			if (i->data_end < pos) i->data_end = pos; // data_end 조정
		}

		if (writable_size == 0 && src->size)
		{	// 다음이 없으므로
			i = Dz1ElasticBuf_alloc(p->elastic, Dz1ElasticBufAppendSide_toTail, errp);
			pos = 0;
		}
	}
	cursor->entry = i;
	cursor->pos = pos;

	return ret;
}

static ssize_t Dz1ElasticBufStream_writeOverwrite(Dz1ElasticBufStream *p, Dz1ElasticBufPos *cursor, Dz1ElasticBufSource *src, Dz1Error *err)
{	// 다음이 있음으로
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	u8_t *dp = NULL;

	Dz1ElasticBufEntry *i = cursor->entry;
	u32_t pos = i->data_start > cursor->pos ? i->data_start : cursor->pos;	// 시작위치 조정

	Dz1Binary *bin = NULL;
	size_t writable_size = 0, copy_size = 0;

	while(src->size)
	{
		bin = i->buf;
		writable_size = i->data_end - pos; // 다음 노드가 있는경우 해당 노드의 유효Data 끝 까지만
		if (writable_size > 0)
		{
			dp = bin->data + pos;
			copy_size = src->size < writable_size ? src->size : writable_size;
			memcpy(dp, src->data, copy_size);
			pos += (u32_t)copy_size;
			src->data += copy_size;
			src->size -= copy_size;

			writable_size -= copy_size;
			ret += (ssize_t)copy_size;
		}

		if (writable_size == 0)
		{	// 다음이 있는지 없는지 모름으로
			if (i->next == NULL)
			{
				// 다음 노드가 없으면 여기서 중단
				break;
			}
			else
			{
				i = i->next;
				pos = i->data_start;
			}
		}
	}
	cursor->entry = i;
	cursor->pos = pos;

	Dz1Error_set(errp, 0);

	return ret;
}

static Dz1Error _pos_write_init(Dz1ElasticBufStream *p, Dz1ElasticBufPos *cursor)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ElasticBuf *eb = p->elastic;
	if (cursor->entry == NULL)
	{
		if (eb->head == NULL)
		{
			if ((cursor->entry = Dz1ElasticBuf_alloc(eb, Dz1ElasticBufAppendSide_toTail, errp)) == NULL) ERR_OUT(errp);
			else cursor->pos = 0;
		}
		else
		{
			cursor->entry = eb->head;
			cursor->pos = 0;
		}
	}
	return err;
}

ssize_t Dz1ElasticBufStream_write(Dz1ElasticBufStream *p, u32_t stream_id, u8_t *src, size_t size, Dz1Error *err)
{	// 겹쳐 쓰거나, 추가하거나
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL || src == NULL || size == 0) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (p->elastic == NULL) ERR_SETOUT_RET(errp, EFAULT, -1);
	else if ((cursor = (Dz1ElasticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT_RET(errp, ENOENT, -1);
	else if ((*errp = _pos_write_init(p, cursor)).code) ERR_OUT_RET(errp, -1);
	else
	{
		Dz1ElasticBufSource acc = { src , size };
		Dz1ElasticBufEntry *current = cursor->entry;
		if (current->next == NULL)
		{	// 늘어나는 모드
			ret = Dz1ElasticBufStream_writeAppend(p, cursor, &acc, errp);
		}
		else
		{	// 겹쳐쓰기 모드
			if ((ret = Dz1ElasticBufStream_writeOverwrite(p, cursor, &acc, errp)) < 0) ERR_OUT_RET(errp, -1);
			else if (acc.size > 0)
			{	// Buffer의 끝에 닿았으나 쓸 Data가 남음 -> 추가모드
				ssize_t status = 0;
				if ((status = Dz1ElasticBufStream_writeAppend(p, cursor, &acc, errp)) < 0) ERR_OUT_RET(errp, -1);
				else ret += status;
			}
		}
	}
	return ret;
}
// Elastic Buffer Stream Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Elastic Buffer Stream Seek
typedef struct ElasticBufStreamSeekCancelArg
{
	Dz1ElasticBufPos *offset;
	Dz1ElasticBufEntry *backup_entry;
	u32_t backup_pos;
} ElasticBufStreamSeekCancelArg;

static void _seek_cancel(void *ptr)
{
	ElasticBufStreamSeekCancelArg *arg = (ElasticBufStreamSeekCancelArg *)ptr;
	Dz1ElasticBufPos *offset = arg->offset;
	offset->entry = arg->backup_entry;
	offset->pos = arg->backup_pos;
}

static Dz1Error _seek_forward(Dz1ElasticBufStream *p, Dz1ElasticBufPos *offset, s64_t diff)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (offset == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1ElasticBufEntry *i = offset->entry;
		u32_t pos = offset->pos;

		ElasticBufStreamSeekCancelArg arg = { offset, offset->entry, offset->pos };
		pthread_cleanup_push(_seek_cancel, (void *)&arg);

		if (diff < 0) diff = -diff;

		while(diff > 0 && errp->code == 0)
		{
			if (i == NULL) ERR_SET_OUT(errp, EPIPE);
			else
			{
				s64_t ahead_size = i->data_end - offset->pos;
				s64_t move_size = diff < ahead_size ? diff : ahead_size;

				pos += (u32_t)(move_size & 0xFFFFFFFF);
				diff -= move_size;
				ahead_size -= move_size;

				if (ahead_size == 0 && diff > 0)
				{
					i = i->next;
					if (i == NULL) ERR_SET_OUT(errp, EPIPE);
					else pos = i->data_start;
				}
			}
		}
		offset->entry = i;
		offset->pos = pos;
		pthread_cleanup_pop(errp->code); // (_seek_cancel, (void *)&arg);
	}
	return err;
}

static Dz1Error _seek_backward(Dz1ElasticBufStream *p, Dz1ElasticBufPos *offset, s64_t diff)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (offset == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1ElasticBufEntry *i = offset->entry;
		u32_t pos = offset->pos;

		ElasticBufStreamSeekCancelArg arg = { offset, offset->entry, offset->pos };
		pthread_cleanup_push(_seek_cancel, (void *)&arg);

		if (diff < 0) diff = -diff;

		while(diff > 0 && errp->code == 0)
		{
			if (i == NULL) ERR_SET_OUT(errp, EPIPE);
			else
			{
				s64_t back_size = offset->pos - i->data_start;
				s64_t move_size = diff < back_size ? diff : back_size;
				pos -= (u32_t)(move_size & 0xFFFFFFFF);
				diff -= back_size;
				back_size -= move_size;
				if (back_size == 0 && diff > 0)
				{
					i = i->prev;
					if (i == NULL) ERR_SET_OUT(errp, EPIPE);
					else pos = i->data_end;
				}
			}
		}
		offset->entry = i;
		offset->pos = pos;

		pthread_cleanup_pop(errp->code); // (_seek_cancel, (void *)&arg);
	}
	return err;
}

static Dz1Error _seek_from_cur(Dz1ElasticBufStream *p, Dz1ElasticBufPos *cursor, s64_t diff)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_pos_read_init(p, cursor) == FALSE) Dz1Error_set(errp, EPIPE);
	else if (diff < 0)
	{	// backward
		diff = -diff;
		if ((*errp = _seek_backward(p, cursor, diff)).code) ERR_OUT(errp);
	}
	else if (diff > 0)
	{	// forward
		if ((*errp = _seek_forward(p, cursor, diff)).code) ERR_OUT(errp);
	}
	return err;
}

static Dz1Error _seek_from_set(Dz1ElasticBufStream *p, Dz1ElasticBufPos *cursor, s64_t movement)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_pos_read_init(p, cursor) == FALSE) Dz1Error_set(errp, EPIPE);
	else if (movement < 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1ElasticBuf *eb = p->elastic;
		Dz1ElasticBufPos offset_temp = { cursor->id, eb->head, eb->head->data_start };
		if ((*errp = _seek_forward(p, &offset_temp, movement)).code) ERR_OUT(errp);
		else (*cursor) = offset_temp;
	}
	return err;
}

static Dz1Error _seek_from_end(Dz1ElasticBufStream *p, Dz1ElasticBufPos *cursor, s64_t movement)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_pos_read_init(p, cursor) == FALSE) Dz1Error_set(errp, EPIPE);
	else if (movement < 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1ElasticBuf *eb = p->elastic;
		Dz1ElasticBufEntry *tail = eb->tail;
		Dz1ElasticBufPos offset_temp = { cursor->id, tail, tail->data_end };
		if ((*errp = _seek_backward(p, &offset_temp, movement)).code) ERR_OUT(errp);
		else (*cursor) = offset_temp;
	}
	return err;
}

Dz1Error Dz1ElasticBufStream_seek(Dz1ElasticBufStream *p, u32_t stream_id, s64_t movement, int origin)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ElasticBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->elastic == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((cursor = (Dz1ElasticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT(errp, ENOENT);
	// else if ((*errp = _initial_io_setup(p)).code) ERR_OUT(errp);
	else
	{
		switch(origin)
		{
		case SEEK_CUR:
			if ((*errp = _seek_from_cur(p, cursor, movement)).code) ERR_OUT(errp);
			break;
		case SEEK_SET:
			if ((*errp = _seek_from_set(p, cursor, movement)).code)
			{
				errp = errp;
			}
			break;
		case SEEK_END:
			if ((*errp = _seek_from_end(p, cursor, movement)).code) ERR_OUT(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return err;
}
// Elastic Buffer Stream Seek
///////////////////////////////////////////////////////////////////////////////

s64_t Dz1ElasticBufStream_tell(Dz1ElasticBufStream *p, u32_t stream_id, Dz1Error *err)
{
	Dz1ElasticBuf *eb = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBufPos key = { stream_id }, *cursor = NULL;

	if (p == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((eb = p->elastic) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
	else if ((cursor = (Dz1ElasticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT_RET(errp, ENOENT, -1);
	else if (_pos_read_init(p, cursor) == FALSE) { Dz1Error_set(errp, EPIPE); return 0; }
	else
	{
		s64_t ret = Dz1ElasticBuf_getDistance(eb, cursor->entry, cursor->pos, errp);
		if (ret < 0) ERR_OUT(errp);
		return ret;
	}
    return -1;
}

bool_t Dz1ElasticBufStream_isEOF(Dz1ElasticBufStream *p, u32_t stream_id)
{
	bool_t ret = TRUE;
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ElasticBufPos key = { stream_id }, *cursor = NULL;

	if (p == NULL) ERR_SET_OUT_RET(errp, EINVAL, TRUE);
	else if (p->elastic == NULL) ERR_SET_OUT_RET(errp, EFAULT, TRUE);
	else if ((cursor = (Dz1ElasticBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT_RET(errp, ENOENT, TRUE);
	else if (_pos_read_init(p, cursor) == FALSE) { Dz1Error_set(errp, EPIPE); return TRUE; }
	else
	{
		Dz1ElasticBufEntry *i = cursor->entry;
		if (i == NULL) ERR_SET_OUT_RET(errp, EFAULT, TRUE);
		else if (i->next != NULL) ret = FALSE;
		else  if (cursor->pos == i->data_end) ret = TRUE;
		else ret = FALSE;
	}
	return ret;
}

typedef struct TakeCursorArg
{
	Dz1AATree		*dst_cursor;
	size_t			 drain_size;
	Dz1ElasticBuf	*eb;
} TakeCursorArg;

static Dz1Error _take_cursors(void *ptr, void *data)
{	// 뽑아내기 전에, 뽑아내면 Cursor 위치가 사라지는 애들을 찾는다
	DZ1_ERROR_SAFE_VAR(errp, err);
	TakeCursorArg *arg = (TakeCursorArg *)ptr;
	Dz1ElasticBufPos *p = (Dz1ElasticBufPos *)data;

	s64_t distance = Dz1ElasticBuf_getDistance(arg->eb, p->entry, p->pos, errp);
	if (distance < 0) Dz1Error_set(errp, 0);
	else if (arg->drain_size >= (size_t)distance)
	{
		if ((*errp = Dz1AATree_insert(arg->dst_cursor, data)).code) ERR_OUT(errp);
	}
	return err;
}

static Dz1Error _reset_user_curser(void *ptr, void *_data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1ElasticBuf *eb = (Dz1ElasticBuf *)ptr;
	Dz1ElasticBufPos *p = (Dz1ElasticBufPos *)_data;

	if (eb->head == NULL)
	{
		p->entry = NULL;
		p->pos = 0;
	}
	else
	{
		p->entry = eb->head;
		p->pos = eb->head->data_start;
	}
	Dz1Error_set(errp, 0);
//	Dz1Thread_eprintf("### Cursor = %p, entry = %p, pos = %u\n", p, p->entry, p->pos);

	return err;
}

ssize_t Dz1ElasticBufStream_drain(Dz1ElasticBufStream *p, size_t drain_size, u8_t *opt_drain_buf, Dz1Error *err)
{	// ELB의 Position은 Node, offset으로 되어 있음으로
	// Drain시 drain size 보다 적은 Position을 0의 위치로 이동시킨다
	ssize_t ret = 0, total_size = 0;
	Dz1ElasticBuf *eb = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (p == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((eb = p->elastic) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
	else if ((total_size = Dz1ElasticBuf_getDataSize(eb, errp)) < 0) ERR_OUT_RET(errp, -1);
	else if (drain_size < (size_t)total_size)
	{	// 뽑아낸 뒤 남는 데이터가 있다
		Dz1AATree *dst_cursors = Dz1AATree_new((Dz1CmpFunc)Dz1ElasticBufPos_cmp,
											   (Dz1DelFunc)NULL,
											   (Dz1DumpFunc)Dz1ElasticBufPos_dump, errp);
		if (dst_cursors == NULL) ERR_OUT(errp);
		else
		{
			//ssize_t status = 0;
			TakeCursorArg arg = { dst_cursors, drain_size, eb };
			pthread_cleanup_push(Dz1AATree_delAndSetNull, (void *)&dst_cursors);

			if ((*errp = Dz1AATree_travel(p->user_cursors, _take_cursors, (void *)&arg)).code) { ERR_OUT(errp); ret = -1; }
			else if ((ret = Dz1ElasticBuf_pop(eb, opt_drain_buf, drain_size, errp)) < 0) ERR_OUT(errp);
			else
			{
//				Dz1ElasticBufEntry *head = eb->head;
//				if (head) Dz1Thread_eprintf("### ELB(R) = %p, head = %p, pos = %u, size = %u\n", eb, head, head->data_start, head->data_end - head->data_start);
//				else Dz1Thread_eprintf("### ELB(R) = %p, head = NULL\n", eb);

				Dz1AATree_travel(dst_cursors, _reset_user_curser, eb);
			}

			pthread_cleanup_pop(1); // (Dz1AATree_delAndSetNull, (void *)&dst_cursors);
		}
	}
	else
	{	// data가 다 비워짐
		if ((ret = Dz1ElasticBuf_pop(eb, opt_drain_buf, total_size, errp)) < 0) ERR_OUT(errp);
		else
		{
//			Dz1ElasticBufEntry *head = eb->head;
//			if (head) Dz1Thread_eprintf("### ELB(E) = %p, head = %p, pos = %u, size = %u\n", eb, head, head->data_start, head->data_end - head->data_start);
//			else Dz1Thread_eprintf("### ELB(E) = %p, head = NULL\n", eb);

			Dz1AATree_travel(p->user_cursors, _reset_user_curser, eb);
		}
	}
	return ret;
}

