#ifndef _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_ENV_H_
#define _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2TestScenarioDef.h"
#include "Dz1JsonDef.h"
#include "Dz1SockUtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ClientSession
typedef struct ITSK00144_2ClientSession
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} ITSK00144_2ClientSession;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ClientSession *ITSK00144_2ClientSession_new(Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ ITSK00144_2ClientSession *ITSK00144_2ClientSession_gen(Dz1Error *err) { return ITSK00144_2ClientSession_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ClientSession_purge(ITSK00144_2ClientSession *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ClientSession_del(ITSK00144_2ClientSession *p);
static __inline__ void ITSK00144_2ClientSession_delAndSetNull(void *ptr)
{
	ITSK00144_2ClientSession **p = (ITSK00144_2ClientSession **)ptr;
	if (p) { ITSK00144_2ClientSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ClientSession_dump(ITSK00144_2ClientSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ITSK00144_2ClientSession_cmp(ITSK00144_2ClientSession *a, ITSK00144_2ClientSession *b); 
// ITSK00144_2ClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ServerSession
typedef struct ITSK00144_2ServerSession
{
	u32_t					 acceptor;
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} ITSK00144_2ServerSession;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ServerSession *ITSK00144_2ServerSession_new(u32_t acceptor, 
																			   Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ ITSK00144_2ServerSession *ITSK00144_2ServerSession_gen(Dz1Error *err) { return ITSK00144_2ServerSession_new(0, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ServerSession_purge(ITSK00144_2ServerSession *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ServerSession_del(ITSK00144_2ServerSession *p);
static __inline__ void ITSK00144_2ServerSession_delAndSetNull(void *ptr)
{
	ITSK00144_2ServerSession **p = (ITSK00144_2ServerSession **)ptr;
	if (p) { ITSK00144_2ServerSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ServerSession_dump(ITSK00144_2ServerSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ITSK00144_2ServerSession_cmp(ITSK00144_2ServerSession *a, ITSK00144_2ServerSession *b); 
// ITSK00144_2ServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2SessionPresent
typedef enum ITSK00144_2SessionPresent
{
	ITSK00144_2SessionPresent_client,
	ITSK00144_2SessionPresent_server,
	ITSK00144_2SessionPresent_max
} ITSK00144_2SessionPresent;

DZ1_CPPLINK str_t ITSK00144_2SessionPresentStrA(ITSK00144_2SessionPresent v);
DZ1_CPPLINK ITSK00144_2SessionPresent ITSK00144_2SessionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2SessionPresentStrW(ITSK00144_2SessionPresent v);
DZ1_CPPLINK ITSK00144_2SessionPresent ITSK00144_2SessionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2SessionPresentStr ITSK00144_2SessionPresentStrW
#define ITSK00144_2SessionPresentFromStr ITSK00144_2SessionPresentFromStrW
#else // UNICODE
#define ITSK00144_2SessionPresentStr ITSK00144_2SessionPresentStrA
#define ITSK00144_2SessionPresentFromStr ITSK00144_2SessionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2SessionPresentStr ITSK00144_2SessionPresentStrA
#define ITSK00144_2SessionPresentFromStr ITSK00144_2SessionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2SessionPresent *ITSK00144_2SessionPresent_new(ITSK00144_2SessionPresent *src, Dz1Error *err);
static __inline__ ITSK00144_2SessionPresent *ITSK00144_2SessionPresent_gen(Dz1Error *err) { ITSK00144_2SessionPresent v = ITSK00144_2SessionPresent_max; return ITSK00144_2SessionPresent_new(&v, err); }
static __inline__ void ITSK00144_2SessionPresent_del(ITSK00144_2SessionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2SessionPresent_delAndSetNull(void *ptr)
{
	ITSK00144_2SessionPresent **p = (ITSK00144_2SessionPresent **)ptr;
	if (p != NULL) { ITSK00144_2SessionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2SessionPresent_dump(ITSK00144_2SessionPresent *v, int tab);
// ITSK00144_2SessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Session
typedef struct ITSK00144_2Session
{
	ITSK00144_2SessionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ITSK00144_2ClientSession	*client;
		ITSK00144_2ServerSession	*server;
	} x;
} ITSK00144_2Session;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Session *ITSK00144_2Session_new(ITSK00144_2SessionPresent present, void *ptr, Dz1Error *err);
static __inline__ ITSK00144_2Session *ITSK00144_2Session_gen(Dz1Error *err) { return ITSK00144_2Session_new(ITSK00144_2SessionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Session_purge(ITSK00144_2Session *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Session_del(ITSK00144_2Session *p);
static __inline__ void ITSK00144_2Session_delAndSetNull(void *ptr)
{
	ITSK00144_2Session **p = (ITSK00144_2Session **)ptr;
	if (p != NULL) { ITSK00144_2Session_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Session_dump(ITSK00144_2Session *p, int tab);
// ITSK00144_2Session
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioServerRole
typedef struct ITSK00144_2ScenarioServerRole
{
	u16_t								 local_port;
	bool_t								 test_rsp_link_unit_status;
	bool_t								 test_rsp_status;
	bool_t								 test_rsp_list;
	bool_t								 test_rsp_update_list;
	bool_t								 test_rsp_reset;
	bool_t								 test_session_maintain;
	s64_t								 hb_duration;
	I2XTrafficSafetyDeviceSerialNo		*id;
	Dz1Binary							*received;
} ITSK00144_2ScenarioServerRole;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ScenarioServerRole *ITSK00144_2ScenarioServerRole_new(u16_t local_port, 
																						 bool_t test_rsp_link_unit_status, 
																						 bool_t test_rsp_status, 
																						 bool_t test_rsp_list, 
																						 bool_t test_rsp_update_list, 
																						 bool_t test_rsp_reset, 
																						 bool_t test_session_maintain, 
																						 s64_t hb_duration, Dz1Error *err);
static __inline__ ITSK00144_2ScenarioServerRole *ITSK00144_2ScenarioServerRole_gen(Dz1Error *err) { return ITSK00144_2ScenarioServerRole_new(0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2ScenarioServerRole_copy(ITSK00144_2ScenarioServerRole *dst, ITSK00144_2ScenarioServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ScenarioServerRole *ITSK00144_2ScenarioServerRole_clone(ITSK00144_2ScenarioServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ScenarioServerRole_purge(ITSK00144_2ScenarioServerRole *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ScenarioServerRole_del(ITSK00144_2ScenarioServerRole *p);
static __inline__ void ITSK00144_2ScenarioServerRole_delAndSetNull(void *ptr)
{
	ITSK00144_2ScenarioServerRole **p = (ITSK00144_2ScenarioServerRole **)ptr;
	if (p) { ITSK00144_2ScenarioServerRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ScenarioServerRole_dump(ITSK00144_2ScenarioServerRole *p, int tab);
// ITSK00144_2ScenarioServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioLinkUnitRole
typedef struct ITSK00144_2ScenarioLinkUnitRole
{
	Dz1Str								 peer_ip;
	u16_t								 peer_port;
	bool_t								 test_req_link_unit_status;
	bool_t								 test_req_status;
	bool_t								 test_req_list;
	bool_t								 test_req_update_list;
	bool_t								 test_req_reset;
	bool_t								 test_session_maintain;
	bool_t								 test_tim;
	bool_t								 test_map;
	s64_t								 hb_duration;
	I2XTrafficSafetyDeviceSerialNo		*id;
} ITSK00144_2ScenarioLinkUnitRole;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ScenarioLinkUnitRole *ITSK00144_2ScenarioLinkUnitRole_new(Dz1Str peer_ip, 
																							 u16_t peer_port, 
																							 bool_t test_req_link_unit_status, 
																							 bool_t test_req_status, 
																							 bool_t test_req_list, 
																							 bool_t test_req_update_list, 
																							 bool_t test_req_reset, 
																							 bool_t test_session_maintain, 
																							 bool_t test_tim, 
																							 bool_t test_map, 
																							 s64_t hb_duration, 
																							 I2XTrafficSafetyDeviceSerialNo *id, Dz1Error *err);
static __inline__ ITSK00144_2ScenarioLinkUnitRole *ITSK00144_2ScenarioLinkUnitRole_gen(Dz1Error *err) { return ITSK00144_2ScenarioLinkUnitRole_new(NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2ScenarioLinkUnitRole_copy(ITSK00144_2ScenarioLinkUnitRole *dst, ITSK00144_2ScenarioLinkUnitRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ScenarioLinkUnitRole *ITSK00144_2ScenarioLinkUnitRole_clone(ITSK00144_2ScenarioLinkUnitRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ScenarioLinkUnitRole_purge(ITSK00144_2ScenarioLinkUnitRole *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ScenarioLinkUnitRole_del(ITSK00144_2ScenarioLinkUnitRole *p);
static __inline__ void ITSK00144_2ScenarioLinkUnitRole_delAndSetNull(void *ptr)
{
	ITSK00144_2ScenarioLinkUnitRole **p = (ITSK00144_2ScenarioLinkUnitRole **)ptr;
	if (p) { ITSK00144_2ScenarioLinkUnitRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ScenarioLinkUnitRole_dump(ITSK00144_2ScenarioLinkUnitRole *p, int tab);
// ITSK00144_2ScenarioLinkUnitRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioPresent
typedef enum ITSK00144_2ScenarioPresent
{
	ITSK00144_2ScenarioPresent_serverRole,
	ITSK00144_2ScenarioPresent_linkUnitRole,
	ITSK00144_2ScenarioPresent_max
} ITSK00144_2ScenarioPresent;

DZ1_CPPLINK str_t ITSK00144_2ScenarioPresentStrA(ITSK00144_2ScenarioPresent v);
DZ1_CPPLINK ITSK00144_2ScenarioPresent ITSK00144_2ScenarioPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2ScenarioPresentStrW(ITSK00144_2ScenarioPresent v);
DZ1_CPPLINK ITSK00144_2ScenarioPresent ITSK00144_2ScenarioPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2ScenarioPresentStr ITSK00144_2ScenarioPresentStrW
#define ITSK00144_2ScenarioPresentFromStr ITSK00144_2ScenarioPresentFromStrW
#else // UNICODE
#define ITSK00144_2ScenarioPresentStr ITSK00144_2ScenarioPresentStrA
#define ITSK00144_2ScenarioPresentFromStr ITSK00144_2ScenarioPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2ScenarioPresentStr ITSK00144_2ScenarioPresentStrA
#define ITSK00144_2ScenarioPresentFromStr ITSK00144_2ScenarioPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ScenarioPresent *ITSK00144_2ScenarioPresent_new(ITSK00144_2ScenarioPresent *src, Dz1Error *err);
static __inline__ ITSK00144_2ScenarioPresent *ITSK00144_2ScenarioPresent_gen(Dz1Error *err) { ITSK00144_2ScenarioPresent v = ITSK00144_2ScenarioPresent_max; return ITSK00144_2ScenarioPresent_new(&v, err); }
#define ITSK00144_2ScenarioPresent_clone             ITSK00144_2ScenarioPresent_new
static __inline__ void ITSK00144_2ScenarioPresent_del(ITSK00144_2ScenarioPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2ScenarioPresent_delAndSetNull(void *ptr)
{
	ITSK00144_2ScenarioPresent **p = (ITSK00144_2ScenarioPresent **)ptr;
	if (p != NULL) { ITSK00144_2ScenarioPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ScenarioPresent_dump(ITSK00144_2ScenarioPresent *v, int tab);
// ITSK00144_2ScenarioPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Scenario
typedef struct ITSK00144_2Scenario
{
	ITSK00144_2ScenarioPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ITSK00144_2ScenarioServerRole		*serverRole;
		ITSK00144_2ScenarioLinkUnitRole		*linkUnitRole;
	} x;
} ITSK00144_2Scenario;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Scenario *ITSK00144_2Scenario_new(ITSK00144_2ScenarioPresent present, void *ptr, Dz1Error *err);
static __inline__ ITSK00144_2Scenario *ITSK00144_2Scenario_gen(Dz1Error *err) { return ITSK00144_2Scenario_new(ITSK00144_2ScenarioPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  ITSK00144_2Scenario_copy(ITSK00144_2Scenario *dst, ITSK00144_2Scenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Scenario *ITSK00144_2Scenario_clone(ITSK00144_2Scenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Scenario_purge(ITSK00144_2Scenario *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Scenario_del(ITSK00144_2Scenario *p);
static __inline__ void ITSK00144_2Scenario_delAndSetNull(void *ptr)
{
	ITSK00144_2Scenario **p = (ITSK00144_2Scenario **)ptr;
	if (p != NULL) { ITSK00144_2Scenario_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Scenario_dump(ITSK00144_2Scenario *p, int tab);
// ITSK00144_2Scenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioEvent
typedef enum ITSK00144_2ScenarioEvent
{
	ITSK00144_2ScenarioEvent_start,
	ITSK00144_2ScenarioEvent_auth,
	ITSK00144_2ScenarioEvent_heartbeat,
	ITSK00144_2ScenarioEvent_data,
	ITSK00144_2ScenarioEvent_data2,
	ITSK00144_2ScenarioEvent_validate,
	ITSK00144_2ScenarioEvent_trigger,
	ITSK00144_2ScenarioEvent_disconnected,
	ITSK00144_2ScenarioEvent_max
} ITSK00144_2ScenarioEvent;

DZ1_CPPLINK str_t ITSK00144_2ScenarioEventStrA(ITSK00144_2ScenarioEvent v);
DZ1_CPPLINK ITSK00144_2ScenarioEvent ITSK00144_2ScenarioEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2ScenarioEventStrW(ITSK00144_2ScenarioEvent v);
DZ1_CPPLINK ITSK00144_2ScenarioEvent ITSK00144_2ScenarioEventFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2ScenarioEventStr ITSK00144_2ScenarioEventStrW
#define ITSK00144_2ScenarioEventFromStr ITSK00144_2ScenarioEventFromStrW
#else // UNICODE
#define ITSK00144_2ScenarioEventStr ITSK00144_2ScenarioEventStrA
#define ITSK00144_2ScenarioEventFromStr ITSK00144_2ScenarioEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2ScenarioEventStr ITSK00144_2ScenarioEventStrA
#define ITSK00144_2ScenarioEventFromStr ITSK00144_2ScenarioEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ScenarioEvent *ITSK00144_2ScenarioEvent_new(ITSK00144_2ScenarioEvent *src, Dz1Error *err);
static __inline__ ITSK00144_2ScenarioEvent *ITSK00144_2ScenarioEvent_gen(Dz1Error *err) { ITSK00144_2ScenarioEvent v = ITSK00144_2ScenarioEvent_max; return ITSK00144_2ScenarioEvent_new(&v, err); }
static __inline__ void ITSK00144_2ScenarioEvent_del(ITSK00144_2ScenarioEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2ScenarioEvent_delAndSetNull(void *ptr)
{
	ITSK00144_2ScenarioEvent **p = (ITSK00144_2ScenarioEvent **)ptr;
	if (p != NULL) { ITSK00144_2ScenarioEvent_del(*p); *p = NULL; }
}
// ITSK00144_2ScenarioEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioServerState
typedef enum ITSK00144_2ScenarioServerState
{
	ITSK00144_2ScenarioServerState_initial,
	ITSK00144_2ScenarioServerState_wait_test_rsp_link_status,
	ITSK00144_2ScenarioServerState_wait_test_rsp_status,
	ITSK00144_2ScenarioServerState_wait_test_rsp_list,
	ITSK00144_2ScenarioServerState_wait_test_rsp_update_list,
	ITSK00144_2ScenarioServerState_wait_test_rsp_reset,
	ITSK00144_2ScenarioServerState_complete,
	ITSK00144_2ScenarioServerState_max
} ITSK00144_2ScenarioServerState;

DZ1_CPPLINK str_t ITSK00144_2ScenarioServerStateStrA(ITSK00144_2ScenarioServerState v);
DZ1_CPPLINK ITSK00144_2ScenarioServerState ITSK00144_2ScenarioServerStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2ScenarioServerStateStrW(ITSK00144_2ScenarioServerState v);
DZ1_CPPLINK ITSK00144_2ScenarioServerState ITSK00144_2ScenarioServerStateFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2ScenarioServerStateStr ITSK00144_2ScenarioServerStateStrW
#define ITSK00144_2ScenarioServerStateFromStr ITSK00144_2ScenarioServerStateFromStrW
#else // UNICODE
#define ITSK00144_2ScenarioServerStateStr ITSK00144_2ScenarioServerStateStrA
#define ITSK00144_2ScenarioServerStateFromStr ITSK00144_2ScenarioServerStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2ScenarioServerStateStr ITSK00144_2ScenarioServerStateStrA
#define ITSK00144_2ScenarioServerStateFromStr ITSK00144_2ScenarioServerStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ScenarioServerState *ITSK00144_2ScenarioServerState_new(ITSK00144_2ScenarioServerState *src, Dz1Error *err);
static __inline__ ITSK00144_2ScenarioServerState *ITSK00144_2ScenarioServerState_gen(Dz1Error *err) { ITSK00144_2ScenarioServerState v = ITSK00144_2ScenarioServerState_max; return ITSK00144_2ScenarioServerState_new(&v, err); }
#define ITSK00144_2ScenarioServerState_clone             ITSK00144_2ScenarioServerState_new
static __inline__ void ITSK00144_2ScenarioServerState_del(ITSK00144_2ScenarioServerState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2ScenarioServerState_delAndSetNull(void *ptr)
{
	ITSK00144_2ScenarioServerState **p = (ITSK00144_2ScenarioServerState **)ptr;
	if (p != NULL) { ITSK00144_2ScenarioServerState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ScenarioServerState_dump(ITSK00144_2ScenarioServerState *v, int tab);
// ITSK00144_2ScenarioServerState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioClientState
typedef enum ITSK00144_2ScenarioClientState
{
	ITSK00144_2ScenarioClientState_initial,
	ITSK00144_2ScenarioClientState_wait_req,
	ITSK00144_2ScenarioClientState_complete,
	ITSK00144_2ScenarioClientState_max
} ITSK00144_2ScenarioClientState;

DZ1_CPPLINK str_t ITSK00144_2ScenarioClientStateStrA(ITSK00144_2ScenarioClientState v);
DZ1_CPPLINK ITSK00144_2ScenarioClientState ITSK00144_2ScenarioClientStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2ScenarioClientStateStrW(ITSK00144_2ScenarioClientState v);
DZ1_CPPLINK ITSK00144_2ScenarioClientState ITSK00144_2ScenarioClientStateFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2ScenarioClientStateStr ITSK00144_2ScenarioClientStateStrW
#define ITSK00144_2ScenarioClientStateFromStr ITSK00144_2ScenarioClientStateFromStrW
#else // UNICODE
#define ITSK00144_2ScenarioClientStateStr ITSK00144_2ScenarioClientStateStrA
#define ITSK00144_2ScenarioClientStateFromStr ITSK00144_2ScenarioClientStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2ScenarioClientStateStr ITSK00144_2ScenarioClientStateStrA
#define ITSK00144_2ScenarioClientStateFromStr ITSK00144_2ScenarioClientStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ScenarioClientState *ITSK00144_2ScenarioClientState_new(ITSK00144_2ScenarioClientState *src, Dz1Error *err);
static __inline__ ITSK00144_2ScenarioClientState *ITSK00144_2ScenarioClientState_gen(Dz1Error *err) { ITSK00144_2ScenarioClientState v = ITSK00144_2ScenarioClientState_max; return ITSK00144_2ScenarioClientState_new(&v, err); }
#define ITSK00144_2ScenarioClientState_clone             ITSK00144_2ScenarioClientState_new
static __inline__ void ITSK00144_2ScenarioClientState_del(ITSK00144_2ScenarioClientState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2ScenarioClientState_delAndSetNull(void *ptr)
{
	ITSK00144_2ScenarioClientState **p = (ITSK00144_2ScenarioClientState **)ptr;
	if (p != NULL) { ITSK00144_2ScenarioClientState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ScenarioClientState_dump(ITSK00144_2ScenarioClientState *v, int tab);
// ITSK00144_2ScenarioClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK001442TestScenarioEnv
typedef struct ITSK001442TestScenarioEnv
{
	void					*tSelf;
	void					*tMain;
	Dz1JsonSpec				*spec;
	ITSK00144_2Session		*session;
	ITSK00144_2Scenario		*scenario;
	u8_t					 received_seq;
	u8_t					 send_seq;
	Dz1Str					 current_test;
	bool_t					 is_run;
	s32_t					 state;
	u32_t					 flags;
	u32_t					 testIdx;
} ITSK001442TestScenarioEnv;

DZ1_CPPLINK DZ1_DLLPORT ITSK001442TestScenarioEnv *ITSK001442TestScenarioEnv_new(void *tSelf, 
																				 void *tMain, 
																				 Dz1JsonSpec *spec, Dz1Error *err);
static __inline__ ITSK001442TestScenarioEnv *ITSK001442TestScenarioEnv_gen(Dz1Error *err) { return ITSK001442TestScenarioEnv_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioEnv_purge(ITSK001442TestScenarioEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioEnv_del(ITSK001442TestScenarioEnv *p);
static __inline__ void ITSK001442TestScenarioEnv_delAndSetNull(void *ptr)
{
	ITSK001442TestScenarioEnv **p = (ITSK001442TestScenarioEnv **)ptr;
	if (p) { ITSK001442TestScenarioEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442TestScenarioEnv_dump(ITSK001442TestScenarioEnv *p, int tab);
// ITSK001442TestScenarioEnv
////////////////////////////////////////////////////////////////////////////////

#endif
