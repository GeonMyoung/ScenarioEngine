#ifndef DZ1_THREAD_H_LOCAL
#define DZ1_THREAD_H_LOCAL

#include "dz1_thread_pool.h"
#include "dz1_console.h"
#include <dz1_thread.h>

DZ1_CPPLINK Dz1ThreadEntry *_Dz1Thread_self(void);
DZ1_CPPLINK Dz1Console *Dz1Thread_getOwnConsole(void);
DZ1_CPPLINK Dz1ConsoleMode dz1DefCon_getMode(void);

#endif
