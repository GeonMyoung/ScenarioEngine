#include <dz1_stdio.h>
 #include <dz1_str.h>
 #include <dz1_malloc.h>
 #include <dz1_fifo.h>
 #include <dz1_thread_stdio.h>

#include "Dz1TdcInfoIncludeSpec.h"

//#include "misc.h"
static FILE *file_open(str_t include, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FILE *ret = Dz1FileStream_open(name, "r+b", errp);
	if (ret == NULL)
	{
		if (include == NULL) { }
		else
		{
			char filename[4096];
			int len = sprintf(filename, "%s", include);
			char *cp = filename + len - 1;

			Dz1Error_set(errp, 0);

			if (*cp != DIR_SEP) cp++;
			*cp++ = DIR_SEP;

			strcpy(cp, name);

			if ((ret = Dz1FileStream_open(filename, "r+b", errp)) == NULL)
			{
				ERR_OUT(errp);
				Dz1Thread_printf("file_open() : No such file : %s\n", filename);
			}
		}
	}
	return ret;
}

static str_t file_load(str_t include, str_t name, Dz1Error *err)
{
	str_t ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	FILE *fp = NULL;
	if ((fp = file_open(include, name, errp)) != NULL)
	{
		long size = 0;

		pthread_cleanup_push((Dz1DelFunc)fclose, (void *)fp);

		if (fseek(fp, 0, SEEK_END) < 0) { Dz1Error_set(errp, errno); }
		else if ((size = ftell(fp)) < 0) { Dz1Error_set(errp, errno); }
		else if (fseek(fp, 0, SEEK_SET) < 0) { Dz1Error_set(errp, errno); }
		else if ((ret = (str_t)Dz1Calloc(size + 1, 1, errp)) == NULL) { }
		else
		{
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
			if (fread(ret, size, 1, fp) == 0) { Dz1Error_set(errp, EPIPE); }
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)fclose, (void *)fp);
	}
	return ret;
}

static str_t _includeSpec_load(IncludeSpec *p, str_t name, Dz1Error *err)
{
	str_t ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (IncludeSpec_count(p) == 0) ERR_SET_OUT(errp, ENOENT);
	else
	{
		void *c = Dz1FifoCursor_new(p->pathFifo, errp);
		if (c == NULL) ERR_OUT(errp);
		else
		{
			char fn[4096];
			str_t path = NULL;
			pthread_cleanup_push(Dz1FifoCursor_del, c);
			for (Dz1FifoCursorForward(c))
			{
				path = (str_t)Dz1FifoCursor_data(c);
				sprintf(fn, "%s" DIR_SEPRATOR "%s", path, name);
				//Dz1Thread_printf("IncludeSpec_load() : Trying \"%s\"\n", fn);
				if ((ret = file_load(NULL, fn, errp)) != NULL) { Dz1Error_set(errp, 0); break; }
			}
			pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
		}
	}
	return ret;
}
static str_t IncludeSpec_load(IncludeSpec *p, str_t name, Dz1Error *err)
{
	str_t ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((ret = file_load(NULL, name, errp)) == NULL)
	{
		if ((ret = _includeSpec_load(p, name, errp)) == NULL) ERR_OUT(errp);
	}
	
	return ret;
}

static bool_t IncludeSpec_add(IncludeSpec *p, str_t path, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t e;
	if ((e = Dz1Str_dup(path, errp)) == NULL) ERR_OUT(errp);
	else
	{
		int len;
		char *cp = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1Str_del, (void *)e);

		len = (int)strlen(e);
		cp = e + len - 1;
		if (*cp == DIR_SEP) *cp = '\0';

		if ((*errp = Dz1Fifo_push(p->pathFifo, e)).code) ERR_OUT(errp);

		pthread_cleanup_pop(errp->code); // ((Dz1DelFunc)Dz1Str_del, (void *)e);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

IncludeSpec *IncludeSpec_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	IncludeSpec *ret = (IncludeSpec *)Dz1Calloc(sizeof(IncludeSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IncludeSpec_delAndSetNull, (void *)&ret);
		ret->add = IncludeSpec_add;
		ret->load = IncludeSpec_load;
		if ((ret->pathFifo = Dz1Fifo_new((Dz1DelFunc)Dz1Str_del, (Dz1DumpFunc)Dz1Str_dump, 0, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (IncludeSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void IncludeSpec_del(IncludeSpec *p)
{
	if (!p) return;
	if (p->pathFifo) Dz1Fifo_del(p->pathFifo);
	Dz1Free(p);
}

void IncludeSpec_dump(IncludeSpec *p, int tab)
{
	if (!p) return;
	Dz1Fifo_dump(p->pathFifo, tab);
}

u32_t IncludeSpec_count(IncludeSpec *p)
{
	u32_t ret = 0;
	if (p != NULL)
	{
		ret = Dz1Fifo_count(p->pathFifo);
	}
	return ret;
}

typedef struct GetPathOfFileArg
{
	str_t fn;
	str_t ret;
} GetPathOfFileArg;

static Dz1Error _getPathOfFile(void *ptr, void *_data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t path = (str_t)_data;
	GetPathOfFileArg *arg = (GetPathOfFileArg *)ptr;
	if (Dz1File_isExist2(path, arg->fn))
	{
		arg->ret = path;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

str_t IncludeSpec_getPathOfFile(IncludeSpec *p, str_t fn)
{
	str_t ret = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	GetPathOfFileArg arg = { fn, NULL };
	if ((*errp = Dz1Fifo_travel(p->pathFifo, _getPathOfFile, (void *)fn)).code == 0) Dz1Error_set(errp, ENOENT);
	else if (errp->code == EEXIST)
	{
		ret = arg.ret;
		Dz1Error_set(errp, 0);
	}

	return ret;
}
