#ifndef DZ1_SHELL_ARGS_H
#define DZ1_SHELL_ARGS_H

#include <dz1_error.h>

typedef struct Dz1ShellArgsA
{
	int argc;
	str_t *argv;
	str_t buf;
} Dz1ShellArgsA;

DZ1_CPPLINK Dz1ShellArgsA *Dz1ShellArgsA_new(str_t text, Dz1Error *err);
DZ1_CPPLINK void Dz1ShellArgsA_del(Dz1ShellArgsA *p);
DZ1_CPPLINK void Dz1ShellArgsA_dump(Dz1ShellArgsA *p, int tab);

static __inline__ void Dz1ShellArgsA_delAndSetNull(void *ptr)
{
	Dz1ShellArgsA **p = (Dz1ShellArgsA **)ptr;
	Dz1ShellArgsA_del(*p); *p = NULL;
}
#ifndef UNIX_SYSTEM
typedef struct Dz1ShellArgsW
{
	int argc;
	wstr_t *argv;
	wstr_t buf;
} Dz1ShellArgsW;

DZ1_CPPLINK Dz1ShellArgsW *Dz1ShellArgsW_new(wstr_t text, Dz1Error *err);
DZ1_CPPLINK void Dz1ShellArgsW_del(Dz1ShellArgsW *p);
DZ1_CPPLINK void Dz1ShellArgsW_dump(Dz1ShellArgsW *p, int tab);

static __inline__ void Dz1ShellArgsW_delAndSetNull(void *ptr)
{
	Dz1ShellArgsW **p = (Dz1ShellArgsW **)ptr;
	Dz1ShellArgsW_del(*p); *p = NULL;
}
#endif
#endif
