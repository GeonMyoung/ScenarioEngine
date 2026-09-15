#ifndef ITS_ISO_14827_DOMAIN_SEND_H_LOCAL
#define ITS_ISO_14827_DOMAIN_SEND_H_LOCAL

#include "ItsIso14827Domain_txFIFO.h"
#include "ItsIso14827SessionDef.h"

// DZ1_CPPLINK Dz1Error ItsIso14827Domain_send_no_retry(ItsIso14827SessionEntry *session,
// 													 Dz1Asn1OctetStr *authInfo, s32_t priority,
// 													 Iso14827PDUs **pdu,
// 													 u32_t pktDumpFlag);
DZ1_CPPLINK Dz1Error ItsIso14827Domain_send_no_retry(ItsIso14827SessionEntry *session,
													 Dz1Asn1OctetStr *authInfo, s32_t priority,
													 Iso14827PDUs **pdu,
													 u32_t hdr_opt_flag, Dz1Asn1UTF8Str *sender, Dz1Asn1UTF8Str *dest,
													 u32_t pktDumpFlag);

DZ1_CPPLINK Dz1Error ItsIso14827Domain_send(ItsIso14827DomainTxFifo *txFifo,
											ItsIso14827SessionEntry *session,
											ItsIso14827DomainType domainType,
											u32_t hdr_opt_flag,
											Dz1Asn1UTF8Str *domainName, Dz1Asn1UTF8Str *peerName,
											Dz1Asn1OctetStr *user, Dz1Asn1OctetStr *authInfo, 
											u32_t responseWaitTime, u32_t heartBeatDuration, s32_t priority,
											Iso14827PDUs **pdu, bool_t needWait,
											ItsIso14827DomainTxFail sendFail,
											void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827Domain_confirm(ItsIso14827DomainTxFifo *txFifo,
											   ItsIso14827SessionEntry *session, 
											   ItsIso14827DomainType type,
											   u32_t hdr_opt_flag,
											   Dz1Asn1UTF8Str *domainName,
											   Dz1Asn1UTF8Str *peerName,
											   Dz1Asn1OctetStr *user,
											   u32_t responseWaitTime,
											   u32_t pktNbr, Iso14827C2CAuthMsg **sent,
											   void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK void ItsIso14827Domain_sendFail(void *uArg, void *uRsc, void *timer,
										   ItsIso14827DomainType type, Dz1Asn1UTF8Str *domainName,
										   Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
										   Iso14827C2CAuthMsg *msg, u32_t hdr_opt_flag);
#endif