#include "ItsIso14827Env.h"
#include "ItsIso14827TimerUtil.h"
#include "ItsIso14827SessionMgr_main.h"
#include "ItsIso14827DomainMgr_main.h"
#include "ItsIso14827ServerDomain_main.h"
#include "ItsIso14827ServerDomainTimer.h"
#include "ItsIso14827ServerDomain_send.h"
#include "ItsIso14827Domain_send.h"

///////////////////////////////////////////////////////////////////////////////
// send FrED
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomainClientEntry_sendFrED(ItsIso14827ServerDomainClientEntry *client,
													 Dz1Asn1UTF8Str *domainName,
													 ItsIso14827SessionEntry *session,
													 u32_t confirmPktNbr, u32_t *sentPktNbr,
													 u32_t hdr_opt_flag,
													 void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_fred, (u32_t *)&confirmPktNbr, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, client->peer, env->pktDumpFlag);
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// send Reject Login
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomainClientEntry_sendRejectLogin(ItsIso14827ServerDomainClientEntry *client,
															Dz1Asn1UTF8Str *domainName,
															ItsIso14827SessionEntry *session,
															u32_t confirmPktNbr, Iso14827RejectLogin reason,
															u32_t hdr_opt_flag,
															void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	Iso14827Reject *nak = NULL;
	Iso14827RejectType *type = NULL;

	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_nak, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.nak = nak = Iso14827Reject_new(confirmPktNbr, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((nak->type = type = Iso14827RejectType_new(Iso14827RejectTypePresent_login, (void *)&reason, &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, client->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// send Reject Subscription
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomainClientEntry_sendRejectSubscription(ItsIso14827ServerDomainClientEntry *client,
																   Dz1Asn1UTF8Str *domainName,
																   ItsIso14827SessionEntry *session,
																   u32_t confirmPktNbr, Iso14827RejectSubscription reason,
																   u32_t hdr_opt_flag,
																   void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	Iso14827Reject *nak = NULL;
	Iso14827RejectType *type = NULL;

	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_nak, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.nak = nak = Iso14827Reject_new(confirmPktNbr, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((nak->type = type = Iso14827RejectType_new(Iso14827RejectTypePresent_subscription, (void *)&reason, &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, client->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// send Reject Publication
///////////////////////////////////////////////////////////////////////////////
// Server not send reject publication

///////////////////////////////////////////////////////////////////////////////
// send Reject Publication Data
///////////////////////////////////////////////////////////////////////////////
// Server not send reject publication data

///////////////////////////////////////////////////////////////////////////////
// send Accept Login
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomainClientEntry_sendAcceptLogin(ItsIso14827ServerDomainClientEntry *client,
															Dz1Asn1UTF8Str *domainName,
															ItsIso14827SessionEntry *session,
															u32_t confirmPktNbr, Dz1Asn1Codec selected,
															u32_t hdr_opt_flag,
															void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	Iso14827Accept *ack = NULL;
	Iso14827AcceptType *type = NULL;
	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_ack, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.ack = ack = Iso14827Accept_new(confirmPktNbr, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((ack->acceptType = type = Iso14827AcceptType_new(Iso14827AcceptTypePresent_login, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((type->x.login = Dz1Asn1Codec2OID(selected, &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, client->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// send Accept Single Subscription
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomainClientEntry_sendAcceptSingleSubscription(ItsIso14827ServerDomainClientEntry *client,
																		 Dz1Asn1UTF8Str *domainName,
																		 ItsIso14827SessionEntry *session,
																		 u32_t confirmPktNbr,
																		 u32_t hdr_opt_flag,
																		 void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	Iso14827Accept *ack = NULL;
	Iso14827AcceptType *type = NULL;

	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_ack, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.ack = ack = Iso14827Accept_new(confirmPktNbr, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((ack->acceptType = type = Iso14827AcceptType_new(Iso14827AcceptTypePresent_singleSubscription, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, client->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// send Accept Registered Subscription
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomainClientEntry_sendAcceptRegisteredSubscription(ItsIso14827ServerDomainClientEntry *client,
																			 Dz1Asn1UTF8Str *domainName,
																			 ItsIso14827SessionEntry *session,
																			 u32_t confirmPktNbr,
//																			 u32_t subID,
																			 u32_t updateDelayQty,
																			 u32_t hdr_opt_flag,
																			 void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	Iso14827Accept *ack = NULL;
	Iso14827AcceptType *type = NULL;

	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_ack, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);

		if ((pdu->x.ack = ack = Iso14827Accept_new(confirmPktNbr, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((ack->acceptType = type = Iso14827AcceptType_new(Iso14827AcceptTypePresent_registeredSubscription, (void *)&updateDelayQty, &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, client->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

Dz1Error ItsIso14827ServerDomainClientEntry_sendAcceptPub(ItsIso14827ServerDomainClientEntry *client,
														  Dz1Asn1UTF8Str *domainName,
														  ItsIso14827SessionEntry *session,
														  u32_t confirmPktNbr, u32_t hdr_opt_flag,
														  void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	Iso14827Accept *ack = NULL;
	Iso14827AcceptType *type = NULL;

	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_ack, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.ack = ack = Iso14827Accept_new(confirmPktNbr, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((ack->acceptType = type = Iso14827AcceptType_new(Iso14827AcceptTypePresent_publication, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, client->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

Dz1Error ItsIso14827ServerDomainClientEntry_sendRejectPub(ItsIso14827ServerDomainClientEntry *client, Dz1Asn1UTF8Str *domainName, ItsIso14827SessionEntry *session,
														  u32_t confirmPktNbr, Iso14827RejectPublication reason, u32_t hdr_opt_flag, void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Iso14827PDUs *pdu = NULL;
	Iso14827Reject *nak = NULL;
	Iso14827RejectType *type = NULL;

	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_nak, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.nak = nak = Iso14827Reject_new(confirmPktNbr, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((nak->type = type = Iso14827RejectType_new(Iso14827RejectTypePresent_publication, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			type->x.publication = reason;
			ItsIso14827Domain_send_no_retry(session, NULL, 1, &pdu, hdr_opt_flag, domainName, client->peer, env->pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

Dz1Error ItsIso14827ServerDomainClientEntry_sendTerminate(ItsIso14827ServerDomainClientEntry *client,
														  Dz1Asn1UTF8Str *domainName,
														  ItsIso14827SessionEntry *session,
														  Iso14827Terminate reason,
														  u32_t hdr_opt_flag,
														  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827PDUs *pdu = NULL;
	//Iso14827Accept *ack = NULL;
	//Iso14827AcceptType *type = NULL;

	if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_term, &reason, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((err = ItsIso14827Domain_send(client->txFifo, session, ItsIso14827DomainType_server, hdr_opt_flag,
										  domainName, client->peer, client->user, NULL, 
										  client->responseWaitTime, client->heartBeadPeriod, 1,
										  &pdu, FALSE, NULL, uArg, uRsc, timer)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

