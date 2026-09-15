#ifndef ITS_ISO_SERVER_SOCKET_ACCEPTOR_H_LOCAL
#define ITS_ISO_SERVER_SOCKET_ACCEPTOR_H_LOCAL

#include <dz1_asn1.h>

DZ1_CPPLINK u32_t ItsIosSocketAcceptor_start(u32_t dstQueueID, Dz1SockAddr *addr,
											 Dz1Asn1Codec initialCodec,
											 ItsIso14827CRCCheck CRCCheck,
											 Dz1Error *err);
DZ1_CPPLINK void ItsIosSocketAcceptor_stop(u32_t thID);

#endif