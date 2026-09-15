////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerProcessStatusCode
static struct TrafficSignalControllerProcessStatusCodeMapA
{
	str_t str;
	TrafficSignalControllerProcessStatusCode v;
} TrafficSignalControllerProcessStatusCodeMapA[] =
{
	{ (char *)"OK", TrafficSignalControllerProcessStatusCode_OK },
	{ (char *)"FAILURE", TrafficSignalControllerProcessStatusCode_FAILURE },
	{ (char *)"AGENT_SYSTEM_ERROR", TrafficSignalControllerProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (char *)"SERVER_DISCONNECTED", TrafficSignalControllerProcessStatusCode_SERVER_DISCONNECTED },
	{ (char *)"TEST_CONFIGURATION_ERROR", TrafficSignalControllerProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (char *)"CONNECTION_FAIL", TrafficSignalControllerProcessStatusCode_CONNECTION_FAIL },
	{ (char *)"DISCONNECTED", TrafficSignalControllerProcessStatusCode_DISCONNECTED },
	{ (char *)"TIMEOUT", TrafficSignalControllerProcessStatusCode_TIMEOUT },
	{ (char *)"OUT_OF_RANGE", TrafficSignalControllerProcessStatusCode_OUT_OF_RANGE },
	{ (char *)"INVALID_PROCESS", TrafficSignalControllerProcessStatusCode_INVALID_PROCESS },
	{ (char *)"INVALID_IDENTIFIER", TrafficSignalControllerProcessStatusCode_INVALID_IDENTIFIER },
	{ (char *)"SESSION_DUPLICATE", TrafficSignalControllerProcessStatusCode_SESSION_DUPLICATE },
	{ (char *)"LOGIN_AUTH_ERROR", TrafficSignalControllerProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (char *)"DECODE_FAIL", TrafficSignalControllerProcessStatusCode_DECODE_FAIL },
	{ (char *)"INVALID_ENCODING_RULE", TrafficSignalControllerProcessStatusCode_INVALID_ENCODING_RULE },
	{ (char *)"INVALID_OID", TrafficSignalControllerProcessStatusCode_INVALID_OID },
	{ (char *)"INVALID_DSRC_MSG_ID", TrafficSignalControllerProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (char *)"JSON_PARSE_ERROR", TrafficSignalControllerProcessStatusCode_JSON_PARSE_ERROR },
	{ (char *)"PROTOBUF_DESERAILIZE_ERROR", TrafficSignalControllerProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (char *)"INVALID_TOPIC", TrafficSignalControllerProcessStatusCode_INVALID_TOPIC },
	{ (char *)"INVALID_REQUEST", TrafficSignalControllerProcessStatusCode_INVALID_REQUEST },
	{ (char *)"UNKNOWN", TrafficSignalControllerProcessStatusCode_UNKNOWN },
	{ NULL, TrafficSignalControllerProcessStatusCode_max }
};

str_t TrafficSignalControllerProcessStatusCodeStrA(TrafficSignalControllerProcessStatusCode v)
{
	struct TrafficSignalControllerProcessStatusCodeMapA *i = NULL;
	for (i = TrafficSignalControllerProcessStatusCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerProcessStatusCode TrafficSignalControllerProcessStatusCodeFromStrA(str_t str)
{
	struct TrafficSignalControllerProcessStatusCodeMapA *i = NULL;
	for (i = TrafficSignalControllerProcessStatusCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerProcessStatusCode_max;
}
#ifndef UNIX_SYSTEM
static struct TrafficSignalControllerProcessStatusCodeMapW
{
	wstr_t str;
	TrafficSignalControllerProcessStatusCode v;
} TrafficSignalControllerProcessStatusCodeMapW[] =
{
	{ (wchar_t *)L"OK", TrafficSignalControllerProcessStatusCode_OK },
	{ (wchar_t *)L"FAILURE", TrafficSignalControllerProcessStatusCode_FAILURE },
	{ (wchar_t *)L"AGENT_SYSTEM_ERROR", TrafficSignalControllerProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (wchar_t *)L"SERVER_DISCONNECTED", TrafficSignalControllerProcessStatusCode_SERVER_DISCONNECTED },
	{ (wchar_t *)L"TEST_CONFIGURATION_ERROR", TrafficSignalControllerProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (wchar_t *)L"CONNECTION_FAIL", TrafficSignalControllerProcessStatusCode_CONNECTION_FAIL },
	{ (wchar_t *)L"DISCONNECTED", TrafficSignalControllerProcessStatusCode_DISCONNECTED },
	{ (wchar_t *)L"TIMEOUT", TrafficSignalControllerProcessStatusCode_TIMEOUT },
	{ (wchar_t *)L"OUT_OF_RANGE", TrafficSignalControllerProcessStatusCode_OUT_OF_RANGE },
	{ (wchar_t *)L"INVALID_PROCESS", TrafficSignalControllerProcessStatusCode_INVALID_PROCESS },
	{ (wchar_t *)L"INVALID_IDENTIFIER", TrafficSignalControllerProcessStatusCode_INVALID_IDENTIFIER },
	{ (wchar_t *)L"SESSION_DUPLICATE", TrafficSignalControllerProcessStatusCode_SESSION_DUPLICATE },
	{ (wchar_t *)L"LOGIN_AUTH_ERROR", TrafficSignalControllerProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (wchar_t *)L"DECODE_FAIL", TrafficSignalControllerProcessStatusCode_DECODE_FAIL },
	{ (wchar_t *)L"INVALID_ENCODING_RULE", TrafficSignalControllerProcessStatusCode_INVALID_ENCODING_RULE },
	{ (wchar_t *)L"INVALID_OID", TrafficSignalControllerProcessStatusCode_INVALID_OID },
	{ (wchar_t *)L"INVALID_DSRC_MSG_ID", TrafficSignalControllerProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (wchar_t *)L"JSON_PARSE_ERROR", TrafficSignalControllerProcessStatusCode_JSON_PARSE_ERROR },
	{ (wchar_t *)L"PROTOBUF_DESERAILIZE_ERROR", TrafficSignalControllerProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (wchar_t *)L"INVALID_TOPIC", TrafficSignalControllerProcessStatusCode_INVALID_TOPIC },
	{ (wchar_t *)L"INVALID_REQUEST", TrafficSignalControllerProcessStatusCode_INVALID_REQUEST },
	{ (wchar_t *)L"UNKNOWN", TrafficSignalControllerProcessStatusCode_UNKNOWN },
	{ NULL, TrafficSignalControllerProcessStatusCode_max }
};

wstr_t TrafficSignalControllerProcessStatusCodeStrW(TrafficSignalControllerProcessStatusCode v)
{
	struct TrafficSignalControllerProcessStatusCodeMapW *i = NULL;
	for (i = TrafficSignalControllerProcessStatusCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerProcessStatusCode TrafficSignalControllerProcessStatusCodeFromStrW(wstr_t str)
{
	struct TrafficSignalControllerProcessStatusCodeMapW *i = NULL;
	for (i = TrafficSignalControllerProcessStatusCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerProcessStatusCode_max;
}
#endif // UNIX_SYSTEM

TrafficSignalControllerProcessStatusCode *TrafficSignalControllerProcessStatusCode_new(TrafficSignalControllerProcessStatusCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerProcessStatusCode *__internal_ret = (TrafficSignalControllerProcessStatusCode *)Dz1Calloc(sizeof(TrafficSignalControllerProcessStatusCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void TrafficSignalControllerProcessStatusCode_dump(TrafficSignalControllerProcessStatusCode *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), TrafficSignalControllerProcessStatusCodeStr(*v));
}
// TrafficSignalControllerProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyStateContext
TrafficSignalControllerNotifyStateContext *TrafficSignalControllerNotifyStateContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 Dz1Str state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerNotifyStateContext *__internal_ret = (TrafficSignalControllerNotifyStateContext *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyStateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyStateContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (state && (__internal_ret->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyStateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerNotifyStateContext_copy(TrafficSignalControllerNotifyStateContext *dst, TrafficSignalControllerNotifyStateContext *src, Dz1Error *err)
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

TrafficSignalControllerNotifyStateContext *TrafficSignalControllerNotifyStateContext_clone(TrafficSignalControllerNotifyStateContext *src, Dz1Error *err)
{
	TrafficSignalControllerNotifyStateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerNotifyStateContext *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyStateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyStateContext_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerNotifyStateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyStateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerNotifyStateContext_purge(TrafficSignalControllerNotifyStateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->state);
}

void TrafficSignalControllerNotifyStateContext_del(TrafficSignalControllerNotifyStateContext *p)
{
	if (p == NULL) return;
	TrafficSignalControllerNotifyStateContext_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerNotifyStateContext_dump(TrafficSignalControllerNotifyStateContext *p, int tab)
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
// TrafficSignalControllerNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyInfoContext
TrafficSignalControllerNotifyInfoContext *TrafficSignalControllerNotifyInfoContext_new(Dz1Str testName, 
																					   s64_t time, 
																					   Dz1Str sender, 
																					   Dz1Str log, 
																					   Dz1Binary *data, 
																					   Dz1Str dataType, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerNotifyInfoContext *__internal_ret = (TrafficSignalControllerNotifyInfoContext *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyInfoContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyInfoContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyInfoContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerNotifyInfoContext_copy(TrafficSignalControllerNotifyInfoContext *dst, TrafficSignalControllerNotifyInfoContext *src, Dz1Error *err)
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

TrafficSignalControllerNotifyInfoContext *TrafficSignalControllerNotifyInfoContext_clone(TrafficSignalControllerNotifyInfoContext *src, Dz1Error *err)
{
	TrafficSignalControllerNotifyInfoContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerNotifyInfoContext *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyInfoContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyInfoContext_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerNotifyInfoContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyInfoContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerNotifyInfoContext_purge(TrafficSignalControllerNotifyInfoContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->sender);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->dataType);
}

void TrafficSignalControllerNotifyInfoContext_del(TrafficSignalControllerNotifyInfoContext *p)
{
	if (p == NULL) return;
	TrafficSignalControllerNotifyInfoContext_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerNotifyInfoContext_dump(TrafficSignalControllerNotifyInfoContext *p, int tab)
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
// TrafficSignalControllerNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyErrorContext
TrafficSignalControllerNotifyErrorContext *TrafficSignalControllerNotifyErrorContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 TrafficSignalControllerProcessStatusCode code, 
																						 Dz1Str desc, 
																						 Dz1Str log, 
																						 Dz1Binary *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerNotifyErrorContext *__internal_ret = (TrafficSignalControllerNotifyErrorContext *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyErrorContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyErrorContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyErrorContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerNotifyErrorContext_copy(TrafficSignalControllerNotifyErrorContext *dst, TrafficSignalControllerNotifyErrorContext *src, Dz1Error *err)
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

TrafficSignalControllerNotifyErrorContext *TrafficSignalControllerNotifyErrorContext_clone(TrafficSignalControllerNotifyErrorContext *src, Dz1Error *err)
{
	TrafficSignalControllerNotifyErrorContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerNotifyErrorContext *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyErrorContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyErrorContext_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerNotifyErrorContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyErrorContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerNotifyErrorContext_purge(TrafficSignalControllerNotifyErrorContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->desc);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
}

void TrafficSignalControllerNotifyErrorContext_del(TrafficSignalControllerNotifyErrorContext *p)
{
	if (p == NULL) return;
	TrafficSignalControllerNotifyErrorContext_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerNotifyErrorContext_dump(TrafficSignalControllerNotifyErrorContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), TrafficSignalControllerProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("log = ")); Dz1Str_dump(p->log, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyStateArg
TrafficSignalControllerNotifyStateArg *TrafficSignalControllerNotifyStateArg_new(u32_t testIdx, 
																				 TrafficSignalControllerNotifyStateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerNotifyStateArg *__internal_ret = (TrafficSignalControllerNotifyStateArg *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyStateArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyStateArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyStateArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerNotifyStateArg_copy(TrafficSignalControllerNotifyStateArg *dst, TrafficSignalControllerNotifyStateArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = TrafficSignalControllerNotifyStateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerNotifyStateArg *TrafficSignalControllerNotifyStateArg_clone(TrafficSignalControllerNotifyStateArg *src, Dz1Error *err)
{
	TrafficSignalControllerNotifyStateArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerNotifyStateArg *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyStateArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyStateArg_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerNotifyStateArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyStateArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerNotifyStateArg_purge(TrafficSignalControllerNotifyStateArg *p)
{
	if (p == NULL) return;
	TrafficSignalControllerNotifyStateContext_del(p->context);
}

void TrafficSignalControllerNotifyStateArg_del(TrafficSignalControllerNotifyStateArg *p)
{
	if (p == NULL) return;
	TrafficSignalControllerNotifyStateArg_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerNotifyStateArg_dump(TrafficSignalControllerNotifyStateArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); TrafficSignalControllerNotifyStateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerNotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyInfoArg
TrafficSignalControllerNotifyInfoArg *TrafficSignalControllerNotifyInfoArg_new(u32_t testIdx, 
																			   TrafficSignalControllerNotifyInfoContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerNotifyInfoArg *__internal_ret = (TrafficSignalControllerNotifyInfoArg *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyInfoArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyInfoArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyInfoArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerNotifyInfoArg_copy(TrafficSignalControllerNotifyInfoArg *dst, TrafficSignalControllerNotifyInfoArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = TrafficSignalControllerNotifyInfoContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerNotifyInfoArg *TrafficSignalControllerNotifyInfoArg_clone(TrafficSignalControllerNotifyInfoArg *src, Dz1Error *err)
{
	TrafficSignalControllerNotifyInfoArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerNotifyInfoArg *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyInfoArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyInfoArg_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerNotifyInfoArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyInfoArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerNotifyInfoArg_purge(TrafficSignalControllerNotifyInfoArg *p)
{
	if (p == NULL) return;
	TrafficSignalControllerNotifyInfoContext_del(p->context);
}

void TrafficSignalControllerNotifyInfoArg_del(TrafficSignalControllerNotifyInfoArg *p)
{
	if (p == NULL) return;
	TrafficSignalControllerNotifyInfoArg_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerNotifyInfoArg_dump(TrafficSignalControllerNotifyInfoArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); TrafficSignalControllerNotifyInfoContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerNotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyErrorArg
TrafficSignalControllerNotifyErrorArg *TrafficSignalControllerNotifyErrorArg_new(u32_t testIdx, 
																				 TrafficSignalControllerNotifyErrorContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerNotifyErrorArg *__internal_ret = (TrafficSignalControllerNotifyErrorArg *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyErrorArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyErrorArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyErrorArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerNotifyErrorArg_copy(TrafficSignalControllerNotifyErrorArg *dst, TrafficSignalControllerNotifyErrorArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = TrafficSignalControllerNotifyErrorContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerNotifyErrorArg *TrafficSignalControllerNotifyErrorArg_clone(TrafficSignalControllerNotifyErrorArg *src, Dz1Error *err)
{
	TrafficSignalControllerNotifyErrorArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerNotifyErrorArg *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyErrorArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyErrorArg_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerNotifyErrorArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyErrorArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerNotifyErrorArg_purge(TrafficSignalControllerNotifyErrorArg *p)
{
	if (p == NULL) return;
	TrafficSignalControllerNotifyErrorContext_del(p->context);
}

void TrafficSignalControllerNotifyErrorArg_del(TrafficSignalControllerNotifyErrorArg *p)
{
	if (p == NULL) return;
	TrafficSignalControllerNotifyErrorArg_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerNotifyErrorArg_dump(TrafficSignalControllerNotifyErrorArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); TrafficSignalControllerNotifyErrorContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerNotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyContextPresent
static struct TrafficSignalControllerNotifyContextPresentMapA
{
	str_t str;
	TrafficSignalControllerNotifyContextPresent v;
} TrafficSignalControllerNotifyContextPresentMapA[] =
{
	{ (char *)"state", TrafficSignalControllerNotifyContextPresent_state },
	{ (char *)"info", TrafficSignalControllerNotifyContextPresent_info },
	{ (char *)"error", TrafficSignalControllerNotifyContextPresent_error },
	{ NULL, TrafficSignalControllerNotifyContextPresent_max }
};

str_t TrafficSignalControllerNotifyContextPresentStrA(TrafficSignalControllerNotifyContextPresent v)
{
	struct TrafficSignalControllerNotifyContextPresentMapA *i = NULL;
	for (i = TrafficSignalControllerNotifyContextPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerNotifyContextPresent TrafficSignalControllerNotifyContextPresentFromStrA(str_t str)
{
	struct TrafficSignalControllerNotifyContextPresentMapA *i = NULL;
	for (i = TrafficSignalControllerNotifyContextPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerNotifyContextPresent_max;
}
#ifndef UNIX_SYSTEM
static struct TrafficSignalControllerNotifyContextPresentMapW
{
	wstr_t str;
	TrafficSignalControllerNotifyContextPresent v;
} TrafficSignalControllerNotifyContextPresentMapW[] =
{
	{ (wchar_t *)L"state", TrafficSignalControllerNotifyContextPresent_state },
	{ (wchar_t *)L"info", TrafficSignalControllerNotifyContextPresent_info },
	{ (wchar_t *)L"error", TrafficSignalControllerNotifyContextPresent_error },
	{ NULL, TrafficSignalControllerNotifyContextPresent_max }
};

wstr_t TrafficSignalControllerNotifyContextPresentStrW(TrafficSignalControllerNotifyContextPresent v)
{
	struct TrafficSignalControllerNotifyContextPresentMapW *i = NULL;
	for (i = TrafficSignalControllerNotifyContextPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerNotifyContextPresent TrafficSignalControllerNotifyContextPresentFromStrW(wstr_t str)
{
	struct TrafficSignalControllerNotifyContextPresentMapW *i = NULL;
	for (i = TrafficSignalControllerNotifyContextPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerNotifyContextPresent_max;
}
#endif // UNIX_SYSTEM

TrafficSignalControllerNotifyContextPresent *TrafficSignalControllerNotifyContextPresent_new(TrafficSignalControllerNotifyContextPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerNotifyContextPresent *__internal_ret = (TrafficSignalControllerNotifyContextPresent *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyContextPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void TrafficSignalControllerNotifyContextPresent_dump(TrafficSignalControllerNotifyContextPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), TrafficSignalControllerNotifyContextPresentStr(*v));
}
// TrafficSignalControllerNotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyContext
TrafficSignalControllerNotifyContext *TrafficSignalControllerNotifyContext_new(TrafficSignalControllerNotifyContextPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerNotifyContext *ret = (TrafficSignalControllerNotifyContext *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyContext), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyContext_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case TrafficSignalControllerNotifyContextPresent_state:
			// _U_cst_clone
			if (ptr != NULL) ret->x.state = (TrafficSignalControllerNotifyStateContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerNotifyContextPresent_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.info = (TrafficSignalControllerNotifyInfoContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerNotifyContextPresent_error:
			// _U_cst_clone
			if (ptr != NULL) ret->x.error = (TrafficSignalControllerNotifyErrorContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerNotifyContextPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t TrafficSignalControllerNotifyContext_copy(TrafficSignalControllerNotifyContext *ret, TrafficSignalControllerNotifyContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case TrafficSignalControllerNotifyContextPresent_state:
			// _U_cst_clone
			if (src->x.state && (ret->x.state = TrafficSignalControllerNotifyStateContext_clone(src->x.state, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerNotifyContextPresent_info:
			// _U_cst_clone
			if (src->x.info && (ret->x.info = TrafficSignalControllerNotifyInfoContext_clone(src->x.info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerNotifyContextPresent_error:
			// _U_cst_clone
			if (src->x.error && (ret->x.error = TrafficSignalControllerNotifyErrorContext_clone(src->x.error, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerNotifyContext *TrafficSignalControllerNotifyContext_clone(TrafficSignalControllerNotifyContext *src, Dz1Error *err)
{
	TrafficSignalControllerNotifyContext *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (TrafficSignalControllerNotifyContext *)Dz1Calloc(sizeof(TrafficSignalControllerNotifyContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyContext_delAndSetNull, (void *)&ret);
		if (TrafficSignalControllerNotifyContext_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerNotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TrafficSignalControllerNotifyContext_purge(TrafficSignalControllerNotifyContext *p)
{
	if (!p) return;
	switch(p->present)
	{
	case TrafficSignalControllerNotifyContextPresent_state:
		TrafficSignalControllerNotifyStateContext_del(p->x.state);
		break;
	case TrafficSignalControllerNotifyContextPresent_info:
		TrafficSignalControllerNotifyInfoContext_del(p->x.info);
		break;
	case TrafficSignalControllerNotifyContextPresent_error:
		TrafficSignalControllerNotifyErrorContext_del(p->x.error);
		break;
	default:
		break;
	}
}

void TrafficSignalControllerNotifyContext_del(TrafficSignalControllerNotifyContext *p)
{
	if (!p) return;
	TrafficSignalControllerNotifyContext_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerNotifyContext_dump(TrafficSignalControllerNotifyContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case TrafficSignalControllerNotifyContextPresent_state:
		Dz1Thread_printf(Dz1T("state = ")); TrafficSignalControllerNotifyStateContext_dump(p->x.state, tab); 
		break;
	case TrafficSignalControllerNotifyContextPresent_info:
		Dz1Thread_printf(Dz1T("info = ")); TrafficSignalControllerNotifyInfoContext_dump(p->x.info, tab); 
		break;
	case TrafficSignalControllerNotifyContextPresent_error:
		Dz1Thread_printf(Dz1T("error = ")); TrafficSignalControllerNotifyErrorContext_dump(p->x.error, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// TrafficSignalControllerNotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerValidateContext
TrafficSignalControllerValidateContext *TrafficSignalControllerValidateContext_new(Dz1Str testName, 
																				   s64_t time, 
																				   Dz1Binary *raw, 
																				   Dz1Binary *data, 
																				   TrafficSignalControllerProcessStatusCode code, 
																				   Dz1Str desc, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerValidateContext *__internal_ret = (TrafficSignalControllerValidateContext *)Dz1Calloc(sizeof(TrafficSignalControllerValidateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerValidateContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerValidateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerValidateContext_copy(TrafficSignalControllerValidateContext *dst, TrafficSignalControllerValidateContext *src, Dz1Error *err)
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

TrafficSignalControllerValidateContext *TrafficSignalControllerValidateContext_clone(TrafficSignalControllerValidateContext *src, Dz1Error *err)
{
	TrafficSignalControllerValidateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerValidateContext *)Dz1Calloc(sizeof(TrafficSignalControllerValidateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerValidateContext_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerValidateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerValidateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerValidateContext_purge(TrafficSignalControllerValidateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Binary_del(p->raw);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->desc);
}

void TrafficSignalControllerValidateContext_del(TrafficSignalControllerValidateContext *p)
{
	if (p == NULL) return;
	TrafficSignalControllerValidateContext_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerValidateContext_dump(TrafficSignalControllerValidateContext *p, int tab)
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
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), TrafficSignalControllerProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerValidateContextArg
TrafficSignalControllerValidateContextArg *TrafficSignalControllerValidateContextArg_new(u32_t testIdx, 
																						 TrafficSignalControllerValidateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerValidateContextArg *__internal_ret = (TrafficSignalControllerValidateContextArg *)Dz1Calloc(sizeof(TrafficSignalControllerValidateContextArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerValidateContextArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerValidateContextArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerValidateContextArg_copy(TrafficSignalControllerValidateContextArg *dst, TrafficSignalControllerValidateContextArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = TrafficSignalControllerValidateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerValidateContextArg *TrafficSignalControllerValidateContextArg_clone(TrafficSignalControllerValidateContextArg *src, Dz1Error *err)
{
	TrafficSignalControllerValidateContextArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerValidateContextArg *)Dz1Calloc(sizeof(TrafficSignalControllerValidateContextArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerValidateContextArg_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerValidateContextArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerValidateContextArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerValidateContextArg_purge(TrafficSignalControllerValidateContextArg *p)
{
	if (p == NULL) return;
	TrafficSignalControllerValidateContext_del(p->context);
}

void TrafficSignalControllerValidateContextArg_del(TrafficSignalControllerValidateContextArg *p)
{
	if (p == NULL) return;
	TrafficSignalControllerValidateContextArg_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerValidateContextArg_dump(TrafficSignalControllerValidateContextArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); TrafficSignalControllerValidateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerValidateContextArg
////////////////////////////////////////////////////////////////////////////////

