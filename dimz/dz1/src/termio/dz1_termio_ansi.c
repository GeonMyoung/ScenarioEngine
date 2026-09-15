#include "dz1_termio_ansi.h"

static ssize_t termANSIA(char esc, Dz1TermMetaKey *meta, Dz1TermKey *key, char *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TermMetaKey _meta, *metap = meta ? meta : &_meta;

	*key = Dz1TermKey_esc;
	*metap = Dz1TermMetaKey_none;

	Dz1Error_set(errp, 0);
	return ret;
}

Dz1ConsoleTermSpecA ansiSpecA =
{
	{ '\x1b', 0 }, 1, termANSIA
};

#ifndef UNIX_SYSTEM
static ssize_t termANSIW(wchar_t esc, Dz1TermMetaKey *meta, Dz1TermKey *key, wchar_t *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TermMetaKey _meta, *metap = meta ? meta : &_meta;

	*key = Dz1TermKey_esc;
	*metap = Dz1TermMetaKey_none;

	Dz1Error_set(errp, 0);
	return ret;
}

Dz1ConsoleTermSpecW ansiSpecW =
{
	{ L'\x1b', 0 }, 1, termANSIW
};
#endif
