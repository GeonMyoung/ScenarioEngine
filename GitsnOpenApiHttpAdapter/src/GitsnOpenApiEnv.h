#ifndef _DZ1_TDC_GITSN_OPEN_API_ENV_H_
#define _DZ1_TDC_GITSN_OPEN_API_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1SockUtilDef.h"
#include "GitsnOpenApiDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpState
typedef enum GitsnOpenApiHttpState
{
	GitsnOpenApiHttpState_header,
	GitsnOpenApiHttpState_body,
	GitsnOpenApiHttpState_max
} GitsnOpenApiHttpState;

DZ1_CPPLINK str_t GitsnOpenApiHttpStateStrA(GitsnOpenApiHttpState v);
DZ1_CPPLINK GitsnOpenApiHttpState GitsnOpenApiHttpStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnOpenApiHttpStateStrW(GitsnOpenApiHttpState v);
DZ1_CPPLINK GitsnOpenApiHttpState GitsnOpenApiHttpStateFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnOpenApiHttpStateStr GitsnOpenApiHttpStateStrW
#define GitsnOpenApiHttpStateFromStr GitsnOpenApiHttpStateFromStrW
#else // UNICODE
#define GitsnOpenApiHttpStateStr GitsnOpenApiHttpStateStrA
#define GitsnOpenApiHttpStateFromStr GitsnOpenApiHttpStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnOpenApiHttpStateStr GitsnOpenApiHttpStateStrA
#define GitsnOpenApiHttpStateFromStr GitsnOpenApiHttpStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpState *GitsnOpenApiHttpState_new(GitsnOpenApiHttpState *src, Dz1Error *err);
static __inline__ GitsnOpenApiHttpState *GitsnOpenApiHttpState_gen(Dz1Error *err) { GitsnOpenApiHttpState v = GitsnOpenApiHttpState_max; return GitsnOpenApiHttpState_new(&v, err); }
static __inline__ void GitsnOpenApiHttpState_del(GitsnOpenApiHttpState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnOpenApiHttpState_delAndSetNull(void *ptr)
{
	GitsnOpenApiHttpState **p = (GitsnOpenApiHttpState **)ptr;
	if (p != NULL) { GitsnOpenApiHttpState_del(*p); *p = NULL; }
}
// GitsnOpenApiHttpState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpLines
typedef struct GitsnOpenApiHttpLines
{
	void *storage;
	unsigned int (*count)(struct GitsnOpenApiHttpLines *p);
	Dz1Error (*travel)(struct GitsnOpenApiHttpLines *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelForward)(struct GitsnOpenApiHttpLines *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelBackward)(struct GitsnOpenApiHttpLines *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	str_t *(*get_array)(struct GitsnOpenApiHttpLines *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct GitsnOpenApiHttpLines *p, str_t data);
	str_t (*extract)(struct GitsnOpenApiHttpLines *p, str_t ptr);
	int (*cmp)(str_t a, str_t b);
} GitsnOpenApiHttpLines;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpLines *GitsnOpenApiHttpLines_new(Dz1Error *err);
static __inline__ GitsnOpenApiHttpLines *GitsnOpenApiHttpLines_gen(Dz1Error *err) { return GitsnOpenApiHttpLines_new(err); }
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpLines *GitsnOpenApiHttpLines_clone(GitsnOpenApiHttpLines *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpLines_purge(GitsnOpenApiHttpLines *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpLines_del(GitsnOpenApiHttpLines *p);
static __inline__ void GitsnOpenApiHttpLines_delAndSetNull(void *ptr)
{
	GitsnOpenApiHttpLines **p = (GitsnOpenApiHttpLines **)ptr;
	if (p != NULL) { GitsnOpenApiHttpLines_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpLinesA_dump(GitsnOpenApiHttpLines *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpLinesA_fdump(FILE *fp, GitsnOpenApiHttpLines *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpLinesW_dump(GitsnOpenApiHttpLines *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpLinesW_fdump(FILE *fp, GitsnOpenApiHttpLines *p, int tab);
#ifdef UNICODE
#define GitsnOpenApiHttpLines_dump GitsnOpenApiHttpLinesW_dump
#define GitsnOpenApiHttpLines_fdump GitsnOpenApiHttpLinesW_fdump
#else //  UNICODE
#define GitsnOpenApiHttpLines_dump GitsnOpenApiHttpLinesA_dump
#define GitsnOpenApiHttpLines_fdump GitsnOpenApiHttpLinesA_fdump
#endif //  UNICODE
static __inline__ void GitsnOpenApiHttpLinesX_dump(GitsnOpenApiHttpLines *p, int tab) { DZ1_DUMP(GitsnOpenApiHttpLines, p, tab); }
static __inline__ void GitsnOpenApiHttpLinesX_fdump(FILE *fp, GitsnOpenApiHttpLines *p, int tab) { DZ1_FDUMP(fp, GitsnOpenApiHttpLines, p, tab); }
#else // UNIX_SYSTEM
#define GitsnOpenApiHttpLines_dump GitsnOpenApiHttpLinesA_dump
#define GitsnOpenApiHttpLinesX_dump GitsnOpenApiHttpLinesA_dump
#define GitsnOpenApiHttpLines_fdump GitsnOpenApiHttpLinesA_fdump
#define GitsnOpenApiHttpLinesX_fdump GitsnOpenApiHttpLinesA_fdump
#endif // UNIX_SYSTEM

// GitsnOpenApiHttpLines
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpParser
typedef struct GitsnOpenApiHttpParser
{
	GitsnOpenApiHttpState		 state;
	Dz1ElasticBuf				*rx_buf;
	GitsnOpenApiHttpLines		*hdr_lines;
	Dz1ElasticBuf				*body;
	ssize_t						 body_size;
	GitsnOpenApiHttpReq			*req;
	bool_t						 close_after_response;
} GitsnOpenApiHttpParser;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpParser *GitsnOpenApiHttpParser_new(Dz1ElasticBuf *rx_buf, 
																		   ssize_t body_size, Dz1Error *err);
static __inline__ GitsnOpenApiHttpParser *GitsnOpenApiHttpParser_gen(Dz1Error *err) { return GitsnOpenApiHttpParser_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpParser_purge(GitsnOpenApiHttpParser *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpParser_del(GitsnOpenApiHttpParser *p);
static __inline__ void GitsnOpenApiHttpParser_delAndSetNull(void *ptr)
{
	GitsnOpenApiHttpParser **p = (GitsnOpenApiHttpParser **)ptr;
	if (p) { GitsnOpenApiHttpParser_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpParser_dump(GitsnOpenApiHttpParser *p, int tab);
// GitsnOpenApiHttpParser
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiSession
typedef struct GitsnOpenApiSession
{
	u32_t								 id;
	Dz1SockAddr							*peer;
	Dz1SockAddr							*local;
	Dz1TcpClientSocket					*sock;
	GitsnOpenApiHttpParser				*parser;
	bool_t								 closing;
	Dz1SockUtilTxFifo					*tx_fifo;
	bool_t								 response_pending;
	void								*response_call;
	bool_t								 idle_timer_armed;
	u32_t								 response_sequence;
	u64_t								 last_response_sent_ms;
	GitsnOpenApiConnectionEventType		 close_event_type;
} GitsnOpenApiSession;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiSession *GitsnOpenApiSession_new(u32_t id, 
																	 Dz1SockAddr *peer, 
																	 Dz1SockAddr *local, 
																	 Dz1TcpClientSocket *sock, 
																	 GitsnOpenApiHttpParser *parser, 
																	 Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ GitsnOpenApiSession *GitsnOpenApiSession_gen(Dz1Error *err) { return GitsnOpenApiSession_new(0, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiSession_purge(GitsnOpenApiSession *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiSession_del(GitsnOpenApiSession *p);
static __inline__ void GitsnOpenApiSession_delAndSetNull(void *ptr)
{
	GitsnOpenApiSession **p = (GitsnOpenApiSession **)ptr;
	if (p) { GitsnOpenApiSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiSession_dump(GitsnOpenApiSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnOpenApiSession_cmp(GitsnOpenApiSession *a, GitsnOpenApiSession *b); 
// GitsnOpenApiSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiSessionTable
typedef struct GitsnOpenApiSessionTable
{
	void *storage;
	unsigned int (*count)(struct GitsnOpenApiSessionTable *p);
	Dz1Error (*travel)(struct GitsnOpenApiSessionTable *p, Dz1Error (*func)(void *ptr, GitsnOpenApiSession *entry), void *ptr);
	Dz1Error (*travelForward)(struct GitsnOpenApiSessionTable *p, Dz1Error (*func)(void *ptr, GitsnOpenApiSession *entry), void *ptr);
	Dz1Error (*travelBackward)(struct GitsnOpenApiSessionTable *p, Dz1Error (*func)(void *ptr, GitsnOpenApiSession *entry), void *ptr);
	GitsnOpenApiSession **(*get_array)(struct GitsnOpenApiSessionTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct GitsnOpenApiSessionTable *p, GitsnOpenApiSession *data);
	bool_t (*remove)(struct GitsnOpenApiSessionTable *p, GitsnOpenApiSession *key);
	GitsnOpenApiSession *(*extract)(struct GitsnOpenApiSessionTable *p, GitsnOpenApiSession *key);
	GitsnOpenApiSession *(*find)(struct GitsnOpenApiSessionTable *p, GitsnOpenApiSession *key);
	int (*cmp)(GitsnOpenApiSession *a, GitsnOpenApiSession *b);
} GitsnOpenApiSessionTable;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiSessionTable *GitsnOpenApiSessionTable_new(Dz1Error *err);
static __inline__ GitsnOpenApiSessionTable *GitsnOpenApiSessionTable_gen(Dz1Error *err) { return GitsnOpenApiSessionTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiSessionTable_purge(GitsnOpenApiSessionTable *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiSessionTable_del(GitsnOpenApiSessionTable *p);
static __inline__ void GitsnOpenApiSessionTable_delAndSetNull(void *ptr)
{
	GitsnOpenApiSessionTable **p = (GitsnOpenApiSessionTable **)ptr;
	if (p != NULL) { GitsnOpenApiSessionTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiSessionTable_dump(GitsnOpenApiSessionTable *p, int tab);

// GitsnOpenApiSessionTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiSessions
typedef struct GitsnOpenApiSessions
{
	GitsnOpenApiSessionTable	*table;
	u32_t						 alloc_id;
} GitsnOpenApiSessions;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiSessions *GitsnOpenApiSessions_new(Dz1Error *err);
static __inline__ GitsnOpenApiSessions *GitsnOpenApiSessions_gen(Dz1Error *err) { return GitsnOpenApiSessions_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiSessions_purge(GitsnOpenApiSessions *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiSessions_del(GitsnOpenApiSessions *p);
static __inline__ void GitsnOpenApiSessions_delAndSetNull(void *ptr)
{
	GitsnOpenApiSessions **p = (GitsnOpenApiSessions **)ptr;
	if (p) { GitsnOpenApiSessions_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiSessions_dump(GitsnOpenApiSessions *p, int tab);
// GitsnOpenApiSessions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiEnv
typedef struct GitsnOpenApiEnv
{
	void					*tSelf;
	u32_t					 acceptor;
	GitsnOpenApiSessions	*sessions;
} GitsnOpenApiEnv;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiEnv *GitsnOpenApiEnv_new(void *tSelf, 
															 u32_t acceptor, 
															 GitsnOpenApiSessions *sessions, Dz1Error *err);
static __inline__ GitsnOpenApiEnv *GitsnOpenApiEnv_gen(Dz1Error *err) { return GitsnOpenApiEnv_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiEnv_purge(GitsnOpenApiEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiEnv_del(GitsnOpenApiEnv *p);
static __inline__ void GitsnOpenApiEnv_delAndSetNull(void *ptr)
{
	GitsnOpenApiEnv **p = (GitsnOpenApiEnv **)ptr;
	if (p) { GitsnOpenApiEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiEnv_dump(GitsnOpenApiEnv *p, int tab);
// GitsnOpenApiEnv
////////////////////////////////////////////////////////////////////////////////

#endif
