#ifndef _DZ1_TDC_ISO14827DZ1_HDR_FORM_H_
#define _DZ1_TDC_ISO14827DZ1_HDR_FORM_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Iso14827dz1.h"
#include "dz1_asn1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827MsgDecodeFunc
typedef ssize_t (*Iso14827MsgDecodeFunc)(
					void **dst, 
					Dz1Asn1Any *src, 
					Dz1Asn1Codec codec, 
					Dz1Error *err);
// Iso14827MsgDecodeFunc
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827HdrForm
typedef struct Iso14827HdrForm
{
	bool_t		originDomainPresent;
	bool_t		originAddrPresent;
	bool_t		senderDomainPresent;
	bool_t		senderAddrPresent;
	bool_t		destDomainPresent;
	bool_t		destAddrPresent;
	str_t		currency;
	s32_t		factor;
	u8_t		timeFlag;
} Iso14827HdrForm;

DZ1_CPPLINK DZ1_DLLPORT Iso14827HdrForm *Iso14827HdrForm_new(bool_t originDomainPresent, 
															 bool_t originAddrPresent, 
															 bool_t senderDomainPresent, 
															 bool_t senderAddrPresent, 
															 bool_t destDomainPresent, 
															 bool_t destAddrPresent, 
															 str_t currency_ref, 
															 s32_t factor, 
															 u8_t timeFlag, Dz1Error *err);
static __inline__ Iso14827HdrForm *Iso14827HdrForm_gen(Dz1Error *err) { return Iso14827HdrForm_new(0, 0, 0, 0, 0, 0, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827HdrForm_purge(Iso14827HdrForm *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827HdrForm_del(Iso14827HdrForm *p);
static __inline__ void Iso14827HdrForm_delAndSetNull(void *ptr)
{
	Iso14827HdrForm **p = (Iso14827HdrForm **)ptr;
	if (p) { Iso14827HdrForm_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827HdrForm_dump(Iso14827HdrForm *p, int tab);
// Iso14827HdrForm
////////////////////////////////////////////////////////////////////////////////

#endif
