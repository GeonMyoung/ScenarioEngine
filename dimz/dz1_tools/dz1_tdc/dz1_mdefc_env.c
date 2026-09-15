#include <dz1_malloc.h>
#include <dz1_str.h>
#include <dz1_thread_stdio.h>

#include "dz1_mdefc_env.h"

///////////////////////////////////////////////////////////////////////////////
// Macro Stack
void Dz1MdefcMacroStack_del(Dz1MdefcMacroStack *p)
{
	if (p != NULL)
	{
		Dz1StrA_delAndSetNull(&p->name);
		Dz1Free(p);
	}
}

Dz1MdefcMacroStack *Dz1MdefcMacroStack_new(str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MdefcMacroStack *ret = NULL;
	
	if (Dz1Str_isVoid(name)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MdefcMacroStack *)Dz1Calloc(sizeof(Dz1MdefcMacroStack), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MdefcMacroStack_delAndSetNull, (void *)&ret);
		if ((ret->name = Dz1StrA_dup(name, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MdefcMacroStack_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1MdefcMacroStack_push(Dz1MdefcMacroStack **_dst, Dz1MdefcMacroStack *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (_dst == NULL || p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1MdefcMacroStack *dst = *_dst;
		p->next = dst;
		(*_dst) = p;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1MdefcMacroStack *Dz1MdefcMacroStack_pop(Dz1MdefcMacroStack **_src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MdefcMacroStack *ret = NULL, *src = NULL;
	if (_src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ( (src = *_src) == NULL) Dz1Error_set(errp, ENOENT);
	else
	{
		ret = *_src;
		(*_src) = ret->next;
		ret->next = NULL;
		Dz1Error_set(errp, 0);
	}
	return ret;
}
// Macro Stack
///////////////////////////////////////////////////////////////////////////////

ObjectInfo *Dz1MdefcParserEnv_getObject(Dz1MdefcParserEnv *p, str_t name, bool_t chkForward, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ObjectInfo *ret = p->module->findObject(p->module, name);
	if (ret == NULL)
	{
		if (chkForward)
		{
			// Dz1Thread_printf("@@@ register unknown object = %s\n", name);
			if ((ret = p->module->regUnknownObject(p->module, name, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else ERR_SET_OUT(errp, ESRCH);
	}
	return ret;
}

static bool_t _forwardDeclareFix(Dz1MdefcParserEnv *p)
{
	bool_t ret = FALSE;
	ObjectInfo *obj = NULL;
	//if ((obj = (ObjectInfo *)Dz1AATree_extract(p->undefObjects, p->obj)) != NULL)
	if ((obj = p->module->extractUnknownObject(p->module, p->obj->name, NULL)) != NULL)
	{	// Forwarded Object
		pthread_cleanup_push((Dz1DelFunc)ObjectInfo_del, (void *)p->obj);

		//Dz1Thread_printf("@@@ predefined = %08X, current = %08X\n", obj->api, p->obj->api);
		obj->type = p->obj->type;
		obj->api = p->obj->api;
		obj->info = p->obj->info; p->obj->info = NULL;

		pthread_cleanup_pop(1); // ((Dz1DelFunc)ObjectInfo_del, (void *)p->obj);

		p->obj = obj;
	}
	else
	{
		char name[1024];
		//ObjectInfo key = { 0, name };
		sprintf(name, "_declare_%s", p->obj->name);
		if ((obj = p->module->extractUnknownObject(p->module, name, NULL)) != NULL)
		{	// Forwarded Object
			pthread_cleanup_push((Dz1DelFunc)ObjectInfo_del, (void *)p->obj);

			//Dz1Thread_printf("@@@ predefined = %08X, current = %08X\n", obj->api, p->obj->api);
			Dz1Str_delAndSetNull(&obj->name);
			obj->name = p->obj->name;
			obj->type = p->obj->type;
			obj->api = p->obj->api;
			obj->info = p->obj->info; p->obj->info = NULL;

			pthread_cleanup_pop(1); // ((Dz1DelFunc)ObjectInfo_del, (void *)p->obj);

			p->obj = obj;
		}
		// else Dz1Thread_printf("@@@ No predefined object [%s]\n", name);
	}
	return ret;
}

#ifndef GLOBAL_MISC_DEF_H
static Dz1Error _addPresent2Enum(void *ptr, UnionMemberEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	ObjectInfo *presentObj = (ObjectInfo *)ptr;
	EnumInfo *enumInfo = (EnumInfo *)presentObj->info;
	EnumList *enums = enumInfo->enums;

//	char name[1024];
//	sprintf(name, "%s_%s", presentObj->name, p->instance);
	if ((*errp = enums->add(enums, p->instance, NULL, &p->presentNum)).code) ERR_OUT(errp);

	return err;
}
#endif

bool_t Dz1MdefcParserEnv_addObject(Dz1MdefcParserEnv *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p->obj != NULL)
	{
		ObjectInfo *exist_obj = NULL;
		pthread_cleanup_push(ObjectInfo_delAndSetNull, (void *)&p->obj);
		if ((exist_obj = p->module->findObject(p->module, p->obj->name)) != NULL)
		{
			if (exist_obj->type == ObjectType_reference)
			{
				_forwardDeclareFix(p);
				if ((*errp = ParserHelp_addPresentObj(p->module, p->obj)).code) ERR_OUT(errp);
				else if ((*errp = p->module->addObject(p->module, p->obj)).code) ERR_OUT(errp);
				else p->obj = NULL;
			}
			else if (exist_obj->type == ObjectType_declare) { }
			else
			{
				Dz1Thread_printf("add_object() : Name %s is already exist\n", p->obj->name);
				ERR_SET_OUT(errp, EEXIST);
			}
		}
		else
		{
			_forwardDeclareFix(p);
			if (0) { }
#ifndef GLOBAL_MISC_DEF_H
			else if (p->obj->type == ObjectType_union)
			{
				ObjectInfo *union_obj = p->obj;
				UnionInfo *union_info = (UnionInfo *)union_obj->info;

				char name[1024];
				ObjectInfo *present_obj = NULL;
				
				sprintf(name, "%sPresent", union_obj->name);
				if ((present_obj = ObjectInfo_new(ObjectType_enumerate, name, NULL, OBJECT_API_NONE, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					EnumInfo *enumInfo = NULL;
					pthread_cleanup_push(ObjectInfo_delAndSetNull, (void *)&present_obj);
					if ((present_obj->info = enumInfo = EnumInfo_new(errp)) == NULL) ERR_OUT(errp);
					else if ((*errp = union_info->members->travel(union_info->members, _addPresent2Enum, (void *)present_obj)).code) ERR_OUT(errp);
					else if ((*errp = p->module->addObject(p->module, present_obj)).code) ERR_OUT(errp);
					else
					{
						present_obj = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (ObjectInfo_delAndSetNull, (void *)&presentObj);
				}
			}
#else
			else if ((*errp = ParserHelp_addPresentObj(p->module, p->obj)).code) ERR_OUT(errp);
#endif
			else if ((*errp = p->module->addObject(p->module, p->obj)).code) ERR_OUT(errp);
			else p->obj = NULL;
		}
		pthread_cleanup_pop(1); // (ObjectInfo_delAndSetNull, (void *)&p->obj);
	}
	return errp->code == 0 ? TRUE : FALSE;
}