#include <dz1_thread.h>
#include <dz1_thread_stdio.h>
#include <dz1_bin.h>
#include "../kernel/dz1_thread_stdio.h"
#include "dz1_socket_callback_skel.h"

#if 0
int Dz1SocketCallbackSkel_wait(struct Dz1TcpClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ERR_SET_OUT(errp, EINVAL);
	return -1;
}

ssize_t Dz1SocketCallbackSkel_recv(struct Dz1TcpClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ERR_SET_OUT(errp, EINVAL);
	return -1;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Dz1SocketCallback2Buffer
static Dz1Error _buf_data_init(Dz1SocketCallback2Buffer *dst, u8_t *src, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (src == Dz1SocketCallback2Buffer_ALLOC)
	{
		if ((dst->data = (u8_t *)Dz1Malloc(sz, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((dst->data = (u8_t *)Dz1Memory_clone(src, sz, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

Dz1SocketCallback2Buffer *Dz1SocketCallback2Buffer_new(u8_t *data, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SocketCallback2Buffer *ret = NULL;
	if (data == NULL || sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1SocketCallback2Buffer *)Dz1Calloc(sizeof(Dz1SocketCallback2Buffer), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SocketCallback2Buffer_delAndSetNull, (void *)&ret);

		if ((*errp = _buf_data_init(ret, data, sz)).code) ERR_OUT(errp);
		else
		{
			ret->io_ptr.buf = (char *)ret->data;
			ret->io_ptr.len = (u32_t)sz;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SocketCallback2Buffer_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SocketCallback2Buffer_del(Dz1SocketCallback2Buffer *p)
{
	if (p == NULL) return;
	
	if (p->data != NULL)
		Dz1Free(p->data);
	p->data = NULL;

	Dz1Free(p);
}
// Dz1SocketCallback2Buffer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SocketCallback2Spec
void Dz1SocketCallback2Spec_closeSock(Dz1SocketCallback2Spec *p)
{
	if (p == NULL) return;
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### Dz1SocketCallback2Spec_closeSock() : Called (%p, %p)\n", p->own_sock.specific, p->own_sock.specific_del);
#endif
	if (p->own_sock.specific != NULL && p->own_sock.specific_del != NULL)
	{
		p->own_sock.specific_del(p->own_sock.specific);
	}
	p->own_sock.specific = NULL;
	p->own_sock.specific_del = NULL;

	p->own_sock.wait = NULL;
	p->own_sock.recv = NULL;
	p->own_sock.send = NULL;
	p->own_sock.getOSHandle = NULL;
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### Dz1SocketCallback2Spec_closeSock() : return\n");
#endif
}

static void _Dz1SocketCallback2Spec_release(Dz1SocketCallback2Spec *p)
{	// called from user or worker
	if (p == NULL) return;
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### _Dz1SocketCallback2Spec_del() : Called\n");
#endif
	Dz1Thread_eprintf("### _Dz1SocketCallback2Spec_del() : Called\n");

	Dz1SocketCallback2Spec_closeSock(p);

	Dz1SockAddr_delAndSetNull(&p->peer);
	Dz1SockAddr_delAndSetNull(&p->local);

	Dz1SocketCallback2Buffer_delAndSetNull(&p->tx_buf);
	Dz1SocketCallback2Buffer_delAndSetNull(&p->rx_buf);

	p->fd = -1;

	if (p->user_ptr != NULL && p->user_ptr_del != NULL) p->user_ptr_del(p->user_ptr);
	p->user_ptr = NULL;
	p->user_ptr_del = NULL;

	pthread_mutex_destroy(&p->lock);

	Dz1Free(p);

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### _Dz1SocketCallback2Spec_del() : return\n");
#endif
}

void Dz1SocketCallback2Spec_del(Dz1SocketCallback2Spec *p)
{	// user side
	int ref_cnt = -1;
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	int temp;
#endif
	if (p == NULL) return;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### Dz1SocketCallback2Spec_del() : Called\n");
#endif

	pthread_mutex_lock(&p->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

	// lock에 상관 없이 native socket의 resource를 삭제한다. -> 대기탄 아이들이 error를 post한다.
	Dz1SocketCallback2Spec_closeSock(p);	// 왜 주석해놨지?

	// reference 를 감소 시킨다
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	temp = p->ref_cnt;
#endif
	if (p->ref_cnt > 0) p->ref_cnt--;
	ref_cnt = p->ref_cnt;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("Dz1SocketCallback2Spec_del() ref_cnr = %d -> %d\n", temp, p->ref_cnt);
#endif
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

	// reference count가 0이면 자원을 해제한다.
	if (ref_cnt == 0) _Dz1SocketCallback2Spec_release(p);
	else
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "Dz1SocketCallback2Spec_del() : not deleted : ref_cnt = %d\n", ref_cnt);
	}
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### Dz1SocketCallback2Spec_del() : return\n");
#endif
}

///////////////////////////////////////////////////////////////////////////////
// TX Complete
bool_t Dz1SocketCallback2_skel_tx_complete(Dz1SocketCallback2Spec *spec, u32_t size, int err_code)
{
	int ref_cnt = -1;
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	int temp;
#endif
	DZ1_ERROR_SAFE_VAR(errp, err);

	pthread_mutex_lock(&spec->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
	// Start Critical

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	temp = spec->ref_cnt;
#endif

	spec->tx_busy = FALSE;

	if (err_code == 0)
	{	// 에러 없음
		if (size > 0)
		{	// 잘 보냄
			Dz1SocketCallback2Buffer *buf = NULL;

			// move tx pointer
			buf = spec->tx_buf;
			buf->io_ptr.buf += size;
			buf->io_ptr.len -= size;

			if (buf->io_ptr.len > 0) 
			{	// data to send is remain in buffer
				if (Dz1SocketCallback2_sys_req_tx(spec, errp) == FALSE)	// TX reserve
				{	// reserve fail -> close and post to user
					ERR_OUT(errp);
					// close socket
					Dz1SocketCallback2Spec_closeSock(spec);

					pthread_mutex_unlock(&spec->lock);
					pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
					// out of Critical

					spec->sent_cb(spec->user_ptr, spec->peer, spec->local, errp);

					// enter of Critical
					pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
				}
				else spec->tx_busy = TRUE;
			}
			else
			{	// transmit is done
				Dz1SocketCallback2Buffer_delAndSetNull(&spec->tx_buf);		// delete tx buffer

				pthread_mutex_unlock(&spec->lock);
				pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
				// out of Critical

				spec->sent_cb(spec->user_ptr, spec->peer, spec->local, NULL);

				// enter of Critical
				pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
			}
		}
	}
	else
	{	// error detected
		ERR_SET_OUT(errp, err_code);
		// close socket
//		Dz1SocketCallback2Spec_closeSock(spec);

		pthread_mutex_unlock(&spec->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
		// out of Critical

		spec->sent_cb(spec->user_ptr, spec->peer, spec->local, errp);

		// enter of Critical
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
	}

	// decrease reference
	if (spec->ref_cnt > 0) spec->ref_cnt--;
	else
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "!!! Dz1SocketCallback2_skel_tx_complete() : CallbackSocket Reference invalid\n");
	}
	ref_cnt = spec->ref_cnt;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("Dz1SocketCallback2_skel_tx_complete() : ref = %d -> %d\n", temp, ref_cnt);
#endif
	// End Critical
	pthread_cleanup_pop(1); // (Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

	if (ref_cnt == 0) return FALSE; else return TRUE;
}
// TX Complete
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// RX Complete
bool_t Dz1SocketCallback2_skel_rx_complete(Dz1SocketCallback2Spec *spec, u32_t size, int err_code)
{
	int leave_ref_cnt = -1;
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	int entry_ref_cnt = -1;
#endif
	DZ1_ERROR_SAFE_VAR(errp, err);

	pthread_mutex_lock(&spec->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	entry_ref_cnt = spec->ref_cnt;
#endif
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

	if (err_code == 0)
	{	// no error
		if (size > 0)
		{	// data received
			ssize_t sz = (ssize_t)size;
			Dz1SocketCallback2Buffer *buf = spec->rx_buf;

			// Reset RX Buffer
			size_t origin_size = (size_t)(buf->io_ptr.buf - (char *)buf->data) + buf->io_ptr.len;
			buf->io_ptr.buf = (char *)buf->data;
			buf->io_ptr.len = (u32_t)origin_size;

			// notify to caller
			spec->rcvd_cb(spec->user_ptr, spec->peer, spec->local, buf->data, sz, NULL);

			// re-request RX
			if (Dz1SocketCallback2_sys_req_rx(spec, errp) == FALSE)
			{	// failed
				pthread_mutex_lock(&spec->lock);
				pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
				// close socket
				Dz1SocketCallback2Spec_closeSock(spec);

				pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
				// notify
				ERR_OUT(errp);
				spec->rcvd_cb(spec->user_ptr, spec->peer, spec->local, NULL, 0, errp);
			}
		}
		else
		{	// nothing received
			pthread_mutex_lock(&spec->lock);
			pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
			// close socket
			Dz1SocketCallback2Spec_closeSock(spec);

			pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
			// notify
			Dz1Error_set(errp, EPIPE);
			spec->rcvd_cb(spec->user_ptr, spec->peer, spec->local, NULL, 0, errp);
		}
	}
	else
	{	// error detect
// 		pthread_mutex_lock(&spec->lock);
// 		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
// 		// close socket
// 		Dz1SocketCallback2Spec_closeSock(spec);
// 
// 		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
		// notify
		ERR_SET_OUT(errp, err_code);
		spec->rcvd_cb(spec->user_ptr, spec->peer, spec->local, NULL, 0, errp);
	}

	pthread_mutex_lock(&spec->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
	// Enter Critical 

	if (spec->ref_cnt > 0) spec->ref_cnt--;
	leave_ref_cnt = spec->ref_cnt;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("Dz1SocketCallback2_skel_rx_complete() : ref = %d -> %d\n", entry_ref_cnt, leave_ref_cnt);
#endif
	// Exit Critical
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

	if (leave_ref_cnt == 0) return FALSE; else return TRUE;
}
// RX Complete
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// User Call
int Dz1SocketCallback2_skel_user_wait(struct Dz1TcpClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ERR_SET_OUT(errp, EINVAL);
	return -1;
}

ssize_t Dz1SocketCallback2_skel_user_recv(struct Dz1TcpClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ERR_SET_OUT(errp, EINVAL);
	return -1;
}
// User Call
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TX Skeleton
static ssize_t _skel_local_write(Dz1SocketCallback2Spec *spec, u8_t *data, size_t size, Dz1Error *errp)
{	// TX Skeleton Code
	ssize_t ret = -1;
	if (spec->tx_buf != NULL) ERR_SET_OUT(errp, EAGAIN);
	else if ((spec->tx_buf = Dz1SocketCallback2Buffer_new(data, size, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SocketCallback2Buffer_delAndSetNull, (void *)&spec->tx_buf);
		if (spec->tx_busy == TRUE)
		{
			ret = (ssize_t)size;
			Dz1Error_set(errp, 0);
		}
		else if (Dz1SocketCallback2_sys_req_tx(spec, errp) == FALSE) ERR_OUT(errp);
		else
		{
			spec->tx_busy = TRUE;
			ret = (ssize_t)size;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SocketCallback2Buffer_delAndSetNull, (void *)&spec->tx_buf);
	}
	return ret;
}

ssize_t Dz1SocketCallback2_skel_local_write(Dz1SocketCallback2Spec *spec, u8_t *data, size_t size, bool_t no_lock, Dz1Error *err)
{	// Internal TX API
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = -1;

	//////////////////////////////////////////
	// Non Critical Section Mode
	if (no_lock == FALSE)
	{
		pthread_mutex_lock(&spec->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

		if ((ret = _skel_local_write(spec, data, size, errp)) < 0) ERR_OUT(errp);
		else if (ret == 0) ERR_SET_OUT(errp, EPIPE);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
	}
	// Non Critical Section Mode
	//////////////////////////////////////////

	//////////////////////////////////////////
	// in Critical Section Mode
	else if ((ret = _skel_local_write(spec, data, size, errp)) < 0) ERR_OUT(errp);
	else if (ret == 0) ERR_SET_OUT(errp, EPIPE);
	else Dz1Error_set(errp, 0);
	// in Critical Section Mode
	//////////////////////////////////////////

	return ret;
}

ssize_t Dz1SocketCallback2_skel_user_write(Dz1TcpClientSocket *p, u8_t *data, size_t size, u32_t flag,
										  struct timeval *to, Dz1Error *err)
{	// User Side Write Skeleton Code
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = -1;
	Dz1SocketCallback2Spec *spec = (Dz1SocketCallback2Spec *)p->specific;

	if ((ret = Dz1SocketCallback2_skel_local_write(spec, data, size, FALSE, errp)) <= 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}
// TX Skeleton
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Initialize Data Only
Dz1Error Dz1SocketCallback2Spec_skel_init_data(Dz1SocketCallback2Spec *spec,
										   Dz1TcpClientSocket *sock, SOCKET fd,
										   Dz1SockAddr *peer,
										   Dz1SockAddr *local,
										   u32_t rx_buf_size,
										   Dz1SocketCallback2Rcvd rx_cb,
										   Dz1SocketCallback2Sent tx_cb,
										   void **user_ptr, Dz1DelFunc user_ptr_del)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((spec->rx_buf = Dz1SocketCallback2Buffer_new(DZ1_BIN_DATA_ALLOC, rx_buf_size, errp)) == NULL) ERR_OUT(errp);
	else if ((spec->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
	else if ((spec->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
	else
	{
		// Backup Original Socket API & Data
		spec->own_sock.wait			= sock->wait;			
		spec->own_sock.recv			= sock->recv;
		spec->own_sock.send			= sock->send;
		spec->own_sock.getOSHandle	= sock->getOSHandle;
		spec->own_sock.specific		= sock->specific;
		spec->own_sock.specific_del = sock->specific_del;

		// Set Callback Mode Socket API & Data
		sock->wait					= Dz1SocketCallback2_skel_user_wait;		// return error function
		sock->recv					= Dz1SocketCallback2_skel_user_recv;		// return error function
		sock->send					= Dz1SocketCallback2_skel_user_write;		// callback mode write function
		sock->getOSHandle			= NULL;										// set NULL = no more changing mode
		sock->specific				= spec;										// Callback Mode Spec Data
		sock->specific_del			= (Dz1DelFunc)Dz1SocketCallback2Spec_del;	// Callback Mode Spec DataDelete

		// Callback mode Internal Data
		spec->rcvd_cb				= rx_cb;									// first step of receive
		spec->sent_cb				= tx_cb;									// last step of transmit
		if (user_ptr != NULL)
		{
			spec->user_ptr			= *user_ptr;								// user data for callback
			spec->user_ptr_del		=  user_ptr_del;							// user data delete

			if (user_ptr_del != NULL) (*user_ptr) = NULL;
		}
		spec->fd			= fd;					// system IO descriptor

		spec->release		= _Dz1SocketCallback2Spec_release;
	}
	return err;
}
// Initialize Data Only
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Allocated Spec Initialize
Dz1Error Dz1SocketCallback2Spec_skel_init(Dz1SocketCallback2Spec *spec,
										  Dz1TcpClientSocket *sock, SOCKET fd,
										  Dz1SockAddr *peer,
										  Dz1SockAddr *local,
										  u32_t rx_buf_size,
										  Dz1SocketCallback2Rcvd rx_cb,
										  Dz1SocketCallback2Sent tx_cb,
										  void **user_ptr, Dz1DelFunc user_ptr_del, bool_t no_lock)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	spec->ref_cnt = 1;
	pthread_mutex_init(&spec->lock, NULL);

	if (no_lock == FALSE)
	{
		pthread_mutex_lock(&spec->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

		if ((*errp = Dz1SocketCallback2Spec_skel_init_data(spec, sock, fd, peer, local, rx_buf_size, rx_cb, tx_cb, user_ptr, user_ptr_del)).code) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(_associated_socket_rollback, (void *)sock);
			if ((*errp = Dz1SocketCallback2_sys_reg(fd, spec)).code) ERR_OUT(errp);
			else
			{
				spec = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (_associated_socket_rollback, (void *)sock);
		}
		pthread_cleanup_pop(1); // (Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
	}
	else if ((*errp = Dz1SocketCallback2Spec_skel_init_data(spec, sock, fd, peer, local, rx_buf_size, rx_cb, tx_cb, user_ptr, user_ptr_del)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Allocated Spec Initialize
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Generate Spec and Initialize
Dz1SocketCallback2Spec *Dz1SocketCallback2Spec_skel_gen(Dz1TcpClientSocket *sock, 
														Dz1SockAddr *peer,
														Dz1SockAddr *local,
														size_t rx_buf_size,
														Dz1SocketCallback2Rcvd rx_cb,
														Dz1SocketCallback2Sent tx_cb,
														void **user_ptr, Dz1DelFunc user_ptr_del,
														bool_t no_lock, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SocketCallback2Spec *ret = NULL;
	
	if (sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (sock->getOSHandle == NULL) ERR_SET_OUT(errp, EPERM);
	else if ((ret = (Dz1SocketCallback2Spec *)Dz1Calloc(sizeof(Dz1SocketCallback2Spec), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		SOCKET fd = sock->getOSHandle(sock);
		pthread_cleanup_push(Dz1SocketCallback2Spec_delAndSetNull, (void *)&ret);

		if ((*errp = Dz1SocketCallback2Spec_skel_init(ret, sock, fd, peer, local, (u32_t)rx_buf_size, rx_cb, tx_cb, user_ptr, user_ptr_del, no_lock)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1SocketCallback2Spec_delAndSetNull, (void *)&spec);
	}
	return ret;
}
// Generate Spec and Initialize
///////////////////////////////////////////////////////////////////////////////

