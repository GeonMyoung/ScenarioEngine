#ifndef _DZ1_TDC_DZ1_ASN1_TYPEDESCR_DEF_H_
#define _DZ1_TDC_DZ1_ASN1_TYPEDESCR_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_constraint_def.h"
#include "dz1_asn1_codec_ber_def.h"
#include "dz1_asn1_codec_per_def.h"

////////////////////////////////////////////////////////////////////////////////
// _declare_Dz1Asn1TypeDescr
struct Dz1Asn1TypeDescr;
// _declare_Dz1Asn1TypeDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeAPI
struct Dz1Asn1TypeAPI;
// Dz1Asn1TypeAPI
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescrChild
struct Dz1Asn1TypeDescrChild;
// Dz1Asn1TypeDescrChild
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1DefaultInfo
typedef struct Dz1Asn1DefaultInfo
{
	void			*value;
	Dz1CmpFunc		 is_same;
} Dz1Asn1DefaultInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1DefaultInfo *Dz1Asn1DefaultInfo_new(void *value, 
																   Dz1CmpFunc is_same, Dz1Error *err);
static __inline__ Dz1Asn1DefaultInfo *Dz1Asn1DefaultInfo_gen(Dz1Error *err) { return Dz1Asn1DefaultInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1DefaultInfo_purge(Dz1Asn1DefaultInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1DefaultInfo_del(Dz1Asn1DefaultInfo *p);
static __inline__ void Dz1Asn1DefaultInfo_delAndSetNull(void *ptr)
{
	Dz1Asn1DefaultInfo **p = (Dz1Asn1DefaultInfo **)ptr;
	if (p) { Dz1Asn1DefaultInfo_del(*p); *p = NULL; }
}
// Dz1Asn1DefaultInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescrPresencePresent
typedef enum Dz1Asn1TypeDescrPresencePresent
{
	Dz1Asn1TypeDescrPresencePresent_opt,
	Dz1Asn1TypeDescrPresencePresent_dflt,
	Dz1Asn1TypeDescrPresencePresent_max
} Dz1Asn1TypeDescrPresencePresent;

DZ1_CPPLINK str_t Dz1Asn1TypeDescrPresencePresentStrA(Dz1Asn1TypeDescrPresencePresent v);
DZ1_CPPLINK Dz1Asn1TypeDescrPresencePresent Dz1Asn1TypeDescrPresencePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1TypeDescrPresencePresentStrW(Dz1Asn1TypeDescrPresencePresent v);
DZ1_CPPLINK Dz1Asn1TypeDescrPresencePresent Dz1Asn1TypeDescrPresencePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1TypeDescrPresencePresentStr Dz1Asn1TypeDescrPresencePresentStrW
#define Dz1Asn1TypeDescrPresencePresentFromStr Dz1Asn1TypeDescrPresencePresentFromStrW
#else // UNICODE
#define Dz1Asn1TypeDescrPresencePresentStr Dz1Asn1TypeDescrPresencePresentStrA
#define Dz1Asn1TypeDescrPresencePresentFromStr Dz1Asn1TypeDescrPresencePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1TypeDescrPresencePresentStr Dz1Asn1TypeDescrPresencePresentStrA
#define Dz1Asn1TypeDescrPresencePresentFromStr Dz1Asn1TypeDescrPresencePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1TypeDescrPresencePresent *Dz1Asn1TypeDescrPresencePresent_new(Dz1Asn1TypeDescrPresencePresent *src, Dz1Error *err);
static __inline__ Dz1Asn1TypeDescrPresencePresent *Dz1Asn1TypeDescrPresencePresent_gen(Dz1Error *err) { Dz1Asn1TypeDescrPresencePresent v = Dz1Asn1TypeDescrPresencePresent_max; return Dz1Asn1TypeDescrPresencePresent_new(&v, err); }
static __inline__ void Dz1Asn1TypeDescrPresencePresent_del(Dz1Asn1TypeDescrPresencePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1TypeDescrPresencePresent_delAndSetNull(void *ptr)
{
	Dz1Asn1TypeDescrPresencePresent **p = (Dz1Asn1TypeDescrPresencePresent **)ptr;
	if (p != NULL) { Dz1Asn1TypeDescrPresencePresent_del(*p); *p = NULL; }
}
// Dz1Asn1TypeDescrPresencePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescrPresence
typedef struct Dz1Asn1TypeDescrPresence
{
	Dz1Asn1TypeDescrPresencePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t					*opt;
		Dz1Asn1DefaultInfo		*dflt;
	} x;
} Dz1Asn1TypeDescrPresence;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1TypeDescrPresence *Dz1Asn1TypeDescrPresence_new(Dz1Asn1TypeDescrPresencePresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1Asn1TypeDescrPresence *Dz1Asn1TypeDescrPresence_gen(Dz1Error *err) { return Dz1Asn1TypeDescrPresence_new(Dz1Asn1TypeDescrPresencePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeDescrPresence_purge(Dz1Asn1TypeDescrPresence *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeDescrPresence_del(Dz1Asn1TypeDescrPresence *p);
static __inline__ void Dz1Asn1TypeDescrPresence_delAndSetNull(void *ptr)
{
	Dz1Asn1TypeDescrPresence **p = (Dz1Asn1TypeDescrPresence **)ptr;
	if (p != NULL) { Dz1Asn1TypeDescrPresence_del(*p); *p = NULL; }
}
// Dz1Asn1TypeDescrPresence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1FinalizeF
typedef bool_t (*Dz1Asn1FinalizeF)(
					void *dst, 
					Dz1Asn1WipValue *src, 
					struct Dz1Asn1TypeDescr *descr, 
					Dz1Error *errp);
// Dz1Asn1FinalizeF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescr
struct Dz1Asn1TypeDescrChild;
struct Dz1Asn1TypeAPI;
struct Dz1Asn1TypeAPI;

typedef struct Dz1Asn1TypeDescr
{
	Dz1Asn1UTF8Str					*name;
	Dz1Asn1Tag						*tag;
	struct Dz1Asn1TypeDescrChild	*childs;
	Dz1Asn1TypeComformance			*conformance;
	struct Dz1Asn1TypeAPI			*wip_api;
	Dz1Asn1DataBerEncF				 ber_enc;
	Dz1Asn1DataBerDecF				 ber_dec;
	Dz1Asn1FinalizeF				 finalize;
	struct Dz1Asn1TypeAPI			*user_api;
} Dz1Asn1TypeDescr;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1TypeDescr *Dz1Asn1TypeDescr_new(Dz1Asn1UTF8Str *name, 
															   Dz1Asn1Tag *tag_ref, 
															   struct Dz1Asn1TypeDescrChild *childs_ref, 
															   Dz1Asn1TypeComformance *conformance_ref, 
															   struct Dz1Asn1TypeAPI *wip_api_ref, 
															   Dz1Asn1DataBerEncF ber_enc, 
															   Dz1Asn1DataBerDecF ber_dec, 
															   Dz1Asn1FinalizeF finalize, 
															   struct Dz1Asn1TypeAPI *user_api_ref, Dz1Error *err);
static __inline__ Dz1Asn1TypeDescr *Dz1Asn1TypeDescr_gen(Dz1Error *err) { return Dz1Asn1TypeDescr_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeDescr_purge(Dz1Asn1TypeDescr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeDescr_del(Dz1Asn1TypeDescr *p);
static __inline__ void Dz1Asn1TypeDescr_delAndSetNull(void *ptr)
{
	Dz1Asn1TypeDescr **p = (Dz1Asn1TypeDescr **)ptr;
	if (p) { Dz1Asn1TypeDescr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeDescrA_dump(Dz1Asn1TypeDescr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeDescrA_fdump(FILE *fp, Dz1Asn1TypeDescr *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeDescrW_dump(Dz1Asn1TypeDescr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeDescrW_fdump(FILE *fp, Dz1Asn1TypeDescr *p, int tab);
#ifdef UNICODE
#define Dz1Asn1TypeDescr_dump Dz1Asn1TypeDescrW_dump
#define Dz1Asn1TypeDescr_fdump Dz1Asn1TypeDescrW_fdump
#else //  UNICODE
#define Dz1Asn1TypeDescr_dump Dz1Asn1TypeDescrA_dump
#define Dz1Asn1TypeDescr_fdump Dz1Asn1TypeDescrA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1TypeDescrX_dump(Dz1Asn1TypeDescr *p, int tab) { DZ1_DUMP(Dz1Asn1TypeDescr, p, tab); }
static __inline__ void Dz1Asn1TypeDescrX_fdump(FILE *fp, Dz1Asn1TypeDescr *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1TypeDescr, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1TypeDescr_dump Dz1Asn1TypeDescrA_dump
#define Dz1Asn1TypeDescrX_dump Dz1Asn1TypeDescrA_dump
#define Dz1Asn1TypeDescr_fdump Dz1Asn1TypeDescrA_fdump
#define Dz1Asn1TypeDescrX_fdump Dz1Asn1TypeDescrA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1TypeDescr
////////////////////////////////////////////////////////////////////////////////

#endif
