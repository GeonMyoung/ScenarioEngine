#ifndef _DZ1_TDC_ISO14827_TEST_HELPER_ARG_H_
#define _DZ1_TDC_ISO14827_TEST_HELPER_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827TestHelperDef.h"
#include "dz1_asn1_support.h"
#include "Iso14827TestMsgUtil.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperArg
typedef struct Iso14827TestHelperArg
{
	void							*tMain;
	void							*t14827;
	Dz1Str							 testScenario;
	Iso14827TestMsgStructAPI		*msg_api;
	u8_t							 codec_bits;
	u16_t							 hb_dur_s;
	u8_t							 rsp_time_s;
	Dz1Asn1Codec					 initial_codec;
	Iso14827TestHelperException		 exceptionProc;
	void							*exceptionArg;
} Iso14827TestHelperArg;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperArg *Iso14827TestHelperArg_new(void *tMain, 
																		 void *t14827, 
																		 Dz1Str testScenario, 
																		 Iso14827TestMsgStructAPI *msg_api_ref, 
																		 u8_t codec_bits, 
																		 u16_t hb_dur_s, 
																		 u8_t rsp_time_s, 
																		 Dz1Asn1Codec initial_codec, 
																		 Iso14827TestHelperException exceptionProc, 
																		 void *exceptionArg, Dz1Error *err);
static __inline__ Iso14827TestHelperArg *Iso14827TestHelperArg_gen(Dz1Error *err) { return Iso14827TestHelperArg_new(NULL, NULL, NULL, NULL, 0, 0, 0, Dz1Asn1Codec_max, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperArg_purge(Iso14827TestHelperArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperArg_del(Iso14827TestHelperArg *p);
static __inline__ void Iso14827TestHelperArg_delAndSetNull(void *ptr)
{
	Iso14827TestHelperArg **p = (Iso14827TestHelperArg **)ptr;
	if (p) { Iso14827TestHelperArg_del(*p); *p = NULL; }
}
// Iso14827TestHelperArg
////////////////////////////////////////////////////////////////////////////////

#endif
