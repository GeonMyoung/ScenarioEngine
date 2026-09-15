#ifndef DZ1_ERROR_H
#define DZ1_ERROR_H

#include <dz1.h>

#define DZ1_ERROR_COMMENT_SIZE		1000
#define DZ1_ERROR_COMMENT_LEN		DZ1_ALIGNED_SIZE(DZ1_ERROR_COMMENT_SIZE)

//Dz1Error Á¤ÀÇ
typedef struct Dz1Error
{
//	__DZ1ALIGN(int, code);
	int code;
	char comment[DZ1_ERROR_COMMENT_LEN];
} Dz1Error;

//#define DZ1_ERROR_INITIALIZER		{ 0, { 0, }, { 0, } }
#define DZ1_ERROR_INITIALIZER		{ 0, { 0, } }

DZ1_CPPLINK DZ1_DLLPORT str_t Dz1ErrorStrA(int code);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t Dz1ErrorStrW(int code);
#ifdef UNICODE
#define Dz1ErrorStr			Dz1ErrorStrW
#else // UNICODE
#define Dz1ErrorStr			Dz1ErrorStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1ErrorStr			Dz1ErrorStrA
#endif // UNIX_SYSTEM
/*
DZ1_CPPLINK DZ1_DLLPORT Dz1Error *Dz1Error_clone(Dz1Error *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Error_del(void *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Error_dump(Dz1Error *p, int tab);
*/

/*
 * Dz1Error_set : Set Error code to Dz1Error structure
 *
 * @errp : Address of Dz1Error structure
 * @err_code : Error Code
 *
 */
#define							   Dz1Error_set(errp, err_code) _Dz1Error_set(errp, err_code, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Error *_Dz1Error_set(Dz1Error *err, int error_code, const char *file, int line);

/*
 * Dz1Error_setWithComment : Set Error code with comment to Dz1Error structure
 *
 * @errp : Address of Dz1Error structure
 * @err_code : Error Code
 * @comment_args : argument of sprintf to make comment
 *
 */
#define DZ1_ERROR_ARG				__comment__, DZ1_ERROR_COMMENT_LEN

#define Dz1Error_setWithComment(errp, err_code, comment_args) \
do {\
	char __comment__[DZ1_ERROR_COMMENT_LEN];\
	snprintf comment_args;\
	_Dz1Error_setWithComment(errp, err_code, __FILE__, __LINE__, __comment__);\
} while(0)
DZ1_CPPLINK DZ1_DLLPORT void _Dz1Error_setWithComment(Dz1Error *err, int error_code, const char *file, int line, const char *comment);

/*
 * Dz1Error_dump : Dump Error Context
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1ErrorA_dump(Dz1Error *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ErrorA_fdump(FILE *fp, Dz1Error *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1ErrorW_dump(Dz1Error *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ErrorW_fdump(FILE *fp, Dz1Error *p, int tab);
#ifndef UNICODE
#define						 Dz1Error_dump			Dz1ErrorW_dump
#define						 Dz1Error_fdump			Dz1ErrorW_fdump
#else // UNICODE
#define						 Dz1Error_dump			Dz1ErrorA_dump
#define						 Dz1Error_fdump			Dz1ErrorA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1Error_dump			Dz1ErrorA_dump
#define						 Dz1Error_fdump			Dz1ErrorA_fdump
#endif // UNIX_SYSTEM

/*
 * Dz1Error_print : Print Error Context to target console
 *
 * @con : target console
 * @errp : Address of Da1Error structure
 * @tab : indent level
 *
 */
#define						  Dz1Error_print(errp, tab) _Dz1Error_print(errp, tab, __FILE__, __LINE__)			// Macro for including Print Location
DZ1_CPPLINK DZ1_DLLPORT void _Dz1Error_print(Dz1Error *err, int tab, const char *file, int line);

#define ERR_PROBE(errp)								((errp)->code ? TRUE : FALSE)
#define ERR_HAPPEN(errp)							((errp)->code != 0)
#define SELECT_BY_ERR(errp, succ, fail)				(ERR_HAPPEN(errp) ? fail : succ)
#define ERR_IS_SUCCESS(errp)						((errp)->code == 0 ? TRUE : FALSE)
#define ERR_IS_FAIL(errp)							(ERR_HAPPEN(errp) ? TRUE : FALSE)

#define ERR_SET(errp, val)							Dz1Error_set(errp, val)
#define ERR_SET_RET(errp, val, retv)				do { Dz1Error_set(errp, val); return (retv); } while(0)
#define ERR_CLEAR(errp)								Dz1Error_set(errp, 0)

#define ERR_OUT(errp)								Dz1Error_print(errp, 0)
#define ERR_OUT_TRC(errp, file, line)				_Dz1Error_print((errp), 0, file, line)

#define ERR_SET_OUT(errp, val)						do { Dz1Error_set(errp, val); ERR_OUT(errp); } while(0)
#define ERR_SET_OUT_TRC(errp, val, file, line)		do { Dz1Error_set(errp, val); ERR_OUT_TRC(errp, file, line) } while(0)

#define ERR_SET_OUT_RET(errp, val, retv)			do { ERR_SET_OUT(errp, val); return (retv); } while(0)
#define ERR_SETOUT_RET(errp, val, retv)				ERR_SET_OUT_RET(errp, val, retv)
#define ERR_OUT_RET(errp, retv)						do { ERR_OUT(errp);			 return (retv); } while(0)

#ifndef UNIX_SYSTEM
#define DZ1_ERROR_SAFE_DECLARE					DZ1_ERROR_SAFE_PTR
#define DZ1_ERROR_SAFE_PTR(dst, src)			Dz1Error _##src = DZ1_ERROR_INITIALIZER, *dst = src ? src : &_##src
#define DZ1_ERROR_SAFE_VAR(ptr, var)			Dz1Error var = DZ1_ERROR_INITIALIZER, *ptr = &var
#else
#define DZ1_ERROR_SAFE_DECLARE(dst, src)		Dz1Error _##src = DZ1_ERROR_INITIALIZER, *dst = src ? src : &_##src
#define DZ1_ERROR_SAFE_PTR(dst, src)			Dz1Error _##src = DZ1_ERROR_INITIALIZER, *dst = src ? src : &_##src
#define DZ1_ERROR_SAFE_VAR(ptr, var)			Dz1Error var = DZ1_ERROR_INITIALIZER, *ptr = &var
#endif

#ifdef _WINDOWS
#ifdef UNICODE
DZ1_CPPLINK void *Dz1String_conv(void *src, size_t src_byte_size, const char *src_charsetname, const char *dst_charsetname, size_t *ret_byte_size);
#define ERR_DLG_OUT_WITH_TITLE(errp, title)	do\
							{\
								CString msg;\
								wstr_t comment = (wstr_t)Dz1String_conv((errp)->comment, strlen((errp)->comment), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_WIDE_CHARSET, NULL);\
								if (comment == NULL) msg.Format(L"%s(%d)", Dz1ErrorStrW((errp)->code), (errp)->code);\
								else\
								{\
									msg.Format(L"%s = %s(%d)", comment, Dz1ErrorStrW((errp)->code), (errp)->code);\
									Dz1Free(comment);\
								}\
								MessageBox(msg, title);\
								ERR_OUT((errp));\
							} while(0)
#define ERR_DLG_OUT(errp)		ERR_DLG_OUT_WITH_TITLE(errp, L"Dz1Error")
#else // UNICODE
#define ERR_DLG_OUT_WITH_TITLE(errp, title)	do\
							{\
								CString msg;\
								msg.Format("%s = %s(%d)", (errp)->comment, Dz1ErrorStrA((errp)->code), (errp)->code);\
								MessageBox(msg, title);\
								ERR_OUT((errp));\
							} while(0)
#define ERR_DLG_OUT(errp)		ERR_DLG_OUT_WITH_TITLE(errp, "Dz1Error")
#endif // UNICODE
#define ERR_DLG_SET_OUT(errp, val) do { Dz1Error_set((errp), val); ERR_DLG_OUT(errp); } while(0)
#define ERR_DLG_SET_OUT_WITH_TITLE(errp, val, title) do { Dz1Error_set((errp), val); ERR_DLG_OUT_WITH_TITLE(errp, title); } while(0)
#endif // _WINDOWS

#define							   Dz1Error_clone(srcp, errp)		_Dz1Error_clone((srcp), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Error *_Dz1Error_clone(Dz1Error *src, Dz1Error *err, const char *__file__, int __line__);

#define							  Dz1Error_del(ptr) _Dz1Error_del(ptr, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT void	 _Dz1Error_del(Dz1Error *p, const char *__file__, int __line__);
static __inline__ void			  Dz1Error_delAndSetNull(void *pptr)
{
	Dz1Error **p = (Dz1Error **)pptr;
	Dz1Error_del(*p); *p = NULL;
}

typedef void *(*Dz1GenFunc)(Dz1Error *erp);

#endif
