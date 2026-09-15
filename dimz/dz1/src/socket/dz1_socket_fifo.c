#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include "../kernel/dz1_thread_stdio.h"
#include "dz1_socket_fifo.h"

///////////////////////////////////////////////////////////////////////////////
// Socket TX FIFO Mode 1 : Binary Handling
Dz1SocketFifo *Dz1SocketFifo_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Fifo *ret = Dz1Fifo_new((Dz1DelFunc)Dz1Binary_del, (Dz1DumpFunc)Dz1Binary_dump, -1, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

void Dz1SocketFifo_del(Dz1SocketFifo *p)
{
	if (p == NULL) return;
	Dz1Fifo_del(p);
}

void Dz1SocketFifoA_dump(Dz1SocketFifo *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1Fifo_dump(p, tab);
}
#ifndef UNIX_SYSTEM
void Dz1SocketFifoW_dump(Dz1SocketFifo *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1Fifo_dump(p, tab);
}
#endif

static Dz1Error _Dz1SocketFifo_push(Dz1SocketFifo *fifo, Dz1Binary **packet)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Binary *src = (*packet);
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Dz1Fifo_push(fifo, src)).code) ERR_OUT(&err);
	else (*packet) = NULL;
	return err;
}

Dz1Error Dz1SocketFifo_push(Dz1SocketFifo *fifo, Dz1Binary **packet)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (fifo == NULL || packet == NULL || *packet == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = _Dz1SocketFifo_push(fifo, packet)).code) ERR_OUT(&err);
	return err;
}

Dz1Error Dz1SocketFifo_copyAndPush(Dz1SocketFifo *fifo, Dz1Binary *packet)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (fifo == NULL || packet == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((packet = Dz1Binary_clone(packet, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&packet);
		if ((err = _Dz1SocketFifo_push(fifo, &packet)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&packet);
	}
	return err;
}

Dz1Error Dz1SocketFifo_copyAndPushData(Dz1SocketFifo *fifo, u8_t *data, size_t size)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Binary *packet = NULL;
	if (fifo == NULL || data == NULL || size == 0) ERR_SET_OUT(&err, EINVAL);
	else if ((packet = Dz1Binary_new(data, (u32_t)size, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&packet);
		if ((err = _Dz1SocketFifo_push(fifo, &packet)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&packet);
	}
	return err;
}

Dz1Binary *Dz1SocketFifo_pop(Dz1SocketFifo *fifo, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Binary *ret = NULL;
	if (fifo == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Binary *)Dz1Fifo_pop(fifo, errp)) == NULL) ERR_OUT(errp);
	return ret;
}

Dz1Binary *Dz1SocketFifo_peek(Dz1SocketFifo *fifo, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Binary *ret = NULL;
	if (fifo == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Binary *)Dz1Fifo_getFirst(fifo)) == NULL) Dz1Error_set(errp, ENOENT);
	return ret;
}

size_t Dz1SocketFifo_count(Dz1SocketFifo *fifo)
{
	return Dz1Fifo_count(fifo);
}
// Socket TX FIFO Mode 1 : Binary Handling
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Socket TX FIFO Type 2 : CODEC Mode(deprecated
static void Dz1SocketFifo2Entry_del(Dz1SocketFifo2Entry *p)
{
	if (p == NULL) return;
	else
	{
		Dz1SocketMsgAPI *api = p->api;
		if (api->del && p->msg) api->del(p->msg);
		p->msg = NULL;
		Dz1Binary_delAndSetNull(&p->stream);
		Dz1Free(p);
	}
}

static void Dz1SocketFifo2Entry_delAndSetNull(void *ptr)
{
	Dz1SocketFifo2Entry **p = (Dz1SocketFifo2Entry **)ptr;
	Dz1SocketFifo2Entry_del(*p); *p = NULL;
}

static Dz1SocketFifo2Entry *Dz1SocketFifo2Entry_new(void *msg, Dz1Binary *stream, Dz1SocketMsgAPI *api, bool_t verbose, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketFifo2Entry *ret = (Dz1SocketFifo2Entry *)Dz1Calloc(sizeof(Dz1SocketFifo2Entry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->msg = msg;
		ret->stream = stream;
		ret->api = api;
		ret->verbose = verbose;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1SocketFifo2Entry_dump(Dz1SocketFifo2Entry *p, int tab)
{
	if (p == NULL) Dz1Thread_eprintf("NULL\n");
	else
	{
		Dz1SocketMsgAPI *api = p->api;
		if (api->dump) api->dump(p->msg, tab);
		else if (p->stream)
		{
			Dz1Binary *bin = p->stream;
			Dz1Thread_eprintf("Stream = {\n"); tab++;
			Dz1Thread_etprintb(tab, bin->data, bin->size, 16, TRUE);
			Dz1Thread_etprintf(--tab, "}\n");
		}
	}
}

Dz1SocketFifo2 *Dz1SocketFifo2_new(Dz1EncodeFunc enc, void *enc_param, Dz1DelFunc del, Dz1DumpFunc dump, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1SocketFifo2 *ret = (_Dz1SocketFifo2 *)Dz1Calloc(sizeof(_Dz1SocketFifo2), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SocketFifo2_delAndSetNull, (void *)&ret);
		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)Dz1SocketFifo2Entry_del,
									 (Dz1DumpFunc)Dz1SocketFifo2Entry_dump,
									 -1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->api.enc = enc;
			ret->api.enc_param = enc_param;

			ret->api.del = del;
			ret->api.dump = dump;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SocketFifo2_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SocketFifo2_del(Dz1SocketFifo2 *ptr)
{
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;
	if (p == NULL) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	p->fifo = NULL;
	Dz1Free(p);
}

void Dz1SocketFifo2A_dump(Dz1SocketFifo2 *ptr, int tab)
{
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1Fifo_dump(p->fifo, tab);
}
#ifndef UNIX_SYSTEM
void Dz1SocketFifo2W_dump(Dz1SocketFifo2 *ptr, int tab)
{
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1Fifo_dump(p->fifo, tab);
}
#endif
static Dz1SocketFifo2Entry *_Dz1SocketFifo2_push(_Dz1SocketFifo2 *p, void **msg, bool_t verbose, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketFifo2Entry *ret = NULL, *node = Dz1SocketFifo2Entry_new((*msg), NULL, &p->api, verbose, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		if (p->api.del != NULL) *msg = NULL;
		pthread_cleanup_push(Dz1SocketFifo2Entry_delAndSetNull, (void *)&node);

		if ((*errp = Dz1Fifo_push(p->fifo, (void *)node)).code) ERR_OUT(errp);
		else
		{
			ret = node;
			node = NULL;
		}

		pthread_cleanup_pop(1); // (Dz1SocketFifo2Entry_delAndSetNull, (void *)&node);
	}
	return ret;
}

void *Dz1SocketFifo2_peek(Dz1SocketFifo2 *ptr)
{
	void *ret = NULL;
	Dz1SocketFifo2Entry *node = NULL;

	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;

	if (p == NULL) { }
	else if ((node = (Dz1SocketFifo2Entry *)Dz1Fifo_getFirst(p->fifo)) == NULL) { }
	else ret = node->msg;

	return ret;
}

size_t Dz1SocketFifo2_count(Dz1SocketFifo2 *ptr)
{
	size_t ret = 0;

	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;

	if (p != NULL) ret = Dz1Fifo_count(p->fifo);

	return ret;
}

static Dz1Error _Dz1SocketFifo2_encodeAndSend(_Dz1SocketFifo2 *p, Dz1TcpClientSocket *sock,
											  Dz1SocketFifo2Entry *node, struct timeval *to)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SocketMsgAPI *api = node->api;
	Dz1Binary *bin = Dz1Binary_new(NULL, 0, &err);
	if (bin == NULL) ERR_OUT(&err);
	else
	{
		ssize_t size = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((size = api->enc(NULL, -1, node->msg, api->enc_param, &err)) < 0) ERR_OUT(&err);
		else if ((bin->data = (u8_t *)Dz1Malloc((bin->size = (u32_t)size), &err)) == NULL) ERR_OUT(&err);
		else if ((size = api->enc(bin->data, bin->size, node->msg, api->enc_param, &err)) < 0) ERR_OUT(&err);
		else if (size != (ssize_t)bin->size) ERR_SET_OUT(&err, EFAULT);
		else
		{
			if (p->verbose || node->verbose)
			{
				Dz1Thread_eprintf(">>> SOCKET FIFO\n");
				Dz1Thread_tprintb(1, bin->data, bin->size, 16, TRUE);
			}
			if (sock->send(sock, bin->data, bin->size, DZ1_TCP_SOCK_FLAG_COMPLETE, to, &err) < 0) ERR_OUT(&err);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}

Dz1Error _Dz1SocketFifo2_sendTCP(Dz1SocketFifo2 *ptr, Dz1TcpClientSocket *sock, void **msg, struct timeval *to, bool_t msg_verbose)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;
	if (p == NULL || msg == NULL || *msg == NULL || sock == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1SocketFifo2Entry *node = NULL, *suspend = (Dz1SocketFifo2Entry *)Dz1Fifo_getFirst(p->fifo);
		if ((node = _Dz1SocketFifo2_push(p, msg, msg_verbose, &err)) == NULL) ERR_OUT(&err);
		else if (suspend != NULL) { /* NOP */ }
		else if ((err = _Dz1SocketFifo2_encodeAndSend(p, sock, node, to)).code) ERR_OUT(&err);
	}
	return err;
}

Dz1Error Dz1SocketFifo2_repeatTCP(Dz1SocketFifo2 *ptr, Dz1TcpClientSocket *sock, struct timeval *to)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;
	Dz1SocketFifo2Entry *node = NULL;
	if (p == NULL || sock == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((node = (Dz1SocketFifo2Entry *)Dz1Fifo_getFirst(p->fifo)) == NULL) ERR_SET_OUT(&err, ENOENT);
	else if (node->stream != NULL)
	{
		Dz1Binary *stream = node->stream;
		if (sock->send(sock, stream->data, stream->size, DZ1_TCP_SOCK_FLAG_COMPLETE, to, &err) < 0) ERR_OUT(&err);
	}
	else if ((err = _Dz1SocketFifo2_encodeAndSend(p, sock, node, to)).code) ERR_OUT(&err);
	return err;
}

Dz1Error Dz1SocketFifo2_retryTCP(Dz1SocketFifo2 *ptr, Dz1TcpClientSocket *sock, struct timeval *to)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;
	Dz1SocketFifo2Entry *node = NULL;

	if (p == NULL || sock == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((node = (Dz1SocketFifo2Entry *)Dz1Fifo_getFirst(p->fifo)) == NULL) ERR_SET_OUT(&err, ENOENT);
	else if ((err = _Dz1SocketFifo2_encodeAndSend(p, sock, node, to)).code) ERR_OUT(&err);

	return err;
}

Dz1Error Dz1SocketFifo2_continueTCP(Dz1SocketFifo2 *ptr, Dz1TcpClientSocket *sock, struct timeval *to)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;
	Dz1SocketFifo2Entry *node = NULL;

	if (p == NULL || sock == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((node = (Dz1SocketFifo2Entry *)Dz1Fifo_pop(p->fifo, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1SocketFifo2Entry *next = NULL;
		pthread_cleanup_push(Dz1SocketFifo2Entry_delAndSetNull, (void *)&node);

		if ((next = (Dz1SocketFifo2Entry *)Dz1Fifo_getFirst(p->fifo)) == NULL) { /* NOP */ }
		else if ((err = _Dz1SocketFifo2_encodeAndSend(p, sock, next, to)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // (Dz1SocketFifo2Entry_delAndSetNull, (void *)&node);
	}
	return err;
}

void Dz1SocketFifo2_setVerbose(Dz1SocketFifo2 *fifo, bool_t verbose)
{
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)fifo;
	if (p != NULL)
		p->verbose = verbose;
}
// Socket TX FIFO Type 2 : CODEC Mode(deprecated)
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SocketFifo3API API
void Dz1SocketFifo3API_del(Dz1SocketFifo3API *p)
{
	if (!p) return;
	// Additional delete code here
	if (p->param_del != NULL && p->param != NULL) p->param_del(p->param_del);
	Dz1Free(p);
}

Dz1SocketFifo3API *Dz1SocketFifo3API_new(Dz1SocketFifo3Encoder msg_enc,
										 Dz1CloneFunc msg_clone, Dz1DelFunc msg_del, Dz1DumpFunc msg_dump,
										 void *param, Dz1DelFunc param_del, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SocketFifo3API *ret = NULL;
	
	if (msg_enc == NULL || msg_del == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1SocketFifo3API *)Dz1Calloc(sizeof(Dz1SocketFifo3API), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ret->msg_enc = msg_enc;
		ret->msg_del = msg_del;
		ret->msg_dump = msg_dump;

		ret->param = param;
		ret->param_del = param_del;

		Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1SocketFifo3API *Dz1SocketFifo3API_clone(Dz1SocketFifo3API *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SocketFifo3API *ret = (Dz1SocketFifo3API *)Dz1Calloc(sizeof(Dz1SocketFifo3API), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->msg_enc = src->msg_enc;
		ret->msg_del = src->msg_del;
		ret->msg_dump = src->msg_dump;

		ret->param = src->param;
		ret->param_del = src->param_del;

		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1SocketFifo3API_dump(Dz1SocketFifo3API *p, int tab)
{
	if (!p) { Dz1Thread_eprintf("NULL\n"); return; }
	else
	{
		Dz1Thread_eprintf("{\n"); tab++;
		Dz1Thread_eprintf("msg_enc = %p\n", p->msg_enc);
		Dz1Thread_eprintf("msg_del = %p\n", p->msg_del);
		Dz1Thread_eprintf("msg_dump = %p\n", p->msg_dump);
		Dz1Thread_eprintf("param = %p\n", p->param);
		Dz1Thread_eprintf("param_del = %p\n", p->param_del);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}
// Dz1SocketFifo3API API
////////////////////////////////////////////////////////////////////////////////


Dz1SocketFifo3Entry *Dz1SocketFifo3Entry_new(void *msg, Dz1SocketFifo3API *api, bool_t verbose, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketFifo3Entry *ret = (Dz1SocketFifo3Entry *)Dz1Calloc(sizeof(Dz1SocketFifo3Entry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->msg = msg;
		ret->api = api;

		ret->verbose = verbose;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1SocketFifo3Entry_del(Dz1SocketFifo3Entry *p)
{
	if (p == NULL) return;
	else
	{
		Dz1SocketFifo3API *api = p->api;
		if (api->msg_del && p->msg) api->msg_del(p->msg);
		p->msg = NULL;
		Dz1Free(p);
	}
}

void Dz1SocketFifo3Entry_dump(Dz1SocketFifo3Entry *p, int tab)
{
	if (p == NULL) Dz1Thread_eprintf("NULL\n");
	else
	{
		Dz1SocketFifo3API *api = p->api;
		if (api->msg_dump) api->msg_dump(p->msg, tab);
		else Dz1Thread_eprintf("msg = %p\n", p->msg);
	}
}

/*
typedef struct _Dz1SocketFifo3
{
	bool_t				 wait_sent;

	Dz1Fifo				*fifo;
	Dz1SocketFifo3API	*api;

	Dz1ElasticBuf		*tx_buf;
	Dz1Stream			*encode_dst;

	bool_t				 verbose;				// common verbose
} _Dz1SocketFifo3;
*/
Dz1SocketFifo3 *Dz1SocketFifo3_new(u32_t alloc_unit_sz, Dz1SocketFifo3Encoder msg_enc,
								   Dz1CloneFunc msg_clone, Dz1DelFunc msg_del, Dz1DumpFunc msg_dump,
								   void *param, Dz1DelFunc param_del, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1SocketFifo3 *ret = (_Dz1SocketFifo3 *)Dz1Calloc(sizeof(_Dz1SocketFifo3), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SocketFifo3_delAndSetNull, (void *)&ret);
		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)Dz1SocketFifo3Entry_del,
									 (Dz1DumpFunc)Dz1SocketFifo3Entry_dump,
									 -1, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->api = Dz1SocketFifo3API_new(msg_enc, msg_clone, msg_del, msg_dump, param, param_del, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->tx_buf = Dz1ElasticBuf_new(alloc_unit_sz, TRUE, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->encode_dst = Dz1Stream_openRefElasticBuf(ret->tx_buf, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->wait_sent = FALSE;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SocketFifo3_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SocketFifo3_del(Dz1SocketFifo3 *ptr)
{
	_Dz1SocketFifo3 *p = (_Dz1SocketFifo3 *)ptr;
	if (p == NULL) return;

	if (p->fifo) Dz1Fifo_delAndSetNull(&p->fifo);
	if (p->api) Dz1SocketFifo3API_delAndSetNull(&p->api);
	if (p->encode_dst) Dz1Stream_closeAndSetNull(&p->encode_dst);
	if (p->tx_buf) Dz1ElasticBuf_delAndSetNull(&p->tx_buf);

	Dz1Free(p);
}

void Dz1SocketFifo3A_dump(Dz1SocketFifo3 *ptr, int tab)
{
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1Fifo_dump(p->fifo, tab);
}
#ifndef UNIX_SYSTEM
void Dz1SocketFifo3W_dump(Dz1SocketFifo3 *ptr, int tab)
{
	_Dz1SocketFifo2 *p = (_Dz1SocketFifo2 *)ptr;
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1Fifo_dump(p->fifo, tab);
}
#endif
/*
static Dz1SocketFifo3Entry *_Dz1SocketFifo3_push(_Dz1SocketFifo3 *p, void **msg, bool_t verbose, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketFifo3Entry *ret = NULL, *node = Dz1SocketFifo3Entry_new((*msg), p->api, verbose, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		Dz1SocketFifo3API *api = p->api;
		if (api->msg_del != NULL) *msg = NULL;
		pthread_cleanup_push(Dz1SocketFifo2Entry_delAndSetNull, (void *)&node);

		if ((*errp = Dz1Fifo_push(p->fifo, (void *)node)).code) ERR_OUT(errp);
		else
		{
			ret = node;
			node = NULL;
		}

		pthread_cleanup_pop(1); // (Dz1SocketFifo2Entry_delAndSetNull, (void *)&node);
	}
	return ret;
}
*/

static Dz1Error Dz1SocketFifo3_encodeAndSend(_Dz1SocketFifo3 *p, Dz1TcpClientSocket *sock, void *msg, struct timeval *to, bool_t msg_verbose)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1SocketFifo3API *api = p->api;
	bool_t verbose = p->verbose || msg_verbose;

	ssize_t sz = 0;
	Dz1Binary *bin = NULL;
	if ((*errp = Dz1Stream_seek(p->encode_dst, 0, SEEK_SET)).code) ERR_OUT(errp);
	else if ((sz = api->msg_enc(p->encode_dst, msg, api->param, verbose, errp)) < 0) ERR_OUT(errp);
	else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(p->tx_buf, errp)) == NULL) ERR_OUT(errp);
	else
	{
		if (verbose)
		{
			Dz1Thread_eprintf(">>> SOCKET FIFO\n");
			Dz1Thread_tprintb(1, bin->data, sz, 16, TRUE);
		}

		if (sock->send(sock, bin->data, sz, DZ1_TCP_SOCK_FLAG_COMPLETE, to, &err) < 0) ERR_OUT(&err);
	}
	return err;
}

Dz1Error Dz1SocketFifo3_sendTCP(Dz1SocketFifo3 *ptr, Dz1TcpClientSocket *sock,
								void *msg, struct timeval *to, bool_t msg_verbose)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	_Dz1SocketFifo3 *p = (_Dz1SocketFifo3 *)ptr;
	if (p == NULL || msg == NULL || sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->wait_sent)
	{	// 전송 완료를 기다리는 중이다 -> node만들어서 Push
		Dz1SocketFifo3Entry *node = NULL;
		if ((node = Dz1SocketFifo3Entry_new(NULL, p->api, msg_verbose, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1SocketFifo3Entry_delAndSetNull, (void *)&node);
			if ((node->msg = p->api->msg_clone(msg, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = Dz1Fifo_push(p->fifo, (void *)node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1SocketFifo3Entry_delAndSetNull, (void *)&node);
		}
	}
	else
	{	// 바로 전송
		if ((*errp = Dz1SocketFifo3_encodeAndSend(p, sock, msg, to, msg_verbose)).code) ERR_OUT(errp);
		else
		{
			p->wait_sent = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

Dz1Error Dz1SocketFifo3_sent(Dz1SocketFifo3 *ptr, Dz1TcpClientSocket *sock, struct timeval *to)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	_Dz1SocketFifo3 *p = (_Dz1SocketFifo3 *)ptr;

	if (p == NULL || sock == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1SocketFifo3Entry *node = (Dz1SocketFifo3Entry *)Dz1Fifo_pop(p->fifo, NULL);

		p->wait_sent = FALSE;

		if (node != NULL)
		{
			pthread_cleanup_push(Dz1SocketFifo3Entry_delAndSetNull, (void *)&node);
			if ((*errp = Dz1SocketFifo3_encodeAndSend(p, sock, node->msg, to, node->verbose)).code) ERR_OUT(errp);
			else
			{
				p->wait_sent = TRUE;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1SocketFifo3Entry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

void Dz1SocketFifo3_setVerbose(Dz1SocketFifo3 *fifo, bool_t verbose)
{
	_Dz1SocketFifo3 *p = (_Dz1SocketFifo3 *)fifo;
	if (p != NULL) p->verbose = verbose;
}
