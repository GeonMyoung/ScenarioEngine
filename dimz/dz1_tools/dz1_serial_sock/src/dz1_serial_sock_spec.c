////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_serial_sock_spec.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1SerialSocketSpecific
Dz1SerialSocketSpecific *Dz1SerialSocketSpecific_new(Dz1Sync *sync, 
													 Dz1SocketBuf *buf, 
													 bool_t eof, 
													 void *io, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SerialSocketSpecific *__internal_ret = (Dz1SerialSocketSpecific *)Dz1Calloc(sizeof(Dz1SerialSocketSpecific), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SerialSocketSpecific_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->sync = sync;
		__internal_ret->buf = buf;
		__internal_ret->eof = eof;
		__internal_ret->io = io;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SerialSocketSpecific_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SerialSocketSpecific_purge(Dz1SerialSocketSpecific *p)
{
	if (p == NULL) return;
	Dz1Sync_del(p->sync);
	Dz1SocketBuf_del(p->buf);
}

void Dz1SerialSocketSpecific_del(Dz1SerialSocketSpecific *p)
{
	if (p == NULL) return;
	Dz1SerialSocketSpecific_purge(p);
	Dz1Free(p);
}

// Dz1SerialSocketSpecific
////////////////////////////////////////////////////////////////////////////////

