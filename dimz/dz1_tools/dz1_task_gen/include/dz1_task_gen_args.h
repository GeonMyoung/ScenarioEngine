#ifndef _DZ1_TDC_DZ1_TASK_GEN_ARGS_H_
#define _DZ1_TDC_DZ1_TASK_GEN_ARGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1GenTextMode
typedef enum Dz1GenTextMode
{
	Dz1GenTextMode_DOS,
	Dz1GenTextMode_UNIX,
	Dz1GenTextMode_max
} Dz1GenTextMode;

DZ1_CPPLINK str_t Dz1GenTextModeStrA(Dz1GenTextMode v);
DZ1_CPPLINK Dz1GenTextMode Dz1GenTextModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1GenTextModeStrW(Dz1GenTextMode v);
DZ1_CPPLINK Dz1GenTextMode Dz1GenTextModeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1GenTextModeStr Dz1GenTextModeStrW
#define Dz1GenTextModeFromStr Dz1GenTextModeFromStrW
#else // UNICODE
#define Dz1GenTextModeStr Dz1GenTextModeStrA
#define Dz1GenTextModeFromStr Dz1GenTextModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1GenTextModeStr Dz1GenTextModeStrA
#define Dz1GenTextModeFromStr Dz1GenTextModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1GenTextMode *Dz1GenTextMode_new(Dz1GenTextMode *src, Dz1Error *err);
static __inline__ Dz1GenTextMode *Dz1GenTextMode_gen(Dz1Error *err) { Dz1GenTextMode v = Dz1GenTextMode_max; return Dz1GenTextMode_new(&v, err); }
static __inline__ void Dz1GenTextMode_del(Dz1GenTextMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1GenTextMode_delAndSetNull(void *ptr)
{
	Dz1GenTextMode **p = (Dz1GenTextMode **)ptr;
	if (p != NULL) { Dz1GenTextMode_del(*p); *p = NULL; }
}
// Dz1GenTextMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GenTarget
typedef enum Dz1GenTarget
{
	Dz1GenTarget_StaticLibrary,
	Dz1GenTarget_Task,
	Dz1GenTarget_max
} Dz1GenTarget;

DZ1_CPPLINK str_t Dz1GenTargetStrA(Dz1GenTarget v);
DZ1_CPPLINK Dz1GenTarget Dz1GenTargetFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1GenTargetStrW(Dz1GenTarget v);
DZ1_CPPLINK Dz1GenTarget Dz1GenTargetFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1GenTargetStr Dz1GenTargetStrW
#define Dz1GenTargetFromStr Dz1GenTargetFromStrW
#else // UNICODE
#define Dz1GenTargetStr Dz1GenTargetStrA
#define Dz1GenTargetFromStr Dz1GenTargetFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1GenTargetStr Dz1GenTargetStrA
#define Dz1GenTargetFromStr Dz1GenTargetFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1GenTarget *Dz1GenTarget_new(Dz1GenTarget *src, Dz1Error *err);
static __inline__ Dz1GenTarget *Dz1GenTarget_gen(Dz1Error *err) { Dz1GenTarget v = Dz1GenTarget_max; return Dz1GenTarget_new(&v, err); }
static __inline__ void Dz1GenTarget_del(Dz1GenTarget *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1GenTarget_delAndSetNull(void *ptr)
{
	Dz1GenTarget **p = (Dz1GenTarget **)ptr;
	if (p != NULL) { Dz1GenTarget_del(*p); *p = NULL; }
}
// Dz1GenTarget
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ProjectVcConf
typedef enum ProjectVcConf
{
	ProjectVcConf_Debug,
	ProjectVcConf_DebugDLL,
	ProjectVcConf_Release,
	ProjectVcConf_ReleaseDLL,
	ProjectVcConf_max
} ProjectVcConf;

DZ1_CPPLINK str_t ProjectVcConfStrA(ProjectVcConf v);
DZ1_CPPLINK ProjectVcConf ProjectVcConfFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ProjectVcConfStrW(ProjectVcConf v);
DZ1_CPPLINK ProjectVcConf ProjectVcConfFromStrW(wstr_t str);
#ifdef UNICODE
#define ProjectVcConfStr ProjectVcConfStrW
#define ProjectVcConfFromStr ProjectVcConfFromStrW
#else // UNICODE
#define ProjectVcConfStr ProjectVcConfStrA
#define ProjectVcConfFromStr ProjectVcConfFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ProjectVcConfStr ProjectVcConfStrA
#define ProjectVcConfFromStr ProjectVcConfFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ProjectVcConf *ProjectVcConf_new(ProjectVcConf *src, Dz1Error *err);
static __inline__ ProjectVcConf *ProjectVcConf_gen(Dz1Error *err) { ProjectVcConf v = ProjectVcConf_max; return ProjectVcConf_new(&v, err); }
static __inline__ void ProjectVcConf_del(ProjectVcConf *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ProjectVcConf_delAndSetNull(void *ptr)
{
	ProjectVcConf **p = (ProjectVcConf **)ptr;
	if (p != NULL) { ProjectVcConf_del(*p); *p = NULL; }
}
// ProjectVcConf
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TaskGenEndian
typedef enum Dz1TaskGenEndian
{
	Dz1TaskGenEndian_Little,
	Dz1TaskGenEndian_Big,
	Dz1TaskGenEndian_max
} Dz1TaskGenEndian;

DZ1_CPPLINK str_t Dz1TaskGenEndianStrA(Dz1TaskGenEndian v);
DZ1_CPPLINK Dz1TaskGenEndian Dz1TaskGenEndianFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TaskGenEndianStrW(Dz1TaskGenEndian v);
DZ1_CPPLINK Dz1TaskGenEndian Dz1TaskGenEndianFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TaskGenEndianStr Dz1TaskGenEndianStrW
#define Dz1TaskGenEndianFromStr Dz1TaskGenEndianFromStrW
#else // UNICODE
#define Dz1TaskGenEndianStr Dz1TaskGenEndianStrA
#define Dz1TaskGenEndianFromStr Dz1TaskGenEndianFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TaskGenEndianStr Dz1TaskGenEndianStrA
#define Dz1TaskGenEndianFromStr Dz1TaskGenEndianFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TaskGenEndian *Dz1TaskGenEndian_new(Dz1TaskGenEndian *src, Dz1Error *err);
static __inline__ Dz1TaskGenEndian *Dz1TaskGenEndian_gen(Dz1Error *err) { Dz1TaskGenEndian v = Dz1TaskGenEndian_max; return Dz1TaskGenEndian_new(&v, err); }
static __inline__ void Dz1TaskGenEndian_del(Dz1TaskGenEndian *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TaskGenEndian_delAndSetNull(void *ptr)
{
	Dz1TaskGenEndian **p = (Dz1TaskGenEndian **)ptr;
	if (p != NULL) { Dz1TaskGenEndian_del(*p); *p = NULL; }
}
// Dz1TaskGenEndian
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2Naming
typedef enum GenArgs2Naming
{
	GenArgs2Naming_canonical,
	GenArgs2Naming_underscore,
	GenArgs2Naming_max
} GenArgs2Naming;

DZ1_CPPLINK str_t GenArgs2NamingStrA(GenArgs2Naming v);
DZ1_CPPLINK GenArgs2Naming GenArgs2NamingFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GenArgs2NamingStrW(GenArgs2Naming v);
DZ1_CPPLINK GenArgs2Naming GenArgs2NamingFromStrW(wstr_t str);
#ifdef UNICODE
#define GenArgs2NamingStr GenArgs2NamingStrW
#define GenArgs2NamingFromStr GenArgs2NamingFromStrW
#else // UNICODE
#define GenArgs2NamingStr GenArgs2NamingStrA
#define GenArgs2NamingFromStr GenArgs2NamingFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GenArgs2NamingStr GenArgs2NamingStrA
#define GenArgs2NamingFromStr GenArgs2NamingFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GenArgs2Naming *GenArgs2Naming_new(GenArgs2Naming *src, Dz1Error *err);
static __inline__ GenArgs2Naming *GenArgs2Naming_gen(Dz1Error *err) { GenArgs2Naming v = GenArgs2Naming_max; return GenArgs2Naming_new(&v, err); }
static __inline__ void GenArgs2Naming_del(GenArgs2Naming *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GenArgs2Naming_delAndSetNull(void *ptr)
{
	GenArgs2Naming **p = (GenArgs2Naming **)ptr;
	if (p != NULL) { GenArgs2Naming_del(*p); *p = NULL; }
}
// GenArgs2Naming
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudioVer
typedef enum GenArgs2VisualStudioVer
{
	GenArgs2VisualStudioVer_vc71,
	GenArgs2VisualStudioVer_vc90,
	GenArgs2VisualStudioVer_vs2015,
	GenArgs2VisualStudioVer_vs2017,
	GenArgs2VisualStudioVer_vs2019,
	GenArgs2VisualStudioVer_vs2022,
	GenArgs2VisualStudioVer_max
} GenArgs2VisualStudioVer;

DZ1_CPPLINK str_t GenArgs2VisualStudioVerStrA(GenArgs2VisualStudioVer v);
DZ1_CPPLINK GenArgs2VisualStudioVer GenArgs2VisualStudioVerFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GenArgs2VisualStudioVerStrW(GenArgs2VisualStudioVer v);
DZ1_CPPLINK GenArgs2VisualStudioVer GenArgs2VisualStudioVerFromStrW(wstr_t str);
#ifdef UNICODE
#define GenArgs2VisualStudioVerStr GenArgs2VisualStudioVerStrW
#define GenArgs2VisualStudioVerFromStr GenArgs2VisualStudioVerFromStrW
#else // UNICODE
#define GenArgs2VisualStudioVerStr GenArgs2VisualStudioVerStrA
#define GenArgs2VisualStudioVerFromStr GenArgs2VisualStudioVerFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GenArgs2VisualStudioVerStr GenArgs2VisualStudioVerStrA
#define GenArgs2VisualStudioVerFromStr GenArgs2VisualStudioVerFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GenArgs2VisualStudioVer *GenArgs2VisualStudioVer_new(GenArgs2VisualStudioVer *src, Dz1Error *err);
static __inline__ GenArgs2VisualStudioVer *GenArgs2VisualStudioVer_gen(Dz1Error *err) { GenArgs2VisualStudioVer v = GenArgs2VisualStudioVer_max; return GenArgs2VisualStudioVer_new(&v, err); }
static __inline__ void GenArgs2VisualStudioVer_del(GenArgs2VisualStudioVer *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GenArgs2VisualStudioVer_delAndSetNull(void *ptr)
{
	GenArgs2VisualStudioVer **p = (GenArgs2VisualStudioVer **)ptr;
	if (p != NULL) { GenArgs2VisualStudioVer_del(*p); *p = NULL; }
}
// GenArgs2VisualStudioVer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudioVerSupport
typedef enum GenArgs2VisualStudioVerSupport
{
	GenArgs2VisualStudioVerSupport_vc90 = GenArgs2VisualStudioVer_vc90,
	GenArgs2VisualStudioVerSupport_vs2022 = GenArgs2VisualStudioVer_vs2022,
	GenArgs2VisualStudioVerSupport_max
} GenArgs2VisualStudioVerSupport;

DZ1_CPPLINK str_t GenArgs2VisualStudioVerSupportStrA(GenArgs2VisualStudioVerSupport v);
DZ1_CPPLINK GenArgs2VisualStudioVerSupport GenArgs2VisualStudioVerSupportFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GenArgs2VisualStudioVerSupportStrW(GenArgs2VisualStudioVerSupport v);
DZ1_CPPLINK GenArgs2VisualStudioVerSupport GenArgs2VisualStudioVerSupportFromStrW(wstr_t str);
#ifdef UNICODE
#define GenArgs2VisualStudioVerSupportStr GenArgs2VisualStudioVerSupportStrW
#define GenArgs2VisualStudioVerSupportFromStr GenArgs2VisualStudioVerSupportFromStrW
#else // UNICODE
#define GenArgs2VisualStudioVerSupportStr GenArgs2VisualStudioVerSupportStrA
#define GenArgs2VisualStudioVerSupportFromStr GenArgs2VisualStudioVerSupportFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GenArgs2VisualStudioVerSupportStr GenArgs2VisualStudioVerSupportStrA
#define GenArgs2VisualStudioVerSupportFromStr GenArgs2VisualStudioVerSupportFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GenArgs2VisualStudioVerSupport *GenArgs2VisualStudioVerSupport_new(GenArgs2VisualStudioVerSupport *src, Dz1Error *err);
static __inline__ GenArgs2VisualStudioVerSupport *GenArgs2VisualStudioVerSupport_gen(Dz1Error *err) { GenArgs2VisualStudioVerSupport v = GenArgs2VisualStudioVerSupport_max; return GenArgs2VisualStudioVerSupport_new(&v, err); }
static __inline__ void GenArgs2VisualStudioVerSupport_del(GenArgs2VisualStudioVerSupport *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GenArgs2VisualStudioVerSupport_delAndSetNull(void *ptr)
{
	GenArgs2VisualStudioVerSupport **p = (GenArgs2VisualStudioVerSupport **)ptr;
	if (p != NULL) { GenArgs2VisualStudioVerSupport_del(*p); *p = NULL; }
}
// GenArgs2VisualStudioVerSupport
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudioEntry
typedef struct GenArgs2VisualStudioEntry
{
	GenArgs2VisualStudioVer		ver;
	Dz1Str						middle_path;
	Dz1Str						proj_file_name;
	Dz1Str						proj_guid;
} GenArgs2VisualStudioEntry;

DZ1_CPPLINK DZ1_DLLPORT GenArgs2VisualStudioEntry *GenArgs2VisualStudioEntry_new(GenArgs2VisualStudioVer ver, 
																				 Dz1Str middle_path, 
																				 Dz1Str proj_file_name, 
																				 Dz1Str proj_guid, Dz1Error *err);
static __inline__ GenArgs2VisualStudioEntry *GenArgs2VisualStudioEntry_gen(Dz1Error *err) { return GenArgs2VisualStudioEntry_new(GenArgs2VisualStudioVer_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GenArgs2VisualStudioEntry_copy(GenArgs2VisualStudioEntry *dst, GenArgs2VisualStudioEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GenArgs2VisualStudioEntry *GenArgs2VisualStudioEntry_clone(GenArgs2VisualStudioEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2VisualStudioEntry_purge(GenArgs2VisualStudioEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2VisualStudioEntry_del(GenArgs2VisualStudioEntry *p);
static __inline__ void GenArgs2VisualStudioEntry_delAndSetNull(void *ptr)
{
	GenArgs2VisualStudioEntry **p = (GenArgs2VisualStudioEntry **)ptr;
	if (p) { GenArgs2VisualStudioEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2VisualStudioEntry_dump(GenArgs2VisualStudioEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GenArgs2VisualStudioEntry_cmp(GenArgs2VisualStudioEntry *a, GenArgs2VisualStudioEntry *b); 
// GenArgs2VisualStudioEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudioList
typedef struct GenArgs2VisualStudioList
{
	void *storage;
	unsigned int (*count)(struct GenArgs2VisualStudioList *p);
	Dz1Error (*travel)(struct GenArgs2VisualStudioList *p, Dz1Error (*func)(void *ptr, GenArgs2VisualStudioEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct GenArgs2VisualStudioList *p, Dz1Error (*func)(void *ptr, GenArgs2VisualStudioEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct GenArgs2VisualStudioList *p, Dz1Error (*func)(void *ptr, GenArgs2VisualStudioEntry *entry), void *ptr);
	GenArgs2VisualStudioEntry **(*get_array)(struct GenArgs2VisualStudioList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct GenArgs2VisualStudioList *p, GenArgs2VisualStudioEntry *data);
	bool_t (*remove)(struct GenArgs2VisualStudioList *p, GenArgs2VisualStudioEntry *key);
	GenArgs2VisualStudioEntry *(*extract)(struct GenArgs2VisualStudioList *p, GenArgs2VisualStudioEntry *key);
	GenArgs2VisualStudioEntry *(*find)(struct GenArgs2VisualStudioList *p, GenArgs2VisualStudioEntry *key);
	int (*cmp)(GenArgs2VisualStudioEntry *a, GenArgs2VisualStudioEntry *b);
} GenArgs2VisualStudioList;

DZ1_CPPLINK DZ1_DLLPORT GenArgs2VisualStudioList *GenArgs2VisualStudioList_new(Dz1Error *err);
static __inline__ GenArgs2VisualStudioList *GenArgs2VisualStudioList_gen(Dz1Error *err) { return GenArgs2VisualStudioList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT GenArgs2VisualStudioList *GenArgs2VisualStudioList_clone(GenArgs2VisualStudioList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2VisualStudioList_purge(GenArgs2VisualStudioList *p);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2VisualStudioList_del(GenArgs2VisualStudioList *p);
static __inline__ void GenArgs2VisualStudioList_delAndSetNull(void *ptr)
{
	GenArgs2VisualStudioList **p = (GenArgs2VisualStudioList **)ptr;
	if (p != NULL) { GenArgs2VisualStudioList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2VisualStudioList_dump(GenArgs2VisualStudioList *p, int tab);

// GenArgs2VisualStudioList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryEntry
typedef struct GenArgs2LibraryEntry
{
	Dz1Str						 name;
	Dz1Str						 path_root_abs;
	u32_t						 order;
	Dz1Str						 root2inc_path;
	Dz1Str						 root2lib_path;
	GenArgs2VisualStudioList	*projects;
} GenArgs2LibraryEntry;

DZ1_CPPLINK DZ1_DLLPORT GenArgs2LibraryEntry *GenArgs2LibraryEntry_new(Dz1Str name, 
																	   Dz1Str path_root_abs, 
																	   u32_t order, 
																	   Dz1Str root2inc_path, 
																	   Dz1Str root2lib_path, Dz1Error *err);
static __inline__ GenArgs2LibraryEntry *GenArgs2LibraryEntry_gen(Dz1Error *err) { return GenArgs2LibraryEntry_new(NULL, NULL, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GenArgs2LibraryEntry_copy(GenArgs2LibraryEntry *dst, GenArgs2LibraryEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GenArgs2LibraryEntry *GenArgs2LibraryEntry_clone(GenArgs2LibraryEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryEntry_purge(GenArgs2LibraryEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryEntry_del(GenArgs2LibraryEntry *p);
static __inline__ void GenArgs2LibraryEntry_delAndSetNull(void *ptr)
{
	GenArgs2LibraryEntry **p = (GenArgs2LibraryEntry **)ptr;
	if (p) { GenArgs2LibraryEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryEntry_dump(GenArgs2LibraryEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GenArgs2LibraryEntry_cmp(GenArgs2LibraryEntry *a, GenArgs2LibraryEntry *b); 
// GenArgs2LibraryEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryList
typedef struct GenArgs2LibraryList
{
	void *storage;
	unsigned int (*count)(struct GenArgs2LibraryList *p);
	Dz1Error (*travel)(struct GenArgs2LibraryList *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct GenArgs2LibraryList *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct GenArgs2LibraryList *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *entry), void *ptr);
	GenArgs2LibraryEntry **(*get_array)(struct GenArgs2LibraryList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct GenArgs2LibraryList *p, GenArgs2LibraryEntry *data);
	bool_t (*remove)(struct GenArgs2LibraryList *p, GenArgs2LibraryEntry *key);
	GenArgs2LibraryEntry *(*extract)(struct GenArgs2LibraryList *p, GenArgs2LibraryEntry *key);
	GenArgs2LibraryEntry *(*find)(struct GenArgs2LibraryList *p, GenArgs2LibraryEntry *key);
	int (*cmp)(GenArgs2LibraryEntry *a, GenArgs2LibraryEntry *b);
} GenArgs2LibraryList;

DZ1_CPPLINK DZ1_DLLPORT GenArgs2LibraryList *GenArgs2LibraryList_new(Dz1Error *err);
static __inline__ GenArgs2LibraryList *GenArgs2LibraryList_gen(Dz1Error *err) { return GenArgs2LibraryList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT GenArgs2LibraryList *GenArgs2LibraryList_clone(GenArgs2LibraryList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryList_purge(GenArgs2LibraryList *p);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryList_del(GenArgs2LibraryList *p);
static __inline__ void GenArgs2LibraryList_delAndSetNull(void *ptr)
{
	GenArgs2LibraryList **p = (GenArgs2LibraryList **)ptr;
	if (p != NULL) { GenArgs2LibraryList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryList_dump(GenArgs2LibraryList *p, int tab);

// GenArgs2LibraryList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryRefIndex
typedef struct GenArgs2LibraryRefIndex
{
	void *storage;
	unsigned int (*count)(struct GenArgs2LibraryRefIndex *p);
	Dz1Error (*travel)(struct GenArgs2LibraryRefIndex *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct GenArgs2LibraryRefIndex *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct GenArgs2LibraryRefIndex *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *entry), void *ptr);
	GenArgs2LibraryEntry **(*get_array)(struct GenArgs2LibraryRefIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct GenArgs2LibraryRefIndex *p, GenArgs2LibraryEntry *data);
	bool_t (*remove)(struct GenArgs2LibraryRefIndex *p, GenArgs2LibraryEntry *key);
	GenArgs2LibraryEntry *(*extract)(struct GenArgs2LibraryRefIndex *p, GenArgs2LibraryEntry *key);
	GenArgs2LibraryEntry *(*find)(struct GenArgs2LibraryRefIndex *p, GenArgs2LibraryEntry *key);
	GenArgs2LibraryEntry *(*getTail)(struct GenArgs2LibraryRefIndex *p);
	int (*cmp)(GenArgs2LibraryEntry *a, GenArgs2LibraryEntry *b);
} GenArgs2LibraryRefIndex;

DZ1_CPPLINK DZ1_DLLPORT GenArgs2LibraryRefIndex *GenArgs2LibraryRefIndex_new(Dz1Error *err);
static __inline__ GenArgs2LibraryRefIndex *GenArgs2LibraryRefIndex_gen(Dz1Error *err) { return GenArgs2LibraryRefIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT GenArgs2LibraryRefIndex *GenArgs2LibraryRefIndex_clone(GenArgs2LibraryRefIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryRefIndex_purge(GenArgs2LibraryRefIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryRefIndex_del(GenArgs2LibraryRefIndex *p);
static __inline__ void GenArgs2LibraryRefIndex_delAndSetNull(void *ptr)
{
	GenArgs2LibraryRefIndex **p = (GenArgs2LibraryRefIndex **)ptr;
	if (p != NULL) { GenArgs2LibraryRefIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryRefIndex_dump(GenArgs2LibraryRefIndex *p, int tab);

// GenArgs2LibraryRefIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryInfoFindF
typedef GenArgs2LibraryEntry *(*GenArgs2LibraryInfoFindF)(struct GenArgs2LibraryInfo *list, GenArgs2LibraryEntry *key);
// GenArgs2LibraryInfoFindF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryInfoAddF
typedef Dz1Error (*GenArgs2LibraryInfoAddF)(struct GenArgs2LibraryInfo *list, GenArgs2LibraryEntry *node);
// GenArgs2LibraryInfoAddF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryInfoRemoveF
typedef void (*GenArgs2LibraryInfoRemoveF)(struct GenArgs2LibraryInfo *list, GenArgs2LibraryEntry *key);
// GenArgs2LibraryInfoRemoveF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryInfoArrayF
typedef GenArgs2LibraryEntry **(*GenArgs2LibraryInfoArrayF)(struct GenArgs2LibraryInfo *list, u32_t *cnt, Dz1Error *err);
// GenArgs2LibraryInfoArrayF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryInfo
typedef struct GenArgs2LibraryInfo
{
	GenArgs2LibraryList				*table;
	GenArgs2LibraryRefIndex			*inorder;
	GenArgs2LibraryInfoAddF			 add;
	GenArgs2LibraryInfoRemoveF		 remove;
	GenArgs2LibraryInfoFindF		 find;
	GenArgs2LibraryInfoFindF		 extract;
	GenArgs2LibraryInfoArrayF		 get_array;
} GenArgs2LibraryInfo;

DZ1_CPPLINK DZ1_DLLPORT GenArgs2LibraryInfo *GenArgs2LibraryInfo_new(Dz1Error *err);	// User Customized
static __inline__ GenArgs2LibraryInfo *GenArgs2LibraryInfo_gen(Dz1Error *err) { return GenArgs2LibraryInfo_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GenArgs2LibraryInfo_copy(GenArgs2LibraryInfo *dst, GenArgs2LibraryInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GenArgs2LibraryInfo *GenArgs2LibraryInfo_clone(GenArgs2LibraryInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryInfo_purge(GenArgs2LibraryInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryInfo_del(GenArgs2LibraryInfo *p);
static __inline__ void GenArgs2LibraryInfo_delAndSetNull(void *ptr)
{
	GenArgs2LibraryInfo **p = (GenArgs2LibraryInfo **)ptr;
	if (p) { GenArgs2LibraryInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2LibraryInfo_dump(GenArgs2LibraryInfo *p, int tab);
// GenArgs2LibraryInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DZ1_TASK_GEN_SOLUTION
#define DZ1_TASK_GEN_SOLUTION			2147483648
// DZ1_TASK_GEN_SOLUTION
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DZ1_TASK_GEN_VC90
#define DZ1_TASK_GEN_VC90			1
// DZ1_TASK_GEN_VC90
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DZ1_TASK_GEN_VS2022
#define DZ1_TASK_GEN_VS2022			2
// DZ1_TASK_GEN_VS2022
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudio
typedef struct GenArgs2VisualStudio
{
	Dz1Str		pthread_root;
	u32_t		gen_project;
} GenArgs2VisualStudio;

DZ1_CPPLINK DZ1_DLLPORT GenArgs2VisualStudio *GenArgs2VisualStudio_new(Dz1Str pthread_root, 
																	   u32_t gen_project, Dz1Error *err);
static __inline__ GenArgs2VisualStudio *GenArgs2VisualStudio_gen(Dz1Error *err) { return GenArgs2VisualStudio_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GenArgs2VisualStudio_copy(GenArgs2VisualStudio *dst, GenArgs2VisualStudio *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GenArgs2VisualStudio *GenArgs2VisualStudio_clone(GenArgs2VisualStudio *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2VisualStudio_purge(GenArgs2VisualStudio *p);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2VisualStudio_del(GenArgs2VisualStudio *p);
static __inline__ void GenArgs2VisualStudio_delAndSetNull(void *ptr)
{
	GenArgs2VisualStudio **p = (GenArgs2VisualStudio **)ptr;
	if (p) { GenArgs2VisualStudio_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2VisualStudio_dump(GenArgs2VisualStudio *p, int tab);
// GenArgs2VisualStudio
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2
typedef struct GenArgs2
{
	Dz1Str					 gen_parent_path;
	Dz1GenTarget			 gen_target_type;
	Dz1Str					 gen_target_name;
	bool_t					 gen_test_main;
	bool_t					 gen_makefile;
	GenArgs2VisualStudio	*gen_studios;
	Dz1GenTextMode			 txt_mode;
	Dz1TaskGenEndian		 endian;
	GenArgs2Naming			 name_rule;
	Dz1Str					 codeconv_root;
	Dz1Str					 dimz_root;
	GenArgs2LibraryInfo		*libraries;
} GenArgs2;

DZ1_CPPLINK DZ1_DLLPORT GenArgs2 *GenArgs2_new(Dz1Str gen_parent_path, 
											   Dz1GenTarget gen_target_type, 
											   Dz1Str gen_target_name, 
											   bool_t gen_test_main, 
											   bool_t gen_makefile, 
											   GenArgs2VisualStudio *gen_studios, 
											   Dz1GenTextMode txt_mode, 
											   Dz1TaskGenEndian endian, 
											   GenArgs2Naming name_rule, 
											   Dz1Str codeconv_root, 
											   Dz1Str dimz_root, 
											   GenArgs2LibraryInfo *libraries, Dz1Error *err);
static __inline__ GenArgs2 *GenArgs2_gen(Dz1Error *err) { return GenArgs2_new(NULL, Dz1GenTarget_max, NULL, 0, 0, NULL, Dz1GenTextMode_max, Dz1TaskGenEndian_max, GenArgs2Naming_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2_purge(GenArgs2 *p);
DZ1_CPPLINK DZ1_DLLPORT void GenArgs2_del(GenArgs2 *p);
static __inline__ void GenArgs2_delAndSetNull(void *ptr)
{
	GenArgs2 **p = (GenArgs2 **)ptr;
	if (p) { GenArgs2_del(*p); *p = NULL; }
}
// GenArgs2
////////////////////////////////////////////////////////////////////////////////

#endif
