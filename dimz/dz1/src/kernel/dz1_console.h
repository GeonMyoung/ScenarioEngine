#ifndef DZ1_CONSOLE_LOCAL_H
#define DZ1_CONSOLE_LOCAL_H

#include <dz1_stdio.h>
#include "dz1_console_prompt.h"
#include "dz1_console_tty_platform.h"

typedef enum
{
	Dz1ConsoleCR_CR,
	Dz1ConsoleCR_CRLF
} Dz1ConsoleCR;

typedef enum Dz1ConsoleMode
{
	Dz1ConsoleMode_mbcs,
	Dz1ConsoleMode_wide
} Dz1ConsoleMode;

struct Dz1Console;

typedef Dz1Error	 (*Dz1ConsoleFunc)(void *con, void *funcArg, int inputIdleTimeout_sec);
typedef void		 (*Dz1ConsolePlatformDelFunc)(Dz1ConsolePlatform *p);

typedef struct Dz1Console
{
	Dz1ConsolePrompt			 prompt;
  
	u32_t						 width;
	u32_t						 height;
	Dz1ConsoleCR				 cr;
	int							 col;

	Dz1ConsolePlatform			*platform;
	Dz1ConsolePlatformDelFunc	 platformDel;

	bool_t						 cr_output;

	pthread_mutex_t				 lockIn;
	pthread_mutex_t				 lockOut;
} Dz1Console;

//DZ1_CPPLINK Dz1Console	*Dz1Console_new(Dz1ConsolePlatform *platform, Dz1ConsolePlatformDelFunc privDel, Dz1Error *err);
DZ1_CPPLINK Dz1Console	*Dz1Console_new(Dz1ConsolePromptMode prompt, Dz1ConsolePlatform *platform, Dz1Error *err);
DZ1_CPPLINK void		 Dz1Console_del(Dz1Console *p);
static __inline__ void	 Dz1Console_delAndSetNull(void *ptr)
{
	Dz1Console **p = (Dz1Console **)ptr;
	Dz1Console_del(*p); *p = NULL;
}

DZ1_CPPLINK Dz1Error Dz1Console_wait(Dz1Console *con, Dz1ThreadIODir flag, s32_t wait_us);
DZ1_CPPLINK int		 Dz1Console_getch(Dz1Console *con, s32_t wait_us, Dz1Error *err);
DZ1_CPPLINK ssize_t	 Dz1Console_write(Dz1Console *con, u8_t *buf, size_t size, s32_t wait_us, Dz1Error *err);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK ssize_t _dz1_core_codeconv(u8_t *dst, size_t dst_byte_size, const char *dstcs, u8_t *src, size_t src_byte_size, const char *srccs);

DZ1_CPPLINK ssize_t	 Dz1Console_etvprintf(Dz1Console *con, int tab, const char *fmt, va_list ap);
DZ1_CPPLINK ssize_t	 Dz1Console_etprintf(Dz1Console *con, int tab, const char *fmt, ...);

DZ1_CPPLINK ssize_t	 Dz1Console_etprintb(Dz1Console *con, int tab, void *buf, size_t size, size_t align, bool_t printLetter);
#else
#define				 Dz1Console_etvprintf		Dz1ConsoleA_tvprintf
#define				 Dz1Console_etprintf		Dz1ConsoleA_tprintf

#define				 Dz1Console_etprintb		Dz1ConsoleA_tprintb
#endif
//////////////////////
// MBCS Part
DZ1_CPPLINK ssize_t	 Dz1ConsoleA_writeText(Dz1Console *con, char *buf, size_t len, int tab);

DZ1_CPPLINK ssize_t	 Dz1ConsoleA_tvprintf(Dz1Console *con, int tab, const char *fmt, va_list ap);
DZ1_CPPLINK ssize_t	 Dz1ConsoleA_tprintf(Dz1Console *con, int tab, const char *fmt, ...);

DZ1_CPPLINK ssize_t	 Dz1ConsoleA_vprintf(Dz1Console *con, const char *fmt, va_list ap);
DZ1_CPPLINK ssize_t	 Dz1ConsoleA_printf(Dz1Console *con, const char *fmt, ...);

DZ1_CPPLINK ssize_t	 Dz1ConsoleA_tprintb(Dz1Console *con, int tab, void *data, size_t data_size, size_t align, bool_t print_letter);
DZ1_CPPLINK ssize_t	 Dz1ConsoleA_printb(Dz1Console *con, void *data, size_t data_size, size_t align, bool_t print_letter);
// MBCS Part
//////////////////////

#ifndef UNIX_SYSTEM
//////////////////////
// UNICODE Part
DZ1_CPPLINK ssize_t	 Dz1ConsoleW_writeText(Dz1Console *con, wchar_t *buf, size_t len, int tab);

DZ1_CPPLINK ssize_t	 Dz1ConsoleW_tvprintf(Dz1Console *con, int tab, const wchar_t *fmt, va_list ap);
DZ1_CPPLINK ssize_t	 Dz1ConsoleW_tprintf(Dz1Console *con, int tab, const wchar_t *fmt, ...);

DZ1_CPPLINK ssize_t	 Dz1ConsoleW_vprintf(Dz1Console *con, const wchar_t *fmt, va_list ap);
DZ1_CPPLINK ssize_t	 Dz1ConsoleW_printf(Dz1Console *con, const wchar_t *fmt, ...);

DZ1_CPPLINK ssize_t	 Dz1ConsoleW_tprintb(Dz1Console *con, int tab, void *data, size_t data_size, size_t align, bool_t print_letter);
DZ1_CPPLINK ssize_t	 Dz1ConsoleW_printb(Dz1Console *con, void *data, size_t data_size, size_t align, bool_t print_letter);
// UNICODE Part
//////////////////////
#ifdef UNICODE
#define Dz1Console_tprintf			Dz1ConsoleW_tprintf
#define Dz1Console_printf			Dz1ConsoleW_printf
#define Dz1Console_tprintb			Dz1ConsoleW_tprintb
#define Dz1Console_printb			Dz1ConsoleW_printb
#else // UNICODE
#define Dz1Console_tprintf			Dz1ConsoleA_tprintf
#define Dz1Console_printf			Dz1ConsoleA_printf
#define Dz1Console_tprintb			Dz1ConsoleA_tprintb
#define Dz1Console_printb			Dz1ConsoleA_printb
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Console_tprintf			Dz1ConsoleA_tprintf
#define Dz1Console_printf			Dz1ConsoleA_printf
#define Dz1Console_tprintb			Dz1ConsoleA_tprintb
#define Dz1Console_printb			Dz1ConsoleA_printb
#endif // UNIX_SYSTEM

static __inline__ void			 no_con_err_out(const char *func_name, const char *msg)
{
//	FILE *fp = fopen("temp.err.txt", "a+b");
//	if (fp != NULL)
//	{
//		fprintf(fp, "!!! %s() : %s\n", func_name, msg);
//		fclose(fp);
//	}
}
#endif
