#ifndef DZ1_STORAGE_FRAG_H_LOCAL
#define DZ1_STORAGE_FRAG_H_LOCAL

#include <dz1_bin.h>

#define DZ1_STORAGE_FRAG_SIZE			4096
#define DZ1_STORAGE_FRAG_DATA_SIZE		4086
// ¾à 15T size
typedef struct Dz1StorageFrag
{
	u32_t					 prev_idx;
	u32_t					 next_idx;
#define DZ1_STORAGE_FRAG_FREE_CHUNK		0xFFFF
	u16_t					 chunk_size;
	u8_t					 data[DZ1_STORAGE_FRAG_DATA_SIZE];
} Dz1StorageFrag;

//DZ1_CPPLINK Dz1StorageFrag *Dz1StorageFrag_new(Dz1Error *err);
//DZ1_CPPLINK void Dz1StorageFrag_del(Dz1StorageFrag *p);
DZ1_CPPLINK void Dz1StorageFrag_dump(Dz1StorageFrag *p, int tab);
/*
static __inline__ void Dz1StorageFrag_delAndSetNull(void *pptr)
{
	Dz1StorageFrag **p = (Dz1StorageFrag **)pptr;
	Dz1StorageFrag_del(*p); *p = NULL;
}
*/

DZ1_CPPLINK Dz1Error	 Dz1StorageFrag_load(FILE *fp, u32_t idx, Dz1StorageFrag *dst);
DZ1_CPPLINK Dz1Error	 Dz1StorageFrag_save(FILE *fp, u32_t idx, Dz1StorageFrag *src);

DZ1_CPPLINK Dz1Error	 Dz1StorageFrag_loadInfo(FILE *fp, u32_t idx, Dz1StorageFrag *dst);
DZ1_CPPLINK Dz1Error	 Dz1StorageFrag_saveInfo(FILE *fp, u32_t idx, Dz1StorageFrag *src);

DZ1_CPPLINK Dz1Binary	*Dz1StorageFrag_loadBin(FILE *fp, u32_t idx, Dz1Error *err);
DZ1_CPPLINK Dz1Error	 Dz1StorageFrag_saveBuf(FILE *fp, u32_t idx, u8_t *src, size_t size, u32_t *space_start);

DZ1_CPPLINK Dz1Error	 Dz1StorageFrag_size(FILE *fp, u32_t start_idx, u64_t *ret);
DZ1_CPPLINK u32_t		 Dz1StorageFrag_append(FILE *fp, Dz1Error *err);
DZ1_CPPLINK Dz1Error	 Dz1StorageFrag_free(FILE *fp, u32_t free_idx, u32_t *space_start, Dz1StorageFrag *free_frag);


typedef struct Dz1StorageSuperFrag
{
	u32_t						magic;
	u32_t						version;
	u32_t						space_start;
} Dz1StorageSuperFrag;

DZ1_CPPLINK Dz1Error	 Dz1StorageSuperFrag_load(FILE *fp, Dz1StorageSuperFrag *dst);
DZ1_CPPLINK Dz1Error	 Dz1StorageSuperFrag_save(FILE *fp, Dz1StorageSuperFrag *src);

#endif