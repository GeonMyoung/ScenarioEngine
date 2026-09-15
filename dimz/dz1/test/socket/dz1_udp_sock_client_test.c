// dz1_udp_sock_client.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <dz1_cleanup.h>
#include <dz1_socket.h>
#include <dz1_socket_receiver.h>
#include <dz1_shell.h>

static FILE *logFP = NULL;
static Dz1SockAddr peer;
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

static void shell_dest_ip_usage(str_t n) { Dz1Thread_printf("Usage] %s ip <ip>\n", n); }
static void shell_dest_ip(Dz1SockAddr *dst, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (argc != 2) shell_dest_ip_usage(n);
	else if ((err = Dz1SockAddr_setAddrStr(dst, argv[1])).code) ERR_OUT(&err);
}

static void shell_dest_port_usage(str_t n) { Dz1Thread_printf("Usage] %s port <port>\n", n); }
static void shell_dest_port(Dz1SockAddr *dst, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (argc != 2) shell_dest_port_usage(n);
	else
	{
		int port = atoi(argv[1]);
		if (port <= 1024 || port > 65535) shell_dest_port_usage(n);
		else if ((err = Dz1SockAddr_setPort(dst, (u16_t)port)).code) ERR_OUT(&err);
	}
}

static void shell_dest_usage(str_t n) { Dz1Thread_printf("Usage] %s ip|port|show <value>\n", n); }
static Dz1ShellCmdReturn shell_dest(void *ptr, int argc, char *argv[])
{
	if (argc < 2) shell_dest_usage(argv[0]);
	else
	{
		Dz1SockAddr *dst = (Dz1SockAddr *)ptr;

		if (strcmp(argv[1], "ip") == 0) shell_dest_ip(dst, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "port") == 0) shell_dest_port(dst, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "show") == 0)
		{
			Dz1Thread_printf("Destination = "); Dz1SockAddr_dump(&peer, 0);
		}
	}
	return Dz1ShellCmdReturn_ok;
}

static void shell_feed_usage(str_t n) { Dz1Thread_printf("Usage] %s <string>\n", n); }
static Dz1ShellCmdReturn shell_feed(void *ptr, int argc, char *argv[])
{
	if (argc != 2) shell_feed_usage(argv[0]);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		Dz1UdpSocket *sock = (Dz1UdpSocket *)ptr;
		char strIP[53];
		Dz1Thread_printf("Feed string \"%s\" to %s\n", argv[1], Dz1SockAddr_printable(&peer, strIP, FALSE, NULL));
		if (sock->send(sock, &peer, (u8_t *)argv[1], strlen(argv[1]), DZ1_UDP_SOCK_FLAG_COMPLETE, NULL, &err) < 0) ERR_OUT(&err);
	}
	return Dz1ShellCmdReturn_ok;
}

static void shell_send_usage(str_t n) { Dz1Thread_printf("Usage] %s <size> [<ip> [<port>]]\n", n); }
static Dz1ShellCmdReturn shell_send(void *ptr, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;

	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1UdpSocket *sock = (Dz1UdpSocket *)ptr;

	if (argc != 2 && argc != 3 && argc != 4) shell_send_usage(argv[0]);
	else
	{
		u8_t *buf = NULL;
		int size = (u32_t)atoi(argv[1]);

		if (size <= 0)
		{
			Dz1Thread_printf("Invalid Size\n");
			return ret;
		}

		if (argc >= 3 && (err = Dz1SockAddr_setAddrStr(&peer, argv[2])).code) { ERR_OUT(&err); return ret; }
		if (argc >= 4 && (err = Dz1SockAddr_setPort(&peer, (u16_t)atoi(argv[3]))).code) { ERR_OUT(&err); return ret; }

		if ((buf = (u8_t *)Dz1Malloc(size, &err)) == NULL) ERR_OUT(&err);
		else
		{
			char strIP[53];
			pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
			Dz1Thread_printf("Send %d Byte Data to %s\n", size, Dz1SockAddr_printable(&peer, strIP, FALSE, NULL));
			if (sock->send(sock, &peer, buf, (size_t)size, DZ1_UDP_SOCK_FLAG_COMPLETE, NULL, &err) < 0) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
		}
	}
	return Dz1ShellCmdReturn_ok;
}

static void shell_slice_usage(str_t n) { Dz1Thread_printf("Usage] %s <repeat> [<size>]\n", n); }
static Dz1ShellCmdReturn shell_slice(void *ptr, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;

	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1UdpSocket *sock = (Dz1UdpSocket *)ptr;

	if (argc != 2 && argc != 3) shell_slice_usage(argv[0]);
	else
	{
		u8_t *buf = NULL;
		int repeat = atoi(argv[1]);
		int size = 10;
		
		if (argc >= 3) size = atoi(argv[2]);
		if (size <= 0)
		{
			Dz1Thread_printf("Invalid Size\n");
			return ret;
		}

		if ((buf = (u8_t *)Dz1Malloc(size, &err)) == NULL) ERR_OUT(&err);
		else
		{
			int i;
			char strIP[53];
			pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
			Dz1Thread_printf("Send %d Byte Data with %d times to %s\n", size, repeat, Dz1SockAddr_printable(&peer, strIP, FALSE, NULL));
			for (i = 0; err.code == 0 && i < repeat; i++)
				if (sock->send(sock, &peer, buf, (size_t)size, DZ1_UDP_SOCK_FLAG_COMPLETE, NULL, &err) < 0) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
		}
	}
	return Dz1ShellCmdReturn_ok;
}

static void shell_start(Dz1UdpSocket *sock)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	void *sh = NULL;
	
#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "BitCore", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "BitCore", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);

		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "dest", shell_dest, (void *)sock, "Manage Destination Address")).code) { ERR_OUT(&err); }
		else if ((err = Dz1Shell_cmdReg(sh, "feed", shell_feed, (void *)sock, "Send Text")).code) { ERR_OUT(&err); }
		else if ((err = Dz1Shell_cmdReg(sh, "send", shell_send, (void *)sock, "Send Data")).code) { ERR_OUT(&err); }
		else if ((err = Dz1Shell_cmdReg(sh, "slice", shell_slice, (void *)sock, "Send Sliced Data")).code) { ERR_OUT(&err); }
		Dz1Shell_start(sh, NULL);
			
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

static Dz1SocketReceierBehavior _rcveFwd(void *userParam, void *userResource,  Dz1SockAddr *peer, Dz1SockAddr *local,
										Dz1UdpSocket *s, u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1Thread_printf("_rcveFwd() : %u Byte Received\n", size);
	return Dz1SocketReceierBehavior_continue;
}

static void _rcvrException(void *userParam, void *userResource, Dz1SockAddr *local, Dz1UdpSocket *s, Dz1Error *reason)
{
	Dz1Thread_printf("_rcveFwd() : Called\n");
	ERR_OUT(reason);
}

int main(int argc, char* argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1SockAddr local;
	Dz1UdpSocket* sock = NULL;
	struct timeval to = { 10, 0 };

	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init() == FALSE) ERR_SET_OUT(&err, ENOSYS);
	else
	{
#endif
	if ((logFP = fopen("dz1_udp_sock.log.txt", "wb")) == NULL) ERR_SET_OUT(&err, errno);
#ifdef UNIX_SYSTEM
	else if ((err = Dz1SockAddr_setAddrStr(&peer, "192.168.2.124")).code) ERR_OUT(&err);
#else
	else if ((err = Dz1SockAddr_setAddrStr(&peer, "192.168.1.1")).code) ERR_OUT(&err);
#endif
	else if ((err = Dz1SockAddr_setPort(&peer, 39978)).code) ERR_OUT(&err);
	else if ((err = Dz1SockAddr_setAddrStr(&local, "0.0.0.0")).code) ERR_OUT(&err);
	else if ((err = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(&err);
	else if ((sock = Dz1UdpSocket_open(NULL, &local, &to, &err)) == NULL) ERR_OUT(&err);
	else
	{
		u32_t rcvr = -1;
		pthread_cleanup_push(Dz1UdpSocket_closeAndSetNull, (void *)&sock);
		Dz1Thread_printf("LOCAL = "); Dz1SockAddr_dump(&local, 1);
		if ((rcvr = Dz1UdpSocketReceiver_start(&local, 51200, 0, &sock, FALSE, NULL, _rcveFwd, _rcvrException, NULL, NULL, NULL, NULL, &err)) == -1) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1SocketReceiver_startCancel, (void *)&rcvr);
			shell_start(sock);
			pthread_cleanup_pop(1); // (Dz1SocketReceiver_startCancel, (void *)&rcvr);
		}
		pthread_cleanup_pop(1); // (Dz1UdpSocket_closeAndSetNull, (void *)&sock);
	}
#ifndef UNIX_SYSTEM
	}
#endif
	return 0;
}

