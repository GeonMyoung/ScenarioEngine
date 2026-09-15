#ifndef ITS_ISO_SERVER_DOMAIN_MGR_MAIN_H_LOCAL
#define ITS_ISO_SERVER_DOMAIN_MGR_MAIN_H_LOCAL

#include "ItsIso14827DomainDef.h"

DZ1_CPPLINK	ItsIso14827DomainMgr	*ItsIso14827DomainMgr_init(void *tSelf, Dz1Error *err);
DZ1_CPPLINK Dz1Error				 ItsIso14827DomainMgr_received(ItsIso14827DomainMgr *mgr,
																   ItsIso14827SessionEntry *session,
																   Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
																   Iso14827PDUs *pdu, bool_t isRetried,
																   void *uArg, void *uRsc, void *timer);

///////////////////////////////////////////////////////////////////////////////
// Session이 끊어져서 user@PEER만 사라지는 경우
DZ1_CPPLINK void					 ItsIso14827DomainMgr_sessionDisconnected(ItsIso14827DomainMgr *domain,
																		  ItsIso14827SessionKey *key, void *timer);

DZ1_CPPLINK Dz1TaskProcStatus		 ItsIso14827DomainMgr_heartBeatDurationTimeout(void *uArg, void *uRsc, void *timer,
																				   void **tData, Dz1Error *errp);

DZ1_CPPLINK ItsIso14827Domain		*ItsIso14827DomainMgr_findByKey(ItsIso14827DomainMgr *mgr, ItsIso14827DomainKey *key);

DZ1_CPPLINK void					 ItsIso14827DomainMgr_terminate(ItsIso14827DomainMgr *mgr);
/*
// Server Only
// return is not null : Login Result is Concluded
// return is null ->
//		err.code == 0 : Login Result will be inform
//		err.code != 0 : Internal Processing Error
DZ1_CPPLINK ItsIso14827LoginResult			*ItsIso14827Domain_login(ItsIso14827Domain *dest, Dz1Asn1UTF8Str *client,
																	Dz1Asn1OctetStr *user, Dz1Asn1OctetStr *pass,
																	Dz1Asn1OctetStr *authInfo, s32_t timeout,
																	ItsIso14827SessionKey *key,
																	Dz1Error *err);
// Server Only
DZ1_CPPLINK Dz1Error						 ItsIso14827Domain_authenticated(ItsIso14827Domain *dst, Dz1Asn1UTF8Str *peer,
																			 ItsIso14827LoginResult *result,
																			 void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK Dz1Error						 ItsIso14827Domain_received(ItsIso14827Domain *dst, ItsIso14827SessionKey *skey,
																		u32_t pktNbr, s32_t priority,
																		Iso14827PDUs *pdu, bool_t isRetried,
																		void *uArg, void *uRsc, void *timer);

DZ1_CPPLINK ItsIso14827CodecList const*const ItsIso14827Domain_getCodecRules(ItsIso14827Domain *p,
																			 ItsIso14827SessionKey *key,
																			 Dz1Error *err);
// Client와 협상 없이 Subscription Cleanup
DZ1_CPPLINK void							 ItsIso14827Domain_sessionShutdown(ItsIso14827Domain *domain, ItsIso14827SessionKey *key);
*/

#endif
