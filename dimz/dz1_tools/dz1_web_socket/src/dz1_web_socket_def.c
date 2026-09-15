////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_web_socket_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockOpCode
static struct Dz1WebSockOpCodeMapA
{
	str_t str;
	Dz1WebSockOpCode v;
} Dz1WebSockOpCodeMapA[] =
{
	{ (char *)"unknown", Dz1WebSockOpCode_unknown },
	{ (char *)"text", Dz1WebSockOpCode_text },
	{ (char *)"binary", Dz1WebSockOpCode_binary },
	{ (char *)"terminate", Dz1WebSockOpCode_terminate },
	{ (char *)"ping", Dz1WebSockOpCode_ping },
	{ (char *)"pong", Dz1WebSockOpCode_pong },
	{ NULL, Dz1WebSockOpCode_max }
};

str_t Dz1WebSockOpCodeStrA(Dz1WebSockOpCode v)
{
	struct Dz1WebSockOpCodeMapA *i = NULL;
	for (i = Dz1WebSockOpCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSockOpCode Dz1WebSockOpCodeFromStrA(str_t str)
{
	struct Dz1WebSockOpCodeMapA *i = NULL;
	for (i = Dz1WebSockOpCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSockOpCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1WebSockOpCodeMapW
{
	wstr_t str;
	Dz1WebSockOpCode v;
} Dz1WebSockOpCodeMapW[] =
{
	{ (wchar_t *)L"unknown", Dz1WebSockOpCode_unknown },
	{ (wchar_t *)L"text", Dz1WebSockOpCode_text },
	{ (wchar_t *)L"binary", Dz1WebSockOpCode_binary },
	{ (wchar_t *)L"terminate", Dz1WebSockOpCode_terminate },
	{ (wchar_t *)L"ping", Dz1WebSockOpCode_ping },
	{ (wchar_t *)L"pong", Dz1WebSockOpCode_pong },
	{ NULL, Dz1WebSockOpCode_max }
};

wstr_t Dz1WebSockOpCodeStrW(Dz1WebSockOpCode v)
{
	struct Dz1WebSockOpCodeMapW *i = NULL;
	for (i = Dz1WebSockOpCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSockOpCode Dz1WebSockOpCodeFromStrW(wstr_t str)
{
	struct Dz1WebSockOpCodeMapW *i = NULL;
	for (i = Dz1WebSockOpCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSockOpCode_max;
}
#endif // UNIX_SYSTEM

Dz1WebSockOpCode *Dz1WebSockOpCode_new(Dz1WebSockOpCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSockOpCode *__internal_ret = (Dz1WebSockOpCode *)Dz1Calloc(sizeof(Dz1WebSockOpCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1WebSockOpCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockMsg
Dz1WebSockMsg *Dz1WebSockMsg_new(Dz1WebSockOpCode op, Dz1Binary *payload, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSockMsg *__internal_ret = (Dz1WebSockMsg *)Dz1Calloc(sizeof(Dz1WebSockMsg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSockMsg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->op = op;
		__internal_ret->payload = payload;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSockMsg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSockMsg_purge(Dz1WebSockMsg *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->payload);
}

void Dz1WebSockMsg_del(Dz1WebSockMsg *p)
{
	if (p == NULL) return;
	Dz1WebSockMsg_purge(p);
	Dz1Free(p);
}

void Dz1WebSockMsgA_dump(Dz1WebSockMsg *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "op = %s(%d)\n", Dz1WebSockOpCodeStrA(p->op), p->op);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "payload = "); Dz1BinaryA_dump(p->payload, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1WebSockMsgW_dump(Dz1WebSockMsg *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"op = %s(%d)\n", Dz1WebSockOpCodeStrW(p->op), p->op);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"payload = "); Dz1BinaryW_dump(p->payload, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1WebSockMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockMsgList
static Dz1Error Dz1WebSockMsgList_add(Dz1WebSockMsgList *p, Dz1WebSockMsg *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static Dz1WebSockMsg *Dz1WebSockMsgList_extract(Dz1WebSockMsgList *p, Dz1WebSockMsg *ptr)
{
	return (Dz1WebSockMsg *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct Dz1WebSockMsgListMkArrArg
{
	Dz1WebSockMsg **arr;
	unsigned int idx;
} Dz1WebSockMsgListMkArrArg;

static Dz1Error _Dz1WebSockMsgList_get_array(void *ptr, Dz1WebSockMsg *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1WebSockMsgListMkArrArg *arg = (Dz1WebSockMsgListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1WebSockMsg **Dz1WebSockMsgList_get_array(Dz1WebSockMsgList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1WebSockMsg **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1WebSockMsg **)Dz1Calloc(sizeof(Dz1WebSockMsg *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1WebSockMsgListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1WebSockMsgList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error Dz1WebSockMsgList_travelForward(Dz1WebSockMsgList *p, Dz1Error (*func)(void *ptr, Dz1WebSockMsg *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1WebSockMsgList_travelBackward(Dz1WebSockMsgList *p, Dz1Error (*func)(void *ptr, Dz1WebSockMsg *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1WebSockMsgList_count(Dz1WebSockMsgList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1WebSockMsgList *Dz1WebSockMsgList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSockMsgList *ret = (Dz1WebSockMsgList *)Dz1Calloc(sizeof(Dz1WebSockMsgList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WebSockMsgList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1WebSockMsg_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1WebSockMsgList_count;
			ret->travel = Dz1WebSockMsgList_travelForward;
			ret->travelForward = Dz1WebSockMsgList_travelForward;
			ret->travelBackward = Dz1WebSockMsgList_travelBackward;
			ret->get_array = Dz1WebSockMsgList_get_array;
			ret->add = Dz1WebSockMsgList_add;
			ret->extract = Dz1WebSockMsgList_extract;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSockMsgList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1WebSockMsgList_purge(Dz1WebSockMsgList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1WebSockMsgList_del(Dz1WebSockMsgList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1WebSockMsgListA_dump(void *ptr, Dz1WebSockMsg *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1WebSockMsgA_dump(p, tab);
	return err;
}

void Dz1WebSockMsgListA_dump(Dz1WebSockMsgList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Dz1WebSockMsgListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _Dz1WebSockMsgListW_dump(void *ptr, Dz1WebSockMsg *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1WebSockMsgW_dump(p, tab);
	return err;
}

void Dz1WebSockMsgListW_dump(Dz1WebSockMsgList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Dz1WebSockMsgListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1WebSockMsgList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketScheme
static struct Dz1WebSocketSchemeMapA
{
	str_t str;
	Dz1WebSocketScheme v;
} Dz1WebSocketSchemeMapA[] =
{
	{ (char *)"ws", Dz1WebSocketScheme_ws },
	{ (char *)"wss", Dz1WebSocketScheme_wss },
	{ NULL, Dz1WebSocketScheme_max }
};

str_t Dz1WebSocketSchemeStrA(Dz1WebSocketScheme v)
{
	struct Dz1WebSocketSchemeMapA *i = NULL;
	for (i = Dz1WebSocketSchemeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSocketScheme Dz1WebSocketSchemeFromStrA(str_t str)
{
	struct Dz1WebSocketSchemeMapA *i = NULL;
	for (i = Dz1WebSocketSchemeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSocketScheme_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1WebSocketSchemeMapW
{
	wstr_t str;
	Dz1WebSocketScheme v;
} Dz1WebSocketSchemeMapW[] =
{
	{ (wchar_t *)L"ws", Dz1WebSocketScheme_ws },
	{ (wchar_t *)L"wss", Dz1WebSocketScheme_wss },
	{ NULL, Dz1WebSocketScheme_max }
};

wstr_t Dz1WebSocketSchemeStrW(Dz1WebSocketScheme v)
{
	struct Dz1WebSocketSchemeMapW *i = NULL;
	for (i = Dz1WebSocketSchemeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSocketScheme Dz1WebSocketSchemeFromStrW(wstr_t str)
{
	struct Dz1WebSocketSchemeMapW *i = NULL;
	for (i = Dz1WebSocketSchemeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSocketScheme_max;
}
#endif // UNIX_SYSTEM

Dz1WebSocketScheme *Dz1WebSocketScheme_new(Dz1WebSocketScheme *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketScheme *__internal_ret = (Dz1WebSocketScheme *)Dz1Calloc(sizeof(Dz1WebSocketScheme), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1WebSocketSchemeA_dump(Dz1WebSocketScheme *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1WebSocketSchemeStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketSchemeW_dump(Dz1WebSocketScheme *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1WebSocketSchemeStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1WebSocketScheme
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketState
static struct Dz1WebSocketStateMapA
{
	str_t str;
	Dz1WebSocketState v;
} Dz1WebSocketStateMapA[] =
{
	{ (char *)"init", Dz1WebSocketState_init },
	{ (char *)"requested", Dz1WebSocketState_requested },
	{ (char *)"established", Dz1WebSocketState_established },
	{ (char *)"closing", Dz1WebSocketState_closing },
	{ (char *)"closed", Dz1WebSocketState_closed },
	{ NULL, Dz1WebSocketState_max }
};

str_t Dz1WebSocketStateStrA(Dz1WebSocketState v)
{
	struct Dz1WebSocketStateMapA *i = NULL;
	for (i = Dz1WebSocketStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSocketState Dz1WebSocketStateFromStrA(str_t str)
{
	struct Dz1WebSocketStateMapA *i = NULL;
	for (i = Dz1WebSocketStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSocketState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1WebSocketStateMapW
{
	wstr_t str;
	Dz1WebSocketState v;
} Dz1WebSocketStateMapW[] =
{
	{ (wchar_t *)L"init", Dz1WebSocketState_init },
	{ (wchar_t *)L"requested", Dz1WebSocketState_requested },
	{ (wchar_t *)L"established", Dz1WebSocketState_established },
	{ (wchar_t *)L"closing", Dz1WebSocketState_closing },
	{ (wchar_t *)L"closed", Dz1WebSocketState_closed },
	{ NULL, Dz1WebSocketState_max }
};

wstr_t Dz1WebSocketStateStrW(Dz1WebSocketState v)
{
	struct Dz1WebSocketStateMapW *i = NULL;
	for (i = Dz1WebSocketStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSocketState Dz1WebSocketStateFromStrW(wstr_t str)
{
	struct Dz1WebSocketStateMapW *i = NULL;
	for (i = Dz1WebSocketStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSocketState_max;
}
#endif // UNIX_SYSTEM

Dz1WebSocketState *Dz1WebSocketState_new(Dz1WebSocketState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketState *__internal_ret = (Dz1WebSocketState *)Dz1Calloc(sizeof(Dz1WebSocketState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1WebSocketStateA_dump(Dz1WebSocketState *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1WebSocketStateStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketStateW_dump(Dz1WebSocketState *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1WebSocketStateStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1WebSocketState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketAuth
Dz1WebSocketAuth *Dz1WebSocketAuth_new(Dz1Binary *key_bin, Dz1Binary *cnf_bin, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketAuth *__internal_ret = (Dz1WebSocketAuth *)Dz1Calloc(sizeof(Dz1WebSocketAuth), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSocketAuth_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->key_bin = key_bin;
		__internal_ret->cnf_bin = cnf_bin;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSocketAuth_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSocketAuth_purge(Dz1WebSocketAuth *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->key_bin);
	Dz1Binary_del(p->cnf_bin);
}

void Dz1WebSocketAuth_del(Dz1WebSocketAuth *p)
{
	if (p == NULL) return;
	Dz1WebSocketAuth_purge(p);
	Dz1Free(p);
}

void Dz1WebSocketAuthA_dump(Dz1WebSocketAuth *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "key_bin = "); Dz1BinaryA_dump(p->key_bin, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "cnf_bin = "); Dz1BinaryA_dump(p->cnf_bin, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketAuthW_dump(Dz1WebSocketAuth *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"key_bin = "); Dz1BinaryW_dump(p->key_bin, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"cnf_bin = "); Dz1BinaryW_dump(p->cnf_bin, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1WebSocketAuth
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecFrame
Dz1WebSockDecFrame *Dz1WebSockDecFrame_new(bool_t is_fin, 
										   Dz1WebSockOpCode op_code, 
										   u64_t payload_len, 
										   u32_t *mask, 
										   Dz1ElasticBuf *payload, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSockDecFrame *__internal_ret = (Dz1WebSockDecFrame *)Dz1Calloc(sizeof(Dz1WebSockDecFrame), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSockDecFrame_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->is_fin = is_fin;
		__internal_ret->op_code = op_code;
		__internal_ret->payload_len = payload_len;
		__internal_ret->mask = mask;
		__internal_ret->payload = payload;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSockDecFrame_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSockDecFrame_purge(Dz1WebSockDecFrame *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->mask);
	Dz1ElasticBuf_del(p->payload);
}

void Dz1WebSockDecFrame_del(Dz1WebSockDecFrame *p)
{
	if (p == NULL) return;
	Dz1WebSockDecFrame_purge(p);
	Dz1Free(p);
}

void Dz1WebSockDecFrameA_dump(Dz1WebSockDecFrame *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "is_fin = "); Dz1BoolA_dump(&p->is_fin, tab); 
		Dz1ThreadA_tprintf(tab, "op_code = %s(%d)\n", Dz1WebSockOpCodeStrA(p->op_code), p->op_code);
		Dz1ThreadA_tprintf(tab, "payload_len = "); Dz1u64A_dump(&p->payload_len, tab); 
		Dz1ThreadA_tprintf(tab, "mask = "); Dz1u32A_dump(p->mask, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "payload = %p\n", p->payload);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1WebSockDecFrameW_dump(Dz1WebSockDecFrame *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"is_fin = "); Dz1BoolW_dump(&p->is_fin, tab); 
		Dz1ThreadW_tprintf(tab, L"op_code = %s(%d)\n", Dz1WebSockOpCodeStrW(p->op_code), p->op_code);
		Dz1ThreadW_tprintf(tab, L"payload_len = "); Dz1u64W_dump(&p->payload_len, tab); 
		Dz1ThreadW_tprintf(tab, L"mask = "); Dz1u32W_dump(p->mask, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"payload = %p\n", p->payload);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1WebSockDecFrame
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecFrameList
static Dz1Error Dz1WebSockDecFrameList_add(Dz1WebSockDecFrameList *p, Dz1WebSockDecFrame *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static Dz1WebSockDecFrame *Dz1WebSockDecFrameList_extract(Dz1WebSockDecFrameList *p, Dz1WebSockDecFrame *ptr)
{
	return (Dz1WebSockDecFrame *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct Dz1WebSockDecFrameListMkArrArg
{
	Dz1WebSockDecFrame **arr;
	unsigned int idx;
} Dz1WebSockDecFrameListMkArrArg;

static Dz1Error _Dz1WebSockDecFrameList_get_array(void *ptr, Dz1WebSockDecFrame *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1WebSockDecFrameListMkArrArg *arg = (Dz1WebSockDecFrameListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1WebSockDecFrame **Dz1WebSockDecFrameList_get_array(Dz1WebSockDecFrameList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1WebSockDecFrame **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1WebSockDecFrame **)Dz1Calloc(sizeof(Dz1WebSockDecFrame *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1WebSockDecFrameListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1WebSockDecFrameList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error Dz1WebSockDecFrameList_travelForward(Dz1WebSockDecFrameList *p, Dz1Error (*func)(void *ptr, Dz1WebSockDecFrame *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1WebSockDecFrameList_travelBackward(Dz1WebSockDecFrameList *p, Dz1Error (*func)(void *ptr, Dz1WebSockDecFrame *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1WebSockDecFrameList_count(Dz1WebSockDecFrameList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1WebSockDecFrameList *Dz1WebSockDecFrameList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSockDecFrameList *ret = (Dz1WebSockDecFrameList *)Dz1Calloc(sizeof(Dz1WebSockDecFrameList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WebSockDecFrameList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1WebSockDecFrame_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1WebSockDecFrameList_count;
			ret->travel = Dz1WebSockDecFrameList_travelForward;
			ret->travelForward = Dz1WebSockDecFrameList_travelForward;
			ret->travelBackward = Dz1WebSockDecFrameList_travelBackward;
			ret->get_array = Dz1WebSockDecFrameList_get_array;
			ret->add = Dz1WebSockDecFrameList_add;
			ret->extract = Dz1WebSockDecFrameList_extract;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSockDecFrameList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1WebSockDecFrameList_purge(Dz1WebSockDecFrameList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1WebSockDecFrameList_del(Dz1WebSockDecFrameList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1WebSockDecFrameListA_dump(void *ptr, Dz1WebSockDecFrame *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1WebSockDecFrameA_dump(p, tab);
	return err;
}

void Dz1WebSockDecFrameListA_dump(Dz1WebSockDecFrameList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Dz1WebSockDecFrameListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _Dz1WebSockDecFrameListW_dump(void *ptr, Dz1WebSockDecFrame *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1WebSockDecFrameW_dump(p, tab);
	return err;
}

void Dz1WebSockDecFrameListW_dump(Dz1WebSockDecFrameList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Dz1WebSockDecFrameListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1WebSockDecFrameList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecState
static struct Dz1WebSockDecStateMapA
{
	str_t str;
	Dz1WebSockDecState v;
} Dz1WebSockDecStateMapA[] =
{
	{ (char *)"fin_opcode", Dz1WebSockDecState_fin_opcode },
	{ (char *)"mask_len0", Dz1WebSockDecState_mask_len0 },
	{ (char *)"ext_len2", Dz1WebSockDecState_ext_len2 },
	{ (char *)"ext_len8", Dz1WebSockDecState_ext_len8 },
	{ (char *)"mask", Dz1WebSockDecState_mask },
	{ (char *)"payload", Dz1WebSockDecState_payload },
	{ NULL, Dz1WebSockDecState_max }
};

str_t Dz1WebSockDecStateStrA(Dz1WebSockDecState v)
{
	struct Dz1WebSockDecStateMapA *i = NULL;
	for (i = Dz1WebSockDecStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSockDecState Dz1WebSockDecStateFromStrA(str_t str)
{
	struct Dz1WebSockDecStateMapA *i = NULL;
	for (i = Dz1WebSockDecStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSockDecState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1WebSockDecStateMapW
{
	wstr_t str;
	Dz1WebSockDecState v;
} Dz1WebSockDecStateMapW[] =
{
	{ (wchar_t *)L"fin_opcode", Dz1WebSockDecState_fin_opcode },
	{ (wchar_t *)L"mask_len0", Dz1WebSockDecState_mask_len0 },
	{ (wchar_t *)L"ext_len2", Dz1WebSockDecState_ext_len2 },
	{ (wchar_t *)L"ext_len8", Dz1WebSockDecState_ext_len8 },
	{ (wchar_t *)L"mask", Dz1WebSockDecState_mask },
	{ (wchar_t *)L"payload", Dz1WebSockDecState_payload },
	{ NULL, Dz1WebSockDecState_max }
};

wstr_t Dz1WebSockDecStateStrW(Dz1WebSockDecState v)
{
	struct Dz1WebSockDecStateMapW *i = NULL;
	for (i = Dz1WebSockDecStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSockDecState Dz1WebSockDecStateFromStrW(wstr_t str)
{
	struct Dz1WebSockDecStateMapW *i = NULL;
	for (i = Dz1WebSockDecStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSockDecState_max;
}
#endif // UNIX_SYSTEM

Dz1WebSockDecState *Dz1WebSockDecState_new(Dz1WebSockDecState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSockDecState *__internal_ret = (Dz1WebSockDecState *)Dz1Calloc(sizeof(Dz1WebSockDecState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1WebSockDecState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecCtx
Dz1WebSockDecCtx *Dz1WebSockDecCtx_new(Dz1WebSockDecState state, 
									   u64_t len_remain, 
									   Dz1WebSockDecFrame *wip, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSockDecCtx *__internal_ret = (Dz1WebSockDecCtx *)Dz1Calloc(sizeof(Dz1WebSockDecCtx), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSockDecCtx_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->wip_list = Dz1WebSockDecFrameList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->state = state;
			__internal_ret->len_remain = len_remain;
			__internal_ret->wip = wip;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSockDecCtx_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSockDecCtx_purge(Dz1WebSockDecCtx *p)
{
	if (p == NULL) return;
	Dz1WebSockDecFrame_del(p->wip);
	Dz1WebSockDecFrameList_del(p->wip_list);
}

void Dz1WebSockDecCtx_del(Dz1WebSockDecCtx *p)
{
	if (p == NULL) return;
	Dz1WebSockDecCtx_purge(p);
	Dz1Free(p);
}

void Dz1WebSockDecCtxA_dump(Dz1WebSockDecCtx *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "state = %s(%d)\n", Dz1WebSockDecStateStrA(p->state), p->state);
		Dz1ThreadA_tprintf(tab, "len_remain = "); Dz1u64A_dump(&p->len_remain, tab); 
		// Normal member
		Dz1ThreadA_tprintf(tab, "wip = "); Dz1WebSockDecFrameA_dump(p->wip, tab); 
		Dz1ThreadA_tprintf(tab, "wip_list = "); Dz1WebSockDecFrameListA_dump(p->wip_list, tab); 
		Dz1ThreadA_tprintf(tab, "mask_idx = "); Dz1u32A_dump(&p->mask_idx, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1WebSockDecCtxW_dump(Dz1WebSockDecCtx *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"state = %s(%d)\n", Dz1WebSockDecStateStrW(p->state), p->state);
		Dz1ThreadW_tprintf(tab, L"len_remain = "); Dz1u64W_dump(&p->len_remain, tab); 
		// Normal member
		Dz1ThreadW_tprintf(tab, L"wip = "); Dz1WebSockDecFrameW_dump(p->wip, tab); 
		Dz1ThreadW_tprintf(tab, L"wip_list = "); Dz1WebSockDecFrameListW_dump(p->wip_list, tab); 
		Dz1ThreadW_tprintf(tab, L"mask_idx = "); Dz1u32W_dump(&p->mask_idx, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1WebSockDecCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocket
Dz1WebSocket *Dz1WebSocket_new(Dz1SockAddr *peer, 
							   Dz1SockAddr *local, 
							   Dz1TcpClientSocket *sock, 
							   Dz1SockUtilTxFifo *tx_fifo, 
							   bool_t masking, 
							   Dz1WebSockDecCtx *ctx, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocket *__internal_ret = (Dz1WebSocket *)Dz1Calloc(sizeof(Dz1WebSocket), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WebSocket_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->msgs = Dz1WebSockMsgList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer = peer;
			__internal_ret->local = local;
			__internal_ret->sock = sock;
			__internal_ret->tx_fifo = tx_fifo;
			__internal_ret->masking = masking;
			__internal_ret->ctx = ctx;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WebSocket_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1WebSocket_purge(Dz1WebSocket *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
	Dz1WebSocketAuth_del(p->auth);
	Dz1WebSockDecCtx_del(p->ctx);
	Dz1WebSockMsgList_del(p->msgs);
}

void Dz1WebSocket_del(Dz1WebSocket *p)
{
	if (p == NULL) return;
	Dz1WebSocket_purge(p);
	Dz1Free(p);
}

void Dz1WebSocketA_dump(Dz1WebSocket *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "peer = "); Dz1SockAddrA_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "local = "); Dz1SockAddrA_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "sock = %p\n", p->sock);
		// Normal member
		Dz1ThreadA_tprintf(tab, "tx_fifo = "); Dz1SockUtilTxFifoA_dump(p->tx_fifo, tab); 
		Dz1ThreadA_tprintf(tab, "state = %s(%d)\n", Dz1WebSocketStateStrA(p->state), p->state);
		// Normal member
		Dz1ThreadA_tprintf(tab, "auth = "); Dz1WebSocketAuthA_dump(p->auth, tab); 
		Dz1ThreadA_tprintf(tab, "masking = "); Dz1BoolA_dump(&p->masking, tab); 
		// Normal member
		Dz1ThreadA_tprintf(tab, "ctx = "); Dz1WebSockDecCtxA_dump(p->ctx, tab); 
		Dz1ThreadA_tprintf(tab, "msgs = "); Dz1WebSockMsgListA_dump(p->msgs, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketW_dump(Dz1WebSocket *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"peer = "); Dz1SockAddrW_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"local = "); Dz1SockAddrW_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"sock = %p\n", p->sock);
		// Normal member
		Dz1ThreadW_tprintf(tab, L"tx_fifo = "); Dz1SockUtilTxFifoW_dump(p->tx_fifo, tab); 
		Dz1ThreadW_tprintf(tab, L"state = %s(%d)\n", Dz1WebSocketStateStrW(p->state), p->state);
		// Normal member
		Dz1ThreadW_tprintf(tab, L"auth = "); Dz1WebSocketAuthW_dump(p->auth, tab); 
		Dz1ThreadW_tprintf(tab, L"masking = "); Dz1BoolW_dump(&p->masking, tab); 
		// Normal member
		Dz1ThreadW_tprintf(tab, L"ctx = "); Dz1WebSockDecCtxW_dump(p->ctx, tab); 
		Dz1ThreadW_tprintf(tab, L"msgs = "); Dz1WebSockMsgListW_dump(p->msgs, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1WebSocket
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketCloseReason
static struct Dz1WebSocketCloseReasonMapA
{
	str_t str;
	Dz1WebSocketCloseReason v;
} Dz1WebSocketCloseReasonMapA[] =
{
	{ (char *)"normal_close", Dz1WebSocketCloseReason_normal_close },
	{ (char *)"process_shutdown", Dz1WebSocketCloseReason_process_shutdown },
	{ (char *)"protocol_error", Dz1WebSocketCloseReason_protocol_error },
	{ (char *)"unknown_context", Dz1WebSocketCloseReason_unknown_context },
	{ NULL, Dz1WebSocketCloseReason_max }
};

str_t Dz1WebSocketCloseReasonStrA(Dz1WebSocketCloseReason v)
{
	struct Dz1WebSocketCloseReasonMapA *i = NULL;
	for (i = Dz1WebSocketCloseReasonMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSocketCloseReason Dz1WebSocketCloseReasonFromStrA(str_t str)
{
	struct Dz1WebSocketCloseReasonMapA *i = NULL;
	for (i = Dz1WebSocketCloseReasonMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSocketCloseReason_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1WebSocketCloseReasonMapW
{
	wstr_t str;
	Dz1WebSocketCloseReason v;
} Dz1WebSocketCloseReasonMapW[] =
{
	{ (wchar_t *)L"normal_close", Dz1WebSocketCloseReason_normal_close },
	{ (wchar_t *)L"process_shutdown", Dz1WebSocketCloseReason_process_shutdown },
	{ (wchar_t *)L"protocol_error", Dz1WebSocketCloseReason_protocol_error },
	{ (wchar_t *)L"unknown_context", Dz1WebSocketCloseReason_unknown_context },
	{ NULL, Dz1WebSocketCloseReason_max }
};

wstr_t Dz1WebSocketCloseReasonStrW(Dz1WebSocketCloseReason v)
{
	struct Dz1WebSocketCloseReasonMapW *i = NULL;
	for (i = Dz1WebSocketCloseReasonMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WebSocketCloseReason Dz1WebSocketCloseReasonFromStrW(wstr_t str)
{
	struct Dz1WebSocketCloseReasonMapW *i = NULL;
	for (i = Dz1WebSocketCloseReasonMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1WebSocketCloseReason_max;
}
#endif // UNIX_SYSTEM

Dz1WebSocketCloseReason *Dz1WebSocketCloseReason_new(Dz1WebSocketCloseReason *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1WebSocketCloseReason *__internal_ret = (Dz1WebSocketCloseReason *)Dz1Calloc(sizeof(Dz1WebSocketCloseReason), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1WebSocketCloseReasonA_dump(Dz1WebSocketCloseReason *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1WebSocketCloseReasonStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1WebSocketCloseReasonW_dump(Dz1WebSocketCloseReason *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1WebSocketCloseReasonStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1WebSocketCloseReason
////////////////////////////////////////////////////////////////////////////////

