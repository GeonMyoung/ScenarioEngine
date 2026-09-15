#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include "dz1_shell_builtin_cmds.h"

///////////////////////////////////////////////////////////////////////////////
// Built-in Command : help
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdA_help(void *funcParam, int argc, char *argv[])
{
	Dz1ShellCmdA_dump((Dz1ShellCmdA *)funcParam, 0);
	return Dz1ShellCmdReturn_ok;
}
#ifndef UNIX_SYSTEM
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdW_help(void *funcParam, int argc, wchar_t *argv[])
{
	Dz1ShellCmdW_dump((Dz1ShellCmdW *)funcParam, 0);
	return Dz1ShellCmdReturn_ok;
}
#endif
// Built-in Command : help
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Built-in Command : exit
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdA_exit(void *funcParam, int argc, char *argv[])
{
	return Dz1ShellCmdReturn_exit;
}
#ifndef UNIX_SYSTEM
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdW_exit(void *funcParam, int argc, wchar_t *argv[])
{
	return Dz1ShellCmdReturn_exit;
}
#endif
// Built-in Command : exit
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Built-in Command : vars
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdA_vars(void *funcParam, int argc, char *argv[])
{
	Dz1ShellVarA *p = (Dz1ShellVarA *)funcParam;
	if (argc == 1)
	{
		Dz1ShellVarA_dump(p, 0);
		return Dz1ShellCmdReturn_ok;
	}
	else if (argc == 2)
	{
		str_t name = argv[1], cp = argv[1], value = NULL;
		do
		{
			if (*cp)
			{
				if (*cp == '\\') { cp++; continue; }
				else if (*cp == '=') break;
				cp++;
			}
			else { cp = NULL; break; }
		} while(1);

		if (cp)
		{
			Dz1Error err = DZ1_ERROR_INITIALIZER;

			*cp++ = '\0';
			value = cp;

			p->remove(p, name);
			if ((err = p->insert(p, name, value)).code) return Dz1ShellCmdReturn_max;
			else return Dz1ShellCmdReturn_ok;
		}
	}

	Dz1ThreadA_printf("Usage] %s <name>=<value>\n", argv[0]);
	return Dz1ShellCmdReturn_max;
}
#ifndef UNIX_SYSTEM
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdW_vars(void *funcParam, int argc, wchar_t *argv[])
{
	Dz1ShellVarW *p = (Dz1ShellVarW *)funcParam;
	if (argc == 1)
	{
		Dz1ShellVarW_dump(p, 0);
		return Dz1ShellCmdReturn_ok;
	}
	else if (argc == 2)
	{
		wstr_t name = argv[1], cp = argv[1], value = NULL;
		do
		{
			if (*cp)
			{
				if (*cp == L'\\') { cp++; continue; }
				else if (*cp == L'=') break;
				cp++;
			}
			else { cp = NULL; break; }
		} while(1);

		if (cp)
		{
			Dz1Error err = DZ1_ERROR_INITIALIZER;

			*cp++ = L'\0';
			value = cp;

			p->remove(p, name);
			if ((err = p->insert(p, name, value)).code) return Dz1ShellCmdReturn_max;
			else return Dz1ShellCmdReturn_ok;
		}
	}

	Dz1ThreadW_printf(L"Usage] %s <name>=<value>\n", argv[0]);
	return Dz1ShellCmdReturn_max;
}
#endif
// Built-in Command : vars
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Built-in Command : echo
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdA_echo(void *funcParam, int argc, char *argv[])
{
	int i;
	if (argc > 1)
	{
		Dz1ThreadA_printf("%s", argv[1]);
		for (i = 2; i < argc; i++)
			Dz1ThreadA_printf(" %s", argv[i]);
	}
	Dz1ThreadA_printf("\n");
	return Dz1ShellCmdReturn_ok;
}
#ifndef UNIX_SYSTEM
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdW_echo(void *funcParam, int argc, wchar_t *argv[])
{
	int i;
	if (argc > 1)
	{
		Dz1ThreadW_printf(L"%s", argv[1]);
		for (i = 2; i < argc; i++)
			Dz1ThreadW_printf(L" %s", argv[i]);
	}
	Dz1ThreadW_printf(L"\n");
	return Dz1ShellCmdReturn_ok;
}
#endif
// Built-in Command : echo
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Built-in Command : history
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdA_history(void *funcParam, int argc, char *argv[])
{
	Dz1ShellHistoryA *h = (Dz1ShellHistoryA *)funcParam;
	Dz1ShellHistoryA_dump(h, 0);
	return Dz1ShellCmdReturn_ok;
}
#ifndef UNIX_SYSTEM
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdW_history(void *funcParam, int argc, wchar_t *argv[])
{
	Dz1ShellHistoryW *h = (Dz1ShellHistoryW *)funcParam;
	Dz1ShellHistoryW_dump(h, 0);
	return Dz1ShellCmdReturn_ok;
}
#endif
// Built-in Command : history
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Thread Log Flag Info
typedef struct LogFlagsInfoA
{
	str_t			full_name;
	str_t			short_name;
	u32_t			falg;
} LogFlagsInfoA;

static LogFlagsInfoA logFlagsInfoA[] =
{
	{ "critical",	"c",	DZ1_THREAD_LOG_CRITICAL },
	{ "error",		"e",	DZ1_THREAD_LOG_ERROR },
	{ "warn",		"w",	DZ1_THREAD_LOG_WARN },
	{ "message",	"m",	DZ1_THREAD_LOG_MESSAGE },

	{ "tdebug",		"t",	DZ1_THREAD_LOG_TASK_DEBUG },
	{ "debug",		"d",	DZ1_THREAD_LOG_DEBUG },
	{ "",			"",		DZ1_THREAD_LOG_RESERVED12 },
	{ "",			"",		DZ1_THREAD_LOG_RESERVED13 },

	{ "",			"",		DZ1_THREAD_LOG_RESERVED20 },
	{ "",			"",		DZ1_THREAD_LOG_RESERVED21 },
	{ "",			"",		DZ1_THREAD_LOG_RESERVED22 },
	{ "",			"",		DZ1_THREAD_LOG_RESERVED23 },

	{ "",			"",		DZ1_THREAD_LOG_RESERVED30 },
	{ "",			"",		DZ1_THREAD_LOG_RESERVED31 },
	{ "",			"",		DZ1_THREAD_LOG_RESERVED32 },
	{ "",			"",		DZ1_THREAD_LOG_RESERVED33 },

	{ "user-0",		"u0",	DZ1_THREAD_LOG_USER01 },
	{ "user-1",		"u1",	DZ1_THREAD_LOG_USER02 },
	{ "user-2",		"u2",	DZ1_THREAD_LOG_USER03 },
	{ "user-3",		"u3",	DZ1_THREAD_LOG_USER04 },
	{ "user-4",		"u4",	DZ1_THREAD_LOG_USER05 },
	{ "user-5",		"u5",	DZ1_THREAD_LOG_USER06 },
	{ "user-6",		"u6",	DZ1_THREAD_LOG_USER07 },
	{ "user-7",		"u7",	DZ1_THREAD_LOG_USER08 },
	{ "user-8",		"u8",	DZ1_THREAD_LOG_USER09 },
	{ "user-9",		"u9",	DZ1_THREAD_LOG_USER10 },
	{ "user-a",		"ua",	DZ1_THREAD_LOG_USER11 },
	{ "user-b",		"ub",	DZ1_THREAD_LOG_USER12 },
	{ "user-c",		"uc",	DZ1_THREAD_LOG_USER13 },
	{ "user-d",		"ud",	DZ1_THREAD_LOG_USER14 },
	{ "user-e",		"ue",	DZ1_THREAD_LOG_USER15 },
	{ "user-f",		"uf",	DZ1_THREAD_LOG_USER16 },
	{ NULL, NULL, 0 }
};
#ifndef UNIX_SYSTEM
typedef struct LogFlagsInfoW
{
	wstr_t			full_name;
	wstr_t			short_name;
	u32_t			falg;
} LogFlagsInfoW;

static LogFlagsInfoW logFlagsInfoW[] =
{
	{ L"critical",	L"c",	DZ1_THREAD_LOG_CRITICAL },
	{ L"error",		L"e",	DZ1_THREAD_LOG_ERROR },
	{ L"warn",		L"w",	DZ1_THREAD_LOG_WARN },
	{ L"message",	L"m",	DZ1_THREAD_LOG_MESSAGE },

	{ L"tdebug",	L"t",	DZ1_THREAD_LOG_TASK_DEBUG },
	{ L"debug",		L"d",	DZ1_THREAD_LOG_DEBUG },
	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED12 },
	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED13 },

	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED20 },
	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED21 },
	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED22 },
	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED23 },

	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED30 },
	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED31 },
	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED32 },
	{ L"",			L"",	DZ1_THREAD_LOG_RESERVED33 },

	{ L"user-0",	L"u0",	DZ1_THREAD_LOG_USER01 },
	{ L"user-1",	L"u1",	DZ1_THREAD_LOG_USER02 },
	{ L"user-2",	L"u2",	DZ1_THREAD_LOG_USER03 },
	{ L"user-3",	L"u3",	DZ1_THREAD_LOG_USER04 },
	{ L"user-4",	L"u4",	DZ1_THREAD_LOG_USER05 },
	{ L"user-5",	L"u5",	DZ1_THREAD_LOG_USER06 },
	{ L"user-6",	L"u6",	DZ1_THREAD_LOG_USER07 },
	{ L"user-7",	L"u7",	DZ1_THREAD_LOG_USER08 },
	{ L"user-8",	L"u8",	DZ1_THREAD_LOG_USER09 },
	{ L"user-9",	L"u9",	DZ1_THREAD_LOG_USER10 },
	{ L"user-a",	L"ua",	DZ1_THREAD_LOG_USER11 },
	{ L"user-b",	L"ub",	DZ1_THREAD_LOG_USER12 },
	{ L"user-c",	L"uc",	DZ1_THREAD_LOG_USER13 },
	{ L"user-d",	L"ud",	DZ1_THREAD_LOG_USER14 },
	{ L"user-e",	L"ue",	DZ1_THREAD_LOG_USER15 },
	{ L"user-f",	L"uf",	DZ1_THREAD_LOG_USER16 },
	{ NULL, NULL, 0 }
};
#endif

static void LogFlagsInfoA_dump(int tab)				// modified by gm 20231019 -- assign return type(void) to function
{
	int idx;
	LogFlagsInfoA *i = NULL;
	Dz1ThreadA_tprintf(tab++, "log_flags\n");
	for (idx = 1, i = logFlagsInfoA; i->full_name != NULL; i++, idx++)
	{
		if (Dz1Str_isVoid(i->full_name) == FALSE)
			Dz1ThreadA_tprintf(tab, "%2d : %s(%s)\n", idx, i->full_name, i->short_name);
	}
}

#ifndef UNIX_SYSTEM
static void LogFlagsInfoW_dump(int tab)
{
	int idx;
	LogFlagsInfoW *i = NULL;
	Dz1ThreadW_tprintf(tab++, L"log_flags\n");
	for (idx = 0, i = logFlagsInfoW; i->full_name != NULL; i++, idx++)
	{
		if (Dz1Str_isVoid(i->full_name) == FALSE)
			Dz1ThreadW_tprintf(tab, L"%2d : %s(%s)\n", idx, i->full_name, i->short_name);
	}
}
#endif

static bool_t LogFlagsInfoA_mark(u32_t *dst, str_t str)
{
	LogFlagsInfoA *i = NULL;
	if (Dz1StrA_isDigitStr(str))
	{
		u32_t idx = 0, idx_max = sizeof(logFlagsInfoA) / sizeof(LogFlagsInfoA);
		if ((idx = Dz1Ato32(str)) >= 1 && idx < idx_max)
		{
			i = &logFlagsInfoA[(idx - 1)];
			(*dst) |= i->falg;
			return TRUE;
		}
	}
	else
	{
		for (i = logFlagsInfoA; i->full_name != NULL; i++)
		{
			if (strcmp(i->full_name, str) == 0 || strcmp(i->short_name, str) == 0)
			{
				(*dst) |= i->falg;
				return TRUE;
			}
		}
	}

	return FALSE;
}
#ifndef UNIX_SYSTEM
static bool_t LogFlagsInfoW_mark(u32_t *dst, wstr_t str)
{
	LogFlagsInfoW *i = NULL;
	if (Dz1StrW_isDigitStr(str))
	{
		u32_t idx = 0, idx_max = sizeof(logFlagsInfoW) / sizeof(LogFlagsInfoW);
		if ((idx = Dz1Wto32(str)) >= 1 && idx < idx_max)
		{
			i = &logFlagsInfoW[(idx - 1)];
			(*dst) |= i->falg;
			return TRUE;
		}
	}
	else
	{
		for (i = logFlagsInfoW; i->full_name != NULL; i++)
		{
			if (wcscmp(i->full_name, str) == 0 || wcscmp(i->short_name, str) == 0)
			{
				(*dst) |= i->falg;
				return TRUE;
			}
		}
	}	;
	return FALSE;
}
#endif
// Thread Log Flag Info
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_thread_log_get Sub Command
static void cmd_thread_log_setA_usage(str_t n)
{ 
	Dz1ThreadA_printf("Usage] %s <thread_id> [<log_flags>]+\n", n);
	LogFlagsInfoA_dump(0);
}
static void cmd_thread_log_setA(void *ptr, str_t parent_cmd, int argc, str_t argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	void (*_print_usage)(str_t n) = cmd_thread_log_setA_usage;
	char n[64];
	strcpy(n, parent_cmd); strcat(n, " "); strcat(n, "set");

	if (argc < 3)
	{
		_Dz1ThreadA_dump(FALSE, 0);
		_print_usage(n);
	}
	else
	{
		int i;
		u32_t flag = 0;
		bool_t mark = FALSE;
		for (i = 2; i < argc; i++)
		{
			if (LogFlagsInfoA_mark(&flag, argv[i]) == FALSE)
			{
				_print_usage(n);
				return;
			}
			else mark = TRUE;
		}
		if (mark)
		{
			if (strcmp(argv[1], "all") == 0) Dz1Thread_modLogLevelAll(TRUE, flag);
			else
			{
				u32_t log_lv = 0, thid = Dz1Ato32(argv[1]);
				if ((*errp = Dz1Thread_getLogLevel(thid, &log_lv)).code) ERR_OUT(errp);
				else
				{
					log_lv |= flag;
					Dz1Thread_setLogLevel(thid, log_lv);
				}
			}
		}
		else _print_usage(n);
	}
}
#ifndef UNIX_SYSTEM
static void cmd_thread_log_setW_usage(wstr_t n)
{ 
	Dz1ThreadW_printf(L"Usage] %s <thread_id> [<log_flags>]+\n", n);
	LogFlagsInfoW_dump(0);
}
static void cmd_thread_log_setW(void *ptr, wstr_t parent_cmd, int argc, wstr_t argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	void (*_print_usage)(wstr_t n) = cmd_thread_log_setW_usage;
	wchar_t n[64];
	wcscpy(n, parent_cmd); wcscat(n, L" "); wcscat(n, L"set");

	if (argc < 3)
	{
		_Dz1ThreadW_dump(FALSE, 0);
		_print_usage(n);
	}
	else
	{
		int i;
		u32_t flag = 0;
		bool_t mark = FALSE;
		for (i = 2; i < argc; i++)
		{
			if (LogFlagsInfoW_mark(&flag, argv[i]) == FALSE)
			{
				_print_usage(n);
				return;
			}
			else mark = TRUE;
		}

		if (mark)
		{
			if (wcscmp(argv[1], L"all") == 0) Dz1Thread_modLogLevelAll(TRUE, flag);
			else
			{
				u32_t log_lv = 0, thid = Dz1Wto32(argv[1]);
				if ((*errp = Dz1Thread_getLogLevel(thid, &log_lv)).code) ERR_OUT(errp);
				else
				{
					log_lv |= flag;
					Dz1Thread_setLogLevel(thid, log_lv);
				}
			}
		}
		else _print_usage(n);
	}
}
#endif
// cmd_thread_log_get Sub Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_clr Sub Command
static void cmd_thread_log_clrA_usage(str_t n)
{
	Dz1ThreadA_printf("Usage] %s <thread_id> [<log_flags>]+\n", n);
	LogFlagsInfoA_dump(0);
}
static void cmd_thread_log_clrA(void *ptr, str_t parent_cmd, int argc, str_t argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	void (*_print_usage)(str_t n) = cmd_thread_log_clrA_usage;
	char n[64];
	strcpy(n, parent_cmd); strcat(n, " "); strcat(n, "clr");

	if (argc < 3)
	{
		_Dz1ThreadA_dump(FALSE, 0);
		_print_usage(n);
	}
	else
	{
		int i;
		u32_t flag = 0;
		bool_t mark = FALSE;
		for (i = 2; errp->code == 0 && i < 3; i++)
		{
			if (LogFlagsInfoA_mark(&flag, argv[i]) == FALSE)
			{
				_print_usage(n);
				return;
			}
			else mark = TRUE;
		}

		if (mark)
		{
			if (strcmp(argv[1], "all") == 0) Dz1Thread_modLogLevelAll(FALSE, flag);
			else
			{
				u32_t log_lv = 0, thid = Dz1Ato32(argv[1]);
				if ((*errp = Dz1Thread_getLogLevel(thid, &log_lv)).code) ERR_OUT(errp);
				else
				{
					log_lv &= ~flag;
					Dz1Thread_setLogLevel(thid, log_lv);
				}
			}
		}
		else _print_usage(n);
	}
}
#ifndef UNIX_SYSTEM
static void cmd_thread_log_clrW_usage(wstr_t n)
{
	Dz1ThreadW_printf(L"Usage] %s <thread_id> [<log_flags>]+\n", n);
	LogFlagsInfoW_dump(0);
}
static void cmd_thread_log_clrW(void *ptr, wstr_t parent_cmd, int argc, wstr_t argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	void (*_print_usage)(wstr_t n) = cmd_thread_log_clrW_usage;
	wchar_t n[64];
	wcscpy(n, parent_cmd); wcscat(n, L" "); wcscat(n, L"clr");

	if (argc < 3)
	{
		_Dz1ThreadW_dump(FALSE, 0);
		_print_usage(n);
	}
	else
	{
		int i;
		u32_t flag = 0;
		bool_t mark = FALSE;
		for (i = 2; errp->code == 0 && i < 3; i++)
		{
			if (LogFlagsInfoW_mark(&flag, argv[i]) == FALSE)
			{
				_print_usage(n);
				return;
			}
			else mark = TRUE;
		}

		if (mark)
		{
			if (wcscmp(argv[1], L"all") == 0) Dz1Thread_modLogLevelAll(FALSE, flag);
			else
			{
				u32_t log_lv = 0, thid = Dz1Wto32(argv[1]);
				if ((*errp = Dz1Thread_getLogLevel(thid, &log_lv)).code) ERR_OUT(errp);
				else
				{
					log_lv &= ~flag;
					Dz1Thread_setLogLevel(thid, log_lv);
				}
			}
		}
		else _print_usage(n);
	}
}
#endif
// cmd_clr Sub Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_thread Root Command
static void cmd_threadA_usage(str_t n) { Dz1ThreadA_printf("Usage] %s <on | off(x)> <thread_id> <...>\n", n); }
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdA_thread(void *ptr, int argc, str_t argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(str_t n) = cmd_threadA_usage;
	str_t n = argv[0];

	if (argc < 2)
	{
		_Dz1ThreadA_dump(FALSE, 0);
		_print_usage(n);
	}
	else
	{
		// Command Code Here
		if (errp->code) { }
		else if (strcmp(argv[1], "on") == 0 || strcmp(argv[1], "o") == 0) cmd_thread_log_setA(ptr, n, argc-1, &argv[1]);
		else if (strcmp(argv[1], "off") == 0 || strcmp(argv[1], "x") == 0) cmd_thread_log_clrA(ptr, n, argc-1, &argv[1]);
		else _print_usage(n);
	}
	return Dz1ShellCmdReturn_ok;
}
#ifndef UNIX_SYSTEM
static void cmd_threadW_usage(wstr_t n) { Dz1ThreadW_printf(L"Usage] %s <on | off(x)> <thread_id> <...>\n", n); }
static Dz1ShellCmdReturn Dz1ShellBuiltinCmdW_thread(void *ptr, int argc, wstr_t argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(wstr_t n) = cmd_threadW_usage;
	wstr_t n = argv[0];

	if (argc < 2)
	{
		_Dz1ThreadW_dump(FALSE, 0);
		_print_usage(n);
	}
	else
	{
		// Command Code Here
		if (errp->code) { }
		else if (wcscmp(argv[1], L"on") == 0 || wcscmp(argv[1], L"o") == 0) cmd_thread_log_setW(ptr, n, argc-1, &argv[1]);
		else if (wcscmp(argv[1], L"off") == 0 || wcscmp(argv[1], L"x") == 0) cmd_thread_log_clrW(ptr, n, argc-1, &argv[1]);
		else _print_usage(n);
	}
	return Dz1ShellCmdReturn_ok;
}
#endif
// cmd_thread Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Built-in Command
Dz1Error Dz1ShellBuiltinCmdInitA(Dz1ShellA *p, u32_t cmdFlag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (0) { }
	else if (										(err = p->cmd->insert(p->cmd, (str_t)"help",	Dz1ShellBuiltinCmdA_help, p->cmd,			(str_t)"Display Help Message")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_EXIT) &&		(err = p->cmd->insert(p->cmd, (str_t)"exit",	Dz1ShellBuiltinCmdA_exit, p->cmd,			(str_t)"Terminate Shell")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_ALIAS) &&		(err = p->cmd->insert(p->cmd, (str_t)"alias",	Dz1ShellBuiltinCmdA_vars, p->alias,			(str_t)"alias management")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_SET) &&		(err = p->cmd->insert(p->cmd, (str_t)"set",		Dz1ShellBuiltinCmdA_vars, p->env,			(str_t)"environment variable management")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_ECHO) &&		(err = p->cmd->insert(p->cmd, (str_t)"echo",	Dz1ShellBuiltinCmdA_echo, p->alias,			(str_t)"Print Message")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_HISTORY) &&	(err = p->cmd->insert(p->cmd, (str_t)"history",	Dz1ShellBuiltinCmdA_history, p->history,	(str_t)"Display History")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_THREAD) &&	(err = p->cmd->insert(p->cmd, (str_t)"thread",	Dz1ShellBuiltinCmdA_thread, p->history,		(str_t)"Thread Status & Log Flags")).code) { }

	return err;
}
#ifndef UNIX_SYSTEM
Dz1Error Dz1ShellBuiltinCmdInitW(Dz1ShellW *p, u32_t cmdFlag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (0) { }
	else if (										(err = p->cmd->insert(p->cmd, (wstr_t)L"help",		Dz1ShellBuiltinCmdW_help, p->cmd,			(wstr_t)L"Display Help Message")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_EXIT) &&		(err = p->cmd->insert(p->cmd, (wstr_t)L"exit",		Dz1ShellBuiltinCmdW_exit, p->cmd,			(wstr_t)L"Terminate Shell")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_ALIAS) &&		(err = p->cmd->insert(p->cmd, (wstr_t)L"alias",		Dz1ShellBuiltinCmdW_vars, p->alias,			(wstr_t)L"alias management")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_SET) &&		(err = p->cmd->insert(p->cmd, (wstr_t)L"set",		Dz1ShellBuiltinCmdW_vars, p->env,			(wstr_t)L"environment variable management")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_ECHO) &&		(err = p->cmd->insert(p->cmd, (wstr_t)L"echo",		Dz1ShellBuiltinCmdW_echo, p->alias,			(wstr_t)L"Print Message")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_HISTORY) &&	(err = p->cmd->insert(p->cmd, (wstr_t)L"history",	Dz1ShellBuiltinCmdW_history, p->history,	(wstr_t)L"Display History")).code) { }
	else if ((cmdFlag & DZ1_SHELL_CMD_THREAD) &&	(err = p->cmd->insert(p->cmd, (wstr_t)L"thread",	Dz1ShellBuiltinCmdW_thread, p->history,		(wstr_t)L"Thread Status & Log Flags")).code) { }

	return err;
}
#endif
// Built-in Command
////////////////////////////////////////////////////////////////////////////////


bool_t Dz1ShellBuiltinCmdA_setLogFlag(u32_t flag, const str_t full_name, const str_t short_name)
{
	LogFlagsInfoA *i = NULL;
	for (i = logFlagsInfoA; i->full_name != NULL; i++)
	{
		if (i->falg == flag)
		{
			if (Dz1Str_isVoid(i->full_name))
			{
				i->full_name = full_name;
				i->short_name = short_name;
				return TRUE;
			}
		}
	}
	return FALSE;
}
#ifndef UNIX_SYSTEM
bool_t Dz1ShellBuiltinCmdW_setLogFlag(u32_t flag, const wstr_t full_name, const wstr_t short_name)
{
	LogFlagsInfoW *i = NULL;
	for (i = logFlagsInfoW; i->full_name != NULL; i++)
	{
		if (i->falg == flag)
		{
			if (Dz1Str_isVoid(i->full_name))
			{
				i->full_name = full_name;
				i->short_name = short_name;
				return TRUE;
			}
		}
	}
	return FALSE;
}
#endif