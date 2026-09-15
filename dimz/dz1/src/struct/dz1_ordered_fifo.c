#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_ordered_fifo.h"

Dz1ORDFifoEntry *Dz1ORDFifoEntry_new(void *data, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ORDFifoEntry *ret = (Dz1ORDFifoEntry *)Dz1Malloc(sizeof(Dz1ORDFifoEntry), errp);
	if (ret)
	{
		ret->prev = NULL;
		ret->next = NULL;
		ret->data = data;

		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1ORDFifoEntry_del(Dz1ORDFifoEntry *p, Dz1DelFunc del)
{
	if (!p) return;
	if (p->data && del) del(p->data);
	Dz1Free(p);
}

void Dz1OrderedFifo_init(Dz1ORDFifo *p)
{
	p->count = 0;
	p->head = p->tail =  NULL;
}

void Dz1OrderedFifo_clean(Dz1ORDFifo *p, Dz1DelFunc del)
{
	if (!p) return;
	else
	{
		Dz1ORDFifoEntry *i = p->head, *next = NULL;
		while(i)
		{
			next = i->next;
			Dz1ORDFifoEntry_del(i, del);
			i = next;
		}
		Dz1OrderedFifo_init(p);
	}
}

Dz1Error Dz1OrderedFifo_push(Dz1OrderedFifo *ptr, void *data)
{
	Dz1ORDFifo *p = (Dz1ORDFifo *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ORDFifoEntry *e = Dz1ORDFifoEntry_new(data, &err);
	if (e)
	{
		if (p->head)
		{
			bool_t found = FALSE;
			Dz1ORDFifoEntry *i;
			for (i = p->head; i != NULL; i = i->next)
			{
				if (p->cmp(e->data, i->data) < 0)
				{
					e->prev = i->prev;
					if (e->prev != NULL) e->prev->next = e;
					else p->head = e;

					e->next = i;
					i->prev = e;

					found = TRUE;
					break;
				}
			}

			if (!found)
			{
				p->tail->next = e;
				e->prev = p->tail;

				p->tail = e;
			}
		}
		else p->head = p->tail = e;
		p->count++;
	}
	return err;
}

void *Dz1OrderedFifo_pop(Dz1OrderedFifo *ptr, Dz1Error *err)
{
	Dz1ORDFifo *p = (Dz1ORDFifo *)ptr;
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (p->head == NULL) Dz1Error_set(errp, ESRCH);
	else
	{
		Dz1ORDFifoEntry *e = p->head;
		if (p->head == p->tail)
		{
			Dz1OrderedFifo_init(p);
		}
		else
		{
			p->head = p->head->next;
			p->head->prev = NULL;

			p->count--;
		}

		ret = e->data;
		e->data = NULL;

		Dz1ORDFifoEntry_del(e, NULL);

		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1OrderedFifo_dump(Dz1OrderedFifo *ptr, int tab)
{
	Dz1ORDFifo *p = (Dz1ORDFifo *)ptr;
	if (!p) return;
	else if (p->head)
	{
		Dz1ORDFifoEntry *i = NULL;
		for (i = p->head; i; i = i->next)
		{
			if (p->dump) { Dz1Thread_tprintf(tab, "Entry = "); p->dump(i->data, tab + 1); }
			else Dz1Thread_tprintf(tab, "%p\n", i->data);
		}
	}
	else Dz1Thread_tprintf(tab, "Empty\n");
}

static void Dz1OrderedFifo_unlink(Dz1OrderedFifo *ptr, Dz1ORDFifoEntry *node)
{
	Dz1ORDFifo *fifo = (Dz1ORDFifo *)ptr;
	if (fifo->head == fifo->tail)
	{	// only one entry
		if (fifo->head == node)
		{
			node->prev = node->next = NULL;
			fifo->head = fifo->tail = NULL;
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
	}
	fifo->count--;
}

void *Dz1OrderedFifo_find(Dz1OrderedFifo *ptr, void *key)
{
	Dz1ORDFifo *fifo = (Dz1ORDFifo *)ptr;
	Dz1ORDFifoEntry *p = fifo->head;
	while(p)
	{
		if (fifo->cmp(p->data, key) == 0)
			return p->data;
		p = p->next;
	}
	return NULL;
}

bool_t Dz1OrderedFifo_remove(Dz1OrderedFifo *ptr, void *key)
{
	bool_t ret = FALSE;
	Dz1ORDFifo *fifo = (Dz1ORDFifo *)ptr;
	Dz1ORDFifoEntry *p = fifo->head;
	while(p)
	{
		if (fifo->cmp(p->data, key) == 0)
		{
			Dz1OrderedFifo_unlink(fifo, p);
			Dz1ORDFifoEntry_del(p, fifo->del);
			ret = TRUE;
			break;
		}
		p = p->next;
	}
	return ret;
}

void *Dz1OrderedFifo_extract(Dz1OrderedFifo *ptr, void *key)
{
	Dz1ORDFifo *fifo = (Dz1ORDFifo *)ptr;
	void *ret = NULL;
	Dz1ORDFifoEntry *p = fifo->head;
	while(p)
	{
		if (fifo->cmp(p->data, key) == 0)
		{
			Dz1OrderedFifo_unlink(fifo, p);

			ret = p->data;
			p->data = NULL;
			Dz1ORDFifoEntry_del(p, fifo->del);

			break;
		}
		p = p->next;
	}
	return ret;
}

bool_t Dz1OrderedFifo_isEmpty(Dz1OrderedFifo *ptr)
{
	Dz1ORDFifo *p = (Dz1ORDFifo *)ptr;
	bool_t ret = FALSE;
	if (!p || !p->head) ret = TRUE;
	return ret;
}

u32_t Dz1OrderedFifo_count(Dz1OrderedFifo *ptr)
{
	Dz1ORDFifo *p = (Dz1ORDFifo *)ptr;
	u32_t ret = 0;
	if (p) ret = p->count;
	return ret;
}

void *Dz1OrderedFifo_getFirst(Dz1OrderedFifo *ptr)
{
	Dz1ORDFifo *p = (Dz1ORDFifo *)ptr;
	void *ret = NULL;
	if (p && p->head) ret = p->head->data;
	return ret;
}

void *Dz1OrderedFifo_getLast(Dz1OrderedFifo *ptr)
{
	Dz1ORDFifo *p = (Dz1ORDFifo *)ptr;
	void *ret = NULL;
	if (p && p->tail) ret = p->tail->data;
	return ret;
}

Dz1OrderedFifo *_Dz1OrderedFifo_new(Dz1CmpFunc cmp, Dz1DelFunc del, Dz1DumpFunc dump, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ORDFifo *ret = NULL;
	if (cmp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1ORDFifo *)_Dz1Calloc(sizeof(Dz1ORDFifo), 1, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
	else
	{
		ret->cmp = cmp;
		ret->del = del;
		ret->dump = dump;
	}
	return (Dz1OrderedFifo *)ret;
}

static void _Dz1OrderedFifo_empty(Dz1ORDFifo *fifo)
{
	Dz1ORDFifoEntry *p = fifo->head, *next;
	while(p)
	{
		next = p->next;
		Dz1ORDFifoEntry_del(p, fifo->del);
		p = next;
	}
}

void Dz1OrderedFifo_empty(Dz1OrderedFifo *ptr)
{
	Dz1ORDFifo *fifo = (Dz1ORDFifo *)ptr;
	if (fifo == NULL) return;
	else _Dz1OrderedFifo_empty(fifo);
}

void Dz1OrderedFifo_del(Dz1OrderedFifo *ptr)
{
	Dz1ORDFifo *fifo = (Dz1ORDFifo *)ptr;
	if (fifo == NULL) return;
	else
	{
		_Dz1OrderedFifo_empty(fifo);
		Dz1Free(fifo);
	}
}

Dz1Error Dz1OrderedFifo_travelForward(Dz1OrderedFifo *ptr, Dz1OrderedFifoTravelFunc func, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1ORDFifo *fifo = (Dz1ORDFifo *)ptr;
	if (fifo == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1ORDFifoEntry *i;
		for (i = fifo->head; err.code == 0 && i != NULL; i = i->next)
			if ((err = func(param, i->data)).code) ERR_OUT(&err);
	}
	return err;
}

Dz1Error Dz1OrderedFifo_travelBackward(Dz1OrderedFifo *ptr, Dz1OrderedFifoTravelFunc func, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1ORDFifo *fifo = (Dz1ORDFifo *)ptr;
	if (fifo == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1ORDFifoEntry *i;
		for (i = fifo->tail; err.code == 0 && i != NULL; i = i->prev)
			if ((err = func(param, i->data)).code) ERR_OUT(&err);
	}
	return err;
}

/*
Dz1Error Dz1ORDFifoCursor_init(Dz1ORDFifoCursor *p, Dz1ORDFifo *fifo, Dz1FifoCursorPos pos)
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

int Dz1ORDFifoCursor_cond(Dz1ORDFifoCursor *p)
{
	bool_t ret = FALSE;
	if (p && p->pos) ret = TRUE;
	return ret;
}

bool_t Dz1ORDFifoCursor_isFirst(Dz1ORDFifoCursor *p)
{
	if (p && p->pos && p->pos->prev == NULL) return TRUE;
	return FALSE;
}

bool_t Dz1ORDFifoCursor_isLast(Dz1ORDFifoCursor *p)
{
	if (p && p->pos && p->pos->next == NULL) return TRUE;
	return FALSE;
}

void Dz1ORDFifoCursor_next(Dz1ORDFifoCursor *p, bool_t notNull) { if (p && p->pos && (!notNull || p->pos->next)) p->pos = p->pos->next; }

void Dz1ORDFifoCursor_prev(Dz1ORDFifoCursor *p, bool_t notNull) { if (p && p->pos && (!notNull || p->pos->prev)) p->pos = p->pos->prev; }

void *Dz1ORDFifoCursor_data(Dz1ORDFifoCursor *p) { void *ret = NULL; if (p && p->pos) ret = p->pos->data; return ret; }
*/
