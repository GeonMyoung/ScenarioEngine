#include "ItsIso14827TimerUtil.h"
#include "ItsIso14827ServerDomainTimer.h"

Dz1Error ItsIso14827ServerDomainTimer_reg(void *timer, Dz1Asn1UTF8Str *domain,
										  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id,
										  u64_t duration, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = ItsIso14827DomainTimer_reg2(timer, ItsIso14827DomainType_server, domain, peer, user, id, duration, timeout)).code) ERR_OUT(&err);
	return err;
}

void ItsIso14827ServerDomainTimer_dereg(void *timer, Dz1Asn1UTF8Str *domain, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id)
{
	ItsIso14827DomainTimer_dereg(timer, ItsIso14827DomainType_server, domain, peer, user, id);
}

Dz1Error ItsIso14827ServerDomainSubscriptionTimer_reg(void *timer, Dz1Asn1UTF8Str *domain,
													  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
													  u32_t subID, u32_t id,
													  u64_t duration, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Timer *tmr = ItsIso14827Timer_new(ItsIso14827TimerPresent_subscription, NULL, &err);
	if (tmr == NULL) ERR_OUT(&err);
	else
	{
		ItsIso14827SubscriptionTimer *st = NULL;
		ItsIso14827DomainKey  *key = NULL;
		pthread_cleanup_push(ItsIso14827Timer_delAndSetNull, (void *)&tmr);
		if ((tmr->x.subscription = st = ItsIso14827SubscriptionTimer_new(NULL, NULL, NULL, subID, id, &err)) == NULL) ERR_OUT(&err);
		else if ((st->key = key = ItsIso14827DomainKey_new(ItsIso14827DomainType_server, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((key->name = Dz1Asn1UTF8Str_clone(domain, &err)) == NULL) ERR_OUT(&err);
		else if ((st->peer = Dz1Asn1UTF8Str_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((st->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else if ((err = ItsIso14827Timer_reg(timer, &tmr, duration, timeout)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827Timer_delAndSetNull, (void *)&tmr);
	}
	return err;
}

void ItsIso14827ServerDomainSubscriptionTimer_dereg(void *timer, Dz1Asn1UTF8Str *domain,
													Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
													u32_t subID, u32_t id)
{
	ItsIso14827DomainKey dkey = { ItsIso14827DomainType_server, domain };
	ItsIso14827SubscriptionTimer st = { &dkey, peer, user, subID, id };
	ItsIso14827Timer tmr = { ItsIso14827TimerPresent_subscription };
	tmr.x.subscription = &st;
	Dz1TaskTimer_dereg(timer, (void *)&tmr);
}
