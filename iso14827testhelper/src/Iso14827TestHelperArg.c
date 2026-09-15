////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827TestHelperArg.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperArg
Iso14827TestHelperArg *Iso14827TestHelperArg_new(void *tMain, 
												 void *t14827, 
												 Dz1Str testScenario, 
												 Iso14827TestMsgStructAPI *msg_api/*_ref*/, 
												 u8_t codec_bits, 
												 u16_t hb_dur_s, 
												 u8_t rsp_time_s, 
												 Dz1Asn1Codec initial_codec, 
												 Iso14827TestHelperException exceptionProc, 
												 void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestHelperArg *__internal_ret = (Iso14827TestHelperArg *)Dz1Calloc(sizeof(Iso14827TestHelperArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestHelperArg_delAndSetNull, (void *)&__internal_ret);
		
		if (testScenario && (__internal_ret->testScenario = Dz1Str_clone(testScenario, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tMain = tMain;
			__internal_ret->t14827 = t14827;
			__internal_ret->msg_api = msg_api;
			__internal_ret->codec_bits = codec_bits;
			__internal_ret->hb_dur_s = hb_dur_s;
			__internal_ret->rsp_time_s = rsp_time_s;
			__internal_ret->initial_codec = initial_codec;
			__internal_ret->exceptionProc = exceptionProc;
			__internal_ret->exceptionArg = exceptionArg;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestHelperArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Iso14827TestHelperArg_purge(Iso14827TestHelperArg *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testScenario);
}

void Iso14827TestHelperArg_del(Iso14827TestHelperArg *p)
{
	if (p == NULL) return;
	Iso14827TestHelperArg_purge(p);
	Dz1Free(p);
}

// Iso14827TestHelperArg
////////////////////////////////////////////////////////////////////////////////

