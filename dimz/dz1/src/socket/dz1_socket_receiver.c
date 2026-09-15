#include <dz1_thread.h>
#include <dz1_usleep.h>
#include <dz1_malloc.h>
#include <dz1_socket_receiver.h>

typedef struct Dz1TcpSocketReceiver
{
	Dz1TcpClientSocket					*sock;
	bool_t								 autoClose;
	Dz1TcpSocketReceiverInitFunc		 init;
	Dz1TcpSocketReceiverForwardFunc		 f;
	Dz1TcpSocketReceiverExceptionFunc	 e;
	Dz1TcpSocketReceiverTimeoutFunc		 to;
	Dz1DelFunc							 cleanup;
	void								*userResource;
} Dz1TcpSocketReceiver;

static Dz1TcpSocketReceiver *Dz1TcpSocketReceiver_new(Dz1TcpClientSocket **sock, bool_t autoClose,
														Dz1TcpSocketReceiverInitFunc init,
														Dz1TcpSocketReceiverForwardFunc f,
														Dz1TcpSocketReceiverExceptionFunc e,
														Dz1TcpSocketReceiverTimeoutFunc to,
														Dz1DelFunc cleanup,
														Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSocketReceiver *ret = NULL;
	if (sock == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (f == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpSocketReceiver *)Dz1Calloc(sizeof(Dz1TcpSocketReceiver), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		ret->sock = *sock;
		if ((ret->autoClose = autoClose) == TRUE) *sock = NULL;
		ret->init = init;
		ret->f = f;
		ret->e = e;
		ret->to = to;
		ret->cleanup = cleanup;
		ret->userResource = NULL;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1TcpSocketReceiver_del(Dz1TcpSocketReceiver *p)
{
	if (!p) return;
	if (p->autoClose && p->sock)
	{
		printf("Dz1TcpSocketReceiver_del() : Auto Close\n"); fflush(stdout);
		Dz1TcpClientSocket_close(p->sock);
	}
	Dz1Free(p);
}

typedef struct Dz1UdpSocketReceiver
{
	Dz1UdpSocket						*sock;
	bool_t								 autoClose;
	Dz1UdpSocketReceiverInitFunc		 init;
	Dz1UdpSocketReceiverForwardFunc		 f;
	Dz1UdpSocketReceiverExceptionFunc	 e;
	Dz1UdpSocketReceiverTimeoutFunc		 to;
	Dz1DelFunc							 cleanup;
	void								*userResource;
} Dz1UdpSocketReceiver;

static Dz1UdpSocketReceiver *Dz1UdpSocketReceiver_new(Dz1UdpSocket **sock, bool_t autoClose,
														Dz1UdpSocketReceiverInitFunc init,
														Dz1UdpSocketReceiverForwardFunc f,
														Dz1UdpSocketReceiverExceptionFunc e,
														Dz1UdpSocketReceiverTimeoutFunc to,
														Dz1DelFunc cleanup,
														Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UdpSocketReceiver *ret = NULL;
	if (sock == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (f == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1UdpSocketReceiver *)Dz1Calloc(sizeof(Dz1UdpSocketReceiver), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		ret->sock = *sock;
		if ((ret->autoClose = autoClose) == TRUE) *sock = NULL;
		ret->init = init;
		ret->f = f;
		ret->e = e;
		ret->to = to;
		ret->cleanup = cleanup;
		ret->userResource = NULL;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1UdpSocketReceiver_del(Dz1UdpSocketReceiver *p)
{
	if (!p) return;
	if (p->autoClose && p->sock)
	{
		printf("Dz1UdpSocketReceiver_del() : Auto Close\n"); fflush(stdout);
		Dz1UdpSocket_close(p->sock);
	}
	Dz1Free(p);
}

/*
typedef Dz1SocketReceierTimeoutBehavior (*Dz1UdpSocketReceiverTimeoutFunc)(void *userParam, Dz1UdpSocket *s);
typedef void (*Dz1UdpSocketReceiverForwardFunc)(void *userParam, Dz1UdpSocket *s, Dz1Socket *peer, u8_t *data, size_t size);
typedef void (*Dz1UdpSocketReceiverExceptionFunc)(void *userParam, Dz1UdpSocket *s, Dz1Error *reason);

typedef struct Dz1UdpSocketReceiver
{
	Dz1UdpSocket						*sock;
	Dz1UdpSocketReceiverForwardFunc		 f;
	Dz1UdpSocketReceiverExceptionFunc	 e;
	Dz1UdpSocketReceiverTimeoutFunc		 to;
} Dz1UdpSocketReceiver;
*/

typedef enum
{
	Dz1SocketReceiverPresent_tcp,
	Dz1SocketReceiverPresent_udp,
	Dz1SocketReceiverPresent_max
} Dz1SocketReceiverPresent;

typedef void (*Dz1SocketReceiverTermInformFunc)(void *userParam, Dz1Error *reason);

typedef struct Dz1SocketReceiver
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
	u8_t *buf;
	size_t bufSize;

	u32_t idleTime_ms;

	Dz1SocketReceiverPresent present;
	union
	{
		Dz1TcpSocketReceiver *tcpReceiver;
		Dz1UdpSocketReceiver *udpReceiver;
		void *ptr;
	} x;

	void *userParam;
	Dz1DelFunc userParamDel;
} Dz1SocketReceiver;

static void Dz1SocketReceiver_del(Dz1SocketReceiver *p)
{
	if (!p) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->buf) Dz1Free(p->buf);
	if (p->x.ptr)
	{
		switch(p->present)
		{
			case Dz1SocketReceiverPresent_tcp:
				Dz1TcpSocketReceiver_del(p->x.tcpReceiver);
				break;
			case Dz1SocketReceiverPresent_udp:
				Dz1UdpSocketReceiver_del(p->x.udpReceiver);
				break;
			default:
				break;
		}
	}
	if (p->userParam && p->userParamDel) p->userParamDel(p->userParam);

	Dz1Free(p);
}

static void Dz1SocketReceiver_delAndSetNull(void *ptr)
{
	Dz1SocketReceiver **p = (Dz1SocketReceiver **)ptr;
	Dz1SocketReceiver_del(*p); *p = NULL;
}

static Dz1SocketReceiver *Dz1SocketReceiver_newTcp(Dz1SockAddr *peer, Dz1SockAddr *local,
												size_t bufSize, u32_t idleTime_ms, Dz1TcpSocketReceiver *rcvr,
												void **userParam, Dz1DelFunc userParamDel, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketReceiver *ret = NULL;
	if (bufSize == 0) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1SocketReceiver *)Dz1Calloc(sizeof(Dz1SocketReceiver), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SocketReceiver_delAndSetNull, (void *)&ret);

		if ((ret->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->buf = (u8_t *)Dz1Malloc(bufSize, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->bufSize = bufSize;
			ret->idleTime_ms = idleTime_ms;
			ret->present = Dz1SocketReceiverPresent_tcp;
			ret->x.tcpReceiver = rcvr;
			if (userParam) ret->userParam = *userParam;
			if ((ret->userParamDel = userParamDel) != NULL) *userParam = NULL;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1SocketReceiver_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1SocketReceiver *Dz1SocketReceiver_newUdp(Dz1SockAddr *local, size_t bufSize, u32_t idleTime_ms, Dz1UdpSocketReceiver *rcvr,
													void **userParam, Dz1DelFunc userParamDel, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketReceiver *ret = NULL;
	if (bufSize == 0) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1SocketReceiver *)Dz1Calloc(sizeof(Dz1SocketReceiver), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SocketReceiver_delAndSetNull, (void *)&ret);

		if ((ret->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->buf = (u8_t *)Dz1Malloc(bufSize, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->bufSize = bufSize;
			ret->idleTime_ms = idleTime_ms;
			ret->present = Dz1SocketReceiverPresent_udp;
			ret->x.udpReceiver = rcvr;
			if (userParam) ret->userParam = *userParam;
			if ((ret->userParamDel = userParamDel) != NULL) *userParam = NULL;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1SocketReceiver_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void Dz1SocketReceiver_cleanupAndDel(void *ptr)
{
	Dz1SocketReceiver *p = (Dz1SocketReceiver *)ptr;
	Dz1SocketReceiver_del(p);
}

static void Dz1TcpSocketReceiver_userResourceClean(void *ptr)
{
	Dz1TcpSocketReceiver *p = (Dz1TcpSocketReceiver *)ptr;
	if (p->userResource && p->cleanup) p->cleanup(p->userResource);
	p->userResource = NULL;
}

static Dz1Error Dz1SocketReceiver_tcp(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpSocketReceiver *p, u8_t *buf, size_t size, u32_t idleTime_ms, void *userParam)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	int status;
	bool_t term = FALSE;
	struct timeval idleTime;
	struct timeval _wait, *wait = idleTime_ms ? &_wait : NULL;

	Dz1TcpClientSocket *s = p->sock;

	idleTime.tv_sec = idleTime_ms / 1000;
	idleTime.tv_usec = (idleTime_ms % 1000) * 1000;

	if (p->init && (err = p->init(&p->userResource, userParam, peer, local, s)).code) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketReceiver_userResourceClean, (void *)p);
		while(!term)
		{
			if (wait) *wait = idleTime;

			if ((status = s->wait(s, Dz1SocketWaitFlag_in, wait, &err)) < 0)
			{	// Socket Wait Error
				ERR_OUT(&err); term = TRUE;
				if (p->e) p->e(userParam, p->userResource, peer, local, s, &err);
			}
			else if (status == 0)
			{	// Socket Idle Timedout
				if (p->to != NULL && idleTime_ms > 0)
				{
					switch(p->to(userParam, p->userResource, peer, local, s, &err))
					{
						case Dz1SocketReceierBehavior_continue:
							break;
						case Dz1SocketReceierBehavior_term:
							term = TRUE;
							break;
						default:
							ERR_OUT(&err);
							if (p->e) p->e(userParam, p->userResource, peer, local, s, &err);
							term = TRUE;
							break;
					}
				}
			}
			else
			{	// Data Receive
				ssize_t recvByte = s->recv(s, buf, size, FALSE, NULL, &err);
				if (recvByte <= 0)
				{	// Socket Receive Error
					if (recvByte == 0) Dz1Error_set(&err, EPIPE);
					ERR_OUT(&err); term = TRUE;
					if (p->e) p->e(userParam, p->userResource, peer, local, s, &err);
				}
				else
				{
					switch(p->f(userParam, p->userResource, peer, local, s, buf, recvByte, &err))
					{
						case Dz1SocketReceierBehavior_continue:
							Dz1Error_set(&err, 0);
							break;
						case Dz1SocketReceierBehavior_term:
							term = TRUE;
							break;
						default:
							if (err.code == 0) ERR_SET_OUT(&err, EINVAL);

							if (p->e) p->e(userParam, p->userResource, peer, local, s, &err);
							term = TRUE;
							break;
					}
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1TcpSocketReceiver_userResourceClean, (void *)p);
	}
	return err;
}

static Dz1Error Dz1SocketReceiver_udp(Dz1UdpSocketReceiver *p, Dz1SockAddr *local, u8_t *buf, size_t size, u32_t idleTime_ms, void *userParam)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	int status;
	bool_t term = FALSE;
	struct timeval idleTime;
	struct timeval _wait, *wait = idleTime_ms ? &_wait : NULL;
	Dz1SockAddr peer;

	Dz1UdpSocket *s = p->sock;

	idleTime.tv_sec = idleTime_ms / 1000;
	idleTime.tv_usec = (idleTime_ms % 1000) * 1000;

	if (p->init && (err = p->init(&p->userResource, userParam, local, s)).code) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketReceiver_userResourceClean, (void *)p);
		while(!term)
		{
			if (wait) *wait = idleTime;

			pthread_testcancel();
			status = s->wait(s, Dz1SocketWaitFlag_in, wait, &err);
			pthread_testcancel();
			if (status < 0)
			{	// Socket Wait Error
				ERR_OUT(&err); term = TRUE;
				if (p->e) p->e(userParam, p->userResource, local, s, &err);
			}
			else if (status == 0)
			{	// Socket Idle Timeout
				if (p->to)
				{
					switch(p->to(userParam, p->userResource, local, s, &err))
					{
						case Dz1SocketReceierBehavior_continue:
							break;
						case Dz1SocketReceierBehavior_term:
							term = TRUE;
							break;
						default:
							ERR_OUT(&err);
							if (p->e) p->e(userParam, p->userResource, local, s, &err);
							term = TRUE;
							break;
					}
				}
			}
			else
			{	// Data Receive
				ssize_t recvByte;
				pthread_testcancel();
				recvByte = s->recv(s, &peer, buf, size, FALSE, NULL, &err);
				pthread_testcancel();
				if (recvByte < 0)
				{	// Socket Receive Error
#ifndef UNIX_SYSTEM
					if (err.code == WSAECONNRESET)
#endif
					Dz1Error_set(&err, 0);
				}
				else if (recvByte == 0)
				{
					if (recvByte == 0) Dz1Error_set(&err, EPIPE);
					ERR_OUT(&err); term = TRUE;
					if (p->e) p->e(userParam, p->userResource, local, s, &err);
				}
				else
				{
					switch(p->f(userParam, p->userResource, &peer, local, s, buf, recvByte, &err))
					{
						case Dz1SocketReceierBehavior_continue:
							Dz1Error_set(&err, 0);
							break;
						case Dz1SocketReceierBehavior_term:
							term = TRUE;
							break;
						default:
							if (err.code == 0) ERR_SET_OUT(&err, EINVAL);

							if (p->e) p->e(userParam, p->userResource, local, s, &err);
							term = TRUE;
							break;
					}
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1TcpSocketReceiver_userResourceClean, (void *)p);
	}
	return err;
}

static Dz1Error Dz1SocketReceiver_thread(void *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1SocketReceiver *param = (Dz1SocketReceiver *)arg;

	pthread_cleanup_push(Dz1SocketReceiver_cleanupAndDel, (void *)param);

	if (param->present == Dz1SocketReceiverPresent_tcp)
	{
		if ((err = Dz1SocketReceiver_tcp(param->peer, param->local, param->x.tcpReceiver,
								param->buf, param->bufSize, param->idleTime_ms, param->userParam)).code) ERR_OUT(&err);
	}
	else if (param->present == Dz1SocketReceiverPresent_udp)
	{
		if ((err = Dz1SocketReceiver_udp(param->x.udpReceiver, param->local, param->buf, param->bufSize, param->idleTime_ms, param->userParam)).code) ERR_OUT(&err);
	}
	else
	{
		ERR_SET_OUT(&err, EINVAL);
	}
	pthread_cleanup_pop(1); // (Dz1SocketReceiver_cleanupAndDel, (void *)param);

	return err;
}

int Dz1TcpSocketReceiver_start(Dz1SockAddr *peer, Dz1SockAddr *local,
								size_t bufSize, u32_t idleTime_ms,
								Dz1TcpClientSocket **sock, bool_t autoClose,
								Dz1TcpSocketReceiverInitFunc init,
								Dz1TcpSocketReceiverForwardFunc f,
								Dz1TcpSocketReceiverExceptionFunc e,
								Dz1TcpSocketReceiverTimeoutFunc to,
								Dz1CancelFunc cleanup,
								void **userParam, Dz1DelFunc userParamDel, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1SocketReceiver *param = Dz1SocketReceiver_newTcp(peer, local, bufSize, idleTime_ms, NULL, userParam, userParamDel, errp);
		if (param == NULL) { ERR_OUT(errp); }
		else
		{
			u32_t log_lv = 0;
			pthread_cleanup_push((Dz1CancelFunc)Dz1SocketReceiver_del, (void *)param);

			Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
			if ((param->x.tcpReceiver = Dz1TcpSocketReceiver_new(sock, autoClose, init, f, e, to, cleanup, errp)) == NULL) { ERR_OUT(errp); }
			else if ((*errp = Dz1Thread_create(&ret, Dz1SocketReceiver_thread, (void *)param, log_lv)).code) { ERR_OUT(errp); }
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)Dz1SocketReceiver_del, (void *)param);
		}
	}
	return ret;
}

int Dz1UdpSocketReceiver_start(Dz1SockAddr *local, size_t bufSize, u32_t idleTime_ms,
								Dz1UdpSocket **sock, bool_t autoClose,
								Dz1UdpSocketReceiverInitFunc init,
								Dz1UdpSocketReceiverForwardFunc f,
								Dz1UdpSocketReceiverExceptionFunc e,
								Dz1UdpSocketReceiverTimeoutFunc to,
								Dz1CancelFunc cleanup,
								void **userParam, Dz1DelFunc userParamDel, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1SocketReceiver *param = Dz1SocketReceiver_newUdp(local, bufSize, idleTime_ms, NULL, userParam, userParamDel, errp);
		if (param == NULL) { ERR_OUT(errp); }
		else
		{
			u32_t log_lv = 0;
			pthread_cleanup_push((Dz1CancelFunc)Dz1SocketReceiver_del, (void *)param);

			Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);

			if ((param->x.udpReceiver = Dz1UdpSocketReceiver_new(sock, autoClose, init, f, e, to, cleanup, errp)) == NULL) { ERR_OUT(errp); }
			else if ((*errp = Dz1Thread_create(&ret, Dz1SocketReceiver_thread, (void *)param, log_lv)).code) { ERR_OUT(errp); }
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)Dz1SocketReceiver_del, (void *)param);
		}
	}
	return ret;
}

Dz1Error Dz1SocketReceiver_stop(u32_t id)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((err = Dz1Thread_stop(id, FALSE)).code) { ERR_OUT(&err); }
	else Dz1Thread_usleep(100000);

	if ((err = Dz1Thread_wait(id, NULL)).code) { ERR_OUT(&err); }

	return err;
}


///////////////////////////////////////////////////////////////////////////////
// 
typedef struct Dz1UniSocketReceiver
{
	Dz1UniClientSocket				*sock;
	bool_t							 autoClose;

	Dz1SockAddr						*peer;
	Dz1SockAddr						*local;

	Dz1UniSocketReceiver_InitF		 init;
	Dz1UniSocketReceiver_fwdF		 f;
	Dz1UniSocketReceiver_errF		 e;
	Dz1UniSocketReceiver_tineoutF	 to;
	Dz1DelFunc						 cleanup;
	void							*uRsc;

	void							*uArg;
	Dz1DelFunc						 uArgDel;

	u8_t							*rx_buf;
	u32_t							 rx_buf_size;

	u32_t							 idle_time_ms;
} Dz1UniSocketReceiver;

static void Dz1UniSocketReceiver_del(Dz1UniSocketReceiver *p)
{
	if (p != NULL)
	{
		if (p->autoClose && p->sock)
		{
			printf("Dz1TcpSocketReceiver_del() : Auto Close\n"); fflush(stdout);
			Dz1UniClientSocket_close(p->sock);
			p->sock = NULL;
		}

		if (p->cleanup != NULL && p->uRsc != NULL) p->cleanup(p->uRsc);

		if (p->uArgDel != NULL && p->uArg != NULL) p->uArgDel(p->uArg);
		p->uArg = NULL;

		Dz1Free(p);
	}
}

static void Dz1UniSocketReceiver_delAndSetNull(void *pptr)
{
	Dz1UniSocketReceiver **p = (Dz1UniSocketReceiver **)pptr;
	Dz1UniSocketReceiver_del(*p);
	*p = NULL;
}

static Dz1UniSocketReceiver *Dz1UniSocketReceiver_new(Dz1UniClientSocket **sock, bool_t autoClose, 
													  Dz1SockAddr *peer, Dz1SockAddr *local,
													  u32_t rx_buf_size, u32_t idle_time_ms,
													  Dz1UniSocketReceiver_InitF init,
													  Dz1UniSocketReceiver_fwdF f,
													  Dz1UniSocketReceiver_errF e,
													  Dz1UniSocketReceiver_tineoutF to,
													  Dz1DelFunc cleanup, 
													  void **uArg, Dz1DelFunc uArgDel,
													  Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UniSocketReceiver *ret = NULL;
	if (sock == NULL || *sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (peer == NULL || local == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (f == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1UniSocketReceiver *)Dz1Calloc(sizeof(Dz1UniSocketReceiver), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1UniSocketReceiver_delAndSetNull, (void *)&ret);
		if (0) { }
		else if ((ret->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->rx_buf = (u8_t *)Dz1Malloc(rx_buf_size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->sock = *sock;
			if ((ret->autoClose = autoClose) == TRUE) *sock = NULL;

			ret->init = init;
			ret->f = f;

			ret->e = e;
			ret->to = to;

			ret->cleanup = cleanup;
			ret->uRsc = NULL;

			if (uArg != NULL) ret->uArg = *uArg;

			ret->uArgDel = uArgDel;
			if (uArgDel != NULL)
			{
				if (uArg != NULL) (*uArg) = NULL;
			}

			ret->idle_time_ms = idle_time_ms;
			ret->rx_buf_size = rx_buf_size;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1UniSocketReceiver_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void Dz1UniSocketReceiver_userResourceClean(void *ptr)
{
	Dz1UniSocketReceiver *p = (Dz1UniSocketReceiver *)ptr;
	if (p->uRsc != NULL && p->cleanup != NULL) p->cleanup(p->uRsc);
	p->uRsc = NULL;
}

static Dz1Error Dz1UniSocketReceiver_thread(void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1UniSocketReceiver *p = (Dz1UniSocketReceiver *)ptr;
	Dz1UniClientSocket *s = p->sock;
	struct timeval _wait, *wait = p->idle_time_ms ? &_wait : NULL;
	struct timeval idleTime = { (long)p->idle_time_ms / 1000, (long)(p->idle_time_ms % 1000) * 1000 };

	int status;
	bool_t term = FALSE;


	if (p->init && (err = p->init(&p->uRsc, p->uArg, p->peer, p->local, s)).code) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1UniSocketReceiver_userResourceClean, (void *)p);
		while(term == FALSE)
		{
			if (wait) *wait = idleTime;

			if ((status = s->wait(s, Dz1SocketWaitFlag_in, wait, errp)) < 0)
			{	// Socket Wait Error
				ERR_OUT(errp); term = TRUE;
				if (p->e) p->e(p->uArg, p->uRsc, p->peer, p->local, s, errp);
			}
			else if (status == 0)
			{	// Socket Idle Timedout
				if (p->to != NULL && p->idle_time_ms > 0)
				{
					switch(p->to(p->uArg, p->uRsc, p->peer, p->local, s, errp))
					{
						case Dz1SocketReceierBehavior_continue:
							break;
						case Dz1SocketReceierBehavior_term:
							term = TRUE;
							break;
						default:
							ERR_OUT(errp);
							if (p->e) p->e(p->uArg, p->uRsc, p->peer, p->local, s, errp);
							term = TRUE;
							break;
					}
				}
			}
			else
			{	// Data Receive
				ssize_t recvByte = s->recv(s, p->rx_buf, p->rx_buf_size, 0, NULL, errp);
				if (recvByte <= 0)
				{	// Socket Receive Error
					if (recvByte == 0) Dz1Error_set(errp, EPIPE);
					ERR_OUT(errp); term = TRUE;

					if (p->e) p->e(p->uArg, p->uRsc, p->peer, p->local, s, errp);
				}
				else
				{
					switch(p->f(p->uArg, p->uRsc, p->peer, p->local, s, p->rx_buf, recvByte, errp))
					{
						case Dz1SocketReceierBehavior_continue:
							Dz1Error_set(errp, 0);
							break;
						case Dz1SocketReceierBehavior_term:
							term = TRUE;
							break;
						default:
							if (errp->code == 0) ERR_SET_OUT(errp, EINVAL);

							if (p->e) p->e(p->uArg, p->uRsc, p->peer, p->local, s, errp);
							term = TRUE;
							break;
					}
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1UniSocketReceiver_userResourceClean, (void *)p);
	}
	return err;
}

int Dz1UniSocketReceiver_start(Dz1UniClientSocket **sock, bool_t autoClose,
							   Dz1SockAddr *peer, Dz1SockAddr *local,
							   size_t bufSize, u32_t idleTime_ms,
							   Dz1UniSocketReceiver_InitF init,
							   Dz1UniSocketReceiver_fwdF f,
							   Dz1UniSocketReceiver_errF e,
							   Dz1UniSocketReceiver_tineoutF to,
							   Dz1CancelFunc cleanup,
							   void **uArg, Dz1DelFunc uArgDel, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1UniSocketReceiver *param = Dz1UniSocketReceiver_new(sock, autoClose, peer, local, (u32_t)bufSize, idleTime_ms, init, f, e, to, cleanup, uArg, uArgDel, errp);
		if (param == NULL) { ERR_OUT(errp); }
		else
		{
			u32_t lv = 0;
			pthread_cleanup_push((Dz1CancelFunc)Dz1SocketReceiver_del, (void *)param);

			Dz1Thread_getLogLevel(Dz1Thread_self(), &lv);
			if ((*errp = Dz1Thread_create(&ret, Dz1UniSocketReceiver_thread, (void *)param, lv)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)Dz1SocketReceiver_del, (void *)param);
		}
	}
	return ret;
}

Dz1Error Dz1UniSocketReceiver_stop(u32_t id)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((*errp = Dz1Thread_stop(id, FALSE)).code) ERR_OUT(errp);
	else Dz1Thread_usleep(100000);

	if ((*errp = Dz1Thread_wait(id, NULL)).code) ERR_OUT(errp);

	return err;
}
