////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_telnet_msg.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptTerminalTypePresent
static struct Dz1InetTelnetOptTerminalTypePresentMapA
{
	str_t str;
	Dz1InetTelnetOptTerminalTypePresent v;
} Dz1InetTelnetOptTerminalTypePresentMapA[] =
{
	{ (char *)"is", Dz1InetTelnetOptTerminalTypePresent_is },
	{ (char *)"send", Dz1InetTelnetOptTerminalTypePresent_send },
	{ NULL, Dz1InetTelnetOptTerminalTypePresent_max }
};

str_t Dz1InetTelnetOptTerminalTypePresentStrA(Dz1InetTelnetOptTerminalTypePresent v)
{
	struct Dz1InetTelnetOptTerminalTypePresentMapA *i = NULL;
	for (i = Dz1InetTelnetOptTerminalTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetOptTerminalTypePresent Dz1InetTelnetOptTerminalTypePresentFromStrA(str_t str)
{
	struct Dz1InetTelnetOptTerminalTypePresentMapA *i = NULL;
	for (i = Dz1InetTelnetOptTerminalTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetOptTerminalTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetTelnetOptTerminalTypePresentMapW
{
	wstr_t str;
	Dz1InetTelnetOptTerminalTypePresent v;
} Dz1InetTelnetOptTerminalTypePresentMapW[] =
{
	{ (wchar_t *)L"is", Dz1InetTelnetOptTerminalTypePresent_is },
	{ (wchar_t *)L"send", Dz1InetTelnetOptTerminalTypePresent_send },
	{ NULL, Dz1InetTelnetOptTerminalTypePresent_max }
};

wstr_t Dz1InetTelnetOptTerminalTypePresentStrW(Dz1InetTelnetOptTerminalTypePresent v)
{
	struct Dz1InetTelnetOptTerminalTypePresentMapW *i = NULL;
	for (i = Dz1InetTelnetOptTerminalTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetOptTerminalTypePresent Dz1InetTelnetOptTerminalTypePresentFromStrW(wstr_t str)
{
	struct Dz1InetTelnetOptTerminalTypePresentMapW *i = NULL;
	for (i = Dz1InetTelnetOptTerminalTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetOptTerminalTypePresent_max;
}
#endif // UNIX_SYSTEM

Dz1InetTelnetOptTerminalTypePresent *Dz1InetTelnetOptTerminalTypePresent_new(Dz1InetTelnetOptTerminalTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetOptTerminalTypePresent *__internal_ret = (Dz1InetTelnetOptTerminalTypePresent *)Dz1Calloc(sizeof(Dz1InetTelnetOptTerminalTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1InetTelnetOptTerminalTypePresent_dump(Dz1InetTelnetOptTerminalTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1InetTelnetOptTerminalTypePresentStr(*v));
}
// Dz1InetTelnetOptTerminalTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptTerminalType
Dz1InetTelnetOptTerminalType *Dz1InetTelnetOptTerminalType_new(Dz1InetTelnetOptTerminalTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetOptTerminalType *ret = (Dz1InetTelnetOptTerminalType *)Dz1Calloc(sizeof(Dz1InetTelnetOptTerminalType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetTelnetOptTerminalType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1InetTelnetOptTerminalTypePresent_is:
			// _U_prim_clone
			if (ptr && (ret->x.is = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetTelnetOptTerminalTypePresent_send:
			// _U_prim_clone
			if (ptr != NULL) ret->x.send = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptTerminalTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetTelnetOptTerminalType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetTelnetOptTerminalType_purge(Dz1InetTelnetOptTerminalType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1InetTelnetOptTerminalTypePresent_is:
		dz1_built_in_str_del(p->x.is);
		break;
	case Dz1InetTelnetOptTerminalTypePresent_send:
		Dz1u32_del(p->x.send);
		break;
	default:
		break;
	}
}

void Dz1InetTelnetOptTerminalType_del(Dz1InetTelnetOptTerminalType *p)
{
	if (!p) return;
	Dz1InetTelnetOptTerminalType_purge(p);
	Dz1Free(p);
}

void Dz1InetTelnetOptTerminalType_dump(Dz1InetTelnetOptTerminalType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1InetTelnetOptTerminalTypePresent_is:
		Dz1Thread_printf(Dz1T("is = ")); dz1_built_in_str_dump(p->x.is, tab); 
		break;
	case Dz1InetTelnetOptTerminalTypePresent_send:
		Dz1Thread_printf(Dz1T("send = ")); Dz1u32_dump(p->x.send, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1InetTelnetOptTerminalType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptWindowSize
Dz1InetTelnetOptWindowSize *Dz1InetTelnetOptWindowSize_new(u16_t width, 
														   u16_t height, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetOptWindowSize *__internal_ret = (Dz1InetTelnetOptWindowSize *)Dz1Calloc(sizeof(Dz1InetTelnetOptWindowSize), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetTelnetOptWindowSize_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->width = width;
		__internal_ret->height = height;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetTelnetOptWindowSize_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetTelnetOptWindowSize_purge(Dz1InetTelnetOptWindowSize *p)
{
	if (p == NULL) return;
}

void Dz1InetTelnetOptWindowSize_del(Dz1InetTelnetOptWindowSize *p)
{
	if (p == NULL) return;
	Dz1InetTelnetOptWindowSize_purge(p);
	Dz1Free(p);
}

void Dz1InetTelnetOptWindowSize_dump(Dz1InetTelnetOptWindowSize *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("width = ")); Dz1u16_dump(&p->width, tab); 
		Dz1Thread_tprintf(tab, Dz1T("height = ")); Dz1u16_dump(&p->height, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetTelnetOptWindowSize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptPresent
static struct Dz1InetTelnetOptPresentMapA
{
	str_t str;
	Dz1InetTelnetOptPresent v;
} Dz1InetTelnetOptPresentMapA[] =
{
	{ (char *)"binary", Dz1InetTelnetOptPresent_binary },
	{ (char *)"echo", Dz1InetTelnetOptPresent_echo },
	{ (char *)"prepareReconnect", Dz1InetTelnetOptPresent_prepareReconnect },
	{ (char *)"suppressGoAhead", Dz1InetTelnetOptPresent_suppressGoAhead },
	{ (char *)"approximateMsgSize", Dz1InetTelnetOptPresent_approximateMsgSize },
	{ (char *)"status", Dz1InetTelnetOptPresent_status },
	{ (char *)"timingMark", Dz1InetTelnetOptPresent_timingMark },
	{ (char *)"rcTxAndEcho", Dz1InetTelnetOptPresent_rcTxAndEcho },
	{ (char *)"lineWidth", Dz1InetTelnetOptPresent_lineWidth },
	{ (char *)"pageSize", Dz1InetTelnetOptPresent_pageSize },
	{ (char *)"crDisposition", Dz1InetTelnetOptPresent_crDisposition },
	{ (char *)"hTabStop", Dz1InetTelnetOptPresent_hTabStop },
	{ (char *)"hTabDisposition", Dz1InetTelnetOptPresent_hTabDisposition },
	{ (char *)"formFeedDisposition", Dz1InetTelnetOptPresent_formFeedDisposition },
	{ (char *)"vTabStop", Dz1InetTelnetOptPresent_vTabStop },
	{ (char *)"vTabDisposition", Dz1InetTelnetOptPresent_vTabDisposition },
	{ (char *)"lfDisposition", Dz1InetTelnetOptPresent_lfDisposition },
	{ (char *)"xAscii", Dz1InetTelnetOptPresent_xAscii },
	{ (char *)"forceLogout", Dz1InetTelnetOptPresent_forceLogout },
	{ (char *)"byteMacro", Dz1InetTelnetOptPresent_byteMacro },
	{ (char *)"dataEntryTerminal", Dz1InetTelnetOptPresent_dataEntryTerminal },
	{ (char *)"supdupProtocol", Dz1InetTelnetOptPresent_supdupProtocol },
	{ (char *)"supdupOutput", Dz1InetTelnetOptPresent_supdupOutput },
	{ (char *)"sendLocation", Dz1InetTelnetOptPresent_sendLocation },
	{ (char *)"terminalType", Dz1InetTelnetOptPresent_terminalType },
	{ (char *)"endOfRecord", Dz1InetTelnetOptPresent_endOfRecord },
	{ (char *)"tacacsUserID", Dz1InetTelnetOptPresent_tacacsUserID },
	{ (char *)"OutputMarking", Dz1InetTelnetOptPresent_OutputMarking },
	{ (char *)"ttyNumber", Dz1InetTelnetOptPresent_ttyNumber },
	{ (char *)"regime3270", Dz1InetTelnetOptPresent_regime3270 },
	{ (char *)"xDot3Pad", Dz1InetTelnetOptPresent_xDot3Pad },
	{ (char *)"windowSize", Dz1InetTelnetOptPresent_windowSize },
	{ (char *)"terminalSpeed", Dz1InetTelnetOptPresent_terminalSpeed },
	{ (char *)"remoteFlowControl", Dz1InetTelnetOptPresent_remoteFlowControl },
	{ (char *)"lineMode", Dz1InetTelnetOptPresent_lineMode },
	{ (char *)"xDispLoc", Dz1InetTelnetOptPresent_xDispLoc },
	{ (char *)"oldEnvs", Dz1InetTelnetOptPresent_oldEnvs },
	{ (char *)"auth", Dz1InetTelnetOptPresent_auth },
	{ (char *)"encryption", Dz1InetTelnetOptPresent_encryption },
	{ (char *)"newEnvs", Dz1InetTelnetOptPresent_newEnvs },
	{ (char *)"extOptList", Dz1InetTelnetOptPresent_extOptList },
	{ NULL, Dz1InetTelnetOptPresent_max }
};

str_t Dz1InetTelnetOptPresentStrA(Dz1InetTelnetOptPresent v)
{
	struct Dz1InetTelnetOptPresentMapA *i = NULL;
	for (i = Dz1InetTelnetOptPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetOptPresent Dz1InetTelnetOptPresentFromStrA(str_t str)
{
	struct Dz1InetTelnetOptPresentMapA *i = NULL;
	for (i = Dz1InetTelnetOptPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetOptPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetTelnetOptPresentMapW
{
	wstr_t str;
	Dz1InetTelnetOptPresent v;
} Dz1InetTelnetOptPresentMapW[] =
{
	{ (wchar_t *)L"binary", Dz1InetTelnetOptPresent_binary },
	{ (wchar_t *)L"echo", Dz1InetTelnetOptPresent_echo },
	{ (wchar_t *)L"prepareReconnect", Dz1InetTelnetOptPresent_prepareReconnect },
	{ (wchar_t *)L"suppressGoAhead", Dz1InetTelnetOptPresent_suppressGoAhead },
	{ (wchar_t *)L"approximateMsgSize", Dz1InetTelnetOptPresent_approximateMsgSize },
	{ (wchar_t *)L"status", Dz1InetTelnetOptPresent_status },
	{ (wchar_t *)L"timingMark", Dz1InetTelnetOptPresent_timingMark },
	{ (wchar_t *)L"rcTxAndEcho", Dz1InetTelnetOptPresent_rcTxAndEcho },
	{ (wchar_t *)L"lineWidth", Dz1InetTelnetOptPresent_lineWidth },
	{ (wchar_t *)L"pageSize", Dz1InetTelnetOptPresent_pageSize },
	{ (wchar_t *)L"crDisposition", Dz1InetTelnetOptPresent_crDisposition },
	{ (wchar_t *)L"hTabStop", Dz1InetTelnetOptPresent_hTabStop },
	{ (wchar_t *)L"hTabDisposition", Dz1InetTelnetOptPresent_hTabDisposition },
	{ (wchar_t *)L"formFeedDisposition", Dz1InetTelnetOptPresent_formFeedDisposition },
	{ (wchar_t *)L"vTabStop", Dz1InetTelnetOptPresent_vTabStop },
	{ (wchar_t *)L"vTabDisposition", Dz1InetTelnetOptPresent_vTabDisposition },
	{ (wchar_t *)L"lfDisposition", Dz1InetTelnetOptPresent_lfDisposition },
	{ (wchar_t *)L"xAscii", Dz1InetTelnetOptPresent_xAscii },
	{ (wchar_t *)L"forceLogout", Dz1InetTelnetOptPresent_forceLogout },
	{ (wchar_t *)L"byteMacro", Dz1InetTelnetOptPresent_byteMacro },
	{ (wchar_t *)L"dataEntryTerminal", Dz1InetTelnetOptPresent_dataEntryTerminal },
	{ (wchar_t *)L"supdupProtocol", Dz1InetTelnetOptPresent_supdupProtocol },
	{ (wchar_t *)L"supdupOutput", Dz1InetTelnetOptPresent_supdupOutput },
	{ (wchar_t *)L"sendLocation", Dz1InetTelnetOptPresent_sendLocation },
	{ (wchar_t *)L"terminalType", Dz1InetTelnetOptPresent_terminalType },
	{ (wchar_t *)L"endOfRecord", Dz1InetTelnetOptPresent_endOfRecord },
	{ (wchar_t *)L"tacacsUserID", Dz1InetTelnetOptPresent_tacacsUserID },
	{ (wchar_t *)L"OutputMarking", Dz1InetTelnetOptPresent_OutputMarking },
	{ (wchar_t *)L"ttyNumber", Dz1InetTelnetOptPresent_ttyNumber },
	{ (wchar_t *)L"regime3270", Dz1InetTelnetOptPresent_regime3270 },
	{ (wchar_t *)L"xDot3Pad", Dz1InetTelnetOptPresent_xDot3Pad },
	{ (wchar_t *)L"windowSize", Dz1InetTelnetOptPresent_windowSize },
	{ (wchar_t *)L"terminalSpeed", Dz1InetTelnetOptPresent_terminalSpeed },
	{ (wchar_t *)L"remoteFlowControl", Dz1InetTelnetOptPresent_remoteFlowControl },
	{ (wchar_t *)L"lineMode", Dz1InetTelnetOptPresent_lineMode },
	{ (wchar_t *)L"xDispLoc", Dz1InetTelnetOptPresent_xDispLoc },
	{ (wchar_t *)L"oldEnvs", Dz1InetTelnetOptPresent_oldEnvs },
	{ (wchar_t *)L"auth", Dz1InetTelnetOptPresent_auth },
	{ (wchar_t *)L"encryption", Dz1InetTelnetOptPresent_encryption },
	{ (wchar_t *)L"newEnvs", Dz1InetTelnetOptPresent_newEnvs },
	{ (wchar_t *)L"extOptList", Dz1InetTelnetOptPresent_extOptList },
	{ NULL, Dz1InetTelnetOptPresent_max }
};

wstr_t Dz1InetTelnetOptPresentStrW(Dz1InetTelnetOptPresent v)
{
	struct Dz1InetTelnetOptPresentMapW *i = NULL;
	for (i = Dz1InetTelnetOptPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetOptPresent Dz1InetTelnetOptPresentFromStrW(wstr_t str)
{
	struct Dz1InetTelnetOptPresentMapW *i = NULL;
	for (i = Dz1InetTelnetOptPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetOptPresent_max;
}
#endif // UNIX_SYSTEM

Dz1InetTelnetOptPresent *Dz1InetTelnetOptPresent_new(Dz1InetTelnetOptPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetOptPresent *__internal_ret = (Dz1InetTelnetOptPresent *)Dz1Calloc(sizeof(Dz1InetTelnetOptPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1InetTelnetOptPresent_dump(Dz1InetTelnetOptPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1InetTelnetOptPresentStr(*v));
}
// Dz1InetTelnetOptPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOpt
Dz1InetTelnetOpt *Dz1InetTelnetOpt_new(Dz1InetTelnetOptPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetOpt *ret = (Dz1InetTelnetOpt *)Dz1Calloc(sizeof(Dz1InetTelnetOpt), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetTelnetOpt_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1InetTelnetOptPresent_binary:
			// _U_prim_clone
			if (ptr != NULL) ret->x.binary = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_echo:
			// _U_prim_clone
			if (ptr != NULL) ret->x.echo = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_prepareReconnect:
			// _U_prim_clone
			if (ptr != NULL) ret->x.prepareReconnect = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_suppressGoAhead:
			// _U_prim_clone
			if (ptr != NULL) ret->x.suppressGoAhead = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_approximateMsgSize:
			// _U_prim_clone
			if (ptr != NULL) ret->x.approximateMsgSize = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_status:
			// _U_prim_clone
			if (ptr != NULL) ret->x.status = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_timingMark:
			// _U_prim_clone
			if (ptr != NULL) ret->x.timingMark = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_rcTxAndEcho:
			// _U_prim_clone
			if (ptr != NULL) ret->x.rcTxAndEcho = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_lineWidth:
			// _U_prim_clone
			if (ptr != NULL) ret->x.lineWidth = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_pageSize:
			// _U_prim_clone
			if (ptr != NULL) ret->x.pageSize = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_crDisposition:
			// _U_prim_clone
			if (ptr != NULL) ret->x.crDisposition = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_hTabStop:
			// _U_prim_clone
			if (ptr != NULL) ret->x.hTabStop = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_hTabDisposition:
			// _U_prim_clone
			if (ptr != NULL) ret->x.hTabDisposition = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_formFeedDisposition:
			// _U_prim_clone
			if (ptr != NULL) ret->x.formFeedDisposition = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_vTabStop:
			// _U_prim_clone
			if (ptr != NULL) ret->x.vTabStop = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_vTabDisposition:
			// _U_prim_clone
			if (ptr != NULL) ret->x.vTabDisposition = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_lfDisposition:
			// _U_prim_clone
			if (ptr != NULL) ret->x.lfDisposition = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_xAscii:
			// _U_prim_clone
			if (ptr != NULL) ret->x.xAscii = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_forceLogout:
			// _U_prim_clone
			if (ptr != NULL) ret->x.forceLogout = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_byteMacro:
			// _U_prim_clone
			if (ptr != NULL) ret->x.byteMacro = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_dataEntryTerminal:
			// _U_prim_clone
			if (ptr != NULL) ret->x.dataEntryTerminal = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_supdupProtocol:
			// _U_prim_clone
			if (ptr != NULL) ret->x.supdupProtocol = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_supdupOutput:
			// _U_prim_clone
			if (ptr != NULL) ret->x.supdupOutput = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_sendLocation:
			// _U_prim_clone
			if (ptr != NULL) ret->x.sendLocation = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_terminalType:
			// _U_cst_clone
			if (ptr != NULL) ret->x.terminalType = (Dz1InetTelnetOptTerminalType *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_endOfRecord:
			// _U_prim_clone
			if (ptr != NULL) ret->x.endOfRecord = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_tacacsUserID:
			// _U_prim_clone
			if (ptr != NULL) ret->x.tacacsUserID = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_OutputMarking:
			// _U_prim_clone
			if (ptr != NULL) ret->x.OutputMarking = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_ttyNumber:
			// _U_prim_clone
			if (ptr != NULL) ret->x.ttyNumber = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_regime3270:
			// _U_prim_clone
			if (ptr != NULL) ret->x.regime3270 = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_xDot3Pad:
			// _U_prim_clone
			if (ptr != NULL) ret->x.xDot3Pad = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_windowSize:
			// _U_cst_clone
			if (ptr != NULL) ret->x.windowSize = (Dz1InetTelnetOptWindowSize *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_terminalSpeed:
			// _U_prim_clone
			if (ptr != NULL) ret->x.terminalSpeed = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_remoteFlowControl:
			// _U_prim_clone
			if (ptr != NULL) ret->x.remoteFlowControl = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_lineMode:
			// _U_prim_clone
			if (ptr != NULL) ret->x.lineMode = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_xDispLoc:
			// _U_prim_clone
			if (ptr != NULL) ret->x.xDispLoc = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_oldEnvs:
			// _U_prim_clone
			if (ptr != NULL) ret->x.oldEnvs = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_auth:
			// _U_prim_clone
			if (ptr != NULL) ret->x.auth = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_encryption:
			// _U_prim_clone
			if (ptr != NULL) ret->x.encryption = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_newEnvs:
			// _U_prim_clone
			if (ptr != NULL) ret->x.newEnvs = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_extOptList:
			// _U_prim_clone
			if (ptr != NULL) ret->x.extOptList = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetOptPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetTelnetOpt_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetTelnetOpt_purge(Dz1InetTelnetOpt *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1InetTelnetOptPresent_binary:
		Dz1u32_del(p->x.binary);
		break;
	case Dz1InetTelnetOptPresent_echo:
		Dz1u32_del(p->x.echo);
		break;
	case Dz1InetTelnetOptPresent_prepareReconnect:
		Dz1u32_del(p->x.prepareReconnect);
		break;
	case Dz1InetTelnetOptPresent_suppressGoAhead:
		Dz1u32_del(p->x.suppressGoAhead);
		break;
	case Dz1InetTelnetOptPresent_approximateMsgSize:
		Dz1u32_del(p->x.approximateMsgSize);
		break;
	case Dz1InetTelnetOptPresent_status:
		Dz1u32_del(p->x.status);
		break;
	case Dz1InetTelnetOptPresent_timingMark:
		Dz1u32_del(p->x.timingMark);
		break;
	case Dz1InetTelnetOptPresent_rcTxAndEcho:
		Dz1u32_del(p->x.rcTxAndEcho);
		break;
	case Dz1InetTelnetOptPresent_lineWidth:
		Dz1u32_del(p->x.lineWidth);
		break;
	case Dz1InetTelnetOptPresent_pageSize:
		Dz1u32_del(p->x.pageSize);
		break;
	case Dz1InetTelnetOptPresent_crDisposition:
		Dz1u32_del(p->x.crDisposition);
		break;
	case Dz1InetTelnetOptPresent_hTabStop:
		Dz1u32_del(p->x.hTabStop);
		break;
	case Dz1InetTelnetOptPresent_hTabDisposition:
		Dz1u32_del(p->x.hTabDisposition);
		break;
	case Dz1InetTelnetOptPresent_formFeedDisposition:
		Dz1u32_del(p->x.formFeedDisposition);
		break;
	case Dz1InetTelnetOptPresent_vTabStop:
		Dz1u32_del(p->x.vTabStop);
		break;
	case Dz1InetTelnetOptPresent_vTabDisposition:
		Dz1u32_del(p->x.vTabDisposition);
		break;
	case Dz1InetTelnetOptPresent_lfDisposition:
		Dz1u32_del(p->x.lfDisposition);
		break;
	case Dz1InetTelnetOptPresent_xAscii:
		Dz1u32_del(p->x.xAscii);
		break;
	case Dz1InetTelnetOptPresent_forceLogout:
		Dz1u32_del(p->x.forceLogout);
		break;
	case Dz1InetTelnetOptPresent_byteMacro:
		Dz1u32_del(p->x.byteMacro);
		break;
	case Dz1InetTelnetOptPresent_dataEntryTerminal:
		Dz1u32_del(p->x.dataEntryTerminal);
		break;
	case Dz1InetTelnetOptPresent_supdupProtocol:
		Dz1u32_del(p->x.supdupProtocol);
		break;
	case Dz1InetTelnetOptPresent_supdupOutput:
		Dz1u32_del(p->x.supdupOutput);
		break;
	case Dz1InetTelnetOptPresent_sendLocation:
		Dz1u32_del(p->x.sendLocation);
		break;
	case Dz1InetTelnetOptPresent_terminalType:
		Dz1InetTelnetOptTerminalType_del(p->x.terminalType);
		break;
	case Dz1InetTelnetOptPresent_endOfRecord:
		Dz1u32_del(p->x.endOfRecord);
		break;
	case Dz1InetTelnetOptPresent_tacacsUserID:
		Dz1u32_del(p->x.tacacsUserID);
		break;
	case Dz1InetTelnetOptPresent_OutputMarking:
		Dz1u32_del(p->x.OutputMarking);
		break;
	case Dz1InetTelnetOptPresent_ttyNumber:
		Dz1u32_del(p->x.ttyNumber);
		break;
	case Dz1InetTelnetOptPresent_regime3270:
		Dz1u32_del(p->x.regime3270);
		break;
	case Dz1InetTelnetOptPresent_xDot3Pad:
		Dz1u32_del(p->x.xDot3Pad);
		break;
	case Dz1InetTelnetOptPresent_windowSize:
		Dz1InetTelnetOptWindowSize_del(p->x.windowSize);
		break;
	case Dz1InetTelnetOptPresent_terminalSpeed:
		Dz1u32_del(p->x.terminalSpeed);
		break;
	case Dz1InetTelnetOptPresent_remoteFlowControl:
		Dz1u32_del(p->x.remoteFlowControl);
		break;
	case Dz1InetTelnetOptPresent_lineMode:
		Dz1u32_del(p->x.lineMode);
		break;
	case Dz1InetTelnetOptPresent_xDispLoc:
		Dz1u32_del(p->x.xDispLoc);
		break;
	case Dz1InetTelnetOptPresent_oldEnvs:
		Dz1u32_del(p->x.oldEnvs);
		break;
	case Dz1InetTelnetOptPresent_auth:
		Dz1u32_del(p->x.auth);
		break;
	case Dz1InetTelnetOptPresent_encryption:
		Dz1u32_del(p->x.encryption);
		break;
	case Dz1InetTelnetOptPresent_newEnvs:
		Dz1u32_del(p->x.newEnvs);
		break;
	case Dz1InetTelnetOptPresent_extOptList:
		Dz1u32_del(p->x.extOptList);
		break;
	default:
		break;
	}
}

void Dz1InetTelnetOpt_del(Dz1InetTelnetOpt *p)
{
	if (!p) return;
	Dz1InetTelnetOpt_purge(p);
	Dz1Free(p);
}

void Dz1InetTelnetOpt_dump(Dz1InetTelnetOpt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1InetTelnetOptPresent_binary:
		Dz1Thread_printf(Dz1T("binary = ")); Dz1u32_dump(p->x.binary, tab); 
		break;
	case Dz1InetTelnetOptPresent_echo:
		Dz1Thread_printf(Dz1T("echo = ")); Dz1u32_dump(p->x.echo, tab); 
		break;
	case Dz1InetTelnetOptPresent_prepareReconnect:
		Dz1Thread_printf(Dz1T("prepareReconnect = ")); Dz1u32_dump(p->x.prepareReconnect, tab); 
		break;
	case Dz1InetTelnetOptPresent_suppressGoAhead:
		Dz1Thread_printf(Dz1T("suppressGoAhead = ")); Dz1u32_dump(p->x.suppressGoAhead, tab); 
		break;
	case Dz1InetTelnetOptPresent_approximateMsgSize:
		Dz1Thread_printf(Dz1T("approximateMsgSize = ")); Dz1u32_dump(p->x.approximateMsgSize, tab); 
		break;
	case Dz1InetTelnetOptPresent_status:
		Dz1Thread_printf(Dz1T("status = ")); Dz1u32_dump(p->x.status, tab); 
		break;
	case Dz1InetTelnetOptPresent_timingMark:
		Dz1Thread_printf(Dz1T("timingMark = ")); Dz1u32_dump(p->x.timingMark, tab); 
		break;
	case Dz1InetTelnetOptPresent_rcTxAndEcho:
		Dz1Thread_printf(Dz1T("rcTxAndEcho = ")); Dz1u32_dump(p->x.rcTxAndEcho, tab); 
		break;
	case Dz1InetTelnetOptPresent_lineWidth:
		Dz1Thread_printf(Dz1T("lineWidth = ")); Dz1u32_dump(p->x.lineWidth, tab); 
		break;
	case Dz1InetTelnetOptPresent_pageSize:
		Dz1Thread_printf(Dz1T("pageSize = ")); Dz1u32_dump(p->x.pageSize, tab); 
		break;
	case Dz1InetTelnetOptPresent_crDisposition:
		Dz1Thread_printf(Dz1T("crDisposition = ")); Dz1u32_dump(p->x.crDisposition, tab); 
		break;
	case Dz1InetTelnetOptPresent_hTabStop:
		Dz1Thread_printf(Dz1T("hTabStop = ")); Dz1u32_dump(p->x.hTabStop, tab); 
		break;
	case Dz1InetTelnetOptPresent_hTabDisposition:
		Dz1Thread_printf(Dz1T("hTabDisposition = ")); Dz1u32_dump(p->x.hTabDisposition, tab); 
		break;
	case Dz1InetTelnetOptPresent_formFeedDisposition:
		Dz1Thread_printf(Dz1T("formFeedDisposition = ")); Dz1u32_dump(p->x.formFeedDisposition, tab); 
		break;
	case Dz1InetTelnetOptPresent_vTabStop:
		Dz1Thread_printf(Dz1T("vTabStop = ")); Dz1u32_dump(p->x.vTabStop, tab); 
		break;
	case Dz1InetTelnetOptPresent_vTabDisposition:
		Dz1Thread_printf(Dz1T("vTabDisposition = ")); Dz1u32_dump(p->x.vTabDisposition, tab); 
		break;
	case Dz1InetTelnetOptPresent_lfDisposition:
		Dz1Thread_printf(Dz1T("lfDisposition = ")); Dz1u32_dump(p->x.lfDisposition, tab); 
		break;
	case Dz1InetTelnetOptPresent_xAscii:
		Dz1Thread_printf(Dz1T("xAscii = ")); Dz1u32_dump(p->x.xAscii, tab); 
		break;
	case Dz1InetTelnetOptPresent_forceLogout:
		Dz1Thread_printf(Dz1T("forceLogout = ")); Dz1u32_dump(p->x.forceLogout, tab); 
		break;
	case Dz1InetTelnetOptPresent_byteMacro:
		Dz1Thread_printf(Dz1T("byteMacro = ")); Dz1u32_dump(p->x.byteMacro, tab); 
		break;
	case Dz1InetTelnetOptPresent_dataEntryTerminal:
		Dz1Thread_printf(Dz1T("dataEntryTerminal = ")); Dz1u32_dump(p->x.dataEntryTerminal, tab); 
		break;
	case Dz1InetTelnetOptPresent_supdupProtocol:
		Dz1Thread_printf(Dz1T("supdupProtocol = ")); Dz1u32_dump(p->x.supdupProtocol, tab); 
		break;
	case Dz1InetTelnetOptPresent_supdupOutput:
		Dz1Thread_printf(Dz1T("supdupOutput = ")); Dz1u32_dump(p->x.supdupOutput, tab); 
		break;
	case Dz1InetTelnetOptPresent_sendLocation:
		Dz1Thread_printf(Dz1T("sendLocation = ")); Dz1u32_dump(p->x.sendLocation, tab); 
		break;
	case Dz1InetTelnetOptPresent_terminalType:
		Dz1Thread_printf(Dz1T("terminalType.")); Dz1InetTelnetOptTerminalType_dump(p->x.terminalType, tab); 
		break;
	case Dz1InetTelnetOptPresent_endOfRecord:
		Dz1Thread_printf(Dz1T("endOfRecord = ")); Dz1u32_dump(p->x.endOfRecord, tab); 
		break;
	case Dz1InetTelnetOptPresent_tacacsUserID:
		Dz1Thread_printf(Dz1T("tacacsUserID = ")); Dz1u32_dump(p->x.tacacsUserID, tab); 
		break;
	case Dz1InetTelnetOptPresent_OutputMarking:
		Dz1Thread_printf(Dz1T("OutputMarking = ")); Dz1u32_dump(p->x.OutputMarking, tab); 
		break;
	case Dz1InetTelnetOptPresent_ttyNumber:
		Dz1Thread_printf(Dz1T("ttyNumber = ")); Dz1u32_dump(p->x.ttyNumber, tab); 
		break;
	case Dz1InetTelnetOptPresent_regime3270:
		Dz1Thread_printf(Dz1T("regime3270 = ")); Dz1u32_dump(p->x.regime3270, tab); 
		break;
	case Dz1InetTelnetOptPresent_xDot3Pad:
		Dz1Thread_printf(Dz1T("xDot3Pad = ")); Dz1u32_dump(p->x.xDot3Pad, tab); 
		break;
	case Dz1InetTelnetOptPresent_windowSize:
		Dz1Thread_printf(Dz1T("windowSize = ")); Dz1InetTelnetOptWindowSize_dump(p->x.windowSize, tab); 
		break;
	case Dz1InetTelnetOptPresent_terminalSpeed:
		Dz1Thread_printf(Dz1T("terminalSpeed = ")); Dz1u32_dump(p->x.terminalSpeed, tab); 
		break;
	case Dz1InetTelnetOptPresent_remoteFlowControl:
		Dz1Thread_printf(Dz1T("remoteFlowControl = ")); Dz1u32_dump(p->x.remoteFlowControl, tab); 
		break;
	case Dz1InetTelnetOptPresent_lineMode:
		Dz1Thread_printf(Dz1T("lineMode = ")); Dz1u32_dump(p->x.lineMode, tab); 
		break;
	case Dz1InetTelnetOptPresent_xDispLoc:
		Dz1Thread_printf(Dz1T("xDispLoc = ")); Dz1u32_dump(p->x.xDispLoc, tab); 
		break;
	case Dz1InetTelnetOptPresent_oldEnvs:
		Dz1Thread_printf(Dz1T("oldEnvs = ")); Dz1u32_dump(p->x.oldEnvs, tab); 
		break;
	case Dz1InetTelnetOptPresent_auth:
		Dz1Thread_printf(Dz1T("auth = ")); Dz1u32_dump(p->x.auth, tab); 
		break;
	case Dz1InetTelnetOptPresent_encryption:
		Dz1Thread_printf(Dz1T("encryption = ")); Dz1u32_dump(p->x.encryption, tab); 
		break;
	case Dz1InetTelnetOptPresent_newEnvs:
		Dz1Thread_printf(Dz1T("newEnvs = ")); Dz1u32_dump(p->x.newEnvs, tab); 
		break;
	case Dz1InetTelnetOptPresent_extOptList:
		Dz1Thread_printf(Dz1T("extOptList = ")); Dz1u32_dump(p->x.extOptList, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1InetTelnetOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptCode
static struct Dz1InetTelnetOptCodeMapA
{
	str_t str;
	Dz1InetTelnetOptCode v;
} Dz1InetTelnetOptCodeMapA[] =
{
	{ (char *)"binary", Dz1InetTelnetOptCode_binary },
	{ (char *)"echo", Dz1InetTelnetOptCode_echo },
	{ (char *)"prepareReconnect", Dz1InetTelnetOptCode_prepareReconnect },
	{ (char *)"suppressGoAhead", Dz1InetTelnetOptCode_suppressGoAhead },
	{ (char *)"approximateMsgSize", Dz1InetTelnetOptCode_approximateMsgSize },
	{ (char *)"status", Dz1InetTelnetOptCode_status },
	{ (char *)"timingMark", Dz1InetTelnetOptCode_timingMark },
	{ (char *)"rcTxAndEcho", Dz1InetTelnetOptCode_rcTxAndEcho },
	{ (char *)"lineWidth", Dz1InetTelnetOptCode_lineWidth },
	{ (char *)"pageSize", Dz1InetTelnetOptCode_pageSize },
	{ (char *)"crDisposition", Dz1InetTelnetOptCode_crDisposition },
	{ (char *)"hTabStop", Dz1InetTelnetOptCode_hTabStop },
	{ (char *)"hTabDisposition", Dz1InetTelnetOptCode_hTabDisposition },
	{ (char *)"formFeedDisposition", Dz1InetTelnetOptCode_formFeedDisposition },
	{ (char *)"vTabStop", Dz1InetTelnetOptCode_vTabStop },
	{ (char *)"vTabDisposition", Dz1InetTelnetOptCode_vTabDisposition },
	{ (char *)"lfDisposition", Dz1InetTelnetOptCode_lfDisposition },
	{ (char *)"xAscii", Dz1InetTelnetOptCode_xAscii },
	{ (char *)"forceLogout", Dz1InetTelnetOptCode_forceLogout },
	{ (char *)"byteMacro", Dz1InetTelnetOptCode_byteMacro },
	{ (char *)"dataEntryTerminal", Dz1InetTelnetOptCode_dataEntryTerminal },
	{ (char *)"supdupProtocol", Dz1InetTelnetOptCode_supdupProtocol },
	{ (char *)"supdupOutput", Dz1InetTelnetOptCode_supdupOutput },
	{ (char *)"sendLocation", Dz1InetTelnetOptCode_sendLocation },
	{ (char *)"terminalType", Dz1InetTelnetOptCode_terminalType },
	{ (char *)"endOfRecord", Dz1InetTelnetOptCode_endOfRecord },
	{ (char *)"tacacsUserID", Dz1InetTelnetOptCode_tacacsUserID },
	{ (char *)"OutputMarking", Dz1InetTelnetOptCode_OutputMarking },
	{ (char *)"ttyNumber", Dz1InetTelnetOptCode_ttyNumber },
	{ (char *)"regime3270", Dz1InetTelnetOptCode_regime3270 },
	{ (char *)"xDot3Pad", Dz1InetTelnetOptCode_xDot3Pad },
	{ (char *)"windowSize", Dz1InetTelnetOptCode_windowSize },
	{ (char *)"terminalSpeed", Dz1InetTelnetOptCode_terminalSpeed },
	{ (char *)"remoteFlowControl", Dz1InetTelnetOptCode_remoteFlowControl },
	{ (char *)"lineMode", Dz1InetTelnetOptCode_lineMode },
	{ (char *)"xDispLoc", Dz1InetTelnetOptCode_xDispLoc },
	{ (char *)"oldEnvs", Dz1InetTelnetOptCode_oldEnvs },
	{ (char *)"auth", Dz1InetTelnetOptCode_auth },
	{ (char *)"encryption", Dz1InetTelnetOptCode_encryption },
	{ (char *)"newEnvs", Dz1InetTelnetOptCode_newEnvs },
	{ (char *)"extOptList", Dz1InetTelnetOptCode_extOptList },
	{ NULL, Dz1InetTelnetOptCode_max }
};

str_t Dz1InetTelnetOptCodeStrA(Dz1InetTelnetOptCode v)
{
	struct Dz1InetTelnetOptCodeMapA *i = NULL;
	for (i = Dz1InetTelnetOptCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetOptCode Dz1InetTelnetOptCodeFromStrA(str_t str)
{
	struct Dz1InetTelnetOptCodeMapA *i = NULL;
	for (i = Dz1InetTelnetOptCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetOptCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetTelnetOptCodeMapW
{
	wstr_t str;
	Dz1InetTelnetOptCode v;
} Dz1InetTelnetOptCodeMapW[] =
{
	{ (wchar_t *)L"binary", Dz1InetTelnetOptCode_binary },
	{ (wchar_t *)L"echo", Dz1InetTelnetOptCode_echo },
	{ (wchar_t *)L"prepareReconnect", Dz1InetTelnetOptCode_prepareReconnect },
	{ (wchar_t *)L"suppressGoAhead", Dz1InetTelnetOptCode_suppressGoAhead },
	{ (wchar_t *)L"approximateMsgSize", Dz1InetTelnetOptCode_approximateMsgSize },
	{ (wchar_t *)L"status", Dz1InetTelnetOptCode_status },
	{ (wchar_t *)L"timingMark", Dz1InetTelnetOptCode_timingMark },
	{ (wchar_t *)L"rcTxAndEcho", Dz1InetTelnetOptCode_rcTxAndEcho },
	{ (wchar_t *)L"lineWidth", Dz1InetTelnetOptCode_lineWidth },
	{ (wchar_t *)L"pageSize", Dz1InetTelnetOptCode_pageSize },
	{ (wchar_t *)L"crDisposition", Dz1InetTelnetOptCode_crDisposition },
	{ (wchar_t *)L"hTabStop", Dz1InetTelnetOptCode_hTabStop },
	{ (wchar_t *)L"hTabDisposition", Dz1InetTelnetOptCode_hTabDisposition },
	{ (wchar_t *)L"formFeedDisposition", Dz1InetTelnetOptCode_formFeedDisposition },
	{ (wchar_t *)L"vTabStop", Dz1InetTelnetOptCode_vTabStop },
	{ (wchar_t *)L"vTabDisposition", Dz1InetTelnetOptCode_vTabDisposition },
	{ (wchar_t *)L"lfDisposition", Dz1InetTelnetOptCode_lfDisposition },
	{ (wchar_t *)L"xAscii", Dz1InetTelnetOptCode_xAscii },
	{ (wchar_t *)L"forceLogout", Dz1InetTelnetOptCode_forceLogout },
	{ (wchar_t *)L"byteMacro", Dz1InetTelnetOptCode_byteMacro },
	{ (wchar_t *)L"dataEntryTerminal", Dz1InetTelnetOptCode_dataEntryTerminal },
	{ (wchar_t *)L"supdupProtocol", Dz1InetTelnetOptCode_supdupProtocol },
	{ (wchar_t *)L"supdupOutput", Dz1InetTelnetOptCode_supdupOutput },
	{ (wchar_t *)L"sendLocation", Dz1InetTelnetOptCode_sendLocation },
	{ (wchar_t *)L"terminalType", Dz1InetTelnetOptCode_terminalType },
	{ (wchar_t *)L"endOfRecord", Dz1InetTelnetOptCode_endOfRecord },
	{ (wchar_t *)L"tacacsUserID", Dz1InetTelnetOptCode_tacacsUserID },
	{ (wchar_t *)L"OutputMarking", Dz1InetTelnetOptCode_OutputMarking },
	{ (wchar_t *)L"ttyNumber", Dz1InetTelnetOptCode_ttyNumber },
	{ (wchar_t *)L"regime3270", Dz1InetTelnetOptCode_regime3270 },
	{ (wchar_t *)L"xDot3Pad", Dz1InetTelnetOptCode_xDot3Pad },
	{ (wchar_t *)L"windowSize", Dz1InetTelnetOptCode_windowSize },
	{ (wchar_t *)L"terminalSpeed", Dz1InetTelnetOptCode_terminalSpeed },
	{ (wchar_t *)L"remoteFlowControl", Dz1InetTelnetOptCode_remoteFlowControl },
	{ (wchar_t *)L"lineMode", Dz1InetTelnetOptCode_lineMode },
	{ (wchar_t *)L"xDispLoc", Dz1InetTelnetOptCode_xDispLoc },
	{ (wchar_t *)L"oldEnvs", Dz1InetTelnetOptCode_oldEnvs },
	{ (wchar_t *)L"auth", Dz1InetTelnetOptCode_auth },
	{ (wchar_t *)L"encryption", Dz1InetTelnetOptCode_encryption },
	{ (wchar_t *)L"newEnvs", Dz1InetTelnetOptCode_newEnvs },
	{ (wchar_t *)L"extOptList", Dz1InetTelnetOptCode_extOptList },
	{ NULL, Dz1InetTelnetOptCode_max }
};

wstr_t Dz1InetTelnetOptCodeStrW(Dz1InetTelnetOptCode v)
{
	struct Dz1InetTelnetOptCodeMapW *i = NULL;
	for (i = Dz1InetTelnetOptCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetOptCode Dz1InetTelnetOptCodeFromStrW(wstr_t str)
{
	struct Dz1InetTelnetOptCodeMapW *i = NULL;
	for (i = Dz1InetTelnetOptCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetOptCode_max;
}
#endif // UNIX_SYSTEM

Dz1InetTelnetOptCode *Dz1InetTelnetOptCode_new(Dz1InetTelnetOptCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetOptCode *__internal_ret = (Dz1InetTelnetOptCode *)Dz1Calloc(sizeof(Dz1InetTelnetOptCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetTelnetOptCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetCmdPresent
static struct Dz1InetTelnetCmdPresentMapA
{
	str_t str;
	Dz1InetTelnetCmdPresent v;
} Dz1InetTelnetCmdPresentMapA[] =
{
	{ (char *)"endOfSubNego", Dz1InetTelnetCmdPresent_endOfSubNego },
	{ (char *)"noOper", Dz1InetTelnetCmdPresent_noOper },
	{ (char *)"dataMark", Dz1InetTelnetCmdPresent_dataMark },
	{ (char *)"brk", Dz1InetTelnetCmdPresent_brk },
	{ (char *)"interruptProcess", Dz1InetTelnetCmdPresent_interruptProcess },
	{ (char *)"abortOutput", Dz1InetTelnetCmdPresent_abortOutput },
	{ (char *)"areYouThere", Dz1InetTelnetCmdPresent_areYouThere },
	{ (char *)"eraseChar", Dz1InetTelnetCmdPresent_eraseChar },
	{ (char *)"eraseLine", Dz1InetTelnetCmdPresent_eraseLine },
	{ (char *)"goAhead", Dz1InetTelnetCmdPresent_goAhead },
	{ (char *)"subNego", Dz1InetTelnetCmdPresent_subNego },
	{ (char *)"willOpt", Dz1InetTelnetCmdPresent_willOpt },
	{ (char *)"wontOpt", Dz1InetTelnetCmdPresent_wontOpt },
	{ (char *)"doOpt", Dz1InetTelnetCmdPresent_doOpt },
	{ (char *)"dontOpt", Dz1InetTelnetCmdPresent_dontOpt },
	{ NULL, Dz1InetTelnetCmdPresent_max }
};

str_t Dz1InetTelnetCmdPresentStrA(Dz1InetTelnetCmdPresent v)
{
	struct Dz1InetTelnetCmdPresentMapA *i = NULL;
	for (i = Dz1InetTelnetCmdPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetCmdPresent Dz1InetTelnetCmdPresentFromStrA(str_t str)
{
	struct Dz1InetTelnetCmdPresentMapA *i = NULL;
	for (i = Dz1InetTelnetCmdPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetCmdPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetTelnetCmdPresentMapW
{
	wstr_t str;
	Dz1InetTelnetCmdPresent v;
} Dz1InetTelnetCmdPresentMapW[] =
{
	{ (wchar_t *)L"endOfSubNego", Dz1InetTelnetCmdPresent_endOfSubNego },
	{ (wchar_t *)L"noOper", Dz1InetTelnetCmdPresent_noOper },
	{ (wchar_t *)L"dataMark", Dz1InetTelnetCmdPresent_dataMark },
	{ (wchar_t *)L"brk", Dz1InetTelnetCmdPresent_brk },
	{ (wchar_t *)L"interruptProcess", Dz1InetTelnetCmdPresent_interruptProcess },
	{ (wchar_t *)L"abortOutput", Dz1InetTelnetCmdPresent_abortOutput },
	{ (wchar_t *)L"areYouThere", Dz1InetTelnetCmdPresent_areYouThere },
	{ (wchar_t *)L"eraseChar", Dz1InetTelnetCmdPresent_eraseChar },
	{ (wchar_t *)L"eraseLine", Dz1InetTelnetCmdPresent_eraseLine },
	{ (wchar_t *)L"goAhead", Dz1InetTelnetCmdPresent_goAhead },
	{ (wchar_t *)L"subNego", Dz1InetTelnetCmdPresent_subNego },
	{ (wchar_t *)L"willOpt", Dz1InetTelnetCmdPresent_willOpt },
	{ (wchar_t *)L"wontOpt", Dz1InetTelnetCmdPresent_wontOpt },
	{ (wchar_t *)L"doOpt", Dz1InetTelnetCmdPresent_doOpt },
	{ (wchar_t *)L"dontOpt", Dz1InetTelnetCmdPresent_dontOpt },
	{ NULL, Dz1InetTelnetCmdPresent_max }
};

wstr_t Dz1InetTelnetCmdPresentStrW(Dz1InetTelnetCmdPresent v)
{
	struct Dz1InetTelnetCmdPresentMapW *i = NULL;
	for (i = Dz1InetTelnetCmdPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetCmdPresent Dz1InetTelnetCmdPresentFromStrW(wstr_t str)
{
	struct Dz1InetTelnetCmdPresentMapW *i = NULL;
	for (i = Dz1InetTelnetCmdPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetCmdPresent_max;
}
#endif // UNIX_SYSTEM

Dz1InetTelnetCmdPresent *Dz1InetTelnetCmdPresent_new(Dz1InetTelnetCmdPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetCmdPresent *__internal_ret = (Dz1InetTelnetCmdPresent *)Dz1Calloc(sizeof(Dz1InetTelnetCmdPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1InetTelnetCmdPresent_dump(Dz1InetTelnetCmdPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1InetTelnetCmdPresentStr(*v));
}
// Dz1InetTelnetCmdPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetCmd
Dz1InetTelnetCmd *Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetCmd *ret = (Dz1InetTelnetCmd *)Dz1Calloc(sizeof(Dz1InetTelnetCmd), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetTelnetCmd_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1InetTelnetCmdPresent_endOfSubNego:
			// _U_prim_clone
			if (ptr != NULL) ret->x.endOfSubNego = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_noOper:
			// _U_prim_clone
			if (ptr != NULL) ret->x.noOper = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_dataMark:
			// _U_prim_clone
			if (ptr != NULL) ret->x.dataMark = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_brk:
			// _U_prim_clone
			if (ptr != NULL) ret->x.brk = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_interruptProcess:
			// _U_prim_clone
			if (ptr != NULL) ret->x.interruptProcess = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_abortOutput:
			// _U_prim_clone
			if (ptr != NULL) ret->x.abortOutput = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_areYouThere:
			// _U_prim_clone
			if (ptr != NULL) ret->x.areYouThere = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_eraseChar:
			// _U_prim_clone
			if (ptr != NULL) ret->x.eraseChar = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_eraseLine:
			// _U_prim_clone
			if (ptr != NULL) ret->x.eraseLine = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_goAhead:
			// _U_prim_clone
			if (ptr != NULL) ret->x.goAhead = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_subNego:
			// _U_cst_clone
			if (ptr != NULL) ret->x.subNego = (Dz1InetTelnetOpt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_willOpt:
			// _U_cst_clone
			if (ptr != NULL) ret->x.willOpt = (Dz1InetTelnetOpt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_wontOpt:
			// _U_cst_clone
			if (ptr != NULL) ret->x.wontOpt = (Dz1InetTelnetOpt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_doOpt:
			// _U_cst_clone
			if (ptr != NULL) ret->x.doOpt = (Dz1InetTelnetOpt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_dontOpt:
			// _U_cst_clone
			if (ptr != NULL) ret->x.dontOpt = (Dz1InetTelnetOpt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetCmdPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetTelnetCmd_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetTelnetCmd_purge(Dz1InetTelnetCmd *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1InetTelnetCmdPresent_endOfSubNego:
		Dz1u32_del(p->x.endOfSubNego);
		break;
	case Dz1InetTelnetCmdPresent_noOper:
		Dz1u32_del(p->x.noOper);
		break;
	case Dz1InetTelnetCmdPresent_dataMark:
		Dz1u32_del(p->x.dataMark);
		break;
	case Dz1InetTelnetCmdPresent_brk:
		Dz1u32_del(p->x.brk);
		break;
	case Dz1InetTelnetCmdPresent_interruptProcess:
		Dz1u32_del(p->x.interruptProcess);
		break;
	case Dz1InetTelnetCmdPresent_abortOutput:
		Dz1u32_del(p->x.abortOutput);
		break;
	case Dz1InetTelnetCmdPresent_areYouThere:
		Dz1u32_del(p->x.areYouThere);
		break;
	case Dz1InetTelnetCmdPresent_eraseChar:
		Dz1u32_del(p->x.eraseChar);
		break;
	case Dz1InetTelnetCmdPresent_eraseLine:
		Dz1u32_del(p->x.eraseLine);
		break;
	case Dz1InetTelnetCmdPresent_goAhead:
		Dz1u32_del(p->x.goAhead);
		break;
	case Dz1InetTelnetCmdPresent_subNego:
		Dz1InetTelnetOpt_del(p->x.subNego);
		break;
	case Dz1InetTelnetCmdPresent_willOpt:
		Dz1InetTelnetOpt_del(p->x.willOpt);
		break;
	case Dz1InetTelnetCmdPresent_wontOpt:
		Dz1InetTelnetOpt_del(p->x.wontOpt);
		break;
	case Dz1InetTelnetCmdPresent_doOpt:
		Dz1InetTelnetOpt_del(p->x.doOpt);
		break;
	case Dz1InetTelnetCmdPresent_dontOpt:
		Dz1InetTelnetOpt_del(p->x.dontOpt);
		break;
	default:
		break;
	}
}

void Dz1InetTelnetCmd_del(Dz1InetTelnetCmd *p)
{
	if (!p) return;
	Dz1InetTelnetCmd_purge(p);
	Dz1Free(p);
}

void Dz1InetTelnetCmd_dump(Dz1InetTelnetCmd *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1InetTelnetCmdPresent_endOfSubNego:
		Dz1Thread_printf(Dz1T("endOfSubNego = ")); Dz1u32_dump(p->x.endOfSubNego, tab); 
		break;
	case Dz1InetTelnetCmdPresent_noOper:
		Dz1Thread_printf(Dz1T("noOper = ")); Dz1u32_dump(p->x.noOper, tab); 
		break;
	case Dz1InetTelnetCmdPresent_dataMark:
		Dz1Thread_printf(Dz1T("dataMark = ")); Dz1u32_dump(p->x.dataMark, tab); 
		break;
	case Dz1InetTelnetCmdPresent_brk:
		Dz1Thread_printf(Dz1T("brk = ")); Dz1u32_dump(p->x.brk, tab); 
		break;
	case Dz1InetTelnetCmdPresent_interruptProcess:
		Dz1Thread_printf(Dz1T("interruptProcess = ")); Dz1u32_dump(p->x.interruptProcess, tab); 
		break;
	case Dz1InetTelnetCmdPresent_abortOutput:
		Dz1Thread_printf(Dz1T("abortOutput = ")); Dz1u32_dump(p->x.abortOutput, tab); 
		break;
	case Dz1InetTelnetCmdPresent_areYouThere:
		Dz1Thread_printf(Dz1T("areYouThere = ")); Dz1u32_dump(p->x.areYouThere, tab); 
		break;
	case Dz1InetTelnetCmdPresent_eraseChar:
		Dz1Thread_printf(Dz1T("eraseChar = ")); Dz1u32_dump(p->x.eraseChar, tab); 
		break;
	case Dz1InetTelnetCmdPresent_eraseLine:
		Dz1Thread_printf(Dz1T("eraseLine = ")); Dz1u32_dump(p->x.eraseLine, tab); 
		break;
	case Dz1InetTelnetCmdPresent_goAhead:
		Dz1Thread_printf(Dz1T("goAhead = ")); Dz1u32_dump(p->x.goAhead, tab); 
		break;
	case Dz1InetTelnetCmdPresent_subNego:
		Dz1Thread_printf(Dz1T("subNego.")); Dz1InetTelnetOpt_dump(p->x.subNego, tab); 
		break;
	case Dz1InetTelnetCmdPresent_willOpt:
		Dz1Thread_printf(Dz1T("willOpt.")); Dz1InetTelnetOpt_dump(p->x.willOpt, tab); 
		break;
	case Dz1InetTelnetCmdPresent_wontOpt:
		Dz1Thread_printf(Dz1T("wontOpt.")); Dz1InetTelnetOpt_dump(p->x.wontOpt, tab); 
		break;
	case Dz1InetTelnetCmdPresent_doOpt:
		Dz1Thread_printf(Dz1T("doOpt.")); Dz1InetTelnetOpt_dump(p->x.doOpt, tab); 
		break;
	case Dz1InetTelnetCmdPresent_dontOpt:
		Dz1Thread_printf(Dz1T("dontOpt.")); Dz1InetTelnetOpt_dump(p->x.dontOpt, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1InetTelnetCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetCmdCode
static struct Dz1InetTelnetCmdCodeMapA
{
	str_t str;
	Dz1InetTelnetCmdCode v;
} Dz1InetTelnetCmdCodeMapA[] =
{
	{ (char *)"endOfSubNego", Dz1InetTelnetCmdCode_endOfSubNego },
	{ (char *)"noOper", Dz1InetTelnetCmdCode_noOper },
	{ (char *)"dataMark", Dz1InetTelnetCmdCode_dataMark },
	{ (char *)"brk", Dz1InetTelnetCmdCode_brk },
	{ (char *)"interruptProcess", Dz1InetTelnetCmdCode_interruptProcess },
	{ (char *)"abortOutput", Dz1InetTelnetCmdCode_abortOutput },
	{ (char *)"areYouThere", Dz1InetTelnetCmdCode_areYouThere },
	{ (char *)"eraseChar", Dz1InetTelnetCmdCode_eraseChar },
	{ (char *)"eraseLine", Dz1InetTelnetCmdCode_eraseLine },
	{ (char *)"goAhead", Dz1InetTelnetCmdCode_goAhead },
	{ (char *)"subNego", Dz1InetTelnetCmdCode_subNego },
	{ (char *)"willOpt", Dz1InetTelnetCmdCode_willOpt },
	{ (char *)"wontOpt", Dz1InetTelnetCmdCode_wontOpt },
	{ (char *)"doOpt", Dz1InetTelnetCmdCode_doOpt },
	{ (char *)"dontOpt", Dz1InetTelnetCmdCode_dontOpt },
	{ NULL, Dz1InetTelnetCmdCode_max }
};

str_t Dz1InetTelnetCmdCodeStrA(Dz1InetTelnetCmdCode v)
{
	struct Dz1InetTelnetCmdCodeMapA *i = NULL;
	for (i = Dz1InetTelnetCmdCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetCmdCode Dz1InetTelnetCmdCodeFromStrA(str_t str)
{
	struct Dz1InetTelnetCmdCodeMapA *i = NULL;
	for (i = Dz1InetTelnetCmdCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetCmdCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetTelnetCmdCodeMapW
{
	wstr_t str;
	Dz1InetTelnetCmdCode v;
} Dz1InetTelnetCmdCodeMapW[] =
{
	{ (wchar_t *)L"endOfSubNego", Dz1InetTelnetCmdCode_endOfSubNego },
	{ (wchar_t *)L"noOper", Dz1InetTelnetCmdCode_noOper },
	{ (wchar_t *)L"dataMark", Dz1InetTelnetCmdCode_dataMark },
	{ (wchar_t *)L"brk", Dz1InetTelnetCmdCode_brk },
	{ (wchar_t *)L"interruptProcess", Dz1InetTelnetCmdCode_interruptProcess },
	{ (wchar_t *)L"abortOutput", Dz1InetTelnetCmdCode_abortOutput },
	{ (wchar_t *)L"areYouThere", Dz1InetTelnetCmdCode_areYouThere },
	{ (wchar_t *)L"eraseChar", Dz1InetTelnetCmdCode_eraseChar },
	{ (wchar_t *)L"eraseLine", Dz1InetTelnetCmdCode_eraseLine },
	{ (wchar_t *)L"goAhead", Dz1InetTelnetCmdCode_goAhead },
	{ (wchar_t *)L"subNego", Dz1InetTelnetCmdCode_subNego },
	{ (wchar_t *)L"willOpt", Dz1InetTelnetCmdCode_willOpt },
	{ (wchar_t *)L"wontOpt", Dz1InetTelnetCmdCode_wontOpt },
	{ (wchar_t *)L"doOpt", Dz1InetTelnetCmdCode_doOpt },
	{ (wchar_t *)L"dontOpt", Dz1InetTelnetCmdCode_dontOpt },
	{ NULL, Dz1InetTelnetCmdCode_max }
};

wstr_t Dz1InetTelnetCmdCodeStrW(Dz1InetTelnetCmdCode v)
{
	struct Dz1InetTelnetCmdCodeMapW *i = NULL;
	for (i = Dz1InetTelnetCmdCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetCmdCode Dz1InetTelnetCmdCodeFromStrW(wstr_t str)
{
	struct Dz1InetTelnetCmdCodeMapW *i = NULL;
	for (i = Dz1InetTelnetCmdCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetCmdCode_max;
}
#endif // UNIX_SYSTEM

Dz1InetTelnetCmdCode *Dz1InetTelnetCmdCode_new(Dz1InetTelnetCmdCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetCmdCode *__internal_ret = (Dz1InetTelnetCmdCode *)Dz1Calloc(sizeof(Dz1InetTelnetCmdCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetTelnetCmdCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetEsc
static struct Dz1InetTelnetEscMapA
{
	str_t str;
	Dz1InetTelnetEsc v;
} Dz1InetTelnetEscMapA[] =
{
	{ (char *)"IAC", Dz1InetTelnetEsc_IAC },
	{ NULL, Dz1InetTelnetEsc_max }
};

str_t Dz1InetTelnetEscStrA(Dz1InetTelnetEsc v)
{
	struct Dz1InetTelnetEscMapA *i = NULL;
	for (i = Dz1InetTelnetEscMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetEsc Dz1InetTelnetEscFromStrA(str_t str)
{
	struct Dz1InetTelnetEscMapA *i = NULL;
	for (i = Dz1InetTelnetEscMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetEsc_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetTelnetEscMapW
{
	wstr_t str;
	Dz1InetTelnetEsc v;
} Dz1InetTelnetEscMapW[] =
{
	{ (wchar_t *)L"IAC", Dz1InetTelnetEsc_IAC },
	{ NULL, Dz1InetTelnetEsc_max }
};

wstr_t Dz1InetTelnetEscStrW(Dz1InetTelnetEsc v)
{
	struct Dz1InetTelnetEscMapW *i = NULL;
	for (i = Dz1InetTelnetEscMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetEsc Dz1InetTelnetEscFromStrW(wstr_t str)
{
	struct Dz1InetTelnetEscMapW *i = NULL;
	for (i = Dz1InetTelnetEscMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetEsc_max;
}
#endif // UNIX_SYSTEM

Dz1InetTelnetEsc *Dz1InetTelnetEsc_new(Dz1InetTelnetEsc *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetEsc *__internal_ret = (Dz1InetTelnetEsc *)Dz1Calloc(sizeof(Dz1InetTelnetEsc), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetTelnetEsc
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetMsgPresent
static struct Dz1InetTelnetMsgPresentMapA
{
	str_t str;
	Dz1InetTelnetMsgPresent v;
} Dz1InetTelnetMsgPresentMapA[] =
{
	{ (char *)"cmd", Dz1InetTelnetMsgPresent_cmd },
	{ (char *)"bytes", Dz1InetTelnetMsgPresent_bytes },
	{ NULL, Dz1InetTelnetMsgPresent_max }
};

str_t Dz1InetTelnetMsgPresentStrA(Dz1InetTelnetMsgPresent v)
{
	struct Dz1InetTelnetMsgPresentMapA *i = NULL;
	for (i = Dz1InetTelnetMsgPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetMsgPresent Dz1InetTelnetMsgPresentFromStrA(str_t str)
{
	struct Dz1InetTelnetMsgPresentMapA *i = NULL;
	for (i = Dz1InetTelnetMsgPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetMsgPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetTelnetMsgPresentMapW
{
	wstr_t str;
	Dz1InetTelnetMsgPresent v;
} Dz1InetTelnetMsgPresentMapW[] =
{
	{ (wchar_t *)L"cmd", Dz1InetTelnetMsgPresent_cmd },
	{ (wchar_t *)L"bytes", Dz1InetTelnetMsgPresent_bytes },
	{ NULL, Dz1InetTelnetMsgPresent_max }
};

wstr_t Dz1InetTelnetMsgPresentStrW(Dz1InetTelnetMsgPresent v)
{
	struct Dz1InetTelnetMsgPresentMapW *i = NULL;
	for (i = Dz1InetTelnetMsgPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetTelnetMsgPresent Dz1InetTelnetMsgPresentFromStrW(wstr_t str)
{
	struct Dz1InetTelnetMsgPresentMapW *i = NULL;
	for (i = Dz1InetTelnetMsgPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetTelnetMsgPresent_max;
}
#endif // UNIX_SYSTEM

Dz1InetTelnetMsgPresent *Dz1InetTelnetMsgPresent_new(Dz1InetTelnetMsgPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetMsgPresent *__internal_ret = (Dz1InetTelnetMsgPresent *)Dz1Calloc(sizeof(Dz1InetTelnetMsgPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1InetTelnetMsgPresent_dump(Dz1InetTelnetMsgPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1InetTelnetMsgPresentStr(*v));
}
// Dz1InetTelnetMsgPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetMsg
Dz1InetTelnetMsg *Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetTelnetMsg *ret = (Dz1InetTelnetMsg *)Dz1Calloc(sizeof(Dz1InetTelnetMsg), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetTelnetMsg_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1InetTelnetMsgPresent_cmd:
			// _U_cst_clone
			if (ptr != NULL) ret->x.cmd = (Dz1InetTelnetCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetMsgPresent_bytes:
			// _U_imp_clone
			if (ptr != NULL) ret->x.bytes = (Dz1Binary *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetTelnetMsgPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetTelnetMsg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetTelnetMsg_purge(Dz1InetTelnetMsg *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1InetTelnetMsgPresent_cmd:
		Dz1InetTelnetCmd_del(p->x.cmd);
		break;
	case Dz1InetTelnetMsgPresent_bytes:
		Dz1Binary_del(p->x.bytes);
		break;
	default:
		break;
	}
}

void Dz1InetTelnetMsg_del(Dz1InetTelnetMsg *p)
{
	if (!p) return;
	Dz1InetTelnetMsg_purge(p);
	Dz1Free(p);
}

void Dz1InetTelnetMsg_dump(Dz1InetTelnetMsg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1InetTelnetMsgPresent_cmd:
		Dz1Thread_printf(Dz1T("cmd.")); Dz1InetTelnetCmd_dump(p->x.cmd, tab); 
		break;
	case Dz1InetTelnetMsgPresent_bytes:
		Dz1Thread_printf(Dz1T("bytes = ")); Dz1Binary_dump(p->x.bytes, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1InetTelnetMsg
////////////////////////////////////////////////////////////////////////////////

