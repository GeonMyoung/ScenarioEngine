////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineArg.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineArg
ScenarioEngineArg *ScenarioEngineArg_new(Dz1Asn1UTF8Str *ws_server, 
										 ScenarioEngineException exceptionProc, 
										 void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineArg *__internal_ret = (ScenarioEngineArg *)Dz1Calloc(sizeof(ScenarioEngineArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->ws_server = ws_server;
		__internal_ret->exceptionProc = exceptionProc;
		__internal_ret->exceptionArg = exceptionArg;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ScenarioEngineArg_purge(ScenarioEngineArg *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->ws_server);
}

void ScenarioEngineArg_del(ScenarioEngineArg *p)
{
	if (p == NULL) return;
	ScenarioEngineArg_purge(p);
	Dz1Free(p);
}

// ScenarioEngineArg
////////////////////////////////////////////////////////////////////////////////

