////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineTimer.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineTimer
ScenarioEngineTimer *ScenarioEngineTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineTimer *__internal_ret = (ScenarioEngineTimer *)Dz1Calloc(sizeof(ScenarioEngineTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ScenarioEngineTimer_purge(ScenarioEngineTimer *p)
{
	if (p == NULL) return;
}

void ScenarioEngineTimer_del(ScenarioEngineTimer *p)
{
	if (p == NULL) return;
	ScenarioEngineTimer_purge(p);
	Dz1Free(p);
}

void ScenarioEngineTimer_dump(ScenarioEngineTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
	}
}
int ScenarioEngineTimer_cmp(ScenarioEngineTimer *a, ScenarioEngineTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// ScenarioEngineTimer
////////////////////////////////////////////////////////////////////////////////

