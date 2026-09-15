#ifndef _DZ1_TDC_ITS_ISO14827_SOCKET_RECEIVER_MSGS_H_
#define _DZ1_TDC_ITS_ISO14827_SOCKET_RECEIVER_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIsoSocketReceiverReceived
typedef struct ItsIsoSocketReceiverReceived
{
	ItsIso14827SessionKey		*key;
	Dz1Binary					*packet;
	time_t						 stamp;
} ItsIsoSocketReceiverReceived;

DZ1_CPPLINK DZ1_DLLPORT ItsIsoSocketReceiverReceived *ItsIsoSocketReceiverReceived_new(ItsIso14827SessionKey *key, 
																					   Dz1Binary *packet, 
																					   time_t stamp, Dz1Error *err);
static __inline__ ItsIsoSocketReceiverReceived *ItsIsoSocketReceiverReceived_gen(Dz1Error *err) { return ItsIsoSocketReceiverReceived_new(NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIsoSocketReceiverReceived_purge(ItsIsoSocketReceiverReceived *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIsoSocketReceiverReceived_del(ItsIsoSocketReceiverReceived *p);
static __inline__ void ItsIsoSocketReceiverReceived_delAndSetNull(void *ptr)
{
	ItsIsoSocketReceiverReceived **p = (ItsIsoSocketReceiverReceived **)ptr;
	if (p) { ItsIsoSocketReceiverReceived_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIsoSocketReceiverReceived_dump(ItsIsoSocketReceiverReceived *p, int tab);
// ItsIsoSocketReceiverReceived
////////////////////////////////////////////////////////////////////////////////

#endif
