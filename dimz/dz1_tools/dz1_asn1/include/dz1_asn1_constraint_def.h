#ifndef _DZ1_TDC_DZ1_ASN1_CONSTRAINT_DEF_H_
#define _DZ1_TDC_DZ1_ASN1_CONSTRAINT_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_asn1_types_def.h"
#include "dz1_asn1_constraint_types.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescr
struct Dz1Asn1TypeDescr;
// Dz1Asn1TypeDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1MetaDataRealRangeInfo
struct Dz1Asn1MetaDataRealRangeInfo;
// Dz1Asn1MetaDataRealRangeInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructConstraintEntry
struct Dz1Asn1ConstructConstraintEntry;
// Dz1Asn1ConstructConstraintEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructConstraintGrp
struct Dz1Asn1ConstructConstraintGrp;
// Dz1Asn1ConstructConstraintGrp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructChildPresence
typedef enum Dz1Asn1ConstructChildPresence
{
	Dz1Asn1ConstructChildPresence_abssent,
	Dz1Asn1ConstructChildPresence_present,
	Dz1Asn1ConstructChildPresence_optional,
	Dz1Asn1ConstructChildPresence_max
} Dz1Asn1ConstructChildPresence;

DZ1_CPPLINK str_t Dz1Asn1ConstructChildPresenceStrA(Dz1Asn1ConstructChildPresence v);
DZ1_CPPLINK Dz1Asn1ConstructChildPresence Dz1Asn1ConstructChildPresenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1ConstructChildPresenceStrW(Dz1Asn1ConstructChildPresence v);
DZ1_CPPLINK Dz1Asn1ConstructChildPresence Dz1Asn1ConstructChildPresenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1ConstructChildPresenceStr Dz1Asn1ConstructChildPresenceStrW
#define Dz1Asn1ConstructChildPresenceFromStr Dz1Asn1ConstructChildPresenceFromStrW
#else // UNICODE
#define Dz1Asn1ConstructChildPresenceStr Dz1Asn1ConstructChildPresenceStrA
#define Dz1Asn1ConstructChildPresenceFromStr Dz1Asn1ConstructChildPresenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1ConstructChildPresenceStr Dz1Asn1ConstructChildPresenceStrA
#define Dz1Asn1ConstructChildPresenceFromStr Dz1Asn1ConstructChildPresenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1ConstructChildPresence *Dz1Asn1ConstructChildPresence_new(Dz1Asn1ConstructChildPresence *src, Dz1Error *err);
static __inline__ Dz1Asn1ConstructChildPresence *Dz1Asn1ConstructChildPresence_gen(Dz1Error *err) { Dz1Asn1ConstructChildPresence v = Dz1Asn1ConstructChildPresence_max; return Dz1Asn1ConstructChildPresence_new(&v, err); }
static __inline__ void Dz1Asn1ConstructChildPresence_del(Dz1Asn1ConstructChildPresence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1ConstructChildPresence_delAndSetNull(void *ptr)
{
	Dz1Asn1ConstructChildPresence **p = (Dz1Asn1ConstructChildPresence **)ptr;
	if (p != NULL) { Dz1Asn1ConstructChildPresence_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildPresenceA_dump(Dz1Asn1ConstructChildPresence *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildPresenceA_fdump(FILE *fp, Dz1Asn1ConstructChildPresence *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildPresenceW_dump(Dz1Asn1ConstructChildPresence *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildPresenceW_fdump(FILE *fp, Dz1Asn1ConstructChildPresence *v, int tab);
#ifdef UNICODE
#define Dz1Asn1ConstructChildPresence_dump Dz1Asn1ConstructChildPresenceW_dump
#define Dz1Asn1ConstructChildPresence_fdump Dz1Asn1ConstructChildPresenceW_fdump
#else //  UNICODE
#define Dz1Asn1ConstructChildPresence_dump Dz1Asn1ConstructChildPresenceA_dump
#define Dz1Asn1ConstructChildPresence_fdump Dz1Asn1ConstructChildPresenceA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1ConstructChildPresenceX_dump(Dz1Asn1ConstructChildPresence *p, int tab) { DZ1_DUMP(Dz1Asn1ConstructChildPresence, p, tab); }
static __inline__ void Dz1Asn1ConstructChildPresenceX_fdump(FILE *fp, Dz1Asn1ConstructChildPresence *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1ConstructChildPresence, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1ConstructChildPresence_dump Dz1Asn1ConstructChildPresenceA_dump
#define Dz1Asn1ConstructChildPresenceX_dump Dz1Asn1ConstructChildPresenceA_dump
#define Dz1Asn1ConstructChildPresence_fdump Dz1Asn1ConstructChildPresenceA_fdump
#define Dz1Asn1ConstructChildPresenceX_fdump Dz1Asn1ConstructChildPresenceA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1ConstructChildPresence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructChildConstraint
struct Dz1Asn1TypeDescr;

typedef struct Dz1Asn1ConstructChildConstraint
{
	struct Dz1Asn1TypeDescr				*childType;
	Dz1Asn1GetChildF					 getChildPtr;
	Dz1Binary							*preEncoded;
	Dz1Asn1ConstructChildPresence		 presence;
} Dz1Asn1ConstructChildConstraint;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1ConstructChildConstraint *Dz1Asn1ConstructChildConstraint_new(struct Dz1Asn1TypeDescr *childType_ref, 
																							 Dz1Asn1GetChildF getChildPtr, 
																							 Dz1Binary *preEncoded, 
																							 Dz1Asn1ConstructChildPresence presence, Dz1Error *err);
static __inline__ Dz1Asn1ConstructChildConstraint *Dz1Asn1ConstructChildConstraint_gen(Dz1Error *err) { return Dz1Asn1ConstructChildConstraint_new(NULL, NULL, NULL, Dz1Asn1ConstructChildPresence_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildConstraint_purge(Dz1Asn1ConstructChildConstraint *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildConstraint_del(Dz1Asn1ConstructChildConstraint *p);
static __inline__ void Dz1Asn1ConstructChildConstraint_delAndSetNull(void *ptr)
{
	Dz1Asn1ConstructChildConstraint **p = (Dz1Asn1ConstructChildConstraint **)ptr;
	if (p) { Dz1Asn1ConstructChildConstraint_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildConstraintA_dump(Dz1Asn1ConstructChildConstraint *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildConstraintA_fdump(FILE *fp, Dz1Asn1ConstructChildConstraint *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildConstraintW_dump(Dz1Asn1ConstructChildConstraint *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructChildConstraintW_fdump(FILE *fp, Dz1Asn1ConstructChildConstraint *p, int tab);
#ifdef UNICODE
#define Dz1Asn1ConstructChildConstraint_dump Dz1Asn1ConstructChildConstraintW_dump
#define Dz1Asn1ConstructChildConstraint_fdump Dz1Asn1ConstructChildConstraintW_fdump
#else //  UNICODE
#define Dz1Asn1ConstructChildConstraint_dump Dz1Asn1ConstructChildConstraintA_dump
#define Dz1Asn1ConstructChildConstraint_fdump Dz1Asn1ConstructChildConstraintA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1ConstructChildConstraintX_dump(Dz1Asn1ConstructChildConstraint *p, int tab) { DZ1_DUMP(Dz1Asn1ConstructChildConstraint, p, tab); }
static __inline__ void Dz1Asn1ConstructChildConstraintX_fdump(FILE *fp, Dz1Asn1ConstructChildConstraint *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1ConstructChildConstraint, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1ConstructChildConstraint_dump Dz1Asn1ConstructChildConstraintA_dump
#define Dz1Asn1ConstructChildConstraintX_dump Dz1Asn1ConstructChildConstraintA_dump
#define Dz1Asn1ConstructChildConstraint_fdump Dz1Asn1ConstructChildConstraintA_fdump
#define Dz1Asn1ConstructChildConstraintX_fdump Dz1Asn1ConstructChildConstraintA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1ConstructChildConstraint
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructConstraintTreeNodePresent
typedef enum Dz1Asn1ConstructConstraintTreeNodePresent
{
	Dz1Asn1ConstructConstraintTreeNodePresent_constraints,
	Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp,
	Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp,
	Dz1Asn1ConstructConstraintTreeNodePresent_max
} Dz1Asn1ConstructConstraintTreeNodePresent;

DZ1_CPPLINK str_t Dz1Asn1ConstructConstraintTreeNodePresentStrA(Dz1Asn1ConstructConstraintTreeNodePresent v);
DZ1_CPPLINK Dz1Asn1ConstructConstraintTreeNodePresent Dz1Asn1ConstructConstraintTreeNodePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1ConstructConstraintTreeNodePresentStrW(Dz1Asn1ConstructConstraintTreeNodePresent v);
DZ1_CPPLINK Dz1Asn1ConstructConstraintTreeNodePresent Dz1Asn1ConstructConstraintTreeNodePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1ConstructConstraintTreeNodePresentStr Dz1Asn1ConstructConstraintTreeNodePresentStrW
#define Dz1Asn1ConstructConstraintTreeNodePresentFromStr Dz1Asn1ConstructConstraintTreeNodePresentFromStrW
#else // UNICODE
#define Dz1Asn1ConstructConstraintTreeNodePresentStr Dz1Asn1ConstructConstraintTreeNodePresentStrA
#define Dz1Asn1ConstructConstraintTreeNodePresentFromStr Dz1Asn1ConstructConstraintTreeNodePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1ConstructConstraintTreeNodePresentStr Dz1Asn1ConstructConstraintTreeNodePresentStrA
#define Dz1Asn1ConstructConstraintTreeNodePresentFromStr Dz1Asn1ConstructConstraintTreeNodePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1ConstructConstraintTreeNodePresent *Dz1Asn1ConstructConstraintTreeNodePresent_new(Dz1Asn1ConstructConstraintTreeNodePresent *src, Dz1Error *err);
static __inline__ Dz1Asn1ConstructConstraintTreeNodePresent *Dz1Asn1ConstructConstraintTreeNodePresent_gen(Dz1Error *err) { Dz1Asn1ConstructConstraintTreeNodePresent v = Dz1Asn1ConstructConstraintTreeNodePresent_max; return Dz1Asn1ConstructConstraintTreeNodePresent_new(&v, err); }
static __inline__ void Dz1Asn1ConstructConstraintTreeNodePresent_del(Dz1Asn1ConstructConstraintTreeNodePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1ConstructConstraintTreeNodePresent_delAndSetNull(void *ptr)
{
	Dz1Asn1ConstructConstraintTreeNodePresent **p = (Dz1Asn1ConstructConstraintTreeNodePresent **)ptr;
	if (p != NULL) { Dz1Asn1ConstructConstraintTreeNodePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNodePresentA_dump(Dz1Asn1ConstructConstraintTreeNodePresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNodePresentA_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNodePresent *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNodePresentW_dump(Dz1Asn1ConstructConstraintTreeNodePresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNodePresentW_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNodePresent *v, int tab);
#ifdef UNICODE
#define Dz1Asn1ConstructConstraintTreeNodePresent_dump Dz1Asn1ConstructConstraintTreeNodePresentW_dump
#define Dz1Asn1ConstructConstraintTreeNodePresent_fdump Dz1Asn1ConstructConstraintTreeNodePresentW_fdump
#else //  UNICODE
#define Dz1Asn1ConstructConstraintTreeNodePresent_dump Dz1Asn1ConstructConstraintTreeNodePresentA_dump
#define Dz1Asn1ConstructConstraintTreeNodePresent_fdump Dz1Asn1ConstructConstraintTreeNodePresentA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1ConstructConstraintTreeNodePresentX_dump(Dz1Asn1ConstructConstraintTreeNodePresent *p, int tab) { DZ1_DUMP(Dz1Asn1ConstructConstraintTreeNodePresent, p, tab); }
static __inline__ void Dz1Asn1ConstructConstraintTreeNodePresentX_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNodePresent *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1ConstructConstraintTreeNodePresent, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1ConstructConstraintTreeNodePresent_dump Dz1Asn1ConstructConstraintTreeNodePresentA_dump
#define Dz1Asn1ConstructConstraintTreeNodePresentX_dump Dz1Asn1ConstructConstraintTreeNodePresentA_dump
#define Dz1Asn1ConstructConstraintTreeNodePresent_fdump Dz1Asn1ConstructConstraintTreeNodePresentA_fdump
#define Dz1Asn1ConstructConstraintTreeNodePresentX_fdump Dz1Asn1ConstructConstraintTreeNodePresentA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1ConstructConstraintTreeNodePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructConstraintTreeNode
struct Dz1Asn1ConstructConstraintEntry;
struct Dz1Asn1ConstructConstraintGrp;
struct Dz1Asn1ConstructConstraintGrp;
typedef struct Dz1Asn1ConstructConstraintTreeNode
{
	Dz1Asn1ConstructConstraintTreeNodePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		struct Dz1Asn1ConstructConstraintEntry		*constraints;
		struct Dz1Asn1ConstructConstraintGrp		*AND_grp;
		struct Dz1Asn1ConstructConstraintGrp		*OR_grp;
	} x;
} Dz1Asn1ConstructConstraintTreeNode;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1ConstructConstraintTreeNode *Dz1Asn1ConstructConstraintTreeNode_new(Dz1Asn1ConstructConstraintTreeNodePresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1Asn1ConstructConstraintTreeNode *Dz1Asn1ConstructConstraintTreeNode_gen(Dz1Error *err) { return Dz1Asn1ConstructConstraintTreeNode_new(Dz1Asn1ConstructConstraintTreeNodePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNode_purge(Dz1Asn1ConstructConstraintTreeNode *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNode_del(Dz1Asn1ConstructConstraintTreeNode *p);
static __inline__ void Dz1Asn1ConstructConstraintTreeNode_delAndSetNull(void *ptr)
{
	Dz1Asn1ConstructConstraintTreeNode **p = (Dz1Asn1ConstructConstraintTreeNode **)ptr;
	if (p != NULL) { Dz1Asn1ConstructConstraintTreeNode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNodeA_dump(Dz1Asn1ConstructConstraintTreeNode *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNodeA_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNode *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNodeW_dump(Dz1Asn1ConstructConstraintTreeNode *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstructConstraintTreeNodeW_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNode *p, int tab);
#ifdef UNICODE
#define Dz1Asn1ConstructConstraintTreeNode_dump Dz1Asn1ConstructConstraintTreeNodeW_dump
#define Dz1Asn1ConstructConstraintTreeNode_fdump Dz1Asn1ConstructConstraintTreeNodeW_fdump
#else //  UNICODE
#define Dz1Asn1ConstructConstraintTreeNode_dump Dz1Asn1ConstructConstraintTreeNodeA_dump
#define Dz1Asn1ConstructConstraintTreeNode_fdump Dz1Asn1ConstructConstraintTreeNodeA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1ConstructConstraintTreeNodeX_dump(Dz1Asn1ConstructConstraintTreeNode *p, int tab) { DZ1_DUMP(Dz1Asn1ConstructConstraintTreeNode, p, tab); }
static __inline__ void Dz1Asn1ConstructConstraintTreeNodeX_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNode *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1ConstructConstraintTreeNode, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1ConstructConstraintTreeNode_dump Dz1Asn1ConstructConstraintTreeNodeA_dump
#define Dz1Asn1ConstructConstraintTreeNodeX_dump Dz1Asn1ConstructConstraintTreeNodeA_dump
#define Dz1Asn1ConstructConstraintTreeNode_fdump Dz1Asn1ConstructConstraintTreeNodeA_fdump
#define Dz1Asn1ConstructConstraintTreeNodeX_fdump Dz1Asn1ConstructConstraintTreeNodeA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1ConstructConstraintTreeNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1KnownMultiplerStrlenF
typedef size_t (*Dz1Asn1KnownMultiplerStrlenF)(Dz1Asn1OctetStr *v);
// Dz1Asn1KnownMultiplerStrlenF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1KnownMultiplerStrToUCS4F
typedef u32_t *(*Dz1Asn1KnownMultiplerStrToUCS4F)(Dz1Asn1OctetStr *v, Dz1Error *err);
// Dz1Asn1KnownMultiplerStrToUCS4F
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1KnownMultiplerConstraints
typedef struct Dz1Asn1KnownMultiplerConstraints
{
	Dz1Asn1UTF8Str		*pattern;
} Dz1Asn1KnownMultiplerConstraints;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1KnownMultiplerConstraints *Dz1Asn1KnownMultiplerConstraints_new(Dz1Asn1UTF8Str *pattern, Dz1Error *err);
static __inline__ Dz1Asn1KnownMultiplerConstraints *Dz1Asn1KnownMultiplerConstraints_gen(Dz1Error *err) { return Dz1Asn1KnownMultiplerConstraints_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1KnownMultiplerConstraints_purge(Dz1Asn1KnownMultiplerConstraints *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1KnownMultiplerConstraints_del(Dz1Asn1KnownMultiplerConstraints *p);
static __inline__ void Dz1Asn1KnownMultiplerConstraints_delAndSetNull(void *ptr)
{
	Dz1Asn1KnownMultiplerConstraints **p = (Dz1Asn1KnownMultiplerConstraints **)ptr;
	if (p) { Dz1Asn1KnownMultiplerConstraints_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1KnownMultiplerConstraintsA_dump(Dz1Asn1KnownMultiplerConstraints *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1KnownMultiplerConstraintsA_fdump(FILE *fp, Dz1Asn1KnownMultiplerConstraints *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1KnownMultiplerConstraintsW_dump(Dz1Asn1KnownMultiplerConstraints *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1KnownMultiplerConstraintsW_fdump(FILE *fp, Dz1Asn1KnownMultiplerConstraints *p, int tab);
#ifdef UNICODE
#define Dz1Asn1KnownMultiplerConstraints_dump Dz1Asn1KnownMultiplerConstraintsW_dump
#define Dz1Asn1KnownMultiplerConstraints_fdump Dz1Asn1KnownMultiplerConstraintsW_fdump
#else //  UNICODE
#define Dz1Asn1KnownMultiplerConstraints_dump Dz1Asn1KnownMultiplerConstraintsA_dump
#define Dz1Asn1KnownMultiplerConstraints_fdump Dz1Asn1KnownMultiplerConstraintsA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1KnownMultiplerConstraintsX_dump(Dz1Asn1KnownMultiplerConstraints *p, int tab) { DZ1_DUMP(Dz1Asn1KnownMultiplerConstraints, p, tab); }
static __inline__ void Dz1Asn1KnownMultiplerConstraintsX_fdump(FILE *fp, Dz1Asn1KnownMultiplerConstraints *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1KnownMultiplerConstraints, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1KnownMultiplerConstraints_dump Dz1Asn1KnownMultiplerConstraintsA_dump
#define Dz1Asn1KnownMultiplerConstraintsX_dump Dz1Asn1KnownMultiplerConstraintsA_dump
#define Dz1Asn1KnownMultiplerConstraints_fdump Dz1Asn1KnownMultiplerConstraintsA_fdump
#define Dz1Asn1KnownMultiplerConstraintsX_fdump Dz1Asn1KnownMultiplerConstraintsA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1KnownMultiplerConstraints
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Constraint
struct Dz1Asn1MetaDataRealRangeInfo;
struct Dz1Asn1TypeDescr;
struct Dz1Asn1Constraint;

typedef struct Dz1Asn1Constraint
{
	void									*value;
	Dz1Asn1MetaDataRangeInfo				*i_ranges;
	struct Dz1Asn1MetaDataRealRangeInfo		*f_ranges;
	Dz1Asn1MetaDataRange					*size;
	struct Dz1Asn1TypeDescr					*type_of_any;
	struct Dz1Asn1Constraint				*component;
	Dz1Asn1ConstructConstraintTreeNode		*components;
	Dz1Asn1KnownMultiplerConstraints		*str_conf;
} Dz1Asn1Constraint;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Constraint *Dz1Asn1Constraint_new(void *value, 
																 Dz1Asn1MetaDataRangeInfo *i_ranges, 
																 struct Dz1Asn1MetaDataRealRangeInfo *f_ranges, 
																 Dz1Asn1MetaDataRange *size, 
																 struct Dz1Asn1TypeDescr *type_of_any, 
																 struct Dz1Asn1Constraint *component_ref, 
																 Dz1Asn1ConstructConstraintTreeNode *components, 
																 Dz1Asn1KnownMultiplerConstraints *str_conf, Dz1Error *err);
static __inline__ Dz1Asn1Constraint *Dz1Asn1Constraint_gen(Dz1Error *err) { return Dz1Asn1Constraint_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1Constraint_purge(Dz1Asn1Constraint *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1Constraint_del(Dz1Asn1Constraint *p);
static __inline__ void Dz1Asn1Constraint_delAndSetNull(void *ptr)
{
	Dz1Asn1Constraint **p = (Dz1Asn1Constraint **)ptr;
	if (p) { Dz1Asn1Constraint_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstraintA_dump(Dz1Asn1Constraint *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstraintA_fdump(FILE *fp, Dz1Asn1Constraint *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstraintW_dump(Dz1Asn1Constraint *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1ConstraintW_fdump(FILE *fp, Dz1Asn1Constraint *p, int tab);
#ifdef UNICODE
#define Dz1Asn1Constraint_dump Dz1Asn1ConstraintW_dump
#define Dz1Asn1Constraint_fdump Dz1Asn1ConstraintW_fdump
#else //  UNICODE
#define Dz1Asn1Constraint_dump Dz1Asn1ConstraintA_dump
#define Dz1Asn1Constraint_fdump Dz1Asn1ConstraintA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1ConstraintX_dump(Dz1Asn1Constraint *p, int tab) { DZ1_DUMP(Dz1Asn1Constraint, p, tab); }
static __inline__ void Dz1Asn1ConstraintX_fdump(FILE *fp, Dz1Asn1Constraint *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1Constraint, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1Constraint_dump Dz1Asn1ConstraintA_dump
#define Dz1Asn1ConstraintX_dump Dz1Asn1ConstraintA_dump
#define Dz1Asn1Constraint_fdump Dz1Asn1ConstraintA_fdump
#define Dz1Asn1ConstraintX_fdump Dz1Asn1ConstraintA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1Constraint
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeComformanceF
typedef bool_t (*Dz1Asn1TypeComformanceF)(Dz1Asn1Constraint *cons, void *user_data, bool_t *ret_is_ext);
// Dz1Asn1TypeComformanceF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeComformance
typedef struct Dz1Asn1TypeComformance
{
	Dz1Asn1Constraint			*cons;
	Dz1Asn1TypeComformanceF		 check;
} Dz1Asn1TypeComformance;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1TypeComformance *Dz1Asn1TypeComformance_new(Dz1Asn1Constraint *cons, 
																		   Dz1Asn1TypeComformanceF check, Dz1Error *err);
static __inline__ Dz1Asn1TypeComformance *Dz1Asn1TypeComformance_gen(Dz1Error *err) { return Dz1Asn1TypeComformance_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeComformance_purge(Dz1Asn1TypeComformance *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TypeComformance_del(Dz1Asn1TypeComformance *p);
static __inline__ void Dz1Asn1TypeComformance_delAndSetNull(void *ptr)
{
	Dz1Asn1TypeComformance **p = (Dz1Asn1TypeComformance **)ptr;
	if (p) { Dz1Asn1TypeComformance_del(*p); *p = NULL; }
}
// Dz1Asn1TypeComformance
////////////////////////////////////////////////////////////////////////////////

#endif
