#include <dz1_malloc.h>
#include "dz1_thread_entry.h"

///////////////////////////////////////////////////////////////////////////////
// DZ1 Thread Status
///////////////////////////////////////////////////////////////////////////////
static struct Dz1ThreadStatusMapA
{
	Dz1ThreadStatus status;
	str_t str;
} Dz1ThreadStatusMapA[] =
{
	{ Dz1ThreadStatus_run,		(str_t)"Running" },
	{ Dz1ThreadStatus_sleep,	(str_t)"Sleeping" },
	{ Dz1ThreadStatus_locking,	(str_t)"Locking" },
	{ Dz1ThreadStatus_waitting,	(str_t)"Waitting" },
	{ Dz1ThreadStatus_joinning,	(str_t)"Joinning" },
	{ Dz1ThreadStatus_max,		(str_t)"Unknown" }
};

static str_t Dz1ThreadStatusStrA(Dz1ThreadStatus status)
{
	struct Dz1ThreadStatusMapA *i;
	for (i = Dz1ThreadStatusMapA; i->status != Dz1ThreadStatus_max; i++)
		if (status == i->status) break;
	return i->str;
}

#ifndef UNIX_SYSTEM
static struct Dz1ThreadStatusMapW
{
	Dz1ThreadStatus status;
	wstr_t str;
} Dz1ThreadStatusMapW[] =
{
	{ Dz1ThreadStatus_run,		(wstr_t)L"Running" },
	{ Dz1ThreadStatus_sleep,	(wstr_t)L"Sleeping" },
	{ Dz1ThreadStatus_locking,	(wstr_t)L"Locking" },
	{ Dz1ThreadStatus_waitting,	(wstr_t)L"Waitting" },
	{ Dz1ThreadStatus_joinning,	(wstr_t)L"Joinning" },
	{ Dz1ThreadStatus_max,		(wstr_t)L"Unknown" }
};

static wstr_t Dz1ThreadStatusStrW(Dz1ThreadStatus status)
{
	struct Dz1ThreadStatusMapW *i;
	for (i = Dz1ThreadStatusMapW; i->status != Dz1ThreadStatus_max; i++)
		if (status == i->status) break;
	return i->str;
}
#endif
///////////////////////////////////////////////////////////////////////////////
// DZ1 Thread Entry
///////////////////////////////////////////////////////////////////////////////
void Dz1ThreadEntry_del(Dz1ThreadEntry *p)
{
	if (!p) return;
	if (p->name) free(p->name);
	if (p->con != NULL)
		Dz1Console_delAndSetNull(&p->con);
	//free(p);
	Dz1Free(p);
}

Dz1ThreadEntry *Dz1ThreadEntry_new(struct Dz1ThreadBucket *b, int id, pthread_t th, Dz1ThreadLogLevel level,
								   Dz1Console *con, str_t name, Dz1ThreadFunc func, Dz1Error *fret, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	//Dz1ThreadEntry *ret = (Dz1ThreadEntry *)malloc(sizeof(Dz1ThreadEntry));
	Dz1ThreadEntry *ret = (Dz1ThreadEntry *)Dz1Malloc(sizeof(Dz1ThreadEntry), errp);
	if (ret == NULL) Dz1Error_set(errp, ENOMEM);
	else
	{
		memset(ret, 0, sizeof(Dz1ThreadEntry));

		pthread_cleanup_push(Dz1ThreadEntry_delAndSetNull, (void *)&ret);

		if ((ret->name = strdup(name)) == NULL) { Dz1Error_set(errp, ENOMEM); }
		else
		{
			ret->bucket = b;
			ret->id = id;
			ret->th = th;
			ret->level = level;
			ret->status = Dz1ThreadStatus_run;
			ret->con = con;
			ret->func = func;
			ret->err = fret;
			ret->stack = NULL;

			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1ThreadEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// DebugLevelMap
struct DebugLevelMapA
{
	u32_t level;
	char on;
	char off;
};

static struct DebugLevelMapA DebugLevelMapA[] = {
	{ DZ1_THREAD_LOG_CRITICAL,		'C', 'c' },
	{ DZ1_THREAD_LOG_ERROR,			'E', 'e' },
	{ DZ1_THREAD_LOG_WARN,			'W', 'w' },
	{ DZ1_THREAD_LOG_MESSAGE,		'M', 'm' },

	{ DZ1_THREAD_LOG_TASK_DEBUG,	'T', 't' },
	{ DZ1_THREAD_LOG_DEBUG,			'D', 'd' },
	{ DZ1_THREAD_LOG_RESERVED12,	'2', L'-' },
	{ DZ1_THREAD_LOG_RESERVED13,	'3', L'-' },

	{ DZ1_THREAD_LOG_RESERVED20,	'0', '-' },
	{ DZ1_THREAD_LOG_RESERVED21,	'1', '-' },
	{ DZ1_THREAD_LOG_RESERVED22,	'2', '-' },
	{ DZ1_THREAD_LOG_RESERVED23,	'3', '-' },

	{ DZ1_THREAD_LOG_RESERVED30,	'0', '-' },
	{ DZ1_THREAD_LOG_RESERVED31,	'1', '-' },
	{ DZ1_THREAD_LOG_RESERVED32,	'2', '-' },
	{ DZ1_THREAD_LOG_RESERVED33,	'3', '-' },
	/*
	{ DZ1_THREAD_LOG_USER01,		'0', '-' },
	{ DZ1_THREAD_LOG_USER02,		'1', '-' },
	{ DZ1_THREAD_LOG_USER03,		'2', '-' },
	{ DZ1_THREAD_LOG_USER04,		'3', '-' },
	{ DZ1_THREAD_LOG_USER05,		'4', '-' },
	{ DZ1_THREAD_LOG_USER06,		'5', '-' },
	{ DZ1_THREAD_LOG_USER07,		'6', '-' },
	{ DZ1_THREAD_LOG_USER08,		'7', '-' },
	{ DZ1_THREAD_LOG_USER09,		'8', '-' },
	{ DZ1_THREAD_LOG_USER10,		'9', '-' },
	{ DZ1_THREAD_LOG_USER11,		'A', '-' },
	{ DZ1_THREAD_LOG_USER12,		'B', '-' },
	{ DZ1_THREAD_LOG_USER13,		'C', '-' },
	{ DZ1_THREAD_LOG_USER14,		'D', '-' },
	{ DZ1_THREAD_LOG_USER15,		'E', '-' },
	{ DZ1_THREAD_LOG_USER16,		'F', '-' },
	*/
	{ DZ1_THREAD_LOG_MINIMUM,		'\0', '\0' },
};
static char _hex_mapA[] = "0123456789ABCDEF";
#ifndef UNIX_SYSTEM
struct DebugLevelMapW
{
	u32_t level;
	wchar_t on;
	wchar_t off;
};

static struct DebugLevelMapW DebugLevelMapW[] = {
	{ DZ1_THREAD_LOG_CRITICAL,		L'C', L'c' },
	{ DZ1_THREAD_LOG_ERROR,			L'E', L'e' },
	{ DZ1_THREAD_LOG_WARN,			L'W', L'w' },
	{ DZ1_THREAD_LOG_MESSAGE,		L'M', L'm' },
	{ DZ1_THREAD_LOG_TASK_DEBUG,	L'T', L't' },
	{ DZ1_THREAD_LOG_DEBUG,			L'D', L'd' },
	{ DZ1_THREAD_LOG_RESERVED12,	L'2', L'-' },
	{ DZ1_THREAD_LOG_RESERVED13,	L'3', L'-' },

	{ DZ1_THREAD_LOG_RESERVED20,	L'0', L'-' },
	{ DZ1_THREAD_LOG_RESERVED21,	L'1', L'-' },
	{ DZ1_THREAD_LOG_RESERVED22,	L'2', L'-' },
	{ DZ1_THREAD_LOG_RESERVED23,	L'3', L'-' },

	{ DZ1_THREAD_LOG_RESERVED30,	L'0', L'-' },
	{ DZ1_THREAD_LOG_RESERVED31,	L'1', L'-' },
	{ DZ1_THREAD_LOG_RESERVED32,	L'2', L'-' },
	{ DZ1_THREAD_LOG_RESERVED33,	L'3', L'-' },
	/*
	{ DZ1_THREAD_LOG_USER01,		L'0', L'-' },
	{ DZ1_THREAD_LOG_USER02,		L'1', L'-' },
	{ DZ1_THREAD_LOG_USER03,		L'2', L'-' },
	{ DZ1_THREAD_LOG_USER04,		L'3', L'-' },
	{ DZ1_THREAD_LOG_USER05,		L'4', L'-' },
	{ DZ1_THREAD_LOG_USER06,		L'5', L'-' },
	{ DZ1_THREAD_LOG_USER07,		L'6', L'-' },
	{ DZ1_THREAD_LOG_USER08,		L'7', L'-' },
	{ DZ1_THREAD_LOG_USER09,		L'8', L'-' },
	{ DZ1_THREAD_LOG_USER10,		L'9', L'-' },
	{ DZ1_THREAD_LOG_USER11,		L'A', L'-' },
	{ DZ1_THREAD_LOG_USER12,		L'B', L'-' },
	{ DZ1_THREAD_LOG_USER13,		L'C', L'-' },
	{ DZ1_THREAD_LOG_USER14,		L'D', L'-' },
	{ DZ1_THREAD_LOG_USER15,		L'E', L'-' },
	{ DZ1_THREAD_LOG_USER16,		L'F', L'-' },
	*/
	{ DZ1_THREAD_LOG_MINIMUM,		L'\0', L'\0' },
};
static char _hex_mapW[] = "0123456789ABCDEF";
#endif
// DebugLevelMap
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DebugLevelStr
static str_t DebugLevelStrA(Dz1ThreadLogLevel level, char buf[33])
{
	char *cp = buf;
	u16_t user_flag = (u16_t)(level & 0xFFFF);
	struct DebugLevelMapA *i = DebugLevelMapA;

	for (i = DebugLevelMapA; i->level != DZ1_THREAD_LOG_MINIMUM; i++, cp++)
		if (level & i->level) *cp = i->on; else *cp = i->off;
	*cp++ = ':';
	*cp++ = _hex_mapA[((user_flag >> 12) & 0xF)];
	*cp++ = _hex_mapA[((user_flag >> 8) & 0xF)];
	*cp++ = _hex_mapA[((user_flag >> 4) & 0xF)];
	*cp++ = _hex_mapA[((user_flag >> 0) & 0xF)];
	*cp = 0;
	return buf;
}
#ifndef UNIX_SYSTEM
static wstr_t DebugLevelStrW(Dz1ThreadLogLevel level, wchar_t buf[33])
{
	wchar_t *cp = buf;
	u16_t user_flag = (u16_t)(level & 0xFFFF);
	struct DebugLevelMapW *i = DebugLevelMapW;

	for (i = DebugLevelMapW; i->level != DZ1_THREAD_LOG_MINIMUM; i++, cp++)
		if (level & i->level) *cp = i->on; else *cp = i->off;
	*cp++ = L':';
	*cp++ = _hex_mapW[((user_flag >> 12) & 0xF)];
	*cp++ = _hex_mapW[((user_flag >> 8) & 0xF)];
	*cp++ = _hex_mapW[((user_flag >> 4) & 0xF)];
	*cp++ = _hex_mapW[((user_flag >> 0) & 0xF)];
	*cp = 0;
	return buf;
}
#endif
// DebugLevelStr
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1ThreadEntry_dump
void Dz1ThreadEntryA_dump(Dz1Console *con, Dz1ThreadEntry *p, int tab)
{
	char logStr[33];
	//int its_me = FALSE;
	if (!p) return;
	if (pthread_equal(p->th, pthread_self()))
	{
	//	its_me = TRUE;
		Dz1ConsoleA_tprintf(con, tab, "*");
	}
	else Dz1ConsoleA_tprintf(con, tab, " ");

#ifdef PTW32_VERSION
	Dz1ConsoleA_tprintf(con, 0, "[ID:%08X][TH:%p][LOG:%s %08X] %s.%s(%d)\n",
									p->id, p->th.p,
									DebugLevelStrA(p->level, logStr), p->level,
									p->name, Dz1ThreadStatusStrA(p->status), p->status);
#else
	Dz1ConsoleA_tprintf(con, 0, "[ID:%08X][TH:" DZ1_PTR_SIZED_PRINTF "][LOG:%s %08X] %s.%s(%d)\n",
									p->id, (DZ1_PTR_SIZED_TYPE)p->th,
									DebugLevelStrA(p->level, logStr), p->level,
									p->name, Dz1ThreadStatusStrA(p->status), p->status);
#endif
	//if (its_me && p->stack)
	if (p->stack)
	{
		Dz1ThreadStack *node;
		for (node = p->stack; node; node = node->next)
			if (node->comment)
				Dz1ConsoleA_tprintf(con, tab + 1, "[%s:%d][%s]\n", node->file, node->line, node->comment);
			else
				Dz1ConsoleA_tprintf(con, tab + 1, "[%s:%d]\n", node->file, node->line);
	}
}
#ifndef UNIX_SYSTEM
void Dz1ThreadEntryW_dump(Dz1Console *con, Dz1ThreadEntry *p, int tab)
{
	wchar_t logStr[33];
	//int its_me = FALSE;
	if (!p) return;
	if (pthread_equal(p->th, pthread_self()))
	{
	//	its_me = TRUE;
		Dz1ConsoleW_tprintf(con, tab, L"*");
	}
	else Dz1ConsoleW_tprintf(con, tab, L" ");

#ifdef PTW32_VERSION
	Dz1ConsoleW_tprintf(con, 0, L"[ID:%08X][TH:%p][LOG:%s %08X] %s.%s(%d)\n",
									p->id, p->th.p,
									DebugLevelStrW(p->level, logStr), p->level,
									p->name, Dz1ThreadStatusStrW(p->status), p->status);
#else
	Dz1ConsoleW_tprintf(con, 0, L"[ID:%08X][TH:" DZ1_PTR_SIZED_PRINTF "][LOG:%s %08X] %s.%s(%d)\n",
									p->id, (DZ1_PTR_SIZED_TYPE)p->th,
									DebugLevelStrW(p->level, logStr), p->level,
									p->name, Dz1ThreadStatusStrW(p->status), p->status);
#endif
	//if (its_me && p->stack)
	if (p->stack)
	{
		Dz1ThreadStack *node;
		for (node = p->stack; node; node = node->next)
			if (node->comment)
				Dz1ConsoleW_tprintf(con, tab + 1, L"[%s:%d][%s]\n", node->file, node->line, node->comment);
			else
				Dz1ConsoleW_tprintf(con, tab + 1, L"[%s:%d]\n", node->file, node->line);
	}
}
#endif
// Dz1ThreadEntry_dump
///////////////////////////////////////////////////////////////////////////////
