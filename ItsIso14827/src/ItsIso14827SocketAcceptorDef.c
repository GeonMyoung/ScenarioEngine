////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827SocketAcceptorDef.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIsoAcceptor
ItsIsoAcceptor *ItsIsoAcceptor_new(u32_t dstQueueID, 
								   Dz1Asn1Codec initialCodec, 
								   ItsIso14827CRCCheck CRCCheck, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIsoAcceptor *__internal_ret = (ItsIsoAcceptor *)Dz1Calloc(sizeof(ItsIsoAcceptor), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIsoAcceptor_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dstQueueID = dstQueueID;
		__internal_ret->initialCodec = initialCodec;
		__internal_ret->CRCCheck = CRCCheck;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIsoAcceptor_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIsoAcceptor_purge(ItsIsoAcceptor *p)
{
	if (p == NULL) return;
}

void ItsIsoAcceptor_del(ItsIsoAcceptor *p)
{
	if (p == NULL) return;
	ItsIsoAcceptor_purge(p);
	Dz1Free(p);
}

// ItsIsoAcceptor
////////////////////////////////////////////////////////////////////////////////

