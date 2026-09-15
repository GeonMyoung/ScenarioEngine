#include <dz1_thread.h>
#include <dz1_aatree.h>
#include <dz1_thread_stdio.h>
#include "dz1_socket_callback_skel.h"

#ifdef LINUX
#include <sys/epoll.h>

#define EVENTS_PER_THREAD			127
//#define DZ1_SOCKET_CALLBACK_DEBUG

static u32_t _get_cpu_count(void)
{
	long v = sysconf(_SC_NPROCESSORS_ONLN);
	return (u32_t)(v & 0xFFFFFFFF);
}

#if 0
///////////////////////////////////////////////////////////////////////////////
// Socket Callback Info
static u16_t id_alloc = 0;
/*
typedef struct Dz1ScoketCallbackInfo
{
	DZ1_SOCKET_CALLBACK_SKEL_MEMBER;
	// ------------------------ SKEL ---------------------
	u32_t							 id;
	u8_t							*tx_src;
} Dz1SocketCallbackInfo;
*/

void Dz1SocketCallbackSkel_del(Dz1SocketCallbackSkel *p)
{
	//Dz1SocketCallbackInfo *p = (Dz1SocketCallbackInfo *)ptr;
	if (p == NULL) return;

	Dz1SockAddr_delAndSetNull(&p->peer);
	Dz1SockAddr_delAndSetNull(&p->local);

	_free_wsa_buf(&p->rx_buf);

	_clean_wsa_ref(&p->tx_ptr);
#ifdef _DZ1_USE_SSL
	Dz1Binary_delAndSetNull(&p->io_buf);
	if (p->ssl) SSL_shutdown(p->ssl);
	if (p->ctx) SSL_CTX_free(p->ctx);
	if (p->ssl) SSL_free(p->ssl);
#else
	if (p->tx_src != NULL) Dz1Memory_freeAndSetNull(&p->tx_src);
#endif
	if (p->cb_rx_param != NULL && p->cb_rx_param_del != NULL) p->cb_rx_param_del(p->cb_rx_param);
	if (p->cb_tx_param != NULL && p->cb_tx_param_del != NULL) p->cb_tx_param_del(p->cb_tx_param);

	if (p->origin_specific && p->origin_specific_del) p->origin_specific_del(p->origin_specific);
	p->origin_specific = NULL;

	pthread_mutex_destroy(&p->lock);
	Dz1Free(p);
}

static u32_t _mk_scb_id(SOCKET s)
{
	u16_t s_h = (u16_t)((s & 0xFFFF0000) >> 16);
	u16_t s_l = (u16_t)(s & 0xFFFF);
	u16_t id_h = id_alloc++;
	return (((u32_t)id_h) << 16) | (((u32_t)(s_h ^ s_l)) & 0xFFFF);
}

Dz1SocketCallbackSkel *Dz1SocketCallbackSkel_new(SOCKET s, Dz1SockAddr *peer, Dz1SockAddr *local,
												 u32_t rx_buf_size,
												 Dz1SocketCallbackRx rx, void *rx_arg, Dz1DelFunc rx_arg_del,
												 Dz1SocketCallbackTx tx, void *tx_arg, Dz1DelFunc tx_arg_del,
												 void *origin_specific, Dz1DelFunc origin_specific_del,
												 Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketCallbackSkel *ret = (Dz1SocketCallbackSkel *)Dz1Calloc(sizeof(Dz1SocketCallbackSkel), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_mutex_init(&ret->lock, NULL);
		pthread_cleanup_push(Dz1SocketCallbackSkel_delAndSetNull, (void *)&ret);

		ret->id = _mk_scb_id(s);

		ret->ref_cnt = 0;

		ret->s = s;

		ret->cb_rx = rx;
		ret->cb_rx_param = rx_arg;
		ret->cb_rx_param_del = rx_arg_del;

		_clean_wsa_ref(&ret->tx_ptr);

		ret->cb_tx = tx;
		ret->cb_tx_param = tx_arg;
		ret->cb_tx_param_del = tx_arg_del;

		ret->origin_specific = origin_specific;
		ret->origin_specific_del = origin_specific_del;

		ret->del_self = (Dz1DelFunc)Dz1SocketCallbackSkel_del;

		ret->rx_osh = -1;
		ret->tx_osh = -1;
#ifdef _DZ1_USE_SSL
		ret->tx_busy = FALSE;
#endif
		if ((ret->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);

		else if ((*errp = _alloc_wsa_buf(&ret->rx_buf, rx_buf_size)).code) ERR_OUT(errp);
#ifdef _DZ1_USE_SSL
		else if ((ret->io_buf = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, rx_buf_size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->tx_bio_buf = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, rx_buf_size, errp)) == NULL) ERR_OUT(errp);
#endif
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1SocketCallbackInfo_delAndSetNull, (void *)&ret);
	}
	return (Dz1SocketCallbackSkel *)ret;
}

static void Dz1SocketCallbackSkel_dump(Dz1SocketCallbackSkel *p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else
	{
		char buf[53];
		Dz1Thread_printf("{\n"); tab++;
		Dz1Thread_tprintf(tab, "id = %u\n", p->id);
		Dz1Thread_tprintf(tab, "ref = %u\n", p->ref_cnt);
		Dz1Thread_tprintf(tab, "socket = %d\n", p->s);
		Dz1Thread_tprintf(tab, "peer = %s\n", Dz1SockAddr_printable(p->peer, buf, FALSE, NULL));
		Dz1Thread_tprintf(tab, "local = %s\n", Dz1SockAddr_printable(p->local, buf, FALSE, NULL));
		Dz1Thread_tprintf(tab, "poll_in = %d\n", p->rx_osh);
		Dz1Thread_tprintf(tab, "poll_out = %d\n", p->tx_osh);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

static int Dz1SocketCallbackSkel_cmp(Dz1SocketCallbackSkel *a, Dz1SocketCallbackSkel *b)
{
	if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (a->id < b->id) return -1;
	else if (a->id > b->id) return 1;
	else return 0;
}

// Socket Callback Info
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Socket Pool
static Dz1AATree *sock_pool = NULL;

static Dz1Error sock_pool_init(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (sock_pool != NULL) { }
	else if ((sock_pool = Dz1AATree_new((Dz1CmpFunc)Dz1SocketCallbackSkel_cmp,
										(Dz1DelFunc)Dz1SocketCallbackSkel_del,
										(Dz1DumpFunc)Dz1SocketCallbackSkel_dump, &err)) == NULL) ERR_OUT(&err);
	return err;
}

static void sock_pool_clean(void)
{
	if (sock_pool == NULL) { }
	else Dz1AATree_delAndSetNull(&sock_pool);
}

///////////////////////
// sock pool dereg
static bool_t _sock_pool_dereg(void *ptr, void *data)
{
	bool_t ret = FALSE;
	Dz1SocketCallbackSkel *info = (Dz1SocketCallbackSkel *)data;
	if (--info->ref_cnt == 0) ret = TRUE;
	return ret;
}

static Dz1SocketCallbackSkel *sock_pool_dereg(u32_t id, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketCallbackSkel key, *ret = NULL;
	key.id = id;
	if (sock_pool == NULL) ERR_SET_OUT(errp, ENOSYS);
	else ret = (Dz1SocketCallbackSkel *)Dz1AATree_extractConditional(sock_pool, (void *)&key, _sock_pool_dereg, NULL, NULL);
	return ret;
}
// sock pool dereg
///////////////////////

///////////////////////
// sock pool put
static Dz1Error sock_pool_put(u32_t sid)
{
	Dz1SocketCallbackSkel *info = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (sock_pool == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((info = sock_pool_dereg(sid, errp)) != NULL)
	{
		pthread_cleanup_push(Dz1SocketCallbackSkel_delAndSetNull, (void *)&info);
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
		Dz1Thread_printf("!!! Delete Socket Callback Info\n");
#endif
		pthread_cleanup_pop(1); // (Dz1SocketCallback_delAndSetNull, (void *)&info);
	}
	return err;
}
// sock pool put
///////////////////////

///////////////////////
// sock pool reg
static void _sock_pool_reg(void *ptr, void *data)
{
	Dz1SocketCallbackSkel *info = (Dz1SocketCallbackSkel *)data;
	info->ref_cnt++;
}

static Dz1Error sock_pool_reg(Dz1SocketCallbackSkel *scb)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (scb == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (sock_pool == NULL) ERR_SET_OUT(&err, ENOSYS);
	else if ((err = Dz1AATree_insertAndDo(sock_pool, scb, _sock_pool_reg, NULL)).code) ERR_OUT(&err);
	return err;
}

static void sock_pool_reg_cancel(void *ptr)
{
	Dz1SocketCallbackSkel *p = (Dz1SocketCallbackSkel *)ptr;
	u32_t id = p->id;
	sock_pool_put(id);
}
// sock pool reg
///////////////////////

///////////////////////
// sock pool get
static void _sock_pool_get(void *ptr, void *data)
{
	Dz1SocketCallbackSkel *info = (Dz1SocketCallbackSkel *)data;
	info->ref_cnt++;
}

static Dz1SocketCallbackSkel *sock_pool_get(u32_t id, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketCallbackSkel key, *ret = NULL;
	key.id = id;
	if (sock_pool == NULL) ERR_SET_OUT(errp, ENOSYS);
	else ret = (Dz1SocketCallbackSkel *)Dz1AATree_findAndDo(sock_pool, (void *)&key, _sock_pool_get, NULL);
	return ret;
}

static void sock_pool_get_cancel(void *ptr)
{
	u32_t sid = *(u32_t *)ptr;
	sock_pool_put(sid);
}
// sock pool get
///////////////////////

// Socket Pool
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// EPoll Monitor
typedef struct Dz1EPollMonInfo
{
	int epoll_fd;
	u32_t epoll_th;
} Dz1EPollMonInfo;

static pthread_mutex_t n_th_lock = PTHREAD_MUTEX_INITIALIZER;
static u32_t n_th_max = 0;
static u32_t n_th_idx = 0;

static Dz1EPollMonInfo ingress[16] = {
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 }
};

static Dz1EPollMonInfo egress[16] = {
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 }
};

static u32_t _get_worker_idx(Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	pthread_mutex_lock(&n_th_lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&n_th_lock);

	if (n_th_max == 0) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		ret = n_th_idx++;
		n_th_idx %= n_th_max;
	}

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&n_th_lock);
	return ret;
}

static Dz1Error _epoll_mon_ingress(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1EPollMonInfo *info = (Dz1EPollMonInfo *)ptr;

	int nfd = 0;
	struct epoll_event events[EVENTS_PER_THREAD], temp;
	while(1)
	{
		pthread_testcancel();
		nfd = epoll_wait(info->epoll_fd, events, EVENTS_PER_THREAD, 100); // 100 ms wait
		pthread_testcancel();

		if (nfd == -1) ERR_SET_OUT(&err, errno);
		else if (nfd > 0)
		{
			u32_t sid;
			int i, status;
			Dz1SocketCallbackSkel *scb = NULL;
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_printf("<<< Dz1TcpClientSocketCallback - RX Event Catch = %d\n", nfd);
#endif
			for (i = 0; i < nfd; i++)
			{
				status = 0;
				scb = (Dz1SocketCallbackSkel *)events[i].data.ptr;

				sid = events[i].data.u32;

				if ((scb = (Dz1SocketCallbackSkel *)sock_pool_get(sid, &err)) == NULL) { Dz1Error_set(&err, 0); }
				else
				{
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
					Dz1Thread_printf("<<< Dz1TcpClientSocketCallback - RX Event = 0x%08x\n", events[i].events);
#endif
					pthread_cleanup_push(sock_pool_get_cancel, (void *)&sid);

					if (events[i].events & EPOLLIN)
					{	// POLLIN Check
						ssize_t size = 0;
						while((size = recv(scb->s, scb->rx_buf.buf, scb->rx_buf.len, MSG_NOSIGNAL)) > 0)
						{	// RX Callback
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
							Dz1Thread_printf("<<< Dz1TcpClientSocketCallback - RX Complete = %u\n", size);
#endif
							scb->rx_complete(scb, (u32_t)size, 0);
						}
					}

					if (events[i].events & EPOLLRDHUP)
					{	// Disconnected
						Dz1Error_set(errp, EPIPE);
						epoll_ctl(info->epoll_fd, EPOLL_CTL_DEL, scb->s, &temp);
						// RX Callback with ERROR
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf("!!! Dz1TcpClientSocketCallback - RX Disconnect\n");
#endif
						scb->rx_complete(scb, 0, errp->code);
					}
					else if (events[i].events & EPOLLERR)
					{	// Error occure
						socklen_t len = sizeof(status);
						if (getsockopt(scb->s, SOL_SOCKET, SO_ERROR, (void *)&status, &len) != 0) Dz1Error_set(errp, EFAULT);
						else Dz1Error_set(errp, status);
						epoll_ctl(info->epoll_fd, EPOLL_CTL_DEL, scb->s, &temp);
						// RX Callback with ERROR
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf("!!! Dz1TcpClientSocketCallback - RX Error = %d\n", errp->code);
#endif
						scb->rx_complete(scb, 0, errp->code);
					}
					pthread_cleanup_pop(1); // (sock_pool_get_cancel, (void *)&sid);
				}
			}
		}
	}
	return err;
}

static Dz1Error _epoll_mon_egress(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1EPollMonInfo *info = (Dz1EPollMonInfo *)ptr;

	int nfd = 0;
	struct epoll_event events[EVENTS_PER_THREAD], temp;
	while(1)
	{
//		Dz1Thread_printf("e");

		pthread_testcancel();
		nfd = epoll_wait(info->epoll_fd, events, EVENTS_PER_THREAD, 100); // 100 ms wait
		pthread_testcancel();

		if (nfd == -1) ERR_SET_OUT(&err, errno);
		else if (nfd > 0)
		{
			int i;
			u32_t sid;
			Dz1SocketCallbackSkel *scb = NULL;

//			Dz1Thread_printf("E");

			for (i = 0; i < nfd; i++)
			{
				sid = events[i].data.u32;

				if ((scb = (Dz1SocketCallbackSkel *)sock_pool_get(sid, &err)) == NULL) Dz1Error_set(&err, 0);
				else
				{
					pthread_cleanup_push(sock_pool_get_cancel, (void *)&sid);

					pthread_mutex_lock(&scb->lock);
					pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&scb->lock);

					if (events[i].events & EPOLLOUT)
					{	// Ready to send
						ssize_t size = 0;
						while((size = send(scb->s, scb->tx_ptr.buf, scb->tx_ptr.len, MSG_NOSIGNAL)) > 0)
						{	// sent
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
							Dz1Thread_printf(">>> Dz1TcpClientSocketCallback - TX Complete = %u\n", size);
#endif
							scb->tx_complete(scb, size, 0);
						}
					}

					if (events[i].events & EPOLLHUP)
					{	// Disconnected
						Dz1Error_set(errp, EPIPE);
						epoll_ctl(info->epoll_fd, EPOLL_CTL_DEL, scb->s, &temp);
						// TX Callback with ERROR
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf("!!! Dz1TcpClientSocketCallback - TX Disconnect\n");
#endif
						scb->tx_complete(scb, 0, errp->code);
					}
					else if (events[i].events & EPOLLERR)
					{
						int status = 0;
						socklen_t len = sizeof(status);
						if (getsockopt(scb->s, SOL_SOCKET, SO_ERROR, (void *)&status, &len) != 0) Dz1Error_set(errp, EFAULT);
						else Dz1Error_set(errp, status);
						epoll_ctl(info->epoll_fd, EPOLL_CTL_DEL, scb->s, &temp);
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf("!!! Dz1TcpClientSocketCallback - TX Error = %d\n", errp->code);
#endif
						// TX Callback with ERROR
						scb->tx_complete(scb, 0, errp->code);
					}

					pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&scb->lock);

					pthread_cleanup_pop(1); // (sock_pool_get_cancel, (void *)&sid);
				}
			}
		}
	}
	return err;
}


// EPoll Monitor
///////////////////////////////////////////////////////////////////////////////

static void _epoll_fd_cancel(void *ptr)
{
	Dz1EPollMonInfo *p = (Dz1EPollMonInfo *)ptr;
	if (p->epoll_fd != -1)
		close(p->epoll_fd);
	p->epoll_fd = -1;
}

static Dz1Error _init_thread(Dz1EPollMonInfo *p, Dz1ThreadFunc func)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if ((p->epoll_fd = epoll_create(1)) == -1) ERR_SET_OUT(errp, errno);
	else
	{
		pthread_cleanup_push(_epoll_fd_cancel, (void *)p);

		if ((err = Dz1Thread_create(&p->epoll_th, func, (void *)p, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(&err);

		pthread_cleanup_pop(err.code); // (_epoll_fd_cancal, (void *)&th_in[i]);
	}
	return err;
}

static void _thread_cancel(Dz1EPollMonInfo *p)
{
	if (p == NULL) return;
	if (p->epoll_th != -1)
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		if ((err = Dz1Thread_stop(p->epoll_th, FALSE)).code == 0)
			Dz1Thread_wait(p->epoll_th, NULL);
		p->epoll_th = -1;
	}
}

static void _init_cancel(void *ptr)
{
	Dz1SocketCallbackSkel_clean();
}

static void Dz1TcpClientSocket_callbackClose(void *ptr)
{
	u32_t sid = (u32_t)DZ1_PTR2VAL32(ptr);
	sock_pool_put(sid);
}

///////////////////////////////////////////////////////////////////////////////
//// Private API
/////////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1SocketCallbackSkel_txRequest(Dz1SocketCallbackSkel *scb)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	struct epoll_event ev;
	ev.events = EPOLLOUT | EPOLLET;
	ev.data.u32 = scb->id;

	if (epoll_ctl(scb->tx_osh, EPOLL_CTL_MOD, scb->s, &ev) != 0) ERR_SET_OUT(&err, errno);
#ifdef _DZ1_USE_SSL
	else
	{
		scb->tx_busy = TRUE;
	}
#endif
	return err;
}

Dz1Error Dz1SocketCallbackSkel_rxRequest(Dz1SocketCallbackSkel *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	return err;
}

void Dz1SocketCallbackSkel_bind(Dz1SocketCallbackSkel *scb , Dz1TcpClientSocket *sock)
{
	scb->origin_specific = sock->specific;
	scb->origin_specific_del = sock->specific_del;
	sock->specific = (void *)DZ1_VAL2PTR32(scb->id);
	sock->specific_del = Dz1TcpClientSocket_callbackClose;

	sock->wait = Dz1SocketCallbackSkel_wait;
	sock->recv = Dz1SocketCallbackSkel_recv;
	sock->getOSHandle = NULL;
}

ssize_t Dz1SocketCallbackSkel_send(Dz1SocketCallbackSkel *scb, u8_t *data, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = -1;

	pthread_mutex_lock(&scb->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&scb->lock);

	if (scb->tx_src != NULL) ERR_SET_OUT(errp, EAGAIN);
	else if ((scb->tx_src = (u8_t *)Dz1Memory_clone(data, size, errp)) == NULL) ERR_OUT(errp);
	else
	{
		_init_wsa_ref(&scb->tx_ptr, scb->tx_src, size);
		if ((*errp = Dz1SocketCallbackSkel_txRequest((Dz1SocketCallbackSkel *)scb)).code) ERR_OUT(errp);
		else ret = size;
	}

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&scb->lock);
	return ret;
}

Dz1Error Dz1SocketCallbackSkel_associate(Dz1SocketCallbackSkel *scb, SOCKET s)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	struct epoll_event ev;
	u32_t idx;

	while((*errp = sock_pool_reg(scb)).code != 0)	// when success sock_pool_reg then ref_cnt is increated
	{
		if (errp->code == EEXIST)
			scb->id = _mk_scb_id(s);
		else return err;
	}

	pthread_cleanup_push(sock_pool_reg_cancel, (void *)scb);

	if ((idx = _get_worker_idx(&err)) == -1) ERR_OUT(&err);
	else
	{
		ev.data.u32 = scb->id;
		
		ev.events = EPOLLIN | EPOLLPRI | EPOLLRDHUP;
		scb->rx_osh = ingress[idx].epoll_fd;
		scb->tx_osh = egress[idx].epoll_fd;

		if (epoll_ctl(scb->rx_osh, EPOLL_CTL_ADD, s, &ev) != 0) ERR_SET_OUT(&err, errno);
		else
		{
			ev.events = EPOLLOUT;
			if (epoll_ctl(scb->tx_osh, EPOLL_CTL_ADD, s, &ev) != 0) ERR_SET_OUT(&err, errno);
		}
	}

	pthread_cleanup_pop(errp->code); // (scb_registration_cancel, (void *)p);

	return err;
}

Dz1SocketCallbackSkel *Dz1SocketCallbackSkel_grab(Dz1TcpClientSocket *sock, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketCallbackSkel *ret = NULL;
	if (sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t sid = (u32_t)DZ1_PTR2VAL32(sock->specific);
		if ((ret = sock_pool_get(sid, errp)) == NULL) ERR_OUT(errp);
	}
	return ret;
}

void Dz1SocketCallbackSkel_release(Dz1TcpClientSocket *sock)
{
	if (sock == NULL) return;
	else
	{
		u32_t sid = (u32_t)DZ1_PTR2VAL32(sock->specific);
		sock_pool_put(sid);
	}
}

///////////////////////////////////////////////////////////////////////////////
//// Public API
/////////////////////////////////////////////////////////////////////////////////
bool_t Dz1SocketCallbackSkel_isReady(void)
{
	if (sock_pool == NULL) return FALSE;
	return TRUE;
}

Dz1Error Dz1SocketCallbackSkel_init(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = sock_pool_init()).code) ERR_OUT(&err);
	else
	{
		u32_t numOfThread = -1;
		u32_t cpus = _get_cpu_count(), i;
		
		pthread_mutex_lock(&n_th_lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&n_th_lock);

		numOfThread = n_th_max = (cpus << 1) > 16 ? 16 : (cpus << 1);
		Dz1Thread_printf("@@@ Working Thread = %u\n", n_th_max);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&n_th_lock);

		pthread_cleanup_push(_init_cancel, NULL);
		for (i = 0; err.code == 0 && i < numOfThread; i++)
		{
			if ((err = _init_thread(&ingress[i], _epoll_mon_ingress)).code) ERR_OUT(&err);
			else if ((err = _init_thread(&egress[i], _epoll_mon_egress)).code) ERR_OUT(&err);
		}
		pthread_cleanup_pop(err.code); // (_cancel_init, NULL);
	}
	return err;
}

void Dz1SocketCallbackSkel_clean(void)
{
	int i;
	for (i = 0; i < 16; i++)
	{
		_thread_cancel(&ingress[i]);
		_thread_cancel(&egress[i]);
		_epoll_fd_cancel(&ingress[i]);
		_epoll_fd_cancel(&egress[i]);
	}
	sock_pool_clean();
}
///////////////////////////////////////////////////////////////////////////////
// Native Socket API
///////////////////////////////////////////////////////////////////////////////
#endif










































#define DZ1_EPOLL_WORKER_MAX				16
static int ep_in = -1;
static int ep_out = -1;

static u32_t monitorRX[DZ1_EPOLL_WORKER_MAX] =	{ -1, };	// MAX 16 core
static u32_t monitorTX[DZ1_EPOLL_WORKER_MAX] =	{ -1, };	// MAX 16 core
static u32_t numOfCpu = 1;

static bool_t monitorStop = FALSE;

// static Dz1SocketCallback2Mon *Dz1SocketCallback2Mon_select(Dz1SocketCallback2Mon monitors[], Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 
// 	Dz1SocketCallback2Mon *ret = NULL, *mon;
// 
// 	u32_t sock_cnt = 0xFFFFFFFF;
// 	int i;
// 	for (i = 0, mon = monitors; i < DZ1_EPOLL_WORKER_MAX && mon->thid != -1; i++, mon++)
// 	{
// 		if (mon->sock_cnt == 0)
// 		{
// 			sock_cnt = mon->sock_cnt;
// 			ret = mon;
// 			break;
// 		}
// 		else if (sock_cnt > mon->sock_cnt)
// 		{
// 			sock_cnt = mon->sock_cnt;
// 			ret = mon;
// 		}
// 	}
// 
// 	if (ret == NULL) ERR_SET_OUT(errp, ENOSYS);
// 
// 	return ret;
// }

static Dz1Error Dz1SocketCallback2MonThreadTX(void *ptr)
{
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	u32_t id = (u32_t)DZ1_PTR2VAL32(ptr);
#endif
	DZ1_ERROR_SAFE_VAR(errp, err);
//	Dz1SocketCallback2Mon *arg = (Dz1SocketCallback2Mon *)ptr;

	int nfd = 0;
	struct epoll_event events[EVENTS_PER_THREAD], temp;
	while(1)
	{
		pthread_testcancel();
		nfd = epoll_wait(ep_out, events, EVENTS_PER_THREAD, 100); // 100 ms wait
		pthread_testcancel();

		if		(nfd < 0) ERR_SET_OUT(&err, errno);
		else if (nfd == 0)
		{	// TIMEDOUT
			if (monitorStop == TRUE) break;
		}
		else if (nfd > 0)
		{
			int i;
			Dz1SocketCallback2Spec *spec = NULL;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_printf(">>> Dz1SocketCallback2MonThreadTX(%u) : Event Catch = %d\n", id, nfd);
#endif
			for (i = 0; i < nfd; i++)
			{
				spec = (Dz1SocketCallback2Spec *)events[i].data.ptr;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
				Dz1Thread_printf(">>> Dz1SocketCallback2MonThreadTX(%u) : TX Event Flag = 0x%08x\n", id, events[i].events);
#endif

				if (spec->own_sock.getOSHandle == NULL)
				{	// user closed
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
					Dz1Thread_printf(">>! Dz1SocketCallback2MonThreadTX(%u) : User Closed\n", id);
#endif
					epoll_ctl(ep_out, EPOLL_CTL_DEL, spec->fd, &temp);
					Dz1SocketCallback2Spec_del(spec);
				}
				else
				{
					int ref_cnt = 0;
					ssize_t sz = 0;

					pthread_mutex_lock(&spec->lock);
					pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

					// increase ref count
					spec->ref_cnt++;

					if ((events[i].events & EPOLLRDHUP) || (events[i].events & EPOLLHUP))
					{	// Disconnected
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf(">>! Dz1SocketCallback2MonThreadTX(%u) : TX Disconnect\n", id);
#endif
						epoll_ctl(ep_out, EPOLL_CTL_DEL, spec->fd, &temp);
						Dz1Error_set(errp, EPIPE);
					}
					else if (events[i].events & EPOLLERR)
					{	// Error occur
						int status = 0;
						socklen_t len = sizeof(status);
						if (getsockopt(spec->fd, SOL_SOCKET, SO_ERROR, (void *)&status, &len) != 0)
							Dz1Error_set(errp, EFAULT);
						else Dz1Error_set(errp, status);

						epoll_ctl(ep_out, EPOLL_CTL_DEL, spec->fd, &temp);

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf(">>! Dz1SocketCallback2MonThreadTX(%u) : TX Error = %d\n", id, errp->code);
#endif
					}
					else
					{	// POLL_OUT
						Dz1SocketCallback2Buffer *buf = NULL;

						if ((buf = spec->tx_buf) != NULL)
						{
							u8_t *cp = (u8_t *)buf->io_ptr.buf;
							size_t len = buf->io_ptr.len;
							ssize_t sent = 0;

							while(len)
							{
								if ((sent = send(spec->fd, cp, len, MSG_NOSIGNAL)) > 0)
								{
									cp += sent;
									len -= sent;
									sz += sent;
								}
								else break;
							}

							if (sent <= 0)
							{
								sz = 0;
								if (sent == 0) Dz1Error_set(errp, EPIPE);
								else Dz1Error_set(errp, errno);

								epoll_ctl(ep_out, EPOLL_CTL_DEL, spec->fd, &temp);
							}
						}

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf(">>> Dz1SocketCallback2MonThreadTX(%u) : TX Complete = %u, code = %d\n", id, sz, errp->code);
#endif
					}

					pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

					// spec->ref_cnt are can't be 0, because ref_cnt is already increased at front of this procedure
					Dz1SocketCallback2_skel_tx_complete(spec, sz, errp->code);

//					if (Dz1SocketCallback2_skel_tx_complete(spec, sz, errp->code) == FALSE)
//					{
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
//						Dz1Thread_printf(">>! Dz1SocketCallback2MonThreadTX(%u) : Delete Spec\n", id);
#endif
//						epoll_ctl(ep_out, EPOLL_CTL_DEL, spec->fd, &temp);
//						spec->release(spec);
//					 	_Dz1SocketCallback2Spec_del(spec);
//					}

					// decrease ref count
					pthread_mutex_lock(&spec->lock);
					pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
					if (spec->ref_cnt > 0) spec->ref_cnt--;
					ref_cnt = spec->ref_cnt;
					pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

					if (ref_cnt == 0)
					{
						epoll_ctl(ep_out, EPOLL_CTL_DEL, spec->fd, &temp);
						spec->release(spec);
					}
				}
			}
		}
	}
	return err;
}

static Dz1Error Dz1SocketCallback2MonThreadRX(void *ptr)
{
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	u32_t id = (u32_t)DZ1_PTR2VAL32(ptr);
#endif
	DZ1_ERROR_SAFE_VAR(errp, err);
//	Dz1SocketCallback2Mon *arg = (Dz1SocketCallback2Mon *)ptr;

	int nfd = 0;
	struct epoll_event events[EVENTS_PER_THREAD], temp;
	while(1)
	{
		pthread_testcancel();
		nfd = epoll_wait(ep_in, events, EVENTS_PER_THREAD, 100); // 100 ms wait
		pthread_testcancel();

		if		(nfd < 0) ERR_SET_OUT(&err, errno);
		else if (nfd == 0)
		{	// TIMEDOUT
			if (monitorStop == TRUE) break;
		}
		else if (nfd > 0)
		{
			int i;
			Dz1SocketCallback2Spec *spec = NULL;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_printf("<<< Dz1SocketCallback2MonThreadRX(%u) : Event Catch = %d\n", id, nfd);
#endif
			for (i = 0; i < nfd; i++)
			{
				spec = (Dz1SocketCallback2Spec *)events[i].data.ptr;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
				Dz1Thread_printf("<<< Dz1SocketCallback2MonThreadRX(%u) : RX Event Flag = 0x%08x\n", id, events[i].events);
#endif
				if (spec->own_sock.getOSHandle == NULL)
				{	// user closed
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
					Dz1Thread_printf("<<! Dz1SocketCallback2MonThreadRX() : User Closed\n");
#endif
					epoll_ctl(ep_in, EPOLL_CTL_DEL, spec->fd, &temp);
					Dz1SocketCallback2Spec_del(spec);
				}
				else
				{
					int ref_cnt = 0;
					ssize_t sz = 0;

					// increase ref count
					pthread_mutex_lock(&spec->lock);
					pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
					spec->ref_cnt++;
					pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

					if ((events[i].events & EPOLLRDHUP) || (events[i].events & EPOLLHUP))
					{	// Disconnected
						Dz1Error_set(errp, EPIPE);
						epoll_ctl(ep_in, EPOLL_CTL_DEL, spec->fd, &temp);
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf("<<! Dz1SocketCallback2MonThreadRX(%u) : RX Disconnect\n", id);
#endif
					}
					else if (events[i].events & EPOLLERR)
					{	// Error occur
						int status = 0;
						socklen_t len = sizeof(status);
						if (getsockopt(spec->fd, SOL_SOCKET, SO_ERROR, (void *)&status, &len) != 0)
							Dz1Error_set(errp, EFAULT);
						else Dz1Error_set(errp, status);
						epoll_ctl(ep_in, EPOLL_CTL_DEL, spec->fd, &temp);
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf("<<! Dz1SocketCallback2MonThreadRX(%u) : RX Error = %d\n", id, errp->code);
#endif
					}
					else
					{	// EPOLLIN | EPOLLPRI
						Dz1SocketCallback2Buffer *buf = spec->rx_buf;
						sz = recv(spec->fd, buf->io_ptr.buf, buf->io_ptr.len, MSG_NOSIGNAL);
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_printf("<<< Dz1SocketCallback2MonThreadRX(%u) : RX Complete = %u\n", id, sz);
#endif
						if (sz <= 0)
						{
							if (sz == 0) Dz1Error_set(errp, EPIPE);
							else
							{
								sz = 0;
								Dz1Error_set(errp, errno);
							}
							epoll_ctl(ep_in, EPOLL_CTL_DEL, spec->fd, &temp);
						}
						else Dz1Error_set(errp, 0);
					}

					// spec->ref_cnt are never be 0, because increase ref_cnt at front of this procedure
					Dz1SocketCallback2_skel_rx_complete(spec, sz, errp->code);
//					if (Dz1SocketCallback2_skel_rx_complete(spec, sz, errp->code) == FALSE)
//					{
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
//						Dz1Thread_printf("<<< Dz1SocketCallback2MonThreadRX(%u) : Delete Spec\n", id);
#endif
//						spec->release(spec);
//						_Dz1SocketCallback2Spec_del(spec);
//					}

					// decrease ref count
					pthread_mutex_lock(&spec->lock);
					pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
					if (spec->ref_cnt > 0) spec->ref_cnt--;
					ref_cnt = spec->ref_cnt;
					pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

					if (ref_cnt == 0)
					{
						epoll_ctl(ep_in, EPOLL_CTL_DEL, spec->fd, &temp);
						spec->release(spec);
					}
				}
			}
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// EPOLL sub system init utility
static void _sys_thread_epoll_fd_cancel(void *ptr)
{
	int *epfd = (int *)ptr;
	if (*epfd != -1) close(*epfd);
	*epfd = -1;
}

static void _sys_thread_init_cancel(void *ptr)
{
	Dz1SocketCallback2_sys_cleanup();
}
// EPOLL sub system init utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// EPOLL sub system Initialize
static Dz1Error _sys_thread_init(u32_t monitors[], int cnt, Dz1ThreadFunc func)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int i;
	u32_t thid = -1;
	for (i = 0; errp->code == 0 && i < cnt; i++)
	{
		if ((*errp = Dz1Thread_create(&thid, func, (void *)DZ1_VAL2PTR32(i), DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(&err);
		else
		{
			monitors[i] = thid;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error _sys_init_in(u32_t monitors[], int cnt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (ep_in == -1)
	{
		if ((ep_in = epoll_create(1)) == -1) ERR_SET_OUT(errp, errno);
		else
		{
			pthread_cleanup_push(_sys_thread_epoll_fd_cancel, (void *)&ep_in);

			if ((*errp = _sys_thread_init(monitors, cnt, Dz1SocketCallback2MonThreadRX)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (_sys_thread_epoll_fd_cancel, (void *)&ep_in);
		}
	}
	return err;
}

static Dz1Error _sys_init_out(u32_t monitors[], int cnt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (ep_out == -1)
	{
		if ((ep_out = epoll_create(1)) == -1) ERR_SET_OUT(errp, errno);
		else
		{
			pthread_cleanup_push(_sys_thread_epoll_fd_cancel, (void *)&ep_out);

			if ((*errp = _sys_thread_init(monitors, cnt, Dz1SocketCallback2MonThreadTX)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (_sys_thread_epoll_fd_cancel, (void *)&ep_in);
		}
	}
	return err;
}

Dz1Error Dz1SocketCallback2_sys_init(void)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	numOfCpu = _get_cpu_count();
	Dz1Thread_printf("@@@ Working Thread = %u\n", numOfCpu);

	pthread_cleanup_push(_sys_thread_init_cancel, NULL);

	if		((*errp = _sys_init_in(monitorRX, numOfCpu)).code) ERR_OUT(errp);
	else if ((*errp = _sys_init_out(monitorTX, numOfCpu)).code) ERR_OUT(errp);

	pthread_cleanup_pop(errp->code); // (_init_cancel, NULL);
	return err;
}
// EPOLL sub system Initialize
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// EPOLL sub system cleanup
//static void _sys_thread_cancel(u32_t *thid)
//{
//	if (thid == NULL) return;
//	if (*thid != -1)
//	{
//		DZ1_ERROR_SAFE_VAR(errp, err);
//		if ((*errp = Dz1Thread_stop(*thid, FALSE)).code) ERR_OUT(errp);
//		Dz1Thread_wait(*thid, NULL);
//		*thid = -1;
//	}
//}

void Dz1SocketCallback2_sys_cleanup(void)
{
	int i;
	monitorStop = TRUE;
	for (i = 0; i < numOfCpu; i++)
	{
//		_sys_thread_cancel(&monitorTX[i]);
//		_sys_thread_cancel(&monitorRX[i]);
		Dz1Thread_printf("@@@ Wait TX Worker %d:%08X\n", i, monitorTX[i]);
		Dz1Thread_wait(monitorTX[i], NULL); monitorTX[i] = -1;

		Dz1Thread_printf("@@@ Wait RX Worker %d:%08X\n", i, monitorRX[i]);
		Dz1Thread_wait(monitorRX[i], NULL); monitorRX[i] = -1;
	}
	if (ep_in != -1) { close(ep_in); ep_in = -1; }
	if (ep_out != -1) { close(ep_out); ep_out = -1; }
	monitorStop = FALSE;
}
// EPOLL sub system cleanup
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1SocketCallback2_sys_reg(SOCKET fd, Dz1SocketCallback2Spec *spec)
{	// Foundational Association with Callback Sub-System = RX registration
	DZ1_ERROR_SAFE_VAR(errp, err);

	struct epoll_event ev;

	ev.data.ptr = spec;
	ev.events = EPOLLONESHOT | EPOLLET;	// edge trigger
	if (epoll_ctl(ep_out, EPOLL_CTL_ADD, spec->fd, &ev) != 0) ERR_SET_OUT(errp, errno);
	else
	{
		// spec->ref_cnt++;
		ev.events = EPOLLIN | EPOLLRDHUP | EPOLLONESHOT;	// level trigger
		if (epoll_ctl(ep_in, EPOLL_CTL_ADD, spec->fd, &ev) != 0) ERR_SET_OUT(&err, errno);
		else
		{
			spec->ref_cnt++;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

bool_t Dz1SocketCallback2_sys_req_tx(Dz1SocketCallback2Spec *spec, Dz1Error  *err)			// unlocked func
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1SocketCallback2Buffer *buf = NULL;

	if ((buf = spec->tx_buf) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (buf->io_ptr.len == 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		struct epoll_event ev;

		ev.data.ptr = spec;
		ev.events = EPOLLOUT | EPOLLONESHOT | EPOLLET;	// edge trigger

		if (epoll_ctl(ep_out, EPOLL_CTL_MOD, spec->fd, &ev) != 0)
		{
			ERR_SET_OUT(errp, errno);
		}
		else
		{
			spec->ref_cnt++;
			Dz1Error_set(errp, 0);
			ret = TRUE;
		}
	}
	return ret;
}

bool_t Dz1SocketCallback2_sys_req_rx(Dz1SocketCallback2Spec *spec, Dz1Error *err)			// unlocked func
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (spec->own_sock.getOSHandle == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		struct epoll_event ev;

		ev.data.ptr = spec;
		ev.events = EPOLLIN | EPOLLRDHUP | EPOLLONESHOT;	// level trigger

		if (epoll_ctl(ep_in, EPOLL_CTL_MOD, spec->fd, &ev) != 0) ERR_SET_OUT(errp, errno);
		else
		{
			spec->ref_cnt++;
			Dz1Error_set(errp, 0);
			ret = TRUE;
		}
	}
	return ret;
}

#else
int __avoid_no_symbol_warning_dz1_socket_callback_skel_linux__ = 0;
#endif
