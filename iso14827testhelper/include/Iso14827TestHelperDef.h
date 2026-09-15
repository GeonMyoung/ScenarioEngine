#ifndef _DZ1_TDC_ISO14827_TEST_HELPER_DEF_H_
#define _DZ1_TDC_ISO14827_TEST_HELPER_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_asn1_support.h"
#include "libdz1_support.h"
#include "GitsnAsnUtilDef.h"
#include "ItsIso14827Def.h"
#include "Iso14827dz1.h"
#include "TechnicalRegulation1Def.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperException
typedef void (*Iso14827TestHelperException)(void *exceptionArg, Dz1Error *reason);
// Iso14827TestHelperException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Cost
typedef struct Gitsn_Iso14827Cost
{
	Dz1Str		currency;
	s32_t		factor;
	s32_t		qty;
} Gitsn_Iso14827Cost;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Cost *Gitsn_Iso14827Cost_new(Dz1Str currency, 
																   s32_t factor, 
																   s32_t qty, Dz1Error *err);
static __inline__ Gitsn_Iso14827Cost *Gitsn_Iso14827Cost_gen(Dz1Error *err) { return Gitsn_Iso14827Cost_new(NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827Cost_copy(Gitsn_Iso14827Cost *dst, Gitsn_Iso14827Cost *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Cost *Gitsn_Iso14827Cost_clone(Gitsn_Iso14827Cost *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Cost_purge(Gitsn_Iso14827Cost *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Cost_del(Gitsn_Iso14827Cost *p);
static __inline__ void Gitsn_Iso14827Cost_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Cost **p = (Gitsn_Iso14827Cost **)ptr;
	if (p) { Gitsn_Iso14827Cost_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Cost_dump(Gitsn_Iso14827Cost *p, int tab);
// Gitsn_Iso14827Cost
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TimeFracPresent
typedef enum Gitsn_Iso14827TimeFracPresent
{
	Gitsn_Iso14827TimeFracPresent_deci,
	Gitsn_Iso14827TimeFracPresent_centi,
	Gitsn_Iso14827TimeFracPresent_milli,
	Gitsn_Iso14827TimeFracPresent_max
} Gitsn_Iso14827TimeFracPresent;

DZ1_CPPLINK str_t Gitsn_Iso14827TimeFracPresentStrA(Gitsn_Iso14827TimeFracPresent v);
DZ1_CPPLINK Gitsn_Iso14827TimeFracPresent Gitsn_Iso14827TimeFracPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827TimeFracPresentStrW(Gitsn_Iso14827TimeFracPresent v);
DZ1_CPPLINK Gitsn_Iso14827TimeFracPresent Gitsn_Iso14827TimeFracPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827TimeFracPresentStr Gitsn_Iso14827TimeFracPresentStrW
#define Gitsn_Iso14827TimeFracPresentFromStr Gitsn_Iso14827TimeFracPresentFromStrW
#else // UNICODE
#define Gitsn_Iso14827TimeFracPresentStr Gitsn_Iso14827TimeFracPresentStrA
#define Gitsn_Iso14827TimeFracPresentFromStr Gitsn_Iso14827TimeFracPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827TimeFracPresentStr Gitsn_Iso14827TimeFracPresentStrA
#define Gitsn_Iso14827TimeFracPresentFromStr Gitsn_Iso14827TimeFracPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827TimeFracPresent *Gitsn_Iso14827TimeFracPresent_new(Gitsn_Iso14827TimeFracPresent *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827TimeFracPresent *Gitsn_Iso14827TimeFracPresent_gen(Dz1Error *err) { Gitsn_Iso14827TimeFracPresent v = Gitsn_Iso14827TimeFracPresent_max; return Gitsn_Iso14827TimeFracPresent_new(&v, err); }
#define Gitsn_Iso14827TimeFracPresent_clone             Gitsn_Iso14827TimeFracPresent_new
static __inline__ void Gitsn_Iso14827TimeFracPresent_del(Gitsn_Iso14827TimeFracPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827TimeFracPresent_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827TimeFracPresent **p = (Gitsn_Iso14827TimeFracPresent **)ptr;
	if (p != NULL) { Gitsn_Iso14827TimeFracPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TimeFracPresent_dump(Gitsn_Iso14827TimeFracPresent *v, int tab);
// Gitsn_Iso14827TimeFracPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TimeFrac
typedef struct Gitsn_Iso14827TimeFrac
{
	Gitsn_Iso14827TimeFracPresent present;
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
} Gitsn_Iso14827TimeFrac;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827TimeFrac *Gitsn_Iso14827TimeFrac_new(Gitsn_Iso14827TimeFracPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_Iso14827TimeFrac *Gitsn_Iso14827TimeFrac_gen(Dz1Error *err) { return Gitsn_Iso14827TimeFrac_new(Gitsn_Iso14827TimeFracPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_Iso14827TimeFrac_copy(Gitsn_Iso14827TimeFrac *dst, Gitsn_Iso14827TimeFrac *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827TimeFrac *Gitsn_Iso14827TimeFrac_clone(Gitsn_Iso14827TimeFrac *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TimeFrac_purge(Gitsn_Iso14827TimeFrac *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TimeFrac_del(Gitsn_Iso14827TimeFrac *p);
static __inline__ void Gitsn_Iso14827TimeFrac_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827TimeFrac **p = (Gitsn_Iso14827TimeFrac **)ptr;
	if (p != NULL) { Gitsn_Iso14827TimeFrac_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TimeFrac_dump(Gitsn_Iso14827TimeFrac *p, int tab);
// Gitsn_Iso14827TimeFrac
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TimeZone
typedef struct Gitsn_Iso14827TimeZone
{
	s32_t		modH;
	s32_t		modM;
} Gitsn_Iso14827TimeZone;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827TimeZone *Gitsn_Iso14827TimeZone_new(s32_t modH, 
																		   s32_t modM, Dz1Error *err);
static __inline__ Gitsn_Iso14827TimeZone *Gitsn_Iso14827TimeZone_gen(Dz1Error *err) { return Gitsn_Iso14827TimeZone_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827TimeZone_copy(Gitsn_Iso14827TimeZone *dst, Gitsn_Iso14827TimeZone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827TimeZone *Gitsn_Iso14827TimeZone_clone(Gitsn_Iso14827TimeZone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TimeZone_purge(Gitsn_Iso14827TimeZone *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TimeZone_del(Gitsn_Iso14827TimeZone *p);
static __inline__ void Gitsn_Iso14827TimeZone_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827TimeZone **p = (Gitsn_Iso14827TimeZone **)ptr;
	if (p) { Gitsn_Iso14827TimeZone_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TimeZone_dump(Gitsn_Iso14827TimeZone *p, int tab);
// Gitsn_Iso14827TimeZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Time
typedef struct Gitsn_Iso14827Time
{
	s32_t						*year;
	s32_t						*month;
	s32_t						*day;
	s32_t						 h;
	s32_t						 m;
	s32_t						 s;
	Gitsn_Iso14827TimeFrac		*frac;
	Gitsn_Iso14827TimeZone		*zone;
} Gitsn_Iso14827Time;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Time *Gitsn_Iso14827Time_new(s32_t *year, 
																   s32_t *month, 
																   s32_t *day, 
																   s32_t h, 
																   s32_t m, 
																   s32_t s, 
																   Gitsn_Iso14827TimeFrac *frac, 
																   Gitsn_Iso14827TimeZone *zone, Dz1Error *err);
static __inline__ Gitsn_Iso14827Time *Gitsn_Iso14827Time_gen(Dz1Error *err) { return Gitsn_Iso14827Time_new(NULL, NULL, NULL, 0, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827Time_copy(Gitsn_Iso14827Time *dst, Gitsn_Iso14827Time *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Time *Gitsn_Iso14827Time_clone(Gitsn_Iso14827Time *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Time_purge(Gitsn_Iso14827Time *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Time_del(Gitsn_Iso14827Time *p);
static __inline__ void Gitsn_Iso14827Time_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Time **p = (Gitsn_Iso14827Time **)ptr;
	if (p) { Gitsn_Iso14827Time_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Time_dump(Gitsn_Iso14827Time *p, int tab);
// Gitsn_Iso14827Time
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827HdrOpt
typedef struct Gitsn_Iso14827HdrOpt
{
	Dz1Str					 origin;
	Dz1Str					 originAddr;
	Dz1Str					 sender;
	Dz1Str					 senderAddr;
	Dz1Str					 dest;
	Dz1Str					 destAddr;
	Gitsn_Iso14827Cost		*cost;
	Gitsn_Iso14827Time		*t;
} Gitsn_Iso14827HdrOpt;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827HdrOpt *Gitsn_Iso14827HdrOpt_new(Dz1Str origin, 
																	   Dz1Str originAddr, 
																	   Dz1Str sender, 
																	   Dz1Str senderAddr, 
																	   Dz1Str dest, 
																	   Dz1Str destAddr, 
																	   Gitsn_Iso14827Cost *cost, 
																	   Gitsn_Iso14827Time *t, Dz1Error *err);
static __inline__ Gitsn_Iso14827HdrOpt *Gitsn_Iso14827HdrOpt_gen(Dz1Error *err) { return Gitsn_Iso14827HdrOpt_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827HdrOpt_copy(Gitsn_Iso14827HdrOpt *dst, Gitsn_Iso14827HdrOpt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827HdrOpt *Gitsn_Iso14827HdrOpt_clone(Gitsn_Iso14827HdrOpt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827HdrOpt_purge(Gitsn_Iso14827HdrOpt *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827HdrOpt_del(Gitsn_Iso14827HdrOpt *p);
static __inline__ void Gitsn_Iso14827HdrOpt_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827HdrOpt **p = (Gitsn_Iso14827HdrOpt **)ptr;
	if (p) { Gitsn_Iso14827HdrOpt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827HdrOpt_dump(Gitsn_Iso14827HdrOpt *p, int tab);
// Gitsn_Iso14827HdrOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Initiate
typedef struct Gitsn_Iso14827Initiate
{
	Dz1Str		sender;
	Dz1Str		dest;
} Gitsn_Iso14827Initiate;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Initiate *Gitsn_Iso14827Initiate_new(Dz1Str sender, 
																		   Dz1Str dest, Dz1Error *err);
static __inline__ Gitsn_Iso14827Initiate *Gitsn_Iso14827Initiate_gen(Dz1Error *err) { return Gitsn_Iso14827Initiate_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827Initiate_copy(Gitsn_Iso14827Initiate *dst, Gitsn_Iso14827Initiate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Initiate *Gitsn_Iso14827Initiate_clone(Gitsn_Iso14827Initiate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Initiate_purge(Gitsn_Iso14827Initiate *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Initiate_del(Gitsn_Iso14827Initiate *p);
static __inline__ void Gitsn_Iso14827Initiate_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Initiate **p = (Gitsn_Iso14827Initiate **)ptr;
	if (p) { Gitsn_Iso14827Initiate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Initiate_dump(Gitsn_Iso14827Initiate *p, int tab);
// Gitsn_Iso14827Initiate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Dz1OIDList
typedef struct Gitsn_Dz1OIDList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_Dz1OIDList *p);
	Dz1Error (*travel)(struct Gitsn_Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Str *(*get_array)(struct Gitsn_Dz1OIDList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_Dz1OIDList *p, Dz1Str data);
	Dz1Str (*find)(struct Gitsn_Dz1OIDList *p, Dz1Str key);
	int (*cmp)(Dz1Str a, Dz1Str b);
} Gitsn_Dz1OIDList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Dz1OIDList *Gitsn_Dz1OIDList_new(Dz1Error *err);
static __inline__ Gitsn_Dz1OIDList *Gitsn_Dz1OIDList_gen(Dz1Error *err) { return Gitsn_Dz1OIDList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Dz1OIDList *Gitsn_Dz1OIDList_clone(Gitsn_Dz1OIDList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Dz1OIDList_purge(Gitsn_Dz1OIDList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Dz1OIDList_del(Gitsn_Dz1OIDList *p);
static __inline__ void Gitsn_Dz1OIDList_delAndSetNull(void *ptr)
{
	Gitsn_Dz1OIDList **p = (Gitsn_Dz1OIDList **)ptr;
	if (p != NULL) { Gitsn_Dz1OIDList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Dz1OIDListA_dump(Gitsn_Dz1OIDList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Dz1OIDListA_fdump(FILE *fp, Gitsn_Dz1OIDList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Dz1OIDListW_dump(Gitsn_Dz1OIDList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Dz1OIDListW_fdump(FILE *fp, Gitsn_Dz1OIDList *p, int tab);
#ifdef UNICODE
#define Gitsn_Dz1OIDList_dump Gitsn_Dz1OIDListW_dump
#define Gitsn_Dz1OIDList_fdump Gitsn_Dz1OIDListW_fdump
#else //  UNICODE
#define Gitsn_Dz1OIDList_dump Gitsn_Dz1OIDListA_dump
#define Gitsn_Dz1OIDList_fdump Gitsn_Dz1OIDListA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Dz1OIDListX_dump(Gitsn_Dz1OIDList *p, int tab) { DZ1_DUMP(Gitsn_Dz1OIDList, p, tab); }
static __inline__ void Gitsn_Dz1OIDListX_fdump(FILE *fp, Gitsn_Dz1OIDList *p, int tab) { DZ1_FDUMP(fp, Gitsn_Dz1OIDList, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Dz1OIDList_dump Gitsn_Dz1OIDListA_dump
#define Gitsn_Dz1OIDListX_dump Gitsn_Dz1OIDListA_dump
#define Gitsn_Dz1OIDList_fdump Gitsn_Dz1OIDListA_fdump
#define Gitsn_Dz1OIDListX_fdump Gitsn_Dz1OIDListA_fdump
#endif // UNIX_SYSTEM

// Gitsn_Dz1OIDList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827LoginInitiator
typedef enum Gitsn_Iso14827LoginInitiator
{
	Gitsn_Iso14827LoginInitiator_serverInitiated,
	Gitsn_Iso14827LoginInitiator_clientInitiated,
	Gitsn_Iso14827LoginInitiator_max
} Gitsn_Iso14827LoginInitiator;

DZ1_CPPLINK str_t Gitsn_Iso14827LoginInitiatorStrA(Gitsn_Iso14827LoginInitiator v);
DZ1_CPPLINK Gitsn_Iso14827LoginInitiator Gitsn_Iso14827LoginInitiatorFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827LoginInitiatorStrW(Gitsn_Iso14827LoginInitiator v);
DZ1_CPPLINK Gitsn_Iso14827LoginInitiator Gitsn_Iso14827LoginInitiatorFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827LoginInitiatorStr Gitsn_Iso14827LoginInitiatorStrW
#define Gitsn_Iso14827LoginInitiatorFromStr Gitsn_Iso14827LoginInitiatorFromStrW
#else // UNICODE
#define Gitsn_Iso14827LoginInitiatorStr Gitsn_Iso14827LoginInitiatorStrA
#define Gitsn_Iso14827LoginInitiatorFromStr Gitsn_Iso14827LoginInitiatorFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827LoginInitiatorStr Gitsn_Iso14827LoginInitiatorStrA
#define Gitsn_Iso14827LoginInitiatorFromStr Gitsn_Iso14827LoginInitiatorFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827LoginInitiator *Gitsn_Iso14827LoginInitiator_new(Gitsn_Iso14827LoginInitiator *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827LoginInitiator *Gitsn_Iso14827LoginInitiator_gen(Dz1Error *err) { Gitsn_Iso14827LoginInitiator v = Gitsn_Iso14827LoginInitiator_max; return Gitsn_Iso14827LoginInitiator_new(&v, err); }
static __inline__ void Gitsn_Iso14827LoginInitiator_del(Gitsn_Iso14827LoginInitiator *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827LoginInitiator_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827LoginInitiator **p = (Gitsn_Iso14827LoginInitiator **)ptr;
	if (p != NULL) { Gitsn_Iso14827LoginInitiator_del(*p); *p = NULL; }
}
// Gitsn_Iso14827LoginInitiator
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Login
typedef struct Gitsn_Iso14827Login
{
	Dz1Str							 sender;
	Dz1Str							 dest;
	Dz1Str							 user;
	Dz1Str							 pass;
	Gitsn_Dz1OIDList				*encRules;
	s32_t							 hbDur;
	s32_t							 timeout;
	Gitsn_Iso14827LoginInitiator	 initiator;
	u16_t							 datagramSize;
} Gitsn_Iso14827Login;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Login *Gitsn_Iso14827Login_new(Dz1Str sender, 
																	 Dz1Str dest, 
																	 Dz1Str user, 
																	 Dz1Str pass, 
																	 s32_t hbDur, 
																	 s32_t timeout, 
																	 Gitsn_Iso14827LoginInitiator initiator, 
																	 u16_t datagramSize, Dz1Error *err);
static __inline__ Gitsn_Iso14827Login *Gitsn_Iso14827Login_gen(Dz1Error *err) { return Gitsn_Iso14827Login_new(NULL, NULL, NULL, NULL, 0, 0, Gitsn_Iso14827LoginInitiator_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827Login_copy(Gitsn_Iso14827Login *dst, Gitsn_Iso14827Login *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Login *Gitsn_Iso14827Login_clone(Gitsn_Iso14827Login *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Login_purge(Gitsn_Iso14827Login *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Login_del(Gitsn_Iso14827Login *p);
static __inline__ void Gitsn_Iso14827Login_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Login **p = (Gitsn_Iso14827Login **)ptr;
	if (p) { Gitsn_Iso14827Login_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Login_dump(Gitsn_Iso14827Login *p, int tab);
// Gitsn_Iso14827Login
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Terminate
typedef enum Gitsn_Iso14827Terminate
{
	Gitsn_Iso14827Terminate_other,
	Gitsn_Iso14827Terminate_serverRequested,
	Gitsn_Iso14827Terminate_clientRequested,
	Gitsn_Iso14827Terminate_serverShutdown,
	Gitsn_Iso14827Terminate_clientShutdown,
	Gitsn_Iso14827Terminate_serverCommProblems,
	Gitsn_Iso14827Terminate_clientCommProblems,
	Gitsn_Iso14827Terminate_max
} Gitsn_Iso14827Terminate;

DZ1_CPPLINK str_t Gitsn_Iso14827TerminateStrA(Gitsn_Iso14827Terminate v);
DZ1_CPPLINK Gitsn_Iso14827Terminate Gitsn_Iso14827TerminateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827TerminateStrW(Gitsn_Iso14827Terminate v);
DZ1_CPPLINK Gitsn_Iso14827Terminate Gitsn_Iso14827TerminateFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827TerminateStr Gitsn_Iso14827TerminateStrW
#define Gitsn_Iso14827TerminateFromStr Gitsn_Iso14827TerminateFromStrW
#else // UNICODE
#define Gitsn_Iso14827TerminateStr Gitsn_Iso14827TerminateStrA
#define Gitsn_Iso14827TerminateFromStr Gitsn_Iso14827TerminateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827TerminateStr Gitsn_Iso14827TerminateStrA
#define Gitsn_Iso14827TerminateFromStr Gitsn_Iso14827TerminateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Terminate *Gitsn_Iso14827Terminate_new(Gitsn_Iso14827Terminate *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827Terminate *Gitsn_Iso14827Terminate_gen(Dz1Error *err) { Gitsn_Iso14827Terminate v = Gitsn_Iso14827Terminate_max; return Gitsn_Iso14827Terminate_new(&v, err); }
static __inline__ void Gitsn_Iso14827Terminate_del(Gitsn_Iso14827Terminate *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827Terminate_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Terminate **p = (Gitsn_Iso14827Terminate **)ptr;
	if (p != NULL) { Gitsn_Iso14827Terminate_del(*p); *p = NULL; }
}
// Gitsn_Iso14827Terminate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Logout
typedef enum Gitsn_Iso14827Logout
{
	Gitsn_Iso14827Logout_other,
	Gitsn_Iso14827Logout_serverRequested,
	Gitsn_Iso14827Logout_clientRequested,
	Gitsn_Iso14827Logout_serverShutdown,
	Gitsn_Iso14827Logout_clientShutdown,
	Gitsn_Iso14827Logout_serverCommProblems,
	Gitsn_Iso14827Logout_clientCommProblems,
	Gitsn_Iso14827Logout_max
} Gitsn_Iso14827Logout;

DZ1_CPPLINK str_t Gitsn_Iso14827LogoutStrA(Gitsn_Iso14827Logout v);
DZ1_CPPLINK Gitsn_Iso14827Logout Gitsn_Iso14827LogoutFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827LogoutStrW(Gitsn_Iso14827Logout v);
DZ1_CPPLINK Gitsn_Iso14827Logout Gitsn_Iso14827LogoutFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827LogoutStr Gitsn_Iso14827LogoutStrW
#define Gitsn_Iso14827LogoutFromStr Gitsn_Iso14827LogoutFromStrW
#else // UNICODE
#define Gitsn_Iso14827LogoutStr Gitsn_Iso14827LogoutStrA
#define Gitsn_Iso14827LogoutFromStr Gitsn_Iso14827LogoutFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827LogoutStr Gitsn_Iso14827LogoutStrA
#define Gitsn_Iso14827LogoutFromStr Gitsn_Iso14827LogoutFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Logout *Gitsn_Iso14827Logout_new(Gitsn_Iso14827Logout *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827Logout *Gitsn_Iso14827Logout_gen(Dz1Error *err) { Gitsn_Iso14827Logout v = Gitsn_Iso14827Logout_max; return Gitsn_Iso14827Logout_new(&v, err); }
static __inline__ void Gitsn_Iso14827Logout_del(Gitsn_Iso14827Logout *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827Logout_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Logout **p = (Gitsn_Iso14827Logout **)ptr;
	if (p != NULL) { Gitsn_Iso14827Logout_del(*p); *p = NULL; }
}
// Gitsn_Iso14827Logout
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataStatus
typedef enum Gitsn_Iso14827SubscriptionDataStatus
{
	Gitsn_Iso14827SubscriptionDataStatus_NEW,
	Gitsn_Iso14827SubscriptionDataStatus_UPDATED,
	Gitsn_Iso14827SubscriptionDataStatus_max
} Gitsn_Iso14827SubscriptionDataStatus;

DZ1_CPPLINK str_t Gitsn_Iso14827SubscriptionDataStatusStrA(Gitsn_Iso14827SubscriptionDataStatus v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionDataStatus Gitsn_Iso14827SubscriptionDataStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827SubscriptionDataStatusStrW(Gitsn_Iso14827SubscriptionDataStatus v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionDataStatus Gitsn_Iso14827SubscriptionDataStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827SubscriptionDataStatusStr Gitsn_Iso14827SubscriptionDataStatusStrW
#define Gitsn_Iso14827SubscriptionDataStatusFromStr Gitsn_Iso14827SubscriptionDataStatusFromStrW
#else // UNICODE
#define Gitsn_Iso14827SubscriptionDataStatusStr Gitsn_Iso14827SubscriptionDataStatusStrA
#define Gitsn_Iso14827SubscriptionDataStatusFromStr Gitsn_Iso14827SubscriptionDataStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827SubscriptionDataStatusStr Gitsn_Iso14827SubscriptionDataStatusStrA
#define Gitsn_Iso14827SubscriptionDataStatusFromStr Gitsn_Iso14827SubscriptionDataStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionDataStatus *Gitsn_Iso14827SubscriptionDataStatus_new(Gitsn_Iso14827SubscriptionDataStatus *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827SubscriptionDataStatus *Gitsn_Iso14827SubscriptionDataStatus_gen(Dz1Error *err) { Gitsn_Iso14827SubscriptionDataStatus v = Gitsn_Iso14827SubscriptionDataStatus_max; return Gitsn_Iso14827SubscriptionDataStatus_new(&v, err); }
static __inline__ void Gitsn_Iso14827SubscriptionDataStatus_del(Gitsn_Iso14827SubscriptionDataStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827SubscriptionDataStatus_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827SubscriptionDataStatus **p = (Gitsn_Iso14827SubscriptionDataStatus **)ptr;
	if (p != NULL) { Gitsn_Iso14827SubscriptionDataStatus_del(*p); *p = NULL; }
}
// Gitsn_Iso14827SubscriptionDataStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RegisteredContinuous
typedef struct Gitsn_Iso14827RegisteredContinuous
{
	u32_t					 updateDelay;
	Gitsn_Iso14827Time		*start;
	Gitsn_Iso14827Time		*end;
} Gitsn_Iso14827RegisteredContinuous;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RegisteredContinuous *Gitsn_Iso14827RegisteredContinuous_new(u32_t updateDelay, 
																								   Gitsn_Iso14827Time *start, 
																								   Gitsn_Iso14827Time *end, Dz1Error *err);
static __inline__ Gitsn_Iso14827RegisteredContinuous *Gitsn_Iso14827RegisteredContinuous_gen(Dz1Error *err) { return Gitsn_Iso14827RegisteredContinuous_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827RegisteredContinuous_copy(Gitsn_Iso14827RegisteredContinuous *dst, Gitsn_Iso14827RegisteredContinuous *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RegisteredContinuous *Gitsn_Iso14827RegisteredContinuous_clone(Gitsn_Iso14827RegisteredContinuous *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RegisteredContinuous_purge(Gitsn_Iso14827RegisteredContinuous *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RegisteredContinuous_del(Gitsn_Iso14827RegisteredContinuous *p);
static __inline__ void Gitsn_Iso14827RegisteredContinuous_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RegisteredContinuous **p = (Gitsn_Iso14827RegisteredContinuous **)ptr;
	if (p) { Gitsn_Iso14827RegisteredContinuous_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RegisteredContinuous_dump(Gitsn_Iso14827RegisteredContinuous *p, int tab);
// Gitsn_Iso14827RegisteredContinuous
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RegisteredDaily
typedef struct Gitsn_Iso14827RegisteredDaily
{
	u32_t					 updateDelay;
	u8_t					 daysOfWeek;
	Gitsn_Iso14827Time		*startDate;
	Gitsn_Iso14827Time		*endDate;
	Gitsn_Iso14827Time		*startTime;
	u16_t					*duration;
} Gitsn_Iso14827RegisteredDaily;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RegisteredDaily *Gitsn_Iso14827RegisteredDaily_new(u32_t updateDelay, 
																						 u8_t daysOfWeek, 
																						 Gitsn_Iso14827Time *startDate, 
																						 Gitsn_Iso14827Time *endDate, 
																						 Gitsn_Iso14827Time *startTime, 
																						 u16_t *duration, Dz1Error *err);
static __inline__ Gitsn_Iso14827RegisteredDaily *Gitsn_Iso14827RegisteredDaily_gen(Dz1Error *err) { return Gitsn_Iso14827RegisteredDaily_new(0, 0, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827RegisteredDaily_copy(Gitsn_Iso14827RegisteredDaily *dst, Gitsn_Iso14827RegisteredDaily *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RegisteredDaily *Gitsn_Iso14827RegisteredDaily_clone(Gitsn_Iso14827RegisteredDaily *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RegisteredDaily_purge(Gitsn_Iso14827RegisteredDaily *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RegisteredDaily_del(Gitsn_Iso14827RegisteredDaily *p);
static __inline__ void Gitsn_Iso14827RegisteredDaily_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RegisteredDaily **p = (Gitsn_Iso14827RegisteredDaily **)ptr;
	if (p) { Gitsn_Iso14827RegisteredDaily_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RegisteredDaily_dump(Gitsn_Iso14827RegisteredDaily *p, int tab);
// Gitsn_Iso14827RegisteredDaily
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RegisteredPresent
typedef enum Gitsn_Iso14827RegisteredPresent
{
	Gitsn_Iso14827RegisteredPresent_continuous,
	Gitsn_Iso14827RegisteredPresent_daily,
	Gitsn_Iso14827RegisteredPresent_max
} Gitsn_Iso14827RegisteredPresent;

DZ1_CPPLINK str_t Gitsn_Iso14827RegisteredPresentStrA(Gitsn_Iso14827RegisteredPresent v);
DZ1_CPPLINK Gitsn_Iso14827RegisteredPresent Gitsn_Iso14827RegisteredPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827RegisteredPresentStrW(Gitsn_Iso14827RegisteredPresent v);
DZ1_CPPLINK Gitsn_Iso14827RegisteredPresent Gitsn_Iso14827RegisteredPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827RegisteredPresentStr Gitsn_Iso14827RegisteredPresentStrW
#define Gitsn_Iso14827RegisteredPresentFromStr Gitsn_Iso14827RegisteredPresentFromStrW
#else // UNICODE
#define Gitsn_Iso14827RegisteredPresentStr Gitsn_Iso14827RegisteredPresentStrA
#define Gitsn_Iso14827RegisteredPresentFromStr Gitsn_Iso14827RegisteredPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827RegisteredPresentStr Gitsn_Iso14827RegisteredPresentStrA
#define Gitsn_Iso14827RegisteredPresentFromStr Gitsn_Iso14827RegisteredPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RegisteredPresent *Gitsn_Iso14827RegisteredPresent_new(Gitsn_Iso14827RegisteredPresent *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827RegisteredPresent *Gitsn_Iso14827RegisteredPresent_gen(Dz1Error *err) { Gitsn_Iso14827RegisteredPresent v = Gitsn_Iso14827RegisteredPresent_max; return Gitsn_Iso14827RegisteredPresent_new(&v, err); }
#define Gitsn_Iso14827RegisteredPresent_clone             Gitsn_Iso14827RegisteredPresent_new
static __inline__ void Gitsn_Iso14827RegisteredPresent_del(Gitsn_Iso14827RegisteredPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827RegisteredPresent_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RegisteredPresent **p = (Gitsn_Iso14827RegisteredPresent **)ptr;
	if (p != NULL) { Gitsn_Iso14827RegisteredPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RegisteredPresent_dump(Gitsn_Iso14827RegisteredPresent *v, int tab);
// Gitsn_Iso14827RegisteredPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Registered
typedef struct Gitsn_Iso14827Registered
{
	Gitsn_Iso14827RegisteredPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_Iso14827RegisteredContinuous		*continuous;
		Gitsn_Iso14827RegisteredDaily			*daily;
	} x;
} Gitsn_Iso14827Registered;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Registered *Gitsn_Iso14827Registered_new(Gitsn_Iso14827RegisteredPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_Iso14827Registered *Gitsn_Iso14827Registered_gen(Dz1Error *err) { return Gitsn_Iso14827Registered_new(Gitsn_Iso14827RegisteredPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_Iso14827Registered_copy(Gitsn_Iso14827Registered *dst, Gitsn_Iso14827Registered *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Registered *Gitsn_Iso14827Registered_clone(Gitsn_Iso14827Registered *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Registered_purge(Gitsn_Iso14827Registered *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Registered_del(Gitsn_Iso14827Registered *p);
static __inline__ void Gitsn_Iso14827Registered_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Registered **p = (Gitsn_Iso14827Registered **)ptr;
	if (p != NULL) { Gitsn_Iso14827Registered_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Registered_dump(Gitsn_Iso14827Registered *p, int tab);
// Gitsn_Iso14827Registered
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataModePresent
typedef enum Gitsn_Iso14827SubscriptionDataModePresent
{
	Gitsn_Iso14827SubscriptionDataModePresent_single,
	Gitsn_Iso14827SubscriptionDataModePresent_eventDriven,
	Gitsn_Iso14827SubscriptionDataModePresent_periodic,
	Gitsn_Iso14827SubscriptionDataModePresent_max
} Gitsn_Iso14827SubscriptionDataModePresent;

DZ1_CPPLINK str_t Gitsn_Iso14827SubscriptionDataModePresentStrA(Gitsn_Iso14827SubscriptionDataModePresent v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionDataModePresent Gitsn_Iso14827SubscriptionDataModePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827SubscriptionDataModePresentStrW(Gitsn_Iso14827SubscriptionDataModePresent v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionDataModePresent Gitsn_Iso14827SubscriptionDataModePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827SubscriptionDataModePresentStr Gitsn_Iso14827SubscriptionDataModePresentStrW
#define Gitsn_Iso14827SubscriptionDataModePresentFromStr Gitsn_Iso14827SubscriptionDataModePresentFromStrW
#else // UNICODE
#define Gitsn_Iso14827SubscriptionDataModePresentStr Gitsn_Iso14827SubscriptionDataModePresentStrA
#define Gitsn_Iso14827SubscriptionDataModePresentFromStr Gitsn_Iso14827SubscriptionDataModePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827SubscriptionDataModePresentStr Gitsn_Iso14827SubscriptionDataModePresentStrA
#define Gitsn_Iso14827SubscriptionDataModePresentFromStr Gitsn_Iso14827SubscriptionDataModePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionDataModePresent *Gitsn_Iso14827SubscriptionDataModePresent_new(Gitsn_Iso14827SubscriptionDataModePresent *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827SubscriptionDataModePresent *Gitsn_Iso14827SubscriptionDataModePresent_gen(Dz1Error *err) { Gitsn_Iso14827SubscriptionDataModePresent v = Gitsn_Iso14827SubscriptionDataModePresent_max; return Gitsn_Iso14827SubscriptionDataModePresent_new(&v, err); }
#define Gitsn_Iso14827SubscriptionDataModePresent_clone             Gitsn_Iso14827SubscriptionDataModePresent_new
static __inline__ void Gitsn_Iso14827SubscriptionDataModePresent_del(Gitsn_Iso14827SubscriptionDataModePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827SubscriptionDataModePresent_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827SubscriptionDataModePresent **p = (Gitsn_Iso14827SubscriptionDataModePresent **)ptr;
	if (p != NULL) { Gitsn_Iso14827SubscriptionDataModePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionDataModePresent_dump(Gitsn_Iso14827SubscriptionDataModePresent *v, int tab);
// Gitsn_Iso14827SubscriptionDataModePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataMode
typedef struct Gitsn_Iso14827SubscriptionDataMode
{
	Gitsn_Iso14827SubscriptionDataModePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		s32_t						*single;
		Gitsn_Iso14827Registered	*eventDriven;
		Gitsn_Iso14827Registered	*periodic;
	} x;
} Gitsn_Iso14827SubscriptionDataMode;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionDataMode *Gitsn_Iso14827SubscriptionDataMode_new(Gitsn_Iso14827SubscriptionDataModePresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_Iso14827SubscriptionDataMode *Gitsn_Iso14827SubscriptionDataMode_gen(Dz1Error *err) { return Gitsn_Iso14827SubscriptionDataMode_new(Gitsn_Iso14827SubscriptionDataModePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_Iso14827SubscriptionDataMode_copy(Gitsn_Iso14827SubscriptionDataMode *dst, Gitsn_Iso14827SubscriptionDataMode *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionDataMode *Gitsn_Iso14827SubscriptionDataMode_clone(Gitsn_Iso14827SubscriptionDataMode *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionDataMode_purge(Gitsn_Iso14827SubscriptionDataMode *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionDataMode_del(Gitsn_Iso14827SubscriptionDataMode *p);
static __inline__ void Gitsn_Iso14827SubscriptionDataMode_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827SubscriptionDataMode **p = (Gitsn_Iso14827SubscriptionDataMode **)ptr;
	if (p != NULL) { Gitsn_Iso14827SubscriptionDataMode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionDataMode_dump(Gitsn_Iso14827SubscriptionDataMode *p, int tab);
// Gitsn_Iso14827SubscriptionDataMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataFormat
typedef enum Gitsn_Iso14827SubscriptionDataFormat
{
	Gitsn_Iso14827SubscriptionDataFormat_other,
	Gitsn_Iso14827SubscriptionDataFormat_ftp,
	Gitsn_Iso14827SubscriptionDataFormat_tftp,
	Gitsn_Iso14827SubscriptionDataFormat_dataPacket,
	Gitsn_Iso14827SubscriptionDataFormat_max
} Gitsn_Iso14827SubscriptionDataFormat;

DZ1_CPPLINK str_t Gitsn_Iso14827SubscriptionDataFormatStrA(Gitsn_Iso14827SubscriptionDataFormat v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionDataFormat Gitsn_Iso14827SubscriptionDataFormatFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827SubscriptionDataFormatStrW(Gitsn_Iso14827SubscriptionDataFormat v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionDataFormat Gitsn_Iso14827SubscriptionDataFormatFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827SubscriptionDataFormatStr Gitsn_Iso14827SubscriptionDataFormatStrW
#define Gitsn_Iso14827SubscriptionDataFormatFromStr Gitsn_Iso14827SubscriptionDataFormatFromStrW
#else // UNICODE
#define Gitsn_Iso14827SubscriptionDataFormatStr Gitsn_Iso14827SubscriptionDataFormatStrA
#define Gitsn_Iso14827SubscriptionDataFormatFromStr Gitsn_Iso14827SubscriptionDataFormatFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827SubscriptionDataFormatStr Gitsn_Iso14827SubscriptionDataFormatStrA
#define Gitsn_Iso14827SubscriptionDataFormatFromStr Gitsn_Iso14827SubscriptionDataFormatFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionDataFormat *Gitsn_Iso14827SubscriptionDataFormat_new(Gitsn_Iso14827SubscriptionDataFormat *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827SubscriptionDataFormat *Gitsn_Iso14827SubscriptionDataFormat_gen(Dz1Error *err) { Gitsn_Iso14827SubscriptionDataFormat v = Gitsn_Iso14827SubscriptionDataFormat_max; return Gitsn_Iso14827SubscriptionDataFormat_new(&v, err); }
static __inline__ void Gitsn_Iso14827SubscriptionDataFormat_del(Gitsn_Iso14827SubscriptionDataFormat *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827SubscriptionDataFormat_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827SubscriptionDataFormat **p = (Gitsn_Iso14827SubscriptionDataFormat **)ptr;
	if (p != NULL) { Gitsn_Iso14827SubscriptionDataFormat_del(*p); *p = NULL; }
}
// Gitsn_Iso14827SubscriptionDataFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827EndAppMsg
typedef struct Gitsn_Iso14827EndAppMsg
{
	Dz1Str			 oid;
	Dz1Binary		*data;
} Gitsn_Iso14827EndAppMsg;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827EndAppMsg *Gitsn_Iso14827EndAppMsg_new(Dz1Str oid, 
																			 Dz1Binary *data, Dz1Error *err);
static __inline__ Gitsn_Iso14827EndAppMsg *Gitsn_Iso14827EndAppMsg_gen(Dz1Error *err) { return Gitsn_Iso14827EndAppMsg_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827EndAppMsg_copy(Gitsn_Iso14827EndAppMsg *dst, Gitsn_Iso14827EndAppMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827EndAppMsg *Gitsn_Iso14827EndAppMsg_clone(Gitsn_Iso14827EndAppMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827EndAppMsg_purge(Gitsn_Iso14827EndAppMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827EndAppMsg_del(Gitsn_Iso14827EndAppMsg *p);
static __inline__ void Gitsn_Iso14827EndAppMsg_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827EndAppMsg **p = (Gitsn_Iso14827EndAppMsg **)ptr;
	if (p) { Gitsn_Iso14827EndAppMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827EndAppMsg_dump(Gitsn_Iso14827EndAppMsg *p, int tab);
// Gitsn_Iso14827EndAppMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionData
typedef struct Gitsn_Iso14827SubscriptionData
{
	bool_t									 persistent;
	Gitsn_Iso14827SubscriptionDataStatus	 status;
	Gitsn_Iso14827SubscriptionDataMode		*mode;
	Gitsn_Iso14827SubscriptionDataFormat	 fmt;
	s32_t									 priority;
	bool_t									 guarantee;
	Gitsn_Iso14827EndAppMsg					*msg;
} Gitsn_Iso14827SubscriptionData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionData *Gitsn_Iso14827SubscriptionData_new(bool_t persistent, 
																						   Gitsn_Iso14827SubscriptionDataStatus status, 
																						   Gitsn_Iso14827SubscriptionDataMode *mode, 
																						   Gitsn_Iso14827SubscriptionDataFormat fmt, 
																						   s32_t priority, 
																						   bool_t guarantee, 
																						   Gitsn_Iso14827EndAppMsg *msg, Dz1Error *err);
static __inline__ Gitsn_Iso14827SubscriptionData *Gitsn_Iso14827SubscriptionData_gen(Dz1Error *err) { return Gitsn_Iso14827SubscriptionData_new(0, Gitsn_Iso14827SubscriptionDataStatus_max, NULL, Gitsn_Iso14827SubscriptionDataFormat_max, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827SubscriptionData_copy(Gitsn_Iso14827SubscriptionData *dst, Gitsn_Iso14827SubscriptionData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionData *Gitsn_Iso14827SubscriptionData_clone(Gitsn_Iso14827SubscriptionData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionData_purge(Gitsn_Iso14827SubscriptionData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionData_del(Gitsn_Iso14827SubscriptionData *p);
static __inline__ void Gitsn_Iso14827SubscriptionData_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827SubscriptionData **p = (Gitsn_Iso14827SubscriptionData **)ptr;
	if (p) { Gitsn_Iso14827SubscriptionData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionData_dump(Gitsn_Iso14827SubscriptionData *p, int tab);
// Gitsn_Iso14827SubscriptionData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionCancel
typedef enum Gitsn_Iso14827SubscriptionCancel
{
	Gitsn_Iso14827SubscriptionCancel_other,
	Gitsn_Iso14827SubscriptionCancel_dataNotNeeded,
	Gitsn_Iso14827SubscriptionCancel_errorsInPublication,
	Gitsn_Iso14827SubscriptionCancel_pendingLogout,
	Gitsn_Iso14827SubscriptionCancel_processingMgmt,
	Gitsn_Iso14827SubscriptionCancel_bandwidthMgmt,
	Gitsn_Iso14827SubscriptionCancel_max
} Gitsn_Iso14827SubscriptionCancel;

DZ1_CPPLINK str_t Gitsn_Iso14827SubscriptionCancelStrA(Gitsn_Iso14827SubscriptionCancel v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionCancel Gitsn_Iso14827SubscriptionCancelFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827SubscriptionCancelStrW(Gitsn_Iso14827SubscriptionCancel v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionCancel Gitsn_Iso14827SubscriptionCancelFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827SubscriptionCancelStr Gitsn_Iso14827SubscriptionCancelStrW
#define Gitsn_Iso14827SubscriptionCancelFromStr Gitsn_Iso14827SubscriptionCancelFromStrW
#else // UNICODE
#define Gitsn_Iso14827SubscriptionCancelStr Gitsn_Iso14827SubscriptionCancelStrA
#define Gitsn_Iso14827SubscriptionCancelFromStr Gitsn_Iso14827SubscriptionCancelFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827SubscriptionCancelStr Gitsn_Iso14827SubscriptionCancelStrA
#define Gitsn_Iso14827SubscriptionCancelFromStr Gitsn_Iso14827SubscriptionCancelFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionCancel *Gitsn_Iso14827SubscriptionCancel_new(Gitsn_Iso14827SubscriptionCancel *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827SubscriptionCancel *Gitsn_Iso14827SubscriptionCancel_gen(Dz1Error *err) { Gitsn_Iso14827SubscriptionCancel v = Gitsn_Iso14827SubscriptionCancel_max; return Gitsn_Iso14827SubscriptionCancel_new(&v, err); }
static __inline__ void Gitsn_Iso14827SubscriptionCancel_del(Gitsn_Iso14827SubscriptionCancel *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827SubscriptionCancel_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827SubscriptionCancel **p = (Gitsn_Iso14827SubscriptionCancel **)ptr;
	if (p != NULL) { Gitsn_Iso14827SubscriptionCancel_del(*p); *p = NULL; }
}
// Gitsn_Iso14827SubscriptionCancel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionTypePresent
typedef enum Gitsn_Iso14827SubscriptionTypePresent
{
	Gitsn_Iso14827SubscriptionTypePresent_data,
	Gitsn_Iso14827SubscriptionTypePresent_reason,
	Gitsn_Iso14827SubscriptionTypePresent_max
} Gitsn_Iso14827SubscriptionTypePresent;

DZ1_CPPLINK str_t Gitsn_Iso14827SubscriptionTypePresentStrA(Gitsn_Iso14827SubscriptionTypePresent v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionTypePresent Gitsn_Iso14827SubscriptionTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827SubscriptionTypePresentStrW(Gitsn_Iso14827SubscriptionTypePresent v);
DZ1_CPPLINK Gitsn_Iso14827SubscriptionTypePresent Gitsn_Iso14827SubscriptionTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827SubscriptionTypePresentStr Gitsn_Iso14827SubscriptionTypePresentStrW
#define Gitsn_Iso14827SubscriptionTypePresentFromStr Gitsn_Iso14827SubscriptionTypePresentFromStrW
#else // UNICODE
#define Gitsn_Iso14827SubscriptionTypePresentStr Gitsn_Iso14827SubscriptionTypePresentStrA
#define Gitsn_Iso14827SubscriptionTypePresentFromStr Gitsn_Iso14827SubscriptionTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827SubscriptionTypePresentStr Gitsn_Iso14827SubscriptionTypePresentStrA
#define Gitsn_Iso14827SubscriptionTypePresentFromStr Gitsn_Iso14827SubscriptionTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionTypePresent *Gitsn_Iso14827SubscriptionTypePresent_new(Gitsn_Iso14827SubscriptionTypePresent *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827SubscriptionTypePresent *Gitsn_Iso14827SubscriptionTypePresent_gen(Dz1Error *err) { Gitsn_Iso14827SubscriptionTypePresent v = Gitsn_Iso14827SubscriptionTypePresent_max; return Gitsn_Iso14827SubscriptionTypePresent_new(&v, err); }
#define Gitsn_Iso14827SubscriptionTypePresent_clone             Gitsn_Iso14827SubscriptionTypePresent_new
static __inline__ void Gitsn_Iso14827SubscriptionTypePresent_del(Gitsn_Iso14827SubscriptionTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827SubscriptionTypePresent_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827SubscriptionTypePresent **p = (Gitsn_Iso14827SubscriptionTypePresent **)ptr;
	if (p != NULL) { Gitsn_Iso14827SubscriptionTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionTypePresent_dump(Gitsn_Iso14827SubscriptionTypePresent *v, int tab);
// Gitsn_Iso14827SubscriptionTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionType
typedef struct Gitsn_Iso14827SubscriptionType
{
	Gitsn_Iso14827SubscriptionTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_Iso14827SubscriptionData		*data;
		Gitsn_Iso14827SubscriptionCancel	 reason;
	} x;
} Gitsn_Iso14827SubscriptionType;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionType *Gitsn_Iso14827SubscriptionType_new(Gitsn_Iso14827SubscriptionTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_Iso14827SubscriptionType *Gitsn_Iso14827SubscriptionType_gen(Dz1Error *err) { return Gitsn_Iso14827SubscriptionType_new(Gitsn_Iso14827SubscriptionTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_Iso14827SubscriptionType_copy(Gitsn_Iso14827SubscriptionType *dst, Gitsn_Iso14827SubscriptionType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827SubscriptionType *Gitsn_Iso14827SubscriptionType_clone(Gitsn_Iso14827SubscriptionType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionType_purge(Gitsn_Iso14827SubscriptionType *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionType_del(Gitsn_Iso14827SubscriptionType *p);
static __inline__ void Gitsn_Iso14827SubscriptionType_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827SubscriptionType **p = (Gitsn_Iso14827SubscriptionType **)ptr;
	if (p != NULL) { Gitsn_Iso14827SubscriptionType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827SubscriptionType_dump(Gitsn_Iso14827SubscriptionType *p, int tab);
// Gitsn_Iso14827SubscriptionType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Subscription
typedef struct Gitsn_Iso14827Subscription
{
	u32_t								 serial;
	Gitsn_Iso14827SubscriptionType		*type;
} Gitsn_Iso14827Subscription;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Subscription *Gitsn_Iso14827Subscription_new(u32_t serial, 
																				   Gitsn_Iso14827SubscriptionType *type, Dz1Error *err);
static __inline__ Gitsn_Iso14827Subscription *Gitsn_Iso14827Subscription_gen(Dz1Error *err) { return Gitsn_Iso14827Subscription_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827Subscription_copy(Gitsn_Iso14827Subscription *dst, Gitsn_Iso14827Subscription *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Subscription *Gitsn_Iso14827Subscription_clone(Gitsn_Iso14827Subscription *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Subscription_purge(Gitsn_Iso14827Subscription *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Subscription_del(Gitsn_Iso14827Subscription *p);
static __inline__ void Gitsn_Iso14827Subscription_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Subscription **p = (Gitsn_Iso14827Subscription **)ptr;
	if (p) { Gitsn_Iso14827Subscription_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Subscription_dump(Gitsn_Iso14827Subscription *p, int tab);
// Gitsn_Iso14827Subscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationMgmt
typedef enum Gitsn_Iso14827PublicationMgmt
{
	Gitsn_Iso14827PublicationMgmt_temporarilySuspended,
	Gitsn_Iso14827PublicationMgmt_resume,
	Gitsn_Iso14827PublicationMgmt_terminateOther,
	Gitsn_Iso14827PublicationMgmt_terminateDataNoLongerAvailable,
	Gitsn_Iso14827PublicationMgmt_terminatePublicationsBeingRejected,
	Gitsn_Iso14827PublicationMgmt_terminatePendingShutdown,
	Gitsn_Iso14827PublicationMgmt_terminateProcessingMgmt,
	Gitsn_Iso14827PublicationMgmt_terminateBandwidthMgmt,
	Gitsn_Iso14827PublicationMgmt_terminateAccessDenied,
	Gitsn_Iso14827PublicationMgmt_unknownRequest,
	Gitsn_Iso14827PublicationMgmt_max
} Gitsn_Iso14827PublicationMgmt;

DZ1_CPPLINK str_t Gitsn_Iso14827PublicationMgmtStrA(Gitsn_Iso14827PublicationMgmt v);
DZ1_CPPLINK Gitsn_Iso14827PublicationMgmt Gitsn_Iso14827PublicationMgmtFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827PublicationMgmtStrW(Gitsn_Iso14827PublicationMgmt v);
DZ1_CPPLINK Gitsn_Iso14827PublicationMgmt Gitsn_Iso14827PublicationMgmtFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827PublicationMgmtStr Gitsn_Iso14827PublicationMgmtStrW
#define Gitsn_Iso14827PublicationMgmtFromStr Gitsn_Iso14827PublicationMgmtFromStrW
#else // UNICODE
#define Gitsn_Iso14827PublicationMgmtStr Gitsn_Iso14827PublicationMgmtStrA
#define Gitsn_Iso14827PublicationMgmtFromStr Gitsn_Iso14827PublicationMgmtFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827PublicationMgmtStr Gitsn_Iso14827PublicationMgmtStrA
#define Gitsn_Iso14827PublicationMgmtFromStr Gitsn_Iso14827PublicationMgmtFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublicationMgmt *Gitsn_Iso14827PublicationMgmt_new(Gitsn_Iso14827PublicationMgmt *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827PublicationMgmt *Gitsn_Iso14827PublicationMgmt_gen(Dz1Error *err) { Gitsn_Iso14827PublicationMgmt v = Gitsn_Iso14827PublicationMgmt_max; return Gitsn_Iso14827PublicationMgmt_new(&v, err); }
static __inline__ void Gitsn_Iso14827PublicationMgmt_del(Gitsn_Iso14827PublicationMgmt *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827PublicationMgmt_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827PublicationMgmt **p = (Gitsn_Iso14827PublicationMgmt **)ptr;
	if (p != NULL) { Gitsn_Iso14827PublicationMgmt_del(*p); *p = NULL; }
}
// Gitsn_Iso14827PublicationMgmt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationTypePresent
typedef enum Gitsn_Iso14827PublicationTypePresent
{
	Gitsn_Iso14827PublicationTypePresent_mgmt,
	Gitsn_Iso14827PublicationTypePresent_msg,
	Gitsn_Iso14827PublicationTypePresent_max
} Gitsn_Iso14827PublicationTypePresent;

DZ1_CPPLINK str_t Gitsn_Iso14827PublicationTypePresentStrA(Gitsn_Iso14827PublicationTypePresent v);
DZ1_CPPLINK Gitsn_Iso14827PublicationTypePresent Gitsn_Iso14827PublicationTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827PublicationTypePresentStrW(Gitsn_Iso14827PublicationTypePresent v);
DZ1_CPPLINK Gitsn_Iso14827PublicationTypePresent Gitsn_Iso14827PublicationTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827PublicationTypePresentStr Gitsn_Iso14827PublicationTypePresentStrW
#define Gitsn_Iso14827PublicationTypePresentFromStr Gitsn_Iso14827PublicationTypePresentFromStrW
#else // UNICODE
#define Gitsn_Iso14827PublicationTypePresentStr Gitsn_Iso14827PublicationTypePresentStrA
#define Gitsn_Iso14827PublicationTypePresentFromStr Gitsn_Iso14827PublicationTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827PublicationTypePresentStr Gitsn_Iso14827PublicationTypePresentStrA
#define Gitsn_Iso14827PublicationTypePresentFromStr Gitsn_Iso14827PublicationTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublicationTypePresent *Gitsn_Iso14827PublicationTypePresent_new(Gitsn_Iso14827PublicationTypePresent *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827PublicationTypePresent *Gitsn_Iso14827PublicationTypePresent_gen(Dz1Error *err) { Gitsn_Iso14827PublicationTypePresent v = Gitsn_Iso14827PublicationTypePresent_max; return Gitsn_Iso14827PublicationTypePresent_new(&v, err); }
#define Gitsn_Iso14827PublicationTypePresent_clone             Gitsn_Iso14827PublicationTypePresent_new
static __inline__ void Gitsn_Iso14827PublicationTypePresent_del(Gitsn_Iso14827PublicationTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827PublicationTypePresent_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827PublicationTypePresent **p = (Gitsn_Iso14827PublicationTypePresent **)ptr;
	if (p != NULL) { Gitsn_Iso14827PublicationTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationTypePresent_dump(Gitsn_Iso14827PublicationTypePresent *v, int tab);
// Gitsn_Iso14827PublicationTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationType
typedef struct Gitsn_Iso14827PublicationType
{
	Gitsn_Iso14827PublicationTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_Iso14827PublicationMgmt		 mgmt;
		Gitsn_Iso14827EndAppMsg				*msg;
	} x;
} Gitsn_Iso14827PublicationType;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublicationType *Gitsn_Iso14827PublicationType_new(Gitsn_Iso14827PublicationTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_Iso14827PublicationType *Gitsn_Iso14827PublicationType_gen(Dz1Error *err) { return Gitsn_Iso14827PublicationType_new(Gitsn_Iso14827PublicationTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_Iso14827PublicationType_copy(Gitsn_Iso14827PublicationType *dst, Gitsn_Iso14827PublicationType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublicationType *Gitsn_Iso14827PublicationType_clone(Gitsn_Iso14827PublicationType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationType_purge(Gitsn_Iso14827PublicationType *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationType_del(Gitsn_Iso14827PublicationType *p);
static __inline__ void Gitsn_Iso14827PublicationType_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827PublicationType **p = (Gitsn_Iso14827PublicationType **)ptr;
	if (p != NULL) { Gitsn_Iso14827PublicationType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationType_dump(Gitsn_Iso14827PublicationType *p, int tab);
// Gitsn_Iso14827PublicationType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationData
typedef struct Gitsn_Iso14827PublicationData
{
	u32_t								 subscriptionSerial;
	u32_t								 serial;
	bool_t								 isLated;
	Gitsn_Iso14827PublicationType		*type;
} Gitsn_Iso14827PublicationData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublicationData *Gitsn_Iso14827PublicationData_new(u32_t subscriptionSerial, 
																						 u32_t serial, 
																						 bool_t isLated, 
																						 Gitsn_Iso14827PublicationType *type, Dz1Error *err);
static __inline__ Gitsn_Iso14827PublicationData *Gitsn_Iso14827PublicationData_gen(Dz1Error *err) { return Gitsn_Iso14827PublicationData_new(0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827PublicationData_copy(Gitsn_Iso14827PublicationData *dst, Gitsn_Iso14827PublicationData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublicationData *Gitsn_Iso14827PublicationData_clone(Gitsn_Iso14827PublicationData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationData_purge(Gitsn_Iso14827PublicationData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationData_del(Gitsn_Iso14827PublicationData *p);
static __inline__ void Gitsn_Iso14827PublicationData_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827PublicationData **p = (Gitsn_Iso14827PublicationData **)ptr;
	if (p) { Gitsn_Iso14827PublicationData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationData_dump(Gitsn_Iso14827PublicationData *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Gitsn_Iso14827PublicationData_cmp(Gitsn_Iso14827PublicationData *a, Gitsn_Iso14827PublicationData *b); 
// Gitsn_Iso14827PublicationData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationDataList
typedef struct Gitsn_Iso14827PublicationDataList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_Iso14827PublicationDataList *p);
	Dz1Error (*travel)(struct Gitsn_Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Gitsn_Iso14827PublicationData *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Gitsn_Iso14827PublicationData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Gitsn_Iso14827PublicationData *entry), void *ptr);
	Gitsn_Iso14827PublicationData **(*get_array)(struct Gitsn_Iso14827PublicationDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_Iso14827PublicationDataList *p, Gitsn_Iso14827PublicationData *data);
	bool_t (*remove)(struct Gitsn_Iso14827PublicationDataList *p, Gitsn_Iso14827PublicationData *key);
	Gitsn_Iso14827PublicationData *(*extract)(struct Gitsn_Iso14827PublicationDataList *p, Gitsn_Iso14827PublicationData *key);
	Gitsn_Iso14827PublicationData *(*find)(struct Gitsn_Iso14827PublicationDataList *p, Gitsn_Iso14827PublicationData *key);
	Gitsn_Iso14827PublicationData *(*getHead)(struct Gitsn_Iso14827PublicationDataList *p);
	int (*cmp)(Gitsn_Iso14827PublicationData *a, Gitsn_Iso14827PublicationData *b);
} Gitsn_Iso14827PublicationDataList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublicationDataList *Gitsn_Iso14827PublicationDataList_new(Dz1Error *err);
static __inline__ Gitsn_Iso14827PublicationDataList *Gitsn_Iso14827PublicationDataList_gen(Dz1Error *err) { return Gitsn_Iso14827PublicationDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublicationDataList *Gitsn_Iso14827PublicationDataList_clone(Gitsn_Iso14827PublicationDataList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationDataList_purge(Gitsn_Iso14827PublicationDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationDataList_del(Gitsn_Iso14827PublicationDataList *p);
static __inline__ void Gitsn_Iso14827PublicationDataList_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827PublicationDataList **p = (Gitsn_Iso14827PublicationDataList **)ptr;
	if (p != NULL) { Gitsn_Iso14827PublicationDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublicationDataList_dump(Gitsn_Iso14827PublicationDataList *p, int tab);

// Gitsn_Iso14827PublicationDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublishFormatPresent
typedef enum Gitsn_Iso14827PublishFormatPresent
{
	Gitsn_Iso14827PublishFormatPresent_dataList,
	Gitsn_Iso14827PublishFormatPresent_filename,
	Gitsn_Iso14827PublishFormatPresent_max
} Gitsn_Iso14827PublishFormatPresent;

DZ1_CPPLINK str_t Gitsn_Iso14827PublishFormatPresentStrA(Gitsn_Iso14827PublishFormatPresent v);
DZ1_CPPLINK Gitsn_Iso14827PublishFormatPresent Gitsn_Iso14827PublishFormatPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827PublishFormatPresentStrW(Gitsn_Iso14827PublishFormatPresent v);
DZ1_CPPLINK Gitsn_Iso14827PublishFormatPresent Gitsn_Iso14827PublishFormatPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827PublishFormatPresentStr Gitsn_Iso14827PublishFormatPresentStrW
#define Gitsn_Iso14827PublishFormatPresentFromStr Gitsn_Iso14827PublishFormatPresentFromStrW
#else // UNICODE
#define Gitsn_Iso14827PublishFormatPresentStr Gitsn_Iso14827PublishFormatPresentStrA
#define Gitsn_Iso14827PublishFormatPresentFromStr Gitsn_Iso14827PublishFormatPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827PublishFormatPresentStr Gitsn_Iso14827PublishFormatPresentStrA
#define Gitsn_Iso14827PublishFormatPresentFromStr Gitsn_Iso14827PublishFormatPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublishFormatPresent *Gitsn_Iso14827PublishFormatPresent_new(Gitsn_Iso14827PublishFormatPresent *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827PublishFormatPresent *Gitsn_Iso14827PublishFormatPresent_gen(Dz1Error *err) { Gitsn_Iso14827PublishFormatPresent v = Gitsn_Iso14827PublishFormatPresent_max; return Gitsn_Iso14827PublishFormatPresent_new(&v, err); }
#define Gitsn_Iso14827PublishFormatPresent_clone             Gitsn_Iso14827PublishFormatPresent_new
static __inline__ void Gitsn_Iso14827PublishFormatPresent_del(Gitsn_Iso14827PublishFormatPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827PublishFormatPresent_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827PublishFormatPresent **p = (Gitsn_Iso14827PublishFormatPresent **)ptr;
	if (p != NULL) { Gitsn_Iso14827PublishFormatPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublishFormatPresent_dump(Gitsn_Iso14827PublishFormatPresent *v, int tab);
// Gitsn_Iso14827PublishFormatPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublishFormat
typedef struct Gitsn_Iso14827PublishFormat
{
	Gitsn_Iso14827PublishFormatPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_Iso14827PublicationDataList		*dataList;
		Dz1Str									 filename;
	} x;
} Gitsn_Iso14827PublishFormat;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublishFormat *Gitsn_Iso14827PublishFormat_new(Gitsn_Iso14827PublishFormatPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_Iso14827PublishFormat *Gitsn_Iso14827PublishFormat_gen(Dz1Error *err) { return Gitsn_Iso14827PublishFormat_new(Gitsn_Iso14827PublishFormatPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_Iso14827PublishFormat_copy(Gitsn_Iso14827PublishFormat *dst, Gitsn_Iso14827PublishFormat *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PublishFormat *Gitsn_Iso14827PublishFormat_clone(Gitsn_Iso14827PublishFormat *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublishFormat_purge(Gitsn_Iso14827PublishFormat *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublishFormat_del(Gitsn_Iso14827PublishFormat *p);
static __inline__ void Gitsn_Iso14827PublishFormat_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827PublishFormat **p = (Gitsn_Iso14827PublishFormat **)ptr;
	if (p != NULL) { Gitsn_Iso14827PublishFormat_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PublishFormat_dump(Gitsn_Iso14827PublishFormat *p, int tab);
// Gitsn_Iso14827PublishFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Publication
typedef struct Gitsn_Iso14827Publication
{
	bool_t							 guaranteed;
	Gitsn_Iso14827PublishFormat		*fmt;
} Gitsn_Iso14827Publication;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Publication *Gitsn_Iso14827Publication_new(bool_t guaranteed, 
																				 Gitsn_Iso14827PublishFormat *fmt, Dz1Error *err);
static __inline__ Gitsn_Iso14827Publication *Gitsn_Iso14827Publication_gen(Dz1Error *err) { return Gitsn_Iso14827Publication_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827Publication_copy(Gitsn_Iso14827Publication *dst, Gitsn_Iso14827Publication *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Publication *Gitsn_Iso14827Publication_clone(Gitsn_Iso14827Publication *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Publication_purge(Gitsn_Iso14827Publication *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Publication_del(Gitsn_Iso14827Publication *p);
static __inline__ void Gitsn_Iso14827Publication_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Publication **p = (Gitsn_Iso14827Publication **)ptr;
	if (p) { Gitsn_Iso14827Publication_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Publication_dump(Gitsn_Iso14827Publication *p, int tab);
// Gitsn_Iso14827Publication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TransferDone
typedef struct Gitsn_Iso14827TransferDone
{
	Dz1Str		filename;
	bool_t		isSuccess;
} Gitsn_Iso14827TransferDone;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827TransferDone *Gitsn_Iso14827TransferDone_new(Dz1Str filename, 
																				   bool_t isSuccess, Dz1Error *err);
static __inline__ Gitsn_Iso14827TransferDone *Gitsn_Iso14827TransferDone_gen(Dz1Error *err) { return Gitsn_Iso14827TransferDone_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827TransferDone_copy(Gitsn_Iso14827TransferDone *dst, Gitsn_Iso14827TransferDone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827TransferDone *Gitsn_Iso14827TransferDone_clone(Gitsn_Iso14827TransferDone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TransferDone_purge(Gitsn_Iso14827TransferDone *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TransferDone_del(Gitsn_Iso14827TransferDone *p);
static __inline__ void Gitsn_Iso14827TransferDone_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827TransferDone **p = (Gitsn_Iso14827TransferDone **)ptr;
	if (p) { Gitsn_Iso14827TransferDone_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827TransferDone_dump(Gitsn_Iso14827TransferDone *p, int tab);
// Gitsn_Iso14827TransferDone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827AcceptTypePresent
typedef enum Gitsn_Iso14827AcceptTypePresent
{
	Gitsn_Iso14827AcceptTypePresent_login,
	Gitsn_Iso14827AcceptTypePresent_singleSubscription,
	Gitsn_Iso14827AcceptTypePresent_registeredSubscription,
	Gitsn_Iso14827AcceptTypePresent_publication,
	Gitsn_Iso14827AcceptTypePresent_max
} Gitsn_Iso14827AcceptTypePresent;

DZ1_CPPLINK str_t Gitsn_Iso14827AcceptTypePresentStrA(Gitsn_Iso14827AcceptTypePresent v);
DZ1_CPPLINK Gitsn_Iso14827AcceptTypePresent Gitsn_Iso14827AcceptTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827AcceptTypePresentStrW(Gitsn_Iso14827AcceptTypePresent v);
DZ1_CPPLINK Gitsn_Iso14827AcceptTypePresent Gitsn_Iso14827AcceptTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827AcceptTypePresentStr Gitsn_Iso14827AcceptTypePresentStrW
#define Gitsn_Iso14827AcceptTypePresentFromStr Gitsn_Iso14827AcceptTypePresentFromStrW
#else // UNICODE
#define Gitsn_Iso14827AcceptTypePresentStr Gitsn_Iso14827AcceptTypePresentStrA
#define Gitsn_Iso14827AcceptTypePresentFromStr Gitsn_Iso14827AcceptTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827AcceptTypePresentStr Gitsn_Iso14827AcceptTypePresentStrA
#define Gitsn_Iso14827AcceptTypePresentFromStr Gitsn_Iso14827AcceptTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827AcceptTypePresent *Gitsn_Iso14827AcceptTypePresent_new(Gitsn_Iso14827AcceptTypePresent *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827AcceptTypePresent *Gitsn_Iso14827AcceptTypePresent_gen(Dz1Error *err) { Gitsn_Iso14827AcceptTypePresent v = Gitsn_Iso14827AcceptTypePresent_max; return Gitsn_Iso14827AcceptTypePresent_new(&v, err); }
#define Gitsn_Iso14827AcceptTypePresent_clone             Gitsn_Iso14827AcceptTypePresent_new
static __inline__ void Gitsn_Iso14827AcceptTypePresent_del(Gitsn_Iso14827AcceptTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827AcceptTypePresent_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827AcceptTypePresent **p = (Gitsn_Iso14827AcceptTypePresent **)ptr;
	if (p != NULL) { Gitsn_Iso14827AcceptTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827AcceptTypePresent_dump(Gitsn_Iso14827AcceptTypePresent *v, int tab);
// Gitsn_Iso14827AcceptTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827AcceptType
typedef struct Gitsn_Iso14827AcceptType
{
	Gitsn_Iso14827AcceptTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Str		 login;
		s32_t		*singleSubscription;
		u32_t		 registeredSubscription;
		s32_t		*publication;
	} x;
} Gitsn_Iso14827AcceptType;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827AcceptType *Gitsn_Iso14827AcceptType_new(Gitsn_Iso14827AcceptTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_Iso14827AcceptType *Gitsn_Iso14827AcceptType_gen(Dz1Error *err) { return Gitsn_Iso14827AcceptType_new(Gitsn_Iso14827AcceptTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_Iso14827AcceptType_copy(Gitsn_Iso14827AcceptType *dst, Gitsn_Iso14827AcceptType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827AcceptType *Gitsn_Iso14827AcceptType_clone(Gitsn_Iso14827AcceptType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827AcceptType_purge(Gitsn_Iso14827AcceptType *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827AcceptType_del(Gitsn_Iso14827AcceptType *p);
static __inline__ void Gitsn_Iso14827AcceptType_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827AcceptType **p = (Gitsn_Iso14827AcceptType **)ptr;
	if (p != NULL) { Gitsn_Iso14827AcceptType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827AcceptType_dump(Gitsn_Iso14827AcceptType *p, int tab);
// Gitsn_Iso14827AcceptType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Accept
typedef struct Gitsn_Iso14827Accept
{
	u32_t						 pktNbr;
	Gitsn_Iso14827AcceptType	*acceptType;
} Gitsn_Iso14827Accept;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Accept *Gitsn_Iso14827Accept_new(u32_t pktNbr, 
																	   Gitsn_Iso14827AcceptType *acceptType, Dz1Error *err);
static __inline__ Gitsn_Iso14827Accept *Gitsn_Iso14827Accept_gen(Dz1Error *err) { return Gitsn_Iso14827Accept_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827Accept_copy(Gitsn_Iso14827Accept *dst, Gitsn_Iso14827Accept *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Accept *Gitsn_Iso14827Accept_clone(Gitsn_Iso14827Accept *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Accept_purge(Gitsn_Iso14827Accept *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Accept_del(Gitsn_Iso14827Accept *p);
static __inline__ void Gitsn_Iso14827Accept_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Accept **p = (Gitsn_Iso14827Accept **)ptr;
	if (p) { Gitsn_Iso14827Accept_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Accept_dump(Gitsn_Iso14827Accept *p, int tab);
// Gitsn_Iso14827Accept
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectLogin
typedef enum Gitsn_Iso14827RejectLogin
{
	Gitsn_Iso14827RejectLogin_other,
	Gitsn_Iso14827RejectLogin_unknownDomainName,
	Gitsn_Iso14827RejectLogin_accessDenied,
	Gitsn_Iso14827RejectLogin_invalidPassword,
	Gitsn_Iso14827RejectLogin_timeoutTooSmall,
	Gitsn_Iso14827RejectLogin_timeoutTooLarge,
	Gitsn_Iso14827RejectLogin_heartbeatTooSmall,
	Gitsn_Iso14827RejectLogin_heartbeatTooLarge,
	Gitsn_Iso14827RejectLogin_sessionExist,
	Gitsn_Iso14827RejectLogin_maxSessionReached,
	Gitsn_Iso14827RejectLogin_max
} Gitsn_Iso14827RejectLogin;

DZ1_CPPLINK str_t Gitsn_Iso14827RejectLoginStrA(Gitsn_Iso14827RejectLogin v);
DZ1_CPPLINK Gitsn_Iso14827RejectLogin Gitsn_Iso14827RejectLoginFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827RejectLoginStrW(Gitsn_Iso14827RejectLogin v);
DZ1_CPPLINK Gitsn_Iso14827RejectLogin Gitsn_Iso14827RejectLoginFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827RejectLoginStr Gitsn_Iso14827RejectLoginStrW
#define Gitsn_Iso14827RejectLoginFromStr Gitsn_Iso14827RejectLoginFromStrW
#else // UNICODE
#define Gitsn_Iso14827RejectLoginStr Gitsn_Iso14827RejectLoginStrA
#define Gitsn_Iso14827RejectLoginFromStr Gitsn_Iso14827RejectLoginFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827RejectLoginStr Gitsn_Iso14827RejectLoginStrA
#define Gitsn_Iso14827RejectLoginFromStr Gitsn_Iso14827RejectLoginFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RejectLogin *Gitsn_Iso14827RejectLogin_new(Gitsn_Iso14827RejectLogin *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827RejectLogin *Gitsn_Iso14827RejectLogin_gen(Dz1Error *err) { Gitsn_Iso14827RejectLogin v = Gitsn_Iso14827RejectLogin_max; return Gitsn_Iso14827RejectLogin_new(&v, err); }
static __inline__ void Gitsn_Iso14827RejectLogin_del(Gitsn_Iso14827RejectLogin *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827RejectLogin_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RejectLogin **p = (Gitsn_Iso14827RejectLogin **)ptr;
	if (p != NULL) { Gitsn_Iso14827RejectLogin_del(*p); *p = NULL; }
}
// Gitsn_Iso14827RejectLogin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectSubscription
typedef enum Gitsn_Iso14827RejectSubscription
{
	Gitsn_Iso14827RejectSubscription_other,
	Gitsn_Iso14827RejectSubscription_unknownSubscriptionNbr,
	Gitsn_Iso14827RejectSubscription_invalidTimes,
	Gitsn_Iso14827RejectSubscription_frequencyTooSmall,
	Gitsn_Iso14827RejectSubscription_frequencyTooLarge,
	Gitsn_Iso14827RejectSubscription_invalidMode,
	Gitsn_Iso14827RejectSubscription_publishFormatNotSupported,
	Gitsn_Iso14827RejectSubscription_unknownSubscriptionMsgId,
	Gitsn_Iso14827RejectSubscription_invalidSubscriptionMsgId,
	Gitsn_Iso14827RejectSubscription_invalidSubscriptionContent,
	Gitsn_Iso14827RejectSubscription_max
} Gitsn_Iso14827RejectSubscription;

DZ1_CPPLINK str_t Gitsn_Iso14827RejectSubscriptionStrA(Gitsn_Iso14827RejectSubscription v);
DZ1_CPPLINK Gitsn_Iso14827RejectSubscription Gitsn_Iso14827RejectSubscriptionFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827RejectSubscriptionStrW(Gitsn_Iso14827RejectSubscription v);
DZ1_CPPLINK Gitsn_Iso14827RejectSubscription Gitsn_Iso14827RejectSubscriptionFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827RejectSubscriptionStr Gitsn_Iso14827RejectSubscriptionStrW
#define Gitsn_Iso14827RejectSubscriptionFromStr Gitsn_Iso14827RejectSubscriptionFromStrW
#else // UNICODE
#define Gitsn_Iso14827RejectSubscriptionStr Gitsn_Iso14827RejectSubscriptionStrA
#define Gitsn_Iso14827RejectSubscriptionFromStr Gitsn_Iso14827RejectSubscriptionFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827RejectSubscriptionStr Gitsn_Iso14827RejectSubscriptionStrA
#define Gitsn_Iso14827RejectSubscriptionFromStr Gitsn_Iso14827RejectSubscriptionFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RejectSubscription *Gitsn_Iso14827RejectSubscription_new(Gitsn_Iso14827RejectSubscription *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827RejectSubscription *Gitsn_Iso14827RejectSubscription_gen(Dz1Error *err) { Gitsn_Iso14827RejectSubscription v = Gitsn_Iso14827RejectSubscription_max; return Gitsn_Iso14827RejectSubscription_new(&v, err); }
static __inline__ void Gitsn_Iso14827RejectSubscription_del(Gitsn_Iso14827RejectSubscription *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827RejectSubscription_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RejectSubscription **p = (Gitsn_Iso14827RejectSubscription **)ptr;
	if (p != NULL) { Gitsn_Iso14827RejectSubscription_del(*p); *p = NULL; }
}
// Gitsn_Iso14827RejectSubscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectPublication
typedef enum Gitsn_Iso14827RejectPublication
{
	Gitsn_Iso14827RejectPublication_other,
	Gitsn_Iso14827RejectPublication_invalidPublishFormat,
	Gitsn_Iso14827RejectPublication_max
} Gitsn_Iso14827RejectPublication;

DZ1_CPPLINK str_t Gitsn_Iso14827RejectPublicationStrA(Gitsn_Iso14827RejectPublication v);
DZ1_CPPLINK Gitsn_Iso14827RejectPublication Gitsn_Iso14827RejectPublicationFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827RejectPublicationStrW(Gitsn_Iso14827RejectPublication v);
DZ1_CPPLINK Gitsn_Iso14827RejectPublication Gitsn_Iso14827RejectPublicationFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827RejectPublicationStr Gitsn_Iso14827RejectPublicationStrW
#define Gitsn_Iso14827RejectPublicationFromStr Gitsn_Iso14827RejectPublicationFromStrW
#else // UNICODE
#define Gitsn_Iso14827RejectPublicationStr Gitsn_Iso14827RejectPublicationStrA
#define Gitsn_Iso14827RejectPublicationFromStr Gitsn_Iso14827RejectPublicationFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827RejectPublicationStr Gitsn_Iso14827RejectPublicationStrA
#define Gitsn_Iso14827RejectPublicationFromStr Gitsn_Iso14827RejectPublicationFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RejectPublication *Gitsn_Iso14827RejectPublication_new(Gitsn_Iso14827RejectPublication *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827RejectPublication *Gitsn_Iso14827RejectPublication_gen(Dz1Error *err) { Gitsn_Iso14827RejectPublication v = Gitsn_Iso14827RejectPublication_max; return Gitsn_Iso14827RejectPublication_new(&v, err); }
static __inline__ void Gitsn_Iso14827RejectPublication_del(Gitsn_Iso14827RejectPublication *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827RejectPublication_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RejectPublication **p = (Gitsn_Iso14827RejectPublication **)ptr;
	if (p != NULL) { Gitsn_Iso14827RejectPublication_del(*p); *p = NULL; }
}
// Gitsn_Iso14827RejectPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectPubDataReason
typedef enum Gitsn_Iso14827RejectPubDataReason
{
	Gitsn_Iso14827RejectPubDataReason_other,
	Gitsn_Iso14827RejectPubDataReason_unknownSubscription,
	Gitsn_Iso14827RejectPubDataReason_unknownPublicationNbr,
	Gitsn_Iso14827RejectPubDataReason_unknownPublicationMsgId,
	Gitsn_Iso14827RejectPubDataReason_invalidPublicationMsgId,
	Gitsn_Iso14827RejectPubDataReason_invalidPublicationMsgContent,
	Gitsn_Iso14827RejectPubDataReason_repeatedPublicationNbr,
	Gitsn_Iso14827RejectPubDataReason_max
} Gitsn_Iso14827RejectPubDataReason;

DZ1_CPPLINK str_t Gitsn_Iso14827RejectPubDataReasonStrA(Gitsn_Iso14827RejectPubDataReason v);
DZ1_CPPLINK Gitsn_Iso14827RejectPubDataReason Gitsn_Iso14827RejectPubDataReasonFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827RejectPubDataReasonStrW(Gitsn_Iso14827RejectPubDataReason v);
DZ1_CPPLINK Gitsn_Iso14827RejectPubDataReason Gitsn_Iso14827RejectPubDataReasonFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827RejectPubDataReasonStr Gitsn_Iso14827RejectPubDataReasonStrW
#define Gitsn_Iso14827RejectPubDataReasonFromStr Gitsn_Iso14827RejectPubDataReasonFromStrW
#else // UNICODE
#define Gitsn_Iso14827RejectPubDataReasonStr Gitsn_Iso14827RejectPubDataReasonStrA
#define Gitsn_Iso14827RejectPubDataReasonFromStr Gitsn_Iso14827RejectPubDataReasonFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827RejectPubDataReasonStr Gitsn_Iso14827RejectPubDataReasonStrA
#define Gitsn_Iso14827RejectPubDataReasonFromStr Gitsn_Iso14827RejectPubDataReasonFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RejectPubDataReason *Gitsn_Iso14827RejectPubDataReason_new(Gitsn_Iso14827RejectPubDataReason *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827RejectPubDataReason *Gitsn_Iso14827RejectPubDataReason_gen(Dz1Error *err) { Gitsn_Iso14827RejectPubDataReason v = Gitsn_Iso14827RejectPubDataReason_max; return Gitsn_Iso14827RejectPubDataReason_new(&v, err); }
static __inline__ void Gitsn_Iso14827RejectPubDataReason_del(Gitsn_Iso14827RejectPubDataReason *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827RejectPubDataReason_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RejectPubDataReason **p = (Gitsn_Iso14827RejectPubDataReason **)ptr;
	if (p != NULL) { Gitsn_Iso14827RejectPubDataReason_del(*p); *p = NULL; }
}
// Gitsn_Iso14827RejectPubDataReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectPubData
typedef struct Gitsn_Iso14827RejectPubData
{
	u32_t									subSerial;
	u32_t									pubSerial;
	Gitsn_Iso14827RejectPubDataReason		reason;
} Gitsn_Iso14827RejectPubData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RejectPubData *Gitsn_Iso14827RejectPubData_new(u32_t subSerial, 
																					 u32_t pubSerial, 
																					 Gitsn_Iso14827RejectPubDataReason reason, Dz1Error *err);
static __inline__ Gitsn_Iso14827RejectPubData *Gitsn_Iso14827RejectPubData_gen(Dz1Error *err) { return Gitsn_Iso14827RejectPubData_new(0, 0, Gitsn_Iso14827RejectPubDataReason_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827RejectPubData_copy(Gitsn_Iso14827RejectPubData *dst, Gitsn_Iso14827RejectPubData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RejectPubData *Gitsn_Iso14827RejectPubData_clone(Gitsn_Iso14827RejectPubData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RejectPubData_purge(Gitsn_Iso14827RejectPubData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RejectPubData_del(Gitsn_Iso14827RejectPubData *p);
static __inline__ void Gitsn_Iso14827RejectPubData_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RejectPubData **p = (Gitsn_Iso14827RejectPubData **)ptr;
	if (p) { Gitsn_Iso14827RejectPubData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RejectPubData_dump(Gitsn_Iso14827RejectPubData *p, int tab);
// Gitsn_Iso14827RejectPubData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectTypePresent
typedef enum Gitsn_Iso14827RejectTypePresent
{
	Gitsn_Iso14827RejectTypePresent_login,
	Gitsn_Iso14827RejectTypePresent_subscription,
	Gitsn_Iso14827RejectTypePresent_publication,
	Gitsn_Iso14827RejectTypePresent_pubData,
	Gitsn_Iso14827RejectTypePresent_max
} Gitsn_Iso14827RejectTypePresent;

DZ1_CPPLINK str_t Gitsn_Iso14827RejectTypePresentStrA(Gitsn_Iso14827RejectTypePresent v);
DZ1_CPPLINK Gitsn_Iso14827RejectTypePresent Gitsn_Iso14827RejectTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827RejectTypePresentStrW(Gitsn_Iso14827RejectTypePresent v);
DZ1_CPPLINK Gitsn_Iso14827RejectTypePresent Gitsn_Iso14827RejectTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827RejectTypePresentStr Gitsn_Iso14827RejectTypePresentStrW
#define Gitsn_Iso14827RejectTypePresentFromStr Gitsn_Iso14827RejectTypePresentFromStrW
#else // UNICODE
#define Gitsn_Iso14827RejectTypePresentStr Gitsn_Iso14827RejectTypePresentStrA
#define Gitsn_Iso14827RejectTypePresentFromStr Gitsn_Iso14827RejectTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827RejectTypePresentStr Gitsn_Iso14827RejectTypePresentStrA
#define Gitsn_Iso14827RejectTypePresentFromStr Gitsn_Iso14827RejectTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RejectTypePresent *Gitsn_Iso14827RejectTypePresent_new(Gitsn_Iso14827RejectTypePresent *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827RejectTypePresent *Gitsn_Iso14827RejectTypePresent_gen(Dz1Error *err) { Gitsn_Iso14827RejectTypePresent v = Gitsn_Iso14827RejectTypePresent_max; return Gitsn_Iso14827RejectTypePresent_new(&v, err); }
#define Gitsn_Iso14827RejectTypePresent_clone             Gitsn_Iso14827RejectTypePresent_new
static __inline__ void Gitsn_Iso14827RejectTypePresent_del(Gitsn_Iso14827RejectTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827RejectTypePresent_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RejectTypePresent **p = (Gitsn_Iso14827RejectTypePresent **)ptr;
	if (p != NULL) { Gitsn_Iso14827RejectTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RejectTypePresent_dump(Gitsn_Iso14827RejectTypePresent *v, int tab);
// Gitsn_Iso14827RejectTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectType
typedef struct Gitsn_Iso14827RejectType
{
	Gitsn_Iso14827RejectTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_Iso14827RejectLogin			 login;
		Gitsn_Iso14827RejectSubscription	 subscription;
		Gitsn_Iso14827RejectPublication		 publication;
		Gitsn_Iso14827RejectPubData			*pubData;
	} x;
} Gitsn_Iso14827RejectType;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RejectType *Gitsn_Iso14827RejectType_new(Gitsn_Iso14827RejectTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_Iso14827RejectType *Gitsn_Iso14827RejectType_gen(Dz1Error *err) { return Gitsn_Iso14827RejectType_new(Gitsn_Iso14827RejectTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_Iso14827RejectType_copy(Gitsn_Iso14827RejectType *dst, Gitsn_Iso14827RejectType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827RejectType *Gitsn_Iso14827RejectType_clone(Gitsn_Iso14827RejectType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RejectType_purge(Gitsn_Iso14827RejectType *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RejectType_del(Gitsn_Iso14827RejectType *p);
static __inline__ void Gitsn_Iso14827RejectType_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827RejectType **p = (Gitsn_Iso14827RejectType **)ptr;
	if (p != NULL) { Gitsn_Iso14827RejectType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827RejectType_dump(Gitsn_Iso14827RejectType *p, int tab);
// Gitsn_Iso14827RejectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Reject
typedef struct Gitsn_Iso14827Reject
{
	u32_t								 pktNbr;
	Gitsn_Iso14827RejectType			*type;
	Gitsn_Iso14827SubscriptionType		*altReq;
} Gitsn_Iso14827Reject;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Reject *Gitsn_Iso14827Reject_new(u32_t pktNbr, 
																	   Gitsn_Iso14827RejectType *type, 
																	   Gitsn_Iso14827SubscriptionType *altReq, Dz1Error *err);
static __inline__ Gitsn_Iso14827Reject *Gitsn_Iso14827Reject_gen(Dz1Error *err) { return Gitsn_Iso14827Reject_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Iso14827Reject_copy(Gitsn_Iso14827Reject *dst, Gitsn_Iso14827Reject *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827Reject *Gitsn_Iso14827Reject_clone(Gitsn_Iso14827Reject *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Reject_purge(Gitsn_Iso14827Reject *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Reject_del(Gitsn_Iso14827Reject *p);
static __inline__ void Gitsn_Iso14827Reject_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827Reject **p = (Gitsn_Iso14827Reject **)ptr;
	if (p) { Gitsn_Iso14827Reject_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827Reject_dump(Gitsn_Iso14827Reject *p, int tab);
// Gitsn_Iso14827Reject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PDUsPresent
typedef enum Gitsn_Iso14827PDUsPresent
{
	Gitsn_Iso14827PDUsPresent_initiate,
	Gitsn_Iso14827PDUsPresent_login,
	Gitsn_Iso14827PDUsPresent_fred,
	Gitsn_Iso14827PDUsPresent_term,
	Gitsn_Iso14827PDUsPresent_logout,
	Gitsn_Iso14827PDUsPresent_subscription,
	Gitsn_Iso14827PDUsPresent_publication,
	Gitsn_Iso14827PDUsPresent_transferDone,
	Gitsn_Iso14827PDUsPresent_ack,
	Gitsn_Iso14827PDUsPresent_nak,
	Gitsn_Iso14827PDUsPresent_max
} Gitsn_Iso14827PDUsPresent;

DZ1_CPPLINK str_t Gitsn_Iso14827PDUsPresentStrA(Gitsn_Iso14827PDUsPresent v);
DZ1_CPPLINK Gitsn_Iso14827PDUsPresent Gitsn_Iso14827PDUsPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827PDUsPresentStrW(Gitsn_Iso14827PDUsPresent v);
DZ1_CPPLINK Gitsn_Iso14827PDUsPresent Gitsn_Iso14827PDUsPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827PDUsPresentStr Gitsn_Iso14827PDUsPresentStrW
#define Gitsn_Iso14827PDUsPresentFromStr Gitsn_Iso14827PDUsPresentFromStrW
#else // UNICODE
#define Gitsn_Iso14827PDUsPresentStr Gitsn_Iso14827PDUsPresentStrA
#define Gitsn_Iso14827PDUsPresentFromStr Gitsn_Iso14827PDUsPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827PDUsPresentStr Gitsn_Iso14827PDUsPresentStrA
#define Gitsn_Iso14827PDUsPresentFromStr Gitsn_Iso14827PDUsPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PDUsPresent *Gitsn_Iso14827PDUsPresent_new(Gitsn_Iso14827PDUsPresent *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827PDUsPresent *Gitsn_Iso14827PDUsPresent_gen(Dz1Error *err) { Gitsn_Iso14827PDUsPresent v = Gitsn_Iso14827PDUsPresent_max; return Gitsn_Iso14827PDUsPresent_new(&v, err); }
#define Gitsn_Iso14827PDUsPresent_clone             Gitsn_Iso14827PDUsPresent_new
static __inline__ void Gitsn_Iso14827PDUsPresent_del(Gitsn_Iso14827PDUsPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827PDUsPresent_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827PDUsPresent **p = (Gitsn_Iso14827PDUsPresent **)ptr;
	if (p != NULL) { Gitsn_Iso14827PDUsPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PDUsPresent_dump(Gitsn_Iso14827PDUsPresent *v, int tab);
// Gitsn_Iso14827PDUsPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PDUs
typedef struct Gitsn_Iso14827PDUs
{
	Gitsn_Iso14827PDUsPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_Iso14827Initiate			*initiate;
		Gitsn_Iso14827Login				*login;
		u32_t							 fred;
		Gitsn_Iso14827Terminate			 term;
		Gitsn_Iso14827Logout			 logout;
		Gitsn_Iso14827Subscription		*subscription;
		Gitsn_Iso14827Publication		*publication;
		Gitsn_Iso14827TransferDone		*transferDone;
		Gitsn_Iso14827Accept			*ack;
		Gitsn_Iso14827Reject			*nak;
	} x;
} Gitsn_Iso14827PDUs;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PDUs *Gitsn_Iso14827PDUs_new(Gitsn_Iso14827PDUsPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_Iso14827PDUs *Gitsn_Iso14827PDUs_gen(Dz1Error *err) { return Gitsn_Iso14827PDUs_new(Gitsn_Iso14827PDUsPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_Iso14827PDUs_copy(Gitsn_Iso14827PDUs *dst, Gitsn_Iso14827PDUs *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827PDUs *Gitsn_Iso14827PDUs_clone(Gitsn_Iso14827PDUs *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PDUs_purge(Gitsn_Iso14827PDUs *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PDUs_del(Gitsn_Iso14827PDUs *p);
static __inline__ void Gitsn_Iso14827PDUs_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827PDUs **p = (Gitsn_Iso14827PDUs **)ptr;
	if (p != NULL) { Gitsn_Iso14827PDUs_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827PDUs_dump(Gitsn_Iso14827PDUs *p, int tab);
// Gitsn_Iso14827PDUs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827C2CAuthMsg
typedef struct Gitsn_Iso14827C2CAuthMsg
{
	Dz1Str					 authInfo;
	u32_t					 pktNbr;
	s32_t					 priority;
	Gitsn_Iso14827HdrOpt	*hdrOpt;
	Gitsn_Iso14827PDUs		*pdu;
} Gitsn_Iso14827C2CAuthMsg;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827C2CAuthMsg *Gitsn_Iso14827C2CAuthMsg_new(Dz1Str authInfo, 
																			   u32_t pktNbr, 
																			   s32_t priority, 
																			   Gitsn_Iso14827HdrOpt *hdrOpt, 
																			   Gitsn_Iso14827PDUs *pdu, Dz1Error *err);
static __inline__ Gitsn_Iso14827C2CAuthMsg *Gitsn_Iso14827C2CAuthMsg_gen(Dz1Error *err) { return Gitsn_Iso14827C2CAuthMsg_new(NULL, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827C2CAuthMsg_purge(Gitsn_Iso14827C2CAuthMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827C2CAuthMsg_del(Gitsn_Iso14827C2CAuthMsg *p);
static __inline__ void Gitsn_Iso14827C2CAuthMsg_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827C2CAuthMsg **p = (Gitsn_Iso14827C2CAuthMsg **)ptr;
	if (p) { Gitsn_Iso14827C2CAuthMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827C2CAuthMsg_dump(Gitsn_Iso14827C2CAuthMsg *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Gitsn_Iso14827C2CAuthMsg_cmp(Gitsn_Iso14827C2CAuthMsg *a, Gitsn_Iso14827C2CAuthMsg *b); 
// Gitsn_Iso14827C2CAuthMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827DatexVersionNumber
typedef enum Gitsn_Iso14827DatexVersionNumber
{
	Gitsn_Iso14827DatexVersionNumber_experimental = 0,
	Gitsn_Iso14827DatexVersionNumber_version1 = 1,
	Gitsn_Iso14827DatexVersionNumber_max
} Gitsn_Iso14827DatexVersionNumber;

DZ1_CPPLINK str_t Gitsn_Iso14827DatexVersionNumberStrA(Gitsn_Iso14827DatexVersionNumber v);
DZ1_CPPLINK Gitsn_Iso14827DatexVersionNumber Gitsn_Iso14827DatexVersionNumberFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_Iso14827DatexVersionNumberStrW(Gitsn_Iso14827DatexVersionNumber v);
DZ1_CPPLINK Gitsn_Iso14827DatexVersionNumber Gitsn_Iso14827DatexVersionNumberFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_Iso14827DatexVersionNumberStr Gitsn_Iso14827DatexVersionNumberStrW
#define Gitsn_Iso14827DatexVersionNumberFromStr Gitsn_Iso14827DatexVersionNumberFromStrW
#else // UNICODE
#define Gitsn_Iso14827DatexVersionNumberStr Gitsn_Iso14827DatexVersionNumberStrA
#define Gitsn_Iso14827DatexVersionNumberFromStr Gitsn_Iso14827DatexVersionNumberFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_Iso14827DatexVersionNumberStr Gitsn_Iso14827DatexVersionNumberStrA
#define Gitsn_Iso14827DatexVersionNumberFromStr Gitsn_Iso14827DatexVersionNumberFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827DatexVersionNumber *Gitsn_Iso14827DatexVersionNumber_new(Gitsn_Iso14827DatexVersionNumber *src, Dz1Error *err);
static __inline__ Gitsn_Iso14827DatexVersionNumber *Gitsn_Iso14827DatexVersionNumber_gen(Dz1Error *err) { Gitsn_Iso14827DatexVersionNumber v = Gitsn_Iso14827DatexVersionNumber_max; return Gitsn_Iso14827DatexVersionNumber_new(&v, err); }
static __inline__ void Gitsn_Iso14827DatexVersionNumber_del(Gitsn_Iso14827DatexVersionNumber *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Iso14827DatexVersionNumber_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827DatexVersionNumber **p = (Gitsn_Iso14827DatexVersionNumber **)ptr;
	if (p != NULL) { Gitsn_Iso14827DatexVersionNumber_del(*p); *p = NULL; }
}
// Gitsn_Iso14827DatexVersionNumber
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827DatexDataPacket
typedef struct Gitsn_Iso14827DatexDataPacket
{
	Gitsn_Iso14827DatexVersionNumber	 version;
	Dz1Asn1OctetStr						*data;
	u16_t								 crc16;
} Gitsn_Iso14827DatexDataPacket;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Iso14827DatexDataPacket *Gitsn_Iso14827DatexDataPacket_new(Gitsn_Iso14827DatexVersionNumber version, 
																						 Dz1Asn1OctetStr *data, 
																						 u16_t crc16, Dz1Error *err);
static __inline__ Gitsn_Iso14827DatexDataPacket *Gitsn_Iso14827DatexDataPacket_gen(Dz1Error *err) { return Gitsn_Iso14827DatexDataPacket_new(Gitsn_Iso14827DatexVersionNumber_max, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827DatexDataPacket_purge(Gitsn_Iso14827DatexDataPacket *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827DatexDataPacket_del(Gitsn_Iso14827DatexDataPacket *p);
static __inline__ void Gitsn_Iso14827DatexDataPacket_delAndSetNull(void *ptr)
{
	Gitsn_Iso14827DatexDataPacket **p = (Gitsn_Iso14827DatexDataPacket **)ptr;
	if (p) { Gitsn_Iso14827DatexDataPacket_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Iso14827DatexDataPacket_dump(Gitsn_Iso14827DatexDataPacket *p, int tab);
// Gitsn_Iso14827DatexDataPacket
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypeRegPresent
typedef enum SubscribeSpecTypeRegPresent
{
	SubscribeSpecTypeRegPresent_continuous,
	SubscribeSpecTypeRegPresent_daily,
	SubscribeSpecTypeRegPresent_max
} SubscribeSpecTypeRegPresent;

DZ1_CPPLINK str_t SubscribeSpecTypeRegPresentStrA(SubscribeSpecTypeRegPresent v);
DZ1_CPPLINK SubscribeSpecTypeRegPresent SubscribeSpecTypeRegPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t SubscribeSpecTypeRegPresentStrW(SubscribeSpecTypeRegPresent v);
DZ1_CPPLINK SubscribeSpecTypeRegPresent SubscribeSpecTypeRegPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define SubscribeSpecTypeRegPresentStr SubscribeSpecTypeRegPresentStrW
#define SubscribeSpecTypeRegPresentFromStr SubscribeSpecTypeRegPresentFromStrW
#else // UNICODE
#define SubscribeSpecTypeRegPresentStr SubscribeSpecTypeRegPresentStrA
#define SubscribeSpecTypeRegPresentFromStr SubscribeSpecTypeRegPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define SubscribeSpecTypeRegPresentStr SubscribeSpecTypeRegPresentStrA
#define SubscribeSpecTypeRegPresentFromStr SubscribeSpecTypeRegPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecTypeRegPresent *SubscribeSpecTypeRegPresent_new(SubscribeSpecTypeRegPresent *src, Dz1Error *err);
static __inline__ SubscribeSpecTypeRegPresent *SubscribeSpecTypeRegPresent_gen(Dz1Error *err) { SubscribeSpecTypeRegPresent v = SubscribeSpecTypeRegPresent_max; return SubscribeSpecTypeRegPresent_new(&v, err); }
#define SubscribeSpecTypeRegPresent_clone             SubscribeSpecTypeRegPresent_new
static __inline__ void SubscribeSpecTypeRegPresent_del(SubscribeSpecTypeRegPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void SubscribeSpecTypeRegPresent_delAndSetNull(void *ptr)
{
	SubscribeSpecTypeRegPresent **p = (SubscribeSpecTypeRegPresent **)ptr;
	if (p != NULL) { SubscribeSpecTypeRegPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecTypeRegPresent_dump(SubscribeSpecTypeRegPresent *v, int tab);
// SubscribeSpecTypeRegPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypeReg
typedef struct SubscribeSpecTypeReg
{
	SubscribeSpecTypeRegPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827RegisteredContinuous	*continuous;
		Iso14827RegisteredDaily			*daily;
	} x;
} SubscribeSpecTypeReg;

DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecTypeReg *SubscribeSpecTypeReg_new(SubscribeSpecTypeRegPresent present, void *ptr, Dz1Error *err);
static __inline__ SubscribeSpecTypeReg *SubscribeSpecTypeReg_gen(Dz1Error *err) { return SubscribeSpecTypeReg_new(SubscribeSpecTypeRegPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  SubscribeSpecTypeReg_copy(SubscribeSpecTypeReg *dst, SubscribeSpecTypeReg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecTypeReg *SubscribeSpecTypeReg_clone(SubscribeSpecTypeReg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecTypeReg_purge(SubscribeSpecTypeReg *p);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecTypeReg_del(SubscribeSpecTypeReg *p);
static __inline__ void SubscribeSpecTypeReg_delAndSetNull(void *ptr)
{
	SubscribeSpecTypeReg **p = (SubscribeSpecTypeReg **)ptr;
	if (p != NULL) { SubscribeSpecTypeReg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecTypeReg_dump(SubscribeSpecTypeReg *p, int tab);
// SubscribeSpecTypeReg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypeRegistered
typedef struct SubscribeSpecTypeRegistered
{
	bool_t							 is_periodic;
	SubscribeSpecTypeReg			*reg_info;
	Iso14827SubscriptionCancel		 when_cancel;
} SubscribeSpecTypeRegistered;

DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecTypeRegistered *SubscribeSpecTypeRegistered_new(bool_t is_periodic, 
																					 SubscribeSpecTypeReg *reg_info, 
																					 Iso14827SubscriptionCancel when_cancel, Dz1Error *err);
static __inline__ SubscribeSpecTypeRegistered *SubscribeSpecTypeRegistered_gen(Dz1Error *err) { return SubscribeSpecTypeRegistered_new(0, NULL, Iso14827SubscriptionCancel_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SubscribeSpecTypeRegistered_copy(SubscribeSpecTypeRegistered *dst, SubscribeSpecTypeRegistered *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecTypeRegistered *SubscribeSpecTypeRegistered_clone(SubscribeSpecTypeRegistered *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecTypeRegistered_purge(SubscribeSpecTypeRegistered *p);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecTypeRegistered_del(SubscribeSpecTypeRegistered *p);
static __inline__ void SubscribeSpecTypeRegistered_delAndSetNull(void *ptr)
{
	SubscribeSpecTypeRegistered **p = (SubscribeSpecTypeRegistered **)ptr;
	if (p) { SubscribeSpecTypeRegistered_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecTypeRegistered_dump(SubscribeSpecTypeRegistered *p, int tab);
// SubscribeSpecTypeRegistered
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypePresent
typedef enum SubscribeSpecTypePresent
{
	SubscribeSpecTypePresent_single,
	SubscribeSpecTypePresent_registered,
	SubscribeSpecTypePresent_max
} SubscribeSpecTypePresent;

DZ1_CPPLINK str_t SubscribeSpecTypePresentStrA(SubscribeSpecTypePresent v);
DZ1_CPPLINK SubscribeSpecTypePresent SubscribeSpecTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t SubscribeSpecTypePresentStrW(SubscribeSpecTypePresent v);
DZ1_CPPLINK SubscribeSpecTypePresent SubscribeSpecTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define SubscribeSpecTypePresentStr SubscribeSpecTypePresentStrW
#define SubscribeSpecTypePresentFromStr SubscribeSpecTypePresentFromStrW
#else // UNICODE
#define SubscribeSpecTypePresentStr SubscribeSpecTypePresentStrA
#define SubscribeSpecTypePresentFromStr SubscribeSpecTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define SubscribeSpecTypePresentStr SubscribeSpecTypePresentStrA
#define SubscribeSpecTypePresentFromStr SubscribeSpecTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecTypePresent *SubscribeSpecTypePresent_new(SubscribeSpecTypePresent *src, Dz1Error *err);
static __inline__ SubscribeSpecTypePresent *SubscribeSpecTypePresent_gen(Dz1Error *err) { SubscribeSpecTypePresent v = SubscribeSpecTypePresent_max; return SubscribeSpecTypePresent_new(&v, err); }
#define SubscribeSpecTypePresent_clone             SubscribeSpecTypePresent_new
static __inline__ void SubscribeSpecTypePresent_del(SubscribeSpecTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void SubscribeSpecTypePresent_delAndSetNull(void *ptr)
{
	SubscribeSpecTypePresent **p = (SubscribeSpecTypePresent **)ptr;
	if (p != NULL) { SubscribeSpecTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecTypePresent_dump(SubscribeSpecTypePresent *v, int tab);
// SubscribeSpecTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecType
typedef struct SubscribeSpecType
{
	SubscribeSpecTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t							 single;
		SubscribeSpecTypeRegistered		*registered;
	} x;
} SubscribeSpecType;

DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecType *SubscribeSpecType_new(SubscribeSpecTypePresent present, void *ptr, Dz1Error *err);
static __inline__ SubscribeSpecType *SubscribeSpecType_gen(Dz1Error *err) { return SubscribeSpecType_new(SubscribeSpecTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  SubscribeSpecType_copy(SubscribeSpecType *dst, SubscribeSpecType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecType *SubscribeSpecType_clone(SubscribeSpecType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecType_purge(SubscribeSpecType *p);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecType_del(SubscribeSpecType *p);
static __inline__ void SubscribeSpecType_delAndSetNull(void *ptr)
{
	SubscribeSpecType **p = (SubscribeSpecType **)ptr;
	if (p != NULL) { SubscribeSpecType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecType_dump(SubscribeSpecType *p, int tab);
// SubscribeSpecType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecEntry
typedef struct SubscribeSpecEntry
{
	Dz1Str					 oid;
	u8_t					 priority;
	SubscribeSpecType		*type;
} SubscribeSpecEntry;

DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecEntry *SubscribeSpecEntry_new(Dz1Str oid, 
																   u8_t priority, 
																   SubscribeSpecType *type, Dz1Error *err);
static __inline__ SubscribeSpecEntry *SubscribeSpecEntry_gen(Dz1Error *err) { return SubscribeSpecEntry_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SubscribeSpecEntry_copy(SubscribeSpecEntry *dst, SubscribeSpecEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecEntry *SubscribeSpecEntry_clone(SubscribeSpecEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecEntry_purge(SubscribeSpecEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecEntry_del(SubscribeSpecEntry *p);
static __inline__ void SubscribeSpecEntry_delAndSetNull(void *ptr)
{
	SubscribeSpecEntry **p = (SubscribeSpecEntry **)ptr;
	if (p) { SubscribeSpecEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecEntry_dump(SubscribeSpecEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int SubscribeSpecEntry_cmp(SubscribeSpecEntry *a, SubscribeSpecEntry *b); 
// SubscribeSpecEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecList
typedef struct SubscribeSpecList
{
	void *storage;
	unsigned int (*count)(struct SubscribeSpecList *p);
	Dz1Error (*travel)(struct SubscribeSpecList *p, Dz1Error (*func)(void *ptr, SubscribeSpecEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct SubscribeSpecList *p, Dz1Error (*func)(void *ptr, SubscribeSpecEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct SubscribeSpecList *p, Dz1Error (*func)(void *ptr, SubscribeSpecEntry *entry), void *ptr);
	SubscribeSpecEntry **(*get_array)(struct SubscribeSpecList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct SubscribeSpecList *p, SubscribeSpecEntry *data);
	bool_t (*remove)(struct SubscribeSpecList *p, SubscribeSpecEntry *key);
	SubscribeSpecEntry *(*extract)(struct SubscribeSpecList *p, SubscribeSpecEntry *key);
	SubscribeSpecEntry *(*find)(struct SubscribeSpecList *p, SubscribeSpecEntry *key);
	SubscribeSpecEntry *(*getHead)(struct SubscribeSpecList *p);
	int (*cmp)(SubscribeSpecEntry *a, SubscribeSpecEntry *b);
} SubscribeSpecList;

DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecList *SubscribeSpecList_new(Dz1Error *err);
static __inline__ SubscribeSpecList *SubscribeSpecList_gen(Dz1Error *err) { return SubscribeSpecList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecList *SubscribeSpecList_clone(SubscribeSpecList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecList_purge(SubscribeSpecList *p);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecList_del(SubscribeSpecList *p);
static __inline__ void SubscribeSpecList_delAndSetNull(void *ptr)
{
	SubscribeSpecList **p = (SubscribeSpecList **)ptr;
	if (p != NULL) { SubscribeSpecList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecList_dump(SubscribeSpecList *p, int tab);

// SubscribeSpecList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConfTestSocketAddress
typedef struct ConfTestSocketAddress
{
	Dz1Str		addr;
	u16_t		port;
} ConfTestSocketAddress;

DZ1_CPPLINK DZ1_DLLPORT ConfTestSocketAddress *ConfTestSocketAddress_new(Dz1Str addr, 
																		 u16_t port, Dz1Error *err);
static __inline__ ConfTestSocketAddress *ConfTestSocketAddress_gen(Dz1Error *err) { return ConfTestSocketAddress_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ConfTestSocketAddress_copy(ConfTestSocketAddress *dst, ConfTestSocketAddress *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ConfTestSocketAddress *ConfTestSocketAddress_clone(ConfTestSocketAddress *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ConfTestSocketAddress_purge(ConfTestSocketAddress *p);
DZ1_CPPLINK DZ1_DLLPORT void ConfTestSocketAddress_del(ConfTestSocketAddress *p);
static __inline__ void ConfTestSocketAddress_delAndSetNull(void *ptr)
{
	ConfTestSocketAddress **p = (ConfTestSocketAddress **)ptr;
	if (p) { ConfTestSocketAddress_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ConfTestSocketAddress_dump(ConfTestSocketAddress *p, int tab);
// ConfTestSocketAddress
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestConnectionPresent
typedef enum Iso14827TestConnectionPresent
{
	Iso14827TestConnectionPresent_passive,
	Iso14827TestConnectionPresent_active,
	Iso14827TestConnectionPresent_max
} Iso14827TestConnectionPresent;

DZ1_CPPLINK str_t Iso14827TestConnectionPresentStrA(Iso14827TestConnectionPresent v);
DZ1_CPPLINK Iso14827TestConnectionPresent Iso14827TestConnectionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestConnectionPresentStrW(Iso14827TestConnectionPresent v);
DZ1_CPPLINK Iso14827TestConnectionPresent Iso14827TestConnectionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestConnectionPresentStr Iso14827TestConnectionPresentStrW
#define Iso14827TestConnectionPresentFromStr Iso14827TestConnectionPresentFromStrW
#else // UNICODE
#define Iso14827TestConnectionPresentStr Iso14827TestConnectionPresentStrA
#define Iso14827TestConnectionPresentFromStr Iso14827TestConnectionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestConnectionPresentStr Iso14827TestConnectionPresentStrA
#define Iso14827TestConnectionPresentFromStr Iso14827TestConnectionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestConnectionPresent *Iso14827TestConnectionPresent_new(Iso14827TestConnectionPresent *src, Dz1Error *err);
static __inline__ Iso14827TestConnectionPresent *Iso14827TestConnectionPresent_gen(Dz1Error *err) { Iso14827TestConnectionPresent v = Iso14827TestConnectionPresent_max; return Iso14827TestConnectionPresent_new(&v, err); }
#define Iso14827TestConnectionPresent_clone             Iso14827TestConnectionPresent_new
static __inline__ void Iso14827TestConnectionPresent_del(Iso14827TestConnectionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestConnectionPresent_delAndSetNull(void *ptr)
{
	Iso14827TestConnectionPresent **p = (Iso14827TestConnectionPresent **)ptr;
	if (p != NULL) { Iso14827TestConnectionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestConnectionPresent_dump(Iso14827TestConnectionPresent *v, int tab);
// Iso14827TestConnectionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestConnection
typedef struct Iso14827TestConnection
{
	Iso14827TestConnectionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u16_t						 passive;
		ConfTestSocketAddress		*active;
	} x;
} Iso14827TestConnection;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestConnection *Iso14827TestConnection_new(Iso14827TestConnectionPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827TestConnection *Iso14827TestConnection_gen(Dz1Error *err) { return Iso14827TestConnection_new(Iso14827TestConnectionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827TestConnection_copy(Iso14827TestConnection *dst, Iso14827TestConnection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestConnection *Iso14827TestConnection_clone(Iso14827TestConnection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestConnection_purge(Iso14827TestConnection *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestConnection_del(Iso14827TestConnection *p);
static __inline__ void Iso14827TestConnection_delAndSetNull(void *ptr)
{
	Iso14827TestConnection **p = (Iso14827TestConnection **)ptr;
	if (p != NULL) { Iso14827TestConnection_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestConnection_dump(Iso14827TestConnection *p, int tab);
// Iso14827TestConnection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2ConnectionPresent
typedef enum TechnicalRegulation2ConnectionPresent
{
	TechnicalRegulation2ConnectionPresent_passive,
	TechnicalRegulation2ConnectionPresent_active,
	TechnicalRegulation2ConnectionPresent_max
} TechnicalRegulation2ConnectionPresent;

DZ1_CPPLINK str_t TechnicalRegulation2ConnectionPresentStrA(TechnicalRegulation2ConnectionPresent v);
DZ1_CPPLINK TechnicalRegulation2ConnectionPresent TechnicalRegulation2ConnectionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TechnicalRegulation2ConnectionPresentStrW(TechnicalRegulation2ConnectionPresent v);
DZ1_CPPLINK TechnicalRegulation2ConnectionPresent TechnicalRegulation2ConnectionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define TechnicalRegulation2ConnectionPresentStr TechnicalRegulation2ConnectionPresentStrW
#define TechnicalRegulation2ConnectionPresentFromStr TechnicalRegulation2ConnectionPresentFromStrW
#else // UNICODE
#define TechnicalRegulation2ConnectionPresentStr TechnicalRegulation2ConnectionPresentStrA
#define TechnicalRegulation2ConnectionPresentFromStr TechnicalRegulation2ConnectionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TechnicalRegulation2ConnectionPresentStr TechnicalRegulation2ConnectionPresentStrA
#define TechnicalRegulation2ConnectionPresentFromStr TechnicalRegulation2ConnectionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2ConnectionPresent *TechnicalRegulation2ConnectionPresent_new(TechnicalRegulation2ConnectionPresent *src, Dz1Error *err);
static __inline__ TechnicalRegulation2ConnectionPresent *TechnicalRegulation2ConnectionPresent_gen(Dz1Error *err) { TechnicalRegulation2ConnectionPresent v = TechnicalRegulation2ConnectionPresent_max; return TechnicalRegulation2ConnectionPresent_new(&v, err); }
#define TechnicalRegulation2ConnectionPresent_clone             TechnicalRegulation2ConnectionPresent_new
static __inline__ void TechnicalRegulation2ConnectionPresent_del(TechnicalRegulation2ConnectionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TechnicalRegulation2ConnectionPresent_delAndSetNull(void *ptr)
{
	TechnicalRegulation2ConnectionPresent **p = (TechnicalRegulation2ConnectionPresent **)ptr;
	if (p != NULL) { TechnicalRegulation2ConnectionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2ConnectionPresent_dump(TechnicalRegulation2ConnectionPresent *v, int tab);
// TechnicalRegulation2ConnectionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2Connection
typedef struct TechnicalRegulation2Connection
{
	TechnicalRegulation2ConnectionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u16_t						 passive;
		ConfTestSocketAddress		*active;
	} x;
} TechnicalRegulation2Connection;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2Connection *TechnicalRegulation2Connection_new(TechnicalRegulation2ConnectionPresent present, void *ptr, Dz1Error *err);
static __inline__ TechnicalRegulation2Connection *TechnicalRegulation2Connection_gen(Dz1Error *err) { return TechnicalRegulation2Connection_new(TechnicalRegulation2ConnectionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  TechnicalRegulation2Connection_copy(TechnicalRegulation2Connection *dst, TechnicalRegulation2Connection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2Connection *TechnicalRegulation2Connection_clone(TechnicalRegulation2Connection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2Connection_purge(TechnicalRegulation2Connection *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2Connection_del(TechnicalRegulation2Connection *p);
static __inline__ void TechnicalRegulation2Connection_delAndSetNull(void *ptr)
{
	TechnicalRegulation2Connection **p = (TechnicalRegulation2Connection **)ptr;
	if (p != NULL) { TechnicalRegulation2Connection_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2Connection_dump(TechnicalRegulation2Connection *p, int tab);
// TechnicalRegulation2Connection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecDuo
typedef struct SubscribeSpecDuo
{
	SubscribeSpecEntry		*session1;
	SubscribeSpecEntry		*session2;
} SubscribeSpecDuo;

DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecDuo *SubscribeSpecDuo_new(SubscribeSpecEntry *session1, 
															   SubscribeSpecEntry *session2, Dz1Error *err);
static __inline__ SubscribeSpecDuo *SubscribeSpecDuo_gen(Dz1Error *err) { return SubscribeSpecDuo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t SubscribeSpecDuo_copy(SubscribeSpecDuo *dst, SubscribeSpecDuo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT SubscribeSpecDuo *SubscribeSpecDuo_clone(SubscribeSpecDuo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecDuo_purge(SubscribeSpecDuo *p);
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecDuo_del(SubscribeSpecDuo *p);
static __inline__ void SubscribeSpecDuo_delAndSetNull(void *ptr)
{
	SubscribeSpecDuo **p = (SubscribeSpecDuo **)ptr;
	if (p) { SubscribeSpecDuo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void SubscribeSpecDuo_dump(SubscribeSpecDuo *p, int tab);
// SubscribeSpecDuo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestAuth
typedef enum Iso14827TestAuth
{
	Iso14827TestAuth_success,
	Iso14827TestAuth_not_found,
	Iso14827TestAuth_invalid_passwd,
	Iso14827TestAuth_codec_not_support,
	Iso14827TestAuth_max
} Iso14827TestAuth;

DZ1_CPPLINK str_t Iso14827TestAuthStrA(Iso14827TestAuth v);
DZ1_CPPLINK Iso14827TestAuth Iso14827TestAuthFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestAuthStrW(Iso14827TestAuth v);
DZ1_CPPLINK Iso14827TestAuth Iso14827TestAuthFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestAuthStr Iso14827TestAuthStrW
#define Iso14827TestAuthFromStr Iso14827TestAuthFromStrW
#else // UNICODE
#define Iso14827TestAuthStr Iso14827TestAuthStrA
#define Iso14827TestAuthFromStr Iso14827TestAuthFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestAuthStr Iso14827TestAuthStrA
#define Iso14827TestAuthFromStr Iso14827TestAuthFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestAuth *Iso14827TestAuth_new(Iso14827TestAuth *src, Dz1Error *err);
static __inline__ Iso14827TestAuth *Iso14827TestAuth_gen(Dz1Error *err) { Iso14827TestAuth v = Iso14827TestAuth_max; return Iso14827TestAuth_new(&v, err); }
static __inline__ void Iso14827TestAuth_del(Iso14827TestAuth *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestAuth_delAndSetNull(void *ptr)
{
	Iso14827TestAuth **p = (Iso14827TestAuth **)ptr;
	if (p != NULL) { Iso14827TestAuth_del(*p); *p = NULL; }
}
// Iso14827TestAuth
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestUserAuthF
typedef Iso14827TestAuth (*Iso14827TestUserAuthF)(
					Dz1Asn1OctetStr *user, 
					Dz1Asn1OctetStr *path, 
					Dz1Asn1OctetStr *autninfo, 
					u8_t selctable_codec_bit, 
					Dz1Asn1Codec *ret_selected_codec);
// Iso14827TestUserAuthF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_centerClient2rse
typedef struct PolicePrj4ValidateSet_centerClient2rse
{
	bool_t		test_bsm;
} PolicePrj4ValidateSet_centerClient2rse;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_centerClient2rse *PolicePrj4ValidateSet_centerClient2rse_new(bool_t test_bsm, Dz1Error *err);
static __inline__ PolicePrj4ValidateSet_centerClient2rse *PolicePrj4ValidateSet_centerClient2rse_gen(Dz1Error *err) { return PolicePrj4ValidateSet_centerClient2rse_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4ValidateSet_centerClient2rse_copy(PolicePrj4ValidateSet_centerClient2rse *dst, PolicePrj4ValidateSet_centerClient2rse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_centerClient2rse *PolicePrj4ValidateSet_centerClient2rse_clone(PolicePrj4ValidateSet_centerClient2rse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_centerClient2rse_purge(PolicePrj4ValidateSet_centerClient2rse *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_centerClient2rse_del(PolicePrj4ValidateSet_centerClient2rse *p);
static __inline__ void PolicePrj4ValidateSet_centerClient2rse_delAndSetNull(void *ptr)
{
	PolicePrj4ValidateSet_centerClient2rse **p = (PolicePrj4ValidateSet_centerClient2rse **)ptr;
	if (p) { PolicePrj4ValidateSet_centerClient2rse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_centerClient2rse_dump(PolicePrj4ValidateSet_centerClient2rse *p, int tab);
// PolicePrj4ValidateSet_centerClient2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_rseServer2center
typedef struct PolicePrj4ValidateSet_rseServer2center
{
	bool_t		test_bsm;
} PolicePrj4ValidateSet_rseServer2center;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_rseServer2center *PolicePrj4ValidateSet_rseServer2center_new(bool_t test_bsm, Dz1Error *err);
static __inline__ PolicePrj4ValidateSet_rseServer2center *PolicePrj4ValidateSet_rseServer2center_gen(Dz1Error *err) { return PolicePrj4ValidateSet_rseServer2center_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4ValidateSet_rseServer2center_copy(PolicePrj4ValidateSet_rseServer2center *dst, PolicePrj4ValidateSet_rseServer2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_rseServer2center *PolicePrj4ValidateSet_rseServer2center_clone(PolicePrj4ValidateSet_rseServer2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_rseServer2center_purge(PolicePrj4ValidateSet_rseServer2center *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_rseServer2center_del(PolicePrj4ValidateSet_rseServer2center *p);
static __inline__ void PolicePrj4ValidateSet_rseServer2center_delAndSetNull(void *ptr)
{
	PolicePrj4ValidateSet_rseServer2center **p = (PolicePrj4ValidateSet_rseServer2center **)ptr;
	if (p) { PolicePrj4ValidateSet_rseServer2center_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_rseServer2center_dump(PolicePrj4ValidateSet_rseServer2center *p, int tab);
// PolicePrj4ValidateSet_rseServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_rseClient2center
typedef struct PolicePrj4ValidateSet_rseClient2center
{
	bool_t		test_map;
	bool_t		test_rsa;
	bool_t		test_tim;
} PolicePrj4ValidateSet_rseClient2center;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_rseClient2center *PolicePrj4ValidateSet_rseClient2center_new(bool_t test_map, 
																										   bool_t test_rsa, 
																										   bool_t test_tim, Dz1Error *err);
static __inline__ PolicePrj4ValidateSet_rseClient2center *PolicePrj4ValidateSet_rseClient2center_gen(Dz1Error *err) { return PolicePrj4ValidateSet_rseClient2center_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4ValidateSet_rseClient2center_copy(PolicePrj4ValidateSet_rseClient2center *dst, PolicePrj4ValidateSet_rseClient2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_rseClient2center *PolicePrj4ValidateSet_rseClient2center_clone(PolicePrj4ValidateSet_rseClient2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_rseClient2center_purge(PolicePrj4ValidateSet_rseClient2center *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_rseClient2center_del(PolicePrj4ValidateSet_rseClient2center *p);
static __inline__ void PolicePrj4ValidateSet_rseClient2center_delAndSetNull(void *ptr)
{
	PolicePrj4ValidateSet_rseClient2center **p = (PolicePrj4ValidateSet_rseClient2center **)ptr;
	if (p) { PolicePrj4ValidateSet_rseClient2center_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_rseClient2center_dump(PolicePrj4ValidateSet_rseClient2center *p, int tab);
// PolicePrj4ValidateSet_rseClient2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_centerServer2rse
typedef struct PolicePrj4ValidateSet_centerServer2rse
{
	bool_t		test_map;
	bool_t		test_rsa;
	bool_t		test_tim;
} PolicePrj4ValidateSet_centerServer2rse;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_centerServer2rse *PolicePrj4ValidateSet_centerServer2rse_new(bool_t test_map, 
																										   bool_t test_rsa, 
																										   bool_t test_tim, Dz1Error *err);
static __inline__ PolicePrj4ValidateSet_centerServer2rse *PolicePrj4ValidateSet_centerServer2rse_gen(Dz1Error *err) { return PolicePrj4ValidateSet_centerServer2rse_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4ValidateSet_centerServer2rse_copy(PolicePrj4ValidateSet_centerServer2rse *dst, PolicePrj4ValidateSet_centerServer2rse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_centerServer2rse *PolicePrj4ValidateSet_centerServer2rse_clone(PolicePrj4ValidateSet_centerServer2rse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_centerServer2rse_purge(PolicePrj4ValidateSet_centerServer2rse *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_centerServer2rse_del(PolicePrj4ValidateSet_centerServer2rse *p);
static __inline__ void PolicePrj4ValidateSet_centerServer2rse_delAndSetNull(void *ptr)
{
	PolicePrj4ValidateSet_centerServer2rse **p = (PolicePrj4ValidateSet_centerServer2rse **)ptr;
	if (p) { PolicePrj4ValidateSet_centerServer2rse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_centerServer2rse_dump(PolicePrj4ValidateSet_centerServer2rse *p, int tab);
// PolicePrj4ValidateSet_centerServer2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_signalserverServer2center
typedef struct PolicePrj4ValidateSet_signalserverServer2center
{
	bool_t		test_spat;
	bool_t		test_tls;
} PolicePrj4ValidateSet_signalserverServer2center;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_signalserverServer2center *PolicePrj4ValidateSet_signalserverServer2center_new(bool_t test_spat, 
																															 bool_t test_tls, Dz1Error *err);
static __inline__ PolicePrj4ValidateSet_signalserverServer2center *PolicePrj4ValidateSet_signalserverServer2center_gen(Dz1Error *err) { return PolicePrj4ValidateSet_signalserverServer2center_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4ValidateSet_signalserverServer2center_copy(PolicePrj4ValidateSet_signalserverServer2center *dst, PolicePrj4ValidateSet_signalserverServer2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4ValidateSet_signalserverServer2center *PolicePrj4ValidateSet_signalserverServer2center_clone(PolicePrj4ValidateSet_signalserverServer2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_signalserverServer2center_purge(PolicePrj4ValidateSet_signalserverServer2center *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_signalserverServer2center_del(PolicePrj4ValidateSet_signalserverServer2center *p);
static __inline__ void PolicePrj4ValidateSet_signalserverServer2center_delAndSetNull(void *ptr)
{
	PolicePrj4ValidateSet_signalserverServer2center **p = (PolicePrj4ValidateSet_signalserverServer2center **)ptr;
	if (p) { PolicePrj4ValidateSet_signalserverServer2center_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4ValidateSet_signalserverServer2center_dump(PolicePrj4ValidateSet_signalserverServer2center *p, int tab);
// PolicePrj4ValidateSet_signalserverServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3ValidateSet_c2cClient
typedef struct ITSK00100_3ValidateSet_c2cClient
{
	bool_t		test_pub_incident_detection_info;
	bool_t		test_pub_incident_termination_info;
	bool_t		test_pub_incident_detection_video_file_info_provide;
	bool_t		test_pub_control_state_info;
	bool_t		test_pub_sensor_state_info;
	bool_t		test_pub_moving_object;
} ITSK00100_3ValidateSet_c2cClient;

DZ1_CPPLINK DZ1_DLLPORT ITSK00100_3ValidateSet_c2cClient *ITSK00100_3ValidateSet_c2cClient_new(bool_t test_pub_incident_detection_info, 
																							   bool_t test_pub_incident_termination_info, 
																							   bool_t test_pub_incident_detection_video_file_info_provide, 
																							   bool_t test_pub_control_state_info, 
																							   bool_t test_pub_sensor_state_info, 
																							   bool_t test_pub_moving_object, Dz1Error *err);
static __inline__ ITSK00100_3ValidateSet_c2cClient *ITSK00100_3ValidateSet_c2cClient_gen(Dz1Error *err) { return ITSK00100_3ValidateSet_c2cClient_new(0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00100_3ValidateSet_c2cClient_copy(ITSK00100_3ValidateSet_c2cClient *dst, ITSK00100_3ValidateSet_c2cClient *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00100_3ValidateSet_c2cClient *ITSK00100_3ValidateSet_c2cClient_clone(ITSK00100_3ValidateSet_c2cClient *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3ValidateSet_c2cClient_purge(ITSK00100_3ValidateSet_c2cClient *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3ValidateSet_c2cClient_del(ITSK00100_3ValidateSet_c2cClient *p);
static __inline__ void ITSK00100_3ValidateSet_c2cClient_delAndSetNull(void *ptr)
{
	ITSK00100_3ValidateSet_c2cClient **p = (ITSK00100_3ValidateSet_c2cClient **)ptr;
	if (p) { ITSK00100_3ValidateSet_c2cClient_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3ValidateSet_c2cClient_dump(ITSK00100_3ValidateSet_c2cClient *p, int tab);
// ITSK00100_3ValidateSet_c2cClient
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3ValidateSet_c2cServer
typedef struct ITSK00100_3ValidateSet_c2cServer
{
	bool_t		test_pub_incident_detection_info;
	bool_t		test_pub_incident_termination_info;
	bool_t		test_pub_incident_detection_video_file_info_provide;
	bool_t		test_pub_control_state_info;
	bool_t		test_pub_sensor_state_info;
	bool_t		test_pub_moving_object;
} ITSK00100_3ValidateSet_c2cServer;

DZ1_CPPLINK DZ1_DLLPORT ITSK00100_3ValidateSet_c2cServer *ITSK00100_3ValidateSet_c2cServer_new(bool_t test_pub_incident_detection_info, 
																							   bool_t test_pub_incident_termination_info, 
																							   bool_t test_pub_incident_detection_video_file_info_provide, 
																							   bool_t test_pub_control_state_info, 
																							   bool_t test_pub_sensor_state_info, 
																							   bool_t test_pub_moving_object, Dz1Error *err);
static __inline__ ITSK00100_3ValidateSet_c2cServer *ITSK00100_3ValidateSet_c2cServer_gen(Dz1Error *err) { return ITSK00100_3ValidateSet_c2cServer_new(0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00100_3ValidateSet_c2cServer_copy(ITSK00100_3ValidateSet_c2cServer *dst, ITSK00100_3ValidateSet_c2cServer *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00100_3ValidateSet_c2cServer *ITSK00100_3ValidateSet_c2cServer_clone(ITSK00100_3ValidateSet_c2cServer *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3ValidateSet_c2cServer_purge(ITSK00100_3ValidateSet_c2cServer *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3ValidateSet_c2cServer_del(ITSK00100_3ValidateSet_c2cServer *p);
static __inline__ void ITSK00100_3ValidateSet_c2cServer_delAndSetNull(void *ptr)
{
	ITSK00100_3ValidateSet_c2cServer **p = (ITSK00100_3ValidateSet_c2cServer **)ptr;
	if (p) { ITSK00100_3ValidateSet_c2cServer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3ValidateSet_c2cServer_dump(ITSK00100_3ValidateSet_c2cServer *p, int tab);
// ITSK00100_3ValidateSet_c2cServer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1ValidateSet_clientRole1
typedef struct TechnicalRegulation1ValidateSet_clientRole1
{
	bool_t		test_pub_current_link_state;
	bool_t		test_pub_event_identity;
	bool_t		test_pub_incident_identity;
	bool_t		test_pub_incident_conditions;
	bool_t		test_pub_roadway_surface_status;
	bool_t		test_pub_weather_information;
	bool_t		test_pub_link_roadway_geometry;
	bool_t		test_pub_probe_vehicle_detection;
	bool_t		test_pub_detector_collection;
	bool_t		test_pub_extention_comm_pdu;
} TechnicalRegulation1ValidateSet_clientRole1;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1ValidateSet_clientRole1 *TechnicalRegulation1ValidateSet_clientRole1_new(bool_t test_pub_current_link_state, 
																													 bool_t test_pub_event_identity, 
																													 bool_t test_pub_incident_identity, 
																													 bool_t test_pub_incident_conditions, 
																													 bool_t test_pub_roadway_surface_status, 
																													 bool_t test_pub_weather_information, 
																													 bool_t test_pub_link_roadway_geometry, 
																													 bool_t test_pub_probe_vehicle_detection, 
																													 bool_t test_pub_detector_collection, 
																													 bool_t test_pub_extention_comm_pdu, Dz1Error *err);
static __inline__ TechnicalRegulation1ValidateSet_clientRole1 *TechnicalRegulation1ValidateSet_clientRole1_gen(Dz1Error *err) { return TechnicalRegulation1ValidateSet_clientRole1_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulation1ValidateSet_clientRole1_copy(TechnicalRegulation1ValidateSet_clientRole1 *dst, TechnicalRegulation1ValidateSet_clientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1ValidateSet_clientRole1 *TechnicalRegulation1ValidateSet_clientRole1_clone(TechnicalRegulation1ValidateSet_clientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1ValidateSet_clientRole1_purge(TechnicalRegulation1ValidateSet_clientRole1 *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1ValidateSet_clientRole1_del(TechnicalRegulation1ValidateSet_clientRole1 *p);
static __inline__ void TechnicalRegulation1ValidateSet_clientRole1_delAndSetNull(void *ptr)
{
	TechnicalRegulation1ValidateSet_clientRole1 **p = (TechnicalRegulation1ValidateSet_clientRole1 **)ptr;
	if (p) { TechnicalRegulation1ValidateSet_clientRole1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1ValidateSet_clientRole1_dump(TechnicalRegulation1ValidateSet_clientRole1 *p, int tab);
// TechnicalRegulation1ValidateSet_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1ValidateSet_serverRole1
typedef struct TechnicalRegulation1ValidateSet_serverRole1
{
	bool_t		test_sub_current_link_state;
	bool_t		test_sub_event_identity;
	bool_t		test_sub_incident_identity;
	bool_t		test_sub_incident_conditions;
	bool_t		test_sub_roadway_surface_status;
	bool_t		test_sub_weather_information;
	bool_t		test_sub_link_roadway_geometry;
	bool_t		test_sub_probe_vehicle_detection;
	bool_t		test_sub_detector_collection;
	bool_t		test_sub_extention_comm_pdu;
} TechnicalRegulation1ValidateSet_serverRole1;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1ValidateSet_serverRole1 *TechnicalRegulation1ValidateSet_serverRole1_new(bool_t test_sub_current_link_state, 
																													 bool_t test_sub_event_identity, 
																													 bool_t test_sub_incident_identity, 
																													 bool_t test_sub_incident_conditions, 
																													 bool_t test_sub_roadway_surface_status, 
																													 bool_t test_sub_weather_information, 
																													 bool_t test_sub_link_roadway_geometry, 
																													 bool_t test_sub_probe_vehicle_detection, 
																													 bool_t test_sub_detector_collection, 
																													 bool_t test_sub_extention_comm_pdu, Dz1Error *err);
static __inline__ TechnicalRegulation1ValidateSet_serverRole1 *TechnicalRegulation1ValidateSet_serverRole1_gen(Dz1Error *err) { return TechnicalRegulation1ValidateSet_serverRole1_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulation1ValidateSet_serverRole1_copy(TechnicalRegulation1ValidateSet_serverRole1 *dst, TechnicalRegulation1ValidateSet_serverRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1ValidateSet_serverRole1 *TechnicalRegulation1ValidateSet_serverRole1_clone(TechnicalRegulation1ValidateSet_serverRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1ValidateSet_serverRole1_purge(TechnicalRegulation1ValidateSet_serverRole1 *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1ValidateSet_serverRole1_del(TechnicalRegulation1ValidateSet_serverRole1 *p);
static __inline__ void TechnicalRegulation1ValidateSet_serverRole1_delAndSetNull(void *ptr)
{
	TechnicalRegulation1ValidateSet_serverRole1 **p = (TechnicalRegulation1ValidateSet_serverRole1 **)ptr;
	if (p) { TechnicalRegulation1ValidateSet_serverRole1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1ValidateSet_serverRole1_dump(TechnicalRegulation1ValidateSet_serverRole1 *p, int tab);
// TechnicalRegulation1ValidateSet_serverRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2ValidateSet_clientRole1
typedef struct TechnicalRegulation2ValidateSet_clientRole1
{
	bool_t		test_pub_comm_tx_pdu;
	bool_t		test_pub_comm_rx_pdu;
} TechnicalRegulation2ValidateSet_clientRole1;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2ValidateSet_clientRole1 *TechnicalRegulation2ValidateSet_clientRole1_new(bool_t test_pub_comm_tx_pdu, 
																													 bool_t test_pub_comm_rx_pdu, Dz1Error *err);
static __inline__ TechnicalRegulation2ValidateSet_clientRole1 *TechnicalRegulation2ValidateSet_clientRole1_gen(Dz1Error *err) { return TechnicalRegulation2ValidateSet_clientRole1_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulation2ValidateSet_clientRole1_copy(TechnicalRegulation2ValidateSet_clientRole1 *dst, TechnicalRegulation2ValidateSet_clientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2ValidateSet_clientRole1 *TechnicalRegulation2ValidateSet_clientRole1_clone(TechnicalRegulation2ValidateSet_clientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2ValidateSet_clientRole1_purge(TechnicalRegulation2ValidateSet_clientRole1 *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2ValidateSet_clientRole1_del(TechnicalRegulation2ValidateSet_clientRole1 *p);
static __inline__ void TechnicalRegulation2ValidateSet_clientRole1_delAndSetNull(void *ptr)
{
	TechnicalRegulation2ValidateSet_clientRole1 **p = (TechnicalRegulation2ValidateSet_clientRole1 **)ptr;
	if (p) { TechnicalRegulation2ValidateSet_clientRole1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2ValidateSet_clientRole1_dump(TechnicalRegulation2ValidateSet_clientRole1 *p, int tab);
// TechnicalRegulation2ValidateSet_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2ValidateSet_serverRole1
typedef struct TechnicalRegulation2ValidateSet_serverRole1
{
	bool_t		test_pub_comm_tx_pdu;
	bool_t		test_pub_comm_rx_pdu;
} TechnicalRegulation2ValidateSet_serverRole1;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2ValidateSet_serverRole1 *TechnicalRegulation2ValidateSet_serverRole1_new(bool_t test_pub_comm_tx_pdu, 
																													 bool_t test_pub_comm_rx_pdu, Dz1Error *err);
static __inline__ TechnicalRegulation2ValidateSet_serverRole1 *TechnicalRegulation2ValidateSet_serverRole1_gen(Dz1Error *err) { return TechnicalRegulation2ValidateSet_serverRole1_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulation2ValidateSet_serverRole1_copy(TechnicalRegulation2ValidateSet_serverRole1 *dst, TechnicalRegulation2ValidateSet_serverRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2ValidateSet_serverRole1 *TechnicalRegulation2ValidateSet_serverRole1_clone(TechnicalRegulation2ValidateSet_serverRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2ValidateSet_serverRole1_purge(TechnicalRegulation2ValidateSet_serverRole1 *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2ValidateSet_serverRole1_del(TechnicalRegulation2ValidateSet_serverRole1 *p);
static __inline__ void TechnicalRegulation2ValidateSet_serverRole1_delAndSetNull(void *ptr)
{
	TechnicalRegulation2ValidateSet_serverRole1 **p = (TechnicalRegulation2ValidateSet_serverRole1 **)ptr;
	if (p) { TechnicalRegulation2ValidateSet_serverRole1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2ValidateSet_serverRole1_dump(TechnicalRegulation2ValidateSet_serverRole1 *p, int tab);
// TechnicalRegulation2ValidateSet_serverRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestValidateSetPresent
typedef enum Iso14827TestValidateSetPresent
{
	Iso14827TestValidateSetPresent_centerClient2rse,
	Iso14827TestValidateSetPresent_rseServer2center,
	Iso14827TestValidateSetPresent_rseClient2center,
	Iso14827TestValidateSetPresent_centerServer2rse,
	Iso14827TestValidateSetPresent_signalserverServer2center,
	Iso14827TestValidateSetPresent_itsk00100_3c2cClient,
	Iso14827TestValidateSetPresent_itsk00100_3c2cServer,
	Iso14827TestValidateSetPresent_technical_regulation1_clientRole1,
	Iso14827TestValidateSetPresent_technical_regulation1_serverRole1,
	Iso14827TestValidateSetPresent_technical_regulation2_clientRole1,
	Iso14827TestValidateSetPresent_technical_regulation2_serverRole1,
	Iso14827TestValidateSetPresent_max
} Iso14827TestValidateSetPresent;

DZ1_CPPLINK str_t Iso14827TestValidateSetPresentStrA(Iso14827TestValidateSetPresent v);
DZ1_CPPLINK Iso14827TestValidateSetPresent Iso14827TestValidateSetPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestValidateSetPresentStrW(Iso14827TestValidateSetPresent v);
DZ1_CPPLINK Iso14827TestValidateSetPresent Iso14827TestValidateSetPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestValidateSetPresentStr Iso14827TestValidateSetPresentStrW
#define Iso14827TestValidateSetPresentFromStr Iso14827TestValidateSetPresentFromStrW
#else // UNICODE
#define Iso14827TestValidateSetPresentStr Iso14827TestValidateSetPresentStrA
#define Iso14827TestValidateSetPresentFromStr Iso14827TestValidateSetPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestValidateSetPresentStr Iso14827TestValidateSetPresentStrA
#define Iso14827TestValidateSetPresentFromStr Iso14827TestValidateSetPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestValidateSetPresent *Iso14827TestValidateSetPresent_new(Iso14827TestValidateSetPresent *src, Dz1Error *err);
static __inline__ Iso14827TestValidateSetPresent *Iso14827TestValidateSetPresent_gen(Dz1Error *err) { Iso14827TestValidateSetPresent v = Iso14827TestValidateSetPresent_max; return Iso14827TestValidateSetPresent_new(&v, err); }
#define Iso14827TestValidateSetPresent_clone             Iso14827TestValidateSetPresent_new
static __inline__ void Iso14827TestValidateSetPresent_del(Iso14827TestValidateSetPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestValidateSetPresent_delAndSetNull(void *ptr)
{
	Iso14827TestValidateSetPresent **p = (Iso14827TestValidateSetPresent **)ptr;
	if (p != NULL) { Iso14827TestValidateSetPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateSetPresent_dump(Iso14827TestValidateSetPresent *v, int tab);
// Iso14827TestValidateSetPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestValidateSet
typedef struct Iso14827TestValidateSet
{
	Iso14827TestValidateSetPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		PolicePrj4ValidateSet_centerClient2rse				*centerClient2rse;
		PolicePrj4ValidateSet_rseServer2center				*rseServer2center;
		PolicePrj4ValidateSet_rseClient2center				*rseClient2center;
		PolicePrj4ValidateSet_centerServer2rse				*centerServer2rse;
		PolicePrj4ValidateSet_signalserverServer2center		*signalserverServer2center;
		ITSK00100_3ValidateSet_c2cClient					*itsk00100_3c2cClient;
		ITSK00100_3ValidateSet_c2cServer					*itsk00100_3c2cServer;
		TechnicalRegulation1ValidateSet_clientRole1			*technical_regulation1_clientRole1;
		TechnicalRegulation1ValidateSet_serverRole1			*technical_regulation1_serverRole1;
		TechnicalRegulation2ValidateSet_clientRole1			*technical_regulation2_clientRole1;
		TechnicalRegulation2ValidateSet_serverRole1			*technical_regulation2_serverRole1;
	} x;
} Iso14827TestValidateSet;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestValidateSet *Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827TestValidateSet *Iso14827TestValidateSet_gen(Dz1Error *err) { return Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827TestValidateSet_copy(Iso14827TestValidateSet *dst, Iso14827TestValidateSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestValidateSet *Iso14827TestValidateSet_clone(Iso14827TestValidateSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateSet_purge(Iso14827TestValidateSet *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateSet_del(Iso14827TestValidateSet *p);
static __inline__ void Iso14827TestValidateSet_delAndSetNull(void *ptr)
{
	Iso14827TestValidateSet **p = (Iso14827TestValidateSet **)ptr;
	if (p != NULL) { Iso14827TestValidateSet_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateSet_dump(Iso14827TestValidateSet *p, int tab);
// Iso14827TestValidateSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRoleSubsEntry
typedef struct Iso14827TestServerRoleSubsEntry
{
	Dz1Str		oid;
} Iso14827TestServerRoleSubsEntry;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRoleSubsEntry *Iso14827TestServerRoleSubsEntry_new(Dz1Str oid, Dz1Error *err);
static __inline__ Iso14827TestServerRoleSubsEntry *Iso14827TestServerRoleSubsEntry_gen(Dz1Error *err) { return Iso14827TestServerRoleSubsEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestServerRoleSubsEntry_copy(Iso14827TestServerRoleSubsEntry *dst, Iso14827TestServerRoleSubsEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRoleSubsEntry *Iso14827TestServerRoleSubsEntry_clone(Iso14827TestServerRoleSubsEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRoleSubsEntry_purge(Iso14827TestServerRoleSubsEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRoleSubsEntry_del(Iso14827TestServerRoleSubsEntry *p);
static __inline__ void Iso14827TestServerRoleSubsEntry_delAndSetNull(void *ptr)
{
	Iso14827TestServerRoleSubsEntry **p = (Iso14827TestServerRoleSubsEntry **)ptr;
	if (p) { Iso14827TestServerRoleSubsEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRoleSubsEntry_dump(Iso14827TestServerRoleSubsEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Iso14827TestServerRoleSubsEntry_cmp(Iso14827TestServerRoleSubsEntry *a, Iso14827TestServerRoleSubsEntry *b); 
// Iso14827TestServerRoleSubsEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRoleSubsList
typedef struct Iso14827TestServerRoleSubsList
{
	void *storage;
	unsigned int (*count)(struct Iso14827TestServerRoleSubsList *p);
	Dz1Error (*travel)(struct Iso14827TestServerRoleSubsList *p, Dz1Error (*func)(void *ptr, Iso14827TestServerRoleSubsEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Iso14827TestServerRoleSubsList *p, Dz1Error (*func)(void *ptr, Iso14827TestServerRoleSubsEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Iso14827TestServerRoleSubsList *p, Dz1Error (*func)(void *ptr, Iso14827TestServerRoleSubsEntry *entry), void *ptr);
	Iso14827TestServerRoleSubsEntry **(*get_array)(struct Iso14827TestServerRoleSubsList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Iso14827TestServerRoleSubsList *p, Iso14827TestServerRoleSubsEntry *data);
	bool_t (*remove)(struct Iso14827TestServerRoleSubsList *p, Iso14827TestServerRoleSubsEntry *key);
	Iso14827TestServerRoleSubsEntry *(*extract)(struct Iso14827TestServerRoleSubsList *p, Iso14827TestServerRoleSubsEntry *key);
	Iso14827TestServerRoleSubsEntry *(*find)(struct Iso14827TestServerRoleSubsList *p, Iso14827TestServerRoleSubsEntry *key);
	int (*cmp)(Iso14827TestServerRoleSubsEntry *a, Iso14827TestServerRoleSubsEntry *b);
} Iso14827TestServerRoleSubsList;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRoleSubsList *Iso14827TestServerRoleSubsList_new(Dz1Error *err);
static __inline__ Iso14827TestServerRoleSubsList *Iso14827TestServerRoleSubsList_gen(Dz1Error *err) { return Iso14827TestServerRoleSubsList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRoleSubsList *Iso14827TestServerRoleSubsList_clone(Iso14827TestServerRoleSubsList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRoleSubsList_purge(Iso14827TestServerRoleSubsList *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRoleSubsList_del(Iso14827TestServerRoleSubsList *p);
static __inline__ void Iso14827TestServerRoleSubsList_delAndSetNull(void *ptr)
{
	Iso14827TestServerRoleSubsList **p = (Iso14827TestServerRoleSubsList **)ptr;
	if (p != NULL) { Iso14827TestServerRoleSubsList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRoleSubsList_dump(Iso14827TestServerRoleSubsList *p, int tab);

// Iso14827TestServerRoleSubsList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRoleViolatedSubTest
typedef struct Iso14827TestServerRoleViolatedSubTest
{
	u32_t		sub_serial;
	bool_t		guaranteed;
	Dz1Str		oid;
	s32_t		wait_pub_s;
} Iso14827TestServerRoleViolatedSubTest;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRoleViolatedSubTest *Iso14827TestServerRoleViolatedSubTest_new(u32_t sub_serial, 
																										 bool_t guaranteed, 
																										 Dz1Str oid, 
																										 s32_t wait_pub_s, Dz1Error *err);
static __inline__ Iso14827TestServerRoleViolatedSubTest *Iso14827TestServerRoleViolatedSubTest_gen(Dz1Error *err) { return Iso14827TestServerRoleViolatedSubTest_new(0, 0, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestServerRoleViolatedSubTest_copy(Iso14827TestServerRoleViolatedSubTest *dst, Iso14827TestServerRoleViolatedSubTest *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRoleViolatedSubTest *Iso14827TestServerRoleViolatedSubTest_clone(Iso14827TestServerRoleViolatedSubTest *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRoleViolatedSubTest_purge(Iso14827TestServerRoleViolatedSubTest *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRoleViolatedSubTest_del(Iso14827TestServerRoleViolatedSubTest *p);
static __inline__ void Iso14827TestServerRoleViolatedSubTest_delAndSetNull(void *ptr)
{
	Iso14827TestServerRoleViolatedSubTest **p = (Iso14827TestServerRoleViolatedSubTest **)ptr;
	if (p) { Iso14827TestServerRoleViolatedSubTest_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRoleViolatedSubTest_dump(Iso14827TestServerRoleViolatedSubTest *p, int tab);
// Iso14827TestServerRoleViolatedSubTest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRole1
typedef struct Iso14827TestServerRole1
{
	Dz1Asn1UTF8Str						*my_domain;
	Dz1Asn1UTF8Str						*peer_domain;
	Iso14827TestConnection				*connection;
	bool_t								 test_session;
	bool_t								 test_login_retry;
	Iso14827TestServerRoleSubsList		*test_subs;
	Iso14827TestValidateSet				*validate_set;
	bool_t								 test_request_retry;
	bool_t								 test_invalid_pub;
} Iso14827TestServerRole1;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRole1 *Iso14827TestServerRole1_new(Dz1Asn1UTF8Str *my_domain, 
																			 Dz1Asn1UTF8Str *peer_domain, 
																			 Iso14827TestConnection *connection, 
																			 bool_t test_session, 
																			 bool_t test_login_retry, 
																			 Iso14827TestServerRoleSubsList *test_subs, 
																			 Iso14827TestValidateSet *validate_set, 
																			 bool_t test_request_retry, 
																			 bool_t test_invalid_pub, Dz1Error *err);
static __inline__ Iso14827TestServerRole1 *Iso14827TestServerRole1_gen(Dz1Error *err) { return Iso14827TestServerRole1_new(NULL, NULL, NULL, 0, 0, NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestServerRole1_copy(Iso14827TestServerRole1 *dst, Iso14827TestServerRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRole1 *Iso14827TestServerRole1_clone(Iso14827TestServerRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRole1_purge(Iso14827TestServerRole1 *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRole1_del(Iso14827TestServerRole1 *p);
static __inline__ void Iso14827TestServerRole1_delAndSetNull(void *ptr)
{
	Iso14827TestServerRole1 **p = (Iso14827TestServerRole1 **)ptr;
	if (p) { Iso14827TestServerRole1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRole1_dump(Iso14827TestServerRole1 *p, int tab);
// Iso14827TestServerRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRole2
typedef struct Iso14827TestServerRole2
{
	Dz1Asn1UTF8Str				*my_domain;
	Dz1Asn1UTF8Str				*peer_domain;
	Iso14827TestConnection		*connection;
	u32_t						 subs_timeout_s;
	Iso14827PublicationMgmt		 subs_cancel_reason;
} Iso14827TestServerRole2;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRole2 *Iso14827TestServerRole2_new(Dz1Asn1UTF8Str *my_domain, 
																			 Dz1Asn1UTF8Str *peer_domain, 
																			 Iso14827TestConnection *connection, 
																			 u32_t subs_timeout_s, 
																			 Iso14827PublicationMgmt subs_cancel_reason, Dz1Error *err);
static __inline__ Iso14827TestServerRole2 *Iso14827TestServerRole2_gen(Dz1Error *err) { return Iso14827TestServerRole2_new(NULL, NULL, NULL, 0, Iso14827PublicationMgmt_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestServerRole2_copy(Iso14827TestServerRole2 *dst, Iso14827TestServerRole2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRole2 *Iso14827TestServerRole2_clone(Iso14827TestServerRole2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRole2_purge(Iso14827TestServerRole2 *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRole2_del(Iso14827TestServerRole2 *p);
static __inline__ void Iso14827TestServerRole2_delAndSetNull(void *ptr)
{
	Iso14827TestServerRole2 **p = (Iso14827TestServerRole2 **)ptr;
	if (p) { Iso14827TestServerRole2_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRole2_dump(Iso14827TestServerRole2 *p, int tab);
// Iso14827TestServerRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRole3
typedef struct Iso14827TestServerRole3
{
	Dz1Asn1UTF8Str				*my_domain;
	Dz1Asn1UTF8Str				*peer_domain;
	Iso14827TestConnection		*connection;
	bool_t						 test_session;
	bool_t						 test_login_retry;
	u32_t						 subs_timeout_s;
	Iso14827PublicationMgmt		 subs_cancel_reason;
	Iso14827TestValidateSet		*validate_set;
	bool_t						 test_request_retry;
	bool_t						 test_invalid_pub;
} Iso14827TestServerRole3;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRole3 *Iso14827TestServerRole3_new(Dz1Asn1UTF8Str *my_domain, 
																			 Dz1Asn1UTF8Str *peer_domain, 
																			 Iso14827TestConnection *connection, 
																			 bool_t test_session, 
																			 bool_t test_login_retry, 
																			 u32_t subs_timeout_s, 
																			 Iso14827PublicationMgmt subs_cancel_reason, 
																			 Iso14827TestValidateSet *validate_set, 
																			 bool_t test_request_retry, 
																			 bool_t test_invalid_pub, Dz1Error *err);
static __inline__ Iso14827TestServerRole3 *Iso14827TestServerRole3_gen(Dz1Error *err) { return Iso14827TestServerRole3_new(NULL, NULL, NULL, 0, 0, 0, Iso14827PublicationMgmt_max, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestServerRole3_copy(Iso14827TestServerRole3 *dst, Iso14827TestServerRole3 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestServerRole3 *Iso14827TestServerRole3_clone(Iso14827TestServerRole3 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRole3_purge(Iso14827TestServerRole3 *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRole3_del(Iso14827TestServerRole3 *p);
static __inline__ void Iso14827TestServerRole3_delAndSetNull(void *ptr)
{
	Iso14827TestServerRole3 **p = (Iso14827TestServerRole3 **)ptr;
	if (p) { Iso14827TestServerRole3_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestServerRole3_dump(Iso14827TestServerRole3 *p, int tab);
// Iso14827TestServerRole3
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientAccount
typedef struct Iso14827TestClientAccount
{
	Dz1Asn1UTF8Str		*my_domain;
	Dz1Asn1OctetStr		*authinfo;
	Dz1Asn1OctetStr		*userid;
	Dz1Asn1OctetStr		*passwd;
} Iso14827TestClientAccount;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientAccount *Iso14827TestClientAccount_new(Dz1Asn1UTF8Str *my_domain, 
																				 Dz1Asn1OctetStr *authinfo, 
																				 Dz1Asn1OctetStr *userid, 
																				 Dz1Asn1OctetStr *passwd, Dz1Error *err);
static __inline__ Iso14827TestClientAccount *Iso14827TestClientAccount_gen(Dz1Error *err) { return Iso14827TestClientAccount_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestClientAccount_copy(Iso14827TestClientAccount *dst, Iso14827TestClientAccount *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientAccount *Iso14827TestClientAccount_clone(Iso14827TestClientAccount *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientAccount_purge(Iso14827TestClientAccount *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientAccount_del(Iso14827TestClientAccount *p);
static __inline__ void Iso14827TestClientAccount_delAndSetNull(void *ptr)
{
	Iso14827TestClientAccount **p = (Iso14827TestClientAccount **)ptr;
	if (p) { Iso14827TestClientAccount_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientAccount_dump(Iso14827TestClientAccount *p, int tab);
// Iso14827TestClientAccount
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientPassive
typedef struct Iso14827TestClientPassive
{
	u16_t							 local_port;
	u16_t							 peer_port;
	Iso14827TestClientAccount		*account1;
	Iso14827TestClientAccount		*account2;
} Iso14827TestClientPassive;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientPassive *Iso14827TestClientPassive_new(u16_t local_port, 
																				 u16_t peer_port, 
																				 Iso14827TestClientAccount *account1, 
																				 Iso14827TestClientAccount *account2, Dz1Error *err);
static __inline__ Iso14827TestClientPassive *Iso14827TestClientPassive_gen(Dz1Error *err) { return Iso14827TestClientPassive_new(0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestClientPassive_copy(Iso14827TestClientPassive *dst, Iso14827TestClientPassive *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientPassive *Iso14827TestClientPassive_clone(Iso14827TestClientPassive *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientPassive_purge(Iso14827TestClientPassive *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientPassive_del(Iso14827TestClientPassive *p);
static __inline__ void Iso14827TestClientPassive_delAndSetNull(void *ptr)
{
	Iso14827TestClientPassive **p = (Iso14827TestClientPassive **)ptr;
	if (p) { Iso14827TestClientPassive_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientPassive_dump(Iso14827TestClientPassive *p, int tab);
// Iso14827TestClientPassive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientActive
typedef struct Iso14827TestClientActive
{
	ConfTestSocketAddress			*peer;
	Iso14827TestClientAccount		*account1;
	Iso14827TestClientAccount		*account2;
} Iso14827TestClientActive;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientActive *Iso14827TestClientActive_new(ConfTestSocketAddress *peer, 
																			   Iso14827TestClientAccount *account1, 
																			   Iso14827TestClientAccount *account2, Dz1Error *err);
static __inline__ Iso14827TestClientActive *Iso14827TestClientActive_gen(Dz1Error *err) { return Iso14827TestClientActive_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestClientActive_copy(Iso14827TestClientActive *dst, Iso14827TestClientActive *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientActive *Iso14827TestClientActive_clone(Iso14827TestClientActive *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientActive_purge(Iso14827TestClientActive *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientActive_del(Iso14827TestClientActive *p);
static __inline__ void Iso14827TestClientActive_delAndSetNull(void *ptr)
{
	Iso14827TestClientActive **p = (Iso14827TestClientActive **)ptr;
	if (p) { Iso14827TestClientActive_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientActive_dump(Iso14827TestClientActive *p, int tab);
// Iso14827TestClientActive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientConnectionPresent
typedef enum Iso14827TestClientConnectionPresent
{
	Iso14827TestClientConnectionPresent_passive,
	Iso14827TestClientConnectionPresent_active,
	Iso14827TestClientConnectionPresent_max
} Iso14827TestClientConnectionPresent;

DZ1_CPPLINK str_t Iso14827TestClientConnectionPresentStrA(Iso14827TestClientConnectionPresent v);
DZ1_CPPLINK Iso14827TestClientConnectionPresent Iso14827TestClientConnectionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestClientConnectionPresentStrW(Iso14827TestClientConnectionPresent v);
DZ1_CPPLINK Iso14827TestClientConnectionPresent Iso14827TestClientConnectionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestClientConnectionPresentStr Iso14827TestClientConnectionPresentStrW
#define Iso14827TestClientConnectionPresentFromStr Iso14827TestClientConnectionPresentFromStrW
#else // UNICODE
#define Iso14827TestClientConnectionPresentStr Iso14827TestClientConnectionPresentStrA
#define Iso14827TestClientConnectionPresentFromStr Iso14827TestClientConnectionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestClientConnectionPresentStr Iso14827TestClientConnectionPresentStrA
#define Iso14827TestClientConnectionPresentFromStr Iso14827TestClientConnectionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientConnectionPresent *Iso14827TestClientConnectionPresent_new(Iso14827TestClientConnectionPresent *src, Dz1Error *err);
static __inline__ Iso14827TestClientConnectionPresent *Iso14827TestClientConnectionPresent_gen(Dz1Error *err) { Iso14827TestClientConnectionPresent v = Iso14827TestClientConnectionPresent_max; return Iso14827TestClientConnectionPresent_new(&v, err); }
#define Iso14827TestClientConnectionPresent_clone             Iso14827TestClientConnectionPresent_new
static __inline__ void Iso14827TestClientConnectionPresent_del(Iso14827TestClientConnectionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestClientConnectionPresent_delAndSetNull(void *ptr)
{
	Iso14827TestClientConnectionPresent **p = (Iso14827TestClientConnectionPresent **)ptr;
	if (p != NULL) { Iso14827TestClientConnectionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientConnectionPresent_dump(Iso14827TestClientConnectionPresent *v, int tab);
// Iso14827TestClientConnectionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientConnection
typedef struct Iso14827TestClientConnection
{
	Iso14827TestClientConnectionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827TestClientPassive		*passive;
		Iso14827TestClientActive		*active;
	} x;
} Iso14827TestClientConnection;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientConnection *Iso14827TestClientConnection_new(Iso14827TestClientConnectionPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827TestClientConnection *Iso14827TestClientConnection_gen(Dz1Error *err) { return Iso14827TestClientConnection_new(Iso14827TestClientConnectionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827TestClientConnection_copy(Iso14827TestClientConnection *dst, Iso14827TestClientConnection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientConnection *Iso14827TestClientConnection_clone(Iso14827TestClientConnection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientConnection_purge(Iso14827TestClientConnection *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientConnection_del(Iso14827TestClientConnection *p);
static __inline__ void Iso14827TestClientConnection_delAndSetNull(void *ptr)
{
	Iso14827TestClientConnection **p = (Iso14827TestClientConnection **)ptr;
	if (p != NULL) { Iso14827TestClientConnection_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientConnection_dump(Iso14827TestClientConnection *p, int tab);
// Iso14827TestClientConnection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientRole1
typedef struct Iso14827TestClientRole1
{
	Iso14827TestClientConnection	*connection;
	Dz1Asn1UTF8Str					*peer_domain;
	bool_t							 test_session;
	bool_t							 test_login_invalid;
	bool_t							 test_login_duplicate;
	bool_t							 test_session_maintain;
	bool_t							 test_normal_pub;
	Iso14827TestValidateSet			*validate_set;
	SubscribeSpecList				*subs_invalid_list;
	SubscribeSpecList				*subs_normal_list;
	SubscribeSpecEntry				*subs_cancel;
	SubscribeSpecEntry				*subs_pub_retry;
	Iso14827SubscriptionCancel		 subs_cancel_reason;
} Iso14827TestClientRole1;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientRole1 *Iso14827TestClientRole1_new(Iso14827TestClientConnection *connection, 
																			 Dz1Asn1UTF8Str *peer_domain, 
																			 bool_t test_session, 
																			 bool_t test_login_invalid, 
																			 bool_t test_login_duplicate, 
																			 bool_t test_session_maintain, 
																			 bool_t test_normal_pub, 
																			 Iso14827TestValidateSet *validate_set, 
																			 SubscribeSpecList *subs_invalid_list, 
																			 SubscribeSpecList *subs_normal_list, 
																			 SubscribeSpecEntry *subs_cancel, 
																			 SubscribeSpecEntry *subs_pub_retry, 
																			 Iso14827SubscriptionCancel subs_cancel_reason, Dz1Error *err);
static __inline__ Iso14827TestClientRole1 *Iso14827TestClientRole1_gen(Dz1Error *err) { return Iso14827TestClientRole1_new(NULL, NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, Iso14827SubscriptionCancel_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestClientRole1_copy(Iso14827TestClientRole1 *dst, Iso14827TestClientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientRole1 *Iso14827TestClientRole1_clone(Iso14827TestClientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientRole1_purge(Iso14827TestClientRole1 *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientRole1_del(Iso14827TestClientRole1 *p);
static __inline__ void Iso14827TestClientRole1_delAndSetNull(void *ptr)
{
	Iso14827TestClientRole1 **p = (Iso14827TestClientRole1 **)ptr;
	if (p) { Iso14827TestClientRole1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientRole1_dump(Iso14827TestClientRole1 *p, int tab);
// Iso14827TestClientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientRole1TR
typedef struct Iso14827TestClientRole1TR
{
	Iso14827TestClientConnection	*connection;
	Dz1Asn1UTF8Str					*peer_domain;
	bool_t							 test_session;
	bool_t							 test_login_invalid;
	bool_t							 test_login_duplicate;
	bool_t							 test_session_maintain;
	bool_t							 test_normal_pub;
	Iso14827TestValidateSet			*validate_set;
	SubscribeSpecList				*subs_invalid_list;
	SubscribeSpecList				*subs_normal_list;
	SubscribeSpecEntry				*subs_cancel;
	SubscribeSpecEntry				*subs_pub_retry;
	Iso14827SubscriptionCancel		 subs_cancel_reason;
} Iso14827TestClientRole1TR;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientRole1TR *Iso14827TestClientRole1TR_new(Iso14827TestClientConnection *connection, 
																				 Dz1Asn1UTF8Str *peer_domain, 
																				 bool_t test_session, 
																				 bool_t test_login_invalid, 
																				 bool_t test_login_duplicate, 
																				 bool_t test_session_maintain, 
																				 bool_t test_normal_pub, 
																				 Iso14827TestValidateSet *validate_set, 
																				 SubscribeSpecList *subs_invalid_list, 
																				 SubscribeSpecList *subs_normal_list, 
																				 SubscribeSpecEntry *subs_cancel, 
																				 SubscribeSpecEntry *subs_pub_retry, 
																				 Iso14827SubscriptionCancel subs_cancel_reason, Dz1Error *err);
static __inline__ Iso14827TestClientRole1TR *Iso14827TestClientRole1TR_gen(Dz1Error *err) { return Iso14827TestClientRole1TR_new(NULL, NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, Iso14827SubscriptionCancel_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestClientRole1TR_copy(Iso14827TestClientRole1TR *dst, Iso14827TestClientRole1TR *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientRole1TR *Iso14827TestClientRole1TR_clone(Iso14827TestClientRole1TR *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientRole1TR_purge(Iso14827TestClientRole1TR *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientRole1TR_del(Iso14827TestClientRole1TR *p);
static __inline__ void Iso14827TestClientRole1TR_delAndSetNull(void *ptr)
{
	Iso14827TestClientRole1TR **p = (Iso14827TestClientRole1TR **)ptr;
	if (p) { Iso14827TestClientRole1TR_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientRole1TR_dump(Iso14827TestClientRole1TR *p, int tab);
// Iso14827TestClientRole1TR
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientRole2
typedef struct Iso14827TestClientRole2
{
	Iso14827TestClientConnection	*connection;
	Dz1Asn1UTF8Str					*peer_domain;
	SubscribeSpecList				*subs_total_list;
	u32_t							 expireTime;
	Iso14827SubscriptionCancel		 subs_cancel_reason;
} Iso14827TestClientRole2;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientRole2 *Iso14827TestClientRole2_new(Iso14827TestClientConnection *connection, 
																			 Dz1Asn1UTF8Str *peer_domain, 
																			 SubscribeSpecList *subs_total_list, 
																			 u32_t expireTime, 
																			 Iso14827SubscriptionCancel subs_cancel_reason, Dz1Error *err);
static __inline__ Iso14827TestClientRole2 *Iso14827TestClientRole2_gen(Dz1Error *err) { return Iso14827TestClientRole2_new(NULL, NULL, NULL, 0, Iso14827SubscriptionCancel_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestClientRole2_copy(Iso14827TestClientRole2 *dst, Iso14827TestClientRole2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestClientRole2 *Iso14827TestClientRole2_clone(Iso14827TestClientRole2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientRole2_purge(Iso14827TestClientRole2 *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientRole2_del(Iso14827TestClientRole2 *p);
static __inline__ void Iso14827TestClientRole2_delAndSetNull(void *ptr)
{
	Iso14827TestClientRole2 **p = (Iso14827TestClientRole2 **)ptr;
	if (p) { Iso14827TestClientRole2_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestClientRole2_dump(Iso14827TestClientRole2 *p, int tab);
// Iso14827TestClientRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoClientRole
typedef struct Iso14827TestDuoClientRole
{
	Iso14827TestClientConnection	*connection;
	Dz1Asn1UTF8Str					*peer_domain;
	SubscribeSpecDuo				*subs_duo;
} Iso14827TestDuoClientRole;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDuoClientRole *Iso14827TestDuoClientRole_new(Iso14827TestClientConnection *connection, 
																				 Dz1Asn1UTF8Str *peer_domain, 
																				 SubscribeSpecDuo *subs_duo, Dz1Error *err);
static __inline__ Iso14827TestDuoClientRole *Iso14827TestDuoClientRole_gen(Dz1Error *err) { return Iso14827TestDuoClientRole_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestDuoClientRole_copy(Iso14827TestDuoClientRole *dst, Iso14827TestDuoClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDuoClientRole *Iso14827TestDuoClientRole_clone(Iso14827TestDuoClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDuoClientRole_purge(Iso14827TestDuoClientRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDuoClientRole_del(Iso14827TestDuoClientRole *p);
static __inline__ void Iso14827TestDuoClientRole_delAndSetNull(void *ptr)
{
	Iso14827TestDuoClientRole **p = (Iso14827TestDuoClientRole **)ptr;
	if (p) { Iso14827TestDuoClientRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDuoClientRole_dump(Iso14827TestDuoClientRole *p, int tab);
// Iso14827TestDuoClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestAccount
typedef struct Iso14827TestAccount
{
	Dz1Asn1OctetStr		*authinfo;
	Dz1Asn1OctetStr		*userid;
	Dz1Asn1OctetStr		*passwd;
} Iso14827TestAccount;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestAccount *Iso14827TestAccount_new(Dz1Asn1OctetStr *authinfo, 
																	 Dz1Asn1OctetStr *userid, 
																	 Dz1Asn1OctetStr *passwd, Dz1Error *err);
static __inline__ Iso14827TestAccount *Iso14827TestAccount_gen(Dz1Error *err) { return Iso14827TestAccount_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestAccount_copy(Iso14827TestAccount *dst, Iso14827TestAccount *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestAccount *Iso14827TestAccount_clone(Iso14827TestAccount *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestAccount_purge(Iso14827TestAccount *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestAccount_del(Iso14827TestAccount *p);
static __inline__ void Iso14827TestAccount_delAndSetNull(void *ptr)
{
	Iso14827TestAccount **p = (Iso14827TestAccount **)ptr;
	if (p) { Iso14827TestAccount_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestAccount_dump(Iso14827TestAccount *p, int tab);
// Iso14827TestAccount
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoSessionRole
typedef struct Iso14827TestDuoSessionRole
{
	Dz1Asn1UTF8Str				*my_domain;
	Dz1Asn1UTF8Str				*peer_server_domain;
	Iso14827TestConnection		*c_peer_server;
	Iso14827TestAccount			*c_account;
	SubscribeSpecEntry			*c_sub;
	Dz1Asn1UTF8Str				*peer_client_domain;
	Iso14827TestConnection		*s_peer_client;
} Iso14827TestDuoSessionRole;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDuoSessionRole *Iso14827TestDuoSessionRole_new(Dz1Asn1UTF8Str *my_domain, 
																				   Dz1Asn1UTF8Str *peer_server_domain, 
																				   Iso14827TestConnection *c_peer_server, 
																				   Iso14827TestAccount *c_account, 
																				   SubscribeSpecEntry *c_sub, 
																				   Dz1Asn1UTF8Str *peer_client_domain, 
																				   Iso14827TestConnection *s_peer_client, Dz1Error *err);
static __inline__ Iso14827TestDuoSessionRole *Iso14827TestDuoSessionRole_gen(Dz1Error *err) { return Iso14827TestDuoSessionRole_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestDuoSessionRole_copy(Iso14827TestDuoSessionRole *dst, Iso14827TestDuoSessionRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestDuoSessionRole *Iso14827TestDuoSessionRole_clone(Iso14827TestDuoSessionRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDuoSessionRole_purge(Iso14827TestDuoSessionRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDuoSessionRole_del(Iso14827TestDuoSessionRole *p);
static __inline__ void Iso14827TestDuoSessionRole_delAndSetNull(void *ptr)
{
	Iso14827TestDuoSessionRole **p = (Iso14827TestDuoSessionRole **)ptr;
	if (p) { Iso14827TestDuoSessionRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestDuoSessionRole_dump(Iso14827TestDuoSessionRole *p, int tab);
// Iso14827TestDuoSessionRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestScenarioPresent
typedef enum Iso14827TestScenarioPresent
{
	Iso14827TestScenarioPresent_server1,
	Iso14827TestScenarioPresent_server2,
	Iso14827TestScenarioPresent_server3,
	Iso14827TestScenarioPresent_client1,
	Iso14827TestScenarioPresent_client2,
	Iso14827TestScenarioPresent_duo_client,
	Iso14827TestScenarioPresent_duo_session,
	Iso14827TestScenarioPresent_client1_tr,
	Iso14827TestScenarioPresent_max
} Iso14827TestScenarioPresent;

DZ1_CPPLINK str_t Iso14827TestScenarioPresentStrA(Iso14827TestScenarioPresent v);
DZ1_CPPLINK Iso14827TestScenarioPresent Iso14827TestScenarioPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestScenarioPresentStrW(Iso14827TestScenarioPresent v);
DZ1_CPPLINK Iso14827TestScenarioPresent Iso14827TestScenarioPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestScenarioPresentStr Iso14827TestScenarioPresentStrW
#define Iso14827TestScenarioPresentFromStr Iso14827TestScenarioPresentFromStrW
#else // UNICODE
#define Iso14827TestScenarioPresentStr Iso14827TestScenarioPresentStrA
#define Iso14827TestScenarioPresentFromStr Iso14827TestScenarioPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestScenarioPresentStr Iso14827TestScenarioPresentStrA
#define Iso14827TestScenarioPresentFromStr Iso14827TestScenarioPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestScenarioPresent *Iso14827TestScenarioPresent_new(Iso14827TestScenarioPresent *src, Dz1Error *err);
static __inline__ Iso14827TestScenarioPresent *Iso14827TestScenarioPresent_gen(Dz1Error *err) { Iso14827TestScenarioPresent v = Iso14827TestScenarioPresent_max; return Iso14827TestScenarioPresent_new(&v, err); }
#define Iso14827TestScenarioPresent_clone             Iso14827TestScenarioPresent_new
static __inline__ void Iso14827TestScenarioPresent_del(Iso14827TestScenarioPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestScenarioPresent_delAndSetNull(void *ptr)
{
	Iso14827TestScenarioPresent **p = (Iso14827TestScenarioPresent **)ptr;
	if (p != NULL) { Iso14827TestScenarioPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestScenarioPresent_dump(Iso14827TestScenarioPresent *v, int tab);
// Iso14827TestScenarioPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestScenario
typedef struct Iso14827TestScenario
{
	Iso14827TestScenarioPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827TestServerRole1			*server1;
		Iso14827TestServerRole2			*server2;
		Iso14827TestServerRole3			*server3;
		Iso14827TestClientRole1			*client1;
		Iso14827TestClientRole2			*client2;
		Iso14827TestDuoClientRole		*duo_client;
		Iso14827TestDuoSessionRole		*duo_session;
		Iso14827TestClientRole1TR		*client1_tr;
	} x;
} Iso14827TestScenario;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestScenario *Iso14827TestScenario_new(Iso14827TestScenarioPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827TestScenario *Iso14827TestScenario_gen(Dz1Error *err) { return Iso14827TestScenario_new(Iso14827TestScenarioPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827TestScenario_copy(Iso14827TestScenario *dst, Iso14827TestScenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestScenario *Iso14827TestScenario_clone(Iso14827TestScenario *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestScenario_purge(Iso14827TestScenario *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestScenario_del(Iso14827TestScenario *p);
static __inline__ void Iso14827TestScenario_delAndSetNull(void *ptr)
{
	Iso14827TestScenario **p = (Iso14827TestScenario **)ptr;
	if (p != NULL) { Iso14827TestScenario_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestScenario_dump(Iso14827TestScenario *p, int tab);
// Iso14827TestScenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestProcessStatusCode
typedef enum Iso14827TestProcessStatusCode
{
	Iso14827TestProcessStatusCode_OK = 0,
	Iso14827TestProcessStatusCode_FAILURE = 1,
	Iso14827TestProcessStatusCode_AGENT_SYSTEM_ERROR = 11,
	Iso14827TestProcessStatusCode_SERVER_DISCONNECTED = 12,
	Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR = 13,
	Iso14827TestProcessStatusCode_CONNECTION_FAIL = 100,
	Iso14827TestProcessStatusCode_DISCONNECTED = 101,
	Iso14827TestProcessStatusCode_TIMEOUT = 102,
	Iso14827TestProcessStatusCode_OUT_OF_RANGE = 201,
	Iso14827TestProcessStatusCode_INVALID_PROCESS,
	Iso14827TestProcessStatusCode_INVALID_IDENTIFIER,
	Iso14827TestProcessStatusCode_SESSION_DUPLICATE,
	Iso14827TestProcessStatusCode_DECODE_FAIL = 210,
	Iso14827TestProcessStatusCode_INVALID_ENCODING_RULE = 211,
	Iso14827TestProcessStatusCode_INVALID_OID = 212,
	Iso14827TestProcessStatusCode_INVALID_DSRC_MSG_ID = 213,
	Iso14827TestProcessStatusCode_JSON_PARSE_ERROR = 221,
	Iso14827TestProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR = 231,
	Iso14827TestProcessStatusCode_INVALID_TOPIC = 241,
	Iso14827TestProcessStatusCode_UNKNOWN = 300,
	Iso14827TestProcessStatusCode_max
} Iso14827TestProcessStatusCode;

DZ1_CPPLINK str_t Iso14827TestProcessStatusCodeStrA(Iso14827TestProcessStatusCode v);
DZ1_CPPLINK Iso14827TestProcessStatusCode Iso14827TestProcessStatusCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestProcessStatusCodeStrW(Iso14827TestProcessStatusCode v);
DZ1_CPPLINK Iso14827TestProcessStatusCode Iso14827TestProcessStatusCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestProcessStatusCodeStr Iso14827TestProcessStatusCodeStrW
#define Iso14827TestProcessStatusCodeFromStr Iso14827TestProcessStatusCodeFromStrW
#else // UNICODE
#define Iso14827TestProcessStatusCodeStr Iso14827TestProcessStatusCodeStrA
#define Iso14827TestProcessStatusCodeFromStr Iso14827TestProcessStatusCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestProcessStatusCodeStr Iso14827TestProcessStatusCodeStrA
#define Iso14827TestProcessStatusCodeFromStr Iso14827TestProcessStatusCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestProcessStatusCode *Iso14827TestProcessStatusCode_new(Iso14827TestProcessStatusCode *src, Dz1Error *err);
static __inline__ Iso14827TestProcessStatusCode *Iso14827TestProcessStatusCode_gen(Dz1Error *err) { Iso14827TestProcessStatusCode v = Iso14827TestProcessStatusCode_max; return Iso14827TestProcessStatusCode_new(&v, err); }
#define Iso14827TestProcessStatusCode_clone             Iso14827TestProcessStatusCode_new
static __inline__ void Iso14827TestProcessStatusCode_del(Iso14827TestProcessStatusCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestProcessStatusCode_delAndSetNull(void *ptr)
{
	Iso14827TestProcessStatusCode **p = (Iso14827TestProcessStatusCode **)ptr;
	if (p != NULL) { Iso14827TestProcessStatusCode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestProcessStatusCode_dump(Iso14827TestProcessStatusCode *v, int tab);
// Iso14827TestProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyStateContext
typedef struct Iso14827TestNotifyStateContext
{
	Dz1Str		testName;
	s64_t		time;
	Dz1Str		state;
} Iso14827TestNotifyStateContext;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyStateContext *Iso14827TestNotifyStateContext_new(Dz1Str testName, 
																						   s64_t time, 
																						   Dz1Str state, Dz1Error *err);
static __inline__ Iso14827TestNotifyStateContext *Iso14827TestNotifyStateContext_gen(Dz1Error *err) { return Iso14827TestNotifyStateContext_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestNotifyStateContext_copy(Iso14827TestNotifyStateContext *dst, Iso14827TestNotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyStateContext *Iso14827TestNotifyStateContext_clone(Iso14827TestNotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyStateContext_purge(Iso14827TestNotifyStateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyStateContext_del(Iso14827TestNotifyStateContext *p);
static __inline__ void Iso14827TestNotifyStateContext_delAndSetNull(void *ptr)
{
	Iso14827TestNotifyStateContext **p = (Iso14827TestNotifyStateContext **)ptr;
	if (p) { Iso14827TestNotifyStateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyStateContext_dump(Iso14827TestNotifyStateContext *p, int tab);
// Iso14827TestNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyInfoContext
typedef struct Iso14827TestNotifyInfoContext
{
	Dz1Str			 testName;
	s64_t			 time;
	Dz1Str			 sender;
	Dz1Str			 log;
	Dz1Binary		*data;
	Dz1Str			 dataType;
} Iso14827TestNotifyInfoContext;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyInfoContext *Iso14827TestNotifyInfoContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 Dz1Str sender, 
																						 Dz1Str log, 
																						 Dz1Binary *data, 
																						 Dz1Str dataType, Dz1Error *err);
static __inline__ Iso14827TestNotifyInfoContext *Iso14827TestNotifyInfoContext_gen(Dz1Error *err) { return Iso14827TestNotifyInfoContext_new(NULL, 0, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestNotifyInfoContext_copy(Iso14827TestNotifyInfoContext *dst, Iso14827TestNotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyInfoContext *Iso14827TestNotifyInfoContext_clone(Iso14827TestNotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyInfoContext_purge(Iso14827TestNotifyInfoContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyInfoContext_del(Iso14827TestNotifyInfoContext *p);
static __inline__ void Iso14827TestNotifyInfoContext_delAndSetNull(void *ptr)
{
	Iso14827TestNotifyInfoContext **p = (Iso14827TestNotifyInfoContext **)ptr;
	if (p) { Iso14827TestNotifyInfoContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyInfoContext_dump(Iso14827TestNotifyInfoContext *p, int tab);
// Iso14827TestNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyErrorContext
typedef struct Iso14827TestNotifyErrorContext
{
	Dz1Str								 testName;
	s64_t								 time;
	Iso14827TestProcessStatusCode		 code;
	Dz1Str								 desc;
	Dz1Str								 log;
	Dz1Binary							*data;
} Iso14827TestNotifyErrorContext;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyErrorContext *Iso14827TestNotifyErrorContext_new(Dz1Str testName, 
																						   s64_t time, 
																						   Iso14827TestProcessStatusCode code, 
																						   Dz1Str desc, 
																						   Dz1Str log, 
																						   Dz1Binary *data, Dz1Error *err);
static __inline__ Iso14827TestNotifyErrorContext *Iso14827TestNotifyErrorContext_gen(Dz1Error *err) { return Iso14827TestNotifyErrorContext_new(NULL, 0, Iso14827TestProcessStatusCode_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestNotifyErrorContext_copy(Iso14827TestNotifyErrorContext *dst, Iso14827TestNotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyErrorContext *Iso14827TestNotifyErrorContext_clone(Iso14827TestNotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyErrorContext_purge(Iso14827TestNotifyErrorContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyErrorContext_del(Iso14827TestNotifyErrorContext *p);
static __inline__ void Iso14827TestNotifyErrorContext_delAndSetNull(void *ptr)
{
	Iso14827TestNotifyErrorContext **p = (Iso14827TestNotifyErrorContext **)ptr;
	if (p) { Iso14827TestNotifyErrorContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyErrorContext_dump(Iso14827TestNotifyErrorContext *p, int tab);
// Iso14827TestNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyContextPresent
typedef enum Iso14827TestNotifyContextPresent
{
	Iso14827TestNotifyContextPresent_state,
	Iso14827TestNotifyContextPresent_info,
	Iso14827TestNotifyContextPresent_error,
	Iso14827TestNotifyContextPresent_max
} Iso14827TestNotifyContextPresent;

DZ1_CPPLINK str_t Iso14827TestNotifyContextPresentStrA(Iso14827TestNotifyContextPresent v);
DZ1_CPPLINK Iso14827TestNotifyContextPresent Iso14827TestNotifyContextPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestNotifyContextPresentStrW(Iso14827TestNotifyContextPresent v);
DZ1_CPPLINK Iso14827TestNotifyContextPresent Iso14827TestNotifyContextPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestNotifyContextPresentStr Iso14827TestNotifyContextPresentStrW
#define Iso14827TestNotifyContextPresentFromStr Iso14827TestNotifyContextPresentFromStrW
#else // UNICODE
#define Iso14827TestNotifyContextPresentStr Iso14827TestNotifyContextPresentStrA
#define Iso14827TestNotifyContextPresentFromStr Iso14827TestNotifyContextPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestNotifyContextPresentStr Iso14827TestNotifyContextPresentStrA
#define Iso14827TestNotifyContextPresentFromStr Iso14827TestNotifyContextPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyContextPresent *Iso14827TestNotifyContextPresent_new(Iso14827TestNotifyContextPresent *src, Dz1Error *err);
static __inline__ Iso14827TestNotifyContextPresent *Iso14827TestNotifyContextPresent_gen(Dz1Error *err) { Iso14827TestNotifyContextPresent v = Iso14827TestNotifyContextPresent_max; return Iso14827TestNotifyContextPresent_new(&v, err); }
#define Iso14827TestNotifyContextPresent_clone             Iso14827TestNotifyContextPresent_new
static __inline__ void Iso14827TestNotifyContextPresent_del(Iso14827TestNotifyContextPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestNotifyContextPresent_delAndSetNull(void *ptr)
{
	Iso14827TestNotifyContextPresent **p = (Iso14827TestNotifyContextPresent **)ptr;
	if (p != NULL) { Iso14827TestNotifyContextPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyContextPresent_dump(Iso14827TestNotifyContextPresent *v, int tab);
// Iso14827TestNotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyContext
typedef struct Iso14827TestNotifyContext
{
	Iso14827TestNotifyContextPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Iso14827TestNotifyStateContext		*state;
		Iso14827TestNotifyInfoContext		*info;
		Iso14827TestNotifyErrorContext		*error;
	} x;
} Iso14827TestNotifyContext;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyContext *Iso14827TestNotifyContext_new(Iso14827TestNotifyContextPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827TestNotifyContext *Iso14827TestNotifyContext_gen(Dz1Error *err) { return Iso14827TestNotifyContext_new(Iso14827TestNotifyContextPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827TestNotifyContext_copy(Iso14827TestNotifyContext *dst, Iso14827TestNotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyContext *Iso14827TestNotifyContext_clone(Iso14827TestNotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyContext_purge(Iso14827TestNotifyContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyContext_del(Iso14827TestNotifyContext *p);
static __inline__ void Iso14827TestNotifyContext_delAndSetNull(void *ptr)
{
	Iso14827TestNotifyContext **p = (Iso14827TestNotifyContext **)ptr;
	if (p != NULL) { Iso14827TestNotifyContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyContext_dump(Iso14827TestNotifyContext *p, int tab);
// Iso14827TestNotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyStateArg
typedef struct Iso14827TestNotifyStateArg
{
	u32_t								 testIdx;
	Iso14827TestNotifyStateContext		*context;
} Iso14827TestNotifyStateArg;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyStateArg *Iso14827TestNotifyStateArg_new(u32_t testIdx, 
																				   Iso14827TestNotifyStateContext *context, Dz1Error *err);
static __inline__ Iso14827TestNotifyStateArg *Iso14827TestNotifyStateArg_gen(Dz1Error *err) { return Iso14827TestNotifyStateArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestNotifyStateArg_copy(Iso14827TestNotifyStateArg *dst, Iso14827TestNotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyStateArg *Iso14827TestNotifyStateArg_clone(Iso14827TestNotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyStateArg_purge(Iso14827TestNotifyStateArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyStateArg_del(Iso14827TestNotifyStateArg *p);
static __inline__ void Iso14827TestNotifyStateArg_delAndSetNull(void *ptr)
{
	Iso14827TestNotifyStateArg **p = (Iso14827TestNotifyStateArg **)ptr;
	if (p) { Iso14827TestNotifyStateArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyStateArg_dump(Iso14827TestNotifyStateArg *p, int tab);
// Iso14827TestNotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyInfoArg
typedef struct Iso14827TestNotifyInfoArg
{
	u32_t								 testIdx;
	Iso14827TestNotifyInfoContext		*context;
} Iso14827TestNotifyInfoArg;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyInfoArg *Iso14827TestNotifyInfoArg_new(u32_t testIdx, 
																				 Iso14827TestNotifyInfoContext *context, Dz1Error *err);
static __inline__ Iso14827TestNotifyInfoArg *Iso14827TestNotifyInfoArg_gen(Dz1Error *err) { return Iso14827TestNotifyInfoArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestNotifyInfoArg_copy(Iso14827TestNotifyInfoArg *dst, Iso14827TestNotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyInfoArg *Iso14827TestNotifyInfoArg_clone(Iso14827TestNotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyInfoArg_purge(Iso14827TestNotifyInfoArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyInfoArg_del(Iso14827TestNotifyInfoArg *p);
static __inline__ void Iso14827TestNotifyInfoArg_delAndSetNull(void *ptr)
{
	Iso14827TestNotifyInfoArg **p = (Iso14827TestNotifyInfoArg **)ptr;
	if (p) { Iso14827TestNotifyInfoArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyInfoArg_dump(Iso14827TestNotifyInfoArg *p, int tab);
// Iso14827TestNotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyErrorArg
typedef struct Iso14827TestNotifyErrorArg
{
	u32_t								 testIdx;
	Iso14827TestNotifyErrorContext		*context;
} Iso14827TestNotifyErrorArg;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyErrorArg *Iso14827TestNotifyErrorArg_new(u32_t testIdx, 
																				   Iso14827TestNotifyErrorContext *context, Dz1Error *err);
static __inline__ Iso14827TestNotifyErrorArg *Iso14827TestNotifyErrorArg_gen(Dz1Error *err) { return Iso14827TestNotifyErrorArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestNotifyErrorArg_copy(Iso14827TestNotifyErrorArg *dst, Iso14827TestNotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestNotifyErrorArg *Iso14827TestNotifyErrorArg_clone(Iso14827TestNotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyErrorArg_purge(Iso14827TestNotifyErrorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyErrorArg_del(Iso14827TestNotifyErrorArg *p);
static __inline__ void Iso14827TestNotifyErrorArg_delAndSetNull(void *ptr)
{
	Iso14827TestNotifyErrorArg **p = (Iso14827TestNotifyErrorArg **)ptr;
	if (p) { Iso14827TestNotifyErrorArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestNotifyErrorArg_dump(Iso14827TestNotifyErrorArg *p, int tab);
// Iso14827TestNotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestValidateContext
typedef struct Iso14827TestValidateContext
{
	Dz1Str								 testName;
	s64_t								 time;
	Dz1Binary							*raw;
	Dz1Binary							*data;
	Iso14827TestProcessStatusCode		 code;
	Dz1Str								 desc;
} Iso14827TestValidateContext;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestValidateContext *Iso14827TestValidateContext_new(Dz1Str testName, 
																					 s64_t time, 
																					 Dz1Binary *raw, 
																					 Dz1Binary *data, 
																					 Iso14827TestProcessStatusCode code, 
																					 Dz1Str desc, Dz1Error *err);
static __inline__ Iso14827TestValidateContext *Iso14827TestValidateContext_gen(Dz1Error *err) { return Iso14827TestValidateContext_new(NULL, 0, NULL, NULL, Iso14827TestProcessStatusCode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestValidateContext_copy(Iso14827TestValidateContext *dst, Iso14827TestValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestValidateContext *Iso14827TestValidateContext_clone(Iso14827TestValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateContext_purge(Iso14827TestValidateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateContext_del(Iso14827TestValidateContext *p);
static __inline__ void Iso14827TestValidateContext_delAndSetNull(void *ptr)
{
	Iso14827TestValidateContext **p = (Iso14827TestValidateContext **)ptr;
	if (p) { Iso14827TestValidateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateContext_dump(Iso14827TestValidateContext *p, int tab);
// Iso14827TestValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestValidateContextArg
typedef struct Iso14827TestValidateContextArg
{
	u32_t							 testIdx;
	Iso14827TestValidateContext		*context;
} Iso14827TestValidateContextArg;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestValidateContextArg *Iso14827TestValidateContextArg_new(u32_t testIdx, 
																						   Iso14827TestValidateContext *context, Dz1Error *err);
static __inline__ Iso14827TestValidateContextArg *Iso14827TestValidateContextArg_gen(Dz1Error *err) { return Iso14827TestValidateContextArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestValidateContextArg_copy(Iso14827TestValidateContextArg *dst, Iso14827TestValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestValidateContextArg *Iso14827TestValidateContextArg_clone(Iso14827TestValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateContextArg_purge(Iso14827TestValidateContextArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateContextArg_del(Iso14827TestValidateContextArg *p);
static __inline__ void Iso14827TestValidateContextArg_delAndSetNull(void *ptr)
{
	Iso14827TestValidateContextArg **p = (Iso14827TestValidateContextArg **)ptr;
	if (p) { Iso14827TestValidateContextArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestValidateContextArg_dump(Iso14827TestValidateContextArg *p, int tab);
// Iso14827TestValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_centerClient2rse
typedef struct PolicePrj4TestConfiguration_centerClient2rse
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	Dz1Str		peer_ip;
	s64_t		peer_port;
	Dz1Str		user;
	Dz1Str		pass;
	bool_t		test_session;
	bool_t		test_login_invalid;
	bool_t		test_session_maintain;
	bool_t		test_normal_pub;
	bool_t		test_bsm;
	bool_t		test_login_duplicate;
	bool_t		test_invalid_sub;
	bool_t		test_subs_cancel;
	bool_t		test_pub_retry;
} PolicePrj4TestConfiguration_centerClient2rse;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_centerClient2rse *PolicePrj4TestConfiguration_centerClient2rse_new(Dz1Str peer_ip, 
																													   s64_t peer_port, 
																													   Dz1Str user, 
																													   Dz1Str pass, 
																													   bool_t test_session, 
																													   bool_t test_login_invalid, 
																													   bool_t test_session_maintain, 
																													   bool_t test_normal_pub, 
																													   bool_t test_bsm, 
																													   bool_t test_login_duplicate, 
																													   bool_t test_invalid_sub, 
																													   bool_t test_subs_cancel, 
																													   bool_t test_pub_retry, Dz1Error *err);
static __inline__ PolicePrj4TestConfiguration_centerClient2rse *PolicePrj4TestConfiguration_centerClient2rse_gen(Dz1Error *err) { return PolicePrj4TestConfiguration_centerClient2rse_new(NULL, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4TestConfiguration_centerClient2rse_copy(PolicePrj4TestConfiguration_centerClient2rse *dst, PolicePrj4TestConfiguration_centerClient2rse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_centerClient2rse *PolicePrj4TestConfiguration_centerClient2rse_clone(PolicePrj4TestConfiguration_centerClient2rse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_centerClient2rse_purge(PolicePrj4TestConfiguration_centerClient2rse *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_centerClient2rse_del(PolicePrj4TestConfiguration_centerClient2rse *p);
static __inline__ void PolicePrj4TestConfiguration_centerClient2rse_delAndSetNull(void *ptr)
{
	PolicePrj4TestConfiguration_centerClient2rse **p = (PolicePrj4TestConfiguration_centerClient2rse **)ptr;
	if (p) { PolicePrj4TestConfiguration_centerClient2rse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_centerClient2rse_dump(PolicePrj4TestConfiguration_centerClient2rse *p, int tab);
// PolicePrj4TestConfiguration_centerClient2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_rseServer2center
typedef struct PolicePrj4TestConfiguration_rseServer2center
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	s64_t		local_port;
	bool_t		test_session;
	bool_t		test_login_retry;
	s64_t		subs_timeout_s;
	bool_t		test_bsm;
	bool_t		test_sub_retry;
	bool_t		test_invalid_pub;
} PolicePrj4TestConfiguration_rseServer2center;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_rseServer2center *PolicePrj4TestConfiguration_rseServer2center_new(s64_t local_port, 
																													   bool_t test_session, 
																													   bool_t test_login_retry, 
																													   s64_t subs_timeout_s, 
																													   bool_t test_bsm, 
																													   bool_t test_sub_retry, 
																													   bool_t test_invalid_pub, Dz1Error *err);
static __inline__ PolicePrj4TestConfiguration_rseServer2center *PolicePrj4TestConfiguration_rseServer2center_gen(Dz1Error *err) { return PolicePrj4TestConfiguration_rseServer2center_new(0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4TestConfiguration_rseServer2center_copy(PolicePrj4TestConfiguration_rseServer2center *dst, PolicePrj4TestConfiguration_rseServer2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_rseServer2center *PolicePrj4TestConfiguration_rseServer2center_clone(PolicePrj4TestConfiguration_rseServer2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_rseServer2center_purge(PolicePrj4TestConfiguration_rseServer2center *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_rseServer2center_del(PolicePrj4TestConfiguration_rseServer2center *p);
static __inline__ void PolicePrj4TestConfiguration_rseServer2center_delAndSetNull(void *ptr)
{
	PolicePrj4TestConfiguration_rseServer2center **p = (PolicePrj4TestConfiguration_rseServer2center **)ptr;
	if (p) { PolicePrj4TestConfiguration_rseServer2center_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_rseServer2center_dump(PolicePrj4TestConfiguration_rseServer2center *p, int tab);
// PolicePrj4TestConfiguration_rseServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_rseClient2center
typedef struct PolicePrj4TestConfiguration_rseClient2center
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	Dz1Str		peer_ip;
	s64_t		peer_port;
	Dz1Str		user;
	Dz1Str		pass;
	bool_t		test_session;
	bool_t		test_login_invalid;
	bool_t		test_session_maintain;
	bool_t		test_normal_pub;
	bool_t		test_map;
	bool_t		test_rsa;
	bool_t		test_tim;
	bool_t		test_login_duplicate;
	bool_t		test_invalid_sub;
	bool_t		test_subs_cancel;
	bool_t		test_pub_retry;
} PolicePrj4TestConfiguration_rseClient2center;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_rseClient2center *PolicePrj4TestConfiguration_rseClient2center_new(Dz1Str peer_ip, 
																													   s64_t peer_port, 
																													   Dz1Str user, 
																													   Dz1Str pass, 
																													   bool_t test_session, 
																													   bool_t test_login_invalid, 
																													   bool_t test_session_maintain, 
																													   bool_t test_normal_pub, 
																													   bool_t test_map, 
																													   bool_t test_rsa, 
																													   bool_t test_tim, 
																													   bool_t test_login_duplicate, 
																													   bool_t test_invalid_sub, 
																													   bool_t test_subs_cancel, 
																													   bool_t test_pub_retry, Dz1Error *err);
static __inline__ PolicePrj4TestConfiguration_rseClient2center *PolicePrj4TestConfiguration_rseClient2center_gen(Dz1Error *err) { return PolicePrj4TestConfiguration_rseClient2center_new(NULL, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4TestConfiguration_rseClient2center_copy(PolicePrj4TestConfiguration_rseClient2center *dst, PolicePrj4TestConfiguration_rseClient2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_rseClient2center *PolicePrj4TestConfiguration_rseClient2center_clone(PolicePrj4TestConfiguration_rseClient2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_rseClient2center_purge(PolicePrj4TestConfiguration_rseClient2center *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_rseClient2center_del(PolicePrj4TestConfiguration_rseClient2center *p);
static __inline__ void PolicePrj4TestConfiguration_rseClient2center_delAndSetNull(void *ptr)
{
	PolicePrj4TestConfiguration_rseClient2center **p = (PolicePrj4TestConfiguration_rseClient2center **)ptr;
	if (p) { PolicePrj4TestConfiguration_rseClient2center_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_rseClient2center_dump(PolicePrj4TestConfiguration_rseClient2center *p, int tab);
// PolicePrj4TestConfiguration_rseClient2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_centerServer2rse
typedef struct PolicePrj4TestConfiguration_centerServer2rse
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	s64_t		local_port;
	bool_t		test_session;
	bool_t		test_login_retry;
	s64_t		subs_timeout_s;
	bool_t		test_map;
	bool_t		test_rsa;
	bool_t		test_tim;
	bool_t		test_sub_retry;
	bool_t		test_invalid_pub;
} PolicePrj4TestConfiguration_centerServer2rse;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_centerServer2rse *PolicePrj4TestConfiguration_centerServer2rse_new(s64_t local_port, 
																													   bool_t test_session, 
																													   bool_t test_login_retry, 
																													   s64_t subs_timeout_s, 
																													   bool_t test_map, 
																													   bool_t test_rsa, 
																													   bool_t test_tim, 
																													   bool_t test_sub_retry, 
																													   bool_t test_invalid_pub, Dz1Error *err);
static __inline__ PolicePrj4TestConfiguration_centerServer2rse *PolicePrj4TestConfiguration_centerServer2rse_gen(Dz1Error *err) { return PolicePrj4TestConfiguration_centerServer2rse_new(0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4TestConfiguration_centerServer2rse_copy(PolicePrj4TestConfiguration_centerServer2rse *dst, PolicePrj4TestConfiguration_centerServer2rse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_centerServer2rse *PolicePrj4TestConfiguration_centerServer2rse_clone(PolicePrj4TestConfiguration_centerServer2rse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_centerServer2rse_purge(PolicePrj4TestConfiguration_centerServer2rse *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_centerServer2rse_del(PolicePrj4TestConfiguration_centerServer2rse *p);
static __inline__ void PolicePrj4TestConfiguration_centerServer2rse_delAndSetNull(void *ptr)
{
	PolicePrj4TestConfiguration_centerServer2rse **p = (PolicePrj4TestConfiguration_centerServer2rse **)ptr;
	if (p) { PolicePrj4TestConfiguration_centerServer2rse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_centerServer2rse_dump(PolicePrj4TestConfiguration_centerServer2rse *p, int tab);
// PolicePrj4TestConfiguration_centerServer2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_signalserverServer2center
typedef struct PolicePrj4TestConfiguration_signalserverServer2center
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	s64_t		local_port;
	bool_t		test_session;
	bool_t		test_login_retry;
	s64_t		subs_timeout_s;
	bool_t		test_spat;
	bool_t		test_tls;
	bool_t		test_sub_retry;
	bool_t		test_invalid_pub;
} PolicePrj4TestConfiguration_signalserverServer2center;

DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_signalserverServer2center *PolicePrj4TestConfiguration_signalserverServer2center_new(s64_t local_port, 
																																		 bool_t test_session, 
																																		 bool_t test_login_retry, 
																																		 s64_t subs_timeout_s, 
																																		 bool_t test_spat, 
																																		 bool_t test_tls, 
																																		 bool_t test_sub_retry, 
																																		 bool_t test_invalid_pub, Dz1Error *err);
static __inline__ PolicePrj4TestConfiguration_signalserverServer2center *PolicePrj4TestConfiguration_signalserverServer2center_gen(Dz1Error *err) { return PolicePrj4TestConfiguration_signalserverServer2center_new(0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PolicePrj4TestConfiguration_signalserverServer2center_copy(PolicePrj4TestConfiguration_signalserverServer2center *dst, PolicePrj4TestConfiguration_signalserverServer2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PolicePrj4TestConfiguration_signalserverServer2center *PolicePrj4TestConfiguration_signalserverServer2center_clone(PolicePrj4TestConfiguration_signalserverServer2center *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_signalserverServer2center_purge(PolicePrj4TestConfiguration_signalserverServer2center *p);
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_signalserverServer2center_del(PolicePrj4TestConfiguration_signalserverServer2center *p);
static __inline__ void PolicePrj4TestConfiguration_signalserverServer2center_delAndSetNull(void *ptr)
{
	PolicePrj4TestConfiguration_signalserverServer2center **p = (PolicePrj4TestConfiguration_signalserverServer2center **)ptr;
	if (p) { PolicePrj4TestConfiguration_signalserverServer2center_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PolicePrj4TestConfiguration_signalserverServer2center_dump(PolicePrj4TestConfiguration_signalserverServer2center *p, int tab);
// PolicePrj4TestConfiguration_signalserverServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3TestConfigurationServerRole
typedef struct ITSK00100_3TestConfigurationServerRole
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	s64_t		local_port;
	bool_t		test_session;
	bool_t		test_login_retry;
	bool_t		test_sub_incident_detection_info;
	bool_t		test_sub_incident_termination_info;
	bool_t		test_sub_incident_detection_video_file_info_provide;
	bool_t		test_sub_control_state_info;
	bool_t		test_sub_sensor_state_info;
	bool_t		test_sub_moving_object;
	bool_t		test_sub_retry;
	bool_t		test_invalid_pub;
} ITSK00100_3TestConfigurationServerRole;

DZ1_CPPLINK DZ1_DLLPORT ITSK00100_3TestConfigurationServerRole *ITSK00100_3TestConfigurationServerRole_new(s64_t local_port, 
																										   bool_t test_session, 
																										   bool_t test_login_retry, 
																										   bool_t test_sub_incident_detection_info, 
																										   bool_t test_sub_incident_termination_info, 
																										   bool_t test_sub_incident_detection_video_file_info_provide, 
																										   bool_t test_sub_control_state_info, 
																										   bool_t test_sub_sensor_state_info, 
																										   bool_t test_sub_moving_object, 
																										   bool_t test_sub_retry, 
																										   bool_t test_invalid_pub, Dz1Error *err);
static __inline__ ITSK00100_3TestConfigurationServerRole *ITSK00100_3TestConfigurationServerRole_gen(Dz1Error *err) { return ITSK00100_3TestConfigurationServerRole_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00100_3TestConfigurationServerRole_copy(ITSK00100_3TestConfigurationServerRole *dst, ITSK00100_3TestConfigurationServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00100_3TestConfigurationServerRole *ITSK00100_3TestConfigurationServerRole_clone(ITSK00100_3TestConfigurationServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3TestConfigurationServerRole_purge(ITSK00100_3TestConfigurationServerRole *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3TestConfigurationServerRole_del(ITSK00100_3TestConfigurationServerRole *p);
static __inline__ void ITSK00100_3TestConfigurationServerRole_delAndSetNull(void *ptr)
{
	ITSK00100_3TestConfigurationServerRole **p = (ITSK00100_3TestConfigurationServerRole **)ptr;
	if (p) { ITSK00100_3TestConfigurationServerRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3TestConfigurationServerRole_dump(ITSK00100_3TestConfigurationServerRole *p, int tab);
// ITSK00100_3TestConfigurationServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3TestConfigurationClientRole
typedef struct ITSK00100_3TestConfigurationClientRole
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	Dz1Str		peer_ip;
	s64_t		peer_port;
	Dz1Str		user;
	Dz1Str		pass;
	bool_t		test_session;
	bool_t		test_login_invalid;
	bool_t		test_session_maintain;
	bool_t		test_normal_pub;
	bool_t		test_pub_incident_detection_info;
	bool_t		test_pub_incident_termination_info;
	bool_t		test_pub_incident_detection_video_file_info_provide;
	bool_t		test_pub_control_state_info;
	bool_t		test_pub_sensor_state_info;
	bool_t		test_pub_moving_object;
	bool_t		test_login_duplicate;
	bool_t		test_invalid_sub;
	bool_t		test_subs_cancel;
	bool_t		test_pub_retry;
} ITSK00100_3TestConfigurationClientRole;

DZ1_CPPLINK DZ1_DLLPORT ITSK00100_3TestConfigurationClientRole *ITSK00100_3TestConfigurationClientRole_new(Dz1Str peer_ip, 
																										   s64_t peer_port, 
																										   Dz1Str user, 
																										   Dz1Str pass, 
																										   bool_t test_session, 
																										   bool_t test_login_invalid, 
																										   bool_t test_session_maintain, 
																										   bool_t test_normal_pub, 
																										   bool_t test_pub_incident_detection_info, 
																										   bool_t test_pub_incident_termination_info, 
																										   bool_t test_pub_incident_detection_video_file_info_provide, 
																										   bool_t test_pub_control_state_info, 
																										   bool_t test_pub_sensor_state_info, 
																										   bool_t test_pub_moving_object, 
																										   bool_t test_login_duplicate, 
																										   bool_t test_invalid_sub, 
																										   bool_t test_subs_cancel, 
																										   bool_t test_pub_retry, Dz1Error *err);
static __inline__ ITSK00100_3TestConfigurationClientRole *ITSK00100_3TestConfigurationClientRole_gen(Dz1Error *err) { return ITSK00100_3TestConfigurationClientRole_new(NULL, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00100_3TestConfigurationClientRole_copy(ITSK00100_3TestConfigurationClientRole *dst, ITSK00100_3TestConfigurationClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00100_3TestConfigurationClientRole *ITSK00100_3TestConfigurationClientRole_clone(ITSK00100_3TestConfigurationClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3TestConfigurationClientRole_purge(ITSK00100_3TestConfigurationClientRole *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3TestConfigurationClientRole_del(ITSK00100_3TestConfigurationClientRole *p);
static __inline__ void ITSK00100_3TestConfigurationClientRole_delAndSetNull(void *ptr)
{
	ITSK00100_3TestConfigurationClientRole **p = (ITSK00100_3TestConfigurationClientRole **)ptr;
	if (p) { ITSK00100_3TestConfigurationClientRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00100_3TestConfigurationClientRole_dump(ITSK00100_3TestConfigurationClientRole *p, int tab);
// ITSK00100_3TestConfigurationClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1TestConfiguration_clientRole1
typedef struct TechnicalRegulation1TestConfiguration_clientRole1
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	Dz1Str		peer_ip;
	s64_t		peer_port;
	Dz1Str		user;
	Dz1Str		pass;
	bool_t		test_session;
	bool_t		test_login_invalid;
	bool_t		test_session_maintain;
	bool_t		test_normal_pub;
	bool_t		test_pub_current_link_state;
	bool_t		test_pub_event_identity;
	bool_t		test_pub_incident_identity;
	bool_t		test_pub_incident_conditions;
	bool_t		test_pub_roadway_surface_status;
	bool_t		test_pub_weather_information;
	bool_t		test_pub_link_roadway_geometry;
	bool_t		test_pub_probe_vehicle_detection;
	bool_t		test_pub_detector_collection;
	bool_t		test_pub_extention_comm_pdu;
	bool_t		test_login_duplicate;
	bool_t		test_invalid_sub;
	bool_t		test_subs_cancel;
	bool_t		test_pub_retry;
} TechnicalRegulation1TestConfiguration_clientRole1;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1TestConfiguration_clientRole1 *TechnicalRegulation1TestConfiguration_clientRole1_new(Dz1Str peer_ip, 
																																 s64_t peer_port, 
																																 Dz1Str user, 
																																 Dz1Str pass, 
																																 bool_t test_session, 
																																 bool_t test_login_invalid, 
																																 bool_t test_session_maintain, 
																																 bool_t test_normal_pub, 
																																 bool_t test_pub_current_link_state, 
																																 bool_t test_pub_event_identity, 
																																 bool_t test_pub_incident_identity, 
																																 bool_t test_pub_incident_conditions, 
																																 bool_t test_pub_roadway_surface_status, 
																																 bool_t test_pub_weather_information, 
																																 bool_t test_pub_link_roadway_geometry, 
																																 bool_t test_pub_probe_vehicle_detection, 
																																 bool_t test_pub_detector_collection, 
																																 bool_t test_pub_extention_comm_pdu, 
																																 bool_t test_login_duplicate, 
																																 bool_t test_invalid_sub, 
																																 bool_t test_subs_cancel, 
																																 bool_t test_pub_retry, Dz1Error *err);
static __inline__ TechnicalRegulation1TestConfiguration_clientRole1 *TechnicalRegulation1TestConfiguration_clientRole1_gen(Dz1Error *err) { return TechnicalRegulation1TestConfiguration_clientRole1_new(NULL, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulation1TestConfiguration_clientRole1_copy(TechnicalRegulation1TestConfiguration_clientRole1 *dst, TechnicalRegulation1TestConfiguration_clientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1TestConfiguration_clientRole1 *TechnicalRegulation1TestConfiguration_clientRole1_clone(TechnicalRegulation1TestConfiguration_clientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1TestConfiguration_clientRole1_purge(TechnicalRegulation1TestConfiguration_clientRole1 *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1TestConfiguration_clientRole1_del(TechnicalRegulation1TestConfiguration_clientRole1 *p);
static __inline__ void TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull(void *ptr)
{
	TechnicalRegulation1TestConfiguration_clientRole1 **p = (TechnicalRegulation1TestConfiguration_clientRole1 **)ptr;
	if (p) { TechnicalRegulation1TestConfiguration_clientRole1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1TestConfiguration_clientRole1_dump(TechnicalRegulation1TestConfiguration_clientRole1 *p, int tab);
// TechnicalRegulation1TestConfiguration_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2TestConfiguration_clientRole1
typedef struct TechnicalRegulation2TestConfiguration_clientRole1
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	Dz1Str		peer_ip;
	s64_t		peer_port;
	Dz1Str		user;
	Dz1Str		pass;
	bool_t		test_session;
	bool_t		test_login_invalid;
	bool_t		test_session_maintain;
	bool_t		test_normal_pub;
	bool_t		test_pub_comm_tx_pdu;
	bool_t		test_pub_comm_rx_pdu;
	bool_t		test_login_duplicate;
	bool_t		test_invalid_sub;
	bool_t		test_subs_cancel;
	bool_t		test_pub_retry;
} TechnicalRegulation2TestConfiguration_clientRole1;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2TestConfiguration_clientRole1 *TechnicalRegulation2TestConfiguration_clientRole1_new(Dz1Str peer_ip, 
																																 s64_t peer_port, 
																																 Dz1Str user, 
																																 Dz1Str pass, 
																																 bool_t test_session, 
																																 bool_t test_login_invalid, 
																																 bool_t test_session_maintain, 
																																 bool_t test_normal_pub, 
																																 bool_t test_pub_comm_tx_pdu, 
																																 bool_t test_pub_comm_rx_pdu, 
																																 bool_t test_login_duplicate, 
																																 bool_t test_invalid_sub, 
																																 bool_t test_subs_cancel, 
																																 bool_t test_pub_retry, Dz1Error *err);
static __inline__ TechnicalRegulation2TestConfiguration_clientRole1 *TechnicalRegulation2TestConfiguration_clientRole1_gen(Dz1Error *err) { return TechnicalRegulation2TestConfiguration_clientRole1_new(NULL, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulation2TestConfiguration_clientRole1_copy(TechnicalRegulation2TestConfiguration_clientRole1 *dst, TechnicalRegulation2TestConfiguration_clientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2TestConfiguration_clientRole1 *TechnicalRegulation2TestConfiguration_clientRole1_clone(TechnicalRegulation2TestConfiguration_clientRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2TestConfiguration_clientRole1_purge(TechnicalRegulation2TestConfiguration_clientRole1 *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2TestConfiguration_clientRole1_del(TechnicalRegulation2TestConfiguration_clientRole1 *p);
static __inline__ void TechnicalRegulation2TestConfiguration_clientRole1_delAndSetNull(void *ptr)
{
	TechnicalRegulation2TestConfiguration_clientRole1 **p = (TechnicalRegulation2TestConfiguration_clientRole1 **)ptr;
	if (p) { TechnicalRegulation2TestConfiguration_clientRole1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2TestConfiguration_clientRole1_dump(TechnicalRegulation2TestConfiguration_clientRole1 *p, int tab);
// TechnicalRegulation2TestConfiguration_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1TestConfiguration_serverRole1
typedef struct TechnicalRegulation1TestConfiguration_serverRole1
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	s64_t		local_port;
	bool_t		test_session;
	bool_t		test_login_retry;
	bool_t		test_normal_sub;
	bool_t		test_sub_retry;
	bool_t		test_invalid_pub;
} TechnicalRegulation1TestConfiguration_serverRole1;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1TestConfiguration_serverRole1 *TechnicalRegulation1TestConfiguration_serverRole1_new(s64_t local_port, 
																																 bool_t test_session, 
																																 bool_t test_login_retry, 
																																 bool_t test_normal_sub, 
																																 bool_t test_sub_retry, 
																																 bool_t test_invalid_pub, Dz1Error *err);
static __inline__ TechnicalRegulation1TestConfiguration_serverRole1 *TechnicalRegulation1TestConfiguration_serverRole1_gen(Dz1Error *err) { return TechnicalRegulation1TestConfiguration_serverRole1_new(0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulation1TestConfiguration_serverRole1_copy(TechnicalRegulation1TestConfiguration_serverRole1 *dst, TechnicalRegulation1TestConfiguration_serverRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1TestConfiguration_serverRole1 *TechnicalRegulation1TestConfiguration_serverRole1_clone(TechnicalRegulation1TestConfiguration_serverRole1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1TestConfiguration_serverRole1_purge(TechnicalRegulation1TestConfiguration_serverRole1 *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1TestConfiguration_serverRole1_del(TechnicalRegulation1TestConfiguration_serverRole1 *p);
static __inline__ void TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull(void *ptr)
{
	TechnicalRegulation1TestConfiguration_serverRole1 **p = (TechnicalRegulation1TestConfiguration_serverRole1 **)ptr;
	if (p) { TechnicalRegulation1TestConfiguration_serverRole1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1TestConfiguration_serverRole1_dump(TechnicalRegulation1TestConfiguration_serverRole1 *p, int tab);
// TechnicalRegulation1TestConfiguration_serverRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_clientRole2
typedef struct TechnicalRegulationTestConfiguration_clientRole2
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	Dz1Str		peer_ip;
	s64_t		peer_port;
	Dz1Str		user;
	Dz1Str		pass;
	bool_t		test_total;
	s64_t		expire_time;
} TechnicalRegulationTestConfiguration_clientRole2;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulationTestConfiguration_clientRole2 *TechnicalRegulationTestConfiguration_clientRole2_new(Dz1Str my_domain, 
																															   Dz1Str peer_domain, 
																															   Dz1Str peer_ip, 
																															   s64_t peer_port, 
																															   Dz1Str user, 
																															   Dz1Str pass, 
																															   bool_t test_total, 
																															   s64_t expire_time, Dz1Error *err);
static __inline__ TechnicalRegulationTestConfiguration_clientRole2 *TechnicalRegulationTestConfiguration_clientRole2_gen(Dz1Error *err) { return TechnicalRegulationTestConfiguration_clientRole2_new(NULL, NULL, NULL, 0, NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulationTestConfiguration_clientRole2_copy(TechnicalRegulationTestConfiguration_clientRole2 *dst, TechnicalRegulationTestConfiguration_clientRole2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulationTestConfiguration_clientRole2 *TechnicalRegulationTestConfiguration_clientRole2_clone(TechnicalRegulationTestConfiguration_clientRole2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_clientRole2_purge(TechnicalRegulationTestConfiguration_clientRole2 *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_clientRole2_del(TechnicalRegulationTestConfiguration_clientRole2 *p);
static __inline__ void TechnicalRegulationTestConfiguration_clientRole2_delAndSetNull(void *ptr)
{
	TechnicalRegulationTestConfiguration_clientRole2 **p = (TechnicalRegulationTestConfiguration_clientRole2 **)ptr;
	if (p) { TechnicalRegulationTestConfiguration_clientRole2_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_clientRole2_dump(TechnicalRegulationTestConfiguration_clientRole2 *p, int tab);
// TechnicalRegulationTestConfiguration_clientRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_serverRole2
typedef struct TechnicalRegulationTestConfiguration_serverRole2
{
	Dz1Str		my_domain;
	Dz1Str		peer_domain;
	s64_t		local_port;
	bool_t		test_total;
	s64_t		subs_timeout_s;
} TechnicalRegulationTestConfiguration_serverRole2;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulationTestConfiguration_serverRole2 *TechnicalRegulationTestConfiguration_serverRole2_new(Dz1Str my_domain, 
																															   Dz1Str peer_domain, 
																															   s64_t local_port, 
																															   bool_t test_total, 
																															   s64_t subs_timeout_s, Dz1Error *err);
static __inline__ TechnicalRegulationTestConfiguration_serverRole2 *TechnicalRegulationTestConfiguration_serverRole2_gen(Dz1Error *err) { return TechnicalRegulationTestConfiguration_serverRole2_new(NULL, NULL, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulationTestConfiguration_serverRole2_copy(TechnicalRegulationTestConfiguration_serverRole2 *dst, TechnicalRegulationTestConfiguration_serverRole2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulationTestConfiguration_serverRole2 *TechnicalRegulationTestConfiguration_serverRole2_clone(TechnicalRegulationTestConfiguration_serverRole2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_serverRole2_purge(TechnicalRegulationTestConfiguration_serverRole2 *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_serverRole2_del(TechnicalRegulationTestConfiguration_serverRole2 *p);
static __inline__ void TechnicalRegulationTestConfiguration_serverRole2_delAndSetNull(void *ptr)
{
	TechnicalRegulationTestConfiguration_serverRole2 **p = (TechnicalRegulationTestConfiguration_serverRole2 **)ptr;
	if (p) { TechnicalRegulationTestConfiguration_serverRole2_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_serverRole2_dump(TechnicalRegulationTestConfiguration_serverRole2 *p, int tab);
// TechnicalRegulationTestConfiguration_serverRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_duoClientRole
typedef struct TechnicalRegulationTestConfiguration_duoClientRole
{
	Dz1Str		peer_domain;
	Dz1Str		peer_ip;
	s64_t		peer_port;
	Dz1Str		my_domain1;
	Dz1Str		user1;
	Dz1Str		pass1;
	Dz1Str		my_domain2;
	Dz1Str		user2;
	Dz1Str		pass2;
	bool_t		test_duo_client;
} TechnicalRegulationTestConfiguration_duoClientRole;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulationTestConfiguration_duoClientRole *TechnicalRegulationTestConfiguration_duoClientRole_new(Dz1Str peer_domain, 
																																   Dz1Str peer_ip, 
																																   s64_t peer_port, 
																																   Dz1Str my_domain1, 
																																   Dz1Str user1, 
																																   Dz1Str pass1, 
																																   Dz1Str my_domain2, 
																																   Dz1Str user2, 
																																   Dz1Str pass2, 
																																   bool_t test_duo_client, Dz1Error *err);
static __inline__ TechnicalRegulationTestConfiguration_duoClientRole *TechnicalRegulationTestConfiguration_duoClientRole_gen(Dz1Error *err) { return TechnicalRegulationTestConfiguration_duoClientRole_new(NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulationTestConfiguration_duoClientRole_copy(TechnicalRegulationTestConfiguration_duoClientRole *dst, TechnicalRegulationTestConfiguration_duoClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulationTestConfiguration_duoClientRole *TechnicalRegulationTestConfiguration_duoClientRole_clone(TechnicalRegulationTestConfiguration_duoClientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_duoClientRole_purge(TechnicalRegulationTestConfiguration_duoClientRole *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_duoClientRole_del(TechnicalRegulationTestConfiguration_duoClientRole *p);
static __inline__ void TechnicalRegulationTestConfiguration_duoClientRole_delAndSetNull(void *ptr)
{
	TechnicalRegulationTestConfiguration_duoClientRole **p = (TechnicalRegulationTestConfiguration_duoClientRole **)ptr;
	if (p) { TechnicalRegulationTestConfiguration_duoClientRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_duoClientRole_dump(TechnicalRegulationTestConfiguration_duoClientRole *p, int tab);
// TechnicalRegulationTestConfiguration_duoClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_duoSessionRole
typedef struct TechnicalRegulationTestConfiguration_duoSessionRole
{
	bool_t		test_duo_session;
	Dz1Str		my_domain;
	Dz1Str		peer_ip;
	Dz1Str		peer_server_domain;
	s64_t		peer_server_port;
	Dz1Str		user;
	Dz1Str		pass;
	Dz1Str		peer_client_domain;
	s64_t		peer_client_port;
} TechnicalRegulationTestConfiguration_duoSessionRole;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulationTestConfiguration_duoSessionRole *TechnicalRegulationTestConfiguration_duoSessionRole_new(bool_t test_duo_session, 
																																	 Dz1Str my_domain, 
																																	 Dz1Str peer_ip, 
																																	 Dz1Str peer_server_domain, 
																																	 s64_t peer_server_port, 
																																	 Dz1Str user, 
																																	 Dz1Str pass, 
																																	 Dz1Str peer_client_domain, 
																																	 s64_t peer_client_port, Dz1Error *err);
static __inline__ TechnicalRegulationTestConfiguration_duoSessionRole *TechnicalRegulationTestConfiguration_duoSessionRole_gen(Dz1Error *err) { return TechnicalRegulationTestConfiguration_duoSessionRole_new(0, NULL, NULL, NULL, 0, NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TechnicalRegulationTestConfiguration_duoSessionRole_copy(TechnicalRegulationTestConfiguration_duoSessionRole *dst, TechnicalRegulationTestConfiguration_duoSessionRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulationTestConfiguration_duoSessionRole *TechnicalRegulationTestConfiguration_duoSessionRole_clone(TechnicalRegulationTestConfiguration_duoSessionRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_duoSessionRole_purge(TechnicalRegulationTestConfiguration_duoSessionRole *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_duoSessionRole_del(TechnicalRegulationTestConfiguration_duoSessionRole *p);
static __inline__ void TechnicalRegulationTestConfiguration_duoSessionRole_delAndSetNull(void *ptr)
{
	TechnicalRegulationTestConfiguration_duoSessionRole **p = (TechnicalRegulationTestConfiguration_duoSessionRole **)ptr;
	if (p) { TechnicalRegulationTestConfiguration_duoSessionRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulationTestConfiguration_duoSessionRole_dump(TechnicalRegulationTestConfiguration_duoSessionRole *p, int tab);
// TechnicalRegulationTestConfiguration_duoSessionRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestConfigurationPresent
typedef enum Iso14827TestConfigurationPresent
{
	Iso14827TestConfigurationPresent_centerClient2rse,
	Iso14827TestConfigurationPresent_rseServer2center,
	Iso14827TestConfigurationPresent_rseClient2center,
	Iso14827TestConfigurationPresent_centerServer2rse,
	Iso14827TestConfigurationPresent_signalserver2center,
	Iso14827TestConfigurationPresent_itsk00100_3c2cClient,
	Iso14827TestConfigurationPresent_itsk00100_3c2cServer,
	Iso14827TestConfigurationPresent_technical_regulation1_clientRole1,
	Iso14827TestConfigurationPresent_technical_regulation1_serverRole1,
	Iso14827TestConfigurationPresent_technical_regulation2_clientRole,
	Iso14827TestConfigurationPresent_technical_regulation1_clientRole2,
	Iso14827TestConfigurationPresent_technical_regulation1_serverRole2,
	Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole,
	Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole,
	Iso14827TestConfigurationPresent_technical_regulation2_clientRole2,
	Iso14827TestConfigurationPresent_technical_regulation2_serverRole2,
	Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole,
	Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole,
	Iso14827TestConfigurationPresent_max
} Iso14827TestConfigurationPresent;

DZ1_CPPLINK str_t Iso14827TestConfigurationPresentStrA(Iso14827TestConfigurationPresent v);
DZ1_CPPLINK Iso14827TestConfigurationPresent Iso14827TestConfigurationPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestConfigurationPresentStrW(Iso14827TestConfigurationPresent v);
DZ1_CPPLINK Iso14827TestConfigurationPresent Iso14827TestConfigurationPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestConfigurationPresentStr Iso14827TestConfigurationPresentStrW
#define Iso14827TestConfigurationPresentFromStr Iso14827TestConfigurationPresentFromStrW
#else // UNICODE
#define Iso14827TestConfigurationPresentStr Iso14827TestConfigurationPresentStrA
#define Iso14827TestConfigurationPresentFromStr Iso14827TestConfigurationPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestConfigurationPresentStr Iso14827TestConfigurationPresentStrA
#define Iso14827TestConfigurationPresentFromStr Iso14827TestConfigurationPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestConfigurationPresent *Iso14827TestConfigurationPresent_new(Iso14827TestConfigurationPresent *src, Dz1Error *err);
static __inline__ Iso14827TestConfigurationPresent *Iso14827TestConfigurationPresent_gen(Dz1Error *err) { Iso14827TestConfigurationPresent v = Iso14827TestConfigurationPresent_max; return Iso14827TestConfigurationPresent_new(&v, err); }
#define Iso14827TestConfigurationPresent_clone             Iso14827TestConfigurationPresent_new
static __inline__ void Iso14827TestConfigurationPresent_del(Iso14827TestConfigurationPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestConfigurationPresent_delAndSetNull(void *ptr)
{
	Iso14827TestConfigurationPresent **p = (Iso14827TestConfigurationPresent **)ptr;
	if (p != NULL) { Iso14827TestConfigurationPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestConfigurationPresent_dump(Iso14827TestConfigurationPresent *v, int tab);
// Iso14827TestConfigurationPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestConfiguration
typedef struct Iso14827TestConfiguration
{
	Iso14827TestConfigurationPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		PolicePrj4TestConfiguration_centerClient2rse				*centerClient2rse;
		PolicePrj4TestConfiguration_rseServer2center				*rseServer2center;
		PolicePrj4TestConfiguration_rseClient2center				*rseClient2center;
		PolicePrj4TestConfiguration_centerServer2rse				*centerServer2rse;
		PolicePrj4TestConfiguration_signalserverServer2center		*signalserver2center;
		ITSK00100_3TestConfigurationClientRole						*itsk00100_3c2cClient;
		ITSK00100_3TestConfigurationServerRole						*itsk00100_3c2cServer;
		TechnicalRegulation1TestConfiguration_clientRole1			*technical_regulation1_clientRole1;
		TechnicalRegulation1TestConfiguration_serverRole1			*technical_regulation1_serverRole1;
		TechnicalRegulation2TestConfiguration_clientRole1			*technical_regulation2_clientRole;
		TechnicalRegulationTestConfiguration_clientRole2			*technical_regulation1_clientRole2;
		TechnicalRegulationTestConfiguration_serverRole2			*technical_regulation1_serverRole2;
		TechnicalRegulationTestConfiguration_duoClientRole			*technical_regulation1_duoClientRole;
		TechnicalRegulationTestConfiguration_duoSessionRole			*technical_regulation1_duoSessionRole;
		TechnicalRegulationTestConfiguration_clientRole2			*technical_regulation2_clientRole2;
		TechnicalRegulationTestConfiguration_serverRole2			*technical_regulation2_serverRole2;
		TechnicalRegulationTestConfiguration_duoClientRole			*technical_regulation2_duoClientRole;
		TechnicalRegulationTestConfiguration_duoSessionRole			*technical_regulation2_duoSessionRole;
	} x;
} Iso14827TestConfiguration;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestConfiguration *Iso14827TestConfiguration_new(Iso14827TestConfigurationPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827TestConfiguration *Iso14827TestConfiguration_gen(Dz1Error *err) { return Iso14827TestConfiguration_new(Iso14827TestConfigurationPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Iso14827TestConfiguration_copy(Iso14827TestConfiguration *dst, Iso14827TestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestConfiguration *Iso14827TestConfiguration_clone(Iso14827TestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestConfiguration_purge(Iso14827TestConfiguration *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestConfiguration_del(Iso14827TestConfiguration *p);
static __inline__ void Iso14827TestConfiguration_delAndSetNull(void *ptr)
{
	Iso14827TestConfiguration **p = (Iso14827TestConfiguration **)ptr;
	if (p != NULL) { Iso14827TestConfiguration_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestConfiguration_dump(Iso14827TestConfiguration *p, int tab);
// Iso14827TestConfiguration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperC2CHookArg
typedef struct Iso14827TestHelperC2CHookArg
{
	Iso14827C2CAuthMsg		*msg;
	Dz1Str					 current_test;
	bool_t					 isReceived;
} Iso14827TestHelperC2CHookArg;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperC2CHookArg *Iso14827TestHelperC2CHookArg_new(Iso14827C2CAuthMsg *msg, 
																					   Dz1Str current_test, 
																					   bool_t isReceived, Dz1Error *err);
static __inline__ Iso14827TestHelperC2CHookArg *Iso14827TestHelperC2CHookArg_gen(Dz1Error *err) { return Iso14827TestHelperC2CHookArg_new(NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Iso14827TestHelperC2CHookArg_copy(Iso14827TestHelperC2CHookArg *dst, Iso14827TestHelperC2CHookArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperC2CHookArg *Iso14827TestHelperC2CHookArg_clone(Iso14827TestHelperC2CHookArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperC2CHookArg_purge(Iso14827TestHelperC2CHookArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperC2CHookArg_del(Iso14827TestHelperC2CHookArg *p);
static __inline__ void Iso14827TestHelperC2CHookArg_delAndSetNull(void *ptr)
{
	Iso14827TestHelperC2CHookArg **p = (Iso14827TestHelperC2CHookArg **)ptr;
	if (p) { Iso14827TestHelperC2CHookArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperC2CHookArg_dump(Iso14827TestHelperC2CHookArg *p, int tab);
// Iso14827TestHelperC2CHookArg
////////////////////////////////////////////////////////////////////////////////

#endif
