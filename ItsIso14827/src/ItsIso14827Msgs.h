#ifndef _DZ1_TDC_ITS_ISO14827_MSGS_H_
#define _DZ1_TDC_ITS_ISO14827_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827MsgDefault
typedef struct ItsIso14827MsgDefault
{
	u32_t		*dummy;
} ItsIso14827MsgDefault;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827MsgDefault *ItsIso14827MsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ ItsIso14827MsgDefault *ItsIso14827MsgDefault_gen(Dz1Error *err) { return ItsIso14827MsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827MsgDefault_purge(ItsIso14827MsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827MsgDefault_del(ItsIso14827MsgDefault *p);
static __inline__ void ItsIso14827MsgDefault_delAndSetNull(void *ptr)
{
	ItsIso14827MsgDefault **p = (ItsIso14827MsgDefault **)ptr;
	if (p) { ItsIso14827MsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827MsgDefault_dump(ItsIso14827MsgDefault *p, int tab);
// ItsIso14827MsgDefault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827OpenPort
typedef struct ItsIso14827OpenPort
{
	u16_t					port;
	Dz1Asn1Codec			initialCodec;
	ItsIso14827CRCCheck		initialCRCMode;
} ItsIso14827OpenPort;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827OpenPort *ItsIso14827OpenPort_new(u16_t port, 
																	 Dz1Asn1Codec initialCodec, 
																	 ItsIso14827CRCCheck initialCRCMode, Dz1Error *err);
static __inline__ ItsIso14827OpenPort *ItsIso14827OpenPort_gen(Dz1Error *err) { return ItsIso14827OpenPort_new(0, Dz1Asn1Codec_max, ItsIso14827CRCCheck_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827OpenPort_purge(ItsIso14827OpenPort *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827OpenPort_del(ItsIso14827OpenPort *p);
static __inline__ void ItsIso14827OpenPort_delAndSetNull(void *ptr)
{
	ItsIso14827OpenPort **p = (ItsIso14827OpenPort **)ptr;
	if (p) { ItsIso14827OpenPort_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827OpenPort_dump(ItsIso14827OpenPort *p, int tab);
// ItsIso14827OpenPort
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClosePort
typedef struct ItsIso14827ClosePort
{
	u16_t		port;
} ItsIso14827ClosePort;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827ClosePort *ItsIso14827ClosePort_new(u16_t port, Dz1Error *err);
static __inline__ ItsIso14827ClosePort *ItsIso14827ClosePort_gen(Dz1Error *err) { return ItsIso14827ClosePort_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClosePort_purge(ItsIso14827ClosePort *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClosePort_del(ItsIso14827ClosePort *p);
static __inline__ void ItsIso14827ClosePort_delAndSetNull(void *ptr)
{
	ItsIso14827ClosePort **p = (ItsIso14827ClosePort **)ptr;
	if (p) { ItsIso14827ClosePort_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827ClosePort_dump(ItsIso14827ClosePort *p, int tab);
// ItsIso14827ClosePort
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DebugStatus
typedef struct ItsIso14827DebugStatus
{
	ItsIso14827DomainType		 type;
	Dz1Asn1UTF8Str				*myDomain;
} ItsIso14827DebugStatus;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DebugStatus *ItsIso14827DebugStatus_new(ItsIso14827DomainType type, 
																		   Dz1Asn1UTF8Str *myDomain, Dz1Error *err);
static __inline__ ItsIso14827DebugStatus *ItsIso14827DebugStatus_gen(Dz1Error *err) { return ItsIso14827DebugStatus_new(ItsIso14827DomainType_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DebugStatus_purge(ItsIso14827DebugStatus *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DebugStatus_del(ItsIso14827DebugStatus *p);
static __inline__ void ItsIso14827DebugStatus_delAndSetNull(void *ptr)
{
	ItsIso14827DebugStatus **p = (ItsIso14827DebugStatus **)ptr;
	if (p) { ItsIso14827DebugStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DebugStatus_dump(ItsIso14827DebugStatus *p, int tab);
// ItsIso14827DebugStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DebugPktDump
typedef struct ItsIso14827DebugPktDump
{
	u32_t		flag;
} ItsIso14827DebugPktDump;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DebugPktDump *ItsIso14827DebugPktDump_new(u32_t flag, Dz1Error *err);
static __inline__ ItsIso14827DebugPktDump *ItsIso14827DebugPktDump_gen(Dz1Error *err) { return ItsIso14827DebugPktDump_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DebugPktDump_purge(ItsIso14827DebugPktDump *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DebugPktDump_del(ItsIso14827DebugPktDump *p);
static __inline__ void ItsIso14827DebugPktDump_delAndSetNull(void *ptr)
{
	ItsIso14827DebugPktDump **p = (ItsIso14827DebugPktDump **)ptr;
	if (p) { ItsIso14827DebugPktDump_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DebugPktDump_dump(ItsIso14827DebugPktDump *p, int tab);
// ItsIso14827DebugPktDump
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainCtrl
typedef struct ItsIso14827DomainCtrl
{
	ItsIso14827DomainType		 myDomainType;
	Dz1Asn1UTF8Str				*domainName;
	Dz1Asn1UTF8Str				*peerName;
	Dz1Asn1OctetStr				*user;
	u32_t						 flag;
	bool_t						 on_off;
} ItsIso14827DomainCtrl;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainCtrl *ItsIso14827DomainCtrl_new(ItsIso14827DomainType myDomainType, 
																		 Dz1Asn1UTF8Str *domainName, 
																		 Dz1Asn1UTF8Str *peerName, 
																		 Dz1Asn1OctetStr *user, 
																		 u32_t flag, 
																		 bool_t on_off, Dz1Error *err);
static __inline__ ItsIso14827DomainCtrl *ItsIso14827DomainCtrl_gen(Dz1Error *err) { return ItsIso14827DomainCtrl_new(ItsIso14827DomainType_max, NULL, NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainCtrl_purge(ItsIso14827DomainCtrl *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainCtrl_del(ItsIso14827DomainCtrl *p);
static __inline__ void ItsIso14827DomainCtrl_delAndSetNull(void *ptr)
{
	ItsIso14827DomainCtrl **p = (ItsIso14827DomainCtrl **)ptr;
	if (p) { ItsIso14827DomainCtrl_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainCtrl_dump(ItsIso14827DomainCtrl *p, int tab);
// ItsIso14827DomainCtrl
////////////////////////////////////////////////////////////////////////////////

#endif
