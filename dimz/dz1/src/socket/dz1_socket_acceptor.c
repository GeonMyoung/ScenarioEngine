#include <dz1_thread.h>
#include <dz1_malloc.h>
#include <dz1_usleep.h>
#include <dz1_socket_acceptor.h>

typedef struct Dz1TcpSocketAcceptor
{
	Dz1TcpServerSocket *sock;
	bool_t autoClose;
	u32_t idleTime_ms;
	u32_t acceptTime_ms;

	Dz1TcpSocketAcceptorInitFunc init;
	Dz1TcpSocketAcceptorExceptionFunc e;
	Dz1TcpSocketAcceptorTimeoutFunc to;
	Dz1TcpSocketAcceptorForwardFunc f;
	Dz1CancelFunc cleanup;

	void *userResource;

	void *userParam;
	Dz1CancelFunc userParamDel;
} Dz1TcpSocketAcceptor;

static Dz1TcpSocketAcceptor *Dz1TcpSocketAcceptor_new(Dz1TcpServerSocket *sock, bool_t autoClose,
													  u32_t idleTime_ms, u32_t acceptTime_ms,
														Dz1TcpSocketAcceptorInitFunc init,
														Dz1TcpSocketAcceptorForwardFunc f,
														Dz1TcpSocketAcceptorExceptionFunc e,
														Dz1TcpSocketAcceptorTimeoutFunc to,
														Dz1CancelFunc cleanup,
														void *userParam,
														Dz1CancelFunc userParamDel,
														Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSocketAcceptor *ret = NULL;
	if (sock == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (f == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpSocketAcceptor *)Dz1Calloc(sizeof(Dz1TcpSocketAcceptor), 1, errp)) ==NULL) { ERR_OUT(errp); }
	else
	{
		ret->sock = sock;
		ret->autoClose = autoClose;
		ret->idleTime_ms = idleTime_ms;
		ret->acceptTime_ms = acceptTime_ms;
		ret->init = init;
		ret->f = f;
		ret->e = e;
		ret->to = to;
		ret->cleanup = cleanup;
		ret->userParam = userParam;
		ret->userParamDel = userParamDel;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1TcpSocketAcceptor_del(Dz1TcpSocketAcceptor *p)
{
	if (!p) return;
	if (p->autoClose) Dz1TcpServerSocket_close(p->sock);
	Dz1Free(p);
}

static void Dz1TcpSocketAcceptor_cleanupAndDel(void *ptr)
{
	Dz1TcpSocketAcceptor *p = (Dz1TcpSocketAcceptor *)ptr;
	if (p->cleanup) p->cleanup(p->userResource);
	if (p->userParamDel) p->userParamDel(p->userParam);
	Dz1TcpSocketAcceptor_del(p);
}

static Dz1Error Dz1TcpSocketAcceptor_thread(void *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1TcpSocketAcceptor *p = (Dz1TcpSocketAcceptor *)arg;
	Dz1TcpServerSocket *s = p->sock;

	int status;
	bool_t term = FALSE;

	struct timeval idleTime, acceptTime;
	struct timeval _wait, *wait = p->idleTime_ms ? &_wait : NULL;
	struct timeval _acceptWait, *acceptWait = p->acceptTime_ms ? &_acceptWait : NULL;

	idleTime.tv_sec = p->idleTime_ms / 1000;
	idleTime.tv_usec = (p->idleTime_ms % 1000) * 1000;

	acceptTime.tv_sec = p->acceptTime_ms / 1000;
	acceptTime.tv_usec = (p->acceptTime_ms % 1000) * 1000;

	pthread_cleanup_push((Dz1CancelFunc)Dz1TcpSocketAcceptor_cleanupAndDel, (void *)p);

	if (p->init != NULL && (err = p->init(&p->userResource, p->userParam, s)).code) ERR_OUT(&err);
	else
	{
		while(!term)
		{
			if (wait) *wait = idleTime;

			if ((status = s->wait(s, wait, &err)) < 0)
			{
				ERR_OUT(&err); term = TRUE;
				if (p->e) p->e(p->userParam, p->userResource, s, &err);
			}
			else if (status == 0)
			{	// timeout
				if (p->to)
				{
					switch(p->to(p->userParam, p->userResource, s))
					{
						case Dz1TcpSocketAcceptorBehavior_continue:
							break;
						case Dz1TcpSocketAcceptorBehavior_term:
							term = TRUE;
							break;
						default:
							ERR_SET_OUT(&err, EINVAL);
							if (p->e) p->e(p->userParam, p->userResource, s, &err);
							term = TRUE;
							break;
					}
				}
				else continue;
			}
			else
			{	// connected -> forward
				Dz1SockAddr local, peer;
				Dz1TcpClientSocket *sock = NULL;
				
				if (acceptWait) *acceptWait = acceptTime;
				sock = s->accept(s, &local, &peer, acceptWait, &err);
				pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&sock);

				if (sock == NULL)
				{
					if (err.code != EAGAIN)
					{
						ERR_OUT(&err); term = TRUE;
						if (p->e) p->e(p->userParam, p->userResource, s, &err);
					}
					else Dz1Error_set(&err, 0);
				}
				else
				{
					switch(p->f(p->userParam, p->userResource, &sock, &local, &peer, &err))
					{
						case Dz1TcpSocketAcceptorBehavior_continue:
							Dz1Error_set(&err, 0);
							break;
						case Dz1TcpSocketAcceptorBehavior_term:
							if (p->e) p->e(p->userParam, p->userResource, s, &err);
							term = TRUE;
							break;
						default:
							ERR_SET_OUT(&err, EINVAL);
							if (p->e) p->e(p->userParam, p->userResource, s, &err);
							term = TRUE;
							break;
					}
				}
				pthread_cleanup_pop(1); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&sock);
			}
		}
	}
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1TcpSocketAcceptor_cleanupAndDel, (void *)p);

	return err;
}

u32_t Dz1TcpSocketAcceptor_start(Dz1TcpServerSocket *sock, bool_t autoClose,
								 u32_t idleTime_ms, u32_t acceptTime_ms,
								 Dz1TcpSocketAcceptorInitFunc init,
								 Dz1TcpSocketAcceptorForwardFunc f,
								 Dz1TcpSocketAcceptorExceptionFunc e,
								 Dz1TcpSocketAcceptorTimeoutFunc to,
								 Dz1CancelFunc cleanup,
								 void **userParam,
								 Dz1DelFunc userParamDel,
								 Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	void *uParam = userParam == NULL ? NULL : (*userParam);
	Dz1TcpSocketAcceptor *param = Dz1TcpSocketAcceptor_new(sock, autoClose,
															idleTime_ms, acceptTime_ms,
															init, f, e, to, cleanup,
															uParam, userParamDel, errp);
	if (param == NULL) { ERR_OUT(errp); }
	else
	{
		u32_t log_lv = 0;
		pthread_cleanup_push((Dz1CancelFunc)Dz1TcpSocketAcceptor_del, (void *)param);

		if (userParam != NULL && userParamDel != NULL) (*userParam) = NULL;

		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
		if ((*errp = Dz1Thread_create(&ret, Dz1TcpSocketAcceptor_thread, (void *)param, log_lv)).code) { ERR_OUT(errp); }
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)Dz1TcpSocketAcceptor_del, (void *)param);
	}
	return ret;
}

Dz1Error Dz1TcpSocketAcceptor_stop(u32_t id)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((err = Dz1Thread_stop(id, FALSE)).code) { ERR_OUT(&err); }
	else Dz1Thread_usleep(100000);

	if ((err = Dz1Thread_wait(id, NULL)).code) { ERR_OUT(&err); }

	return err;
}



///////////////////////////////////////////////////////////////////////////////
// Dz1UniSocketAcceptor
typedef struct Dz1UniSocketAcceptor
{
	Dz1UniServerSocket				*sock;
	bool_t							 autoClose;

	Dz1SockAddr						*local;

	u32_t							 idleTime_ms;
	u32_t							 acceptTime_ms;

	Dz1UniSocketAcceptor_initF		 init;
	Dz1UniSocketAcceptor_fwdF		 f;
	Dz1UniSocketAcceptor_timeoutF	 to;
	Dz1UniSocketAcceptor_errF		 e;
	Dz1CancelFunc					 cleanup;

	void							*uRsc;

	void							*uArg;
	Dz1CancelFunc					 uArgDel;
} Dz1UniSocketAcceptor;

static void Dz1UniSocketAcceptor_del(Dz1UniSocketAcceptor *p)
{
	if (!p) return;
	if (p->autoClose) Dz1UniServerSocket_close(p->sock);
	Dz1Free(p);
}

static void Dz1UniSocketAcceptor_delAndSetNull(void *pptr)
{
	Dz1UniSocketAcceptor **p = (Dz1UniSocketAcceptor **)pptr;
	Dz1UniSocketAcceptor_del(*p);
	*p = NULL;
}

static Dz1UniSocketAcceptor *Dz1UniSocketAcceptor_new(Dz1UniServerSocket **sock, bool_t autoClose,
													  Dz1SockAddr *local,
													  u32_t idleTime_ms, u32_t acceptTime_ms,
													  Dz1UniSocketAcceptor_initF init,
													  Dz1UniSocketAcceptor_fwdF f,
													  Dz1UniSocketAcceptor_timeoutF to,
													  Dz1UniSocketAcceptor_errF e,
													  Dz1CancelFunc cleanup,
													  void **uArg, Dz1CancelFunc uArgDel, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UniSocketAcceptor *ret = NULL;
	if (sock == NULL || *sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (f == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1UniSocketAcceptor *)Dz1Calloc(sizeof(Dz1UniSocketAcceptor), 1, errp)) ==NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1UniSocketAcceptor_delAndSetNull, (void *)&ret);
		if ((ret->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->sock = (*sock);
			ret->autoClose = autoClose;
			if (ret->autoClose) (*sock) = NULL;

			ret->idleTime_ms = idleTime_ms;
			ret->acceptTime_ms = acceptTime_ms;

			ret->init = init;
			ret->f = f;
			ret->to = to;
			ret->e = e;

			ret->cleanup = cleanup;

			if (uArg != NULL) ret->uArg = (*uArg);

			ret->uArgDel = uArgDel;
			if (uArgDel != NULL) 
			{
				if (uArg != NULL) (*uArg) = NULL;
			}

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1UniSocketAcceptor_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void Dz1UniSocketAcceptor_cleanupAndDel(void *ptr)
{
	Dz1UniSocketAcceptor *p = (Dz1UniSocketAcceptor *)ptr;
	if (p->cleanup != NULL && p->uRsc != NULL) p->cleanup(p->uRsc);
	if (p->uArgDel != NULL && p->uArg != NULL) p->uArgDel(p->uArg);
	Dz1SockAddr_delAndSetNull(&p->local);
	Dz1UniSocketAcceptor_del(p);
}


static Dz1Error Dz1UniSocketAcceptor_thread(void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1UniSocketAcceptor *p = (Dz1UniSocketAcceptor *)arg;
	Dz1UniServerSocket *s = p->sock;

	int status;
	bool_t term = FALSE;

	struct timeval idleTime, acceptTime;
	struct timeval _wait,		*wait		= p->idleTime_ms > 0	? &_wait : NULL;
	struct timeval _acceptWait, *acceptWait = p->acceptTime_ms > 0	? &_acceptWait : NULL;

	idleTime.tv_sec = p->idleTime_ms / 1000;
	idleTime.tv_usec = (p->idleTime_ms % 1000) * 1000;

	acceptTime.tv_sec = p->acceptTime_ms / 1000;
	acceptTime.tv_usec = (p->acceptTime_ms % 1000) * 1000;

	pthread_cleanup_push((Dz1CancelFunc)Dz1UniSocketAcceptor_cleanupAndDel, (void *)p);

	if (p->init != NULL && (*errp = p->init(&p->uRsc, p->uArg, p->local, s)).code) ERR_OUT(errp);
	else
	{
		while(!term)
		{
			if (wait) *wait = idleTime;

			if ((status = s->wait(s, wait, errp)) < 0)
			{
				ERR_OUT(errp); term = TRUE;
				if (p->e) p->e(p->uArg, p->uRsc, s, errp);
			}
			else if (status == 0)
			{	// timeout
				if (p->to)
				{
					switch(p->to(p->uArg, p->uRsc, s))
					{
						case Dz1TcpSocketAcceptorBehavior_continue:
							break;
						case Dz1TcpSocketAcceptorBehavior_term:
							term = TRUE;
							break;
						default:
							ERR_SET_OUT(errp, EINVAL);
							if (p->e) p->e(p->uArg, p->uRsc, s, errp);
							term = TRUE;
							break;
					}
				}
				else continue;
			}
			else
			{	// connected -> forward
				Dz1SockAddr local, peer;
				Dz1UniClientSocket *sock = NULL;
				
				if (acceptWait) *acceptWait = acceptTime;
				sock = s->accept(s, &local, &peer, acceptWait, errp);
				pthread_cleanup_push(Dz1UniClientSocket_closeAndSetNull, (void *)&sock);

				if (sock == NULL)
				{
					if (errp->code != EAGAIN)
					{
						ERR_OUT(errp); term = TRUE;
						if (p->e) p->e(p->uArg, p->uRsc, s, errp);
					}
					else Dz1Error_set(errp, 0);
				}
				else
				{
					switch(p->f(p->uArg, p->uRsc, &sock, &local, &peer, errp))
					{
						case Dz1TcpSocketAcceptorBehavior_continue:
							Dz1Error_set(errp, 0);
							break;
						case Dz1TcpSocketAcceptorBehavior_term:
							if (p->e) p->e(p->uArg, p->uRsc, s, errp);
							term = TRUE;
							break;
						default:
							ERR_SET_OUT(errp, EINVAL);
							if (p->e) p->e(p->uArg, p->uRsc, s, errp);
							term = TRUE;
							break;
					}
				}
				pthread_cleanup_pop(1); // (Dz1UniClientSocket_closeAndSetNull, (void *)&sock);
			}
		}
	}
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1TcpSocketAcceptor_cleanupAndDel, (void *)p);

	return err;
}

u32_t Dz1UniSocketAcceptor_start(Dz1UniServerSocket **sock, bool_t autoClose, Dz1SockAddr *local, 
								 u32_t idleTime_ms, u32_t acceptTime_ms,
								 Dz1UniSocketAcceptor_initF		 init,
								 Dz1UniSocketAcceptor_fwdF		 f,
								 Dz1UniSocketAcceptor_errF		 e,
								 Dz1UniSocketAcceptor_timeoutF	 to,
								 Dz1CancelFunc cleanup,
								 void **uArg, Dz1CancelFunc uArgDel, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UniSocketAcceptor *param = Dz1UniSocketAcceptor_new(sock, autoClose, local, idleTime_ms, acceptTime_ms, init, f, to, e, cleanup, uArg, uArgDel, errp);
	if (param == NULL) { ERR_OUT(errp); }
	else
	{
		u32_t lv = 0;
		pthread_cleanup_push((Dz1CancelFunc)Dz1UniSocketAcceptor_del, (void *)param);

		Dz1Thread_getLogLevel(Dz1Thread_self(), &lv);

		if ((*errp = Dz1Thread_create(&ret, Dz1UniSocketAcceptor_thread, (void *)param, lv)).code) { ERR_OUT(errp); }
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)Dz1UniSocketAcceptor_del, (void *)param);
	}
	return ret;
}

Dz1Error Dz1UniSocketAcceptor_stop(u32_t id)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((*errp = Dz1Thread_stop(id, FALSE)).code) ERR_OUT(errp);
	else Dz1Thread_usleep(100000);

	if ((*errp = Dz1Thread_wait(id, NULL)).code) ERR_OUT(errp);

	return err;
}
