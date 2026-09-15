#ifndef _ASN1_PER_ObjectDescriptor_H
#define _ASN1_PER_ObjectDescriptor_H

#include "ASN1_PER_STRING.h"

/*ObjectDescriptor */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_ObjectDescriptor (ASN1WorkSpace *ws,ObjectDescriptor *value,
									     Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_ObjectDescriptor (ASN1WorkSpace *ws,ObjectDescriptor *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_ObjectDescriptor (ASN1WorkSpace *ws,ObjectDescriptor *value,
									     Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_ObjectDescriptor (ASN1WorkSpace* ws,ObjectDescriptor* value, 
										   Asn1ConsInfo *consinfo);

#endif
