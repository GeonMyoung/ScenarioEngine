#include <dz1_termio.h>
#include <dz1_thread_stdio.h>
#include "dz1_shell.h"

static str_t validLettersA = (str_t)" `~!@#$%^&*()+-=_\\|{}[]:\";',./<>?";
static bool_t isValidLetterA(int c)
{
	if (c >= '0' && c <= '9') return TRUE;
	else if (c >= 'a' && c <= 'z') return TRUE;
	else if (c >= 'A' && c <= 'Z') return TRUE;
	else return strchr(validLettersA, c) ? TRUE : FALSE;
}

Dz1ShellInputStatus Dz1ShellInputA_recv(Dz1ShellInputA *p, str_t defStr)
{
	int c, len;
	Dz1TermKey key;
	Dz1TermMetaKey meta;
	bool_t done = FALSE;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellInputStatus ret = Dz1ShellInputStatus_ok;

	if (defStr && (len = (int)strlen(defStr)))
	{
		strcpy(p->buf, defStr);
		p->cursor = p->buf + len;
		p->end = p->buf + len;
	}
	else
	{
		p->cursor = p->buf;
		p->end = p->buf;
		*p->end = 0;
	}

	Dz1ThreadA_printf("%s", p->buf);

	while(!done)
	{
		c = Dz1TermIoA_getc(p->termio, &meta, &key, &err);
		if (c == -1) { ERR_OUT(&err); }
		else if (c == 0)
		{
			done = TRUE;
			switch(key)
			{
				case Dz1TermKey_esc:
					ret = Dz1ShellInputStatus_esc;
					break;
				case Dz1TermKey_up:
					ret = Dz1ShellInputStatus_up;
					break;
				case Dz1TermKey_down:
					ret = Dz1ShellInputStatus_down;
					break;
				case Dz1TermKey_right:
					ret = Dz1ShellInputStatus_right;
					if (p->cursor < p->end)
					{
						u32_t width = 80;
						Dz1Thread_getSize(&width, NULL);
						if ((u32_t)(p->end - p->buf) <= width)
							Dz1ThreadA_tprintf(0, "%c", *p->cursor++);
					}
					done = FALSE;
					break;
				case Dz1TermKey_left:
					ret = Dz1ShellInputStatus_left;
					if (p->cursor > p->buf)
					{
						u32_t width = 80;
						Dz1Thread_getSize(&width, NULL);
						if ((u32_t)(p->end - p->buf) <= width)
						{
							p->cursor--;
							Dz1ThreadA_tprintf(0, "\b");
						}
					}
					done = FALSE;
					break;
				case Dz1TermKey_end:
				case Dz1TermKey_home:
				case Dz1TermKey_insert:
				case Dz1TermKey_delete:
					ret = Dz1ShellInputStatus_notSupport;
					break;
				case Dz1TermKey_pageUp:
					ret = Dz1ShellInputStatus_pageUp;
					break;
				case Dz1TermKey_pageDown:
					ret = Dz1ShellInputStatus_pageDown;
					break;
				case Dz1TermKey_f1:
				case Dz1TermKey_f2:
				case Dz1TermKey_f3:
				case Dz1TermKey_f4:
				case Dz1TermKey_f5:
				case Dz1TermKey_f6:
				case Dz1TermKey_f7:
				case Dz1TermKey_f8:
				case Dz1TermKey_f9:
				case Dz1TermKey_f10:
				case Dz1TermKey_f11:
				case Dz1TermKey_f12:
					ret = Dz1ShellInputStatus_notSupport;
					break;
				case Dz1TermKey_max:
				default:
					Dz1ThreadA_tprintf(0, "Unknown Escape Sequence\n");
					break;
			}
		}
		else if (c & 0xFF00)
		{	// 2 byte read
			char a = (c >> 8) & 0xFF;
			char b = c & 0xFF;
			if (p->cursor == p->end) *(++p->end) = 0;
			*p->cursor++ = a;
			if (p->cursor == p->end) *(++p->end) = 0;
			*p->cursor++ = b;
			Dz1ThreadA_tprintf(0, "%c%c", a, b);
		}
		else
		{
			switch((char)c)
			{
				case '\x7F':
				case '\x08': // back space
					if (p->cursor > p->buf)
					{
						if (p->cursor == p->end)
						{	// at end
							u32_t width = 80;
							*(--p->end) = 0;
							p->cursor--;
							Dz1Thread_getSize(&width, NULL);
							if ((u32_t)(p->end - p->buf) > width)
								Dz1ThreadA_tprintf(0, "\n%s", p->buf);
							else
								Dz1ThreadA_tprintf(0, "\b \b");
						}
						else
						{	// at middle
							u32_t width = 80;
							char *src = p->cursor--;
							char *dst = p->cursor;
							p->end--;

							while(*src) *dst++ = *src++;
							*dst = 0;

							Dz1Thread_getSize(&width, NULL);
							if ((u32_t)(p->end - p->buf) > width)
								Dz1ThreadA_tprintf(0, "\n%s", p->buf);
							else
							{
								ssize_t loop;
								Dz1ThreadA_tprintf(0, "\b");
								loop = Dz1ThreadA_tprintf(0, "%s ", p->cursor) + 1;
								while(loop--) Dz1ThreadA_tprintf(0, "\b");
							}
						}
					}
					break;
				case '\t':
					ret = Dz1ShellInputStatus_tab;
					done = TRUE;
					break;
				case '\r':
					break;
				case '\n':
					Dz1ThreadA_tprintf(0, "\n");
					ret = Dz1ShellInputStatus_ok;
					done = TRUE;
					break;
				default:
					if (isValidLetterA(c))
					{
						if (p->cursor == p->end) *(++p->end) = 0;
						*p->cursor++ = c;
						Dz1ThreadA_tprintf(0, "%c", c);
					}
					else Dz1ThreadA_tprintf(0, "<%02X>", (u8_t)c);
					break;
			}
		}
	}
	return ret;
}
#ifndef UNIX_SYSTEM
// static wstr_t validLettersW = L" `~!@#$%^&*()+-=_\\|{}[]:\";',./<>?";
// static bool_t isValidLetterW(int c)
// {
// 	if		(c >= L'0' && c <= L'9') return TRUE;
// 	else if (c >= L'a' && c <= L'z') return TRUE;
// 	else if (c >= L'A' && c <= L'Z') return TRUE;
// 	else return wcschr(validLettersW, c) ? TRUE : FALSE;
// }

Dz1ShellInputStatus Dz1ShellInputW_recv(Dz1ShellInputW *p, wstr_t defStr)
{
	int c, len;
	Dz1TermKey key;
	Dz1TermMetaKey meta;
	bool_t done = FALSE;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellInputStatus ret = Dz1ShellInputStatus_ok;

	if (defStr && (len = (int)wcslen(defStr)))
	{
		wcscpy(p->buf, defStr);
		p->cursor = p->buf + len;
		p->end = p->buf + len;
	}
	else
	{
		p->cursor = p->buf;
		p->end = p->buf;
		*p->end = 0;
	}

	Dz1ThreadW_printf(L"%s", p->buf);

	while(!done)
	{
		c = Dz1TermIoW_getc(p->termio, &meta, &key, &err);
		if (c == -1) { ERR_OUT(&err); }
		else if (c == 0)
		{
			done = TRUE;
			switch(key)
			{
				case Dz1TermKey_esc:
					ret = Dz1ShellInputStatus_esc;
					break;
				case Dz1TermKey_up:
					ret = Dz1ShellInputStatus_up;
					break;
				case Dz1TermKey_down:
					ret = Dz1ShellInputStatus_down;
					break;
				case Dz1TermKey_right:
					ret = Dz1ShellInputStatus_right;
					if (p->cursor < p->end)
					{
						u32_t width = 80;
						Dz1Thread_getSize(&width, NULL);
						if ((u32_t)(p->end - p->buf) <= width)
							Dz1ThreadW_tprintf(0, L"%c", *p->cursor++);
					}
					done = FALSE;
					break;
				case Dz1TermKey_left:
					ret = Dz1ShellInputStatus_left;
					if (p->cursor > p->buf)
					{
						u32_t width = 80;
						Dz1Thread_getSize(&width, NULL);
						if ((u32_t)(p->end - p->buf) <= width)
						{
							p->cursor--;
							Dz1ThreadW_tprintf(0, L"\b");
						}
					}
					done = FALSE;
					break;
				case Dz1TermKey_end:
				case Dz1TermKey_home:
				case Dz1TermKey_insert:
				case Dz1TermKey_delete:
					ret = Dz1ShellInputStatus_notSupport;
					break;
				case Dz1TermKey_pageUp:
					ret = Dz1ShellInputStatus_pageUp;
					break;
				case Dz1TermKey_pageDown:
					ret = Dz1ShellInputStatus_pageDown;
					break;
				case Dz1TermKey_f1:
				case Dz1TermKey_f2:
				case Dz1TermKey_f3:
				case Dz1TermKey_f4:
				case Dz1TermKey_f5:
				case Dz1TermKey_f6:
				case Dz1TermKey_f7:
				case Dz1TermKey_f8:
				case Dz1TermKey_f9:
				case Dz1TermKey_f10:
				case Dz1TermKey_f11:
				case Dz1TermKey_f12:
					ret = Dz1ShellInputStatus_notSupport;
					break;
				case Dz1TermKey_max:
				default:
					Dz1ThreadW_tprintf(0, L"Unknown Escape Sequence\n");
					break;
			}
		}
// 		else if (c & 0xFF00)
// 		{	// 2 byte read
// 			char a = (c >> 8) & 0xFF;
// 			char b = c & 0xFF;
// 			if (p->cursor == p->end) *(++p->end) = 0;
// 			*p->cursor++ = a;
// 			if (p->cursor == p->end) *(++p->end) = 0;
// 			*p->cursor++ = b;
// 			Dz1ThreadW_tprintf(0, L"%c%c", a, b);
// 		}
		else
		{
			switch((wchar_t)c)
			{
				case L'\x7F':
				case L'\x08': // back space
					if (p->cursor > p->buf)
					{
						if (p->cursor == p->end)
						{	// at end
							u32_t width = 80;
							*(--p->end) = 0;
							p->cursor--;
							Dz1Thread_getSize(&width, NULL);
							if ((u32_t)(p->end - p->buf) > width)
								Dz1ThreadW_tprintf(0, L"\n%s", p->buf);
							else
								Dz1ThreadW_tprintf(0, L"\b \b");
						}
						else
						{	// at middle
							u32_t width = 80;
							wchar_t *src = p->cursor--;
							wchar_t *dst = p->cursor;
							p->end--;

							while(*src) *dst++ = *src++;
							*dst = 0;

							Dz1Thread_getSize(&width, NULL);
							if ((u32_t)(p->end - p->buf) > width)
								Dz1ThreadW_tprintf(0, L"\n%s", p->buf);
							else
							{
								ssize_t loop;
								Dz1ThreadW_tprintf(0, L"\b");
								loop = Dz1ThreadW_tprintf(0, L"%s ", p->cursor) + 1;
								while(loop--) Dz1ThreadW_tprintf(0, L"\b");
							}
						}
					}
					break;
				case L'\t':
					ret = Dz1ShellInputStatus_tab;
					done = TRUE;
					break;
				case L'\r':
					break;
				case L'\n':
					Dz1ThreadW_tprintf(0, L"\n");
					ret = Dz1ShellInputStatus_ok;
					done = TRUE;
					break;
				default:
// 					if (isValidLetterW(c))
					{
						if (p->cursor == p->end) *(++p->end) = 0;
						*p->cursor++ = c;
						Dz1ThreadW_tprintf(0, L"%c", c);
					}
// 					else Dz1ThreadW_tprintf(0, L"<%02X>", (u8_t)c);
					break;
			}
		}
	}
	return ret;
}
#endif
