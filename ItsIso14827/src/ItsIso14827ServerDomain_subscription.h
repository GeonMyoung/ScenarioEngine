#ifndef ITS_ISO14827_SERVER_DOMAIN_SUBSCRIPTION_H_LOCAL
#define ITS_ISO14827_SERVER_DOMAIN_SUBSCRIPTION_H_LOCAL

#include "ItsIso14827ServerDomainDef.h"

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntrySubscription_recv(ItsIso14827ServerDomain *server,
															 ItsIso14827ServerDomainClientEntry *client,
															 ItsIso14827SessionEntry *session,
															 Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
															 Iso14827PDUs *pdu, bool_t isRetried,
															 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntrySubscription_nak(ItsIso14827ServerDomainClientEntry *client,
																		Dz1Asn1UTF8Str *domainName,
																		ItsIso14827SessionEntry *session,
																		Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
																		Iso14827PDUs *pdu, Iso14827C2CAuthMsg *sent,
																		void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntrySubscription_accept(ItsIso14827ServerDomainClientEntry *client,
																		   Dz1Asn1UTF8Str *domainName,
																		   ItsIso14827SessionEntry *session,
																		   u32_t serial, void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntrySubscription_reject(ItsIso14827ServerDomainClientEntry *client,
																		   Dz1Asn1UTF8Str *domainName,
																		   ItsIso14827SessionEntry *session,
																		   u32_t serial, Iso14827RejectSubscription reason,
																		   void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntrySubscription_publication(ItsIso14827ServerDomainClientEntry *client,
																				Dz1Asn1UTF8Str *domainName,
																				ItsIso14827SessionEntry *session,
																				u32_t serial, Iso14827EndAppMsg **eam,
																				void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainClientEntrySubscription_pubControl(ItsIso14827ServerDomainClientEntry *client,
																			   Dz1Asn1UTF8Str *domainName,
																			   ItsIso14827SessionEntry *session,
																			   u32_t serial, Iso14827PublicationMgmt cmd,
																			   void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK void ItsIso14827ServerDomainClientEntrySubscription_disconnected(ItsIso14827ServerDomainClientEntry *client,
																			 Dz1Asn1UTF8Str *domainName, void *timer);

#endif