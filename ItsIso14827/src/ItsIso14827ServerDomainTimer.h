#ifndef ITS_ISO_14827_SERVER_DOMAIN_TIMER_H_LOCAL
#define ITS_ISO_14827_SERVER_DOMAIN_TIMER_H_LOCAL

#include <dz1_asn1.h>
#include <dz1_task_timer.h>
#include "ItsIso14827TimerUtil.h"

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainTimer_reg(void *timer, Dz1Asn1UTF8Str *domain,
													  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id,
													  u64_t duration, Dz1TaskTimeoutProcFunc timeout);

DZ1_CPPLINK void ItsIso14827ServerDomainTimer_dereg(void *timer, Dz1Asn1UTF8Str *domain,
													Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t id);

DZ1_CPPLINK Dz1Error ItsIso14827ServerDomainSubscriptionTimer_reg(void *timer, Dz1Asn1UTF8Str *domain,
																  Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
																  u32_t subID, u32_t id,
																  u64_t duration, Dz1TaskTimeoutProcFunc timeout);

DZ1_CPPLINK void ItsIso14827ServerDomainSubscriptionTimer_dereg(void *timer, Dz1Asn1UTF8Str *domain,
																Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user,
																u32_t subID, u32_t id);

#endif