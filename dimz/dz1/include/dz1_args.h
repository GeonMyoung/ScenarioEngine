#ifndef DZ1_ARGS_H
#define DZ1_ARGS_H

#include <dz1_error.h>

typedef Dz1Error (*Dz1ArgProcFunc)(void *user_ptr, str_t baseName, int argc, char *argv[]);
typedef struct Dz1Args
{
	str_t name;					// Option name
	__DZ1ALIGN(int, consume);	// number of argument include option name to be processed
	Dz1ArgProcFunc func;		// processing function
	str_t *help;				// help messages of this option that NULL terminated string array
} Dz1Args;

#define Dz1ArgsEntry(optStr, consumeInt, parseFunc, helpFunc)		{ (optStr), (consumeInt), { 0, }, (parseFunc), (helpFunc) } 
#define Dz1ArgsTermEntry	{ NULL }

typedef struct Dz1Param
{
	__DZ1ALIGN(int, argc);
	char **argv;
} Dz1Param;

/*
 * Dz1Param_new : Create Argument Information "Dz1Param" structure
 *
 * @argc : number of element of argv
 * @argv : array of string
 * @err : result of execution
 *
 * return : Address if Dz1Args structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Param	*Dz1Param_new(int argc, char *argv[], Dz1Error *err);

/*
 * Dz1Param_del : Delete Dz1Param structure
 *
 * @p : address of Dz1Param structure that created by Dz1Param_new function
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1Param_del(Dz1Param *p);

/*
 * Dz1Param_proc : Perform Argument Process
 *
 * @p : Argument Data to processing
 * @opt : Processing Info to processing
 * @baseName : name of process. it is argv[0] passed from main function
 * @userPtr : User Data for argument processing
 *
 * return : Dz1Error structure
 *
 * NOTE : after this function call, p->argc is number of remain args and p->argv keeping not used to processing
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Param_proc(Dz1Param *p, Dz1Args *opt, str_t baseName, void *userPtr);

DZ1_CPPLINK DZ1_DLLPORT void		 Dz1Args_help(Dz1Args *opt, str_t basename, str_t nonOptionedArguments, int tab);

#endif
