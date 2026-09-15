#ifndef DZ1_ASN1_TYPE_DESCR_H_LOCAL
#define DZ1_ASN1_TYPE_DESCR_H_LOCAL

#include <dz1_asn1_typedescr.h>

#define Dz1Asn1TypeComformance_fname(struct_name)	__internal_api_##struct_name##_check
#define Dz1Asn1TypeComformance_name(struct_name)	dz1Asn1TypeComformance##struct_name
#define static_Dz1Asn1TypeComformance_declare(struct_name)\
static bool_t Dz1Asn1TypeComformance_fname(struct_name)(Dz1Asn1Constraint *cons, void *user_data, bool_t *ret_is_ext)\
{\
	bool_t ret = FALSE;\
	struct_name *p = (struct_name *)user_data;\
	if ((ret = struct_name##_check(p)) == FALSE) { }\
	else if (cons != NULL)\
		ret = struct_name##_conformance(cons, p, ret_is_ext);\
	return ret;\
}\
static Dz1Asn1TypeComformance Dz1Asn1TypeComformance_name(struct_name) =\
{\
	NULL,\
	Dz1Asn1TypeComformance_fname(struct_name)\
}

// Internal Common Stuff
DZ1_CPPLINK_VAR Dz1Asn1TypeDescr	 dz1Asn1TypeDescrDz1Asn1EmbPdvID;

// Child Descriptor Utility
DZ1_CPPLINK bool_t					 Dz1Asn1TypeDescrChild_isDefault(Dz1Asn1TypeDescrChild *p, void *data_ptr);
DZ1_CPPLINK bool_t					 Dz1Asn1TypeDescrChild_isOptional(Dz1Asn1TypeDescrChild *p, void *data_ptr);

// Descriptor Utility
DZ1_CPPLINK Dz1Asn1TypeDescrChild	*Dz1Asn1TypeDescr_findChild(Dz1Asn1TypeDescr *p, Dz1Asn1Tag *key, s32_t *opt_ret_idx);
DZ1_CPPLINK Dz1Asn1Custom			*Dz1Asn1TypeDescr_genWipCustom(Dz1Asn1TypeDescr *descr, Dz1Error *errp);

#endif
