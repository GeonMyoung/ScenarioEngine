#include <ctype.h>

#include <dz1_malloc.h>
#include "dz1_shell_parse.h"

static str_t Dz1ShellParseA_anyCotate(str_t dst, str_t src, char cotate, bool_t includeCotateLetter, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	// Trim white space
	while(*src && isspace(*src)) src++;

	if (*src && *src == cotate)
	{
		// 첫 글자 처리
		if (includeCotateLetter)
		{	// cotate포함형 이면 dst에 복사
			if (dst) *dst++ = *src++;
		}
		else src++;	// 아니면 cotate문자 패스

		// 출력 가능하고 cotate문자가 아닌 동안
		while(*src && isprint(*src) && *src != cotate)
		{	// 문자 복사
			if (*src == '\\') src++; // skip escape sequence

			if (dst) *dst++ = *src++;
			else src++;
		}

		// while문 종료 조건 : NULL을 만났거나, print불가능하거나, cotate문자를 만남
		if (*src == '\0' || *src != cotate)
		{	// NULL을 만났거나, print불가능하거나
			src = NULL;
			Dz1Error_set(errp, EINVAL);
		}
		else
		{	// cotate문자를 만남
			// 마지막 글자 처리
			if (includeCotateLetter)
			{	// cotate 포함 형이면 dst에 복사
				if (dst) *dst++ = *src++;
			}
			else src++;	// 아니면 cotate문자 패스

			if (dst) *dst = '\0'; // make ASCIIZ string
			Dz1Error_set(errp, 0);
		}
	}

	return src;
}

static bool_t isCP949(str_t src)
{
	if (*src & 0x80 && *(src + 1) != '\0' && *(src + 1) & 0x80) return TRUE;
	return FALSE;
}

str_t Dz1ShellParseA_word(str_t dst, str_t src, bool_t parseESCLetter, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	// Trim white space
	while(*src && isspace(*src & 0xFF)) src++;

	while(*src && (isgraph(*src & 0xFF) || isCP949(src)))
	{
		if (parseESCLetter && *src == '\\') src++; // skip escape sequence

		if (isCP949(src))
		{
			if (dst) *dst++ = *src++;
			else src++;
		}
		if (dst) *dst++ = *src++;
		else src++;
	}
	// make ASCIIZ string
	if (dst) *dst = '\0';


	Dz1Error_set(errp, 0);

	return src;
}

ssize_t Dz1ShellParseA(str_t text, bool_t includeCotateLetter, bool_t parseESCLetter, Dz1ShellParseEmitFuncA func, void *funcArg, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	str_t src = text;
	str_t dst = (str_t)Dz1Malloc(65535, errp);

	if (dst)
	{
		Dz1ShellParseToken type = Dz1ShellParseToken_max;

		pthread_cleanup_push(Dz1Memory_cancel, (void *)dst);

		while(*src)
		{
			// Trim white space
			if (*src && isspace(*src & 0xFF))
			{
				while(*src && isspace(*src & 0xFF)) src++;
				continue;
			}

			type = Dz1ShellParseToken_max;
			if (*src == '\"' || *src == '\'')
			{	// Cotate String
				char cotate = *src;
				switch(cotate)
				{
					case '\"':
						type = Dz1ShellParseToken_doubleCotatedString;
						break;
					case '\'':
						type = Dz1ShellParseToken_singleCotatedString;
						break;
				}
				if ((src = Dz1ShellParseA_anyCotate(dst, src, cotate, includeCotateLetter, errp)) == NULL) { ret = -1; break; }
			}
			else if (isgraph(*src & 0xFF) || isCP949(src))
			{
				if (*src == '$')
				{
					src++;
					if ((src = Dz1ShellParseA_word(dst, src, parseESCLetter, errp)) == NULL) { ret = -1; break; }
					else
					{
						type = Dz1ShellParseToken_literal;
						// Dz1Console_printf(NULL, 0, "[LITERAL:%s]\n", dst);
					}
				}
				else
				{
					if ((src = Dz1ShellParseA_word(dst, src, parseESCLetter, errp)) == NULL) { ret = -1; break; }
					else
					{
						type = Dz1ShellParseToken_word;
						// Dz1Console_printf(NULL, 0, "[WORD:%s]\n", dst);
					}
				}
			}

			if (type == Dz1ShellParseToken_max) { ret = -1; break; }

			if (func && (*errp = func(funcArg, type, dst)).code) { ret = -1; break; }
		}

		pthread_cleanup_pop(1); // (Dz1Mem_cancel, (void *)dst);
	}

	if (ret == 0) ret = (ssize_t)(src - text);

	return ret;
}
#ifndef UNIX_SYSTEM
static wstr_t Dz1ShellParseW_anyCotate(wstr_t dst, wstr_t src, wchar_t cotate, bool_t includeCotateLetter, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	// Trim white space
	while(*src && iswspace(*src)) src++;

	if (*src && *src == cotate)
	{
		// 첫 글자 처리
		if (includeCotateLetter)
		{	// cotate포함형 이면 dst에 복사
			if (dst) *dst++ = *src++;
		}
		else src++;	// 아니면 cotate문자 패스

		// 출력 가능하고 cotate문자가 아닌 동안
		while(*src && iswprint(*src) && *src != cotate)
		{	// 문자 복사
			if (*src == L'\\') src++; // skip escape sequence

			if (dst) *dst++ = *src++;
			else src++;
		}

		// while문 종료 조건 : NULL을 만났거나, print불가능하거나, cotate문자를 만남
		if (*src == L'\0' || *src != cotate)
		{	// NULL을 만났거나, print불가능하거나
			src = NULL;
			Dz1Error_set(errp, EINVAL);
		}
		else
		{	// cotate문자를 만남
			// 마지막 글자 처리
			if (includeCotateLetter)
			{	// cotate 포함 형이면 dst에 복사
				if (dst) *dst++ = *src++;
			}
			else src++;	// 아니면 cotate문자 패스

			if (dst) *dst = L'\0'; // make ASCIIZ string
			Dz1Error_set(errp, 0);
		}
	}
	return src;
}

wstr_t Dz1ShellParseW_word(wstr_t dst, wstr_t src, bool_t parseESCLetter, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	// Trim white space
	while(*src && iswspace(*src & 0xFFFF)) src++;

	while(*src && iswgraph(*src & 0xFFFF))
	{
		if (parseESCLetter && *src == L'\\') src++; // skip escape sequence

		if (dst) *dst++ = *src++;
		else src++;
	}
	// make ASCIIZ string
	if (dst) *dst = L'\0';

	Dz1Error_set(errp, 0);

	return src;
}

ssize_t Dz1ShellParseW(wstr_t text, bool_t includeCotateLetter, bool_t parseESCLetter, Dz1ShellParseEmitFuncW func, void *funcArg, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	wstr_t src = text;
	wstr_t dst = (wstr_t)Dz1Malloc(65535, errp);

	if (dst)
	{
		Dz1ShellParseToken type = Dz1ShellParseToken_max;

		pthread_cleanup_push(Dz1Memory_cancel, (void *)dst);

		while(*src)
		{
			// Trim white space
			if (*src && iswspace(*src & 0xFFFF))
			{
				while(*src && iswspace(*src & 0xFFFF)) src++;
				continue;
			}

			type = Dz1ShellParseToken_max;
			if (*src == L'\"' || *src == L'\'')
			{	// Cotate String
				wchar_t cotate = *src;
				switch(cotate)
				{
					case L'\"':
						type = Dz1ShellParseToken_doubleCotatedString;
						break;
					case L'\'':
						type = Dz1ShellParseToken_singleCotatedString;
						break;
				}
				if ((src = Dz1ShellParseW_anyCotate(dst, src, cotate, includeCotateLetter, errp)) == NULL) { ret = -1; break; }
			}
			else if (iswgraph(*src & 0xFFFF))
			{
				if (*src == L'$')
				{
					src++;
					if ((src = Dz1ShellParseW_word(dst, src, parseESCLetter, errp)) == NULL) { ret = -1; break; }
					else
					{
						type = Dz1ShellParseToken_literal;
						// Dz1Console_printf(NULL, 0, "[LITERAL:%s]\n", dst);
					}
				}
				else
				{
					if ((src = Dz1ShellParseW_word(dst, src, parseESCLetter, errp)) == NULL) { ret = -1; break; }
					else
					{
						type = Dz1ShellParseToken_word;
						// Dz1Console_printf(NULL, 0, "[WORD:%s]\n", dst);
					}
				}
			}

			if (type == Dz1ShellParseToken_max) { ret = -1; break; }

			if (func && (*errp = func(funcArg, type, dst)).code) { ret = -1; break; }
		}

		pthread_cleanup_pop(1); // (Dz1Mem_cancel, (void *)dst);
	}

	if (ret == 0) ret = (ssize_t)(src - text);

	return ret;
}
#endif