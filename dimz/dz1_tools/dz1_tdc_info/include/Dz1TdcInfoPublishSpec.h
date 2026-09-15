#ifndef PUBLISH_SPEC_H
#define PUBLISH_SPEC_H

#include <Dz1TdcInfoCommon.h>
#include "Dz1TdcInfoArray.h"

static __inline__ void tab_publish(FILE *fp, int tab) { while(tab--) fprintf(fp, "\t"); }
#define TP(fp, tab)		tab_publish(fp, tab)

// if isPointer == TRUE then
// 		flow function is needed
//
//		<nativeName> <nativeName><newPostFix>(<nativeName> src, <ErrorType> *err);
//		void <nativeName><delPostFix>(<nativeName> p);
//		void <nativeName><delAndSetNullPostFix>(void *ptr);
//		void <nativeName><dumpPostFix>(<nativeName> p, int tab);
//		int <nativeName><cmpPostFix>(<nativeName> a, <nativeName> b);
//
// end if

///////////////////////////////////////////////////////////////////////////////
// Native Type Spec
typedef enum NativeStorage
{
	NativeStorage_data,		// primitive
	NativeStorage_address,	// pointer
	NativeStorage_none,		// void
	NativeStorage_max
} NativeStorage;

str_t NativeStorageStr(NativeStorage src);

typedef struct NativeTypeSpec
{
	str_t			 name;		// Object Name(TDC Type Name)
	str_t			 native;	// original implementation name
	NativeStorage	 storage;	// storage attribute
	str_t			 prefix;	// API prefix name
	u32_t			 attr_flag;	// some flags
} NativeTypeSpec;
// Native Type Spec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Basic Spec
typedef struct PublishBasicSpec
{
	str_t			cpplink;
	str_t			dllport;
	str_t			printf[3];
	str_t			tprintf[3];
	str_t			fprintf[3];
	str_t			ftprintf[3];
} PublishBasicSpec;

DZ1_CPPLINK PublishBasicSpec *PublishBasicSpec_new(str_t cpplink, str_t dllport, 
												   str_t printf, str_t printfA, str_t printfW, 
												   str_t tprintf, str_t tprintfA, str_t tprintfW,
												   str_t fprintf, str_t fprintfA, str_t fprintfW, 
												   str_t ftprintf, str_t ftprintfA, str_t ftprintfW, 
												   Dz1Error *err);
void PublishBasicSpec_del(PublishBasicSpec *p);
void PublishBasicSpec_dump(PublishBasicSpec *p, int tab);
static __inline__ void PublishBasicSpec_delAndSetNull(void *ptr)
{
	PublishBasicSpec **p = (PublishBasicSpec **)ptr;
	PublishBasicSpec_del(*p); *p = NULL;
}
// Basic Spec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Error Spec
typedef enum ErrorCodeGenType
{
	ErrorCodeGenType_init,			// for pointer type error variable : var = real destination, arg = temporary destination
									// else var = error variable, arg = NULL
	ErrorCodeGenType_set,			// val = error variable, arg = error value
	ErrorCodeGenType_print,			// var = error variable, arg = NULL
	ErrorCodeGenType_setAndPrint,	// var = error variable, arg = error value
	ErrorCodeGenType_probe,			// var = error variable, arg = NULL
	ErrorCodeGenType_clear			// var = error variable, arg = NULL
} ErrorCodeGenType;

typedef struct PublishErrorSpecEntry
{
	str_t					name;
	bool_t					argIsPtr;
} PublishErrorSpecEntry;

PublishErrorSpecEntry	*PublishErrorSpecEntry_new(str_t name, bool_t argIsPtr, Dz1Error *err);
void					 PublishErrorSpecEntry_del(PublishErrorSpecEntry *p);
void					 PublishErrorSpecEntry_dump(PublishErrorSpecEntry *p, int tab);
static __inline__ void	 PublishErrorSpecEntry_delAndSetNull(void *ptr)
{
	PublishErrorSpecEntry **p = (PublishErrorSpecEntry **)ptr;
	PublishErrorSpecEntry_del(*p); *p = NULL;
}

typedef struct PublishErrorSpec
{
	str_t					type;			// error variable type
	str_t					defaultVal;		// initial default value
	PublishErrorSpecEntry	*set;
	PublishErrorSpecEntry	*print;
	PublishErrorSpecEntry	*setAndPrint;
	PublishErrorSpecEntry	*probe;
	PublishErrorSpecEntry	*clear;
	str_t					(*code)(struct PublishErrorSpec *p, char buf[1024], ErrorCodeGenType type, str_t var, str_t arg);
} PublishErrorSpec;

PublishErrorSpec		*PublishErrorSpec_new(str_t type, str_t defaultVal,
											  PublishErrorSpecEntry	*set,
											  PublishErrorSpecEntry	*print,
											  PublishErrorSpecEntry	*setAndPrint,
											  PublishErrorSpecEntry	*probe,
											  PublishErrorSpecEntry	*clear, Dz1Error *err);
void					 PublishErrorSpec_del(PublishErrorSpec *p);
void					 PublishErrorSpec_dump(PublishErrorSpec *p, int tab);
static __inline__ void	 PublishErrorSpec_delAndSetNull(void *ptr)
{
	PublishErrorSpec **p = (PublishErrorSpec **)ptr;
	PublishErrorSpec_del(*p); *p = NULL;
}
// Error Spec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Cast Spec
typedef struct PublishCastSpec
{
	str_t			del;
	str_t			cmp;
	str_t			dump;
} PublishCastSpec;

PublishCastSpec			*PublishCastSpec_new(str_t del, str_t cmp, str_t dump, Dz1Error *err);
void					 PublishCastSpec_del(PublishCastSpec *p);
void					 PublishCastSpec_dump(PublishCastSpec *p, int tab);
static __inline__ void	 PublishCastSpec_delAndSetNull(void *ptr)
{
	PublishCastSpec **p = (PublishCastSpec **)ptr;
	PublishCastSpec_del(*p); *p = NULL;
}
// Cast Spec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Memory Function Spec
typedef struct PublishMemFuncSpec
{
	bool_t		allocNeedErrorPtr;
	str_t		malloc;
	str_t		calloc;
	str_t		free;
	str_t		cancel;
} PublishMemFuncSpec;

PublishMemFuncSpec		*PublishMemFuncSpec_new(bool_t allocNeedErrorPtr, str_t malloc, str_t calloc, str_t free, str_t cancel, Dz1Error *err);
void					 PublishMemFuncSpec_del(PublishMemFuncSpec *p);
void					 PublishMemFuncSpec_dump(PublishMemFuncSpec *p, int tab);
static __inline__ void	 PublishMemFuncSpec_delAndSetNull(void *ptr)
{
	PublishMemFuncSpec **p = (PublishMemFuncSpec **)ptr;
	PublishMemFuncSpec_del(*p); *p = NULL;
}
// Memory Function Spec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Post Fix Spec
typedef struct PublishPostFix
{
	str_t			_new;
	str_t			_gen;
	str_t			_purge;
	str_t			_del;
	str_t			_delAndSetNull;
	str_t			_dump;
	str_t			_fdump;
	str_t			_cmp;
	str_t			_clone;
	str_t			_copy;
	str_t			_enc;
	str_t			_dec;
	int				lenMax;
} PublishPostFix;

PublishPostFix			*PublishPostFix_new(str_t _new, str_t _gen, str_t _putge, str_t _del, str_t _delAndSetNull, str_t _dump, str_t _fdump, str_t _cmp, str_t _clone, str_t _copy, str_t _enc, str_t _dec, Dz1Error *err);
void					 PublishPostFix_del(PublishPostFix *p);
void					 PublishPostFix_dump(PublishPostFix *p, int tab);
static __inline__ void	 PublishPostFix_delAndSetNull(void *ptr)
{
	PublishPostFix **p = (PublishPostFix **)ptr;
	PublishPostFix_del(*p); *p = NULL;
}
void					 PublishPostFix_lengthFix(PublishPostFix *p);
// Post Fix Spec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Spec
typedef enum
{
	ArraySpecCallType_method,
	ArraySpecCallType_func
} ArraySpecCallType;

typedef enum
{	// Mandatory API
	ArraySpecApiType_new,			// type *(del, dump, *err) | type *(cmp, del, dump, *err)
	ArraySpecApiType_purge,			// void (type *)
	ArraySpecApiType_del,			// void (type *)
	ArraySpecApiType_delAndSetNull, // void (void *)

	// Optional API
//	ArraySpecApiType_dump,			// void (type *, tab)
	ArraySpecApiType_clone,			// type *(type *, ErrorType *)

	// Mandatory Array API 
	ArraySpecApiType_add,			// ErrorType (type *, void *data)
	ArraySpecApiType_remove,		// void (type *, void *dataOrKey)
	ArraySpecApiType_travelForward,	// ErrorType (type *, func, arg)
	ArraySpecApiType_travelBackward,// ErrorType (type *, func, arg)

	// Optional API
	ArraySpecApiType_extract,		// void *(type *, void *dataOrKey)

	// Optional API (can generate)
	ArraySpecApiType_cnt,			// void *(type *)
	ArraySpecApiType_find,			// void *(type *, void *key)
	ArraySpecApiType_gethead,		// void *(type *)
	ArraySpecApiType_gettail,		// void *(type *)

	ArraySpecApiType_max
} ArraySpecApiType;

str_t			 ArraySpecApiTypeStr(ArraySpecApiType type);
ArraySpecApiType ArraySpecApiTypeFromStr(str_t str);

typedef struct PublishArraySpecApiMap
{
	ArraySpecCallType		type;
	str_t					name;
} PublishArraySpecApiMap;
// Method Calling Type Name Generation ::= {ArrayTypeName}{->|.}{name}
// Method Calling Type Name Generation ::= {ArrayTypeName}{_}{name}

typedef enum
{
	NewFuncArgMode_delAndDump,
	NewFuncArgMode_cmpAndDelAndDump
} NewFuncArgMode;

typedef struct PublishArraySpec
{
	str_t					 name;
	bool_t					 createNeedCmp;
	str_t					 travelFuncCast;
	PublishArraySpecApiMap	*map[ArraySpecApiType_max];
//	Dz1Error				 (*addMap)(struct PublishArraySpec *p, ArraySpecApiType apiType, ArraySpecCallType callType, str_t name);
	bool_t					 (*addMap)(struct PublishArraySpec *p, ArraySpecApiType apiType, ArraySpecCallType callType, str_t name, Dz1Error *err);
	str_t					 (*apiName)(struct PublishArraySpec *p, str_t buf, ArraySpecApiType type, str_t object);
	str_t					 (*code)(struct PublishArraySpec *p, PublishCastSpec *cast, str_t buf, ArraySpecApiType type,
									 str_t object, str_t arg0, str_t arg1, str_t arg2, str_t arg3);
} PublishArraySpec;

PublishArraySpec		*PublishArraySpec_new(str_t name, bool_t createNeedCmp, str_t travelFuncCast, Dz1Error *err);
void					 PublishArraySpec_del(PublishArraySpec *p);
void					 PublishArraySpec_dump(PublishArraySpec *p, int tab);
static __inline__ void	 PublishArraySpec_delAndSetNull(void *ptr)
{
	PublishArraySpec **p = (PublishArraySpec **)ptr;
	PublishArraySpec_del(*p); *p = NULL;
}
// Array Spec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Publish Spec
typedef struct PublishSpec
{
	bool_t				 pthread;

	PublishBasicSpec	*base;

	PublishErrorSpec	*error;
	PublishCastSpec		*cast;
	PublishMemFuncSpec	*mem;

	PublishPostFix		*postFix;

	PublishArraySpec	*arraySpec[ArrayType_max];

	void				*primitives;					// List of NativeSpec
	void				*headerInclude;					// List of str_t	foundational includes in header
	void				*sourceInclude;					// List of str_t	foundational includes in source

	bool_t				 (*regPrimitive)(struct PublishSpec *p, str_t name, str_t native, bool_t isPointer, str_t prefix, u32_t attr_flag, Dz1Error *err);
	NativeTypeSpec		*(*findPrimitive)(struct PublishSpec *p, str_t name);
	Dz1Error			 (*regHeaderInc)(struct PublishSpec *p, str_t fn);
	Dz1Error			 (*regSourceInc)(struct PublishSpec *p, str_t fn);
} PublishSpec;

PublishSpec				*PublishSpec_new(bool_t				 pthread,
										 PublishBasicSpec	*base,
										 PublishErrorSpec	*error,
										 PublishCastSpec	*cast,
										 PublishMemFuncSpec	*mem,
										 PublishPostFix		*postFix,
										 Dz1Error			*err);
void					 PublishSpec_del(PublishSpec *p);
void					 PublishSpec_dump(PublishSpec *p, int tab);
static __inline__ void	 PublishSpec_delAndSetNull(void *ptr)
{
	PublishSpec **p = (PublishSpec **)ptr;
	PublishSpec_del(*p); *p = NULL;
}
// Publish Spec
///////////////////////////////////////////////////////////////////////////////

#endif
