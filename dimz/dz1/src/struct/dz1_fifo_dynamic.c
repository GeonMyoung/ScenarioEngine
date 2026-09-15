#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_fifo_dynamic.h"

Dz1FifoDynamicEntry *Dz1FifoDynamicEntry_new(void *data, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1FifoDynamicEntry *ret = (Dz1FifoDynamicEntry *)Dz1Malloc(sizeof(Dz1FifoDynamicEntry), errp);
	if (ret)
	{
		ret->prev = NULL;
		ret->next = NULL;
		ret->data = data;

		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1FifoDynamicEntry_del(Dz1FifoDynamicEntry *p, Dz1DelFunc del)
{
	if (!p) return;
	if (p->data && del) del(p->data);
	Dz1Free(p);
}

void Dz1FifoDynamic_init(Dz1FifoDynamic *p)
{
	p->count = 0;
	p->head = p->tail =  NULL;
}

void Dz1FifoDynamic_clean(Dz1FifoDynamic *p, Dz1DelFunc del)
{
	if (!p) return;
	else
	{
		Dz1FifoDynamicEntry *i = p->head, *next = NULL;
		while(i)
		{
			next = i->next;
			Dz1FifoDynamicEntry_del(i, del);
			i = next;
		}
		Dz1FifoDynamic_init(p);
	}
}

Dz1Error Dz1FifoDynamic_pushHead(Dz1FifoDynamic *p, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1FifoDynamicEntry *e = Dz1FifoDynamicEntry_new(data, &err);
	if (e)
	{
		if (p->head)
		{
			p->head->prev = e;
			e->next = p->head;

			p->head = e;

		}
		else p->head = p->tail = e;
		p->count++;
	}
	return err;
}

Dz1Error Dz1FifoDynamic_pushTail(Dz1FifoDynamic *p, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1FifoDynamicEntry *e = Dz1FifoDynamicEntry_new(data, &err);
	if (e)
	{
		if (p->head)
		{
			p->tail->next = e;
			e->prev = p->tail;

			p->tail = e;
		}
		else p->head = p->tail = e;
		p->count++;
	}
	return err;
}

void *Dz1FifoDynamic_popHead(Dz1FifoDynamic *p, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (p->head == NULL) Dz1Error_set(errp, ESRCH);
	else
	{
		Dz1FifoDynamicEntry *e = p->head;
		if (p->head == p->tail)
		{
			Dz1FifoDynamic_init(p);
		}
		else
		{
			p->head = p->head->next;
			p->head->prev = NULL;

			p->count--;
		}

		ret = e->data;
		e->data = NULL;

		Dz1FifoDynamicEntry_del(e, NULL);

		Dz1Error_set(errp, 0);
	}
	return ret;
}

void *Dz1FifoDynamic_popTail(Dz1FifoDynamic *p, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (p->head == NULL) Dz1Error_set(errp, ESRCH);
	else
	{
		Dz1FifoDynamicEntry *e = p->tail;
		if (p->head == p->tail)
		{
			Dz1FifoDynamic_init(p);
		}
		else
		{
			p->tail = p->tail->prev;
			p->tail->next = NULL;

			p->count--;
		}

		ret = e->data;
		e->data = NULL;

		Dz1FifoDynamicEntry_del(e, NULL);

		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1FifoDynamic_dump(Dz1FifoDynamic *p, int tab, Dz1DumpFunc dump)
{
	if (!p) return;
	else if (p->head)
	{
		Dz1FifoDynamicEntry *i = NULL;
		for (i = p->head; i; i = i->next)
		{
			if (dump) dump(i->data, tab);
			else Dz1Thread_tprintf(tab, "entry = %p\n", i->data);
		}
	}
	else Dz1Thread_tprintf(tab, "empty\n");
}

static void Dz1FifoDynamic_unlink(Dz1FifoDynamic *fifo, Dz1FifoDynamicEntry *node)
{
	if (fifo->head == fifo->tail)
	{	// only one entry
		if (fifo->head == node)
		{
			node->prev = node->next = NULL;
			fifo->head = fifo->tail = NULL;
			fifo->count--;
		}
	}
	else
	{
		if (fifo->head == node)
		{
			node->next->prev = node->prev;
			fifo->head = node->next;
		}
		else if (fifo->tail == node)
		{
			node->prev->next = node->next;
			fifo->tail = node->prev;
		}
		else
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
		}
		node->next = node->prev = NULL;
		fifo->count--;
	}
}

bool_t Dz1FifoDynamic_remove(Dz1FifoDynamic *fifo, void *removeptr, Dz1DelFunc del)
{
	bool_t ret = FALSE;
	Dz1FifoDynamicEntry *p = fifo->head;
	while(p)
	{
		if (p->data == removeptr)
		{
			Dz1FifoDynamic_unlink(fifo, p);
			Dz1FifoDynamicEntry_del(p, del);
			ret = TRUE;
			break;
		}
		p = p->next;
	}
	return ret;
}

void *Dz1FifoDynamic_extract(Dz1FifoDynamic *fifo, void *removeptr, Dz1DelFunc del)
{
	void *ret = NULL;
	if (removeptr == NULL)
		ret = Dz1FifoDynamic_popHead(fifo, NULL);
	else if (removeptr == (void *)-1)
		ret = Dz1FifoDynamic_popTail(fifo, NULL);
	else
	{
		Dz1FifoDynamicEntry *p = NULL;
		for (p = fifo->head; p != NULL; p = p->next)
		{
			if (p->data == removeptr)
			{
				Dz1FifoDynamic_unlink(fifo, p);

				ret = p->data;
				p->data = NULL;
				Dz1FifoDynamicEntry_del(p, del);

				break;
			}
		}
	}
	return ret;
}

bool_t Dz1FifoDynamic_isEmpty(Dz1FifoDynamic *p)
{
	bool_t ret = FALSE;
	if (!p || !p->head) ret = TRUE;
	return ret;
}

u32_t Dz1FifoDynamic_count(Dz1FifoDynamic *p)
{
	u32_t ret = 0;
	if (p) ret = p->count;
	return ret;
}

void *Dz1FifoDynamic_getFirst(Dz1FifoDynamic *p)
{
	void *ret = NULL;
	if (p && p->head) ret = p->head->data;
	return ret;
}

void *Dz1FifoDynamic_getLast(Dz1FifoDynamic *p)
{
	void *ret = NULL;
	if (p && p->tail) ret = p->tail->data;
	return ret;
}

Dz1Error Dz1FifoDynamicCursor_init(Dz1FifoDynamicCursor *p, Dz1FifoDynamic *fifo, Dz1FifoCursorPos pos)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (fifo == NULL) fifo = p->fifo;

	if (fifo == NULL) { ERR_SET_OUT(&err, EINVAL); }
	else
	{
	   	p->fifo = fifo;
		switch(pos)
		{
			case Dz1FifoCursorPos_head:
				p->pos = fifo->head;
				break;
			case Dz1FifoCursorPos_tail:
				if (fifo->tail) p->pos = fifo->tail;
				break;
			default:
				ERR_SET_OUT(&err, EINVAL);
				break;
		}
	}
	return err;
}

int Dz1FifoDynamicCursor_cond(Dz1FifoDynamicCursor *p)
{
	bool_t ret = FALSE;
	if (p && p->pos) ret = TRUE;
	return ret;
}

bool_t Dz1FifoDynamicCursor_isFirst(Dz1FifoDynamicCursor *p)
{
	if (p && p->pos && p->pos->prev == NULL) return TRUE;
	return FALSE;
}

bool_t Dz1FifoDynamicCursor_isLast(Dz1FifoDynamicCursor *p)
{
	if (p && p->pos && p->pos->next == NULL) return TRUE;
	return FALSE;
}

void Dz1FifoDynamicCursor_next(Dz1FifoDynamicCursor *p, bool_t notNull) { if (p && p->pos && (!notNull || p->pos->next)) p->pos = p->pos->next; }

void Dz1FifoDynamicCursor_prev(Dz1FifoDynamicCursor *p, bool_t notNull) { if (p && p->pos && (!notNull || p->pos->prev)) p->pos = p->pos->prev; }

void *Dz1FifoDynamicCursor_data(Dz1FifoDynamicCursor *p) { void *ret = NULL; if (p && p->pos) ret = p->pos->data; return ret; }
