#ifndef DZ1_TDC_INFO_TEST_REF_H_LOCAL
#define DZ1_TDC_INFO_TEST_REF_H_LOCAL

#include <dz1_error.h>

typedef struct TestExternalType
{
	int				 a;
	int				 b;
} TestExternalType;

DZ1_CPPLINK TestExternalType	*TestExternalType_new(int a, int b, Dz1Error *err);
DZ1_CPPLINK bool_t				 TestExternalType_copy(TestExternalType *dst, TestExternalType *src, Dz1Error *err);
DZ1_CPPLINK void				 TestExternalType_purge(TestExternalType *p);
DZ1_CPPLINK TestExternalType	*TestExternalType_clone(TestExternalType *src, Dz1Error *err);
DZ1_CPPLINK void				 TestExternalType_del(TestExternalType *p);
static __inline__ void			 TestExternalType_delAndSetNull(void *pptr)
{
	TestExternalType **p = (TestExternalType **)pptr;
	if (p) { TestExternalType_del(*p); *p = NULL; }
}

DZ1_CPPLINK void				 TestExternalTypeA_dump(TestExternalType *p, int tab);
DZ1_CPPLINK void				 TestExternalTypeA_fdump(FILE *fp, TestExternalType *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void				 TestExternalTypeW_dump(TestExternalType *p, int tab);
DZ1_CPPLINK void				 TestExternalTypeA_fdump(FILE *fp, TestExternalType *p, int tab);
#ifdef UNICODE
#define							 TestExternalType_dump			TestExternalTypeW_dump
#define							 TestExternalType_fdump			TestExternalTypeW_fdump
#else // UNICODE
#define							 TestExternalType_dump			TestExternalTypeA_dump
#define							 TestExternalType_fdump			TestExternalTypeA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 TestExternalType_dump			TestExternalTypeA_dump
#define							 TestExternalType_fdump			TestExternalTypeA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK int					 TestExternalType_cmp(TestExternalType *a, TestExternalType *b);

#endif
