////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v2TestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ProcessStatusCode
static struct Itsk00126v2ProcessStatusCodeMapA
{
	str_t str;
	Itsk00126v2ProcessStatusCode v;
} Itsk00126v2ProcessStatusCodeMapA[] =
{
	{ (char *)"OK", Itsk00126v2ProcessStatusCode_OK },
	{ (char *)"FAILURE", Itsk00126v2ProcessStatusCode_FAILURE },
	{ (char *)"AGENT_SYSTEM_ERROR", Itsk00126v2ProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (char *)"SERVER_DISCONNECTED", Itsk00126v2ProcessStatusCode_SERVER_DISCONNECTED },
	{ (char *)"TEST_CONFIGURATION_ERROR", Itsk00126v2ProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (char *)"CONNECTION_FAIL", Itsk00126v2ProcessStatusCode_CONNECTION_FAIL },
	{ (char *)"DISCONNECTED", Itsk00126v2ProcessStatusCode_DISCONNECTED },
	{ (char *)"TIMEOUT", Itsk00126v2ProcessStatusCode_TIMEOUT },
	{ (char *)"OUT_OF_RANGE", Itsk00126v2ProcessStatusCode_OUT_OF_RANGE },
	{ (char *)"INVALID_PROCESS", Itsk00126v2ProcessStatusCode_INVALID_PROCESS },
	{ (char *)"INVALID_IDENTIFIER", Itsk00126v2ProcessStatusCode_INVALID_IDENTIFIER },
	{ (char *)"SESSION_DUPLICATE", Itsk00126v2ProcessStatusCode_SESSION_DUPLICATE },
	{ (char *)"LOGIN_AUTH_ERROR", Itsk00126v2ProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (char *)"DECODE_FAIL", Itsk00126v2ProcessStatusCode_DECODE_FAIL },
	{ (char *)"INVALID_ENCODING_RULE", Itsk00126v2ProcessStatusCode_INVALID_ENCODING_RULE },
	{ (char *)"INVALID_OID", Itsk00126v2ProcessStatusCode_INVALID_OID },
	{ (char *)"INVALID_DSRC_MSG_ID", Itsk00126v2ProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (char *)"JSON_PARSE_ERROR", Itsk00126v2ProcessStatusCode_JSON_PARSE_ERROR },
	{ (char *)"PROTOBUF_DESERAILIZE_ERROR", Itsk00126v2ProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (char *)"INVALID_TOPIC", Itsk00126v2ProcessStatusCode_INVALID_TOPIC },
	{ (char *)"INVALID_REQUEST", Itsk00126v2ProcessStatusCode_INVALID_REQUEST },
	{ (char *)"UNKNOWN", Itsk00126v2ProcessStatusCode_UNKNOWN },
	{ NULL, Itsk00126v2ProcessStatusCode_max }
};

str_t Itsk00126v2ProcessStatusCodeStrA(Itsk00126v2ProcessStatusCode v)
{
	struct Itsk00126v2ProcessStatusCodeMapA *i = NULL;
	for (i = Itsk00126v2ProcessStatusCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ProcessStatusCode Itsk00126v2ProcessStatusCodeFromStrA(str_t str)
{
	struct Itsk00126v2ProcessStatusCodeMapA *i = NULL;
	for (i = Itsk00126v2ProcessStatusCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ProcessStatusCode_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v2ProcessStatusCodeMapW
{
	wstr_t str;
	Itsk00126v2ProcessStatusCode v;
} Itsk00126v2ProcessStatusCodeMapW[] =
{
	{ (wchar_t *)L"OK", Itsk00126v2ProcessStatusCode_OK },
	{ (wchar_t *)L"FAILURE", Itsk00126v2ProcessStatusCode_FAILURE },
	{ (wchar_t *)L"AGENT_SYSTEM_ERROR", Itsk00126v2ProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (wchar_t *)L"SERVER_DISCONNECTED", Itsk00126v2ProcessStatusCode_SERVER_DISCONNECTED },
	{ (wchar_t *)L"TEST_CONFIGURATION_ERROR", Itsk00126v2ProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (wchar_t *)L"CONNECTION_FAIL", Itsk00126v2ProcessStatusCode_CONNECTION_FAIL },
	{ (wchar_t *)L"DISCONNECTED", Itsk00126v2ProcessStatusCode_DISCONNECTED },
	{ (wchar_t *)L"TIMEOUT", Itsk00126v2ProcessStatusCode_TIMEOUT },
	{ (wchar_t *)L"OUT_OF_RANGE", Itsk00126v2ProcessStatusCode_OUT_OF_RANGE },
	{ (wchar_t *)L"INVALID_PROCESS", Itsk00126v2ProcessStatusCode_INVALID_PROCESS },
	{ (wchar_t *)L"INVALID_IDENTIFIER", Itsk00126v2ProcessStatusCode_INVALID_IDENTIFIER },
	{ (wchar_t *)L"SESSION_DUPLICATE", Itsk00126v2ProcessStatusCode_SESSION_DUPLICATE },
	{ (wchar_t *)L"LOGIN_AUTH_ERROR", Itsk00126v2ProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (wchar_t *)L"DECODE_FAIL", Itsk00126v2ProcessStatusCode_DECODE_FAIL },
	{ (wchar_t *)L"INVALID_ENCODING_RULE", Itsk00126v2ProcessStatusCode_INVALID_ENCODING_RULE },
	{ (wchar_t *)L"INVALID_OID", Itsk00126v2ProcessStatusCode_INVALID_OID },
	{ (wchar_t *)L"INVALID_DSRC_MSG_ID", Itsk00126v2ProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (wchar_t *)L"JSON_PARSE_ERROR", Itsk00126v2ProcessStatusCode_JSON_PARSE_ERROR },
	{ (wchar_t *)L"PROTOBUF_DESERAILIZE_ERROR", Itsk00126v2ProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (wchar_t *)L"INVALID_TOPIC", Itsk00126v2ProcessStatusCode_INVALID_TOPIC },
	{ (wchar_t *)L"INVALID_REQUEST", Itsk00126v2ProcessStatusCode_INVALID_REQUEST },
	{ (wchar_t *)L"UNKNOWN", Itsk00126v2ProcessStatusCode_UNKNOWN },
	{ NULL, Itsk00126v2ProcessStatusCode_max }
};

wstr_t Itsk00126v2ProcessStatusCodeStrW(Itsk00126v2ProcessStatusCode v)
{
	struct Itsk00126v2ProcessStatusCodeMapW *i = NULL;
	for (i = Itsk00126v2ProcessStatusCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ProcessStatusCode Itsk00126v2ProcessStatusCodeFromStrW(wstr_t str)
{
	struct Itsk00126v2ProcessStatusCodeMapW *i = NULL;
	for (i = Itsk00126v2ProcessStatusCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ProcessStatusCode_max;
}
#endif // UNIX_SYSTEM

Itsk00126v2ProcessStatusCode *Itsk00126v2ProcessStatusCode_new(Itsk00126v2ProcessStatusCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ProcessStatusCode *__internal_ret = (Itsk00126v2ProcessStatusCode *)Dz1Calloc(sizeof(Itsk00126v2ProcessStatusCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v2ProcessStatusCode_dump(Itsk00126v2ProcessStatusCode *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v2ProcessStatusCodeStr(*v));
}
// Itsk00126v2ProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyStateContext
Itsk00126v2NotifyStateContext *Itsk00126v2NotifyStateContext_new(Dz1Str testName, 
																 s64_t time, 
																 Dz1Str state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2NotifyStateContext *__internal_ret = (Itsk00126v2NotifyStateContext *)Dz1Calloc(sizeof(Itsk00126v2NotifyStateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyStateContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (state && (__internal_ret->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyStateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2NotifyStateContext_copy(Itsk00126v2NotifyStateContext *dst, Itsk00126v2NotifyStateContext *src, Dz1Error *err)
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

Itsk00126v2NotifyStateContext *Itsk00126v2NotifyStateContext_clone(Itsk00126v2NotifyStateContext *src, Dz1Error *err)
{
	Itsk00126v2NotifyStateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2NotifyStateContext *)Dz1Calloc(sizeof(Itsk00126v2NotifyStateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyStateContext_delAndSetNull, (void *)&dst);
		if (Itsk00126v2NotifyStateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyStateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2NotifyStateContext_purge(Itsk00126v2NotifyStateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->state);
}

void Itsk00126v2NotifyStateContext_del(Itsk00126v2NotifyStateContext *p)
{
	if (p == NULL) return;
	Itsk00126v2NotifyStateContext_purge(p);
	Dz1Free(p);
}

void Itsk00126v2NotifyStateContext_dump(Itsk00126v2NotifyStateContext *p, int tab)
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
// Itsk00126v2NotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyInfoContext
Itsk00126v2NotifyInfoContext *Itsk00126v2NotifyInfoContext_new(Dz1Str testName, 
															   s64_t time, 
															   Dz1Str sender, 
															   Dz1Str log, 
															   Dz1Binary *data, 
															   Dz1Str dataType, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2NotifyInfoContext *__internal_ret = (Itsk00126v2NotifyInfoContext *)Dz1Calloc(sizeof(Itsk00126v2NotifyInfoContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyInfoContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyInfoContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2NotifyInfoContext_copy(Itsk00126v2NotifyInfoContext *dst, Itsk00126v2NotifyInfoContext *src, Dz1Error *err)
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

Itsk00126v2NotifyInfoContext *Itsk00126v2NotifyInfoContext_clone(Itsk00126v2NotifyInfoContext *src, Dz1Error *err)
{
	Itsk00126v2NotifyInfoContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2NotifyInfoContext *)Dz1Calloc(sizeof(Itsk00126v2NotifyInfoContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyInfoContext_delAndSetNull, (void *)&dst);
		if (Itsk00126v2NotifyInfoContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyInfoContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2NotifyInfoContext_purge(Itsk00126v2NotifyInfoContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->sender);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->dataType);
}

void Itsk00126v2NotifyInfoContext_del(Itsk00126v2NotifyInfoContext *p)
{
	if (p == NULL) return;
	Itsk00126v2NotifyInfoContext_purge(p);
	Dz1Free(p);
}

void Itsk00126v2NotifyInfoContext_dump(Itsk00126v2NotifyInfoContext *p, int tab)
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
// Itsk00126v2NotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyErrorContext
Itsk00126v2NotifyErrorContext *Itsk00126v2NotifyErrorContext_new(Dz1Str testName, 
																 s64_t time, 
																 Itsk00126v2ProcessStatusCode code, 
																 Dz1Str desc, 
																 Dz1Str log, 
																 Dz1Binary *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2NotifyErrorContext *__internal_ret = (Itsk00126v2NotifyErrorContext *)Dz1Calloc(sizeof(Itsk00126v2NotifyErrorContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyErrorContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyErrorContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2NotifyErrorContext_copy(Itsk00126v2NotifyErrorContext *dst, Itsk00126v2NotifyErrorContext *src, Dz1Error *err)
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

Itsk00126v2NotifyErrorContext *Itsk00126v2NotifyErrorContext_clone(Itsk00126v2NotifyErrorContext *src, Dz1Error *err)
{
	Itsk00126v2NotifyErrorContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2NotifyErrorContext *)Dz1Calloc(sizeof(Itsk00126v2NotifyErrorContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyErrorContext_delAndSetNull, (void *)&dst);
		if (Itsk00126v2NotifyErrorContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyErrorContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2NotifyErrorContext_purge(Itsk00126v2NotifyErrorContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->desc);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
}

void Itsk00126v2NotifyErrorContext_del(Itsk00126v2NotifyErrorContext *p)
{
	if (p == NULL) return;
	Itsk00126v2NotifyErrorContext_purge(p);
	Dz1Free(p);
}

void Itsk00126v2NotifyErrorContext_dump(Itsk00126v2NotifyErrorContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), Itsk00126v2ProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("log = ")); Dz1Str_dump(p->log, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2NotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyStateArg
Itsk00126v2NotifyStateArg *Itsk00126v2NotifyStateArg_new(u32_t testIdx, 
														 Itsk00126v2NotifyStateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2NotifyStateArg *__internal_ret = (Itsk00126v2NotifyStateArg *)Dz1Calloc(sizeof(Itsk00126v2NotifyStateArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyStateArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyStateArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2NotifyStateArg_copy(Itsk00126v2NotifyStateArg *dst, Itsk00126v2NotifyStateArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Itsk00126v2NotifyStateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2NotifyStateArg *Itsk00126v2NotifyStateArg_clone(Itsk00126v2NotifyStateArg *src, Dz1Error *err)
{
	Itsk00126v2NotifyStateArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2NotifyStateArg *)Dz1Calloc(sizeof(Itsk00126v2NotifyStateArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyStateArg_delAndSetNull, (void *)&dst);
		if (Itsk00126v2NotifyStateArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyStateArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2NotifyStateArg_purge(Itsk00126v2NotifyStateArg *p)
{
	if (p == NULL) return;
	Itsk00126v2NotifyStateContext_del(p->context);
}

void Itsk00126v2NotifyStateArg_del(Itsk00126v2NotifyStateArg *p)
{
	if (p == NULL) return;
	Itsk00126v2NotifyStateArg_purge(p);
	Dz1Free(p);
}

void Itsk00126v2NotifyStateArg_dump(Itsk00126v2NotifyStateArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Itsk00126v2NotifyStateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2NotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyInfoArg
Itsk00126v2NotifyInfoArg *Itsk00126v2NotifyInfoArg_new(u32_t testIdx, 
													   Itsk00126v2NotifyInfoContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2NotifyInfoArg *__internal_ret = (Itsk00126v2NotifyInfoArg *)Dz1Calloc(sizeof(Itsk00126v2NotifyInfoArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyInfoArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyInfoArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2NotifyInfoArg_copy(Itsk00126v2NotifyInfoArg *dst, Itsk00126v2NotifyInfoArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Itsk00126v2NotifyInfoContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2NotifyInfoArg *Itsk00126v2NotifyInfoArg_clone(Itsk00126v2NotifyInfoArg *src, Dz1Error *err)
{
	Itsk00126v2NotifyInfoArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2NotifyInfoArg *)Dz1Calloc(sizeof(Itsk00126v2NotifyInfoArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyInfoArg_delAndSetNull, (void *)&dst);
		if (Itsk00126v2NotifyInfoArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyInfoArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2NotifyInfoArg_purge(Itsk00126v2NotifyInfoArg *p)
{
	if (p == NULL) return;
	Itsk00126v2NotifyInfoContext_del(p->context);
}

void Itsk00126v2NotifyInfoArg_del(Itsk00126v2NotifyInfoArg *p)
{
	if (p == NULL) return;
	Itsk00126v2NotifyInfoArg_purge(p);
	Dz1Free(p);
}

void Itsk00126v2NotifyInfoArg_dump(Itsk00126v2NotifyInfoArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Itsk00126v2NotifyInfoContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2NotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyErrorArg
Itsk00126v2NotifyErrorArg *Itsk00126v2NotifyErrorArg_new(u32_t testIdx, 
														 Itsk00126v2NotifyErrorContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2NotifyErrorArg *__internal_ret = (Itsk00126v2NotifyErrorArg *)Dz1Calloc(sizeof(Itsk00126v2NotifyErrorArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyErrorArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyErrorArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2NotifyErrorArg_copy(Itsk00126v2NotifyErrorArg *dst, Itsk00126v2NotifyErrorArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Itsk00126v2NotifyErrorContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2NotifyErrorArg *Itsk00126v2NotifyErrorArg_clone(Itsk00126v2NotifyErrorArg *src, Dz1Error *err)
{
	Itsk00126v2NotifyErrorArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2NotifyErrorArg *)Dz1Calloc(sizeof(Itsk00126v2NotifyErrorArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyErrorArg_delAndSetNull, (void *)&dst);
		if (Itsk00126v2NotifyErrorArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyErrorArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2NotifyErrorArg_purge(Itsk00126v2NotifyErrorArg *p)
{
	if (p == NULL) return;
	Itsk00126v2NotifyErrorContext_del(p->context);
}

void Itsk00126v2NotifyErrorArg_del(Itsk00126v2NotifyErrorArg *p)
{
	if (p == NULL) return;
	Itsk00126v2NotifyErrorArg_purge(p);
	Dz1Free(p);
}

void Itsk00126v2NotifyErrorArg_dump(Itsk00126v2NotifyErrorArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Itsk00126v2NotifyErrorContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2NotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyContextPresent
static struct Itsk00126v2NotifyContextPresentMapA
{
	str_t str;
	Itsk00126v2NotifyContextPresent v;
} Itsk00126v2NotifyContextPresentMapA[] =
{
	{ (char *)"state", Itsk00126v2NotifyContextPresent_state },
	{ (char *)"info", Itsk00126v2NotifyContextPresent_info },
	{ (char *)"error", Itsk00126v2NotifyContextPresent_error },
	{ NULL, Itsk00126v2NotifyContextPresent_max }
};

str_t Itsk00126v2NotifyContextPresentStrA(Itsk00126v2NotifyContextPresent v)
{
	struct Itsk00126v2NotifyContextPresentMapA *i = NULL;
	for (i = Itsk00126v2NotifyContextPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2NotifyContextPresent Itsk00126v2NotifyContextPresentFromStrA(str_t str)
{
	struct Itsk00126v2NotifyContextPresentMapA *i = NULL;
	for (i = Itsk00126v2NotifyContextPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2NotifyContextPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v2NotifyContextPresentMapW
{
	wstr_t str;
	Itsk00126v2NotifyContextPresent v;
} Itsk00126v2NotifyContextPresentMapW[] =
{
	{ (wchar_t *)L"state", Itsk00126v2NotifyContextPresent_state },
	{ (wchar_t *)L"info", Itsk00126v2NotifyContextPresent_info },
	{ (wchar_t *)L"error", Itsk00126v2NotifyContextPresent_error },
	{ NULL, Itsk00126v2NotifyContextPresent_max }
};

wstr_t Itsk00126v2NotifyContextPresentStrW(Itsk00126v2NotifyContextPresent v)
{
	struct Itsk00126v2NotifyContextPresentMapW *i = NULL;
	for (i = Itsk00126v2NotifyContextPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2NotifyContextPresent Itsk00126v2NotifyContextPresentFromStrW(wstr_t str)
{
	struct Itsk00126v2NotifyContextPresentMapW *i = NULL;
	for (i = Itsk00126v2NotifyContextPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2NotifyContextPresent_max;
}
#endif // UNIX_SYSTEM

Itsk00126v2NotifyContextPresent *Itsk00126v2NotifyContextPresent_new(Itsk00126v2NotifyContextPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2NotifyContextPresent *__internal_ret = (Itsk00126v2NotifyContextPresent *)Dz1Calloc(sizeof(Itsk00126v2NotifyContextPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v2NotifyContextPresent_dump(Itsk00126v2NotifyContextPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v2NotifyContextPresentStr(*v));
}
// Itsk00126v2NotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyContext
Itsk00126v2NotifyContext *Itsk00126v2NotifyContext_new(Itsk00126v2NotifyContextPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2NotifyContext *ret = (Itsk00126v2NotifyContext *)Dz1Calloc(sizeof(Itsk00126v2NotifyContext), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyContext_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Itsk00126v2NotifyContextPresent_state:
			// _U_cst_clone
			if (ptr != NULL) ret->x.state = (Itsk00126v2NotifyStateContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2NotifyContextPresent_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.info = (Itsk00126v2NotifyInfoContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2NotifyContextPresent_error:
			// _U_cst_clone
			if (ptr != NULL) ret->x.error = (Itsk00126v2NotifyErrorContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2NotifyContextPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Itsk00126v2NotifyContext_copy(Itsk00126v2NotifyContext *ret, Itsk00126v2NotifyContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Itsk00126v2NotifyContextPresent_state:
			// _U_cst_clone
			if (src->x.state && (ret->x.state = Itsk00126v2NotifyStateContext_clone(src->x.state, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v2NotifyContextPresent_info:
			// _U_cst_clone
			if (src->x.info && (ret->x.info = Itsk00126v2NotifyInfoContext_clone(src->x.info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v2NotifyContextPresent_error:
			// _U_cst_clone
			if (src->x.error && (ret->x.error = Itsk00126v2NotifyErrorContext_clone(src->x.error, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2NotifyContext *Itsk00126v2NotifyContext_clone(Itsk00126v2NotifyContext *src, Dz1Error *err)
{
	Itsk00126v2NotifyContext *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Itsk00126v2NotifyContext *)Dz1Calloc(sizeof(Itsk00126v2NotifyContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyContext_delAndSetNull, (void *)&ret);
		if (Itsk00126v2NotifyContext_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2NotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Itsk00126v2NotifyContext_purge(Itsk00126v2NotifyContext *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Itsk00126v2NotifyContextPresent_state:
		Itsk00126v2NotifyStateContext_del(p->x.state);
		break;
	case Itsk00126v2NotifyContextPresent_info:
		Itsk00126v2NotifyInfoContext_del(p->x.info);
		break;
	case Itsk00126v2NotifyContextPresent_error:
		Itsk00126v2NotifyErrorContext_del(p->x.error);
		break;
	default:
		break;
	}
}

void Itsk00126v2NotifyContext_del(Itsk00126v2NotifyContext *p)
{
	if (!p) return;
	Itsk00126v2NotifyContext_purge(p);
	Dz1Free(p);
}

void Itsk00126v2NotifyContext_dump(Itsk00126v2NotifyContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Itsk00126v2NotifyContextPresent_state:
		Dz1Thread_printf(Dz1T("state = ")); Itsk00126v2NotifyStateContext_dump(p->x.state, tab); 
		break;
	case Itsk00126v2NotifyContextPresent_info:
		Dz1Thread_printf(Dz1T("info = ")); Itsk00126v2NotifyInfoContext_dump(p->x.info, tab); 
		break;
	case Itsk00126v2NotifyContextPresent_error:
		Dz1Thread_printf(Dz1T("error = ")); Itsk00126v2NotifyErrorContext_dump(p->x.error, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Itsk00126v2NotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ValidateContext
Itsk00126v2ValidateContext *Itsk00126v2ValidateContext_new(Dz1Str testName, 
														   s64_t time, 
														   Dz1Binary *raw, 
														   Dz1Binary *data, 
														   Itsk00126v2ProcessStatusCode code, 
														   Dz1Str desc, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ValidateContext *__internal_ret = (Itsk00126v2ValidateContext *)Dz1Calloc(sizeof(Itsk00126v2ValidateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ValidateContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ValidateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2ValidateContext_copy(Itsk00126v2ValidateContext *dst, Itsk00126v2ValidateContext *src, Dz1Error *err)
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

Itsk00126v2ValidateContext *Itsk00126v2ValidateContext_clone(Itsk00126v2ValidateContext *src, Dz1Error *err)
{
	Itsk00126v2ValidateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2ValidateContext *)Dz1Calloc(sizeof(Itsk00126v2ValidateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ValidateContext_delAndSetNull, (void *)&dst);
		if (Itsk00126v2ValidateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ValidateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2ValidateContext_purge(Itsk00126v2ValidateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Binary_del(p->raw);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->desc);
}

void Itsk00126v2ValidateContext_del(Itsk00126v2ValidateContext *p)
{
	if (p == NULL) return;
	Itsk00126v2ValidateContext_purge(p);
	Dz1Free(p);
}

void Itsk00126v2ValidateContext_dump(Itsk00126v2ValidateContext *p, int tab)
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
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), Itsk00126v2ProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2ValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ValidateContextArg
Itsk00126v2ValidateContextArg *Itsk00126v2ValidateContextArg_new(u32_t testIdx, 
																 Itsk00126v2ValidateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ValidateContextArg *__internal_ret = (Itsk00126v2ValidateContextArg *)Dz1Calloc(sizeof(Itsk00126v2ValidateContextArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ValidateContextArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ValidateContextArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2ValidateContextArg_copy(Itsk00126v2ValidateContextArg *dst, Itsk00126v2ValidateContextArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Itsk00126v2ValidateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2ValidateContextArg *Itsk00126v2ValidateContextArg_clone(Itsk00126v2ValidateContextArg *src, Dz1Error *err)
{
	Itsk00126v2ValidateContextArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2ValidateContextArg *)Dz1Calloc(sizeof(Itsk00126v2ValidateContextArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ValidateContextArg_delAndSetNull, (void *)&dst);
		if (Itsk00126v2ValidateContextArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ValidateContextArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2ValidateContextArg_purge(Itsk00126v2ValidateContextArg *p)
{
	if (p == NULL) return;
	Itsk00126v2ValidateContext_del(p->context);
}

void Itsk00126v2ValidateContextArg_del(Itsk00126v2ValidateContextArg *p)
{
	if (p == NULL) return;
	Itsk00126v2ValidateContextArg_purge(p);
	Dz1Free(p);
}

void Itsk00126v2ValidateContextArg_dump(Itsk00126v2ValidateContextArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Itsk00126v2ValidateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2ValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfiguration_serverRole
Itsk00126v2TestConfiguration_serverRole *Itsk00126v2TestConfiguration_serverRole_new(s64_t local_port, 
																					 Dz1Str iot_im_device_id, 
																					 bool_t test_iot_im_device_sttus_info, 
																					 bool_t test_iot_device_list_response_info, 
																					 bool_t test_iot_device_sttus_info, 
																					 bool_t test_safety_signal_list_response_info, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2TestConfiguration_serverRole *__internal_ret = (Itsk00126v2TestConfiguration_serverRole *)Dz1Calloc(sizeof(Itsk00126v2TestConfiguration_serverRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2TestConfiguration_serverRole_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->local_port = local_port;
			__internal_ret->test_iot_im_device_sttus_info = test_iot_im_device_sttus_info;
			__internal_ret->test_iot_device_list_response_info = test_iot_device_list_response_info;
			__internal_ret->test_iot_device_sttus_info = test_iot_device_sttus_info;
			__internal_ret->test_safety_signal_list_response_info = test_safety_signal_list_response_info;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2TestConfiguration_serverRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2TestConfiguration_serverRole_copy(Itsk00126v2TestConfiguration_serverRole *dst, Itsk00126v2TestConfiguration_serverRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->test_iot_im_device_sttus_info = src->test_iot_im_device_sttus_info;
		dst->test_iot_device_list_response_info = src->test_iot_device_list_response_info;
		dst->test_iot_device_sttus_info = src->test_iot_device_sttus_info;
		dst->test_safety_signal_list_response_info = src->test_safety_signal_list_response_info;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2TestConfiguration_serverRole *Itsk00126v2TestConfiguration_serverRole_clone(Itsk00126v2TestConfiguration_serverRole *src, Dz1Error *err)
{
	Itsk00126v2TestConfiguration_serverRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2TestConfiguration_serverRole *)Dz1Calloc(sizeof(Itsk00126v2TestConfiguration_serverRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2TestConfiguration_serverRole_delAndSetNull, (void *)&dst);
		if (Itsk00126v2TestConfiguration_serverRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2TestConfiguration_serverRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2TestConfiguration_serverRole_purge(Itsk00126v2TestConfiguration_serverRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
}

void Itsk00126v2TestConfiguration_serverRole_del(Itsk00126v2TestConfiguration_serverRole *p)
{
	if (p == NULL) return;
	Itsk00126v2TestConfiguration_serverRole_purge(p);
	Dz1Free(p);
}

void Itsk00126v2TestConfiguration_serverRole_dump(Itsk00126v2TestConfiguration_serverRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1s64_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_iot_im_device_sttus_info = ")); Dz1Bool_dump(&p->test_iot_im_device_sttus_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_iot_device_list_response_info = ")); Dz1Bool_dump(&p->test_iot_device_list_response_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_iot_device_sttus_info = ")); Dz1Bool_dump(&p->test_iot_device_sttus_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_safety_signal_list_response_info = ")); Dz1Bool_dump(&p->test_safety_signal_list_response_info, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2TestConfiguration_serverRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfiguration_clientRole
Itsk00126v2TestConfiguration_clientRole *Itsk00126v2TestConfiguration_clientRole_new(Dz1Str peer_ip, 
																					 bool_t peer_port, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2TestConfiguration_clientRole *__internal_ret = (Itsk00126v2TestConfiguration_clientRole *)Dz1Calloc(sizeof(Itsk00126v2TestConfiguration_clientRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2TestConfiguration_clientRole_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2TestConfiguration_clientRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2TestConfiguration_clientRole_copy(Itsk00126v2TestConfiguration_clientRole *dst, Itsk00126v2TestConfiguration_clientRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2TestConfiguration_clientRole *Itsk00126v2TestConfiguration_clientRole_clone(Itsk00126v2TestConfiguration_clientRole *src, Dz1Error *err)
{
	Itsk00126v2TestConfiguration_clientRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2TestConfiguration_clientRole *)Dz1Calloc(sizeof(Itsk00126v2TestConfiguration_clientRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2TestConfiguration_clientRole_delAndSetNull, (void *)&dst);
		if (Itsk00126v2TestConfiguration_clientRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2TestConfiguration_clientRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2TestConfiguration_clientRole_purge(Itsk00126v2TestConfiguration_clientRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->peer_ip);
}

void Itsk00126v2TestConfiguration_clientRole_del(Itsk00126v2TestConfiguration_clientRole *p)
{
	if (p == NULL) return;
	Itsk00126v2TestConfiguration_clientRole_purge(p);
	Dz1Free(p);
}

void Itsk00126v2TestConfiguration_clientRole_dump(Itsk00126v2TestConfiguration_clientRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1Bool_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2TestConfiguration_clientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfigurationPresent
static struct Itsk00126v2TestConfigurationPresentMapA
{
	str_t str;
	Itsk00126v2TestConfigurationPresent v;
} Itsk00126v2TestConfigurationPresentMapA[] =
{
	{ (char *)"serverRole", Itsk00126v2TestConfigurationPresent_serverRole },
	{ (char *)"clientRole", Itsk00126v2TestConfigurationPresent_clientRole },
	{ NULL, Itsk00126v2TestConfigurationPresent_max }
};

str_t Itsk00126v2TestConfigurationPresentStrA(Itsk00126v2TestConfigurationPresent v)
{
	struct Itsk00126v2TestConfigurationPresentMapA *i = NULL;
	for (i = Itsk00126v2TestConfigurationPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2TestConfigurationPresent Itsk00126v2TestConfigurationPresentFromStrA(str_t str)
{
	struct Itsk00126v2TestConfigurationPresentMapA *i = NULL;
	for (i = Itsk00126v2TestConfigurationPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2TestConfigurationPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v2TestConfigurationPresentMapW
{
	wstr_t str;
	Itsk00126v2TestConfigurationPresent v;
} Itsk00126v2TestConfigurationPresentMapW[] =
{
	{ (wchar_t *)L"serverRole", Itsk00126v2TestConfigurationPresent_serverRole },
	{ (wchar_t *)L"clientRole", Itsk00126v2TestConfigurationPresent_clientRole },
	{ NULL, Itsk00126v2TestConfigurationPresent_max }
};

wstr_t Itsk00126v2TestConfigurationPresentStrW(Itsk00126v2TestConfigurationPresent v)
{
	struct Itsk00126v2TestConfigurationPresentMapW *i = NULL;
	for (i = Itsk00126v2TestConfigurationPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2TestConfigurationPresent Itsk00126v2TestConfigurationPresentFromStrW(wstr_t str)
{
	struct Itsk00126v2TestConfigurationPresentMapW *i = NULL;
	for (i = Itsk00126v2TestConfigurationPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2TestConfigurationPresent_max;
}
#endif // UNIX_SYSTEM

Itsk00126v2TestConfigurationPresent *Itsk00126v2TestConfigurationPresent_new(Itsk00126v2TestConfigurationPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2TestConfigurationPresent *__internal_ret = (Itsk00126v2TestConfigurationPresent *)Dz1Calloc(sizeof(Itsk00126v2TestConfigurationPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v2TestConfigurationPresent_dump(Itsk00126v2TestConfigurationPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v2TestConfigurationPresentStr(*v));
}
// Itsk00126v2TestConfigurationPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfiguration
Itsk00126v2TestConfiguration *Itsk00126v2TestConfiguration_new(Itsk00126v2TestConfigurationPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2TestConfiguration *ret = (Itsk00126v2TestConfiguration *)Dz1Calloc(sizeof(Itsk00126v2TestConfiguration), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2TestConfiguration_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Itsk00126v2TestConfigurationPresent_serverRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.serverRole = (Itsk00126v2TestConfiguration_serverRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2TestConfigurationPresent_clientRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clientRole = (Itsk00126v2TestConfiguration_clientRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2TestConfigurationPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2TestConfiguration_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Itsk00126v2TestConfiguration_copy(Itsk00126v2TestConfiguration *ret, Itsk00126v2TestConfiguration *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Itsk00126v2TestConfigurationPresent_serverRole:
			// _U_cst_clone
			if (src->x.serverRole && (ret->x.serverRole = Itsk00126v2TestConfiguration_serverRole_clone(src->x.serverRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v2TestConfigurationPresent_clientRole:
			// _U_cst_clone
			if (src->x.clientRole && (ret->x.clientRole = Itsk00126v2TestConfiguration_clientRole_clone(src->x.clientRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2TestConfiguration *Itsk00126v2TestConfiguration_clone(Itsk00126v2TestConfiguration *src, Dz1Error *err)
{
	Itsk00126v2TestConfiguration *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Itsk00126v2TestConfiguration *)Dz1Calloc(sizeof(Itsk00126v2TestConfiguration), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2TestConfiguration_delAndSetNull, (void *)&ret);
		if (Itsk00126v2TestConfiguration_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2TestConfiguration_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Itsk00126v2TestConfiguration_purge(Itsk00126v2TestConfiguration *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Itsk00126v2TestConfigurationPresent_serverRole:
		Itsk00126v2TestConfiguration_serverRole_del(p->x.serverRole);
		break;
	case Itsk00126v2TestConfigurationPresent_clientRole:
		Itsk00126v2TestConfiguration_clientRole_del(p->x.clientRole);
		break;
	default:
		break;
	}
}

void Itsk00126v2TestConfiguration_del(Itsk00126v2TestConfiguration *p)
{
	if (!p) return;
	Itsk00126v2TestConfiguration_purge(p);
	Dz1Free(p);
}

void Itsk00126v2TestConfiguration_dump(Itsk00126v2TestConfiguration *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Itsk00126v2TestConfigurationPresent_serverRole:
		Dz1Thread_printf(Dz1T("serverRole = ")); Itsk00126v2TestConfiguration_serverRole_dump(p->x.serverRole, tab); 
		break;
	case Itsk00126v2TestConfigurationPresent_clientRole:
		Dz1Thread_printf(Dz1T("clientRole = ")); Itsk00126v2TestConfiguration_clientRole_dump(p->x.clientRole, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Itsk00126v2TestConfiguration
////////////////////////////////////////////////////////////////////////////////

