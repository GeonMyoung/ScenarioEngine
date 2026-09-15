#ifndef DZ1_ASN1_TYPES_H
#define DZ1_ASN1_TYPES_H

#include <dz1_asn1_types_def.h>

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Tag
DZ1_CPPLINK str_t	 Dz1Asn1TagA_printable(Dz1Asn1Tag *p, char *buf, size_t buf_sz);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t	 Dz1Asn1TagW_printable(Dz1Asn1Tag *p, wchar_t *buf, size_t buf_sz);
#ifdef UNICODE
#define				 Dz1Asn1Tag_printable	Dz1Asn1TagW_printable
#else // UNICODE
#define				 Dz1Asn1Tag_printable	Dz1Asn1TagA_printable
#endif // UNICODE
#else // UNIX_SYSTEM
#define				 Dz1Asn1Tag_printable	Dz1Asn1TagA_printable
#endif // UNIX_SYSTEM
// Dz1Asn1Tag
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeAPI &  Macros
typedef struct Dz1Asn1TypeAPI
{
	Dz1GenFunc						 gen;
	Dz1CloneFunc					 clone;
	Dz1DelFunc						 del;
	Dz1DelFunc						 delAndSetNull;
	Dz1CmpFunc						 cmp;

	Dz1DumpFunc						 dumpA;
	Dz1FDumpFunc					 fdumpA;

	Dz1DumpFunc						 dumpW;
	Dz1FDumpFunc					 fdumpW;
} Dz1Asn1TypeAPI;

static __inline__ void Dz1Asn1TypeAPIA_DUMP(Dz1Asn1TypeAPI *c_api, void *v_ptr, int tab)
{
	if (c_api == NULL || c_api->dumpA == NULL)
		Dz1ThreadA_printf("#FAULT\n");
	else c_api->dumpA(v_ptr, tab);
}
#ifndef UNIX_SYSTEM
static __inline__ void Dz1Asn1TypeAPIW_DUMP(Dz1Asn1TypeAPI *c_api, void *v_ptr, int tab)
{
	if (c_api == NULL || c_api->dumpW == NULL)
		Dz1ThreadW_printf(L"#FAULT\n");
	else c_api->dumpW(v_ptr, tab);
}
#ifdef UNICODE
#define					Dz1Asn1TypeAPI_DUMP		Dz1Asn1TypeAPIW_DUMP
#else // UNICODE
#define					Dz1Asn1TypeAPI_DUMP		Dz1Asn1TypeAPIA_DUMP
#endif // UNICODE
#else	// UNIX_SYSTEM
#define					Dz1Asn1TypeAPI_DUMP		Dz1Asn1TypeAPIA_DUMP
#endif // UNIX_SYSTEM

#define Dz1Asn1TypeAPI_name(struct_name)			struct_name##Api
#define Dz1Asn1TypeAPI_announce(struct_name)		Dz1Asn1TypeAPI Dz1Asn1TypeAPI_name(struct_name)
#ifdef UNIX_SYSTEM
#define Dz1Asn1TypeAPI_declare(struct_name)\
						Dz1Asn1TypeAPI_announce(struct_name) =\
						{\
							(Dz1GenFunc)struct_name##_gen,\
							(Dz1CloneFunc)struct_name##_clone,\
							(Dz1DelFunc)struct_name##_del,\
							(Dz1DelFunc)struct_name##_delAndSetNull,\
							(Dz1CmpFunc)struct_name##_cmp,\
							(Dz1DumpFunc)struct_name##A_dump,\
							(Dz1FDumpFunc)struct_name##A_fdump\
							NULL,\
							NULL\
						}
#define Dz1Asn1TypeAPI_declare_trk(struct_name, var_name)\
						Dz1Asn1TypeAPI_announce(struct_name) =\
						{\
							(Dz1GenFunc)__##struct_name##_gen,\
							(Dz1CloneFunc)__##struct_name##_clone,\
							(Dz1DelFunc)struct_name##_del,\
							(Dz1DelFunc)struct_name##_delAndSetNull,\
							(Dz1CmpFunc)struct_name##_cmp,\
							(Dz1DumpFunc)struct_name##A_dump,\
							(Dz1FDumpFunc)struct_name##A_fdump\
							NULL,\
							NULL\
						}
#else // UNIX_SYSTEM
#define Dz1Asn1TypeAPI_declare(struct_name)\
						Dz1Asn1TypeAPI_announce(struct_name) =\
						{\
							(Dz1GenFunc)struct_name##_gen,\
							(Dz1CloneFunc)struct_name##_clone,\
							(Dz1DelFunc)struct_name##_del,\
							(Dz1DelFunc)struct_name##_delAndSetNull,\
							(Dz1CmpFunc)struct_name##_cmp,\
							(Dz1DumpFunc)struct_name##A_dump,\
							(Dz1FDumpFunc)struct_name##A_fdump,\
							(Dz1DumpFunc)struct_name##W_dump,\
							(Dz1FDumpFunc)struct_name##W_fdump\
						}
#define Dz1Asn1TypeAPI_declare_trk(struct_name)\
						Dz1Asn1TypeAPI_announce(struct_name) =\
						{\
							(Dz1GenFunc)__##struct_name##_gen,\
							(Dz1CloneFunc)__##struct_name##_clone,\
							(Dz1DelFunc)struct_name##_del,\
							(Dz1DelFunc)struct_name##_delAndSetNull,\
							(Dz1CmpFunc)struct_name##_cmp,\
							(Dz1DumpFunc)struct_name##A_dump,\
							(Dz1FDumpFunc)struct_name##A_fdump,\
							(Dz1DumpFunc)struct_name##W_dump,\
							(Dz1FDumpFunc)struct_name##W_fdump\
						}
#endif
// Dz1Asn1TypeAPI &  Macros
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescrChild : get_child macros
//#define Dz1Asn1TypeDescrChild_GetMember_name(struct_name, memb)		struct_name##_get_##memb
#define Dz1Asn1GetChildF_func_name(struct_name, memb)		struct_name##_get_##memb

// get pointer child from struct
#define Dz1Asn1GetChildF_SeqMembPtr(struct_name, memb)	\
void *Dz1Asn1GetChildF_func_name(struct_name, memb)(void *_src, Dz1Asn1TypeDescr **opt_ret_descr)\
{\
	void *ret = NULL;\
	struct_name *src = (struct_name *)_src;\
	if (src != NULL)\
		ret = (void *)src->memb;\
	return ret;\
}

// get variable child from struct
#define Dz1Asn1GetChildF_SeqMembVar(struct_name, memb)	\
void *Dz1Asn1GetChildF_func_name(struct_name, memb)(void *_src, Dz1Asn1TypeDescr **opt_ret_descr)\
{\
	void *ret = NULL;\
	struct_name *src = (struct_name *)_src;\
	if (src != NULL)\
		ret = (void *)&src->memb;\
	return ret;\
}

// get pointer child from union
#define Dz1Asn1GetChildF_ChoiceMembPtr(struct_name, memb)	\
void *Dz1Asn1GetChildF_func_name(struct_name, memb)(void *_src, Dz1Asn1TypeDescr **opt_ret_descr)\
{\
	void *ret = NULL;\
	struct_name *src = (struct_name *)_src;\
	if (src != NULL && src->present == struct_name##Present##_##memb)\
		ret = (void *)src->x.memb;\
	return ret;\
}

// get variable child from union
#define Dz1Asn1GetChildF_ChoiceMembVar(struct_name, memb)	\
void *Dz1Asn1GetChildF_func_name(struct_name, memb)(void *_src, Dz1Asn1TypeDescr **opt_ret_descr)\
{\
	void *ret = NULL;\
	struct_name *src = (struct_name *)_src;\
	if (src != NULL && src->present == struct_name##Present##_##memb)\
		ret = (void *)&src->x.memb;\
	return ret;\
}
// Dz1Asn1TypeDescrChild : get_child macros
///////////////////////////////////////////////////////////////////////////////

#define Dz1Asn1TagVOID { Dz1Asn1TagClass_max,		Dz1Asn1TagFlag_max,		(u64_t)-1 }

#define BerTagValueDz1Asn1Bool			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_boolean }
#define BerTagValueDz1Asn1Int			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_integer }
#define BerTagValueDz1Asn1BitStr		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_bit_str }
#define BerTagValueDz1Asn1OctetStr		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_octet_str }
#define BerTagValueDz1Asn1Null			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_nul }
#define BerTagValueDz1Asn1OID			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_oid }
#define BerTagValueDz1Asn1ObjDescr		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_obj_descr }
#define BerTagValueDz1Asn1External		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_construct, Dz1Asn1Type_external }
#define BerTagValueDz1Asn1InstanceOf	{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_construct, Dz1Asn1Type_instance }
#define BerTagValueDz1Asn1Real			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_realnum }
#define BerTagValueDz1Asn1Enum			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_enumerated }
#define BerTagValueDz1Asn1EmbPdv		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_construct, Dz1Asn1Type_embPDV }
#define BerTagValueDz1Asn1UTF8Str		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_utf8str }
#define BerTagValueDz1Asn1RelOID		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_reloid }
#define BerTagValueDz1Asn1Time			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_time }
#define BerTagValueDz1Asn1Sequence		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_construct, Dz1Asn1Type_seq }
#define BerTagValueDz1Asn1SequenceOf	{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_construct, Dz1Asn1Type_seqof }
#define BerTagValueDz1Asn1Set			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_construct, Dz1Asn1Type_set }
#define BerTagValueDz1Asn1SetOf			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_construct, Dz1Asn1Type_setof }
#define BerTagValueDz1Asn1DigitStr		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_digit_str }
#define BerTagValueDz1Asn1PrintStr		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_print_str }
#define BerTagValueDz1Asn1TeletexStr	{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_teletex_str }
#define BerTagValueDz1Asn1VideotexStr	{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_videotex_str }
#define BerTagValueDz1Asn1IA5Str		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_ia5_str }
#define BerTagValueDz1Asn1UTCTime		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_utc_time }		// forced primitive
#define BerTagValueDz1Asn1GeneralTime	{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_general_time }	// forced primitive
#define BerTagValueDz1Asn1GraphicStr	{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_graphic_str }
#define BerTagValueDz1Asn1VisibleStr	{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_visible_str }
#define BerTagValueDz1Asn1GeneralStr	{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_general_str }
#define BerTagValueDz1Asn1UniversalStr	{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_uni_str }
#define BerTagValueDz1Asn1CharStr		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_construct, Dz1Asn1Type_char_str }
#define BerTagValueDz1Asn1BMPStr		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_variable,  Dz1Asn1Type_bmp_str }
#define BerTagValueDz1Asn1Date			{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_date }
#define BerTagValueDz1Asn1TimeOfDay		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_time_of_day }
#define BerTagValueDz1Asn1DateTime		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_date_time }
#define BerTagValueDz1Asn1Duration		{ Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, Dz1Asn1Type_duration }

DZ1_CPPLINK_VAR Dz1Asn1Tag		 dz1Asn1BerTagSequence;
DZ1_CPPLINK_VAR Dz1Asn1Tag		 dz1Asn1BerTagSequenceOf;
DZ1_CPPLINK_VAR Dz1Asn1Tag		 dz1Asn1BerTagSet;
DZ1_CPPLINK_VAR Dz1Asn1Tag		 dz1Asn1BerTagSetOf;

DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1Any);

DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1Bool);							// 1
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1Int);							// 2
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1BitStr);							// 3
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1OctetStr);						// 4
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1Null);							// 5
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1OID);							// 6
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1ObjDescr);						// 7
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1External);						// 8
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1InstanceOf);						// 8
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1Real);							// 9
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1Enum);							// 10
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1EmbPdv);							// 11
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1UTF8Str);						// 12
#define									Dz1Asn1RelOIDApi Dz1Asn1OIDApi			// 13
#define									Dz1Asn1TimeApi	 Dz1Asn1UTF8StrApi		// 14
																							// 15 Reserved
																							// 16 Sequence, Sequence-Of
																							// 17 Set, Set-Of
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1DigitStr);						// 18
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1PrintStr);						// 19
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1TeletexStr);						// 20
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1VideotexStr);					// 21
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1IA5Str);							// 22
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1UTCTime);						// 23
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1GeneralTime);					// 24
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1GraphicStr);						// 25
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1VisibleStr);						// 26
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1GeneralStr);						// 27
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1UniversalStr);					// 28
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1CharStr);						// 29
DZ1_CPPLINK_VAR Dz1Asn1TypeAPI_announce(Dz1Asn1BMPStr);							// 30
#define									Dz1Asn1DateApi		Dz1Asn1UTF8StrApi	// 31
#define									Dz1Asn1TimeOfDayApi	Dz1Asn1UTF8StrApi	// 32
#define									Dz1Asn1DateTimeApi	Dz1Asn1UTF8StrApi	// 33
#define									Dz1Asn1DurationApi	Dz1Asn1UTF8StrApi	// 34

DZ1_CPPLINK bool_t	 Dz1Asn1OID_initFromWIP(Dz1Asn1OID *dst, Dz1Asn1WipOid *src, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// Prefixed Type Support
DZ1_CPPLINK bool_t	 Dz1Asn1Prefixed_apply(Dz1Asn1WipValue *dst_data, struct Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *src_data, u32_t order, Dz1Error *errp);
DZ1_CPPLINK void	*Dz1Asn1Prefixed_getChild(void *_src, struct Dz1Asn1TypeDescr **opt_ret_descr);
// Prefixed Type Support
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1MetaDataRange API
DZ1_CPPLINK bool_t	 Dz1Asn1MetaDataRange_match(Dz1Asn1MetaDataRange *p, Dz1Asn1Int v);
DZ1_CPPLINK int		 Dz1Asn1MetaDataRange_test(Dz1Asn1MetaDataRange *p, Dz1Asn1Int v);
// Dz1Asn1MetaDataRange API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// REAL Range Entry
DZ1_CPPLINK bool_t	 Dz1Asn1MetaDataRealRange_match(Dz1Asn1MetaDataRealRange *p, Dz1Asn1Real v);
// REAL Range Entry
///////////////////////////////////////////////////////////////////////////////


#endif	// DZ1_ASN1_TYPES_H
