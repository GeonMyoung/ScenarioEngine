#include <dz1_gasn_support.h>

#include "ItsIso14827Env.h"
#include "ItsIso14827TimerUtil.h"
#include "ItsIso14827SessionMgr_main.h"
#include "ItsIso14827Domain_send.h"
#include "ItsIso14827DomainMsg.h"
#include "ItsIso14827DomainMgr_main.h"
#include "ItsIso14827ClientDomain_main.h"
#include "ItsIso14827ClientDomain_send.h"

///////////////////////////////////////////////////////////////////////////////
// Extract
///////////////////////////////////////////////////////////////////////////////
ItsIso14827ClientDomainServerEntry *ItsIso14827ClientDomain_extractServerByPeerUser(ItsIso14827ClientDomain *domain,
																 Dz1Asn1UTF8Str *server, Dz1Asn1OctetStr *user)
{
	ItsIso14827ClientDomainServerEntry key = { server, user }, *ret = domain->servers->extract(domain->servers, &key);
	if (ret) domain->sessions->extract(domain->sessions, (ItsIso14827ClientDomainSessionEntry *)ret);
	return ret;
}

static ItsIso14827ClientDomainServerEntry *_extractServerBySession(ItsIso14827ClientDomain *domain, ItsIso14827SessionKey *skey)
{
	ItsIso14827ClientDomainSessionEntry key = { NULL, NULL, skey }, *ret = domain->sessions->extract(domain->sessions, &key);
	if (ret) domain->servers->extract(domain->servers, (ItsIso14827ClientDomainServerEntry *)ret);
	return (ItsIso14827ClientDomainServerEntry *)ret;
}

///////////////////////////////////////////////////////////////////////////////
// Find
///////////////////////////////////////////////////////////////////////////////
ItsIso14827ClientDomainServerEntry *ItsIso14827ClientDomain_findServerByPeerUser(ItsIso14827ClientDomain *domain,
																 Dz1Asn1UTF8Str *server, Dz1Asn1OctetStr *user)
{
	ItsIso14827ClientDomainServerEntry key = { server, user };
	return domain->servers->find(domain->servers, &key);
}
/*
static ItsIso14827ClientDomainServerEntry *_findServerBySession(ItsIso14827ClientDomain *domain, ItsIso14827SessionKey *skey)
{
	ItsIso14827ClientDomainSessionEntry key = { NULL, NULL, skey };
	return (ItsIso14827ClientDomainServerEntry *)domain->sessions->find(domain->sessions, &key);
}
*/
///////////////////////////////////////////////////////////////////////////////
// Heart Beat Period Timeout
///////////////////////////////////////////////////////////////////////////////
Dz1TaskProcStatus ItsIso14827ClientDomainMgr_heartBeatPeriodTimeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827Timer *tmr = (ItsIso14827Timer *)(*tData);
	ItsIso14827DomainTimer *dTmr = tmr->x.domain;

	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, dTmr->key);
	if (domain)
	{
		ItsIso14827ClientDomain *client = domain->x.client;
		ItsIso14827ClientDomainServerEntry *server = ItsIso14827ClientDomain_findServerByPeerUser(client, dTmr->peer, dTmr->user);
		if (server)
		{
			ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, server->key);
			if (session)
			{
				if ((server->ctrl_flags & ItsIso14827ClientCtrlFlag_HeartBeatOFF) == 0)
					ItsIso14827ClientDomainServerEntry_sendFrED(server, session, client->name, 0, NULL, client->hdr_opt_flag, uArg, uRsc, timer);
				else Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "ItsIso14827ClientDomainMgr_heartBeatPeriodTimeout() : HeartBeat is disabled\n");
			}
		}
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Timer Cleanup
///////////////////////////////////////////////////////////////////////////////
static void ItsIso14827ClientDomainServerEntry_timerCleanup(ItsIso14827ClientDomainServerEntry *server,
															Dz1Asn1UTF8Str *domainName, void *timer)
{
	ItsIso14827DomainTimer_dereg(timer, ItsIso14827DomainType_client, domainName,
								server->peer, server->user, DOMAIN_RETRANSMIT_TIMER);
	ItsIso14827DomainTimer_dereg(timer, ItsIso14827DomainType_client, domainName,
								server->peer, server->user, DOMAIN_HEARTBEAT_PERIOD_TIMER);
	ItsIso14827DomainTimer_dereg(timer, ItsIso14827DomainType_client, domainName,
								server->peer, server->user, DOMAIN_HEARTBEAT_DURATION_TIMER);
	if (server->state == ItsIso14827ClientDomainSessionState_established)
	{
		ItsIso14827ClientDomainCallback *cbs = server->cb;
		if (cbs->disconnected) cbs->disconnected(cbs->param, domainName, server->peer, server->user);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Timer Cleanup Helper
///////////////////////////////////////////////////////////////////////////////
typedef struct DomainTimerCleanupArg
{
	ItsIso14827ClientDomainServerEntry *server;
	Dz1Asn1UTF8Str *domainName;
	void *timer;
} DomainTimerCleanupArg;

static void _ItsIso14827ClientDomainServerEntry_timerCleanup(void *ptr)
{
	DomainTimerCleanupArg *arg = (DomainTimerCleanupArg *)ptr;
	ItsIso14827ClientDomainServerEntry *server = arg->server;
	if (server->userWait != NULL)
	{
		Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);
		Dz1Error_set(status, EINTR);
		Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);
		server->userWaitState = ItsIso14827ClientDomainWaitState_none;
	}
	ItsIso14827ClientDomainServerEntry_timerCleanup(arg->server, arg->domainName, arg->timer);
}

///////////////////////////////////////////////////////////////////////////////
// _registerServerEntry 도중 등록 실패 시 Cleanup
///////////////////////////////////////////////////////////////////////////////
typedef struct ServerAddCancelArg
{
	ItsIso14827ClientDomainServerList *list;
	ItsIso14827ClientDomainServerEntry *entry;
} ServerAddCancelArg;

static void _serverAddCancel(void *ptr)
{
	ServerAddCancelArg *arg = (ServerAddCancelArg *)ptr;
	arg->list->extract(arg->list, arg->entry);
}

///////////////////////////////////////////////////////////////////////////////
// Server Entry 등록
///////////////////////////////////////////////////////////////////////////////
static Dz1Error _registerServerEntry(ItsIso14827ClientDomain *domain, ItsIso14827ClientDomainServerEntry *server)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = domain->servers->add(domain->servers, server)).code) ERR_OUT(&err);
	else
	{
		ServerAddCancelArg _arg = { domain->servers, server };
		pthread_cleanup_push(_serverAddCancel, (void *)&_arg);

		if ((err = domain->sessions->add(domain->sessions, (ItsIso14827ClientDomainSessionEntry *)server)).code) ERR_OUT(&err);

		pthread_cleanup_pop(err.code); // (_serverAddCancel, (void *)&_arg);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Packet 전송 실패 시 호출되는 Callback
///////////////////////////////////////////////////////////////////////////////
static void _cleanup_subscription(ItsIso14827ClientDomainServerEntry *server, u32_t serial)
{
	ItsIso14827SubscribeEntry key = { serial }, *node = server->subscribes->extract(server->subscribes, &key);
	if (node)
	{
		pthread_cleanup_push(ItsIso14827SubscribeEntry_delAndSetNull, (void *)&node);
		Dz1Thread_printf("_cleanup_subscription() = ");
		ItsIso14827SubscribeEntry_dump(node, 0);
		pthread_cleanup_pop(1); // (ItsIso14827SubscribeEntry_delAndSetNull, (void *)&node);
	}
}

ItsIso14827SessionKey *ItsIso14827ClientDomain_sendFail(ItsIso14827ClientDomain *domain,
														Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														Iso14827C2CAuthMsg *c2c, void *uArg, void *uRsc, void *timer)
{
	ItsIso14827SessionKey *ret = NULL;
	ItsIso14827ClientDomainServerEntry *server = ItsIso14827ClientDomain_findServerByPeerUser(domain, peer, user);
	if (server && server->userWait)
	{
		Iso14827PDUs *pdu = c2c->pdu;

		Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);

/*
	Iso14827PDUsPresent_initiate,		// 보낼일 없음
	Iso14827PDUsPresent_login,			// !
	Iso14827PDUsPresent_fred,			// 전송 확인 하지 않음
	Iso14827PDUsPresent_term,			// 보낼일 없음
	Iso14827PDUsPresent_logout,			// !
	Iso14827PDUsPresent_subscription,	// !
	Iso14827PDUsPresent_publication,	// Embedded Server인 경우
	Iso14827PDUsPresent_transferDone,	// ! 다른 전송방식 지원 안함 -> 보낼일 없음
	Iso14827PDUsPresent_ack,			// 전송 확인 하지 않음
	Iso14827PDUsPresent_nak,			// 전송 확인 하지 않음
*/
		switch(pdu->present)
		{
		case Iso14827PDUsPresent_login:	// Login전송 시 실패 했다.
			if (server->userWaitState == ItsIso14827ClientDomainWaitState_loginResultWait)
			{
				ERR_SET_OUT(status, ETIMEDOUT);							// Application에게 Timeout 알림
				Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);		// 대기중인 Application을 깨움
				server->userWaitState = ItsIso14827ClientDomainWaitState_none;
				ItsIso14827ClientDomain_extractServerByPeerUser(domain, peer, user);	// server entry를 짤라낸다.
				ret = server->key; server->key = NULL;			// Sessin Key를 돌려준다
				ItsIso14827ClientDomainServerEntry_timerCleanup(server, domain->name, timer);
				ItsIso14827ClientDomainServerEntry_del(server);
			}
			break;
		case Iso14827PDUsPresent_logout: // Logout전송 시 실패 했다.
			if (server->userWaitState == ItsIso14827ClientDomainWaitState_logoutResultWait)
			{
				Dz1Error_set(status, 0);								// 어찌되었은 성공~
				Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);		// 대기중인 Application을 깨움
				server->userWaitState = ItsIso14827ClientDomainWaitState_none;

				ItsIso14827ClientDomain_extractServerByPeerUser(domain, peer, user);	// server entry를 짤라낸다.
				ret = server->key; server->key = NULL;			// Sessin Key를 돌려준다
				ItsIso14827ClientDomainServerEntry_timerCleanup(server, domain->name, timer);
				ItsIso14827ClientDomainServerEntry_del(server);
			}
			break;
		case Iso14827PDUsPresent_subscription: // Subscription 전송 시 실패 했다.
			if (server->userWaitState == ItsIso14827ClientDomainWaitState_singleSubscriptionResultWait ||
				server->userWaitState == ItsIso14827ClientDomainWaitState_registeredSubscriptionResultWait)
			{
				ERR_SET_OUT(status, ETIMEDOUT);							// Application에게 Timeout 알림
				Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);		// 대기중인 Application을 깨움
				_cleanup_subscription(server, pdu->x.subscription->serial);
				server->userWaitState = ItsIso14827ClientDomainWaitState_none;
			}
			else if (server->userWaitState == ItsIso14827ClientDomainWaitState_subscriptionCancelResultWait)
			{
				Dz1Error_set(status, 0);								// 어쨋든 성공
				Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);		// 대기중인 Application을 깨움
				_cleanup_subscription(server, pdu->x.subscription->serial);
				server->userWaitState = ItsIso14827ClientDomainWaitState_none;
			}
			break;
		case Iso14827PDUsPresent_publication:	// Embedded Server인 경우에
			break;
		case Iso14827PDUsPresent_transferDone:
			break;
		default:
			break;
		}
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// 서버에 접속
///////////////////////////////////////////////////////////////////////////////
#define	SUBSCRIPBE_ALLOCID_START	1
Dz1Error ItsISo14827Clientdomain_connectToServer(ItsIso14827ClientDomain *domain, ItsIso14827SessionEntry *session,
												 Dz1Asn1OctetStr *authInfo, Iso14827Login **login, 
												 ItsIso14827ClientDomainViolatedSubscription **violatedSub, Dz1TaskSigMsg **sg,
												 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	// user@SERVER로 존재 유무를 찾는다.
	ItsIso14827ClientDomainServerEntry *server = ItsIso14827ClientDomain_findServerByPeerUser(domain, (*login)->dest, (*login)->user);
	// 이미 있으면 에러!!
	if (server != NULL) ERR_SET_OUT(&err, EEXIST);
	// 서버 엔트리를 만든다.
	else if ((server = ItsIso14827ClientDomainServerEntry_new(NULL, NULL, NULL, SUBSCRIPBE_ALLOCID_START,
															NULL, (*login)->hbDur, (*login)->timeout,
															domain->callback, (*violatedSub), &err)) == NULL) ERR_OUT(&err);
	else
	{
		(*violatedSub) = NULL;
		pthread_cleanup_push(ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&server);
		// 서버 이름
		if ((server->peer = Dz1Asn1UTF8Str_clone((*login)->dest, &err)) == NULL) ERR_OUT(&err);
		// 사용자
		else if ((server->user = Dz1Asn1OctetStr_clone((*login)->user, &err)) == NULL) ERR_OUT(&err);
		// Session Key
		else if ((server->key = ItsIso14827SessionKey_clone(session->key, &err)) == NULL) ERR_OUT(&err);
		// TxFIFO
		else if ((server->txFifo = ItsIso14827DomainTxFifo_new(&err)) == NULL) ERR_OUT(&err);
		// Login Message 전송
		else if ((err = ItsIso14827ClientDomainServerEntry_sendLogin(server, session, domain->name, authInfo, login, domain->hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(&err);
		// 서버 등록 -> servers와 sessions에 동시에 등록
		else if ((err = _registerServerEntry(domain, server)).code) ERR_OUT(&err);
		else
		{
			ItsIso14827SessionTimer_dereg(timer, session->key, SESSION_ALIVE_TIMER);
			server->userWaitState = ItsIso14827ClientDomainWaitState_loginResultWait;
			server->userWait = (*sg); (*sg) = NULL;
			Dz1Thread_printf("@@@ USER WAIT = %p\n", server->userWait);
			server = NULL;
		}
		pthread_cleanup_pop(1); // (ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&server);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// 접속 종료
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ClientDomain_disconnectFromServer(ItsIso14827ClientDomain *domain,
													  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
													  Iso14827Logout reason, Dz1TaskSigMsg **sg,
													  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	// user@SERVER로 존재 유무를 찾는다.
	ItsIso14827ClientDomainServerEntry *server = ItsIso14827ClientDomain_extractServerByPeerUser(domain, peer, user);
	if (server == NULL) ERR_SET_OUT(&err, ENOENT);
	else if (server->userWait != NULL) ERR_SET_OUT(&err, EAGAIN);
	else
	{
		ItsIso14827SessionEntry *session = NULL;
		DomainTimerCleanupArg _arg = { server, domain->name, timer };
		pthread_cleanup_push(ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&server);

		pthread_cleanup_push(_ItsIso14827ClientDomainServerEntry_timerCleanup, (void *)&_arg);

		if ((session = ItsIso14827SessionMgr_find(env->sessionMgr, server->key)) == NULL) ERR_SET_OUT(&err, ENOENT);
		else if ((err = ItsIso14827ClientDomainServerEntry_sendLogout(server, session, domain->name,
																	  reason, domain->hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(&err);
		else if ((err = _registerServerEntry(domain, server)).code) ERR_OUT(&err);
		else
		{
			server->state = ItsIso14827ClientDomainSessionState_pending;
			server->userWaitState = ItsIso14827ClientDomainWaitState_logoutResultWait;
			server->userWait = (*sg); (*sg) = NULL;
			server = NULL;
		}
		pthread_cleanup_pop(err.code); // (_ItsIso14827ClientDomainServerEntry_timerCleanup, (void *)&_arg);

		pthread_cleanup_pop(1); // (ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&server);
	}
	return err;
}

typedef struct DomainClientUserActionCancel
{
	bool_t cleanEntry;
	ItsIso14827ClientDomain *domain;
	ItsIso14827ClientDomainServerEntry *server;
	void *timer;
} DomainClientUserActionCancel;

static void domainClientUserActionCancel(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	DomainClientUserActionCancel *arg = (DomainClientUserActionCancel *)ptr;
	ItsIso14827ClientDomain *domain = arg->domain;
	ItsIso14827ClientDomainServerEntry *server = arg->server;
	if (arg->cleanEntry == TRUE || (err = _registerServerEntry(domain, server)).code != 0)
	{
		if (server->userWait != NULL)
		{
			Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);
			Dz1Error_set(status, EINTR);
			Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);
			server->userWaitState = ItsIso14827ClientDomainWaitState_none;
		}
		ItsIso14827ClientDomainServerEntry_timerCleanup(arg->server, domain->name, arg->timer);
		ItsIso14827ClientDomainServerEntry_del(arg->server);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Subscription 전송
///////////////////////////////////////////////////////////////////////////////
static ItsIso14827SubscribeEntry *_registerSubscripbe(ItsIso14827ClientDomainServerEntry *server, Iso14827SubscriptionData *data, Dz1Error *errp)
{
	ItsIso14827SubscribeEntry *ret = NULL;
	ItsIso14827SubscribeEntry *e = NULL;
	
	if (server->subscribeAlloc == 0) server->subscribeAlloc = 1;	// subscription serial 0 is reserved

	if ((e = ItsIso14827SubscribeEntry_new(server->subscribeAlloc++, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827SubscribeEntry_delAndSetNull, (void *)&e);
		if ((e->data = Iso14827SubscriptionData_clone(data, errp)) == NULL) ERR_OUT(errp);
		else
		{
			while (server->subscribes->find(server->subscribes, e) != NULL)
			{
				if (server->subscribeAlloc == 0) server->subscribeAlloc = 1;
				e->serial = server->subscribeAlloc++;
			}

			if ((*errp = server->subscribes->add(server->subscribes, e)).code) ERR_OUT(errp);
			else
			{
				ret = e;
				e = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (ItsIso14827SubscribeEntry_delAndSetNull, (void *)&e);
	}
	return ret;
}

Dz1Error ItsIso14827ClientDomain_subscription(ItsIso14827ClientDomain *domain,
											  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
											  Iso14827SubscriptionData **data, Dz1TaskSigMsg **sg,
											  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	// user@SERVER로 존재 유무를 찾는다.
	ItsIso14827ClientDomainServerEntry *server = ItsIso14827ClientDomain_extractServerByPeerUser(domain, peer, user);
	if (server == NULL)
	{
//		Dz1Thread_printf("Peer = "); Dz1Asn1UTF8Str_dump(peer, 0);
//		Dz1Thread_printf("User = "); Dz1Asn1OctetStr_dump(user, 0);
//		Dz1Thread_printf("Current Sessions = ");
//		ItsIso14827ClientDomain_dump(domain, 0);
		ERR_SET_OUT(&err, ENOENT);
	}
	else
	{
		DomainClientUserActionCancel _arg = { FALSE, domain, server, timer };
		pthread_cleanup_push(domainClientUserActionCancel, (void *)&_arg);
		if (server->userWait != NULL) ERR_SET_OUT(&err, EAGAIN);
		else
		{
			ItsIso14827SubscribeEntry *sub = NULL;
			ItsIso14827SessionEntry *session = NULL;
			Iso14827SubscriptionData *temp = (*data);
			Iso14827SubscriptionDataMode *mode = temp->mode;

			if ((session = ItsIso14827SessionMgr_find(env->sessionMgr, server->key)) == NULL) ERR_SET_OUT(&err, ENOENT);
			else if ((sub = _registerSubscripbe(server, *data, &err)) == NULL) ERR_OUT(&err);
			else if ((err = ItsIso14827ClientDomainServerEntry_sendSubscriptionData(server, session, domain->name, 
																					sub->serial, *data,
																					domain->hdr_opt_flag,
																					uArg, uRsc, timer)).code)
			{
				_arg.cleanEntry = TRUE;
				ERR_OUT(&err);
			}
			else
			{
				ItsIso14827ClientDomainWaitState state = mode->present == Iso14827SubscriptionDataModePresent_single ?
																ItsIso14827ClientDomainWaitState_singleSubscriptionResultWait : 
																ItsIso14827ClientDomainWaitState_registeredSubscriptionResultWait;
				server->userWaitState = state;
				server->userWait = (*sg); (*sg) = NULL;
				server = NULL;
			}
		}
		pthread_cleanup_pop(1); // (domainClientUserActionCancel, (void *)&_arg);
	}
	return err;
}

Dz1Error ItsIso14827ClientDomain_violatedPub(ItsIso14827ClientDomain *domain, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
											 Iso14827Publication **pub, void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ClientDomainServerEntry key = { peer, user }, *server = domain->servers->find(domain->servers, &key);
	if (server == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		Iso14827PDUs *pdu = NULL;
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, server->key);
		if (session == NULL) ERR_SET_OUT(&err, EPIPE);
		else if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_publication, (*pub), &err)) == NULL) ERR_OUT(&err);
		else
		{
			(*pub) = NULL;
			pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
			if ((err = ItsIso14827Domain_send(server->txFifo, session, ItsIso14827DomainType_client, domain->hdr_opt_flag, domain->name,
											  server->peer, server->user, NULL, server->responseWaitTime, server->heartBeadPeriod,
											  1, &pdu, FALSE, NULL, uArg, uRsc, timer)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Subscription 취소
///////////////////////////////////////////////////////////////////////////////
static bool_t _isExistSubscription(ItsIso14827ClientDomainServerEntry *server, u32_t serial)
{
	ItsIso14827SubscribeEntry key = { serial };
	if (server->subscribes->find(server->subscribes, &key)) return TRUE;
	else return FALSE;
}

Dz1Error ItsIso14827ClientDomain_subCancel(ItsIso14827ClientDomain *domain,
										   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
										   u32_t serial, Iso14827SubscriptionCancel reason,
										   Dz1TaskSigMsg **sg, void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	// user@SERVER로 존재 유무를 찾는다.
	ItsIso14827ClientDomainServerEntry *server = ItsIso14827ClientDomain_extractServerByPeerUser(domain, peer, user);
	if (server == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		DomainClientUserActionCancel _arg = { FALSE, domain, server, timer };
		pthread_cleanup_push(domainClientUserActionCancel, (void *)&_arg);
		if (server->userWait != NULL) ERR_SET_OUT(&err, EAGAIN);
		else
		{
			ItsIso14827SessionEntry *session = NULL;
			if ((session = ItsIso14827SessionMgr_find(env->sessionMgr, server->key)) == NULL) ERR_SET_OUT(&err, ENOENT);
			else if (_isExistSubscription(server, serial) == FALSE)
			{
				ERR_SET_OUT(&err, ENOENT);
			}
			else if ((err = ItsIso14827ClientDomainServerEntry_sendSubscriptionCancel(server, session, domain->name, 
																					  serial, reason, domain->hdr_opt_flag,
																					  uArg, uRsc, timer)).code)
			{
				_arg.cleanEntry = TRUE;
				ERR_OUT(&err);
			}
			else
			{
				server->userWaitState = ItsIso14827ClientDomainWaitState_subscriptionCancelResultWait;
				server->userWait = (*sg); (*sg) = NULL;
				server = NULL;
			}
		}
		pthread_cleanup_pop(1); // (domainClientUserActionCancel, (void *)&_arg);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publication Data Reject
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ClientDomain_rejectPubData(ItsIso14827ClientDomain *domain,
											   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
											   u32_t serial, u32_t pubSerial, Iso14827RejectPubDataReason reason,
											   Dz1TaskSigMsg **sg, void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	// user@SERVER로 존재 유무를 찾는다.
	ItsIso14827ClientDomainServerEntry *server = ItsIso14827ClientDomain_extractServerByPeerUser(domain, peer, user);
	if (server == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		DomainClientUserActionCancel _arg = { FALSE, domain, server, timer };
		pthread_cleanup_push(domainClientUserActionCancel, (void *)&_arg);
		if (server->userWait != NULL) ERR_SET_OUT(&err, EAGAIN);
		else
		{
			//ItsIso14827SubscribeEntry *sub = NULL;
			ItsIso14827SessionEntry *session = NULL;
			if ((session = ItsIso14827SessionMgr_find(env->sessionMgr, server->key)) == NULL) ERR_SET_OUT(&err, ENOENT);
			else if (_isExistSubscription(server, serial) == FALSE) ERR_SET_OUT(&err, ENOENT);
			else if ((err = ItsIso14827ClientDomainServerEntry_sendRejectPubData(server, session, domain->name, 
																				 serial, pubSerial, reason, domain->hdr_opt_flag,
																				 uArg, uRsc, timer)).code)
			{
				_arg.cleanEntry = TRUE;
				ERR_OUT(&err);
			}
			else server = NULL;
		}
		pthread_cleanup_pop(1); // (domainClientUserActionCancel, (void *)&_arg);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Initiate를 수신한 경우
///////////////////////////////////////////////////////////////////////////////
/*
*/
///////////////////////////////////////////////////////////////////////////////
// Terminate를 수신한 경우
///////////////////////////////////////////////////////////////////////////////
static Dz1Error client_receiveTerminated(ItsIso14827ClientDomainServerEntry *server,
										 Dz1Asn1UTF8Str *domainName,
										 Iso14827Terminate reason, ItsIso14827SessionEntry *session,
										 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ItsIso14827ClientDomainCallback *cbs = server->cb;
	if (cbs->terminate) cbs->terminate(cbs->param, domainName, server->peer, server->user, reason);

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// FrED를 수신한 경우
///////////////////////////////////////////////////////////////////////////////
static Dz1Error client_receiveFrED(ItsIso14827ClientDomainServerEntry *server,
									 ItsIso14827ClientDomain *domain,
									 ItsIso14827SessionEntry *session,
									 Iso14827PDUs *pdu,
									 u32_t hdr_opt_flag,
									 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ItsIso14827ClientDomainCallback *cb = domain->callback;
	u32_t cnfPktNbr = pdu->x.fred;
	Iso14827C2CAuthMsg *sent = NULL;
	// HeratBeatPeriod가 되어 FrED(0)를 전송한 경우 -> 대기하고 있는것이 없을 것이니 sent 가 NULL이 됨
	if ((err = ItsIso14827Domain_confirm(server->txFifo, session, ItsIso14827DomainType_client, hdr_opt_flag,
										domain->name, server->peer, server->user, server->responseWaitTime,
										cnfPktNbr, &sent, uArg, uRsc, timer)).code) ERR_OUT(&err);
	else if (sent != NULL)
	{
		Iso14827PDUs *sentPDU = sent->pdu;
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&sent);

		switch(sentPDU->present)
		{
		case Iso14827PDUsPresent_logout:
			// Logout을 보낸 경우 -> userWait을 깨우고 Error를 유발하여 이 세션 종료
			if (server->userWait != NULL && server->userWaitState == ItsIso14827ClientDomainWaitState_logoutResultWait)
			{
				Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);
				Dz1Error_set(status, 0);
				Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);
				server->userWaitState = ItsIso14827ClientDomainWaitState_none;
				// Error를 지정하여 이 세션을 정리한다
				if (cb != NULL && cb->disconnected != NULL)
					cb->disconnected(cb->param, domain->name, server->peer, server->user);
				Dz1Error_set(&err, EPIPE);
			}
			break;
		case Iso14827PDUsPresent_transferDone:
			// Transfer-Done을 보낸 경우 -> 지금은 보낼 일이 없다 -> 보냈다면 txFIFO에서 Confirm을 기다리는 중일 것임으로
			// 위에서 해결
			// NOP
			break;
		default:
			break;
		}
		pthread_cleanup_pop(1); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&sent);
	}
	// Heartbeat에 대한 응답을 수신
	else if (cb != NULL && cb->echo_responsed) cb->echo_responsed(cb->param, domain->name, server->peer, server->user);

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Accept를 수신한 경우
///////////////////////////////////////////////////////////////////////////////
static Dz1Error client_receiveAccept(ItsIso14827ClientDomainServerEntry *server,
									 Dz1Asn1UTF8Str *domainName,
									 ItsIso14827SessionEntry *session,
									 Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
									 Iso14827PDUs *pdu, bool_t isRetried,
									 u32_t hdr_opt_flag,
									 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827Accept *ack = pdu->x.ack;
	Iso14827C2CAuthMsg *sent = NULL;
	if ((err = ItsIso14827Domain_confirm(server->txFifo, session, ItsIso14827DomainType_client, hdr_opt_flag,
										domainName, server->peer, server->user, server->responseWaitTime,
										ack->pktNbr, &sent, uArg, uRsc, timer)).code) ERR_OUT(&err);
	else if (sent == NULL)
	{
		Dz1Thread_printf("@@@ Unknown ACK...\n");
	}
	else
	{
		Iso14827PDUs *sentPDU = sent->pdu;
		Iso14827AcceptType *type = ack->acceptType;
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&sent);
		switch(type->present)
		{
		case Iso14827AcceptTypePresent_login:
			if (server->userWaitState == ItsIso14827ClientDomainWaitState_loginResultWait)
			{
//				Iso14827Login *login = sentPdu->x.login;
				Dz1Thread_printf("@@@ USER WAIT = %p\n", server->userWait);
//				Dz1SocketBuf_expand(session->buf, login->datagramSize);				// no need to ElasticBuf
				if (server->userWait != NULL)
				{
					Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);

					Dz1Asn1OID *oid = type->x.login;
					Dz1Asn1Codec codec = Dz1GASN_oid2Codec(oid);
					if (codec == Dz1Asn1Codec_unknown || codec >= Dz1Asn1Codec_max)
					{	// 모르는 코덱을 지정하면
						ERR_SET_OUT(&err, ENOSYS);		// 오류를 내서 이 세션을 끝낸다.
						Dz1Error_set(status, ENOSYS);
					}
					else
					{
						ItsIso14827DomainLogin *userMsg = (ItsIso14827DomainLogin *)Dz1TaskSigMsg_getData(server->userWait);
						userMsg->initialCodec = session->codecRule = codec;		// 코덱 지정
						Dz1Error_set(status, 0);
					}
					Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);
				}
				server->userWaitState = ItsIso14827ClientDomainWaitState_none;
				server->state = ItsIso14827ClientDomainSessionState_established;
			}
			break;
		case Iso14827AcceptTypePresent_singleSubscription:
			if (server->userWaitState == ItsIso14827ClientDomainWaitState_singleSubscriptionResultWait)
			{
				if (server->userWait != NULL)
				{
					Iso14827Subscription *sentSub = sentPDU->x.subscription;			// 보냈던 Subscription
					ItsIso14827SubscribeEntry key = { sentSub->serial };
					if (server->subscribes->find(server->subscribes, &key) != NULL)		// 정말로 있는지 확인
					{	// 정상이면 값 설정하고 Application을 깨운다.
						ItsIso14827DomainSubscription *msg = (ItsIso14827DomainSubscription *)Dz1TaskSigMsg_getData(server->userWait);
						Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);
						Dz1Error_set(status, 0);
						msg->retSerial = sentSub->serial;
						Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);
						server->userWaitState = ItsIso14827ClientDomainWaitState_none;
					}
				}
			}
			else if (server->userWaitState == ItsIso14827ClientDomainWaitState_subscriptionCancelResultWait)
			{	// don't care
				if (server->userWait != NULL)
				{
					Iso14827Subscription *sentSub = sentPDU->x.subscription;			// 보냈던 Subscription

					Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);
					Dz1Error_set(status, 0);
					Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);

					_cleanup_subscription(server, sentSub->serial);
					server->userWaitState = ItsIso14827ClientDomainWaitState_none;
				}
			}
			break;
		case Iso14827AcceptTypePresent_registeredSubscription:
			if (server->userWaitState == ItsIso14827ClientDomainWaitState_registeredSubscriptionResultWait)
			{
				if (server->userWait != NULL)
				{
					Iso14827Subscription *sentSubs = sentPDU->x.subscription;
					ItsIso14827SubscribeEntry key = { sentSubs->serial/*type->x.registeredSubscription*/ };		// 등록된 Subscription인지 확인
					if (server->subscribes->find(server->subscribes, &key) != NULL)
					{	// 있으면 값 설정하고 Application을 깨운다.
						ItsIso14827DomainSubscription *msg = (ItsIso14827DomainSubscription *)Dz1TaskSigMsg_getData(server->userWait);
						Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);

						Dz1Thread_printf("@@@ Ack to = "); ItsIso14827DomainSubscription_dump(msg, 0);
						Dz1Error_set(status, 0);
						msg->retSerial = /*type->x.registeredSubscription*/ sentSubs->serial;
						Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);
						server->userWaitState = ItsIso14827ClientDomainWaitState_none;
					}
				}
			}
			else if (server->userWaitState == ItsIso14827ClientDomainWaitState_subscriptionCancelResultWait)
			{
				if (server->userWait != NULL)
				{
					//ItsIso14827DomainSubCancel *msg = (ItsIso14827DomainSubCancel *)Dz1TaskSigMsg_getData(server->userWait);
					Iso14827Subscription *sentSubs = sentPDU->x.subscription;
					Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);
					Dz1Error_set(status, 0);
					Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);
//					_cleanup_subscription(server, type->x.registeredSubscription);
					_cleanup_subscription(server, sentSubs->serial);
					server->userWaitState = ItsIso14827ClientDomainWaitState_none;
				}
			}
			break;
		case Iso14827AcceptTypePresent_publication:
			// embedded sserver인 경우 수신 가능
			break;
		default:
			break;
		}
		pthread_cleanup_pop(1); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&sent);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject를 수신한 경우
///////////////////////////////////////////////////////////////////////////////
static Dz1Error client_receiveReject(ItsIso14827ClientDomainServerEntry *server,
									 Dz1Asn1UTF8Str *domainName,
									 ItsIso14827SessionEntry *session,
									 Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
									 Iso14827PDUs *pdu, bool_t isRetried,
									 u32_t hdr_opt_flag,
									 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827Reject *msg = pdu->x.nak;
	Iso14827C2CAuthMsg *sent = NULL;
	if ((err = ItsIso14827Domain_confirm(server->txFifo, session, ItsIso14827DomainType_client, hdr_opt_flag,
									domainName, server->peer, server->user, server->responseWaitTime,
									msg->pktNbr, &sent, uArg, uRsc, timer)).code) ERR_OUT(&err);
	else
	{
		Iso14827RejectType *type = msg->type;
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&sent);
		switch(type->present)
		{
		case Iso14827RejectTypePresent_login:
			if (server->userWaitState == ItsIso14827ClientDomainWaitState_loginResultWait)
			{
				if (server->userWait != NULL)
				{
					Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);
					ItsIso14827DomainLogin *msg = (ItsIso14827DomainLogin *)Dz1TaskSigMsg_getData(server->userWait);
					msg->reason = type->x.login;
					ERR_SET_OUT(status, EPERM);
					Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);
				}
				server->userWaitState = ItsIso14827ClientDomainWaitState_none;
			}
			Dz1Error_set(&err, EPERM);
			break;
		case Iso14827RejectTypePresent_subscription:
			if (server->userWaitState == ItsIso14827ClientDomainWaitState_singleSubscriptionResultWait ||
				server->userWaitState == ItsIso14827ClientDomainWaitState_registeredSubscriptionResultWait)
			{
				if (server->userWait != NULL)
				{
					Iso14827PDUs *sentPDU = sent->pdu;									// 보냈던 PDU
					Iso14827Subscription *sentSub = sentPDU->x.subscription;			// 보냈던 Subscription
					ItsIso14827SubscribeEntry key = { sentSub->serial };
					ItsIso14827SubscribeEntry *sub = server->subscribes->extract(server->subscribes, &key); // Subscription을 때낸다.
					if (sub)
					{	// 있으면 Application에게 오류를 알린다.
						ItsIso14827DomainSubscription *msg = (ItsIso14827DomainSubscription *)Dz1TaskSigMsg_getData(server->userWait);
						Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);
						pthread_cleanup_push(ItsIso14827SubscribeEntry_delAndSetNull, (void *)&sub);

						ERR_SET_OUT(status, EPERM);
						msg->retError = type->x.subscription;
						Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);
						server->userWaitState = ItsIso14827ClientDomainWaitState_none;

						pthread_cleanup_pop(1); // (ItsIso14827SubscribeEntry_delAndSetNull, (void *)&sub);
					}
				}
			}
			else if (server->userWaitState == ItsIso14827ClientDomainWaitState_subscriptionCancelResultWait)
			{	// 어째뜬 Cancel을 시킨다.
				if (server->userWait != NULL)
				{
					Iso14827PDUs *sentPDU = sent->pdu;									// 보냈던 PDU
					Iso14827Subscription *sentSub = sentPDU->x.subscription;			// 보냈던 Subscription

					Dz1Error *status = Dz1TaskSigMsg_getErrPtr(server->userWait);
					Dz1Error_set(status, 0);
					Dz1TaskSigMsg_termDelAndSetNull(&server->userWait);

					_cleanup_subscription(server, sentSub->serial);
					server->userWaitState = ItsIso14827ClientDomainWaitState_none;
				}
			}
			break;
		case Iso14827RejectTypePresent_publication:
			// Embedded Server인 경우엔 수신 가능
			break;
		case Iso14827RejectTypePresent_pubData:
			// Embedded Server인 경우엔 수신 가능
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}
		pthread_cleanup_pop(1); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&sent);
	}
	return err;
}

typedef struct ReceivePublicationArg
{
	ItsIso14827ClientDomainServerEntry *server;
	ItsIso14827ClientDomain *domain;
	ItsIso14827SessionEntry *session;
	bool_t is_retried;
	void *uArg;
	void *uRsc;
	void *timer;
} ReceivePublicationArg;

static int _is_pub_serial_duplicated(ItsIso14827SubscribeEntry *sub, u32_t pubSerial, Dz1Error *errp)
{
	int ret = 0;
	if (sub->pubSerial == NULL)
	{
		if ((sub->pubSerial = Dz1u32_new(pubSerial, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
	}
	else if (*sub->pubSerial == pubSerial) ret = 1;
	else *sub->pubSerial = pubSerial;
	return ret;
}

static Dz1Error _client_receivePublication(void *ptr, Iso14827PublicationData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ReceivePublicationArg *arg = (ReceivePublicationArg *)ptr;
	ItsIso14827ClientDomainServerEntry *server = arg->server;
	ItsIso14827ClientDomain *domain = arg->domain;
	ItsIso14827SessionEntry *session = arg->session;
	ItsIso14827ClientDomainCallback *cbs = server->cb;

	ItsIso14827SubscribeEntry key = { p->subscriptionSerial };
	Iso14827PublicationType *type = p->type;
	ItsIso14827SubscribeEntry *sub = server->subscribes->find(server->subscribes, &key);
/*
	Iso14827RejectPubDataReason_other,
	Iso14827RejectPubDataReason_unknownSubscription,			(OK)
	Iso14827RejectPubDataReason_unknownPublicationNbr,			(?)
	Iso14827RejectPubDataReason_unknownPublicationMsgId,		(User Application)
	Iso14827RejectPubDataReason_invalidPublicationMsgId,		(User Application)
	Iso14827RejectPubDataReason_invalidPublicationMsgContent,	(User Application)
	Iso14827RejectPubDataReason_repeatedPublicationNbr,			(OK)
*/
	if (sub)
	{
		int status = 0;
		if (arg->is_retried)
		{	// 재전송된 퍼블리케이션
			if (type->present == Iso14827PublicationTypePresent_mgmt)
			{	// Subscription 관리 명령이 또 도착
				if (cbs->pubControl)
				{	// Pause / Resume 인 경우는 그냥 알림만, Terminate 인 경우는 앞서서 추출하고 알리고 삭제했으니 알람만
					Iso14827PublicationMgmt cmd = type->x.mgmt;
					cbs->pubControl(cbs->param, domain->name, server->peer, server->user, sub->serial, p->serial, cmd);
				}
			}
			else
			{	// Data 가 또 도착
				if (cbs->publication)
				{
					Iso14827SubscriptionData *data = sub->data;
					Iso14827SubscriptionDataMode *mode = data->mode;

					Iso14827EndAppMsg *eam = type->x.msg;
					Dz1Asn1Any *userMsg = eam->data;
					char strOID[128];
					Dz1Asn1OID_printable(eam->oid, strOID, 128, NULL);
					strOID[127] = '\0';
					cbs->publication(cbs->param, domain->name, server->peer, server->user, sub->serial, p->serial, strOID, userMsg->data, userMsg->size);
				}
			}
		}
		// 처음 수신한 퍼블리케이션
		else if ((status = _is_pub_serial_duplicated(sub, p->serial, &err)) < 0) ERR_OUT(&err);
		else if (status == 1)
		{	// 같은 Publication Serial 번호가 왔다 -> repeatedPublicationNbr
			ItsIso14827ClientDomainServerEntry_sendRejectPubData(server, session, domain->name,
																p->subscriptionSerial, p->serial,
																Iso14827RejectPubDataReason_repeatedPublicationNbr,
																domain->hdr_opt_flag,
																arg->uArg, arg->uRsc, arg->timer);
		}
		else if (type->present == Iso14827PublicationTypePresent_mgmt)
		{	// Subscription 관리 명령이 도착
			if (cbs->pubControl)
			{
				Iso14827PublicationMgmt cmd = type->x.mgmt;
				// Pause / Resume 인 경우는 그냥 알림만
				if (cmd == Iso14827PublicationMgmt_temporarilySuspended || cmd == Iso14827PublicationMgmt_resume)
					cbs->pubControl(cbs->param, domain->name, server->peer, server->user, sub->serial, p->serial, cmd);
				else
				{	// Terminate 인 경우는 추출하고 알리고 삭제
					server->subscribes->extract(server->subscribes, sub);
					pthread_cleanup_push(ItsIso14827SubscribeEntry_delAndSetNull, (void *)&sub);

					cbs->pubControl(cbs->param, domain->name, server->peer, server->user, sub->serial, p->serial, cmd);

					pthread_cleanup_pop(1); // (ItsIso14827SubscribeEntry_delAndSetNull, (void *)&sub);
				}
			}
		}
		else
		{	// Data가 도착
			if (cbs->publication)
			{
				Iso14827SubscriptionData *data = sub->data;
				Iso14827SubscriptionDataMode *mode = data->mode;

				Iso14827EndAppMsg *eam = type->x.msg;
				Dz1Asn1Any *userMsg = eam->data;
				char strOID[128];
				Dz1Asn1OID_printable(eam->oid, strOID, 128, NULL);
				strOID[127] = '\0';
				cbs->publication(cbs->param, domain->name, server->peer, server->user, sub->serial, p->serial, strOID, userMsg->data, userMsg->size);

				if (mode->present == Iso14827SubscriptionDataModePresent_single)
				{
					server->subscribes->remove(server->subscribes, sub);
				}
			}
		}
	}
	else
	{	// Subscription 이 없다 -> unknownSubscription
		ItsIso14827ClientDomainServerEntry_sendRejectPubData(server, session, domain->name,
															p->subscriptionSerial, p->serial,
															Iso14827RejectPubDataReason_unknownSubscription,
															domain->hdr_opt_flag,
															arg->uArg, arg->uRsc, arg->timer);
	}
	return err;
}

static Dz1Error client_receivePublication(ItsIso14827ClientDomainServerEntry *server,
										  ItsIso14827ClientDomain *domain,
										  u32_t pktNbr, Iso14827Publication *pub, bool_t isRetried,
										  ItsIso14827SessionEntry *session,
										  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827PublishFormat *fmt = pub->fmt;
	if (fmt->present != Iso14827PublishFormatPresent_dataList)
		ItsIso14827ClientDomainServerEntry_sendRejectPub(server, session, domain->name,
													pktNbr, Iso14827RejectPublication_invalidPublishFormat,
													domain->hdr_opt_flag,
													uArg, uRsc, timer);
	else
	{
		ReceivePublicationArg _arg = { server, domain, session, isRetried, uArg, uRsc, timer };
		Iso14827PublicationDataList *list = fmt->x.dataList;

		if (pub->guaranteed)
		{
			if (!(server->ctrl_flags & ItsIso14827ClientCtrlFlag_PubAckDeferred))
				ItsISo14827ClientDomainServerEntry_sendAcceptPub(server, session, domain->name, pktNbr, domain->hdr_opt_flag, uArg, uRsc, timer);
			else if ((server->ctrl_flags & ItsIso14827ClientCtrlFlag_PubAckDeferred) && isRetried)
				ItsISo14827ClientDomainServerEntry_sendAcceptPub(server, session, domain->name, pktNbr, domain->hdr_opt_flag, uArg, uRsc, timer);
		}

		if ((err = list->travel(list, _client_receivePublication, (void *)&_arg)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error _violatedSubReceived_sendRejectSub(ItsIso14827ClientDomain *my_domain, ItsIso14827ClientDomainServerEntry *peer_server, ItsIso14827SessionEntry *session,
												   Iso14827RejectSubscription reason, Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority, u32_t hdr_opt_flag, u32_t pktDumpFlag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Iso14827PDUs *pdu = Iso14827PDUs_new(Iso14827PDUsPresent_nak, NULL, errp);
	if (pdu == NULL) ERR_OUT(errp);
	else
	{
		Iso14827RejectType *rej_type = NULL;
		Iso14827Reject *nak = NULL;
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
		if ((pdu->x.nak = nak = Iso14827Reject_new(pktNbr, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((nak->type = rej_type = Iso14827RejectType_new(Iso14827RejectTypePresent_subscription, NULL, errp)) == NULL) ERR_OUT(errp);
		else 
		{
			rej_type->x.subscription = reason;
			ItsIso14827Domain_send_no_retry(session, authInfo, priority, &pdu, hdr_opt_flag, my_domain->name, peer_server->peer, pktDumpFlag);
		}
		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

static Dz1Error _violatedSubReceived_sendAcceptSub(ItsIso14827ClientDomain *my_domain, ItsIso14827ClientDomainServerEntry *peer_server, ItsIso14827SessionEntry *session,
												   Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority, u32_t hdr_opt_flag, u32_t pktDumpFlag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Iso14827PDUs *pdu = Iso14827PDUs_new(Iso14827PDUsPresent_ack, NULL, errp);
	if (pdu == NULL) ERR_OUT(errp);
	else
	{
		Iso14827AcceptType *ack_type = NULL;
		Iso14827Accept *ack = NULL;
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);

		if ((pdu->x.ack = ack = Iso14827Accept_new(pktNbr, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((ack->acceptType = ack_type = Iso14827AcceptType_new(Iso14827AcceptTypePresent_singleSubscription, NULL, errp)) == NULL) ERR_OUT(errp);
		else ItsIso14827Domain_send_no_retry(session, authInfo, priority, &pdu, hdr_opt_flag, my_domain->name, peer_server->peer, pktDumpFlag);

		pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
	}
	return err;
}

static Dz1Error client_receivedSubscription(ItsIso14827ClientDomainServerEntry *server, ItsIso14827ClientDomain *domain,
											ItsIso14827SessionEntry *session, Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
											Iso14827Subscription *sub, u32_t hdr_opt_flag, void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827ClientDomainViolatedSubscription *v_cb = NULL;

	Iso14827EndAppMsg *sub_eam = NULL;
	Iso14827SubscriptionDataMode *sub_mode = NULL;
	Iso14827SubscriptionData *sub_data = NULL;
	Iso14827SubscriptionType *sub_type = NULL;
	if ((sub_type = sub->type) == NULL || sub_type->present != Iso14827SubscriptionTypePresent_data || (sub_data = sub_type->x.data) == NULL)
		_violatedSubReceived_sendRejectSub(domain, server, session, Iso14827RejectSubscription_invalidSubscriptionContent, authInfo, pktNbr, priority, hdr_opt_flag, env->pktDumpFlag);
	else if (sub_data->fmt != Iso14827SubscriptionDataFormat_dataPacket)
		_violatedSubReceived_sendRejectSub(domain, server, session, Iso14827RejectSubscription_publishFormatNotSupported, authInfo, pktNbr, priority, hdr_opt_flag, env->pktDumpFlag);
	else if ((sub_mode = sub_data->mode) == NULL || sub_mode->present != Iso14827SubscriptionDataModePresent_single)
		_violatedSubReceived_sendRejectSub(domain, server, session, Iso14827RejectSubscription_invalidMode, authInfo, pktNbr, priority, hdr_opt_flag, env->pktDumpFlag);
	else if ((sub_eam = sub_data->msg) == NULL)
		_violatedSubReceived_sendRejectSub(domain, server, session, Iso14827RejectSubscription_invalidSubscriptionContent, authInfo, pktNbr, priority, hdr_opt_flag, env->pktDumpFlag);
	else if ((v_cb = server->violatedSub) == NULL || v_cb->inform == NULL)
		_violatedSubReceived_sendRejectSub(domain, server, session, Iso14827RejectSubscription_other, authInfo, pktNbr, priority, hdr_opt_flag, env->pktDumpFlag);
	else
	{
		char str_oid[1024] = { 0, };
		Dz1Asn1Any *ctx = sub_eam->data;
		Dz1Asn1OID *oid = sub_eam->oid;

		_violatedSubReceived_sendAcceptSub(domain, server, session, authInfo, pktNbr, priority, hdr_opt_flag, env->pktDumpFlag);

		Dz1Asn1OID_printable(oid, str_oid, 1024, NULL);
		v_cb->inform(v_cb->param, domain->name, server->peer, server->user, sub_data->guarantee, sub->serial, str_oid, ctx->data, ctx->size);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionMgr_received  = 오류 시 Session Entry 삭제
//   -> _ItsIso14827SessionMgr_received = C2C Message 삭제
//     -> ItsIso14827DomainMgr_received = 오류 시 Domain-Session Map 삭제
//	     -> _ItsIso14827DomainMgr_received = Server/Client에 따라 분기
//		   -> ItsIso14827ClientDomain_received = 오류 시 Server 삭제
//		     -> _ItsIso14827ClientDomain_received = PDU종류에 따라 분기
///////////////////////////////////////////////////////////////////////////////
static Dz1Error _ItsIso14827ClientDomain_received(ItsIso14827ClientDomainServerEntry *server,
												  ItsIso14827ClientDomain *domain,
												  ItsIso14827SessionEntry *session,
												  Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
												  Iso14827PDUs *pdu, bool_t isRetried,
												  void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	switch(pdu->present)
	{
	case Iso14827PDUsPresent_initiate:
		// 이미 연결 되어 있다. -> Ignore
		break;
	case Iso14827PDUsPresent_login:
		// Server 가 수신하는 Message -> Ignore
		break;
	case Iso14827PDUsPresent_fred:
		// FrED를 수신하는 경우
		if ((err = client_receiveFrED(server, domain, session, pdu, domain->hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	case Iso14827PDUsPresent_term:
		if ((err = client_receiveTerminated(server, domain->name, pdu->x.term, session, uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	case Iso14827PDUsPresent_logout:
		// Server 가 수신하는 Message -> Ignore
		break;
	case Iso14827PDUsPresent_transferDone:
		// Server 가 수신하는 Message -> Embedded Server인 경우 수신 가능
		// 기타 전송방법은 지원하지 않으니 그냥 FrED만 전송
		if ((err = ItsIso14827ClientDomainServerEntry_sendFrED(server, session, domain->name, pktNbr, NULL,
															   domain->hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	case Iso14827PDUsPresent_subscription:
		// client 가 Subscription 을 수신 -> 표준 위반. 그러나 허용
		if ((*errp = client_receivedSubscription(server, domain, session, authInfo, pktNbr, priority, pdu->x.subscription, domain->hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827PDUsPresent_publication:
		// Callback 만 호출
		if ((err = client_receivePublication(server, domain,
										pktNbr, pdu->x.publication, isRetried,
										session, uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	case Iso14827PDUsPresent_ack:
		if ((err = client_receiveAccept(server, domain->name, session,
										authInfo, pktNbr, priority,
										pdu, isRetried, domain->hdr_opt_flag,
										uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	case Iso14827PDUsPresent_nak:
		if ((err = client_receiveReject(server, domain->name, session,
										authInfo, pktNbr, priority,
										pdu, isRetried, domain->hdr_opt_flag,
										uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionMgr_received  = 오류 시 Session Entry 삭제
//   -> _ItsIso14827SessionMgr_received = C2C Message 삭제
//     -> ItsIso14827DomainMgr_received = 오류 시 Domain-Session Map 삭제
//	     -> _ItsIso14827DomainMgr_received = Server/Client에 따라 분기
//		   -> ItsIso14827ClientDomain_received = 오류 시 Server 삭제
///////////////////////////////////////////////////////////////////////////////
#define INITIATED_TEMPORARY_USER "###@@@$$$_INITIATED_TEMPORARY_USER_$$$@@@###"
Dz1Error ItsIso14827ClientDomain_received(ItsIso14827ClientDomain *domain,
										  ItsIso14827SessionEntry *session,
										  Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
										  Iso14827PDUs *pdu, bool_t isRetried,
										  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827ClientDomainServerEntry *server = _extractServerBySession(domain, session->key);
	if (server == NULL)
	{	// 세션 정보가 없다.
		// initiate인 경우
		if (pdu->present != Iso14827PDUsPresent_initiate) ERR_SET_OUT(&err, EINVAL);
		else
		{
			Iso14827Initiate *initiate = pdu->x.initiate;
			ItsIso14827ClientDomainCallback *cbs = domain->callback;
			if (cbs->initiated) cbs->initiated(cbs->param, domain->name, initiate->sender, session->codecRule, session->key);
		}
	}	
	else
	{
		DomainTimerCleanupArg _arg = { server, domain->name, timer };		
		pthread_cleanup_push(ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&server);
		pthread_cleanup_push(_ItsIso14827ClientDomainServerEntry_timerCleanup, (void *)&_arg);
		if ((err = _ItsIso14827ClientDomain_received(server, domain, session,
													authInfo, pktNbr, priority, pdu, isRetried,
													uArg, uRsc, timer)).code) ERR_OUT(&err);
		else if ((err = _registerServerEntry(domain, server)).code) ERR_OUT(&err);
		else
		{	// Heart-Beat Period Timer 갱신
			ItsIso14827DomainTimer_reg2(timer, ItsIso14827DomainType_client,
										domain->name, server->peer, server->user,
										DOMAIN_HEARTBEAT_PERIOD_TIMER,
										(u64_t)(1000000 * server->heartBeadPeriod) / 3,
										ItsIso14827ClientDomainMgr_heartBeatPeriodTimeout);
			// Heart-Beat Duration Timer 갱신
			ItsIso14827DomainTimer_reg2(timer, ItsIso14827DomainType_client,
										domain->name, server->peer, server->user,
										DOMAIN_HEARTBEAT_DURATION_TIMER,
										(u64_t)(1000000 * server->heartBeadPeriod),
										ItsIso14827DomainMgr_heartBeatDurationTimeout);
			server = NULL;
		}
		pthread_cleanup_pop(err.code); // (_ItsIso14827ClientDomainServerEntry_timerCleanup, (void *)&_arg);
		pthread_cleanup_pop(1); // (ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&server);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Task가 종료 할 때
void ItsIso14827ClientDomain_terminate(ItsIso14827ClientDomain *p)
{	// p는 지우면 안됨
	if (p == NULL) return;
}

///////////////////////////////////////////////////////////////////////////////
// Session이 끊어져서 user@PEER만 사라지는 경우
void ItsIso14827ClientDomain_sessionDisconnected(ItsIso14827ClientDomain *p, ItsIso14827SessionKey *skey, void *timer)
{
	ItsIso14827ClientDomainServerEntry *server = _extractServerBySession(p, skey);
	if (server != NULL)
	{
		DomainTimerCleanupArg arg = { server, p->name, timer };
		pthread_cleanup_push(ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&server);
		Dz1Thread_printf("ItsIso14827ClientDomain_sessionDisconnected() = ");
		ItsIso14827ClientDomainServerEntry_dump(server, 0);

		_ItsIso14827ClientDomainServerEntry_timerCleanup((void *)&arg);
		pthread_cleanup_pop(1); // (ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&server);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Heart-Beat Duration이 지나서 user@PEER를 제거하는 경우
ItsIso14827SessionKey *ItsIso14827ClientDomain_expireSession(ItsIso14827ClientDomain *p, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, void *timer)
{
	ItsIso14827SessionKey *ret = NULL;
	return ret;
}
