#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_logics.h>

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

static bool_t _test_(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	bool_t result = FALSE;
	s32_t v32 = 99;
	Dz1LogicMatchNumSimple num_simple = { 100, Dz1LogicMatchType_LessThen };
	Dz1LogicMatchNum num_match = { Dz1LogicMatchNumPresent_simple, { &num_simple } };
	Dz1LogicMatch match = { Dz1LogicMatchAPresent_number, { &num_match } };

	Dz1Thread_printf(Dz1T("match =")); Dz1LogicMatch_dump(&match, 0);
	Dz1Thread_printf(Dz1T("value = %d\n"), v32);
	if ((*errp = Dz1Logics_express(Dz1LogicMatchValueType_Signed32, &v32, &match, &result)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf(Dz1T("result = %d\n"), result);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static void _shell_start(void *task)
{	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_logics", errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_logics", errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);

		_test_(errp);
		if (0) { }
		//else if ((*errp = Dz1Shell_cmdReg(sh, "{command}", {command_func}, task, "{command description}")).code) ERR_OUT(errp);
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
	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_logicsTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init() == FALSE) { Dz1Thread_printf("Win sock Initialize Fail\n"); return EFAULT; }
#endif

	_shell_start(NULL);


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
