#ifndef _ASN1_PER_GraphicString_H
#define _ASN1_PER_GraphicString_H

#include "ASN1_PER_STRING.h"

/*GraphicString */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_GraphicString (ASN1WorkSpace *ws,GraphicString *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_GraphicString (ASN1WorkSpace *ws,GraphicString *value,
											 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_GraphicString (ASN1WorkSpace *ws,GraphicString *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_GraphicString (ASN1WorkSpace* ws,GraphicString* value, 
											 Asn1ConsInfo *consinfo);

#endif
