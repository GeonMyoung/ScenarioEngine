#ifndef _DZ1_TDC_ITS_ISO14827_DOMAIN_MSGS_H_
#define _DZ1_TDC_ITS_ISO14827_DOMAIN_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827DefLocal.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainCreateServer
typedef struct ItsIso14827DomainCreateServer
{
	Dz1Asn1UTF8Str						*name;
	u32_t								 maxClient;
	ItsIso14827CodecOIDMapList			*codecOIDMap;
	ItsIso14827ServerDomainCallback		*cbs;
} ItsIso14827DomainCreateServer;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainCreateServer *ItsIso14827DomainCreateServer_new(Dz1Asn1UTF8Str *name, 
																						 u32_t maxClient, 
																						 ItsIso14827CodecOIDMapList *codecOIDMap, 
																						 ItsIso14827ServerDomainCallback *cbs, Dz1Error *err);
static __inline__ ItsIso14827DomainCreateServer *ItsIso14827DomainCreateServer_gen(Dz1Error *err) { return ItsIso14827DomainCreateServer_new(NULL, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainCreateServer_purge(ItsIso14827DomainCreateServer *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainCreateServer_del(ItsIso14827DomainCreateServer *p);
static __inline__ void ItsIso14827DomainCreateServer_delAndSetNull(void *ptr)
{
	ItsIso14827DomainCreateServer **p = (ItsIso14827DomainCreateServer **)ptr;
	if (p) { ItsIso14827DomainCreateServer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainCreateServer_dump(ItsIso14827DomainCreateServer *p, int tab);
// ItsIso14827DomainCreateServer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainCreateClient
typedef struct ItsIso14827DomainCreateClient
{
	Dz1Asn1UTF8Str						*name;
	ItsIso14827ClientDomainCallback		*cbs;
} ItsIso14827DomainCreateClient;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainCreateClient *ItsIso14827DomainCreateClient_new(Dz1Asn1UTF8Str *name, 
																						 ItsIso14827ClientDomainCallback *cbs, Dz1Error *err);
static __inline__ ItsIso14827DomainCreateClient *ItsIso14827DomainCreateClient_gen(Dz1Error *err) { return ItsIso14827DomainCreateClient_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainCreateClient_purge(ItsIso14827DomainCreateClient *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainCreateClient_del(ItsIso14827DomainCreateClient *p);
static __inline__ void ItsIso14827DomainCreateClient_delAndSetNull(void *ptr)
{
	ItsIso14827DomainCreateClient **p = (ItsIso14827DomainCreateClient **)ptr;
	if (p) { ItsIso14827DomainCreateClient_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainCreateClient_dump(ItsIso14827DomainCreateClient *p, int tab);
// ItsIso14827DomainCreateClient
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainInitiate
typedef struct ItsIso14827DomainInitiate
{
	Dz1SockAddr				*peerAddr;
	Dz1SockAddr				*localAddr;
	Dz1TcpClientSocket		*sock;
	Iso14827Initiate		*data;
	Dz1Asn1Codec			 initialCodec;
	ItsIso14827CRCCheck		 initialCRCMode;
} ItsIso14827DomainInitiate;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainInitiate *ItsIso14827DomainInitiate_new(Dz1SockAddr *peerAddr, 
																				 Dz1SockAddr *localAddr, 
																				 Dz1TcpClientSocket *sock, 
																				 Iso14827Initiate *data, 
																				 Dz1Asn1Codec initialCodec, 
																				 ItsIso14827CRCCheck initialCRCMode, Dz1Error *err);
static __inline__ ItsIso14827DomainInitiate *ItsIso14827DomainInitiate_gen(Dz1Error *err) { return ItsIso14827DomainInitiate_new(NULL, NULL, NULL, NULL, Dz1Asn1Codec_max, ItsIso14827CRCCheck_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainInitiate_purge(ItsIso14827DomainInitiate *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainInitiate_del(ItsIso14827DomainInitiate *p);
static __inline__ void ItsIso14827DomainInitiate_delAndSetNull(void *ptr)
{
	ItsIso14827DomainInitiate **p = (ItsIso14827DomainInitiate **)ptr;
	if (p) { ItsIso14827DomainInitiate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainInitiate_dump(ItsIso14827DomainInitiate *p, int tab);
// ItsIso14827DomainInitiate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainLogin
typedef struct ItsIso14827DomainLogin
{
	Dz1Asn1Codec									 initialCodec;
	Iso14827RejectLogin								 reason;
	Dz1SockAddr										*peerAddr;
	Dz1SockAddr										*localAddr;
	Dz1TcpClientSocket								*sock;
	Dz1Asn1OctetStr									*authInfo;
	Iso14827Login									*data;
	ItsIso14827CRCCheck								 initialCRCMode;
	ItsIso14827ClientDomainViolatedSubscription		*violatedSub;
} ItsIso14827DomainLogin;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainLogin *ItsIso14827DomainLogin_new(Dz1Asn1Codec initialCodec, 
																		   Iso14827RejectLogin reason, 
																		   Dz1SockAddr *peerAddr, 
																		   Dz1SockAddr *localAddr, 
																		   Dz1TcpClientSocket *sock, 
																		   Dz1Asn1OctetStr *authInfo, 
																		   Iso14827Login *data, 
																		   ItsIso14827CRCCheck initialCRCMode, 
																		   ItsIso14827ClientDomainViolatedSubscription *violatedSub, Dz1Error *err);
static __inline__ ItsIso14827DomainLogin *ItsIso14827DomainLogin_gen(Dz1Error *err) { return ItsIso14827DomainLogin_new(Dz1Asn1Codec_max, Iso14827RejectLogin_max, NULL, NULL, NULL, NULL, NULL, ItsIso14827CRCCheck_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLogin_purge(ItsIso14827DomainLogin *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLogin_del(ItsIso14827DomainLogin *p);
static __inline__ void ItsIso14827DomainLogin_delAndSetNull(void *ptr)
{
	ItsIso14827DomainLogin **p = (ItsIso14827DomainLogin **)ptr;
	if (p) { ItsIso14827DomainLogin_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLogin_dump(ItsIso14827DomainLogin *p, int tab);
// ItsIso14827DomainLogin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainBind
typedef struct ItsIso14827DomainBind
{
	Dz1Asn1Codec									 initialCodec;
	Iso14827RejectLogin								 reason;
	Dz1Asn1UTF8Str									*myDomain;
	Dz1Asn1UTF8Str									*peerDomain;
	ItsIso14827SessionKey							*bindKey;
	Dz1Asn1OctetStr									*authInfo;
	Iso14827Login									*data;
	ItsIso14827ClientDomainViolatedSubscription		*violatedSub;
} ItsIso14827DomainBind;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainBind *ItsIso14827DomainBind_new(Dz1Asn1Codec initialCodec, 
																		 Iso14827RejectLogin reason, 
																		 Dz1Asn1UTF8Str *myDomain, 
																		 Dz1Asn1UTF8Str *peerDomain, 
																		 ItsIso14827SessionKey *bindKey, 
																		 Dz1Asn1OctetStr *authInfo, 
																		 Iso14827Login *data, 
																		 ItsIso14827ClientDomainViolatedSubscription *violatedSub, Dz1Error *err);
static __inline__ ItsIso14827DomainBind *ItsIso14827DomainBind_gen(Dz1Error *err) { return ItsIso14827DomainBind_new(Dz1Asn1Codec_max, Iso14827RejectLogin_max, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainBind_purge(ItsIso14827DomainBind *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainBind_del(ItsIso14827DomainBind *p);
static __inline__ void ItsIso14827DomainBind_delAndSetNull(void *ptr)
{
	ItsIso14827DomainBind **p = (ItsIso14827DomainBind **)ptr;
	if (p) { ItsIso14827DomainBind_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainBind_dump(ItsIso14827DomainBind *p, int tab);
// ItsIso14827DomainBind
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainLoginAccept
typedef struct ItsIso14827DomainLoginAccept
{
	Dz1Asn1UTF8Str									*domainName;
	Dz1Asn1UTF8Str									*peerName;
	Dz1Asn1OctetStr									*user;
	Dz1Asn1Codec									 selectedCodec;
	ItsIso14827CRCCheck								 CRCMode;
	ItsIso14827ServerDomainViolatedPublication		*violatedPub;
} ItsIso14827DomainLoginAccept;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainLoginAccept *ItsIso14827DomainLoginAccept_new(Dz1Asn1UTF8Str *domainName, 
																					   Dz1Asn1UTF8Str *peerName, 
																					   Dz1Asn1OctetStr *user, 
																					   Dz1Asn1Codec selectedCodec, 
																					   ItsIso14827CRCCheck CRCMode, 
																					   ItsIso14827ServerDomainViolatedPublication *violatedPub, Dz1Error *err);
static __inline__ ItsIso14827DomainLoginAccept *ItsIso14827DomainLoginAccept_gen(Dz1Error *err) { return ItsIso14827DomainLoginAccept_new(NULL, NULL, NULL, Dz1Asn1Codec_max, ItsIso14827CRCCheck_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLoginAccept_purge(ItsIso14827DomainLoginAccept *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLoginAccept_del(ItsIso14827DomainLoginAccept *p);
static __inline__ void ItsIso14827DomainLoginAccept_delAndSetNull(void *ptr)
{
	ItsIso14827DomainLoginAccept **p = (ItsIso14827DomainLoginAccept **)ptr;
	if (p) { ItsIso14827DomainLoginAccept_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLoginAccept_dump(ItsIso14827DomainLoginAccept *p, int tab);
// ItsIso14827DomainLoginAccept
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainLoginReject
typedef struct ItsIso14827DomainLoginReject
{
	Dz1Asn1UTF8Str			*domainName;
	Dz1Asn1UTF8Str			*peerName;
	Dz1Asn1OctetStr			*user;
	Iso14827RejectLogin		 reason;
} ItsIso14827DomainLoginReject;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainLoginReject *ItsIso14827DomainLoginReject_new(Dz1Asn1UTF8Str *domainName, 
																					   Dz1Asn1UTF8Str *peerName, 
																					   Dz1Asn1OctetStr *user, 
																					   Iso14827RejectLogin reason, Dz1Error *err);
static __inline__ ItsIso14827DomainLoginReject *ItsIso14827DomainLoginReject_gen(Dz1Error *err) { return ItsIso14827DomainLoginReject_new(NULL, NULL, NULL, Iso14827RejectLogin_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLoginReject_purge(ItsIso14827DomainLoginReject *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLoginReject_del(ItsIso14827DomainLoginReject *p);
static __inline__ void ItsIso14827DomainLoginReject_delAndSetNull(void *ptr)
{
	ItsIso14827DomainLoginReject **p = (ItsIso14827DomainLoginReject **)ptr;
	if (p) { ItsIso14827DomainLoginReject_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLoginReject_dump(ItsIso14827DomainLoginReject *p, int tab);
// ItsIso14827DomainLoginReject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainTerminateClient
typedef struct ItsIso14827DomainTerminateClient
{
	Dz1Asn1UTF8Str			*myDomain;
	Dz1Asn1UTF8Str			*peerDomain;
	Dz1Asn1OctetStr			*user;
	Iso14827Terminate		 reason;
} ItsIso14827DomainTerminateClient;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainTerminateClient *ItsIso14827DomainTerminateClient_new(Dz1Asn1UTF8Str *myDomain, 
																							   Dz1Asn1UTF8Str *peerDomain, 
																							   Dz1Asn1OctetStr *user, 
																							   Iso14827Terminate reason, Dz1Error *err);
static __inline__ ItsIso14827DomainTerminateClient *ItsIso14827DomainTerminateClient_gen(Dz1Error *err) { return ItsIso14827DomainTerminateClient_new(NULL, NULL, NULL, Iso14827Terminate_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainTerminateClient_purge(ItsIso14827DomainTerminateClient *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainTerminateClient_del(ItsIso14827DomainTerminateClient *p);
static __inline__ void ItsIso14827DomainTerminateClient_delAndSetNull(void *ptr)
{
	ItsIso14827DomainTerminateClient **p = (ItsIso14827DomainTerminateClient **)ptr;
	if (p) { ItsIso14827DomainTerminateClient_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainTerminateClient_dump(ItsIso14827DomainTerminateClient *p, int tab);
// ItsIso14827DomainTerminateClient
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainLogout
typedef struct ItsIso14827DomainLogout
{
	Dz1Asn1UTF8Str		*domainName;
	Dz1Asn1UTF8Str		*peerName;
	Dz1Asn1OctetStr		*user;
	Iso14827Logout		 reason;
} ItsIso14827DomainLogout;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainLogout *ItsIso14827DomainLogout_new(Dz1Asn1UTF8Str *domainName, 
																			 Dz1Asn1UTF8Str *peerName, 
																			 Dz1Asn1OctetStr *user, 
																			 Iso14827Logout reason, Dz1Error *err);
static __inline__ ItsIso14827DomainLogout *ItsIso14827DomainLogout_gen(Dz1Error *err) { return ItsIso14827DomainLogout_new(NULL, NULL, NULL, Iso14827Logout_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLogout_purge(ItsIso14827DomainLogout *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLogout_del(ItsIso14827DomainLogout *p);
static __inline__ void ItsIso14827DomainLogout_delAndSetNull(void *ptr)
{
	ItsIso14827DomainLogout **p = (ItsIso14827DomainLogout **)ptr;
	if (p) { ItsIso14827DomainLogout_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainLogout_dump(ItsIso14827DomainLogout *p, int tab);
// ItsIso14827DomainLogout
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainEchoReply
typedef struct ItsIso14827DomainEchoReply
{
	Dz1Asn1UTF8Str		*domainName;
	Dz1Asn1UTF8Str		*peerName;
	Dz1Asn1OctetStr		*user;
	u32_t				 confirmPktNbr;
} ItsIso14827DomainEchoReply;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainEchoReply *ItsIso14827DomainEchoReply_new(Dz1Asn1UTF8Str *domainName, 
																				   Dz1Asn1UTF8Str *peerName, 
																				   Dz1Asn1OctetStr *user, 
																				   u32_t confirmPktNbr, Dz1Error *err);
static __inline__ ItsIso14827DomainEchoReply *ItsIso14827DomainEchoReply_gen(Dz1Error *err) { return ItsIso14827DomainEchoReply_new(NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainEchoReply_purge(ItsIso14827DomainEchoReply *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainEchoReply_del(ItsIso14827DomainEchoReply *p);
static __inline__ void ItsIso14827DomainEchoReply_delAndSetNull(void *ptr)
{
	ItsIso14827DomainEchoReply **p = (ItsIso14827DomainEchoReply **)ptr;
	if (p) { ItsIso14827DomainEchoReply_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainEchoReply_dump(ItsIso14827DomainEchoReply *p, int tab);
// ItsIso14827DomainEchoReply
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainPrepareAccept
typedef struct ItsIso14827DomainPrepareAccept
{
	ItsIso14827DomainType		 domainType;
	Dz1Asn1UTF8Str				*domainName;
	Dz1Asn1UTF8Str				*peerName;
	Dz1Asn1OctetStr				*user;
	u32_t						 serial;
} ItsIso14827DomainPrepareAccept;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainPrepareAccept *ItsIso14827DomainPrepareAccept_new(ItsIso14827DomainType domainType, 
																						   Dz1Asn1UTF8Str *domainName, 
																						   Dz1Asn1UTF8Str *peerName, 
																						   Dz1Asn1OctetStr *user, 
																						   u32_t serial, Dz1Error *err);
static __inline__ ItsIso14827DomainPrepareAccept *ItsIso14827DomainPrepareAccept_gen(Dz1Error *err) { return ItsIso14827DomainPrepareAccept_new(ItsIso14827DomainType_max, NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainPrepareAccept_purge(ItsIso14827DomainPrepareAccept *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainPrepareAccept_del(ItsIso14827DomainPrepareAccept *p);
static __inline__ void ItsIso14827DomainPrepareAccept_delAndSetNull(void *ptr)
{
	ItsIso14827DomainPrepareAccept **p = (ItsIso14827DomainPrepareAccept **)ptr;
	if (p) { ItsIso14827DomainPrepareAccept_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainPrepareAccept_dump(ItsIso14827DomainPrepareAccept *p, int tab);
// ItsIso14827DomainPrepareAccept
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainPrepareReject
typedef struct ItsIso14827DomainPrepareReject
{
	ItsIso14827DomainType			 domainType;
	Dz1Asn1UTF8Str					*domainName;
	Dz1Asn1UTF8Str					*peerName;
	Dz1Asn1OctetStr					*user;
	u32_t							 serial;
	Iso14827RejectSubscription		 reason;
} ItsIso14827DomainPrepareReject;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainPrepareReject *ItsIso14827DomainPrepareReject_new(ItsIso14827DomainType domainType, 
																						   Dz1Asn1UTF8Str *domainName, 
																						   Dz1Asn1UTF8Str *peerName, 
																						   Dz1Asn1OctetStr *user, 
																						   u32_t serial, 
																						   Iso14827RejectSubscription reason, Dz1Error *err);
static __inline__ ItsIso14827DomainPrepareReject *ItsIso14827DomainPrepareReject_gen(Dz1Error *err) { return ItsIso14827DomainPrepareReject_new(ItsIso14827DomainType_max, NULL, NULL, NULL, 0, Iso14827RejectSubscription_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainPrepareReject_purge(ItsIso14827DomainPrepareReject *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainPrepareReject_del(ItsIso14827DomainPrepareReject *p);
static __inline__ void ItsIso14827DomainPrepareReject_delAndSetNull(void *ptr)
{
	ItsIso14827DomainPrepareReject **p = (ItsIso14827DomainPrepareReject **)ptr;
	if (p) { ItsIso14827DomainPrepareReject_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainPrepareReject_dump(ItsIso14827DomainPrepareReject *p, int tab);
// ItsIso14827DomainPrepareReject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainDataProvide
typedef struct ItsIso14827DomainDataProvide
{
	ItsIso14827DomainType		 domainType;
	Dz1Asn1UTF8Str				*domainName;
	Dz1Asn1UTF8Str				*peerName;
	Dz1Asn1OctetStr				*user;
	u32_t						 serial;
	Iso14827EndAppMsg			*eam;
} ItsIso14827DomainDataProvide;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainDataProvide *ItsIso14827DomainDataProvide_new(ItsIso14827DomainType domainType, 
																					   Dz1Asn1UTF8Str *domainName, 
																					   Dz1Asn1UTF8Str *peerName, 
																					   Dz1Asn1OctetStr *user, 
																					   u32_t serial, 
																					   Iso14827EndAppMsg *eam, Dz1Error *err);
static __inline__ ItsIso14827DomainDataProvide *ItsIso14827DomainDataProvide_gen(Dz1Error *err) { return ItsIso14827DomainDataProvide_new(ItsIso14827DomainType_max, NULL, NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainDataProvide_purge(ItsIso14827DomainDataProvide *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainDataProvide_del(ItsIso14827DomainDataProvide *p);
static __inline__ void ItsIso14827DomainDataProvide_delAndSetNull(void *ptr)
{
	ItsIso14827DomainDataProvide **p = (ItsIso14827DomainDataProvide **)ptr;
	if (p) { ItsIso14827DomainDataProvide_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainDataProvide_dump(ItsIso14827DomainDataProvide *p, int tab);
// ItsIso14827DomainDataProvide
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainDataControl
typedef struct ItsIso14827DomainDataControl
{
	ItsIso14827DomainType		 domainType;
	Dz1Asn1UTF8Str				*domainName;
	Dz1Asn1UTF8Str				*peerName;
	Dz1Asn1OctetStr				*user;
	u32_t						 serial;
	Iso14827PublicationMgmt		 cmd;
} ItsIso14827DomainDataControl;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainDataControl *ItsIso14827DomainDataControl_new(ItsIso14827DomainType domainType, 
																					   Dz1Asn1UTF8Str *domainName, 
																					   Dz1Asn1UTF8Str *peerName, 
																					   Dz1Asn1OctetStr *user, 
																					   u32_t serial, 
																					   Iso14827PublicationMgmt cmd, Dz1Error *err);
static __inline__ ItsIso14827DomainDataControl *ItsIso14827DomainDataControl_gen(Dz1Error *err) { return ItsIso14827DomainDataControl_new(ItsIso14827DomainType_max, NULL, NULL, NULL, 0, Iso14827PublicationMgmt_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainDataControl_purge(ItsIso14827DomainDataControl *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainDataControl_del(ItsIso14827DomainDataControl *p);
static __inline__ void ItsIso14827DomainDataControl_delAndSetNull(void *ptr)
{
	ItsIso14827DomainDataControl **p = (ItsIso14827DomainDataControl **)ptr;
	if (p) { ItsIso14827DomainDataControl_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainDataControl_dump(ItsIso14827DomainDataControl *p, int tab);
// ItsIso14827DomainDataControl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainSubscription
typedef struct ItsIso14827DomainSubscription
{
	ItsIso14827DomainType			 domainType;
	Dz1Asn1UTF8Str					*domainName;
	Dz1Asn1UTF8Str					*peerName;
	Dz1Asn1OctetStr					*user;
	Iso14827SubscriptionData		*data;
	u32_t							 retSerial;
	Iso14827RejectSubscription		 retError;
} ItsIso14827DomainSubscription;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainSubscription *ItsIso14827DomainSubscription_new(ItsIso14827DomainType domainType, 
																						 Dz1Asn1UTF8Str *domainName, 
																						 Dz1Asn1UTF8Str *peerName, 
																						 Dz1Asn1OctetStr *user, 
																						 Iso14827SubscriptionData *data, Dz1Error *err);
static __inline__ ItsIso14827DomainSubscription *ItsIso14827DomainSubscription_gen(Dz1Error *err) { return ItsIso14827DomainSubscription_new(ItsIso14827DomainType_max, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSubscription_purge(ItsIso14827DomainSubscription *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSubscription_del(ItsIso14827DomainSubscription *p);
static __inline__ void ItsIso14827DomainSubscription_delAndSetNull(void *ptr)
{
	ItsIso14827DomainSubscription **p = (ItsIso14827DomainSubscription **)ptr;
	if (p) { ItsIso14827DomainSubscription_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSubscription_dump(ItsIso14827DomainSubscription *p, int tab);
// ItsIso14827DomainSubscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainSubCancel
typedef struct ItsIso14827DomainSubCancel
{
	ItsIso14827DomainType			 domainType;
	Dz1Asn1UTF8Str					*domainName;
	Dz1Asn1UTF8Str					*peerName;
	Dz1Asn1OctetStr					*user;
	u32_t							 serial;
	Iso14827SubscriptionCancel		 reason;
} ItsIso14827DomainSubCancel;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainSubCancel *ItsIso14827DomainSubCancel_new(ItsIso14827DomainType domainType, 
																				   Dz1Asn1UTF8Str *domainName, 
																				   Dz1Asn1UTF8Str *peerName, 
																				   Dz1Asn1OctetStr *user, 
																				   u32_t serial, 
																				   Iso14827SubscriptionCancel reason, Dz1Error *err);
static __inline__ ItsIso14827DomainSubCancel *ItsIso14827DomainSubCancel_gen(Dz1Error *err) { return ItsIso14827DomainSubCancel_new(ItsIso14827DomainType_max, NULL, NULL, NULL, 0, Iso14827SubscriptionCancel_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSubCancel_purge(ItsIso14827DomainSubCancel *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSubCancel_del(ItsIso14827DomainSubCancel *p);
static __inline__ void ItsIso14827DomainSubCancel_delAndSetNull(void *ptr)
{
	ItsIso14827DomainSubCancel **p = (ItsIso14827DomainSubCancel **)ptr;
	if (p) { ItsIso14827DomainSubCancel_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainSubCancel_dump(ItsIso14827DomainSubCancel *p, int tab);
// ItsIso14827DomainSubCancel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainRejectPubData
typedef struct ItsIso14827DomainRejectPubData
{
	ItsIso14827DomainType			 domainType;
	Dz1Asn1UTF8Str					*domainName;
	Dz1Asn1UTF8Str					*peerName;
	Dz1Asn1OctetStr					*user;
	u32_t							 serial;
	u32_t							 pubSerial;
	Iso14827RejectPubDataReason		 reason;
} ItsIso14827DomainRejectPubData;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainRejectPubData *ItsIso14827DomainRejectPubData_new(ItsIso14827DomainType domainType, 
																						   Dz1Asn1UTF8Str *domainName, 
																						   Dz1Asn1UTF8Str *peerName, 
																						   Dz1Asn1OctetStr *user, 
																						   u32_t serial, 
																						   u32_t pubSerial, 
																						   Iso14827RejectPubDataReason reason, Dz1Error *err);
static __inline__ ItsIso14827DomainRejectPubData *ItsIso14827DomainRejectPubData_gen(Dz1Error *err) { return ItsIso14827DomainRejectPubData_new(ItsIso14827DomainType_max, NULL, NULL, NULL, 0, 0, Iso14827RejectPubDataReason_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainRejectPubData_purge(ItsIso14827DomainRejectPubData *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainRejectPubData_del(ItsIso14827DomainRejectPubData *p);
static __inline__ void ItsIso14827DomainRejectPubData_delAndSetNull(void *ptr)
{
	ItsIso14827DomainRejectPubData **p = (ItsIso14827DomainRejectPubData **)ptr;
	if (p) { ItsIso14827DomainRejectPubData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainRejectPubData_dump(ItsIso14827DomainRejectPubData *p, int tab);
// ItsIso14827DomainRejectPubData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ViolatedPublication
typedef struct ItsIso14827ViolatedPublication
{
	ItsIso14827DomainType		 domainType;
	Dz1Asn1UTF8Str				*myDomain;
	Dz1Asn1UTF8Str				*peerDomain;
	Dz1Asn1OctetStr				*user;
	Iso14827Publication			*pub;
} ItsIso14827ViolatedPublication;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ViolatedPublication *ItsIso14827ViolatedPublication_new(ItsIso14827DomainType domainType, 
																						   Dz1Asn1UTF8Str *myDomain, 
																						   Dz1Asn1UTF8Str *peerDomain, 
																						   Dz1Asn1OctetStr *user, 
																						   Iso14827Publication *pub, Dz1Error *err);
static __inline__ ItsIso14827ViolatedPublication *ItsIso14827ViolatedPublication_gen(Dz1Error *err) { return ItsIso14827ViolatedPublication_new(ItsIso14827DomainType_max, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ViolatedPublication_purge(ItsIso14827ViolatedPublication *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ViolatedPublication_del(ItsIso14827ViolatedPublication *p);
static __inline__ void ItsIso14827ViolatedPublication_delAndSetNull(void *ptr)
{
	ItsIso14827ViolatedPublication **p = (ItsIso14827ViolatedPublication **)ptr;
	if (p) { ItsIso14827ViolatedPublication_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ViolatedPublication_dump(ItsIso14827ViolatedPublication *p, int tab);
// ItsIso14827ViolatedPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ViolatedSubscription
typedef struct ItsIso14827ViolatedSubscription
{
	ItsIso14827DomainType		 domainType;
	Dz1Asn1UTF8Str				*myDomain;
	Dz1Asn1UTF8Str				*peerDomain;
	Dz1Asn1OctetStr				*user;
	Iso14827Subscription		*sub;
} ItsIso14827ViolatedSubscription;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ViolatedSubscription *ItsIso14827ViolatedSubscription_new(ItsIso14827DomainType domainType, 
																							 Dz1Asn1UTF8Str *myDomain, 
																							 Dz1Asn1UTF8Str *peerDomain, 
																							 Dz1Asn1OctetStr *user, 
																							 Iso14827Subscription *sub, Dz1Error *err);
static __inline__ ItsIso14827ViolatedSubscription *ItsIso14827ViolatedSubscription_gen(Dz1Error *err) { return ItsIso14827ViolatedSubscription_new(ItsIso14827DomainType_max, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ViolatedSubscription_purge(ItsIso14827ViolatedSubscription *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ViolatedSubscription_del(ItsIso14827ViolatedSubscription *p);
static __inline__ void ItsIso14827ViolatedSubscription_delAndSetNull(void *ptr)
{
	ItsIso14827ViolatedSubscription **p = (ItsIso14827ViolatedSubscription **)ptr;
	if (p) { ItsIso14827ViolatedSubscription_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ViolatedSubscription_dump(ItsIso14827ViolatedSubscription *p, int tab);
// ItsIso14827ViolatedSubscription
////////////////////////////////////////////////////////////////////////////////

#endif
