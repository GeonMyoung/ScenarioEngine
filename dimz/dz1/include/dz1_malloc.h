#ifndef DZ1_MALLOC_H
#define DZ1_MALLOC_H

#include <dz1_error.h>

/*
 * Dz1Malloc : Allocate Memory
 *
 * @size : amount size
 * @errp : Address of Dz1Error structure
 *
 * return : Address of allocated memory or NULL
 */
#define						   Dz1Malloc(size, errp) _Dz1Malloc(size, errp, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT void *_Dz1Malloc(size_t size, Dz1Error *err, const char *file, int line);

/*
 * Dz1Calloc : Allocate Memory and Clear
 *
 * @size : amount size
 * @errp : Address of Dz1Error structure
 *
 * return : Address of allocated memory or NULL
 */
#define						   Dz1Calloc(unit, numb, errp) _Dz1Calloc(unit, numb, errp, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT void *_Dz1Calloc(size_t unit, size_t numb, Dz1Error *err, const char *file, int line);

/*
 * Dz1Free : Release Memory
 *
 * @ptr : Address of allocated memory
 *
 * return : Dz1Error structure
 */
#define						  Dz1Free(ptr) _Dz1Free(ptr, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT void _Dz1Free(void *ptr, const char *file, int line);

static __inline__ void		  Dz1Memory_cancel(void *p) { if (p) Dz1Free(p); }
static __inline__ void		  Dz1Memory_freeAndSetNull(void *ptr)
{
	void **p = (void **)ptr;
	if (p)
	{
		if (*p != NULL) Dz1Free(*p);
		*p = NULL;
	}
}

/*
 * Dz1Memory_clone : Clone Memory
 *
 * @ptr : Address of allocated memory
 * @sz  : Size of allocated memory
 * @errp : Address of Dz1Error structure
 *
 * return : Address of cloned memory or NULL
 */
#define						   Dz1Memory_clone(p, sz, errp) _Dz1Memory_clone((p), (sz), (errp), __FILE__, __LINE__)
static __inline__ void		 *_Dz1Memory_clone(void *p, size_t size, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	void *ret = size > 0 ? _Dz1Malloc(size, errp, __file__, __line__) : NULL;
	if (ret) memcpy(ret, p, size);
	return ret;
}

/*
 * Dz1Mem_freez : Increace Memory Debugging Tag value
 *
 * return : Old Tag Value
 */
DZ1_CPPLINK DZ1_DLLPORT int Dz1Mem_freez(void);

/*
 * Dz1Mem_melt : Decreace Memory Debugging Tag value
 *
 * return : Old Tag Value
 */
DZ1_CPPLINK DZ1_DLLPORT int Dz1Mem_melt(void);

/*
 * Dz1Mem_getFreez : Get Current Memory Debugging Tag value
 *
 * return : Tag Value
 */
DZ1_CPPLINK DZ1_DLLPORT int Dz1Mem_getFreez(void);

DZ1_CPPLINK DZ1_DLLPORT void Dz1Mem_setTracker(void *ptr);

/*
 * Dz1Mem_export : Write Memory Allocation Information to FILE stream
 *
 * @fp : target File Stream
 * @binDump : export behavior flag
 * 			  this value is TRUE then each frag will dump entire memory
 */

DZ1_CPPLINK DZ1_DLLPORT void Dz1MemA_export(FILE *fp, bool_t binDump);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1MemW_export(FILE *fp, bool_t binDump);
#ifdef UNICODE
#define Dz1Mem_export			Dz1MemW_export
#else // UNICODE
#define Dz1Mem_export			Dz1MemA_export
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Mem_export			Dz1MemA_export
#endif
/*
 * Dz1Mem_dump : Print Memory Allocation Information to target console
 *
 * @freezNum : Tag Value which to print out
 * @binDump : print behavior flag
 * 			  this value is TRUE then each frag will dump entire memory
 * @tab : indant level
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1MemA_dump(int freezNum, int dump_bin, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1MemW_dump(int freezNum, int dump_bin, int tab);
#ifdef UNICODE
#define Dz1Mem_dump				Dz1MemW_dump
#else // UNICODE
#define Dz1Mem_dump				Dz1MemA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Mem_dump				Dz1MemA_dump
#endif

#endif

