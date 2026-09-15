#include <dz1_time.h>
#include "dz1_console_prompt.h"

static int isValidPromptMode(Dz1ConsolePromptMode mode)
{
	switch(mode)
	{
		case Dz1ConsolePromptMode_longTime:
		case Dz1ConsolePromptMode_shortTime:
		case Dz1ConsolePromptMode_userSpecific:
			return TRUE;
		default:
			return FALSE;
	}
}

void Dz1ConsolePrompt_init(Dz1ConsolePrompt *p)
{
	if (p)
	{
		Dz1ConsolePrompt temp = Dz1ConsolePromptInitializer;

		memcpy(p, &temp, sizeof(Dz1ConsolePrompt));
	}
}

Dz1Error Dz1ConsolePrompt_set(Dz1ConsolePrompt *p, Dz1ConsolePromptMode mode, Dz1ConsolePromptFunc func, void *userPtr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (p == NULL) Dz1Error_set(&err, EINVAL);
	else if (!isValidPromptMode(mode)) Dz1Error_set(&err, EINVAL);
	else if (mode == Dz1ConsolePromptMode_userSpecific && !func) Dz1Error_set(&err, EINVAL);
	else
	{
		if (p->mode != mode) p->lastBuilt = 0;
		p->mode = mode;

		if (p->mode == Dz1ConsolePromptMode_userSpecific)
		{
			p->func = func;
			p->userPtr = userPtr;
		}
		else
		{
			p->func = NULL;
			p->userPtr = NULL;
		}
	}

	return err;
}

static void mkLongTimePromptA(Dz1ConsolePrompt *p)
{
	struct timeval tv = Dz1GetTimeval();
	//time_t t = time(NULL);
	time_t t = (time_t)tv.tv_sec;
	u32_t msec = (u32_t)(tv.tv_usec / 1000);
	if (p->lastBuilt != t)
	{
		struct tm *tmp = localtime(&t), tm = *tmp;
		snprintf((char *)p->buf, 63, "[%04d-%02d-%02d %02d:%02d:%02d.%03u] ",
				tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
				tm.tm_hour, tm.tm_min, tm.tm_sec, msec);
		p->lastBuilt = t;
	}
}

static void mkShortTimePromptA(Dz1ConsolePrompt *p)
{
	time_t t = time(NULL);
	if (p->lastBuilt != t)
	{
		struct tm *tmp = localtime(&t), tm = *tmp;
		snprintf((char *)p->buf, 63, "[%02d:%02d:%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec);
		p->lastBuilt = t;
	}
}

str_t Dz1ConsolePromptA_get(Dz1ConsolePrompt *p)
{
	switch(p->mode)
	{
		case Dz1ConsolePromptMode_longTime:
			mkLongTimePromptA(p);
			break;
		case Dz1ConsolePromptMode_shortTime:
			mkShortTimePromptA(p);
			break;
		default:
		case Dz1ConsolePromptMode_userSpecific:
			{
				Dz1Error err = DZ1_ERROR_INITIALIZER;
				if (p->func == NULL || (err = p->func(p->userPtr, p->buf)).code != 0) p->buf[0] = 0;
			}
			break;
	}
	return (str_t)p->buf;
}

#ifndef UNIX_SYSTEM
static void mkLongTimePromptW(Dz1ConsolePrompt *p)
{
	struct timeval tv = Dz1GetTimeval();
	//time_t t = time(NULL);
	time_t t = (time_t)tv.tv_sec;
	u32_t msec = (u32_t)(tv.tv_usec / 1000);
	if (p->lastBuilt != t)
	{
		struct tm *tmp = localtime(&t), tm = *tmp;
		swprintf((wchar_t *)p->buf, 31, L"[%04d-%02d-%02d %02d:%02d:%02d.%03u] ",
				tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
				tm.tm_hour, tm.tm_min, tm.tm_sec, msec);
		p->lastBuilt = t;
	}
}

static void mkShortTimePromptW(Dz1ConsolePrompt *p)
{
	time_t t = time(NULL);
	if (p->lastBuilt != t)
	{
		struct tm *tmp = localtime(&t), tm = *tmp;
		swprintf((wchar_t *)p->buf, 31, L"[%02d:%02d:%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec);
		p->lastBuilt = t;
	}
}

wstr_t Dz1ConsolePromptW_get(Dz1ConsolePrompt *p)
{
	switch(p->mode)
	{
		case Dz1ConsolePromptMode_longTime:
			mkLongTimePromptW(p);
			break;
		case Dz1ConsolePromptMode_shortTime:
			mkShortTimePromptW(p);
			break;
		default:
		case Dz1ConsolePromptMode_userSpecific:
			{
				Dz1Error err = DZ1_ERROR_INITIALIZER;
				if (p->func == NULL || (err = p->func(p->userPtr, p->buf)).code != 0) { p->buf[0] = 0; p->buf[1] = 0; }
			}
			break;
	}
	return (wstr_t)p->buf;
}
#endif
