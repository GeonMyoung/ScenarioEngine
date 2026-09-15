#ifndef _DZ1_TDC_ITS_ISO14827_SOCKET_RECEIVER_DEF_H_
#define _DZ1_TDC_ITS_ISO14827_SOCKET_RECEIVER_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SocketReceiverArg
typedef struct ItsIso14827SocketReceiverArg
{
	u32_t		parentQueueID;
	u32_t		sid;
} ItsIso14827SocketReceiverArg;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827SocketReceiverArg *ItsIso14827SocketReceiverArg_new(u32_t parentQueueID, 
																					   u32_t sid, Dz1Error *err);
static __inline__ ItsIso14827SocketReceiverArg *ItsIso14827SocketReceiverArg_gen(Dz1Error *err) { return ItsIso14827SocketReceiverArg_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SocketReceiverArg_purge(ItsIso14827SocketReceiverArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SocketReceiverArg_del(ItsIso14827SocketReceiverArg *p);
static __inline__ void ItsIso14827SocketReceiverArg_delAndSetNull(void *ptr)
{
	ItsIso14827SocketReceiverArg **p = (ItsIso14827SocketReceiverArg **)ptr;
	if (p) { ItsIso14827SocketReceiverArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827SocketReceiverArg_dump(ItsIso14827SocketReceiverArg *p, int tab);
// ItsIso14827SocketReceiverArg
////////////////////////////////////////////////////////////////////////////////

#endif
