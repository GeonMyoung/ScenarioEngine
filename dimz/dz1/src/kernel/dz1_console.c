#include <codeconv.h>
#include <dz1_malloc.h>
#include "dz1_thread.h"
#include "dz1_console.h"

///////////////////////////////////////////////////////////////////////////////
// Basic
//Dz1Console *Dz1Console_new(Dz1ConsolePlatform *platform, Dz1ConsolePlatformDelFunc platformDel, Dz1Error *err)
Dz1Console *Dz1Console_new(Dz1ConsolePromptMode prompt, Dz1ConsolePlatform *platform, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Console *ret = (Dz1Console *)calloc(sizeof(Dz1Console), 1);
	if (ret == NULL) Dz1Error_set(errp, ENOMEM);
	else
	{
		pthread_cleanup_push(Dz1Console_delAndSetNull, (void *)&ret);

		Dz1ConsolePrompt_init(&ret->prompt);
		ret->prompt.mode = prompt;

		ret->width = 80;
		ret->height = 25;
		ret->cr = Dz1ConsoleCR_CR;
		ret->col = 0;

		ret->platform = platform;
//		ret->platformDel = platformDel;

		ret->cr_output = TRUE;

		pthread_mutex_init(&ret->lockIn, NULL);
		pthread_mutex_init(&ret->lockOut, NULL);

		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Console_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Console_del(Dz1Console *con)
{
	if (!con) return;
//	if (con->platformDel) con->platformDel(con->platform);
	if (con->platform) Dz1ConsolePlatform_del(con->platform);
	pthread_mutex_destroy(&con->lockIn);
	pthread_mutex_destroy(&con->lockOut);
	free(con);
}
// Basic
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// APIs
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1Console_wait(Dz1Console *con, Dz1ThreadIODir flag, s32_t wait_us)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (con == NULL) Dz1Error_set(&err, EINVAL);
	else
	{
		switch(flag)
		{
			case Dz1ThreadIODir_in:
				pthread_mutex_lock(&con->lockIn);
				pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockIn);

				err = con->platform->wait(con->platform->priv, flag, wait_us);

				pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockIn);
				break;
			case Dz1ThreadIODir_out:
				pthread_mutex_lock(&con->lockOut);
				pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

				err = con->platform->wait(con->platform->priv, flag, wait_us);

				pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);
				break;
			default:
				break;
		}
	}
	return err;
}


// ssize_t Dz1Console_read(Dz1Console *con, u8_t *buf, size_t size, s32_t wait_us, Dz1Error *err)
// {
// 	ssize_t ret = -1;
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	if (con == NULL) Dz1Error_set(errp, EINVAL);
// 	else if (!buf || !size) Dz1Error_set(errp, EINVAL);
// 	else
// 	{
// 		pthread_mutex_lock(&con->lockIn);
// 		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockIn);
// 
// 		ret = con->platform->read(con->platform->priv, buf, size, wait_us, errp);
// 
// 		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockIn);
// 	}
// 	return ret;
// }

int Dz1Console_getch(Dz1Console *con, s32_t wait_us, Dz1Error *err)
{
	int ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (con == NULL) Dz1Error_set(errp, EINVAL);
	else
	{
		pthread_mutex_lock(&con->lockIn);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockIn);

		ret = con->platform->getch(con->platform->priv, wait_us, errp);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockIn);
	}
	return ret;
}

ssize_t Dz1Console_write(Dz1Console *con, u8_t *buf, size_t size, s32_t wait_us, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (con == NULL) Dz1Error_set(errp, EINVAL);
	else if (!buf || !size) Dz1Error_set(errp, EINVAL);
	else
	{
		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		ret = con->platform->write(con->platform->priv, buf, size, wait_us, errp);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);
	}
	return ret;
}

static ssize_t _Dz1ConsoleA_writeText(Dz1Console *con, str_t prompt, size_t promptLen, int tab, char *data, size_t size, Dz1Error *err);
ssize_t Dz1ConsoleA_writeText(Dz1Console *con, char *buf, size_t len, int tab)
{
	ssize_t ret = -1;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (con)
	{
		char *prompt = NULL;

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		prompt = Dz1ConsolePromptA_get(&con->prompt);

		ret = _Dz1ConsoleA_writeText(con, prompt, prompt ? strlen(prompt) : 0, tab, buf, len, &err);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);
	}

	return ret;
}

#ifndef UNIX_SYSTEM
static ssize_t _Dz1ConsoleW_writeText(Dz1Console *con, wstr_t prompt, size_t promptLen, int tab, wchar_t *data, size_t len, Dz1Error *err);
ssize_t Dz1ConsoleW_writeText(Dz1Console *con, wchar_t *buf, size_t len, int tab)
{
	ssize_t ret = -1;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (con)
	{
		wchar_t *prompt = NULL;

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		prompt = Dz1ConsolePromptW_get(&con->prompt);

		ret = _Dz1ConsoleW_writeText(con, prompt, prompt ? wcslen(prompt) : 0, tab, buf, len, &err);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);
	}

	return ret;
}
#endif

static bool_t sureWrite(Dz1Console *con, void *data, size_t size, Dz1Error *err)
{
	ssize_t write_size;
	unsigned char *dp = (unsigned char *)data;
	while(size)
	{
		if ((write_size = con->platform->write(con->platform->priv, dp, size, -1, err)) < 0) return FALSE;
		else { dp += write_size; size -= write_size; }
	}
	return TRUE;
}

#define conpush(con, dp, chunk, size, errp) \
	({\
		if ((size = dp - chunk) >= 1024)\
		{\
			if (sureWrite(con, chunk, size, errp) == TRUE) dp = chunk;\
	 		else size = -1;\
		}\
	 	else size = 0;\
	 	size; \
	 })

#define conflush(con, dp, chunk, size, errp) \
	({\
		if ((size = dp - chunk))\
		{\
			if (sureWrite(con, chunk, size, errp) == TRUE) dp = chunk;\
	 		else size = -1;\
		}\
	 	size; \
	 })


static str_t tab_str_A = (str_t)DZ1_TAB_STR_A DZ1_TAB_STR_A DZ1_TAB_STR_A DZ1_TAB_STR_A;
static ssize_t tab4size = (DZ1_TAB_STR_LEN << 2);
static ssize_t tab3size = (DZ1_TAB_STR_LEN << 1) + DZ1_TAB_STR_LEN;
static ssize_t tab2size = (DZ1_TAB_STR_LEN << 1);
static ssize_t tab1size = DZ1_TAB_STR_LEN;
#ifndef UNIX_SYSTEM
#endif

#define OUTPUT_BUFFER_SIZE		(1024 + DZ1_ALIGNED_SIZE(32) + 10)
typedef struct OutputBuffer
{
	Dz1Console *console;
	size_t pos;
	u8_t buf[OUTPUT_BUFFER_SIZE];
} OutputBuffer;

static ssize_t _push_to_buffer(OutputBuffer *dst, u8_t *src, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = -1;
	if (size >= OUTPUT_BUFFER_SIZE) Dz1Error_set(errp, E2BIG);
	else
	{
		size_t remain_len = OUTPUT_BUFFER_SIZE - dst->pos;
		if (remain_len < size)
		{
			if (sureWrite(dst->console, dst->buf, dst->pos, errp) == FALSE) return -1;
			else dst->pos = 0;
		}
		memcpy(&dst->buf[dst->pos], src, size);
		dst->pos += size;
		ret = (ssize_t)size;
	}
	return ret;
}

static ssize_t _flush_buffer(OutputBuffer *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst->pos > 0)
	{
		if (sureWrite(dst->console, dst->buf, dst->pos, errp) == FALSE) return -1;
		else
		{
			ret = (ssize_t)dst->pos;
			dst->pos = 0;
		}
	}
	return ret;
}

static ssize_t _push_to_bufferA_tab(OutputBuffer *dst, int tab_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0, sz;
	while(tab_cnt >= 4)
	{
		if ((sz = _push_to_buffer(dst, (u8_t *)tab_str_A, tab4size, errp)) < 0) return -1;
		else { ret += sz; tab_cnt -= 4; }
	}
	switch(tab_cnt)
	{
	case 3:
		if ((sz = _push_to_buffer(dst, (u8_t *)tab_str_A, tab3size, errp)) < 0) return -1;
		else { ret += sz; tab_cnt -= 3; }
		break;
	case 2:
		if ((sz = _push_to_buffer(dst, (u8_t *)tab_str_A, tab2size, errp)) < 0) return -1;
		else { ret += sz; tab_cnt -= 2; }
		break;
	case 1:
		if ((sz = _push_to_buffer(dst, (u8_t *)tab_str_A, tab1size, errp)) < 0) return -1;
		else { ret += sz; tab_cnt -= 1; }
		break;
	default: break;
	}
	return ret;
}

static ssize_t _push_promptA(OutputBuffer *buf, str_t prompt, size_t promptLen, Dz1Error *errp)
{
	ssize_t sz, ret = 0;
	if (promptLen)
	{	// print prompt
		if ((sz = _push_to_buffer(buf, (u8_t *)prompt, promptLen, errp)) < 0) return -1;
		else ret += sz;
	}
	return ret;
}

static ssize_t _Dz1ConsoleA_writeText(Dz1Console *con, str_t prompt, size_t promptLen, int tab, char *data, size_t size, Dz1Error *err)
{	// 매 개행을 만날때 마다 tab많큼 띄우고 출력
	DZ1_ERROR_SAFE_PTR(errp, err);
	char *cp = data;
	ssize_t ret = 0; //  push_size = 0;
	// char chunk[1024 + DZ1_ALIGNED_SIZE(32) + 10 ], *dp = chunk;

	ssize_t sz = 0;
	OutputBuffer buf = { NULL, 0 };
	buf.console = con;

	while(size > 0)
	{
		if (*cp == '\r')
		{	// Ignore LF
			cp++; size--; continue;
		}
		else if (*cp == '\n')
		{	// CR :: out prompt, tab and put cr
			if (con->cr_output)
			{	// 이전 출력이 \n 으로 끝난 경우
				if ((sz = _push_promptA(&buf, prompt, promptLen, errp)) < 0) return -1; else ret += sz;
				con->cr_output = FALSE;
			}
			// Print New Line
			switch(con->cr)
			{
			case Dz1ConsoleCR_CRLF: if ((sz = _push_to_buffer(&buf, (u8_t *)"\r\n",	2, errp)) < 0) return -1; else ret += sz; break;
			default:				if ((sz = _push_to_buffer(&buf, (u8_t *)"\n",	1, errp)) < 0) return -1; else ret += sz; break;
			}
			con->col = 0;
			
			if (size > 1)	// include CR
			{	// 출력할 것이 남았다
				if ((sz = _push_promptA(&buf, prompt, promptLen, errp)) < 0) return -1; else ret += sz;
				// print TAB
				if ((sz = _push_to_bufferA_tab(&buf, tab, errp)) < 0) return -1; else { ret += sz; con->col += (int)(tab * DZ1_TAB_STR_LEN); }
			}
			else con->cr_output = TRUE;
		}
		else
		{	// Other Letters
			if (con->cr_output)
			{	// 이전 출력이 \n 으로 끝난 경우
				if ((sz = _push_promptA(&buf, prompt, promptLen, errp)) < 0) return -1; else ret += sz;
				// print TAB
				if ((sz = _push_to_bufferA_tab(&buf, tab, errp)) < 0) return -1; else { ret += sz; con->col += (int)(tab * DZ1_TAB_STR_LEN); }
				con->cr_output = FALSE;
			}

			if (*cp == '\t')
			{
				ssize_t len = DZ1_TAB_STR_LEN - (con->col % DZ1_TAB_STR_LEN);
				if ((sz = _push_to_buffer(&buf, (u8_t *)tab_str_A, len, errp)) < 0) return -1; else { ret += sz; con->col += (int)len; }
			}
			else if ((sz = _push_to_buffer(&buf, (u8_t *)cp, 1, errp)) < 0) return -1; else { ret += sz; con->col++; }
		}
		cp++; size--;
	}
	_flush_buffer(&buf, errp);
	return ret;
}

#ifndef UNIX_SYSTEM
#define DZ1_TAB_STR_W_SZ		(DZ1_TAB_STR_LEN * sizeof(wchar_t))
static wstr_t  tab_str_W	= (wstr_t)DZ1_TAB_STR_W DZ1_TAB_STR_W DZ1_TAB_STR_W DZ1_TAB_STR_W;

static ssize_t tab4w_len	= (DZ1_TAB_STR_LEN * 4);
static ssize_t tab4w_sz		= (DZ1_TAB_STR_W_SZ * 4);

static ssize_t tab3w_len	= (DZ1_TAB_STR_LEN * 3);
static ssize_t tab3w_sz		= (DZ1_TAB_STR_W_SZ * 3);

static ssize_t tab2w_len	= (DZ1_TAB_STR_LEN * 2);
static ssize_t tab2w_sz		= (DZ1_TAB_STR_W_SZ * 2);

static ssize_t tab1w_len	= (DZ1_TAB_STR_LEN * 1);
static ssize_t tab1w_sz		= (DZ1_TAB_STR_W_SZ * 1);

// typedef struct OutputBufferW
// {
// 	Dz1Console *console;
// 	size_t pos;
// 	wchar_t buf[OUTPUT_BUFFER_SIZE];
// } OutputBufferW;

static ssize_t _push_to_bufferW_tab(OutputBuffer *dst, int tab_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0, sz;
	while(tab_cnt >= 4)
	{
		if ((sz = _push_to_buffer(dst, (u8_t *)tab_str_W, tab4w_sz, errp)) < 0) return -1;
		else { ret += sz; tab_cnt -= 4; }
	}
	switch(tab_cnt)
	{
	case 3:
		if ((sz = _push_to_buffer(dst, (u8_t *)tab_str_W, tab3w_sz, errp)) < 0) return -1;
		else { ret += sz; tab_cnt -= 3; }
		break;
	case 2:
		if ((sz = _push_to_buffer(dst, (u8_t *)tab_str_W, tab2w_sz, errp)) < 0) return -1;
		else { ret += sz; tab_cnt -= 2; }
		break;
	case 1:
		if ((sz = _push_to_buffer(dst, (u8_t *)tab_str_W, tab1w_sz, errp)) < 0) return -1;
		else { ret += sz; tab_cnt -= 1; }
		break;
	default: break;
	}
	return ret;
}

static ssize_t _push_promptW(OutputBuffer *buf, wstr_t prompt, size_t promptLen, Dz1Error *errp)
{
	ssize_t sz, ret = 0;
	if (promptLen)
	{	// print prompt
		if ((sz = _push_to_buffer(buf, (u8_t *)prompt, promptLen * sizeof(wchar_t), errp)) < 0) return -1;
		else ret += sz;
	}
	return ret;
}

static ssize_t _Dz1ConsoleW_writeText(Dz1Console *con, wstr_t prompt, size_t promptLen, int tab, wchar_t *data, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	wchar_t *cp = data;
	ssize_t ret = 0;

	ssize_t sz = 0;
	OutputBuffer buf = { NULL, 0 };
	buf.console = con;

	while(size > 0)
	{
		if (*cp == L'\r')
		{	// Ignore LF
			cp++; size--; continue;
		}
		else if (*cp == L'\n')
		{	// CR :: out prompt, tab and put cr
			if (con->cr_output)
			{	// 이전 출력이 \n 으로 끝난 경우
				if ((sz = _push_promptW(&buf, prompt, promptLen, errp)) < 0) return -1; else ret += sz;
				con->cr_output = FALSE;
			}
			// Print New Line
			switch(con->cr)
			{
			case Dz1ConsoleCR_CRLF: if ((sz = _push_to_buffer(&buf, (u8_t *)L"\r\n", 2 * sizeof(wchar_t), errp)) < 0) return -1; else ret += sz; break;
			default:				if ((sz = _push_to_buffer(&buf, (u8_t *)L"\n",   1 * sizeof(wchar_t), errp)) < 0) return -1; else ret += sz; break;
			}
			con->col = 0;
			
			if (size > 1)	// include CR
			{	// 출력할 것이 남았다
				if ((sz = _push_promptW(&buf, prompt, promptLen, errp)) < 0) return -1; else ret += sz;
				if ((sz = _push_to_bufferW_tab(&buf, tab, errp)) < 0) return -1; else { ret += sz; con->col += (tab * DZ1_TAB_STR_LEN); }
			}
			else con->cr_output = TRUE;
		}
		else
		{	// Other Letters
			if (con->cr_output)
			{	// 이전 출력이 \n 으로 끝난 경우
				if ((sz = _push_promptW(&buf, prompt, promptLen, errp)) < 0) return -1; else ret += sz;
				if ((sz = _push_to_bufferW_tab(&buf, tab, errp)) < 0) return -1; else { ret += sz; con->col += (tab * DZ1_TAB_STR_LEN); }
				con->cr_output = FALSE;
			}

			if (*cp == L'\t')
			{
				ssize_t len = DZ1_TAB_STR_LEN - (con->col % DZ1_TAB_STR_LEN);
				if ((sz = _push_to_buffer(&buf, (u8_t *)tab_str_W, len * sizeof(wchar_t), errp)) < 0) return -1; else { ret += sz; con->col += (int)len; }
			}
			if ((sz = _push_to_buffer(&buf, (u8_t *)cp, 1 * sizeof(wchar_t), errp)) < 0) return -1;
			else
			{
				ret += sz;
				if (*cp & 0x8000) con->col += 2;
				else con->col++;
			}
		}
		cp++; size--;
	}
	_flush_buffer(&buf, errp);
	return ret;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// tvprintf
static ssize_t _Dz1ConsoleA_tvprintf(Dz1Console *con, str_t prompt, int tab, const char *fmt, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ssize_t ret = -1;
	char *buf = NULL;
	if ((buf = (char *)Dz1Malloc(0x4000, &err)) != NULL)
	{
		ssize_t size = 0;

		pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);

		size = vsnprintf(buf, 0x3FFF, fmt, ap);

		ret = _Dz1ConsoleA_writeText(con, prompt, prompt ? strlen(prompt) : 0, tab, buf, size, &err);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)free, (void *)buf);
	}
	return ret;
}

ssize_t Dz1ConsoleA_tvprintf(Dz1Console *con, int tab, const char *fmt, va_list ap)
{
	ssize_t ret = -1;

	if (con)
	{
		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		ret = _Dz1ConsoleA_tvprintf(con, Dz1ConsolePromptA_get(&con->prompt), tab, fmt, ap);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}
	else
	{
		no_con_err_out("Dz1Console_tvprintf", "con == NULL");
	}

	return ret;
}
#ifndef UNIX_SYSTEM
static ssize_t _Dz1ConsoleW_tvprintf(Dz1Console *con, wstr_t prompt, int tab, const wchar_t *fmt, va_list ap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ssize_t ret = -1;
	wchar_t *buf = NULL;
	//if ((buf = (char *)malloc(0x4000)) != NULL)
	if ((buf = (wchar_t *)Dz1Malloc(0x4000, &err)) != NULL)
	{
		ssize_t size = 0;

		//pthread_cleanup_push((Dz1CancelFunc)free, (void *)buf);
		pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);

		size = _vsnwprintf(buf, 0x1FFF, fmt, ap);

		ret = _Dz1ConsoleW_writeText(con, prompt, prompt ? wcslen(prompt) : 0, tab, buf, size, &err);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)free, (void *)buf);
	}
	return ret;
}

ssize_t Dz1ConsoleW_tvprintf(Dz1Console *con, int tab, const wchar_t *fmt, va_list ap)
{
	ssize_t ret = -1;

	if (con)
	{
		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		ret = _Dz1ConsoleW_tvprintf(con, Dz1ConsolePromptW_get(&con->prompt), tab, fmt, ap);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}
	else
	{
		no_con_err_out("Dz1Console_tvprintf", "con == NULL");
	}

	return ret;
}
#endif
// tvprintf
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// tprintf
ssize_t Dz1ConsoleA_tprintf(Dz1Console *con, int tab, const char *fmt, ...)
{
	ssize_t ret = -1;

	if (con)
	{
		va_list ap;
		va_start(ap, fmt);

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		ret = _Dz1ConsoleA_tvprintf(con, Dz1ConsolePromptA_get(&con->prompt), tab, fmt, ap);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

		va_end(ap);
	}

	return ret;
}

#ifndef UNIX_SYSTEM
ssize_t Dz1ConsoleW_tprintf(Dz1Console *con, int tab, const wchar_t *fmt, ...)
{
	ssize_t ret = -1;

	if (con)
	{
		va_list ap;
		va_start(ap, fmt);

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		ret = _Dz1ConsoleW_tvprintf(con, Dz1ConsolePromptW_get(&con->prompt), tab, fmt, ap);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

		va_end(ap);
	}

	return ret;
}
#endif
// tprintf
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// vprintf
ssize_t Dz1ConsoleA_vprintf(Dz1Console *con, const char *fmt, va_list ap)
{
	ssize_t ret = -1;

	if (con)
	{
		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		ret = _Dz1ConsoleA_tvprintf(con, Dz1ConsolePromptA_get(&con->prompt), 0, fmt, ap);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}

	return ret;
}

#ifndef UNIX_SYSTEM
ssize_t Dz1ConsoleW_vprintf(Dz1Console *con, const wchar_t *fmt, va_list ap)
{
	ssize_t ret = -1;

	if (con)
	{
		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		ret = _Dz1ConsoleW_tvprintf(con, Dz1ConsolePromptW_get(&con->prompt), 0, fmt, ap);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}

	return ret;
}
#endif
// vprintf
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// printf
static ssize_t _Dz1ConsoleA_printf(Dz1Console *con, str_t prompt, int tab, const char *fmt, ...)
{
	ssize_t ret = 0;
	va_list ap;
	va_start(ap, fmt);

	ret = _Dz1ConsoleA_tvprintf(con, prompt, tab, fmt, ap);

	va_end(ap);

	return ret;
}

ssize_t Dz1ConsoleA_printf(Dz1Console *con, const char *fmt, ...)
{
	ssize_t ret = -1;

	if (con)
	{
		va_list ap;
		va_start(ap, fmt);

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		ret = _Dz1ConsoleA_tvprintf(con, Dz1ConsolePromptA_get(&con->prompt), 0, fmt, ap);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

		va_end(ap);
	}

	return ret;
}

#ifndef UNIX_SYSTEM
static ssize_t _Dz1ConsoleW_printf(Dz1Console *con, wstr_t prompt, int tab, const wchar_t *fmt, ...)
{
	ssize_t ret = 0;
	va_list ap;
	va_start(ap, fmt);

	ret = _Dz1ConsoleW_tvprintf(con, prompt, tab, fmt, ap);

	va_end(ap);

	return ret;
}

ssize_t Dz1ConsoleW_printf(Dz1Console *con, const wchar_t *fmt, ...)
{
	ssize_t ret = -1;

	if (con)
	{
		va_list ap;
		va_start(ap, fmt);

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		ret = _Dz1ConsoleW_tvprintf(con, Dz1ConsolePromptW_get(&con->prompt), 0, fmt, ap);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

		va_end(ap);
	}

	return ret;
}
#endif
// printf
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// printb core
static ssize_t _Dz1ConsoleA_printb(Dz1Console *con, str_t prompt, int tab, u32_t offset, void *data, size_t size, size_t align, bool_t print_letter)
{
	ssize_t ret = _Dz1ConsoleA_printf(con, prompt, tab, "%08X : ", offset);
	size_t temp;
	char *lp = (char *)data;
	u8_t *cp = (u8_t *)data;

	temp = size; while(temp--) { ret += _Dz1ConsoleA_printf(con, prompt, tab, "%02X ", *cp++); align--; }

	if (align) while(align--) { ret += _Dz1ConsoleA_printf(con, prompt, 0, "   "); }

	if (print_letter)
	{
		ret += _Dz1ConsoleA_printf(con, prompt, 0, ": ");
		temp = size; while(temp--) { ret += _Dz1ConsoleA_printf(con, prompt, 0, "%c", (*lp > 0x20 ? *lp : '.')); lp++; }
	}
	ret += _Dz1ConsoleA_printf(con, prompt, 0, "\n");

	return ret;
}
#ifndef UNIX_SYSTEM
static ssize_t _Dz1ConsoleW_printb(Dz1Console *con, wstr_t prompt, int tab, u32_t offset, void *data, size_t size, size_t align, bool_t print_letter)
{
	ssize_t ret = _Dz1ConsoleW_printf(con, prompt, tab, L"%08X : ", offset);
	size_t temp;
	char *lp = (char *)data;
	u8_t *cp = (u8_t *)data;

	temp = size; while(temp--) { ret += _Dz1ConsoleW_printf(con, prompt, tab, L"%02X ", *cp++); align--; }

	if (align) while(align--) { ret += _Dz1ConsoleW_printf(con, prompt, 0, L"   "); }

	if (print_letter)
	{
		ret += _Dz1ConsoleW_printf(con, prompt, 0, L": ");
		temp = size; while(temp--) { ret += _Dz1ConsoleW_printf(con, prompt, 0, L"%c", (*lp > 0x20 && *lp <= 0x7f ? *lp : '.')); lp++; }
	}
	ret += _Dz1ConsoleW_printf(con, prompt, 0, L"\n");

	return ret;
}
#endif
// printb core
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// tprintb
ssize_t Dz1ConsoleA_tprintb(Dz1Console *con, int tab, void *data, size_t size, size_t align, bool_t print_letter)
{
	ssize_t ret = -1;

	if (con && data && size)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		align = align ? align : 16;

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _Dz1ConsoleA_printb(con, Dz1ConsolePromptA_get(&con->prompt), tab, (u32_t)(cp - base), cp, jobSize, align, print_letter);
			cp += jobSize; size -= jobSize;
		}

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
ssize_t Dz1ConsoleW_tprintb(Dz1Console *con, int tab, void *data, size_t size, size_t align, bool_t print_letter)
{
	ssize_t ret = -1;

	if (con && data && size)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		align = align ? align : 16;

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _Dz1ConsoleW_printb(con, Dz1ConsolePromptW_get(&con->prompt), tab, (u32_t)(cp - base), cp, jobSize, align, print_letter);
			cp += jobSize; size -= jobSize;
		}

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}
	return ret;
}
#endif
// tprintb
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// printb
ssize_t Dz1ConsoleA_printb(Dz1Console *con, void *data, size_t size, size_t align, bool_t print_letter)
{
	ssize_t ret = -1;

	if (con && data && size)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		align = align ? align : 16;

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _Dz1ConsoleA_printb(con, Dz1ConsolePromptA_get(&con->prompt), 0, (u32_t)(cp - base), cp, jobSize, align, print_letter);
			cp += jobSize; size -= jobSize;
		}

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
ssize_t Dz1ConsoleW_printb(Dz1Console *con, void *data, size_t size, size_t align, bool_t print_letter)
{
	ssize_t ret = -1;

	if (con && data && size)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		align = align ? align : 16;

		pthread_mutex_lock(&con->lockOut);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _Dz1ConsoleW_printb(con, Dz1ConsolePromptW_get(&con->prompt), 0, (u32_t)(cp - base), cp, jobSize, align, print_letter);
			cp += jobSize; size -= jobSize;
		}

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}
	return ret;
}
#endif
// printb
///////////////////////////////////////////////////////////////////////////////

////////////////////////
#ifndef UNIX_SYSTEM
static void codeconv_openCancel(void *ptr)
{
	codeconv_t h = (codeconv_t)ptr;
	codeconv_close(h);
}
ssize_t _dz1_core_codeconv(u8_t *dst, size_t dst_byte_size, const char *dstcs, u8_t *src, size_t src_byte_size, const char *srccs)
{
	ssize_t ret = -1;
#ifdef USE_CODECONV
	codeconv_t h = (void *)-1;

	char _dst_charset[64];
	strcpy(_dst_charset, dstcs);

	if (strstr(dstcs, "//TRANSLIT") == NULL) strcat(_dst_charset, "//TRANSLIT");

	if ((h = codeconv_open(_dst_charset, srccs)) == (void *)-1) no_con_err_out("_Dz1Console_conv", "open fail");
	else
	{
		ssize_t sz = 0;
		u8_t	*_src = src;
		size_t	 _src_byte_size = src_byte_size;

		u8_t	*_dst = dst;
		size_t	_dst_byte_size = dst_byte_size;

		pthread_cleanup_push(codeconv_openCancel, (void *)h);

		while(_src_byte_size > 0)
		{
			if ((sz = (ssize_t)codeconv(h, (char **)&_src, &_src_byte_size, (char **)&_dst, &_dst_byte_size)) == -1)
			{
				_src++;
				_src_byte_size--;
				*_dst++ = '?';
				_dst_byte_size--;
			}
		}
		ret = (ssize_t)(_dst - dst);
		
		pthread_cleanup_pop(1); // (codeconv_openCancel, (void *)h);
		sz = sz;
	}
#else
	no_con_err_out("_Dz1Console_conv", "no system");
#endif
	return ret;
}

static ssize_t _Dz1Console_etvprintf(Dz1Console *con, str_t mbcs, size_t sz, int tab)
{
	ssize_t ret = -1;
	wstr_t temp = NULL;
	if ((temp = (wchar_t *)Dz1Calloc(sizeof(wchar_t), sz + 1, NULL)) == NULL) no_con_err_out("Dz1ConsoleW_etvprintf", "malloc fail");	// 8KB unicode buffer
	else
	{
		ssize_t byte_sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);

		if ((byte_sz = _dz1_core_codeconv((u8_t *)temp, sizeof(wchar_t) * (sz + 1), DZ1_SYSTEM_WIDE_CHARSET, (u8_t *)mbcs, sz, DZ1_SYSTEM_MBCS_CHARSET)) < 0) no_con_err_out("Dz1ConsoleW_etvprintf", "convert fail");
		else if (byte_sz > 0) ret = Dz1ConsoleW_writeText(con, temp, byte_sz >> 1, tab);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
	return ret;
}

ssize_t Dz1Console_etvprintf(Dz1Console *con, int tab, const char *fmt, va_list ap)
{	// Text : av_list
	ssize_t ret = -1;

	if (con)
	{
		Dz1ConsoleMode mode;
		
		if ((mode = dz1DefCon_getMode()) == Dz1ConsoleMode_mbcs)
		{
			pthread_mutex_lock(&con->lockOut);
			pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);

			ret = _Dz1ConsoleA_tvprintf(con, Dz1ConsolePromptA_get(&con->prompt), tab, fmt, ap);

			pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&con->lockOut);
		}
		else if (mode == Dz1ConsoleMode_wide)
		{
			char *temp = NULL;
			if ((temp = (char *)Dz1Malloc(4096, NULL)) == NULL) no_con_err_out("Dz1ConsoleW_etvprintf", "malloc fail");	// 4KB sprintf buffer
			else
			{
				int temp_len = 0;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);

				if ((temp_len = vsnprintf(temp, 4095, fmt, ap)) < 0) no_con_err_out("Dz1ConsoleW_etvprintf", "formatting fail");
				else if (temp_len == 0) { }
				else ret = _Dz1Console_etvprintf(con, temp, temp_len, tab);

				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
			}
		}
	}
	else
	{
		no_con_err_out("Dz1ConsoleW_etvprintf", "con == NULL");
	}

	return ret;
}

ssize_t	 Dz1Console_etprintf(Dz1Console *con, int tab, const char *fmt, ...)
{	// Text
	ssize_t ret = 0;
	va_list ap;
	va_start(ap, fmt);
	ret = Dz1Console_etvprintf(con, tab, fmt, ap);
	va_end(ap);
	return ret;
}

ssize_t	Dz1Console_etprintb(Dz1Console *con, int tab, void *data, size_t size, size_t align, bool_t printLetter)
{	// Binary
	switch(dz1DefCon_getMode())
	{
	default:
	case Dz1ConsoleMode_mbcs: return Dz1ConsoleA_tprintb(con, tab, data, size, align, printLetter);
	case Dz1ConsoleMode_wide: return Dz1ConsoleW_tprintb(con, tab, data, size, align, printLetter);
	}
}
////////////////////////
#endif	// UNIX_SYSTEM



