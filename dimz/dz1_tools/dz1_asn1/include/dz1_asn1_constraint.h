#ifndef DZ1_ASN1_CONSTRAINT_H
#define DZ1_ASN1_CONSTRAINT_H

#include <dz1_asn1_constraint_def.h>

///////////////////////////////////////////////////////////////////////////////
// Construct Child Constraint
DZ1_CPPLINK bool_t	 Dz1Asn1ConstructChildConstraint_match(Dz1Asn1ConstructChildConstraint *p, void *parentPtr);
// Construct Child Constraint
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Constraint Entry
typedef struct Dz1Asn1ConstructConstraintEntry									// Single Construct Constraint
{	// full components = full childs, partial components = subset of childs
	Dz1Asn1ConstructChildConstraint			*childs;
	u32_t									 childs_cnt;
} Dz1Asn1ConstructConstraintEntry;
DZ1_CPPLINK Dz1Asn1ConstructConstraintEntry	*Dz1Asn1ConstructConstraintEntry_new(Dz1Asn1ConstructChildConstraint *childs, u32_t childs_cnt, Dz1Error *err);
DZ1_CPPLINK void							 Dz1Asn1ConstructConstraintEntry_del(Dz1Asn1ConstructConstraintEntry *p);
static __inline__ void						 Dz1Asn1ConstructConstraintEntry_delAndSetNull(void *pptr)
{
	Dz1Asn1ConstructConstraintEntry **p = (Dz1Asn1ConstructConstraintEntry **)pptr;
	if (p) { Dz1Asn1ConstructConstraintEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK void							 Dz1Asn1ConstructConstraintEntryA_dump(Dz1Asn1ConstructConstraintEntry *p, int tab);
DZ1_CPPLINK void							 Dz1Asn1ConstructConstraintEntryA_fdump(FILE *fp, Dz1Asn1ConstructConstraintEntry *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void							 Dz1Asn1ConstructConstraintEntryW_dump(Dz1Asn1ConstructConstraintEntry *p, int tab);
DZ1_CPPLINK void							 Dz1Asn1ConstructConstraintEntryW_fdump(FILE *fp, Dz1Asn1ConstructConstraintEntry *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1ConstructConstraintEntry_dump Dz1Asn1ConstructConstraintEntryW_dump
#define										 Dz1Asn1ConstructConstraintEntry_fdump Dz1Asn1ConstructConstraintEntryW_fdump
#else // UNICODE
#define										 Dz1Asn1ConstructConstraintEntry_dump Dz1Asn1ConstructConstraintEntryA_dump
#define										 Dz1Asn1ConstructConstraintEntry_fdump Dz1Asn1ConstructConstraintEntryA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1ConstructConstraintEntry_dump Dz1Asn1ConstructConstraintEntryA_dump
#define										 Dz1Asn1ConstructConstraintEntry_fdump Dz1Asn1ConstructConstraintEntryA_fdump
#endif // UNIX_SYSTEM

DZ1_CPPLINK bool_t							 Dz1Asn1ConstructConstraintEntry_match(Dz1Asn1ConstructConstraintEntry *p, void *ptr);
// Construct Constraint Entry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Constraint Group
struct Dz1Asn1ConstructConstraintTreeNode;
typedef struct Dz1Asn1ConstructConstraintGrp									// Set of Construct Constraints
{
	struct Dz1Asn1ConstructConstraintTreeNode	*collection_arr;
	u32_t										 collection_arr_cnt;
} Dz1Asn1ConstructConstraintGrp;
DZ1_CPPLINK Dz1Asn1ConstructConstraintGrp	*Dz1Asn1ConstructConstraintGrp_new(struct Dz1Asn1ConstructConstraintTreeNode *arr, u32_t cnt, Dz1Error *err);
DZ1_CPPLINK void							 Dz1Asn1ConstructConstraintGrp_del(Dz1Asn1ConstructConstraintGrp *p);
static __inline__ void						 Dz1Asn1ConstructConstraintGrp_delAndSetNull(void *pptr)
{
	Dz1Asn1ConstructConstraintGrp **p = (Dz1Asn1ConstructConstraintGrp **)pptr;
	if (p) { Dz1Asn1ConstructConstraintGrp_del(*p); *p = NULL; }
}
DZ1_CPPLINK void						 Dz1Asn1ConstructConstraintGrpA_dump(Dz1Asn1ConstructConstraintGrp *p, int tab);
DZ1_CPPLINK void						 Dz1Asn1ConstructConstraintGrpA_fdump(FILE *fp, Dz1Asn1ConstructConstraintGrp *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void						 Dz1Asn1ConstructConstraintGrpW_dump(Dz1Asn1ConstructConstraintGrp *p, int tab);
DZ1_CPPLINK void						 Dz1Asn1ConstructConstraintGrpW_fdump(FILE *fp, Dz1Asn1ConstructConstraintGrp *p, int tab);
#ifdef UNICODE
#define									 Dz1Asn1ConstructConstraintGrp_dump Dz1Asn1ConstructConstraintGrpW_dump
#define									 Dz1Asn1ConstructConstraintGrp_fdump Dz1Asn1ConstructConstraintGrpW_fdump
#else // UNICODE
#define									 Dz1Asn1ConstructConstraintGrp_dump Dz1Asn1ConstructConstraintGrpA_dump
#define									 Dz1Asn1ConstructConstraintGrp_fdump Dz1Asn1ConstructConstraintGrpA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define									 Dz1Asn1ConstructConstraintGrp_dump Dz1Asn1ConstructConstraintGrpA_dump
#define									 Dz1Asn1ConstructConstraintGrp_fdump Dz1Asn1ConstructConstraintGrpA_fdump
#endif // UNIX_SYSTEM

DZ1_CPPLINK bool_t Dz1Asn1ConstructConstraintGrp_matchALL(Dz1Asn1ConstructConstraintGrp *p, void *ptr);
DZ1_CPPLINK bool_t Dz1Asn1ConstructConstraintGrp_matchANY(Dz1Asn1ConstructConstraintGrp *p, void *ptr);
// Construct Constraint Group
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Constraints Tree Node
DZ1_CPPLINK bool_t	 Dz1Asn1ConstructConstraintTreeNode_match(Dz1Asn1ConstructConstraintTreeNode *p, void *ptr);
// Construct Constraints Tree Node
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ANY
// struct Dz1Asn1TypeDescr;
// typedef struct Dz1Asn1AnyConstraints
// {
// 	// type
// 	struct Dz1Asn1TypeDescr						*possible_type_arr;
// 	u32_t										 possible_type_arr_cnt;
// 	struct Dz1Asn1TypeDescr						*(*resolver)(void *parentPtr);
// } Dz1Asn1AnyConstraints;
// ANY
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Conformance Tool
static __inline__ bool_t	 Dz1Asn1Constraint_none(Dz1Asn1Constraint *cons, void *ptr, bool_t *ret_is_ext) { return TRUE; }
static __inline__ bool_t	 Dz1Asn1Constraint_sizeMatch(Dz1Asn1Constraint *p, Dz1Asn1Int v, bool_t *ret_is_ext)
{
	return Dz1Asn1MetaDataRange_match(p->size, v);
}
static __inline__ bool_t	 Dz1Asn1Constraint_intRangeMatch(Dz1Asn1Constraint *p, Dz1Asn1Int v, bool_t *ret_is_ext)
{
	return Dz1Asn1MetaDataRangeInfo_match(p->i_ranges, v, ret_is_ext);
}
static __inline__ bool_t	 Dz1Asn1Constraint_realRangeMatch(Dz1Asn1Constraint *p, Dz1Asn1Real v, bool_t *ret_is_ext)
{
	return Dz1Asn1MetaDataRealRangeInfo_match(p->f_ranges, v, ret_is_ext);
}

DZ1_CPPLINK size_t Dz1Asn1ASCIIStr_strlen(Dz1Asn1OctetStr *p);
DZ1_CPPLINK u32_t *Dz1Asn1ASCIIStr_toUCS4(Dz1Asn1OctetStr *p, Dz1Error *err);

typedef struct Dz1Asn1StringConformanceAPI
{
	Dz1Asn1KnownMultiplerStrlenF     getLen;
	Dz1Asn1KnownMultiplerStrToUCS4F  toUCS4;
} Dz1Asn1StringConformanceAPI;

DZ1_CPPLINK bool_t	 Dz1Asn1Constraint_KMS_match(Dz1Asn1Constraint *p, Dz1Asn1StringConformanceAPI *api, Dz1Asn1OctetStr *v, bool_t *ret_is_ext);
DZ1_CPPLINK bool_t	 Dz1Asn1Construct_conformance(Dz1Asn1Constraint *cons, void *ptr, bool_t *ret_is_ext);

typedef enum Dz1Asn1ListTravelRet
{
	Dz1Asn1ListTravelRet_error = -1,
	Dz1Asn1ListTravelRet_no_issue,
	Dz1Asn1ListTravelRet_stop
} Dz1Asn1ListTravelRet;

typedef struct Dz1Asn1List	// List Caster
{
	void				 *storage;
	size_t				  (*count)(struct Dz1Asn1List *p);
	Dz1Asn1ListTravelRet  (*travel)(struct Dz1Asn1List *p, bool_t go_fwd, Dz1Asn1ListTravelRet (*func)(void *ptr, void *e, Dz1Error *err), void *ptr, Dz1Error *err);
} Dz1Asn1List;
#define Dz1Asn1List_add(list_p, node_p, ep)				list_p##->add(list_p, node_p, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Array_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)
{
	Dz1Asn1List *v = (Dz1Asn1List *)dataPtr;
	size_t cnt = v->count(v);
	return Dz1Asn1Constraint_sizeMatch(p, (Dz1Asn1Int)cnt & 0xFFFFFFFF, ret_is_ext);
}
// Conformance Tool
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Type Constraint
#define						 Dz1Asn1Any_conformance			Dz1Asn1Constraint_none										// ANY
#define						 Dz1Asn1Choice_conformance		Dz1Asn1Construct_conformance								// CHOICE

#define						 Dz1Asn1Bool_conformance		Dz1Asn1Constraint_none										// 1
static __inline__ bool_t	 Dz1Asn1Int_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)			// 2
{
	Dz1Asn1Int *v = (Dz1Asn1Int *)dataPtr;
	return Dz1Asn1Constraint_intRangeMatch(p, *v, ret_is_ext);
}
DZ1_CPPLINK bool_t			 Dz1Asn1BitStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext);		// 3
static __inline__ bool_t	 Dz1Asn1OctetStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)		// 4
{
	Dz1Asn1OctetStr *v = (Dz1Asn1OctetStr *)dataPtr;
	return Dz1Asn1Constraint_sizeMatch(p, (Dz1Asn1Int)v->size & 0xFFFFFFFF, ret_is_ext);
}
#define						 Dz1Asn1Null_conformance		Dz1Asn1Constraint_none										// 5
#define						 Dz1Asn1OID_conformance			Dz1Asn1Constraint_none										// 6
static __inline__ bool_t	 Dz1Asn1ObjDescr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)		// 7
{
	Dz1Asn1ObjDescr *v = (Dz1Asn1ObjDescr *)dataPtr;
	return Dz1Asn1Constraint_sizeMatch(p, (Dz1Asn1Int)v->size & 0xFFFFFFFF, ret_is_ext);
}
#define						 Dz1Asn1External_conformance	Dz1Asn1Sequence_conformance									// 8
#define						 Dz1Asn1InstanceOf_conformance	Dz1Asn1Sequence_conformance									// 8
static __inline__ bool_t	 Dz1Asn1Real_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)			// 9
{
	Dz1Asn1Real *v = (Dz1Asn1Real *)dataPtr;
	return Dz1Asn1Constraint_realRangeMatch(p, *v, ret_is_ext);
}
#define						 Dz1Asn1Enum_conformance		Dz1Asn1Constraint_none										// 10
#define						 Dz1Asn1EmbPdv_conformance		Dz1Asn1Sequence_conformance									// 11
static __inline__ bool_t	 Dz1Asn1UTF8Str_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)		// 12
{	// Dz1Asn1UTF8Str
	Dz1Asn1UTF8Str *v = (Dz1Asn1UTF8Str *)dataPtr;
	Dz1Asn1StringConformanceAPI api = { Dz1Asn1UTF8Str_strlen, Dz1Asn1UTF8Str_toUCS4 };
	return Dz1Asn1Constraint_KMS_match(p, &api, v, ret_is_ext);
}
#define						 Dz1Asn1RelOID_conformance		Dz1Asn1Constraint_none										// 13
#define						 Dz1Asn1Time_conformance		Dz1Asn1Constraint_none										// 14
																														// 15 : Reserved
#define						 Dz1Asn1Sequence_conformance	Dz1Asn1Construct_conformance								// 16
#define						 Dz1Asn1SequenceOf_conformance	Dz1Asn1Array_conformance									// 16

#define						 Dz1Asn1Set_conformance			Dz1Asn1Construct_conformance								// 17
#define						 Dz1Asn1SetOf_conformance		Dz1Asn1Array_conformance									// 17

static __inline__ bool_t	 Dz1Asn1DigitStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)		// 18
{	// Dz1Asn1DigitStr
	Dz1Asn1DigitStr *v = (Dz1Asn1DigitStr *)dataPtr;
	Dz1Asn1StringConformanceAPI api = { Dz1Asn1ASCIIStr_strlen, Dz1Asn1ASCIIStr_toUCS4 };
	return Dz1Asn1Constraint_KMS_match(p, &api, v, ret_is_ext);
}

static __inline__ bool_t	 Dz1Asn1PrintStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)		// 19
{	// Dz1Asn1PrintStr
	Dz1Asn1PrintStr *v = (Dz1Asn1PrintStr *)dataPtr;
	Dz1Asn1StringConformanceAPI api = { Dz1Asn1ASCIIStr_strlen, Dz1Asn1ASCIIStr_toUCS4 };
	return Dz1Asn1Constraint_KMS_match(p, &api, v, ret_is_ext);
}

static __inline__ bool_t	 Dz1Asn1TeletexStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)		// 20
{	// Dz1Asn1PrintStr
	return TRUE;		// XXX : TBD
}
static __inline__ bool_t	 Dz1Asn1VideotexStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)	// 21
{	// Dz1Asn1PrintStr
	return TRUE;		// XXX : TBD
}
static __inline__			Dz1Asn1IA5Str_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)			// 22
{	// Dz1Asn1IA5Str
	Dz1Asn1IA5Str *v = (Dz1Asn1IA5Str *)dataPtr;
	Dz1Asn1StringConformanceAPI api = { Dz1Asn1ASCIIStr_strlen, Dz1Asn1ASCIIStr_toUCS4 };
	return Dz1Asn1Constraint_KMS_match(p, &api, v, ret_is_ext);
}

#define						 Dz1Asn1UTCTime_conformance		Dz1Asn1Constraint_none										// 23
#define						 Dz1Asn1GeneralTime_conformance	Dz1Asn1Constraint_none										// 24

#define						 Dz1Asn1GraphicStr_conformance	Dz1Asn1Constraint_none										// 25

static __inline__ Dz1Asn1VisibleStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)				// 26
{	// Dz1Asn1VisibleStr
	Dz1Asn1VisibleStr *v = (Dz1Asn1VisibleStr *)dataPtr;
	Dz1Asn1StringConformanceAPI api = { Dz1Asn1ASCIIStr_strlen, Dz1Asn1ASCIIStr_toUCS4 };
	return Dz1Asn1Constraint_KMS_match(p, &api, v, ret_is_ext);
}

#define						 Dz1Asn1GeneralStr_conformance	Dz1Asn1Constraint_none										// 27

static __inline__ bool_t	 Dz1Asn1UniversalStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)	// 28
{	// Dz1Asn1UniversalStr
	Dz1Asn1UniversalStr *v = (Dz1Asn1UniversalStr *)dataPtr;
	Dz1Asn1StringConformanceAPI api = { Dz1Asn1UniversalStr_strlen, Dz1Asn1UniversalStr_toUCS4 };
	return Dz1Asn1Constraint_KMS_match(p, &api, v, ret_is_ext);
}

#define						 Dz1Asn1CharStr_conformance		Dz1Asn1Sequence_conformance									// 29

static __inline__ bool_t	 Dz1Asn1BMPStr_conformance(Dz1Asn1Constraint *p, void *dataPtr, bool_t *ret_is_ext)			// 30
{	// Dz1Asn1BMPStr
	Dz1Asn1BMPStr *v = (Dz1Asn1BMPStr *)dataPtr;
	Dz1Asn1StringConformanceAPI api = { Dz1Asn1BMPStr_strlen, Dz1Asn1BMPStr_toUCS4 };
	return Dz1Asn1Constraint_KMS_match(p, &api, v, ret_is_ext);
}

#define						 Dz1Asn1Date_conformance		Dz1Asn1Constraint_none										// 31
#define						 Dz1Asn1TimeOfDay_conformance	Dz1Asn1Constraint_none										// 32
#define						 Dz1Asn1DateTime_conformance	Dz1Asn1Constraint_none										// 33
#define						 Dz1Asn1Duration_conformance	Dz1Asn1Constraint_none										// 34
// ASN.1 Type Constraint
///////////////////////////////////////////////////////////////////////////////
#endif	// DZ1_ASN1_CONSTRAINT_H
