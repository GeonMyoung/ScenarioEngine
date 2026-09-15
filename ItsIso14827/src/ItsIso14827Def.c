////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CRCCheck
static struct ItsIso14827CRCCheckMapA
{
	str_t str;
	ItsIso14827CRCCheck v;
} ItsIso14827CRCCheckMapA[] =
{
	{ (char *)"explict", ItsIso14827CRCCheck_explict },
	{ (char *)"warning", ItsIso14827CRCCheck_warning },
	{ (char *)"ignore", ItsIso14827CRCCheck_ignore },
	{ NULL, ItsIso14827CRCCheck_max }
};

str_t ItsIso14827CRCCheckStrA(ItsIso14827CRCCheck v)
{
	struct ItsIso14827CRCCheckMapA *i = NULL;
	for (i = ItsIso14827CRCCheckMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827CRCCheck ItsIso14827CRCCheckFromStrA(str_t str)
{
	struct ItsIso14827CRCCheckMapA *i = NULL;
	for (i = ItsIso14827CRCCheckMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827CRCCheck_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827CRCCheckMapW
{
	wstr_t str;
	ItsIso14827CRCCheck v;
} ItsIso14827CRCCheckMapW[] =
{
	{ (wchar_t *)L"explict", ItsIso14827CRCCheck_explict },
	{ (wchar_t *)L"warning", ItsIso14827CRCCheck_warning },
	{ (wchar_t *)L"ignore", ItsIso14827CRCCheck_ignore },
	{ NULL, ItsIso14827CRCCheck_max }
};

wstr_t ItsIso14827CRCCheckStrW(ItsIso14827CRCCheck v)
{
	struct ItsIso14827CRCCheckMapW *i = NULL;
	for (i = ItsIso14827CRCCheckMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827CRCCheck ItsIso14827CRCCheckFromStrW(wstr_t str)
{
	struct ItsIso14827CRCCheckMapW *i = NULL;
	for (i = ItsIso14827CRCCheckMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827CRCCheck_max;
}
#endif // UNIX_SYSTEM

ItsIso14827CRCCheck *ItsIso14827CRCCheck_new(ItsIso14827CRCCheck *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827CRCCheck *__internal_ret = (ItsIso14827CRCCheck *)Dz1Calloc(sizeof(ItsIso14827CRCCheck), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ItsIso14827CRCCheck
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainType
static struct ItsIso14827DomainTypeMapA
{
	str_t str;
	ItsIso14827DomainType v;
} ItsIso14827DomainTypeMapA[] =
{
	{ (char *)"server", ItsIso14827DomainType_server },
	{ (char *)"client", ItsIso14827DomainType_client },
	{ NULL, ItsIso14827DomainType_max }
};

str_t ItsIso14827DomainTypeStrA(ItsIso14827DomainType v)
{
	struct ItsIso14827DomainTypeMapA *i = NULL;
	for (i = ItsIso14827DomainTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827DomainType ItsIso14827DomainTypeFromStrA(str_t str)
{
	struct ItsIso14827DomainTypeMapA *i = NULL;
	for (i = ItsIso14827DomainTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827DomainType_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827DomainTypeMapW
{
	wstr_t str;
	ItsIso14827DomainType v;
} ItsIso14827DomainTypeMapW[] =
{
	{ (wchar_t *)L"server", ItsIso14827DomainType_server },
	{ (wchar_t *)L"client", ItsIso14827DomainType_client },
	{ NULL, ItsIso14827DomainType_max }
};

wstr_t ItsIso14827DomainTypeStrW(ItsIso14827DomainType v)
{
	struct ItsIso14827DomainTypeMapW *i = NULL;
	for (i = ItsIso14827DomainTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827DomainType ItsIso14827DomainTypeFromStrW(wstr_t str)
{
	struct ItsIso14827DomainTypeMapW *i = NULL;
	for (i = ItsIso14827DomainTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827DomainType_max;
}
#endif // UNIX_SYSTEM

ItsIso14827DomainType *ItsIso14827DomainType_new(ItsIso14827DomainType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainType *__internal_ret = (ItsIso14827DomainType *)Dz1Calloc(sizeof(ItsIso14827DomainType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ItsIso14827DomainType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827PublicarionErrorPresent
static struct ItsIso14827PublicarionErrorPresentMapA
{
	str_t str;
	ItsIso14827PublicarionErrorPresent v;
} ItsIso14827PublicarionErrorPresentMapA[] =
{
	{ (char *)"pubError", ItsIso14827PublicarionErrorPresent_pubError },
	{ (char *)"pubDataError", ItsIso14827PublicarionErrorPresent_pubDataError },
	{ NULL, ItsIso14827PublicarionErrorPresent_max }
};

str_t ItsIso14827PublicarionErrorPresentStrA(ItsIso14827PublicarionErrorPresent v)
{
	struct ItsIso14827PublicarionErrorPresentMapA *i = NULL;
	for (i = ItsIso14827PublicarionErrorPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827PublicarionErrorPresent ItsIso14827PublicarionErrorPresentFromStrA(str_t str)
{
	struct ItsIso14827PublicarionErrorPresentMapA *i = NULL;
	for (i = ItsIso14827PublicarionErrorPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827PublicarionErrorPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827PublicarionErrorPresentMapW
{
	wstr_t str;
	ItsIso14827PublicarionErrorPresent v;
} ItsIso14827PublicarionErrorPresentMapW[] =
{
	{ (wchar_t *)L"pubError", ItsIso14827PublicarionErrorPresent_pubError },
	{ (wchar_t *)L"pubDataError", ItsIso14827PublicarionErrorPresent_pubDataError },
	{ NULL, ItsIso14827PublicarionErrorPresent_max }
};

wstr_t ItsIso14827PublicarionErrorPresentStrW(ItsIso14827PublicarionErrorPresent v)
{
	struct ItsIso14827PublicarionErrorPresentMapW *i = NULL;
	for (i = ItsIso14827PublicarionErrorPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827PublicarionErrorPresent ItsIso14827PublicarionErrorPresentFromStrW(wstr_t str)
{
	struct ItsIso14827PublicarionErrorPresentMapW *i = NULL;
	for (i = ItsIso14827PublicarionErrorPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827PublicarionErrorPresent_max;
}
#endif // UNIX_SYSTEM

ItsIso14827PublicarionErrorPresent *ItsIso14827PublicarionErrorPresent_new(ItsIso14827PublicarionErrorPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827PublicarionErrorPresent *__internal_ret = (ItsIso14827PublicarionErrorPresent *)Dz1Calloc(sizeof(ItsIso14827PublicarionErrorPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ItsIso14827PublicarionErrorPresent_dump(ItsIso14827PublicarionErrorPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ItsIso14827PublicarionErrorPresentStr(*v));
}
// ItsIso14827PublicarionErrorPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827PublicarionError
ItsIso14827PublicarionError *ItsIso14827PublicarionError_new(ItsIso14827PublicarionErrorPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827PublicarionError *ret = (ItsIso14827PublicarionError *)Dz1Calloc(sizeof(ItsIso14827PublicarionError), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827PublicarionError_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ItsIso14827PublicarionErrorPresent_pubError:
			// _U_enum_clone
			if (ptr != NULL) ret->x.pubError = *(Iso14827RejectPublication *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827PublicarionErrorPresent_pubDataError:
			// _U_enum_clone
			if (ptr != NULL) ret->x.pubDataError = *(Iso14827RejectPubDataReason *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827PublicarionErrorPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827PublicarionError_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t ItsIso14827PublicarionError_copy(ItsIso14827PublicarionError *ret, ItsIso14827PublicarionError *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case ItsIso14827PublicarionErrorPresent_pubError:
			// _U_enum_clone
			ret->x.pubError = src->x.pubError;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827PublicarionErrorPresent_pubDataError:
			// _U_enum_clone
			ret->x.pubDataError = src->x.pubDataError;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827PublicarionError *ItsIso14827PublicarionError_clone(ItsIso14827PublicarionError *src, Dz1Error *err)
{
	ItsIso14827PublicarionError *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (ItsIso14827PublicarionError *)Dz1Calloc(sizeof(ItsIso14827PublicarionError), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827PublicarionError_delAndSetNull, (void *)&ret);
		if (ItsIso14827PublicarionError_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827PublicarionError_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827PublicarionError_purge(ItsIso14827PublicarionError *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ItsIso14827PublicarionErrorPresent_pubError:
		break;
	case ItsIso14827PublicarionErrorPresent_pubDataError:
		break;
	default:
		break;
	}
}

void ItsIso14827PublicarionError_del(ItsIso14827PublicarionError *p)
{
	if (!p) return;
	ItsIso14827PublicarionError_purge(p);
	Dz1Free(p);
}

void ItsIso14827PublicarionError_dump(ItsIso14827PublicarionError *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ItsIso14827PublicarionErrorPresent_pubError:
		Dz1Thread_printf(Dz1T("pubError = %s(%d)\n"), Iso14827RejectPublicationStr(p->x.pubError), p->x.pubError);
		break;
	case ItsIso14827PublicarionErrorPresent_pubDataError:
		Dz1Thread_printf(Dz1T("pubDataError = %s(%d)\n"), Iso14827RejectPubDataReasonStr(p->x.pubDataError), p->x.pubDataError);
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// ItsIso14827PublicarionError
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionExpireReasonPresent
static struct ItsIso14827SubscriptionExpireReasonPresentMapA
{
	str_t str;
	ItsIso14827SubscriptionExpireReasonPresent v;
} ItsIso14827SubscriptionExpireReasonPresentMapA[] =
{
	{ (char *)"subscriptionExpired", ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired },
	{ (char *)"clientDisconnected", ItsIso14827SubscriptionExpireReasonPresent_clientDisconnected },
	{ (char *)"clientRequested", ItsIso14827SubscriptionExpireReasonPresent_clientRequested },
	{ NULL, ItsIso14827SubscriptionExpireReasonPresent_max }
};

str_t ItsIso14827SubscriptionExpireReasonPresentStrA(ItsIso14827SubscriptionExpireReasonPresent v)
{
	struct ItsIso14827SubscriptionExpireReasonPresentMapA *i = NULL;
	for (i = ItsIso14827SubscriptionExpireReasonPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827SubscriptionExpireReasonPresent ItsIso14827SubscriptionExpireReasonPresentFromStrA(str_t str)
{
	struct ItsIso14827SubscriptionExpireReasonPresentMapA *i = NULL;
	for (i = ItsIso14827SubscriptionExpireReasonPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827SubscriptionExpireReasonPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827SubscriptionExpireReasonPresentMapW
{
	wstr_t str;
	ItsIso14827SubscriptionExpireReasonPresent v;
} ItsIso14827SubscriptionExpireReasonPresentMapW[] =
{
	{ (wchar_t *)L"subscriptionExpired", ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired },
	{ (wchar_t *)L"clientDisconnected", ItsIso14827SubscriptionExpireReasonPresent_clientDisconnected },
	{ (wchar_t *)L"clientRequested", ItsIso14827SubscriptionExpireReasonPresent_clientRequested },
	{ NULL, ItsIso14827SubscriptionExpireReasonPresent_max }
};

wstr_t ItsIso14827SubscriptionExpireReasonPresentStrW(ItsIso14827SubscriptionExpireReasonPresent v)
{
	struct ItsIso14827SubscriptionExpireReasonPresentMapW *i = NULL;
	for (i = ItsIso14827SubscriptionExpireReasonPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827SubscriptionExpireReasonPresent ItsIso14827SubscriptionExpireReasonPresentFromStrW(wstr_t str)
{
	struct ItsIso14827SubscriptionExpireReasonPresentMapW *i = NULL;
	for (i = ItsIso14827SubscriptionExpireReasonPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827SubscriptionExpireReasonPresent_max;
}
#endif // UNIX_SYSTEM

ItsIso14827SubscriptionExpireReasonPresent *ItsIso14827SubscriptionExpireReasonPresent_new(ItsIso14827SubscriptionExpireReasonPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionExpireReasonPresent *__internal_ret = (ItsIso14827SubscriptionExpireReasonPresent *)Dz1Calloc(sizeof(ItsIso14827SubscriptionExpireReasonPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ItsIso14827SubscriptionExpireReasonPresent_dump(ItsIso14827SubscriptionExpireReasonPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ItsIso14827SubscriptionExpireReasonPresentStr(*v));
}
// ItsIso14827SubscriptionExpireReasonPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionExpireReason
ItsIso14827SubscriptionExpireReason *ItsIso14827SubscriptionExpireReason_new(ItsIso14827SubscriptionExpireReasonPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionExpireReason *ret = (ItsIso14827SubscriptionExpireReason *)Dz1Calloc(sizeof(ItsIso14827SubscriptionExpireReason), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SubscriptionExpireReason_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired:
			// _U_prim_clone
			if (ptr != NULL) ret->x.subscriptionExpired = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827SubscriptionExpireReasonPresent_clientDisconnected:
			// _U_prim_clone
			if (ptr != NULL) ret->x.clientDisconnected = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827SubscriptionExpireReasonPresent_clientRequested:
			// _U_enum_clone
			if (ptr != NULL) ret->x.clientRequested = *(Iso14827SubscriptionCancel *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827SubscriptionExpireReasonPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscriptionExpireReason_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t ItsIso14827SubscriptionExpireReason_copy(ItsIso14827SubscriptionExpireReason *ret, ItsIso14827SubscriptionExpireReason *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired:
			// _U_prim_clone
			if (src->x.subscriptionExpired && (ret->x.subscriptionExpired = Dz1u32_clone(src->x.subscriptionExpired, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ItsIso14827SubscriptionExpireReasonPresent_clientDisconnected:
			// _U_prim_clone
			if (src->x.clientDisconnected && (ret->x.clientDisconnected = Dz1u32_clone(src->x.clientDisconnected, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ItsIso14827SubscriptionExpireReasonPresent_clientRequested:
			// _U_enum_clone
			ret->x.clientRequested = src->x.clientRequested;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827SubscriptionExpireReason *ItsIso14827SubscriptionExpireReason_clone(ItsIso14827SubscriptionExpireReason *src, Dz1Error *err)
{
	ItsIso14827SubscriptionExpireReason *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (ItsIso14827SubscriptionExpireReason *)Dz1Calloc(sizeof(ItsIso14827SubscriptionExpireReason), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827SubscriptionExpireReason_delAndSetNull, (void *)&ret);
		if (ItsIso14827SubscriptionExpireReason_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscriptionExpireReason_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827SubscriptionExpireReason_purge(ItsIso14827SubscriptionExpireReason *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired:
		Dz1u32_del(p->x.subscriptionExpired);
		break;
	case ItsIso14827SubscriptionExpireReasonPresent_clientDisconnected:
		Dz1u32_del(p->x.clientDisconnected);
		break;
	case ItsIso14827SubscriptionExpireReasonPresent_clientRequested:
		break;
	default:
		break;
	}
}

void ItsIso14827SubscriptionExpireReason_del(ItsIso14827SubscriptionExpireReason *p)
{
	if (!p) return;
	ItsIso14827SubscriptionExpireReason_purge(p);
	Dz1Free(p);
}

void ItsIso14827SubscriptionExpireReason_dump(ItsIso14827SubscriptionExpireReason *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired:
		Dz1Thread_printf(Dz1T("subscriptionExpired = ")); Dz1u32_dump(p->x.subscriptionExpired, tab); 
		break;
	case ItsIso14827SubscriptionExpireReasonPresent_clientDisconnected:
		Dz1Thread_printf(Dz1T("clientDisconnected = ")); Dz1u32_dump(p->x.clientDisconnected, tab); 
		break;
	case ItsIso14827SubscriptionExpireReasonPresent_clientRequested:
		Dz1Thread_printf(Dz1T("clientRequested = %s(%d)\n"), Iso14827SubscriptionCancelStr(p->x.clientRequested), p->x.clientRequested);
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// ItsIso14827SubscriptionExpireReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainCallback
ItsIso14827ServerDomainCallback *ItsIso14827ServerDomainCallback_new(ItsIso14827CallbackAuthenticate authenticate, 
																	 ItsIso14827CallbackEstablished established, 
																	 ItsIso14827CallbackDisconnected disconnected, 
																	 ItsIso14827CallbackEchoRequest echoRequest, 
																	 ItsIso14827CallbackSingle singleRequest, 
																	 ItsIso14827CallbackEventPrepare eventPrepare, 
																	 ItsIso14827CallbackPublicationStart eventStart, 
																	 ItsIso14827CallbackPeriodicPrepare periodicPreapre, 
																	 ItsIso14827CallbackPublicationStart periodicStart, 
																	 ItsIso14827CallbackPublicationInvoke periodicInvoke, 
																	 ItsIso14827CallbackSubscriptionPubInfom pubErrorInform, 
																	 ItsIso14827CallbackSubscriptionStop stopped, 
																	 ItsIso14827CallbackSubscriptionExpire expired, 
																	 ItsIso14827CallbackSysHealthWarning sysHealthWarning, 
																	 void *param, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerDomainCallback *__internal_ret = (ItsIso14827ServerDomainCallback *)Dz1Calloc(sizeof(ItsIso14827ServerDomainCallback), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomainCallback_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->authenticate = authenticate;
		__internal_ret->established = established;
		__internal_ret->disconnected = disconnected;
		__internal_ret->echoRequest = echoRequest;
		__internal_ret->singleRequest = singleRequest;
		__internal_ret->eventPrepare = eventPrepare;
		__internal_ret->eventStart = eventStart;
		__internal_ret->periodicPreapre = periodicPreapre;
		__internal_ret->periodicStart = periodicStart;
		__internal_ret->periodicInvoke = periodicInvoke;
		__internal_ret->pubErrorInform = pubErrorInform;
		__internal_ret->stopped = stopped;
		__internal_ret->expired = expired;
		__internal_ret->sysHealthWarning = sysHealthWarning;
		__internal_ret->param = param;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomainCallback_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerDomainCallback_copy(ItsIso14827ServerDomainCallback *dst, ItsIso14827ServerDomainCallback *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->authenticate = src->authenticate;
		dst->established = src->established;
		dst->disconnected = src->disconnected;
		dst->echoRequest = src->echoRequest;
		dst->singleRequest = src->singleRequest;
		dst->eventPrepare = src->eventPrepare;
		dst->eventStart = src->eventStart;
		dst->periodicPreapre = src->periodicPreapre;
		dst->periodicStart = src->periodicStart;
		dst->periodicInvoke = src->periodicInvoke;
		dst->pubErrorInform = src->pubErrorInform;
		dst->stopped = src->stopped;
		dst->expired = src->expired;
		dst->sysHealthWarning = src->sysHealthWarning;
		dst->param = src->param;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerDomainCallback *ItsIso14827ServerDomainCallback_clone(ItsIso14827ServerDomainCallback *src, Dz1Error *err)
{
	ItsIso14827ServerDomainCallback *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerDomainCallback *)Dz1Calloc(sizeof(ItsIso14827ServerDomainCallback), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomainCallback_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerDomainCallback_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomainCallback_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerDomainCallback_purge(ItsIso14827ServerDomainCallback *p)
{
	if (p == NULL) return;
}

void ItsIso14827ServerDomainCallback_del(ItsIso14827ServerDomainCallback *p)
{
	if (p == NULL) return;
	ItsIso14827ServerDomainCallback_purge(p);
	Dz1Free(p);
}

// ItsIso14827ServerDomainCallback
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainCallback
ItsIso14827ClientDomainCallback *ItsIso14827ClientDomainCallback_new(ItsIso14827CallbackInitiated initiated, 
																	 ItsIso14827CallbackDisconnected echo_responsed, 
																	 ItsIso14827CallbackTerminate terminate, 
																	 ItsIso14827CallbackPublication publication, 
																	 ItsIso14827CallbackPubControl pubControl, 
																	 ItsIso14827CallbackDisconnected disconnected, 
																	 void *param, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomainCallback *__internal_ret = (ItsIso14827ClientDomainCallback *)Dz1Calloc(sizeof(ItsIso14827ClientDomainCallback), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomainCallback_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->initiated = initiated;
		__internal_ret->echo_responsed = echo_responsed;
		__internal_ret->terminate = terminate;
		__internal_ret->publication = publication;
		__internal_ret->pubControl = pubControl;
		__internal_ret->disconnected = disconnected;
		__internal_ret->param = param;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomainCallback_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ClientDomainCallback_copy(ItsIso14827ClientDomainCallback *dst, ItsIso14827ClientDomainCallback *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->initiated = src->initiated;
		dst->echo_responsed = src->echo_responsed;
		dst->terminate = src->terminate;
		dst->publication = src->publication;
		dst->pubControl = src->pubControl;
		dst->disconnected = src->disconnected;
		dst->param = src->param;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ClientDomainCallback *ItsIso14827ClientDomainCallback_clone(ItsIso14827ClientDomainCallback *src, Dz1Error *err)
{
	ItsIso14827ClientDomainCallback *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ClientDomainCallback *)Dz1Calloc(sizeof(ItsIso14827ClientDomainCallback), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomainCallback_delAndSetNull, (void *)&dst);
		if (ItsIso14827ClientDomainCallback_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomainCallback_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ClientDomainCallback_purge(ItsIso14827ClientDomainCallback *p)
{
	if (p == NULL) return;
}

void ItsIso14827ClientDomainCallback_del(ItsIso14827ClientDomainCallback *p)
{
	if (p == NULL) return;
	ItsIso14827ClientDomainCallback_purge(p);
	Dz1Free(p);
}

// ItsIso14827ClientDomainCallback
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventAuth
ItsIso14827ServerEventAuth *ItsIso14827ServerEventAuth_new(Dz1Asn1UTF8Str *myDomain, 
														   Dz1Asn1UTF8Str *peerDomain, 
														   Dz1Asn1OctetStr *user, 
														   Dz1Asn1OctetStr *pass, 
														   Dz1Asn1OctetStr *authInfo, 
														   s32_t hbDur, 
														   s32_t timeout, 
														   u8_t codecBits, 
														   bool_t is_retried, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventAuth *__internal_ret = (ItsIso14827ServerEventAuth *)Dz1Calloc(sizeof(ItsIso14827ServerEventAuth), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventAuth_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->pass = pass;
		__internal_ret->authInfo = authInfo;
		__internal_ret->hbDur = hbDur;
		__internal_ret->timeout = timeout;
		__internal_ret->codecBits = codecBits;
		__internal_ret->is_retried = is_retried;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventAuth_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventAuth_copy(ItsIso14827ServerEventAuth *dst, ItsIso14827ServerEventAuth *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Asn1OctetStr_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else if (src->authInfo && (dst->authInfo = Dz1Asn1OctetStr_clone(src->authInfo, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->hbDur = src->hbDur;
		dst->timeout = src->timeout;
		dst->codecBits = src->codecBits;
		dst->is_retried = src->is_retried;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventAuth *ItsIso14827ServerEventAuth_clone(ItsIso14827ServerEventAuth *src, Dz1Error *err)
{
	ItsIso14827ServerEventAuth *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventAuth *)Dz1Calloc(sizeof(ItsIso14827ServerEventAuth), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventAuth_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventAuth_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventAuth_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventAuth_purge(ItsIso14827ServerEventAuth *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	Dz1Asn1OctetStr_del(p->pass);
	Dz1Asn1OctetStr_del(p->authInfo);
}

void ItsIso14827ServerEventAuth_del(ItsIso14827ServerEventAuth *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventAuth_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventAuth_dump(ItsIso14827ServerEventAuth *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Asn1OctetStr_dump(p->pass, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("authInfo = ")); Dz1Asn1OctetStr_dump(p->authInfo, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hbDur = ")); Dz1s32_dump(&p->hbDur, tab); 
		Dz1Thread_tprintf(tab, Dz1T("timeout = ")); Dz1s32_dump(&p->timeout, tab); 
		Dz1Thread_tprintf(tab, Dz1T("codecBits = ")); Dz1u8_dump(&p->codecBits, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_retried = ")); Dz1Bool_dump(&p->is_retried, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventAuth
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventConnected
ItsIso14827ServerEventConnected *ItsIso14827ServerEventConnected_new(Dz1Asn1UTF8Str *myDomain, 
																	 Dz1Asn1UTF8Str *peerDomain, 
																	 Dz1Asn1OctetStr *user, 
																	 Dz1Asn1Codec selected, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventConnected *__internal_ret = (ItsIso14827ServerEventConnected *)Dz1Calloc(sizeof(ItsIso14827ServerEventConnected), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventConnected_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->selected = selected;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventConnected_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventConnected_copy(ItsIso14827ServerEventConnected *dst, ItsIso14827ServerEventConnected *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->selected = src->selected;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventConnected *ItsIso14827ServerEventConnected_clone(ItsIso14827ServerEventConnected *src, Dz1Error *err)
{
	ItsIso14827ServerEventConnected *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventConnected *)Dz1Calloc(sizeof(ItsIso14827ServerEventConnected), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventConnected_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventConnected_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventConnected_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventConnected_purge(ItsIso14827ServerEventConnected *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827ServerEventConnected_del(ItsIso14827ServerEventConnected *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventConnected_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventConnected_dump(ItsIso14827ServerEventConnected *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("selected = %s(%d)\n"), Dz1Asn1CodecStr(p->selected), p->selected);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventConnected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventEcho
ItsIso14827ServerEventEcho *ItsIso14827ServerEventEcho_new(Dz1Asn1UTF8Str *myDomain, 
														   Dz1Asn1UTF8Str *peerDomain, 
														   Dz1Asn1OctetStr *user, 
														   u32_t echoID, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventEcho *__internal_ret = (ItsIso14827ServerEventEcho *)Dz1Calloc(sizeof(ItsIso14827ServerEventEcho), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventEcho_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->echoID = echoID;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventEcho_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventEcho_copy(ItsIso14827ServerEventEcho *dst, ItsIso14827ServerEventEcho *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->echoID = src->echoID;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventEcho *ItsIso14827ServerEventEcho_clone(ItsIso14827ServerEventEcho *src, Dz1Error *err)
{
	ItsIso14827ServerEventEcho *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventEcho *)Dz1Calloc(sizeof(ItsIso14827ServerEventEcho), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventEcho_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventEcho_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventEcho_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventEcho_purge(ItsIso14827ServerEventEcho *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827ServerEventEcho_del(ItsIso14827ServerEventEcho *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventEcho_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventEcho_dump(ItsIso14827ServerEventEcho *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("echoID = ")); Dz1u32_dump(&p->echoID, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventEcho
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventSubSignle
ItsIso14827ServerEventSubSignle *ItsIso14827ServerEventSubSignle_new(Dz1Asn1UTF8Str *myDomain, 
																	 Dz1Asn1UTF8Str *peerDomain, 
																	 Dz1Asn1OctetStr *user, 
																	 u32_t subID, 
																	 str_t oidStr, 
																	 u8_t *encodedEAM, 
																	 u32_t encodedEAMSize, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventSubSignle *__internal_ret = (ItsIso14827ServerEventSubSignle *)Dz1Calloc(sizeof(ItsIso14827ServerEventSubSignle), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventSubSignle_delAndSetNull, (void *)&__internal_ret);
		
		if (oidStr && (__internal_ret->oidStr = dz1_built_in_str_clone(oidStr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->myDomain = myDomain;
			__internal_ret->peerDomain = peerDomain;
			__internal_ret->user = user;
			__internal_ret->subID = subID;
			__internal_ret->encodedEAM = encodedEAM;
			__internal_ret->encodedEAMSize = encodedEAMSize;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventSubSignle_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventSubSignle_copy(ItsIso14827ServerEventSubSignle *dst, ItsIso14827ServerEventSubSignle *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->oidStr && (dst->oidStr = dz1_built_in_str_clone(src->oidStr, errp)) == NULL) ERR_OUT(errp);
	else if (src->encodedEAM && (dst->encodedEAM = Dz1u8_clone(src->encodedEAM, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subID = src->subID;
		dst->encodedEAMSize = src->encodedEAMSize;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventSubSignle *ItsIso14827ServerEventSubSignle_clone(ItsIso14827ServerEventSubSignle *src, Dz1Error *err)
{
	ItsIso14827ServerEventSubSignle *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventSubSignle *)Dz1Calloc(sizeof(ItsIso14827ServerEventSubSignle), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventSubSignle_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventSubSignle_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventSubSignle_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventSubSignle_purge(ItsIso14827ServerEventSubSignle *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	dz1_built_in_str_del(p->oidStr);
	Dz1u8_del(p->encodedEAM);
}

void ItsIso14827ServerEventSubSignle_del(ItsIso14827ServerEventSubSignle *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventSubSignle_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventSubSignle_dump(ItsIso14827ServerEventSubSignle *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subID = ")); Dz1u32_dump(&p->subID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oidStr = ")); dz1_built_in_str_dump(p->oidStr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAM = ")); Dz1u8_dump(p->encodedEAM, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAMSize = ")); Dz1u32_dump(&p->encodedEAMSize, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventSubSignle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventSubPrepareED
ItsIso14827ServerEventSubPrepareED *ItsIso14827ServerEventSubPrepareED_new(Dz1Asn1UTF8Str *myDomain, 
																		   Dz1Asn1UTF8Str *peerDomain, 
																		   Dz1Asn1OctetStr *user, 
																		   u32_t subID, 
																		   u32_t latency_sec, 
																		   str_t oidStr, 
																		   u8_t *encodedEAM, 
																		   u32_t encodedEAMSize, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventSubPrepareED *__internal_ret = (ItsIso14827ServerEventSubPrepareED *)Dz1Calloc(sizeof(ItsIso14827ServerEventSubPrepareED), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventSubPrepareED_delAndSetNull, (void *)&__internal_ret);
		
		if (oidStr && (__internal_ret->oidStr = dz1_built_in_str_clone(oidStr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->myDomain = myDomain;
			__internal_ret->peerDomain = peerDomain;
			__internal_ret->user = user;
			__internal_ret->subID = subID;
			__internal_ret->latency_sec = latency_sec;
			__internal_ret->encodedEAM = encodedEAM;
			__internal_ret->encodedEAMSize = encodedEAMSize;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventSubPrepareED_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventSubPrepareED_copy(ItsIso14827ServerEventSubPrepareED *dst, ItsIso14827ServerEventSubPrepareED *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->oidStr && (dst->oidStr = dz1_built_in_str_clone(src->oidStr, errp)) == NULL) ERR_OUT(errp);
	else if (src->encodedEAM && (dst->encodedEAM = Dz1u8_clone(src->encodedEAM, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subID = src->subID;
		dst->latency_sec = src->latency_sec;
		dst->encodedEAMSize = src->encodedEAMSize;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventSubPrepareED *ItsIso14827ServerEventSubPrepareED_clone(ItsIso14827ServerEventSubPrepareED *src, Dz1Error *err)
{
	ItsIso14827ServerEventSubPrepareED *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventSubPrepareED *)Dz1Calloc(sizeof(ItsIso14827ServerEventSubPrepareED), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventSubPrepareED_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventSubPrepareED_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventSubPrepareED_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventSubPrepareED_purge(ItsIso14827ServerEventSubPrepareED *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	dz1_built_in_str_del(p->oidStr);
	Dz1u8_del(p->encodedEAM);
}

void ItsIso14827ServerEventSubPrepareED_del(ItsIso14827ServerEventSubPrepareED *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventSubPrepareED_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventSubPrepareED_dump(ItsIso14827ServerEventSubPrepareED *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subID = ")); Dz1u32_dump(&p->subID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("latency_sec = ")); Dz1u32_dump(&p->latency_sec, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oidStr = ")); dz1_built_in_str_dump(p->oidStr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAM = ")); Dz1u8_dump(p->encodedEAM, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAMSize = ")); Dz1u32_dump(&p->encodedEAMSize, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventSubPrepareED
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventSubPrepareP
ItsIso14827ServerEventSubPrepareP *ItsIso14827ServerEventSubPrepareP_new(Dz1Asn1UTF8Str *myDomain, 
																		 Dz1Asn1UTF8Str *peerDomain, 
																		 Dz1Asn1OctetStr *user, 
																		 u32_t subID, 
																		 u32_t period_sec, 
																		 str_t oidStr, 
																		 u8_t *encodedEAM, 
																		 u32_t encodedEAMSize, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventSubPrepareP *__internal_ret = (ItsIso14827ServerEventSubPrepareP *)Dz1Calloc(sizeof(ItsIso14827ServerEventSubPrepareP), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventSubPrepareP_delAndSetNull, (void *)&__internal_ret);
		
		if (oidStr && (__internal_ret->oidStr = dz1_built_in_str_clone(oidStr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->myDomain = myDomain;
			__internal_ret->peerDomain = peerDomain;
			__internal_ret->user = user;
			__internal_ret->subID = subID;
			__internal_ret->period_sec = period_sec;
			__internal_ret->encodedEAM = encodedEAM;
			__internal_ret->encodedEAMSize = encodedEAMSize;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventSubPrepareP_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventSubPrepareP_copy(ItsIso14827ServerEventSubPrepareP *dst, ItsIso14827ServerEventSubPrepareP *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->oidStr && (dst->oidStr = dz1_built_in_str_clone(src->oidStr, errp)) == NULL) ERR_OUT(errp);
	else if (src->encodedEAM && (dst->encodedEAM = Dz1u8_clone(src->encodedEAM, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subID = src->subID;
		dst->period_sec = src->period_sec;
		dst->encodedEAMSize = src->encodedEAMSize;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventSubPrepareP *ItsIso14827ServerEventSubPrepareP_clone(ItsIso14827ServerEventSubPrepareP *src, Dz1Error *err)
{
	ItsIso14827ServerEventSubPrepareP *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventSubPrepareP *)Dz1Calloc(sizeof(ItsIso14827ServerEventSubPrepareP), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventSubPrepareP_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventSubPrepareP_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventSubPrepareP_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventSubPrepareP_purge(ItsIso14827ServerEventSubPrepareP *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	dz1_built_in_str_del(p->oidStr);
	Dz1u8_del(p->encodedEAM);
}

void ItsIso14827ServerEventSubPrepareP_del(ItsIso14827ServerEventSubPrepareP *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventSubPrepareP_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventSubPrepareP_dump(ItsIso14827ServerEventSubPrepareP *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subID = ")); Dz1u32_dump(&p->subID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("period_sec = ")); Dz1u32_dump(&p->period_sec, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oidStr = ")); dz1_built_in_str_dump(p->oidStr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAM = ")); Dz1u8_dump(p->encodedEAM, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAMSize = ")); Dz1u32_dump(&p->encodedEAMSize, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventSubPrepareP
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventPubStart
ItsIso14827ServerEventPubStart *ItsIso14827ServerEventPubStart_new(Dz1Asn1UTF8Str *myDomain, 
																   Dz1Asn1UTF8Str *peerDomain, 
																   Dz1Asn1OctetStr *user, 
																   u32_t subID, 
																   str_t oidStr, 
																   u8_t *encodedEAM, 
																   u32_t encodedEAMSize, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventPubStart *__internal_ret = (ItsIso14827ServerEventPubStart *)Dz1Calloc(sizeof(ItsIso14827ServerEventPubStart), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubStart_delAndSetNull, (void *)&__internal_ret);
		
		if (oidStr && (__internal_ret->oidStr = dz1_built_in_str_clone(oidStr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->myDomain = myDomain;
			__internal_ret->peerDomain = peerDomain;
			__internal_ret->user = user;
			__internal_ret->subID = subID;
			__internal_ret->encodedEAM = encodedEAM;
			__internal_ret->encodedEAMSize = encodedEAMSize;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventPubStart_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventPubStart_copy(ItsIso14827ServerEventPubStart *dst, ItsIso14827ServerEventPubStart *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->oidStr && (dst->oidStr = dz1_built_in_str_clone(src->oidStr, errp)) == NULL) ERR_OUT(errp);
	else if (src->encodedEAM && (dst->encodedEAM = Dz1u8_clone(src->encodedEAM, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subID = src->subID;
		dst->encodedEAMSize = src->encodedEAMSize;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventPubStart *ItsIso14827ServerEventPubStart_clone(ItsIso14827ServerEventPubStart *src, Dz1Error *err)
{
	ItsIso14827ServerEventPubStart *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventPubStart *)Dz1Calloc(sizeof(ItsIso14827ServerEventPubStart), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubStart_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventPubStart_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventPubStart_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventPubStart_purge(ItsIso14827ServerEventPubStart *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	dz1_built_in_str_del(p->oidStr);
	Dz1u8_del(p->encodedEAM);
}

void ItsIso14827ServerEventPubStart_del(ItsIso14827ServerEventPubStart *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventPubStart_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventPubStart_dump(ItsIso14827ServerEventPubStart *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subID = ")); Dz1u32_dump(&p->subID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oidStr = ")); dz1_built_in_str_dump(p->oidStr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAM = ")); Dz1u8_dump(p->encodedEAM, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAMSize = ")); Dz1u32_dump(&p->encodedEAMSize, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventPubStart
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventPubInform
ItsIso14827ServerEventPubInform *ItsIso14827ServerEventPubInform_new(Dz1Asn1UTF8Str *myDomain, 
																	 Dz1Asn1UTF8Str *peerDomain, 
																	 Dz1Asn1OctetStr *user, 
																	 u32_t subID, 
																	 ItsIso14827PublicarionError *reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventPubInform *__internal_ret = (ItsIso14827ServerEventPubInform *)Dz1Calloc(sizeof(ItsIso14827ServerEventPubInform), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubInform_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->subID = subID;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventPubInform_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventPubInform_copy(ItsIso14827ServerEventPubInform *dst, ItsIso14827ServerEventPubInform *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->reason && (dst->reason = ItsIso14827PublicarionError_clone(src->reason, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subID = src->subID;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventPubInform *ItsIso14827ServerEventPubInform_clone(ItsIso14827ServerEventPubInform *src, Dz1Error *err)
{
	ItsIso14827ServerEventPubInform *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventPubInform *)Dz1Calloc(sizeof(ItsIso14827ServerEventPubInform), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubInform_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventPubInform_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventPubInform_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventPubInform_purge(ItsIso14827ServerEventPubInform *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	ItsIso14827PublicarionError_del(p->reason);
}

void ItsIso14827ServerEventPubInform_del(ItsIso14827ServerEventPubInform *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventPubInform_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventPubInform_dump(ItsIso14827ServerEventPubInform *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subID = ")); Dz1u32_dump(&p->subID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason.")); ItsIso14827PublicarionError_dump(p->reason, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventPubInform
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventPubStop
ItsIso14827ServerEventPubStop *ItsIso14827ServerEventPubStop_new(Dz1Asn1UTF8Str *myDomain, 
																 Dz1Asn1UTF8Str *peerDomain, 
																 Dz1Asn1OctetStr *user, 
																 u32_t subID, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventPubStop *__internal_ret = (ItsIso14827ServerEventPubStop *)Dz1Calloc(sizeof(ItsIso14827ServerEventPubStop), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubStop_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->subID = subID;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventPubStop_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventPubStop_copy(ItsIso14827ServerEventPubStop *dst, ItsIso14827ServerEventPubStop *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subID = src->subID;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventPubStop *ItsIso14827ServerEventPubStop_clone(ItsIso14827ServerEventPubStop *src, Dz1Error *err)
{
	ItsIso14827ServerEventPubStop *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventPubStop *)Dz1Calloc(sizeof(ItsIso14827ServerEventPubStop), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubStop_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventPubStop_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventPubStop_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventPubStop_purge(ItsIso14827ServerEventPubStop *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827ServerEventPubStop_del(ItsIso14827ServerEventPubStop *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventPubStop_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventPubStop_dump(ItsIso14827ServerEventPubStop *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subID = ")); Dz1u32_dump(&p->subID, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventPubStop
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerEventPubExpire
ItsIso14827ServerEventPubExpire *ItsIso14827ServerEventPubExpire_new(Dz1Asn1UTF8Str *myDomain, 
																	 Dz1Asn1UTF8Str *peerDomain, 
																	 Dz1Asn1OctetStr *user, 
																	 u32_t subID, 
																	 ItsIso14827SubscriptionExpireReason *reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerEventPubExpire *__internal_ret = (ItsIso14827ServerEventPubExpire *)Dz1Calloc(sizeof(ItsIso14827ServerEventPubExpire), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubExpire_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->subID = subID;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventPubExpire_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerEventPubExpire_copy(ItsIso14827ServerEventPubExpire *dst, ItsIso14827ServerEventPubExpire *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->reason && (dst->reason = ItsIso14827SubscriptionExpireReason_clone(src->reason, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subID = src->subID;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerEventPubExpire *ItsIso14827ServerEventPubExpire_clone(ItsIso14827ServerEventPubExpire *src, Dz1Error *err)
{
	ItsIso14827ServerEventPubExpire *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerEventPubExpire *)Dz1Calloc(sizeof(ItsIso14827ServerEventPubExpire), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubExpire_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerEventPubExpire_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerEventPubExpire_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerEventPubExpire_purge(ItsIso14827ServerEventPubExpire *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	ItsIso14827SubscriptionExpireReason_del(p->reason);
}

void ItsIso14827ServerEventPubExpire_del(ItsIso14827ServerEventPubExpire *p)
{
	if (p == NULL) return;
	ItsIso14827ServerEventPubExpire_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerEventPubExpire_dump(ItsIso14827ServerEventPubExpire *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subID = ")); Dz1u32_dump(&p->subID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason.")); ItsIso14827SubscriptionExpireReason_dump(p->reason, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerEventPubExpire
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientEventInitiate
ItsIso14827ClientEventInitiate *ItsIso14827ClientEventInitiate_new(Dz1Asn1UTF8Str *myDomain, 
																   Dz1Asn1UTF8Str *peerDomain, 
																   Dz1Asn1Codec initial_codec, 
																   ItsIso14827SessionKey *key, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientEventInitiate *__internal_ret = (ItsIso14827ClientEventInitiate *)Dz1Calloc(sizeof(ItsIso14827ClientEventInitiate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventInitiate_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->initial_codec = initial_codec;
		__internal_ret->key = key;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientEventInitiate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ClientEventInitiate_copy(ItsIso14827ClientEventInitiate *dst, ItsIso14827ClientEventInitiate *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->key && (dst->key = ItsIso14827SessionKey_clone(src->key, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->initial_codec = src->initial_codec;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ClientEventInitiate *ItsIso14827ClientEventInitiate_clone(ItsIso14827ClientEventInitiate *src, Dz1Error *err)
{
	ItsIso14827ClientEventInitiate *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ClientEventInitiate *)Dz1Calloc(sizeof(ItsIso14827ClientEventInitiate), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventInitiate_delAndSetNull, (void *)&dst);
		if (ItsIso14827ClientEventInitiate_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientEventInitiate_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ClientEventInitiate_purge(ItsIso14827ClientEventInitiate *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	ItsIso14827SessionKey_del(p->key);
}

void ItsIso14827ClientEventInitiate_del(ItsIso14827ClientEventInitiate *p)
{
	if (p == NULL) return;
	ItsIso14827ClientEventInitiate_purge(p);
	Dz1Free(p);
}

void ItsIso14827ClientEventInitiate_dump(ItsIso14827ClientEventInitiate *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("initial_codec = %s(%d)\n"), Dz1Asn1CodecStr(p->initial_codec), p->initial_codec);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("key = ")); ItsIso14827SessionKey_dump(p->key, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ClientEventInitiate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientEventTerminate
ItsIso14827ClientEventTerminate *ItsIso14827ClientEventTerminate_new(Dz1Asn1UTF8Str *myDomain, 
																	 Dz1Asn1UTF8Str *peerDomain, 
																	 Dz1Asn1OctetStr *user, 
																	 Iso14827Terminate reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientEventTerminate *__internal_ret = (ItsIso14827ClientEventTerminate *)Dz1Calloc(sizeof(ItsIso14827ClientEventTerminate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventTerminate_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientEventTerminate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ClientEventTerminate_copy(ItsIso14827ClientEventTerminate *dst, ItsIso14827ClientEventTerminate *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->reason = src->reason;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ClientEventTerminate *ItsIso14827ClientEventTerminate_clone(ItsIso14827ClientEventTerminate *src, Dz1Error *err)
{
	ItsIso14827ClientEventTerminate *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ClientEventTerminate *)Dz1Calloc(sizeof(ItsIso14827ClientEventTerminate), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventTerminate_delAndSetNull, (void *)&dst);
		if (ItsIso14827ClientEventTerminate_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientEventTerminate_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ClientEventTerminate_purge(ItsIso14827ClientEventTerminate *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827ClientEventTerminate_del(ItsIso14827ClientEventTerminate *p)
{
	if (p == NULL) return;
	ItsIso14827ClientEventTerminate_purge(p);
	Dz1Free(p);
}

void ItsIso14827ClientEventTerminate_dump(ItsIso14827ClientEventTerminate *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827TerminateStr(p->reason), p->reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ClientEventTerminate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientEventPublication
ItsIso14827ClientEventPublication *ItsIso14827ClientEventPublication_new(Dz1Asn1UTF8Str *myDomain, 
																		 Dz1Asn1UTF8Str *peerDomain, 
																		 Dz1Asn1OctetStr *user, 
																		 u32_t sid, 
																		 u32_t pubSerial, 
																		 str_t oidStr, 
																		 u8_t *encodedEAM, 
																		 u32_t encodedEAMSize, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientEventPublication *__internal_ret = (ItsIso14827ClientEventPublication *)Dz1Calloc(sizeof(ItsIso14827ClientEventPublication), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventPublication_delAndSetNull, (void *)&__internal_ret);
		
		if (oidStr && (__internal_ret->oidStr = dz1_built_in_str_clone(oidStr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->myDomain = myDomain;
			__internal_ret->peerDomain = peerDomain;
			__internal_ret->user = user;
			__internal_ret->sid = sid;
			__internal_ret->pubSerial = pubSerial;
			__internal_ret->encodedEAM = encodedEAM;
			__internal_ret->encodedEAMSize = encodedEAMSize;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientEventPublication_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ClientEventPublication_copy(ItsIso14827ClientEventPublication *dst, ItsIso14827ClientEventPublication *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->oidStr && (dst->oidStr = dz1_built_in_str_clone(src->oidStr, errp)) == NULL) ERR_OUT(errp);
	else if (src->encodedEAM && (dst->encodedEAM = Dz1u8_clone(src->encodedEAM, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->sid = src->sid;
		dst->pubSerial = src->pubSerial;
		dst->encodedEAMSize = src->encodedEAMSize;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ClientEventPublication *ItsIso14827ClientEventPublication_clone(ItsIso14827ClientEventPublication *src, Dz1Error *err)
{
	ItsIso14827ClientEventPublication *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ClientEventPublication *)Dz1Calloc(sizeof(ItsIso14827ClientEventPublication), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventPublication_delAndSetNull, (void *)&dst);
		if (ItsIso14827ClientEventPublication_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientEventPublication_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ClientEventPublication_purge(ItsIso14827ClientEventPublication *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	dz1_built_in_str_del(p->oidStr);
	Dz1u8_del(p->encodedEAM);
}

void ItsIso14827ClientEventPublication_del(ItsIso14827ClientEventPublication *p)
{
	if (p == NULL) return;
	ItsIso14827ClientEventPublication_purge(p);
	Dz1Free(p);
}

void ItsIso14827ClientEventPublication_dump(ItsIso14827ClientEventPublication *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sid = ")); Dz1u32_dump(&p->sid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pubSerial = ")); Dz1u32_dump(&p->pubSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oidStr = ")); dz1_built_in_str_dump(p->oidStr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAM = ")); Dz1u8_dump(p->encodedEAM, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encodedEAMSize = ")); Dz1u32_dump(&p->encodedEAMSize, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ClientEventPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientEventPubControl
ItsIso14827ClientEventPubControl *ItsIso14827ClientEventPubControl_new(Dz1Asn1UTF8Str *myDomain, 
																	   Dz1Asn1UTF8Str *peerDomain, 
																	   Dz1Asn1OctetStr *user, 
																	   u32_t sid, 
																	   u32_t pubSerial, 
																	   Iso14827PublicationMgmt cmd, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientEventPubControl *__internal_ret = (ItsIso14827ClientEventPubControl *)Dz1Calloc(sizeof(ItsIso14827ClientEventPubControl), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventPubControl_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->sid = sid;
		__internal_ret->pubSerial = pubSerial;
		__internal_ret->cmd = cmd;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientEventPubControl_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ClientEventPubControl_copy(ItsIso14827ClientEventPubControl *dst, ItsIso14827ClientEventPubControl *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->sid = src->sid;
		dst->pubSerial = src->pubSerial;
		dst->cmd = src->cmd;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ClientEventPubControl *ItsIso14827ClientEventPubControl_clone(ItsIso14827ClientEventPubControl *src, Dz1Error *err)
{
	ItsIso14827ClientEventPubControl *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ClientEventPubControl *)Dz1Calloc(sizeof(ItsIso14827ClientEventPubControl), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventPubControl_delAndSetNull, (void *)&dst);
		if (ItsIso14827ClientEventPubControl_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientEventPubControl_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ClientEventPubControl_purge(ItsIso14827ClientEventPubControl *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827ClientEventPubControl_del(ItsIso14827ClientEventPubControl *p)
{
	if (p == NULL) return;
	ItsIso14827ClientEventPubControl_purge(p);
	Dz1Free(p);
}

void ItsIso14827ClientEventPubControl_dump(ItsIso14827ClientEventPubControl *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sid = ")); Dz1u32_dump(&p->sid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pubSerial = ")); Dz1u32_dump(&p->pubSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("cmd = %s(%d)\n"), Iso14827PublicationMgmtStr(p->cmd), p->cmd);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ClientEventPubControl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827EventDisconnected
ItsIso14827EventDisconnected *ItsIso14827EventDisconnected_new(Dz1Asn1UTF8Str *myDomain, 
															   Dz1Asn1UTF8Str *peerDomain, 
															   Dz1Asn1OctetStr *user, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827EventDisconnected *__internal_ret = (ItsIso14827EventDisconnected *)Dz1Calloc(sizeof(ItsIso14827EventDisconnected), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827EventDisconnected_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827EventDisconnected_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827EventDisconnected_copy(ItsIso14827EventDisconnected *dst, ItsIso14827EventDisconnected *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->myDomain && (dst->myDomain = Dz1Asn1UTF8Str_clone(src->myDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peerDomain && (dst->peerDomain = Dz1Asn1UTF8Str_clone(src->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827EventDisconnected *ItsIso14827EventDisconnected_clone(ItsIso14827EventDisconnected *src, Dz1Error *err)
{
	ItsIso14827EventDisconnected *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827EventDisconnected *)Dz1Calloc(sizeof(ItsIso14827EventDisconnected), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827EventDisconnected_delAndSetNull, (void *)&dst);
		if (ItsIso14827EventDisconnected_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827EventDisconnected_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827EventDisconnected_purge(ItsIso14827EventDisconnected *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827EventDisconnected_del(ItsIso14827EventDisconnected *p)
{
	if (p == NULL) return;
	ItsIso14827EventDisconnected_purge(p);
	Dz1Free(p);
}

void ItsIso14827EventDisconnected_dump(ItsIso14827EventDisconnected *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827EventDisconnected
////////////////////////////////////////////////////////////////////////////////

