#ifndef DZ1_THREAD_H
#define DZ1_THREAD_H

#include <dz1.h>
#include <dz1_bits.h>
#include <dz1_error.h>

#include <dz1_thread_log.h>
#include <dz1_thread_status.h>
#include <dz1_thread_stack.h>

#define DZ1_THREAD_INVALID				((u32_t)-1)

#define DZ1_THREAD_MAX					1024
#define DZ1_THREAD_INDEX_SIZE			DZ1_BITS_UNIT_SIZE_ARRAY(DZ1_THREAD_MAX)

#define Dz1Struct_delAndSetNull_push(struct_type, struct_ptr)\
									do {\
										struct_type *__type_checker_##struct_ptr = struct_ptr;\
										__type_checker_##struct_ptr = __type_checker_##struct_ptr;\
										pthread_cleanup_push(struct_type##_delAndSetNull, (void *)(&struct_ptr))

#define Dz1Struct_delAndSetNull_pop(execute_cond)\
										pthread_cleanup_pop(execute_cond);\
									} while(0)

#define Dz1Primitive_delAndSetNull_push(primitive_ptr_type, primitive_ptr)\
									do {\
										primitive_ptr_type __type_checker_##primitive_ptr = primitive_ptr;\
										__type_checker_##primitive_ptr = __type_checker_##primitive_ptr;\
										pthread_cleanup_push(primitive_ptr_type##_delAndSetNull, (void *)(&primitive_ptr))

#define Dz1Primitive_delAndSetNull_pop(execute_cond)\
										pthread_cleanup_pop(execute_cond);\
									} while(0)

typedef Dz1Error (*Dz1ThreadFunc)(void *ptr);

DZ1_CPPLINK DZ1_DLLPORT void	 dz1DefCon_setMode(bool_t wide);
DZ1_CPPLINK DZ1_DLLPORT bool_t	 dz1DefCon_isWide(void);

/*
 * Dz1Thread_init : Register Thread such as main thread to Thread Management Pool
 *
 * @level : Log Level
 * @err : result of execution
 *
 * return thread id
 */
DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1Thread_init(Dz1ThreadLogLevel level, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Thread_clean(void);

typedef struct Dz1ThreadInitEntry
{
	void							 (*init)(void);
	struct Dz1ThreadInitEntry		*next;
} Dz1ThreadInitEntry;
#define Dz1ThreadInitEntryInit(initF)			{ initF, NULL }

typedef struct Dz1ThreadCleanupEntry
{
	void							 (*cleanup)(void);
	struct Dz1ThreadCleanupEntry	*prev;
} Dz1ThreadCleanupEntry;
#define Dz1ThreadCleanupEntryInit(cleanF)		{ cleanF, NULL }

DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1ThreadBarrier_reg(Dz1ThreadInitEntry *init, Dz1ThreadCleanupEntry *clean, Dz1Error *err);

/*
 * Dz1Thread_create : Function to Starting Thread
 *
 * @idp : pointer of thread id that created after this function is returned
 * @func : thread function to execute
 * @func_arg : argument of "func"
 * @level : Dz1ThreadLogLevel
 *
 * return Dz1Error structure
 */
#define Dz1Thread_create(idp, func, func_arg_p, level)	_Dz1Thread_create(idp, #func, func, func_arg_p, level)
DZ1_CPPLINK DZ1_DLLPORT Dz1Error _Dz1Thread_create(u32_t *id, const char *name, Dz1ThreadFunc func, void *func_arg_p, Dz1ThreadLogLevel level);

// pthread_exit
#define Dz1Thread_exit(result) pthread_exit(result)

/*
 * Dz1Thread_self : retrieve thread id
 */
DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1Thread_self(void);

/*
 * Dz1Thread_stop : Stop other thread
 *
 * @id : Thread ID to stopping
 * @detach : detach flag. if you don't need call Dz1Thread_wait, then this flag set to TRUE
 *
 * return Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Thread_stop(u32_t id, bool_t detach);

/*
 * Dz1Thread_wait : Wait until other thread is joined
 *
 * @id : Thread ID to joining
 * @result : Dz1Error structure pointer's address.
 * 			if Target Thread is normally terminated then Dz1Error Structure Pointer has some address.
 * 			else Dz1Error Structure Pointer set to be (Dz1Error *)-1.
 *
 * return Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Thread_wait(u32_t id, Dz1Error *result);

/*
 * Dz1Thread_setCancelState : same as pthread_setcancelstate
 *
 * @state : new cancel state is either PTHREAD_CANCEL_ENABLE or PTHREAD_CANCEL_DISABLE
 * @oldp : previous cancel state
 *
 * return Dz1Error Structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Thread_setCancelState(int state, int *oldp);

/*
 * Dz1Thread_setCancelType : same as pthread_setcanceltype
 *
 * @type : new cancel type is either PTHREAD_CANCEL_DEFERRED or PTHREAD_CANCEL_IMMEDICATE
 * @oldp : previous cancel type
 *
 * return Dz1Error Structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Thread_setCancelType(int type, int *oldp);

#define Dz1Thread_testCancel	pthread_testcancel

/*
 * Dz1Thread_dump : dump all thread information
 *
 * @con : console handler pointer used to output
 * @tab : indent number
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void	_Dz1ThreadA_dump(bool_t dump_pool, int tab);
static __inline__ void			 Dz1ThreadA_dump(int tab) { _Dz1ThreadA_dump(TRUE, tab); }
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	_Dz1ThreadW_dump(bool_t dump_pool, int tab);
static __inline__ void			 Dz1ThreadW_dump(int tab) { _Dz1ThreadW_dump(TRUE, tab); }
#ifdef UNICODE
#define							_Dz1Thread_dump			_Dz1ThreadW_dump
#define							 Dz1Thread_dump			 Dz1ThreadW_dump
#else // UNICODE
#define							_Dz1Thread_dump			_Dz1ThreadA_dump
#define							 Dz1Thread_dump			 Dz1ThreadA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							_Dz1Thread_dump			_Dz1ThreadA_dump
#define							 Dz1Thread_dump			 Dz1ThreadA_dump
#endif // UNIX_SYSTEM

typedef enum Dz1ThreadIODir
{
	Dz1ThreadIODir_in = 		0x1,
	Dz1ThreadIODir_out =		0x2,
} Dz1ThreadIODir;

struct Dz1Console;

typedef Dz1Error (*Dz1ThreadIOWaitF)(void *ptr, Dz1ThreadIODir flag, s32_t wait_us);
typedef int		 (*Dz1ThreadIOGetChF)(void *ptr, s32_t wait_us, Dz1Error *errp);
typedef ssize_t	 (*Dz1ThreadIOWriteF)(void *ptr, u8_t *buf, size_t size, s32_t wait_us, Dz1Error *errp);

typedef enum Dz1ThreadConsolPrompt
{
	Dz1ThreadConsolPrompt_longTime,
	Dz1ThreadConsolPrompt_shortTime,
	Dz1ThreadConsolPrompt_none
} Dz1ThreadConsolPrompt;

DZ1_CPPLINK bool_t Dz1Thread_setConsole(Dz1ThreadConsolPrompt prompt,
										void *priv, Dz1DelFunc priv_del, 
										Dz1ThreadIOWaitF wait,
										Dz1ThreadIOGetChF getch,
										Dz1ThreadIOWriteF write,
										Dz1Error *err);

#endif
