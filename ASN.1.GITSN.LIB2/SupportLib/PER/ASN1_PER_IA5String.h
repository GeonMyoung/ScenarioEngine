#ifndef _ASN1_PER_IA5String_H
#define _ASN1_PER_IA5String_H

#include "ASN1_PER_STRING.h"

/*IA5String */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_IA5String (ASN1WorkSpace *ws,IA5String *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_IA5String (ASN1WorkSpace *ws,IA5String *value,
											 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_IA5String (ASN1WorkSpace *ws,IA5String *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_IA5String (ASN1WorkSpace* ws,IA5String* value, 
											 Asn1ConsInfo *consinfo);

#endif
