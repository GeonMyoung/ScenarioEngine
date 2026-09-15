#ifndef _ASN1_PER_VisibleString_H
#define _ASN1_PER_VisibleString_H

#include "ASN1_PER_STRING.h"

/*VisibleString */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_VisibleString (ASN1WorkSpace *ws,VisibleString *value,
											Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_VisibleString (ASN1WorkSpace *ws,VisibleString *value,
											  Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_VisibleString (ASN1WorkSpace *ws,VisibleString *value,
											Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_VisibleString (ASN1WorkSpace* ws,VisibleString* value, 
														  Asn1ConsInfo *consinfo);
			
#endif
