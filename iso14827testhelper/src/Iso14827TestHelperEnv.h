#ifndef _DZ1_TDC_ISO14827_TEST_HELPER_ENV_H_
#define _DZ1_TDC_ISO14827_TEST_HELPER_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1JsonDef.h"
#include "Iso14827TestHelperDef.h"

////////////////////////////////////////////////////////////////////////////////
// Prj2TxDataCheckList
typedef struct Prj2TxDataCheckList
{
	bool_t		test_map;
	bool_t		test_spat;
	bool_t		test_sdsm;
} Prj2TxDataCheckList;

DZ1_CPPLINK DZ1_DLLPORT Prj2TxDataCheckList *Prj2TxDataCheckList_new(bool_t test_map, 
																	 bool_t test_spat, 
																	 bool_t test_sdsm, Dz1Error *err);
static __inline__ Prj2TxDataCheckList *Prj2TxDataCheckList_gen(Dz1Error *err) { return Prj2TxDataCheckList_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Prj2TxDataCheckList_copy(Prj2TxDataCheckList *dst, Prj2TxDataCheckList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Prj2TxDataCheckList *Prj2TxDataCheckList_clone(Prj2TxDataCheckList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Prj2TxDataCheckList_purge(Prj2TxDataCheckList *p);
DZ1_CPPLINK DZ1_DLLPORT void Prj2TxDataCheckList_del(Prj2TxDataCheckList *p);
static __inline__ void Prj2TxDataCheckList_delAndSetNull(void *ptr)
{
	Prj2TxDataCheckList **p = (Prj2TxDataCheckList **)ptr;
	if (p) { Prj2TxDataCheckList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Prj2TxDataCheckList_dump(Prj2TxDataCheckList *p, int tab);
// Prj2TxDataCheckList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prj2RxDataCheckList
typedef struct Prj2RxDataCheckList
{
	bool_t		test_pvd;
} Prj2RxDataCheckList;

DZ1_CPPLINK DZ1_DLLPORT Prj2RxDataCheckList *Prj2RxDataCheckList_new(bool_t test_pvd, Dz1Error *err);
static __inline__ Prj2RxDataCheckList *Prj2RxDataCheckList_gen(Dz1Error *err) { return Prj2RxDataCheckList_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Prj2RxDataCheckList_copy(Prj2RxDataCheckList *dst, Prj2RxDataCheckList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Prj2RxDataCheckList *Prj2RxDataCheckList_clone(Prj2RxDataCheckList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Prj2RxDataCheckList_purge(Prj2RxDataCheckList *p);
DZ1_CPPLINK DZ1_DLLPORT void Prj2RxDataCheckList_del(Prj2RxDataCheckList *p);
static __inline__ void Prj2RxDataCheckList_delAndSetNull(void *ptr)
{
	Prj2RxDataCheckList **p = (Prj2RxDataCheckList **)ptr;
	if (p) { Prj2RxDataCheckList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Prj2RxDataCheckList_dump(Prj2RxDataCheckList *p, int tab);
// Prj2RxDataCheckList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDataCheckListPresent
typedef enum Iso14827TestDataCheckListPresent
{
	Iso14827TestDataCheckListPresent_prj2_tx,
	Iso14827TestDataCheckListPresent_prj2_rx,
	Iso14827TestDataCheckListPresent_max
} Iso14827TestDataCheckListPresent;

DZ1_CPPLINK str_t Iso14827TestDataCheckListPresentStrA(Iso14827TestDataCheckListPresent v);
DZ1_CPPLINK Iso14827TestDataCheckListPresent Iso14827TestDataCheckListPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestDataCheckListPresentStrW(Iso14827TestDataCheckListPresent v);
DZ1_CPPLINK Iso14827TestDataCheckListPresent Iso14827TestDataCheckListPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestDataCheckListPresentStr Iso14827TestDataCheckListPresentStrW
#define Iso14827TestDataCheckListPresentFromStr Iso14827TestDataCheckListPresentFromStrW
#else // UNICODE
#define Iso14827TestDataCheckListPresentStr Iso14827TestDataCheckListPresentStrA
#define Iso14827TestDataCheckListPresentFromStr Iso14827TestDataCheckListPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestDataCheckListPresentStr Iso14827TestDataCheckListPresentStrA
#define Iso14827TestDataCheckListPresentFromStr Iso14827TestDataCheckListPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDataCheckListPresent *Iso14827TestDataCheckListPresent_new(Iso14827TestDataCheckListPresent *src, Dz1Error *err);
static __inline__ Iso14827TestDataCheckListPresent *Iso14827TestDataCheckListPresent_gen(Dz1Error *err) { Iso14827TestDataCheckListPresent v = Iso14827TestDataCheckListPresent_max; return Iso14827TestDataCheckListPresent_new(&v, err); }
#define Iso14827TestDataCheckListPresent_clone             Iso14827TestDataCheckListPresent_new
static __inline__ void Iso14827TestDataCheckListPresent_del(Iso14827TestDataCheckListPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestDataCheckListPresent_delAndSetNull(void *ptr)
{
	Iso14827TestDataCheckListPresent **p = (Iso14827TestDataCheckListPresent **)ptr;
	if (p != NULL) { Iso14827TestDataCheckListPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDataCheckListPresent_dump(Iso14827TestDataCheckListPresent *v, int tab);
// Iso14827TestDataCheckListPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDataCheckList
typedef struct Iso14827TestDataCheckList
{
	Iso14827TestDataCheckListPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Prj2TxDataCheckList		*prj2_tx;
		Prj2RxDataCheckList		*prj2_rx;
	} x;
} Iso14827TestDataCheckList;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDataCheckList *Iso14827TestDataCheckList_new(Iso14827TestDataCheckListPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827TestDataCheckList *Iso14827TestDataCheckList_gen(Dz1Error *err) { return Iso14827TestDataCheckList_new(Iso14827TestDataCheckListPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827TestDataCheckList_copy(Iso14827TestDataCheckList *dst, Iso14827TestDataCheckList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDataCheckList *Iso14827TestDataCheckList_clone(Iso14827TestDataCheckList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDataCheckList_purge(Iso14827TestDataCheckList *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDataCheckList_del(Iso14827TestDataCheckList *p);
static __inline__ void Iso14827TestDataCheckList_delAndSetNull(void *ptr)
{
	Iso14827TestDataCheckList **p = (Iso14827TestDataCheckList **)ptr;
	if (p != NULL) { Iso14827TestDataCheckList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDataCheckList_dump(Iso14827TestDataCheckList *p, int tab);
// Iso14827TestDataCheckList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestScenarioSetup
typedef struct Iso14827TestScenarioSetup
{
	Iso14827TestScenario	*scenario;
} Iso14827TestScenarioSetup;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestScenarioSetup *Iso14827TestScenarioSetup_new(Iso14827TestScenario *scenario, Dz1Error *err);
static __inline__ Iso14827TestScenarioSetup *Iso14827TestScenarioSetup_gen(Dz1Error *err) { return Iso14827TestScenarioSetup_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestScenarioSetup_copy(Iso14827TestScenarioSetup *dst, Iso14827TestScenarioSetup *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestScenarioSetup *Iso14827TestScenarioSetup_clone(Iso14827TestScenarioSetup *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestScenarioSetup_purge(Iso14827TestScenarioSetup *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestScenarioSetup_del(Iso14827TestScenarioSetup *p);
static __inline__ void Iso14827TestScenarioSetup_delAndSetNull(void *ptr)
{
	Iso14827TestScenarioSetup **p = (Iso14827TestScenarioSetup **)ptr;
	if (p) { Iso14827TestScenarioSetup_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestScenarioSetup_dump(Iso14827TestScenarioSetup *p, int tab);
// Iso14827TestScenarioSetup
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClient1State
typedef enum Iso14827TestClient1State
{
	Iso14827TestClient1State_initial,
	Iso14827TestClient1State_wait_initiate,
	Iso14827TestClient1State_wait_login_dup,
	Iso14827TestClient1State_wait_disconnect,
	Iso14827TestClient1State_wait_restart,
	Iso14827TestClient1State_wait_invalid_subs,
	Iso14827TestClient1State_wait_normal_subs,
	Iso14827TestClient1State_wait_subs_cancel,
	Iso14827TestClient1State_wait_deferred_ack,
	Iso14827TestClient1State_wait_terminate,
	Iso14827TestClient1State_complete,
	Iso14827TestClient1State_max
} Iso14827TestClient1State;

DZ1_CPPLINK str_t Iso14827TestClient1StateStrA(Iso14827TestClient1State v);
DZ1_CPPLINK Iso14827TestClient1State Iso14827TestClient1StateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestClient1StateStrW(Iso14827TestClient1State v);
DZ1_CPPLINK Iso14827TestClient1State Iso14827TestClient1StateFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestClient1StateStr Iso14827TestClient1StateStrW
#define Iso14827TestClient1StateFromStr Iso14827TestClient1StateFromStrW
#else // UNICODE
#define Iso14827TestClient1StateStr Iso14827TestClient1StateStrA
#define Iso14827TestClient1StateFromStr Iso14827TestClient1StateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestClient1StateStr Iso14827TestClient1StateStrA
#define Iso14827TestClient1StateFromStr Iso14827TestClient1StateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClient1State *Iso14827TestClient1State_new(Iso14827TestClient1State *src, Dz1Error *err);
static __inline__ Iso14827TestClient1State *Iso14827TestClient1State_gen(Dz1Error *err) { Iso14827TestClient1State v = Iso14827TestClient1State_max; return Iso14827TestClient1State_new(&v, err); }
static __inline__ void Iso14827TestClient1State_del(Iso14827TestClient1State *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestClient1State_delAndSetNull(void *ptr)
{
	Iso14827TestClient1State **p = (Iso14827TestClient1State **)ptr;
	if (p != NULL) { Iso14827TestClient1State_del(*p); *p = NULL; }
}
// Iso14827TestClient1State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClient2State
typedef enum Iso14827TestClient2State
{
	Iso14827TestClient2State_initial,
	Iso14827TestClient2State_connected,
	Iso14827TestClient2State_wait_total_test,
	Iso14827TestClient2State_wait_terminate,
	Iso14827TestClient2State_complete,
	Iso14827TestClient2State_max
} Iso14827TestClient2State;

DZ1_CPPLINK str_t Iso14827TestClient2StateStrA(Iso14827TestClient2State v);
DZ1_CPPLINK Iso14827TestClient2State Iso14827TestClient2StateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestClient2StateStrW(Iso14827TestClient2State v);
DZ1_CPPLINK Iso14827TestClient2State Iso14827TestClient2StateFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestClient2StateStr Iso14827TestClient2StateStrW
#define Iso14827TestClient2StateFromStr Iso14827TestClient2StateFromStrW
#else // UNICODE
#define Iso14827TestClient2StateStr Iso14827TestClient2StateStrA
#define Iso14827TestClient2StateFromStr Iso14827TestClient2StateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestClient2StateStr Iso14827TestClient2StateStrA
#define Iso14827TestClient2StateFromStr Iso14827TestClient2StateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClient2State *Iso14827TestClient2State_new(Iso14827TestClient2State *src, Dz1Error *err);
static __inline__ Iso14827TestClient2State *Iso14827TestClient2State_gen(Dz1Error *err) { Iso14827TestClient2State v = Iso14827TestClient2State_max; return Iso14827TestClient2State_new(&v, err); }
static __inline__ void Iso14827TestClient2State_del(Iso14827TestClient2State *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestClient2State_delAndSetNull(void *ptr)
{
	Iso14827TestClient2State **p = (Iso14827TestClient2State **)ptr;
	if (p != NULL) { Iso14827TestClient2State_del(*p); *p = NULL; }
}
// Iso14827TestClient2State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoClientState
typedef enum Iso14827TestDuoClientState
{
	Iso14827TestDuoClientState_initial,
	Iso14827TestDuoClientState_wait_duo_client1_established,
	Iso14827TestDuoClientState_wait_duo_subs_test,
	Iso14827TestDuoClientState_wait_duo_terminate,
	Iso14827TestDuoClientState_wait_terminate,
	Iso14827TestDuoClientState_complete,
	Iso14827TestDuoClientState_max
} Iso14827TestDuoClientState;

DZ1_CPPLINK str_t Iso14827TestDuoClientStateStrA(Iso14827TestDuoClientState v);
DZ1_CPPLINK Iso14827TestDuoClientState Iso14827TestDuoClientStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestDuoClientStateStrW(Iso14827TestDuoClientState v);
DZ1_CPPLINK Iso14827TestDuoClientState Iso14827TestDuoClientStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestDuoClientStateStr Iso14827TestDuoClientStateStrW
#define Iso14827TestDuoClientStateFromStr Iso14827TestDuoClientStateFromStrW
#else // UNICODE
#define Iso14827TestDuoClientStateStr Iso14827TestDuoClientStateStrA
#define Iso14827TestDuoClientStateFromStr Iso14827TestDuoClientStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestDuoClientStateStr Iso14827TestDuoClientStateStrA
#define Iso14827TestDuoClientStateFromStr Iso14827TestDuoClientStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDuoClientState *Iso14827TestDuoClientState_new(Iso14827TestDuoClientState *src, Dz1Error *err);
static __inline__ Iso14827TestDuoClientState *Iso14827TestDuoClientState_gen(Dz1Error *err) { Iso14827TestDuoClientState v = Iso14827TestDuoClientState_max; return Iso14827TestDuoClientState_new(&v, err); }
static __inline__ void Iso14827TestDuoClientState_del(Iso14827TestDuoClientState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestDuoClientState_delAndSetNull(void *ptr)
{
	Iso14827TestDuoClientState **p = (Iso14827TestDuoClientState **)ptr;
	if (p != NULL) { Iso14827TestDuoClientState_del(*p); *p = NULL; }
}
// Iso14827TestDuoClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServer1State
typedef enum Iso14827TestServer1State
{
	Iso14827TestServer1State_initial,
	Iso14827TestServer1State_wait_auth,
	Iso14827TestServer1State_wait_connected,
	Iso14827TestServer1State_established,
	Iso14827TestServer1State_wait_violated_pub,
	Iso14827TestServer1State_wait_disconnect,
	Iso14827TestServer1State_complete,
	Iso14827TestServer1State_max
} Iso14827TestServer1State;

DZ1_CPPLINK str_t Iso14827TestServer1StateStrA(Iso14827TestServer1State v);
DZ1_CPPLINK Iso14827TestServer1State Iso14827TestServer1StateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestServer1StateStrW(Iso14827TestServer1State v);
DZ1_CPPLINK Iso14827TestServer1State Iso14827TestServer1StateFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestServer1StateStr Iso14827TestServer1StateStrW
#define Iso14827TestServer1StateFromStr Iso14827TestServer1StateFromStrW
#else // UNICODE
#define Iso14827TestServer1StateStr Iso14827TestServer1StateStrA
#define Iso14827TestServer1StateFromStr Iso14827TestServer1StateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestServer1StateStr Iso14827TestServer1StateStrA
#define Iso14827TestServer1StateFromStr Iso14827TestServer1StateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServer1State *Iso14827TestServer1State_new(Iso14827TestServer1State *src, Dz1Error *err);
static __inline__ Iso14827TestServer1State *Iso14827TestServer1State_gen(Dz1Error *err) { Iso14827TestServer1State v = Iso14827TestServer1State_max; return Iso14827TestServer1State_new(&v, err); }
static __inline__ void Iso14827TestServer1State_del(Iso14827TestServer1State *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestServer1State_delAndSetNull(void *ptr)
{
	Iso14827TestServer1State **p = (Iso14827TestServer1State **)ptr;
	if (p != NULL) { Iso14827TestServer1State_del(*p); *p = NULL; }
}
// Iso14827TestServer1State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServer2State
typedef enum Iso14827TestServer2State
{
	Iso14827TestServer2State_initial,
	Iso14827TestServer2State_wait_auth,
	Iso14827TestServer2State_wait_connected,
	Iso14827TestServer2State_established,
	Iso14827TestServer2State_wait_timeout,
	Iso14827TestServer2State_wait_logout,
	Iso14827TestServer2State_complete,
	Iso14827TestServer2State_max
} Iso14827TestServer2State;

DZ1_CPPLINK str_t Iso14827TestServer2StateStrA(Iso14827TestServer2State v);
DZ1_CPPLINK Iso14827TestServer2State Iso14827TestServer2StateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestServer2StateStrW(Iso14827TestServer2State v);
DZ1_CPPLINK Iso14827TestServer2State Iso14827TestServer2StateFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestServer2StateStr Iso14827TestServer2StateStrW
#define Iso14827TestServer2StateFromStr Iso14827TestServer2StateFromStrW
#else // UNICODE
#define Iso14827TestServer2StateStr Iso14827TestServer2StateStrA
#define Iso14827TestServer2StateFromStr Iso14827TestServer2StateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestServer2StateStr Iso14827TestServer2StateStrA
#define Iso14827TestServer2StateFromStr Iso14827TestServer2StateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServer2State *Iso14827TestServer2State_new(Iso14827TestServer2State *src, Dz1Error *err);
static __inline__ Iso14827TestServer2State *Iso14827TestServer2State_gen(Dz1Error *err) { Iso14827TestServer2State v = Iso14827TestServer2State_max; return Iso14827TestServer2State_new(&v, err); }
static __inline__ void Iso14827TestServer2State_del(Iso14827TestServer2State *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestServer2State_delAndSetNull(void *ptr)
{
	Iso14827TestServer2State **p = (Iso14827TestServer2State **)ptr;
	if (p != NULL) { Iso14827TestServer2State_del(*p); *p = NULL; }
}
// Iso14827TestServer2State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServer3State
typedef enum Iso14827TestServer3State
{
	Iso14827TestServer3State_initial,
	Iso14827TestServer3State_wait_auth,
	Iso14827TestServer3State_wait_connected,
	Iso14827TestServer3State_established,
	Iso14827TestServer3State_wait_timeout,
	Iso14827TestServer3State_wait_disconnect,
	Iso14827TestServer3State_complete,
	Iso14827TestServer3State_max
} Iso14827TestServer3State;

DZ1_CPPLINK str_t Iso14827TestServer3StateStrA(Iso14827TestServer3State v);
DZ1_CPPLINK Iso14827TestServer3State Iso14827TestServer3StateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestServer3StateStrW(Iso14827TestServer3State v);
DZ1_CPPLINK Iso14827TestServer3State Iso14827TestServer3StateFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestServer3StateStr Iso14827TestServer3StateStrW
#define Iso14827TestServer3StateFromStr Iso14827TestServer3StateFromStrW
#else // UNICODE
#define Iso14827TestServer3StateStr Iso14827TestServer3StateStrA
#define Iso14827TestServer3StateFromStr Iso14827TestServer3StateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestServer3StateStr Iso14827TestServer3StateStrA
#define Iso14827TestServer3StateFromStr Iso14827TestServer3StateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServer3State *Iso14827TestServer3State_new(Iso14827TestServer3State *src, Dz1Error *err);
static __inline__ Iso14827TestServer3State *Iso14827TestServer3State_gen(Dz1Error *err) { Iso14827TestServer3State v = Iso14827TestServer3State_max; return Iso14827TestServer3State_new(&v, err); }
static __inline__ void Iso14827TestServer3State_del(Iso14827TestServer3State *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestServer3State_delAndSetNull(void *ptr)
{
	Iso14827TestServer3State **p = (Iso14827TestServer3State **)ptr;
	if (p != NULL) { Iso14827TestServer3State_del(*p); *p = NULL; }
}
// Iso14827TestServer3State
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoSessionServerState
typedef enum Iso14827TestDuoSessionServerState
{
	Iso14827TestDuoSessionServerState_initial,
	Iso14827TestDuoSessionServerState_wait_auth,
	Iso14827TestDuoSessionServerState_wait_connected,
	Iso14827TestDuoSessionServerState_established,
	Iso14827TestDuoSessionServerState_idle,
	Iso14827TestDuoSessionServerState_wait_logout,
	Iso14827TestDuoSessionServerState_complete,
	Iso14827TestDuoSessionServerState_max
} Iso14827TestDuoSessionServerState;

DZ1_CPPLINK str_t Iso14827TestDuoSessionServerStateStrA(Iso14827TestDuoSessionServerState v);
DZ1_CPPLINK Iso14827TestDuoSessionServerState Iso14827TestDuoSessionServerStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestDuoSessionServerStateStrW(Iso14827TestDuoSessionServerState v);
DZ1_CPPLINK Iso14827TestDuoSessionServerState Iso14827TestDuoSessionServerStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestDuoSessionServerStateStr Iso14827TestDuoSessionServerStateStrW
#define Iso14827TestDuoSessionServerStateFromStr Iso14827TestDuoSessionServerStateFromStrW
#else // UNICODE
#define Iso14827TestDuoSessionServerStateStr Iso14827TestDuoSessionServerStateStrA
#define Iso14827TestDuoSessionServerStateFromStr Iso14827TestDuoSessionServerStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestDuoSessionServerStateStr Iso14827TestDuoSessionServerStateStrA
#define Iso14827TestDuoSessionServerStateFromStr Iso14827TestDuoSessionServerStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDuoSessionServerState *Iso14827TestDuoSessionServerState_new(Iso14827TestDuoSessionServerState *src, Dz1Error *err);
static __inline__ Iso14827TestDuoSessionServerState *Iso14827TestDuoSessionServerState_gen(Dz1Error *err) { Iso14827TestDuoSessionServerState v = Iso14827TestDuoSessionServerState_max; return Iso14827TestDuoSessionServerState_new(&v, err); }
static __inline__ void Iso14827TestDuoSessionServerState_del(Iso14827TestDuoSessionServerState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestDuoSessionServerState_delAndSetNull(void *ptr)
{
	Iso14827TestDuoSessionServerState **p = (Iso14827TestDuoSessionServerState **)ptr;
	if (p != NULL) { Iso14827TestDuoSessionServerState_del(*p); *p = NULL; }
}
// Iso14827TestDuoSessionServerState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoSessionClientState
typedef enum Iso14827TestDuoSessionClientState
{
	Iso14827TestDuoSessionClientState_initial,
	Iso14827TestDuoSessionClientState_wait_initiate,
	Iso14827TestDuoSessionClientState_wait_heartbeat,
	Iso14827TestDuoSessionClientState_wait_pub_data,
	Iso14827TestDuoSessionClientState_idle,
	Iso14827TestDuoSessionClientState_wait_disconnect,
	Iso14827TestDuoSessionClientState_complete,
	Iso14827TestDuoSessionClientState_max
} Iso14827TestDuoSessionClientState;

DZ1_CPPLINK str_t Iso14827TestDuoSessionClientStateStrA(Iso14827TestDuoSessionClientState v);
DZ1_CPPLINK Iso14827TestDuoSessionClientState Iso14827TestDuoSessionClientStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestDuoSessionClientStateStrW(Iso14827TestDuoSessionClientState v);
DZ1_CPPLINK Iso14827TestDuoSessionClientState Iso14827TestDuoSessionClientStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestDuoSessionClientStateStr Iso14827TestDuoSessionClientStateStrW
#define Iso14827TestDuoSessionClientStateFromStr Iso14827TestDuoSessionClientStateFromStrW
#else // UNICODE
#define Iso14827TestDuoSessionClientStateStr Iso14827TestDuoSessionClientStateStrA
#define Iso14827TestDuoSessionClientStateFromStr Iso14827TestDuoSessionClientStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestDuoSessionClientStateStr Iso14827TestDuoSessionClientStateStrA
#define Iso14827TestDuoSessionClientStateFromStr Iso14827TestDuoSessionClientStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDuoSessionClientState *Iso14827TestDuoSessionClientState_new(Iso14827TestDuoSessionClientState *src, Dz1Error *err);
static __inline__ Iso14827TestDuoSessionClientState *Iso14827TestDuoSessionClientState_gen(Dz1Error *err) { Iso14827TestDuoSessionClientState v = Iso14827TestDuoSessionClientState_max; return Iso14827TestDuoSessionClientState_new(&v, err); }
static __inline__ void Iso14827TestDuoSessionClientState_del(Iso14827TestDuoSessionClientState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestDuoSessionClientState_delAndSetNull(void *ptr)
{
	Iso14827TestDuoSessionClientState **p = (Iso14827TestDuoSessionClientState **)ptr;
	if (p != NULL) { Iso14827TestDuoSessionClientState_del(*p); *p = NULL; }
}
// Iso14827TestDuoSessionClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientEvent
typedef enum Iso14827TestClientEvent
{
	Iso14827TestClientEvent_start,
	Iso14827TestClientEvent_trigger,
	Iso14827TestClientEvent_validate,
	Iso14827TestClientEvent_initiated = 200,
	Iso14827TestClientEvent_echo,
	Iso14827TestClientEvent_data,
	Iso14827TestClientEvent_data_ctrl,
	Iso14827TestClientEvent_terminate,
	Iso14827TestClientEvent_disconnected,
	Iso14827TestClientEvent_sub_received,
	Iso14827TestClientEvent_timeout = 1000,
	Iso14827TestClientEvent_max
} Iso14827TestClientEvent;

DZ1_CPPLINK str_t Iso14827TestClientEventStrA(Iso14827TestClientEvent v);
DZ1_CPPLINK Iso14827TestClientEvent Iso14827TestClientEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestClientEventStrW(Iso14827TestClientEvent v);
DZ1_CPPLINK Iso14827TestClientEvent Iso14827TestClientEventFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestClientEventStr Iso14827TestClientEventStrW
#define Iso14827TestClientEventFromStr Iso14827TestClientEventFromStrW
#else // UNICODE
#define Iso14827TestClientEventStr Iso14827TestClientEventStrA
#define Iso14827TestClientEventFromStr Iso14827TestClientEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestClientEventStr Iso14827TestClientEventStrA
#define Iso14827TestClientEventFromStr Iso14827TestClientEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientEvent *Iso14827TestClientEvent_new(Iso14827TestClientEvent *src, Dz1Error *err);
static __inline__ Iso14827TestClientEvent *Iso14827TestClientEvent_gen(Dz1Error *err) { Iso14827TestClientEvent v = Iso14827TestClientEvent_max; return Iso14827TestClientEvent_new(&v, err); }
static __inline__ void Iso14827TestClientEvent_del(Iso14827TestClientEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestClientEvent_delAndSetNull(void *ptr)
{
	Iso14827TestClientEvent **p = (Iso14827TestClientEvent **)ptr;
	if (p != NULL) { Iso14827TestClientEvent_del(*p); *p = NULL; }
}
// Iso14827TestClientEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerEvent
typedef enum Iso14827TestServerEvent
{
	Iso14827TestServerEvent_start,
	Iso14827TestServerEvent_validate,
	Iso14827TestServerEvent_auth = 100,
	Iso14827TestServerEvent_connected,
	Iso14827TestServerEvent_heartbeat,
	Iso14827TestServerEvent_req_single,
	Iso14827TestServerEvent_req_event_driven,
	Iso14827TestServerEvent_req_periodic,
	Iso14827TestServerEvent_data_start,
	Iso14827TestServerEvent_data_period,
	Iso14827TestServerEvent_data_stop,
	Iso14827TestServerEvent_pubdata_rejected,
	Iso14827TestServerEvent_req_expired,
	Iso14827TestServerEvent_logout,
	Iso14827TestServerEvent_pub_received,
	Iso14827TestServerEvent_timeout = 1000,
	Iso14827TestServerEvent_max
} Iso14827TestServerEvent;

DZ1_CPPLINK str_t Iso14827TestServerEventStrA(Iso14827TestServerEvent v);
DZ1_CPPLINK Iso14827TestServerEvent Iso14827TestServerEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestServerEventStrW(Iso14827TestServerEvent v);
DZ1_CPPLINK Iso14827TestServerEvent Iso14827TestServerEventFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestServerEventStr Iso14827TestServerEventStrW
#define Iso14827TestServerEventFromStr Iso14827TestServerEventFromStrW
#else // UNICODE
#define Iso14827TestServerEventStr Iso14827TestServerEventStrA
#define Iso14827TestServerEventFromStr Iso14827TestServerEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestServerEventStr Iso14827TestServerEventStrA
#define Iso14827TestServerEventFromStr Iso14827TestServerEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerEvent *Iso14827TestServerEvent_new(Iso14827TestServerEvent *src, Dz1Error *err);
static __inline__ Iso14827TestServerEvent *Iso14827TestServerEvent_gen(Dz1Error *err) { Iso14827TestServerEvent v = Iso14827TestServerEvent_max; return Iso14827TestServerEvent_new(&v, err); }
static __inline__ void Iso14827TestServerEvent_del(Iso14827TestServerEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestServerEvent_delAndSetNull(void *ptr)
{
	Iso14827TestServerEvent **p = (Iso14827TestServerEvent **)ptr;
	if (p != NULL) { Iso14827TestServerEvent_del(*p); *p = NULL; }
}
// Iso14827TestServerEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoSessionEvent
typedef enum Iso14827TestDuoSessionEvent
{
	Iso14827TestDuoSessionEvent_start,
	Iso14827TestDuoSessionEvent_trigger,
	Iso14827TestDuoSessionEvent_auth = 100,
	Iso14827TestDuoSessionEvent_connected,
	Iso14827TestDuoSessionEvent_heartbeat,
	Iso14827TestDuoSessionEvent_req_single,
	Iso14827TestDuoSessionEvent_req_event_driven,
	Iso14827TestDuoSessionEvent_req_periodic,
	Iso14827TestDuoSessionEvent_data_start,
	Iso14827TestDuoSessionEvent_data_period,
	Iso14827TestDuoSessionEvent_data_stop,
	Iso14827TestDuoSessionEvent_pubdata_rejected,
	Iso14827TestDuoSessionEvent_req_expired,
	Iso14827TestDuoSessionEvent_logout,
	Iso14827TestDuoSessionEvent_pub_received,
	Iso14827TestDuoSessionEvent_initiated = 200,
	Iso14827TestDuoSessionEvent_echo,
	Iso14827TestDuoSessionEvent_data,
	Iso14827TestDuoSessionEvent_data_ctrl,
	Iso14827TestDuoSessionEvent_terminate,
	Iso14827TestDuoSessionEvent_disconnected,
	Iso14827TestDuoSessionEvent_sub_received,
	Iso14827TestDuoSessionEvent_timeout = 1000,
	Iso14827TestDuoSessionEvent_max
} Iso14827TestDuoSessionEvent;

DZ1_CPPLINK str_t Iso14827TestDuoSessionEventStrA(Iso14827TestDuoSessionEvent v);
DZ1_CPPLINK Iso14827TestDuoSessionEvent Iso14827TestDuoSessionEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestDuoSessionEventStrW(Iso14827TestDuoSessionEvent v);
DZ1_CPPLINK Iso14827TestDuoSessionEvent Iso14827TestDuoSessionEventFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestDuoSessionEventStr Iso14827TestDuoSessionEventStrW
#define Iso14827TestDuoSessionEventFromStr Iso14827TestDuoSessionEventFromStrW
#else // UNICODE
#define Iso14827TestDuoSessionEventStr Iso14827TestDuoSessionEventStrA
#define Iso14827TestDuoSessionEventFromStr Iso14827TestDuoSessionEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestDuoSessionEventStr Iso14827TestDuoSessionEventStrA
#define Iso14827TestDuoSessionEventFromStr Iso14827TestDuoSessionEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDuoSessionEvent *Iso14827TestDuoSessionEvent_new(Iso14827TestDuoSessionEvent *src, Dz1Error *err);
static __inline__ Iso14827TestDuoSessionEvent *Iso14827TestDuoSessionEvent_gen(Dz1Error *err) { Iso14827TestDuoSessionEvent v = Iso14827TestDuoSessionEvent_max; return Iso14827TestDuoSessionEvent_new(&v, err); }
static __inline__ void Iso14827TestDuoSessionEvent_del(Iso14827TestDuoSessionEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestDuoSessionEvent_delAndSetNull(void *ptr)
{
	Iso14827TestDuoSessionEvent **p = (Iso14827TestDuoSessionEvent **)ptr;
	if (p != NULL) { Iso14827TestDuoSessionEvent_del(*p); *p = NULL; }
}
// Iso14827TestDuoSessionEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestSubType
typedef enum Iso14827TestSubType
{
	Iso14827TestSubType_single,
	Iso14827TestSubType_event_driven,
	Iso14827TestSubType_periodic,
	Iso14827TestSubType_max
} Iso14827TestSubType;

DZ1_CPPLINK str_t Iso14827TestSubTypeStrA(Iso14827TestSubType v);
DZ1_CPPLINK Iso14827TestSubType Iso14827TestSubTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestSubTypeStrW(Iso14827TestSubType v);
DZ1_CPPLINK Iso14827TestSubType Iso14827TestSubTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestSubTypeStr Iso14827TestSubTypeStrW
#define Iso14827TestSubTypeFromStr Iso14827TestSubTypeFromStrW
#else // UNICODE
#define Iso14827TestSubTypeStr Iso14827TestSubTypeStrA
#define Iso14827TestSubTypeFromStr Iso14827TestSubTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestSubTypeStr Iso14827TestSubTypeStrA
#define Iso14827TestSubTypeFromStr Iso14827TestSubTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestSubType *Iso14827TestSubType_new(Iso14827TestSubType *src, Dz1Error *err);
static __inline__ Iso14827TestSubType *Iso14827TestSubType_gen(Dz1Error *err) { Iso14827TestSubType v = Iso14827TestSubType_max; return Iso14827TestSubType_new(&v, err); }
static __inline__ void Iso14827TestSubType_del(Iso14827TestSubType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestSubType_delAndSetNull(void *ptr)
{
	Iso14827TestSubType **p = (Iso14827TestSubType **)ptr;
	if (p != NULL) { Iso14827TestSubType_del(*p); *p = NULL; }
}
// Iso14827TestSubType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestSubEntry
typedef struct Iso14827TestSubEntry
{
	Dz1Asn1UTF8Str			*peer;
	u32_t					 sid;
	Dz1Str					 oid;
	Iso14827TestSubType		 type;
	u32_t					 cnt;
} Iso14827TestSubEntry;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestSubEntry *Iso14827TestSubEntry_new(Dz1Asn1UTF8Str *peer, 
																	   u32_t sid, 
																	   Dz1Str oid, 
																	   Iso14827TestSubType type, Dz1Error *err);
static __inline__ Iso14827TestSubEntry *Iso14827TestSubEntry_gen(Dz1Error *err) { return Iso14827TestSubEntry_new(NULL, 0, NULL, Iso14827TestSubType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestSubEntry_copy(Iso14827TestSubEntry *dst, Iso14827TestSubEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestSubEntry *Iso14827TestSubEntry_clone(Iso14827TestSubEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestSubEntry_purge(Iso14827TestSubEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestSubEntry_del(Iso14827TestSubEntry *p);
static __inline__ void Iso14827TestSubEntry_delAndSetNull(void *ptr)
{
	Iso14827TestSubEntry **p = (Iso14827TestSubEntry **)ptr;
	if (p) { Iso14827TestSubEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestSubEntry_dump(Iso14827TestSubEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Iso14827TestSubEntry_cmp(Iso14827TestSubEntry *a, Iso14827TestSubEntry *b); 
// Iso14827TestSubEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestSubList
typedef struct Iso14827TestSubList
{
	void *storage;
	unsigned int (*count)(struct Iso14827TestSubList *p);
	Dz1Error (*travel)(struct Iso14827TestSubList *p, Dz1Error (*func)(void *ptr, Iso14827TestSubEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Iso14827TestSubList *p, Dz1Error (*func)(void *ptr, Iso14827TestSubEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Iso14827TestSubList *p, Dz1Error (*func)(void *ptr, Iso14827TestSubEntry *entry), void *ptr);
	Iso14827TestSubEntry **(*get_array)(struct Iso14827TestSubList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Iso14827TestSubList *p, Iso14827TestSubEntry *data);
	bool_t (*remove)(struct Iso14827TestSubList *p, Iso14827TestSubEntry *key);
	Iso14827TestSubEntry *(*extract)(struct Iso14827TestSubList *p, Iso14827TestSubEntry *key);
	Iso14827TestSubEntry *(*find)(struct Iso14827TestSubList *p, Iso14827TestSubEntry *key);
	Iso14827TestSubEntry *(*getHead)(struct Iso14827TestSubList *p);
	int (*cmp)(Iso14827TestSubEntry *a, Iso14827TestSubEntry *b);
} Iso14827TestSubList;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestSubList *Iso14827TestSubList_new(Dz1Error *err);
static __inline__ Iso14827TestSubList *Iso14827TestSubList_gen(Dz1Error *err) { return Iso14827TestSubList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestSubList *Iso14827TestSubList_clone(Iso14827TestSubList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestSubList_purge(Iso14827TestSubList *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestSubList_del(Iso14827TestSubList *p);
static __inline__ void Iso14827TestSubList_delAndSetNull(void *ptr)
{
	Iso14827TestSubList **p = (Iso14827TestSubList **)ptr;
	if (p != NULL) { Iso14827TestSubList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestSubList_dump(Iso14827TestSubList *p, int tab);

// Iso14827TestSubList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperEnv
typedef struct Iso14827TestHelperEnv
{
	void							*tSelf;
	void							*t14827;
	void							*tMain;
	Dz1JsonSpec						*spec;
	Iso14827TestScenario			*scenario;
	bool_t							 is_run;
	s32_t							 state;
	u32_t							 flags;
	Dz1Asn1Codec					 selected_codec;
	Dz1Asn1Codec					 selected_codec_duo;
	Dz1Asn1OctetStr					*user;
	Dz1SockAddr						*server_addr;
	Iso14827TestClientAccount		*primary_acc;
	Iso14827TestClientAccount		*secondary_acc;
	SubscribeSpecList				*test_subs;
	SubscribeSpecList				*test_subs2;
	u32_t							 test_subs_id;
	Iso14827TestSubList				*subs_reg;
	Iso14827TestSubList				*subs_reg2;
	Iso14827TestDataCheckList		*check_list;
	Dz1Str							 current_test;
	u32_t							 testIdx;
	u64_t							 hb_cnt;
} Iso14827TestHelperEnv;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperEnv *Iso14827TestHelperEnv_new(void *tSelf, 
																		 void *t14827_ref, 
																		 void *tMain, 
																		 Dz1JsonSpec *spec, 
																		 SubscribeSpecList *test_subs, 
																		 Iso14827TestSubList *subs_reg, 
																		 Iso14827TestSubList *subs_reg2, Dz1Error *err);
static __inline__ Iso14827TestHelperEnv *Iso14827TestHelperEnv_gen(Dz1Error *err) { return Iso14827TestHelperEnv_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperEnv_purge(Iso14827TestHelperEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperEnv_del(Iso14827TestHelperEnv *p);
static __inline__ void Iso14827TestHelperEnv_delAndSetNull(void *ptr)
{
	Iso14827TestHelperEnv **p = (Iso14827TestHelperEnv **)ptr;
	if (p) { Iso14827TestHelperEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperEnv_dump(Iso14827TestHelperEnv *p, int tab);
// Iso14827TestHelperEnv
////////////////////////////////////////////////////////////////////////////////

#endif
