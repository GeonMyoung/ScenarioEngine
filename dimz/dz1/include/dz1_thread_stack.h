#ifndef DZ1_THREAD_STACK_H
#define DZ1_THREAD_STACK_H

typedef struct Dz1ThreadStack
{
	str_t file;
	__DZ1ALIGN(int, line);
	str_t text;
	str_t comment;
	struct Dz1ThreadStack *next;
} Dz1ThreadStack;

#ifdef DZ1_THREAD_STACK_TRACE

DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1Thread_stackPush(Dz1ThreadStack *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Thread_stackPop(void *ptr);

#define DZ1_THREAD_CALL_COMMENT_SIZE		DZ1_ALIGNED_SIZE(128)
#define DZ1_THREAD_CALL_ARG					__comment__, DZ1_THREAD_CALL_COMMENT_SIZE
#endif

#ifdef DZ1_THREAD_STACK_TRACE
#define Dz1Thread_stackTrace_push()	\
{\
	Dz1ThreadStack __mark__ = { __FILE__, __LINE__, { 0, }, NULL, NULL, NULL };\
	Dz1Thread_stackPush(&__mark__);\
	pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_stackPop, NULL);

#define Dz1Thread_stackTrace_pop() \
	pthread_cleanup_pop(1);\
}
#else
#define Dz1Thread_stackTrace_push()		do { } while(0)
#define Dz1Thread_stackTrace_pop()		do { } while(0)
#endif

#ifdef DZ1_THREAD_STACK_TRACE
#define Dz1Thread_stackTrace_PUSH(snprintfarg)	\
{\
	char __comment__[DZ1_ALIGNED_SIZE(128)]; \
	Dz1ThreadStack __mark__ = { __FILE__, __LINE__, { 0, }, NULL, __comment__, NULL };\
	snprintf snprintfarg;\
	Dz1Thread_stackPush(&__mark__);\
	pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_stackPop, NULL);

#define Dz1Thread_stackTrace_POP() \
	pthread_cleanup_pop(1);\
}
#else
#define Dz1Thread_stackTrace_PUSH(s)	do { } while(0)
#define Dz1Thread_stackTrace_POP()		do { } while(0)
#endif

/*
 * Dz1Thread_proc : Stack Trace Macro for void type function
 *
 * @func : void type function call statements (not function name only)
 *
 */
#ifdef DZ1_THREAD_STACK_TRACE
#define Dz1Thread_proc(func) \
do {\
	Dz1ThreadStack __mark__ = { __FILE__, __LINE__, { 0, }, #func, NULL, NULL };\
	if (Dz1Thread_stackPush(&__mark__)) \
	{ \
		pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_stackPop, NULL);\
		func;\
		pthread_cleanup_pop(1);\
	}\
	else \
	{\
		func;\
	}\
} while(0)
#else
#define Dz1Thread_proc(func)		do { func; } while(0)
#endif
/*
 * Dz1Thread_call : Stack Trace Macro for non void type function
 *
 * @ret : return variable is same type of "func"
 * @func : non void type function call statements (not function name only)
 *
 */

#ifdef DZ1_THREAD_STACK_TRACE
#define Dz1Thread_call(ret, func) \
do {\
	Dz1ThreadStack __mark__ = { __FILE__, __LINE__, { 0, }, #func, NULL, NULL };\
	if (Dz1Thread_stackPush(&__mark__)) \
	{ \
		pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_stackPop, NULL);\
		ret = func;\
		pthread_cleanup_pop(1);\
	}\
 	else \
 	{\
		ret = func;\
 	}\
} while(0)
#else
#define Dz1Thread_call(ret, func)		do { ret = func; } while(0)
#endif

/*
 * Dz1Thread_PROC : Stack Trace Macro with Comment for void type function
 *
 * @func : void type function call statements (not function name only)
 * @comment_args : same as snprintf.
 * 
 * example)
 * 	Dz1Thread_PROC(SomeFunc(arg1, arg2, arg3), (DZ1_THREAD_CALL_ARG, "arg1 = %d, arg2 = %d, arg3 = %d", arg1, arg2, arg3))
 *
 */
#ifdef DZ1_THREAD_STACK_TRACE
#define Dz1Thread_PROC(func, comment_args) \
do {\
	char __comment__[DZ1_ALIGNED_SIZE(128)]; \
	Dz1ThreadStack __mark__ = { __FILE__, __LINE__, { 0, }, #func, __comment__, NULL };\
	snprintf comment_args;\
	if (Dz1Thread_stackPush(&__mark__)) \
	{\
		pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_stackPop, NULL);\
		func;\
		pthread_cleanup_pop(1);\
	}\
	else func;\
} while(0)
#else
#define Dz1Thread_PROC(func, comment_args)		do { func; } while(0)
#endif
/*
 * Dz1Thread_FUNC : Stack Trace Macro with Comment for non void type function
 *
 * @ret : return variable is same type of "func"
 * @func : non void type function call statements (not function name only)
 * @comment_args : same as snprintf.
 * 
 * example)
 * 	Dz1Thread_CALL(err, SomeFunc(arg1, arg2, arg3), (DZ1_THREAD_CALL_ARG, "arg1 = %d, arg2 = %d, arg3 = %d", arg1, arg2, arg3))
 *
 */
#ifdef DZ1_THREAD_STACK_TRACE
#define Dz1Thread_CALL(ret, func, comment_args) \
do {\
	char __comment__[DZ1_ALIGNED_SIZE(128)]; \
	Dz1ThreadStack __mark__ = { __FILE__, __LINE__, { 0, }, #func, __comment__, NULL };\
	snprintf comment_args;\
	if (Dz1Thread_stackPush(&__mark__)) \
	{\
		pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_stackPop, NULL);\
		ret = func;\
		pthread_cleanup_pop(1);\
	}\
	else ret = func;\
} while(0)
#else
#define Dz1Thread_CALL(ret, func, comment_args)		do { ret = func; } while(0)
#endif
#endif
