#include <Iso14827dz1_assist.h>

#include "ItsIso14827Env.h"
#include "ItsIso14827TimerUtil.h"

#include "ItsIso14827SessionMgr_main.h"

#include "ItsIso14827ServerDomainTimer.h"
#include "ItsIso14827Domain_send.h"
#include "ItsIso14827DomainMgr_main.h"
#include "ItsIso14827ServerDomain_send.h"
#include "ItsIso14827ServerDomain_main.h"
#include "ItsIso14827ServerDomain_subscription.h"

#ifdef __BORLANDC__
#pragma warn -8006
#endif

/*
datexReject-Subscription-cd	ENUMERATED 
{
	other, 
	unknownSubscriptionNbr, 
	invalidTimes, 
	frequencyTooSmall, 
	frequencyTooLarge, 
	invalid-mode,
	publishFormatNotSupported, 
	unknowSubscriptionMsgId, 
	invalidSubscriptionMsgId, 
	invalidSubscriptionContent,
	...
},
*/
///////////////////////////////////////////////////////////////////////////////
// Send Accept(Subscription) Helper
static time_t _calcMidNight(struct tm tSrc)
{
	struct tm temp;
	temp = tSrc;
	temp.tm_hour = 0;
	temp.tm_min = 0;
	temp.tm_sec = 0;
	return mktime(&temp);
}

static time_t _calcMidNightFromTime(time_t tSrc)
{
	time_t ret = 0;
	struct tm *tm_p = localtime(&tSrc), tmSrc = *tm_p;
	ret = _calcMidNight(tmSrc);
	return ret;
}

static Dz1Error Iso14827Time2MidnightTime(time_t *dst, Iso14827Time *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (dst == NULL || src == NULL || src->year == NULL || src->month == NULL || src->day == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		struct tm temp;
		temp.tm_year = (*src->year - 1900);
		temp.tm_mon = (*src->month - 1);
		temp.tm_mday = *src->day;
		temp.tm_hour = 0;
		temp.tm_min = 0;
		temp.tm_sec = 0;

		(*dst) = mktime(&temp);
	}

	return err;
}

static u32_t Iso14827Registered_getUpdateDelay(Iso14827Registered *r)
{
	u32_t ret = 0;
	if (r != NULL)
	{
		Iso14827RegisteredDaily *d = NULL;
		Iso14827RegisteredContinuous *c = NULL;
		switch(r->present)
		{
		case Iso14827RegisteredPresent_continuous:
			if ((c = r->x.continuous) != NULL) ret = c->updateDelay;
			break;
		case Iso14827RegisteredPresent_daily:
			if ((d = r->x.daily) != NULL) ret = d->updateDelay;
			break;
		default:
			break;
		}
	}
	return ret;
}

static Dz1Error _sendAcceptSubscription(ItsIso14827ServerDomainClientEntry *client, Dz1Asn1UTF8Str *domainName,
										ItsIso14827SessionEntry *session, u32_t pktNbr,
										Iso14827SubscriptionDataMode *mode, u32_t hdr_opt_flag,
										void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (mode->present != Iso14827SubscriptionDataModePresent_single)
	{
		Iso14827Registered *r = (Iso14827Registered *)mode->x.__ptr__;
		u32_t updateDelayQty = Iso14827Registered_getUpdateDelay(r);
		ItsIso14827ServerDomainClientEntry_sendAcceptRegisteredSubscription(client, domainName, session, 
																			pktNbr, updateDelayQty,
																			hdr_opt_flag, uArg, uRsc, timer);
	}
	else ItsIso14827ServerDomainClientEntry_sendAcceptSingleSubscription(client, domainName, session, pktNbr, hdr_opt_flag, uArg, uRsc, timer);
	return err;
}
/*
static Dz1Error _sendAcceptSubscriptionRetried(ItsIso14827ServerSubscriptionFsmArg *fsmArg, ItsIso14827ServerDomainClientEntry *client,
											   Dz1Asn1UTF8Str *domainName, ItsIso14827SessionEntry *session, u32_t updateDelayQty,
											   ItsIso14827SubscriptionOperPresent check, void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (fsmArg->retried != NULL)
	{
		ItsIso14827SubscriptionOper *retried = fsmArg->retried;
		pthread_cleanup_push(ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->retried);

		if (retried->present == check)
		{
			ItsIso14827ServerDomain *server = fsmArg->server;
			ItsIso14827SubscriptionReq *req = retried->x.create;
			Iso14827SubscriptionData *data = req->data;
			if ((err = _sendAcceptSubscription(client, domainName, session,
											   req->pktNbr, updateDelayQty, data->mode, server->hdr_opt_flag,
											   uArg, uRsc, timer)).code) ERR_OUT(&err);
		}
		pthread_cleanup_pop(1); // (ItsIso14827SubscriptionOper_delAndSetNull, (void *)&node->retried);
	}
	return err;
}
*/
// Send Accept(Subscription) Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Send Reject Subscription
static Dz1Error _sendRejectSubscription(ItsIso14827ServerDomainClientEntry *client,
										Dz1Asn1UTF8Str *domainName,
										ItsIso14827SessionEntry *session,
										u32_t pktNbr, Iso14827RejectSubscription reason,
										u32_t hdr_opt_flag,
										void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = ItsIso14827ServerDomainClientEntry_sendRejectSubscription(client, domainName, session, pktNbr,
																		 reason, hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(&err);
	return err;

}

static Dz1Error _sendRejectSubscriptionRetried(ItsIso14827ServerSubscriptionFsmArg *fsmArg,
											   ItsIso14827ServerDomainClientEntry *client,
											   Dz1Asn1UTF8Str *domainName,
											   ItsIso14827SessionEntry *session,
											   ItsIso14827SubscriptionOperPresent check,
											   Iso14827RejectSubscription reason,
											   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (fsmArg->retried != NULL)
	{
		ItsIso14827SubscriptionOper *retried = fsmArg->retried;
		pthread_cleanup_push(ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->retried);

		if (retried->present == check)
		{
			ItsIso14827ServerDomain *server = fsmArg->server;
			ItsIso14827SubscriptionReq *req = retried->x.create;
			if ((err = ItsIso14827ServerDomainClientEntry_sendRejectSubscription(client, domainName, session,
																				 req->pktNbr, reason, server->hdr_opt_flag,
																				 uArg, uRsc, timer)).code) ERR_OUT(&err);
		}

		pthread_cleanup_pop(1); // (ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->retried);
	}
	return err;
}
// Send Reject Subscription
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Send Publication Control Helper
static Dz1Error _makeupPubDataControl(Iso14827PublicationDataList *dst, u32_t serial, u32_t pubSerial, Iso14827PublicationMgmt cmd)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827PublicationData *pubData = NULL;
	if ((pubData = Iso14827PublicationData_new(serial, pubSerial, FALSE, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827PublicationType *type = NULL;
		pthread_cleanup_push(Iso14827PublicationData_delAndSetNull, (void *)&pubData);

		if ((pubData->type = type = Iso14827PublicationType_new(Iso14827PublicationTypePresent_mgmt, &cmd, &err)) == NULL) ERR_OUT(&err);
		else if ((err = dst->add(dst, pubData)).code) ERR_OUT(&err);
		else pubData = NULL;

		pthread_cleanup_pop(1); // (Iso14827PublicationData_delAndSetNull, (void *)&pubData);
	}
	return err;
}

static Dz1Error _sendPubControl(ItsIso14827ServerDomainClientEntry *client,
								Dz1Asn1UTF8Str *domainName,
								ItsIso14827SessionEntry *session,
								u32_t serial, Iso14827SubscriptionData *data,
								u32_t pubSerial, Iso14827PublicationMgmt cmd,
								u32_t hdr_opt_flag,
								void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (session != NULL)
	{
		Iso14827PDUs *pdu = Iso14827PDUs_new(Iso14827PDUsPresent_publication, NULL, &err);
		if (pdu == NULL) ERR_OUT(&err);
		else
		{
			Iso14827Publication *p = NULL;
			Iso14827PublishFormat *fmt = NULL;
			Iso14827PublicationDataList *list = NULL;
			pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);

			if ((pdu->x.publication = p = Iso14827Publication_new(data->guarantee, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((p->fmt = fmt = Iso14827PublishFormat_new(Iso14827PublishFormatPresent_dataList, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((fmt->x.dataList = list = Iso14827PublicationDataList_new(&err)) == NULL) ERR_OUT(&err);
			else if ((err = _makeupPubDataControl(list, serial, pubSerial, cmd)).code) ERR_OUT(&err);
			else if ((err = ItsIso14827Domain_send(client->txFifo, session, ItsIso14827DomainType_server, hdr_opt_flag,
												   domainName, client->peer, client->user, NULL, 
												   client->responseWaitTime, client->heartBeadPeriod, 1, 
												   &pdu, data->guarantee, NULL, uArg, uRsc, timer)).code) ERR_OUT(&err);

			pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
		}
	}
	return err;
}
// Send Publication Control Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Send Publication Data Type Helper
static Dz1Error _makeupPubDataType(Iso14827PublicationDataList *dst, u32_t serial, u32_t pubSerial, Iso14827PublicationType **type)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827PublicationData *pubData = NULL;
	if ((pubData = Iso14827PublicationData_new(serial, pubSerial, FALSE, (*type), &err)) == NULL) ERR_OUT(&err);
	else
	{
		(*type) = NULL;
		pthread_cleanup_push(Iso14827PublicationData_delAndSetNull, (void *)&pubData);
		if ((err = dst->add(dst, pubData)).code) ERR_OUT(&err);
		else pubData = NULL;
		pthread_cleanup_pop(1); // (Iso14827PublicationData_delAndSetNull, (void *)&pubData);
	}
	return err;
}

static Dz1Error _sendPublicationType(ItsIso14827ServerDomainClientEntry *client,
									 Dz1Asn1UTF8Str *domainName,
									 ItsIso14827SessionEntry *session,
									 u32_t serial, Iso14827SubscriptionData *data,
									 u32_t pubSerial, Iso14827PublicationType **type,
									 u32_t hdr_opt_flag,
									 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827PDUs *pdu = Iso14827PDUs_new(Iso14827PDUsPresent_publication, NULL, &err);
	if (pdu == NULL) ERR_OUT(&err);
	else
	{
		Iso14827Publication *p = NULL;
		Iso14827PublishFormat *fmt = NULL;
		Iso14827PublicationDataList *list = NULL;
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);

		if ((pdu->x.publication = p = Iso14827Publication_new(data->guarantee, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((p->fmt = fmt = Iso14827PublishFormat_new(Iso14827PublishFormatPresent_dataList, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((fmt->x.dataList = list = Iso14827PublicationDataList_new(&err)) == NULL) ERR_OUT(&err);
		else if ((err = _makeupPubDataType(list, serial, pubSerial, type)).code) ERR_OUT(&err);
		else if ((err = ItsIso14827Domain_send(client->txFifo, session, ItsIso14827DomainType_server, hdr_opt_flag,
											   domainName, client->peer, client->user, NULL, 
											   client->responseWaitTime, client->heartBeadPeriod, 1, 
											   &pdu, data->guarantee, NULL, uArg, uRsc, timer)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}
// Send Publication Data Type Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Subscription Timer Cleanup
static void ItsIso14827SubscriptionEntry_timerCleanup(ItsIso14827ServerDomainClientEntry *client, Dz1Asn1UTF8Str *domainName, ItsIso14827SubscriptionEntry *node, void *timer)
{
	ItsIso14827ServerDomainSubscriptionTimer_dereg(timer, domainName, client->peer, client->user, node->serial, DOMAIN_SUBSCRIPTION_REGISTERED_START);
	ItsIso14827ServerDomainSubscriptionTimer_dereg(timer, domainName, client->peer, client->user, node->serial, DOMAIN_SUBSCRIPTION_REGISTERED_STOP);
	ItsIso14827ServerDomainSubscriptionTimer_dereg(timer, domainName, client->peer, client->user, node->serial, DOMAIN_SUBSCRIPTION_REGISTERED_INVOKE);
}

typedef struct SubscriptionTimerCleanupArg
{
	ItsIso14827ServerDomainClientEntry *client;
	Dz1Asn1UTF8Str *domainName;
	ItsIso14827SubscriptionEntry *node;
	void *timer;
} SubscriptionTimerCleanupArg;

static void _ItsIso14827SubscriptionEntry_timerCleanup(void *ptr)
{
	SubscriptionTimerCleanupArg *arg = (SubscriptionTimerCleanupArg *)ptr;
	ItsIso14827SubscriptionEntry_timerCleanup(arg->client, arg->domainName, arg->node, arg->timer);
}

// Subscription Timer Cleanup
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Delay Value Helper
static u32_t Iso14827Registered_getDelay(Iso14827Registered *src)
{
	switch(src->present)
	{
	default:
	case Iso14827RegisteredPresent_continuous:
		return src->x.continuous->updateDelay;
		break;
	case Iso14827RegisteredPresent_daily:
		return src->x.daily->updateDelay;
		break;
	}
}
// Delay Value Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Subscription Checker
static bool_t _isValidScheduleContinuous(Iso14827RegisteredContinuous *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	time_t end, tNow = time(NULL);
	if (p->end == NULL) return TRUE;	// 끝 없음 -> 정상
	else
	{	// 끝 있음
		if ((err = Iso14827Time2Time(&end, p->end)).code) return FALSE;
		else if (end <= tNow) return FALSE;	// 끝이 이미 과거 -> 비정상
		else if (p->start != NULL)
		{	// 시작이 있음
			time_t start;
			if ((err = Iso14827Time2Time(&start, p->start)).code) return FALSE;
			else if (end <= start) return FALSE; // 끝이 시작보다 과거 -> 비정상
		}
	}
	return TRUE;
}

static bool_t _isValidScheduleDaily(Iso14827RegisteredDaily *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	time_t tToday = _calcMidNightFromTime(time(NULL));
	if (p->endDate == NULL) return TRUE;	// 끝 없음 -> 정상
	else
	{	// 끝 있음
		time_t tEnd;
		if ((err = Iso14827Time2MidnightTime(&tEnd, p->endDate)).code) return FALSE;
		else if (tEnd < tToday) return FALSE;	// 끝날이 이미 과거 -> 비정상
		else if (p->startDate != NULL)
		{	// 시작이 있음
			time_t tStart;
			if ((err = Iso14827Time2MidnightTime(&tStart, p->startDate)).code) return FALSE;
			else if (tEnd < tStart) return FALSE; // 끝이 시작보다 과거 -> 비정상
		}
	}
	return TRUE;
}

static bool_t _isValidSchedule(Iso14827SubscriptionDataMode *mode)
{
	if (mode->present == Iso14827SubscriptionDataModePresent_single) return TRUE;
	else
	{
		Iso14827Registered *r = (Iso14827Registered  *)mode->x.__ptr__;
		switch(r->present)
		{
		case Iso14827RegisteredPresent_continuous:
			return _isValidScheduleContinuous(r->x.continuous);
		case Iso14827RegisteredPresent_daily:
			return _isValidScheduleDaily(r->x.daily);
		default:
			return FALSE;
		}
	}
}

static bool_t _isUpdatableMode(Iso14827SubscriptionDataMode *a, Iso14827SubscriptionDataMode *b)
{
	if (a->present != b->present ||
		a->present == Iso14827SubscriptionDataModePresent_single ||
		b->present == Iso14827SubscriptionDataModePresent_single) return FALSE;
	else
	{	// Check Daily/Continuous
		Iso14827Registered *ra = (Iso14827Registered  *)a->x.__ptr__;
		Iso14827Registered *rb = (Iso14827Registered  *)b->x.__ptr__;
		if (ra->present != rb->present) return FALSE;
	}
	return TRUE;
}
// Subscription Checker
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Subscription Callback
static void _subscriptionCallback(ItsIso14827ServerDomainClientEntry *client, Dz1Asn1UTF8Str *domainName,
								  u32_t serial, Iso14827SubscriptionData *data)
{
	char strOID[128] = { 0, };
	ItsIso14827ServerDomainCallback *cbs = client->cb;
	Iso14827SubscriptionDataMode *mode = data->mode;
	Iso14827EndAppMsg *msg = data->msg;
	Dz1Asn1Any *body = msg->data;
	switch(mode->present)
	{
	case Iso14827SubscriptionDataModePresent_single:
		Dz1Asn1OID_printable(msg->oid, strOID, 128, NULL); strOID[127] = '\0';
		cbs->singleRequest(cbs->param, domainName, client->peer, client->user, serial, strOID, body->data, body->size);
		break;
	case Iso14827SubscriptionDataModePresent_eventDriven:
		{
			Iso14827Registered *schedule = mode->x.eventDriven;
			u32_t delayValue = Iso14827Registered_getDelay(schedule);
			Dz1Asn1OID_printable(msg->oid, strOID, 128, NULL); strOID[127] = '\0';
			cbs->eventPrepare(cbs->param, domainName, client->peer, client->user, serial, delayValue,
								strOID, body->data, body->size);
		}
		break;
	case Iso14827SubscriptionDataModePresent_periodic:
		{
			Iso14827Registered *schedule = mode->x.periodic;
			u32_t delayValue = Iso14827Registered_getDelay(schedule);
			Dz1Asn1OID_printable(msg->oid, strOID, 128, NULL); strOID[127] = '\0';
			cbs->periodicPreapre(cbs->param, domainName, client->peer, client->user, serial, delayValue,
								strOID, body->data, body->size);
		}
		break;
	default:
		break;
	}
}

static void _subscriptionCallbackUpdate(ItsIso14827ServerDomainClientEntry *client, Dz1Asn1UTF8Str *domainName,
										u32_t serial, Iso14827SubscriptionData *data, Iso14827EndAppMsg *msg)
{
	ItsIso14827ServerDomainCallback *cbs = client->cb;
	Iso14827SubscriptionDataMode *mode = data->mode;
	switch(mode->present)
	{
	case Iso14827SubscriptionDataModePresent_eventDriven:
		{
			char strOID[128];
			Dz1Asn1Any *body = msg->data;
			Iso14827Registered *schedule = mode->x.eventDriven;
			u32_t delayValue = Iso14827Registered_getDelay(schedule);
			Dz1Asn1OID_printable(msg->oid, strOID, 128, NULL); strOID[127] = '\0';
			cbs->eventPrepare(cbs->param, domainName, client->peer, client->user, serial, delayValue,
								strOID, body->data, body->size);
		}
		break;
	case Iso14827SubscriptionDataModePresent_periodic:
		{
			char strOID[128];
			Dz1Asn1Any *body = msg->data;
			Iso14827Registered *schedule = mode->x.periodic;
			u32_t delayValue = Iso14827Registered_getDelay(schedule);
			Dz1Asn1OID_printable(msg->oid, strOID, 128, NULL); strOID[127] = '\0';
			cbs->periodicPreapre(cbs->param, domainName, client->peer, client->user, serial, delayValue,
								strOID, body->data, body->size);
		}
		break;
	default:
		break;
	}
}
// Subscription Callback
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * Periodic Subscription Invoke
 *****************************************************************************/
/*
the initial publication will be at a random point in the cycle, and the second publication may follow
at any fraction of the cycle later, but will occur on a cycle point as measured from the datexRegistered-StartTime.

00------05--07----10--------15--------20--------25
^- Start    |               |
            +- Activate     |
                            +- Period
7 % 15 = 7
15 - 7 = 8
*/
///////////////////////////////////////////////////////////////////////////////
// Periodic Cycle Synchronizer
static time_t _getDailyStartTime(time_t todayMidnight, Iso14827Time *t)
{
	time_t mod = t->h * 3600 + t->m * 60 + t->s;
	return todayMidnight + mod;
}

static u32_t _getRemainder(time_t tNow, time_t start, Iso14827Registered *r)
{
	// start 값은 Continuous인 경우 시작시간
	// Daily인 경우 활성일 00:00:00 이다
	u32_t remainder = 0;
	if (r->present == Iso14827RegisteredPresent_daily)
	{
		Iso14827RegisteredDaily *sch = r->x.daily;
		time_t todayMidnight = _calcMidNightFromTime(tNow);
		remainder = (tNow - _getDailyStartTime(todayMidnight, sch->startTime)) % sch->updateDelay;
	}
	else if (r->present == Iso14827RegisteredPresent_continuous)
	{
		Iso14827RegisteredContinuous *sch = r->x.continuous;
		remainder = (tNow - start) % sch->updateDelay;
	}
	return remainder;
}
// Periodic Cycle Synchronizer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Periodic Invoke Timer
static Dz1TaskProcStatus _subscriptionPeriodicInvoke(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp);
static Dz1Error _registerPeriodicInvokeTimer(ItsIso14827ServerDomainClientEntry *client,
											 Dz1Asn1UTF8Str *domainName,
											 ItsIso14827SubscriptionEntry *node,
											 Iso14827Registered *r,
											 void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	time_t tNow = time(NULL);
	u32_t remainder = _getRemainder(tNow, node->start, r);
	u64_t duration = (u64_t)(Iso14827Registered_getDelay(r) - remainder) * 1000000;

	if ((err = ItsIso14827ServerDomainSubscriptionTimer_reg(timer, domainName, client->peer, client->user, node->serial,
															DOMAIN_SUBSCRIPTION_REGISTERED_INVOKE, duration,
															_subscriptionPeriodicInvoke)).code) ERR_OUT(&err);

	return err;
}

static Dz1TaskProcStatus _subscriptionPeriodicInvoke(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827Timer *tmr = (ItsIso14827Timer *)(*tData);
	ItsIso14827SubscriptionTimer *sTmr = tmr->x.subscription;

	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, sTmr->key);
	if (domain)
	{
		ItsIso14827ServerDomain *server = domain->x.server;
		ItsIso14827ServerDomainClientEntry *client = ItsIso14827ServerDomain_findClientByPeerUser(server, sTmr->peer, sTmr->user);
		if (client)
		{
			ItsIso14827SubscriptionEntry key = { sTmr->subID }, *node = client->subscriptions->find(client->subscriptions, &key);
			if (node)
			{
				Iso14827SubscriptionData *data = node->data;
				Iso14827SubscriptionDataMode *mode = data->mode;
				Iso14827Registered *periodic = mode->x.periodic;
				Iso14827EndAppMsg *msg = data->msg;
				ItsIso14827ServerDomainCallback *cbs = client->cb;
				// Application에게 전송 주기가 되었음을 알림
				if (node->isPaused == FALSE)
				{
					char strOID[128];
					Dz1Asn1Any *body = msg->data;
					Dz1Asn1OID_printable(msg->oid, strOID, 128, NULL); strOID[127] = '\0';
					cbs->periodicInvoke(cbs->param, server->name, client->peer, client->user, node->serial,
										strOID, body->data, body->size);
				}
				// 다음 주기 타이머 등록
				if ((*errp = _registerPeriodicInvokeTimer(client, server->name, node, periodic, timer)).code) ERR_OUT(errp);
			}
		}
	}
	return ret;
}
// Periodic Invoke Timer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Subscription Cleanup
typedef struct ItsIso14827SubscriptionEntryCleanupArg
{
	void *timer;
	ItsIso14827ServerDomainClientEntry *client;
	Dz1Asn1UTF8Str *domainName;
	ItsIso14827SubscriptionEntry *node;

	ItsIso14827SessionEntry *session;
	void *uArg;
	void *uRsc;

	u32_t hdr_opt_flag;
} ItsIso14827SubscriptionEntryCleanupArg;

// --------------------
// Subscription 만료 시
static void ItsIso14827SubscriptionEntry_expire(void *ptr)
{
	ItsIso14827SubscriptionEntryCleanupArg *arg = (ItsIso14827SubscriptionEntryCleanupArg *)ptr;
	ItsIso14827ServerDomainClientEntry *client = arg->client;
	ItsIso14827SubscriptionEntry *node = arg->node;

	ItsIso14827ServerDomainCallback *cbs = client->cb; 

	ItsIso14827SubscriptionEntry_timerCleanup(client, arg->domainName, node, arg->timer);

	_sendPubControl(arg->client, arg->domainName, arg->session,
					node->serial, node->data,
					node->pubSerial++, Iso14827PublicationMgmt_terminateDataNoLongerAvailable,
					arg->hdr_opt_flag,
					arg->uArg, arg->uRsc, arg->timer);

	/////////////////////////////////////////////
	// 2025-11-17 : fixed
	if (node->pubSerial == 0) node->pubSerial = 1;
	// 2025-11-17 : fixed
	/////////////////////////////////////////////

	if (node->isActive)
	{
		if (cbs->stopped) cbs->stopped(cbs->param, arg->domainName, client->peer, client->user, node->serial);
		node->isActive = FALSE;
	}

	if (cbs->expired)
	{
		ItsIso14827SubscriptionExpireReason reason = { ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired, { NULL } };
		cbs->expired(cbs->param, arg->domainName, client->peer, client->user, node->serial, &reason);
	}
}

// Subscription Cleanup
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * Subscription Deactivate BEGIN
 *****************************************************************************/
//static int _getMaxWeekDay(u8_t daysOfWeek)
static __inline__ int _getMaxWeekDay(u8_t daysOfWeek)
{
	if		(daysOfWeek & ISO14827DAILY_SAT) return 6;
	else if (daysOfWeek & ISO14827DAILY_FRI) return 5;
	else if (daysOfWeek & ISO14827DAILY_THU) return 4;
	else if (daysOfWeek & ISO14827DAILY_WED) return 3;
	else if (daysOfWeek & ISO14827DAILY_TUE) return 2;
	else if (daysOfWeek & ISO14827DAILY_MON) return 1;
	else if (daysOfWeek & ISO14827DAILY_SUN) return 0;
	else return 6;	// other ?
}

static u8_t _tmWDAY2WEEKBIT(int tm_wday)
{
	u8_t mask = 0;
	switch(tm_wday)
	{
	case 0: // Sun
		mask = ISO14827DAILY_SUN;
		break;
	case 1:	// Mon
		mask = ISO14827DAILY_MON;
		break;
	case 2: // Tue
		mask = ISO14827DAILY_TUE;
		break;
	case 3: // Wed
		mask = ISO14827DAILY_WED;
		break;
	case 4: // Thu
		mask = ISO14827DAILY_THU;
		break;
	case 5: // Fri
		mask = ISO14827DAILY_FRI;
		break;
	case 6: // Sat
		mask = ISO14827DAILY_SAT;
		break;
	default:
		mask = ISO14827DAILY_OTHER;
		break;
	}
	return mask;
}

static bool_t _isItWorkingDay(u8_t dayOfWeek, int tm_wday /* days since Sunday - [0,6] */)
{
	bool_t ret = FALSE;
	u8_t mask = _tmWDAY2WEEKBIT(tm_wday);
	ret = (dayOfWeek & mask) ? TRUE : FALSE;
	return ret;
}

// Daily스케줄에서 Application에게 Stop을 알려줘야 하는 상황인가?
static bool_t _dailyStopCondition(Iso14827RegisteredDaily *sch, ItsIso14827SubscriptionEntry *node)
{
	bool_t ret = FALSE;

	if (sch->duration != NULL && *sch->duration < 1440)
	{	// duration이 NULL이 아니고 1440 미만의 값을 가지는 경우
		ret = TRUE;
	}
	else
	{	// duration이 NULL 이거나, 1440 이상의 값을 가지는 경우 
		time_t t;
		struct tm temp, *tm_p = NULL, tmNext;
		ItsIso14827SubscriptionDate *startDate = node->daily;
		temp.tm_year = startDate->year - 1900;
		temp.tm_mon = startDate->mon - 1;
		temp.tm_mday = startDate->day;
		temp.tm_hour = 0;
		temp.tm_min = 0;
		temp.tm_sec = 0;

		t = mktime(&temp) + (3600 * 24);		// 시작일 다음날 자정 시각 계산
		tm_p = localtime(&t), tmNext = *tm_p;	// 시각을 tm으로 변환

		if (_isItWorkingDay(sch->daysOfWeek, tmNext.tm_wday) == FALSE) ret = TRUE; // 요일 확인
	}

	return ret;
}

// Subscription Stop
static Dz1Error _subscriptionDeactivate(ItsIso14827ServerDomainClientEntry *client,
										Dz1Asn1UTF8Str *domainName,
										ItsIso14827SubscriptionEntry *node,
										Iso14827Registered *sch, bool_t force, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ItsIso14827ServerDomainCallback *cbs = client->cb;

	// Callback을 호출하여 Application에게 Stop을 알림
	// Contunuous	- 항상
	// Daily		- 조건부
	//	- duration이 1440분 보다 작은 경우,
	//	- 1440보다 같거나 크면서 시작시점 다음날이 활성 요일에 해당되지 않는 경우
	if (force == TRUE || sch->present == Iso14827RegisteredPresent_continuous || _dailyStopCondition(sch->x.daily, node) == TRUE)
	{
		if (node->isActive)
		{
			// XXX : 이 부분은 그냥 중지로 알려줘야 할듯?
			if (cbs->stopped) cbs->stopped(cbs->param, domainName, client->peer, client->user, node->serial);
			node->isActive = FALSE;

			// Periodic이면 Invoke Timer가 돌고 있으니 이를 삭제
			ItsIso14827ServerDomainSubscriptionTimer_dereg(timer, domainName,
														client->peer, client->user,
														node->serial, DOMAIN_SUBSCRIPTION_REGISTERED_INVOKE);
			Dz1Thread_printf("@@@ Deactivation : Success\n");
		}
		else
		{
			Dz1Thread_printf("@@@ Deactivation : Already deactivated\n");
		}
	}
	else //if (force == FALSE && sch->present == Iso14827RegisteredPresent_daily && _dailyStopCondition(sch->x.daily, node) == FALSE)
	{
		Dz1Thread_printf("@@@ Deactivation : Omitted bcuz (_dailyStopCondition(sch->x.daily, node) == FALSE)\n");
	}

	if (sch->present == Iso14827RegisteredPresent_continuous)
	{	// Continuous모드이면 ETIMEDOUT을 return하여 Subscription 종료
		Dz1Error_set(&err, ETIMEDOUT);
	}

	return err;
}

// static function Prototype
static Dz1Error _subscriptionDeactivateTimerProc(ItsIso14827ServerDomainClientEntry *client,
												 Dz1Asn1UTF8Str *domainName,
												 ItsIso14827SubscriptionEntry *node,
												 Iso14827Registered *r,
												 void *timer);

// DOMAIN_SUBSCRIPTION_REGISTERED_STOP Timer에 의해 호출 됨
static Dz1TaskProcStatus _subscriptionDeactivateTimeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827Timer *tmr = (ItsIso14827Timer *)(*tData);
	ItsIso14827SubscriptionTimer *sTmr = tmr->x.subscription;

	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, sTmr->key);
	if (domain)
	{	// 타이머가 지정하는 내 도메인 있음
		ItsIso14827ServerDomain *server = domain->x.server;
		ItsIso14827ServerDomainClientEntry *client = ItsIso14827ServerDomain_findClientByPeerUser(server, sTmr->peer, sTmr->user);
		if (client)
		{	// 타이머가 지정하는 클라이언트 있음
			ItsIso14827SubscriptionEntry key = { sTmr->subID }, *node = client->subscriptions->extract(client->subscriptions, &key);
			if (node)
			{	// 타이머가 지정하는 Subscription있음
				Iso14827SubscriptionData *data = node->data;
				Iso14827SubscriptionDataMode *mode = data->mode;
				ItsIso14827SessionEntry *session = NULL;

				ItsIso14827SubscriptionEntryCleanupArg _arg = { timer, client, server->name, node, NULL, uArg, uRsc, server->hdr_opt_flag };

				pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
				pthread_cleanup_push(ItsIso14827SubscriptionEntry_expire, (void *)&_arg);

				if ((session = _arg.session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key)) == NULL)
				{	// 클라이언트에 해당하는 세션이 없음
					switch(mode->present)
					{
					case Iso14827SubscriptionDataModePresent_periodic:
						_subscriptionDeactivate(client, server->name, node, mode->x.periodic, TRUE, timer);
						break;
					case Iso14827SubscriptionDataModePresent_eventDriven:
						_subscriptionDeactivate(client, server->name, node, mode->x.eventDriven, TRUE, timer);
						break;
					default:
						break;
					}
					ERR_SET_OUT(errp, EPIPE);
				}
				else
				{	// 클라이언트에 해당하는 세션이 있음
					// 여기서 Error 나는건 무조건 ETIMEDOUT이다.
					switch(mode->present)
					{
					case Iso14827SubscriptionDataModePresent_periodic:
						if ((*errp = _subscriptionDeactivate(client, server->name, node, mode->x.periodic, FALSE, timer)).code) ERR_OUT(errp);
						else if ((*errp = _subscriptionDeactivateTimerProc(client, server->name, node, mode->x.periodic, timer)).code) ERR_OUT(errp);
						else if ((*errp = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(errp);
						else node = NULL;
						break;
					case Iso14827SubscriptionDataModePresent_eventDriven:
						if ((*errp = _subscriptionDeactivate(client, server->name, node, mode->x.eventDriven, FALSE, timer)).code) ERR_OUT(errp);
						else if ((*errp = _subscriptionDeactivateTimerProc(client, server->name, node, mode->x.periodic, timer)).code) ERR_OUT(errp);
						else if ((*errp = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(errp);
						else node = NULL;
						break;
					default:
						break;
					}
				}
				pthread_cleanup_pop(errp->code); // (ItsIso14827SubscriptionEntry_expire, (void *)&_arg);
				pthread_cleanup_pop(1); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

// tmNow의 YMD에다가 sch->startTime을 합쳐서 계산
static time_t _calcStartTime(Iso14827RegisteredDaily *sch, struct tm tmNow)
{
	time_t ret = 0;	
	struct tm temp;
	temp.tm_year = tmNow.tm_year;
	temp.tm_mon	= tmNow.tm_mon;
	temp.tm_mday = tmNow.tm_mday;
	temp.tm_hour = 0;
	temp.tm_min = 0;
	temp.tm_sec = 0;
	if (sch->startTime != NULL)
	{
		Iso14827Time *tStart = sch->startTime;
		temp.tm_hour = tStart->h;
		temp.tm_min = tStart->m;
		temp.tm_sec = tStart->s;
	}
	ret = mktime(&temp);
	return ret;
}

static time_t _calcEndTime(Iso14827RegisteredDaily *sch, time_t tStart)
{
	time_t ret = tStart;
	time_t duration = 1440;
	if (sch->duration != NULL)
		duration = *sch->duration;
	duration *= 60;
	ret += duration;
	return ret;
}

static time_t _calcMidnightFromStartDate(ItsIso14827SubscriptionDate *src)
{
	struct tm temp;
	temp.tm_year = (src->year - 1900);
	temp.tm_mon = (src->mon - 1);
	temp.tm_mday = src->day;
	temp.tm_hour = 0;
	temp.tm_min = 0;
	temp.tm_sec = 0;
	return mktime(&temp);
}

// 중지를 알리고 난 뒤 다음 Daily Stop Timer등록 처리
// 요일 여부에 관계 없이 활성 기간이면 무조건 등록
static Dz1Error _subscriptionDeactivateTimerProc(ItsIso14827ServerDomainClientEntry *client,
												 Dz1Asn1UTF8Str *domainName,
												 ItsIso14827SubscriptionEntry *node,
												 Iso14827Registered *r,
												 void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (r->present == Iso14827RegisteredPresent_daily)
	{	// Daily Schedule
		Iso14827RegisteredDaily *sch = r->x.daily;
		// node->daily는 Activation시의 Date값이 저장
		time_t tTomorrow = _calcMidnightFromStartDate(node->daily) + (24 * 3600);	// 시작시간에다 하루를 더한다.
		// node->end는 0 이거나, 종료일 23:59:59초를 지징한다.
		if (node->end == 0 || tTomorrow <= node->end)								// 내일이 종료일보다 작으면
		{
			struct tm *tm_p = localtime(&tTomorrow), tmTomorrow = *tm_p;			// 내일 자정 시각을 struct tm으로 변환
			time_t tStart = _calcStartTime(sch, tmTomorrow);						// 내일 자정에 Start Time값을 더함
			time_t tEnd = _calcEndTime(sch, tStart);								// 유지시간 추가

			time_t tNow = time(NULL);												// 지금 시간
			u64_t toEnd = tEnd > tNow ? (u64_t)1000000 * (tEnd - tNow) : 0;			// 종료 시간 까지의 시간차

			struct tm *_tmEnd = localtime(&tEnd), tmEnd = *_tmEnd;
			Dz1Thread_printf("@@@ Next Daily Subscription End = " DZ1_TIME_TM_FMT_FULL "\n", DZ1_TIME_TM_ARG_FULL(&tmEnd));

			if ((err = ItsIso14827ServerDomainSubscriptionTimer_reg(timer, domainName, client->peer, client->user, node->serial,
																	DOMAIN_SUBSCRIPTION_REGISTERED_STOP, toEnd,
																	_subscriptionDeactivateTimeout)).code) ERR_OUT(&err);
		}
		else
		{
			Dz1Thread_printf("@@@ It's final deactivation -> terminate\n");
			Dz1Error_set(&err, ETIMEDOUT);
		}
	}
	return err;
}

/******************************************************************************
 * Subscription Deactivate End
 *****************************************************************************/

/******************************************************************************
 * Subscription Activate - BEGIN
 *****************************************************************************/
// Continuous/Daily 공통
// Daily의 경우 해당 기간, 해당 요일 시작시간에 호출됨
static Dz1Error _subscriptionActivate(ItsIso14827ServerDomainClientEntry *client,
									  Dz1Asn1UTF8Str *domainName,
									  ItsIso14827SubscriptionEntry *node,
									  Iso14827Registered *r, bool_t isPeriodic,
									  void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	time_t tNow = time(NULL);
	struct tm *tm_p = localtime(&tNow), tmNow = *tm_p;

	// 활성 일자 갱신
	ItsIso14827SubscriptionDate_delAndSetNull(&node->daily);
	if ((node->daily = ItsIso14827SubscriptionDate_new(tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday, NULL)) != NULL)
	{
		Dz1Thread_printf("@@@ Start = ");
		ItsIso14827SubscriptionDate_dump(node->daily, 0);
	}
	
	// Continuous - 항상
	// Daily - 당 일자에 해당하는 요일이 활성 요일인 경우
	if (r->present == Iso14827RegisteredPresent_continuous || _isItWorkingDay(r->x.daily->daysOfWeek, tmNow.tm_wday) == TRUE)
	{
		if (node->isActive == FALSE)
		{
			ItsIso14827ServerDomainCallback *cbs = client->cb;
			Iso14827SubscriptionData *data = node->data;
			Iso14827EndAppMsg *msg = data->msg;

			char strOID[128];
			Dz1Asn1Any *body = msg->data;
			Dz1Asn1OID_printable(msg->oid, strOID, 128, NULL); strOID[127] = '\0';

			// Callback을 호출하여 Application에게 Start를 알림
			if (isPeriodic)
			{	// Periodic
				if (cbs->periodicStart)
					cbs->periodicStart(cbs->param, domainName,
									client->peer, client->user, node->serial,
									strOID, body->data, body->size);

				// Periodic은 Start시 주기를 계산하여 따로 Timer등록.
				// node->start로부터 sch->updateDelay 주기 시간에 맞춰 Timer설정
				if ((err = _registerPeriodicInvokeTimer(client, domainName, node, r, timer)).code) ERR_OUT(&err);
			}
			else
			{	// Event-Driven
				Dz1Thread_printf("!@# : eventStart = %p\n", cbs->eventStart);
				if (cbs->eventStart)
					cbs->eventStart(cbs->param, domainName,
									client->peer, client->user, node->serial,
									strOID, body->data, body->size);
			}
			node->isActive = TRUE;
			Dz1Thread_printf("@@@ Activation : Success\n");
		}
		else
		{
			Dz1Thread_printf("@@@ Activation : Already Activated\n");
		}
	}
	else // (r->present == Iso14827RegisteredPresent_daily && _isItWorkingDay(r->x.daily->daysOfWeek, tmNow.tm_wday) == FALSE)
	{
		Dz1Thread_printf("@@@ Activation : Does not match today with daily bit\n");
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Periodic Continuous/Daily Activate
///////////////////////////////////////////////////////////////////////////////
static Dz1Error _subscriptionPeriodicActivate(ItsIso14827ServerDomainClientEntry *client,
											  Dz1Asn1UTF8Str *domainName,
											  ItsIso14827SubscriptionEntry *node,
											  Iso14827Registered *r,
											  void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = _subscriptionActivate(client, domainName, node, r, TRUE, timer)).code) ERR_OUT(&err);
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Event-Driven Continuous/Daily Activate
///////////////////////////////////////////////////////////////////////////////
// Event-Driven은 Continuous나 Daily나 Start/Stop밖에 없다.
static Dz1Error _subscriptionEventDrivenActivate(ItsIso14827ServerDomainClientEntry *client,
												 Dz1Asn1UTF8Str *domainName,
												 ItsIso14827SubscriptionEntry *node,
												 Iso14827Registered *r)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = _subscriptionActivate(client, domainName, node, r, FALSE, NULL)).code) ERR_OUT(&err);
	return err;
}

static Dz1Error _subscriptionActivateDailyTimerProc(ItsIso14827ServerDomainClientEntry *client,
													  Dz1Asn1UTF8Str *domainName,
													  ItsIso14827SubscriptionEntry *node,
													  Iso14827Registered *r,
													  void *timer);
// DOMAIN_SUBSCRIPTION_REGISTERED_START 타이머에 의해 호출 됨
static Dz1TaskProcStatus _subscriptionActivateTimeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827Timer *tmr = (ItsIso14827Timer *)(*tData);
	ItsIso14827SubscriptionTimer *sTmr = tmr->x.subscription;

	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, sTmr->key);
	if (domain)
	{	// 타이머가 지정하는 내 도메인 있음
		ItsIso14827ServerDomain *server = domain->x.server;
		ItsIso14827ServerDomainClientEntry *client = ItsIso14827ServerDomain_findClientByPeerUser(server, sTmr->peer, sTmr->user);
		if (client)
		{	// 타이머가 지정하는 클라이언트 있음
			ItsIso14827SubscriptionEntry key = { sTmr->subID }, *node = client->subscriptions->extract(client->subscriptions, &key);
			if (node)
			{	// 타이머가 지정하는 Subscription 잇음
				Iso14827SubscriptionData *data = node->data;
				Iso14827SubscriptionDataMode *mode = data->mode;
				ItsIso14827SessionEntry *session = NULL;
				ItsIso14827SubscriptionEntryCleanupArg _arg = { timer, client, server->name, node, NULL, uArg, uRsc, server->hdr_opt_flag };
				pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
				pthread_cleanup_push(ItsIso14827SubscriptionEntry_expire, (void *)&_arg);
				if ((session = _arg.session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key)) == NULL)
				{	// 클라이언트에 대한 세션이 없음
					switch(mode->present)
					{
					case Iso14827SubscriptionDataModePresent_periodic:
						_subscriptionDeactivate(client, server->name, node, mode->x.periodic, TRUE, timer);
						break;
					case Iso14827SubscriptionDataModePresent_eventDriven:
						_subscriptionDeactivate(client, server->name, node, mode->x.eventDriven, TRUE, timer);
						break;
					default:
						break;
					}
					ERR_SET_OUT(errp, EPIPE);
				}
				else
				{	// 클라이언트에 대한 세션이 있음
					switch(mode->present)
					{
					case Iso14827SubscriptionDataModePresent_periodic:
						if ((*errp = _subscriptionPeriodicActivate(client, server->name, node, mode->x.periodic, timer)).code) ERR_OUT(errp);
						else if ((*errp = _subscriptionActivateDailyTimerProc(client, server->name, node, mode->x.periodic, timer)).code) ERR_OUT(errp);
						else if ((*errp = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(errp);
						else node = NULL;
						break;
					case Iso14827SubscriptionDataModePresent_eventDriven:
						if ((*errp = _subscriptionEventDrivenActivate(client, server->name, node, mode->x.eventDriven)).code) ERR_OUT(errp);
						else if ((*errp = _subscriptionActivateDailyTimerProc(client, server->name, node, mode->x.periodic, timer)).code) ERR_OUT(errp);
						else if ((*errp = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(errp);
						else node = NULL;
						break;
					default:
						break;
					}
				}
				pthread_cleanup_pop(errp->code); // (ItsIso14827SubscriptionEntry_expire, (void *)&_arg);
				pthread_cleanup_pop(1); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

// Daily Subscription의 활성화 타이머 등록
// 요일 여부와 상관없이 활성 기간에는 무조건 등록
static Dz1Error _subscriptionActivateDailyTimerProc(ItsIso14827ServerDomainClientEntry *client,
													  Dz1Asn1UTF8Str *domainName,
													  ItsIso14827SubscriptionEntry *node,
													  Iso14827Registered *r,
													  void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (r->present == Iso14827RegisteredPresent_daily)
	{
		Iso14827RegisteredDaily *sch = r->x.daily;
		time_t tTomorrow = _calcMidnightFromStartDate(node->daily) + (3600 * 24);	// 다음날 자정시간값 계산
		// node->end는 0이거나 종료일 23:59:59를 지정
		if (node->end == 0 || tTomorrow <= node->end)								// 내일이 종료일보다 작으면
		{
			struct tm *tm_p = localtime(&tTomorrow), tmTomorrow = *tm_p;			// 내일 자정 시각을 struct tm으로 변환
			time_t tStart = _calcStartTime(sch, tmTomorrow);						// 내일 자정에 시작시간 추가
			time_t tNow = time(NULL);												// 지금 시각
			u64_t toStart = tStart > tNow ? (u64_t)1000000 * (tStart - tNow) : 0;	// 지금부터 시작시간까지 시간차

			struct tm *_tmStart = localtime(&tStart), tmStart = *_tmStart;
			Dz1Thread_printf("@@@ Next Daily Subscription Start = " DZ1_TIME_TM_FMT_FULL "\n", DZ1_TIME_TM_ARG_FULL(&tmStart));

			if ((err = ItsIso14827ServerDomainSubscriptionTimer_reg(timer, domainName, client->peer, client->user, node->serial,
														DOMAIN_SUBSCRIPTION_REGISTERED_START, toStart,
														_subscriptionActivateTimeout)).code) ERR_OUT(&err);
		}
		else
		{
			Dz1Thread_printf("@@@ It's final Activation -> no more activation\n");
		}
	}
	return err;
}

/******************************************************************************
 * Subscription Activate END
 *****************************************************************************/

/******************************************************************************
 * Periodic/Event-Driven Daily Schedule Tracking Timers
 *****************************************************************************/
//static time_t ItsIso14827SubscriptionDate2Time(ItsIso14827SubscriptionDate *src)
static __inline__ time_t ItsIso14827SubscriptionDate2Time(ItsIso14827SubscriptionDate *src)
{
	struct tm temp;
	temp.tm_year = src->year - 1900;
	temp.tm_mon = src->mon - 1;
	temp.tm_mday = src->day;
	temp.tm_hour = 0;
	temp.tm_min = 0;
	temp.tm_sec = 0;
	return mktime(&temp);
}

//static time_t _mkTodayDst(struct tm date, Iso14827Time *t)
static __inline__ time_t _mkTodayDst(struct tm date, Iso14827Time *t)
{
	time_t ret = 0;
	struct tm tmp;
	tmp.tm_year = date.tm_year;
	tmp.tm_mon = date.tm_mon;
	tmp.tm_year = date.tm_mday;
	tmp.tm_hour = t->h;
	tmp.tm_min = t->m;
	tmp.tm_sec = t->s;
	ret = mktime(&tmp);
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// set Periodic/Event-Driven Daily Tracking Timer
///////////////////////////////////////////////////////////////////////////////
static Dz1TaskProcStatus _subscriptionDailyActivateTimeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = _subscriptionActivateTimeout(uArg, uRsc, timer, tData, errp);
	return ret;
}

static Dz1TaskProcStatus _subscriptionDailyDeactivateTimeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = _subscriptionDeactivateTimeout(uArg, uRsc, timer, tData, errp);
	return ret;
}


static Dz1Error _startDailySchedule(ItsIso14827ServerDomainClientEntry *client, Dz1Asn1UTF8Str *domainName,
									ItsIso14827SubscriptionEntry *node, Iso14827RegisteredDaily *sch, void *timer)
{	// Daily Subscription최초 시작될 때 한번 호출 된다.
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	time_t tNow = time(NULL);
	struct tm *_tmNow = localtime(&tNow), tmNow = *_tmNow;

	// 오늘과 관계 없이 등록
	time_t tStart = _calcStartTime(sch, tmNow), tEnd = _calcEndTime(sch, tStart);	// 시작시간 종료시간 계산

	struct tm *_tmStart = localtime(&tStart), tmStart = *_tmStart;
	struct tm *_tmEnd = localtime(&tEnd), tmEnd = *_tmEnd;

	u64_t toStart = tStart > tNow ? (u64_t)1000000 * (tStart - tNow) : 0;			// 시작 타이머 시간
	u64_t toEnd = tEnd > tNow ? (u64_t)1000000 * (tEnd - tNow) : 0;					// 종료 타이머 시간
	if (toStart == toEnd) toEnd++;													// Timeout 호출 순서를 맞추기 위해

	Dz1Thread_printf("@@@ Daily Subscription Start = " DZ1_TIME_TM_FMT_FULL "\n", DZ1_TIME_TM_ARG_FULL(&tmStart));
	Dz1Thread_printf("@@@ Daily Subscription End = " DZ1_TIME_TM_FMT_FULL "\n", DZ1_TIME_TM_ARG_FULL(&tmEnd));

	if ((err = ItsIso14827ServerDomainSubscriptionTimer_reg(timer, domainName, client->peer, client->user, node->serial,
															DOMAIN_SUBSCRIPTION_REGISTERED_START, toStart,
															_subscriptionDailyActivateTimeout)).code) ERR_OUT(&err);
	else if ((err = ItsIso14827ServerDomainSubscriptionTimer_reg(timer, domainName, client->peer, client->user, node->serial,
																 DOMAIN_SUBSCRIPTION_REGISTERED_STOP, toEnd,
																 _subscriptionDailyDeactivateTimeout)).code) ERR_OUT(&err);
	return err;
}

static Dz1TaskProcStatus _startDailyScheduleTimeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827Timer *tmr = (ItsIso14827Timer *)(*tData);
	ItsIso14827SubscriptionTimer *sTmr = tmr->x.subscription;

	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, sTmr->key);
	if (domain)
	{	// 타이머가 지정하는 내 도메인 있음
		ItsIso14827ServerDomain *server = domain->x.server;
		ItsIso14827ServerDomainClientEntry *client = ItsIso14827ServerDomain_findClientByPeerUser(server, sTmr->peer, sTmr->user);
		if (client)
		{	// 타이머가 지정하는 클라이언트 도메인 있음
			ItsIso14827SubscriptionEntry key = { sTmr->subID }, *node = client->subscriptions->extract(client->subscriptions, &key);
			if (node)
			{	// 타이머가 지정하는 Subscription있음
				Iso14827SubscriptionData *data = node->data;
				Iso14827SubscriptionDataMode *mode = data->mode;
				ItsIso14827SessionEntry *session = NULL;

				ItsIso14827SubscriptionEntryCleanupArg _arg = { timer, client, server->name, node, NULL, uArg, uRsc, server->hdr_opt_flag };

				pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
				pthread_cleanup_push(ItsIso14827SubscriptionEntry_expire, (void *)&_arg);
				if ((session = _arg.session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key)) == NULL)
				{	// 클라이언트에 해당하는 세션이 없음
					switch(mode->present)
					{
					case Iso14827SubscriptionDataModePresent_periodic:
						_subscriptionDeactivate(client, server->name, node, mode->x.periodic, TRUE, timer);
						break;
					case Iso14827SubscriptionDataModePresent_eventDriven:
						_subscriptionDeactivate(client, server->name, node, mode->x.eventDriven, TRUE, timer);
						break;
					default:
						break;
					}
					ERR_SET_OUT(errp, EPIPE);
				}
				else
				{	// 클라이언트에 해당하는 세션이 있음
					Iso14827Registered *sch = NULL;
					switch(mode->present)
					{
					case Iso14827SubscriptionDataModePresent_periodic:
						sch = mode->x.periodic;
						if ((*errp = _startDailySchedule(client, server->name, node, sch->x.daily, timer)).code) ERR_OUT(errp);
						else if ((*errp = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(errp);
						else node = NULL;
						break;
					case Iso14827SubscriptionDataModePresent_eventDriven:
						sch = mode->x.eventDriven;
						if ((*errp = _startDailySchedule(client, server->name, node, sch->x.daily, timer)).code) ERR_OUT(errp);
						else if ((*errp = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(errp);
						else node = NULL;
						break;
					default:
						break;
					}
				}
				pthread_cleanup_pop(errp->code); // (ItsIso14827SubscriptionEntry_expire, (void *)&_arg);
				pthread_cleanup_pop(1); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}

// 시작일이 미래인 경우, targetDate 자정에 깨어나는 타이머 등록
static Dz1Error _setStartDailyScheduleTimer(ItsIso14827ServerDomainClientEntry *client,
											Dz1Asn1UTF8Str *domainName,
											ItsIso14827SubscriptionEntry *node,
											time_t targetDate,
											void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	time_t tNow = time(NULL);														// 지금 시간
	u64_t duration = targetDate > tNow ? (u64_t)1000000 * (targetDate - tNow) : 0;	// 지금부터 목적시간까지의 시간차
	if ((*errp = ItsIso14827ServerDomainSubscriptionTimer_reg(timer, domainName, client->peer, client->user,
															  node->serial, DOMAIN_SUBSCRIPTION_REGISTERED_START,
															  duration, _startDailyScheduleTimeout)).code) ERR_OUT(errp);
	return err;
}
/******************************************************************************
 * Periodic/Event-Driven Daily Schedule Tracking Timers - END
 *****************************************************************************/

/******************************************************************************
 * Periodic/Event-Driven Continuous Schedule Starter - START
 *****************************************************************************/
///////////////////////////////////////////////////////////////////////////////
// Continuous Schedule Start/Stop Time Helper
///////////////////////////////////////////////////////////////////////////////
static Dz1Error _takeStartTimeContinuous(ItsIso14827SubscriptionEntry *dst, Iso14827RegisteredContinuous *sch, time_t tNow)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (sch->start == NULL)
	{	// 당장 시작, 이 시간이 시작시간으로 지정. Period는 이 시간으로부터 추정
		dst->start = tNow;
	}
	// 계산한 시간이 과거일 수 있음
	else if ((err = Iso14827Time2Time(&dst->start, sch->start)).code) ERR_OUT(&err);
	return err;
}

static Dz1Error _takeEndTimeContinuous(ItsIso14827SubscriptionEntry *dst, Iso14827RegisteredContinuous *sch)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (sch->end == NULL)
	{	// 끝없이 달려~
		dst->end = 0;
	}
	else if ((err = Iso14827Time2Time(&dst->end, sch->end)).code) ERR_OUT(&err);
	return err;
}
///////////////////////////////////////////////////////////////////////////////
// Periodic/Event-Driven Continuous Start Scheduler
///////////////////////////////////////////////////////////////////////////////
static u8_t _getWeekBit(time_t midnight)
{
	struct tm *tm_p = localtime(&midnight), tm = *tm_p;
	return _tmWDAY2WEEKBIT(tm.tm_wday);
}

static bool_t _isAvailableSchedule(ItsIso14827SubscriptionEntry *node, u8_t daysOfWeek)
{	// Daily든 Continuou든 start는 0이 아닌 값이다. end는 0일 수 있다
	time_t start = node->start, end = node->end;
	if (daysOfWeek == 0) return FALSE;	// 활성 요일 비트가 0이면 비정상
	else if (end != 0)
	{	// 끝이 있음
		if (end <= start) return FALSE;	// 시작이 끝보다 과거다 -> 비정상
		else if ((daysOfWeek & ISO14827DAILY_OTHER) == 0 && (daysOfWeek != ISO14827DAILY_FULLWEEK))
		{	// 시작~끝 사이에 활성화 되는 요일이 있는지 검사한다.
			int cnt;
			u8_t temp = 0;
			time_t s = _calcMidNightFromTime(start), e = _calcMidNightFromTime(end);
			for (cnt = 0, s = _calcMidNightFromTime(start); cnt < 7 && s <= e; cnt++, s += (24 * 3600))
			{	// 시작일 자정부터 종료일 자정까지 최대 7회만
				temp |= _getWeekBit(s);
			}

			if ((daysOfWeek & temp) == 0) return FALSE;	// 활성 요일이 하나두 없음
			else
			{	// 활성 요일 있음
				time_t base = _calcMidNightFromTime(time(NULL));
				struct tm *tm_p = NULL, tmTrack, tmTemp;

				// 오늘과 시작일 중 큰것을 기준으로...
				s = _calcMidNightFromTime(start);
				if (s < base) s = base;

				tm_p = localtime(&e); tmTrack = *tm_p;
				while((e > s) && (_isItWorkingDay(daysOfWeek, tmTrack.tm_wday) == FALSE))
				{	// 종료일이 기준일보다 미래이고, 활성 요일이 아니면
					e -= (24 * 3600);						// 하루 뺀다.
					tm_p = localtime(&e); tmTrack = *tm_p;	// 시간 정보 갱신
				}

				tm_p = localtime(&node->end); tmTemp = *tm_p;
				Dz1Thread_printf("@@@ End Date Current = " DZ1_TIME_TM_FMT_FULL "\n",
								  DZ1_TIME_TM_ARG_FULL(&tmTemp));

				node->end = e + (23 * 3600) + (59 * 60) + 59;

				tm_p = localtime(&node->end); tmTemp = *tm_p;
				Dz1Thread_printf("@@@ End Date Changed = " DZ1_TIME_TM_FMT_FULL "\n",
								  DZ1_TIME_TM_ARG_FULL(&tmTemp));
				return TRUE;
			}
		}
		else return TRUE;
	}
	else
	{	// 끝이 없음 -> 무조건 일정 정상
		return TRUE;
	}
}

// Called from FSM
// 시작과 끝 Timer를 등록한다.
static Dz1Error _startScheduleContinuous(ItsIso14827ServerDomainClientEntry *client,
										 Dz1Asn1UTF8Str *domainName,
										 ItsIso14827SubscriptionEntry *src,
										 Iso14827RegisteredContinuous *sch,
										 void *timer)
{	// Periodic은 Activate될 때 주기 Timer가 등록된다
	time_t tNow = time(NULL);
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((err = _takeStartTimeContinuous(src, sch, tNow)).code) ERR_OUT(&err);
	else if ((err = _takeEndTimeContinuous(src, sch)).code) ERR_OUT(&err);
	else if (_isAvailableSchedule(src, 0x7F) == FALSE) ERR_SET_OUT(&err, ETIMEDOUT);
	else
	{
		u64_t toStart = src->start > tNow ? (u64_t)1000000 * (src->start - tNow) : 0;

		struct tm *_tmStart = localtime(&src->start), tmStart = *_tmStart;
		Dz1Thread_printf("@@@ Continuous Subscription Start = " DZ1_TIME_TM_FMT_FULL "\n", DZ1_TIME_TM_ARG_FULL(&tmStart));

		if ((err = ItsIso14827ServerDomainSubscriptionTimer_reg(timer, domainName, client->peer, client->user, src->serial,
													DOMAIN_SUBSCRIPTION_REGISTERED_START, toStart,
													_subscriptionActivateTimeout)).code) ERR_OUT(&err);
		else if (src->end != 0)
		{
			u64_t toEnd = (u64_t)1000000 * (src->end - tNow);

			struct tm *_tmEnd = localtime(&src->end), tmEnd = *_tmEnd;
			Dz1Thread_printf("@@@ Continuous Subscription End = " DZ1_TIME_TM_FMT_FULL "\n", DZ1_TIME_TM_ARG_FULL(&tmEnd));

			if ((err = ItsIso14827ServerDomainSubscriptionTimer_reg(timer, domainName, client->peer, client->user, src->serial,
														DOMAIN_SUBSCRIPTION_REGISTERED_STOP, toEnd,
														_subscriptionDeactivateTimeout)).code) ERR_OUT(&err);
		}
	}
	return err;
}
/******************************************************************************
 * Periodic/Event-Driven Continuous Schedule Starter - END
 *****************************************************************************/

/******************************************************************************
 * Periodic/Event-Driven Daily Schedule Starter - START
 *****************************************************************************/
///////////////////////////////////////////////////////////////////////////////
// Daily Schedule Start/Stop Time Helper
///////////////////////////////////////////////////////////////////////////////
// Daily의 시작 시간은 시작일 00:00:00
static Dz1Error _takeStartTimeDaily(ItsIso14827SubscriptionEntry *dst, Iso14827RegisteredDaily *sch, time_t tNow)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (sch->startDate == NULL)
	{	// 당장 시작, 시작시간은 당일 자정. Period는 이 시간으로부터 추정
		struct tm *tm_p = localtime(&tNow), tmStart = *tm_p;
		tmStart.tm_hour = 0;
		tmStart.tm_min = 0;
		tmStart.tm_sec = 0;
		dst->start = mktime(&tmStart);
	}
	else if ((err = Iso14827Time2MidnightTime(&dst->start, sch->startDate)).code) ERR_OUT(&err);
	return err;
}

// Daily의 종료 시간은 종료일 23:59:59임
static Dz1Error _takeEndTimeDaily(ItsIso14827SubscriptionEntry *dst, Iso14827RegisteredDaily *sch)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (sch->endDate == NULL)
	{	// 끝이 없음
		dst->end = 0;
	}
	else if ((err = Iso14827Time2MidnightTime(&dst->end, sch->endDate)).code) ERR_OUT(&err);
	else dst->end += (23 * 3600) + (59 * 60) + 59;
	return err;
}
static Dz1Error _fixupStartTimeDaily(Iso14827RegisteredDaily *dst, time_t tNow)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst->startTime == NULL)
	{
		struct tm *tm_p = localtime(&tNow), tmNow = *tm_p;
		if ((dst->startTime = Iso14827Time_new(NULL, NULL, NULL,
										tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec,
										NULL, NULL, &err)) == NULL) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error _fixupDurationDaily(Iso14827RegisteredDaily *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst->duration == NULL)
	{
		if ((dst->duration = Dz1u16_new(1440, &err)) == NULL) ERR_OUT(&err);
	}
	else if (*dst->duration > 1440) *dst->duration = 1440;
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Periodic/Event-Driven Daily Scheduler Starter
///////////////////////////////////////////////////////////////////////////////
// Called from FSM
static Dz1Error _startScheduleDaily(ItsIso14827ServerDomainClientEntry *client,
									Dz1Asn1UTF8Str *domainName,
									ItsIso14827SubscriptionEntry *node,
									Iso14827RegisteredDaily *sch, void *timer)
{	// Daily Schedule은 시작만 지정하며, 매일 자정에 깨어나 정확한 시작 시간을 계산한다.
	// End Date까지 반복한다.
	time_t tNow = time(NULL);
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if		((err = _takeEndTimeDaily(node, sch)).code) ERR_OUT(&err);				// 최종 종료일 계산
	else if ((err = _takeStartTimeDaily(node, sch, tNow)).code) ERR_OUT(&err);		// 최초 시작일 계산
	else if ((err = _fixupStartTimeDaily(sch, tNow)).code) ERR_OUT(&err);			// 시작시간 NULL 인 경우 생성
	else if ((err = _fixupDurationDaily(sch)).code) ERR_OUT(&err);					// 유지시간 NULL 인 경우 생성
	else if (_isAvailableSchedule(node, sch->daysOfWeek) == FALSE) ERR_SET_OUT(&err, ETIMEDOUT);	// 시작 끝 앞뒤 맞는지 검사
	else
	{
		time_t midnight = _calcMidNightFromTime(tNow);								// 오늘 자정 시간 구하기

		ItsIso14827SubscriptionDate_delAndSetNull(&node->daily);					// daily 삭제(Update 시 이전 값을 제거)

		if ((node->start != 0) && (midnight < node->start))
		{	// 시작일 자정 시간이 미래-> 시작일 자정에 시작처리 함수 호출
			struct tm *_tm_p = localtime(&node->start), tmTemp = *_tm_p;
			Dz1Thread_printf("@@@ Daily Subscription will start " DZ1_TIME_TM_FMT_FULL "\n", DZ1_TIME_TM_ARG_FULL(&tmTemp));
			if ((err = _setStartDailyScheduleTimer(client, domainName, node, node->start, timer)).code) ERR_OUT(&err);
		}
		else if ((node->end == 0) || tNow < node->end)
		{	// 활성 기간 이내
			struct tm *tm_p = localtime(&tNow), tmNow = *tm_p;
			time_t tStart = _calcStartTime(sch, tmNow);
			time_t tEnd = _calcEndTime(sch, tStart);
			if (tNow < tEnd)
			{	// 종료 시간 이전 -> 당장 시작/끝 타이머 등록
				if ((err = _startDailySchedule(client, domainName, node, sch, timer)).code) ERR_OUT(&err);
			}
			else
			{	// 종료 시간 이후 -> 내일 자정에 시작처리 함수 호출
				time_t tomorrow = midnight + (3600 * 24);
				if (node->end != 0 && node->end < tomorrow)
				{	// 내일은 이미 종료일이 지남
					ERR_SET_OUT(&err, ETIMEDOUT);
				}
				else
				{
					struct tm *_tmTemp = localtime(&tomorrow), tmTemp = *_tmTemp;
					Dz1Thread_printf("@@@ Daily Subscription will start " DZ1_TIME_TM_FMT_FULL "\n", DZ1_TIME_TM_ARG_FULL(&tmTemp));

					if ((err = _setStartDailyScheduleTimer(client, domainName, node, tomorrow, timer)).code) ERR_OUT(&err);
				}
			}
		}
		else
		{	// 활성기간은 다 지나감 -> don't care
			ERR_SET_OUT(&err, ETIMEDOUT);
		}
	}
	return err;
}
/******************************************************************************
 * Periodic/Event-Driven Daily Schedule Starter - END
 *****************************************************************************/

///////////////////////////////////////////////////////////////////////////////
// Subscription Start Scheduler
///////////////////////////////////////////////////////////////////////////////
// Called from FSM
// 서비스 Duration이 안되면 ETIMEDOUT
static Dz1Error _startScheduleRegistered(ItsIso14827ServerDomainClientEntry *client,
								Dz1Asn1UTF8Str *domainName,
								ItsIso14827SubscriptionEntry *node,
								Iso14827Registered *r,
								void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(r->present)
	{
	case Iso14827RegisteredPresent_continuous:
		if ((err = _startScheduleContinuous(client, domainName, node, r->x.continuous, timer)).code) ERR_OUT(&err);
		break;
	case Iso14827RegisteredPresent_daily:
		if ((err = _startScheduleDaily(client, domainName, node, r->x.daily, timer)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

// Called from FSM
static Dz1Error _startSchedule(ItsIso14827ServerDomainClientEntry *client,
							   Dz1Asn1UTF8Str *domainName,
							   ItsIso14827SubscriptionEntry *node,
							   Iso14827SubscriptionDataMode *mode,
							   void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(mode->present)
	{
	default:
	case Iso14827SubscriptionDataModePresent_single:
		break;
	case Iso14827SubscriptionDataModePresent_periodic:
	case Iso14827SubscriptionDataModePresent_eventDriven:
		if ((err = _startScheduleRegistered(client, domainName, node,
								(Iso14827Registered *)mode->x.__ptr__, timer)).code) ERR_OUT(&err);
		break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Misc.
static Dz1Error _setupRetriedData(ItsIso14827ServerSubscriptionFsmArg *fsmArg, ItsIso14827SubscriptionOperPresent present, u32_t pktNbr, Iso14827SubscriptionData *data)
{
	ItsIso14827SubscriptionOper *oper = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((fsmArg->retried = oper = ItsIso14827SubscriptionOper_new(present, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827SubscriptionReq *req = NULL;
		pthread_cleanup_push(ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->retried);

		if ((oper->x.__ptr__ = req = ItsIso14827SubscriptionReq_new(pktNbr, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((req->data = Iso14827SubscriptionData_clone(data, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(errp->code); // (ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->retried);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// FSM Message
typedef struct ItsIso14827SubscriptionMsg
{
	ItsIso14827SessionEntry		*session;

	Dz1Asn1OctetStr				*authInfo;
	s32_t						 priority;
	u32_t						 pktNbr;
	Iso14827PDUs				*pdu;
	bool_t						 isRetried;
	Iso14827RejectSubscription	 reason;
	Iso14827PublicationType		*pubType;
} ItsIso14827SubscriptionMsg;

///////////////////////////////////////////////////////////////////////////////
// FSM Functions
static Dz1FsmReturn SS00(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// waitAddConfirm : Peer send New/Update Subscription
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;
	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
	ItsIso14827SessionEntry *session = msg->session;

	if (msg->isRetried == TRUE)
	{	// 재전송 된거면
		Iso14827PDUs *pdu = msg->pdu;
		Iso14827Subscription *sub = pdu->x.subscription;
		Iso14827SubscriptionType *type = sub->type;

		if (fsmArg->retried != NULL)
		{	// 앞서 전송된 Retry Packet이 있음
			_sendRejectSubscription(client, domainName, session, msg->pktNbr,
									Iso14827RejectSubscription_other, server->hdr_opt_flag,
									uArg, uRsc, timer);
		}
		else if ((*errp = _setupRetriedData(fsmArg, ItsIso14827SubscriptionOperPresent_create,
											msg->pktNbr, type->x.data)).code) ERR_OUT(errp);
		else
		{
			ItsIso14827SubscriptionEntry *node = fsmArg->subscription;
			_subscriptionCallback(client, domainName, node->serial, node->data);
		}
	}
	else
	{	// 있는데 또!!
		_sendRejectSubscription(client, domainName, session, msg->pktNbr,
								Iso14827RejectSubscription_other,
								server->hdr_opt_flag, uArg, uRsc, timer);
	}

	return ret;
}

static Dz1FsmReturn SS01(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// Established : Peer send New Subscription
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;

	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;
	ItsIso14827SubscriptionEntry *node = fsmArg->subscription;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
	ItsIso14827SessionEntry *session = msg->session;

	Iso14827PDUs *pdu = msg->pdu;
	Iso14827Subscription *subscription = pdu->x.subscription;
	Iso14827SubscriptionType *type = subscription->type;
	Iso14827SubscriptionData *data = type->x.data;

	if (msg->isRetried == TRUE)
	{	// 재전송 된거면
		_sendAcceptSubscription(client, domainName, session,
								msg->pktNbr, data->mode,
								server->hdr_opt_flag, uArg, uRsc, timer);
	}
	else
	{	// 잘 있는데 왜!!!
		_sendRejectSubscription(client, domainName, session, msg->pktNbr,
								Iso14827RejectSubscription_other,
								server->hdr_opt_flag, uArg, uRsc, timer);
	}

	return ret;
}

static Dz1FsmReturn SSrj(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// else : Peer send New Subscription
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;

	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
	ItsIso14827SessionEntry *session = msg->session;

	_sendRejectSubscription(client, domainName, session, msg->pktNbr,
							Iso14827RejectSubscription_other,
							server->hdr_opt_flag, uArg, uRsc, timer);
	return ret;
}

static Dz1FsmReturn SS02(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// waitAddConfirm : application send add OK
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;

	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;

	ItsIso14827SubscriptionEntry *node = fsmArg->subscription;
	Iso14827SubscriptionData *data = node->data;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
	ItsIso14827SessionEntry *session = msg->session;

	_sendAcceptSubscription(client, domainName, session, 
							node->pktNbr, /*node->serial, */
							data->mode, server->hdr_opt_flag, 
							uArg, uRsc, timer);
//	_sendAcceptSubscriptionRetried(fsmArg, client, domainName, session, node->serial, ItsIso14827SubscriptionOperPresent_create, uArg, uRsc, timer);

	// Start Schedule if registered subscription
	if ((*errp = _startSchedule(client, domainName, node, data->mode, timer)).code)
	{	// Client에 Terminate를 알려줌
		ERR_OUT(errp);

		ItsIso14827SubscriptionEntry_timerCleanup(client, domainName, node, timer);
		_sendPubControl(client, domainName, session, node->serial, node->data, node->pubSerial++, Iso14827PublicationMgmt_terminateOther, server->hdr_opt_flag, uArg, uRsc, timer);

		/////////////////////////////////////////////
		// 2025-11-17 : fixed
		if (node->pubSerial == 0) node->pubSerial = 1;
		// 2025-11-17 : fixed
		/////////////////////////////////////////////

		ret = Dz1FsmReturn_terminate;
	}
	else fsm->state = ItsIso14827SubscriptionState_established;

	return ret;
}

static Dz1FsmReturn SS03(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// waitAddConfirm : application send add Reject
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;

	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;
	ItsIso14827SubscriptionEntry *node = fsmArg->subscription;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
	ItsIso14827SessionEntry *session = msg->session;

	_sendRejectSubscription(client, domainName, session,
							node->pktNbr, msg->reason,
							server->hdr_opt_flag, uArg, uRsc, timer);

	_sendRejectSubscriptionRetried(fsmArg, client, domainName, session,
								   ItsIso14827SubscriptionOperPresent_create,
								   msg->reason, uArg, uRsc, timer);

	ret = Dz1FsmReturn_terminate;

	return ret;
}

static Dz1FsmReturn SS04(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// Established : Peer send Update Subscription
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;

	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;
	ItsIso14827SubscriptionEntry *node = fsmArg->subscription;
	Iso14827SubscriptionData *dst = node->data;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
	ItsIso14827SessionEntry *session = msg->session;
	Iso14827PDUs *pdu = msg->pdu;
	Iso14827Subscription *subscription = pdu->x.subscription;
	Iso14827SubscriptionType *type = subscription->type;
	Iso14827SubscriptionData *src = type->x.data;

	if (fsmArg->oper != NULL)
	{	// 이전에 보낸 Update가 있다?
		_sendRejectSubscription(client, domainName, session, msg->pktNbr,
								Iso14827RejectSubscription_other,
								server->hdr_opt_flag, uArg, uRsc, timer);
	}
	else if (src->fmt != Iso14827SubscriptionDataFormat_dataPacket)
	{	// Data Packet말고는 지원 안함
		_sendRejectSubscription(client, domainName, session, msg->pktNbr,
								Iso14827RejectSubscription_publishFormatNotSupported,
								server->hdr_opt_flag, uArg, uRsc, timer);
	}
	else
	{
		ItsIso14827SubscriptionOper *oper = NULL;
		Iso14827SubscriptionDataMode *dstMode = dst->mode;
		Iso14827SubscriptionDataMode *srcMode = src->mode;
		if (_isUpdatableMode(dstMode, srcMode) == FALSE)
		{	// Mode가 바뀌는 것은 허용하지 않는다.
			_sendRejectSubscription(client, domainName, session, msg->pktNbr,
									Iso14827RejectSubscription_invalidMode,
									server->hdr_opt_flag, uArg, uRsc, timer);
		}
		else if (src->persistent != dst->persistent)
		{	// persistance가 바뀌는것도 혀용하지 않는다.
			_sendRejectSubscription(client, domainName, session, msg->pktNbr,
									Iso14827RejectSubscription_other,
									server->hdr_opt_flag, uArg, uRsc, timer);
		}
		// Update에 필요한 부분만 취하여 새로 만든다.
		else if ((fsmArg->oper = oper = ItsIso14827SubscriptionOper_new(ItsIso14827SubscriptionOperPresent_update, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ItsIso14827SubscriptionReq *req = NULL;
			Iso14827SubscriptionData *update = NULL;
			pthread_cleanup_push(ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->oper);

			if ((oper->x.update = req = ItsIso14827SubscriptionReq_new(msg->pktNbr, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((req->data = update = Iso14827SubscriptionData_new(src->persistent, src->status, NULL,
																		src->fmt, src->priority, src->guarantee,
																		NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((update->mode = Iso14827SubscriptionDataMode_clone(src->mode, errp)) == NULL) ERR_OUT(errp);
			{
				// Application에 각 요청을 알림... Accept/Reject는 Application이 되돌려 주는 값으로...
				_subscriptionCallbackUpdate(client, domainName, node->serial, update, src->msg);
				fsm->state = ItsIso14827SubscriptionState_waitUpdateConfirm;
			}

			pthread_cleanup_pop(errp->code); // (ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->oper);
		}
	}
	return ret;
}

static Dz1FsmReturn SS05(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// waitUpdateConfirm : Peer send Update Subscription
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;
	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
	ItsIso14827SessionEntry *session = msg->session;

	if (msg->isRetried == TRUE)
	{	// 재전송 된거면
		Iso14827PDUs *pdu = msg->pdu;
		Iso14827Subscription *sub = pdu->x.subscription;
		Iso14827SubscriptionType *type = sub->type;
		Iso14827SubscriptionData *src = type->x.data;
		if (fsmArg->retried != NULL)
		{	// 앞서 전송된 Retry Packet이 있음
			_sendRejectSubscription(client, domainName, session, msg->pktNbr,
									Iso14827RejectSubscription_other,
									server->hdr_opt_flag, uArg, uRsc, timer);
		}
		else if ((*errp = _setupRetriedData(fsmArg, ItsIso14827SubscriptionOperPresent_update, msg->pktNbr, src)).code) ERR_OUT(errp);
	}
	else
	{	// 했는데 또!!
		_sendRejectSubscription(client, domainName, session, msg->pktNbr,
								Iso14827RejectSubscription_other,
								server->hdr_opt_flag, uArg, uRsc, timer);
	}

	return ret;
}

static void _updateData(Iso14827SubscriptionData *dst, Iso14827SubscriptionData *src)
{
	dst->persistent = src->persistent;
	Iso14827SubscriptionDataMode_delAndSetNull(&dst->mode);
	dst->mode = src->mode; src->mode = NULL;
	dst->fmt = src->fmt;
	dst->priority = src->priority;
	dst->guarantee = src->guarantee;
}

static Dz1FsmReturn SS06(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// waitUpdateConfirm : application send add OK
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;
	if (fsmArg->oper != NULL)
	{
		ItsIso14827SubscriptionOper *oper = fsmArg->oper;
		pthread_cleanup_push(ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->oper);

		if (oper->present == ItsIso14827SubscriptionOperPresent_update)
		{
			ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
			Dz1Asn1UTF8Str *domainName = fsmArg->domainName;

			ItsIso14827SubscriptionEntry *node = fsmArg->subscription;
			Iso14827SubscriptionData *dst = node->data;

			ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
			ItsIso14827SessionEntry *session = msg->session;

			ItsIso14827SubscriptionReq *req = oper->x.update;
			Iso14827SubscriptionData *update = req->data;

			ItsIso14827ServerDomainCallback *cbs = client->cb;

			_sendAcceptSubscription(client, domainName, session, 
									req->pktNbr, /*node->serial, */
									update->mode, server->hdr_opt_flag, 
									uArg, uRsc, timer);
//			_sendAcceptSubscriptionRetried(fsmArg, client, domainName, session, node->serial, ItsIso14827SubscriptionOperPresent_update, uArg, uRsc, timer);

			// apply Update data to current & reschedule timer
			ItsIso14827SubscriptionEntry_timerCleanup(client, domainName, node, timer);
			if (node->isActive)
			{
				if (cbs->stopped) cbs->stopped(cbs->param, domainName, client->peer, client->user, node->serial);
			}

			if (cbs->expired)
			{
				ItsIso14827SubscriptionExpireReason reason = { ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired, { NULL } };
				cbs->expired(cbs->param, domainName, client->peer, client->user, node->serial, &reason);
			}

			_updateData(dst, update);

			if ((*errp = _startSchedule(client, domainName, node, dst->mode, timer)).code)
			{	// 에러가 나면...
				Iso14827PublicationMgmt code = Iso14827PublicationMgmt_terminateOther;
				ItsIso14827SubscriptionEntry_timerCleanup(client, domainName, node, timer);
				if (errp->code == ETIMEDOUT) code = Iso14827PublicationMgmt_terminateDataNoLongerAvailable;
				_sendPubControl(client, domainName, session,
								node->serial, node->data, node->pubSerial++,
								code, server->hdr_opt_flag, uArg, uRsc, timer);

				/////////////////////////////////////////////
				// 2025-11-17 : fixed
				if (node->pubSerial == 0) node->pubSerial = 1;
				// 2025-11-17 : fixed
				/////////////////////////////////////////////

				ERR_OUT(errp);
			}
		}
		pthread_cleanup_pop(1); // (ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->oper);
	}
	fsm->state = ItsIso14827SubscriptionState_established;

	return ret;
}

static Dz1FsmReturn SS07(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// waitUpdateConfirm : application send add Reject
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;
	if (fsmArg->oper != NULL)
	{
		ItsIso14827SubscriptionOper *oper = fsmArg->oper;
		pthread_cleanup_push(ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->oper);

		if (oper->present == ItsIso14827SubscriptionOperPresent_update)
		{
			ItsIso14827SubscriptionReq *req = oper->x.update;

			//ItsIso14827SubscriptionEntry *node = fsmArg->subscription;
			ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
			Dz1Asn1UTF8Str *domainName = fsmArg->domainName;

			ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
			ItsIso14827SessionEntry *session = msg->session;

			_sendRejectSubscription(client, domainName, session,
									req->pktNbr, msg->reason,
									server->hdr_opt_flag, uArg, uRsc, timer);

			_sendRejectSubscriptionRetried(fsmArg, client, domainName, session,
										   ItsIso14827SubscriptionOperPresent_update,
										   msg->reason, uArg, uRsc, timer);
		}
		pthread_cleanup_pop(1); // (ItsIso14827SubscriptionOper_delAndSetNull, (void *)&fsmArg->oper);
	}
	fsm->state = ItsIso14827SubscriptionState_established;
	return ret;
}

static Dz1FsmReturn SS08(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// Established : Peer send Delete Subscription
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;

	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;

	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	ItsIso14827ServerDomainCallback  *cbs = client->cb;

	ItsIso14827SubscriptionEntry *node = fsmArg->subscription;

	Iso14827SubscriptionData *data = node->data;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);

	ItsIso14827SessionEntry *session = msg->session;

	Iso14827PDUs *pdu = msg->pdu;
	Iso14827Subscription *subscription = pdu->x.subscription;
	Iso14827SubscriptionType *type = subscription->type;
	Iso14827SubscriptionCancel reason = type->x.reason;

	_sendAcceptSubscription(client, domainName, session, 
							msg->pktNbr, /*node->serial, */
							data->mode, server->hdr_opt_flag, 
							uArg, uRsc, timer);

	ItsIso14827SubscriptionEntry_timerCleanup(client, domainName, node, timer);
	if (node->isActive)
	{
		if (cbs->stopped) cbs->stopped(cbs->param, domainName, client->peer, client->user, node->serial);
		node->isActive = FALSE;
	}
	if (cbs->expired)
	{
		ItsIso14827SubscriptionExpireReason terminated = { ItsIso14827SubscriptionExpireReasonPresent_clientRequested };
		terminated.x.clientRequested = reason;
		cbs->expired(cbs->param, domainName, client->peer, client->user, node->serial, &terminated);
	}
	ret = Dz1FsmReturn_terminate;

	return ret;
}

static Dz1FsmReturn SS11(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// established : Application send Publication
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
	ItsIso14827ServerDomain *server = fsmArg->server;

	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;
	ItsIso14827SubscriptionEntry *node = fsmArg->subscription;
	Iso14827SubscriptionData *data = node->data;
	Iso14827SubscriptionDataMode *mode = data->mode;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
	ItsIso14827SessionEntry *session = msg->session;

	Iso14827PublicationType *type = msg->pubType;

	if (mode->present == Iso14827SubscriptionDataModePresent_single)
	{
		if ((*errp = _sendPublicationType(client, domainName, session,
										  node->serial, data,
										  node->pubSerial++, &msg->pubType,
										  server->hdr_opt_flag,
										  uArg, uRsc, timer)).code) ERR_OUT(errp);

		/////////////////////////////////////////////
		// 2025-11-17 : fixed
		if (node->pubSerial == 0) node->pubSerial = 1;
		// 2025-11-17 : fixed
		/////////////////////////////////////////////

		ret = Dz1FsmReturn_terminate;
	}
	else
	{	// Periodic/Event-Driven
		Iso14827PublicationMgmt cmd;
		switch(type->present)
		{
		case Iso14827PublicationTypePresent_mgmt:
			cmd = type->x.mgmt;
			switch(cmd)
			{
			case Iso14827PublicationMgmt_temporarilySuspended:
				node->isPaused = TRUE;
				break;
			case Iso14827PublicationMgmt_resume:
				node->isPaused = FALSE;
				break;
			default:
				ItsIso14827SubscriptionEntry_timerCleanup(client, domainName, node, timer);
				ret = Dz1FsmReturn_terminate;
				break;
			}

			if ((*errp = _sendPublicationType(client, domainName, session,
											  node->serial, data,
											  node->pubSerial++, &msg->pubType,
											  server->hdr_opt_flag,
											  uArg, uRsc, timer)).code) ERR_OUT(errp);

			/////////////////////////////////////////////
			// 2025-11-17 : fixed
			if (node->pubSerial == 0) node->pubSerial = 1;
			// 2025-11-17 : fixed
			/////////////////////////////////////////////

			break;
		case Iso14827PublicationTypePresent_msg:
			/*
			for system health monitoring, check here which following conditions
			// ----------------------------------------------------------------------------------------------------------------------
			If the mode is "periodic", the server shall attempt to produce a new publication periodically
			at a frequency as defined by datexRegistered-UpdateDelay-qty.
			If the subscription is sent after the start time, the cycle shall be synchronized with the datexRegistered-StartTime.

			In the periodic mode, a server should publish information at every cycle point.
			If the server is unable to publish the information within a period of 60 % of a cycle beyond the cycle point,
			the publication should not be transmitted.
			Both the server and the client should terminate less important subscriptions
			(e.g. as reflected in the datexSubscription-Priority field) to minimize the probability of this occuring.

			--> omit message if moment over 60% of cycle and call sysHealthAlarm callback
			// ----------------------------------------------------------------------------------------------------------------------
			If the mode is "event-driven", the server shall produce a publication within a period of datexRegistered-UpdateDelay-qty
			after the server is notified of an event. Thus, in this case, the datexRegistered-UpdateDelay-qty parameter serves as
			a maximum latency value for event reporting.
			The subscription message shall define the term "event" in the definition and/or message body.

			If the maximum latency is exceeded, the data shall be published as soon as possible and
			the datexPublish-LatePublicationFlag shall be set.
			Servers should terminate less important subscriptions (as reflected in the datexSubscription-Priority field)
			to minimize the probability of this occuring.

			--> set datexPublish-LatePublicationFlag to TRUE if maximum latency is exceeded and call sysHealthAlarm callback
			// ----------------------------------------------------------------------------------------------------------------------
			*/
			if ((*errp = _sendPublicationType(client, domainName, session,
											  node->serial, data,
											  node->pubSerial++, &msg->pubType,
											  server->hdr_opt_flag,
											  uArg, uRsc, timer)).code) ERR_OUT(errp);
			
			/////////////////////////////////////////////
			// 2025-11-17 : fixed
			if (node->pubSerial == 0) node->pubSerial = 1;
			// 2025-11-17 : fixed
			/////////////////////////////////////////////

			break;
		default:
			// don't care
			break;
		}
	}

	return ret;
}

static Dz1FsmReturn SS12(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **ptr, Dz1Error *errp)
{	// established : Peer Send REJECT
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827ServerSubscriptionFsmArg *fsmArg = (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;

	ItsIso14827ServerDomainClientEntry *client = fsmArg->client;
	Dz1Asn1UTF8Str *domainName = fsmArg->domainName;
	ItsIso14827SubscriptionEntry *node = fsmArg->subscription;

	ItsIso14827SubscriptionMsg *msg = (*(ItsIso14827SubscriptionMsg **)ptr);
	//ItsIso14827SessionEntry *session = msg->session;

	Iso14827PDUs *pdu = msg->pdu;
	Iso14827Reject *nak = pdu->x.nak;
	Iso14827RejectType *type = nak->type;

	ItsIso14827ServerDomainCallback *cbs = client->cb;

	if (type->present == Iso14827RejectTypePresent_publication)
	{
		ItsIso14827PublicarionError reason = { ItsIso14827PublicarionErrorPresent_pubError };
		reason.x.pubError = type->x.publication;
		if (cbs->pubErrorInform)
			cbs->pubErrorInform(cbs->param, domainName, client->peer, client->user, node->serial, &reason);
	}
	else if (type->present == Iso14827RejectTypePresent_pubData)
	{
		ItsIso14827PublicarionError reason = { ItsIso14827PublicarionErrorPresent_pubDataError };
		Iso14827RejectPubData *pubData = type->x.pubData;
		reason.x.pubDataError = pubData->reason;
		if (cbs->pubErrorInform)
			cbs->pubErrorInform(cbs->param, domainName, client->peer, client->user, node->serial, &reason);
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// FSM Table
static Dz1Fsm2Func serverSubscriptionFSM[ItsIso14827SubscriptionState_max][ItsIso14827SubscriptionEvent_max] =
{//   Cre   updt  del   AppOK AppRj Pub   peRej
	{ SS00, SS00, SSrj, SS02, SS03, NULL, NULL },	// waitAddConfirm
	{ SS01, SS04, SS08, NULL, NULL, SS11, SS12 },	// established
	{ SSrj, SS05, SSrj, SS06, SS07, NULL, NULL }	// waitUpdateConfirm
};
//	{ SSrj, SSrj, SS09, NULL, NULL, SS10, NULL, NULL }	// waitDeleteConfirm

///////////////////////////////////////////////////////////////////////////////
// FSM Helper
Dz1Fsm2_getFuncDefine(ItsIso14827ServerDomainSubscriptionFSM_getFunc,
					  ItsIso14827SubscriptionState_max,
					  ItsIso14827SubscriptionEvent_max,
					  serverSubscriptionFSM)

static int ItsIso14827ServerDomainSubscriptionFSM_getEventByData(struct Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *sg)
{
	int ret = 0;
	ItsIso14827SubscriptionMsg *msg = (ItsIso14827SubscriptionMsg *)sg;
	Iso14827PDUs *pdu = msg->pdu;
	if (pdu->present == Iso14827PDUsPresent_nak)
	{
		Iso14827Reject *rej = pdu->x.nak;
		Iso14827RejectType *type = rej->type;
		if (type->present == Iso14827RejectTypePresent_publication ||
			type->present == Iso14827RejectTypePresent_pubData)
			return ItsIso14827SubscriptionEvent_peerReject;
		else
		{
			Dz1Thread_printf("ItsIso14827ServerDomainSubscriptionFSM_getEvent() : it's Invalid PDU!! = ");
			Iso14827PDUs_dump(pdu, 0);
			return -1;
		}
	}
	else if (pdu->present == Iso14827PDUsPresent_subscription)
	{
		Iso14827Subscription *sub = pdu->x.subscription;
		Iso14827SubscriptionType *type = sub->type;
		if (type->present == Iso14827SubscriptionTypePresent_reason) return ItsIso14827SubscriptionEvent_delete;
		else
		{
			Iso14827SubscriptionData *data = type->x.data;
			if (data->status == Iso14827SubscriptionDataStatus_NEW)
				return ItsIso14827SubscriptionEvent_create;
			else return ItsIso14827SubscriptionEvent_update;
		}
	}
	else
	{
		Dz1Thread_printf("ItsIso14827ServerDomainSubscriptionFSM_getEvent() : it's Invalid PDU!! = ");
		Iso14827PDUs_dump(pdu, 0);
		return -1;
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Server Subscription FSM
static Dz1Fsm2 *ItsIso14827ServerDomainSubscriptionFSM_new(ItsIso14827ServerDomain *server,
														   ItsIso14827ServerDomainClientEntry *client,
														   ItsIso14827SubscriptionEntry *subscription,
														   Dz1Error *errp)
{
	Dz1Fsm2 *ret = NULL;
	ItsIso14827ServerSubscriptionFsmArg *arg = ItsIso14827ServerSubscriptionFsmArg_new(server, client, NULL, subscription, errp);

	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerSubscriptionFsmArg_delAndSetNull, (void *)&arg);
		if ((arg->domainName = Dz1Asn1UTF8Str_clone(server->name, errp)) == NULL) ERR_OUT(errp);
		else if ((ret = Dz1Fsm2_new((str_t)"ServerSubscriptionFSM", FALSE, 16,
									ItsIso14827ServerDomainSubscriptionFSM_getEventByData, NULL,
									ItsIso14827ServerDomainSubscriptionFSM_getFunc,
									(void **)&arg, (Dz1DelFunc)ItsIso14827ServerSubscriptionFsmArg_del,
									errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ItsIso14827ServerSubscriptionFsmArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

static Iso14827RejectSubscription _error_code_to_sub_reject_reason(Dz1Error *src)
{
	Iso14827RejectSubscription ret = Iso14827RejectSubscription_other;
	switch(src->code)
	{
	case ENOENT:	ret = Iso14827RejectSubscription_unknownSubscriptionNbr;		break;
	case ENOSYS:	ret = Iso14827RejectSubscription_publishFormatNotSupported;		break;
	case ETIMEDOUT:	ret = Iso14827RejectSubscription_invalidTimes;					break;
	}
	return ret;
}

static Dz1Error _fsm_subscription_check(ItsIso14827SubscriptionEntry *node, Iso14827Subscription *sub)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

// 	ItsIso14827ServerSubscriptionFsmArg *fsmArg		= (ItsIso14827ServerSubscriptionFsmArg *)fsm->fsmArg;
// 	ItsIso14827ServerDomain				*server		= fsmArg->server;
// 	ItsIso14827ServerDomainClientEntry	*client		= fsmArg->client;
// 	Dz1Asn1UTF8Str						*domainName	= fsmArg->domainName;
// 	ItsIso14827SubscriptionEntry		*node		= fsmArg->subscription;
// 
// 	ItsIso14827SessionEntry				*session	= msg->session;
// 	Iso14827PDUs						*pdu		= msg->pdu;
// 	Iso14827Subscription				*sub		= pdu->x.subscription;
 	Iso14827SubscriptionType			*type		= sub->type;

	if (type->present == Iso14827SubscriptionTypePresent_reason)
	{	// 알 수 없는 Subscription 번호
//		_sendRejectSubscription(client, domainName, session, msg->pktNbr, Iso14827RejectSubscription_other, server->hdr_opt_flag, uArg, uRsc, timer);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Iso14827SubscriptionData *data = node->data;
		if (data->fmt != Iso14827SubscriptionDataFormat_dataPacket)
		{	// 다른 전송수단 지원 안함
//			_sendRejectSubscription(client, domainName, session, msg->pktNbr, Iso14827RejectSubscription_publishFormatNotSupported, server->hdr_opt_flag, uArg, uRsc, timer);
			ERR_SET_OUT(errp, ENOSYS);
		}
		else if (_isValidSchedule(data->mode) == FALSE)
		{	// 지나간 일정인 경우
//			_sendRejectSubscription(client, domainName, session, msg->pktNbr, Iso14827RejectSubscription_invalidTimes, server->hdr_opt_flag, uArg, uRsc, timer);
			ERR_SET_OUT(errp, ETIMEDOUT);
		}
		else
		{	// 정상적인 새로운 요청
//			fsm->state = ItsIso14827SubscriptionState_waitAddConfirm;
			Dz1Error_set(errp, 0);
//			_subscriptionCallback(client, domainName, node->serial, node->data);	// Application 에 각 요청을 알림... Accept/Reject 는 Application 이 되돌려 주는 값으로...
		}
	}
	return err;
}

static Dz1Error _recvNak(ItsIso14827ServerDomainClientEntry *client,
						 Dz1Asn1UTF8Str *domainName,
						 ItsIso14827SessionEntry *session,
						 u32_t serial,
						 Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
						 Iso14827PDUs *pdu,
						 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	ItsIso14827SubscriptionEntry key = { serial }, *node = client->subscriptions->find(client->subscriptions, &key);

	if (node != NULL)
	{
		ItsIso14827SubscriptionMsg _msg = { session, authInfo, priority, pktNbr, pdu, FALSE }, *msg = &_msg;
		// 여기선 에러없이 진행된다.
		switch((ret = Dz1Fsm2_proc2(node->fsm, uArg, uRsc, timer, ItsIso14827SubscriptionEvent_peerReject, (void **)&msg, &err)))
		{
		case Dz1FsmReturn_continue:
//			if ((err = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(&err);
// 			else node = NULL;
			client->subscriptions->remove(client->subscriptions, &key);
			break;
		default:
		case Dz1FsmReturn_error:
			ERR_OUT(&err);
		case Dz1FsmReturn_terminate:
			break;
		}
	}
	return err;
}

Dz1Error ItsIso14827ServerDomainClientEntrySubscription_nak(ItsIso14827ServerDomainClientEntry *client,
															Dz1Asn1UTF8Str *domainName,
															ItsIso14827SessionEntry *session,
															Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
															Iso14827PDUs *pdu, Iso14827C2CAuthMsg *sent,
															void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827Reject *rej = pdu->x.nak;
	Iso14827RejectType *type = rej->type;
	if (type->present == Iso14827RejectTypePresent_publication)
	{
		//Iso14827RejectPublication reason = type->x.publication;
		Iso14827PDUs *sentPdu = sent->pdu;
		Iso14827Publication *pub = sentPdu->x.publication;
		Iso14827PublishFormat *sentFmt = pub->fmt;
		if (sentFmt->present == Iso14827PublishFormatPresent_dataList)
		{
			Iso14827PublicationDataList *list = sentFmt->x.dataList;
			Iso14827PublicationData *data = list->getHead(list);
			if (data != NULL)
			{
				if ((err = _recvNak(client, domainName, session, data->subscriptionSerial,
									authInfo, pktNbr, priority, pdu, uArg, uRsc, timer)).code) ERR_OUT(&err);
			}
		}
		else
		{	// 아닌 경우 답없음...
		}
	}
	else if (type->present == Iso14827RejectTypePresent_pubData)
	{
		//Dz1FsmReturn ret = Dz1FsmReturn_continue;

		Iso14827RejectPubData *nakPubData = type->x.pubData;
		if ((err = _recvNak(client, domainName, session, nakPubData->subSerial,
							authInfo, pktNbr, priority, pdu, uArg, uRsc, timer)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Iso14827 Subscription Message Handler
///////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionMgr_received  = 오류 시 Session Entry 삭제
//   -> _ItsIso14827SessionMgr_received = C2C Message 삭제
//     -> ItsIso14827DomainMgr_received = 오류 시 Domain-Session Map 삭제
//	     -> _ItsIso14827DomainMgr_received = Server/Client에 따라 분기
//		   -> ItsIso14827ServerDomain_received = 오류 시 Client 삭제
//		     -> _ItsIso14827ServerDomain_received = PDU종류에 따라 분기
//			   -> ItsIso14827ServerDomainClientEntrySubscription_recv = 오류 시 Subscription 삭제
///////////////////////////////////////////////////////////////////////////////
typedef struct ItsIso14827SubscriptionEntryRejectArg
{
	ItsIso14827ServerDomainClientEntry		*client;
	ItsIso14827ServerDomain					*server;
	ItsIso14827SessionEntry					*session;
	u32_t									 subPktNbr;
	Dz1Error								*err;
	void									*uArg;
	void									*uRsc;
	void									*timer;
} ItsIso14827SubscriptionEntryRejectArg;

static void ItsIso14827SubscriptionEntry_reject(void *ptr)
{
	ItsIso14827SubscriptionEntryRejectArg	*arg		= (ItsIso14827SubscriptionEntryRejectArg *)ptr;
	ItsIso14827ServerDomainClientEntry		*client		= arg->client;
	ItsIso14827ServerDomain					*server		= arg->server;
	ItsIso14827SessionEntry					*session	= arg->session;
	Iso14827RejectSubscription				 reason		= _error_code_to_sub_reject_reason(arg->err);
	_sendRejectSubscription(arg->client, server->name, arg->session, arg->subPktNbr, reason, server->hdr_opt_flag, arg->uArg, arg->uRsc, arg->timer);
}

Dz1Error ItsIso14827ServerDomainClientEntrySubscription_recv(ItsIso14827ServerDomain *server,
															 ItsIso14827ServerDomainClientEntry *client,
															 ItsIso14827SessionEntry *session,
															 Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
															 Iso14827PDUs *pdu, bool_t isRetried,
															 void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Iso14827Subscription *sub = pdu->x.subscription;
	ItsIso14827SubscriptionEntry key = { sub->serial }, *node = client->subscriptions->extract(client->subscriptions, &key);
	if (node == NULL)
	{	// 새로운 Subscription
		Iso14827SubscriptionType *type = sub->type;
		if (type->present == Iso14827SubscriptionTypePresent_reason)	// 없는데 Delete 가 왔다 -> 알 수 없는 Serial
			_sendRejectSubscription(client, server->name, session, pktNbr, Iso14827RejectSubscription_unknownSubscriptionNbr, server->hdr_opt_flag, uArg, uRsc, timer);
		else if ((node = ItsIso14827SubscriptionEntry_new(sub->serial, NULL, pktNbr, type->x.data, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Fsm2 *fsm = NULL;
			ItsIso14827SubscriptionEntryRejectArg _arg = { client, server, session, pktNbr, errp, uArg, uRsc, timer };
			ItsIso14827SubscriptionMsg msg = { session, authInfo, priority, pktNbr, pdu, isRetried };
			type->x.data = NULL;
			pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
			pthread_cleanup_push(ItsIso14827SubscriptionEntry_reject, (void *)&_arg);	// reject 를 해야하는 시점

			// FSM 시작하다 에러나면 -> 걍 노드 삭제(만약을 위해 타이머만 클린업)
			if ((fsm = node->fsm = ItsIso14827ServerDomainSubscriptionFSM_new(server, client, node, errp)) == NULL) { ERR_OUT(errp); Dz1Error_set(errp, 0); }
			else if ((err = _fsm_subscription_check(node, sub)).code) ERR_OUT(errp);
			else if ((err = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(errp);
			else
			{	// Application 에 각 요청을 알림... Accept/Reject 는 Application 이 되돌려 주는 값으로...
				u32_t serial = node->serial;
				Iso14827SubscriptionData *data = node->data;
				fsm->state = ItsIso14827SubscriptionState_waitAddConfirm;
				node = NULL;
				Dz1Error_set(errp, 0);

				_subscriptionCallback(client, server->name, serial, data);
			}
			pthread_cleanup_pop(errp->code); // (ItsIso14827SubscriptionEntry_expire, (void *)&_arg);
			pthread_cleanup_pop(1); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
		}
	}
	else
	{
		Dz1FsmReturn ret = Dz1FsmReturn_continue;
		ItsIso14827SubscriptionMsg _msg = { session, authInfo, priority, pktNbr, pdu, isRetried }, *msg = &_msg;
		pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
		// State 를 돌다가 에러나면 ?
		switch((ret = Dz1Fsm2_proc(node->fsm, uArg, uRsc, timer, (void **)&msg, errp)))
		{
		case Dz1FsmReturn_continue:
			if ((err = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(errp);
			else { node = NULL; Dz1Error_set(errp, 0); }
			break;
		default:
		case Dz1FsmReturn_error:
			ERR_OUT(errp);
		case Dz1FsmReturn_terminate:
			break;
		}
		pthread_cleanup_pop(1); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// User Confirm : Accept
Dz1Error ItsIso14827ServerDomainClientEntrySubscription_accept(ItsIso14827ServerDomainClientEntry *client,
															   Dz1Asn1UTF8Str *domainName,
															   ItsIso14827SessionEntry *session,
															   u32_t serial, void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SubscriptionEntry key = { serial }, *node = client->subscriptions->extract(client->subscriptions, &key);
	if (node == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		//Dz1FsmReturn ret = Dz1FsmReturn_continue;
		ItsIso14827SubscriptionMsg _msg = { session, NULL, 1, 0, NULL, FALSE }, *msg = &_msg;
		pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);

		switch(Dz1Fsm2_proc2(node->fsm, uArg, uRsc, timer, ItsIso14827SubscriptionEvent_accept, (void **)&msg, &err))
		{
		case Dz1FsmReturn_continue:
			if ((err = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(&err);
			else { node = NULL; Dz1Error_set(&err, 0); }
			break;
		default:
		case Dz1FsmReturn_error:
			ERR_OUT(&err);
		case Dz1FsmReturn_terminate:
			break;
		}

		pthread_cleanup_pop(1); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// User Confirm : Reject
Dz1Error ItsIso14827ServerDomainClientEntrySubscription_reject(ItsIso14827ServerDomainClientEntry *client,
															   Dz1Asn1UTF8Str *domainName,
															   ItsIso14827SessionEntry *session,
															   u32_t serial, Iso14827RejectSubscription reason,
															   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SubscriptionEntry key = { serial }, *node = client->subscriptions->extract(client->subscriptions, &key);
	if (node == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		Dz1FsmReturn ret = Dz1FsmReturn_continue;
		ItsIso14827SubscriptionMsg _msg = { session, NULL, 1, 0, NULL, FALSE, reason }, *msg = &_msg;
		SubscriptionTimerCleanupArg _arg = { client, domainName, node, timer };

		pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
		pthread_cleanup_push(_ItsIso14827SubscriptionEntry_timerCleanup, (void *)&_arg);
		switch(Dz1Fsm2_proc2(node->fsm, uArg, uRsc, timer, ItsIso14827SubscriptionEvent_reject, (void **)&msg, &err))
		{
		case Dz1FsmReturn_continue:
			if ((err = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(&err);
			else node = NULL;
			break;
		default:
		case Dz1FsmReturn_error:
			ERR_OUT(&err);
		case Dz1FsmReturn_terminate:
			break;
		}
		pthread_cleanup_pop(ret != Dz1FsmReturn_continue); // (_ItsIso14827SubscriptionEntry_timerCleanup, (void *)&_arg);
		pthread_cleanup_pop(1); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// User API : Publication
Dz1Error ItsIso14827ServerDomainClientEntrySubscription_publication(ItsIso14827ServerDomainClientEntry *client,
																	Dz1Asn1UTF8Str *domainName,
																	ItsIso14827SessionEntry *session,
																	u32_t serial, Iso14827EndAppMsg **eam,
																	void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SubscriptionEntry key = { serial }, *node = client->subscriptions->extract(client->subscriptions, &key);
	if (node == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		//Dz1FsmReturn ret = Dz1FsmReturn_continue;
		//Iso14827SubscriptionData *data = node->data;
/*
typedef struct ItsIso14827SubscriptionMsg
{
	ItsIso14827SessionEntry		*session;

	Dz1Asn1OctetStr				*authInfo;
	s32_t						 priority;
	u32_t						 pktNbr;
	Iso14827PDUs				*pdu;
	bool_t						 isRetried;
	Iso14827RejectSubscription	 reason;
	Iso14827PublicationType		*pubType;
} ItsIso14827SubscriptionMsg;
*/
		ItsIso14827SubscriptionMsg _msg = { session, NULL, 1, 0, NULL, FALSE, Iso14827RejectSubscription_other, NULL }, *msg = &_msg;

		Iso14827PublicationType *type = NULL;
		pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
		if ((_msg.pubType = type = Iso14827PublicationType_new(Iso14827PublicationTypePresent_msg, (void *)(*eam), &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1FsmReturn ret = Dz1FsmReturn_continue;

			(*eam) = NULL;
			pthread_cleanup_push(Iso14827PublicationType_delAndSetNull, (void *)&_msg.pubType);

			switch((ret = Dz1Fsm2_proc2(node->fsm, uArg, uRsc, timer, ItsIso14827SubscriptionEvent_publication, (void **)&msg, &err)))
			{
			case Dz1FsmReturn_continue:
				if ((err = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(&err);
				else node = NULL;
				break;
			default:
			case Dz1FsmReturn_error:
				ERR_OUT(&err);
			case Dz1FsmReturn_terminate:
				break;
			}
			pthread_cleanup_pop(1); // (Iso14827PublicationType_delAndSetNull, (void *)&_msg.pubType);
		}
		pthread_cleanup_pop(1); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// User API : Publication Control
/*
static bool_t _pubControlIsTerminate(Iso14827PublicationMgmt v)
{
	if (v == Iso14827PublicationMgmt_temporarilySuspended ||
		v == Iso14827PublicationMgmt_resume) return FALSE;
	return TRUE;
}
*/
Dz1Error ItsIso14827ServerDomainClientEntrySubscription_pubControl(ItsIso14827ServerDomainClientEntry *client,
																   Dz1Asn1UTF8Str *domainName,
																   ItsIso14827SessionEntry *session,
																   u32_t serial, Iso14827PublicationMgmt cmd,
																   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SubscriptionEntry key = { serial }, *node = client->subscriptions->extract(client->subscriptions, &key);
	if (node == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		//Dz1FsmReturn ret = Dz1FsmReturn_continue;
		//Iso14827SubscriptionData *data = node->data;
		ItsIso14827SubscriptionMsg _msg = { session, NULL, 1, 0, NULL, FALSE, Iso14827RejectSubscription_other, NULL }, *msg = &_msg;

		Iso14827PublicationType *type = NULL;
		pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
		if ((_msg.pubType = type = Iso14827PublicationType_new(Iso14827PublicationTypePresent_mgmt, (void *)&cmd, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1FsmReturn ret = Dz1FsmReturn_continue;
			pthread_cleanup_push(Iso14827PublicationType_delAndSetNull, (void *)&_msg.pubType);

			switch((ret = Dz1Fsm2_proc2(node->fsm, uArg, uRsc, timer, ItsIso14827SubscriptionEvent_publication, (void **)&msg, &err)))
			{
			case Dz1FsmReturn_continue:
				if ((err = client->subscriptions->add(client->subscriptions, node)).code) ERR_OUT(&err);
				else node = NULL;
				break;
			default:
			case Dz1FsmReturn_error:
				ERR_OUT(&err);
			case Dz1FsmReturn_terminate:
				break;
			}
			pthread_cleanup_pop(1); // (Iso14827PublicationType_delAndSetNull, (void *)&_msg.pubType);
		}
		pthread_cleanup_pop(1); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error _clientDisconnected(void *ptr, ItsIso14827SubscriptionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SubscriptionEntryCleanupArg *arg = (ItsIso14827SubscriptionEntryCleanupArg *)ptr;
	ItsIso14827ServerDomainClientEntry *client = arg->client;
	ItsIso14827ServerDomainCallback *cbs = client->cb; 
	ItsIso14827SubscriptionEntry *node = p;
	ItsIso14827SubscriptionEntry_timerCleanup(client, arg->domainName, node, arg->timer);
	if (node->isActive)
	{	// 활성된 Subscription
		if (cbs->stopped) cbs->stopped(cbs->param, arg->domainName, client->peer, client->user, node->serial);
	}
	if (cbs->expired)
	{
		ItsIso14827SubscriptionExpireReason reason = { ItsIso14827SubscriptionExpireReasonPresent_clientDisconnected, { NULL } };
		cbs->expired(cbs->param, arg->domainName, client->peer, client->user, node->serial, &reason);
	}
	return err;
}

void ItsIso14827ServerDomainClientEntrySubscription_disconnected(ItsIso14827ServerDomainClientEntry *client,
																 Dz1Asn1UTF8Str *domainName, void *timer)
{
	ItsIso14827SubscriptionEntryCleanupArg _arg = { timer, client, domainName, NULL, NULL, NULL, NULL, 0 };
	client->subscriptions->travel(client->subscriptions, _clientDisconnected, (void *)&_arg);
}
