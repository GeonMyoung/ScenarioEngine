////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDSRCMsgTestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgProcessStatusCode
static struct GitsnDSRCMsgProcessStatusCodeMapA
{
	str_t str;
	GitsnDSRCMsgProcessStatusCode v;
} GitsnDSRCMsgProcessStatusCodeMapA[] =
{
	{ (char *)"OK", GitsnDSRCMsgProcessStatusCode_OK },
	{ (char *)"FAILURE", GitsnDSRCMsgProcessStatusCode_FAILURE },
	{ (char *)"AGENT_SYSTEM_ERROR", GitsnDSRCMsgProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (char *)"SERVER_DISCONNECTED", GitsnDSRCMsgProcessStatusCode_SERVER_DISCONNECTED },
	{ (char *)"TEST_CONFIGURATION_ERROR", GitsnDSRCMsgProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (char *)"CONNECTION_FAIL", GitsnDSRCMsgProcessStatusCode_CONNECTION_FAIL },
	{ (char *)"DISCONNECTED", GitsnDSRCMsgProcessStatusCode_DISCONNECTED },
	{ (char *)"TIMEOUT", GitsnDSRCMsgProcessStatusCode_TIMEOUT },
	{ (char *)"OUT_OF_RANGE", GitsnDSRCMsgProcessStatusCode_OUT_OF_RANGE },
	{ (char *)"INVALID_PROCESS", GitsnDSRCMsgProcessStatusCode_INVALID_PROCESS },
	{ (char *)"INVALID_IDENTIFIER", GitsnDSRCMsgProcessStatusCode_INVALID_IDENTIFIER },
	{ (char *)"SESSION_DUPLICATE", GitsnDSRCMsgProcessStatusCode_SESSION_DUPLICATE },
	{ (char *)"LOGIN_AUTH_ERROR", GitsnDSRCMsgProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (char *)"DECODE_FAIL", GitsnDSRCMsgProcessStatusCode_DECODE_FAIL },
	{ (char *)"INVALID_ENCODING_RULE", GitsnDSRCMsgProcessStatusCode_INVALID_ENCODING_RULE },
	{ (char *)"INVALID_OID", GitsnDSRCMsgProcessStatusCode_INVALID_OID },
	{ (char *)"INVALID_DSRC_MSG_ID", GitsnDSRCMsgProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (char *)"JSON_PARSE_ERROR", GitsnDSRCMsgProcessStatusCode_JSON_PARSE_ERROR },
	{ (char *)"PROTOBUF_DESERAILIZE_ERROR", GitsnDSRCMsgProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (char *)"INVALID_TOPIC", GitsnDSRCMsgProcessStatusCode_INVALID_TOPIC },
	{ (char *)"INVALID_REQUEST", GitsnDSRCMsgProcessStatusCode_INVALID_REQUEST },
	{ (char *)"UNKNOWN", GitsnDSRCMsgProcessStatusCode_UNKNOWN },
	{ NULL, GitsnDSRCMsgProcessStatusCode_max }
};

str_t GitsnDSRCMsgProcessStatusCodeStrA(GitsnDSRCMsgProcessStatusCode v)
{
	struct GitsnDSRCMsgProcessStatusCodeMapA *i = NULL;
	for (i = GitsnDSRCMsgProcessStatusCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgProcessStatusCode GitsnDSRCMsgProcessStatusCodeFromStrA(str_t str)
{
	struct GitsnDSRCMsgProcessStatusCodeMapA *i = NULL;
	for (i = GitsnDSRCMsgProcessStatusCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgProcessStatusCode_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnDSRCMsgProcessStatusCodeMapW
{
	wstr_t str;
	GitsnDSRCMsgProcessStatusCode v;
} GitsnDSRCMsgProcessStatusCodeMapW[] =
{
	{ (wchar_t *)L"OK", GitsnDSRCMsgProcessStatusCode_OK },
	{ (wchar_t *)L"FAILURE", GitsnDSRCMsgProcessStatusCode_FAILURE },
	{ (wchar_t *)L"AGENT_SYSTEM_ERROR", GitsnDSRCMsgProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (wchar_t *)L"SERVER_DISCONNECTED", GitsnDSRCMsgProcessStatusCode_SERVER_DISCONNECTED },
	{ (wchar_t *)L"TEST_CONFIGURATION_ERROR", GitsnDSRCMsgProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (wchar_t *)L"CONNECTION_FAIL", GitsnDSRCMsgProcessStatusCode_CONNECTION_FAIL },
	{ (wchar_t *)L"DISCONNECTED", GitsnDSRCMsgProcessStatusCode_DISCONNECTED },
	{ (wchar_t *)L"TIMEOUT", GitsnDSRCMsgProcessStatusCode_TIMEOUT },
	{ (wchar_t *)L"OUT_OF_RANGE", GitsnDSRCMsgProcessStatusCode_OUT_OF_RANGE },
	{ (wchar_t *)L"INVALID_PROCESS", GitsnDSRCMsgProcessStatusCode_INVALID_PROCESS },
	{ (wchar_t *)L"INVALID_IDENTIFIER", GitsnDSRCMsgProcessStatusCode_INVALID_IDENTIFIER },
	{ (wchar_t *)L"SESSION_DUPLICATE", GitsnDSRCMsgProcessStatusCode_SESSION_DUPLICATE },
	{ (wchar_t *)L"LOGIN_AUTH_ERROR", GitsnDSRCMsgProcessStatusCode_LOGIN_AUTH_ERROR },
	{ (wchar_t *)L"DECODE_FAIL", GitsnDSRCMsgProcessStatusCode_DECODE_FAIL },
	{ (wchar_t *)L"INVALID_ENCODING_RULE", GitsnDSRCMsgProcessStatusCode_INVALID_ENCODING_RULE },
	{ (wchar_t *)L"INVALID_OID", GitsnDSRCMsgProcessStatusCode_INVALID_OID },
	{ (wchar_t *)L"INVALID_DSRC_MSG_ID", GitsnDSRCMsgProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (wchar_t *)L"JSON_PARSE_ERROR", GitsnDSRCMsgProcessStatusCode_JSON_PARSE_ERROR },
	{ (wchar_t *)L"PROTOBUF_DESERAILIZE_ERROR", GitsnDSRCMsgProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (wchar_t *)L"INVALID_TOPIC", GitsnDSRCMsgProcessStatusCode_INVALID_TOPIC },
	{ (wchar_t *)L"INVALID_REQUEST", GitsnDSRCMsgProcessStatusCode_INVALID_REQUEST },
	{ (wchar_t *)L"UNKNOWN", GitsnDSRCMsgProcessStatusCode_UNKNOWN },
	{ NULL, GitsnDSRCMsgProcessStatusCode_max }
};

wstr_t GitsnDSRCMsgProcessStatusCodeStrW(GitsnDSRCMsgProcessStatusCode v)
{
	struct GitsnDSRCMsgProcessStatusCodeMapW *i = NULL;
	for (i = GitsnDSRCMsgProcessStatusCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgProcessStatusCode GitsnDSRCMsgProcessStatusCodeFromStrW(wstr_t str)
{
	struct GitsnDSRCMsgProcessStatusCodeMapW *i = NULL;
	for (i = GitsnDSRCMsgProcessStatusCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgProcessStatusCode_max;
}
#endif // UNIX_SYSTEM

GitsnDSRCMsgProcessStatusCode *GitsnDSRCMsgProcessStatusCode_new(GitsnDSRCMsgProcessStatusCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgProcessStatusCode *__internal_ret = (GitsnDSRCMsgProcessStatusCode *)Dz1Calloc(sizeof(GitsnDSRCMsgProcessStatusCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void GitsnDSRCMsgProcessStatusCode_dump(GitsnDSRCMsgProcessStatusCode *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), GitsnDSRCMsgProcessStatusCodeStr(*v));
}
// GitsnDSRCMsgProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyStateContext
GitsnDSRCMsgNotifyStateContext *GitsnDSRCMsgNotifyStateContext_new(Dz1Str testName, 
																   s64_t time, 
																   Dz1Str state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgNotifyStateContext *__internal_ret = (GitsnDSRCMsgNotifyStateContext *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyStateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyStateContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (state && (__internal_ret->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyStateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgNotifyStateContext_copy(GitsnDSRCMsgNotifyStateContext *dst, GitsnDSRCMsgNotifyStateContext *src, Dz1Error *err)
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

GitsnDSRCMsgNotifyStateContext *GitsnDSRCMsgNotifyStateContext_clone(GitsnDSRCMsgNotifyStateContext *src, Dz1Error *err)
{
	GitsnDSRCMsgNotifyStateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgNotifyStateContext *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyStateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyStateContext_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgNotifyStateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyStateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgNotifyStateContext_purge(GitsnDSRCMsgNotifyStateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->state);
}

void GitsnDSRCMsgNotifyStateContext_del(GitsnDSRCMsgNotifyStateContext *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgNotifyStateContext_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgNotifyStateContext_dump(GitsnDSRCMsgNotifyStateContext *p, int tab)
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
// GitsnDSRCMsgNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyInfoContext
GitsnDSRCMsgNotifyInfoContext *GitsnDSRCMsgNotifyInfoContext_new(Dz1Str testName, 
																 s64_t time, 
																 Dz1Str sender, 
																 Dz1Str log, 
																 Dz1Binary *data, 
																 Dz1Str dataType, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgNotifyInfoContext *__internal_ret = (GitsnDSRCMsgNotifyInfoContext *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyInfoContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyInfoContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyInfoContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgNotifyInfoContext_copy(GitsnDSRCMsgNotifyInfoContext *dst, GitsnDSRCMsgNotifyInfoContext *src, Dz1Error *err)
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

GitsnDSRCMsgNotifyInfoContext *GitsnDSRCMsgNotifyInfoContext_clone(GitsnDSRCMsgNotifyInfoContext *src, Dz1Error *err)
{
	GitsnDSRCMsgNotifyInfoContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgNotifyInfoContext *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyInfoContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyInfoContext_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgNotifyInfoContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyInfoContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgNotifyInfoContext_purge(GitsnDSRCMsgNotifyInfoContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->sender);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->dataType);
}

void GitsnDSRCMsgNotifyInfoContext_del(GitsnDSRCMsgNotifyInfoContext *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgNotifyInfoContext_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgNotifyInfoContext_dump(GitsnDSRCMsgNotifyInfoContext *p, int tab)
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
// GitsnDSRCMsgNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyErrorContext
GitsnDSRCMsgNotifyErrorContext *GitsnDSRCMsgNotifyErrorContext_new(Dz1Str testName, 
																   s64_t time, 
																   GitsnDSRCMsgProcessStatusCode code, 
																   Dz1Str desc, 
																   Dz1Str log, 
																   Dz1Binary *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgNotifyErrorContext *__internal_ret = (GitsnDSRCMsgNotifyErrorContext *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyErrorContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyErrorContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyErrorContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgNotifyErrorContext_copy(GitsnDSRCMsgNotifyErrorContext *dst, GitsnDSRCMsgNotifyErrorContext *src, Dz1Error *err)
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

GitsnDSRCMsgNotifyErrorContext *GitsnDSRCMsgNotifyErrorContext_clone(GitsnDSRCMsgNotifyErrorContext *src, Dz1Error *err)
{
	GitsnDSRCMsgNotifyErrorContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgNotifyErrorContext *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyErrorContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyErrorContext_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgNotifyErrorContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyErrorContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgNotifyErrorContext_purge(GitsnDSRCMsgNotifyErrorContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->desc);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
}

void GitsnDSRCMsgNotifyErrorContext_del(GitsnDSRCMsgNotifyErrorContext *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgNotifyErrorContext_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgNotifyErrorContext_dump(GitsnDSRCMsgNotifyErrorContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), GitsnDSRCMsgProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("log = ")); Dz1Str_dump(p->log, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDSRCMsgNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyStateArg
GitsnDSRCMsgNotifyStateArg *GitsnDSRCMsgNotifyStateArg_new(u32_t testIdx, 
														   GitsnDSRCMsgNotifyStateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgNotifyStateArg *__internal_ret = (GitsnDSRCMsgNotifyStateArg *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyStateArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyStateArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyStateArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgNotifyStateArg_copy(GitsnDSRCMsgNotifyStateArg *dst, GitsnDSRCMsgNotifyStateArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = GitsnDSRCMsgNotifyStateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnDSRCMsgNotifyStateArg *GitsnDSRCMsgNotifyStateArg_clone(GitsnDSRCMsgNotifyStateArg *src, Dz1Error *err)
{
	GitsnDSRCMsgNotifyStateArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgNotifyStateArg *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyStateArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyStateArg_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgNotifyStateArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyStateArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgNotifyStateArg_purge(GitsnDSRCMsgNotifyStateArg *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgNotifyStateContext_del(p->context);
}

void GitsnDSRCMsgNotifyStateArg_del(GitsnDSRCMsgNotifyStateArg *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgNotifyStateArg_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgNotifyStateArg_dump(GitsnDSRCMsgNotifyStateArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); GitsnDSRCMsgNotifyStateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDSRCMsgNotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyInfoArg
GitsnDSRCMsgNotifyInfoArg *GitsnDSRCMsgNotifyInfoArg_new(u32_t testIdx, 
														 GitsnDSRCMsgNotifyInfoContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgNotifyInfoArg *__internal_ret = (GitsnDSRCMsgNotifyInfoArg *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyInfoArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyInfoArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyInfoArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgNotifyInfoArg_copy(GitsnDSRCMsgNotifyInfoArg *dst, GitsnDSRCMsgNotifyInfoArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = GitsnDSRCMsgNotifyInfoContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnDSRCMsgNotifyInfoArg *GitsnDSRCMsgNotifyInfoArg_clone(GitsnDSRCMsgNotifyInfoArg *src, Dz1Error *err)
{
	GitsnDSRCMsgNotifyInfoArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgNotifyInfoArg *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyInfoArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyInfoArg_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgNotifyInfoArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyInfoArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgNotifyInfoArg_purge(GitsnDSRCMsgNotifyInfoArg *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgNotifyInfoContext_del(p->context);
}

void GitsnDSRCMsgNotifyInfoArg_del(GitsnDSRCMsgNotifyInfoArg *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgNotifyInfoArg_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgNotifyInfoArg_dump(GitsnDSRCMsgNotifyInfoArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); GitsnDSRCMsgNotifyInfoContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDSRCMsgNotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyErrorArg
GitsnDSRCMsgNotifyErrorArg *GitsnDSRCMsgNotifyErrorArg_new(u32_t testIdx, 
														   GitsnDSRCMsgNotifyErrorContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgNotifyErrorArg *__internal_ret = (GitsnDSRCMsgNotifyErrorArg *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyErrorArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyErrorArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyErrorArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgNotifyErrorArg_copy(GitsnDSRCMsgNotifyErrorArg *dst, GitsnDSRCMsgNotifyErrorArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = GitsnDSRCMsgNotifyErrorContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnDSRCMsgNotifyErrorArg *GitsnDSRCMsgNotifyErrorArg_clone(GitsnDSRCMsgNotifyErrorArg *src, Dz1Error *err)
{
	GitsnDSRCMsgNotifyErrorArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgNotifyErrorArg *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyErrorArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyErrorArg_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgNotifyErrorArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyErrorArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgNotifyErrorArg_purge(GitsnDSRCMsgNotifyErrorArg *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgNotifyErrorContext_del(p->context);
}

void GitsnDSRCMsgNotifyErrorArg_del(GitsnDSRCMsgNotifyErrorArg *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgNotifyErrorArg_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgNotifyErrorArg_dump(GitsnDSRCMsgNotifyErrorArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); GitsnDSRCMsgNotifyErrorContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDSRCMsgNotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyContextPresent
static struct GitsnDSRCMsgNotifyContextPresentMapA
{
	str_t str;
	GitsnDSRCMsgNotifyContextPresent v;
} GitsnDSRCMsgNotifyContextPresentMapA[] =
{
	{ (char *)"state", GitsnDSRCMsgNotifyContextPresent_state },
	{ (char *)"info", GitsnDSRCMsgNotifyContextPresent_info },
	{ (char *)"error", GitsnDSRCMsgNotifyContextPresent_error },
	{ NULL, GitsnDSRCMsgNotifyContextPresent_max }
};

str_t GitsnDSRCMsgNotifyContextPresentStrA(GitsnDSRCMsgNotifyContextPresent v)
{
	struct GitsnDSRCMsgNotifyContextPresentMapA *i = NULL;
	for (i = GitsnDSRCMsgNotifyContextPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgNotifyContextPresent GitsnDSRCMsgNotifyContextPresentFromStrA(str_t str)
{
	struct GitsnDSRCMsgNotifyContextPresentMapA *i = NULL;
	for (i = GitsnDSRCMsgNotifyContextPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgNotifyContextPresent_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnDSRCMsgNotifyContextPresentMapW
{
	wstr_t str;
	GitsnDSRCMsgNotifyContextPresent v;
} GitsnDSRCMsgNotifyContextPresentMapW[] =
{
	{ (wchar_t *)L"state", GitsnDSRCMsgNotifyContextPresent_state },
	{ (wchar_t *)L"info", GitsnDSRCMsgNotifyContextPresent_info },
	{ (wchar_t *)L"error", GitsnDSRCMsgNotifyContextPresent_error },
	{ NULL, GitsnDSRCMsgNotifyContextPresent_max }
};

wstr_t GitsnDSRCMsgNotifyContextPresentStrW(GitsnDSRCMsgNotifyContextPresent v)
{
	struct GitsnDSRCMsgNotifyContextPresentMapW *i = NULL;
	for (i = GitsnDSRCMsgNotifyContextPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgNotifyContextPresent GitsnDSRCMsgNotifyContextPresentFromStrW(wstr_t str)
{
	struct GitsnDSRCMsgNotifyContextPresentMapW *i = NULL;
	for (i = GitsnDSRCMsgNotifyContextPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgNotifyContextPresent_max;
}
#endif // UNIX_SYSTEM

GitsnDSRCMsgNotifyContextPresent *GitsnDSRCMsgNotifyContextPresent_new(GitsnDSRCMsgNotifyContextPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgNotifyContextPresent *__internal_ret = (GitsnDSRCMsgNotifyContextPresent *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyContextPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void GitsnDSRCMsgNotifyContextPresent_dump(GitsnDSRCMsgNotifyContextPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), GitsnDSRCMsgNotifyContextPresentStr(*v));
}
// GitsnDSRCMsgNotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyContext
GitsnDSRCMsgNotifyContext *GitsnDSRCMsgNotifyContext_new(GitsnDSRCMsgNotifyContextPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgNotifyContext *ret = (GitsnDSRCMsgNotifyContext *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyContext), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyContext_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case GitsnDSRCMsgNotifyContextPresent_state:
			// _U_cst_clone
			if (ptr != NULL) ret->x.state = (GitsnDSRCMsgNotifyStateContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnDSRCMsgNotifyContextPresent_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.info = (GitsnDSRCMsgNotifyInfoContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnDSRCMsgNotifyContextPresent_error:
			// _U_cst_clone
			if (ptr != NULL) ret->x.error = (GitsnDSRCMsgNotifyErrorContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnDSRCMsgNotifyContextPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t GitsnDSRCMsgNotifyContext_copy(GitsnDSRCMsgNotifyContext *ret, GitsnDSRCMsgNotifyContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case GitsnDSRCMsgNotifyContextPresent_state:
			// _U_cst_clone
			if (src->x.state && (ret->x.state = GitsnDSRCMsgNotifyStateContext_clone(src->x.state, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case GitsnDSRCMsgNotifyContextPresent_info:
			// _U_cst_clone
			if (src->x.info && (ret->x.info = GitsnDSRCMsgNotifyInfoContext_clone(src->x.info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case GitsnDSRCMsgNotifyContextPresent_error:
			// _U_cst_clone
			if (src->x.error && (ret->x.error = GitsnDSRCMsgNotifyErrorContext_clone(src->x.error, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnDSRCMsgNotifyContext *GitsnDSRCMsgNotifyContext_clone(GitsnDSRCMsgNotifyContext *src, Dz1Error *err)
{
	GitsnDSRCMsgNotifyContext *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (GitsnDSRCMsgNotifyContext *)Dz1Calloc(sizeof(GitsnDSRCMsgNotifyContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyContext_delAndSetNull, (void *)&ret);
		if (GitsnDSRCMsgNotifyContext_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgNotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GitsnDSRCMsgNotifyContext_purge(GitsnDSRCMsgNotifyContext *p)
{
	if (!p) return;
	switch(p->present)
	{
	case GitsnDSRCMsgNotifyContextPresent_state:
		GitsnDSRCMsgNotifyStateContext_del(p->x.state);
		break;
	case GitsnDSRCMsgNotifyContextPresent_info:
		GitsnDSRCMsgNotifyInfoContext_del(p->x.info);
		break;
	case GitsnDSRCMsgNotifyContextPresent_error:
		GitsnDSRCMsgNotifyErrorContext_del(p->x.error);
		break;
	default:
		break;
	}
}

void GitsnDSRCMsgNotifyContext_del(GitsnDSRCMsgNotifyContext *p)
{
	if (!p) return;
	GitsnDSRCMsgNotifyContext_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgNotifyContext_dump(GitsnDSRCMsgNotifyContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case GitsnDSRCMsgNotifyContextPresent_state:
		Dz1Thread_printf(Dz1T("state = ")); GitsnDSRCMsgNotifyStateContext_dump(p->x.state, tab); 
		break;
	case GitsnDSRCMsgNotifyContextPresent_info:
		Dz1Thread_printf(Dz1T("info = ")); GitsnDSRCMsgNotifyInfoContext_dump(p->x.info, tab); 
		break;
	case GitsnDSRCMsgNotifyContextPresent_error:
		Dz1Thread_printf(Dz1T("error = ")); GitsnDSRCMsgNotifyErrorContext_dump(p->x.error, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// GitsnDSRCMsgNotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgValidateContext
GitsnDSRCMsgValidateContext *GitsnDSRCMsgValidateContext_new(Dz1Str testName, 
															 s64_t time, 
															 Dz1Binary *raw, 
															 Dz1Binary *data, 
															 GitsnDSRCMsgProcessStatusCode code, 
															 Dz1Str desc, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgValidateContext *__internal_ret = (GitsnDSRCMsgValidateContext *)Dz1Calloc(sizeof(GitsnDSRCMsgValidateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgValidateContext_delAndSetNull, (void *)&__internal_ret);
		
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgValidateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgValidateContext_copy(GitsnDSRCMsgValidateContext *dst, GitsnDSRCMsgValidateContext *src, Dz1Error *err)
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

GitsnDSRCMsgValidateContext *GitsnDSRCMsgValidateContext_clone(GitsnDSRCMsgValidateContext *src, Dz1Error *err)
{
	GitsnDSRCMsgValidateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgValidateContext *)Dz1Calloc(sizeof(GitsnDSRCMsgValidateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgValidateContext_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgValidateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgValidateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgValidateContext_purge(GitsnDSRCMsgValidateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Binary_del(p->raw);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->desc);
}

void GitsnDSRCMsgValidateContext_del(GitsnDSRCMsgValidateContext *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgValidateContext_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgValidateContext_dump(GitsnDSRCMsgValidateContext *p, int tab)
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
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), GitsnDSRCMsgProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDSRCMsgValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgValidateContextArg
GitsnDSRCMsgValidateContextArg *GitsnDSRCMsgValidateContextArg_new(u32_t testIdx, 
																   GitsnDSRCMsgValidateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgValidateContextArg *__internal_ret = (GitsnDSRCMsgValidateContextArg *)Dz1Calloc(sizeof(GitsnDSRCMsgValidateContextArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgValidateContextArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgValidateContextArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgValidateContextArg_copy(GitsnDSRCMsgValidateContextArg *dst, GitsnDSRCMsgValidateContextArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = GitsnDSRCMsgValidateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnDSRCMsgValidateContextArg *GitsnDSRCMsgValidateContextArg_clone(GitsnDSRCMsgValidateContextArg *src, Dz1Error *err)
{
	GitsnDSRCMsgValidateContextArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgValidateContextArg *)Dz1Calloc(sizeof(GitsnDSRCMsgValidateContextArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgValidateContextArg_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgValidateContextArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgValidateContextArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgValidateContextArg_purge(GitsnDSRCMsgValidateContextArg *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgValidateContext_del(p->context);
}

void GitsnDSRCMsgValidateContextArg_del(GitsnDSRCMsgValidateContextArg *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgValidateContextArg_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgValidateContextArg_dump(GitsnDSRCMsgValidateContextArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); GitsnDSRCMsgValidateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDSRCMsgValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestConfiguration
GitsnDSRCMsgTestConfiguration *GitsnDSRCMsgTestConfiguration_new(s64_t local_port, 
																 bool_t test_map, 
																 bool_t test_spat, 
																 bool_t test_bsm, 
																 bool_t test_eva, 
																 bool_t test_pvd, 
																 bool_t test_rsa, 
																 bool_t test_rtcm, 
																 bool_t test_srm, 
																 bool_t test_ssm, 
																 bool_t test_tim, 
																 bool_t test_psm, 
																 bool_t test_sdsm, 
																 bool_t test_tls, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgTestConfiguration *__internal_ret = (GitsnDSRCMsgTestConfiguration *)Dz1Calloc(sizeof(GitsnDSRCMsgTestConfiguration), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgTestConfiguration_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->test_map = test_map;
		__internal_ret->test_spat = test_spat;
		__internal_ret->test_bsm = test_bsm;
		__internal_ret->test_eva = test_eva;
		__internal_ret->test_pvd = test_pvd;
		__internal_ret->test_rsa = test_rsa;
		__internal_ret->test_rtcm = test_rtcm;
		__internal_ret->test_srm = test_srm;
		__internal_ret->test_ssm = test_ssm;
		__internal_ret->test_tim = test_tim;
		__internal_ret->test_psm = test_psm;
		__internal_ret->test_sdsm = test_sdsm;
		__internal_ret->test_tls = test_tls;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgTestConfiguration_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgTestConfiguration_copy(GitsnDSRCMsgTestConfiguration *dst, GitsnDSRCMsgTestConfiguration *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->local_port = src->local_port;
		dst->test_map = src->test_map;
		dst->test_spat = src->test_spat;
		dst->test_bsm = src->test_bsm;
		dst->test_eva = src->test_eva;
		dst->test_pvd = src->test_pvd;
		dst->test_rsa = src->test_rsa;
		dst->test_rtcm = src->test_rtcm;
		dst->test_srm = src->test_srm;
		dst->test_ssm = src->test_ssm;
		dst->test_tim = src->test_tim;
		dst->test_psm = src->test_psm;
		dst->test_sdsm = src->test_sdsm;
		dst->test_tls = src->test_tls;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnDSRCMsgTestConfiguration *GitsnDSRCMsgTestConfiguration_clone(GitsnDSRCMsgTestConfiguration *src, Dz1Error *err)
{
	GitsnDSRCMsgTestConfiguration *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgTestConfiguration *)Dz1Calloc(sizeof(GitsnDSRCMsgTestConfiguration), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgTestConfiguration_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgTestConfiguration_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgTestConfiguration_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgTestConfiguration_purge(GitsnDSRCMsgTestConfiguration *p)
{
	if (p == NULL) return;
}

void GitsnDSRCMsgTestConfiguration_del(GitsnDSRCMsgTestConfiguration *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgTestConfiguration_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgTestConfiguration_dump(GitsnDSRCMsgTestConfiguration *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1s64_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_map = ")); Dz1Bool_dump(&p->test_map, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_spat = ")); Dz1Bool_dump(&p->test_spat, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_bsm = ")); Dz1Bool_dump(&p->test_bsm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_eva = ")); Dz1Bool_dump(&p->test_eva, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pvd = ")); Dz1Bool_dump(&p->test_pvd, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsa = ")); Dz1Bool_dump(&p->test_rsa, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rtcm = ")); Dz1Bool_dump(&p->test_rtcm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_srm = ")); Dz1Bool_dump(&p->test_srm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_ssm = ")); Dz1Bool_dump(&p->test_ssm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tim = ")); Dz1Bool_dump(&p->test_tim, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_psm = ")); Dz1Bool_dump(&p->test_psm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sdsm = ")); Dz1Bool_dump(&p->test_sdsm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tls = ")); Dz1Bool_dump(&p->test_tls, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDSRCMsgTestConfiguration
////////////////////////////////////////////////////////////////////////////////

