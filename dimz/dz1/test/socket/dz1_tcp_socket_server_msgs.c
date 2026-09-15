#include <dz1_str.h>
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "dz1_tcp_socket_server_msgs.h"

Dz1TcpSocketServerConnected *Dz1TcpSocketServerConnected_new(
			Dz1SockAddr *peer,
			Dz1SockAddr *local,
			Dz1TcpClientSocket *sock, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSocketServerConnected *__internal_ret = (Dz1TcpSocketServerConnected *)Dz1Calloc(sizeof(Dz1TcpSocketServerConnected), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerConnected_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSocketServerConnected_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSocketServerConnected_del(Dz1TcpSocketServerConnected *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->sock) Dz1TcpClientSocket_del(p->sock);
	Dz1Free(p);
}

void Dz1TcpSocketServerConnected_dump(Dz1TcpSocketServerConnected *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); }

	if (p->sock == NULL) Dz1Thread_tprintf(tab, "sock = NULL\n");
	else { Dz1Thread_tprintf(tab, "sock = %p\n", p->sock); }

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpSocketServerReceived *Dz1TcpSocketServerReceived_new(
			Dz1SockAddr *peer,
			Dz1SockAddr *local,
			Dz1Binary *pkt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSocketServerReceived *__internal_ret = (Dz1TcpSocketServerReceived *)Dz1Calloc(sizeof(Dz1TcpSocketServerReceived), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerReceived_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->pkt = pkt;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSocketServerReceived_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSocketServerReceived_del(Dz1TcpSocketServerReceived *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->pkt) Dz1Binary_del(p->pkt);
	Dz1Free(p);
}

void Dz1TcpSocketServerReceived_dump(Dz1TcpSocketServerReceived *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); }

	if (p->pkt == NULL) Dz1Thread_tprintf(tab, "pkt = NULL\n");
	else { Dz1Thread_tprintf(tab, "pkt = "); Dz1Binary_dump(p->pkt, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpSocketServerOpen *Dz1TcpSocketServerOpen_new(u16_t port, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSocketServerOpen *__internal_ret = (Dz1TcpSocketServerOpen *)Dz1Calloc(sizeof(Dz1TcpSocketServerOpen), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerOpen_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->port = port;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSocketServerOpen_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSocketServerOpen_del(Dz1TcpSocketServerOpen *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSocketServerOpen_dump(Dz1TcpSocketServerOpen *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("port = "); Dz1u16_dump(&p->port, tab);
}

