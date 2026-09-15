#include "code_template.h"

///////////////////////////////////////////////////////////////////////////////
// {project_name}{def_suffix}.tdc
Dz1Str task_def2[] = {
Dz1T("message set definition"),
Dz1T("{"),
Dz1T("	include libdz1_support;"),
Dz1T("	typedef func void [[PROJ_STRUCT_NAME]]Exception(void *exceptionArg, Dz1Error *reason);"),
Dz1T("	-- [[PROJ_STRUCT_NAME]]Def structure declared for Linker warning"),
Dz1T("	typedef struct [[PROJ_STRUCT_NAME]]Def"),
Dz1T("	{"),
Dz1T("		int32		dummy;"),
Dz1T("	} [[PROJ_STRUCT_NAME]]Def;"),
Dz1T("	-- if you declare other structure on this file, then delete [[PROJ_STRUCT_NAME]]Def structure"),
Dz1T("}"),
NULL
};
// {project_name}{def_suffix}.tdc
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {proj_name}.h
Dz1Str task_main_hdr2[] = {
Dz1T("#ifndef [[PROJ_HDR_DEFINE]]_H"),
Dz1T("#define [[PROJ_HDR_DEFINE]]_H"),
Dz1T(""),
Dz1T("#include <[[PROJ_TDC_NAME]].h>"),
Dz1T(""),
Dz1T("DZ1_CPPLINK void *[[PROJ_STRUCT_NAME]]_new([[PROJ_STRUCT_NAME]]Exception exceptionProc, void *exceptionArg, Dz1Error *err);"),
Dz1T("DZ1_CPPLINK void [[PROJ_STRUCT_NAME]]_del(void *task);"),
Dz1T(""),
Dz1T("#endif // [[PROJ_HDR_DEFINE]]"),
NULL
};
// {proj_name}.h
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {project_name}{arg_suffix}.tdc
Dz1Str task_arg_def2[] = {
Dz1T("message set definition"),
Dz1T("{"),
Dz1T("	include [[PROJ_TDC_NAME]];"),
Dz1T("	typedef struct [[STRUCT_ARG_NAME]]"),
Dz1T("	{"),
Dz1T("		[[PROJ_STRUCT_NAME]]Exception exceptionProc;"),
Dz1T("		void *exceptionArg;"),
Dz1T("	} [[STRUCT_ARG_NAME]];"),
Dz1T("}"),
NULL
};
// {project_name}{arg_suffix}.tdc
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {project_name}{env_suffix}.tdc
Dz1Str task_env_def2[] = {
Dz1T("message set definition"),
Dz1T("{"),
Dz1T("	include [[PROJ_TDC_NAME]];"),
Dz1T("	typedef struct [[STRUCT_ENV_NAME]]"),
Dz1T("	{"),
Dz1T("		void *tSelf;"),
Dz1T("	} [[STRUCT_ENV_NAME]];				// with api dump"),
Dz1T("}"),
NULL
};
// {project_name}{env_suffix}.tdc
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {porj_name}{tmr_suffix}.tdc
Dz1Str task_timer_def2[] = {
Dz1T("message set definition"),
Dz1T("{"),
Dz1T("	include [[PROJ_TDC_NAME]];"),
Dz1T("	typedef struct [[STRUCT_TMR_NAME]]"),
Dz1T("	{"),
Dz1T("		uint32 id; // is key"),
Dz1T("	} [[STRUCT_TMR_NAME]]; // with api dump, compare"),
Dz1T("}"),
NULL
};
// {porj_name}{tmr_suffix}.tdc
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {porj_name}{tmr_util_suffix}.h
Dz1Str task_timer_util_hdr2[] = {
Dz1T("#ifndef [[PROJ_HDR_DEFINE]]_TIMER_UTIL_H_LOCAL"),
Dz1T("#define [[PROJ_HDR_DEFINE]]_TIMER_UTIL_H_LOCAL"),
Dz1T(""),
Dz1T("#include <dz1_task.h>"),
Dz1T("#include \"[[PROJ_TMR_NAME]].h\""),
Dz1T(""),
Dz1T("DZ1_CPPLINK Dz1Error [[STRUCT_TMR_NAME]]_set(void *timer, [[STRUCT_TMR_NAME]] **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);"),
Dz1T("DZ1_CPPLINK Dz1Error [[STRUCT_TMR_NAME]]_update(void *timer, [[STRUCT_TMR_NAME]] **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);"),
Dz1T("DZ1_CPPLINK void [[STRUCT_TMR_NAME]]_clr(void *timer, [[STRUCT_TMR_NAME]] *key);"),
Dz1T(""),
Dz1T("#endif	// [[PROJ_HDR_DEFINE]]_TIMER_UTIL_H_LOCAL"),
NULL
};
// {porj_name}{tmr_util_suffix}.h
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {porj_name}{tmr_util_suffix}.c
Dz1Str task_timer_util_src2[] = {
Dz1T("#include <dz1_task_timer.h>"),
Dz1T("#include \"[[PROJ_TMR_UTIL_NAME]].h\""),
Dz1T(""),
Dz1T("Dz1Error [[STRUCT_TMR_NAME]]_set(void *timer, [[STRUCT_TMR_NAME]] **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)"),
Dz1T("{"),
Dz1T("	DZ1_ERROR_SAFE_VAR(errp, err);"),
Dz1T("	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)[[STRUCT_TMR_NAME]]_del, timeout, FALSE)).code) ERR_OUT(errp);"),
Dz1T("	return err;"),
Dz1T("}"),
Dz1T(""),
Dz1T("Dz1Error [[STRUCT_TMR_NAME]]_update(void *timer, [[STRUCT_TMR_NAME]] **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)"),
Dz1T("{"),
Dz1T("	DZ1_ERROR_SAFE_VAR(errp, err);"),
Dz1T("	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)[[STRUCT_TMR_NAME]]_del, timeout, TRUE)).code) ERR_OUT(errp);"),
Dz1T("	return err;"),
Dz1T("}"),
Dz1T(""),
Dz1T("void [[STRUCT_TMR_NAME]]_clr(void *timer, [[STRUCT_TMR_NAME]] *key)"),
Dz1T("{"),
Dz1T("	Dz1TaskTimer_dereg(timer, (void *)key);"),
Dz1T("}"),
NULL
};
// {porj_name}{tmr_util_suffix}.c
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {porj_name}{msg_suffix}.h
Dz1Str task_msg_hdr2[] = {
Dz1T("#ifndef [[PROJ_HDR_DEFINE]]_MSG_H_LOCAL"),
Dz1T("#define [[PROJ_HDR_DEFINE]]_MSG_H_LOCAL"),
Dz1T(""),
Dz1T("#define [[PROJ_HDR_DEFINE]]_CORE_MSG			0xF0000000"),
Dz1T("#define [[PROJ_HDR_DEFINE]]_DO_DEFAULT			([[PROJ_HDR_DEFINE]]_CORE_MSG | 0x00000001)"),
Dz1T(""),
Dz1T("#include \"[[PROJ_MSGS_NAME]].h\""),
Dz1T(""),
Dz1T("#endif // [[PROJ_HDR_DEFINE]]_MSG_H_LOCAL"),
NULL
};
// {porj_name}{msg_suffix}.h
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {porj_name}{msgs_suffix}.h
Dz1Str task_msgs_def2[] = {
Dz1T("message set definition"),
Dz1T("{"),
Dz1T("	include [[PROJ_TDC_NAME]];"),
Dz1T("	typedef struct [[PROJ_STRUCT_NAME]]MsgDefault"),
Dz1T("	{"),
Dz1T("		uint32 *dummy;"),
Dz1T("	} [[PROJ_STRUCT_NAME]]MsgDefault;					// with api dump"),
Dz1T("}"),
NULL
};
// {porj_name}{msgs_suffix}.h
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {proj_name}.c
Dz1Str task_main_src2[] = {
Dz1T("#include <dz1_task.h>"),
Dz1T(""),
Dz1T("#include \"[[PROJ_ARG_NAME]].h\""),
Dz1T("#include \"[[PROJ_ENV_NAME]].h\""),
Dz1T("#include \"[[PROJ_TMR_UTIL_NAME]].h\""),
Dz1T("#include \"[[PROJ_MSG_NAME]].h\""),
Dz1T(""),
Dz1T("#include <[[PROJ_NAME]].h>"),
Dz1T(""),
Dz1T("static Dz1Error [[PROJ_STRUCT_NAME]]_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)"),
Dz1T("{"),
Dz1T("	DZ1_ERROR_SAFE_VAR(errp, err);"),
Dz1T("	//[[STRUCT_ARG_NAME]] *arg = ([[STRUCT_ARG_NAME]] *)uArg;"),
Dz1T("	[[STRUCT_ENV_NAME]] *env = NULL;"),
Dz1T(""),
Dz1T("	if (((*uRsc) = env = [[STRUCT_ENV_NAME]]_new(tSelf, errp)) == NULL) ERR_OUT(errp);"),
Dz1T("	else"),
Dz1T("	{"),
Dz1T("		pthread_cleanup_push([[STRUCT_ENV_NAME]]_delAndSetNull,(void *)uRsc);"),
Dz1T("		if (0) { }"),
Dz1T("		else"),
Dz1T("		{"),
Dz1T("			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, [[PROJ_HDR_DEFINE]]_DO_DEFAULT);"),
Dz1T("			Dz1Error_set(errp, 0);"),
Dz1T("		}"),
Dz1T("		pthread_cleanup_pop(errp->code); // ([[STRUCT_ENV_NAME]]_delAndSetNull,(void *)uRsc);"),
Dz1T("	}"),
Dz1T(""),
Dz1T("	return err;"),
Dz1T("}"),
Dz1T(""),
Dz1T("static void [[PROJ_STRUCT_NAME]]_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)"),
Dz1T("{"),
Dz1T("	[[STRUCT_ARG_NAME]] *arg = ([[STRUCT_ARG_NAME]] *)uArg;"),
Dz1T("	if (arg->exceptionProc)"),
Dz1T("		arg->exceptionProc(arg->exceptionArg, reason);"),
Dz1T("}"),
Dz1T(""),
Dz1T("static void [[PROJ_STRUCT_NAME]]_cleanup(void *uRsc)"),
Dz1T("{"),
Dz1T("	[[STRUCT_ENV_NAME]] *env = ([[STRUCT_ENV_NAME]] *)uRsc;"),
Dz1T("	// Individual Cleanup Code Here"),
Dz1T("	[[STRUCT_ENV_NAME]]_del(env);"),
Dz1T("}"),
Dz1T(""),
Dz1T("static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)"),
Dz1T("{	// Task work starting point"),
Dz1T("	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;"),
Dz1T("	// [[STRUCT_ARG_NAME]] *arg = ([[STRUCT_ARG_NAME]] *)uArg;"),
Dz1T("	// [[STRUCT_ENV_NAME]] *env = ([[STRUCT_ENV_NAME]] *)uRsc;"),
Dz1T(""),
Dz1T("	return ret;"),
Dz1T("}"),
Dz1T(""),
Dz1T("void *[[PROJ_STRUCT_NAME]]_new([[PROJ_STRUCT_NAME]]Exception e, void *eArg, Dz1Error *err)"),
Dz1T("{"),
Dz1T("	void *ret = NULL;"),
Dz1T("	DZ1_ERROR_SAFE_PTR(errp, err);"),
Dz1T("	[[STRUCT_ARG_NAME]] *arg = [[STRUCT_ARG_NAME]]_new(e, eArg, errp);"),
Dz1T("	if (arg == NULL) ERR_OUT(errp);"),
Dz1T("	else"),
Dz1T("	{"),
Dz1T("		pthread_cleanup_push([[STRUCT_ARG_NAME]]_delAndSetNull, (void *)&arg);"),
Dz1T("		if ((ret = Dz1Task_new(\"[[PROJ_STRUCT_NAME]]\" , 1024,"),
Dz1T("							   (void **)&arg, (Dz1DelFunc)[[STRUCT_ARG_NAME]]_del,"),
Dz1T("							   (Dz1CmpFunc)[[STRUCT_TMR_NAME]]_cmp,"),
Dz1T("							   [[PROJ_STRUCT_NAME]]_init,"),
Dz1T("							   [[PROJ_STRUCT_NAME]]_exception,"),
Dz1T("							   [[PROJ_STRUCT_NAME]]_cleanup, errp)) == NULL) ERR_OUT(errp);"),
Dz1T("		else"),
Dz1T("		{"),
Dz1T("			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);"),
Dz1T("			if (0) { }"),
Dz1T("			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT([[PROJ_HDR_DEFINE]]_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);"),
Dz1T("			else"),
Dz1T("			{"),
Dz1T("				Dz1Error_set(errp, 0);"),
Dz1T("			}"),
Dz1T("			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);"),
Dz1T("		}"),
Dz1T("		pthread_cleanup_pop(1); // ([[STRUCT_ARG_NAME]]_delAndSetNull, (void *)&arg);"),
Dz1T("	}"),
Dz1T("	return ret;"),
Dz1T("}"),
Dz1T(""),
Dz1T("void [[PROJ_STRUCT_NAME]]_del(void *task)"),
Dz1T("{"),
Dz1T("	DZ1_ERROR_SAFE_VAR(errp, err);"),
Dz1T(""),
Dz1T("	if (task == NULL) return;"),
Dz1T("	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);"),
Dz1T("}"),
NULL
};
// {proj_name}.c
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {proj_name}{test_suffix}.c
Dz1Str task_test_src2[] = {
Dz1T("#include <dz1_cleanup.h>"),
Dz1T("#include <dz1_thread_log.h>"),
Dz1T("#include <dz1_usleep.h>"),
Dz1T("#include <dz1_shell.h>"),
Dz1T("#include <dz1_str.h>"),
Dz1T("#include <dz1_socket.h>"),
Dz1T("#include <[[PROJ_NAME]].h>"),
Dz1T(""),
Dz1T("#ifndef UNIX_SYSTEM"),
Dz1T("#include <TCHAR.h>"),
Dz1T("#endif // UNIX_SYSTEM"),
Dz1T(""),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
Dz1T("// Log-File"),
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
Dz1T("// Log-File"),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
Dz1T(""),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
Dz1T("// Test-Env"),
Dz1T("typedef struct TestEnv"),
Dz1T("{"),
Dz1T("	void					*task;"),
Dz1T("} TestEnv;"),
Dz1T("static void TestEnv_cleanup(void *ptr)"),
Dz1T("{"),
Dz1T("	TestEnv *env = (TestEnv *)ptr;"),
Dz1T("	Dz1Task_delAndSetNull(&env->task);"),
Dz1T("}"),
Dz1T("// Test-Env"),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
Dz1T(""),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
Dz1T("// Shell"),
Dz1T("static void _shell_start(void *task)"),
Dz1T("{"),
Dz1T("	void *sh = NULL;"),
Dz1T("	DZ1_ERROR_SAFE_VAR(errp, err);"),
Dz1T(""),
Dz1T("#ifdef WIN32"),
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
Dz1T("// Shell"),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
Dz1T(""),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
Dz1T("// Process-Entry"),
Dz1T("static void _task_exception_handler(void *ptr, Dz1Error *reason)"),
Dz1T("{"),
Dz1T("	Dz1Thread_log(DZ1_THREAD_LOG_ERROR, \"[[PROJ_STRUCT_NAME]] : Exception Catch\\n\");"),
Dz1T("	ERR_OUT(reason);"),
Dz1T("}"),
Dz1T(""),
Dz1T("static bool_t _process_start(bool_t is_daemon, Dz1Error *errp)"),
Dz1T("{"),
Dz1T("	Dz1Cleanup_init();"),
Dz1T("	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);"),
Dz1T("	if ((logfp = Dz1FileStream_open(Dz1Text(\"[[PROJ_TEST_NAME]].log.txt\"), Dz1Text(\"wb\"), NULL)) != NULL)"),
Dz1T("	{"),
Dz1T("		fwrite(DZ1_SYSTEM_CHARSET_BOM, DZ1_SYSTEM_CHARSET_BOM_SZ, 1, logfp);"),
Dz1T("		fflush(logfp);"),
Dz1T("		Dz1OutputHook_set(_outputHook, NULL);"),
Dz1T("	}"),
Dz1T(""),
Dz1T("	if (Dz1Socket_init() == FALSE) { Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, Dz1Text(\"Win sock Initialize Fail\\n\")); Dz1Error_set(errp, EFAULT); }"),
Dz1T("	else"),
Dz1T("	{"),
Dz1T("		TestEnv env = { NULL };"),
Dz1T("		pthread_cleanup_push(TestEnv_cleanup, (void *)&env);"),
Dz1T("		if ((env.task = [[PROJ_STRUCT_NAME]]_new(_task_exception_handler, NULL, errp)) == NULL) ERR_OUT(errp);	// Edit Task Argument"),
Dz1T("		else if ((*errp = Dz1Task_start(env.task, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(errp);"),
Dz1T("		else"),
Dz1T("		{"),
Dz1T("			pthread_cleanup_push(Dz1Task_startCancel, (void *)env.task);"),
Dz1T(""),
Dz1T("			if (is_daemon) { while(1) Dz1Thread_usleep(1000000); }"),
Dz1T("			else _shell_start((void *)&env);"),
Dz1T(""),
Dz1T("			pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)env.task);"),
Dz1T("		}"),
Dz1T("		pthread_cleanup_pop(1); // (TestEnv_cleanup, (void *)&env);"),
Dz1T("		Dz1Socket_cleanup();"),
Dz1T("	}"),
Dz1T(""),
Dz1T("#ifdef _DEBUG"),
Dz1T("	if (is_daemon == FALSE)"),
Dz1T("	{"),
Dz1T("		Dz1Thread_printf(\"press any key...\\n\");"),
Dz1T("		Dz1Thread_getch(-1, NULL);"),
Dz1T("	}"),
Dz1T("#endif // _DEBUG"),
Dz1T("	return errp->code == 0 ? TRUE : FALSE;"),
Dz1T("}"),
Dz1T("// Process-Entry"),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
Dz1T(""),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
Dz1T("// Main-Entry"),
Dz1T("#ifndef UNIX_SYSTEM"),
Dz1T("int _tmain(int argc, TCHAR *argv[])"),
Dz1T("#else // UNIX_SYSTEM"),
Dz1T("int main(int argc, char *argv[])"),
Dz1T("#endif // UNIC_SYSTEM"),
Dz1T("{"),
Dz1T("	DZ1_ERROR_SAFE_VAR(errp, err);"),
Dz1T(""),
Dz1T("	// parse argv, choice fork or shell"),
Dz1T("	_process_start(FALSE, errp);"),
Dz1T(""),
Dz1T("	return errp->code;"),
Dz1T("}"),
Dz1T("// Main-Entry"),
Dz1T("////////////////////////////////////////////////////////////////////////////////"),
NULL
};
// {proj_name}{test_suffix}.c
///////////////////////////////////////////////////////////////////////////////

