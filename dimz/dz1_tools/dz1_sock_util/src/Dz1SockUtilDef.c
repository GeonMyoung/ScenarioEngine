////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1SockUtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilReceiverArg
Dz1SockUtilReceiverArg *Dz1SockUtilReceiverArg_new(u32_t parentQueueID, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilReceiverArg *__internal_ret = (Dz1SockUtilReceiverArg *)Dz1Calloc(sizeof(Dz1SockUtilReceiverArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiverArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->parentQueueID = parentQueueID;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilReceiverArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilReceiverArg_purge(Dz1SockUtilReceiverArg *p)
{
	if (p == NULL) return;
}

void Dz1SockUtilReceiverArg_del(Dz1SockUtilReceiverArg *p)
{
	if (p == NULL) return;
	Dz1SockUtilReceiverArg_purge(p);
	Dz1Free(p);
}

// Dz1SockUtilReceiverArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilReceiver2Arg
Dz1SockUtilReceiver2Arg *Dz1SockUtilReceiver2Arg_new(u32_t parentQueueID, 
													 u32_t sessionID, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilReceiver2Arg *__internal_ret = (Dz1SockUtilReceiver2Arg *)Dz1Calloc(sizeof(Dz1SockUtilReceiver2Arg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiver2Arg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->parentQueueID = parentQueueID;
		__internal_ret->sessionID = sessionID;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilReceiver2Arg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilReceiver2Arg_purge(Dz1SockUtilReceiver2Arg *p)
{
	if (p == NULL) return;
}

void Dz1SockUtilReceiver2Arg_del(Dz1SockUtilReceiver2Arg *p)
{
	if (p == NULL) return;
	Dz1SockUtilReceiver2Arg_purge(p);
	Dz1Free(p);
}

// Dz1SockUtilReceiver2Arg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilAcceptorConnected
Dz1SockUtilAcceptorConnected *Dz1SockUtilAcceptorConnected_new(Dz1SockAddr *peer, 
															   Dz1SockAddr *local, 
															   u32_t acceptorID, 
															   Dz1TcpClientSocket *sock, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilAcceptorConnected *__internal_ret = (Dz1SockUtilAcceptorConnected *)Dz1Calloc(sizeof(Dz1SockUtilAcceptorConnected), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilAcceptorConnected_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->acceptorID = acceptorID;
		__internal_ret->sock = sock;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilAcceptorConnected_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilAcceptorConnected_purge(Dz1SockUtilAcceptorConnected *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
}

void Dz1SockUtilAcceptorConnected_del(Dz1SockUtilAcceptorConnected *p)
{
	if (p == NULL) return;
	Dz1SockUtilAcceptorConnected_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilAcceptorConnectedA_dump(Dz1SockUtilAcceptorConnected *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "peer = "); Dz1SockAddrA_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "local = "); Dz1SockAddrA_dump(p->local, tab); 
		Dz1ThreadA_tprintf(tab, "acceptorID = "); Dz1u32A_dump(&p->acceptorID, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "sock = %p\n", p->sock);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilAcceptorConnectedW_dump(Dz1SockUtilAcceptorConnected *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"peer = "); Dz1SockAddrW_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"local = "); Dz1SockAddrW_dump(p->local, tab); 
		Dz1ThreadW_tprintf(tab, L"acceptorID = "); Dz1u32W_dump(&p->acceptorID, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"sock = %p\n", p->sock);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilAcceptorConnected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilAcceptorException
Dz1SockUtilAcceptorException *Dz1SockUtilAcceptorException_new(u32_t acceptorID, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilAcceptorException *__internal_ret = (Dz1SockUtilAcceptorException *)Dz1Calloc(sizeof(Dz1SockUtilAcceptorException), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilAcceptorException_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->acceptorID = acceptorID;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilAcceptorException_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilAcceptorException_purge(Dz1SockUtilAcceptorException *p)
{
	if (p == NULL) return;
}

void Dz1SockUtilAcceptorException_del(Dz1SockUtilAcceptorException *p)
{
	if (p == NULL) return;
	Dz1SockUtilAcceptorException_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilAcceptorExceptionA_dump(Dz1SockUtilAcceptorException *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("acceptorID = "); Dz1u32A_dump(&p->acceptorID, tab); 
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilAcceptorExceptionW_dump(Dz1SockUtilAcceptorException *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"acceptorID = "); Dz1u32W_dump(&p->acceptorID, tab); 
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilAcceptorException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilReceiverReceived
Dz1SockUtilReceiverReceived *Dz1SockUtilReceiverReceived_new(Dz1SockAddr *peer, 
															 Dz1SockAddr *local, 
															 Dz1Binary *stream, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilReceiverReceived *__internal_ret = (Dz1SockUtilReceiverReceived *)Dz1Calloc(sizeof(Dz1SockUtilReceiverReceived), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiverReceived_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->stream = stream;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilReceiverReceived_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilReceiverReceived_purge(Dz1SockUtilReceiverReceived *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1Binary_del(p->stream);
}

void Dz1SockUtilReceiverReceived_del(Dz1SockUtilReceiverReceived *p)
{
	if (p == NULL) return;
	Dz1SockUtilReceiverReceived_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilReceiverReceivedA_dump(Dz1SockUtilReceiverReceived *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "peer = "); Dz1SockAddrA_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "local = "); Dz1SockAddrA_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "stream = "); Dz1BinaryA_dump(p->stream, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilReceiverReceivedW_dump(Dz1SockUtilReceiverReceived *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"peer = "); Dz1SockAddrW_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"local = "); Dz1SockAddrW_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"stream = "); Dz1BinaryW_dump(p->stream, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilReceiverReceived
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTransmiterSent
Dz1SockUtilTransmiterSent *Dz1SockUtilTransmiterSent_new(Dz1SockAddr *peer, 
														 Dz1SockAddr *local, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilTransmiterSent *__internal_ret = (Dz1SockUtilTransmiterSent *)Dz1Calloc(sizeof(Dz1SockUtilTransmiterSent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilTransmiterSent_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilTransmiterSent_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilTransmiterSent_purge(Dz1SockUtilTransmiterSent *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
}

void Dz1SockUtilTransmiterSent_del(Dz1SockUtilTransmiterSent *p)
{
	if (p == NULL) return;
	Dz1SockUtilTransmiterSent_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilTransmiterSentA_dump(Dz1SockUtilTransmiterSent *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "peer = "); Dz1SockAddrA_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "local = "); Dz1SockAddrA_dump(p->local, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilTransmiterSentW_dump(Dz1SockUtilTransmiterSent *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"peer = "); Dz1SockAddrW_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"local = "); Dz1SockAddrW_dump(p->local, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilTransmiterSent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilReceiver2Received
Dz1SockUtilReceiver2Received *Dz1SockUtilReceiver2Received_new(u32_t sessionID, 
															   Dz1Binary *stream, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilReceiver2Received *__internal_ret = (Dz1SockUtilReceiver2Received *)Dz1Calloc(sizeof(Dz1SockUtilReceiver2Received), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiver2Received_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->sessionID = sessionID;
		__internal_ret->stream = stream;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilReceiver2Received_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilReceiver2Received_purge(Dz1SockUtilReceiver2Received *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->stream);
}

void Dz1SockUtilReceiver2Received_del(Dz1SockUtilReceiver2Received *p)
{
	if (p == NULL) return;
	Dz1SockUtilReceiver2Received_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilReceiver2ReceivedA_dump(Dz1SockUtilReceiver2Received *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "sessionID = "); Dz1u32A_dump(&p->sessionID, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "stream = "); Dz1BinaryA_dump(p->stream, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilReceiver2ReceivedW_dump(Dz1SockUtilReceiver2Received *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"sessionID = "); Dz1u32W_dump(&p->sessionID, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"stream = "); Dz1BinaryW_dump(p->stream, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilReceiver2Received
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTransmiter2Sent
Dz1SockUtilTransmiter2Sent *Dz1SockUtilTransmiter2Sent_new(u32_t sessionID, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilTransmiter2Sent *__internal_ret = (Dz1SockUtilTransmiter2Sent *)Dz1Calloc(sizeof(Dz1SockUtilTransmiter2Sent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilTransmiter2Sent_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->sessionID = sessionID;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilTransmiter2Sent_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilTransmiter2Sent_purge(Dz1SockUtilTransmiter2Sent *p)
{
	if (p == NULL) return;
}

void Dz1SockUtilTransmiter2Sent_del(Dz1SockUtilTransmiter2Sent *p)
{
	if (p == NULL) return;
	Dz1SockUtilTransmiter2Sent_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilTransmiter2SentA_dump(Dz1SockUtilTransmiter2Sent *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("sessionID = "); Dz1u32A_dump(&p->sessionID, tab); 
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilTransmiter2SentW_dump(Dz1SockUtilTransmiter2Sent *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"sessionID = "); Dz1u32W_dump(&p->sessionID, tab); 
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilTransmiter2Sent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectEntry
Dz1SockUtilBulkConnectEntry *Dz1SockUtilBulkConnectEntry_new(Dz1SockAddr *addr, 
															 u32_t thid, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilBulkConnectEntry *__internal_ret = (Dz1SockUtilBulkConnectEntry *)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->addr = addr;
		__internal_ret->thid = thid;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilBulkConnectEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilBulkConnectEntry_purge(Dz1SockUtilBulkConnectEntry *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->addr);
}

void Dz1SockUtilBulkConnectEntry_del(Dz1SockUtilBulkConnectEntry *p)
{
	if (p == NULL) return;
	Dz1SockUtilBulkConnectEntry_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilBulkConnectEntryA_dump(Dz1SockUtilBulkConnectEntry *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "addr = "); Dz1SockAddrA_dump(p->addr, tab); 
		Dz1ThreadA_tprintf(tab, "thid = "); Dz1u32A_dump(&p->thid, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilBulkConnectEntryW_dump(Dz1SockUtilBulkConnectEntry *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"addr = "); Dz1SockAddrW_dump(p->addr, tab); 
		Dz1ThreadW_tprintf(tab, L"thid = "); Dz1u32W_dump(&p->thid, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectResult
Dz1SockUtilBulkConnectResult *Dz1SockUtilBulkConnectResult_new(Dz1SockAddr *peer, 
															   Dz1SockAddr *local, 
															   Dz1TcpClientSocket *sock, 
															   void *userData, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilBulkConnectResult *__internal_ret = (Dz1SockUtilBulkConnectResult *)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectResult), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectResult_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->userData = userData;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilBulkConnectResult_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SockUtilBulkConnectResult_purge(Dz1SockUtilBulkConnectResult *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
}

void Dz1SockUtilBulkConnectResult_del(Dz1SockUtilBulkConnectResult *p)
{
	if (p == NULL) return;
	Dz1SockUtilBulkConnectResult_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilBulkConnectResultA_dump(Dz1SockUtilBulkConnectResult *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "peer = "); Dz1SockAddrA_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "local = "); Dz1SockAddrA_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "sock = %p\n", p->sock);
		Dz1ThreadA_tprintf(tab, "userData = %p\n", p->userData);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilBulkConnectResultW_dump(Dz1SockUtilBulkConnectResult *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"peer = "); Dz1SockAddrW_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"local = "); Dz1SockAddrW_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"sock = %p\n", p->sock);
		Dz1ThreadW_tprintf(tab, L"userData = %p\n", p->userData);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilBulkConnectResult
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilRxBuf
void Dz1SockUtilRxBuf_purge(Dz1SockUtilRxBuf *p)
{
	if (p == NULL) return;
	Dz1Stream_del(p->st);
	Dz1ElasticBuf_del(p->elb);
}

void Dz1SockUtilRxBuf_del(Dz1SockUtilRxBuf *p)
{
	if (p == NULL) return;
	Dz1SockUtilRxBuf_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilRxBufA_dump(Dz1SockUtilRxBuf *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "elastic_size = "); Dz1u32A_dump(&p->elastic_size, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "st = %p\n", p->st);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "elb = %p\n", p->elb);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilRxBufW_dump(Dz1SockUtilRxBuf *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"elastic_size = "); Dz1u32W_dump(&p->elastic_size, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"st = %p\n", p->st);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"elb = %p\n", p->elb);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilRxBuf
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTxEntry
Dz1SockUtilTxEntry *Dz1SockUtilTxEntry_new(Dz1SockUtilTxEntry *next/*_ref*/, 
										   Dz1Binary *chunk, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilTxEntry *__internal_ret = (Dz1SockUtilTxEntry *)Dz1Calloc(sizeof(Dz1SockUtilTxEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilTxEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->next = next;
		__internal_ret->chunk = chunk;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilTxEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1SockUtilTxEntry_copy(Dz1SockUtilTxEntry *dst, Dz1SockUtilTxEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->chunk && (dst->chunk = Dz1Binary_clone(src->chunk, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->next = src->next;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1SockUtilTxEntry *Dz1SockUtilTxEntry_clone(Dz1SockUtilTxEntry *src, Dz1Error *err)
{
	Dz1SockUtilTxEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1SockUtilTxEntry *)Dz1Calloc(sizeof(Dz1SockUtilTxEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilTxEntry_delAndSetNull, (void *)&dst);
		if (Dz1SockUtilTxEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilTxEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1SockUtilTxEntry_purge(Dz1SockUtilTxEntry *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->chunk);
}

void Dz1SockUtilTxEntry_del(Dz1SockUtilTxEntry *p)
{
	if (p == NULL) return;
	Dz1SockUtilTxEntry_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilTxEntryA_dump(Dz1SockUtilTxEntry *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_printf("chunk = "); Dz1BinaryA_dump(p->chunk, tab); 
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilTxEntryW_dump(Dz1SockUtilTxEntry *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_printf(L"chunk = "); Dz1BinaryW_dump(p->chunk, tab); 
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilTxEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTxFifo
Dz1SockUtilTxFifo *Dz1SockUtilTxFifo_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilTxFifo *__internal_ret = (Dz1SockUtilTxFifo *)Dz1Calloc(sizeof(Dz1SockUtilTxFifo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilTxFifo_delAndSetNull, (void *)&__internal_ret);
		
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilTxFifo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1SockUtilTxFifo_copy(Dz1SockUtilTxFifo *dst, Dz1SockUtilTxFifo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->head && (dst->head = Dz1SockUtilTxEntry_clone(src->head, errp)) == NULL) ERR_OUT(errp);
	else if (src->tail && (dst->tail = Dz1SockUtilTxEntry_clone(src->tail, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1SockUtilTxFifo *Dz1SockUtilTxFifo_clone(Dz1SockUtilTxFifo *src, Dz1Error *err)
{
	Dz1SockUtilTxFifo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1SockUtilTxFifo *)Dz1Calloc(sizeof(Dz1SockUtilTxFifo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilTxFifo_delAndSetNull, (void *)&dst);
		if (Dz1SockUtilTxFifo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilTxFifo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1SockUtilTxFifoA_dump(Dz1SockUtilTxFifo *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		// Normal member
		Dz1ThreadA_printf("head = "); Dz1SockUtilTxEntryA_dump(p->head, tab); 
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilTxFifoW_dump(Dz1SockUtilTxFifo *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		// Normal member
		Dz1ThreadW_printf(L"head = "); Dz1SockUtilTxEntryW_dump(p->head, tab); 
	}
}
#endif // UNIX_SYSTEM
// Dz1SockUtilTxFifo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CallbackSockIO
void Dz1CallbackSockIO_purge(Dz1CallbackSockIO *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void Dz1CallbackSockIO_del(Dz1CallbackSockIO *p)
{
	if (p == NULL) return;
	Dz1CallbackSockIO_purge(p);
	Dz1Free(p);
}

void Dz1CallbackSockIOA_dump(Dz1CallbackSockIO *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "peer = "); Dz1SockAddrA_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "local = "); Dz1SockAddrA_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "rx_buf = %p\n", p->rx_buf);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "rx_stream = %p\n", p->rx_stream);
		// Normal member
		Dz1ThreadA_tprintf(tab, "tx_fifo = "); Dz1SockUtilTxFifoA_dump(p->tx_fifo, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1CallbackSockIOW_dump(Dz1CallbackSockIO *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"peer = "); Dz1SockAddrW_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"local = "); Dz1SockAddrW_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"rx_buf = %p\n", p->rx_buf);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"rx_stream = %p\n", p->rx_stream);
		// Normal member
		Dz1ThreadW_tprintf(tab, L"tx_fifo = "); Dz1SockUtilTxFifoW_dump(p->tx_fifo, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
int Dz1CallbackSockIO_cmp(Dz1CallbackSockIO *a, Dz1CallbackSockIO *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->peer == NULL && b->peer == NULL) ret = 0;
	else if (a->peer == NULL /*&& b->peer != NULL*/) ret = -1;
	else if (/*a->peer != NULL &&*/ b->peer == NULL) ret = 1;
	else if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) { }
	else if (a->local == NULL && b->local == NULL) ret = 0;
	else if (a->local == NULL /*&& b->local != NULL*/) ret = -1;
	else if (/*a->local != NULL &&*/ b->local == NULL) ret = 1;
	else if ((ret = Dz1SockAddr_cmp(a->local, b->local)) != 0) { }
	return ret;
}
// Dz1CallbackSockIO
////////////////////////////////////////////////////////////////////////////////

