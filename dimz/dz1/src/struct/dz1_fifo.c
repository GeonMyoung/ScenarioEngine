#include <dz1_malloc.h>
#include <dz1_sync.h>

#include <dz1_fifo.h>
#include "dz1_fifo_dynamic.h"
#include "dz1_fifo_static.h"

typedef enum
{
	Dz1FifoType_static,
	Dz1FifoType_dynamic,
	Dz1FifoType_max
} Dz1FifoType;

typedef struct _Dz1Fifo
{
	Dz1DelFunc del;
	Dz1DumpFunc dump;

	Dz1FifoType type;
	union
	{
		Dz1FifoDynamic d;
		Dz1FifoStatic s;
	} x;
} _Dz1Fifo;

// 0=Dynamic FIFO, 0 < Static Size FIFO, 0 > Static Size FIFO with Auto Pop-out
void *Dz1Fifo_new(Dz1DelFunc del, Dz1DumpFunc dump, int size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1Fifo *ret = (_Dz1Fifo *)Dz1Malloc(sizeof(_Dz1Fifo), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(_Dz1Fifo));

		ret->del = del;
		ret->dump = dump;

		if (size == 0)
		{
			ret->type = Dz1FifoType_dynamic;
			Dz1FifoDynamic_init(&ret->x.d);
		}
		else
		{
			ret->type = Dz1FifoType_static;

			pthread_cleanup_push(Dz1Fifo_delAndSetNull, (void *)&ret);
			if (size > 0)
				*errp = Dz1FifoStatic_init(&ret->x.s, size, FALSE);
			else
			{
				size = -size;
				*errp = Dz1FifoStatic_init(&ret->x.s, size, TRUE);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Fifo_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

static void _Dz1Fifo_empty(_Dz1Fifo *p)
{
	switch(p->type)
	{
	case Dz1FifoType_static: Dz1FifoStatic_clean(&p->x.s, p->del); break;
	case Dz1FifoType_dynamic: Dz1FifoDynamic_clean(&p->x.d, p->del); break;
	default: break;
	}
}

void Dz1Fifo_empty(void *ptr)
{
	_Dz1Fifo *p = (_Dz1Fifo *)ptr;
	if (!p) return;
	else _Dz1Fifo_empty(p);
}

void Dz1Fifo_del(void *ptr)
{
	_Dz1Fifo *p = (_Dz1Fifo *)ptr;
	if (!p) return;
	else
	{
		_Dz1Fifo_empty(p);
		Dz1Free(p);
	}
}

Dz1Error Dz1Fifo_push(void *ptr, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_Dz1Fifo *p = (_Dz1Fifo *)ptr;

	if (!p) Dz1Error_set(&err, EINVAL);
	else
	{
		if (p->type == Dz1FifoType_static)
		{
			Dz1FifoStatic *fifo = &p->x.s;
			err = Dz1FifoStatic_push(fifo, data, p->del);
		}
		else if (p->type == Dz1FifoType_dynamic)
		{
			Dz1FifoDynamic *fifo = &p->x.d;
			err = Dz1FifoDynamic_pushTail(fifo, data);
		}
		else Dz1Error_set(&err, EINVAL);
	}

	return err;
}

void *Dz1Fifo_pop(void *ptr, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1Fifo *p = (_Dz1Fifo *)ptr;

	if (!p) Dz1Error_set(errp, EINVAL);
	else
	{
		if (p->type == Dz1FifoType_static)
		{
			Dz1FifoStatic *fifo = &p->x.s;
			ret = Dz1FifoStatic_pop(fifo, errp);
		}
		else if (p->type == Dz1FifoType_dynamic)
		{
			Dz1FifoDynamic *fifo = &p->x.d;
			ret = Dz1FifoDynamic_popHead(fifo, errp);
		}
		else Dz1Error_set(errp, EINVAL);
	}
	return ret;
}

void Dz1Fifo_dump(void *ptr, int tab)
{
	_Dz1Fifo *p = (_Dz1Fifo *)ptr;
	if (!p) return;
	else
	{
		if (p->type == Dz1FifoType_static)
		{
			Dz1FifoStatic *fifo = &p->x.s;
			Dz1FifoStatic_dump(fifo, tab, p->dump);
		}
		else if (p->type == Dz1FifoType_dynamic)
		{
			Dz1FifoDynamic *fifo = &p->x.d;
			Dz1FifoDynamic_dump(fifo, tab, p->dump);
		}
		else { printf("Dz1Fifo_dump() : unknown type\n"); fflush(stdout); }
	}
}

bool_t Dz1Fifo_remove(void *ptr, void *removeptr)
{
	_Dz1Fifo *p = (_Dz1Fifo *)ptr;
	bool_t ret = FALSE;
	if (p == NULL) { }
	else
	{
		if (p->type == Dz1FifoType_static)
		{
			printf("Dz1Fifo_remove() : This Function not support for Static Sized Fifo\n");
		}
		else if (p->type == Dz1FifoType_dynamic)
		{
			Dz1FifoDynamic *fifo = &p->x.d;
			ret = Dz1FifoDynamic_remove(fifo, removeptr, p->del);
		}
		else { printf("Dz1Fifo_remove() : unknown type\n"); fflush(stdout); }
	}
	return ret;
}

void *Dz1Fifo_extract(void *ptr, void *removeptr)
{
	void *ret = NULL;
	_Dz1Fifo *p = (_Dz1Fifo *)ptr;
	if (p->type == Dz1FifoType_static)
	{
		printf("Dz1Fifo_extract() : Static Sized Fifo does not support extract function\n");
	}
	else if (p->type == Dz1FifoType_dynamic)
	{
		Dz1FifoDynamic *fifo = &p->x.d;
		ret = Dz1FifoDynamic_extract(fifo, removeptr, p->del);
	}
	else { printf("Dz1Fifo_remove() : unknown type\n"); fflush(stdout); }
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Travel
Dz1Error Dz1Fifo_travelForward(void *ptr, Dz1FifoTravelFunc func, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	void *c = Dz1FifoCursor_new(ptr, &err), *data;
	if (c == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);
		for (Dz1FifoCursorForward(c))
		{
			data = Dz1FifoCursor_data(c);
			if ((err = func(param, data)).code) { break; }
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return err;
}

Dz1Error Dz1Fifo_travelBackward(void *ptr, Dz1FifoTravelFunc func, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	void *c = Dz1FifoCursor_new(ptr, &err), *data;
	if (c == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);
		for (Dz1FifoCursorBackward(c))
		{
			data = Dz1FifoCursor_data(c);
			if ((err = func(param, data)).code) { break; }
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return err;
}
// Travel
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Travel Mode 2
int Dz1Fifo_travelForward2(void *ptr, Dz1FifoTravelFunc2 func, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = 0;
	void *c = Dz1FifoCursor_new(ptr, errp), *data;
	if (c == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);
		for (Dz1FifoCursorForward(c))
		{
			data = Dz1FifoCursor_data(c);
			if ((ret = func(param, data, errp)) != 0) { break; }
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}
int Dz1Fifo_travelBackward2(void *ptr, Dz1FifoTravelFunc2 func, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = 0;
	void *c = Dz1FifoCursor_new(ptr, errp), *data;
	if (c == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);
		for (Dz1FifoCursorBackward(c))
		{
			data = Dz1FifoCursor_data(c);
			if ((ret = func(param, data, errp)) != 0) { break; }
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}
// Travel Mode 2
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1Fifo_isEmpty(void *ptr)
{
	bool_t ret = TRUE;

	_Dz1Fifo *p = (_Dz1Fifo *)ptr;

	if (p)
	{

		if (p->type == Dz1FifoType_static)
		{
			Dz1FifoStatic *fifo = &p->x.s;
			ret = Dz1FifoStatic_isEmpty(fifo);
		}
		else if (p->type == Dz1FifoType_dynamic)
		{
			Dz1FifoDynamic *fifo = &p->x.d;
			ret = Dz1FifoDynamic_isEmpty(fifo);
		}

	}

	return ret;
}

bool_t Dz1Fifo_isFull(void *ptr)
{
	bool_t ret = TRUE;

	_Dz1Fifo *p = (_Dz1Fifo *)ptr;

	if (p)
	{

		if (p->type == Dz1FifoType_static)
		{
			Dz1FifoStatic *fifo = &p->x.s;
			ret = Dz1FifoStatic_isFull(fifo);
		}
		else if (p->type == Dz1FifoType_dynamic)
		{
			ret = FALSE;
		}

	}

	return ret;

}

u32_t Dz1Fifo_count(void *ptr)
{
	u32_t ret = 0;

	_Dz1Fifo *p = (_Dz1Fifo *)ptr;
	if (p)
	{

		if (p->type == Dz1FifoType_static)
		{
			Dz1FifoStatic *fifo = &p->x.s;
			ret = Dz1FifoStatic_count(fifo);
		}
		else if (p->type == Dz1FifoType_dynamic)
		{
			Dz1FifoDynamic *fifo = &p->x.d;
			ret = Dz1FifoDynamic_count(fifo);
		}

	}

	return ret;
}

void *Dz1Fifo_getFirst(void *ptr)
{
	void *ret = 0;

	_Dz1Fifo *p = (_Dz1Fifo *)ptr;
	if (p)
	{

		if (p->type == Dz1FifoType_static)
		{
			Dz1FifoStatic *fifo = &p->x.s;
			ret = Dz1FifoStatic_getFirst(fifo);
		}
		else if (p->type == Dz1FifoType_dynamic)
		{
			Dz1FifoDynamic *fifo = &p->x.d;
			ret = Dz1FifoDynamic_getFirst(fifo);
		}
	}

	return ret;
}

void *Dz1Fifo_getLast(void *ptr)
{
	void *ret = 0;

	_Dz1Fifo *p = (_Dz1Fifo *)ptr;
	if (p)
	{

		if (p->type == Dz1FifoType_static)
		{
			Dz1FifoStatic *fifo = &p->x.s;
			ret = Dz1FifoStatic_getLast(fifo);
		}
		else if (p->type == Dz1FifoType_dynamic)
		{
			Dz1FifoDynamic *fifo = &p->x.d;
			ret = Dz1FifoDynamic_getLast(fifo);
		}
	}

	return ret;
}

typedef struct Dz1FifoCursor
{
	Dz1FifoType type;
	union
	{
		Dz1FifoDynamicCursor d;
		Dz1FifoStaticCursor s;
	} x;
} Dz1FifoCursor;

Dz1Error Dz1FifoCursor_init(void *ptr, void *fifo, Dz1FifoCursorPos pos)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1FifoCursor *p = (Dz1FifoCursor *)ptr;

	_Dz1Fifo *f = (_Dz1Fifo *)fifo;

	if (p->type == Dz1FifoType_static)
	{
		Dz1FifoStaticCursor *c = &p->x.s;
		Dz1FifoStatic *s = f ? &f->x.s : NULL;

//		printf("Dz1FifoCursor_init() : Static(%p)\n", ptr);
		Dz1FifoStaticCursor_init(c, s, pos);
	}
	else if (p->type == Dz1FifoType_dynamic)
	{
		Dz1FifoDynamicCursor *c = &p->x.d;
		Dz1FifoDynamic *d = f ? &f->x.d : NULL;

		if ((err = Dz1FifoDynamicCursor_init(c, d, pos)).code) { ERR_OUT(&err); }
	}
	else { ERR_SET_OUT(&err, EINVAL); }
	return err;
}

void *_Dz1FifoCursor_new(void *ptr, Dz1Error *err, const char *file, int line)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1FifoCursor *ret = NULL;

	if (ptr == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1FifoCursor *)_Dz1Calloc(sizeof(Dz1FifoCursor), 1, errp, file, line)) == NULL) { ERR_OUT(errp); }
	else
	{
		_Dz1Fifo *fifo = (_Dz1Fifo *)ptr;
		ret->type = fifo->type;
		if ((*errp = Dz1FifoCursor_init(ret, fifo, Dz1FifoCursorPos_head)).code) { ERR_OUT(errp); }
	}
	return ret;
}

void Dz1FifoCursor_del(void *cursor)
{
	Dz1FifoCursor *c = (Dz1FifoCursor *)cursor;
	if (!c) return;
	if (c->type == Dz1FifoType_static)
	{
	}
	else if (c->type == Dz1FifoType_dynamic)
	{
	}
	Dz1Free(c);
}

bool_t Dz1FifoCursor_cond(void *ptr)
{
	Dz1FifoCursor *p = (Dz1FifoCursor *)ptr;
	bool_t ret = FALSE;
	if (p->type == Dz1FifoType_static)
		ret = Dz1FifoStaticCursor_cond(&p->x.s);
	else if (p->type == Dz1FifoType_dynamic)
		ret = Dz1FifoDynamicCursor_cond(&p->x.d);
	return ret;
}

bool_t Dz1FifoCursor_isFirst(void *ptr)
{
	Dz1FifoCursor *p = (Dz1FifoCursor *)ptr;
	bool_t ret = FALSE;
	if (p->type == Dz1FifoType_static)
		ret = Dz1FifoStaticCursor_isFirst(&p->x.s);
	else if (p->type == Dz1FifoType_dynamic)
		ret = Dz1FifoDynamicCursor_isFirst(&p->x.d);
	return ret;
}

bool_t Dz1FifoCursor_isLast(void *ptr)
{
	Dz1FifoCursor *p = (Dz1FifoCursor *)ptr;
	bool_t ret = FALSE;
	if (p->type == Dz1FifoType_static)
		ret = Dz1FifoStaticCursor_isLast(&p->x.s);
	else if (p->type == Dz1FifoType_dynamic)
		ret = Dz1FifoDynamicCursor_isLast(&p->x.d);
	return ret;
}

void Dz1FifoCursor_next(void *ptr, bool_t notNull)
{
	Dz1FifoCursor *p = (Dz1FifoCursor *)ptr;
	if (p->type == Dz1FifoType_static)
		Dz1FifoStaticCursor_next(&p->x.s, notNull);
	else if (p->type == Dz1FifoType_dynamic)
		Dz1FifoDynamicCursor_next(&p->x.d, notNull);
}

void Dz1FifoCursor_prev(void *ptr, bool_t notNull)
{
	Dz1FifoCursor *p = (Dz1FifoCursor *)ptr;
	if (p->type == Dz1FifoType_static)
		Dz1FifoStaticCursor_prev(&p->x.s, notNull);
	else if (p->type == Dz1FifoType_dynamic)
		Dz1FifoDynamicCursor_prev(&p->x.d, notNull);
}

void *Dz1FifoCursor_data(void *ptr)
{
	void *ret = NULL;
	Dz1FifoCursor *p = (Dz1FifoCursor *)ptr;
	if (p->type == Dz1FifoType_static)
		ret = Dz1FifoStaticCursor_data(&p->x.s);
	else if (p->type == Dz1FifoType_dynamic)
		ret = Dz1FifoDynamicCursor_data(&p->x.d);
	return ret;
}
