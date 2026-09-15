#ifndef _DZ1_TDC_DZ1_VFS_DEF_H_
#define _DZ1_TDC_DZ1_VFS_DEF_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_sock_addr.h>

#include "dz1_meta_tag_def.h"
#include "dz1_storage.h"
#include "dz1_storage_def.h"
#include "dz1_sync.h"
#include "libdz1_support.h"

typedef struct Dz1VfsFile
{
	u32_t idx;
	Dz1MetaTagTargetType body_type;
	u32_t body_idx;
	Dz1MetaTagData *tags;
} Dz1VfsFile;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsFile *Dz1VfsFile_new(
			u32_t idx,
			Dz1MetaTagTargetType body_type,
			u32_t body_idx,
			Dz1MetaTagData *tags, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsFile_del(Dz1VfsFile *p);
static __inline__ void Dz1VfsFile_delAndSetNull(void *ptr)
{
	Dz1VfsFile **p = (Dz1VfsFile **)ptr;
	Dz1VfsFile_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsFile_dump(Dz1VfsFile *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1VfsFile_cmp(Dz1VfsFile *a, Dz1VfsFile *b);
typedef struct Dz1VfsChildNode
{
	Dz1Asn1UTF8Str *name;
	u32_t idx;
} Dz1VfsChildNode;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsChildNode *Dz1VfsChildNode_new(Dz1Asn1UTF8Str *name, u32_t idx, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsChildNode_del(Dz1VfsChildNode *p);
static __inline__ void Dz1VfsChildNode_delAndSetNull(void *ptr)
{
	Dz1VfsChildNode **p = (Dz1VfsChildNode **)ptr;
	Dz1VfsChildNode_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsChildNode_dump(Dz1VfsChildNode *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1VfsChildNode_cmp(Dz1VfsChildNode *a, Dz1VfsChildNode *b);
typedef struct Dz1VfsChildList
{
	void *storage;
	Dz1Error (*add)(struct Dz1VfsChildList *p, Dz1VfsChildNode *data);
	void (*remove)(struct Dz1VfsChildList *p, Dz1VfsChildNode *key);
	Dz1VfsChildNode *(*extract)(struct Dz1VfsChildList *p, Dz1VfsChildNode *key);
	Dz1Error (*travel)(struct Dz1VfsChildList *p, Dz1Error (*func)(void *ptr, Dz1VfsChildNode *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1VfsChildList *p, Dz1Error (*func)(void *ptr, Dz1VfsChildNode *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1VfsChildList *p, Dz1Error (*func)(void *ptr, Dz1VfsChildNode *entry), void *ptr);
	Dz1VfsChildNode *(*find)(struct Dz1VfsChildList *p, Dz1VfsChildNode *key);
	unsigned int (*count)(struct Dz1VfsChildList *p);
} Dz1VfsChildList;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsChildList *Dz1VfsChildList_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsChildList_del(Dz1VfsChildList *p);
static __inline__ void Dz1VfsChildList_delAndSetNull(void *ptr)
{
	Dz1VfsChildList **p = (Dz1VfsChildList **)ptr;
	Dz1VfsChildList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsChildList_dump(Dz1VfsChildList *p, int tab);
typedef struct Dz1VfsDir
{
	u32_t idx;
	u32_t parent_idx;
	Dz1MetaTagData *tags;
	Dz1VfsChildList *dirs;
	Dz1VfsChildList *files;
} Dz1VfsDir;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsDir *Dz1VfsDir_new(
			u32_t idx,
			u32_t parent_idx,
			Dz1MetaTagData *tags, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsDir_del(Dz1VfsDir *p);
static __inline__ void Dz1VfsDir_delAndSetNull(void *ptr)
{
	Dz1VfsDir **p = (Dz1VfsDir **)ptr;
	Dz1VfsDir_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsDir_dump(Dz1VfsDir *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1VfsDir_cmp(Dz1VfsDir *a, Dz1VfsDir *b);
typedef struct Dz1VfsHandleFileInfo
{
	u32_t handle_id;
	bool_t read;
	bool_t write;
	bool_t seek;
	bool_t tagChanged;
	bool_t dataChanged;
	Dz1StoragePos *pos;
} Dz1VfsHandleFileInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsHandleFileInfo *Dz1VfsHandleFileInfo_new(
			u32_t handle_id,
			bool_t read,
			bool_t write,
			bool_t seek,
			bool_t tagChanged,
			bool_t dataChanged,
			Dz1StoragePos *pos, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleFileInfo_del(Dz1VfsHandleFileInfo *p);
static __inline__ void Dz1VfsHandleFileInfo_delAndSetNull(void *ptr)
{
	Dz1VfsHandleFileInfo **p = (Dz1VfsHandleFileInfo **)ptr;
	Dz1VfsHandleFileInfo_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleFileInfo_dump(Dz1VfsHandleFileInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1VfsHandleFileInfo_cmp(Dz1VfsHandleFileInfo *a, Dz1VfsHandleFileInfo *b);
typedef struct Dz1VfsHandleFileInfoList
{
	void *storage;
	Dz1Error (*add)(struct Dz1VfsHandleFileInfoList *p, Dz1VfsHandleFileInfo *data);
	void (*remove)(struct Dz1VfsHandleFileInfoList *p, Dz1VfsHandleFileInfo *key);
	Dz1VfsHandleFileInfo *(*extract)(struct Dz1VfsHandleFileInfoList *p, Dz1VfsHandleFileInfo *key);
	Dz1Error (*travel)(struct Dz1VfsHandleFileInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1VfsHandleFileInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1VfsHandleFileInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileInfo *entry), void *ptr);
	Dz1VfsHandleFileInfo *(*find)(struct Dz1VfsHandleFileInfoList *p, Dz1VfsHandleFileInfo *key);
	unsigned int (*count)(struct Dz1VfsHandleFileInfoList *p);
} Dz1VfsHandleFileInfoList;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsHandleFileInfoList *Dz1VfsHandleFileInfoList_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleFileInfoList_del(Dz1VfsHandleFileInfoList *p);
static __inline__ void Dz1VfsHandleFileInfoList_delAndSetNull(void *ptr)
{
	Dz1VfsHandleFileInfoList **p = (Dz1VfsHandleFileInfoList **)ptr;
	Dz1VfsHandleFileInfoList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleFileInfoList_dump(Dz1VfsHandleFileInfoList *p, int tab);
typedef struct Dz1VfsHandleFileEntry
{
	u32_t idx;
	Dz1Sync *sync;
	Dz1VfsFile *source;
	Dz1VfsHandleFileInfoList *handles;
} Dz1VfsHandleFileEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsHandleFileEntry *Dz1VfsHandleFileEntry_new(
			u32_t idx,
			Dz1Sync *sync,
			Dz1VfsFile *source, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleFileEntry_del(Dz1VfsHandleFileEntry *p);
static __inline__ void Dz1VfsHandleFileEntry_delAndSetNull(void *ptr)
{
	Dz1VfsHandleFileEntry **p = (Dz1VfsHandleFileEntry **)ptr;
	Dz1VfsHandleFileEntry_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleFileEntry_dump(Dz1VfsHandleFileEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1VfsHandleFileEntry_cmp(Dz1VfsHandleFileEntry *a, Dz1VfsHandleFileEntry *b);
typedef struct Dz1VfsHandleFileList
{
	void *storage;
	Dz1Error (*add)(struct Dz1VfsHandleFileList *p, Dz1VfsHandleFileEntry *data);
	void (*remove)(struct Dz1VfsHandleFileList *p, Dz1VfsHandleFileEntry *key);
	Dz1VfsHandleFileEntry *(*extract)(struct Dz1VfsHandleFileList *p, Dz1VfsHandleFileEntry *key);
	Dz1Error (*travel)(struct Dz1VfsHandleFileList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1VfsHandleFileList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1VfsHandleFileList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileEntry *entry), void *ptr);
	Dz1VfsHandleFileEntry *(*find)(struct Dz1VfsHandleFileList *p, Dz1VfsHandleFileEntry *key);
	unsigned int (*count)(struct Dz1VfsHandleFileList *p);
} Dz1VfsHandleFileList;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsHandleFileList *Dz1VfsHandleFileList_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleFileList_del(Dz1VfsHandleFileList *p);
static __inline__ void Dz1VfsHandleFileList_delAndSetNull(void *ptr)
{
	Dz1VfsHandleFileList **p = (Dz1VfsHandleFileList **)ptr;
	Dz1VfsHandleFileList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleFileList_dump(Dz1VfsHandleFileList *p, int tab);
typedef struct Dz1VfsHandleDir
{
	u32_t handle_id;
	bool_t tagChanged;
	bool_t childChanged;
	bool_t fileChanged;
} Dz1VfsHandleDir;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsHandleDir *Dz1VfsHandleDir_new(
			u32_t handle_id,
			bool_t tagChanged,
			bool_t childChanged,
			bool_t fileChanged, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleDir_del(Dz1VfsHandleDir *p);
static __inline__ void Dz1VfsHandleDir_delAndSetNull(void *ptr)
{
	Dz1VfsHandleDir **p = (Dz1VfsHandleDir **)ptr;
	Dz1VfsHandleDir_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleDir_dump(Dz1VfsHandleDir *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1VfsHandleDir_cmp(Dz1VfsHandleDir *a, Dz1VfsHandleDir *b);
typedef struct Dz1VfsHandleDirInfoList
{
	void *storage;
	Dz1Error (*add)(struct Dz1VfsHandleDirInfoList *p, Dz1VfsHandleDir *data);
	void (*remove)(struct Dz1VfsHandleDirInfoList *p, Dz1VfsHandleDir *key);
	Dz1VfsHandleDir *(*extract)(struct Dz1VfsHandleDirInfoList *p, Dz1VfsHandleDir *key);
	Dz1Error (*travel)(struct Dz1VfsHandleDirInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDir *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1VfsHandleDirInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDir *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1VfsHandleDirInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDir *entry), void *ptr);
	Dz1VfsHandleDir *(*find)(struct Dz1VfsHandleDirInfoList *p, Dz1VfsHandleDir *key);
	unsigned int (*count)(struct Dz1VfsHandleDirInfoList *p);
} Dz1VfsHandleDirInfoList;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsHandleDirInfoList *Dz1VfsHandleDirInfoList_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleDirInfoList_del(Dz1VfsHandleDirInfoList *p);
static __inline__ void Dz1VfsHandleDirInfoList_delAndSetNull(void *ptr)
{
	Dz1VfsHandleDirInfoList **p = (Dz1VfsHandleDirInfoList **)ptr;
	Dz1VfsHandleDirInfoList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleDirInfoList_dump(Dz1VfsHandleDirInfoList *p, int tab);
typedef struct Dz1VfsHandleDirEntry
{
	u32_t idx;
	Dz1Sync *sync;
	Dz1VfsDir *source;
	Dz1VfsHandleDirInfoList *handles;
} Dz1VfsHandleDirEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsHandleDirEntry *Dz1VfsHandleDirEntry_new(
			u32_t idx,
			Dz1Sync *sync,
			Dz1VfsDir *source, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleDirEntry_del(Dz1VfsHandleDirEntry *p);
static __inline__ void Dz1VfsHandleDirEntry_delAndSetNull(void *ptr)
{
	Dz1VfsHandleDirEntry **p = (Dz1VfsHandleDirEntry **)ptr;
	Dz1VfsHandleDirEntry_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleDirEntry_dump(Dz1VfsHandleDirEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1VfsHandleDirEntry_cmp(Dz1VfsHandleDirEntry *a, Dz1VfsHandleDirEntry *b);
typedef struct Dz1VfsHandleDirList
{
	void *storage;
	Dz1Error (*add)(struct Dz1VfsHandleDirList *p, Dz1VfsHandleDirEntry *data);
	void (*remove)(struct Dz1VfsHandleDirList *p, Dz1VfsHandleDirEntry *key);
	Dz1VfsHandleDirEntry *(*extract)(struct Dz1VfsHandleDirList *p, Dz1VfsHandleDirEntry *key);
	Dz1Error (*travel)(struct Dz1VfsHandleDirList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDirEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1VfsHandleDirList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDirEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1VfsHandleDirList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDirEntry *entry), void *ptr);
	Dz1VfsHandleDirEntry *(*find)(struct Dz1VfsHandleDirList *p, Dz1VfsHandleDirEntry *key);
	unsigned int (*count)(struct Dz1VfsHandleDirList *p);
} Dz1VfsHandleDirList;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsHandleDirList *Dz1VfsHandleDirList_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleDirList_del(Dz1VfsHandleDirList *p);
static __inline__ void Dz1VfsHandleDirList_delAndSetNull(void *ptr)
{
	Dz1VfsHandleDirList **p = (Dz1VfsHandleDirList **)ptr;
	Dz1VfsHandleDirList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleDirList_dump(Dz1VfsHandleDirList *p, int tab);
typedef struct Dz1VfsHandleID
{
	u32_t idx;
	u32_t handle;
} Dz1VfsHandleID;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsHandleID *Dz1VfsHandleID_new(u32_t idx, u32_t handle, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleID_del(Dz1VfsHandleID *p);
static __inline__ void Dz1VfsHandleID_delAndSetNull(void *ptr)
{
	Dz1VfsHandleID **p = (Dz1VfsHandleID **)ptr;
	Dz1VfsHandleID_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsHandleID_dump(Dz1VfsHandleID *p, int tab);
typedef enum Dz1VfsAccessPresent
{
	Dz1VfsAccessPresent_dir,
	Dz1VfsAccessPresent_file,
	Dz1VfsAccessPresent_max
} Dz1VfsAccessPresent;

DZ1_CPPLINK str_t Dz1VfsAccessPresentStr(Dz1VfsAccessPresent v);
DZ1_CPPLINK Dz1VfsAccessPresent Dz1VfsAccessPresentFromStr(str_t str);

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsAccessPresent *Dz1VfsAccessPresent_new(Dz1VfsAccessPresent *src, Dz1Error *err);
#define Dz1VfsAccessPresent_del               Dz1u32_del
#define Dz1VfsAccessPresent_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsAccessPresent_dump(Dz1VfsAccessPresent *v, int tab);
typedef struct Dz1VfsAccess
{
	Dz1VfsAccessPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1VfsHandleID *dir;
		Dz1VfsHandleID *file;
	} x;
} Dz1VfsAccess;

DZ1_CPPLINK DZ1_DLLPORT Dz1VfsAccess *Dz1VfsAccess_new(Dz1VfsAccessPresent present, void *ptr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsAccess_del(Dz1VfsAccess *p);
static __inline__ void Dz1VfsAccess_delAndSetNull(void *ptr)
{
	Dz1VfsAccess **p = (Dz1VfsAccess **)ptr;
	Dz1VfsAccess_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT void Dz1VfsAccess_dump(Dz1VfsAccess *p, int tab);
typedef struct Dz1Vfs
{
	Dz1VfsAccess *root;
	Dz1StorageHandle *io;
	Dz1VfsHandleDirList *dirHandles;
	Dz1VfsHandleFileList *fileHandles;
} Dz1Vfs;

DZ1_CPPLINK DZ1_DLLPORT Dz1Vfs *Dz1Vfs_new(
			Dz1VfsAccess *root,
			Dz1StorageHandle *io, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Vfs_del(Dz1Vfs *p);
static __inline__ void Dz1Vfs_delAndSetNull(void *ptr)
{
	Dz1Vfs **p = (Dz1Vfs **)ptr;
	Dz1Vfs_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Vfs_dump(Dz1Vfs *p, int tab);
#endif
