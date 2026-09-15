////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_web_socket_test_task_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskArg
Dz1WebSocketTaskArg *Dz1WebSocketTaskArg_new(Dz1WebSocketTaskExceptionCB cb, void *cb_param, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketTaskArg *__internal_ret = (Dz1WebSocketTaskArg *)Dz1Calloc(sizeof(Dz1WebSocketTaskArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskArg_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->cb = cb;
		__internal_ret->cb_param = cb_param;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSocketTaskArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1WebSocketTaskArg *Dz1WebSocketTaskArg_clone(Dz1WebSocketTaskArg *src, Dz1Error *err)
{
	Dz1WebSocketTaskArg *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1WebSocketTaskArg *)Dz1Calloc(sizeof(Dz1WebSocketTaskArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskArg_delAndSetNull, (void *)&ret);

		ret->cb = src->cb;
		ret->cb_param = src->cb_param;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSocketTaskArg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1WebSocketTaskArg_del(Dz1WebSocketTaskArg *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1WebSocketTaskArgA_dump(Dz1WebSocketTaskArg *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("{\n"); tab++;

	Dz1ThreadA_tprintf(tab, "cb = %p\n", p->cb); /* function pointer */

	if (p->cb_param == NULL) Dz1ThreadA_tprintf(tab, "cb_param = NULL\n");
	else Dz1ThreadA_tprintf(tab, "cb_param = %p\n", p->cb_param);

	Dz1ThreadA_tprintf(--tab, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketTaskArgW_dump(Dz1WebSocketTaskArg *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"{\n"); tab++;

	Dz1ThreadW_tprintf(tab, L"cb = %p\n", p->cb); /* function pointer */

	if (p->cb_param == NULL) Dz1ThreadW_tprintf(tab, L"cb_param = NULL\n");
	else Dz1ThreadW_tprintf(tab, L"cb_param = %p\n", p->cb_param);

	Dz1ThreadW_tprintf(--tab, L"}\n");
}
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskTimer
Dz1WebSocketTaskTimer *Dz1WebSocketTaskTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketTaskTimer *__internal_ret = (Dz1WebSocketTaskTimer *)Dz1Calloc(sizeof(Dz1WebSocketTaskTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskTimer_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->id = id;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSocketTaskTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSocketTaskTimer_del(Dz1WebSocketTaskTimer *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1WebSocketTaskTimerA_dump(Dz1WebSocketTaskTimer *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("id = "); Dz1u32A_dump(&p->id, tab);
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketTaskTimerW_dump(Dz1WebSocketTaskTimer *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"id = "); Dz1u32W_dump(&p->id, tab);
}
#endif // UNIX_SYSTEM

int Dz1WebSocketTaskTimer_cmp(Dz1WebSocketTaskTimer *a, Dz1WebSocketTaskTimer *b)
{
	int ret = 0;
	if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) return ret;
	else return ret;
}
// Dz1WebSocketTaskTimer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskEnv
Dz1WebSocketTaskEnv *Dz1WebSocketTaskEnv_new(Dz1Task *tSelf, Dz1WebSocket *wsock, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketTaskEnv *__internal_ret = (Dz1WebSocketTaskEnv *)Dz1Calloc(sizeof(Dz1WebSocketTaskEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskEnv_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->msgs = Dz1WebSockMsgList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else
		{
			__internal_ret->tSelf = tSelf;
			__internal_ret->wsock = wsock;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSocketTaskEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSocketTaskEnv_del(Dz1WebSocketTaskEnv *p)
{
	if (p == NULL) return;
	if (p->wsock) Dz1WebSocket_del(p->wsock);
	if (p->msgs) Dz1WebSockMsgList_del(p->msgs);
	if (p->pend_sg) Dz1TaskSigMsg_del(p->pend_sg);
	Dz1Free(p);
}

void Dz1WebSocketTaskEnvA_dump(Dz1WebSocketTaskEnv *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("{\n"); tab++;

	if (p->tSelf == NULL) Dz1ThreadA_tprintf(tab, "tSelf = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "tSelf = %p\n", p->tSelf); /* no way to dump */ }

	if (p->wsock == NULL) Dz1ThreadA_tprintf(tab, "wsock = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "wsock = "); Dz1WebSocketA_dump(p->wsock, tab); /* using dump func */ }

	if (p->msgs == NULL) Dz1ThreadA_tprintf(tab, "msgs = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "msgs = "); Dz1WebSockMsgListA_dump(p->msgs, tab); /* using dump func */ }

	if (p->pend_sg == NULL) Dz1ThreadA_tprintf(tab, "pend_sg = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "pend_sg = %p\n", p->pend_sg); /* no way to dump */ }

	Dz1ThreadA_tprintf(--tab, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketTaskEnvW_dump(Dz1WebSocketTaskEnv *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"{\n"); tab++;

	if (p->tSelf == NULL) Dz1ThreadW_tprintf(tab, L"tSelf = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"tSelf = %p\n", p->tSelf); /* no way to dump */ }

	if (p->wsock == NULL) Dz1ThreadW_tprintf(tab, L"wsock = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"wsock = "); Dz1WebSocketW_dump(p->wsock, tab); /* using dump func */ }

	if (p->msgs == NULL) Dz1ThreadW_tprintf(tab, L"msgs = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"msgs = "); Dz1WebSockMsgListW_dump(p->msgs, tab); /* using dump func */ }

	if (p->pend_sg == NULL) Dz1ThreadW_tprintf(tab, L"pend_sg = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"pend_sg = %p\n", p->pend_sg); /* no way to dump */ }

	Dz1ThreadW_tprintf(--tab, L"}\n");
}
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskEnv
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskMsgOpen
Dz1WebSocketTaskMsgOpen *Dz1WebSocketTaskMsgOpen_new(Dz1Asn1UTF8Str *uri, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketTaskMsgOpen *__internal_ret = (Dz1WebSocketTaskMsgOpen *)Dz1Calloc(sizeof(Dz1WebSocketTaskMsgOpen), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskMsgOpen_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->uri = uri;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSocketTaskMsgOpen_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSocketTaskMsgOpen_del(Dz1WebSocketTaskMsgOpen *p)
{
	if (p == NULL) return;
	if (p->uri) Dz1Asn1UTF8Str_del(p->uri);
	Dz1Free(p);
}

void Dz1WebSocketTaskMsgOpenA_dump(Dz1WebSocketTaskMsgOpen *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	if (p->uri == NULL) Dz1ThreadA_printf("uri = NULL\n");
	else { Dz1ThreadA_printf("uri = "); Dz1Asn1UTF8StrA_dump(p->uri, tab); }
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketTaskMsgOpenW_dump(Dz1WebSocketTaskMsgOpen *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	if (p->uri == NULL) Dz1ThreadW_printf(L"uri = NULL\n");
	else { Dz1ThreadW_printf(L"uri = "); Dz1Asn1UTF8StrW_dump(p->uri, tab); }
}
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskMsgOpen
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskMsgSendPresent
static struct Dz1WebSocketTaskMsgSendPresentMapA
{
	str_t str;
	Dz1WebSocketTaskMsgSendPresent v;
} Dz1WebSocketTaskMsgSendPresentMapA[] =
{
	{ (char *)"text", Dz1WebSocketTaskMsgSendPresent_text },
	{ (char *)"bin", Dz1WebSocketTaskMsgSendPresent_bin },
	{ (char *)"ping", Dz1WebSocketTaskMsgSendPresent_ping },
	{ NULL, Dz1WebSocketTaskMsgSendPresent_max }
};

str_t Dz1WebSocketTaskMsgSendPresentStrA(Dz1WebSocketTaskMsgSendPresent v)
{
	struct Dz1WebSocketTaskMsgSendPresentMapA *i = NULL;
	for (i = Dz1WebSocketTaskMsgSendPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSocketTaskMsgSendPresent Dz1WebSocketTaskMsgSendPresentFromStrA(str_t str)
{
	struct Dz1WebSocketTaskMsgSendPresentMapA *i = NULL;
	for (i = Dz1WebSocketTaskMsgSendPresentMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1WebSocketTaskMsgSendPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1WebSocketTaskMsgSendPresentMapW
{
	wstr_t str;
	Dz1WebSocketTaskMsgSendPresent v;
} Dz1WebSocketTaskMsgSendPresentMapW[] =
{
	{ (wchar_t *)L"text", Dz1WebSocketTaskMsgSendPresent_text },
	{ (wchar_t *)L"bin", Dz1WebSocketTaskMsgSendPresent_bin },
	{ (wchar_t *)L"ping", Dz1WebSocketTaskMsgSendPresent_ping },
	{ NULL, Dz1WebSocketTaskMsgSendPresent_max }
};

wstr_t Dz1WebSocketTaskMsgSendPresentStrW(Dz1WebSocketTaskMsgSendPresent v)
{
	struct Dz1WebSocketTaskMsgSendPresentMapW *i = NULL;
	for (i = Dz1WebSocketTaskMsgSendPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSocketTaskMsgSendPresent Dz1WebSocketTaskMsgSendPresentFromStrW(wstr_t str)
{
	struct Dz1WebSocketTaskMsgSendPresentMapW *i = NULL;
	for (i = Dz1WebSocketTaskMsgSendPresentMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1WebSocketTaskMsgSendPresent_max;
}
#endif // UNIX_SYSTEM

Dz1WebSocketTaskMsgSendPresent *Dz1WebSocketTaskMsgSendPresent_new(Dz1WebSocketTaskMsgSendPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketTaskMsgSendPresent *__internal_ret = (Dz1WebSocketTaskMsgSendPresent *)Dz1Calloc(sizeof(Dz1WebSocketTaskMsgSendPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1WebSocketTaskMsgSendPresentA_dump(Dz1WebSocketTaskMsgSendPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1WebSocketTaskMsgSendPresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketTaskMsgSendPresentW_dump(Dz1WebSocketTaskMsgSendPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1WebSocketTaskMsgSendPresentStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskMsgSendPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskMsgSend
Dz1WebSocketTaskMsgSend *Dz1WebSocketTaskMsgSend_new(Dz1WebSocketTaskMsgSendPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketTaskMsgSend *ret = (Dz1WebSocketTaskMsgSend *)Dz1Calloc(sizeof(Dz1WebSocketTaskMsgSend), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskMsgSend_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
			case Dz1WebSocketTaskMsgSendPresent_text:
				ret->x.text = (Dz1Asn1UTF8Str *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1WebSocketTaskMsgSendPresent_bin:
				ret->x.bin = (Dz1Binary *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1WebSocketTaskMsgSendPresent_ping:
				ret->x.ping = (Dz1Binary *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1WebSocketTaskMsgSendPresent_max:
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSocketTaskMsgSend_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1WebSocketTaskMsgSend_del(Dz1WebSocketTaskMsgSend *p)
{
	if (!p) return;
	switch(p->present)
	{
		case Dz1WebSocketTaskMsgSendPresent_text:
			if (p->x.text) Dz1Asn1UTF8Str_del(p->x.text);
			break;
		case Dz1WebSocketTaskMsgSendPresent_bin:
			if (p->x.bin) Dz1Binary_del(p->x.bin);
			break;
		case Dz1WebSocketTaskMsgSendPresent_ping:
			if (p->x.ping) Dz1Binary_del(p->x.ping);
			break;
		default:
			break;
	}
	Dz1Free(p);
}

void Dz1WebSocketTaskMsgSendA_dump(Dz1WebSocketTaskMsgSend *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	switch(p->present)
	{
		case Dz1WebSocketTaskMsgSendPresent_text:
			if (p->x.text == NULL) Dz1ThreadA_tprintf(tab, "text = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "text = "); Dz1Asn1UTF8StrA_dump(p->x.text, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1WebSocketTaskMsgSendPresent_bin:
			if (p->x.bin == NULL) Dz1ThreadA_tprintf(tab, "bin = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "bin = "); Dz1BinaryA_dump(p->x.bin, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1WebSocketTaskMsgSendPresent_ping:
			if (p->x.ping == NULL) Dz1ThreadA_tprintf(tab, "ping = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "ping = "); Dz1BinaryA_dump(p->x.ping, tab); } // Pointer Construct with DUMP API
			break;
		default:
			Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
			break;
	}
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketTaskMsgSendW_dump(Dz1WebSocketTaskMsgSend *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	switch(p->present)
	{
		case Dz1WebSocketTaskMsgSendPresent_text:
			if (p->x.text == NULL) Dz1ThreadW_tprintf(tab, L"text = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"text = "); Dz1Asn1UTF8StrW_dump(p->x.text, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1WebSocketTaskMsgSendPresent_bin:
			if (p->x.bin == NULL) Dz1ThreadW_tprintf(tab, L"bin = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"bin = "); Dz1BinaryW_dump(p->x.bin, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1WebSocketTaskMsgSendPresent_ping:
			if (p->x.ping == NULL) Dz1ThreadW_tprintf(tab, L"ping = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"ping = "); Dz1BinaryW_dump(p->x.ping, tab); } // Pointer Construct with DUMP API
			break;
		default:
			Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
			break;
	}
}
#endif // UNIX_SYSTEM

// Dz1WebSocketTaskMsgSend
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskMsgClose
Dz1WebSocketTaskMsgClose *Dz1WebSocketTaskMsgClose_new(Dz1Asn1UTF8Str *opt_text, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketTaskMsgClose *__internal_ret = (Dz1WebSocketTaskMsgClose *)Dz1Calloc(sizeof(Dz1WebSocketTaskMsgClose), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskMsgClose_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->opt_text = opt_text;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSocketTaskMsgClose_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSocketTaskMsgClose_del(Dz1WebSocketTaskMsgClose *p)
{
	if (p == NULL) return;
	if (p->opt_text) Dz1Asn1UTF8Str_del(p->opt_text);
	Dz1Free(p);
}

void Dz1WebSocketTaskMsgCloseA_dump(Dz1WebSocketTaskMsgClose *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	if (p->opt_text == NULL) Dz1ThreadA_printf("opt_text = NULL\n");
	else { Dz1ThreadA_printf("opt_text = "); Dz1Asn1UTF8StrA_dump(p->opt_text, tab); }
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketTaskMsgCloseW_dump(Dz1WebSocketTaskMsgClose *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	if (p->opt_text == NULL) Dz1ThreadW_printf(L"opt_text = NULL\n");
	else { Dz1ThreadW_printf(L"opt_text = "); Dz1Asn1UTF8StrW_dump(p->opt_text, tab); }
}
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskMsgClose
////////////////////////////////////////////////////////////////////////////////

