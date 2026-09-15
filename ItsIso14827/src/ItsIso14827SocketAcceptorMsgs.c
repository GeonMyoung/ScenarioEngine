////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827SocketAcceptorMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIsoAcceptorConnected
ItsIsoAcceptorConnected *ItsIsoAcceptorConnected_new(Dz1SockAddr *peer, 
													 Dz1SockAddr *local, 
													 Dz1TcpClientSocket *sock, 
													 Dz1Asn1Codec initialCodec, 
													 ItsIso14827CRCCheck CRCCheck, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIsoAcceptorConnected *__internal_ret = (ItsIsoAcceptorConnected *)Dz1Calloc(sizeof(ItsIsoAcceptorConnected), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIsoAcceptorConnected_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->initialCodec = initialCodec;
		__internal_ret->CRCCheck = CRCCheck;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIsoAcceptorConnected_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIsoAcceptorConnected_purge(ItsIsoAcceptorConnected *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
}

void ItsIsoAcceptorConnected_del(ItsIsoAcceptorConnected *p)
{
	if (p == NULL) return;
	ItsIsoAcceptorConnected_purge(p);
	Dz1Free(p);
}

void ItsIsoAcceptorConnected_dump(ItsIsoAcceptorConnected *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("sock = %p\n"), p->sock);
		Dz1Thread_tprintf(tab, Dz1T("initialCodec = %s(%d)\n"), Dz1Asn1CodecStr(p->initialCodec), p->initialCodec);
		Dz1Thread_tprintf(tab, Dz1T("CRCCheck = %s(%d)\n"), ItsIso14827CRCCheckStr(p->CRCCheck), p->CRCCheck);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIsoAcceptorConnected
////////////////////////////////////////////////////////////////////////////////

