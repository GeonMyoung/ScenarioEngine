#include "dz1_socket.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1UniClientSocket
static int Dz1UniClientSocket_wait(Dz1UniClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err)
{
	return Dz1Socket_wait((Dz1Socket *)p->specific, flag, to, err);
}

ssize_t Dz1UniClientSocket_send(Dz1UniClientSocket *p, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
{
	ssize_t sendByte, ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u8_t *cp = data;
//	bool_t isUrgent = flag & DZ1_TCP_SOCK_FLAG_URGENT ? TRUE : FALSE;

	Dz1Error_set(errp, 0);
	do
	{
		if ((sendByte = Dz1Socket_send((Dz1Socket *)p->specific, NULL, cp, size, FALSE, to, errp)) <= 0)
		{
#ifdef WIN32
			if (errp->code == 10035)	// EWOUNDBLOCK
			{
				int status = 0;
				do 
				{
					if ((status = p->wait(p, Dz1SocketWaitFlag_out, NULL, errp)) == 0) break;
				} while(status < 0);
			}
			else
#endif
			{ 
				ERR_OUT(errp);
				break;
			}
		}
		else
		{
			cp += sendByte;
			size -= sendByte;
		}
	} while ((flag & DZ1_UNI_SOCK_FLAG_COMPLETE) && size);

	ret = errp->code == 0 ? (ssize_t)(cp - data) : -1;
	return ret;
}

static ssize_t Dz1UniClientSocket_recv(Dz1UniClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
{
	ssize_t recvByte = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u8_t *cp = buf;

	Dz1Error_set(errp, 0);
	do
	{
		if ((recvByte = Dz1Socket_recv((Dz1Socket *)p->specific, NULL, cp, size, errp)) <= 0)
		{
			ERR_OUT(errp);
			break;
		}
		else { cp += recvByte; size -= recvByte; }
	} while ((flag & DZ1_UNI_SOCK_FLAG_COMPLETE) && size);

	return (ssize_t)(cp - buf);
}

static SOCKET Dz1UniClientSocket_getOSHandle(Dz1UniClientSocket *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SOCKET ret = INVALID_SOCKET;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->specific == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1Socket *s = (Dz1Socket *)p->specific;
		ret = s->fd;
	}
	return ret;
}

Dz1UniClientSocket *_Dz1UniClientSocket_open(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UniSocketType type, struct timeval *to, Dz1Error *err, const char *__file__, int __line__)
{
	Dz1UniClientSocket *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (peer == NULL || local == NULL) Dz1Error_set(errp, EINVAL);
	else if ((ret = (Dz1UniClientSocket *)_Dz1Calloc(sizeof(Dz1UniClientSocket), 1, errp, __file__, __line__)) == NULL) { ERR_OUT(errp); }
	else
	{
		Dz1SockAddr temp;

//		u32_t localIP = 0;
//		size_t localIPSize = sizeof(u32_t);
//		u16_t tempPort = 0;

		pthread_cleanup_push(Dz1UniClientSocket_closeAndSetNull, (void *)&ret);

		memset(&temp, 0, sizeof(Dz1SockAddr));

		ret->specific_del = (Dz1DelFunc)Dz1Socket_close;
		if ((ret->specific = _Dz1Socket_open(local, type, 0, NULL, errp, __file__, __line__)) == NULL) { ERR_OUT(errp); }
		else if ((*errp = Dz1Socket_connect((Dz1Socket *)ret->specific, peer, to)).code) { ERR_OUT(errp); }
		else if ((*errp = Dz1Socket_getLocalAddr((Dz1Socket *)ret->specific, &temp)).code) { ERR_OUT(errp); }
		else if (Dz1SockAddr_isValid(&temp) == FALSE) Dz1Error_set(errp, ECONNREFUSED);
		else
		{
			memcpy(local, &temp, sizeof(Dz1SockAddr));

			ret->wait = Dz1UniClientSocket_wait;
			ret->send = Dz1UniClientSocket_send;
			ret->recv = Dz1UniClientSocket_recv;
			ret->getOSHandle = Dz1UniClientSocket_getOSHandle;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1UniClientSocket_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1UniClientSocket_close(Dz1UniClientSocket *p)
{
	if (!p) return;
	if (p->specific_del && p->specific)
	{
		p->specific_del(p->specific);
		p->specific = NULL;
	}
	Dz1Free(p);
}

Dz1UniClientSocket *Dz1UniClientSocket_encapsulation(void **specific, Dz1DelFunc specific_del,
													 Dz1UniClientSocket_waitF wait_f,
													 Dz1UniClientSocket_sendF send_f,
													 Dz1UniClientSocket_recvF recv_f,
													 Dz1UniClientSocket_getfdF getfd_f,
													 Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UniClientSocket *ret = (Dz1UniClientSocket *)Dz1Calloc(sizeof(Dz1UniClientSocket), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1UniClientSocket_closeAndSetNull, (void *)&ret);

		if (specific) ret->specific = (*specific);
		ret->specific_del = specific_del;
		if (specific_del && specific) *specific = NULL;

		ret->wait = wait_f;
		ret->send = send_f;
		ret->recv = recv_f;
		ret->getOSHandle = getfd_f;

		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1UniClientSocket_closeAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1UniClientSocket
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1UniServerSocket
static int Dz1UniServerSocket_wait(Dz1UniServerSocket *p, struct timeval *to, Dz1Error *err)
{
	return Dz1Socket_wait((Dz1Socket *)p->specific, Dz1SocketWaitFlag_in, to, err);
}

static Dz1UniClientSocket *Dz1UniServerSocket_accept(Dz1UniServerSocket *p, Dz1SockAddr *local, Dz1SockAddr *peer, struct timeval *to, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1UniClientSocket *ret = (Dz1UniClientSocket *)Dz1Calloc(sizeof(Dz1UniClientSocket), 1, errp);
	if (ret == NULL) { Dz1Error_set(errp, ENOMEM); }
	else
	{
		int status = 0;
		pthread_cleanup_push(Dz1UniClientSocket_closeAndSetNull, (void *)&ret);

		if ((status = Dz1Socket_wait((Dz1Socket *)p->specific, Dz1SocketWaitFlag_in, to, errp)) <= 0) { ERR_OUT(errp); }
		else if ((ret->specific = Dz1Socket_accept((Dz1Socket *)p->specific, local, peer, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->specific_del = (Dz1DelFunc)Dz1Socket_close;
			ret->wait = Dz1UniClientSocket_wait;
			ret->send = Dz1UniClientSocket_send;
			ret->recv = Dz1UniClientSocket_recv;
			ret->getOSHandle = Dz1UniClientSocket_getOSHandle;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1UniClientSocket_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1UniServerSocket *_Dz1UniServerSocket_open(Dz1SockAddr *local, u16_t *o_port, Dz1UniSocketType type, int backlog, Dz1Error *err, const char *__file__, int __line__)
{
	Dz1UniServerSocket *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!local) Dz1Error_set(errp, EINVAL);
	else if (type == Dz1UniSocketType_raw) ERR_SET_OUT(errp, EPERM);
	else if ((ret = (Dz1UniServerSocket *)_Dz1Calloc(sizeof(Dz1UniServerSocket), 1,errp, __file__, __line__)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1UniServerSocket_closeAndSetNull, (void *)&ret);

		if ((ret->specific = _Dz1Socket_open(local, type, 0, o_port, errp, __file__, __line__)) == NULL) { ERR_OUT(errp); }
		else if (type == Dz1UniSocketType_stream && (*errp = Dz1Socket_listen((Dz1Socket *)ret->specific, backlog)).code) { ERR_OUT(errp); }
		else
		{
			ret->wait = Dz1UniServerSocket_wait;
			ret->accept = Dz1UniServerSocket_accept;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1UniServerSocket_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1UniServerSocket_close(Dz1UniServerSocket *p)
{
	if (!p) return;
	if (p->specific) Dz1Socket_close((Dz1Socket *)p->specific);
	Dz1Free(p);
}
// Dz1UniServerSocket
///////////////////////////////////////////////////////////////////////////////
