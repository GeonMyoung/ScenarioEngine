#ifndef ENUM_INFO_H
#define ENUM_INFO_H

#include "dz1_error.h"

// val should be to int type
// <objectName>_<name>[ = <valStr>],
typedef struct EnumEntry
{
	str_t name;
	str_t valStr;
	s32_t value;
} EnumEntry;

DZ1_CPPLINK EnumEntry *EnumEntry_new(str_t name, str_t val, s32_t value, Dz1Error *err);
DZ1_CPPLINK EnumEntry *EnumEntry_clone(EnumEntry *src, Dz1Error *err);

DZ1_CPPLINK void EnumEntry_del(EnumEntry *p);
DZ1_CPPLINK void EnumEntry_dump(EnumEntry *p, int tab);
static __inline__ void EnumEntry_delAndSetNull(void *ptr)
{
	EnumEntry **p = (EnumEntry **)ptr;
	EnumEntry_del(*p); *p = NULL;
}

// <entries>,
// <entries>,
// <entries>,
typedef struct EnumList
{
	void *fifo;
	Dz1Error (*add)(struct EnumList *p, str_t name, str_t valStr, s32_t *val);
	Dz1Error (*append)(struct EnumList *p, EnumEntry *node);
	EnumEntry *(*findByName)(struct EnumList *p, str_t name);
	EnumEntry *(*findByVal)(struct EnumList *p, int value);
	u32_t (*count)(struct EnumList *p);
	Dz1Error (*travel)(struct EnumList *p, Dz1Error (*func)(void *ptr, EnumEntry *p), void *ptr);
} EnumList;

DZ1_CPPLINK EnumList *EnumList_new(Dz1Error *err);
DZ1_CPPLINK void EnumList_del(EnumList *p);
DZ1_CPPLINK void EnumList_dump(EnumList *p, int tab);
static __inline__ void EnumList_delAndSetNull(void *ptr)
{
	EnumList **p = (EnumList **)ptr;
	EnumList_del(*p); *p = NULL;
}

// typedef enum
// {
// 	<enum list>
// 	{ NULL, <name>_max }
// } <name>;
typedef struct EnumInfo
{
	EnumList *enums;
	bool_t	  isGenerated;
} EnumInfo;

DZ1_CPPLINK EnumInfo *EnumInfo_new(bool_t isGenerated, Dz1Error *err);
DZ1_CPPLINK EnumInfo *EnumInfo_clone(EnumInfo *src, Dz1Error *err);
DZ1_CPPLINK void EnumInfo_del(EnumInfo *p);
DZ1_CPPLINK void EnumInfo_dump(EnumInfo *p, int tab);
static __inline__ void EnumInfo_delAndSetNull(void *ptr)
{
	EnumInfo **p = (EnumInfo **)ptr;
	EnumInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK void *EnumInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t EnumInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t EnumInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif
