#include "Dz1CodeGen_shell.h"

typedef struct ArgumentParseResult
{
	int				cnt_min;
	int				cnt_max;
	bool_t			is_dynamic;
	bool_t			is_extensible;
} ArgumentParseResult;

static char for_loop_text[64] = { 0, };

static str_t dynamic_arg_proc[] =
{
	"		int i;"_CRLF,
	"		Dz1Str str = NULL;"_CRLF,
	_CRLF,
//	"		for (i = 1; errp->code == 0 && i < argc; i++)	// make sure minimum and maximum of i"_CRLF,
	for_loop_text,
	"		{"_CRLF,
	"			str = argv[i];"_CRLF,
	"			if (0) { }"_CRLF,
	"//			else if (Dz1STRNCMP(str, Dz1T(\"_identifier_str_\"), _identifier_len_) == 0)"_CRLF,
	"//			{	// some argument processing here"_CRLF,
	"//				Dz1Str src = str + _identifier_len_;"_CRLF,
	"//			}"_CRLF,
	"			else"_CRLF,
	"			{"_CRLF,
	"				_print_usage(n);"_CRLF,
	"				ERR_SET_OUT(errp, EINVAL);"_CRLF,
	"			}"_CRLF,
	"		}"_CRLF
	_CRLF
};
#define dynamic_arg_proc_sz		(sizeof(dynamic_arg_proc) / sizeof(str_t))

static bool_t _mk_base_code(str_t *dst, size_t dst_sz, str_t *front, size_t front_sz, str_t *tail, size_t tail_sz, ArgumentParseResult *arg_info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (front == NULL || front_sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if (dst == NULL || dst_sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if (dst_sz < front_sz + tail_sz) ERR_SET_OUT(errp, E2BIG);
	else
	{
		size_t i;
		str_t *dp = dst;
		for (i = 0; i < front_sz; i++) *dp++ = front[i];

		if (arg_info->is_dynamic)
		{
			if (dst_sz < front_sz + tail_sz + dynamic_arg_proc_sz) ERR_SET_OUT(errp, E2BIG);
			else
			{
				snprintf(for_loop_text, 63, "		for (i = %d; errp->code == 0 && i < %d; i++)"_CRLF, arg_info->cnt_min, arg_info->cnt_max);
				for (i = 0; i < dynamic_arg_proc_sz; i++) *dp++ = dynamic_arg_proc[i];
			}
		}

		if (errp->code == 0)
		{
			if (tail != NULL)
				for (i = 0; i < tail_sz; i++) *dp++ = tail[i];

			Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _parse_arguments(ArgumentParseResult *dst, str_t arg_str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char *cp = arg_str;
		char temp[64] = { 0, };

		dst->is_dynamic = FALSE;
		dst->is_extensible = FALSE;
		dst->cnt_min = dst->cnt_max = 1;

		if (strcmp(arg_str, "<>") == 0) return TRUE;

		while(errp->code == 0 && *cp)
		{
			if (*cp == '<')
			{
				u32_t len = 0;
				char *dp = temp;
				cp++;
				while(*cp && *cp != '>') 
				{
					*dp++ = *cp++;
					len++;
				}
				*dp = 0;

				if (*cp != '>') ERR_SET_OUT(errp, EINVAL);
				else if (len == 0) ERR_SET_OUT(errp, EINVAL);
				else if (strcmp(temp, "...") == 0)
				{	// 인자가 "..."이다. -> 최대값 없음, 최소값 변화 없음
					if (dst->is_extensible) ERR_SET_OUT(errp, EEXIST);						// <...> 반복 허용 안함
					else dst->is_extensible = TRUE;
				}
				else if (dst->is_dynamic || dst->is_extensible) ERR_SET_OUT(errp, EPERM);	// <...> 나 [...] 이후에 확정인자 허용 안함
				else
				{	// 확정 인자 -> 최소값, 최대값 각각 증가
					dst->cnt_min++;
					dst->cnt_max++;
				}
			}
			else if (*cp == '[')
			{	// 생략 가능한 인수
				if (dst->is_extensible) ERR_SET_OUT(errp, EPERM);	// <...> 이후에 [...] 허용 안함
				else
				{
					u32_t pair_cnt = 1;
					dst->is_dynamic = TRUE;
					cp++;											// pass '['
					dst->cnt_max++;									// 최대값 증가
					while(*cp && pair_cnt > 0)
					{
						if (*cp == '[')
						{											// 생략 인수 발견
							pair_cnt++;								// pair 값 증가
							dst->cnt_max++;							// 최대값 증가
							cp++;									// cp 이동
						}
						else if (*cp == ']')
						{											// 생략 인수의 종료
							pair_cnt--;								// pair 값 감소
							if (pair_cnt > 0) cp++;					// 마지막이 아닌 경우에만 cp 이동
						}
						else cp++;									// 일반문자 -> cp이동
					}

					if (*cp != ']' || pair_cnt != 0) ERR_SET_OUT(errp, EINVAL);
				}
			}
			cp++;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#define ARGS_CHECK_CODE_STR					"@@ARGUMENT_CHECK_CODE@@"
static bool_t _set_argc_chk_code(str_t *base_code, ArgumentParseResult *argc, char *buf, size_t buf_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t i;
	if (base_code == NULL || argc == NULL || buf == NULL || buf_sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if (argc->is_extensible)
	{	// just minimum
		snprintf(buf, buf_sz, "\tif (argc < %d) _print_usage(n);\r\n", argc->cnt_min);
	}
	else if (argc->is_dynamic)
	{	// range
		snprintf(buf, buf_sz, "\tif (argc < %d || argc > %d) _print_usage(n);\r\n", argc->cnt_min, argc->cnt_max);
	}
	else
	{	// single value
		snprintf(buf, buf_sz, "\tif (argc != %d) _print_usage(n);\r\n", argc->cnt_min);
	}

	for (i = 0; base_code[i] != NULL; i++)
	{
		if (strcmp(base_code[i], ARGS_CHECK_CODE_STR) == 0)
		{
			base_code[i] = buf;
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Root Command
static Dz1CodeGenSetupEntry shellRootCmdArgSetup[] =
{
	{ "EnvType",	TRUE },
	{ "Arguments",	TRUE },
	{ "Command",	TRUE },
	{ "-",			FALSE },
	{ NULL }
};

static str_t root_cmd_front[] =
{
	"////////////////////////////////////////////////////////////////////////////////"_CRLF,
	"// cmd_$cmd$ Root Command"_CRLF,
	"static void cmd_$cmd$_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text(\"Usage] %s $arguments$\\n\"), n); }"_CRLF,
	"static Dz1ShellCmdReturn cmd_$cmd$(void *ptr, int argc, Dz1Str argv[])"_CRLF,
	"{"_CRLF,
	"	DZ1_ERROR_SAFE_VAR(errp, err);"_CRLF,
	"	void (*_print_usage)(Dz1Str n) = cmd_$cmd$_usage;"_CRLF,
	"	Dz1Str n = argv[0];"_CRLF,
	"	//$envtype$ *env = ($envtype$ *)ptr;"_CRLF,
	ARGS_CHECK_CODE_STR,
	"	else"_CRLF,
	"	{"_CRLF,
};
#define root_cmd_front_sz	(sizeof(root_cmd_front) / sizeof(str_t))

static str_t root_cmd_tail[] =
{
	"		// Command Code Here"_CRLF,
	"		if (errp->code) { }"_CRLF,
	"//		else if (Dz1STRCMP(argv[1], Dz1Text(\"_long_sub_cmd_\")) == 0 || Dz1STRCMP(argv[1], Dz1Text(\"_short_sub_cmd_\")) == 0) _sub_cmd_(ptr, n, argc-1, &argv[1]);"_CRLF,
	"		else _print_usage(n);"_CRLF,
	"	}"_CRLF,
	"	return Dz1ShellCmdReturn_ok;"_CRLF,
	"}"_CRLF,
	"// cmd_$cmd$ Root Command"_CRLF,
	"////////////////////////////////////////////////////////////////////////////////"_CRLF,
	_CRLF,
	NULL
};
#define root_cmd_tail_sz	(sizeof(root_cmd_tail) / sizeof(str_t))

static Dz1Error _shellGen_root_cmd(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[root_cmd_front_sz + dynamic_arg_proc_sz + root_cmd_tail_sz] = { NULL, };
	size_t base_code_sz = sizeof(base_code) / sizeof(str_t);
// 	{
// 		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
// 		"// cmd_$cmd$ Root Command"_CRLF,
// 		"static void cmd_$cmd$_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text(\"Usage] %s $arguments$\\n\"), n); }"_CRLF,
// 		"static Dz1ShellCmdReturn cmd_$cmd$(void *ptr, int argc, Dz1Str argv[])"_CRLF,
// 		"{"_CRLF,
// 		"	DZ1_ERROR_SAFE_VAR(errp, err);"_CRLF,
// 		"	void (*_print_usage)(Dz1Str n) = cmd_$cmd$_usage;"_CRLF,
// 		"	Dz1Str n = argv[0];"_CRLF,
// 		"	//$envtype$ *env = ($envtype$ *)ptr;"_CRLF,
// 		ARGS_CHECK_CODE_STR,
// 		"	else"_CRLF,
// 		"	{"_CRLF,
// 		"		// Command Code Here"_CRLF,
// 		"		if (errp->code) { }"_CRLF,
// 		"//		else if (Dz1STRCMP(argv[1], Dz1Text(\"_long_sub_cmd_\")) == 0 || Dz1STRCMP(argv[1], Dz1Text(\"_short_sub_cmd_\")) == 0) _sub_cmd_(ptr, n, argc-1, &argv[1]);"_CRLF,
// 		"		else _print_usage(n);"_CRLF,
// 		"	}"_CRLF,
// 		"	return Dz1ShellCmdReturn_ok;"_CRLF,
// 		"}"_CRLF,
// 		"// cmd_$cmd$ Root Command"_CRLF,
// 		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
// 		_CRLF,
// 		NULL
// 	};
	str_t envtype = va_arg(ap, str_t);
	str_t _arguments = va_arg(ap, str_t);
	str_t arguments = strcmp(_arguments, "<>") == 0 ? "" : _arguments;
	str_t cmd = va_arg(ap, str_t);
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(cmd),
		Dz1CodeGenReplaceEntry(envtype),
		Dz1CodeGenReplaceEntry(arguments),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = NULL;
	
	if ((list = Dz1CodeGenReplaceList_generate(arr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ArgumentParseResult argc = { 0, 0 };
		char argc_chk_line[128] = { 0, };
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);

		if (_parse_arguments(&argc, arguments, errp) == FALSE) ERR_OUT(errp);
		else if (_mk_base_code(base_code, base_code_sz, root_cmd_front, root_cmd_front_sz, root_cmd_tail, root_cmd_tail_sz, &argc, errp) == FALSE) ERR_OUT(errp);
		else if (_set_argc_chk_code(base_code, &argc, argc_chk_line, 128, errp) == FALSE) ERR_OUT(errp);
		else if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}
// Root Command
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Sub Command
static Dz1CodeGenSetupEntry shellSubCmdArgSetup[] =
{
	{ "EnvType",	TRUE },
	{ "Arguments",	TRUE },
	{ "Root Cmd",	TRUE },
	{ "Command",	TRUE },
	{ NULL }
};

static str_t sub_cmd_front[] =
{
	"////////////////////////////////////////////////////////////////////////////////"_CRLF,
	"// cmd_$cmd$ Sub Command"_CRLF,
	"static void cmd_$parentcmd$_$cmd$_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text(\"Usage] %s $arguments$\\n\"), n); }"_CRLF,
	"static void cmd_$parentcmd$_$cmd$(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])"_CRLF,
	"{"_CRLF,
	"	DZ1_ERROR_SAFE_VAR(errp, err);"_CRLF,
	"	//$envtype$ *env = ($envtype$ *)ptr;"_CRLF,
	""_CRLF,
	"	void (*_print_usage)(Dz1Str n) = cmd_$parentcmd$_$cmd$_usage;"_CRLF,
	"	TCHAR n[64];"_CRLF,
	"	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(\" \")); Dz1STRCAT(n, Dz1Text(\"$cmd$\"));"_CRLF,
	""_CRLF,
	ARGS_CHECK_CODE_STR,
	"	else"_CRLF,
	"	{"_CRLF,
};
#define sub_cmd_front_sz	(sizeof(sub_cmd_front) / sizeof(str_t))

static str_t sub_cmd_tail[] =
{
	"		// Command Code Here"_CRLF,
	"//		if (errp->code) { }"_CRLF,
	"//		else if (Dz1STRCMP(argv[1], Dz1Text(\"_long_sub_cmd_\")) == 0 || Dz1STRCMP(argv[1], Dz1Text(\"_short_sub_cmd_\")) == 0) _sub_cmd_(ptr, n, argc-1, &argv[1]);"_CRLF,
	"//		else _print_usage(n);"_CRLF,
	"	}"_CRLF,
	"}"_CRLF,
	"// cmd_$cmd$ Sub Command"_CRLF,
	"////////////////////////////////////////////////////////////////////////////////"_CRLF,
	_CRLF,
	NULL
};
#define sub_cmd_tail_sz		(sizeof(sub_cmd_tail) / sizeof(str_t))

static Dz1Error _shellGen_sub_cmd(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[sub_cmd_front_sz + dynamic_arg_proc_sz + sub_cmd_tail_sz] = { NULL, };
	size_t base_code_sz = sizeof(base_code) / sizeof(str_t);
// 	{
// 		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
// 		"// cmd_$cmd$ Sub Command"_CRLF,
// 		"static void cmd_$parentcmd$_$cmd$_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text(\"Usage] %s $arguments$\\n\"), n); }"_CRLF,
// 		"static void cmd_$parentcmd$_$cmd$(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])"_CRLF,
// 		"{"_CRLF,
// 		"	DZ1_ERROR_SAFE_VAR(errp, err);"_CRLF,
// 		"	//$envtype$ *env = ($envtype$ *)ptr;"_CRLF,
// 		""_CRLF,
// 		"	void (*_print_usage)(Dz1Str n) = cmd_$parentcmd$_$cmd$_usage;"_CRLF,
// 		"	TCHAR n[64];"_CRLF,
// 		"	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(\" \")); Dz1STRCAT(n, Dz1Text(\"$cmd$\"));"_CRLF,
// 		""_CRLF,
// 		ARGS_CHECK_CODE_STR,
// 		"	else"_CRLF,
// 		"	{"_CRLF,
// 		"		// Command Code Here"_CRLF,
// 		"//		if (errp->code) { }"_CRLF,
// 		"//		else if (Dz1STRCMP(argv[1], Dz1Text(\"_long_sub_cmd_\")) == 0 || Dz1STRCMP(argv[1], Dz1Text(\"_short_sub_cmd_\")) == 0) _sub_cmd_(ptr, n, argc-1, &argv[1]);"_CRLF,
// 		"//		else _print_usage(n);"_CRLF,
// 		"	}"_CRLF,
// 		"}"_CRLF,
// 		"// cmd_$cmd$ Sub Command"_CRLF,
// 		"////////////////////////////////////////////////////////////////////////////////"_CRLF,
// 		_CRLF,
// 		NULL
// 	};
	str_t envtype = va_arg(ap, str_t);
	str_t _arguments = va_arg(ap, str_t);
	str_t arguments = strcmp(_arguments, "<>") == 0 ? "" : _arguments;
	str_t parentcmd = va_arg(ap, str_t);
	str_t cmd = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		Dz1CodeGenReplaceEntry(parentcmd),
		Dz1CodeGenReplaceEntry(envtype),
		Dz1CodeGenReplaceEntry(arguments),
		Dz1CodeGenReplaceEntry(cmd),
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = NULL;
	if ((list = Dz1CodeGenReplaceList_generate(arr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ArgumentParseResult argc = { 0, 0 };
		char argc_chk_line[128] = { 0, };
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);

		if (_parse_arguments(&argc, arguments, errp) == FALSE) ERR_OUT(errp);
		else if (_mk_base_code(base_code, base_code_sz, sub_cmd_front, sub_cmd_front_sz, sub_cmd_tail, sub_cmd_tail_sz, &argc, errp) == FALSE) ERR_OUT(errp);
		else if (_set_argc_chk_code(base_code, &argc, argc_chk_line, 128, errp) == FALSE) ERR_OUT(errp);
		else if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}
// Sub Command
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Shell Command
Dz1CodeGenSetupTable shellCodeGenSetupTable[] =
{
	{ Dz1CodeGenShellType_root_cmd, shellRootCmdArgSetup },
	{ Dz1CodeGenShellType_sub_cmd, shellSubCmdArgSetup },
	{ Dz1CodeGenListType_max, NULL }
};

Dz1Error Dz1CodeGen_shellGen(str_t *dst, Dz1CodeGenShellType type, ...)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	va_list ap;
	va_start(ap, type);

	switch(type)
	{
	case Dz1CodeGenShellType_root_cmd:
		if ((*errp = _shellGen_root_cmd(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenShellType_sub_cmd:
		if ((*errp = _shellGen_sub_cmd(dst, ap)).code) ERR_OUT(errp);
		break;

	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return *errp;

	va_end(ap);
}
// Shell Command
///////////////////////////////////////////////////////////////////////////////
