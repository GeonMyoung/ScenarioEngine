#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_str.h>
#include <dz1_syslogr.h>

#ifdef _DEBUG
#include <conio.h>
#endif

typedef struct TestEnv
{
	Dz1SyslogR		 *dst;
} TestEnv;

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
static void _cmd_open_usage(str_t n) { Dz1Thread_printf("Usage] %s [<server_addr_url> [<port>]]\n", n); }
static Dz1ShellCmdReturn _cmd_open(void *ptr, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv *env = (TestEnv *)ptr;
	if (env->dst != NULL) ERR_SET_OUT(errp, EEXIST);
	if (argc < 1 || argc > 3) _cmd_open_usage(argv[0]);
	else
	{
		Dz1Str addr = Dz1Text("192.168.75.128");
		u16_t port = 514;

		if (argc >= 2) addr = argv[1];
		if (argc >= 3) port = (u16_t)(Dz1StrTo32(argv[2]) & 0xFFFF);

		if ((env->dst = Dz1SyslogR_new(addr, port, DZ1_SYSLOGR_F_USER, DZ1_SYSLOGR_PF_ALL, errp)) == NULL) ERR_OUT(errp);
		else 
		{
			Dz1Thread_printf("remote syslog = "); Dz1SyslogR_dump(env->dst, 0);
			Dz1Error_set(errp, 0);
		}
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_open Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// _cmd_close Root Command
static void _cmd_close_usage(str_t n) { Dz1Thread_printf("Usage] %s\n", n); }
static Dz1ShellCmdReturn _cmd_close(void *ptr, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv *env = (TestEnv *)ptr;
	if (env->dst == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (argc != 1) _cmd_close_usage(argv[0]);
	else
	{
		Dz1SyslogR_delAndSetNull(&env->dst);
	}
	return Dz1ShellCmdReturn_ok;
}
// _cmd_close Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// _cmd_log Root Command
static u32_t cnt = 0;
static void _cmd_log_usage(str_t n) { Dz1Thread_printf("Usage] %s [<pri>] <message>\n", n); }
static Dz1ShellCmdReturn _cmd_log(void *ptr, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv *env = (TestEnv *)ptr;
	if (env->dst == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (argc < 2 || argc > 3) _cmd_log_usage(argv[0]);
	else 
	{
		Dz1SyslogPri pri = Dz1SyslogPri_DEBUG;
		Dz1Str msg = "";

		switch(argc)
		{
		case 3:
			if ((pri = Dz1SyslogPriFromStr(argv[1])) == Dz1SyslogPri_max) ERR_SET_OUT(errp, EINVAL);
			else Dz1SyslogR_log(env->dst, pri, Dz1Text("Test Log %s %u"), argv[2], cnt++);
			break;
		case 2:
			Dz1SyslogR_log(env->dst, pri, Dz1Text("Test Log %s %u"), argv[1], cnt++);
			break;
		default:
			break;
		}
	}
	return Dz1ShellCmdReturn_ok;
}
// _cmd_log Root Command
////////////////////////////////////////////////////////////////////////////////


static void _shell_start(void *ptr)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_parser_util", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_parser_util", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "open", _cmd_open, ptr, "open remote syslog")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "close", _cmd_close, ptr, "close remote syslog")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "log", _cmd_log, ptr, "write syslog")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

int main(int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv env = { NULL };

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_syslogTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif

	_shell_start((void *)&env);



#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#endif

#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
	return err.code;
}
