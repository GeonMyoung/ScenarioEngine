#ifndef DZ1_SHELL_PARSE_H
#define DZ1_SHELL_PARSE_H

#include <dz1_error.h>

typedef enum
{
	Dz1ShellParseToken_doubleCotatedString,
	Dz1ShellParseToken_singleCotatedString,
	Dz1ShellParseToken_word,
	Dz1ShellParseToken_literal,
	Dz1ShellParseToken_max
} Dz1ShellParseToken;

typedef Dz1Error (*Dz1ShellParseEmitFuncA)(void *ptr, Dz1ShellParseToken type, str_t token);

DZ1_CPPLINK str_t Dz1ShellParseA_word(str_t dst, str_t src, bool_t parseESCLetter, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1ShellParseA(str_t text, bool_t includeCotateLetter, bool_t parseESCLetter, Dz1ShellParseEmitFuncA func, void *funcArg, Dz1Error *err);
#ifndef UNIX_SYSTEM
typedef Dz1Error (*Dz1ShellParseEmitFuncW)(void *ptr, Dz1ShellParseToken type, wstr_t token);

DZ1_CPPLINK wstr_t Dz1ShellParseW_word(wstr_t dst, wstr_t src, bool_t parseESCLetter, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1ShellParseW(wstr_t text, bool_t includeCotateLetter, bool_t parseESCLetter, Dz1ShellParseEmitFuncW func, void *funcArg, Dz1Error *err);
#endif

#endif
