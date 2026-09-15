#ifndef DZ1_SOCKET_SSL_H
#define DZ1_SOCKET_SSL_H

#include <dz1_socket_ssl_def.h>
#include <dz1_socket_callback.h>
#include <Dz1SockUtil.h>

#include <openssl/opensslv.h>

#ifndef UNIX_SYSTEM
#if OPENSSL_VERSION_NUMBER <= 0x009080efL
///////////////////////////////////////////////
// OpenSSL 0.9.8
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
// OpenSSL 0.9.8
///////////////////////////////////////////////
#elif OPENSSL_VERSION_NUMBER == 0x1010111fL
///////////////////////////////////////////////
// OpenSSL 1.1.1q
#if _MSC_VER <= 1500

#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libssl.lib")
#else // _MSC_VER
#if __WORDSIZE == 32
#	if defined(_DEBUG)
#		if defined(_DLL)	//	/MDd
#pragma comment(lib, "libcrypto32MDd.lib")
#pragma comment(lib, "libssl32MDd.lib")
#		else // _DLL			/MTd
#pragma comment(lib, "libcrypto32MTd.lib")
#pragma comment(lib, "libssl32MTd.lib")
#		endif // _DLL
#	elif defined(NDEBUG)
#		if defined(_DLL)		/MD
#pragma comment(lib, "libcrypto32MD.lib")
#pragma comment(lib, "libssl32MD.lib")
#		else // _DLL			/MT
#pragma comment(lib, "libcrypto32MT.lib")
#pragma comment(lib, "libssl32MT.lib")
#		endif // _DLL
#	endif // _DEBUG, NDEBUG
#elif __WORDSIZE == 64
#	if defined(_DEBUG)
#		if defined(_DLL)	//	/MDd
#pragma comment(lib, "libcrypto64MDd.lib")
#pragma comment(lib, "libssl64MDd.lib")
#		else // _DLL			/MTd
#pragma comment(lib, "libcrypto64MTd.lib")
#pragma comment(lib, "libssl64MTd.lib")
#		endif // _DLL
#	elif defined(NDEBUG)
#		if defined(_DLL)	//	/MD
#pragma comment(lib, "libcrypto64MD.lib")
#pragma comment(lib, "libssl64MD.lib")
#		else // _DLL			/MT
#pragma comment(lib, "libcrypto64MT.lib")
#pragma comment(lib, "libssl64MT.lib")
#		endif // _DLL
#	endif // _DEBUG, NDEBUG
#endif // __WORDSIZE
#endif // _MSC_VER

#pragma comment(lib, "ADVAPI32.lib")
#pragma comment(lib, "CRYPT32.lib")
#pragma comment(lib, "USER32.lib")
// OpenSSL 1.1.1q
///////////////////////////////////////////////
#else // OPENSSL_VERSION_NUMBER
///////////////////////////////////////////////
// OpenSSL
#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "ADVAPI32.lib")
#pragma comment(lib, "CRYPT32.lib")
#pragma comment(lib, "USER32.lib")
// OpenSSL
///////////////////////////////////////////////
#endif
#endif // UNIX_SYSTEM

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/engine.h>

#include <dz1_bin.h>

#define DZ1_SSL_DEFAULT_CIPHER_LIST		"AES:ALL:!aNULL:!eNULL:+RC4:@STRENGTH" /* low priority for RC4 */

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SocketCallback2SSL_init(void);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1SocketCallback2SSL_clean(void);
static __inline__ void				 Dz1SocketCallback2SSL_initCancel(void *ptr)
{
	Dz1SocketCallback2SSL_clean();
}

typedef enum Dz1SocketCallback2SSLVer
{
//	Dz1SocketCallback2SSLVer_2,
//	Dz1SocketCallback2SSLVer_3,
	Dz1SocketCallback2SSLVer_23
} Dz1SocketCallback2SSLVer;

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SocketCallback2SSL_assoServer(Dz1TcpClientSocket *sock,
																  Dz1SockAddr *peer, Dz1SockAddr *local, u32_t rx_buf_size,
																  Dz1SocketCallback2Rcvd rx_cb, 
																  Dz1SocketCallback2Sent tx_cb,
																  void **user_ptr, Dz1DelFunc user_ptr_del,
																  Dz1SocketCallback2SSLVer ssl_ver, str_t certName, str_t keyName);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SocketCallback2SSL_assoClient(Dz1TcpClientSocket *sock,
																  Dz1SockAddr *peer, Dz1SockAddr *local, u32_t rx_buf_size,
																  Dz1SocketCallback2Rcvd rx_cb, 
																  Dz1SocketCallback2Sent tx_cb,
																  void **user_ptr, Dz1DelFunc user_ptr_del,
																  Dz1SocketCallback2SSLVer ssl_ver, str_t cyper_str);

///////////////////////////////////////////////////////////////////////////////
// Callback Mode TCP Socket for TASK that
// Socket Recognized by Socket Address
// Calling TASK will received followed Message Type
// ----------------------------------------------------------------------------
// DZ1_SOCK_UTIL_RECEIVER_RECEIVED(Dz1SockUtilReceiverReceived)
// DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED(Dz1SockUtilReceiverReceived)
// DZ1_SOCK_UTIL_TRANSMITER_SENT(Dz1SockUtilTransmiterSent)
// ----------------------------------------------------------------------------
DZ1_CPPLINK Dz1Error Dz1SockUtilTcpClient_modeSSLServer(Dz1TcpClientSocket *sock,
														Dz1SockAddr *peer, Dz1SockAddr *local,
														u32_t buf_size, // Dz1TcpClientSocketSSLServerMode mode,
														Dz1SocketCallback2SSLVer mode,
														str_t certName, str_t keyName, u32_t parentTaskQueueID);

DZ1_CPPLINK Dz1Error Dz1SockUtilTcpClient_modeSSLClient(Dz1TcpClientSocket *sock,
														Dz1SockAddr *peer, Dz1SockAddr *local,
														u32_t buf_size, // Dz1TcpClientSocketSSLClientMode mode,
														Dz1SocketCallback2SSLVer mode,
														str_t ciper_list, u32_t parentTaskQueueID);

///////////////////////////////////////////////////////////////////////////////
// Callback Mode TCP Socket Receiver for TASK that
// Socket Recognized by Session ID
// Calling TASK will received followed Message Type
// ----------------------------------------------------------------------------
// DZ1_SOCK_UTIL_RECEIVER2_RECEIVED(Dz1SockUtilReceiver2Received)
// DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED(Dz1SockUtilReceiver2Received)
// DZ1_SOCK_UTIL_TRANSMITER2_SENT(Dz1SockUtilTransmiter2Sent)
// ----------------------------------------------------------------------------
DZ1_CPPLINK Dz1Error Dz1SockUtilTcpClient_mode2SSLServer(u32_t sessionID,
														 Dz1TcpClientSocket *sock,
														 Dz1SockAddr *peer, Dz1SockAddr *local,
														 u32_t buf_size, // Dz1TcpClientSocketSSLServerMode mode,
														 Dz1SocketCallback2SSLVer mode,
														 str_t certName, str_t keyName, u32_t parentTaskQueueID);

DZ1_CPPLINK Dz1Error Dz1SockUtilTcpClient_mode2SSLClient(u32_t sessionID,
														 Dz1TcpClientSocket *sock,
														 Dz1SockAddr *peer, Dz1SockAddr *local,
														 u32_t buf_size, // Dz1TcpClientSocketSSLClientMode mode,
														 Dz1SocketCallback2SSLVer mode,
														 str_t ciper_list, u32_t parentTaskQueueID);

#endif
