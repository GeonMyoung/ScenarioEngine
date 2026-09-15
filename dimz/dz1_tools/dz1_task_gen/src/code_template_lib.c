#include "code_template.h"

///////////////////////////////////////////////////////////////////////////////
// {project_name}{def_suffix}.tdc
Dz1Str lib_def2[] = {
Dz1T("message set definition"),
Dz1T("{"),
Dz1T("	include libdz1_support;"),
Dz1T("	typedef struct [[PROJ_STRUCT_NAME]]"),
Dz1T("	{"),
Dz1T("		int32		dummy;"),
Dz1T("	} [[PROJ_STRUCT_NAME]];"),
Dz1T("}"),
NULL
};
// {project_name}{def_suffix}.tdc
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {project_name}.h
Dz1Str lib_main_hdr2[] =
{
Dz1T("#ifndef [[PROJ_HDR_DEFINE]]_H"),
Dz1T("#define [[PROJ_HDR_DEFINE]]_H"),
Dz1T(""),
Dz1T("#include <[[PROJ_TDC_NAME]].h>"),
Dz1T(""),
Dz1T("// declare library functions here"),
Dz1T(""),
Dz1T("#endif // [[PROJ_HDR_DEFINE]]_H"),
NULL
};
// {project_name}.h
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {project_name}.c
Dz1Str lib_main_src2[] =
{
Dz1T("#include <[[PROJ_NAME]].h>"),
Dz1T(""),
Dz1T("// implement library functions here"),
NULL
};
// {project_name}.c
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {project_name}{test_suffix}.c
Dz1Str lib_test_src2[] = {
Dz1T("#include <dz1_cleanup.h>"),
Dz1T("#include <dz1_thread_log.h>"),
Dz1T("#include <dz1_shell.h>"),
Dz1T("#include <dz1_str.h>"),
Dz1T("#include <dz1_socket.h>"),
Dz1T("//#include <[[PROJ_NAME]].h>"),
Dz1T(""),
Dz1T("#ifndef UNIX_SYSTEM"),
Dz1T("#include <TCHAR.h>"),
Dz1T("#endif // UNIX_SYSTEM"),
Dz1T(""),
Dz1T("static FILE *logfp = NULL;"),
Dz1T("static void _outputHook(void *ptr, unsigned char *data, size_t size)"),
Dz1T("{"),
Dz1T("	if (logfp != NULL)"),
Dz1T("	{"),
Dz1T("		fwrite(data, size, 1, logfp);"),
Dz1T("		fflush(logfp);"),
Dz1T("	}"),
Dz1T("}"),
Dz1T("static void _memoryExport(void *ptr) { if (logfp) Dz1Mem_export(logfp, TRUE); }"),
Dz1T(""),
Dz1T("static void _shell_start(void *task)"),
Dz1T("{"),
Dz1T("	void *sh = NULL;"),
Dz1T("	DZ1_ERROR_SAFE_VAR(errp, err);"),
Dz1T(""),
Dz1T("#ifndef UNIX_SYSTEM"),
Dz1T("	if ((sh = Dz1Shell_new(Dz1Text(\"win32crt\"), DZ1_SHELL_CMD_ALL, 16, Dz1Text(\"root\"), Dz1Text(\"[[PROJ_STRUCT_NAME]]\"), errp)) == NULL) ERR_OUT(errp);"),
Dz1T("#else"),
Dz1T("	if ((sh = Dz1Shell_new(Dz1Text(\"xterm\"), DZ1_SHELL_CMD_ALL, 16, Dz1Text(\"root\"), Dz1Text(\"[[PROJ_STRUCT_NAME]]\"), errp)) == NULL) ERR_OUT(errp);"),
Dz1T("#endif"),
Dz1T("	else"),
Dz1T("	{"),
Dz1T("		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);"),
Dz1T("		if (0) { }"),
Dz1T("		//else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text(\"command_name\"), command_func, task, Dz1Text(\"command_description\") )).code) ERR_OUT(errp);"),
Dz1T("		else"),
Dz1T("		{"),
Dz1T("			Dz1Shell_start(sh, NULL);"),
Dz1T("		}"),
Dz1T(""),
Dz1T("		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);"),
Dz1T("	}"),
Dz1T("}"),
Dz1T(""),
Dz1T("#ifndef UNIX_SYSTEM"),
Dz1T("int _tmain(int argc, TCHAR *argv[])"),
Dz1T("#else // UNIX_SYSTEM"),
Dz1T("int main(int argc, char *argv[])"),
Dz1T("#endif // UNIC_SYSTEM"),
Dz1T("{"),
Dz1T("	DZ1_ERROR_SAFE_VAR(errp, err);"),
Dz1T("	Dz1Cleanup_init();"),
Dz1T(""),
Dz1T("	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);"),
Dz1T("	if ((logfp = Dz1FileStream_open(Dz1Text(\"[[PROJ_NAME]]Test.log.txt\"), Dz1Text(\"wb\"), NULL)) != NULL)"),
Dz1T("	{"),
Dz1T("		fwrite(DZ1_SYSTEM_CHARSET_BOM, DZ1_SYSTEM_CHARSET_BOM_SZ, 1, logfp);"),
Dz1T("		Dz1OutputHook_set(_outputHook, NULL);"),
Dz1T("	}"),
Dz1T(""),
Dz1T("	if (Dz1Socket_init() == FALSE) { Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, \"Win sock Initialize Fail\\n\"); return EFAULT; }"),
Dz1T("	else _shell_start(NULL);"),
Dz1T(""),
Dz1T("	Dz1Socket_cleanup();"),
Dz1T(""),
Dz1T("#ifdef _DEBUG"),
Dz1T("#ifdef UNICODE"),
Dz1T("	wprintf(L\"Press Any Key...\\n\");"),
Dz1T("#else"),
Dz1T("	printf(\"Press Any Key...\\n\");"),
Dz1T("#endif // UNICODE"),
Dz1T("	Dz1Thread_getch(-1, NULL);"),
Dz1T("#endif // _DEBUG"),
Dz1T("	return errp->code;"),
Dz1T("}"),
NULL
};
// {project_name}{test_suffix}.c
///////////////////////////////////////////////////////////////////////////////

