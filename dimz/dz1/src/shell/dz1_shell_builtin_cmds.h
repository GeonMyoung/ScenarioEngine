#ifndef DZ1_SHELL_BUILTIN_CMD_H
#define DZ1_SHELL_BUILTIN_CMD_H

#include "dz1_shell.h"

DZ1_CPPLINK Dz1Error Dz1ShellBuiltinCmdInitA(Dz1ShellA *p, u32_t cmdFlag);
DZ1_CPPLINK bool_t	 Dz1ShellBuiltinCmdA_setLogFlag(u32_t flag, const str_t full_name, const str_t short_name);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK Dz1Error Dz1ShellBuiltinCmdInitW(Dz1ShellW *p, u32_t cmdFlag);
DZ1_CPPLINK bool_t	 Dz1ShellBuiltinCmdW_setLogFlag(u32_t flag, const wstr_t full_name, const wstr_t short_name);
#endif

#endif
