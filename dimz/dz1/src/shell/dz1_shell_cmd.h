#ifndef DZ1_SHELL_CMD_H
#define DZ1_SHELL_CMD_H

#include <dz1_error.h>
#include <dz1_shell.h>

///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdEntryA
typedef struct Dz1ShellCmdEntryA
{
	str_t				 name;
	Dz1ShellCmdFuncA	 func;
	void				*funcParam;
	str_t				 help;
} Dz1ShellCmdEntryA;

DZ1_CPPLINK Dz1ShellCmdReturn Dz1ShellCmdEntryA_execute(Dz1ShellCmdEntryA *p, int argc, char *argv[]);
// Dz1ShellCmdEntryA
///////////////////////////////////////////////////////////////////////////////
#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdEntryA
typedef struct Dz1ShellCmdEntryW
{
	wstr_t				 name;
	Dz1ShellCmdFuncW	 func;
	void				*funcParam;
	wstr_t				 help;
} Dz1ShellCmdEntryW;

DZ1_CPPLINK Dz1ShellCmdReturn Dz1ShellCmdEntryW_execute(Dz1ShellCmdEntryW *p, int argc, wchar_t *argv[]);
// Dz1ShellCmdEntryA
///////////////////////////////////////////////////////////////////////////////
#endif
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdListA
typedef struct Dz1ShellCmdListA
{
	void *fifo;
	Dz1Error (*push)(struct Dz1ShellCmdListA *p, Dz1ShellCmdEntryA *e);
	Dz1ShellCmdEntryA *(*pop)(struct Dz1ShellCmdListA *p, Dz1Error *err);
} Dz1ShellCmdListA;

DZ1_CPPLINK void Dz1ShellCmdListA_del(Dz1ShellCmdListA *p);
DZ1_CPPLINK void Dz1ShellCmdListA_dump(Dz1ShellCmdListA *p, int tab);

static __inline__ void Dz1ShellCmdListA_delAndSetNull(void *ptr)
{
	Dz1ShellCmdListA **p = (Dz1ShellCmdListA **)ptr;
	Dz1ShellCmdListA_del(*p); *p = NULL;
}
// Dz1ShellCmdListA
///////////////////////////////////////////////////////////////////////////////
#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdListW
typedef struct Dz1ShellCmdListW
{
	void *fifo;
	Dz1Error (*push)(struct Dz1ShellCmdListW *p, Dz1ShellCmdEntryW *e);
	Dz1ShellCmdEntryW *(*pop)(struct Dz1ShellCmdListW *p, Dz1Error *err);
} Dz1ShellCmdListW;

DZ1_CPPLINK void Dz1ShellCmdListW_del(Dz1ShellCmdListW *p);
DZ1_CPPLINK void Dz1ShellCmdListW_dump(Dz1ShellCmdListW *p, int tab);

static __inline__ void Dz1ShellCmdListW_delAndSetNull(void *ptr)
{
	Dz1ShellCmdListW **p = (Dz1ShellCmdListW **)ptr;
	Dz1ShellCmdListW_del(*p); *p = NULL;
}
// Dz1ShellCmdListW
///////////////////////////////////////////////////////////////////////////////
#endif
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdA
typedef struct Dz1ShellCmdA
{
	void *tree;
	Dz1Error (*insert)(struct Dz1ShellCmdA *p, str_t name, Dz1ShellCmdFuncA func, void *funcParam, str_t help);
	void (*remove)(struct Dz1ShellCmdA *p, str_t name);
	Dz1ShellCmdEntryA *(*find)(struct Dz1ShellCmdA *p, str_t name);
	Dz1ShellCmdListA *(*like)(struct Dz1ShellCmdA *p, str_t name, Dz1Error *err);
} Dz1ShellCmdA;

DZ1_CPPLINK Dz1ShellCmdA *Dz1ShellCmdA_new(Dz1Error *err);
DZ1_CPPLINK void Dz1ShellCmdA_del(Dz1ShellCmdA *p);
DZ1_CPPLINK void Dz1ShellCmdA_dump(Dz1ShellCmdA *p, int tab);

static __inline__ void Dz1ShellCmdA_delAndSetNull(void *ptr)
{
	Dz1ShellCmdA **p = (Dz1ShellCmdA **)ptr;
	Dz1ShellCmdA_del(*p); *p = NULL;
}
// Dz1ShellCmdA
///////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdW
typedef struct Dz1ShellCmdW
{
	void *tree;
	Dz1Error (*insert)(struct Dz1ShellCmdW *p, wstr_t name, Dz1ShellCmdFuncW func, void *funcParam, wstr_t help);
	void (*remove)(struct Dz1ShellCmdW *p, wstr_t name);
	Dz1ShellCmdEntryW *(*find)(struct Dz1ShellCmdW *p, wstr_t name);
	Dz1ShellCmdListW *(*like)(struct Dz1ShellCmdW *p, wstr_t name, Dz1Error *err);
} Dz1ShellCmdW;

DZ1_CPPLINK Dz1ShellCmdW *Dz1ShellCmdW_new(Dz1Error *err);
DZ1_CPPLINK void Dz1ShellCmdW_del(Dz1ShellCmdW *p);
DZ1_CPPLINK void Dz1ShellCmdW_dump(Dz1ShellCmdW *p, int tab);

static __inline__ void Dz1ShellCmdW_delAndSetNull(void *ptr)
{
	Dz1ShellCmdW **p = (Dz1ShellCmdW **)ptr;
	Dz1ShellCmdW_del(*p); *p = NULL;
}
// Dz1ShellCmdW
///////////////////////////////////////////////////////////////////////////////
#endif
#endif
