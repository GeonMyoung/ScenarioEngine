#ifndef _DZ1_TDC_LIBDZ1_SUPPORT_H_
#define _DZ1_TDC_LIBDZ1_SUPPORT_H_

#include <dz1_bin.h>
#include <dz1_stdio.h>

#include <dz1_mutex.h>

#include <dz1_error.h>
#include <dz1_task.h>
#include <dz1_sock_addr.h>
#include <dz1_socket.h>
#include <dz1_socket_buf.h>
#include <dz1_socket_fifo.h>

///////////////////////////////////////////////////////////////////////////////
// Dz1Void TDC support
static __inline__ int	 Dz1Void_cmp(void *a, void *b) { if (a < b) return -1; else if (a > b) return 1; else return 0; }

static __inline__ void	 Dz1VoidA_dump(void *p, int tab) { if (p) Dz1ThreadA_printf("%p\n", p); else Dz1ThreadA_printf("NULL\n"); }
static __inline__ void	 Dz1VoidA_fdump(FILE *fp, void *p, int tab) { if (p) Dz1ThreadA_fprintf(fp, "%p\n", p); else Dz1ThreadA_fprintf(fp, "NULL\n"); }
#ifndef UNIX_SYSTEM
static __inline__ void	 Dz1VoidW_dump(void *p, int tab) { if (p) Dz1ThreadW_printf(L"%p\n", p); else Dz1ThreadW_printf(L"NULL\n"); }
static __inline__ void	 Dz1VoidW_fdump(FILE *fp, void *p, int tab) { if (p) Dz1ThreadW_fprintf(fp, L"%p\n", p); else Dz1ThreadW_fprintf(fp, L"NULL\n"); }
#ifdef UNICODE
#define					 Dz1Void_dump					Dz1VoidW_dump
#define					 Dz1Void_fdump					Dz1VoidW_fdump
#else // UNICODE
#define					 Dz1Void_dump					Dz1VoidA_dump
#define					 Dz1Void_fdump					Dz1VoidA_fdump
#endif // UNICODE
#else	// UNIX_SYSTEM
#define					 Dz1Void_dump					Dz1VoidA_dump
#define					 Dz1Void_fdump					Dz1VoidA_fdump
#endif	// UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ListAddCancelArg
typedef struct Dz1ListAddCancelArg
{
	void			*list;
	void			**node;
} Dz1ListAddCancelArg;

#define Dz1ListAddCancel_impl(list_type, node_type)\
void list_type##_addCancel(void *ptr)\
{\
	Dz1ListAddCancelArg *arg = (Dz1ListAddCancelArg *)ptr;\
	list_type *list = (list_type *)arg->list;\
	node_type **node = (node_type **)arg->node;\
	if (list && node && *node) list->extract(list, *node);\
}

// Dz1ListAddCancelArg
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1ListFDumpArg
typedef struct Dz1ListFDumpArg
{
	FILE			*fp;
	int				 tab;
} Dz1ListFDumpArg;

typedef struct Dz1ListFDumpArg2
{
	FILE			*fp;
	int				*tab;
} Dz1ListFDumpArg2;

typedef struct Dz1ListFDumpArg3
{
	FILE			*fp;
	int				*tab;
	bool_t			 is_first;
} Dz1ListFDumpArg3;
// Dz1ListFDumpArg
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1ListSaveArg
typedef struct Dz1ListSaveArg
{
	FILE	*fp;
	int		 tab;
	bool_t	 isFirst;
} Dz1ListSaveArg;
#define Dz1ListSaveArg_init(argp, fp, tab)	do { (argp)->fp = (fp); (argp)->tab = (tab); (argp)->isFirst = TRUE; } while(0)
// Dz1ListSaveArg
///////////////////////////////////////////////////////////////////////////////

typedef struct Dz1ArrayMemberInfo
{
	void			**arr;
	void			*cntp;
} Dz1ArrayMemberInfo;

///////////////////////////////////////////////////////////////////////////////
// Pointer Element Array Helper (include Referenced Pointer)
// int *a, enum *b, real *c, some_construct *x, some_union *y
#define Dz1StructArrayMemb_ptr_del(parent_type, arr_elem_type, member_name, cnt_type, elem_del)	\
void parent_type##_##member_name##_del(arr_elem_type *arr, cnt_type cnt)\
{\
	if (arr != NULL)\
	{\
		cnt_type i;\
		for (i = 0; i < cnt; i++)\
		{\
			if (arr[i] != NULL)\
			{\
				if (arr[i] != NULL) elem_del(arr[i]);\
				arr[i] = NULL;\
			}\
		}\
		Dz1Free(arr);\
	}\
}
#define Dz1StructArrayMemb_ptrref_del(parent_type, arr_elem_type, member_name, cnt_type)	\
void parent_type##_##member_name##_del(arr_elem_type *arr, cnt_type cnt)\
{\
	if (arr != NULL)\
		Dz1Free(arr);\
}

#define Dz1StructArrayMemb_ptr_delAndSetNull(parent_type, arr_elem_type, member_name, cnt_type)	\
void parent_type##_##member_name##_delAndSetNull(void *ptr)\
{\
	Dz1ArrayMemberInfo *arg = (Dz1ArrayMemberInfo *)ptr;\
	if (arg->arr != NULL && arg->cntp != NULL)\
	{\
		arr_elem_type *arr = (arr_elem_type *)*(arg->arr);\
		cnt_type cnt = *(cnt_type *)arg->cntp;\
		parent_type##_##member_name##_del(arr, cnt);\
		*arg->arr = NULL;\
	}\
}
#define Dz1StructArrayMemb_ptrref_delAndSetNull(parent_type, arr_elem_type, member_name)	\
void parent_type##_##member_name##_delAndSetNull(void *ptr)\
{\
	Dz1ArrayMemberInfo *arg = (Dz1ArrayMemberInfo *)ptr;\
	if (arg->arr != NULL && arg->cntp != NULL)\
	{\
		arr_elem_type *arr = (arr_elem_type *)*(arg->arr);\
		parent_type##_##member_name##_del(arr, 0);\
		*arg->arr = NULL;\
	}\
}

#define Dz1StructArrayMemb_ptr_clone(parent_type, arr_elem_type, member_name, cnt_type, elem_clone)	\
arr_elem_type *parent_type##_##member_name##_clone(arr_elem_type *src, cnt_type cnt, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	arr_elem_type *ret = NULL;\
	if (cnt == 0) ERR_SET_OUT(errp, EINVAL);\
	else if ((ret = (arr_elem_type *)Dz1Calloc(sizeof(arr_elem_type), cnt, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		Dz1ArrayMemberInfo rollback_data = { (void **)&ret, &cnt };\
		pthread_cleanup_push(parent_type##_##member_name##_delAndSetNull, (void *)&rollback_data);\
		if (src != NULL)\
		{\
			cnt_type i;\
			for (i = 0; i < cnt && errp->code == 0; i++)\
			{\
				if (src[i] != NULL && (ret[i] = elem_clone(src[i], errp)) == NULL) ERR_OUT(errp);\
				else Dz1Error_set(errp, 0);\
			}\
		}\
		else Dz1Error_set(errp, 0);\
		pthread_cleanup_pop(errp->code); /* (parent_type##_##member_name##_delAndSetNull, (void *)&rollback_data); */\
	}\
	return ret;\
}
#define Dz1StructArrayMemb_ptrref_clone(parent_type, arr_elem_type, member_name, cnt_type) \
arr_elem_type *parent_type##_##member_name##_clone(arr_elem_type *src, cnt_type cnt, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	arr_elem_type *ret = NULL;\
	if (cnt == 0) ERR_SET_OUT(errp, EINVAL);\
	else if ((ret = (arr_elem_type *)Dz1Calloc(sizeof(arr_elem_type), cnt, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		Dz1ArrayMemberInfo rollback_data = { (void **)&ret, &cnt };\
		pthread_cleanup_push(parent_type##_##member_name##_delAndSetNull, (void *)&rollback_data);\
		if (src != NULL)\
		{\
			cnt_type i;\
			for (i = 0; i < cnt && errp->code == 0; i++)\
				ret[i] = src[i];\
		}\
		Dz1Error_set(errp, 0);\
		pthread_cleanup_pop(errp->code); /* (parent_type##_##member_name##_delAndSetNull, (void *)&rollback_data); */\
	}\
	return ret;\
}

#define Dz1StructArrayMemb_ptr_dump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_dump)	\
void parent_type##_##member_name##_dump(arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1Thread_printf(Dz1T("NULL\n"));\
	else if (cnt == 0) Dz1Thread_printf(Dz1T("empty\n"));\
	else\
	{\
		cnt_type i;\
		arr_elem_type node; \
		Dz1Thread_printf(Dz1T("{ %u entry\n"),(u32_t)cnt); tab++;\
		for (i = 0; i < cnt; i++)\
		{\
			node = src[i];\
			Dz1Thread_tprintf(tab, Dz1T("[%u]%s"),(u32_t)i, bridge);\
			elem_dump(node, tab);\
		}\
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));\
	}\
}
#define Dz1StructArrayMemb_ptrref_dump					Dz1StructArrayMemb_ptr_dump

#define Dz1StructArrayMemb_ptr_fdump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_fdump)	\
void parent_type##_##member_name##_fdump(FILE *fp, arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n)"));\
	else if (cnt == 0) Dz1Thread_fprintf(fp, Dz1T("empty\n"));\
	else\
	{\
		cnt_type i;\
		arr_elem_type node; \
		Dz1Thread_fprintf(fp, Dz1T("{ %u entry\n"),(u32_t)cnt); tab++;\
		for (i = 0; i < cnt; i++)\
		{\
			node = src[i];\
			Dz1Thread_ftprintf(fp, tab, Dz1T("[%u]%s"),(u32_t)i, bridge);\
			elem_fdump(fp, node, tab);\
		}\
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));\
	}\
}
#define Dz1StructArrayMemb_ptrref_fdump					Dz1StructArrayMemb_ptr_fdump

#define Dz1StructArrayMemb_ptrA_dump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_dump)	\
void parent_type##_##member_name##A_dump(arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1ThreadA_printf("NULL\n");\
	else if (cnt == 0) Dz1ThreadA_printf("empty\n");\
	else\
	{\
		cnt_type i;\
		arr_elem_type node; \
		Dz1ThreadA_printf("{ %u entry\n", (u32_t)cnt); tab++;\
		for (i = 0; i < cnt; i++)\
		{\
			node = src[i];\
			Dz1ThreadA_tprintf(tab, "[%u]%s", (u32_t)i, bridge);\
			elem_dump(node, tab);\
		}\
		Dz1ThreadA_tprintf(--tab, "}\n");\
	}\
}
#define Dz1StructArrayMemb_ptrrefA_dump					Dz1StructArrayMemb_ptrA_dump

#define Dz1StructArrayMemb_ptrA_fdump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_fdump)	\
void parent_type##_##member_name##A_fdump(FILE *fp, arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");\
	else if (cnt == 0) Dz1ThreadA_fprintf(fp, "empty\n");\
	else\
	{\
		cnt_type i;\
		arr_elem_type node; \
		Dz1ThreadA_fprintf(fp, "{ %u entry\n", (u32_t)cnt); tab++;\
		for (i = 0; i < cnt; i++)\
		{\
			node = src[i];\
			Dz1ThreadA_ftprintf(fp, tab, "[%u]%s", (u32_t)i, bridge);\
			elem_fdump(fp, node, tab);\
		}\
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");\
	}\
}
#define Dz1StructArrayMemb_ptrrefA_fdump				Dz1StructArrayMemb_ptrA_fdump

#define Dz1StructArrayMemb_ptrW_dump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_dump)	\
void parent_type##_##member_name##W_dump(arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1ThreadW_printf(L"NULL\n");\
	else if (cnt == 0) Dz1ThreadW_printf(L"empty\n");\
	else\
	{\
		cnt_type i;\
		arr_elem_type node; \
		Dz1ThreadW_printf(L"{ %u entry\n", (u32_t)cnt); tab++;\
		for (i = 0; i < cnt; i++)\
		{\
			node = src[i];\
			Dz1ThreadW_tprintf(tab, L"[%u]%s", (u32_t)i, bridge);\
			elem_dump(node, tab);\
		}\
		Dz1ThreadW_tprintf(--tab, L"}\n");\
	}\
}
#define Dz1StructArrayMemb_ptrrefW_dump					Dz1StructArrayMemb_ptrW_dump

#define Dz1StructArrayMemb_ptrW_fdump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_fdump)	\
void parent_type##_##member_name##W_fdump(FILE *fp, arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");\
	else if (cnt == 0) Dz1ThreadW_fprintf(fp, L"empty\n");\
	else\
	{\
		cnt_type i;\
		arr_elem_type node; \
		Dz1ThreadW_fprintf(fp, L"{ %u entry\n", (u32_t)cnt); tab++;\
		for (i = 0; i < cnt; i++)\
		{\
			node = src[i];\
			Dz1ThreadW_ftprintf(fp, tab, L"[%u]%s", (u32_t)i, bridge);\
			elem_fdump(fp, node, tab);\
		}\
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");\
	}\
}
#define Dz1StructArrayMemb_ptrrefW_fdump				Dz1StructArrayMemb_ptrW_fdump
// Pointer Element Array Helper (include Referenced Pointer)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Primitive Element Array Helper
// int a, enum b, real c
#define Dz1StructArrayMemb_val_primitive_del			Dz1StructArrayMemb_ptrref_del			// (parent_type, arr_elem_type, member_name, cnt_type)
#define Dz1StructArrayMemb_val_primitive_delAndSetNull	Dz1StructArrayMemb_ptrref_delAndSetNull	// (parent_type, arr_elem_type, member_name, cnt_type)
#define Dz1StructArrayMemb_val_primitive_clone			Dz1StructArrayMemb_ptrref_clone			// (parent_type, arr_elem_type, member_name, cnt_type)

#define Dz1StructArrayMemb_val_primitive_dump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_dump)	\
void parent_type##_##member_name##_dump(arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1Thread_printf(Dz1T("NULL\n"));\
	else if (cnt == 0) Dz1Thread_printf(Dz1T("empty\n"));\
	else\
	{\
		cnt_type i;\
		arr_elem_type *node; \
		Dz1Thread_printf(Dz1T("{ %u entry\n"),(u32_t)cnt); tab++;\
		for (i = 0, node = src; i < cnt; i++, node++)\
		{\
			Dz1Thread_tprintf(tab, Dz1T("[%u]%s"),(u32_t)i, bridge);\
			elem_dump(node, tab);\
		}\
		Dz1Thread_tprintf(--tab, "}\n");\
	}\
}

#define Dz1StructArrayMemb_val_primitive_fdump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_fdump)	\
void parent_type##_##member_name##_fdump(FILE *fp, arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));\
	else if (cnt == 0) Dz1Thread_fprintf(fp, Dz1T("empty\n"));\
	else\
	{\
		cnt_type i;\
		arr_elem_type *node; \
		Dz1Thread_fprintf(fp, Dz1T("{ %u entry\n"),(u32_t)cnt); tab++;\
		for (i = 0, node = src; i < cnt; i++, node++)\
		{\
			Dz1Thread_ftprintf(fp, tab, Dz1T("[%u]%s"),(u32_t)i, bridge);\
			elem_fdump(fp, node, tab);\
		}\
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));\
	}\
}

#define Dz1StructArrayMemb_val_primitiveA_dump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_dump)	\
void parent_type##_##member_name##A_dump(arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1ThreadA_printf("NULL\n");\
	else if (cnt == 0) Dz1ThreadA_printf("empty\n");\
	else\
	{\
		cnt_type i;\
		arr_elem_type *node; \
		Dz1ThreadA_printf("{ %u entry\n", (u32_t)cnt); tab++;\
		for (i = 0, node = src; i < cnt; i++, node++)\
		{\
			Dz1ThreadA_tprintf(tab, "[%u]%s", (u32_t)i, bridge);\
			elem_dump(node, tab);\
		}\
		Dz1ThreadA_tprintf(--tab, "}\n");\
	}\
}

#define Dz1StructArrayMemb_val_primitiveA_fdump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_fdump)	\
void parent_type##_##member_name##A_fdump(FILE *fp, arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");\
	else if (cnt == 0) Dz1ThreadA_fprintf(fp, "empty\n");\
	else\
	{\
		cnt_type i;\
		arr_elem_type *node; \
		Dz1ThreadA_fprintf(fp, "{ %u entry\n", (u32_t)cnt); tab++;\
		for (i = 0, node = src; i < cnt; i++, node++)\
		{\
			Dz1ThreadA_ftprintf(fp, tab, "[%u]%s", (u32_t)i, bridge);\
			elem_fdump(fp, node, tab);\
		}\
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");\
	}\
}

#define Dz1StructArrayMemb_val_primitiveW_dump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_dump)	\
void parent_type##_##member_name##W_dump(arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1ThreadW_printf(L"NULL\n");\
	else if (cnt == 0) Dz1ThreadW_printf(L"empty\n");\
	else\
	{\
		cnt_type i;\
		arr_elem_type *node; \
		Dz1ThreadW_printf(L"{ %u entry\n", (u32_t)cnt); tab++;\
		for (i = 0, node = src; i < cnt; i++, node++)\
		{\
			Dz1ThreadW_tprintf(tab, L"[%u]%s", (u32_t)i, bridge);\
			elem_dump(node, tab);\
		}\
		Dz1ThreadW_tprintf(--tab, L"}\n");\
	}\
}

#define Dz1StructArrayMemb_val_primitiveW_fdump(parent_type, arr_elem_type, member_name, cnt_type, bridge, elem_fdump)	\
void parent_type##_##member_name##W_fdump(FILE *fp, arr_elem_type *src, cnt_type cnt, int tab)\
{\
	if (src == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");\
	else if (cnt == 0) Dz1ThreadW_fprintf(fp, L"empty\n");\
	else\
	{\
		cnt_type i;\
		arr_elem_type *node; \
		Dz1ThreadW_fprintf(fp, L"{ %u entry\n", (u32_t)cnt); tab++;\
		for (i = 0, node = src; i < cnt; i++, node++)\
		{\
			Dz1ThreadW_ftprintf(fp, tab, L"[%u]%s", (u32_t)i, bridge);\
			elem_fdump(fp, node, tab);\
		}\
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");\
	}\
}
// Primitive Element Array Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Element Array Helper
// some_construct x, some_union y
#define Dz1StructArrayMemb_val_construct_del(parent_type, arr_elem_type, member_name, cnt_type, elem_purge)	\
void parent_type##_##member_name##_del(arr_elem_type *arr, cnt_type cnt)\
{\
	if (arr != NULL)\
	{\
		cnt_type i;\
		arr_elem_type *ap;\
		for (i = 0, ap = arr; i < cnt; i++, ap++)\
			elem_purge(ap);\
		Dz1Free(arr);\
	}\
}
#define Dz1StructArrayMemb_val_construct_delAndSetNull	Dz1StructArrayMemb_ptr_delAndSetNull	// (parent_type, arr_elem_type, member_name, cnt_type)
#define Dz1StructArrayMemb_val_construct_clone(parent_type, arr_elem_type, member_name, cnt_type, elem_copy) \
arr_elem_type *parent_type##_##member_name##_clone(arr_elem_type *src, cnt_type cnt, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	arr_elem_type *ret = NULL;\
	if (cnt == 0) ERR_SET_OUT(errp, EINVAL);\
	else if ((ret = (arr_elem_type *)Dz1Calloc(sizeof(arr_elem_type), cnt, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		Dz1ArrayMemberInfo rollback_data = { (void **)&ret, &cnt };\
		pthread_cleanup_push(parent_type##_##member_name##_delAndSetNull, (void *)&rollback_data);\
		if (src != NULL)\
		{\
			cnt_type i;\
			arr_elem_type *sp, *dp;\
			for (i = 0, dp = ret, sp = src; i < cnt && errp->code == 0; i++, dp++, sp++)\
			{\
				if (elem_copy(dp, sp, errp) == FALSE) ERR_OUT(errp);\
				else Dz1Error_set(errp, 0);\
			}\
		}\
		Dz1Error_set(errp, 0);\
		pthread_cleanup_pop(errp->code); /* (parent_type##_##member_name##_delAndSetNull, (void *)&rollback_data); */\
	}\
	return ret;\
}
#define Dz1StructArrayMemb_val_construct_dump			Dz1StructArrayMemb_val_primitive_dump
#define Dz1StructArrayMemb_val_construct_fdump			Dz1StructArrayMemb_val_primitive_fdump
#define Dz1StructArrayMemb_val_constructA_dump			Dz1StructArrayMemb_val_primitiveA_dump
#define Dz1StructArrayMemb_val_constructA_fdump			Dz1StructArrayMemb_val_primitiveA_fdump
#define Dz1StructArrayMemb_val_constructW_dump			Dz1StructArrayMemb_val_primitiveW_dump
#define Dz1StructArrayMemb_val_constructW_fdump			Dz1StructArrayMemb_val_primitiveW_fdump
// Construct Element Array Helper
///////////////////////////////////////////////////////////////////////////////











///////////////////////////////////////////////////////////////////////////////
// Pointer Element Array without counter Helper
#define Dz1StructArrayMemb_ptr_nocnt_del(parent_type, arr_elem_type, member_name, eoa_cond, elem_del)\
void parent_type##_##member_name##_del(arr_elem_type *arr)\
{\
	if (arr != NULL)\
	{\
		arr_elem_type *ap;\
		for (ap = arr; !(eoa_cond); ap++)\
		{\
			elem_del(*ap);\
			*ap = NULL;\
		}\
		Dz1Free(arr);\
	}\
}
#define Dz1StructArrayMemb_ptrref_nocnt_del(parent_type, arr_elem_type, member_name, eoa_cond)\
void parent_type##_##member_name##_del(arr_elem_type *arr)\
{\
	if (arr != NULL)\
		Dz1Free(arr);\
}

#define Dz1StructArrayMemb_ptr_nocnt_delAndSetNull(parent_type, arr_elem_type, member_name)	\
void parent_type##_##member_name##_delAndSetNull(void *ptr)\
{\
	arr_elem_type **ar = (arr_elem_type **)ptr;\
	if (*ar != NULL)\
	{\
		parent_type##_##member_name##_del(*ar);\
		*ar = NULL;\
	}\
}
#define Dz1StructArrayMemb_ptrref_nocnt_delAndSetNull		Dz1StructArrayMemb_ptr_nocnt_delAndSetNull//(parent_type, arr_elem_type, member_name)

#define Dz1StructArrayMemb_ptr_nocnt_count(parent_type, arr_elem_type, member_name, eoa_cond)\
unsigned int parent_type##_##member_name##_count(arr_elem_type *arr)\
{\
	unsigned int ret = 0;\
	if (arr != NULL)\
	{\
		arr_elem_type *ap;\
		for (ap = arr; !(eoa_cond); ap++, ret++);\
		ret++; /* for NULL entry */ \
	}\
	return ret;\
}
#define Dz1StructArrayMemb_ptrref_nocnt_count				Dz1StructArrayMemb_ptr_nocnt_count//(parent_type, arr_elem_type, member_name)

#define Dz1StructArrayMemb_ptr_nocnt_clone(parent_type, arr_elem_type, member_name, eoa_cond, elem_clone)	\
arr_elem_type *parent_type##_##member_name##_clone(arr_elem_type *src, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	arr_elem_type *ret = NULL;\
	unsigned int cnt = 0;\
	if (src == NULL) ERR_SET_OUT(errp, EINVAL); \
	else if ((cnt = parent_type##_##member_name##_count(src)) == 0) ERR_SET_OUT(errp, ENOENT); /* at least 1 entry */ \
	else if ((ret = (arr_elem_type *)Dz1Calloc(sizeof(arr_elem_type), cnt, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		unsigned int i;\
		pthread_cleanup_push(parent_type##_##member_name##_delAndSetNull, (void *)&ret);\
		for (i = 0; i < cnt && errp->code == 0; i++)\
		{\
			if ((ret[i] = elem_clone(src[i], errp)) == NULL) ERR_OUT(errp);\
			else Dz1Error_set(errp, 0);\
		}\
		pthread_cleanup_pop(errp->code); /* (parent_type##_##member_name##_delAndSetNull, (void *)&ret); */\
	}\
	return ret;\
}
#define Dz1StructArrayMemb_ptrref_nocnt_clone(parent_type, arr_elem_type, member_name, eoa_cond) \
arr_elem_type *parent_type##_##member_name##_clone(arr_elem_type *src, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	arr_elem_type *ret = NULL;\
	unsigned int cnt = 0;\
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if ((cnt = parent_type##_##member_name##_count(src)) == 0) ERR_SET_OUT(errp, ENOENT); /* at least 1 entry */ \
	else if ((ret = (arr_elem_type *)Dz1Calloc(sizeof(arr_elem_type), cnt, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		unsigned int i;\
		for (i = 0; i < cnt && errp->code == 0; i++) ret[i] = src[i];\
		Dz1Error_set(errp, 0);\
	}\
	return ret;\
}

#define Dz1StructArrayMemb_ptr_nocnt_dump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_dump) \
void parent_type##_##member_name##_dump(arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1Thread_printf(Dz1T("NULL\n"));\
	else if (eoa_cond) Dz1Thread_printf(Dz1T("empty\n"));\
	else\
	{\
		unsigned int idx;\
		Dz1Thread_printf(Dz1T("{\n")); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1Thread_tprintf(tab, Dz1T("[%u]%s"),idx, bridge);\
			elem_dump(*ap, tab);\
		}\
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));\
	}\
}
#define Dz1StructArrayMemb_ptrref_nocnt_dump			Dz1StructArrayMemb_ptr_nocnt_dump

#define Dz1StructArrayMemb_ptr_nocnt_fdump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_fdump) \
void parent_type##_##member_name##_fdump(FILE *fp, arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (src == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));\
	else if (eoa_cond) Dz1Thread_fprintf(fp, Dz1T("empty\n"));\
	else\
	{\
		unsigned int idx;\
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1Thread_ftprintf(fp, tab, Dz1T("[%u]%s"),idx, bridge);\
			elem_fdump(fp, *ap, tab);\
		}\
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));\
	}\
}
#define Dz1StructArrayMemb_ptrref_nocnt_fdump			Dz1StructArrayMemb_ptr_nocnt_fdump

#define Dz1StructArrayMemb_ptr_nocntA_dump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_dump)	\
void parent_type##_##member_name##A_dump(arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1ThreadA_printf("NULL\n");\
	else if (eoa_cond) Dz1ThreadA_printf("empty\n");\
	else\
	{\
		unsigned int idx;\
		Dz1ThreadA_printf("{\n"); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1ThreadA_tprintf(tab, "[%u]%s", idx, bridge);\
			elem_dump(*ap, tab);\
		}\
		Dz1ThreadA_tprintf(--tab, "}\n");\
	}\
}
#define Dz1StructArrayMemb_ptrref_nocntA_dump			Dz1StructArrayMemb_ptr_nocntA_dump

#define Dz1StructArrayMemb_ptr_nocntA_fdump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_fdump) \
void parent_type##_##member_name##A_fdump(FILE *fp, arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");\
	else if (eoa_cond) Dz1ThreadA_fprintf(fp, "empty\n");\
	else\
	{\
		unsigned int idx;\
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1ThreadA_ftprintf(fp, tab, "[%u]%s", idx, bridge);\
			elem_fdump(fp, *ap, tab);\
		}\
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");\
	}\
}
#define Dz1StructArrayMemb_ptrref_nocntA_fdump			Dz1StructArrayMemb_ptr_nocntA_fdump

#define Dz1StructArrayMemb_ptr_nocntW_dump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_dump)	\
void parent_type##_##member_name##W_dump(arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1ThreadW_printf(L"NULL\n");\
	else if (eoa_cond) Dz1ThreadW_printf(L"empty\n");\
	else\
	{\
		unsigned int idx;\
		Dz1ThreadW_printf(L"{\n"); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1ThreadW_tprintf(tab, L"[%u]%s", idx, bridge);\
			elem_dump(*ap, tab);\
		}\
		Dz1ThreadW_tprintf(--tab, L"}\n");\
	}\
}
#define Dz1StructArrayMemb_ptrref_nocntW_dump			Dz1StructArrayMemb_ptr_nocntW_dump

#define Dz1StructArrayMemb_ptr_nocntW_fdump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_fdump)	\
void parent_type##_##member_name##W_fdump(FILE *fp, arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");\
	else if (eoa_cond) Dz1ThreadW_fprintf(fp, L"empty\n");\
	else\
	{\
		unsigned int idx;\
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1ThreadW_ftprintf(fp, tab, L"[%u]%s", idx, bridge);\
			elem_fdump(fp, *ap, tab);\
		}\
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");\
	}\
}
#define Dz1StructArrayMemb_ptrref_nocntW_fdump			Dz1StructArrayMemb_ptr_nocntW_fdump
// Pointer Element Array without counter Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Primitive Element Array without counter Helper
#define Dz1StructArrayMemb_val_primitive_nocnt_del				Dz1StructArrayMemb_ptrref_nocnt_del		// (parent_type, arr_elem_type, member_name)
#define Dz1StructArrayMemb_val_primitive_nocnt_delAndSetNull(parent_type, arr_elem_type, member_name) \
void parent_type##_##member_name##_delAndSetNull(void *ptr)\
{\
	Dz1ArrayMemberInfo *arg = (Dz1ArrayMemberInfo *)ptr;\
	if (arg->arr != NULL && arg->cntp != NULL)\
	{\
		arr_elem_type *arr = (arr_elem_type *)*(arg->arr);\
		parent_type##_##member_name##_del(arr);\
		*arg->arr = NULL;\
	}\
}

#define Dz1StructArrayMemb_val_primitive_nocnt_count(parent_type, arr_elem_type, member_name, eoa_cond)\
unsigned int parent_type##_##member_name##_count(arr_elem_type *arr)\
{\
	unsigned int ret = 0;\
	if (arr != NULL)\
	{\
		arr_elem_type *ap;\
		for (ap = arr; !(eoa_cond); ap++, ret++);\
		ret++; /* for NULL entry */ \
	}\
	return ret;\
}
#define Dz1StructArrayMemb_val_primitive_nocnt_clone(parent_type, arr_elem_type, member_name, eoa_cond) \
arr_elem_type *parent_type##_##member_name##_clone(arr_elem_type *src, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	arr_elem_type *ret = NULL;\
	unsigned int cnt = 0; \
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if ((cnt = parent_type##_##member_name##_count(src)) == 0) ERR_SET_OUT(errp, ENOENT); /* at least 1 entry */ \
	else if ((ret = (arr_elem_type *)Dz1Calloc(sizeof(arr_elem_type), cnt, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		unsigned int i;\
		arr_elem_type *sp, *dp;\
		pthread_cleanup_push(parent_type##_##member_name##_delAndSetNull, (void *)&ret);\
		for (i = 0, dp = ret, sp = src; errp->code == 0 && i < cnt; dp++, sp++, i++) *dp = *sp;\
		Dz1Error_set(errp, 0);\
		pthread_cleanup_pop(errp->code); /* (parent_type##_##member_name##_delAndSetNull, (void *)&ret); */\
	}\
	return ret;\
}
#define Dz1StructArrayMemb_val_primitive_nocnt_dump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_dump) \
void parent_type##_##member_name##_dump(arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src;\
	if (ap == NULL) Dz1Thread_printf(Dz1T("NULL\n"));\
	else if (eoa_cond) Dz1Thread_printf(Dz1T("empty\n"));\
	else\
	{\
		unsigned int idx;\
		Dz1Thread_printf(Dz1T("{\n")); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1Thread_tprintf(tab, Dz1T("[%u]%s"),idx, bridge);\
			elem_dump(ap, tab);\
		}\
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));\
	}\
}
#define Dz1StructArrayMemb_val_primitive_nocnt_fdump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_fdump) \
void parent_type##_##member_name##_fdump(FILE *fp, arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));\
	else if (eoa_cond) Dz1Thread_fprintf(fp, Dz1T("empty\n"));\
	else\
	{\
		unsigned int idx;\
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1Thread_ftprintf(fp, tab, Dz1T("[%u]%s"),idx, bridge);\
			elem_fdump(fp, ap, tab);\
		}\
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));\
	}\
}
#define Dz1StructArrayMemb_val_primitive_nocntA_dump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_dump) \
void parent_type##_##member_name##A_dump(arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1ThreadA_printf("NULL\n");\
	else if (eoa_cond) Dz1ThreadA_printf("empty\n");\
	else\
	{\
		unsigned int idx;\
		Dz1ThreadA_printf("{\n"); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1ThreadA_tprintf(tab, "[%u]%s", idx, bridge);\
			elem_dump(ap, tab);\
		}\
		Dz1ThreadA_tprintf(--tab, "}\n");\
	}\
}
#define Dz1StructArrayMemb_val_primitive_nocntA_fdump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_fdump) \
void parent_type##_##member_name##A_fdump(FILE *fp, arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");\
	else if (eoa_cond) Dz1ThreadA_fprintf(fp, "empty\n");\
	else\
	{\
		unsigned int idx;\
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1ThreadA_ftprintf(fp, tab, "[%u]%s",idx, bridge);\
			elem_fdump(fp, ap, tab);\
		}\
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");\
	}\
}
#define Dz1StructArrayMemb_val_primitive_nocntW_dump(parent_type, arr_elem_type, member_name, eoa_cond,bridge, elem_dump) \
void parent_type##_##member_name##W_dump(arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1ThreadW_printf(L"NULL\n");\
	else if (eoa_cond) Dz1ThreadW_printf(L"empty\n");\
	else\
	{\
		unsigned int idx;\
		Dz1ThreadW_printf(L"{\n"); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1ThreadW_tprintf(tab, L"[%u]%s",idx, bridge);\
			elem_dump(ap, tab);\
		}\
		Dz1ThreadW_tprintf(--tab, L"}\n");\
	}\
}
#define Dz1StructArrayMemb_val_primitive_nocntW_fdump(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_fdump) \
void parent_type##_##member_name##W_fdump(FILE *fp, arr_elem_type *src, int tab)\
{\
	arr_elem_type *ap = src; \
	if (ap == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");\
	else if (eoa_cond) Dz1ThreadW_fprintf(fp, L"empty\n");\
	else\
	{\
		unsigned int idx;\
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;\
		for (idx = 0; !(eoa_cond); ap++, idx++)\
		{\
			Dz1ThreadW_ftprintf(fp, tab, L"[%u]%s",idx, bridge);\
			elem_fdump(fp, ap, tab);\
		}\
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");\
	}\
}
// Primitive Element Array without counter Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Element Array without counter Helper
#define Dz1StructArrayMemb_val_construct_nocnt_del(parent_type, arr_elem_type, member_name, eoa_cond, elem_purge)	\
void parent_type##_##member_name##_del(arr_elem_type *arr)\
{\
	if (arr != NULL)\
	{\
		arr_elem_type *ap;\
		for (ap = arr; !(eoa_cond); ap++)\
			elem_purge(ap);\
		Dz1Free(arr);\
	}\
}
#define Dz1StructArrayMemb_val_construct_nocnt_delAndSetNull	Dz1StructArrayMemb_ptr_nocnt_delAndSetNull//(parent_type, arr_elem_type, member_name)
#define Dz1StructArrayMemb_val_construct_nocnt_count			Dz1StructArrayMemb_val_primitive_nocnt_count//(parent_type, arr_elem_type, member_name, eoa_cond)
#define Dz1StructArrayMemb_val_construct_nocnt_clone(parent_type, arr_elem_type, member_name, eoa_cond, elem_copy) \
arr_elem_type *parent_type##_##member_name##_clone(arr_elem_type *src, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	arr_elem_type *ret = NULL;\
	unsigned int cnt = 0; \
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if ((cnt = parent_type##_##member_name##_count(src)) == 0) ERR_SET_OUT(errp, ENOENT); /* at least 1 entry */ \
	else if ((ret = (arr_elem_type *)Dz1Calloc(sizeof(arr_elem_type), cnt, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		unsigned int i;\
		arr_elem_type *sp, *dp;\
		pthread_cleanup_push(parent_type##_##member_name##_delAndSetNull, (void *)&ret);\
		for (i = 0, dp = ret, sp = src; errp->code == 0 && i < cnt; dp++, sp++, i++)\
		{\
			if (elem_copy(dp, sp, errp) == FALSE) ERR_OUT(errp);\
			else Dz1Error_set(errp, 0);\
		}\
		pthread_cleanup_pop(errp->code); /* (parent_type##_##member_name##_delAndSetNull, (void *)&ret); */\
	}\
	return ret;\
}

#define Dz1StructArrayMemb_val_construct_nocnt_dump		Dz1StructArrayMemb_val_primitive_nocnt_dump//(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_dump)
#define Dz1StructArrayMemb_val_construct_nocnt_fdump	Dz1StructArrayMemb_val_primitive_nocnt_fdump//(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_fdump)
#define Dz1StructArrayMemb_val_construct_nocntA_dump	Dz1StructArrayMemb_val_primitive_nocntA_dump//(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_dump)
#define Dz1StructArrayMemb_val_construct_nocntA_fdump	Dz1StructArrayMemb_val_primitive_nocntA_fdump//(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_fdump)
#define Dz1StructArrayMemb_val_construct_nocntW_dump	Dz1StructArrayMemb_val_primitive_nocntW_dump//(parent_type, arr_elem_type, member_name, eoa_cond,bridge, elem_dump)
#define Dz1StructArrayMemb_val_construct_nocntW_fdump	Dz1StructArrayMemb_val_primitive_nocntW_fdump//(parent_type, arr_elem_type, member_name, eoa_cond, bridge, elem_fdump)
// Construct Element Array without counter Helper
///////////////////////////////////////////////////////////////////////////////

#endif 
