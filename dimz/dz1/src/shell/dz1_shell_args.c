#include <ctype.h>
#include <dz1_malloc.h>
#include <dz1_str.h>
#include <dz1_thread_stdio.h>

#include "dz1_shell.h"
#include "dz1_shell_parse.h"
#include "dz1_shell_args.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1ShellArgs parse
typedef struct Dz1ShellParseArgA
{
	str_t *argv;
	str_t dp;
} Dz1ShellParseArgA;

static Dz1Error Dz1ShellArgsA_argc(void *p, Dz1ShellParseToken type, str_t token)
{
	int *argc = (int *)p;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	(*argc)++;
	//Dz1Console_printf(NULL, 0, "%d\n", *argc);
	return err;
}

static Dz1Error Dz1ShellArgsA_parse(void *ptr, Dz1ShellParseToken type, str_t token)
{
	Dz1ShellParseArgA *p = (Dz1ShellParseArgA *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	*p->argv = p->dp; p->argv++;
	strcpy(p->dp, token);
	//Dz1Console_printf(NULL, 0, "[%s]\n", p->dp);
	p->dp += strlen(token) + 1;

	return err;
}
#ifndef UNIX_SYSTEM
typedef struct Dz1ShellParseArgW
{
	wstr_t	*argv;
	wstr_t	 dp;
} Dz1ShellParseArgW;

static Dz1Error Dz1ShellArgsW_argc(void *p, Dz1ShellParseToken type, wstr_t token)
{
	int *argc = (int *)p;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	(*argc)++;
	//Dz1Console_printf(NULL, 0, "%d\n", *argc);
	return err;
}

static Dz1Error Dz1ShellArgsW_parse(void *ptr, Dz1ShellParseToken type, wstr_t token)
{
	Dz1ShellParseArgW *p = (Dz1ShellParseArgW *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	*p->argv = p->dp; p->argv++;
	wcscpy(p->dp, token);
	//Dz1Console_printf(NULL, 0, "[%s]\n", p->dp);
	p->dp += wcslen(token) + 1;

	return err;
}
#endif
// Dz1ShellArgs parse
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1ShellArgs
Dz1ShellArgsA *Dz1ShellArgsA_new(str_t text, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellArgsA *ret = (Dz1ShellArgsA *)Dz1Malloc(sizeof(Dz1ShellArgsA), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellArgsA));
		pthread_cleanup_push(Dz1ShellArgsA_delAndSetNull, (void *)&ret);
		if ((ret->buf = (str_t)Dz1Malloc(strlen(text) + 1, errp)))
		{
			if (Dz1ShellParseA(text, FALSE, FALSE, Dz1ShellArgsA_argc, (void *)&ret->argc, errp) < 0) { }
			else if ((ret->argv = (str_t *)Dz1Malloc(sizeof(str_t) * ret->argc, errp)))
			{
				Dz1ShellParseArgA arg;
				arg.argv = ret->argv;
				arg.dp = ret->buf;
				Dz1ShellParseA(text, FALSE, FALSE, (Dz1ShellParseEmitFuncA)Dz1ShellArgsA_parse, (void *)&arg, errp);
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1ShellArgs_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ShellArgsA_del(Dz1ShellArgsA *p)
{
	if (!p) return;
	if (p->argv) Dz1Free(p->argv);
	if (p->buf) Dz1Free(p->buf);
	Dz1Free(p);
}

void Dz1ShellArgsA_dump(Dz1ShellArgsA *p, int tab)
{
	int i;
	char buf[32];
	if (!p) return;
	sprintf(buf, "%d", p->argc + 1);
	sprintf(buf, "[%%0%dd][%%s]\n", (int)strlen(buf));
	for (i = 0; i < p->argc; i++)
		Dz1ThreadA_tprintf(tab, buf, i + 1, p->argv[i]);
}
#ifndef UNIX_SYSTEM
Dz1ShellArgsW *Dz1ShellArgsW_new(wstr_t text, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellArgsW *ret = (Dz1ShellArgsW *)Dz1Malloc(sizeof(Dz1ShellArgsW), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellArgsW));
		pthread_cleanup_push(Dz1ShellArgsW_delAndSetNull, (void *)&ret);
		if ((ret->buf = (wstr_t)Dz1Malloc((wcslen(text) + 1) * sizeof(wchar_t), errp)))
		{
			if (Dz1ShellParseW(text, FALSE, FALSE, Dz1ShellArgsW_argc, (void *)&ret->argc, errp) < 0) { }
			else if ((ret->argv = (wstr_t *)Dz1Malloc(sizeof(wstr_t) * ret->argc, errp)))
			{
				Dz1ShellParseArgW arg;
				arg.argv = ret->argv;
				arg.dp = ret->buf;
				Dz1ShellParseW(text, FALSE, FALSE, (Dz1ShellParseEmitFuncW)Dz1ShellArgsW_parse, (void *)&arg, errp);
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1ShellArgs_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ShellArgsW_del(Dz1ShellArgsW *p)
{
	if (!p) return;
	if (p->argv) Dz1Free(p->argv);
	if (p->buf) Dz1Free(p->buf);
	Dz1Free(p);
}

void Dz1ShellArgsW_dump(Dz1ShellArgsW *p, int tab)
{
	int i;
	wchar_t buf[32];
	if (!p) return;
	swprintf(buf, 32, L"%d", p->argc + 1);
	swprintf(buf, 32, L"[%%0%dd][%%s]\n", (int)wcslen(buf));
	for (i = 0; i < p->argc; i++)
		Dz1ThreadW_tprintf(tab, buf, i + 1, p->argv[i]);
}
#endif
// Dz1ShellArgs
///////////////////////////////////////////////////////////////////////////////
