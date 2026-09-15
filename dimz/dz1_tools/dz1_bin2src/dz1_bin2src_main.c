#include <dz1_str.h>
#include <dz1_args.h>
#include <dz1_thread_stdio.h>

typedef struct Bin2SrcEnv
{
	int headerOnly;
	int sourceOnly;
	str_t sourcename;
	str_t targetname;
	str_t variablename;
} Bin2SrcEnv;

static void Bin2SrcEnv_cleanup(void *ptr)
{
	Bin2SrcEnv *p = (Bin2SrcEnv *)ptr;
	if (p->sourcename) Dz1Str_del(p->sourcename);
	if (p->targetname) Dz1Str_del(p->targetname);
	if (p->variablename) Dz1Str_del(p->variablename);
}

static __inline__ void Bin2SrcEnv_dump(Bin2SrcEnv *p, int tab)
{
	if (!p) return;
	if (p->headerOnly != p->sourceOnly)
		Dz1Thread_tprintf(tab, "%s\n", p->headerOnly ? "Output Header Only" : "Output Source Only");
	else
		Dz1Thread_tprintf(tab, "Output Source & Header\n");
	Dz1Thread_tprintf(tab, "Source Binary = %s\n", p->sourcename);
	Dz1Thread_tprintf(tab, "Target File = %s\n", p->targetname);
	Dz1Thread_tprintf(tab, "Variable Name = %s\n", p->variablename);
}

static Dz1Error SetOutputSource(void *ptr, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Bin2SrcEnv *p = (Bin2SrcEnv *)ptr;
	p->sourceOnly = 1;
	return err;
}

static Dz1Error SetOutputHeader(void *ptr, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Bin2SrcEnv *p = (Bin2SrcEnv *)ptr;
	p->headerOnly = 1;
	return err;
}

static Dz1Error SetOutputFilename(void *ptr, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Bin2SrcEnv *p = (Bin2SrcEnv *)ptr;
	p->targetname = Dz1Str_dup(argv[1], &err);
	return err;
}

static Dz1Error SetVariableName(void *ptr, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Bin2SrcEnv *p = (Bin2SrcEnv *)ptr;
	p->variablename = Dz1Str_dup(argv[1], &err);
	return err;
}

str_t SetOutputSourceHelp[] =
{
	"Source File Only",
	NULL
};

str_t SetOutputHeaderHelp[] =
{
	"Header File Only",
	NULL
};

str_t SetOutputFilenameHelp[] =
{
	"Set Output Filename",
	NULL
};

str_t SetVariableNameHelp[] =
{
	"Set Variable Name",
	NULL
};

static Dz1Args args[] =
{
	{
		.name = "--source",
		.consume = 1,
		.func = SetOutputSource,
		.help = SetOutputSourceHelp
	},
	{
		.name = "--header",
		.consume = 1,
		.func = SetOutputHeader,
		.help = SetOutputHeaderHelp
	},
	{
		.name = "--output",
		.consume = 2,
		.func = SetOutputFilename,
		.help = SetOutputFilenameHelp
	},
	{
		.name = "--var",
		.consume = 2,
		.func = SetVariableName,
		.help = SetVariableNameHelp
	},
	Dz1ArgsTermEntry
};


int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (argc == 1) Dz1Args_help(args, argv[0], "<filename>", 0);
	else
	{
		Bin2SrcEnv env = { 0, 0, NULL, NULL, NULL };
		Dz1Param *param = Dz1Param_new(argc - 1, &argv[1], &err);

		pthread_cleanup_push((Dz1CancelFunc)Bin2SrcEnv_cleanup, (void *)&env);

		if (param == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1CancelFunc)Dz1Param_del, (void *)param);

			if ((err = Dz1Param_proc(param, args, argv[0], &env)).code)
				Dz1Args_help(args, argv[0], "<filename>", 0);
			else if (param->argc != 1)
				Dz1Args_help(args, argv[0], "<filename>", 0);
			else
			{
				env.sourcename = Dz1Str_dup(param->argv[0], NULL);
				//if (env.targetname == NULL) env.targetname = mkTargetName(param->argv[0], &err);
				//if (env.targetname == NULL) env.targetname = Dz1Str_dup(param->argv[0], NULL);
				if (env.targetname == NULL) env.targetname = mkVariableName(param->argv[0], &err);
				if (env.variablename == NULL) env.variablename = mkVariableName(param->argv[0], &err);
				if ((err = execute(&env)).code) ERR_OUT(&err);
			}

			pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1Param_del, (void *)param);
		}
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)Bin2SrcEnv_cleanup, (void *)&env);
	}

	return err.code;
}
