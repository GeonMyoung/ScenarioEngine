#ifndef DZ1_THREAD_STDIO_H
#define DZ1_THREAD_STDIO_H

#include <dz1_mutex.h>
#include <dz1_stdio.h>
#include <dz1_thread.h>

///////////////////////////////////////////////////////////////////////////////
// Print Letter
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1ThreadA_putc(char c, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1ThreadA_fputc(FILE *fp, char c, Dz1Error *err);
// Print Letter
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK DZ1_DLLPORT void Dz1ThreadA_tabprint(int tab);
#define						 Dz1ThreadA_dumptab					Dz1ThreadA_tabprint
DZ1_CPPLINK DZ1_DLLPORT void Dz1ThreadA_ftabprint(FILE *fp, int tab);
#define						 Dz1ThreadA_fdumptab				Dz1ThreadA_ftabprint

///////////////////////////////////////////////////////////////////////////////
// Formatted Print
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_tvprintf(int tab, const char *fmt, va_list ap);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_tprintf(int tab, const char *fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_printf(const char *fmt, ...);

DZ1_CPPLINK DZ1_DLLPORT bool_t	Dz1ThreadA_setFpTab(char *str);	// set single tab string (max 15 letter)
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_ftvprintf(FILE *fp, int tab, const char *fmt, va_list ap);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_ftprintf(FILE *fp, int tab, const char *fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_fprintf(FILE *fp, const char *fmt, ...);
// Formatted Print
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Binary Print
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_tprintb(int tab, void *ptr, size_t size, size_t align, bool_t print_letter);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_printb(void *ptr, size_t size, size_t align, bool_t print_letter);

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_ftprintb(FILE *fp, int tab, void *ptr, size_t size, size_t align);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_fprintb(FILE *fp, void *data, size_t size, size_t align);
// Binary Print
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadA_writeText(char *buf, size_t len, int tab);

#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Print Letter UNICODE
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1ThreadW_putc(wchar_t c, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1ThreadW_fputc(FILE *fp, wchar_t c, Dz1Error *err);
// Print Letter UNICODE
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK DZ1_DLLPORT void Dz1ThreadW_tabprint(int tab);
#define						 Dz1ThreadW_dumptab					Dz1ThreadW_tabprint
DZ1_CPPLINK DZ1_DLLPORT void Dz1ThreadW_ftabprint(FILE *fp, int tab);
#define						 Dz1ThreadW_fdumptab				Dz1ThreadW_ftabprint

///////////////////////////////////////////////////////////////////////////////
// Formatted Print UNICODE
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_tvprintf(int tab, const wchar_t *fmt, va_list ap);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_tprintf(int tab, const wchar_t *fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_printf(const wchar_t *fmt, ...);

DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1ThreadW_setFpTab(wchar_t *str);	// set single tab string (max 15 letter)
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_ftvprintf(FILE *fp, int tab, const wchar_t *fmt, va_list ap);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_ftprintf(FILE *fp, int tab, const wchar_t *fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_fprintf(FILE *fp, const wchar_t *fmt, ...);
// Formatted FILE Print UNICODE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Binary Print UNICODE
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_tprintb(int tab, void *ptr, size_t size, size_t align, bool_t print_letter);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_printb(void *ptr, size_t size, size_t align, bool_t print_letter);
// Binary Print UNICODE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Binary FILE Print UNICODE
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_ftprintb(FILE *fp, int tab, void *ptr, size_t size, size_t align);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_fprintb(FILE *fp, void *data, size_t size, size_t align);
// Binary FILE Print UNICODE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MBCS Argument Formatted Print to Code Free
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Thread_tvprintfA(int tab, const char *fmt, va_list mbcs_ap);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Thread_tprintfA(int tab, const char *fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Thread_printfA(const char *fmt, ...);

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Thread_ftvprintfA(FILE *fp, int tab, const char *fmt, va_list mbcs_ap);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Thread_ftprintfA(FILE *fp, int tab, const char *fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Thread_fprintfA(FILE *fp, const char *fmt, ...);
// MBCS Argument Formatted Print to Code Free
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadW_writeText(wchar_t *buf, size_t len, int tab);

#ifdef UNICODE
#define Dz1Thread_putc			Dz1ThreadW_putc
#define Dz1Thread_fputc			Dz1ThreadW_fputc
#define Dz1Thread_tabprint		Dz1ThreadW_tabprint
#define Dz1Thread_dumptab		Dz1ThreadW_dumptab
#define Dz1Thread_ftabprint		Dz1ThreadW_ftabprint
#define Dz1Thread_fdumptab		Dz1ThreadW_fdumptab

#define Dz1Thread_tvprintf		Dz1ThreadW_tvprintf
#define Dz1Thread_tprintf		Dz1ThreadW_tprintf
#define Dz1Thread_printf		Dz1ThreadW_printf

#define Dz1Thread_setFpTab		Dz1ThreadW_setFpTab
#define Dz1Thread_ftvprintf		Dz1ThreadW_ftvprintf
#define Dz1Thread_ftprintf		Dz1ThreadW_ftprintf
#define Dz1Thread_fprintf		Dz1ThreadW_fprintf

#define Dz1Thread_tprintb		Dz1ThreadW_tprintb
#define Dz1Thread_printb		Dz1ThreadW_printb

#define Dz1Thread_ftprintb		Dz1ThreadW_ftprintb
#define Dz1Thread_fprintb		Dz1ThreadW_fprintb

#define Dz1Thread_writeText		Dz1ThreadW_writeText
#else // UNICODE
#define Dz1Thread_putc			Dz1ThreadA_putc
#define Dz1Thread_fputc			Dz1ThreadA_fputc
#define Dz1Thread_tabprint		Dz1ThreadA_tabprint
#define Dz1Thread_dumptab		Dz1ThreadA_dumptab
#define Dz1Thread_ftabprint		Dz1ThreadA_ftabprint
#define Dz1Thread_fdumptab		Dz1ThreadA_fdumptab

#define Dz1Thread_tvprintf		Dz1ThreadA_tvprintf
#define Dz1Thread_tprintf		Dz1ThreadA_tprintf
#define Dz1Thread_printf		Dz1ThreadA_printf

#define Dz1Thread_setFpTab		Dz1ThreadA_setFpTab
#define Dz1Thread_ftvprintf		Dz1ThreadA_ftvprintf
#define Dz1Thread_ftprintf		Dz1ThreadA_ftprintf
#define Dz1Thread_fprintf		Dz1ThreadA_fprintf

#define Dz1Thread_ftprintb		Dz1ThreadA_ftprintb
#define Dz1Thread_fprintb		Dz1ThreadA_fprintb

#define Dz1Thread_tprintb		Dz1ThreadA_tprintb
#define Dz1Thread_printb		Dz1ThreadA_printb

#define Dz1Thread_writeText		Dz1ThreadA_writeText
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Thread_putc			Dz1ThreadA_putc
#define Dz1Thread_fputc			Dz1ThreadA_fputc
#define Dz1Thread_tabprint		Dz1ThreadA_tabprint
#define Dz1Thread_dumptab		Dz1ThreadA_dumptab
#define Dz1Thread_ftabprint		Dz1ThreadA_ftabprint
#define Dz1Thread_fdumptab		Dz1ThreadA_fdumptab

#define Dz1Thread_tvprintf		Dz1ThreadA_tvprintf
#define Dz1Thread_tprintf		Dz1ThreadA_tprintf
#define Dz1Thread_printf		Dz1ThreadA_printf

#define Dz1Thread_setFpTab		Dz1ThreadA_setFpTab
#define Dz1Thread_ftvprintf		Dz1ThreadA_ftvprintf
#define Dz1Thread_ftprintf		Dz1ThreadA_ftprintf
#define Dz1Thread_fprintf		Dz1ThreadA_fprintf

#define Dz1Thread_ftprintb		Dz1ThreadA_ftprintb
#define Dz1Thread_fprintb		Dz1ThreadA_fprintb

#define Dz1Thread_tprintb		Dz1ThreadA_tprintb
#define Dz1Thread_printb		Dz1ThreadA_printb

#define Dz1Thread_writeText		Dz1ThreadA_writeText

#define Dz1Thread_tvprintfA		Dz1ThreadA_tvprintf
#define Dz1Thread_tprintfA		Dz1ThreadA_tprintf
#define Dz1Thread_printfA		Dz1ThreadA_printf

#define Dz1Thread_ftvprintfA	Dz1ThreadA_ftvprintf
#define Dz1Thread_ftprintfA		Dz1ThreadA_ftprintf
#define Dz1Thread_fprintfA		Dz1ThreadA_fprintf
#endif // UNIX_SYSTEM

// code free dump helper
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadX_ftvprintf(FILE *fp, int tab, char *fmt, va_list ap);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadX_ftprintf(FILE *fp, int tab, char *fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1ThreadX_fprintf(FILE *fp, char *fmt, ...);

DZ1_CPPLINK DZ1_DLLPORT void Dz1ThreadX_dump(void *p, int tab, Dz1DumpFunc dumpA, Dz1DumpFunc dumpW);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ThreadX_fdump(FILE *fp, void *p, int tab, Dz1FDumpFunc dumpA, Dz1FDumpFunc dumpW);
#ifndef UNIX_SYSTEM
#define DZ1_DUMP(struct_name, ptr, tab)						Dz1ThreadX_dump(ptr, tab, (Dz1DumpFunc)struct_name##A_dump, (Dz1DumpFunc)struct_name##W_dump)
#define DZ1_DUMPALT(struct_name, postfix, ptr, tab)			Dz1ThreadX_dump(ptr, tab, (Dz1DumpFunc)struct_name##A_dump##postfix, (Dz1DumpFunc)struct_name##W_dump##postfix)

#define DZ1_FDUMP(fp, struct_name, ptr, tab)				Dz1ThreadX_fdump(fp, ptr, tab, (Dz1FDumpFunc)struct_name##A_fdump, (Dz1FDumpFunc)struct_name##W_fdump)
#define DZ1_FDUMPALT(fp, struct_name, postfix, ptr, tab)	Dz1ThreadX_fdump(fp, ptr, tab, (Dz1FDumpFunc)struct_name##A_fdump##postfix, (Dz1FDumpFunc)struct_name##W_fdump##postfix)
#else
#define DZ1_DUMP(struct_name, ptr, tab)						Dz1ThreadX_dump(ptr, tab, (Dz1DumpFunc)struct_name##A_dump, NULL)
#define DZ1_DUMPALT(struct_name, postfix, ptr, tab)			Dz1ThreadX_dump(ptr, tab, (Dz1DumpFunc)struct_name##A_dump##postfix, NULL)

#define DZ1_FDUMP(fp, struct_name, ptr, tab)				Dz1ThreadX_fdump(fp, ptr, tab, (Dz1FDumpFunc)struct_name##A_fdump, NULL)
#define DZ1_FDUMPALT(fp, struct_name, postfix, ptr, tab)	Dz1ThreadX_fdump(fp, ptr, tab, (Dz1FDumpFunc)struct_name##A_fdump##postfix, NULL)
#endif

//DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Thread_read(u8_t *buf, size_t size, s32_t wait_us, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1Thread_getch(s32_t wait_us, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Thread_getSize(u32_t *width, u32_t *height);

DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1Thread_setConsoleFILE(Dz1ThreadConsolPrompt prompt,FILE *fp, Dz1Mutex *lock, Dz1Error *err);

#endif
