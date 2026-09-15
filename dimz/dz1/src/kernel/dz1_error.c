#include <dz1.h>
#ifndef MAC_OS_X
#include <malloc.h>
#endif
#include "dz1_thread.h"
#include "dz1_thread_stdio.h"
#include <dz1_error.h>
#include <dz1_str.h>
#include <dz1_socket.h>
#include "dz1_console.h"

///////////////////////////////////////////////////////////////////////////////
// Error String
static struct Dz1ErrorStrMapA
{
	int code;
	str_t str;
} Dz1ErrorStrMapA[] =
{
#ifdef WIN32
	{ ETIMEDOUT,				(str_t)"timeout" },
	{ ECONNREFUSED,				(str_t)"connection refused" },
	{ WSAECONNRESET,			(str_t)"connection reset" },
	{ ERROR_NETNAME_DELETED,	(str_t)"network name is deleted" },
	{ ERROR_CONNECTION_ABORTED, (str_t)"network connection was aborted" },
	{ HOST_NOT_FOUND,			(str_t)"host not found" },
#endif
	{ -1, NULL }
};

str_t Dz1ErrorStrA(int code)
{
	struct Dz1ErrorStrMapA *i;
	for (i = Dz1ErrorStrMapA; i->str != NULL; i++)
		if (i->code == code) return i->str;
	return strerror(code);
}
#ifndef UNIX_SYSTEM
static struct Dz1ErrorStrMapW
{
	int code;
	wstr_t str;
} Dz1ErrorStrMapW[] =
{
#ifdef WIN32
	{ ETIMEDOUT,				(wstr_t)L"timeout" },
	{ ECONNREFUSED,				(wstr_t)L"connection refused" },
	{ WSAECONNRESET,			(wstr_t)L"connection reset" },
	{ ERROR_NETNAME_DELETED,	(wstr_t)L"network name is deleted" },
	{ ERROR_CONNECTION_ABORTED, (wstr_t)L"network connection was aborted" },
	{ HOST_NOT_FOUND,			(wstr_t)L"host not found" },
#endif
	{ -1, NULL }
};
wstr_t Dz1ErrorStrW(int code)
{
	struct Dz1ErrorStrMapW *i;
	for (i = Dz1ErrorStrMapW; i->str != NULL; i++)
		if (i->code == code) return i->str;
	return _wcserror(code);
}
#endif
// Error String
///////////////////////////////////////////////////////////////////////////////

Dz1Error *_Dz1Error_set(Dz1Error *err, int error_code, const char *file, int line)
{
	if (err)
	{
		err->code = error_code;
#ifndef UNIX_SYSTEM
		snprintf(err->comment, DZ1_ERROR_COMMENT_LEN, "%s:%d", basenameA((char *)file), line);
#else
		snprintf(err->comment, DZ1_ERROR_COMMENT_LEN, "%s:%d", file, line);
#endif
		err->comment[DZ1_ERROR_COMMENT_LEN - 1] = '\0';
	}
	return err;
}

void _Dz1Error_setWithComment(Dz1Error *err, int error_code, const char *file, int line, const char *comment)
{
	if (err)
	{
		char *cp = err->comment;
		int len = DZ1_ERROR_COMMENT_LEN, consume;

		err->code = error_code;

#ifndef UNIX_SYSTEM
		consume = snprintf(cp, len, "%s:%d:", basenameA((char *)file), line);
#else
		consume = snprintf(cp, len, "%s:%d:", file, line);
#endif
		cp += consume; len -= consume;
		strncpy(cp, comment, len);
		err->comment[DZ1_ERROR_COMMENT_LEN - 1] = '\0';
	}
}

void _Dz1Error_print(Dz1Error *p, int tab, const char *file, int line)
{
	u32_t lv = 0;
	if (!p) return;
	else if (_Dz1Thread_getLogLevel(Dz1Thread_self(), &lv, NULL) == FALSE) { }
	else if ((lv & DZ1_THREAD_LOG_ERROR) == 0) { }
	else
	{
		char *comment = p->comment;
		if (comment[0] == 0) Dz1Thread_etprintf(tab, "%s(%d) => %s:%d\n", Dz1ErrorStrA(p->code), p->code, basenameA((char *)file), line);
		else Dz1Thread_etprintf(tab, "%s(%d)=%s => %s:%d\n", Dz1ErrorStrA(p->code), p->code, comment, basenameA((char *)file), line);
	}
}

void Dz1ErrorA_dump(Dz1Error *p, int tab)
{
	if (!p) return;
	else
	{
		char *comment = p->comment;
		if (comment[0] == 0) Dz1ThreadA_tprintf(tab, "%s(%d)\n", Dz1ErrorStrA(p->code), p->code);
		else Dz1ThreadA_tprintf(tab, "%s(%d)=%s\n", Dz1ErrorStrA(p->code), p->code, comment);
	}
}
void Dz1ErrorA_fdump(FILE *fp, Dz1Error *p, int tab)
{
	if (!p) return;
	else
	{
		char *comment = p->comment;
		if (comment[0] == '\0') Dz1ThreadA_ftprintf(fp, tab, "%s(%d)\n", Dz1ErrorStrA(p->code), p->code);
		else Dz1ThreadA_ftprintf(fp, tab, "%s(%d)=%s\n", Dz1ErrorStrA(p->code), p->code, comment);
	}
}

#ifndef UNIX_SYSTEM
void Dz1ErrorW_dump(Dz1Error *p, int tab)
{
	if (!p) return;
	{
		if (p->comment[0] == 0) Dz1ThreadW_tprintf(tab, L"%s(%d)\n", Dz1ErrorStrW(p->code), p->code);
		else 
		{
			wchar_t *text = (wchar_t *)Dz1String_conv(p->comment, strlen(p->comment), "UTF-8", DZ1_SYSTEM_WIDE_CHARSET, NULL);
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&text);
			Dz1ThreadW_tprintf(tab, L"%s(%d)=%s\n", Dz1ErrorStrW(p->code), p->code, text);
			pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&text);
		}
	}
}
void Dz1ErrorW_fdump(FILE *fp, Dz1Error *p, int tab)
{
	if (!p) return;
	{
		if (p->comment[0] == 0) Dz1ThreadW_ftprintf(fp, tab, L"%s(%d)\n", Dz1ErrorStrW(p->code), p->code);
		else 
		{
			wchar_t *text = (wchar_t *)Dz1String_conv(p->comment, strlen(p->comment), "UTF-8", DZ1_SYSTEM_WIDE_CHARSET, NULL);
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&text);
			Dz1ThreadW_ftprintf(fp, tab, L"%s(%d)=%s\n", Dz1ErrorStrW(p->code), p->code, text);
			pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&text);
		}
	}
}
#endif

Dz1Error *_Dz1Error_clone(Dz1Error *src, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Error *ret = (Dz1Error *)_Dz1Malloc(sizeof(Dz1Error), errp, __file__, __line__);
	if (ret == NULL) { }
	else memcpy(ret, src, sizeof(Dz1Error));
	return ret;
}

void _Dz1Error_del(Dz1Error *p, const char *__file__, int __line__)
{
	if (p == NULL) return;
	_Dz1Free(p, __file__, __line__);
}
