////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2EmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorDef
ITSK001442EmulatorDef *ITSK001442EmulatorDef_new(s32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK001442EmulatorDef *__internal_ret = (ITSK001442EmulatorDef *)Dz1Calloc(sizeof(ITSK001442EmulatorDef), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK001442EmulatorDef_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK001442EmulatorDef_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK001442EmulatorDef_purge(ITSK001442EmulatorDef *p)
{
	if (p == NULL) return;
}

void ITSK001442EmulatorDef_del(ITSK001442EmulatorDef *p)
{
	if (p == NULL) return;
	ITSK001442EmulatorDef_purge(p);
	Dz1Free(p);
}

// ITSK001442EmulatorDef
////////////////////////////////////////////////////////////////////////////////

