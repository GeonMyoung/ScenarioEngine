#ifndef _DZ1_TDC_ISO14827_TEST_HELPER_TIMER_H_
#define _DZ1_TDC_ISO14827_TEST_HELPER_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"
#include "Iso14827TestHelperDef.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimerSession
typedef struct Iso14827TestHelperTimerSession
{
	Dz1Asn1UTF8Str		*my_domain;
	Dz1Asn1UTF8Str		*peer_domain;
	Dz1Asn1UTF8Str		*user;
	u32_t				 identifier;
} Iso14827TestHelperTimerSession;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperTimerSession *Iso14827TestHelperTimerSession_new(Dz1Asn1UTF8Str *my_domain, 
																						   Dz1Asn1UTF8Str *peer_domain, 
																						   Dz1Asn1UTF8Str *user, 
																						   u32_t identifier, Dz1Error *err);
static __inline__ Iso14827TestHelperTimerSession *Iso14827TestHelperTimerSession_gen(Dz1Error *err) { return Iso14827TestHelperTimerSession_new(NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerSession_purge(Iso14827TestHelperTimerSession *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerSession_del(Iso14827TestHelperTimerSession *p);
static __inline__ void Iso14827TestHelperTimerSession_delAndSetNull(void *ptr)
{
	Iso14827TestHelperTimerSession **p = (Iso14827TestHelperTimerSession **)ptr;
	if (p) { Iso14827TestHelperTimerSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerSession_dump(Iso14827TestHelperTimerSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Iso14827TestHelperTimerSession_cmp(Iso14827TestHelperTimerSession *a, Iso14827TestHelperTimerSession *b); 
// Iso14827TestHelperTimerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimerDuo
typedef struct Iso14827TestHelperTimerDuo
{
	ItsIso14827DomainType		 my_type;
	Dz1Asn1UTF8Str				*my_domain;
	Dz1Asn1UTF8Str				*peer_domain;
	Dz1Asn1OctetStr				*user;
	u32_t						 identifier;
} Iso14827TestHelperTimerDuo;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperTimerDuo *Iso14827TestHelperTimerDuo_new(ItsIso14827DomainType my_type, 
																				   Dz1Asn1UTF8Str *my_domain, 
																				   Dz1Asn1UTF8Str *peer_domain, 
																				   Dz1Asn1OctetStr *user, 
																				   u32_t identifier, Dz1Error *err);
static __inline__ Iso14827TestHelperTimerDuo *Iso14827TestHelperTimerDuo_gen(Dz1Error *err) { return Iso14827TestHelperTimerDuo_new(ItsIso14827DomainType_max, NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerDuo_purge(Iso14827TestHelperTimerDuo *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerDuo_del(Iso14827TestHelperTimerDuo *p);
static __inline__ void Iso14827TestHelperTimerDuo_delAndSetNull(void *ptr)
{
	Iso14827TestHelperTimerDuo **p = (Iso14827TestHelperTimerDuo **)ptr;
	if (p) { Iso14827TestHelperTimerDuo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerDuo_dump(Iso14827TestHelperTimerDuo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Iso14827TestHelperTimerDuo_cmp(Iso14827TestHelperTimerDuo *a, Iso14827TestHelperTimerDuo *b); 
// Iso14827TestHelperTimerDuo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimerED
typedef struct Iso14827TestHelperTimerED
{
	Dz1Asn1OctetStr		*user;
	Dz1Str				 oidStr;
	u32_t				 subID;
	u32_t				 identifier;
} Iso14827TestHelperTimerED;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperTimerED *Iso14827TestHelperTimerED_new(Dz1Asn1OctetStr *user, 
																				 Dz1Str oidStr, 
																				 u32_t subID, 
																				 u32_t identifier, Dz1Error *err);
static __inline__ Iso14827TestHelperTimerED *Iso14827TestHelperTimerED_gen(Dz1Error *err) { return Iso14827TestHelperTimerED_new(NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerED_purge(Iso14827TestHelperTimerED *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerED_del(Iso14827TestHelperTimerED *p);
static __inline__ void Iso14827TestHelperTimerED_delAndSetNull(void *ptr)
{
	Iso14827TestHelperTimerED **p = (Iso14827TestHelperTimerED **)ptr;
	if (p) { Iso14827TestHelperTimerED_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerED_dump(Iso14827TestHelperTimerED *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Iso14827TestHelperTimerED_cmp(Iso14827TestHelperTimerED *a, Iso14827TestHelperTimerED *b); 
// Iso14827TestHelperTimerED
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimerPresent
typedef enum Iso14827TestHelperTimerPresent
{
	Iso14827TestHelperTimerPresent_general,
	Iso14827TestHelperTimerPresent_ed,
	Iso14827TestHelperTimerPresent_client,
	Iso14827TestHelperTimerPresent_duo,
	Iso14827TestHelperTimerPresent_max
} Iso14827TestHelperTimerPresent;

DZ1_CPPLINK str_t Iso14827TestHelperTimerPresentStrA(Iso14827TestHelperTimerPresent v);
DZ1_CPPLINK Iso14827TestHelperTimerPresent Iso14827TestHelperTimerPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Iso14827TestHelperTimerPresentStrW(Iso14827TestHelperTimerPresent v);
DZ1_CPPLINK Iso14827TestHelperTimerPresent Iso14827TestHelperTimerPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Iso14827TestHelperTimerPresentStr Iso14827TestHelperTimerPresentStrW
#define Iso14827TestHelperTimerPresentFromStr Iso14827TestHelperTimerPresentFromStrW
#else // UNICODE
#define Iso14827TestHelperTimerPresentStr Iso14827TestHelperTimerPresentStrA
#define Iso14827TestHelperTimerPresentFromStr Iso14827TestHelperTimerPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Iso14827TestHelperTimerPresentStr Iso14827TestHelperTimerPresentStrA
#define Iso14827TestHelperTimerPresentFromStr Iso14827TestHelperTimerPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperTimerPresent *Iso14827TestHelperTimerPresent_new(Iso14827TestHelperTimerPresent *src, Dz1Error *err);
static __inline__ Iso14827TestHelperTimerPresent *Iso14827TestHelperTimerPresent_gen(Dz1Error *err) { Iso14827TestHelperTimerPresent v = Iso14827TestHelperTimerPresent_max; return Iso14827TestHelperTimerPresent_new(&v, err); }
static __inline__ void Iso14827TestHelperTimerPresent_del(Iso14827TestHelperTimerPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Iso14827TestHelperTimerPresent_delAndSetNull(void *ptr)
{
	Iso14827TestHelperTimerPresent **p = (Iso14827TestHelperTimerPresent **)ptr;
	if (p != NULL) { Iso14827TestHelperTimerPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimerPresent_dump(Iso14827TestHelperTimerPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Iso14827TestHelperTimerPresent_cmp(Iso14827TestHelperTimerPresent *a, Iso14827TestHelperTimerPresent *b);
// Iso14827TestHelperTimerPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimer
typedef struct Iso14827TestHelperTimer
{
	Iso14827TestHelperTimerPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t								 general;
		Iso14827TestHelperTimerED			*ed;
		Iso14827TestHelperTimerSession		*client;
		Iso14827TestHelperTimerDuo			*duo;
	} x;
} Iso14827TestHelperTimer;

DZ1_CPPLINK DZ1_DLLPORT Iso14827TestHelperTimer *Iso14827TestHelperTimer_new(Iso14827TestHelperTimerPresent present, void *ptr, Dz1Error *err);
static __inline__ Iso14827TestHelperTimer *Iso14827TestHelperTimer_gen(Dz1Error *err) { return Iso14827TestHelperTimer_new(Iso14827TestHelperTimerPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimer_purge(Iso14827TestHelperTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimer_del(Iso14827TestHelperTimer *p);
static __inline__ void Iso14827TestHelperTimer_delAndSetNull(void *ptr)
{
	Iso14827TestHelperTimer **p = (Iso14827TestHelperTimer **)ptr;
	if (p != NULL) { Iso14827TestHelperTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Iso14827TestHelperTimer_dump(Iso14827TestHelperTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Iso14827TestHelperTimer_cmp(Iso14827TestHelperTimer *a, Iso14827TestHelperTimer *b);
// Iso14827TestHelperTimer
////////////////////////////////////////////////////////////////////////////////

#endif
