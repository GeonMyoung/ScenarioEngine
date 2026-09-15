#ifndef DZ1_STORAGE_H_LOCAL
#define DZ1_STORAGE_H_LOCAL

#include "dz1_storage_frag.h"

#include <dz1_storage.h>

typedef struct Dz1Storage
{
	FILE					*fp;

	u32_t					 magic;
	Dz1StorageSuperFrag		 hdr;
} Dz1Storage;

#endif