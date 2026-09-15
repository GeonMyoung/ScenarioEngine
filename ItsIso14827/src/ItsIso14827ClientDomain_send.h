#ifndef ITS_ISO_14827_CLIENT_DOMAIN_SEND_H_LOCAL
#define ITS_ISO_14827_CLIENT_DOMAIN_SEND_H_LOCAL

#include "ItsIso14827ClientDomainDef.h"

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomainServerEntry_sendLogin(ItsIso14827ClientDomainServerEntry *server,
																  ItsIso14827SessionEntry *session,
																  Dz1Asn1UTF8Str *domainName,
																  Dz1Asn1OctetStr *authInfo,
																  Iso14827Login **login,
																  u32_t hdr_opt_flag,
																  void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomainServerEntry_sendLogout(ItsIso14827ClientDomainServerEntry *server,
																   ItsIso14827SessionEntry *session,
																   Dz1Asn1UTF8Str *domainName, Iso14827Logout reason,
													  u32_t hdr_opt_flag,
																   void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomainServerEntry_sendFrED(ItsIso14827ClientDomainServerEntry *server,
																 ItsIso14827SessionEntry *session,
																 Dz1Asn1UTF8Str *domainName,
																 u32_t confirmPktNbr, u32_t *sentPktNbr,
													  u32_t hdr_opt_flag,
																 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomainServerEntry_sendSubscriptionData(ItsIso14827ClientDomainServerEntry *server,
																			 ItsIso14827SessionEntry *session,
																			 Dz1Asn1UTF8Str *domainName,
																			 u32_t serial, Iso14827SubscriptionData *data,
													  u32_t hdr_opt_flag,
																			 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomainServerEntry_sendSubscriptionCancel(ItsIso14827ClientDomainServerEntry *server,
																			   ItsIso14827SessionEntry *session,
																			   Dz1Asn1UTF8Str *domainName,
																			   u32_t serial, Iso14827SubscriptionCancel reason,
													  u32_t hdr_opt_flag,
																			   void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsISo14827ClientDomainServerEntry_sendAcceptPub(ItsIso14827ClientDomainServerEntry *server,
																	  ItsIso14827SessionEntry *session,
																	  Dz1Asn1UTF8Str *domainName,
																	  u32_t confirmPktNbr,
													  u32_t hdr_opt_flag,
																	  void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomainServerEntry_sendRejectPub(ItsIso14827ClientDomainServerEntry *server,
																	  ItsIso14827SessionEntry *session,
																	  Dz1Asn1UTF8Str *domainName,
																	  u32_t confirmPktNbr, Iso14827RejectPublication reason,
													  u32_t hdr_opt_flag,
																	  void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error ItsIso14827ClientDomainServerEntry_sendRejectPubData(ItsIso14827ClientDomainServerEntry *server,
																		  ItsIso14827SessionEntry *session,
																		  Dz1Asn1UTF8Str *domainName,
																		  u32_t subSerial, u32_t pubSerial,
																		  Iso14827RejectPubDataReason reason,
													  u32_t hdr_opt_flag,
																		  void *uArg, void *uRsc, void *timer);

#endif