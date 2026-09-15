#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_todec.h>

#include "sample_test.h"

#ifdef _DEBUG
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

typedef struct TestEnv
{
	Dz1MdefcModule			*module;
	Dz1Todec				*todec;
	TodecAnalysisData		*analysis;
} TestEnv;

static void TestEnv_cleanup(void *ptr)
{
	TestEnv *p = (TestEnv *)ptr;
	TodecAnalysisData_delAndSetNull(&p->analysis);
	Dz1Todec_delAndSetNull(&p->todec);
	Dz1MdefcModule_delAndSetNull(&p->module);
}

////////////////////////////////////////////////////////////////////////////////
// cmd_conv Root Command
static void cmd_conv_usage(str_t n) { Dz1Thread_printf("Usage] %s <args...>\n", n); }
static Dz1ShellCmdReturn cmd_conv(void *ptr, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
//	TestEnv *env = (TestEnv *)ptr;
	if (argc < 1 || argc > 1) cmd_conv_usage(argv[0]);
	else if ((*errp = Dz1Todec_convert("..\\..", "sample", Dz1TodecTargetCodecMode_public, "..\\..", "_stream", "_stream")).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return Dz1ShellCmdReturn_ok;
}
// cmd_conv Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_pub Root Command
static void cmd_pub_usage(str_t n) { Dz1Thread_printf("Usage] %s <args...>\n", n); }
static Dz1ShellCmdReturn cmd_pub(void *ptr, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
//	TestEnv *env = (TestEnv *)ptr;
	Dz1TodecPubArg pub_arg = { 
		"..\\..",				// Module Include Path 
		"..\\..", "..\\..", 	// {path}/sample_stream.c, {path}/sample_stream.h
		TRUE, TRUE
	}; 
	if (argc < 1 || argc > 1) cmd_pub_usage(argv[0]);
	else if ((*errp = Dz1Todec_publish("..\\..", "sample_stream", "todec", &pub_arg, "Stream")).code) ERR_OUT(errp);
	return Dz1ShellCmdReturn_ok;
}
// cmd_pub Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_codec Root Command
static void cmd_codec_usage(Dz1Str n)
{
	Dz1Thread_printf(Dz1Text("Usage] %s <name|idx|all>\n"), n);
	sample_test_dump(1);
}
static Dz1ShellCmdReturn cmd_codec(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_codec_usage;
	Dz1Str n = argv[0];
	if (argc != 2) _print_usage(n);
	else
	{
		// Command Code Here
		if (errp->code) { }
		else if (Dz1Str_isDigitStr(argv[1]))
		{
			u32_t idx = Dz1StrTo32(argv[1]);
			if (sample_test_by_idx(idx, TRUE, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], "all") == 0) { }
		else if (sample_test_by_name(argv[1], TRUE, errp) == FALSE)
		{
			if (errp->code == ENOSYS) _print_usage(n);
			else ERR_OUT(errp);
		}
		else _print_usage(n);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_codec Root Command
////////////////////////////////////////////////////////////////////////////////

static void _shell_start(void *task)
{	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_todec", errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_todec", errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		//else if ((*errp = Dz1Shell_cmdReg(sh, "{command}", {command_func}, task, "{command description}")).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, "conv", cmd_conv, task, "convert TDC module to TODEC")).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, "pub", cmd_pub, task, "Publish CODEC source/header")).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, "c", cmd_codec, task, "CODEC test")).code) ERR_OUT(errp);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

int main(int argc, char *argv[])
{
	TestEnv env = { NULL, };
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_todecTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init() == FALSE) { Dz1Thread_printf("Win sock Initialize Fail\n"); return EFAULT; }
#endif

	pthread_cleanup_push(TestEnv_cleanup, (void *)&env);
	_shell_start((void *)&env);
	pthread_cleanup_pop(1); // (TestEnv_cleanup, (void *)&env);

#ifndef UNIX_SYSTEM
	Dz1Socket_cleanup();
#endif
#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
	return errp->code;
}
