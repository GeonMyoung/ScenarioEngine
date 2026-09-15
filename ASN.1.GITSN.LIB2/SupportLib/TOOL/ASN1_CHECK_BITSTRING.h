#ifndef _ASN_BITSTRING_H_
#define _ASN_BITSTRING_H_

#include "OS/ASN1_Sys.h"
#include "TYPE/ASN1_Type.h"

ASN1_CPPLINK int ASN1_CHECK_BITSTRING(BITSTRING *ValueChecked, ASNUINT8 *ConsChecked);
ASN1_CPPLINK int ASN1_CXER_Dec_BitString_Process(ASN1WorkSpace * ws, BITSTRING *value, ASNUINT32 lower);


#endif
