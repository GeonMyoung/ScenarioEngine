#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpCallbackServerDef.h"

static struct Dz1TcpCallbackServerDefMapA
{
	str_t str;
	Dz1TcpCallbackServerDef v;
} Dz1TcpCallbackServerDefMapA[] =
{
	{ "pseudo", Dz1TcpCallbackServerDef_pseudo },
	{ NULL, Dz1TcpCallbackServerDef_max }
};

str_t Dz1TcpCallbackServerDefStrA(Dz1TcpCallbackServerDef v)
{
	struct Dz1TcpCallbackServerDefMapA *i = NULL;
	for (i = Dz1TcpCallbackServerDefMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpCallbackServerDef Dz1TcpCallbackServerDefFromStrA(str_t str)
{
	struct Dz1TcpCallbackServerDefMapA *i = NULL;
	for (i = Dz1TcpCallbackServerDefMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1TcpCallbackServerDef_max;
}

static struct Dz1TcpCallbackServerDefMapW
{
	wstr_t str;
	Dz1TcpCallbackServerDef v;
} Dz1TcpCallbackServerDefMapW[] =
{
	{ L"pseudo", Dz1TcpCallbackServerDef_pseudo },
	{ NULL, Dz1TcpCallbackServerDef_max }
};

wstr_t Dz1TcpCallbackServerDefStrW(Dz1TcpCallbackServerDef v)
{
	struct Dz1TcpCallbackServerDefMapW *i = NULL;
	for (i = Dz1TcpCallbackServerDefMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpCallbackServerDef Dz1TcpCallbackServerDefFromStrW(wstr_t str)
{
	struct Dz1TcpCallbackServerDefMapW *i = NULL;
	for (i = Dz1TcpCallbackServerDefMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1TcpCallbackServerDef_max;
}

Dz1TcpCallbackServerDef *Dz1TcpCallbackServerDef_new(Dz1TcpCallbackServerDef *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackServerDef *__internal_ret = (Dz1TcpCallbackServerDef *)Dz1Calloc(sizeof(Dz1TcpCallbackServerDef), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1TcpCallbackServerDef_dump(Dz1TcpCallbackServerDef *v, int tab)
{
	if (v == NULL) Dz1Thread_printf("NULL\n");
	else Dz1Thread_printf("%s\n", Dz1TcpCallbackServerDefStrA(*v));
}

