////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00100_3UtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001003Util
ITSK001003Util *ITSK001003Util_new(s32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK001003Util *__internal_ret = (ITSK001003Util *)Dz1Calloc(sizeof(ITSK001003Util), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK001003Util_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK001003Util_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK001003Util_purge(ITSK001003Util *p)
{
	if (p == NULL) return;
}

void ITSK001003Util_del(ITSK001003Util *p)
{
	if (p == NULL) return;
	ITSK001003Util_purge(p);
	Dz1Free(p);
}

// ITSK001003Util
////////////////////////////////////////////////////////////////////////////////

