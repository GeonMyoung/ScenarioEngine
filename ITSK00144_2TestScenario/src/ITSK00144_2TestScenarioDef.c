////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2TestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ProcessStatusCode
static struct ITSK00144_2ProcessStatusCodeMapA
{
	str_t str;
	ITSK00144_2ProcessStatusCode v;
} ITSK00144_2ProcessStatusCodeMapA[] =
{
	{ (char *)"OK", ITSK00144_2ProcessStatusCode_OK },
	{ (char *)"FAILURE", ITSK00144_2ProcessStatusCode_FAILURE },
	{ (char *)"AGENT_SYSTEM_ERROR", ITSK00144_2ProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (char *)"SERVER_DISCONNECTED", ITSK00144_2ProcessStatusCode_SERVER_DISCONNECTED },
	{ (char *)"TEST_CONFIGURATION_ERROR", ITSK00144_2ProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (char *)"CONNECTION_FAIL", ITSK00144_2ProcessStatusCode_CONNECTION_FAIL },
	{ (char *)"DISCONNECTED", ITSK00144_2ProcessStatusCode_DISCONNECTED },
	{ (char *)"TIMEOUT", ITSK00144_2ProcessStatusCode_TIMEOUT },
	{ (char *)"OUT_OF_RANGE", ITSK00144_2ProcessStatusCode_OUT_OF_RANGE },
	{ (char *)"INVALID_PROCESS", ITSK00144_2ProcessStatusCode_INVALID_PROCESS },
	{ (char *)"INVALID_IDENTIFIER", ITSK00144_2ProcessStatusCode_INVALID_IDENTIFIER },
	{ (char *)"SESSION_DUPLICATE", ITSK00144_2ProcessStatusCode_SESSION_DUPLICATE },
	{ (char *)"LOGIN_AUTH_ERROR", ITSK00144_2ProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (char *)"DECODE_FAIL", ITSK00144_2ProcessStatusCode_DECODE_FAIL },
	{ (char *)"INVALID_ENCODING_RULE", ITSK00144_2ProcessStatusCode_INVALID_ENCODING_RULE },
	{ (char *)"INVALID_OID", ITSK00144_2ProcessStatusCode_INVALID_OID },
	{ (char *)"INVALID_DSRC_MSG_ID", ITSK00144_2ProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (char *)"JSON_PARSE_ERROR", ITSK00144_2ProcessStatusCode_JSON_PARSE_ERROR },
	{ (char *)"PROTOBUF_DESERAILIZE_ERROR", ITSK00144_2ProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (char *)"INVALID_TOPIC", ITSK00144_2ProcessStatusCode_INVALID_TOPIC },
	{ (char *)"INVALID_REQUEST", ITSK00144_2ProcessStatusCode_INVALID_REQUEST },
	{ (char *)"UNKNOWN", ITSK00144_2ProcessStatusCode_UNKNOWN },
	{ NULL, ITSK00144_2ProcessStatusCode_max }
};

str_t ITSK00144_2ProcessStatusCodeStrA(ITSK00144_2ProcessStatusCode v)
{
	struct ITSK00144_2ProcessStatusCodeMapA *i = NULL;
	for (i = ITSK00144_2ProcessStatusCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ProcessStatusCode ITSK00144_2ProcessStatusCodeFromStrA(str_t str)
{
	struct ITSK00144_2ProcessStatusCodeMapA *i = NULL;
	for (i = ITSK00144_2ProcessStatusCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ProcessStatusCode_max;
}
#ifndef UNIX_SYSTEM
static struct ITSK00144_2ProcessStatusCodeMapW
{
	wstr_t str;
	ITSK00144_2ProcessStatusCode v;
} ITSK00144_2ProcessStatusCodeMapW[] =
{
	{ (wchar_t *)L"OK", ITSK00144_2ProcessStatusCode_OK },
	{ (wchar_t *)L"FAILURE", ITSK00144_2ProcessStatusCode_FAILURE },
	{ (wchar_t *)L"AGENT_SYSTEM_ERROR", ITSK00144_2ProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (wchar_t *)L"SERVER_DISCONNECTED", ITSK00144_2ProcessStatusCode_SERVER_DISCONNECTED },
	{ (wchar_t *)L"TEST_CONFIGURATION_ERROR", ITSK00144_2ProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (wchar_t *)L"CONNECTION_FAIL", ITSK00144_2ProcessStatusCode_CONNECTION_FAIL },
	{ (wchar_t *)L"DISCONNECTED", ITSK00144_2ProcessStatusCode_DISCONNECTED },
	{ (wchar_t *)L"TIMEOUT", ITSK00144_2ProcessStatusCode_TIMEOUT },
	{ (wchar_t *)L"OUT_OF_RANGE", ITSK00144_2ProcessStatusCode_OUT_OF_RANGE },
	{ (wchar_t *)L"INVALID_PROCESS", ITSK00144_2ProcessStatusCode_INVALID_PROCESS },
	{ (wchar_t *)L"INVALID_IDENTIFIER", ITSK00144_2ProcessStatusCode_INVALID_IDENTIFIER },
	{ (wchar_t *)L"SESSION_DUPLICATE", ITSK00144_2ProcessStatusCode_SESSION_DUPLICATE },
	{ (wchar_t *)L"LOGIN_AUTH_ERROR", ITSK00144_2ProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (wchar_t *)L"DECODE_FAIL", ITSK00144_2ProcessStatusCode_DECODE_FAIL },
	{ (wchar_t *)L"INVALID_ENCODING_RULE", ITSK00144_2ProcessStatusCode_INVALID_ENCODING_RULE },
	{ (wchar_t *)L"INVALID_OID", ITSK00144_2ProcessStatusCode_INVALID_OID },
	{ (wchar_t *)L"INVALID_DSRC_MSG_ID", ITSK00144_2ProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (wchar_t *)L"JSON_PARSE_ERROR", ITSK00144_2ProcessStatusCode_JSON_PARSE_ERROR },
	{ (wchar_t *)L"PROTOBUF_DESERAILIZE_ERROR", ITSK00144_2ProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (wchar_t *)L"INVALID_TOPIC", ITSK00144_2ProcessStatusCode_INVALID_TOPIC },
	{ (wchar_t *)L"INVALID_REQUEST", ITSK00144_2ProcessStatusCode_INVALID_REQUEST },
	{ (wchar_t *)L"UNKNOWN", ITSK00144_2ProcessStatusCode_UNKNOWN },
	{ NULL, ITSK00144_2ProcessStatusCode_max }
};

wstr_t ITSK00144_2ProcessStatusCodeStrW(ITSK00144_2ProcessStatusCode v)
{
	struct ITSK00144_2ProcessStatusCodeMapW *i = NULL;
	for (i = ITSK00144_2ProcessStatusCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ProcessStatusCode ITSK00144_2ProcessStatusCodeFromStrW(wstr_t str)
{
	struct ITSK00144_2ProcessStatusCodeMapW *i = NULL;
	for (i = ITSK00144_2ProcessStatusCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ProcessStatusCode_max;
}
#endif // UNIX_SYSTEM

ITSK00144_2ProcessStatusCode *ITSK00144_2ProcessStatusCode_new(ITSK00144_2ProcessStatusCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ProcessStatusCode *__internal_ret = (ITSK00144_2ProcessStatusCode *)Dz1Calloc(sizeof(ITSK00144_2ProcessStatusCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ITSK00144_2ProcessStatusCode_dump(ITSK00144_2ProcessStatusCode *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ITSK00144_2ProcessStatusCodeStr(*v));
}
// ITSK00144_2ProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyStateContext
ITSK00144_2NotifyStateContext *ITSK00144_2NotifyStateContext_new(Dz1Str testName, 
																 s64_t time, 
																 Dz1Str state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2NotifyStateContext *__internal_ret = (ITSK00144_2NotifyStateContext *)Dz1Calloc(sizeof(ITSK00144_2NotifyStateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyStateContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (state && (__internal_ret->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyStateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2NotifyStateContext_copy(ITSK00144_2NotifyStateContext *dst, ITSK00144_2NotifyStateContext *src, Dz1Error *err)
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

ITSK00144_2NotifyStateContext *ITSK00144_2NotifyStateContext_clone(ITSK00144_2NotifyStateContext *src, Dz1Error *err)
{
	ITSK00144_2NotifyStateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2NotifyStateContext *)Dz1Calloc(sizeof(ITSK00144_2NotifyStateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyStateContext_delAndSetNull, (void *)&dst);
		if (ITSK00144_2NotifyStateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyStateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2NotifyStateContext_purge(ITSK00144_2NotifyStateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->state);
}

void ITSK00144_2NotifyStateContext_del(ITSK00144_2NotifyStateContext *p)
{
	if (p == NULL) return;
	ITSK00144_2NotifyStateContext_purge(p);
	Dz1Free(p);
}

void ITSK00144_2NotifyStateContext_dump(ITSK00144_2NotifyStateContext *p, int tab)
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
// ITSK00144_2NotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyInfoContext
ITSK00144_2NotifyInfoContext *ITSK00144_2NotifyInfoContext_new(Dz1Str testName, 
															   s64_t time, 
															   Dz1Str sender, 
															   Dz1Str log, 
															   Dz1Binary *data, 
															   Dz1Str dataType, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2NotifyInfoContext *__internal_ret = (ITSK00144_2NotifyInfoContext *)Dz1Calloc(sizeof(ITSK00144_2NotifyInfoContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyInfoContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyInfoContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2NotifyInfoContext_copy(ITSK00144_2NotifyInfoContext *dst, ITSK00144_2NotifyInfoContext *src, Dz1Error *err)
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

ITSK00144_2NotifyInfoContext *ITSK00144_2NotifyInfoContext_clone(ITSK00144_2NotifyInfoContext *src, Dz1Error *err)
{
	ITSK00144_2NotifyInfoContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2NotifyInfoContext *)Dz1Calloc(sizeof(ITSK00144_2NotifyInfoContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyInfoContext_delAndSetNull, (void *)&dst);
		if (ITSK00144_2NotifyInfoContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyInfoContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2NotifyInfoContext_purge(ITSK00144_2NotifyInfoContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->sender);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->dataType);
}

void ITSK00144_2NotifyInfoContext_del(ITSK00144_2NotifyInfoContext *p)
{
	if (p == NULL) return;
	ITSK00144_2NotifyInfoContext_purge(p);
	Dz1Free(p);
}

void ITSK00144_2NotifyInfoContext_dump(ITSK00144_2NotifyInfoContext *p, int tab)
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
// ITSK00144_2NotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyErrorContext
ITSK00144_2NotifyErrorContext *ITSK00144_2NotifyErrorContext_new(Dz1Str testName, 
																 s64_t time, 
																 ITSK00144_2ProcessStatusCode code, 
																 Dz1Str desc, 
																 Dz1Str log, 
																 Dz1Binary *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2NotifyErrorContext *__internal_ret = (ITSK00144_2NotifyErrorContext *)Dz1Calloc(sizeof(ITSK00144_2NotifyErrorContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyErrorContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyErrorContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2NotifyErrorContext_copy(ITSK00144_2NotifyErrorContext *dst, ITSK00144_2NotifyErrorContext *src, Dz1Error *err)
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

ITSK00144_2NotifyErrorContext *ITSK00144_2NotifyErrorContext_clone(ITSK00144_2NotifyErrorContext *src, Dz1Error *err)
{
	ITSK00144_2NotifyErrorContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2NotifyErrorContext *)Dz1Calloc(sizeof(ITSK00144_2NotifyErrorContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyErrorContext_delAndSetNull, (void *)&dst);
		if (ITSK00144_2NotifyErrorContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyErrorContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2NotifyErrorContext_purge(ITSK00144_2NotifyErrorContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->desc);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
}

void ITSK00144_2NotifyErrorContext_del(ITSK00144_2NotifyErrorContext *p)
{
	if (p == NULL) return;
	ITSK00144_2NotifyErrorContext_purge(p);
	Dz1Free(p);
}

void ITSK00144_2NotifyErrorContext_dump(ITSK00144_2NotifyErrorContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), ITSK00144_2ProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("log = ")); Dz1Str_dump(p->log, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2NotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyStateArg
ITSK00144_2NotifyStateArg *ITSK00144_2NotifyStateArg_new(u32_t testIdx, 
														 ITSK00144_2NotifyStateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2NotifyStateArg *__internal_ret = (ITSK00144_2NotifyStateArg *)Dz1Calloc(sizeof(ITSK00144_2NotifyStateArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyStateArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyStateArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2NotifyStateArg_copy(ITSK00144_2NotifyStateArg *dst, ITSK00144_2NotifyStateArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = ITSK00144_2NotifyStateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2NotifyStateArg *ITSK00144_2NotifyStateArg_clone(ITSK00144_2NotifyStateArg *src, Dz1Error *err)
{
	ITSK00144_2NotifyStateArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2NotifyStateArg *)Dz1Calloc(sizeof(ITSK00144_2NotifyStateArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyStateArg_delAndSetNull, (void *)&dst);
		if (ITSK00144_2NotifyStateArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyStateArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2NotifyStateArg_purge(ITSK00144_2NotifyStateArg *p)
{
	if (p == NULL) return;
	ITSK00144_2NotifyStateContext_del(p->context);
}

void ITSK00144_2NotifyStateArg_del(ITSK00144_2NotifyStateArg *p)
{
	if (p == NULL) return;
	ITSK00144_2NotifyStateArg_purge(p);
	Dz1Free(p);
}

void ITSK00144_2NotifyStateArg_dump(ITSK00144_2NotifyStateArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); ITSK00144_2NotifyStateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2NotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyInfoArg
ITSK00144_2NotifyInfoArg *ITSK00144_2NotifyInfoArg_new(u32_t testIdx, 
													   ITSK00144_2NotifyInfoContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2NotifyInfoArg *__internal_ret = (ITSK00144_2NotifyInfoArg *)Dz1Calloc(sizeof(ITSK00144_2NotifyInfoArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyInfoArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyInfoArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2NotifyInfoArg_copy(ITSK00144_2NotifyInfoArg *dst, ITSK00144_2NotifyInfoArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = ITSK00144_2NotifyInfoContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2NotifyInfoArg *ITSK00144_2NotifyInfoArg_clone(ITSK00144_2NotifyInfoArg *src, Dz1Error *err)
{
	ITSK00144_2NotifyInfoArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2NotifyInfoArg *)Dz1Calloc(sizeof(ITSK00144_2NotifyInfoArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyInfoArg_delAndSetNull, (void *)&dst);
		if (ITSK00144_2NotifyInfoArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyInfoArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2NotifyInfoArg_purge(ITSK00144_2NotifyInfoArg *p)
{
	if (p == NULL) return;
	ITSK00144_2NotifyInfoContext_del(p->context);
}

void ITSK00144_2NotifyInfoArg_del(ITSK00144_2NotifyInfoArg *p)
{
	if (p == NULL) return;
	ITSK00144_2NotifyInfoArg_purge(p);
	Dz1Free(p);
}

void ITSK00144_2NotifyInfoArg_dump(ITSK00144_2NotifyInfoArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); ITSK00144_2NotifyInfoContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2NotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyErrorArg
ITSK00144_2NotifyErrorArg *ITSK00144_2NotifyErrorArg_new(u32_t testIdx, 
														 ITSK00144_2NotifyErrorContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2NotifyErrorArg *__internal_ret = (ITSK00144_2NotifyErrorArg *)Dz1Calloc(sizeof(ITSK00144_2NotifyErrorArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyErrorArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyErrorArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2NotifyErrorArg_copy(ITSK00144_2NotifyErrorArg *dst, ITSK00144_2NotifyErrorArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = ITSK00144_2NotifyErrorContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2NotifyErrorArg *ITSK00144_2NotifyErrorArg_clone(ITSK00144_2NotifyErrorArg *src, Dz1Error *err)
{
	ITSK00144_2NotifyErrorArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2NotifyErrorArg *)Dz1Calloc(sizeof(ITSK00144_2NotifyErrorArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyErrorArg_delAndSetNull, (void *)&dst);
		if (ITSK00144_2NotifyErrorArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyErrorArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2NotifyErrorArg_purge(ITSK00144_2NotifyErrorArg *p)
{
	if (p == NULL) return;
	ITSK00144_2NotifyErrorContext_del(p->context);
}

void ITSK00144_2NotifyErrorArg_del(ITSK00144_2NotifyErrorArg *p)
{
	if (p == NULL) return;
	ITSK00144_2NotifyErrorArg_purge(p);
	Dz1Free(p);
}

void ITSK00144_2NotifyErrorArg_dump(ITSK00144_2NotifyErrorArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); ITSK00144_2NotifyErrorContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2NotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyContextPresent
static struct ITSK00144_2NotifyContextPresentMapA
{
	str_t str;
	ITSK00144_2NotifyContextPresent v;
} ITSK00144_2NotifyContextPresentMapA[] =
{
	{ (char *)"state", ITSK00144_2NotifyContextPresent_state },
	{ (char *)"info", ITSK00144_2NotifyContextPresent_info },
	{ (char *)"error", ITSK00144_2NotifyContextPresent_error },
	{ NULL, ITSK00144_2NotifyContextPresent_max }
};

str_t ITSK00144_2NotifyContextPresentStrA(ITSK00144_2NotifyContextPresent v)
{
	struct ITSK00144_2NotifyContextPresentMapA *i = NULL;
	for (i = ITSK00144_2NotifyContextPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2NotifyContextPresent ITSK00144_2NotifyContextPresentFromStrA(str_t str)
{
	struct ITSK00144_2NotifyContextPresentMapA *i = NULL;
	for (i = ITSK00144_2NotifyContextPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2NotifyContextPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ITSK00144_2NotifyContextPresentMapW
{
	wstr_t str;
	ITSK00144_2NotifyContextPresent v;
} ITSK00144_2NotifyContextPresentMapW[] =
{
	{ (wchar_t *)L"state", ITSK00144_2NotifyContextPresent_state },
	{ (wchar_t *)L"info", ITSK00144_2NotifyContextPresent_info },
	{ (wchar_t *)L"error", ITSK00144_2NotifyContextPresent_error },
	{ NULL, ITSK00144_2NotifyContextPresent_max }
};

wstr_t ITSK00144_2NotifyContextPresentStrW(ITSK00144_2NotifyContextPresent v)
{
	struct ITSK00144_2NotifyContextPresentMapW *i = NULL;
	for (i = ITSK00144_2NotifyContextPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2NotifyContextPresent ITSK00144_2NotifyContextPresentFromStrW(wstr_t str)
{
	struct ITSK00144_2NotifyContextPresentMapW *i = NULL;
	for (i = ITSK00144_2NotifyContextPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2NotifyContextPresent_max;
}
#endif // UNIX_SYSTEM

ITSK00144_2NotifyContextPresent *ITSK00144_2NotifyContextPresent_new(ITSK00144_2NotifyContextPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2NotifyContextPresent *__internal_ret = (ITSK00144_2NotifyContextPresent *)Dz1Calloc(sizeof(ITSK00144_2NotifyContextPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ITSK00144_2NotifyContextPresent_dump(ITSK00144_2NotifyContextPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ITSK00144_2NotifyContextPresentStr(*v));
}
// ITSK00144_2NotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyContext
ITSK00144_2NotifyContext *ITSK00144_2NotifyContext_new(ITSK00144_2NotifyContextPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2NotifyContext *ret = (ITSK00144_2NotifyContext *)Dz1Calloc(sizeof(ITSK00144_2NotifyContext), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyContext_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ITSK00144_2NotifyContextPresent_state:
			// _U_cst_clone
			if (ptr != NULL) ret->x.state = (ITSK00144_2NotifyStateContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2NotifyContextPresent_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.info = (ITSK00144_2NotifyInfoContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2NotifyContextPresent_error:
			// _U_cst_clone
			if (ptr != NULL) ret->x.error = (ITSK00144_2NotifyErrorContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2NotifyContextPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t ITSK00144_2NotifyContext_copy(ITSK00144_2NotifyContext *ret, ITSK00144_2NotifyContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case ITSK00144_2NotifyContextPresent_state:
			// _U_cst_clone
			if (src->x.state && (ret->x.state = ITSK00144_2NotifyStateContext_clone(src->x.state, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2NotifyContextPresent_info:
			// _U_cst_clone
			if (src->x.info && (ret->x.info = ITSK00144_2NotifyInfoContext_clone(src->x.info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2NotifyContextPresent_error:
			// _U_cst_clone
			if (src->x.error && (ret->x.error = ITSK00144_2NotifyErrorContext_clone(src->x.error, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2NotifyContext *ITSK00144_2NotifyContext_clone(ITSK00144_2NotifyContext *src, Dz1Error *err)
{
	ITSK00144_2NotifyContext *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (ITSK00144_2NotifyContext *)Dz1Calloc(sizeof(ITSK00144_2NotifyContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2NotifyContext_delAndSetNull, (void *)&ret);
		if (ITSK00144_2NotifyContext_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2NotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ITSK00144_2NotifyContext_purge(ITSK00144_2NotifyContext *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ITSK00144_2NotifyContextPresent_state:
		ITSK00144_2NotifyStateContext_del(p->x.state);
		break;
	case ITSK00144_2NotifyContextPresent_info:
		ITSK00144_2NotifyInfoContext_del(p->x.info);
		break;
	case ITSK00144_2NotifyContextPresent_error:
		ITSK00144_2NotifyErrorContext_del(p->x.error);
		break;
	default:
		break;
	}
}

void ITSK00144_2NotifyContext_del(ITSK00144_2NotifyContext *p)
{
	if (!p) return;
	ITSK00144_2NotifyContext_purge(p);
	Dz1Free(p);
}

void ITSK00144_2NotifyContext_dump(ITSK00144_2NotifyContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ITSK00144_2NotifyContextPresent_state:
		Dz1Thread_printf(Dz1T("state = ")); ITSK00144_2NotifyStateContext_dump(p->x.state, tab); 
		break;
	case ITSK00144_2NotifyContextPresent_info:
		Dz1Thread_printf(Dz1T("info = ")); ITSK00144_2NotifyInfoContext_dump(p->x.info, tab); 
		break;
	case ITSK00144_2NotifyContextPresent_error:
		Dz1Thread_printf(Dz1T("error = ")); ITSK00144_2NotifyErrorContext_dump(p->x.error, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// ITSK00144_2NotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ValidateContext
ITSK00144_2ValidateContext *ITSK00144_2ValidateContext_new(Dz1Str testName, 
														   s64_t time, 
														   Dz1Binary *raw, 
														   Dz1Binary *data, 
														   ITSK00144_2ProcessStatusCode code, 
														   Dz1Str desc, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ValidateContext *__internal_ret = (ITSK00144_2ValidateContext *)Dz1Calloc(sizeof(ITSK00144_2ValidateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ValidateContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ValidateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2ValidateContext_copy(ITSK00144_2ValidateContext *dst, ITSK00144_2ValidateContext *src, Dz1Error *err)
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

ITSK00144_2ValidateContext *ITSK00144_2ValidateContext_clone(ITSK00144_2ValidateContext *src, Dz1Error *err)
{
	ITSK00144_2ValidateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2ValidateContext *)Dz1Calloc(sizeof(ITSK00144_2ValidateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ValidateContext_delAndSetNull, (void *)&dst);
		if (ITSK00144_2ValidateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ValidateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2ValidateContext_purge(ITSK00144_2ValidateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Binary_del(p->raw);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->desc);
}

void ITSK00144_2ValidateContext_del(ITSK00144_2ValidateContext *p)
{
	if (p == NULL) return;
	ITSK00144_2ValidateContext_purge(p);
	Dz1Free(p);
}

void ITSK00144_2ValidateContext_dump(ITSK00144_2ValidateContext *p, int tab)
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
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), ITSK00144_2ProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2ValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ValidateContextArg
ITSK00144_2ValidateContextArg *ITSK00144_2ValidateContextArg_new(u32_t testIdx, 
																 ITSK00144_2ValidateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ValidateContextArg *__internal_ret = (ITSK00144_2ValidateContextArg *)Dz1Calloc(sizeof(ITSK00144_2ValidateContextArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ValidateContextArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ValidateContextArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2ValidateContextArg_copy(ITSK00144_2ValidateContextArg *dst, ITSK00144_2ValidateContextArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = ITSK00144_2ValidateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2ValidateContextArg *ITSK00144_2ValidateContextArg_clone(ITSK00144_2ValidateContextArg *src, Dz1Error *err)
{
	ITSK00144_2ValidateContextArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2ValidateContextArg *)Dz1Calloc(sizeof(ITSK00144_2ValidateContextArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ValidateContextArg_delAndSetNull, (void *)&dst);
		if (ITSK00144_2ValidateContextArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ValidateContextArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2ValidateContextArg_purge(ITSK00144_2ValidateContextArg *p)
{
	if (p == NULL) return;
	ITSK00144_2ValidateContext_del(p->context);
}

void ITSK00144_2ValidateContextArg_del(ITSK00144_2ValidateContextArg *p)
{
	if (p == NULL) return;
	ITSK00144_2ValidateContextArg_purge(p);
	Dz1Free(p);
}

void ITSK00144_2ValidateContextArg_dump(ITSK00144_2ValidateContextArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); ITSK00144_2ValidateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2ValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfiguration_ServerRole
ITSK00144_2TestConfiguration_ServerRole *ITSK00144_2TestConfiguration_ServerRole_new(u64_t local_port, 
																					 u32_t serial_no, 
																					 bool_t test_rsp_link_unit_status, 
																					 bool_t test_rsp_status, 
																					 bool_t test_rsp_list, 
																					 bool_t test_rsp_update_list, 
																					 bool_t test_rsp_reset, 
																					 bool_t test_session_maintain, 
																					 s64_t hb_duration, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2TestConfiguration_ServerRole *__internal_ret = (ITSK00144_2TestConfiguration_ServerRole *)Dz1Calloc(sizeof(ITSK00144_2TestConfiguration_ServerRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2TestConfiguration_ServerRole_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->serial_no = serial_no;
		__internal_ret->test_rsp_link_unit_status = test_rsp_link_unit_status;
		__internal_ret->test_rsp_status = test_rsp_status;
		__internal_ret->test_rsp_list = test_rsp_list;
		__internal_ret->test_rsp_update_list = test_rsp_update_list;
		__internal_ret->test_rsp_reset = test_rsp_reset;
		__internal_ret->test_session_maintain = test_session_maintain;
		__internal_ret->hb_duration = hb_duration;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2TestConfiguration_ServerRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2TestConfiguration_ServerRole_copy(ITSK00144_2TestConfiguration_ServerRole *dst, ITSK00144_2TestConfiguration_ServerRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->local_port = src->local_port;
		dst->serial_no = src->serial_no;
		dst->test_rsp_link_unit_status = src->test_rsp_link_unit_status;
		dst->test_rsp_status = src->test_rsp_status;
		dst->test_rsp_list = src->test_rsp_list;
		dst->test_rsp_update_list = src->test_rsp_update_list;
		dst->test_rsp_reset = src->test_rsp_reset;
		dst->test_session_maintain = src->test_session_maintain;
		dst->hb_duration = src->hb_duration;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2TestConfiguration_ServerRole *ITSK00144_2TestConfiguration_ServerRole_clone(ITSK00144_2TestConfiguration_ServerRole *src, Dz1Error *err)
{
	ITSK00144_2TestConfiguration_ServerRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2TestConfiguration_ServerRole *)Dz1Calloc(sizeof(ITSK00144_2TestConfiguration_ServerRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2TestConfiguration_ServerRole_delAndSetNull, (void *)&dst);
		if (ITSK00144_2TestConfiguration_ServerRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2TestConfiguration_ServerRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2TestConfiguration_ServerRole_purge(ITSK00144_2TestConfiguration_ServerRole *p)
{
	if (p == NULL) return;
}

void ITSK00144_2TestConfiguration_ServerRole_del(ITSK00144_2TestConfiguration_ServerRole *p)
{
	if (p == NULL) return;
	ITSK00144_2TestConfiguration_ServerRole_purge(p);
	Dz1Free(p);
}

void ITSK00144_2TestConfiguration_ServerRole_dump(ITSK00144_2TestConfiguration_ServerRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1u64_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial_no = ")); Dz1u32_dump(&p->serial_no, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_link_unit_status = ")); Dz1Bool_dump(&p->test_rsp_link_unit_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_status = ")); Dz1Bool_dump(&p->test_rsp_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_list = ")); Dz1Bool_dump(&p->test_rsp_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_update_list = ")); Dz1Bool_dump(&p->test_rsp_update_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_reset = ")); Dz1Bool_dump(&p->test_rsp_reset, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hb_duration = ")); Dz1s64_dump(&p->hb_duration, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2TestConfiguration_ServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfiguration_LinkUnitRole
ITSK00144_2TestConfiguration_LinkUnitRole *ITSK00144_2TestConfiguration_LinkUnitRole_new(Dz1Str peer_ip, 
																						 u64_t peer_port, 
																						 u32_t serial_no, 
																						 bool_t test_req_link_unit_status, 
																						 bool_t test_req_status, 
																						 bool_t test_req_list, 
																						 bool_t test_req_update_list, 
																						 bool_t test_req_reset, 
																						 bool_t test_session_maintain, 
																						 s64_t hb_duration, 
																						 bool_t test_tim, 
																						 bool_t test_map, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2TestConfiguration_LinkUnitRole *__internal_ret = (ITSK00144_2TestConfiguration_LinkUnitRole *)Dz1Calloc(sizeof(ITSK00144_2TestConfiguration_LinkUnitRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2TestConfiguration_LinkUnitRole_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			__internal_ret->serial_no = serial_no;
			__internal_ret->test_req_link_unit_status = test_req_link_unit_status;
			__internal_ret->test_req_status = test_req_status;
			__internal_ret->test_req_list = test_req_list;
			__internal_ret->test_req_update_list = test_req_update_list;
			__internal_ret->test_req_reset = test_req_reset;
			__internal_ret->test_session_maintain = test_session_maintain;
			__internal_ret->hb_duration = hb_duration;
			__internal_ret->test_tim = test_tim;
			__internal_ret->test_map = test_map;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2TestConfiguration_LinkUnitRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2TestConfiguration_LinkUnitRole_copy(ITSK00144_2TestConfiguration_LinkUnitRole *dst, ITSK00144_2TestConfiguration_LinkUnitRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		dst->serial_no = src->serial_no;
		dst->test_req_link_unit_status = src->test_req_link_unit_status;
		dst->test_req_status = src->test_req_status;
		dst->test_req_list = src->test_req_list;
		dst->test_req_update_list = src->test_req_update_list;
		dst->test_req_reset = src->test_req_reset;
		dst->test_session_maintain = src->test_session_maintain;
		dst->hb_duration = src->hb_duration;
		dst->test_tim = src->test_tim;
		dst->test_map = src->test_map;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2TestConfiguration_LinkUnitRole *ITSK00144_2TestConfiguration_LinkUnitRole_clone(ITSK00144_2TestConfiguration_LinkUnitRole *src, Dz1Error *err)
{
	ITSK00144_2TestConfiguration_LinkUnitRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2TestConfiguration_LinkUnitRole *)Dz1Calloc(sizeof(ITSK00144_2TestConfiguration_LinkUnitRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2TestConfiguration_LinkUnitRole_delAndSetNull, (void *)&dst);
		if (ITSK00144_2TestConfiguration_LinkUnitRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2TestConfiguration_LinkUnitRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2TestConfiguration_LinkUnitRole_purge(ITSK00144_2TestConfiguration_LinkUnitRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->peer_ip);
}

void ITSK00144_2TestConfiguration_LinkUnitRole_del(ITSK00144_2TestConfiguration_LinkUnitRole *p)
{
	if (p == NULL) return;
	ITSK00144_2TestConfiguration_LinkUnitRole_purge(p);
	Dz1Free(p);
}

void ITSK00144_2TestConfiguration_LinkUnitRole_dump(ITSK00144_2TestConfiguration_LinkUnitRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1u64_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial_no = ")); Dz1u32_dump(&p->serial_no, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_link_unit_status = ")); Dz1Bool_dump(&p->test_req_link_unit_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_status = ")); Dz1Bool_dump(&p->test_req_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_list = ")); Dz1Bool_dump(&p->test_req_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_update_list = ")); Dz1Bool_dump(&p->test_req_update_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_reset = ")); Dz1Bool_dump(&p->test_req_reset, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hb_duration = ")); Dz1s64_dump(&p->hb_duration, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tim = ")); Dz1Bool_dump(&p->test_tim, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_map = ")); Dz1Bool_dump(&p->test_map, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2TestConfiguration_LinkUnitRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfigurationPresent
static struct ITSK00144_2TestConfigurationPresentMapA
{
	str_t str;
	ITSK00144_2TestConfigurationPresent v;
} ITSK00144_2TestConfigurationPresentMapA[] =
{
	{ (char *)"serverRole", ITSK00144_2TestConfigurationPresent_serverRole },
	{ (char *)"linkUnitRole", ITSK00144_2TestConfigurationPresent_linkUnitRole },
	{ NULL, ITSK00144_2TestConfigurationPresent_max }
};

str_t ITSK00144_2TestConfigurationPresentStrA(ITSK00144_2TestConfigurationPresent v)
{
	struct ITSK00144_2TestConfigurationPresentMapA *i = NULL;
	for (i = ITSK00144_2TestConfigurationPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2TestConfigurationPresent ITSK00144_2TestConfigurationPresentFromStrA(str_t str)
{
	struct ITSK00144_2TestConfigurationPresentMapA *i = NULL;
	for (i = ITSK00144_2TestConfigurationPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2TestConfigurationPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ITSK00144_2TestConfigurationPresentMapW
{
	wstr_t str;
	ITSK00144_2TestConfigurationPresent v;
} ITSK00144_2TestConfigurationPresentMapW[] =
{
	{ (wchar_t *)L"serverRole", ITSK00144_2TestConfigurationPresent_serverRole },
	{ (wchar_t *)L"linkUnitRole", ITSK00144_2TestConfigurationPresent_linkUnitRole },
	{ NULL, ITSK00144_2TestConfigurationPresent_max }
};

wstr_t ITSK00144_2TestConfigurationPresentStrW(ITSK00144_2TestConfigurationPresent v)
{
	struct ITSK00144_2TestConfigurationPresentMapW *i = NULL;
	for (i = ITSK00144_2TestConfigurationPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2TestConfigurationPresent ITSK00144_2TestConfigurationPresentFromStrW(wstr_t str)
{
	struct ITSK00144_2TestConfigurationPresentMapW *i = NULL;
	for (i = ITSK00144_2TestConfigurationPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2TestConfigurationPresent_max;
}
#endif // UNIX_SYSTEM

ITSK00144_2TestConfigurationPresent *ITSK00144_2TestConfigurationPresent_new(ITSK00144_2TestConfigurationPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2TestConfigurationPresent *__internal_ret = (ITSK00144_2TestConfigurationPresent *)Dz1Calloc(sizeof(ITSK00144_2TestConfigurationPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ITSK00144_2TestConfigurationPresent_dump(ITSK00144_2TestConfigurationPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ITSK00144_2TestConfigurationPresentStr(*v));
}
// ITSK00144_2TestConfigurationPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfiguration
ITSK00144_2TestConfiguration *ITSK00144_2TestConfiguration_new(ITSK00144_2TestConfigurationPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2TestConfiguration *ret = (ITSK00144_2TestConfiguration *)Dz1Calloc(sizeof(ITSK00144_2TestConfiguration), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2TestConfiguration_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ITSK00144_2TestConfigurationPresent_serverRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.serverRole = (ITSK00144_2TestConfiguration_ServerRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2TestConfigurationPresent_linkUnitRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.linkUnitRole = (ITSK00144_2TestConfiguration_LinkUnitRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2TestConfigurationPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2TestConfiguration_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t ITSK00144_2TestConfiguration_copy(ITSK00144_2TestConfiguration *ret, ITSK00144_2TestConfiguration *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case ITSK00144_2TestConfigurationPresent_serverRole:
			// _U_cst_clone
			if (src->x.serverRole && (ret->x.serverRole = ITSK00144_2TestConfiguration_ServerRole_clone(src->x.serverRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2TestConfigurationPresent_linkUnitRole:
			// _U_cst_clone
			if (src->x.linkUnitRole && (ret->x.linkUnitRole = ITSK00144_2TestConfiguration_LinkUnitRole_clone(src->x.linkUnitRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2TestConfiguration *ITSK00144_2TestConfiguration_clone(ITSK00144_2TestConfiguration *src, Dz1Error *err)
{
	ITSK00144_2TestConfiguration *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (ITSK00144_2TestConfiguration *)Dz1Calloc(sizeof(ITSK00144_2TestConfiguration), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2TestConfiguration_delAndSetNull, (void *)&ret);
		if (ITSK00144_2TestConfiguration_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2TestConfiguration_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ITSK00144_2TestConfiguration_purge(ITSK00144_2TestConfiguration *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ITSK00144_2TestConfigurationPresent_serverRole:
		ITSK00144_2TestConfiguration_ServerRole_del(p->x.serverRole);
		break;
	case ITSK00144_2TestConfigurationPresent_linkUnitRole:
		ITSK00144_2TestConfiguration_LinkUnitRole_del(p->x.linkUnitRole);
		break;
	default:
		break;
	}
}

void ITSK00144_2TestConfiguration_del(ITSK00144_2TestConfiguration *p)
{
	if (!p) return;
	ITSK00144_2TestConfiguration_purge(p);
	Dz1Free(p);
}

void ITSK00144_2TestConfiguration_dump(ITSK00144_2TestConfiguration *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ITSK00144_2TestConfigurationPresent_serverRole:
		Dz1Thread_printf(Dz1T("serverRole = ")); ITSK00144_2TestConfiguration_ServerRole_dump(p->x.serverRole, tab); 
		break;
	case ITSK00144_2TestConfigurationPresent_linkUnitRole:
		Dz1Thread_printf(Dz1T("linkUnitRole = ")); ITSK00144_2TestConfiguration_LinkUnitRole_dump(p->x.linkUnitRole, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// ITSK00144_2TestConfiguration
////////////////////////////////////////////////////////////////////////////////

