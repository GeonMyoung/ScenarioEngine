#ifndef ITS_ISO_SERVER_TIMER_UTIL_H_LOCAL
#define ITS_ISO_SERVER_TIMER_UTIL_H_LOCAL

#include <dz1_task_timer.h>
#include "ItsIso14827Timer.h"

#define TIMER_TYPE_SESSION						0x10000000

#define SESSION_ALIVE_TIMER						(TIMER_TYPE_SESSION | 0x00000001)

#define TIMER_TYPE_DOMAIN						0x20000000

#define DOMAIN_RETRANSMIT_TIMER					(TIMER_TYPE_DOMAIN | 0x00000001)
#define DOMAIN_HEARTBEAT_DURATION_TIMER			(TIMER_TYPE_DOMAIN | 0x00000002)
#define DOMAIN_HEARTBEAT_PERIOD_TIMER			(TIMER_TYPE_DOMAIN | 0x00000003)

#define TIMER_TYPE_DOMAIN_SUBSCRIPTION			0x01000000

#define DOMAIN_SUBSCRIPTION_REGISTERED_START	(TIMER_TYPE_DOMAIN | TIMER_TYPE_DOMAIN_SUBSCRIPTION | 0x00000001)
#define DOMAIN_SUBSCRIPTION_REGISTERED_STOP		(TIMER_TYPE_DOMAIN | TIMER_TYPE_DOMAIN_SUBSCRIPTION | 0x00000002)
#define DOMAIN_SUBSCRIPTION_REGISTERED_INVOKE	(TIMER_TYPE_DOMAIN | TIMER_TYPE_DOMAIN_SUBSCRIPTION | 0x00000003)

DZ1_CPPLINK Dz1Error ItsIso14827Timer_reg(void *timer, ItsIso14827Timer **tmr, u64_t duration, Dz1TaskTimeoutProcFunc timeout);

DZ1_CPPLINK Dz1Error ItsIso14827DomainTimer_reg(void *timer, ItsIso14827DomainKey *key,
												Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id,
												u64_t duration, Dz1TaskTimeoutProcFunc timeout);

DZ1_CPPLINK Dz1Error ItsIso14827DomainTimer_reg2(void *timer,
												 ItsIso14827DomainType type, Dz1Asn1UTF8Str *domain,
												 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id,
												 u64_t duration, Dz1TaskTimeoutProcFunc timeout);

DZ1_CPPLINK Dz1Error ItsIso14827DomainTimer_reg3(void *timer, ItsIso14827Domain *domain, 
												 Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id,
												 u64_t duration, Dz1TaskTimeoutProcFunc timeout);

DZ1_CPPLINK void ItsIso14827DomainTimer_dereg(void *timer, ItsIso14827DomainType type, Dz1Asn1UTF8Str *domainName,
											  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id);

DZ1_CPPLINK Dz1Error ItsIso14827SessionTimer_reg(void *timer, ItsIso14827SessionKey *key, u32_t id,
												u64_t duration, Dz1TaskTimeoutProcFunc timeout);

DZ1_CPPLINK void ItsIso14827SessionTimer_dereg(void *timer, ItsIso14827SessionKey *key, u32_t id);
#endif