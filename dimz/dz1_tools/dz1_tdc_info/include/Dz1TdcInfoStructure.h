#ifndef STRUCTURE_INFO_H
#define STRUCTURE_INFO_H

#include <dz1_fifo.h>

#include "Dz1TdcInfoCommon.h"

struct ObjectInfo;
//	<type->name>	[*]<name>;

typedef struct StructMemberEntry
{
	FORWARD_TYPE		 isForwarded;
	struct ObjectInfo	*type;				// References
	str_t				 srcType;			// original type name before conventional convert
	int					 isPointer;			// it will bay be count of '*'
	str_t				 instance;
	u32_t				 memb_flags;		// ref, arg, key, array, elem_is_ref, asn_optional
	MemberDumpMode		 dumpMode;			// nodump=MemberDumpMode_omit | valdump=MemberDumpMode_value | cascadedump=MemberDumpMode_cascade
	str_t				 arr_cnt_name;
} StructMemberEntry;

#define StructMemberEntry_isReferenced(membp)		MemberFlag_isReferenced((membp)->memb_flags)
#define StructMemberEntry_isArgInvolve(membp)		MemberFlag_isArgInvolve((membp)->memb_flags)
#define StructMemberEntry_isIndex(membp)			MemberFlag_isIndex((membp)->memb_flags)
#define StructMemberEntry_isArray(membp)			MemberFlag_isArray((membp)->memb_flags)
#define StructMemberEntry_isArrayElemRef(membp)		MemberFlag_isArrayElemRef((membp)->memb_flags)

#define StructMemberEntry_isAsnOptional(membp)		MemberFlag_isAsnOptional((membp)->memb_flags)

DZ1_CPPLINK StructMemberEntry *StructMemberEntry_new(FORWARD_TYPE isForwarded, struct ObjectInfo *type, str_t srcType,
													 int isPointer, str_t instance, 
													 u32_t memb_flags,
													 MemberDumpMode mode,
													 str_t arr_cnt_name, Dz1Error *err);
DZ1_CPPLINK void StructMemberEntry_del(StructMemberEntry *p);
DZ1_CPPLINK void StructMemberEntry_dump(StructMemberEntry *p, int tab);
static __inline__ void StructMemberEntry_delAndSetNull(void *ptr)
{
	StructMemberEntry **p = (StructMemberEntry **)ptr;
	StructMemberEntry_del(*p); *p = NULL;
}


// 		<member>,
// 		<member>,
// 		<member>,
// 		<member>
typedef struct StructMemberList
{
	Dz1Fifo *fifo;
	Dz1Error			 (*add)(struct StructMemberList *p, StructMemberEntry *e);
	Dz1Error			 (*append)(struct StructMemberList *p,
								FORWARD_TYPE isForwarded, struct ObjectInfo *type,
								str_t srcType, int isPointer, str_t instance,
//								int isReferenced, MemberDumpMode mode, int argInvolve, int isIndex, bool_t isAsnOptional);
								u32_t memb_flags, MemberDumpMode dump_mode, str_t arr_cnt_name);
	StructMemberEntry	*(*find)(struct StructMemberList *p, str_t instance);
	u32_t				 (*count)(struct StructMemberList *p);
	Dz1Error			 (*travel)(struct StructMemberList *p, Dz1Error (*func)(void *ptr, StructMemberEntry *p), void *ptr);
	StructMemberEntry	**(*get_array)(struct StructMemberList *p, u32_t *ret_cnt, Dz1Error *err);
	int					 (*cmp)(StructMemberEntry *a, StructMemberEntry *b);
} StructMemberList;

DZ1_CPPLINK StructMemberList *StructMemberList_new(Dz1Error *err);
DZ1_CPPLINK void StructMemberList_del(StructMemberList *p);
DZ1_CPPLINK void StructMemberList_dump(StructMemberList *p, int tab);
static __inline__ void StructMemberList_delAndSetNull(void *ptr)
{
	StructMemberList **p = (StructMemberList **)ptr;
	StructMemberList_del(*p); *p = NULL;
}
DZ1_CPPLINK StructMemberEntry *StructMemberList_find(StructMemberList *p, str_t instance);

// typedef struct <objeectName>
// {
// 		<memberList>
// } <objectName>;
typedef struct StructureInfo
{
	StructMemberList *members;
} StructureInfo;

DZ1_CPPLINK StructureInfo *StructureInfo_new(Dz1Error *err);
DZ1_CPPLINK void StructureInfo_del(StructureInfo *p);
DZ1_CPPLINK void StructureInfo_dump(StructureInfo *p, int tab);
static __inline__ void StructureInfo_delAndSetNull(void *ptr)
{
	StructureInfo **p = (StructureInfo **)ptr;
	StructureInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK int StructureInfo_isStaticSize(StructureInfo *p);
DZ1_CPPLINK int StructureInfo_comparable(StructureInfo *p, PublishSpec *sp);

DZ1_CPPLINK StructureInfo *StructureInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t StructureInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t StructureInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);
#endif
