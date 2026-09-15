#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>

#include "dz1_termio.h"
#include "dz1_termio_xterm.h"
#include "dz1_termio_ansi.h"
#ifndef UNIX_SYSTEM
#include "dz1_termio_win32crt.h"
#endif

///////////////////////////////////////////////////////////////////////////////
// Dz1TermKeyStr
static struct Dz1TermKeyMapA
{
	Dz1TermKey	 key;
	str_t		 name;
} Dz1TermKeyMapA[] =
{
	{ Dz1TermKey_esc,		(str_t)"ESC" },
	{ Dz1TermKey_up,		(str_t)"UP" },
	{ Dz1TermKey_down,		(str_t)"DOWN" },
	{ Dz1TermKey_right,		(str_t)"RIGHT" },
	{ Dz1TermKey_left,		(str_t)"LEFT" },
	{ Dz1TermKey_end,		(str_t)"END" },
	{ Dz1TermKey_home,		(str_t)"HOME" },
	{ Dz1TermKey_insert,	(str_t)"INSERT" },
	{ Dz1TermKey_delete,	(str_t)"DELETE" },
	{ Dz1TermKey_pageUp,	(str_t)"PgUP" },
	{ Dz1TermKey_pageDown,	(str_t)"PgDN" },
	{ Dz1TermKey_f1,		(str_t)"F1" },
	{ Dz1TermKey_f2,		(str_t)"F2" },
	{ Dz1TermKey_f3,		(str_t)"F3" },
	{ Dz1TermKey_f4,		(str_t)"F4" },
	{ Dz1TermKey_f5,		(str_t)"F5" },
	{ Dz1TermKey_f6,		(str_t)"F6" },
	{ Dz1TermKey_f7,		(str_t)"F7" },
	{ Dz1TermKey_f8,		(str_t)"F8" },
	{ Dz1TermKey_f9,		(str_t)"F9" },
	{ Dz1TermKey_f10,		(str_t)"F10" },
	{ Dz1TermKey_f11,		(str_t)"F11" },
	{ Dz1TermKey_f12,		(str_t)"F12" },
	{ Dz1TermKey_max,		(str_t)"Unknown" }
};

str_t Dz1TermKeyStrA(Dz1TermKey key)
{
	struct Dz1TermKeyMapA *i;
	for (i = Dz1TermKeyMapA; i->key != Dz1TermKey_max; i++)
		if (i->key == key) break;
	return i->name;
}
#ifndef UNIX_SYSTEM
static struct Dz1TermKeyMapW
{
	Dz1TermKey	 key;
	wstr_t		 name;
} Dz1TermKeyMapW[] =
{
	{ Dz1TermKey_esc,		(wstr_t)L"ESC" },
	{ Dz1TermKey_up,		(wstr_t)L"UP" },
	{ Dz1TermKey_down,		(wstr_t)L"DOWN" },
	{ Dz1TermKey_right,		(wstr_t)L"RIGHT" },
	{ Dz1TermKey_left,		(wstr_t)L"LEFT" },
	{ Dz1TermKey_end,		(wstr_t)L"END" },
	{ Dz1TermKey_home,		(wstr_t)L"HOME" },
	{ Dz1TermKey_insert,	(wstr_t)L"INSERT" },
	{ Dz1TermKey_delete,	(wstr_t)L"DELETE" },
	{ Dz1TermKey_pageUp,	(wstr_t)L"PgUP" },
	{ Dz1TermKey_pageDown,	(wstr_t)L"PgDN" },
	{ Dz1TermKey_f1,		(wstr_t)L"F1" },
	{ Dz1TermKey_f2,		(wstr_t)L"F2" },
	{ Dz1TermKey_f3,		(wstr_t)L"F3" },
	{ Dz1TermKey_f4,		(wstr_t)L"F4" },
	{ Dz1TermKey_f5,		(wstr_t)L"F5" },
	{ Dz1TermKey_f6,		(wstr_t)L"F6" },
	{ Dz1TermKey_f7,		(wstr_t)L"F7" },
	{ Dz1TermKey_f8,		(wstr_t)L"F8" },
	{ Dz1TermKey_f9,		(wstr_t)L"F9" },
	{ Dz1TermKey_f10,		(wstr_t)L"F10" },
	{ Dz1TermKey_f11,		(wstr_t)L"F11" },
	{ Dz1TermKey_f12,		(wstr_t)L"F12" },
	{ Dz1TermKey_max,		(wstr_t)L"Unknown" }
};

wstr_t Dz1TermKeyStrW(Dz1TermKey key)
{
	struct Dz1TermKeyMapW *i;
	for (i = Dz1TermKeyMapW; i->key != Dz1TermKey_max; i++)
		if (i->key == key) break;
	return i->name;
}
#endif
// Dz1TermKeyStr
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TermMetaKeyStr
static struct Dz1TermMetaKeyMapA
{
	Dz1TermMetaKey	 key;
	str_t			 name;
} Dz1TermMetaKeyMapA[] =
{
	{ Dz1TermMetaKey_none,				(str_t)"None" },
	{ Dz1TermMetaKey_shift,				(str_t)"Shift" },
	{ Dz1TermMetaKey_alt,				(str_t)"Alt" },
	{ Dz1TermMetaKey_control,			(str_t)"Ctrl" },
	{ Dz1TermMetaKey_shiftAlt,			(str_t)"Shift|Alt" },
	{ Dz1TermMetaKey_shiftControl,		(str_t)"Shift|Ctrl" },
	{ Dz1TermMetaKey_controlAlt,		(str_t)"Ctrl|Alt" },
	{ Dz1TermMetaKey_shiftControlAlt,	(str_t)"Shift|Alt|Ctrl" },
	{ Dz1TermMetaKey_max,				(str_t)"Unknown" }
};

str_t Dz1TermMetaKeyStrA(Dz1TermMetaKey key)
{
	struct Dz1TermMetaKeyMapA *i;
	for (i = Dz1TermMetaKeyMapA; i->key != Dz1TermMetaKey_max; i++)
		if (i->key == key) break;
	return i->name;
}
#ifndef UNIX_SYSTEM
static struct Dz1TermMetaKeyMapW
{
	Dz1TermMetaKey	 key;
	wstr_t			 name;
} Dz1TermMetaKeyMapW[] =
{
	{ Dz1TermMetaKey_none,				(wstr_t)L"None" },
	{ Dz1TermMetaKey_shift,				(wstr_t)L"Shift" },
	{ Dz1TermMetaKey_alt,				(wstr_t)L"Alt" },
	{ Dz1TermMetaKey_control,			(wstr_t)L"Ctrl" },
	{ Dz1TermMetaKey_shiftAlt,			(wstr_t)L"Shift|Alt" },
	{ Dz1TermMetaKey_shiftControl,		(wstr_t)L"Shift|Ctrl" },
	{ Dz1TermMetaKey_controlAlt,		(wstr_t)L"Ctrl|Alt" },
	{ Dz1TermMetaKey_shiftControlAlt,	(wstr_t)L"Shift|Alt|Ctrl" },
	{ Dz1TermMetaKey_max,				(wstr_t)L"Unknown" }
};

wstr_t Dz1TermMetaKeyStrW(Dz1TermMetaKey key)
{
	struct Dz1TermMetaKeyMapW *i;
	for (i = Dz1TermMetaKeyMapW; i->key != Dz1TermMetaKey_max; i++)
		if (i->key == key) break;
	return i->name;
}
#endif
// Dz1TermMetaKeyStr
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TermIo Find
struct Dz1TermcapA
{
	str_t				 name;
	Dz1ConsoleTermSpecA	*spec;
} Dz1TermcapA[] =
{
	{ (str_t)"ansi",		&ansiSpecA },
	{ (str_t)"vt100",		&xtermSpecA },
	{ (str_t)"xterm",		&xtermSpecA },
#ifndef UNIX_SYSTEM
	{ (str_t)"win32crt",	&win32CrtSpecA },
#endif
	{ NULL, NULL }
};

static Dz1ConsoleTermSpecA *Dz1TermIoA_find(str_t name)
{
	struct Dz1TermcapA *i;
	for (i = Dz1TermcapA; i->name; i++)
		if (strcmp(name, i->name) == 0) return i->spec;
	return NULL;
}
#ifndef UNIX_SYSTEM
struct Dz1TermcapW
{
	wstr_t				 name;
	Dz1ConsoleTermSpecW	*spec;
} Dz1TermcapW[] =
{
	{ (wstr_t)L"ansi",		&ansiSpecW },
	{ (wstr_t)L"vt100",		&xtermSpecW },
	{ (wstr_t)L"xterm",		&xtermSpecW },
	{ (wstr_t)L"win32crt",	&win32CrtSpecW },
	{ NULL, NULL }
};

static Dz1ConsoleTermSpecW *Dz1TermIoW_find(wstr_t name)
{
	struct Dz1TermcapW *i;
	for (i = Dz1TermcapW; i->name; i++)
		if (wcscmp(name, i->name) == 0) return i->spec;
	return NULL;
}
#endif
// Dz1TermIo Find
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TermIoFifo
typedef struct Dz1TermIoFifoA
{
	size_t head;
	size_t tail;
	size_t size;
	char *buf;

	void	 (*reset)(struct Dz1TermIoFifoA *p);
	bool_t	 (*isEmpty)(struct Dz1TermIoFifoA *p);
	char	 (*pop)(struct Dz1TermIoFifoA *p, Dz1Error *errp);
	Dz1Error (*push)(struct Dz1TermIoFifoA *p, char c);
} Dz1TermIoFifoA;

static void Dz1TermIoFifoA_reset(Dz1TermIoFifoA *p) { p->head = p->tail = 0; }
static bool_t Dz1TermIoFifoA_isEmpty(Dz1TermIoFifoA *p) { return p->head == p->tail ? TRUE : FALSE; }
static char Dz1TermIoFifoA_pop(Dz1TermIoFifoA *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	char ret = '\0';
	if (p->head == p->tail) { ERR_SET_OUT(errp, ESRCH); }
	else
	{
		ret = p->buf[p->tail++];
		p->tail %= p->size;
	}
	return ret;
}

static Dz1Error Dz1TermIoFifoA_push(Dz1TermIoFifoA *p, char c)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	p->buf[p->head++] = c;
	return err;
}

static char Dz1TermIoFifoA_head(Dz1TermIoFifoA *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	char ret = '\0';
	if (p->head == p->tail) { ERR_SET_OUT(errp, ESRCH); }
	else ret = p->buf[p->tail];
	return ret;
}

static void Dz1TermIoFifoA_del(Dz1TermIoFifoA *p)
{
	if (!p) return;
	if (p->buf) Dz1Free(p->buf);
	Dz1Free(p);
}

static void Dz1TermIoFifoA_delAndSetNull(void *ptr)
{
	Dz1TermIoFifoA **p = (Dz1TermIoFifoA **)ptr;
	Dz1TermIoFifoA_del(*p); *p = NULL;
}

static Dz1TermIoFifoA *Dz1TermIoFifoA_new(size_t size, Dz1Error *errp)
{
	Dz1TermIoFifoA *ret = (Dz1TermIoFifoA *)Dz1Calloc(sizeof(Dz1TermIoFifoA), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TermIoFifoA_delAndSetNull, (void *)&ret);
		if ((ret->buf = (char *)Dz1Malloc(size, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->size = size;
			ret->reset = Dz1TermIoFifoA_reset;
			ret->isEmpty = Dz1TermIoFifoA_isEmpty;
			ret->pop = Dz1TermIoFifoA_pop;
			ret->push = Dz1TermIoFifoA_push;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TermIoFifoA_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
typedef struct Dz1TermIoFifoW
{
	size_t head;
	size_t tail;
	size_t size;
	wchar_t *buf;

	void	 (*reset)(struct Dz1TermIoFifoW *p);
	bool_t	 (*isEmpty)(struct Dz1TermIoFifoW *p);
	wchar_t	 (*pop)(struct Dz1TermIoFifoW *p, Dz1Error *errp);
	Dz1Error (*push)(struct Dz1TermIoFifoW *p, wchar_t c);
} Dz1TermIoFifoW;

static void Dz1TermIoFifoW_reset(Dz1TermIoFifoW *p) { p->head = p->tail = 0; }
static bool_t Dz1TermIoFifoW_isEmpty(Dz1TermIoFifoW *p) { return p->head == p->tail ? TRUE : FALSE; }
static wchar_t Dz1TermIoFifoW_pop(Dz1TermIoFifoW *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	wchar_t ret = L'\0';
	if (p->head == p->tail) { ERR_SET_OUT(errp, ESRCH); }
	else
	{
		ret = p->buf[p->tail++];
		p->tail %= p->size;
	}
	return ret;
}

static Dz1Error Dz1TermIoFifoW_push(Dz1TermIoFifoW *p, wchar_t c)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	p->buf[p->head++] = c;
	return err;
}

static wchar_t Dz1TermIoFifoW_head(Dz1TermIoFifoW *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	wchar_t ret = L'\0';
	if (p->head == p->tail) { ERR_SET_OUT(errp, ESRCH); }
	else ret = p->buf[p->tail];
	return ret;
}

static void Dz1TermIoFifoW_del(Dz1TermIoFifoW *p)
{
	if (!p) return;
	if (p->buf) Dz1Free(p->buf);
	Dz1Free(p);
}

static void Dz1TermIoFifoW_delAndSetNull(void *ptr)
{
	Dz1TermIoFifoW **p = (Dz1TermIoFifoW **)ptr;
	Dz1TermIoFifoW_del(*p); *p = NULL;
}

static Dz1TermIoFifoW *Dz1TermIoFifoW_new(size_t size, Dz1Error *errp)
{
	Dz1TermIoFifoW *ret = (Dz1TermIoFifoW *)Dz1Calloc(sizeof(Dz1TermIoFifoW), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TermIoFifoW_delAndSetNull, (void *)&ret);
		if ((ret->buf = (wchar_t *)Dz1Malloc(sizeof(wchar_t) * size, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->size = size;
			ret->reset = Dz1TermIoFifoW_reset;
			ret->isEmpty = Dz1TermIoFifoW_isEmpty;
			ret->pop = Dz1TermIoFifoW_pop;
			ret->push = Dz1TermIoFifoW_push;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TermIoFifoW_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif
// Dz1TermIoFifo
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TermIo
typedef struct Dz1TermIoA
{
	Dz1TermIoFifoA		*fifo;
	Dz1ConsoleTermSpecA	*spec;
} Dz1TermIoA;

void *Dz1TermIoA_new(str_t termName, size_t fifoSize, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TermIoA *ret = (Dz1TermIoA *)Dz1Calloc(sizeof(Dz1TermIoA), 1, errp);
	if (ret == NULL) { }
	else
	{
		pthread_cleanup_push(Dz1TermIoA_delAndSetNull, (void *)&ret);

		if ((ret->spec = Dz1TermIoA_find(termName)) == NULL) { ERR_SET_OUT(errp, ESRCH); }
		else if ((ret->fifo = Dz1TermIoFifoA_new(fifoSize, errp)) == NULL) { ERR_OUT(errp); }
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1TermIoA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TermIoA_del(void *ptr)
{
	Dz1TermIoA *p = (Dz1TermIoA *)ptr;
	if (!p) return;
	if (p->fifo) Dz1TermIoFifoA_del(p->fifo);
	Dz1Free(p);
}

void Dz1TermIoA_delAndSetNull(void *ptr)
{
	Dz1TermIoA **p = (Dz1TermIoA **)ptr;
	Dz1TermIoA_del(*p); *p = NULL;
}
#ifndef UNIX_SYSTEM
typedef struct Dz1TermIoW
{
	Dz1TermIoFifoW		*fifo;
	Dz1ConsoleTermSpecW	*spec;
} Dz1TermIoW;

void *Dz1TermIoW_new(wstr_t termName, size_t fifoSize, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TermIoW *ret = (Dz1TermIoW *)Dz1Calloc(sizeof(Dz1TermIoW), 1, errp);
	if (ret == NULL) { }
	else
	{
		pthread_cleanup_push(Dz1TermIoW_delAndSetNull, (void *)&ret);

		if ((ret->spec = Dz1TermIoW_find(termName)) == NULL) { ERR_SET_OUT(errp, ESRCH); }
		else if ((ret->fifo = Dz1TermIoFifoW_new(fifoSize, errp)) == NULL) { ERR_OUT(errp); }
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1TermIoW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TermIoW_del(void *ptr)
{
	Dz1TermIoW *p = (Dz1TermIoW *)ptr;
	if (!p) return;
	if (p->fifo) Dz1TermIoFifoW_del(p->fifo);
	Dz1Free(p);
}

void Dz1TermIoW_delAndSetNull(void *ptr)
{
	Dz1TermIoW **p = (Dz1TermIoW **)ptr;
	Dz1TermIoW_del(*p); *p = NULL;
}
#endif
// Dz1TermIo
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GETC
static bool_t isEscKeyA(int c, Dz1ConsoleTermSpecA *spec)
{
	int i;
	for (i = 0; i < spec->numOfEsc; i++)
		if (spec->esc[i] == c) return TRUE;
	return FALSE;
}

// -1 = error, 0 = Special Key, 0 < Char
int Dz1TermIoA_getc(void *ptr, Dz1TermMetaKey *meta, Dz1TermKey *key, Dz1Error *err)
{
	char c;
	int ret = -1, read_c;
	ssize_t readByte;
	Dz1TermIoA *p = (Dz1TermIoA *)ptr;

	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (!p->fifo->isEmpty(p->fifo))
	{	// not empty fifo -> read from fifo
		if ((ret = p->fifo->pop(p->fifo, errp)) == 0) { ret = -1; ERR_SET_OUT(errp, EFAULT); }
		else if (ret & 0x80)
		{
			int temp;
			if ((temp = Dz1TermIoFifoA_head(p->fifo, errp)) == 0) { ret = -1; ERR_SET_OUT(errp, EFAULT); }
			else if (temp & 0x80) ret = (ret << 8 | (temp & 0xFF)) & 0xFFFF;
		}
	}
	// read a byte from CONSOLE
// 	else if ((readByte = Dz1Thread_read((u8_t *)&c, 1, -1, errp)) < 0) { ERR_OUT(errp); }
// 	else if (readByte == 0) { ERR_SET_OUT(errp, EPIPE); }
	else if ((read_c = Dz1Thread_getch(-1, errp)) < 0) ERR_OUT(errp);
	else if ((c = (char)(read_c & 0xFF)) == 0) ERR_SET_OUT(errp, EPIPE);
	// check escape key
	else if (isEscKeyA(c, p->spec))
	{
		p->fifo->reset(p->fifo);
		if ((readByte = p->spec->getKey(c, meta, key, p->fifo->buf, p->fifo->size, errp)) < 0) { ERR_OUT(errp); }
		else
		{
			p->fifo->head = readByte;
			ret = 0;
		}
	}
	// check MBCS sequence
	else if (c & 0x80)
	{
		char temp = 0;
// 		if ((readByte = Dz1Thread_read((u8_t *)&temp, 1, -1, errp)) < 0) { ERR_OUT(errp); }
		if ((read_c = Dz1Thread_getch(-1, errp)) < 0) ERR_OUT(errp);
		else if ((temp = (char)(read_c & 0xFF)) == 0) ERR_SET_OUT(errp, EPIPE);
		else if (temp & 0x80) ret = ((c << 8) | (temp & 0xFF)) & 0xFFFF;
		else
		{
			p->fifo->push(p->fifo, temp);
			ret = c & 0xFF;
		}
	}
	else ret = c;

	return ret;
}
#ifndef UNIX_SYSTEM
static bool_t isEscKeyW(int c, Dz1ConsoleTermSpecW *spec)
{
	int i;
	for (i = 0; i < spec->numOfEsc; i++)
		if (spec->esc[i] == c) return TRUE;
	return FALSE;
}

// -1 = error, 0 = Special Key, 0 < Char
int Dz1TermIoW_getc(void *ptr, Dz1TermMetaKey *meta, Dz1TermKey *key, Dz1Error *err)
{
	wchar_t c;
	int ret = -1, read_c;
	ssize_t readByte;
	Dz1TermIoW *p = (Dz1TermIoW *)ptr;

	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (!p->fifo->isEmpty(p->fifo))
	{	// not empty fifo -> read from fifo
		if ((ret = p->fifo->pop(p->fifo, errp)) == 0) { ret = -1; ERR_SET_OUT(errp, EFAULT); }
		else Dz1Error_set(errp, 0);
	}
	// read a byte from CONSOLE
// 	else if ((readByte = Dz1Thread_read((u8_t *)&c, sizeof(wchar_t), -1, errp)) < 0) { ERR_OUT(errp); }
// 	else if (readByte == 0) { ERR_SET_OUT(errp, EPIPE); }
	else if ((read_c = Dz1Thread_getch(-1, errp)) < 0) ERR_OUT(errp);
	else if ((c = (wchar_t)(read_c & 0xFFFF)) == 0) ERR_SET_OUT(errp, EPIPE);
	// check escape key
	else if (isEscKeyW((int)c & 0xFFFF, p->spec))
	{
		p->fifo->reset(p->fifo);
		if ((readByte = p->spec->getKey(c, meta, key, p->fifo->buf, p->fifo->size, errp)) < 0) { ERR_OUT(errp); }
		else
		{
			p->fifo->head = readByte;
			ret = 0;
		}
	}
	else ret = c;

	return ret;
}
#endif
// GETC
///////////////////////////////////////////////////////////////////////////////
