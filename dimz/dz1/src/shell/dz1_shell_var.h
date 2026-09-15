#ifndef DZ1_SHELL_VAR_H
#define DZ1_SHELL_VAR_H

#include <dz1_error.h>

typedef struct Dz1ShellVarEntryA
{
	str_t name;
	str_t value;
} Dz1ShellVarEntryA;

typedef struct Dz1ShellVarA
{
	void *tree;
	Dz1Error (*insert)(struct Dz1ShellVarA *p, str_t name, str_t value);
	void (*remove)(struct Dz1ShellVarA *p, str_t name);
	str_t (*find)(struct Dz1ShellVarA *p, str_t name);
} Dz1ShellVarA;

DZ1_CPPLINK Dz1ShellVarA *Dz1ShellVarA_new(Dz1Error *err);
DZ1_CPPLINK void Dz1ShellVarA_del(Dz1ShellVarA *p);
DZ1_CPPLINK void Dz1ShellVarA_dump(Dz1ShellVarA *p, int tab);

static __inline__ void Dz1ShellVarA_delAndSetNull(void *ptr)
{
	Dz1ShellVarA **p = (Dz1ShellVarA **)ptr;
	Dz1ShellVarA_del(*p); *p = NULL;
}

#ifndef UNIX_SYSTEM
typedef struct Dz1ShellVarEntryW
{
	wstr_t name;
	wstr_t value;
} Dz1ShellVarEntryW;

typedef struct Dz1ShellVarW
{
	void *tree;
	Dz1Error (*insert)(struct Dz1ShellVarW *p, wstr_t name, wstr_t value);
	void (*remove)(struct Dz1ShellVarW *p, wstr_t name);
	wstr_t (*find)(struct Dz1ShellVarW *p, wstr_t name);
} Dz1ShellVarW;

DZ1_CPPLINK Dz1ShellVarW *Dz1ShellVarW_new(Dz1Error *err);
DZ1_CPPLINK void Dz1ShellVarW_del(Dz1ShellVarW *p);
DZ1_CPPLINK void Dz1ShellVarW_dump(Dz1ShellVarW *p, int tab);

static __inline__ void Dz1ShellVarW_delAndSetNull(void *ptr)
{
	Dz1ShellVarW **p = (Dz1ShellVarW **)ptr;
	Dz1ShellVarW_del(*p); *p = NULL;
}
#endif

#endif
