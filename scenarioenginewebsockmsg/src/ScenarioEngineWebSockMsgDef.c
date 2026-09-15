////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineWebSockMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketStatusCode
static struct ScenarioEngineWebSocketStatusCodeMapA
{
	str_t str;
	ScenarioEngineWebSocketStatusCode v;
} ScenarioEngineWebSocketStatusCodeMapA[] =
{
	{ (char *)"Informational", ScenarioEngineWebSocketStatusCode_Informational },
	{ (char *)"OK", ScenarioEngineWebSocketStatusCode_OK },
	{ (char *)"Redirection", ScenarioEngineWebSocketStatusCode_Redirection },
	{ (char *)"ClientError", ScenarioEngineWebSocketStatusCode_ClientError },
	{ (char *)"ServerError", ScenarioEngineWebSocketStatusCode_ServerError },
	{ (char *)"AgentError", ScenarioEngineWebSocketStatusCode_AgentError },
	{ NULL, ScenarioEngineWebSocketStatusCode_max }
};

str_t ScenarioEngineWebSocketStatusCodeStrA(ScenarioEngineWebSocketStatusCode v)
{
	struct ScenarioEngineWebSocketStatusCodeMapA *i = NULL;
	for (i = ScenarioEngineWebSocketStatusCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineWebSocketStatusCode ScenarioEngineWebSocketStatusCodeFromStrA(str_t str)
{
	struct ScenarioEngineWebSocketStatusCodeMapA *i = NULL;
	for (i = ScenarioEngineWebSocketStatusCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineWebSocketStatusCode_max;
}
#ifndef UNIX_SYSTEM
static struct ScenarioEngineWebSocketStatusCodeMapW
{
	wstr_t str;
	ScenarioEngineWebSocketStatusCode v;
} ScenarioEngineWebSocketStatusCodeMapW[] =
{
	{ (wchar_t *)L"Informational", ScenarioEngineWebSocketStatusCode_Informational },
	{ (wchar_t *)L"OK", ScenarioEngineWebSocketStatusCode_OK },
	{ (wchar_t *)L"Redirection", ScenarioEngineWebSocketStatusCode_Redirection },
	{ (wchar_t *)L"ClientError", ScenarioEngineWebSocketStatusCode_ClientError },
	{ (wchar_t *)L"ServerError", ScenarioEngineWebSocketStatusCode_ServerError },
	{ (wchar_t *)L"AgentError", ScenarioEngineWebSocketStatusCode_AgentError },
	{ NULL, ScenarioEngineWebSocketStatusCode_max }
};

wstr_t ScenarioEngineWebSocketStatusCodeStrW(ScenarioEngineWebSocketStatusCode v)
{
	struct ScenarioEngineWebSocketStatusCodeMapW *i = NULL;
	for (i = ScenarioEngineWebSocketStatusCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineWebSocketStatusCode ScenarioEngineWebSocketStatusCodeFromStrW(wstr_t str)
{
	struct ScenarioEngineWebSocketStatusCodeMapW *i = NULL;
	for (i = ScenarioEngineWebSocketStatusCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineWebSocketStatusCode_max;
}
#endif // UNIX_SYSTEM

ScenarioEngineWebSocketStatusCode *ScenarioEngineWebSocketStatusCode_new(ScenarioEngineWebSocketStatusCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineWebSocketStatusCode *__internal_ret = (ScenarioEngineWebSocketStatusCode *)Dz1Calloc(sizeof(ScenarioEngineWebSocketStatusCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ScenarioEngineWebSocketStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineProcessStatusCode
static struct ScenarioEngineProcessStatusCodeMapA
{
	str_t str;
	ScenarioEngineProcessStatusCode v;
} ScenarioEngineProcessStatusCodeMapA[] =
{
	{ (char *)"OK", ScenarioEngineProcessStatusCode_OK },
	{ (char *)"FAILURE", ScenarioEngineProcessStatusCode_FAILURE },
	{ (char *)"AGENT_SYSTEM_ERROR", ScenarioEngineProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (char *)"SERVER_DISCONNECTED", ScenarioEngineProcessStatusCode_SERVER_DISCONNECTED },
	{ (char *)"TEST_CONFIGURATION_ERROR", ScenarioEngineProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (char *)"CONNECTION_FAIL", ScenarioEngineProcessStatusCode_CONNECTION_FAIL },
	{ (char *)"DISCONNECTED", ScenarioEngineProcessStatusCode_DISCONNECTED },
	{ (char *)"TIMEOUT", ScenarioEngineProcessStatusCode_TIMEOUT },
	{ (char *)"OUT_OF_RANGE", ScenarioEngineProcessStatusCode_OUT_OF_RANGE },
	{ (char *)"INVALID_PROCESS", ScenarioEngineProcessStatusCode_INVALID_PROCESS },
	{ (char *)"INVALID_IDENTIFIER", ScenarioEngineProcessStatusCode_INVALID_IDENTIFIER },
	{ (char *)"SESSION_DUPLICATE", ScenarioEngineProcessStatusCode_SESSION_DUPLICATE },
	{ (char *)"LOGIN_AUTH_ERROR", ScenarioEngineProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (char *)"DECODE_FAIL", ScenarioEngineProcessStatusCode_DECODE_FAIL },
	{ (char *)"INVALID_ENCODING_RULE", ScenarioEngineProcessStatusCode_INVALID_ENCODING_RULE },
	{ (char *)"INVALID_OID", ScenarioEngineProcessStatusCode_INVALID_OID },
	{ (char *)"INVALID_DSRC_MSG_ID", ScenarioEngineProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (char *)"JSON_PARSE_ERROR", ScenarioEngineProcessStatusCode_JSON_PARSE_ERROR },
	{ (char *)"PROTOBUF_DESERAILIZE_ERROR", ScenarioEngineProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (char *)"INVALID_TOPIC", ScenarioEngineProcessStatusCode_INVALID_TOPIC },
	{ (char *)"INVALID_REQUEST", ScenarioEngineProcessStatusCode_INVALID_REQUEST },
	{ (char *)"UNKNOWN", ScenarioEngineProcessStatusCode_UNKNOWN },
	{ NULL, ScenarioEngineProcessStatusCode_max }
};

str_t ScenarioEngineProcessStatusCodeStrA(ScenarioEngineProcessStatusCode v)
{
	struct ScenarioEngineProcessStatusCodeMapA *i = NULL;
	for (i = ScenarioEngineProcessStatusCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineProcessStatusCode ScenarioEngineProcessStatusCodeFromStrA(str_t str)
{
	struct ScenarioEngineProcessStatusCodeMapA *i = NULL;
	for (i = ScenarioEngineProcessStatusCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineProcessStatusCode_max;
}
#ifndef UNIX_SYSTEM
static struct ScenarioEngineProcessStatusCodeMapW
{
	wstr_t str;
	ScenarioEngineProcessStatusCode v;
} ScenarioEngineProcessStatusCodeMapW[] =
{
	{ (wchar_t *)L"OK", ScenarioEngineProcessStatusCode_OK },
	{ (wchar_t *)L"FAILURE", ScenarioEngineProcessStatusCode_FAILURE },
	{ (wchar_t *)L"AGENT_SYSTEM_ERROR", ScenarioEngineProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (wchar_t *)L"SERVER_DISCONNECTED", ScenarioEngineProcessStatusCode_SERVER_DISCONNECTED },
	{ (wchar_t *)L"TEST_CONFIGURATION_ERROR", ScenarioEngineProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (wchar_t *)L"CONNECTION_FAIL", ScenarioEngineProcessStatusCode_CONNECTION_FAIL },
	{ (wchar_t *)L"DISCONNECTED", ScenarioEngineProcessStatusCode_DISCONNECTED },
	{ (wchar_t *)L"TIMEOUT", ScenarioEngineProcessStatusCode_TIMEOUT },
	{ (wchar_t *)L"OUT_OF_RANGE", ScenarioEngineProcessStatusCode_OUT_OF_RANGE },
	{ (wchar_t *)L"INVALID_PROCESS", ScenarioEngineProcessStatusCode_INVALID_PROCESS },
	{ (wchar_t *)L"INVALID_IDENTIFIER", ScenarioEngineProcessStatusCode_INVALID_IDENTIFIER },
	{ (wchar_t *)L"SESSION_DUPLICATE", ScenarioEngineProcessStatusCode_SESSION_DUPLICATE },
	{ (wchar_t *)L"LOGIN_AUTH_ERROR", ScenarioEngineProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (wchar_t *)L"DECODE_FAIL", ScenarioEngineProcessStatusCode_DECODE_FAIL },
	{ (wchar_t *)L"INVALID_ENCODING_RULE", ScenarioEngineProcessStatusCode_INVALID_ENCODING_RULE },
	{ (wchar_t *)L"INVALID_OID", ScenarioEngineProcessStatusCode_INVALID_OID },
	{ (wchar_t *)L"INVALID_DSRC_MSG_ID", ScenarioEngineProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (wchar_t *)L"JSON_PARSE_ERROR", ScenarioEngineProcessStatusCode_JSON_PARSE_ERROR },
	{ (wchar_t *)L"PROTOBUF_DESERAILIZE_ERROR", ScenarioEngineProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (wchar_t *)L"INVALID_TOPIC", ScenarioEngineProcessStatusCode_INVALID_TOPIC },
	{ (wchar_t *)L"INVALID_REQUEST", ScenarioEngineProcessStatusCode_INVALID_REQUEST },
	{ (wchar_t *)L"UNKNOWN", ScenarioEngineProcessStatusCode_UNKNOWN },
	{ NULL, ScenarioEngineProcessStatusCode_max }
};

wstr_t ScenarioEngineProcessStatusCodeStrW(ScenarioEngineProcessStatusCode v)
{
	struct ScenarioEngineProcessStatusCodeMapW *i = NULL;
	for (i = ScenarioEngineProcessStatusCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineProcessStatusCode ScenarioEngineProcessStatusCodeFromStrW(wstr_t str)
{
	struct ScenarioEngineProcessStatusCodeMapW *i = NULL;
	for (i = ScenarioEngineProcessStatusCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineProcessStatusCode_max;
}
#endif // UNIX_SYSTEM

ScenarioEngineProcessStatusCode *ScenarioEngineProcessStatusCode_new(ScenarioEngineProcessStatusCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineProcessStatusCode *__internal_ret = (ScenarioEngineProcessStatusCode *)Dz1Calloc(sizeof(ScenarioEngineProcessStatusCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ScenarioEngineProcessStatusCode_dump(ScenarioEngineProcessStatusCode *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ScenarioEngineProcessStatusCodeStr(*v));
}
// ScenarioEngineProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageDefault
ScenarioEngineRequestMessageDefault *ScenarioEngineRequestMessageDefault_new(Dz1Str method, 
																			 u32_t seq, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageDefault *__internal_ret = (ScenarioEngineRequestMessageDefault *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageDefault_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageDefault_copy(ScenarioEngineRequestMessageDefault *dst, ScenarioEngineRequestMessageDefault *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageDefault *ScenarioEngineRequestMessageDefault_clone(ScenarioEngineRequestMessageDefault *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageDefault *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageDefault *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageDefault), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageDefault_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageDefault_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageDefault_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageDefault_purge(ScenarioEngineRequestMessageDefault *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
}

void ScenarioEngineRequestMessageDefault_del(ScenarioEngineRequestMessageDefault *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageDefault_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageDefault_dump(ScenarioEngineRequestMessageDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageDefault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageDescribe
ScenarioEngineRequestMessageDescribe *ScenarioEngineRequestMessageDescribe_new(Dz1Str method, 
																			   u32_t seq, 
																			   Dz1Str type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageDescribe *__internal_ret = (ScenarioEngineRequestMessageDescribe *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageDescribe), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageDescribe_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else if (type && (__internal_ret->type = Dz1Str_clone(type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageDescribe_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageDescribe_copy(ScenarioEngineRequestMessageDescribe *dst, ScenarioEngineRequestMessageDescribe *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else if (src->type && (dst->type = Dz1Str_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageDescribe *ScenarioEngineRequestMessageDescribe_clone(ScenarioEngineRequestMessageDescribe *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageDescribe *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageDescribe *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageDescribe), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageDescribe_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageDescribe_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageDescribe_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageDescribe_purge(ScenarioEngineRequestMessageDescribe *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
	Dz1Str_del(p->type);
}

void ScenarioEngineRequestMessageDescribe_del(ScenarioEngineRequestMessageDescribe *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageDescribe_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageDescribe_dump(ScenarioEngineRequestMessageDescribe *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type = ")); Dz1Str_dump(p->type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageDescribe
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineInitializeContext
ScenarioEngineInitializeContext *ScenarioEngineInitializeContext_new(Dz1Str category, 
																	 Dz1Str testScenario, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineInitializeContext *__internal_ret = (ScenarioEngineInitializeContext *)Dz1Calloc(sizeof(ScenarioEngineInitializeContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineInitializeContext_delAndSetNull, (void *)&__internal_ret);
		
		if (category && (__internal_ret->category = Dz1Str_clone(category, errp)) == NULL) ERR_OUT(errp);
		else if (testScenario && (__internal_ret->testScenario = Dz1Str_clone(testScenario, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineInitializeContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineInitializeContext_copy(ScenarioEngineInitializeContext *dst, ScenarioEngineInitializeContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->category && (dst->category = Dz1Str_clone(src->category, errp)) == NULL) ERR_OUT(errp);
	else if (src->testScenario && (dst->testScenario = Dz1Str_clone(src->testScenario, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineInitializeContext *ScenarioEngineInitializeContext_clone(ScenarioEngineInitializeContext *src, Dz1Error *err)
{
	ScenarioEngineInitializeContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineInitializeContext *)Dz1Calloc(sizeof(ScenarioEngineInitializeContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineInitializeContext_delAndSetNull, (void *)&dst);
		if (ScenarioEngineInitializeContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineInitializeContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineInitializeContext_purge(ScenarioEngineInitializeContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->category);
	Dz1Str_del(p->testScenario);
}

void ScenarioEngineInitializeContext_del(ScenarioEngineInitializeContext *p)
{
	if (p == NULL) return;
	ScenarioEngineInitializeContext_purge(p);
	Dz1Free(p);
}

void ScenarioEngineInitializeContext_dump(ScenarioEngineInitializeContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("category = ")); Dz1Str_dump(p->category, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testScenario = ")); Dz1Str_dump(p->testScenario, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineInitializeContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageInitialize
ScenarioEngineRequestMessageInitialize *ScenarioEngineRequestMessageInitialize_new(Dz1Str method, 
																				   u32_t seq, 
																				   Dz1Binary *testScenario, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageInitialize *__internal_ret = (ScenarioEngineRequestMessageInitialize *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageInitialize), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageInitialize_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			__internal_ret->testScenario = testScenario;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageInitialize_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageInitialize_copy(ScenarioEngineRequestMessageInitialize *dst, ScenarioEngineRequestMessageInitialize *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else if (src->testScenario && (dst->testScenario = Dz1Binary_clone(src->testScenario, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageInitialize *ScenarioEngineRequestMessageInitialize_clone(ScenarioEngineRequestMessageInitialize *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageInitialize *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageInitialize *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageInitialize), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageInitialize_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageInitialize_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageInitialize_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageInitialize_purge(ScenarioEngineRequestMessageInitialize *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
	Dz1Binary_del(p->testScenario);
}

void ScenarioEngineRequestMessageInitialize_del(ScenarioEngineRequestMessageInitialize *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageInitialize_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageInitialize_dump(ScenarioEngineRequestMessageInitialize *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("testScenario = ")); Dz1Binary_dump(p->testScenario, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageInitialize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageUIConfigure
ScenarioEngineRequestMessageUIConfigure *ScenarioEngineRequestMessageUIConfigure_new(Dz1Str method, 
																					 u32_t seq, 
																					 Dz1Binary *conf, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageUIConfigure *__internal_ret = (ScenarioEngineRequestMessageUIConfigure *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageUIConfigure), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageUIConfigure_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			__internal_ret->conf = conf;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageUIConfigure_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageUIConfigure_copy(ScenarioEngineRequestMessageUIConfigure *dst, ScenarioEngineRequestMessageUIConfigure *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else if (src->conf && (dst->conf = Dz1Binary_clone(src->conf, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageUIConfigure *ScenarioEngineRequestMessageUIConfigure_clone(ScenarioEngineRequestMessageUIConfigure *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageUIConfigure *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageUIConfigure *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageUIConfigure), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageUIConfigure_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageUIConfigure_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageUIConfigure_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageUIConfigure_purge(ScenarioEngineRequestMessageUIConfigure *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
	Dz1Binary_del(p->conf);
}

void ScenarioEngineRequestMessageUIConfigure_del(ScenarioEngineRequestMessageUIConfigure *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageUIConfigure_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageUIConfigure_dump(ScenarioEngineRequestMessageUIConfigure *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("conf = ")); Dz1Binary_dump(p->conf, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageUIConfigure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageWithData
ScenarioEngineRequestMessageWithData *ScenarioEngineRequestMessageWithData_new(Dz1Str method, 
																			   u32_t seq, 
																			   Dz1Str data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageWithData *__internal_ret = (ScenarioEngineRequestMessageWithData *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageWithData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageWithData_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else if (data && (__internal_ret->data = Dz1Str_clone(data, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageWithData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageWithData_copy(ScenarioEngineRequestMessageWithData *dst, ScenarioEngineRequestMessageWithData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1Str_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageWithData *ScenarioEngineRequestMessageWithData_clone(ScenarioEngineRequestMessageWithData *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageWithData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageWithData *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageWithData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageWithData_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageWithData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageWithData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageWithData_purge(ScenarioEngineRequestMessageWithData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
	Dz1Str_del(p->data);
}

void ScenarioEngineRequestMessageWithData_del(ScenarioEngineRequestMessageWithData *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageWithData_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageWithData_dump(ScenarioEngineRequestMessageWithData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Str_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageWithData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageSetup
ScenarioEngineRequestMessageSetup *ScenarioEngineRequestMessageSetup_new(Dz1Str method, 
																		 u32_t seq, 
																		 Dz1Str testConfiguration, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageSetup *__internal_ret = (ScenarioEngineRequestMessageSetup *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageSetup), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageSetup_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else if (testConfiguration && (__internal_ret->testConfiguration = Dz1Str_clone(testConfiguration, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageSetup_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageSetup_copy(ScenarioEngineRequestMessageSetup *dst, ScenarioEngineRequestMessageSetup *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else if (src->testConfiguration && (dst->testConfiguration = Dz1Str_clone(src->testConfiguration, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageSetup *ScenarioEngineRequestMessageSetup_clone(ScenarioEngineRequestMessageSetup *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageSetup *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageSetup *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageSetup), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageSetup_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageSetup_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageSetup_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageSetup_purge(ScenarioEngineRequestMessageSetup *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
	Dz1Str_del(p->testConfiguration);
}

void ScenarioEngineRequestMessageSetup_del(ScenarioEngineRequestMessageSetup *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageSetup_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageSetup_dump(ScenarioEngineRequestMessageSetup *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testConfiguration = ")); Dz1Str_dump(p->testConfiguration, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageSetup
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyStateContext
ScenarioEngineNotifyStateContext *ScenarioEngineNotifyStateContext_new(Dz1Str testName, 
																	   s64_t time, 
																	   Dz1Str state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineNotifyStateContext *__internal_ret = (ScenarioEngineNotifyStateContext *)Dz1Calloc(sizeof(ScenarioEngineNotifyStateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyStateContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (state && (__internal_ret->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyStateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineNotifyStateContext_copy(ScenarioEngineNotifyStateContext *dst, ScenarioEngineNotifyStateContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->testName && (dst->testName = Dz1Str_clone(src->testName, errp)) == NULL) ERR_OUT(errp);
	else if (src->state && (dst->state = Dz1Str_clone(src->state, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->time = src->time;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineNotifyStateContext *ScenarioEngineNotifyStateContext_clone(ScenarioEngineNotifyStateContext *src, Dz1Error *err)
{
	ScenarioEngineNotifyStateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineNotifyStateContext *)Dz1Calloc(sizeof(ScenarioEngineNotifyStateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyStateContext_delAndSetNull, (void *)&dst);
		if (ScenarioEngineNotifyStateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyStateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineNotifyStateContext_purge(ScenarioEngineNotifyStateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->state);
}

void ScenarioEngineNotifyStateContext_del(ScenarioEngineNotifyStateContext *p)
{
	if (p == NULL) return;
	ScenarioEngineNotifyStateContext_purge(p);
	Dz1Free(p);
}

void ScenarioEngineNotifyStateContext_dump(ScenarioEngineNotifyStateContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = ")); Dz1Str_dump(p->state, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyInfoContext
ScenarioEngineNotifyInfoContext *ScenarioEngineNotifyInfoContext_new(Dz1Str testName, 
																	 s64_t time, 
																	 Dz1Str sender, 
																	 Dz1Str log, 
																	 Dz1Binary *data, 
																	 Dz1Str dataType, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineNotifyInfoContext *__internal_ret = (ScenarioEngineNotifyInfoContext *)Dz1Calloc(sizeof(ScenarioEngineNotifyInfoContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyInfoContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (sender && (__internal_ret->sender = Dz1Str_clone(sender, errp)) == NULL) ERR_OUT(errp);
		else if (log && (__internal_ret->log = Dz1Str_clone(log, errp)) == NULL) ERR_OUT(errp);
		else if (dataType && (__internal_ret->dataType = Dz1Str_clone(dataType, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyInfoContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineNotifyInfoContext_copy(ScenarioEngineNotifyInfoContext *dst, ScenarioEngineNotifyInfoContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->testName && (dst->testName = Dz1Str_clone(src->testName, errp)) == NULL) ERR_OUT(errp);
	else if (src->sender && (dst->sender = Dz1Str_clone(src->sender, errp)) == NULL) ERR_OUT(errp);
	else if (src->log && (dst->log = Dz1Str_clone(src->log, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1Binary_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else if (src->dataType && (dst->dataType = Dz1Str_clone(src->dataType, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->time = src->time;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineNotifyInfoContext *ScenarioEngineNotifyInfoContext_clone(ScenarioEngineNotifyInfoContext *src, Dz1Error *err)
{
	ScenarioEngineNotifyInfoContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineNotifyInfoContext *)Dz1Calloc(sizeof(ScenarioEngineNotifyInfoContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyInfoContext_delAndSetNull, (void *)&dst);
		if (ScenarioEngineNotifyInfoContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyInfoContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineNotifyInfoContext_purge(ScenarioEngineNotifyInfoContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->sender);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->dataType);
}

void ScenarioEngineNotifyInfoContext_del(ScenarioEngineNotifyInfoContext *p)
{
	if (p == NULL) return;
	ScenarioEngineNotifyInfoContext_purge(p);
	Dz1Free(p);
}

void ScenarioEngineNotifyInfoContext_dump(ScenarioEngineNotifyInfoContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sender = ")); Dz1Str_dump(p->sender, tab); 
		Dz1Thread_tprintf(tab, Dz1T("log = ")); Dz1Str_dump(p->log, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dataType = ")); Dz1Str_dump(p->dataType, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyErrorContext
ScenarioEngineNotifyErrorContext *ScenarioEngineNotifyErrorContext_new(Dz1Str testName, 
																	   s64_t time, 
																	   ScenarioEngineProcessStatusCode code, 
																	   Dz1Str desc, 
																	   Dz1Str log, 
																	   Dz1Binary *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineNotifyErrorContext *__internal_ret = (ScenarioEngineNotifyErrorContext *)Dz1Calloc(sizeof(ScenarioEngineNotifyErrorContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyErrorContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (desc && (__internal_ret->desc = Dz1Str_clone(desc, errp)) == NULL) ERR_OUT(errp);
		else if (log && (__internal_ret->log = Dz1Str_clone(log, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			__internal_ret->code = code;
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyErrorContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineNotifyErrorContext_copy(ScenarioEngineNotifyErrorContext *dst, ScenarioEngineNotifyErrorContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->testName && (dst->testName = Dz1Str_clone(src->testName, errp)) == NULL) ERR_OUT(errp);
	else if (src->desc && (dst->desc = Dz1Str_clone(src->desc, errp)) == NULL) ERR_OUT(errp);
	else if (src->log && (dst->log = Dz1Str_clone(src->log, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1Binary_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->time = src->time;
		dst->code = src->code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineNotifyErrorContext *ScenarioEngineNotifyErrorContext_clone(ScenarioEngineNotifyErrorContext *src, Dz1Error *err)
{
	ScenarioEngineNotifyErrorContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineNotifyErrorContext *)Dz1Calloc(sizeof(ScenarioEngineNotifyErrorContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyErrorContext_delAndSetNull, (void *)&dst);
		if (ScenarioEngineNotifyErrorContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyErrorContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineNotifyErrorContext_purge(ScenarioEngineNotifyErrorContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->desc);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
}

void ScenarioEngineNotifyErrorContext_del(ScenarioEngineNotifyErrorContext *p)
{
	if (p == NULL) return;
	ScenarioEngineNotifyErrorContext_purge(p);
	Dz1Free(p);
}

void ScenarioEngineNotifyErrorContext_dump(ScenarioEngineNotifyErrorContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), ScenarioEngineProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("log = ")); Dz1Str_dump(p->log, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyStateArg
ScenarioEngineNotifyStateArg *ScenarioEngineNotifyStateArg_new(u32_t testIdx, 
															   ScenarioEngineNotifyStateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineNotifyStateArg *__internal_ret = (ScenarioEngineNotifyStateArg *)Dz1Calloc(sizeof(ScenarioEngineNotifyStateArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyStateArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyStateArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineNotifyStateArg_copy(ScenarioEngineNotifyStateArg *dst, ScenarioEngineNotifyStateArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = ScenarioEngineNotifyStateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineNotifyStateArg *ScenarioEngineNotifyStateArg_clone(ScenarioEngineNotifyStateArg *src, Dz1Error *err)
{
	ScenarioEngineNotifyStateArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineNotifyStateArg *)Dz1Calloc(sizeof(ScenarioEngineNotifyStateArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyStateArg_delAndSetNull, (void *)&dst);
		if (ScenarioEngineNotifyStateArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyStateArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineNotifyStateArg_purge(ScenarioEngineNotifyStateArg *p)
{
	if (p == NULL) return;
	ScenarioEngineNotifyStateContext_del(p->context);
}

void ScenarioEngineNotifyStateArg_del(ScenarioEngineNotifyStateArg *p)
{
	if (p == NULL) return;
	ScenarioEngineNotifyStateArg_purge(p);
	Dz1Free(p);
}

void ScenarioEngineNotifyStateArg_dump(ScenarioEngineNotifyStateArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); ScenarioEngineNotifyStateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineNotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyInfoArg
ScenarioEngineNotifyInfoArg *ScenarioEngineNotifyInfoArg_new(u32_t testIdx, 
															 ScenarioEngineNotifyInfoContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineNotifyInfoArg *__internal_ret = (ScenarioEngineNotifyInfoArg *)Dz1Calloc(sizeof(ScenarioEngineNotifyInfoArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyInfoArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyInfoArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineNotifyInfoArg_copy(ScenarioEngineNotifyInfoArg *dst, ScenarioEngineNotifyInfoArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = ScenarioEngineNotifyInfoContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineNotifyInfoArg *ScenarioEngineNotifyInfoArg_clone(ScenarioEngineNotifyInfoArg *src, Dz1Error *err)
{
	ScenarioEngineNotifyInfoArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineNotifyInfoArg *)Dz1Calloc(sizeof(ScenarioEngineNotifyInfoArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyInfoArg_delAndSetNull, (void *)&dst);
		if (ScenarioEngineNotifyInfoArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyInfoArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineNotifyInfoArg_purge(ScenarioEngineNotifyInfoArg *p)
{
	if (p == NULL) return;
	ScenarioEngineNotifyInfoContext_del(p->context);
}

void ScenarioEngineNotifyInfoArg_del(ScenarioEngineNotifyInfoArg *p)
{
	if (p == NULL) return;
	ScenarioEngineNotifyInfoArg_purge(p);
	Dz1Free(p);
}

void ScenarioEngineNotifyInfoArg_dump(ScenarioEngineNotifyInfoArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); ScenarioEngineNotifyInfoContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineNotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyErrorArg
ScenarioEngineNotifyErrorArg *ScenarioEngineNotifyErrorArg_new(u32_t testIdx, 
															   ScenarioEngineNotifyErrorContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineNotifyErrorArg *__internal_ret = (ScenarioEngineNotifyErrorArg *)Dz1Calloc(sizeof(ScenarioEngineNotifyErrorArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyErrorArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyErrorArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineNotifyErrorArg_copy(ScenarioEngineNotifyErrorArg *dst, ScenarioEngineNotifyErrorArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = ScenarioEngineNotifyErrorContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineNotifyErrorArg *ScenarioEngineNotifyErrorArg_clone(ScenarioEngineNotifyErrorArg *src, Dz1Error *err)
{
	ScenarioEngineNotifyErrorArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineNotifyErrorArg *)Dz1Calloc(sizeof(ScenarioEngineNotifyErrorArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyErrorArg_delAndSetNull, (void *)&dst);
		if (ScenarioEngineNotifyErrorArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineNotifyErrorArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineNotifyErrorArg_purge(ScenarioEngineNotifyErrorArg *p)
{
	if (p == NULL) return;
	ScenarioEngineNotifyErrorContext_del(p->context);
}

void ScenarioEngineNotifyErrorArg_del(ScenarioEngineNotifyErrorArg *p)
{
	if (p == NULL) return;
	ScenarioEngineNotifyErrorArg_purge(p);
	Dz1Free(p);
}

void ScenarioEngineNotifyErrorArg_dump(ScenarioEngineNotifyErrorArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); ScenarioEngineNotifyErrorContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineNotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyState
ScenarioEngineRequestMessageNotifyState *ScenarioEngineRequestMessageNotifyState_new(Dz1Str method, 
																					 u32_t seq, 
																					 u32_t testIdx, 
																					 Dz1Str level, 
																					 ScenarioEngineNotifyStateContext *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageNotifyState *__internal_ret = (ScenarioEngineRequestMessageNotifyState *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageNotifyState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageNotifyState_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else if (level && (__internal_ret->level = Dz1Str_clone(level, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			__internal_ret->testIdx = testIdx;
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageNotifyState_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageNotifyState_copy(ScenarioEngineRequestMessageNotifyState *dst, ScenarioEngineRequestMessageNotifyState *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else if (src->level && (dst->level = Dz1Str_clone(src->level, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = ScenarioEngineNotifyStateContext_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageNotifyState *ScenarioEngineRequestMessageNotifyState_clone(ScenarioEngineRequestMessageNotifyState *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageNotifyState *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageNotifyState *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageNotifyState), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageNotifyState_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageNotifyState_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageNotifyState_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageNotifyState_purge(ScenarioEngineRequestMessageNotifyState *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
	Dz1Str_del(p->level);
	ScenarioEngineNotifyStateContext_del(p->data);
}

void ScenarioEngineRequestMessageNotifyState_del(ScenarioEngineRequestMessageNotifyState *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageNotifyState_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageNotifyState_dump(ScenarioEngineRequestMessageNotifyState *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("level = ")); Dz1Str_dump(p->level, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); ScenarioEngineNotifyStateContext_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageNotifyState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyInfo
ScenarioEngineRequestMessageNotifyInfo *ScenarioEngineRequestMessageNotifyInfo_new(Dz1Str method, 
																				   u32_t seq, 
																				   u32_t testIdx, 
																				   Dz1Str level, 
																				   ScenarioEngineNotifyInfoContext *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageNotifyInfo *__internal_ret = (ScenarioEngineRequestMessageNotifyInfo *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageNotifyInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageNotifyInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else if (level && (__internal_ret->level = Dz1Str_clone(level, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			__internal_ret->testIdx = testIdx;
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageNotifyInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageNotifyInfo_copy(ScenarioEngineRequestMessageNotifyInfo *dst, ScenarioEngineRequestMessageNotifyInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else if (src->level && (dst->level = Dz1Str_clone(src->level, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = ScenarioEngineNotifyInfoContext_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageNotifyInfo *ScenarioEngineRequestMessageNotifyInfo_clone(ScenarioEngineRequestMessageNotifyInfo *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageNotifyInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageNotifyInfo *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageNotifyInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageNotifyInfo_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageNotifyInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageNotifyInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageNotifyInfo_purge(ScenarioEngineRequestMessageNotifyInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
	Dz1Str_del(p->level);
	ScenarioEngineNotifyInfoContext_del(p->data);
}

void ScenarioEngineRequestMessageNotifyInfo_del(ScenarioEngineRequestMessageNotifyInfo *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageNotifyInfo_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageNotifyInfo_dump(ScenarioEngineRequestMessageNotifyInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("level = ")); Dz1Str_dump(p->level, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); ScenarioEngineNotifyInfoContext_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageNotifyInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyError
ScenarioEngineRequestMessageNotifyError *ScenarioEngineRequestMessageNotifyError_new(Dz1Str method, 
																					 u32_t seq, 
																					 u32_t testIdx, 
																					 Dz1Str level, 
																					 ScenarioEngineNotifyErrorContext *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageNotifyError *__internal_ret = (ScenarioEngineRequestMessageNotifyError *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageNotifyError), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageNotifyError_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else if (level && (__internal_ret->level = Dz1Str_clone(level, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			__internal_ret->testIdx = testIdx;
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageNotifyError_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageNotifyError_copy(ScenarioEngineRequestMessageNotifyError *dst, ScenarioEngineRequestMessageNotifyError *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else if (src->level && (dst->level = Dz1Str_clone(src->level, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = ScenarioEngineNotifyErrorContext_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageNotifyError *ScenarioEngineRequestMessageNotifyError_clone(ScenarioEngineRequestMessageNotifyError *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageNotifyError *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageNotifyError *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageNotifyError), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageNotifyError_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageNotifyError_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageNotifyError_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageNotifyError_purge(ScenarioEngineRequestMessageNotifyError *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
	Dz1Str_del(p->level);
	ScenarioEngineNotifyErrorContext_del(p->data);
}

void ScenarioEngineRequestMessageNotifyError_del(ScenarioEngineRequestMessageNotifyError *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageNotifyError_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageNotifyError_dump(ScenarioEngineRequestMessageNotifyError *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("level = ")); Dz1Str_dump(p->level, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); ScenarioEngineNotifyErrorContext_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageNotifyError
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyPresent
static struct ScenarioEngineRequestMessageNotifyPresentMapA
{
	str_t str;
	ScenarioEngineRequestMessageNotifyPresent v;
} ScenarioEngineRequestMessageNotifyPresentMapA[] =
{
	{ (char *)"state", ScenarioEngineRequestMessageNotifyPresent_state },
	{ (char *)"info", ScenarioEngineRequestMessageNotifyPresent_info },
	{ (char *)"error", ScenarioEngineRequestMessageNotifyPresent_error },
	{ NULL, ScenarioEngineRequestMessageNotifyPresent_max }
};

str_t ScenarioEngineRequestMessageNotifyPresentStrA(ScenarioEngineRequestMessageNotifyPresent v)
{
	struct ScenarioEngineRequestMessageNotifyPresentMapA *i = NULL;
	for (i = ScenarioEngineRequestMessageNotifyPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineRequestMessageNotifyPresent ScenarioEngineRequestMessageNotifyPresentFromStrA(str_t str)
{
	struct ScenarioEngineRequestMessageNotifyPresentMapA *i = NULL;
	for (i = ScenarioEngineRequestMessageNotifyPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineRequestMessageNotifyPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ScenarioEngineRequestMessageNotifyPresentMapW
{
	wstr_t str;
	ScenarioEngineRequestMessageNotifyPresent v;
} ScenarioEngineRequestMessageNotifyPresentMapW[] =
{
	{ (wchar_t *)L"state", ScenarioEngineRequestMessageNotifyPresent_state },
	{ (wchar_t *)L"info", ScenarioEngineRequestMessageNotifyPresent_info },
	{ (wchar_t *)L"error", ScenarioEngineRequestMessageNotifyPresent_error },
	{ NULL, ScenarioEngineRequestMessageNotifyPresent_max }
};

wstr_t ScenarioEngineRequestMessageNotifyPresentStrW(ScenarioEngineRequestMessageNotifyPresent v)
{
	struct ScenarioEngineRequestMessageNotifyPresentMapW *i = NULL;
	for (i = ScenarioEngineRequestMessageNotifyPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineRequestMessageNotifyPresent ScenarioEngineRequestMessageNotifyPresentFromStrW(wstr_t str)
{
	struct ScenarioEngineRequestMessageNotifyPresentMapW *i = NULL;
	for (i = ScenarioEngineRequestMessageNotifyPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineRequestMessageNotifyPresent_max;
}
#endif // UNIX_SYSTEM

ScenarioEngineRequestMessageNotifyPresent *ScenarioEngineRequestMessageNotifyPresent_new(ScenarioEngineRequestMessageNotifyPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageNotifyPresent *__internal_ret = (ScenarioEngineRequestMessageNotifyPresent *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageNotifyPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ScenarioEngineRequestMessageNotifyPresent_dump(ScenarioEngineRequestMessageNotifyPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ScenarioEngineRequestMessageNotifyPresentStr(*v));
}
// ScenarioEngineRequestMessageNotifyPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotify
ScenarioEngineRequestMessageNotify *ScenarioEngineRequestMessageNotify_new(ScenarioEngineRequestMessageNotifyPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageNotify *ret = (ScenarioEngineRequestMessageNotify *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageNotify), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageNotify_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ScenarioEngineRequestMessageNotifyPresent_state:
			// _U_cst_clone
			if (ptr != NULL) ret->x.state = (ScenarioEngineRequestMessageNotifyState *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineRequestMessageNotifyPresent_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.info = (ScenarioEngineRequestMessageNotifyInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineRequestMessageNotifyPresent_error:
			// _U_cst_clone
			if (ptr != NULL) ret->x.error = (ScenarioEngineRequestMessageNotifyError *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineRequestMessageNotifyPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageNotify_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t ScenarioEngineRequestMessageNotify_copy(ScenarioEngineRequestMessageNotify *ret, ScenarioEngineRequestMessageNotify *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case ScenarioEngineRequestMessageNotifyPresent_state:
			// _U_cst_clone
			if (src->x.state && (ret->x.state = ScenarioEngineRequestMessageNotifyState_clone(src->x.state, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ScenarioEngineRequestMessageNotifyPresent_info:
			// _U_cst_clone
			if (src->x.info && (ret->x.info = ScenarioEngineRequestMessageNotifyInfo_clone(src->x.info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ScenarioEngineRequestMessageNotifyPresent_error:
			// _U_cst_clone
			if (src->x.error && (ret->x.error = ScenarioEngineRequestMessageNotifyError_clone(src->x.error, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageNotify *ScenarioEngineRequestMessageNotify_clone(ScenarioEngineRequestMessageNotify *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageNotify *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (ScenarioEngineRequestMessageNotify *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageNotify), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageNotify_delAndSetNull, (void *)&ret);
		if (ScenarioEngineRequestMessageNotify_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageNotify_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ScenarioEngineRequestMessageNotify_purge(ScenarioEngineRequestMessageNotify *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ScenarioEngineRequestMessageNotifyPresent_state:
		ScenarioEngineRequestMessageNotifyState_del(p->x.state);
		break;
	case ScenarioEngineRequestMessageNotifyPresent_info:
		ScenarioEngineRequestMessageNotifyInfo_del(p->x.info);
		break;
	case ScenarioEngineRequestMessageNotifyPresent_error:
		ScenarioEngineRequestMessageNotifyError_del(p->x.error);
		break;
	default:
		break;
	}
}

void ScenarioEngineRequestMessageNotify_del(ScenarioEngineRequestMessageNotify *p)
{
	if (!p) return;
	ScenarioEngineRequestMessageNotify_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageNotify_dump(ScenarioEngineRequestMessageNotify *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ScenarioEngineRequestMessageNotifyPresent_state:
		Dz1Thread_printf(Dz1T("state = ")); ScenarioEngineRequestMessageNotifyState_dump(p->x.state, tab); 
		break;
	case ScenarioEngineRequestMessageNotifyPresent_info:
		Dz1Thread_printf(Dz1T("info = ")); ScenarioEngineRequestMessageNotifyInfo_dump(p->x.info, tab); 
		break;
	case ScenarioEngineRequestMessageNotifyPresent_error:
		Dz1Thread_printf(Dz1T("error = ")); ScenarioEngineRequestMessageNotifyError_dump(p->x.error, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// ScenarioEngineRequestMessageNotify
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineValidateContext
ScenarioEngineValidateContext *ScenarioEngineValidateContext_new(Dz1Str testName, 
																 s64_t time, 
																 Dz1Binary *raw, 
																 Dz1Binary *data, 
																 ScenarioEngineProcessStatusCode code, 
																 Dz1Str desc, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineValidateContext *__internal_ret = (ScenarioEngineValidateContext *)Dz1Calloc(sizeof(ScenarioEngineValidateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineValidateContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (desc && (__internal_ret->desc = Dz1Str_clone(desc, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			__internal_ret->raw = raw;
			__internal_ret->data = data;
			__internal_ret->code = code;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineValidateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineValidateContext_copy(ScenarioEngineValidateContext *dst, ScenarioEngineValidateContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->testName && (dst->testName = Dz1Str_clone(src->testName, errp)) == NULL) ERR_OUT(errp);
	else if (src->raw && (dst->raw = Dz1Binary_clone(src->raw, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1Binary_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else if (src->desc && (dst->desc = Dz1Str_clone(src->desc, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->time = src->time;
		dst->code = src->code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineValidateContext *ScenarioEngineValidateContext_clone(ScenarioEngineValidateContext *src, Dz1Error *err)
{
	ScenarioEngineValidateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineValidateContext *)Dz1Calloc(sizeof(ScenarioEngineValidateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineValidateContext_delAndSetNull, (void *)&dst);
		if (ScenarioEngineValidateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineValidateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineValidateContext_purge(ScenarioEngineValidateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Binary_del(p->raw);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->desc);
}

void ScenarioEngineValidateContext_del(ScenarioEngineValidateContext *p)
{
	if (p == NULL) return;
	ScenarioEngineValidateContext_purge(p);
	Dz1Free(p);
}

void ScenarioEngineValidateContext_dump(ScenarioEngineValidateContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("raw = ")); Dz1Binary_dump(p->raw, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), ScenarioEngineProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageValidate
ScenarioEngineRequestMessageValidate *ScenarioEngineRequestMessageValidate_new(Dz1Str method, 
																			   u32_t seq, 
																			   u32_t testIdx, 
																			   ScenarioEngineValidateContext *validate, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineRequestMessageValidate *__internal_ret = (ScenarioEngineRequestMessageValidate *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageValidate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageValidate_delAndSetNull, (void *)&__internal_ret);
		
		if (method && (__internal_ret->method = Dz1Str_clone(method, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			__internal_ret->testIdx = testIdx;
			__internal_ret->validate = validate;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageValidate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineRequestMessageValidate_copy(ScenarioEngineRequestMessageValidate *dst, ScenarioEngineRequestMessageValidate *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->method && (dst->method = Dz1Str_clone(src->method, errp)) == NULL) ERR_OUT(errp);
	else if (src->validate && (dst->validate = ScenarioEngineValidateContext_clone(src->validate, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineRequestMessageValidate *ScenarioEngineRequestMessageValidate_clone(ScenarioEngineRequestMessageValidate *src, Dz1Error *err)
{
	ScenarioEngineRequestMessageValidate *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineRequestMessageValidate *)Dz1Calloc(sizeof(ScenarioEngineRequestMessageValidate), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageValidate_delAndSetNull, (void *)&dst);
		if (ScenarioEngineRequestMessageValidate_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineRequestMessageValidate_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineRequestMessageValidate_purge(ScenarioEngineRequestMessageValidate *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->method);
	ScenarioEngineValidateContext_del(p->validate);
}

void ScenarioEngineRequestMessageValidate_del(ScenarioEngineRequestMessageValidate *p)
{
	if (p == NULL) return;
	ScenarioEngineRequestMessageValidate_purge(p);
	Dz1Free(p);
}

void ScenarioEngineRequestMessageValidate_dump(ScenarioEngineRequestMessageValidate *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = ")); Dz1Str_dump(p->method, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("validate = ")); ScenarioEngineValidateContext_dump(p->validate, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineRequestMessageValidate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineResponseMessageValidate
ScenarioEngineResponseMessageValidate *ScenarioEngineResponseMessageValidate_new(u32_t seq, 
																				 u32_t testIdx, 
																				 Dz1Str result, 
																				 ScenarioEngineValidateContext *validate, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineResponseMessageValidate *__internal_ret = (ScenarioEngineResponseMessageValidate *)Dz1Calloc(sizeof(ScenarioEngineResponseMessageValidate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineResponseMessageValidate_delAndSetNull, (void *)&__internal_ret);
		
		if (result && (__internal_ret->result = Dz1Str_clone(result, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->seq = seq;
			__internal_ret->testIdx = testIdx;
			__internal_ret->validate = validate;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineResponseMessageValidate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineResponseMessageValidate_copy(ScenarioEngineResponseMessageValidate *dst, ScenarioEngineResponseMessageValidate *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->result && (dst->result = Dz1Str_clone(src->result, errp)) == NULL) ERR_OUT(errp);
	else if (src->validate && (dst->validate = ScenarioEngineValidateContext_clone(src->validate, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineResponseMessageValidate *ScenarioEngineResponseMessageValidate_clone(ScenarioEngineResponseMessageValidate *src, Dz1Error *err)
{
	ScenarioEngineResponseMessageValidate *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineResponseMessageValidate *)Dz1Calloc(sizeof(ScenarioEngineResponseMessageValidate), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineResponseMessageValidate_delAndSetNull, (void *)&dst);
		if (ScenarioEngineResponseMessageValidate_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineResponseMessageValidate_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineResponseMessageValidate_purge(ScenarioEngineResponseMessageValidate *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->result);
	ScenarioEngineValidateContext_del(p->validate);
}

void ScenarioEngineResponseMessageValidate_del(ScenarioEngineResponseMessageValidate *p)
{
	if (p == NULL) return;
	ScenarioEngineResponseMessageValidate_purge(p);
	Dz1Free(p);
}

void ScenarioEngineResponseMessageValidate_dump(ScenarioEngineResponseMessageValidate *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("result = ")); Dz1Str_dump(p->result, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("validate = ")); ScenarioEngineValidateContext_dump(p->validate, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineResponseMessageValidate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineValidateContextArg
ScenarioEngineValidateContextArg *ScenarioEngineValidateContextArg_new(u32_t testIdx, 
																	   ScenarioEngineValidateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineValidateContextArg *__internal_ret = (ScenarioEngineValidateContextArg *)Dz1Calloc(sizeof(ScenarioEngineValidateContextArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineValidateContextArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineValidateContextArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ScenarioEngineValidateContextArg_copy(ScenarioEngineValidateContextArg *dst, ScenarioEngineValidateContextArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = ScenarioEngineValidateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ScenarioEngineValidateContextArg *ScenarioEngineValidateContextArg_clone(ScenarioEngineValidateContextArg *src, Dz1Error *err)
{
	ScenarioEngineValidateContextArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ScenarioEngineValidateContextArg *)Dz1Calloc(sizeof(ScenarioEngineValidateContextArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ScenarioEngineValidateContextArg_delAndSetNull, (void *)&dst);
		if (ScenarioEngineValidateContextArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineValidateContextArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ScenarioEngineValidateContextArg_purge(ScenarioEngineValidateContextArg *p)
{
	if (p == NULL) return;
	ScenarioEngineValidateContext_del(p->context);
}

void ScenarioEngineValidateContextArg_del(ScenarioEngineValidateContextArg *p)
{
	if (p == NULL) return;
	ScenarioEngineValidateContextArg_purge(p);
	Dz1Free(p);
}

void ScenarioEngineValidateContextArg_dump(ScenarioEngineValidateContextArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); ScenarioEngineValidateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketResponseMessageContext
ScenarioEngineWebSocketResponseMessageContext *ScenarioEngineWebSocketResponseMessageContext_new(ScenarioEngineWebSocketStatusCode code, 
																								 Dz1Str reason, 
																								 Dz1Str data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineWebSocketResponseMessageContext *__internal_ret = (ScenarioEngineWebSocketResponseMessageContext *)Dz1Calloc(sizeof(ScenarioEngineWebSocketResponseMessageContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineWebSocketResponseMessageContext_delAndSetNull, (void *)&__internal_ret);
		
		if (reason && (__internal_ret->reason = Dz1Str_clone(reason, errp)) == NULL) ERR_OUT(errp);
		else if (data && (__internal_ret->data = Dz1Str_clone(data, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->code = code;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineWebSocketResponseMessageContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ScenarioEngineWebSocketResponseMessageContext_purge(ScenarioEngineWebSocketResponseMessageContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->reason);
	Dz1Str_del(p->data);
}

void ScenarioEngineWebSocketResponseMessageContext_del(ScenarioEngineWebSocketResponseMessageContext *p)
{
	if (p == NULL) return;
	ScenarioEngineWebSocketResponseMessageContext_purge(p);
	Dz1Free(p);
}

void ScenarioEngineWebSocketResponseMessageContext_dump(ScenarioEngineWebSocketResponseMessageContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), ScenarioEngineWebSocketStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("reason = ")); Dz1Str_dump(p->reason, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Str_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineWebSocketResponseMessageContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineResponseMessageDefault
ScenarioEngineResponseMessageDefault *ScenarioEngineResponseMessageDefault_new(u32_t seq, 
																			   ScenarioEngineWebSocketResponseMessageContext *result, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineResponseMessageDefault *__internal_ret = (ScenarioEngineResponseMessageDefault *)Dz1Calloc(sizeof(ScenarioEngineResponseMessageDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineResponseMessageDefault_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->seq = seq;
		__internal_ret->result = result;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineResponseMessageDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ScenarioEngineResponseMessageDefault_purge(ScenarioEngineResponseMessageDefault *p)
{
	if (p == NULL) return;
	ScenarioEngineWebSocketResponseMessageContext_del(p->result);
}

void ScenarioEngineResponseMessageDefault_del(ScenarioEngineResponseMessageDefault *p)
{
	if (p == NULL) return;
	ScenarioEngineResponseMessageDefault_purge(p);
	Dz1Free(p);
}

void ScenarioEngineResponseMessageDefault_dump(ScenarioEngineResponseMessageDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u32_dump(&p->seq, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("result = ")); ScenarioEngineWebSocketResponseMessageContext_dump(p->result, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ScenarioEngineResponseMessageDefault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageRequestPresent
static struct ScenarioEngineWebSocketMessageRequestPresentMapA
{
	str_t str;
	ScenarioEngineWebSocketMessageRequestPresent v;
} ScenarioEngineWebSocketMessageRequestPresentMapA[] =
{
	{ (char *)"request", ScenarioEngineWebSocketMessageRequestPresent_request },
	{ (char *)"describe", ScenarioEngineWebSocketMessageRequestPresent_describe },
	{ (char *)"initialize", ScenarioEngineWebSocketMessageRequestPresent_initialize },
	{ (char *)"uiConfigure", ScenarioEngineWebSocketMessageRequestPresent_uiConfigure },
	{ (char *)"withData", ScenarioEngineWebSocketMessageRequestPresent_withData },
	{ (char *)"setup", ScenarioEngineWebSocketMessageRequestPresent_setup },
	{ (char *)"notify", ScenarioEngineWebSocketMessageRequestPresent_notify },
	{ (char *)"validate", ScenarioEngineWebSocketMessageRequestPresent_validate },
	{ NULL, ScenarioEngineWebSocketMessageRequestPresent_max }
};

str_t ScenarioEngineWebSocketMessageRequestPresentStrA(ScenarioEngineWebSocketMessageRequestPresent v)
{
	struct ScenarioEngineWebSocketMessageRequestPresentMapA *i = NULL;
	for (i = ScenarioEngineWebSocketMessageRequestPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineWebSocketMessageRequestPresent ScenarioEngineWebSocketMessageRequestPresentFromStrA(str_t str)
{
	struct ScenarioEngineWebSocketMessageRequestPresentMapA *i = NULL;
	for (i = ScenarioEngineWebSocketMessageRequestPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineWebSocketMessageRequestPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ScenarioEngineWebSocketMessageRequestPresentMapW
{
	wstr_t str;
	ScenarioEngineWebSocketMessageRequestPresent v;
} ScenarioEngineWebSocketMessageRequestPresentMapW[] =
{
	{ (wchar_t *)L"request", ScenarioEngineWebSocketMessageRequestPresent_request },
	{ (wchar_t *)L"describe", ScenarioEngineWebSocketMessageRequestPresent_describe },
	{ (wchar_t *)L"initialize", ScenarioEngineWebSocketMessageRequestPresent_initialize },
	{ (wchar_t *)L"uiConfigure", ScenarioEngineWebSocketMessageRequestPresent_uiConfigure },
	{ (wchar_t *)L"withData", ScenarioEngineWebSocketMessageRequestPresent_withData },
	{ (wchar_t *)L"setup", ScenarioEngineWebSocketMessageRequestPresent_setup },
	{ (wchar_t *)L"notify", ScenarioEngineWebSocketMessageRequestPresent_notify },
	{ (wchar_t *)L"validate", ScenarioEngineWebSocketMessageRequestPresent_validate },
	{ NULL, ScenarioEngineWebSocketMessageRequestPresent_max }
};

wstr_t ScenarioEngineWebSocketMessageRequestPresentStrW(ScenarioEngineWebSocketMessageRequestPresent v)
{
	struct ScenarioEngineWebSocketMessageRequestPresentMapW *i = NULL;
	for (i = ScenarioEngineWebSocketMessageRequestPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineWebSocketMessageRequestPresent ScenarioEngineWebSocketMessageRequestPresentFromStrW(wstr_t str)
{
	struct ScenarioEngineWebSocketMessageRequestPresentMapW *i = NULL;
	for (i = ScenarioEngineWebSocketMessageRequestPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineWebSocketMessageRequestPresent_max;
}
#endif // UNIX_SYSTEM

ScenarioEngineWebSocketMessageRequestPresent *ScenarioEngineWebSocketMessageRequestPresent_new(ScenarioEngineWebSocketMessageRequestPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineWebSocketMessageRequestPresent *__internal_ret = (ScenarioEngineWebSocketMessageRequestPresent *)Dz1Calloc(sizeof(ScenarioEngineWebSocketMessageRequestPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ScenarioEngineWebSocketMessageRequestPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageRequest
ScenarioEngineWebSocketMessageRequest *ScenarioEngineWebSocketMessageRequest_new(ScenarioEngineWebSocketMessageRequestPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineWebSocketMessageRequest *ret = (ScenarioEngineWebSocketMessageRequest *)Dz1Calloc(sizeof(ScenarioEngineWebSocketMessageRequest), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineWebSocketMessageRequest_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ScenarioEngineWebSocketMessageRequestPresent_request:
			// _U_cst_clone
			if (ptr != NULL) ret->x.request = (ScenarioEngineRequestMessageDefault *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageRequestPresent_describe:
			// _U_cst_clone
			if (ptr != NULL) ret->x.describe = (ScenarioEngineRequestMessageDescribe *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageRequestPresent_initialize:
			// _U_cst_clone
			if (ptr != NULL) ret->x.initialize = (ScenarioEngineRequestMessageInitialize *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageRequestPresent_uiConfigure:
			// _U_cst_clone
			if (ptr != NULL) ret->x.uiConfigure = (ScenarioEngineRequestMessageUIConfigure *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageRequestPresent_withData:
			// _U_cst_clone
			if (ptr != NULL) ret->x.withData = (ScenarioEngineRequestMessageWithData *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageRequestPresent_setup:
			// _U_cst_clone
			if (ptr != NULL) ret->x.setup = (ScenarioEngineRequestMessageSetup *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageRequestPresent_notify:
			// _U_cst_clone
			if (ptr != NULL) ret->x.notify = (ScenarioEngineRequestMessageNotify *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageRequestPresent_validate:
			// _U_cst_clone
			if (ptr != NULL) ret->x.validate = (ScenarioEngineRequestMessageValidate *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageRequestPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineWebSocketMessageRequest_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ScenarioEngineWebSocketMessageRequest_purge(ScenarioEngineWebSocketMessageRequest *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ScenarioEngineWebSocketMessageRequestPresent_request:
		ScenarioEngineRequestMessageDefault_del(p->x.request);
		break;
	case ScenarioEngineWebSocketMessageRequestPresent_describe:
		ScenarioEngineRequestMessageDescribe_del(p->x.describe);
		break;
	case ScenarioEngineWebSocketMessageRequestPresent_initialize:
		ScenarioEngineRequestMessageInitialize_del(p->x.initialize);
		break;
	case ScenarioEngineWebSocketMessageRequestPresent_uiConfigure:
		ScenarioEngineRequestMessageUIConfigure_del(p->x.uiConfigure);
		break;
	case ScenarioEngineWebSocketMessageRequestPresent_withData:
		ScenarioEngineRequestMessageWithData_del(p->x.withData);
		break;
	case ScenarioEngineWebSocketMessageRequestPresent_setup:
		ScenarioEngineRequestMessageSetup_del(p->x.setup);
		break;
	case ScenarioEngineWebSocketMessageRequestPresent_notify:
		ScenarioEngineRequestMessageNotify_del(p->x.notify);
		break;
	case ScenarioEngineWebSocketMessageRequestPresent_validate:
		ScenarioEngineRequestMessageValidate_del(p->x.validate);
		break;
	default:
		break;
	}
}

void ScenarioEngineWebSocketMessageRequest_del(ScenarioEngineWebSocketMessageRequest *p)
{
	if (!p) return;
	ScenarioEngineWebSocketMessageRequest_purge(p);
	Dz1Free(p);
}

// ScenarioEngineWebSocketMessageRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageResponsePresent
static struct ScenarioEngineWebSocketMessageResponsePresentMapA
{
	str_t str;
	ScenarioEngineWebSocketMessageResponsePresent v;
} ScenarioEngineWebSocketMessageResponsePresentMapA[] =
{
	{ (char *)"response", ScenarioEngineWebSocketMessageResponsePresent_response },
	{ (char *)"validate", ScenarioEngineWebSocketMessageResponsePresent_validate },
	{ NULL, ScenarioEngineWebSocketMessageResponsePresent_max }
};

str_t ScenarioEngineWebSocketMessageResponsePresentStrA(ScenarioEngineWebSocketMessageResponsePresent v)
{
	struct ScenarioEngineWebSocketMessageResponsePresentMapA *i = NULL;
	for (i = ScenarioEngineWebSocketMessageResponsePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineWebSocketMessageResponsePresent ScenarioEngineWebSocketMessageResponsePresentFromStrA(str_t str)
{
	struct ScenarioEngineWebSocketMessageResponsePresentMapA *i = NULL;
	for (i = ScenarioEngineWebSocketMessageResponsePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineWebSocketMessageResponsePresent_max;
}
#ifndef UNIX_SYSTEM
static struct ScenarioEngineWebSocketMessageResponsePresentMapW
{
	wstr_t str;
	ScenarioEngineWebSocketMessageResponsePresent v;
} ScenarioEngineWebSocketMessageResponsePresentMapW[] =
{
	{ (wchar_t *)L"response", ScenarioEngineWebSocketMessageResponsePresent_response },
	{ (wchar_t *)L"validate", ScenarioEngineWebSocketMessageResponsePresent_validate },
	{ NULL, ScenarioEngineWebSocketMessageResponsePresent_max }
};

wstr_t ScenarioEngineWebSocketMessageResponsePresentStrW(ScenarioEngineWebSocketMessageResponsePresent v)
{
	struct ScenarioEngineWebSocketMessageResponsePresentMapW *i = NULL;
	for (i = ScenarioEngineWebSocketMessageResponsePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineWebSocketMessageResponsePresent ScenarioEngineWebSocketMessageResponsePresentFromStrW(wstr_t str)
{
	struct ScenarioEngineWebSocketMessageResponsePresentMapW *i = NULL;
	for (i = ScenarioEngineWebSocketMessageResponsePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineWebSocketMessageResponsePresent_max;
}
#endif // UNIX_SYSTEM

ScenarioEngineWebSocketMessageResponsePresent *ScenarioEngineWebSocketMessageResponsePresent_new(ScenarioEngineWebSocketMessageResponsePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineWebSocketMessageResponsePresent *__internal_ret = (ScenarioEngineWebSocketMessageResponsePresent *)Dz1Calloc(sizeof(ScenarioEngineWebSocketMessageResponsePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ScenarioEngineWebSocketMessageResponsePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageResponse
ScenarioEngineWebSocketMessageResponse *ScenarioEngineWebSocketMessageResponse_new(ScenarioEngineWebSocketMessageResponsePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineWebSocketMessageResponse *ret = (ScenarioEngineWebSocketMessageResponse *)Dz1Calloc(sizeof(ScenarioEngineWebSocketMessageResponse), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineWebSocketMessageResponse_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ScenarioEngineWebSocketMessageResponsePresent_response:
			// _U_cst_clone
			if (ptr != NULL) ret->x.response = (ScenarioEngineResponseMessageDefault *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageResponsePresent_validate:
			// _U_cst_clone
			if (ptr != NULL) ret->x.validate = (ScenarioEngineResponseMessageValidate *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessageResponsePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineWebSocketMessageResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ScenarioEngineWebSocketMessageResponse_purge(ScenarioEngineWebSocketMessageResponse *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ScenarioEngineWebSocketMessageResponsePresent_response:
		ScenarioEngineResponseMessageDefault_del(p->x.response);
		break;
	case ScenarioEngineWebSocketMessageResponsePresent_validate:
		ScenarioEngineResponseMessageValidate_del(p->x.validate);
		break;
	default:
		break;
	}
}

void ScenarioEngineWebSocketMessageResponse_del(ScenarioEngineWebSocketMessageResponse *p)
{
	if (!p) return;
	ScenarioEngineWebSocketMessageResponse_purge(p);
	Dz1Free(p);
}

// ScenarioEngineWebSocketMessageResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessagePresent
static struct ScenarioEngineWebSocketMessagePresentMapA
{
	str_t str;
	ScenarioEngineWebSocketMessagePresent v;
} ScenarioEngineWebSocketMessagePresentMapA[] =
{
	{ (char *)"rsp", ScenarioEngineWebSocketMessagePresent_rsp },
	{ (char *)"req", ScenarioEngineWebSocketMessagePresent_req },
	{ NULL, ScenarioEngineWebSocketMessagePresent_max }
};

str_t ScenarioEngineWebSocketMessagePresentStrA(ScenarioEngineWebSocketMessagePresent v)
{
	struct ScenarioEngineWebSocketMessagePresentMapA *i = NULL;
	for (i = ScenarioEngineWebSocketMessagePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineWebSocketMessagePresent ScenarioEngineWebSocketMessagePresentFromStrA(str_t str)
{
	struct ScenarioEngineWebSocketMessagePresentMapA *i = NULL;
	for (i = ScenarioEngineWebSocketMessagePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineWebSocketMessagePresent_max;
}
#ifndef UNIX_SYSTEM
static struct ScenarioEngineWebSocketMessagePresentMapW
{
	wstr_t str;
	ScenarioEngineWebSocketMessagePresent v;
} ScenarioEngineWebSocketMessagePresentMapW[] =
{
	{ (wchar_t *)L"rsp", ScenarioEngineWebSocketMessagePresent_rsp },
	{ (wchar_t *)L"req", ScenarioEngineWebSocketMessagePresent_req },
	{ NULL, ScenarioEngineWebSocketMessagePresent_max }
};

wstr_t ScenarioEngineWebSocketMessagePresentStrW(ScenarioEngineWebSocketMessagePresent v)
{
	struct ScenarioEngineWebSocketMessagePresentMapW *i = NULL;
	for (i = ScenarioEngineWebSocketMessagePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ScenarioEngineWebSocketMessagePresent ScenarioEngineWebSocketMessagePresentFromStrW(wstr_t str)
{
	struct ScenarioEngineWebSocketMessagePresentMapW *i = NULL;
	for (i = ScenarioEngineWebSocketMessagePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ScenarioEngineWebSocketMessagePresent_max;
}
#endif // UNIX_SYSTEM

ScenarioEngineWebSocketMessagePresent *ScenarioEngineWebSocketMessagePresent_new(ScenarioEngineWebSocketMessagePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineWebSocketMessagePresent *__internal_ret = (ScenarioEngineWebSocketMessagePresent *)Dz1Calloc(sizeof(ScenarioEngineWebSocketMessagePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ScenarioEngineWebSocketMessagePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessage
ScenarioEngineWebSocketMessage *ScenarioEngineWebSocketMessage_new(ScenarioEngineWebSocketMessagePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineWebSocketMessage *ret = (ScenarioEngineWebSocketMessage *)Dz1Calloc(sizeof(ScenarioEngineWebSocketMessage), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineWebSocketMessage_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ScenarioEngineWebSocketMessagePresent_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rsp = (ScenarioEngineWebSocketMessageResponse *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessagePresent_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.req = (ScenarioEngineWebSocketMessageRequest *)ptr;
			ERR_CLEAR(errp);
			break;
		case ScenarioEngineWebSocketMessagePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineWebSocketMessage_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ScenarioEngineWebSocketMessage_purge(ScenarioEngineWebSocketMessage *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ScenarioEngineWebSocketMessagePresent_rsp:
		ScenarioEngineWebSocketMessageResponse_del(p->x.rsp);
		break;
	case ScenarioEngineWebSocketMessagePresent_req:
		ScenarioEngineWebSocketMessageRequest_del(p->x.req);
		break;
	default:
		break;
	}
}

void ScenarioEngineWebSocketMessage_del(ScenarioEngineWebSocketMessage *p)
{
	if (!p) return;
	ScenarioEngineWebSocketMessage_purge(p);
	Dz1Free(p);
}

// ScenarioEngineWebSocketMessage
////////////////////////////////////////////////////////////////////////////////

