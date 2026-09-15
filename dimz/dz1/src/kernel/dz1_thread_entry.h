#ifndef DZ1_THREAD_ENTRY_H_LOCAL
#define DZ1_THREAD_ENTRY_H_LOCAL

#include <dz1_thread.h>
#include "dz1_console.h"

struct Dz1ThreadBucket;

//typedef Dz1Error (*Dz1ThreadFunc)(void *ptr);

typedef struct Dz1ThreadEntry
{
	pthread_t				 th;		// System Thread ID
	struct Dz1ThreadBucket	*bucket;	// Pointer of it's bucket
	u32_t					 id;		// Thread ID
	Dz1ThreadLogLevel		 level;		// Log Level for this Thread
	Dz1ThreadStatus			 status;	// Current Thread Status
	Dz1Console				*con;		// Associated Console
	str_t					 name;		// name of thread
	Dz1ThreadFunc			 func;		// Thread Function Pointer
	Dz1Error				*err;		// func result
	Dz1ThreadStack			*stack;		// Stack Tracking Information
} Dz1ThreadEntry;

#define DZ1_THREAD_ENTRY_INITIALIZER				{ pthread_self() }

DZ1_CPPLINK Dz1ThreadEntry *Dz1ThreadEntry_new(struct Dz1ThreadBucket *b, int id, pthread_t th, Dz1ThreadLogLevel level,
											Dz1Console *con, str_t name, Dz1ThreadFunc func, Dz1Error *fret, Dz1Error *err);
DZ1_CPPLINK void Dz1ThreadEntry_del(Dz1ThreadEntry *p);
DZ1_CPPLINK void Dz1ThreadEntryA_dump(Dz1Console *con, Dz1ThreadEntry *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void Dz1ThreadEntryW_dump(Dz1Console *con, Dz1ThreadEntry *p, int tab);
#ifdef UNICODE
#define Dz1ThreadEntry_dump			Dz1ThreadEntryW_dump
#else // UNICODE
#define Dz1ThreadEntry_dump			Dz1ThreadEntryA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1ThreadEntry_dump			Dz1ThreadEntryA_dump
#endif // UNIX_SYSTEM
static __inline__ void Dz1ThreadEntry_delAndSetNull(void *ptr)
{
	Dz1ThreadEntry **p = (Dz1ThreadEntry **)ptr;
	Dz1ThreadEntry_del(*p); *p = NULL;
}

#endif
