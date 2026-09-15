#include "ItsIso14827TimerUtil.h"

Dz1Error ItsIso14827Timer_reg(void *timer, ItsIso14827Timer **tmr, u64_t duration, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1TaskTimer_reg(timer, duration, (void **)tmr, (Dz1DelFunc)ItsIso14827Timer_del, timeout, TRUE)).code) ERR_OUT(&err);
	return err;
}

Dz1Error ItsIso14827DomainTimer_reg(void *timer, ItsIso14827DomainKey *key,
									Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id,
									u64_t duration, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Timer *tmr = ItsIso14827Timer_new(ItsIso14827TimerPresent_domain, NULL, &err);
	if (tmr == NULL) ERR_OUT(&err);
	else
	{
		ItsIso14827DomainTimer *domain = NULL;
		pthread_cleanup_push(ItsIso14827Timer_delAndSetNull, (void *)&tmr);
		if ((tmr->x.domain = domain = ItsIso14827DomainTimer_new(NULL, NULL, NULL, id, &err)) == NULL) ERR_OUT(&err);
		else if ((domain->key = ItsIso14827DomainKey_clone(key, &err)) == NULL) ERR_OUT(&err);
		else if ((domain->peer = Dz1Asn1UTF8Str_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((domain->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else
		{
			//Dz1Thread_printf("@@@ Timer = "); ItsIso14827Timer_dump(tmr, 0);
			//Dz1Thread_printf("@@@ Duration = %u.%06u\n", duration / 1000000, duration % 1000000);
			if ((err = ItsIso14827Timer_reg(timer, &tmr, duration, timeout)).code) ERR_OUT(&err);
		}
		pthread_cleanup_pop(1); // (ItsIso14827Timer_delAndSetNull, (void *)&tmr);
	}
	return err;
}

Dz1Error ItsIso14827DomainTimer_reg2(void *timer,
									 ItsIso14827DomainType type, Dz1Asn1UTF8Str *domain,
									 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id,
									 u64_t duration, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { type, domain };
	if ((err = ItsIso14827DomainTimer_reg(timer, &key, peer, user, id, duration, timeout)).code) ERR_OUT(&err);
	return err;
}

Dz1Error ItsIso14827DomainTimer_reg3(void *timer, ItsIso14827Domain *domain, 
									 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id,
									 u64_t duration, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(domain->present)
	{
	case ItsIso14827DomainPresent_server:
		if ((err = ItsIso14827DomainTimer_reg2(timer, ItsIso14827DomainType_server, domain->x.server->name,
												peer, user, id, duration, timeout)).code) ERR_OUT(&err);
		break;
	case ItsIso14827DomainPresent_client:
		if ((err = ItsIso14827DomainTimer_reg2(timer, ItsIso14827DomainType_client, domain->x.client->name,
												peer, user, id, duration, timeout)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

void ItsIso14827DomainTimer_dereg(void *timer, ItsIso14827DomainType type, Dz1Asn1UTF8Str *domainName,
								  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id)
{
	ItsIso14827DomainKey dKey = { type, domainName };
	ItsIso14827DomainTimer d = { &dKey, peer, user, id };
	ItsIso14827Timer key = { ItsIso14827TimerPresent_domain, { &d } };
	Dz1TaskTimer_dereg(timer, &key);
}

Dz1Error ItsIso14827SessionTimer_reg(void *timer, ItsIso14827SessionKey *key, u32_t id,
									u64_t duration, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ItsIso14827Timer *tmr = ItsIso14827Timer_new(ItsIso14827TimerPresent_session, NULL, &err);
	if (tmr == NULL) ERR_OUT(&err);
	else
	{
		ItsIso14827SessionTimer *session;
		pthread_cleanup_push(ItsIso14827Timer_delAndSetNull, (void *)&tmr);

		if ((tmr->x.session = session = ItsIso14827SessionTimer_new(NULL, id, &err)) == NULL) ERR_OUT(&err);
		else if ((session->key = ItsIso14827SessionKey_clone(key, &err)) == NULL) ERR_OUT(&err);
		else if ((err = ItsIso14827Timer_reg(timer, &tmr, duration, timeout)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // (ItsIso14827Timer_delAndSetNull, (void *)&tmr);
	}
	return err;
}


void ItsIso14827SessionTimer_dereg(void *timer, ItsIso14827SessionKey *skey, u32_t id)
{
	ItsIso14827SessionTimer s = { skey, id };
	ItsIso14827Timer key = { ItsIso14827TimerPresent_session, { &s } };
	//Dz1Thread_printf("### Deregister Session Timer = "); ItsIso14827SessionKey_dump(skey, 0);
	Dz1TaskTimer_dereg(timer, &key);
}

