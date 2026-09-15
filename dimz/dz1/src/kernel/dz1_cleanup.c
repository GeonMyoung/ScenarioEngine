#include <stdlib.h>
#include <dz1_cleanup.h>
#include <dz1_malloc.h>
#include "dz1_thread.h"

static Dz1CancelFunc _memoryExporter = NULL;
static void *_memoryExporterArg = NULL;

void Dz1Cleanup_setMemoryExporter(Dz1CancelFunc _func, void *_funcParam)
{
	_memoryExporter = _func;
	_memoryExporterArg = _funcParam;
}

///////////////////////////////////////////////////////////////////////////////
// Memory Cleaner
static void Dz1Mem_clean(void *ptr)
{
	Dz1Thread_clean();
	if (_memoryExporter == NULL)
	{
#if defined(__BORLANDC__)
		FILE *fp = _fdopen(1, "w");
		Dz1MemA_export(fp, TRUE);
#else
		FILE *fp = stdout;
#endif
#ifndef UNIX_SYSTEM
		switch(dz1DefCon_getMode())
		{
		case Dz1ConsoleMode_mbcs: Dz1MemA_export(fp, TRUE); break;
		case Dz1ConsoleMode_wide: Dz1MemW_export(fp, TRUE); break;
		}
#else
		Dz1Mem_export(fp, TRUE);
#endif
	}
	else _memoryExporter(_memoryExporterArg);
}

// static void Dz1MemA_clean(void *ptr)
// {
// 	Dz1Thread_clean();
// 	if (_memoryExporter == NULL)
// 	{
// #if defined(__BORLANDC__)
// 		FILE *fp = _fdopen(1, "w");
// 		Dz1MemA_export(fp, TRUE);
// #else
// 		Dz1MemA_export(stdout, TRUE);
// #endif
// 	}
// 	else _memoryExporter(_memoryExporterArg);
// }
// #ifndef UNIX_SYSTEM
// static void Dz1MemW_clean(void *ptr)
// {
// 	Dz1Thread_clean();
// 	if (_memoryExporter == NULL)
// 	{
// #if defined(__BORLANDC__)
// 		FILE *fp = _fdopen(1, "w");
// 		Dz1MemW_export(fp, TRUE);
// #else
// 		Dz1MemW_export(stdout, TRUE);
// #endif
// 	}
// 	else _memoryExporter(_memoryExporterArg);
// }
// #endif
// Memory Cleaner
///////////////////////////////////////////////////////////////////////////////

static pthread_mutex_t	 dz1CleanupLock = PTHREAD_MUTEX_INITIALIZER;
static int				 initialized = FALSE;
#define DZ1_CLEANUP_DYNAMIC_PHASE_START				1

typedef struct Dz1CleanupEntry
{
	Dz1CancelFunc	 func;
	void			*ptr;
} Dz1CleanupEntry;



/////////////<<
static struct Dz1CleanupEntry dz1Cleanup[DZ1_CLEANUP_MAX] =
{
	{ Dz1Mem_clean, NULL },
	{ NULL, NULL }
};

static Dz1CleanupEntry *dz1CleanupFirstPtr	= &dz1Cleanup[DZ1_CLEANUP_DYNAMIC_PHASE_START];
static Dz1CleanupEntry *dz1CleanupLastPtr	= &dz1Cleanup[DZ1_CLEANUP_MAX - 1];
static Dz1CleanupEntry *dz1CleanupPushPtr	= &dz1Cleanup[DZ1_CLEANUP_DYNAMIC_PHASE_START];

Dz1Error Dz1Cleanup_reg(Dz1CancelFunc func, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	pthread_mutex_lock(&dz1CleanupLock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1CleanupLock);

	if (!initialized) Dz1Error_set(errp, ENOSYS);
	else if (dz1CleanupPushPtr > dz1CleanupLastPtr) Dz1Error_set(&err, ENOMEM);
	else if (func == NULL) Dz1Error_set(&err, EINVAL);
	else
	{
		dz1CleanupPushPtr->func = func;
		dz1CleanupPushPtr->ptr = ptr;

		dz1CleanupPushPtr++;
	}

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1CleanupLock);

	return err;
}

void Dz1Cleanup(void)
{
	dz1CleanupPushPtr--;
	while(dz1CleanupFirstPtr <= dz1CleanupPushPtr)
	{
		dz1CleanupPushPtr->func(dz1CleanupPushPtr->ptr);
		dz1CleanupPushPtr--;
	}
}

static void _Dz1Cleanup(void)
{
	Dz1Cleanup();
	while(dz1Cleanup <= dz1CleanupPushPtr)
	{
		dz1CleanupPushPtr->func(dz1CleanupPushPtr->ptr);
		dz1CleanupPushPtr--;
	}
#ifdef __BORLANDC__
#ifdef _DEBUG
	{
		FILE *fp = fdopen(0, "r");
		printf("Press any key..."); fgetc(fp);
	}
#endif
#endif
}

Dz1Error _Dz1Cleanup_init(bool_t stdio_is_wide)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	pthread_mutex_lock(&dz1CleanupLock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1CleanupLock);
	if (initialized == FALSE)
	{
		int code = atexit(_Dz1Cleanup);
		if (code) Dz1Error_set(&err, code);
		else 
		{
			dz1DefCon_setMode(stdio_is_wide);
			initialized = TRUE;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock);

	Dz1Error_set(errp, 0);
	return err;
}
