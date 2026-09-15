#ifndef _ASN1_PER_GeneralString_H
#define _ASN1_PER_GeneralString_H

#include "ASN1_PER_STRING.h"

/*GeneralString */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_GeneralString (ASN1WorkSpace *ws,GeneralString *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_GeneralString (ASN1WorkSpace *ws,GeneralString *value,
											 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_GeneralString (ASN1WorkSpace *ws,GeneralString *value,
											 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_GeneralString (ASN1WorkSpace* ws,GeneralString* value, 
											   Asn1ConsInfo *consinfo);

#endif
