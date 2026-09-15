#ifndef ITS_ISO_SERVER_SESSION_MGR_MAIN_H_LOCAL
#define ITS_ISO_SERVER_SESSION_MGR_MAIN_H_LOCAL

#include "ItsIso14827SessionDef.h"

///////////////////////////////////////////////////////////////////////////////
// Session Manager API
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK ItsIso14827SessionMgr	*ItsIso14827SessionMgr_init(void *tParent, Dz1Error *err);
DZ1_CPPLINK void					 ItsIso14827SessionMgr_cleanup(ItsIso14827SessionMgr *p);
DZ1_CPPLINK ItsIso14827SessionEntry	*ItsIso14827SessionMgr_connected(ItsIso14827SessionMgr *mgr,
																Dz1SockAddr *peer, Dz1SockAddr *local,
																Dz1TcpClientSocket **sock,
																Dz1Asn1Codec initialCodec,
																ItsIso14827CRCCheck CRCCheck,
																void **initiatorSG,
																void *uArg, void *uRsc, void *timer,
																Dz1Error *err);
/*
DZ1_CPPLINK Dz1Error				 ItsIso14827SessionMgr_received(ItsIso14827SessionMgr *mgr,
																	ItsIso14827SessionKey *_key, Dz1Binary *packet,
																	void *uArg, void *uRsc, void *timer);
*/
DZ1_CPPLINK Dz1Error				 ItsIso14827SessionMgr_openPort(ItsIso14827SessionMgr *mgr, u16_t port,
																	Dz1Asn1Codec initialCodec,
																	ItsIso14827CRCCheck initialCRCmode);

DZ1_CPPLINK void					 ItsIso14827SessionMgr_closePort(ItsIso14827SessionMgr *mgr, u16_t port);

DZ1_CPPLINK ItsIso14827SessionEntry	*ItsISo14827SessionMgr_connect(ItsIso14827SessionMgr *mgr,
																   Dz1SockAddr *peer, size_t datagramSize,
																   Dz1Asn1Codec initialCodec,
																   ItsIso14827CRCCheck initialCRCMode,
																   void *uRsc, void *timer, Dz1Error *err);

DZ1_CPPLINK ItsIso14827SessionEntry	*ItsIso14827SessionMgr_find(ItsIso14827SessionMgr *mgr, ItsIso14827SessionKey *key);
DZ1_CPPLINK Dz1Error ItsIso14827SessionMgr_setSessionAliveTimer(void *timer, ItsIso14827SessionKey *skey, u64_t duration_us);

// Task가 종료 할 때 호출
DZ1_CPPLINK void					 ItsISo14827SessionMgr_terminate(ItsIso14827SessionMgr *p);

// Domain이 Session을 끝내는 함수
DZ1_CPPLINK void					 ItsIso14827SessionMgr_sessionDisconnect(ItsIso14827SessionMgr *mgr, ItsIso14827SessionKey *key);

///////////////////////////////////////////////////////////////////////////////
// Direct Send API via Session Manager
// DZ1_CPPLINK Dz1Error ItsIso14827SessionMgr_encodeAndSend(ItsIso14827SessionMgr *mgr, ItsIso14827SessionKey *skey,
// 														 Iso14827C2CAuthMsg *msg, u32_t dumpFlag);
// DZ1_CPPLINK Dz1Error ItsIso14827SessionMgr_sendFrED(ItsIso14827SessionMgr *mgr, ItsIso14827SessionKey *skey,
// 													u32_t confirmPktNbr, u32_t *sentPktNbr, u32_t dumpFlag);

// DZ1_CPPLINK Dz1Error ItsIso14827SessionMgr_sendRejectLogin(ItsIso14827SessionMgr *mgr, ItsIso14827SessionKey *skey,
// 														   u32_t confirmPktNbr, Iso14827RejectLogin reason, u32_t dumpFlag);

///////////////////////////////////////////////////////////////////////////////
// Session Entry API
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK void		 ItsIso14827SessionEntry_cleanup(ItsIso14827SessionEntry *p);
static __inline__ void	 ItsIso14827SessionEntry_cleanupAndSetNull(void *ptr)
{
	ItsIso14827SessionEntry **p = (ItsIso14827SessionEntry **)ptr;
	ItsIso14827SessionEntry_cleanup(*p); *p = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Direct Send API via Session Entry
DZ1_CPPLINK Dz1Error ItsIso14827SessionEntry_encodeAndSend(ItsIso14827SessionEntry *e, Iso14827C2CAuthMsg *msg,
														   u32_t hdr_opt_flag, Dz1Asn1OctetStr *sender, Dz1Asn1OctetStr *dest, 
														   u32_t dumpFlag);

//DZ1_CPPLINK Dz1Error ItsIso14827SessionEntry_sendInitiate(ItsIso14827SessionEntry *e, Iso14827Initiate *initiate, u32_t *sentPktNbr, u32_t dumpFlag);
DZ1_CPPLINK Dz1Error ItsIso14827SessionEntry_sendInitiate(ItsIso14827SessionEntry *e, Iso14827Initiate *initiate, u32_t *sentPktNbr,
														  u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest, u32_t dumpFlag);

DZ1_CPPLINK Dz1Error ItsIso14827SessionEntry_sendLogin(ItsIso14827SessionEntry *e, Dz1Asn1OctetStr *authInfo, Iso14827Login *msg);

//DZ1_CPPLINK Dz1Error ItsIso14827SessionEntry_sendFrED(ItsIso14827SessionEntry *e, u32_t confirmPktNbr, u32_t *sentPktNbr, u32_t dumpFlag);
DZ1_CPPLINK Dz1Error ItsIso14827SessionEntry_sendFrED(ItsIso14827SessionEntry *e, u32_t confirmPktNbr, u32_t *sentPktNbr,
													  u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest, u32_t dumpFlag);

// DZ1_CPPLINK Dz1Error ItsIso14827SessionEntry_sendRejectLogin(ItsIso14827SessionEntry *e, u32_t confirmPktNbt,
// 															 Iso14827RejectLogin reason, u32_t dumpFlag);
DZ1_CPPLINK Dz1Error ItsIso14827SessionEntry_sendRejectLogin(ItsIso14827SessionEntry *e, u32_t confirmPktNbr, Iso14827RejectLogin reason,
															 u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest, u32_t dumpFlag);

//DZ1_CPPLINK Dz1Error ItsIso14827Socket_encodeAndSend(Dz1TcpClientSocket *sock, Iso14827C2CAuthMsg *msg, Dz1Asn1Codec codec, u32_t dumpFlag);

#endif
