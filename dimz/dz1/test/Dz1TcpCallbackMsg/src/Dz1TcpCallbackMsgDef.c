#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpCallbackMsgDef.h"

Dz1TcpCallbackEcho *Dz1TcpCallbackEcho_new(u32_t echoID, Dz1TimeVal *stamp, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackEcho *__internal_ret = (Dz1TcpCallbackEcho *)Dz1Calloc(sizeof(Dz1TcpCallbackEcho), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackEcho_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->echoID = echoID;
		__internal_ret->stamp = stamp;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackEcho_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1TcpCallbackEcho *Dz1TcpCallbackEcho_clone(Dz1TcpCallbackEcho *src, Dz1Error *err)
{
	Dz1TcpCallbackEcho *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpCallbackEcho *)Dz1Calloc(sizeof(Dz1TcpCallbackEcho), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackEcho_delAndSetNull, (void *)&ret);

		if (src->stamp && (ret->stamp = Dz1TimeVal_clone(src->stamp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->echoID = src->echoID;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackEcho_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpCallbackEcho_del(Dz1TcpCallbackEcho *p)
{
	if (p == NULL) return;
	if (p->stamp) Dz1TimeVal_del(p->stamp);
	Dz1Free(p);
}

void Dz1TcpCallbackEcho_dump(Dz1TcpCallbackEcho *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "echoID = "); Dz1u32_dump(&p->echoID, tab);

	if (p->stamp == NULL) Dz1Thread_tprintf(tab, "stamp = NULL\n");
	else { Dz1Thread_tprintf(tab, "stamp = "); Dz1TimeVal_dump(p->stamp, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, "}\n");
}

static struct Dz1TcpCallbackMsgPresentMapA
{
	str_t str;
	Dz1TcpCallbackMsgPresent v;
} Dz1TcpCallbackMsgPresentMapA[] =
{
	{ "echo", Dz1TcpCallbackMsgPresent_echo },
	{ NULL, Dz1TcpCallbackMsgPresent_max }
};

str_t Dz1TcpCallbackMsgPresentStrA(Dz1TcpCallbackMsgPresent v)
{
	struct Dz1TcpCallbackMsgPresentMapA *i = NULL;
	for (i = Dz1TcpCallbackMsgPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpCallbackMsgPresent Dz1TcpCallbackMsgPresentFromStrA(str_t str)
{
	struct Dz1TcpCallbackMsgPresentMapA *i = NULL;
	for (i = Dz1TcpCallbackMsgPresentMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1TcpCallbackMsgPresent_max;
}

static struct Dz1TcpCallbackMsgPresentMapW
{
	wstr_t str;
	Dz1TcpCallbackMsgPresent v;
} Dz1TcpCallbackMsgPresentMapW[] =
{
	{ L"echo", Dz1TcpCallbackMsgPresent_echo },
	{ NULL, Dz1TcpCallbackMsgPresent_max }
};

wstr_t Dz1TcpCallbackMsgPresentStrW(Dz1TcpCallbackMsgPresent v)
{
	struct Dz1TcpCallbackMsgPresentMapW *i = NULL;
	for (i = Dz1TcpCallbackMsgPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpCallbackMsgPresent Dz1TcpCallbackMsgPresentFromStrW(wstr_t str)
{
	struct Dz1TcpCallbackMsgPresentMapW *i = NULL;
	for (i = Dz1TcpCallbackMsgPresentMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1TcpCallbackMsgPresent_max;
}

Dz1TcpCallbackMsgPresent *Dz1TcpCallbackMsgPresent_new(Dz1TcpCallbackMsgPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackMsgPresent *__internal_ret = (Dz1TcpCallbackMsgPresent *)Dz1Calloc(sizeof(Dz1TcpCallbackMsgPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1TcpCallbackMsgPresent_dump(Dz1TcpCallbackMsgPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf("NULL\n");
	else Dz1Thread_printf("%s\n", Dz1TcpCallbackMsgPresentStrA(*v));
}

Dz1TcpCallbackMsg *Dz1TcpCallbackMsg_new(Dz1TcpCallbackMsgPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackMsg *ret = (Dz1TcpCallbackMsg *)Dz1Calloc(sizeof(Dz1TcpCallbackMsg), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackMsg_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
			case Dz1TcpCallbackMsgPresent_echo:
				ret->x.echo = (Dz1TcpCallbackEcho *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1TcpCallbackMsgPresent_max:
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackMsg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1TcpCallbackMsg *Dz1TcpCallbackMsg_clone(Dz1TcpCallbackMsg *src, Dz1Error *err)
{
	Dz1TcpCallbackMsg *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TcpCallbackMsg *)Dz1Calloc(sizeof(Dz1TcpCallbackMsg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackMsg_delAndSetNull, (void *)&ret);

		ret->present = src->present;
		switch(ret->present)
		{
			case Dz1TcpCallbackMsgPresent_echo:
				if (src->x.echo && (ret->x.echo = Dz1TcpCallbackEcho_clone(src->x.echo, errp)) == NULL) { ERR_OUT(errp); }
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackMsg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpCallbackMsg_del(Dz1TcpCallbackMsg *p)
{
	if (!p) return;
	switch(p->present)
	{
		case Dz1TcpCallbackMsgPresent_echo:
			if (p->x.echo) Dz1TcpCallbackEcho_del(p->x.echo);
			break;
		default:
			break;
	}
	Dz1Free(p);
}

void Dz1TcpCallbackMsg_dump(Dz1TcpCallbackMsg *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	switch(p->present)
	{
		case Dz1TcpCallbackMsgPresent_echo:
			if (p->x.echo == NULL) Dz1Thread_tprintf(tab, "echo = NULL\n");
			else { Dz1Thread_tprintf(tab, "echo = "); Dz1TcpCallbackEcho_dump(p->x.echo, tab); } // Pointer Construct with DUMP API
			break;
		default:
			Dz1Thread_tprintf(tab, "??? = %d\n", p->present);
			break;
	}
}

