#ifndef DZ1_SHELL_LOCAL_H
#define DZ1_SHELL_LOCAL_H

#include <ctype.h>

#include <dz1_shell.h>

#include "dz1_shell_var.h"
#include "dz1_shell_history.h"
#include "dz1_shell_cmd.h"
#include "dz1_shell_input.h"

#define DZ1_SHELL_BUFFER_SIZE			65535

#define DZ1_SHELL_NAME_A		"dz1sh"
typedef struct Dz1ShellA
{
	str_t				 user;
	str_t				 systemName;
	Dz1ShellInputA		 input;
	char				 buf[DZ1_SHELL_BUFFER_SIZE];
	Dz1ShellVarA		*env;
	Dz1ShellVarA		*alias;
	Dz1ShellHistoryA	*history;
	Dz1ShellCmdA		*cmd;
} Dz1ShellA;

#ifndef UNIX_SYSTEM
#define DZ1_SHELL_NAME_W		L"dz1sh"
typedef struct Dz1ShellW
{
	wstr_t				 user;
	wstr_t				 systemName;
	Dz1ShellInputW		 input;
	wchar_t				 buf[DZ1_SHELL_BUFFER_SIZE];
	Dz1ShellVarW		*env;
	Dz1ShellVarW		*alias;
	Dz1ShellHistoryW	*history;
	Dz1ShellCmdW		*cmd;
} Dz1ShellW;
#endif

#endif
