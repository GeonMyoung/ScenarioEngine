#ifndef DZ1_GASN_SUPPORT_H
#define DZ1_GASN_SUPPORT_H

#include <IO/ASN1_WorkSpace.h>
#include <TYPE/ASN1_Type.h>
#include <TOOL/ASN1_Set.h>
#include <TOOL/ASN1_List.h>
#include <TOOL/ASN1_Print.h>
#include <BER/ASN1_BER_OCTETSTRING.h>
#include <PER/ASN1_PER_OCTETSTRING.h>

#include <BER/ASN1_BER_OBJECTIDENTIFIER.h>
#include <PER/ASN1_PER_OBJECTIDENTIFIER.h>

#include <dz1_asn1.h>
#include <dz1_real.h>
#include <dz1_bin.h>
#include <dz1_timeval.h>
#include <dz1_thread_stdio.h>
#include <dz1_io_stream.h>

///////////////////////////////////////////////////////////////////////////////
// PER Constraint(UNCONS)
DZ1_CPPLINK_VAR Asn1ConsInfo dz1GasnPerNoConstraint;
// PER Constraint(UNCONS)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN1WorkSapce support
DZ1_CPPLINK ASN1WorkSpace	*ASN1WorkSpace_new(int *ret_err_status);
DZ1_CPPLINK void			 ASN1WorkSpace_del(ASN1WorkSpace *p);

static __inline__ void		 ASN1WorkSpace_delAndSetNull(void *pptr)
{
	ASN1WorkSpace **p = (ASN1WorkSpace **)pptr;
	ASN1WorkSpace_del(*p); *p = NULL;
}

static __inline__ void		 ASN1_INIT_WS_INFO_cancel(void *ptr)
{
	ASN1WorkSpace *ws = (ASN1WorkSpace *)ptr;
	if (ws != NULL) ASN1_Destroy_WORKSPACE(ws);
}

DZ1_CPPLINK ASNUINT8		*ASN1WorkSpace_getEncodePtr(ASN1WorkSpace *p);
DZ1_CPPLINK ASNUINT32		 ASN1WorkSpace_getEncodedSize(ASN1WorkSpace *p, Dz1Asn1Codec codec);
// ASN1WorkSapce support
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Codec
#define DZ1_ASN1_CODEC_BIT_BER		0x80
#define DZ1_ASN1_CODEC_BIT_APER		0x40
#define DZ1_ASN1_CODEC_BIT_UPER		0x20
#define DZ1_ASN1_CODEC_BIT_XER		0x10
#define DZ1_ASN1_CODEC_BIT_CXER		0x08

DZ1_CPPLINK u8_t		 Dz1GASN_getSupportedCodec(void);
DZ1_CPPLINK u8_t		 Dz1GASN_codec2Bit(Dz1Asn1Codec codec);
DZ1_CPPLINK Dz1Asn1Codec Dz1GASN_oid2Codec(Dz1Asn1OID *oid);
DZ1_CPPLINK Dz1Asn1OID	*Dz1GASN_codec2OID(Dz1Asn1Codec codec);
// Dz1Asn1Codec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN1List processing arguments
typedef struct Asn1ListProcArg
{
	ASN1WorkSpace	*ws;
	ASN1List		*dst;
} Asn1ListProcArg;
// ASN1List processing arguments
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GasnStructPkg
typedef struct GasnStructPkg
{
	void			*asn;
	ASN1WorkSpace	*storage;
} GasnStructPkg
;
DZ1_CPPLINK GasnStructPkg	   *_GasnStructPkg_gen(Dz1Error *err, char *__file__, int __line__);
DZ1_CPPLINK GasnStructPkg	   *_GasnStructPkg_gen2(Dz1Error *err, char *__file__, int __line__);
DZ1_CPPLINK void				 GasnStructPkg_del(GasnStructPkg *p);
static __inline__ void			 GasnStructPkg_delAndSetNull(void *pptr) { GasnStructPkg **p = (GasnStructPkg **)pptr; if (p != NULL) { GasnStructPkg_del(*p); *p = NULL; } }

#ifndef UNIX_SYSTEM
#define GASN_PKG_ORIGIN_DUMP_DECLARE(asn_name)\
static __inline__	void asn_name##A_dump(asn_name *p, int tab) { ASN1_Print_##asn_name(p, tab); }\
static __inline__	void asn_name##W_dump(asn_name *p, int tab) { ASN1_Print_##asn_name(p, tab); }\
static __inline__	void asn_name##_dump(asn_name *p, int tab) { DZ1_DUMP(asn_name, p, tab); }

#define GASN_PKG_DUMP_DECLARE(asn_name)\
static __inline__ void			 asn_name##PkgA_dump(asn_name##Pkg *p, int tab)						{ if (p == NULL) Dz1ThreadA_printf("[NULL]\n"); else asn_name##A_dump(p->asn, tab); }\
static __inline__ void			 asn_name##PkgW_dump(asn_name##Pkg *p, int tab)						{ if (p == NULL) Dz1ThreadW_printf(L"[NULL]\n"); else asn_name##W_dump(p->asn, tab); }\
static __inline__ void			 asn_name##Pkg_dump(asn_name##Pkg *p, int tab)						{ DZ1_DUMP(asn_name##Pkg, p, tab); }

#define GASN_PKG_API_DECLARE(asn_name)\
static __inline__ asn_name##Pkg *_##asn_name##Pkg_gen(Dz1Error *ep, char *__file__, int __line__)	{ return (asn_name##Pkg *)_GasnStructPkg_gen(ep, __file__, __line__); } \
static __inline__ void			 asn_name##Pkg_del(asn_name##Pkg *p)								{ GasnStructPkg_del((void *)p); }\
static __inline__ void			 asn_name##Pkg_delAndSetNull(void *pptr)							{ GasnStructPkg_delAndSetNull(pptr); }

#define GASN_PKG_DECLARE(asn_name)\
GASN_PKG_ORIGIN_DUMP_DECLARE(asn_name)\
typedef struct asn_name##Pkg\
{\
	asn_name		*asn;\
	ASN1WorkSpace	*storage;\
} asn_name##Pkg;\
GASN_PKG_API_DECLARE(asn_name)\
GASN_PKG_DUMP_DECLARE(asn_name)

#define GASN_PKG_API_DECLARE2(asn_name)\
static __inline__ asn_name##Pkg *_##asn_name##Pkg2_gen(Dz1Error *ep, char *__file__, int __line__)	{ return (asn_name##Pkg *)_GasnStructPkg_gen2(ep, __file__, __line__); } \
static __inline__ void			 asn_name##Pkg_del(asn_name##Pkg *p)								{ GasnStructPkg_del((void *)p); }\
static __inline__ void			 asn_name##Pkg_delAndSetNull(void *pptr)							{ GasnStructPkg_delAndSetNull(pptr); }

#define GASN_PKG_DECLARE2(asn_name)\
GASN_PKG_ORIGIN_DUMP_DECLARE(asn_name)\
typedef struct asn_name##Pkg\
{\
	asn_name		*asn;\
	ASN1WorkSpace	*storage;\
} asn_name##Pkg;\
GASN_PKG_API_DECLARE2(asn_name)\
GASN_PKG_DUMP_DECLARE(asn_name)
#else	// UNIX_SYSTEM
#define GASN_PKG_DECLARE(asn_name)\
static __inline__	void asn_name##_dump(asn_name *p, int tab) { ASN1_Print_##asn_name(p, tab); }\
typedef struct asn_name##Pkg\
{\
	asn_name		*asn;\
	ASN1WorkSpace	*storage;\
} asn_name##Pkg;\
static __inline__ asn_name##Pkg *_##asn_name##Pkg_gen(Dz1Error *ep, char *__file__, int __line__)	{ return (asn_name##Pkg *)_GasnStructPkg_gen(ep, __file__, __line__); } \
static __inline__ void			 asn_name##Pkg_del(asn_name##Pkg *p)								{ GasnStructPkg_del((void *)p); }\
static __inline__ void			 asn_name##Pkg_delAndSetNull(void *pptr)							{ GasnStructPkg_delAndSetNull(pptr); }\
static __inline__ void			 asn_name##Pkg_dump(asn_name##Pkg *p, int tab)						{ if (p == NULL) Dz1ThreadA_printf("[NULL]\n"); else asn_name##_dump(p->asn, tab); }
#endif
// GasnStructPkg
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TDC Support : NEW_FROM_ASN
#define DZ1_DECL_FROM_ASN(typename, asnname)			Dz1Error typename##_fromASN(typename *dst, asnname *src)
#define DZ1_DECL_NEW_FROM_ASN(typename, asnname)		typename *typename##_newFromASN(asnname *src, Dz1Error *err)
#define DZ1_DECL_NEW_FROM_ASN_NAME(typename, asnname)	typename *typename##_newFrom##asnname(asnname *src, Dz1Error *err)

// ASN Type -> TDC Type
#define DZ1_NEW_FROM_ASN(typename, asnname)\
typename *typename##_newFromASN(asnname *src, Dz1Error *err)\
{\
	typename *ret = NULL;\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if ((ret = (typename *)Dz1Calloc(sizeof(typename), 1, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		pthread_cleanup_push(typename##_delAndSetNull, (void *)&ret);\
		if ((*errp = typename##_fromASN(ret, src)).code) ERR_OUT(errp);\
		else Dz1Error_set(errp, 0);\
		pthread_cleanup_pop(errp->code);\
	}\
	return ret;\
}

// Specific ASN Type -> TDC Type
#define DZ1_NEW_FROM_ASN_NAME(typename, asnname)\
typename *typename##_newFrom##asnname(asnname *src, Dz1Error *err)\
{\
	typename *ret = NULL;\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if ((ret = (typename *)Dz1Calloc(sizeof(typename), 1, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		pthread_cleanup_push(typename##_delAndSetNull, (void *)&ret);\
		if ((*errp = typename##_from##asnname(ret, src)).code) ERR_OUT(errp);\
		else Dz1Error_set(errp, 0);\
		pthread_cleanup_pop(errp->code);\
	}\
	return ret;\
}

// ASN1 List Type -> TDC List Type
#define DZ1_NEW_LIST_FROM_ASN(typename, asnname)\
typename *typename##_newFromASN(asnname *src, Dz1Error *err)\
{\
	typename *ret = NULL;\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if ((ret = typename##_new(errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		pthread_cleanup_push(typename##_delAndSetNull, (void *)&ret);\
		if ((*errp = typename##_fromASN(ret, src)).code) ERR_OUT(errp);\
		else Dz1Error_set(errp, 0);\
		pthread_cleanup_pop(errp->code);\
	}\
	return ret;\
}

// ASN1 List Elements(ptr) -> TDC List Elements(ptr)
#define PSEUDO_LIST_FROM_ASN(Dz1ListType, Dz1EntryType, ASN1EntryType)\
Dz1Error Dz1ListType##_fromASN(Dz1ListType *dst, ASN1List *src)\
{\
	DZ1_ERROR_SAFE_VAR(errp, err);\
	ASN1WorkSpace ws;\
	ASN1_INIT_WS_INFO(&ws);\
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);\
	else\
	{\
		ASN1EntryType *v;\
		/*ASN1ListNode *i = NULL;*/\
		Dz1EntryType *node = NULL;\
		/*for (i = ASN1List_getFirst(src); err.code == 0 && i != NULL; i = ASN1List_getNext(src))*/\
		for (v = (ASN1EntryType *)ASN1List_getFirst(src); err.code == 0 && v != NULL; v = (ASN1EntryType *)ASN1List_getNext(src))\
		{\
			/*if ((node = Dz1EntryType##_newFromASN((ASN1EntryType *)i->data, &err)) == NULL) ERR_OUT(&err);*/\
			if ((node = Dz1EntryType##_newFromASN(v, &err)) == NULL) ERR_OUT(&err);\
			else\
			{\
				pthread_cleanup_push(Dz1EntryType##_delAndSetNull, (void *)&node);\
				if ((err = dst->add(dst, node)).code) ERR_OUT(&err);\
				else { node = NULL; Dz1Error_set(errp, 0); }\
				pthread_cleanup_pop(1);\
			}\
		}\
	}\
	pthread_cleanup_pop(1);\
	return err;\
}

// ASN1 List Elements(value) -> TDC List Elements(value)
#define PSEUDO_S_LIST_FROM_ASN(Dz1ListType, Dz1EntryType, ASN1EntryType)\
Dz1Error Dz1ListType##_fromASN(Dz1ListType *dst, ASN1List *src)\
{\
	DZ1_ERROR_SAFE_VAR(errp, err);\
	ASN1WorkSpace ws;\
	ASN1_INIT_WS_INFO(&ws);\
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);\
	else\
	{\
		ASN1EntryType *v;\
		Dz1EntryType node;\
		/*ASN1ListNode *i = NULL;*/\
		memset(&node, 0, sizeof(Dz1EntryType));\
		/*for (i = ASN1List_getFirst(src); err.code == 0 && i != NULL; i = ASN1List_getNext(src))*/\
		for (v = (ASN1EntryType *)ASN1List_getFirst(src); err.code == 0 && v != NULL; v = (ASN1EntryType *)ASN1List_getNext(src))\
		{\
			/*if ((err = Dz1EntryType##_fromASN(&node, (ASN1EntryType *)i->data)).code) ERR_OUT(&err);*/\
			if ((err = Dz1EntryType##_fromASN(&node, v)).code) ERR_OUT(&err);\
			else if ((err = dst->add(dst, node)).code) ERR_OUT(&err);\
			else Dz1Error_set(errp, 0);\
		}\
	}\
	pthread_cleanup_pop(1);\
	return err;\
}
// TDC Support : NEW_FROM_ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TDC Support : NEW_TO_ASN
#define DZ1_DECL_TO_ASN(typename, asnname)				Dz1Error typename##_toASN(asnname *dst, typename *src, ASN1WorkSpace *ws)
#define DZ1_DECL_TO_NEW_ASN(typename, asnname)			asnname *typename##_toNewASN(typename *src, ASN1WorkSpace *ws, Dz1Error *err)
#define DZ1_DECL_TO_NEW_ASN_NAME(typename, asnname)		asnname *typename##_toNew##asnname(typename *src, ASN1WorkSpace *ws, Dz1Error *err)

// TDC Type -> ASN1 Type
#define DZ1_TO_NEW_ASN(typename, asnname)\
asnname *typename##_toNewASN(typename *src, ASN1WorkSpace *ws, Dz1Error *err)\
{\
	asnname *ret = NULL;\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	if (ws == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if ((ret = (asnname *)mpool_calloc(ws->Pmemory, sizeof(asnname), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);\
	else if ((*errp = typename##_toASN(ret, src, ws)).code) ERR_OUT(errp);\
	else Dz1Error_set(errp, 0);\
	return ret;\
}

// TDC Type -> Specific ASN1 Type
#define DZ1_TO_NEW_ASN_NAME(typename, asnname)\
asnname *typename##_toNew##asnname(typename *src, ASN1WorkSpace *ws, Dz1Error *err)\
{\
	asnname *ret = NULL;\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	if (ws == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if ((ret = (asnname *)mpool_calloc(ws->Pmemory, sizeof(asnname), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);\
	else if ((*errp = typename##_to##asnname(ret, src, ws)).code) ERR_OUT(errp);\
	else Dz1Error_set(errp, 0);\
	return ret;\
}

// TDC List Type -> ASN1 List Type
#define DZ1_TO_NEW_ASN_LIST(typename, asnname)\
asnname *typename##_toNewASN(typename *src, ASN1WorkSpace *ws, Dz1Error *err)\
{\
	asnname *ret = NULL;\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	if (ws == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if ((ret = (asnname *)mpool_calloc(ws->Pmemory, sizeof(asnname), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);\
	else\
	{\
		ASN1List_init(ws, ret);\
		if ((*errp = typename##_toASN(ret, src, ws)).code) ERR_OUT(errp);\
	}\
	return ret;\
}

// (TDC List Element -> ASN1 List Element) -> Append
#define PSEUDO_ENTRY_TO_ASN(Dz1ListType, Dz1EntryType, ASN1EntryType) \
Dz1Error _##Dz1ListType##_toASN(void *ptr, Dz1EntryType *p)\
{\
	DZ1_ERROR_SAFE_VAR(errp, err);\
	Asn1ListProcArg *arg = (Asn1ListProcArg *)ptr;\
	ASN1EntryType *v = Dz1EntryType##_toNewASN(p, arg->ws, &err);\
	if (v == NULL) ERR_SET_OUT(&err, EFAULT);\
	else if (ASN1List_insert(arg->ws, arg->dst, v) < 0) ERR_SET_OUT(&err, EFAULT);\
	else Dz1Error_set(errp, 0);\
	return err;\
}

// TDC List Elements -> ASN1 List Elements
#define PSEUDO_LIST_TO_ASN(Dz1ListType)\
Dz1Error Dz1ListType##_toASN(ASN1List *dst, Dz1ListType *src, ASN1WorkSpace *ws)\
{\
	Dz1Error err = DZ1_ERROR_INITIALIZER;\
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);\
	else\
	{\
		Asn1ListProcArg arg = { ws, dst };\
		if (ASN1List_init(ws, dst) < 0) ERR_SET_OUT(&err, EFAULT);\
		else if ((err = src->travel(src, _##Dz1ListType##_toASN, (void *)&arg)).code) ERR_OUT(&err);\
	}\
	return err;\
}
// TDC Support : GEN_TO_ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TDC Support : Decoder
#define DECODE_FUNC_IMPL(typename) \
ssize_t typename##_decode(typename **dst, u8_t *src, size_t size, Dz1Asn1Codec codec, Dz1Error *err)\
{\
	ssize_t ret = -1;\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	switch(codec)\
	{\
	case Dz1Asn1Codec_ber:\
		if ((ret = typename##_decodeBer(dst, src, size, errp)) < 0) ERR_OUT(errp);\
		break;\
	case Dz1Asn1Codec_aper:\
		ERR_SET_OUT(errp, ENOSYS);\
		break;\
	case Dz1Asn1Codec_uper:\
		if ((ret = typename##_decodeUPer(dst, src, size, errp)) < 0) ERR_OUT(errp);\
		break;\
	case Dz1Asn1Codec_xer:\
	case Dz1Asn1Codec_cxer:\
	case Dz1Asn1Codec_unknown:\
	default:\
		ERR_SET_OUT(errp, ENOSYS);\
		break;\
	}\
	return ret;\
}
#define DECODE_FUNC_DECL(typename) ssize_t typename##_decode(typename **dst, u8_t *src, size_t size, Dz1Asn1Codec codec, Dz1Error *err)
// TDC Support : Decoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TDC Support : BER Decoder
#define DECODE_BER_FUNC_IMPL_NODUMP(typename, asnname)\
ssize_t typename##_decodeBer(typename **dst, u8_t *buf, size_t size, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err)\
	ssize_t ret = -1;\
	if (dst == NULL || buf == NULL) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_decodeBer : Argument(dst:%p, buf:%p) -> ", dst, buf); ERR_SET_OUT(errp, EINVAL); }\
	else\
	{\
		asnname msg;\
 		ASN1WorkSpace ws;\
 		ASN1_INIT_WS_INFO(&ws);\
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\
		ASN1_Save_WORKSPACE(&ws, buf, (ASNINT32)size);\
		ws.dataSize = (ASNINT32)size;\
		memset(&msg, 0, sizeof(asnname));\
		if ((ASN1_BER_Dec_##asnname(&ws, &msg, (int)size, ASN1EXPL)) < 0) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "ASN1_BER_Dec_" #asnname " -> "); ERR_SET_OUT(errp, EFAULT);}\
 		else if (((*dst) = typename##_newFromASN(&msg, errp)) == NULL) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_newFromASN -> "); ERR_SET_OUT(errp, EFAULT); }\
		else { ret = (ssize_t)(ws.buffer.current - ws.buffer.data); Dz1Error_set(errp, 0); }\
		pthread_cleanup_pop(1);\
	}\
	return ret;\
}

#define DECODE_BER_FUNC_IMPL(typename, asnname)\
ssize_t typename##_decodeBer(typename **dst, u8_t *buf, size_t size, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err)\
	ssize_t ret = -1;\
	if (dst == NULL || buf == NULL) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_decodeBer : Argument(dst:%p, buf:%p) -> ", dst, buf); ERR_SET_OUT(errp, EINVAL); }\
	else\
	{\
		asnname msg;\
 		ASN1WorkSpace ws;\
 		ASN1_INIT_WS_INFO(&ws);\
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\
		ASN1_Save_WORKSPACE(&ws, buf, (ASNINT32)size);\
		ws.dataSize = (ASNINT32)size;\
		memset(&msg, 0, sizeof(asnname));\
		if ((ASN1_BER_Dec_##asnname(&ws, &msg, (int)size, ASN1EXPL)) < 0) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "ASN1_BER_Dec_" #asnname " -> "); ERR_SET_OUT(errp, EFAULT);}\
 		else if (((*dst) = typename##_newFromASN(&msg, errp)) == NULL) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_newFromASN -> "); ERR_SET_OUT(errp, EFAULT); }\
		else { ret = (ssize_t)(ws.buffer.current - ws.buffer.data); Dz1Error_set(errp, 0); }\
		pthread_cleanup_pop(1);\
	}\
	return ret;\
}
// TDC Support : BER Decoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TDC Support : UPER Decoder
#define DECODE_UPER_FUNC_IMPL_NODUMP(typename, asnname)\
ssize_t typename##_decodeUPer(typename **dst, u8_t *buf, size_t size, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err)\
	ssize_t ret = -1;\
	if (dst == NULL || buf == NULL) ERR_SET_OUT(errp, EINVAL);\
	else\
	{\
		asnname msg;\
 		ASN1WorkSpace ws;\
 		ASN1_INIT_WS_INFO(&ws);\
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\
		ASN1_Save_WORKSPACE(&ws, buf, (ASNINT32)size);\
		ws.dataSize = (ASNINT32)size;\
		memset(&msg, 0, sizeof(asnname));\
		if ((ASN1_PER_UNAlign_Dec_##asnname(&ws, &msg)) < 0) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "ASN1_PER_UNAlign_Dec_" #asnname " -> "); ERR_SET_OUT(errp, EFAULT);}\
 		else if (((*dst) = typename##_newFromASN(&msg, errp)) == NULL) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_newFromASN -> "); ERR_SET_OUT(errp, EFAULT); }\
		else { ret = (ssize_t)(ws.buffer.current - ws.buffer.data + (ws.buffer.bitOffset != 8 ? 1 : 0)); Dz1Error_set(errp, 0); }\
		pthread_cleanup_pop(1);\
	}\
	return ret;\
}

#define DECODE_UPER_FUNC_IMPL(typename, asnname)\
ssize_t typename##_decodeUPer(typename **dst, u8_t *buf, size_t size, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err)\
	ssize_t ret = -1;\
	if (dst == NULL || buf == NULL) ERR_SET_OUT(errp, EINVAL);\
	else\
	{\
		asnname msg;\
 		ASN1WorkSpace ws;\
 		ASN1_INIT_WS_INFO(&ws);\
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\
		ASN1_Save_WORKSPACE(&ws, buf, (ASNINT32)size);\
		ws.dataSize = (ASNINT32)size;\
		memset(&msg, 0, sizeof(asnname));\
		if ((ASN1_PER_UNAlign_Dec_##asnname(&ws, &msg)) < 0) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "ASN1_PER_UNAlign_Dec_" #asnname " -> "); ERR_SET_OUT(errp, EFAULT);}\
 		else if (((*dst) = typename##_newFromASN(&msg, errp)) == NULL) { Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_newFromASN -> "); ERR_SET_OUT(errp, EFAULT); }\
		else { ret = (ssize_t)(ws.buffer.current - ws.buffer.data + (ws.buffer.bitOffset != 8 ? 1 : 0)); Dz1Error_set(errp, 0); }\
		pthread_cleanup_pop(1);\
	}\
	return ret;\
}
// TDC Support : UPER Decoder
///////////////////////////////////////////////////////////////////////////////

#define STATIC_DECODE_EACH_FUNC_IMPL(typename, asnname)\
static DECODE_BER_FUNC_IMPL(typename, asnname)\
static DECODE_UPER_FUNC_IMPL(typename, asnname)

#define STATIC_DECODE_ND_EACH_FUNC_IMPL(typename, asnname)\
static DECODE_BER_FUNC_IMPL_NODUMP(typename, asnname)\
static DECODE_UPER_FUNC_IMPL_NODUMP(typename, asnname)

///////////////////////////////////////////////////////////////////////////////
// TDC Support : Encoder
#define ENCODE_FUNC_IMPL_NODUMP(typename, asnname) \
ssize_t typename##_encode(typename *src, u8_t **dst, Dz1Asn1Codec codec, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	ssize_t ret = -1;\
	asnname *_msg = NULL;\
	ASN1WorkSpace ws;\
	ASN1_INIT_WS_INFO(&ws);\
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\
	if ((_msg = typename##_toNewASN(src, &ws, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		switch(codec)\
		{\
		case Dz1Asn1Codec_ber:\
			if ((ret = typename##_encodeBer(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);\
			break;\
		case Dz1Asn1Codec_aper:\
			ERR_SET_OUT(errp, ENOSYS);\
			break;\
		case Dz1Asn1Codec_uper:\
			if ((ret = typename##_encodeUPer(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);\
			break;\
		case Dz1Asn1Codec_xer:\
		case Dz1Asn1Codec_cxer:\
		case Dz1Asn1Codec_unknown:\
		default:\
			ERR_SET_OUT(errp, ENOSYS);\
			break;\
		}\
	}\
	pthread_cleanup_pop(1);\
	return ret;\
}

#define ENCODE_FUNC_IMPL(typename, asnname) \
ssize_t typename##_encode(typename *src, u8_t **dst, Dz1Asn1Codec codec, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	ssize_t ret = -1;\
	asnname *_msg = NULL;\
	ASN1WorkSpace ws;\
	ASN1_INIT_WS_INFO(&ws);\
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\
	if ((_msg = typename##_toNewASN(src, &ws, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		switch(codec)\
		{\
		case Dz1Asn1Codec_ber:\
			if ((ret = typename##_encodeBer(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);\
			break;\
		case Dz1Asn1Codec_aper:\
			ERR_SET_OUT(errp, ENOSYS);\
			break;\
		case Dz1Asn1Codec_uper:\
			if ((ret = typename##_encodeUPer(_msg, dst, &ws, errp)) < 0) ERR_OUT(errp);\
			break;\
		case Dz1Asn1Codec_xer:\
		case Dz1Asn1Codec_cxer:\
		case Dz1Asn1Codec_unknown:\
		default:\
			ERR_SET_OUT(errp, ENOSYS);\
			break;\
		}\
	}\
	pthread_cleanup_pop(1);\
	return ret;\
}
#define ENCODE_FUNC_DECL(typename) ssize_t typename##_encode(typename *src, u8_t **dst, Dz1Asn1Codec codec, Dz1Error *err)
// TDC Support : Encoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TDC Support : BER Encoder
#define ENCODE_BER_FUNC_IMPL_NODUMP(typename, asnname)\
ssize_t typename##_encodeBer(asnname *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	ssize_t ret = 0;\
	if (src == NULL || dst == NULL || *dst != NULL || ws == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }\
	else if ((ASN1_BER_Enc_##asnname(ws, src, ASN1EXPL)) < 0)	{ Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "ASN1_BER_Enc_" #asnname"()->"); ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else if (IndefinelenTodefinelen(ws) < 0)					{ Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_encodeBer(length calculate) ->"); ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else if ((ret = GetDataLength(ws)) < 0)						{ Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_encodeBer(retrieve length) ->"); ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else if (((*dst) = (u8_t *)Dz1Malloc(ret, errp)) == NULL)	{ Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_encodeBer(allocation) ->"); ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else\
	{\
		memcpy((*dst), ws->buffer.data, ret);\
		Dz1Error_set(errp, 0);\
	}\
	return ret;\
}

#define ENCODE_BER_FUNC_IMPL(typename, asnname)\
ssize_t typename##_encodeBer(asnname *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	ssize_t ret = 0;\
	if (src == NULL || dst == NULL || *dst != NULL || ws == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }\
	else if ((ASN1_BER_Enc_##asnname(ws, src, ASN1EXPL)) < 0)	{ Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "ASN1_BER_Enc_" #asnname"()->"); ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else if (IndefinelenTodefinelen(ws) < 0)					{ Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_encodeBer(length calculate) ->"); ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else if ((ret = GetDataLength(ws)) < 0)						{ Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_encodeBer(retrieve length) ->"); ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else if (((*dst) = (u8_t *)Dz1Malloc(ret, errp)) == NULL)	{ Dz1Thread_log(DZ1_THREAD_LOG_ERROR, #typename "_encodeBer(allocation) ->"); ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else\
	{\
		memcpy((*dst), ws->buffer.data, ret);\
		Dz1Error_set(errp, 0);\
	}\
	return ret;\
}
// TDC Support : BER Encoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TDC Support : UPER Encoder
#define ENCODE_UPER_FUNC_IMPL_NODUMP(typename, asnname)\
ssize_t typename##_encodeUPer(asnname *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	ssize_t ret = 0;\
	if ((ASN1_PER_UNAlign_Enc_##asnname(ws, src)) < 0) { ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else\
	{\
		ret = (ssize_t)(ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0))\
		if (((*dst) = (u8_t *)Dz1Malloc(ret, errp)) == NULL) { ERR_SET_OUT(errp, EFAULT); ret = -1; }\
		else\
		{\
			memcpy((*dst), ws->buffer.data, ret);\
			Dz1Error_set(errp, 0);\
		}\
	}\
	return ret;\
}

#define ENCODE_UPER_FUNC_IMPL(typename, asnname)\
ssize_t typename##_encodeUPer(asnname *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_DECLARE(errp, err);\
	ssize_t ret = 0;\
	if ((ASN1_PER_UNAlign_Enc_##asnname(ws, src)) < 0) { ERR_SET_OUT(errp, EFAULT); ret = -1; }\
	else\
	{\
		ret = (ssize_t)(ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0));\
		if (((*dst) = (u8_t *)Dz1Malloc(ret, errp)) == NULL) { ERR_SET_OUT(errp, EFAULT); ret = -1; }\
		else\
		{\
			memcpy((*dst), ws->buffer.data, ret);\
			Dz1Error_set(errp, 0);\
		}\
	}\
	return ret;\
}
// TDC Support : UPER Encoder
///////////////////////////////////////////////////////////////////////////////

#define STATIC_ENCODE_EACH_FUNC_IMPL(typename, asnname)\
static ENCODE_BER_FUNC_IMPL(typename, asnname)\
static ENCODE_UPER_FUNC_IMPL(typename, asnname)

///////////////////////////////////////////////////////////////////////////////
// from ASN Error Condition macro
#define PREPARE_FROM_ASN_ENUM(asn1srcp, asn1src_member) int asn1src_member = (int)(asn1srcp)->asn1src_member

// OPTIONAL dstPtr = newFromASN(&srcVal)
#define COND_OPTIONAL_FROM_ASN(asn1type, dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src_member, errp)\
	(asn1srcp)->DEF_##asn1type##_##asn1src_member && ( (dz1dstp)->dz1dst_member = dz1type_member##_newFromASN(&(asn1srcp)->asn1src_member, (errp))) == NULL
#define COND_OPTIONAL_FROM_ASN_NAME(asn1type, dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src, asn1src_member, errp)\
	(asn1srcp)->DEF_##asn1type##_##asn1src_member && ( (dz1dstp)->dz1dst_member = dz1type_member##_newFrom##asn1src(&(asn1srcp)->asn1src_member, (errp))) == NULL
#define _COND_OPTIONAL_FROM_ASN(asn1type, dz1type_member, dz1dstp, asn1srcp, same_member, errp)\
	COND_OPTIONAL_FROM_ASN(asn1type, dz1type_member, dz1dstp, asn1srcp, same_member, same_member, errp)
#define _COND_OPTIONAL_FROM_ASN_NAME(asn1type, dz1type_member, dz1dstp, asn1srcp, asn1src, same_member, errp)\
	COND_OPTIONAL_FROM_ASN_NAME(asn1type, dz1type_member, dz1dstp, asn1srcp, same_member, asn1src, same_member, errp)

// OPTIONAL dstPtr = newFromASN(srcPtr)
#define COND_OPTIONAL_FROM_ASN_PTR(asn1type, dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src_member, errp)\
	(asn1srcp)->DEF_##asn1type##_##asn1src_member && ( (dz1dstp)->dz1dst_member = dz1type_member##_newFromASN((asn1srcp)->asn1src_member, (errp))) == NULL
#define _COND_OPTIONAL_FROM_ASN_PTR(asn1type, dz1type_member, dz1dstp, asn1srcp, same_member, errp)\
	COND_OPTIONAL_FROM_ASN_PTR(asn1type, dz1type_member, dz1dstp, asn1srcp, same_member, same_member, errp)

// OPTIONAL dstEnumPtr = newFromASN(&srcEnumVal)
#define COND_OPTIONAL_FROM_ASN_ENUM(asn1type, dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src_member, errp)\
	(asn1srcp)->DEF_##asn1type##_##asn1src_member && ( (dz1dstp)->dz1dst_member = dz1type_member##_newFromASN(&asn1src_member, (errp))) == NULL
#define _COND_OPTIONAL_FROM_ASN_ENUM(asn1type, dz1type_member, dz1dstp, asn1srcp, same_member, errp)\
	COND_OPTIONAL_FROM_ASN_ENUM(asn1type, dz1type_member, dz1dstp, asn1srcp, same_member, same_member, errp)

// dstPtr = newFromASN(&srcVal)
#define COND_NEW_FROM_ASN(dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src_member, errp)\
	((dz1dstp)->dz1dst_member = dz1type_member##_newFromASN(&(asn1srcp)->asn1src_member, (errp))) == NULL
#define COND_NEW_FROM_ASN_NAME(dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src, asn1src_member, errp)\
	((dz1dstp)->dz1dst_member = dz1type_member##_newFrom##asn1src(&(asn1srcp)->asn1src_member, (errp))) == NULL
#define _COND_NEW_FROM_ASN(dz1type_member, dz1dstp, asn1srcp, same_member, errp) \
	COND_NEW_FROM_ASN(dz1type_member, dz1dstp, asn1srcp, same_member, same_member, errp)
#define _COND_NEW_FROM_ASN_NAME(dz1type_member, dz1dstp, asn1srcp, asn1src, same_member, errp) \
	COND_NEW_FROM_ASN_NAME(dz1type_member, dz1dstp, asn1srcp, same_member, asn1src, same_member, errp)

// dstPtr = newFromASN(srcPtr)
#define COND_NEW_FROM_ASN_PTR(dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src_member, errp)\
	((dz1dstp)->dz1dst_member = dz1type_member##_newFromASN((asn1srcp)->asn1src_member, (errp))) == NULL
#define _COND_NEW_FROM_ASN_PTR(dz1type_member, dz1dstp, asn1srcp, same_member, errp)\
	COND_NEW_FROM_ASN_PTR(dz1type_member, dz1dstp, asn1srcp, same_member, same_member, errp)

// fromASN(&dstVal, &srcVal)
#define COND_FROM_ASN(dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src_member, errp)\
	( *(errp) = dz1type_member##_fromASN(&(dz1dstp)->dz1dst_member, &(asn1srcp)->asn1src_member)).code
#define _COND_FROM_ASN(dz1type_member, dz1dstp, asn1srcp, same_member, errp)\
	COND_FROM_ASN(dz1type_member, dz1dstp, asn1srcp, same_member, same_member, errp)

// fromASN(&dstVal, srcPtr)
#define COND_FROM_ASN_PTR(dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src_member, errp)\
	( *(errp) = dz1type_member##_fromASN(&(dz1dstp)->dz1dst_member, (asn1srcp)->asn1src_member)).code

// fromASN(&dstEnumVal, &srcEnumVal)
#define COND_FROM_ASN_ENUM(dz1type_member, dz1dstp, asn1srcp, dz1dst_member, asn1src_member, errp)\
	( *(errp) = dz1type_member##_fromASN(&(dz1dstp)->dz1dst_member, &asn1src_member)).code
#define _COND_FROM_ASN_ENUM(dz1type_member, dz1dstp, asn1srcp, same_member, errp)\
	COND_FROM_ASN_ENUM(dz1type_member, dz1dstp, asn1srcp, same_member, same_member, errp)
// from ASN Error Condition macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// to ASN Error Condition macro
#define PREDEF_TO_ASN_ENUM(asn1dstp, asn1dst_member) int asn1dst_member = 0
#define APPLY_TO_ASN_ENUM(asn1dstp, asn1dst_member)	(asn1dstp)->asn1dst_member = asn1dst_member

// OPTIONAL toASN(&dstVal, srcPtr)
#define COND_OPTIONAL_TO_ASN(asn1type, dz1type_member, asn1dstp, dz1srcp, asn1dst_member, dz1src_member, wsp, errp)\
	((asn1dstp)->DEF_##asn1type##_##asn1dst_member = (dz1srcp)->dz1src_member ? 1 : 0) && \
	(*(errp) = dz1type_member##_toASN(&(asn1dstp)->asn1dst_member, (dz1srcp)->dz1src_member, (wsp))).code
#define COND_OPTIONAL_TO_ASN_NAME(asn1type, dz1type_member, asn1dstp, dz1srcp, asn1dst, asn1dst_member, dz1src_member, wsp, errp)\
	((asn1dstp)->DEF_##asn1type##_##asn1dst_member = (dz1srcp)->dz1src_member ? 1 : 0) && \
	(*(errp) = dz1type_member##_to##asn1dst(&(asn1dstp)->asn1dst_member, (dz1srcp)->dz1src_member, (wsp))).code
#define _COND_OPTIONAL_TO_ASN(asn1type, dz1type_member, asn1dstp, dz1srcp, same_member, wsp, errp)\
	COND_OPTIONAL_TO_ASN(asn1type, dz1type_member, asn1dstp, dz1srcp, same_member, same_member, wsp, errp)
#define _COND_OPTIONAL_TO_ASN_NAME(asn1type, dz1type_member, asn1dstp, dz1srcp, asn1dst, same_member, wsp, errp)\
	COND_OPTIONAL_TO_ASN_NAME(asn1type, dz1type_member, asn1dstp, dz1srcp, asn1dst, same_member, same_member, wsp, errp)

// OPTIONAL toASN(dstPtr, srcPtr)
#define COND_OPTIONAL_TO_ASN_PTR(asn1type, dz1type_member, asn1dstp, dz1srcp, asn1dst_member, dz1src_member, wsp, errp)\
	((asn1dstp)->DEF_##asn1type##_##asn1dst_member = (dz1srcp)->dz1src_member ? 1 : 0) && \
	((asn1dstp)->asn1dst_member = dz1type_member##_toNewASN((dz1srcp)->dz1src_member, (wsp), (errp))) == NULL
#define _COND_OPTIONAL_TO_ASN_PTR(asn1type, dz1type_member, asn1dstp, dz1srcp, same_member, wsp, errp)\
	COND_OPTIONAL_TO_ASN_PTR(asn1type, dz1type_member, asn1dstp, dz1srcp, same_member, same_member, wsp, errp)

// OPTIONAL toASN(&dstEnumVal, srcEnumPtr)
#define COND_OPTIONAL_TO_ASN_ENUM(asn1type, dz1type_member, asn1dstp, dz1srcp, asn1dst_member, dz1src_member, wsp, errp)\
	((asn1dstp)->DEF_##asn1type##_##asn1dst_member = (dz1srcp)->dz1src_member ? 1 : 0) && \
	(*(errp) = dz1type_member##_toASN(&asn1dst_member, (dz1srcp)->dz1src_member, (wsp))).code
#define _COND_OPTIONAL_TO_ASN_ENUM(asn1type, dz1type_member, asn1dstp, dz1srcp, same_member, wsp, errp)\
	COND_OPTIONAL_TO_ASN_ENUM(asn1type, dz1type_member, asn1dstp, dz1srcp, same_member, same_member, wsp, errp)

// toASN(&dstVal, &srcVal)
#define COND_VAL_TO_ASN(dz1type_member, asn1dstp, dz1srcp, asn1dst_member, dz1src_member, wsp, errp)\
	(*(errp) = dz1type_member##_toASN(&(asn1dstp)->asn1dst_member, &(dz1srcp)->dz1src_member, (wsp))).code
#define _COND_VAL_TO_ASN(dz1type_member, asn1dstp, dz1srcp, same_member, wsp, errp)\
	COND_VAL_TO_ASN(dz1type_member, asn1dstp, dz1srcp, same_member, same_member, wsp, errp)

// toASN(&dstVal, srcPtr)
#define COND_PTR_TO_ASN(dz1type_member, asn1dstp, dz1srcp, asn1dst_member, dz1src_member, wsp, errp)\
	(*(errp) = dz1type_member##_toASN(&(asn1dstp)->asn1dst_member, (dz1srcp)->dz1src_member, (wsp))).code
#define COND_PTR_TO_ASN_NAME(dz1type_member, asn1dstp, dz1srcp, asn1dst, asn1dst_member, dz1src_member, wsp, errp)\
	(*(errp) = dz1type_member##_to##asn1dst(&(asn1dstp)->asn1dst_member, (dz1srcp)->dz1src_member, (wsp))).code
#define _COND_PTR_TO_ASN(dz1type_member, asn1dstp, dz1srcp, same_member, wsp, errp)\
	COND_PTR_TO_ASN(dz1type_member, asn1dstp, dz1srcp, same_member, same_member, wsp, errp)
#define _COND_PTR_TO_ASN_NAME(dz1type_member, asn1dstp, dz1srcp, asn1dst, same_member, wsp, errp)\
	COND_PTR_TO_ASN_NAME(dz1type_member, asn1dstp, dz1srcp, asn1dst, same_member, same_member, wsp, errp)

// dstPtr = toNewASN(&srcVal)
#define COND_VAL_TO_NEW_ASN(dz1type_member, asn1dstp, dz1srcp, asn1dst_member, dz1src_member, wsp, errp)\
	((asn1dstp)->asn1dst_member = dz1type_member##_toNewASN(&(dz1srcp)->dz1src_member, (wsp), (errp))) == NULL

// dstPtr = toNewASN(srcPtr)
#define COND_PTR_TO_NEW_ASN(dz1type_member, asn1dstp, dz1srcp, asn1dst_member, dz1src_member, wsp, errp)\
	((asn1dstp)->asn1dst_member = dz1type_member##_toNewASN((dz1srcp)->dz1src_member, (wsp), (errp))) == NULL
#define _COND_PTR_TO_NEW_ASN(dz1type_member, asn1dstp, dz1srcp, same_member, wsp, errp)\
	COND_PTR_TO_NEW_ASN(dz1type_member, asn1dstp, dz1srcp, same_member, same_member, wsp, errp)

// toASN(&dstEnumVal, &srcEnumVal)
#define COND_TO_ASN_ENUM(dz1type_member, asn1dstp, dz1srcp, asn1dst_member, dz1src_member, wsp, errp)\
	(*(errp) = dz1type_member##_toASN(&asn1dst_member, &(dz1srcp)->dz1src_member, (wsp))).code
#define _COND_TO_ASN_ENUM(dz1type_member, asn1dstp, dz1srcp, same_member, wsp, errp)\
	COND_TO_ASN_ENUM(dz1type_member, asn1dstp, dz1srcp, same_member, same_member, wsp, errp)
// to ASN Error Condition macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Support APIs : String
DZ1_CPPLINK Dz1Error Dz1Asn1OctetStr_fromASN(Dz1Asn1OctetStr *dst, OCTETSTRING *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(Dz1Asn1OctetStr, OCTETSTRING);

DZ1_CPPLINK Dz1Error Dz1Asn1OctetStr_toASN(OCTETSTRING *dst, Dz1Asn1OctetStr *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(Dz1Asn1OctetStr, OCTETSTRING);

DZ1_CPPLINK Dz1Error Dz1Asn1VisibleStr_fromASN(Dz1Asn1VisibleStr *dst, VisibleString *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(Dz1Asn1VisibleStr, VisibleString);

DZ1_CPPLINK Dz1Error Dz1Asn1VisibleStr_toASN(VisibleString *dst, Dz1Asn1VisibleStr *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(Dz1Asn1VisibleStr, VisibleString);

DZ1_CPPLINK Dz1Error Dz1Asn1BitStr_fromASN(Dz1Asn1BitStr *dst, BITSTRING *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(Dz1Asn1BitStr, BITSTRING);

DZ1_CPPLINK Dz1Error Dz1Asn1BitStr_toASN(BITSTRING *dst, Dz1Asn1BitStr *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(Dz1Asn1BitStr, BITSTRING);

DZ1_CPPLINK str_t str_t_newFromVisibleString(VisibleString *src, Dz1Error *err);
DZ1_CPPLINK Dz1Error str_t_toVisibleString(VisibleString *dst, str_t src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN_NAME(str_t, VisibleString);

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
DZ1_CPPLINK Dz1Error Dz1Asn1UTF8Str_fromASN(Dz1Asn1UTF8Str *dst, UTF8Str *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(Dz1Asn1UTF8Str, UTF8Str);

DZ1_CPPLINK Dz1Error Dz1Asn1UTF8Str_toASN(UTF8Str *dst, Dz1Asn1UTF8Str *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(Dz1Asn1UTF8Str, UTF8Str);
#else
DZ1_CPPLINK Dz1Error Dz1Asn1UTF8Str_fromASN(Dz1Asn1UTF8Str *dst, UTF8String *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(Dz1Asn1UTF8Str, UTF8String);

DZ1_CPPLINK Dz1Error Dz1Asn1UTF8Str_toASN(UTF8String *dst, Dz1Asn1UTF8Str *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(Dz1Asn1UTF8Str, UTF8String);
#endif

DZ1_CPPLINK Dz1Error Dz1Asn1UniversalStr_fromASN(Dz1Asn1UniversalStr *dst, UniversalString *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(Dz1Asn1UniversalStr, UniversalString);

DZ1_CPPLINK Dz1Error Dz1Asn1UniversalStr_toASN(UniversalString *dst, Dz1Asn1UniversalStr *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(Dz1Asn1UniversalStr, UniversalString);
// Support APIs : String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Support APIs : OBJECTIDENTIFIER
DZ1_CPPLINK Dz1Error Dz1Asn1OID_fromASN(Dz1Asn1OID *dst, OBJECTIDENTIFIER *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(Dz1Asn1OID, OBJECTIDENTIFIER);

DZ1_CPPLINK Dz1Error Dz1Asn1OID_toASN(OBJECTIDENTIFIER *dst, Dz1Asn1OID *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(Dz1Asn1OID, OBJECTIDENTIFIER);
// Support APIs : OBJECTIDENTIFIER
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Support APIs : BOOLEAN
DZ1_CPPLINK Dz1Error bool_t_fromASN(bool_t *dst, BOOLEAN *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(bool_t, BOOLEAN);

DZ1_CPPLINK Dz1Error bool_t_toASN(BOOLEAN *dst, bool_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(bool_t, BOOLEAN);
// Support APIs : BOOLEAN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Support APIs : INTEGER - 64bit
DZ1_CPPLINK Dz1Error u64_t_fromASN(u64_t *dst, INTEGER *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(u64_t, INTEGER);

DZ1_CPPLINK Dz1Error u64_t_toASN(INTEGER *dst, u64_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(u64_t, INTEGER);

DZ1_CPPLINK Dz1Error s64_t_fromASN(s64_t *dst, INTEGER *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(s64_t, INTEGER);

DZ1_CPPLINK Dz1Error s64_t_toASN(INTEGER *dst, s64_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(s64_t, INTEGER);
// Support APIs : INTEGER - 64bit
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Support APIs : INTEGER - 32bit
DZ1_CPPLINK Dz1Error u32_t_fromASN(u32_t *dst, INTEGER *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(u32_t, INTEGER);

DZ1_CPPLINK Dz1Error u32_t_toASN(INTEGER *dst, u32_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(u32_t, INTEGER);

DZ1_CPPLINK Dz1Error s32_t_fromASN(s32_t *dst, INTEGER *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(s32_t, INTEGER);

DZ1_CPPLINK Dz1Error s32_t_toASN(INTEGER *dst, s32_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(s32_t, INTEGER);
// Support APIs : INTEGER - 32bit
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Support APIs : INTEGER - 16bit
DZ1_CPPLINK Dz1Error u16_t_fromASN(u16_t *dst, INTEGER *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(u16_t, INTEGER);
#define Dz1u16_newFromASN	u16_t_newFromASN

DZ1_CPPLINK Dz1Error u16_t_toASN(INTEGER *dst, u16_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(u16_t, INTEGER);
#define Dz1u16_toNewASN		u16_t_toNewASN

DZ1_CPPLINK Dz1Error s16_t_fromASN(s16_t *dst, INTEGER *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(s16_t, INTEGER);
#define Dz1s16_newFromASN	s16_t_newFromASN

DZ1_CPPLINK Dz1Error s16_t_toASN(INTEGER *dst, s16_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(s16_t, INTEGER);
#define Dz1s16_toNewASN		s16_t_toNewASN
// Support APIs : INTEGER - 16bit
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Support APIs : INTEGER - 8bit
DZ1_CPPLINK Dz1Error u8_t_fromASN(u8_t *dst, INTEGER *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(u8_t, INTEGER);
#define Dz1u8_fromASN		u8_t_fromASN
#define Dz1u8_newFromASN	u8_t_newFromASN

DZ1_CPPLINK Dz1Error u8_t_toASN(INTEGER *dst, u8_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(u8_t, INTEGER);
#define Dz1u8_toASN			u8_t_toASN
#define Dz1u8_toNewASN		u8_t_toNewASN

DZ1_CPPLINK Dz1Error s8_t_fromASN(s8_t *dst, INTEGER *src);
#define Dz1s8_newFromASN	s8_t_fromASN
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(s8_t, INTEGER);

DZ1_CPPLINK Dz1Error s8_t_toASN(INTEGER *dst, s8_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(s8_t, INTEGER);
// Support APIs : INTEGER - 8bit
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Support APIs : REAL
DZ1_CPPLINK Dz1Error real_t_fromASN(real_t *dst, REAL *src);
DZ1_CPPLINK DZ1_DECL_NEW_FROM_ASN(real_t, REAL);

DZ1_CPPLINK Dz1Error real_t_toASN(REAL *dst, real_t *src, ASN1WorkSpace *ws);
DZ1_CPPLINK DZ1_DECL_TO_NEW_ASN(real_t, REAL);
// Support APIs : REAL
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Support APIs : TIME
DZ1_CPPLINK Dz1Error		 Dz1TimeVal_fromGeneralizedTime(Dz1TimeVal *dst, GeneralizedTime *src);
DZ1_DECL_NEW_FROM_ASN_NAME(Dz1TimeVal, GeneralizedTime);	// Dz1TimeVal_newFromGeneralizedTime

DZ1_CPPLINK Dz1Error		 Dz1TimeVal_toGeneralizedTime(GeneralizedTime *dst, Dz1TimeVal *src, ASN1WorkSpace *ws);
DZ1_CPPLINK GeneralizedTime *Dz1TimeVal_toNewGeneralizedTime(Dz1TimeVal *src, ASN1WorkSpace *ws, Dz1Error *err);
// Support APIs : TIME
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CODEC Support
typedef ssize_t (*__asn_encode_func__)(void  *srcptr, u8_t **dstbuf,			  Dz1Asn1Codec codec, Dz1Error *err);
typedef ssize_t (*__asn_decode_func__)(void **dstptr, u8_t  *srcbuf, size_t size, Dz1Asn1Codec codec, Dz1Error *err);

typedef struct Dz1GasnMsgCodecApi
{
	int present;
	str_t oidStr;
	__asn_encode_func__ enc;
	__asn_decode_func__ dec;
} Dz1GasnMsgCodecApi;

#define _ASN_CODEC_ENTRY_(msg, oid, name, type)		{ msg##Present_##name, oid, (__asn_encode_func__)type##_encode, (__asn_decode_func__)type##_decode }
#define _ASN_CODEX_ENTRY_(msg, oid, name)			{ msg##Present_##name, oid, NULL, NULL }
#define _ASN_CODEC_TERM_							{ -1 }

#define _ASN_CODEC_API_IMPL(AsnName) \
	STATIC_DECODE_EACH_FUNC_IMPL(Dz1##AsnName, AsnName) \
	static DECODE_FUNC_IMPL		(Dz1##AsnName) \
	STATIC_ENCODE_EACH_FUNC_IMPL(Dz1##AsnName, AsnName) \
	static ENCODE_FUNC_IMPL		(Dz1##AsnName, AsnName)

typedef void *(*Dz1GasnUnionNewFunc)(int present, void *ptr, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1GasnSupport_asn_encode(void *srcptr, u8_t **dstbuf, Dz1Asn1Codec codec, str_t *retOID, Dz1GasnMsgCodecApi table[], Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1GasnSupport_asn_decode(str_t oidStr, void **dstptr, u8_t *srcbuf, size_t size, Dz1Asn1Codec codec, Dz1GasnMsgCodecApi table[],
											  Dz1GasnUnionNewFunc _new, Dz1CancelFunc _delAndSetNull, Dz1Error *err);
// CODEC Support
///////////////////////////////////////////////////////////////////////////////

#endif