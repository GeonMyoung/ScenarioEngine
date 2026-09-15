#ifndef _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_ENV_H_
#define _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDSRCMsgTestScenarioDef.h"
#include "Dz1SockUtilDef.h"
#include "GitsnTestDataProtocolDef.h"
#include "Dz1JsonDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgClientSession
typedef struct GitsnDSRCMsgClientSession
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} GitsnDSRCMsgClientSession;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgClientSession *GitsnDSRCMsgClientSession_new(Dz1SockAddr *peer, 
																				 Dz1SockAddr *local, 
																				 Dz1TcpClientSocket *sock, 
																				 Dz1ElasticBuf *rx_buf, 
																				 Dz1Stream *rx_stream, 
																				 Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ GitsnDSRCMsgClientSession *GitsnDSRCMsgClientSession_gen(Dz1Error *err) { return GitsnDSRCMsgClientSession_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgClientSession_purge(GitsnDSRCMsgClientSession *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgClientSession_del(GitsnDSRCMsgClientSession *p);
static __inline__ void GitsnDSRCMsgClientSession_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgClientSession **p = (GitsnDSRCMsgClientSession **)ptr;
	if (p) { GitsnDSRCMsgClientSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgClientSession_dump(GitsnDSRCMsgClientSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnDSRCMsgClientSession_cmp(GitsnDSRCMsgClientSession *a, GitsnDSRCMsgClientSession *b); 
// GitsnDSRCMsgClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgServerSession
typedef struct GitsnDSRCMsgServerSession
{
	u32_t					 acceptor;
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} GitsnDSRCMsgServerSession;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgServerSession *GitsnDSRCMsgServerSession_new(u32_t acceptor, 
																				 Dz1SockAddr *peer, 
																				 Dz1SockAddr *local, 
																				 Dz1TcpClientSocket *sock, 
																				 Dz1ElasticBuf *rx_buf, 
																				 Dz1Stream *rx_stream, 
																				 Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ GitsnDSRCMsgServerSession *GitsnDSRCMsgServerSession_gen(Dz1Error *err) { return GitsnDSRCMsgServerSession_new(0, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgServerSession_purge(GitsnDSRCMsgServerSession *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgServerSession_del(GitsnDSRCMsgServerSession *p);
static __inline__ void GitsnDSRCMsgServerSession_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgServerSession **p = (GitsnDSRCMsgServerSession **)ptr;
	if (p) { GitsnDSRCMsgServerSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgServerSession_dump(GitsnDSRCMsgServerSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnDSRCMsgServerSession_cmp(GitsnDSRCMsgServerSession *a, GitsnDSRCMsgServerSession *b); 
// GitsnDSRCMsgServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgSessionPresent
typedef enum GitsnDSRCMsgSessionPresent
{
	GitsnDSRCMsgSessionPresent_client,
	GitsnDSRCMsgSessionPresent_server,
	GitsnDSRCMsgSessionPresent_max
} GitsnDSRCMsgSessionPresent;

DZ1_CPPLINK str_t GitsnDSRCMsgSessionPresentStrA(GitsnDSRCMsgSessionPresent v);
DZ1_CPPLINK GitsnDSRCMsgSessionPresent GitsnDSRCMsgSessionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnDSRCMsgSessionPresentStrW(GitsnDSRCMsgSessionPresent v);
DZ1_CPPLINK GitsnDSRCMsgSessionPresent GitsnDSRCMsgSessionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnDSRCMsgSessionPresentStr GitsnDSRCMsgSessionPresentStrW
#define GitsnDSRCMsgSessionPresentFromStr GitsnDSRCMsgSessionPresentFromStrW
#else // UNICODE
#define GitsnDSRCMsgSessionPresentStr GitsnDSRCMsgSessionPresentStrA
#define GitsnDSRCMsgSessionPresentFromStr GitsnDSRCMsgSessionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnDSRCMsgSessionPresentStr GitsnDSRCMsgSessionPresentStrA
#define GitsnDSRCMsgSessionPresentFromStr GitsnDSRCMsgSessionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgSessionPresent *GitsnDSRCMsgSessionPresent_new(GitsnDSRCMsgSessionPresent *src, Dz1Error *err);
static __inline__ GitsnDSRCMsgSessionPresent *GitsnDSRCMsgSessionPresent_gen(Dz1Error *err) { GitsnDSRCMsgSessionPresent v = GitsnDSRCMsgSessionPresent_max; return GitsnDSRCMsgSessionPresent_new(&v, err); }
static __inline__ void GitsnDSRCMsgSessionPresent_del(GitsnDSRCMsgSessionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnDSRCMsgSessionPresent_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgSessionPresent **p = (GitsnDSRCMsgSessionPresent **)ptr;
	if (p != NULL) { GitsnDSRCMsgSessionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgSessionPresent_dump(GitsnDSRCMsgSessionPresent *v, int tab);
// GitsnDSRCMsgSessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgSession
typedef struct GitsnDSRCMsgSession
{
	GitsnDSRCMsgSessionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		GitsnDSRCMsgClientSession		*client;
		GitsnDSRCMsgServerSession		*server;
	} x;
} GitsnDSRCMsgSession;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgSession *GitsnDSRCMsgSession_new(GitsnDSRCMsgSessionPresent present, void *ptr, Dz1Error *err);
static __inline__ GitsnDSRCMsgSession *GitsnDSRCMsgSession_gen(Dz1Error *err) { return GitsnDSRCMsgSession_new(GitsnDSRCMsgSessionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgSession_purge(GitsnDSRCMsgSession *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgSession_del(GitsnDSRCMsgSession *p);
static __inline__ void GitsnDSRCMsgSession_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgSession **p = (GitsnDSRCMsgSession **)ptr;
	if (p != NULL) { GitsnDSRCMsgSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgSession_dump(GitsnDSRCMsgSession *p, int tab);
// GitsnDSRCMsgSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgScenario
typedef struct GitsnDSRCMsgScenario
{
	u16_t		local_port;
	bool_t		test_map;
	bool_t		test_spat;
	bool_t		test_bsm;
	bool_t		test_eva;
	bool_t		test_pvd;
	bool_t		test_rsa;
	bool_t		test_rtcm;
	bool_t		test_srm;
	bool_t		test_ssm;
	bool_t		test_tim;
	bool_t		test_psm;
	bool_t		test_sdsm;
	bool_t		test_tls;
} GitsnDSRCMsgScenario;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgScenario *GitsnDSRCMsgScenario_new(u16_t local_port, 
																	   bool_t test_map, 
																	   bool_t test_spat, 
																	   bool_t test_bsm, 
																	   bool_t test_eva, 
																	   bool_t test_pvd, 
																	   bool_t test_rsa, 
																	   bool_t test_rtcm, 
																	   bool_t test_srm, 
																	   bool_t test_ssm, 
																	   bool_t test_tim, 
																	   bool_t test_psm, 
																	   bool_t test_sdsm, 
																	   bool_t test_tls, Dz1Error *err);
static __inline__ GitsnDSRCMsgScenario *GitsnDSRCMsgScenario_gen(Dz1Error *err) { return GitsnDSRCMsgScenario_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgScenario_copy(GitsnDSRCMsgScenario *dst, GitsnDSRCMsgScenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgScenario *GitsnDSRCMsgScenario_clone(GitsnDSRCMsgScenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgScenario_purge(GitsnDSRCMsgScenario *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgScenario_del(GitsnDSRCMsgScenario *p);
static __inline__ void GitsnDSRCMsgScenario_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgScenario **p = (GitsnDSRCMsgScenario **)ptr;
	if (p) { GitsnDSRCMsgScenario_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgScenario_dump(GitsnDSRCMsgScenario *p, int tab);
// GitsnDSRCMsgScenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgScenarioEvent
typedef enum GitsnDSRCMsgScenarioEvent
{
	GitsnDSRCMsgScenarioEvent_start,
	GitsnDSRCMsgScenarioEvent_auth,
	GitsnDSRCMsgScenarioEvent_trigger,
	GitsnDSRCMsgScenarioEvent_data,
	GitsnDSRCMsgScenarioEvent_validate,
	GitsnDSRCMsgScenarioEvent_disconnected,
	GitsnDSRCMsgScenarioEvent_max
} GitsnDSRCMsgScenarioEvent;

DZ1_CPPLINK str_t GitsnDSRCMsgScenarioEventStrA(GitsnDSRCMsgScenarioEvent v);
DZ1_CPPLINK GitsnDSRCMsgScenarioEvent GitsnDSRCMsgScenarioEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnDSRCMsgScenarioEventStrW(GitsnDSRCMsgScenarioEvent v);
DZ1_CPPLINK GitsnDSRCMsgScenarioEvent GitsnDSRCMsgScenarioEventFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnDSRCMsgScenarioEventStr GitsnDSRCMsgScenarioEventStrW
#define GitsnDSRCMsgScenarioEventFromStr GitsnDSRCMsgScenarioEventFromStrW
#else // UNICODE
#define GitsnDSRCMsgScenarioEventStr GitsnDSRCMsgScenarioEventStrA
#define GitsnDSRCMsgScenarioEventFromStr GitsnDSRCMsgScenarioEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnDSRCMsgScenarioEventStr GitsnDSRCMsgScenarioEventStrA
#define GitsnDSRCMsgScenarioEventFromStr GitsnDSRCMsgScenarioEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgScenarioEvent *GitsnDSRCMsgScenarioEvent_new(GitsnDSRCMsgScenarioEvent *src, Dz1Error *err);
static __inline__ GitsnDSRCMsgScenarioEvent *GitsnDSRCMsgScenarioEvent_gen(Dz1Error *err) { GitsnDSRCMsgScenarioEvent v = GitsnDSRCMsgScenarioEvent_max; return GitsnDSRCMsgScenarioEvent_new(&v, err); }
#define GitsnDSRCMsgScenarioEvent_clone             GitsnDSRCMsgScenarioEvent_new
static __inline__ void GitsnDSRCMsgScenarioEvent_del(GitsnDSRCMsgScenarioEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnDSRCMsgScenarioEvent_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgScenarioEvent **p = (GitsnDSRCMsgScenarioEvent **)ptr;
	if (p != NULL) { GitsnDSRCMsgScenarioEvent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgScenarioEvent_dump(GitsnDSRCMsgScenarioEvent *v, int tab);
// GitsnDSRCMsgScenarioEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgScenarioState
typedef enum GitsnDSRCMsgScenarioState
{
	GitsnDSRCMsgScenarioState_initial,
	GitsnDSRCMsgScenarioState_wait_data,
	GitsnDSRCMsgScenarioState_complete,
	GitsnDSRCMsgScenarioState_max
} GitsnDSRCMsgScenarioState;

DZ1_CPPLINK str_t GitsnDSRCMsgScenarioStateStrA(GitsnDSRCMsgScenarioState v);
DZ1_CPPLINK GitsnDSRCMsgScenarioState GitsnDSRCMsgScenarioStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnDSRCMsgScenarioStateStrW(GitsnDSRCMsgScenarioState v);
DZ1_CPPLINK GitsnDSRCMsgScenarioState GitsnDSRCMsgScenarioStateFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnDSRCMsgScenarioStateStr GitsnDSRCMsgScenarioStateStrW
#define GitsnDSRCMsgScenarioStateFromStr GitsnDSRCMsgScenarioStateFromStrW
#else // UNICODE
#define GitsnDSRCMsgScenarioStateStr GitsnDSRCMsgScenarioStateStrA
#define GitsnDSRCMsgScenarioStateFromStr GitsnDSRCMsgScenarioStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnDSRCMsgScenarioStateStr GitsnDSRCMsgScenarioStateStrA
#define GitsnDSRCMsgScenarioStateFromStr GitsnDSRCMsgScenarioStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgScenarioState *GitsnDSRCMsgScenarioState_new(GitsnDSRCMsgScenarioState *src, Dz1Error *err);
static __inline__ GitsnDSRCMsgScenarioState *GitsnDSRCMsgScenarioState_gen(Dz1Error *err) { GitsnDSRCMsgScenarioState v = GitsnDSRCMsgScenarioState_max; return GitsnDSRCMsgScenarioState_new(&v, err); }
#define GitsnDSRCMsgScenarioState_clone             GitsnDSRCMsgScenarioState_new
static __inline__ void GitsnDSRCMsgScenarioState_del(GitsnDSRCMsgScenarioState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnDSRCMsgScenarioState_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgScenarioState **p = (GitsnDSRCMsgScenarioState **)ptr;
	if (p != NULL) { GitsnDSRCMsgScenarioState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgScenarioState_dump(GitsnDSRCMsgScenarioState *v, int tab);
// GitsnDSRCMsgScenarioState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestScenarioEnv
typedef struct GitsnDSRCMsgTestScenarioEnv
{
	void					*tSelf;
	void					*tMain;
	Dz1JsonSpec				*spec;
	GitsnDSRCMsgSession		*session;
	GitsnDSRCMsgScenario	*scenario;
	bool_t					 is_run;
	s32_t					 state;
	u32_t					 flags;
	GitsnTestDataFrames		*dfs;
	u32_t					 testIdx;
	Dz1Str					 current_test;
} GitsnDSRCMsgTestScenarioEnv;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgTestScenarioEnv *GitsnDSRCMsgTestScenarioEnv_new(void *tSelf, 
																					 void *tMain, 
																					 Dz1JsonSpec *spec, Dz1Error *err);
static __inline__ GitsnDSRCMsgTestScenarioEnv *GitsnDSRCMsgTestScenarioEnv_gen(Dz1Error *err) { return GitsnDSRCMsgTestScenarioEnv_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioEnv_purge(GitsnDSRCMsgTestScenarioEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioEnv_del(GitsnDSRCMsgTestScenarioEnv *p);
static __inline__ void GitsnDSRCMsgTestScenarioEnv_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgTestScenarioEnv **p = (GitsnDSRCMsgTestScenarioEnv **)ptr;
	if (p) { GitsnDSRCMsgTestScenarioEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioEnv_dump(GitsnDSRCMsgTestScenarioEnv *p, int tab);
// GitsnDSRCMsgTestScenarioEnv
////////////////////////////////////////////////////////////////////////////////

#endif
