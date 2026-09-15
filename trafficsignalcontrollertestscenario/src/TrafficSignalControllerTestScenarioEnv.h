#ifndef _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_ENV_H_
#define _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestScenarioDef.h"
#include "TrafficSignalControllerTestMsgDef.h"
#include "TrafficSignalControllerTestMsgFrameDef.h"
#include "Dz1JsonDef.h"
#include "Dz1SockUtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerSession
typedef struct TrafficSignalControllerSession
{
	u32_t					 acceptor;
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} TrafficSignalControllerSession;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerSession *TrafficSignalControllerSession_new(u32_t acceptor, 
																						   Dz1SockAddr *peer, 
																						   Dz1SockAddr *local, 
																						   Dz1TcpClientSocket *sock, 
																						   Dz1ElasticBuf *rx_buf, 
																						   Dz1Stream *rx_stream, 
																						   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ TrafficSignalControllerSession *TrafficSignalControllerSession_gen(Dz1Error *err) { return TrafficSignalControllerSession_new(0, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerSession_purge(TrafficSignalControllerSession *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerSession_del(TrafficSignalControllerSession *p);
static __inline__ void TrafficSignalControllerSession_delAndSetNull(void *ptr)
{
	TrafficSignalControllerSession **p = (TrafficSignalControllerSession **)ptr;
	if (p) { TrafficSignalControllerSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerSession_dump(TrafficSignalControllerSession *p, int tab);
// TrafficSignalControllerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerScenario
typedef struct TrafficSignalControllerScenario
{
	TrafficSignalControllerTestMsgFrame		*received;
	bool_t									 result;
	Dz1Str									 ip;
	u16_t									 port;
	u8_t									 cross_id;
	Dz1Str									 req_str;
	u8_t									 eam_type;
} TrafficSignalControllerScenario;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerScenario *TrafficSignalControllerScenario_new(TrafficSignalControllerTestMsgFrame *received, 
																							 bool_t result, 
																							 Dz1Str ip, 
																							 u16_t port, 
																							 u8_t cross_id, 
																							 Dz1Str req_str, 
																							 u8_t eam_type, Dz1Error *err);
static __inline__ TrafficSignalControllerScenario *TrafficSignalControllerScenario_gen(Dz1Error *err) { return TrafficSignalControllerScenario_new(NULL, 0, NULL, 0, 0, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerScenario_copy(TrafficSignalControllerScenario *dst, TrafficSignalControllerScenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerScenario *TrafficSignalControllerScenario_clone(TrafficSignalControllerScenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerScenario_purge(TrafficSignalControllerScenario *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerScenario_del(TrafficSignalControllerScenario *p);
static __inline__ void TrafficSignalControllerScenario_delAndSetNull(void *ptr)
{
	TrafficSignalControllerScenario **p = (TrafficSignalControllerScenario **)ptr;
	if (p) { TrafficSignalControllerScenario_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerScenario_dump(TrafficSignalControllerScenario *p, int tab);
// TrafficSignalControllerScenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerScenarioEvent
typedef enum TrafficSignalControllerScenarioEvent
{
	TrafficSignalControllerScenarioEvent_start,
	TrafficSignalControllerScenarioEvent_auth,
	TrafficSignalControllerScenarioEvent_trigger,
	TrafficSignalControllerScenarioEvent_data,
	TrafficSignalControllerScenarioEvent_validate,
	TrafficSignalControllerScenarioEvent_disconnected,
	TrafficSignalControllerScenarioEvent_max
} TrafficSignalControllerScenarioEvent;

DZ1_CPPLINK str_t TrafficSignalControllerScenarioEventStrA(TrafficSignalControllerScenarioEvent v);
DZ1_CPPLINK TrafficSignalControllerScenarioEvent TrafficSignalControllerScenarioEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TrafficSignalControllerScenarioEventStrW(TrafficSignalControllerScenarioEvent v);
DZ1_CPPLINK TrafficSignalControllerScenarioEvent TrafficSignalControllerScenarioEventFromStrW(wstr_t str);
#ifdef UNICODE
#define TrafficSignalControllerScenarioEventStr TrafficSignalControllerScenarioEventStrW
#define TrafficSignalControllerScenarioEventFromStr TrafficSignalControllerScenarioEventFromStrW
#else // UNICODE
#define TrafficSignalControllerScenarioEventStr TrafficSignalControllerScenarioEventStrA
#define TrafficSignalControllerScenarioEventFromStr TrafficSignalControllerScenarioEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TrafficSignalControllerScenarioEventStr TrafficSignalControllerScenarioEventStrA
#define TrafficSignalControllerScenarioEventFromStr TrafficSignalControllerScenarioEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerScenarioEvent *TrafficSignalControllerScenarioEvent_new(TrafficSignalControllerScenarioEvent *src, Dz1Error *err);
static __inline__ TrafficSignalControllerScenarioEvent *TrafficSignalControllerScenarioEvent_gen(Dz1Error *err) { TrafficSignalControllerScenarioEvent v = TrafficSignalControllerScenarioEvent_max; return TrafficSignalControllerScenarioEvent_new(&v, err); }
#define TrafficSignalControllerScenarioEvent_clone             TrafficSignalControllerScenarioEvent_new
static __inline__ void TrafficSignalControllerScenarioEvent_del(TrafficSignalControllerScenarioEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TrafficSignalControllerScenarioEvent_delAndSetNull(void *ptr)
{
	TrafficSignalControllerScenarioEvent **p = (TrafficSignalControllerScenarioEvent **)ptr;
	if (p != NULL) { TrafficSignalControllerScenarioEvent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerScenarioEvent_dump(TrafficSignalControllerScenarioEvent *v, int tab);
// TrafficSignalControllerScenarioEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerScenarioState
typedef enum TrafficSignalControllerScenarioState
{
	TrafficSignalControllerScenarioState_initial,
	TrafficSignalControllerScenarioState_wait_test,
	TrafficSignalControllerScenarioState_complete,
	TrafficSignalControllerScenarioState_max
} TrafficSignalControllerScenarioState;

DZ1_CPPLINK str_t TrafficSignalControllerScenarioStateStrA(TrafficSignalControllerScenarioState v);
DZ1_CPPLINK TrafficSignalControllerScenarioState TrafficSignalControllerScenarioStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TrafficSignalControllerScenarioStateStrW(TrafficSignalControllerScenarioState v);
DZ1_CPPLINK TrafficSignalControllerScenarioState TrafficSignalControllerScenarioStateFromStrW(wstr_t str);
#ifdef UNICODE
#define TrafficSignalControllerScenarioStateStr TrafficSignalControllerScenarioStateStrW
#define TrafficSignalControllerScenarioStateFromStr TrafficSignalControllerScenarioStateFromStrW
#else // UNICODE
#define TrafficSignalControllerScenarioStateStr TrafficSignalControllerScenarioStateStrA
#define TrafficSignalControllerScenarioStateFromStr TrafficSignalControllerScenarioStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TrafficSignalControllerScenarioStateStr TrafficSignalControllerScenarioStateStrA
#define TrafficSignalControllerScenarioStateFromStr TrafficSignalControllerScenarioStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerScenarioState *TrafficSignalControllerScenarioState_new(TrafficSignalControllerScenarioState *src, Dz1Error *err);
static __inline__ TrafficSignalControllerScenarioState *TrafficSignalControllerScenarioState_gen(Dz1Error *err) { TrafficSignalControllerScenarioState v = TrafficSignalControllerScenarioState_max; return TrafficSignalControllerScenarioState_new(&v, err); }
static __inline__ void TrafficSignalControllerScenarioState_del(TrafficSignalControllerScenarioState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TrafficSignalControllerScenarioState_delAndSetNull(void *ptr)
{
	TrafficSignalControllerScenarioState **p = (TrafficSignalControllerScenarioState **)ptr;
	if (p != NULL) { TrafficSignalControllerScenarioState_del(*p); *p = NULL; }
}
// TrafficSignalControllerScenarioState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestScenarioEnv
typedef struct TrafficSignalControllerTestScenarioEnv
{
	void								*tSelf;
	void								*tMain;
	Dz1JsonSpec							*spec;
	TrafficSignalControllerSession		*session;
	TrafficSignalControllerScenario		*scenario;
	u32_t								 testIdx;
	s32_t								 state;
	u32_t								 flags;
	bool_t								 is_run;
	bool_t								 is_r29;
} TrafficSignalControllerTestScenarioEnv;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestScenarioEnv *TrafficSignalControllerTestScenarioEnv_new(void *tSelf, 
																										   void *tMain, 
																										   Dz1JsonSpec *spec, Dz1Error *err);
static __inline__ TrafficSignalControllerTestScenarioEnv *TrafficSignalControllerTestScenarioEnv_gen(Dz1Error *err) { return TrafficSignalControllerTestScenarioEnv_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioEnv_purge(TrafficSignalControllerTestScenarioEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioEnv_del(TrafficSignalControllerTestScenarioEnv *p);
static __inline__ void TrafficSignalControllerTestScenarioEnv_delAndSetNull(void *ptr)
{
	TrafficSignalControllerTestScenarioEnv **p = (TrafficSignalControllerTestScenarioEnv **)ptr;
	if (p) { TrafficSignalControllerTestScenarioEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestScenarioEnv_dump(TrafficSignalControllerTestScenarioEnv *p, int tab);
// TrafficSignalControllerTestScenarioEnv
////////////////////////////////////////////////////////////////////////////////

#endif
