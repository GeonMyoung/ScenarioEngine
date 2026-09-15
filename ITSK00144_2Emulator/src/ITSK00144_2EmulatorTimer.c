////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2EmulatorTimer.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorTimer
ITSK001442EmulatorTimer *ITSK001442EmulatorTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK001442EmulatorTimer *__internal_ret = (ITSK001442EmulatorTimer *)Dz1Calloc(sizeof(ITSK001442EmulatorTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK001442EmulatorTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK001442EmulatorTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK001442EmulatorTimer_purge(ITSK001442EmulatorTimer *p)
{
	if (p == NULL) return;
}

void ITSK001442EmulatorTimer_del(ITSK001442EmulatorTimer *p)
{
	if (p == NULL) return;
	ITSK001442EmulatorTimer_purge(p);
	Dz1Free(p);
}

void ITSK001442EmulatorTimer_dump(ITSK001442EmulatorTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
	}
}
int ITSK001442EmulatorTimer_cmp(ITSK001442EmulatorTimer *a, ITSK001442EmulatorTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// ITSK001442EmulatorTimer
////////////////////////////////////////////////////////////////////////////////

