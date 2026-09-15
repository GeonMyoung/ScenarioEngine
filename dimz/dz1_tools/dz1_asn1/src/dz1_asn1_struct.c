////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_asn1_struct.h"

////////////////////////////////////////////////////////////////////////////////
// DummyStruct
DummyStruct *DummyStruct_new(u32_t dumb, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DummyStruct *__internal_ret = (DummyStruct *)Dz1Calloc(sizeof(DummyStruct), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(DummyStruct_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dumb = dumb;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DummyStruct_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void DummyStruct_purge(DummyStruct *p)
{
	if (p == NULL) return;
}

void DummyStruct_del(DummyStruct *p)
{
	if (p == NULL) return;
	DummyStruct_purge(p);
	Dz1Free(p);
}

// DummyStruct
////////////////////////////////////////////////////////////////////////////////

