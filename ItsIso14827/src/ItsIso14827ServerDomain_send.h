#ifndef ITS_ISO14827_SERVER_DOMAIN_SEND_H_LOCAL
#define ITS_ISO14827_SERVER_DOMAIN_SEND_H_LOCAL

#include "ItsIso14827ServerDomainDef.h"

/*
DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_send(ItsIso14827ServerDomainClientEntry *client,
															 Dz1Asn1UTF8Str *domainName,
															 ItsIso14827SessionEntry *session,
															 Dz1Asn1OctetStr *authInfo, s32_t priority,
															 Iso14827PDUs **pdu, bool_t needWait,
															 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_confirm(ItsIso14827ServerDomainClientEntry *client,
																Dz1Asn1UTF8Str *domainName,
																ItsIso14827SessionEntry *session, u32_t pktNbr,
																Iso14827C2CAuthMsg **sent,
																void *uArg, void *uRsc, void *timer);
*/
///////////////////////////////////////////////////////////////////////////////
// Send FrED
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_sendFrED(ItsIso14827ServerDomainClientEntry *e,
																 Dz1Asn1UTF8Str *domainName,
																 ItsIso14827SessionEntry *session,
																 u32_t confirmPktNbr, u32_t *sentPktNbr,
																 u32_t hdr_opt_flag,
																 void *uArg, void *uRsc, void *timer);

///////////////////////////////////////////////////////////////////////////////
// Send Reject
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_sendRejectLogin(ItsIso14827ServerDomainClientEntry *e,
																		Dz1Asn1UTF8Str *domainName,
																		ItsIso14827SessionEntry *session,
																		u32_t confirmPktNbr, Iso14827RejectLogin reason,
																		u32_t hdr_opt_flag,
																		void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_sendRejectSubscription(ItsIso14827ServerDomainClientEntry *e,
																			   Dz1Asn1UTF8Str *domainName,
																			   ItsIso14827SessionEntry *session,
																			   u32_t confirmPktNbr, Iso14827RejectSubscription reason,
																			   u32_t hdr_opt_flag,
																			   void *uArg, void *uRsc, void *timer);

///////////////////////////////////////////////////////////////////////////////
// Send Accept
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_sendAcceptLogin(ItsIso14827ServerDomainClientEntry *client,
																		Dz1Asn1UTF8Str *domainName,
																		ItsIso14827SessionEntry *session,
																		u32_t confirmPktNbr, Dz1Asn1Codec selected,
																		u32_t hdr_opt_flag,
																		void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_sendAcceptSingleSubscription(ItsIso14827ServerDomainClientEntry *client,
																					 Dz1Asn1UTF8Str *domainName,
																					 ItsIso14827SessionEntry *session,
																					 u32_t confirmPktNbr,
																					 u32_t hdr_opt_flag,
																					 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_sendAcceptRegisteredSubscription(ItsIso14827ServerDomainClientEntry *client,
																						 Dz1Asn1UTF8Str *domainName,
																						 ItsIso14827SessionEntry *session,
																						 u32_t confirmPktNbr,
// 																						 u32_t subID,
																						 u32_t updateDelayQty, 
																						 u32_t hdr_opt_flag,
																						 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_sendAcceptPub(ItsIso14827ServerDomainClientEntry *client,
																	  Dz1Asn1UTF8Str *domainName,
																	  ItsIso14827SessionEntry *session,
																	  u32_t confirmPktNbr, u32_t hdr_opt_flag,
																	  void *uArg, void *uRsc, void *timer);
DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_sendRejectPub(ItsIso14827ServerDomainClientEntry *client,
																	  Dz1Asn1UTF8Str *domainName,
																	  ItsIso14827SessionEntry *session,
																	  u32_t confirmPktNbr, Iso14827RejectPublication reason, u32_t hdr_opt_flag,
																	  void *uArg, void *uRsc, void *timer);

///////////////////////////////////////////////////////////////////////////////
// Send Terminate
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntry_sendTerminate(ItsIso14827ServerDomainClientEntry *client,
																	  Dz1Asn1UTF8Str *domainName,
																	  ItsIso14827SessionEntry *session,
																	  Iso14827Terminate reason, u32_t hdr_opt_flag,
																	  void *uArg, void *uRsc, void *timer);
#endif