#ifndef _DZ1_TDC_GITSN_DSRC_EMULATOR_ENV_H_
#define _DZ1_TDC_GITSN_DSRC_EMULATOR_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDsrcEmulatorDef.h"
#include "Dz1SockUtilDef.h"
#include "Dz1JsonDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorClientSession
typedef struct GitsnDsrcEmulatorClientSession
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} GitsnDsrcEmulatorClientSession;

DZ1_CPPLINK DZ1_DLLPORT GitsnDsrcEmulatorClientSession *GitsnDsrcEmulatorClientSession_new(Dz1SockAddr *peer, 
																						   Dz1SockAddr *local, 
																						   Dz1TcpClientSocket *sock, 
																						   Dz1ElasticBuf *rx_buf, 
																						   Dz1Stream *rx_stream, 
																						   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ GitsnDsrcEmulatorClientSession *GitsnDsrcEmulatorClientSession_gen(Dz1Error *err) { return GitsnDsrcEmulatorClientSession_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorClientSession_purge(GitsnDsrcEmulatorClientSession *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorClientSession_del(GitsnDsrcEmulatorClientSession *p);
static __inline__ void GitsnDsrcEmulatorClientSession_delAndSetNull(void *ptr)
{
	GitsnDsrcEmulatorClientSession **p = (GitsnDsrcEmulatorClientSession **)ptr;
	if (p) { GitsnDsrcEmulatorClientSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorClientSession_dump(GitsnDsrcEmulatorClientSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnDsrcEmulatorClientSession_cmp(GitsnDsrcEmulatorClientSession *a, GitsnDsrcEmulatorClientSession *b); 
// GitsnDsrcEmulatorClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorServerSession
typedef struct GitsnDsrcEmulatorServerSession
{
	u32_t					 acceptor;
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} GitsnDsrcEmulatorServerSession;

DZ1_CPPLINK DZ1_DLLPORT GitsnDsrcEmulatorServerSession *GitsnDsrcEmulatorServerSession_new(u32_t acceptor, 
																						   Dz1SockAddr *peer, 
																						   Dz1SockAddr *local, 
																						   Dz1TcpClientSocket *sock, 
																						   Dz1ElasticBuf *rx_buf, 
																						   Dz1Stream *rx_stream, 
																						   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ GitsnDsrcEmulatorServerSession *GitsnDsrcEmulatorServerSession_gen(Dz1Error *err) { return GitsnDsrcEmulatorServerSession_new(0, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorServerSession_purge(GitsnDsrcEmulatorServerSession *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorServerSession_del(GitsnDsrcEmulatorServerSession *p);
static __inline__ void GitsnDsrcEmulatorServerSession_delAndSetNull(void *ptr)
{
	GitsnDsrcEmulatorServerSession **p = (GitsnDsrcEmulatorServerSession **)ptr;
	if (p) { GitsnDsrcEmulatorServerSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorServerSession_dump(GitsnDsrcEmulatorServerSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnDsrcEmulatorServerSession_cmp(GitsnDsrcEmulatorServerSession *a, GitsnDsrcEmulatorServerSession *b); 
// GitsnDsrcEmulatorServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorSessionPresent
typedef enum GitsnDsrcEmulatorSessionPresent
{
	GitsnDsrcEmulatorSessionPresent_client,
	GitsnDsrcEmulatorSessionPresent_server,
	GitsnDsrcEmulatorSessionPresent_max
} GitsnDsrcEmulatorSessionPresent;

DZ1_CPPLINK str_t GitsnDsrcEmulatorSessionPresentStrA(GitsnDsrcEmulatorSessionPresent v);
DZ1_CPPLINK GitsnDsrcEmulatorSessionPresent GitsnDsrcEmulatorSessionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnDsrcEmulatorSessionPresentStrW(GitsnDsrcEmulatorSessionPresent v);
DZ1_CPPLINK GitsnDsrcEmulatorSessionPresent GitsnDsrcEmulatorSessionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnDsrcEmulatorSessionPresentStr GitsnDsrcEmulatorSessionPresentStrW
#define GitsnDsrcEmulatorSessionPresentFromStr GitsnDsrcEmulatorSessionPresentFromStrW
#else // UNICODE
#define GitsnDsrcEmulatorSessionPresentStr GitsnDsrcEmulatorSessionPresentStrA
#define GitsnDsrcEmulatorSessionPresentFromStr GitsnDsrcEmulatorSessionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnDsrcEmulatorSessionPresentStr GitsnDsrcEmulatorSessionPresentStrA
#define GitsnDsrcEmulatorSessionPresentFromStr GitsnDsrcEmulatorSessionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnDsrcEmulatorSessionPresent *GitsnDsrcEmulatorSessionPresent_new(GitsnDsrcEmulatorSessionPresent *src, Dz1Error *err);
static __inline__ GitsnDsrcEmulatorSessionPresent *GitsnDsrcEmulatorSessionPresent_gen(Dz1Error *err) { GitsnDsrcEmulatorSessionPresent v = GitsnDsrcEmulatorSessionPresent_max; return GitsnDsrcEmulatorSessionPresent_new(&v, err); }
static __inline__ void GitsnDsrcEmulatorSessionPresent_del(GitsnDsrcEmulatorSessionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnDsrcEmulatorSessionPresent_delAndSetNull(void *ptr)
{
	GitsnDsrcEmulatorSessionPresent **p = (GitsnDsrcEmulatorSessionPresent **)ptr;
	if (p != NULL) { GitsnDsrcEmulatorSessionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorSessionPresent_dump(GitsnDsrcEmulatorSessionPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnDsrcEmulatorSessionPresent_cmp(GitsnDsrcEmulatorSessionPresent *a, GitsnDsrcEmulatorSessionPresent *b);
// GitsnDsrcEmulatorSessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorSession
typedef struct GitsnDsrcEmulatorSession
{
	GitsnDsrcEmulatorSessionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		GitsnDsrcEmulatorClientSession		*client;
		GitsnDsrcEmulatorServerSession		*server;
	} x;
} GitsnDsrcEmulatorSession;

DZ1_CPPLINK DZ1_DLLPORT GitsnDsrcEmulatorSession *GitsnDsrcEmulatorSession_new(GitsnDsrcEmulatorSessionPresent present, void *ptr, Dz1Error *err);
static __inline__ GitsnDsrcEmulatorSession *GitsnDsrcEmulatorSession_gen(Dz1Error *err) { return GitsnDsrcEmulatorSession_new(GitsnDsrcEmulatorSessionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorSession_purge(GitsnDsrcEmulatorSession *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorSession_del(GitsnDsrcEmulatorSession *p);
static __inline__ void GitsnDsrcEmulatorSession_delAndSetNull(void *ptr)
{
	GitsnDsrcEmulatorSession **p = (GitsnDsrcEmulatorSession **)ptr;
	if (p != NULL) { GitsnDsrcEmulatorSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorSession_dump(GitsnDsrcEmulatorSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnDsrcEmulatorSession_cmp(GitsnDsrcEmulatorSession *a, GitsnDsrcEmulatorSession *b);
// GitsnDsrcEmulatorSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorEnv
typedef struct GitsnDsrcEmulatorEnv
{
	void						*tSelf;
	GitsnDsrcEmulatorSession	*session;
} GitsnDsrcEmulatorEnv;

DZ1_CPPLINK DZ1_DLLPORT GitsnDsrcEmulatorEnv *GitsnDsrcEmulatorEnv_new(void *tSelf, Dz1Error *err);
static __inline__ GitsnDsrcEmulatorEnv *GitsnDsrcEmulatorEnv_gen(Dz1Error *err) { return GitsnDsrcEmulatorEnv_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorEnv_purge(GitsnDsrcEmulatorEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorEnv_del(GitsnDsrcEmulatorEnv *p);
static __inline__ void GitsnDsrcEmulatorEnv_delAndSetNull(void *ptr)
{
	GitsnDsrcEmulatorEnv **p = (GitsnDsrcEmulatorEnv **)ptr;
	if (p) { GitsnDsrcEmulatorEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDsrcEmulatorEnv_dump(GitsnDsrcEmulatorEnv *p, int tab);
// GitsnDsrcEmulatorEnv
////////////////////////////////////////////////////////////////////////////////

#endif
