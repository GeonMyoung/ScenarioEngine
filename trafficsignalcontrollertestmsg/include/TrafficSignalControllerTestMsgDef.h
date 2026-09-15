#ifndef _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_DEF_H_
#define _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingRcCmd
typedef enum CrossControlRingRcCmd
{
	CrossControlRingRcCmd_none,
	CrossControlRingRcCmd_EndPhase1,
	CrossControlRingRcCmd_EndPhase2,
	CrossControlRingRcCmd_EndPhase3,
	CrossControlRingRcCmd_EndPhase4,
	CrossControlRingRcCmd_EndPhase5,
	CrossControlRingRcCmd_EndPhase6,
	CrossControlRingRcCmd_EndPhase7,
	CrossControlRingRcCmd_EndPhase8,
	CrossControlRingRcCmd_max
} CrossControlRingRcCmd;

DZ1_CPPLINK str_t CrossControlRingRcCmdStrA(CrossControlRingRcCmd v);
DZ1_CPPLINK CrossControlRingRcCmd CrossControlRingRcCmdFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t CrossControlRingRcCmdStrW(CrossControlRingRcCmd v);
DZ1_CPPLINK CrossControlRingRcCmd CrossControlRingRcCmdFromStrW(wstr_t str);
#ifdef UNICODE
#define CrossControlRingRcCmdStr CrossControlRingRcCmdStrW
#define CrossControlRingRcCmdFromStr CrossControlRingRcCmdFromStrW
#else // UNICODE
#define CrossControlRingRcCmdStr CrossControlRingRcCmdStrA
#define CrossControlRingRcCmdFromStr CrossControlRingRcCmdFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define CrossControlRingRcCmdStr CrossControlRingRcCmdStrA
#define CrossControlRingRcCmdFromStr CrossControlRingRcCmdFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT CrossControlRingRcCmd *CrossControlRingRcCmd_new(CrossControlRingRcCmd *src, Dz1Error *err);
static __inline__ CrossControlRingRcCmd *CrossControlRingRcCmd_gen(Dz1Error *err) { CrossControlRingRcCmd v = CrossControlRingRcCmd_max; return CrossControlRingRcCmd_new(&v, err); }
static __inline__ void CrossControlRingRcCmd_del(CrossControlRingRcCmd *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void CrossControlRingRcCmd_delAndSetNull(void *ptr)
{
	CrossControlRingRcCmd **p = (CrossControlRingRcCmd **)ptr;
	if (p != NULL) { CrossControlRingRcCmd_del(*p); *p = NULL; }
}
// CrossControlRingRcCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingRcDualCmd
typedef struct CrossControlRingRcDualCmd
{
	CrossControlRingRcCmd		ring_b;
	CrossControlRingRcCmd		ring_a;
} CrossControlRingRcDualCmd;

DZ1_CPPLINK DZ1_DLLPORT CrossControlRingRcDualCmd *CrossControlRingRcDualCmd_new(CrossControlRingRcCmd ring_b, 
																				 CrossControlRingRcCmd ring_a, Dz1Error *err);
static __inline__ CrossControlRingRcDualCmd *CrossControlRingRcDualCmd_gen(Dz1Error *err) { return CrossControlRingRcDualCmd_new(CrossControlRingRcCmd_max, CrossControlRingRcCmd_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CrossControlRingRcDualCmd_copy(CrossControlRingRcDualCmd *dst, CrossControlRingRcDualCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossControlRingRcDualCmd *CrossControlRingRcDualCmd_clone(CrossControlRingRcDualCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlRingRcDualCmd_purge(CrossControlRingRcDualCmd *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlRingRcDualCmd_del(CrossControlRingRcDualCmd *p);
static __inline__ void CrossControlRingRcDualCmd_delAndSetNull(void *ptr)
{
	CrossControlRingRcDualCmd **p = (CrossControlRingRcDualCmd **)ptr;
	if (p) { CrossControlRingRcDualCmd_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossControlRingRcDualCmd_dump(CrossControlRingRcDualCmd *p, int tab);
// CrossControlRingRcDualCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingLcCmd
typedef enum CrossControlRingLcCmd
{
	CrossControlRingLcCmd_none,
	CrossControlRingLcCmd_SetPhase1,
	CrossControlRingLcCmd_SetPhase2,
	CrossControlRingLcCmd_SetPhase3,
	CrossControlRingLcCmd_SetPhase4,
	CrossControlRingLcCmd_SetPhase5,
	CrossControlRingLcCmd_SetPhase6,
	CrossControlRingLcCmd_SetPhase7,
	CrossControlRingLcCmd_SetPhase8,
	CrossControlRingLcCmd_SetPhaseNext,
	CrossControlRingLcCmd_max
} CrossControlRingLcCmd;

DZ1_CPPLINK str_t CrossControlRingLcCmdStrA(CrossControlRingLcCmd v);
DZ1_CPPLINK CrossControlRingLcCmd CrossControlRingLcCmdFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t CrossControlRingLcCmdStrW(CrossControlRingLcCmd v);
DZ1_CPPLINK CrossControlRingLcCmd CrossControlRingLcCmdFromStrW(wstr_t str);
#ifdef UNICODE
#define CrossControlRingLcCmdStr CrossControlRingLcCmdStrW
#define CrossControlRingLcCmdFromStr CrossControlRingLcCmdFromStrW
#else // UNICODE
#define CrossControlRingLcCmdStr CrossControlRingLcCmdStrA
#define CrossControlRingLcCmdFromStr CrossControlRingLcCmdFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define CrossControlRingLcCmdStr CrossControlRingLcCmdStrA
#define CrossControlRingLcCmdFromStr CrossControlRingLcCmdFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT CrossControlRingLcCmd *CrossControlRingLcCmd_new(CrossControlRingLcCmd *src, Dz1Error *err);
static __inline__ CrossControlRingLcCmd *CrossControlRingLcCmd_gen(Dz1Error *err) { CrossControlRingLcCmd v = CrossControlRingLcCmd_max; return CrossControlRingLcCmd_new(&v, err); }
static __inline__ void CrossControlRingLcCmd_del(CrossControlRingLcCmd *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void CrossControlRingLcCmd_delAndSetNull(void *ptr)
{
	CrossControlRingLcCmd **p = (CrossControlRingLcCmd **)ptr;
	if (p != NULL) { CrossControlRingLcCmd_del(*p); *p = NULL; }
}
// CrossControlRingLcCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingLcDualCmd
typedef struct CrossControlRingLcDualCmd
{
	CrossControlRingLcCmd		ring_b;
	CrossControlRingLcCmd		ring_a;
} CrossControlRingLcDualCmd;

DZ1_CPPLINK DZ1_DLLPORT CrossControlRingLcDualCmd *CrossControlRingLcDualCmd_new(CrossControlRingLcCmd ring_b, 
																				 CrossControlRingLcCmd ring_a, Dz1Error *err);
static __inline__ CrossControlRingLcDualCmd *CrossControlRingLcDualCmd_gen(Dz1Error *err) { return CrossControlRingLcDualCmd_new(CrossControlRingLcCmd_max, CrossControlRingLcCmd_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CrossControlRingLcDualCmd_copy(CrossControlRingLcDualCmd *dst, CrossControlRingLcDualCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossControlRingLcDualCmd *CrossControlRingLcDualCmd_clone(CrossControlRingLcDualCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlRingLcDualCmd_purge(CrossControlRingLcDualCmd *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlRingLcDualCmd_del(CrossControlRingLcDualCmd *p);
static __inline__ void CrossControlRingLcDualCmd_delAndSetNull(void *ptr)
{
	CrossControlRingLcDualCmd **p = (CrossControlRingLcDualCmd **)ptr;
	if (p) { CrossControlRingLcDualCmd_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossControlRingLcDualCmd_dump(CrossControlRingLcDualCmd *p, int tab);
// CrossControlRingLcDualCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlSingleCmdPresent
typedef enum CrossControlSingleCmdPresent
{
	CrossControlSingleCmdPresent_lc_fixed = 0,
	CrossControlSingleCmdPresent_lc_control = 16,
	CrossControlSingleCmdPresent_lc_actuation = 18,
	CrossControlSingleCmdPresent_rc_actuation = 20,
	CrossControlSingleCmdPresent_rc_online = 22,
	CrossControlSingleCmdPresent_max
} CrossControlSingleCmdPresent;

DZ1_CPPLINK str_t CrossControlSingleCmdPresentStrA(CrossControlSingleCmdPresent v);
DZ1_CPPLINK CrossControlSingleCmdPresent CrossControlSingleCmdPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t CrossControlSingleCmdPresentStrW(CrossControlSingleCmdPresent v);
DZ1_CPPLINK CrossControlSingleCmdPresent CrossControlSingleCmdPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define CrossControlSingleCmdPresentStr CrossControlSingleCmdPresentStrW
#define CrossControlSingleCmdPresentFromStr CrossControlSingleCmdPresentFromStrW
#else // UNICODE
#define CrossControlSingleCmdPresentStr CrossControlSingleCmdPresentStrA
#define CrossControlSingleCmdPresentFromStr CrossControlSingleCmdPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define CrossControlSingleCmdPresentStr CrossControlSingleCmdPresentStrA
#define CrossControlSingleCmdPresentFromStr CrossControlSingleCmdPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT CrossControlSingleCmdPresent *CrossControlSingleCmdPresent_new(CrossControlSingleCmdPresent *src, Dz1Error *err);
static __inline__ CrossControlSingleCmdPresent *CrossControlSingleCmdPresent_gen(Dz1Error *err) { CrossControlSingleCmdPresent v = CrossControlSingleCmdPresent_max; return CrossControlSingleCmdPresent_new(&v, err); }
#define CrossControlSingleCmdPresent_clone             CrossControlSingleCmdPresent_new
static __inline__ void CrossControlSingleCmdPresent_del(CrossControlSingleCmdPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void CrossControlSingleCmdPresent_delAndSetNull(void *ptr)
{
	CrossControlSingleCmdPresent **p = (CrossControlSingleCmdPresent **)ptr;
	if (p != NULL) { CrossControlSingleCmdPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossControlSingleCmdPresent_dump(CrossControlSingleCmdPresent *v, int tab);
// CrossControlSingleCmdPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlSingleCmd
typedef struct CrossControlSingleCmd
{
	CrossControlSingleCmdPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		CrossControlRingLcCmd		lc_fixed;
		CrossControlRingLcCmd		lc_control;
		CrossControlRingLcCmd		lc_actuation;
		CrossControlRingRcCmd		rc_actuation;
		CrossControlRingRcCmd		rc_online;
	} x;
} CrossControlSingleCmd;

DZ1_CPPLINK DZ1_DLLPORT CrossControlSingleCmd *CrossControlSingleCmd_new(CrossControlSingleCmdPresent present, void *ptr, Dz1Error *err);
static __inline__ CrossControlSingleCmd *CrossControlSingleCmd_gen(Dz1Error *err) { return CrossControlSingleCmd_new(CrossControlSingleCmdPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  CrossControlSingleCmd_copy(CrossControlSingleCmd *dst, CrossControlSingleCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossControlSingleCmd *CrossControlSingleCmd_clone(CrossControlSingleCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlSingleCmd_purge(CrossControlSingleCmd *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlSingleCmd_del(CrossControlSingleCmd *p);
static __inline__ void CrossControlSingleCmd_delAndSetNull(void *ptr)
{
	CrossControlSingleCmd **p = (CrossControlSingleCmd **)ptr;
	if (p != NULL) { CrossControlSingleCmd_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossControlSingleCmd_dump(CrossControlSingleCmd *p, int tab);
// CrossControlSingleCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlDualCmdPresent
typedef enum CrossControlDualCmdPresent
{
	CrossControlDualCmdPresent_lc_fixed = 0,
	CrossControlDualCmdPresent_lc_control = 16,
	CrossControlDualCmdPresent_lc_actuation = 18,
	CrossControlDualCmdPresent_rc_actuation = 20,
	CrossControlDualCmdPresent_rc_online = 22,
	CrossControlDualCmdPresent_max
} CrossControlDualCmdPresent;

DZ1_CPPLINK str_t CrossControlDualCmdPresentStrA(CrossControlDualCmdPresent v);
DZ1_CPPLINK CrossControlDualCmdPresent CrossControlDualCmdPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t CrossControlDualCmdPresentStrW(CrossControlDualCmdPresent v);
DZ1_CPPLINK CrossControlDualCmdPresent CrossControlDualCmdPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define CrossControlDualCmdPresentStr CrossControlDualCmdPresentStrW
#define CrossControlDualCmdPresentFromStr CrossControlDualCmdPresentFromStrW
#else // UNICODE
#define CrossControlDualCmdPresentStr CrossControlDualCmdPresentStrA
#define CrossControlDualCmdPresentFromStr CrossControlDualCmdPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define CrossControlDualCmdPresentStr CrossControlDualCmdPresentStrA
#define CrossControlDualCmdPresentFromStr CrossControlDualCmdPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT CrossControlDualCmdPresent *CrossControlDualCmdPresent_new(CrossControlDualCmdPresent *src, Dz1Error *err);
static __inline__ CrossControlDualCmdPresent *CrossControlDualCmdPresent_gen(Dz1Error *err) { CrossControlDualCmdPresent v = CrossControlDualCmdPresent_max; return CrossControlDualCmdPresent_new(&v, err); }
#define CrossControlDualCmdPresent_clone             CrossControlDualCmdPresent_new
static __inline__ void CrossControlDualCmdPresent_del(CrossControlDualCmdPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void CrossControlDualCmdPresent_delAndSetNull(void *ptr)
{
	CrossControlDualCmdPresent **p = (CrossControlDualCmdPresent **)ptr;
	if (p != NULL) { CrossControlDualCmdPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossControlDualCmdPresent_dump(CrossControlDualCmdPresent *v, int tab);
// CrossControlDualCmdPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlDualCmd
typedef struct CrossControlDualCmd
{
	CrossControlDualCmdPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		CrossControlRingLcDualCmd		*lc_fixed;
		CrossControlRingLcDualCmd		*lc_control;
		CrossControlRingLcDualCmd		*lc_actuation;
		CrossControlRingRcDualCmd		*rc_actuation;
		CrossControlRingRcDualCmd		*rc_online;
	} x;
} CrossControlDualCmd;

DZ1_CPPLINK DZ1_DLLPORT CrossControlDualCmd *CrossControlDualCmd_new(CrossControlDualCmdPresent present, void *ptr, Dz1Error *err);
static __inline__ CrossControlDualCmd *CrossControlDualCmd_gen(Dz1Error *err) { return CrossControlDualCmd_new(CrossControlDualCmdPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  CrossControlDualCmd_copy(CrossControlDualCmd *dst, CrossControlDualCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossControlDualCmd *CrossControlDualCmd_clone(CrossControlDualCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlDualCmd_purge(CrossControlDualCmd *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlDualCmd_del(CrossControlDualCmd *p);
static __inline__ void CrossControlDualCmd_delAndSetNull(void *ptr)
{
	CrossControlDualCmd **p = (CrossControlDualCmd **)ptr;
	if (p != NULL) { CrossControlDualCmd_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossControlDualCmd_dump(CrossControlDualCmd *p, int tab);
// CrossControlDualCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlCmdPresent
typedef enum CrossControlCmdPresent
{
	CrossControlCmdPresent_single = 0,
	CrossControlCmdPresent_dual = 1,
	CrossControlCmdPresent_max
} CrossControlCmdPresent;

DZ1_CPPLINK str_t CrossControlCmdPresentStrA(CrossControlCmdPresent v);
DZ1_CPPLINK CrossControlCmdPresent CrossControlCmdPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t CrossControlCmdPresentStrW(CrossControlCmdPresent v);
DZ1_CPPLINK CrossControlCmdPresent CrossControlCmdPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define CrossControlCmdPresentStr CrossControlCmdPresentStrW
#define CrossControlCmdPresentFromStr CrossControlCmdPresentFromStrW
#else // UNICODE
#define CrossControlCmdPresentStr CrossControlCmdPresentStrA
#define CrossControlCmdPresentFromStr CrossControlCmdPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define CrossControlCmdPresentStr CrossControlCmdPresentStrA
#define CrossControlCmdPresentFromStr CrossControlCmdPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT CrossControlCmdPresent *CrossControlCmdPresent_new(CrossControlCmdPresent *src, Dz1Error *err);
static __inline__ CrossControlCmdPresent *CrossControlCmdPresent_gen(Dz1Error *err) { CrossControlCmdPresent v = CrossControlCmdPresent_max; return CrossControlCmdPresent_new(&v, err); }
#define CrossControlCmdPresent_clone             CrossControlCmdPresent_new
static __inline__ void CrossControlCmdPresent_del(CrossControlCmdPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void CrossControlCmdPresent_delAndSetNull(void *ptr)
{
	CrossControlCmdPresent **p = (CrossControlCmdPresent **)ptr;
	if (p != NULL) { CrossControlCmdPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossControlCmdPresent_dump(CrossControlCmdPresent *v, int tab);
// CrossControlCmdPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlCmd
typedef struct CrossControlCmd
{
	CrossControlCmdPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		CrossControlSingleCmd		*single;
		CrossControlDualCmd			*dual;
	} x;
} CrossControlCmd;

DZ1_CPPLINK DZ1_DLLPORT CrossControlCmd *CrossControlCmd_new(CrossControlCmdPresent present, void *ptr, Dz1Error *err);
static __inline__ CrossControlCmd *CrossControlCmd_gen(Dz1Error *err) { return CrossControlCmd_new(CrossControlCmdPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  CrossControlCmd_copy(CrossControlCmd *dst, CrossControlCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossControlCmd *CrossControlCmd_clone(CrossControlCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlCmd_purge(CrossControlCmd *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlCmd_del(CrossControlCmd *p);
static __inline__ void CrossControlCmd_delAndSetNull(void *ptr)
{
	CrossControlCmd **p = (CrossControlCmd **)ptr;
	if (p != NULL) { CrossControlCmd_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossControlCmd_dump(CrossControlCmd *p, int tab);
// CrossControlCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlInformation
typedef struct CrossControlInformation
{
	u8_t				 cross_id;
	CrossControlCmd		*command;
} CrossControlInformation;

DZ1_CPPLINK DZ1_DLLPORT CrossControlInformation *CrossControlInformation_new(u8_t cross_id, 
																			 CrossControlCmd *command, Dz1Error *err);
static __inline__ CrossControlInformation *CrossControlInformation_gen(Dz1Error *err) { return CrossControlInformation_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CrossControlInformation_copy(CrossControlInformation *dst, CrossControlInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossControlInformation *CrossControlInformation_clone(CrossControlInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlInformation_purge(CrossControlInformation *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossControlInformation_del(CrossControlInformation *p);
static __inline__ void CrossControlInformation_delAndSetNull(void *ptr)
{
	CrossControlInformation **p = (CrossControlInformation **)ptr;
	if (p) { CrossControlInformation_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossControlInformation_dump(CrossControlInformation *p, int tab);
// CrossControlInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossIndicator
typedef struct CrossIndicator
{
	u8_t	cross_id;
} CrossIndicator;

DZ1_CPPLINK DZ1_DLLPORT CrossIndicator *CrossIndicator_new(u8_t cross_id, Dz1Error *err);
static __inline__ CrossIndicator *CrossIndicator_gen(Dz1Error *err) { return CrossIndicator_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CrossIndicator_copy(CrossIndicator *dst, CrossIndicator *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossIndicator *CrossIndicator_clone(CrossIndicator *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossIndicator_purge(CrossIndicator *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossIndicator_del(CrossIndicator *p);
static __inline__ void CrossIndicator_delAndSetNull(void *ptr)
{
	CrossIndicator **p = (CrossIndicator **)ptr;
	if (p) { CrossIndicator_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossIndicator_dump(CrossIndicator *p, int tab);
// CrossIndicator
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo_OperationMode
typedef enum CrossStatusBasicInfo_OperationMode
{
	CrossStatusBasicInfo_OperationMode_fixed,
	CrossStatusBasicInfo_OperationMode_lc,
	CrossStatusBasicInfo_OperationMode_lc_actuator,
	CrossStatusBasicInfo_OperationMode_rc_actuator = 4,
	CrossStatusBasicInfo_OperationMode_rc,
	CrossStatusBasicInfo_OperationMode_max
} CrossStatusBasicInfo_OperationMode;

DZ1_CPPLINK str_t CrossStatusBasicInfo_OperationModeStrA(CrossStatusBasicInfo_OperationMode v);
DZ1_CPPLINK CrossStatusBasicInfo_OperationMode CrossStatusBasicInfo_OperationModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t CrossStatusBasicInfo_OperationModeStrW(CrossStatusBasicInfo_OperationMode v);
DZ1_CPPLINK CrossStatusBasicInfo_OperationMode CrossStatusBasicInfo_OperationModeFromStrW(wstr_t str);
#ifdef UNICODE
#define CrossStatusBasicInfo_OperationModeStr CrossStatusBasicInfo_OperationModeStrW
#define CrossStatusBasicInfo_OperationModeFromStr CrossStatusBasicInfo_OperationModeFromStrW
#else // UNICODE
#define CrossStatusBasicInfo_OperationModeStr CrossStatusBasicInfo_OperationModeStrA
#define CrossStatusBasicInfo_OperationModeFromStr CrossStatusBasicInfo_OperationModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define CrossStatusBasicInfo_OperationModeStr CrossStatusBasicInfo_OperationModeStrA
#define CrossStatusBasicInfo_OperationModeFromStr CrossStatusBasicInfo_OperationModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT CrossStatusBasicInfo_OperationMode *CrossStatusBasicInfo_OperationMode_new(CrossStatusBasicInfo_OperationMode *src, Dz1Error *err);
static __inline__ CrossStatusBasicInfo_OperationMode *CrossStatusBasicInfo_OperationMode_gen(Dz1Error *err) { CrossStatusBasicInfo_OperationMode v = CrossStatusBasicInfo_OperationMode_max; return CrossStatusBasicInfo_OperationMode_new(&v, err); }
static __inline__ void CrossStatusBasicInfo_OperationMode_del(CrossStatusBasicInfo_OperationMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void CrossStatusBasicInfo_OperationMode_delAndSetNull(void *ptr)
{
	CrossStatusBasicInfo_OperationMode **p = (CrossStatusBasicInfo_OperationMode **)ptr;
	if (p != NULL) { CrossStatusBasicInfo_OperationMode_del(*p); *p = NULL; }
}
// CrossStatusBasicInfo_OperationMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo_BlinkReason
typedef enum CrossStatusBasicInfo_BlinkReason
{
	CrossStatusBasicInfo_BlinkReason_unknown,
	CrossStatusBasicInfo_BlinkReason_power_on,
	CrossStatusBasicInfo_BlinkReason_config,
	CrossStatusBasicInfo_BlinkReason_switched,
	CrossStatusBasicInfo_BlinkReason_contradiction,
	CrossStatusBasicInfo_BlinkReason_db_error,
	CrossStatusBasicInfo_BlinkReason_lights_off,
	CrossStatusBasicInfo_BlinkReason_sys_fault,
	CrossStatusBasicInfo_BlinkReason_max
} CrossStatusBasicInfo_BlinkReason;

DZ1_CPPLINK str_t CrossStatusBasicInfo_BlinkReasonStrA(CrossStatusBasicInfo_BlinkReason v);
DZ1_CPPLINK CrossStatusBasicInfo_BlinkReason CrossStatusBasicInfo_BlinkReasonFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t CrossStatusBasicInfo_BlinkReasonStrW(CrossStatusBasicInfo_BlinkReason v);
DZ1_CPPLINK CrossStatusBasicInfo_BlinkReason CrossStatusBasicInfo_BlinkReasonFromStrW(wstr_t str);
#ifdef UNICODE
#define CrossStatusBasicInfo_BlinkReasonStr CrossStatusBasicInfo_BlinkReasonStrW
#define CrossStatusBasicInfo_BlinkReasonFromStr CrossStatusBasicInfo_BlinkReasonFromStrW
#else // UNICODE
#define CrossStatusBasicInfo_BlinkReasonStr CrossStatusBasicInfo_BlinkReasonStrA
#define CrossStatusBasicInfo_BlinkReasonFromStr CrossStatusBasicInfo_BlinkReasonFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define CrossStatusBasicInfo_BlinkReasonStr CrossStatusBasicInfo_BlinkReasonStrA
#define CrossStatusBasicInfo_BlinkReasonFromStr CrossStatusBasicInfo_BlinkReasonFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT CrossStatusBasicInfo_BlinkReason *CrossStatusBasicInfo_BlinkReason_new(CrossStatusBasicInfo_BlinkReason *src, Dz1Error *err);
static __inline__ CrossStatusBasicInfo_BlinkReason *CrossStatusBasicInfo_BlinkReason_gen(Dz1Error *err) { CrossStatusBasicInfo_BlinkReason v = CrossStatusBasicInfo_BlinkReason_max; return CrossStatusBasicInfo_BlinkReason_new(&v, err); }
static __inline__ void CrossStatusBasicInfo_BlinkReason_del(CrossStatusBasicInfo_BlinkReason *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void CrossStatusBasicInfo_BlinkReason_delAndSetNull(void *ptr)
{
	CrossStatusBasicInfo_BlinkReason **p = (CrossStatusBasicInfo_BlinkReason **)ptr;
	if (p != NULL) { CrossStatusBasicInfo_BlinkReason_del(*p); *p = NULL; }
}
// CrossStatusBasicInfo_BlinkReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo
typedef struct CrossStatusBasicInfo
{
	bool_t									power_fail;
	bool_t									comm_fail;
	bool_t									lamp_oper;
	bool_t									is_dual_ring;
	bool_t									ppc_enabled;
	CrossStatusBasicInfo_OperationMode		oper_mode;
	u8_t									ring_a_phase;
	u8_t									ring_a_step;
	u8_t									ring_b_phase;
	u8_t									ring_b_step;
	bool_t									pannel_is_manual;
	bool_t									pannel_manual_sw;
	bool_t									pannel_blink_sw;
	bool_t									pannel_light_out_sw;
	bool_t									is_contradiction;
	bool_t									is_light_out;
	bool_t									is_blink;
	bool_t									is_database;
	bool_t									push_button_enable;
	CrossStatusBasicInfo_BlinkReason		blink_reason;
	bool_t									is_timed_left_signal;
	bool_t									manual_enabled;
	bool_t									conflict_enabled;
	bool_t									is_door_opened;
	u8_t									contradiction_lsu;
	bool_t									contradiction_from_sw;
	u8_t									contradiction_curcuit;
	u8_t									pedestrian_lamp;
	u8_t									push_button_pending;
	u8_t									push_button_status;
	u8_t									opt_board_status;
	u8_t									period_counter;
	u8_t									total_period;
	u8_t									curr_period;
	u8_t									period_offset;
	u8_t									hold_phase;
	u8_t									omit_phase;
	bool_t									is_four_color_lamp;
	u8_t									oper_map_id;
	bool_t									jam_ctrl_enabled;
	bool_t									jam_ctrl_mode;
	bool_t									jam_term_early0;
	bool_t									jam_term_early1;
	u16_t									firmware_id;
	u16_t									firmware_idx;
	u8_t									database_status;
	u8_t									ppc_control_status;
	u8_t									ups_control_status;
	bool_t									map_is_dirty;
	bool_t									lock_installed;
	bool_t									lock_is_locked;
	bool_t									db_is_locked;
} CrossStatusBasicInfo;

DZ1_CPPLINK DZ1_DLLPORT CrossStatusBasicInfo *CrossStatusBasicInfo_new(bool_t power_fail, 
																	   bool_t comm_fail, 
																	   bool_t lamp_oper, 
																	   bool_t is_dual_ring, 
																	   bool_t ppc_enabled, 
																	   CrossStatusBasicInfo_OperationMode oper_mode, 
																	   u8_t ring_a_phase, 
																	   u8_t ring_a_step, 
																	   u8_t ring_b_phase, 
																	   u8_t ring_b_step, 
																	   bool_t pannel_is_manual, 
																	   bool_t pannel_manual_sw, 
																	   bool_t pannel_blink_sw, 
																	   bool_t pannel_light_out_sw, 
																	   bool_t is_contradiction, 
																	   bool_t is_light_out, 
																	   bool_t is_blink, 
																	   bool_t is_database, 
																	   bool_t push_button_enable, 
																	   CrossStatusBasicInfo_BlinkReason blink_reason, 
																	   bool_t is_timed_left_signal, 
																	   bool_t manual_enabled, 
																	   bool_t conflict_enabled, 
																	   bool_t is_door_opened, 
																	   u8_t contradiction_lsu, 
																	   bool_t contradiction_from_sw, 
																	   u8_t contradiction_curcuit, 
																	   u8_t pedestrian_lamp, 
																	   u8_t push_button_pending, 
																	   u8_t push_button_status, 
																	   u8_t opt_board_status, 
																	   u8_t period_counter, 
																	   u8_t total_period, 
																	   u8_t curr_period, 
																	   u8_t period_offset, 
																	   u8_t hold_phase, 
																	   u8_t omit_phase, 
																	   bool_t is_four_color_lamp, 
																	   u8_t oper_map_id, 
																	   bool_t jam_ctrl_enabled, 
																	   bool_t jam_ctrl_mode, 
																	   bool_t jam_term_early0, 
																	   bool_t jam_term_early1, 
																	   u16_t firmware_id, 
																	   u16_t firmware_idx, 
																	   u8_t database_status, 
																	   u8_t ppc_control_status, 
																	   u8_t ups_control_status, 
																	   bool_t map_is_dirty, 
																	   bool_t lock_installed, 
																	   bool_t lock_is_locked, 
																	   bool_t db_is_locked, Dz1Error *err);
static __inline__ CrossStatusBasicInfo *CrossStatusBasicInfo_gen(Dz1Error *err) { return CrossStatusBasicInfo_new(0, 0, 0, 0, 0, CrossStatusBasicInfo_OperationMode_max, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CrossStatusBasicInfo_BlinkReason_max, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CrossStatusBasicInfo_copy(CrossStatusBasicInfo *dst, CrossStatusBasicInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossStatusBasicInfo *CrossStatusBasicInfo_clone(CrossStatusBasicInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusBasicInfo_purge(CrossStatusBasicInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusBasicInfo_del(CrossStatusBasicInfo *p);
static __inline__ void CrossStatusBasicInfo_delAndSetNull(void *ptr)
{
	CrossStatusBasicInfo **p = (CrossStatusBasicInfo **)ptr;
	if (p) { CrossStatusBasicInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusBasicInfo_dump(CrossStatusBasicInfo *p, int tab);
// CrossStatusBasicInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusExtInfo_ContradictionReason
typedef enum CrossStatusExtInfo_ContradictionReason
{
	CrossStatusExtInfo_ContradictionReason_none,
	CrossStatusExtInfo_ContradictionReason_voltage,
	CrossStatusExtInfo_ContradictionReason_current,
	CrossStatusExtInfo_ContradictionReason_map,
	CrossStatusExtInfo_ContradictionReason_max
} CrossStatusExtInfo_ContradictionReason;

DZ1_CPPLINK str_t CrossStatusExtInfo_ContradictionReasonStrA(CrossStatusExtInfo_ContradictionReason v);
DZ1_CPPLINK CrossStatusExtInfo_ContradictionReason CrossStatusExtInfo_ContradictionReasonFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t CrossStatusExtInfo_ContradictionReasonStrW(CrossStatusExtInfo_ContradictionReason v);
DZ1_CPPLINK CrossStatusExtInfo_ContradictionReason CrossStatusExtInfo_ContradictionReasonFromStrW(wstr_t str);
#ifdef UNICODE
#define CrossStatusExtInfo_ContradictionReasonStr CrossStatusExtInfo_ContradictionReasonStrW
#define CrossStatusExtInfo_ContradictionReasonFromStr CrossStatusExtInfo_ContradictionReasonFromStrW
#else // UNICODE
#define CrossStatusExtInfo_ContradictionReasonStr CrossStatusExtInfo_ContradictionReasonStrA
#define CrossStatusExtInfo_ContradictionReasonFromStr CrossStatusExtInfo_ContradictionReasonFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define CrossStatusExtInfo_ContradictionReasonStr CrossStatusExtInfo_ContradictionReasonStrA
#define CrossStatusExtInfo_ContradictionReasonFromStr CrossStatusExtInfo_ContradictionReasonFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT CrossStatusExtInfo_ContradictionReason *CrossStatusExtInfo_ContradictionReason_new(CrossStatusExtInfo_ContradictionReason *src, Dz1Error *err);
static __inline__ CrossStatusExtInfo_ContradictionReason *CrossStatusExtInfo_ContradictionReason_gen(Dz1Error *err) { CrossStatusExtInfo_ContradictionReason v = CrossStatusExtInfo_ContradictionReason_max; return CrossStatusExtInfo_ContradictionReason_new(&v, err); }
static __inline__ void CrossStatusExtInfo_ContradictionReason_del(CrossStatusExtInfo_ContradictionReason *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void CrossStatusExtInfo_ContradictionReason_delAndSetNull(void *ptr)
{
	CrossStatusExtInfo_ContradictionReason **p = (CrossStatusExtInfo_ContradictionReason **)ptr;
	if (p != NULL) { CrossStatusExtInfo_ContradictionReason_del(*p); *p = NULL; }
}
// CrossStatusExtInfo_ContradictionReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusExtInfo_r27
typedef struct CrossStatusExtInfo_r27
{
	u8_t										 type;
	u8_t										 ver;
	Dz1Binary									*ppc_data;
	u32_t										 detector_status;
	u8_t										 mlc_slc_comm_fail;
	u8_t										 contradiction_slc;
	CrossStatusExtInfo_ContradictionReason		 contradiction_prove;
	u8_t										 contradiction_circuit;
	u8_t										 ring_a_phase;
	u8_t										 ring_a_step;
	u8_t										 ring_b_phase;
	u8_t										 ring_b_step;
} CrossStatusExtInfo_r27;

DZ1_CPPLINK DZ1_DLLPORT CrossStatusExtInfo_r27 *CrossStatusExtInfo_r27_new(u8_t type, 
																		   u8_t ver, 
																		   Dz1Binary *ppc_data, 
																		   u32_t detector_status, 
																		   u8_t mlc_slc_comm_fail, 
																		   u8_t contradiction_slc, 
																		   CrossStatusExtInfo_ContradictionReason contradiction_prove, 
																		   u8_t contradiction_circuit, 
																		   u8_t ring_a_phase, 
																		   u8_t ring_a_step, 
																		   u8_t ring_b_phase, 
																		   u8_t ring_b_step, Dz1Error *err);
static __inline__ CrossStatusExtInfo_r27 *CrossStatusExtInfo_r27_gen(Dz1Error *err) { return CrossStatusExtInfo_r27_new(0, 0, NULL, 0, 0, 0, CrossStatusExtInfo_ContradictionReason_max, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CrossStatusExtInfo_r27_copy(CrossStatusExtInfo_r27 *dst, CrossStatusExtInfo_r27 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossStatusExtInfo_r27 *CrossStatusExtInfo_r27_clone(CrossStatusExtInfo_r27 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusExtInfo_r27_purge(CrossStatusExtInfo_r27 *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusExtInfo_r27_del(CrossStatusExtInfo_r27 *p);
static __inline__ void CrossStatusExtInfo_r27_delAndSetNull(void *ptr)
{
	CrossStatusExtInfo_r27 **p = (CrossStatusExtInfo_r27 **)ptr;
	if (p) { CrossStatusExtInfo_r27_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusExtInfo_r27_dump(CrossStatusExtInfo_r27 *p, int tab);
// CrossStatusExtInfo_r27
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusExtInfo_r29
typedef struct CrossStatusExtInfo_r29
{
	u8_t										 type;
	u8_t										 ver;
	Dz1Binary									*ppc_data;
	u32_t										 detector_status;
	u8_t										 mlc_slc_comm_fail;
	u8_t										 contradiction_slc;
	CrossStatusExtInfo_ContradictionReason		 contradiction_prove;
	u8_t										 contradiction_circuit;
	u8_t										 ring_a_phase;
	u8_t										 ring_a_step;
	u8_t										 ring_b_phase;
	u8_t										 ring_b_step;
	u16_t										 period_cnt;
	u16_t										 last_period_len;
	u16_t										 current_period;
	u16_t										 offset;
} CrossStatusExtInfo_r29;

DZ1_CPPLINK DZ1_DLLPORT CrossStatusExtInfo_r29 *CrossStatusExtInfo_r29_new(u8_t type, 
																		   u8_t ver, 
																		   Dz1Binary *ppc_data, 
																		   u32_t detector_status, 
																		   u8_t mlc_slc_comm_fail, 
																		   u8_t contradiction_slc, 
																		   CrossStatusExtInfo_ContradictionReason contradiction_prove, 
																		   u8_t contradiction_circuit, 
																		   u8_t ring_a_phase, 
																		   u8_t ring_a_step, 
																		   u8_t ring_b_phase, 
																		   u8_t ring_b_step, 
																		   u16_t period_cnt, 
																		   u16_t last_period_len, 
																		   u16_t current_period, 
																		   u16_t offset, Dz1Error *err);
static __inline__ CrossStatusExtInfo_r29 *CrossStatusExtInfo_r29_gen(Dz1Error *err) { return CrossStatusExtInfo_r29_new(0, 0, NULL, 0, 0, 0, CrossStatusExtInfo_ContradictionReason_max, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CrossStatusExtInfo_r29_copy(CrossStatusExtInfo_r29 *dst, CrossStatusExtInfo_r29 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossStatusExtInfo_r29 *CrossStatusExtInfo_r29_clone(CrossStatusExtInfo_r29 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusExtInfo_r29_purge(CrossStatusExtInfo_r29 *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusExtInfo_r29_del(CrossStatusExtInfo_r29 *p);
static __inline__ void CrossStatusExtInfo_r29_delAndSetNull(void *ptr)
{
	CrossStatusExtInfo_r29 **p = (CrossStatusExtInfo_r29 **)ptr;
	if (p) { CrossStatusExtInfo_r29_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusExtInfo_r29_dump(CrossStatusExtInfo_r29 *p, int tab);
// CrossStatusExtInfo_r29
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusInformation
typedef struct CrossStatusInformation
{
	u8_t						 cross_id;
	CrossStatusBasicInfo		*lc_status;
	CrossStatusExtInfo_r27		*ex_status;
} CrossStatusInformation;

DZ1_CPPLINK DZ1_DLLPORT CrossStatusInformation *CrossStatusInformation_new(u8_t cross_id, 
																		   CrossStatusBasicInfo *lc_status, Dz1Error *err);
static __inline__ CrossStatusInformation *CrossStatusInformation_gen(Dz1Error *err) { return CrossStatusInformation_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CrossStatusInformation_copy(CrossStatusInformation *dst, CrossStatusInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CrossStatusInformation *CrossStatusInformation_clone(CrossStatusInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusInformation_purge(CrossStatusInformation *p);
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusInformation_del(CrossStatusInformation *p);
static __inline__ void CrossStatusInformation_delAndSetNull(void *ptr)
{
	CrossStatusInformation **p = (CrossStatusInformation **)ptr;
	if (p) { CrossStatusInformation_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CrossStatusInformation_dump(CrossStatusInformation *p, int tab);
// CrossStatusInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfoFlagMap
typedef struct DetectorInfoFlagMap
{
	bool_t		bit6;
	bool_t		bit5;
	bool_t		bit4;
	bool_t		bit3;
	bool_t		bit2;
	bool_t		bit1;
	bool_t		bit0;
} DetectorInfoFlagMap;

DZ1_CPPLINK DZ1_DLLPORT DetectorInfoFlagMap *DetectorInfoFlagMap_new(bool_t bit6, 
																	 bool_t bit5, 
																	 bool_t bit4, 
																	 bool_t bit3, 
																	 bool_t bit2, 
																	 bool_t bit1, 
																	 bool_t bit0, Dz1Error *err);
static __inline__ DetectorInfoFlagMap *DetectorInfoFlagMap_gen(Dz1Error *err) { return DetectorInfoFlagMap_new(0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t DetectorInfoFlagMap_copy(DetectorInfoFlagMap *dst, DetectorInfoFlagMap *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT DetectorInfoFlagMap *DetectorInfoFlagMap_clone(DetectorInfoFlagMap *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfoFlagMap_purge(DetectorInfoFlagMap *p);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfoFlagMap_del(DetectorInfoFlagMap *p);
static __inline__ void DetectorInfoFlagMap_delAndSetNull(void *ptr)
{
	DetectorInfoFlagMap **p = (DetectorInfoFlagMap **)ptr;
	if (p) { DetectorInfoFlagMap_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfoFlagMap_dump(DetectorInfoFlagMap *p, int tab);
// DetectorInfoFlagMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfoFlagMaps
typedef struct DetectorInfoFlagMaps
{
	DetectorInfoFlagMap		*detector1;
	DetectorInfoFlagMap		*detector2;
	DetectorInfoFlagMap		*detector3;
	DetectorInfoFlagMap		*detector4;
	DetectorInfoFlagMap		*detector5;
	DetectorInfoFlagMap		*detector6;
	DetectorInfoFlagMap		*detector7;
	DetectorInfoFlagMap		*detector8;
	DetectorInfoFlagMap		*detector9;
	DetectorInfoFlagMap		*detector10;
	DetectorInfoFlagMap		*detector11;
	DetectorInfoFlagMap		*detector12;
	DetectorInfoFlagMap		*detector13;
	DetectorInfoFlagMap		*detector14;
	DetectorInfoFlagMap		*detector15;
	DetectorInfoFlagMap		*detector16;
	DetectorInfoFlagMap		*detector17;
	DetectorInfoFlagMap		*detector18;
	DetectorInfoFlagMap		*detector19;
	DetectorInfoFlagMap		*detector20;
	DetectorInfoFlagMap		*detector21;
	DetectorInfoFlagMap		*detector22;
	DetectorInfoFlagMap		*detector23;
	DetectorInfoFlagMap		*detector24;
	DetectorInfoFlagMap		*detector25;
	DetectorInfoFlagMap		*detector26;
	DetectorInfoFlagMap		*detector27;
	DetectorInfoFlagMap		*detector28;
	DetectorInfoFlagMap		*detector29;
	DetectorInfoFlagMap		*detector30;
	DetectorInfoFlagMap		*detector31;
	DetectorInfoFlagMap		*detector32;
} DetectorInfoFlagMaps;

DZ1_CPPLINK DZ1_DLLPORT DetectorInfoFlagMaps *DetectorInfoFlagMaps_new(DetectorInfoFlagMap *detector1, 
																	   DetectorInfoFlagMap *detector2, 
																	   DetectorInfoFlagMap *detector3, 
																	   DetectorInfoFlagMap *detector4, 
																	   DetectorInfoFlagMap *detector5, 
																	   DetectorInfoFlagMap *detector6, 
																	   DetectorInfoFlagMap *detector7, 
																	   DetectorInfoFlagMap *detector8, 
																	   DetectorInfoFlagMap *detector9, 
																	   DetectorInfoFlagMap *detector10, 
																	   DetectorInfoFlagMap *detector11, 
																	   DetectorInfoFlagMap *detector12, 
																	   DetectorInfoFlagMap *detector13, 
																	   DetectorInfoFlagMap *detector14, 
																	   DetectorInfoFlagMap *detector15, 
																	   DetectorInfoFlagMap *detector16, 
																	   DetectorInfoFlagMap *detector17, 
																	   DetectorInfoFlagMap *detector18, 
																	   DetectorInfoFlagMap *detector19, 
																	   DetectorInfoFlagMap *detector20, 
																	   DetectorInfoFlagMap *detector21, 
																	   DetectorInfoFlagMap *detector22, 
																	   DetectorInfoFlagMap *detector23, 
																	   DetectorInfoFlagMap *detector24, 
																	   DetectorInfoFlagMap *detector25, 
																	   DetectorInfoFlagMap *detector26, 
																	   DetectorInfoFlagMap *detector27, 
																	   DetectorInfoFlagMap *detector28, 
																	   DetectorInfoFlagMap *detector29, 
																	   DetectorInfoFlagMap *detector30, 
																	   DetectorInfoFlagMap *detector31, 
																	   DetectorInfoFlagMap *detector32, Dz1Error *err);
static __inline__ DetectorInfoFlagMaps *DetectorInfoFlagMaps_gen(Dz1Error *err) { return DetectorInfoFlagMaps_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t DetectorInfoFlagMaps_copy(DetectorInfoFlagMaps *dst, DetectorInfoFlagMaps *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT DetectorInfoFlagMaps *DetectorInfoFlagMaps_clone(DetectorInfoFlagMaps *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfoFlagMaps_purge(DetectorInfoFlagMaps *p);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfoFlagMaps_del(DetectorInfoFlagMaps *p);
static __inline__ void DetectorInfoFlagMaps_delAndSetNull(void *ptr)
{
	DetectorInfoFlagMaps **p = (DetectorInfoFlagMaps **)ptr;
	if (p) { DetectorInfoFlagMaps_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfoFlagMaps_dump(DetectorInfoFlagMaps *p, int tab);
// DetectorInfoFlagMaps
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfoValueMap
typedef struct DetectorInfoValueMap
{
	u8_t	detector1;
	u8_t	detector2;
	u8_t	detector3;
	u8_t	detector4;
	u8_t	detector5;
	u8_t	detector6;
	u8_t	detector7;
	u8_t	detector8;
	u8_t	detector9;
	u8_t	detector10;
	u8_t	detector11;
	u8_t	detector12;
	u8_t	detector13;
	u8_t	detector14;
	u8_t	detector15;
	u8_t	detector16;
	u8_t	detector17;
	u8_t	detector18;
	u8_t	detector19;
	u8_t	detector20;
	u8_t	detector21;
	u8_t	detector22;
	u8_t	detector23;
	u8_t	detector24;
	u8_t	detector25;
	u8_t	detector26;
	u8_t	detector27;
	u8_t	detector28;
	u8_t	detector29;
	u8_t	detector30;
	u8_t	detector31;
	u8_t	detector32;
} DetectorInfoValueMap;

DZ1_CPPLINK DZ1_DLLPORT DetectorInfoValueMap *DetectorInfoValueMap_new(u8_t detector1, 
																	   u8_t detector2, 
																	   u8_t detector3, 
																	   u8_t detector4, 
																	   u8_t detector5, 
																	   u8_t detector6, 
																	   u8_t detector7, 
																	   u8_t detector8, 
																	   u8_t detector9, 
																	   u8_t detector10, 
																	   u8_t detector11, 
																	   u8_t detector12, 
																	   u8_t detector13, 
																	   u8_t detector14, 
																	   u8_t detector15, 
																	   u8_t detector16, 
																	   u8_t detector17, 
																	   u8_t detector18, 
																	   u8_t detector19, 
																	   u8_t detector20, 
																	   u8_t detector21, 
																	   u8_t detector22, 
																	   u8_t detector23, 
																	   u8_t detector24, 
																	   u8_t detector25, 
																	   u8_t detector26, 
																	   u8_t detector27, 
																	   u8_t detector28, 
																	   u8_t detector29, 
																	   u8_t detector30, 
																	   u8_t detector31, 
																	   u8_t detector32, Dz1Error *err);
static __inline__ DetectorInfoValueMap *DetectorInfoValueMap_gen(Dz1Error *err) { return DetectorInfoValueMap_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t DetectorInfoValueMap_copy(DetectorInfoValueMap *dst, DetectorInfoValueMap *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT DetectorInfoValueMap *DetectorInfoValueMap_clone(DetectorInfoValueMap *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfoValueMap_purge(DetectorInfoValueMap *p);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfoValueMap_del(DetectorInfoValueMap *p);
static __inline__ void DetectorInfoValueMap_delAndSetNull(void *ptr)
{
	DetectorInfoValueMap **p = (DetectorInfoValueMap **)ptr;
	if (p) { DetectorInfoValueMap_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfoValueMap_dump(DetectorInfoValueMap *p, int tab);
// DetectorInfoValueMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfo
typedef struct DetectorInfo
{
	DetectorInfoFlagMaps	*detector_info_flags;
	DetectorInfoValueMap	*detector_not_occupy_times;
	DetectorInfoValueMap	*detector_occupy_times;
	DetectorInfoValueMap	*detector_traffic_volumes;
	DetectorInfoValueMap	*detector_traffic_saturations;
	DetectorInfoValueMap	*detector_saturation_flow_rate_per_speeds;
	DetectorInfoValueMap	*detector_saturation_not_ocuppy_time;
} DetectorInfo;

DZ1_CPPLINK DZ1_DLLPORT DetectorInfo *DetectorInfo_new(DetectorInfoFlagMaps *detector_info_flags, 
													   DetectorInfoValueMap *detector_not_occupy_times, 
													   DetectorInfoValueMap *detector_occupy_times, 
													   DetectorInfoValueMap *detector_traffic_volumes, 
													   DetectorInfoValueMap *detector_traffic_saturations, 
													   DetectorInfoValueMap *detector_saturation_flow_rate_per_speeds, 
													   DetectorInfoValueMap *detector_saturation_not_ocuppy_time, Dz1Error *err);
static __inline__ DetectorInfo *DetectorInfo_gen(Dz1Error *err) { return DetectorInfo_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t DetectorInfo_copy(DetectorInfo *dst, DetectorInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT DetectorInfo *DetectorInfo_clone(DetectorInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfo_purge(DetectorInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfo_del(DetectorInfo *p);
static __inline__ void DetectorInfo_delAndSetNull(void *ptr)
{
	DetectorInfo **p = (DetectorInfo **)ptr;
	if (p) { DetectorInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void DetectorInfo_dump(DetectorInfo *p, int tab);
// DetectorInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInformation
typedef struct DetectorInformation
{
	u8_t			 cross_id;
	DetectorInfo	*detector_info;
} DetectorInformation;

DZ1_CPPLINK DZ1_DLLPORT DetectorInformation *DetectorInformation_new(u8_t cross_id, 
																	 DetectorInfo *detector_info, Dz1Error *err);
static __inline__ DetectorInformation *DetectorInformation_gen(Dz1Error *err) { return DetectorInformation_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t DetectorInformation_copy(DetectorInformation *dst, DetectorInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT DetectorInformation *DetectorInformation_clone(DetectorInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInformation_purge(DetectorInformation *p);
DZ1_CPPLINK DZ1_DLLPORT void DetectorInformation_del(DetectorInformation *p);
static __inline__ void DetectorInformation_delAndSetNull(void *ptr)
{
	DetectorInformation **p = (DetectorInformation **)ptr;
	if (p) { DetectorInformation_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void DetectorInformation_dump(DetectorInformation *p, int tab);
// DetectorInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoPeriodicOperationTime
typedef struct SignalPhaseInfoPeriodicOperationTime
{
	u8_t	ring_a_phase1;
	u8_t	ring_a_phase2;
	u8_t	ring_a_phase3;
	u8_t	ring_a_phase4;
	u8_t	ring_a_phase5;
	u8_t	ring_a_phase6;
	u8_t	ring_a_phase7;
	u8_t	ring_a_phase8;
	u8_t	ring_b_phase1;
	u8_t	ring_b_phase2;
	u8_t	ring_b_phase3;
	u8_t	ring_b_phase4;
	u8_t	ring_b_phase5;
	u8_t	ring_b_phase6;
	u8_t	ring_b_phase7;
	u8_t	ring_b_phase8;
} SignalPhaseInfoPeriodicOperationTime;

DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoPeriodicOperationTime *SignalPhaseInfoPeriodicOperationTime_new(u8_t ring_a_phase1, 
																									   u8_t ring_a_phase2, 
																									   u8_t ring_a_phase3, 
																									   u8_t ring_a_phase4, 
																									   u8_t ring_a_phase5, 
																									   u8_t ring_a_phase6, 
																									   u8_t ring_a_phase7, 
																									   u8_t ring_a_phase8, 
																									   u8_t ring_b_phase1, 
																									   u8_t ring_b_phase2, 
																									   u8_t ring_b_phase3, 
																									   u8_t ring_b_phase4, 
																									   u8_t ring_b_phase5, 
																									   u8_t ring_b_phase6, 
																									   u8_t ring_b_phase7, 
																									   u8_t ring_b_phase8, Dz1Error *err);
static __inline__ SignalPhaseInfoPeriodicOperationTime *SignalPhaseInfoPeriodicOperationTime_gen(Dz1Error *err) { return SignalPhaseInfoPeriodicOperationTime_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SignalPhaseInfoPeriodicOperationTime_copy(SignalPhaseInfoPeriodicOperationTime *dst, SignalPhaseInfoPeriodicOperationTime *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoPeriodicOperationTime *SignalPhaseInfoPeriodicOperationTime_clone(SignalPhaseInfoPeriodicOperationTime *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoPeriodicOperationTime_purge(SignalPhaseInfoPeriodicOperationTime *p);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoPeriodicOperationTime_del(SignalPhaseInfoPeriodicOperationTime *p);
static __inline__ void SignalPhaseInfoPeriodicOperationTime_delAndSetNull(void *ptr)
{
	SignalPhaseInfoPeriodicOperationTime **p = (SignalPhaseInfoPeriodicOperationTime **)ptr;
	if (p) { SignalPhaseInfoPeriodicOperationTime_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoPeriodicOperationTime_dump(SignalPhaseInfoPeriodicOperationTime *p, int tab);
// SignalPhaseInfoPeriodicOperationTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoDownBasic
typedef struct SignalPhaseInfoDownBasic
{
	SignalPhaseInfoPeriodicOperationTime	*periodic_oper_time1;
	u8_t									 offset;
} SignalPhaseInfoDownBasic;

DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoDownBasic *SignalPhaseInfoDownBasic_new(SignalPhaseInfoPeriodicOperationTime *periodic_oper_time1, 
																			   u8_t offset, Dz1Error *err);
static __inline__ SignalPhaseInfoDownBasic *SignalPhaseInfoDownBasic_gen(Dz1Error *err) { return SignalPhaseInfoDownBasic_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SignalPhaseInfoDownBasic_copy(SignalPhaseInfoDownBasic *dst, SignalPhaseInfoDownBasic *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoDownBasic *SignalPhaseInfoDownBasic_clone(SignalPhaseInfoDownBasic *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoDownBasic_purge(SignalPhaseInfoDownBasic *p);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoDownBasic_del(SignalPhaseInfoDownBasic *p);
static __inline__ void SignalPhaseInfoDownBasic_delAndSetNull(void *ptr)
{
	SignalPhaseInfoDownBasic **p = (SignalPhaseInfoDownBasic **)ptr;
	if (p) { SignalPhaseInfoDownBasic_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoDownBasic_dump(SignalPhaseInfoDownBasic *p, int tab);
// SignalPhaseInfoDownBasic
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoDown_r27
typedef struct SignalPhaseInfoDown_r27
{
	SignalPhaseInfoDownBasic				*mandatory;
	SignalPhaseInfoPeriodicOperationTime	*periodic_oper_time2;
	SignalPhaseInfoPeriodicOperationTime	*periodic_oper_time3;
} SignalPhaseInfoDown_r27;

DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoDown_r27 *SignalPhaseInfoDown_r27_new(SignalPhaseInfoDownBasic *mandatory, Dz1Error *err);
static __inline__ SignalPhaseInfoDown_r27 *SignalPhaseInfoDown_r27_gen(Dz1Error *err) { return SignalPhaseInfoDown_r27_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SignalPhaseInfoDown_r27_copy(SignalPhaseInfoDown_r27 *dst, SignalPhaseInfoDown_r27 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoDown_r27 *SignalPhaseInfoDown_r27_clone(SignalPhaseInfoDown_r27 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoDown_r27_purge(SignalPhaseInfoDown_r27 *p);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoDown_r27_del(SignalPhaseInfoDown_r27 *p);
static __inline__ void SignalPhaseInfoDown_r27_delAndSetNull(void *ptr)
{
	SignalPhaseInfoDown_r27 **p = (SignalPhaseInfoDown_r27 **)ptr;
	if (p) { SignalPhaseInfoDown_r27_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoDown_r27_dump(SignalPhaseInfoDown_r27 *p, int tab);
// SignalPhaseInfoDown_r27
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoDown_r29
typedef struct SignalPhaseInfoDown_r29
{
	SignalPhaseInfoDownBasic				*mandatory;
	SignalPhaseInfoPeriodicOperationTime	*periodic_oper_time2;
	SignalPhaseInfoPeriodicOperationTime	*periodic_oper_time3;
	u16_t									 offset1;
	u16_t									 offset2;
	u16_t									 offset3;
} SignalPhaseInfoDown_r29;

DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoDown_r29 *SignalPhaseInfoDown_r29_new(SignalPhaseInfoDownBasic *mandatory, 
																			 u16_t offset1, Dz1Error *err);
static __inline__ SignalPhaseInfoDown_r29 *SignalPhaseInfoDown_r29_gen(Dz1Error *err) { return SignalPhaseInfoDown_r29_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SignalPhaseInfoDown_r29_copy(SignalPhaseInfoDown_r29 *dst, SignalPhaseInfoDown_r29 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoDown_r29 *SignalPhaseInfoDown_r29_clone(SignalPhaseInfoDown_r29 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoDown_r29_purge(SignalPhaseInfoDown_r29 *p);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoDown_r29_del(SignalPhaseInfoDown_r29 *p);
static __inline__ void SignalPhaseInfoDown_r29_delAndSetNull(void *ptr)
{
	SignalPhaseInfoDown_r29 **p = (SignalPhaseInfoDown_r29 **)ptr;
	if (p) { SignalPhaseInfoDown_r29_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoDown_r29_dump(SignalPhaseInfoDown_r29 *p, int tab);
// SignalPhaseInfoDown_r29
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInformationDownload
typedef struct SignalPhaseInformationDownload
{
	u8_t						 cross_id;
	SignalPhaseInfoDown_r27		*signal_phase_info_down;
} SignalPhaseInformationDownload;

DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInformationDownload *SignalPhaseInformationDownload_new(u8_t cross_id, 
																						   SignalPhaseInfoDown_r27 *signal_phase_info_down, Dz1Error *err);
static __inline__ SignalPhaseInformationDownload *SignalPhaseInformationDownload_gen(Dz1Error *err) { return SignalPhaseInformationDownload_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SignalPhaseInformationDownload_copy(SignalPhaseInformationDownload *dst, SignalPhaseInformationDownload *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInformationDownload *SignalPhaseInformationDownload_clone(SignalPhaseInformationDownload *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInformationDownload_purge(SignalPhaseInformationDownload *p);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInformationDownload_del(SignalPhaseInformationDownload *p);
static __inline__ void SignalPhaseInformationDownload_delAndSetNull(void *ptr)
{
	SignalPhaseInformationDownload **p = (SignalPhaseInformationDownload **)ptr;
	if (p) { SignalPhaseInformationDownload_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInformationDownload_dump(SignalPhaseInformationDownload *p, int tab);
// SignalPhaseInformationDownload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoUpPPCControl
typedef struct SignalPhaseInfoUpPPCControl
{
	u8_t	ppc_blink_time;
	u8_t	ppc_all_red_time;
	u8_t	ppc_priority_signal;
} SignalPhaseInfoUpPPCControl;

DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoUpPPCControl *SignalPhaseInfoUpPPCControl_new(Dz1Error *err);
static __inline__ SignalPhaseInfoUpPPCControl *SignalPhaseInfoUpPPCControl_gen(Dz1Error *err) { return SignalPhaseInfoUpPPCControl_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SignalPhaseInfoUpPPCControl_copy(SignalPhaseInfoUpPPCControl *dst, SignalPhaseInfoUpPPCControl *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoUpPPCControl *SignalPhaseInfoUpPPCControl_clone(SignalPhaseInfoUpPPCControl *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoUpPPCControl_purge(SignalPhaseInfoUpPPCControl *p);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoUpPPCControl_del(SignalPhaseInfoUpPPCControl *p);
static __inline__ void SignalPhaseInfoUpPPCControl_delAndSetNull(void *ptr)
{
	SignalPhaseInfoUpPPCControl **p = (SignalPhaseInfoUpPPCControl **)ptr;
	if (p) { SignalPhaseInfoUpPPCControl_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoUpPPCControl_dump(SignalPhaseInfoUpPPCControl *p, int tab);
// SignalPhaseInfoUpPPCControl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoUp
typedef struct SignalPhaseInfoUp
{
	SignalPhaseInfoPeriodicOperationTime	*operation_time;
	SignalPhaseInfoPeriodicOperationTime	*pedestrianoperation_time;
	SignalPhaseInfoUpPPCControl				*ppc_control;
} SignalPhaseInfoUp;

DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoUp *SignalPhaseInfoUp_new(SignalPhaseInfoPeriodicOperationTime *operation_time, Dz1Error *err);
static __inline__ SignalPhaseInfoUp *SignalPhaseInfoUp_gen(Dz1Error *err) { return SignalPhaseInfoUp_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SignalPhaseInfoUp_copy(SignalPhaseInfoUp *dst, SignalPhaseInfoUp *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInfoUp *SignalPhaseInfoUp_clone(SignalPhaseInfoUp *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoUp_purge(SignalPhaseInfoUp *p);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoUp_del(SignalPhaseInfoUp *p);
static __inline__ void SignalPhaseInfoUp_delAndSetNull(void *ptr)
{
	SignalPhaseInfoUp **p = (SignalPhaseInfoUp **)ptr;
	if (p) { SignalPhaseInfoUp_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInfoUp_dump(SignalPhaseInfoUp *p, int tab);
// SignalPhaseInfoUp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInformationUpload
typedef struct SignalPhaseInformationUpload
{
	u8_t					 cross_id;
	SignalPhaseInfoUp		*signal_phase_info_up;
} SignalPhaseInformationUpload;

DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInformationUpload *SignalPhaseInformationUpload_new(u8_t cross_id, 
																					   SignalPhaseInfoUp *signal_phase_info_up, Dz1Error *err);
static __inline__ SignalPhaseInformationUpload *SignalPhaseInformationUpload_gen(Dz1Error *err) { return SignalPhaseInformationUpload_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SignalPhaseInformationUpload_copy(SignalPhaseInformationUpload *dst, SignalPhaseInformationUpload *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SignalPhaseInformationUpload *SignalPhaseInformationUpload_clone(SignalPhaseInformationUpload *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInformationUpload_purge(SignalPhaseInformationUpload *p);
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInformationUpload_del(SignalPhaseInformationUpload *p);
static __inline__ void SignalPhaseInformationUpload_delAndSetNull(void *ptr)
{
	SignalPhaseInformationUpload **p = (SignalPhaseInformationUpload **)ptr;
	if (p) { SignalPhaseInformationUpload_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SignalPhaseInformationUpload_dump(SignalPhaseInformationUpload *p, int tab);
// SignalPhaseInformationUpload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInfoWeekIndex
typedef enum ClockInfoWeekIndex
{
	ClockInfoWeekIndex_sun = 0,
	ClockInfoWeekIndex_mon,
	ClockInfoWeekIndex_tue,
	ClockInfoWeekIndex_wed,
	ClockInfoWeekIndex_thu,
	ClockInfoWeekIndex_fri,
	ClockInfoWeekIndex_sat,
	ClockInfoWeekIndex_max
} ClockInfoWeekIndex;

DZ1_CPPLINK str_t ClockInfoWeekIndexStrA(ClockInfoWeekIndex v);
DZ1_CPPLINK ClockInfoWeekIndex ClockInfoWeekIndexFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ClockInfoWeekIndexStrW(ClockInfoWeekIndex v);
DZ1_CPPLINK ClockInfoWeekIndex ClockInfoWeekIndexFromStrW(wstr_t str);
#ifdef UNICODE
#define ClockInfoWeekIndexStr ClockInfoWeekIndexStrW
#define ClockInfoWeekIndexFromStr ClockInfoWeekIndexFromStrW
#else // UNICODE
#define ClockInfoWeekIndexStr ClockInfoWeekIndexStrA
#define ClockInfoWeekIndexFromStr ClockInfoWeekIndexFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ClockInfoWeekIndexStr ClockInfoWeekIndexStrA
#define ClockInfoWeekIndexFromStr ClockInfoWeekIndexFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ClockInfoWeekIndex *ClockInfoWeekIndex_new(ClockInfoWeekIndex *src, Dz1Error *err);
static __inline__ ClockInfoWeekIndex *ClockInfoWeekIndex_gen(Dz1Error *err) { ClockInfoWeekIndex v = ClockInfoWeekIndex_max; return ClockInfoWeekIndex_new(&v, err); }
static __inline__ void ClockInfoWeekIndex_del(ClockInfoWeekIndex *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ClockInfoWeekIndex_delAndSetNull(void *ptr)
{
	ClockInfoWeekIndex **p = (ClockInfoWeekIndex **)ptr;
	if (p != NULL) { ClockInfoWeekIndex_del(*p); *p = NULL; }
}
// ClockInfoWeekIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInfo
typedef struct ClockInfo
{
	u8_t					year;
	u8_t					month;
	u8_t					day;
	u8_t					hour;
	u8_t					minute;
	u8_t					second;
	ClockInfoWeekIndex		week_index;
} ClockInfo;

DZ1_CPPLINK DZ1_DLLPORT ClockInfo *ClockInfo_new(u8_t year, 
												 u8_t month, 
												 u8_t day, 
												 u8_t hour, 
												 u8_t minute, 
												 u8_t second, 
												 ClockInfoWeekIndex week_index, Dz1Error *err);
static __inline__ ClockInfo *ClockInfo_gen(Dz1Error *err) { return ClockInfo_new(0, 0, 0, 0, 0, 0, ClockInfoWeekIndex_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ClockInfo_copy(ClockInfo *dst, ClockInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ClockInfo *ClockInfo_clone(ClockInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ClockInfo_purge(ClockInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void ClockInfo_del(ClockInfo *p);
static __inline__ void ClockInfo_delAndSetNull(void *ptr)
{
	ClockInfo **p = (ClockInfo **)ptr;
	if (p) { ClockInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ClockInfo_dump(ClockInfo *p, int tab);
// ClockInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInformationDownload
typedef struct ClockInformationDownload
{
	u8_t			 cross_id;
	ClockInfo		*clock_info_down;
} ClockInformationDownload;

DZ1_CPPLINK DZ1_DLLPORT ClockInformationDownload *ClockInformationDownload_new(u8_t cross_id, 
																			   ClockInfo *clock_info_down, Dz1Error *err);
static __inline__ ClockInformationDownload *ClockInformationDownload_gen(Dz1Error *err) { return ClockInformationDownload_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ClockInformationDownload_copy(ClockInformationDownload *dst, ClockInformationDownload *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ClockInformationDownload *ClockInformationDownload_clone(ClockInformationDownload *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ClockInformationDownload_purge(ClockInformationDownload *p);
DZ1_CPPLINK DZ1_DLLPORT void ClockInformationDownload_del(ClockInformationDownload *p);
static __inline__ void ClockInformationDownload_delAndSetNull(void *ptr)
{
	ClockInformationDownload **p = (ClockInformationDownload **)ptr;
	if (p) { ClockInformationDownload_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ClockInformationDownload_dump(ClockInformationDownload *p, int tab);
// ClockInformationDownload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInformationUpload
typedef struct ClockInformationUpload
{
	u8_t			 cross_id;
	ClockInfo		*clock_info_up;
} ClockInformationUpload;

DZ1_CPPLINK DZ1_DLLPORT ClockInformationUpload *ClockInformationUpload_new(u8_t cross_id, 
																		   ClockInfo *clock_info_up, Dz1Error *err);
static __inline__ ClockInformationUpload *ClockInformationUpload_gen(Dz1Error *err) { return ClockInformationUpload_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ClockInformationUpload_copy(ClockInformationUpload *dst, ClockInformationUpload *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ClockInformationUpload *ClockInformationUpload_clone(ClockInformationUpload *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ClockInformationUpload_purge(ClockInformationUpload *p);
DZ1_CPPLINK DZ1_DLLPORT void ClockInformationUpload_del(ClockInformationUpload *p);
static __inline__ void ClockInformationUpload_delAndSetNull(void *ptr)
{
	ClockInformationUpload **p = (ClockInformationUpload **)ptr;
	if (p) { ClockInformationUpload_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ClockInformationUpload_dump(ClockInformationUpload *p, int tab);
// ClockInformationUpload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCVehicleProperty
typedef struct SpecialCommandPPCVehicleProperty
{
	u32_t		property;
} SpecialCommandPPCVehicleProperty;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCVehicleProperty *SpecialCommandPPCVehicleProperty_new(u32_t property, Dz1Error *err);
static __inline__ SpecialCommandPPCVehicleProperty *SpecialCommandPPCVehicleProperty_gen(Dz1Error *err) { return SpecialCommandPPCVehicleProperty_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandPPCVehicleProperty_copy(SpecialCommandPPCVehicleProperty *dst, SpecialCommandPPCVehicleProperty *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCVehicleProperty *SpecialCommandPPCVehicleProperty_clone(SpecialCommandPPCVehicleProperty *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCVehicleProperty_purge(SpecialCommandPPCVehicleProperty *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCVehicleProperty_del(SpecialCommandPPCVehicleProperty *p);
static __inline__ void SpecialCommandPPCVehicleProperty_delAndSetNull(void *ptr)
{
	SpecialCommandPPCVehicleProperty **p = (SpecialCommandPPCVehicleProperty **)ptr;
	if (p) { SpecialCommandPPCVehicleProperty_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCVehicleProperty_dump(SpecialCommandPPCVehicleProperty *p, int tab);
// SpecialCommandPPCVehicleProperty
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCVehicleProperties
typedef struct SpecialCommandPPCVehicleProperties
{
	void *storage;
	unsigned int (*count)(struct SpecialCommandPPCVehicleProperties *p);
	Dz1Error (*travel)(struct SpecialCommandPPCVehicleProperties *p, Dz1Error (*func)(void *ptr, SpecialCommandPPCVehicleProperty *entry), void *ptr);
	Dz1Error (*travelForward)(struct SpecialCommandPPCVehicleProperties *p, Dz1Error (*func)(void *ptr, SpecialCommandPPCVehicleProperty *entry), void *ptr);
	Dz1Error (*travelBackward)(struct SpecialCommandPPCVehicleProperties *p, Dz1Error (*func)(void *ptr, SpecialCommandPPCVehicleProperty *entry), void *ptr);
	SpecialCommandPPCVehicleProperty **(*get_array)(struct SpecialCommandPPCVehicleProperties *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct SpecialCommandPPCVehicleProperties *p, SpecialCommandPPCVehicleProperty *data);
	SpecialCommandPPCVehicleProperty *(*extract)(struct SpecialCommandPPCVehicleProperties *p, SpecialCommandPPCVehicleProperty *ptr);
	SpecialCommandPPCVehicleProperty *(*getHead)(struct SpecialCommandPPCVehicleProperties *p);
} SpecialCommandPPCVehicleProperties;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCVehicleProperties *SpecialCommandPPCVehicleProperties_new(Dz1Error *err);
static __inline__ SpecialCommandPPCVehicleProperties *SpecialCommandPPCVehicleProperties_gen(Dz1Error *err) { return SpecialCommandPPCVehicleProperties_new(err); }
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCVehicleProperties *SpecialCommandPPCVehicleProperties_clone(SpecialCommandPPCVehicleProperties *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCVehicleProperties_purge(SpecialCommandPPCVehicleProperties *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCVehicleProperties_del(SpecialCommandPPCVehicleProperties *p);
static __inline__ void SpecialCommandPPCVehicleProperties_delAndSetNull(void *ptr)
{
	SpecialCommandPPCVehicleProperties **p = (SpecialCommandPPCVehicleProperties **)ptr;
	if (p != NULL) { SpecialCommandPPCVehicleProperties_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCVehicleProperties_dump(SpecialCommandPPCVehicleProperties *p, int tab);

// SpecialCommandPPCVehicleProperties
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInfoPPCControlManage
typedef struct SpecialCommandInfoPPCControlManage
{
	bool_t								 is_org_code_registered_vehicle_request;
	bool_t								 is_register_org_code;
	bool_t								 is_delete_org_code;
	bool_t								 is_register_vehicle_num;
	bool_t								 is_delete_vehicle_num;
	bool_t								 vehicle_code;
	u8_t								 org_manage_code;
	SpecialCommandPPCVehicleProperty	*vehicle_property;
} SpecialCommandInfoPPCControlManage;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandInfoPPCControlManage *SpecialCommandInfoPPCControlManage_new(bool_t is_org_code_registered_vehicle_request, 
																								   bool_t is_register_org_code, 
																								   bool_t is_delete_org_code, 
																								   bool_t is_register_vehicle_num, 
																								   bool_t is_delete_vehicle_num, 
																								   bool_t vehicle_code, 
																								   u8_t org_manage_code, 
																								   SpecialCommandPPCVehicleProperty *vehicle_property, Dz1Error *err);
static __inline__ SpecialCommandInfoPPCControlManage *SpecialCommandInfoPPCControlManage_gen(Dz1Error *err) { return SpecialCommandInfoPPCControlManage_new(0, 0, 0, 0, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandInfoPPCControlManage_copy(SpecialCommandInfoPPCControlManage *dst, SpecialCommandInfoPPCControlManage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandInfoPPCControlManage *SpecialCommandInfoPPCControlManage_clone(SpecialCommandInfoPPCControlManage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInfoPPCControlManage_purge(SpecialCommandInfoPPCControlManage *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInfoPPCControlManage_del(SpecialCommandInfoPPCControlManage *p);
static __inline__ void SpecialCommandInfoPPCControlManage_delAndSetNull(void *ptr)
{
	SpecialCommandInfoPPCControlManage **p = (SpecialCommandInfoPPCControlManage **)ptr;
	if (p) { SpecialCommandInfoPPCControlManage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInfoPPCControlManage_dump(SpecialCommandInfoPPCControlManage *p, int tab);
// SpecialCommandInfoPPCControlManage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInfo
typedef struct SpecialCommandInfo
{
	bool_t									 is_shut_down;
	bool_t									 is_blink_control;
	bool_t									 is_lamp_light_control;
	bool_t									 is_confilct;
	bool_t									 is_manual;
	bool_t									 is_confilct_reset;
	bool_t									 is_scu_reset;
	bool_t									 is_mcu_reset;
	bool_t									 is_ppc_control;
	bool_t									 is_pedestrian_button;
	bool_t									 is_x_control;
	bool_t									 is_spill_back_control;
	bool_t									 is_phase_omit;
	bool_t									 is_phase_hold;
	bool_t									 is_actuation_control;
	bool_t									 is_stagger_control;
	u8_t									 operation_flag;
	u8_t									 hold_omit_phase;
	u8_t									 stagger_plan;
	u8_t									 spill_back_direction_code;
	u8_t									 sub_phase_spill_back;
	u8_t									 main_phase_spill_back;
	SpecialCommandInfoPPCControlManage		*ppc_control_manage;
} SpecialCommandInfo;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandInfo *SpecialCommandInfo_new(bool_t is_shut_down, 
																   bool_t is_blink_control, 
																   bool_t is_lamp_light_control, 
																   bool_t is_confilct, 
																   bool_t is_manual, 
																   bool_t is_confilct_reset, 
																   bool_t is_scu_reset, 
																   bool_t is_mcu_reset, 
																   bool_t is_ppc_control, 
																   bool_t is_pedestrian_button, 
																   bool_t is_x_control, 
																   bool_t is_spill_back_control, 
																   bool_t is_phase_omit, 
																   bool_t is_phase_hold, 
																   bool_t is_actuation_control, 
																   bool_t is_stagger_control, 
																   u8_t operation_flag, 
																   u8_t hold_omit_phase, 
																   u8_t stagger_plan, 
																   u8_t spill_back_direction_code, 
																   u8_t sub_phase_spill_back, 
																   u8_t main_phase_spill_back, 
																   SpecialCommandInfoPPCControlManage *ppc_control_manage, Dz1Error *err);
static __inline__ SpecialCommandInfo *SpecialCommandInfo_gen(Dz1Error *err) { return SpecialCommandInfo_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandInfo_copy(SpecialCommandInfo *dst, SpecialCommandInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandInfo *SpecialCommandInfo_clone(SpecialCommandInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInfo_purge(SpecialCommandInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInfo_del(SpecialCommandInfo *p);
static __inline__ void SpecialCommandInfo_delAndSetNull(void *ptr)
{
	SpecialCommandInfo **p = (SpecialCommandInfo **)ptr;
	if (p) { SpecialCommandInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInfo_dump(SpecialCommandInfo *p, int tab);
// SpecialCommandInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInformation
typedef struct SpecialCommandInformation
{
	u8_t					 cross_id;
	SpecialCommandInfo		*special_command;
} SpecialCommandInformation;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandInformation *SpecialCommandInformation_new(u8_t cross_id, 
																				 SpecialCommandInfo *special_command, Dz1Error *err);
static __inline__ SpecialCommandInformation *SpecialCommandInformation_gen(Dz1Error *err) { return SpecialCommandInformation_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandInformation_copy(SpecialCommandInformation *dst, SpecialCommandInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandInformation *SpecialCommandInformation_clone(SpecialCommandInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInformation_purge(SpecialCommandInformation *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInformation_del(SpecialCommandInformation *p);
static __inline__ void SpecialCommandInformation_delAndSetNull(void *ptr)
{
	SpecialCommandInformation **p = (SpecialCommandInformation **)ptr;
	if (p) { SpecialCommandInformation_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInformation_dump(SpecialCommandInformation *p, int tab);
// SpecialCommandInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_is_emergency
typedef struct SpecialCommandPPCNumberList_is_emergency
{
	bool_t		is_emergency;
} SpecialCommandPPCNumberList_is_emergency;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList_is_emergency *SpecialCommandPPCNumberList_is_emergency_new(bool_t is_emergency, Dz1Error *err);
static __inline__ SpecialCommandPPCNumberList_is_emergency *SpecialCommandPPCNumberList_is_emergency_gen(Dz1Error *err) { return SpecialCommandPPCNumberList_is_emergency_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandPPCNumberList_is_emergency_copy(SpecialCommandPPCNumberList_is_emergency *dst, SpecialCommandPPCNumberList_is_emergency *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList_is_emergency *SpecialCommandPPCNumberList_is_emergency_clone(SpecialCommandPPCNumberList_is_emergency *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_is_emergency_purge(SpecialCommandPPCNumberList_is_emergency *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_is_emergency_del(SpecialCommandPPCNumberList_is_emergency *p);
static __inline__ void SpecialCommandPPCNumberList_is_emergency_delAndSetNull(void *ptr)
{
	SpecialCommandPPCNumberList_is_emergency **p = (SpecialCommandPPCNumberList_is_emergency **)ptr;
	if (p) { SpecialCommandPPCNumberList_is_emergency_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_is_emergency_dump(SpecialCommandPPCNumberList_is_emergency *p, int tab);
// SpecialCommandPPCNumberList_is_emergency
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_org_code
typedef struct SpecialCommandPPCNumberList_org_code
{
	u8_t	org_code;
} SpecialCommandPPCNumberList_org_code;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList_org_code *SpecialCommandPPCNumberList_org_code_new(u8_t org_code, Dz1Error *err);
static __inline__ SpecialCommandPPCNumberList_org_code *SpecialCommandPPCNumberList_org_code_gen(Dz1Error *err) { return SpecialCommandPPCNumberList_org_code_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandPPCNumberList_org_code_copy(SpecialCommandPPCNumberList_org_code *dst, SpecialCommandPPCNumberList_org_code *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList_org_code *SpecialCommandPPCNumberList_org_code_clone(SpecialCommandPPCNumberList_org_code *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_org_code_purge(SpecialCommandPPCNumberList_org_code *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_org_code_del(SpecialCommandPPCNumberList_org_code *p);
static __inline__ void SpecialCommandPPCNumberList_org_code_delAndSetNull(void *ptr)
{
	SpecialCommandPPCNumberList_org_code **p = (SpecialCommandPPCNumberList_org_code **)ptr;
	if (p) { SpecialCommandPPCNumberList_org_code_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_org_code_dump(SpecialCommandPPCNumberList_org_code *p, int tab);
// SpecialCommandPPCNumberList_org_code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_org_code_num
typedef struct SpecialCommandPPCNumberList_org_code_num
{
	u8_t	org_code_num;
} SpecialCommandPPCNumberList_org_code_num;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList_org_code_num *SpecialCommandPPCNumberList_org_code_num_new(u8_t org_code_num, Dz1Error *err);
static __inline__ SpecialCommandPPCNumberList_org_code_num *SpecialCommandPPCNumberList_org_code_num_gen(Dz1Error *err) { return SpecialCommandPPCNumberList_org_code_num_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandPPCNumberList_org_code_num_copy(SpecialCommandPPCNumberList_org_code_num *dst, SpecialCommandPPCNumberList_org_code_num *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList_org_code_num *SpecialCommandPPCNumberList_org_code_num_clone(SpecialCommandPPCNumberList_org_code_num *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_org_code_num_purge(SpecialCommandPPCNumberList_org_code_num *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_org_code_num_del(SpecialCommandPPCNumberList_org_code_num *p);
static __inline__ void SpecialCommandPPCNumberList_org_code_num_delAndSetNull(void *ptr)
{
	SpecialCommandPPCNumberList_org_code_num **p = (SpecialCommandPPCNumberList_org_code_num **)ptr;
	if (p) { SpecialCommandPPCNumberList_org_code_num_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_org_code_num_dump(SpecialCommandPPCNumberList_org_code_num *p, int tab);
// SpecialCommandPPCNumberList_org_code_num
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_org_code_type
typedef struct SpecialCommandPPCNumberList_org_code_type
{
	u32_t		org_code_type;
} SpecialCommandPPCNumberList_org_code_type;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList_org_code_type *SpecialCommandPPCNumberList_org_code_type_new(u32_t org_code_type, Dz1Error *err);
static __inline__ SpecialCommandPPCNumberList_org_code_type *SpecialCommandPPCNumberList_org_code_type_gen(Dz1Error *err) { return SpecialCommandPPCNumberList_org_code_type_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandPPCNumberList_org_code_type_copy(SpecialCommandPPCNumberList_org_code_type *dst, SpecialCommandPPCNumberList_org_code_type *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList_org_code_type *SpecialCommandPPCNumberList_org_code_type_clone(SpecialCommandPPCNumberList_org_code_type *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_org_code_type_purge(SpecialCommandPPCNumberList_org_code_type *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_org_code_type_del(SpecialCommandPPCNumberList_org_code_type *p);
static __inline__ void SpecialCommandPPCNumberList_org_code_type_delAndSetNull(void *ptr)
{
	SpecialCommandPPCNumberList_org_code_type **p = (SpecialCommandPPCNumberList_org_code_type **)ptr;
	if (p) { SpecialCommandPPCNumberList_org_code_type_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_org_code_type_dump(SpecialCommandPPCNumberList_org_code_type *p, int tab);
// SpecialCommandPPCNumberList_org_code_type
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList
typedef struct SpecialCommandPPCNumberList
{
	SpecialCommandPPCNumberList_is_emergency		*is_emergency;
	SpecialCommandPPCNumberList_org_code			*org_code;
	SpecialCommandPPCNumberList_org_code_num		*org_code_num;
	SpecialCommandPPCNumberList_org_code_type		*org_code_type;
	SpecialCommandPPCVehicleProperties				*vehicle_properties;
} SpecialCommandPPCNumberList;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList *SpecialCommandPPCNumberList_new(SpecialCommandPPCNumberList_is_emergency *is_emergency, 
																					 SpecialCommandPPCNumberList_org_code *org_code, 
																					 SpecialCommandPPCNumberList_org_code_num *org_code_num, 
																					 SpecialCommandPPCNumberList_org_code_type *org_code_type, 
																					 SpecialCommandPPCVehicleProperties *vehicle_properties, Dz1Error *err);
static __inline__ SpecialCommandPPCNumberList *SpecialCommandPPCNumberList_gen(Dz1Error *err) { return SpecialCommandPPCNumberList_new(NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandPPCNumberList_copy(SpecialCommandPPCNumberList *dst, SpecialCommandPPCNumberList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandPPCNumberList *SpecialCommandPPCNumberList_clone(SpecialCommandPPCNumberList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_purge(SpecialCommandPPCNumberList *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_del(SpecialCommandPPCNumberList *p);
static __inline__ void SpecialCommandPPCNumberList_delAndSetNull(void *ptr)
{
	SpecialCommandPPCNumberList **p = (SpecialCommandPPCNumberList **)ptr;
	if (p) { SpecialCommandPPCNumberList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandPPCNumberList_dump(SpecialCommandPPCNumberList *p, int tab);
// SpecialCommandPPCNumberList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInformationResponse
typedef struct SpecialCommandInformationResponse
{
	u8_t							 cross_id;
	SpecialCommandPPCNumberList		*ppc_register_num_list;
} SpecialCommandInformationResponse;

DZ1_CPPLINK DZ1_DLLPORT SpecialCommandInformationResponse *SpecialCommandInformationResponse_new(u8_t cross_id, Dz1Error *err);
static __inline__ SpecialCommandInformationResponse *SpecialCommandInformationResponse_gen(Dz1Error *err) { return SpecialCommandInformationResponse_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SpecialCommandInformationResponse_copy(SpecialCommandInformationResponse *dst, SpecialCommandInformationResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SpecialCommandInformationResponse *SpecialCommandInformationResponse_clone(SpecialCommandInformationResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInformationResponse_purge(SpecialCommandInformationResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInformationResponse_del(SpecialCommandInformationResponse *p);
static __inline__ void SpecialCommandInformationResponse_delAndSetNull(void *ptr)
{
	SpecialCommandInformationResponse **p = (SpecialCommandInformationResponse **)ptr;
	if (p) { SpecialCommandInformationResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SpecialCommandInformationResponse_dump(SpecialCommandInformationResponse *p, int tab);
// SpecialCommandInformationResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeData
typedef struct FirmwareUpgradeData
{
	u16_t		fw_module_id;
	u32_t		fw_module_size;
	Dz1Str		fname;
	u8_t		major_version;
	u8_t		minor_version;
	u8_t		module_version;
	u16_t		revision_version;
	bool_t		is_forced_upgrade;
	u8_t		reboot_option;
	u32_t		crc32;
} FirmwareUpgradeData;

DZ1_CPPLINK DZ1_DLLPORT FirmwareUpgradeData *FirmwareUpgradeData_new(u16_t fw_module_id, 
																	 u32_t fw_module_size, 
																	 Dz1Str fname, 
																	 u8_t major_version, 
																	 u8_t minor_version, 
																	 u8_t module_version, 
																	 u16_t revision_version, 
																	 bool_t is_forced_upgrade, 
																	 u8_t reboot_option, 
																	 u32_t crc32, Dz1Error *err);
static __inline__ FirmwareUpgradeData *FirmwareUpgradeData_gen(Dz1Error *err) { return FirmwareUpgradeData_new(0, 0, NULL, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t FirmwareUpgradeData_copy(FirmwareUpgradeData *dst, FirmwareUpgradeData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FirmwareUpgradeData *FirmwareUpgradeData_clone(FirmwareUpgradeData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeData_purge(FirmwareUpgradeData *p);
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeData_del(FirmwareUpgradeData *p);
static __inline__ void FirmwareUpgradeData_delAndSetNull(void *ptr)
{
	FirmwareUpgradeData **p = (FirmwareUpgradeData **)ptr;
	if (p) { FirmwareUpgradeData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeData_dump(FirmwareUpgradeData *p, int tab);
// FirmwareUpgradeData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeCommand
typedef struct FirmwareUpgradeCommand
{
	u8_t					 cross_id;
	FirmwareUpgradeData		*fw_upgrade_data;
} FirmwareUpgradeCommand;

DZ1_CPPLINK DZ1_DLLPORT FirmwareUpgradeCommand *FirmwareUpgradeCommand_new(u8_t cross_id, 
																		   FirmwareUpgradeData *fw_upgrade_data, Dz1Error *err);
static __inline__ FirmwareUpgradeCommand *FirmwareUpgradeCommand_gen(Dz1Error *err) { return FirmwareUpgradeCommand_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t FirmwareUpgradeCommand_copy(FirmwareUpgradeCommand *dst, FirmwareUpgradeCommand *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FirmwareUpgradeCommand *FirmwareUpgradeCommand_clone(FirmwareUpgradeCommand *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeCommand_purge(FirmwareUpgradeCommand *p);
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeCommand_del(FirmwareUpgradeCommand *p);
static __inline__ void FirmwareUpgradeCommand_delAndSetNull(void *ptr)
{
	FirmwareUpgradeCommand **p = (FirmwareUpgradeCommand **)ptr;
	if (p) { FirmwareUpgradeCommand_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeCommand_dump(FirmwareUpgradeCommand *p, int tab);
// FirmwareUpgradeCommand
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeErrorCode
typedef enum FirmwareUpgradeErrorCode
{
	FirmwareUpgradeErrorCode_no_error,
	FirmwareUpgradeErrorCode_lower_version_than_current_module,
	FirmwareUpgradeErrorCode_mismatched_vender_code,
	FirmwareUpgradeErrorCode_crc_error,
	FirmwareUpgradeErrorCode_module_size_exceeds_the_initial_size,
	FirmwareUpgradeErrorCode_other,
	FirmwareUpgradeErrorCode_max
} FirmwareUpgradeErrorCode;

DZ1_CPPLINK str_t FirmwareUpgradeErrorCodeStrA(FirmwareUpgradeErrorCode v);
DZ1_CPPLINK FirmwareUpgradeErrorCode FirmwareUpgradeErrorCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t FirmwareUpgradeErrorCodeStrW(FirmwareUpgradeErrorCode v);
DZ1_CPPLINK FirmwareUpgradeErrorCode FirmwareUpgradeErrorCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define FirmwareUpgradeErrorCodeStr FirmwareUpgradeErrorCodeStrW
#define FirmwareUpgradeErrorCodeFromStr FirmwareUpgradeErrorCodeFromStrW
#else // UNICODE
#define FirmwareUpgradeErrorCodeStr FirmwareUpgradeErrorCodeStrA
#define FirmwareUpgradeErrorCodeFromStr FirmwareUpgradeErrorCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define FirmwareUpgradeErrorCodeStr FirmwareUpgradeErrorCodeStrA
#define FirmwareUpgradeErrorCodeFromStr FirmwareUpgradeErrorCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT FirmwareUpgradeErrorCode *FirmwareUpgradeErrorCode_new(FirmwareUpgradeErrorCode *src, Dz1Error *err);
static __inline__ FirmwareUpgradeErrorCode *FirmwareUpgradeErrorCode_gen(Dz1Error *err) { FirmwareUpgradeErrorCode v = FirmwareUpgradeErrorCode_max; return FirmwareUpgradeErrorCode_new(&v, err); }
static __inline__ void FirmwareUpgradeErrorCode_del(FirmwareUpgradeErrorCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void FirmwareUpgradeErrorCode_delAndSetNull(void *ptr)
{
	FirmwareUpgradeErrorCode **p = (FirmwareUpgradeErrorCode **)ptr;
	if (p != NULL) { FirmwareUpgradeErrorCode_del(*p); *p = NULL; }
}
// FirmwareUpgradeErrorCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeError
typedef struct FirmwareUpgradeError
{
	FirmwareUpgradeErrorCode	code;
} FirmwareUpgradeError;

DZ1_CPPLINK DZ1_DLLPORT FirmwareUpgradeError *FirmwareUpgradeError_new(FirmwareUpgradeErrorCode code, Dz1Error *err);
static __inline__ FirmwareUpgradeError *FirmwareUpgradeError_gen(Dz1Error *err) { return FirmwareUpgradeError_new(FirmwareUpgradeErrorCode_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t FirmwareUpgradeError_copy(FirmwareUpgradeError *dst, FirmwareUpgradeError *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FirmwareUpgradeError *FirmwareUpgradeError_clone(FirmwareUpgradeError *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeError_purge(FirmwareUpgradeError *p);
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeError_del(FirmwareUpgradeError *p);
static __inline__ void FirmwareUpgradeError_delAndSetNull(void *ptr)
{
	FirmwareUpgradeError **p = (FirmwareUpgradeError **)ptr;
	if (p) { FirmwareUpgradeError_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeError_dump(FirmwareUpgradeError *p, int tab);
// FirmwareUpgradeError
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeResponse
typedef struct FirmwareUpgradeResponse
{
	u8_t					 cross_id;
	FirmwareUpgradeError	*error;
} FirmwareUpgradeResponse;

DZ1_CPPLINK DZ1_DLLPORT FirmwareUpgradeResponse *FirmwareUpgradeResponse_new(u8_t cross_id, 
																			 FirmwareUpgradeError *error, Dz1Error *err);
static __inline__ FirmwareUpgradeResponse *FirmwareUpgradeResponse_gen(Dz1Error *err) { return FirmwareUpgradeResponse_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t FirmwareUpgradeResponse_copy(FirmwareUpgradeResponse *dst, FirmwareUpgradeResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FirmwareUpgradeResponse *FirmwareUpgradeResponse_clone(FirmwareUpgradeResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeResponse_purge(FirmwareUpgradeResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeResponse_del(FirmwareUpgradeResponse *p);
static __inline__ void FirmwareUpgradeResponse_delAndSetNull(void *ptr)
{
	FirmwareUpgradeResponse **p = (FirmwareUpgradeResponse **)ptr;
	if (p) { FirmwareUpgradeResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void FirmwareUpgradeResponse_dump(FirmwareUpgradeResponse *p, int tab);
// FirmwareUpgradeResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerRequestPresent
typedef enum TrafficSignalControllerRequestPresent
{
	TrafficSignalControllerRequestPresent_control = 16,
	TrafficSignalControllerRequestPresent_status = 18,
	TrafficSignalControllerRequestPresent_detector = 34,
	TrafficSignalControllerRequestPresent_signal_phase_down = 48,
	TrafficSignalControllerRequestPresent_signal_phase_up = 50,
	TrafficSignalControllerRequestPresent_clock_down = 64,
	TrafficSignalControllerRequestPresent_clock_up = 66,
	TrafficSignalControllerRequestPresent_special_cmd = 80,
	TrafficSignalControllerRequestPresent_fw_upgrade_cmd = 86,
	TrafficSignalControllerRequestPresent_max
} TrafficSignalControllerRequestPresent;

DZ1_CPPLINK str_t TrafficSignalControllerRequestPresentStrA(TrafficSignalControllerRequestPresent v);
DZ1_CPPLINK TrafficSignalControllerRequestPresent TrafficSignalControllerRequestPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TrafficSignalControllerRequestPresentStrW(TrafficSignalControllerRequestPresent v);
DZ1_CPPLINK TrafficSignalControllerRequestPresent TrafficSignalControllerRequestPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define TrafficSignalControllerRequestPresentStr TrafficSignalControllerRequestPresentStrW
#define TrafficSignalControllerRequestPresentFromStr TrafficSignalControllerRequestPresentFromStrW
#else // UNICODE
#define TrafficSignalControllerRequestPresentStr TrafficSignalControllerRequestPresentStrA
#define TrafficSignalControllerRequestPresentFromStr TrafficSignalControllerRequestPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TrafficSignalControllerRequestPresentStr TrafficSignalControllerRequestPresentStrA
#define TrafficSignalControllerRequestPresentFromStr TrafficSignalControllerRequestPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerRequestPresent *TrafficSignalControllerRequestPresent_new(TrafficSignalControllerRequestPresent *src, Dz1Error *err);
static __inline__ TrafficSignalControllerRequestPresent *TrafficSignalControllerRequestPresent_gen(Dz1Error *err) { TrafficSignalControllerRequestPresent v = TrafficSignalControllerRequestPresent_max; return TrafficSignalControllerRequestPresent_new(&v, err); }
#define TrafficSignalControllerRequestPresent_clone             TrafficSignalControllerRequestPresent_new
static __inline__ void TrafficSignalControllerRequestPresent_del(TrafficSignalControllerRequestPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TrafficSignalControllerRequestPresent_delAndSetNull(void *ptr)
{
	TrafficSignalControllerRequestPresent **p = (TrafficSignalControllerRequestPresent **)ptr;
	if (p != NULL) { TrafficSignalControllerRequestPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerRequestPresent_dump(TrafficSignalControllerRequestPresent *v, int tab);
// TrafficSignalControllerRequestPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerRequest
typedef struct TrafficSignalControllerRequest
{
	TrafficSignalControllerRequestPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		CrossControlInformation				*control;
		CrossIndicator						*status;
		CrossIndicator						*detector;
		SignalPhaseInformationDownload		*signal_phase_down;
		CrossIndicator						*signal_phase_up;
		ClockInformationDownload			*clock_down;
		CrossIndicator						*clock_up;
		SpecialCommandInformation			*special_cmd;
		FirmwareUpgradeCommand				*fw_upgrade_cmd;
	} x;
} TrafficSignalControllerRequest;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerRequest *TrafficSignalControllerRequest_new(TrafficSignalControllerRequestPresent present, void *ptr, Dz1Error *err);
static __inline__ TrafficSignalControllerRequest *TrafficSignalControllerRequest_gen(Dz1Error *err) { return TrafficSignalControllerRequest_new(TrafficSignalControllerRequestPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  TrafficSignalControllerRequest_copy(TrafficSignalControllerRequest *dst, TrafficSignalControllerRequest *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerRequest *TrafficSignalControllerRequest_clone(TrafficSignalControllerRequest *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerRequest_purge(TrafficSignalControllerRequest *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerRequest_del(TrafficSignalControllerRequest *p);
static __inline__ void TrafficSignalControllerRequest_delAndSetNull(void *ptr)
{
	TrafficSignalControllerRequest **p = (TrafficSignalControllerRequest **)ptr;
	if (p != NULL) { TrafficSignalControllerRequest_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerRequest_dump(TrafficSignalControllerRequest *p, int tab);
// TrafficSignalControllerRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerResponsePresent
typedef enum TrafficSignalControllerResponsePresent
{
	TrafficSignalControllerResponsePresent_control = 17,
	TrafficSignalControllerResponsePresent_status = 19,
	TrafficSignalControllerResponsePresent_detector = 35,
	TrafficSignalControllerResponsePresent_signal_phase_down = 49,
	TrafficSignalControllerResponsePresent_signal_phase_up = 51,
	TrafficSignalControllerResponsePresent_clock_down = 65,
	TrafficSignalControllerResponsePresent_clock_up = 67,
	TrafficSignalControllerResponsePresent_special_cmd = 81,
	TrafficSignalControllerResponsePresent_fw_upgrade_cmd = 87,
	TrafficSignalControllerResponsePresent_max
} TrafficSignalControllerResponsePresent;

DZ1_CPPLINK str_t TrafficSignalControllerResponsePresentStrA(TrafficSignalControllerResponsePresent v);
DZ1_CPPLINK TrafficSignalControllerResponsePresent TrafficSignalControllerResponsePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TrafficSignalControllerResponsePresentStrW(TrafficSignalControllerResponsePresent v);
DZ1_CPPLINK TrafficSignalControllerResponsePresent TrafficSignalControllerResponsePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define TrafficSignalControllerResponsePresentStr TrafficSignalControllerResponsePresentStrW
#define TrafficSignalControllerResponsePresentFromStr TrafficSignalControllerResponsePresentFromStrW
#else // UNICODE
#define TrafficSignalControllerResponsePresentStr TrafficSignalControllerResponsePresentStrA
#define TrafficSignalControllerResponsePresentFromStr TrafficSignalControllerResponsePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TrafficSignalControllerResponsePresentStr TrafficSignalControllerResponsePresentStrA
#define TrafficSignalControllerResponsePresentFromStr TrafficSignalControllerResponsePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerResponsePresent *TrafficSignalControllerResponsePresent_new(TrafficSignalControllerResponsePresent *src, Dz1Error *err);
static __inline__ TrafficSignalControllerResponsePresent *TrafficSignalControllerResponsePresent_gen(Dz1Error *err) { TrafficSignalControllerResponsePresent v = TrafficSignalControllerResponsePresent_max; return TrafficSignalControllerResponsePresent_new(&v, err); }
#define TrafficSignalControllerResponsePresent_clone             TrafficSignalControllerResponsePresent_new
static __inline__ void TrafficSignalControllerResponsePresent_del(TrafficSignalControllerResponsePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TrafficSignalControllerResponsePresent_delAndSetNull(void *ptr)
{
	TrafficSignalControllerResponsePresent **p = (TrafficSignalControllerResponsePresent **)ptr;
	if (p != NULL) { TrafficSignalControllerResponsePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerResponsePresent_dump(TrafficSignalControllerResponsePresent *v, int tab);
// TrafficSignalControllerResponsePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerResponse
typedef struct TrafficSignalControllerResponse
{
	TrafficSignalControllerResponsePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		CrossIndicator							*control;
		CrossStatusInformation					*status;
		DetectorInformation						*detector;
		CrossIndicator							*signal_phase_down;
		SignalPhaseInformationUpload			*signal_phase_up;
		CrossIndicator							*clock_down;
		ClockInformationUpload					*clock_up;
		SpecialCommandInformationResponse		*special_cmd;
		FirmwareUpgradeResponse					*fw_upgrade_cmd;
	} x;
} TrafficSignalControllerResponse;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerResponse *TrafficSignalControllerResponse_new(TrafficSignalControllerResponsePresent present, void *ptr, Dz1Error *err);
static __inline__ TrafficSignalControllerResponse *TrafficSignalControllerResponse_gen(Dz1Error *err) { return TrafficSignalControllerResponse_new(TrafficSignalControllerResponsePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  TrafficSignalControllerResponse_copy(TrafficSignalControllerResponse *dst, TrafficSignalControllerResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerResponse *TrafficSignalControllerResponse_clone(TrafficSignalControllerResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerResponse_purge(TrafficSignalControllerResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerResponse_del(TrafficSignalControllerResponse *p);
static __inline__ void TrafficSignalControllerResponse_delAndSetNull(void *ptr)
{
	TrafficSignalControllerResponse **p = (TrafficSignalControllerResponse **)ptr;
	if (p != NULL) { TrafficSignalControllerResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerResponse_dump(TrafficSignalControllerResponse *p, int tab);
// TrafficSignalControllerResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestConfiguration
typedef struct TrafficSignalControllerTestConfiguration
{
	u16_t		port;
	bool_t		test_data;
	u8_t		cross_id;
	Dz1Str		req_str;
} TrafficSignalControllerTestConfiguration;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestConfiguration *TrafficSignalControllerTestConfiguration_new(u16_t port, 
																											   bool_t test_data, 
																											   u8_t cross_id, 
																											   Dz1Str req_str, Dz1Error *err);
static __inline__ TrafficSignalControllerTestConfiguration *TrafficSignalControllerTestConfiguration_gen(Dz1Error *err) { return TrafficSignalControllerTestConfiguration_new(0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerTestConfiguration_copy(TrafficSignalControllerTestConfiguration *dst, TrafficSignalControllerTestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestConfiguration *TrafficSignalControllerTestConfiguration_clone(TrafficSignalControllerTestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestConfiguration_purge(TrafficSignalControllerTestConfiguration *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestConfiguration_del(TrafficSignalControllerTestConfiguration *p);
static __inline__ void TrafficSignalControllerTestConfiguration_delAndSetNull(void *ptr)
{
	TrafficSignalControllerTestConfiguration **p = (TrafficSignalControllerTestConfiguration **)ptr;
	if (p) { TrafficSignalControllerTestConfiguration_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestConfiguration_dump(TrafficSignalControllerTestConfiguration *p, int tab);
// TrafficSignalControllerTestConfiguration
////////////////////////////////////////////////////////////////////////////////

#endif
