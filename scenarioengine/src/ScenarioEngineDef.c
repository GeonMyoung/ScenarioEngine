////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineDef.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineDef
ScenarioEngineDef *ScenarioEngineDef_new(s32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineDef *__internal_ret = (ScenarioEngineDef *)Dz1Calloc(sizeof(ScenarioEngineDef), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineDef_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineDef_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ScenarioEngineDef_purge(ScenarioEngineDef *p)
{
	if (p == NULL) return;
}

void ScenarioEngineDef_del(ScenarioEngineDef *p)
{
	if (p == NULL) return;
	ScenarioEngineDef_purge(p);
	Dz1Free(p);
}

// ScenarioEngineDef
////////////////////////////////////////////////////////////////////////////////

