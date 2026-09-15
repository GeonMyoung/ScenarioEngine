#include <dz1_cleanup.h>
#include <dz1_str.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <Dz1CodeGen.h>

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

static Dz1ShellCmdReturn cmd_t(void *ptr, int argc, char *argv[])
{
	str_t str = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1CodeGen_listGen(&str, Dz1CodeGenListType_addNode, "MyList", "dst", "MyEntry")).code) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&str);
		Dz1Thread_printf("%s", str);
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&str);
	}
	return Dz1ShellCmdReturn_ok;
}

static void _shell_start(void *task)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_code_gen", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_code_gen", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push(Dz1Shell_del, (void *)sh);

		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "t", cmd_t, task, "test code generation")).code) ERR_OUT(&err);
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
	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_code_genTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif

	_shell_start(NULL);


#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
#endif
	return err.code;
}
