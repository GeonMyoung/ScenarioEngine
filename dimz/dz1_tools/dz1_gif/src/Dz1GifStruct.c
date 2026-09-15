////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1GifStruct.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1GifParallelArg
Dz1GifParallelArg *Dz1GifParallelArg_new(Dz1GifDecodeOptParallel *opt/*_ref*/, 
										 Dz1GifDescr *descr/*_ref*/, 
										 Dz1GifGraphic *graphic/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifParallelArg *__internal_ret = (Dz1GifParallelArg *)Dz1Calloc(sizeof(Dz1GifParallelArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifParallelArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->opt = opt;
		__internal_ret->descr = descr;
		__internal_ret->graphic = graphic;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifParallelArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1GifParallelArg_purge(Dz1GifParallelArg *p)
{
	if (p == NULL) return;
}

void Dz1GifParallelArg_del(Dz1GifParallelArg *p)
{
	if (p == NULL) return;
	Dz1GifParallelArg_purge(p);
	Dz1Free(p);
}

// Dz1GifParallelArg
////////////////////////////////////////////////////////////////////////////////

