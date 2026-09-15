
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_args.h>

static Dz1Args *Dz1Args_find(Dz1Args *arr, str_t name)
{
	Dz1Args *i;
	for (i = arr; i->name != NULL; i++)
		if (strncmp(name, i->name, strlen(i->name)) == 0) return i;
	return NULL;
}

static void Dz1Param_delAndSetNull(void *ptr)
{
	Dz1Param **p = (Dz1Param **)ptr;
	Dz1Param_del(*p); *p = NULL;
}

Dz1Param *Dz1Param_new(int argc, char *argv[], Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Param *ret = (Dz1Param *)Dz1Malloc(sizeof(Dz1Param), errp);
	if (ret)
	{
		pthread_cleanup_push(Dz1Param_delAndSetNull, (void *)&ret);
		ret->argc = argc;
		if ((ret->argv = (char **)Dz1Malloc(sizeof(char *) * ret->argc, errp)))
		{
			int i;
			for (i = 0; i < ret->argc; i++)
			{
				if ((ret->argv[i] = (str_t)Dz1Malloc(strlen(argv[i]) + 1, errp)) == NULL)
				{
					Dz1Error_setWithComment(errp, ENOMEM, (DZ1_ERROR_ARG, "arc=%d", i));
					break;
				}
				else strcpy(ret->argv[i], argv[i]);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Param_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Param_del(Dz1Param *p)
{
	if (p == NULL) return;
	if (p->argv)
	{
		int i;
		for (i = 0; i < p->argc; i++) Dz1Free(p->argv[i]);
		Dz1Free(p->argv);
	}
	Dz1Free(p);
}

static void largv_cancel(void *ptr)
{
	char **p = (char **)ptr;
	if (p)
	{
		while(*p) Dz1Free(*p++);
		Dz1Free(ptr);
	}
}

static Dz1Error _Dz1Param_proc(Dz1Args *opt, int argc, char *argv[], int *nargc, char **nargv, char *baseName, void *userPtr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int i;

	Dz1Args *arg = NULL;

	*nargc = 0;
	for (i = 0; i < argc; i++)
	{
		if ((arg = Dz1Args_find(opt, argv[i])))
		{
			char **largv = NULL;
			if (argc - i < arg->consume) { Dz1Error_setWithComment(&err, EINVAL, (DZ1_ERROR_ARG, "argv = %s\n", arg->name)); }
			else if ((largv = (char **)Dz1Calloc(sizeof(char *), (arg->consume + 1), &err)))
			{
				int j;

				pthread_cleanup_push(largv_cancel, (void *)largv);

				//for (j = i; j < i + arg->consume; j++)
				for (j = 0; j < arg->consume; j++) largv[j] = argv[i + j];
				i += arg->consume - 1;
				if ((err = arg->func(userPtr, baseName, arg->consume, largv)).code) break;

				pthread_cleanup_pop(1); // (largv_cancel, (void *)largv);
			}
		}
		else { *nargv++ = argv[i]; argv[i] = NULL; (*nargc)++; }
	}

	return err;
}

Dz1Error Dz1Param_proc(Dz1Param *p, Dz1Args *opt, str_t baseName, void *userPtr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	int nargc = 0;
	char **nargv = NULL;

	if ((nargv = (char **)Dz1Malloc(sizeof(char *) * p->argc, &err)))
	{
		int nargv_del = TRUE;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)nargv);
		if ((err = _Dz1Param_proc(opt, p->argc, p->argv, &nargc, nargv, baseName, userPtr)).code == 0)
		{
			p->argc = nargc;
			Dz1Free(p->argv);
			p->argv = nargv;
			nargv_del = FALSE;
		}
		pthread_cleanup_pop(nargv_del); // (DzBuffer_cancel, (void *)temp);
	}
	return err;
}

static int isProcessed(Dz1Args *opt, Dz1Args *pos)
{
	Dz1Args *i;
	for (i = pos; i >= opt; i--)
		if (pos->func == i->func && i != pos) return TRUE;
	return FALSE;
}

static void Dz1Args_helpOptList(Dz1Args *opt)
{
	Dz1Args *i, *j;
	for (i = opt; i->name; i++)
	{
		if (!isProcessed(opt, i))
		{
			int printed = 0;
			Dz1ArgProcFunc func = i->func;
			Dz1Thread_tprintf(0, " [");
			for (j = i; j->name; j++)
			{
				if (func == j->func)
				{
					if (printed) Dz1Thread_tprintf(0, "|");
					Dz1Thread_tprintf(0, "%s", j->name);
					printed = 1;
				}
			}
			Dz1Thread_tprintf(0, "]");
		}
	}
}

static void Dz1Args_helpOptEntry(Dz1Args *opt, int tab)
{
	Dz1Args *i, *j;
	str_t *h;
	for (i = opt; i->name; i++)
	{
		if (!isProcessed(opt, i))
		{
			int printed = 0;
			Dz1ArgProcFunc func = i->func;
			for (j = i; j->name; j++)
			{
				if (func == j->func)
				{
					if (printed) Dz1Thread_tprintf(0, "|%s", j->name);
					else Dz1Thread_tprintf(tab, "%s", j->name);
					printed = 1;
				}
			}
			Dz1Thread_tprintf(0, "\n");
			for (h = i->help; *h; h++)
				Dz1Thread_tprintf(tab + 1, "%s\n", *h);
		}
	}
}

void Dz1Args_help(Dz1Args *opt, str_t basename, str_t nonOptionedArguments, int tab)
{
	Dz1Thread_tprintf(tab, "Usage] %s", basename);
	Dz1Args_helpOptList(opt);
	if (nonOptionedArguments)
		Dz1Thread_tprintf(0, " %s\n", nonOptionedArguments);
	else
		Dz1Thread_tprintf(0, "\n");
	Dz1Args_helpOptEntry(opt, tab + 1);
}

