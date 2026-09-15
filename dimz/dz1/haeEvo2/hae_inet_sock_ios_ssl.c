#include <pthread.h>
#include <openssl/ssl.h> 

#include <hae_local_memory.h>
#include <hae_inet_sock_ios.h>
#include <hae_inet.h>
#include <hae_misc.h>
#include <hae_inet_sock_ios_ssl.h>

#include <hae_output.h>
#define DBG_OUT(err)			HaeOut->printf(0, __FILE__ ":%d = %s(%d)\n", __LINE__, strerror((err)), (err))

static int translateSSLErrorToSyserr(SSL *ssl, int ssl_func_ret)
{
	int err = 0;
	switch(SSL_get_error(ssl, ssl_func_ret))
	{
		case SSL_ERROR_NONE:
			err = 0;
			break;
		case SSL_ERROR_ZERO_RETURN:
			err = EPIPE;
			break;
		case SSL_ERROR_WANT_READ: case SSL_ERROR_WANT_WRITE:
			err = EAGAIN;
			break;
		case SSL_ERROR_WANT_CONNECT:
	//	case SSL_ERROR_WANT_ACCEPT:
			err = EINVAL;
			break;
		case SSL_ERROR_WANT_X509_LOOKUP: case SSL_ERROR_SSL:
			err = EFAULT;
			break;
		case SSL_ERROR_SYSCALL:
			err = errno;
			break;
	}
	return err;
}

#ifdef HAE_INET_SSL_SOCKET_IOS_PRINT_X509
static void print_x509(SSL *ssl) 
{ 
	char *ascii_cert = NULL; 
	X509 *cert = SSL_get_peer_certificate(ssl); 
	BIO *b; 
	BUF_MEM *bptr; 

	b = BIO_new(BIO_s_mem()); 

	if(X509_print(b, cert) > 0) 
	{ 
		BIO_get_mem_ptr(b, &bptr); 
		ascii_cert = (char *)malloc(1 + bptr->length); 
		memcpy(ascii_cert, bptr->data, bptr->length); 
	} 
	else 
	{ 
		ascii_cert = (char *)malloc(1024); 
		sprintf(ascii_cert, "This certificate has never been seen before and can't be shown\n"); 
	} 

	BIO_free(b); 

	/* X.509   */ 
	printf("X.509:\n%s\n", ascii_cert); 
} 
#endif

typedef struct HaeInetSSLSockIOSParam
{
	HaeInetSSLSocketIOSMode	 mode;
	str_t					 server_req_name;
	str_t					 server_key_name;
	SSL						*ssl;
} HaeInetSSLSockIOSParam;

static void haeInetSSLSockIOSParam_del(HaeInetSSLSockIOSParam *p)
{
	if (!p) return;
	if (p->server_req_name) LOCAL_FREE(p->server_req_name);
	if (p->server_key_name) LOCAL_FREE(p->server_key_name);
	if (p->ssl)
	{
		SSL_shutdown(p->ssl);   
		SSL_free (p->ssl); 
	}
	LOCAL_FREE(p);
}

static void HaeInetSSLSockIOSParam_delAndSetNull(void *ptr)
{
	HaeInetSSLSockIOSParam **p = (HaeInetSSLSockIOSParam **)ptr;
	haeInetSSLSockIOSParam_del(*p); *p = NULL;
}

static SSL_METHOD *meth = NULL;
static SSL_CTX *ctx = NULL;

static int meth_init(int mode)
{
	int err = 0;
	SSL_METHOD *(*get_method)(void) = ((mode == HAE_INET_SSL_SOCKET_IOS_SERVER) ? SSLv3_server_method : SSLv3_client_method);
	SSLeay_add_ssl_algorithms();
	SSL_load_error_strings();
	if ((meth = get_method()) == NULL) { err = EFAULT; DBG_OUT(err); }
	return err;
}

static HaeInetSSLSockIOSParam *haeInetSSLSockIOSParam_new(HaeInetSSLSocketIOSMode mode, str_t server_req_name, str_t server_key_name, 
															str_t ciper_list, int *err)
{
	HaeInetSSLSockIOSParam *ret = NULL;
	if (meth == NULL && (*err = meth_init(mode))) { DBG_OUT(*err); }
	else if (ctx == NULL && (ctx = SSL_CTX_new(meth)) == NULL) { *err = EFAULT; DBG_OUT(*err); }
	else
	{
		if ((ret = (HaeInetSSLSockIOSParam *)LOCAL_MALLOC(sizeof(HaeInetSSLSockIOSParam))) == NULL) { *err = ENOMEM; DBG_OUT(*err); }
		else
		{
			memset(ret, 0, sizeof(HaeInetSSLSockIOSParam));
			pthread_cleanup_push(HaeInetSSLSockIOSParam_delAndSetNull, (void *)&ret);

			if ((ret->ssl = SSL_new(ctx)) == NULL) { *err = EFAULT; DBG_OUT(*err); }
			else
			{
				if (mode == HAE_INET_SSL_SOCKET_IOS_SERVER)
				{
					if ((ret->server_req_name = haeMiscStr_cloneToLocal(server_req_name, err)) == NULL) { DBG_OUT(*err); }
					else if ((ret->server_key_name = haeMiscStr_cloneToLocal(server_key_name, err)) == NULL) { DBG_OUT(*err); }
					else if (SSL_CTX_use_certificate_file(ctx, ret->server_req_name, SSL_FILETYPE_PEM) <= 0) { *err = EFAULT; DBG_OUT(*err); }
					else if (SSL_CTX_use_PrivateKey_file(ctx, ret->server_key_name, SSL_FILETYPE_PEM) <= 0) { *err = EFAULT; DBG_OUT(*err); }
					else if (!SSL_CTX_check_private_key(ctx)) { *err = EFAULT; DBG_OUT(*err); }
					else *err = 0;
				}
				else
				{
					if (ciper_list && strlen(ciper_list)) SSL_set_cipher_list(ret->ssl, ciper_list); // "SEED-SHA:AES256-SHA"
					ret->server_req_name = NULL;
					ret->server_key_name = NULL;
					*err = 0;
				}
			}
			pthread_cleanup_pop(*err); // (HaeInetSSLSockIOSParam_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

static int ssl_combine(SOCKET fd, void *p)
{
	int err = 0, ssl_func_ret;
	HaeInetSSLSockIOSParam *param = (HaeInetSSLSockIOSParam *)p;

	SSL_set_fd(param->ssl, fd); 

	if (param->mode == HAE_INET_SSL_SOCKET_IOS_SERVER)
		ssl_func_ret = SSL_accept (param->ssl);
	else
		ssl_func_ret = SSL_connect(param->ssl);     
	
	if ((err = translateSSLErrorToSyserr(param->ssl, ssl_func_ret))) { DBG_OUT(err); }

#ifdef HAE_INET_SSL_SOCKET_IOS_PRINT_X509
	{
		X509 *server_cert = NULL; 
		printf("SSL connection using %s\n", SSL_get_cipher(param->ssl)); 
		server_cert = SSL_get_peer_certificate(param->ssl);     

		print_x509(param->ssl); 

		X509_free (server_cert); 
	}

	if (param->mode == HAE_INET_SSL_SOCKET_IOS_SERVER)
	{
		X509 *client_cert = SSL_get_peer_certificate (ssl); 
		if (client_cert != NULL)  
		{ 
			str_t str = NULL;

			printf ("Client certificate:\n"); 
			if ((str = X509_NAME_oneline (X509_get_subject_name (client_cert), 0, 0)))
			{
				printf ("\t subject: %s\n", str); 
				free (str); 
			}
			if ((str = X509_NAME_oneline(X509_get_issuer_name(client_cert), 0, 0)))
			{
				printf ("\t issuer: %s\n", str); 
				free (str); 
			}
			X509_free (client_cert); 
		}  
		else 
			printf ("Client does not have certificate.\n"); 
	}
#endif

	return err;
}

static int ssl_wait(SOCKET fd, struct timeval *to, void *param)
{
	return hae_inet_detectIncome(fd, to);
}

// return read byte or -1, err will assign when return -1, 0 mean closed
static int ssl_recv(SOCKET fd, u8_t *buf, int size, void *param, int *err)
{
	int local_err, *errp = err ? err : &local_err;
	HaeInetSSLSockIOSParam *p = (HaeInetSSLSockIOSParam *)param;

	int read_byte = SSL_read(p->ssl, buf, size);

	if ((*errp = translateSSLErrorToSyserr(p->ssl, read_byte))) { DBG_OUT(*errp); }

	return *errp ? -1 : read_byte;
}

// return 0 or error code
static int ssl_send(SOCKET fd, u8_t *buf, int buf_size, void *param)
//(SSL *ssl, u8_t *buf, int buf_size)
{
	int err = 0;
	HaeInetSSLSockIOSParam *p = (HaeInetSSLSockIOSParam *)param;

	int write_byte = SSL_write(p->ssl, buf, buf_size);

	if ((err = translateSSLErrorToSyserr(p->ssl, write_byte))) { DBG_OUT(err); }

	return err;
}

HaeInetSocketIOS *haeInetSSLSockIos_new(HaeInetSSLSocketIOSMode mode, str_t server_req_name, str_t server_key_name, str_t ciper_list, int *err)
{
	int local_err, *errp = err ? err : &local_err;

	HaeInetSocketIOS *ret = NULL;

	HaeInetSSLSockIOSParam *param = haeInetSSLSockIOSParam_new(mode, server_req_name, server_key_name, ciper_list, errp);
	if (param == NULL) { DBG_OUT(*errp); }
	else
	{
		pthread_cleanup_push((HaeGeneralDelFunc)haeInetSSLSockIOSParam_del, (void *)param);

		if ((ret = haeInetSocketIOS_new(ssl_combine, ssl_wait, ssl_recv, ssl_send, param, (HaeGeneralDelFunc)haeInetSSLSockIOSParam_del, errp)) == NULL)
		{ DBG_OUT(*errp); } else { *errp = 0; }

		pthread_cleanup_pop(*errp); // ((HaeGeneralDelFunc)haeInetSSLSockIOSParam_del, (void *)param);
	}
	return ret;
}
