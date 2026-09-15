#ifndef _DZ1_TDC_CONFORMANCE1_EAM_DEF_H_
#define _DZ1_TDC_CONFORMANCE1_EAM_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_support.h"

#include "TechnicalRegulation1Eam.h"
////////////////////////////////////////////////////////////////////////////////
// Dz1CurrentLinkState
typedef struct Dz1CurrentLinkState
{
	Dz1Asn1UTF8Str* link_LinkIdNumber;
	u16_t           link_SpeedRate;
	u32_t* link_VolumeRate;
	u16_t* link_DensityRate;
	u16_t* link_TravelTimeQuantity;
	u16_t* link_DelayQuantity;
	u32_t* tfdt_VehicleQueueLengthQuantity;
	u8_t            tfdt_OccupancyPercent;
} Dz1CurrentLinkState;

DZ1_CPPLINK DZ1_DLLPORT Dz1CurrentLinkState* Dz1CurrentLinkState_new(Dz1Asn1UTF8Str* link_LinkIdNumber,
	u16_t link_SpeedRate,
	u8_t tfdt_OccupancyPercent, Dz1Error* err);
static __inline__ Dz1CurrentLinkState* Dz1CurrentLinkState_gen(Dz1Error* err) { return Dz1CurrentLinkState_new(NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1CurrentLinkState* Dz1CurrentLinkState_clone(Dz1CurrentLinkState* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CurrentLinkState_del(Dz1CurrentLinkState* p);
static __inline__ void Dz1CurrentLinkState_delAndSetNull(void* ptr)
{
	Dz1CurrentLinkState** p = (Dz1CurrentLinkState**)ptr;
	Dz1CurrentLinkState_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CurrentLinkState_dump(Dz1CurrentLinkState* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CurrentLinkState_fdump(FILE* fp, Dz1CurrentLinkState* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CurrentLinkState_fromASN(Dz1CurrentLinkState* dst, CurrentLinkState* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1CurrentLinkState* Dz1CurrentLinkState_newFromASN(CurrentLinkState* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CurrentLinkState_toASN(CurrentLinkState* dst, Dz1CurrentLinkState* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT CurrentLinkState* Dz1CurrentLinkState_toNewASN(Dz1CurrentLinkState* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1CurrentLinkState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CurrentLinkStateRequest
typedef Dz1Asn1UTF8Str Dz1CurrentLinkStateRequest;

#define Dz1CurrentLinkStateRequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1CurrentLinkStateRequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1CurrentLinkStateRequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1CurrentLinkStateRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CurrentLinkStateResponse
typedef struct Dz1CurrentLinkStateResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1CurrentLinkStateResponse* p, Dz1CurrentLinkState* data);
	Dz1CurrentLinkState** (*get_array)(struct Dz1CurrentLinkStateResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1CurrentLinkStateResponse* p, Dz1Error(*func)(void* ptr, Dz1CurrentLinkState* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1CurrentLinkStateResponse* p, Dz1Error(*func)(void* ptr, Dz1CurrentLinkState* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1CurrentLinkStateResponse* p, Dz1Error(*func)(void* ptr, Dz1CurrentLinkState* entry), void* ptr);
	unsigned int (*count)(struct Dz1CurrentLinkStateResponse* p);
} Dz1CurrentLinkStateResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1CurrentLinkStateResponse* Dz1CurrentLinkStateResponse_new(Dz1Error* err);
static __inline__ Dz1CurrentLinkStateResponse* Dz1CurrentLinkStateResponse_gen(Dz1Error* err) { return Dz1CurrentLinkStateResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1CurrentLinkStateResponse* Dz1CurrentLinkStateResponse_clone(Dz1CurrentLinkStateResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CurrentLinkStateResponse_del(Dz1CurrentLinkStateResponse* p);
static __inline__ void Dz1CurrentLinkStateResponse_delAndSetNull(void* ptr)
{
	Dz1CurrentLinkStateResponse** p = (Dz1CurrentLinkStateResponse**)ptr;
	Dz1CurrentLinkStateResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CurrentLinkStateResponse_dump(Dz1CurrentLinkStateResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CurrentLinkStateResponse_fdump(FILE* fp, Dz1CurrentLinkStateResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CurrentLinkStateResponse_fromASN(Dz1CurrentLinkStateResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1CurrentLinkStateResponse* Dz1CurrentLinkStateResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CurrentLinkStateResponse_toASN(ASN1List* dst, Dz1CurrentLinkStateResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1CurrentLinkStateResponse_toNewASN(Dz1CurrentLinkStateResponse* src, ASN1WorkSpace* ws, Dz1Error* err);


// Dz1CurrentLinkStateResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentity_evnt_DescriptionTypeEventCode
typedef enum Dz1EventIdentity_evnt_DescriptionTypeEventCode
{
	Dz1EventIdentity_evnt_DescriptionTypeEventCode_none = 0,
	Dz1EventIdentity_evnt_DescriptionTypeEventCode_other = 1,
	Dz1EventIdentity_evnt_DescriptionTypeEventCode_constructions = 2,
	Dz1EventIdentity_evnt_DescriptionTypeEventCode_planned_roadway_closure = 3,
	Dz1EventIdentity_evnt_DescriptionTypeEventCode_special_event = 4,
	Dz1EventIdentity_evnt_DescriptionTypeEventCode_max
} Dz1EventIdentity_evnt_DescriptionTypeEventCode;

DZ1_CPPLINK str_t Dz1EventIdentity_evnt_DescriptionTypeEventCodeStrA(Dz1EventIdentity_evnt_DescriptionTypeEventCode v);
DZ1_CPPLINK Dz1EventIdentity_evnt_DescriptionTypeEventCode Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1EventIdentity_evnt_DescriptionTypeEventCodeStrW(Dz1EventIdentity_evnt_DescriptionTypeEventCode v);
DZ1_CPPLINK Dz1EventIdentity_evnt_DescriptionTypeEventCode Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1EventIdentity_evnt_DescriptionTypeEventCodeStr Dz1EventIdentity_evnt_DescriptionTypeEventCodeStrW
#define Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStr Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStrW
#else // UNICODE
#define Dz1EventIdentity_evnt_DescriptionTypeEventCodeStr Dz1EventIdentity_evnt_DescriptionTypeEventCodeStrA
#define Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStr Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1EventIdentity_evnt_DescriptionTypeEventCodeStr Dz1EventIdentity_evnt_DescriptionTypeEventCodeStrA
#define Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStr Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1EventIdentity_evnt_DescriptionTypeEventCode* Dz1EventIdentity_evnt_DescriptionTypeEventCode_new(Dz1EventIdentity_evnt_DescriptionTypeEventCode* src, Dz1Error* err);
static __inline__ Dz1EventIdentity_evnt_DescriptionTypeEventCode* Dz1EventIdentity_evnt_DescriptionTypeEventCode_gen(Dz1Error* err) { Dz1EventIdentity_evnt_DescriptionTypeEventCode v = Dz1EventIdentity_evnt_DescriptionTypeEventCode_max; return Dz1EventIdentity_evnt_DescriptionTypeEventCode_new(&v, err); }
#define Dz1EventIdentity_evnt_DescriptionTypeEventCode_clone             Dz1EventIdentity_evnt_DescriptionTypeEventCode_new
#define Dz1EventIdentity_evnt_DescriptionTypeEventCode_del               Dz1u32_del
#define Dz1EventIdentity_evnt_DescriptionTypeEventCode_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentity_evnt_DescriptionTypeEventCode_dump(Dz1EventIdentity_evnt_DescriptionTypeEventCode* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentity_evnt_DescriptionTypeEventCode_fdump(FILE* fp, Dz1EventIdentity_evnt_DescriptionTypeEventCode* v, int tab);
// Dz1EventIdentity_evnt_DescriptionTypeEventCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode
typedef enum Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode
{
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_none = 0,
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_other = 1,
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_parade = 2,
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_sporting_event = 3,
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_demonstration = 4,
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_festival = 5,
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_performing_arts = 6,
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_dignitary_visit = 7,
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_max
} Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode;

DZ1_CPPLINK str_t Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStrA(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode v);
DZ1_CPPLINK Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStrW(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode v);
DZ1_CPPLINK Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStr Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStrW
#define Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStr Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStrW
#else // UNICODE
#define Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStr Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStrA
#define Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStr Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStr Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStrA
#define Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStr Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_new(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* src, Dz1Error* err);
static __inline__ Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_gen(Dz1Error* err) { Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode v = Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_max; return Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_new(&v, err); }
#define Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_clone             Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_new
#define Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_del               Dz1u32_del
#define Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_dump(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_fdump(FILE* fp, Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* v, int tab);
// Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode
typedef enum Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode
{
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_none = 0,
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_other = 1,
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_long_term_construction = 2,
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_short_term_construction = 3,
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_maintenance = 4,
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_emergency_maintenance = 5,
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_max
} Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode;

DZ1_CPPLINK str_t Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStrA(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode v);
DZ1_CPPLINK Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStrW(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode v);
DZ1_CPPLINK Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStr Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStrW
#define Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStr Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStrW
#else // UNICODE
#define Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStr Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStrA
#define Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStr Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStr Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStrA
#define Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStr Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_new(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* src, Dz1Error* err);
static __inline__ Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_gen(Dz1Error* err) { Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode v = Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_max; return Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_new(&v, err); }
#define Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_clone             Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_new
#define Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_del               Dz1u32_del
#define Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_dump(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_fdump(FILE* fp, Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* v, int tab);
// Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentity
typedef struct Dz1EventIdentity
{
	Dz1Asn1UTF8Str* node_NodeIdNumber;
	Dz1Asn1UTF8Str* link_LinkIdNumber;
	u32_t* evnt_IdentificationNumber;
	Dz1Asn1UTF8Str* evnt_LocationJurisDictionNameText;
	Dz1Asn1UTF8Str* evnt_LocationLinkIdNumber;
	Dz1Asn1UTF8Str* evnt_LocationNodeIdNumber;
	Dz1Asn1UTF8Str* evnt_LocationRoadwayNameText;
	Dz1EventIdentity_evnt_DescriptionTypeEventCode* evnt_DescriptionTypeEventCode;
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* evnt_DescriptionTypeSpecialEventCode;
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* evnt_DescriptionPlannedRoadWayClosureCode;
	u8_t                                                        evnt_LanesBlockedOrClosedNumber;
	Dz1Asn1BitStr* evnt_LanesShouldersBlockedCode;
	Dz1Asn1VisibleStr* evnt_TimelineStartGeneralizedTime;
	Dz1Asn1VisibleStr* evnt_TimelineEndGeneralizedTime;
	u32_t                                                       evnt_TimelineDurationTime;
} Dz1EventIdentity;

DZ1_CPPLINK DZ1_DLLPORT Dz1EventIdentity* Dz1EventIdentity_new(Dz1Asn1UTF8Str* node_NodeIdNumber,
	Dz1Asn1UTF8Str* link_LinkIdNumber,
	Dz1Asn1UTF8Str* evnt_LocationJurisDictionNameText,
	Dz1Asn1UTF8Str* evnt_LocationLinkIdNumber,
	Dz1Asn1UTF8Str* evnt_LocationNodeIdNumber,
	Dz1Asn1UTF8Str* evnt_LocationRoadwayNameText,
	u8_t evnt_LanesBlockedOrClosedNumber,
	Dz1Asn1BitStr* evnt_LanesShouldersBlockedCode,
	Dz1Asn1VisibleStr* evnt_TimelineStartGeneralizedTime,
	Dz1Asn1VisibleStr* evnt_TimelineEndGeneralizedTime,
	u32_t evnt_TimelineDurationTime, Dz1Error* err);
static __inline__ Dz1EventIdentity* Dz1EventIdentity_gen(Dz1Error* err) { return Dz1EventIdentity_new(NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1EventIdentity* Dz1EventIdentity_clone(Dz1EventIdentity* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentity_del(Dz1EventIdentity* p);
static __inline__ void Dz1EventIdentity_delAndSetNull(void* ptr)
{
	Dz1EventIdentity** p = (Dz1EventIdentity**)ptr;
	Dz1EventIdentity_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentity_dump(Dz1EventIdentity* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentity_fdump(FILE* fp, Dz1EventIdentity* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1EventIdentity_fromASN(Dz1EventIdentity* dst, EventIdentity* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1EventIdentity* Dz1EventIdentity_newFromASN(EventIdentity* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1EventIdentity_toASN(EventIdentity* dst, Dz1EventIdentity* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT EventIdentity* Dz1EventIdentity_toNewASN(Dz1EventIdentity* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1EventIdentity
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentityRequest
typedef Dz1Asn1UTF8Str Dz1EventIdentityRequest;

#define Dz1EventIdentityRequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1EventIdentityRequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1EventIdentityRequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1EventIdentityRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentityResponse
typedef struct Dz1EventIdentityResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1EventIdentityResponse* p, Dz1EventIdentity* data);
	Dz1EventIdentity** (*get_array)(struct Dz1EventIdentityResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1EventIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1EventIdentity* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1EventIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1EventIdentity* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1EventIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1EventIdentity* entry), void* ptr);
	unsigned int (*count)(struct Dz1EventIdentityResponse* p);
} Dz1EventIdentityResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1EventIdentityResponse* Dz1EventIdentityResponse_new(Dz1Error* err);
static __inline__ Dz1EventIdentityResponse* Dz1EventIdentityResponse_gen(Dz1Error* err) { return Dz1EventIdentityResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1EventIdentityResponse* Dz1EventIdentityResponse_clone(Dz1EventIdentityResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentityResponse_del(Dz1EventIdentityResponse* p);
static __inline__ void Dz1EventIdentityResponse_delAndSetNull(void* ptr)
{
	Dz1EventIdentityResponse** p = (Dz1EventIdentityResponse**)ptr;
	Dz1EventIdentityResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentityResponse_dump(Dz1EventIdentityResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1EventIdentityResponse_fdump(FILE* fp, Dz1EventIdentityResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1EventIdentityResponse_fromASN(Dz1EventIdentityResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1EventIdentityResponse* Dz1EventIdentityResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1EventIdentityResponse_toASN(ASN1List* dst, Dz1EventIdentityResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1EventIdentityResponse_toNewASN(Dz1EventIdentityResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1EventIdentityResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentIdentity
typedef struct Dz1IncidentIdentity
{
	Dz1Asn1UTF8Str* node_NodeIdNumber;
	Dz1Asn1UTF8Str* link_LinkIdNumber;
	u16_t* evnt_LocationLinearDistanceOffsetBeginNumber;
	u16_t* evnt_LinearDistanceoffsetEndNumber;
	Dz1Asn1VisibleStr* evnt_UpdateGeneralizedTime;
	u8_t* evnt_IncidentHumanFatalitiesCountQuantity;
	u8_t* evnt_IncidentHumanInjuriesCountQuantity;
	Dz1Asn1BitStr* evnt_IncidentPropertyDamageCode;
	Dz1Asn1UTF8Str* evnt_IncidentPropertyDamageOther;
} Dz1IncidentIdentity;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentIdentity* Dz1IncidentIdentity_new(Dz1Asn1UTF8Str* node_NodeIdNumber,
	Dz1Asn1UTF8Str* link_LinkIdNumber,
	Dz1Asn1VisibleStr* evnt_UpdateGeneralizedTime,
	Dz1Asn1BitStr* evnt_IncidentPropertyDamageCode, Dz1Error* err);
static __inline__ Dz1IncidentIdentity* Dz1IncidentIdentity_gen(Dz1Error* err) { return Dz1IncidentIdentity_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentIdentity* Dz1IncidentIdentity_clone(Dz1IncidentIdentity* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentIdentity_del(Dz1IncidentIdentity* p);
static __inline__ void Dz1IncidentIdentity_delAndSetNull(void* ptr)
{
	Dz1IncidentIdentity** p = (Dz1IncidentIdentity**)ptr;
	Dz1IncidentIdentity_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentIdentity_dump(Dz1IncidentIdentity* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentIdentity_fdump(FILE* fp, Dz1IncidentIdentity* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentIdentity_fromASN(Dz1IncidentIdentity* dst, IncidentIdentity* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentIdentity* Dz1IncidentIdentity_newFromASN(IncidentIdentity* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentIdentity_toASN(IncidentIdentity* dst, Dz1IncidentIdentity* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT IncidentIdentity* Dz1IncidentIdentity_toNewASN(Dz1IncidentIdentity* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1IncidentIdentity
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentIdentityRequest
typedef Dz1Asn1UTF8Str Dz1IncidentIdentityRequest;

#define Dz1IncidentIdentityRequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1IncidentIdentityRequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1IncidentIdentityRequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1IncidentIdentityRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentIdentityResponse
typedef struct Dz1IncidentIdentityResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1IncidentIdentityResponse* p, Dz1IncidentIdentity* data);
	Dz1IncidentIdentity** (*get_array)(struct Dz1IncidentIdentityResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1IncidentIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentIdentity* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1IncidentIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentIdentity* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1IncidentIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentIdentity* entry), void* ptr);
	unsigned int (*count)(struct Dz1IncidentIdentityResponse* p);
} Dz1IncidentIdentityResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentIdentityResponse* Dz1IncidentIdentityResponse_new(Dz1Error* err);
static __inline__ Dz1IncidentIdentityResponse* Dz1IncidentIdentityResponse_gen(Dz1Error* err) { return Dz1IncidentIdentityResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentIdentityResponse* Dz1IncidentIdentityResponse_clone(Dz1IncidentIdentityResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentIdentityResponse_del(Dz1IncidentIdentityResponse* p);
static __inline__ void Dz1IncidentIdentityResponse_delAndSetNull(void* ptr)
{
	Dz1IncidentIdentityResponse** p = (Dz1IncidentIdentityResponse**)ptr;
	Dz1IncidentIdentityResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentIdentityResponse_dump(Dz1IncidentIdentityResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentIdentityResponse_fdump(FILE* fp, Dz1IncidentIdentityResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentIdentityResponse_fromASN(Dz1IncidentIdentityResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentIdentityResponse* Dz1IncidentIdentityResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentIdentityResponse_toASN(ASN1List* dst, Dz1IncidentIdentityResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1IncidentIdentityResponse_toNewASN(Dz1IncidentIdentityResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1IncidentIdentityResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode
typedef enum Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode
{
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_other_no_additional_information_required = 0,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_other_additional_information_required = 1,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_vehicular_accident = 2,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_weather_related_incident = 3,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_stalled_vehicle = 4,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_vehicle_fire = 5,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_roadway_debris = 6,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_hazmat_spill = 7,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_earthquake = 8,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_landslide = 9,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_flood = 10,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_typhoon = 11,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_unplanned_demonstration = 12,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_increased_traffice_volume = 13,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_max
} Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode;

DZ1_CPPLINK str_t Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStrA(Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode v);
DZ1_CPPLINK Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStrW(Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode v);
DZ1_CPPLINK Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStr Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStrW
#define Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStr Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStrW
#else // UNICODE
#define Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStr Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStrA
#define Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStr Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStr Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStrA
#define Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStr Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_new(Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* src, Dz1Error* err);
static __inline__ Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_gen(Dz1Error* err) { Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode v = Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_max; return Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_new(&v, err); }
#define Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_clone             Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_new
#define Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_del               Dz1u32_del
#define Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_dump(Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_fdump(FILE* fp, Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* v, int tab);
// Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditions_evnt_IncidentStatusCode
typedef enum Dz1IncidentConditions_evnt_IncidentStatusCode
{
	Dz1IncidentConditions_evnt_IncidentStatusCode_other_no_additional_information_required = 0,
	Dz1IncidentConditions_evnt_IncidentStatusCode_other_additional_information_required = 1,
	Dz1IncidentConditions_evnt_IncidentStatusCode_incident_detected = 2,
	Dz1IncidentConditions_evnt_IncidentStatusCode_confirmed_and_responding = 3,
	Dz1IncidentConditions_evnt_IncidentStatusCode_cleared_and_recovering = 4,
	Dz1IncidentConditions_evnt_IncidentStatusCode_over_and_done = 5,
	Dz1IncidentConditions_evnt_IncidentStatusCode_other = 6,
	Dz1IncidentConditions_evnt_IncidentStatusCode_max
} Dz1IncidentConditions_evnt_IncidentStatusCode;

DZ1_CPPLINK str_t Dz1IncidentConditions_evnt_IncidentStatusCodeStrA(Dz1IncidentConditions_evnt_IncidentStatusCode v);
DZ1_CPPLINK Dz1IncidentConditions_evnt_IncidentStatusCode Dz1IncidentConditions_evnt_IncidentStatusCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1IncidentConditions_evnt_IncidentStatusCodeStrW(Dz1IncidentConditions_evnt_IncidentStatusCode v);
DZ1_CPPLINK Dz1IncidentConditions_evnt_IncidentStatusCode Dz1IncidentConditions_evnt_IncidentStatusCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1IncidentConditions_evnt_IncidentStatusCodeStr Dz1IncidentConditions_evnt_IncidentStatusCodeStrW
#define Dz1IncidentConditions_evnt_IncidentStatusCodeFromStr Dz1IncidentConditions_evnt_IncidentStatusCodeFromStrW
#else // UNICODE
#define Dz1IncidentConditions_evnt_IncidentStatusCodeStr Dz1IncidentConditions_evnt_IncidentStatusCodeStrA
#define Dz1IncidentConditions_evnt_IncidentStatusCodeFromStr Dz1IncidentConditions_evnt_IncidentStatusCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1IncidentConditions_evnt_IncidentStatusCodeStr Dz1IncidentConditions_evnt_IncidentStatusCodeStrA
#define Dz1IncidentConditions_evnt_IncidentStatusCodeFromStr Dz1IncidentConditions_evnt_IncidentStatusCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentConditions_evnt_IncidentStatusCode* Dz1IncidentConditions_evnt_IncidentStatusCode_new(Dz1IncidentConditions_evnt_IncidentStatusCode* src, Dz1Error* err);
static __inline__ Dz1IncidentConditions_evnt_IncidentStatusCode* Dz1IncidentConditions_evnt_IncidentStatusCode_gen(Dz1Error* err) { Dz1IncidentConditions_evnt_IncidentStatusCode v = Dz1IncidentConditions_evnt_IncidentStatusCode_max; return Dz1IncidentConditions_evnt_IncidentStatusCode_new(&v, err); }
#define Dz1IncidentConditions_evnt_IncidentStatusCode_clone             Dz1IncidentConditions_evnt_IncidentStatusCode_new
#define Dz1IncidentConditions_evnt_IncidentStatusCode_del               Dz1u32_del
#define Dz1IncidentConditions_evnt_IncidentStatusCode_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditions_evnt_IncidentStatusCode_dump(Dz1IncidentConditions_evnt_IncidentStatusCode* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditions_evnt_IncidentStatusCode_fdump(FILE* fp, Dz1IncidentConditions_evnt_IncidentStatusCode* v, int tab);
// Dz1IncidentConditions_evnt_IncidentStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditions_evnt_UpdateTypeCode
typedef enum Dz1IncidentConditions_evnt_UpdateTypeCode
{
	Dz1IncidentConditions_evnt_UpdateTypeCode_other_no_additional_information_required = 0,
	Dz1IncidentConditions_evnt_UpdateTypeCode_other_additional_information_required = 1,
	Dz1IncidentConditions_evnt_UpdateTypeCode_new_code = 2,
	Dz1IncidentConditions_evnt_UpdateTypeCode_update = 3,
	Dz1IncidentConditions_evnt_UpdateTypeCode_delete = 4,
	Dz1IncidentConditions_evnt_UpdateTypeCode_clear_or_closed = 5,
	Dz1IncidentConditions_evnt_UpdateTypeCode_max
} Dz1IncidentConditions_evnt_UpdateTypeCode;

DZ1_CPPLINK str_t Dz1IncidentConditions_evnt_UpdateTypeCodeStrA(Dz1IncidentConditions_evnt_UpdateTypeCode v);
DZ1_CPPLINK Dz1IncidentConditions_evnt_UpdateTypeCode Dz1IncidentConditions_evnt_UpdateTypeCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1IncidentConditions_evnt_UpdateTypeCodeStrW(Dz1IncidentConditions_evnt_UpdateTypeCode v);
DZ1_CPPLINK Dz1IncidentConditions_evnt_UpdateTypeCode Dz1IncidentConditions_evnt_UpdateTypeCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1IncidentConditions_evnt_UpdateTypeCodeStr Dz1IncidentConditions_evnt_UpdateTypeCodeStrW
#define Dz1IncidentConditions_evnt_UpdateTypeCodeFromStr Dz1IncidentConditions_evnt_UpdateTypeCodeFromStrW
#else // UNICODE
#define Dz1IncidentConditions_evnt_UpdateTypeCodeStr Dz1IncidentConditions_evnt_UpdateTypeCodeStrA
#define Dz1IncidentConditions_evnt_UpdateTypeCodeFromStr Dz1IncidentConditions_evnt_UpdateTypeCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1IncidentConditions_evnt_UpdateTypeCodeStr Dz1IncidentConditions_evnt_UpdateTypeCodeStrA
#define Dz1IncidentConditions_evnt_UpdateTypeCodeFromStr Dz1IncidentConditions_evnt_UpdateTypeCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentConditions_evnt_UpdateTypeCode* Dz1IncidentConditions_evnt_UpdateTypeCode_new(Dz1IncidentConditions_evnt_UpdateTypeCode* src, Dz1Error* err);
static __inline__ Dz1IncidentConditions_evnt_UpdateTypeCode* Dz1IncidentConditions_evnt_UpdateTypeCode_gen(Dz1Error* err) { Dz1IncidentConditions_evnt_UpdateTypeCode v = Dz1IncidentConditions_evnt_UpdateTypeCode_max; return Dz1IncidentConditions_evnt_UpdateTypeCode_new(&v, err); }
#define Dz1IncidentConditions_evnt_UpdateTypeCode_clone             Dz1IncidentConditions_evnt_UpdateTypeCode_new
#define Dz1IncidentConditions_evnt_UpdateTypeCode_del               Dz1u32_del
#define Dz1IncidentConditions_evnt_UpdateTypeCode_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditions_evnt_UpdateTypeCode_dump(Dz1IncidentConditions_evnt_UpdateTypeCode* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditions_evnt_UpdateTypeCode_fdump(FILE* fp, Dz1IncidentConditions_evnt_UpdateTypeCode* v, int tab);
// Dz1IncidentConditions_evnt_UpdateTypeCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditions
typedef struct Dz1IncidentConditions
{
	Dz1Asn1UTF8Str* node_NodeIdNumber;
	Dz1Asn1UTF8Str* link_LinkIdNumber;
	Dz1Asn1UTF8Str* orgn_ContatOrganizationNameText;
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode  evnt_DescriptionTypeIncidentCode;
	Dz1Asn1UTF8Str* evnt_DescriptionTypeIncidentOther;
	Dz1Asn1BitStr* evnt_IncidentVehiclesInvolvedCode;
	Dz1Asn1UTF8Str* evnt_IncidentVehiclesInvolvedOther;
	Dz1IncidentConditions_evnt_IncidentStatusCode           evnt_IncidentStatusCode;
	Dz1Asn1UTF8Str* evnt_IncidentStatusOther;
	Dz1IncidentConditions_evnt_UpdateTypeCode               evnt_UpdateTypeCode;
	Dz1Asn1UTF8Str* evnt_UpdateTypeOther;
} Dz1IncidentConditions;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentConditions* Dz1IncidentConditions_new(Dz1Asn1UTF8Str* node_NodeIdNumber,
	Dz1Asn1UTF8Str* link_LinkIdNumber,
	Dz1Asn1UTF8Str* orgn_ContatOrganizationNameText,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode evnt_DescriptionTypeIncidentCode,
	Dz1Asn1BitStr* evnt_IncidentVehiclesInvolvedCode,
	Dz1IncidentConditions_evnt_IncidentStatusCode evnt_IncidentStatusCode,
	Dz1IncidentConditions_evnt_UpdateTypeCode evnt_UpdateTypeCode, Dz1Error* err);
static __inline__ Dz1IncidentConditions* Dz1IncidentConditions_gen(Dz1Error* err) { return Dz1IncidentConditions_new(NULL, NULL, NULL, Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_max, NULL, Dz1IncidentConditions_evnt_IncidentStatusCode_max, Dz1IncidentConditions_evnt_UpdateTypeCode_max, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentConditions* Dz1IncidentConditions_clone(Dz1IncidentConditions* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditions_del(Dz1IncidentConditions* p);
static __inline__ void Dz1IncidentConditions_delAndSetNull(void* ptr)
{
	Dz1IncidentConditions** p = (Dz1IncidentConditions**)ptr;
	Dz1IncidentConditions_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditions_dump(Dz1IncidentConditions* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditions_fdump(FILE* fp, Dz1IncidentConditions* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentConditions_fromASN(Dz1IncidentConditions* dst, IncidentConditions* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentConditions* Dz1IncidentConditions_newFromASN(IncidentConditions* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentConditions_toASN(IncidentConditions* dst, Dz1IncidentConditions* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT IncidentConditions* Dz1IncidentConditions_toNewASN(Dz1IncidentConditions* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1IncidentConditions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditionsRequest
typedef Dz1Asn1UTF8Str Dz1IncidentConditionsRequest;

#define Dz1IncidentConditionsRequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1IncidentConditionsRequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1IncidentConditionsRequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1IncidentConditionsRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditionsResponse
typedef struct Dz1IncidentConditionsResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1IncidentConditionsResponse* p, Dz1IncidentConditions* data);
	Dz1IncidentConditions** (*get_array)(struct Dz1IncidentConditionsResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1IncidentConditionsResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentConditions* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1IncidentConditionsResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentConditions* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1IncidentConditionsResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentConditions* entry), void* ptr);
	unsigned int (*count)(struct Dz1IncidentConditionsResponse* p);
} Dz1IncidentConditionsResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentConditionsResponse* Dz1IncidentConditionsResponse_new(Dz1Error* err);
static __inline__ Dz1IncidentConditionsResponse* Dz1IncidentConditionsResponse_gen(Dz1Error* err) { return Dz1IncidentConditionsResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentConditionsResponse* Dz1IncidentConditionsResponse_clone(Dz1IncidentConditionsResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditionsResponse_del(Dz1IncidentConditionsResponse* p);
static __inline__ void Dz1IncidentConditionsResponse_delAndSetNull(void* ptr)
{
	Dz1IncidentConditionsResponse** p = (Dz1IncidentConditionsResponse**)ptr;
	Dz1IncidentConditionsResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditionsResponse_dump(Dz1IncidentConditionsResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentConditionsResponse_fdump(FILE* fp, Dz1IncidentConditionsResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentConditionsResponse_fromASN(Dz1IncidentConditionsResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentConditionsResponse* Dz1IncidentConditionsResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentConditionsResponse_toASN(ASN1List* dst, Dz1IncidentConditionsResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1IncidentConditionsResponse_toNewASN(Dz1IncidentConditionsResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1IncidentConditionsResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RoadwaySurfaceStatus
typedef struct Dz1RoadwaySurfaceStatus
{
	Dz1Asn1UTF8Str* node_NodeIdNumber;
	Dz1Asn1UTF8Str* link_LinkIdNumber;
	Dz1Asn1BitStr* link_SurfaceConditionCode;
	Dz1Asn1BitStr* link_LandBlockedOrClosedCode;
	u16_t* evsn_DataSurfacePrecipitationDepth;
	u16_t* evsn_DataSurfaceTemperatureQuantity;
} Dz1RoadwaySurfaceStatus;

DZ1_CPPLINK DZ1_DLLPORT Dz1RoadwaySurfaceStatus* Dz1RoadwaySurfaceStatus_new(Dz1Asn1UTF8Str* node_NodeIdNumber,
	Dz1Asn1UTF8Str* link_LinkIdNumber,
	Dz1Asn1BitStr* link_SurfaceConditionCode,
	Dz1Asn1BitStr* link_LandBlockedOrClosedCode, Dz1Error* err);
static __inline__ Dz1RoadwaySurfaceStatus* Dz1RoadwaySurfaceStatus_gen(Dz1Error* err) { return Dz1RoadwaySurfaceStatus_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1RoadwaySurfaceStatus* Dz1RoadwaySurfaceStatus_clone(Dz1RoadwaySurfaceStatus* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RoadwaySurfaceStatus_del(Dz1RoadwaySurfaceStatus* p);
static __inline__ void Dz1RoadwaySurfaceStatus_delAndSetNull(void* ptr)
{
	Dz1RoadwaySurfaceStatus** p = (Dz1RoadwaySurfaceStatus**)ptr;
	Dz1RoadwaySurfaceStatus_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RoadwaySurfaceStatus_dump(Dz1RoadwaySurfaceStatus* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RoadwaySurfaceStatus_fdump(FILE* fp, Dz1RoadwaySurfaceStatus* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1RoadwaySurfaceStatus_fromASN(Dz1RoadwaySurfaceStatus* dst, RoadwaySurfaceStatus* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1RoadwaySurfaceStatus* Dz1RoadwaySurfaceStatus_newFromASN(RoadwaySurfaceStatus* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1RoadwaySurfaceStatus_toASN(RoadwaySurfaceStatus* dst, Dz1RoadwaySurfaceStatus* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT RoadwaySurfaceStatus* Dz1RoadwaySurfaceStatus_toNewASN(Dz1RoadwaySurfaceStatus* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1RoadwaySurfaceStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RoadwaySurfaceStatusRequest
typedef Dz1Asn1UTF8Str Dz1RoadwaySurfaceStatusRequest;

#define Dz1RoadwaySurfaceStatusRequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1RoadwaySurfaceStatusRequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1RoadwaySurfaceStatusRequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1RoadwaySurfaceStatusRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RoadwaySurfaceStatusResponse
typedef struct Dz1RoadwaySurfaceStatusResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1RoadwaySurfaceStatusResponse* p, Dz1RoadwaySurfaceStatus* data);
	Dz1RoadwaySurfaceStatus** (*get_array)(struct Dz1RoadwaySurfaceStatusResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1RoadwaySurfaceStatusResponse* p, Dz1Error(*func)(void* ptr, Dz1RoadwaySurfaceStatus* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1RoadwaySurfaceStatusResponse* p, Dz1Error(*func)(void* ptr, Dz1RoadwaySurfaceStatus* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1RoadwaySurfaceStatusResponse* p, Dz1Error(*func)(void* ptr, Dz1RoadwaySurfaceStatus* entry), void* ptr);
	unsigned int (*count)(struct Dz1RoadwaySurfaceStatusResponse* p);
} Dz1RoadwaySurfaceStatusResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1RoadwaySurfaceStatusResponse* Dz1RoadwaySurfaceStatusResponse_new(Dz1Error* err);
static __inline__ Dz1RoadwaySurfaceStatusResponse* Dz1RoadwaySurfaceStatusResponse_gen(Dz1Error* err) { return Dz1RoadwaySurfaceStatusResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1RoadwaySurfaceStatusResponse* Dz1RoadwaySurfaceStatusResponse_clone(Dz1RoadwaySurfaceStatusResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RoadwaySurfaceStatusResponse_del(Dz1RoadwaySurfaceStatusResponse* p);
static __inline__ void Dz1RoadwaySurfaceStatusResponse_delAndSetNull(void* ptr)
{
	Dz1RoadwaySurfaceStatusResponse** p = (Dz1RoadwaySurfaceStatusResponse**)ptr;
	Dz1RoadwaySurfaceStatusResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RoadwaySurfaceStatusResponse_dump(Dz1RoadwaySurfaceStatusResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RoadwaySurfaceStatusResponse_fdump(FILE* fp, Dz1RoadwaySurfaceStatusResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1RoadwaySurfaceStatusResponse_fromASN(Dz1RoadwaySurfaceStatusResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1RoadwaySurfaceStatusResponse* Dz1RoadwaySurfaceStatusResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1RoadwaySurfaceStatusResponse_toASN(ASN1List* dst, Dz1RoadwaySurfaceStatusResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1RoadwaySurfaceStatusResponse_toNewASN(Dz1RoadwaySurfaceStatusResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1RoadwaySurfaceStatusResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WeatherInformation_wthr_ForecastOrActualCode
typedef enum Dz1WeatherInformation_wthr_ForecastOrActualCode
{
	Dz1WeatherInformation_wthr_ForecastOrActualCode_actual = 0,
	Dz1WeatherInformation_wthr_ForecastOrActualCode_forecast = 1,
	Dz1WeatherInformation_wthr_ForecastOrActualCode_max
} Dz1WeatherInformation_wthr_ForecastOrActualCode;

DZ1_CPPLINK str_t Dz1WeatherInformation_wthr_ForecastOrActualCodeStrA(Dz1WeatherInformation_wthr_ForecastOrActualCode v);
DZ1_CPPLINK Dz1WeatherInformation_wthr_ForecastOrActualCode Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1WeatherInformation_wthr_ForecastOrActualCodeStrW(Dz1WeatherInformation_wthr_ForecastOrActualCode v);
DZ1_CPPLINK Dz1WeatherInformation_wthr_ForecastOrActualCode Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1WeatherInformation_wthr_ForecastOrActualCodeStr Dz1WeatherInformation_wthr_ForecastOrActualCodeStrW
#define Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStr Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStrW
#else // UNICODE
#define Dz1WeatherInformation_wthr_ForecastOrActualCodeStr Dz1WeatherInformation_wthr_ForecastOrActualCodeStrA
#define Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStr Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1WeatherInformation_wthr_ForecastOrActualCodeStr Dz1WeatherInformation_wthr_ForecastOrActualCodeStrA
#define Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStr Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1WeatherInformation_wthr_ForecastOrActualCode* Dz1WeatherInformation_wthr_ForecastOrActualCode_new(Dz1WeatherInformation_wthr_ForecastOrActualCode* src, Dz1Error* err);
static __inline__ Dz1WeatherInformation_wthr_ForecastOrActualCode* Dz1WeatherInformation_wthr_ForecastOrActualCode_gen(Dz1Error* err) { Dz1WeatherInformation_wthr_ForecastOrActualCode v = Dz1WeatherInformation_wthr_ForecastOrActualCode_max; return Dz1WeatherInformation_wthr_ForecastOrActualCode_new(&v, err); }
#define Dz1WeatherInformation_wthr_ForecastOrActualCode_clone             Dz1WeatherInformation_wthr_ForecastOrActualCode_new
#define Dz1WeatherInformation_wthr_ForecastOrActualCode_del               Dz1u32_del
#define Dz1WeatherInformation_wthr_ForecastOrActualCode_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformation_wthr_ForecastOrActualCode_dump(Dz1WeatherInformation_wthr_ForecastOrActualCode* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformation_wthr_ForecastOrActualCode_fdump(FILE* fp, Dz1WeatherInformation_wthr_ForecastOrActualCode* v, int tab);
// Dz1WeatherInformation_wthr_ForecastOrActualCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WeatherInformation_wthr_WindDirectionCode
typedef enum Dz1WeatherInformation_wthr_WindDirectionCode
{
	Dz1WeatherInformation_wthr_WindDirectionCode_north = 0,
	Dz1WeatherInformation_wthr_WindDirectionCode_south = 1,
	Dz1WeatherInformation_wthr_WindDirectionCode_west = 2,
	Dz1WeatherInformation_wthr_WindDirectionCode_east = 3,
	Dz1WeatherInformation_wthr_WindDirectionCode_northwest = 4,
	Dz1WeatherInformation_wthr_WindDirectionCode_northeast = 5,
	Dz1WeatherInformation_wthr_WindDirectionCode_southwest = 6,
	Dz1WeatherInformation_wthr_WindDirectionCode_southeast = 7,
	Dz1WeatherInformation_wthr_WindDirectionCode_max
} Dz1WeatherInformation_wthr_WindDirectionCode;

DZ1_CPPLINK str_t Dz1WeatherInformation_wthr_WindDirectionCodeStrA(Dz1WeatherInformation_wthr_WindDirectionCode v);
DZ1_CPPLINK Dz1WeatherInformation_wthr_WindDirectionCode Dz1WeatherInformation_wthr_WindDirectionCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1WeatherInformation_wthr_WindDirectionCodeStrW(Dz1WeatherInformation_wthr_WindDirectionCode v);
DZ1_CPPLINK Dz1WeatherInformation_wthr_WindDirectionCode Dz1WeatherInformation_wthr_WindDirectionCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1WeatherInformation_wthr_WindDirectionCodeStr Dz1WeatherInformation_wthr_WindDirectionCodeStrW
#define Dz1WeatherInformation_wthr_WindDirectionCodeFromStr Dz1WeatherInformation_wthr_WindDirectionCodeFromStrW
#else // UNICODE
#define Dz1WeatherInformation_wthr_WindDirectionCodeStr Dz1WeatherInformation_wthr_WindDirectionCodeStrA
#define Dz1WeatherInformation_wthr_WindDirectionCodeFromStr Dz1WeatherInformation_wthr_WindDirectionCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1WeatherInformation_wthr_WindDirectionCodeStr Dz1WeatherInformation_wthr_WindDirectionCodeStrA
#define Dz1WeatherInformation_wthr_WindDirectionCodeFromStr Dz1WeatherInformation_wthr_WindDirectionCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1WeatherInformation_wthr_WindDirectionCode* Dz1WeatherInformation_wthr_WindDirectionCode_new(Dz1WeatherInformation_wthr_WindDirectionCode* src, Dz1Error* err);
static __inline__ Dz1WeatherInformation_wthr_WindDirectionCode* Dz1WeatherInformation_wthr_WindDirectionCode_gen(Dz1Error* err) { Dz1WeatherInformation_wthr_WindDirectionCode v = Dz1WeatherInformation_wthr_WindDirectionCode_max; return Dz1WeatherInformation_wthr_WindDirectionCode_new(&v, err); }
#define Dz1WeatherInformation_wthr_WindDirectionCode_clone             Dz1WeatherInformation_wthr_WindDirectionCode_new
#define Dz1WeatherInformation_wthr_WindDirectionCode_del               Dz1u32_del
#define Dz1WeatherInformation_wthr_WindDirectionCode_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformation_wthr_WindDirectionCode_dump(Dz1WeatherInformation_wthr_WindDirectionCode* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformation_wthr_WindDirectionCode_fdump(FILE* fp, Dz1WeatherInformation_wthr_WindDirectionCode* v, int tab);
// Dz1WeatherInformation_wthr_WindDirectionCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WeatherInformation
typedef struct Dz1WeatherInformation
{
	Dz1WeatherInformation_wthr_ForecastOrActualCode  wthr_ForecastOrActualCode;
	s8_t* wthr_TemperatureQuantity;
	s8_t* wthr_HighTemperatureQuantity;
	s8_t* wthr_LowTemperatureQuantity;
	Dz1Asn1BitStr* wthr_SpecialConditions;
	Dz1Asn1UTF8Str* wthr_SpecialConditionsOther;
	u8_t                                             wthr_ProbabilityPercent;
	u8_t* wthr_VisibilityQuantity;
	u8_t* wthr_WindSpeedQuantity;
	Dz1WeatherInformation_wthr_WindDirectionCode* wthr_WindDirectionCode;
	u8_t* wthr_HumidityQuantity;
	u8_t* wthr_PressureQuantity;
	Dz1Asn1VisibleStr* wthr_SunriseTimeGeneralizedTime;
	Dz1Asn1VisibleStr* wthr_SunsetTimeGeneralizedTime;
} Dz1WeatherInformation;

DZ1_CPPLINK DZ1_DLLPORT Dz1WeatherInformation* Dz1WeatherInformation_new(Dz1WeatherInformation_wthr_ForecastOrActualCode wthr_ForecastOrActualCode, u8_t wthr_ProbabilityPercent, Dz1Error* err);
static __inline__ Dz1WeatherInformation* Dz1WeatherInformation_gen(Dz1Error* err) { return Dz1WeatherInformation_new(Dz1WeatherInformation_wthr_ForecastOrActualCode_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1WeatherInformation* Dz1WeatherInformation_clone(Dz1WeatherInformation* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformation_del(Dz1WeatherInformation* p);
static __inline__ void Dz1WeatherInformation_delAndSetNull(void* ptr)
{
	Dz1WeatherInformation** p = (Dz1WeatherInformation**)ptr;
	Dz1WeatherInformation_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformation_dump(Dz1WeatherInformation* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformation_fdump(FILE* fp, Dz1WeatherInformation* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1WeatherInformation_fromASN(Dz1WeatherInformation* dst, WeatherInformation* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1WeatherInformation* Dz1WeatherInformation_newFromASN(WeatherInformation* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1WeatherInformation_toASN(WeatherInformation* dst, Dz1WeatherInformation* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT WeatherInformation* Dz1WeatherInformation_toNewASN(Dz1WeatherInformation* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1WeatherInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WeatherInformationRequest
typedef Dz1Asn1UTF8Str Dz1WeatherInformationRequest;

#define Dz1WeatherInformationRequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1WeatherInformationRequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1WeatherInformationRequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1WeatherInformationRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WeatherInformationResponse
typedef struct Dz1WeatherInformationResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1WeatherInformationResponse* p, Dz1WeatherInformation* data);
	Dz1WeatherInformation** (*get_array)(struct Dz1WeatherInformationResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1WeatherInformationResponse* p, Dz1Error(*func)(void* ptr, Dz1WeatherInformation* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1WeatherInformationResponse* p, Dz1Error(*func)(void* ptr, Dz1WeatherInformation* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1WeatherInformationResponse* p, Dz1Error(*func)(void* ptr, Dz1WeatherInformation* entry), void* ptr);
	unsigned int (*count)(struct Dz1WeatherInformationResponse* p);
} Dz1WeatherInformationResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1WeatherInformationResponse* Dz1WeatherInformationResponse_new(Dz1Error* err);
static __inline__ Dz1WeatherInformationResponse* Dz1WeatherInformationResponse_gen(Dz1Error* err) { return Dz1WeatherInformationResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1WeatherInformationResponse* Dz1WeatherInformationResponse_clone(Dz1WeatherInformationResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformationResponse_del(Dz1WeatherInformationResponse* p);
static __inline__ void Dz1WeatherInformationResponse_delAndSetNull(void* ptr)
{
	Dz1WeatherInformationResponse** p = (Dz1WeatherInformationResponse**)ptr;
	Dz1WeatherInformationResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformationResponse_dump(Dz1WeatherInformationResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WeatherInformationResponse_fdump(FILE* fp, Dz1WeatherInformationResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1WeatherInformationResponse_fromASN(Dz1WeatherInformationResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1WeatherInformationResponse* Dz1WeatherInformationResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1WeatherInformationResponse_toASN(ASN1List* dst, Dz1WeatherInformationResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1WeatherInformationResponse_toNewASN(Dz1WeatherInformationResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1WeatherInformationResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode
typedef enum Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode
{
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_opengrass = 0,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_opensand = 1,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_concrete_barrier_with_visibility_screens = 2,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_separate_roadways = 3,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_no_separation = 4,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_painted_median_no_access = 5,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_painted_MedianLeft_Turns = 6,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_concrete_barrier = 7,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_guardrail = 8,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_max
} Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode;

DZ1_CPPLINK str_t Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStrA(Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode v);
DZ1_CPPLINK Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStrW(Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode v);
DZ1_CPPLINK Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStr Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStrW
#define Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStr Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStrW
#else // UNICODE
#define Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStr Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStrA
#define Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStr Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStr Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStrA
#define Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStr Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_new(Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* src, Dz1Error* err);
static __inline__ Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_gen(Dz1Error* err) { Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode v = Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_max; return Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_new(&v, err); }
#define Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_clone             Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_new
#define Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_del               Dz1u32_del
#define Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_dump(Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_fdump(FILE* fp, Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* v, int tab);
// Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LinkRoadwayGeometry
typedef struct Dz1LinkRoadwayGeometry
{
	Dz1Asn1UTF8Str* link_BeginNodeIdNumber;
	s64_t* link_BiginNodeLatitudeLocation;
	u32_t* link_BeginNodeLongitudeLocation;
	Dz1Asn1UTF8Str* link_EndNodeIdNumber;
	s64_t* link_EndNodeLatitudeLocation;
	u32_t* link_EndNodeLongitudeLocation;
	Dz1Asn1UTF8Str* link_JurisdictionText;
	Dz1Asn1BitStr* link_TypeCode;
	Dz1Asn1UTF8Str* link_NameText;
	u32_t                                           link_LengthQuantity;
	Dz1Asn1BitStr* link_PavementTypeCode;
	u16_t* tfmg_LinkHeigthRestrictionQunatity;
	u16_t* tfmg_LinkLeftShoulderWidthQuantity;
	u16_t* tfmg_LinkLengthRestrictionQuatity;
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode  tfmg_LinkMedianTypeCode;
	u16_t                                           tfmg_LinkNumLanesNumber;
	u8_t                                            tfmg_LinkNumLanesOpenNumber;
	u16_t* tfmg_LinkRightShoulderWidthQuantity;
} Dz1LinkRoadwayGeometry;

DZ1_CPPLINK DZ1_DLLPORT Dz1LinkRoadwayGeometry* Dz1LinkRoadwayGeometry_new(Dz1Asn1UTF8Str* link_BeginNodeIdNumber,
	Dz1Asn1UTF8Str* link_EndNodeIdNumber,
	Dz1Asn1UTF8Str* link_JurisdictionText,
	Dz1Asn1BitStr* link_TypeCode,
	Dz1Asn1UTF8Str* link_NameText,
	u32_t link_LengthQuantity,
	Dz1Asn1BitStr* link_PavementTypeCode,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode tfmg_LinkMedianTypeCode,
	u16_t tfmg_LinkNumLanesNumber,
	u8_t tfmg_LinkNumLanesOpenNumber, Dz1Error* err);
static __inline__ Dz1LinkRoadwayGeometry* Dz1LinkRoadwayGeometry_gen(Dz1Error* err) { return Dz1LinkRoadwayGeometry_new(NULL, NULL, NULL, NULL, NULL, 0, NULL, Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_max, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1LinkRoadwayGeometry* Dz1LinkRoadwayGeometry_clone(Dz1LinkRoadwayGeometry* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LinkRoadwayGeometry_del(Dz1LinkRoadwayGeometry* p);
static __inline__ void Dz1LinkRoadwayGeometry_delAndSetNull(void* ptr)
{
	Dz1LinkRoadwayGeometry** p = (Dz1LinkRoadwayGeometry**)ptr;
	Dz1LinkRoadwayGeometry_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LinkRoadwayGeometry_dump(Dz1LinkRoadwayGeometry* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LinkRoadwayGeometry_fdump(FILE* fp, Dz1LinkRoadwayGeometry* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1LinkRoadwayGeometry_fromASN(Dz1LinkRoadwayGeometry* dst, LinkRoadwayGeometry* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1LinkRoadwayGeometry* Dz1LinkRoadwayGeometry_newFromASN(LinkRoadwayGeometry* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1LinkRoadwayGeometry_toASN(LinkRoadwayGeometry* dst, Dz1LinkRoadwayGeometry* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT LinkRoadwayGeometry* Dz1LinkRoadwayGeometry_toNewASN(Dz1LinkRoadwayGeometry* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1LinkRoadwayGeometry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LinkRoadwayGeometryRequest
typedef Dz1Asn1UTF8Str Dz1LinkRoadwayGeometryRequest;

#define Dz1LinkRoadwayGeometryRequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1LinkRoadwayGeometryRequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1LinkRoadwayGeometryRequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1LinkRoadwayGeometryRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LinkRoadwayGeometryResponse
typedef struct Dz1LinkRoadwayGeometryResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1LinkRoadwayGeometryResponse* p, Dz1LinkRoadwayGeometry* data);
	Dz1LinkRoadwayGeometry** (*get_array)(struct Dz1LinkRoadwayGeometryResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1LinkRoadwayGeometryResponse* p, Dz1Error(*func)(void* ptr, Dz1LinkRoadwayGeometry* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1LinkRoadwayGeometryResponse* p, Dz1Error(*func)(void* ptr, Dz1LinkRoadwayGeometry* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1LinkRoadwayGeometryResponse* p, Dz1Error(*func)(void* ptr, Dz1LinkRoadwayGeometry* entry), void* ptr);
	unsigned int (*count)(struct Dz1LinkRoadwayGeometryResponse* p);
} Dz1LinkRoadwayGeometryResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1LinkRoadwayGeometryResponse* Dz1LinkRoadwayGeometryResponse_new(Dz1Error* err);
static __inline__ Dz1LinkRoadwayGeometryResponse* Dz1LinkRoadwayGeometryResponse_gen(Dz1Error* err) { return Dz1LinkRoadwayGeometryResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1LinkRoadwayGeometryResponse* Dz1LinkRoadwayGeometryResponse_clone(Dz1LinkRoadwayGeometryResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LinkRoadwayGeometryResponse_del(Dz1LinkRoadwayGeometryResponse* p);
static __inline__ void Dz1LinkRoadwayGeometryResponse_delAndSetNull(void* ptr)
{
	Dz1LinkRoadwayGeometryResponse** p = (Dz1LinkRoadwayGeometryResponse**)ptr;
	Dz1LinkRoadwayGeometryResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LinkRoadwayGeometryResponse_dump(Dz1LinkRoadwayGeometryResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LinkRoadwayGeometryResponse_fdump(FILE* fp, Dz1LinkRoadwayGeometryResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1LinkRoadwayGeometryResponse_fromASN(Dz1LinkRoadwayGeometryResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1LinkRoadwayGeometryResponse* Dz1LinkRoadwayGeometryResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1LinkRoadwayGeometryResponse_toASN(ASN1List* dst, Dz1LinkRoadwayGeometryResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1LinkRoadwayGeometryResponse_toNewASN(Dz1LinkRoadwayGeometryResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1LinkRoadwayGeometryResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ProbeVehicleDetection_vpbd_VehicleClass
typedef enum Dz1ProbeVehicleDetection_vpbd_VehicleClass
{
	Dz1ProbeVehicleDetection_vpbd_VehicleClass_other_no_additional_information_required = 0,
	Dz1ProbeVehicleDetection_vpbd_VehicleClass_other_additional_information_required = 1,
	Dz1ProbeVehicleDetection_vpbd_VehicleClass_bus_vehicle = 2,
	Dz1ProbeVehicleDetection_vpbd_VehicleClass_taxi_vehicle = 3,
	Dz1ProbeVehicleDetection_vpbd_VehicleClass_passenger_cars = 4,
	Dz1ProbeVehicleDetection_vpbd_VehicleClass_emergency_vehicles = 5,
	Dz1ProbeVehicleDetection_vpbd_VehicleClass_official_vehicle = 6,
	Dz1ProbeVehicleDetection_vpbd_VehicleClass_max
} Dz1ProbeVehicleDetection_vpbd_VehicleClass;

DZ1_CPPLINK str_t Dz1ProbeVehicleDetection_vpbd_VehicleClassStrA(Dz1ProbeVehicleDetection_vpbd_VehicleClass v);
DZ1_CPPLINK Dz1ProbeVehicleDetection_vpbd_VehicleClass Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1ProbeVehicleDetection_vpbd_VehicleClassStrW(Dz1ProbeVehicleDetection_vpbd_VehicleClass v);
DZ1_CPPLINK Dz1ProbeVehicleDetection_vpbd_VehicleClass Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1ProbeVehicleDetection_vpbd_VehicleClassStr Dz1ProbeVehicleDetection_vpbd_VehicleClassStrW
#define Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStr Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStrW
#else // UNICODE
#define Dz1ProbeVehicleDetection_vpbd_VehicleClassStr Dz1ProbeVehicleDetection_vpbd_VehicleClassStrA
#define Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStr Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1ProbeVehicleDetection_vpbd_VehicleClassStr Dz1ProbeVehicleDetection_vpbd_VehicleClassStrA
#define Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStr Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1ProbeVehicleDetection_vpbd_VehicleClass* Dz1ProbeVehicleDetection_vpbd_VehicleClass_new(Dz1ProbeVehicleDetection_vpbd_VehicleClass* src, Dz1Error* err);
static __inline__ Dz1ProbeVehicleDetection_vpbd_VehicleClass* Dz1ProbeVehicleDetection_vpbd_VehicleClass_gen(Dz1Error* err) { Dz1ProbeVehicleDetection_vpbd_VehicleClass v = Dz1ProbeVehicleDetection_vpbd_VehicleClass_max; return Dz1ProbeVehicleDetection_vpbd_VehicleClass_new(&v, err); }
#define Dz1ProbeVehicleDetection_vpbd_VehicleClass_clone             Dz1ProbeVehicleDetection_vpbd_VehicleClass_new
#define Dz1ProbeVehicleDetection_vpbd_VehicleClass_del               Dz1u32_del
#define Dz1ProbeVehicleDetection_vpbd_VehicleClass_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1ProbeVehicleDetection_vpbd_VehicleClass_dump(Dz1ProbeVehicleDetection_vpbd_VehicleClass* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ProbeVehicleDetection_vpbd_VehicleClass_fdump(FILE* fp, Dz1ProbeVehicleDetection_vpbd_VehicleClass* v, int tab);
// Dz1ProbeVehicleDetection_vpbd_VehicleClass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ProbeVehicleDetection
typedef struct Dz1ProbeVehicleDetection
{
	Dz1Asn1UTF8Str* vpbd_VehicleIdNumber;
	Dz1ProbeVehicleDetection_vpbd_VehicleClass  vpbd_VehicleClass;
	Dz1Asn1VisibleStr* vpbd_VehicleTimeInGeneralizedTime;
	Dz1Asn1VisibleStr* vpbd_VehicleTimeOutGeneralizedTime;
	u16_t                                       vpbd_VehicleTravelTimeTime;
	u16_t* vpbd_VehicleAverageSpeedRate;
	Dz1Asn1UTF8Str* vpbd_AviReaderIdNumber;
	s64_t* vpbd_AviReaderLocationLatitude;
	u32_t* vpbd_AviReaderLocationLongitude;
	Dz1Asn1UTF8Str* vpbd_ReferenceLocatorIdNumber;
	s64_t* vpbd_ReferenceLocatorLatitude;
	u32_t* vpbd_ReferenceLocatorLongitude;
} Dz1ProbeVehicleDetection;

DZ1_CPPLINK DZ1_DLLPORT Dz1ProbeVehicleDetection* Dz1ProbeVehicleDetection_new(Dz1Asn1UTF8Str* vpbd_VehicleIdNumber,
	Dz1ProbeVehicleDetection_vpbd_VehicleClass vpbd_VehicleClass,
	Dz1Asn1VisibleStr* vpbd_VehicleTimeInGeneralizedTime,
	Dz1Asn1VisibleStr* vpbd_VehicleTimeOutGeneralizedTime,
	u16_t vpbd_VehicleTravelTimeTime, Dz1Error* err);
static __inline__ Dz1ProbeVehicleDetection* Dz1ProbeVehicleDetection_gen(Dz1Error* err) { return Dz1ProbeVehicleDetection_new(NULL, Dz1ProbeVehicleDetection_vpbd_VehicleClass_max, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1ProbeVehicleDetection* Dz1ProbeVehicleDetection_clone(Dz1ProbeVehicleDetection* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ProbeVehicleDetection_del(Dz1ProbeVehicleDetection* p);
static __inline__ void Dz1ProbeVehicleDetection_delAndSetNull(void* ptr)
{
	Dz1ProbeVehicleDetection** p = (Dz1ProbeVehicleDetection**)ptr;
	Dz1ProbeVehicleDetection_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ProbeVehicleDetection_dump(Dz1ProbeVehicleDetection* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ProbeVehicleDetection_fdump(FILE* fp, Dz1ProbeVehicleDetection* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ProbeVehicleDetection_fromASN(Dz1ProbeVehicleDetection* dst, ProbeVehicleDetection* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ProbeVehicleDetection* Dz1ProbeVehicleDetection_newFromASN(ProbeVehicleDetection* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ProbeVehicleDetection_toASN(ProbeVehicleDetection* dst, Dz1ProbeVehicleDetection* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ProbeVehicleDetection* Dz1ProbeVehicleDetection_toNewASN(Dz1ProbeVehicleDetection* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1ProbeVehicleDetection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ProbeVehicleDetectionRequest
typedef Dz1Asn1UTF8Str Dz1ProbeVehicleDetectionRequest;

#define Dz1ProbeVehicleDetectionRequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1ProbeVehicleDetectionRequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1ProbeVehicleDetectionRequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1ProbeVehicleDetectionRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ProbeVehicleDetectionResponse
typedef struct Dz1ProbeVehicleDetectionResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1ProbeVehicleDetectionResponse* p, Dz1ProbeVehicleDetection* data);
	Dz1ProbeVehicleDetection** (*get_array)(struct Dz1ProbeVehicleDetectionResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1ProbeVehicleDetectionResponse* p, Dz1Error(*func)(void* ptr, Dz1ProbeVehicleDetection* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1ProbeVehicleDetectionResponse* p, Dz1Error(*func)(void* ptr, Dz1ProbeVehicleDetection* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1ProbeVehicleDetectionResponse* p, Dz1Error(*func)(void* ptr, Dz1ProbeVehicleDetection* entry), void* ptr);
	unsigned int (*count)(struct Dz1ProbeVehicleDetectionResponse* p);
} Dz1ProbeVehicleDetectionResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1ProbeVehicleDetectionResponse* Dz1ProbeVehicleDetectionResponse_new(Dz1Error* err);
static __inline__ Dz1ProbeVehicleDetectionResponse* Dz1ProbeVehicleDetectionResponse_gen(Dz1Error* err) { return Dz1ProbeVehicleDetectionResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1ProbeVehicleDetectionResponse* Dz1ProbeVehicleDetectionResponse_clone(Dz1ProbeVehicleDetectionResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ProbeVehicleDetectionResponse_del(Dz1ProbeVehicleDetectionResponse* p);
static __inline__ void Dz1ProbeVehicleDetectionResponse_delAndSetNull(void* ptr)
{
	Dz1ProbeVehicleDetectionResponse** p = (Dz1ProbeVehicleDetectionResponse**)ptr;
	Dz1ProbeVehicleDetectionResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ProbeVehicleDetectionResponse_dump(Dz1ProbeVehicleDetectionResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ProbeVehicleDetectionResponse_fdump(FILE* fp, Dz1ProbeVehicleDetectionResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ProbeVehicleDetectionResponse_fromASN(Dz1ProbeVehicleDetectionResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ProbeVehicleDetectionResponse* Dz1ProbeVehicleDetectionResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ProbeVehicleDetectionResponse_toASN(ASN1List* dst, Dz1ProbeVehicleDetectionResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1ProbeVehicleDetectionResponse_toNewASN(Dz1ProbeVehicleDetectionResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1ProbeVehicleDetectionResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DetectorCollection
typedef struct Dz1DetectorCollection
{
	Dz1Asn1UTF8Str* tfdt_DetectorIdNumber;
	Dz1Asn1VisibleStr* tfdt_DetectorTimeGeneralizedTime;
	u16_t              tfdt_SpeedRate;
	u8_t* tfdt_VolumeRate;
	u8_t               tfdt_OccupancyPercent;
	u32_t* tfdt_VehicleQueueLengthQuantity;
} Dz1DetectorCollection;

DZ1_CPPLINK DZ1_DLLPORT Dz1DetectorCollection* Dz1DetectorCollection_new(Dz1Asn1UTF8Str* tfdt_DetectorIdNumber,
	Dz1Asn1VisibleStr* tfdt_DetectorTimeGeneralizedTime,
	u16_t tfdt_SpeedRate,
	u8_t tfdt_OccupancyPercent, Dz1Error* err);
static __inline__ Dz1DetectorCollection* Dz1DetectorCollection_gen(Dz1Error* err) { return Dz1DetectorCollection_new(NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1DetectorCollection* Dz1DetectorCollection_clone(Dz1DetectorCollection* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1DetectorCollection_del(Dz1DetectorCollection* p);
static __inline__ void Dz1DetectorCollection_delAndSetNull(void* ptr)
{
	Dz1DetectorCollection** p = (Dz1DetectorCollection**)ptr;
	Dz1DetectorCollection_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1DetectorCollection_dump(Dz1DetectorCollection* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1DetectorCollection_fdump(FILE* fp, Dz1DetectorCollection* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1DetectorCollection_fromASN(Dz1DetectorCollection* dst, DetectorCollection* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1DetectorCollection* Dz1DetectorCollection_newFromASN(DetectorCollection* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1DetectorCollection_toASN(DetectorCollection* dst, Dz1DetectorCollection* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT DetectorCollection* Dz1DetectorCollection_toNewASN(Dz1DetectorCollection* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1DetectorCollection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DetectorCollectionRequest
typedef Dz1Asn1UTF8Str Dz1DetectorCollectionRequest;

#define Dz1DetectorCollectionRequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1DetectorCollectionRequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1DetectorCollectionRequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1DetectorCollectionRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DetectorCollectionResponse
typedef struct Dz1DetectorCollectionResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1DetectorCollectionResponse* p, Dz1DetectorCollection* data);
	Dz1DetectorCollection** (*get_array)(struct Dz1DetectorCollectionResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1DetectorCollectionResponse* p, Dz1Error(*func)(void* ptr, Dz1DetectorCollection* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1DetectorCollectionResponse* p, Dz1Error(*func)(void* ptr, Dz1DetectorCollection* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1DetectorCollectionResponse* p, Dz1Error(*func)(void* ptr, Dz1DetectorCollection* entry), void* ptr);
	unsigned int (*count)(struct Dz1DetectorCollectionResponse* p);
} Dz1DetectorCollectionResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1DetectorCollectionResponse* Dz1DetectorCollectionResponse_new(Dz1Error* err);
static __inline__ Dz1DetectorCollectionResponse* Dz1DetectorCollectionResponse_gen(Dz1Error* err) { return Dz1DetectorCollectionResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1DetectorCollectionResponse* Dz1DetectorCollectionResponse_clone(Dz1DetectorCollectionResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1DetectorCollectionResponse_del(Dz1DetectorCollectionResponse* p);
static __inline__ void Dz1DetectorCollectionResponse_delAndSetNull(void* ptr)
{
	Dz1DetectorCollectionResponse** p = (Dz1DetectorCollectionResponse**)ptr;
	Dz1DetectorCollectionResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1DetectorCollectionResponse_dump(Dz1DetectorCollectionResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1DetectorCollectionResponse_fdump(FILE* fp, Dz1DetectorCollectionResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1DetectorCollectionResponse_fromASN(Dz1DetectorCollectionResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1DetectorCollectionResponse* Dz1DetectorCollectionResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1DetectorCollectionResponse_toASN(ASN1List* dst, Dz1DetectorCollectionResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1DetectorCollectionResponse_toNewASN(Dz1DetectorCollectionResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1DetectorCollectionResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ExtentionCommPDU
typedef struct Dz1ExtentionCommPDU
{
	u32_t            index;
	u32_t            aid;
	Dz1TimeVal* deliveryStart;
	Dz1TimeVal* deliveryStop;
	bool_t* signature;
	s64_t* payloadType;
	Dz1Asn1OctetStr* payload;
} Dz1ExtentionCommPDU;

DZ1_CPPLINK DZ1_DLLPORT Dz1ExtentionCommPDU* Dz1ExtentionCommPDU_new(u32_t index,
	u32_t aid,
	Dz1TimeVal* deliveryStart,
	Dz1TimeVal* deliveryStop,
	Dz1Asn1OctetStr* payload, Dz1Error* err);
static __inline__ Dz1ExtentionCommPDU* Dz1ExtentionCommPDU_gen(Dz1Error* err) { return Dz1ExtentionCommPDU_new(0, 0, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1ExtentionCommPDU* Dz1ExtentionCommPDU_clone(Dz1ExtentionCommPDU* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ExtentionCommPDU_del(Dz1ExtentionCommPDU* p);
static __inline__ void Dz1ExtentionCommPDU_delAndSetNull(void* ptr)
{
	Dz1ExtentionCommPDU** p = (Dz1ExtentionCommPDU**)ptr;
	Dz1ExtentionCommPDU_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ExtentionCommPDU_dump(Dz1ExtentionCommPDU* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ExtentionCommPDU_fdump(FILE* fp, Dz1ExtentionCommPDU* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ExtentionCommPDU_fromASN(Dz1ExtentionCommPDU* dst, ExtentionCommPDU* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ExtentionCommPDU* Dz1ExtentionCommPDU_newFromASN(ExtentionCommPDU* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ExtentionCommPDU_toASN(ExtentionCommPDU* dst, Dz1ExtentionCommPDU* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ExtentionCommPDU* Dz1ExtentionCommPDU_toNewASN(Dz1ExtentionCommPDU* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1ExtentionCommPDU
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ExtentionCommPDURequest
typedef Dz1Asn1UTF8Str Dz1ExtentionCommPDURequest;

#define Dz1ExtentionCommPDURequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1ExtentionCommPDURequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1ExtentionCommPDURequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1ExtentionCommPDURequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ExtentionCommPDUResponse
typedef struct Dz1ExtentionCommPDUResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1ExtentionCommPDUResponse* p, Dz1ExtentionCommPDU* data);
	Dz1ExtentionCommPDU** (*get_array)(struct Dz1ExtentionCommPDUResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1ExtentionCommPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1ExtentionCommPDU* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1ExtentionCommPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1ExtentionCommPDU* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1ExtentionCommPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1ExtentionCommPDU* entry), void* ptr);
	unsigned int (*count)(struct Dz1ExtentionCommPDUResponse* p);
} Dz1ExtentionCommPDUResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1ExtentionCommPDUResponse* Dz1ExtentionCommPDUResponse_new(Dz1Error* err);
static __inline__ Dz1ExtentionCommPDUResponse* Dz1ExtentionCommPDUResponse_gen(Dz1Error* err) { return Dz1ExtentionCommPDUResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1ExtentionCommPDUResponse* Dz1ExtentionCommPDUResponse_clone(Dz1ExtentionCommPDUResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ExtentionCommPDUResponse_del(Dz1ExtentionCommPDUResponse* p);
static __inline__ void Dz1ExtentionCommPDUResponse_delAndSetNull(void* ptr)
{
	Dz1ExtentionCommPDUResponse** p = (Dz1ExtentionCommPDUResponse**)ptr;
	Dz1ExtentionCommPDUResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ExtentionCommPDUResponse_dump(Dz1ExtentionCommPDUResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ExtentionCommPDUResponse_fdump(FILE* fp, Dz1ExtentionCommPDUResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ExtentionCommPDUResponse_fromASN(Dz1ExtentionCommPDUResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ExtentionCommPDUResponse* Dz1ExtentionCommPDUResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ExtentionCommPDUResponse_toASN(ASN1List* dst, Dz1ExtentionCommPDUResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1ExtentionCommPDUResponse_toNewASN(Dz1ExtentionCommPDUResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1ExtentionCommPDUResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ItsIso14827TestTimeFormat
typedef enum Dz1ItsIso14827TestTimeFormat
{
	Dz1ItsIso14827TestTimeFormat_full,
	Dz1ItsIso14827TestTimeFormat_hhmmss,
	Dz1ItsIso14827TestTimeFormat_hhmm,
	Dz1ItsIso14827TestTimeFormat_max
} Dz1ItsIso14827TestTimeFormat;

DZ1_CPPLINK str_t Dz1ItsIso14827TestTimeFormatStrA(Dz1ItsIso14827TestTimeFormat v);
DZ1_CPPLINK Dz1ItsIso14827TestTimeFormat Dz1ItsIso14827TestTimeFormatFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1ItsIso14827TestTimeFormatStrW(Dz1ItsIso14827TestTimeFormat v);
DZ1_CPPLINK Dz1ItsIso14827TestTimeFormat Dz1ItsIso14827TestTimeFormatFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1ItsIso14827TestTimeFormatStr Dz1ItsIso14827TestTimeFormatStrW
#define Dz1ItsIso14827TestTimeFormatFromStr Dz1ItsIso14827TestTimeFormatFromStrW
#else // UNICODE
#define Dz1ItsIso14827TestTimeFormatStr Dz1ItsIso14827TestTimeFormatStrA
#define Dz1ItsIso14827TestTimeFormatFromStr Dz1ItsIso14827TestTimeFormatFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1ItsIso14827TestTimeFormatStr Dz1ItsIso14827TestTimeFormatStrA
#define Dz1ItsIso14827TestTimeFormatFromStr Dz1ItsIso14827TestTimeFormatFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1ItsIso14827TestTimeFormat* Dz1ItsIso14827TestTimeFormat_new(Dz1ItsIso14827TestTimeFormat* src, Dz1Error* err);
static __inline__ Dz1ItsIso14827TestTimeFormat* Dz1ItsIso14827TestTimeFormat_gen(Dz1Error* err) { Dz1ItsIso14827TestTimeFormat v = Dz1ItsIso14827TestTimeFormat_max; return Dz1ItsIso14827TestTimeFormat_new(&v, err); }
#define Dz1ItsIso14827TestTimeFormat_clone             Dz1ItsIso14827TestTimeFormat_new
#define Dz1ItsIso14827TestTimeFormat_del               Dz1u32_del
#define Dz1ItsIso14827TestTimeFormat_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1ItsIso14827TestTimeFormat_dump(Dz1ItsIso14827TestTimeFormat* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ItsIso14827TestTimeFormat_fdump(FILE* fp, Dz1ItsIso14827TestTimeFormat* v, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ItsIso14827TestTimeFormat_fromASN(Dz1ItsIso14827TestTimeFormat* dst, ItsIso14827TestTimeFormat* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ItsIso14827TestTimeFormat* Dz1ItsIso14827TestTimeFormat_newFromASN(ItsIso14827TestTimeFormat* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ItsIso14827TestTimeFormat_toASN(ItsIso14827TestTimeFormat* dst, Dz1ItsIso14827TestTimeFormat* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827TestTimeFormat* Dz1ItsIso14827TestTimeFormat_toNewASN(Dz1ItsIso14827TestTimeFormat* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1ItsIso14827TestTimeFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ItsIso14827TestTimeRequest
typedef struct Dz1ItsIso14827TestTimeRequest
{
	Dz1ItsIso14827TestTimeFormat  fmt;
} Dz1ItsIso14827TestTimeRequest;

DZ1_CPPLINK DZ1_DLLPORT Dz1ItsIso14827TestTimeRequest* Dz1ItsIso14827TestTimeRequest_new(Dz1ItsIso14827TestTimeFormat fmt, Dz1Error* err);
static __inline__ Dz1ItsIso14827TestTimeRequest* Dz1ItsIso14827TestTimeRequest_gen(Dz1Error* err) { return Dz1ItsIso14827TestTimeRequest_new(Dz1ItsIso14827TestTimeFormat_max, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1ItsIso14827TestTimeRequest* Dz1ItsIso14827TestTimeRequest_clone(Dz1ItsIso14827TestTimeRequest* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ItsIso14827TestTimeRequest_del(Dz1ItsIso14827TestTimeRequest* p);
static __inline__ void Dz1ItsIso14827TestTimeRequest_delAndSetNull(void* ptr)
{
	Dz1ItsIso14827TestTimeRequest** p = (Dz1ItsIso14827TestTimeRequest**)ptr;
	Dz1ItsIso14827TestTimeRequest_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ItsIso14827TestTimeRequest_dump(Dz1ItsIso14827TestTimeRequest* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ItsIso14827TestTimeRequest_fdump(FILE* fp, Dz1ItsIso14827TestTimeRequest* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ItsIso14827TestTimeRequest_fromASN(Dz1ItsIso14827TestTimeRequest* dst, ItsIso14827TestTimeRequest* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ItsIso14827TestTimeRequest* Dz1ItsIso14827TestTimeRequest_newFromASN(ItsIso14827TestTimeRequest* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ItsIso14827TestTimeRequest_toASN(ItsIso14827TestTimeRequest* dst, Dz1ItsIso14827TestTimeRequest* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827TestTimeRequest* Dz1ItsIso14827TestTimeRequest_toNewASN(Dz1ItsIso14827TestTimeRequest* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1ItsIso14827TestTimeRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ItsIso14827TestTimeResponse
typedef struct Dz1ItsIso14827TestTimeResponse
{
	Dz1Asn1UTF8Str* str;
} Dz1ItsIso14827TestTimeResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1ItsIso14827TestTimeResponse* Dz1ItsIso14827TestTimeResponse_new(Dz1Asn1UTF8Str* str, Dz1Error* err);
static __inline__ Dz1ItsIso14827TestTimeResponse* Dz1ItsIso14827TestTimeResponse_gen(Dz1Error* err) { return Dz1ItsIso14827TestTimeResponse_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1ItsIso14827TestTimeResponse* Dz1ItsIso14827TestTimeResponse_clone(Dz1ItsIso14827TestTimeResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ItsIso14827TestTimeResponse_del(Dz1ItsIso14827TestTimeResponse* p);
static __inline__ void Dz1ItsIso14827TestTimeResponse_delAndSetNull(void* ptr)
{
	Dz1ItsIso14827TestTimeResponse** p = (Dz1ItsIso14827TestTimeResponse**)ptr;
	Dz1ItsIso14827TestTimeResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ItsIso14827TestTimeResponse_dump(Dz1ItsIso14827TestTimeResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ItsIso14827TestTimeResponse_fdump(FILE* fp, Dz1ItsIso14827TestTimeResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ItsIso14827TestTimeResponse_fromASN(Dz1ItsIso14827TestTimeResponse* dst, ItsIso14827TestTimeResponse* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ItsIso14827TestTimeResponse* Dz1ItsIso14827TestTimeResponse_newFromASN(ItsIso14827TestTimeResponse* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ItsIso14827TestTimeResponse_toASN(ItsIso14827TestTimeResponse* dst, Dz1ItsIso14827TestTimeResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ItsIso14827TestTimeResponse* Dz1ItsIso14827TestTimeResponse_toNewASN(Dz1ItsIso14827TestTimeResponse* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1ItsIso14827TestTimeResponse
////////////////////////////////////////////////////////////////////////////////

#endif
