#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket_receiver.h>
#include <dz1_serial_sock.h>

#ifdef _DEBUG
#include <conio.h>
#endif

Dz1TcpClientSocket *sock = NULL;

static FILE *logfp = NULL;
static void _outputHook(void *ptr, unsigned char *data, size_t size)
{
	if (logfp != NULL)
	{
		fwrite(data, size, 1, logfp);
		fflush(logfp);
	}
}
static void _memoryExport(void *ptr) { if (logfp) Dz1Mem_export(logfp, TRUE); }

static void cmd_serial_open_usage(str_t n) { Dz1Thread_printf("Usage] %s open <port> [<baud>]\n", n); }
static void cmd_serial_open(void *ptr, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (argc != 2 && argc != 3) cmd_serial_open_usage(n);
	else if (sock != NULL) Dz1Thread_printf("Already open\n");
	else
	{
		int port = atoi(argv[1]);
		u32_t baud = 9600;
		if (argc == 3) baud = (u32_t)atoi(argv[2]);

		if (baud == 0) cmd_serial_open_usage(n);
		else if ((sock = Dz1SerialSock_new(port, baud, &err)) == NULL) ERR_OUT(&err);
		else Dz1Thread_printf("Open Success\n");
	}

}

static void cmd_serial_close(void *ptr, str_t n, int argc, char *argv[])
{
	if (sock == NULL) Dz1Thread_printf("not opened\n");
	else Dz1TcpClientSocket_closeAndSetNull((void *)&sock);
}

static void cmd_serial_send_usage(str_t n) { Dz1Thread_printf("Usage] %s send <string>\n", n); }
static void cmd_serial_send(void *ptr, str_t n, int argc, char *argv[])
{
	if (argc != 2) cmd_serial_send_usage(n);
	else if (sock == NULL) Dz1Thread_printf("not opened\n");
	else
	{
		ssize_t status;
		u8_t buf[1024] = { 0, };
		struct timeval wait_to = { 5, 0 };
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		if (sock->send(sock, argv[1], strlen(argv[1]), DZ1_TCP_SOCK_FLAG_COMPLETE, NULL, &err) < 0) ERR_OUT(&err);
		else if ((status = sock->recv(sock, buf, sizeof(buf), 0, &wait_to, &err)) < 0) ERR_OUT(&err);
		else if (status == 0) ERR_SET_OUT(&err, EPIPE);
		else
		{
			Dz1Thread_printf("Received ---\n");
			Dz1Thread_printb(buf, status, 16, FALSE);
		}
	}
}

static void cmd_serial_usage(str_t n) { Dz1Thread_printf("Usage] %s <open|close|send> <parameter...>\n", n); }
static Dz1ShellCmdReturn cmd_serial(void *ptr, int argc, char *argv[])
{
	if (argc < 2) cmd_serial_usage(argv[0]);
	else if (strcmp(argv[1], "open") == 0 || strcmp(argv[1], "o") == 0) cmd_serial_open(ptr, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "close") == 0 || strcmp(argv[1], "x") == 0) cmd_serial_close(ptr, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "send") == 0 || strcmp(argv[1], "s") == 0) cmd_serial_send(ptr, argv[0], argc-1, &argv[1]);
	return Dz1ShellCmdReturn_ok;
}

int th = -1;

static Dz1SocketReceierBehavior _mySockForward(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local,
											   Dz1TcpClientSocket *s, u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;

	Dz1Thread_printf("<<< TASK Received\n");
	Dz1Thread_tprintb(1, data, size, 16, FALSE);

	return ret;
}

static void cmd_serial_task_open_usage(str_t n) { Dz1Thread_printf("Usage] %s open <port> [<baud>]\n", n); }
static void cmd_serial_task_open(void *ptr, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (argc != 2 && argc != 3) cmd_serial_task_open_usage(n);
	else if (th != -1) Dz1Thread_printf("Already Opened\n");
	else
	{
		int port = atoi(argv[1]);
		u32_t baud = 9600;
		if (argc == 3) baud = (u32_t)atoi(argv[2]);

		if (baud == 0) cmd_serial_task_open_usage(n);
		else if ((sock = Dz1SerialSock_new(port, baud, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1SockAddr peer, local;
			pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&sock);
			if		((err = Dz1SockAddr_setAddrStr(&peer, "0.0.255.0")).code) ERR_OUT(&err);
			else if ((err = Dz1SockAddr_setPort(&peer, (u16_t)port)).code) ERR_OUT(&err);
			else if	((err = Dz1SockAddr_setAddrStr(&local, "0.0.255.0")).code) ERR_OUT(&err);
			else if ((err = Dz1SockAddr_setPort(&local, (u16_t)port)).code) ERR_OUT(&err);
			else if ((th = Dz1TcpSocketReceiver_start(&peer, &local, 4096, 0, &sock, TRUE,
											NULL,
											_mySockForward, NULL, NULL, 
											NULL,
											NULL, NULL, &err)) == -1) ERR_OUT(&err);
			else
			{
				Dz1Thread_printf("Open Success\n");
			}
			pthread_cleanup_pop(err.code); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&sock);
		}
	}
}

static void cmd_serial_task_close(void *ptr, str_t n, int argc, char *argv[])
{
	if (th == -1) Dz1Thread_printf("Not opened\n");
	else
	{
		Dz1TcpSocketReceiver_stop(th); th = -1;
		Dz1TcpClientSocket_closeAndSetNull(&sock);
	}
}

static void cmd_serial_task_send_usage(str_t n) { Dz1Thread_printf("Usage] %s send <string>\n", n); }
static void cmd_serial_task_send(void *ptr, str_t n, int argc, char *argv[])
{
	if (argc != 2) cmd_serial_send_usage(n);
	else if (sock == NULL) Dz1Thread_printf("not opened\n");
	else
	{
		u8_t buf[1024] = { 0, };
		struct timeval wait_to = { 5, 0 };
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		if (sock->send(sock, argv[1], strlen(argv[1]), DZ1_TCP_SOCK_FLAG_COMPLETE, NULL, &err) < 0) ERR_OUT(&err);
	}
}

static void cmd_serial_task_usage(str_t n) { Dz1Thread_printf("Usage] %s <open|close|send> <parameter...>\n", n); }
static Dz1ShellCmdReturn cmd_serial_task(void *ptr, int argc, char *argv[])
{
	if (argc < 2) cmd_serial_usage(argv[0]);
	else if (strcmp(argv[1], "open") == 0 || strcmp(argv[1], "o") == 0) cmd_serial_task_open(ptr, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "close") == 0 || strcmp(argv[1], "x") == 0) cmd_serial_task_close(ptr, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "send") == 0 || strcmp(argv[1], "s") == 0) cmd_serial_task_send(ptr, argv[0], argc-1, &argv[1]);
	return Dz1ShellCmdReturn_ok;
}

static void _shell_start(void *ptr)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_serial_sock", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_serial_sock", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "s", cmd_serial, NULL, "serial test command")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "t", cmd_serial_task, NULL, "serial test in task mode")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_serial_sockTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#endif
	// Edit Task Argument
	_shell_start(NULL);

#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
	return err.code;
}
