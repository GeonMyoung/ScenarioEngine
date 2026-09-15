#ifndef DZ1_CODE_GEN_H_LOCAL
#define DZ1_CODE_GEN_H_LOCAL

#include <Dz1CodeGen.h>

#define _CRLF		"\r\n"

#define Dz1CodeGenReplaceEntry(name)		{ #name, name }
#define Dz1CodeGenReplaceEntryAlloc(name)	{ #name, NULL }
#define	Dz1CodeGenReplaceEnt_last		{ NULL, NULL }

DZ1_CPPLINK Dz1CodeGenReplaceList *Dz1CodeGenReplaceList_generate(Dz1CodeGenReplaceEnt arr[], Dz1Error *err);
DZ1_CPPLINK str_t Dz1CodeGen_replace(str_t fmt_arr[], Dz1CodeGenReplaceList *list, Dz1Error *err);
DZ1_CPPLINK Dz1Error Dz1CodeGen_replacef(FILE *dst, str_t fmt_arr[], Dz1CodeGenReplaceList *list);

DZ1_CPPLINK str_t Dz1CodeGenReplaceList_getStr(Dz1CodeGenReplaceList *list, str_t name);

#endif