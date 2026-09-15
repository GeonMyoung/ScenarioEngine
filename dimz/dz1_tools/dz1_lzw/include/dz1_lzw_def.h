#ifndef _DZ1_TDC_DZ1_LZW_DEF_H_
#define _DZ1_TDC_DZ1_LZW_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictData
typedef struct Dz1LzwDictData
{
	u32_t			 code;
	Dz1Binary		*bin;
} Dz1LzwDictData;

DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictData *Dz1LzwDictData_new(u32_t code, 
														   Dz1Binary *bin, Dz1Error *err);
static __inline__ Dz1LzwDictData *Dz1LzwDictData_gen(Dz1Error *err) { return Dz1LzwDictData_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictData_purge(Dz1LzwDictData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictData_del(Dz1LzwDictData *p);
static __inline__ void Dz1LzwDictData_delAndSetNull(void *ptr)
{
	Dz1LzwDictData **p = (Dz1LzwDictData **)ptr;
	if (p) { Dz1LzwDictData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictData_dump(Dz1LzwDictData *p, int tab);
// Dz1LzwDictData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictDataArray
typedef struct Dz1LzwDictDataArray
{
	void *storage;
	unsigned int (*count)(struct Dz1LzwDictDataArray *p);
	Dz1Error (*travel)(struct Dz1LzwDictDataArray *p, Dz1Error (*func)(void *ptr, Dz1LzwDictData *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1LzwDictDataArray *p, Dz1Error (*func)(void *ptr, Dz1LzwDictData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1LzwDictDataArray *p, Dz1Error (*func)(void *ptr, Dz1LzwDictData *entry), void *ptr);
	Dz1LzwDictData **(*get_array)(struct Dz1LzwDictDataArray *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1LzwDictDataArray *p, Dz1LzwDictData *data);
} Dz1LzwDictDataArray;

DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictDataArray *Dz1LzwDictDataArray_new(Dz1Error *err);
static __inline__ Dz1LzwDictDataArray *Dz1LzwDictDataArray_gen(Dz1Error *err) { return Dz1LzwDictDataArray_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictDataArray_purge(Dz1LzwDictDataArray *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictDataArray_del(Dz1LzwDictDataArray *p);
static __inline__ void Dz1LzwDictDataArray_delAndSetNull(void *ptr)
{
	Dz1LzwDictDataArray **p = (Dz1LzwDictDataArray **)ptr;
	if (p != NULL) { Dz1LzwDictDataArray_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictDataArray_dump(Dz1LzwDictDataArray *p, int tab);

// Dz1LzwDictDataArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictWord
typedef struct Dz1LzwDictWord
{
	u32_t			 code;
	Dz1Binary		*bin;
} Dz1LzwDictWord;

DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictWord *Dz1LzwDictWord_new(u32_t code, 
														   Dz1Binary *bin, Dz1Error *err);
static __inline__ Dz1LzwDictWord *Dz1LzwDictWord_gen(Dz1Error *err) { return Dz1LzwDictWord_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictWord_purge(Dz1LzwDictWord *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictWord_del(Dz1LzwDictWord *p);
static __inline__ void Dz1LzwDictWord_delAndSetNull(void *ptr)
{
	Dz1LzwDictWord **p = (Dz1LzwDictWord **)ptr;
	if (p) { Dz1LzwDictWord_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictWord_dump(Dz1LzwDictWord *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1LzwDictWord_cmp(Dz1LzwDictWord *a, Dz1LzwDictWord *b); 
// Dz1LzwDictWord
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictWordList
typedef struct Dz1LzwDictWordList
{
	void *storage;
	unsigned int (*count)(struct Dz1LzwDictWordList *p);
	Dz1Error (*travel)(struct Dz1LzwDictWordList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictWord *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1LzwDictWordList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictWord *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1LzwDictWordList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictWord *entry), void *ptr);
	Dz1LzwDictWord **(*get_array)(struct Dz1LzwDictWordList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1LzwDictWordList *p, Dz1LzwDictWord *data);
	bool_t (*remove)(struct Dz1LzwDictWordList *p, Dz1LzwDictWord *key);
	Dz1LzwDictWord *(*extract)(struct Dz1LzwDictWordList *p, Dz1LzwDictWord *key);
	Dz1LzwDictWord *(*find)(struct Dz1LzwDictWordList *p, Dz1LzwDictWord *key);
	int (*cmp)(Dz1LzwDictWord *a, Dz1LzwDictWord *b);
} Dz1LzwDictWordList;

DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictWordList *Dz1LzwDictWordList_new(Dz1Error *err);
static __inline__ Dz1LzwDictWordList *Dz1LzwDictWordList_gen(Dz1Error *err) { return Dz1LzwDictWordList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictWordList *Dz1LzwDictWordList_clone(Dz1LzwDictWordList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictWordList_purge(Dz1LzwDictWordList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictWordList_del(Dz1LzwDictWordList *p);
static __inline__ void Dz1LzwDictWordList_delAndSetNull(void *ptr)
{
	Dz1LzwDictWordList **p = (Dz1LzwDictWordList **)ptr;
	if (p != NULL) { Dz1LzwDictWordList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictWordList_dump(Dz1LzwDictWordList *p, int tab);

// Dz1LzwDictWordList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictSizeNode
typedef struct Dz1LzwDictSizeNode
{
	u32_t					 size;
	Dz1LzwDictWordList		*list;
} Dz1LzwDictSizeNode;

DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictSizeNode *Dz1LzwDictSizeNode_new(u32_t size, Dz1Error *err);
static __inline__ Dz1LzwDictSizeNode *Dz1LzwDictSizeNode_gen(Dz1Error *err) { return Dz1LzwDictSizeNode_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictSizeNode_purge(Dz1LzwDictSizeNode *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictSizeNode_del(Dz1LzwDictSizeNode *p);
static __inline__ void Dz1LzwDictSizeNode_delAndSetNull(void *ptr)
{
	Dz1LzwDictSizeNode **p = (Dz1LzwDictSizeNode **)ptr;
	if (p) { Dz1LzwDictSizeNode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictSizeNode_dump(Dz1LzwDictSizeNode *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1LzwDictSizeNode_cmp(Dz1LzwDictSizeNode *a, Dz1LzwDictSizeNode *b); 
// Dz1LzwDictSizeNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictSizeTable
typedef struct Dz1LzwDictSizeTable
{
	void *storage;
	unsigned int (*count)(struct Dz1LzwDictSizeTable *p);
	Dz1Error (*travel)(struct Dz1LzwDictSizeTable *p, Dz1Error (*func)(void *ptr, Dz1LzwDictSizeNode *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1LzwDictSizeTable *p, Dz1Error (*func)(void *ptr, Dz1LzwDictSizeNode *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1LzwDictSizeTable *p, Dz1Error (*func)(void *ptr, Dz1LzwDictSizeNode *entry), void *ptr);
	Dz1LzwDictSizeNode **(*get_array)(struct Dz1LzwDictSizeTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1LzwDictSizeTable *p, Dz1LzwDictSizeNode *data);
	bool_t (*remove)(struct Dz1LzwDictSizeTable *p, Dz1LzwDictSizeNode *key);
	Dz1LzwDictSizeNode *(*extract)(struct Dz1LzwDictSizeTable *p, Dz1LzwDictSizeNode *key);
	Dz1LzwDictSizeNode *(*find)(struct Dz1LzwDictSizeTable *p, Dz1LzwDictSizeNode *key);
	int (*cmp)(Dz1LzwDictSizeNode *a, Dz1LzwDictSizeNode *b);
} Dz1LzwDictSizeTable;

DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictSizeTable *Dz1LzwDictSizeTable_new(Dz1Error *err);
static __inline__ Dz1LzwDictSizeTable *Dz1LzwDictSizeTable_gen(Dz1Error *err) { return Dz1LzwDictSizeTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictSizeTable_purge(Dz1LzwDictSizeTable *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictSizeTable_del(Dz1LzwDictSizeTable *p);
static __inline__ void Dz1LzwDictSizeTable_delAndSetNull(void *ptr)
{
	Dz1LzwDictSizeTable **p = (Dz1LzwDictSizeTable **)ptr;
	if (p != NULL) { Dz1LzwDictSizeTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictSizeTable_dump(Dz1LzwDictSizeTable *p, int tab);

// Dz1LzwDictSizeTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictCode
typedef struct Dz1LzwDictCode
{
	u32_t			 code;
	Dz1Binary		*bin;
} Dz1LzwDictCode;

DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictCode *Dz1LzwDictCode_new(u32_t code, 
														   Dz1Binary *bin, Dz1Error *err);
static __inline__ Dz1LzwDictCode *Dz1LzwDictCode_gen(Dz1Error *err) { return Dz1LzwDictCode_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictCode_purge(Dz1LzwDictCode *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictCode_del(Dz1LzwDictCode *p);
static __inline__ void Dz1LzwDictCode_delAndSetNull(void *ptr)
{
	Dz1LzwDictCode **p = (Dz1LzwDictCode **)ptr;
	if (p) { Dz1LzwDictCode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictCode_dump(Dz1LzwDictCode *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1LzwDictCode_cmp(Dz1LzwDictCode *a, Dz1LzwDictCode *b); 
// Dz1LzwDictCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictCodeList
typedef struct Dz1LzwDictCodeList
{
	void *storage;
	unsigned int (*count)(struct Dz1LzwDictCodeList *p);
	Dz1Error (*travel)(struct Dz1LzwDictCodeList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictCode *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1LzwDictCodeList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictCode *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1LzwDictCodeList *p, Dz1Error (*func)(void *ptr, Dz1LzwDictCode *entry), void *ptr);
	Dz1LzwDictCode **(*get_array)(struct Dz1LzwDictCodeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1LzwDictCodeList *p, Dz1LzwDictCode *data);
	bool_t (*remove)(struct Dz1LzwDictCodeList *p, Dz1LzwDictCode *key);
	Dz1LzwDictCode *(*extract)(struct Dz1LzwDictCodeList *p, Dz1LzwDictCode *key);
	Dz1LzwDictCode *(*find)(struct Dz1LzwDictCodeList *p, Dz1LzwDictCode *key);
	int (*cmp)(Dz1LzwDictCode *a, Dz1LzwDictCode *b);
} Dz1LzwDictCodeList;

DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictCodeList *Dz1LzwDictCodeList_new(Dz1Error *err);
static __inline__ Dz1LzwDictCodeList *Dz1LzwDictCodeList_gen(Dz1Error *err) { return Dz1LzwDictCodeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictCodeList *Dz1LzwDictCodeList_clone(Dz1LzwDictCodeList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictCodeList_purge(Dz1LzwDictCodeList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictCodeList_del(Dz1LzwDictCodeList *p);
static __inline__ void Dz1LzwDictCodeList_delAndSetNull(void *ptr)
{
	Dz1LzwDictCodeList **p = (Dz1LzwDictCodeList **)ptr;
	if (p != NULL) { Dz1LzwDictCodeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictCodeList_dump(Dz1LzwDictCodeList *p, int tab);

// Dz1LzwDictCodeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LzwDictionary
typedef struct Dz1LzwDictionary
{
	u32_t					 code_bits;
	u32_t					 base_code_max;
	u32_t					 curr_code_max;
	u32_t					 alloc_code;
	Dz1LzwDictDataArray		*arr;
	Dz1LzwDictSizeTable		*sizes;
	Dz1LzwDictCodeList		*codes;
} Dz1LzwDictionary;

DZ1_CPPLINK DZ1_DLLPORT Dz1LzwDictionary *Dz1LzwDictionary_new(Dz1Error *err);
static __inline__ Dz1LzwDictionary *Dz1LzwDictionary_gen(Dz1Error *err) { return Dz1LzwDictionary_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictionary_purge(Dz1LzwDictionary *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictionary_del(Dz1LzwDictionary *p);
static __inline__ void Dz1LzwDictionary_delAndSetNull(void *ptr)
{
	Dz1LzwDictionary **p = (Dz1LzwDictionary **)ptr;
	if (p) { Dz1LzwDictionary_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LzwDictionary_dump(Dz1LzwDictionary *p, int tab);
// Dz1LzwDictionary
////////////////////////////////////////////////////////////////////////////////

#endif
