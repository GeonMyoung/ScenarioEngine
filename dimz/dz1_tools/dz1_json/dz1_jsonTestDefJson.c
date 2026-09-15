#include "dz1_jsonTestDefJson.h"

////////////////////////////////////////////////////////////////////////////////
// MyStruct
static bool_t MyStruct_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyStruct *p = (MyStruct *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->a =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->b =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->c =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->d =  *(u64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->e); p->e = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
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
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStructList
static bool_t MyStructList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyStructList *dst = (MyStructList *)dst_ptr;
	MyStruct *node = NULL;
	if (dst == NULL || var == NULL || (node = (MyStruct *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
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

static Dz1Error MyStructList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MyStructList *list = (MyStructList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// MyStructList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyExternHz
// extern type
// MyExternHz
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnion
static bool_t MyUnion_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyUnion *p = (MyUnion *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case MyUnionPresent_a: p->x.a = *(u8_t *)info->data; break;
	case MyUnionPresent_b: p->x.b = *(u16_t *)info->data; break;
	case MyUnionPresent_c: p->x.c = *(u32_t *)info->data; break;
	case MyUnionPresent_d: p->x.d = *(u64_t *)info->data; break;
	case MyUnionPresent_e: Dz1Str_delAndSetNull(&p->x.e); p->x.e =(Dz1Str)info->data; info->data = NULL; break;
	case MyUnionPresent_f: MyStructList_delAndSetNull(&p->x.f); p->x.f =(MyStructList *)info->data; info->data = NULL; break;
	case MyUnionPresent_g: p->x.g = *(real64_t *)info->data; break;
	case MyUnionPresent_h: p->x.h = *(real32_t *)info->data; break;
	case MyUnionPresent_i: p->x.i = *(MyEnum *)info->data; break;
	case MyUnionPresent_j: p->x.j = *(MyExternHz *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (MyUnionPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *MyUnion_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
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
		case MyUnionPresent_f: return p->x.f;
		case MyUnionPresent_g: return &p->x.g;
		case MyUnionPresent_h: return &p->x.h;
		case MyUnionPresent_i: return &p->x.i;
		case MyUnionPresent_j: return &p->x.j;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild MyUnion_membs[] =
{
	{ Dz1Text("a"), Dz1Text("u8_t"), MyUnionPresent_a },
	{ Dz1Text("b"), Dz1Text("u16_t"), MyUnionPresent_b },
	{ Dz1Text("c"), Dz1Text("u32_t"), MyUnionPresent_c },
	{ Dz1Text("d"), Dz1Text("u64_t"), MyUnionPresent_d },
	{ Dz1Text("e"), Dz1Text("Dz1Str"), MyUnionPresent_e },
	{ Dz1Text("f"), Dz1Text("MyStructList"), MyUnionPresent_f },
	{ Dz1Text("g"), Dz1Text("real64_t"), MyUnionPresent_g },
	{ Dz1Text("h"), Dz1Text("real32_t"), MyUnionPresent_h },
	{ Dz1Text("i"), Dz1Text("MyEnum"), MyUnionPresent_i },
	{ Dz1Text("j"), Dz1Text("MyExternHz"), MyUnionPresent_j },
	{ NULL, NULL, -1 }
};
// MyUnion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionList
static bool_t MyUnionList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyUnionList *dst = (MyUnionList *)dst_ptr;
	MyUnion *node = NULL;
	if (dst == NULL || var == NULL || (node = (MyUnion *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t MyUnionList_cnt(void *ptr)
{
	u32_t ret = 0;
	MyUnionList *list = (MyUnionList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error MyUnionList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MyUnionList *list = (MyUnionList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// MyUnionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyComponent
static bool_t MyComponent_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MyComponent *p = (MyComponent *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->a =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: MyStruct_delAndSetNull(&p->b); p->b = (MyStruct *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: MyUnion_delAndSetNull(&p->c); p->c = (MyUnion *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: MyStructList_delAndSetNull(&p->d); p->d = (MyStructList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: MyUnionList_delAndSetNull(&p->e); p->e = (MyUnionList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: p->f =  *(real64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->g =  *(real32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->h =  *(MyEnum *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->i =  *(MyExternHz *)info->data; break; // type_scalar = 1, ptr_instance = 0
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
	case 8: return &p->i;
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
	{ Dz1Text("i"), Dz1Text("MyExternHz"), 8 },
	{ NULL, NULL, -1 }
};
// MyComponent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StringList
static bool_t StringList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StringList *dst = (StringList *)dst_ptr;
	Dz1Str node = NULL;
	if (dst == NULL || var == NULL || (node = (Dz1Str )var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
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

static Dz1Error StringList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StringList *list = (StringList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// StringList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Asn1MetaDataModule
static bool_t Asn1MetaDataModule_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Asn1MetaDataModule *p = (Asn1MetaDataModule *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Asn1MetaDataList_delAndSetNull(&p->elements); p->elements = (Asn1MetaDataList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Asn1MetaDataModule_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Asn1MetaDataModule *p = (Asn1MetaDataModule *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->name;
	case 1: return p->elements;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Asn1MetaDataModule_membs[] =
{
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("elements"), Dz1Text("Asn1MetaDataList"), 1 },
	{ NULL, NULL, -1 }
};
// Asn1MetaDataModule
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Asn1MetaData
static bool_t Asn1MetaData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Asn1MetaData *p = (Asn1MetaData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->value); p->value = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Asn1MetaDataList_delAndSetNull(&p->elements); p->elements = (Asn1MetaDataList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Asn1MetaData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Asn1MetaData *p = (Asn1MetaData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->name;
	case 1: return p->value;
	case 2: return p->elements;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Asn1MetaData_membs[] =
{
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("value"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("elements"), Dz1Text("Asn1MetaDataList"), 2 },
	{ NULL, NULL, -1 }
};
// Asn1MetaData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Asn1MetaDataList
static bool_t Asn1MetaDataList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Asn1MetaDataList *dst = (Asn1MetaDataList *)dst_ptr;
	Asn1MetaData *node = NULL;
	if (dst == NULL || var == NULL || (node = (Asn1MetaData *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Asn1MetaDataList_cnt(void *ptr)
{
	u32_t ret = 0;
	Asn1MetaDataList *list = (Asn1MetaDataList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Asn1MetaDataList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Asn1MetaDataList *list = (Asn1MetaDataList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Asn1MetaDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec Initializer
bool_t dz1_jsonTestDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("MyEnum"), MyEnum_gen, MyEnum_del, MyEnum_load, MyEnum_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("MyStruct"), MyStruct_gen, MyStruct_del, MyStruct_setChild, MyStruct_getChild, MyStruct_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("MyUnion"), MyUnion_gen, MyUnion_del, MyUnion_setChild, MyUnion_getChild, MyUnion_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("MyComponent"), MyComponent_gen, MyComponent_del, MyComponent_setChild, MyComponent_getChild, MyComponent_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Asn1MetaDataModule"), Asn1MetaDataModule_gen, Asn1MetaDataModule_del, Asn1MetaDataModule_setChild, Asn1MetaDataModule_getChild, Asn1MetaDataModule_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Asn1MetaData"), Asn1MetaData_gen, Asn1MetaData_del, Asn1MetaData_setChild, Asn1MetaData_getChild, Asn1MetaData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("MyStructList"), MyStructList_gen, MyStructList_del, MyStructList_append, MyStructList_cnt, MyStructList_tlv, Dz1Text("MyStruct") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("MyUnionList"), MyUnionList_gen, MyUnionList_del, MyUnionList_append, MyUnionList_cnt, MyUnionList_tlv, Dz1Text("MyUnion") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("StringList"), StringList_gen, StringList_del, StringList_append, StringList_cnt, StringList_tlv, Dz1Text("Dz1Str") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Asn1MetaDataList"), Asn1MetaDataList_gen, Asn1MetaDataList_del, Asn1MetaDataList_append, Asn1MetaDataList_cnt, Asn1MetaDataList_tlv, Dz1Text("Asn1MetaData") )).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
Dz1JsonSpec *dz1_jsonTestDef_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (dz1_jsonTestDef_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////
