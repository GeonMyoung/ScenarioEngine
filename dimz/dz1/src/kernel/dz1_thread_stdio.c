#include "dz1_malloc.h"
#include "dz1_thread.h"
#include "dz1_str.h"
#include "dz1_thread_stdio.h"

ssize_t Dz1Thread_eprintf(const char *fmt, ...)
{
	ssize_t ret = -1;
//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	va_list ap;
	va_start(ap, fmt);
//	ret = Dz1Console_etvprintf(e-> con, 0, fmt, ap);
	ret = Dz1Console_etvprintf(con, 0, fmt, ap);
	va_end(ap);

	return ret;
}

ssize_t Dz1Thread_etprintf(int tab, const char *fmt, ...)
{
	ssize_t ret = -1;

//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	va_list ap;
	va_start(ap, fmt);
//	ret = Dz1Console_etvprintf(e-> con, tab, fmt, ap);
	ret = Dz1Console_etvprintf(con, tab, fmt, ap);
	va_end(ap);

	return ret;
}

ssize_t Dz1Thread_etprintb(int tab, void *data, size_t size, size_t align, bool_t printLetter)
{
//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	return Dz1Console_etprintb(con, tab, data, size, align, printLetter);
}

ssize_t Dz1Thread_eprintb(void *data, size_t size, size_t align, bool_t printLetter)
{
	return Dz1Thread_etprintb(0, data, size, align, printLetter);
}

///////////////////////////////////////////////////////////////////////////////
// Thread STDIO
///////////////////////////////////////////////////////////////////////////////
// Print Letter
bool_t Dz1ThreadA_putc(char c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t sz = 0;
	Dz1Console *con = Dz1Thread_getOwnConsole();
	if ((sz = Dz1ConsoleA_writeText(con, &c, 1, 0)) < 0) Dz1Error_set(errp, EFAULT);
	else if (sz != 1) Dz1Error_set(errp, EPIPE);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1ThreadA_fputc(FILE *fp, char c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int code = -1, c32 = (int)c & 0xFF;
	if (fp == NULL) Dz1Error_set(errp, EINVAL);
	else if ((code = fputc(c32, fp)) != c32) Dz1Error_set(errp, EPIPE);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
#ifndef UNIX_SYSTEM
bool_t Dz1ThreadW_putc(wchar_t c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t sz = 0;
	Dz1Console *con = Dz1Thread_getOwnConsole();
	if ((sz = Dz1ConsoleW_writeText(con, (wchar_t *)&c, 1, 0)) < 0) Dz1Error_set(errp, EFAULT);
	else if (sz != 1) Dz1Error_set(errp, EPIPE);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1ThreadW_fputc(FILE *fp, wchar_t c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wint_t code = -1;
	if (fp == NULL) Dz1Error_set(errp, EINVAL);
	else if ((code = fputwc(c, fp)) != c) Dz1Error_set(errp, EPIPE);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
#endif
// Print Letter
///////////////////////////////////////////////////////////////////////////////

void Dz1ThreadA_tabprint(int tab)
{
	while(tab--) Dz1ThreadA_printf(DZ1_TAB_STR_A);
}

#ifndef UNIX_SYSTEM
void Dz1ThreadW_tabprint(int tab)
{
	while(tab--) Dz1ThreadW_printf(DZ1_TAB_STR_W);
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Basic Print
ssize_t Dz1ThreadA_tvprintf(int tab, const char *fmt, va_list ap)
{
	ssize_t ret = -1;

//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	ret = Dz1ConsoleA_tvprintf(con, tab, fmt, ap);

	return ret;
}

#ifndef UNIX_SYSTEM
ssize_t Dz1ThreadW_tvprintf(int tab, const wchar_t *fmt, va_list ap)
{
	ssize_t ret = -1;

//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	ret = Dz1ConsoleW_tvprintf(con, tab, fmt, ap);

	return ret;
}
#endif

ssize_t Dz1ThreadA_tprintf(int tab, const char *fmt, ...)
{
	ssize_t ret = -1;

//	Dz1ThreadEntry *e = _Dz1Thread_self();
	va_list ap;
	va_start(ap, fmt);
	ret = Dz1ThreadA_tvprintf(tab, fmt, ap);
	va_end(ap);

	return ret;
}
#ifndef UNIX_SYSTEM
ssize_t Dz1ThreadW_tprintf(int tab, const wchar_t *fmt, ...)
{
	ssize_t ret = -1;

//	Dz1ThreadEntry *e = _Dz1Thread_self();
	va_list ap;
	va_start(ap, fmt);
	ret = Dz1ThreadW_tvprintf(tab, fmt, ap);
	va_end(ap);

	return ret;
}
#endif

ssize_t Dz1ThreadA_printf(const char *fmt, ...)
{
	ssize_t ret = -1;

//	Dz1ThreadEntry *e = _Dz1Thread_self();
	va_list ap;
	va_start(ap, fmt);
	ret = Dz1ThreadA_tvprintf(0, fmt, ap);
	va_end(ap);

	return ret;
}

#ifndef UNIX_SYSTEM
ssize_t Dz1ThreadW_printf(const wchar_t *fmt, ...)
{
	ssize_t ret = -1;

//	Dz1ThreadEntry *e = _Dz1Thread_self();
	va_list ap;
	va_start(ap, fmt);
	ret = Dz1ThreadW_tvprintf(0, fmt, ap);
	va_end(ap);

	return ret;
}

static wstr_t _prepare_wide_str(const char *fmt, va_list mbcs_ap, size_t *ret_sz)
{
	wstr_t ret = NULL;
	char *temp = NULL;
	if ((temp = (char *)Dz1Malloc(4096, NULL)) == NULL) no_con_err_out("_prepare_wide_str", "malloc fail");	// 4KB sprintf buffer
	else
	{
		int temp_len = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);

		if ((temp_len = vsnprintf(temp, 4095, fmt, mbcs_ap)) < 0) no_con_err_out("_prepare_wide_str", "formatting fail");
		else if (temp_len == 0) { }
		else if ((ret = (wchar_t *)Dz1String_conv(temp, temp_len, DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_WIDE_CHARSET, ret_sz)) == NULL) no_con_err_out("_prepare_wide_str", "convert fail");

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
	return ret;
}

ssize_t Dz1Thread_tvprintfA(int tab, const char *fmt, va_list mbcs_ap)
{	// mbcs arguments to any char type output
	ssize_t ret = 0;
	Dz1Console *con = Dz1Thread_getOwnConsole();
	Dz1ConsoleMode mode = dz1DefCon_getMode();
	if (mode == Dz1ConsoleMode_mbcs)
	{
		ret = Dz1ConsoleA_tvprintf(con, tab, fmt, mbcs_ap);
	}
	else if (mode == Dz1ConsoleMode_wide)
	{
		size_t str_sz = 0;
		wstr_t str = _prepare_wide_str(fmt, mbcs_ap, &str_sz);
		if (str == NULL) { }
		else
		{
			pthread_cleanup_push(Dz1Memory_cancel, (void *)str);

			if (con != NULL) // Dz1Console_write(con, (u8_t *)str, str_sz, -1, NULL);
				Dz1ConsoleW_writeText(con, str, str_sz >> 1, tab);
			ret = (ssize_t)(str_sz / sizeof(wchar_t));

			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)str);
		}
	}
	return ret;
}

ssize_t Dz1Thread_tprintfA(int tab, const char *fmt, ...)
{
	ssize_t ret = -1;
	va_list mbcs_ap;
	va_start(mbcs_ap, fmt);
	ret = Dz1Thread_tvprintfA(tab, fmt, mbcs_ap);
	va_end(mbcs_ap);

	return ret;
}

ssize_t Dz1Thread_printfA(const char *fmt, ...)
{
	ssize_t ret = -1;
	va_list mbcs_ap;
	va_start(mbcs_ap, fmt);
	ret = Dz1Thread_tvprintfA(0, fmt, mbcs_ap);
	va_end(mbcs_ap);

	return ret;
}

ssize_t Dz1Thread_ftvprintfA(FILE *fp, int tab, const char *fmt, va_list mbcs_ap)
{	// mbcs arguments to any char type output
	ssize_t ret = 0;
	Dz1ConsoleMode mode = dz1DefCon_getMode();
	if (mode == Dz1ConsoleMode_mbcs)
	{
		ret = Dz1ThreadA_ftvprintf(fp, tab, fmt, mbcs_ap);
	}
	else if (mode == Dz1ConsoleMode_wide)
	{
		size_t str_sz = 0;
		wstr_t str = _prepare_wide_str(fmt, mbcs_ap, &str_sz);
		if (str == NULL) { }
		else
		{
			pthread_cleanup_push(Dz1Memory_cancel, (void *)str);

			fwrite((u8_t *)str, sizeof(u8_t), str_sz, fp);
			ret = (ssize_t)(str_sz / sizeof(wchar_t));

			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)str);
		}
	}
	return ret;
}

ssize_t Dz1Thread_ftprintfA(FILE *fp, int tab, const char *fmt, ...)
{
	ssize_t ret = -1;
	va_list mbcs_ap;
	va_start(mbcs_ap, fmt);
	ret = Dz1Thread_ftvprintfA(fp, tab, fmt, mbcs_ap);
	va_end(mbcs_ap);

	return ret;
}

ssize_t Dz1Thread_fprintfA(FILE *fp, const char *fmt, ...)
{
	ssize_t ret = -1;
	va_list mbcs_ap;
	va_start(mbcs_ap, fmt);
	ret = Dz1Thread_ftvprintfA(fp, 0, fmt, mbcs_ap);
	va_end(mbcs_ap);

	return ret;
}
#endif
// Basic Print
///////////////////////////////////////

///////////////////////////////////////
// FILE Print
static char _ftprintA_tab[16] = "    ";
bool_t Dz1ThreadA_setFpTab(char *str)
{
	bool_t ret = FALSE;
	if (strlen(str) + 1 < sizeof(_ftprintA_tab))
	{
		strcpy(_ftprintA_tab, str);
		ret = TRUE;
	}
	return ret;
}

void Dz1ThreadA_ftabprint(FILE *fp, int tab)
{
	while(tab--) Dz1ThreadA_fprintf(fp, _ftprintA_tab);
}

ssize_t Dz1ThreadA_ftvprintf(FILE *fp, int tab, const char *fmt, va_list ap)
{
	ssize_t ret = 0;
	while(tab--) ret += fprintf(fp, _ftprintA_tab);
	ret += vfprintf(fp, fmt, ap);
	return ret;
}

ssize_t Dz1ThreadA_ftprintf(FILE *fp, int tab, const char *fmt, ...)
{
	ssize_t ret = -1;

	va_list ap;
	va_start(ap, fmt);
	ret = Dz1ThreadA_ftvprintf(fp, tab, fmt, ap);
	va_end(ap);

	return ret;
}
ssize_t Dz1ThreadA_fprintf(FILE *fp, const char *fmt, ...)
{
	ssize_t ret = -1;

	va_list ap;
	va_start(ap, fmt);
	Dz1ThreadA_ftvprintf(fp, 0, fmt, ap);
	va_end(ap);

	return ret;
}

#ifndef UNIX_SYSTEM
static wchar_t _ftprintW_tab[16] = L"    ";
bool_t Dz1ThreadW_setFpTab(wchar_t *str)
{
	bool_t ret = FALSE;
	if (wcslen(str) + 1 < sizeof(_ftprintW_tab))
	{
		wcscpy(_ftprintW_tab, str);
		ret = TRUE;
	}
	return ret;
}

void Dz1ThreadW_ftabprint(FILE *fp, int tab)
{
	while(tab) Dz1ThreadW_fprintf(fp, _ftprintW_tab);
}

ssize_t Dz1ThreadW_ftvprintf(FILE *fp, int tab, const wchar_t *fmt, va_list ap)
{
	ssize_t ret = 0;
	while(tab--) ret += fwprintf(fp, _ftprintW_tab);
	ret += vfwprintf(fp, fmt, ap);
	return ret;
}

ssize_t Dz1ThreadW_ftprintf(FILE *fp, int tab, const wchar_t *fmt, ...)
{
	ssize_t ret = -1;

	va_list ap;
	va_start(ap, fmt);
	Dz1ThreadW_ftvprintf(fp, tab, fmt, ap);
	va_end(ap);

	return ret;
}

ssize_t Dz1ThreadW_fprintf(FILE *fp, const wchar_t *fmt, ...)
{
	ssize_t ret = -1;

	va_list ap;
	va_start(ap, fmt);
	Dz1ThreadW_ftvprintf(fp, 0, fmt, ap);
	va_end(ap);

	return ret;
}
#endif
// FILE Print
///////////////////////////////////////

#ifndef UNIX_SYSTEM
static ssize_t __Dz1ThreadX_ftvprintf(FILE *fp, str_t mbcs, size_t sz)
{
	ssize_t ret = -1;
	wstr_t temp = NULL;
	if ((temp = (wchar_t *)Dz1Calloc(sizeof(wchar_t), sz + 1, NULL)) == NULL) no_con_err_out("Dz1ConsoleW_etvprintf", "malloc fail");	// 8KB uni-code buffer
	else
	{
		ssize_t byte_sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);

		if ((byte_sz = _dz1_core_codeconv((u8_t *)temp, sizeof(wchar_t) * (sz + 1), DZ1_SYSTEM_WIDE_CHARSET, (u8_t *)mbcs, sz, DZ1_SYSTEM_MBCS_CHARSET)) < 0) no_con_err_out("Dz1ConsoleW_etvprintf", "convert fail");
		else if (byte_sz == 0) ret = 0;
		else
		{
			ret = (ssize_t)fwrite(temp, sizeof(wchar_t), byte_sz >> 1, fp);
			fflush(fp);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
	return ret;
}

static ssize_t _Dz1ThreadX_ftvprintf(FILE *fp, int tab, char *fmt, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ssize_t ret = -1;
	char *buf = (char *)Dz1Malloc(4096, errp);	// 4K byte output buffer
	if (buf == NULL) ERR_OUT(errp);
	else
	{
		int buf_len = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);

		if ((buf_len = vsnprintf(buf, 4095, fmt, ap)) < 0) no_con_err_out("Dz1ConsoleW_etvprintf", "formatting fail");	// put all string to buffer
		else if (buf_len == 0) ret = 0;																					// nothing to print
		else if (buf_len > 0) ret = __Dz1ThreadX_ftvprintf(fp, buf, (size_t)buf_len);								// convert & emit

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
	}
	return ret;
}
#endif

ssize_t Dz1ThreadX_ftvprintf(FILE *fp, int tab, char *fmt, va_list ap)
{
	ssize_t ret = -1;
	switch(dz1DefCon_getMode())
	{
	default:
	case Dz1ConsoleMode_mbcs: ret = Dz1ThreadA_ftvprintf(fp, tab, fmt, ap); break;
#ifndef UNIX_SYSTEM
	case Dz1ConsoleMode_wide: ret = _Dz1ThreadX_ftvprintf(fp, tab, fmt, ap); break;
#endif
	}
	return ret;
}

ssize_t Dz1ThreadX_ftprintf(FILE *fp, int tab, char *fmt, ...)
{
	ssize_t ret = -1;

	va_list ap;
	va_start(ap, fmt);
	Dz1ThreadX_ftvprintf(fp, tab, fmt, ap);
	va_end(ap);

	return ret;
}

ssize_t Dz1ThreadX_fprintf(FILE *fp, char *fmt, ...)
{
	ssize_t ret = -1;

	va_list ap;
	va_start(ap, fmt);
	Dz1ThreadX_ftvprintf(fp, 0, fmt, ap);
	va_end(ap);

	return ret;
}

///////////////////////////////////////
// Binary Print
ssize_t Dz1ThreadA_tprintb(int tab, void *ptr, size_t size, size_t align, bool_t print_letter)
{
//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	return Dz1ConsoleA_tprintb(con, tab, ptr, size, align, print_letter);
}
#ifndef UNIX_SYSTEM
ssize_t Dz1ThreadW_tprintb(int tab, void *ptr, size_t size, size_t align, bool_t print_letter)
{
//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	return Dz1ConsoleW_tprintb(con, tab, ptr, size, align, print_letter);
}
#endif

ssize_t Dz1ThreadA_printb(void *ptr, size_t size, size_t align, bool_t print_letter)
{
//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	return Dz1ConsoleA_printb(con, ptr, size, align, print_letter);
}
#ifndef UNIX_SYSTEM
ssize_t Dz1ThreadW_printb(void *ptr, size_t size, size_t align, bool_t print_letter)
{
//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	return Dz1ConsoleW_printb(con, ptr, size, align, print_letter);
}
#endif

static ssize_t _A_ftprintb(FILE *fp, int tab, u32_t offset, char *data, size_t size, size_t align)
{
	ssize_t ret = Dz1ThreadA_ftprintf(fp, tab, "%08X : ", offset);
	size_t temp;
	char *lp = data;
	u8_t *cp = (u8_t *)data;

	temp = size; while(temp--) { ret += Dz1ThreadA_ftprintf(fp, 0, "%02X ", *cp++); align--; }

	if (align) while(align--) { ret += Dz1ThreadA_fprintf(fp, "   "); }

	ret += Dz1ThreadA_fprintf(fp, ": ");

	temp = size; while(temp--) { ret += Dz1ThreadA_fprintf(fp, "%c", (*lp > 0x20 ? *lp : '.')); lp++; }

	ret += Dz1ThreadA_fprintf(fp, "\n");

	return ret;
}

ssize_t Dz1ThreadA_ftprintb(FILE *fp, int tab, void *data, size_t size, size_t align)
{
	ssize_t ret = -1;

	if (fp && data && size)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		align = align ? align : 16;

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _A_ftprintb(fp, tab, (u32_t)(cp - base), (char *)cp, jobSize, align);
			cp += jobSize; size -= jobSize;
		}
	}
	return ret;
}
#ifndef UNIX_SYSTEM
static ssize_t _W_ftprintb(FILE *fp, int tab, u32_t offset, char *data, size_t size, size_t align)
{
	ssize_t ret = Dz1ThreadW_ftprintf(fp, tab, L"%08X : ", offset);
	size_t temp;
	char *lp = data;
	u8_t *cp = (u8_t *)data;

	temp = size; while(temp--) { ret += Dz1ThreadW_ftprintf(fp, 0, L"%02X ", *cp++); align--; }

	if (align) while(align--) { ret += Dz1ThreadW_fprintf(fp, L"   "); }

	ret += Dz1ThreadW_fprintf(fp, L": ");

	temp = size; while(temp--) { ret += Dz1ThreadW_fprintf(fp, L"%c", (*lp > 0x20 && *lp <= 0x7F ? *lp : '.')); lp++; }

	ret += Dz1ThreadW_fprintf(fp, L"\n");

	return ret;
}

ssize_t Dz1ThreadW_ftprintb(FILE *fp, int tab, void *data, size_t size, size_t align)
{
	ssize_t ret = -1;

	if (fp && data && size)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		align = align ? align : 16;

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _W_ftprintb(fp, tab, (u32_t)(cp - base), (char *)cp, jobSize, align);
			cp += jobSize; size -= jobSize;
		}
	}
	return ret;
}
#endif

ssize_t Dz1ThreadA_fprintb(FILE *fp, void *data, size_t size, size_t align)
{
	return Dz1ThreadA_ftprintb(fp, 0, data, size, align);
}
#ifndef UNIX_SYSTEM
ssize_t Dz1ThreadW_fprintb(FILE *fp, void *data, size_t size, size_t align)
{
	return Dz1ThreadW_ftprintb(fp, 0, data, size, align);
}
#endif
// Binary Print
///////////////////////////////////////

///////////////////////////////////////
// Chunk Operation
ssize_t Dz1ThreadA_writeText(char *buf, size_t size, int tab)
{
//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	return Dz1ConsoleA_writeText(con, buf, size, tab);
}
#ifndef UNIX_SYSTEM
ssize_t Dz1ThreadW_writeText(wchar_t *buf, size_t size, int tab)
{
//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	return Dz1ConsoleW_writeText(con, buf, size, tab);
}
#endif
// Chunk Operation
///////////////////////////////////////

///////////////////////////////////////
// Input
// ssize_t Dz1Thread_read(u8_t *buf, size_t size, s32_t wait_us, Dz1Error *err)
// {
// 	Dz1ThreadEntry *e = _Dz1Thread_self();
//	Dz1Console *con = Dz1Thread_getOwnConsole();
// 	return Dz1Console_read(con, buf, size, wait_us, err);
// }

int Dz1Thread_getch(s32_t wait_us, Dz1Error *err)
{
//	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	return Dz1Console_getch(con, wait_us, err);
}

void Dz1Thread_getSize(u32_t *width, u32_t *height)
{
//	Dz1ThreadEntry *e = _Dz1Thread_self();
// 	if (e && e-> con)
// 	{
// 		Dz1Console *con = e-> con;
// 		if (width) *width = con->width;
// 		if (height) *height = con->height;
// 	}
	Dz1Console *con = Dz1Thread_getOwnConsole();
	if (con)
	{
		if (width) *width = con->width;
		if (height) *height = con->height;
	}
}
// Input
///////////////////////////////////////

void Dz1ThreadX_dump(void *p, int tab, Dz1DumpFunc dumpA, Dz1DumpFunc dumpW)
{
	switch(dz1DefCon_getMode())
	{
	case Dz1ConsoleMode_mbcs: dumpA(p, tab); break;
	case Dz1ConsoleMode_wide: if (dumpW != NULL) dumpW(p, tab); break;
	}
}

void Dz1ThreadX_fdump(FILE *fp, void *p, int tab, Dz1FDumpFunc dumpA, Dz1FDumpFunc dumpW)
{
	switch(dz1DefCon_getMode())
	{
	case Dz1ConsoleMode_mbcs: dumpA(fp, p, tab); break;
	case Dz1ConsoleMode_wide: if (dumpW != NULL) dumpW(fp, p, tab); break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// FILE stream Console
typedef struct FileConsole
{
	FILE				*fp;		// is ref
	Dz1Mutex			*lock;		// is ref
} FileConsole;

static FileConsole *FileConsole_new(FILE *fp, Dz1Mutex *lock, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FileConsole *ret = NULL;
	if (fp == NULL || lock == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (FileConsole *)Dz1Calloc(sizeof(FileConsole), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ret->fp = fp;
		ret->lock = lock;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void FileConsole_del(void *ptr)
{
	FileConsole *p = (FileConsole *)ptr;
	if (p != NULL) Dz1Free(p);
}

static void FileConsole_delAndSetNull(void *pptr)
{
	FileConsole **p = (FileConsole **)pptr;
	FileConsole_del(*p);
	*p = NULL;
}

static Dz1Error FileConsole_wait(void *ptr, Dz1ThreadIODir flag, s32_t wait_us)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Error_set(errp, 0);
	return err;
}

static int FileConsole_getch(void *ptr, s32_t wait_us, Dz1Error *errp)
{
	Dz1Error_set(errp, ENOSYS);
	return -1;
}

static ssize_t FileConsole_write(void *ptr, u8_t *buf, size_t size, s32_t wait_us, Dz1Error *errp)
{
	ssize_t ret = 0;
	FileConsole *p = (FileConsole *)ptr;
	if (p != NULL && p->fp != NULL && p->lock != NULL)
	{
		size_t sz = 0;
		Dz1Mutex_lock(p->lock);
		pthread_cleanup_push(Dz1Mutex_lockCancel, (void *)p->lock);
		if ((sz = fwrite(buf, sizeof(u8_t), size, p->fp)) != size) Dz1Error_set(errp, EPIPE);
		else 
		{
			fflush(p->fp);
			ret = (ssize_t)sz;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Mutex_lockCancel, (void *)p->lock);
	}
	return ret;
}

bool_t Dz1Thread_setConsoleFILE(Dz1ThreadConsolPrompt prompt, FILE *fp, Dz1Mutex *lock, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FileConsole *file_con = FileConsole_new(fp, lock, errp);
	if (file_con == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(FileConsole_delAndSetNull, (void *)&file_con);
		if (Dz1Thread_setConsole(prompt, (void *)file_con,
								 FileConsole_del,
								 FileConsole_wait,
								 FileConsole_getch,
								 FileConsole_write, err) == FALSE) ERR_OUT(errp);
		else
		{
			file_con = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (FileConsole_delAndSetNull, (void *)&con);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// FILE stream Console
///////////////////////////////////////////////////////////////////////////////

