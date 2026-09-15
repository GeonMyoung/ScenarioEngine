#ifndef _ASN1_PER_PrintableString_H
#define _ASN1_PER_PrintableString_H

#include "ASN1_PER_STRING.h"

/*PrintableString */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_PrintableString (ASN1WorkSpace *ws,PrintableString *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_PrintableString (ASN1WorkSpace *ws,PrintableString *value,
											 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_PrintableString (ASN1WorkSpace *ws,PrintableString *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_PrintableString (ASN1WorkSpace* ws,PrintableString* value, 
											 Asn1ConsInfo *consinfo);

#endif
