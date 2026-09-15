#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_stream_fifo.h>
#include <dz1_dynamic_buffer.h>

typedef struct Dz1DynamicBufferEntry
{
	struct Dz1DynamicBufferEntry	*prev;
	struct Dz1DynamicBufferEntry	*next;
	Dz1StreamFifo					*fifo;
} Dz1DynamicBufferEntry;

static void Dz1DynamicBufferEntry_del(Dz1DynamicBufferEntry *p)
{
	if (p == NULL) return;
	if (p->fifo != NULL) Dz1StreamFifo_delAndSetNull(&p->fifo);
	Dz1Free(p);
}

static void Dz1DynamicBufferEntry_delAndSetNull(void *ptr)
{
	Dz1DynamicBufferEntry **p = (Dz1DynamicBufferEntry **)ptr;
	Dz1DynamicBufferEntry_del(*p); *p = NULL;
}

static Dz1DynamicBufferEntry *Dz1DynamicBufferEntry_new(Dz1Error *errp)
{
	Dz1DynamicBufferEntry *ret = (Dz1DynamicBufferEntry *)Dz1Calloc(sizeof(Dz1DynamicBufferEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DynamicBufferEntry_delAndSetNull, (void *)&ret);
		if ((ret->fifo = Dz1StreamFifo_new(DZ1_DYNAMIC_BUFFER_FRAG_SIZE, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1DynamicBufferEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static ssize_t Dz1DynamicBufferEntry_push(Dz1DynamicBufferEntry *p, u8_t *data, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1StreamFifo_push(p->fifo, data, size, errp)) < 0) ERR_OUT(errp);
	return ret;
}

static ssize_t Dz1DynamicBufferEntry_pop(Dz1DynamicBufferEntry *p, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1StreamFifo_pop(p->fifo, buf, size, errp)) < 0) ERR_OUT(errp);
	return ret;
}

static ssize_t Dz1DynamicBufferEntry_getDataSize(Dz1DynamicBufferEntry *p, Dz1Error *errp)
{
	ssize_t ret = -1;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1StreamFifo_getDataSize(p->fifo, errp)) < 0) ERR_OUT(errp);
	return ret;
}

typedef struct _Dz1DynamicBuffer
{
	Dz1DynamicBufferEntry *head;
	Dz1DynamicBufferEntry *tail;
} _Dz1DynamicBuffer;

Dz1DynamicBuffer *Dz1DynamicBuffer_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1DynamicBuffer *ret = (_Dz1DynamicBuffer *)Dz1Calloc(sizeof(_Dz1DynamicBuffer), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1DynamicBuffer_del(Dz1DynamicBuffer *pDB)
{
	_Dz1DynamicBuffer *p = (_Dz1DynamicBuffer *)pDB;
	if (p == NULL) return;
	if (p->head != NULL)
	{
		Dz1DynamicBufferEntry *e = p->head, *next = NULL;
		while(e)
		{
			next = e->next;
			Dz1DynamicBufferEntry_del(e);
			e = next;
		}
	}
	Dz1Free(p);
}

void Dz1DynamicBuffer_delAndSetNull(void *ptr)
{
	_Dz1DynamicBuffer **p = (_Dz1DynamicBuffer **)ptr;
	Dz1DynamicBuffer_del(*p); *p = NULL;
}

static void _initialPushCleanup(void *ptr)
{
	_Dz1DynamicBuffer *p = (_Dz1DynamicBuffer *)ptr;
	Dz1DynamicBufferEntry_del(p->head);
	p->head = p->tail = NULL;
}

ssize_t Dz1DynamicBuffer_push(Dz1DynamicBuffer *pDB, u8_t *data, size_t size, Dz1Error *err)
{
	ssize_t ret = -1;
	_Dz1DynamicBuffer *p = (_Dz1DynamicBuffer *)pDB;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->head == NULL)
	{
		if ((p->head = p->tail = Dz1DynamicBufferEntry_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(_initialPushCleanup, (void *)p);
			if ((ret = Dz1DynamicBuffer_push(p, data, size, errp)) < 0) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (_initialPushCleanup, (void *)p);
		}
	}
	else
	{
		ssize_t status;
		u8_t *cp = data;
		Dz1DynamicBufferEntry *e = NULL;

		ret = 0;
		Dz1Error_set(errp, 0);
		while(errp->code == 0 && size > 0)
		{
			e = p->tail;
			if ((status = Dz1DynamicBufferEntry_push(e, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				ret += status;
				size -= status;
				cp += status;

				if (size)
				{
					if ((p->tail->next = Dz1DynamicBufferEntry_new(errp)) == NULL) { ERR_OUT(errp); ret = -1; }
					else p->tail = p->tail->next;
				}
			}
		}
	}
	return ret;
}

ssize_t Dz1DynamicBuffer_pop(Dz1DynamicBuffer *pDB, u8_t *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = -1;
	_Dz1DynamicBuffer *p = (_Dz1DynamicBuffer *)pDB;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->head == NULL) ret = 0;
	else
	{
		ssize_t status;
		u8_t *cp = buf;
		Dz1DynamicBufferEntry *e = NULL;

		ret = 0;
		Dz1Error_set(errp, 0);
		while(errp->code == 0 && size)
		{
			e = p->head;
			if (e == NULL) break;
			if ((status = Dz1DynamicBufferEntry_pop(e, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				ret += status;
				size -= status;
				cp += status;

				if (size)
				{
					pthread_cleanup_push(Dz1DynamicBufferEntry_delAndSetNull, (void *)&e);
					if ((p->head = p->head->next) == NULL) p->tail = NULL;
					pthread_cleanup_pop(1); // (Dz1DynamicBufferEntry_delAndSetNull, (void *)&e);
				}
			}
		}
	}
	return ret;
}

ssize_t Dz1DynamicBuffer_getDataSize(Dz1DynamicBuffer *pDB, Dz1Error *err)
{
	ssize_t ret = -1;
	_Dz1DynamicBuffer *p = (_Dz1DynamicBuffer *)pDB;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->head == NULL) ret = 0;
	else
	{
		ssize_t status;
		Dz1DynamicBufferEntry *i;

		ret = 0;
		Dz1Error_set(errp, 0);
		for (i = p->head; i; i = i->next)
		{
			if ((status = Dz1DynamicBufferEntry_getDataSize(i, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else ret += status;
		}
	}
	return ret;
}

typedef struct Dz1ElasticBufferEntry
{
	struct Dz1ElasticBufferEntry	*prev;
	struct Dz1ElasticBufferEntry	*next;
	u8_t						*space;
	size_t						 space_size;
	size_t						 space_filled;

	size_t						 pos;
} Dz1ElasticBufferEntry;

static void Dz1ElasticBufferEntry_del(Dz1ElasticBufferEntry *p)
{
	if (p == NULL) return;
	if (p->space) Dz1Free(p);
	Dz1Free(p);
}

static void Dz1ElasticBufferEntry_delAndSetNull(void *pptr)
{
	Dz1ElasticBufferEntry **p = (Dz1ElasticBufferEntry **)pptr;
	Dz1ElasticBufferEntry_del(*p); *p = NULL;
}

static Dz1ElasticBufferEntry *Dz1ElasticBufferEntry_new(size_t space_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBufferEntry *ret = (Dz1ElasticBufferEntry *)Dz1Calloc(sizeof(Dz1ElasticBufferEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBufferEntry_delAndSetNull, (void *)&ret);

		if ((ret->space = (u8_t *)Dz1Malloc((ret->space_size = space_size), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1ElasticBufferEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static __inline__ Dz1ElasticBufferEntry *Dz1ElasticBufferEntry_clone(Dz1ElasticBufferEntry *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBufferEntry *ret = (Dz1ElasticBufferEntry *)Dz1Calloc(sizeof(Dz1ElasticBufferEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBufferEntry_delAndSetNull, (void *)&ret);

		if ((ret->space = (u8_t *)Dz1Malloc((ret->space_size = src->space_size), errp)) == NULL) ERR_OUT(errp);
		else
		{
			memcpy(ret->space, src->space, (ret->space_filled = src->space_filled));
			ret->pos = src->pos;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1ElasticBufferEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static ssize_t Dz1ElasticBufferEntry_read(Dz1ElasticBufferEntry *p, u8_t *dst_buf, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (p == NULL || dst_buf == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else if (size > 0)
	{
		u8_t *copy_ptr = p->space + p->pos;
		size_t data_size = (p->space_filled - p->pos);
		if (data_size > 0)
		{
			size_t copy_size = data_size > size ? size : data_size;
			memcpy(dst_buf, copy_ptr, copy_size);
			p->pos += copy_size;
		}
	}
	return ret;
}

static ssize_t Dz1ElasticBufferEntry_write(Dz1ElasticBufferEntry *p, u8_t *src_buf, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (p == NULL || src_buf == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else if (size > 0)
	{
		u8_t *copy_ptr = p->space + p->pos;
		size_t space_size = (p->space_size - p->pos);
		if (space_size > 0)
		{
			size_t copy_size = space_size > size ? size : space_size;
			memcpy(copy_ptr, src_buf, copy_size);
			p->pos += copy_size;
			p->space_filled = p->pos;
		}
	}
	return ret;
}

static ssize_t Dz1ElasticBufferEntry_move(Dz1ElasticBufferEntry *p, ssize_t pos, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (p == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else if (pos > 0)
	{
		size_t want_size = -pos;
		size_t backward_size = p->pos;
		ret = (ssize_t)(want_size > backward_size ? backward_size : want_size);
		p->pos -= ret;
		
	}
	else
	{
		size_t want_size = pos;
		size_t forward_size = p->space_filled - p->pos;
		ret = (ssize_t)(want_size > forward_size ? forward_size : want_size);
		p->pos += ret;
	}
	return ret;
}

static ssize_t Dz1ElasticBufferEntry_load(Dz1ElasticBufferEntry *p, u8_t *data_ptr, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (p == NULL || data_ptr == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else if (size == 0) { }
	else
	{
		u8_t *copy_ptr = p->space + p->space_filled;
		size_t space_size = p->space_size - p->space_filled;
		ret = (ssize_t)(size > space_size ? space_size : size);
		memcpy(copy_ptr, data_ptr, ret);
		p->space_filled += ret;
	}
	return ret;
}

static void Dz1ElasticBufferEntryA_dump(Dz1ElasticBufferEntry *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("[%u/%u:%u]\n", p->space_filled, p->space_size, p->pos);
}
#ifndef UNIX_SYSTEM
static void Dz1ElasticBufferEntryW_dump(Dz1ElasticBufferEntry *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"[%u/%u:%u]\n", p->space_filled, p->space_size, p->pos);
}
#endif
typedef struct Dz1ElasticBuffer
{
	Dz1ElasticBufferEntry			*head;
	Dz1ElasticBufferEntry			*tail;

	Dz1ElasticBufferEntry			*cur;
	size_t						 alloc_size;
} Dz1ElasticBuffer;


static __inline__ void Dz1ElasticBufferEntry_link(Dz1ElasticBufferEntry *p,

									Dz1ElasticBufferEntry *prev,
									Dz1ElasticBufferEntry **prev_next,

									Dz1ElasticBufferEntry *next,
									Dz1ElasticBufferEntry **next_prev)
{
	if (prev_next) (*prev_next) = p;
	p->prev = prev;

	if (next_prev) (*next_prev) = p;
	p->next = next;
}


Dz1ElasticBufferfer *Dz1ElasticBufferfer_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuffer *ret = (Dz1ElasticBuffer *)Dz1Calloc(sizeof(Dz1ElasticBuffer), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBufferfer_delAndSetNull, (void *)&ret);
		ret->head = ret->tail = NULL;
		ret->cur = NULL;
		ret->alloc_size = 0;
		pthread_cleanup_pop(1); // (Dz1ElasticBufferfer_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ElasticBufferfer_del(Dz1ElasticBufferfer *p)
{
	Dz1ElasticBuffer *_p = (Dz1ElasticBuffer *)p;
	if (_p == NULL) return;

	if (_p->head)
	{
		Dz1ElasticBufferEntry *next = NULL, *i = _p->head;
		while(i != NULL)
		{
			next = i->next;
			Dz1ElasticBufferEntry_del(i);
			i = next;
		}
	}
	Dz1Free(p);
}

void Dz1ElasticBufferferA_dump(Dz1ElasticBufferfer *_p, int tab)
{
	Dz1ElasticBuffer *p = (Dz1ElasticBuffer *)_p;
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else if (p->head == NULL) Dz1ThreadA_printf("Empty\n");
	else
	{
		Dz1ElasticBufferEntry *i;
		Dz1ThreadA_printf("{\n"); tab++;
		for (i = p->head; i != NULL; i = i->next)
		{
			Dz1ThreadA_tprintf(tab, "entry = ");
			Dz1ElasticBufferEntryA_dump(i, tab);
		}
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1ElasticBufferferW_dump(Dz1ElasticBufferfer *_p, int tab)
{
	Dz1ElasticBuffer *p = (Dz1ElasticBuffer *)_p;
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else if (p->head == NULL) Dz1ThreadW_printf(L"Empty\n");
	else
	{
		Dz1ElasticBufferEntry *i;
		Dz1ThreadW_printf(L"{\n"); tab++;
		for (i = p->head; i != NULL; i = i->next)
		{
			Dz1ThreadW_tprintf(tab, L"entry = ");
			Dz1ElasticBufferEntryW_dump(i, tab);
		}
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif
ssize_t Dz1ElasticBufferfer_read(Dz1ElasticBufferfer *_p, u8_t *dst_buf, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = 0;
	Dz1ElasticBuffer *p = (Dz1ElasticBuffer *)_p;
	if (p == NULL || dst_buf == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else
	{
		u8_t *dp = dst_buf;
		ssize_t status = 0;
		if (p->cur == NULL)
		{
			if (p->head == NULL) { ERR_SET_OUT(errp, EPIPE); ret = -1; }
			else p->cur = p->head;
		}

		if (p->cur)
		{
			while(size && p->cur != NULL && errp->code == 0)
			{
				if ((status = Dz1ElasticBufferEntry_read(p->cur, dp, size, errp)) < 0) ERR_OUT(errp);
				else if (status == 0) p->cur = p->cur->next;
				else
				{
					dp += status;
					size -= status;
					ret += status;
				}
			}
		}
	}
	return ret;
}

ssize_t Dz1ElasticBufferfer_write(Dz1ElasticBufferfer *_p, u8_t *data_buf, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = 0;
	Dz1ElasticBuffer *p = (Dz1ElasticBuffer *)_p;
	if (p == NULL || data_buf == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else if (size > 0)
	{
		if (p->cur == NULL)
		{	// 위치가 초기화 되어있지 않았다
			if (p->head == NULL)
			{	// 버퍼가 비어있다=> Entry보충
				if ((p->cur = p->head = p->tail = Dz1ElasticBufferEntry_new(4096, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
			}
			else
			{	// 위치 초기화
				Dz1ElasticBufferEntry *i = NULL;
				for (i = p->head; i != NULL; i = i->next) i->pos = 0;
				p->cur = p->head;
			}
		}

		if (p->cur != NULL)
		{
			u8_t *sp = data_buf;
			ssize_t status = 0;
			while(size && errp->code == 0)
			{
				if (p->cur == NULL)
				{	// 끝에 다다랐다 => Entry 보충
					Dz1ElasticBufferEntry *new_node = Dz1ElasticBufferEntry_new(4096, errp);
					if (new_node == NULL) { ERR_OUT(errp); ret = -1; break; }
					else
					{
						p->tail->next = new_node;
						new_node->prev = p->tail;
						p->cur = p->tail = new_node;
					}
				}

				if ((status = Dz1ElasticBufferEntry_write(p->cur, sp, size, errp)) < 0) ERR_OUT(errp);
				else if (status == 0) p->cur = p->cur->next;
				else
				{
					sp += status;
					size -= status;
					ret += status;
				}
			}
		}
	}
	return ret;
}

ssize_t Dz1ElasticBufferfer_tell(Dz1ElasticBufferfer *_p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = 0;
	Dz1ElasticBuffer *p = (Dz1ElasticBuffer *)_p;
	if (p == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else
	{
		if (p->cur == NULL)
		{
			if (p->head != NULL)
			{
				Dz1ElasticBufferEntry *i;
				for (i = p->head; i != NULL; i = i->next) i->pos = 0;
				p->cur = p->head;
			}
		}
		else
		{
			Dz1ElasticBufferEntry *i;
			for (i = p->head; i != NULL; i = i->next)
			{
				if (i == p->cur)
				{
					ret += (ssize_t)i->pos;
					break;
				}
				else
				{
					ret += (ssize_t)i->space_filled;
					i->pos = i->space_filled;
				}
			}
		}
	}
	return ret;
}

Dz1Error Dz1ElasticBufferfer_seek(Dz1ElasticBufferfer *_p, Dz1ElasticBufferferSeek seek, ssize_t pos)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ElasticBuffer *p = (Dz1ElasticBuffer *)_p;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->head == NULL) { /* nothing to do */ }
	else
	{
		ssize_t status = 0;
		Dz1ElasticBufferEntry *i;
		switch(seek)
		{
		case Dz1ElasticBufferferSeek_atFirst:
			for (i = p->tail; i != NULL; i = i->prev) i->pos = 0;
			p->cur = p->head;
			break;
		case Dz1ElasticBufferferSeek_atLast:
			for (i = p->head; i != NULL; i = i->next) i->pos = i->space_filled;
			p->cur = p->tail;
			break;
		default:
			if (p->cur == NULL)
			{
				for (i = p->tail; i != NULL; i = i->prev) i->pos = 0;
				p->cur = p->head;
			}
			break;
		}

		if (pos < 0)
		{
			pos = -pos;
			// backward
			while(pos && p->cur != NULL)
			{
				if ((status = Dz1ElasticBufferEntry_move(p->cur, -pos, errp)) < 0) ERR_OUT(errp);
				else if (status == 0) p->cur = p->cur->prev;
				else pos -= status;
			}
		}
		else
		{	// forward
			while(pos && p->cur != NULL)
			{
				if ((status = Dz1ElasticBufferEntry_move(p->cur, pos, errp)) < 0) ERR_OUT(errp);
				else if (status == 0) p->cur = p->cur->next;
				else pos -= status;
			}
		}
	}
	return err;
}

ssize_t Dz1ElasticBufferfer_push(Dz1ElasticBufferfer *_p, u8_t *data_buf, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	Dz1ElasticBuffer *p = (Dz1ElasticBuffer *)_p;
	if (p == NULL || data_buf == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else
	{
		if (p->head == NULL)
		{
			if ((p->head = p->tail = Dz1ElasticBufferEntry_new(4096, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
		}

		if (p->head != NULL)
		{
			u8_t *dp = data_buf;
			ssize_t status = 0;
			while(size && errp->code == 0)
			{
				if ((status = Dz1ElasticBufferEntry_load(p->tail, dp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; break; }
				else if (status == 0)
				{
					Dz1ElasticBufferEntry *new_node = Dz1ElasticBufferEntry_new(4096, errp);
					if (new_node == NULL) { ERR_OUT(errp); ret = -1; break; }
					else
					{
						p->tail->next = new_node;
						new_node->prev = p->tail;
						p->tail = new_node;
					}
				}
				else
				{
					dp += status;
					size -= status;
				}
			}
		}
	}
	return ret;
}
