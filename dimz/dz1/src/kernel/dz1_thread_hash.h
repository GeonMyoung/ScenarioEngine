#ifndef DZ1_THREAD_HASH_H_LOCAL
#define DZ1_THREAD_HASH_H_LOCAL

#include "dz1_thread_entry.h"

#define DZ1_THREAD_HASH_SIZE		1027

typedef struct Dz1ThreadBucket
{
	struct Dz1ThreadBucket *prev;
	struct Dz1ThreadBucket *next;
	struct Dz1ThreadEntry *slot;
} Dz1ThreadBucket;

typedef struct Dz1ThreadHash
{
	Dz1ThreadBucket *bucket[DZ1_THREAD_HASH_SIZE];
} Dz1ThreadHash;

DZ1_CPPLINK Dz1ThreadEntry *Dz1ThreadHash_add(Dz1ThreadHash *p, u32_t id, Dz1ThreadLogLevel level, Dz1Console *con,
																str_t name, Dz1ThreadFunc func, Dz1Error *fret, Dz1Error *err);
DZ1_CPPLINK void Dz1ThreadHash_remove(Dz1ThreadHash *p, Dz1ThreadEntry *e);
DZ1_CPPLINK Dz1ThreadEntry *Dz1ThreadHash_find(Dz1ThreadHash *p, Dz1ThreadEntry *key);

DZ1_CPPLINK double Dz1ThreadHash_analysis(Dz1ThreadHash *p);

#endif
