////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineEnv.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineEnv
ScenarioEngineEnv *ScenarioEngineEnv_new(void *tSelf, 
										 void *tScenario, 
										 Dz1JsonSpec *spec, 
										 Dz1WebSocket *wsock, 
										 u32_t seq, 
										 u32_t test_done_seq, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineEnv *__internal_ret = (ScenarioEngineEnv *)Dz1Calloc(sizeof(ScenarioEngineEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineEnv_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->ws_msgs = Dz1WebSockMsgList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tSelf = tSelf;
			__internal_ret->tScenario = tScenario;
			__internal_ret->spec = spec;
			__internal_ret->wsock = wsock;
			__internal_ret->seq = seq;
			__internal_ret->test_done_seq = test_done_seq;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ScenarioEngineEnv_purge(ScenarioEngineEnv *p)
{
	if (p == NULL) return;
	Dz1JsonSpec_del(p->spec);
	Dz1WebSocket_del(p->wsock);
	Dz1WebSockMsgList_del(p->ws_msgs);
}

void ScenarioEngineEnv_del(ScenarioEngineEnv *p)
{
	if (p == NULL) return;
	ScenarioEngineEnv_purge(p);
	Dz1Free(p);
}

void ScenarioEngineEnv_dump(ScenarioEngineEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		Dz1Thread_tprintf(tab, Dz1T("tScenario = %p\n"), p->tScenario);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("spec = ")); Dz1JsonSpec_dump(p->spec, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("wsock = ")); Dz1WebSocket_dump(p->wsock, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ws_msgs = ")); Dz1WebSockMsgList_dump(p->ws_msgs, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_done_seq = ")); Dz1u32_dump(&p->test_done_seq, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineEnv
////////////////////////////////////////////////////////////////////////////////

