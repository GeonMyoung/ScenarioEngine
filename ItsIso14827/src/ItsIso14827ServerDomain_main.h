#ifndef ITS_ISO_14827_SERVER_DOMAIN_MAIN_H_LOCAL
#define ITS_ISO_14827_SERVER_DOMAIN_MAIN_H_LOCAL

#include "ItsIso14827ServerDomainDef.h"

DZ1_CPPLINK Dz1Error				 ItsIso14827ServerDomain_received(ItsIso14827ServerDomain *dst, ItsIso14827SessionEntry *src,
																	  Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
																	  Iso14827PDUs *pdu, bool_t isRetried,
																	  void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK ItsIso14827ServerDomainClientEntry *ItsIso14827ServerDomain_findClientBySession(ItsIso14827ServerDomain *domain,
																					  ItsIso14827SessionKey *skey);
DZ1_CPPLINK ItsIso14827ServerDomainClientEntry *ItsIso14827ServerDomain_findClientByPeerUser(ItsIso14827ServerDomain *domain,
																				   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user);


DZ1_CPPLINK Dz1Error ItsISo14827ServerDomain_connectToClient(ItsIso14827ServerDomain *domain,
															 ItsIso14827SessionEntry *session,
															 Iso14827Initiate **initiate, Dz1TaskSigMsg **sg,
															 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomain_loginAccept(ItsIso14827ServerDomain *domain,
														 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														 Dz1Asn1Codec selectedCodec, ItsIso14827CRCCheck CRCMode,
														 ItsIso14827ServerDomainViolatedPublication *violatedPub,
														 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK ItsIso14827SessionKey *ItsIso14827ServerDomain_loginReject(ItsIso14827ServerDomain *domain,
																	   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
																	   Iso14827RejectLogin reason,
																	   void *uArg, void *uRsc, void *timer, Dz1Error *err);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomain_echoReply(ItsIso14827ServerDomain *domain,
													   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
													   u32_t confirmPktNbr,
													   void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomain_prepareAccept(ItsIso14827ServerDomain *domain,
														   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														   u32_t serial,
														   void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomain_prepareReject(ItsIso14827ServerDomain *domain,
														   Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														   u32_t serial, Iso14827RejectSubscription reason,
														   void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomain_dataProvide(ItsIso14827ServerDomain *domain,
														 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														 u32_t serial, Iso14827EndAppMsg **eam,
														 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomain_dataControl(ItsIso14827ServerDomain *domain,
														 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														 u32_t serial, Iso14827PublicationMgmt cmd,
														 void *uArg, void *uRsc, void *timer);
// 서버가 Subscription도 안줬는데 꼴리는데로 Publication을 하려고 할 때(미친새끼...)
DZ1_CPPLINK Dz1Error ItsIso14827ServerDomain_violatedPub(ItsIso14827ServerDomain *domain,
														 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														 Iso14827Publication **pub,
														 void *uArg, void *uRsc, void *timer);
DZ1_CPPLINK Dz1Error ItsIso14827ServerDomain_violatedSub(ItsIso14827ServerDomain *domain,
														 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														 Iso14827Subscription **pub,
														 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomain_terminateClient(ItsIso14827ServerDomain *domain,
														 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
														 Iso14827Terminate reason,
														 void *uArg, void *uRsc, void *timer);

///////////////////////////////////////////////////////////////////////////////
// Application이 Domain을 삭제하는 경우
DZ1_CPPLINK void ItsIso14827ServerDomain_delete(ItsIso14827ServerDomain *p);

///////////////////////////////////////////////////////////////////////////////
// Session이 끊어져서 user@PEER만 사라지는 경우
DZ1_CPPLINK void ItsIso14827ServerDomain_sessionDisconnected(ItsIso14827ServerDomain *p, ItsIso14827SessionKey *skey, void *timer);

///////////////////////////////////////////////////////////////////////////////
// Heart-Beat Duration이 지나서 user@PEER를 제거하는 경우
DZ1_CPPLINK ItsIso14827SessionKey *ItsIso14827ServerDomain_expireSession(ItsIso14827ServerDomain *p, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, void *timer);

///////////////////////////////////////////////////////////////////////////////
// Task가 종료될 때
DZ1_CPPLINK void ItsIso14827ServerDomain_terminate(ItsIso14827ServerDomain *p);

#endif