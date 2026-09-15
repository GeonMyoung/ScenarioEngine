#include <dz1_time.h>
#include "dz1_thread.h"
#include "dz1_console_tty_platform.h"
#include "dz1_console.h"

#ifndef UNIX_SYSTEM
#include <io.h>
#include <conio.h>

static OutputHook outputHook = NULL;
static void *outputHookParam = NULL;

void Dz1OutputHook_set(OutputHook func, void *param)
{
	outputHook = func;
	outputHookParam = param;
}

typedef struct Dz1ConsolePlatformWin32CrtPriv
{
	int con_in;
	int con_out;
} Dz1ConsolePlatformWin32CrtPriv;

static void Dz1ConsolePlatformWin32CrtPriv_del(Dz1ConsolePlatformWin32CrtPriv *p)
{
	if (!p) return;
	free(p);
}

static void Dz1ConsolePlatformWin32CrtPriv_delAndSetNull(void *ptr)
{
	Dz1ConsolePlatformWin32CrtPriv **p = (Dz1ConsolePlatformWin32CrtPriv **)ptr;
	Dz1ConsolePlatformWin32CrtPriv_del(*p); *p = NULL;
}

static Dz1ConsolePlatformWin32CrtPriv *Dz1ConsolePlatformWin32CrtPriv_new(Dz1FileDescr con_in, Dz1FileDescr con_out, Dz1Error *errp)
{
	Dz1ConsolePlatformWin32CrtPriv *ret = (Dz1ConsolePlatformWin32CrtPriv *)calloc(sizeof(Dz1ConsolePlatformWin32CrtPriv), 1);
	if (ret == NULL) Dz1Error_set(errp, ENOMEM);
	else
	{
		ret->con_in = ret->con_out = -1;
		pthread_cleanup_push(Dz1ConsolePlatformWin32CrtPriv_delAndSetNull, (void *)&ret);

		Dz1Error_set(errp, 0);
		if (errp->code == 0 && con_in >= 0)
		{
#ifdef __BORLANDC__
			ret->con_in = con_in;
#else
			ret->con_in = _dup(con_in);
#endif
			if (ret->con_in < 0) Dz1Error_set(errp, errno);
		}

		if (errp->code == 0 && con_out >= 0)
		{
#ifdef __BORLANDC__
			ret->con_out = con_out;
#else
			ret->con_out = _dup(con_out);
#endif
			if (ret->con_out < 0) Dz1Error_set(errp, errno);
		}


		pthread_cleanup_pop(errp->code); // (Dz1ConsolePlatformWin32CrtPriv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static bool_t _Dz1ConsolePlatformWin32Crt_wait(void *ptr, Dz1ThreadIODir flag, s32_t wait_us, Dz1Error *errp)
{
	int t;
	if (flag == Dz1ThreadIODir_out) Dz1Error_set(errp, 0);
	else
	{	// Dz1ThreadIODir_in
		if (wait_us < 0)
		{
			while(1)
			{
				pthread_testcancel();
				if ((t = _kbhit()) != 0)
				{
					Dz1Error_set(errp, 0);
					break;
				}
			}
		}
		else
		{
			u32_t bias, now;
			Dz1Time_getMonotonic(&bias);
			while(1)
			{
				pthread_testcancel();
				if ((t = _kbhit()) == 0)
				{
					Sleep(1);
					Dz1Time_getMonotonic(&now);
					if (now - bias > (u32_t)wait_us)
					{
						Dz1Error_set(errp, ETIMEDOUT);
						break;
					}
				}
				else { Dz1Error_set(errp, 0); break; }
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}
static Dz1Error Dz1ConsolePlatformWin32Crt_wait(void *ptr, Dz1ThreadIODir flag, s32_t wait_us)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	_Dz1ConsolePlatformWin32Crt_wait(ptr, flag, wait_us, errp);
	return err;
}

int Dz1ConsolePlatformWin32Crt_getch(void *ptr, s32_t wait_us, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ConsolePlatformWin32CrtPriv *priv = (Dz1ConsolePlatformWin32CrtPriv *)ptr;

	wait_us = wait_us == 0 ? -1 : wait_us;

	if (_Dz1ConsolePlatformWin32Crt_wait(ptr, Dz1ThreadIODir_in, wait_us, errp) == FALSE) return -1;
	else
	{
#ifdef __BORLANDC__
		int c = _getch();
#else
		int c = dz1DefCon_getMode() == Dz1ConsoleMode_wide ? _getwch() : _getch();
#endif
		if (c == '\r') c = '\n';

		return c;
	}
}

ssize_t Dz1ConsolePlatformWin32Crt_write(void *ptr, u8_t *buf, size_t size, s32_t wait_us, Dz1Error *errp)
{
	Dz1ConsolePlatformWin32CrtPriv *priv = (Dz1ConsolePlatformWin32CrtPriv *)ptr;
	if (priv->con_out >= 0)	_write(priv->con_out, (const void *)buf, (u32_t)size);
	if (outputHook != NULL) outputHook(outputHookParam, buf, size);
	return (ssize_t)size;
}

Dz1Console *Dz1ConsoleTTY_new(Dz1FileDescr con_in, Dz1FileDescr con_out, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Console *ret = Dz1Console_new(Dz1ConsolePromptMode_longTime, NULL, errp);
	if (ret == NULL) { }
	else
	{
		Dz1ConsolePlatform *pf = NULL;
		Dz1ConsolePlatformWin32CrtPriv *priv = NULL;
		pthread_cleanup_push(Dz1Console_delAndSetNull, (void *)&ret);

		if ((ret->platform = pf = Dz1ConsolePlatform_new(NULL, 
														 (Dz1DelFunc)Dz1ConsolePlatformWin32CrtPriv_del, 
														 Dz1ConsolePlatformWin32Crt_wait, 
														 Dz1ConsolePlatformWin32Crt_getch, 
														 Dz1ConsolePlatformWin32Crt_write, errp)) == NULL) { }
		else if ((pf->priv = Dz1ConsolePlatformWin32CrtPriv_new(con_in, con_out, errp)) == NULL) { }
		else
		{
//			ret->cr = Dz1ConsoleCR_CRLF;
			ret->cr = Dz1ConsoleCR_CR;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1Console_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1ConsoleTTY_sizeTraceOn(struct Dz1Console *con)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	return err;
}

void Dz1ConsoleTTY_sizeTraceOff(struct Dz1Console *con)
{
}
#else
u32_t __no_symbol_warning_avoid__()
{
	return 0;
}
#endif
