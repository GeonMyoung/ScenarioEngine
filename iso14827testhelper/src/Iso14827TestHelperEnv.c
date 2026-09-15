////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827TestHelperEnv.h"

////////////////////////////////////////////////////////////////////////////////
// Prj2TxDataCheckList
Prj2TxDataCheckList *Prj2TxDataCheckList_new(bool_t test_map, 
											 bool_t test_spat, 
											 bool_t test_sdsm, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Prj2TxDataCheckList *__internal_ret = (Prj2TxDataCheckList *)Dz1Calloc(sizeof(Prj2TxDataCheckList), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Prj2TxDataCheckList_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_map = test_map;
		__internal_ret->test_spat = test_spat;
		__internal_ret->test_sdsm = test_sdsm;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Prj2TxDataCheckList_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Prj2TxDataCheckList_copy(Prj2TxDataCheckList *dst, Prj2TxDataCheckList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_map = src->test_map;
		dst->test_spat = src->test_spat;
		dst->test_sdsm = src->test_sdsm;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Prj2TxDataCheckList *Prj2TxDataCheckList_clone(Prj2TxDataCheckList *src, Dz1Error *err)
{
	Prj2TxDataCheckList *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Prj2TxDataCheckList *)Dz1Calloc(sizeof(Prj2TxDataCheckList), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Prj2TxDataCheckList_delAndSetNull, (void *)&dst);
		if (Prj2TxDataCheckList_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Prj2TxDataCheckList_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Prj2TxDataCheckList_purge(Prj2TxDataCheckList *p)
{
	if (p == NULL) return;
}

void Prj2TxDataCheckList_del(Prj2TxDataCheckList *p)
{
	if (p == NULL) return;
	Prj2TxDataCheckList_purge(p);
	Dz1Free(p);
}

void Prj2TxDataCheckList_dump(Prj2TxDataCheckList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_map = ")); Dz1Bool_dump(&p->test_map, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_spat = ")); Dz1Bool_dump(&p->test_spat, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sdsm = ")); Dz1Bool_dump(&p->test_sdsm, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Prj2TxDataCheckList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prj2RxDataCheckList
Prj2RxDataCheckList *Prj2RxDataCheckList_new(bool_t test_pvd, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Prj2RxDataCheckList *__internal_ret = (Prj2RxDataCheckList *)Dz1Calloc(sizeof(Prj2RxDataCheckList), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Prj2RxDataCheckList_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_pvd = test_pvd;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Prj2RxDataCheckList_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Prj2RxDataCheckList_copy(Prj2RxDataCheckList *dst, Prj2RxDataCheckList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_pvd = src->test_pvd;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Prj2RxDataCheckList *Prj2RxDataCheckList_clone(Prj2RxDataCheckList *src, Dz1Error *err)
{
	Prj2RxDataCheckList *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Prj2RxDataCheckList *)Dz1Calloc(sizeof(Prj2RxDataCheckList), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Prj2RxDataCheckList_delAndSetNull, (void *)&dst);
		if (Prj2RxDataCheckList_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Prj2RxDataCheckList_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Prj2RxDataCheckList_purge(Prj2RxDataCheckList *p)
{
	if (p == NULL) return;
}

void Prj2RxDataCheckList_del(Prj2RxDataCheckList *p)
{
	if (p == NULL) return;
	Prj2RxDataCheckList_purge(p);
	Dz1Free(p);
}

void Prj2RxDataCheckList_dump(Prj2RxDataCheckList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("test_pvd = ")); Dz1Bool_dump(&p->test_pvd, tab); 
	}
}
// Prj2RxDataCheckList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDataCheckListPresent
static struct Iso14827TestDataCheckListPresentMapA
{
	str_t str;
	Iso14827TestDataCheckListPresent v;
} Iso14827TestDataCheckListPresentMapA[] =
{
	{ (char *)"prj2_tx", Iso14827TestDataCheckListPresent_prj2_tx },
	{ (char *)"prj2_rx", Iso14827TestDataCheckListPresent_prj2_rx },
	{ NULL, Iso14827TestDataCheckListPresent_max }
};

str_t Iso14827TestDataCheckListPresentStrA(Iso14827TestDataCheckListPresent v)
{
	struct Iso14827TestDataCheckListPresentMapA *i = NULL;
	for (i = Iso14827TestDataCheckListPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDataCheckListPresent Iso14827TestDataCheckListPresentFromStrA(str_t str)
{
	struct Iso14827TestDataCheckListPresentMapA *i = NULL;
	for (i = Iso14827TestDataCheckListPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDataCheckListPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestDataCheckListPresentMapW
{
	wstr_t str;
	Iso14827TestDataCheckListPresent v;
} Iso14827TestDataCheckListPresentMapW[] =
{
	{ (wchar_t *)L"prj2_tx", Iso14827TestDataCheckListPresent_prj2_tx },
	{ (wchar_t *)L"prj2_rx", Iso14827TestDataCheckListPresent_prj2_rx },
	{ NULL, Iso14827TestDataCheckListPresent_max }
};

wstr_t Iso14827TestDataCheckListPresentStrW(Iso14827TestDataCheckListPresent v)
{
	struct Iso14827TestDataCheckListPresentMapW *i = NULL;
	for (i = Iso14827TestDataCheckListPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDataCheckListPresent Iso14827TestDataCheckListPresentFromStrW(wstr_t str)
{
	struct Iso14827TestDataCheckListPresentMapW *i = NULL;
	for (i = Iso14827TestDataCheckListPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDataCheckListPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestDataCheckListPresent *Iso14827TestDataCheckListPresent_new(Iso14827TestDataCheckListPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestDataCheckListPresent *__internal_ret = (Iso14827TestDataCheckListPresent *)Dz1Calloc(sizeof(Iso14827TestDataCheckListPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TestDataCheckListPresent_dump(Iso14827TestDataCheckListPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TestDataCheckListPresentStr(*v));
}
// Iso14827TestDataCheckListPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDataCheckList
Iso14827TestDataCheckList *Iso14827TestDataCheckList_new(Iso14827TestDataCheckListPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestDataCheckList *ret = (Iso14827TestDataCheckList *)Dz1Calloc(sizeof(Iso14827TestDataCheckList), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestDataCheckList_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827TestDataCheckListPresent_prj2_tx:
			// _U_cst_clone
			if (ptr != NULL) ret->x.prj2_tx = (Prj2TxDataCheckList *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestDataCheckListPresent_prj2_rx:
			// _U_cst_clone
			if (ptr != NULL) ret->x.prj2_rx = (Prj2RxDataCheckList *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestDataCheckListPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestDataCheckList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827TestDataCheckList_copy(Iso14827TestDataCheckList *ret, Iso14827TestDataCheckList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827TestDataCheckListPresent_prj2_tx:
			// _U_cst_clone
			if (src->x.prj2_tx && (ret->x.prj2_tx = Prj2TxDataCheckList_clone(src->x.prj2_tx, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestDataCheckListPresent_prj2_rx:
			// _U_cst_clone
			if (src->x.prj2_rx && (ret->x.prj2_rx = Prj2RxDataCheckList_clone(src->x.prj2_rx, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestDataCheckList *Iso14827TestDataCheckList_clone(Iso14827TestDataCheckList *src, Dz1Error *err)
{
	Iso14827TestDataCheckList *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827TestDataCheckList *)Dz1Calloc(sizeof(Iso14827TestDataCheckList), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestDataCheckList_delAndSetNull, (void *)&ret);
		if (Iso14827TestDataCheckList_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestDataCheckList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestDataCheckList_purge(Iso14827TestDataCheckList *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827TestDataCheckListPresent_prj2_tx:
		Prj2TxDataCheckList_del(p->x.prj2_tx);
		break;
	case Iso14827TestDataCheckListPresent_prj2_rx:
		Prj2RxDataCheckList_del(p->x.prj2_rx);
		break;
	default:
		break;
	}
}

void Iso14827TestDataCheckList_del(Iso14827TestDataCheckList *p)
{
	if (!p) return;
	Iso14827TestDataCheckList_purge(p);
	Dz1Free(p);
}

void Iso14827TestDataCheckList_dump(Iso14827TestDataCheckList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827TestDataCheckListPresent_prj2_tx:
		Dz1Thread_printf(Dz1T("prj2_tx = ")); Prj2TxDataCheckList_dump(p->x.prj2_tx, tab); 
		break;
	case Iso14827TestDataCheckListPresent_prj2_rx:
		Dz1Thread_printf(Dz1T("prj2_rx = ")); Prj2RxDataCheckList_dump(p->x.prj2_rx, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827TestDataCheckList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestScenarioSetup
Iso14827TestScenarioSetup *Iso14827TestScenarioSetup_new(Iso14827TestScenario *scenario, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestScenarioSetup *__internal_ret = (Iso14827TestScenarioSetup *)Dz1Calloc(sizeof(Iso14827TestScenarioSetup), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestScenarioSetup_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->scenario = scenario;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestScenarioSetup_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestScenarioSetup_copy(Iso14827TestScenarioSetup *dst, Iso14827TestScenarioSetup *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->scenario && (dst->scenario = Iso14827TestScenario_clone(src->scenario, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestScenarioSetup *Iso14827TestScenarioSetup_clone(Iso14827TestScenarioSetup *src, Dz1Error *err)
{
	Iso14827TestScenarioSetup *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestScenarioSetup *)Dz1Calloc(sizeof(Iso14827TestScenarioSetup), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestScenarioSetup_delAndSetNull, (void *)&dst);
		if (Iso14827TestScenarioSetup_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestScenarioSetup_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestScenarioSetup_purge(Iso14827TestScenarioSetup *p)
{
	if (p == NULL) return;
	Iso14827TestScenario_del(p->scenario);
}

void Iso14827TestScenarioSetup_del(Iso14827TestScenarioSetup *p)
{
	if (p == NULL) return;
	Iso14827TestScenarioSetup_purge(p);
	Dz1Free(p);
}

void Iso14827TestScenarioSetup_dump(Iso14827TestScenarioSetup *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("scenario.")); Iso14827TestScenario_dump(p->scenario, tab); 
	}
}
// Iso14827TestScenarioSetup
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClient1State
static struct Iso14827TestClient1StateMapA
{
	str_t str;
	Iso14827TestClient1State v;
} Iso14827TestClient1StateMapA[] =
{
	{ (char *)"initial", Iso14827TestClient1State_initial },
	{ (char *)"wait_initiate", Iso14827TestClient1State_wait_initiate },
	{ (char *)"wait_login_dup", Iso14827TestClient1State_wait_login_dup },
	{ (char *)"wait_disconnect", Iso14827TestClient1State_wait_disconnect },
	{ (char *)"wait_restart", Iso14827TestClient1State_wait_restart },
	{ (char *)"wait_invalid_subs", Iso14827TestClient1State_wait_invalid_subs },
	{ (char *)"wait_normal_subs", Iso14827TestClient1State_wait_normal_subs },
	{ (char *)"wait_subs_cancel", Iso14827TestClient1State_wait_subs_cancel },
	{ (char *)"wait_deferred_ack", Iso14827TestClient1State_wait_deferred_ack },
	{ (char *)"wait_terminate", Iso14827TestClient1State_wait_terminate },
	{ (char *)"complete", Iso14827TestClient1State_complete },
	{ NULL, Iso14827TestClient1State_max }
};

str_t Iso14827TestClient1StateStrA(Iso14827TestClient1State v)
{
	struct Iso14827TestClient1StateMapA *i = NULL;
	for (i = Iso14827TestClient1StateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestClient1State Iso14827TestClient1StateFromStrA(str_t str)
{
	struct Iso14827TestClient1StateMapA *i = NULL;
	for (i = Iso14827TestClient1StateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestClient1State_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestClient1StateMapW
{
	wstr_t str;
	Iso14827TestClient1State v;
} Iso14827TestClient1StateMapW[] =
{
	{ (wchar_t *)L"initial", Iso14827TestClient1State_initial },
	{ (wchar_t *)L"wait_initiate", Iso14827TestClient1State_wait_initiate },
	{ (wchar_t *)L"wait_login_dup", Iso14827TestClient1State_wait_login_dup },
	{ (wchar_t *)L"wait_disconnect", Iso14827TestClient1State_wait_disconnect },
	{ (wchar_t *)L"wait_restart", Iso14827TestClient1State_wait_restart },
	{ (wchar_t *)L"wait_invalid_subs", Iso14827TestClient1State_wait_invalid_subs },
	{ (wchar_t *)L"wait_normal_subs", Iso14827TestClient1State_wait_normal_subs },
	{ (wchar_t *)L"wait_subs_cancel", Iso14827TestClient1State_wait_subs_cancel },
	{ (wchar_t *)L"wait_deferred_ack", Iso14827TestClient1State_wait_deferred_ack },
	{ (wchar_t *)L"wait_terminate", Iso14827TestClient1State_wait_terminate },
	{ (wchar_t *)L"complete", Iso14827TestClient1State_complete },
	{ NULL, Iso14827TestClient1State_max }
};

wstr_t Iso14827TestClient1StateStrW(Iso14827TestClient1State v)
{
	struct Iso14827TestClient1StateMapW *i = NULL;
	for (i = Iso14827TestClient1StateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestClient1State Iso14827TestClient1StateFromStrW(wstr_t str)
{
	struct Iso14827TestClient1StateMapW *i = NULL;
	for (i = Iso14827TestClient1StateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestClient1State_max;
}
#endif // UNIX_SYSTEM

Iso14827TestClient1State *Iso14827TestClient1State_new(Iso14827TestClient1State *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClient1State *__internal_ret = (Iso14827TestClient1State *)Dz1Calloc(sizeof(Iso14827TestClient1State), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestClient1State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClient2State
static struct Iso14827TestClient2StateMapA
{
	str_t str;
	Iso14827TestClient2State v;
} Iso14827TestClient2StateMapA[] =
{
	{ (char *)"initial", Iso14827TestClient2State_initial },
	{ (char *)"connected", Iso14827TestClient2State_connected },
	{ (char *)"wait_total_test", Iso14827TestClient2State_wait_total_test },
	{ (char *)"wait_terminate", Iso14827TestClient2State_wait_terminate },
	{ (char *)"complete", Iso14827TestClient2State_complete },
	{ NULL, Iso14827TestClient2State_max }
};

str_t Iso14827TestClient2StateStrA(Iso14827TestClient2State v)
{
	struct Iso14827TestClient2StateMapA *i = NULL;
	for (i = Iso14827TestClient2StateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestClient2State Iso14827TestClient2StateFromStrA(str_t str)
{
	struct Iso14827TestClient2StateMapA *i = NULL;
	for (i = Iso14827TestClient2StateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestClient2State_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestClient2StateMapW
{
	wstr_t str;
	Iso14827TestClient2State v;
} Iso14827TestClient2StateMapW[] =
{
	{ (wchar_t *)L"initial", Iso14827TestClient2State_initial },
	{ (wchar_t *)L"connected", Iso14827TestClient2State_connected },
	{ (wchar_t *)L"wait_total_test", Iso14827TestClient2State_wait_total_test },
	{ (wchar_t *)L"wait_terminate", Iso14827TestClient2State_wait_terminate },
	{ (wchar_t *)L"complete", Iso14827TestClient2State_complete },
	{ NULL, Iso14827TestClient2State_max }
};

wstr_t Iso14827TestClient2StateStrW(Iso14827TestClient2State v)
{
	struct Iso14827TestClient2StateMapW *i = NULL;
	for (i = Iso14827TestClient2StateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestClient2State Iso14827TestClient2StateFromStrW(wstr_t str)
{
	struct Iso14827TestClient2StateMapW *i = NULL;
	for (i = Iso14827TestClient2StateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestClient2State_max;
}
#endif // UNIX_SYSTEM

Iso14827TestClient2State *Iso14827TestClient2State_new(Iso14827TestClient2State *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClient2State *__internal_ret = (Iso14827TestClient2State *)Dz1Calloc(sizeof(Iso14827TestClient2State), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestClient2State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoClientState
static struct Iso14827TestDuoClientStateMapA
{
	str_t str;
	Iso14827TestDuoClientState v;
} Iso14827TestDuoClientStateMapA[] =
{
	{ (char *)"initial", Iso14827TestDuoClientState_initial },
	{ (char *)"wait_duo_client1_established", Iso14827TestDuoClientState_wait_duo_client1_established },
	{ (char *)"wait_duo_subs_test", Iso14827TestDuoClientState_wait_duo_subs_test },
	{ (char *)"wait_duo_terminate", Iso14827TestDuoClientState_wait_duo_terminate },
	{ (char *)"wait_terminate", Iso14827TestDuoClientState_wait_terminate },
	{ (char *)"complete", Iso14827TestDuoClientState_complete },
	{ NULL, Iso14827TestDuoClientState_max }
};

str_t Iso14827TestDuoClientStateStrA(Iso14827TestDuoClientState v)
{
	struct Iso14827TestDuoClientStateMapA *i = NULL;
	for (i = Iso14827TestDuoClientStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDuoClientState Iso14827TestDuoClientStateFromStrA(str_t str)
{
	struct Iso14827TestDuoClientStateMapA *i = NULL;
	for (i = Iso14827TestDuoClientStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDuoClientState_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestDuoClientStateMapW
{
	wstr_t str;
	Iso14827TestDuoClientState v;
} Iso14827TestDuoClientStateMapW[] =
{
	{ (wchar_t *)L"initial", Iso14827TestDuoClientState_initial },
	{ (wchar_t *)L"wait_duo_client1_established", Iso14827TestDuoClientState_wait_duo_client1_established },
	{ (wchar_t *)L"wait_duo_subs_test", Iso14827TestDuoClientState_wait_duo_subs_test },
	{ (wchar_t *)L"wait_duo_terminate", Iso14827TestDuoClientState_wait_duo_terminate },
	{ (wchar_t *)L"wait_terminate", Iso14827TestDuoClientState_wait_terminate },
	{ (wchar_t *)L"complete", Iso14827TestDuoClientState_complete },
	{ NULL, Iso14827TestDuoClientState_max }
};

wstr_t Iso14827TestDuoClientStateStrW(Iso14827TestDuoClientState v)
{
	struct Iso14827TestDuoClientStateMapW *i = NULL;
	for (i = Iso14827TestDuoClientStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDuoClientState Iso14827TestDuoClientStateFromStrW(wstr_t str)
{
	struct Iso14827TestDuoClientStateMapW *i = NULL;
	for (i = Iso14827TestDuoClientStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDuoClientState_max;
}
#endif // UNIX_SYSTEM

Iso14827TestDuoClientState *Iso14827TestDuoClientState_new(Iso14827TestDuoClientState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestDuoClientState *__internal_ret = (Iso14827TestDuoClientState *)Dz1Calloc(sizeof(Iso14827TestDuoClientState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestDuoClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServer1State
static struct Iso14827TestServer1StateMapA
{
	str_t str;
	Iso14827TestServer1State v;
} Iso14827TestServer1StateMapA[] =
{
	{ (char *)"initial", Iso14827TestServer1State_initial },
	{ (char *)"wait_auth", Iso14827TestServer1State_wait_auth },
	{ (char *)"wait_connected", Iso14827TestServer1State_wait_connected },
	{ (char *)"established", Iso14827TestServer1State_established },
	{ (char *)"wait_violated_pub", Iso14827TestServer1State_wait_violated_pub },
	{ (char *)"wait_disconnect", Iso14827TestServer1State_wait_disconnect },
	{ (char *)"complete", Iso14827TestServer1State_complete },
	{ NULL, Iso14827TestServer1State_max }
};

str_t Iso14827TestServer1StateStrA(Iso14827TestServer1State v)
{
	struct Iso14827TestServer1StateMapA *i = NULL;
	for (i = Iso14827TestServer1StateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestServer1State Iso14827TestServer1StateFromStrA(str_t str)
{
	struct Iso14827TestServer1StateMapA *i = NULL;
	for (i = Iso14827TestServer1StateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestServer1State_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestServer1StateMapW
{
	wstr_t str;
	Iso14827TestServer1State v;
} Iso14827TestServer1StateMapW[] =
{
	{ (wchar_t *)L"initial", Iso14827TestServer1State_initial },
	{ (wchar_t *)L"wait_auth", Iso14827TestServer1State_wait_auth },
	{ (wchar_t *)L"wait_connected", Iso14827TestServer1State_wait_connected },
	{ (wchar_t *)L"established", Iso14827TestServer1State_established },
	{ (wchar_t *)L"wait_violated_pub", Iso14827TestServer1State_wait_violated_pub },
	{ (wchar_t *)L"wait_disconnect", Iso14827TestServer1State_wait_disconnect },
	{ (wchar_t *)L"complete", Iso14827TestServer1State_complete },
	{ NULL, Iso14827TestServer1State_max }
};

wstr_t Iso14827TestServer1StateStrW(Iso14827TestServer1State v)
{
	struct Iso14827TestServer1StateMapW *i = NULL;
	for (i = Iso14827TestServer1StateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestServer1State Iso14827TestServer1StateFromStrW(wstr_t str)
{
	struct Iso14827TestServer1StateMapW *i = NULL;
	for (i = Iso14827TestServer1StateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestServer1State_max;
}
#endif // UNIX_SYSTEM

Iso14827TestServer1State *Iso14827TestServer1State_new(Iso14827TestServer1State *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServer1State *__internal_ret = (Iso14827TestServer1State *)Dz1Calloc(sizeof(Iso14827TestServer1State), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestServer1State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServer2State
static struct Iso14827TestServer2StateMapA
{
	str_t str;
	Iso14827TestServer2State v;
} Iso14827TestServer2StateMapA[] =
{
	{ (char *)"initial", Iso14827TestServer2State_initial },
	{ (char *)"wait_auth", Iso14827TestServer2State_wait_auth },
	{ (char *)"wait_connected", Iso14827TestServer2State_wait_connected },
	{ (char *)"established", Iso14827TestServer2State_established },
	{ (char *)"wait_timeout", Iso14827TestServer2State_wait_timeout },
	{ (char *)"wait_logout", Iso14827TestServer2State_wait_logout },
	{ (char *)"complete", Iso14827TestServer2State_complete },
	{ NULL, Iso14827TestServer2State_max }
};

str_t Iso14827TestServer2StateStrA(Iso14827TestServer2State v)
{
	struct Iso14827TestServer2StateMapA *i = NULL;
	for (i = Iso14827TestServer2StateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestServer2State Iso14827TestServer2StateFromStrA(str_t str)
{
	struct Iso14827TestServer2StateMapA *i = NULL;
	for (i = Iso14827TestServer2StateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestServer2State_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestServer2StateMapW
{
	wstr_t str;
	Iso14827TestServer2State v;
} Iso14827TestServer2StateMapW[] =
{
	{ (wchar_t *)L"initial", Iso14827TestServer2State_initial },
	{ (wchar_t *)L"wait_auth", Iso14827TestServer2State_wait_auth },
	{ (wchar_t *)L"wait_connected", Iso14827TestServer2State_wait_connected },
	{ (wchar_t *)L"established", Iso14827TestServer2State_established },
	{ (wchar_t *)L"wait_timeout", Iso14827TestServer2State_wait_timeout },
	{ (wchar_t *)L"wait_logout", Iso14827TestServer2State_wait_logout },
	{ (wchar_t *)L"complete", Iso14827TestServer2State_complete },
	{ NULL, Iso14827TestServer2State_max }
};

wstr_t Iso14827TestServer2StateStrW(Iso14827TestServer2State v)
{
	struct Iso14827TestServer2StateMapW *i = NULL;
	for (i = Iso14827TestServer2StateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestServer2State Iso14827TestServer2StateFromStrW(wstr_t str)
{
	struct Iso14827TestServer2StateMapW *i = NULL;
	for (i = Iso14827TestServer2StateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestServer2State_max;
}
#endif // UNIX_SYSTEM

Iso14827TestServer2State *Iso14827TestServer2State_new(Iso14827TestServer2State *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServer2State *__internal_ret = (Iso14827TestServer2State *)Dz1Calloc(sizeof(Iso14827TestServer2State), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestServer2State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServer3State
static struct Iso14827TestServer3StateMapA
{
	str_t str;
	Iso14827TestServer3State v;
} Iso14827TestServer3StateMapA[] =
{
	{ (char *)"initial", Iso14827TestServer3State_initial },
	{ (char *)"wait_auth", Iso14827TestServer3State_wait_auth },
	{ (char *)"wait_connected", Iso14827TestServer3State_wait_connected },
	{ (char *)"established", Iso14827TestServer3State_established },
	{ (char *)"wait_timeout", Iso14827TestServer3State_wait_timeout },
	{ (char *)"wait_disconnect", Iso14827TestServer3State_wait_disconnect },
	{ (char *)"complete", Iso14827TestServer3State_complete },
	{ NULL, Iso14827TestServer3State_max }
};

str_t Iso14827TestServer3StateStrA(Iso14827TestServer3State v)
{
	struct Iso14827TestServer3StateMapA *i = NULL;
	for (i = Iso14827TestServer3StateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestServer3State Iso14827TestServer3StateFromStrA(str_t str)
{
	struct Iso14827TestServer3StateMapA *i = NULL;
	for (i = Iso14827TestServer3StateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestServer3State_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestServer3StateMapW
{
	wstr_t str;
	Iso14827TestServer3State v;
} Iso14827TestServer3StateMapW[] =
{
	{ (wchar_t *)L"initial", Iso14827TestServer3State_initial },
	{ (wchar_t *)L"wait_auth", Iso14827TestServer3State_wait_auth },
	{ (wchar_t *)L"wait_connected", Iso14827TestServer3State_wait_connected },
	{ (wchar_t *)L"established", Iso14827TestServer3State_established },
	{ (wchar_t *)L"wait_timeout", Iso14827TestServer3State_wait_timeout },
	{ (wchar_t *)L"wait_disconnect", Iso14827TestServer3State_wait_disconnect },
	{ (wchar_t *)L"complete", Iso14827TestServer3State_complete },
	{ NULL, Iso14827TestServer3State_max }
};

wstr_t Iso14827TestServer3StateStrW(Iso14827TestServer3State v)
{
	struct Iso14827TestServer3StateMapW *i = NULL;
	for (i = Iso14827TestServer3StateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestServer3State Iso14827TestServer3StateFromStrW(wstr_t str)
{
	struct Iso14827TestServer3StateMapW *i = NULL;
	for (i = Iso14827TestServer3StateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestServer3State_max;
}
#endif // UNIX_SYSTEM

Iso14827TestServer3State *Iso14827TestServer3State_new(Iso14827TestServer3State *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServer3State *__internal_ret = (Iso14827TestServer3State *)Dz1Calloc(sizeof(Iso14827TestServer3State), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestServer3State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoSessionServerState
static struct Iso14827TestDuoSessionServerStateMapA
{
	str_t str;
	Iso14827TestDuoSessionServerState v;
} Iso14827TestDuoSessionServerStateMapA[] =
{
	{ (char *)"initial", Iso14827TestDuoSessionServerState_initial },
	{ (char *)"wait_auth", Iso14827TestDuoSessionServerState_wait_auth },
	{ (char *)"wait_connected", Iso14827TestDuoSessionServerState_wait_connected },
	{ (char *)"established", Iso14827TestDuoSessionServerState_established },
	{ (char *)"idle", Iso14827TestDuoSessionServerState_idle },
	{ (char *)"wait_logout", Iso14827TestDuoSessionServerState_wait_logout },
	{ (char *)"complete", Iso14827TestDuoSessionServerState_complete },
	{ NULL, Iso14827TestDuoSessionServerState_max }
};

str_t Iso14827TestDuoSessionServerStateStrA(Iso14827TestDuoSessionServerState v)
{
	struct Iso14827TestDuoSessionServerStateMapA *i = NULL;
	for (i = Iso14827TestDuoSessionServerStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDuoSessionServerState Iso14827TestDuoSessionServerStateFromStrA(str_t str)
{
	struct Iso14827TestDuoSessionServerStateMapA *i = NULL;
	for (i = Iso14827TestDuoSessionServerStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDuoSessionServerState_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestDuoSessionServerStateMapW
{
	wstr_t str;
	Iso14827TestDuoSessionServerState v;
} Iso14827TestDuoSessionServerStateMapW[] =
{
	{ (wchar_t *)L"initial", Iso14827TestDuoSessionServerState_initial },
	{ (wchar_t *)L"wait_auth", Iso14827TestDuoSessionServerState_wait_auth },
	{ (wchar_t *)L"wait_connected", Iso14827TestDuoSessionServerState_wait_connected },
	{ (wchar_t *)L"established", Iso14827TestDuoSessionServerState_established },
	{ (wchar_t *)L"idle", Iso14827TestDuoSessionServerState_idle },
	{ (wchar_t *)L"wait_logout", Iso14827TestDuoSessionServerState_wait_logout },
	{ (wchar_t *)L"complete", Iso14827TestDuoSessionServerState_complete },
	{ NULL, Iso14827TestDuoSessionServerState_max }
};

wstr_t Iso14827TestDuoSessionServerStateStrW(Iso14827TestDuoSessionServerState v)
{
	struct Iso14827TestDuoSessionServerStateMapW *i = NULL;
	for (i = Iso14827TestDuoSessionServerStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDuoSessionServerState Iso14827TestDuoSessionServerStateFromStrW(wstr_t str)
{
	struct Iso14827TestDuoSessionServerStateMapW *i = NULL;
	for (i = Iso14827TestDuoSessionServerStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDuoSessionServerState_max;
}
#endif // UNIX_SYSTEM

Iso14827TestDuoSessionServerState *Iso14827TestDuoSessionServerState_new(Iso14827TestDuoSessionServerState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestDuoSessionServerState *__internal_ret = (Iso14827TestDuoSessionServerState *)Dz1Calloc(sizeof(Iso14827TestDuoSessionServerState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestDuoSessionServerState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoSessionClientState
static struct Iso14827TestDuoSessionClientStateMapA
{
	str_t str;
	Iso14827TestDuoSessionClientState v;
} Iso14827TestDuoSessionClientStateMapA[] =
{
	{ (char *)"initial", Iso14827TestDuoSessionClientState_initial },
	{ (char *)"wait_initiate", Iso14827TestDuoSessionClientState_wait_initiate },
	{ (char *)"wait_heartbeat", Iso14827TestDuoSessionClientState_wait_heartbeat },
	{ (char *)"wait_pub_data", Iso14827TestDuoSessionClientState_wait_pub_data },
	{ (char *)"idle", Iso14827TestDuoSessionClientState_idle },
	{ (char *)"wait_disconnect", Iso14827TestDuoSessionClientState_wait_disconnect },
	{ (char *)"complete", Iso14827TestDuoSessionClientState_complete },
	{ NULL, Iso14827TestDuoSessionClientState_max }
};

str_t Iso14827TestDuoSessionClientStateStrA(Iso14827TestDuoSessionClientState v)
{
	struct Iso14827TestDuoSessionClientStateMapA *i = NULL;
	for (i = Iso14827TestDuoSessionClientStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDuoSessionClientState Iso14827TestDuoSessionClientStateFromStrA(str_t str)
{
	struct Iso14827TestDuoSessionClientStateMapA *i = NULL;
	for (i = Iso14827TestDuoSessionClientStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDuoSessionClientState_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestDuoSessionClientStateMapW
{
	wstr_t str;
	Iso14827TestDuoSessionClientState v;
} Iso14827TestDuoSessionClientStateMapW[] =
{
	{ (wchar_t *)L"initial", Iso14827TestDuoSessionClientState_initial },
	{ (wchar_t *)L"wait_initiate", Iso14827TestDuoSessionClientState_wait_initiate },
	{ (wchar_t *)L"wait_heartbeat", Iso14827TestDuoSessionClientState_wait_heartbeat },
	{ (wchar_t *)L"wait_pub_data", Iso14827TestDuoSessionClientState_wait_pub_data },
	{ (wchar_t *)L"idle", Iso14827TestDuoSessionClientState_idle },
	{ (wchar_t *)L"wait_disconnect", Iso14827TestDuoSessionClientState_wait_disconnect },
	{ (wchar_t *)L"complete", Iso14827TestDuoSessionClientState_complete },
	{ NULL, Iso14827TestDuoSessionClientState_max }
};

wstr_t Iso14827TestDuoSessionClientStateStrW(Iso14827TestDuoSessionClientState v)
{
	struct Iso14827TestDuoSessionClientStateMapW *i = NULL;
	for (i = Iso14827TestDuoSessionClientStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDuoSessionClientState Iso14827TestDuoSessionClientStateFromStrW(wstr_t str)
{
	struct Iso14827TestDuoSessionClientStateMapW *i = NULL;
	for (i = Iso14827TestDuoSessionClientStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDuoSessionClientState_max;
}
#endif // UNIX_SYSTEM

Iso14827TestDuoSessionClientState *Iso14827TestDuoSessionClientState_new(Iso14827TestDuoSessionClientState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestDuoSessionClientState *__internal_ret = (Iso14827TestDuoSessionClientState *)Dz1Calloc(sizeof(Iso14827TestDuoSessionClientState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestDuoSessionClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientEvent
static struct Iso14827TestClientEventMapA
{
	str_t str;
	Iso14827TestClientEvent v;
} Iso14827TestClientEventMapA[] =
{
	{ (char *)"start", Iso14827TestClientEvent_start },
	{ (char *)"trigger", Iso14827TestClientEvent_trigger },
	{ (char *)"validate", Iso14827TestClientEvent_validate },
	{ (char *)"initiated", Iso14827TestClientEvent_initiated },
	{ (char *)"echo", Iso14827TestClientEvent_echo },
	{ (char *)"data", Iso14827TestClientEvent_data },
	{ (char *)"data_ctrl", Iso14827TestClientEvent_data_ctrl },
	{ (char *)"terminate", Iso14827TestClientEvent_terminate },
	{ (char *)"disconnected", Iso14827TestClientEvent_disconnected },
	{ (char *)"sub_received", Iso14827TestClientEvent_sub_received },
	{ (char *)"timeout", Iso14827TestClientEvent_timeout },
	{ NULL, Iso14827TestClientEvent_max }
};

str_t Iso14827TestClientEventStrA(Iso14827TestClientEvent v)
{
	struct Iso14827TestClientEventMapA *i = NULL;
	for (i = Iso14827TestClientEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestClientEvent Iso14827TestClientEventFromStrA(str_t str)
{
	struct Iso14827TestClientEventMapA *i = NULL;
	for (i = Iso14827TestClientEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestClientEvent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestClientEventMapW
{
	wstr_t str;
	Iso14827TestClientEvent v;
} Iso14827TestClientEventMapW[] =
{
	{ (wchar_t *)L"start", Iso14827TestClientEvent_start },
	{ (wchar_t *)L"trigger", Iso14827TestClientEvent_trigger },
	{ (wchar_t *)L"validate", Iso14827TestClientEvent_validate },
	{ (wchar_t *)L"initiated", Iso14827TestClientEvent_initiated },
	{ (wchar_t *)L"echo", Iso14827TestClientEvent_echo },
	{ (wchar_t *)L"data", Iso14827TestClientEvent_data },
	{ (wchar_t *)L"data_ctrl", Iso14827TestClientEvent_data_ctrl },
	{ (wchar_t *)L"terminate", Iso14827TestClientEvent_terminate },
	{ (wchar_t *)L"disconnected", Iso14827TestClientEvent_disconnected },
	{ (wchar_t *)L"sub_received", Iso14827TestClientEvent_sub_received },
	{ (wchar_t *)L"timeout", Iso14827TestClientEvent_timeout },
	{ NULL, Iso14827TestClientEvent_max }
};

wstr_t Iso14827TestClientEventStrW(Iso14827TestClientEvent v)
{
	struct Iso14827TestClientEventMapW *i = NULL;
	for (i = Iso14827TestClientEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestClientEvent Iso14827TestClientEventFromStrW(wstr_t str)
{
	struct Iso14827TestClientEventMapW *i = NULL;
	for (i = Iso14827TestClientEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestClientEvent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestClientEvent *Iso14827TestClientEvent_new(Iso14827TestClientEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClientEvent *__internal_ret = (Iso14827TestClientEvent *)Dz1Calloc(sizeof(Iso14827TestClientEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestClientEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerEvent
static struct Iso14827TestServerEventMapA
{
	str_t str;
	Iso14827TestServerEvent v;
} Iso14827TestServerEventMapA[] =
{
	{ (char *)"start", Iso14827TestServerEvent_start },
	{ (char *)"validate", Iso14827TestServerEvent_validate },
	{ (char *)"auth", Iso14827TestServerEvent_auth },
	{ (char *)"connected", Iso14827TestServerEvent_connected },
	{ (char *)"heartbeat", Iso14827TestServerEvent_heartbeat },
	{ (char *)"req_single", Iso14827TestServerEvent_req_single },
	{ (char *)"req_event_driven", Iso14827TestServerEvent_req_event_driven },
	{ (char *)"req_periodic", Iso14827TestServerEvent_req_periodic },
	{ (char *)"data_start", Iso14827TestServerEvent_data_start },
	{ (char *)"data_period", Iso14827TestServerEvent_data_period },
	{ (char *)"data_stop", Iso14827TestServerEvent_data_stop },
	{ (char *)"pubdata_rejected", Iso14827TestServerEvent_pubdata_rejected },
	{ (char *)"req_expired", Iso14827TestServerEvent_req_expired },
	{ (char *)"logout", Iso14827TestServerEvent_logout },
	{ (char *)"pub_received", Iso14827TestServerEvent_pub_received },
	{ (char *)"timeout", Iso14827TestServerEvent_timeout },
	{ NULL, Iso14827TestServerEvent_max }
};

str_t Iso14827TestServerEventStrA(Iso14827TestServerEvent v)
{
	struct Iso14827TestServerEventMapA *i = NULL;
	for (i = Iso14827TestServerEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestServerEvent Iso14827TestServerEventFromStrA(str_t str)
{
	struct Iso14827TestServerEventMapA *i = NULL;
	for (i = Iso14827TestServerEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestServerEvent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestServerEventMapW
{
	wstr_t str;
	Iso14827TestServerEvent v;
} Iso14827TestServerEventMapW[] =
{
	{ (wchar_t *)L"start", Iso14827TestServerEvent_start },
	{ (wchar_t *)L"validate", Iso14827TestServerEvent_validate },
	{ (wchar_t *)L"auth", Iso14827TestServerEvent_auth },
	{ (wchar_t *)L"connected", Iso14827TestServerEvent_connected },
	{ (wchar_t *)L"heartbeat", Iso14827TestServerEvent_heartbeat },
	{ (wchar_t *)L"req_single", Iso14827TestServerEvent_req_single },
	{ (wchar_t *)L"req_event_driven", Iso14827TestServerEvent_req_event_driven },
	{ (wchar_t *)L"req_periodic", Iso14827TestServerEvent_req_periodic },
	{ (wchar_t *)L"data_start", Iso14827TestServerEvent_data_start },
	{ (wchar_t *)L"data_period", Iso14827TestServerEvent_data_period },
	{ (wchar_t *)L"data_stop", Iso14827TestServerEvent_data_stop },
	{ (wchar_t *)L"pubdata_rejected", Iso14827TestServerEvent_pubdata_rejected },
	{ (wchar_t *)L"req_expired", Iso14827TestServerEvent_req_expired },
	{ (wchar_t *)L"logout", Iso14827TestServerEvent_logout },
	{ (wchar_t *)L"pub_received", Iso14827TestServerEvent_pub_received },
	{ (wchar_t *)L"timeout", Iso14827TestServerEvent_timeout },
	{ NULL, Iso14827TestServerEvent_max }
};

wstr_t Iso14827TestServerEventStrW(Iso14827TestServerEvent v)
{
	struct Iso14827TestServerEventMapW *i = NULL;
	for (i = Iso14827TestServerEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestServerEvent Iso14827TestServerEventFromStrW(wstr_t str)
{
	struct Iso14827TestServerEventMapW *i = NULL;
	for (i = Iso14827TestServerEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestServerEvent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestServerEvent *Iso14827TestServerEvent_new(Iso14827TestServerEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServerEvent *__internal_ret = (Iso14827TestServerEvent *)Dz1Calloc(sizeof(Iso14827TestServerEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestServerEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoSessionEvent
static struct Iso14827TestDuoSessionEventMapA
{
	str_t str;
	Iso14827TestDuoSessionEvent v;
} Iso14827TestDuoSessionEventMapA[] =
{
	{ (char *)"start", Iso14827TestDuoSessionEvent_start },
	{ (char *)"trigger", Iso14827TestDuoSessionEvent_trigger },
	{ (char *)"auth", Iso14827TestDuoSessionEvent_auth },
	{ (char *)"connected", Iso14827TestDuoSessionEvent_connected },
	{ (char *)"heartbeat", Iso14827TestDuoSessionEvent_heartbeat },
	{ (char *)"req_single", Iso14827TestDuoSessionEvent_req_single },
	{ (char *)"req_event_driven", Iso14827TestDuoSessionEvent_req_event_driven },
	{ (char *)"req_periodic", Iso14827TestDuoSessionEvent_req_periodic },
	{ (char *)"data_start", Iso14827TestDuoSessionEvent_data_start },
	{ (char *)"data_period", Iso14827TestDuoSessionEvent_data_period },
	{ (char *)"data_stop", Iso14827TestDuoSessionEvent_data_stop },
	{ (char *)"pubdata_rejected", Iso14827TestDuoSessionEvent_pubdata_rejected },
	{ (char *)"req_expired", Iso14827TestDuoSessionEvent_req_expired },
	{ (char *)"logout", Iso14827TestDuoSessionEvent_logout },
	{ (char *)"pub_received", Iso14827TestDuoSessionEvent_pub_received },
	{ (char *)"initiated", Iso14827TestDuoSessionEvent_initiated },
	{ (char *)"echo", Iso14827TestDuoSessionEvent_echo },
	{ (char *)"data", Iso14827TestDuoSessionEvent_data },
	{ (char *)"data_ctrl", Iso14827TestDuoSessionEvent_data_ctrl },
	{ (char *)"terminate", Iso14827TestDuoSessionEvent_terminate },
	{ (char *)"disconnected", Iso14827TestDuoSessionEvent_disconnected },
	{ (char *)"sub_received", Iso14827TestDuoSessionEvent_sub_received },
	{ (char *)"timeout", Iso14827TestDuoSessionEvent_timeout },
	{ NULL, Iso14827TestDuoSessionEvent_max }
};

str_t Iso14827TestDuoSessionEventStrA(Iso14827TestDuoSessionEvent v)
{
	struct Iso14827TestDuoSessionEventMapA *i = NULL;
	for (i = Iso14827TestDuoSessionEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDuoSessionEvent Iso14827TestDuoSessionEventFromStrA(str_t str)
{
	struct Iso14827TestDuoSessionEventMapA *i = NULL;
	for (i = Iso14827TestDuoSessionEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDuoSessionEvent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestDuoSessionEventMapW
{
	wstr_t str;
	Iso14827TestDuoSessionEvent v;
} Iso14827TestDuoSessionEventMapW[] =
{
	{ (wchar_t *)L"start", Iso14827TestDuoSessionEvent_start },
	{ (wchar_t *)L"trigger", Iso14827TestDuoSessionEvent_trigger },
	{ (wchar_t *)L"auth", Iso14827TestDuoSessionEvent_auth },
	{ (wchar_t *)L"connected", Iso14827TestDuoSessionEvent_connected },
	{ (wchar_t *)L"heartbeat", Iso14827TestDuoSessionEvent_heartbeat },
	{ (wchar_t *)L"req_single", Iso14827TestDuoSessionEvent_req_single },
	{ (wchar_t *)L"req_event_driven", Iso14827TestDuoSessionEvent_req_event_driven },
	{ (wchar_t *)L"req_periodic", Iso14827TestDuoSessionEvent_req_periodic },
	{ (wchar_t *)L"data_start", Iso14827TestDuoSessionEvent_data_start },
	{ (wchar_t *)L"data_period", Iso14827TestDuoSessionEvent_data_period },
	{ (wchar_t *)L"data_stop", Iso14827TestDuoSessionEvent_data_stop },
	{ (wchar_t *)L"pubdata_rejected", Iso14827TestDuoSessionEvent_pubdata_rejected },
	{ (wchar_t *)L"req_expired", Iso14827TestDuoSessionEvent_req_expired },
	{ (wchar_t *)L"logout", Iso14827TestDuoSessionEvent_logout },
	{ (wchar_t *)L"pub_received", Iso14827TestDuoSessionEvent_pub_received },
	{ (wchar_t *)L"initiated", Iso14827TestDuoSessionEvent_initiated },
	{ (wchar_t *)L"echo", Iso14827TestDuoSessionEvent_echo },
	{ (wchar_t *)L"data", Iso14827TestDuoSessionEvent_data },
	{ (wchar_t *)L"data_ctrl", Iso14827TestDuoSessionEvent_data_ctrl },
	{ (wchar_t *)L"terminate", Iso14827TestDuoSessionEvent_terminate },
	{ (wchar_t *)L"disconnected", Iso14827TestDuoSessionEvent_disconnected },
	{ (wchar_t *)L"sub_received", Iso14827TestDuoSessionEvent_sub_received },
	{ (wchar_t *)L"timeout", Iso14827TestDuoSessionEvent_timeout },
	{ NULL, Iso14827TestDuoSessionEvent_max }
};

wstr_t Iso14827TestDuoSessionEventStrW(Iso14827TestDuoSessionEvent v)
{
	struct Iso14827TestDuoSessionEventMapW *i = NULL;
	for (i = Iso14827TestDuoSessionEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestDuoSessionEvent Iso14827TestDuoSessionEventFromStrW(wstr_t str)
{
	struct Iso14827TestDuoSessionEventMapW *i = NULL;
	for (i = Iso14827TestDuoSessionEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestDuoSessionEvent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestDuoSessionEvent *Iso14827TestDuoSessionEvent_new(Iso14827TestDuoSessionEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestDuoSessionEvent *__internal_ret = (Iso14827TestDuoSessionEvent *)Dz1Calloc(sizeof(Iso14827TestDuoSessionEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestDuoSessionEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestSubType
static struct Iso14827TestSubTypeMapA
{
	str_t str;
	Iso14827TestSubType v;
} Iso14827TestSubTypeMapA[] =
{
	{ (char *)"single", Iso14827TestSubType_single },
	{ (char *)"event_driven", Iso14827TestSubType_event_driven },
	{ (char *)"periodic", Iso14827TestSubType_periodic },
	{ NULL, Iso14827TestSubType_max }
};

str_t Iso14827TestSubTypeStrA(Iso14827TestSubType v)
{
	struct Iso14827TestSubTypeMapA *i = NULL;
	for (i = Iso14827TestSubTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestSubType Iso14827TestSubTypeFromStrA(str_t str)
{
	struct Iso14827TestSubTypeMapA *i = NULL;
	for (i = Iso14827TestSubTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestSubType_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestSubTypeMapW
{
	wstr_t str;
	Iso14827TestSubType v;
} Iso14827TestSubTypeMapW[] =
{
	{ (wchar_t *)L"single", Iso14827TestSubType_single },
	{ (wchar_t *)L"event_driven", Iso14827TestSubType_event_driven },
	{ (wchar_t *)L"periodic", Iso14827TestSubType_periodic },
	{ NULL, Iso14827TestSubType_max }
};

wstr_t Iso14827TestSubTypeStrW(Iso14827TestSubType v)
{
	struct Iso14827TestSubTypeMapW *i = NULL;
	for (i = Iso14827TestSubTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestSubType Iso14827TestSubTypeFromStrW(wstr_t str)
{
	struct Iso14827TestSubTypeMapW *i = NULL;
	for (i = Iso14827TestSubTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestSubType_max;
}
#endif // UNIX_SYSTEM

Iso14827TestSubType *Iso14827TestSubType_new(Iso14827TestSubType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestSubType *__internal_ret = (Iso14827TestSubType *)Dz1Calloc(sizeof(Iso14827TestSubType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestSubType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestSubEntry
Iso14827TestSubEntry *Iso14827TestSubEntry_new(Dz1Asn1UTF8Str *peer, 
											   u32_t sid, 
											   Dz1Str oid, 
											   Iso14827TestSubType type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestSubEntry *__internal_ret = (Iso14827TestSubEntry *)Dz1Calloc(sizeof(Iso14827TestSubEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestSubEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (oid && (__internal_ret->oid = Dz1Str_clone(oid, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer = peer;
			__internal_ret->sid = sid;
			__internal_ret->type = type;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestSubEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestSubEntry_copy(Iso14827TestSubEntry *dst, Iso14827TestSubEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->peer && (dst->peer = Dz1Asn1UTF8Str_clone(src->peer, errp)) == NULL) ERR_OUT(errp);
	else if (src->oid && (dst->oid = Dz1Str_clone(src->oid, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->sid = src->sid;
		dst->type = src->type;
		dst->cnt = src->cnt;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestSubEntry *Iso14827TestSubEntry_clone(Iso14827TestSubEntry *src, Dz1Error *err)
{
	Iso14827TestSubEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestSubEntry *)Dz1Calloc(sizeof(Iso14827TestSubEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestSubEntry_delAndSetNull, (void *)&dst);
		if (Iso14827TestSubEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestSubEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestSubEntry_purge(Iso14827TestSubEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->peer);
	Dz1Str_del(p->oid);
}

void Iso14827TestSubEntry_del(Iso14827TestSubEntry *p)
{
	if (p == NULL) return;
	Iso14827TestSubEntry_purge(p);
	Dz1Free(p);
}

void Iso14827TestSubEntry_dump(Iso14827TestSubEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1Asn1UTF8Str_dump(p->peer, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sid = ")); Dz1u32_dump(&p->sid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oid = ")); Dz1Str_dump(p->oid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type = %s(%d)\n"), Iso14827TestSubTypeStr(p->type), p->type);
		Dz1Thread_tprintf(tab, Dz1T("cnt = ")); Dz1u32_dump(&p->cnt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Iso14827TestSubEntry_cmp(Iso14827TestSubEntry *a, Iso14827TestSubEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->peer == NULL && b->peer == NULL) ret = 0;
	else if (a->peer == NULL /*&& b->peer != NULL*/) ret = -1;
	else if (/*a->peer != NULL &&*/ b->peer == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->peer, b->peer)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->sid, &b->sid)) != 0) { }
	return ret;
}
// Iso14827TestSubEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestSubList
static Dz1Error Iso14827TestSubList_add(Iso14827TestSubList *p, Iso14827TestSubEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t Iso14827TestSubList_remove(Iso14827TestSubList *p, Iso14827TestSubEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Iso14827TestSubEntry *Iso14827TestSubList_extract(Iso14827TestSubList *p, Iso14827TestSubEntry *key)
{
	return (Iso14827TestSubEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Iso14827TestSubListMkArrArg
{
	Iso14827TestSubEntry **arr;
	unsigned int idx;
} Iso14827TestSubListMkArrArg;

static Dz1Error _Iso14827TestSubList_get_array(void *ptr, Iso14827TestSubEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827TestSubListMkArrArg *arg = (Iso14827TestSubListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Iso14827TestSubEntry **Iso14827TestSubList_get_array(Iso14827TestSubList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Iso14827TestSubEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Iso14827TestSubEntry **)Dz1Calloc(sizeof(Iso14827TestSubEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827TestSubListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Iso14827TestSubList_get_array, (void *)&arg);
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

static Dz1Error Iso14827TestSubList_travelForward(Iso14827TestSubList *p, Dz1Error (*func)(void *ptr, Iso14827TestSubEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Iso14827TestSubList_travelBackward(Iso14827TestSubList *p, Dz1Error (*func)(void *ptr, Iso14827TestSubEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Iso14827TestSubEntry *Iso14827TestSubList_find(Iso14827TestSubList *p, Iso14827TestSubEntry *key)
{
	return (Iso14827TestSubEntry *)Dz1AATree_find(p->storage, key);
}

static Iso14827TestSubEntry *Iso14827TestSubList_getHead(Iso14827TestSubList *p)
{
	return (Iso14827TestSubEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int Iso14827TestSubList_count(Iso14827TestSubList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Iso14827TestSubList *Iso14827TestSubList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestSubList *ret = (Iso14827TestSubList *)Dz1Calloc(sizeof(Iso14827TestSubList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestSubList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Iso14827TestSubEntry_cmp,
				(Dz1DelFunc)Iso14827TestSubEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Iso14827TestSubList_count;
			ret->travel = Iso14827TestSubList_travelForward;
			ret->travelForward = Iso14827TestSubList_travelForward;
			ret->travelBackward = Iso14827TestSubList_travelBackward;
			ret->get_array = Iso14827TestSubList_get_array;
			ret->add = Iso14827TestSubList_add;
			ret->remove = Iso14827TestSubList_remove;
			ret->find = Iso14827TestSubList_find;
			ret->extract = Iso14827TestSubList_extract;
			ret->getHead = Iso14827TestSubList_getHead;
			ret->cmp = Iso14827TestSubEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestSubList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Iso14827TestSubList_clone(void *ptr, Iso14827TestSubEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827TestSubList *p = (Iso14827TestSubList *)ptr;
	Iso14827TestSubEntry *cloned = Iso14827TestSubEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Iso14827TestSubList *Iso14827TestSubList_clone(Iso14827TestSubList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestSubList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Iso14827TestSubList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestSubList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Iso14827TestSubList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestSubList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestSubList_purge(Iso14827TestSubList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Iso14827TestSubList_del(Iso14827TestSubList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Iso14827TestSubList_dump(void *ptr, Iso14827TestSubEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Iso14827TestSubEntry_dump(p, tab);
	return err;
}

void Iso14827TestSubList_dump(Iso14827TestSubList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Iso14827TestSubList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestSubList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperEnv
Iso14827TestHelperEnv *Iso14827TestHelperEnv_new(void *tSelf, 
												 void *t14827/*_ref*/, 
												 void *tMain, 
												 Dz1JsonSpec *spec, 
												 SubscribeSpecList *test_subs, 
												 Iso14827TestSubList *subs_reg, 
												 Iso14827TestSubList *subs_reg2, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestHelperEnv *__internal_ret = (Iso14827TestHelperEnv *)Dz1Calloc(sizeof(Iso14827TestHelperEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestHelperEnv_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->test_subs2 = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tSelf = tSelf;
			__internal_ret->t14827 = t14827;
			__internal_ret->tMain = tMain;
			__internal_ret->spec = spec;
			__internal_ret->test_subs = test_subs;
			__internal_ret->subs_reg = subs_reg;
			__internal_ret->subs_reg2 = subs_reg2;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestHelperEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Iso14827TestHelperEnv_purge(Iso14827TestHelperEnv *p)
{
	if (p == NULL) return;
	Dz1JsonSpec_del(p->spec);
	Iso14827TestScenario_del(p->scenario);
	Dz1Asn1OctetStr_del(p->user);
	Dz1SockAddr_del(p->server_addr);
	SubscribeSpecList_del(p->test_subs);
	SubscribeSpecList_del(p->test_subs2);
	Iso14827TestSubList_del(p->subs_reg);
	Iso14827TestSubList_del(p->subs_reg2);
	Iso14827TestDataCheckList_del(p->check_list);
	Dz1Str_del(p->current_test);
}

void Iso14827TestHelperEnv_del(Iso14827TestHelperEnv *p)
{
	if (p == NULL) return;
	Iso14827TestHelperEnv_purge(p);
	Dz1Free(p);
}

void Iso14827TestHelperEnv_dump(Iso14827TestHelperEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tMain = %p\n"), p->tMain);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("spec = ")); Dz1JsonSpec_dump(p->spec, tab); 
		Dz1Thread_tprintf(tab, Dz1T("scenario.")); Iso14827TestScenario_dump(p->scenario, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_run = ")); Dz1Bool_dump(&p->is_run, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = ")); Dz1s32_dump(&p->state, tab); 
		Dz1Thread_tprintf(tab, Dz1T("flags = ")); Dz1u32_dump(&p->flags, tab); 
		Dz1Thread_tprintf(tab, Dz1T("selected_codec = %s(%d)\n"), Dz1Asn1CodecStr(p->selected_codec), p->selected_codec);
		Dz1Thread_tprintf(tab, Dz1T("selected_codec_duo = %s(%d)\n"), Dz1Asn1CodecStr(p->selected_codec_duo), p->selected_codec_duo);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("server_addr = ")); Dz1SockAddr_dump(p->server_addr, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("primary_acc = ")); Iso14827TestClientAccount_dump(p->primary_acc, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("secondary_acc = ")); Iso14827TestClientAccount_dump(p->secondary_acc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_subs = ")); SubscribeSpecList_dump(p->test_subs, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_subs2 = ")); SubscribeSpecList_dump(p->test_subs2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_subs_id = ")); Dz1u32_dump(&p->test_subs_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_reg = ")); Iso14827TestSubList_dump(p->subs_reg, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_reg2 = ")); Iso14827TestSubList_dump(p->subs_reg2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("check_list.")); Iso14827TestDataCheckList_dump(p->check_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("current_test = ")); Dz1Str_dump(p->current_test, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hb_cnt = ")); Dz1u64_dump(&p->hb_cnt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestHelperEnv
////////////////////////////////////////////////////////////////////////////////

