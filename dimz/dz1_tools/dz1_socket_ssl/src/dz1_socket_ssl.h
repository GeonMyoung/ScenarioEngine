#ifndef DZ1_SOCKET_SSL_LOCAL
#define DZ1_SOCKET_SSL_LOCAL

#include <dz1_socket_ssl.h>

#include "dz1_socket.h"
#include "../src/socket/dz1_socket_callback_skel.h"
// #include <dz1_socket_callback_ssl.h>

///////////////////////////////////////////////////////////////////////
// Dz1SocketCallback2SpecSSL과 Dz1SocketCallback2Spec은 위치상 동일하다
///////////////////////////////////////////////////////////////////////

typedef struct Dz1SocketCallback2SpecSSL
{
	Dz1SocketCallback2Spec			 cb_spec;

	SSL_CTX							*ctx;
	SSL								*ssl;
	BIO								*egress;		// is ref
	BIO								*ingress;		// is ref

	Dz1SocketCallback2Buffer		*tx_user_buf;	// USER vs SSL

	Dz1SocketCallback2Sent			 sent_cb;
	Dz1SocketCallback2Rcvd			 rcvd_cb;
	void							*user_ptr;
	Dz1DelFunc						 user_ptr_del;
} Dz1SocketCallback2SpecSSL;

#endif
