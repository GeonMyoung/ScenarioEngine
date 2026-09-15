#include "ASN1_BER_VideotexString.h"

ASNINT32 ASN1_BER_Enc_VideotexString(ASN1WorkSpace *ws, VideotexString *value, ASN1TagType flag)
{
	return ASN1_BER_Enc_String(ws, value, 21, flag);
}

ASNINT32 ASN1_BER_Dec_VideotexString(ASN1WorkSpace *ws, VideotexString *value, ASNINT32 length, ASN1TagType flag)
{
	return ASN1_BER_Dec_String(ws, value, 21, length, flag);
}
