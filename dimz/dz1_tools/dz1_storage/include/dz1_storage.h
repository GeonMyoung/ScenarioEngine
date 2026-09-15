#ifndef DZ1_STORAGE_H
#define DZ1_STORAGE_H

#include <dz1_io_stream.h>
#include <dz1_storage_def.h>

#define DZ1_STORAGE_FRAG_IDX_NONE				0
#define DZ1_STORAGE_FRAG_IDX_MAIN				1
#define DZ1_STORAGE_FRAG_IDX_ERROR				(u32_t)(-1)
#define DZ1_STROAGE_FILE_MAGIC(a, b, c, d)		((((u32_t)(a) & 0xFF) << 24) | (((u32_t)(b) & 0xFF) << 16) | (((u32_t)(c) & 0xFF) << 8) | (((u32_t)(c) & 0xFF) & 0xFF))

// if is_created == NULL Creation Function does not create file
DZ1_CPPLINK Dz1StorageHandle	*Dz1StorageA_new(str_t fn,					u32_t magic, bool_t *is_created, Dz1Error *err);
DZ1_CPPLINK Dz1StorageHandle	*Dz1StorageA_new2(str_t path, str_t name,	u32_t magic, bool_t *is_created, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK Dz1StorageHandle	*Dz1StorageW_new(wstr_t fn,					u32_t magic, bool_t *is_created, Dz1Error *err);
DZ1_CPPLINK Dz1StorageHandle	*Dz1StorageW_new2(wstr_t path, wstr_t name,	u32_t magic, bool_t *is_created, Dz1Error *err);
#ifdef	UNICODE
#define Dz1Storage_new			Dz1StorageW_new
#define Dz1Storage_new2			Dz1StorageW_new2
#else //UNICODE
#define Dz1Storage_new			Dz1StorageA_new
#define Dz1Storage_new2			Dz1StorageA_new2
#endif//UNICODE
#else //UNIX_SYSTEM
#define Dz1Storage_new			Dz1StorageA_new
#define Dz1Storage_new2			Dz1StorageA_new2
#endif//UNIX_SYSTEM

DZ1_CPPLINK void Dz1Storage_del(Dz1StorageHandle *p);

static __inline__ void Dz1Storage_delAndSetNull(void *pptr)
{
	Dz1StorageHandle **p = (Dz1StorageHandle **)pptr;
	Dz1Storage_del(*p); *p = NULL;
}

DZ1_CPPLINK void Dz1Storage_dump(Dz1StorageHandle *ptr, int tab);

DZ1_CPPLINK u32_t	 Dz1Storage_alloc(Dz1StorageHandle *ptr, Dz1Error *err);
DZ1_CPPLINK Dz1Error Dz1Storage_free(Dz1StorageHandle *ptr, u32_t idx);

typedef struct Dz1SotrageAllocCancelArg
{
	Dz1StorageHandle			*io;
	u32_t						 alloc_idx;
} Dz1SotrageAllocCancelArg;
static __inline__ void Dz1Storage_allocCancel(void *struct_Dz1SotrageAllocCancelArg)
{
	Dz1SotrageAllocCancelArg *arg = (Dz1SotrageAllocCancelArg *)struct_Dz1SotrageAllocCancelArg;
	Dz1Storage_free(arg->io, arg->alloc_idx);
}

DZ1_CPPLINK Dz1StorageChunkList	*Dz1Storage_getEntries(Dz1StorageHandle *ptr, Dz1Error *err);

DZ1_CPPLINK u8_t				*Dz1Storage_load(Dz1StorageHandle *ptr, u32_t entry_idx, size_t *ret_size, Dz1Error *err);
DZ1_CPPLINK Dz1Error			 Dz1Storage_save(Dz1StorageHandle *ptr, u32_t entry_idx, u8_t *data, size_t size);

DZ1_CPPLINK Dz1Binary			*Dz1Storage_loadBin(Dz1StorageHandle *ptr, u32_t entry_idx, Dz1Error *err);
DZ1_CPPLINK Dz1Error			 Dz1Storage_saveBin(Dz1StorageHandle *ptr, u32_t entry_idx, Dz1Binary *src);

DZ1_CPPLINK Dz1StorageInfo		*Dz1Storage_analysis(Dz1StorageHandle *ptr, Dz1Error *err);
DZ1_CPPLINK Dz1Error			 Dz1Sotrage_sort(Dz1StorageHandle *ptr);

static __inline__ void			 Dz1StorageHandle_del(Dz1StorageHandle *p) { Dz1Storage_del(p); }
static __inline__ void			 Dz1StorageHandle_delAndSetNull(void *pptr) { Dz1Storage_delAndSetNull(pptr); }
static __inline__ void			 Dz1StorageHandle_dump(Dz1StorageHandle *p, int tab) { Dz1Storage_dump(p, tab); }

//DZ1_CPPLINK Dz1InStream		*Dz1StorageInStream_open(Dz1StorageHandle *ptr, u32_t open_idx, Dz1Error *err);
//DZ1_CPPLINK Dz1OutStream		*Dz1StorageOutStream_open(Dz1StorageHandle *ptr, u32_t open_idx, bool_t keepData, Dz1Error *err);

DZ1_CPPLINK Dz1Stream			*Dz1StorageStream_open(Dz1StorageHandle *ptr, u32_t open_idx, Dz1StreamFileMode mode, Dz1Error *err);

DZ1_CPPLINK u32_t				 Dz1Storage_import(Dz1StorageHandle *ptr, Dz1Stream *src, Dz1Error *err);

#endif