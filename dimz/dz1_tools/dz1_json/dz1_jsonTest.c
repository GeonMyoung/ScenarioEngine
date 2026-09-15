#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <Dz1Json.h>
#include "dz1_jsonTestDefJson.h"
#include "dz1_jsonTestUtil.h"

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

static __inline__ void _shell_start(void *task)
{	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_json", errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_json", errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
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

	Dz1JsonSpec *spec = NULL;
	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_jsonTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init() == FALSE) { Dz1Thread_printf("Win sock Initialize Fail\n"); return EFAULT; }
	else
	{
#endif
	test_line_mode = Dz1JsonNewLine_continuous;
	if ((spec = Dz1JsonSpec_generate(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&spec);
		if (0) { }
		else if (dz1_jsonTestDef_initJsonSpec(spec, errp) == FALSE) ERR_OUT(errp);
		else if (dz1_jsonTestTypes_initJsonSpec(spec, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(spec, errp) == FALSE) ERR_OUT(errp);

		else if ((*errp = Dz1Json_testReal32(spec)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Json_testReal64(spec)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Json_testBinary(spec)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Json_testString(spec)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Json_testStringList(spec)).code) ERR_OUT(errp);
 		else if ((*errp = Dz1Json_testMyStruct(spec)).code) ERR_OUT(errp);
 		else if ((*errp = Dz1Json_testMyUnion(spec)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Json_testMyStructList(spec)).code) ERR_OUT(errp);
 		else if ((*errp = Dz1Json_testMyUnionList(spec)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Json_testMyComponent(spec)).code) ERR_OUT(errp);
// 		else _shell_start(NULL);
		pthread_cleanup_pop(1); // (Dz1JsonSpec_delAndSetNull, (void *)&spec);
	}
#ifndef UNIX_SYSTEM
	Dz1Socket_cleanup();
	}
#endif
#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
	return errp->code;
}
