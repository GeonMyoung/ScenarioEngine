#include "dz1_jsonTestTypes.h"

MyExternHz *MyExternHz_new(MyExternHz src, Dz1Error *err) { return (MyExternHz *)Dz1u64_new((u64_t)src, err); }
MyExternHz *MyExternHz_clone(MyExternHz *src, Dz1Error *err) { return (MyExternHz *)Dz1u64_clone((u64_t *)src, err); }
void MyExternHz_del(MyExternHz *p) { Dz1u64_del((u64_t *)p); }
void MyExternHz_dump(MyExternHz *p, int tab) { Dz1u64_dump((u64_t *)p, tab); }

static bool_t MyExternHz_load(Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err) { return Dz1Json_u64_t_load(dst_obj, tok, err); }
static bool_t MyExternHz_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err) { return Dz1Json_u64_t_stringify(obj, buf, err); }


bool_t dz1_jsonTestTypes_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("MyExternHz"), MyExternHz_gen, MyExternHz_del, MyExternHz_load, MyExternHz_stringify)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
