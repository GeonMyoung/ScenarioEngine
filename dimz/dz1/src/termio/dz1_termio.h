#ifndef DZ1_TERMCAP_H_LOCAL
#define DZ1_TERMCAP_H_LOCAL

#include <dz1_termio.h>

struct TermcapKeyMapA
{
	str_t		 pattern;
	Dz1TermKey	 key;
};

struct TermcapMetaKeyMapA
{
	char			 letter;
	Dz1TermMetaKey	 key;
};

typedef struct Dz1ConsoleTermSpecA
{
	char	 esc[3];
	int		 numOfEsc;
	ssize_t	 (*getKey)(char esc, Dz1TermMetaKey *meta, Dz1TermKey *key, char *buf, size_t size, Dz1Error *err);
} Dz1ConsoleTermSpecA;

#ifndef UNIX_SYSTEM
struct TermcapKeyMapW
{
	wstr_t		 pattern;
	Dz1TermKey	 key;
};

struct TermcapMetaKeyMapW
{
	wchar_t			 letter;
	Dz1TermMetaKey	 key;
};

typedef struct Dz1ConsoleTermSpecW
{
	wchar_t	 esc[3];
	int		 numOfEsc;
	ssize_t	 (*getKey)(wchar_t esc, Dz1TermMetaKey *meta, Dz1TermKey *key, wchar_t *buf, size_t size, Dz1Error *err);
} Dz1ConsoleTermSpecW;
#endif

#endif
