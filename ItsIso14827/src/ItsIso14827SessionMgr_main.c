#include "ItsIso14827Env.h"

#include <Iso14827dz1_assist.h>

#include <ItsIso14827.h>
#include "ItsIso14827TimerUtil.h"
#include "ItsIso14827SocketAcceptor.h"
#include "ItsIso14827SocketAcceptorMsg.h"
#include "ItsIso14827SocketReceiver.h"
#include "ItsIso14827SocketReceiverMsg.h"
#include "ItsIso14827DomainMgr_main.h"
//#include "ItsIso14827ServerSessionFSM.h"
//#include "ItsIso14827ClientSessionFSM.h"
#include "ItsIso14827SessionMgr_main.h"

static void *ItsIso14827SocketHookArg = NULL;
static void (*ItsIso14827SocketHookFunc)(void *hookArg, Iso14827C2CAuthMsg *msg, bool_t *isReceived) = NULL;

void ItsIso14827SocketHook_set(void (*hook_func)(void *hook_arg, Iso14827C2CAuthMsg *msg, bool_t *isReceived), void *hook_arg)
{
	ItsIso14827SocketHookArg = hook_arg;
	ItsIso14827SocketHookFunc = hook_func;
}

#define ISO14827_MTU_DEFAULT				0x4000

/******************************************************************************
Session Manager의 역활
- Socket Receiver가 Forward한 Data수집
- Datex Data Packet을 Decode하여 CRC 확인
- Datex Data Packet의 Data를 Decode하여 C2C Authenticate Message 추출
- C2C Authenticate Message Sequence를 확인하여
  정상 수신 PDU인지 Retried PDU인지 구별
- 이상 없으면 Domain Manager에게 Forward
******************************************************************************/

static Dz1Error _makeSureAuthInfo(Iso14827C2CAuthMsg *msg, Dz1Asn1OctetStr *authInfo)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (authInfo == NULL)
	{
		if ((msg->authInfo = Dz1Asn1OctetStr_new((u8_t *)" ", 1, &err)) == NULL) ERR_OUT(&err);
		else msg->authInfo->size = 0;
	}
	else
	{
		if ((msg->authInfo = Dz1Asn1OctetStr_clone(authInfo, &err)) == NULL) ERR_OUT(&err);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Session Entry Cleanup
///////////////////////////////////////////////////////////////////////////////
static void ItsIso14827SessionEntry_timerCleanup(ItsIso14827SessionEntry *p)
{
	ItsIso14827SessionTimer_dereg(p->timer, p->key, SESSION_ALIVE_TIMER);
}

static void _sessionInitiatorCleanup(ItsIso14827SessionEntry *p, Dz1Error *reason)
{
	if (p->initiator != NULL)
	{
		Dz1Error *status = Dz1TaskSigMsg_getErrPtr(p->initiator);
		memcpy(status, reason, sizeof(Dz1Error));
		Dz1TaskSigMsg_termDelAndSetNull(&p->initiator);
	}
}

///////////////////////////////////////////////////////////////////////////////
// 연결이 끊겼을 때
void _ItsIso14827SessionEntry_cleanup(ItsIso14827SessionEntry *p)
{	// Just Cleanup
	if (p == NULL) return;
	else
	{
		ItsIso14827Env *env = (ItsIso14827Env *)p->uRsc;

		Dz1Error status = DZ1_ERROR_INITIALIZER;
		Dz1Error_set(&status, EPIPE);
		_sessionInitiatorCleanup(p, &status);

		ItsIso14827DomainMgr_sessionDisconnected(env->domainMgr, p->key, p->timer);

		if (p->receiver != -1) ItsIsoSocketReceiver_stop(p->receiver);
		p->receiver = -1;
		Dz1TcpClientSocket_closeAndSetNull(&p->sock);

		ItsIso14827SessionEntry_timerCleanup(p);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Task가 종료 될 때
// Session을 종료 시킬 때
void _ItsIso14827SessionEntry_terminate(ItsIso14827SessionEntry *p)
{	// Just Cleanup
	if (p == NULL) return;
	else
	{
		Dz1Error status = DZ1_ERROR_INITIALIZER;
		Dz1Error_set(&status, EINTR);
		_sessionInitiatorCleanup(p, &status);

		if (p->receiver != -1) ItsIsoSocketReceiver_stop(p->receiver);
		p->receiver = -1;
		Dz1TcpClientSocket_closeAndSetNull(&p->sock);
		ItsIso14827SessionEntry_timerCleanup(p);
	}
}

///////////////////////////////////////////////////////////////////////////////
// 연결이 끊겼을 때
void ItsIso14827SessionEntry_cleanup(ItsIso14827SessionEntry *p)
{	// Cleanup + Delete
	if (p == NULL) return;
	_ItsIso14827SessionEntry_cleanup(p);
	ItsIso14827SessionEntry_del(p);
}

///////////////////////////////////////////////////////////////////////////////
// Session List Cleanup
/*
static Dz1Error _ItsIso14827SessionMgr_cleanupSessions(void *ptr, ItsIso14827SessionEntry *p)
{	// Travel Function -> Just Cleanup
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_ItsIso14827SessionEntry_cleanup(p);
	return err;
}
*/
///////////////////////////////////////////////////////////////////////////////
// Task가 종료 될 때
static Dz1Error _ItsIso14827SessionMgr_terminateSessions(void *ptr, ItsIso14827SessionEntry *p)
{	// Travel Function -> Just Cleanup
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_ItsIso14827SessionEntry_terminate(p);
	return err;
}
///////////////////////////////////////////////////////////////////////////////
// CRC Checker
static bool_t _CRC_Check(Dz1Asn1OctetStr *msg, u16_t crc, ItsIso14827CRCCheck opt)
{
	bool_t ret = TRUE;
	u16_t _crc = 0;
	switch(opt)
	{
	default:
	case ItsIso14827CRCCheck_explict:	// CRC 검사 함
	case ItsIso14827CRCCheck_warning:	// CRC 검사 하지만 틀릴 경우 경고만
		_crc = Iso3309Crc(msg->data, msg->size);
		if (_crc != crc)
		{
			Dz1Thread_printf("_CRC_Check() : CRC Mismatch!!! %04X != %04X\n", crc, _crc);
			if (opt == ItsIso14827CRCCheck_explict) ret = FALSE;
		}
		break;
	case ItsIso14827CRCCheck_ignore:	// CRC 검사 안함
		break;
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Packet Number Checker
static Dz1Error _PktNbr_Check(ItsIso14827SessionEntry *e, Iso14827C2CAuthMsg *c2c, bool_t *isRetried)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	bool_t _isRetried = FALSE, *isrp = isRetried ? isRetried : &_isRetried;

	if (e->rxSerial == NULL)
	{	// 첫 Packet 인 경우 Packet Number 저장
		if ((e->rxSerial = Dz1u32_new(c2c->pktNbr, &err)) == NULL) ERR_OUT(&err);
		else *isrp = FALSE;
	}
	else
	{
		u32_t last_pkt_nbr = *e->rxSerial, expect_pkt_nbr = last_pkt_nbr + 1;
		if (expect_pkt_nbr == c2c->pktNbr)
		{
			*isrp = FALSE;			// 정상적인 경우
			(*e->rxSerial) = c2c->pktNbr; // 새로운 값 저장
		}
		else if (c2c->pktNbr <= last_pkt_nbr)						// 지난번 Packet Number 와 같거나 작음 -> Retry한 Packet
		{
			Dz1Thread_printf("_PktNbr_Check() : Retried Packet\n");
			*isrp = TRUE;
		}
		else if (expect_pkt_nbr < 3 && (c2c->pktNbr & 0x80000000))	// overflow 값 근처에서 Retry 가 일어난 경우
		{
			Dz1Thread_printf("_PktNbr_Check() : Retried Packet\n");
			*isrp = TRUE;
		}
		else
		{	// Retry 도 아니고 정상 순서도 아니면 경고
			Dz1Thread_printf("_PktNbr_Check() : Packet Lost(?) = except = %u, received = %u\n", *e->rxSerial, c2c->pktNbr);
			*isrp = FALSE;
			(*e->rxSerial) = c2c->pktNbr; // 새로운 값 저장
		}
	}
	return err;
}

static void _pdu_dump(str_t prefix, Iso14827PDUs *pdu, u32_t flag, u32_t pktNbr)
{
	if (flag & ITS_ISO14827_PACKET_DUMP_PDU)
	{
		Dz1Thread_printf("%s PDU = ", prefix);
		Iso14827PDUs_dump(pdu, 0);
	}
	else
	{
		switch(pdu->present)
		{
		case Iso14827PDUsPresent_initiate:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_INITIATE)
			{
				Dz1Thread_printf("%s [%u] Initiate = ", prefix), pktNbr;
				Iso14827Initiate_dump(pdu->x.initiate, 0);
			}
			break;
		case Iso14827PDUsPresent_login:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_LOGIN)
			{
				Dz1Thread_printf("%s [%u] Login = ", prefix, pktNbr);
				Iso14827Login_dump(pdu->x.login, 0);
			}
			break;
		case Iso14827PDUsPresent_fred:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_FRED)
				Dz1Thread_printf("%s [%u] FrED = %u\n", prefix, pktNbr, pdu->x.fred);
			break;
		case Iso14827PDUsPresent_term:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_TERM)
				Dz1Thread_printf("%s [%u] Terminate = %s(%d)\n", prefix, pktNbr, Iso14827TerminateStr(pdu->x.term), pdu->x.term);
			break;
		case Iso14827PDUsPresent_logout:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_LOGOUT)
				Dz1Thread_printf("%s [%u] Logout = %s(%d)\n", prefix, pktNbr, Iso14827LogoutStr(pdu->x.logout), pdu->x.logout);
			break;
		case Iso14827PDUsPresent_subscription:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_SUBSCRIPTION)
			{
				Dz1Thread_printf("%s [%u] Subscription = ", prefix, pktNbr);
				Iso14827Subscription_dump(pdu->x.subscription, 0);
			}
			break;
		case Iso14827PDUsPresent_publication:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_PUBLICATION)
			{
				Dz1Thread_printf("%s [%u] Publication = ", prefix, pktNbr);
				Iso14827Publication_dump(pdu->x.publication, 0);
			}
			break;
		case Iso14827PDUsPresent_transferDone:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_TRANSFER_DONE)
			{
				Dz1Thread_printf("%s [%u] TransferDone = ", prefix, pktNbr);
				Iso14827TransferDone_dump(pdu->x.transferDone, 0);
			}
			break;
		case Iso14827PDUsPresent_ack:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_ACCEPT)
			{
				Dz1Thread_printf("%s [%u] Accept = ", prefix, pktNbr);
				Iso14827Accept_dump(pdu->x.ack, 0);
			}
			break;
		case Iso14827PDUsPresent_nak:
			if (flag & ITS_ISO14827_PACKET_DUMP_PDU_REJECT)
			{
				Dz1Thread_printf("%s [%u] Reject = ", prefix, pktNbr);
				Iso14827Reject_dump(pdu->x.nak, 0);
			}
			break;
		default:
			break;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// Received API
static Dz1Error _ItsIso14827SessionMgr_received(ItsIso14827SessionEntry *e, void *uArg, void *uRsc, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ssize_t status = 0, __sz = 0;
	Dz1Asn1OctetStr *msg = NULL;
	Iso14827C2CAuthMsg *c2c = NULL;
	Iso14827DatexDataPacket *datex = NULL;

	Dz1Binary *bin = NULL;
	while(errp->code == 0 && (__sz = Dz1ElasticBuf_getDataSize(e->buf, NULL)) > 0)
	{
		if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(e->buf, errp)) == NULL) ERR_OUT(errp);
		else if ((status = Iso14827DatexDataPacket_decode(&datex, bin->data, bin->size, e->codecRule, NULL)) > 0)
		{
			pthread_cleanup_push(Iso14827DatexDataPacket_delAndSetNull, (void *)&datex);
			Dz1ElasticBuf_pop(e->buf, NULL, status, NULL);

			if (env->pktDumpFlag & ITS_ISO14827_PACKET_DUMP_DATEX) { Dz1Thread_printf("<<< DatexMSG = "); Iso14827DatexDataPacket_dump(datex, 0); }

			msg = datex->data;
			// CRC check
			if (_CRC_Check(msg, datex->crc16, e->CRCCheck) == FALSE) ERR_SET_OUT(&err, EINVAL);
			// Decode
			else if (Iso14827C2CAuthMsg_decode(&c2c, msg->data, msg->size, e->codecRule, &err) < 0) ERR_OUT(&err);
			else
			{
				bool_t isRetried = FALSE;
				pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&c2c);

				/////////////////////////
				// debugging dump & hook
				if (env->pktDumpFlag & ITS_ISO14827_PACKET_DUMP_C2CAUTH) { Dz1Thread_printf("<<< C2CMsg = "); Iso14827C2CAuthMsg_dump(c2c, 0); }
				_pdu_dump((str_t)"<<<", c2c->pdu, env->pktDumpFlag, c2c->pktNbr);

				if (ItsIso14827SocketHookFunc != NULL)
				{
					bool_t isReceived = TRUE;
					ItsIso14827SocketHookFunc(ItsIso14827SocketHookArg, c2c, &isReceived);
				}
				// debugging dump & hook
				/////////////////////////

				// Packet Number Check
				if ((err = _PktNbr_Check(e, c2c, &isRetried)).code) ERR_OUT(&err); 
				// just forward to domain manager
				else if ((err = ItsIso14827DomainMgr_received(env->domainMgr, e, c2c->authInfo, c2c->pktNbr, c2c->priority, c2c->pdu, isRetried, uArg, uRsc, timer)).code) ERR_OUT(&err);

				pthread_cleanup_pop(1); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&c2c);
			}
			pthread_cleanup_pop(1); // (Iso14827DatexDataPacket_delAndSetNull, (void *)&datex);
		}
	}
	return err;
}

static Dz1Error ItsIso14827SessionMgr_received(ItsIso14827SessionMgr *mgr,
											   ItsIso14827SessionKey *_key, Dz1Binary *packet,
											   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;


	ItsIso14827SessionEntry key = { _key }, *e = mgr->sessions->extract(mgr->sessions, &key);
	if (e != NULL)
	{
		pthread_cleanup_push(ItsIso14827SessionEntry_cleanupAndSetNull, (void *)&e);

		if (mgr->debug_dump)
		{
			Dz1Thread_printf("<<< Session Received(%u Bytes)\n", packet->size);
			Dz1Thread_tprintb(1, packet->data, packet->size > 64 ? 64 : packet->size, 16, FALSE);
		}

		if (_Dz1ElasticBuf_push(e->buf, packet->data, packet->size, &err) == FALSE) ERR_OUT(&err);
		else if ((err = _ItsIso14827SessionMgr_received(e, uArg, uRsc, timer)).code) ERR_OUT(&err);
		else if ((err = mgr->sessions->add(mgr->sessions, e)).code) ERR_OUT(&err);
		else e = NULL;

		pthread_cleanup_pop(1); // (ItsIso14827SessionEntry_cleanupAndSetNull, (void *)&e);
	}

	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Received Message Handler
static Dz1TaskProcStatus _sessionReceived(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827SessionMgr *mgr = env->sessionMgr;

	ItsIsoSocketReceiverReceived *msg = (ItsIsoSocketReceiverReceived *)Dz1TaskSigMsg_getData(*sg);
	if ((*errp = ItsIso14827SessionMgr_received(mgr, msg->key, msg->packet, uArg, uRsc, timer)).code) ERR_OUT(errp);

	return ret;
}

static Dz1TaskProcStatus _sessionAliveTimeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827Timer *tmr = (ItsIso14827Timer *)(*tData);
	ItsIso14827SessionTimer *sTmr = tmr->x.session;

	Dz1Thread_printf("!!! Session Alive Timeout = "); ItsIso14827SessionTimer_dump(sTmr, 0);
	ItsIso14827SessionMgr_sessionDisconnect(env->sessionMgr, sTmr->key);

	return ret;
}

Dz1Error ItsIso14827SessionMgr_setSessionAliveTimer(void *timer, ItsIso14827SessionKey *skey, u64_t duration_us)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Thread_printf("### Register SESSION Alive Timer = "); ItsIso14827SessionKey_dump(skey, 0);
	if ((err = ItsIso14827SessionTimer_reg(timer, skey, SESSION_ALIVE_TIMER, duration_us, _sessionAliveTimeout)).code) ERR_OUT(&err);
	return err;
}

static void _initiator_wakeup(void *ptr)
{
	ItsIso14827SessionEntry *session = (ItsIso14827SessionEntry *)ptr;
	if (session->initiator != NULL)
	{
		Dz1Error *status = Dz1TaskSigMsg_getErrPtr(session->initiator);
		Dz1Error_set(status, EINTR);
		Dz1TaskSigMsg_termDelAndSetNull(&session->initiator);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Connected API
ItsIso14827SessionEntry *ItsIso14827SessionMgr_connected(ItsIso14827SessionMgr *mgr,
														 Dz1SockAddr *peer, Dz1SockAddr *local,
														 Dz1TcpClientSocket **sock,
														 Dz1Asn1Codec initialCodec,
														 ItsIso14827CRCCheck CRCCheck,
														 void **initiatorSG,
														 void *uArg, void *uRsc, void *timer,
														 Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827SessionEntry *ret = NULL;
	ItsIso14827SessionEntry *session = ItsIso14827SessionEntry_new(NULL, (*sock), -1, NULL,
																   initialCodec, CRCCheck,
																   initiatorSG != NULL ? (*initiatorSG) : NULL,
																   uRsc, timer, errp);
	if (session == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827SessionKey *key = NULL;

		(*sock) = NULL;
		if (initiatorSG != NULL) (*initiatorSG) = NULL;
		pthread_cleanup_push(ItsIso14827SessionEntry_delAndSetNull, (void *)&session);
		pthread_cleanup_push(_initiator_wakeup, (void *)session);
		// Make sure KEY
		if ((session->key = key = ItsIso14827SessionKey_new(NULL, NULL, mgr->allocSID++, errp)) == NULL) ERR_OUT(errp);
		else if ((key->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((key->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		// Create Buffer
//		else if ((session->buf = Dz1SocketBuf_new(ISO14827_MTU_DEFAULT, errp)) == NULL) ERR_OUT(errp);
		else if ((session->buf = Dz1ElasticBuf_new(2048, FALSE, errp)) == NULL) ERR_OUT(errp);
		// Receiver Start
		else if ((session->receiver = ItsIsoSocketReceiver_start(env->tSelf, key->peer, key->local, session->sock, key->sid, errp)) == -1) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1SocketReceiver_startCancel, (void *)&session->receiver);

			// just session add
			if ((*errp = ItsIso14827SessionMgr_setSessionAliveTimer(timer, session->key, (u64_t)5 * 1000000)).code) ERR_OUT(errp);
			else if ((*errp = mgr->sessions->add(mgr->sessions, session)).code) ERR_OUT(errp);
			else { ret = session; session = NULL; }

			pthread_cleanup_pop(errp->code); // (Dz1SocketReceiver_startCancel, (void *)&session->receiver);
		}
		pthread_cleanup_pop(errp->code); // (_initiator_wakeup, (void *)session);
		pthread_cleanup_pop(1); // (ItsIso14827SessionEntry_delAndSetNull, (void *)&session);
	}
	return ret;
}

ItsIso14827SessionEntry	*ItsISo14827SessionMgr_connect(ItsIso14827SessionMgr *mgr,
													   Dz1SockAddr *peer, size_t datagramSize,
													   Dz1Asn1Codec initialCodec,
													   ItsIso14827CRCCheck initialCRCMode,
													   void *uRsc, void *timer, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827SessionEntry *ret = NULL, *node = ItsIso14827SessionEntry_new(NULL, NULL, -1, NULL,
																			 initialCodec, initialCRCMode,
																			 NULL,
																			 uRsc, timer, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockAddr local;
		struct timeval to = { 3, 0 };
		ItsIso14827SessionKey *key = NULL;

		pthread_cleanup_push(ItsIso14827SessionEntry_delAndSetNull, (void *)&node);

		if (datagramSize == 0) datagramSize = 65535;

		if ((*errp = Dz1SockAddr_setAddrStr(&local, (str_t)"0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(errp);
		else if ((node->key = key = ItsIso14827SessionKey_new(NULL, NULL, mgr->allocSID, errp)) == NULL) ERR_OUT(errp);
		else if ((key->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((node->sock = Dz1TcpClientSocket_open(peer, &local, &to, errp)) == NULL) ERR_OUT(errp);
		else if ((key->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
//		else if ((node->buf = Dz1SocketBuf_new(datagramSize, errp)) == NULL) ERR_OUT(errp);
		else if ((node->buf = Dz1ElasticBuf_new(2048, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((node->receiver = ItsIsoSocketReceiver_start(env->tSelf, key->peer, key->local, node->sock, key->sid, errp)) == -1) ERR_OUT(errp);
		else if ((*errp = ItsIso14827SessionMgr_setSessionAliveTimer(timer, key, (u64_t)5 * 1000000)).code) ERR_OUT(errp);
		else if ((*errp = mgr->sessions->add(mgr->sessions, node)).code) ERR_OUT(errp);
		else { ret = node; node = NULL; }

		pthread_cleanup_pop(1); // (ItsIso14827SessionEntry_delAndSetNull, (void *)&node);
	}
	return ret;													
}

///////////////////////////////////////////////////////////////////////////////
// Connected Message Handler
static Dz1TaskProcStatus _sessionConnected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIsoAcceptorConnected *msg = (ItsIsoAcceptorConnected *)Dz1TaskSigMsg_getData(*sg);

	if (ItsIso14827SessionMgr_connected(env->sessionMgr,
										msg->peer, msg->local, &msg->sock,
										msg->initialCodec,
										msg->CRCCheck,
										NULL, uArg, uRsc, timer, errp) == NULL) ERR_OUT(errp);
	return ret;
}

static Dz1Error ItsIso14827SessionMgr_disconnected(ItsIso14827SessionMgr *mgr, ItsIso14827SessionKey *skey,
												   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	//ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827SessionEntry key = { skey }, *node = mgr->sessions->extract(mgr->sessions, &key);
	if (node) ItsIso14827SessionEntry_cleanup(node);
	return err;
}

static Dz1TaskProcStatus _sessionDisconnected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;

	ItsIso14827SessionKey *msg = (ItsIso14827SessionKey *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827SessionMgr_disconnected(env->sessionMgr, msg, uArg, uRsc, timer)).code) ERR_OUT(errp);

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Session Manager Init
ItsIso14827SessionMgr *ItsIso14827SessionMgr_init(void *tParent, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	ItsIso14827SessionMgr *ret = ItsIso14827SessionMgr_new(Dz1Task_getQueueID(tParent), errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827SessionMgr_delAndSetNull, (void *)&ret);
		if ((*errp = Dz1Task_regMsg(tParent, DZ1_TASK_MSG_EXACT(ITS_ISO_SERVER_RECEIVER_RECEIVED), _sessionReceived)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tParent, DZ1_TASK_MSG_EXACT(ITS_ISO_SERVER_ACCEPTOR_CONNECTED), _sessionConnected)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tParent, DZ1_TASK_MSG_EXACT(ITS_ISO_SERVER_RECEIVER_EXCEPTION), _sessionDisconnected)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ItsIso14827SessionMgr_delAndSetNull, (void *)&ret);
	}

	return ret;
}

void ItsIso14827SessionMgr_sessionDisconnect(ItsIso14827SessionMgr *mgr, ItsIso14827SessionKey *skey)
{
	ItsIso14827SessionEntry key = { skey }, *node = mgr->sessions->extract(mgr->sessions, &key);
	if (node)
	{
		pthread_cleanup_push(ItsIso14827SessionEntry_delAndSetNull, (void *)&node);
		_ItsIso14827SessionEntry_terminate(node);
		pthread_cleanup_pop(1); // (ItsIso14827SessionEntry_del, (void *)node);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Accept Entry Cleanup
// Task가 종료 될 때
// Run-Time 중 Cancel시
// Port Close 시
static void _ItsIso14827AcceptorEntry_cleanup(ItsIso14827AcceptorEntry *p)
{	// Just Cleanup
	if (p == NULL) return;
	if (p->thID != -1) ItsIosSocketAcceptor_stop(p->thID);
	p->thID = -1;
}

///////////////////////////////////////////////////////////////////////////////
// Run-Time 중 Cancel시
static void ItsIso14827AcceptorEntry_cleanup(ItsIso14827AcceptorEntry *p)
{	// Cleanup + Delete
	if (p == NULL) return;
	_ItsIso14827AcceptorEntry_cleanup(p);
	ItsIso14827AcceptorEntry_del(p);
}
static void ItsIso14827AcceptorEntry_cleanupAndSetNull(void *ptr)
{
	ItsIso14827AcceptorEntry **p = (ItsIso14827AcceptorEntry **)ptr;
	ItsIso14827AcceptorEntry_cleanup(*p); *p = NULL;
}
///////////////////////////////////////////////////////////////////////////////

static ItsIso14827AcceptorEntry *_findAcceptorEntry(ItsIso14827SessionMgr *mgr, u16_t port)
{
	ItsIso14827AcceptorEntry *ret = NULL;

	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1SockAddr server;
	if ((err = Dz1SockAddr_setAddrStr(&server, (str_t)"0.0.0.0")).code) ERR_OUT(&err);
	else if ((err = Dz1SockAddr_setPort(&server, port)).code) ERR_OUT(&err);
	else
	{
		ItsIso14827AcceptorEntry key = { &server };
		ret = mgr->listener->find(mgr->listener, &key);
	}

	return ret;
}

Dz1Error ItsIso14827SessionMgr_openPort(ItsIso14827SessionMgr *mgr, u16_t port, Dz1Asn1Codec initialCodec, ItsIso14827CRCCheck initialCRCmode)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827AcceptorEntry *node = _findAcceptorEntry(mgr, port);

	if (node != NULL)
	{
		if (node->initial != initialCodec || node->CRCCheck != initialCRCmode)
			ERR_SET_OUT(&err, EINVAL);
		else node->ref++;
	}
	else
	{
		if ((node = ItsIso14827AcceptorEntry_new(NULL, -1, initialCodec, initialCRCmode, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1SockAddr server;
			pthread_cleanup_push(ItsIso14827AcceptorEntry_cleanupAndSetNull, (void *)&node);

			if ((err = Dz1SockAddr_setAddrStr(&server, (str_t)"0.0.0.0")).code) ERR_OUT(&err);
			else if ((err = Dz1SockAddr_setPort(&server, port)).code) ERR_OUT(&err);
			else if ((node->server = Dz1SockAddr_clone(&server, &err)) == NULL) ERR_OUT(&err);
			else if ((node->thID = ItsIosSocketAcceptor_start(mgr->myQueueID, node->server, node->initial, node->CRCCheck, &err)) == -1) ERR_OUT(&err);
			else if ((err = mgr->listener->add(mgr->listener, node)).code) ERR_OUT(&err);
			else
			{
				node->ref++;
				node = NULL;
			}
			pthread_cleanup_pop(1); // (ItsIso14827AcceptorEntry_cleanupAndSetNull, (void *)&node);
		}
	}
	return err;
}

void ItsIso14827SessionMgr_closePort(ItsIso14827SessionMgr *mgr, u16_t port)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SockAddr server;
	ItsIso14827AcceptorEntry key = { &server }, *node = NULL;
	if ((err = Dz1SockAddr_setAddrStr(&server, (str_t)"0.0.0.0")).code) ERR_OUT(&err);
	else if ((err = Dz1SockAddr_setPort(&server, port)).code) ERR_OUT(&err);
	else if ((node = mgr->listener->find(mgr->listener, &key)) != NULL)
	{
		node->ref--;
		if (node->ref <= 0)
		{
			mgr->listener->extract(mgr->listener, &key);
			pthread_cleanup_push(ItsIso14827AcceptorEntry_delAndSetNull, (void *)&node);
			_ItsIso14827AcceptorEntry_cleanup(node);
			pthread_cleanup_pop(1); // (ItsIso14827AcceptorEntry_del, (void *)node);
		}
	}
}

ItsIso14827SessionEntry *ItsIso14827SessionMgr_find(ItsIso14827SessionMgr *mgr, ItsIso14827SessionKey *skey)
{
	ItsIso14827SessionEntry key = { skey };
	return mgr->sessions->find(mgr->sessions, &key);
}

///////////////////////////////////////////////////////////////////////////////
// Session Acceptor Cleanup
// Task가 종료 될 때
static Dz1Error _ItsIso14827SessionMgr_terminateServers(void *ptr, ItsIso14827AcceptorEntry *p)
{	// Travel Function -> Just Cleanup
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_ItsIso14827AcceptorEntry_cleanup(p);
	return err;
}
 
///////////////////////////////////////////////////////////////////////////////
// Session Manager Terminate
// Task가 종료 될 때
void ItsISo14827SessionMgr_terminate(ItsIso14827SessionMgr *p)
{
	if (p == NULL) return;

	p->sessions->travel(p->sessions, _ItsIso14827SessionMgr_terminateSessions, NULL);
	p->listener->travel(p->listener, _ItsIso14827SessionMgr_terminateServers, NULL);

	ItsIso14827SessionMgr_del(p);
}






///////////////////////////////////////////////////////////////////////////////
// Encode And Send
///////////////////////////////////////////////////////////////////////////////
#define ISO14827HDROPT_SENDER				0x80000000
#define ISO14827HDROPT_SENDER_ADDR			0x40000000
#define ISO14827HDROPT_DEST					0x20000000
#define ISO14827HDROPT_DEST_ADDR			0x10000000
#define ISO14827HDROPT_COST					0x08000000
#define ISO14827HDROPT_TIME					0x04000000

static Dz1Asn1OctetStr *_encode_sock_addr(Dz1SockAddr *addr, Dz1Error *err)
{
	Dz1Asn1OctetStr *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	u8_t buf[32] = { 0, };
	size_t sz = 32;
	if ((*errp = Dz1SockAddr_getAddr(addr, buf, &sz)).code) ERR_OUT(errp);
	else
	{
		u8_t *cp = buf + sz;
		u16_t port = 0;
		Dz1SockAddr_getPort(addr, &port);
		*cp++ = (u8_t)((port >> 8) & 0xFF); sz++;
		*cp++ = (u8_t)(port & 0xFF); sz++;
		if ((ret = Dz1Asn1OctetStr_new(buf, (u32_t)sz, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	return ret;
}

static Dz1Error _hdr_opt_proc(Iso14827HdrOpt *dst, u8_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest, ItsIso14827SessionKey *skey)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (hdr_opt_flag & ISO14827HDROPT_SENDER)		dst->sender		= sender == NULL ? NULL : Dz1Asn1UTF8Str_clone(sender, NULL);
	if (hdr_opt_flag & ISO14827HDROPT_DEST)			dst->dest		= dest == NULL ? NULL : Dz1Asn1UTF8Str_clone(dest, NULL);

	if (hdr_opt_flag & ISO14827HDROPT_SENDER_ADDR)	dst->senderAddr = _encode_sock_addr(skey->local, NULL);
	if (hdr_opt_flag & ISO14827HDROPT_DEST_ADDR)	dst->destAddr	= _encode_sock_addr(skey->peer, NULL);

	if (hdr_opt_flag & ISO14827HDROPT_COST)			Dz1Thread_printf("### Header Option COST not support\n");

	if (hdr_opt_flag & ISO14827HDROPT_TIME)			dst->t			= Iso14827Time_get(NULL, ISO14827TIME_FLAG_UTC, NULL);
	Dz1Error_set(errp, 0);
	return err;
}


static Dz1Error ItsIso14827Socket_encodeAndSend(Dz1TcpClientSocket *sock, Iso14827C2CAuthMsg *msg, Dz1Asn1Codec codec,
												u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest,
												ItsIso14827SessionKey *skey, u32_t dumpFlag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u8_t *buf = NULL;
//	Iso14827HdrOpt *opt = msg->hdrOpt;
	ssize_t size = 0;
	if ((*errp = _hdr_opt_proc(msg->hdrOpt, hdr_opt_flag, sender, dest, skey)).code) ERR_OUT(errp);
	else if ((size = Iso14827C2CAuthMsg_encodeDatex(msg, &buf, codec, errp)) < 0) ERR_OUT(errp);
	else if (size == 0) ERR_SET_OUT(errp, EPIPE);
	else
	{
		struct timeval to = { 10, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);

		_pdu_dump((str_t)">>>", msg->pdu, dumpFlag, msg->pktNbr);

		if (dumpFlag & ITS_ISO14827_PACKET_DUMP_C2CAUTH)
		{
			Dz1Thread_printf(">>> C2CMsg = ");
			Iso14827C2CAuthMsg_dump(msg, 0);
		}

		if (dumpFlag & ITS_ISO14827_SESSION_DUMP)
		{
			Dz1Thread_printf(">>> Session Send(%u Bytes)\n", size);
			Dz1Thread_tprintb(1, buf, size > 64 ? 64 : size, 16, FALSE);
		}

		if (sock->send(sock, buf, size, DZ1_TCP_SOCK_FLAG_COMPLETE, &to, errp) < 0) ERR_OUT(errp);
		else
		{
			if (ItsIso14827SocketHookFunc != NULL)
			{
				bool_t isReceived = FALSE;
				ItsIso14827SocketHookFunc(ItsIso14827SocketHookArg, msg, &isReceived);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
	}
	return err;
}

Dz1Error ItsIso14827SessionEntry_encodeAndSend(ItsIso14827SessionEntry *e, Iso14827C2CAuthMsg *msg,
											   u32_t hdr_opt_flag, Dz1Asn1OctetStr *sender, Dz1Asn1OctetStr *dest, 
											   u32_t dumpFlag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((err = ItsIso14827Socket_encodeAndSend(e->sock, msg, e->codecRule,
											   hdr_opt_flag, sender, dest, e->key,
											   dumpFlag)).code) ERR_OUT(&err);

	return err;
}

/*
Dz1Error ItsIso14827SessionMgr_encodeAndSend(ItsIso14827SessionMgr *mgr,
											 ItsIso14827SessionKey *skey,
											 Iso14827C2CAuthMsg *msg,
											 u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest, u32_t dumpFlag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ItsIso14827SessionEntry key = { skey }, *session = mgr->sessions->find(mgr->sessions, &key);

	if (session == NULL)
	{
		Dz1Thread_printf("### Unknown Domain = "); ItsIso14827SessionKey_dump(skey, 0);
		ERR_SET_OUT(&err, ENOENT);
	}
	else if ((err = ItsIso14827SessionEntry_encodeAndSend(session, msg, dumpFlag)).code) ERR_OUT(&err);

	return err;
}
*/

Dz1Error ItsIso14827SessionEntry_sendInitiate(ItsIso14827SessionEntry *e, Iso14827Initiate *initiate, u32_t *sentPktNbr,
											  u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest, u32_t dumpFlag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827C2CAuthMsg *msg = NULL;
	// Maximum priority
	if ((msg = Iso14827C2CAuthMsg_new(NULL, e->txSerial, 1, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827PDUs *pdu = NULL;
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&msg);

		if ((err = _makeSureAuthInfo(msg, NULL)).code) ERR_OUT(&err); // no authenticate info
		else if ((msg->hdrOpt = Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);	// empty header option
		else if ((msg->pdu = pdu = Iso14827PDUs_new(Iso14827PDUsPresent_initiate, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((pdu->x.initiate = Iso14827Initiate_clone(initiate, &err)) == NULL) ERR_OUT(&err);
		else if ((err = ItsIso14827SessionEntry_encodeAndSend(e, msg, hdr_opt_flag, sender, dest, dumpFlag)).code) ERR_OUT(&err);
		else
		{
			e->txSerial++;
			if (sentPktNbr) *sentPktNbr = msg->pktNbr;
		}

		pthread_cleanup_pop(1); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// send FrED
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827SessionEntry_sendFrED(ItsIso14827SessionEntry *e, u32_t confirmPktNbr, u32_t *sentPktNbr,
										  u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest, u32_t dumpFlag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827C2CAuthMsg *msg = NULL;
	// Maximum priority
	if ((msg = Iso14827C2CAuthMsg_new(NULL, e->txSerial, 1, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827PDUs *pdu = NULL;
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&msg);

		if ((err = _makeSureAuthInfo(msg, NULL)).code) ERR_OUT(&err); // no authenticate info
		else if ((msg->hdrOpt = Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);	// empty header option
		else if ((msg->pdu = pdu = Iso14827PDUs_new(Iso14827PDUsPresent_fred, &confirmPktNbr, &err)) == NULL) ERR_OUT(&err);
		else if ((err = ItsIso14827SessionEntry_encodeAndSend(e, msg, hdr_opt_flag, sender, dest, dumpFlag)).code) ERR_OUT(&err);
		else
		{
			e->txSerial++;
			if (sentPktNbr) *sentPktNbr = msg->pktNbr;
		}

		pthread_cleanup_pop(1); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// send Reject Login
///////////////////////////////////////////////////////////////////////////////
Dz1Error ItsIso14827SessionEntry_sendRejectLogin(ItsIso14827SessionEntry *e, u32_t confirmPktNbr, Iso14827RejectLogin reason,
												 u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest, u32_t dumpFlag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Iso14827C2CAuthMsg *msg = NULL;
	// Maximum priority
	if ((msg = Iso14827C2CAuthMsg_new(NULL, e->txSerial, 1, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827PDUs *pdu = NULL;
		Iso14827Reject *nak = NULL;
		Iso14827RejectType *type = NULL;
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&msg);

		if ((err = _makeSureAuthInfo(msg, NULL)).code) ERR_OUT(&err); // no authenticate info
		else if ((msg->hdrOpt = Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);	// empty header option
		else if ((msg->pdu = pdu = Iso14827PDUs_new(Iso14827PDUsPresent_nak, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((pdu->x.nak = nak = Iso14827Reject_new(confirmPktNbr, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((nak->type = type = Iso14827RejectType_new(Iso14827RejectTypePresent_login, (void *)&reason, &err)) == NULL) ERR_OUT(&err);
		else if ((err = ItsIso14827SessionEntry_encodeAndSend(e, msg, hdr_opt_flag, sender, dest, dumpFlag)).code) ERR_OUT(&err);
		else e->txSerial++;

		pthread_cleanup_pop(1); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}

static Dz1Error _acceptor_cleanup(void *ptr, ItsIso14827AcceptorEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->thID != -1)
	{
		ItsIosSocketAcceptor_stop(p->thID);
		p->thID = -1;
	}
	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _session_cleanup(void *ptr, ItsIso14827SessionEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->receiver != -1)
	{
		ItsIsoSocketReceiver_stop(p->receiver);
		p->receiver = -1;
	}
	Dz1Error_set(errp, 0);
	return err;
}

void ItsIso14827SessionMgr_cleanup(ItsIso14827SessionMgr *p)
{
	if (p == NULL) return;
	if (p->listener)
	{
		ItsIso14827AcceptorList *list = p->listener;
		list->travel(list, _acceptor_cleanup, NULL);
		ItsIso14827AcceptorList_delAndSetNull(&p->listener);
	}
	if (p->sessions)
	{
		ItsIso14827SessionList *list = p->sessions;
		list->travel(list, _session_cleanup, NULL);
		ItsIso14827SessionList_delAndSetNull(&p->sessions);
	}
	ItsIso14827SessionMgr_del(p);
}

void ItsIso14827SessionMgr_debugDumpPorts(ItsIso14827SessionMgr *p, int tab)
{
	if (p == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else ItsIso14827AcceptorList_dump(p->listener, tab);
}