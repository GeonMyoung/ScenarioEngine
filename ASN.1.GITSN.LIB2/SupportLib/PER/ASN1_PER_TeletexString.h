#ifndef _ASN1_PER_TeletexString_H
#define _ASN1_PER_TeletexString_H

#include "ASN1_PER_STRING.h"

/*TeletexString */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_TeletexString (ASN1WorkSpace *ws,TeletexString *value,
										Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_TeletexString (ASN1WorkSpace *ws,TeletexString *value,
										  Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_TeletexString (ASN1WorkSpace *ws,TeletexString *value,
										Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_TeletexString (ASN1WorkSpace* ws,TeletexString* value, 
										  Asn1ConsInfo *consinfo);

#endif
