////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1TestScenarioTimer.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1TestScenarioTimer
Itsk00126V1TestScenarioTimer *Itsk00126V1TestScenarioTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126V1TestScenarioTimer *__internal_ret = (Itsk00126V1TestScenarioTimer *)Dz1Calloc(sizeof(Itsk00126V1TestScenarioTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126V1TestScenarioTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126V1TestScenarioTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126V1TestScenarioTimer_purge(Itsk00126V1TestScenarioTimer *p)
{
	if (p == NULL) return;
}

void Itsk00126V1TestScenarioTimer_del(Itsk00126V1TestScenarioTimer *p)
{
	if (p == NULL) return;
	Itsk00126V1TestScenarioTimer_purge(p);
	Dz1Free(p);
}

void Itsk00126V1TestScenarioTimer_dump(Itsk00126V1TestScenarioTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
	}
}
int Itsk00126V1TestScenarioTimer_cmp(Itsk00126V1TestScenarioTimer *a, Itsk00126V1TestScenarioTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// Itsk00126V1TestScenarioTimer
////////////////////////////////////////////////////////////////////////////////

