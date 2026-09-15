#ifndef HAE_INET_SOCK_IOS_SSL_H
#define HAE_INET_SOCK_IOS_SSL_H

#include <hae_def.h>
#include <hae_inet_sock_ios.h>

typedef enum
{
	HAE_INET_SSL_SOCKET_IOS_SERVER = 1,
	HAE_INET_SSL_SOCKET_IOS_CLIENT
} HaeInetSSLSocketIOSMode;

ASMLINK HaeInetSocketIOS *haeInetSSLSockIos_new(HaeInetSSLSocketIOSMode mode, str_t server_req_name, str_t server_key_name,
																				str_t ciper_list, int *err);

#endif
