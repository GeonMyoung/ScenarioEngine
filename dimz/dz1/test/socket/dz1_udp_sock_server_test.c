// dz1_udp_sock.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <dz1_cleanup.h>
#include <dz1_socket_receiver.h>
#include <dz1_malloc.h>

static Dz1Error _udpRecvInit(void **ret, void *userParam, Dz1SockAddr *local, Dz1UdpSocket *s)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	return err;
}

static Dz1SocketReceierBehavior _udpRecvFwd(void *userParam, void *userResource,
											Dz1SockAddr *peer, Dz1SockAddr *local,
											Dz1UdpSocket *s, u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;
	struct timeval to = { 5, };
	if (s->send(s, peer, data, size, DZ1_UDP_SOCK_FLAG_COMPLETE, &to, errp) != size) ERR_SET_OUT(errp, EFAULT);
	Dz1Thread_printf("_udpRecvFwd() : %u Byte Replect\n", size);
	/*
	Dz1Thread_printf("_udpRecvFwd() : Data Received...\n");
	Dz1Thread_printf("PEER  = "); Dz1SockAddr_dump(peer, 1);
	Dz1Thread_printf("LOCAL = "); Dz1SockAddr_dump(local, 1);
	Dz1Thread_printf("DATA = {\n");
	Dz1Thread_tprintb(1, data, size, 16);
	Dz1Thread_printf("}\n");
	*/
	return ret;
}

static Dz1SocketReceierBehavior _udpRecvTimeout(void *userParam, void *userResource, Dz1SockAddr *local, Dz1UdpSocket *s, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;
	Dz1Thread_printf("_udpRecvTimeout() : Just timeout... wait more..\n");
	return ret;
}

static void _udpRecvException(void *userParam, void *userResource, Dz1SockAddr *local, Dz1UdpSocket *s, Dz1Error *reason)
{
	Dz1Thread_printf("_udpRecvException() : Got Exception\n");
	Dz1Thread_printf("LOCAL = "); Dz1SockAddr_dump(local, 1);
	ERR_OUT(reason);
}

static void _udpRecvCleanup(void *ptr)
{
}

/*
static Dz1Error _setAddr(Dz1SockAddr *addr, str_t fqdn)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	memset(addr, 0, sizeof(Dz1SockAddr));
	if ((err = Dz1SockAddr_getByName(addr, fqdn)).code)
	{
		str_t gitsnSTAR = "59.150.106.51";
		if ((err = Dz1SockAddr_setAddrStr(addr, gitsnSTAR)).code) ERR_OUT(&err);
	}
	Dz1SockAddr_setPort(addr, 30099);
	return err;
}
*/

static FILE *logFP = NULL;
static void _memoryExport(void *ptr)
{
	if (logFP != NULL)
	{
		Dz1Mem_export(logFP, TRUE);
		fflush(logFP);
	}
}

static void _outputHook(void *ptr, unsigned char *data, size_t size)
{
	if (logFP != NULL)
	{
		fwrite(data, size, 1, logFP);
		fflush(logFP);
	}
}

int main(int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int status = 0;
	Dz1SockAddr local;
	Dz1UdpSocket* sock = NULL;
	struct timeval to = { 10, 0 };

	Dz1Cleanup_init();
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if ((status = Dz1Socket_init()) == FALSE) ERR_SET_OUT(&err, status);
	else
	{
#endif
	if ((logFP = fopen("dz1_udp_sock.log.txt", "wb")) == NULL) ERR_SET_OUT(&err, errno);
	else if ((err = Dz1SockAddr_setAddrStr(&local, "0.0.0.0")).code) ERR_OUT(&err);
	else if ((err = Dz1SockAddr_setPort(&local, 39978)).code) ERR_OUT(&err);
	else if ((sock = Dz1UdpSocket_open(NULL, &local, &to, &err)) == NULL) ERR_OUT(&err);
	else
	{
		int id = -1;
		pthread_cleanup_push(Dz1UdpSocket_closeAndSetNull, (void *)&sock);
		Dz1Thread_printf("LOCAL = "); Dz1SockAddr_dump(&local, 1);
		if ((id = Dz1UdpSocketReceiver_start(&local, 40960, 0, &sock, FALSE,
											_udpRecvInit,
											_udpRecvFwd,
											_udpRecvException,
											_udpRecvTimeout,
											_udpRecvCleanup,
											NULL, NULL, &err)) == -1) ERR_OUT(&err);
		else
		{
//			u8_t temp;
			pthread_cleanup_push(Dz1SocketReceiver_startCancel, (void *)&id);
			Dz1Thread_printf("Press Any key to Terminate...\n");
//			if (Dz1Thread_read((u8_t *)&temp, 1, -1, &err) < 0) ERR_OUT(&err);
			if (Dz1Thread_getch(-1, errp) < 0) ERR_OUT(errp);
			pthread_cleanup_pop(1); // (Dz1UdpSocketReceiver_startCancel, (void *)&id);
		}
		pthread_cleanup_pop(1); // (Dz1UdpSocket_closeAndSetNull, (void *)&sock);
	}
#ifndef UNIX_SYSTEM
	}
#endif
	return err.code;
}
 
