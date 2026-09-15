////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2TestScenarioTimer.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442TestScenarioTimer
ITSK001442TestScenarioTimer *ITSK001442TestScenarioTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK001442TestScenarioTimer *__internal_ret = (ITSK001442TestScenarioTimer *)Dz1Calloc(sizeof(ITSK001442TestScenarioTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK001442TestScenarioTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK001442TestScenarioTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK001442TestScenarioTimer_purge(ITSK001442TestScenarioTimer *p)
{
	if (p == NULL) return;
}

void ITSK001442TestScenarioTimer_del(ITSK001442TestScenarioTimer *p)
{
	if (p == NULL) return;
	ITSK001442TestScenarioTimer_purge(p);
	Dz1Free(p);
}

void ITSK001442TestScenarioTimer_dump(ITSK001442TestScenarioTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
	}
}
int ITSK001442TestScenarioTimer_cmp(ITSK001442TestScenarioTimer *a, ITSK001442TestScenarioTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// ITSK001442TestScenarioTimer
////////////////////////////////////////////////////////////////////////////////

