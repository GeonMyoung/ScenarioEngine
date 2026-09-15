#ifndef _DZ1_TDC_ITSK00126V1_TEST_SCENARIO_ENV_H_
#define _DZ1_TDC_ITSK00126V1_TEST_SCENARIO_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1TestScenarioDef.h"
#include "Dz1SockUtilDef.h"
#include "Dz1JsonDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ClientSession
typedef struct Itsk00126v1ClientSession
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} Itsk00126v1ClientSession;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ClientSession *Itsk00126v1ClientSession_new(Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ Itsk00126v1ClientSession *Itsk00126v1ClientSession_gen(Dz1Error *err) { return Itsk00126v1ClientSession_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ClientSession_purge(Itsk00126v1ClientSession *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ClientSession_del(Itsk00126v1ClientSession *p);
static __inline__ void Itsk00126v1ClientSession_delAndSetNull(void *ptr)
{
	Itsk00126v1ClientSession **p = (Itsk00126v1ClientSession **)ptr;
	if (p) { Itsk00126v1ClientSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ClientSession_dump(Itsk00126v1ClientSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Itsk00126v1ClientSession_cmp(Itsk00126v1ClientSession *a, Itsk00126v1ClientSession *b); 
// Itsk00126v1ClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ServerSession
typedef struct Itsk00126v1ServerSession
{
	u32_t					 acceptor;
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} Itsk00126v1ServerSession;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ServerSession *Itsk00126v1ServerSession_new(u32_t acceptor, 
																			   Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ Itsk00126v1ServerSession *Itsk00126v1ServerSession_gen(Dz1Error *err) { return Itsk00126v1ServerSession_new(0, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ServerSession_purge(Itsk00126v1ServerSession *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ServerSession_del(Itsk00126v1ServerSession *p);
static __inline__ void Itsk00126v1ServerSession_delAndSetNull(void *ptr)
{
	Itsk00126v1ServerSession **p = (Itsk00126v1ServerSession **)ptr;
	if (p) { Itsk00126v1ServerSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ServerSession_dump(Itsk00126v1ServerSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Itsk00126v1ServerSession_cmp(Itsk00126v1ServerSession *a, Itsk00126v1ServerSession *b); 
// Itsk00126v1ServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1SessionPresent
typedef enum Itsk00126v1SessionPresent
{
	Itsk00126v1SessionPresent_client,
	Itsk00126v1SessionPresent_server,
	Itsk00126v1SessionPresent_max
} Itsk00126v1SessionPresent;

DZ1_CPPLINK str_t Itsk00126v1SessionPresentStrA(Itsk00126v1SessionPresent v);
DZ1_CPPLINK Itsk00126v1SessionPresent Itsk00126v1SessionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1SessionPresentStrW(Itsk00126v1SessionPresent v);
DZ1_CPPLINK Itsk00126v1SessionPresent Itsk00126v1SessionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1SessionPresentStr Itsk00126v1SessionPresentStrW
#define Itsk00126v1SessionPresentFromStr Itsk00126v1SessionPresentFromStrW
#else // UNICODE
#define Itsk00126v1SessionPresentStr Itsk00126v1SessionPresentStrA
#define Itsk00126v1SessionPresentFromStr Itsk00126v1SessionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1SessionPresentStr Itsk00126v1SessionPresentStrA
#define Itsk00126v1SessionPresentFromStr Itsk00126v1SessionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1SessionPresent *Itsk00126v1SessionPresent_new(Itsk00126v1SessionPresent *src, Dz1Error *err);
static __inline__ Itsk00126v1SessionPresent *Itsk00126v1SessionPresent_gen(Dz1Error *err) { Itsk00126v1SessionPresent v = Itsk00126v1SessionPresent_max; return Itsk00126v1SessionPresent_new(&v, err); }
static __inline__ void Itsk00126v1SessionPresent_del(Itsk00126v1SessionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1SessionPresent_delAndSetNull(void *ptr)
{
	Itsk00126v1SessionPresent **p = (Itsk00126v1SessionPresent **)ptr;
	if (p != NULL) { Itsk00126v1SessionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1SessionPresent_dump(Itsk00126v1SessionPresent *v, int tab);
// Itsk00126v1SessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1Session
typedef struct Itsk00126v1Session
{
	Itsk00126v1SessionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Itsk00126v1ClientSession	*client;
		Itsk00126v1ServerSession	*server;
	} x;
} Itsk00126v1Session;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1Session *Itsk00126v1Session_new(Itsk00126v1SessionPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v1Session *Itsk00126v1Session_gen(Dz1Error *err) { return Itsk00126v1Session_new(Itsk00126v1SessionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Session_purge(Itsk00126v1Session *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Session_del(Itsk00126v1Session *p);
static __inline__ void Itsk00126v1Session_delAndSetNull(void *ptr)
{
	Itsk00126v1Session **p = (Itsk00126v1Session **)ptr;
	if (p != NULL) { Itsk00126v1Session_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Session_dump(Itsk00126v1Session *p, int tab);
// Itsk00126v1Session
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ScenarioClientRole
typedef struct Itsk00126v1ScenarioClientRole
{
	Dz1Str		peer_ip;
	u16_t		peer_port;
} Itsk00126v1ScenarioClientRole;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ScenarioClientRole *Itsk00126v1ScenarioClientRole_new(Dz1Str peer_ip, 
																						 u16_t peer_port, Dz1Error *err);
static __inline__ Itsk00126v1ScenarioClientRole *Itsk00126v1ScenarioClientRole_gen(Dz1Error *err) { return Itsk00126v1ScenarioClientRole_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1ScenarioClientRole_copy(Itsk00126v1ScenarioClientRole *dst, Itsk00126v1ScenarioClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ScenarioClientRole *Itsk00126v1ScenarioClientRole_clone(Itsk00126v1ScenarioClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioClientRole_purge(Itsk00126v1ScenarioClientRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioClientRole_del(Itsk00126v1ScenarioClientRole *p);
static __inline__ void Itsk00126v1ScenarioClientRole_delAndSetNull(void *ptr)
{
	Itsk00126v1ScenarioClientRole **p = (Itsk00126v1ScenarioClientRole **)ptr;
	if (p) { Itsk00126v1ScenarioClientRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioClientRole_dump(Itsk00126v1ScenarioClientRole *p, int tab);
// Itsk00126v1ScenarioClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ScenarioServerRole
typedef struct Itsk00126v1ScenarioServerRole
{
	bool_t		local_port;
	Dz1Str		local_center_id;
	bool_t		test_iot_im_device_sttus_info;
	bool_t		test_iot_device_list_response_info;
	bool_t		test_iot_device_sttus_info;
	bool_t		test_safety_signal_list_response_info;
} Itsk00126v1ScenarioServerRole;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ScenarioServerRole *Itsk00126v1ScenarioServerRole_new(bool_t local_port, 
																						 Dz1Str local_center_id, 
																						 bool_t test_iot_im_device_sttus_info, 
																						 bool_t test_iot_device_list_response_info, 
																						 bool_t test_iot_device_sttus_info, 
																						 bool_t test_safety_signal_list_response_info, Dz1Error *err);
static __inline__ Itsk00126v1ScenarioServerRole *Itsk00126v1ScenarioServerRole_gen(Dz1Error *err) { return Itsk00126v1ScenarioServerRole_new(0, NULL, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1ScenarioServerRole_copy(Itsk00126v1ScenarioServerRole *dst, Itsk00126v1ScenarioServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ScenarioServerRole *Itsk00126v1ScenarioServerRole_clone(Itsk00126v1ScenarioServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioServerRole_purge(Itsk00126v1ScenarioServerRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioServerRole_del(Itsk00126v1ScenarioServerRole *p);
static __inline__ void Itsk00126v1ScenarioServerRole_delAndSetNull(void *ptr)
{
	Itsk00126v1ScenarioServerRole **p = (Itsk00126v1ScenarioServerRole **)ptr;
	if (p) { Itsk00126v1ScenarioServerRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioServerRole_dump(Itsk00126v1ScenarioServerRole *p, int tab);
// Itsk00126v1ScenarioServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ScenarioPresent
typedef enum Itsk00126v1ScenarioPresent
{
	Itsk00126v1ScenarioPresent_clientRole,
	Itsk00126v1ScenarioPresent_serverRole,
	Itsk00126v1ScenarioPresent_max
} Itsk00126v1ScenarioPresent;

DZ1_CPPLINK str_t Itsk00126v1ScenarioPresentStrA(Itsk00126v1ScenarioPresent v);
DZ1_CPPLINK Itsk00126v1ScenarioPresent Itsk00126v1ScenarioPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1ScenarioPresentStrW(Itsk00126v1ScenarioPresent v);
DZ1_CPPLINK Itsk00126v1ScenarioPresent Itsk00126v1ScenarioPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1ScenarioPresentStr Itsk00126v1ScenarioPresentStrW
#define Itsk00126v1ScenarioPresentFromStr Itsk00126v1ScenarioPresentFromStrW
#else // UNICODE
#define Itsk00126v1ScenarioPresentStr Itsk00126v1ScenarioPresentStrA
#define Itsk00126v1ScenarioPresentFromStr Itsk00126v1ScenarioPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1ScenarioPresentStr Itsk00126v1ScenarioPresentStrA
#define Itsk00126v1ScenarioPresentFromStr Itsk00126v1ScenarioPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ScenarioPresent *Itsk00126v1ScenarioPresent_new(Itsk00126v1ScenarioPresent *src, Dz1Error *err);
static __inline__ Itsk00126v1ScenarioPresent *Itsk00126v1ScenarioPresent_gen(Dz1Error *err) { Itsk00126v1ScenarioPresent v = Itsk00126v1ScenarioPresent_max; return Itsk00126v1ScenarioPresent_new(&v, err); }
#define Itsk00126v1ScenarioPresent_clone             Itsk00126v1ScenarioPresent_new
static __inline__ void Itsk00126v1ScenarioPresent_del(Itsk00126v1ScenarioPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1ScenarioPresent_delAndSetNull(void *ptr)
{
	Itsk00126v1ScenarioPresent **p = (Itsk00126v1ScenarioPresent **)ptr;
	if (p != NULL) { Itsk00126v1ScenarioPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioPresent_dump(Itsk00126v1ScenarioPresent *v, int tab);
// Itsk00126v1ScenarioPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1Scenario
typedef struct Itsk00126v1Scenario
{
	Itsk00126v1ScenarioPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Itsk00126v1ScenarioClientRole		*clientRole;
		Itsk00126v1ScenarioServerRole		*serverRole;
	} x;
} Itsk00126v1Scenario;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1Scenario *Itsk00126v1Scenario_new(Itsk00126v1ScenarioPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v1Scenario *Itsk00126v1Scenario_gen(Dz1Error *err) { return Itsk00126v1Scenario_new(Itsk00126v1ScenarioPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Itsk00126v1Scenario_copy(Itsk00126v1Scenario *dst, Itsk00126v1Scenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1Scenario *Itsk00126v1Scenario_clone(Itsk00126v1Scenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Scenario_purge(Itsk00126v1Scenario *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Scenario_del(Itsk00126v1Scenario *p);
static __inline__ void Itsk00126v1Scenario_delAndSetNull(void *ptr)
{
	Itsk00126v1Scenario **p = (Itsk00126v1Scenario **)ptr;
	if (p != NULL) { Itsk00126v1Scenario_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Scenario_dump(Itsk00126v1Scenario *p, int tab);
// Itsk00126v1Scenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ScenarioEvent
typedef enum Itsk00126v1ScenarioEvent
{
	Itsk00126v1ScenarioEvent_start,
	Itsk00126v1ScenarioEvent_auth,
	Itsk00126v1ScenarioEvent_trigger,
	Itsk00126v1ScenarioEvent_data,
	Itsk00126v1ScenarioEvent_disconnected,
	Itsk00126v1ScenarioEvent_max
} Itsk00126v1ScenarioEvent;

DZ1_CPPLINK str_t Itsk00126v1ScenarioEventStrA(Itsk00126v1ScenarioEvent v);
DZ1_CPPLINK Itsk00126v1ScenarioEvent Itsk00126v1ScenarioEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1ScenarioEventStrW(Itsk00126v1ScenarioEvent v);
DZ1_CPPLINK Itsk00126v1ScenarioEvent Itsk00126v1ScenarioEventFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1ScenarioEventStr Itsk00126v1ScenarioEventStrW
#define Itsk00126v1ScenarioEventFromStr Itsk00126v1ScenarioEventFromStrW
#else // UNICODE
#define Itsk00126v1ScenarioEventStr Itsk00126v1ScenarioEventStrA
#define Itsk00126v1ScenarioEventFromStr Itsk00126v1ScenarioEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1ScenarioEventStr Itsk00126v1ScenarioEventStrA
#define Itsk00126v1ScenarioEventFromStr Itsk00126v1ScenarioEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ScenarioEvent *Itsk00126v1ScenarioEvent_new(Itsk00126v1ScenarioEvent *src, Dz1Error *err);
static __inline__ Itsk00126v1ScenarioEvent *Itsk00126v1ScenarioEvent_gen(Dz1Error *err) { Itsk00126v1ScenarioEvent v = Itsk00126v1ScenarioEvent_max; return Itsk00126v1ScenarioEvent_new(&v, err); }
#define Itsk00126v1ScenarioEvent_clone             Itsk00126v1ScenarioEvent_new
static __inline__ void Itsk00126v1ScenarioEvent_del(Itsk00126v1ScenarioEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1ScenarioEvent_delAndSetNull(void *ptr)
{
	Itsk00126v1ScenarioEvent **p = (Itsk00126v1ScenarioEvent **)ptr;
	if (p != NULL) { Itsk00126v1ScenarioEvent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioEvent_dump(Itsk00126v1ScenarioEvent *v, int tab);
// Itsk00126v1ScenarioEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ScenarioServerState
typedef enum Itsk00126v1ScenarioServerState
{
	Itsk00126v1ScenarioServerState_initial,
	Itsk00126v1ScenarioServerState_wait_test_iot_im_device_sttus_info,
	Itsk00126v1ScenarioServerState_wait_test_iot_device_list_response_info,
	Itsk00126v1ScenarioServerState_wait_test_iot_device_sttus_info,
	Itsk00126v1ScenarioServerState_wait_test_safety_signal_list_response_info,
	Itsk00126v1ScenarioServerState_complete,
	Itsk00126v1ScenarioServerState_max
} Itsk00126v1ScenarioServerState;

DZ1_CPPLINK str_t Itsk00126v1ScenarioServerStateStrA(Itsk00126v1ScenarioServerState v);
DZ1_CPPLINK Itsk00126v1ScenarioServerState Itsk00126v1ScenarioServerStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1ScenarioServerStateStrW(Itsk00126v1ScenarioServerState v);
DZ1_CPPLINK Itsk00126v1ScenarioServerState Itsk00126v1ScenarioServerStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1ScenarioServerStateStr Itsk00126v1ScenarioServerStateStrW
#define Itsk00126v1ScenarioServerStateFromStr Itsk00126v1ScenarioServerStateFromStrW
#else // UNICODE
#define Itsk00126v1ScenarioServerStateStr Itsk00126v1ScenarioServerStateStrA
#define Itsk00126v1ScenarioServerStateFromStr Itsk00126v1ScenarioServerStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1ScenarioServerStateStr Itsk00126v1ScenarioServerStateStrA
#define Itsk00126v1ScenarioServerStateFromStr Itsk00126v1ScenarioServerStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ScenarioServerState *Itsk00126v1ScenarioServerState_new(Itsk00126v1ScenarioServerState *src, Dz1Error *err);
static __inline__ Itsk00126v1ScenarioServerState *Itsk00126v1ScenarioServerState_gen(Dz1Error *err) { Itsk00126v1ScenarioServerState v = Itsk00126v1ScenarioServerState_max; return Itsk00126v1ScenarioServerState_new(&v, err); }
#define Itsk00126v1ScenarioServerState_clone             Itsk00126v1ScenarioServerState_new
static __inline__ void Itsk00126v1ScenarioServerState_del(Itsk00126v1ScenarioServerState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1ScenarioServerState_delAndSetNull(void *ptr)
{
	Itsk00126v1ScenarioServerState **p = (Itsk00126v1ScenarioServerState **)ptr;
	if (p != NULL) { Itsk00126v1ScenarioServerState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioServerState_dump(Itsk00126v1ScenarioServerState *v, int tab);
// Itsk00126v1ScenarioServerState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ScenarioClientState
typedef enum Itsk00126v1ScenarioClientState
{
	Itsk00126v1ScenarioClientState_initial,
	Itsk00126v1ScenarioClientState_complete,
	Itsk00126v1ScenarioClientState_max
} Itsk00126v1ScenarioClientState;

DZ1_CPPLINK str_t Itsk00126v1ScenarioClientStateStrA(Itsk00126v1ScenarioClientState v);
DZ1_CPPLINK Itsk00126v1ScenarioClientState Itsk00126v1ScenarioClientStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1ScenarioClientStateStrW(Itsk00126v1ScenarioClientState v);
DZ1_CPPLINK Itsk00126v1ScenarioClientState Itsk00126v1ScenarioClientStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1ScenarioClientStateStr Itsk00126v1ScenarioClientStateStrW
#define Itsk00126v1ScenarioClientStateFromStr Itsk00126v1ScenarioClientStateFromStrW
#else // UNICODE
#define Itsk00126v1ScenarioClientStateStr Itsk00126v1ScenarioClientStateStrA
#define Itsk00126v1ScenarioClientStateFromStr Itsk00126v1ScenarioClientStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1ScenarioClientStateStr Itsk00126v1ScenarioClientStateStrA
#define Itsk00126v1ScenarioClientStateFromStr Itsk00126v1ScenarioClientStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ScenarioClientState *Itsk00126v1ScenarioClientState_new(Itsk00126v1ScenarioClientState *src, Dz1Error *err);
static __inline__ Itsk00126v1ScenarioClientState *Itsk00126v1ScenarioClientState_gen(Dz1Error *err) { Itsk00126v1ScenarioClientState v = Itsk00126v1ScenarioClientState_max; return Itsk00126v1ScenarioClientState_new(&v, err); }
#define Itsk00126v1ScenarioClientState_clone             Itsk00126v1ScenarioClientState_new
static __inline__ void Itsk00126v1ScenarioClientState_del(Itsk00126v1ScenarioClientState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1ScenarioClientState_delAndSetNull(void *ptr)
{
	Itsk00126v1ScenarioClientState **p = (Itsk00126v1ScenarioClientState **)ptr;
	if (p != NULL) { Itsk00126v1ScenarioClientState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ScenarioClientState_dump(Itsk00126v1ScenarioClientState *v, int tab);
// Itsk00126v1ScenarioClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1TestScenarioEnv
typedef struct Itsk00126V1TestScenarioEnv
{
	void					*tSelf;
	void					*tMain;
	Dz1JsonSpec				*spec;
	Itsk00126v1Session		*session;
	Itsk00126v1Scenario		*scenario;
	bool_t					 is_run;
	s32_t					 state;
	u32_t					 flags;
	u32_t					 testIdx;
	Dz1Str					 current_test;
} Itsk00126V1TestScenarioEnv;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V1TestScenarioEnv *Itsk00126V1TestScenarioEnv_new(void *tSelf, 
																				   void *tMain, 
																				   Dz1JsonSpec *spec, Dz1Error *err);
static __inline__ Itsk00126V1TestScenarioEnv *Itsk00126V1TestScenarioEnv_gen(Dz1Error *err) { return Itsk00126V1TestScenarioEnv_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1TestScenarioEnv_purge(Itsk00126V1TestScenarioEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1TestScenarioEnv_del(Itsk00126V1TestScenarioEnv *p);
static __inline__ void Itsk00126V1TestScenarioEnv_delAndSetNull(void *ptr)
{
	Itsk00126V1TestScenarioEnv **p = (Itsk00126V1TestScenarioEnv **)ptr;
	if (p) { Itsk00126V1TestScenarioEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1TestScenarioEnv_dump(Itsk00126V1TestScenarioEnv *p, int tab);
// Itsk00126V1TestScenarioEnv
////////////////////////////////////////////////////////////////////////////////

#endif
