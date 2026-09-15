#ifndef _ASN1_PER_UTF8STRING_H
#define _ASN1_PER_UTF8STRING_H

#include "ASN1_PER_STRING.h"

/*UTF8String */
#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_UTF8Str (ASN1WorkSpace *ws,UTF8Str *value,
									     Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_UTF8Str (ASN1WorkSpace *ws,UTF8Str *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_UTF8Str (ASN1WorkSpace *ws,UTF8Str *value,
									     Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_UTF8Str (ASN1WorkSpace* ws,UTF8Str* value, 
													   Asn1ConsInfo *consinfo);
#else
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_UTF8String (ASN1WorkSpace *ws,UTF8String *value,
									     Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_UTF8String (ASN1WorkSpace *ws,UTF8String *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_UTF8String (ASN1WorkSpace *ws,UTF8String *value,
									     Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_UTF8String (ASN1WorkSpace* ws,UTF8String* value, 
													   Asn1ConsInfo *consinfo);
#endif // AVIOD_NAME_COLLISION_UTF8_STRING

#endif
