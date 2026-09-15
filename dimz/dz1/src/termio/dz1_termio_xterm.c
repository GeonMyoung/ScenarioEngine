#include <dz1_thread_stdio.h>

#include "dz1_termio.h"
#include "dz1_termio_xterm.h"

///////////////////////////////////////////////////////////////////////////////
// XTERMKeys find
struct TermcapKeyMapA XTERMKeysA[] =
{
	{ (str_t)"[A", Dz1TermKey_up },
	{ (str_t)"[B", Dz1TermKey_down },
	{ (str_t)"[C", Dz1TermKey_right },
	{ (str_t)"[D", Dz1TermKey_left },
	{ (str_t)"[F", Dz1TermKey_end },
	{ (str_t)"[H", Dz1TermKey_home },
	{ (str_t)"[2~", Dz1TermKey_insert },
	{ (str_t)"[3~", Dz1TermKey_delete },
	{ (str_t)"[5~", Dz1TermKey_pageUp },
	{ (str_t)"[6~", Dz1TermKey_pageDown },
	{ (str_t)"OP", Dz1TermKey_f1 },
	{ (str_t)"OQ", Dz1TermKey_f2 },
	{ (str_t)"OR", Dz1TermKey_f3 },
	{ (str_t)"OS", Dz1TermKey_f4 },
	{ (str_t)"[15~", Dz1TermKey_f5 },
	{ (str_t)"[17~", Dz1TermKey_f6 },
	{ (str_t)"[18~", Dz1TermKey_f7 },
	{ (str_t)"[19~", Dz1TermKey_f8 },
	{ (str_t)"[20~", Dz1TermKey_f9 },
	{ (str_t)"[21~", Dz1TermKey_f10 },
	{ (str_t)"[23~", Dz1TermKey_f11 },
	{ (str_t)"[24~", Dz1TermKey_f12 },
	{ NULL }
};

static Dz1TermKey XTERMKeysA_find(str_t str)
{
	struct TermcapKeyMapA *i;
	for (i = XTERMKeysA; i->pattern; i++)
		if (strcmp(i->pattern, str) == 0) return i->key;
	return Dz1TermKey_max;
}
#ifndef UNIX_SYSTEM
struct TermcapKeyMapW XTERMKeysW[] =
{
	{ (wstr_t)L"[A", Dz1TermKey_up },
	{ (wstr_t)L"[B", Dz1TermKey_down },
	{ (wstr_t)L"[C", Dz1TermKey_right },
	{ (wstr_t)L"[D", Dz1TermKey_left },
	{ (wstr_t)L"[F", Dz1TermKey_end },
	{ (wstr_t)L"[H", Dz1TermKey_home },
	{ (wstr_t)L"[2~", Dz1TermKey_insert },
	{ (wstr_t)L"[3~", Dz1TermKey_delete },
	{ (wstr_t)L"[5~", Dz1TermKey_pageUp },
	{ (wstr_t)L"[6~", Dz1TermKey_pageDown },
	{ (wstr_t)L"OP", Dz1TermKey_f1 },
	{ (wstr_t)L"OQ", Dz1TermKey_f2 },
	{ (wstr_t)L"OR", Dz1TermKey_f3 },
	{ (wstr_t)L"OS", Dz1TermKey_f4 },
	{ (wstr_t)L"[15~", Dz1TermKey_f5 },
	{ (wstr_t)L"[17~", Dz1TermKey_f6 },
	{ (wstr_t)L"[18~", Dz1TermKey_f7 },
	{ (wstr_t)L"[19~", Dz1TermKey_f8 },
	{ (wstr_t)L"[20~", Dz1TermKey_f9 },
	{ (wstr_t)L"[21~", Dz1TermKey_f10 },
	{ (wstr_t)L"[23~", Dz1TermKey_f11 },
	{ (wstr_t)L"[24~", Dz1TermKey_f12 },
	{ NULL }
};

static Dz1TermKey XTERMKeysW_find(wstr_t str)
{
	struct TermcapKeyMapW *i;
	for (i = XTERMKeysW; i->pattern; i++)
		if (wcscmp(i->pattern, str) == 0) return i->key;
	return Dz1TermKey_max;
}
#endif
// XTERMKeys find
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// XtermMetaKeys find
static struct TermcapMetaKeyMapA XtermMetaKeysA[] =
{
	{ '2', Dz1TermMetaKey_shift },
	{ '3', Dz1TermMetaKey_alt },
	{ '4', Dz1TermMetaKey_shiftAlt },
	{ '5', Dz1TermMetaKey_control },
	{ '6', Dz1TermMetaKey_shiftControl },
	{ '7', Dz1TermMetaKey_controlAlt },
	{ '8', Dz1TermMetaKey_shiftControlAlt },
	{ 0, Dz1TermMetaKey_none }
};

static Dz1TermMetaKey XtermMetaKeysA_find(char c)
{
	struct TermcapMetaKeyMapA *i;
	for (i = XtermMetaKeysA; i->letter; i++)
		if (i->letter == c) break;
	return i->key;
}
#ifndef UNIX_SYSTEM
static struct TermcapMetaKeyMapW XtermMetaKeysW[] =
{
	{ L'2', Dz1TermMetaKey_shift },
	{ L'3', Dz1TermMetaKey_alt },
	{ L'4', Dz1TermMetaKey_shiftAlt },
	{ L'5', Dz1TermMetaKey_control },
	{ L'6', Dz1TermMetaKey_shiftControl },
	{ L'7', Dz1TermMetaKey_controlAlt },
	{ L'8', Dz1TermMetaKey_shiftControlAlt },
	{ 0, Dz1TermMetaKey_none }
};

static Dz1TermMetaKey XtermMetaKeysW_find(wchar_t c)
{
	struct TermcapMetaKeyMapW *i;
	for (i = XtermMetaKeysW; i->letter; i++)
		if (i->letter == c) break;
	return i->key;
}
#endif
// XtermMetaKeys find
///////////////////////////////////////////////////////////////////////////////

typedef enum
{
	XT_STATE_ESC,
	XT_STATE_SWITCH,
	XT_STATE_SEMI,
	XT_STATE_META,
	XT_STATE_LETTER,
	XT_STATE_CODE,
	XT_STATE_CODEMETA,
	XT_STATE_OPT,
	XT_STATE_TERM
} XtermFsmState;
#define XT_STATE_MAX				XT_STATE_TERM

typedef enum
{
	XT_EVENT_LB,			// '['
	XT_EVENT_SEMI,			// ';'
	XT_EVENT_NUM,			// '1..9'
	XT_EVENT_LETTER,		// 'A..z'
	XT_EVENT_TILD,			// '~'
	XT_EVENT_OPT,			// 'O'
	XT_EVENT_EXCEPTION,		// 
	XT_EVENT_MAX
} XtermFsmEvent;

static XtermFsmEvent XtermFsmEventA_get(char c)
{
	XtermFsmEvent ret = XT_EVENT_EXCEPTION;
	if (0) { }
	else if (c == '[') ret = XT_EVENT_LB;
	else if (c == ';') ret = XT_EVENT_SEMI;
	else if (c == '~') ret = XT_EVENT_TILD;
	else if (c == 'O') ret = XT_EVENT_OPT;
	else if (c >= '0' && c <= '9') ret = XT_EVENT_NUM;
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ret = XT_EVENT_LETTER;
	return ret;
}
#ifndef UNIX_SYSTEM
static XtermFsmEvent XtermFsmEventW_get(wchar_t c)
{
	XtermFsmEvent ret = XT_EVENT_EXCEPTION;
	if (0) { }
	else if (c == L'[') ret = XT_EVENT_LB;
	else if (c == L';') ret = XT_EVENT_SEMI;
	else if (c == L'~') ret = XT_EVENT_TILD;
	else if (c == L'O') ret = XT_EVENT_OPT;
	else if (c >= L'0' && c <= L'9') ret = XT_EVENT_NUM;
	else if ((c >= L'a' && c <= L'z') || (c >= L'A' && c <= L'Z')) ret = XT_EVENT_LETTER;
	return ret;
}
#endif

// [{1;(meta key num)}(key letter)
// [(key num){;(meta key num)}~
//
// O{(meta key num)}(key letter)
//
/*
           | '['  | ';'  | Num  | Letter | '~'  | 'O'  | Exception |
-----------+------+------+------+--------+------+------+-----------+
00 Escaped | 01 00|      |      |        |      | 07 09| XX      10|
-----------+------+------+------+--------+------+------+-----------+
01 Switch  |      |      | 05 01| XX   08|      |      | XX      10|
-----------+------+------+------+--------+------+------+-----------+
02 Semi    |      | 03 02| 05 11|        |      |      | XX      10|
-----------+------+------+------+--------+------+------+-----------+
03 Meta    |      |      | 04 05|        |      |      | XX      10|
-----------+------+------+------+--------+------+------+-----------+
04 Letter  |      |      |      | XX   08|      |      | XX      10|
-----------+------+------+------+--------+------+------+-----------+
05 Code    |      | 06 03| 05 04|        | XX 08|      | XX      10|
-----------+------+------+------+--------+------+------+-----------+
06 CodeMeta|      |      | 05 06|        |      |      | XX      10|
-----------+------+------+------+--------+------+------+-----------+
07 Opt     |      |      | 07 07| XX   08|      |      | XX      10|
-----------+------+------+------+--------+------+------+-----------+
*/

///////////////////////////////////////////////////////////////////////////////
// XTERM FSM
typedef struct XtermFsmA
{
	char			 buf[32];
	char			*cp;
	Dz1TermMetaKey	 meta;
	XtermFsmState	 state;
	Dz1TermKey		 key;
} XtermFsmA;

typedef int (*XtermFsmFuncA)(XtermFsmA *p, char c);

static int xt00A(XtermFsmA *p, char c)
{
	*p->cp++ = c;
	p->state = XT_STATE_SWITCH;
	return 0;
}

static int xt01A(XtermFsmA *p, char c)
{
	if (c == '1')
		p->state = XT_STATE_SEMI;
	else
	{
		*p->cp++ = c;
		p->state = XT_STATE_CODE;
	}
	return 0;
}

static int xt02A(XtermFsmA *p, char c)
{
	p->state = XT_STATE_META;
	return 0;
}

static int xt03A(XtermFsmA *p, char c)
{
	p->state = XT_STATE_CODEMETA;
	return 0;
}

static int xt04A(XtermFsmA *p, char c)
{
	*p->cp++ = c;
	p->state = XT_STATE_CODE;
	return 0;
}

static int xt05A(XtermFsmA *p, char c)
{
	p->meta = XtermMetaKeysA_find(c);
	p->state = XT_STATE_LETTER;
	return 0;
}

static int xt06A(XtermFsmA *p, char c)
{
	p->meta = XtermMetaKeysA_find(c);
	p->state = XT_STATE_CODE;
	return 0;
}

static int xt07A(XtermFsmA *p, char c)
{
	p->meta = XtermMetaKeysA_find(c);
	p->state = XT_STATE_OPT;
	return 0;
}

static int xt08A(XtermFsmA *p, char c)
{
	*p->cp++ = c;
	*p->cp = '\0';
	if ((p->key = XTERMKeysA_find(p->buf)) == Dz1TermKey_max)
	{
		p->key = Dz1TermKey_esc;
	}
	else
	{
		p->buf[0] = '\0';
	}
	return 1;
}

static int xt09A(XtermFsmA *p, char c)
{
	*p->cp++ = c;
	p->state = XT_STATE_OPT;
	return 0;
}

static int xt10A(XtermFsmA *p, char c)
{
	*p->cp++ = c;
	*p->cp = '\0';
	p->key = Dz1TermKey_esc;
	return 1;
}

static int xt12A(XtermFsmA *p, char c)
{
	*p->cp = '\0';
	p->key = Dz1TermKey_esc;
	return 1;
}

static int xt11A(XtermFsmA *p, char c)
{
	*p->cp++ = '1';
	*p->cp++ = c;
	p->state = XT_STATE_CODE;
	return 0;
}

static XtermFsmFuncA xtermFsmA[XT_STATE_MAX][XT_EVENT_MAX] =
{//   0      1      2      3      4      5      6
	{ xt00A, xt10A, xt10A, xt10A, xt10A, xt09A, xt12A }, // 0
	{ xt10A, xt10A, xt01A, xt08A, xt10A, xt10A, xt12A }, // 1
	{ xt10A, xt02A, xt11A, xt10A, xt10A, xt10A, xt12A }, // 2
	{ xt10A, xt10A, xt05A, xt10A, xt10A, xt10A, xt12A }, // 3
	{ xt10A, xt10A, xt10A, xt08A, xt10A, xt10A, xt12A }, // 4
	{ xt10A, xt03A, xt04A, xt10A, xt08A, xt10A, xt12A }, // 5
	{ xt10A, xt10A, xt06A, xt10A, xt10A, xt10A, xt12A }, // 6
	{ xt10A, xt10A, xt07A, xt08A, xt10A, xt10A, xt12A }  // 7
};
#ifndef UNIX_SYSTEM
typedef struct XtermFsmW
{
	wchar_t			 buf[32];
	wchar_t			*cp;
	Dz1TermMetaKey	 meta;
	XtermFsmState	 state;
	Dz1TermKey		 key;
} XtermFsmW;

typedef int (*XtermFsmFuncW)(XtermFsmW *p, wchar_t c);

static int xt00W(XtermFsmW *p, wchar_t c)
{
	*p->cp++ = c;
	p->state = XT_STATE_SWITCH;
	return 0;
}

static int xt01W(XtermFsmW *p, wchar_t c)
{
	if (c == L'1')
		p->state = XT_STATE_SEMI;
	else
	{
		*p->cp++ = c;
		p->state = XT_STATE_CODE;
	}
	return 0;
}

static int xt02W(XtermFsmW *p, wchar_t c)
{
	p->state = XT_STATE_META;
	return 0;
}

static int xt03W(XtermFsmW *p, wchar_t c)
{
	p->state = XT_STATE_CODEMETA;
	return 0;
}

static int xt04W(XtermFsmW *p, wchar_t c)
{
	*p->cp++ = c;
	p->state = XT_STATE_CODE;
	return 0;
}

static int xt05W(XtermFsmW *p, wchar_t c)
{
	p->meta = XtermMetaKeysW_find(c);
	p->state = XT_STATE_LETTER;
	return 0;
}

static int xt06W(XtermFsmW *p, wchar_t c)
{
	p->meta = XtermMetaKeysW_find(c);
	p->state = XT_STATE_CODE;
	return 0;
}

static int xt07W(XtermFsmW *p, wchar_t c)
{
	p->meta = XtermMetaKeysW_find(c);
	p->state = XT_STATE_OPT;
	return 0;
}

static int xt08W(XtermFsmW *p, wchar_t c)
{
	*p->cp++ = c;
	*p->cp = L'\0';
	if ((p->key = XTERMKeysW_find(p->buf)) == Dz1TermKey_max)
	{
		p->key = Dz1TermKey_esc;
	}
	else
	{
		p->buf[0] = L'\0';
	}
	return 1;
}

static int xt09W(XtermFsmW *p, wchar_t c)
{
	*p->cp++ = c;
	p->state = XT_STATE_OPT;
	return 0;
}

static int xt10W(XtermFsmW *p, wchar_t c)
{
	*p->cp++ = c;
	*p->cp = '\0';
	p->key = Dz1TermKey_esc;
	return 1;
}

static int xt12W(XtermFsmW *p, wchar_t c)
{
	*p->cp = '\0';
	p->key = Dz1TermKey_esc;
	return 1;
}

static int xt11W(XtermFsmW *p, wchar_t c)
{
	*p->cp++ = '1';
	*p->cp++ = c;
	p->state = XT_STATE_CODE;
	return 0;
}

static XtermFsmFuncW xtermFsmW[XT_STATE_MAX][XT_EVENT_MAX] =
{//   0      1      2      3      4      5      6
	{ xt00W, xt10W, xt10W, xt10W, xt10W, xt09W, xt12W }, // 0
	{ xt10W, xt10W, xt01W, xt08W, xt10W, xt10W, xt12W }, // 1
	{ xt10W, xt02W, xt11W, xt10W, xt10W, xt10W, xt12W }, // 2
	{ xt10W, xt10W, xt05W, xt10W, xt10W, xt10W, xt12W }, // 3
	{ xt10W, xt10W, xt10W, xt08W, xt10W, xt10W, xt12W }, // 4
	{ xt10W, xt03W, xt04W, xt10W, xt08W, xt10W, xt12W }, // 5
	{ xt10W, xt10W, xt06W, xt10W, xt10W, xt10W, xt12W }, // 6
	{ xt10W, xt10W, xt07W, xt08W, xt10W, xt10W, xt12W }  // 7
};
// XTERM FSM
///////////////////////////////////////////////////////////////////////////////
#endif
static ssize_t Dz1TermIoXtermA_read(char esc, Dz1TermMetaKey *meta, Dz1TermKey *key, char *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TermMetaKey _meta, *metap = meta ? meta : &_meta;

	char c;
	int read_c;
	XtermFsmA fsm = { { 0, }, NULL, Dz1TermMetaKey_none, XT_STATE_ESC, Dz1TermKey_esc };
	XtermFsmEvent ev;

	fsm.cp = fsm.buf;

	size = size > 31 ? 31 : size;

	while(1)
	{
//		if (Dz1Thread_read((u8_t *)&c, 1, 500000, errp) == 1)
		if ((read_c = Dz1Thread_getch(500000, errp)) < 0) 
			ev = XT_EVENT_EXCEPTION;
		else if ((c = (char)(read_c & 0xFF)) == 0)
			ev = XT_EVENT_EXCEPTION;
		else
			ev = XtermFsmEventA_get(c);

		if (xtermFsmA[fsm.state][ev] != NULL)
		{
			if (xtermFsmA[fsm.state][ev](&fsm, c))
			{
				ssize_t len = (ssize_t)strlen(fsm.buf);
				len = len > (ssize_t)size ? (ssize_t)size : len;
				strncpy(buf, fsm.buf, len);
				buf[len] = '\0';
				ret = len;
				Dz1Error_set(errp, 0);
				*key = fsm.key;
				*metap = fsm.meta;
				break;
			}
		}
	}
	return ret;
}

Dz1ConsoleTermSpecA xtermSpecA =
{
	{ '\x1b', 0 }, 1, Dz1TermIoXtermA_read
};
#ifndef UNIX_SYSTEM
static ssize_t Dz1TermIoXtermW_read(wchar_t esc, Dz1TermMetaKey *meta, Dz1TermKey *key, wchar_t *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TermMetaKey _meta, *metap = meta ? meta : &_meta;

	int read_c;
	wchar_t c;
	XtermFsmW fsm = { { 0, }, NULL, Dz1TermMetaKey_none, XT_STATE_ESC, Dz1TermKey_esc };
	XtermFsmEvent ev;

	fsm.cp = fsm.buf;

	size = size > 31 ? 31 : size;

	while(1)
	{
//		if (Dz1Thread_read((u8_t *)&c, sizeof(wchar_t), 500000, errp) == 1)
		if ((read_c = Dz1Thread_getch(500000, errp)) < 0) ev = XT_EVENT_EXCEPTION;
		else if ((c = (wchar_t)(read_c & 0xFFFF)) == 0) ev = XT_EVENT_EXCEPTION;
		else ev = XtermFsmEventW_get(c);
// 		else if (errp->code == ETIMEDOUT)
// 			ev = XT_EVENT_EXCEPTION;
// 		else
// 			break;

		if (xtermFsmW[fsm.state][ev] != NULL)
		{
			if (xtermFsmW[fsm.state][ev](&fsm, c))
			{
				ssize_t len = (ssize_t)wcslen(fsm.buf);
				len = len > (ssize_t)size ? (ssize_t)size : len;
				wcsncpy(buf, fsm.buf, len);
				buf[len] = L'\0';
				ret = len;
				Dz1Error_set(errp, 0);
				*key = fsm.key;
				*metap = fsm.meta;
				break;
			}
		}
	}
	return ret;
}

Dz1ConsoleTermSpecW xtermSpecW =
{
	{ L'\x1b', 0 }, 1, Dz1TermIoXtermW_read
};
#endif

