#ifndef ITS_ISO_SERVER_H
#define ITS_ISO_SERVER_H

#include <ItsIso14827Def.h>

DZ1_CPPLINK void		*ItsIso14827_new(ItsIso14827Exception exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void		 ItsIso14827_del(void *t14827);
static __inline__ void	 ItsIso14827_delAndSetNull(void *pptr)
{
	void **t14827 = (void **)pptr;
	ItsIso14827_del( *t14827 ); (*t14827) = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// TCP Port Manipulate - BEGIN
// ----------------------------------------------------------------------
// Open TCP Server Port
DZ1_CPPLINK Dz1Error	 ItsIso14827_openPort(void *t14827, u16_t port, Dz1Asn1Codec initialCodec, ItsIso14827CRCCheck initialCRCMode);

// ----------------------------------------------------------------------
// Close TCP Server Port
DZ1_CPPLINK Dz1Error	 ItsIso14827_closePort(void *t14827, u16_t port);

// TCP Port Manipulate - END
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Server Domain Manipulate - BEGIN
typedef struct ItsIso14827CodecOIDInfo
{
	str_t oidStr;
	Dz1Asn1Codec mean;
} ItsIso14827CodecOIDInfo;

// ----------------------------------------------------------------------
// Create Server Domain
DZ1_CPPLINK Dz1Error	 ItsIso14827_createServer(void *t14827, Dz1Asn1UTF8Str *name, u32_t maxClient,
												  ItsIso14827CodecOIDInfo userOIDMap[], size_t numOfMap,
												  ItsIso14827ServerDomainCallback *cbs);

// ----------------------------------------------------------------------
// Delete Server Domain
DZ1_CPPLINK Dz1Error	 ItsIso14827_deleteServer(void *t14827, Dz1Asn1UTF8Str *name);

// ----------------------------------------------------------------------
// Connect to Client and send INITIATE
DZ1_CPPLINK Dz1Error	 ItsIso14827_connectToClient(void *t14827, Dz1SockAddr *dstAddr,
													 Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
													 Dz1Asn1Codec initialCodec, ItsIso14827CRCCheck initialCRCMode);

// ----------------------------------------------------------------------
// send INITIATE using already connected
DZ1_CPPLINK Dz1Error	 ItsIso14827_connectedToClient(void *t14827, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket **sock,
													   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
													   Dz1Asn1Codec initialCodec, ItsIso14827CRCCheck initialCRCMode);

// ----------------------------------------------------------------------
// Accept LOGIN
#define					 ItsIso14827_loginAccept(t14827, my, peer, user, codec, crc) _ItsIso14827_loginAccept(t14827, my, peer, user, codec, crc, NULL, NULL)
DZ1_CPPLINK Dz1Error	_ItsIso14827_loginAccept(void *t14827, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
												 Dz1Asn1Codec selectedCodec, ItsIso14827CRCCheck CRCMode,
												 ItsIso14827CallbackPublication violatedPubRecv, void *violatedPubRecvParam);	// 불법 Publication 수신 시 사용할 callback

// ----------------------------------------------------------------------
// Reject LOGIN
DZ1_CPPLINK Dz1Error	 ItsIso14827_loginReject(void *t14827, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, Iso14827RejectLogin reason);
// peer domain/user				:: Iso14827RejectLogin_sessionExist
// user-name/password			:: Iso14827RejectLogin_accessDenied      / Iso14827RejectLogin_invalidPassword
// maximum heartbeat duration	:: Iso14827RejectLogin_heartbeatTooSmall / Iso14827RejectLogin_heartbeatTooLarge
// response time-out period		:: Iso14827RejectLogin_timeoutTooSmall   / Iso14827RejectLogin_timeoutTooLarge
// allowed encoding rules		:: Iso14827RejectLogin_other

// ----------------------------------------------------------------------
// Echo Request Response
DZ1_CPPLINK Dz1Error	 ItsIso14827_echoReply(void *t14827, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, u32_t confirmPktNbr);

// ----------------------------------------------------------------------
// TERMINATE
DZ1_CPPLINK Dz1Error	 ItsIso14827_terminateClient(void *t14827, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user);

// Server Domain Manipulate - END
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Client Domain Manipulate - BEGIN
// ----------------------------------------------------------------------
// Create Client Domain
DZ1_CPPLINK Dz1Error	 ItsIso14827_createClient(void *t14827, Dz1Asn1UTF8Str *myDomain, ItsIso14827ClientDomainCallback *cbs);

// ----------------------------------------------------------------------
// Delete Client Domain
DZ1_CPPLINK Dz1Error	 ItsIso14827_deleteClient(void *t14827, Dz1Asn1UTF8Str *myDomain);

// ----------------------------------------------------------------------
// LOGIN : Connect to Server (Client Initiated Login)
#define					 ItsIso14827_connectToServer(t14827, dst_addr, my_domain, peer_domain, auth_info, user, pass, codec_bits, hb_dur, rsp_time, dg_size, in_out_codec, crc_mode, ret_reason) \
						_ItsIso14827_connectToServer(t14827, dst_addr, my_domain, peer_domain, auth_info, user, pass, codec_bits, hb_dur, rsp_time, dg_size, in_out_codec, crc_mode, NULL, NULL, ret_reason)
DZ1_CPPLINK Dz1Error	_ItsIso14827_connectToServer(void *t14827, Dz1SockAddr *dstAddr,
													 Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
													 Dz1Asn1OctetStr *authInfo, Dz1Asn1OctetStr *user, Dz1Asn1OctetStr *pass,
													 u8_t codecRuleBits, u16_t heartBeatDuration,
													 u8_t responseWaitTime, u16_t datagramSize,
													 Dz1Asn1Codec *in_out_codec, ItsIso14827CRCCheck CRCMode,
													 ItsIso14827CallbackViolatedSubRcvd violatedSubRecv, void *violatedSubRecvParam,
													 Iso14827RejectLogin *retReason);

// ----------------------------------------------------------------------
// LOGIN : Using already connected socket (Client Initiated Login)
#define					 ItsIso14827_connectedToServer(t14827, peer, local, sock_pp, my_domain, peer_domain, auth_info, user, pass, codec_bits, hb_dur, rsp_time, dg_size, in_out_codec, crc_mode, ret_reason) \
						_ItsIso14827_connectedToServer(t14827, peer, local, sock_pp, my_domain, peer_domain, auth_info, user, pass, codec_bits, hb_dur, rsp_time, dg_size, in_out_codec, crc_mode, NULL, NULL, ret_reason)
DZ1_CPPLINK Dz1Error	_ItsIso14827_connectedToServer(void *t14827,
													   Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket **sock,
													   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
													   Dz1Asn1OctetStr *authInfo, Dz1Asn1OctetStr *user, Dz1Asn1OctetStr *pass,
													   u8_t codecRuleBits, u16_t heartBeatDuration_s,
													   u8_t responseWaitTime_s, u16_t datagramSize_octet,
													   Dz1Asn1Codec *in_out_codec, ItsIso14827CRCCheck initialCRCMode,
													   ItsIso14827CallbackViolatedSubRcvd violatedSubRecv, void *violatedSubRecvParam,
													   Iso14827RejectLogin *retReason);

// ----------------------------------------------------------------------
// Reject INITIATE
DZ1_CPPLINK Dz1Error	 ItsIso14827_rejectInitiate(void *t14827, ItsIso14827SessionKey *bindKey);

// ----------------------------------------------------------------------
// Accept INITIATE
#define					 ItsIso14827_bindWithServer(t14827, bindKey, my_domain, peer_domain, auth_info, user, pass, codec_bits, hb_dur, rsp_time, dg_size, in_out_codec, ret_reason) \
						_ItsIso14827_bindWithServer(t14827, bindKey, my_domain, peer_domain, auth_info, user, pass, codec_bits, hb_dur, rsp_time, dg_size, in_out_codec, NULL, NULL, ret_reason)
DZ1_CPPLINK Dz1Error	_ItsIso14827_bindWithServer(void *t14827, ItsIso14827SessionKey *bindKey,
													Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
													Dz1Asn1OctetStr *authInfo, Dz1Asn1OctetStr *user, Dz1Asn1OctetStr *pass,
													u8_t codecRuleBits, u16_t heartBeatDuration,
													u8_t responseWaitTime, u16_t datagramSize,
													Dz1Asn1Codec *out_codec,
													ItsIso14827CallbackViolatedSubRcvd violatedSubRecv, void *violatedSubRecvParam,
													Iso14827RejectLogin *retReason);

// ----------------------------------------------------------------------
// LOGOUT : Disconnect
DZ1_CPPLINK Dz1Error	 ItsIso14827_disconnectFromServer(void *t14726, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, Iso14827Logout reason);

// ----------------------------------------------------------------------
// Misc Controls
DZ1_CPPLINK Dz1Error	_ItsIso14827_controlClient(void *t14827, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, u32_t ItsIso14827ClientCtrlFlag_flags, bool_t on_off);
DZ1_CPPLINK Dz1Error	 ItsIso14827_controlClient(void *t14827, Dz1Str			 myDomain, Dz1Str		   peerDomain, str_t			user, u32_t ItsIso14827ClientCtrlFlag_flags, bool_t on_off);

// Client Domain Manipulate - END
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Publication - BEGIN
// ----------------------------------------------------------------------
// Accept : Single/Event/Periodic Prepare Response
#define					 ItsIso14827_singleAccept(t14827, dt, myDomain, peerDomain, user, subID) \
						 ItsIso14827_prepareAccept((t14827), (dt), (myDomain), (peerDomain), (user), (subID))

DZ1_CPPLINK Dz1Error	 ItsIso14827_prepareAccept(void *t14827, ItsIso14827DomainType domainType,
												   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
												   Dz1Asn1OctetStr *user, u32_t subscriptionID);

// ----------------------------------------------------------------------
// Reject : Single/Event/Periodic Prepare Response
#define					 ItsIso14827_singleReject(t14827, dt, myd, peerd, usr, sid, rsn) \
						 ItsIso14827_prepareReject((t14827), (dt), (myd), (peerd), (usr), (sid), (rsn))
DZ1_CPPLINK Dz1Error	 ItsIso14827_prepareReject(void *t14827, ItsIso14827DomainType domainType,
												   Dz1Asn1UTF8Str *myDomainName, Dz1Asn1UTF8Str *peerDomainName,
												   Dz1Asn1OctetStr *user, u32_t subscriptionID, Iso14827RejectSubscription reason);

// ----------------------------------------------------------------------
// Publication(Data) : Single/Event/Periodic
DZ1_CPPLINK Dz1Error	 ItsIso14827_dataProvide(void *t14827, ItsIso14827DomainType domainType,
												 Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
												 u32_t subscriptionID, str_t oidStr, u8_t *encoddedEndAppMsg, size_t encoddedEndAppMsgSize);
// Single Request Response	=> Single Response
// Event Start Response		=> Initial Publication
// Event Detected			=> Subsequent Publication
// Periodic Start Response	=> Initial Publication
// Periodic Invoke Response	=> Subsequent Publication

// ----------------------------------------------------------------------
// Publication(Management) : Error Response or Providing Control(Event/Periodic Only)
DZ1_CPPLINK Dz1Error	 ItsIso14827_dataControl(void *t14827, ItsIso14827DomainType domainType,
												 Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
												 u32_t subscriptionID, Iso14827PublicationMgmt cmd);

// Publication - END
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Subscription - BEGIN
// ----------------------------------------------------------------------
// Single Request
DZ1_CPPLINK Dz1Error	 ItsIso14827_singleRequest(void *t14827, ItsIso14827DomainType domainType,
												   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
												   Dz1Asn1OctetStr *user, u32_t priority, bool_t guarantee,
												   str_t oidStr, u8_t *encoddedEndAppMsg, size_t encoddedEndAppMsgSize,
												   u32_t *retSubscriptionID, Iso14827RejectSubscription *retErr);
// ----------------------------------------------------------------------
// Registered Continuous Request API
#define					 Iso14827RegisteredContinuousDeclare(var, delay)		Iso14827RegisteredContinuous var = { (delay), NULL, NULL }
DZ1_CPPLINK Dz1Error	 ItsIso14827_continuousRequest(void *t14827, ItsIso14827DomainType domainType,
													   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
													   Dz1Asn1OctetStr *user, bool_t isPersistent, u32_t priority, bool_t guarantee,
													   bool_t isPeriodic, Iso14827RegisteredContinuous *schedule,
													   str_t oidStr, u8_t *encoddedEndAppMsg, size_t encoddedEndAppMsgSize,
													   u32_t *retSubscriptionID, Iso14827RejectSubscription* retErr);
// ----------------------------------------------------------------------
// Registered Daily Request API
DZ1_CPPLINK				 Iso14827RegisteredDaily *iso14827D247Unlimited;
DZ1_CPPLINK Dz1Error	 ItsIso14827_dailyRequest(void *t14827, ItsIso14827DomainType domainType,
												  Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
												  Dz1Asn1OctetStr *user, bool_t isPersistent, u32_t priority, bool_t guarantee,
												  bool_t isPeriodic, Iso14827RegisteredDaily *schedule,
												  str_t oidStr, u8_t *encoddedEndAppMsg, size_t encoddedEndAppMsgSize,
												  u32_t *retSubscriptionID, Iso14827RejectSubscription* retErr);

/*
// ----------------------------------------------------------------------
// Registered Continuous Request Change API
DZ1_CPPLINK Dz1Error ItsIso14827_continuousChange(void *t14827,
												  ItsIso14827DomainType domainType, Dz1Asn1UTF8Str *myDomainName,
												  Dz1Asn1UTF8Str *peerDomainName, Dz1Asn1OctetStr *user,
												  u32_t serial,
												  bool_t isPersistent,
												  u32_t priority,
												  bool_t guarantee,
												  Iso14827RegisteredContinuous *schedule);

// ----------------------------------------------------------------------
// Registered Daily Request Change API
DZ1_CPPLINK Dz1Error ItsIso14827_dailyChange(void *t14827,
											 ItsIso14827DomainType domainType, Dz1Asn1UTF8Str *myDomainName,
											 Dz1Asn1UTF8Str *peerDomainName, Dz1Asn1OctetStr *user,
											 u32_t serial,
											 bool_t isPersistent,
											 u32_t priority,
											 bool_t guarantee,
											 Iso14827RegisteredDaily *schedule);
*/
// ----------------------------------------------------------------------
// Reject : Publication Data
DZ1_CPPLINK Dz1Error	 ItsIso14827_rejectPubData(void *t14827, ItsIso14827DomainType domainType,
												   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
												   Dz1Asn1OctetStr *user, u32_t subscriptionID, u32_t pubSerial,
												   Iso14827RejectPubDataReason reason);
// ----------------------------------------------------------------------
// Cancel Subscription
DZ1_CPPLINK Dz1Error	 ItsIso14827_requestCancel(void *t14827, ItsIso14827DomainType domainType,
												   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
												   Dz1Asn1OctetStr *user, u32_t subscriptionID,
												   Iso14827SubscriptionCancel reason);
// Subscription - END
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Non-Standard : Violation API

// ----------------------------------------------------------------------
// ItsIso14827_violatedPub
//			to send Publication Message
//			from Client Domain or
//			from Server Domain without prior Subscription
DZ1_CPPLINK Dz1Error	 ItsIso14827_violatedPub(void *t14827, ItsIso14827DomainType domainType,
												 Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
												 Dz1Asn1OctetStr *user, bool_t guaranteed,
												 u32_t subSerial, u32_t pubSerial, bool_t isLated,
												 str_t oidStr, u8_t *msgBody, size_t msgDize);

// ----------------------------------------------------------------------
// ItsIso14827_violatedSub
//		Send Subscription from Server Domain
//		Note. this function will send Single Subscription to Client Domain
//		Pair with LoginAccept argument
//			ItsIso14827CallbackPublication	 violatedPubRecv
//			void							*violatedPubRecvParam
DZ1_CPPLINK Dz1Error	 ItsIso14827_violatedSub(void *t14827, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
												 Dz1Asn1OctetStr *user, u32_t subSerial, bool_t guaranteed,
												 str_t oidStr, u8_t *msgBody, size_t msgDize);
// Non-Standard : Violation API
///////////////////////////////////////////////////////////////////////////////

// type == ItsIso14827DomainType_max : dump all domains, ignore myDomainName
// myDomainName == NULL : dump all type's domain
DZ1_CPPLINK Dz1Error	 ItsIso14827_debugStatus(void *t14827, ItsIso14827DomainType type, Dz1Asn1UTF8Str *myDomainName);

#define ITS_ISO14827_PACKET_DUMP_DATEX				0x80000000
#define ITS_ISO14827_PACKET_DUMP_C2CAUTH			0x40000000
#define ITS_ISO14827_PACKET_DUMP_PDU				0x20000000
#define ITS_ISO14827_PACKET_DUMP_PDU_LOGIN			0x08000000
#define ITS_ISO14827_PACKET_DUMP_PDU_FRED			0x04000000
#define ITS_ISO14827_PACKET_DUMP_PDU_TERM			0x02000000
#define ITS_ISO14827_PACKET_DUMP_PDU_LOGOUT			0x01000000
#define ITS_ISO14827_PACKET_DUMP_PDU_SUBSCRIPTION	0x00800000
#define ITS_ISO14827_PACKET_DUMP_PDU_PUBLICATION	0x00400000
#define ITS_ISO14827_PACKET_DUMP_PDU_TRANSFER_DONE	0x00200000
#define ITS_ISO14827_PACKET_DUMP_PDU_ACCEPT			0x00100000
#define ITS_ISO14827_PACKET_DUMP_PDU_REJECT			0x00080000
#define ITS_ISO14827_PACKET_DUMP_PDU_INITIATE		0x00040000

#define ITS_ISO14827_SESSION_DUMP					0x00000001

#define ITS_ISO14827_PACKET_DUMP_ALL				0xFFFFFFFF

#define ITS_ISO14827_PACKET_DUMP_DEFAULT			(ITS_ISO14827_PACKET_DUMP_DATEX | ITS_ISO14827_PACKET_DUMP_C2CAUTH)

#define ITS_ISO14827_PACKET_DUMP_PDU_ELEMENTS		(ITS_ISO14827_PACKET_DUMP_PDU_LOGIN |\
													 ITS_ISO14827_PACKET_DUMP_PDU_FRED |\
													 ITS_ISO14827_PACKET_DUMP_PDU_TERM |\
													 ITS_ISO14827_PACKET_DUMP_PDU_LOGOUT |\
													 ITS_ISO14827_PACKET_DUMP_PDU_SUBSCRIPTION |\
													 ITS_ISO14827_PACKET_DUMP_PDU_PUBLICATION |\
													 ITS_ISO14827_PACKET_DUMP_PDU_TRANSFER_DONE |\
													 ITS_ISO14827_PACKET_DUMP_PDU_ACCEPT |\
													 ITS_ISO14827_PACKET_DUMP_PDU_REJECT)

#define ITS_ISO14827_PACKET_DUMP_END_APPLICATION	(ITS_ISO14827_PACKET_DUMP_PDU_SUBSCRIPTION | ITS_ISO14827_PACKET_DUMP_PDU_PUBLICATION |\
													 ITS_ISO14827_PACKET_DUMP_PDU_ACCEPT | ITS_ISO14827_PACKET_DUMP_PDU_REJECT)
DZ1_CPPLINK Dz1Error	 ItsIso14827_pktDumpOn(void *t14827, u32_t flag);
DZ1_CPPLINK Dz1Error	 ItsIso14827_pktDumpOff(void *t14827, u32_t flag);
DZ1_CPPLINK Dz1Error	 ItsIso14827_pktDumpSet(void *t14827, u32_t flag);

DZ1_CPPLINK void		 ItsIso14827SocketHook_set(void (*hook_func)(void *hook_arg, Iso14827C2CAuthMsg *msg, bool_t *isReceived), void *hook_arg);
static __inline__ void	 ItsIso14827SocketHook_setCancel(void *ptr)
{
	ItsIso14827SocketHook_set(NULL, NULL);
}

#endif
