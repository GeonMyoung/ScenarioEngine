#ifndef _ASN1_PER_UTCTime_H
#define _ASN1_PER_UTCTime_H

#include "ASN1_PER_STRING.h"

/*UTCTime */
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_UTCTime (ASN1WorkSpace *ws,UTCTime *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_UTCTime (ASN1WorkSpace *ws,UTCTime *value,
											 Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_UTCTime (ASN1WorkSpace *ws,UTCTime *value,
										   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_UTCTime (ASN1WorkSpace* ws,UTCTime* value, 
											 Asn1ConsInfo *consinfo);

#endif
