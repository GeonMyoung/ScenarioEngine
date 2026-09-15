#include "ASN1_BER_UTCTime.h"


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_UTCTime(ASN1WorkSpace* ws,UTCTime* value,
							 ASN1TagType flag)
{
	return	ASN1_BER_Enc_String(ws,value,23,flag);
}

ASNINT32 ASN1_BER_Dec_UTCTime(ASN1WorkSpace *ws, UTCTime *value, ASNINT32 length, ASN1TagType flag)
{
	return	ASN1_BER_Dec_String(ws, value, 23, length, flag);
}
