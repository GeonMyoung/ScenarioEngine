#ifndef _ASN1_PER_GeneralizedTime_H
#define _ASN1_PER_GeneralizedTime_H

#include "ASN1_PER_STRING.h"

/*GeneralizedTime */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_GeneralizedTime (ASN1WorkSpace *ws,GeneralizedTime *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_GeneralizedTime (ASN1WorkSpace *ws,GeneralizedTime *value,
											 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_GeneralizedTime (ASN1WorkSpace *ws,GeneralizedTime *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_GeneralizedTime (ASN1WorkSpace* ws,GeneralizedTime* value, 
											 Asn1ConsInfo *consinfo);

#endif
