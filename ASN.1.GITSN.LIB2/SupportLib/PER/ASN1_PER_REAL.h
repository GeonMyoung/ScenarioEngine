#ifndef _ASN_PER_REAL_H_H
#define _ASN_PER_REAL_H_H


#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TYPE/ASN1_Type.h"
#include "../PER/ASN1_PER_SET.h"

#include <math.h>

 
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_Real(ASN1WorkSpace*ws, ASNREAL *Tvalue,Asn1ConsInfo *consinfo);
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_REAL(ASN1WorkSpace*ws, REAL *Tvalue,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_Real(ASN1WorkSpace*ws, ASNREAL *value,Asn1ConsInfo *consinfo);
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_REAL(ASN1WorkSpace*ws, REAL *value,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_Real(ASN1WorkSpace*ws, ASNREAL *Tvalue,Asn1ConsInfo *consinfo);
ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_REAL(ASN1WorkSpace*ws, REAL *Tvalue,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_Real(ASN1WorkSpace*ws, ASNREAL *value,Asn1ConsInfo *consinfo);
ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_REAL(ASN1WorkSpace*ws, REAL *value,Asn1ConsInfo *consinfo);


#endif

