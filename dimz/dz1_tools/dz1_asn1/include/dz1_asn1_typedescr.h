#ifndef DZ1_ASN1_TYPEDESCR_H
#define DZ1_ASN1_TYPEDESCR_H

#include <dz1_asn1_typedescr_def.h>

DZ1_CPPLINK_VAR Dz1Asn1TypeDescrPresence dz1Asn1TypeDescrChildPresence_optional;

typedef struct Dz1Asn1TypeDescrChild
{
	Dz1Asn1Tag					 tag;
	Dz1Asn1TagOpt				 descr_tag;
	Dz1Asn1TypeDescr			*descr;
	Dz1Asn1ApplyChildF			 apply_data;
	Dz1Asn1GetChildF			 get_child;
	Dz1Asn1TypeDescrPresence	*presence;
} Dz1Asn1TypeDescrChild;
#define Dz1Asn1TypeDescrChild_NULL		{ Dz1Asn1TagVOID, Dz1Asn1TagOpt_max, NULL, NULL, NULL, NULL }
#define Dz1Asn1TypeDescrChild_isNULL(p)	((p->descr_tag == Dz1Asn1TagOpt_max && p->descr == NULL && p->apply_data == NULL && p->get_child == NULL) ? TRUE : FALSE)
#define Dz1Asn1TypeDescrChild_last		Dz1Asn1TypeDescrChild_NULL

///////////////////////////////////////////////////////////////////////////////
// Type Descriptor Name Macro
#define Dz1Asn1TypeDescrName(struct_name)							__##struct_name##_u8_
#define Dz1Asn1TypeDescrNameDecl(struct_name)						Dz1Asn1UTF8Str Dz1Asn1TypeDescrName(struct_name) = { (u8_t *)#struct_name, sizeof(#struct_name) - 1 }
// Type Descriptor Name Macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Finalize Macros
#define Dz1Asn1DataTypeFinalizeF_args						void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeDescr *descr, Dz1Error *err
#define Dz1Asn1DataTypeFinalizeF_name(struct_name)			struct_name##_finalize
#define Dz1Asn1DataTypeFinalizeF_announce(struct_name)		bool_t Dz1Asn1DataTypeFinalizeF_name(struct_name)(Dz1Asn1DataTypeFinalizeF_args)

// Construct Type
#define Dz1Asn1DataTypeFinalizeF_declare(struct_name) \
Dz1Asn1DataTypeFinalizeF_announce(struct_name)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	Dz1Asn1WipCst *src_cst = NULL;\
	Dz1Asn1Custom *src_sto = NULL;\
	struct_name *dst = (struct_name *)_dst, *src = NULL;\
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if (_src->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);\
	else if ((src_cst = _src->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);\
	else if ((src_sto = src_cst->storage) == NULL) ERR_SET_OUT(errp, EFAULT);\
	else if ((src = (struct_name *)src_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);\
	else\
	{\
		memcpy(dst, src, sizeof(struct_name));\
		memset(src, 0, sizeof(struct_name));\
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)\
		{\
			char str_name[64];\
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);\
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);\
		}\
		Dz1Error_set(errp, 0);\
	}\
	return errp->code == 0 ? TRUE : FALSE;\
}

// Array Type
#define Dz1Asn1ArrayTypeFinalizeF_declare(struct_name) \
Dz1Asn1DataTypeFinalizeF_announce(struct_name)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	Dz1Asn1WipCst *src_cst = NULL;\
	Dz1Asn1Custom *src_sto = NULL;\
	struct_name *dst = (struct_name *)_dst, *src = NULL;\
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if (_src->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);\
	else if ((src_cst = _src->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);\
	else if ((src_sto = src_cst->storage) == NULL) ERR_SET_OUT(errp, EFAULT);\
	else if ((src = (struct_name *)src_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);\
	else\
	{\
		Dz1Fifo_delAndSetNull(&dst->storage);\
		dst->storage = src->storage;\
		src->storage = NULL;\
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)\
		{\
			char str_name[64];\
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);\
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);\
		}\
		Dz1Error_set(errp, 0);\
	}\
	return errp->code == 0 ? TRUE : FALSE;\
}

// Table Type(?)
#define Dz1Asn1TableTypeFinalizeF_declare(struct_name) \
Dz1Asn1DataTypeFinalizeF_announce(struct_name)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	Dz1Asn1WipCst *src_cst = NULL;\
	Dz1Asn1Custom *src_sto = NULL;\
	struct_name *dst = (struct_name *)_dst, *src = NULL;\
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if (_src->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);\
	else if ((src_cst = _src->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);\
	else if ((src_sto = src_cst->storage) == NULL) ERR_SET_OUT(errp, EFAULT);\
	else if ((src = (struct_name *)src_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);\
	else\
	{\
		Dz1AATree_delAndSetNull(&dst->storage);\
		dst->storage = src->storage;\
		src->storage = NULL;\
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)\
		{\
			char str_name[64];\
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);\
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);\
		}\
		Dz1Error_set(errp, 0);\
	}\
	return errp->code == 0 ? TRUE : FALSE;\
}

// Enumerate Type
#define Dz1Asn1EnumTypeFinalizeF_declare(type_name)	\
Dz1Asn1DataTypeFinalizeF_announce(type_name)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	type_name *dst = (type_name *)_dst;\
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);\
	else if (_src->present != Dz1Asn1WipValuePresent_number) ERR_SET_OUT(errp, EFAULT);\
	else\
	{\
		(*dst) = (type_name)_src->x.number;\
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst) == FALSE)\
		{\
			char str_name[64];\
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);\
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);\
		}\
		Dz1Error_set(errp, 0);\
	}\
	return errp->code == 0 ? TRUE : FALSE;\
}
// Finalize Macros
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK bool_t  Dz1Asn1ApplyUtil_pointer_toss(void **_dst, Dz1Asn1WipValue *src, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// Finalize
DZ1_CPPLINK bool_t	Dz1Asn1Any_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeDescr *descr, Dz1Error *err);

DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1Bool);						//  1
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1Int);						//  2
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1BitStr);					//  3
DZ1_CPPLINK bool_t	Dz1Asn1OctetStr_finalize(Dz1Asn1DataTypeFinalizeF_args);	//  4
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1Null);						//  5
DZ1_CPPLINK bool_t	Dz1Asn1OID_finalize(Dz1Asn1DataTypeFinalizeF_args);			//  6
#define				Dz1Asn1ObjDescr_finalize Dz1Asn1OctetStr_finalize			//  7
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1External);					//  8
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1InstanceOf);				//  8
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1Real);						//  9
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1Enum);						// 10
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1EmbPdv);					// 11
#define				Dz1Asn1UTF8Str_finalize		Dz1Asn1OctetStr_finalize		// 12
#define				Dz1Asn1RelOID_finalize		Dz1Asn1OID_finalize				// 13
#define				Dz1Asn1Time_finalize		Dz1Asn1OctetStr_finalize		// 14
																				// 15 : Reserved
																				// 16 : Sequence, Sequence-Of
																				// 17 : Set, Set-Of
#define				Dz1Asn1DigitStr_finalize	Dz1Asn1OctetStr_finalize		// 18
#define				Dz1Asn1PrintStr_finalize	Dz1Asn1OctetStr_finalize		// 19
#define				Dz1Asn1TeletexStr_finalize	Dz1Asn1OctetStr_finalize		// 20
#define				Dz1Asn1VideotexStr_finalize Dz1Asn1OctetStr_finalize		// 21
#define				Dz1Asn1VideotexStr_finalize Dz1Asn1OctetStr_finalize		// 22
#define				Dz1Asn1UTCTime_finalize		Dz1Asn1OctetStr_finalize		// 23
#define				Dz1Asn1GeneralTime_finalize	Dz1Asn1OctetStr_finalize		// 24
#define				Dz1Asn1GraphicStr_finalize	Dz1Asn1OctetStr_finalize		// 25
#define				Dz1Asn1GraphicStr_finalize	Dz1Asn1OctetStr_finalize		// 26
#define				Dz1Asn1GeneralStr_finalize	Dz1Asn1OctetStr_finalize		// 27
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1UniversalStr);				// 28
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1CharStr);					// 29
DZ1_CPPLINK Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1BMPStr);					// 30
#define				Dz1Asn1Date_finalize		Dz1Asn1OctetStr_finalize		// 31
#define				Dz1Asn1TimeOfDay_finalize	Dz1Asn1OctetStr_finalize		// 32
#define				Dz1Asn1DateTime_finalize	Dz1Asn1OctetStr_finalize		// 33
#define				Dz1Asn1Duration_finalize	Dz1Asn1OctetStr_finalize		// 34
// Finalize
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK bool_t			 Dz1Asn1TypeDescr_chkConformance(Dz1Asn1TypeDescr *descr, void *user_data, bool_t *ret_is_ext);

///////////////////////////////////////////////////////////////////////////////
// Descriptor
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrEOC;
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrOpenType;
#define								 dz1Asn1TypeDescrAny				dz1Asn1TypeDescrOpenType

DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrBool;				// 1
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrInt;				// 2
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrBitStr;			// 3
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrOctetStr;			// 4
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrNull;				// 5
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrOID;				// 6
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrObjDescr;			// 7
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrExternal;			// 8
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrInstanceOf;		// 8
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrReal;				// 9
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrEnum;				// 10
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrEmbPdv;			// 11
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrUTF8Str;			// 12
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrRelOID;			// 13
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrTime;				// 14
																		// 15 Reserved
																		// 16 Sequence, Sequence-Of
																		// 17 Set, Set-Of
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrDigitStr;			// 18
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrPrintStr;			// 19
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrTeletexStr;		// 20
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrVideotexStr;		// 21
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrIA5Str;			// 22
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrUTCTime;			// 23
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrGeneralTime;		// 24
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrGraphicStr;		// 25
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrVisibleStr;		// 26
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrGeneralStr;		// 27	1B							-s	OK		OK
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrUniversalStr;		// 28
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrCharStr;			// 29
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrBMPStr;			// 30
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrDate;				// 31
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrTimeOfDay;			// 32
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrDateTime;			// 33	1F21	Not Support			-t	??		??
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrDuration;			// 34
// Descriptor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescrData clone, dump, fdump
DZ1_CPPLINK void			*Dz1Asn1TypeDescrData_gen(Dz1Asn1TypeDescr *descr, Dz1Error *err);
//#define					 Dz1Asn1TypeDescrData_clone(src_p, descr_p, ep)	_Dz1Asn1TypeDescrData_clone(src_p, descr_p, ep, __FILE__, __LINE__)
DZ1_CPPLINK void			*Dz1Asn1TypeDescrData_clone(Dz1Asn1TypeDescr *descr, void *src, Dz1Error *err /*, const char *__file, int __line*/);
//static __inline__ void	  *__Dz1Asn1TypeDescrData_clone(void *src, Dz1Asn1TypeDescr *descr, Dz1Error *err) { return Dz1Asn1TypeDescrData_clone(src, descr, err); }

DZ1_CPPLINK void			 Dz1Asn1TypeDescrDataA_dump(Dz1Asn1TypeDescr *descr, void *data, int tab);
DZ1_CPPLINK void			 Dz1Asn1TypeDescrDataA_fdump(Dz1Asn1TypeDescr *descr, FILE *fp, void *data, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void			 Dz1Asn1TypeDescrDataW_dump(Dz1Asn1TypeDescr *descr, void *data, int tab);
DZ1_CPPLINK void			 Dz1Asn1TypeDescrDataW_fdump(Dz1Asn1TypeDescr *descr, FILE *fp, void *data, int tab);
#ifdef UNICODE
#define						 Dz1Asn1TypeDescrData_dump									Dz1Asn1TypeDescrDataW_dump
#define						 Dz1Asn1TypeDescrData_fdump									Dz1Asn1TypeDescrDataW_vdump
#else // UNICODE
#define						 Dz1Asn1TypeDescrData_dump									Dz1Asn1TypeDescrDataA_dump
#define						 Dz1Asn1TypeDescrData_fdump									Dz1Asn1TypeDescrDataA_vdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1Asn1TypeDescrData_dump									Dz1Asn1TypeDescrDataA_dump
#define						 Dz1Asn1TypeDescrData_fdump									Dz1Asn1TypeDescrDataA_vdump
#endif // UNIX_SYSTEM
// Dz1Asn1TypeDescrData clone, dump, fdump
///////////////////////////////////////////////////////////////////////////////

#endif
