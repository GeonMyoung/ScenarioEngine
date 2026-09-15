#ifndef UNION_INFO_H
#define UNION_INFO_H

#include <dz1_fifo.h>

#include "Dz1TdcInfoCommon.h"

struct ObjectInfo;
typedef struct UnionMemberEntry
{
	FORWARD_TYPE		 isForwarded;
	struct ObjectInfo	*type;				// References
	str_t				 srcType;			// original type name before conventional convert
	int					 isPointer;			// it will bay be count of '*'
	str_t				 instance;
	u32_t				 memb_flags;		// ref, array, elem_is_ref		// original => "int isReferenced;"
	MemberDumpMode		 dumpMode;			// nodump=MemberDumpMode_omit | valdump=MemberDumpMode_value | cascadedump=MemberDumpMode_cascade
	str_t				 end_of_arr;
	str_t				 presentStr;
} UnionMemberEntry;

#define UnionMemberEntry_isReferenced(membp)		MemberFlag_isReferenced((membp)->memb_flags)
#define UnionMemberEntry_isArray(membp)				MemberFlag_isArray((membp)->memb_flags)
#define UnionMemberEntry_isArrayElemRef(membp)		MemberFlag_isArrayElemRef((membp)->memb_flags)

DZ1_CPPLINK UnionMemberEntry *UnionMemberEntry_new(int isForwarded, struct ObjectInfo *type, str_t presentStr,
												   str_t srcType, int isPointer, str_t instance,
												   u32_t memb_flags, MemberDumpMode dumpMode, str_t end_of_arr, Dz1Error *err);
DZ1_CPPLINK UnionMemberEntry *UnionMemberEntry_clone(UnionMemberEntry *src, Dz1Error *err);
DZ1_CPPLINK void UnionMemberEntry_purge(UnionMemberEntry *p);
DZ1_CPPLINK void UnionMemberEntry_del(UnionMemberEntry *p);
DZ1_CPPLINK void UnionMemberEntry_dump(UnionMemberEntry *p, int tab);
static __inline__ void UnionMemberEntry_delAndSetNull(void *ptr)
{
	UnionMemberEntry **p = (UnionMemberEntry **)ptr;
	UnionMemberEntry_del(*p); *p = NULL;
}

typedef struct UnionMemberList
{
	Dz1Fifo *fifo;
	Dz1Error (*insert)(struct UnionMemberList *p, UnionMemberEntry *e);
	Dz1Error (*add)(struct UnionMemberList *p,
					int isForwarded, struct ObjectInfo *type, str_t presentStr,
					str_t srcType, int isPointer, str_t instance,
					u32_t memb_flags, MemberDumpMode dumpMode, str_t end_of_arr);
	UnionMemberEntry *(*find)(struct UnionMemberList *p, str_t instance);
	u32_t (*count)(struct UnionMemberList *p);
	Dz1Error (*travel)(struct UnionMemberList *p, Dz1Error (*func)(void *ptr, UnionMemberEntry *p), void *ptr);
	UnionMemberEntry **(*get_array)(struct UnionMemberList *list, u32_t *ret_cnt, Dz1Error *err);
} UnionMemberList;

DZ1_CPPLINK UnionMemberList *UnionMemberList_new(Dz1Error *err);
DZ1_CPPLINK void UnionMemberList_del(UnionMemberList *p);
DZ1_CPPLINK void UnionMemberList_dump(UnionMemberList *p, int tab);
static __inline__ void UnionMemberList_delAndSetNull(void *ptr)
{
	UnionMemberList **p = (UnionMemberList **)ptr;
	UnionMemberList_del(*p); *p = NULL;
}
DZ1_CPPLINK Dz1Error UnionMemberList_merge(UnionMemberList *dst, UnionMemberList *src);

typedef struct UnionInfo
{
	UnionMemberList *members;
	bool_t comparePresentOnly;
} UnionInfo;

UnionInfo *UnionInfo_new(Dz1Error *err);
DZ1_CPPLINK void UnionInfo_del(UnionInfo *p);
DZ1_CPPLINK void UnionInfo_dump(UnionInfo *p, int tab);
static __inline__ void UnionInfo_delAndSetNull(void *ptr)
{
	UnionInfo **p = (UnionInfo **)ptr;
	UnionInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK int UnionInfo_isStaticSize(UnionInfo *p);
DZ1_CPPLINK int UnionInfo_comparable(UnionInfo *p, PublishSpec *sp);

DZ1_CPPLINK UnionInfo *UnionInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t UnionInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t UnionInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);
#endif
