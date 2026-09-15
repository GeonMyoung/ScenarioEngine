#ifndef DZ1_PARSER_H
#define DZ1_PARSER_H

#include <dz1_error.h>
#include <dz1_parser_token.h>

typedef void Dz1ParserHandle;
typedef Dz1Error (*Dz1ParserEmitFunc)(Dz1ParserToken *t, void *param);

DZ1_CPPLINK DZ1_DLLPORT Dz1ParserHandle *Dz1Parser_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Parser_del(Dz1ParserHandle *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Parser_dump(Dz1ParserHandle *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Parser_delAndSetNull(void *pptr);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Parser_addEmiter(Dz1ParserHandle *p, str_t name, Dz1ParserEmitFunc func);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Parser_prepare(Dz1ParserHandle *p, str_t text); // take text pointer to lexer

DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1Parser_getLineNum(Dz1ParserHandle *p);

// return 1 is success, 0 is fail, -1 is no match
//DZ1_CPPLINK DZ1_DLLPORT int Dz1Parser_process(void *p, str_t syntaxName, void *param, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Parser_process(Dz1ParserHandle *p, str_t syntaxName, void *param, int tab);
#endif
