#ifndef DZ1_ASN1_CONSTRAINT_TYPE_H
#define DZ1_ASN1_CONSTRAINT_TYPE_H

#include <dz1_asn1_types.h>

///////////////////////////////////////////////////////////////////////////////
// Range Array
typedef struct Dz1Asn1MetaDataRangeInfo
{
	Dz1Asn1MetaDataRange					*arr;
	u32_t									 cnt;
	bool_t									 extensible;
} Dz1Asn1MetaDataRangeInfo;
DZ1_CPPLINK Dz1Asn1MetaDataRangeInfo	*Dz1Asn1MetaDataRangeInfo_new(Dz1Asn1MetaDataRange *arr, u32_t cnt, bool_t extensible, Dz1Error *err);
DZ1_CPPLINK void						 Dz1Asn1MetaDataRangeInfo_del(Dz1Asn1MetaDataRangeInfo *p);
static __inline__ void					 Dz1Asn1MetaDataRangeInfo_delAndSetNull(void *pptr)
{
	Dz1Asn1MetaDataRangeInfo **p = (Dz1Asn1MetaDataRangeInfo **)pptr;
	if (p) { Dz1Asn1MetaDataRangeInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK void						 Dz1Asn1MetaDataRangeInfoA_dump(Dz1Asn1MetaDataRangeInfo *p, int tab);
DZ1_CPPLINK void						 Dz1Asn1MetaDataRangeInfoA_fdump(FILE *fp, Dz1Asn1MetaDataRangeInfo *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void						 Dz1Asn1MetaDataRangeInfoW_dump(Dz1Asn1MetaDataRangeInfo *p, int tab);
DZ1_CPPLINK void						 Dz1Asn1MetaDataRangeInfoW_fdump(FILE *fp, Dz1Asn1MetaDataRangeInfo *p, int tab);
#ifdef UNICODE
#define									 Dz1Asn1MetaDataRangeInfo_dump Dz1Asn1MetaDataRangeInfoW_dump
#define									 Dz1Asn1MetaDataRangeInfo_fdump Dz1Asn1MetaDataRangeInfoW_fdump
#else // UNICODE
#define									 Dz1Asn1MetaDataRangeInfo_dump Dz1Asn1MetaDataRangeInfoA_dump
#define									 Dz1Asn1MetaDataRangeInfo_fdump Dz1Asn1MetaDataRangeInfoA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define									 Dz1Asn1MetaDataRangeInfo_dump Dz1Asn1MetaDataRangeInfoA_dump
#define									 Dz1Asn1MetaDataRangeInfo_fdump Dz1Asn1MetaDataRangeInfoA_fdump
#endif // UNIX_SYSTEM

DZ1_CPPLINK bool_t						 Dz1Asn1MetaDataRangeInfo_match(Dz1Asn1MetaDataRangeInfo *p, Dz1Asn1Int v, bool_t *ret_is_ext);
// Range Array
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// REAL Range Array
typedef struct Dz1Asn1MetaDataRealRangeInfo
{
	Dz1Asn1MetaDataRealRange				*arr;
	u32_t									 cnt;
	bool_t									 extensible;
} Dz1Asn1MetaDataRealRangeInfo;
DZ1_CPPLINK Dz1Asn1MetaDataRealRangeInfo	*Dz1Asn1MetaDataRealRangeInfo_new(Dz1Asn1MetaDataRealRange *arr, u32_t arr_cnt, bool_t extensible, Dz1Error *err);
DZ1_CPPLINK void							 Dz1Asn1MetaDataRealRangeInfo_del(Dz1Asn1MetaDataRealRangeInfo *p);
static __inline__ void						 Dz1Asn1MetaDataRealRangeInfo_delAndSetNull(void *pptr)
{
	Dz1Asn1MetaDataRealRangeInfo **p = (Dz1Asn1MetaDataRealRangeInfo **)pptr;
	if (p) { Dz1Asn1MetaDataRealRangeInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK void							 Dz1Asn1MetaDataRealRangeInfoA_dump(Dz1Asn1MetaDataRealRangeInfo *p, int tab);
DZ1_CPPLINK void							 Dz1Asn1MetaDataRealRangeInfoA_fdump(FILE *fp, Dz1Asn1MetaDataRealRangeInfo *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void							 Dz1Asn1MetaDataRealRangeInfoW_dump(Dz1Asn1MetaDataRealRangeInfo *p, int tab);
DZ1_CPPLINK void							 Dz1Asn1MetaDataRealRangeInfoW_fdump(FILE *fp, Dz1Asn1MetaDataRealRangeInfo *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1MetaDataRealRangeInfo_dump Dz1Asn1MetaDataRealRangeInfoW_dump
#define										 Dz1Asn1MetaDataRealRangeInfo_fdump Dz1Asn1MetaDataRealRangeInfoW_fdump
#else // UNICODE
#define										 Dz1Asn1MetaDataRealRangeInfo_dump Dz1Asn1MetaDataRealRangeInfoA_dump
#define										 Dz1Asn1MetaDataRealRangeInfo_fdump Dz1Asn1MetaDataRealRangeInfoA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1MetaDataRealRangeInfo_dump Dz1Asn1MetaDataRealRangeInfoA_dump
#define										 Dz1Asn1MetaDataRealRangeInfo_fdump Dz1Asn1MetaDataRealRangeInfoA_fdump
#endif // UNIX_SYSTEM

DZ1_CPPLINK bool_t							 Dz1Asn1MetaDataRealRangeInfo_match(Dz1Asn1MetaDataRealRangeInfo *p, Dz1Asn1Real v, bool_t *ret_is_ext);
// REAL Range Array
///////////////////////////////////////////////////////////////////////////////

#endif	// DZ1_ASN1_CONSTRAINT_TYPE_H
