////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_receiver_arg.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpReceiverArg
Dz1InetFtpReceiverArg *Dz1InetFtpReceiverArg_new(void *tControl, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpReceiverArg *__internal_ret = (Dz1InetFtpReceiverArg *)Dz1Calloc(sizeof(Dz1InetFtpReceiverArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpReceiverArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tControl = tControl;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpReceiverArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpReceiverArg_purge(Dz1InetFtpReceiverArg *p)
{
	if (p == NULL) return;
}

void Dz1InetFtpReceiverArg_del(Dz1InetFtpReceiverArg *p)
{
	if (p == NULL) return;
	Dz1InetFtpReceiverArg_purge(p);
	Dz1Free(p);
}

// Dz1InetFtpReceiverArg
////////////////////////////////////////////////////////////////////////////////

