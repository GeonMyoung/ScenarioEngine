#ifndef DZ1_TDC_INFO_TEST_TYPES_H_LOCAL
#define DZ1_TDC_INFO_TEST_TYPES_H_LOCAL

#include <dz1_error.h>

typedef struct TestTypeInfo
{
	int					 a;
	int					 b;
} TestTypeInfo;

DZ1_CPPLINK TestTypeInfo	*TestTypeInfo_clone(TestTypeInfo *src, Dz1Error *err);
DZ1_CPPLINK bool_t			 TestTypeInfo_copy(TestTypeInfo *dst, TestTypeInfo *src, Dz1Error *err);
DZ1_CPPLINK void			 TestTypeInfo_purge(TestTypeInfo *p);
DZ1_CPPLINK void			 TestTypeInfo_del(TestTypeInfo *p);
static __inline__ void		 TestTypeInfo_delAndSetNull(void *pptr)
{
	TestTypeInfo **p = (TestTypeInfo **)pptr;
	if (p) { TestTypeInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK void			 TestTypeInfoA_dump(TestTypeInfo *p, int tab);
DZ1_CPPLINK void			 TestTypeInfoA_fdump(FILE *fp, TestTypeInfo *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void			 TestTypeInfoW_dump(TestTypeInfo *p, int tab);
DZ1_CPPLINK void			 TestTypeInfoW_fdump(FILE *fp, TestTypeInfo *p, int tab);
#ifdef UNICODE
#define						 TestTypeInfo_dump		TestTypeInfoW_dump
#define						 TestTypeInfo_fdump		TestTypeInfoW_fdump
#else // UNICODE
#define						 TestTypeInfo_dump		TestTypeInfoA_dump
#define						 TestTypeInfo_fdump		TestTypeInfoA_fdump
#endif // UNICODE
#endif // UNIX_SYSTEM
#define						 TestTypeInfo_dump		TestTypeInfoA_dump
#define						 TestTypeInfo_fdump		TestTypeInfoA_fdump

DZ1_CPPLINK int				 TestTypeInfo_cmp(TestTypeInfo *a, TestTypeInfo *b);
#endif
