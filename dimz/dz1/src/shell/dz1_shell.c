#include <dz1_stdio.h>
#include <dz1_aatree.h>
#include <dz1_str.h>
#include <dz1_malloc.h>
#include "../kernel/dz1_thread_stdio.h"
#include <dz1_time.h>

#include "dz1_shell_parse.h"
#include "dz1_shell_args.h"
#include "dz1_shell_builtin_cmds.h"
#include "dz1_shell.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1Shell
void *Dz1ShellA_new(str_t termName, u32_t cmdFlag, u32_t historySize, str_t user, str_t host, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellA *ret = NULL;

	if (Dz1Str_isVoid(user) == TRUE || Dz1Str_isVoid(host) == TRUE) Dz1Error_set(errp, EINVAL);
	else if ((ret = (Dz1ShellA *)Dz1Malloc(sizeof(Dz1ShellA), errp)))
	{
		memset(ret, 0, sizeof(Dz1ShellA));
		pthread_cleanup_push(Dz1ShellA_delAndSetNull, (void *)&ret);

		if ((ret->user = Dz1StrA_dup(user, errp)) == NULL) { }
		else if ((ret->systemName = Dz1StrA_dup(host, errp)) == NULL) { }
		else if ((ret->env = Dz1ShellVarA_new(errp)) == NULL) { }
		else if ((ret->alias = Dz1ShellVarA_new(errp)) == NULL) { }
		else if ((ret->history = Dz1ShellHistoryA_new(historySize, errp)) == NULL) { }
		else if ((ret->cmd = Dz1ShellCmdA_new(errp)) == NULL) { }
		else if ((*errp = Dz1ShellBuiltinCmdInitA(ret, cmdFlag)).code) { }
		else if ((*errp = ret->env->insert(ret->env, (str_t)"HOST", host)).code) { }
		else if ((*errp = ret->env->insert(ret->env, (str_t)"USER", user)).code) { }
		else if ((*errp = ret->env->insert(ret->env, (str_t)"PS1", (str_t)"[\\u@\\h]\\$ ")).code) { }
		else if ((*errp = Dz1ShellInputA_init(&ret->input, termName)).code) { }
		else
		{
			ret->history->cursorInit(ret->history, Dz1FifoCursorPos_head);
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1Shell_delAndSetNull, (void *)&ret);
	}
	return (void *)ret;
}

void Dz1ShellA_del(void *ptr)
{
	Dz1ShellA *p = (Dz1ShellA *)ptr;
	if (!ptr) return;
	if (p->user) Dz1StrA_del(p->user);
	if (p->systemName) Dz1StrA_del(p->systemName);
	if (p->env) Dz1ShellVarA_del(p->env);
	if (p->alias) Dz1ShellVarA_del(p->alias);
	if (p->history) Dz1ShellHistoryA_del(p->history);
	if (p->cmd) Dz1ShellCmdA_del(p->cmd);
	Dz1ShellInputA_clean(&p->input);
	Dz1Free(p);
}

void Dz1ShellA_delAndSetNull(void *ptr)
{
	Dz1ShellA **p = (Dz1ShellA **)ptr;
	Dz1ShellA_del(*p);
	*p = NULL;
}

bool_t Dz1ShellA_thredCmdSetLogFlag(u32_t flag, const str_t full_name, const str_t short_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1ShellBuiltinCmdA_setLogFlag(flag, full_name, short_name) == FALSE) ERR_SET_OUT(errp, EEXIST);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
#ifndef UNIX_SYSTEM
void *Dz1ShellW_new(wstr_t termName, u32_t cmdFlag, u32_t historySize, wstr_t user, wstr_t host, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellW *ret = NULL;

	if (Dz1Str_isVoid(user) == TRUE || Dz1Str_isVoid(host) == TRUE) Dz1Error_set(errp, EINVAL);
	else if ((ret = (Dz1ShellW *)Dz1Malloc(sizeof(Dz1ShellW), errp)))
	{
		memset(ret, 0, sizeof(Dz1ShellW));
		pthread_cleanup_push(Dz1ShellW_delAndSetNull, (void *)&ret);

		if ((ret->user = Dz1StrW_dup(user, errp)) == NULL) { }
		else if ((ret->systemName = Dz1StrW_dup(host, errp)) == NULL) { }
		else if ((ret->env = Dz1ShellVarW_new(errp)) == NULL) { }
		else if ((ret->alias = Dz1ShellVarW_new(errp)) == NULL) { }
		else if ((ret->history = Dz1ShellHistoryW_new(historySize, errp)) == NULL) { }
		else if ((ret->cmd = Dz1ShellCmdW_new(errp)) == NULL) { }
		else if ((*errp = Dz1ShellBuiltinCmdInitW(ret, cmdFlag)).code) { }
		else if ((*errp = ret->env->insert(ret->env, (wstr_t)L"HOST", host)).code) { }
		else if ((*errp = ret->env->insert(ret->env, (wstr_t)L"USER", user)).code) { }
		else if ((*errp = ret->env->insert(ret->env, (wstr_t)L"PS1", (wstr_t)L"[\\u@\\h]\\$ ")).code) { }
		else if ((*errp = Dz1ShellInputW_init(&ret->input, termName)).code) { }
		else
		{
			ret->history->cursorInit(ret->history, Dz1FifoCursorPos_head);
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1Shell_delAndSetNull, (void *)&ret);
	}
	return (void *)ret;
}

void Dz1ShellW_del(void *ptr)
{
	Dz1ShellW *p = (Dz1ShellW *)ptr;
	if (!ptr) return;
	if (p->user) Dz1StrW_del(p->user);
	if (p->systemName) Dz1StrW_del(p->systemName);
	if (p->env) Dz1ShellVarW_del(p->env);
	if (p->alias) Dz1ShellVarW_del(p->alias);
	if (p->history) Dz1ShellHistoryW_del(p->history);
	if (p->cmd) Dz1ShellCmdW_del(p->cmd);
	Dz1ShellInputW_clean(&p->input);
	Dz1Free(p);
}

void Dz1ShellW_delAndSetNull(void *ptr)
{
	Dz1ShellW **p = (Dz1ShellW **)ptr;
	Dz1ShellW_del(*p);
	*p = NULL;
}

bool_t Dz1ShellW_thredCmdSetLogFlag(u32_t flag, const wstr_t full_name, const wstr_t short_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1ShellBuiltinCmdW_setLogFlag(flag, full_name, short_name) == FALSE) ERR_SET_OUT(errp, EEXIST);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
#endif
// Dz1Shell
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Shell Command
Dz1Error Dz1ShellA_cmdReg(void *h, str_t name, Dz1ShellCmdFuncA func, void *funcParam, str_t help)
{
	Dz1ShellA *p = (Dz1ShellA *)h;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p ||!name || !func || !help) Dz1Error_set(&err, EINVAL);
	else err = p->cmd->insert(p->cmd, name, func, funcParam, help);
	return err;
}

void Dz1ShellA_cmdDereg(void *h, str_t name)
{
	Dz1ShellA *p = (Dz1ShellA *)h;
	if (p && name) p->cmd->remove(p->cmd, name);
}
#ifndef UNIX_SYSTEM
Dz1Error Dz1ShellW_cmdReg(void *h, wstr_t name, Dz1ShellCmdFuncW func, void *funcParam, wstr_t help)
{
	Dz1ShellW *p = (Dz1ShellW *)h;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p ||!name || !func || !help) Dz1Error_set(&err, EINVAL);
	else err = p->cmd->insert(p->cmd, name, func, funcParam, help);
	return err;
}

void Dz1ShellW_cmdDereg(void *h, wstr_t name)
{
	Dz1ShellW *p = (Dz1ShellW *)h;
	if (p && name) p->cmd->remove(p->cmd, name);
}
#endif
// Dz1Shell Command
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Shell Environment
Dz1Error Dz1ShellA_envSet(void *h, str_t name, str_t value)
{
	Dz1ShellA *p = (Dz1ShellA *)h;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!p || !name || !value) Dz1Error_set(&err, EINVAL);
	else err = p->env->insert(p->env, name, value);

	return err;
}

void Dz1ShellA_envUnset(void *h, str_t name)
{
	Dz1ShellA *p = (Dz1ShellA *)h;
	if (p && name) p->env->remove(p->env, name);
}
#ifndef UNIX_SYSTEM
Dz1Error Dz1ShellW_envSet(void *h, wstr_t name, wstr_t value)
{
	Dz1ShellW *p = (Dz1ShellW *)h;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!p || !name || !value) Dz1Error_set(&err, EINVAL);
	else err = p->env->insert(p->env, name, value);

	return err;
}

void Dz1ShellW_envUnset(void *h, wstr_t name)
{
	Dz1ShellW *p = (Dz1ShellW *)h;
	if (p && name) p->env->remove(p->env, name);
}
#endif
// Dz1Shell Environment
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Shell Alias
Dz1Error Dz1ShellA_alias(void *h, str_t name, str_t value)
{
	Dz1ShellA *p = (Dz1ShellA *)h;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!p || !name || !value) Dz1Error_set(&err, EINVAL);
	else err = p->alias->insert(p->alias, name, value);

	return err;
}

void Dz1ShellA_unalias(void *h, str_t name)
{
	Dz1ShellA *p = (Dz1ShellA *)h;
	if (p && name) p->alias->remove(p->alias, name);
}
#ifndef UNIX_SYSTEM
Dz1Error Dz1ShellW_alias(void *h, wstr_t name, wstr_t value)
{
	Dz1ShellW *p = (Dz1ShellW *)h;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!p || !name || !value) Dz1Error_set(&err, EINVAL);
	else err = p->alias->insert(p->alias, name, value);

	return err;
}

void Dz1ShellW_unalias(void *h, wstr_t name)
{
	Dz1ShellW *p = (Dz1ShellW *)h;
	if (p && name) p->alias->remove(p->alias, name);
}
#endif
// Dz1Shell Alias
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Shell Prompt
static int get_timeA(char *dst)
{
	time_t now = time(NULL);
	struct tm *tmp = localtime(&now);
	struct tm tm = *tmp;
	sprintf(dst, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
	return (int)strlen(dst);
}

static str_t week_nameA[] =
{
	(str_t)"Sun",
	(str_t)"Mon",
	(str_t)"Tue",
	(str_t)"Wed",
	(str_t)"Thu",
	(str_t)"Fri",
	(str_t)"Sat"
};
static str_t month_nameA[] =
{
	(str_t)"Jan",
	(str_t)"Feb",
	(str_t)"Mar",
	(str_t)"Apr",
	(str_t)"May",
	(str_t)"Jun",
	(str_t)"Jul",
	(str_t)"Aug",
	(str_t)"Sep",
	(str_t)"Oct",
	(str_t)"Nov",
	(str_t)"Dec"
};
static int get_dateA(char *dst)
{
	time_t now = time(NULL);
	struct tm *tmp = localtime(&now);
	struct tm tm = *tmp;
	sprintf(dst, "%s %s %02d", week_nameA[tm.tm_wday], month_nameA[tm.tm_mon], tm.tm_mday);
	return (int)strlen(dst);
}

static str_t Dz1ShellA_prompt(Dz1ShellA *p, int *len)
{
	int _len, *lenp = len ? len : &_len;
	char *s = p->env->find(p->env, (str_t)"PS1");
	if (s == NULL) sprintf(p->buf, DZ1_SHELL_NAME_A "$ ");
	else
	{
		int size;
		char *c = p->buf;
		while(*s)
		{
			if (*s != '\\') *c++ = *s++; // Pass Normal Letter
			else
			{	// Escape Sequence
				s++; // skip '\' letter
				switch(*s)
				{
					// system time
					case 't': size = get_timeA(c); c += size; break;
					// system date
					case 'd': size = get_dateA(c); c += size; break;
					// new line
					case 'n': *c++ = '\n'; break;
					// shell name
					case 's': strcpy(c, DZ1_SHELL_NAME_A); c += strlen(DZ1_SHELL_NAME_A); break;
					// current path's dirname : not support
					case 'w': break;
					// current path's basename : not support
					case 'W': break;
					// login user name
					case 'u': strcpy(c, p->user); c += strlen(p->user); break;
					// host name
					case 'h': strcpy(c, p->systemName); c += strlen(p->systemName); break;
					// command count sence user login
					case '#':
					// history number : this is same as '#' in Dz1Shell
					case '!': size = sprintf(c, "%d", p->history->count(p->history)); c += size; break;
					// prompt letter. if user is root(UID==0) then this is '#' else '$'
					case '$': *c++ = '$'; break;
					// other letter is pass
					default: *c++ = *s; break;
				}
				s++;
			}
		}
		*c = '\0';
	}
	*lenp = (int)strlen(p->buf);
	return p->buf;
}
#ifndef UNIX_SYSTEM
static int get_timeW(wchar_t *dst, size_t sz)
{
	time_t now = time(NULL);
	struct tm *tmp = localtime(&now);
	struct tm tm = *tmp;
	swprintf(dst, sz, L"%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
	return (int)wcslen(dst);
}

static wstr_t week_nameW[] =
{
	(wstr_t)L"Sun",
	(wstr_t)L"Mon",
	(wstr_t)L"Tue",
	(wstr_t)L"Wed",
	(wstr_t)L"Thu",
	(wstr_t)L"Fri",
	(wstr_t)L"Sat"
};
static wstr_t month_nameW[] =
{
	(wstr_t)L"Jan",
	(wstr_t)L"Feb",
	(wstr_t)L"Mar",
	(wstr_t)L"Apr",
	(wstr_t)L"May",
	(wstr_t)L"Jun",
	(wstr_t)L"Jul",
	(wstr_t)L"Aug",
	(wstr_t)L"Sep",
	(wstr_t)L"Oct",
	(wstr_t)L"Nov",
	(wstr_t)L"Dec"
};
static int get_dateW(wchar_t *dst, size_t sz)
{
	time_t now = time(NULL);
	struct tm *tmp = localtime(&now);
	struct tm tm = *tmp;
	swprintf(dst, sz, L"%s %s %02d", week_nameW[tm.tm_wday], month_nameW[tm.tm_mon], tm.tm_mday);
	return (int)wcslen(dst);
}

static wstr_t Dz1ShellW_prompt(Dz1ShellW *p, int *len)
{
	int _len, *lenp = len ? len : &_len;
	wchar_t *s = p->env->find(p->env, (wstr_t)L"PS1");
	if (s == NULL) swprintf(p->buf, DZ1_SHELL_BUFFER_SIZE - 1, DZ1_SHELL_NAME_W L"$ ");
	else
	{
		int size;
		size_t sz = DZ1_SHELL_BUFFER_SIZE - 1;
		wchar_t *c = p->buf;
		while(*s)
		{
			if (*s != L'\\') { *c++ = *s++; sz--; }// Pass Normal Letter
			else
			{	// Escape Sequence
				s++; // skip '\' letter
				sz--;
				switch(*s)
				{
					// system time
					case L't': size = get_timeW(c, sz); c += size; sz -= size; break;
					// system date
					case L'd': size = get_dateW(c, sz); c += size; sz -= size; break;
					// new line
					case L'n': *c++ = L'\n'; sz--; break;
					// shell name
					case L's': wcscpy(c, DZ1_SHELL_NAME_W); size = (int)wcslen(DZ1_SHELL_NAME_W); c+= size; sz -= size; break;
					// current path's dirname : not support
					case L'w': break;
					// current path's basename : not support
					case L'W': break;
					// login user name
					case L'u': wcscpy(c, p->user); size = (int)wcslen(p->user); c += size; sz -= size; break;
					// host name
					case L'h': wcscpy(c, p->systemName); size = (int)wcslen(p->systemName); c += size; sz -= size; break;
					// command count sense user login
					case L'#':
					// history number : this is same as '#' in Dz1Shell
					case L'!': size = swprintf(c, sz, L"%d", p->history->count(p->history)); c += size; sz -= size; break;
					// prompt letter. if user is root(UID==0) then this is '#' else '$'
					case L'$': *c++ = L'$'; sz--; break;
					// other letter is pass
					default: *c++ = *s; break;
				}
				s++;
			}
		}
		*c = 0;
	}
	*lenp = (int)wcslen(p->buf);
	return p->buf;
}
#endif
// Dz1Shell Prompt
///////////////////////////////////////////////////////////////////////////////

typedef enum Dz1ShellCmdParseTokenType
{
	Dz1ShellCmdParseTokenType_normal,
	Dz1ShellCmdParseTokenType_singleCotate,
	Dz1ShellCmdParseTokenType_doubleCotate,
	Dz1ShellCmdParseTokenType_broken
} Dz1ShellCmdParseTokenType;

typedef enum Dz1ShellCmdParseLetter
{
	Dz1ShellCmdParseLetter_alnum,
	Dz1ShellCmdParseLetter_cp949,
	Dz1ShellCmdParseLetter_singleCotate,
	Dz1ShellCmdParseLetter_doubleCotate,
	Dz1ShellCmdParseLetter_unknown
} Dz1ShellCmdParseLetter;

///////////////////////////////////////////////////////////////////////////////
// Dz1Shell Execute Misc Utility
static void trimNewLineA(char *buf)
{
	char *cp = buf;
	while(*cp)
	{
		if (*cp == '\r' || *cp == '\n')
		{
			char *src = cp + 1;
			char *dst = cp;
			while(*src) *dst++ = *src++;
		}
		cp++;
	}
}

static bool_t isDigitStringA(str_t src)
{
	while(*src)
		if (!isdigit(*src++)) return FALSE;
	return TRUE;
}

static bool_t isCP949(char *src, size_t size)
{
	if (size >= 2 && *src & 0x80 && *(src + 1) != '\0' && *(src + 1) & 0x80) return TRUE;
	return FALSE;
}

static Dz1ShellCmdParseLetter _get_letter_typeA(char *src, size_t size)
{
	if		( *src == '!' || isalnum( (int)( *src & 0xFF) ) )	return Dz1ShellCmdParseLetter_alnum;
	else if ( *src == '\'' )									return Dz1ShellCmdParseLetter_singleCotate;
	else if ( *src == '\"' )									return Dz1ShellCmdParseLetter_doubleCotate;
	else if (isCP949(src, size))								return Dz1ShellCmdParseLetter_cp949;
	else														return Dz1ShellCmdParseLetter_unknown;
}
#ifndef UNIX_SYSTEM
static void trimNewLineW(wchar_t *buf)
{
	wchar_t *cp = buf;
	while(*cp)
	{
		if (*cp == L'\r' || *cp == L'\n')
		{
			wchar_t *src = cp + 1;
			wchar_t *dst = cp;
			while(*src) *dst++ = *src++;
		}
		cp++;
	}
}

static bool_t isDigitStringW(wstr_t src)
{
	while(*src)
		if (!iswdigit(*src++)) return FALSE;
	return TRUE;
}

static Dz1ShellCmdParseLetter _get_letter_typeW(wchar_t *src, size_t size)
{
	if		( *src == L'!' || iswalnum( (int)(*src & 0xFFFF)) )	return Dz1ShellCmdParseLetter_alnum;
	else if ( *src == L'\'' )									return Dz1ShellCmdParseLetter_singleCotate;
	else if ( *src == L'\"' )									return Dz1ShellCmdParseLetter_doubleCotate;
	else														return Dz1ShellCmdParseLetter_unknown;
}
#endif
// Dz1Shell Execute Misc Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Shell Command Execute
typedef struct CmdExpandArgA
{
	Dz1ShellVarA *env;
	str_t dst;
	bool_t expandded;
} CmdExpandArgA;

static __inline__ Dz1Error _cmdExpandA(CmdExpandArgA *p, Dz1ShellParseToken type, str_t token)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	str_t expand = NULL;
	switch(type)
	{
		case Dz1ShellParseToken_doubleCotatedString:
			*p->dst++ = '\"';
			if (Dz1ShellParseA(token, TRUE, FALSE, (Dz1ShellParseEmitFuncA)_cmdExpandA, (void *)p, &err) >= 0)
			{
				*p->dst++ = '\"'; 
				*p->dst++ = ' ';
				*p->dst = '\0';
			}
			break;
		case Dz1ShellParseToken_singleCotatedString:
			*p->dst++ = '\'';
			strcpy(p->dst, token);
			p->dst += strlen(token);
			*p->dst++ = '\'';
			*p->dst++ = ' ';
			*p->dst = '\0';
			break;
		case Dz1ShellParseToken_word:
			strcpy(p->dst, token);
			p->dst += strlen(token);
			*p->dst++ = ' ';
			*p->dst = '\0';
			break;
		case Dz1ShellParseToken_literal:
			if ((expand = p->env->find(p->env, token)))
			{
				strcpy(p->dst, expand);
				p->dst += strlen(expand);
				*p->dst++ = ' ';
				*p->dst = '\0';
				p->expandded = TRUE;
			}
			break;
		default: break;
	}
	return err;
}

typedef struct Dz1ShellCmdParseTokenA
{
	Dz1ShellCmdParseTokenType		type;
	char							string[1024];
} Dz1ShellCmdParseTokenA;

#define TRIM_WHITE_SPACE_A(srcp)		do { while( *(srcp) != 0 && isspace( (*srcp) & 0xFF)) (srcp)++; } while(0)
static char *_take_one_wordA(str_t src, Dz1ShellCmdParseTokenA *dst)
{
	char *cp = src;
	size_t size = strlen(src);
	char *dp = dst->string;

	Dz1ShellCmdParseLetter letter;

	dst->type = Dz1ShellCmdParseTokenType_broken;
	*dp = '\0';

	TRIM_WHITE_SPACE_A(cp);
	letter = _get_letter_typeA(cp, size);
	if (letter == Dz1ShellCmdParseLetter_singleCotate)
	{
		bool_t done = FALSE;
		cp++; size--;
		while(size && done == FALSE && (letter = _get_letter_typeA(cp, size)) != Dz1ShellCmdParseLetter_unknown)
		{
			switch(letter)
			{
			default:
			case Dz1ShellCmdParseLetter_cp949:
				*dp++ = *cp++; size--;
			case Dz1ShellCmdParseLetter_doubleCotate:
			case Dz1ShellCmdParseLetter_alnum:
				*dp++ = *cp++; size--;
				break;
			case Dz1ShellCmdParseLetter_singleCotate:
				cp++; size--;
				done = TRUE;
				break;
			}
		}
		if (done) dst->type = Dz1ShellCmdParseTokenType_singleCotate;
		else dst->type = Dz1ShellCmdParseTokenType_broken;
	}
	else if (letter == Dz1ShellCmdParseLetter_doubleCotate)
	{
		bool_t done = FALSE;
		cp++; size--;
		while(size && done == FALSE && (letter = _get_letter_typeA(cp, size)) != Dz1ShellCmdParseLetter_unknown)
		{
			switch(letter)
			{
			default:
			case Dz1ShellCmdParseLetter_cp949:
				*dp++ = *cp++; size--;
			case Dz1ShellCmdParseLetter_singleCotate:
			case Dz1ShellCmdParseLetter_alnum:
				*dp++ = *cp++; size--;
				break;
			case Dz1ShellCmdParseLetter_doubleCotate:
				cp++; size--;
				done = TRUE;
				break;
			}
		}
		if (done) dst->type = Dz1ShellCmdParseTokenType_doubleCotate;
		else dst->type = Dz1ShellCmdParseTokenType_broken;
	}
	else
	{
		bool_t broken = FALSE;
		while(broken == FALSE && (letter = _get_letter_typeA(cp, size)) != Dz1ShellCmdParseLetter_unknown)
		{
			switch(letter)
			{
			default:
			case Dz1ShellCmdParseLetter_cp949:
				*dp++ = *cp++; size--;
			case Dz1ShellCmdParseLetter_alnum:
				*dp++ = *cp++; size--;
				break;
			case Dz1ShellCmdParseLetter_singleCotate:
			case Dz1ShellCmdParseLetter_doubleCotate:
				broken = TRUE;
				break;
			}
		}

		if (broken) dst->type = Dz1ShellCmdParseTokenType_broken;
		else dst->type = Dz1ShellCmdParseTokenType_normal;
	}
	*dp++ = '\0';
	return cp;
}

typedef struct MatchFinterArgA
{
	char *src;
	Dz1ShellVarEntryA *result;
} MatchFinterArgA;

static Dz1Error _match_finderA(void *ptr, void *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MatchFinterArgA *arg = (MatchFinterArgA *)ptr;
	Dz1ShellVarEntryA *p = (Dz1ShellVarEntryA *)data;
	if (strncmp(arg->src, p->name, strlen(p->name)) == 0)
	{
		arg->result = p;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

static __inline__ bool_t cmdExpandA(Dz1ShellHistoryA *history, Dz1ShellVarA *alias, Dz1ShellVarA *env, str_t dst, str_t src)
{
	bool_t ret = TRUE;

	char *cp = src;
	char *dp = dst;
	Dz1ShellCmdParseTokenA token;

	str_t aliased = NULL;
	cp = _take_one_wordA(cp, &token);
	
	// first token
	if (token.string[0] == '!')
	{	// check history expand
		bool_t found = FALSE;
		str_t history_key = &token.string[1];
		if (isDigitStringA(history_key))
		{
			int hisCount = history->count(history), pos = hisCount - (history->num - atoi(history_key));
			if (pos >= 0 && pos < hisCount)
			{
				for (history->cursorInit(history, Dz1FifoCursorPos_head); history->cursorCond(history); history->cursorNext(history, FALSE))
					if (pos-- == 0) { found = TRUE; break; }
			}
		}
		else
		{
			for (history->cursorInit(history, Dz1FifoCursorPos_tail); history->cursorCond(history); history->cursorPrev(history, FALSE))
				if (strncmp(history->cursorData(history), history_key, strlen(history_key)) == 0) { found = TRUE; break; }
		}
		if (found) { strcpy(dst, history->cursorData(history)); dp += strlen(history->cursorData(history)); }
	}
	else if ((aliased = alias->find(alias, token.string)) != NULL)
	{	// check alias expand
		strcpy(dp, aliased);
		dp += strlen(aliased);
	}
	else
	{
		if (token.type == Dz1ShellCmdParseTokenType_singleCotate) *dp++ = '\'';
		else if (token.type == Dz1ShellCmdParseTokenType_doubleCotate) *dp++ = '\"';

		strcpy(dp, token.string);
		dp += strlen(token.string);

		if (token.type == Dz1ShellCmdParseTokenType_singleCotate) *dp++ = '\'';
		else if (token.type == Dz1ShellCmdParseTokenType_doubleCotate) *dp++ = '\"';
	}
	*dp++ = ' ';

	// after first token
	TRIM_WHITE_SPACE_A(cp);
	while(*cp)
	{
		if (*cp == '$')
		{
			Dz1Error status = DZ1_ERROR_INITIALIZER;
			MatchFinterArgA arg = { cp, NULL };
			if ((status = Dz1AATree_travel(env->tree, _match_finderA, (void *)&arg)).code == EEXIST)
			{
				Dz1ShellVarEntryA *result = arg.result;
				strcpy(dp, result->value); dp += strlen(result->value);
				cp++; // pass $
				cp += strlen(result->name);
			}
			else *dp++ = *cp++;
		}
		else
		{
			*dp++ = *cp++;
		}
	}
	*dp = '\0';

	return ret;
}

static Dz1ShellCmdReturn cmdExecuteA(Dz1ShellA *sh, bool_t push_history)
{
	Dz1ShellCmdReturn status = Dz1ShellCmdReturn_ok;
	if (!cmdExpandA(sh->history, sh->alias, sh->env, sh->buf, sh->input.buf)) return Dz1ShellCmdReturn_exit;
	else
	{
		Dz1ShellArgsA *args = NULL;
		sh->history->push(sh->history, sh->buf);
		if ((args = Dz1ShellArgsA_new(sh->buf, NULL)))
		{
			Dz1ShellCmdEntryA *e = NULL;
			pthread_cleanup_push((Dz1DelFunc)Dz1ShellArgsA_del, (void *)args);

			if ((e = sh->cmd->find(sh->cmd, args->argv[0])) == NULL) 
			{
				int i;
				for (i = 0; i < args->argc; i++)
					Dz1ThreadA_printf("%s ", args->argv[i]);
				Dz1ThreadA_printf(": not found\n");
				status = Dz1ShellCmdReturn_nocmd;
			}
			else status = Dz1ShellCmdEntryA_execute(e, args->argc, args->argv);

			pthread_cleanup_pop(1); // ((Dz1DelFunc_Dz1ShellArgs_del, (void *)args);
		}
	}
	return status;
}
#ifndef UNIX_SYSTEM
typedef struct CmdExpandArgW
{
	Dz1ShellVarW	*env;
	wstr_t			 dst;
	bool_t			 expandded;
} CmdExpandArgW;

static __inline__ Dz1Error _cmdExpandW(CmdExpandArgW *p, Dz1ShellParseToken type, wstr_t token)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	wstr_t expand = NULL;
	switch(type)
	{
		case Dz1ShellParseToken_doubleCotatedString:
			*p->dst++ = L'\"';
			if (Dz1ShellParseW(token, TRUE, FALSE, (Dz1ShellParseEmitFuncW)_cmdExpandW, (void *)p, &err) >= 0)
			{
				*p->dst++ = L'\"'; 
				*p->dst++ = L' ';
				*p->dst = 0;
			}
			break;
		case Dz1ShellParseToken_singleCotatedString:
			*p->dst++ = L'\'';
			wcscpy(p->dst, token);
			p->dst += wcslen(token);
			*p->dst++ = L'\'';
			*p->dst++ = L' ';
			*p->dst = 0;
			break;
		case Dz1ShellParseToken_word:
			wcscpy(p->dst, token);
			p->dst += wcslen(token);
			*p->dst++ = ' ';
			*p->dst = 0;
			break;
		case Dz1ShellParseToken_literal:
			if ((expand = p->env->find(p->env, token)))
			{
				wcscpy(p->dst, expand);
				p->dst += wcslen(expand);
				*p->dst++ = ' ';
				*p->dst = 0;
				p->expandded = TRUE;
			}
			break;
		default: break;
	}
	return err;
}

typedef struct Dz1ShellCmdParseTokenW
{
	Dz1ShellCmdParseTokenType		type;
	wchar_t							string[1024];
} Dz1ShellCmdParseTokenW;

#define TRIM_WHITE_SPACE_W(srcp)		do { while( *(srcp) != 0 && iswspace( (*srcp) & 0xFFFF)) (srcp)++; } while(0)
static wchar_t *_take_one_wordW(wstr_t src, Dz1ShellCmdParseTokenW *dst)
{
	wchar_t *cp = src;
	size_t size = wcslen(src);
	wchar_t *dp = dst->string;

	Dz1ShellCmdParseLetter letter;

	dst->type = Dz1ShellCmdParseTokenType_broken;
	*dp = 0;

	TRIM_WHITE_SPACE_W(cp);
	letter = _get_letter_typeW(cp, size);
	if (letter == Dz1ShellCmdParseLetter_singleCotate)
	{
		bool_t done = FALSE;
		cp++; size--;
		while(size && done == FALSE && (letter = _get_letter_typeW(cp, size)) != Dz1ShellCmdParseLetter_unknown)
		{
			switch(letter)
			{
			default:
			case Dz1ShellCmdParseLetter_cp949:
				*dp++ = *cp++; size--;
			case Dz1ShellCmdParseLetter_doubleCotate:
			case Dz1ShellCmdParseLetter_alnum:
				*dp++ = *cp++; size--;
				break;
			case Dz1ShellCmdParseLetter_singleCotate:
				cp++; size--;
				done = TRUE;
				break;
			}
		}
		if (done) dst->type = Dz1ShellCmdParseTokenType_singleCotate;
		else dst->type = Dz1ShellCmdParseTokenType_broken;
	}
	else if (letter == Dz1ShellCmdParseLetter_doubleCotate)
	{
		bool_t done = FALSE;
		cp++; size--;
		while(size && done == FALSE && (letter = _get_letter_typeW(cp, size)) != Dz1ShellCmdParseLetter_unknown)
		{
			switch(letter)
			{
			default:
			case Dz1ShellCmdParseLetter_cp949:
				*dp++ = *cp++; size--;
			case Dz1ShellCmdParseLetter_singleCotate:
			case Dz1ShellCmdParseLetter_alnum:
				*dp++ = *cp++; size--;
				break;
			case Dz1ShellCmdParseLetter_doubleCotate:
				cp++; size--;
				done = TRUE;
				break;
			}
		}
		if (done) dst->type = Dz1ShellCmdParseTokenType_doubleCotate;
		else dst->type = Dz1ShellCmdParseTokenType_broken;
	}
	else
	{
		bool_t broken = FALSE;
		while(broken == FALSE && (letter = _get_letter_typeW(cp, size)) != Dz1ShellCmdParseLetter_unknown)
		{
			switch(letter)
			{
			default:
			case Dz1ShellCmdParseLetter_cp949:
				*dp++ = *cp++; size--;
			case Dz1ShellCmdParseLetter_alnum:
				*dp++ = *cp++; size--;
				break;
			case Dz1ShellCmdParseLetter_singleCotate:
			case Dz1ShellCmdParseLetter_doubleCotate:
				broken = TRUE;
				break;
			}
		}

		if (broken) dst->type = Dz1ShellCmdParseTokenType_broken;
		else dst->type = Dz1ShellCmdParseTokenType_normal;
	}
	*dp++ = 0;
	return cp;
}

typedef struct MatchFinterArgW
{
	wchar_t				*src;
	Dz1ShellVarEntryW	*result;
} MatchFinterArgW;

static Dz1Error _match_finderW(void *ptr, void *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MatchFinterArgW *arg = (MatchFinterArgW *)ptr;
	Dz1ShellVarEntryW *p = (Dz1ShellVarEntryW *)data;
	if (wcsncmp(arg->src, p->name, wcslen(p->name)) == 0)
	{
		arg->result = p;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

static __inline__ bool_t cmdExpandW(Dz1ShellHistoryW *history, Dz1ShellVarW *alias, Dz1ShellVarW *env, wstr_t dst, wstr_t src)
{
	bool_t ret = TRUE;

	wchar_t *cp = src;
	wchar_t *dp = dst;
	Dz1ShellCmdParseTokenW token;

	wstr_t aliased = NULL;
	cp = _take_one_wordW(cp, &token);
	
	// first token
	if (token.string[0] == L'!')
	{	// check history expand
		bool_t found = FALSE;
		wstr_t history_key = &token.string[1];
		if (isDigitStringW(history_key))
		{
			int hisCount = history->count(history), pos = hisCount - (history->num - _wtoi(history_key));
			if (pos >= 0 && pos < hisCount)
			{
				for (history->cursorInit(history, Dz1FifoCursorPos_head); history->cursorCond(history); history->cursorNext(history, FALSE))
					if (pos-- == 0) { found = TRUE; break; }
			}
		}
		else
		{
			for (history->cursorInit(history, Dz1FifoCursorPos_tail); history->cursorCond(history); history->cursorPrev(history, FALSE))
				if (wcsncmp(history->cursorData(history), history_key, wcslen(history_key)) == 0) { found = TRUE; break; }
		}
		if (found) { wcscpy(dst, history->cursorData(history)); dp += wcslen(history->cursorData(history)); }
	}
	else if ((aliased = alias->find(alias, token.string)) != NULL)
	{	// check alias expand
		wcscpy(dp, aliased);
		dp += wcslen(aliased);
	}
	else
	{
		if (token.type == Dz1ShellCmdParseTokenType_singleCotate) *dp++ = L'\'';
		else if (token.type == Dz1ShellCmdParseTokenType_doubleCotate) *dp++ = L'\"';

		wcscpy(dp, token.string);
		dp += wcslen(token.string);

		if (token.type == Dz1ShellCmdParseTokenType_singleCotate) *dp++ = L'\'';
		else if (token.type == Dz1ShellCmdParseTokenType_doubleCotate) *dp++ = L'\"';
	}
	*dp++ = L' ';

	// after first token
	TRIM_WHITE_SPACE_W(cp);
	while(*cp)
	{
		if (*cp == L'$')
		{
			Dz1Error status = DZ1_ERROR_INITIALIZER;
			MatchFinterArgW arg = { cp, NULL };
			if ((status = Dz1AATree_travel(env->tree, _match_finderW, (void *)&arg)).code == EEXIST)
			{
				Dz1ShellVarEntryW *result = arg.result;
				wcscpy(dp, result->value); dp += wcslen(result->value);
				cp++; // pass $
				cp += wcslen(result->name);
			}
			else *dp++ = *cp++;
		}
		else
		{
			*dp++ = *cp++;
		}
	}
	*dp = 0;

	return ret;
}

static Dz1ShellCmdReturn cmdExecuteW(Dz1ShellW *sh, bool_t push_history)
{
	Dz1ShellCmdReturn status = Dz1ShellCmdReturn_ok;
	if (!cmdExpandW(sh->history, sh->alias, sh->env, sh->buf, sh->input.buf)) return Dz1ShellCmdReturn_exit;
	else
	{
		Dz1ShellArgsW *args = NULL;
		sh->history->push(sh->history, sh->buf);
		if ((args = Dz1ShellArgsW_new(sh->buf, NULL)))
		{
			Dz1ShellCmdEntryW *e = NULL;
			pthread_cleanup_push((Dz1DelFunc)Dz1ShellArgsW_del, (void *)args);

			if ((e = sh->cmd->find(sh->cmd, args->argv[0])) == NULL) 
			{
				Dz1ThreadW_printf(L"%s : not found\n", args->argv[0]);
				status = Dz1ShellCmdReturn_nocmd;
			}
			else status = Dz1ShellCmdEntryW_execute(e, args->argc, args->argv);

			pthread_cleanup_pop(1); // ((Dz1DelFunc_Dz1ShellArgs_del, (void *)args);
		}
	}
	return status;
}
#endif
// Dz1Shell Command Execute
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Shell Parse
static void lineClearA(str_t text, int prompt_len)
{
	int len = (int)(strlen(text) + prompt_len);
	int temp = len;
	while(temp--) Dz1ThreadA_printf("\b");

	temp = len;
	while(temp--) Dz1ThreadA_printf(" ");

	temp = len;
	while(temp--) Dz1ThreadA_printf("\b");
}

static bool_t isAnyLetterA(str_t src)
{
	while(*src)
	{
		if (!isspace((int)((*src++) & 0xFF))) 
			return TRUE;
	}
	return FALSE;
}

void Dz1ShellA_start(void *h, str_t rcFileName)
{
	bool_t halt = FALSE;
	Dz1ShellA *sh = (Dz1ShellA *)h;

	if (rcFileName && strlen(rcFileName))
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
		FILE *fp = Dz1FileStreamA_open(rcFileName, "rb", errp);
		if (fp == NULL) Dz1ThreadA_printf("%s(%d) : %s\n", Dz1ErrorStr(errp->code), errp->code, rcFileName);
		else
		{
			pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
			while(fgets(sh->input.buf, 65535, fp))
			{
				trimNewLineA(sh->input.buf);
				if (cmdExecuteA(sh, FALSE) == Dz1ShellCmdReturn_exit) { halt = TRUE; break; }
			}
			pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
		}
	}

	if (!halt)
	{
		int len = 0;
		// Dz1Error err = DZ1_ERROR_INITIALIZER;
		bool_t defStrReset = TRUE, hcInit = FALSE;
		//bool_t tabPressed = FALSE;
		str_t defStr = (str_t)Dz1Malloc(65535, NULL);
		if (defStr)
		{
			pthread_cleanup_push(Dz1Memory_cancel, (void *)defStr);
			do
			{
				Dz1ThreadA_printf("%s", Dz1ShellA_prompt(sh, &len));

				if (defStrReset) defStr[0] = '\0';
				defStrReset = TRUE;

				switch(Dz1ShellInputA_recv(&sh->input, defStr))
				{
					case Dz1ShellInputStatus_ok:
						if (strlen(sh->input.buf) && isAnyLetterA(sh->input.buf))
						{
//							if ((err = (sh->history->push(sh->history, sh->input.buf))).code) { Dz1Error_print(&err, 0); }
//							else
							{
								Dz1ShellCmdReturn status;
								hcInit = FALSE;
								if ((status = cmdExecuteA(sh, TRUE)) == Dz1ShellCmdReturn_exit) { halt = TRUE; }
								else if (status == Dz1ShellCmdReturn_nocmd) Dz1ThreadA_printf("No such command\n");
								else if (status == Dz1ShellCmdReturn_max) Dz1ThreadA_printf("Command Execution Error\n");
							}
						}
						break;
						// History Control
					case Dz1ShellInputStatus_up:
						lineClearA(sh->input.buf, len);
						if (!hcInit) { sh->history->cursorInit(sh->history, Dz1FifoCursorPos_tail); hcInit = TRUE; }
						else if (sh->history->isFull(sh->history))
							sh->history->cursorPrev(sh->history, FALSE);
						else if (sh->history->cursorCond(sh->history))
							sh->history->cursorPrev(sh->history, TRUE);

						if (sh->history->isFull(sh->history) || sh->history->cursorCond(sh->history))
							strcpy(defStr, sh->history->cursorData(sh->history));

						defStrReset = FALSE;
						break;
					case Dz1ShellInputStatus_down:
						lineClearA(sh->input.buf, len);
						if (hcInit && (sh->history->cursorCond(sh->history))) sh->history->cursorNext(sh->history, FALSE);

						if (sh->history->cursorCond(sh->history))
						{
							strcpy(defStr, sh->history->cursorData(sh->history));
							defStrReset = FALSE;
						}
						else hcInit = FALSE;
						break;
					case Dz1ShellInputStatus_pageUp:
						lineClearA(sh->input.buf, len);
						if (!hcInit) { sh->history->cursorInit(sh->history, Dz1FifoCursorPos_tail); hcInit = TRUE; }
						else if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);

						if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);
						if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);
						if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);
						if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);

						if (sh->history->cursorCond(sh->history))
						{
							strcpy(defStr, sh->history->cursorData(sh->history));
							defStrReset = FALSE;
						}
						break;
					case Dz1ShellInputStatus_pageDown:
						lineClearA(sh->input.buf, len);
						if (hcInit)
						{
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);

							if (sh->history->cursorCond(sh->history))
							{
								strcpy(defStr, sh->history->cursorData(sh->history));
								defStrReset = FALSE;
							}
							else hcInit = FALSE;
						}
						break;

					case Dz1ShellInputStatus_tab:
#if 0
						if (!tabPressed)
						{
							// strcpy(defStr, sh->input.buf);
							// str_t temp = getLastWord(defStr)
							// if (temp && (aliasList = findAlias(alias, temp)) || (cmdList = commandFind(cmd, temp)))
							// {
							// 		if (copyCommonPart(temp, aliasList, cmdList) != exeact)
							//			tabPressed = TRUE;
							// }
						}
						else
						{
							// strcpy(defStr, sh->input.buf);
							// str_t temp = getLastWord(defStr)
							// if (temp && (aliasList = findAlias(alias, temp)) || (cmdList = commandFind(cmd, temp)))
							// 	listPrint(aliasList, cmdList);
						}
#else
						strcpy(defStr, sh->input.buf);
#endif
						Dz1ThreadA_printf("\n");
						defStrReset = FALSE;
						break;
					case Dz1ShellInputStatus_notSupport:
					case Dz1ShellInputStatus_esc:
					default:
						break;
				}
			} while(!halt);

			pthread_cleanup_pop(1); // (Dz1Memory_clean, (void *)defStr);
		}
	}
}
#ifndef UNIX_SYSTEM
static void lineClearW(wstr_t text, int prompt_len)
{
	int len = (int)(wcslen(text) + prompt_len);
	int temp = len;
	while(temp--) Dz1ThreadW_printf(L"\b");

	temp = len;
	while(temp--) Dz1ThreadW_printf(L" ");

	temp = len;
	while(temp--) Dz1ThreadW_printf(L"\b");
}

static bool_t isAnyLetterW(wstr_t src)
{
	while(*src)
	{
		if (!iswspace((int)((*src++) & 0xFFFF))) 
			return TRUE;
	}
	return FALSE;
}

void Dz1ShellW_start(void *h, wstr_t rcFileName)
{
	bool_t halt = FALSE;
	Dz1ShellW *sh = (Dz1ShellW *)h;

	if (rcFileName && wcslen(rcFileName))
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		FILE *fp = Dz1FileStreamW_open(rcFileName, L"rb", errp);
		if (fp == NULL) 
			Dz1Thread_eprintf("%s(%d)\n", Dz1ErrorStr(errp->code), errp->code);
		else
		{
			pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
			while(fgetws(sh->input.buf, DZ1_SHELL_INPUT_BUF_SIZE, fp))
			{
				trimNewLineW(sh->input.buf);
				if (cmdExecuteW(sh, FALSE) == Dz1ShellCmdReturn_exit) { halt = TRUE; break; }
			}
			pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
		}
	}

	if (!halt)
	{
		int len = 0;
		// Dz1Error err = DZ1_ERROR_INITIALIZER;
		bool_t defStrReset = TRUE, hcInit = FALSE;
		//bool_t tabPressed = FALSE;
		wstr_t defStr = (wstr_t)Dz1Malloc(DZ1_SHELL_INPUT_BUF_SIZE, NULL);
		if (defStr)
		{
			pthread_cleanup_push(Dz1Memory_cancel, (void *)defStr);
			do
			{
				Dz1ThreadW_printf(L"%s", Dz1ShellW_prompt(sh, &len));

				if (defStrReset) defStr[0] = 0;
				defStrReset = TRUE;

				switch(Dz1ShellInputW_recv(&sh->input, defStr))
				{
					case Dz1ShellInputStatus_ok:
						if (wcslen(sh->input.buf) && isAnyLetterW(sh->input.buf))
						{
							Dz1ShellCmdReturn status;
							hcInit = FALSE;
							if ((status = cmdExecuteW(sh, TRUE)) == Dz1ShellCmdReturn_exit) { halt = TRUE; }
							else if (status == Dz1ShellCmdReturn_nocmd) Dz1ThreadW_printf(L"No such command\n");
							else if (status == Dz1ShellCmdReturn_max) Dz1ThreadW_printf(L"Command Execution Error\n");
						}
						break;
						// History Control
					case Dz1ShellInputStatus_up:
						lineClearW(sh->input.buf, len);
						if (!hcInit) { sh->history->cursorInit(sh->history, Dz1FifoCursorPos_tail); hcInit = TRUE; }
						else if (sh->history->isFull(sh->history))
							sh->history->cursorPrev(sh->history, FALSE);
						else if (sh->history->cursorCond(sh->history))
							sh->history->cursorPrev(sh->history, TRUE);

						if (sh->history->isFull(sh->history) || sh->history->cursorCond(sh->history))
							wcscpy(defStr, sh->history->cursorData(sh->history));

						defStrReset = FALSE;
						break;
					case Dz1ShellInputStatus_down:
						lineClearW(sh->input.buf, len);
						if (hcInit && (sh->history->cursorCond(sh->history))) sh->history->cursorNext(sh->history, FALSE);

						if (sh->history->cursorCond(sh->history))
						{
							wcscpy(defStr, sh->history->cursorData(sh->history));
							defStrReset = FALSE;
						}
						else hcInit = FALSE;
						break;
					case Dz1ShellInputStatus_pageUp:
						lineClearW(sh->input.buf, len);
						if (!hcInit) { sh->history->cursorInit(sh->history, Dz1FifoCursorPos_tail); hcInit = TRUE; }
						else if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);

						if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);
						if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);
						if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);
						if (sh->history->cursorCond(sh->history)) sh->history->cursorPrev(sh->history, TRUE);

						if (sh->history->cursorCond(sh->history))
						{
							wcscpy(defStr, sh->history->cursorData(sh->history));
							defStrReset = FALSE;
						}
						break;
					case Dz1ShellInputStatus_pageDown:
						lineClearW(sh->input.buf, len);
						if (hcInit)
						{
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);
							if (sh->history->cursorCond(sh->history)) sh->history->cursorNext(sh->history, FALSE);

							if (sh->history->cursorCond(sh->history))
							{
								wcscpy(defStr, sh->history->cursorData(sh->history));
								defStrReset = FALSE;
							}
							else hcInit = FALSE;
						}
						break;

					case Dz1ShellInputStatus_tab:
						wcscpy(defStr, sh->input.buf);
						Dz1ThreadW_printf(L"\n");
						defStrReset = FALSE;
						break;
					case Dz1ShellInputStatus_notSupport:
					case Dz1ShellInputStatus_esc:
					default:
						break;
				}
			} while(!halt);

			pthread_cleanup_pop(1); // (Dz1Memory_clean, (void *)defStr);
		}
	}
}
#endif
// Dz1Shell Parse
///////////////////////////////////////////////////////////////////////////////
