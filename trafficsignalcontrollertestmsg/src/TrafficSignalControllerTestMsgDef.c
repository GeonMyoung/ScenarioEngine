////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingRcCmd
static struct CrossControlRingRcCmdMapA
{
	str_t str;
	CrossControlRingRcCmd v;
} CrossControlRingRcCmdMapA[] =
{
	{ (char *)"none", CrossControlRingRcCmd_none },
	{ (char *)"EndPhase1", CrossControlRingRcCmd_EndPhase1 },
	{ (char *)"EndPhase2", CrossControlRingRcCmd_EndPhase2 },
	{ (char *)"EndPhase3", CrossControlRingRcCmd_EndPhase3 },
	{ (char *)"EndPhase4", CrossControlRingRcCmd_EndPhase4 },
	{ (char *)"EndPhase5", CrossControlRingRcCmd_EndPhase5 },
	{ (char *)"EndPhase6", CrossControlRingRcCmd_EndPhase6 },
	{ (char *)"EndPhase7", CrossControlRingRcCmd_EndPhase7 },
	{ (char *)"EndPhase8", CrossControlRingRcCmd_EndPhase8 },
	{ NULL, CrossControlRingRcCmd_max }
};

str_t CrossControlRingRcCmdStrA(CrossControlRingRcCmd v)
{
	struct CrossControlRingRcCmdMapA *i = NULL;
	for (i = CrossControlRingRcCmdMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlRingRcCmd CrossControlRingRcCmdFromStrA(str_t str)
{
	struct CrossControlRingRcCmdMapA *i = NULL;
	for (i = CrossControlRingRcCmdMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return CrossControlRingRcCmd_max;
}
#ifndef UNIX_SYSTEM
static struct CrossControlRingRcCmdMapW
{
	wstr_t str;
	CrossControlRingRcCmd v;
} CrossControlRingRcCmdMapW[] =
{
	{ (wchar_t *)L"none", CrossControlRingRcCmd_none },
	{ (wchar_t *)L"EndPhase1", CrossControlRingRcCmd_EndPhase1 },
	{ (wchar_t *)L"EndPhase2", CrossControlRingRcCmd_EndPhase2 },
	{ (wchar_t *)L"EndPhase3", CrossControlRingRcCmd_EndPhase3 },
	{ (wchar_t *)L"EndPhase4", CrossControlRingRcCmd_EndPhase4 },
	{ (wchar_t *)L"EndPhase5", CrossControlRingRcCmd_EndPhase5 },
	{ (wchar_t *)L"EndPhase6", CrossControlRingRcCmd_EndPhase6 },
	{ (wchar_t *)L"EndPhase7", CrossControlRingRcCmd_EndPhase7 },
	{ (wchar_t *)L"EndPhase8", CrossControlRingRcCmd_EndPhase8 },
	{ NULL, CrossControlRingRcCmd_max }
};

wstr_t CrossControlRingRcCmdStrW(CrossControlRingRcCmd v)
{
	struct CrossControlRingRcCmdMapW *i = NULL;
	for (i = CrossControlRingRcCmdMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlRingRcCmd CrossControlRingRcCmdFromStrW(wstr_t str)
{
	struct CrossControlRingRcCmdMapW *i = NULL;
	for (i = CrossControlRingRcCmdMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return CrossControlRingRcCmd_max;
}
#endif // UNIX_SYSTEM

CrossControlRingRcCmd *CrossControlRingRcCmd_new(CrossControlRingRcCmd *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlRingRcCmd *__internal_ret = (CrossControlRingRcCmd *)Dz1Calloc(sizeof(CrossControlRingRcCmd), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// CrossControlRingRcCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingRcDualCmd
CrossControlRingRcDualCmd *CrossControlRingRcDualCmd_new(CrossControlRingRcCmd ring_b, 
														 CrossControlRingRcCmd ring_a, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlRingRcDualCmd *__internal_ret = (CrossControlRingRcDualCmd *)Dz1Calloc(sizeof(CrossControlRingRcDualCmd), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossControlRingRcDualCmd_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->ring_b = ring_b;
		__internal_ret->ring_a = ring_a;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlRingRcDualCmd_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CrossControlRingRcDualCmd_copy(CrossControlRingRcDualCmd *dst, CrossControlRingRcDualCmd *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->ring_b = src->ring_b;
		dst->ring_a = src->ring_a;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossControlRingRcDualCmd *CrossControlRingRcDualCmd_clone(CrossControlRingRcDualCmd *src, Dz1Error *err)
{
	CrossControlRingRcDualCmd *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CrossControlRingRcDualCmd *)Dz1Calloc(sizeof(CrossControlRingRcDualCmd), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossControlRingRcDualCmd_delAndSetNull, (void *)&dst);
		if (CrossControlRingRcDualCmd_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlRingRcDualCmd_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CrossControlRingRcDualCmd_purge(CrossControlRingRcDualCmd *p)
{
	if (p == NULL) return;
}

void CrossControlRingRcDualCmd_del(CrossControlRingRcDualCmd *p)
{
	if (p == NULL) return;
	CrossControlRingRcDualCmd_purge(p);
	Dz1Free(p);
}

void CrossControlRingRcDualCmd_dump(CrossControlRingRcDualCmd *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("ring_b = %s(%d)\n"), CrossControlRingRcCmdStr(p->ring_b), p->ring_b);
		Dz1Thread_tprintf(tab, Dz1T("ring_a = %s(%d)\n"), CrossControlRingRcCmdStr(p->ring_a), p->ring_a);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CrossControlRingRcDualCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingLcCmd
static struct CrossControlRingLcCmdMapA
{
	str_t str;
	CrossControlRingLcCmd v;
} CrossControlRingLcCmdMapA[] =
{
	{ (char *)"none", CrossControlRingLcCmd_none },
	{ (char *)"SetPhase1", CrossControlRingLcCmd_SetPhase1 },
	{ (char *)"SetPhase2", CrossControlRingLcCmd_SetPhase2 },
	{ (char *)"SetPhase3", CrossControlRingLcCmd_SetPhase3 },
	{ (char *)"SetPhase4", CrossControlRingLcCmd_SetPhase4 },
	{ (char *)"SetPhase5", CrossControlRingLcCmd_SetPhase5 },
	{ (char *)"SetPhase6", CrossControlRingLcCmd_SetPhase6 },
	{ (char *)"SetPhase7", CrossControlRingLcCmd_SetPhase7 },
	{ (char *)"SetPhase8", CrossControlRingLcCmd_SetPhase8 },
	{ (char *)"SetPhaseNext", CrossControlRingLcCmd_SetPhaseNext },
	{ NULL, CrossControlRingLcCmd_max }
};

str_t CrossControlRingLcCmdStrA(CrossControlRingLcCmd v)
{
	struct CrossControlRingLcCmdMapA *i = NULL;
	for (i = CrossControlRingLcCmdMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlRingLcCmd CrossControlRingLcCmdFromStrA(str_t str)
{
	struct CrossControlRingLcCmdMapA *i = NULL;
	for (i = CrossControlRingLcCmdMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return CrossControlRingLcCmd_max;
}
#ifndef UNIX_SYSTEM
static struct CrossControlRingLcCmdMapW
{
	wstr_t str;
	CrossControlRingLcCmd v;
} CrossControlRingLcCmdMapW[] =
{
	{ (wchar_t *)L"none", CrossControlRingLcCmd_none },
	{ (wchar_t *)L"SetPhase1", CrossControlRingLcCmd_SetPhase1 },
	{ (wchar_t *)L"SetPhase2", CrossControlRingLcCmd_SetPhase2 },
	{ (wchar_t *)L"SetPhase3", CrossControlRingLcCmd_SetPhase3 },
	{ (wchar_t *)L"SetPhase4", CrossControlRingLcCmd_SetPhase4 },
	{ (wchar_t *)L"SetPhase5", CrossControlRingLcCmd_SetPhase5 },
	{ (wchar_t *)L"SetPhase6", CrossControlRingLcCmd_SetPhase6 },
	{ (wchar_t *)L"SetPhase7", CrossControlRingLcCmd_SetPhase7 },
	{ (wchar_t *)L"SetPhase8", CrossControlRingLcCmd_SetPhase8 },
	{ (wchar_t *)L"SetPhaseNext", CrossControlRingLcCmd_SetPhaseNext },
	{ NULL, CrossControlRingLcCmd_max }
};

wstr_t CrossControlRingLcCmdStrW(CrossControlRingLcCmd v)
{
	struct CrossControlRingLcCmdMapW *i = NULL;
	for (i = CrossControlRingLcCmdMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlRingLcCmd CrossControlRingLcCmdFromStrW(wstr_t str)
{
	struct CrossControlRingLcCmdMapW *i = NULL;
	for (i = CrossControlRingLcCmdMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return CrossControlRingLcCmd_max;
}
#endif // UNIX_SYSTEM

CrossControlRingLcCmd *CrossControlRingLcCmd_new(CrossControlRingLcCmd *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlRingLcCmd *__internal_ret = (CrossControlRingLcCmd *)Dz1Calloc(sizeof(CrossControlRingLcCmd), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// CrossControlRingLcCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingLcDualCmd
CrossControlRingLcDualCmd *CrossControlRingLcDualCmd_new(CrossControlRingLcCmd ring_b, 
														 CrossControlRingLcCmd ring_a, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlRingLcDualCmd *__internal_ret = (CrossControlRingLcDualCmd *)Dz1Calloc(sizeof(CrossControlRingLcDualCmd), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossControlRingLcDualCmd_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->ring_b = ring_b;
		__internal_ret->ring_a = ring_a;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlRingLcDualCmd_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CrossControlRingLcDualCmd_copy(CrossControlRingLcDualCmd *dst, CrossControlRingLcDualCmd *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->ring_b = src->ring_b;
		dst->ring_a = src->ring_a;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossControlRingLcDualCmd *CrossControlRingLcDualCmd_clone(CrossControlRingLcDualCmd *src, Dz1Error *err)
{
	CrossControlRingLcDualCmd *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CrossControlRingLcDualCmd *)Dz1Calloc(sizeof(CrossControlRingLcDualCmd), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossControlRingLcDualCmd_delAndSetNull, (void *)&dst);
		if (CrossControlRingLcDualCmd_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlRingLcDualCmd_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CrossControlRingLcDualCmd_purge(CrossControlRingLcDualCmd *p)
{
	if (p == NULL) return;
}

void CrossControlRingLcDualCmd_del(CrossControlRingLcDualCmd *p)
{
	if (p == NULL) return;
	CrossControlRingLcDualCmd_purge(p);
	Dz1Free(p);
}

void CrossControlRingLcDualCmd_dump(CrossControlRingLcDualCmd *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("ring_b = %s(%d)\n"), CrossControlRingLcCmdStr(p->ring_b), p->ring_b);
		Dz1Thread_tprintf(tab, Dz1T("ring_a = %s(%d)\n"), CrossControlRingLcCmdStr(p->ring_a), p->ring_a);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CrossControlRingLcDualCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlSingleCmdPresent
static struct CrossControlSingleCmdPresentMapA
{
	str_t str;
	CrossControlSingleCmdPresent v;
} CrossControlSingleCmdPresentMapA[] =
{
	{ (char *)"lc_fixed", CrossControlSingleCmdPresent_lc_fixed },
	{ (char *)"lc_control", CrossControlSingleCmdPresent_lc_control },
	{ (char *)"lc_actuation", CrossControlSingleCmdPresent_lc_actuation },
	{ (char *)"rc_actuation", CrossControlSingleCmdPresent_rc_actuation },
	{ (char *)"rc_online", CrossControlSingleCmdPresent_rc_online },
	{ NULL, CrossControlSingleCmdPresent_max }
};

str_t CrossControlSingleCmdPresentStrA(CrossControlSingleCmdPresent v)
{
	struct CrossControlSingleCmdPresentMapA *i = NULL;
	for (i = CrossControlSingleCmdPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlSingleCmdPresent CrossControlSingleCmdPresentFromStrA(str_t str)
{
	struct CrossControlSingleCmdPresentMapA *i = NULL;
	for (i = CrossControlSingleCmdPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return CrossControlSingleCmdPresent_max;
}
#ifndef UNIX_SYSTEM
static struct CrossControlSingleCmdPresentMapW
{
	wstr_t str;
	CrossControlSingleCmdPresent v;
} CrossControlSingleCmdPresentMapW[] =
{
	{ (wchar_t *)L"lc_fixed", CrossControlSingleCmdPresent_lc_fixed },
	{ (wchar_t *)L"lc_control", CrossControlSingleCmdPresent_lc_control },
	{ (wchar_t *)L"lc_actuation", CrossControlSingleCmdPresent_lc_actuation },
	{ (wchar_t *)L"rc_actuation", CrossControlSingleCmdPresent_rc_actuation },
	{ (wchar_t *)L"rc_online", CrossControlSingleCmdPresent_rc_online },
	{ NULL, CrossControlSingleCmdPresent_max }
};

wstr_t CrossControlSingleCmdPresentStrW(CrossControlSingleCmdPresent v)
{
	struct CrossControlSingleCmdPresentMapW *i = NULL;
	for (i = CrossControlSingleCmdPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlSingleCmdPresent CrossControlSingleCmdPresentFromStrW(wstr_t str)
{
	struct CrossControlSingleCmdPresentMapW *i = NULL;
	for (i = CrossControlSingleCmdPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return CrossControlSingleCmdPresent_max;
}
#endif // UNIX_SYSTEM

CrossControlSingleCmdPresent *CrossControlSingleCmdPresent_new(CrossControlSingleCmdPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlSingleCmdPresent *__internal_ret = (CrossControlSingleCmdPresent *)Dz1Calloc(sizeof(CrossControlSingleCmdPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void CrossControlSingleCmdPresent_dump(CrossControlSingleCmdPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), CrossControlSingleCmdPresentStr(*v));
}
// CrossControlSingleCmdPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlSingleCmd
CrossControlSingleCmd *CrossControlSingleCmd_new(CrossControlSingleCmdPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlSingleCmd *ret = (CrossControlSingleCmd *)Dz1Calloc(sizeof(CrossControlSingleCmd), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossControlSingleCmd_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case CrossControlSingleCmdPresent_lc_fixed:
			// _U_enum_clone
			if (ptr != NULL) ret->x.lc_fixed = *(CrossControlRingLcCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlSingleCmdPresent_lc_control:
			// _U_enum_clone
			if (ptr != NULL) ret->x.lc_control = *(CrossControlRingLcCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlSingleCmdPresent_lc_actuation:
			// _U_enum_clone
			if (ptr != NULL) ret->x.lc_actuation = *(CrossControlRingLcCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlSingleCmdPresent_rc_actuation:
			// _U_enum_clone
			if (ptr != NULL) ret->x.rc_actuation = *(CrossControlRingRcCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlSingleCmdPresent_rc_online:
			// _U_enum_clone
			if (ptr != NULL) ret->x.rc_online = *(CrossControlRingRcCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlSingleCmdPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlSingleCmd_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t CrossControlSingleCmd_copy(CrossControlSingleCmd *ret, CrossControlSingleCmd *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case CrossControlSingleCmdPresent_lc_fixed:
			// _U_enum_clone
			ret->x.lc_fixed = src->x.lc_fixed;
			ERR_CLEAR(errp);
			break;
		case CrossControlSingleCmdPresent_lc_control:
			// _U_enum_clone
			ret->x.lc_control = src->x.lc_control;
			ERR_CLEAR(errp);
			break;
		case CrossControlSingleCmdPresent_lc_actuation:
			// _U_enum_clone
			ret->x.lc_actuation = src->x.lc_actuation;
			ERR_CLEAR(errp);
			break;
		case CrossControlSingleCmdPresent_rc_actuation:
			// _U_enum_clone
			ret->x.rc_actuation = src->x.rc_actuation;
			ERR_CLEAR(errp);
			break;
		case CrossControlSingleCmdPresent_rc_online:
			// _U_enum_clone
			ret->x.rc_online = src->x.rc_online;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossControlSingleCmd *CrossControlSingleCmd_clone(CrossControlSingleCmd *src, Dz1Error *err)
{
	CrossControlSingleCmd *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (CrossControlSingleCmd *)Dz1Calloc(sizeof(CrossControlSingleCmd), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossControlSingleCmd_delAndSetNull, (void *)&ret);
		if (CrossControlSingleCmd_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlSingleCmd_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void CrossControlSingleCmd_purge(CrossControlSingleCmd *p)
{
	if (!p) return;
	switch(p->present)
	{
	case CrossControlSingleCmdPresent_lc_fixed:
		break;
	case CrossControlSingleCmdPresent_lc_control:
		break;
	case CrossControlSingleCmdPresent_lc_actuation:
		break;
	case CrossControlSingleCmdPresent_rc_actuation:
		break;
	case CrossControlSingleCmdPresent_rc_online:
		break;
	default:
		break;
	}
}

void CrossControlSingleCmd_del(CrossControlSingleCmd *p)
{
	if (!p) return;
	CrossControlSingleCmd_purge(p);
	Dz1Free(p);
}

void CrossControlSingleCmd_dump(CrossControlSingleCmd *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case CrossControlSingleCmdPresent_lc_fixed:
		Dz1Thread_printf(Dz1T("lc_fixed = %s(%d)\n"), CrossControlRingLcCmdStr(p->x.lc_fixed), p->x.lc_fixed);
		break;
	case CrossControlSingleCmdPresent_lc_control:
		Dz1Thread_printf(Dz1T("lc_control = %s(%d)\n"), CrossControlRingLcCmdStr(p->x.lc_control), p->x.lc_control);
		break;
	case CrossControlSingleCmdPresent_lc_actuation:
		Dz1Thread_printf(Dz1T("lc_actuation = %s(%d)\n"), CrossControlRingLcCmdStr(p->x.lc_actuation), p->x.lc_actuation);
		break;
	case CrossControlSingleCmdPresent_rc_actuation:
		Dz1Thread_printf(Dz1T("rc_actuation = %s(%d)\n"), CrossControlRingRcCmdStr(p->x.rc_actuation), p->x.rc_actuation);
		break;
	case CrossControlSingleCmdPresent_rc_online:
		Dz1Thread_printf(Dz1T("rc_online = %s(%d)\n"), CrossControlRingRcCmdStr(p->x.rc_online), p->x.rc_online);
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// CrossControlSingleCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlDualCmdPresent
static struct CrossControlDualCmdPresentMapA
{
	str_t str;
	CrossControlDualCmdPresent v;
} CrossControlDualCmdPresentMapA[] =
{
	{ (char *)"lc_fixed", CrossControlDualCmdPresent_lc_fixed },
	{ (char *)"lc_control", CrossControlDualCmdPresent_lc_control },
	{ (char *)"lc_actuation", CrossControlDualCmdPresent_lc_actuation },
	{ (char *)"rc_actuation", CrossControlDualCmdPresent_rc_actuation },
	{ (char *)"rc_online", CrossControlDualCmdPresent_rc_online },
	{ NULL, CrossControlDualCmdPresent_max }
};

str_t CrossControlDualCmdPresentStrA(CrossControlDualCmdPresent v)
{
	struct CrossControlDualCmdPresentMapA *i = NULL;
	for (i = CrossControlDualCmdPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlDualCmdPresent CrossControlDualCmdPresentFromStrA(str_t str)
{
	struct CrossControlDualCmdPresentMapA *i = NULL;
	for (i = CrossControlDualCmdPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return CrossControlDualCmdPresent_max;
}
#ifndef UNIX_SYSTEM
static struct CrossControlDualCmdPresentMapW
{
	wstr_t str;
	CrossControlDualCmdPresent v;
} CrossControlDualCmdPresentMapW[] =
{
	{ (wchar_t *)L"lc_fixed", CrossControlDualCmdPresent_lc_fixed },
	{ (wchar_t *)L"lc_control", CrossControlDualCmdPresent_lc_control },
	{ (wchar_t *)L"lc_actuation", CrossControlDualCmdPresent_lc_actuation },
	{ (wchar_t *)L"rc_actuation", CrossControlDualCmdPresent_rc_actuation },
	{ (wchar_t *)L"rc_online", CrossControlDualCmdPresent_rc_online },
	{ NULL, CrossControlDualCmdPresent_max }
};

wstr_t CrossControlDualCmdPresentStrW(CrossControlDualCmdPresent v)
{
	struct CrossControlDualCmdPresentMapW *i = NULL;
	for (i = CrossControlDualCmdPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlDualCmdPresent CrossControlDualCmdPresentFromStrW(wstr_t str)
{
	struct CrossControlDualCmdPresentMapW *i = NULL;
	for (i = CrossControlDualCmdPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return CrossControlDualCmdPresent_max;
}
#endif // UNIX_SYSTEM

CrossControlDualCmdPresent *CrossControlDualCmdPresent_new(CrossControlDualCmdPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlDualCmdPresent *__internal_ret = (CrossControlDualCmdPresent *)Dz1Calloc(sizeof(CrossControlDualCmdPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void CrossControlDualCmdPresent_dump(CrossControlDualCmdPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), CrossControlDualCmdPresentStr(*v));
}
// CrossControlDualCmdPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlDualCmd
CrossControlDualCmd *CrossControlDualCmd_new(CrossControlDualCmdPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlDualCmd *ret = (CrossControlDualCmd *)Dz1Calloc(sizeof(CrossControlDualCmd), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossControlDualCmd_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case CrossControlDualCmdPresent_lc_fixed:
			// _U_cst_clone
			if (ptr != NULL) ret->x.lc_fixed = (CrossControlRingLcDualCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlDualCmdPresent_lc_control:
			// _U_cst_clone
			if (ptr != NULL) ret->x.lc_control = (CrossControlRingLcDualCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlDualCmdPresent_lc_actuation:
			// _U_cst_clone
			if (ptr != NULL) ret->x.lc_actuation = (CrossControlRingLcDualCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlDualCmdPresent_rc_actuation:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rc_actuation = (CrossControlRingRcDualCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlDualCmdPresent_rc_online:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rc_online = (CrossControlRingRcDualCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlDualCmdPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlDualCmd_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t CrossControlDualCmd_copy(CrossControlDualCmd *ret, CrossControlDualCmd *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case CrossControlDualCmdPresent_lc_fixed:
			// _U_cst_clone
			if (src->x.lc_fixed && (ret->x.lc_fixed = CrossControlRingLcDualCmd_clone(src->x.lc_fixed, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case CrossControlDualCmdPresent_lc_control:
			// _U_cst_clone
			if (src->x.lc_control && (ret->x.lc_control = CrossControlRingLcDualCmd_clone(src->x.lc_control, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case CrossControlDualCmdPresent_lc_actuation:
			// _U_cst_clone
			if (src->x.lc_actuation && (ret->x.lc_actuation = CrossControlRingLcDualCmd_clone(src->x.lc_actuation, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case CrossControlDualCmdPresent_rc_actuation:
			// _U_cst_clone
			if (src->x.rc_actuation && (ret->x.rc_actuation = CrossControlRingRcDualCmd_clone(src->x.rc_actuation, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case CrossControlDualCmdPresent_rc_online:
			// _U_cst_clone
			if (src->x.rc_online && (ret->x.rc_online = CrossControlRingRcDualCmd_clone(src->x.rc_online, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossControlDualCmd *CrossControlDualCmd_clone(CrossControlDualCmd *src, Dz1Error *err)
{
	CrossControlDualCmd *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (CrossControlDualCmd *)Dz1Calloc(sizeof(CrossControlDualCmd), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossControlDualCmd_delAndSetNull, (void *)&ret);
		if (CrossControlDualCmd_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlDualCmd_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void CrossControlDualCmd_purge(CrossControlDualCmd *p)
{
	if (!p) return;
	switch(p->present)
	{
	case CrossControlDualCmdPresent_lc_fixed:
		CrossControlRingLcDualCmd_del(p->x.lc_fixed);
		break;
	case CrossControlDualCmdPresent_lc_control:
		CrossControlRingLcDualCmd_del(p->x.lc_control);
		break;
	case CrossControlDualCmdPresent_lc_actuation:
		CrossControlRingLcDualCmd_del(p->x.lc_actuation);
		break;
	case CrossControlDualCmdPresent_rc_actuation:
		CrossControlRingRcDualCmd_del(p->x.rc_actuation);
		break;
	case CrossControlDualCmdPresent_rc_online:
		CrossControlRingRcDualCmd_del(p->x.rc_online);
		break;
	default:
		break;
	}
}

void CrossControlDualCmd_del(CrossControlDualCmd *p)
{
	if (!p) return;
	CrossControlDualCmd_purge(p);
	Dz1Free(p);
}

void CrossControlDualCmd_dump(CrossControlDualCmd *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case CrossControlDualCmdPresent_lc_fixed:
		Dz1Thread_printf(Dz1T("lc_fixed = ")); CrossControlRingLcDualCmd_dump(p->x.lc_fixed, tab); 
		break;
	case CrossControlDualCmdPresent_lc_control:
		Dz1Thread_printf(Dz1T("lc_control = ")); CrossControlRingLcDualCmd_dump(p->x.lc_control, tab); 
		break;
	case CrossControlDualCmdPresent_lc_actuation:
		Dz1Thread_printf(Dz1T("lc_actuation = ")); CrossControlRingLcDualCmd_dump(p->x.lc_actuation, tab); 
		break;
	case CrossControlDualCmdPresent_rc_actuation:
		Dz1Thread_printf(Dz1T("rc_actuation = ")); CrossControlRingRcDualCmd_dump(p->x.rc_actuation, tab); 
		break;
	case CrossControlDualCmdPresent_rc_online:
		Dz1Thread_printf(Dz1T("rc_online = ")); CrossControlRingRcDualCmd_dump(p->x.rc_online, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// CrossControlDualCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlCmdPresent
static struct CrossControlCmdPresentMapA
{
	str_t str;
	CrossControlCmdPresent v;
} CrossControlCmdPresentMapA[] =
{
	{ (char *)"single", CrossControlCmdPresent_single },
	{ (char *)"dual", CrossControlCmdPresent_dual },
	{ NULL, CrossControlCmdPresent_max }
};

str_t CrossControlCmdPresentStrA(CrossControlCmdPresent v)
{
	struct CrossControlCmdPresentMapA *i = NULL;
	for (i = CrossControlCmdPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlCmdPresent CrossControlCmdPresentFromStrA(str_t str)
{
	struct CrossControlCmdPresentMapA *i = NULL;
	for (i = CrossControlCmdPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return CrossControlCmdPresent_max;
}
#ifndef UNIX_SYSTEM
static struct CrossControlCmdPresentMapW
{
	wstr_t str;
	CrossControlCmdPresent v;
} CrossControlCmdPresentMapW[] =
{
	{ (wchar_t *)L"single", CrossControlCmdPresent_single },
	{ (wchar_t *)L"dual", CrossControlCmdPresent_dual },
	{ NULL, CrossControlCmdPresent_max }
};

wstr_t CrossControlCmdPresentStrW(CrossControlCmdPresent v)
{
	struct CrossControlCmdPresentMapW *i = NULL;
	for (i = CrossControlCmdPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossControlCmdPresent CrossControlCmdPresentFromStrW(wstr_t str)
{
	struct CrossControlCmdPresentMapW *i = NULL;
	for (i = CrossControlCmdPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return CrossControlCmdPresent_max;
}
#endif // UNIX_SYSTEM

CrossControlCmdPresent *CrossControlCmdPresent_new(CrossControlCmdPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlCmdPresent *__internal_ret = (CrossControlCmdPresent *)Dz1Calloc(sizeof(CrossControlCmdPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void CrossControlCmdPresent_dump(CrossControlCmdPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), CrossControlCmdPresentStr(*v));
}
// CrossControlCmdPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlCmd
CrossControlCmd *CrossControlCmd_new(CrossControlCmdPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlCmd *ret = (CrossControlCmd *)Dz1Calloc(sizeof(CrossControlCmd), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossControlCmd_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case CrossControlCmdPresent_single:
			// _U_cst_clone
			if (ptr != NULL) ret->x.single = (CrossControlSingleCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlCmdPresent_dual:
			// _U_cst_clone
			if (ptr != NULL) ret->x.dual = (CrossControlDualCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case CrossControlCmdPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlCmd_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t CrossControlCmd_copy(CrossControlCmd *ret, CrossControlCmd *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case CrossControlCmdPresent_single:
			// _U_cst_clone
			if (src->x.single && (ret->x.single = CrossControlSingleCmd_clone(src->x.single, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case CrossControlCmdPresent_dual:
			// _U_cst_clone
			if (src->x.dual && (ret->x.dual = CrossControlDualCmd_clone(src->x.dual, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossControlCmd *CrossControlCmd_clone(CrossControlCmd *src, Dz1Error *err)
{
	CrossControlCmd *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (CrossControlCmd *)Dz1Calloc(sizeof(CrossControlCmd), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossControlCmd_delAndSetNull, (void *)&ret);
		if (CrossControlCmd_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlCmd_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void CrossControlCmd_purge(CrossControlCmd *p)
{
	if (!p) return;
	switch(p->present)
	{
	case CrossControlCmdPresent_single:
		CrossControlSingleCmd_del(p->x.single);
		break;
	case CrossControlCmdPresent_dual:
		CrossControlDualCmd_del(p->x.dual);
		break;
	default:
		break;
	}
}

void CrossControlCmd_del(CrossControlCmd *p)
{
	if (!p) return;
	CrossControlCmd_purge(p);
	Dz1Free(p);
}

void CrossControlCmd_dump(CrossControlCmd *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case CrossControlCmdPresent_single:
		Dz1Thread_printf(Dz1T("single.")); CrossControlSingleCmd_dump(p->x.single, tab); 
		break;
	case CrossControlCmdPresent_dual:
		Dz1Thread_printf(Dz1T("dual.")); CrossControlDualCmd_dump(p->x.dual, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// CrossControlCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlInformation
CrossControlInformation *CrossControlInformation_new(u8_t cross_id, 
													 CrossControlCmd *command, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossControlInformation *__internal_ret = (CrossControlInformation *)Dz1Calloc(sizeof(CrossControlInformation), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossControlInformation_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->command = command;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlInformation_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CrossControlInformation_copy(CrossControlInformation *dst, CrossControlInformation *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = CrossControlCmd_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossControlInformation *CrossControlInformation_clone(CrossControlInformation *src, Dz1Error *err)
{
	CrossControlInformation *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CrossControlInformation *)Dz1Calloc(sizeof(CrossControlInformation), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossControlInformation_delAndSetNull, (void *)&dst);
		if (CrossControlInformation_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossControlInformation_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CrossControlInformation_purge(CrossControlInformation *p)
{
	if (p == NULL) return;
	CrossControlCmd_del(p->command);
}

void CrossControlInformation_del(CrossControlInformation *p)
{
	if (p == NULL) return;
	CrossControlInformation_purge(p);
	Dz1Free(p);
}

void CrossControlInformation_dump(CrossControlInformation *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("command.")); CrossControlCmd_dump(p->command, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CrossControlInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossIndicator
CrossIndicator *CrossIndicator_new(u8_t cross_id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossIndicator *__internal_ret = (CrossIndicator *)Dz1Calloc(sizeof(CrossIndicator), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossIndicator_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossIndicator_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CrossIndicator_copy(CrossIndicator *dst, CrossIndicator *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossIndicator *CrossIndicator_clone(CrossIndicator *src, Dz1Error *err)
{
	CrossIndicator *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CrossIndicator *)Dz1Calloc(sizeof(CrossIndicator), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossIndicator_delAndSetNull, (void *)&dst);
		if (CrossIndicator_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossIndicator_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CrossIndicator_purge(CrossIndicator *p)
{
	if (p == NULL) return;
}

void CrossIndicator_del(CrossIndicator *p)
{
	if (p == NULL) return;
	CrossIndicator_purge(p);
	Dz1Free(p);
}

void CrossIndicator_dump(CrossIndicator *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
	}
}
// CrossIndicator
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo_OperationMode
static struct CrossStatusBasicInfo_OperationModeMapA
{
	str_t str;
	CrossStatusBasicInfo_OperationMode v;
} CrossStatusBasicInfo_OperationModeMapA[] =
{
	{ (char *)"fixed", CrossStatusBasicInfo_OperationMode_fixed },
	{ (char *)"lc", CrossStatusBasicInfo_OperationMode_lc },
	{ (char *)"lc_actuator", CrossStatusBasicInfo_OperationMode_lc_actuator },
	{ (char *)"rc_actuator", CrossStatusBasicInfo_OperationMode_rc_actuator },
	{ (char *)"rc", CrossStatusBasicInfo_OperationMode_rc },
	{ NULL, CrossStatusBasicInfo_OperationMode_max }
};

str_t CrossStatusBasicInfo_OperationModeStrA(CrossStatusBasicInfo_OperationMode v)
{
	struct CrossStatusBasicInfo_OperationModeMapA *i = NULL;
	for (i = CrossStatusBasicInfo_OperationModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossStatusBasicInfo_OperationMode CrossStatusBasicInfo_OperationModeFromStrA(str_t str)
{
	struct CrossStatusBasicInfo_OperationModeMapA *i = NULL;
	for (i = CrossStatusBasicInfo_OperationModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return CrossStatusBasicInfo_OperationMode_max;
}
#ifndef UNIX_SYSTEM
static struct CrossStatusBasicInfo_OperationModeMapW
{
	wstr_t str;
	CrossStatusBasicInfo_OperationMode v;
} CrossStatusBasicInfo_OperationModeMapW[] =
{
	{ (wchar_t *)L"fixed", CrossStatusBasicInfo_OperationMode_fixed },
	{ (wchar_t *)L"lc", CrossStatusBasicInfo_OperationMode_lc },
	{ (wchar_t *)L"lc_actuator", CrossStatusBasicInfo_OperationMode_lc_actuator },
	{ (wchar_t *)L"rc_actuator", CrossStatusBasicInfo_OperationMode_rc_actuator },
	{ (wchar_t *)L"rc", CrossStatusBasicInfo_OperationMode_rc },
	{ NULL, CrossStatusBasicInfo_OperationMode_max }
};

wstr_t CrossStatusBasicInfo_OperationModeStrW(CrossStatusBasicInfo_OperationMode v)
{
	struct CrossStatusBasicInfo_OperationModeMapW *i = NULL;
	for (i = CrossStatusBasicInfo_OperationModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossStatusBasicInfo_OperationMode CrossStatusBasicInfo_OperationModeFromStrW(wstr_t str)
{
	struct CrossStatusBasicInfo_OperationModeMapW *i = NULL;
	for (i = CrossStatusBasicInfo_OperationModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return CrossStatusBasicInfo_OperationMode_max;
}
#endif // UNIX_SYSTEM

CrossStatusBasicInfo_OperationMode *CrossStatusBasicInfo_OperationMode_new(CrossStatusBasicInfo_OperationMode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossStatusBasicInfo_OperationMode *__internal_ret = (CrossStatusBasicInfo_OperationMode *)Dz1Calloc(sizeof(CrossStatusBasicInfo_OperationMode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// CrossStatusBasicInfo_OperationMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo_BlinkReason
static struct CrossStatusBasicInfo_BlinkReasonMapA
{
	str_t str;
	CrossStatusBasicInfo_BlinkReason v;
} CrossStatusBasicInfo_BlinkReasonMapA[] =
{
	{ (char *)"unknown", CrossStatusBasicInfo_BlinkReason_unknown },
	{ (char *)"power_on", CrossStatusBasicInfo_BlinkReason_power_on },
	{ (char *)"config", CrossStatusBasicInfo_BlinkReason_config },
	{ (char *)"switched", CrossStatusBasicInfo_BlinkReason_switched },
	{ (char *)"contradiction", CrossStatusBasicInfo_BlinkReason_contradiction },
	{ (char *)"db_error", CrossStatusBasicInfo_BlinkReason_db_error },
	{ (char *)"lights_off", CrossStatusBasicInfo_BlinkReason_lights_off },
	{ (char *)"sys_fault", CrossStatusBasicInfo_BlinkReason_sys_fault },
	{ NULL, CrossStatusBasicInfo_BlinkReason_max }
};

str_t CrossStatusBasicInfo_BlinkReasonStrA(CrossStatusBasicInfo_BlinkReason v)
{
	struct CrossStatusBasicInfo_BlinkReasonMapA *i = NULL;
	for (i = CrossStatusBasicInfo_BlinkReasonMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossStatusBasicInfo_BlinkReason CrossStatusBasicInfo_BlinkReasonFromStrA(str_t str)
{
	struct CrossStatusBasicInfo_BlinkReasonMapA *i = NULL;
	for (i = CrossStatusBasicInfo_BlinkReasonMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return CrossStatusBasicInfo_BlinkReason_max;
}
#ifndef UNIX_SYSTEM
static struct CrossStatusBasicInfo_BlinkReasonMapW
{
	wstr_t str;
	CrossStatusBasicInfo_BlinkReason v;
} CrossStatusBasicInfo_BlinkReasonMapW[] =
{
	{ (wchar_t *)L"unknown", CrossStatusBasicInfo_BlinkReason_unknown },
	{ (wchar_t *)L"power_on", CrossStatusBasicInfo_BlinkReason_power_on },
	{ (wchar_t *)L"config", CrossStatusBasicInfo_BlinkReason_config },
	{ (wchar_t *)L"switched", CrossStatusBasicInfo_BlinkReason_switched },
	{ (wchar_t *)L"contradiction", CrossStatusBasicInfo_BlinkReason_contradiction },
	{ (wchar_t *)L"db_error", CrossStatusBasicInfo_BlinkReason_db_error },
	{ (wchar_t *)L"lights_off", CrossStatusBasicInfo_BlinkReason_lights_off },
	{ (wchar_t *)L"sys_fault", CrossStatusBasicInfo_BlinkReason_sys_fault },
	{ NULL, CrossStatusBasicInfo_BlinkReason_max }
};

wstr_t CrossStatusBasicInfo_BlinkReasonStrW(CrossStatusBasicInfo_BlinkReason v)
{
	struct CrossStatusBasicInfo_BlinkReasonMapW *i = NULL;
	for (i = CrossStatusBasicInfo_BlinkReasonMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossStatusBasicInfo_BlinkReason CrossStatusBasicInfo_BlinkReasonFromStrW(wstr_t str)
{
	struct CrossStatusBasicInfo_BlinkReasonMapW *i = NULL;
	for (i = CrossStatusBasicInfo_BlinkReasonMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return CrossStatusBasicInfo_BlinkReason_max;
}
#endif // UNIX_SYSTEM

CrossStatusBasicInfo_BlinkReason *CrossStatusBasicInfo_BlinkReason_new(CrossStatusBasicInfo_BlinkReason *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossStatusBasicInfo_BlinkReason *__internal_ret = (CrossStatusBasicInfo_BlinkReason *)Dz1Calloc(sizeof(CrossStatusBasicInfo_BlinkReason), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// CrossStatusBasicInfo_BlinkReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo
CrossStatusBasicInfo *CrossStatusBasicInfo_new(bool_t power_fail, 
											   bool_t comm_fail, 
											   bool_t lamp_oper, 
											   bool_t is_dual_ring, 
											   bool_t ppc_enabled, 
											   CrossStatusBasicInfo_OperationMode oper_mode, 
											   u8_t ring_a_phase, 
											   u8_t ring_a_step, 
											   u8_t ring_b_phase, 
											   u8_t ring_b_step, 
											   bool_t pannel_is_manual, 
											   bool_t pannel_manual_sw, 
											   bool_t pannel_blink_sw, 
											   bool_t pannel_light_out_sw, 
											   bool_t is_contradiction, 
											   bool_t is_light_out, 
											   bool_t is_blink, 
											   bool_t is_database, 
											   bool_t push_button_enable, 
											   CrossStatusBasicInfo_BlinkReason blink_reason, 
											   bool_t is_timed_left_signal, 
											   bool_t manual_enabled, 
											   bool_t conflict_enabled, 
											   bool_t is_door_opened, 
											   u8_t contradiction_lsu, 
											   bool_t contradiction_from_sw, 
											   u8_t contradiction_curcuit, 
											   u8_t pedestrian_lamp, 
											   u8_t push_button_pending, 
											   u8_t push_button_status, 
											   u8_t opt_board_status, 
											   u8_t period_counter, 
											   u8_t total_period, 
											   u8_t curr_period, 
											   u8_t period_offset, 
											   u8_t hold_phase, 
											   u8_t omit_phase, 
											   bool_t is_four_color_lamp, 
											   u8_t oper_map_id, 
											   bool_t jam_ctrl_enabled, 
											   bool_t jam_ctrl_mode, 
											   bool_t jam_term_early0, 
											   bool_t jam_term_early1, 
											   u16_t firmware_id, 
											   u16_t firmware_idx, 
											   u8_t database_status, 
											   u8_t ppc_control_status, 
											   u8_t ups_control_status, 
											   bool_t map_is_dirty, 
											   bool_t lock_installed, 
											   bool_t lock_is_locked, 
											   bool_t db_is_locked, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossStatusBasicInfo *__internal_ret = (CrossStatusBasicInfo *)Dz1Calloc(sizeof(CrossStatusBasicInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossStatusBasicInfo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->power_fail = power_fail;
		__internal_ret->comm_fail = comm_fail;
		__internal_ret->lamp_oper = lamp_oper;
		__internal_ret->is_dual_ring = is_dual_ring;
		__internal_ret->ppc_enabled = ppc_enabled;
		__internal_ret->oper_mode = oper_mode;
		__internal_ret->ring_a_phase = ring_a_phase;
		__internal_ret->ring_a_step = ring_a_step;
		__internal_ret->ring_b_phase = ring_b_phase;
		__internal_ret->ring_b_step = ring_b_step;
		__internal_ret->pannel_is_manual = pannel_is_manual;
		__internal_ret->pannel_manual_sw = pannel_manual_sw;
		__internal_ret->pannel_blink_sw = pannel_blink_sw;
		__internal_ret->pannel_light_out_sw = pannel_light_out_sw;
		__internal_ret->is_contradiction = is_contradiction;
		__internal_ret->is_light_out = is_light_out;
		__internal_ret->is_blink = is_blink;
		__internal_ret->is_database = is_database;
		__internal_ret->push_button_enable = push_button_enable;
		__internal_ret->blink_reason = blink_reason;
		__internal_ret->is_timed_left_signal = is_timed_left_signal;
		__internal_ret->manual_enabled = manual_enabled;
		__internal_ret->conflict_enabled = conflict_enabled;
		__internal_ret->is_door_opened = is_door_opened;
		__internal_ret->contradiction_lsu = contradiction_lsu;
		__internal_ret->contradiction_from_sw = contradiction_from_sw;
		__internal_ret->contradiction_curcuit = contradiction_curcuit;
		__internal_ret->pedestrian_lamp = pedestrian_lamp;
		__internal_ret->push_button_pending = push_button_pending;
		__internal_ret->push_button_status = push_button_status;
		__internal_ret->opt_board_status = opt_board_status;
		__internal_ret->period_counter = period_counter;
		__internal_ret->total_period = total_period;
		__internal_ret->curr_period = curr_period;
		__internal_ret->period_offset = period_offset;
		__internal_ret->hold_phase = hold_phase;
		__internal_ret->omit_phase = omit_phase;
		__internal_ret->is_four_color_lamp = is_four_color_lamp;
		__internal_ret->oper_map_id = oper_map_id;
		__internal_ret->jam_ctrl_enabled = jam_ctrl_enabled;
		__internal_ret->jam_ctrl_mode = jam_ctrl_mode;
		__internal_ret->jam_term_early0 = jam_term_early0;
		__internal_ret->jam_term_early1 = jam_term_early1;
		__internal_ret->firmware_id = firmware_id;
		__internal_ret->firmware_idx = firmware_idx;
		__internal_ret->database_status = database_status;
		__internal_ret->ppc_control_status = ppc_control_status;
		__internal_ret->ups_control_status = ups_control_status;
		__internal_ret->map_is_dirty = map_is_dirty;
		__internal_ret->lock_installed = lock_installed;
		__internal_ret->lock_is_locked = lock_is_locked;
		__internal_ret->db_is_locked = db_is_locked;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossStatusBasicInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CrossStatusBasicInfo_copy(CrossStatusBasicInfo *dst, CrossStatusBasicInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->power_fail = src->power_fail;
		dst->comm_fail = src->comm_fail;
		dst->lamp_oper = src->lamp_oper;
		dst->is_dual_ring = src->is_dual_ring;
		dst->ppc_enabled = src->ppc_enabled;
		dst->oper_mode = src->oper_mode;
		dst->ring_a_phase = src->ring_a_phase;
		dst->ring_a_step = src->ring_a_step;
		dst->ring_b_phase = src->ring_b_phase;
		dst->ring_b_step = src->ring_b_step;
		dst->pannel_is_manual = src->pannel_is_manual;
		dst->pannel_manual_sw = src->pannel_manual_sw;
		dst->pannel_blink_sw = src->pannel_blink_sw;
		dst->pannel_light_out_sw = src->pannel_light_out_sw;
		dst->is_contradiction = src->is_contradiction;
		dst->is_light_out = src->is_light_out;
		dst->is_blink = src->is_blink;
		dst->is_database = src->is_database;
		dst->push_button_enable = src->push_button_enable;
		dst->blink_reason = src->blink_reason;
		dst->is_timed_left_signal = src->is_timed_left_signal;
		dst->manual_enabled = src->manual_enabled;
		dst->conflict_enabled = src->conflict_enabled;
		dst->is_door_opened = src->is_door_opened;
		dst->contradiction_lsu = src->contradiction_lsu;
		dst->contradiction_from_sw = src->contradiction_from_sw;
		dst->contradiction_curcuit = src->contradiction_curcuit;
		dst->pedestrian_lamp = src->pedestrian_lamp;
		dst->push_button_pending = src->push_button_pending;
		dst->push_button_status = src->push_button_status;
		dst->opt_board_status = src->opt_board_status;
		dst->period_counter = src->period_counter;
		dst->total_period = src->total_period;
		dst->curr_period = src->curr_period;
		dst->period_offset = src->period_offset;
		dst->hold_phase = src->hold_phase;
		dst->omit_phase = src->omit_phase;
		dst->is_four_color_lamp = src->is_four_color_lamp;
		dst->oper_map_id = src->oper_map_id;
		dst->jam_ctrl_enabled = src->jam_ctrl_enabled;
		dst->jam_ctrl_mode = src->jam_ctrl_mode;
		dst->jam_term_early0 = src->jam_term_early0;
		dst->jam_term_early1 = src->jam_term_early1;
		dst->firmware_id = src->firmware_id;
		dst->firmware_idx = src->firmware_idx;
		dst->database_status = src->database_status;
		dst->ppc_control_status = src->ppc_control_status;
		dst->ups_control_status = src->ups_control_status;
		dst->map_is_dirty = src->map_is_dirty;
		dst->lock_installed = src->lock_installed;
		dst->lock_is_locked = src->lock_is_locked;
		dst->db_is_locked = src->db_is_locked;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossStatusBasicInfo *CrossStatusBasicInfo_clone(CrossStatusBasicInfo *src, Dz1Error *err)
{
	CrossStatusBasicInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CrossStatusBasicInfo *)Dz1Calloc(sizeof(CrossStatusBasicInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossStatusBasicInfo_delAndSetNull, (void *)&dst);
		if (CrossStatusBasicInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossStatusBasicInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CrossStatusBasicInfo_purge(CrossStatusBasicInfo *p)
{
	if (p == NULL) return;
}

void CrossStatusBasicInfo_del(CrossStatusBasicInfo *p)
{
	if (p == NULL) return;
	CrossStatusBasicInfo_purge(p);
	Dz1Free(p);
}

void CrossStatusBasicInfo_dump(CrossStatusBasicInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("power_fail = ")); Dz1Bool_dump(&p->power_fail, tab); 
		Dz1Thread_tprintf(tab, Dz1T("comm_fail = ")); Dz1Bool_dump(&p->comm_fail, tab); 
		Dz1Thread_tprintf(tab, Dz1T("lamp_oper = ")); Dz1Bool_dump(&p->lamp_oper, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_dual_ring = ")); Dz1Bool_dump(&p->is_dual_ring, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ppc_enabled = ")); Dz1Bool_dump(&p->ppc_enabled, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oper_mode = %s(%d)\n"), CrossStatusBasicInfo_OperationModeStr(p->oper_mode), p->oper_mode);
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase = ")); Dz1u8_dump(&p->ring_a_phase, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_step = ")); Dz1u8_dump(&p->ring_a_step, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase = ")); Dz1u8_dump(&p->ring_b_phase, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_step = ")); Dz1u8_dump(&p->ring_b_step, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pannel_is_manual = ")); Dz1Bool_dump(&p->pannel_is_manual, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pannel_manual_sw = ")); Dz1Bool_dump(&p->pannel_manual_sw, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pannel_blink_sw = ")); Dz1Bool_dump(&p->pannel_blink_sw, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pannel_light_out_sw = ")); Dz1Bool_dump(&p->pannel_light_out_sw, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_contradiction = ")); Dz1Bool_dump(&p->is_contradiction, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_light_out = ")); Dz1Bool_dump(&p->is_light_out, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_blink = ")); Dz1Bool_dump(&p->is_blink, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_database = ")); Dz1Bool_dump(&p->is_database, tab); 
		Dz1Thread_tprintf(tab, Dz1T("push_button_enable = ")); Dz1Bool_dump(&p->push_button_enable, tab); 
		Dz1Thread_tprintf(tab, Dz1T("blink_reason = %s(%d)\n"), CrossStatusBasicInfo_BlinkReasonStr(p->blink_reason), p->blink_reason);
		Dz1Thread_tprintf(tab, Dz1T("is_timed_left_signal = ")); Dz1Bool_dump(&p->is_timed_left_signal, tab); 
		Dz1Thread_tprintf(tab, Dz1T("manual_enabled = ")); Dz1Bool_dump(&p->manual_enabled, tab); 
		Dz1Thread_tprintf(tab, Dz1T("conflict_enabled = ")); Dz1Bool_dump(&p->conflict_enabled, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_door_opened = ")); Dz1Bool_dump(&p->is_door_opened, tab); 
		Dz1Thread_tprintf(tab, Dz1T("contradiction_lsu = ")); Dz1u8_dump(&p->contradiction_lsu, tab); 
		Dz1Thread_tprintf(tab, Dz1T("contradiction_from_sw = ")); Dz1Bool_dump(&p->contradiction_from_sw, tab); 
		Dz1Thread_tprintf(tab, Dz1T("contradiction_curcuit = ")); Dz1u8_dump(&p->contradiction_curcuit, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pedestrian_lamp = ")); Dz1u8_dump(&p->pedestrian_lamp, tab); 
		Dz1Thread_tprintf(tab, Dz1T("push_button_pending = ")); Dz1u8_dump(&p->push_button_pending, tab); 
		Dz1Thread_tprintf(tab, Dz1T("push_button_status = ")); Dz1u8_dump(&p->push_button_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("opt_board_status = ")); Dz1u8_dump(&p->opt_board_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("period_counter = ")); Dz1u8_dump(&p->period_counter, tab); 
		Dz1Thread_tprintf(tab, Dz1T("total_period = ")); Dz1u8_dump(&p->total_period, tab); 
		Dz1Thread_tprintf(tab, Dz1T("curr_period = ")); Dz1u8_dump(&p->curr_period, tab); 
		Dz1Thread_tprintf(tab, Dz1T("period_offset = ")); Dz1u8_dump(&p->period_offset, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hold_phase = ")); Dz1u8_dump(&p->hold_phase, tab); 
		Dz1Thread_tprintf(tab, Dz1T("omit_phase = ")); Dz1u8_dump(&p->omit_phase, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_four_color_lamp = ")); Dz1Bool_dump(&p->is_four_color_lamp, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oper_map_id = ")); Dz1u8_dump(&p->oper_map_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("jam_ctrl_enabled = ")); Dz1Bool_dump(&p->jam_ctrl_enabled, tab); 
		Dz1Thread_tprintf(tab, Dz1T("jam_ctrl_mode = ")); Dz1Bool_dump(&p->jam_ctrl_mode, tab); 
		Dz1Thread_tprintf(tab, Dz1T("jam_term_early0 = ")); Dz1Bool_dump(&p->jam_term_early0, tab); 
		Dz1Thread_tprintf(tab, Dz1T("jam_term_early1 = ")); Dz1Bool_dump(&p->jam_term_early1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("firmware_id = ")); Dz1u16_dump(&p->firmware_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("firmware_idx = ")); Dz1u16_dump(&p->firmware_idx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("database_status = ")); Dz1u8_dump(&p->database_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ppc_control_status = ")); Dz1u8_dump(&p->ppc_control_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ups_control_status = ")); Dz1u8_dump(&p->ups_control_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("map_is_dirty = ")); Dz1Bool_dump(&p->map_is_dirty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("lock_installed = ")); Dz1Bool_dump(&p->lock_installed, tab); 
		Dz1Thread_tprintf(tab, Dz1T("lock_is_locked = ")); Dz1Bool_dump(&p->lock_is_locked, tab); 
		Dz1Thread_tprintf(tab, Dz1T("db_is_locked = ")); Dz1Bool_dump(&p->db_is_locked, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CrossStatusBasicInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusExtInfo_ContradictionReason
static struct CrossStatusExtInfo_ContradictionReasonMapA
{
	str_t str;
	CrossStatusExtInfo_ContradictionReason v;
} CrossStatusExtInfo_ContradictionReasonMapA[] =
{
	{ (char *)"none", CrossStatusExtInfo_ContradictionReason_none },
	{ (char *)"voltage", CrossStatusExtInfo_ContradictionReason_voltage },
	{ (char *)"current", CrossStatusExtInfo_ContradictionReason_current },
	{ (char *)"map", CrossStatusExtInfo_ContradictionReason_map },
	{ NULL, CrossStatusExtInfo_ContradictionReason_max }
};

str_t CrossStatusExtInfo_ContradictionReasonStrA(CrossStatusExtInfo_ContradictionReason v)
{
	struct CrossStatusExtInfo_ContradictionReasonMapA *i = NULL;
	for (i = CrossStatusExtInfo_ContradictionReasonMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossStatusExtInfo_ContradictionReason CrossStatusExtInfo_ContradictionReasonFromStrA(str_t str)
{
	struct CrossStatusExtInfo_ContradictionReasonMapA *i = NULL;
	for (i = CrossStatusExtInfo_ContradictionReasonMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return CrossStatusExtInfo_ContradictionReason_max;
}
#ifndef UNIX_SYSTEM
static struct CrossStatusExtInfo_ContradictionReasonMapW
{
	wstr_t str;
	CrossStatusExtInfo_ContradictionReason v;
} CrossStatusExtInfo_ContradictionReasonMapW[] =
{
	{ (wchar_t *)L"none", CrossStatusExtInfo_ContradictionReason_none },
	{ (wchar_t *)L"voltage", CrossStatusExtInfo_ContradictionReason_voltage },
	{ (wchar_t *)L"current", CrossStatusExtInfo_ContradictionReason_current },
	{ (wchar_t *)L"map", CrossStatusExtInfo_ContradictionReason_map },
	{ NULL, CrossStatusExtInfo_ContradictionReason_max }
};

wstr_t CrossStatusExtInfo_ContradictionReasonStrW(CrossStatusExtInfo_ContradictionReason v)
{
	struct CrossStatusExtInfo_ContradictionReasonMapW *i = NULL;
	for (i = CrossStatusExtInfo_ContradictionReasonMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

CrossStatusExtInfo_ContradictionReason CrossStatusExtInfo_ContradictionReasonFromStrW(wstr_t str)
{
	struct CrossStatusExtInfo_ContradictionReasonMapW *i = NULL;
	for (i = CrossStatusExtInfo_ContradictionReasonMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return CrossStatusExtInfo_ContradictionReason_max;
}
#endif // UNIX_SYSTEM

CrossStatusExtInfo_ContradictionReason *CrossStatusExtInfo_ContradictionReason_new(CrossStatusExtInfo_ContradictionReason *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossStatusExtInfo_ContradictionReason *__internal_ret = (CrossStatusExtInfo_ContradictionReason *)Dz1Calloc(sizeof(CrossStatusExtInfo_ContradictionReason), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// CrossStatusExtInfo_ContradictionReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusExtInfo_r27
CrossStatusExtInfo_r27 *CrossStatusExtInfo_r27_new(u8_t type, 
												   u8_t ver, 
												   Dz1Binary *ppc_data, 
												   u32_t detector_status, 
												   u8_t mlc_slc_comm_fail, 
												   u8_t contradiction_slc, 
												   CrossStatusExtInfo_ContradictionReason contradiction_prove, 
												   u8_t contradiction_circuit, 
												   u8_t ring_a_phase, 
												   u8_t ring_a_step, 
												   u8_t ring_b_phase, 
												   u8_t ring_b_step, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossStatusExtInfo_r27 *__internal_ret = (CrossStatusExtInfo_r27 *)Dz1Calloc(sizeof(CrossStatusExtInfo_r27), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossStatusExtInfo_r27_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->type = type;
		__internal_ret->ver = ver;
		__internal_ret->ppc_data = ppc_data;
		__internal_ret->detector_status = detector_status;
		__internal_ret->mlc_slc_comm_fail = mlc_slc_comm_fail;
		__internal_ret->contradiction_slc = contradiction_slc;
		__internal_ret->contradiction_prove = contradiction_prove;
		__internal_ret->contradiction_circuit = contradiction_circuit;
		__internal_ret->ring_a_phase = ring_a_phase;
		__internal_ret->ring_a_step = ring_a_step;
		__internal_ret->ring_b_phase = ring_b_phase;
		__internal_ret->ring_b_step = ring_b_step;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossStatusExtInfo_r27_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CrossStatusExtInfo_r27_copy(CrossStatusExtInfo_r27 *dst, CrossStatusExtInfo_r27 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->ppc_data && (dst->ppc_data = Dz1Binary_clone(src->ppc_data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->type = src->type;
		dst->ver = src->ver;
		dst->detector_status = src->detector_status;
		dst->mlc_slc_comm_fail = src->mlc_slc_comm_fail;
		dst->contradiction_slc = src->contradiction_slc;
		dst->contradiction_prove = src->contradiction_prove;
		dst->contradiction_circuit = src->contradiction_circuit;
		dst->ring_a_phase = src->ring_a_phase;
		dst->ring_a_step = src->ring_a_step;
		dst->ring_b_phase = src->ring_b_phase;
		dst->ring_b_step = src->ring_b_step;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossStatusExtInfo_r27 *CrossStatusExtInfo_r27_clone(CrossStatusExtInfo_r27 *src, Dz1Error *err)
{
	CrossStatusExtInfo_r27 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CrossStatusExtInfo_r27 *)Dz1Calloc(sizeof(CrossStatusExtInfo_r27), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossStatusExtInfo_r27_delAndSetNull, (void *)&dst);
		if (CrossStatusExtInfo_r27_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossStatusExtInfo_r27_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CrossStatusExtInfo_r27_purge(CrossStatusExtInfo_r27 *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->ppc_data);
}

void CrossStatusExtInfo_r27_del(CrossStatusExtInfo_r27 *p)
{
	if (p == NULL) return;
	CrossStatusExtInfo_r27_purge(p);
	Dz1Free(p);
}

void CrossStatusExtInfo_r27_dump(CrossStatusExtInfo_r27 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("type = ")); Dz1u8_dump(&p->type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ver = ")); Dz1u8_dump(&p->ver, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("ppc_data = ")); Dz1Binary_dump(p->ppc_data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector_status = ")); Dz1u32_dump(&p->detector_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("mlc_slc_comm_fail = ")); Dz1u8_dump(&p->mlc_slc_comm_fail, tab); 
		Dz1Thread_tprintf(tab, Dz1T("contradiction_slc = ")); Dz1u8_dump(&p->contradiction_slc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("contradiction_prove = %s(%d)\n"), CrossStatusExtInfo_ContradictionReasonStr(p->contradiction_prove), p->contradiction_prove);
		Dz1Thread_tprintf(tab, Dz1T("contradiction_circuit = ")); Dz1u8_dump(&p->contradiction_circuit, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase = ")); Dz1u8_dump(&p->ring_a_phase, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_step = ")); Dz1u8_dump(&p->ring_a_step, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase = ")); Dz1u8_dump(&p->ring_b_phase, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_step = ")); Dz1u8_dump(&p->ring_b_step, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CrossStatusExtInfo_r27
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusExtInfo_r29
CrossStatusExtInfo_r29 *CrossStatusExtInfo_r29_new(u8_t type, 
												   u8_t ver, 
												   Dz1Binary *ppc_data, 
												   u32_t detector_status, 
												   u8_t mlc_slc_comm_fail, 
												   u8_t contradiction_slc, 
												   CrossStatusExtInfo_ContradictionReason contradiction_prove, 
												   u8_t contradiction_circuit, 
												   u8_t ring_a_phase, 
												   u8_t ring_a_step, 
												   u8_t ring_b_phase, 
												   u8_t ring_b_step, 
												   u16_t period_cnt, 
												   u16_t last_period_len, 
												   u16_t current_period, 
												   u16_t offset, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossStatusExtInfo_r29 *__internal_ret = (CrossStatusExtInfo_r29 *)Dz1Calloc(sizeof(CrossStatusExtInfo_r29), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossStatusExtInfo_r29_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->type = type;
		__internal_ret->ver = ver;
		__internal_ret->ppc_data = ppc_data;
		__internal_ret->detector_status = detector_status;
		__internal_ret->mlc_slc_comm_fail = mlc_slc_comm_fail;
		__internal_ret->contradiction_slc = contradiction_slc;
		__internal_ret->contradiction_prove = contradiction_prove;
		__internal_ret->contradiction_circuit = contradiction_circuit;
		__internal_ret->ring_a_phase = ring_a_phase;
		__internal_ret->ring_a_step = ring_a_step;
		__internal_ret->ring_b_phase = ring_b_phase;
		__internal_ret->ring_b_step = ring_b_step;
		__internal_ret->period_cnt = period_cnt;
		__internal_ret->last_period_len = last_period_len;
		__internal_ret->current_period = current_period;
		__internal_ret->offset = offset;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossStatusExtInfo_r29_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CrossStatusExtInfo_r29_copy(CrossStatusExtInfo_r29 *dst, CrossStatusExtInfo_r29 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->ppc_data && (dst->ppc_data = Dz1Binary_clone(src->ppc_data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->type = src->type;
		dst->ver = src->ver;
		dst->detector_status = src->detector_status;
		dst->mlc_slc_comm_fail = src->mlc_slc_comm_fail;
		dst->contradiction_slc = src->contradiction_slc;
		dst->contradiction_prove = src->contradiction_prove;
		dst->contradiction_circuit = src->contradiction_circuit;
		dst->ring_a_phase = src->ring_a_phase;
		dst->ring_a_step = src->ring_a_step;
		dst->ring_b_phase = src->ring_b_phase;
		dst->ring_b_step = src->ring_b_step;
		dst->period_cnt = src->period_cnt;
		dst->last_period_len = src->last_period_len;
		dst->current_period = src->current_period;
		dst->offset = src->offset;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossStatusExtInfo_r29 *CrossStatusExtInfo_r29_clone(CrossStatusExtInfo_r29 *src, Dz1Error *err)
{
	CrossStatusExtInfo_r29 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CrossStatusExtInfo_r29 *)Dz1Calloc(sizeof(CrossStatusExtInfo_r29), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossStatusExtInfo_r29_delAndSetNull, (void *)&dst);
		if (CrossStatusExtInfo_r29_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossStatusExtInfo_r29_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CrossStatusExtInfo_r29_purge(CrossStatusExtInfo_r29 *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->ppc_data);
}

void CrossStatusExtInfo_r29_del(CrossStatusExtInfo_r29 *p)
{
	if (p == NULL) return;
	CrossStatusExtInfo_r29_purge(p);
	Dz1Free(p);
}

void CrossStatusExtInfo_r29_dump(CrossStatusExtInfo_r29 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("type = ")); Dz1u8_dump(&p->type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ver = ")); Dz1u8_dump(&p->ver, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("ppc_data = ")); Dz1Binary_dump(p->ppc_data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector_status = ")); Dz1u32_dump(&p->detector_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("mlc_slc_comm_fail = ")); Dz1u8_dump(&p->mlc_slc_comm_fail, tab); 
		Dz1Thread_tprintf(tab, Dz1T("contradiction_slc = ")); Dz1u8_dump(&p->contradiction_slc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("contradiction_prove = %s(%d)\n"), CrossStatusExtInfo_ContradictionReasonStr(p->contradiction_prove), p->contradiction_prove);
		Dz1Thread_tprintf(tab, Dz1T("contradiction_circuit = ")); Dz1u8_dump(&p->contradiction_circuit, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase = ")); Dz1u8_dump(&p->ring_a_phase, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_step = ")); Dz1u8_dump(&p->ring_a_step, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase = ")); Dz1u8_dump(&p->ring_b_phase, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_step = ")); Dz1u8_dump(&p->ring_b_step, tab); 
		Dz1Thread_tprintf(tab, Dz1T("period_cnt = ")); Dz1u16_dump(&p->period_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("last_period_len = ")); Dz1u16_dump(&p->last_period_len, tab); 
		Dz1Thread_tprintf(tab, Dz1T("current_period = ")); Dz1u16_dump(&p->current_period, tab); 
		Dz1Thread_tprintf(tab, Dz1T("offset = ")); Dz1u16_dump(&p->offset, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CrossStatusExtInfo_r29
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusInformation
CrossStatusInformation *CrossStatusInformation_new(u8_t cross_id, 
												   CrossStatusBasicInfo *lc_status, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CrossStatusInformation *__internal_ret = (CrossStatusInformation *)Dz1Calloc(sizeof(CrossStatusInformation), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CrossStatusInformation_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->lc_status = lc_status;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossStatusInformation_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CrossStatusInformation_copy(CrossStatusInformation *dst, CrossStatusInformation *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->lc_status && (dst->lc_status = CrossStatusBasicInfo_clone(src->lc_status, errp)) == NULL) ERR_OUT(errp);
	else if (src->ex_status && (dst->ex_status = CrossStatusExtInfo_r27_clone(src->ex_status, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CrossStatusInformation *CrossStatusInformation_clone(CrossStatusInformation *src, Dz1Error *err)
{
	CrossStatusInformation *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CrossStatusInformation *)Dz1Calloc(sizeof(CrossStatusInformation), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CrossStatusInformation_delAndSetNull, (void *)&dst);
		if (CrossStatusInformation_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CrossStatusInformation_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CrossStatusInformation_purge(CrossStatusInformation *p)
{
	if (p == NULL) return;
	CrossStatusBasicInfo_del(p->lc_status);
	CrossStatusExtInfo_r27_del(p->ex_status);
}

void CrossStatusInformation_del(CrossStatusInformation *p)
{
	if (p == NULL) return;
	CrossStatusInformation_purge(p);
	Dz1Free(p);
}

void CrossStatusInformation_dump(CrossStatusInformation *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("lc_status = ")); CrossStatusBasicInfo_dump(p->lc_status, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("ex_status = ")); CrossStatusExtInfo_r27_dump(p->ex_status, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CrossStatusInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfoFlagMap
DetectorInfoFlagMap *DetectorInfoFlagMap_new(bool_t bit6, 
											 bool_t bit5, 
											 bool_t bit4, 
											 bool_t bit3, 
											 bool_t bit2, 
											 bool_t bit1, 
											 bool_t bit0, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DetectorInfoFlagMap *__internal_ret = (DetectorInfoFlagMap *)Dz1Calloc(sizeof(DetectorInfoFlagMap), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(DetectorInfoFlagMap_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->bit6 = bit6;
		__internal_ret->bit5 = bit5;
		__internal_ret->bit4 = bit4;
		__internal_ret->bit3 = bit3;
		__internal_ret->bit2 = bit2;
		__internal_ret->bit1 = bit1;
		__internal_ret->bit0 = bit0;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInfoFlagMap_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t DetectorInfoFlagMap_copy(DetectorInfoFlagMap *dst, DetectorInfoFlagMap *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->bit6 = src->bit6;
		dst->bit5 = src->bit5;
		dst->bit4 = src->bit4;
		dst->bit3 = src->bit3;
		dst->bit2 = src->bit2;
		dst->bit1 = src->bit1;
		dst->bit0 = src->bit0;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

DetectorInfoFlagMap *DetectorInfoFlagMap_clone(DetectorInfoFlagMap *src, Dz1Error *err)
{
	DetectorInfoFlagMap *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (DetectorInfoFlagMap *)Dz1Calloc(sizeof(DetectorInfoFlagMap), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(DetectorInfoFlagMap_delAndSetNull, (void *)&dst);
		if (DetectorInfoFlagMap_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInfoFlagMap_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void DetectorInfoFlagMap_purge(DetectorInfoFlagMap *p)
{
	if (p == NULL) return;
}

void DetectorInfoFlagMap_del(DetectorInfoFlagMap *p)
{
	if (p == NULL) return;
	DetectorInfoFlagMap_purge(p);
	Dz1Free(p);
}

void DetectorInfoFlagMap_dump(DetectorInfoFlagMap *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("bit6 = ")); Dz1Bool_dump(&p->bit6, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bit5 = ")); Dz1Bool_dump(&p->bit5, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bit4 = ")); Dz1Bool_dump(&p->bit4, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bit3 = ")); Dz1Bool_dump(&p->bit3, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bit2 = ")); Dz1Bool_dump(&p->bit2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bit1 = ")); Dz1Bool_dump(&p->bit1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bit0 = ")); Dz1Bool_dump(&p->bit0, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// DetectorInfoFlagMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfoFlagMaps
DetectorInfoFlagMaps *DetectorInfoFlagMaps_new(DetectorInfoFlagMap *detector1, 
											   DetectorInfoFlagMap *detector2, 
											   DetectorInfoFlagMap *detector3, 
											   DetectorInfoFlagMap *detector4, 
											   DetectorInfoFlagMap *detector5, 
											   DetectorInfoFlagMap *detector6, 
											   DetectorInfoFlagMap *detector7, 
											   DetectorInfoFlagMap *detector8, 
											   DetectorInfoFlagMap *detector9, 
											   DetectorInfoFlagMap *detector10, 
											   DetectorInfoFlagMap *detector11, 
											   DetectorInfoFlagMap *detector12, 
											   DetectorInfoFlagMap *detector13, 
											   DetectorInfoFlagMap *detector14, 
											   DetectorInfoFlagMap *detector15, 
											   DetectorInfoFlagMap *detector16, 
											   DetectorInfoFlagMap *detector17, 
											   DetectorInfoFlagMap *detector18, 
											   DetectorInfoFlagMap *detector19, 
											   DetectorInfoFlagMap *detector20, 
											   DetectorInfoFlagMap *detector21, 
											   DetectorInfoFlagMap *detector22, 
											   DetectorInfoFlagMap *detector23, 
											   DetectorInfoFlagMap *detector24, 
											   DetectorInfoFlagMap *detector25, 
											   DetectorInfoFlagMap *detector26, 
											   DetectorInfoFlagMap *detector27, 
											   DetectorInfoFlagMap *detector28, 
											   DetectorInfoFlagMap *detector29, 
											   DetectorInfoFlagMap *detector30, 
											   DetectorInfoFlagMap *detector31, 
											   DetectorInfoFlagMap *detector32, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DetectorInfoFlagMaps *__internal_ret = (DetectorInfoFlagMaps *)Dz1Calloc(sizeof(DetectorInfoFlagMaps), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(DetectorInfoFlagMaps_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->detector1 = detector1;
		__internal_ret->detector2 = detector2;
		__internal_ret->detector3 = detector3;
		__internal_ret->detector4 = detector4;
		__internal_ret->detector5 = detector5;
		__internal_ret->detector6 = detector6;
		__internal_ret->detector7 = detector7;
		__internal_ret->detector8 = detector8;
		__internal_ret->detector9 = detector9;
		__internal_ret->detector10 = detector10;
		__internal_ret->detector11 = detector11;
		__internal_ret->detector12 = detector12;
		__internal_ret->detector13 = detector13;
		__internal_ret->detector14 = detector14;
		__internal_ret->detector15 = detector15;
		__internal_ret->detector16 = detector16;
		__internal_ret->detector17 = detector17;
		__internal_ret->detector18 = detector18;
		__internal_ret->detector19 = detector19;
		__internal_ret->detector20 = detector20;
		__internal_ret->detector21 = detector21;
		__internal_ret->detector22 = detector22;
		__internal_ret->detector23 = detector23;
		__internal_ret->detector24 = detector24;
		__internal_ret->detector25 = detector25;
		__internal_ret->detector26 = detector26;
		__internal_ret->detector27 = detector27;
		__internal_ret->detector28 = detector28;
		__internal_ret->detector29 = detector29;
		__internal_ret->detector30 = detector30;
		__internal_ret->detector31 = detector31;
		__internal_ret->detector32 = detector32;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInfoFlagMaps_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t DetectorInfoFlagMaps_copy(DetectorInfoFlagMaps *dst, DetectorInfoFlagMaps *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->detector1 && (dst->detector1 = DetectorInfoFlagMap_clone(src->detector1, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector2 && (dst->detector2 = DetectorInfoFlagMap_clone(src->detector2, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector3 && (dst->detector3 = DetectorInfoFlagMap_clone(src->detector3, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector4 && (dst->detector4 = DetectorInfoFlagMap_clone(src->detector4, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector5 && (dst->detector5 = DetectorInfoFlagMap_clone(src->detector5, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector6 && (dst->detector6 = DetectorInfoFlagMap_clone(src->detector6, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector7 && (dst->detector7 = DetectorInfoFlagMap_clone(src->detector7, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector8 && (dst->detector8 = DetectorInfoFlagMap_clone(src->detector8, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector9 && (dst->detector9 = DetectorInfoFlagMap_clone(src->detector9, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector10 && (dst->detector10 = DetectorInfoFlagMap_clone(src->detector10, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector11 && (dst->detector11 = DetectorInfoFlagMap_clone(src->detector11, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector12 && (dst->detector12 = DetectorInfoFlagMap_clone(src->detector12, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector13 && (dst->detector13 = DetectorInfoFlagMap_clone(src->detector13, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector14 && (dst->detector14 = DetectorInfoFlagMap_clone(src->detector14, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector15 && (dst->detector15 = DetectorInfoFlagMap_clone(src->detector15, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector16 && (dst->detector16 = DetectorInfoFlagMap_clone(src->detector16, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector17 && (dst->detector17 = DetectorInfoFlagMap_clone(src->detector17, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector18 && (dst->detector18 = DetectorInfoFlagMap_clone(src->detector18, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector19 && (dst->detector19 = DetectorInfoFlagMap_clone(src->detector19, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector20 && (dst->detector20 = DetectorInfoFlagMap_clone(src->detector20, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector21 && (dst->detector21 = DetectorInfoFlagMap_clone(src->detector21, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector22 && (dst->detector22 = DetectorInfoFlagMap_clone(src->detector22, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector23 && (dst->detector23 = DetectorInfoFlagMap_clone(src->detector23, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector24 && (dst->detector24 = DetectorInfoFlagMap_clone(src->detector24, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector25 && (dst->detector25 = DetectorInfoFlagMap_clone(src->detector25, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector26 && (dst->detector26 = DetectorInfoFlagMap_clone(src->detector26, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector27 && (dst->detector27 = DetectorInfoFlagMap_clone(src->detector27, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector28 && (dst->detector28 = DetectorInfoFlagMap_clone(src->detector28, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector29 && (dst->detector29 = DetectorInfoFlagMap_clone(src->detector29, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector30 && (dst->detector30 = DetectorInfoFlagMap_clone(src->detector30, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector31 && (dst->detector31 = DetectorInfoFlagMap_clone(src->detector31, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector32 && (dst->detector32 = DetectorInfoFlagMap_clone(src->detector32, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

DetectorInfoFlagMaps *DetectorInfoFlagMaps_clone(DetectorInfoFlagMaps *src, Dz1Error *err)
{
	DetectorInfoFlagMaps *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (DetectorInfoFlagMaps *)Dz1Calloc(sizeof(DetectorInfoFlagMaps), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(DetectorInfoFlagMaps_delAndSetNull, (void *)&dst);
		if (DetectorInfoFlagMaps_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInfoFlagMaps_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void DetectorInfoFlagMaps_purge(DetectorInfoFlagMaps *p)
{
	if (p == NULL) return;
	DetectorInfoFlagMap_del(p->detector1);
	DetectorInfoFlagMap_del(p->detector2);
	DetectorInfoFlagMap_del(p->detector3);
	DetectorInfoFlagMap_del(p->detector4);
	DetectorInfoFlagMap_del(p->detector5);
	DetectorInfoFlagMap_del(p->detector6);
	DetectorInfoFlagMap_del(p->detector7);
	DetectorInfoFlagMap_del(p->detector8);
	DetectorInfoFlagMap_del(p->detector9);
	DetectorInfoFlagMap_del(p->detector10);
	DetectorInfoFlagMap_del(p->detector11);
	DetectorInfoFlagMap_del(p->detector12);
	DetectorInfoFlagMap_del(p->detector13);
	DetectorInfoFlagMap_del(p->detector14);
	DetectorInfoFlagMap_del(p->detector15);
	DetectorInfoFlagMap_del(p->detector16);
	DetectorInfoFlagMap_del(p->detector17);
	DetectorInfoFlagMap_del(p->detector18);
	DetectorInfoFlagMap_del(p->detector19);
	DetectorInfoFlagMap_del(p->detector20);
	DetectorInfoFlagMap_del(p->detector21);
	DetectorInfoFlagMap_del(p->detector22);
	DetectorInfoFlagMap_del(p->detector23);
	DetectorInfoFlagMap_del(p->detector24);
	DetectorInfoFlagMap_del(p->detector25);
	DetectorInfoFlagMap_del(p->detector26);
	DetectorInfoFlagMap_del(p->detector27);
	DetectorInfoFlagMap_del(p->detector28);
	DetectorInfoFlagMap_del(p->detector29);
	DetectorInfoFlagMap_del(p->detector30);
	DetectorInfoFlagMap_del(p->detector31);
	DetectorInfoFlagMap_del(p->detector32);
}

void DetectorInfoFlagMaps_del(DetectorInfoFlagMaps *p)
{
	if (p == NULL) return;
	DetectorInfoFlagMaps_purge(p);
	Dz1Free(p);
}

void DetectorInfoFlagMaps_dump(DetectorInfoFlagMaps *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector1 = ")); DetectorInfoFlagMap_dump(p->detector1, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector2 = ")); DetectorInfoFlagMap_dump(p->detector2, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector3 = ")); DetectorInfoFlagMap_dump(p->detector3, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector4 = ")); DetectorInfoFlagMap_dump(p->detector4, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector5 = ")); DetectorInfoFlagMap_dump(p->detector5, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector6 = ")); DetectorInfoFlagMap_dump(p->detector6, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector7 = ")); DetectorInfoFlagMap_dump(p->detector7, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector8 = ")); DetectorInfoFlagMap_dump(p->detector8, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector9 = ")); DetectorInfoFlagMap_dump(p->detector9, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector10 = ")); DetectorInfoFlagMap_dump(p->detector10, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector11 = ")); DetectorInfoFlagMap_dump(p->detector11, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector12 = ")); DetectorInfoFlagMap_dump(p->detector12, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector13 = ")); DetectorInfoFlagMap_dump(p->detector13, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector14 = ")); DetectorInfoFlagMap_dump(p->detector14, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector15 = ")); DetectorInfoFlagMap_dump(p->detector15, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector16 = ")); DetectorInfoFlagMap_dump(p->detector16, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector17 = ")); DetectorInfoFlagMap_dump(p->detector17, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector18 = ")); DetectorInfoFlagMap_dump(p->detector18, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector19 = ")); DetectorInfoFlagMap_dump(p->detector19, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector20 = ")); DetectorInfoFlagMap_dump(p->detector20, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector21 = ")); DetectorInfoFlagMap_dump(p->detector21, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector22 = ")); DetectorInfoFlagMap_dump(p->detector22, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector23 = ")); DetectorInfoFlagMap_dump(p->detector23, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector24 = ")); DetectorInfoFlagMap_dump(p->detector24, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector25 = ")); DetectorInfoFlagMap_dump(p->detector25, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector26 = ")); DetectorInfoFlagMap_dump(p->detector26, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector27 = ")); DetectorInfoFlagMap_dump(p->detector27, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector28 = ")); DetectorInfoFlagMap_dump(p->detector28, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector29 = ")); DetectorInfoFlagMap_dump(p->detector29, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector30 = ")); DetectorInfoFlagMap_dump(p->detector30, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector31 = ")); DetectorInfoFlagMap_dump(p->detector31, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector32 = ")); DetectorInfoFlagMap_dump(p->detector32, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// DetectorInfoFlagMaps
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfoValueMap
DetectorInfoValueMap *DetectorInfoValueMap_new(u8_t detector1, 
											   u8_t detector2, 
											   u8_t detector3, 
											   u8_t detector4, 
											   u8_t detector5, 
											   u8_t detector6, 
											   u8_t detector7, 
											   u8_t detector8, 
											   u8_t detector9, 
											   u8_t detector10, 
											   u8_t detector11, 
											   u8_t detector12, 
											   u8_t detector13, 
											   u8_t detector14, 
											   u8_t detector15, 
											   u8_t detector16, 
											   u8_t detector17, 
											   u8_t detector18, 
											   u8_t detector19, 
											   u8_t detector20, 
											   u8_t detector21, 
											   u8_t detector22, 
											   u8_t detector23, 
											   u8_t detector24, 
											   u8_t detector25, 
											   u8_t detector26, 
											   u8_t detector27, 
											   u8_t detector28, 
											   u8_t detector29, 
											   u8_t detector30, 
											   u8_t detector31, 
											   u8_t detector32, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DetectorInfoValueMap *__internal_ret = (DetectorInfoValueMap *)Dz1Calloc(sizeof(DetectorInfoValueMap), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(DetectorInfoValueMap_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->detector1 = detector1;
		__internal_ret->detector2 = detector2;
		__internal_ret->detector3 = detector3;
		__internal_ret->detector4 = detector4;
		__internal_ret->detector5 = detector5;
		__internal_ret->detector6 = detector6;
		__internal_ret->detector7 = detector7;
		__internal_ret->detector8 = detector8;
		__internal_ret->detector9 = detector9;
		__internal_ret->detector10 = detector10;
		__internal_ret->detector11 = detector11;
		__internal_ret->detector12 = detector12;
		__internal_ret->detector13 = detector13;
		__internal_ret->detector14 = detector14;
		__internal_ret->detector15 = detector15;
		__internal_ret->detector16 = detector16;
		__internal_ret->detector17 = detector17;
		__internal_ret->detector18 = detector18;
		__internal_ret->detector19 = detector19;
		__internal_ret->detector20 = detector20;
		__internal_ret->detector21 = detector21;
		__internal_ret->detector22 = detector22;
		__internal_ret->detector23 = detector23;
		__internal_ret->detector24 = detector24;
		__internal_ret->detector25 = detector25;
		__internal_ret->detector26 = detector26;
		__internal_ret->detector27 = detector27;
		__internal_ret->detector28 = detector28;
		__internal_ret->detector29 = detector29;
		__internal_ret->detector30 = detector30;
		__internal_ret->detector31 = detector31;
		__internal_ret->detector32 = detector32;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInfoValueMap_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t DetectorInfoValueMap_copy(DetectorInfoValueMap *dst, DetectorInfoValueMap *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->detector1 = src->detector1;
		dst->detector2 = src->detector2;
		dst->detector3 = src->detector3;
		dst->detector4 = src->detector4;
		dst->detector5 = src->detector5;
		dst->detector6 = src->detector6;
		dst->detector7 = src->detector7;
		dst->detector8 = src->detector8;
		dst->detector9 = src->detector9;
		dst->detector10 = src->detector10;
		dst->detector11 = src->detector11;
		dst->detector12 = src->detector12;
		dst->detector13 = src->detector13;
		dst->detector14 = src->detector14;
		dst->detector15 = src->detector15;
		dst->detector16 = src->detector16;
		dst->detector17 = src->detector17;
		dst->detector18 = src->detector18;
		dst->detector19 = src->detector19;
		dst->detector20 = src->detector20;
		dst->detector21 = src->detector21;
		dst->detector22 = src->detector22;
		dst->detector23 = src->detector23;
		dst->detector24 = src->detector24;
		dst->detector25 = src->detector25;
		dst->detector26 = src->detector26;
		dst->detector27 = src->detector27;
		dst->detector28 = src->detector28;
		dst->detector29 = src->detector29;
		dst->detector30 = src->detector30;
		dst->detector31 = src->detector31;
		dst->detector32 = src->detector32;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

DetectorInfoValueMap *DetectorInfoValueMap_clone(DetectorInfoValueMap *src, Dz1Error *err)
{
	DetectorInfoValueMap *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (DetectorInfoValueMap *)Dz1Calloc(sizeof(DetectorInfoValueMap), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(DetectorInfoValueMap_delAndSetNull, (void *)&dst);
		if (DetectorInfoValueMap_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInfoValueMap_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void DetectorInfoValueMap_purge(DetectorInfoValueMap *p)
{
	if (p == NULL) return;
}

void DetectorInfoValueMap_del(DetectorInfoValueMap *p)
{
	if (p == NULL) return;
	DetectorInfoValueMap_purge(p);
	Dz1Free(p);
}

void DetectorInfoValueMap_dump(DetectorInfoValueMap *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("detector1 = ")); Dz1u8_dump(&p->detector1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector2 = ")); Dz1u8_dump(&p->detector2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector3 = ")); Dz1u8_dump(&p->detector3, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector4 = ")); Dz1u8_dump(&p->detector4, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector5 = ")); Dz1u8_dump(&p->detector5, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector6 = ")); Dz1u8_dump(&p->detector6, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector7 = ")); Dz1u8_dump(&p->detector7, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector8 = ")); Dz1u8_dump(&p->detector8, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector9 = ")); Dz1u8_dump(&p->detector9, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector10 = ")); Dz1u8_dump(&p->detector10, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector11 = ")); Dz1u8_dump(&p->detector11, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector12 = ")); Dz1u8_dump(&p->detector12, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector13 = ")); Dz1u8_dump(&p->detector13, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector14 = ")); Dz1u8_dump(&p->detector14, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector15 = ")); Dz1u8_dump(&p->detector15, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector16 = ")); Dz1u8_dump(&p->detector16, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector17 = ")); Dz1u8_dump(&p->detector17, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector18 = ")); Dz1u8_dump(&p->detector18, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector19 = ")); Dz1u8_dump(&p->detector19, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector20 = ")); Dz1u8_dump(&p->detector20, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector21 = ")); Dz1u8_dump(&p->detector21, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector22 = ")); Dz1u8_dump(&p->detector22, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector23 = ")); Dz1u8_dump(&p->detector23, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector24 = ")); Dz1u8_dump(&p->detector24, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector25 = ")); Dz1u8_dump(&p->detector25, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector26 = ")); Dz1u8_dump(&p->detector26, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector27 = ")); Dz1u8_dump(&p->detector27, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector28 = ")); Dz1u8_dump(&p->detector28, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector29 = ")); Dz1u8_dump(&p->detector29, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector30 = ")); Dz1u8_dump(&p->detector30, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector31 = ")); Dz1u8_dump(&p->detector31, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector32 = ")); Dz1u8_dump(&p->detector32, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// DetectorInfoValueMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfo
DetectorInfo *DetectorInfo_new(DetectorInfoFlagMaps *detector_info_flags, 
							   DetectorInfoValueMap *detector_not_occupy_times, 
							   DetectorInfoValueMap *detector_occupy_times, 
							   DetectorInfoValueMap *detector_traffic_volumes, 
							   DetectorInfoValueMap *detector_traffic_saturations, 
							   DetectorInfoValueMap *detector_saturation_flow_rate_per_speeds, 
							   DetectorInfoValueMap *detector_saturation_not_ocuppy_time, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DetectorInfo *__internal_ret = (DetectorInfo *)Dz1Calloc(sizeof(DetectorInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(DetectorInfo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->detector_info_flags = detector_info_flags;
		__internal_ret->detector_not_occupy_times = detector_not_occupy_times;
		__internal_ret->detector_occupy_times = detector_occupy_times;
		__internal_ret->detector_traffic_volumes = detector_traffic_volumes;
		__internal_ret->detector_traffic_saturations = detector_traffic_saturations;
		__internal_ret->detector_saturation_flow_rate_per_speeds = detector_saturation_flow_rate_per_speeds;
		__internal_ret->detector_saturation_not_ocuppy_time = detector_saturation_not_ocuppy_time;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t DetectorInfo_copy(DetectorInfo *dst, DetectorInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->detector_info_flags && (dst->detector_info_flags = DetectorInfoFlagMaps_clone(src->detector_info_flags, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector_not_occupy_times && (dst->detector_not_occupy_times = DetectorInfoValueMap_clone(src->detector_not_occupy_times, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector_occupy_times && (dst->detector_occupy_times = DetectorInfoValueMap_clone(src->detector_occupy_times, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector_traffic_volumes && (dst->detector_traffic_volumes = DetectorInfoValueMap_clone(src->detector_traffic_volumes, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector_traffic_saturations && (dst->detector_traffic_saturations = DetectorInfoValueMap_clone(src->detector_traffic_saturations, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector_saturation_flow_rate_per_speeds && (dst->detector_saturation_flow_rate_per_speeds = DetectorInfoValueMap_clone(src->detector_saturation_flow_rate_per_speeds, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector_saturation_not_ocuppy_time && (dst->detector_saturation_not_ocuppy_time = DetectorInfoValueMap_clone(src->detector_saturation_not_ocuppy_time, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

DetectorInfo *DetectorInfo_clone(DetectorInfo *src, Dz1Error *err)
{
	DetectorInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (DetectorInfo *)Dz1Calloc(sizeof(DetectorInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(DetectorInfo_delAndSetNull, (void *)&dst);
		if (DetectorInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void DetectorInfo_purge(DetectorInfo *p)
{
	if (p == NULL) return;
	DetectorInfoFlagMaps_del(p->detector_info_flags);
	DetectorInfoValueMap_del(p->detector_not_occupy_times);
	DetectorInfoValueMap_del(p->detector_occupy_times);
	DetectorInfoValueMap_del(p->detector_traffic_volumes);
	DetectorInfoValueMap_del(p->detector_traffic_saturations);
	DetectorInfoValueMap_del(p->detector_saturation_flow_rate_per_speeds);
	DetectorInfoValueMap_del(p->detector_saturation_not_ocuppy_time);
}

void DetectorInfo_del(DetectorInfo *p)
{
	if (p == NULL) return;
	DetectorInfo_purge(p);
	Dz1Free(p);
}

void DetectorInfo_dump(DetectorInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector_info_flags = ")); DetectorInfoFlagMaps_dump(p->detector_info_flags, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector_not_occupy_times = ")); DetectorInfoValueMap_dump(p->detector_not_occupy_times, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector_occupy_times = ")); DetectorInfoValueMap_dump(p->detector_occupy_times, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector_traffic_volumes = ")); DetectorInfoValueMap_dump(p->detector_traffic_volumes, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector_traffic_saturations = ")); DetectorInfoValueMap_dump(p->detector_traffic_saturations, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector_saturation_flow_rate_per_speeds = ")); DetectorInfoValueMap_dump(p->detector_saturation_flow_rate_per_speeds, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector_saturation_not_ocuppy_time = ")); DetectorInfoValueMap_dump(p->detector_saturation_not_ocuppy_time, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// DetectorInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInformation
DetectorInformation *DetectorInformation_new(u8_t cross_id, 
											 DetectorInfo *detector_info, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DetectorInformation *__internal_ret = (DetectorInformation *)Dz1Calloc(sizeof(DetectorInformation), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(DetectorInformation_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->detector_info = detector_info;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInformation_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t DetectorInformation_copy(DetectorInformation *dst, DetectorInformation *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->detector_info && (dst->detector_info = DetectorInfo_clone(src->detector_info, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

DetectorInformation *DetectorInformation_clone(DetectorInformation *src, Dz1Error *err)
{
	DetectorInformation *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (DetectorInformation *)Dz1Calloc(sizeof(DetectorInformation), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(DetectorInformation_delAndSetNull, (void *)&dst);
		if (DetectorInformation_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorInformation_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void DetectorInformation_purge(DetectorInformation *p)
{
	if (p == NULL) return;
	DetectorInfo_del(p->detector_info);
}

void DetectorInformation_del(DetectorInformation *p)
{
	if (p == NULL) return;
	DetectorInformation_purge(p);
	Dz1Free(p);
}

void DetectorInformation_dump(DetectorInformation *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("detector_info = ")); DetectorInfo_dump(p->detector_info, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// DetectorInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoPeriodicOperationTime
SignalPhaseInfoPeriodicOperationTime *SignalPhaseInfoPeriodicOperationTime_new(u8_t ring_a_phase1, 
																			   u8_t ring_a_phase2, 
																			   u8_t ring_a_phase3, 
																			   u8_t ring_a_phase4, 
																			   u8_t ring_a_phase5, 
																			   u8_t ring_a_phase6, 
																			   u8_t ring_a_phase7, 
																			   u8_t ring_a_phase8, 
																			   u8_t ring_b_phase1, 
																			   u8_t ring_b_phase2, 
																			   u8_t ring_b_phase3, 
																			   u8_t ring_b_phase4, 
																			   u8_t ring_b_phase5, 
																			   u8_t ring_b_phase6, 
																			   u8_t ring_b_phase7, 
																			   u8_t ring_b_phase8, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SignalPhaseInfoPeriodicOperationTime *__internal_ret = (SignalPhaseInfoPeriodicOperationTime *)Dz1Calloc(sizeof(SignalPhaseInfoPeriodicOperationTime), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoPeriodicOperationTime_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->ring_a_phase1 = ring_a_phase1;
		__internal_ret->ring_a_phase2 = ring_a_phase2;
		__internal_ret->ring_a_phase3 = ring_a_phase3;
		__internal_ret->ring_a_phase4 = ring_a_phase4;
		__internal_ret->ring_a_phase5 = ring_a_phase5;
		__internal_ret->ring_a_phase6 = ring_a_phase6;
		__internal_ret->ring_a_phase7 = ring_a_phase7;
		__internal_ret->ring_a_phase8 = ring_a_phase8;
		__internal_ret->ring_b_phase1 = ring_b_phase1;
		__internal_ret->ring_b_phase2 = ring_b_phase2;
		__internal_ret->ring_b_phase3 = ring_b_phase3;
		__internal_ret->ring_b_phase4 = ring_b_phase4;
		__internal_ret->ring_b_phase5 = ring_b_phase5;
		__internal_ret->ring_b_phase6 = ring_b_phase6;
		__internal_ret->ring_b_phase7 = ring_b_phase7;
		__internal_ret->ring_b_phase8 = ring_b_phase8;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoPeriodicOperationTime_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SignalPhaseInfoPeriodicOperationTime_copy(SignalPhaseInfoPeriodicOperationTime *dst, SignalPhaseInfoPeriodicOperationTime *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->ring_a_phase1 = src->ring_a_phase1;
		dst->ring_a_phase2 = src->ring_a_phase2;
		dst->ring_a_phase3 = src->ring_a_phase3;
		dst->ring_a_phase4 = src->ring_a_phase4;
		dst->ring_a_phase5 = src->ring_a_phase5;
		dst->ring_a_phase6 = src->ring_a_phase6;
		dst->ring_a_phase7 = src->ring_a_phase7;
		dst->ring_a_phase8 = src->ring_a_phase8;
		dst->ring_b_phase1 = src->ring_b_phase1;
		dst->ring_b_phase2 = src->ring_b_phase2;
		dst->ring_b_phase3 = src->ring_b_phase3;
		dst->ring_b_phase4 = src->ring_b_phase4;
		dst->ring_b_phase5 = src->ring_b_phase5;
		dst->ring_b_phase6 = src->ring_b_phase6;
		dst->ring_b_phase7 = src->ring_b_phase7;
		dst->ring_b_phase8 = src->ring_b_phase8;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SignalPhaseInfoPeriodicOperationTime *SignalPhaseInfoPeriodicOperationTime_clone(SignalPhaseInfoPeriodicOperationTime *src, Dz1Error *err)
{
	SignalPhaseInfoPeriodicOperationTime *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SignalPhaseInfoPeriodicOperationTime *)Dz1Calloc(sizeof(SignalPhaseInfoPeriodicOperationTime), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoPeriodicOperationTime_delAndSetNull, (void *)&dst);
		if (SignalPhaseInfoPeriodicOperationTime_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoPeriodicOperationTime_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SignalPhaseInfoPeriodicOperationTime_purge(SignalPhaseInfoPeriodicOperationTime *p)
{
	if (p == NULL) return;
}

void SignalPhaseInfoPeriodicOperationTime_del(SignalPhaseInfoPeriodicOperationTime *p)
{
	if (p == NULL) return;
	SignalPhaseInfoPeriodicOperationTime_purge(p);
	Dz1Free(p);
}

void SignalPhaseInfoPeriodicOperationTime_dump(SignalPhaseInfoPeriodicOperationTime *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase1 = ")); Dz1u8_dump(&p->ring_a_phase1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase2 = ")); Dz1u8_dump(&p->ring_a_phase2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase3 = ")); Dz1u8_dump(&p->ring_a_phase3, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase4 = ")); Dz1u8_dump(&p->ring_a_phase4, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase5 = ")); Dz1u8_dump(&p->ring_a_phase5, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase6 = ")); Dz1u8_dump(&p->ring_a_phase6, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase7 = ")); Dz1u8_dump(&p->ring_a_phase7, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_a_phase8 = ")); Dz1u8_dump(&p->ring_a_phase8, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase1 = ")); Dz1u8_dump(&p->ring_b_phase1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase2 = ")); Dz1u8_dump(&p->ring_b_phase2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase3 = ")); Dz1u8_dump(&p->ring_b_phase3, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase4 = ")); Dz1u8_dump(&p->ring_b_phase4, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase5 = ")); Dz1u8_dump(&p->ring_b_phase5, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase6 = ")); Dz1u8_dump(&p->ring_b_phase6, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase7 = ")); Dz1u8_dump(&p->ring_b_phase7, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ring_b_phase8 = ")); Dz1u8_dump(&p->ring_b_phase8, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SignalPhaseInfoPeriodicOperationTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoDownBasic
SignalPhaseInfoDownBasic *SignalPhaseInfoDownBasic_new(SignalPhaseInfoPeriodicOperationTime *periodic_oper_time1, 
													   u8_t offset, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SignalPhaseInfoDownBasic *__internal_ret = (SignalPhaseInfoDownBasic *)Dz1Calloc(sizeof(SignalPhaseInfoDownBasic), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoDownBasic_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->periodic_oper_time1 = periodic_oper_time1;
		__internal_ret->offset = offset;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoDownBasic_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SignalPhaseInfoDownBasic_copy(SignalPhaseInfoDownBasic *dst, SignalPhaseInfoDownBasic *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->periodic_oper_time1 && (dst->periodic_oper_time1 = SignalPhaseInfoPeriodicOperationTime_clone(src->periodic_oper_time1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->offset = src->offset;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SignalPhaseInfoDownBasic *SignalPhaseInfoDownBasic_clone(SignalPhaseInfoDownBasic *src, Dz1Error *err)
{
	SignalPhaseInfoDownBasic *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SignalPhaseInfoDownBasic *)Dz1Calloc(sizeof(SignalPhaseInfoDownBasic), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoDownBasic_delAndSetNull, (void *)&dst);
		if (SignalPhaseInfoDownBasic_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoDownBasic_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SignalPhaseInfoDownBasic_purge(SignalPhaseInfoDownBasic *p)
{
	if (p == NULL) return;
	SignalPhaseInfoPeriodicOperationTime_del(p->periodic_oper_time1);
}

void SignalPhaseInfoDownBasic_del(SignalPhaseInfoDownBasic *p)
{
	if (p == NULL) return;
	SignalPhaseInfoDownBasic_purge(p);
	Dz1Free(p);
}

void SignalPhaseInfoDownBasic_dump(SignalPhaseInfoDownBasic *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("periodic_oper_time1 = ")); SignalPhaseInfoPeriodicOperationTime_dump(p->periodic_oper_time1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("offset = ")); Dz1u8_dump(&p->offset, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SignalPhaseInfoDownBasic
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoDown_r27
SignalPhaseInfoDown_r27 *SignalPhaseInfoDown_r27_new(SignalPhaseInfoDownBasic *mandatory, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SignalPhaseInfoDown_r27 *__internal_ret = (SignalPhaseInfoDown_r27 *)Dz1Calloc(sizeof(SignalPhaseInfoDown_r27), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoDown_r27_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->mandatory = mandatory;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoDown_r27_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SignalPhaseInfoDown_r27_copy(SignalPhaseInfoDown_r27 *dst, SignalPhaseInfoDown_r27 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->mandatory && (dst->mandatory = SignalPhaseInfoDownBasic_clone(src->mandatory, errp)) == NULL) ERR_OUT(errp);
	else if (src->periodic_oper_time2 && (dst->periodic_oper_time2 = SignalPhaseInfoPeriodicOperationTime_clone(src->periodic_oper_time2, errp)) == NULL) ERR_OUT(errp);
	else if (src->periodic_oper_time3 && (dst->periodic_oper_time3 = SignalPhaseInfoPeriodicOperationTime_clone(src->periodic_oper_time3, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SignalPhaseInfoDown_r27 *SignalPhaseInfoDown_r27_clone(SignalPhaseInfoDown_r27 *src, Dz1Error *err)
{
	SignalPhaseInfoDown_r27 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SignalPhaseInfoDown_r27 *)Dz1Calloc(sizeof(SignalPhaseInfoDown_r27), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoDown_r27_delAndSetNull, (void *)&dst);
		if (SignalPhaseInfoDown_r27_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoDown_r27_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SignalPhaseInfoDown_r27_purge(SignalPhaseInfoDown_r27 *p)
{
	if (p == NULL) return;
	SignalPhaseInfoDownBasic_del(p->mandatory);
	SignalPhaseInfoPeriodicOperationTime_del(p->periodic_oper_time2);
	SignalPhaseInfoPeriodicOperationTime_del(p->periodic_oper_time3);
}

void SignalPhaseInfoDown_r27_del(SignalPhaseInfoDown_r27 *p)
{
	if (p == NULL) return;
	SignalPhaseInfoDown_r27_purge(p);
	Dz1Free(p);
}

void SignalPhaseInfoDown_r27_dump(SignalPhaseInfoDown_r27 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("mandatory = ")); SignalPhaseInfoDownBasic_dump(p->mandatory, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("periodic_oper_time2 = ")); SignalPhaseInfoPeriodicOperationTime_dump(p->periodic_oper_time2, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("periodic_oper_time3 = ")); SignalPhaseInfoPeriodicOperationTime_dump(p->periodic_oper_time3, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SignalPhaseInfoDown_r27
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoDown_r29
SignalPhaseInfoDown_r29 *SignalPhaseInfoDown_r29_new(SignalPhaseInfoDownBasic *mandatory, 
													 u16_t offset1, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SignalPhaseInfoDown_r29 *__internal_ret = (SignalPhaseInfoDown_r29 *)Dz1Calloc(sizeof(SignalPhaseInfoDown_r29), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoDown_r29_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->mandatory = mandatory;
		__internal_ret->offset1 = offset1;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoDown_r29_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SignalPhaseInfoDown_r29_copy(SignalPhaseInfoDown_r29 *dst, SignalPhaseInfoDown_r29 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->mandatory && (dst->mandatory = SignalPhaseInfoDownBasic_clone(src->mandatory, errp)) == NULL) ERR_OUT(errp);
	else if (src->periodic_oper_time2 && (dst->periodic_oper_time2 = SignalPhaseInfoPeriodicOperationTime_clone(src->periodic_oper_time2, errp)) == NULL) ERR_OUT(errp);
	else if (src->periodic_oper_time3 && (dst->periodic_oper_time3 = SignalPhaseInfoPeriodicOperationTime_clone(src->periodic_oper_time3, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->offset1 = src->offset1;
		dst->offset2 = src->offset2;
		dst->offset3 = src->offset3;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SignalPhaseInfoDown_r29 *SignalPhaseInfoDown_r29_clone(SignalPhaseInfoDown_r29 *src, Dz1Error *err)
{
	SignalPhaseInfoDown_r29 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SignalPhaseInfoDown_r29 *)Dz1Calloc(sizeof(SignalPhaseInfoDown_r29), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoDown_r29_delAndSetNull, (void *)&dst);
		if (SignalPhaseInfoDown_r29_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoDown_r29_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SignalPhaseInfoDown_r29_purge(SignalPhaseInfoDown_r29 *p)
{
	if (p == NULL) return;
	SignalPhaseInfoDownBasic_del(p->mandatory);
	SignalPhaseInfoPeriodicOperationTime_del(p->periodic_oper_time2);
	SignalPhaseInfoPeriodicOperationTime_del(p->periodic_oper_time3);
}

void SignalPhaseInfoDown_r29_del(SignalPhaseInfoDown_r29 *p)
{
	if (p == NULL) return;
	SignalPhaseInfoDown_r29_purge(p);
	Dz1Free(p);
}

void SignalPhaseInfoDown_r29_dump(SignalPhaseInfoDown_r29 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("mandatory = ")); SignalPhaseInfoDownBasic_dump(p->mandatory, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("periodic_oper_time2 = ")); SignalPhaseInfoPeriodicOperationTime_dump(p->periodic_oper_time2, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("periodic_oper_time3 = ")); SignalPhaseInfoPeriodicOperationTime_dump(p->periodic_oper_time3, tab); 
		Dz1Thread_tprintf(tab, Dz1T("offset1 = ")); Dz1u16_dump(&p->offset1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("offset2 = ")); Dz1u16_dump(&p->offset2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("offset3 = ")); Dz1u16_dump(&p->offset3, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SignalPhaseInfoDown_r29
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInformationDownload
SignalPhaseInformationDownload *SignalPhaseInformationDownload_new(u8_t cross_id, 
																   SignalPhaseInfoDown_r27 *signal_phase_info_down, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SignalPhaseInformationDownload *__internal_ret = (SignalPhaseInformationDownload *)Dz1Calloc(sizeof(SignalPhaseInformationDownload), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SignalPhaseInformationDownload_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->signal_phase_info_down = signal_phase_info_down;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInformationDownload_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SignalPhaseInformationDownload_copy(SignalPhaseInformationDownload *dst, SignalPhaseInformationDownload *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->signal_phase_info_down && (dst->signal_phase_info_down = SignalPhaseInfoDown_r27_clone(src->signal_phase_info_down, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SignalPhaseInformationDownload *SignalPhaseInformationDownload_clone(SignalPhaseInformationDownload *src, Dz1Error *err)
{
	SignalPhaseInformationDownload *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SignalPhaseInformationDownload *)Dz1Calloc(sizeof(SignalPhaseInformationDownload), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SignalPhaseInformationDownload_delAndSetNull, (void *)&dst);
		if (SignalPhaseInformationDownload_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInformationDownload_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SignalPhaseInformationDownload_purge(SignalPhaseInformationDownload *p)
{
	if (p == NULL) return;
	SignalPhaseInfoDown_r27_del(p->signal_phase_info_down);
}

void SignalPhaseInformationDownload_del(SignalPhaseInformationDownload *p)
{
	if (p == NULL) return;
	SignalPhaseInformationDownload_purge(p);
	Dz1Free(p);
}

void SignalPhaseInformationDownload_dump(SignalPhaseInformationDownload *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("signal_phase_info_down = ")); SignalPhaseInfoDown_r27_dump(p->signal_phase_info_down, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SignalPhaseInformationDownload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoUpPPCControl
SignalPhaseInfoUpPPCControl *SignalPhaseInfoUpPPCControl_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SignalPhaseInfoUpPPCControl *__internal_ret = (SignalPhaseInfoUpPPCControl *)Dz1Calloc(sizeof(SignalPhaseInfoUpPPCControl), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoUpPPCControl_delAndSetNull, (void *)&__internal_ret);
		
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoUpPPCControl_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SignalPhaseInfoUpPPCControl_copy(SignalPhaseInfoUpPPCControl *dst, SignalPhaseInfoUpPPCControl *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->ppc_blink_time = src->ppc_blink_time;
		dst->ppc_all_red_time = src->ppc_all_red_time;
		dst->ppc_priority_signal = src->ppc_priority_signal;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SignalPhaseInfoUpPPCControl *SignalPhaseInfoUpPPCControl_clone(SignalPhaseInfoUpPPCControl *src, Dz1Error *err)
{
	SignalPhaseInfoUpPPCControl *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SignalPhaseInfoUpPPCControl *)Dz1Calloc(sizeof(SignalPhaseInfoUpPPCControl), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoUpPPCControl_delAndSetNull, (void *)&dst);
		if (SignalPhaseInfoUpPPCControl_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoUpPPCControl_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SignalPhaseInfoUpPPCControl_purge(SignalPhaseInfoUpPPCControl *p)
{
	if (p == NULL) return;
}

void SignalPhaseInfoUpPPCControl_del(SignalPhaseInfoUpPPCControl *p)
{
	if (p == NULL) return;
	SignalPhaseInfoUpPPCControl_purge(p);
	Dz1Free(p);
}

void SignalPhaseInfoUpPPCControl_dump(SignalPhaseInfoUpPPCControl *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("ppc_blink_time = ")); Dz1u8_dump(&p->ppc_blink_time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ppc_all_red_time = ")); Dz1u8_dump(&p->ppc_all_red_time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ppc_priority_signal = ")); Dz1u8_dump(&p->ppc_priority_signal, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SignalPhaseInfoUpPPCControl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoUp
SignalPhaseInfoUp *SignalPhaseInfoUp_new(SignalPhaseInfoPeriodicOperationTime *operation_time, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SignalPhaseInfoUp *__internal_ret = (SignalPhaseInfoUp *)Dz1Calloc(sizeof(SignalPhaseInfoUp), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoUp_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->operation_time = operation_time;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoUp_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SignalPhaseInfoUp_copy(SignalPhaseInfoUp *dst, SignalPhaseInfoUp *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->operation_time && (dst->operation_time = SignalPhaseInfoPeriodicOperationTime_clone(src->operation_time, errp)) == NULL) ERR_OUT(errp);
	else if (src->pedestrianoperation_time && (dst->pedestrianoperation_time = SignalPhaseInfoPeriodicOperationTime_clone(src->pedestrianoperation_time, errp)) == NULL) ERR_OUT(errp);
	else if (src->ppc_control && (dst->ppc_control = SignalPhaseInfoUpPPCControl_clone(src->ppc_control, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SignalPhaseInfoUp *SignalPhaseInfoUp_clone(SignalPhaseInfoUp *src, Dz1Error *err)
{
	SignalPhaseInfoUp *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SignalPhaseInfoUp *)Dz1Calloc(sizeof(SignalPhaseInfoUp), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SignalPhaseInfoUp_delAndSetNull, (void *)&dst);
		if (SignalPhaseInfoUp_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInfoUp_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SignalPhaseInfoUp_purge(SignalPhaseInfoUp *p)
{
	if (p == NULL) return;
	SignalPhaseInfoPeriodicOperationTime_del(p->operation_time);
	SignalPhaseInfoPeriodicOperationTime_del(p->pedestrianoperation_time);
	SignalPhaseInfoUpPPCControl_del(p->ppc_control);
}

void SignalPhaseInfoUp_del(SignalPhaseInfoUp *p)
{
	if (p == NULL) return;
	SignalPhaseInfoUp_purge(p);
	Dz1Free(p);
}

void SignalPhaseInfoUp_dump(SignalPhaseInfoUp *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("operation_time = ")); SignalPhaseInfoPeriodicOperationTime_dump(p->operation_time, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("pedestrianoperation_time = ")); SignalPhaseInfoPeriodicOperationTime_dump(p->pedestrianoperation_time, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("ppc_control = ")); SignalPhaseInfoUpPPCControl_dump(p->ppc_control, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SignalPhaseInfoUp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInformationUpload
SignalPhaseInformationUpload *SignalPhaseInformationUpload_new(u8_t cross_id, 
															   SignalPhaseInfoUp *signal_phase_info_up, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SignalPhaseInformationUpload *__internal_ret = (SignalPhaseInformationUpload *)Dz1Calloc(sizeof(SignalPhaseInformationUpload), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SignalPhaseInformationUpload_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->signal_phase_info_up = signal_phase_info_up;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInformationUpload_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SignalPhaseInformationUpload_copy(SignalPhaseInformationUpload *dst, SignalPhaseInformationUpload *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->signal_phase_info_up && (dst->signal_phase_info_up = SignalPhaseInfoUp_clone(src->signal_phase_info_up, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SignalPhaseInformationUpload *SignalPhaseInformationUpload_clone(SignalPhaseInformationUpload *src, Dz1Error *err)
{
	SignalPhaseInformationUpload *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SignalPhaseInformationUpload *)Dz1Calloc(sizeof(SignalPhaseInformationUpload), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SignalPhaseInformationUpload_delAndSetNull, (void *)&dst);
		if (SignalPhaseInformationUpload_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SignalPhaseInformationUpload_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SignalPhaseInformationUpload_purge(SignalPhaseInformationUpload *p)
{
	if (p == NULL) return;
	SignalPhaseInfoUp_del(p->signal_phase_info_up);
}

void SignalPhaseInformationUpload_del(SignalPhaseInformationUpload *p)
{
	if (p == NULL) return;
	SignalPhaseInformationUpload_purge(p);
	Dz1Free(p);
}

void SignalPhaseInformationUpload_dump(SignalPhaseInformationUpload *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("signal_phase_info_up = ")); SignalPhaseInfoUp_dump(p->signal_phase_info_up, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SignalPhaseInformationUpload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInfoWeekIndex
static struct ClockInfoWeekIndexMapA
{
	str_t str;
	ClockInfoWeekIndex v;
} ClockInfoWeekIndexMapA[] =
{
	{ (char *)"sun", ClockInfoWeekIndex_sun },
	{ (char *)"mon", ClockInfoWeekIndex_mon },
	{ (char *)"tue", ClockInfoWeekIndex_tue },
	{ (char *)"wed", ClockInfoWeekIndex_wed },
	{ (char *)"thu", ClockInfoWeekIndex_thu },
	{ (char *)"fri", ClockInfoWeekIndex_fri },
	{ (char *)"sat", ClockInfoWeekIndex_sat },
	{ NULL, ClockInfoWeekIndex_max }
};

str_t ClockInfoWeekIndexStrA(ClockInfoWeekIndex v)
{
	struct ClockInfoWeekIndexMapA *i = NULL;
	for (i = ClockInfoWeekIndexMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ClockInfoWeekIndex ClockInfoWeekIndexFromStrA(str_t str)
{
	struct ClockInfoWeekIndexMapA *i = NULL;
	for (i = ClockInfoWeekIndexMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ClockInfoWeekIndex_max;
}
#ifndef UNIX_SYSTEM
static struct ClockInfoWeekIndexMapW
{
	wstr_t str;
	ClockInfoWeekIndex v;
} ClockInfoWeekIndexMapW[] =
{
	{ (wchar_t *)L"sun", ClockInfoWeekIndex_sun },
	{ (wchar_t *)L"mon", ClockInfoWeekIndex_mon },
	{ (wchar_t *)L"tue", ClockInfoWeekIndex_tue },
	{ (wchar_t *)L"wed", ClockInfoWeekIndex_wed },
	{ (wchar_t *)L"thu", ClockInfoWeekIndex_thu },
	{ (wchar_t *)L"fri", ClockInfoWeekIndex_fri },
	{ (wchar_t *)L"sat", ClockInfoWeekIndex_sat },
	{ NULL, ClockInfoWeekIndex_max }
};

wstr_t ClockInfoWeekIndexStrW(ClockInfoWeekIndex v)
{
	struct ClockInfoWeekIndexMapW *i = NULL;
	for (i = ClockInfoWeekIndexMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ClockInfoWeekIndex ClockInfoWeekIndexFromStrW(wstr_t str)
{
	struct ClockInfoWeekIndexMapW *i = NULL;
	for (i = ClockInfoWeekIndexMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ClockInfoWeekIndex_max;
}
#endif // UNIX_SYSTEM

ClockInfoWeekIndex *ClockInfoWeekIndex_new(ClockInfoWeekIndex *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ClockInfoWeekIndex *__internal_ret = (ClockInfoWeekIndex *)Dz1Calloc(sizeof(ClockInfoWeekIndex), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ClockInfoWeekIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInfo
ClockInfo *ClockInfo_new(u8_t year, 
						 u8_t month, 
						 u8_t day, 
						 u8_t hour, 
						 u8_t minute, 
						 u8_t second, 
						 ClockInfoWeekIndex week_index, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ClockInfo *__internal_ret = (ClockInfo *)Dz1Calloc(sizeof(ClockInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ClockInfo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->year = year;
		__internal_ret->month = month;
		__internal_ret->day = day;
		__internal_ret->hour = hour;
		__internal_ret->minute = minute;
		__internal_ret->second = second;
		__internal_ret->week_index = week_index;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ClockInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ClockInfo_copy(ClockInfo *dst, ClockInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->year = src->year;
		dst->month = src->month;
		dst->day = src->day;
		dst->hour = src->hour;
		dst->minute = src->minute;
		dst->second = src->second;
		dst->week_index = src->week_index;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ClockInfo *ClockInfo_clone(ClockInfo *src, Dz1Error *err)
{
	ClockInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ClockInfo *)Dz1Calloc(sizeof(ClockInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ClockInfo_delAndSetNull, (void *)&dst);
		if (ClockInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ClockInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ClockInfo_purge(ClockInfo *p)
{
	if (p == NULL) return;
}

void ClockInfo_del(ClockInfo *p)
{
	if (p == NULL) return;
	ClockInfo_purge(p);
	Dz1Free(p);
}

void ClockInfo_dump(ClockInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("year = ")); Dz1u8_dump(&p->year, tab); 
		Dz1Thread_tprintf(tab, Dz1T("month = ")); Dz1u8_dump(&p->month, tab); 
		Dz1Thread_tprintf(tab, Dz1T("day = ")); Dz1u8_dump(&p->day, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hour = ")); Dz1u8_dump(&p->hour, tab); 
		Dz1Thread_tprintf(tab, Dz1T("minute = ")); Dz1u8_dump(&p->minute, tab); 
		Dz1Thread_tprintf(tab, Dz1T("second = ")); Dz1u8_dump(&p->second, tab); 
		Dz1Thread_tprintf(tab, Dz1T("week_index = %s(%d)\n"), ClockInfoWeekIndexStr(p->week_index), p->week_index);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ClockInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInformationDownload
ClockInformationDownload *ClockInformationDownload_new(u8_t cross_id, 
													   ClockInfo *clock_info_down, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ClockInformationDownload *__internal_ret = (ClockInformationDownload *)Dz1Calloc(sizeof(ClockInformationDownload), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ClockInformationDownload_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->clock_info_down = clock_info_down;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ClockInformationDownload_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ClockInformationDownload_copy(ClockInformationDownload *dst, ClockInformationDownload *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->clock_info_down && (dst->clock_info_down = ClockInfo_clone(src->clock_info_down, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ClockInformationDownload *ClockInformationDownload_clone(ClockInformationDownload *src, Dz1Error *err)
{
	ClockInformationDownload *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ClockInformationDownload *)Dz1Calloc(sizeof(ClockInformationDownload), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ClockInformationDownload_delAndSetNull, (void *)&dst);
		if (ClockInformationDownload_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ClockInformationDownload_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ClockInformationDownload_purge(ClockInformationDownload *p)
{
	if (p == NULL) return;
	ClockInfo_del(p->clock_info_down);
}

void ClockInformationDownload_del(ClockInformationDownload *p)
{
	if (p == NULL) return;
	ClockInformationDownload_purge(p);
	Dz1Free(p);
}

void ClockInformationDownload_dump(ClockInformationDownload *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("clock_info_down = ")); ClockInfo_dump(p->clock_info_down, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ClockInformationDownload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInformationUpload
ClockInformationUpload *ClockInformationUpload_new(u8_t cross_id, 
												   ClockInfo *clock_info_up, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ClockInformationUpload *__internal_ret = (ClockInformationUpload *)Dz1Calloc(sizeof(ClockInformationUpload), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ClockInformationUpload_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->clock_info_up = clock_info_up;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ClockInformationUpload_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ClockInformationUpload_copy(ClockInformationUpload *dst, ClockInformationUpload *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->clock_info_up && (dst->clock_info_up = ClockInfo_clone(src->clock_info_up, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ClockInformationUpload *ClockInformationUpload_clone(ClockInformationUpload *src, Dz1Error *err)
{
	ClockInformationUpload *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ClockInformationUpload *)Dz1Calloc(sizeof(ClockInformationUpload), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ClockInformationUpload_delAndSetNull, (void *)&dst);
		if (ClockInformationUpload_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ClockInformationUpload_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ClockInformationUpload_purge(ClockInformationUpload *p)
{
	if (p == NULL) return;
	ClockInfo_del(p->clock_info_up);
}

void ClockInformationUpload_del(ClockInformationUpload *p)
{
	if (p == NULL) return;
	ClockInformationUpload_purge(p);
	Dz1Free(p);
}

void ClockInformationUpload_dump(ClockInformationUpload *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("clock_info_up = ")); ClockInfo_dump(p->clock_info_up, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ClockInformationUpload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCVehicleProperty
SpecialCommandPPCVehicleProperty *SpecialCommandPPCVehicleProperty_new(u32_t property, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandPPCVehicleProperty *__internal_ret = (SpecialCommandPPCVehicleProperty *)Dz1Calloc(sizeof(SpecialCommandPPCVehicleProperty), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCVehicleProperty_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->property = property;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCVehicleProperty_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandPPCVehicleProperty_copy(SpecialCommandPPCVehicleProperty *dst, SpecialCommandPPCVehicleProperty *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->property = src->property;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandPPCVehicleProperty *SpecialCommandPPCVehicleProperty_clone(SpecialCommandPPCVehicleProperty *src, Dz1Error *err)
{
	SpecialCommandPPCVehicleProperty *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandPPCVehicleProperty *)Dz1Calloc(sizeof(SpecialCommandPPCVehicleProperty), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCVehicleProperty_delAndSetNull, (void *)&dst);
		if (SpecialCommandPPCVehicleProperty_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCVehicleProperty_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandPPCVehicleProperty_purge(SpecialCommandPPCVehicleProperty *p)
{
	if (p == NULL) return;
}

void SpecialCommandPPCVehicleProperty_del(SpecialCommandPPCVehicleProperty *p)
{
	if (p == NULL) return;
	SpecialCommandPPCVehicleProperty_purge(p);
	Dz1Free(p);
}

void SpecialCommandPPCVehicleProperty_dump(SpecialCommandPPCVehicleProperty *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("property = ")); Dz1u32_dump(&p->property, tab); 
	}
}
// SpecialCommandPPCVehicleProperty
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCVehicleProperties
static Dz1Error SpecialCommandPPCVehicleProperties_add(SpecialCommandPPCVehicleProperties *p, SpecialCommandPPCVehicleProperty *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static SpecialCommandPPCVehicleProperty *SpecialCommandPPCVehicleProperties_extract(SpecialCommandPPCVehicleProperties *p, SpecialCommandPPCVehicleProperty *ptr)
{
	return (SpecialCommandPPCVehicleProperty *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct SpecialCommandPPCVehiclePropertiesMkArrArg
{
	SpecialCommandPPCVehicleProperty **arr;
	unsigned int idx;
} SpecialCommandPPCVehiclePropertiesMkArrArg;

static Dz1Error _SpecialCommandPPCVehicleProperties_get_array(void *ptr, SpecialCommandPPCVehicleProperty *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	SpecialCommandPPCVehiclePropertiesMkArrArg *arg = (SpecialCommandPPCVehiclePropertiesMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static SpecialCommandPPCVehicleProperty **SpecialCommandPPCVehicleProperties_get_array(SpecialCommandPPCVehicleProperties *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	SpecialCommandPPCVehicleProperty **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (SpecialCommandPPCVehicleProperty **)Dz1Calloc(sizeof(SpecialCommandPPCVehicleProperty *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		SpecialCommandPPCVehiclePropertiesMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _SpecialCommandPPCVehicleProperties_get_array, (void *)&arg);
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

static Dz1Error SpecialCommandPPCVehicleProperties_travelForward(SpecialCommandPPCVehicleProperties *p, Dz1Error (*func)(void *ptr, SpecialCommandPPCVehicleProperty *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error SpecialCommandPPCVehicleProperties_travelBackward(SpecialCommandPPCVehicleProperties *p, Dz1Error (*func)(void *ptr, SpecialCommandPPCVehicleProperty *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static SpecialCommandPPCVehicleProperty *SpecialCommandPPCVehicleProperties_getHead(SpecialCommandPPCVehicleProperties *p)
{
	return (SpecialCommandPPCVehicleProperty *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int SpecialCommandPPCVehicleProperties_count(SpecialCommandPPCVehicleProperties *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

SpecialCommandPPCVehicleProperties *SpecialCommandPPCVehicleProperties_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandPPCVehicleProperties *ret = (SpecialCommandPPCVehicleProperties *)Dz1Calloc(sizeof(SpecialCommandPPCVehicleProperties), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SpecialCommandPPCVehicleProperties_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)SpecialCommandPPCVehicleProperty_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = SpecialCommandPPCVehicleProperties_count;
			ret->travel = SpecialCommandPPCVehicleProperties_travelForward;
			ret->travelForward = SpecialCommandPPCVehicleProperties_travelForward;
			ret->travelBackward = SpecialCommandPPCVehicleProperties_travelBackward;
			ret->get_array = SpecialCommandPPCVehicleProperties_get_array;
			ret->add = SpecialCommandPPCVehicleProperties_add;
			ret->extract = SpecialCommandPPCVehicleProperties_extract;
			ret->getHead = SpecialCommandPPCVehicleProperties_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCVehicleProperties_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _SpecialCommandPPCVehicleProperties_clone(void *ptr, SpecialCommandPPCVehicleProperty *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	SpecialCommandPPCVehicleProperties *p = (SpecialCommandPPCVehicleProperties *)ptr;
	SpecialCommandPPCVehicleProperty *cloned = SpecialCommandPPCVehicleProperty_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

SpecialCommandPPCVehicleProperties *SpecialCommandPPCVehicleProperties_clone(SpecialCommandPPCVehicleProperties *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandPPCVehicleProperties *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = SpecialCommandPPCVehicleProperties_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SpecialCommandPPCVehicleProperties_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_SpecialCommandPPCVehicleProperties_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCVehicleProperties_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void SpecialCommandPPCVehicleProperties_purge(SpecialCommandPPCVehicleProperties *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void SpecialCommandPPCVehicleProperties_del(SpecialCommandPPCVehicleProperties *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _SpecialCommandPPCVehicleProperties_dump(void *ptr, SpecialCommandPPCVehicleProperty *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); SpecialCommandPPCVehicleProperty_dump(p, tab);
	return err;
}

void SpecialCommandPPCVehicleProperties_dump(SpecialCommandPPCVehicleProperties *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _SpecialCommandPPCVehicleProperties_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SpecialCommandPPCVehicleProperties
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInfoPPCControlManage
SpecialCommandInfoPPCControlManage *SpecialCommandInfoPPCControlManage_new(bool_t is_org_code_registered_vehicle_request, 
																		   bool_t is_register_org_code, 
																		   bool_t is_delete_org_code, 
																		   bool_t is_register_vehicle_num, 
																		   bool_t is_delete_vehicle_num, 
																		   bool_t vehicle_code, 
																		   u8_t org_manage_code, 
																		   SpecialCommandPPCVehicleProperty *vehicle_property, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandInfoPPCControlManage *__internal_ret = (SpecialCommandInfoPPCControlManage *)Dz1Calloc(sizeof(SpecialCommandInfoPPCControlManage), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandInfoPPCControlManage_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->is_org_code_registered_vehicle_request = is_org_code_registered_vehicle_request;
		__internal_ret->is_register_org_code = is_register_org_code;
		__internal_ret->is_delete_org_code = is_delete_org_code;
		__internal_ret->is_register_vehicle_num = is_register_vehicle_num;
		__internal_ret->is_delete_vehicle_num = is_delete_vehicle_num;
		__internal_ret->vehicle_code = vehicle_code;
		__internal_ret->org_manage_code = org_manage_code;
		__internal_ret->vehicle_property = vehicle_property;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandInfoPPCControlManage_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandInfoPPCControlManage_copy(SpecialCommandInfoPPCControlManage *dst, SpecialCommandInfoPPCControlManage *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->vehicle_property && (dst->vehicle_property = SpecialCommandPPCVehicleProperty_clone(src->vehicle_property, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->is_org_code_registered_vehicle_request = src->is_org_code_registered_vehicle_request;
		dst->is_register_org_code = src->is_register_org_code;
		dst->is_delete_org_code = src->is_delete_org_code;
		dst->is_register_vehicle_num = src->is_register_vehicle_num;
		dst->is_delete_vehicle_num = src->is_delete_vehicle_num;
		dst->vehicle_code = src->vehicle_code;
		dst->org_manage_code = src->org_manage_code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandInfoPPCControlManage *SpecialCommandInfoPPCControlManage_clone(SpecialCommandInfoPPCControlManage *src, Dz1Error *err)
{
	SpecialCommandInfoPPCControlManage *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandInfoPPCControlManage *)Dz1Calloc(sizeof(SpecialCommandInfoPPCControlManage), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandInfoPPCControlManage_delAndSetNull, (void *)&dst);
		if (SpecialCommandInfoPPCControlManage_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandInfoPPCControlManage_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandInfoPPCControlManage_purge(SpecialCommandInfoPPCControlManage *p)
{
	if (p == NULL) return;
	SpecialCommandPPCVehicleProperty_del(p->vehicle_property);
}

void SpecialCommandInfoPPCControlManage_del(SpecialCommandInfoPPCControlManage *p)
{
	if (p == NULL) return;
	SpecialCommandInfoPPCControlManage_purge(p);
	Dz1Free(p);
}

void SpecialCommandInfoPPCControlManage_dump(SpecialCommandInfoPPCControlManage *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("is_org_code_registered_vehicle_request = ")); Dz1Bool_dump(&p->is_org_code_registered_vehicle_request, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_register_org_code = ")); Dz1Bool_dump(&p->is_register_org_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_delete_org_code = ")); Dz1Bool_dump(&p->is_delete_org_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_register_vehicle_num = ")); Dz1Bool_dump(&p->is_register_vehicle_num, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_delete_vehicle_num = ")); Dz1Bool_dump(&p->is_delete_vehicle_num, tab); 
		Dz1Thread_tprintf(tab, Dz1T("vehicle_code = ")); Dz1Bool_dump(&p->vehicle_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("org_manage_code = ")); Dz1u8_dump(&p->org_manage_code, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("vehicle_property = ")); SpecialCommandPPCVehicleProperty_dump(p->vehicle_property, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SpecialCommandInfoPPCControlManage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInfo
SpecialCommandInfo *SpecialCommandInfo_new(bool_t is_shut_down, 
										   bool_t is_blink_control, 
										   bool_t is_lamp_light_control, 
										   bool_t is_confilct, 
										   bool_t is_manual, 
										   bool_t is_confilct_reset, 
										   bool_t is_scu_reset, 
										   bool_t is_mcu_reset, 
										   bool_t is_ppc_control, 
										   bool_t is_pedestrian_button, 
										   bool_t is_x_control, 
										   bool_t is_spill_back_control, 
										   bool_t is_phase_omit, 
										   bool_t is_phase_hold, 
										   bool_t is_actuation_control, 
										   bool_t is_stagger_control, 
										   u8_t operation_flag, 
										   u8_t hold_omit_phase, 
										   u8_t stagger_plan, 
										   u8_t spill_back_direction_code, 
										   u8_t sub_phase_spill_back, 
										   u8_t main_phase_spill_back, 
										   SpecialCommandInfoPPCControlManage *ppc_control_manage, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandInfo *__internal_ret = (SpecialCommandInfo *)Dz1Calloc(sizeof(SpecialCommandInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandInfo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->is_shut_down = is_shut_down;
		__internal_ret->is_blink_control = is_blink_control;
		__internal_ret->is_lamp_light_control = is_lamp_light_control;
		__internal_ret->is_confilct = is_confilct;
		__internal_ret->is_manual = is_manual;
		__internal_ret->is_confilct_reset = is_confilct_reset;
		__internal_ret->is_scu_reset = is_scu_reset;
		__internal_ret->is_mcu_reset = is_mcu_reset;
		__internal_ret->is_ppc_control = is_ppc_control;
		__internal_ret->is_pedestrian_button = is_pedestrian_button;
		__internal_ret->is_x_control = is_x_control;
		__internal_ret->is_spill_back_control = is_spill_back_control;
		__internal_ret->is_phase_omit = is_phase_omit;
		__internal_ret->is_phase_hold = is_phase_hold;
		__internal_ret->is_actuation_control = is_actuation_control;
		__internal_ret->is_stagger_control = is_stagger_control;
		__internal_ret->operation_flag = operation_flag;
		__internal_ret->hold_omit_phase = hold_omit_phase;
		__internal_ret->stagger_plan = stagger_plan;
		__internal_ret->spill_back_direction_code = spill_back_direction_code;
		__internal_ret->sub_phase_spill_back = sub_phase_spill_back;
		__internal_ret->main_phase_spill_back = main_phase_spill_back;
		__internal_ret->ppc_control_manage = ppc_control_manage;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandInfo_copy(SpecialCommandInfo *dst, SpecialCommandInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->ppc_control_manage && (dst->ppc_control_manage = SpecialCommandInfoPPCControlManage_clone(src->ppc_control_manage, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->is_shut_down = src->is_shut_down;
		dst->is_blink_control = src->is_blink_control;
		dst->is_lamp_light_control = src->is_lamp_light_control;
		dst->is_confilct = src->is_confilct;
		dst->is_manual = src->is_manual;
		dst->is_confilct_reset = src->is_confilct_reset;
		dst->is_scu_reset = src->is_scu_reset;
		dst->is_mcu_reset = src->is_mcu_reset;
		dst->is_ppc_control = src->is_ppc_control;
		dst->is_pedestrian_button = src->is_pedestrian_button;
		dst->is_x_control = src->is_x_control;
		dst->is_spill_back_control = src->is_spill_back_control;
		dst->is_phase_omit = src->is_phase_omit;
		dst->is_phase_hold = src->is_phase_hold;
		dst->is_actuation_control = src->is_actuation_control;
		dst->is_stagger_control = src->is_stagger_control;
		dst->operation_flag = src->operation_flag;
		dst->hold_omit_phase = src->hold_omit_phase;
		dst->stagger_plan = src->stagger_plan;
		dst->spill_back_direction_code = src->spill_back_direction_code;
		dst->sub_phase_spill_back = src->sub_phase_spill_back;
		dst->main_phase_spill_back = src->main_phase_spill_back;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandInfo *SpecialCommandInfo_clone(SpecialCommandInfo *src, Dz1Error *err)
{
	SpecialCommandInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandInfo *)Dz1Calloc(sizeof(SpecialCommandInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandInfo_delAndSetNull, (void *)&dst);
		if (SpecialCommandInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandInfo_purge(SpecialCommandInfo *p)
{
	if (p == NULL) return;
	SpecialCommandInfoPPCControlManage_del(p->ppc_control_manage);
}

void SpecialCommandInfo_del(SpecialCommandInfo *p)
{
	if (p == NULL) return;
	SpecialCommandInfo_purge(p);
	Dz1Free(p);
}

void SpecialCommandInfo_dump(SpecialCommandInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("is_shut_down = ")); Dz1Bool_dump(&p->is_shut_down, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_blink_control = ")); Dz1Bool_dump(&p->is_blink_control, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_lamp_light_control = ")); Dz1Bool_dump(&p->is_lamp_light_control, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_confilct = ")); Dz1Bool_dump(&p->is_confilct, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_manual = ")); Dz1Bool_dump(&p->is_manual, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_confilct_reset = ")); Dz1Bool_dump(&p->is_confilct_reset, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_scu_reset = ")); Dz1Bool_dump(&p->is_scu_reset, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_mcu_reset = ")); Dz1Bool_dump(&p->is_mcu_reset, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_ppc_control = ")); Dz1Bool_dump(&p->is_ppc_control, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_pedestrian_button = ")); Dz1Bool_dump(&p->is_pedestrian_button, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_x_control = ")); Dz1Bool_dump(&p->is_x_control, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_spill_back_control = ")); Dz1Bool_dump(&p->is_spill_back_control, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_phase_omit = ")); Dz1Bool_dump(&p->is_phase_omit, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_phase_hold = ")); Dz1Bool_dump(&p->is_phase_hold, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_actuation_control = ")); Dz1Bool_dump(&p->is_actuation_control, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_stagger_control = ")); Dz1Bool_dump(&p->is_stagger_control, tab); 
		Dz1Thread_tprintf(tab, Dz1T("operation_flag = ")); Dz1u8_dump(&p->operation_flag, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hold_omit_phase = ")); Dz1u8_dump(&p->hold_omit_phase, tab); 
		Dz1Thread_tprintf(tab, Dz1T("stagger_plan = ")); Dz1u8_dump(&p->stagger_plan, tab); 
		Dz1Thread_tprintf(tab, Dz1T("spill_back_direction_code = ")); Dz1u8_dump(&p->spill_back_direction_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sub_phase_spill_back = ")); Dz1u8_dump(&p->sub_phase_spill_back, tab); 
		Dz1Thread_tprintf(tab, Dz1T("main_phase_spill_back = ")); Dz1u8_dump(&p->main_phase_spill_back, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("ppc_control_manage = ")); SpecialCommandInfoPPCControlManage_dump(p->ppc_control_manage, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SpecialCommandInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInformation
SpecialCommandInformation *SpecialCommandInformation_new(u8_t cross_id, 
														 SpecialCommandInfo *special_command, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandInformation *__internal_ret = (SpecialCommandInformation *)Dz1Calloc(sizeof(SpecialCommandInformation), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandInformation_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->special_command = special_command;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandInformation_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandInformation_copy(SpecialCommandInformation *dst, SpecialCommandInformation *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->special_command && (dst->special_command = SpecialCommandInfo_clone(src->special_command, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandInformation *SpecialCommandInformation_clone(SpecialCommandInformation *src, Dz1Error *err)
{
	SpecialCommandInformation *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandInformation *)Dz1Calloc(sizeof(SpecialCommandInformation), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandInformation_delAndSetNull, (void *)&dst);
		if (SpecialCommandInformation_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandInformation_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandInformation_purge(SpecialCommandInformation *p)
{
	if (p == NULL) return;
	SpecialCommandInfo_del(p->special_command);
}

void SpecialCommandInformation_del(SpecialCommandInformation *p)
{
	if (p == NULL) return;
	SpecialCommandInformation_purge(p);
	Dz1Free(p);
}

void SpecialCommandInformation_dump(SpecialCommandInformation *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("special_command = ")); SpecialCommandInfo_dump(p->special_command, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SpecialCommandInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_is_emergency
SpecialCommandPPCNumberList_is_emergency *SpecialCommandPPCNumberList_is_emergency_new(bool_t is_emergency, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandPPCNumberList_is_emergency *__internal_ret = (SpecialCommandPPCNumberList_is_emergency *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList_is_emergency), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_is_emergency_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->is_emergency = is_emergency;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_is_emergency_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandPPCNumberList_is_emergency_copy(SpecialCommandPPCNumberList_is_emergency *dst, SpecialCommandPPCNumberList_is_emergency *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->is_emergency = src->is_emergency;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandPPCNumberList_is_emergency *SpecialCommandPPCNumberList_is_emergency_clone(SpecialCommandPPCNumberList_is_emergency *src, Dz1Error *err)
{
	SpecialCommandPPCNumberList_is_emergency *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandPPCNumberList_is_emergency *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList_is_emergency), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_is_emergency_delAndSetNull, (void *)&dst);
		if (SpecialCommandPPCNumberList_is_emergency_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_is_emergency_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandPPCNumberList_is_emergency_purge(SpecialCommandPPCNumberList_is_emergency *p)
{
	if (p == NULL) return;
}

void SpecialCommandPPCNumberList_is_emergency_del(SpecialCommandPPCNumberList_is_emergency *p)
{
	if (p == NULL) return;
	SpecialCommandPPCNumberList_is_emergency_purge(p);
	Dz1Free(p);
}

void SpecialCommandPPCNumberList_is_emergency_dump(SpecialCommandPPCNumberList_is_emergency *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("is_emergency = ")); Dz1Bool_dump(&p->is_emergency, tab); 
	}
}
// SpecialCommandPPCNumberList_is_emergency
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_org_code
SpecialCommandPPCNumberList_org_code *SpecialCommandPPCNumberList_org_code_new(u8_t org_code, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandPPCNumberList_org_code *__internal_ret = (SpecialCommandPPCNumberList_org_code *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList_org_code), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_org_code_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->org_code = org_code;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_org_code_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandPPCNumberList_org_code_copy(SpecialCommandPPCNumberList_org_code *dst, SpecialCommandPPCNumberList_org_code *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->org_code = src->org_code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandPPCNumberList_org_code *SpecialCommandPPCNumberList_org_code_clone(SpecialCommandPPCNumberList_org_code *src, Dz1Error *err)
{
	SpecialCommandPPCNumberList_org_code *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandPPCNumberList_org_code *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList_org_code), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_org_code_delAndSetNull, (void *)&dst);
		if (SpecialCommandPPCNumberList_org_code_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_org_code_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandPPCNumberList_org_code_purge(SpecialCommandPPCNumberList_org_code *p)
{
	if (p == NULL) return;
}

void SpecialCommandPPCNumberList_org_code_del(SpecialCommandPPCNumberList_org_code *p)
{
	if (p == NULL) return;
	SpecialCommandPPCNumberList_org_code_purge(p);
	Dz1Free(p);
}

void SpecialCommandPPCNumberList_org_code_dump(SpecialCommandPPCNumberList_org_code *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("org_code = ")); Dz1u8_dump(&p->org_code, tab); 
	}
}
// SpecialCommandPPCNumberList_org_code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_org_code_num
SpecialCommandPPCNumberList_org_code_num *SpecialCommandPPCNumberList_org_code_num_new(u8_t org_code_num, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandPPCNumberList_org_code_num *__internal_ret = (SpecialCommandPPCNumberList_org_code_num *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList_org_code_num), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_org_code_num_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->org_code_num = org_code_num;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_org_code_num_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandPPCNumberList_org_code_num_copy(SpecialCommandPPCNumberList_org_code_num *dst, SpecialCommandPPCNumberList_org_code_num *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->org_code_num = src->org_code_num;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandPPCNumberList_org_code_num *SpecialCommandPPCNumberList_org_code_num_clone(SpecialCommandPPCNumberList_org_code_num *src, Dz1Error *err)
{
	SpecialCommandPPCNumberList_org_code_num *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandPPCNumberList_org_code_num *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList_org_code_num), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_org_code_num_delAndSetNull, (void *)&dst);
		if (SpecialCommandPPCNumberList_org_code_num_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_org_code_num_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandPPCNumberList_org_code_num_purge(SpecialCommandPPCNumberList_org_code_num *p)
{
	if (p == NULL) return;
}

void SpecialCommandPPCNumberList_org_code_num_del(SpecialCommandPPCNumberList_org_code_num *p)
{
	if (p == NULL) return;
	SpecialCommandPPCNumberList_org_code_num_purge(p);
	Dz1Free(p);
}

void SpecialCommandPPCNumberList_org_code_num_dump(SpecialCommandPPCNumberList_org_code_num *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("org_code_num = ")); Dz1u8_dump(&p->org_code_num, tab); 
	}
}
// SpecialCommandPPCNumberList_org_code_num
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_org_code_type
SpecialCommandPPCNumberList_org_code_type *SpecialCommandPPCNumberList_org_code_type_new(u32_t org_code_type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandPPCNumberList_org_code_type *__internal_ret = (SpecialCommandPPCNumberList_org_code_type *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList_org_code_type), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_org_code_type_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->org_code_type = org_code_type;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_org_code_type_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandPPCNumberList_org_code_type_copy(SpecialCommandPPCNumberList_org_code_type *dst, SpecialCommandPPCNumberList_org_code_type *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->org_code_type = src->org_code_type;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandPPCNumberList_org_code_type *SpecialCommandPPCNumberList_org_code_type_clone(SpecialCommandPPCNumberList_org_code_type *src, Dz1Error *err)
{
	SpecialCommandPPCNumberList_org_code_type *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandPPCNumberList_org_code_type *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList_org_code_type), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_org_code_type_delAndSetNull, (void *)&dst);
		if (SpecialCommandPPCNumberList_org_code_type_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_org_code_type_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandPPCNumberList_org_code_type_purge(SpecialCommandPPCNumberList_org_code_type *p)
{
	if (p == NULL) return;
}

void SpecialCommandPPCNumberList_org_code_type_del(SpecialCommandPPCNumberList_org_code_type *p)
{
	if (p == NULL) return;
	SpecialCommandPPCNumberList_org_code_type_purge(p);
	Dz1Free(p);
}

void SpecialCommandPPCNumberList_org_code_type_dump(SpecialCommandPPCNumberList_org_code_type *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("org_code_type = ")); Dz1u32_dump(&p->org_code_type, tab); 
	}
}
// SpecialCommandPPCNumberList_org_code_type
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList
SpecialCommandPPCNumberList *SpecialCommandPPCNumberList_new(SpecialCommandPPCNumberList_is_emergency *is_emergency, 
															 SpecialCommandPPCNumberList_org_code *org_code, 
															 SpecialCommandPPCNumberList_org_code_num *org_code_num, 
															 SpecialCommandPPCNumberList_org_code_type *org_code_type, 
															 SpecialCommandPPCVehicleProperties *vehicle_properties, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandPPCNumberList *__internal_ret = (SpecialCommandPPCNumberList *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->is_emergency = is_emergency;
		__internal_ret->org_code = org_code;
		__internal_ret->org_code_num = org_code_num;
		__internal_ret->org_code_type = org_code_type;
		__internal_ret->vehicle_properties = vehicle_properties;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandPPCNumberList_copy(SpecialCommandPPCNumberList *dst, SpecialCommandPPCNumberList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->is_emergency && (dst->is_emergency = SpecialCommandPPCNumberList_is_emergency_clone(src->is_emergency, errp)) == NULL) ERR_OUT(errp);
	else if (src->org_code && (dst->org_code = SpecialCommandPPCNumberList_org_code_clone(src->org_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->org_code_num && (dst->org_code_num = SpecialCommandPPCNumberList_org_code_num_clone(src->org_code_num, errp)) == NULL) ERR_OUT(errp);
	else if (src->org_code_type && (dst->org_code_type = SpecialCommandPPCNumberList_org_code_type_clone(src->org_code_type, errp)) == NULL) ERR_OUT(errp);
	else if (src->vehicle_properties && (dst->vehicle_properties = SpecialCommandPPCVehicleProperties_clone(src->vehicle_properties, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandPPCNumberList *SpecialCommandPPCNumberList_clone(SpecialCommandPPCNumberList *src, Dz1Error *err)
{
	SpecialCommandPPCNumberList *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandPPCNumberList *)Dz1Calloc(sizeof(SpecialCommandPPCNumberList), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandPPCNumberList_delAndSetNull, (void *)&dst);
		if (SpecialCommandPPCNumberList_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandPPCNumberList_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandPPCNumberList_purge(SpecialCommandPPCNumberList *p)
{
	if (p == NULL) return;
	SpecialCommandPPCNumberList_is_emergency_del(p->is_emergency);
	SpecialCommandPPCNumberList_org_code_del(p->org_code);
	SpecialCommandPPCNumberList_org_code_num_del(p->org_code_num);
	SpecialCommandPPCNumberList_org_code_type_del(p->org_code_type);
	SpecialCommandPPCVehicleProperties_del(p->vehicle_properties);
}

void SpecialCommandPPCNumberList_del(SpecialCommandPPCNumberList *p)
{
	if (p == NULL) return;
	SpecialCommandPPCNumberList_purge(p);
	Dz1Free(p);
}

void SpecialCommandPPCNumberList_dump(SpecialCommandPPCNumberList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("is_emergency = ")); SpecialCommandPPCNumberList_is_emergency_dump(p->is_emergency, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("org_code = ")); SpecialCommandPPCNumberList_org_code_dump(p->org_code, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("org_code_num = ")); SpecialCommandPPCNumberList_org_code_num_dump(p->org_code_num, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("org_code_type = ")); SpecialCommandPPCNumberList_org_code_type_dump(p->org_code_type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("vehicle_properties = ")); SpecialCommandPPCVehicleProperties_dump(p->vehicle_properties, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SpecialCommandPPCNumberList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInformationResponse
SpecialCommandInformationResponse *SpecialCommandInformationResponse_new(u8_t cross_id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SpecialCommandInformationResponse *__internal_ret = (SpecialCommandInformationResponse *)Dz1Calloc(sizeof(SpecialCommandInformationResponse), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SpecialCommandInformationResponse_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandInformationResponse_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SpecialCommandInformationResponse_copy(SpecialCommandInformationResponse *dst, SpecialCommandInformationResponse *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->ppc_register_num_list && (dst->ppc_register_num_list = SpecialCommandPPCNumberList_clone(src->ppc_register_num_list, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SpecialCommandInformationResponse *SpecialCommandInformationResponse_clone(SpecialCommandInformationResponse *src, Dz1Error *err)
{
	SpecialCommandInformationResponse *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SpecialCommandInformationResponse *)Dz1Calloc(sizeof(SpecialCommandInformationResponse), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SpecialCommandInformationResponse_delAndSetNull, (void *)&dst);
		if (SpecialCommandInformationResponse_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SpecialCommandInformationResponse_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SpecialCommandInformationResponse_purge(SpecialCommandInformationResponse *p)
{
	if (p == NULL) return;
	SpecialCommandPPCNumberList_del(p->ppc_register_num_list);
}

void SpecialCommandInformationResponse_del(SpecialCommandInformationResponse *p)
{
	if (p == NULL) return;
	SpecialCommandInformationResponse_purge(p);
	Dz1Free(p);
}

void SpecialCommandInformationResponse_dump(SpecialCommandInformationResponse *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("ppc_register_num_list = ")); SpecialCommandPPCNumberList_dump(p->ppc_register_num_list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SpecialCommandInformationResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeData
FirmwareUpgradeData *FirmwareUpgradeData_new(u16_t fw_module_id, 
											 u32_t fw_module_size, 
											 Dz1Str fname, 
											 u8_t major_version, 
											 u8_t minor_version, 
											 u8_t module_version, 
											 u16_t revision_version, 
											 bool_t is_forced_upgrade, 
											 u8_t reboot_option, 
											 u32_t crc32, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	FirmwareUpgradeData *__internal_ret = (FirmwareUpgradeData *)Dz1Calloc(sizeof(FirmwareUpgradeData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(FirmwareUpgradeData_delAndSetNull, (void *)&__internal_ret);
		
		if (fname && (__internal_ret->fname = Dz1Str_clone(fname, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->fw_module_id = fw_module_id;
			__internal_ret->fw_module_size = fw_module_size;
			__internal_ret->major_version = major_version;
			__internal_ret->minor_version = minor_version;
			__internal_ret->module_version = module_version;
			__internal_ret->revision_version = revision_version;
			__internal_ret->is_forced_upgrade = is_forced_upgrade;
			__internal_ret->reboot_option = reboot_option;
			__internal_ret->crc32 = crc32;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (FirmwareUpgradeData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t FirmwareUpgradeData_copy(FirmwareUpgradeData *dst, FirmwareUpgradeData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->fname && (dst->fname = Dz1Str_clone(src->fname, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->fw_module_id = src->fw_module_id;
		dst->fw_module_size = src->fw_module_size;
		dst->major_version = src->major_version;
		dst->minor_version = src->minor_version;
		dst->module_version = src->module_version;
		dst->revision_version = src->revision_version;
		dst->is_forced_upgrade = src->is_forced_upgrade;
		dst->reboot_option = src->reboot_option;
		dst->crc32 = src->crc32;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

FirmwareUpgradeData *FirmwareUpgradeData_clone(FirmwareUpgradeData *src, Dz1Error *err)
{
	FirmwareUpgradeData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (FirmwareUpgradeData *)Dz1Calloc(sizeof(FirmwareUpgradeData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(FirmwareUpgradeData_delAndSetNull, (void *)&dst);
		if (FirmwareUpgradeData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (FirmwareUpgradeData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void FirmwareUpgradeData_purge(FirmwareUpgradeData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->fname);
}

void FirmwareUpgradeData_del(FirmwareUpgradeData *p)
{
	if (p == NULL) return;
	FirmwareUpgradeData_purge(p);
	Dz1Free(p);
}

void FirmwareUpgradeData_dump(FirmwareUpgradeData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("fw_module_id = ")); Dz1u16_dump(&p->fw_module_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fw_module_size = ")); Dz1u32_dump(&p->fw_module_size, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fname = ")); Dz1Str_dump(p->fname, tab); 
		Dz1Thread_tprintf(tab, Dz1T("major_version = ")); Dz1u8_dump(&p->major_version, tab); 
		Dz1Thread_tprintf(tab, Dz1T("minor_version = ")); Dz1u8_dump(&p->minor_version, tab); 
		Dz1Thread_tprintf(tab, Dz1T("module_version = ")); Dz1u8_dump(&p->module_version, tab); 
		Dz1Thread_tprintf(tab, Dz1T("revision_version = ")); Dz1u16_dump(&p->revision_version, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_forced_upgrade = ")); Dz1Bool_dump(&p->is_forced_upgrade, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reboot_option = ")); Dz1u8_dump(&p->reboot_option, tab); 
		Dz1Thread_tprintf(tab, Dz1T("crc32 = ")); Dz1u32_dump(&p->crc32, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// FirmwareUpgradeData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeCommand
FirmwareUpgradeCommand *FirmwareUpgradeCommand_new(u8_t cross_id, 
												   FirmwareUpgradeData *fw_upgrade_data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	FirmwareUpgradeCommand *__internal_ret = (FirmwareUpgradeCommand *)Dz1Calloc(sizeof(FirmwareUpgradeCommand), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(FirmwareUpgradeCommand_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->fw_upgrade_data = fw_upgrade_data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (FirmwareUpgradeCommand_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t FirmwareUpgradeCommand_copy(FirmwareUpgradeCommand *dst, FirmwareUpgradeCommand *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->fw_upgrade_data && (dst->fw_upgrade_data = FirmwareUpgradeData_clone(src->fw_upgrade_data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

FirmwareUpgradeCommand *FirmwareUpgradeCommand_clone(FirmwareUpgradeCommand *src, Dz1Error *err)
{
	FirmwareUpgradeCommand *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (FirmwareUpgradeCommand *)Dz1Calloc(sizeof(FirmwareUpgradeCommand), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(FirmwareUpgradeCommand_delAndSetNull, (void *)&dst);
		if (FirmwareUpgradeCommand_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (FirmwareUpgradeCommand_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void FirmwareUpgradeCommand_purge(FirmwareUpgradeCommand *p)
{
	if (p == NULL) return;
	FirmwareUpgradeData_del(p->fw_upgrade_data);
}

void FirmwareUpgradeCommand_del(FirmwareUpgradeCommand *p)
{
	if (p == NULL) return;
	FirmwareUpgradeCommand_purge(p);
	Dz1Free(p);
}

void FirmwareUpgradeCommand_dump(FirmwareUpgradeCommand *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("fw_upgrade_data = ")); FirmwareUpgradeData_dump(p->fw_upgrade_data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// FirmwareUpgradeCommand
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeErrorCode
static struct FirmwareUpgradeErrorCodeMapA
{
	str_t str;
	FirmwareUpgradeErrorCode v;
} FirmwareUpgradeErrorCodeMapA[] =
{
	{ (char *)"no_error", FirmwareUpgradeErrorCode_no_error },
	{ (char *)"lower_version_than_current_module", FirmwareUpgradeErrorCode_lower_version_than_current_module },
	{ (char *)"mismatched_vender_code", FirmwareUpgradeErrorCode_mismatched_vender_code },
	{ (char *)"crc_error", FirmwareUpgradeErrorCode_crc_error },
	{ (char *)"module_size_exceeds_the_initial_size", FirmwareUpgradeErrorCode_module_size_exceeds_the_initial_size },
	{ (char *)"other", FirmwareUpgradeErrorCode_other },
	{ NULL, FirmwareUpgradeErrorCode_max }
};

str_t FirmwareUpgradeErrorCodeStrA(FirmwareUpgradeErrorCode v)
{
	struct FirmwareUpgradeErrorCodeMapA *i = NULL;
	for (i = FirmwareUpgradeErrorCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

FirmwareUpgradeErrorCode FirmwareUpgradeErrorCodeFromStrA(str_t str)
{
	struct FirmwareUpgradeErrorCodeMapA *i = NULL;
	for (i = FirmwareUpgradeErrorCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return FirmwareUpgradeErrorCode_max;
}
#ifndef UNIX_SYSTEM
static struct FirmwareUpgradeErrorCodeMapW
{
	wstr_t str;
	FirmwareUpgradeErrorCode v;
} FirmwareUpgradeErrorCodeMapW[] =
{
	{ (wchar_t *)L"no_error", FirmwareUpgradeErrorCode_no_error },
	{ (wchar_t *)L"lower_version_than_current_module", FirmwareUpgradeErrorCode_lower_version_than_current_module },
	{ (wchar_t *)L"mismatched_vender_code", FirmwareUpgradeErrorCode_mismatched_vender_code },
	{ (wchar_t *)L"crc_error", FirmwareUpgradeErrorCode_crc_error },
	{ (wchar_t *)L"module_size_exceeds_the_initial_size", FirmwareUpgradeErrorCode_module_size_exceeds_the_initial_size },
	{ (wchar_t *)L"other", FirmwareUpgradeErrorCode_other },
	{ NULL, FirmwareUpgradeErrorCode_max }
};

wstr_t FirmwareUpgradeErrorCodeStrW(FirmwareUpgradeErrorCode v)
{
	struct FirmwareUpgradeErrorCodeMapW *i = NULL;
	for (i = FirmwareUpgradeErrorCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

FirmwareUpgradeErrorCode FirmwareUpgradeErrorCodeFromStrW(wstr_t str)
{
	struct FirmwareUpgradeErrorCodeMapW *i = NULL;
	for (i = FirmwareUpgradeErrorCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return FirmwareUpgradeErrorCode_max;
}
#endif // UNIX_SYSTEM

FirmwareUpgradeErrorCode *FirmwareUpgradeErrorCode_new(FirmwareUpgradeErrorCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	FirmwareUpgradeErrorCode *__internal_ret = (FirmwareUpgradeErrorCode *)Dz1Calloc(sizeof(FirmwareUpgradeErrorCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// FirmwareUpgradeErrorCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeError
FirmwareUpgradeError *FirmwareUpgradeError_new(FirmwareUpgradeErrorCode code, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	FirmwareUpgradeError *__internal_ret = (FirmwareUpgradeError *)Dz1Calloc(sizeof(FirmwareUpgradeError), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(FirmwareUpgradeError_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->code = code;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (FirmwareUpgradeError_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t FirmwareUpgradeError_copy(FirmwareUpgradeError *dst, FirmwareUpgradeError *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->code = src->code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

FirmwareUpgradeError *FirmwareUpgradeError_clone(FirmwareUpgradeError *src, Dz1Error *err)
{
	FirmwareUpgradeError *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (FirmwareUpgradeError *)Dz1Calloc(sizeof(FirmwareUpgradeError), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(FirmwareUpgradeError_delAndSetNull, (void *)&dst);
		if (FirmwareUpgradeError_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (FirmwareUpgradeError_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void FirmwareUpgradeError_purge(FirmwareUpgradeError *p)
{
	if (p == NULL) return;
}

void FirmwareUpgradeError_del(FirmwareUpgradeError *p)
{
	if (p == NULL) return;
	FirmwareUpgradeError_purge(p);
	Dz1Free(p);
}

void FirmwareUpgradeError_dump(FirmwareUpgradeError *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("code = %s(%d)\n"), FirmwareUpgradeErrorCodeStr(p->code), p->code);
	}
}
// FirmwareUpgradeError
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeResponse
FirmwareUpgradeResponse *FirmwareUpgradeResponse_new(u8_t cross_id, 
													 FirmwareUpgradeError *error, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	FirmwareUpgradeResponse *__internal_ret = (FirmwareUpgradeResponse *)Dz1Calloc(sizeof(FirmwareUpgradeResponse), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(FirmwareUpgradeResponse_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->error = error;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (FirmwareUpgradeResponse_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t FirmwareUpgradeResponse_copy(FirmwareUpgradeResponse *dst, FirmwareUpgradeResponse *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->error && (dst->error = FirmwareUpgradeError_clone(src->error, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

FirmwareUpgradeResponse *FirmwareUpgradeResponse_clone(FirmwareUpgradeResponse *src, Dz1Error *err)
{
	FirmwareUpgradeResponse *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (FirmwareUpgradeResponse *)Dz1Calloc(sizeof(FirmwareUpgradeResponse), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(FirmwareUpgradeResponse_delAndSetNull, (void *)&dst);
		if (FirmwareUpgradeResponse_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (FirmwareUpgradeResponse_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void FirmwareUpgradeResponse_purge(FirmwareUpgradeResponse *p)
{
	if (p == NULL) return;
	FirmwareUpgradeError_del(p->error);
}

void FirmwareUpgradeResponse_del(FirmwareUpgradeResponse *p)
{
	if (p == NULL) return;
	FirmwareUpgradeResponse_purge(p);
	Dz1Free(p);
}

void FirmwareUpgradeResponse_dump(FirmwareUpgradeResponse *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("error = ")); FirmwareUpgradeError_dump(p->error, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// FirmwareUpgradeResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerRequestPresent
static struct TrafficSignalControllerRequestPresentMapA
{
	str_t str;
	TrafficSignalControllerRequestPresent v;
} TrafficSignalControllerRequestPresentMapA[] =
{
	{ (char *)"control", TrafficSignalControllerRequestPresent_control },
	{ (char *)"status", TrafficSignalControllerRequestPresent_status },
	{ (char *)"detector", TrafficSignalControllerRequestPresent_detector },
	{ (char *)"signal_phase_down", TrafficSignalControllerRequestPresent_signal_phase_down },
	{ (char *)"signal_phase_up", TrafficSignalControllerRequestPresent_signal_phase_up },
	{ (char *)"clock_down", TrafficSignalControllerRequestPresent_clock_down },
	{ (char *)"clock_up", TrafficSignalControllerRequestPresent_clock_up },
	{ (char *)"special_cmd", TrafficSignalControllerRequestPresent_special_cmd },
	{ (char *)"fw_upgrade_cmd", TrafficSignalControllerRequestPresent_fw_upgrade_cmd },
	{ NULL, TrafficSignalControllerRequestPresent_max }
};

str_t TrafficSignalControllerRequestPresentStrA(TrafficSignalControllerRequestPresent v)
{
	struct TrafficSignalControllerRequestPresentMapA *i = NULL;
	for (i = TrafficSignalControllerRequestPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerRequestPresent TrafficSignalControllerRequestPresentFromStrA(str_t str)
{
	struct TrafficSignalControllerRequestPresentMapA *i = NULL;
	for (i = TrafficSignalControllerRequestPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerRequestPresent_max;
}
#ifndef UNIX_SYSTEM
static struct TrafficSignalControllerRequestPresentMapW
{
	wstr_t str;
	TrafficSignalControllerRequestPresent v;
} TrafficSignalControllerRequestPresentMapW[] =
{
	{ (wchar_t *)L"control", TrafficSignalControllerRequestPresent_control },
	{ (wchar_t *)L"status", TrafficSignalControllerRequestPresent_status },
	{ (wchar_t *)L"detector", TrafficSignalControllerRequestPresent_detector },
	{ (wchar_t *)L"signal_phase_down", TrafficSignalControllerRequestPresent_signal_phase_down },
	{ (wchar_t *)L"signal_phase_up", TrafficSignalControllerRequestPresent_signal_phase_up },
	{ (wchar_t *)L"clock_down", TrafficSignalControllerRequestPresent_clock_down },
	{ (wchar_t *)L"clock_up", TrafficSignalControllerRequestPresent_clock_up },
	{ (wchar_t *)L"special_cmd", TrafficSignalControllerRequestPresent_special_cmd },
	{ (wchar_t *)L"fw_upgrade_cmd", TrafficSignalControllerRequestPresent_fw_upgrade_cmd },
	{ NULL, TrafficSignalControllerRequestPresent_max }
};

wstr_t TrafficSignalControllerRequestPresentStrW(TrafficSignalControllerRequestPresent v)
{
	struct TrafficSignalControllerRequestPresentMapW *i = NULL;
	for (i = TrafficSignalControllerRequestPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerRequestPresent TrafficSignalControllerRequestPresentFromStrW(wstr_t str)
{
	struct TrafficSignalControllerRequestPresentMapW *i = NULL;
	for (i = TrafficSignalControllerRequestPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerRequestPresent_max;
}
#endif // UNIX_SYSTEM

TrafficSignalControllerRequestPresent *TrafficSignalControllerRequestPresent_new(TrafficSignalControllerRequestPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerRequestPresent *__internal_ret = (TrafficSignalControllerRequestPresent *)Dz1Calloc(sizeof(TrafficSignalControllerRequestPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void TrafficSignalControllerRequestPresent_dump(TrafficSignalControllerRequestPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), TrafficSignalControllerRequestPresentStr(*v));
}
// TrafficSignalControllerRequestPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerRequest
TrafficSignalControllerRequest *TrafficSignalControllerRequest_new(TrafficSignalControllerRequestPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerRequest *ret = (TrafficSignalControllerRequest *)Dz1Calloc(sizeof(TrafficSignalControllerRequest), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerRequest_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case TrafficSignalControllerRequestPresent_control:
			// _U_cst_clone
			if (ptr != NULL) ret->x.control = (CrossControlInformation *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerRequestPresent_status:
			// _U_cst_clone
			if (ptr != NULL) ret->x.status = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerRequestPresent_detector:
			// _U_cst_clone
			if (ptr != NULL) ret->x.detector = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerRequestPresent_signal_phase_down:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signal_phase_down = (SignalPhaseInformationDownload *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerRequestPresent_signal_phase_up:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signal_phase_up = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerRequestPresent_clock_down:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clock_down = (ClockInformationDownload *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerRequestPresent_clock_up:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clock_up = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerRequestPresent_special_cmd:
			// _U_cst_clone
			if (ptr != NULL) ret->x.special_cmd = (SpecialCommandInformation *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerRequestPresent_fw_upgrade_cmd:
			// _U_cst_clone
			if (ptr != NULL) ret->x.fw_upgrade_cmd = (FirmwareUpgradeCommand *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerRequestPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerRequest_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t TrafficSignalControllerRequest_copy(TrafficSignalControllerRequest *ret, TrafficSignalControllerRequest *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case TrafficSignalControllerRequestPresent_control:
			// _U_cst_clone
			if (src->x.control && (ret->x.control = CrossControlInformation_clone(src->x.control, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerRequestPresent_status:
			// _U_cst_clone
			if (src->x.status && (ret->x.status = CrossIndicator_clone(src->x.status, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerRequestPresent_detector:
			// _U_cst_clone
			if (src->x.detector && (ret->x.detector = CrossIndicator_clone(src->x.detector, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerRequestPresent_signal_phase_down:
			// _U_cst_clone
			if (src->x.signal_phase_down && (ret->x.signal_phase_down = SignalPhaseInformationDownload_clone(src->x.signal_phase_down, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerRequestPresent_signal_phase_up:
			// _U_cst_clone
			if (src->x.signal_phase_up && (ret->x.signal_phase_up = CrossIndicator_clone(src->x.signal_phase_up, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerRequestPresent_clock_down:
			// _U_cst_clone
			if (src->x.clock_down && (ret->x.clock_down = ClockInformationDownload_clone(src->x.clock_down, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerRequestPresent_clock_up:
			// _U_cst_clone
			if (src->x.clock_up && (ret->x.clock_up = CrossIndicator_clone(src->x.clock_up, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerRequestPresent_special_cmd:
			// _U_cst_clone
			if (src->x.special_cmd && (ret->x.special_cmd = SpecialCommandInformation_clone(src->x.special_cmd, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerRequestPresent_fw_upgrade_cmd:
			// _U_cst_clone
			if (src->x.fw_upgrade_cmd && (ret->x.fw_upgrade_cmd = FirmwareUpgradeCommand_clone(src->x.fw_upgrade_cmd, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerRequest *TrafficSignalControllerRequest_clone(TrafficSignalControllerRequest *src, Dz1Error *err)
{
	TrafficSignalControllerRequest *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (TrafficSignalControllerRequest *)Dz1Calloc(sizeof(TrafficSignalControllerRequest), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerRequest_delAndSetNull, (void *)&ret);
		if (TrafficSignalControllerRequest_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerRequest_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TrafficSignalControllerRequest_purge(TrafficSignalControllerRequest *p)
{
	if (!p) return;
	switch(p->present)
	{
	case TrafficSignalControllerRequestPresent_control:
		CrossControlInformation_del(p->x.control);
		break;
	case TrafficSignalControllerRequestPresent_status:
		CrossIndicator_del(p->x.status);
		break;
	case TrafficSignalControllerRequestPresent_detector:
		CrossIndicator_del(p->x.detector);
		break;
	case TrafficSignalControllerRequestPresent_signal_phase_down:
		SignalPhaseInformationDownload_del(p->x.signal_phase_down);
		break;
	case TrafficSignalControllerRequestPresent_signal_phase_up:
		CrossIndicator_del(p->x.signal_phase_up);
		break;
	case TrafficSignalControllerRequestPresent_clock_down:
		ClockInformationDownload_del(p->x.clock_down);
		break;
	case TrafficSignalControllerRequestPresent_clock_up:
		CrossIndicator_del(p->x.clock_up);
		break;
	case TrafficSignalControllerRequestPresent_special_cmd:
		SpecialCommandInformation_del(p->x.special_cmd);
		break;
	case TrafficSignalControllerRequestPresent_fw_upgrade_cmd:
		FirmwareUpgradeCommand_del(p->x.fw_upgrade_cmd);
		break;
	default:
		break;
	}
}

void TrafficSignalControllerRequest_del(TrafficSignalControllerRequest *p)
{
	if (!p) return;
	TrafficSignalControllerRequest_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerRequest_dump(TrafficSignalControllerRequest *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case TrafficSignalControllerRequestPresent_control:
		Dz1Thread_printf(Dz1T("control = ")); CrossControlInformation_dump(p->x.control, tab); 
		break;
	case TrafficSignalControllerRequestPresent_status:
		Dz1Thread_printf(Dz1T("status = ")); CrossIndicator_dump(p->x.status, tab); 
		break;
	case TrafficSignalControllerRequestPresent_detector:
		Dz1Thread_printf(Dz1T("detector = ")); CrossIndicator_dump(p->x.detector, tab); 
		break;
	case TrafficSignalControllerRequestPresent_signal_phase_down:
		Dz1Thread_printf(Dz1T("signal_phase_down = ")); SignalPhaseInformationDownload_dump(p->x.signal_phase_down, tab); 
		break;
	case TrafficSignalControllerRequestPresent_signal_phase_up:
		Dz1Thread_printf(Dz1T("signal_phase_up = ")); CrossIndicator_dump(p->x.signal_phase_up, tab); 
		break;
	case TrafficSignalControllerRequestPresent_clock_down:
		Dz1Thread_printf(Dz1T("clock_down = ")); ClockInformationDownload_dump(p->x.clock_down, tab); 
		break;
	case TrafficSignalControllerRequestPresent_clock_up:
		Dz1Thread_printf(Dz1T("clock_up = ")); CrossIndicator_dump(p->x.clock_up, tab); 
		break;
	case TrafficSignalControllerRequestPresent_special_cmd:
		Dz1Thread_printf(Dz1T("special_cmd = ")); SpecialCommandInformation_dump(p->x.special_cmd, tab); 
		break;
	case TrafficSignalControllerRequestPresent_fw_upgrade_cmd:
		Dz1Thread_printf(Dz1T("fw_upgrade_cmd = ")); FirmwareUpgradeCommand_dump(p->x.fw_upgrade_cmd, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// TrafficSignalControllerRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerResponsePresent
static struct TrafficSignalControllerResponsePresentMapA
{
	str_t str;
	TrafficSignalControllerResponsePresent v;
} TrafficSignalControllerResponsePresentMapA[] =
{
	{ (char *)"control", TrafficSignalControllerResponsePresent_control },
	{ (char *)"status", TrafficSignalControllerResponsePresent_status },
	{ (char *)"detector", TrafficSignalControllerResponsePresent_detector },
	{ (char *)"signal_phase_down", TrafficSignalControllerResponsePresent_signal_phase_down },
	{ (char *)"signal_phase_up", TrafficSignalControllerResponsePresent_signal_phase_up },
	{ (char *)"clock_down", TrafficSignalControllerResponsePresent_clock_down },
	{ (char *)"clock_up", TrafficSignalControllerResponsePresent_clock_up },
	{ (char *)"special_cmd", TrafficSignalControllerResponsePresent_special_cmd },
	{ (char *)"fw_upgrade_cmd", TrafficSignalControllerResponsePresent_fw_upgrade_cmd },
	{ NULL, TrafficSignalControllerResponsePresent_max }
};

str_t TrafficSignalControllerResponsePresentStrA(TrafficSignalControllerResponsePresent v)
{
	struct TrafficSignalControllerResponsePresentMapA *i = NULL;
	for (i = TrafficSignalControllerResponsePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerResponsePresent TrafficSignalControllerResponsePresentFromStrA(str_t str)
{
	struct TrafficSignalControllerResponsePresentMapA *i = NULL;
	for (i = TrafficSignalControllerResponsePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerResponsePresent_max;
}
#ifndef UNIX_SYSTEM
static struct TrafficSignalControllerResponsePresentMapW
{
	wstr_t str;
	TrafficSignalControllerResponsePresent v;
} TrafficSignalControllerResponsePresentMapW[] =
{
	{ (wchar_t *)L"control", TrafficSignalControllerResponsePresent_control },
	{ (wchar_t *)L"status", TrafficSignalControllerResponsePresent_status },
	{ (wchar_t *)L"detector", TrafficSignalControllerResponsePresent_detector },
	{ (wchar_t *)L"signal_phase_down", TrafficSignalControllerResponsePresent_signal_phase_down },
	{ (wchar_t *)L"signal_phase_up", TrafficSignalControllerResponsePresent_signal_phase_up },
	{ (wchar_t *)L"clock_down", TrafficSignalControllerResponsePresent_clock_down },
	{ (wchar_t *)L"clock_up", TrafficSignalControllerResponsePresent_clock_up },
	{ (wchar_t *)L"special_cmd", TrafficSignalControllerResponsePresent_special_cmd },
	{ (wchar_t *)L"fw_upgrade_cmd", TrafficSignalControllerResponsePresent_fw_upgrade_cmd },
	{ NULL, TrafficSignalControllerResponsePresent_max }
};

wstr_t TrafficSignalControllerResponsePresentStrW(TrafficSignalControllerResponsePresent v)
{
	struct TrafficSignalControllerResponsePresentMapW *i = NULL;
	for (i = TrafficSignalControllerResponsePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerResponsePresent TrafficSignalControllerResponsePresentFromStrW(wstr_t str)
{
	struct TrafficSignalControllerResponsePresentMapW *i = NULL;
	for (i = TrafficSignalControllerResponsePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerResponsePresent_max;
}
#endif // UNIX_SYSTEM

TrafficSignalControllerResponsePresent *TrafficSignalControllerResponsePresent_new(TrafficSignalControllerResponsePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerResponsePresent *__internal_ret = (TrafficSignalControllerResponsePresent *)Dz1Calloc(sizeof(TrafficSignalControllerResponsePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void TrafficSignalControllerResponsePresent_dump(TrafficSignalControllerResponsePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), TrafficSignalControllerResponsePresentStr(*v));
}
// TrafficSignalControllerResponsePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerResponse
TrafficSignalControllerResponse *TrafficSignalControllerResponse_new(TrafficSignalControllerResponsePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerResponse *ret = (TrafficSignalControllerResponse *)Dz1Calloc(sizeof(TrafficSignalControllerResponse), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerResponse_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case TrafficSignalControllerResponsePresent_control:
			// _U_cst_clone
			if (ptr != NULL) ret->x.control = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerResponsePresent_status:
			// _U_cst_clone
			if (ptr != NULL) ret->x.status = (CrossStatusInformation *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerResponsePresent_detector:
			// _U_cst_clone
			if (ptr != NULL) ret->x.detector = (DetectorInformation *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerResponsePresent_signal_phase_down:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signal_phase_down = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerResponsePresent_signal_phase_up:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signal_phase_up = (SignalPhaseInformationUpload *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerResponsePresent_clock_down:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clock_down = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerResponsePresent_clock_up:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clock_up = (ClockInformationUpload *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerResponsePresent_special_cmd:
			// _U_cst_clone
			if (ptr != NULL) ret->x.special_cmd = (SpecialCommandInformationResponse *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerResponsePresent_fw_upgrade_cmd:
			// _U_cst_clone
			if (ptr != NULL) ret->x.fw_upgrade_cmd = (FirmwareUpgradeResponse *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerResponsePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t TrafficSignalControllerResponse_copy(TrafficSignalControllerResponse *ret, TrafficSignalControllerResponse *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case TrafficSignalControllerResponsePresent_control:
			// _U_cst_clone
			if (src->x.control && (ret->x.control = CrossIndicator_clone(src->x.control, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerResponsePresent_status:
			// _U_cst_clone
			if (src->x.status && (ret->x.status = CrossStatusInformation_clone(src->x.status, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerResponsePresent_detector:
			// _U_cst_clone
			if (src->x.detector && (ret->x.detector = DetectorInformation_clone(src->x.detector, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerResponsePresent_signal_phase_down:
			// _U_cst_clone
			if (src->x.signal_phase_down && (ret->x.signal_phase_down = CrossIndicator_clone(src->x.signal_phase_down, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerResponsePresent_signal_phase_up:
			// _U_cst_clone
			if (src->x.signal_phase_up && (ret->x.signal_phase_up = SignalPhaseInformationUpload_clone(src->x.signal_phase_up, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerResponsePresent_clock_down:
			// _U_cst_clone
			if (src->x.clock_down && (ret->x.clock_down = CrossIndicator_clone(src->x.clock_down, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerResponsePresent_clock_up:
			// _U_cst_clone
			if (src->x.clock_up && (ret->x.clock_up = ClockInformationUpload_clone(src->x.clock_up, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerResponsePresent_special_cmd:
			// _U_cst_clone
			if (src->x.special_cmd && (ret->x.special_cmd = SpecialCommandInformationResponse_clone(src->x.special_cmd, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerResponsePresent_fw_upgrade_cmd:
			// _U_cst_clone
			if (src->x.fw_upgrade_cmd && (ret->x.fw_upgrade_cmd = FirmwareUpgradeResponse_clone(src->x.fw_upgrade_cmd, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerResponse *TrafficSignalControllerResponse_clone(TrafficSignalControllerResponse *src, Dz1Error *err)
{
	TrafficSignalControllerResponse *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (TrafficSignalControllerResponse *)Dz1Calloc(sizeof(TrafficSignalControllerResponse), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerResponse_delAndSetNull, (void *)&ret);
		if (TrafficSignalControllerResponse_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TrafficSignalControllerResponse_purge(TrafficSignalControllerResponse *p)
{
	if (!p) return;
	switch(p->present)
	{
	case TrafficSignalControllerResponsePresent_control:
		CrossIndicator_del(p->x.control);
		break;
	case TrafficSignalControllerResponsePresent_status:
		CrossStatusInformation_del(p->x.status);
		break;
	case TrafficSignalControllerResponsePresent_detector:
		DetectorInformation_del(p->x.detector);
		break;
	case TrafficSignalControllerResponsePresent_signal_phase_down:
		CrossIndicator_del(p->x.signal_phase_down);
		break;
	case TrafficSignalControllerResponsePresent_signal_phase_up:
		SignalPhaseInformationUpload_del(p->x.signal_phase_up);
		break;
	case TrafficSignalControllerResponsePresent_clock_down:
		CrossIndicator_del(p->x.clock_down);
		break;
	case TrafficSignalControllerResponsePresent_clock_up:
		ClockInformationUpload_del(p->x.clock_up);
		break;
	case TrafficSignalControllerResponsePresent_special_cmd:
		SpecialCommandInformationResponse_del(p->x.special_cmd);
		break;
	case TrafficSignalControllerResponsePresent_fw_upgrade_cmd:
		FirmwareUpgradeResponse_del(p->x.fw_upgrade_cmd);
		break;
	default:
		break;
	}
}

void TrafficSignalControllerResponse_del(TrafficSignalControllerResponse *p)
{
	if (!p) return;
	TrafficSignalControllerResponse_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerResponse_dump(TrafficSignalControllerResponse *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case TrafficSignalControllerResponsePresent_control:
		Dz1Thread_printf(Dz1T("control = ")); CrossIndicator_dump(p->x.control, tab); 
		break;
	case TrafficSignalControllerResponsePresent_status:
		Dz1Thread_printf(Dz1T("status = ")); CrossStatusInformation_dump(p->x.status, tab); 
		break;
	case TrafficSignalControllerResponsePresent_detector:
		Dz1Thread_printf(Dz1T("detector = ")); DetectorInformation_dump(p->x.detector, tab); 
		break;
	case TrafficSignalControllerResponsePresent_signal_phase_down:
		Dz1Thread_printf(Dz1T("signal_phase_down = ")); CrossIndicator_dump(p->x.signal_phase_down, tab); 
		break;
	case TrafficSignalControllerResponsePresent_signal_phase_up:
		Dz1Thread_printf(Dz1T("signal_phase_up = ")); SignalPhaseInformationUpload_dump(p->x.signal_phase_up, tab); 
		break;
	case TrafficSignalControllerResponsePresent_clock_down:
		Dz1Thread_printf(Dz1T("clock_down = ")); CrossIndicator_dump(p->x.clock_down, tab); 
		break;
	case TrafficSignalControllerResponsePresent_clock_up:
		Dz1Thread_printf(Dz1T("clock_up = ")); ClockInformationUpload_dump(p->x.clock_up, tab); 
		break;
	case TrafficSignalControllerResponsePresent_special_cmd:
		Dz1Thread_printf(Dz1T("special_cmd = ")); SpecialCommandInformationResponse_dump(p->x.special_cmd, tab); 
		break;
	case TrafficSignalControllerResponsePresent_fw_upgrade_cmd:
		Dz1Thread_printf(Dz1T("fw_upgrade_cmd = ")); FirmwareUpgradeResponse_dump(p->x.fw_upgrade_cmd, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// TrafficSignalControllerResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestConfiguration
TrafficSignalControllerTestConfiguration *TrafficSignalControllerTestConfiguration_new(u16_t port, 
																					   bool_t test_data, 
																					   u8_t cross_id, 
																					   Dz1Str req_str, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerTestConfiguration *__internal_ret = (TrafficSignalControllerTestConfiguration *)Dz1Calloc(sizeof(TrafficSignalControllerTestConfiguration), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestConfiguration_delAndSetNull, (void *)&__internal_ret);
		
		if (req_str && (__internal_ret->req_str = Dz1Str_clone(req_str, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->port = port;
			__internal_ret->test_data = test_data;
			__internal_ret->cross_id = cross_id;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestConfiguration_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerTestConfiguration_copy(TrafficSignalControllerTestConfiguration *dst, TrafficSignalControllerTestConfiguration *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->req_str && (dst->req_str = Dz1Str_clone(src->req_str, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->port = src->port;
		dst->test_data = src->test_data;
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerTestConfiguration *TrafficSignalControllerTestConfiguration_clone(TrafficSignalControllerTestConfiguration *src, Dz1Error *err)
{
	TrafficSignalControllerTestConfiguration *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerTestConfiguration *)Dz1Calloc(sizeof(TrafficSignalControllerTestConfiguration), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestConfiguration_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerTestConfiguration_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestConfiguration_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerTestConfiguration_purge(TrafficSignalControllerTestConfiguration *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->req_str);
}

void TrafficSignalControllerTestConfiguration_del(TrafficSignalControllerTestConfiguration *p)
{
	if (p == NULL) return;
	TrafficSignalControllerTestConfiguration_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerTestConfiguration_dump(TrafficSignalControllerTestConfiguration *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("port = ")); Dz1u16_dump(&p->port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_data = ")); Dz1Bool_dump(&p->test_data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("req_str = ")); Dz1Str_dump(p->req_str, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerTestConfiguration
////////////////////////////////////////////////////////////////////////////////

