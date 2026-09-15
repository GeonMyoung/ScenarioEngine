#include <dz1_usleep.h>
#include <dz1_thread.h>
#include <dz1_thread_log.h>
#include <dz1_socket_connector.h>

Dz1TcpClientSocket *Dz1TcpSocketConnector_func(Dz1SockAddr *dst, Dz1SockAddr *local, u32_t period_sec, int retry, bool_t wait_and_connect, Dz1Error *err)
{
	Dz1TcpClientSocket *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u32_t wait_us = (u32_t)period_sec * 1000000;
	struct timeval _wait;
	if (period_sec == 0 || period_sec > 4000) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		if (wait_and_connect)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "Dz1TcpSocketConnector_func() : Wait First %d sec\n", period_sec);
			Dz1Thread_usleep(wait_us);
		}

		do
		{
			_wait.tv_sec = period_sec, _wait.tv_usec = 0;
			if ((ret = Dz1TcpClientSocket_open(dst, local, &_wait, errp)) == NULL)
			{
				if (errp->code == ETIMEDOUT)
				{
					Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "Dz1TcpSocketConnector_func() : retry(%d)\n", retry);
					continue;
				}
				else if (errp->code == ECONNREFUSED)
				{
					if (retry)
					{
						wait_us = _wait.tv_sec * 1000000 + _wait.tv_usec;
						Dz1Error_set(errp, 0);
						Dz1Thread_usleep(wait_us);
						Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "Dz1TcpSocketConnector_func() : retry(%d)\n", retry);
					}
				}
				else { /* ERR_OUT(errp);*/ break; }
			}
			else
			{
				Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "Dz1TcpSocketConnector_func() : Connected\n");
				Dz1Error_set(errp, 0);
				break;
			}
		} while(ret == NULL && (retry == -1 || retry--));
	}
	return ret;
}


typedef struct Dz1TcpSocketConnectorThreadArg
{
	Dz1SockAddr *dst;
	u32_t period_sec;
	int retry;
	bool_t wait_and_connect;
	Dz1TcpSocketConnectorCallback callback;
	void *callback_param;
} Dz1TcpSocketConnectorThreadArg;

static void Dz1TcpSocketConnectorThreadArg_del(Dz1TcpSocketConnectorThreadArg *p)
{
	if (p == NULL) return;
	if (p->dst) Dz1SockAddr_delAndSetNull(&p->dst);
	Dz1Free(p);
}

static void Dz1TcpSocketConnectorThreadArg_delAndSetNull(void *ptr)
{
	Dz1TcpSocketConnectorThreadArg **p = (Dz1TcpSocketConnectorThreadArg **)ptr;
	Dz1TcpSocketConnectorThreadArg_del(*p); *p = NULL;
}

static Dz1TcpSocketConnectorThreadArg *Dz1TcpSocketConnectorThreadArg_new(Dz1SockAddr *dst,
																		u32_t period_sec,
																		int retry,
																		bool_t wait_and_connect, 
																		Dz1TcpSocketConnectorCallback callback,
																		void *callback_param,
																		Dz1Error *errp)
{
	Dz1TcpSocketConnectorThreadArg *ret = NULL;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (period_sec == 0 || period_sec >= 1800) ERR_SET_OUT(errp, EINVAL);
	else if (callback == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TcpSocketConnectorThreadArg *)Dz1Calloc(sizeof(Dz1TcpSocketConnectorThreadArg), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketConnectorThreadArg_delAndSetNull, (void *)&ret);
		if ((ret->dst = Dz1SockAddr_clone(dst, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->period_sec = period_sec;
			ret->retry = retry;
			ret->wait_and_connect = wait_and_connect;
			ret->callback = callback;
			ret->callback_param = callback_param;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TcpSocketConnectorThreadArg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TcpSocketConnector_thread(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSocketConnectorThreadArg *arg = (Dz1TcpSocketConnectorThreadArg *)ptr;
	Dz1TcpClientSocket *sock = NULL;
	Dz1SockAddr local;

	pthread_cleanup_push(Dz1TcpSocketConnectorThreadArg_delAndSetNull, (void *)&arg);
	memset(&local, 0, sizeof(Dz1SockAddr));
	if ((sock = Dz1TcpSocketConnector_func(arg->dst, &local, arg->period_sec, arg->retry, arg->wait_and_connect, &err)) == NULL)
	{
		ERR_OUT(&err);
	}
	arg->callback(arg->callback_param, arg->dst, &local, &sock, &err);
	Dz1TcpClientSocket_closeAndSetNull(&sock);
	pthread_cleanup_pop(1); // (Dz1TcpSocketConnectorThreadArg_delAndSetNull, (void *)&arg);
	return err;
}

u32_t Dz1TcpSocketConnectorThread_create(Dz1SockAddr *dst,
										 u32_t period_sec, int retry, bool_t wait_and_connect,
										 Dz1TcpSocketConnectorCallback callback, void *callback_param,
										 u32_t thread_log_bits, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u32_t ret = -1;
	Dz1TcpSocketConnectorThreadArg *arg = Dz1TcpSocketConnectorThreadArg_new(dst, period_sec, retry, wait_and_connect, callback, callback_param, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketConnectorThreadArg_delAndSetNull, (void *)&arg);

		if ((*errp = Dz1Thread_create(&ret, _Dz1TcpSocketConnector_thread, (void *)arg, thread_log_bits)).code) ERR_OUT(errp);
		else arg = NULL;

		pthread_cleanup_pop(1); // (Dz1TcpSocketConnectorThreadArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

Dz1Error Dz1TcpSocketConnectorThread_join(u32_t id)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (id == (u32_t)-1) { }
	else if ((err = Dz1Thread_stop(id, FALSE)).code != 0 && err.code != ESRCH) ERR_OUT(&err);

	Dz1Thread_wait(id, &err);

	return err;
}