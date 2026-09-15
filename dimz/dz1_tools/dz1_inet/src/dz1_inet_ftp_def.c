////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCmdResult
static struct Dz1InetFtpCmdResultMapA
{
	str_t str;
	Dz1InetFtpCmdResult v;
} Dz1InetFtpCmdResultMapA[] =
{
	{ (char *)"success", Dz1InetFtpCmdResult_success },
	{ (char *)"omitted", Dz1InetFtpCmdResult_omitted },
	{ (char *)"serviceNotReady", Dz1InetFtpCmdResult_serviceNotReady },
	{ (char *)"serverBusy", Dz1InetFtpCmdResult_serverBusy },
	{ (char *)"serverFail", Dz1InetFtpCmdResult_serverFail },
	{ (char *)"authFail", Dz1InetFtpCmdResult_authFail },
	{ (char *)"fileNotFound", Dz1InetFtpCmdResult_fileNotFound },
	{ (char *)"pathNotFound", Dz1InetFtpCmdResult_pathNotFound },
	{ (char *)"transferFail", Dz1InetFtpCmdResult_transferFail },
	{ (char *)"unknown", Dz1InetFtpCmdResult_unknown },
	{ (char *)"noPermission", Dz1InetFtpCmdResult_noPermission },
	{ NULL, Dz1InetFtpCmdResult_max }
};

str_t Dz1InetFtpCmdResultStrA(Dz1InetFtpCmdResult v)
{
	struct Dz1InetFtpCmdResultMapA *i = NULL;
	for (i = Dz1InetFtpCmdResultMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpCmdResult Dz1InetFtpCmdResultFromStrA(str_t str)
{
	struct Dz1InetFtpCmdResultMapA *i = NULL;
	for (i = Dz1InetFtpCmdResultMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpCmdResult_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpCmdResultMapW
{
	wstr_t str;
	Dz1InetFtpCmdResult v;
} Dz1InetFtpCmdResultMapW[] =
{
	{ (wchar_t *)L"success", Dz1InetFtpCmdResult_success },
	{ (wchar_t *)L"omitted", Dz1InetFtpCmdResult_omitted },
	{ (wchar_t *)L"serviceNotReady", Dz1InetFtpCmdResult_serviceNotReady },
	{ (wchar_t *)L"serverBusy", Dz1InetFtpCmdResult_serverBusy },
	{ (wchar_t *)L"serverFail", Dz1InetFtpCmdResult_serverFail },
	{ (wchar_t *)L"authFail", Dz1InetFtpCmdResult_authFail },
	{ (wchar_t *)L"fileNotFound", Dz1InetFtpCmdResult_fileNotFound },
	{ (wchar_t *)L"pathNotFound", Dz1InetFtpCmdResult_pathNotFound },
	{ (wchar_t *)L"transferFail", Dz1InetFtpCmdResult_transferFail },
	{ (wchar_t *)L"unknown", Dz1InetFtpCmdResult_unknown },
	{ (wchar_t *)L"noPermission", Dz1InetFtpCmdResult_noPermission },
	{ NULL, Dz1InetFtpCmdResult_max }
};

wstr_t Dz1InetFtpCmdResultStrW(Dz1InetFtpCmdResult v)
{
	struct Dz1InetFtpCmdResultMapW *i = NULL;
	for (i = Dz1InetFtpCmdResultMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpCmdResult Dz1InetFtpCmdResultFromStrW(wstr_t str)
{
	struct Dz1InetFtpCmdResultMapW *i = NULL;
	for (i = Dz1InetFtpCmdResultMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpCmdResult_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpCmdResult *Dz1InetFtpCmdResult_new(Dz1InetFtpCmdResult *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpCmdResult *__internal_ret = (Dz1InetFtpCmdResult *)Dz1Calloc(sizeof(Dz1InetFtpCmdResult), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetFtpCmdResult
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpFileName
Dz1InetFtpFileName *Dz1InetFtpFileName_new(str_t path, str_t name, u32_t size, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpFileName *__internal_ret = (Dz1InetFtpFileName *)Dz1Calloc(sizeof(Dz1InetFtpFileName), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpFileName_delAndSetNull, (void *)&__internal_ret);
		
		if (path && (__internal_ret->path = dz1_built_in_str_clone(path, errp)) == NULL) ERR_OUT(errp);
		else if (name && (__internal_ret->name = dz1_built_in_str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->size = size;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpFileName_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1InetFtpFileName_copy(Dz1InetFtpFileName *dst, Dz1InetFtpFileName *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->path && (dst->path = dz1_built_in_str_clone(src->path, errp)) == NULL) ERR_OUT(errp);
	else if (src->name && (dst->name = dz1_built_in_str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->size = src->size;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1InetFtpFileName *Dz1InetFtpFileName_clone(Dz1InetFtpFileName *src, Dz1Error *err)
{
	Dz1InetFtpFileName *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1InetFtpFileName *)Dz1Calloc(sizeof(Dz1InetFtpFileName), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpFileName_delAndSetNull, (void *)&dst);
		if (Dz1InetFtpFileName_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpFileName_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1InetFtpFileName_purge(Dz1InetFtpFileName *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->path);
	dz1_built_in_str_del(p->name);
}

void Dz1InetFtpFileName_del(Dz1InetFtpFileName *p)
{
	if (p == NULL) return;
	Dz1InetFtpFileName_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpFileName_dump(Dz1InetFtpFileName *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("path = ")); dz1_built_in_str_dump(p->path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("name = ")); dz1_built_in_str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("size = ")); Dz1u32_dump(&p->size, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1InetFtpFileName_cmp(Dz1InetFtpFileName *a, Dz1InetFtpFileName *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->path == NULL && b->path == NULL) ret = 0;
	else if (a->path == NULL /*&& b->path != NULL*/) ret = -1;
	else if (/*a->path != NULL &&*/ b->path == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->path, b->path)) != 0) { }
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->name, b->name)) != 0) { }
	return ret;
}
// Dz1InetFtpFileName
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpFileInfoPresent
static struct Dz1InetFtpFileInfoPresentMapA
{
	str_t str;
	Dz1InetFtpFileInfoPresent v;
} Dz1InetFtpFileInfoPresentMapA[] =
{
	{ (char *)"file", Dz1InetFtpFileInfoPresent_file },
	{ (char *)"buffer", Dz1InetFtpFileInfoPresent_buffer },
	{ NULL, Dz1InetFtpFileInfoPresent_max }
};

str_t Dz1InetFtpFileInfoPresentStrA(Dz1InetFtpFileInfoPresent v)
{
	struct Dz1InetFtpFileInfoPresentMapA *i = NULL;
	for (i = Dz1InetFtpFileInfoPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpFileInfoPresent Dz1InetFtpFileInfoPresentFromStrA(str_t str)
{
	struct Dz1InetFtpFileInfoPresentMapA *i = NULL;
	for (i = Dz1InetFtpFileInfoPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpFileInfoPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpFileInfoPresentMapW
{
	wstr_t str;
	Dz1InetFtpFileInfoPresent v;
} Dz1InetFtpFileInfoPresentMapW[] =
{
	{ (wchar_t *)L"file", Dz1InetFtpFileInfoPresent_file },
	{ (wchar_t *)L"buffer", Dz1InetFtpFileInfoPresent_buffer },
	{ NULL, Dz1InetFtpFileInfoPresent_max }
};

wstr_t Dz1InetFtpFileInfoPresentStrW(Dz1InetFtpFileInfoPresent v)
{
	struct Dz1InetFtpFileInfoPresentMapW *i = NULL;
	for (i = Dz1InetFtpFileInfoPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpFileInfoPresent Dz1InetFtpFileInfoPresentFromStrW(wstr_t str)
{
	struct Dz1InetFtpFileInfoPresentMapW *i = NULL;
	for (i = Dz1InetFtpFileInfoPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpFileInfoPresent_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpFileInfoPresent *Dz1InetFtpFileInfoPresent_new(Dz1InetFtpFileInfoPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpFileInfoPresent *__internal_ret = (Dz1InetFtpFileInfoPresent *)Dz1Calloc(sizeof(Dz1InetFtpFileInfoPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1InetFtpFileInfoPresent_dump(Dz1InetFtpFileInfoPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1InetFtpFileInfoPresentStr(*v));
}
// Dz1InetFtpFileInfoPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpFileInfo
Dz1InetFtpFileInfo *Dz1InetFtpFileInfo_new(Dz1InetFtpFileInfoPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpFileInfo *ret = (Dz1InetFtpFileInfo *)Dz1Calloc(sizeof(Dz1InetFtpFileInfo), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpFileInfo_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1InetFtpFileInfoPresent_file:
			// _U_cst_clone
			if (ptr != NULL) ret->x.file = (Dz1InetFtpFileName *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpFileInfoPresent_buffer:
			// _U_imp_clone
			if (ptr != NULL) ret->x.buffer = (Dz1Binary *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpFileInfoPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpFileInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1InetFtpFileInfo_copy(Dz1InetFtpFileInfo *ret, Dz1InetFtpFileInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1InetFtpFileInfoPresent_file:
			// _U_cst_clone
			if (src->x.file && (ret->x.file = Dz1InetFtpFileName_clone(src->x.file, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpFileInfoPresent_buffer:
			// _U_imp_clone
			if (src->x.buffer && (ret->x.buffer = Dz1Binary_clone(src->x.buffer, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1InetFtpFileInfo *Dz1InetFtpFileInfo_clone(Dz1InetFtpFileInfo *src, Dz1Error *err)
{
	Dz1InetFtpFileInfo *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1InetFtpFileInfo *)Dz1Calloc(sizeof(Dz1InetFtpFileInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpFileInfo_delAndSetNull, (void *)&ret);
		if (Dz1InetFtpFileInfo_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpFileInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetFtpFileInfo_purge(Dz1InetFtpFileInfo *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1InetFtpFileInfoPresent_file:
		Dz1InetFtpFileName_del(p->x.file);
		break;
	case Dz1InetFtpFileInfoPresent_buffer:
		Dz1Binary_del(p->x.buffer);
		break;
	default:
		break;
	}
}

void Dz1InetFtpFileInfo_del(Dz1InetFtpFileInfo *p)
{
	if (!p) return;
	Dz1InetFtpFileInfo_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpFileInfo_dump(Dz1InetFtpFileInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1InetFtpFileInfoPresent_file:
		Dz1Thread_printf(Dz1T("file = ")); Dz1InetFtpFileName_dump(p->x.file, tab); 
		break;
	case Dz1InetFtpFileInfoPresent_buffer:
		Dz1Thread_printf(Dz1T("buffer = ")); Dz1Binary_dump(p->x.buffer, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1InetFtpFileInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDirection
static struct Dz1InetFtpDirectionMapA
{
	str_t str;
	Dz1InetFtpDirection v;
} Dz1InetFtpDirectionMapA[] =
{
	{ (char *)"upload", Dz1InetFtpDirection_upload },
	{ (char *)"download", Dz1InetFtpDirection_download },
	{ NULL, Dz1InetFtpDirection_max }
};

str_t Dz1InetFtpDirectionStrA(Dz1InetFtpDirection v)
{
	struct Dz1InetFtpDirectionMapA *i = NULL;
	for (i = Dz1InetFtpDirectionMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDirection Dz1InetFtpDirectionFromStrA(str_t str)
{
	struct Dz1InetFtpDirectionMapA *i = NULL;
	for (i = Dz1InetFtpDirectionMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDirection_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpDirectionMapW
{
	wstr_t str;
	Dz1InetFtpDirection v;
} Dz1InetFtpDirectionMapW[] =
{
	{ (wchar_t *)L"upload", Dz1InetFtpDirection_upload },
	{ (wchar_t *)L"download", Dz1InetFtpDirection_download },
	{ NULL, Dz1InetFtpDirection_max }
};

wstr_t Dz1InetFtpDirectionStrW(Dz1InetFtpDirection v)
{
	struct Dz1InetFtpDirectionMapW *i = NULL;
	for (i = Dz1InetFtpDirectionMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDirection Dz1InetFtpDirectionFromStrW(wstr_t str)
{
	struct Dz1InetFtpDirectionMapW *i = NULL;
	for (i = Dz1InetFtpDirectionMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDirection_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpDirection *Dz1InetFtpDirection_new(Dz1InetFtpDirection *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpDirection *__internal_ret = (Dz1InetFtpDirection *)Dz1Calloc(sizeof(Dz1InetFtpDirection), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetFtpDirection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTransfer
Dz1InetFtpTransfer *Dz1InetFtpTransfer_new(Dz1InetFtpDirection direction, 
										   Dz1InetFtpFileName *remote, 
										   Dz1InetFtpFileInfo *local, 
										   bool_t overwrite, 
										   void *userKey, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpTransfer *__internal_ret = (Dz1InetFtpTransfer *)Dz1Calloc(sizeof(Dz1InetFtpTransfer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpTransfer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->direction = direction;
		__internal_ret->remote = remote;
		__internal_ret->local = local;
		__internal_ret->overwrite = overwrite;
		__internal_ret->userKey = userKey;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpTransfer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1InetFtpTransfer_copy(Dz1InetFtpTransfer *dst, Dz1InetFtpTransfer *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->remote && (dst->remote = Dz1InetFtpFileName_clone(src->remote, errp)) == NULL) ERR_OUT(errp);
	else if (src->local && (dst->local = Dz1InetFtpFileInfo_clone(src->local, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->direction = src->direction;
		dst->overwrite = src->overwrite;
		dst->result = src->result;
		dst->userKey = src->userKey;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1InetFtpTransfer *Dz1InetFtpTransfer_clone(Dz1InetFtpTransfer *src, Dz1Error *err)
{
	Dz1InetFtpTransfer *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1InetFtpTransfer *)Dz1Calloc(sizeof(Dz1InetFtpTransfer), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpTransfer_delAndSetNull, (void *)&dst);
		if (Dz1InetFtpTransfer_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpTransfer_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1InetFtpTransfer_purge(Dz1InetFtpTransfer *p)
{
	if (p == NULL) return;
	Dz1InetFtpFileName_del(p->remote);
	Dz1InetFtpFileInfo_del(p->local);
}

void Dz1InetFtpTransfer_del(Dz1InetFtpTransfer *p)
{
	if (p == NULL) return;
	Dz1InetFtpTransfer_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpTransfer_dump(Dz1InetFtpTransfer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("direction = %s(%d)\n"), Dz1InetFtpDirectionStr(p->direction), p->direction);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("remote = ")); Dz1InetFtpFileName_dump(p->remote, tab); 
		Dz1Thread_tprintf(tab, Dz1T("local.")); Dz1InetFtpFileInfo_dump(p->local, tab); 
		Dz1Thread_tprintf(tab, Dz1T("overwrite = ")); Dz1Bool_dump(&p->overwrite, tab); 
		Dz1Thread_tprintf(tab, Dz1T("result = %s(%d)\n"), Dz1InetFtpCmdResultStr(p->result), p->result);
		Dz1Thread_tprintf(tab, Dz1T("userKey = %p\n"), p->userKey);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1InetFtpTransfer_cmp(Dz1InetFtpTransfer *a, Dz1InetFtpTransfer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = (int)(a->direction - b->direction)) != 0) { }
	else if (a->remote == NULL && b->remote == NULL) ret = 0;
	else if (a->remote == NULL /*&& b->remote != NULL*/) ret = -1;
	else if (/*a->remote != NULL &&*/ b->remote == NULL) ret = 1;
	else if ((ret = Dz1InetFtpFileName_cmp(a->remote, b->remote)) != 0) { }
	return ret;
}
// Dz1InetFtpTransfer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTransferList
static Dz1Error Dz1InetFtpTransferList_add(Dz1InetFtpTransferList *p, Dz1InetFtpTransfer *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1InetFtpTransferListMkArrArg
{
	Dz1InetFtpTransfer **arr;
	unsigned int idx;
} Dz1InetFtpTransferListMkArrArg;

static Dz1Error _Dz1InetFtpTransferList_get_array(void *ptr, Dz1InetFtpTransfer *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpTransferListMkArrArg *arg = (Dz1InetFtpTransferListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1InetFtpTransfer **Dz1InetFtpTransferList_get_array(Dz1InetFtpTransferList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1InetFtpTransfer **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1InetFtpTransfer **)Dz1Calloc(sizeof(Dz1InetFtpTransfer *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1InetFtpTransferListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1InetFtpTransferList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error Dz1InetFtpTransferList_travelForward(Dz1InetFtpTransferList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpTransfer *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1InetFtpTransferList_travelBackward(Dz1InetFtpTransferList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpTransfer *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1InetFtpTransferList_count(Dz1InetFtpTransferList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1InetFtpTransferList *Dz1InetFtpTransferList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpTransferList *ret = (Dz1InetFtpTransferList *)Dz1Calloc(sizeof(Dz1InetFtpTransferList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpTransferList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1InetFtpTransfer_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1InetFtpTransferList_count;
			ret->travel = Dz1InetFtpTransferList_travelForward;
			ret->travelForward = Dz1InetFtpTransferList_travelForward;
			ret->travelBackward = Dz1InetFtpTransferList_travelBackward;
			ret->get_array = Dz1InetFtpTransferList_get_array;
			ret->add = Dz1InetFtpTransferList_add;
			ret->cmp = Dz1InetFtpTransfer_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpTransferList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1InetFtpTransferList_clone(void *ptr, Dz1InetFtpTransfer *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpTransferList *p = (Dz1InetFtpTransferList *)ptr;
	Dz1InetFtpTransfer *cloned = Dz1InetFtpTransfer_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1InetFtpTransferList *Dz1InetFtpTransferList_clone(Dz1InetFtpTransferList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpTransferList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1InetFtpTransferList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpTransferList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1InetFtpTransferList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpTransferList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetFtpTransferList_purge(Dz1InetFtpTransferList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1InetFtpTransferList_del(Dz1InetFtpTransferList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1InetFtpTransferList_dump(void *ptr, Dz1InetFtpTransfer *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1InetFtpTransfer_dump(p, tab);
	return err;
}

void Dz1InetFtpTransferList_dump(Dz1InetFtpTransferList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1InetFtpTransferList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpTransferList
////////////////////////////////////////////////////////////////////////////////

