#include <dz1_str.h>
#include <dz1_stdio.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>

#include "misc.h"

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

str_t file_load(str_t include, str_t name, Dz1Error *err)
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
			if (fread(ret, size, 1, fp) == 0)
			{
				if (size == 0) Dz1Error_set(errp, 0);
				else Dz1Error_set(errp, EPIPE);
			}
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)fclose, (void *)fp);
	}
	return ret;
}

str_t mkBaseName(char dst[1024], char *src)
{
	int len = (int)strlen(src), size = 0;
	char *cp = src + len - 1;
	if (*cp == DIR_SEP) cp--;
	while(cp >= src && *cp != DIR_SEP) { cp--; size++; }
	cp++;
	memcpy(dst, cp, size);
	dst[size] = '\0';
	return dst;
}

static Dz1Error _addPresent2Enum(void *ptr, UnionMemberEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	ObjectInfo *presentObj = (ObjectInfo *)ptr;
	EnumInfo *enumInfo = (EnumInfo *)presentObj->info;
	EnumList *enums = enumInfo->enums;

	s32_t v = 0;
 	if ((*errp = enums->add(enums, p->instance, p->presentStr, &v)).code) ERR_OUT(errp);

	return err;
}
Dz1Error ParserHelp_addPresentObj(Dz1MdefcModule *module, ObjectInfo *obj)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (obj->type == ObjectType_union)
	{
		UnionInfo *unionInfo = (UnionInfo *)obj->info;
		char name[1024];
		ObjectInfo *presentObj = NULL;
		
		sprintf(name, "%sPresent", obj->name);
		if ((presentObj = ObjectInfo_new(ObjectType_enumerate, name, NULL, (OBJECT_API_BASE | obj->api) & (~OBJECT_API_ASN_CONV), NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			EnumInfo *enumInfo = NULL;
			pthread_cleanup_push(ObjectInfo_delAndSetNull, (void *)&presentObj);
			if ((presentObj->info = enumInfo = EnumInfo_new(TRUE, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = unionInfo->members->travel(unionInfo->members, _addPresent2Enum, (void *)presentObj)).code) ERR_OUT(errp);
			else if ((*errp = module->addObject(module, presentObj)).code) ERR_OUT(errp);
			else
			{
				presentObj = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (ObjectInfo_delAndSetNull, (void *)&presentObj);
		}
	}
	return err;
}

Dz1AATree *Dz1TdcStringList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1AATree *ret = NULL;
	if ((ret = Dz1AATree_new((Dz1CmpFunc)strcmp, (Dz1DelFunc)Dz1Str_del, (Dz1DumpFunc)Dz1Str_dump, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

bool_t Dz1TdcStringList_add(Dz1AATree *dst, Dz1Str str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str temp = Dz1Str_dup(str, errp);
	if (temp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&temp);
		if ((*errp = Dz1AATree_insert(dst, temp)).code) ERR_OUT(errp);
		else
		{
			temp = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
