#ifndef DZ1_SOCKET_FIFO_H
#define DZ1_SOCKET_FIFO_H

#include <dz1_error.h>
#include <dz1_bin.h>

#include <dz1_socket.h>
#include <dz1_codec.h>

///////////////////////////////////////////////////////////////////////////////
// Dz1 Socket Type 1 : Binary Mode
typedef void Dz1SocketFifo;

DZ1_CPPLINK DZ1_DLLPORT Dz1SocketFifo	*Dz1SocketFifo_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketFifo_del(Dz1SocketFifo *p);
static __inline__ void					 Dz1SocketFifo_delAndSetNull(void *ptr)
{
	Dz1SocketFifo **p = (Dz1SocketFifo **)ptr;
	Dz1SocketFifo_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketFifoA_dump(Dz1SocketFifo *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketFifoW_dump(Dz1SocketFifo *p, int tab);
#ifdef UNICODE
#define									 Dz1SocketFifo_dump		Dz1SocketFifoW_dump
#else // UNICODE
#define									 Dz1SocketFifo_dump		Dz1SocketFifoA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define									 Dz1SocketFifo_dump		Dz1SocketFifoA_dump
#endif // UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketFifo_push(Dz1SocketFifo *fifo, Dz1Binary **packet);					// push (*packet) and set NULL
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketFifo_copyAndPush(Dz1SocketFifo *fifo, Dz1Binary *packet);				// copy packet and push
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketFifo_copyAndPushData(Dz1SocketFifo *fifo, u8_t *data, size_t size);	// create Dz1Binary *packet and push
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary		*Dz1SocketFifo_pop(Dz1SocketFifo *fifo, Dz1Error *err);							// Pop Dz1Binary *packet
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary		*Dz1SocketFifo_peek(Dz1SocketFifo *fifo, Dz1Error *err);						// return Dz1Binary pointer without pop
DZ1_CPPLINK DZ1_DLLPORT size_t			 Dz1SocketFifo_count(Dz1SocketFifo *fifo);
// Dz1 Socket Type 1 : Binary Mode
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1 Socket Type 2 : CODEC Mode
typedef void Dz1SocketFifo2;

DZ1_CPPLINK DZ1_DLLPORT Dz1SocketFifo2 *Dz1SocketFifo2_new(Dz1EncodeFunc enc, void *enc_param, Dz1DelFunc del, Dz1DumpFunc dump, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void			Dz1SocketFifo2_del(Dz1SocketFifo2 *p);
static __inline__ void					Dz1SocketFifo2_delAndSetNull(void *ptr)
{
	Dz1SocketFifo2 **p = (Dz1SocketFifo2 **)ptr;
	Dz1SocketFifo2_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void			Dz1SocketFifo2A_dump(Dz1SocketFifo2 *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void			Dz1SocketFifo2W_dump(Dz1SocketFifo2 *p, int tab);
#ifdef UNICODE
#define									Dz1SocketFifo2_dump			Dz1SocketFifo2W_dump
#else // UNICODE
#define									Dz1SocketFifo2_dump			Dz1SocketFifo2A_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define									Dz1SocketFifo2_dump			Dz1SocketFifo2A_dump
#endif // UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT void			*Dz1SocketFifo2_peek(Dz1SocketFifo2 *fifo);
DZ1_CPPLINK DZ1_DLLPORT size_t			 Dz1SocketFifo2_count(Dz1SocketFifo2 *fifo);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketFifo2_setVerbose(Dz1SocketFifo2 *fifo, bool_t verbose);
///////////////////////////////////////
// TCP Client Socket Helper
#define									 Dz1SocketFifo2_sendTCP(fifo, sock, msgpp, to) _Dz1SocketFifo2_sendTCP((fifo), (sock), (msgpp), (to), FALSE)				// msg를 fifo에 넣고, 상황에 따라 전송한다.
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		_Dz1SocketFifo2_sendTCP(Dz1SocketFifo2 *fifo, Dz1TcpClientSocket *sock, void **msg, struct timeval *to, bool_t msg_verbose);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketFifo2_repeatTCP(Dz1SocketFifo2 *fifo, Dz1TcpClientSocket *sock, struct timeval *to);	// head에 있는 stream을 전송한다. stream이 준비되어 있지 않으면 encode callback을 호출하여 생성한다.
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketFifo2_retryTCP(Dz1SocketFifo2 *fifo, Dz1TcpClientSocket *sock, struct timeval *to);	// head에 있는 msg를 encode callback을 호출하여 stream을 만든 다음 전송한다.
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketFifo2_continueTCP(Dz1SocketFifo2 *fifo, Dz1TcpClientSocket *sock, struct timeval *to);// head에 있는 node를 제거하고, retryTCP를 호출한다.
// TCP Client Socket Helper
///////////////////////////////////////
// Dz1 Socket Type 2 : CODEC Mode
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
// Dz1 Socket Type 3 : Dz1Stream Mode
#include <dz1_io_stream.h>
typedef ssize_t (*Dz1SocketFifo3Encoder)(Dz1Stream *dst, void *src, void *param, bool_t verbose, Dz1Error *err);
typedef void Dz1SocketFifo3;
DZ1_CPPLINK DZ1_DLLPORT Dz1SocketFifo3	*Dz1SocketFifo3_new(u32_t alloc_unit_sz, Dz1SocketFifo3Encoder msg_enc, Dz1CloneFunc msg_clone, Dz1DelFunc msg_del, Dz1DumpFunc msg_dump, void *param, Dz1DelFunc param_del, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketFifo3_del(Dz1SocketFifo3 *ptr);
static __inline__ void					 Dz1SocketFifo3_delAndSetNull(void *pptr)
{
	Dz1SocketFifo3 **p = (Dz1SocketFifo3 **)pptr;
	Dz1SocketFifo3_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketFifo3A_dump(Dz1SocketFifo3 *ptr, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketFifo3W_dump(Dz1SocketFifo3 *ptr, int tab);
#ifdef UNICODE
#define									 Dz1SocketFifo3_dump		Dz1SocketFifo3W_dump
#else // UNICODE
#define									 Dz1SocketFifo3_dump		Dz1SocketFifo3A_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define									 Dz1SocketFifo3_dump		Dz1SocketFifo3A_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketFifo3_sendTCP(Dz1SocketFifo3 *ptr, Dz1TcpClientSocket *sock, void *msg, struct timeval *to, bool_t msg_verbose);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketFifo3_sent(Dz1SocketFifo3 *ptr, Dz1TcpClientSocket *sock, struct timeval *to);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketFifo3_setVerbose(Dz1SocketFifo3 *fifo, bool_t verbose);
// Dz1 Socket Type 2 : Dz1Stream Mode
///////////////////////////////////////////////////////////////////////////////

#endif
