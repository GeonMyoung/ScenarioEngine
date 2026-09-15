#include <dz1_cleanup.h>
#include <dz1_thread_log.h>
#include <dz1_shell.h>
#include <dz1_str.h>
#include <dz1_socket.h>
#include <dz1_web_socket.h>
#include "dz1_web_socket_test_task.h"
#ifndef UNIX_SYSTEM
#include <TCHAR.h>
#endif // UNIX_SYSTEM

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

////////////////////////////////////////////////////////////////////////////////
// cmd_open Root Command
static void cmd_open_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s [<uri>]\n"), n); }
static Dz1ShellCmdReturn cmd_open(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_open_usage;
	Dz1Str n = argv[0];
	Dz1Task *env = (Dz1Task *)ptr;
	if (argc < 1 || argc > 2) _print_usage(n);
	else
	{
		int i;
		Dz1Str str = NULL;
		Dz1Asn1UTF8Str *uri = NULL;

		for (i = 1; errp->code == 0 && i < argc; i++)
		{
			str = argv[i];
			if (0) { }
			else if (uri != NULL) _print_usage(n);
			else if ((uri = Dz1Asn1UTF8Str_newFromStr(str, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		// Command Code Here
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&uri);

		if (errp->code) { }
		else if (uri == NULL && (uri = Dz1Asn1UTF8Str_newFromStr(Dz1T("ws://175.106.97.18:5000"), errp)) == NULL) ERR_OUT(errp);
		else if (Dz1WebSocketTask_open(env, uri, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&uri);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_open Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_close Root Command
static void cmd_close_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static Dz1ShellCmdReturn cmd_close(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_close_usage;
	Dz1Str n = argv[0];
	Dz1Task *env = (Dz1Task *)ptr;
	if (argc != 1) _print_usage(n);
	else
	{
		// Command Code Here
		if (errp->code) { }
		else if (Dz1WebSocketTask_close(env, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_close Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_ping Root Command
static void cmd_ping_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <text>\n"), n); }
static Dz1ShellCmdReturn cmd_ping(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_ping_usage;
	Dz1Str n = argv[0];
	Dz1Task *env = (Dz1Task *)ptr;
	Dz1Binary *bin = NULL;
	if (argc != 2) _print_usage(n);
	else if ((bin = Dz1Binary_new((u8_t *)argv[1], (u32_t)strlen(argv[1]), errp)) == NULL) ERR_OUT(errp);
	else
	{
		// Command Code Here
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		if (Dz1WebSocketTask_sendPing(env, bin, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_ping Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_msg Root Command
static char letter_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01234567890-=_+~`!@#$%^&*(){}[]|:;,./<>?";
static size_t letter_size = sizeof(letter_table) - 1;
static char *_mk_string(u32_t sz, Dz1Error *errp)
{
	char *ret = (char *)Dz1Malloc(sz + 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		int idx = 0;
		char *dp = ret;
		while(sz)
		{
			*dp++ = letter_table[idx++];
			idx %= letter_size;
			sz--;
		}
		*dp = 0;
	}
	return ret;
}

static void cmd_msg_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <size>\n"), n); }
static Dz1ShellCmdReturn cmd_msg(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_msg_usage;
	Dz1Str n = argv[0];
	Dz1Task *env = (Dz1Task *)ptr;
	if (argc != 2) _print_usage(n);
	else
	{
		Dz1Asn1UTF8Str *utf8 = NULL;
		u32_t size = Dz1StrTo32(argv[1]);
		char *src = NULL;
		if ((src = _mk_string(size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Memory_cancel, (void *)src);
			if ((utf8 = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
				if (Dz1WebSocketTask_sendText(env, utf8, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)src);
		}
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_msg Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_bin Root Command
static void cmd_bin_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <size>\n"), n); }
static Dz1ShellCmdReturn cmd_bin(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_bin_usage;
	Dz1Str n = argv[0];
	Dz1Task *env = (Dz1Task *)ptr;
	Dz1Binary *bin = NULL;
	if (argc != 2) _print_usage(n);
	else
	{
		u32_t len = Dz1StrTo32(argv[1]);
		if ((bin = Dz1Binary_new(DZ1_BIN_DATA_ALLOC,len, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			u8_t *dp = NULL;
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			for (i = 0, dp = bin->data; i < len; i++, dp++) *dp = (u8_t)(i % 0xFF);

			if (Dz1WebSocketTask_sendBin(env, bin, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_bin Root Command
////////////////////////////////////////////////////////////////////////////////

static void _shell_start(void *task)
{
	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifndef UNIX_SYSTEM
	if ((sh = Dz1Shell_new(Dz1Text("win32crt"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("Dz1WebSocket"), errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new(Dz1Text("xterm"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("Dz1WebSocket"), errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("open"), cmd_open, task, Dz1Text("Open Web Socket Session") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("close"), cmd_close, task, Dz1Text("Close Web Socket Session") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("ping"), cmd_ping, task, Dz1Text("Send PING Frame") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("msg"), cmd_msg, task, Dz1Text("Send TEXT Frame") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("bin"), cmd_bin, task, Dz1Text("Send BINARY Frame") )).code) ERR_OUT(errp);
		//else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("command_name"), command_func, task, Dz1Text("command_description") )).code) ERR_OUT(errp);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

static void _exception_cb(void *ptr, Dz1Error *reason)
{
	Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Exception !!!\n");
	ERR_OUT(reason);
}

static bool_t _process_start(void *ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Task *task = NULL;
	if ((task = Dz1WebSocketTask_create(_exception_cb, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&task);
		if ((*errp = Dz1Task_start(task, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_MESSAGE | DZ1_THREAD_LOG_DEBUG)).code) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_startCancel, (void *)task);
			_shell_start(task);
			pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)task);
		}
		pthread_cleanup_pop(1); // (Dz1Task_delAndSetNull, (void *)&task);
	}
	return ERR_IS_SUCCESS(errp);
}

#ifndef UNIX_SYSTEM
int _tmain(int argc, TCHAR *argv[])
#else // UNIX_SYSTEM
int main(int argc, char *argv[])
#endif // UNIC_SYSTEM
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = Dz1FileStream_open(Dz1Text("dz1_web_socketTest.log.txt"), Dz1Text("wb"), NULL)) != NULL)
	{
		fwrite(DZ1_SYSTEM_CHARSET_BOM, DZ1_SYSTEM_CHARSET_BOM_SZ, 1, logfp);
		Dz1OutputHook_set(_outputHook, NULL);
	}

	if (Dz1Socket_init() == FALSE) { Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "Win sock Initialize Fail\n"); return EFAULT; }
	else
	{
		pthread_cleanup_push(Dz1Socket_initCancel, NULL);
		if ((*errp = Dz1SocketCallback2_init()).code) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1SocketCallback2_initCancel, NULL);
			if ((*errp = Dz1SocketCallback2SSL_init()).code) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1SocketCallback2SSL_initCancel, NULL);
				_process_start(NULL, errp);
				pthread_cleanup_pop(1); // (Dz1SocketCallback2SSL_initCancel, NULL);
			}
			pthread_cleanup_pop(1); // (Dz1SocketCallback2_initCancel, NULL);
		}
		pthread_cleanup_pop(1); // (Dz1Socket_initCancel, NULL);
	}

#ifdef _DEBUG
#ifdef UNICODE
	wprintf(L"Press Any Key...\n");
#else
	printf("Press Any Key...\n");
#endif // UNICODE
	Dz1Thread_getch(-1, NULL);
#endif // _DEBUG
	return errp->code;
}
