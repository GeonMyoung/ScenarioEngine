////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1EmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1EmulatorDef
Itsk00126V1EmulatorDef *Itsk00126V1EmulatorDef_new(s32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126V1EmulatorDef *__internal_ret = (Itsk00126V1EmulatorDef *)Dz1Calloc(sizeof(Itsk00126V1EmulatorDef), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126V1EmulatorDef_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126V1EmulatorDef_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126V1EmulatorDef_purge(Itsk00126V1EmulatorDef *p)
{
	if (p == NULL) return;
}

void Itsk00126V1EmulatorDef_del(Itsk00126V1EmulatorDef *p)
{
	if (p == NULL) return;
	Itsk00126V1EmulatorDef_purge(p);
	Dz1Free(p);
}

// Itsk00126V1EmulatorDef
////////////////////////////////////////////////////////////////////////////////

