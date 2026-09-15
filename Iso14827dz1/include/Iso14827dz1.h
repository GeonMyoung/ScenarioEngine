#ifndef _DZ1_TDC_ISO14827DZ1_H_
#define _DZ1_TDC_ISO14827DZ1_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827Cost
typedef struct Iso14827Cost
{
	Dz1Asn1OctetStr		*currency;
	s32_t				 factor;
	s32_t				 qty;
} Iso14827Cost;

DZ1_CPPLINK DZ1_DLLPORT Iso14827Cost *Iso14827Cost_new(Dz1Asn1OctetStr *currency, 
													   s32_t factor, 
													   s32_t qty, Dz1Error *err);
static __inline__ Iso14827Cost *Iso14827Cost_gen(Dz1Error *err) { return Iso14827Cost_new(NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827Cost_copy(Iso14827Cost *dst, Iso14827Cost *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827Cost *Iso14827Cost_clone(Iso14827Cost *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Cost_purge(Iso14827Cost *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Cost_del(Iso14827Cost *p);
static __inline__ void Iso14827Cost_delAndSetNull(void *ptr)
{
	Iso14827Cost **p = (Iso14827Cost **)ptr;
	if (p) { Iso14827Cost_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Cost_dump(Iso14827Cost *p, int tab);
// Iso14827Cost
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TimeFracPresent
typedef enum Iso14827TimeFracPresent
{
	Iso14827TimeFracPresent_deci,
	Iso14827TimeFracPresent_centi,
	Iso14827TimeFracPresent_milli,
	Iso14827TimeFracPresent_max
} Iso14827TimeFracPresent;

DZ1_CPPLINK str_t Iso14827TimeFracPresentStrA(Iso14827TimeFracPresent v);
DZ1_CPPLINK Iso14827TimeFracPresent Iso14827TimeFracPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TimeFracPresentStrW(Iso14827TimeFracPresent v);
DZ1_CPPLINK Iso14827TimeFracPresent Iso14827TimeFracPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TimeFracPresentStr Iso14827TimeFracPresentStrW
#define Iso14827TimeFracPresentFromStr Iso14827TimeFracPresentFromStrW
#else // UNICODE
#define Iso14827TimeFracPresentStr Iso14827TimeFracPresentStrA
#define Iso14827TimeFracPresentFromStr Iso14827TimeFracPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TimeFracPresentStr Iso14827TimeFracPresentStrA
#define Iso14827TimeFracPresentFromStr Iso14827TimeFracPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TimeFracPresent *Iso14827TimeFracPresent_new(Iso14827TimeFracPresent *src, Dz1Error *err);
static __inline__ Iso14827TimeFracPresent *Iso14827TimeFracPresent_gen(Dz1Error *err) { Iso14827TimeFracPresent v = Iso14827TimeFracPresent_max; return Iso14827TimeFracPresent_new(&v, err); }
#define Iso14827TimeFracPresent_clone             Iso14827TimeFracPresent_new
static __inline__ void Iso14827TimeFracPresent_del(Iso14827TimeFracPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TimeFracPresent_delAndSetNull(void *ptr)
{
	Iso14827TimeFracPresent **p = (Iso14827TimeFracPresent **)ptr;
	if (p != NULL) { Iso14827TimeFracPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TimeFracPresent_dump(Iso14827TimeFracPresent *v, int tab);
// Iso14827TimeFracPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TimeFrac
typedef struct Iso14827TimeFrac
{
	Iso14827TimeFracPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		s32_t		deci;
		s32_t		centi;
		s32_t		milli;
	} x;
} Iso14827TimeFrac;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TimeFrac *Iso14827TimeFrac_new(Iso14827TimeFracPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827TimeFrac *Iso14827TimeFrac_gen(Dz1Error *err) { return Iso14827TimeFrac_new(Iso14827TimeFracPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827TimeFrac_copy(Iso14827TimeFrac *dst, Iso14827TimeFrac *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TimeFrac *Iso14827TimeFrac_clone(Iso14827TimeFrac *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TimeFrac_purge(Iso14827TimeFrac *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TimeFrac_del(Iso14827TimeFrac *p);
static __inline__ void Iso14827TimeFrac_delAndSetNull(void *ptr)
{
	Iso14827TimeFrac **p = (Iso14827TimeFrac **)ptr;
	if (p != NULL) { Iso14827TimeFrac_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TimeFrac_dump(Iso14827TimeFrac *p, int tab);
// Iso14827TimeFrac
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TimeZone
typedef struct Iso14827TimeZone
{
	s32_t		modH;
	s32_t		modM;
} Iso14827TimeZone;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TimeZone *Iso14827TimeZone_new(s32_t modH, 
															   s32_t modM, Dz1Error *err);
static __inline__ Iso14827TimeZone *Iso14827TimeZone_gen(Dz1Error *err) { return Iso14827TimeZone_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TimeZone_copy(Iso14827TimeZone *dst, Iso14827TimeZone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TimeZone *Iso14827TimeZone_clone(Iso14827TimeZone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TimeZone_purge(Iso14827TimeZone *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TimeZone_del(Iso14827TimeZone *p);
static __inline__ void Iso14827TimeZone_delAndSetNull(void *ptr)
{
	Iso14827TimeZone **p = (Iso14827TimeZone **)ptr;
	if (p) { Iso14827TimeZone_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TimeZone_dump(Iso14827TimeZone *p, int tab);
// Iso14827TimeZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Time
typedef struct Iso14827Time
{
	s32_t				*year;
	s32_t				*month;
	s32_t				*day;
	s32_t				 h;
	s32_t				 m;
	s32_t				 s;
	Iso14827TimeFrac	*frac;
	Iso14827TimeZone	*zone;
} Iso14827Time;

DZ1_CPPLINK DZ1_DLLPORT Iso14827Time *Iso14827Time_new(s32_t *year, 
													   s32_t *month, 
													   s32_t *day, 
													   s32_t h, 
													   s32_t m, 
													   s32_t s, 
													   Iso14827TimeFrac *frac, 
													   Iso14827TimeZone *zone, Dz1Error *err);
static __inline__ Iso14827Time *Iso14827Time_gen(Dz1Error *err) { return Iso14827Time_new(NULL, NULL, NULL, 0, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827Time_copy(Iso14827Time *dst, Iso14827Time *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827Time *Iso14827Time_clone(Iso14827Time *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Time_purge(Iso14827Time *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Time_del(Iso14827Time *p);
static __inline__ void Iso14827Time_delAndSetNull(void *ptr)
{
	Iso14827Time **p = (Iso14827Time **)ptr;
	if (p) { Iso14827Time_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Time_dump(Iso14827Time *p, int tab);
// Iso14827Time
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827HdrOpt
typedef struct Iso14827HdrOpt
{
	Dz1Asn1UTF8Str		*origin;
	Dz1Asn1OctetStr		*originAddr;
	Dz1Asn1UTF8Str		*sender;
	Dz1Asn1OctetStr		*senderAddr;
	Dz1Asn1UTF8Str		*dest;
	Dz1Asn1OctetStr		*destAddr;
	Iso14827Cost		*cost;
	Iso14827Time		*t;
} Iso14827HdrOpt;

DZ1_CPPLINK DZ1_DLLPORT Iso14827HdrOpt *Iso14827HdrOpt_new(Dz1Asn1UTF8Str *origin, 
														   Dz1Asn1OctetStr *originAddr, 
														   Dz1Asn1UTF8Str *sender, 
														   Dz1Asn1OctetStr *senderAddr, 
														   Dz1Asn1UTF8Str *dest, 
														   Dz1Asn1OctetStr *destAddr, 
														   Iso14827Cost *cost, 
														   Iso14827Time *t, Dz1Error *err);
static __inline__ Iso14827HdrOpt *Iso14827HdrOpt_gen(Dz1Error *err) { return Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827HdrOpt_copy(Iso14827HdrOpt *dst, Iso14827HdrOpt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827HdrOpt *Iso14827HdrOpt_clone(Iso14827HdrOpt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827HdrOpt_purge(Iso14827HdrOpt *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827HdrOpt_del(Iso14827HdrOpt *p);
static __inline__ void Iso14827HdrOpt_delAndSetNull(void *ptr)
{
	Iso14827HdrOpt **p = (Iso14827HdrOpt **)ptr;
	if (p) { Iso14827HdrOpt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827HdrOpt_dump(Iso14827HdrOpt *p, int tab);
// Iso14827HdrOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Initiate
typedef struct Iso14827Initiate
{
	Dz1Asn1UTF8Str		*sender;
	Dz1Asn1UTF8Str		*dest;
} Iso14827Initiate;

DZ1_CPPLINK DZ1_DLLPORT Iso14827Initiate *Iso14827Initiate_new(Dz1Asn1UTF8Str *sender, 
															   Dz1Asn1UTF8Str *dest, Dz1Error *err);
static __inline__ Iso14827Initiate *Iso14827Initiate_gen(Dz1Error *err) { return Iso14827Initiate_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827Initiate_copy(Iso14827Initiate *dst, Iso14827Initiate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827Initiate *Iso14827Initiate_clone(Iso14827Initiate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Initiate_purge(Iso14827Initiate *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Initiate_del(Iso14827Initiate *p);
static __inline__ void Iso14827Initiate_delAndSetNull(void *ptr)
{
	Iso14827Initiate **p = (Iso14827Initiate **)ptr;
	if (p) { Iso14827Initiate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Initiate_dump(Iso14827Initiate *p, int tab);
// Iso14827Initiate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1OIDList
typedef struct Dz1OIDList
{
	void *storage;
	unsigned int (*count)(struct Dz1OIDList *p);
	Dz1Error (*travel)(struct Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Asn1OID *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Asn1OID *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Asn1OID *entry), void *ptr);
	Dz1Asn1OID **(*get_array)(struct Dz1OIDList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1OIDList *p, Dz1Asn1OID *data);
	Dz1Asn1OID *(*find)(struct Dz1OIDList *p, Dz1Asn1OID *key);
	int (*cmp)(Dz1Asn1OID *a, Dz1Asn1OID *b);
} Dz1OIDList;

DZ1_CPPLINK DZ1_DLLPORT Dz1OIDList *Dz1OIDList_new(Dz1Error *err);
static __inline__ Dz1OIDList *Dz1OIDList_gen(Dz1Error *err) { return Dz1OIDList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1OIDList *Dz1OIDList_clone(Dz1OIDList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1OIDList_purge(Dz1OIDList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1OIDList_del(Dz1OIDList *p);
static __inline__ void Dz1OIDList_delAndSetNull(void *ptr)
{
	Dz1OIDList **p = (Dz1OIDList **)ptr;
	if (p != NULL) { Dz1OIDList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1OIDListA_dump(Dz1OIDList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1OIDListA_fdump(FILE *fp, Dz1OIDList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1OIDListW_dump(Dz1OIDList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1OIDListW_fdump(FILE *fp, Dz1OIDList *p, int tab);
#ifdef UNICODE
#define Dz1OIDList_dump Dz1OIDListW_dump
#define Dz1OIDList_fdump Dz1OIDListW_fdump
#else //  UNICODE
#define Dz1OIDList_dump Dz1OIDListA_dump
#define Dz1OIDList_fdump Dz1OIDListA_fdump
#endif //  UNICODE
static __inline__ void Dz1OIDListX_dump(Dz1OIDList *p, int tab) { DZ1_DUMP(Dz1OIDList, p, tab); }
static __inline__ void Dz1OIDListX_fdump(FILE *fp, Dz1OIDList *p, int tab) { DZ1_FDUMP(fp, Dz1OIDList, p, tab); }
#else // UNIX_SYSTEM
#define Dz1OIDList_dump Dz1OIDListA_dump
#define Dz1OIDListX_dump Dz1OIDListA_dump
#define Dz1OIDList_fdump Dz1OIDListA_fdump
#define Dz1OIDListX_fdump Dz1OIDListA_fdump
#endif // UNIX_SYSTEM

// Dz1OIDList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827LoginInitiator
typedef enum Iso14827LoginInitiator
{
	Iso14827LoginInitiator_serverInitiated,
	Iso14827LoginInitiator_clientInitiated,
	Iso14827LoginInitiator_max
} Iso14827LoginInitiator;

DZ1_CPPLINK str_t Iso14827LoginInitiatorStrA(Iso14827LoginInitiator v);
DZ1_CPPLINK Iso14827LoginInitiator Iso14827LoginInitiatorFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827LoginInitiatorStrW(Iso14827LoginInitiator v);
DZ1_CPPLINK Iso14827LoginInitiator Iso14827LoginInitiatorFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827LoginInitiatorStr Iso14827LoginInitiatorStrW
#define Iso14827LoginInitiatorFromStr Iso14827LoginInitiatorFromStrW
#else // UNICODE
#define Iso14827LoginInitiatorStr Iso14827LoginInitiatorStrA
#define Iso14827LoginInitiatorFromStr Iso14827LoginInitiatorFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827LoginInitiatorStr Iso14827LoginInitiatorStrA
#define Iso14827LoginInitiatorFromStr Iso14827LoginInitiatorFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827LoginInitiator *Iso14827LoginInitiator_new(Iso14827LoginInitiator *src, Dz1Error *err);
static __inline__ Iso14827LoginInitiator *Iso14827LoginInitiator_gen(Dz1Error *err) { Iso14827LoginInitiator v = Iso14827LoginInitiator_max; return Iso14827LoginInitiator_new(&v, err); }
static __inline__ void Iso14827LoginInitiator_del(Iso14827LoginInitiator *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827LoginInitiator_delAndSetNull(void *ptr)
{
	Iso14827LoginInitiator **p = (Iso14827LoginInitiator **)ptr;
	if (p != NULL) { Iso14827LoginInitiator_del(*p); *p = NULL; }
}
// Iso14827LoginInitiator
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Login
typedef struct Iso14827Login
{
	Dz1Asn1UTF8Str				*sender;
	Dz1Asn1UTF8Str				*dest;
	Dz1Asn1OctetStr				*user;
	Dz1Asn1OctetStr				*pass;
	Dz1OIDList					*encRules;
	s32_t						 hbDur;
	s32_t						 timeout;
	Iso14827LoginInitiator		 initiator;
	u16_t						 datagramSize;
} Iso14827Login;

DZ1_CPPLINK DZ1_DLLPORT Iso14827Login *Iso14827Login_new(Dz1Asn1UTF8Str *sender, 
														 Dz1Asn1UTF8Str *dest, 
														 Dz1Asn1OctetStr *user, 
														 Dz1Asn1OctetStr *pass, 
														 s32_t hbDur, 
														 s32_t timeout, 
														 Iso14827LoginInitiator initiator, 
														 u16_t datagramSize, Dz1Error *err);
static __inline__ Iso14827Login *Iso14827Login_gen(Dz1Error *err) { return Iso14827Login_new(NULL, NULL, NULL, NULL, 0, 0, Iso14827LoginInitiator_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827Login_copy(Iso14827Login *dst, Iso14827Login *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827Login *Iso14827Login_clone(Iso14827Login *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Login_purge(Iso14827Login *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Login_del(Iso14827Login *p);
static __inline__ void Iso14827Login_delAndSetNull(void *ptr)
{
	Iso14827Login **p = (Iso14827Login **)ptr;
	if (p) { Iso14827Login_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Login_dump(Iso14827Login *p, int tab);
// Iso14827Login
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Terminate
typedef enum Iso14827Terminate
{
	Iso14827Terminate_other,
	Iso14827Terminate_serverRequested,
	Iso14827Terminate_clientRequested,
	Iso14827Terminate_serverShutdown,
	Iso14827Terminate_clientShutdown,
	Iso14827Terminate_serverCommProblems,
	Iso14827Terminate_clientCommProblems,
	Iso14827Terminate_max
} Iso14827Terminate;

DZ1_CPPLINK str_t Iso14827TerminateStrA(Iso14827Terminate v);
DZ1_CPPLINK Iso14827Terminate Iso14827TerminateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TerminateStrW(Iso14827Terminate v);
DZ1_CPPLINK Iso14827Terminate Iso14827TerminateFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TerminateStr Iso14827TerminateStrW
#define Iso14827TerminateFromStr Iso14827TerminateFromStrW
#else // UNICODE
#define Iso14827TerminateStr Iso14827TerminateStrA
#define Iso14827TerminateFromStr Iso14827TerminateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TerminateStr Iso14827TerminateStrA
#define Iso14827TerminateFromStr Iso14827TerminateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827Terminate *Iso14827Terminate_new(Iso14827Terminate *src, Dz1Error *err);
static __inline__ Iso14827Terminate *Iso14827Terminate_gen(Dz1Error *err) { Iso14827Terminate v = Iso14827Terminate_max; return Iso14827Terminate_new(&v, err); }
static __inline__ void Iso14827Terminate_del(Iso14827Terminate *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827Terminate_delAndSetNull(void *ptr)
{
	Iso14827Terminate **p = (Iso14827Terminate **)ptr;
	if (p != NULL) { Iso14827Terminate_del(*p); *p = NULL; }
}
// Iso14827Terminate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Logout
typedef enum Iso14827Logout
{
	Iso14827Logout_other,
	Iso14827Logout_serverRequested,
	Iso14827Logout_clientRequested,
	Iso14827Logout_serverShutdown,
	Iso14827Logout_clientShutdown,
	Iso14827Logout_serverCommProblems,
	Iso14827Logout_clientCommProblems,
	Iso14827Logout_max
} Iso14827Logout;

DZ1_CPPLINK str_t Iso14827LogoutStrA(Iso14827Logout v);
DZ1_CPPLINK Iso14827Logout Iso14827LogoutFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827LogoutStrW(Iso14827Logout v);
DZ1_CPPLINK Iso14827Logout Iso14827LogoutFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827LogoutStr Iso14827LogoutStrW
#define Iso14827LogoutFromStr Iso14827LogoutFromStrW
#else // UNICODE
#define Iso14827LogoutStr Iso14827LogoutStrA
#define Iso14827LogoutFromStr Iso14827LogoutFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827LogoutStr Iso14827LogoutStrA
#define Iso14827LogoutFromStr Iso14827LogoutFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827Logout *Iso14827Logout_new(Iso14827Logout *src, Dz1Error *err);
static __inline__ Iso14827Logout *Iso14827Logout_gen(Dz1Error *err) { Iso14827Logout v = Iso14827Logout_max; return Iso14827Logout_new(&v, err); }
static __inline__ void Iso14827Logout_del(Iso14827Logout *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827Logout_delAndSetNull(void *ptr)
{
	Iso14827Logout **p = (Iso14827Logout **)ptr;
	if (p != NULL) { Iso14827Logout_del(*p); *p = NULL; }
}
// Iso14827Logout
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionDataStatus
typedef enum Iso14827SubscriptionDataStatus
{
	Iso14827SubscriptionDataStatus_NEW,
	Iso14827SubscriptionDataStatus_UPDATED,
	Iso14827SubscriptionDataStatus_max
} Iso14827SubscriptionDataStatus;

DZ1_CPPLINK str_t Iso14827SubscriptionDataStatusStrA(Iso14827SubscriptionDataStatus v);
DZ1_CPPLINK Iso14827SubscriptionDataStatus Iso14827SubscriptionDataStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827SubscriptionDataStatusStrW(Iso14827SubscriptionDataStatus v);
DZ1_CPPLINK Iso14827SubscriptionDataStatus Iso14827SubscriptionDataStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827SubscriptionDataStatusStr Iso14827SubscriptionDataStatusStrW
#define Iso14827SubscriptionDataStatusFromStr Iso14827SubscriptionDataStatusFromStrW
#else // UNICODE
#define Iso14827SubscriptionDataStatusStr Iso14827SubscriptionDataStatusStrA
#define Iso14827SubscriptionDataStatusFromStr Iso14827SubscriptionDataStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827SubscriptionDataStatusStr Iso14827SubscriptionDataStatusStrA
#define Iso14827SubscriptionDataStatusFromStr Iso14827SubscriptionDataStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionDataStatus *Iso14827SubscriptionDataStatus_new(Iso14827SubscriptionDataStatus *src, Dz1Error *err);
static __inline__ Iso14827SubscriptionDataStatus *Iso14827SubscriptionDataStatus_gen(Dz1Error *err) { Iso14827SubscriptionDataStatus v = Iso14827SubscriptionDataStatus_max; return Iso14827SubscriptionDataStatus_new(&v, err); }
static __inline__ void Iso14827SubscriptionDataStatus_del(Iso14827SubscriptionDataStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827SubscriptionDataStatus_delAndSetNull(void *ptr)
{
	Iso14827SubscriptionDataStatus **p = (Iso14827SubscriptionDataStatus **)ptr;
	if (p != NULL) { Iso14827SubscriptionDataStatus_del(*p); *p = NULL; }
}
// Iso14827SubscriptionDataStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RegisteredContinuous
typedef struct Iso14827RegisteredContinuous
{
	u32_t			 updateDelay;
	Iso14827Time	*start;
	Iso14827Time	*end;
} Iso14827RegisteredContinuous;

DZ1_CPPLINK DZ1_DLLPORT Iso14827RegisteredContinuous *Iso14827RegisteredContinuous_new(u32_t updateDelay, 
																					   Iso14827Time *start, 
																					   Iso14827Time *end, Dz1Error *err);
static __inline__ Iso14827RegisteredContinuous *Iso14827RegisteredContinuous_gen(Dz1Error *err) { return Iso14827RegisteredContinuous_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827RegisteredContinuous_copy(Iso14827RegisteredContinuous *dst, Iso14827RegisteredContinuous *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827RegisteredContinuous *Iso14827RegisteredContinuous_clone(Iso14827RegisteredContinuous *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RegisteredContinuous_purge(Iso14827RegisteredContinuous *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RegisteredContinuous_del(Iso14827RegisteredContinuous *p);
static __inline__ void Iso14827RegisteredContinuous_delAndSetNull(void *ptr)
{
	Iso14827RegisteredContinuous **p = (Iso14827RegisteredContinuous **)ptr;
	if (p) { Iso14827RegisteredContinuous_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RegisteredContinuous_dump(Iso14827RegisteredContinuous *p, int tab);
// Iso14827RegisteredContinuous
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RegisteredDaily
typedef struct Iso14827RegisteredDaily
{
	u32_t			 updateDelay;
	u8_t			 daysOfWeek;
	Iso14827Time	*startDate;
	Iso14827Time	*endDate;
	Iso14827Time	*startTime;
	u16_t			*duration;
} Iso14827RegisteredDaily;

DZ1_CPPLINK DZ1_DLLPORT Iso14827RegisteredDaily *Iso14827RegisteredDaily_new(u32_t updateDelay, 
																			 u8_t daysOfWeek, 
																			 Iso14827Time *startDate, 
																			 Iso14827Time *endDate, 
																			 Iso14827Time *startTime, 
																			 u16_t *duration, Dz1Error *err);
static __inline__ Iso14827RegisteredDaily *Iso14827RegisteredDaily_gen(Dz1Error *err) { return Iso14827RegisteredDaily_new(0, 0, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827RegisteredDaily_copy(Iso14827RegisteredDaily *dst, Iso14827RegisteredDaily *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827RegisteredDaily *Iso14827RegisteredDaily_clone(Iso14827RegisteredDaily *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RegisteredDaily_purge(Iso14827RegisteredDaily *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RegisteredDaily_del(Iso14827RegisteredDaily *p);
static __inline__ void Iso14827RegisteredDaily_delAndSetNull(void *ptr)
{
	Iso14827RegisteredDaily **p = (Iso14827RegisteredDaily **)ptr;
	if (p) { Iso14827RegisteredDaily_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RegisteredDaily_dump(Iso14827RegisteredDaily *p, int tab);
// Iso14827RegisteredDaily
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RegisteredPresent
typedef enum Iso14827RegisteredPresent
{
	Iso14827RegisteredPresent_continuous,
	Iso14827RegisteredPresent_daily,
	Iso14827RegisteredPresent_max
} Iso14827RegisteredPresent;

DZ1_CPPLINK str_t Iso14827RegisteredPresentStrA(Iso14827RegisteredPresent v);
DZ1_CPPLINK Iso14827RegisteredPresent Iso14827RegisteredPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827RegisteredPresentStrW(Iso14827RegisteredPresent v);
DZ1_CPPLINK Iso14827RegisteredPresent Iso14827RegisteredPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827RegisteredPresentStr Iso14827RegisteredPresentStrW
#define Iso14827RegisteredPresentFromStr Iso14827RegisteredPresentFromStrW
#else // UNICODE
#define Iso14827RegisteredPresentStr Iso14827RegisteredPresentStrA
#define Iso14827RegisteredPresentFromStr Iso14827RegisteredPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827RegisteredPresentStr Iso14827RegisteredPresentStrA
#define Iso14827RegisteredPresentFromStr Iso14827RegisteredPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827RegisteredPresent *Iso14827RegisteredPresent_new(Iso14827RegisteredPresent *src, Dz1Error *err);
static __inline__ Iso14827RegisteredPresent *Iso14827RegisteredPresent_gen(Dz1Error *err) { Iso14827RegisteredPresent v = Iso14827RegisteredPresent_max; return Iso14827RegisteredPresent_new(&v, err); }
#define Iso14827RegisteredPresent_clone             Iso14827RegisteredPresent_new
static __inline__ void Iso14827RegisteredPresent_del(Iso14827RegisteredPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827RegisteredPresent_delAndSetNull(void *ptr)
{
	Iso14827RegisteredPresent **p = (Iso14827RegisteredPresent **)ptr;
	if (p != NULL) { Iso14827RegisteredPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RegisteredPresent_dump(Iso14827RegisteredPresent *v, int tab);
// Iso14827RegisteredPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Registered
typedef struct Iso14827Registered
{
	Iso14827RegisteredPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827RegisteredContinuous	*continuous;
		Iso14827RegisteredDaily			*daily;
	} x;
} Iso14827Registered;

DZ1_CPPLINK DZ1_DLLPORT Iso14827Registered *Iso14827Registered_new(Iso14827RegisteredPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827Registered *Iso14827Registered_gen(Dz1Error *err) { return Iso14827Registered_new(Iso14827RegisteredPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827Registered_copy(Iso14827Registered *dst, Iso14827Registered *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827Registered *Iso14827Registered_clone(Iso14827Registered *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Registered_purge(Iso14827Registered *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Registered_del(Iso14827Registered *p);
static __inline__ void Iso14827Registered_delAndSetNull(void *ptr)
{
	Iso14827Registered **p = (Iso14827Registered **)ptr;
	if (p != NULL) { Iso14827Registered_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Registered_dump(Iso14827Registered *p, int tab);
// Iso14827Registered
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionDataModePresent
typedef enum Iso14827SubscriptionDataModePresent
{
	Iso14827SubscriptionDataModePresent_single,
	Iso14827SubscriptionDataModePresent_eventDriven,
	Iso14827SubscriptionDataModePresent_periodic,
	Iso14827SubscriptionDataModePresent_max
} Iso14827SubscriptionDataModePresent;

DZ1_CPPLINK str_t Iso14827SubscriptionDataModePresentStrA(Iso14827SubscriptionDataModePresent v);
DZ1_CPPLINK Iso14827SubscriptionDataModePresent Iso14827SubscriptionDataModePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827SubscriptionDataModePresentStrW(Iso14827SubscriptionDataModePresent v);
DZ1_CPPLINK Iso14827SubscriptionDataModePresent Iso14827SubscriptionDataModePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827SubscriptionDataModePresentStr Iso14827SubscriptionDataModePresentStrW
#define Iso14827SubscriptionDataModePresentFromStr Iso14827SubscriptionDataModePresentFromStrW
#else // UNICODE
#define Iso14827SubscriptionDataModePresentStr Iso14827SubscriptionDataModePresentStrA
#define Iso14827SubscriptionDataModePresentFromStr Iso14827SubscriptionDataModePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827SubscriptionDataModePresentStr Iso14827SubscriptionDataModePresentStrA
#define Iso14827SubscriptionDataModePresentFromStr Iso14827SubscriptionDataModePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionDataModePresent *Iso14827SubscriptionDataModePresent_new(Iso14827SubscriptionDataModePresent *src, Dz1Error *err);
static __inline__ Iso14827SubscriptionDataModePresent *Iso14827SubscriptionDataModePresent_gen(Dz1Error *err) { Iso14827SubscriptionDataModePresent v = Iso14827SubscriptionDataModePresent_max; return Iso14827SubscriptionDataModePresent_new(&v, err); }
#define Iso14827SubscriptionDataModePresent_clone             Iso14827SubscriptionDataModePresent_new
static __inline__ void Iso14827SubscriptionDataModePresent_del(Iso14827SubscriptionDataModePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827SubscriptionDataModePresent_delAndSetNull(void *ptr)
{
	Iso14827SubscriptionDataModePresent **p = (Iso14827SubscriptionDataModePresent **)ptr;
	if (p != NULL) { Iso14827SubscriptionDataModePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionDataModePresent_dump(Iso14827SubscriptionDataModePresent *v, int tab);
// Iso14827SubscriptionDataModePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionDataMode
typedef struct Iso14827SubscriptionDataMode
{
	Iso14827SubscriptionDataModePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		s32_t					*single;
		Iso14827Registered		*eventDriven;
		Iso14827Registered		*periodic;
	} x;
} Iso14827SubscriptionDataMode;

DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionDataMode *Iso14827SubscriptionDataMode_new(Iso14827SubscriptionDataModePresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827SubscriptionDataMode *Iso14827SubscriptionDataMode_gen(Dz1Error *err) { return Iso14827SubscriptionDataMode_new(Iso14827SubscriptionDataModePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827SubscriptionDataMode_copy(Iso14827SubscriptionDataMode *dst, Iso14827SubscriptionDataMode *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionDataMode *Iso14827SubscriptionDataMode_clone(Iso14827SubscriptionDataMode *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionDataMode_purge(Iso14827SubscriptionDataMode *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionDataMode_del(Iso14827SubscriptionDataMode *p);
static __inline__ void Iso14827SubscriptionDataMode_delAndSetNull(void *ptr)
{
	Iso14827SubscriptionDataMode **p = (Iso14827SubscriptionDataMode **)ptr;
	if (p != NULL) { Iso14827SubscriptionDataMode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionDataMode_dump(Iso14827SubscriptionDataMode *p, int tab);
// Iso14827SubscriptionDataMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionDataFormat
typedef enum Iso14827SubscriptionDataFormat
{
	Iso14827SubscriptionDataFormat_other,
	Iso14827SubscriptionDataFormat_ftp,
	Iso14827SubscriptionDataFormat_tftp,
	Iso14827SubscriptionDataFormat_dataPacket,
	Iso14827SubscriptionDataFormat_max
} Iso14827SubscriptionDataFormat;

DZ1_CPPLINK str_t Iso14827SubscriptionDataFormatStrA(Iso14827SubscriptionDataFormat v);
DZ1_CPPLINK Iso14827SubscriptionDataFormat Iso14827SubscriptionDataFormatFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827SubscriptionDataFormatStrW(Iso14827SubscriptionDataFormat v);
DZ1_CPPLINK Iso14827SubscriptionDataFormat Iso14827SubscriptionDataFormatFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827SubscriptionDataFormatStr Iso14827SubscriptionDataFormatStrW
#define Iso14827SubscriptionDataFormatFromStr Iso14827SubscriptionDataFormatFromStrW
#else // UNICODE
#define Iso14827SubscriptionDataFormatStr Iso14827SubscriptionDataFormatStrA
#define Iso14827SubscriptionDataFormatFromStr Iso14827SubscriptionDataFormatFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827SubscriptionDataFormatStr Iso14827SubscriptionDataFormatStrA
#define Iso14827SubscriptionDataFormatFromStr Iso14827SubscriptionDataFormatFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionDataFormat *Iso14827SubscriptionDataFormat_new(Iso14827SubscriptionDataFormat *src, Dz1Error *err);
static __inline__ Iso14827SubscriptionDataFormat *Iso14827SubscriptionDataFormat_gen(Dz1Error *err) { Iso14827SubscriptionDataFormat v = Iso14827SubscriptionDataFormat_max; return Iso14827SubscriptionDataFormat_new(&v, err); }
static __inline__ void Iso14827SubscriptionDataFormat_del(Iso14827SubscriptionDataFormat *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827SubscriptionDataFormat_delAndSetNull(void *ptr)
{
	Iso14827SubscriptionDataFormat **p = (Iso14827SubscriptionDataFormat **)ptr;
	if (p != NULL) { Iso14827SubscriptionDataFormat_del(*p); *p = NULL; }
}
// Iso14827SubscriptionDataFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827EndAppMsg
typedef struct Iso14827EndAppMsg
{
	Dz1Asn1OID		*oid;
	Dz1Asn1Any		*data;
} Iso14827EndAppMsg;

DZ1_CPPLINK DZ1_DLLPORT Iso14827EndAppMsg *Iso14827EndAppMsg_new(Dz1Asn1OID *oid, 
																 Dz1Asn1Any *data, Dz1Error *err);
static __inline__ Iso14827EndAppMsg *Iso14827EndAppMsg_gen(Dz1Error *err) { return Iso14827EndAppMsg_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827EndAppMsg_copy(Iso14827EndAppMsg *dst, Iso14827EndAppMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827EndAppMsg *Iso14827EndAppMsg_clone(Iso14827EndAppMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827EndAppMsg_purge(Iso14827EndAppMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827EndAppMsg_del(Iso14827EndAppMsg *p);
static __inline__ void Iso14827EndAppMsg_delAndSetNull(void *ptr)
{
	Iso14827EndAppMsg **p = (Iso14827EndAppMsg **)ptr;
	if (p) { Iso14827EndAppMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827EndAppMsg_dump(Iso14827EndAppMsg *p, int tab);
// Iso14827EndAppMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionData
typedef struct Iso14827SubscriptionData
{
	bool_t								 persistent;
	Iso14827SubscriptionDataStatus		 status;
	Iso14827SubscriptionDataMode		*mode;
	Iso14827SubscriptionDataFormat		 fmt;
	s32_t								 priority;
	bool_t								 guarantee;
	Iso14827EndAppMsg					*msg;
} Iso14827SubscriptionData;

DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionData *Iso14827SubscriptionData_new(bool_t persistent, 
																			   Iso14827SubscriptionDataStatus status, 
																			   Iso14827SubscriptionDataMode *mode, 
																			   Iso14827SubscriptionDataFormat fmt, 
																			   s32_t priority, 
																			   bool_t guarantee, 
																			   Iso14827EndAppMsg *msg, Dz1Error *err);
static __inline__ Iso14827SubscriptionData *Iso14827SubscriptionData_gen(Dz1Error *err) { return Iso14827SubscriptionData_new(0, Iso14827SubscriptionDataStatus_max, NULL, Iso14827SubscriptionDataFormat_max, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827SubscriptionData_copy(Iso14827SubscriptionData *dst, Iso14827SubscriptionData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionData *Iso14827SubscriptionData_clone(Iso14827SubscriptionData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionData_purge(Iso14827SubscriptionData *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionData_del(Iso14827SubscriptionData *p);
static __inline__ void Iso14827SubscriptionData_delAndSetNull(void *ptr)
{
	Iso14827SubscriptionData **p = (Iso14827SubscriptionData **)ptr;
	if (p) { Iso14827SubscriptionData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionData_dump(Iso14827SubscriptionData *p, int tab);
// Iso14827SubscriptionData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionCancel
typedef enum Iso14827SubscriptionCancel
{
	Iso14827SubscriptionCancel_other,
	Iso14827SubscriptionCancel_dataNotNeeded,
	Iso14827SubscriptionCancel_errorsInPublication,
	Iso14827SubscriptionCancel_pendingLogout,
	Iso14827SubscriptionCancel_processingMgmt,
	Iso14827SubscriptionCancel_bandwidthMgmt,
	Iso14827SubscriptionCancel_max
} Iso14827SubscriptionCancel;

DZ1_CPPLINK str_t Iso14827SubscriptionCancelStrA(Iso14827SubscriptionCancel v);
DZ1_CPPLINK Iso14827SubscriptionCancel Iso14827SubscriptionCancelFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827SubscriptionCancelStrW(Iso14827SubscriptionCancel v);
DZ1_CPPLINK Iso14827SubscriptionCancel Iso14827SubscriptionCancelFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827SubscriptionCancelStr Iso14827SubscriptionCancelStrW
#define Iso14827SubscriptionCancelFromStr Iso14827SubscriptionCancelFromStrW
#else // UNICODE
#define Iso14827SubscriptionCancelStr Iso14827SubscriptionCancelStrA
#define Iso14827SubscriptionCancelFromStr Iso14827SubscriptionCancelFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827SubscriptionCancelStr Iso14827SubscriptionCancelStrA
#define Iso14827SubscriptionCancelFromStr Iso14827SubscriptionCancelFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionCancel *Iso14827SubscriptionCancel_new(Iso14827SubscriptionCancel *src, Dz1Error *err);
static __inline__ Iso14827SubscriptionCancel *Iso14827SubscriptionCancel_gen(Dz1Error *err) { Iso14827SubscriptionCancel v = Iso14827SubscriptionCancel_max; return Iso14827SubscriptionCancel_new(&v, err); }
static __inline__ void Iso14827SubscriptionCancel_del(Iso14827SubscriptionCancel *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827SubscriptionCancel_delAndSetNull(void *ptr)
{
	Iso14827SubscriptionCancel **p = (Iso14827SubscriptionCancel **)ptr;
	if (p != NULL) { Iso14827SubscriptionCancel_del(*p); *p = NULL; }
}
// Iso14827SubscriptionCancel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionTypePresent
typedef enum Iso14827SubscriptionTypePresent
{
	Iso14827SubscriptionTypePresent_data,
	Iso14827SubscriptionTypePresent_reason,
	Iso14827SubscriptionTypePresent_max
} Iso14827SubscriptionTypePresent;

DZ1_CPPLINK str_t Iso14827SubscriptionTypePresentStrA(Iso14827SubscriptionTypePresent v);
DZ1_CPPLINK Iso14827SubscriptionTypePresent Iso14827SubscriptionTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827SubscriptionTypePresentStrW(Iso14827SubscriptionTypePresent v);
DZ1_CPPLINK Iso14827SubscriptionTypePresent Iso14827SubscriptionTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827SubscriptionTypePresentStr Iso14827SubscriptionTypePresentStrW
#define Iso14827SubscriptionTypePresentFromStr Iso14827SubscriptionTypePresentFromStrW
#else // UNICODE
#define Iso14827SubscriptionTypePresentStr Iso14827SubscriptionTypePresentStrA
#define Iso14827SubscriptionTypePresentFromStr Iso14827SubscriptionTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827SubscriptionTypePresentStr Iso14827SubscriptionTypePresentStrA
#define Iso14827SubscriptionTypePresentFromStr Iso14827SubscriptionTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionTypePresent *Iso14827SubscriptionTypePresent_new(Iso14827SubscriptionTypePresent *src, Dz1Error *err);
static __inline__ Iso14827SubscriptionTypePresent *Iso14827SubscriptionTypePresent_gen(Dz1Error *err) { Iso14827SubscriptionTypePresent v = Iso14827SubscriptionTypePresent_max; return Iso14827SubscriptionTypePresent_new(&v, err); }
#define Iso14827SubscriptionTypePresent_clone             Iso14827SubscriptionTypePresent_new
static __inline__ void Iso14827SubscriptionTypePresent_del(Iso14827SubscriptionTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827SubscriptionTypePresent_delAndSetNull(void *ptr)
{
	Iso14827SubscriptionTypePresent **p = (Iso14827SubscriptionTypePresent **)ptr;
	if (p != NULL) { Iso14827SubscriptionTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionTypePresent_dump(Iso14827SubscriptionTypePresent *v, int tab);
// Iso14827SubscriptionTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionType
typedef struct Iso14827SubscriptionType
{
	Iso14827SubscriptionTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827SubscriptionData		*data;
		Iso14827SubscriptionCancel		 reason;
	} x;
} Iso14827SubscriptionType;

DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionType *Iso14827SubscriptionType_new(Iso14827SubscriptionTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827SubscriptionType *Iso14827SubscriptionType_gen(Dz1Error *err) { return Iso14827SubscriptionType_new(Iso14827SubscriptionTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827SubscriptionType_copy(Iso14827SubscriptionType *dst, Iso14827SubscriptionType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827SubscriptionType *Iso14827SubscriptionType_clone(Iso14827SubscriptionType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionType_purge(Iso14827SubscriptionType *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionType_del(Iso14827SubscriptionType *p);
static __inline__ void Iso14827SubscriptionType_delAndSetNull(void *ptr)
{
	Iso14827SubscriptionType **p = (Iso14827SubscriptionType **)ptr;
	if (p != NULL) { Iso14827SubscriptionType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827SubscriptionType_dump(Iso14827SubscriptionType *p, int tab);
// Iso14827SubscriptionType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Subscription
typedef struct Iso14827Subscription
{
	u32_t						 serial;
	Iso14827SubscriptionType	*type;
} Iso14827Subscription;

DZ1_CPPLINK DZ1_DLLPORT Iso14827Subscription *Iso14827Subscription_new(u32_t serial, 
																	   Iso14827SubscriptionType *type, Dz1Error *err);
static __inline__ Iso14827Subscription *Iso14827Subscription_gen(Dz1Error *err) { return Iso14827Subscription_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827Subscription_copy(Iso14827Subscription *dst, Iso14827Subscription *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827Subscription *Iso14827Subscription_clone(Iso14827Subscription *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Subscription_purge(Iso14827Subscription *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Subscription_del(Iso14827Subscription *p);
static __inline__ void Iso14827Subscription_delAndSetNull(void *ptr)
{
	Iso14827Subscription **p = (Iso14827Subscription **)ptr;
	if (p) { Iso14827Subscription_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Subscription_dump(Iso14827Subscription *p, int tab);
// Iso14827Subscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationMgmt
typedef enum Iso14827PublicationMgmt
{
	Iso14827PublicationMgmt_temporarilySuspended,
	Iso14827PublicationMgmt_resume,
	Iso14827PublicationMgmt_terminateOther,
	Iso14827PublicationMgmt_terminateDataNoLongerAvailable,
	Iso14827PublicationMgmt_terminatePublicationsBeingRejected,
	Iso14827PublicationMgmt_terminatePendingShutdown,
	Iso14827PublicationMgmt_terminateProcessingMgmt,
	Iso14827PublicationMgmt_terminateBandwidthMgmt,
	Iso14827PublicationMgmt_terminateAccessDenied,
	Iso14827PublicationMgmt_unknownRequest,
	Iso14827PublicationMgmt_max
} Iso14827PublicationMgmt;

DZ1_CPPLINK str_t Iso14827PublicationMgmtStrA(Iso14827PublicationMgmt v);
DZ1_CPPLINK Iso14827PublicationMgmt Iso14827PublicationMgmtFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827PublicationMgmtStrW(Iso14827PublicationMgmt v);
DZ1_CPPLINK Iso14827PublicationMgmt Iso14827PublicationMgmtFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827PublicationMgmtStr Iso14827PublicationMgmtStrW
#define Iso14827PublicationMgmtFromStr Iso14827PublicationMgmtFromStrW
#else // UNICODE
#define Iso14827PublicationMgmtStr Iso14827PublicationMgmtStrA
#define Iso14827PublicationMgmtFromStr Iso14827PublicationMgmtFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827PublicationMgmtStr Iso14827PublicationMgmtStrA
#define Iso14827PublicationMgmtFromStr Iso14827PublicationMgmtFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827PublicationMgmt *Iso14827PublicationMgmt_new(Iso14827PublicationMgmt *src, Dz1Error *err);
static __inline__ Iso14827PublicationMgmt *Iso14827PublicationMgmt_gen(Dz1Error *err) { Iso14827PublicationMgmt v = Iso14827PublicationMgmt_max; return Iso14827PublicationMgmt_new(&v, err); }
static __inline__ void Iso14827PublicationMgmt_del(Iso14827PublicationMgmt *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827PublicationMgmt_delAndSetNull(void *ptr)
{
	Iso14827PublicationMgmt **p = (Iso14827PublicationMgmt **)ptr;
	if (p != NULL) { Iso14827PublicationMgmt_del(*p); *p = NULL; }
}
// Iso14827PublicationMgmt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationTypePresent
typedef enum Iso14827PublicationTypePresent
{
	Iso14827PublicationTypePresent_mgmt,
	Iso14827PublicationTypePresent_msg,
	Iso14827PublicationTypePresent_max
} Iso14827PublicationTypePresent;

DZ1_CPPLINK str_t Iso14827PublicationTypePresentStrA(Iso14827PublicationTypePresent v);
DZ1_CPPLINK Iso14827PublicationTypePresent Iso14827PublicationTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827PublicationTypePresentStrW(Iso14827PublicationTypePresent v);
DZ1_CPPLINK Iso14827PublicationTypePresent Iso14827PublicationTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827PublicationTypePresentStr Iso14827PublicationTypePresentStrW
#define Iso14827PublicationTypePresentFromStr Iso14827PublicationTypePresentFromStrW
#else // UNICODE
#define Iso14827PublicationTypePresentStr Iso14827PublicationTypePresentStrA
#define Iso14827PublicationTypePresentFromStr Iso14827PublicationTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827PublicationTypePresentStr Iso14827PublicationTypePresentStrA
#define Iso14827PublicationTypePresentFromStr Iso14827PublicationTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827PublicationTypePresent *Iso14827PublicationTypePresent_new(Iso14827PublicationTypePresent *src, Dz1Error *err);
static __inline__ Iso14827PublicationTypePresent *Iso14827PublicationTypePresent_gen(Dz1Error *err) { Iso14827PublicationTypePresent v = Iso14827PublicationTypePresent_max; return Iso14827PublicationTypePresent_new(&v, err); }
#define Iso14827PublicationTypePresent_clone             Iso14827PublicationTypePresent_new
static __inline__ void Iso14827PublicationTypePresent_del(Iso14827PublicationTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827PublicationTypePresent_delAndSetNull(void *ptr)
{
	Iso14827PublicationTypePresent **p = (Iso14827PublicationTypePresent **)ptr;
	if (p != NULL) { Iso14827PublicationTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationTypePresent_dump(Iso14827PublicationTypePresent *v, int tab);
// Iso14827PublicationTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationType
typedef struct Iso14827PublicationType
{
	Iso14827PublicationTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827PublicationMgmt		 mgmt;
		Iso14827EndAppMsg			*msg;
	} x;
} Iso14827PublicationType;

DZ1_CPPLINK DZ1_DLLPORT Iso14827PublicationType *Iso14827PublicationType_new(Iso14827PublicationTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827PublicationType *Iso14827PublicationType_gen(Dz1Error *err) { return Iso14827PublicationType_new(Iso14827PublicationTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827PublicationType_copy(Iso14827PublicationType *dst, Iso14827PublicationType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827PublicationType *Iso14827PublicationType_clone(Iso14827PublicationType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationType_purge(Iso14827PublicationType *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationType_del(Iso14827PublicationType *p);
static __inline__ void Iso14827PublicationType_delAndSetNull(void *ptr)
{
	Iso14827PublicationType **p = (Iso14827PublicationType **)ptr;
	if (p != NULL) { Iso14827PublicationType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationType_dump(Iso14827PublicationType *p, int tab);
// Iso14827PublicationType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationData
typedef struct Iso14827PublicationData
{
	u32_t						 subscriptionSerial;
	u32_t						 serial;
	bool_t						 isLated;
	Iso14827PublicationType		*type;
} Iso14827PublicationData;

DZ1_CPPLINK DZ1_DLLPORT Iso14827PublicationData *Iso14827PublicationData_new(u32_t subscriptionSerial, 
																			 u32_t serial, 
																			 bool_t isLated, 
																			 Iso14827PublicationType *type, Dz1Error *err);
static __inline__ Iso14827PublicationData *Iso14827PublicationData_gen(Dz1Error *err) { return Iso14827PublicationData_new(0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827PublicationData_copy(Iso14827PublicationData *dst, Iso14827PublicationData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827PublicationData *Iso14827PublicationData_clone(Iso14827PublicationData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationData_purge(Iso14827PublicationData *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationData_del(Iso14827PublicationData *p);
static __inline__ void Iso14827PublicationData_delAndSetNull(void *ptr)
{
	Iso14827PublicationData **p = (Iso14827PublicationData **)ptr;
	if (p) { Iso14827PublicationData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationData_dump(Iso14827PublicationData *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Iso14827PublicationData_cmp(Iso14827PublicationData *a, Iso14827PublicationData *b); 
// Iso14827PublicationData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationDataList
typedef struct Iso14827PublicationDataList
{
	void *storage;
	unsigned int (*count)(struct Iso14827PublicationDataList *p);
	Dz1Error (*travel)(struct Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Iso14827PublicationData *entry), void *ptr);
	Dz1Error (*travelForward)(struct Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Iso14827PublicationData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Iso14827PublicationData *entry), void *ptr);
	Iso14827PublicationData **(*get_array)(struct Iso14827PublicationDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Iso14827PublicationDataList *p, Iso14827PublicationData *data);
	bool_t (*remove)(struct Iso14827PublicationDataList *p, Iso14827PublicationData *key);
	Iso14827PublicationData *(*extract)(struct Iso14827PublicationDataList *p, Iso14827PublicationData *key);
	Iso14827PublicationData *(*find)(struct Iso14827PublicationDataList *p, Iso14827PublicationData *key);
	Iso14827PublicationData *(*getHead)(struct Iso14827PublicationDataList *p);
	int (*cmp)(Iso14827PublicationData *a, Iso14827PublicationData *b);
} Iso14827PublicationDataList;

DZ1_CPPLINK DZ1_DLLPORT Iso14827PublicationDataList *Iso14827PublicationDataList_new(Dz1Error *err);
static __inline__ Iso14827PublicationDataList *Iso14827PublicationDataList_gen(Dz1Error *err) { return Iso14827PublicationDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Iso14827PublicationDataList *Iso14827PublicationDataList_clone(Iso14827PublicationDataList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationDataList_purge(Iso14827PublicationDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationDataList_del(Iso14827PublicationDataList *p);
static __inline__ void Iso14827PublicationDataList_delAndSetNull(void *ptr)
{
	Iso14827PublicationDataList **p = (Iso14827PublicationDataList **)ptr;
	if (p != NULL) { Iso14827PublicationDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublicationDataList_dump(Iso14827PublicationDataList *p, int tab);

// Iso14827PublicationDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublishFormatPresent
typedef enum Iso14827PublishFormatPresent
{
	Iso14827PublishFormatPresent_dataList,
	Iso14827PublishFormatPresent_filename,
	Iso14827PublishFormatPresent_max
} Iso14827PublishFormatPresent;

DZ1_CPPLINK str_t Iso14827PublishFormatPresentStrA(Iso14827PublishFormatPresent v);
DZ1_CPPLINK Iso14827PublishFormatPresent Iso14827PublishFormatPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827PublishFormatPresentStrW(Iso14827PublishFormatPresent v);
DZ1_CPPLINK Iso14827PublishFormatPresent Iso14827PublishFormatPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827PublishFormatPresentStr Iso14827PublishFormatPresentStrW
#define Iso14827PublishFormatPresentFromStr Iso14827PublishFormatPresentFromStrW
#else // UNICODE
#define Iso14827PublishFormatPresentStr Iso14827PublishFormatPresentStrA
#define Iso14827PublishFormatPresentFromStr Iso14827PublishFormatPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827PublishFormatPresentStr Iso14827PublishFormatPresentStrA
#define Iso14827PublishFormatPresentFromStr Iso14827PublishFormatPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827PublishFormatPresent *Iso14827PublishFormatPresent_new(Iso14827PublishFormatPresent *src, Dz1Error *err);
static __inline__ Iso14827PublishFormatPresent *Iso14827PublishFormatPresent_gen(Dz1Error *err) { Iso14827PublishFormatPresent v = Iso14827PublishFormatPresent_max; return Iso14827PublishFormatPresent_new(&v, err); }
#define Iso14827PublishFormatPresent_clone             Iso14827PublishFormatPresent_new
static __inline__ void Iso14827PublishFormatPresent_del(Iso14827PublishFormatPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827PublishFormatPresent_delAndSetNull(void *ptr)
{
	Iso14827PublishFormatPresent **p = (Iso14827PublishFormatPresent **)ptr;
	if (p != NULL) { Iso14827PublishFormatPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublishFormatPresent_dump(Iso14827PublishFormatPresent *v, int tab);
// Iso14827PublishFormatPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublishFormat
typedef struct Iso14827PublishFormat
{
	Iso14827PublishFormatPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827PublicationDataList		*dataList;
		Dz1Asn1UTF8Str					*filename;
	} x;
} Iso14827PublishFormat;

DZ1_CPPLINK DZ1_DLLPORT Iso14827PublishFormat *Iso14827PublishFormat_new(Iso14827PublishFormatPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827PublishFormat *Iso14827PublishFormat_gen(Dz1Error *err) { return Iso14827PublishFormat_new(Iso14827PublishFormatPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827PublishFormat_copy(Iso14827PublishFormat *dst, Iso14827PublishFormat *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827PublishFormat *Iso14827PublishFormat_clone(Iso14827PublishFormat *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublishFormat_purge(Iso14827PublishFormat *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublishFormat_del(Iso14827PublishFormat *p);
static __inline__ void Iso14827PublishFormat_delAndSetNull(void *ptr)
{
	Iso14827PublishFormat **p = (Iso14827PublishFormat **)ptr;
	if (p != NULL) { Iso14827PublishFormat_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PublishFormat_dump(Iso14827PublishFormat *p, int tab);
// Iso14827PublishFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Publication
typedef struct Iso14827Publication
{
	bool_t						 guaranteed;
	Iso14827PublishFormat		*fmt;
} Iso14827Publication;

DZ1_CPPLINK DZ1_DLLPORT Iso14827Publication *Iso14827Publication_new(bool_t guaranteed, 
																	 Iso14827PublishFormat *fmt, Dz1Error *err);
static __inline__ Iso14827Publication *Iso14827Publication_gen(Dz1Error *err) { return Iso14827Publication_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827Publication_copy(Iso14827Publication *dst, Iso14827Publication *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827Publication *Iso14827Publication_clone(Iso14827Publication *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Publication_purge(Iso14827Publication *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Publication_del(Iso14827Publication *p);
static __inline__ void Iso14827Publication_delAndSetNull(void *ptr)
{
	Iso14827Publication **p = (Iso14827Publication **)ptr;
	if (p) { Iso14827Publication_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Publication_dump(Iso14827Publication *p, int tab);
// Iso14827Publication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TransferDone
typedef struct Iso14827TransferDone
{
	Dz1Asn1UTF8Str		*filename;
	bool_t				 isSuccess;
} Iso14827TransferDone;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TransferDone *Iso14827TransferDone_new(Dz1Asn1UTF8Str *filename, 
																	   bool_t isSuccess, Dz1Error *err);
static __inline__ Iso14827TransferDone *Iso14827TransferDone_gen(Dz1Error *err) { return Iso14827TransferDone_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TransferDone_copy(Iso14827TransferDone *dst, Iso14827TransferDone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TransferDone *Iso14827TransferDone_clone(Iso14827TransferDone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TransferDone_purge(Iso14827TransferDone *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TransferDone_del(Iso14827TransferDone *p);
static __inline__ void Iso14827TransferDone_delAndSetNull(void *ptr)
{
	Iso14827TransferDone **p = (Iso14827TransferDone **)ptr;
	if (p) { Iso14827TransferDone_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TransferDone_dump(Iso14827TransferDone *p, int tab);
// Iso14827TransferDone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827AcceptTypePresent
typedef enum Iso14827AcceptTypePresent
{
	Iso14827AcceptTypePresent_login,
	Iso14827AcceptTypePresent_singleSubscription,
	Iso14827AcceptTypePresent_registeredSubscription,
	Iso14827AcceptTypePresent_publication,
	Iso14827AcceptTypePresent_max
} Iso14827AcceptTypePresent;

DZ1_CPPLINK str_t Iso14827AcceptTypePresentStrA(Iso14827AcceptTypePresent v);
DZ1_CPPLINK Iso14827AcceptTypePresent Iso14827AcceptTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827AcceptTypePresentStrW(Iso14827AcceptTypePresent v);
DZ1_CPPLINK Iso14827AcceptTypePresent Iso14827AcceptTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827AcceptTypePresentStr Iso14827AcceptTypePresentStrW
#define Iso14827AcceptTypePresentFromStr Iso14827AcceptTypePresentFromStrW
#else // UNICODE
#define Iso14827AcceptTypePresentStr Iso14827AcceptTypePresentStrA
#define Iso14827AcceptTypePresentFromStr Iso14827AcceptTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827AcceptTypePresentStr Iso14827AcceptTypePresentStrA
#define Iso14827AcceptTypePresentFromStr Iso14827AcceptTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827AcceptTypePresent *Iso14827AcceptTypePresent_new(Iso14827AcceptTypePresent *src, Dz1Error *err);
static __inline__ Iso14827AcceptTypePresent *Iso14827AcceptTypePresent_gen(Dz1Error *err) { Iso14827AcceptTypePresent v = Iso14827AcceptTypePresent_max; return Iso14827AcceptTypePresent_new(&v, err); }
#define Iso14827AcceptTypePresent_clone             Iso14827AcceptTypePresent_new
static __inline__ void Iso14827AcceptTypePresent_del(Iso14827AcceptTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827AcceptTypePresent_delAndSetNull(void *ptr)
{
	Iso14827AcceptTypePresent **p = (Iso14827AcceptTypePresent **)ptr;
	if (p != NULL) { Iso14827AcceptTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827AcceptTypePresent_dump(Iso14827AcceptTypePresent *v, int tab);
// Iso14827AcceptTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827AcceptType
typedef struct Iso14827AcceptType
{
	Iso14827AcceptTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1OID		*login;
		s32_t			*singleSubscription;
		u32_t			 registeredSubscription;
		s32_t			*publication;
	} x;
} Iso14827AcceptType;

DZ1_CPPLINK DZ1_DLLPORT Iso14827AcceptType *Iso14827AcceptType_new(Iso14827AcceptTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827AcceptType *Iso14827AcceptType_gen(Dz1Error *err) { return Iso14827AcceptType_new(Iso14827AcceptTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827AcceptType_copy(Iso14827AcceptType *dst, Iso14827AcceptType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827AcceptType *Iso14827AcceptType_clone(Iso14827AcceptType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827AcceptType_purge(Iso14827AcceptType *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827AcceptType_del(Iso14827AcceptType *p);
static __inline__ void Iso14827AcceptType_delAndSetNull(void *ptr)
{
	Iso14827AcceptType **p = (Iso14827AcceptType **)ptr;
	if (p != NULL) { Iso14827AcceptType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827AcceptType_dump(Iso14827AcceptType *p, int tab);
// Iso14827AcceptType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Accept
typedef struct Iso14827Accept
{
	u32_t					 pktNbr;
	Iso14827AcceptType		*acceptType;
} Iso14827Accept;

DZ1_CPPLINK DZ1_DLLPORT Iso14827Accept *Iso14827Accept_new(u32_t pktNbr, 
														   Iso14827AcceptType *acceptType, Dz1Error *err);
static __inline__ Iso14827Accept *Iso14827Accept_gen(Dz1Error *err) { return Iso14827Accept_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827Accept_copy(Iso14827Accept *dst, Iso14827Accept *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827Accept *Iso14827Accept_clone(Iso14827Accept *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Accept_purge(Iso14827Accept *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Accept_del(Iso14827Accept *p);
static __inline__ void Iso14827Accept_delAndSetNull(void *ptr)
{
	Iso14827Accept **p = (Iso14827Accept **)ptr;
	if (p) { Iso14827Accept_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Accept_dump(Iso14827Accept *p, int tab);
// Iso14827Accept
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectLogin
typedef enum Iso14827RejectLogin
{
	Iso14827RejectLogin_other,
	Iso14827RejectLogin_unknownDomainName,
	Iso14827RejectLogin_accessDenied,
	Iso14827RejectLogin_invalidPassword,
	Iso14827RejectLogin_timeoutTooSmall,
	Iso14827RejectLogin_timeoutTooLarge,
	Iso14827RejectLogin_heartbeatTooSmall,
	Iso14827RejectLogin_heartbeatTooLarge,
	Iso14827RejectLogin_sessionExist,
	Iso14827RejectLogin_maxSessionReached,
	Iso14827RejectLogin_max
} Iso14827RejectLogin;

DZ1_CPPLINK str_t Iso14827RejectLoginStrA(Iso14827RejectLogin v);
DZ1_CPPLINK Iso14827RejectLogin Iso14827RejectLoginFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827RejectLoginStrW(Iso14827RejectLogin v);
DZ1_CPPLINK Iso14827RejectLogin Iso14827RejectLoginFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827RejectLoginStr Iso14827RejectLoginStrW
#define Iso14827RejectLoginFromStr Iso14827RejectLoginFromStrW
#else // UNICODE
#define Iso14827RejectLoginStr Iso14827RejectLoginStrA
#define Iso14827RejectLoginFromStr Iso14827RejectLoginFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827RejectLoginStr Iso14827RejectLoginStrA
#define Iso14827RejectLoginFromStr Iso14827RejectLoginFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827RejectLogin *Iso14827RejectLogin_new(Iso14827RejectLogin *src, Dz1Error *err);
static __inline__ Iso14827RejectLogin *Iso14827RejectLogin_gen(Dz1Error *err) { Iso14827RejectLogin v = Iso14827RejectLogin_max; return Iso14827RejectLogin_new(&v, err); }
static __inline__ void Iso14827RejectLogin_del(Iso14827RejectLogin *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827RejectLogin_delAndSetNull(void *ptr)
{
	Iso14827RejectLogin **p = (Iso14827RejectLogin **)ptr;
	if (p != NULL) { Iso14827RejectLogin_del(*p); *p = NULL; }
}
// Iso14827RejectLogin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectSubscription
typedef enum Iso14827RejectSubscription
{
	Iso14827RejectSubscription_other,
	Iso14827RejectSubscription_unknownSubscriptionNbr,
	Iso14827RejectSubscription_invalidTimes,
	Iso14827RejectSubscription_frequencyTooSmall,
	Iso14827RejectSubscription_frequencyTooLarge,
	Iso14827RejectSubscription_invalidMode,
	Iso14827RejectSubscription_publishFormatNotSupported,
	Iso14827RejectSubscription_unknownSubscriptionMsgId,
	Iso14827RejectSubscription_invalidSubscriptionMsgId,
	Iso14827RejectSubscription_invalidSubscriptionContent,
	Iso14827RejectSubscription_max
} Iso14827RejectSubscription;

DZ1_CPPLINK str_t Iso14827RejectSubscriptionStrA(Iso14827RejectSubscription v);
DZ1_CPPLINK Iso14827RejectSubscription Iso14827RejectSubscriptionFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827RejectSubscriptionStrW(Iso14827RejectSubscription v);
DZ1_CPPLINK Iso14827RejectSubscription Iso14827RejectSubscriptionFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827RejectSubscriptionStr Iso14827RejectSubscriptionStrW
#define Iso14827RejectSubscriptionFromStr Iso14827RejectSubscriptionFromStrW
#else // UNICODE
#define Iso14827RejectSubscriptionStr Iso14827RejectSubscriptionStrA
#define Iso14827RejectSubscriptionFromStr Iso14827RejectSubscriptionFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827RejectSubscriptionStr Iso14827RejectSubscriptionStrA
#define Iso14827RejectSubscriptionFromStr Iso14827RejectSubscriptionFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827RejectSubscription *Iso14827RejectSubscription_new(Iso14827RejectSubscription *src, Dz1Error *err);
static __inline__ Iso14827RejectSubscription *Iso14827RejectSubscription_gen(Dz1Error *err) { Iso14827RejectSubscription v = Iso14827RejectSubscription_max; return Iso14827RejectSubscription_new(&v, err); }
static __inline__ void Iso14827RejectSubscription_del(Iso14827RejectSubscription *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827RejectSubscription_delAndSetNull(void *ptr)
{
	Iso14827RejectSubscription **p = (Iso14827RejectSubscription **)ptr;
	if (p != NULL) { Iso14827RejectSubscription_del(*p); *p = NULL; }
}
// Iso14827RejectSubscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectPublication
typedef enum Iso14827RejectPublication
{
	Iso14827RejectPublication_other,
	Iso14827RejectPublication_invalidPublishFormat,
	Iso14827RejectPublication_max
} Iso14827RejectPublication;

DZ1_CPPLINK str_t Iso14827RejectPublicationStrA(Iso14827RejectPublication v);
DZ1_CPPLINK Iso14827RejectPublication Iso14827RejectPublicationFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827RejectPublicationStrW(Iso14827RejectPublication v);
DZ1_CPPLINK Iso14827RejectPublication Iso14827RejectPublicationFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827RejectPublicationStr Iso14827RejectPublicationStrW
#define Iso14827RejectPublicationFromStr Iso14827RejectPublicationFromStrW
#else // UNICODE
#define Iso14827RejectPublicationStr Iso14827RejectPublicationStrA
#define Iso14827RejectPublicationFromStr Iso14827RejectPublicationFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827RejectPublicationStr Iso14827RejectPublicationStrA
#define Iso14827RejectPublicationFromStr Iso14827RejectPublicationFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827RejectPublication *Iso14827RejectPublication_new(Iso14827RejectPublication *src, Dz1Error *err);
static __inline__ Iso14827RejectPublication *Iso14827RejectPublication_gen(Dz1Error *err) { Iso14827RejectPublication v = Iso14827RejectPublication_max; return Iso14827RejectPublication_new(&v, err); }
static __inline__ void Iso14827RejectPublication_del(Iso14827RejectPublication *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827RejectPublication_delAndSetNull(void *ptr)
{
	Iso14827RejectPublication **p = (Iso14827RejectPublication **)ptr;
	if (p != NULL) { Iso14827RejectPublication_del(*p); *p = NULL; }
}
// Iso14827RejectPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectPubDataReason
typedef enum Iso14827RejectPubDataReason
{
	Iso14827RejectPubDataReason_other,
	Iso14827RejectPubDataReason_unknownSubscription,
	Iso14827RejectPubDataReason_unknownPublicationNbr,
	Iso14827RejectPubDataReason_unknownPublicationMsgId,
	Iso14827RejectPubDataReason_invalidPublicationMsgId,
	Iso14827RejectPubDataReason_invalidPublicationMsgContent,
	Iso14827RejectPubDataReason_repeatedPublicationNbr,
	Iso14827RejectPubDataReason_max
} Iso14827RejectPubDataReason;

DZ1_CPPLINK str_t Iso14827RejectPubDataReasonStrA(Iso14827RejectPubDataReason v);
DZ1_CPPLINK Iso14827RejectPubDataReason Iso14827RejectPubDataReasonFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827RejectPubDataReasonStrW(Iso14827RejectPubDataReason v);
DZ1_CPPLINK Iso14827RejectPubDataReason Iso14827RejectPubDataReasonFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827RejectPubDataReasonStr Iso14827RejectPubDataReasonStrW
#define Iso14827RejectPubDataReasonFromStr Iso14827RejectPubDataReasonFromStrW
#else // UNICODE
#define Iso14827RejectPubDataReasonStr Iso14827RejectPubDataReasonStrA
#define Iso14827RejectPubDataReasonFromStr Iso14827RejectPubDataReasonFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827RejectPubDataReasonStr Iso14827RejectPubDataReasonStrA
#define Iso14827RejectPubDataReasonFromStr Iso14827RejectPubDataReasonFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827RejectPubDataReason *Iso14827RejectPubDataReason_new(Iso14827RejectPubDataReason *src, Dz1Error *err);
static __inline__ Iso14827RejectPubDataReason *Iso14827RejectPubDataReason_gen(Dz1Error *err) { Iso14827RejectPubDataReason v = Iso14827RejectPubDataReason_max; return Iso14827RejectPubDataReason_new(&v, err); }
static __inline__ void Iso14827RejectPubDataReason_del(Iso14827RejectPubDataReason *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827RejectPubDataReason_delAndSetNull(void *ptr)
{
	Iso14827RejectPubDataReason **p = (Iso14827RejectPubDataReason **)ptr;
	if (p != NULL) { Iso14827RejectPubDataReason_del(*p); *p = NULL; }
}
// Iso14827RejectPubDataReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectPubData
typedef struct Iso14827RejectPubData
{
	u32_t							subSerial;
	u32_t							pubSerial;
	Iso14827RejectPubDataReason		reason;
} Iso14827RejectPubData;

DZ1_CPPLINK DZ1_DLLPORT Iso14827RejectPubData *Iso14827RejectPubData_new(u32_t subSerial, 
																		 u32_t pubSerial, 
																		 Iso14827RejectPubDataReason reason, Dz1Error *err);
static __inline__ Iso14827RejectPubData *Iso14827RejectPubData_gen(Dz1Error *err) { return Iso14827RejectPubData_new(0, 0, Iso14827RejectPubDataReason_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827RejectPubData_copy(Iso14827RejectPubData *dst, Iso14827RejectPubData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827RejectPubData *Iso14827RejectPubData_clone(Iso14827RejectPubData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RejectPubData_purge(Iso14827RejectPubData *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RejectPubData_del(Iso14827RejectPubData *p);
static __inline__ void Iso14827RejectPubData_delAndSetNull(void *ptr)
{
	Iso14827RejectPubData **p = (Iso14827RejectPubData **)ptr;
	if (p) { Iso14827RejectPubData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RejectPubData_dump(Iso14827RejectPubData *p, int tab);
// Iso14827RejectPubData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectTypePresent
typedef enum Iso14827RejectTypePresent
{
	Iso14827RejectTypePresent_login,
	Iso14827RejectTypePresent_subscription,
	Iso14827RejectTypePresent_publication,
	Iso14827RejectTypePresent_pubData,
	Iso14827RejectTypePresent_max
} Iso14827RejectTypePresent;

DZ1_CPPLINK str_t Iso14827RejectTypePresentStrA(Iso14827RejectTypePresent v);
DZ1_CPPLINK Iso14827RejectTypePresent Iso14827RejectTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827RejectTypePresentStrW(Iso14827RejectTypePresent v);
DZ1_CPPLINK Iso14827RejectTypePresent Iso14827RejectTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827RejectTypePresentStr Iso14827RejectTypePresentStrW
#define Iso14827RejectTypePresentFromStr Iso14827RejectTypePresentFromStrW
#else // UNICODE
#define Iso14827RejectTypePresentStr Iso14827RejectTypePresentStrA
#define Iso14827RejectTypePresentFromStr Iso14827RejectTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827RejectTypePresentStr Iso14827RejectTypePresentStrA
#define Iso14827RejectTypePresentFromStr Iso14827RejectTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827RejectTypePresent *Iso14827RejectTypePresent_new(Iso14827RejectTypePresent *src, Dz1Error *err);
static __inline__ Iso14827RejectTypePresent *Iso14827RejectTypePresent_gen(Dz1Error *err) { Iso14827RejectTypePresent v = Iso14827RejectTypePresent_max; return Iso14827RejectTypePresent_new(&v, err); }
#define Iso14827RejectTypePresent_clone             Iso14827RejectTypePresent_new
static __inline__ void Iso14827RejectTypePresent_del(Iso14827RejectTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827RejectTypePresent_delAndSetNull(void *ptr)
{
	Iso14827RejectTypePresent **p = (Iso14827RejectTypePresent **)ptr;
	if (p != NULL) { Iso14827RejectTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RejectTypePresent_dump(Iso14827RejectTypePresent *v, int tab);
// Iso14827RejectTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectType
typedef struct Iso14827RejectType
{
	Iso14827RejectTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827RejectLogin				 login;
		Iso14827RejectSubscription		 subscription;
		Iso14827RejectPublication		 publication;
		Iso14827RejectPubData			*pubData;
	} x;
} Iso14827RejectType;

DZ1_CPPLINK DZ1_DLLPORT Iso14827RejectType *Iso14827RejectType_new(Iso14827RejectTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827RejectType *Iso14827RejectType_gen(Dz1Error *err) { return Iso14827RejectType_new(Iso14827RejectTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827RejectType_copy(Iso14827RejectType *dst, Iso14827RejectType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827RejectType *Iso14827RejectType_clone(Iso14827RejectType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RejectType_purge(Iso14827RejectType *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RejectType_del(Iso14827RejectType *p);
static __inline__ void Iso14827RejectType_delAndSetNull(void *ptr)
{
	Iso14827RejectType **p = (Iso14827RejectType **)ptr;
	if (p != NULL) { Iso14827RejectType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827RejectType_dump(Iso14827RejectType *p, int tab);
// Iso14827RejectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Reject
typedef struct Iso14827Reject
{
	u32_t						 pktNbr;
	Iso14827RejectType			*type;
	Iso14827SubscriptionType	*altReq;
} Iso14827Reject;

DZ1_CPPLINK DZ1_DLLPORT Iso14827Reject *Iso14827Reject_new(u32_t pktNbr, 
														   Iso14827RejectType *type, 
														   Iso14827SubscriptionType *altReq, Dz1Error *err);
static __inline__ Iso14827Reject *Iso14827Reject_gen(Dz1Error *err) { return Iso14827Reject_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827Reject_copy(Iso14827Reject *dst, Iso14827Reject *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827Reject *Iso14827Reject_clone(Iso14827Reject *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Reject_purge(Iso14827Reject *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Reject_del(Iso14827Reject *p);
static __inline__ void Iso14827Reject_delAndSetNull(void *ptr)
{
	Iso14827Reject **p = (Iso14827Reject **)ptr;
	if (p) { Iso14827Reject_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827Reject_dump(Iso14827Reject *p, int tab);
// Iso14827Reject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PDUsPresent
typedef enum Iso14827PDUsPresent
{
	Iso14827PDUsPresent_initiate,
	Iso14827PDUsPresent_login,
	Iso14827PDUsPresent_fred,
	Iso14827PDUsPresent_term,
	Iso14827PDUsPresent_logout,
	Iso14827PDUsPresent_subscription,
	Iso14827PDUsPresent_publication,
	Iso14827PDUsPresent_transferDone,
	Iso14827PDUsPresent_ack,
	Iso14827PDUsPresent_nak,
	Iso14827PDUsPresent_max
} Iso14827PDUsPresent;

DZ1_CPPLINK str_t Iso14827PDUsPresentStrA(Iso14827PDUsPresent v);
DZ1_CPPLINK Iso14827PDUsPresent Iso14827PDUsPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827PDUsPresentStrW(Iso14827PDUsPresent v);
DZ1_CPPLINK Iso14827PDUsPresent Iso14827PDUsPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827PDUsPresentStr Iso14827PDUsPresentStrW
#define Iso14827PDUsPresentFromStr Iso14827PDUsPresentFromStrW
#else // UNICODE
#define Iso14827PDUsPresentStr Iso14827PDUsPresentStrA
#define Iso14827PDUsPresentFromStr Iso14827PDUsPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827PDUsPresentStr Iso14827PDUsPresentStrA
#define Iso14827PDUsPresentFromStr Iso14827PDUsPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827PDUsPresent *Iso14827PDUsPresent_new(Iso14827PDUsPresent *src, Dz1Error *err);
static __inline__ Iso14827PDUsPresent *Iso14827PDUsPresent_gen(Dz1Error *err) { Iso14827PDUsPresent v = Iso14827PDUsPresent_max; return Iso14827PDUsPresent_new(&v, err); }
#define Iso14827PDUsPresent_clone             Iso14827PDUsPresent_new
static __inline__ void Iso14827PDUsPresent_del(Iso14827PDUsPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827PDUsPresent_delAndSetNull(void *ptr)
{
	Iso14827PDUsPresent **p = (Iso14827PDUsPresent **)ptr;
	if (p != NULL) { Iso14827PDUsPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PDUsPresent_dump(Iso14827PDUsPresent *v, int tab);
// Iso14827PDUsPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PDUs
typedef struct Iso14827PDUs
{
	Iso14827PDUsPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827Initiate		*initiate;
		Iso14827Login			*login;
		u32_t					 fred;
		Iso14827Terminate		 term;
		Iso14827Logout			 logout;
		Iso14827Subscription	*subscription;
		Iso14827Publication		*publication;
		Iso14827TransferDone	*transferDone;
		Iso14827Accept			*ack;
		Iso14827Reject			*nak;
	} x;
} Iso14827PDUs;

DZ1_CPPLINK DZ1_DLLPORT Iso14827PDUs *Iso14827PDUs_new(Iso14827PDUsPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827PDUs *Iso14827PDUs_gen(Dz1Error *err) { return Iso14827PDUs_new(Iso14827PDUsPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827PDUs_copy(Iso14827PDUs *dst, Iso14827PDUs *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827PDUs *Iso14827PDUs_clone(Iso14827PDUs *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PDUs_purge(Iso14827PDUs *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PDUs_del(Iso14827PDUs *p);
static __inline__ void Iso14827PDUs_delAndSetNull(void *ptr)
{
	Iso14827PDUs **p = (Iso14827PDUs **)ptr;
	if (p != NULL) { Iso14827PDUs_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827PDUs_dump(Iso14827PDUs *p, int tab);
// Iso14827PDUs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg
typedef struct Iso14827C2CAuthMsg
{
	Dz1Asn1OctetStr		*authInfo;
	u32_t				 pktNbr;
	s32_t				 priority;
	Iso14827HdrOpt		*hdrOpt;
	Iso14827PDUs		*pdu;
} Iso14827C2CAuthMsg;

DZ1_CPPLINK DZ1_DLLPORT Iso14827C2CAuthMsg *Iso14827C2CAuthMsg_new(Dz1Asn1OctetStr *authInfo, 
																   u32_t pktNbr, 
																   s32_t priority, 
																   Iso14827HdrOpt *hdrOpt, 
																   Iso14827PDUs *pdu, Dz1Error *err);
static __inline__ Iso14827C2CAuthMsg *Iso14827C2CAuthMsg_gen(Dz1Error *err) { return Iso14827C2CAuthMsg_new(NULL, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827C2CAuthMsg_copy(Iso14827C2CAuthMsg *dst, Iso14827C2CAuthMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827C2CAuthMsg *Iso14827C2CAuthMsg_clone(Iso14827C2CAuthMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827C2CAuthMsg_purge(Iso14827C2CAuthMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827C2CAuthMsg_del(Iso14827C2CAuthMsg *p);
static __inline__ void Iso14827C2CAuthMsg_delAndSetNull(void *ptr)
{
	Iso14827C2CAuthMsg **p = (Iso14827C2CAuthMsg **)ptr;
	if (p) { Iso14827C2CAuthMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827C2CAuthMsg_dump(Iso14827C2CAuthMsg *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Iso14827C2CAuthMsg_cmp(Iso14827C2CAuthMsg *a, Iso14827C2CAuthMsg *b); 
// Iso14827C2CAuthMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827DatexVersionNumber
typedef enum Iso14827DatexVersionNumber
{
	Iso14827DatexVersionNumber_experimental = 0,
	Iso14827DatexVersionNumber_version1 = 1,
	Iso14827DatexVersionNumber_version2 = 2,
	Iso14827DatexVersionNumber_max
} Iso14827DatexVersionNumber;

DZ1_CPPLINK str_t Iso14827DatexVersionNumberStrA(Iso14827DatexVersionNumber v);
DZ1_CPPLINK Iso14827DatexVersionNumber Iso14827DatexVersionNumberFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827DatexVersionNumberStrW(Iso14827DatexVersionNumber v);
DZ1_CPPLINK Iso14827DatexVersionNumber Iso14827DatexVersionNumberFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827DatexVersionNumberStr Iso14827DatexVersionNumberStrW
#define Iso14827DatexVersionNumberFromStr Iso14827DatexVersionNumberFromStrW
#else // UNICODE
#define Iso14827DatexVersionNumberStr Iso14827DatexVersionNumberStrA
#define Iso14827DatexVersionNumberFromStr Iso14827DatexVersionNumberFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827DatexVersionNumberStr Iso14827DatexVersionNumberStrA
#define Iso14827DatexVersionNumberFromStr Iso14827DatexVersionNumberFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827DatexVersionNumber *Iso14827DatexVersionNumber_new(Iso14827DatexVersionNumber *src, Dz1Error *err);
static __inline__ Iso14827DatexVersionNumber *Iso14827DatexVersionNumber_gen(Dz1Error *err) { Iso14827DatexVersionNumber v = Iso14827DatexVersionNumber_max; return Iso14827DatexVersionNumber_new(&v, err); }
static __inline__ void Iso14827DatexVersionNumber_del(Iso14827DatexVersionNumber *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827DatexVersionNumber_delAndSetNull(void *ptr)
{
	Iso14827DatexVersionNumber **p = (Iso14827DatexVersionNumber **)ptr;
	if (p != NULL) { Iso14827DatexVersionNumber_del(*p); *p = NULL; }
}
// Iso14827DatexVersionNumber
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827DatexDataPacket
typedef struct Iso14827DatexDataPacket
{
	Iso14827DatexVersionNumber		 version;
	Dz1Asn1OctetStr					*data;
	u16_t							 crc16;
} Iso14827DatexDataPacket;

DZ1_CPPLINK DZ1_DLLPORT Iso14827DatexDataPacket *Iso14827DatexDataPacket_new(Iso14827DatexVersionNumber version, 
																			 Dz1Asn1OctetStr *data, 
																			 u16_t crc16, Dz1Error *err);
static __inline__ Iso14827DatexDataPacket *Iso14827DatexDataPacket_gen(Dz1Error *err) { return Iso14827DatexDataPacket_new(Iso14827DatexVersionNumber_max, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827DatexDataPacket_purge(Iso14827DatexDataPacket *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827DatexDataPacket_del(Iso14827DatexDataPacket *p);
static __inline__ void Iso14827DatexDataPacket_delAndSetNull(void *ptr)
{
	Iso14827DatexDataPacket **p = (Iso14827DatexDataPacket **)ptr;
	if (p) { Iso14827DatexDataPacket_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827DatexDataPacket_dump(Iso14827DatexDataPacket *p, int tab);
// Iso14827DatexDataPacket
////////////////////////////////////////////////////////////////////////////////

#endif
