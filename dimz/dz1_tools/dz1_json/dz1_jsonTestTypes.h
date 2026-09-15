#ifndef DZ1_JSON_TEST_TYPES_H
#define DZ1_JSON_TEST_TYPES_H

#include <Dz1Json.h>
typedef u64_t MyExternHz;
DZ1_CPPLINK MyExternHz *MyExternHz_new(MyExternHz src, Dz1Error *errp);
static __inline__ MyExternHz *MyExternHz_gen(Dz1Error *err) { return MyExternHz_new(0, err); }
DZ1_CPPLINK MyExternHz *MyExternHz_clone(MyExternHz *src, Dz1Error *errp);
DZ1_CPPLINK void MyExternHz_del(MyExternHz *p);
static __inline__ void MyExternHz_delAndSetNull(void *pptr)
{
	MyExternHz **p = (MyExternHz **)pptr;
	MyExternHz_del(*p); *p = NULL;
}
DZ1_CPPLINK void MyExternHz_dump(MyExternHz *p, int tab);

DZ1_CPPLINK bool_t dz1_jsonTestTypes_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);

// DZ1_CPPLINK bool_t MyExternHz_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err);
// DZ1_CPPLINK bool_t MyExternHz_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err);

#endif
