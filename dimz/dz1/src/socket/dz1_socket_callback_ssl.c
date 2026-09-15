#if 0
#include <dz1.h>

#ifdef _DZ1_USE_SSL
#include "dz1_socket.h"
#include <dz1_bin.h>
#include <dz1_sock_addr.h>
#include <dz1_elastic_buf.h>
#include "../kernel/dz1_thread_stdio.h"
#include "dz1_socket_callback_ssl.h"

///////////////////////////////////////////////////////////////////////////////
// Error Detect
typedef enum Dz1SslBehavior
{
	Dz1SslBehavior_nop,
	Dz1SslBehavior_read,
	Dz1SslBehavior_write,
	Dz1SslBehavior_error
} Dz1SslBehavior;

static Dz1SslBehavior SslFuncRet2Behavior(SSL *ssl, int ssl_func_ret, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SslBehavior ret = Dz1SslBehavior_nop;

	int code = SSL_get_error(ssl, ssl_func_ret);
	Dz1Error_set(errp, 0);
	if (code != SSL_ERROR_NONE)
	{
		unsigned long numErr = ERR_get_error();
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
		char buf[128], *strErr = ERR_error_string(numErr, buf);
#endif
		switch(code)
		{
		default:
		case SSL_ERROR_SSL:
			// A failure in the SSL library occurred, usually a protocol error.
			// The OpenSSL error queue contains more information on the error.
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_eprintf("!!! SSL Error = [%d]%s\n", numErr, strErr);
#endif
			Dz1Error_set(errp, EFAULT);
			ret = Dz1SslBehavior_error;
			break;
		case SSL_ERROR_WANT_READ:
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_eprintf("@@@ WANT READ\n");
#endif
			ret = Dz1SslBehavior_read;
			break;
		case SSL_ERROR_WANT_WRITE:
			// The operation did not complete; the same TLS/SSL I/O function should be called again later.
			// If, by then, the underlying BIO has data available for reading(if the result code is SSL_ERROR_WANT_READ)
			// or allows writing data (SSL_ERROR_WANT_WRITE), then some TLS/SSL protocol progress will take place,
			// i.e. at least part of an TLS/SSL record will be read or written.
			// Note that the retry may again lead to a SSL_ERROR_WANT_READ or SSL_ERROR_WANT_WRITE condition.
			// There is no fixed upper limit for the number of iterations that may be necessary until progress
			// becomes visible at application protocol level. 

			// For socket BIOs (e.g. when SSL_set_fd() was used), select() or poll() on the underlying socket
			// can be used to find out when the TLS/SSL I/O function should be retried. 

			// Caveat: Any TLS/SSL I/O function can lead to either of SSL_ERROR_WANT_READ and SSL_ERROR_WANT_WRITE.
			// In particular, SSL_read() or SSL_peek() may want to write data and SSL_write() may want to read data.
			// This is mainly because TLS/SSL handshakes may occur at any time during the protocol
			// (initiated by either the client or the server);
			// SSL_read(), SSL_peek(), and SSL_write() will handle any pending handshakes. 
			// Dz1Error_set(errp, EAGAIN);
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_eprintf("@@@ WANT WRITE\n");
#endif
			ret = Dz1SslBehavior_write;
			break;
		case SSL_ERROR_WANT_X509_LOOKUP:
			// The operation did not complete because an application callback set by SSL_CTX_set_client_cert_cb()
			// has asked to be called again. The TLS/SSL I/O function should be called again later.
			// Details depend on the application.
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_eprintf("!!! SSL Error = [%d]%s\n", numErr, strErr);
#endif
			Dz1Error_set(errp, EPERM);
			ret = Dz1SslBehavior_error;
			break;
		case SSL_ERROR_SYSCALL:
			// Some I/O error occurred. The OpenSSL error queue may contain more information on the error.
			// If the error queue is empty (i.e. ERR_get_error() returns 0), ret can be used to find out more about the error:
			// If ret == 0, an EOF was observed that violates the protocol.
			// If ret == -1, the underlying BIO reported an I/O error (for socket I/O on Unix systems, consult errno for details). 
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_eprintf("!!! SSL Error = [%d]%s\n", numErr, strErr);
#endif
			if (numErr == 0)
			{
				if (ssl_func_ret == 0) ERR_SET_OUT(errp, EPIPE);
				else if (ssl_func_ret < 0)
				{	// ???
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
					Dz1Thread_eprintf("!!! SSL Error = BIO Fault\n");
#endif
					ERR_SET_OUT(errp, EFAULT);
				}
			}
			else
			{
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_eprintf("!!! SSL Error = [%d]%s\n", numErr, strErr);
#endif
				ERR_SET_OUT(errp, EFAULT);
			}
			ret = Dz1SslBehavior_error;
			break;
		case SSL_ERROR_ZERO_RETURN:
			// The TLS/SSL connection has been closed.
			// If the protocol version is SSL 3.0 or TLS 1.0, this result code is returned
			// only if a closure alert has occurred in the protocol,
			// i.e. if the connection has been closed cleanly.
			// Note that in this case SSL_ERROR_ZERO_RETURN does not necessarily indicate that the underlying transport has been closed.
 			ret = Dz1SslBehavior_nop;
			break;
		case SSL_ERROR_WANT_CONNECT:
		case SSL_ERROR_WANT_ACCEPT:
			// The operation did not complete; the same TLS/SSL I/O function should be called again later.
			// The underlying BIO was not connected yet to the peer and the call would block in connect()/accept().
			// The SSL function should be called again when the connection is established.

			// These messages can only appear with a BIO_s_connect() or BIO_s_accept() BIO, respectively.
			// In order to find out, when the connection has been successfully established,
			// on many platforms select() or poll() for writing on the socket file descriptor can be used.
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_eprintf("!!! SSL Error = [%d]%s\n", numErr, strErr);
#endif
			ERR_SET_OUT(errp, EFAULT); // don't care. just treat fatal error
			ret = Dz1SslBehavior_error;
			break;
		}
	}
	return ret;
}
// Error Detect
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TX Utility
static Dz1Error _ssl_outbound_bio_in_critical(Dz1SocketCallback2SpecSSL *ssl_spec, Dz1ElasticBuf *_el_buf, bool_t *ret_sent)
{	// BIO outbound
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;
	bool_t _sent = FALSE, *sentp = ret_sent == NULL ? &_sent : ret_sent;
	(*sentp) = FALSE;

	if (spec->tx_busy == FALSE)
	{
		Dz1ElasticBuf *elb_temp = NULL, *el_buf = NULL;

		register int sz = 0, size = 0;
		u8_t temp[1024];
		Dz1Binary *bin = NULL;

		if (_el_buf == NULL)
		{	// caller가 준 buf가 NULL이면 elb_temp를 생성하고 elb_temp를 el_buf에 대입
			if ((elb_temp = el_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT_RET(errp, err);
			else Dz1Error_set(errp, 0);
		}
		// caller가 준 buf가 NULL이 아니면 buf를 el_buf에 대입
		else el_buf = _el_buf;

		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb_temp);

		while ((sz = BIO_read(ssl_spec->egress, temp, 1024)) > 0)
		{
			Dz1ElasticBuf_push(el_buf, temp, sz);
			size += sz;
		}

		if (size > 0)
		{
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_eprintf(">>> TX %d byte\n", size);
#endif
			if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(el_buf, errp)) == NULL) ERR_OUT(errp);
			else if (Dz1SocketCallback2_skel_local_write(&ssl_spec->cb_spec, bin->data, bin->size, TRUE, errp) <= 0) ERR_OUT(errp);
			else
			{
//				spec->tx_busy = TRUE;
				(*sentp) = TRUE;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb_temp);
	}
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1Error _ssl_outbound_user_in_critical(Dz1SocketCallback2SpecSSL *ssl_spec, Dz1ElasticBuf *el_buf, bool_t *ret_sent)
{	// User Data outbound
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;
	bool_t _sent = FALSE, *sentp = ret_sent == NULL ? &_sent : ret_sent;
	(*sentp) = FALSE;

	if (spec->tx_busy == FALSE)
	{
		Dz1SocketCallback2Buffer *buf = ssl_spec->tx_user_buf;
//		WSABUF *iop = NULL;
		if (buf != NULL && buf->io_ptr.len > 0)
		{
			int status = 0;
			if ((status = SSL_write(ssl_spec->ssl, buf->io_ptr.buf, buf->io_ptr.len)) <= 0)
			{	// write down error
				switch(SslFuncRet2Behavior(ssl_spec->ssl, status, errp))
				{
				case Dz1SslBehavior_nop:
				case Dz1SslBehavior_read:
				case Dz1SslBehavior_write:
					if ((*errp = _ssl_outbound_bio_in_critical(ssl_spec, el_buf, ret_sent)).code) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				case Dz1SslBehavior_error:
					ERR_OUT(errp);
					break;
				}
			}
			else
			{	// 넣은만큼 원문 포인터를 움직인다.
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
				Dz1Thread_eprintf(">>> User Data %d byte written\n", status);
#endif
				buf->io_ptr.buf += status;
				buf->io_ptr.len -= status;

				// 에러 없음 : SSL이 BIO에 적어놓은 암호문 확인
				if ((*errp = _ssl_outbound_bio_in_critical(ssl_spec, el_buf, ret_sent)).code) { /* ERR_OUT(&err); */ }
				else Dz1Error_set(errp, 0);
			}
		}
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _ssl_outbound_in_critical(Dz1SocketCallback2SpecSSL *ssl_spec, bool_t *ret_sent)
{	// Check EGRESS BIO and SEND in critical section
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;
	bool_t _sent = FALSE, *sentp = ret_sent == NULL ? &_sent : ret_sent;
	(*sentp) = FALSE;

	if (spec->tx_busy == FALSE)
	{
		Dz1ElasticBuf *el_buf = Dz1ElasticBuf_new(1024, FALSE, errp);
		if (el_buf == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&el_buf);

			if ((*errp = _ssl_outbound_bio_in_critical(ssl_spec, el_buf, sentp)).code) 
			{
				ERR_OUT(errp);
			}
			else if (*sentp == TRUE) Dz1Error_set(errp, 0);

			else if ((*errp = _ssl_outbound_user_in_critical(ssl_spec, el_buf, sentp)).code) 
			{
				ERR_OUT(errp);
			}
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&el_buf);
		}
	}

	return err;
}
 
// static Dz1Error _ssl_outbound(Dz1SocketCallback2SpecSSL *ssl_spec, bool_t *ret_sent)
// {	// full outgoing procedure
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;
// 
// 	pthread_mutex_lock(&spec->lock);
// 	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
// 	// Begin of Critical
// 
// #ifdef DZ1_SOCKET_CALLBACK_DEBUG
// 	Dz1Thread_eprintf("### _ssl_outbound() : Called\n");
// #endif
// 
// 	if ((*errp = _ssl_outbound_in_critical(ssl_spec, ret_sent)).code) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 
// #ifdef DZ1_SOCKET_CALLBACK_DEBUG
// 	Dz1Thread_eprintf("### _ssl_outbound() : Return\n");
// #endif
// 
// 	// End of Critical
// 	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
// 
// 	return err;
// }
// TX Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TX Callback : Last Step of Transmit
static void _ssl_tx_cb(void *user_ptr, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *status)
{	// unlocked
	DZ1_ERROR_SAFE_VAR(errp, err);

	bool_t sent = FALSE;

	Dz1SocketCallback2SpecSSL *ssl_spec = (Dz1SocketCallback2SpecSSL *)user_ptr;
	Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;

	pthread_mutex_lock(&spec->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
	// Begin of Critical

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### _ssl_tx_cb() : Called\n");
#endif

	spec->tx_busy = FALSE;

	// try TX to keep sending continue
	if ((*errp = _ssl_outbound_in_critical(ssl_spec, &sent)).code)					// BIO flush, SSL_write & BIO flush
	{	// TX Fault
		Dz1SocketCallback2Spec_closeSock(spec);

		pthread_mutex_unlock(&spec->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
		// Escape from Critical

		ssl_spec->sent_cb(ssl_spec->user_ptr, spec->peer, spec->local, errp);

		// Return to Critical
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
	}
	else if (sent == TRUE) Dz1Error_set(errp, 0);
	else
	{	// no data to send -> check user desired data
		Dz1SocketCallback2Buffer *buf = ssl_spec->tx_user_buf;
		if (buf != NULL && buf->io_ptr.len == 0)
		{	// TX Complete
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1SocketCallback2Buffer *txb = ssl_spec->tx_user_buf;
			size_t sent_size = txb->io_ptr.buf - txb->data;
			Dz1Thread_eprintf("### _ssl_tx_cb() : User Data %u Byte Sent\n", sent_size);
#endif
			Dz1SocketCallback2Buffer_delAndSetNull(&ssl_spec->tx_user_buf);

			pthread_mutex_unlock(&spec->lock);
			pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
			// Escape from Critical

			ssl_spec->sent_cb(ssl_spec->user_ptr, spec->peer, spec->local, NULL);

			// Return to Critical
			pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
		}
	}

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### _ssl_tx_cb() : Return\n");
#endif
	// End of Critical
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
}
// TX Callback
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// User Side Write
ssize_t Dz1SocketCallback2_ssl_user_write(Dz1TcpClientSocket *p, u8_t *data, size_t size, u32_t flag,
										  struct timeval *to, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = -1;
	Dz1SocketCallback2SpecSSL *ssl_spec = (Dz1SocketCallback2SpecSSL *)p->specific;
	Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;

	pthread_mutex_lock(&spec->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
	// Start Critical

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### Dz1SocketCallback2_ssl_user_write() : Called\n");
#endif

	if (ssl_spec->tx_user_buf != NULL) ERR_SET_OUT(errp, EAGAIN);
	else if ((ssl_spec->tx_user_buf = Dz1SocketCallback2Buffer_new(data, size, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SocketCallback2Buffer_delAndSetNull, (void *)&ssl_spec->tx_user_buf);

		if ((*errp = _ssl_outbound_in_critical(ssl_spec, NULL)).code) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret = (ssize_t)size;
		}

		pthread_cleanup_pop(errp->code); // (Dz1SocketCallback2Buffer_delAndSetNull, (void *)&spec->tx_buf);
	}

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### Dz1SocketCallback2_ssl_user_write() : Return\n");
#endif

	// End Critical
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&ssl_spec->tx_user_buf);

	return ret;
}
// User Side Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// RX Callback
static void push_to_ingress_bio(Dz1SocketCallback2SpecSSL *ssl_spec, u8_t *data, size_t sz) // , BIO *dst, u8_t *data, size_t sz)
{
	int status = 0;
	u8_t *cp = data;
	while(sz)
	{
		if ((status = BIO_write(ssl_spec->ingress, cp, (int)sz)) > 0)
		{
			cp += status;
			sz -= status;
		}
		else break;
	}
}

static Dz1ElasticBuf *_extract_data_from_ssl(Dz1SocketCallback2SpecSSL *ssl_spec, size_t *ret_user_size, Dz1Error *errp)
{	// in critical
	size_t size = 0;
	Dz1ElasticBuf *ret = Dz1ElasticBuf_new(1024, FALSE, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
//		Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;

		bool_t done = FALSE;
		int status;
		u8_t temp[1024];

		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&ret);

		while(errp->code == 0 && done == FALSE)
		{	// SSL에서 뽑을만큼 뽑는다.
			if ((status = SSL_read(ssl_spec->ssl, temp, 1024)) <= 0)
			{	// 에러가 발생
				switch(SslFuncRet2Behavior(ssl_spec->ssl, status, errp))
				{
				default:
				case Dz1SslBehavior_nop:
				case Dz1SslBehavior_read:
				case Dz1SslBehavior_write:
					if ((*errp = _ssl_outbound_in_critical(ssl_spec, NULL)).code) ERR_OUT(errp);
					else
					{
						Dz1Error_set(errp, 0);
						done = TRUE;
					}
					break;
				case Dz1SslBehavior_error:
					ERR_OUT(errp);
					break;
				}
				break;
			}
			else
			{
				Dz1ElasticBuf_push(ret, temp, status);
				size += status;
			}
		}

		pthread_cleanup_pop(errp->code); // (Dz1ElasticBuf_delAndSetNull, (void *)&ret);
	}

	if (ret_user_size) (*ret_user_size) = size;
	return ret;
}

////////////////////////////////////////////////////////////////
// First Step of Receive
static void _ssl_rx_cb(void *user_ptr, Dz1SockAddr *peer, Dz1SockAddr *local, u8_t *data, size_t size, Dz1Error *status)
{	// unlocked 
	Dz1SocketCallback2SpecSSL *ssl_spec = (Dz1SocketCallback2SpecSSL *)user_ptr;
	Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;

	DZ1_ERROR_SAFE_VAR(errp, err);

	pthread_mutex_lock(&spec->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
	// Begin Critical

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### _ssl_rx_cb() : Called\n");
#endif

	if (status == NULL || status->code == 0)
	{	// success, but check size
		if (size > 0)
		{
			size_t user_size = 0;
			Dz1ElasticBuf *el_buf = NULL;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
			Dz1Thread_eprintf("<<< RX %d Byte\n", size);
#endif
			push_to_ingress_bio(ssl_spec, data, size);	// 수신한 Data를 SSL Ingress에 넣는다
			if ((el_buf = _extract_data_from_ssl(ssl_spec, &user_size, errp)) == NULL)
			{
				if (errp->code == EAGAIN)
				{	// Full TX Process
				}
				else ERR_OUT(errp);
			}
			else
			{
				pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&el_buf);
				if (user_size == 0) { }
				else
				{	// Normal Received Process
					Dz1Binary *bin = NULL;

					if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(el_buf, errp)) == NULL) ERR_OUT(errp);
					else if (bin->size == 0) ERR_SET_OUT(errp, EFAULT);
					else
					{
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
						Dz1Thread_eprintf("<<< User Data %u Byte Read\n", bin->size);
#endif

						pthread_mutex_unlock(&spec->lock);
						pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
						ssl_spec->rcvd_cb(ssl_spec->user_ptr, spec->peer, spec->local, bin->data, bin->size, NULL);
						pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);

						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&el_buf);
			}
		}
		else
		{	// EPIPE
			ERR_SET_OUT(errp, EPIPE);

			pthread_mutex_unlock(&spec->lock);
			pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
			ssl_spec->rcvd_cb(ssl_spec->user_ptr, spec->peer, spec->local, NULL, 0, errp);
			pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
		}
	}
	else
	{	// fail
		pthread_mutex_unlock(&spec->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
		ssl_spec->rcvd_cb(ssl_spec->user_ptr, spec->peer, spec->local, NULL, 0, status);
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_lock, (void *)&spec->lock);
	}
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### _ssl_rx_cb() : Return\n");
#endif
	// End Critical
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
}
// RX Callback
///////////////////////////////////////////////////////////////////////////////

static const SSL_METHOD *_get_server_method(Dz1SocketCallback2SSLVer mode)
{
	const SSL_METHOD *ret = NULL;
	switch(mode)
	{
#if 0
	case Dz1SocketCallback2SSLVer_2:
		ret = SSLv2_server_method();
		break;
	case Dz1SocketCallback2SSLVer_3:
		ret = SSLv3_server_method();
		break;
#endif
	case Dz1SocketCallback2SSLVer_23:
		ret = SSLv23_server_method();
		break;
	default:
		break;
	}
	return ret;
}

static void _Dz1SocketCallback2SpecSSL_release(Dz1SocketCallback2Spec *spec)
{
	Dz1SocketCallback2SpecSSL *p = (Dz1SocketCallback2SpecSSL *)spec;
//	Dz1SocketCallback2Spec *spec = (Dz1SocketCallback2Spec *)p;

	if (p == NULL) return;
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### _Dz1SocketCallback2SpecSSL_del() : Called\n");
#endif

	Dz1Thread_eprintf("### _Dz1SocketCallback2SpecSSL_del() : Called\n");

	if (p->ssl) SSL_shutdown(p->ssl);

	if (p->ctx) SSL_CTX_free(p->ctx); p->ctx = NULL;
	if (p->ssl) SSL_free(p->ssl); p->ssl = NULL;

	Dz1SocketCallback2Buffer_delAndSetNull(&p->tx_user_buf);

	Dz1SocketCallback2Spec_closeSock(spec);

	Dz1SockAddr_delAndSetNull(&spec->peer);
	Dz1SockAddr_delAndSetNull(&spec->local);

	Dz1SocketCallback2Buffer_delAndSetNull(&spec->tx_buf);
	Dz1SocketCallback2Buffer_delAndSetNull(&spec->rx_buf);

	spec->fd = -1;

	if (p->user_ptr != NULL && p->user_ptr_del != NULL) p->user_ptr_del(p->user_ptr);
	p->user_ptr = NULL;
	p->user_ptr_del = NULL;

	pthread_mutex_destroy(&spec->lock);
	Dz1Free(p);

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### _Dz1SocketCallback2SpecSSL_del() : return\n");
#endif
}

static void Dz1SocketCallback2SpecSSL_del(Dz1SocketCallback2SpecSSL *p)
{
	int ref_cnt = -1;
	Dz1SocketCallback2Spec *orig_spec = (Dz1SocketCallback2Spec *)p;
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	int temp;
#endif
	if (p == NULL) return;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### Dz1SocketCallback2SpecSSL_del() : Called\n");
#endif

// 	pthread_mutex_lock(&spec->lock);
// 	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
	// Begin of Critical

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	temp = orig_spec->ref_cnt;
#endif

	// native socket의 resource를 삭제한다. -> 대기탄 아이들이 error를 post한다.
	Dz1SocketCallback2Spec_closeSock(orig_spec);

	// reference 를 감소 시킨다
	if (orig_spec->ref_cnt > 0) orig_spec->ref_cnt--;
	ref_cnt = orig_spec->ref_cnt;

#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("Dz1SocketCallback2SpecSSL_del() ref_cnr = %d -> %d\n", temp, orig_spec->ref_cnt);
#endif
	// End of Critical
// 	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);

	// reference count가 0이면 자원을 해제한다.
	if (ref_cnt == 0) _Dz1SocketCallback2SpecSSL_release((Dz1SocketCallback2Spec *)p);
#ifdef DZ1_SOCKET_CALLBACK_DEBUG
	Dz1Thread_eprintf("### Dz1SocketCallback2SpecSSL_del() : return\n");
#endif
}

static __inline__ void Dz1SocketCallback2SpecSSL_delAndSetNull(void *pptr)
{
	Dz1SocketCallback2SpecSSL **p = (Dz1SocketCallback2SpecSSL **)pptr;
	Dz1SocketCallback2SpecSSL_del(*p); *p = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// SSL Server Association
static Dz1Error _init_ssl_server(Dz1SocketCallback2SpecSSL *ssl_spec, Dz1SocketCallback2SSLVer ver, str_t certName, str_t keyName)
{
	int status;
	DZ1_ERROR_SAFE_VAR(errp, err);
	const SSL_METHOD *meth = NULL;

	if ((meth = _get_server_method(ver)) == NULL) ERR_SET_OUT(errp, EINVAL);							// 메써드 결정
	if ((ssl_spec->ctx = SSL_CTX_new((SSL_METHOD *)meth)) == NULL) ERR_SET_OUT(errp, EFAULT);			// 컨텍스트 생성
	else if ((status = SSL_CTX_use_certificate_file(ssl_spec->ctx, certName, SSL_FILETYPE_PEM)) <= 0)	// 서트파일 설정
	{
		char errstr[512];
		int errnum = ERR_get_error();
		Dz1Thread_eprintf("!!! _init_ssl_server() : SSL_CTX_use_certificate_file error = %s(%d)\n", ERR_error_string(errnum, errstr), errnum);
		Dz1Thread_eprintf("!!! _init_ssl_server() : SSL_CTX_use_certificate_file status = %d\n", status);
		Dz1Thread_eprintf("!!! _init_ssl_server() : certName = %s\n", certName);
		Dz1Error_set(errp, EFAULT);
	}
	else if ((status = SSL_CTX_use_PrivateKey_file(ssl_spec->ctx, keyName, SSL_FILETYPE_PEM)) <= 0)		// 사설키 파일 설정
	{
		char errstr[512];
		int errnum = ERR_get_error();
		Dz1Thread_eprintf("!!! _init_ssl_server() : SSL_CTX_use_PrivateKey_file error = %s(%d)\n", ERR_error_string(errnum, errstr), errnum);
		Dz1Thread_eprintf("!!! _init_ssl_server() : SSL_CTX_use_PrivateKey_file status = %d\n", status);
		Dz1Thread_eprintf("!!! _init_ssl_server() : keyName = %s\n", keyName);
		Dz1Error_set(errp, EFAULT);
	}
	else if (!SSL_CTX_check_private_key(ssl_spec->ctx)) Dz1Error_set(errp, EFAULT);						// 사설키 확인
	else if ((ssl_spec->ssl = SSL_new(ssl_spec->ctx)) == NULL) ERR_SET_OUT(errp, EFAULT);				// SSL 생성
	else if ((ssl_spec->ingress = BIO_new(BIO_s_mem())) == NULL) ERR_SET_OUT(errp, EFAULT);				// BIO 연결
	else if ((ssl_spec->egress = BIO_new(BIO_s_mem())) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		SSL_set_bio(ssl_spec->ssl, ssl_spec->ingress, ssl_spec->egress);
		Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1Error Dz1SocketCallback2SSL_assoServer(Dz1TcpClientSocket *sock,
										  Dz1SockAddr *peer, Dz1SockAddr *local, u32_t rx_buf_size,
										  Dz1SocketCallback2Rcvd rx_cb, 
										  Dz1SocketCallback2Sent tx_cb,
										  void **user_ptr, Dz1DelFunc user_ptr_del,
										  Dz1SocketCallback2SSLVer ssl_ver, str_t certName, str_t keyName)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (sock->getOSHandle == NULL) ERR_SET_OUT(errp, EPERM);
	else
	{	// Native Socket을 SSL Callback Mode로 바꾼다
		SOCKET fd = sock->getOSHandle(sock);
		Dz1SocketCallback2SpecSSL *ssl_spec = (Dz1SocketCallback2SpecSSL *)Dz1Calloc(sizeof(Dz1SocketCallback2SpecSSL), 1, errp);
		if (ssl_spec == NULL) ERR_OUT(errp);
		else
		{
			Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;
			pthread_cleanup_push(Dz1SocketCallback2SpecSSL_delAndSetNull, (void *)&ssl_spec);

			spec->ref_cnt = 1;
			pthread_mutex_init(&spec->lock, NULL);

			pthread_mutex_lock(&spec->lock);
			pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
			// Start Critical Section

			if (0) { }
			else if ((*errp = _init_ssl_server(ssl_spec, ssl_ver, certName, keyName)).code) ERR_OUT(errp);
			else if ((*errp = Dz1SocketCallback2Spec_skel_init_data(&ssl_spec->cb_spec, sock, fd, peer, local, 
																	rx_buf_size, _ssl_rx_cb, _ssl_tx_cb, 
																	ssl_spec, (Dz1DelFunc)Dz1SocketCallback2SpecSSL_del)).code) ERR_OUT(errp);
			else
			{
// 				sock->specific			= ssl_spec;
 				sock->specific_del		= (Dz1DelFunc)Dz1SocketCallback2SpecSSL_del;
				sock->send				= Dz1SocketCallback2_ssl_user_write;

				spec->release			= _Dz1SocketCallback2SpecSSL_release;

				ssl_spec->rcvd_cb		= rx_cb;
				ssl_spec->sent_cb		= tx_cb;
				if (user_ptr != NULL) { ssl_spec->user_ptr = *user_ptr; *user_ptr = NULL; }
				ssl_spec->user_ptr_del	= user_ptr_del;

				pthread_cleanup_push(_associated_socket_rollback, (void *)sock);

				if ((*errp = Dz1SocketCallback2_sys_reg(fd, spec)).code) ERR_OUT(errp);
				else
				{
					int status;
					if ((status = SSL_accept(ssl_spec->ssl)) <= 0)
					{
						switch(SslFuncRet2Behavior(ssl_spec->ssl, status, errp))
						{
						default:
						case Dz1SslBehavior_nop:
						case Dz1SslBehavior_read:
						case Dz1SslBehavior_write:
							if ((*errp = _ssl_outbound_bio_in_critical(ssl_spec, NULL, NULL)).code) ERR_OUT(errp);
							else
							{
								ssl_spec = NULL;
								Dz1Error_set(errp, 0);
							}
							break;
						case Dz1SslBehavior_error:
							ERR_OUT(errp);
							break;
						}
					}
					else if ((*errp = _ssl_outbound_in_critical(ssl_spec, NULL)).code) ERR_OUT(errp);
					else
					{
						ssl_spec = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(errp->code); // (_associated_socket_rollback, (void *)sock);
			}
			// End Critical Section
			pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
			pthread_cleanup_pop(errp->code); // (Dz1SocketCallback2SpecSSL_delAndSetNull, (void *)&ssl_spec);
		}
	}
	return err;
}
// SSL Server Association
///////////////////////////////////////////////////////////////////////////////

static const SSL_METHOD *_get_client_method(Dz1SocketCallback2SSLVer ver)
{
	const SSL_METHOD *ret = NULL;
	switch(ver)
	{
#if 0
	case Dz1SocketCallback2SSLVer_2:
		ret = SSLv2_client_method();
		break;
	case Dz1SocketCallback2SSLVer_3:
		ret = SSLv3_client_method();
		break;
#endif
	case Dz1SocketCallback2SSLVer_23:
		ret = SSLv23_client_method();
		break;
	default:
		break;
	}
	return ret;
}

static Dz1Error _init_ssl_client(Dz1SocketCallback2SpecSSL *ssl_spec, Dz1SocketCallback2SSLVer ver, str_t ciper_list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	const SSL_METHOD *meth = NULL;

	if ((meth = _get_client_method(ver)) == NULL) ERR_SET_OUT(errp, EINVAL);						// 메써드 결정
	else if ((ssl_spec->ctx = SSL_CTX_new((SSL_METHOD *)meth)) == NULL) ERR_SET_OUT(errp, EFAULT);	// 컨텍스트 생성
	else if ((ssl_spec->ssl = (SSL *)SSL_new(ssl_spec->ctx)) == NULL) ERR_SET_OUT(errp, EFAULT);	// SSL 생성
	else if (SSL_set_cipher_list(ssl_spec->ssl, ciper_list) == 0)
	{
		Dz1Thread_eprintf("!!! CIFER Fail = %s\n", ciper_list);
		ERR_SET_OUT(errp, EFAULT);		// cifer설정
	}
	else if ((ssl_spec->ingress = BIO_new(BIO_s_mem())) == NULL) ERR_SET_OUT(errp, EFAULT);			// BIO 연결
	else if ((ssl_spec->egress = BIO_new(BIO_s_mem())) == NULL) ERR_SET_OUT(errp, EFAULT);
	else SSL_set_bio(ssl_spec->ssl, ssl_spec->ingress, ssl_spec->egress);

	return err;
}

Dz1Error Dz1SocketCallback2SSL_assoClient(Dz1TcpClientSocket *sock,
										  Dz1SockAddr *peer, Dz1SockAddr *local, u32_t rx_buf_size,
										  Dz1SocketCallback2Rcvd rx_cb, 
										  Dz1SocketCallback2Sent tx_cb,
										  void **user_ptr, Dz1DelFunc user_ptr_del,
										  Dz1SocketCallback2SSLVer ssl_ver, str_t cyper_str)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (sock->getOSHandle == NULL) ERR_SET_OUT(errp, EPERM);
	else
	{	// Native Socket을 SSL Callback Mode로 바꾼다
		SOCKET fd = sock->getOSHandle(sock);
		Dz1SocketCallback2SpecSSL *ssl_spec = (Dz1SocketCallback2SpecSSL *)Dz1Calloc(sizeof(Dz1SocketCallback2SpecSSL), 1, errp);
		if (ssl_spec == NULL) ERR_OUT(errp);
		else
		{
			Dz1SocketCallback2Spec *spec = &ssl_spec->cb_spec;
			pthread_cleanup_push(Dz1SocketCallback2SpecSSL_delAndSetNull, (void *)&ssl_spec);

			spec->ref_cnt = 1;
			pthread_mutex_init(&spec->lock, NULL);

			pthread_mutex_lock(&spec->lock);
			pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
			// Start Critical Section

			if (0) { }
			else if ((*errp = _init_ssl_client(ssl_spec, ssl_ver, cyper_str)).code) ERR_OUT(errp);
			else if ((*errp = Dz1SocketCallback2Spec_skel_init_data(&ssl_spec->cb_spec, sock, fd, 
																	peer, local, rx_buf_size, 
																	_ssl_rx_cb, _ssl_tx_cb, 
																	ssl_spec, (Dz1DelFunc)Dz1SocketCallback2SpecSSL_del)).code) ERR_OUT(errp);
			else
			{
// 				sock->specific		= ssl_spec;
 				sock->specific_del	= (Dz1DelFunc)Dz1SocketCallback2SpecSSL_del;
				sock->send = Dz1SocketCallback2_ssl_user_write;

				spec->release = _Dz1SocketCallback2SpecSSL_release;

				ssl_spec->rcvd_cb = rx_cb;
				ssl_spec->sent_cb = tx_cb;
				if (user_ptr != NULL) { ssl_spec->user_ptr = *user_ptr; *user_ptr = NULL; }
				ssl_spec->user_ptr_del = user_ptr_del;

				pthread_cleanup_push(_associated_socket_rollback, (void *)sock);
				if ((*errp = Dz1SocketCallback2_sys_reg(fd, spec)).code) ERR_OUT(errp);
				else
				{
					int status;
					if ((status = SSL_connect(ssl_spec->ssl)) <= 0)
					{	// error occur
						switch(SslFuncRet2Behavior(ssl_spec->ssl, status, errp))
						{
						default:
						case Dz1SslBehavior_nop:
						case Dz1SslBehavior_read:
						case Dz1SslBehavior_write:
							if ((*errp = _ssl_outbound_bio_in_critical(ssl_spec, NULL, NULL)).code) ERR_OUT(errp);		// outbound process
							else
							{
								ssl_spec = NULL;
								Dz1Error_set(errp, 0);
							}
							break;
						case Dz1SslBehavior_error:
							break;
						}
					}
					else if ((*errp = _ssl_outbound_in_critical(ssl_spec, NULL)).code) ERR_OUT(errp);		// outbound process
					else
					{
						ssl_spec = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(errp->code); // (_associated_socket_rollback, (void *)sock);
			}

			// End Critical Section
			pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&spec->lock);
			pthread_cleanup_pop(1); // (Dz1SocketCallback2SpecSSL_delAndSetNull, (void *)&ssl_spec);
		}
	}
	return err;
}

static void _ssl_err_queue_clean(void)
{
	Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "_ssl_err_queue_clean() : Called\n");
#if OPENSSL_VERSION_NUMBER <= 0x009080efL
	ERR_remove_state(0);
#endif
}

static Dz1ThreadInitEntry		 thread_ssl_init = Dz1ThreadInitEntryInit(NULL);
static Dz1ThreadCleanupEntry	 thread_ssl_clean = Dz1ThreadCleanupEntryInit(_ssl_err_queue_clean);

Dz1Error Dz1SocketCallback2SSL_init(void)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ERR_load_crypto_strings();
	SSL_load_error_strings();
	SSL_library_init();

	if (Dz1ThreadBarrier_reg(&thread_ssl_init, &thread_ssl_clean, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

void Dz1SocketCallback2SSL_clean(void)
{
	CONF_modules_free();
#if OPENSSL_VERSION_NUMBER <= 0x009080efL
	ERR_remove_state(0);
#endif
	ENGINE_cleanup();
	CONF_modules_unload(1);
	ERR_free_strings();
	EVP_cleanup();
	CRYPTO_cleanup_all_ex_data();
#if OPENSSL_VERSION_NUMBER <= 0x009080efL
	sk_free(SSL_COMP_get_compression_methods());
#endif
}
#else	// #ifdef _DZ1_USE_SSL
int __dz1_socket_ssl_avoid_no_symbol_warning(void) { return 0; }
#endif	// #ifdef _DZ1_USE_SSL
#else
int __avoid_no_symbol_warning_dz1_socket_callback_ssl__ = 0;
#endif