#ifndef ITS_ISO_14827_CLIENT_DOMAIN_MAIN_H_LOCAL
#define ITS_ISO_14827_CLIENT_DOMAIN_MAIN_H_LOCAL

#include <Iso14827dz1.h>
#include "ItsIso14827ClientDomainDef.h"
#include "ItsIso14827SessionDef.h"
DZ1_CPPLINK Dz1Error ItsIso14827ClientDomain_received(ItsIso14827ClientDomain *domain,
													  ItsIso14827SessionEntry *session,
													  Dz1Asn1OctetStr *authInfo,
													  u32_t pktNbr, s32_t priority,
													  Iso14827PDUs *pdu, bool_t isRetried,
													  void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK ItsIso14827ClientDomainServerEntry *ItsIso14827ClientDomain_findServerByPeerUser(ItsIso14827ClientDomain *domain,
																							 Dz1Asn1UTF8Str *peer,
																							 Dz1Asn1OctetStr *user);
DZ1_CPPLINK ItsIso14827ClientDomainServerEntry *ItsIso14827ClientDomain_extractServerByPeerUser(ItsIso14827ClientDomain *domain,
																							    Dz1Asn1UTF8Str *peer,
																							    Dz1Asn1OctetStr *user);

DZ1_CPPLINK ItsIso14827SessionKey *ItsIso14827ClientDomain_sendFail(ItsIso14827ClientDomain *domain,
																	Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
																	Iso14827C2CAuthMsg *c2c, void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsISo14827Clientdomain_connectToServer(ItsIso14827ClientDomain *domain,
															 ItsIso14827SessionEntry *session,
															 Dz1Asn1OctetStr *authInfo, Iso14827Login **login, 
															 ItsIso14827ClientDomainViolatedSubscription **violatedSub, Dz1TaskSigMsg **sg,
															 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomain_disconnectFromServer(ItsIso14827ClientDomain *domain,
																  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
																  Iso14827Logout reason, Dz1TaskSigMsg **sg,
																  void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomain_subscription(ItsIso14827ClientDomain *domain,
														  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														  Iso14827SubscriptionData **data, Dz1TaskSigMsg **sg,
														  void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomain_subCancel(ItsIso14827ClientDomain *domain,
													   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
													   u32_t serial, Iso14827SubscriptionCancel reason,
													   Dz1TaskSigMsg **sg, void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomain_rejectPubData(ItsIso14827ClientDomain *domain,
														   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														   u32_t serial, u32_t pubSerial, Iso14827RejectPubDataReason reason,
														   Dz1TaskSigMsg **sg, void *uArg, void *uRsc, void *timer);
// 클라이언트가 제멋데로 Publication을 하려고 할 때(미친새끼...)
DZ1_CPPLINK Dz1Error ItsIso14827ClientDomain_violatedPub(ItsIso14827ClientDomain *domain,
														 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														 Iso14827Publication **pub,
														 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1TaskProcStatus ItsIso14827ClientDomainMgr_heartBeatPeriodTimeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp);

///////////////////////////////////////////////////////////////////////////////
// Task가 종료 할 때
DZ1_CPPLINK void ItsIso14827ClientDomain_terminate(ItsIso14827ClientDomain *p);

///////////////////////////////////////////////////////////////////////////////
// Session이 끊어져서 user@PEER만 사라지는 경우
DZ1_CPPLINK void ItsIso14827ClientDomain_sessionDisconnected(ItsIso14827ClientDomain *p, ItsIso14827SessionKey *skey, void *timer);

///////////////////////////////////////////////////////////////////////////////
// Heart-Beat Duration이 지나서 user@PEER를 제거하는 경우
DZ1_CPPLINK ItsIso14827SessionKey *ItsIso14827ClientDomain_expireSession(ItsIso14827ClientDomain *p, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, void *timer);

#endif