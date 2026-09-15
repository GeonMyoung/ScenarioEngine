#ifndef DZ1_SOCKET_CALLBACK_SKEL_H_LOCAL
#define DZ1_SOCKET_CALLBACK_SKEL_H_LOCAL

#include <pthread.h>
#include <dz1_socket_callback.h>
#include "dz1_socket.h"

#ifdef UNIX_SYSTEM
typedef struct WSABUF
{
	char *buf;
	size_t len;
} WSABUF;
#endif

// #define DZ1_SOCKET_CALLBACK_DEBUG

#if defined(LINUX)
#define Dz1ScbOSHandleType			int
#elif defined(WIN32)
#define Dz1ScbOSHandleType			OVERLAPPED
#endif
															   
///////////////////////////////////////////////////////////////////////////////
// Callback mode2 
typedef struct Dz1SocketCallback2Buffer
{
	u8_t							*data;
	WSABUF							 io_ptr;
} Dz1SocketCallback2Buffer;

#define Dz1SocketCallback2Buffer_ALLOC			(void *)-1
DZ1_CPPLINK Dz1SocketCallback2Buffer	*Dz1SocketCallback2Buffer_new(u8_t *data, size_t sz, Dz1Error *err);
DZ1_CPPLINK void						 Dz1SocketCallback2Buffer_del(Dz1SocketCallback2Buffer *p);
static __inline__ void					 Dz1SocketCallback2Buffer_delAndSetNull(void *pptr)
{
	Dz1SocketCallback2Buffer **p = (Dz1SocketCallback2Buffer **)pptr;
	Dz1SocketCallback2Buffer_del(*p); *p = NULL;
}

typedef struct Dz1SocketCallback2Spec
{
	Dz1TcpClientSocket				 own_sock;	// RXW vs TXW vs UPPER
	Dz1SockAddr						*peer;
	Dz1SockAddr						*local;

	pthread_mutex_t					 lock;

	int								 ref_cnt;	// RXW vs TXW vs UPPER

	Dz1SocketCallback2Buffer		*tx_buf;	// TXW vs UPPER
	Dz1SocketCallback2Buffer		*rx_buf;	// RXW
#ifdef WIN32
	OVERLAPPED						 tx_ols;	// TXW
	OVERLAPPED						 rx_ols;	// RXW
#endif
	bool_t							 tx_busy;	// TXW vs USER

	SOCKET							 fd;

	Dz1SocketCallback2Sent			 sent_cb;
	Dz1SocketCallback2Rcvd			 rcvd_cb;
	void							*user_ptr;
	Dz1DelFunc						 user_ptr_del;

	void							(*release)(struct Dz1SocketCallback2Spec *self);
} Dz1SocketCallback2Spec;

DZ1_CPPLINK void Dz1SocketCallback2Spec_closeSock(Dz1SocketCallback2Spec *p);	// in critical
// DZ1_CPPLINK void _Dz1SocketCallback2Spec_del(Dz1SocketCallback2Spec *p);		// internal side call
DZ1_CPPLINK void Dz1SocketCallback2Spec_del(Dz1SocketCallback2Spec *p);			// user side call
static __inline__ void Dz1SocketCallback2Spec_delAndSetNull(void *pptr)
{
	Dz1SocketCallback2Spec **p = (Dz1SocketCallback2Spec **)pptr;
	Dz1SocketCallback2Spec_del(*p); *p = NULL;
}


DZ1_CPPLINK bool_t  Dz1SocketCallback2_skel_tx_complete(Dz1SocketCallback2Spec *spec, u32_t size, int err_code);
DZ1_CPPLINK bool_t  Dz1SocketCallback2_skel_rx_complete(Dz1SocketCallback2Spec *spec, u32_t size, int err_code);

DZ1_CPPLINK int		Dz1SocketCallback2_skel_user_wait(struct Dz1TcpClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1SocketCallback2_skel_user_recv(struct Dz1TcpClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1SocketCallback2_skel_user_write(Dz1TcpClientSocket *p, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1SocketCallback2_skel_local_write(Dz1SocketCallback2Spec *spec, u8_t *data, size_t size, bool_t no_lock, Dz1Error *err);

DZ1_CPPLINK Dz1Error Dz1SocketCallback2_sys_init(void);
DZ1_CPPLINK void	 Dz1SocketCallback2_sys_cleanup(void);

DZ1_CPPLINK Dz1Error Dz1SocketCallback2_sys_reg(SOCKET fd, Dz1SocketCallback2Spec *spec);					// unlocked func
DZ1_CPPLINK bool_t	 Dz1SocketCallback2_sys_req_tx(Dz1SocketCallback2Spec *spec, Dz1Error *err);			// unlocked func
DZ1_CPPLINK bool_t	 Dz1SocketCallback2_sys_req_rx(Dz1SocketCallback2Spec *spec, Dz1Error *err);			// unlocked func

// 할당되어있는 spec에 값만 설정한다.
DZ1_CPPLINK Dz1Error				 Dz1SocketCallback2Spec_skel_init_data(Dz1SocketCallback2Spec *spec,
																	   Dz1TcpClientSocket *sock, SOCKET fd,
																	   Dz1SockAddr *peer,
																	   Dz1SockAddr *local,
																	   u32_t rx_buf_size,
																	   Dz1SocketCallback2Rcvd rx_cb,
																	   Dz1SocketCallback2Sent tx_cb,
																	   void **user_ptr, Dz1DelFunc user_ptr_del);

// 할당되어있는 spec에 값을 설정하고, sub-system에 attach한다.
DZ1_CPPLINK Dz1Error				 Dz1SocketCallback2Spec_skel_init(Dz1SocketCallback2Spec *spec,
																	  Dz1TcpClientSocket *sock, SOCKET fd,
																	  Dz1SockAddr *peer,
																	  Dz1SockAddr *local,
																	  u32_t rx_buf_size,
																	  Dz1SocketCallback2Rcvd rx_cb,
																	  Dz1SocketCallback2Sent tx_cb,
																	  void **user_ptr, Dz1DelFunc user_ptr_del,
																	  bool_t no_lock);

// 새로운 spec을 할당하고 값을 설정, sub-system에 attach한다.
DZ1_CPPLINK Dz1SocketCallback2Spec	*Dz1SocketCallback2Spec_skel_gen(Dz1TcpClientSocket *sock, 
																	 Dz1SockAddr *peer,
																	 Dz1SockAddr *local,
																	 size_t rx_buf_size,
																	 Dz1SocketCallback2Rcvd rx_cb,
																	 Dz1SocketCallback2Sent tx_cb,
																	 void **user_ptr, Dz1DelFunc user_ptr_del,
																	 bool_t no_lock,
																	 Dz1Error *err);

static __inline__ void _associated_socket_rollback(void *ptr)
{
	Dz1TcpClientSocket *sock = (Dz1TcpClientSocket *)ptr;
	Dz1SocketCallback2Spec *spec = (Dz1SocketCallback2Spec *)sock->specific;

	sock->wait			= spec->own_sock.wait;			spec->own_sock.wait			= NULL;
	sock->recv			= spec->own_sock.recv;			spec->own_sock.recv			= NULL;
	sock->send			= spec->own_sock.send;			spec->own_sock.send			= NULL;
	sock->getOSHandle	= spec->own_sock.getOSHandle;	spec->own_sock.getOSHandle	= NULL;

	sock->specific		= spec->own_sock.specific;		spec->own_sock.specific		= NULL;
	sock->specific_del	= spec->own_sock.specific_del;	spec->own_sock.specific_del	= NULL;
}

// Callback mode2 
///////////////////////////////////////////////////////////////////////////////

#endif
