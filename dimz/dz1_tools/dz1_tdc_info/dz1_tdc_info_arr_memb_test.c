////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_arr_memb_test.h"

////////////////////////////////////////////////////////////////////////////////
// TestDataType
TestDataType *TestDataType_new(s32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TestDataType *__internal_ret = (TestDataType *)Dz1Calloc(sizeof(TestDataType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TestDataType_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TestDataType_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TestDataType_copy(TestDataType *dst, TestDataType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->id = src->id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TestDataType *TestDataType_clone(TestDataType *src, Dz1Error *err)
{
	TestDataType *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TestDataType *)Dz1Calloc(sizeof(TestDataType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TestDataType_delAndSetNull, (void *)&dst);
		if (TestDataType_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TestDataType_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TestDataType_purge(TestDataType *p)
{
	if (p == NULL) return;
}

void TestDataType_del(TestDataType *p)
{
	if (p == NULL) return;
	TestDataType_purge(p);
	Dz1Free(p);
}

void TestDataTypeA_dump(TestDataType *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("id = "); Dz1s32A_dump(&p->id, tab); 
	}
}
void TestDataTypeA_fdump(FILE *fp, TestDataType *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "id = "); Dz1s32A_fdump(fp, &p->id, tab); 
	}
}
#ifndef UNIX_SYSTEM
void TestDataTypeW_dump(TestDataType *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"id = "); Dz1s32W_dump(&p->id, tab); 
	}
}
void TestDataTypeW_fdump(FILE *fp, TestDataType *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"id = "); Dz1s32W_fdump(fp, &p->id, tab); 
	}
}
#endif // UNIX_SYSTEM
int TestDataType_cmp(TestDataType *a, TestDataType *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1s32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// TestDataType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData0
// void ArrayMemberData0_int_arr1_del(u32_t *src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(ArrayMemberData0, u32_t, int_arr1, unsigned int)
// void ArrayMemberData0_int_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(ArrayMemberData0, u32_t, int_arr1)
// u32_t *ArrayMemberData0_int_arr1_clone(u32_t *src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(ArrayMemberData0, u32_t, int_arr1, unsigned int)
// void ArrayMemberData0_int_arr1_dump(u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_dump(ArrayMemberData0, u32_t, int_arr1, unsigned int, " = ", Dz1u32_dump)
// void ArrayMemberData0_int_arr1_fdump(FILE *fp, u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_fdump(ArrayMemberData0, u32_t, int_arr1, unsigned int, " = ", Dz1u32_fdump)

ArrayMemberData0 *ArrayMemberData0_new(u32_t *int_arr1/*_e_copy*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberData0 *__internal_ret = (ArrayMemberData0 *)Dz1Calloc(sizeof(ArrayMemberData0), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ArrayMemberData0_delAndSetNull, (void *)&__internal_ret);
		
		if (int_arr1 != NULL && (__internal_ret->int_arr1 = ArrayMemberData0_int_arr1_clone(int_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData0_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ArrayMemberData0_copy(ArrayMemberData0 *dst, ArrayMemberData0 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->int_arr1 != NULL && (dst->int_arr1 = ArrayMemberData0_int_arr1_clone(src->int_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ArrayMemberData0 *ArrayMemberData0_clone(ArrayMemberData0 *src, Dz1Error *err)
{
	ArrayMemberData0 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ArrayMemberData0 *)Dz1Calloc(sizeof(ArrayMemberData0), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ArrayMemberData0_delAndSetNull, (void *)&dst);
		if (ArrayMemberData0_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData0_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ArrayMemberData0_purge(ArrayMemberData0 *p)
{
	if (p == NULL) return;
	ArrayMemberData0_int_arr1_del(p->int_arr1, 16);
}

void ArrayMemberData0_del(ArrayMemberData0 *p)
{
	if (p == NULL) return;
	ArrayMemberData0_purge(p);
	Dz1Free(p);
}

void ArrayMemberData0_dump(ArrayMemberData0 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("int_arr1 = ")); ArrayMemberData0_int_arr1_dump(p->int_arr1, 16, tab);
	}
}
void ArrayMemberData0_fdump(FILE *fp, ArrayMemberData0 *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("int_arr1 = ")); ArrayMemberData0_int_arr1_fdump(fp, p->int_arr1, 16, tab);
	}
}
// ArrayMemberData0
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData1
// void ArrayMemberData1_int_arr1_del(u32_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(ArrayMemberData1, u32_t, int_arr1, u32_t)
// void ArrayMemberData1_int_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(ArrayMemberData1, u32_t, int_arr1)
// u32_t *ArrayMemberData1_int_arr1_clone(u32_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(ArrayMemberData1, u32_t, int_arr1, u32_t)
// void ArrayMemberData1_int_arr1A_dump(u32_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_dump(ArrayMemberData1, u32_t, int_arr1, u32_t, " = ", Dz1u32A_dump)
// void ArrayMemberData1_int_arr1A_fdump(FILE *fp, u32_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_fdump(ArrayMemberData1, u32_t, int_arr1, u32_t, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_int_arr1W_dump(u32_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_dump(ArrayMemberData1, u32_t, int_arr1, u32_t, " = ", Dz1u32W_dump)
// void ArrayMemberData1_int_arr1W_fdump(FILE *fp, u32_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_fdump(ArrayMemberData1, u32_t, int_arr1, u32_t, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_int_arr2_del(u32_t **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberData1, u32_t*, int_arr2, u32_t, Dz1u32_del)
// void ArrayMemberData1_int_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberData1, u32_t*, int_arr2, u32_t)
// u32_t **ArrayMemberData1_int_arr2_clone(u32_t **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberData1, u32_t*, int_arr2, u32_t, Dz1u32_clone)
// void ArrayMemberData1_int_arr2A_dump(u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData1, u32_t*, int_arr2, u32_t, " = ", Dz1u32A_dump)
// void ArrayMemberData1_int_arr2A_fdump(FILE *fp, u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData1, u32_t*, int_arr2, u32_t, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_int_arr2W_dump(u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData1, u32_t*, int_arr2, u32_t, " = ", Dz1u32W_dump)
// void ArrayMemberData1_int_arr2W_fdump(FILE *fp, u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData1, u32_t*, int_arr2, u32_t, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_int_arr3_del(u32_t **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptrref_del(ArrayMemberData1, u32_t*, int_arr3, u32_t)
// void ArrayMemberData1_int_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_delAndSetNull(ArrayMemberData1, u32_t*, int_arr3)
// u32_t **ArrayMemberData1_int_arr3_clone(u32_t **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_clone(ArrayMemberData1, u32_t*, int_arr3, u32_t)
// void ArrayMemberData1_int_arr3A_dump(u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData1, u32_t*, int_arr3, u32_t, " = ", Dz1u32A_dump)
// void ArrayMemberData1_int_arr3A_fdump(FILE *fp, u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData1, u32_t*, int_arr3, u32_t, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_int_arr3W_dump(u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData1, u32_t*, int_arr3, u32_t, " = ", Dz1u32W_dump)
// void ArrayMemberData1_int_arr3W_fdump(FILE *fp, u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData1, u32_t*, int_arr3, u32_t, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_int_arr4A_dump(u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData1, u32_t*, int_arr4, u32_t, " = ", Dz1u32A_dump)
// void ArrayMemberData1_int_arr4A_fdump(FILE *fp, u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData1, u32_t*, int_arr4, u32_t, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_int_arr4W_dump(u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData1, u32_t*, int_arr4, u32_t, " = ", Dz1u32W_dump)
// void ArrayMemberData1_int_arr4W_fdump(FILE *fp, u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData1, u32_t*, int_arr4, u32_t, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_int_arr5A_dump(u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData1, u32_t*, int_arr5, u32_t, " = ", Dz1u32A_dump)
// void ArrayMemberData1_int_arr5A_fdump(FILE *fp, u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData1, u32_t*, int_arr5, u32_t, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_int_arr5W_dump(u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData1, u32_t*, int_arr5, u32_t, " = ", Dz1u32W_dump)
// void ArrayMemberData1_int_arr5W_fdump(FILE *fp, u32_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData1, u32_t*, int_arr5, u32_t, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_data_arr1_del(TestDataType *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(ArrayMemberData1, TestDataType, data_arr1, u32_t, TestDataType_purge)
// void ArrayMemberData1_data_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(ArrayMemberData1, TestDataType, data_arr1, u32_t)
// TestDataType *ArrayMemberData1_data_arr1_clone(TestDataType *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(ArrayMemberData1, TestDataType, data_arr1, u32_t, TestDataType_copy)
// void ArrayMemberData1_data_arr1A_dump(TestDataType *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_dump(ArrayMemberData1, TestDataType, data_arr1, u32_t, " = ", TestDataTypeA_dump)
// void ArrayMemberData1_data_arr1A_fdump(FILE *fp, TestDataType *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_fdump(ArrayMemberData1, TestDataType, data_arr1, u32_t, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_data_arr1W_dump(TestDataType *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_dump(ArrayMemberData1, TestDataType, data_arr1, u32_t, " = ", TestDataTypeW_dump)
// void ArrayMemberData1_data_arr1W_fdump(FILE *fp, TestDataType *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_fdump(ArrayMemberData1, TestDataType, data_arr1, u32_t, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_data_arr2_del(TestDataType **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberData1, TestDataType*, data_arr2, u32_t, TestDataType_del)
// void ArrayMemberData1_data_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberData1, TestDataType*, data_arr2, u32_t)
// TestDataType **ArrayMemberData1_data_arr2_clone(TestDataType **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberData1, TestDataType*, data_arr2, u32_t, TestDataType_clone)
// void ArrayMemberData1_data_arr2A_dump(TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData1, TestDataType*, data_arr2, u32_t, " = ", TestDataTypeA_dump)
// void ArrayMemberData1_data_arr2A_fdump(FILE *fp, TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData1, TestDataType*, data_arr2, u32_t, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_data_arr2W_dump(TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData1, TestDataType*, data_arr2, u32_t, " = ", TestDataTypeW_dump)
// void ArrayMemberData1_data_arr2W_fdump(FILE *fp, TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData1, TestDataType*, data_arr2, u32_t, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_data_arr3_del(TestDataType **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptrref_del(ArrayMemberData1, TestDataType*, data_arr3, u32_t)
// void ArrayMemberData1_data_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_delAndSetNull(ArrayMemberData1, TestDataType*, data_arr3)
// TestDataType **ArrayMemberData1_data_arr3_clone(TestDataType **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_clone(ArrayMemberData1, TestDataType*, data_arr3, u32_t)
// void ArrayMemberData1_data_arr3A_dump(TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData1, TestDataType*, data_arr3, u32_t, " = ", TestDataTypeA_dump)
// void ArrayMemberData1_data_arr3A_fdump(FILE *fp, TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData1, TestDataType*, data_arr3, u32_t, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_data_arr3W_dump(TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData1, TestDataType*, data_arr3, u32_t, " = ", TestDataTypeW_dump)
// void ArrayMemberData1_data_arr3W_fdump(FILE *fp, TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData1, TestDataType*, data_arr3, u32_t, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_data_arr4A_dump(TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData1, TestDataType*, data_arr4, u32_t, " = ", TestDataTypeA_dump)
// void ArrayMemberData1_data_arr4A_fdump(FILE *fp, TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData1, TestDataType*, data_arr4, u32_t, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_data_arr4W_dump(TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData1, TestDataType*, data_arr4, u32_t, " = ", TestDataTypeW_dump)
// void ArrayMemberData1_data_arr4W_fdump(FILE *fp, TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData1, TestDataType*, data_arr4, u32_t, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_data_arr5A_dump(TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData1, TestDataType*, data_arr5, u32_t, " = ", TestDataTypeA_dump)
// void ArrayMemberData1_data_arr5A_fdump(FILE *fp, TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData1, TestDataType*, data_arr5, u32_t, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_data_arr5W_dump(TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData1, TestDataType*, data_arr5, u32_t, " = ", TestDataTypeW_dump)
// void ArrayMemberData1_data_arr5W_fdump(FILE *fp, TestDataType **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData1, TestDataType*, data_arr5, u32_t, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_utf8_arr1_del(Dz1Asn1UTF8Str *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(ArrayMemberData1, Dz1Asn1UTF8Str, utf8_arr1, u32_t, Dz1Asn1UTF8Str_purge)
// void ArrayMemberData1_utf8_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(ArrayMemberData1, Dz1Asn1UTF8Str, utf8_arr1, u32_t)
// Dz1Asn1UTF8Str *ArrayMemberData1_utf8_arr1_clone(Dz1Asn1UTF8Str *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(ArrayMemberData1, Dz1Asn1UTF8Str, utf8_arr1, u32_t, Dz1Asn1UTF8Str_copy)
// void ArrayMemberData1_utf8_arr1A_dump(Dz1Asn1UTF8Str *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_dump(ArrayMemberData1, Dz1Asn1UTF8Str, utf8_arr1, u32_t, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData1_utf8_arr1A_fdump(FILE *fp, Dz1Asn1UTF8Str *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_fdump(ArrayMemberData1, Dz1Asn1UTF8Str, utf8_arr1, u32_t, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_utf8_arr1W_dump(Dz1Asn1UTF8Str *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_dump(ArrayMemberData1, Dz1Asn1UTF8Str, utf8_arr1, u32_t, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData1_utf8_arr1W_fdump(FILE *fp, Dz1Asn1UTF8Str *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_fdump(ArrayMemberData1, Dz1Asn1UTF8Str, utf8_arr1, u32_t, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_utf8_arr2_del(Dz1Asn1UTF8Str **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr2, u32_t, Dz1Asn1UTF8Str_del)
// void ArrayMemberData1_utf8_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr2, u32_t)
// Dz1Asn1UTF8Str **ArrayMemberData1_utf8_arr2_clone(Dz1Asn1UTF8Str **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr2, u32_t, Dz1Asn1UTF8Str_clone)
// void ArrayMemberData1_utf8_arr2A_dump(Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr2, u32_t, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData1_utf8_arr2A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr2, u32_t, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_utf8_arr2W_dump(Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr2, u32_t, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData1_utf8_arr2W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr2, u32_t, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_utf8_arr3_del(Dz1Asn1UTF8Str **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptrref_del(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr3, u32_t)
// void ArrayMemberData1_utf8_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_delAndSetNull(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr3)
// Dz1Asn1UTF8Str **ArrayMemberData1_utf8_arr3_clone(Dz1Asn1UTF8Str **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_clone(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr3, u32_t)
// void ArrayMemberData1_utf8_arr3A_dump(Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr3, u32_t, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData1_utf8_arr3A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr3, u32_t, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_utf8_arr3W_dump(Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr3, u32_t, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData1_utf8_arr3W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr3, u32_t, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_utf8_arr4A_dump(Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr4, u32_t, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData1_utf8_arr4A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr4, u32_t, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_utf8_arr4W_dump(Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr4, u32_t, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData1_utf8_arr4W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr4, u32_t, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData1_utf8_arr5A_dump(Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr5, u32_t, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData1_utf8_arr5A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr5, u32_t, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData1_utf8_arr5W_dump(Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr5, u32_t, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData1_utf8_arr5W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData1, Dz1Asn1UTF8Str*, utf8_arr5, u32_t, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

ArrayMemberData1 *ArrayMemberData1_new(u32_t *int_arr1/*_e_copy*/, 
									   u32_t int_cnt1, 
									   u32_t **int_arr2/*_e_clone*/, 
									   u32_t int_cnt2, 
									   u32_t **int_arr3/*_e_ref*/, 
									   u32_t int_cnt3, 
									   u32_t **int_arr4/*_ref*/, 
									   u32_t int_cnt4, 
									   u32_t **int_arr5/*_ref*/, 
									   u32_t int_cnt5, 
									   TestDataType *data_arr1/*_e_copy*/, 
									   u32_t data_cnt1, 
									   TestDataType **data_arr2/*_e_clone*/, 
									   u32_t data_cnt2, 
									   TestDataType **data_arr3/*_e_ref*/, 
									   u32_t data_cnt3, 
									   TestDataType **data_arr4/*_ref*/, 
									   u32_t data_cnt4, 
									   TestDataType **data_arr5/*_ref*/, 
									   u32_t data_cnt5, 
									   Dz1Asn1UTF8Str *utf8_arr1/*_e_copy*/, 
									   u32_t utf8_cnt1, 
									   Dz1Asn1UTF8Str **utf8_arr2/*_e_clone*/, 
									   u32_t utf8_cnt2, 
									   Dz1Asn1UTF8Str **utf8_arr3/*_e_ref*/, 
									   u32_t utf8_cnt3, 
									   Dz1Asn1UTF8Str **utf8_arr4/*_ref*/, 
									   u32_t utf8_cnt4, 
									   Dz1Asn1UTF8Str **utf8_arr5/*_ref*/, 
									   u32_t utf8_cnt5, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberData1 *__internal_ret = (ArrayMemberData1 *)Dz1Calloc(sizeof(ArrayMemberData1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ArrayMemberData1_delAndSetNull, (void *)&__internal_ret);
		
		if (int_arr1 != NULL && (__internal_ret->int_arr1 = ArrayMemberData1_int_arr1_clone(int_arr1, int_cnt1, errp)) == NULL) { ERR_OUT(errp); }
		else if (int_arr2 != NULL && (__internal_ret->int_arr2 = ArrayMemberData1_int_arr2_clone(int_arr2, int_cnt2, errp)) == NULL) { ERR_OUT(errp); }
		else if (int_arr3 != NULL && (__internal_ret->int_arr3 = ArrayMemberData1_int_arr3_clone(int_arr3, int_cnt3, errp)) == NULL) { ERR_OUT(errp); }
		else if (data_arr1 != NULL && (__internal_ret->data_arr1 = ArrayMemberData1_data_arr1_clone(data_arr1, data_cnt1, errp)) == NULL) { ERR_OUT(errp); }
		else if (data_arr2 != NULL && (__internal_ret->data_arr2 = ArrayMemberData1_data_arr2_clone(data_arr2, data_cnt2, errp)) == NULL) { ERR_OUT(errp); }
		else if (data_arr3 != NULL && (__internal_ret->data_arr3 = ArrayMemberData1_data_arr3_clone(data_arr3, data_cnt3, errp)) == NULL) { ERR_OUT(errp); }
		else if (utf8_arr1 != NULL && (__internal_ret->utf8_arr1 = ArrayMemberData1_utf8_arr1_clone(utf8_arr1, utf8_cnt1, errp)) == NULL) { ERR_OUT(errp); }
		else if (utf8_arr2 != NULL && (__internal_ret->utf8_arr2 = ArrayMemberData1_utf8_arr2_clone(utf8_arr2, utf8_cnt2, errp)) == NULL) { ERR_OUT(errp); }
		else if (utf8_arr3 != NULL && (__internal_ret->utf8_arr3 = ArrayMemberData1_utf8_arr3_clone(utf8_arr3, utf8_cnt3, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			__internal_ret->int_cnt1 = int_cnt1;
			__internal_ret->int_cnt2 = int_cnt2;
			__internal_ret->int_cnt3 = int_cnt3;
			__internal_ret->int_arr4 = int_arr4;
			__internal_ret->int_cnt4 = int_cnt4;
			__internal_ret->int_arr5 = int_arr5;
			__internal_ret->int_cnt5 = int_cnt5;
			__internal_ret->data_cnt1 = data_cnt1;
			__internal_ret->data_cnt2 = data_cnt2;
			__internal_ret->data_cnt3 = data_cnt3;
			__internal_ret->data_arr4 = data_arr4;
			__internal_ret->data_cnt4 = data_cnt4;
			__internal_ret->data_arr5 = data_arr5;
			__internal_ret->data_cnt5 = data_cnt5;
			__internal_ret->utf8_cnt1 = utf8_cnt1;
			__internal_ret->utf8_cnt2 = utf8_cnt2;
			__internal_ret->utf8_cnt3 = utf8_cnt3;
			__internal_ret->utf8_arr4 = utf8_arr4;
			__internal_ret->utf8_cnt4 = utf8_cnt4;
			__internal_ret->utf8_arr5 = utf8_arr5;
			__internal_ret->utf8_cnt5 = utf8_cnt5;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ArrayMemberData1_copy(ArrayMemberData1 *dst, ArrayMemberData1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->int_arr1 != NULL && (dst->int_arr1 = ArrayMemberData1_int_arr1_clone(src->int_arr1, src->int_cnt1, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->int_arr2 != NULL && (dst->int_arr2 = ArrayMemberData1_int_arr2_clone(src->int_arr2, src->int_cnt2, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->int_arr3 != NULL && (dst->int_arr3 = ArrayMemberData1_int_arr3_clone(src->int_arr3, src->int_cnt3, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->data_arr1 != NULL && (dst->data_arr1 = ArrayMemberData1_data_arr1_clone(src->data_arr1, src->data_cnt1, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->data_arr2 != NULL && (dst->data_arr2 = ArrayMemberData1_data_arr2_clone(src->data_arr2, src->data_cnt2, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->data_arr3 != NULL && (dst->data_arr3 = ArrayMemberData1_data_arr3_clone(src->data_arr3, src->data_cnt3, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->utf8_arr1 != NULL && (dst->utf8_arr1 = ArrayMemberData1_utf8_arr1_clone(src->utf8_arr1, src->utf8_cnt1, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->utf8_arr2 != NULL && (dst->utf8_arr2 = ArrayMemberData1_utf8_arr2_clone(src->utf8_arr2, src->utf8_cnt2, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->utf8_arr3 != NULL && (dst->utf8_arr3 = ArrayMemberData1_utf8_arr3_clone(src->utf8_arr3, src->utf8_cnt3, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		dst->int_cnt1 = src->int_cnt1;
		dst->int_cnt2 = src->int_cnt2;
		dst->int_cnt3 = src->int_cnt3;
		dst->int_arr4 = src->int_arr4;
		dst->int_cnt4 = src->int_cnt4;
		dst->int_arr5 = src->int_arr5;
		dst->int_cnt5 = src->int_cnt5;
		dst->data_cnt1 = src->data_cnt1;
		dst->data_cnt2 = src->data_cnt2;
		dst->data_cnt3 = src->data_cnt3;
		dst->data_arr4 = src->data_arr4;
		dst->data_cnt4 = src->data_cnt4;
		dst->data_arr5 = src->data_arr5;
		dst->data_cnt5 = src->data_cnt5;
		dst->utf8_cnt1 = src->utf8_cnt1;
		dst->utf8_cnt2 = src->utf8_cnt2;
		dst->utf8_cnt3 = src->utf8_cnt3;
		dst->utf8_arr4 = src->utf8_arr4;
		dst->utf8_cnt4 = src->utf8_cnt4;
		dst->utf8_arr5 = src->utf8_arr5;
		dst->utf8_cnt5 = src->utf8_cnt5;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ArrayMemberData1 *ArrayMemberData1_clone(ArrayMemberData1 *src, Dz1Error *err)
{
	ArrayMemberData1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ArrayMemberData1 *)Dz1Calloc(sizeof(ArrayMemberData1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ArrayMemberData1_delAndSetNull, (void *)&dst);
		if (ArrayMemberData1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ArrayMemberData1_purge(ArrayMemberData1 *p)
{
	if (p == NULL) return;
	ArrayMemberData1_int_arr1_del(p->int_arr1, p->int_cnt1);
	ArrayMemberData1_int_arr2_del(p->int_arr2, p->int_cnt2);
	ArrayMemberData1_int_arr3_del(p->int_arr3, p->int_cnt3);
	ArrayMemberData1_data_arr1_del(p->data_arr1, p->data_cnt1);
	ArrayMemberData1_data_arr2_del(p->data_arr2, p->data_cnt2);
	ArrayMemberData1_data_arr3_del(p->data_arr3, p->data_cnt3);
	ArrayMemberData1_utf8_arr1_del(p->utf8_arr1, p->utf8_cnt1);
	ArrayMemberData1_utf8_arr2_del(p->utf8_arr2, p->utf8_cnt2);
	ArrayMemberData1_utf8_arr3_del(p->utf8_arr3, p->utf8_cnt3);
}

void ArrayMemberData1_del(ArrayMemberData1 *p)
{
	if (p == NULL) return;
	ArrayMemberData1_purge(p);
	Dz1Free(p);
}

void ArrayMemberData1A_dump(ArrayMemberData1 *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "int_arr1 = "); ArrayMemberData1_int_arr1A_dump(p->int_arr1, p->int_cnt1, tab);
		Dz1ThreadA_tprintf(tab, "int_cnt1 = "); Dz1u32A_dump(&p->int_cnt1, tab); 
		Dz1ThreadA_tprintf(tab, "int_arr2 = "); ArrayMemberData1_int_arr2A_dump(p->int_arr2, p->int_cnt2, tab);
		Dz1ThreadA_tprintf(tab, "int_cnt2 = "); Dz1u32A_dump(&p->int_cnt2, tab); 
		Dz1ThreadA_tprintf(tab, "int_arr3 = "); ArrayMemberData1_int_arr3A_dump(p->int_arr3, p->int_cnt3, tab);
		Dz1ThreadA_tprintf(tab, "int_cnt3 = "); Dz1u32A_dump(&p->int_cnt3, tab); 
		Dz1ThreadA_tprintf(tab, "int_arr4 = "); ArrayMemberData1_int_arr4A_dump(p->int_arr4, p->int_cnt4, tab);
		Dz1ThreadA_tprintf(tab, "int_cnt4 = "); Dz1u32A_dump(&p->int_cnt4, tab); 
		Dz1ThreadA_tprintf(tab, "int_arr5 = "); ArrayMemberData1_int_arr5A_dump(p->int_arr5, p->int_cnt5, tab);
		Dz1ThreadA_tprintf(tab, "int_cnt5 = "); Dz1u32A_dump(&p->int_cnt5, tab); 
		Dz1ThreadA_tprintf(tab, "data_arr1 = "); ArrayMemberData1_data_arr1A_dump(p->data_arr1, p->data_cnt1, tab);
		Dz1ThreadA_tprintf(tab, "data_cnt1 = "); Dz1u32A_dump(&p->data_cnt1, tab); 
		Dz1ThreadA_tprintf(tab, "data_arr2 = "); ArrayMemberData1_data_arr2A_dump(p->data_arr2, p->data_cnt2, tab);
		Dz1ThreadA_tprintf(tab, "data_cnt2 = "); Dz1u32A_dump(&p->data_cnt2, tab); 
		Dz1ThreadA_tprintf(tab, "data_arr3 = "); ArrayMemberData1_data_arr3A_dump(p->data_arr3, p->data_cnt3, tab);
		Dz1ThreadA_tprintf(tab, "data_cnt3 = "); Dz1u32A_dump(&p->data_cnt3, tab); 
		Dz1ThreadA_tprintf(tab, "data_arr4 = "); ArrayMemberData1_data_arr4A_dump(p->data_arr4, p->data_cnt4, tab);
		Dz1ThreadA_tprintf(tab, "data_cnt4 = "); Dz1u32A_dump(&p->data_cnt4, tab); 
		Dz1ThreadA_tprintf(tab, "data_arr5 = "); ArrayMemberData1_data_arr5A_dump(p->data_arr5, p->data_cnt5, tab);
		Dz1ThreadA_tprintf(tab, "data_cnt5 = "); Dz1u32A_dump(&p->data_cnt5, tab); 
		Dz1ThreadA_tprintf(tab, "utf8_arr1 = "); ArrayMemberData1_utf8_arr1A_dump(p->utf8_arr1, p->utf8_cnt1, tab);
		Dz1ThreadA_tprintf(tab, "utf8_cnt1 = "); Dz1u32A_dump(&p->utf8_cnt1, tab); 
		Dz1ThreadA_tprintf(tab, "utf8_arr2 = "); ArrayMemberData1_utf8_arr2A_dump(p->utf8_arr2, p->utf8_cnt2, tab);
		Dz1ThreadA_tprintf(tab, "utf8_cnt2 = "); Dz1u32A_dump(&p->utf8_cnt2, tab); 
		Dz1ThreadA_tprintf(tab, "utf8_arr3 = "); ArrayMemberData1_utf8_arr3A_dump(p->utf8_arr3, p->utf8_cnt3, tab);
		Dz1ThreadA_tprintf(tab, "utf8_cnt3 = "); Dz1u32A_dump(&p->utf8_cnt3, tab); 
		Dz1ThreadA_tprintf(tab, "utf8_arr4 = "); ArrayMemberData1_utf8_arr4A_dump(p->utf8_arr4, p->utf8_cnt4, tab);
		Dz1ThreadA_tprintf(tab, "utf8_cnt4 = "); Dz1u32A_dump(&p->utf8_cnt4, tab); 
		Dz1ThreadA_tprintf(tab, "utf8_arr5 = "); ArrayMemberData1_utf8_arr5A_dump(p->utf8_arr5, p->utf8_cnt5, tab);
		Dz1ThreadA_tprintf(tab, "utf8_cnt5 = "); Dz1u32A_dump(&p->utf8_cnt5, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void ArrayMemberData1A_fdump(FILE *fp, ArrayMemberData1 *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintf(fp, tab, "int_arr1 = "); ArrayMemberData1_int_arr1A_fdump(fp, p->int_arr1, p->int_cnt1, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_cnt1 = "); Dz1u32A_fdump(fp, &p->int_cnt1, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "int_arr2 = "); ArrayMemberData1_int_arr2A_fdump(fp, p->int_arr2, p->int_cnt2, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_cnt2 = "); Dz1u32A_fdump(fp, &p->int_cnt2, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "int_arr3 = "); ArrayMemberData1_int_arr3A_fdump(fp, p->int_arr3, p->int_cnt3, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_cnt3 = "); Dz1u32A_fdump(fp, &p->int_cnt3, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "int_arr4 = "); ArrayMemberData1_int_arr4A_fdump(fp, p->int_arr4, p->int_cnt4, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_cnt4 = "); Dz1u32A_fdump(fp, &p->int_cnt4, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "int_arr5 = "); ArrayMemberData1_int_arr5A_fdump(fp, p->int_arr5, p->int_cnt5, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_cnt5 = "); Dz1u32A_fdump(fp, &p->int_cnt5, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "data_arr1 = "); ArrayMemberData1_data_arr1A_fdump(fp, p->data_arr1, p->data_cnt1, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_cnt1 = "); Dz1u32A_fdump(fp, &p->data_cnt1, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "data_arr2 = "); ArrayMemberData1_data_arr2A_fdump(fp, p->data_arr2, p->data_cnt2, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_cnt2 = "); Dz1u32A_fdump(fp, &p->data_cnt2, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "data_arr3 = "); ArrayMemberData1_data_arr3A_fdump(fp, p->data_arr3, p->data_cnt3, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_cnt3 = "); Dz1u32A_fdump(fp, &p->data_cnt3, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "data_arr4 = "); ArrayMemberData1_data_arr4A_fdump(fp, p->data_arr4, p->data_cnt4, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_cnt4 = "); Dz1u32A_fdump(fp, &p->data_cnt4, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "data_arr5 = "); ArrayMemberData1_data_arr5A_fdump(fp, p->data_arr5, p->data_cnt5, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_cnt5 = "); Dz1u32A_fdump(fp, &p->data_cnt5, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "utf8_arr1 = "); ArrayMemberData1_utf8_arr1A_fdump(fp, p->utf8_arr1, p->utf8_cnt1, tab);
		Dz1ThreadA_ftprintf(fp, tab, "utf8_cnt1 = "); Dz1u32A_fdump(fp, &p->utf8_cnt1, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "utf8_arr2 = "); ArrayMemberData1_utf8_arr2A_fdump(fp, p->utf8_arr2, p->utf8_cnt2, tab);
		Dz1ThreadA_ftprintf(fp, tab, "utf8_cnt2 = "); Dz1u32A_fdump(fp, &p->utf8_cnt2, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "utf8_arr3 = "); ArrayMemberData1_utf8_arr3A_fdump(fp, p->utf8_arr3, p->utf8_cnt3, tab);
		Dz1ThreadA_ftprintf(fp, tab, "utf8_cnt3 = "); Dz1u32A_fdump(fp, &p->utf8_cnt3, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "utf8_arr4 = "); ArrayMemberData1_utf8_arr4A_fdump(fp, p->utf8_arr4, p->utf8_cnt4, tab);
		Dz1ThreadA_ftprintf(fp, tab, "utf8_cnt4 = "); Dz1u32A_fdump(fp, &p->utf8_cnt4, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "utf8_arr5 = "); ArrayMemberData1_utf8_arr5A_fdump(fp, p->utf8_arr5, p->utf8_cnt5, tab);
		Dz1ThreadA_ftprintf(fp, tab, "utf8_cnt5 = "); Dz1u32A_fdump(fp, &p->utf8_cnt5, tab); 
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void ArrayMemberData1W_dump(ArrayMemberData1 *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"int_arr1 = "); ArrayMemberData1_int_arr1W_dump(p->int_arr1, p->int_cnt1, tab);
		Dz1ThreadW_tprintf(tab, L"int_cnt1 = "); Dz1u32W_dump(&p->int_cnt1, tab); 
		Dz1ThreadW_tprintf(tab, L"int_arr2 = "); ArrayMemberData1_int_arr2W_dump(p->int_arr2, p->int_cnt2, tab);
		Dz1ThreadW_tprintf(tab, L"int_cnt2 = "); Dz1u32W_dump(&p->int_cnt2, tab); 
		Dz1ThreadW_tprintf(tab, L"int_arr3 = "); ArrayMemberData1_int_arr3W_dump(p->int_arr3, p->int_cnt3, tab);
		Dz1ThreadW_tprintf(tab, L"int_cnt3 = "); Dz1u32W_dump(&p->int_cnt3, tab); 
		Dz1ThreadW_tprintf(tab, L"int_arr4 = "); ArrayMemberData1_int_arr4W_dump(p->int_arr4, p->int_cnt4, tab);
		Dz1ThreadW_tprintf(tab, L"int_cnt4 = "); Dz1u32W_dump(&p->int_cnt4, tab); 
		Dz1ThreadW_tprintf(tab, L"int_arr5 = "); ArrayMemberData1_int_arr5W_dump(p->int_arr5, p->int_cnt5, tab);
		Dz1ThreadW_tprintf(tab, L"int_cnt5 = "); Dz1u32W_dump(&p->int_cnt5, tab); 
		Dz1ThreadW_tprintf(tab, L"data_arr1 = "); ArrayMemberData1_data_arr1W_dump(p->data_arr1, p->data_cnt1, tab);
		Dz1ThreadW_tprintf(tab, L"data_cnt1 = "); Dz1u32W_dump(&p->data_cnt1, tab); 
		Dz1ThreadW_tprintf(tab, L"data_arr2 = "); ArrayMemberData1_data_arr2W_dump(p->data_arr2, p->data_cnt2, tab);
		Dz1ThreadW_tprintf(tab, L"data_cnt2 = "); Dz1u32W_dump(&p->data_cnt2, tab); 
		Dz1ThreadW_tprintf(tab, L"data_arr3 = "); ArrayMemberData1_data_arr3W_dump(p->data_arr3, p->data_cnt3, tab);
		Dz1ThreadW_tprintf(tab, L"data_cnt3 = "); Dz1u32W_dump(&p->data_cnt3, tab); 
		Dz1ThreadW_tprintf(tab, L"data_arr4 = "); ArrayMemberData1_data_arr4W_dump(p->data_arr4, p->data_cnt4, tab);
		Dz1ThreadW_tprintf(tab, L"data_cnt4 = "); Dz1u32W_dump(&p->data_cnt4, tab); 
		Dz1ThreadW_tprintf(tab, L"data_arr5 = "); ArrayMemberData1_data_arr5W_dump(p->data_arr5, p->data_cnt5, tab);
		Dz1ThreadW_tprintf(tab, L"data_cnt5 = "); Dz1u32W_dump(&p->data_cnt5, tab); 
		Dz1ThreadW_tprintf(tab, L"utf8_arr1 = "); ArrayMemberData1_utf8_arr1W_dump(p->utf8_arr1, p->utf8_cnt1, tab);
		Dz1ThreadW_tprintf(tab, L"utf8_cnt1 = "); Dz1u32W_dump(&p->utf8_cnt1, tab); 
		Dz1ThreadW_tprintf(tab, L"utf8_arr2 = "); ArrayMemberData1_utf8_arr2W_dump(p->utf8_arr2, p->utf8_cnt2, tab);
		Dz1ThreadW_tprintf(tab, L"utf8_cnt2 = "); Dz1u32W_dump(&p->utf8_cnt2, tab); 
		Dz1ThreadW_tprintf(tab, L"utf8_arr3 = "); ArrayMemberData1_utf8_arr3W_dump(p->utf8_arr3, p->utf8_cnt3, tab);
		Dz1ThreadW_tprintf(tab, L"utf8_cnt3 = "); Dz1u32W_dump(&p->utf8_cnt3, tab); 
		Dz1ThreadW_tprintf(tab, L"utf8_arr4 = "); ArrayMemberData1_utf8_arr4W_dump(p->utf8_arr4, p->utf8_cnt4, tab);
		Dz1ThreadW_tprintf(tab, L"utf8_cnt4 = "); Dz1u32W_dump(&p->utf8_cnt4, tab); 
		Dz1ThreadW_tprintf(tab, L"utf8_arr5 = "); ArrayMemberData1_utf8_arr5W_dump(p->utf8_arr5, p->utf8_cnt5, tab);
		Dz1ThreadW_tprintf(tab, L"utf8_cnt5 = "); Dz1u32W_dump(&p->utf8_cnt5, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void ArrayMemberData1W_fdump(FILE *fp, ArrayMemberData1 *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr1 = "); ArrayMemberData1_int_arr1W_fdump(fp, p->int_arr1, p->int_cnt1, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_cnt1 = "); Dz1u32W_fdump(fp, &p->int_cnt1, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr2 = "); ArrayMemberData1_int_arr2W_fdump(fp, p->int_arr2, p->int_cnt2, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_cnt2 = "); Dz1u32W_fdump(fp, &p->int_cnt2, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr3 = "); ArrayMemberData1_int_arr3W_fdump(fp, p->int_arr3, p->int_cnt3, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_cnt3 = "); Dz1u32W_fdump(fp, &p->int_cnt3, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr4 = "); ArrayMemberData1_int_arr4W_fdump(fp, p->int_arr4, p->int_cnt4, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_cnt4 = "); Dz1u32W_fdump(fp, &p->int_cnt4, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr5 = "); ArrayMemberData1_int_arr5W_fdump(fp, p->int_arr5, p->int_cnt5, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_cnt5 = "); Dz1u32W_fdump(fp, &p->int_cnt5, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr1 = "); ArrayMemberData1_data_arr1W_fdump(fp, p->data_arr1, p->data_cnt1, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_cnt1 = "); Dz1u32W_fdump(fp, &p->data_cnt1, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr2 = "); ArrayMemberData1_data_arr2W_fdump(fp, p->data_arr2, p->data_cnt2, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_cnt2 = "); Dz1u32W_fdump(fp, &p->data_cnt2, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr3 = "); ArrayMemberData1_data_arr3W_fdump(fp, p->data_arr3, p->data_cnt3, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_cnt3 = "); Dz1u32W_fdump(fp, &p->data_cnt3, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr4 = "); ArrayMemberData1_data_arr4W_fdump(fp, p->data_arr4, p->data_cnt4, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_cnt4 = "); Dz1u32W_fdump(fp, &p->data_cnt4, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr5 = "); ArrayMemberData1_data_arr5W_fdump(fp, p->data_arr5, p->data_cnt5, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_cnt5 = "); Dz1u32W_fdump(fp, &p->data_cnt5, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_arr1 = "); ArrayMemberData1_utf8_arr1W_fdump(fp, p->utf8_arr1, p->utf8_cnt1, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_cnt1 = "); Dz1u32W_fdump(fp, &p->utf8_cnt1, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_arr2 = "); ArrayMemberData1_utf8_arr2W_fdump(fp, p->utf8_arr2, p->utf8_cnt2, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_cnt2 = "); Dz1u32W_fdump(fp, &p->utf8_cnt2, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_arr3 = "); ArrayMemberData1_utf8_arr3W_fdump(fp, p->utf8_arr3, p->utf8_cnt3, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_cnt3 = "); Dz1u32W_fdump(fp, &p->utf8_cnt3, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_arr4 = "); ArrayMemberData1_utf8_arr4W_fdump(fp, p->utf8_arr4, p->utf8_cnt4, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_cnt4 = "); Dz1u32W_fdump(fp, &p->utf8_cnt4, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_arr5 = "); ArrayMemberData1_utf8_arr5W_fdump(fp, p->utf8_arr5, p->utf8_cnt5, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"utf8_cnt5 = "); Dz1u32W_fdump(fp, &p->utf8_cnt5, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// ArrayMemberData1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData2
// void ArrayMemberData2_int_arr1_del(u32_t *src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(ArrayMemberData2, u32_t, int_arr1, unsigned int)
// void ArrayMemberData2_int_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(ArrayMemberData2, u32_t, int_arr1)
// u32_t *ArrayMemberData2_int_arr1_clone(u32_t *src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(ArrayMemberData2, u32_t, int_arr1, unsigned int)
// void ArrayMemberData2_int_arr1A_dump(u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_dump(ArrayMemberData2, u32_t, int_arr1, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData2_int_arr1A_fdump(FILE *fp, u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_fdump(ArrayMemberData2, u32_t, int_arr1, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_int_arr1W_dump(u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_dump(ArrayMemberData2, u32_t, int_arr1, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData2_int_arr1W_fdump(FILE *fp, u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_fdump(ArrayMemberData2, u32_t, int_arr1, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_int_arr2_del(u32_t **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberData2, u32_t*, int_arr2, unsigned int, Dz1u32_del)
// void ArrayMemberData2_int_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberData2, u32_t*, int_arr2, unsigned int)
// u32_t **ArrayMemberData2_int_arr2_clone(u32_t **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberData2, u32_t*, int_arr2, unsigned int, Dz1u32_clone)
// void ArrayMemberData2_int_arr2A_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData2, u32_t*, int_arr2, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData2_int_arr2A_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData2, u32_t*, int_arr2, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_int_arr2W_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData2, u32_t*, int_arr2, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData2_int_arr2W_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData2, u32_t*, int_arr2, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_int_arr3_del(u32_t **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptrref_del(ArrayMemberData2, u32_t*, int_arr3, unsigned int)
// void ArrayMemberData2_int_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_delAndSetNull(ArrayMemberData2, u32_t*, int_arr3)
// u32_t **ArrayMemberData2_int_arr3_clone(u32_t **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_clone(ArrayMemberData2, u32_t*, int_arr3, unsigned int)
// void ArrayMemberData2_int_arr3A_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData2, u32_t*, int_arr3, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData2_int_arr3A_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData2, u32_t*, int_arr3, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_int_arr3W_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData2, u32_t*, int_arr3, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData2_int_arr3W_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData2, u32_t*, int_arr3, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_int_arr4A_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData2, u32_t*, int_arr4, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData2_int_arr4A_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData2, u32_t*, int_arr4, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_int_arr4W_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData2, u32_t*, int_arr4, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData2_int_arr4W_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData2, u32_t*, int_arr4, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_int_arr5A_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData2, u32_t*, int_arr5, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData2_int_arr5A_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData2, u32_t*, int_arr5, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_int_arr5W_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData2, u32_t*, int_arr5, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData2_int_arr5W_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData2, u32_t*, int_arr5, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_data_arr1_del(TestDataType *src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(ArrayMemberData2, TestDataType, data_arr1, unsigned int, TestDataType_purge)
// void ArrayMemberData2_data_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(ArrayMemberData2, TestDataType, data_arr1, unsigned int)
// TestDataType *ArrayMemberData2_data_arr1_clone(TestDataType *src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(ArrayMemberData2, TestDataType, data_arr1, unsigned int, TestDataType_copy)
// void ArrayMemberData2_data_arr1A_dump(TestDataType *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_dump(ArrayMemberData2, TestDataType, data_arr1, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData2_data_arr1A_fdump(FILE *fp, TestDataType *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_fdump(ArrayMemberData2, TestDataType, data_arr1, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_data_arr1W_dump(TestDataType *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_dump(ArrayMemberData2, TestDataType, data_arr1, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData2_data_arr1W_fdump(FILE *fp, TestDataType *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_fdump(ArrayMemberData2, TestDataType, data_arr1, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_data_arr2_del(TestDataType **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberData2, TestDataType*, data_arr2, unsigned int, TestDataType_del)
// void ArrayMemberData2_data_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberData2, TestDataType*, data_arr2, unsigned int)
// TestDataType **ArrayMemberData2_data_arr2_clone(TestDataType **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberData2, TestDataType*, data_arr2, unsigned int, TestDataType_clone)
// void ArrayMemberData2_data_arr2A_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData2, TestDataType*, data_arr2, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData2_data_arr2A_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData2, TestDataType*, data_arr2, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_data_arr2W_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData2, TestDataType*, data_arr2, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData2_data_arr2W_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData2, TestDataType*, data_arr2, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_data_arr3_del(TestDataType **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptrref_del(ArrayMemberData2, TestDataType*, data_arr3, unsigned int)
// void ArrayMemberData2_data_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_delAndSetNull(ArrayMemberData2, TestDataType*, data_arr3)
// TestDataType **ArrayMemberData2_data_arr3_clone(TestDataType **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_clone(ArrayMemberData2, TestDataType*, data_arr3, unsigned int)
// void ArrayMemberData2_data_arr3A_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData2, TestDataType*, data_arr3, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData2_data_arr3A_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData2, TestDataType*, data_arr3, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_data_arr3W_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData2, TestDataType*, data_arr3, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData2_data_arr3W_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData2, TestDataType*, data_arr3, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_data_arr4A_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData2, TestDataType*, data_arr4, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData2_data_arr4A_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData2, TestDataType*, data_arr4, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_data_arr4W_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData2, TestDataType*, data_arr4, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData2_data_arr4W_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData2, TestDataType*, data_arr4, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_data_arr5A_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData2, TestDataType*, data_arr5, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData2_data_arr5A_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData2, TestDataType*, data_arr5, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_data_arr5W_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData2, TestDataType*, data_arr5, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData2_data_arr5W_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData2, TestDataType*, data_arr5, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_u8_arr1_del(Dz1Asn1UTF8Str *src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(ArrayMemberData2, Dz1Asn1UTF8Str, u8_arr1, unsigned int, Dz1Asn1UTF8Str_purge)
// void ArrayMemberData2_u8_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(ArrayMemberData2, Dz1Asn1UTF8Str, u8_arr1, unsigned int)
// Dz1Asn1UTF8Str *ArrayMemberData2_u8_arr1_clone(Dz1Asn1UTF8Str *src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(ArrayMemberData2, Dz1Asn1UTF8Str, u8_arr1, unsigned int, Dz1Asn1UTF8Str_copy)
// void ArrayMemberData2_u8_arr1A_dump(Dz1Asn1UTF8Str *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_dump(ArrayMemberData2, Dz1Asn1UTF8Str, u8_arr1, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData2_u8_arr1A_fdump(FILE *fp, Dz1Asn1UTF8Str *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_fdump(ArrayMemberData2, Dz1Asn1UTF8Str, u8_arr1, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_u8_arr1W_dump(Dz1Asn1UTF8Str *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_dump(ArrayMemberData2, Dz1Asn1UTF8Str, u8_arr1, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData2_u8_arr1W_fdump(FILE *fp, Dz1Asn1UTF8Str *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_fdump(ArrayMemberData2, Dz1Asn1UTF8Str, u8_arr1, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_u8_arr2_del(Dz1Asn1UTF8Str **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, Dz1Asn1UTF8Str_del)
// void ArrayMemberData2_u8_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr2, unsigned int)
// Dz1Asn1UTF8Str **ArrayMemberData2_u8_arr2_clone(Dz1Asn1UTF8Str **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, Dz1Asn1UTF8Str_clone)
// void ArrayMemberData2_u8_arr2A_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData2_u8_arr2A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_u8_arr2W_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData2_u8_arr2W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_u8_arr3_del(Dz1Asn1UTF8Str **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptrref_del(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr3, unsigned int)
// void ArrayMemberData2_u8_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_delAndSetNull(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr3)
// Dz1Asn1UTF8Str **ArrayMemberData2_u8_arr3_clone(Dz1Asn1UTF8Str **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_clone(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr3, unsigned int)
// void ArrayMemberData2_u8_arr3A_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr3, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData2_u8_arr3A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr3, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_u8_arr3W_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr3, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData2_u8_arr3W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr3, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_u8_arr4A_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr4, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData2_u8_arr4A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr4, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_u8_arr4W_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr4, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData2_u8_arr4W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr4, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData2_u8_arr5A_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr5, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData2_u8_arr5A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr5, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData2_u8_arr5W_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr5, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData2_u8_arr5W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData2, Dz1Asn1UTF8Str*, u8_arr5, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

ArrayMemberData2 *ArrayMemberData2_new(u32_t *int_arr1/*_e_copy*/, 
									   u32_t **int_arr2/*_e_clone*/, 
									   u32_t **int_arr3/*_e_ref*/, 
									   u32_t **int_arr4/*_ref*/, 
									   u32_t **int_arr5/*_ref*/, 
									   TestDataType *data_arr1/*_e_copy*/, 
									   TestDataType **data_arr2/*_e_clone*/, 
									   TestDataType **data_arr3/*_e_ref*/, 
									   TestDataType **data_arr4/*_ref*/, 
									   TestDataType **data_arr5/*_ref*/, 
									   Dz1Asn1UTF8Str *u8_arr1/*_e_copy*/, 
									   Dz1Asn1UTF8Str **u8_arr2/*_e_clone*/, 
									   Dz1Asn1UTF8Str **u8_arr3/*_e_ref*/, 
									   Dz1Asn1UTF8Str **u8_arr4/*_ref*/, 
									   Dz1Asn1UTF8Str **u8_arr5/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberData2 *__internal_ret = (ArrayMemberData2 *)Dz1Calloc(sizeof(ArrayMemberData2), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ArrayMemberData2_delAndSetNull, (void *)&__internal_ret);
		
		if (int_arr1 != NULL && (__internal_ret->int_arr1 = ArrayMemberData2_int_arr1_clone(int_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
		else if (int_arr2 != NULL && (__internal_ret->int_arr2 = ArrayMemberData2_int_arr2_clone(int_arr2, 16, errp)) == NULL) { ERR_OUT(errp); }
		else if (int_arr3 != NULL && (__internal_ret->int_arr3 = ArrayMemberData2_int_arr3_clone(int_arr3, 16, errp)) == NULL) { ERR_OUT(errp); }
		else if (data_arr1 != NULL && (__internal_ret->data_arr1 = ArrayMemberData2_data_arr1_clone(data_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
		else if (data_arr2 != NULL && (__internal_ret->data_arr2 = ArrayMemberData2_data_arr2_clone(data_arr2, 16, errp)) == NULL) { ERR_OUT(errp); }
		else if (data_arr3 != NULL && (__internal_ret->data_arr3 = ArrayMemberData2_data_arr3_clone(data_arr3, 16, errp)) == NULL) { ERR_OUT(errp); }
		else if (u8_arr1 != NULL && (__internal_ret->u8_arr1 = ArrayMemberData2_u8_arr1_clone(u8_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
		else if (u8_arr2 != NULL && (__internal_ret->u8_arr2 = ArrayMemberData2_u8_arr2_clone(u8_arr2, 16, errp)) == NULL) { ERR_OUT(errp); }
		else if (u8_arr3 != NULL && (__internal_ret->u8_arr3 = ArrayMemberData2_u8_arr3_clone(u8_arr3, 16, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			__internal_ret->int_arr4 = int_arr4;
			__internal_ret->int_arr5 = int_arr5;
			__internal_ret->data_arr4 = data_arr4;
			__internal_ret->data_arr5 = data_arr5;
			__internal_ret->u8_arr4 = u8_arr4;
			__internal_ret->u8_arr5 = u8_arr5;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData2_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ArrayMemberData2_copy(ArrayMemberData2 *dst, ArrayMemberData2 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->int_arr1 != NULL && (dst->int_arr1 = ArrayMemberData2_int_arr1_clone(src->int_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->int_arr2 != NULL && (dst->int_arr2 = ArrayMemberData2_int_arr2_clone(src->int_arr2, 16, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->int_arr3 != NULL && (dst->int_arr3 = ArrayMemberData2_int_arr3_clone(src->int_arr3, 16, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->data_arr1 != NULL && (dst->data_arr1 = ArrayMemberData2_data_arr1_clone(src->data_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->data_arr2 != NULL && (dst->data_arr2 = ArrayMemberData2_data_arr2_clone(src->data_arr2, 16, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->data_arr3 != NULL && (dst->data_arr3 = ArrayMemberData2_data_arr3_clone(src->data_arr3, 16, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->u8_arr1 != NULL && (dst->u8_arr1 = ArrayMemberData2_u8_arr1_clone(src->u8_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->u8_arr2 != NULL && (dst->u8_arr2 = ArrayMemberData2_u8_arr2_clone(src->u8_arr2, 16, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->u8_arr3 != NULL && (dst->u8_arr3 = ArrayMemberData2_u8_arr3_clone(src->u8_arr3, 16, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		dst->int_arr4 = src->int_arr4;
		dst->int_arr5 = src->int_arr5;
		dst->data_arr4 = src->data_arr4;
		dst->data_arr5 = src->data_arr5;
		dst->u8_arr4 = src->u8_arr4;
		dst->u8_arr5 = src->u8_arr5;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ArrayMemberData2 *ArrayMemberData2_clone(ArrayMemberData2 *src, Dz1Error *err)
{
	ArrayMemberData2 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ArrayMemberData2 *)Dz1Calloc(sizeof(ArrayMemberData2), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ArrayMemberData2_delAndSetNull, (void *)&dst);
		if (ArrayMemberData2_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData2_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ArrayMemberData2_purge(ArrayMemberData2 *p)
{
	if (p == NULL) return;
	ArrayMemberData2_int_arr1_del(p->int_arr1, 16);
	ArrayMemberData2_int_arr2_del(p->int_arr2, 16);
	ArrayMemberData2_int_arr3_del(p->int_arr3, 16);
	ArrayMemberData2_data_arr1_del(p->data_arr1, 16);
	ArrayMemberData2_data_arr2_del(p->data_arr2, 16);
	ArrayMemberData2_data_arr3_del(p->data_arr3, 16);
	ArrayMemberData2_u8_arr1_del(p->u8_arr1, 16);
	ArrayMemberData2_u8_arr2_del(p->u8_arr2, 16);
	ArrayMemberData2_u8_arr3_del(p->u8_arr3, 16);
}

void ArrayMemberData2_del(ArrayMemberData2 *p)
{
	if (p == NULL) return;
	ArrayMemberData2_purge(p);
	Dz1Free(p);
}

void ArrayMemberData2A_dump(ArrayMemberData2 *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "int_arr1 = "); ArrayMemberData2_int_arr1A_dump(p->int_arr1, 16, tab);
		Dz1ThreadA_tprintf(tab, "int_arr2 = "); ArrayMemberData2_int_arr2A_dump(p->int_arr2, 16, tab);
		Dz1ThreadA_tprintf(tab, "int_arr3 = "); ArrayMemberData2_int_arr3A_dump(p->int_arr3, 16, tab);
		Dz1ThreadA_tprintf(tab, "int_arr4 = "); ArrayMemberData2_int_arr4A_dump(p->int_arr4, 16, tab);
		Dz1ThreadA_tprintf(tab, "int_arr5 = "); ArrayMemberData2_int_arr5A_dump(p->int_arr5, 16, tab);
		Dz1ThreadA_tprintf(tab, "data_arr1 = "); ArrayMemberData2_data_arr1A_dump(p->data_arr1, 16, tab);
		Dz1ThreadA_tprintf(tab, "data_arr2 = "); ArrayMemberData2_data_arr2A_dump(p->data_arr2, 16, tab);
		Dz1ThreadA_tprintf(tab, "data_arr3 = "); ArrayMemberData2_data_arr3A_dump(p->data_arr3, 16, tab);
		Dz1ThreadA_tprintf(tab, "data_arr4 = "); ArrayMemberData2_data_arr4A_dump(p->data_arr4, 16, tab);
		Dz1ThreadA_tprintf(tab, "data_arr5 = "); ArrayMemberData2_data_arr5A_dump(p->data_arr5, 16, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr1 = "); ArrayMemberData2_u8_arr1A_dump(p->u8_arr1, 16, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr2 = "); ArrayMemberData2_u8_arr2A_dump(p->u8_arr2, 16, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr3 = "); ArrayMemberData2_u8_arr3A_dump(p->u8_arr3, 16, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr4 = "); ArrayMemberData2_u8_arr4A_dump(p->u8_arr4, 16, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr5 = "); ArrayMemberData2_u8_arr5A_dump(p->u8_arr5, 16, tab);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void ArrayMemberData2A_fdump(FILE *fp, ArrayMemberData2 *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintf(fp, tab, "int_arr1 = "); ArrayMemberData2_int_arr1A_fdump(fp, p->int_arr1, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_arr2 = "); ArrayMemberData2_int_arr2A_fdump(fp, p->int_arr2, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_arr3 = "); ArrayMemberData2_int_arr3A_fdump(fp, p->int_arr3, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_arr4 = "); ArrayMemberData2_int_arr4A_fdump(fp, p->int_arr4, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_arr5 = "); ArrayMemberData2_int_arr5A_fdump(fp, p->int_arr5, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr1 = "); ArrayMemberData2_data_arr1A_fdump(fp, p->data_arr1, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr2 = "); ArrayMemberData2_data_arr2A_fdump(fp, p->data_arr2, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr3 = "); ArrayMemberData2_data_arr3A_fdump(fp, p->data_arr3, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr4 = "); ArrayMemberData2_data_arr4A_fdump(fp, p->data_arr4, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr5 = "); ArrayMemberData2_data_arr5A_fdump(fp, p->data_arr5, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr1 = "); ArrayMemberData2_u8_arr1A_fdump(fp, p->u8_arr1, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr2 = "); ArrayMemberData2_u8_arr2A_fdump(fp, p->u8_arr2, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr3 = "); ArrayMemberData2_u8_arr3A_fdump(fp, p->u8_arr3, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr4 = "); ArrayMemberData2_u8_arr4A_fdump(fp, p->u8_arr4, 16, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr5 = "); ArrayMemberData2_u8_arr5A_fdump(fp, p->u8_arr5, 16, tab);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void ArrayMemberData2W_dump(ArrayMemberData2 *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"int_arr1 = "); ArrayMemberData2_int_arr1W_dump(p->int_arr1, 16, tab);
		Dz1ThreadW_tprintf(tab, L"int_arr2 = "); ArrayMemberData2_int_arr2W_dump(p->int_arr2, 16, tab);
		Dz1ThreadW_tprintf(tab, L"int_arr3 = "); ArrayMemberData2_int_arr3W_dump(p->int_arr3, 16, tab);
		Dz1ThreadW_tprintf(tab, L"int_arr4 = "); ArrayMemberData2_int_arr4W_dump(p->int_arr4, 16, tab);
		Dz1ThreadW_tprintf(tab, L"int_arr5 = "); ArrayMemberData2_int_arr5W_dump(p->int_arr5, 16, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr1 = "); ArrayMemberData2_data_arr1W_dump(p->data_arr1, 16, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr2 = "); ArrayMemberData2_data_arr2W_dump(p->data_arr2, 16, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr3 = "); ArrayMemberData2_data_arr3W_dump(p->data_arr3, 16, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr4 = "); ArrayMemberData2_data_arr4W_dump(p->data_arr4, 16, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr5 = "); ArrayMemberData2_data_arr5W_dump(p->data_arr5, 16, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr1 = "); ArrayMemberData2_u8_arr1W_dump(p->u8_arr1, 16, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr2 = "); ArrayMemberData2_u8_arr2W_dump(p->u8_arr2, 16, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr3 = "); ArrayMemberData2_u8_arr3W_dump(p->u8_arr3, 16, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr4 = "); ArrayMemberData2_u8_arr4W_dump(p->u8_arr4, 16, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr5 = "); ArrayMemberData2_u8_arr5W_dump(p->u8_arr5, 16, tab);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void ArrayMemberData2W_fdump(FILE *fp, ArrayMemberData2 *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr1 = "); ArrayMemberData2_int_arr1W_fdump(fp, p->int_arr1, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr2 = "); ArrayMemberData2_int_arr2W_fdump(fp, p->int_arr2, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr3 = "); ArrayMemberData2_int_arr3W_fdump(fp, p->int_arr3, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr4 = "); ArrayMemberData2_int_arr4W_fdump(fp, p->int_arr4, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr5 = "); ArrayMemberData2_int_arr5W_fdump(fp, p->int_arr5, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr1 = "); ArrayMemberData2_data_arr1W_fdump(fp, p->data_arr1, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr2 = "); ArrayMemberData2_data_arr2W_fdump(fp, p->data_arr2, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr3 = "); ArrayMemberData2_data_arr3W_fdump(fp, p->data_arr3, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr4 = "); ArrayMemberData2_data_arr4W_fdump(fp, p->data_arr4, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr5 = "); ArrayMemberData2_data_arr5W_fdump(fp, p->data_arr5, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr1 = "); ArrayMemberData2_u8_arr1W_fdump(fp, p->u8_arr1, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr2 = "); ArrayMemberData2_u8_arr2W_fdump(fp, p->u8_arr2, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr3 = "); ArrayMemberData2_u8_arr3W_fdump(fp, p->u8_arr3, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr4 = "); ArrayMemberData2_u8_arr4W_fdump(fp, p->u8_arr4, 16, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr5 = "); ArrayMemberData2_u8_arr5W_fdump(fp, p->u8_arr5, 16, tab);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// ArrayMemberData2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData3
// void ArrayMemberData3_int_arr1_del(u32_t *src);
static __inline__ Dz1StructArrayMemb_val_primitive_nocnt_del(ArrayMemberData3, u32_t, int_arr1, (*ap) == 0)
// void ArrayMemberData3_int_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_nocnt_delAndSetNull(ArrayMemberData3, u32_t, int_arr1)
// unsigned int ArrayMemberData3_int_arr1_count(u32_t *src);
static __inline__ Dz1StructArrayMemb_val_primitive_nocnt_count(ArrayMemberData3, u32_t, int_arr1, (*ap) == 0)
// u32_t *ArrayMemberData3_int_arr1_clone(u32_t *src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_nocnt_clone(ArrayMemberData3, u32_t, int_arr1, (*ap) == 0)
// void ArrayMemberData3_int_arr1A_dump(u32_t *p, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_nocntA_dump(ArrayMemberData3, u32_t, int_arr1, (*ap) == 0, " = ", Dz1u32A_dump)
// void ArrayMemberData3_int_arr1A_fdump(FILE *fp, u32_t *p, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_nocntA_fdump(ArrayMemberData3, u32_t, int_arr1, (*ap) == 0, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_int_arr1W_dump(u32_t *p, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_nocntW_dump(ArrayMemberData3, u32_t, int_arr1, (*ap) == 0, " = ", Dz1u32W_dump)
// void ArrayMemberData3_int_arr1W_fdump(FILE *fp, u32_t *p, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_nocntW_fdump(ArrayMemberData3, u32_t, int_arr1, (*ap) == 0, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_int_arr2_del(u32_t **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_del(ArrayMemberData3, u32_t*, int_arr2, (*ap) == NULL, Dz1u32_del)
// void ArrayMemberData3_int_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_delAndSetNull(ArrayMemberData3, u32_t*, int_arr2)
// unsigned int ArrayMemberData3_int_arr2_count(u32_t **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_count(ArrayMemberData3, u32_t*, int_arr2, (*ap) == NULL)
// u32_t **ArrayMemberData3_int_arr2_clone(u32_t **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_clone(ArrayMemberData3, u32_t*, int_arr2, (*ap) == NULL, Dz1u32_clone)
// void ArrayMemberData3_int_arr2A_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData3, u32_t*, int_arr2, (*ap) == NULL, " = ", Dz1u32A_dump)
// void ArrayMemberData3_int_arr2A_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData3, u32_t*, int_arr2, (*ap) == NULL, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_int_arr2W_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData3, u32_t*, int_arr2, (*ap) == NULL, " = ", Dz1u32W_dump)
// void ArrayMemberData3_int_arr2W_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData3, u32_t*, int_arr2, (*ap) == NULL, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_int_arr3_del(u32_t **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_del(ArrayMemberData3, u32_t*, int_arr3, (*ap) == NULL)
// void ArrayMemberData3_int_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_delAndSetNull(ArrayMemberData3, u32_t*, int_arr3)
// unsigned int ArrayMemberData3_int_arr3_count(u32_t **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_count(ArrayMemberData3, u32_t*, int_arr3, (*ap) == NULL)
// u32_t **ArrayMemberData3_int_arr3_clone(u32_t **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_clone(ArrayMemberData3, u32_t*, int_arr3, (*ap) == NULL)
// void ArrayMemberData3_int_arr3A_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData3, u32_t*, int_arr3, (*ap) == NULL, " = ", Dz1u32A_dump)
// void ArrayMemberData3_int_arr3A_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData3, u32_t*, int_arr3, (*ap) == NULL, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_int_arr3W_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData3, u32_t*, int_arr3, (*ap) == NULL, " = ", Dz1u32W_dump)
// void ArrayMemberData3_int_arr3W_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData3, u32_t*, int_arr3, (*ap) == NULL, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_int_arr4A_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData3, u32_t*, int_arr4, (*ap) == NULL, " = ", Dz1u32A_dump)
// void ArrayMemberData3_int_arr4A_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData3, u32_t*, int_arr4, (*ap) == NULL, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_int_arr4W_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData3, u32_t*, int_arr4, (*ap) == NULL, " = ", Dz1u32W_dump)
// void ArrayMemberData3_int_arr4W_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData3, u32_t*, int_arr4, (*ap) == NULL, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_int_arr5A_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData3, u32_t*, int_arr5, (*ap) == NULL, " = ", Dz1u32A_dump)
// void ArrayMemberData3_int_arr5A_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData3, u32_t*, int_arr5, (*ap) == NULL, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_int_arr5W_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData3, u32_t*, int_arr5, (*ap) == NULL, " = ", Dz1u32W_dump)
// void ArrayMemberData3_int_arr5W_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData3, u32_t*, int_arr5, (*ap) == NULL, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_data_arr1_del(TestDataType *src);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_del(ArrayMemberData3, TestDataType, data_arr1, ap->id == 0, TestDataType_purge)
// void ArrayMemberData3_data_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_delAndSetNull(ArrayMemberData3, TestDataType, data_arr1)
// unsigned int ArrayMemberData3_data_arr1_count(TestDataType *src);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_count(ArrayMemberData3, TestDataType, data_arr1, ap->id == 0)
// TestDataType *ArrayMemberData3_data_arr1_clone(TestDataType *src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_clone(ArrayMemberData3, TestDataType, data_arr1, ap->id == 0, TestDataType_copy)
// void ArrayMemberData3_data_arr1A_dump(TestDataType *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntA_dump(ArrayMemberData3, TestDataType, data_arr1, ap->id == 0, " = ", TestDataTypeA_dump)
// void ArrayMemberData3_data_arr1A_fdump(FILE *fp, TestDataType *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntA_fdump(ArrayMemberData3, TestDataType, data_arr1, ap->id == 0, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_data_arr1W_dump(TestDataType *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntW_dump(ArrayMemberData3, TestDataType, data_arr1, ap->id == 0, " = ", TestDataTypeW_dump)
// void ArrayMemberData3_data_arr1W_fdump(FILE *fp, TestDataType *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntW_fdump(ArrayMemberData3, TestDataType, data_arr1, ap->id == 0, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_data_arr2_del(TestDataType **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_del(ArrayMemberData3, TestDataType*, data_arr2, (*ap) == NULL, TestDataType_del)
// void ArrayMemberData3_data_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_delAndSetNull(ArrayMemberData3, TestDataType*, data_arr2)
// unsigned int ArrayMemberData3_data_arr2_count(TestDataType **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_count(ArrayMemberData3, TestDataType*, data_arr2, (*ap) == NULL)
// TestDataType **ArrayMemberData3_data_arr2_clone(TestDataType **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_clone(ArrayMemberData3, TestDataType*, data_arr2, (*ap) == NULL, TestDataType_clone)
// void ArrayMemberData3_data_arr2A_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData3, TestDataType*, data_arr2, (*ap) == NULL, " = ", TestDataTypeA_dump)
// void ArrayMemberData3_data_arr2A_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData3, TestDataType*, data_arr2, (*ap) == NULL, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_data_arr2W_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData3, TestDataType*, data_arr2, (*ap) == NULL, " = ", TestDataTypeW_dump)
// void ArrayMemberData3_data_arr2W_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData3, TestDataType*, data_arr2, (*ap) == NULL, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_data_arr3_del(TestDataType **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_del(ArrayMemberData3, TestDataType*, data_arr3, (*ap) == NULL)
// void ArrayMemberData3_data_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_delAndSetNull(ArrayMemberData3, TestDataType*, data_arr3)
// unsigned int ArrayMemberData3_data_arr3_count(TestDataType **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_count(ArrayMemberData3, TestDataType*, data_arr3, (*ap) == NULL)
// TestDataType **ArrayMemberData3_data_arr3_clone(TestDataType **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_clone(ArrayMemberData3, TestDataType*, data_arr3, (*ap) == NULL)
// void ArrayMemberData3_data_arr3A_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData3, TestDataType*, data_arr3, (*ap) == NULL, " = ", TestDataTypeA_dump)
// void ArrayMemberData3_data_arr3A_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData3, TestDataType*, data_arr3, (*ap) == NULL, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_data_arr3W_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData3, TestDataType*, data_arr3, (*ap) == NULL, " = ", TestDataTypeW_dump)
// void ArrayMemberData3_data_arr3W_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData3, TestDataType*, data_arr3, (*ap) == NULL, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_data_arr4A_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData3, TestDataType*, data_arr4, (*ap) == NULL, " = ", TestDataTypeA_dump)
// void ArrayMemberData3_data_arr4A_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData3, TestDataType*, data_arr4, (*ap) == NULL, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_data_arr4W_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData3, TestDataType*, data_arr4, (*ap) == NULL, " = ", TestDataTypeW_dump)
// void ArrayMemberData3_data_arr4W_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData3, TestDataType*, data_arr4, (*ap) == NULL, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_data_arr5A_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData3, TestDataType*, data_arr5, (*ap) == NULL, " = ", TestDataTypeA_dump)
// void ArrayMemberData3_data_arr5A_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData3, TestDataType*, data_arr5, (*ap) == NULL, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_data_arr5W_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData3, TestDataType*, data_arr5, (*ap) == NULL, " = ", TestDataTypeW_dump)
// void ArrayMemberData3_data_arr5W_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData3, TestDataType*, data_arr5, (*ap) == NULL, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_u8_arr1_del(Dz1Asn1UTF8Str *src);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_del(ArrayMemberData3, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, Dz1Asn1UTF8Str_purge)
// void ArrayMemberData3_u8_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_delAndSetNull(ArrayMemberData3, Dz1Asn1UTF8Str, u8_arr1)
// unsigned int ArrayMemberData3_u8_arr1_count(Dz1Asn1UTF8Str *src);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_count(ArrayMemberData3, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0)
// Dz1Asn1UTF8Str *ArrayMemberData3_u8_arr1_clone(Dz1Asn1UTF8Str *src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_clone(ArrayMemberData3, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, Dz1Asn1UTF8Str_copy)
// void ArrayMemberData3_u8_arr1A_dump(Dz1Asn1UTF8Str *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntA_dump(ArrayMemberData3, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData3_u8_arr1A_fdump(FILE *fp, Dz1Asn1UTF8Str *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntA_fdump(ArrayMemberData3, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_u8_arr1W_dump(Dz1Asn1UTF8Str *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntW_dump(ArrayMemberData3, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData3_u8_arr1W_fdump(FILE *fp, Dz1Asn1UTF8Str *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntW_fdump(ArrayMemberData3, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_u8_arr2_del(Dz1Asn1UTF8Str **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_del(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, Dz1Asn1UTF8Str_del)
// void ArrayMemberData3_u8_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_delAndSetNull(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr2)
// unsigned int ArrayMemberData3_u8_arr2_count(Dz1Asn1UTF8Str **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_count(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL)
// Dz1Asn1UTF8Str **ArrayMemberData3_u8_arr2_clone(Dz1Asn1UTF8Str **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_clone(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, Dz1Asn1UTF8Str_clone)
// void ArrayMemberData3_u8_arr2A_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData3_u8_arr2A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_u8_arr2W_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData3_u8_arr2W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_u8_arr3_del(Dz1Asn1UTF8Str **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_del(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL)
// void ArrayMemberData3_u8_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_delAndSetNull(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr3)
// unsigned int ArrayMemberData3_u8_arr3_count(Dz1Asn1UTF8Str **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_count(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL)
// Dz1Asn1UTF8Str **ArrayMemberData3_u8_arr3_clone(Dz1Asn1UTF8Str **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_clone(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL)
// void ArrayMemberData3_u8_arr3A_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData3_u8_arr3A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_u8_arr3W_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData3_u8_arr3W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_u8_arr4A_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr4, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData3_u8_arr4A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr4, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_u8_arr4W_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr4, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData3_u8_arr4W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr4, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData3_u8_arr5A_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr5, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData3_u8_arr5A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr5, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData3_u8_arr5W_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr5, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData3_u8_arr5W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData3, Dz1Asn1UTF8Str*, u8_arr5, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

ArrayMemberData3 *ArrayMemberData3_new(u32_t *int_arr1/*_e_copy*/, 
									   u32_t **int_arr2/*_e_clone*/, 
									   u32_t **int_arr3/*_e_ref*/, 
									   u32_t **int_arr4/*_ref*/, 
									   u32_t **int_arr5/*_ref*/, 
									   TestDataType *data_arr1/*_e_copy*/, 
									   TestDataType **data_arr2/*_e_clone*/, 
									   TestDataType **data_arr3/*_e_ref*/, 
									   TestDataType **data_arr4/*_ref*/, 
									   TestDataType **data_arr5/*_ref*/, 
									   Dz1Asn1UTF8Str *u8_arr1/*_e_copy*/, 
									   Dz1Asn1UTF8Str **u8_arr2/*_e_clone*/, 
									   Dz1Asn1UTF8Str **u8_arr3/*_e_ref*/, 
									   Dz1Asn1UTF8Str **u8_arr4/*_ref*/, 
									   Dz1Asn1UTF8Str **u8_arr5/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberData3 *__internal_ret = (ArrayMemberData3 *)Dz1Calloc(sizeof(ArrayMemberData3), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ArrayMemberData3_delAndSetNull, (void *)&__internal_ret);
		
		if (int_arr1 != NULL && (__internal_ret->int_arr1 = ArrayMemberData3_int_arr1_clone(int_arr1, errp)) == NULL) { ERR_OUT(errp); }
		else if (int_arr2 != NULL && (__internal_ret->int_arr2 = ArrayMemberData3_int_arr2_clone(int_arr2, errp)) == NULL) { ERR_OUT(errp); }
		else if (int_arr3 != NULL && (__internal_ret->int_arr3 = ArrayMemberData3_int_arr3_clone(int_arr3, errp)) == NULL) { ERR_OUT(errp); }
		else if (data_arr1 != NULL && (__internal_ret->data_arr1 = ArrayMemberData3_data_arr1_clone(data_arr1, errp)) == NULL) { ERR_OUT(errp); }
		else if (data_arr2 != NULL && (__internal_ret->data_arr2 = ArrayMemberData3_data_arr2_clone(data_arr2, errp)) == NULL) { ERR_OUT(errp); }
		else if (data_arr3 != NULL && (__internal_ret->data_arr3 = ArrayMemberData3_data_arr3_clone(data_arr3, errp)) == NULL) { ERR_OUT(errp); }
		else if (u8_arr1 != NULL && (__internal_ret->u8_arr1 = ArrayMemberData3_u8_arr1_clone(u8_arr1, errp)) == NULL) { ERR_OUT(errp); }
		else if (u8_arr2 != NULL && (__internal_ret->u8_arr2 = ArrayMemberData3_u8_arr2_clone(u8_arr2, errp)) == NULL) { ERR_OUT(errp); }
		else if (u8_arr3 != NULL && (__internal_ret->u8_arr3 = ArrayMemberData3_u8_arr3_clone(u8_arr3, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			__internal_ret->int_arr4 = int_arr4;
			__internal_ret->int_arr5 = int_arr5;
			__internal_ret->data_arr4 = data_arr4;
			__internal_ret->data_arr5 = data_arr5;
			__internal_ret->u8_arr4 = u8_arr4;
			__internal_ret->u8_arr5 = u8_arr5;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData3_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ArrayMemberData3_copy(ArrayMemberData3 *dst, ArrayMemberData3 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->int_arr1 != NULL && (dst->int_arr1 = ArrayMemberData3_int_arr1_clone(src->int_arr1, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->int_arr2 != NULL && (dst->int_arr2 = ArrayMemberData3_int_arr2_clone(src->int_arr2, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->int_arr3 != NULL && (dst->int_arr3 = ArrayMemberData3_int_arr3_clone(src->int_arr3, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->data_arr1 != NULL && (dst->data_arr1 = ArrayMemberData3_data_arr1_clone(src->data_arr1, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->data_arr2 != NULL && (dst->data_arr2 = ArrayMemberData3_data_arr2_clone(src->data_arr2, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->data_arr3 != NULL && (dst->data_arr3 = ArrayMemberData3_data_arr3_clone(src->data_arr3, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->u8_arr1 != NULL && (dst->u8_arr1 = ArrayMemberData3_u8_arr1_clone(src->u8_arr1, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->u8_arr2 != NULL && (dst->u8_arr2 = ArrayMemberData3_u8_arr2_clone(src->u8_arr2, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->u8_arr3 != NULL && (dst->u8_arr3 = ArrayMemberData3_u8_arr3_clone(src->u8_arr3, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		dst->int_arr4 = src->int_arr4;
		dst->int_arr5 = src->int_arr5;
		dst->data_arr4 = src->data_arr4;
		dst->data_arr5 = src->data_arr5;
		dst->u8_arr4 = src->u8_arr4;
		dst->u8_arr5 = src->u8_arr5;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ArrayMemberData3 *ArrayMemberData3_clone(ArrayMemberData3 *src, Dz1Error *err)
{
	ArrayMemberData3 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ArrayMemberData3 *)Dz1Calloc(sizeof(ArrayMemberData3), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ArrayMemberData3_delAndSetNull, (void *)&dst);
		if (ArrayMemberData3_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData3_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ArrayMemberData3_purge(ArrayMemberData3 *p)
{
	if (p == NULL) return;
	ArrayMemberData3_int_arr1_del(p->int_arr1);
	ArrayMemberData3_int_arr2_del(p->int_arr2);
	ArrayMemberData3_int_arr3_del(p->int_arr3);
	ArrayMemberData3_data_arr1_del(p->data_arr1);
	ArrayMemberData3_data_arr2_del(p->data_arr2);
	ArrayMemberData3_data_arr3_del(p->data_arr3);
	ArrayMemberData3_u8_arr1_del(p->u8_arr1);
	ArrayMemberData3_u8_arr2_del(p->u8_arr2);
	ArrayMemberData3_u8_arr3_del(p->u8_arr3);
}

void ArrayMemberData3_del(ArrayMemberData3 *p)
{
	if (p == NULL) return;
	ArrayMemberData3_purge(p);
	Dz1Free(p);
}

void ArrayMemberData3A_dump(ArrayMemberData3 *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "int_arr1 = "); ArrayMemberData3_int_arr1A_dump(p->int_arr1, tab);
		Dz1ThreadA_tprintf(tab, "int_arr2 = "); ArrayMemberData3_int_arr2A_dump(p->int_arr2, tab);
		Dz1ThreadA_tprintf(tab, "int_arr3 = "); ArrayMemberData3_int_arr3A_dump(p->int_arr3, tab);
		Dz1ThreadA_tprintf(tab, "int_arr4 = "); ArrayMemberData3_int_arr4A_dump(p->int_arr4, tab);
		Dz1ThreadA_tprintf(tab, "int_arr5 = "); ArrayMemberData3_int_arr5A_dump(p->int_arr5, tab);
		Dz1ThreadA_tprintf(tab, "data_arr1 = "); ArrayMemberData3_data_arr1A_dump(p->data_arr1, tab);
		Dz1ThreadA_tprintf(tab, "data_arr2 = "); ArrayMemberData3_data_arr2A_dump(p->data_arr2, tab);
		Dz1ThreadA_tprintf(tab, "data_arr3 = "); ArrayMemberData3_data_arr3A_dump(p->data_arr3, tab);
		Dz1ThreadA_tprintf(tab, "data_arr4 = "); ArrayMemberData3_data_arr4A_dump(p->data_arr4, tab);
		Dz1ThreadA_tprintf(tab, "data_arr5 = "); ArrayMemberData3_data_arr5A_dump(p->data_arr5, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr1 = "); ArrayMemberData3_u8_arr1A_dump(p->u8_arr1, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr2 = "); ArrayMemberData3_u8_arr2A_dump(p->u8_arr2, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr3 = "); ArrayMemberData3_u8_arr3A_dump(p->u8_arr3, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr4 = "); ArrayMemberData3_u8_arr4A_dump(p->u8_arr4, tab);
		Dz1ThreadA_tprintf(tab, "u8_arr5 = "); ArrayMemberData3_u8_arr5A_dump(p->u8_arr5, tab);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void ArrayMemberData3A_fdump(FILE *fp, ArrayMemberData3 *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintf(fp, tab, "int_arr1 = "); ArrayMemberData3_int_arr1A_fdump(fp, p->int_arr1, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_arr2 = "); ArrayMemberData3_int_arr2A_fdump(fp, p->int_arr2, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_arr3 = "); ArrayMemberData3_int_arr3A_fdump(fp, p->int_arr3, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_arr4 = "); ArrayMemberData3_int_arr4A_fdump(fp, p->int_arr4, tab);
		Dz1ThreadA_ftprintf(fp, tab, "int_arr5 = "); ArrayMemberData3_int_arr5A_fdump(fp, p->int_arr5, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr1 = "); ArrayMemberData3_data_arr1A_fdump(fp, p->data_arr1, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr2 = "); ArrayMemberData3_data_arr2A_fdump(fp, p->data_arr2, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr3 = "); ArrayMemberData3_data_arr3A_fdump(fp, p->data_arr3, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr4 = "); ArrayMemberData3_data_arr4A_fdump(fp, p->data_arr4, tab);
		Dz1ThreadA_ftprintf(fp, tab, "data_arr5 = "); ArrayMemberData3_data_arr5A_fdump(fp, p->data_arr5, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr1 = "); ArrayMemberData3_u8_arr1A_fdump(fp, p->u8_arr1, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr2 = "); ArrayMemberData3_u8_arr2A_fdump(fp, p->u8_arr2, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr3 = "); ArrayMemberData3_u8_arr3A_fdump(fp, p->u8_arr3, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr4 = "); ArrayMemberData3_u8_arr4A_fdump(fp, p->u8_arr4, tab);
		Dz1ThreadA_ftprintf(fp, tab, "u8_arr5 = "); ArrayMemberData3_u8_arr5A_fdump(fp, p->u8_arr5, tab);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void ArrayMemberData3W_dump(ArrayMemberData3 *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"int_arr1 = "); ArrayMemberData3_int_arr1W_dump(p->int_arr1, tab);
		Dz1ThreadW_tprintf(tab, L"int_arr2 = "); ArrayMemberData3_int_arr2W_dump(p->int_arr2, tab);
		Dz1ThreadW_tprintf(tab, L"int_arr3 = "); ArrayMemberData3_int_arr3W_dump(p->int_arr3, tab);
		Dz1ThreadW_tprintf(tab, L"int_arr4 = "); ArrayMemberData3_int_arr4W_dump(p->int_arr4, tab);
		Dz1ThreadW_tprintf(tab, L"int_arr5 = "); ArrayMemberData3_int_arr5W_dump(p->int_arr5, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr1 = "); ArrayMemberData3_data_arr1W_dump(p->data_arr1, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr2 = "); ArrayMemberData3_data_arr2W_dump(p->data_arr2, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr3 = "); ArrayMemberData3_data_arr3W_dump(p->data_arr3, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr4 = "); ArrayMemberData3_data_arr4W_dump(p->data_arr4, tab);
		Dz1ThreadW_tprintf(tab, L"data_arr5 = "); ArrayMemberData3_data_arr5W_dump(p->data_arr5, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr1 = "); ArrayMemberData3_u8_arr1W_dump(p->u8_arr1, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr2 = "); ArrayMemberData3_u8_arr2W_dump(p->u8_arr2, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr3 = "); ArrayMemberData3_u8_arr3W_dump(p->u8_arr3, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr4 = "); ArrayMemberData3_u8_arr4W_dump(p->u8_arr4, tab);
		Dz1ThreadW_tprintf(tab, L"u8_arr5 = "); ArrayMemberData3_u8_arr5W_dump(p->u8_arr5, tab);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void ArrayMemberData3W_fdump(FILE *fp, ArrayMemberData3 *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr1 = "); ArrayMemberData3_int_arr1W_fdump(fp, p->int_arr1, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr2 = "); ArrayMemberData3_int_arr2W_fdump(fp, p->int_arr2, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr3 = "); ArrayMemberData3_int_arr3W_fdump(fp, p->int_arr3, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr4 = "); ArrayMemberData3_int_arr4W_fdump(fp, p->int_arr4, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"int_arr5 = "); ArrayMemberData3_int_arr5W_fdump(fp, p->int_arr5, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr1 = "); ArrayMemberData3_data_arr1W_fdump(fp, p->data_arr1, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr2 = "); ArrayMemberData3_data_arr2W_fdump(fp, p->data_arr2, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr3 = "); ArrayMemberData3_data_arr3W_fdump(fp, p->data_arr3, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr4 = "); ArrayMemberData3_data_arr4W_fdump(fp, p->data_arr4, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"data_arr5 = "); ArrayMemberData3_data_arr5W_fdump(fp, p->data_arr5, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr1 = "); ArrayMemberData3_u8_arr1W_fdump(fp, p->u8_arr1, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr2 = "); ArrayMemberData3_u8_arr2W_fdump(fp, p->u8_arr2, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr3 = "); ArrayMemberData3_u8_arr3W_fdump(fp, p->u8_arr3, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr4 = "); ArrayMemberData3_u8_arr4W_fdump(fp, p->u8_arr4, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"u8_arr5 = "); ArrayMemberData3_u8_arr5W_fdump(fp, p->u8_arr5, tab);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// ArrayMemberData3
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData4Present
static struct ArrayMemberData4PresentMapA
{
	str_t str;
	ArrayMemberData4Present v;
} ArrayMemberData4PresentMapA[] =
{
	{ (char *)"int_arr1", ArrayMemberData4Present_int_arr1 },
	{ (char *)"int_arr2", ArrayMemberData4Present_int_arr2 },
	{ (char *)"int_arr3", ArrayMemberData4Present_int_arr3 },
	{ (char *)"int_arr4", ArrayMemberData4Present_int_arr4 },
	{ (char *)"int_arr5", ArrayMemberData4Present_int_arr5 },
	{ (char *)"int_arr6", ArrayMemberData4Present_int_arr6 },
	{ (char *)"data_arr1", ArrayMemberData4Present_data_arr1 },
	{ (char *)"data_arr2", ArrayMemberData4Present_data_arr2 },
	{ (char *)"data_arr3", ArrayMemberData4Present_data_arr3 },
	{ (char *)"data_arr4", ArrayMemberData4Present_data_arr4 },
	{ (char *)"data_arr5", ArrayMemberData4Present_data_arr5 },
	{ (char *)"u8_arr1", ArrayMemberData4Present_u8_arr1 },
	{ (char *)"u8_arr2", ArrayMemberData4Present_u8_arr2 },
	{ (char *)"u8_arr3", ArrayMemberData4Present_u8_arr3 },
	{ (char *)"u8_arr4", ArrayMemberData4Present_u8_arr4 },
	{ (char *)"u8_arr5", ArrayMemberData4Present_u8_arr5 },
	{ NULL, ArrayMemberData4Present_max }
};

str_t ArrayMemberData4PresentStrA(ArrayMemberData4Present v)
{
	struct ArrayMemberData4PresentMapA *i = NULL;
	for (i = ArrayMemberData4PresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ArrayMemberData4Present ArrayMemberData4PresentFromStrA(str_t str)
{
	struct ArrayMemberData4PresentMapA *i = NULL;
	for (i = ArrayMemberData4PresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ArrayMemberData4Present_max;
}
#ifndef UNIX_SYSTEM
static struct ArrayMemberData4PresentMapW
{
	wstr_t str;
	ArrayMemberData4Present v;
} ArrayMemberData4PresentMapW[] =
{
	{ (wchar_t *)L"int_arr1", ArrayMemberData4Present_int_arr1 },
	{ (wchar_t *)L"int_arr2", ArrayMemberData4Present_int_arr2 },
	{ (wchar_t *)L"int_arr3", ArrayMemberData4Present_int_arr3 },
	{ (wchar_t *)L"int_arr4", ArrayMemberData4Present_int_arr4 },
	{ (wchar_t *)L"int_arr5", ArrayMemberData4Present_int_arr5 },
	{ (wchar_t *)L"int_arr6", ArrayMemberData4Present_int_arr6 },
	{ (wchar_t *)L"data_arr1", ArrayMemberData4Present_data_arr1 },
	{ (wchar_t *)L"data_arr2", ArrayMemberData4Present_data_arr2 },
	{ (wchar_t *)L"data_arr3", ArrayMemberData4Present_data_arr3 },
	{ (wchar_t *)L"data_arr4", ArrayMemberData4Present_data_arr4 },
	{ (wchar_t *)L"data_arr5", ArrayMemberData4Present_data_arr5 },
	{ (wchar_t *)L"u8_arr1", ArrayMemberData4Present_u8_arr1 },
	{ (wchar_t *)L"u8_arr2", ArrayMemberData4Present_u8_arr2 },
	{ (wchar_t *)L"u8_arr3", ArrayMemberData4Present_u8_arr3 },
	{ (wchar_t *)L"u8_arr4", ArrayMemberData4Present_u8_arr4 },
	{ (wchar_t *)L"u8_arr5", ArrayMemberData4Present_u8_arr5 },
	{ NULL, ArrayMemberData4Present_max }
};

wstr_t ArrayMemberData4PresentStrW(ArrayMemberData4Present v)
{
	struct ArrayMemberData4PresentMapW *i = NULL;
	for (i = ArrayMemberData4PresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ArrayMemberData4Present ArrayMemberData4PresentFromStrW(wstr_t str)
{
	struct ArrayMemberData4PresentMapW *i = NULL;
	for (i = ArrayMemberData4PresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ArrayMemberData4Present_max;
}
#endif // UNIX_SYSTEM

ArrayMemberData4Present *ArrayMemberData4Present_new(ArrayMemberData4Present *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberData4Present *__internal_ret = (ArrayMemberData4Present *)Dz1Calloc(sizeof(ArrayMemberData4Present), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ArrayMemberData4PresentA_dump(ArrayMemberData4Present *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", ArrayMemberData4PresentStrA(*v));
}
void ArrayMemberData4PresentA_fdump(FILE *fp, ArrayMemberData4Present *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", ArrayMemberData4PresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void ArrayMemberData4PresentW_dump(ArrayMemberData4Present *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", ArrayMemberData4PresentStrW(*v));
}
void ArrayMemberData4PresentW_fdump(FILE *fp, ArrayMemberData4Present *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", ArrayMemberData4PresentStrW(*v));
}
#endif // UNIX_SYSTEM
// ArrayMemberData4Present
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData4
// void ArrayMemberData4_int_arr1_del(u32_t *src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(ArrayMemberData4, u32_t, int_arr1, unsigned int)
// void ArrayMemberData4_int_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(ArrayMemberData4, u32_t, int_arr1)
// u32_t *ArrayMemberData4_int_arr1_clone(u32_t *src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(ArrayMemberData4, u32_t, int_arr1, unsigned int)
// void ArrayMemberData4_int_arr1A_dump(u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_dump(ArrayMemberData4, u32_t, int_arr1, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData4_int_arr1A_fdump(FILE *fp, u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_fdump(ArrayMemberData4, u32_t, int_arr1, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_int_arr1W_dump(u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_dump(ArrayMemberData4, u32_t, int_arr1, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData4_int_arr1W_fdump(FILE *fp, u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_fdump(ArrayMemberData4, u32_t, int_arr1, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_int_arr2_del(u32_t *src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(ArrayMemberData4, u32_t, int_arr2, unsigned int)
// void ArrayMemberData4_int_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(ArrayMemberData4, u32_t, int_arr2)
// u32_t *ArrayMemberData4_int_arr2_clone(u32_t *src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(ArrayMemberData4, u32_t, int_arr2, unsigned int)
// void ArrayMemberData4_int_arr2A_dump(u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_dump(ArrayMemberData4, u32_t, int_arr2, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData4_int_arr2A_fdump(FILE *fp, u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_fdump(ArrayMemberData4, u32_t, int_arr2, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_int_arr2W_dump(u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_dump(ArrayMemberData4, u32_t, int_arr2, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData4_int_arr2W_fdump(FILE *fp, u32_t *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_fdump(ArrayMemberData4, u32_t, int_arr2, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_int_arr3_del(u32_t **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberData4, u32_t*, int_arr3, unsigned int, Dz1u32_del)
// void ArrayMemberData4_int_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberData4, u32_t*, int_arr3, unsigned int)
// u32_t **ArrayMemberData4_int_arr3_clone(u32_t **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberData4, u32_t*, int_arr3, unsigned int, Dz1u32_clone)
// void ArrayMemberData4_int_arr3A_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData4, u32_t*, int_arr3, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData4_int_arr3A_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData4, u32_t*, int_arr3, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_int_arr3W_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData4, u32_t*, int_arr3, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData4_int_arr3W_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData4, u32_t*, int_arr3, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_int_arr4A_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData4, u32_t*, int_arr4, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData4_int_arr4A_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData4, u32_t*, int_arr4, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_int_arr4W_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData4, u32_t*, int_arr4, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData4_int_arr4W_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData4, u32_t*, int_arr4, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_int_arr5_del(u32_t **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptrref_del(ArrayMemberData4, u32_t*, int_arr5, unsigned int)
// void ArrayMemberData4_int_arr5_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_delAndSetNull(ArrayMemberData4, u32_t*, int_arr5)
// u32_t **ArrayMemberData4_int_arr5_clone(u32_t **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_clone(ArrayMemberData4, u32_t*, int_arr5, unsigned int)
// void ArrayMemberData4_int_arr5A_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData4, u32_t*, int_arr5, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData4_int_arr5A_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData4, u32_t*, int_arr5, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_int_arr5W_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData4, u32_t*, int_arr5, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData4_int_arr5W_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData4, u32_t*, int_arr5, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_int_arr6A_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData4, u32_t*, int_arr6, unsigned int, " = ", Dz1u32A_dump)
// void ArrayMemberData4_int_arr6A_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData4, u32_t*, int_arr6, unsigned int, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_int_arr6W_dump(u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData4, u32_t*, int_arr6, unsigned int, " = ", Dz1u32W_dump)
// void ArrayMemberData4_int_arr6W_fdump(FILE *fp, u32_t **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData4, u32_t*, int_arr6, unsigned int, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_data_arr1_del(TestDataType *src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(ArrayMemberData4, TestDataType, data_arr1, unsigned int, TestDataType_purge)
// void ArrayMemberData4_data_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(ArrayMemberData4, TestDataType, data_arr1, unsigned int)
// TestDataType *ArrayMemberData4_data_arr1_clone(TestDataType *src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(ArrayMemberData4, TestDataType, data_arr1, unsigned int, TestDataType_copy)
// void ArrayMemberData4_data_arr1A_dump(TestDataType *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_dump(ArrayMemberData4, TestDataType, data_arr1, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData4_data_arr1A_fdump(FILE *fp, TestDataType *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_fdump(ArrayMemberData4, TestDataType, data_arr1, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_data_arr1W_dump(TestDataType *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_dump(ArrayMemberData4, TestDataType, data_arr1, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData4_data_arr1W_fdump(FILE *fp, TestDataType *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_fdump(ArrayMemberData4, TestDataType, data_arr1, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_data_arr2_del(TestDataType **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberData4, TestDataType*, data_arr2, unsigned int, TestDataType_del)
// void ArrayMemberData4_data_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberData4, TestDataType*, data_arr2, unsigned int)
// TestDataType **ArrayMemberData4_data_arr2_clone(TestDataType **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberData4, TestDataType*, data_arr2, unsigned int, TestDataType_clone)
// void ArrayMemberData4_data_arr2A_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData4, TestDataType*, data_arr2, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData4_data_arr2A_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData4, TestDataType*, data_arr2, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_data_arr2W_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData4, TestDataType*, data_arr2, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData4_data_arr2W_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData4, TestDataType*, data_arr2, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_data_arr3_del(TestDataType **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptrref_del(ArrayMemberData4, TestDataType*, data_arr3, unsigned int)
// void ArrayMemberData4_data_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_delAndSetNull(ArrayMemberData4, TestDataType*, data_arr3)
// TestDataType **ArrayMemberData4_data_arr3_clone(TestDataType **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_clone(ArrayMemberData4, TestDataType*, data_arr3, unsigned int)
// void ArrayMemberData4_data_arr3A_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData4, TestDataType*, data_arr3, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData4_data_arr3A_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData4, TestDataType*, data_arr3, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_data_arr3W_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData4, TestDataType*, data_arr3, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData4_data_arr3W_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData4, TestDataType*, data_arr3, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_data_arr4A_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData4, TestDataType*, data_arr4, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData4_data_arr4A_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData4, TestDataType*, data_arr4, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_data_arr4W_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData4, TestDataType*, data_arr4, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData4_data_arr4W_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData4, TestDataType*, data_arr4, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_data_arr5A_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData4, TestDataType*, data_arr5, unsigned int, " = ", TestDataTypeA_dump)
// void ArrayMemberData4_data_arr5A_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData4, TestDataType*, data_arr5, unsigned int, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_data_arr5W_dump(TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData4, TestDataType*, data_arr5, unsigned int, " = ", TestDataTypeW_dump)
// void ArrayMemberData4_data_arr5W_fdump(FILE *fp, TestDataType **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData4, TestDataType*, data_arr5, unsigned int, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_u8_arr1_del(Dz1Asn1UTF8Str *src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(ArrayMemberData4, Dz1Asn1UTF8Str, u8_arr1, unsigned int, Dz1Asn1UTF8Str_purge)
// void ArrayMemberData4_u8_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(ArrayMemberData4, Dz1Asn1UTF8Str, u8_arr1, unsigned int)
// Dz1Asn1UTF8Str *ArrayMemberData4_u8_arr1_clone(Dz1Asn1UTF8Str *src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(ArrayMemberData4, Dz1Asn1UTF8Str, u8_arr1, unsigned int, Dz1Asn1UTF8Str_copy)
// void ArrayMemberData4_u8_arr1A_dump(Dz1Asn1UTF8Str *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_dump(ArrayMemberData4, Dz1Asn1UTF8Str, u8_arr1, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData4_u8_arr1A_fdump(FILE *fp, Dz1Asn1UTF8Str *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_fdump(ArrayMemberData4, Dz1Asn1UTF8Str, u8_arr1, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_u8_arr1W_dump(Dz1Asn1UTF8Str *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_dump(ArrayMemberData4, Dz1Asn1UTF8Str, u8_arr1, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData4_u8_arr1W_fdump(FILE *fp, Dz1Asn1UTF8Str *p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_fdump(ArrayMemberData4, Dz1Asn1UTF8Str, u8_arr1, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_u8_arr2_del(Dz1Asn1UTF8Str **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, Dz1Asn1UTF8Str_del)
// void ArrayMemberData4_u8_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr2, unsigned int)
// Dz1Asn1UTF8Str **ArrayMemberData4_u8_arr2_clone(Dz1Asn1UTF8Str **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, Dz1Asn1UTF8Str_clone)
// void ArrayMemberData4_u8_arr2A_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData4_u8_arr2A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_u8_arr2W_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData4_u8_arr2W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr2, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_u8_arr3_del(Dz1Asn1UTF8Str **src, unsigned int cnt);
static __inline__ Dz1StructArrayMemb_ptrref_del(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr3, unsigned int)
// void ArrayMemberData4_u8_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_delAndSetNull(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr3)
// Dz1Asn1UTF8Str **ArrayMemberData4_u8_arr3_clone(Dz1Asn1UTF8Str **src, unsigned int cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_clone(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr3, unsigned int)
// void ArrayMemberData4_u8_arr3A_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr3, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData4_u8_arr3A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr3, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_u8_arr3W_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr3, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData4_u8_arr3W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr3, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_u8_arr4A_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr4, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData4_u8_arr4A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr4, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_u8_arr4W_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr4, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData4_u8_arr4W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr4, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData4_u8_arr5A_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_dump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr5, unsigned int, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData4_u8_arr5A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefA_fdump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr5, unsigned int, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData4_u8_arr5W_dump(Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_dump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr5, unsigned int, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData4_u8_arr5W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, unsigned int cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrrefW_fdump(ArrayMemberData4, Dz1Asn1UTF8Str*, u8_arr5, unsigned int, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

ArrayMemberData4 *ArrayMemberData4_new(ArrayMemberData4Present present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberData4 *ret = (ArrayMemberData4 *)Dz1Calloc(sizeof(ArrayMemberData4), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ArrayMemberData4_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ArrayMemberData4Present_int_arr1:
			if (ptr != NULL && (ret->x.int_arr1 = ArrayMemberData4_int_arr1_clone(ptr, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_int_arr2:
			if (ptr != NULL) ret->x.int_arr2 = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_int_arr3:
			if (ptr != NULL && (ret->x.int_arr3 = ArrayMemberData4_int_arr3_clone(ptr, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_int_arr4:
			if (ptr != NULL) ret->x.int_arr4 = (u32_t **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_int_arr5:
			if (ptr != NULL && (ret->x.int_arr5 = ArrayMemberData4_int_arr5_clone(ptr, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_int_arr6:
			if (ptr != NULL) ret->x.int_arr6 = (u32_t **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_data_arr1:
			if (ptr != NULL && (ret->x.data_arr1 = ArrayMemberData4_data_arr1_clone(ptr, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_data_arr2:
			if (ptr != NULL && (ret->x.data_arr2 = ArrayMemberData4_data_arr2_clone(ptr, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_data_arr3:
			if (ptr != NULL && (ret->x.data_arr3 = ArrayMemberData4_data_arr3_clone(ptr, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_data_arr4:
			if (ptr != NULL) ret->x.data_arr4 = (TestDataType **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_data_arr5:
			if (ptr != NULL) ret->x.data_arr5 = (TestDataType **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_u8_arr1:
			if (ptr != NULL && (ret->x.u8_arr1 = ArrayMemberData4_u8_arr1_clone(ptr, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_u8_arr2:
			if (ptr != NULL && (ret->x.u8_arr2 = ArrayMemberData4_u8_arr2_clone(ptr, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_u8_arr3:
			if (ptr != NULL && (ret->x.u8_arr3 = ArrayMemberData4_u8_arr3_clone(ptr, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_u8_arr4:
			if (ptr != NULL) ret->x.u8_arr4 = (Dz1Asn1UTF8Str **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_u8_arr5:
			if (ptr != NULL) ret->x.u8_arr5 = (Dz1Asn1UTF8Str **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData4_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t ArrayMemberData4_copy(ArrayMemberData4 *ret, ArrayMemberData4 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case ArrayMemberData4Present_int_arr1:
			if (src->x.int_arr1 != NULL && (ret->x.int_arr1 = ArrayMemberData4_int_arr1_clone(src->x.int_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_int_arr2:
			ret->x.int_arr2 = src->x.int_arr2;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_int_arr3:
			if (src->x.int_arr3 != NULL && (ret->x.int_arr3 = ArrayMemberData4_int_arr3_clone(src->x.int_arr3, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_int_arr4:
			ret->x.int_arr4 = src->x.int_arr4;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_int_arr5:
			if (src->x.int_arr5 != NULL && (ret->x.int_arr5 = ArrayMemberData4_int_arr5_clone(src->x.int_arr5, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_int_arr6:
			ret->x.int_arr6 = src->x.int_arr6;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_data_arr1:
			if (src->x.data_arr1 != NULL && (ret->x.data_arr1 = ArrayMemberData4_data_arr1_clone(src->x.data_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_data_arr2:
			if (src->x.data_arr2 != NULL && (ret->x.data_arr2 = ArrayMemberData4_data_arr2_clone(src->x.data_arr2, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_data_arr3:
			if (src->x.data_arr3 != NULL && (ret->x.data_arr3 = ArrayMemberData4_data_arr3_clone(src->x.data_arr3, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_data_arr4:
			ret->x.data_arr4 = src->x.data_arr4;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_data_arr5:
			ret->x.data_arr5 = src->x.data_arr5;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_u8_arr1:
			if (src->x.u8_arr1 != NULL && (ret->x.u8_arr1 = ArrayMemberData4_u8_arr1_clone(src->x.u8_arr1, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_u8_arr2:
			if (src->x.u8_arr2 != NULL && (ret->x.u8_arr2 = ArrayMemberData4_u8_arr2_clone(src->x.u8_arr2, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_u8_arr3:
			if (src->x.u8_arr3 != NULL && (ret->x.u8_arr3 = ArrayMemberData4_u8_arr3_clone(src->x.u8_arr3, 16, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData4Present_u8_arr4:
			ret->x.u8_arr4 = src->x.u8_arr4;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData4Present_u8_arr5:
			ret->x.u8_arr5 = src->x.u8_arr5;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ArrayMemberData4 *ArrayMemberData4_clone(ArrayMemberData4 *src, Dz1Error *err)
{
	ArrayMemberData4 *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (ArrayMemberData4 *)Dz1Calloc(sizeof(ArrayMemberData4), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ArrayMemberData4_delAndSetNull, (void *)&ret);
		if (ArrayMemberData4_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData4_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ArrayMemberData4_purge(ArrayMemberData4 *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ArrayMemberData4Present_int_arr1:
		ArrayMemberData4_int_arr1_del(p->x.int_arr1, 16);
		break;
	case ArrayMemberData4Present_int_arr2:
		break;
	case ArrayMemberData4Present_int_arr3:
		ArrayMemberData4_int_arr3_del(p->x.int_arr3, 16);
		break;
	case ArrayMemberData4Present_int_arr4:
		break;
	case ArrayMemberData4Present_int_arr5:
		ArrayMemberData4_int_arr5_del(p->x.int_arr5, 16);
		break;
	case ArrayMemberData4Present_int_arr6:
		break;
	case ArrayMemberData4Present_data_arr1:
		ArrayMemberData4_data_arr1_del(p->x.data_arr1, 16);
		break;
	case ArrayMemberData4Present_data_arr2:
		ArrayMemberData4_data_arr2_del(p->x.data_arr2, 16);
		break;
	case ArrayMemberData4Present_data_arr3:
		ArrayMemberData4_data_arr3_del(p->x.data_arr3, 16);
		break;
	case ArrayMemberData4Present_data_arr4:
		break;
	case ArrayMemberData4Present_data_arr5:
		break;
	case ArrayMemberData4Present_u8_arr1:
		ArrayMemberData4_u8_arr1_del(p->x.u8_arr1, 16);
		break;
	case ArrayMemberData4Present_u8_arr2:
		ArrayMemberData4_u8_arr2_del(p->x.u8_arr2, 16);
		break;
	case ArrayMemberData4Present_u8_arr3:
		ArrayMemberData4_u8_arr3_del(p->x.u8_arr3, 16);
		break;
	case ArrayMemberData4Present_u8_arr4:
		break;
	case ArrayMemberData4Present_u8_arr5:
		break;
	default:
		break;
	}
}

void ArrayMemberData4_del(ArrayMemberData4 *p)
{
	if (!p) return;
	ArrayMemberData4_purge(p);
	Dz1Free(p);
}

void ArrayMemberData4A_dump(ArrayMemberData4 *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else switch(p->present)
	{
	case ArrayMemberData4Present_int_arr1:
		Dz1ThreadA_printf("int_arr1 = "); ArrayMemberData4_int_arr1A_dump(p->x.int_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr2:
		Dz1ThreadA_printf("int_arr2 = "); ArrayMemberData4_int_arr2A_dump(p->x.int_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr3:
		Dz1ThreadA_printf("int_arr3 = "); ArrayMemberData4_int_arr3A_dump(p->x.int_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr4:
		Dz1ThreadA_printf("int_arr4 = "); ArrayMemberData4_int_arr4A_dump(p->x.int_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr5:
		Dz1ThreadA_printf("int_arr5 = "); ArrayMemberData4_int_arr5A_dump(p->x.int_arr5, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr6:
		Dz1ThreadA_printf("int_arr6 = "); ArrayMemberData4_int_arr6A_dump(p->x.int_arr6, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr1:
		Dz1ThreadA_printf("data_arr1 = "); ArrayMemberData4_data_arr1A_dump(p->x.data_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr2:
		Dz1ThreadA_printf("data_arr2 = "); ArrayMemberData4_data_arr2A_dump(p->x.data_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr3:
		Dz1ThreadA_printf("data_arr3 = "); ArrayMemberData4_data_arr3A_dump(p->x.data_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr4:
		Dz1ThreadA_printf("data_arr4 = "); ArrayMemberData4_data_arr4A_dump(p->x.data_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr5:
		Dz1ThreadA_printf("data_arr5 = "); ArrayMemberData4_data_arr5A_dump(p->x.data_arr5, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr1:
		Dz1ThreadA_printf("u8_arr1 = "); ArrayMemberData4_u8_arr1A_dump(p->x.u8_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr2:
		Dz1ThreadA_printf("u8_arr2 = "); ArrayMemberData4_u8_arr2A_dump(p->x.u8_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr3:
		Dz1ThreadA_printf("u8_arr3 = "); ArrayMemberData4_u8_arr3A_dump(p->x.u8_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr4:
		Dz1ThreadA_printf("u8_arr4 = "); ArrayMemberData4_u8_arr4A_dump(p->x.u8_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr5:
		Dz1ThreadA_printf("u8_arr5 = "); ArrayMemberData4_u8_arr5A_dump(p->x.u8_arr5, 16, tab);
		break;
	default:
		Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
		break;
	}
}
void ArrayMemberData4A_fdump(FILE *fp, ArrayMemberData4 *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else switch(p->present)
	{
	case ArrayMemberData4Present_int_arr1:
		Dz1ThreadA_fprintf(fp, "int_arr1 = "); ArrayMemberData4_int_arr1A_fdump(fp, p->x.int_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr2:
		Dz1ThreadA_fprintf(fp, "int_arr2 = "); ArrayMemberData4_int_arr2A_fdump(fp, p->x.int_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr3:
		Dz1ThreadA_fprintf(fp, "int_arr3 = "); ArrayMemberData4_int_arr3A_fdump(fp, p->x.int_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr4:
		Dz1ThreadA_fprintf(fp, "int_arr4 = "); ArrayMemberData4_int_arr4A_fdump(fp, p->x.int_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr5:
		Dz1ThreadA_fprintf(fp, "int_arr5 = "); ArrayMemberData4_int_arr5A_fdump(fp, p->x.int_arr5, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr6:
		Dz1ThreadA_fprintf(fp, "int_arr6 = "); ArrayMemberData4_int_arr6A_fdump(fp, p->x.int_arr6, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr1:
		Dz1ThreadA_fprintf(fp, "data_arr1 = "); ArrayMemberData4_data_arr1A_fdump(fp, p->x.data_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr2:
		Dz1ThreadA_fprintf(fp, "data_arr2 = "); ArrayMemberData4_data_arr2A_fdump(fp, p->x.data_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr3:
		Dz1ThreadA_fprintf(fp, "data_arr3 = "); ArrayMemberData4_data_arr3A_fdump(fp, p->x.data_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr4:
		Dz1ThreadA_fprintf(fp, "data_arr4 = "); ArrayMemberData4_data_arr4A_fdump(fp, p->x.data_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr5:
		Dz1ThreadA_fprintf(fp, "data_arr5 = "); ArrayMemberData4_data_arr5A_fdump(fp, p->x.data_arr5, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr1:
		Dz1ThreadA_fprintf(fp, "u8_arr1 = "); ArrayMemberData4_u8_arr1A_fdump(fp, p->x.u8_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr2:
		Dz1ThreadA_fprintf(fp, "u8_arr2 = "); ArrayMemberData4_u8_arr2A_fdump(fp, p->x.u8_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr3:
		Dz1ThreadA_fprintf(fp, "u8_arr3 = "); ArrayMemberData4_u8_arr3A_fdump(fp, p->x.u8_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr4:
		Dz1ThreadA_fprintf(fp, "u8_arr4 = "); ArrayMemberData4_u8_arr4A_fdump(fp, p->x.u8_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr5:
		Dz1ThreadA_fprintf(fp, "u8_arr5 = "); ArrayMemberData4_u8_arr5A_fdump(fp, p->x.u8_arr5, 16, tab);
		break;
	default:
		Dz1ThreadA_ftprintf(fp, tab, "??? = %d\n", p->present);
		break;
	}
}
#ifndef UNIX_SYSTEM
void ArrayMemberData4W_dump(ArrayMemberData4 *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case ArrayMemberData4Present_int_arr1:
		Dz1ThreadW_printf(L"int_arr1 = "); ArrayMemberData4_int_arr1W_dump(p->x.int_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr2:
		Dz1ThreadW_printf(L"int_arr2 = "); ArrayMemberData4_int_arr2W_dump(p->x.int_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr3:
		Dz1ThreadW_printf(L"int_arr3 = "); ArrayMemberData4_int_arr3W_dump(p->x.int_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr4:
		Dz1ThreadW_printf(L"int_arr4 = "); ArrayMemberData4_int_arr4W_dump(p->x.int_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr5:
		Dz1ThreadW_printf(L"int_arr5 = "); ArrayMemberData4_int_arr5W_dump(p->x.int_arr5, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr6:
		Dz1ThreadW_printf(L"int_arr6 = "); ArrayMemberData4_int_arr6W_dump(p->x.int_arr6, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr1:
		Dz1ThreadW_printf(L"data_arr1 = "); ArrayMemberData4_data_arr1W_dump(p->x.data_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr2:
		Dz1ThreadW_printf(L"data_arr2 = "); ArrayMemberData4_data_arr2W_dump(p->x.data_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr3:
		Dz1ThreadW_printf(L"data_arr3 = "); ArrayMemberData4_data_arr3W_dump(p->x.data_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr4:
		Dz1ThreadW_printf(L"data_arr4 = "); ArrayMemberData4_data_arr4W_dump(p->x.data_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr5:
		Dz1ThreadW_printf(L"data_arr5 = "); ArrayMemberData4_data_arr5W_dump(p->x.data_arr5, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr1:
		Dz1ThreadW_printf(L"u8_arr1 = "); ArrayMemberData4_u8_arr1W_dump(p->x.u8_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr2:
		Dz1ThreadW_printf(L"u8_arr2 = "); ArrayMemberData4_u8_arr2W_dump(p->x.u8_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr3:
		Dz1ThreadW_printf(L"u8_arr3 = "); ArrayMemberData4_u8_arr3W_dump(p->x.u8_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr4:
		Dz1ThreadW_printf(L"u8_arr4 = "); ArrayMemberData4_u8_arr4W_dump(p->x.u8_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr5:
		Dz1ThreadW_printf(L"u8_arr5 = "); ArrayMemberData4_u8_arr5W_dump(p->x.u8_arr5, 16, tab);
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}
void ArrayMemberData4W_fdump(FILE *fp, ArrayMemberData4 *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else switch(p->present)
	{
	case ArrayMemberData4Present_int_arr1:
		Dz1ThreadW_fprintf(fp, L"int_arr1 = "); ArrayMemberData4_int_arr1W_fdump(fp, p->x.int_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr2:
		Dz1ThreadW_fprintf(fp, L"int_arr2 = "); ArrayMemberData4_int_arr2W_fdump(fp, p->x.int_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr3:
		Dz1ThreadW_fprintf(fp, L"int_arr3 = "); ArrayMemberData4_int_arr3W_fdump(fp, p->x.int_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr4:
		Dz1ThreadW_fprintf(fp, L"int_arr4 = "); ArrayMemberData4_int_arr4W_fdump(fp, p->x.int_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr5:
		Dz1ThreadW_fprintf(fp, L"int_arr5 = "); ArrayMemberData4_int_arr5W_fdump(fp, p->x.int_arr5, 16, tab);
		break;
	case ArrayMemberData4Present_int_arr6:
		Dz1ThreadW_fprintf(fp, L"int_arr6 = "); ArrayMemberData4_int_arr6W_fdump(fp, p->x.int_arr6, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr1:
		Dz1ThreadW_fprintf(fp, L"data_arr1 = "); ArrayMemberData4_data_arr1W_fdump(fp, p->x.data_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr2:
		Dz1ThreadW_fprintf(fp, L"data_arr2 = "); ArrayMemberData4_data_arr2W_fdump(fp, p->x.data_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr3:
		Dz1ThreadW_fprintf(fp, L"data_arr3 = "); ArrayMemberData4_data_arr3W_fdump(fp, p->x.data_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr4:
		Dz1ThreadW_fprintf(fp, L"data_arr4 = "); ArrayMemberData4_data_arr4W_fdump(fp, p->x.data_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_data_arr5:
		Dz1ThreadW_fprintf(fp, L"data_arr5 = "); ArrayMemberData4_data_arr5W_fdump(fp, p->x.data_arr5, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr1:
		Dz1ThreadW_fprintf(fp, L"u8_arr1 = "); ArrayMemberData4_u8_arr1W_fdump(fp, p->x.u8_arr1, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr2:
		Dz1ThreadW_fprintf(fp, L"u8_arr2 = "); ArrayMemberData4_u8_arr2W_fdump(fp, p->x.u8_arr2, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr3:
		Dz1ThreadW_fprintf(fp, L"u8_arr3 = "); ArrayMemberData4_u8_arr3W_fdump(fp, p->x.u8_arr3, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr4:
		Dz1ThreadW_fprintf(fp, L"u8_arr4 = "); ArrayMemberData4_u8_arr4W_fdump(fp, p->x.u8_arr4, 16, tab);
		break;
	case ArrayMemberData4Present_u8_arr5:
		Dz1ThreadW_fprintf(fp, L"u8_arr5 = "); ArrayMemberData4_u8_arr5W_fdump(fp, p->x.u8_arr5, 16, tab);
		break;
	default:
		Dz1ThreadW_ftprintf(fp, tab, L"??? = %d\n", p->present);
		break;
	}
}
#endif // UNIX_SYSTEM

// ArrayMemberData4
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData5Present
static struct ArrayMemberData5PresentMapA
{
	str_t str;
	ArrayMemberData5Present v;
} ArrayMemberData5PresentMapA[] =
{
	{ (char *)"int_arr1", ArrayMemberData5Present_int_arr1 },
	{ (char *)"int_arr2", ArrayMemberData5Present_int_arr2 },
	{ (char *)"int_arr3", ArrayMemberData5Present_int_arr3 },
	{ (char *)"int_arr4", ArrayMemberData5Present_int_arr4 },
	{ (char *)"int_arr5", ArrayMemberData5Present_int_arr5 },
	{ (char *)"data_arr1", ArrayMemberData5Present_data_arr1 },
	{ (char *)"data_arr2", ArrayMemberData5Present_data_arr2 },
	{ (char *)"data_arr3", ArrayMemberData5Present_data_arr3 },
	{ (char *)"data_arr4", ArrayMemberData5Present_data_arr4 },
	{ (char *)"data_arr5", ArrayMemberData5Present_data_arr5 },
	{ (char *)"u8_arr1", ArrayMemberData5Present_u8_arr1 },
	{ (char *)"u8_arr2", ArrayMemberData5Present_u8_arr2 },
	{ (char *)"u8_arr3", ArrayMemberData5Present_u8_arr3 },
	{ (char *)"u8_arr4", ArrayMemberData5Present_u8_arr4 },
	{ (char *)"u8_arr5", ArrayMemberData5Present_u8_arr5 },
	{ NULL, ArrayMemberData5Present_max }
};

str_t ArrayMemberData5PresentStrA(ArrayMemberData5Present v)
{
	struct ArrayMemberData5PresentMapA *i = NULL;
	for (i = ArrayMemberData5PresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ArrayMemberData5Present ArrayMemberData5PresentFromStrA(str_t str)
{
	struct ArrayMemberData5PresentMapA *i = NULL;
	for (i = ArrayMemberData5PresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ArrayMemberData5Present_max;
}
#ifndef UNIX_SYSTEM
static struct ArrayMemberData5PresentMapW
{
	wstr_t str;
	ArrayMemberData5Present v;
} ArrayMemberData5PresentMapW[] =
{
	{ (wchar_t *)L"int_arr1", ArrayMemberData5Present_int_arr1 },
	{ (wchar_t *)L"int_arr2", ArrayMemberData5Present_int_arr2 },
	{ (wchar_t *)L"int_arr3", ArrayMemberData5Present_int_arr3 },
	{ (wchar_t *)L"int_arr4", ArrayMemberData5Present_int_arr4 },
	{ (wchar_t *)L"int_arr5", ArrayMemberData5Present_int_arr5 },
	{ (wchar_t *)L"data_arr1", ArrayMemberData5Present_data_arr1 },
	{ (wchar_t *)L"data_arr2", ArrayMemberData5Present_data_arr2 },
	{ (wchar_t *)L"data_arr3", ArrayMemberData5Present_data_arr3 },
	{ (wchar_t *)L"data_arr4", ArrayMemberData5Present_data_arr4 },
	{ (wchar_t *)L"data_arr5", ArrayMemberData5Present_data_arr5 },
	{ (wchar_t *)L"u8_arr1", ArrayMemberData5Present_u8_arr1 },
	{ (wchar_t *)L"u8_arr2", ArrayMemberData5Present_u8_arr2 },
	{ (wchar_t *)L"u8_arr3", ArrayMemberData5Present_u8_arr3 },
	{ (wchar_t *)L"u8_arr4", ArrayMemberData5Present_u8_arr4 },
	{ (wchar_t *)L"u8_arr5", ArrayMemberData5Present_u8_arr5 },
	{ NULL, ArrayMemberData5Present_max }
};

wstr_t ArrayMemberData5PresentStrW(ArrayMemberData5Present v)
{
	struct ArrayMemberData5PresentMapW *i = NULL;
	for (i = ArrayMemberData5PresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ArrayMemberData5Present ArrayMemberData5PresentFromStrW(wstr_t str)
{
	struct ArrayMemberData5PresentMapW *i = NULL;
	for (i = ArrayMemberData5PresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ArrayMemberData5Present_max;
}
#endif // UNIX_SYSTEM

ArrayMemberData5Present *ArrayMemberData5Present_new(ArrayMemberData5Present *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberData5Present *__internal_ret = (ArrayMemberData5Present *)Dz1Calloc(sizeof(ArrayMemberData5Present), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ArrayMemberData5PresentA_dump(ArrayMemberData5Present *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", ArrayMemberData5PresentStrA(*v));
}
void ArrayMemberData5PresentA_fdump(FILE *fp, ArrayMemberData5Present *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", ArrayMemberData5PresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void ArrayMemberData5PresentW_dump(ArrayMemberData5Present *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", ArrayMemberData5PresentStrW(*v));
}
void ArrayMemberData5PresentW_fdump(FILE *fp, ArrayMemberData5Present *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", ArrayMemberData5PresentStrW(*v));
}
#endif // UNIX_SYSTEM
// ArrayMemberData5Present
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData5
// void ArrayMemberData5_int_arr1_del(u32_t *src);
static __inline__ Dz1StructArrayMemb_val_primitive_nocnt_del(ArrayMemberData5, u32_t, int_arr1, (*ap) == 0)
// void ArrayMemberData5_int_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_nocnt_delAndSetNull(ArrayMemberData5, u32_t, int_arr1)
// unsigned int ArrayMemberData5_int_arr1_count(u32_t *src);
static __inline__ Dz1StructArrayMemb_val_primitive_nocnt_count(ArrayMemberData5, u32_t, int_arr1, (*ap) == 0)
// u32_t *ArrayMemberData5_int_arr1_clone(u32_t *src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_nocnt_clone(ArrayMemberData5, u32_t, int_arr1, (*ap) == 0)
// void ArrayMemberData5_int_arr1A_dump(u32_t *p, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_nocntA_dump(ArrayMemberData5, u32_t, int_arr1, (*ap) == 0, " = ", Dz1u32A_dump)
// void ArrayMemberData5_int_arr1A_fdump(FILE *fp, u32_t *p, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_nocntA_fdump(ArrayMemberData5, u32_t, int_arr1, (*ap) == 0, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_int_arr1W_dump(u32_t *p, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_nocntW_dump(ArrayMemberData5, u32_t, int_arr1, (*ap) == 0, " = ", Dz1u32W_dump)
// void ArrayMemberData5_int_arr1W_fdump(FILE *fp, u32_t *p, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_nocntW_fdump(ArrayMemberData5, u32_t, int_arr1, (*ap) == 0, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_int_arr2_del(u32_t **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_del(ArrayMemberData5, u32_t*, int_arr2, (*ap) == NULL, Dz1u32_del)
// void ArrayMemberData5_int_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_delAndSetNull(ArrayMemberData5, u32_t*, int_arr2)
// unsigned int ArrayMemberData5_int_arr2_count(u32_t **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_count(ArrayMemberData5, u32_t*, int_arr2, (*ap) == NULL)
// u32_t **ArrayMemberData5_int_arr2_clone(u32_t **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_clone(ArrayMemberData5, u32_t*, int_arr2, (*ap) == NULL, Dz1u32_clone)
// void ArrayMemberData5_int_arr2A_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData5, u32_t*, int_arr2, (*ap) == NULL, " = ", Dz1u32A_dump)
// void ArrayMemberData5_int_arr2A_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData5, u32_t*, int_arr2, (*ap) == NULL, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_int_arr2W_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData5, u32_t*, int_arr2, (*ap) == NULL, " = ", Dz1u32W_dump)
// void ArrayMemberData5_int_arr2W_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData5, u32_t*, int_arr2, (*ap) == NULL, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_int_arr3_del(u32_t **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_del(ArrayMemberData5, u32_t*, int_arr3, (*ap) == NULL)
// void ArrayMemberData5_int_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_delAndSetNull(ArrayMemberData5, u32_t*, int_arr3)
// unsigned int ArrayMemberData5_int_arr3_count(u32_t **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_count(ArrayMemberData5, u32_t*, int_arr3, (*ap) == NULL)
// u32_t **ArrayMemberData5_int_arr3_clone(u32_t **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_clone(ArrayMemberData5, u32_t*, int_arr3, (*ap) == NULL)
// void ArrayMemberData5_int_arr3A_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData5, u32_t*, int_arr3, (*ap) == NULL, " = ", Dz1u32A_dump)
// void ArrayMemberData5_int_arr3A_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData5, u32_t*, int_arr3, (*ap) == NULL, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_int_arr3W_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData5, u32_t*, int_arr3, (*ap) == NULL, " = ", Dz1u32W_dump)
// void ArrayMemberData5_int_arr3W_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData5, u32_t*, int_arr3, (*ap) == NULL, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_int_arr4A_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData5, u32_t*, int_arr4, (*ap) == NULL, " = ", Dz1u32A_dump)
// void ArrayMemberData5_int_arr4A_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData5, u32_t*, int_arr4, (*ap) == NULL, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_int_arr4W_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData5, u32_t*, int_arr4, (*ap) == NULL, " = ", Dz1u32W_dump)
// void ArrayMemberData5_int_arr4W_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData5, u32_t*, int_arr4, (*ap) == NULL, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_int_arr5A_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData5, u32_t*, int_arr5, (*ap) == NULL, " = ", Dz1u32A_dump)
// void ArrayMemberData5_int_arr5A_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData5, u32_t*, int_arr5, (*ap) == NULL, " = ", Dz1u32A_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_int_arr5W_dump(u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData5, u32_t*, int_arr5, (*ap) == NULL, " = ", Dz1u32W_dump)
// void ArrayMemberData5_int_arr5W_fdump(FILE *fp, u32_t **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData5, u32_t*, int_arr5, (*ap) == NULL, " = ", Dz1u32W_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_data_arr1_del(TestDataType *src);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_del(ArrayMemberData5, TestDataType, data_arr1, ap->id == 0, TestDataType_purge)
// void ArrayMemberData5_data_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_delAndSetNull(ArrayMemberData5, TestDataType, data_arr1)
// unsigned int ArrayMemberData5_data_arr1_count(TestDataType *src);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_count(ArrayMemberData5, TestDataType, data_arr1, ap->id == 0)
// TestDataType *ArrayMemberData5_data_arr1_clone(TestDataType *src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_clone(ArrayMemberData5, TestDataType, data_arr1, ap->id == 0, TestDataType_copy)
// void ArrayMemberData5_data_arr1A_dump(TestDataType *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntA_dump(ArrayMemberData5, TestDataType, data_arr1, ap->id == 0, " = ", TestDataTypeA_dump)
// void ArrayMemberData5_data_arr1A_fdump(FILE *fp, TestDataType *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntA_fdump(ArrayMemberData5, TestDataType, data_arr1, ap->id == 0, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_data_arr1W_dump(TestDataType *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntW_dump(ArrayMemberData5, TestDataType, data_arr1, ap->id == 0, " = ", TestDataTypeW_dump)
// void ArrayMemberData5_data_arr1W_fdump(FILE *fp, TestDataType *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntW_fdump(ArrayMemberData5, TestDataType, data_arr1, ap->id == 0, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_data_arr2_del(TestDataType **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_del(ArrayMemberData5, TestDataType*, data_arr2, (*ap) == NULL, TestDataType_del)
// void ArrayMemberData5_data_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_delAndSetNull(ArrayMemberData5, TestDataType*, data_arr2)
// unsigned int ArrayMemberData5_data_arr2_count(TestDataType **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_count(ArrayMemberData5, TestDataType*, data_arr2, (*ap) == NULL)
// TestDataType **ArrayMemberData5_data_arr2_clone(TestDataType **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_clone(ArrayMemberData5, TestDataType*, data_arr2, (*ap) == NULL, TestDataType_clone)
// void ArrayMemberData5_data_arr2A_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData5, TestDataType*, data_arr2, (*ap) == NULL, " = ", TestDataTypeA_dump)
// void ArrayMemberData5_data_arr2A_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData5, TestDataType*, data_arr2, (*ap) == NULL, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_data_arr2W_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData5, TestDataType*, data_arr2, (*ap) == NULL, " = ", TestDataTypeW_dump)
// void ArrayMemberData5_data_arr2W_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData5, TestDataType*, data_arr2, (*ap) == NULL, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_data_arr3_del(TestDataType **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_del(ArrayMemberData5, TestDataType*, data_arr3, (*ap) == NULL)
// void ArrayMemberData5_data_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_delAndSetNull(ArrayMemberData5, TestDataType*, data_arr3)
// unsigned int ArrayMemberData5_data_arr3_count(TestDataType **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_count(ArrayMemberData5, TestDataType*, data_arr3, (*ap) == NULL)
// TestDataType **ArrayMemberData5_data_arr3_clone(TestDataType **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_clone(ArrayMemberData5, TestDataType*, data_arr3, (*ap) == NULL)
// void ArrayMemberData5_data_arr3A_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData5, TestDataType*, data_arr3, (*ap) == NULL, " = ", TestDataTypeA_dump)
// void ArrayMemberData5_data_arr3A_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData5, TestDataType*, data_arr3, (*ap) == NULL, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_data_arr3W_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData5, TestDataType*, data_arr3, (*ap) == NULL, " = ", TestDataTypeW_dump)
// void ArrayMemberData5_data_arr3W_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData5, TestDataType*, data_arr3, (*ap) == NULL, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_data_arr4A_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData5, TestDataType*, data_arr4, (*ap) == NULL, " = ", TestDataTypeA_dump)
// void ArrayMemberData5_data_arr4A_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData5, TestDataType*, data_arr4, (*ap) == NULL, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_data_arr4W_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData5, TestDataType*, data_arr4, (*ap) == NULL, " = ", TestDataTypeW_dump)
// void ArrayMemberData5_data_arr4W_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData5, TestDataType*, data_arr4, (*ap) == NULL, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_data_arr5A_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData5, TestDataType*, data_arr5, (*ap) == NULL, " = ", TestDataTypeA_dump)
// void ArrayMemberData5_data_arr5A_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData5, TestDataType*, data_arr5, (*ap) == NULL, " = ", TestDataTypeA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_data_arr5W_dump(TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData5, TestDataType*, data_arr5, (*ap) == NULL, " = ", TestDataTypeW_dump)
// void ArrayMemberData5_data_arr5W_fdump(FILE *fp, TestDataType **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData5, TestDataType*, data_arr5, (*ap) == NULL, " = ", TestDataTypeW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_u8_arr1_del(Dz1Asn1UTF8Str *src);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_del(ArrayMemberData5, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, Dz1Asn1UTF8Str_purge)
// void ArrayMemberData5_u8_arr1_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_delAndSetNull(ArrayMemberData5, Dz1Asn1UTF8Str, u8_arr1)
// unsigned int ArrayMemberData5_u8_arr1_count(Dz1Asn1UTF8Str *src);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_count(ArrayMemberData5, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0)
// Dz1Asn1UTF8Str *ArrayMemberData5_u8_arr1_clone(Dz1Asn1UTF8Str *src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_nocnt_clone(ArrayMemberData5, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, Dz1Asn1UTF8Str_copy)
// void ArrayMemberData5_u8_arr1A_dump(Dz1Asn1UTF8Str *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntA_dump(ArrayMemberData5, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData5_u8_arr1A_fdump(FILE *fp, Dz1Asn1UTF8Str *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntA_fdump(ArrayMemberData5, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_u8_arr1W_dump(Dz1Asn1UTF8Str *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntW_dump(ArrayMemberData5, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData5_u8_arr1W_fdump(FILE *fp, Dz1Asn1UTF8Str *p, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_nocntW_fdump(ArrayMemberData5, Dz1Asn1UTF8Str, u8_arr1, ap->data == NULL && ap->size == 0, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_u8_arr2_del(Dz1Asn1UTF8Str **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_del(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, Dz1Asn1UTF8Str_del)
// void ArrayMemberData5_u8_arr2_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_delAndSetNull(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr2)
// unsigned int ArrayMemberData5_u8_arr2_count(Dz1Asn1UTF8Str **src);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_count(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL)
// Dz1Asn1UTF8Str **ArrayMemberData5_u8_arr2_clone(Dz1Asn1UTF8Str **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_nocnt_clone(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, Dz1Asn1UTF8Str_clone)
// void ArrayMemberData5_u8_arr2A_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData5_u8_arr2A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_u8_arr2W_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData5_u8_arr2W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr2, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_u8_arr3_del(Dz1Asn1UTF8Str **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_del(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL)
// void ArrayMemberData5_u8_arr3_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_delAndSetNull(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr3)
// unsigned int ArrayMemberData5_u8_arr3_count(Dz1Asn1UTF8Str **src);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_count(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL)
// Dz1Asn1UTF8Str **ArrayMemberData5_u8_arr3_clone(Dz1Asn1UTF8Str **src, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptrref_nocnt_clone(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL)
// void ArrayMemberData5_u8_arr3A_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData5_u8_arr3A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_u8_arr3W_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData5_u8_arr3W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr3, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_u8_arr4A_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_dump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr4, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData5_u8_arr4A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntA_fdump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr4, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_u8_arr4W_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_dump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr4, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData5_u8_arr4W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptr_nocntW_fdump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr4, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

// void ArrayMemberData5_u8_arr5A_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_dump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr5, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_dump)
// void ArrayMemberData5_u8_arr5A_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntA_fdump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr5, (*ap) == NULL, " = ", Dz1Asn1UTF8StrA_fdump)
#ifndef UNIX_SYSTEM
// void ArrayMemberData5_u8_arr5W_dump(Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_dump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr5, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_dump)
// void ArrayMemberData5_u8_arr5W_fdump(FILE *fp, Dz1Asn1UTF8Str **p, int tab);
static __inline__ Dz1StructArrayMemb_ptrref_nocntW_fdump(ArrayMemberData5, Dz1Asn1UTF8Str*, u8_arr5, (*ap) == NULL, " = ", Dz1Asn1UTF8StrW_fdump)
#endif // UNIX_SYSTEM

ArrayMemberData5 *ArrayMemberData5_new(ArrayMemberData5Present present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberData5 *ret = (ArrayMemberData5 *)Dz1Calloc(sizeof(ArrayMemberData5), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ArrayMemberData5_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ArrayMemberData5Present_int_arr1:
			if (ptr != NULL && (ret->x.int_arr1 = ArrayMemberData5_int_arr1_clone(ptr, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_int_arr2:
			if (ptr != NULL && (ret->x.int_arr2 = ArrayMemberData5_int_arr2_clone(ptr, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_int_arr3:
			if (ptr != NULL && (ret->x.int_arr3 = ArrayMemberData5_int_arr3_clone(ptr, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_int_arr4:
			if (ptr != NULL) ret->x.int_arr4 = (u32_t **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_int_arr5:
			if (ptr != NULL) ret->x.int_arr5 = (u32_t **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_data_arr1:
			if (ptr != NULL && (ret->x.data_arr1 = ArrayMemberData5_data_arr1_clone(ptr, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_data_arr2:
			if (ptr != NULL && (ret->x.data_arr2 = ArrayMemberData5_data_arr2_clone(ptr, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_data_arr3:
			if (ptr != NULL && (ret->x.data_arr3 = ArrayMemberData5_data_arr3_clone(ptr, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_data_arr4:
			if (ptr != NULL) ret->x.data_arr4 = (TestDataType **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_data_arr5:
			if (ptr != NULL) ret->x.data_arr5 = (TestDataType **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_u8_arr1:
			if (ptr != NULL && (ret->x.u8_arr1 = ArrayMemberData5_u8_arr1_clone(ptr, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_u8_arr2:
			if (ptr != NULL && (ret->x.u8_arr2 = ArrayMemberData5_u8_arr2_clone(ptr, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_u8_arr3:
			if (ptr != NULL && (ret->x.u8_arr3 = ArrayMemberData5_u8_arr3_clone(ptr, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_u8_arr4:
			if (ptr != NULL) ret->x.u8_arr4 = (Dz1Asn1UTF8Str **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_u8_arr5:
			if (ptr != NULL) ret->x.u8_arr5 = (Dz1Asn1UTF8Str **)ptr;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData5_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t ArrayMemberData5_copy(ArrayMemberData5 *ret, ArrayMemberData5 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case ArrayMemberData5Present_int_arr1:
			if (src->x.int_arr1 != NULL && (ret->x.int_arr1 = ArrayMemberData5_int_arr1_clone(src->x.int_arr1, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_int_arr2:
			if (src->x.int_arr2 != NULL && (ret->x.int_arr2 = ArrayMemberData5_int_arr2_clone(src->x.int_arr2, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_int_arr3:
			if (src->x.int_arr3 != NULL && (ret->x.int_arr3 = ArrayMemberData5_int_arr3_clone(src->x.int_arr3, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_int_arr4:
			ret->x.int_arr4 = src->x.int_arr4;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_int_arr5:
			ret->x.int_arr5 = src->x.int_arr5;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_data_arr1:
			if (src->x.data_arr1 != NULL && (ret->x.data_arr1 = ArrayMemberData5_data_arr1_clone(src->x.data_arr1, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_data_arr2:
			if (src->x.data_arr2 != NULL && (ret->x.data_arr2 = ArrayMemberData5_data_arr2_clone(src->x.data_arr2, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_data_arr3:
			if (src->x.data_arr3 != NULL && (ret->x.data_arr3 = ArrayMemberData5_data_arr3_clone(src->x.data_arr3, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_data_arr4:
			ret->x.data_arr4 = src->x.data_arr4;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_data_arr5:
			ret->x.data_arr5 = src->x.data_arr5;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_u8_arr1:
			if (src->x.u8_arr1 != NULL && (ret->x.u8_arr1 = ArrayMemberData5_u8_arr1_clone(src->x.u8_arr1, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_u8_arr2:
			if (src->x.u8_arr2 != NULL && (ret->x.u8_arr2 = ArrayMemberData5_u8_arr2_clone(src->x.u8_arr2, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_u8_arr3:
			if (src->x.u8_arr3 != NULL && (ret->x.u8_arr3 = ArrayMemberData5_u8_arr3_clone(src->x.u8_arr3, errp)) == NULL) { ERR_OUT(errp); }
			else {ERR_CLEAR(errp); }
			break;
		case ArrayMemberData5Present_u8_arr4:
			ret->x.u8_arr4 = src->x.u8_arr4;
			ERR_CLEAR(errp);
			break;
		case ArrayMemberData5Present_u8_arr5:
			ret->x.u8_arr5 = src->x.u8_arr5;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ArrayMemberData5 *ArrayMemberData5_clone(ArrayMemberData5 *src, Dz1Error *err)
{
	ArrayMemberData5 *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (ArrayMemberData5 *)Dz1Calloc(sizeof(ArrayMemberData5), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ArrayMemberData5_delAndSetNull, (void *)&ret);
		if (ArrayMemberData5_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberData5_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ArrayMemberData5_purge(ArrayMemberData5 *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ArrayMemberData5Present_int_arr1:
		ArrayMemberData5_int_arr1_del(p->x.int_arr1);
		break;
	case ArrayMemberData5Present_int_arr2:
		ArrayMemberData5_int_arr2_del(p->x.int_arr2);
		break;
	case ArrayMemberData5Present_int_arr3:
		ArrayMemberData5_int_arr3_del(p->x.int_arr3);
		break;
	case ArrayMemberData5Present_int_arr4:
		break;
	case ArrayMemberData5Present_int_arr5:
		break;
	case ArrayMemberData5Present_data_arr1:
		ArrayMemberData5_data_arr1_del(p->x.data_arr1);
		break;
	case ArrayMemberData5Present_data_arr2:
		ArrayMemberData5_data_arr2_del(p->x.data_arr2);
		break;
	case ArrayMemberData5Present_data_arr3:
		ArrayMemberData5_data_arr3_del(p->x.data_arr3);
		break;
	case ArrayMemberData5Present_data_arr4:
		break;
	case ArrayMemberData5Present_data_arr5:
		break;
	case ArrayMemberData5Present_u8_arr1:
		ArrayMemberData5_u8_arr1_del(p->x.u8_arr1);
		break;
	case ArrayMemberData5Present_u8_arr2:
		ArrayMemberData5_u8_arr2_del(p->x.u8_arr2);
		break;
	case ArrayMemberData5Present_u8_arr3:
		ArrayMemberData5_u8_arr3_del(p->x.u8_arr3);
		break;
	case ArrayMemberData5Present_u8_arr4:
		break;
	case ArrayMemberData5Present_u8_arr5:
		break;
	default:
		break;
	}
}

void ArrayMemberData5_del(ArrayMemberData5 *p)
{
	if (!p) return;
	ArrayMemberData5_purge(p);
	Dz1Free(p);
}

void ArrayMemberData5A_dump(ArrayMemberData5 *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else switch(p->present)
	{
	case ArrayMemberData5Present_int_arr1:
		Dz1ThreadA_printf("int_arr1 = "); ArrayMemberData5_int_arr1A_dump(p->x.int_arr1, tab);
		break;
	case ArrayMemberData5Present_int_arr2:
		Dz1ThreadA_printf("int_arr2 = "); ArrayMemberData5_int_arr2A_dump(p->x.int_arr2, tab);
		break;
	case ArrayMemberData5Present_int_arr3:
		Dz1ThreadA_printf("int_arr3 = "); ArrayMemberData5_int_arr3A_dump(p->x.int_arr3, tab);
		break;
	case ArrayMemberData5Present_int_arr4:
		Dz1ThreadA_printf("int_arr4 = "); ArrayMemberData5_int_arr4A_dump(p->x.int_arr4, tab);
		break;
	case ArrayMemberData5Present_int_arr5:
		Dz1ThreadA_printf("int_arr5 = "); ArrayMemberData5_int_arr5A_dump(p->x.int_arr5, tab);
		break;
	case ArrayMemberData5Present_data_arr1:
		Dz1ThreadA_printf("data_arr1 = "); ArrayMemberData5_data_arr1A_dump(p->x.data_arr1, tab);
		break;
	case ArrayMemberData5Present_data_arr2:
		Dz1ThreadA_printf("data_arr2 = "); ArrayMemberData5_data_arr2A_dump(p->x.data_arr2, tab);
		break;
	case ArrayMemberData5Present_data_arr3:
		Dz1ThreadA_printf("data_arr3 = "); ArrayMemberData5_data_arr3A_dump(p->x.data_arr3, tab);
		break;
	case ArrayMemberData5Present_data_arr4:
		Dz1ThreadA_printf("data_arr4 = "); ArrayMemberData5_data_arr4A_dump(p->x.data_arr4, tab);
		break;
	case ArrayMemberData5Present_data_arr5:
		Dz1ThreadA_printf("data_arr5 = "); ArrayMemberData5_data_arr5A_dump(p->x.data_arr5, tab);
		break;
	case ArrayMemberData5Present_u8_arr1:
		Dz1ThreadA_printf("u8_arr1 = "); ArrayMemberData5_u8_arr1A_dump(p->x.u8_arr1, tab);
		break;
	case ArrayMemberData5Present_u8_arr2:
		Dz1ThreadA_printf("u8_arr2 = "); ArrayMemberData5_u8_arr2A_dump(p->x.u8_arr2, tab);
		break;
	case ArrayMemberData5Present_u8_arr3:
		Dz1ThreadA_printf("u8_arr3 = "); ArrayMemberData5_u8_arr3A_dump(p->x.u8_arr3, tab);
		break;
	case ArrayMemberData5Present_u8_arr4:
		Dz1ThreadA_printf("u8_arr4 = "); ArrayMemberData5_u8_arr4A_dump(p->x.u8_arr4, tab);
		break;
	case ArrayMemberData5Present_u8_arr5:
		Dz1ThreadA_printf("u8_arr5 = "); ArrayMemberData5_u8_arr5A_dump(p->x.u8_arr5, tab);
		break;
	default:
		Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
		break;
	}
}
void ArrayMemberData5A_fdump(FILE *fp, ArrayMemberData5 *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else switch(p->present)
	{
	case ArrayMemberData5Present_int_arr1:
		Dz1ThreadA_fprintf(fp, "int_arr1 = "); ArrayMemberData5_int_arr1A_fdump(fp, p->x.int_arr1, tab);
		break;
	case ArrayMemberData5Present_int_arr2:
		Dz1ThreadA_fprintf(fp, "int_arr2 = "); ArrayMemberData5_int_arr2A_fdump(fp, p->x.int_arr2, tab);
		break;
	case ArrayMemberData5Present_int_arr3:
		Dz1ThreadA_fprintf(fp, "int_arr3 = "); ArrayMemberData5_int_arr3A_fdump(fp, p->x.int_arr3, tab);
		break;
	case ArrayMemberData5Present_int_arr4:
		Dz1ThreadA_fprintf(fp, "int_arr4 = "); ArrayMemberData5_int_arr4A_fdump(fp, p->x.int_arr4, tab);
		break;
	case ArrayMemberData5Present_int_arr5:
		Dz1ThreadA_fprintf(fp, "int_arr5 = "); ArrayMemberData5_int_arr5A_fdump(fp, p->x.int_arr5, tab);
		break;
	case ArrayMemberData5Present_data_arr1:
		Dz1ThreadA_fprintf(fp, "data_arr1 = "); ArrayMemberData5_data_arr1A_fdump(fp, p->x.data_arr1, tab);
		break;
	case ArrayMemberData5Present_data_arr2:
		Dz1ThreadA_fprintf(fp, "data_arr2 = "); ArrayMemberData5_data_arr2A_fdump(fp, p->x.data_arr2, tab);
		break;
	case ArrayMemberData5Present_data_arr3:
		Dz1ThreadA_fprintf(fp, "data_arr3 = "); ArrayMemberData5_data_arr3A_fdump(fp, p->x.data_arr3, tab);
		break;
	case ArrayMemberData5Present_data_arr4:
		Dz1ThreadA_fprintf(fp, "data_arr4 = "); ArrayMemberData5_data_arr4A_fdump(fp, p->x.data_arr4, tab);
		break;
	case ArrayMemberData5Present_data_arr5:
		Dz1ThreadA_fprintf(fp, "data_arr5 = "); ArrayMemberData5_data_arr5A_fdump(fp, p->x.data_arr5, tab);
		break;
	case ArrayMemberData5Present_u8_arr1:
		Dz1ThreadA_fprintf(fp, "u8_arr1 = "); ArrayMemberData5_u8_arr1A_fdump(fp, p->x.u8_arr1, tab);
		break;
	case ArrayMemberData5Present_u8_arr2:
		Dz1ThreadA_fprintf(fp, "u8_arr2 = "); ArrayMemberData5_u8_arr2A_fdump(fp, p->x.u8_arr2, tab);
		break;
	case ArrayMemberData5Present_u8_arr3:
		Dz1ThreadA_fprintf(fp, "u8_arr3 = "); ArrayMemberData5_u8_arr3A_fdump(fp, p->x.u8_arr3, tab);
		break;
	case ArrayMemberData5Present_u8_arr4:
		Dz1ThreadA_fprintf(fp, "u8_arr4 = "); ArrayMemberData5_u8_arr4A_fdump(fp, p->x.u8_arr4, tab);
		break;
	case ArrayMemberData5Present_u8_arr5:
		Dz1ThreadA_fprintf(fp, "u8_arr5 = "); ArrayMemberData5_u8_arr5A_fdump(fp, p->x.u8_arr5, tab);
		break;
	default:
		Dz1ThreadA_ftprintf(fp, tab, "??? = %d\n", p->present);
		break;
	}
}
#ifndef UNIX_SYSTEM
void ArrayMemberData5W_dump(ArrayMemberData5 *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case ArrayMemberData5Present_int_arr1:
		Dz1ThreadW_printf(L"int_arr1 = "); ArrayMemberData5_int_arr1W_dump(p->x.int_arr1, tab);
		break;
	case ArrayMemberData5Present_int_arr2:
		Dz1ThreadW_printf(L"int_arr2 = "); ArrayMemberData5_int_arr2W_dump(p->x.int_arr2, tab);
		break;
	case ArrayMemberData5Present_int_arr3:
		Dz1ThreadW_printf(L"int_arr3 = "); ArrayMemberData5_int_arr3W_dump(p->x.int_arr3, tab);
		break;
	case ArrayMemberData5Present_int_arr4:
		Dz1ThreadW_printf(L"int_arr4 = "); ArrayMemberData5_int_arr4W_dump(p->x.int_arr4, tab);
		break;
	case ArrayMemberData5Present_int_arr5:
		Dz1ThreadW_printf(L"int_arr5 = "); ArrayMemberData5_int_arr5W_dump(p->x.int_arr5, tab);
		break;
	case ArrayMemberData5Present_data_arr1:
		Dz1ThreadW_printf(L"data_arr1 = "); ArrayMemberData5_data_arr1W_dump(p->x.data_arr1, tab);
		break;
	case ArrayMemberData5Present_data_arr2:
		Dz1ThreadW_printf(L"data_arr2 = "); ArrayMemberData5_data_arr2W_dump(p->x.data_arr2, tab);
		break;
	case ArrayMemberData5Present_data_arr3:
		Dz1ThreadW_printf(L"data_arr3 = "); ArrayMemberData5_data_arr3W_dump(p->x.data_arr3, tab);
		break;
	case ArrayMemberData5Present_data_arr4:
		Dz1ThreadW_printf(L"data_arr4 = "); ArrayMemberData5_data_arr4W_dump(p->x.data_arr4, tab);
		break;
	case ArrayMemberData5Present_data_arr5:
		Dz1ThreadW_printf(L"data_arr5 = "); ArrayMemberData5_data_arr5W_dump(p->x.data_arr5, tab);
		break;
	case ArrayMemberData5Present_u8_arr1:
		Dz1ThreadW_printf(L"u8_arr1 = "); ArrayMemberData5_u8_arr1W_dump(p->x.u8_arr1, tab);
		break;
	case ArrayMemberData5Present_u8_arr2:
		Dz1ThreadW_printf(L"u8_arr2 = "); ArrayMemberData5_u8_arr2W_dump(p->x.u8_arr2, tab);
		break;
	case ArrayMemberData5Present_u8_arr3:
		Dz1ThreadW_printf(L"u8_arr3 = "); ArrayMemberData5_u8_arr3W_dump(p->x.u8_arr3, tab);
		break;
	case ArrayMemberData5Present_u8_arr4:
		Dz1ThreadW_printf(L"u8_arr4 = "); ArrayMemberData5_u8_arr4W_dump(p->x.u8_arr4, tab);
		break;
	case ArrayMemberData5Present_u8_arr5:
		Dz1ThreadW_printf(L"u8_arr5 = "); ArrayMemberData5_u8_arr5W_dump(p->x.u8_arr5, tab);
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}
void ArrayMemberData5W_fdump(FILE *fp, ArrayMemberData5 *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else switch(p->present)
	{
	case ArrayMemberData5Present_int_arr1:
		Dz1ThreadW_fprintf(fp, L"int_arr1 = "); ArrayMemberData5_int_arr1W_fdump(fp, p->x.int_arr1, tab);
		break;
	case ArrayMemberData5Present_int_arr2:
		Dz1ThreadW_fprintf(fp, L"int_arr2 = "); ArrayMemberData5_int_arr2W_fdump(fp, p->x.int_arr2, tab);
		break;
	case ArrayMemberData5Present_int_arr3:
		Dz1ThreadW_fprintf(fp, L"int_arr3 = "); ArrayMemberData5_int_arr3W_fdump(fp, p->x.int_arr3, tab);
		break;
	case ArrayMemberData5Present_int_arr4:
		Dz1ThreadW_fprintf(fp, L"int_arr4 = "); ArrayMemberData5_int_arr4W_fdump(fp, p->x.int_arr4, tab);
		break;
	case ArrayMemberData5Present_int_arr5:
		Dz1ThreadW_fprintf(fp, L"int_arr5 = "); ArrayMemberData5_int_arr5W_fdump(fp, p->x.int_arr5, tab);
		break;
	case ArrayMemberData5Present_data_arr1:
		Dz1ThreadW_fprintf(fp, L"data_arr1 = "); ArrayMemberData5_data_arr1W_fdump(fp, p->x.data_arr1, tab);
		break;
	case ArrayMemberData5Present_data_arr2:
		Dz1ThreadW_fprintf(fp, L"data_arr2 = "); ArrayMemberData5_data_arr2W_fdump(fp, p->x.data_arr2, tab);
		break;
	case ArrayMemberData5Present_data_arr3:
		Dz1ThreadW_fprintf(fp, L"data_arr3 = "); ArrayMemberData5_data_arr3W_fdump(fp, p->x.data_arr3, tab);
		break;
	case ArrayMemberData5Present_data_arr4:
		Dz1ThreadW_fprintf(fp, L"data_arr4 = "); ArrayMemberData5_data_arr4W_fdump(fp, p->x.data_arr4, tab);
		break;
	case ArrayMemberData5Present_data_arr5:
		Dz1ThreadW_fprintf(fp, L"data_arr5 = "); ArrayMemberData5_data_arr5W_fdump(fp, p->x.data_arr5, tab);
		break;
	case ArrayMemberData5Present_u8_arr1:
		Dz1ThreadW_fprintf(fp, L"u8_arr1 = "); ArrayMemberData5_u8_arr1W_fdump(fp, p->x.u8_arr1, tab);
		break;
	case ArrayMemberData5Present_u8_arr2:
		Dz1ThreadW_fprintf(fp, L"u8_arr2 = "); ArrayMemberData5_u8_arr2W_fdump(fp, p->x.u8_arr2, tab);
		break;
	case ArrayMemberData5Present_u8_arr3:
		Dz1ThreadW_fprintf(fp, L"u8_arr3 = "); ArrayMemberData5_u8_arr3W_fdump(fp, p->x.u8_arr3, tab);
		break;
	case ArrayMemberData5Present_u8_arr4:
		Dz1ThreadW_fprintf(fp, L"u8_arr4 = "); ArrayMemberData5_u8_arr4W_fdump(fp, p->x.u8_arr4, tab);
		break;
	case ArrayMemberData5Present_u8_arr5:
		Dz1ThreadW_fprintf(fp, L"u8_arr5 = "); ArrayMemberData5_u8_arr5W_fdump(fp, p->x.u8_arr5, tab);
		break;
	default:
		Dz1ThreadW_ftprintf(fp, tab, L"??? = %d\n", p->present);
		break;
	}
}
#endif // UNIX_SYSTEM

// ArrayMemberData5
////////////////////////////////////////////////////////////////////////////////

