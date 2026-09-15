#ifndef _DZ1_TDC_ITS_ISO14827_SOCKET_ACCEPTOR_MSGS_H_
#define _DZ1_TDC_ITS_ISO14827_SOCKET_ACCEPTOR_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIsoAcceptorConnected
typedef struct ItsIsoAcceptorConnected
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1Asn1Codec			 initialCodec;
	ItsIso14827CRCCheck		 CRCCheck;
} ItsIsoAcceptorConnected;

DZ1_CPPLINK DZ1_DLLPORT ItsIsoAcceptorConnected *ItsIsoAcceptorConnected_new(Dz1SockAddr *peer, 
																			 Dz1SockAddr *local, 
																			 Dz1TcpClientSocket *sock, 
																			 Dz1Asn1Codec initialCodec, 
																			 ItsIso14827CRCCheck CRCCheck, Dz1Error *err);
static __inline__ ItsIsoAcceptorConnected *ItsIsoAcceptorConnected_gen(Dz1Error *err) { return ItsIsoAcceptorConnected_new(NULL, NULL, NULL, Dz1Asn1Codec_max, ItsIso14827CRCCheck_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIsoAcceptorConnected_purge(ItsIsoAcceptorConnected *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIsoAcceptorConnected_del(ItsIsoAcceptorConnected *p);
static __inline__ void ItsIsoAcceptorConnected_delAndSetNull(void *ptr)
{
	ItsIsoAcceptorConnected **p = (ItsIsoAcceptorConnected **)ptr;
	if (p) { ItsIsoAcceptorConnected_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIsoAcceptorConnected_dump(ItsIsoAcceptorConnected *p, int tab);
// ItsIsoAcceptorConnected
////////////////////////////////////////////////////////////////////////////////

#endif
