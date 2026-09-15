#include "ItsIso14827Domain_send.h"
#include "ItsIso14827Env.h"
#include "ItsIso14827ClientDomain_send.h"

Dz1Error ItsIso14827ClientDomainServerEntry_sendLogin(ItsIso14827ClientDomainServerEntry *server,
													  ItsIso14827SessionEntry *session,
													  Dz1Asn1UTF8Str *domainName,
													  Dz1Asn1OctetStr *authInfo,
													  Iso14827Login **login,
													  u32_t hdr_opt_flag,
													  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827PDUs *pdu = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_login, (void *)(*login), &err)) == NULL) ERR_OUT(&err);
	else
	{
		(*login) = NULL;
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((err = ItsIso14827Domain_send(server->txFifo, session,
										ItsIso14827DomainType_client,
										hdr_opt_flag,
										domainName, server->peer, server->user, NULL, 
										server->responseWaitTime, server->heartBeadPeriod,
										1, &pdu, TRUE, ItsIso14827Domain_sendFail,
										uArg, uRsc, timer)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

Dz1Error ItsIso14827ClientDomainServerEntry_sendLogout(ItsIso14827ClientDomainServerEntry *server,
													   ItsIso14827SessionEntry *session,
													   Dz1Asn1UTF8Str *domainName, Iso14827Logout reason,
													   u32_t hdr_opt_flag,
													   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827PDUs *pdu = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_logout, (void *)(&reason), &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((err = ItsIso14827Domain_send(server->txFifo, session,
										ItsIso14827DomainType_client,
										hdr_opt_flag, domainName, 
										server->peer, server->user, NULL, 
										server->responseWaitTime, server->heartBeadPeriod,
										1, &pdu, TRUE, ItsIso14827Domain_sendFail,
										uArg, uRsc, timer)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

Dz1Error ItsIso14827ClientDomainServerEntry_sendFrED(ItsIso14827ClientDomainServerEntry *server,
													 ItsIso14827SessionEntry *session,
													 Dz1Asn1UTF8Str *domainName,
													 u32_t confirmPktNbr, u32_t *sentPktNbr,
													 u32_t hdr_opt_flag,
													 void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_fred, (void *)(&confirmPktNbr), &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, server->peer,env->pktDumpFlag);
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}


Dz1Error ItsIso14827ClientDomainServerEntry_sendSubscriptionData(ItsIso14827ClientDomainServerEntry *server,
																 ItsIso14827SessionEntry *session,
																 Dz1Asn1UTF8Str *domainName,
																 u32_t serial, Iso14827SubscriptionData *data,
																 u32_t hdr_opt_flag,
																 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827PDUs *pdu = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_subscription, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827Subscription *sub = NULL;
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.subscription = sub = Iso14827Subscription_new(serial, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((sub->type = Iso14827SubscriptionType_new(Iso14827SubscriptionTypePresent_data, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((sub->type->x.data = Iso14827SubscriptionData_clone(data, &err)) == NULL) ERR_OUT(&err);
		else if ((err = ItsIso14827Domain_send(server->txFifo, session, ItsIso14827DomainType_client,
											hdr_opt_flag, domainName, 
											server->peer, server->user, NULL, 
											server->responseWaitTime, server->heartBeadPeriod,
											1, &pdu, TRUE, ItsIso14827Domain_sendFail,
											uArg, uRsc, timer)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}


Dz1Error ItsIso14827ClientDomainServerEntry_sendSubscriptionCancel(ItsIso14827ClientDomainServerEntry *server,
																   ItsIso14827SessionEntry *session,
																   Dz1Asn1UTF8Str *domainName,
																   u32_t serial, Iso14827SubscriptionCancel reason,
																   u32_t hdr_opt_flag,
																   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827PDUs *pdu = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_subscription, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827Subscription *sub = NULL;
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.subscription = sub = Iso14827Subscription_new(serial, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((sub->type = Iso14827SubscriptionType_new(Iso14827SubscriptionTypePresent_reason, (void *)(&reason), &err)) == NULL) ERR_OUT(&err);
		else if ((err = ItsIso14827Domain_send(server->txFifo, session, ItsIso14827DomainType_client,
											hdr_opt_flag, domainName, 
											server->peer, server->user, NULL, 
											server->responseWaitTime, server->heartBeadPeriod,
											1, &pdu, TRUE, ItsIso14827Domain_sendFail,
											uArg, uRsc, timer)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

Dz1Error ItsISo14827ClientDomainServerEntry_sendAcceptPub(ItsIso14827ClientDomainServerEntry *server,
														  ItsIso14827SessionEntry *session,
														  Dz1Asn1UTF8Str *domainName,
														  u32_t confirmPktNbr,
														  u32_t hdr_opt_flag,
														  void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	
	Iso14827PDUs *pdu = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_ack, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827Accept *ack = NULL;
		Iso14827AcceptType *type = NULL;
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.ack = ack = Iso14827Accept_new(confirmPktNbr, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((ack->acceptType = type = Iso14827AcceptType_new(Iso14827AcceptTypePresent_publication, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, server->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}


Dz1Error ItsIso14827ClientDomainServerEntry_sendRejectPub(ItsIso14827ClientDomainServerEntry *server,
														  ItsIso14827SessionEntry *session,
														  Dz1Asn1UTF8Str *domainName,
														  u32_t confirmPktNbr, Iso14827RejectPublication reason,
														  u32_t hdr_opt_flag,
														  void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_nak, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827Reject *nak = NULL;
		Iso14827RejectType *type = NULL;
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.nak = nak = Iso14827Reject_new(confirmPktNbr, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((nak->type = type = Iso14827RejectType_new(Iso14827RejectTypePresent_publication, (void *)&reason, &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, server->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

Dz1Error ItsIso14827ClientDomainServerEntry_sendRejectPubData(ItsIso14827ClientDomainServerEntry *server,
															  ItsIso14827SessionEntry *session,
															  Dz1Asn1UTF8Str *domainName,
															  u32_t subSerial, u32_t pubSerial,
															  Iso14827RejectPubDataReason reason,
															  u32_t hdr_opt_flag,
															  void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_nak, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827Reject *nak = NULL;
		Iso14827RejectType *type = NULL;
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.nak = nak = Iso14827Reject_new(0, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((nak->type = type = Iso14827RejectType_new(Iso14827RejectTypePresent_pubData, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((type->x.pubData = Iso14827RejectPubData_new(subSerial, pubSerial, reason, &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, server->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}
