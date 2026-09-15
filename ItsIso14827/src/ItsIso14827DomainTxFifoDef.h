#ifndef _DZ1_TDC_ITS_ISO14827_DOMAIN_TX_FIFO_DEF_H_
#define _DZ1_TDC_ITS_ISO14827_DOMAIN_TX_FIFO_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainTxStatus
typedef enum ItsIso14827DomainTxStatus
{
	ItsIso14827DomainTxStatus_none,
	ItsIso14827DomainTxStatus_sent,
	ItsIso14827DomainTxStatus_final,
	ItsIso14827DomainTxStatus_max
} ItsIso14827DomainTxStatus;

DZ1_CPPLINK str_t ItsIso14827DomainTxStatusStrA(ItsIso14827DomainTxStatus v);
DZ1_CPPLINK ItsIso14827DomainTxStatus ItsIso14827DomainTxStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ItsIso14827DomainTxStatusStrW(ItsIso14827DomainTxStatus v);
DZ1_CPPLINK ItsIso14827DomainTxStatus ItsIso14827DomainTxStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define ItsIso14827DomainTxStatusStr ItsIso14827DomainTxStatusStrW
#define ItsIso14827DomainTxStatusFromStr ItsIso14827DomainTxStatusFromStrW
#else // UNICODE
#define ItsIso14827DomainTxStatusStr ItsIso14827DomainTxStatusStrA
#define ItsIso14827DomainTxStatusFromStr ItsIso14827DomainTxStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ItsIso14827DomainTxStatusStr ItsIso14827DomainTxStatusStrA
#define ItsIso14827DomainTxStatusFromStr ItsIso14827DomainTxStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainTxStatus *ItsIso14827DomainTxStatus_new(ItsIso14827DomainTxStatus *src, Dz1Error *err);
static __inline__ ItsIso14827DomainTxStatus *ItsIso14827DomainTxStatus_gen(Dz1Error *err) { ItsIso14827DomainTxStatus v = ItsIso14827DomainTxStatus_max; return ItsIso14827DomainTxStatus_new(&v, err); }
static __inline__ void ItsIso14827DomainTxStatus_del(ItsIso14827DomainTxStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ItsIso14827DomainTxStatus_delAndSetNull(void *ptr)
{
	ItsIso14827DomainTxStatus **p = (ItsIso14827DomainTxStatus **)ptr;
	if (p != NULL) { ItsIso14827DomainTxStatus_del(*p); *p = NULL; }
}
// ItsIso14827DomainTxStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainTxFail
typedef void (*ItsIso14827DomainTxFail)(
					void *uArg, 
					void *uRsc, 
					void *timer, 
					ItsIso14827DomainType type, 
					Dz1Asn1UTF8Str *domainName, 
					Dz1Asn1UTF8Str *peerName, 
					Dz1Asn1OctetStr *user, 
					Iso14827C2CAuthMsg *c2c, 
					u32_t hdr_opt_flag);
// ItsIso14827DomainTxFail
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainTxEntry
typedef struct ItsIso14827DomainTxEntry
{
	Iso14827C2CAuthMsg			*c2c;
	u32_t						*status;
	ItsIso14827DomainTxFail		 sendFail;
	u32_t						 hdr_opt_flag;
} ItsIso14827DomainTxEntry;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827DomainTxEntry *ItsIso14827DomainTxEntry_new(Iso14827C2CAuthMsg *c2c, 
																			   u32_t *status, 
																			   ItsIso14827DomainTxFail sendFail, 
																			   u32_t hdr_opt_flag, Dz1Error *err);
static __inline__ ItsIso14827DomainTxEntry *ItsIso14827DomainTxEntry_gen(Dz1Error *err) { return ItsIso14827DomainTxEntry_new(NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainTxEntry_purge(ItsIso14827DomainTxEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainTxEntry_del(ItsIso14827DomainTxEntry *p);
static __inline__ void ItsIso14827DomainTxEntry_delAndSetNull(void *ptr)
{
	ItsIso14827DomainTxEntry **p = (ItsIso14827DomainTxEntry **)ptr;
	if (p) { ItsIso14827DomainTxEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827DomainTxEntry_dump(ItsIso14827DomainTxEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ItsIso14827DomainTxEntry_cmp(ItsIso14827DomainTxEntry *a, ItsIso14827DomainTxEntry *b); 
// ItsIso14827DomainTxEntry
////////////////////////////////////////////////////////////////////////////////

#endif
