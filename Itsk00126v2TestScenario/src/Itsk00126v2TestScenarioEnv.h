#ifndef _DZ1_TDC_ITSK00126V2_TEST_SCENARIO_ENV_H_
#define _DZ1_TDC_ITSK00126V2_TEST_SCENARIO_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v2TestScenarioDef.h"
#include "Dz1SockUtilDef.h"
#include "Dz1JsonDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ClientSession
typedef struct Itsk00126v2ClientSession
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} Itsk00126v2ClientSession;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ClientSession *Itsk00126v2ClientSession_new(Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ Itsk00126v2ClientSession *Itsk00126v2ClientSession_gen(Dz1Error *err) { return Itsk00126v2ClientSession_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ClientSession_purge(Itsk00126v2ClientSession *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ClientSession_del(Itsk00126v2ClientSession *p);
static __inline__ void Itsk00126v2ClientSession_delAndSetNull(void *ptr)
{
	Itsk00126v2ClientSession **p = (Itsk00126v2ClientSession **)ptr;
	if (p) { Itsk00126v2ClientSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ClientSession_dump(Itsk00126v2ClientSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Itsk00126v2ClientSession_cmp(Itsk00126v2ClientSession *a, Itsk00126v2ClientSession *b); 
// Itsk00126v2ClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ServerSession
typedef struct Itsk00126v2ServerSession
{
	u32_t					 acceptor;
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} Itsk00126v2ServerSession;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ServerSession *Itsk00126v2ServerSession_new(u32_t acceptor, 
																			   Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ Itsk00126v2ServerSession *Itsk00126v2ServerSession_gen(Dz1Error *err) { return Itsk00126v2ServerSession_new(0, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ServerSession_purge(Itsk00126v2ServerSession *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ServerSession_del(Itsk00126v2ServerSession *p);
static __inline__ void Itsk00126v2ServerSession_delAndSetNull(void *ptr)
{
	Itsk00126v2ServerSession **p = (Itsk00126v2ServerSession **)ptr;
	if (p) { Itsk00126v2ServerSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ServerSession_dump(Itsk00126v2ServerSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Itsk00126v2ServerSession_cmp(Itsk00126v2ServerSession *a, Itsk00126v2ServerSession *b); 
// Itsk00126v2ServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2SessionPresent
typedef enum Itsk00126v2SessionPresent
{
	Itsk00126v2SessionPresent_client,
	Itsk00126v2SessionPresent_server,
	Itsk00126v2SessionPresent_max
} Itsk00126v2SessionPresent;

DZ1_CPPLINK str_t Itsk00126v2SessionPresentStrA(Itsk00126v2SessionPresent v);
DZ1_CPPLINK Itsk00126v2SessionPresent Itsk00126v2SessionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v2SessionPresentStrW(Itsk00126v2SessionPresent v);
DZ1_CPPLINK Itsk00126v2SessionPresent Itsk00126v2SessionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v2SessionPresentStr Itsk00126v2SessionPresentStrW
#define Itsk00126v2SessionPresentFromStr Itsk00126v2SessionPresentFromStrW
#else // UNICODE
#define Itsk00126v2SessionPresentStr Itsk00126v2SessionPresentStrA
#define Itsk00126v2SessionPresentFromStr Itsk00126v2SessionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v2SessionPresentStr Itsk00126v2SessionPresentStrA
#define Itsk00126v2SessionPresentFromStr Itsk00126v2SessionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2SessionPresent *Itsk00126v2SessionPresent_new(Itsk00126v2SessionPresent *src, Dz1Error *err);
static __inline__ Itsk00126v2SessionPresent *Itsk00126v2SessionPresent_gen(Dz1Error *err) { Itsk00126v2SessionPresent v = Itsk00126v2SessionPresent_max; return Itsk00126v2SessionPresent_new(&v, err); }
static __inline__ void Itsk00126v2SessionPresent_del(Itsk00126v2SessionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v2SessionPresent_delAndSetNull(void *ptr)
{
	Itsk00126v2SessionPresent **p = (Itsk00126v2SessionPresent **)ptr;
	if (p != NULL) { Itsk00126v2SessionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2SessionPresent_dump(Itsk00126v2SessionPresent *v, int tab);
// Itsk00126v2SessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2Session
typedef struct Itsk00126v2Session
{
	Itsk00126v2SessionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Itsk00126v2ClientSession	*client;
		Itsk00126v2ServerSession	*server;
	} x;
} Itsk00126v2Session;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2Session *Itsk00126v2Session_new(Itsk00126v2SessionPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v2Session *Itsk00126v2Session_gen(Dz1Error *err) { return Itsk00126v2Session_new(Itsk00126v2SessionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2Session_purge(Itsk00126v2Session *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2Session_del(Itsk00126v2Session *p);
static __inline__ void Itsk00126v2Session_delAndSetNull(void *ptr)
{
	Itsk00126v2Session **p = (Itsk00126v2Session **)ptr;
	if (p != NULL) { Itsk00126v2Session_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2Session_dump(Itsk00126v2Session *p, int tab);
// Itsk00126v2Session
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioClientRole
typedef struct Itsk00126v2ScenarioClientRole
{
	Dz1Str		peer_ip;
	u16_t		peer_port;
} Itsk00126v2ScenarioClientRole;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ScenarioClientRole *Itsk00126v2ScenarioClientRole_new(Dz1Str peer_ip, 
																						 u16_t peer_port, Dz1Error *err);
static __inline__ Itsk00126v2ScenarioClientRole *Itsk00126v2ScenarioClientRole_gen(Dz1Error *err) { return Itsk00126v2ScenarioClientRole_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2ScenarioClientRole_copy(Itsk00126v2ScenarioClientRole *dst, Itsk00126v2ScenarioClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ScenarioClientRole *Itsk00126v2ScenarioClientRole_clone(Itsk00126v2ScenarioClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioClientRole_purge(Itsk00126v2ScenarioClientRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioClientRole_del(Itsk00126v2ScenarioClientRole *p);
static __inline__ void Itsk00126v2ScenarioClientRole_delAndSetNull(void *ptr)
{
	Itsk00126v2ScenarioClientRole **p = (Itsk00126v2ScenarioClientRole **)ptr;
	if (p) { Itsk00126v2ScenarioClientRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioClientRole_dump(Itsk00126v2ScenarioClientRole *p, int tab);
// Itsk00126v2ScenarioClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioServerRole
typedef struct Itsk00126v2ScenarioServerRole
{
	bool_t		local_port;
	Dz1Str		iot_im_device_id;
	bool_t		test_iot_im_device_sttus_info;
	bool_t		test_iot_device_list_response_info;
	bool_t		test_iot_device_sttus_info;
} Itsk00126v2ScenarioServerRole;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ScenarioServerRole *Itsk00126v2ScenarioServerRole_new(bool_t local_port, 
																						 Dz1Str iot_im_device_id, 
																						 bool_t test_iot_im_device_sttus_info, 
																						 bool_t test_iot_device_list_response_info, 
																						 bool_t test_iot_device_sttus_info, Dz1Error *err);
static __inline__ Itsk00126v2ScenarioServerRole *Itsk00126v2ScenarioServerRole_gen(Dz1Error *err) { return Itsk00126v2ScenarioServerRole_new(0, NULL, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2ScenarioServerRole_copy(Itsk00126v2ScenarioServerRole *dst, Itsk00126v2ScenarioServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ScenarioServerRole *Itsk00126v2ScenarioServerRole_clone(Itsk00126v2ScenarioServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioServerRole_purge(Itsk00126v2ScenarioServerRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioServerRole_del(Itsk00126v2ScenarioServerRole *p);
static __inline__ void Itsk00126v2ScenarioServerRole_delAndSetNull(void *ptr)
{
	Itsk00126v2ScenarioServerRole **p = (Itsk00126v2ScenarioServerRole **)ptr;
	if (p) { Itsk00126v2ScenarioServerRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioServerRole_dump(Itsk00126v2ScenarioServerRole *p, int tab);
// Itsk00126v2ScenarioServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioPresent
typedef enum Itsk00126v2ScenarioPresent
{
	Itsk00126v2ScenarioPresent_clientRole,
	Itsk00126v2ScenarioPresent_serverRole,
	Itsk00126v2ScenarioPresent_max
} Itsk00126v2ScenarioPresent;

DZ1_CPPLINK str_t Itsk00126v2ScenarioPresentStrA(Itsk00126v2ScenarioPresent v);
DZ1_CPPLINK Itsk00126v2ScenarioPresent Itsk00126v2ScenarioPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v2ScenarioPresentStrW(Itsk00126v2ScenarioPresent v);
DZ1_CPPLINK Itsk00126v2ScenarioPresent Itsk00126v2ScenarioPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v2ScenarioPresentStr Itsk00126v2ScenarioPresentStrW
#define Itsk00126v2ScenarioPresentFromStr Itsk00126v2ScenarioPresentFromStrW
#else // UNICODE
#define Itsk00126v2ScenarioPresentStr Itsk00126v2ScenarioPresentStrA
#define Itsk00126v2ScenarioPresentFromStr Itsk00126v2ScenarioPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v2ScenarioPresentStr Itsk00126v2ScenarioPresentStrA
#define Itsk00126v2ScenarioPresentFromStr Itsk00126v2ScenarioPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ScenarioPresent *Itsk00126v2ScenarioPresent_new(Itsk00126v2ScenarioPresent *src, Dz1Error *err);
static __inline__ Itsk00126v2ScenarioPresent *Itsk00126v2ScenarioPresent_gen(Dz1Error *err) { Itsk00126v2ScenarioPresent v = Itsk00126v2ScenarioPresent_max; return Itsk00126v2ScenarioPresent_new(&v, err); }
#define Itsk00126v2ScenarioPresent_clone             Itsk00126v2ScenarioPresent_new
static __inline__ void Itsk00126v2ScenarioPresent_del(Itsk00126v2ScenarioPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v2ScenarioPresent_delAndSetNull(void *ptr)
{
	Itsk00126v2ScenarioPresent **p = (Itsk00126v2ScenarioPresent **)ptr;
	if (p != NULL) { Itsk00126v2ScenarioPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioPresent_dump(Itsk00126v2ScenarioPresent *v, int tab);
// Itsk00126v2ScenarioPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2Scenario
typedef struct Itsk00126v2Scenario
{
	Itsk00126v2ScenarioPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Itsk00126v2ScenarioClientRole		*clientRole;
		Itsk00126v2ScenarioServerRole		*serverRole;
	} x;
} Itsk00126v2Scenario;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2Scenario *Itsk00126v2Scenario_new(Itsk00126v2ScenarioPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v2Scenario *Itsk00126v2Scenario_gen(Dz1Error *err) { return Itsk00126v2Scenario_new(Itsk00126v2ScenarioPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Itsk00126v2Scenario_copy(Itsk00126v2Scenario *dst, Itsk00126v2Scenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2Scenario *Itsk00126v2Scenario_clone(Itsk00126v2Scenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2Scenario_purge(Itsk00126v2Scenario *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2Scenario_del(Itsk00126v2Scenario *p);
static __inline__ void Itsk00126v2Scenario_delAndSetNull(void *ptr)
{
	Itsk00126v2Scenario **p = (Itsk00126v2Scenario **)ptr;
	if (p != NULL) { Itsk00126v2Scenario_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2Scenario_dump(Itsk00126v2Scenario *p, int tab);
// Itsk00126v2Scenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioEvent
typedef enum Itsk00126v2ScenarioEvent
{
	Itsk00126v2ScenarioEvent_start,
	Itsk00126v2ScenarioEvent_auth,
	Itsk00126v2ScenarioEvent_trigger,
	Itsk00126v2ScenarioEvent_data,
	Itsk00126v2ScenarioEvent_disconnected,
	Itsk00126v2ScenarioEvent_max
} Itsk00126v2ScenarioEvent;

DZ1_CPPLINK str_t Itsk00126v2ScenarioEventStrA(Itsk00126v2ScenarioEvent v);
DZ1_CPPLINK Itsk00126v2ScenarioEvent Itsk00126v2ScenarioEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v2ScenarioEventStrW(Itsk00126v2ScenarioEvent v);
DZ1_CPPLINK Itsk00126v2ScenarioEvent Itsk00126v2ScenarioEventFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v2ScenarioEventStr Itsk00126v2ScenarioEventStrW
#define Itsk00126v2ScenarioEventFromStr Itsk00126v2ScenarioEventFromStrW
#else // UNICODE
#define Itsk00126v2ScenarioEventStr Itsk00126v2ScenarioEventStrA
#define Itsk00126v2ScenarioEventFromStr Itsk00126v2ScenarioEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v2ScenarioEventStr Itsk00126v2ScenarioEventStrA
#define Itsk00126v2ScenarioEventFromStr Itsk00126v2ScenarioEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ScenarioEvent *Itsk00126v2ScenarioEvent_new(Itsk00126v2ScenarioEvent *src, Dz1Error *err);
static __inline__ Itsk00126v2ScenarioEvent *Itsk00126v2ScenarioEvent_gen(Dz1Error *err) { Itsk00126v2ScenarioEvent v = Itsk00126v2ScenarioEvent_max; return Itsk00126v2ScenarioEvent_new(&v, err); }
#define Itsk00126v2ScenarioEvent_clone             Itsk00126v2ScenarioEvent_new
static __inline__ void Itsk00126v2ScenarioEvent_del(Itsk00126v2ScenarioEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v2ScenarioEvent_delAndSetNull(void *ptr)
{
	Itsk00126v2ScenarioEvent **p = (Itsk00126v2ScenarioEvent **)ptr;
	if (p != NULL) { Itsk00126v2ScenarioEvent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioEvent_dump(Itsk00126v2ScenarioEvent *v, int tab);
// Itsk00126v2ScenarioEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioServerState
typedef enum Itsk00126v2ScenarioServerState
{
	Itsk00126v2ScenarioServerState_initial,
	Itsk00126v2ScenarioServerState_wait_test_iot_im_device_sttus_info,
	Itsk00126v2ScenarioServerState_wait_test_iot_device_list_response_info,
	Itsk00126v2ScenarioServerState_wait_test_iot_device_sttus_info,
	Itsk00126v2ScenarioServerState_complete,
	Itsk00126v2ScenarioServerState_max
} Itsk00126v2ScenarioServerState;

DZ1_CPPLINK str_t Itsk00126v2ScenarioServerStateStrA(Itsk00126v2ScenarioServerState v);
DZ1_CPPLINK Itsk00126v2ScenarioServerState Itsk00126v2ScenarioServerStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v2ScenarioServerStateStrW(Itsk00126v2ScenarioServerState v);
DZ1_CPPLINK Itsk00126v2ScenarioServerState Itsk00126v2ScenarioServerStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v2ScenarioServerStateStr Itsk00126v2ScenarioServerStateStrW
#define Itsk00126v2ScenarioServerStateFromStr Itsk00126v2ScenarioServerStateFromStrW
#else // UNICODE
#define Itsk00126v2ScenarioServerStateStr Itsk00126v2ScenarioServerStateStrA
#define Itsk00126v2ScenarioServerStateFromStr Itsk00126v2ScenarioServerStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v2ScenarioServerStateStr Itsk00126v2ScenarioServerStateStrA
#define Itsk00126v2ScenarioServerStateFromStr Itsk00126v2ScenarioServerStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ScenarioServerState *Itsk00126v2ScenarioServerState_new(Itsk00126v2ScenarioServerState *src, Dz1Error *err);
static __inline__ Itsk00126v2ScenarioServerState *Itsk00126v2ScenarioServerState_gen(Dz1Error *err) { Itsk00126v2ScenarioServerState v = Itsk00126v2ScenarioServerState_max; return Itsk00126v2ScenarioServerState_new(&v, err); }
#define Itsk00126v2ScenarioServerState_clone             Itsk00126v2ScenarioServerState_new
static __inline__ void Itsk00126v2ScenarioServerState_del(Itsk00126v2ScenarioServerState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v2ScenarioServerState_delAndSetNull(void *ptr)
{
	Itsk00126v2ScenarioServerState **p = (Itsk00126v2ScenarioServerState **)ptr;
	if (p != NULL) { Itsk00126v2ScenarioServerState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioServerState_dump(Itsk00126v2ScenarioServerState *v, int tab);
// Itsk00126v2ScenarioServerState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioClientState
typedef enum Itsk00126v2ScenarioClientState
{
	Itsk00126v2ScenarioClientState_initial,
	Itsk00126v2ScenarioClientState_complete,
	Itsk00126v2ScenarioClientState_max
} Itsk00126v2ScenarioClientState;

DZ1_CPPLINK str_t Itsk00126v2ScenarioClientStateStrA(Itsk00126v2ScenarioClientState v);
DZ1_CPPLINK Itsk00126v2ScenarioClientState Itsk00126v2ScenarioClientStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v2ScenarioClientStateStrW(Itsk00126v2ScenarioClientState v);
DZ1_CPPLINK Itsk00126v2ScenarioClientState Itsk00126v2ScenarioClientStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v2ScenarioClientStateStr Itsk00126v2ScenarioClientStateStrW
#define Itsk00126v2ScenarioClientStateFromStr Itsk00126v2ScenarioClientStateFromStrW
#else // UNICODE
#define Itsk00126v2ScenarioClientStateStr Itsk00126v2ScenarioClientStateStrA
#define Itsk00126v2ScenarioClientStateFromStr Itsk00126v2ScenarioClientStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v2ScenarioClientStateStr Itsk00126v2ScenarioClientStateStrA
#define Itsk00126v2ScenarioClientStateFromStr Itsk00126v2ScenarioClientStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ScenarioClientState *Itsk00126v2ScenarioClientState_new(Itsk00126v2ScenarioClientState *src, Dz1Error *err);
static __inline__ Itsk00126v2ScenarioClientState *Itsk00126v2ScenarioClientState_gen(Dz1Error *err) { Itsk00126v2ScenarioClientState v = Itsk00126v2ScenarioClientState_max; return Itsk00126v2ScenarioClientState_new(&v, err); }
#define Itsk00126v2ScenarioClientState_clone             Itsk00126v2ScenarioClientState_new
static __inline__ void Itsk00126v2ScenarioClientState_del(Itsk00126v2ScenarioClientState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v2ScenarioClientState_delAndSetNull(void *ptr)
{
	Itsk00126v2ScenarioClientState **p = (Itsk00126v2ScenarioClientState **)ptr;
	if (p != NULL) { Itsk00126v2ScenarioClientState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ScenarioClientState_dump(Itsk00126v2ScenarioClientState *v, int tab);
// Itsk00126v2ScenarioClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V2TestScenarioEnv
typedef struct Itsk00126V2TestScenarioEnv
{
	void					*tSelf;
	void					*tMain;
	Dz1JsonSpec				*spec;
	Itsk00126v2Session		*session;
	Itsk00126v2Scenario		*scenario;
	bool_t					 is_run;
	s32_t					 state;
	u32_t					 flags;
	u32_t					 testIdx;
	Dz1Str					 current_test;
} Itsk00126V2TestScenarioEnv;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V2TestScenarioEnv *Itsk00126V2TestScenarioEnv_new(void *tSelf, 
																				   void *tMain, 
																				   Dz1JsonSpec *spec, Dz1Error *err);
static __inline__ Itsk00126V2TestScenarioEnv *Itsk00126V2TestScenarioEnv_gen(Dz1Error *err) { return Itsk00126V2TestScenarioEnv_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V2TestScenarioEnv_purge(Itsk00126V2TestScenarioEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V2TestScenarioEnv_del(Itsk00126V2TestScenarioEnv *p);
static __inline__ void Itsk00126V2TestScenarioEnv_delAndSetNull(void *ptr)
{
	Itsk00126V2TestScenarioEnv **p = (Itsk00126V2TestScenarioEnv **)ptr;
	if (p) { Itsk00126V2TestScenarioEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V2TestScenarioEnv_dump(Itsk00126V2TestScenarioEnv *p, int tab);
// Itsk00126V2TestScenarioEnv
////////////////////////////////////////////////////////////////////////////////

#endif
