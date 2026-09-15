#include <dz1_task_timer.h>
#include "Iso14827TestHelperTimerUtil.h"
#include "Iso14827TestHelperScenario.h"

Dz1Error Iso14827TestHelperTimer_set(void *timer, Iso14827TestHelperTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)Iso14827TestHelperTimer_del, timeout, FALSE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Iso14827TestHelperTimer_update(void *timer, Iso14827TestHelperTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)Iso14827TestHelperTimer_del, timeout, TRUE)).code) ERR_OUT(errp);
	return err;
}

void Iso14827TestHelperTimer_clr(void *timer, Iso14827TestHelperTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}



bool_t Iso14827TestHelperTimer_setGeneralTimer(void* timer, u32_t id, u64_t dur_us, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestHelperTimer* tmr = Iso14827TestHelperTimer_new(Iso14827TestHelperTimerPresent_general, NULL, errp);
	if (tmr == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestHelperTimer_delAndSetNull, (void*)&tmr);
		tmr->x.general = id;
		if ((*errp = Iso14827TestHelperTimer_update(timer, &tmr, dur_us, Iso14827TestScenario_timeout)).code) ERR_OUT(errp);
		else
		{
			tmr = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestHelperTimer_delAndSetNull, (void*)&tmr);
	}
	return ERR_IS_SUCCESS(errp);
}

void Iso14827TestHelperTimer_clrGeneralTimer(void* timer, u32_t id)
{
	Iso14827TestHelperTimer key = { Iso14827TestHelperTimerPresent_general };
	key.x.general = id;
	Iso14827TestHelperTimer_clr(timer, &key);
}

bool_t Iso14827TestHelperTimer_setClientTimer(void* timer, Dz1Asn1UTF8Str* my_domain, Dz1Asn1UTF8Str* peer_domain, Dz1Asn1OctetStr* user, u32_t id, u64_t dur_us, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestHelperTimer* tmr = Iso14827TestHelperTimer_new(Iso14827TestHelperTimerPresent_client, NULL, errp);
	if (tmr == NULL) ERR_OUT(errp);
	else
	{
		Iso14827TestHelperTimerSession* stmr = NULL;
		pthread_cleanup_push(Iso14827TestHelperTimer_delAndSetNull, (void*)&tmr);

		if ((stmr = tmr->x.client = Iso14827TestHelperTimerSession_new(NULL, NULL, NULL, id, errp)) == NULL) ERR_OUT(errp);
		else if ((stmr->my_domain = Dz1Asn1UTF8Str_clone(my_domain, errp)) == NULL) ERR_OUT(errp);
		else if ((stmr->peer_domain = Dz1Asn1UTF8Str_clone(peer_domain, errp)) == NULL) ERR_OUT(errp);
		else if ((stmr->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Iso14827TestHelperTimer_update(timer, &tmr, dur_us, Iso14827TestScenario_timeout)).code) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "!!! Iso14827TestHelperTimer_setClientTimer(): called\n");
			tmr = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); //  (Iso14827TestHelperTimer_delAndSetNull, (void*)&tmr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

void Iso14827TestHelperTimer_clrClientTimer(void* timer, Dz1Asn1UTF8Str* my_domain, Dz1Asn1UTF8Str* peer_domain, Dz1Asn1OctetStr* user, u32_t id)
{
	Iso14827TestHelperTimerSession skey = { my_domain, peer_domain, user, id };
	Iso14827TestHelperTimer key = { Iso14827TestHelperTimerPresent_client, { &skey } };
	Iso14827TestHelperTimer_clr(timer, &key);
}