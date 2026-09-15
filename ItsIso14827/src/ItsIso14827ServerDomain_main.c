#include <dz1_gasn_support.h>
#include <Iso14827dz1_assist.h>

#include "ItsIso14827Env.h"

#include "ItsIso14827SessionMgr_main.h"
#include "ItsIso14827DomainMgr_main.h"
#include "ItsIso14827ServerDomainTimer.h"
#include "ItsIso14827Domain_send.h"
#include "ItsIso14827ServerDomain_send.h"
#include "ItsIso14827ServerDomain_main.h"
#include "ItsIso14827ServerDomain_subscription.h"

static void ItsIso14827ServerDomainClientEntry_timerCleanup(ItsIso14827ServerDomainClientEntry *client, Dz1Asn1UTF8Str *domainName, void *timer)
{	// 본 Client와 연관된 모든 Timer제거
	ItsIso14827ServerDomainTimer_dereg(timer, domainName, client->peer, client->user, DOMAIN_RETRANSMIT_TIMER);
	ItsIso14827ServerDomainTimer_dereg(timer, domainName, client->peer, client->user, DOMAIN_HEARTBEAT_DURATION_TIMER);
	ItsIso14827ServerDomainClientEntrySubscription_disconnected(client, domainName, timer);
	if (client->state == ItsIso14827ServerDomainClientState_established)
	{
		ItsIso14827ServerDomainCallback *cbs = client->cb;
		if (cbs->disconnected) 
			cbs->disconnected(cbs->param, domainName, client->peer, client->user);
	}
}

typedef struct DomainTimerCleanupArg
{
	ItsIso14827ServerDomainClientEntry *client;
	Dz1Asn1UTF8Str *domainName;
	void *timer;
} DomainTimerCleanupArg;

static void _ItsIso14827ServerDomainClientEntry_timerCleanup(void *ptr)
{
	DomainTimerCleanupArg *arg = (DomainTimerCleanupArg *)ptr;	
	ItsIso14827ServerDomainClientEntry_timerCleanup(arg->client, arg->domainName, arg->timer);
}

// 등록 중 에러가 난 경우 등록한거 취소하기
typedef struct ClientAddCancelArg
{
	ItsIso14827ServerDomainClientList *list;
	Dz1Asn1UTF8Str *peer;
} ClientAddCancelArg;

static void ItsIso14827ServerDomainClientList_addCancel(void *ptr)
{
	ClientAddCancelArg *arg = (ClientAddCancelArg *)ptr;
	ItsIso14827ServerDomainClientEntry key = { arg->peer };
	arg->list->extract(arg->list, &key);
}
// Client 등록하기
static Dz1Error _registerClientEntry(ItsIso14827ServerDomain *domain, ItsIso14827ServerDomainClientEntry *client)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = domain->clients->add(domain->clients, client)).code) ERR_OUT(&err);
	else
	{
		ClientAddCancelArg arg = { domain->clients, client->peer };
		pthread_cleanup_push(ItsIso14827ServerDomainClientList_addCancel, (void *)&arg);

		if ((err = domain->sessions->add(domain->sessions, (ItsIso14827ServerDomainSessionEntry *)client)).code) ERR_OUT(&err);
		else Dz1Error_set(&err, 0);

		pthread_cleanup_pop(err.code); // (ItsIso14827ServerDomainClientList_addCancel, (void *)&arg);
	}
	return err;
}

// Session Key로 등록된 Client 뽑아내기
static ItsIso14827ServerDomainClientEntry *_extractClientBySession(ItsIso14827ServerDomain *domain, ItsIso14827SessionKey *skey)
{
	ItsIso14827ServerDomainSessionEntry key = { NULL, NULL, skey }, *client = domain->sessions->extract(domain->sessions, &key);
	if (client) domain->clients->extract(domain->clients, (ItsIso14827ServerDomainClientEntry *)client);
	return (ItsIso14827ServerDomainClientEntry *)client;
}

static ItsIso14827ServerDomainClientEntry *_extractClientByPeerUser(ItsIso14827ServerDomain *domain,
																	Dz1Asn1UTF8Str *peer,
																	Dz1Asn1OctetStr *user)
{
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->extract(domain->clients, &key);
	if (client) domain->sessions->extract(domain->sessions, (ItsIso14827ServerDomainSessionEntry *)client);
	return client;
}

// Session Key로 Client찾아내기
ItsIso14827ServerDomainClientEntry *ItsIso14827ServerDomain_findClientBySession(ItsIso14827ServerDomain *domain, ItsIso14827SessionKey *skey)
{
	ItsIso14827ServerDomainSessionEntry key = { NULL, NULL, skey };
	return (ItsIso14827ServerDomainClientEntry *)domain->sessions->find(domain->sessions, &key);
}

// Peer Domain Name과 User로 Client찾아내기
ItsIso14827ServerDomainClientEntry *ItsIso14827ServerDomain_findClientByPeerUser(ItsIso14827ServerDomain *domain,
																			 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user)
{
	ItsIso14827ServerDomainClientEntry key = { peer, user };
	return domain->clients->find(domain->clients, &key);
}


///////////////////////////////////////////////////////////////////////////////
// Accept를 수신한 경우
///////////////////////////////////////////////////////////////////////////////
static Dz1Error server_receiveAccept(ItsIso14827ServerDomainClientEntry *client,
									 Dz1Asn1UTF8Str *domainName,
									 ItsIso14827SessionEntry *session,
									 Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
									 Iso14827PDUs *pdu, bool_t isRetried,
									 u32_t hdr_opt_flag,
									 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827Accept *msg = pdu->x.ack;
	if ((err = ItsIso14827Domain_confirm(client->txFifo, session, ItsIso14827DomainType_server,
										hdr_opt_flag, domainName, client->peer, client->user, client->responseWaitTime,
										msg->pktNbr, NULL, uArg, uRsc, timer)).code) ERR_OUT(&err);
	else
	{
		Iso14827AcceptType *type = msg->acceptType;
		switch(type->present)
		{
		case Iso14827AcceptTypePresent_login:
			// Client인 경우에만 수신 -> 에러로 처리 -> 세션 종료
			ERR_SET_OUT(&err, EINVAL);
			break;
		case Iso14827AcceptTypePresent_singleSubscription:
			// Client인 경우에만 수신 하지만, 한국에선 Server도 수신할 수 있다...
			// XXX : if (embeddedClient)
			// XXX : {
			// XXX :	Simple Indication Confirm(msg->pktNbr) ->
			// XXX :		Confirm to Confirm List ->
			// XXX :			notify to user via subscribe list
			// XXX : }
			break;
		case Iso14827AcceptTypePresent_registeredSubscription:
			// Client인 경우에만 수신 하지만, 한국에선 Server도 수신할 수 있다...
			// XXX : if (embeddedClient)
			// XXX : {
			// XXX :	Simple Indication Confirm(msg->pktNbr) ->
			// XXX :		Confirm to Confirm List ->
			// XXX :			notify to user via subscribe list
			// XXX : }
			break;
		case Iso14827AcceptTypePresent_publication:
			// 잘 보냈으면 땡~
			break;
		default:
			break;
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Reject를 수신한 경우
///////////////////////////////////////////////////////////////////////////////
static Dz1Error server_receiveReject(ItsIso14827ServerDomainClientEntry *client,
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
	if ((err = ItsIso14827Domain_confirm(client->txFifo, session, ItsIso14827DomainType_server,
									hdr_opt_flag, domainName, client->peer, client->user, client->responseWaitTime,
									msg->pktNbr, &sent, uArg, uRsc, timer)).code) ERR_OUT(&err);
	else
	{
		Iso14827RejectType *type = msg->type;
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&sent);
		switch(type->present)
		{
		case Iso14827RejectTypePresent_login:
			// Client인 경우에만 수신 -> 에러로 처리 -> 세션 종료
			ERR_SET_OUT(&err, EINVAL);
			break;
		case Iso14827RejectTypePresent_subscription:
			// XXX : Error in Indication
			// XXX : if (embeddedClient)
			// XXX : {
			// XXX :	Indication Confirm(msg->pktNbr, type->x.subscription) ->
			// XXX :		Confirm to Confirm List ->
			// XXX :			notify to user via subscribe list
			// XXX : }
			break;
		case Iso14827RejectTypePresent_publication:
		case Iso14827RejectTypePresent_pubData:
			// Publication 관련 Reject는 Subsctiprion Entry FSM에서 처리 하도록 한다.
			if ((err = ItsIso14827ServerDomainClientEntrySubscription_nak(client, domainName, session,
																		  authInfo, pktNbr, priority,
																		  pdu, sent, uArg, uRsc, timer)).code) ERR_OUT(&err);
			break;
		default:
			break;
		}
		pthread_cleanup_pop(1); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&sent);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Login을 받은 경우
///////////////////////////////////////////////////////////////////////////////
// Login Reason 검사
static Dz1Error _checkLoginReason(ItsIso14827ServerDomain *domain, Iso14827Login *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	/*
	// XXX : Initiate기능이 구현되면 하자.
	if (p->initiator == Iso14827LoginInitiator_serverInitiated)
	{
		ItsIso14827DomainInitiatorWaitEntry key = { p->sender }, *node = domain->initWaits->find(domain->initWaits, &key);
		if (node == NULL) ERR_SET_OUT(&err, ENOENT);
		else ItsIso14827DomainInitiatorWaitEntry_del(node);
	}
	else if (p->initiator != Iso14827LoginInitiator_clientInitiated) ERR_SET_OUT(&err, EINVAL);
	*/
	return err;
}

static u8_t _getUserCodecOIDMean(ItsIso14827CodecOIDMapList *list, Dz1Asn1OID *p)
{
	u8_t ret = 0;
	if (list != NULL)
	{
		ItsIso14827CodecOIDMap key = { p }, *node = list->find(list, &key);
		if (node != NULL)
			ret = Dz1GASN_codec2Bit(node->mean);
	}
	return ret;
}

typedef struct MkCodecBitsArg
{
	ItsIso14827CodecOIDMapList	*userCodecOIDList;
	u8_t dst;
} MkCodecBitsArg;

// Codec OID를 Codec Bit Flag 값으로 변환
static Dz1Error __mkCodecBits(void *ptr, Dz1Asn1OID *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MkCodecBitsArg *arg = (MkCodecBitsArg *)ptr;
	Dz1Asn1Codec codec = Dz1GASN_oid2Codec(p);
	if (codec == Dz1Asn1Codec_unknown || codec >= Dz1Asn1Codec_max)
		arg->dst |= _getUserCodecOIDMean(arg->userCodecOIDList, p);
	else
		arg->dst |= Dz1GASN_codec2Bit(codec);

	Dz1Thread_printf("CODEC Bits = %02X\n", arg->dst);

	return err;
}

#define DEFAULT_HEARTBEAT_DURATION				30
#define DEFAULT_RESPONSE_WAIT					7
// Login에 들어있는 Codec OID들을 Codec Bit Flag로 변환
static Dz1Error _mkCodecBits(u8_t *dst, Dz1OIDList *oids, ItsIso14827CodecOIDMapList *userCodecOIDList)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MkCodecBitsArg arg = { userCodecOIDList, 0 };

	if ((err = oids->travel(oids, __mkCodecBits, (void *)&arg)).code) ERR_OUT(&err);
	else (*dst) = arg.dst;

	return err;
}

static void _initiatorConfirm(ItsIso14827SessionEntry *session)
{
	if (session->initiator != NULL)
	{
		Dz1Error *status = Dz1TaskSigMsg_getErrPtr(session->initiator);
		Dz1Error_set(status, 0);
		Dz1TaskSigMsg_termDelAndSetNull(&session->initiator);
	}
}

static Dz1Error ItsIso14827ServerDomain_receivedLogin(ItsIso14827ServerDomain *domain,
													  ItsIso14827SessionEntry *session,
													  u32_t pktNbr, Iso14827Login *p, Dz1Asn1OctetStr *authInfo,
													  Iso14827RejectLogin *reason, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Iso14827RejectLogin _reason = Iso14827RejectLogin_other, *rp = reason ? reason : &_reason;
	ItsIso14827ServerDomainCallback *cb = domain->callback;

	ItsIso14827ServerDomainClientEntry *client = NULL;
	if (domain->sessions->count(domain->sessions) >= domain->maxClients)
	{
		(*rp) = Iso14827RejectLogin_maxSessionReached;
		ERR_SET_OUT(errp, ENOMEM);
	}
	else if ((client = ItsIso14827ServerDomainClientEntry_new(NULL, NULL, NULL, NULL,
															p->hbDur, p->timeout, pktNbr,
															domain->callback, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u8_t codecBits = 0, libCodecBits = 0;
//		Dz1SocketBuf *buf = session->buf;
		pthread_cleanup_push(ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);

		if ((client->peer = Dz1Asn1UTF8Str_clone(p->sender, errp)) == NULL)					ERR_OUT(errp);		// *rp = Iso14827RejectLogin_other
		else if ((client->user = Dz1Asn1OctetStr_clone(p->user, errp)) == NULL)				ERR_OUT(errp);		// *rp = Iso14827RejectLogin_other
		else if ((client->key = ItsIso14827SessionKey_clone(session->key, errp)) == NULL)	ERR_OUT(errp);		// *rp = Iso14827RejectLogin_other
		else if ((client->txFifo = ItsIso14827DomainTxFifo_new(errp)) == NULL)				ERR_OUT(errp);		// *rp = Iso14827RejectLogin_other
		/*
		A server shall determine if the domain names, user-name, password, maximum heartbeat duration,
		response time-out period, allowed encoding rules, datagram size and login reason are valid for the request.
		The server shall also ensure that a session with the given domain name and transport profile does not already exist.

		domain names				:: Already
		user-name/password			:: User Application
		maximum heartbeat duration	:: User Application
		response time-out period	:: User Application
		allowed encoding rules		:: User Application
		datagram size				:: Checkable
		login reason				:: Checkable
		domain name(Server, Client) + transport profile(Session) is unique :: Already
		*/
		// 요구한 버퍼 사이즈만큼 키움(궂이 줄일 필요는 없음)
//		else if ((err = Dz1SocketBuf_expand(session->buf, p->datagramSize)).code) ERR_OUT(errp);				// no need to ElasticBuf
		// Login Reason 검사
		else if ((err = _checkLoginReason(domain, p)).code)									ERR_OUT(errp);		// *rp = Iso14827RejectLogin_other
		// Login에서 지정한 Codec Rule 조사
		else if ((err = _mkCodecBits(&codecBits, p->encRules, domain->codecOidMap)).code)	ERR_OUT(errp);		// *rp = Iso14827RejectLogin_other
		// Iso14827 Codec이 지원하는 Codec Bit Mask와 결합 -> 사용가능한 Codec이 없으면 에러
		else if ((libCodecBits = Iso14827dz1_getSupportedCodec() & codecBits) == 0)
		{
        	Dz1Thread_printf("Library CODEC = %02X, Login CODEC = %02X\n", libCodecBits, codecBits);
			ERR_SET_OUT(errp, ENOSYS);																			// *rp = Iso14827RejectLogin_other
		}
		// Client 등록
		else if ((err = _registerClientEntry(domain, client)).code)
		{
			ERR_OUT(errp);
			if (errp->code == EEXIST) *rp = Iso14827RejectLogin_sessionExist;									// EEXIST = Iso14827RejectLogin_sessionExist
		}
		else
		{
			_initiatorConfirm(session);

			ItsIso14827SessionTimer_dereg(timer, session->key, SESSION_ALIVE_TIMER);

			client = NULL;
			// User Application에게 인증 요청
			// Callback to Application
			cb->authenticate(cb->param, domain->name, p->sender, p->user, p->pass, authInfo, p->hbDur, p->timeout, codecBits, FALSE);
			// XXX : LOGIN_RESULT_WAIT_TIMER(Response Wait Time)
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);
	}
	return err;
}

typedef struct ServerReceivedPublicationArg
{
	Dz1Asn1UTF8Str *domainName;
	Dz1Asn1UTF8Str *peerName;
	Dz1Asn1OctetStr *user;
	ItsIso14827ServerDomainViolatedPublication *vpcb;
} ServerReceivedPublicationArg;

static Dz1Error __server_receivedPublication(void *ptr, Iso14827PublicationData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ServerReceivedPublicationArg *arg = (ServerReceivedPublicationArg *)ptr;


	Iso14827PublicationType *type = p->type;
	if (type->present == Iso14827PublicationTypePresent_msg)
	{
		Iso14827EndAppMsg *eam = type->x.msg;

		Dz1Asn1OID *oid = eam->oid;
		Dz1Asn1Any *body = eam->data;
		char oidStr[1025];
		if (Dz1Asn1OID_printable(oid, oidStr, 1024, &err) <= 0) ERR_OUT(&err);
		else
		{
			ItsIso14827ServerDomainViolatedPublication *vpcb = arg->vpcb;
			vpcb->inform(vpcb->param, arg->domainName, arg->peerName, arg->user,
						 p->subscriptionSerial, p->serial,
						 oidStr, body->data, body->size);
		}
	}

	return err;
}

static Dz1Error _server_receivedPublication(ItsIso14827ServerDomainClientEntry *client,
											Dz1Asn1UTF8Str *domainName,
											ItsIso14827SessionEntry *session,
											Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
											Iso14827Publication *pub, bool_t isRetried,
											u32_t hdr_opt_flag,
											void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827PublishFormat *fmt = NULL;
	ItsIso14827ServerDomainViolatedPublication *vp = client->violatedPub;
	if (vp == NULL || vp->inform == NULL || (fmt = pub->fmt) == NULL)
		ItsIso14827ServerDomainClientEntry_sendRejectPub(client, domainName, session, pktNbr, Iso14827RejectPublication_other, hdr_opt_flag, uArg, uRsc, timer);
	else if (fmt->present != Iso14827PublishFormatPresent_dataList)
		ItsIso14827ServerDomainClientEntry_sendRejectPub(client, domainName, session, pktNbr, Iso14827RejectPublication_invalidPublishFormat, hdr_opt_flag, uArg, uRsc, timer);
	else
	{
		ServerReceivedPublicationArg arg = { domainName, client->peer, client->user, vp };
		Iso14827PublicationDataList *list = fmt->x.dataList;

		if (pub->guaranteed)
			ItsIso14827ServerDomainClientEntry_sendAcceptPub(client, domainName, session, pktNbr, hdr_opt_flag, uArg, uRsc, timer);

		if ((err = list->travel(list, __server_receivedPublication, (void *)&arg)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionMgr_received  = 오류 시 Session Entry 삭제
//   -> _ItsIso14827SessionMgr_received = C2C Message 삭제
//     -> ItsIso14827DomainMgr_received = 오류 시 Domain-Session Map 삭제
//	     -> _ItsIso14827DomainMgr_received = Server/Client에 따라 분기
//		   -> ItsIso14827ServerDomain_received = 오류 시 Client 삭제
//		     -> _ItsIso14827ServerDomain_received = PDU종류에 따라 분기
///////////////////////////////////////////////////////////////////////////////
static Dz1Error _ItsIso14827ServerDomain_received(ItsIso14827ServerDomainClientEntry *client,
												  ItsIso14827ServerDomain *domain,
												  ItsIso14827SessionEntry *session,
												  Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
												  Iso14827PDUs *pdu, bool_t isRetried,
												  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainCallback *cb = domain->callback;
	switch(pdu->present)
	{
	//case Iso14827PDUsPresent_initiate: // Server Send, Client Receive
	case Iso14827PDUsPresent_login: // Server Received(if retransmitted), Client Send
		// Login State를 이용하여 순차적인 처리를 하도록 변경 해야 함
		if (isRetried)
		{
			if (client->loginRetriedPktNbr != NULL)
			{
				ItsIso14827ServerDomainClientEntry_sendRejectLogin(client, domain->name, session, pktNbr,
																	Iso14827RejectLogin_sessionExist,
																	domain->hdr_opt_flag, uArg, uRsc, timer);
			}
			if (client->state == ItsIso14827ServerDomainClientState_waitLoginResult)
			{
				Iso14827Login *p = pdu->x.login;
				if ((client->loginRetriedPktNbr = Dz1u32_new(pktNbr, &err)) == NULL) ERR_OUT(&err);
				else
				{
					u8_t codecBits = 0;
					_mkCodecBits(&codecBits, p->encRules, domain->codecOidMap);
					cb->authenticate(cb->param, domain->name, p->sender, p->user, p->pass, authInfo, p->hbDur, p->timeout, codecBits, TRUE);
				}
			}
			else
			{
				ItsIso14827ServerDomainClientEntry_sendRejectLogin(client, domain->name, session, pktNbr,
																	Iso14827RejectLogin_other,
																	domain->hdr_opt_flag, uArg, uRsc, timer);
			}
		}
		else
			ItsIso14827ServerDomainClientEntry_sendRejectLogin(client, domain->name, session, pktNbr,
																Iso14827RejectLogin_sessionExist,
																domain->hdr_opt_flag, uArg, uRsc, timer);
		break;
	case Iso14827PDUsPresent_fred:	// Server Receive FrED(0) Packet Only and Send, Client Send/Receive
		if (pdu->x.fred != 0)
		{
			Dz1Thread_printf("--- Stupid CLIENT!!! client send FrED(%u)\n", pdu->x.fred);
			//ERR_SET_OUT(&err, EINVAL); // 아니면 에러 유발 -> Entry 삭제됨
		}
		// Application에 Echo요청이 왔음을 알림
		if (cb->echoRequest) cb->echoRequest(cb->param, domain->name, client->peer, client->user, pktNbr);
		break;
	//case Iso14827PDUsPresent_term: // Server Send, Client Receive
	case Iso14827PDUsPresent_logout: // Server Receive, Client Send
		// 즉시 응답을 위해 Fifo를 거치지 않고 바로 전송
		// txFifo에 있는것들과 Confirm대기중인 것들 처리는?
		ItsIso14827SessionEntry_sendFrED(session, pktNbr, NULL,
										domain->hdr_opt_flag, domain->name, client->peer,
										env->pktDumpFlag); // 일단 응답

		if (client->state == ItsIso14827ServerDomainClientState_terminated)
		{	// terminate를 전송하여 삭제 대기 : Application은 이미 이 Client에 대한 정보를 싸그리 지웠을 것임
		}
		else
		{	// Client가 Logout하기 원함
			// Application에게 접속이 예상치 못하게 끊겼음
		}
		// 각각 Subscription에 대한 terminate callback 호출 및 타이머는 상위 함수에서 Cleanup할 때 한다.

		// error를 리턴하여 Session이 삭제 되도록 한다.
		ERR_SET_OUT(&err, EPIPE);
		break;
	case Iso14827PDUsPresent_subscription: // Server Receive, Client Send
		if ((err = ItsIso14827ServerDomainClientEntrySubscription_recv(domain, client, session,
																		authInfo, pktNbr, priority,
																		pdu, isRetried,
																		uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	case Iso14827PDUsPresent_publication: // Server Send, Client Receive
		// 한국에서는 Server가 Publication도 수신 할 수 있음!!!
		if ((err = _server_receivedPublication(client, domain->name, session, authInfo, pktNbr, priority, pdu->x.publication, isRetried,
											   domain->hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	case Iso14827PDUsPresent_transferDone: // Server Receive, Client Send
		// FTP기능은 추후에... 단순히 FrED만 전송한다
		if ((err = ItsIso14827ServerDomainClientEntry_sendFrED(client, domain->name, session, pktNbr, NULL,
																domain->hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	case Iso14827PDUsPresent_ack: // Server Send/Receive, Client Send/Receive
		if ((*errp = server_receiveAccept(client, domain->name, session,
										  authInfo, pktNbr, priority,
										  pdu, isRetried, domain->hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	case Iso14827PDUsPresent_nak: // Server Send/Receive, Client Send/Receive
		if ((*errp = server_receiveReject(client, domain->name, session,
											authInfo, pktNbr, priority,
											pdu, isRetried, domain->hdr_opt_flag, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	default:
		break;
	}
	return err;
}

////////////////////////////////////////////////
// Domain이 PDU를 수신한 경우
// ItsIso14827SessionMgr_received  = 오류 시 Session Entry 삭제
//   -> _ItsIso14827SessionMgr_received = C2C Message 삭제
//     -> ItsIso14827DomainMgr_received = 오류 시 Domain-Session Map 삭제
//	     -> _ItsIso14827DomainMgr_received = Server/Client에 따라 분기
//		   -> ItsIso14827ServerDomain_received = 오류 시 Client 삭제
////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomain_received(ItsIso14827ServerDomain *domain,
										  ItsIso14827SessionEntry *session,
										  Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
										  Iso14827PDUs *pdu, bool_t isRetried,
										  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827ServerDomainClientEntry *client = _extractClientBySession(domain, session->key);
	if (client == NULL)
	{	// 연관된 Client Entry가 없음
		if (pdu->present == Iso14827PDUsPresent_login)
		{	// Login의 경우에 한하여...
			Iso14827RejectLogin reason = Iso14827RejectLogin_other;
			if ((err = ItsIso14827ServerDomain_receivedLogin(domain, session, pktNbr,
															pdu->x.login, authInfo,
															&reason, timer)).code)
			{	// 등록 중 실패 -> 직접 전송
				// Send Reject Login
				Iso14827Login *p = pdu->x.login;
				ItsIso14827SessionEntry_sendRejectLogin(session, pktNbr, reason,
														domain->hdr_opt_flag, domain->name, p->sender,
														env->pktDumpFlag);
				ERR_OUT(&err);
			}
		}
		else
		{	// login이 아닌경우 -> 걍 에러 -> 그럼 Session 끊어지겠지?
			ERR_SET_OUT(&err, ENOENT);
		}
	}
	else
	{	// Session으로 user@PEER를 찾아낼 수 있는 상황
		DomainTimerCleanupArg _arg = { client, domain->name, timer };
		pthread_cleanup_push(ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);
		pthread_cleanup_push(_ItsIso14827ServerDomainClientEntry_timerCleanup, (void *)&_arg);
		if ((err = _ItsIso14827ServerDomain_received(client, domain, session,
													authInfo, pktNbr, priority,
													pdu, isRetried,
													uArg, uRsc, timer)).code) ERR_OUT(&err);
		else if ((err = _registerClientEntry(domain, client)).code) ERR_OUT(&err);
		else
		{
			// Heart-Beat Duration Timer 갱신
			ItsIso14827ServerDomainTimer_reg(timer, domain->name, client->peer, client->user,
											DOMAIN_HEARTBEAT_DURATION_TIMER,
											(u64_t)1000000 * client->heartBeadPeriod,
											ItsIso14827DomainMgr_heartBeatDurationTimeout);
			client = NULL;
		}
		pthread_cleanup_pop(err.code); // (_ItsIso14827ServerDomainClientEntry_timerCleanup, (void *)&_arg);
		pthread_cleanup_pop(1); // (ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);
	}
	return err;
}

Dz1Error ItsISo14827ServerDomain_connectToClient(ItsIso14827ServerDomain *domain,
												 ItsIso14827SessionEntry *session,
												 Iso14827Initiate **initiate, Dz1TaskSigMsg **sg,
												 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	return err;
}


///////////////////////////////////////////////////////////////////////////////
// Login Accept
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomain_loginAccept(ItsIso14827ServerDomain *domain,
											 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
											 Dz1Asn1Codec selectedCodec, ItsIso14827CRCCheck CRCMode,
											 ItsIso14827ServerDomainViolatedPublication *violatedPub,
											 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->find(domain->clients, &key);

	ItsIso14827ServerDomain_dump(domain, 1);

	if (client == NULL)
	{
		// func test
		// vmsDatex Test 중 ItsIcInterfaceTest에서 VMSS VMSC 동시 접속시 ItsIcInterfaceTest에서 VMSC의 timeout=ItsIso14827ClientDomain_main.c:196이 발생
		// 접속이 안된걸 vmsDatexControl 쪽에서 인식을 못함
		// 하여 등록된 콜백의 discconet를 호출하여 세선 해제를 알도록 함
		// 이전단계에서 login단계에서 AliveTimer가 해제되어동작하지않음
		// 	ItsIso14827SessionMgr_setSessionAliveTimer( timer, session->key, 
		//	ItsIso14827SessionTimer_dereg(timer, session->key, SESSION_ALIVE_TIMER);
		// if ((err = ItsIso14827_loginReject(env->tSelf, domain->name, peer, user, Iso14827RejectLogin_accessDenied )).code) ERR_OUT(&err);
		// ItsIso14827SessionMgr_sessionDisconnect(env->sessionMgr, sTmr->key); // session key를 모르겠다		
		// ItsIcVMSDatextControl의 callBack함수 _control_authenticate가 post될시 VMSService쪽의 일련의 동작때문에 작업이 밀려 동작을안하는듯함
		if (domain->callback) 
		{
			if( domain->callback->disconnected)
				domain->callback->disconnected( domain->callback->param, domain->name, peer, user);  
		}

		ERR_SET_OUT(&err, ENOENT);
	}
	else
	{
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);

		if (session == NULL) ERR_SET_OUT(&err, ENOENT);
		else
		{
			ItsIso14827ServerDomainCallback *cbs = client->cb;
			session->codecRule = selectedCodec;
			session->CRCCheck = CRCMode;

			if (violatedPub != NULL)
			{
				ItsIso14827ServerDomainViolatedPublication_delAndSetNull(&client->violatedPub);
				client->violatedPub = ItsIso14827ServerDomainViolatedPublication_clone(violatedPub, NULL);
			}

			// Login 성공->결과를 통보
			ItsIso14827ServerDomainClientEntry_sendAcceptLogin(client, domain->name, session,
															client->loginPktNbr, selectedCodec,
															domain->hdr_opt_flag, uArg, uRsc, timer);
			// Retried Packet 처리
			if (client->loginRetriedPktNbr != NULL)
			{
				pthread_cleanup_push(Dz1u32_delAndSetNull, (void *)&client->loginRetriedPktNbr);
				ItsIso14827ServerDomainClientEntry_sendAcceptLogin(client, domain->name, session,
																*client->loginRetriedPktNbr, selectedCodec,
																domain->hdr_opt_flag, uArg, uRsc, timer);
				pthread_cleanup_pop(1); // (Dz1u32_delAndSetNull, (void *)&client->loginRetriedPktNbr);
			}

			// Heart-Beat Timer 등록
			ItsIso14827ServerDomainTimer_reg(timer, domain->name, client->peer, client->user,
											DOMAIN_HEARTBEAT_DURATION_TIMER,
											(u64_t)1000000 * client->heartBeadPeriod,
											ItsIso14827DomainMgr_heartBeatDurationTimeout);

			if (cbs->established) cbs->established(cbs->param, domain->name, client->peer, client->user, session->codecRule);

			client->state = ItsIso14827ServerDomainClientState_established;
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Login Reject
///////////////////////////////////////////////////////////////////////////////
ItsIso14827SessionKey *ItsIso14827ServerDomain_loginReject(ItsIso14827ServerDomain *domain,
														   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														   Iso14827RejectLogin reason,
														   void *uArg, void *uRsc, void *timer, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ItsIso14827SessionKey *ret = NULL;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry *client = _extractClientByPeerUser(domain, peer, user);
	if (client == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		ItsIso14827SessionEntry *session = NULL;
		DomainTimerCleanupArg _arg = { client, domain->name, timer };
		pthread_cleanup_push(ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);
		pthread_cleanup_push(_ItsIso14827ServerDomainClientEntry_timerCleanup, (void *)&_arg);

		if ((session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key)) == NULL) { }
		else
		{
			ret = client->key; client->key = NULL;
			// Login 실패 -> 결과를 통보
			ItsIso14827ServerDomainClientEntry_sendRejectLogin(client, domain->name, session,
															client->loginPktNbr, reason,
															domain->hdr_opt_flag, uArg, uRsc, timer);
			if (client->loginRetriedPktNbr != NULL)
			{
				pthread_cleanup_push(Dz1u32_delAndSetNull, (void *)&client->loginRetriedPktNbr);
				ItsIso14827ServerDomainClientEntry_sendRejectLogin(client, domain->name, session,
																*client->loginRetriedPktNbr, reason,
																domain->hdr_opt_flag, uArg, uRsc, timer);
				pthread_cleanup_pop(1); // (Dz1u32_delAndSetNull, (void *)&client->loginRetriedPktNbr);
			}
		}

		pthread_cleanup_pop(1); // (_ItsIso14827ServerDomainClientEntry_timerCleanup, (void *)&_arg);
		pthread_cleanup_pop(1); // (ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Echo Reply
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomain_echoReply(ItsIso14827ServerDomain *domain,
										   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
										   u32_t confirmPktNbr,
										   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->find(domain->clients, &key);
	if (client == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);
		ItsIso14827ServerDomainClientEntry_sendFrED(client, domain->name, session,
													confirmPktNbr, NULL,
													domain->hdr_opt_flag, uArg, uRsc, timer);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Prepare Accept
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomain_prepareAccept(ItsIso14827ServerDomain *domain, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t serial, void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->find(domain->clients, &key);
	if (client == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);
		if ((err = ItsIso14827ServerDomainClientEntrySubscription_accept(client, domain->name, session, serial, uArg, uRsc, timer)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Prepare Reject
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomain_prepareReject(ItsIso14827ServerDomain *domain,
											   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
											   u32_t serial, Iso14827RejectSubscription reason,
											   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->find(domain->clients, &key);
	if (client == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);
		if ((err = ItsIso14827ServerDomainClientEntrySubscription_reject(client, domain->name, session,
																		 serial, reason,
																		 uArg, uRsc, timer)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Data Provide
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomain_dataProvide(ItsIso14827ServerDomain *domain,
											 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
											 u32_t serial, Iso14827EndAppMsg **eam,
											 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->find(domain->clients, &key);
	if (client == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);
		if ((err = ItsIso14827ServerDomainClientEntrySubscription_publication(client, domain->name, session,
																			  serial, eam,
																			  uArg, uRsc, timer)).code) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Data Control
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomain_dataControl(ItsIso14827ServerDomain *domain,
											 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
											 u32_t serial, Iso14827PublicationMgmt cmd,
											 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->find(domain->clients, &key);
	if (client == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);
		if ((err = ItsIso14827ServerDomainClientEntrySubscription_pubControl(client, domain->name, session,
																			 serial, cmd,
																			 uArg, uRsc, timer)).code) ERR_OUT(&err);
	}
	return err;
}

Dz1Error ItsIso14827ServerDomain_violatedPub(ItsIso14827ServerDomain *domain, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
											 Iso14827Publication **pub, void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->find(domain->clients, &key);
	if (client == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		Iso14827PDUs *pdu = NULL;
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);
		if (session == NULL) ERR_SET_OUT(&err, EPIPE);
		else if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_publication, (*pub), &err)) == NULL) ERR_OUT(&err);
		else
		{
			bool_t guranteed = (*pub)->guaranteed;
			(*pub) = NULL;
			pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
			if ((err = ItsIso14827Domain_send(client->txFifo, session, ItsIso14827DomainType_server, domain->hdr_opt_flag,
											  domain->name, client->peer, client->user, NULL, 
											  client->responseWaitTime, client->heartBeadPeriod, 1,
											  &pdu, guranteed, NULL, uArg, uRsc, timer)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
		}
	}
	return err;
}

Dz1Error ItsIso14827ServerDomain_violatedSub(ItsIso14827ServerDomain *domain,
											 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
											 Iso14827Subscription **sub,
											 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->find(domain->clients, &key);
	if (client == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		Iso14827PDUs *pdu = NULL;
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);
		if (session == NULL) ERR_SET_OUT(&err, EPIPE);
		else if ((pdu = Iso14827PDUs_new(Iso14827PDUsPresent_subscription, (*sub), &err)) == NULL) ERR_OUT(&err);
		else
		{
			(*sub) = NULL;
			pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&pdu);
			if ((err = ItsIso14827Domain_send(client->txFifo, session, ItsIso14827DomainType_server,
											  domain->hdr_opt_flag, 
											  domain->name, client->peer, client->user, NULL,
											  client->responseWaitTime, client->heartBeadPeriod, 1,
											  &pdu,			// pdu
											  FALSE,		// need_wait
											  NULL,			// ItsIso14827DomainTxFail
											  uArg, uRsc, timer)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (Iso14827PDUs_delAndSetNull, (void *)&pdu);
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Terminate Client : Terminate 를 Client 로 전송
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827ServerDomain_terminateClient(ItsIso14827ServerDomain *domain,
												 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
												 Iso14827Terminate reason,
												 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ServerDomainClientEntry key = { peer, user }, *client = domain->clients->find(domain->clients, &key);
	if (client == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		ItsIso14827SessionEntry *session = ItsIso14827SessionMgr_find(env->sessionMgr, client->key);
		ItsIso14827ServerDomainClientEntry_sendTerminate(client, domain->name, session, reason, domain->hdr_opt_flag, uArg, uRsc, timer);
		ItsIso14827SessionMgr_setSessionAliveTimer(timer, client->key, (u64_t)30000000);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Session이 끊어져서 user@PEER만 사라지는 경우
void ItsIso14827ServerDomain_sessionDisconnected(ItsIso14827ServerDomain *p, ItsIso14827SessionKey *skey, void *timer)
{
	ItsIso14827ServerDomainClientEntry *client = _extractClientBySession(p, skey);
	if (client)
	{
		pthread_cleanup_push(ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);

		Dz1Thread_printf("ItsIso14827ServerDomain_sessionDisconnected() = ");
		ItsIso14827ServerDomainClientEntry_dump(client, 0);

		ItsIso14827ServerDomainClientEntry_timerCleanup(client, p->name, timer);

		pthread_cleanup_pop(1); // (ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Heart-Beat Duration이 지나서 user@PEER를 제거하는 경우
ItsIso14827SessionKey *ItsIso14827ServerDomain_expireSession(ItsIso14827ServerDomain *p, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, void *timer)
{
	ItsIso14827SessionKey *ret = NULL;
	ItsIso14827ServerDomainClientEntry *client = _extractClientByPeerUser(p, peer, user);
	if (client)
	{
		pthread_cleanup_push(ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);

		Dz1Thread_printf("ItsIso14827ServerDomain_expireSession() = ");
		ItsIso14827ServerDomainClientEntry_dump(client, 0);

		ret = client->key; client->key = NULL;
		ItsIso14827ServerDomainClientEntry_timerCleanup(client, p->name, timer);

		pthread_cleanup_pop(1); // (ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&client);
	}
	// Session Key를 돌려주면 Session Manager에게 접종 명령을 내린다.
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Application이 Domain을 삭제하는 경우
void ItsIso14827ServerDomain_delete(ItsIso14827ServerDomain *p)
{	// p는 지우면 안됨
	if (p == NULL) return;
}

///////////////////////////////////////////////////////////////////////////////
// Task가 종료될 때
void ItsIso14827ServerDomain_terminate(ItsIso14827ServerDomain *p)
{	// 상위 함수에서 삭제를 함으로
	if (p == NULL) return;
	// 할 일이 엄따...;;
}
