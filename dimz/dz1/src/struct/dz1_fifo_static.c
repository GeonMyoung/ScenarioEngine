#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_fifo_static.h"

#define FIFO_STATUS_EMPTY		0
#define FIFO_STATUS_FILLED		1
#define FIFO_STATUS_FULL		2

Dz1Error Dz1FifoStatic_init(Dz1FifoStatic *p, u32_t size, bool_t autoPop)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((p->arr = (void **)Dz1Calloc(sizeof(void *), (size + 1), &err)))
	{
		p->size = size + 1;
		p->head = 0;
		p->tail = 0;
		p->status = FIFO_STATUS_EMPTY;
		p->isAutoPop = autoPop;
	}
	return err;
}

void Dz1FifoStatic_clean(Dz1FifoStatic *p, Dz1DelFunc del)
{
	unsigned int i;
	if (p->arr)
	{
		if (p->head < p->tail)
		{
			for (i = p->head; i < p->tail; i++)
				if (p->arr[i] && del) { del(p->arr[i]); p->arr[i] = NULL; }
		}
		else if (p->head > p->tail)
		{
			for (i = p->head; i < p->size; i++)
				if (p->arr[i] && del) { del(p->arr[i]); p->arr[i] = NULL; }
			for (i = 0; i < p->tail; i++)
				if (p->arr[i] && del) { del(p->arr[i]); p->arr[i] = NULL; }
		}
		else if (p->status == FIFO_STATUS_FULL)
		{
			for (i = 0; i < p->size; i++)
				if (p->arr[i] && del) { del(p->arr[i]); p->arr[i] = NULL; }
		}
		Dz1Free(p->arr);
	}
}

void *Dz1FifoStatic_pop(Dz1FifoStatic *p, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (p->status == FIFO_STATUS_EMPTY) Dz1Error_set(errp, ESRCH);
	else
	{
		ret = p->arr[p->head];
		p->arr[p->head++] = NULL;
		p->head %= p->size;

		if (p->head == p->tail) p->status = FIFO_STATUS_EMPTY; else p->status = FIFO_STATUS_FILLED;
		Dz1Error_set(errp, 0);
	}
//	printf("count = %d\n", Dz1FifoStatic_count(p));
	return ret;
}

Dz1Error Dz1FifoStatic_push(Dz1FifoStatic *p, void *data, Dz1DelFunc del)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p->status == FIFO_STATUS_FULL)
	{
		if (!p->isAutoPop) Dz1Error_set(&err, ENOMEM);
		else
		{
			void *temp = Dz1FifoStatic_pop(p, &err);
			if (temp && del) del(temp);
			err = Dz1FifoStatic_push(p, data, del);
		}
	}
	else
	{
		p->arr[p->tail++] = data;
		p->tail %= p->size;
		if (p->head == p->tail) p->status = FIFO_STATUS_FULL; else p->status = FIFO_STATUS_FILLED;
	}
	return err;
}

void Dz1FifoStatic_dump(Dz1FifoStatic *p, int tab, Dz1DumpFunc dump)
{
	unsigned int i;
	if (p->status == FIFO_STATUS_EMPTY)
		Dz1Thread_tprintf(tab, "empty\n");
	else if (p->head < p->tail)
	{
		for (i = p->head; i < p->tail; i++)
			if (p->arr[i] && dump) dump(p->arr[i], tab);
	}
	else
	{
		for (i = p->head; i < p->size; i++)
			if (p->arr[i] && dump) dump(p->arr[i], tab);
		for (i = 0; i < p->tail; i++)
			if (p->arr[i] && dump) dump(p->arr[i], tab);
	}
}

bool_t Dz1FifoStatic_isFull(Dz1FifoStatic *p)
{
	bool_t ret = (p->status == FIFO_STATUS_FULL) ? TRUE : FALSE;
	return ret;
}

bool_t Dz1FifoStatic_isEmpty(Dz1FifoStatic *p)
{
	bool_t ret = (p->status == FIFO_STATUS_EMPTY) ? TRUE : FALSE;
	return ret;
}

u32_t Dz1FifoStatic_count(Dz1FifoStatic *p)
{
	u32_t ret = FALSE;
	if (p)
	{
		if (p->head == p->tail)
		{
			if (p->status == FIFO_STATUS_FULL) ret = p->size;
			else ret = 0;
		}
		else if (p->head <= p->tail) return p->tail - p->head;
		else if (p->head > p->tail) return p->size - p->head + p->tail;
	}
	return ret;
}

void *Dz1FifoStatic_getFirst(Dz1FifoStatic *p)
{
	void *ret = NULL;
	if (p && p->status != FIFO_STATUS_EMPTY) ret = p->arr[p->head];
	return ret;
}

void *Dz1FifoStatic_getLast(Dz1FifoStatic *p)
{
	void *ret = NULL;
	if (p && p->status != FIFO_STATUS_EMPTY)
	{
		if (p->tail) ret = p->arr[p->tail - 1];
		else ret = p->arr[p->size - 1];
	}
	return ret;
}

Dz1Error Dz1FifoStaticCursor_init(Dz1FifoStaticCursor *p, Dz1FifoStatic *fifo, Dz1FifoCursorPos pos)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (fifo == NULL) fifo = p->fifo;
	
	if (fifo == NULL) { ERR_SET_OUT(&err, EINVAL); }
	else
	{
		p->fifo = fifo;
		if (pos == Dz1FifoCursorPos_head) p->pos = fifo->head;
		else
		{
			if (fifo->tail) p->pos = fifo->tail - 1;
			else p->pos = fifo->size - 1;
		}
	}
	return err;
}

void Dz1FifoStaticCursor_del(Dz1FifoStaticCursor *p)
{
	if (!p) return;
	Dz1Free(p);
}

static bool_t _Dz1FifoStaticCursor_cond(Dz1FifoStatic *p, u32_t pos)
{
	bool_t ret = FALSE;
	if (p && p->status != FIFO_STATUS_EMPTY)
	{
		if (p->head < p->tail && pos < p->tail && pos >= p->head) ret = TRUE;
		else if (p->head > p->tail && (pos >= p->head || pos < p->tail)) ret = TRUE;
		else if (p->head == p->tail && pos < p->size) ret = TRUE;
	}
	return ret;
}

bool_t Dz1FifoStaticCursor_cond(Dz1FifoStaticCursor *p)
{
	bool_t ret = FALSE;
	if (p)
	{
		Dz1FifoStatic *fifo = p->fifo;
		ret = _Dz1FifoStaticCursor_cond(fifo, p->pos);
	}
	return ret;
}

bool_t Dz1FifoStaticCursor_isFirst(Dz1FifoStaticCursor *p)
{
	if (p)
	{
		Dz1FifoStatic *fifo = p->fifo;
		if (fifo && p->pos == fifo->head) return TRUE;
	}
	return FALSE;
}

bool_t Dz1FifoStaticCursor_isLast(Dz1FifoStaticCursor *p)
{
	if (p)
	{
		Dz1FifoStatic *fifo = p->fifo;
		if (fifo && ((p->pos + 1) % fifo->size) == fifo->tail) return TRUE;
	}
	return FALSE;
}

void Dz1FifoStaticCursor_next(Dz1FifoStaticCursor *p, bool_t notNull)
{
	if (p)
	{
		Dz1FifoStatic *fifo = p->fifo;
		if (fifo)
		{
			int pos = (p->pos + 1) % fifo->size;
			if (!notNull || _Dz1FifoStaticCursor_cond(fifo, pos)) p->pos = pos;
		}
	}
}

void Dz1FifoStaticCursor_prev(Dz1FifoStaticCursor *p, bool_t notNull)
{
	if (p)
	{
		Dz1FifoStatic *fifo = p->fifo;
		if (fifo)
		{
			int pos;
			if (p->pos == 0)
				pos = fifo->size - 1;
			else
				pos = p->pos - 1;

			if (!notNull || _Dz1FifoStaticCursor_cond(fifo, pos)) p->pos = pos;
		}
	}
}

void *Dz1FifoStaticCursor_data(Dz1FifoStaticCursor *p)
{
	void *ret = NULL;
	if (p)
	{
		Dz1FifoStatic *fifo = p->fifo;
		if (fifo)
		{
			if (Dz1FifoStaticCursor_cond(p)) ret = fifo->arr[p->pos];
		}
	}
	return ret;
}


