#ifndef DZ1_SOCKET_CALLBACK_H
#define DZ1_SOCKET_CALLBACK_H

#include <dz1_socket.h>
#include <dz1_sock_addr.h>

#if 0
// 한바이트라도 받으면 호출된다.
typedef void (*Dz1SocketCallbackRx)(void *cb_param, Dz1SockAddr *peer, Dz1SockAddr *local, u8_t *data, size_t size, Dz1Error *errp);

// 이전에 전송 요청한 Byte가 모두 전송되면 호출된다.
typedef void (*Dz1SocketCallbackTx)(void *cb_param, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *errp);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	Dz1SocketCallbackSkel_init(void);
DZ1_CPPLINK DZ1_DLLPORT void		Dz1SocketCallbackSkel_clean(void);
static __inline__ void				Dz1SocketCallbackSkel_initCancel(void *ptr)
{
	Dz1SocketCallbackSkel_clean();
}

/******************************************************************************
* Callback mode
*******************************************************************************
* wait *
    sock->wait은 항상 -1을 리턴한다.
    Callback mode로 전환되면 wait은 사용할 수 없다.

* send *
    sock->send는 전송 요청 큐에 데이터를 걸고 리턴되며,
    항상 인수로 넣어준 size가 리턴된다.

    이는 전송이 성공적으로 스케쥴링 되었다는것을 의미하며,
    데이터가 상대방으로 전송된것은 아니다.
    sock->send를 호출할 당시에 지정한 size만큼 전송이 완료
    된 시점에 Dz1SocketCallbackTx가 호출된다.

* recv *
    sock->recv는 항상 -1을 리턴한다.
    Callback mode로 전환되면 recv는 사용할 수 없다.
******************************************************************************/
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1TcpClientSocket_modeCallback(Dz1TcpClientSocket *sock,
																 Dz1SockAddr *peer, Dz1SockAddr *local,
																 size_t rx_buf_size,
																 Dz1SocketCallbackRx rx, void *rx_arg, Dz1DelFunc rx_arg_del,
																 Dz1SocketCallbackTx tx, void *tx_arg, Dz1DelFunc tx_arg_del);
#endif	// #if 0

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SocketCallback2_init(void);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1SocketCallback2_cleanup(void);
static __inline__ void			 Dz1SocketCallback2_initCancel(void *ptr)
{
	Dz1SocketCallback2_cleanup();
}

// Dz1Error *status는 별다른 Error가 없으면 NULL이다.
typedef void (*Dz1SocketCallback2Rcvd)(void *user_ptr, Dz1SockAddr *peer, Dz1SockAddr *local, u8_t *data, size_t size, Dz1Error *status);
typedef void (*Dz1SocketCallback2Sent)(void *user_ptr, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *status);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SocketCallback2_associate(Dz1TcpClientSocket *sock, Dz1SockAddr *peer, Dz1SockAddr *local,
															  size_t rx_buf_size,
															  Dz1SocketCallback2Rcvd rx_cb,
															  Dz1SocketCallback2Sent tx_cb,
															  void **user_ptr, Dz1DelFunc user_ptr_del);

#endif	// #ifndef DZ1_SOCKET_CALLBACK_H
