#include <dz1_parser_init.h>

#include "Dz1ParserUtil.h"

#define DZ1_PARSER_UTIL_ENTRY_END			-1

///////////////////////////////////////////////////////////////////////////////
// Dz1ParserUtilEnv
Dz1Error Dz1ParserUtilEnv_check(Dz1ParserUtilEnvEntry *table)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ParserUtilEnvEntry *i, *node;
	Dz1ParserUtilEnvList *list = Dz1ParserUtilEnvList_new(errp);
	if (list == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ParserUtilEnvList_delAndSetNull, (void *)&list);
		for (i = table; errp->code == 0 && i->parserID != -1; i++)
		{
			if ((node = Dz1ParserUtilEnvEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = list->add(list, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Dz1ParserUtilEnvList_delAndSetNull, (void *)&list);
	}
	return err;
}

Dz1ParserUtilEnvEntry *Dz1ParserUtilEnvEntry_find(Dz1ParserUtilEnvEntry arr[], u32_t parserID)
{
	Dz1ParserUtilEnvEntry *i;
	for (i = arr; i->parserID != DZ1_PARSER_UTIL_ENTRY_END; i++)
		if (i->parserID == parserID) return i;
	return NULL;
}
// Dz1ParserUtilEnv
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1ParserUtil_addEmitter(void *p, Dz1ParserUtilEmitterInfo *table)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ParserUtilEmitterInfo *i;
	for (i = table; err.code == 0 && i->name != NULL; i++)
		if ((err = Dz1Parser_addEmiter(p, i->name, i->func)).code) ERR_OUT(&err);
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// IPv4Syntax
static str_t IPv4Syntax = ""
"IPv4Syntax = <number_u_real>=IPv4Emit_setAB <dot> <number_u_real>=IPv4Emit_setCD <dot> <number>=IPv4Emit_setB <dot> <number>=IPv4Emit_setB;"
"";

static Dz1Error IPv4Emit_setAB(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t str = NULL;
	Dz1ParserIPv4Env *env = NULL;
	Dz1ParserUtilEnvEntry *node = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	if ((node = Dz1ParserUtilEnvEntry_find(table, DZ1_PARSER_UTIL_PARSER_IPv4)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (Dz1ParserIPv4Env *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((str = Dz1StrA_dup(t->v, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *a = str, *b = NULL;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&str);
		env->dst = 0;
		if ((b = strchr(str, '.')) == NULL) ERR_SET_OUT(errp, EINVAL);
		else
		{
			*b++ = 0;
			u32_t va = (u32_t)atoi(a);
			u32_t vb = (u32_t)atoi(a);
			if (va > 0xFF) ERR_SET_OUT(errp, EINVAL);
			else if (vb > 0xFF) ERR_SET_OUT(errp, EINVAL);
			else
			{
				env->dst |= va;
				env->dst <<= 8;
				env->dst |= vb;
			}
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&str);
	}
	return err;
}

static Dz1Error IPv4Emit_setCD(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t str = NULL;
	Dz1ParserIPv4Env *env = NULL;
	Dz1ParserUtilEnvEntry *node = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	if ((node = Dz1ParserUtilEnvEntry_find(table, DZ1_PARSER_UTIL_PARSER_IPv4)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (Dz1ParserIPv4Env *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((str = Dz1StrA_dup(t->v, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *a = str, *b = NULL;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&str);
		if ((b = strchr(str, '.')) == NULL) ERR_SET_OUT(errp, EINVAL);
		else
		{
			*b++ = 0;
			u32_t va = (u32_t)atoi(a);
			u32_t vb = (u32_t)atoi(a);
			if (va > 0xFF) ERR_SET_OUT(errp, EINVAL);
			else if (vb > 0xFF) ERR_SET_OUT(errp, EINVAL);
			else
			{
				env->dst <<= 8;
				env->dst |= va;
				env->dst <<= 8;
				env->dst |= vb;
			}
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&str);
	}
	return err;
}

static Dz1ParserUtilEmitterInfo IPv4Emitter[] =
{
	Dz1ParserEmitterInfoEntry(IPv4Emit_setAB),
	Dz1ParserEmitterInfoEntry(IPv4Emit_setCD),
	Dz1ParserEmitterInfoEndOfEntry
};

Dz1Error Dz1ParserUtilIPv4_emitterInit(void *parser)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1ParserUtil_addEmitter(parser, IPv4Emitter)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1ParserUtilIPv4_syntaxInit(void *parser)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1ParserInit_parse(parser, IPv4Syntax)).code) ERR_OUT(errp);
	return err;
}
// IPv4Syntax
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TcpListenAddr4Syntax
static str_t TcpListenAddr4Syntax = ""
"TcpListenAddr4Syntax =		listen addr <equal> <liststart>\n"
"								interface <equal> <IPv4Syntax>=TcpListenAddr4_setIPv4 <semicolon>\n"
"								tcp port <equal> <number>=TcpListenAddr4_setPort <semicolon>\n"
"							<listend>;\n";

Dz1Error TcpListenAddr4_setIPv4(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_PARSER_UTIL_PARSER_TCP_LISTEN_ADDR);
	Dz1ParserUtilEnvEntry *ipv4node = Dz1ParserUtilEnvEntry_find(table, DZ1_PARSER_UTIL_PARSER_IPv4);
	if (node == NULL || ipv4node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1ParserTcpListenAddrEnv *env = (Dz1ParserTcpListenAddrEnv *)node->env;
		Dz1ParserIPv4Env *ipv4env = (Dz1ParserIPv4Env *)ipv4node->env;

		if ((*errp = Dz1SockAddr_setAddr4(&env->addr, ipv4env->dst)).code) ERR_OUT(errp);
	}
	return err;
}

Dz1Error TcpListenAddr4_setPort(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_PARSER_UTIL_PARSER_TCP_LISTEN_ADDR);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1ParserTcpListenAddrEnv *env = (Dz1ParserTcpListenAddrEnv *)node->env;
		u32_t port = (u32_t)atoi(t->v);
		if (port > 0xFFFF) ERR_SET_OUT(errp, EINVAL);
		else if ((*errp = Dz1SockAddr_setPort(&env->addr, (u16_t)(port & 0xFFFF))).code) ERR_OUT(errp);
	}
	return err;
}

static Dz1ParserUtilEmitterInfo TcpListenAddr4Emitter[] =
{
	Dz1ParserEmitterInfoEntry(TcpListenAddr4_setIPv4),
	Dz1ParserEmitterInfoEntry(TcpListenAddr4_setPort),
	Dz1ParserEmitterInfoEndOfEntry
};

Dz1Error Dz1ParserUtilTcpListenAddr4_emitterInit(void *parser)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1ParserUtil_addEmitter(parser, TcpListenAddr4Emitter)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1ParserUtilTcpListenAddr4_syntaxInit(void *parser)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1ParserInit_parse(parser, TcpListenAddr4Syntax)).code) ERR_OUT(errp);
	return err;
}
// TcpListenAddr4Syntax
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1ParserUtilTcpListenAddr4_save(Dz1SockAddr *addr, FILE *fp, int tab)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	u16_t port = 0;
	char buf[64] = { 0, };
	if (Dz1SockAddr_printableNoPort(addr, buf, FALSE, errp) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_getPort(addr, &port)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_fprintf(fp, "listen addr = {\n"); tab++;
		Dz1Thread_ftprintf(fp, tab, "interface = %s;\n", buf);
		Dz1Thread_ftprintf(fp, tab, "tcp port = %u;\n", port);
		Dz1Thread_ftprintf(fp, --tab, "}\n");
	}
	return err;
}

