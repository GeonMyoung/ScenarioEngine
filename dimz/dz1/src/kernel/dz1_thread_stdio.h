#ifndef DZ1_THREAD_STDIO_H_LOCAL
#define DZ1_THREAD_STDIO_H_LOCAL

#include <dz1_thread_stdio.h>

DZ1_CPPLINK ssize_t Dz1Thread_etprintf(int tab, const char *fmt, ...);
DZ1_CPPLINK ssize_t Dz1Thread_eprintf(const char *fmt, ...);

DZ1_CPPLINK ssize_t Dz1Thread_etprintb(int tab, void *data, size_t size, size_t align, bool_t printLetter);
DZ1_CPPLINK ssize_t Dz1Thread_eprintb(void *data, size_t size, size_t align, bool_t printLetter);

DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1Thread_setConsoleFILE(Dz1ThreadConsolPrompt prompt, FILE *fp, Dz1Mutex *lock, Dz1Error *err);

#endif