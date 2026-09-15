#include "dz1_jsonTestSpec.h"

///////////////////////////////////////////////////////////////////////////////
// MyEnum
static bool_t MyEnum_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyEnum v = MyEnum_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (MyEnum)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = MyEnumFromStr(tok->v)) == MyEnum_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = MyEnum_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t MyEnum_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		MyEnum v = *(MyEnum *)obj;
		Dz1Str str_v = MyEnumStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// MyEnum
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MyStruct
static bool_t MyStruct_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyStruct *p = (MyStruct *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->a = *(u8_t *)info->data; break;
	case 1: p->b = *(u16_t *)info->data; break;
	case 2: p->c = *(u32_t *)info->data; break;
	case 3: p->d = *(u64_t *)info->data; break;
	case 4: p->e = (Dz1Str)info->data; info->data = NULL; break;
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *MyStruct_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	MyStruct *p = (MyStruct *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->a;
	case 1: return &p->b;
	case 2: return &p->c;
	case 3: return &p->d;
	case 4: return p->e;
	default: return NULL;
	}
}

static Dz1JsonSpecChild MyStruct_membs[] =
{
	{ Dz1Text("a"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("b"), Dz1Text("u16_t"), 1 },
	{ Dz1Text("c"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("d"), Dz1Text("u64_t"), 3 },
	{ Dz1Text("e"), Dz1Text("Dz1Str"), 4 },
	{ NULL, NULL, -1 }
};
// MyStruct
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MyUnion
static bool_t MyUnion_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyUnion *p = (MyUnion *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->x.a = *(u8_t *)info->data; break;
	case 1: p->x.b = *(u16_t *)info->data; break;
	case 2: p->x.c = *(u32_t *)info->data; break;
	case 3: p->x.d = *(u64_t *)info->data; break;
	case 4: p->x.e = (Dz1Str)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (MyUnionPresent)id->index; 
	return errp->code == 0 ? TRUE : FALSE;
}

static void *MyUnion_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	void *ret = NULL;
	MyUnion *p = (MyUnion *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case MyUnionPresent_a: return &p->x.a;
		case MyUnionPresent_b: return &p->x.b;
		case MyUnionPresent_c: return &p->x.c;
		case MyUnionPresent_d: return &p->x.d;
		case MyUnionPresent_e: return p->x.e;
		default: return NULL;
		}
	}
	return ret;
}

static Dz1JsonSpecChild MyUnion_membs[] =
{
	{ Dz1Text("a"), Dz1Text("u8_t"), MyUnionPresent_a },
	{ Dz1Text("b"), Dz1Text("u16_t"), MyUnionPresent_b },
	{ Dz1Text("c"), Dz1Text("u32_t"), MyUnionPresent_c },
	{ Dz1Text("d"), Dz1Text("u64_t"), MyUnionPresent_d },
	{ Dz1Text("e"), Dz1Text("Dz1Str"), MyUnionPresent_e },
	{ NULL, NULL, -1 }
};
// MyUnion
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// StringList
static bool_t StringList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StringList *dst = (StringList *)dst_ptr;
	Dz1Str str = (Dz1Str)var->data;
	if (dst == NULL || var == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, str)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t StringList_cnt(void *ptr)
{
	u32_t ret = 0;
	StringList *list = (StringList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

typedef Dz1Error (*StringList_tlvf)(void *ptr, Dz1Str entry);
static Dz1Error StringList_tlv(void *obj, Dz1JsonArrayEntryF _f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StringList *list = (StringList *)obj;
	StringList_tlvf f = (StringList_tlvf)_f;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// StringList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MyStructList
static bool_t MyStructList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyStructList *dst = (MyStructList *)dst_ptr;
	MyStruct *node = (MyStruct *)var->data;
	if (dst == NULL || node == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static u32_t MyStructList_cnt(void *ptr)
{
	u32_t ret = 0;
	MyStructList *list = (MyStructList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

typedef Dz1Error (*MyStructList_tlvf)(void *ptr, MyStruct *entry);
static Dz1Error MyStructList_tlv(void *obj, Dz1JsonArrayEntryF _f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MyStructList *list = (MyStructList *)obj;
	MyStructList_tlvf f = (MyStructList_tlvf)_f;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// MyStructList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MyUnionList
static bool_t MyUnionList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyUnionList *dst = (MyUnionList *)dst_ptr;
	MyUnion *node = (MyUnion *)var->data;
	if (dst == NULL || node == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t MyUnionList_cnt(void *ptr)
{	// static function으로 대체 가능
	u32_t ret = 0;
	MyUnionList *list = (MyUnionList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

typedef Dz1Error (*MyUnionList_tlvf)(void *ptr, MyUnion *entry);
static Dz1Error MyUnionList_tlv(void *obj, Dz1JsonArrayEntryF _f, void *arg)
{	// static function으로 대체 가능
	DZ1_ERROR_SAFE_VAR(errp, err);
	MyUnionList_tlvf f = (MyUnionList_tlvf)_f;
	MyUnionList *list = (MyUnionList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// MyUnionList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MyComponent
static bool_t MyComponent_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyComponent *p = (MyComponent *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->a = *(u32_t *)info->data; break;
	case 1: p->b = (MyStruct *)info->data; info->data = NULL; break;
	case 2: p->c = (MyUnion *)info->data; info->data = NULL; break;
	case 3: MyStructList_delAndSetNull(&p->d); p->d = (MyStructList *)info->data; info->data = NULL; break;
	case 4: MyUnionList_delAndSetNull(&p->e); p->e = (MyUnionList *)info->data; info->data = NULL; break;
	case 5: p->f = *(real64_t *)info->data; break;
	case 6: p->g = *(real32_t *)info->data; break;
	case 7: p->h = *(MyEnum *)info->data; break;
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *MyComponent_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	MyComponent *p = (MyComponent *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->a;
	case 1: return p->b;
	case 2: return p->c;
	case 3: return p->d;
	case 4: return p->e;
	case 5: return &p->f;
	case 6: return &p->g;
	case 7: return &p->h;
	default: return NULL;
	}
}

static Dz1JsonSpecChild MyComponent_membs[] =
{
	{ Dz1Text("a"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("b"), Dz1Text("MyStruct"), 1 },
	{ Dz1Text("c"), Dz1Text("MyUnion"), 2 },
	{ Dz1Text("d"), Dz1Text("MyStructList"), 3 },
	{ Dz1Text("e"), Dz1Text("MyUnionList"), 4 },
	{ Dz1Text("f"), Dz1Text("real64_t"), 5 },
	{ Dz1Text("g"), Dz1Text("real32_t"), 6 },
	{ Dz1Text("h"), Dz1Text("MyEnum"), 7 },
	{ NULL, NULL, -1 }
};
// MyComponent
///////////////////////////////////////////////////////////////////////////////

#define _primitive_arg(name)	#name, (Dz1GenFunc)name##_gen, (Dz1DelFunc)name##_del, name##_load, name##_stringify
#define _construct_arg(name)	#name, (Dz1GenFunc)name##_gen, (Dz1DelFunc)name##_del, name##_setChild, name##_getChild, name##_membs
#define _array_arg(name, memb)	#name, (Dz1GenFunc)name##_new, (Dz1DelFunc)name##_del, name##_append, name##_cnt, name##_tlv, #memb
Dz1JsonSpec *Dz1JsonTest_genSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (0) { }
		else if ((*errp = Dz1JsonSpec_add_primitive(ret,	_primitive_arg(MyEnum) )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(ret,	_construct_arg(MyStruct), Dz1JsonConstructType_struct )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(ret,	_construct_arg(MyUnion), Dz1JsonConstructType_union )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(ret,	_construct_arg(MyComponent), Dz1JsonConstructType_struct )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(ret,		_array_arg(MyStructList, MyStruct) )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(ret,		_array_arg(MyUnionList, MyUnion) )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(ret,		_array_arg(StringList, Dz1Str) )).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

