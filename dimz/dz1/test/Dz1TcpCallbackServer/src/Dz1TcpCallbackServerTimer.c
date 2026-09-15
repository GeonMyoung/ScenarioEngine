#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpCallbackServerTimer.h"

Dz1TcpCallbackServerSessionTimer *Dz1TcpCallbackServerSessionTimer_new(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackServerSessionTimer *__internal_ret = (Dz1TcpCallbackServerSessionTimer *)Dz1Calloc(sizeof(Dz1TcpCallbackServerSessionTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerSessionTimer_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackServerSessionTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackServerSessionTimer_del(Dz1TcpCallbackServerSessionTimer *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	Dz1Free(p);
}

void Dz1TcpCallbackServerSessionTimer_dump(Dz1TcpCallbackServerSessionTimer *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1TcpCallbackServerSessionTimer_cmp(Dz1TcpCallbackServerSessionTimer *a, Dz1TcpCallbackServerSessionTimer *b)
{
	int ret = 0;
	if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) return ret;
	else if ((ret = Dz1SockAddr_cmp(a->local, b->local)) != 0) return ret;
	else return ret;
}

static struct Dz1TcpCallbackServerTimerPresentMapA
{
	str_t str;
	Dz1TcpCallbackServerTimerPresent v;
} Dz1TcpCallbackServerTimerPresentMapA[] =
{
	{ "id", Dz1TcpCallbackServerTimerPresent_id },
	{ "session", Dz1TcpCallbackServerTimerPresent_session },
	{ NULL, Dz1TcpCallbackServerTimerPresent_max }
};

str_t Dz1TcpCallbackServerTimerPresentStrA(Dz1TcpCallbackServerTimerPresent v)
{
	struct Dz1TcpCallbackServerTimerPresentMapA *i = NULL;
	for (i = Dz1TcpCallbackServerTimerPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpCallbackServerTimerPresent Dz1TcpCallbackServerTimerPresentFromStrA(str_t str)
{
	struct Dz1TcpCallbackServerTimerPresentMapA *i = NULL;
	for (i = Dz1TcpCallbackServerTimerPresentMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1TcpCallbackServerTimerPresent_max;
}

static struct Dz1TcpCallbackServerTimerPresentMapW
{
	wstr_t str;
	Dz1TcpCallbackServerTimerPresent v;
} Dz1TcpCallbackServerTimerPresentMapW[] =
{
	{ L"id", Dz1TcpCallbackServerTimerPresent_id },
	{ L"session", Dz1TcpCallbackServerTimerPresent_session },
	{ NULL, Dz1TcpCallbackServerTimerPresent_max }
};

wstr_t Dz1TcpCallbackServerTimerPresentStrW(Dz1TcpCallbackServerTimerPresent v)
{
	struct Dz1TcpCallbackServerTimerPresentMapW *i = NULL;
	for (i = Dz1TcpCallbackServerTimerPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpCallbackServerTimerPresent Dz1TcpCallbackServerTimerPresentFromStrW(wstr_t str)
{
	struct Dz1TcpCallbackServerTimerPresentMapW *i = NULL;
	for (i = Dz1TcpCallbackServerTimerPresentMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1TcpCallbackServerTimerPresent_max;
}

Dz1TcpCallbackServerTimerPresent *Dz1TcpCallbackServerTimerPresent_new(Dz1TcpCallbackServerTimerPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackServerTimerPresent *__internal_ret = (Dz1TcpCallbackServerTimerPresent *)Dz1Calloc(sizeof(Dz1TcpCallbackServerTimerPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1TcpCallbackServerTimerPresent_dump(Dz1TcpCallbackServerTimerPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf("NULL\n");
	else Dz1Thread_printf("%s\n", Dz1TcpCallbackServerTimerPresentStrA(*v));
}

int Dz1TcpCallbackServerTimerPresent_cmp(Dz1TcpCallbackServerTimerPresent *a, Dz1TcpCallbackServerTimerPresent *b)
{
	int ret = (int)(*a - *b);
	return ret;
}

Dz1TcpCallbackServerTimer *Dz1TcpCallbackServerTimer_new(Dz1TcpCallbackServerTimerPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackServerTimer *ret = (Dz1TcpCallbackServerTimer *)Dz1Calloc(sizeof(Dz1TcpCallbackServerTimer), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerTimer_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
			case Dz1TcpCallbackServerTimerPresent_id:
				if (ptr) ret->x.id = *(u32_t *)ptr; // Value Primitive Scalar Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpCallbackServerTimerPresent_session:
				ret->x.session = (Dz1TcpCallbackServerSessionTimer *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpCallbackServerTimerPresent_max:
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackServerTimer_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpCallbackServerTimer_del(Dz1TcpCallbackServerTimer *p)
{
	if (!p) return;
	switch(p->present)
	{
		case Dz1TcpCallbackServerTimerPresent_id:
			break;
		case Dz1TcpCallbackServerTimerPresent_session:
			if (p->x.session) Dz1TcpCallbackServerSessionTimer_del(p->x.session);
			break;
		default:
			break;
	}
	Dz1Free(p);
}

void Dz1TcpCallbackServerTimer_dump(Dz1TcpCallbackServerTimer *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	switch(p->present)
	{
		case Dz1TcpCallbackServerTimerPresent_id:
			Dz1Thread_tprintf(tab, "id = "); Dz1u32_dump(&p->x.id, tab); // Value Primitive Scalar Type
			break;
		case Dz1TcpCallbackServerTimerPresent_session:
			if (p->x.session == NULL) Dz1Thread_tprintf(tab, "session = NULL\n");
			else { Dz1Thread_tprintf(tab, "session = "); Dz1TcpCallbackServerSessionTimer_dump(p->x.session, tab); } // Pointer Construct with DUMP API
			break;
		default:
			Dz1Thread_tprintf(tab, "??? = %d\n", p->present);
			break;
	}
}

int Dz1TcpCallbackServerTimer_cmp(Dz1TcpCallbackServerTimer *a, Dz1TcpCallbackServerTimer *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (a->present != b->present) return (int)(a->present - b->present);
	else
	{
		switch(a->present)
		{
			case Dz1TcpCallbackServerTimerPresent_id:
				 return (int)(a->x.id - b->x.id);
				break;
			case Dz1TcpCallbackServerTimerPresent_session:
				if (a->x.session == NULL && b->x.session == NULL) return 0;
				else if (a->x.session == NULL && b->x.session != NULL) return -1;
				else if (a->x.session != NULL && b->x.session == NULL) return 1;
				else return Dz1TcpCallbackServerSessionTimer_cmp(a->x.session, b->x.session);
				break;
			default:
				return 0;
		}
	}
}

