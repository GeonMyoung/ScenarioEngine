#ifndef DZ1_SHELL_H
#define DZ1_SHELL_H

#include <dz1_error.h>

#define DZ1_SHELL_CMD_EXIT			0x80000000
#define DZ1_SHELL_CMD_ALIAS			0x40000000
#define DZ1_SHELL_CMD_SET			0x20000000
#define DZ1_SHELL_CMD_ECHO			0x10000000
#define DZ1_SHELL_CMD_HISTORY		0x08000000
#define DZ1_SHELL_CMD_THREAD		0x04000000

#define DZ1_SHELL_CMD_FOUNDATION	(DZ1_SHELL_CMD_HISTORY | DZ1_SHELL_CMD_THREAD)
#define DZ1_SHELL_CMD_GENERAL		(DZ1_SHELL_CMD_ALIAS | DZ1_SHELL_CMD_SET | DZ1_SHELL_CMD_ECHO)

#define DZ1_SHELL_CMD_NOEXIT		(DZ1_SHELL_CMD_FOUNDATION | DZ1_SHELL_CMD_GENERAL)
#define DZ1_SHELL_CMD_ALL			(DZ1_SHELL_CMD_FOUNDATION | DZ1_SHELL_CMD_GENERAL | DZ1_SHELL_CMD_EXIT)

//-->ldg::m:
//typedef enum
//{
//	Dz1ShellCmdReturn_ok,
//	Dz1ShellCmdReturn_nocmd,
//	Dz1ShellCmdReturn_exit,
//	Dz1ShellCmdReturn_max
//} Dz1ShellCmdReturn;

#ifndef __Dz1ShellCmdReturn__
#define __Dz1ShellCmdReturn__
typedef enum
{
	Dz1ShellCmdReturn_ok,
	Dz1ShellCmdReturn_nocmd,
	Dz1ShellCmdReturn_exit,
	Dz1ShellCmdReturn_max
} Dz1ShellCmdReturn;
#endif

//<--ldg::m:

typedef Dz1ShellCmdReturn (*Dz1ShellCmdFuncA)(void *funcParam, int argc, char *argv[]);
#ifndef UNIX_SYSTEM
typedef Dz1ShellCmdReturn (*Dz1ShellCmdFuncW)(void *funcParam, int argc, wchar_t *argv[]);
#ifndef UNICODE
#define						Dz1ShellCmdFunc		Dz1ShellCmdFuncW
#else // UNICODE
#define						Dz1ShellCmdFunc		Dz1ShellCmdFuncA
#endif // UNICODE
#else // UNIX_SYSTEM
#define						Dz1ShellCmdFunc		Dz1ShellCmdFuncA
#endif // UNIX_SYSTEM
/*
 * Dz1Shell_new : create Dz1Shell
 *
 * @termName : Terminal Name to Emulate
 * @cmdFlag : builtin command flag
 * @historySize : size of history (0 = Unlimited)
 * @user : name of shell user
 * @host : name of host system
 * @err : Address of Dz1Error structure
 *
 * return : Address of Dz1Shell
 */
DZ1_CPPLINK DZ1_DLLPORT void *Dz1ShellA_new(str_t termName, u32_t cmdFlag, u32_t historySize, str_t user, str_t host, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void *Dz1ShellW_new(wstr_t termName, u32_t cmdFlag, u32_t historySize, wstr_t user, wstr_t host, Dz1Error *err);
#ifdef UNICODE
#define						  Dz1Shell_new		Dz1ShellW_new
#else // UNICODE
#define						  Dz1Shell_new		Dz1ShellA_new
#endif // UNICODE
#else // UNIX_SYSTEM
#define						  Dz1Shell_new		Dz1ShellA_new
#endif // UNIX_SYSTEM

/*
 * Dz1Shell_del : Delete Dz1Shell
 *
 * @h : target shell
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellA_del(void *h);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellA_delAndSetNull(void *h);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1ShellA_thredCmdSetLogFlag(u32_t flag, const str_t full_name, const str_t short_name, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellW_del(void *h);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellW_delAndSetNull(void *h);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1ShellW_thredCmdSetLogFlag(u32_t flag, const wstr_t full_name, const wstr_t short_name, Dz1Error *err);
#ifdef UNICODE
#define						 Dz1Shell_del					Dz1ShellW_del
#define						 Dz1Shell_delAndSetNull			Dz1ShellW_delAndSetNull
#define						 Dz1Shell_thredCmdSetLogFlag	Dz1ShellW_thredCmdSetLogFlag
#else // UNICODE
#define						 Dz1Shell_del					Dz1ShellA_del
#define						 Dz1Shell_delAndSetNull			Dz1ShellA_delAndSetNull
#define						 Dz1Shell_thredCmdSetLogFlag	Dz1ShellA_thredCmdSetLogFlag
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1Shell_del					Dz1ShellA_del
#define						 Dz1Shell_delAndSetNull			Dz1ShellA_delAndSetNull
#define						 Dz1Shell_thredCmdSetLogFlag	Dz1ShellA_thredCmdSetLogFlag
#endif // UNIX_SYSTEM

/*
 * Dz1Shell_cmdReg : register user shell command to target shell
 *
 * @h : target shell
 * @name : name of user command
 * @func : user command function
 * @funcParam : Argument of user function
 * @descr : comment of user command
 *
 * return : Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ShellA_cmdReg(void *h, str_t name, Dz1ShellCmdFuncA func, void *funcParam, str_t descr);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ShellW_cmdReg(void *h, wstr_t name, Dz1ShellCmdFuncW func, void *funcParam, wstr_t descr);
#ifdef UNICODE
#define							 Dz1Shell_cmdReg		Dz1ShellW_cmdReg
#else // UNICODE
#define							 Dz1Shell_cmdReg		Dz1ShellA_cmdReg
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1Shell_cmdReg		Dz1ShellA_cmdReg
#endif // UNIX_SYSTEM


/*
 * Dz1Shell_cmdDereg : Deregister user command from target shell
 *
 * @h : target shell
 * @name : name of user command
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellA_cmdDereg(void *h, str_t name);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellW_cmdDereg(void *h, wstr_t name);
#ifdef UNICODE
#define						 Dz1Shell_cmdDereg		Dz1ShellW_cmdDereg
#else // UNICODE
#define						 Dz1Shell_cmdDereg		Dz1ShellA_cmdDereg
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1Shell_cmdDereg		Dz1ShellA_cmdDereg
#endif // UNIX_SYSTEM


/*
 * Dz1Shell_envSet : Append Environment Variable to target shell
 *
 * @h : target shell
 * @name : name of environment variable
 * @value : value of environment variable
 *
 * return : Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ShellA_envSet(void *h, str_t name, str_t value);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ShellW_envSet(void *h, wstr_t name, wstr_t value);
#ifdef UNICODE
#define							 Dz1Shell_envSet		Dz1ShellW_envSet
#else // UNICODE
#define							 Dz1Shell_envSet		Dz1ShellA_envSet
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1Shell_envSet		Dz1ShellA_envSet
#endif // UNIX_SYSTEM


/*
 * Dz1Shell_envUnset : Remove Environment Variable from target shell
 *
 * @h : target shell
 * @name : name of environment variable
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellA_envUnset(void *h, str_t name);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellW_envUnset(void *h, wstr_t name);
#ifdef UNICODE
#define						 Dz1Shell_envUnset		Dz1ShellW_envUnset
#else // UNICODE
#define						 Dz1Shell_envUnset		Dz1ShellA_envUnset
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1Shell_envUnset		Dz1ShellA_envUnset
#endif // UNIX_SYSTEM


/*
 * Dz1Shell_alias : Append Alias to target shell
 *
 * @h : target shell
 * @name : name of alias
 * @value : value of alias
 *
 * return : Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ShellA_alias(void *h, str_t name, str_t value);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ShellW_alias(void *h, wstr_t name, wstr_t value);
#ifdef UNICODE
#define							 Dz1Shell_alias		Dz1ShellW_alias
#else // UNICODE
#define							 Dz1Shell_alias		Dz1ShellA_alias
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1Shell_alias		Dz1ShellA_alias
#endif // UNIX_SYSTEM


/*
 * Dz1Shell_unalias : Remove Alias from target shell
 *
 * @h : target shell
 * @name : name of alias
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellA_unalias(void *h, str_t name);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellW_unalias(void *h, wstr_t name);
#ifdef UNICODE
#define						 Dz1Shell_unalias		Dz1ShellW_unalias
#else // UNICODE
#define						 Dz1Shell_unalias		Dz1ShellA_unalias
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1Shell_unalias		Dz1ShellA_unalias
#endif // UNIX_SYSTEM


/*
 * Dz1Shell_start : start Dz1Shell
 *
 * @h : shell
 * @rcFileName : RC script file name
 *
 */
#define						 Dz1Shell_no_rc		NULL
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellA_start(void *h, str_t rcFileName);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1ShellW_start(void *h, wstr_t rcFileName);
#ifdef UNICODE
#define						 Dz1Shell_start		Dz1ShellW_start
#else // UNICODE
#define						 Dz1Shell_start		Dz1ShellA_start
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1Shell_start		Dz1ShellA_start
#endif // UNIX_SYSTEM


#endif
