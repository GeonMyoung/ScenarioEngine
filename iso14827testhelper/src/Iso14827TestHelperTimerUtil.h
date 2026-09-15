#ifndef ISO14827_TEST_HELPER_TIMER_UTIL_H_LOCAL
#define ISO14827_TEST_HELPER_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "Iso14827TestHelperTimer.h"

#define TIMER_sec_to_us(sec)		((u64_t)(sec) * 1000000)

#define ISO14827_TEST_HELPER_TIMER_SERVER1				0x00000001
#define ISO14827_TEST_HELPER_TIMER_SERVER2				0x00000002
#define ISO14827_TEST_HELPER_TIMER_DUO_SERVER			0x00000003
#define ISO14827_TEST_HELPER_TIMER_DUO_CLIENT			0x00000004
#define ISO14827_TEST_HELPER_TIMER_PUB_ED				0x00000005

DZ1_CPPLINK Dz1Error Iso14827TestHelperTimer_set(void *timer, Iso14827TestHelperTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error Iso14827TestHelperTimer_update(void *timer, Iso14827TestHelperTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void Iso14827TestHelperTimer_clr(void *timer, Iso14827TestHelperTimer *key);

DZ1_CPPLINK bool_t Iso14827TestHelperTimer_setGeneralTimer(void* timer, u32_t id, u64_t dur_us, Dz1Error* err);
DZ1_CPPLINK void   Iso14827TestHelperTimer_clrGeneralTimer(void* timer, u32_t id);


#define CLIENT_TIMER_ID_DISCONNECT_WAIT				0x00000001
DZ1_CPPLINK bool_t	 Iso14827TestHelperTimer_setClientTimer(void* timer, Dz1Asn1UTF8Str* my_domain, Dz1Asn1UTF8Str* peer_domain, Dz1Asn1OctetStr* user, u32_t id, u64_t dur_us, Dz1Error* err);
DZ1_CPPLINK void	 Iso14827TestHelperTimer_clrClientTimer(void* timer, Dz1Asn1UTF8Str* my_domain, Dz1Asn1UTF8Str* peer_domain, Dz1Asn1OctetStr* user, u32_t id);

#endif	// ISO14827_TEST_HELPER_TIMER_UTIL_H_LOCAL
