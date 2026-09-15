#ifndef DZ1_ASN1_CONSTRAINT_TYPES_H_LOCAL
#define DZ1_ASN1_CONSTRAINT_TYPES_H_LOCAL

#include <dz1_asn1_constraint_types.h>

#define _array_clone(type_name, ret, memb_arr, memb_cnt, src_arr, src_cnt, ep)\
	if (src_cnt > 0)\
	{\
		if (src_arr == NULL)\
		{\
			if ((ret##->##memb_arr = (type_name *)Dz1Calloc(sizeof(type_name), (ret##->##memb_cnt = src_cnt), ep)) == NULL) ERR_OUT(ep);\
			else Dz1Error_set(ep, 0);\
		}\
		else if ((ret##->##memb_arr = (type_name *)Dz1Memory_clone((void *)src_arr, sizeof(type_name) * (ret##->##memb_cnt = src_cnt), ep)) == NULL) ERR_OUT(ep);\
		else Dz1Error_set(ep, 0);\
	}\
	else Dz1Error_set(ep, 0)


#endif
