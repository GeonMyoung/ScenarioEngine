#include "txt_replace_env_util.h"
#include "txt_util.h"

///////////////////////////////////////////////////////////////////////////////
// TxtReplaceEnv Utility
Dz1Error TxtReplaceEnv_addReplace(TxtReplaceEnv *dst, str_t symbol, str_t replace)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TxtReplaceEntry *node = TxtReplaceEntry_new(symbol, replace, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TxtReplaceEntry_delAndSetNull, (void *)&node);
		if ((err = dst->list->add(dst->list, node)).code)
		{
			Dz1Thread_printf("!!! %s is not handled\n", symbol);
			ERR_OUT(errp);
		}
		else node = NULL;
		pthread_cleanup_pop(1); // (TxtReplaceEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

TxtReplaceEntry *TxtReplaceEnv_find(TxtReplaceEnv *env, Dz1Str symbol)
{
	TxtReplaceEntry *ret = NULL;
	TxtReplaceList *list = NULL;
	if (env != NULL && (list = env->list) != NULL && Dz1Str_isVoid(symbol) == FALSE)
	{
		TxtReplaceEntry key = { symbol };
		ret = list->find(list, &key);
	}
	return ret;
}
// TxtReplaceEnv Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Replace Core Function
typedef ssize_t (DataEmitFunc)(void *ptr, u8_t *data, size_t unit_size, size_t cnt, Dz1Error *err);
static bool_t txt_replace(TxtReplaceEnv *env, Dz1Str src, DataEmitFunc data_emit, void *emit_arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	size_t leadInSize = Dz1STRLEN(env->leadin);
	size_t leadOutSize = Dz1STRLEN(env->leadout);
	size_t writeSize, len = 0;

	TCHAR *cp = src, *leadin = NULL, *leadout = NULL, *_tok = NULL;

	Dz1Error_set(errp, 0);
	while ((leadin = Dz1STRSTR(cp, env->leadin)) != NULL)
	{
		writeSize = (size_t)(leadin - cp);						// length of 'cp' ~ {leadin}
		_tok = (leadin + leadInSize);							// pick token pointer = cp + len(leadin)
		if ((leadout = Dz1STRSTR(_tok, env->leadout)) == NULL)
		{
			Dz1Thread_printf(Dz1T("Lead IN str does not pare with Lead OUT str\n"));
			ERR_SET_OUT(errp, EINVAL);
		}
		else
		{
			TCHAR tok [64] = { 0, };
			size_t tokSize = leadout - _tok;
			if (tokSize >= 64) ERR_SET_OUT(errp, E2BIG);
			else 
			{
				TxtReplaceEntry key = { tok }, *p = NULL;
				memcpy(tok, _tok, tokSize);
				if (Dz1STRCMP(tok, Dz1T("$GUID")) == 0)
				{	// Ondemand GUID
					TCHAR str_guid[40] = { 0, }, *guid_str = NULL;
					if ((guid_str = MkGUIDStr(str_guid)) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((len = Dz1STRLEN(guid_str)) == 0) ERR_SET_OUT(errp, EFAULT);
					else if (data_emit(emit_arg, (u8_t *)cp,	   sizeof(TCHAR), writeSize, errp) != writeSize)  ERR_SET_OUT(errp, EPIPE);
					else if (data_emit(emit_arg, (u8_t *)str_guid, sizeof(TCHAR), len,		 errp) != len)  ERR_SET_OUT(errp, EPIPE);
				}
				else if ((p = env->list->find(env->list, &key)) == NULL)
				{
					Dz1Thread_printf(Dz1T("Unrecognized Literal [%s]\n"), tok);
					ERR_SET_OUT(errp, EINVAL);
				}
				// (cp::writeSize)([tok])
				else if ((len = Dz1STRLEN(p->replace)) == 0) ERR_SET_OUT(errp, EFAULT);
				else if (data_emit(emit_arg, (u8_t *)cp,		 sizeof(TCHAR), writeSize, errp) != writeSize)  ERR_SET_OUT(errp, EPIPE);
				else if (data_emit(emit_arg, (u8_t *)p->replace, sizeof(TCHAR), len,	   errp) != len)  ERR_SET_OUT(errp, EPIPE);
			}
			cp = leadout + leadOutSize;							// move cp = {leadout} + len(leadout)
		}
	}

	if (errp->code == 0 && (len = Dz1STRLEN(cp)) > 0)
	{	// flush remains
		if (data_emit(emit_arg, (u8_t*)cp, sizeof(TCHAR), len, errp) != len) // modified by gm 20230602 - type casting cp to u8_t*
			ERR_SET_OUT(errp, EPIPE);
		else Dz1Error_set(errp, 0);
	}

	return errp->code == 0 ? TRUE : FALSE;
}
// Replace Core Function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Execute Replace to FILE Stream
static ssize_t _fp_write(void *ptr, u8_t *data, size_t unit_size, size_t cnt, Dz1Error *err)
{
	// DZ1_ERROR_SAFE_PTR(errp, err); // modified by gm 20230602 - unused err
	FILE *fp = (FILE *)ptr;
	size_t sz = fwrite((void *)data, unit_size, cnt, fp);
	return (ssize_t)sz;
}

bool_t TxtReplaceEnv_do(TxtReplaceEnv *env, FILE *dst, str_t src[], Dz1GenTextMode txt_mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	while(errp->code == 0 && *src != NULL)
	{
		if (txt_replace(env, *src, _fp_write, dst, errp) == FALSE) ERR_OUT(errp);
		else
		{
			_lf(dst, txt_mode);
			src++;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Execute Replace to FILE Stream
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Execute Replace to Elastic Buffer
static ssize_t _elb_write(void *ptr, u8_t *data, size_t unit_size, size_t cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *dst = (Dz1ElasticBuf *)ptr;
	size_t byte_size = unit_size * cnt;
	if ((*errp = Dz1ElasticBuf_push(dst, data, byte_size)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? (ssize_t)cnt : -1;
}

bool_t TxtReplaceEnv_doElb(TxtReplaceEnv *env, Dz1ElasticBuf *dst, str_t src[], Dz1GenTextMode txt_mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str CRLF = NULL;
	switch(txt_mode)
	{
	default:
	case Dz1GenTextMode_DOS:	CRLF = Dz1T("\r\n"); break;
	case Dz1GenTextMode_UNIX:	CRLF = Dz1T("\n");	 break;
	}

	while(errp->code == 0 && *src != NULL)
	{
		if (txt_replace(env, *src, _elb_write, dst, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1ElasticBuf_pushStr(dst, CRLF, errp) == FALSE) ERR_OUT(errp);
		else src++;
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Execute Replace to Elastic Buffer
///////////////////////////////////////////////////////////////////////////////
