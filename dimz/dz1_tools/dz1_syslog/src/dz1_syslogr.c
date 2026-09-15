#include <codeconv.h>
#include <dz1_str.h>
#include "dz1_syslogr.h"

#ifndef UNIX_SYSTEM
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#endif

#if 0
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <WinBase.h>

#ifdef WIN32
#pragma warning(disable:4996)
#endif

#ifndef SYSLOG_CONF_DIR
static const char *syslog_conf_dir = ".";
#else
static const char *syslog_conf_dir = SYSLOG_CONF_DIR;
#endif

#define SYSLOG_DGRAM_SIZE	8192
#define MAX_IDENT_LENGTH	128
#define MAX_APP_NAME_LENGTH 48

static char UTF8_BOM[] = { 0xEF, 0xBB, 0xBF, '\0' };
//static char UTF8_BOM[] = {'\0'};

static BOOL				initialized = FALSE;
static int				log_mask = 0xFF;
static char				syslog_ident[MAX_IDENT_LENGTH];
static int				syslog_facility;
static char				str_pid[ 40 ];
static SOCKADDR_IN		sa_logger;
static SOCKET			sock;
static char				local_hostname[MAX_COMPUTERNAME_LENGTH + 1];
static int				datagramm_size;

static int				version = 1;
static char				app_name[MAX_APP_NAME_LENGTH];
static volatile LONG	mid = 0;

/******************************************************************************
* set_syslog_conf_dir
*
* maybe this function will be useful...
*/
const char *set_syslog_conf_dir(const char *dir)
{
	const char *ret = syslog_conf_dir;
	syslog_conf_dir = dir;
	return ret;
}

/******************************************************************************
* init_logger_addr
*
* Read configuration file syslog.host. This file should contain host address
* and, optionally, port. Initialize sa_logger. If the configuration file does
* not exist, use localhost:514.
* Returns: 0 - ok, -1 - error.
*/
static void init_logger_addr()
{
	char pathname[FILENAME_MAX];
	char *p;
	FILE *fd;
	char host[256];
	struct hostent * phe;

	/*
	UTF8_BOM[0] = (char)0xEF;
	UTF8_BOM[1] = (char)0xBB;
	UTF8_BOM[2] = (char)0xBF;
	UTF8_BOM[3] = '\0';
	*/

	memset(&sa_logger, 0, sizeof(SOCKADDR_IN));
	sa_logger.sin_family = AF_INET;

	if( '\\' == syslog_conf_dir[0] || '/' == syslog_conf_dir[0] || ':' == syslog_conf_dir[1] )
	{	// absolute path
		strcpy(pathname, syslog_conf_dir);
	}
	else
	{	/* relative path */
		char *q;

		strcpy( pathname, __argv[0] );
		p = strrchr(pathname, '\\') + 1;
		q = strrchr(pathname, '/' ) + 1;
		if (p < q)			*q = 0;			// q가 더 뒤면 q에서 끝
		else if(p > q)		*p = 0;			// p가 더 뒤면 p에서 끝
		else pathname[0] = 0;				// 둘 다 같으면 pathname을 비움

		strcat(pathname, syslog_conf_dir);
	}

	p = &pathname[strlen(pathname) - 1];
	if('\\' != *p && '/' != *p)
	{	// 끝이 Seprator가 아니면 추가
		p++; *p = '/';
	}
	strcpy( ++p, "syslog.host" );			// {path} + "syslog.host"

	/* read destination host name */
	// "syslog.gitsn.com:3335"
	if ((fd = fopen(pathname, "r")) == NULL) goto use_default;

	if(NULL == fgets(host, sizeof(host), fd)) host[0] = 0;
	else
	{
		if ((p = strchr(host, '\n')) != NULL) *p = 0;
		if ((p = strchr(host, '\r')) != NULL) *p = 0;
	}
	fclose( fd );

	if ((p = strchr(host, ':')) != NULL) *p++ = 0;

	if ((phe = gethostbyname(host)) == NULL) goto use_default;

	memcpy(&sa_logger.sin_addr.s_addr, phe->h_addr, phe->h_length);

	if(p) sa_logger.sin_port = htons( (unsigned short) strtoul( p, NULL, 0 ) );
	else sa_logger.sin_port = htons( SYSLOG_PORT );

	return;

use_default:
	sa_logger.sin_addr.S_un.S_addr = htonl( 0x7F000001 );	// 127.0.0.1
	sa_logger.sin_port = htons(SYSLOG_PORT);				// 514
}

void set_syslog_host(const char *host, u_short port) 
{
	struct hostent *phe = gethostbyname(host);
	if(phe == NULL)  return;

	memcpy( &sa_logger.sin_addr.s_addr, phe->h_addr, phe->h_length );
	sa_logger.sin_port = htons(port);
}

/******************************************************************************
* closelog
*
* Close desriptor used to write to system logger.
*/
void closelog(void)
{
	if( !initialized ) return;
	closesocket(sock);
	WSACleanup();
	initialized = FALSE;
}

/******************************************************************************
* openlog
*
* Open connection to system logger.
*/
void openlog(const char *ident, int option, int facility)
{
	BOOL failed = TRUE, wsa_initialized = FALSE;
	WSADATA wsd;
	SOCKADDR_IN sa_local;
	DWORD n;
	char exeFile[1024];
	int size;

	if (initialized) return;

	syslog_facility = facility ? facility : LOG_USER;

	/* FIXME: should we reset logmask? */

	if (option & LOG_PID) 
		_snprintf(str_pid, sizeof(str_pid), "%lu", GetCurrentProcessId());
	else str_pid[0] = 0;

	/* FIXME: handle other options */

	n = sizeof(local_hostname);
	if(!GetComputerName(local_hostname, &n)) goto done;					// 컴퓨터 이름

	if ((n = GetModuleFileName(NULL, exeFile, 1024)) > 0) 
	{
		while (--n) 
		{
			if (exeFile[n] == '\\' ) 
			{
				strncpy(app_name, &exeFile[n+1], MAX_APP_NAME_LENGTH);	// 실행파일 이름
				break;
			}
		}
	}

	sock = INVALID_SOCKET;
	if(WSAStartup(MAKEWORD( 2, 2 ), &wsd)) goto done;
	wsa_initialized = TRUE;

	init_logger_addr();				// {config_path} / syslog.host 에서 읽어서 주소 설정

	for(n = 0; ; n++)
	{
		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) goto done;

		memset(&sa_local, 0, sizeof(SOCKADDR_IN));
		sa_local.sin_family = AF_INET;
		if(bind(sock, (SOCKADDR *)&sa_local, sizeof(SOCKADDR_IN)) == 0) break;	// bind (0.0.0.0:0)

		closesocket(sock);
		sock = INVALID_SOCKET;

		if(n == 100) goto done;

		Sleep(0);
	}

	/* get size of datagramm */
	size = sizeof(datagramm_size);
	if (getsockopt(sock, SOL_SOCKET, SO_MAX_MSG_SIZE, (char *)&datagramm_size, &size))	goto done;	// SDU Size 읽어오기

	if (datagramm_size - strlen(local_hostname) - (ident? strlen(ident) : 0) < 64)		goto done;	// 컴퓨터 이름과 인식명을 뺀 자리가 64보다 작으면 실채

	if( datagramm_size > SYSLOG_DGRAM_SIZE) datagramm_size = SYSLOG_DGRAM_SIZE;

	if(atexit(closelog)) goto done;																	// Cleanup Callback

	strncpy(syslog_ident, ident, MAX_IDENT_LENGTH);													// 인식 명 보관

	syslog_facility = facility;
	failed = FALSE;

done:
	if(failed)
	{
		if(sock != INVALID_SOCKET) closesocket(sock);
		if(wsa_initialized) WSACleanup();
	}
	initialized = !failed;
}

/******************************************************************************
* setlogmask
*
* Set the log mask level.
*/
int setlogmask( int mask )
{
	int ret = log_mask;

	if( mask )
		log_mask = mask;
	return ret;
}

/******************************************************************************
* syslog
*
* Generate a log message using FMT string and option arguments.
*/
void syslog( int pri, char* fmt, ... )
{
	va_list ap;

	va_start( ap, fmt );
	vsyslog( pri, fmt, ap );
	va_end( ap );
}

/******************************************************************************
* vsyslog
*
* Generate a log message using FMT and using arguments pointed to by AP.
*/
static char *month[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
void vsyslog( int pri, char* fmt, va_list ap )
{
	SYSTEMTIME stm;
	int len;
	char *p;
	char datagramm[SYSLOG_DGRAM_SIZE];
	LONG current_mid = 0;
	char timestamp[128];

	if( !(LOG_MASK( LOG_PRI( pri )) & log_mask) )
		return;

	openlog( NULL, 0, pri & LOG_FACMASK );
	if( !initialized )
		return;

	if( !(pri & LOG_FACMASK) ) {
		pri |= syslog_facility;
	}

	current_mid = InterlockedIncrement(&mid);

	GetLocalTime( &stm );
	sprintf(timestamp, "%04d-%02d-%02dT%02d:%02d:%02d.%dZ", stm.wYear, stm.wMonth, stm.wDay, stm.wHour, 
		stm.wMinute, stm.wSecond, stm.wMilliseconds);

	//                          p  v  ts lh ap pd md  ?  bmid
	len = sprintf( datagramm, "<%d>%d %s %s %s %s %ld %s %s%s ",
								pri, version, timestamp, local_hostname, app_name, str_pid, current_mid, "", UTF8_BOM, syslog_ident);

	vsnprintf( datagramm + len, datagramm_size - len, fmt, ap );
	p = strchr( datagramm, '\n' );
	if( p )
		*p = 0;
	p = strchr( datagramm, '\r' );
	if( p )
		*p = 0;

	//printf("log: %s", datagramm);
	sendto( sock, datagramm, strlen(datagramm), 0, (SOCKADDR*) &sa_logger, sizeof(SOCKADDR_IN) );
}

/******************************************************************************
* test
*/
#ifdef TEST

static HANDLE hRxEvent = NULL, hAckEvent = NULL;
static SOCKET rxsock = INVALID_SOCKET;
static char buffer[ sizeof(datagramm)+1 ];

static DWORD WINAPI listener( LPVOID param )
{
	for(;;)
	{
		int ret;

		WaitForSingleObject( hAckEvent, INFINITE );
		ret = recv( rxsock, buffer, sizeof(datagramm), 0 );
		if( ret <= 0 )
			break;
		buffer[ ret ] = 0;
		SetEvent( hRxEvent );
	}
	return 0;
}

static int transact( int pri, char* fmt, ... )
{
	va_list ap;
	DWORD r;

	va_start( ap, fmt );
	vsyslog( pri, fmt, ap );
	va_end( ap );
	r = WaitForSingleObject( hRxEvent, 2000 );
	if( WAIT_TIMEOUT == r )
	{
		fprintf( stderr, "timeout\n" );
		return -1;
	}
	if( WAIT_FAILED == r )
	{
		fprintf( stderr, "wait failed, error %lu\n", GetLastError() );
		return -1;
	}
	printf( "*** %s\n", buffer );
	SetEvent( hAckEvent );
	return 0;
}

int main( int argc, char* argv[] )
{
	int ret = 1;
	WSADATA wsd;
	SOCKADDR_IN sa_local;
	DWORD tid;
	HANDLE hThread = NULL;

	if( WSAStartup( MAKEWORD( 2, 2 ), &wsd ) )
	{
		fprintf( stderr, "WSAStartup() failed, error %d\n", WSAGetLastError() );
		return 1;
	}

	hRxEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	if( !hRxEvent )
	{
		fprintf( stderr, "CreateEvent() failed, error %lu\n", GetLastError() );
		goto done;
	}

	hAckEvent = CreateEvent( NULL, FALSE, TRUE, NULL );
	if( !hAckEvent )
	{
		fprintf( stderr, "CreateEvent() failed, error %lu\n", GetLastError() );
		goto done;
	}

	rxsock = socket( AF_INET, SOCK_DGRAM, 0 );
	if( INVALID_SOCKET == sock )
	{
		fprintf( stderr, "socket() failed, error %d\n", WSAGetLastError() );
		goto done;
	}

	memset( &sa_local, 0, sizeof(SOCKADDR_IN) );
	sa_local.sin_family = AF_INET;
	sa_local.sin_addr.S_un.S_addr = htonl( 0x7F000001 );
	sa_local.sin_port = htons( SYSLOG_PORT );
	if( bind( rxsock, (SOCKADDR*) &sa_local, sizeof(SOCKADDR_IN) ) )
	{
		fprintf( stderr, "bind() failed, error %d\n", WSAGetLastError() );
		goto done;
	}

	hThread = CreateThread( NULL, 0, listener, NULL, 0, &tid );
	if( !hThread )
	{
		fprintf( stderr, "CreateThread() failed, error %lu\n", GetLastError() );
		goto done;
	}

	openlog( "test_ident", 0, LOG_USER );
	if( !initialized )
	{
		fprintf( stderr, "openlog() failed\n" );
		goto done;
	}

	if( transact( LOG_DEBUG, "test message %d", 1 ) )
		goto done;

	setlogmask( LOG_MASK( LOG_EMERG ) );

	if( !transact( LOG_DEBUG, "test message %d", 2 ) )
		goto done;

	if( transact( LOG_EMERG, "test message %d", 3 ) )
		goto done;

	closelog();
	openlog( "test_ident", LOG_PID, LOG_USER );
	if( !initialized )
	{
		fprintf( stderr, "openlog() failed\n" );
		goto done;
	}

	setlogmask( LOG_MASK( LOG_DEBUG ) );

	if( transact( LOG_DEBUG, "test message %d with pid", 4 ) )
		goto done;

	if( transact( LOG_DEBUG, "long test message %d 1234567890 1234567890 1234567890 1234567890 1234567890", 5 ) )
		goto done;

	ret = 0;

done:
	if( rxsock != INVALID_SOCKET ) closesocket( rxsock );
	if( hAckEvent )
	{
		if( hThread )
		{
			SetEvent( hAckEvent );
			puts( "waiting for thread shutdown" );
			WaitForSingleObject( hThread, INFINITE );
		}
		CloseHandle( hAckEvent );
	}
	if( hThread ) CloseHandle( hThread );
	if( hRxEvent ) CloseHandle( hRxEvent );
	WSACleanup();
	return 0;
}

#endif /* TEST */
#endif

///////////////////////////////////////////////////////////////////////////////
// PID String
static bool_t _get_pid_strA(char *dst, size_t sz, Dz1Error *errp)
{
	u32_t pid = 0;
#ifndef UNIX_SYSTEM
	pid = (u32_t)GetCurrentProcessId();
#else
	pid = (u32_t)getpid();
#endif
	if (Dz1StrA_fromU32(dst, sz, pid) < 0) ERR_SET_OUT(errp, EINVAL);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
static bool_t _get_pid_strW(wchar_t *dst, size_t sz, Dz1Error *errp)
{
	u32_t pid = 0;
	pid = (u32_t)GetCurrentProcessId();
	if (Dz1StrW_fromU32(dst, sz, pid) < 0) ERR_SET_OUT(errp, EINVAL);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
#endif
// PID String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Name
static bool_t _get_system_nameA(char *dst, size_t sz, Dz1Error *errp)
{
#ifndef UNIX_SYSTEM
	DWORD n = (DWORD)sz;
	if(GetComputerNameA(dst, &n) == 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
#else
	ERR_SET_OUT(errp, ENOSYS);
#endif
	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
static bool_t _get_system_nameW(wchar_t *dst, size_t sz, Dz1Error *errp)
{
	DWORD n = (DWORD)sz;
	if(GetComputerNameW(dst, &n) == 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
#endif
// System Name
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// App Name
static bool_t _get_app_nameA(char *dst, size_t sz, Dz1Error *errp)
{
	char exeFile[1024];
#ifndef UNIX_SYSTEM
	DWORD n = (DWORD)sz;
	if ((n = GetModuleFileNameA(NULL, exeFile, 1024)) == 0) ERR_SET_OUT(errp, GetLastError());
#else
#ifdef LINUX
	ssize_t n = readlink("/proc/self/exe", exeFile, 1024);
	if (n < 0) ERR_SET_OUT(errp, errno);
#else
	if (1) ERR_SET_OUT(errp, ENOSYS);
#endif
#endif
	else
	{
		while (--n) 
		{
			if (exeFile[n] == '\\' ) 
			{
				strncpy(dst, &exeFile[n + 1], sz);	// 실행파일 이름
				break;
			}
		}

		if (dst[0] == 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
static bool_t _get_app_nameW(wchar_t *dst, size_t sz, Dz1Error *errp)
{
	wchar_t exeFile[1024];
	DWORD n = (DWORD)sz;
	if ((n = GetModuleFileNameW(NULL, exeFile, 1024)) == 0) ERR_SET_OUT(errp, GetLastError());
	else
	{
		while (--n) 
		{
			if (exeFile[n] == L'\\' ) 
			{
				wcsncpy(dst, &exeFile[n + 1], sz);	// 실행파일 이름
				break;
			}
		}

		if (dst[0] == 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif
// App Name
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Peer SockAddr
static bool_t _set_peer_sockA(Dz1SockAddr *dst, char *url, u16_t port, Dz1Error *errp)
{
	if ((*errp = Dz1SockAddr_setAddrS(dst, url)).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(dst, port)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
static bool_t _set_peer_sockW(Dz1SockAddr *dst, wchar_t *url, u16_t port, Dz1Error *errp)
{
	Dz1Str url_u8 = (Dz1Str)Dz1String_conv(url, wcslen(url) * sizeof(TCHAR), WINDOWS_UNICODE, "UTF-8", NULL);
	if (url_u8 = NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&url_u8);
		if (url_u8[0] == 0) ERR_SET_OUT(errp, EINVAL);
		else if (_set_peer_sockA(dst, url_u8, port, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&url_u8);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif
// Peer SockAddr
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Socket Opt
static bool_t _socket_option_set(Dz1UdpSocket *sock, Dz1Error *errp)
{
	/* get size of datagramm 
	size = sizeof(datagramm_size);
	if (getsockopt(sock, SOL_SOCKET, SO_MAX_MSG_SIZE, (char *)&datagramm_size, &size))	goto done;	// SDU Size 읽어오기
	if (datagramm_size - strlen(local_hostname) - (ident? strlen(ident) : 0) < 64)		goto done;	// 컴퓨터 이름과 인식명을 뺀 자리가 64보다 작으면 실패
	if( datagramm_size > SYSLOG_DGRAM_SIZE) datagramm_size = SYSLOG_DGRAM_SIZE;
	*/
	return errp->code == 0 ? TRUE : FALSE;
}
// Socket Opt
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SyslogR new
Dz1SyslogRA *Dz1SyslogR_newA(char *url, u16_t port, u32_t facilitiy, u32_t priority_flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SyslogRA *ret = (Dz1SyslogRA *)Dz1Calloc(sizeof(Dz1SyslogRA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SyslogR_delAndSetNullA, (void *)&ret);
		pthread_mutex_init(&ret->lock, NULL);
		if (_get_pid_strA(ret->str_pid, DZ1_SYSLOGR_PID_SIZE, errp) == FALSE) ERR_OUT(errp);
		else if (_get_system_nameA(ret->sys_name, DZ1_SYSLOGR_SYSNAME_SIZE + 1, errp) == FALSE) ERR_OUT(errp);
		else if (_get_app_nameA(ret->app_name, DZ1_SYSLOGR_APPNAME_SIZE, errp) == FALSE) ERR_OUT(errp);
		else if (_set_peer_sockA(&ret->peer, url, port, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setAddrStr(&ret->local, "0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&ret->local, 0)).code) ERR_OUT(errp);
		else
		{
			ret->facilitiy = facilitiy ? facilitiy : DZ1_SYSLOGR_F_USER;
			ret->priority_flag = priority_flag ? priority_flag : DZ1_SYSLOGR_PF_ALL;

			if ((ret->sock = Dz1UdpSocket_open(&ret->peer, &ret->local, NULL, errp)) == NULL) ERR_OUT(errp);
			else if (_socket_option_set(ret->sock, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SyslogR_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
Dz1SyslogRW *Dz1SyslogR_newW(wchar_t *url, u16_t port, u32_t facilitiy, u32_t priority_flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SyslogRW *ret = (Dz1SyslogRW *)Dz1Calloc(sizeof(Dz1SyslogRW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SyslogR_delAndSetNullW, (void *)&ret);
		pthread_mutex_init(&ret->lock, NULL);
		if (_get_pid_strW(ret->str_pid, DZ1_SYSLOGR_PID_SIZE, errp) == FALSE) ERR_OUT(errp);
		else if (_get_system_nameW(ret->sys_name, DZ1_SYSLOGR_SYSNAME_SIZE + 1, errp) == FALSE) ERR_OUT(errp);
		else if (_get_app_nameW(ret->app_name, DZ1_SYSLOGR_APPNAME_SIZE, errp) == FALSE) ERR_OUT(errp);
		else if (_set_peer_sockW(&ret->peer, url, port, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setAddrStr(&ret->local, "0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&ret->local, 0)).code) ERR_OUT(errp);
		else
		{
			ret->facilitiy = facilitiy ? facilitiy : DZ1_SYSLOGR_F_USER;
			ret->priority_flag = priority_flag ? priority_flag : DZ1_SYSLOGR_PF_ALL;
			if ((ret->sock = Dz1UdpSocket_open(&ret->peer, &ret->local, NULL, errp)) == NULL) ERR_OUT(errp);
			else if (_socket_option_set(ret->sock, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SyslogR_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif
// Dz1SyslogR new
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SyslogR del
void Dz1SyslogR_delA(Dz1SyslogRA *p)
{
	if (p != NULL) 
	{
		pthread_mutex_lock(&p->lock);

		if (p->sock != NULL) 
			Dz1UdpSocket_closeAndSetNull(&p->sock);

		pthread_mutex_unlock(&p->lock);
		pthread_mutex_destroy(&p->lock);
		Dz1Free(p);
	}
}
#ifndef UNIX_SYSTEM
void Dz1SyslogR_delW(Dz1SyslogRW *p)
{
	if (p != NULL) Dz1SyslogR_delA((Dz1SyslogRA *)p);
}
#endif
// Dz1SyslogR del
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SyslogR_dump
void Dz1SyslogR_dumpA(Dz1SyslogRA *p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else
	{
		pthread_mutex_lock(&p->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
		Dz1Thread_printf("{\n"); tab++;
		Dz1Thread_tprintf(tab, "sock = %p\n", p->sock);
		Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(&p->peer, 0);
		Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(&p->local, 0);
		Dz1Thread_tprintf(tab, "facilitiy = %08X\n", p->facilitiy);
		Dz1Thread_tprintf(tab, "periority_flag = %08X\n", p->priority_flag);
		Dz1Thread_tprintf(tab, "pid = "); Dz1StrA_dump(p->str_pid, 0);
		Dz1Thread_tprintf(tab, "sys_name = "); Dz1StrA_dump(p->sys_name, 0);
		Dz1Thread_tprintf(tab, "app_name = "); Dz1StrA_dump(p->app_name, 0);
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}
}
#ifndef UNIX_SYSTEM
void Dz1SyslogR_dumpW(Dz1SyslogRW *p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else
	{
		pthread_mutex_lock(&p->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
		Dz1Thread_printf("{\n"); tab++;
		Dz1Thread_tprintf(tab, "sock = %p\n", p->sock);
		Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(&p->peer, 0);
		Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(&p->local, 0);
		Dz1Thread_tprintf(tab, "facilitiy = %08X\n", p->facilitiy);
		Dz1Thread_tprintf(tab, "periority_flag = %08X\n", p->priority_flag);
		Dz1Thread_tprintf(tab, "pid = "); Dz1StrW_dump(p->str_pid, 0);
		Dz1Thread_tprintf(tab, "sys_name = "); Dz1StrW_dump(p->sys_name, 0);
		Dz1Thread_tprintf(tab, "app_name = "); Dz1StrW_dump(p->app_name, 0);
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}
}
#endif
// Dz1SyslogR_dump
///////////////////////////////////////////////////////////////////////////////

static char DZ1_SYSLOGR_UTF8_BOM[] = { 0xEF, 0xBB, 0xBF, '\0' };

#define	DZ1_SYSLOGR_PRI_MASK				0x07								// lower 3bit = priority
#define	DZ1_SYSLOGR_PRI_GET(priv)			((priv) & DZ1_SYSLOGR_PRI_MASK)		// extract priority from log_attr

#define	DZ1_SYSLOGR_PRI_V2BIT(priv)			(1 << (priv))						// priority value to priority flag

#define	DZ1_SYSLOGR_FAC_MASK				0x03f8								// mask to extract facility part

static ssize_t _get_time_stringA(char *buf, size_t sz, Dz1Error *err)
{	// day month year
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = -1;

	time_t tNow = time(NULL);
	Dz1TimeVal tvNow = Dz1TimeVal_get();
	struct tm *tm_p = localtime(&tNow);
	if (tm_p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		struct tm tmNow = *tm_p;
		int offset_s = Dz1Time_GetGmtOffset();
		int offset = offset_s / 60;
		char sign = offset >= 0 ? '+' : '-';
		int abs_offset = offset < 0 ? -offset : offset;
		int offset_h = abs_offset / 60;
		int offset_m = abs_offset % 60;
		ret = snprintf(buf, sz, "%04d-%02d-%02dT%02d:%02d:%02d.%03u%c%02d:%02d",
								tmNow.tm_year + 1900,
								tmNow.tm_mon + 1,
								tmNow.tm_mday,
								tmNow.tm_hour, 
								tmNow.tm_min, 
								tmNow.tm_sec, 
								(u32_t)(tvNow.tv_usec / 1000),
								sign,
								offset_h,
								offset_m);
		Dz1Error_set(errp, 0);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
static ssize_t _get_time_stringW(wchar_t *buf, size_t sz, Dz1Error *err)
{	// day month year
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = -1;

	time_t tNow = time(NULL);
	Dz1TimeVal tvNow = Dz1TimeVal_get();
	struct tm *tm_p = localtime(&tNow);
	if (tm_p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		struct tm tmNow = *tm_p;
		int offset_s = Dz1Time_GetGmtOffset();
		int offset = offset_s / 60;
		wchar_t sign = offset >= 0 ? L'+' : L'-';
		int abs_offset = offset < 0 ? -offset : offset;
		int offset_h = abs_offset / 60;
		int offset_m = abs_offset % 60;
		ret = wnsprintfW(buf, (int)sz, L"%04d-%02d-%02dT%02d:%02d:%02d.%03u%c%02d:%02d",
									tmNow.tm_year + 1900,
									tmNow.tm_mon + 1,
									tmNow.tm_mday,
									tmNow.tm_hour, 
									tmNow.tm_min, 
									tmNow.tm_sec, 
									tvNow.tv_usec / 1000,
									sign,
									offset_h,
									offset_m);
		Dz1Error_set(errp, 0);
	}
	return ret;
}
#endif
typedef struct Dz1SyslogPriMapA
{
	Dz1SyslogPri	 v;
	char			*str;
} Dz1SyslogPriMapA;

static Dz1SyslogPriMapA dz1SyslogPriMapA[] =
{
	{ Dz1SyslogPri_EMERG,	"emerg" },
	{ Dz1SyslogPri_ALERT,	"alert" },
	{ Dz1SyslogPri_CRIT,	"crit" },
	{ Dz1SyslogPri_ERR,		"err" },
	{ Dz1SyslogPri_WARNING,	"warning" },
	{ Dz1SyslogPri_NOTICE,	"notice" },
	{ Dz1SyslogPri_INFO,	"info" },
	{ Dz1SyslogPri_DEBUG,	"debug" },
	{ Dz1SyslogPri_max,		NULL }
};

char *Dz1SyslogPriToStrA(Dz1SyslogPri v)
{
	Dz1SyslogPriMapA *i;
	for (i = dz1SyslogPriMapA; i->v != Dz1SyslogPri_max; i++)
		if (i->v == v) break;
	return i->str;
}

Dz1SyslogPri Dz1SyslogPriFromStrA(char *str)
{
	Dz1SyslogPriMapA *i;
	for (i = dz1SyslogPriMapA; i->v != Dz1SyslogPri_max; i++)
		if (strcmp(i->str, str) == 0) break;
	return i->v;
}

#ifndef UNIX_SYSTEM
typedef struct Dz1SyslogPriMapW
{
	Dz1SyslogPri	 v;
	wchar_t			*str;
} Dz1SyslogPriMapW;

static Dz1SyslogPriMapW dz1SyslogPriMapW[] =
{
	{ Dz1SyslogPri_EMERG,	L"emerg" },
	{ Dz1SyslogPri_ALERT,	L"alert" },
	{ Dz1SyslogPri_CRIT,	L"crit" },
	{ Dz1SyslogPri_ERR,		L"err" },
	{ Dz1SyslogPri_WARNING,	L"warning" },
	{ Dz1SyslogPri_NOTICE,	L"notice" },
	{ Dz1SyslogPri_INFO,	L"info" },
	{ Dz1SyslogPri_DEBUG,	L"debug" },
	{ Dz1SyslogPri_max,		NULL }
};

wchar_t *Dz1SyslogPriMapToStrW(Dz1SyslogPri v)
{
	Dz1SyslogPriMapW *i;
	for (i = dz1SyslogPriMapW; i->v != Dz1SyslogPri_max; i++)
		if (i->v == v) break;
	return i->str;
}

Dz1SyslogPri Dz1SyslogPriMapFromStrW(wchar_t *str)
{
	Dz1SyslogPriMapW *i;
	for (i = dz1SyslogPriMapW; i->v != Dz1SyslogPri_max; i++)
		if (wcscmp(i->str, str) == 0) break;
	return i->v;
}
#endif

bool_t Dz1SyslogR_vlogA(Dz1SyslogRA *dst, Dz1SyslogPri priority, char *fmt, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(fmt) == TRUE) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char *temp = NULL;
		pthread_mutex_lock(&dst->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dst->lock);

		if (dst->sock == NULL) ERR_SET_OUT(errp, ENOSYS);
		else if ((DZ1_SYSLOGR_PRI_V2BIT(DZ1_SYSLOGR_PRI_GET(priority)) & dst->priority_flag) == 0) Dz1Error_set(errp, 0);		// no match no log
		else if ((temp = (char *)Dz1Calloc(sizeof(char), 8192, errp)) == NULL) ERR_OUT(errp);									// make temp buffer 8K of char
		else
		{
			int version = 1;
			char *c = NULL;

			u8_t *dp = dst->buf;	// destination buffer
			size_t dp_sz = 8192;

			char *tp = temp;
			size_t sz = 8192, len;
			size_t hdr_len = 0, txt_len = 0, tx_len = 0;

			pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
			len = snprintf(tp, sz, "<%d>%d ", dst->facilitiy | priority, version);												// make header to temp buffer
			tp += len;
			sz -= len;

			if ((len = _get_time_stringA(tp, sz, errp)) < 0) ERR_OUT(errp);														// append time_str to temp buffer
			else
			{
				tp += len; 
				sz -= len;

				len = snprintf(tp, sz, " %s %s %s - ", dst->sys_name, dst->app_name, dst->str_pid);								// append process info to temp buffer
				tp += len;	
				sz -= len;

				// Header
				hdr_len = Dz1CodeConv(dp, dp_sz, "UTF-8", (u8_t *)temp, (size_t)(tp - temp) * sizeof(char), OS_MBCS_CHARSET);	// put temp to destination buffer
				dp += hdr_len; 
				dp_sz -= hdr_len;

				/*
				// BOM
				strcpy(dp, DZ1_SYSLOGR_UTF8_BOM);																				// append UTF-8 BOM
				dp += 3;
				dp_sz -= 3;
				*/

				tp = temp;
				sz = 8192;
				len = vsnprintf(tp, sz, fmt, ap);																				// make context to temp buffer
				tp += len;
				sz -= len;

				// Context
				txt_len = Dz1CodeConv(dp, dp_sz, "UTF-8", (u8_t *)temp, (size_t)(tp - temp) * sizeof(char), OS_MBCS_CHARSET);// convert from temp to UTF-8 destination
				dp += txt_len;
				dp_sz -= txt_len;

				// BOM
				strcpy((char *)dp, DZ1_SYSLOGR_UTF8_BOM);																				// append UTF-8 BOM
				dp += 3;
				dp_sz -= 3;

				*dp = 0;

				while ((c = strrchr((char *)dst->buf, '\n')) != NULL) *c = 0;
				while ((c = strrchr((char *)dst->buf, '\r')) != NULL) *c = 0;
				
//				Dz1Thread_printf("Dz1SyslogR : "); Dz1StrA_dump(dst->buf, 0);

				tx_len = hdr_len + 3 + txt_len;
				if (tx_len > 8192) tx_len = 8192;

				if (dst->sock->send(dst->sock, &dst->peer, dst->buf, tx_len, DZ1_UDP_SOCK_FLAG_COMPLETE, NULL, errp) < 0) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
		}
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dst->lock);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1SyslogR_logA(Dz1SyslogRA *dst, Dz1SyslogPri priority, char *fmt, ...)
{
	bool_t ret = FALSE;
	va_list ap;

	va_start( ap, fmt );
	ret = Dz1SyslogR_vlogA(dst, priority, fmt, ap);
	va_end( ap );

	return ret;
}

#ifndef UNIX_SYSTEM
bool_t Dz1SyslogR_vlogW(Dz1SyslogRW *dst, Dz1SyslogPri priority, wchar_t *fmt, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(fmt) == TRUE) ERR_SET_OUT(errp, EINVAL);
	else
	{
		wchar_t *temp = NULL;
		pthread_mutex_lock(&dst->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dst->lock);

		if (dst->sock == NULL) ERR_SET_OUT(errp, ENOSYS);
		else if ((DZ1_SYSLOGR_PRI_V2BIT(DZ1_SYSLOGR_PRI_GET(priority)) & dst->priority_flag) == 0) Dz1Error_set(errp, 0);		// no match no log
		else if ((temp = (wchar_t *)Dz1Calloc(sizeof(wchar_t), 8192, errp)) == NULL) ERR_OUT(errp);								// make temp buffer 8K wchar_t
		else
		{
			int version = 1;
			char *c = NULL;

			u8_t *dp = dst->buf;	// destination buffer
			size_t dp_sz = 8192;

			wchar_t *tp = temp;
			size_t sz = 8192, len;

			size_t hdr_len = 0, txt_len = 0, tx_len = 0;

			pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
			len = _snwprintf(tp, sz, L"<%d>%d ", dst->facilitiy | priority, version);											// make header to temp buffer
			tp += len;
			sz -= len;

			if ((len = _get_time_stringW(tp, sz, errp)) < 0) ERR_OUT(errp);														// append time_str to temp buffer
			else
			{
				tp += len; 
				sz -= len;

				len = _snwprintf(tp, sz, L" %s %s %s - ", dst->sys_name, dst->app_name, dst->str_pid);							// append process info to temp buffer
				tp += len; 
				sz -= len;

				// Header
				hdr_len = Dz1CodeConv(dp, dp_sz, "UTF-8", (u8_t *)temp, (size_t)(tp - temp) * sizeof(wchar_t), OS_WIDE_CHARSET);// put temp to destination buffer
				dp += hdr_len; 
				dp_sz -= hdr_len;

				/*
				// BOM
				strcpy(dp, DZ1_SYSLOGR_UTF8_BOM);																				// append UTF-8 BOM
				dp += 3;
				dp_sz -= 3;
				*/

				tp = temp;
				sz = 8192;
				len = _vsnwprintf(tp, sz, fmt, ap);																				// make context to temp buffer
				tp += len;
				sz -= len;

				// Context
				txt_len = Dz1CodeConv(dp, dp_sz, "UTF-8", (u8_t *)temp, (size_t)(tp - temp) * sizeof(wchar_t), OS_WIDE_CHARSET);// convert from temp to UTF-8 destination
				dp += txt_len;
				dp_sz -= txt_len;

				// BOM
				strcpy(dp, DZ1_SYSLOGR_UTF8_BOM);																				// append UTF-8 BOM
				dp += 3;
				dp_sz -= 3;

				*dp = 0;

				while ((c = strrchr(dst->buf, '\n')) != NULL) *c = 0;
				while ((c = strrchr(dst->buf, '\r')) != NULL) *c = 0;
				
//				Dz1Thread_printf("Dz1SyslogR : "); Dz1StrA_dump(dst->buf, 0);

				tx_len = hdr_len + 3 + txt_len;
				if (tx_len > 8192) tx_len = 8192;

				if (dst->sock->send(dst->sock, &dst->peer, dst->buf, tx_len, DZ1_UDP_SOCK_FLAG_COMPLETE, NULL, errp) < 0) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
		}
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dst->lock);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1SyslogR_logW(Dz1SyslogRW *dst, Dz1SyslogPri priority, wchar_t *fmt, ...)
{
	bool_t ret = FALSE;
	va_list ap;

	va_start( ap, fmt );
	ret = Dz1SyslogR_vlogW(dst, priority, fmt, ap);
	va_end( ap );

	return ret;
}
#endif
