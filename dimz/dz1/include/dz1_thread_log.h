#ifndef DZ1_THREAD_LOG_H
#define DZ1_THREAD_LOG_H

#include <dz1_error.h>

#define DZ1_THREAD_LOG_CRITICAL			0x80000000			// Critical Log Message
#define DZ1_THREAD_LOG_ERROR			0x40000000			// Error Log Message
#define DZ1_THREAD_LOG_FLOW				0x20000000			// Flow Log Message
#define DZ1_THREAD_LOG_WARN				DZ1_THREAD_LOG_FLOW
#define DZ1_THREAD_LOG_MESSAGE			0x10000000			// Additional or Optional Log Message

#define DZ1_THREAD_LOG_TASK_DEBUG		0x08000000
#define DZ1_THREAD_LOG_DEBUG			0x04000000
#define DZ1_THREAD_LOG_RESERVED12		0x02000000
#define DZ1_THREAD_LOG_RESERVED13		0x01000000

#define DZ1_THREAD_LOG_RESERVED20		0x00800000
#define DZ1_THREAD_LOG_RESERVED21		0x00400000
#define DZ1_THREAD_LOG_RESERVED22		0x00200000
#define DZ1_THREAD_LOG_RESERVED23		0x00100000

#define DZ1_THREAD_LOG_RESERVED30		0x00080000
#define DZ1_THREAD_LOG_RESERVED31		0x00040000
#define DZ1_THREAD_LOG_RESERVED32		0x00020000
#define DZ1_THREAD_LOG_RESERVED33		0x00010000

#define DZ1_THREAD_LOG_BASIS			(DZ1_THREAD_LOG_CRITICAL | DZ1_THREAD_LOG_ERROR | DZ1_THREAD_LOG_WARN)

// User Defined LOG Level
#define DZ1_THREAD_LOG_USER01			0x00008000
#define DZ1_THREAD_LOG_USER02			0x00004000
#define DZ1_THREAD_LOG_USER03			0x00002000
#define DZ1_THREAD_LOG_USER04			0x00001000

#define DZ1_THREAD_LOG_USER05			0x00000800
#define DZ1_THREAD_LOG_USER06			0x00000400
#define DZ1_THREAD_LOG_USER07			0x00000200
#define DZ1_THREAD_LOG_USER08			0x00000100

#define DZ1_THREAD_LOG_USER09			0x00000080
#define DZ1_THREAD_LOG_USER10			0x00000040
#define DZ1_THREAD_LOG_USER11			0x00000020
#define DZ1_THREAD_LOG_USER12			0x00000010

#define DZ1_THREAD_LOG_USER13			0x00000008
#define DZ1_THREAD_LOG_USER14			0x00000004
#define DZ1_THREAD_LOG_USER15			0x00000002
#define DZ1_THREAD_LOG_USER16			0x00000001

#define DZ1_THREAD_LOG_MINIMUM			0x00000000

typedef u32_t Dz1ThreadLogLevel;

/*
 * Dz1Thread_setLogLevel : Set Log Level to target thread
 *							after this function return, Log Message will printed out that indicated "level"
 * @id : Target Thread ID
 * @level : Log Level to set
 *
 * return Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Thread_setLogLevel(u32_t id, Dz1ThreadLogLevel level);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Thread_modLogLevelAll(bool_t is_set, Dz1ThreadLogLevel level);	// to all thread

/*
 * Dz1Thread_clrLogLevel : Clear Log Level to target thread
 *							after this function return, Log Message will not printed out that indicated "level"
 *
 * @id : Target Thread ID
 * @level : Log Level to clear
 *
 * return Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Thread_clrLogLevel(u32_t id, Dz1ThreadLogLevel level);

/*
 * Dz1Thread_getLogLevel : Get Log Level of target thread
 *
 * @id : Target Thread ID
 * @level : Log Level
 *
 * return Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Thread_getLogLevel(u32_t id, Dz1ThreadLogLevel *level);
DZ1_CPPLINK DZ1_DLLPORT bool_t	_Dz1Thread_getLogLevel(u32_t id, Dz1ThreadLogLevel *level, Dz1Error *err);

/*
 * Dz1Thread_log : print log message
 *
 * @level : log level of this message
 * @tab : indent level
 * @fmt : format string is same as fmt of printf function
 * @... : variables
 */
DZ1_CPPLINK DZ1_DLLPORT void _Dz1Thread_tlog(int tab, const char *fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT void _Dz1Thread_log(const char *fmt, ...);

DZ1_CPPLINK DZ1_DLLPORT void  Dz1Thread_tlog(Dz1ThreadLogLevel level, int tab, const char *fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT void  Dz1Thread_log(Dz1ThreadLogLevel level, const char *fmt, ...);
#endif
