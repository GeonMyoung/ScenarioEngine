#include "Dz1CodeGen_parser.h"

static Dz1CodeGenSetupEntry parserEmitterArgSetup[] =
{
	{ "Emitter 함수명", TRUE },
	{ "Parser Env ID", TRUE },
	{ "Parser Env Type", TRUE },
	{ NULL }
};

static Dz1CodeGenSetupEntry parserParserArgSetup[] =
{
	{ "대상 Type", TRUE },
	{ "Parser Env ID", TRUE },
	{ "Parser Env Type", TRUE },
	{ NULL }
};

Dz1CodeGenSetupTable parserCodeGenSetupTable[] =
{
	{ Dz1CodeGenParserType_emitter, parserEmitterArgSetup },
	{ Dz1CodeGenParserType_parser, parserParserArgSetup },
	{ Dz1CodeGenListType_max, NULL }
};

static Dz1Error _parserGen_emitter(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"static Dz1Error $emitter_func_name$(Dz1ParserToken *t, void *ptr)"_CRLF,
		"{"_CRLF,
		"	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;"_CRLF,
		"	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;"_CRLF,
		"	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, $parser_env_id$);"_CRLF,
		"	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		$parser_env_type$ *env = ($parser_env_type$ *)node->env;"_CRLF,
		"		// emitting code here"_CRLF,
		"	}"_CRLF,
		"	return err;"_CRLF,
		"}"_CRLF,
		NULL
	};
	str_t emitter_func_name = va_arg(ap, str_t);
	str_t parser_env_id = va_arg(ap, str_t);
	str_t parser_env_type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		{ "emitter_func_name", emitter_func_name },
		{ "parser_env_id", parser_env_id },
		{ "parser_env_type", parser_env_type },
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}


static Dz1Error _parserGen_parser(str_t *dst, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	str_t base_code[] =
	{
		"static Dz1Error $result_type$_parse($result_type$ *dst, str_t src_text)"_CRLF,
		"{"_CRLF,
		"	DZ1_ERROR_SAFE_VAR(errp, err);"_CRLF,
		"	void *parser = Dz1Parser_new(errp);"_CRLF,
		"	if (parser == NULL) ERR_OUT(errp);"_CRLF,
		"	else"_CRLF,
		"	{"_CRLF,
		"		// Dz1ParserIPv4Env ipv4env;"_CRLF,
		"		// Dz1ParserTcpListenAddrEnv listenAddrEnv;"_CRLF,
		"		$parser_env_type$ user_env = { dst, NULL, };"_CRLF,
		"		Dz1ParserUtilEnvEntry parse_env[] ="_CRLF,
		"		{"_CRLF,
		"		//	Dz1ParserIPv4Env_entry(&ipv4env),"_CRLF,
		"		//	Dz1ParserTcpListenAddrEnv_entrp(&listenAddrEnv),"_CRLF,
		"			{ $parser_env_id$, &user_env },"_CRLF,
		"			Dz1ParserEnvEntryLast"_CRLF,
		"		};"_CRLF,
		""_CRLF,
		"		pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&parser);"_CRLF,
		""_CRLF,
		"		if ((*errp = Dz1ParserUtilEnv_check(parse_env)).code) ERR_OUT(errp);"_CRLF,
		"		else if ((*errp = Dz1ParserUtil_addEmitter(parser, __emitter_table__)).code) ERR_OUT(errp);"_CRLF,
		"		else if ((*errp = Dz1ParserInit_parse(parser, __syntax_str__)).code) ERR_OUT(errp);"_CRLF,
		"		else if ((*errp = Dz1Parser_prepare(parser, src_text)).code) ERR_OUT(errp);"_CRLF,
		"		else if ((*errp = Dz1Parser_process(parser, \"__syntax_name__\", (void *)parse_env, 0)).code)"_CRLF,
		"		{"_CRLF,
		"			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, \"$result_type$_parse() : Parse Fail at %u line\\n\", Dz1Parser_getLineNum(parser));"_CRLF,
		"			ERR_OUT(errp);"_CRLF,
		"		}"_CRLF,
		"		pthread_cleanup_pop(1); // (Dz1Parser_delAndSetNull, (void *)&parser);"_CRLF,
		"	}"_CRLF,
		"	return err;"_CRLF,
		"}"_CRLF,
		NULL
	};
	str_t result_type = va_arg(ap, str_t);
	str_t parser_env_id = va_arg(ap, str_t);
	str_t parser_env_type = va_arg(ap, str_t);
	
	Dz1CodeGenReplaceEnt arr[] =
	{
		{ "result_type", result_type },
		{ "parser_env_id", parser_env_id },
		{ "parser_env_type", parser_env_type },
		Dz1CodeGenReplaceEnt_last
	};

	Dz1CodeGenReplaceList *list = Dz1CodeGenReplaceList_generate(arr, errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
		if (( (*dst) = Dz1CodeGen_replace(base_code, list, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&list);
	}
	return *errp;
}

Dz1Error Dz1CodeGen_parserGen(str_t *dst, Dz1CodeGenParserType type, ...)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	va_list ap;
	va_start(ap, type);

	switch(type)
	{
	case Dz1CodeGenParserType_emitter:
		if ((*errp = _parserGen_emitter(dst, ap)).code) ERR_OUT(errp);
		break;
	case Dz1CodeGenParserType_parser:
		if ((*errp = _parserGen_parser(dst, ap)).code) ERR_OUT(errp);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return *errp;

	va_end(ap);
}

