////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1EmulatorTimer.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1EmulatorTimer
Itsk00126V1EmulatorTimer *Itsk00126V1EmulatorTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126V1EmulatorTimer *__internal_ret = (Itsk00126V1EmulatorTimer *)Dz1Calloc(sizeof(Itsk00126V1EmulatorTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126V1EmulatorTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126V1EmulatorTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126V1EmulatorTimer_purge(Itsk00126V1EmulatorTimer *p)
{
	if (p == NULL) return;
}

void Itsk00126V1EmulatorTimer_del(Itsk00126V1EmulatorTimer *p)
{
	if (p == NULL) return;
	Itsk00126V1EmulatorTimer_purge(p);
	Dz1Free(p);
}

void Itsk00126V1EmulatorTimer_dump(Itsk00126V1EmulatorTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
	}
}
int Itsk00126V1EmulatorTimer_cmp(Itsk00126V1EmulatorTimer *a, Itsk00126V1EmulatorTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// Itsk00126V1EmulatorTimer
////////////////////////////////////////////////////////////////////////////////

