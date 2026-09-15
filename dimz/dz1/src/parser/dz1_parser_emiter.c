#include <dz1_malloc.h>
#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include "dz1_parser_emiter.h"

Dz1ParserEmitEntry *Dz1ParserEmitEntry_new(str_t name, Dz1ParserEmitFunc func, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ParserEmitEntry *ret = (Dz1ParserEmitEntry *)Dz1Malloc(sizeof(Dz1ParserEmitEntry), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ParserEmitEntry));
		pthread_cleanup_push(Dz1ParserEmitEntry_delAndSetNull, (void *)&ret);

		if ((ret->name = Dz1StrA_dup(name, errp)))
		{
			ret->func = func;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1ParserEmitEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ParserEmitEntry_del(Dz1ParserEmitEntry *p)
{
	if (!p) return;
	if (p->name) Dz1StrA_del(p->name);
	Dz1Free(p);
}

void Dz1ParserEmitEntry_dump(Dz1ParserEmitEntry *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "[%s][%p]\n", p->name, p->func);
}

