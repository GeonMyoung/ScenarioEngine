#include "dz1_socket.h"
#include <fcntl.h>
#include <dz1_malloc.h>
#include <dz1_usleep.h>
#ifdef UNIX_SYSTEM
#include <netinet/tcp.h>
#endif

#ifdef __BORLANDC__
#pragma warn -8012
#endif

bool_t Dz1Socket_init(void)
{
#ifndef UNIX_SYSTEM
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD( 2, 2 );

    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        return FALSE;
    }

    /* Confirm that the WinSock DLL supports 2.2.*/
    /* Note that if the DLL supports versions greater    */
    /* than 2.2 in addition to 2.2, it will still return */
    /* 2.2 in wVersion since that is the version we      */
    /* requested.                                        */

    if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
    {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        WSACleanup();
        return FALSE;
    }
#endif
    /* The WinSock DLL is acceptable. Proceed. */
    return TRUE;
}

void Dz1Socket_cleanup(void)
{
#ifndef UNIX_SYSTEM
	WSACleanup( );
#endif
}

#ifndef UNIX_SYSTEM
// http://msdn.microsoft.com/en-us/library/ms740668(VS.85).aspx
static int _ConvWsaError2Errno(int wserr)
{
	switch(wserr)
	{
	case WSANOTINITIALISED:
		return EFAULT;
	case WSAEAFNOSUPPORT:
		return ESRCH;
	case WSAECONNABORTED:
		return EINTR;
	case WSAETIMEDOUT:
		return EAGAIN;
	default:
		return wserr;
	}
}
#endif

int _GetSockError(void)
{
#ifndef UNIX_SYSTEM
	int wserr = WSAGetLastError();
	return _ConvWsaError2Errno(wserr);
#else
	return errno;
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Socket Version
///////////////////////////////////////////////////////////////////////////////
static socklen_t __Dz1SocketSize__[Dz1SocketVer_max] =
{
#ifdef UNIX_SYSTEM
	sizeof(struct sockaddr_in),
	sizeof(struct sockaddr_in6)
#else
#ifdef DIMZ_SUPPORT_IPV6
	sizeof(struct sockaddr_in),
	sizeof(struct sockaddr_in6)
#else
	sizeof(struct sockaddr_in)
#endif
#endif
};

static int Dz1SocketVer2Domain(Dz1SocketVer ver, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	int ret = -1;
	Dz1Error_set(errp, 0);
	switch(ver)
	{
		default:
			Dz1Error_set(errp, ESRCH);
			break;
		case Dz1SocketVer_inet4:
			ret = AF_INET;
			break;
#ifdef DIMZ_SUPPORT_IPV6
		case Dz1SocketVer_inet6:
			ret = AF_INET6;
			break;
#endif
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1Socket
///////////////////////////////////////////////////////////////////////////////
// static void Dz1SockAddrFromSockAddr(Dz1SockAddr *dst, struct sockaddr_in *src, socklen_t src_size)
// {
// 	memcpy(dst->x.ptr, src, src_size);
// 	if (src->sin_family == AF_INET) dst->ver = Dz1SocketVer_inet4;
// #ifdef DIMZ_SUPPORT_IPV6
// 	else if (src->sin_family == AF_INET6) dst->ver = Dz1SocketVer_inet6;
// #endif
// 	else dst->ver = Dz1SocketVer_max;
// }

Dz1Error Dz1Socket_getLocalAddr(Dz1Socket *p, Dz1SockAddr *local)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (local == NULL) Dz1Error_set(&err, EINVAL);
	else
	{
#ifdef DIMZ_SUPPORT_IPV6
		socklen_t addr_len = sizeof(struct sockaddr_in6);
#else
		socklen_t addr_len = sizeof(struct sockaddr_in);
#endif

		if (getsockname(p->fd, (struct sockaddr *)local->x.ptr, &addr_len) < 0) Dz1Error_set(&err, _GetSockError());
		else if (addr_len == sizeof(struct sockaddr_in)) local->ver = Dz1SocketVer_inet4;
#ifdef DIMZ_SUPPORT_IPV6
		else if (addr_len == sizeof(struct sockaddr_in6)) local->ver = Dz1SocketVer_inet6;
#endif
		else Dz1Error_set(errp, EFAULT);
	}
	return err;
}

static Dz1Error Dz1Socket_nonblock(Dz1Socket *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
#ifndef UNIX_SYSTEM
    int iMode = 1;
    if (ioctlsocket(p->fd, FIONBIO, (u_long FAR*) &iMode) != 0) Dz1Error_set(&err, WSAGetLastError());
#else
	int flag;
	if ((flag = fcntl(p->fd, F_GETFL)) < 0) { Dz1Error_set(&err, errno); }
	else if (fcntl(p->fd, F_SETFL, flag | O_NONBLOCK) < 0) { Dz1Error_set(&err, errno); }
#endif
	return err;
}

static Dz1Error Dz1Socket_reuse(Dz1Socket *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int value = 1;
	if (setsockopt(p->fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&value, sizeof(int))) { Dz1Error_set(&err, _GetSockError()); }
	return err;
}

static Dz1Error Dz1Socket_bind(Dz1Socket *p, int srcDomain, Dz1SockAddr *local, int type, u16_t *o_port)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	in_port_t _o_port, *o_portp = o_port ? o_port : &_o_port;

	if (!Dz1SocketVerIsValid(local->ver)) { Dz1Error_set(&err, EINVAL); }
	else if (type == SOCK_STREAM || type == SOCK_DGRAM)
	{
		Dz1SockAddr temp;
		struct sockaddr_in *in_addr = (struct sockaddr_in *)local->x.ptr;
		in_addr->sin_family = srcDomain;

		if (bind(p->fd, (struct sockaddr *)local->x.ptr, __Dz1SocketSize__[local->ver]) < 0) { Dz1Error_set(&err, _GetSockError()); }
		else if ((err = Dz1Socket_getLocalAddr(p, &temp)).code) { ERR_OUT(&err); }
		else if ((err = Dz1SockAddr_getPort(&temp, o_portp)).code) { ERR_OUT(&err); }
	}
	else *o_portp = 0;

	return err;
}

Dz1Error Dz1Socket_listen(Dz1Socket *p, int backlog)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (listen(p->fd, backlog) < 0) { Dz1Error_set(&err, _GetSockError()); }
	return err;
}

void Dz1Socket_close(Dz1Socket *p)
{
	if (!p) return;
	if (p->fd != fileno(stdin) && p->fd != fileno(stdout) && p->fd != fileno(stderr))
#ifndef UNIX_SYSTEM
		closesocket(p->fd);
#else
	{
		fsync(p->fd);
		close(p->fd);
	}
#endif
	Dz1Free(p);
}

static void Dz1Socket_closeAndSetNull(void *ptr)
{
	Dz1Socket **p = (Dz1Socket **)ptr;
	Dz1Socket_close(*p); *p = NULL;
}

Dz1Socket *_Dz1Socket_open(Dz1SockAddr *local, int type, int protocol, in_port_t *o_port, Dz1Error *err, const char *__file__, int __line__)
{
	Dz1Socket *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!local) { Dz1Error_set(errp, EINVAL); }
	else if ((ret = (Dz1Socket *)_Dz1Calloc(sizeof(Dz1Socket), 1, errp, __file__, __line__)) == NULL) { ERR_OUT(errp); }
	else
	{
		int domain = Dz1SocketVer2Domain(local->ver, errp);

		pthread_cleanup_push(Dz1Socket_closeAndSetNull, (void *)&ret);

		if (domain < 0) { ERR_OUT(errp); }
		else
		{
			if ((ret->fd = socket(domain, type, protocol)) == INVALID_SOCKET)
			{
				Dz1Error_set(errp, _GetSockError());
			}
			else if ((*errp = Dz1Socket_nonblock(ret)).code) { ERR_OUT(errp); }
			else if ((*errp = Dz1Socket_reuse(ret)).code) { ERR_OUT(errp); }
			else if ((*errp = Dz1Socket_bind(ret, domain, local, type, o_port)).code) { ERR_OUT(errp); }
			else
			{
				Dz1Error_set(errp, 0);
				if (type == SOCK_STREAM)
				{
					int value = 1;
					if (setsockopt(ret->fd, IPPROTO_TCP, TCP_NODELAY, (const char *)&value, sizeof(int)))
					{
						Dz1Error_set(errp, _GetSockError());
					}
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Socket_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Socket *Dz1Socket_accept(Dz1Socket *p, Dz1SockAddr *local, Dz1SockAddr *peer, Dz1Error *err)
{
	Dz1Socket *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SockAddr _peer, *peerp = peer ? peer : &_peer;
	Dz1SockAddr _local, *localp = local ? local : &_local;
	if ((ret = (Dz1Socket *)Dz1Calloc(sizeof(Dz1Socket), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
#ifdef DIMZ_SUPPORT_IPV6
		socklen_t addr_len = sizeof(struct sockaddr_in6);
#else
		socklen_t addr_len = sizeof(struct sockaddr_in);
#endif

		pthread_cleanup_push(Dz1Socket_closeAndSetNull, (void *)&ret);

		if ((ret->fd = accept(p->fd, (struct sockaddr *)peerp->x.ptr, &addr_len)) == INVALID_SOCKET) { Dz1Error_set(errp, _GetSockError()); }
		else if ((*errp = Dz1Socket_nonblock(ret)).code) { ERR_OUT(errp); }
		else if ((*errp = Dz1Socket_getLocalAddr(ret, localp)).code) { ERR_OUT(errp); }
		else
		{
//			Dz1SockAddrFromSockAddr(peerp, (struct sockaddr_in *)&addr, addr_len);
			if (addr_len == sizeof(struct sockaddr_in)) peerp->ver = Dz1SocketVer_inet4;
#ifdef DIMZ_SUPPORT_IPV6
			else if (addr_len == sizeof(struct sockaddr_in6)) peerp->ver = Dz1SocketVer_inet6;
#endif
			else ERR_SET_OUT(errp, EFAULT);
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1Socket_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static int _Dz1Socket_wait(SOCKET fd, int flag, struct timeval *wait, Dz1Error *errp)
{
	int ret = -1, nFound;

	fd_set _rd, _wr, _ex;
	fd_set *rd = NULL, *wr = NULL, *ex = NULL;

	if (flag & Dz1SocketWaitFlag_in) { rd = &_rd; FD_ZERO(rd); FD_SET(fd, rd); }
	if (flag & Dz1SocketWaitFlag_out) { wr = &_wr; FD_ZERO(wr); FD_SET(fd, wr); }
	if (flag & Dz1SocketWaitFlag_except) { ex = &_ex; FD_ZERO(ex); FD_SET(fd, ex); }

	pthread_testcancel();

	if ((nFound = select((int)(fd + 1), rd, wr, ex, wait)) < 0) { Dz1Error_set(errp, _GetSockError()); }
	else
	{
		pthread_testcancel();
		if (nFound == 0) { ret = 0; Dz1Error_set(errp, ETIMEDOUT); }
		else
		{
			ret = 0;

			if (rd && FD_ISSET(fd, rd)) ret |= Dz1SocketWaitFlag_in;
			if (wr && FD_ISSET(fd, wr)) ret |= Dz1SocketWaitFlag_out;
			if (ex && FD_ISSET(fd, ex)) ret |= Dz1SocketWaitFlag_except;

			Dz1Error_set(errp, 0);
		}
	}
	pthread_testcancel();

	return ret;
}

int Dz1Socket_wait(Dz1Socket *p, int flag, struct timeval *to, Dz1Error *err)
{
	int ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	struct timeval base = { 0, 100000 };

	if (to)
	{
		struct timeval now, wait, abstv;

		gettimeofday(&now, NULL);
		abstv = Dz1TimeVal_add(now, *to);

		while(1)
		{
			gettimeofday(&now, NULL);
			wait = Dz1TimeVal_sub(abstv, now);

			if (Dz1TimeVal_isZero(wait)) { ret = 0; memset(to, 0, sizeof(struct timeval)); Dz1Error_set(errp, ETIMEDOUT); break; }
			else
			{
				if (_Dz1TimeVal_cmp(wait, base) > 0) wait = base;

				if ((ret = _Dz1Socket_wait(p->fd, flag, &wait, errp)) == 0) { continue; }
				else if (ret == -1) { ERR_OUT(errp); break; }
				else
				{
					gettimeofday(&now, NULL);
					*to = Dz1TimeVal_sub(abstv, now);

					Dz1Error_set(errp, 0);
					break;
				}
			}
		}
	}
	else
	{
		struct timeval _to;
		while(1)
		{
			_to = base;
			if ((ret = _Dz1Socket_wait(p->fd, flag, &_to, errp)) == 0) { continue; }
			else if (ret == -1) { ERR_OUT(errp); break; }
			else break;
		}
	}
	return ret;
}


Dz1Error Dz1Socket_connect(Dz1Socket *p, Dz1SockAddr *dst, struct timeval *to)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int domain = Dz1SocketVer2Domain(dst->ver, &err);
	if (domain < 0) { ERR_OUT(&err); }
	else if (connect(p->fd, (struct sockaddr *)dst->x.ptr, __Dz1SocketSize__[dst->ver]) < 0)
	{
		int status;
		Dz1Error_set(&err, _GetSockError());
#ifndef UNIX_SYSTEM
		if (err.code != WSAEWOULDBLOCK) { ERR_OUT(&err); }
#else
		if (err.code != EINPROGRESS) { ERR_OUT(&err); }
#endif
		else if ((status = Dz1Socket_wait(p, Dz1SocketWaitFlag_exceptout, to, &err)) < 0) { ERR_OUT(&err); }
		else if (status & Dz1SocketWaitFlag_out)
		{
			if (status & Dz1SocketWaitFlag_except) { ERR_SET_OUT(&err, EFAULT); }
			else
			{
				int result = 0;
				socklen_t result_len = sizeof(result);

				Dz1Error_set(&err, 0);
				if (getsockopt(p->fd, SOL_SOCKET, SO_ERROR, (char *)&result, (socklen_t *)&result_len) < 0) { Dz1Error_set(&err, _GetSockError()); }
				else if (result)
				{
#ifndef UNIX_SYSTEM
					result = _ConvWsaError2Errno(result);
#endif
					Dz1Error_set(&err, result);
				}
			}
		}
	}
	return err;
}

ssize_t Dz1Socket_send(Dz1Socket *p, Dz1SockAddr *dst, u8_t *data, size_t size, bool_t isUrgent, struct timeval *to, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	int flag = MSG_NOSIGNAL | (isUrgent ? MSG_OOB : 0);
	if (size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (dst != NULL)
	{	// Connectionless Socket
		int domain = Dz1SocketVer2Domain(dst->ver, errp);
		if (domain < 0) { ERR_OUT(errp); }
		else if ((ret = sendto(p->fd, (char *)data, (int)size, flag, (struct sockaddr *)dst->x.ptr, __Dz1SocketSize__[dst->ver])) == 0) { Dz1Error_set(errp, EPIPE); }
		else if (ret < 0) Dz1Error_set(errp, _GetSockError());
		else Dz1Error_set(errp, 0);
	}
	else
	{	// Connection Socket
		if (0) { }
		else 
		{
			if ((ret = send(p->fd, (char *)data, (int)size, flag)) == 0) { Dz1Error_set(errp, EPIPE); }
			//else if (ret < 0) Dz1Error_set(errp, _GetSockError());
			else if (ret < 0)
			{
				int sockErr = _GetSockError();
#ifndef UNIX_SYSTEM
				if (sockErr == WSAEWOULDBLOCK) 
#else
				if (sockErr == EAGAIN || sockErr == EWOULDBLOCK)
#endif
				{
					while(ret < 0 )
					{
						Dz1Thread_usleep(10000);
						if ((ret = send(p->fd, (char *)data, (int)size, flag)) == 0) { Dz1Error_set(errp, EPIPE); }
					}
				}
			}
			else
			{
				Dz1Error_set(errp, 0);
//				printf("Dz1Socket_send() : Data sent %lu\n", ret);
			}
		}
	}
	return ret;
}

ssize_t Dz1Socket_recv(Dz1Socket *p, Dz1SockAddr *peer, u8_t *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (peer)
	{
#ifdef DIMZ_SUPPORT_IPV6
		socklen_t addr_len = sizeof(struct sockaddr_in6);
#else
		socklen_t addr_len = sizeof(struct sockaddr_in);
#endif
		memset(peer, 0, sizeof(Dz1SockAddr));

		if ((ret = recvfrom(p->fd, (char *)buf, (int)size, 0, (struct sockaddr *)peer->x.ptr, &addr_len)) < 0)
		{
			Dz1Error_set(errp, _GetSockError());
		}
		else if (ret == 0) { Dz1Error_set(errp, EPIPE); }
		else if (addr_len == sizeof(struct sockaddr_in))
		{
			peer->ver = Dz1SocketVer_inet4;
			Dz1Error_set(errp, 0);
		}
#ifdef DIMZ_SUPPORT_IPV6
		else if (addr_len == sizeof(struct sockaddr_in6))
		{
			peer->ver = Dz1SocketVer_inet6;
			Dz1Error_set(errp, 0);
		}
#endif
		else ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		if ((ret = recv(p->fd, (char *)buf, (int)size, 0)) < 0) { Dz1Error_set(errp, _GetSockError()); }
		else if (ret == 0)
		{
			Dz1Error_set(errp, EPIPE);
		}
		else { Dz1Error_set(errp, 0); }
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1 TCP Client Socket
///////////////////////////////////////////////////////////////////////////////
static int Dz1TcpClientSocket_wait(Dz1TcpClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err)
{
	return Dz1Socket_wait((Dz1Socket *)p->specific, flag, to, err);
}

static ssize_t Dz1TcpClientSocket_send(Dz1TcpClientSocket *p, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
{
	ssize_t sendByte, ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u8_t *cp = data;
	bool_t isUrgent = flag & DZ1_TCP_SOCK_FLAG_URGENT ? TRUE : FALSE;

	Dz1Error_set(errp, 0);
	do
	{
		if ((sendByte = Dz1Socket_send((Dz1Socket *)p->specific, NULL, cp, size, isUrgent, to, errp)) <= 0)
		{
#ifdef WIN32
			if (errp->code == 10035)
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
	} while ((flag & DZ1_TCP_SOCK_FLAG_COMPLETE) && size);

	ret = errp->code == 0 ? (ssize_t)(cp - data) : -1;
	return ret;
}

static ssize_t Dz1TcpClientSocket_recv(Dz1TcpClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
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
	} while ((flag & DZ1_TCP_SOCK_FLAG_COMPLETE) && size);

	return (ssize_t)(cp - buf);
}

static SOCKET Dz1TcpClientSocket_getOSHandle(Dz1TcpClientSocket *p)
{
	Dz1Socket *s = (Dz1Socket *)p->specific;
	return s->fd;
}

static bool_t _is_zero(u8_t *buf, size_t sz)
{
	u8_t *cp = buf;
	while(sz)
	{
		if (*cp != 0) return FALSE;
		else { cp++; sz--; }
	}
	return TRUE;
}

Dz1TcpClientSocket *_Dz1TcpClientSocket_open(Dz1SockAddr *dst, Dz1SockAddr *local, struct timeval *to, Dz1Error *err, const char *__file__, int __line__)
{
	Dz1TcpClientSocket *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SockAddr _local, *localp = local ? local : &_local;
	memset(&_local, 0, sizeof(Dz1SockAddr));
	if (!dst) { Dz1Error_set(errp, EINVAL); }
	else if ((ret = (Dz1TcpClientSocket *)_Dz1Calloc(sizeof(Dz1TcpClientSocket), 1, errp, __file__, __line__)) == NULL) { ERR_OUT(errp); }
	else
	{
		u8_t local_addr[16] = { 0, };
		size_t local_addr_sz = sizeof(local_addr);
		Dz1SockAddr temp;
		u16_t local_port = 0;

		pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&ret);

		memset(&temp, 0, sizeof(Dz1SockAddr));

		ret->specific_del = (Dz1DelFunc)Dz1Socket_close;
		Dz1SockAddr_setPort(localp, 0);
		if ((ret->specific = _Dz1Socket_open(localp, SOCK_STREAM, 0, NULL, errp, __file__, __line__)) == NULL) { ERR_OUT(errp); }
		else if ((*errp = Dz1Socket_connect((Dz1Socket *)ret->specific, dst, to)).code) { }
		else if ((*errp = Dz1Socket_getLocalAddr((Dz1Socket *)ret->specific, &temp)).code) { ERR_OUT(errp); }
		else if ((*errp = Dz1SockAddr_getAddr(&temp, local_addr, &local_addr_sz)).code) { ERR_OUT(errp); }
		else if ((*errp = Dz1SockAddr_getPort(&temp, &local_port)).code) ERR_OUT(errp);
		else if (_is_zero(local_addr, local_addr_sz) || local_port == 0) { Dz1Error_set(errp, ECONNREFUSED); }
		else
		{
			memcpy(localp, &temp, sizeof(Dz1SockAddr));

			ret->wait = Dz1TcpClientSocket_wait;
			ret->send = Dz1TcpClientSocket_send;
			ret->recv = Dz1TcpClientSocket_recv;
			ret->getOSHandle = Dz1TcpClientSocket_getOSHandle;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1TcpClientSocket_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpClientSocket_close(Dz1TcpClientSocket *p)
{
	if (!p) return;
	if (p->specific_del && p->specific)
	{
		p->specific_del(p->specific);
		p->specific = NULL;
	}
	Dz1Free(p);
}

Dz1TcpClientSocket *Dz1TcpClientSocket_encapsulation(void **specific, Dz1DelFunc specific_del,
												int (*wait)(Dz1TcpClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err),
												ssize_t (*send)(Dz1TcpClientSocket *p, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err),
												ssize_t (*recv)(Dz1TcpClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err),
												SOCKET (*getOSHandle)(Dz1TcpClientSocket *p),
												Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpClientSocket *ret = (Dz1TcpClientSocket *)Dz1Calloc(sizeof(Dz1TcpClientSocket), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&ret);

		if (specific) ret->specific = (*specific);
		ret->specific_del = specific_del;
		if (specific_del && specific) *specific = NULL;

		ret->wait = wait;
		ret->send = send;
		ret->recv = recv;
		ret->getOSHandle = getOSHandle;

		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1 UDP Socket
///////////////////////////////////////////////////////////////////////////////
static int Dz1UdpSocket_wait(Dz1UdpSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err)
{ return Dz1Socket_wait((Dz1Socket *)p->specific, flag, to, err); }

static ssize_t Dz1UdpSocket_send(Dz1UdpSocket *p, Dz1SockAddr *peer, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
{
	ssize_t sendByte;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u8_t *cp = data;

	Dz1Error_set(errp, 0);

	do
	{
		if ((sendByte = Dz1Socket_send((Dz1Socket *)p->specific, peer, cp, size, FALSE, to, errp)) <= 0) { ERR_OUT(errp); break; }
		else { cp += sendByte; size -= sendByte; }

	} while ((flag & DZ1_UDP_SOCK_FLAG_COMPLETE) && size);

	return errp->code == 0 ? (ssize_t)(cp - data) : -1;
}

static ssize_t Dz1UdpSocket_recv(Dz1UdpSocket *p, Dz1SockAddr *peer, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
{
	Dz1SockAddr _peer, *peerp = peer ? peer : &_peer;
	ssize_t recvByte = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u8_t *cp = buf;

	Dz1Error_set(errp, 0);
	do
	{
		if ((recvByte = Dz1Socket_recv((Dz1Socket *)p->specific, peerp, cp, size, errp)) <= 0)
		{
			return recvByte;
		}
		else { cp += recvByte; size -= recvByte; }
	} while ((flag & DZ1_UDP_SOCK_FLAG_COMPLETE) && size);

	return (ssize_t)(cp - buf);
}

static SOCKET Dz1UdpSocket_getOSHandle(Dz1TcpClientSocket *p)
{
	Dz1Socket *s = (Dz1Socket *)p->specific;
	return s->fd;
}

Dz1UdpSocket *_Dz1UdpSocket_open(Dz1SockAddr *peer, Dz1SockAddr *local, struct timeval *to, Dz1Error *err, const char *__file__, int __line__)
{
	Dz1UdpSocket *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!local) { Dz1Error_set(errp, EINVAL); }
	else if ((ret = (Dz1UdpSocket *)_Dz1Calloc(sizeof(Dz1UdpSocket), 1, errp, __file__, __line__)) == NULL) { ERR_OUT(errp); }
	else
	{
		Dz1SockAddr temp;
		u16_t tempPort = 0;

		pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&ret);

		memset(&temp, 0, sizeof(Dz1SockAddr));

		ret->specific_del = (Dz1DelFunc)Dz1Socket_close;
		if ((ret->specific = _Dz1Socket_open(local, SOCK_DGRAM, 0, NULL, errp, __file__, __line__)) == NULL) { ERR_OUT(errp); }
		else if (peer != NULL && (*errp = Dz1Socket_connect((Dz1Socket *)ret->specific, peer, to)).code) { ERR_OUT(errp); }
		else if ((*errp = Dz1Socket_getLocalAddr((Dz1Socket *)ret->specific, &temp)).code) { ERR_OUT(errp); }
		else if ((*errp = Dz1SockAddr_getPort(&temp, &tempPort)).code) ERR_OUT(errp);
		else if (tempPort == 0) { ERR_SET_OUT(errp, EPIPE); }
		else
		{
			memcpy(local, &temp, sizeof(Dz1SockAddr));

			ret->wait = Dz1UdpSocket_wait;
			ret->send = Dz1UdpSocket_send;
			ret->recv = Dz1UdpSocket_recv;
			ret->getOSHandle = Dz1UdpSocket_getOSHandle;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1TcpClientSocket_delAndSetNull, (void *)&ret);
	}
	return ret;
}

// Dz1UdpSocket *_Dz1UdpSocket_openAsServer(Dz1SocketVer ver, u16_t *in_out_port, struct timeval *to, Dz1Error *err, const char *__file__, int __line__)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1SockAddr local ;
// 	Dz1UdpSocket *ret = NULL;
// 	if (in_out_port == NULL) ERR_SET_OUT(errp, EINVAL);
// 	else if (Dz1SockAddr_setZeroAddr(&local, ver, errp) == FALSE) ERR_OUT(errp);
// 	else if (*in_out_port != 0 && (*errp = Dz1SockAddr_setPort(&local, *in_out_port)).code) ERR_OUT(errp);
// 	else if ((ret = _Dz1UdpSocket_open(NULL, &local, to, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 	return ret;
// }
// 
// Dz1UdpSocket *Dz1UdpSocket_accept(Dz1UdpSocket *sock_svr, struct timeval *to, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 
// 	int addr_len = 0;
// 	Dz1SockAddr peer, local;
// 	memset(&peer, 0, sizeof(Dz1SockAddr));
// 	memset(&local, 0, sizeof(Dz1SockAddr));
// 
// 	if ((*errp = Dz1Socket_getLocalAddr((Dz1Socket *)sock_svr->specific, &local)).code) { ERR_OUT(errp); }
// 	else if (Dz1SockAddr_setAddrZero(&peer, &local, errp) == FALSE) ERR_OUT(errp);
// 	else if ((addr_len = Dz1SockAddr_getAddrLen(&peer, errp)) < 0) ERR_OUT(errp);
// 	else if ((s = accept(sock_svr, (struct sockaddr *)peer.x.ptr, addr_len)) == INVALID_SOCKET) ERR_SET_OUT(errp, GetLastError());
// }

void Dz1UdpSocket_close(Dz1UdpSocket *p)
{
	if (!p) return;
	if (p->specific_del && p->specific)
	{
		p->specific_del(p->specific);
		p->specific = NULL;
	}
	Dz1Free(p);
}

///////////////////////////////////////////////////////////////////////////////
// Dz1 TCP Server Socket
///////////////////////////////////////////////////////////////////////////////
static int Dz1TcpServerSocket_wait(Dz1TcpServerSocket *p, struct timeval *to, Dz1Error *err)
{
	return Dz1Socket_wait((Dz1Socket *)p->specific, Dz1SocketWaitFlag_in, to, err);
}

static Dz1TcpClientSocket *Dz1TcpServerSocket_accept(Dz1TcpServerSocket *p, Dz1SockAddr *local, Dz1SockAddr *peer, struct timeval *to, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpClientSocket *ret = (Dz1TcpClientSocket *)Dz1Calloc(sizeof(Dz1TcpClientSocket), 1, errp);
	if (ret == NULL) { Dz1Error_set(errp, ENOMEM); }
	else
	{
		int status = 0;
		pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&ret);
		if ((status = Dz1Socket_wait((Dz1Socket *)p->specific, Dz1SocketWaitFlag_in, to, errp)) <= 0) { ERR_OUT(errp); }
		else if ((ret->specific = Dz1Socket_accept((Dz1Socket *)p->specific, local, peer, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->specific_del = (Dz1DelFunc)Dz1Socket_close;
			ret->wait = Dz1TcpClientSocket_wait;
			ret->send = Dz1TcpClientSocket_send;
			ret->recv = Dz1TcpClientSocket_recv;
			ret->getOSHandle = Dz1TcpClientSocket_getOSHandle;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1TcpServerSocket *Dz1TcpServerSocket_open(Dz1SockAddr *local, u16_t *o_port, int backlog, Dz1Error *err)
{
	Dz1TcpServerSocket *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!local) { Dz1Error_set(errp, EINVAL); }
	else if ((ret = (Dz1TcpServerSocket *)Dz1Calloc(sizeof(Dz1TcpServerSocket), 1,errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpServerSocket_closeAndSetNull, (void *)&ret);

		if ((ret->specific = Dz1Socket_open(local, SOCK_STREAM, 0, o_port, errp)) == NULL) { ERR_OUT(errp); }
		else if ((*errp = Dz1Socket_listen((Dz1Socket *)ret->specific, backlog)).code) { ERR_OUT(errp); }
		else
		{
			ret->wait = Dz1TcpServerSocket_wait;
			ret->accept = Dz1TcpServerSocket_accept;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1TcpServerSocket_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpServerSocket_close(Dz1TcpServerSocket *p)
{
	if (!p) return;
	if (p->specific) Dz1Socket_close((Dz1Socket *)p->specific);
	Dz1Free(p);
}

/*
///////////////////////////////////////////////////////////////////////////////
// Dz1 ICMP Socket
///////////////////////////////////////////////////////////////////////////////
typedef struct Dz1IcmpSocket
{
	u32_t identifier;

	Dz1Socket *sock;

	Dz1Error (*send)(struct Dz1IcmpSocket *, uint8_t *data, size_t size, struct timeval *to);

	int (*wait)(struct Dz1IcmpSocket *p, struct timeval *to, Dz1Error *err);
	ssize_t (*recv)(struct Dz1IcmpSocket *, uint8_t *buf, size_t size, struct timeval *to, Dz1Error *err);
} Dz1IcmpSocket;
*/
