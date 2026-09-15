#ifndef DZ1_PARSER_UTIL_H
#define DZ1_PARSER_UTIL_H

#include <dz1_parser.h>
#include "Dz1ParserUtilDef.h"

DZ1_CPPLINK Dz1Error				 Dz1ParserUtilEnv_check(Dz1ParserUtilEnvEntry *table); // env_id collision check

#define Dz1ParserEnvEntryLast				Dz1ParserUtilEnvEntry_NULL

#define Dz1ParserUtilEnvEntry_NULL			{ -1, NULL }
#define Dz1ParserUtilEnvEntry_isNULL(p)		((p != NULL && p->env != NULL && p->id != -1) ? TRUE : FALSE)

DZ1_CPPLINK Dz1ParserUtilEnvEntry	*Dz1ParserUtilEnvEntry_find(Dz1ParserUtilEnvEntry array[], u32_t parserID);


///////////////////////////////////////////////////////////////////////////////
// Parser Util : Emitter
typedef struct Dz1ParserUtilEmitterInfo
{
	str_t				 name;
	Dz1ParserEmitFunc	 func;
} Dz1ParserUtilEmitterInfo;
#define Dz1ParserUtilEmitterInfo_NULL				{ NULL, NULL }
#define Dz1ParserUtilEmitterInfo_isNULL(p)			(p->name == NULL && p->func == NULL)
#define Dz1ParserUtilEmitterInfo_entry(func)		{ #func, func }

#define Dz1ParserUtilEmitterInfoEntry(func)			Dz1ParserUtilEmitterInfo_entry
#define Dz1ParserEmitterInfoEntry					Dz1ParserUtilEmitterInfo_entry
#define Dz1ParserUtilEmitterInfoLast				Dz1ParserUtilEmitterInfo_NULL
#define Dz1ParserEmitterInfoEndOfEntry				Dz1ParserUtilEmitterInfo_NULL

DZ1_CPPLINK Dz1Error Dz1ParserUtil_addEmitter(void *parser, Dz1ParserUtilEmitterInfo *table);

/*
///////////////////////////////////////////////////////////////////////////////
// Typical Emitter Function
Dz1Error <func_name>(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = NULL;
	<user_env> *env = NULL;
	if ((node = Dz1ParserUtilEnvEntry_find(table, <parser_id>)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (<user_env> *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}
// Typical Emitter Function
///////////////////////////////////////////////////////////////////////////////
parser_id
func_name
user_env
*/
// Parser Util : Emitter
///////////////////////////////////////////////////////////////////////////////

#define DZ1_PARSER_UTIL_PARSER_ID						0xF0000000											// Parser Utility Env Category

///////////////////////////////////////////////////////////////////////////////
// IPv4 Parse Helper
// 	typedef struct Dz1ParserIPv4Env
// 	{
// 		u32_t dst;
// 	} Dz1ParserIPv4Env;
#define DZ1_PARSER_UTIL_PARSER_IPv4						(DZ1_PARSER_UTIL_PARSER_ID | 0x00000001)			// IPv4 Parse Env ID
#define Dz1ParserIPv4Env_entry(envp)					{ DZ1_PARSER_UTIL_PARSER_IPv4, (void *)(envp) }
DZ1_CPPLINK Dz1Error Dz1ParserUtilIPv4_emitterInit(void *parser);
DZ1_CPPLINK Dz1Error Dz1ParserUtilIPv4_syntaxInit(void *parser);
// IPv4 Parse Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Tcp Listen Address Parser Helper
// 	typedef struct Dz1ParserTcpListenAddrEnv
// 	{
// 		Dz1SockAddr				 addr;
// 	} Dz1ParserTcpListenAddrEnv;
#define DZ1_PARSER_UTIL_PARSER_TCP_LISTEN_ADDR			(DZ1_PARSER_UTIL_PARSER_ID | 0x00000002)			// IPv4 TCP Listen Address Parse Env ID
#define Dz1ParserTcpListenAddrEnv_entrp(envp)			{ DZ1_PARSER_UTIL_PARSER_TCP_LISTEN_ADDR, (void *)(envp) }

DZ1_CPPLINK Dz1Error Dz1ParserUtilTcpListenAddr4_emitterInit(void *parser);
DZ1_CPPLINK Dz1Error Dz1ParserUtilTcpListenAddr4_syntaxInit(void *parser);

DZ1_CPPLINK Dz1Error Dz1ParserUtilTcpListenAddr4_save(Dz1SockAddr *addr, FILE *fp, int tab);
// Tcp Listen Address Parser Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1ParserUtilPathArr
typedef struct Dz1ParserUtilPathArr
{
	Dz1Str					*arr;
	u32_t					 cnt;
} Dz1ParserUtilPathArr;

DZ1_CPPLINK Dz1ParserUtilPathArr *Dz1ParserUtilPathArr_new(Dz1Str str, Dz1Error *err);
DZ1_CPPLINK Dz1ParserUtilPathArr *Dz1ParserUtilPathArr_clone(Dz1ParserUtilPathArr *src, Dz1Error *err);
DZ1_CPPLINK void				  Dz1ParserUtilPathArr_del(Dz1ParserUtilPathArr *p);
static __inline__ void			  Dz1ParserUtilPathArr_delAndSetNull(void *pptr)
{
	Dz1ParserUtilPathArr **p = (Dz1ParserUtilPathArr **)pptr;
	Dz1ParserUtilPathArr_del(*p); *p = NULL;
}
DZ1_CPPLINK void				  Dz1ParserUtilPathArr_dump(Dz1ParserUtilPathArr *p, int tab);
// Dz1ParserUtilPathArr
///////////////////////////////////////////////////////////////////////////////

/*
///////////////////////////////////////////////////////////////////////////////
// Typical Parser Function
static Dz1Error <result_type>_parse(<result_type> *dst, str_t src_text)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void *parser = Dz1Parser_new(errp);
	if (parser == NULL) ERR_OUT(errp);
	else
	{
		// Dz1ParserIPv4Env ipv4env;
		// Dz1ParserTcpListenAddrEnv listenAddrEnv;
		<parse_env_type> user_env = { NULL, };
		Dz1ParserUtilEnvEntry parse_env[] =
		{
		//	Dz1ParserIPv4Env_entry(&ipv4env),
		//	Dz1ParserTcpListenAddrEnv_entrp(&listenAddrEnv),
			{ <parser_env_id>, &user_env },
			Dz1ParserEnvEntryLast
		};

		pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&parser);

		if ((*errp = Dz1ParserUtilEnv_check(parse_env)).code) ERR_OUT(errp);
		else if ((*errp = Dz1ParserUtil_addEmitter(parser, <emitter_table>)).code) ERR_OUT(errp);
		else if ((*errp = Dz1ParserInit_parse(parser, <syntax_str>)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Parser_prepare(parser, src_text)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Parser_process(parser, <syntax_name>, (void *)parse_env, 0)).code)
		{
			Dz1Thread_printf("<result_type>_parse() : Parse Fail at %u line\n", Dz1Parser_getLineNum(parser));
			ERR_OUT(errp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Parser_delAndSetNull, (void *)&parser);
	}
	return err;
}
// Typical Parser Function
///////////////////////////////////////////////////////////////////////////////
result_type
parse_env_id
parse_env_type
*/

#endif