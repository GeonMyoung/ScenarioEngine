#ifndef _ASN_PER_UnString_H_
#define _ASN_PER_UnString_H_


#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "ASN1_PER_STRING.h"



/*UniversalString*/
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_UniversalString(ASN1WorkSpace *ws,UniversalString *value,
											Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_UniversalString(ASN1WorkSpace *ws,UniversalString *value,
											  Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_UniversalString(ASN1WorkSpace *ws,UniversalString *value,
											Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_UniversalString(ASN1WorkSpace* ws,UniversalString* value, 
											  Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_UNI_Process(ASN1WorkSpace *ws,UniversalString *value,
										Asn1ConsInfo *consinfo,ASNINT32 Default_bit);



ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_UNI_Process(ASN1WorkSpace *ws,UniversalString *value,
										  Asn1ConsInfo *consinfo,ASNINT32 Default_bit);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_UNI_Process(ASN1WorkSpace *ws,UniversalString *value,
										Asn1ConsInfo *consinfo,ASNINT32 Default_bit);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_UNI_Process(ASN1WorkSpace* ws,UniversalString* value, 
										  Asn1ConsInfo *consinfo,ASNINT32 Default_bit);

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_UNI_Value(ASN1WorkSpace* ws,UniversalString* value,
								ASNUINT32 length,ASNINT32 Default_bit,
								struct PER_Flag *per_flag,ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_UNI_Value(ASN1WorkSpace* ws,UniversalString* value,
								ASNUINT32 length,ASNINT32 Default_bit,
								struct PER_Flag *per_flag,ASN1PERAlign Align_Flag);

#endif /*_ASN_UnString_H_*/

