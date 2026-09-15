#ifndef _DZ1_TDC_ITS_ISO14827_SOCKET_ACCEPTOR_DEF_H_
#define _DZ1_TDC_ITS_ISO14827_SOCKET_ACCEPTOR_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIsoAcceptor
typedef struct ItsIsoAcceptor
{
	u32_t					dstQueueID;
	Dz1Asn1Codec			initialCodec;
	ItsIso14827CRCCheck		CRCCheck;
} ItsIsoAcceptor;

DZ1_CPPLINK DZ1_DLLPORT ItsIsoAcceptor *ItsIsoAcceptor_new(u32_t dstQueueID, 
														   Dz1Asn1Codec initialCodec, 
														   ItsIso14827CRCCheck CRCCheck, Dz1Error *err);
static __inline__ ItsIsoAcceptor *ItsIsoAcceptor_gen(Dz1Error *err) { return ItsIsoAcceptor_new(0, Dz1Asn1Codec_max, ItsIso14827CRCCheck_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIsoAcceptor_purge(ItsIsoAcceptor *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIsoAcceptor_del(ItsIsoAcceptor *p);
static __inline__ void ItsIsoAcceptor_delAndSetNull(void *ptr)
{
	ItsIsoAcceptor **p = (ItsIsoAcceptor **)ptr;
	if (p) { ItsIsoAcceptor_del(*p); *p = NULL; }
}
// ItsIsoAcceptor
////////////////////////////////////////////////////////////////////////////////

#endif
