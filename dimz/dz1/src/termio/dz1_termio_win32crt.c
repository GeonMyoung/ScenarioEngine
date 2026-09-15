#include <dz1_thread_stdio.h>
#ifndef UNIX_SYSTEM
#include "dz1_termio_win32crt.h"

static ssize_t termWin32CrtA(char esc, Dz1TermMetaKey *meta, Dz1TermKey *key, char *buf, size_t size, Dz1Error *err)
{
	char c;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TermMetaKey _meta, *metap = meta ? meta : &_meta;
	Dz1TermKey _key, *keyp = key ? key : &_key;

	if (esc == 0x1b)
	{
		*metap = Dz1TermMetaKey_none;
		*keyp = Dz1TermKey_esc;
		Dz1Error_set(errp, 0);
		return 0;
	}
	else
	{
		int read_c;
//		if (Dz1Thread_read((u8_t *)&c, 1, 500000, errp) == 1)
		if ((read_c = Dz1Thread_getch(500000, errp)) < 0) { }
		else if ((c = (char)(read_c & 0xFF)) == 0) Dz1Error_set(errp, EPIPE);
		else
		{
			switch((u8_t)c)
			{
			case 0x48:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_up;
				break;
			case 0x50:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_down;
				break;
			case 0x4D:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_right;
				break;
			case 0x4B:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_left;
				break;
			case 0x4F:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_end;
				break;
			case 0x47:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_home;
				break;
			case 0x52:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_insert;
				break;
			case 0x53:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_delete;
				break;
			case 0x49:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_pageUp;
				break;
			case 0x51:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_pageDown;
				break;
			case 0x3B:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f1;
				break;
			case 0x3C:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f2;
				break;
			case 0x3D:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f3;
				break;
			case 0x3E:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f4;
				break;
			case 0x3F:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f5;
				break;
			case 0x40:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f6;
				break;
			case 0x41:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f7;
				break;
			case 0x42:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f8;
				break;
			case 0x43:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f9;
				break;
			case 0x44:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f10;
				break;
			case 0x85:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f11;
				break;
			case 0x86:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f12;
				break;
			//-----------------------------------------
			// Shifted
			case 0x54:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f1;
				break;
			case 0x55:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f2;
				break;
			case 0x56:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f3;
				break;
			case 0x57:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f4;
				break;
			case 0x58:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f5;
				break;
			case 0x59:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f6;
				break;
			case 0x5A:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f7;
				break;
			case 0x5B:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f8;
				break;
			case 0x5C:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f9;
				break;
			case 0x5D:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f10;
				break;
			case 0x87:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f11;
				break;
			case 0x88:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f12;
				break;
			//-----------------------------------------
			// Alted
			case 0x98:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_up;
				break;
			case 0xA0:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_down;
				break;
			case 0x9D:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_right;
				break;
			case 0x9B:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_left;
				break;
			case 0x9F:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_end;
				break;
			case 0x97:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_home;
				break;
			case 0xA2:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_insert;
				break;
			case 0xA3:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_delete;
				break;
			case 0x99:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_pageUp;
				break;
			case 0xA1:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_pageDown;
				break;
			case 0x68:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f1;
				break;
			case 0x69:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f2;
				break;
			case 0x6A:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f3;
				break;
			case 0x6B:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f4;
				break;
			case 0x6C:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f5;
				break;
			case 0x6D:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f6;
				break;
			case 0x6E:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f7;
				break;
			case 0x6F:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f8;
				break;
			case 0x70:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f9;
				break;
			case 0x71:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f10;
				break;
			case 0x8B:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f11;
				break;
			case 0x8C:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f12;
				break;
			// Ctrl ---------------------------
			case 0x8D:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_up;
				break;
			case 0x91:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_down;
				break;
			case 0x74:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_right;
				break;
			case 0x73:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_left;
				break;
			case 0x75:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_end;
				break;
			case 0x77:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_home;
				break;
			case 0x92:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_insert;
				break;
			case 0x93:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_delete;
				break;
			/*
			case 0x86:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_pageUp;
				break;
			*/
			case 0x76:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_pageDown;
				break;
			case 0x5E:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f1;
				break;
			case 0x5F:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f2;
				break;
			case 0x60:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f3;
				break;
			case 0x61:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f4;
				break;
			case 0x62:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f5;
				break;
			case 0x63:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f6;
				break;
			case 0x64:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f7;
				break;
			case 0x65:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f8;
				break;
			case 0x66:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f9;
				break;
			case 0x67:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f10;
				break;
			case 0x89:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f11;
				break;
			case 0x8A:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f12;
				break;
			default:
				*buf = c;
				return 1;
			}
		}
	}
	Dz1Error_set(errp, 0);
	return 0;
}

Dz1ConsoleTermSpecA win32CrtSpecA =
{
	{ '\xE0', '\0' }, 2, termWin32CrtA
};

static ssize_t termWin32CrtW(wchar_t esc, Dz1TermMetaKey *meta, Dz1TermKey *key, wchar_t *buf, size_t size, Dz1Error *err)
{
	wchar_t c;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TermMetaKey _meta, *metap = meta ? meta : &_meta;
	Dz1TermKey _key, *keyp = key ? key : &_key;

	if (esc == 0x1b)
	{
		*metap = Dz1TermMetaKey_none;
		*keyp = Dz1TermKey_esc;
		Dz1Error_set(errp, 0);
		return 0;
	}
	else
	{
		int read_c;
//		if (Dz1Thread_read((u8_t *)&c, sizeof(wchar_t), 500000, errp) == 1)
		if ((read_c = Dz1Thread_getch(500000, errp)) < 0) { }
		else if ((c = (wchar_t)(read_c & 0xFFFF)) == 0) Dz1Error_set(errp, EPIPE);
		else 
		{
			switch(c)
			{
			case 0x48:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_up;
				break;
			case 0x50:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_down;
				break;
			case 0x4D:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_right;
				break;
			case 0x4B:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_left;
				break;
			case 0x4F:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_end;
				break;
			case 0x47:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_home;
				break;
			case 0x52:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_insert;
				break;
			case 0x53:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_delete;
				break;
			case 0x49:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_pageUp;
				break;
			case 0x51:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_pageDown;
				break;
			case 0x3B:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f1;
				break;
			case 0x3C:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f2;
				break;
			case 0x3D:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f3;
				break;
			case 0x3E:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f4;
				break;
			case 0x3F:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f5;
				break;
			case 0x40:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f6;
				break;
			case 0x41:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f7;
				break;
			case 0x42:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f8;
				break;
			case 0x43:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f9;
				break;
			case 0x44:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f10;
				break;
			case 0x85:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f11;
				break;
			case 0x86:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f12;
				break;
			//-----------------------------------------
			// Shifted
			case 0x54:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f1;
				break;
			case 0x55:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f2;
				break;
			case 0x56:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f3;
				break;
			case 0x57:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f4;
				break;
			case 0x58:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f5;
				break;
			case 0x59:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f6;
				break;
			case 0x5A:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f7;
				break;
			case 0x5B:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f8;
				break;
			case 0x5C:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f9;
				break;
			case 0x5D:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f10;
				break;
			case 0x87:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f11;
				break;
			case 0x88:
				*metap = Dz1TermMetaKey_shift;
				*keyp = Dz1TermKey_f12;
				break;
			//-----------------------------------------
			// Alted
			case 0x98:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_up;
				break;
			case 0xA0:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_down;
				break;
			case 0x9D:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_right;
				break;
			case 0x9B:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_left;
				break;
			case 0x9F:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_end;
				break;
			case 0x97:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_home;
				break;
			case 0xA2:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_insert;
				break;
			case 0xA3:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_delete;
				break;
			case 0x99:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_pageUp;
				break;
			case 0xA1:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_pageDown;
				break;
			case 0x68:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f1;
				break;
			case 0x69:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f2;
				break;
			case 0x6A:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f3;
				break;
			case 0x6B:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f4;
				break;
			case 0x6C:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f5;
				break;
			case 0x6D:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f6;
				break;
			case 0x6E:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f7;
				break;
			case 0x6F:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f8;
				break;
			case 0x70:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f9;
				break;
			case 0x71:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f10;
				break;
			case 0x8B:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f11;
				break;
			case 0x8C:
				*metap = Dz1TermMetaKey_alt;
				*keyp = Dz1TermKey_f12;
				break;
			// Ctrl ---------------------------
			case 0x8D:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_up;
				break;
			case 0x91:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_down;
				break;
			case 0x74:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_right;
				break;
			case 0x73:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_left;
				break;
			case 0x75:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_end;
				break;
			case 0x77:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_home;
				break;
			case 0x92:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_insert;
				break;
			case 0x93:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_delete;
				break;
			/*
			case 0x86:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_pageUp;
				break;
			*/
			case 0x76:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_pageDown;
				break;
			case 0x5E:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f1;
				break;
			case 0x5F:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f2;
				break;
			case 0x60:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f3;
				break;
			case 0x61:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f4;
				break;
			case 0x62:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f5;
				break;
			case 0x63:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f6;
				break;
			case 0x64:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f7;
				break;
			case 0x65:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f8;
				break;
			case 0x66:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f9;
				break;
			case 0x67:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f10;
				break;
			case 0x89:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f11;
				break;
			case 0x8A:
				*metap = Dz1TermMetaKey_none;
				*keyp = Dz1TermKey_f12;
				break;
			default:
				*buf = c;
				return 1;
			}
		}
	}
	Dz1Error_set(errp, 0);
	return 0;
}

Dz1ConsoleTermSpecW win32CrtSpecW =
{
	{ L'\xE0', L'\0' }, 2, termWin32CrtW
};

#endif
