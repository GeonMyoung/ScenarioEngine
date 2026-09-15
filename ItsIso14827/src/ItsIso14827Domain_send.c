#include <dz1_task.h>
#include <ItsIso14827Def.h>
#include "ItsIso14827Env.h"
#include "ItsIso14827TimerUtil.h"
#include "ItsIso14827SessionMgr_main.h"
#include "ItsIso14827DomainMgr_main.h"
#include "ItsIso14827ServerDomain_main.h"
#include "ItsIso14827ClientDomain_main.h"
#include "ItsIso14827Domain_send.h"

static Dz1Error _heartBeatTimerUpdate(void *timer, ItsIso14827DomainType type,
									  Dz1Asn1UTF8Str *domainName, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
									  u32_t heartBeadDuration)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (type == ItsIso14827DomainType_client && (err = ItsIso14827DomainTimer_reg2(timer, type,
										domainName, peerDomain, user,
										DOMAIN_HEARTBEAT_PERIOD_TIMER,
										(u64_t)(1000000 * heartBeadDuration) / 3,
										ItsIso14827ClientDomainMgr_heartBeatPeriodTimeout)).code) ERR_OUT(&err);
	else if ((err = ItsIso14827DomainTimer_reg2(timer, type, domainName, peerDomain, user,
												DOMAIN_HEARTBEAT_DURATION_TIMER,
												(u64_t)1000000 * heartBeadDuration,
												ItsIso14827DomainMgr_heartBeatDurationTimeout)).code) ERR_OUT(&err);
	return err;
}

static Dz1Asn1OctetStr *_makeSureAuthInfo(Dz1Asn1OctetStr *src, Dz1Error *errp)
{
	Dz1Asn1OctetStr *ret = NULL;
	if (src == NULL || (src->data == NULL && src->size == 0))
	{
		if ((ret = Dz1Asn1OctetStr_new((u8_t *)" ", 1, errp)) == NULL) ERR_OUT(errp);
		else ret->size = 0;
	}
	else
	{
		if ((ret = Dz1Asn1OctetStr_clone(src, errp)) == NULL) ERR_OUT(errp);
	}
	return ret;
}

void ItsIso14827Domain_sendFail(void *uArg, void *uRsc, void *timer,
							   ItsIso14827DomainType type, Dz1Asn1UTF8Str *domainName,
							   Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
							   Iso14827C2CAuthMsg *msg, u32_t hdr_opt_flag)
{
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827DomainKey key = { type, domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, &key);
	if (domain)
	{
		if (domain->present == ItsIso14827DomainPresent_server)
		{
		}
		else if (domain->present == ItsIso14827DomainPresent_client)
		{
			ItsIso14827SessionKey *skey = NULL;
			if ((skey = ItsIso14827ClientDomain_sendFail(domain->x.client, peerName, user, msg, uArg, uRsc, timer)) != NULL)
			{
				pthread_cleanup_push(ItsIso14827SessionKey_delAndSetNull, (void *)&skey);
				ItsIso14827SessionMgr_sessionDisconnect(env->sessionMgr, skey);
				pthread_cleanup_pop(1); // (ItsIso14827SessionKey_delAndSetNull, (void *)&skey);
			}
		}
	}
}

static Dz1TaskProcStatus ItsIso14827Domain_retransmit(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp);
static Dz1Error ItsIso14827Domain_txForward(ItsIso14827DomainTxFifo *txFifo,
											ItsIso14827SessionEntry *session,
											ItsIso14827DomainType type,
											u32_t hdr_opt_flag,
											Dz1Asn1UTF8Str *domainName,
											Dz1Asn1UTF8Str *peerName,
											Dz1Asn1OctetStr *user,
											u32_t responseWaitTime,
											void *uArg, ItsIso14827Env *env, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	bool_t done = FALSE;
	ItsIso14827DomainTxEntry *e = NULL;
	while(done == FALSE)
	{
		if ((e = ItsIso14827DomainTxFifo_getTail(txFifo)) != NULL)
		{
			Dz1Thread_printf("ItsIso14827Domain_txForward() : process e = %p\n", e);
			if (e->status)
			{	// 응답 대기형
				if (*e->status < ItsIso14827DomainTxStatus_final)
				{	// 재전송 한적 없거나, 한번 보냄
					(*e->status)++; // none->sent or sent->final
					ItsIso14827SessionEntry_encodeAndSend(session, e->c2c, hdr_opt_flag, domainName, peerName, env->pktDumpFlag);
					if ((*errp = ItsIso14827DomainTimer_reg2(timer, type, domainName,
															peerName, user, DOMAIN_RETRANSMIT_TIMER,
															(u64_t)1000000 * responseWaitTime,
															ItsIso14827Domain_retransmit)).code) ERR_OUT(errp);
					done = TRUE;
				}
				else
				{	// 응답 완전 없음 -> 폐기
					ItsIso14827DomainTxFifo_pop(txFifo, NULL);
					if (e->sendFail)
					{
						e->sendFail(uArg, env, timer, type, domainName, peerName, user, e->c2c, hdr_opt_flag);
					}
					ItsIso14827DomainTxEntry_delAndSetNull(&e);
					done = TRUE;
				}
			}
			else
			{	// 응답 대기형이 아님 -> 전송 후 폐기
				ItsIso14827SessionEntry_encodeAndSend(session, e->c2c, hdr_opt_flag, domainName, peerName, env->pktDumpFlag);
				Dz1Thread_printf("ItsIso14827Domain_txForward() : delete e = %p\n", e);
				ItsIso14827DomainTxFifo_pop(txFifo, NULL);
				ItsIso14827DomainTxEntry_delAndSetNull(&e);
			}
		}
		else done = TRUE;
	}
	return err;
}

static Dz1TaskProcStatus ItsIso14827Domain_retransmit(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827Timer *tmr = (ItsIso14827Timer *)(*tData);
	if (tmr->present == ItsIso14827TimerPresent_domain)
	{
		ItsIso14827DomainTimer *tDomain = tmr->x.domain;

		ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, tDomain->key);
		if (domain)
		{
			if (domain->present == ItsIso14827DomainPresent_server)
			{
				ItsIso14827ServerDomain *server = domain->x.server;
				ItsIso14827ServerDomainClientEntry *client = ItsIso14827ServerDomain_findClientByPeerUser(server, tDomain->peer, tDomain->user);
				if (client)
				{
					ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);
					if (session == NULL)
					{
						Dz1Thread_printf("!!! Unknown Session = "); ItsIso14827SessionKey_dump(client->key, 0);
						ERR_SET_OUT(errp, ENOENT);
					}
					else if ((*errp = ItsIso14827Domain_txForward(client->txFifo, session,
															ItsIso14827DomainType_server,
															server->hdr_opt_flag,
															server->name, client->peer,
															client->user, client->responseWaitTime,
															uArg, env, timer)).code) ERR_OUT(errp);
				}
			}
			else if (domain->present == ItsIso14827DomainPresent_client)
			{
				ItsIso14827ClientDomain *client = domain->x.client;
				ItsIso14827ClientDomainServerEntry *server = ItsIso14827ClientDomain_findServerByPeerUser(client, tDomain->peer, tDomain->user);
				if (server)
				{
					ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, server->key);
					if (session == NULL)
					{
						Dz1Thread_printf("!!! Unknown Session = "); ItsIso14827SessionKey_dump(server->key, 0);
						ERR_SET_OUT(errp, ENOENT);
					}
					if ((*errp = ItsIso14827Domain_txForward(server->txFifo, session,
															 ItsIso14827DomainType_client,
															 client->hdr_opt_flag,
															 client->name, server->peer,
															 server->user, server->responseWaitTime,
															 uArg, env, timer)).code) ERR_OUT(errp);
				}
			}
		}
	}
	return ret;
}

Dz1Error ItsIso14827Domain_send_no_retry(ItsIso14827SessionEntry *session,
										 Dz1Asn1OctetStr *authInfo, s32_t priority,
										 Iso14827PDUs **pdu,
										 u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest,
										 u32_t pktDumpFlag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Iso14827C2CAuthMsg *msg = NULL;
	if ((msg = Iso14827C2CAuthMsg_new(NULL, session->txSerial, priority, NULL, (*pdu), errp)) == NULL) ERR_OUT(errp);
	else
	{
		(*pdu) = NULL;
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&msg);
		if (0) { }
		else if ((msg->authInfo = _makeSureAuthInfo(authInfo, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->hdrOpt = Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			session->txSerial++;
			ItsIso14827SessionEntry_encodeAndSend(session, msg, hdr_opt_flag, sender, dest, pktDumpFlag);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}

Dz1Error ItsIso14827Domain_send(ItsIso14827DomainTxFifo *txFifo,
								ItsIso14827SessionEntry *session,
								ItsIso14827DomainType domainType,
								u32_t hdr_opt_flag,
								Dz1Asn1UTF8Str *domainName, Dz1Asn1UTF8Str *peerName,
								Dz1Asn1OctetStr *user, Dz1Asn1OctetStr *authInfo, 
								u32_t responseWaitTime, u32_t heartBeatDuration, s32_t priority,
								Iso14827PDUs **pdu, bool_t needWait,
								ItsIso14827DomainTxFail sendFail,
								void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainTxEntry *e = ItsIso14827DomainTxEntry_new(NULL, NULL, sendFail, hdr_opt_flag, &err);
	if (e == NULL) ERR_OUT(&err);
	else
	{
		Iso14827C2CAuthMsg *msg = NULL;
		pthread_cleanup_push(ItsIso14827DomainTxEntry_delAndSetNull, (void *)&e);
		if ((e->c2c = msg = Iso14827C2CAuthMsg_new(NULL, session->txSerial, priority, NULL, (*pdu), &err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827DomainTxStatus v = ItsIso14827DomainTxStatus_none;
			*pdu = NULL;
			if (needWait == TRUE && (e->status = (u32_t *)ItsIso14827DomainTxStatus_new(&v, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->authInfo = _makeSureAuthInfo(authInfo, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->hdrOpt = Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
			else
			{
				session->txSerial++;
				if (ItsIso14827DomainTxFifo_isEmpty(txFifo))
				{	// fifo가 비었으면 일단 전송
					ItsIso14827SessionEntry_encodeAndSend(session, msg, hdr_opt_flag, domainName, peerName, env->pktDumpFlag);
					_heartBeatTimerUpdate(timer, domainType, domainName, peerName, user, heartBeatDuration);
					// 응답을 기다려야 되면
					if (needWait)
					{
						*e->status = ItsIso14827DomainTxStatus_sent;
						// 재 전송 타이머 등록
						if ((err = ItsIso14827DomainTimer_reg2(timer, domainType, domainName,
															peerName, user, DOMAIN_RETRANSMIT_TIMER,
															(u64_t)1000000 * responseWaitTime,
															ItsIso14827Domain_retransmit)).code) ERR_OUT(&err);
						// fifo에 push
						else if ((err = ItsIso14827DomainTxFifo_push(txFifo, e)).code) ERR_OUT(&err);
						// 메세지 보존
						else e = NULL;
					}
					// 응답을 기다릴 필요가 없으면 (fifo가 비었음으로) 끝
					else
					{
					}
				}
				else
				{	// fifo가 비어있지 않으면 push 하고 끝
					if ((err = ItsIso14827DomainTxFifo_push(txFifo, e)).code) ERR_OUT(&err);
					// 메세지 보존
					else e = NULL;
				}
			}
		}
		pthread_cleanup_pop(1); // (ItsIso14827DomainTxEntry_delAndSetNull, (void *)&e);
	}
	return err;
}

Dz1Error ItsIso14827Domain_confirm(ItsIso14827DomainTxFifo *txFifo,
								   ItsIso14827SessionEntry *session, 
								   ItsIso14827DomainType type,
								   u32_t hdr_opt_flag,
								   Dz1Asn1UTF8Str *domainName,
								   Dz1Asn1UTF8Str *peerName,
								   Dz1Asn1OctetStr *user,
								   u32_t responseWaitTime,
								   u32_t pktNbr, Iso14827C2CAuthMsg **sent,
								   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainTxEntry *e = ItsIso14827DomainTxFifo_getTail(txFifo);
	if (e)
	{
		Iso14827C2CAuthMsg *c2c = e->c2c;
		if (c2c->pktNbr == pktNbr)
		{
			//bool_t done = FALSE;
			ItsIso14827DomainTxFifo_pop(txFifo, NULL);
			if (sent != NULL) { (*sent) = e->c2c; e->c2c = NULL; }

			ItsIso14827DomainTimer_dereg(timer, type, domainName, peerName, user, DOMAIN_RETRANSMIT_TIMER);

			ItsIso14827DomainTxEntry_delAndSetNull(&e);

			if ((err = ItsIso14827Domain_txForward(txFifo, session, type,
												   hdr_opt_flag, domainName, peerName,
												   user, responseWaitTime,
												   uArg, env, timer)).code) ERR_OUT(&err);
		}
	}
	return err;
}


