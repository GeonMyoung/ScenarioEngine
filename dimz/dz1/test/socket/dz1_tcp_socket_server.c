#include <dz1_shell.h>
#ifdef CPP_BUILDER_WIN32
#include <stdio.h>
#pragma hdrstop
#endif

#include <dz1_cleanup.h>
#include <dz1_socket.h>
#include <dz1_socket_callback.h>
#ifdef _DZ1_USE_SSL
#include <dz1_socket_callback_ssl.h>
#endif
#include <dz1_malloc.h>
#include <dz1_thread.h>
#include <dz1_thread_stdio.h>
#include <dz1_usleep.h>

#include "dz1_tcp_socket_server_task.h"

#ifdef WIN32
#include <conio.h>
#endif

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

/*
static Dz1SocketReceierBehavior receiverEcho(void *ptr, void *resource, Dz1SockAddr *peer, Dz1SockAddr *local,
											Dz1TcpClientSocket *s, u8_t *data, size_t size, Dz1Error *errp)
{
	size_t recvByte;
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;

	if ((recvByte = s->send(s, data, size, TRUE, NULL, errp)) <= 0) { ERR_OUT(errp); ret = Dz1SocketReceierBehavior_term; }
	else Dz1Thread_printf("receiverEcho() : %d byte\n", recvByte);

	return ret;
}
*/

static void _cmd_port_open_usage(str_t n) { Dz1Thread_printf("Usage] %s open <port_number>\n", n); }
static void _cmd_port_open(void *task, str_t n, int argc, char *argv[])
{
	if (argc >= 2 && (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0)) _cmd_port_open_usage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		u32_t port = 9999;
		
		if (argc >= 2) port = (u32_t)atoi(argv[1]);

		if (port == 0 || port & 0xFFFF0000) Dz1Thread_printf("Port Number = 1 ~ 65535\n");
		else if ((err = Dz1TcpSocketServerTask_open(task, port)).code) ERR_OUT(&err);
	}
}

static Dz1ShellCmdReturn _cmd_open_port(void *task, int argc, char *argv[])
{
	_cmd_port_open(task, argv[0], argc-1, &argv[1]);
	return Dz1ShellCmdReturn_ok;
}

static void _cmd_port_open2(void *task, str_t n, int argc, char *argv[])
{
//	if (argc < 2) _cmd_port_open_usage(n);
//	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		u32_t port = 9999;
		
		if (argc >= 2) port = (u32_t)atoi(argv[1]);

		if (port == 0 || port & 0xFFFF0000) Dz1Thread_printf("Port Number = 1 ~ 65535\n");
		else if ((err = Dz1TcpSocketServerTask_open2(task, port)).code) ERR_OUT(&err);
	}
}

static Dz1ShellCmdReturn _cmd_open_port2(void *task, int argc, char *argv[])
{
	_cmd_port_open2(task, argv[0], argc-1, &argv[1]);
	return Dz1ShellCmdReturn_ok;
}

static void _cmd_port_open3(void *task, str_t n, int argc, char *argv[])
{
//	if (argc < 2) _cmd_port_open_usage(n);
//	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		u32_t port = 9999;
		
		if (argc >= 2) port = (u32_t)atoi(argv[1]);

		if (port == 0 || port & 0xFFFF0000) Dz1Thread_printf("Port Number = 1 ~ 65535\n");
		else if ((err = Dz1TcpSocketServerTask_open3(task, port)).code) ERR_OUT(&err);
	}
}

static Dz1ShellCmdReturn _cmd_open_port3(void *task, int argc, char *argv[])
{
	_cmd_port_open3(task, argv[0], argc-1, &argv[1]);
	return Dz1ShellCmdReturn_ok;
}

static void _cmd_port_close_usage(str_t n) { Dz1Thread_printf("Usage] %s close <port_number>\n", n); }
static void _cmd_port_close(void *task, str_t n, int argc, char *argv[])
{
	if (argc >= 2 && (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0)) _cmd_port_close_usage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		u32_t port = 9999;
		if (argc >= 2) port = (u32_t)atoi(argv[1]);
		if (port == 0 || port & 0xFFFF0000) Dz1Thread_printf("Port Number = 1 ~ 65535\n");
		else if ((err = Dz1TcpSocketServerTask_close(task, port)).code) ERR_OUT(&err);
	}
}

static Dz1ShellCmdReturn _cmd_close_port(void *task, int argc, char *argv[])
{
	_cmd_port_close(task, argv[0], argc-1, &argv[1]);
	return Dz1ShellCmdReturn_ok;
}

static void _cmd_port_status(void *task, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1TcpSocketServerTask_status(task)).code) ERR_OUT(&err);
}

static void _cmd_port_usage(str_t n) { Dz1Thread_printf("Usage] %s open|close|status <parameters...>\n", n); }
static Dz1ShellCmdReturn _cmd_port(void *task, int argc, char *argv[])
{
	if (argc < 2) _cmd_port_usage(argv[0]);
	else if (strcmp(argv[1], "open") == 0 || strcmp(argv[1], "o") == 0) _cmd_port_open(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "open2") == 0 || strcmp(argv[1], "o2") == 0) _cmd_port_open2(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "open3") == 0 || strcmp(argv[1], "o3") == 0) _cmd_port_open3(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "close") == 0 || strcmp(argv[1], "c") == 0) _cmd_port_close(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "status") == 0 || strcmp(argv[1], "s") == 0) _cmd_port_status(task, argv[0], argc-1, &argv[1]);
	else _cmd_port_usage(argv[0]);

	return Dz1ShellCmdReturn_ok;
}

static void _shell_start(void *task)
{	
	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "TcpEchoServer", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "TcpProxy", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "port", _cmd_port, task, "TCP Server port management")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "o", _cmd_open_port, task, "TCP Server port open")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "o2", _cmd_open_port2, task, "TCP Server port open(close immediatly)")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "o3", _cmd_open_port3, task, "TCP Server port open(ssl negotiation and close)")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "c", _cmd_close_port, task, "close opened port")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

int main(void)
{
	void *task = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_tcp_socket_server.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
#ifdef _DZ1_USE_SSL
#if 1
	Dz1SocketCallback2SSL_init();
	pthread_cleanup_push(Dz1SocketCallback2SSL_initCancel, NULL);
#endif
#endif
	if ((err = Dz1SocketCallback2_init()).code) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1SocketCallback2_initCancel, NULL);
		if ((task = Dz1TcpSocketServerTask_new(&err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&task);
			if ((err = Dz1Task_start(task, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Dz1Task_startCancel, (void *)task);
				// Edit Task Argument
				_shell_start(task);
				pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)task);
			}
			pthread_cleanup_pop(1); // (Dz1Task_delAndSetNull, (void *)&task);
		}
		pthread_cleanup_pop(1); // (Dz1SocketCallback2_initCancel, NULL);
	}
#ifdef _DZ1_USE_SSL
#if 1
	pthread_cleanup_pop(1); // (Dz1SocketCallback2SSL_initCancel, NULL);
#endif
#endif
#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#ifdef _DEBUG
#if (_MSC_VER < 1930)
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
#endif
#endif
	return err.code;
}
