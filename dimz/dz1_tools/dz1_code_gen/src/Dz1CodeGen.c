#include <dz1_str.h>
#include "Dz1CodeGen.h"

Dz1CodeGenReplaceList *Dz1CodeGenReplaceList_generate(Dz1CodeGenReplaceEnt arr[], Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1CodeGenReplaceList *ret = Dz1CodeGenReplaceList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1CodeGenReplaceEnt *i, *node = NULL;;
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&ret);
		for (i = arr; i->target != NULL && errp->code == 0; i++)
		{
			if ((node = Dz1CodeGenReplaceEnt_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1CodeGenReplaceEnt_delAndSetNull, (void *)&node);
				if ((*errp = ret->add(ret, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1CodeGenReplaceEnt_delAndSetNull, (void *)&node);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1CodeGenReplaceEnt *_find_node(Dz1CodeGenReplaceList *list, str_t name)
{
	Dz1CodeGenReplaceEnt key = { name, NULL };
	return list->find(list, &key);
}

Dz1Error _replace_line(char buf[1024], str_t fmt_line, Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	char *dp = buf, *cp = fmt_line;
	buf[0] = '\0';
	while(*cp && errp->code == 0)
	{
		if (*cp != '$') *dp++ = *cp++;
		else
		{	// $를 만나면
			Dz1CodeGenReplaceEnt *node = NULL;
			char target[255] = { 0, }, *tp = target;
			cp++;	// $ 치우고
			while(*cp && *cp != '$')
				*tp++ = *cp++;
			cp++;	// $ 치우고
			if ((node = _find_node(list, target)) == NULL)
			{
				Dz1Thread_printf(Dz1Text("!!! Unknown string = %s\n"), target);
				ERR_SET_OUT(errp, ENOENT);
			}
			else
			{
				size_t len = strlen(node->replace);
				strcpy(dp, node->replace); dp+= len;
			}
		}
	}
	*dp++ = '\0';

	return err;
}

str_t Dz1CodeGen_replace(str_t fmt_arr[], Dz1CodeGenReplaceList *list, Dz1Error *err)
{
	str_t ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	str_t *i;
	size_t size = 0;
	char buf[1024];

	for (i = fmt_arr; *i != NULL && errp->code == 0; i++)
	{
		if ((*errp = _replace_line(buf, *i, list)).code) ERR_OUT_RET(errp, NULL);
		else size += strlen(buf);
	}

	if ((ret = (str_t)Dz1Malloc(size + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *dp = ret;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&ret);
		for (i = fmt_arr; *i != NULL && errp->code == 0; i++)
		{
			if ((*errp = _replace_line(buf, *i, list)).code) ERR_OUT(errp);
			else 
			{
				size = strlen(buf);
				memcpy(dp, buf, size); dp += size;
			}
		}
		*dp++ = '\0';
		pthread_cleanup_pop(errp->code); // (Dz1Str_delAndSetNull, (void *)&ret);
	}

	return ret;
}

Dz1Error Dz1CodeGen_replacef(FILE *dst, str_t fmt_arr[], Dz1CodeGenReplaceList *list)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	str_t *i;
	size_t size = 0;
	ssize_t sz = 0;
	char buf[1024];

	for (i = fmt_arr; *i != NULL && errp->code == 0; i++)
	{
		if ((*errp = _replace_line(buf, *i, list)).code) ERR_OUT(errp);
		else
		{
			size += strlen(buf);
			if ((sz = (ssize_t)fwrite(buf, sizeof(char), size, dst)) < 0)
			{
				if (feof(dst)) ERR_SET_OUT(errp, EPIPE);
				else ERR_SET_OUT(errp, ferror(dst));
			}
			else if (sz == 0) ERR_SET_OUT(errp, EPIPE);
		}
	}

	return err;
}

str_t Dz1CodeGenReplaceList_getStr(Dz1CodeGenReplaceList *list, str_t name)
{
	Dz1CodeGenReplaceEnt key = { name }, *node = list->find(list, &key);
	if (node != NULL) return node->replace;
	else return NULL;
}

