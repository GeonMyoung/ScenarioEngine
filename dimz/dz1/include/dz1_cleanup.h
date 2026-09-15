#ifndef DZ1_CLEANUP_H
#define DZ1_CLEANUP_H

#include <dz1_error.h>

#define DZ1_CLEANUP_MAX		32
DZ1_CPPLINK DZ1_DLLPORT void Dz1Cleanup_setMemoryExporter(Dz1CancelFunc _func, void *_funcParam);

/*
 * Dz1Cleanup_reg : Register process cleanup function
 *
 * @func : process cleanup func
 * @ptr : address of argument structure
 *
 * return : Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Cleanup_reg(Dz1CancelFunc func, void *ptr);

/*
 * Dz1Cleanup : Execute Cleanup Process manually
 */
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Cleanup(void);

/*
 * Dz1Cleanup_init : Initialize Cleanup Feature
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error _Dz1Cleanup_init(bool_t stdio_is_wide);
#ifndef UNIX_SYSTEM
#ifdef UNICODE
#define							  Dz1Cleanup_init()		do { _Dz1Cleanup_init(1); } while(0)
#else // UNICODE
#define							  Dz1Cleanup_init()		do { _Dz1Cleanup_init(0); } while(0)
#endif // UNICODE
#else // UNIX_SYSTEM
#define							  Dz1Cleanup_init()		do { _Dz1Cleanup_init(0); } while(0)
#endif // UNIX_SYSTEM

#endif
