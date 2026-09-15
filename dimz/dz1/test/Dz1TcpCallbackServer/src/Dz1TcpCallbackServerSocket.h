#ifndef DZ1_TCP_CALLBACK_SERVER_ACCEPTOR_H_LOCAL
#define DZ1_TCP_CALLBACK_SERVER_ACCEPTOR_H_LOCAL

#include <dz1_error.h>

DZ1_CPPLINK u32_t Dz1TcpCallbackServerAcceptor_start(u32_t parent_queue_id, u16_t port, Dz1Error *err);
DZ1_CPPLINK void Dz1TcpCallbackServerAcceptor_stop(u32_t id);
static __inline__ void Dz1TcpCallbackServerAcceptor_stopAndSetNull(void *ptr)
{
	u32_t *id = (u32_t *)ptr;
	Dz1TcpCallbackServerAcceptor_stop(*id); (*id) = -1;
}

DZ1_CPPLINK Dz1Error Dz1TcpCallbackServerSocketMsg_init(void *task);

#endif
