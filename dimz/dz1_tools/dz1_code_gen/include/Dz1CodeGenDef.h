#ifndef _DZ1_TDC_DZ1_CODE_GEN_DEF_H_
#define _DZ1_TDC_DZ1_CODE_GEN_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Dz1TdcInfoObject.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenSetupEntry
typedef struct Dz1CodeGenSetupEntry
{
	str_t		label;
	bool_t		useThisArg;
} Dz1CodeGenSetupEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenSetupEntry *Dz1CodeGenSetupEntry_new(str_t label, 
																	   bool_t useThisArg, Dz1Error *err);
static __inline__ Dz1CodeGenSetupEntry *Dz1CodeGenSetupEntry_gen(Dz1Error *err) { return Dz1CodeGenSetupEntry_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenSetupEntry_purge(Dz1CodeGenSetupEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenSetupEntry_del(Dz1CodeGenSetupEntry *p);
static __inline__ void Dz1CodeGenSetupEntry_delAndSetNull(void *ptr)
{
	Dz1CodeGenSetupEntry **p = (Dz1CodeGenSetupEntry **)ptr;
	if (p) { Dz1CodeGenSetupEntry_del(*p); *p = NULL; }
}
// Dz1CodeGenSetupEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenSetupTable
typedef struct Dz1CodeGenSetupTable
{
	s32_t					 type;
	Dz1CodeGenSetupEntry	*setup;
} Dz1CodeGenSetupTable;

DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenSetupTable *Dz1CodeGenSetupTable_new(s32_t type, 
																	   Dz1CodeGenSetupEntry *setup, Dz1Error *err);
static __inline__ Dz1CodeGenSetupTable *Dz1CodeGenSetupTable_gen(Dz1Error *err) { return Dz1CodeGenSetupTable_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenSetupTable_purge(Dz1CodeGenSetupTable *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenSetupTable_del(Dz1CodeGenSetupTable *p);
static __inline__ void Dz1CodeGenSetupTable_delAndSetNull(void *ptr)
{
	Dz1CodeGenSetupTable **p = (Dz1CodeGenSetupTable **)ptr;
	if (p) { Dz1CodeGenSetupTable_del(*p); *p = NULL; }
}
// Dz1CodeGenSetupTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenReplaceEnt
typedef struct Dz1CodeGenReplaceEnt
{
	str_t		target;
	str_t		replace;
} Dz1CodeGenReplaceEnt;

DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenReplaceEnt *Dz1CodeGenReplaceEnt_new(str_t target, 
																	   str_t replace, Dz1Error *err);
static __inline__ Dz1CodeGenReplaceEnt *Dz1CodeGenReplaceEnt_gen(Dz1Error *err) { return Dz1CodeGenReplaceEnt_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1CodeGenReplaceEnt_copy(Dz1CodeGenReplaceEnt *dst, Dz1CodeGenReplaceEnt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenReplaceEnt *Dz1CodeGenReplaceEnt_clone(Dz1CodeGenReplaceEnt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenReplaceEnt_purge(Dz1CodeGenReplaceEnt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenReplaceEnt_del(Dz1CodeGenReplaceEnt *p);
static __inline__ void Dz1CodeGenReplaceEnt_delAndSetNull(void *ptr)
{
	Dz1CodeGenReplaceEnt **p = (Dz1CodeGenReplaceEnt **)ptr;
	if (p) { Dz1CodeGenReplaceEnt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenReplaceEnt_dump(Dz1CodeGenReplaceEnt *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1CodeGenReplaceEnt_cmp(Dz1CodeGenReplaceEnt *a, Dz1CodeGenReplaceEnt *b); 
// Dz1CodeGenReplaceEnt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenReplaceList
typedef struct Dz1CodeGenReplaceList
{
	void *storage;
	unsigned int (*count)(struct Dz1CodeGenReplaceList *p);
	Dz1Error (*travel)(struct Dz1CodeGenReplaceList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenReplaceEnt *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1CodeGenReplaceList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenReplaceEnt *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1CodeGenReplaceList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenReplaceEnt *entry), void *ptr);
	Dz1CodeGenReplaceEnt **(*get_array)(struct Dz1CodeGenReplaceList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1CodeGenReplaceList *p, Dz1CodeGenReplaceEnt *data);
	bool_t (*remove)(struct Dz1CodeGenReplaceList *p, Dz1CodeGenReplaceEnt *key);
	Dz1CodeGenReplaceEnt *(*extract)(struct Dz1CodeGenReplaceList *p, Dz1CodeGenReplaceEnt *key);
	Dz1CodeGenReplaceEnt *(*find)(struct Dz1CodeGenReplaceList *p, Dz1CodeGenReplaceEnt *key);
	int (*cmp)(Dz1CodeGenReplaceEnt *a, Dz1CodeGenReplaceEnt *b);
} Dz1CodeGenReplaceList;

DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenReplaceList *Dz1CodeGenReplaceList_new(Dz1Error *err);
static __inline__ Dz1CodeGenReplaceList *Dz1CodeGenReplaceList_gen(Dz1Error *err) { return Dz1CodeGenReplaceList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenReplaceList *Dz1CodeGenReplaceList_clone(Dz1CodeGenReplaceList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenReplaceList_purge(Dz1CodeGenReplaceList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenReplaceList_del(Dz1CodeGenReplaceList *p);
static __inline__ void Dz1CodeGenReplaceList_delAndSetNull(void *ptr)
{
	Dz1CodeGenReplaceList **p = (Dz1CodeGenReplaceList **)ptr;
	if (p != NULL) { Dz1CodeGenReplaceList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenReplaceList_dump(Dz1CodeGenReplaceList *p, int tab);

// Dz1CodeGenReplaceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListType
typedef enum Dz1CodeGenListType
{
	Dz1CodeGenListType_addNode,
	Dz1CodeGenListType_codec,
	Dz1CodeGenListType_stream,
	Dz1CodeGenListType_mfc_list_h,
	Dz1CodeGenListType_mfc_list_cpp,
	Dz1CodeGenListType_mfc_list_base,
	Dz1CodeGenListType_mfc_list_changed,
	Dz1CodeGenListType_mfc_list_clicked,
	Dz1CodeGenListType_max
} Dz1CodeGenListType;

DZ1_CPPLINK str_t Dz1CodeGenListTypeStrA(Dz1CodeGenListType v);
DZ1_CPPLINK Dz1CodeGenListType Dz1CodeGenListTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1CodeGenListTypeStrW(Dz1CodeGenListType v);
DZ1_CPPLINK Dz1CodeGenListType Dz1CodeGenListTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1CodeGenListTypeStr Dz1CodeGenListTypeStrW
#define Dz1CodeGenListTypeFromStr Dz1CodeGenListTypeFromStrW
#else // UNICODE
#define Dz1CodeGenListTypeStr Dz1CodeGenListTypeStrA
#define Dz1CodeGenListTypeFromStr Dz1CodeGenListTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1CodeGenListTypeStr Dz1CodeGenListTypeStrA
#define Dz1CodeGenListTypeFromStr Dz1CodeGenListTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenListType *Dz1CodeGenListType_new(Dz1CodeGenListType *src, Dz1Error *err);
static __inline__ Dz1CodeGenListType *Dz1CodeGenListType_gen(Dz1Error *err) { Dz1CodeGenListType v = Dz1CodeGenListType_max; return Dz1CodeGenListType_new(&v, err); }
static __inline__ void Dz1CodeGenListType_del(Dz1CodeGenListType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1CodeGenListType_delAndSetNull(void *ptr)
{
	Dz1CodeGenListType **p = (Dz1CodeGenListType **)ptr;
	if (p != NULL) { Dz1CodeGenListType_del(*p); *p = NULL; }
}
// Dz1CodeGenListType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenStubType
typedef enum Dz1CodeGenStubType
{
	Dz1CodeGenStubType_creation,
	Dz1CodeGenStubType_s_api,
	Dz1CodeGenStubType_s_codec,
	Dz1CodeGenStubType_u_codec,
	Dz1CodeGenStubType_v_codec,
	Dz1CodeGenStubType_codec_conv,
	Dz1CodeGenStubType_codec_test,
	Dz1CodeGenStubType_s_stream,
	Dz1CodeGenStubType_u_stream,
	Dz1CodeGenStubType_v_stream,
	Dz1CodeGenStubType_stream_conv,
	Dz1CodeGenStubType_stream_test,
	Dz1CodeGenStubType_test_gen,
	Dz1CodeGenStubType_test_ugen,
	Dz1CodeGenStubType_mfc_enum_combo_h,
	Dz1CodeGenStubType_max
} Dz1CodeGenStubType;

DZ1_CPPLINK str_t Dz1CodeGenStubTypeStrA(Dz1CodeGenStubType v);
DZ1_CPPLINK Dz1CodeGenStubType Dz1CodeGenStubTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1CodeGenStubTypeStrW(Dz1CodeGenStubType v);
DZ1_CPPLINK Dz1CodeGenStubType Dz1CodeGenStubTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1CodeGenStubTypeStr Dz1CodeGenStubTypeStrW
#define Dz1CodeGenStubTypeFromStr Dz1CodeGenStubTypeFromStrW
#else // UNICODE
#define Dz1CodeGenStubTypeStr Dz1CodeGenStubTypeStrA
#define Dz1CodeGenStubTypeFromStr Dz1CodeGenStubTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1CodeGenStubTypeStr Dz1CodeGenStubTypeStrA
#define Dz1CodeGenStubTypeFromStr Dz1CodeGenStubTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenStubType *Dz1CodeGenStubType_new(Dz1CodeGenStubType *src, Dz1Error *err);
static __inline__ Dz1CodeGenStubType *Dz1CodeGenStubType_gen(Dz1Error *err) { Dz1CodeGenStubType v = Dz1CodeGenStubType_max; return Dz1CodeGenStubType_new(&v, err); }
static __inline__ void Dz1CodeGenStubType_del(Dz1CodeGenStubType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1CodeGenStubType_delAndSetNull(void *ptr)
{
	Dz1CodeGenStubType **p = (Dz1CodeGenStubType **)ptr;
	if (p != NULL) { Dz1CodeGenStubType_del(*p); *p = NULL; }
}
// Dz1CodeGenStubType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenParserType
typedef enum Dz1CodeGenParserType
{
	Dz1CodeGenParserType_emitter,
	Dz1CodeGenParserType_parser,
	Dz1CodeGenParserType_max
} Dz1CodeGenParserType;

DZ1_CPPLINK str_t Dz1CodeGenParserTypeStrA(Dz1CodeGenParserType v);
DZ1_CPPLINK Dz1CodeGenParserType Dz1CodeGenParserTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1CodeGenParserTypeStrW(Dz1CodeGenParserType v);
DZ1_CPPLINK Dz1CodeGenParserType Dz1CodeGenParserTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1CodeGenParserTypeStr Dz1CodeGenParserTypeStrW
#define Dz1CodeGenParserTypeFromStr Dz1CodeGenParserTypeFromStrW
#else // UNICODE
#define Dz1CodeGenParserTypeStr Dz1CodeGenParserTypeStrA
#define Dz1CodeGenParserTypeFromStr Dz1CodeGenParserTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1CodeGenParserTypeStr Dz1CodeGenParserTypeStrA
#define Dz1CodeGenParserTypeFromStr Dz1CodeGenParserTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenParserType *Dz1CodeGenParserType_new(Dz1CodeGenParserType *src, Dz1Error *err);
static __inline__ Dz1CodeGenParserType *Dz1CodeGenParserType_gen(Dz1Error *err) { Dz1CodeGenParserType v = Dz1CodeGenParserType_max; return Dz1CodeGenParserType_new(&v, err); }
static __inline__ void Dz1CodeGenParserType_del(Dz1CodeGenParserType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1CodeGenParserType_delAndSetNull(void *ptr)
{
	Dz1CodeGenParserType **p = (Dz1CodeGenParserType **)ptr;
	if (p != NULL) { Dz1CodeGenParserType_del(*p); *p = NULL; }
}
// Dz1CodeGenParserType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenShellType
typedef enum Dz1CodeGenShellType
{
	Dz1CodeGenShellType_root_cmd,
	Dz1CodeGenShellType_sub_cmd,
	Dz1CodeGenShellType_max
} Dz1CodeGenShellType;

DZ1_CPPLINK str_t Dz1CodeGenShellTypeStrA(Dz1CodeGenShellType v);
DZ1_CPPLINK Dz1CodeGenShellType Dz1CodeGenShellTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1CodeGenShellTypeStrW(Dz1CodeGenShellType v);
DZ1_CPPLINK Dz1CodeGenShellType Dz1CodeGenShellTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1CodeGenShellTypeStr Dz1CodeGenShellTypeStrW
#define Dz1CodeGenShellTypeFromStr Dz1CodeGenShellTypeFromStrW
#else // UNICODE
#define Dz1CodeGenShellTypeStr Dz1CodeGenShellTypeStrA
#define Dz1CodeGenShellTypeFromStr Dz1CodeGenShellTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1CodeGenShellTypeStr Dz1CodeGenShellTypeStrA
#define Dz1CodeGenShellTypeFromStr Dz1CodeGenShellTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenShellType *Dz1CodeGenShellType_new(Dz1CodeGenShellType *src, Dz1Error *err);
static __inline__ Dz1CodeGenShellType *Dz1CodeGenShellType_gen(Dz1Error *err) { Dz1CodeGenShellType v = Dz1CodeGenShellType_max; return Dz1CodeGenShellType_new(&v, err); }
static __inline__ void Dz1CodeGenShellType_del(Dz1CodeGenShellType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1CodeGenShellType_delAndSetNull(void *ptr)
{
	Dz1CodeGenShellType **p = (Dz1CodeGenShellType **)ptr;
	if (p != NULL) { Dz1CodeGenShellType_del(*p); *p = NULL; }
}
// Dz1CodeGenShellType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListCtrlObjectParent
struct Dz1CodeGenListCtrlObjectParent;

typedef struct Dz1CodeGenListCtrlObjectParent
{
	struct Dz1CodeGenListCtrlObjectParent		*p;
	str_t										 instance;
} Dz1CodeGenListCtrlObjectParent;

DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenListCtrlObjectParent *Dz1CodeGenListCtrlObjectParent_new(struct Dz1CodeGenListCtrlObjectParent *p_ref, 
																						   str_t instance, Dz1Error *err);
static __inline__ Dz1CodeGenListCtrlObjectParent *Dz1CodeGenListCtrlObjectParent_gen(Dz1Error *err) { return Dz1CodeGenListCtrlObjectParent_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenListCtrlObjectParent_purge(Dz1CodeGenListCtrlObjectParent *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenListCtrlObjectParent_del(Dz1CodeGenListCtrlObjectParent *p);
static __inline__ void Dz1CodeGenListCtrlObjectParent_delAndSetNull(void *ptr)
{
	Dz1CodeGenListCtrlObjectParent **p = (Dz1CodeGenListCtrlObjectParent **)ptr;
	if (p) { Dz1CodeGenListCtrlObjectParent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenListCtrlObjectParent_dump(Dz1CodeGenListCtrlObjectParent *p, int tab);
// Dz1CodeGenListCtrlObjectParent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListCtrlInstanceMode
typedef enum Dz1CodeGenListCtrlInstanceMode
{
	Dz1CodeGenListCtrlInstanceMode_dot,
	Dz1CodeGenListCtrlInstanceMode_arrow,
	Dz1CodeGenListCtrlInstanceMode_arrowxdot,
	Dz1CodeGenListCtrlInstanceMode_max
} Dz1CodeGenListCtrlInstanceMode;

DZ1_CPPLINK str_t Dz1CodeGenListCtrlInstanceModeStrA(Dz1CodeGenListCtrlInstanceMode v);
DZ1_CPPLINK Dz1CodeGenListCtrlInstanceMode Dz1CodeGenListCtrlInstanceModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1CodeGenListCtrlInstanceModeStrW(Dz1CodeGenListCtrlInstanceMode v);
DZ1_CPPLINK Dz1CodeGenListCtrlInstanceMode Dz1CodeGenListCtrlInstanceModeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1CodeGenListCtrlInstanceModeStr Dz1CodeGenListCtrlInstanceModeStrW
#define Dz1CodeGenListCtrlInstanceModeFromStr Dz1CodeGenListCtrlInstanceModeFromStrW
#else // UNICODE
#define Dz1CodeGenListCtrlInstanceModeStr Dz1CodeGenListCtrlInstanceModeStrA
#define Dz1CodeGenListCtrlInstanceModeFromStr Dz1CodeGenListCtrlInstanceModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1CodeGenListCtrlInstanceModeStr Dz1CodeGenListCtrlInstanceModeStrA
#define Dz1CodeGenListCtrlInstanceModeFromStr Dz1CodeGenListCtrlInstanceModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenListCtrlInstanceMode *Dz1CodeGenListCtrlInstanceMode_new(Dz1CodeGenListCtrlInstanceMode *src, Dz1Error *err);
static __inline__ Dz1CodeGenListCtrlInstanceMode *Dz1CodeGenListCtrlInstanceMode_gen(Dz1Error *err) { Dz1CodeGenListCtrlInstanceMode v = Dz1CodeGenListCtrlInstanceMode_max; return Dz1CodeGenListCtrlInstanceMode_new(&v, err); }
static __inline__ void Dz1CodeGenListCtrlInstanceMode_del(Dz1CodeGenListCtrlInstanceMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1CodeGenListCtrlInstanceMode_delAndSetNull(void *ptr)
{
	Dz1CodeGenListCtrlInstanceMode **p = (Dz1CodeGenListCtrlInstanceMode **)ptr;
	if (p != NULL) { Dz1CodeGenListCtrlInstanceMode_del(*p); *p = NULL; }
}
// Dz1CodeGenListCtrlInstanceMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListColumn
typedef struct Dz1CodeGenListColumn
{
	u32_t								 order;
	str_t								 name;
	ObjectInfo							*type;
	str_t								 instance;
	Dz1CodeGenListCtrlInstanceMode		 mode;
	Dz1CodeGenListCtrlObjectParent		*parent;
} Dz1CodeGenListColumn;

DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenListColumn *Dz1CodeGenListColumn_new(u32_t order, 
																	   str_t name, 
																	   ObjectInfo *type, 
																	   str_t instance, 
																	   Dz1CodeGenListCtrlInstanceMode mode, 
																	   Dz1CodeGenListCtrlObjectParent *parent, Dz1Error *err);
static __inline__ Dz1CodeGenListColumn *Dz1CodeGenListColumn_gen(Dz1Error *err) { return Dz1CodeGenListColumn_new(0, NULL, NULL, NULL, Dz1CodeGenListCtrlInstanceMode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenListColumn_purge(Dz1CodeGenListColumn *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenListColumn_del(Dz1CodeGenListColumn *p);
static __inline__ void Dz1CodeGenListColumn_delAndSetNull(void *ptr)
{
	Dz1CodeGenListColumn **p = (Dz1CodeGenListColumn **)ptr;
	if (p) { Dz1CodeGenListColumn_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenListColumn_dump(Dz1CodeGenListColumn *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1CodeGenListColumn_cmp(Dz1CodeGenListColumn *a, Dz1CodeGenListColumn *b); 
// Dz1CodeGenListColumn
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListColumnList
typedef struct Dz1CodeGenListColumnList
{
	void *storage;
	unsigned int (*count)(struct Dz1CodeGenListColumnList *p);
	Dz1Error (*travel)(struct Dz1CodeGenListColumnList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenListColumn *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1CodeGenListColumnList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenListColumn *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1CodeGenListColumnList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenListColumn *entry), void *ptr);
	Dz1CodeGenListColumn **(*get_array)(struct Dz1CodeGenListColumnList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1CodeGenListColumnList *p, Dz1CodeGenListColumn *data);
	bool_t (*remove)(struct Dz1CodeGenListColumnList *p, Dz1CodeGenListColumn *key);
	Dz1CodeGenListColumn *(*extract)(struct Dz1CodeGenListColumnList *p, Dz1CodeGenListColumn *key);
	Dz1CodeGenListColumn *(*find)(struct Dz1CodeGenListColumnList *p, Dz1CodeGenListColumn *key);
	int (*cmp)(Dz1CodeGenListColumn *a, Dz1CodeGenListColumn *b);
} Dz1CodeGenListColumnList;

DZ1_CPPLINK DZ1_DLLPORT Dz1CodeGenListColumnList *Dz1CodeGenListColumnList_new(Dz1Error *err);
static __inline__ Dz1CodeGenListColumnList *Dz1CodeGenListColumnList_gen(Dz1Error *err) { return Dz1CodeGenListColumnList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenListColumnList_purge(Dz1CodeGenListColumnList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenListColumnList_del(Dz1CodeGenListColumnList *p);
static __inline__ void Dz1CodeGenListColumnList_delAndSetNull(void *ptr)
{
	Dz1CodeGenListColumnList **p = (Dz1CodeGenListColumnList **)ptr;
	if (p != NULL) { Dz1CodeGenListColumnList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CodeGenListColumnList_dump(Dz1CodeGenListColumnList *p, int tab);

// Dz1CodeGenListColumnList
////////////////////////////////////////////////////////////////////////////////

#endif
