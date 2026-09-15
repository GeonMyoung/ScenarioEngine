////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_fsm_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpState
static struct Dz1InetFtpStateMapA
{
	str_t str;
	Dz1InetFtpState v;
} Dz1InetFtpStateMapA[] =
{
	{ (char *)"initial", Dz1InetFtpState_initial },
	{ (char *)"sentUSER", Dz1InetFtpState_sentUSER },
	{ (char *)"sentPASS", Dz1InetFtpState_sentPASS },
	{ (char *)"sentACCT", Dz1InetFtpState_sentACCT },
	{ (char *)"sentTYPE", Dz1InetFtpState_sentTYPE },
	{ (char *)"sentCWDd", Dz1InetFtpState_sentCWDd },
	{ (char *)"sentPASVPORT", Dz1InetFtpState_sentPASVPORT },
	{ (char *)"sentRETRSTOR", Dz1InetFtpState_sentRETRSTOR },
	{ (char *)"waitANY", Dz1InetFtpState_waitANY },
	{ (char *)"sentCWDu", Dz1InetFtpState_sentCWDu },
	{ (char *)"sentMKD", Dz1InetFtpState_sentMKD },
	{ (char *)"sentCWDs", Dz1InetFtpState_sentCWDs },
	{ (char *)"sentSIZE", Dz1InetFtpState_sentSIZE },
	{ (char *)"waitDTP", Dz1InetFtpState_waitDTP },
	{ (char *)"waitDONE", Dz1InetFtpState_waitDONE },
	{ (char *)"sentFEAT", Dz1InetFtpState_sentFEAT },
	{ NULL, Dz1InetFtpState_max }
};

str_t Dz1InetFtpStateStrA(Dz1InetFtpState v)
{
	struct Dz1InetFtpStateMapA *i = NULL;
	for (i = Dz1InetFtpStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpState Dz1InetFtpStateFromStrA(str_t str)
{
	struct Dz1InetFtpStateMapA *i = NULL;
	for (i = Dz1InetFtpStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpStateMapW
{
	wstr_t str;
	Dz1InetFtpState v;
} Dz1InetFtpStateMapW[] =
{
	{ (wchar_t *)L"initial", Dz1InetFtpState_initial },
	{ (wchar_t *)L"sentUSER", Dz1InetFtpState_sentUSER },
	{ (wchar_t *)L"sentPASS", Dz1InetFtpState_sentPASS },
	{ (wchar_t *)L"sentACCT", Dz1InetFtpState_sentACCT },
	{ (wchar_t *)L"sentTYPE", Dz1InetFtpState_sentTYPE },
	{ (wchar_t *)L"sentCWDd", Dz1InetFtpState_sentCWDd },
	{ (wchar_t *)L"sentPASVPORT", Dz1InetFtpState_sentPASVPORT },
	{ (wchar_t *)L"sentRETRSTOR", Dz1InetFtpState_sentRETRSTOR },
	{ (wchar_t *)L"waitANY", Dz1InetFtpState_waitANY },
	{ (wchar_t *)L"sentCWDu", Dz1InetFtpState_sentCWDu },
	{ (wchar_t *)L"sentMKD", Dz1InetFtpState_sentMKD },
	{ (wchar_t *)L"sentCWDs", Dz1InetFtpState_sentCWDs },
	{ (wchar_t *)L"sentSIZE", Dz1InetFtpState_sentSIZE },
	{ (wchar_t *)L"waitDTP", Dz1InetFtpState_waitDTP },
	{ (wchar_t *)L"waitDONE", Dz1InetFtpState_waitDONE },
	{ (wchar_t *)L"sentFEAT", Dz1InetFtpState_sentFEAT },
	{ NULL, Dz1InetFtpState_max }
};

wstr_t Dz1InetFtpStateStrW(Dz1InetFtpState v)
{
	struct Dz1InetFtpStateMapW *i = NULL;
	for (i = Dz1InetFtpStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpState Dz1InetFtpStateFromStrW(wstr_t str)
{
	struct Dz1InetFtpStateMapW *i = NULL;
	for (i = Dz1InetFtpStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpState_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpState *Dz1InetFtpState_new(Dz1InetFtpState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpState *__internal_ret = (Dz1InetFtpState *)Dz1Calloc(sizeof(Dz1InetFtpState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetFtpState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpEvent
static struct Dz1InetFtpEventMapA
{
	str_t str;
	Dz1InetFtpEvent v;
} Dz1InetFtpEventMapA[] =
{
	{ (char *)"prepare", Dz1InetFtpEvent_prepare },
	{ (char *)"success", Dz1InetFtpEvent_success },
	{ (char *)"andNext", Dz1InetFtpEvent_andNext },
	{ (char *)"error", Dz1InetFtpEvent_error },
	{ (char *)"transferDone", Dz1InetFtpEvent_transferDone },
	{ NULL, Dz1InetFtpEvent_max }
};

str_t Dz1InetFtpEventStrA(Dz1InetFtpEvent v)
{
	struct Dz1InetFtpEventMapA *i = NULL;
	for (i = Dz1InetFtpEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpEvent Dz1InetFtpEventFromStrA(str_t str)
{
	struct Dz1InetFtpEventMapA *i = NULL;
	for (i = Dz1InetFtpEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpEvent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpEventMapW
{
	wstr_t str;
	Dz1InetFtpEvent v;
} Dz1InetFtpEventMapW[] =
{
	{ (wchar_t *)L"prepare", Dz1InetFtpEvent_prepare },
	{ (wchar_t *)L"success", Dz1InetFtpEvent_success },
	{ (wchar_t *)L"andNext", Dz1InetFtpEvent_andNext },
	{ (wchar_t *)L"error", Dz1InetFtpEvent_error },
	{ (wchar_t *)L"transferDone", Dz1InetFtpEvent_transferDone },
	{ NULL, Dz1InetFtpEvent_max }
};

wstr_t Dz1InetFtpEventStrW(Dz1InetFtpEvent v)
{
	struct Dz1InetFtpEventMapW *i = NULL;
	for (i = Dz1InetFtpEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpEvent Dz1InetFtpEventFromStrW(wstr_t str)
{
	struct Dz1InetFtpEventMapW *i = NULL;
	for (i = Dz1InetFtpEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpEvent_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpEvent *Dz1InetFtpEvent_new(Dz1InetFtpEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpEvent *__internal_ret = (Dz1InetFtpEvent *)Dz1Calloc(sizeof(Dz1InetFtpEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetFtpEvent
////////////////////////////////////////////////////////////////////////////////

