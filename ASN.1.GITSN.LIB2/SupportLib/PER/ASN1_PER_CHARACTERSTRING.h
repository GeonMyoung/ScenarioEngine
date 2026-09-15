#ifndef _ASN_PER_Charstr_H_
#define _ASN_PER_Charstr_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "ASN1_PER_STRING.h"
#include "../TOOL/ASN1_CHAR_TOOL.h"


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, 
									   Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value,
									  Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, 
										Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value,
										Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_CHARACTERSTRING_Value(ASN1WorkSpace* ws,CHARACTERSTRING* value,
									  ASNUINT32 length,struct PER_Flag *per_flag,
									  ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_CHARACTERSTRING_Value(ASN1WorkSpace* ws,CHARACTERSTRING* value,
									  ASNUINT32 length,struct PER_Flag *per_flag,
									  ASN1PERAlign Align_Flag);

#endif
