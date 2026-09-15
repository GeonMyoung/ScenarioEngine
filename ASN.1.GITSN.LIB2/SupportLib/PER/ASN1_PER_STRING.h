#ifndef _ASN1_PER_STRING_H_
#define _ASN1_PER_STRING_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"

#define NUM_ABITS  4
#define NUM_UBITS  4

#define PRN_ABITS  8
#define PRN_UBITS  7

#define VIS_ABITS  8
#define VIS_UBITS  7

#define T61_ABITS  8
#define T61_UBITS  8

#define IA5_ABITS  8
#define IA5_UBITS  7

#define GEN_ABITS  8
#define GEN_UBITS  7

#define BMP_ABITS  16
#define BMP_UBITS  16

#define UCS_ABITS  32
#define UCS_UBITS  32

#define NORMAL_ABITS 8
#define NORMAL_UBITS 8


#define GENT_ABITS  8
#define GENT_UBITS  7

#define UTC_ABITS  8
#define UTC_UBITS  7

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_String(ASN1WorkSpace *ws,ASNSTRING *value,
								   Asn1ConsInfo *consinfo,ASNINT32 Default_bit);



ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_String(ASN1WorkSpace* ws,ASNSTRING* value, 
						        	 Asn1ConsInfo *consinfo,ASNINT32 Default_bit);

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_strLength(ASN1WorkSpace * ws, ASNUINT32 length,
								Asn1ConsInfo *consinfo, struct PER_Flag *per_flag,
								ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_SeverLength(ASN1WorkSpace * ws, ASNUINT32 *length,
								  Asn1ConsInfo *consinfo, ASNUINT32 *process_length,
								  ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_ExtLength(ASN1WorkSpace *ws, ASNUINT32 length,
								Asn1ConsInfo *consinfo,struct PER_Flag *per_flag,
								ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_String_Value(ASN1WorkSpace* ws,ASNSTRING* value,
								   ASNUINT32 length,ASNINT32 Default_bit,
								   struct PER_Flag *per_flag,ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 PER_CONSTRAINT_Enc_Process(ASN1WorkSpace* ws,Asn1ConsInfo *consinfo,
									ASNINT32 *Default_bit,struct PER_Flag *per_flag,
								    ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 per_encode_change_char_table(ASNUINT8 *input_string,ASNUINT8 *output_string);

ASN1_CPPLINK ASNINT32 per_ordering_char(ASNUINT8 *input_string,ASNUINT8 **output_string);


ASN1_CPPLINK ASNINT32 PER_DEFAULT_Bit_Align_Process(ASNINT32 default_bit);
ASN1_CPPLINK ASNINT32 PER_DEFAULT_Bit_UNAlign_Process(ASNINT32 default_bit);

ASN1_CPPLINK ASNINT32 PER_Enc_Len_Process(ASNUINT8* encode_memony,ASNINT16 length,ASNINT32 ebit);

ASN1_CPPLINK ASNINT32 PER_Dec_Len_Process(ASNUINT8* decode_memony,struct PER_Flag *per_flag,ASNINT32 ebit);


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_String(ASN1WorkSpace *ws,ASNSTRING *value,
								   Asn1ConsInfo *consinfo,ASNINT32 Default_bit);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_String(ASN1WorkSpace* ws,ASNSTRING* value, 
									 Asn1ConsInfo *consinfo,ASNINT32 Default_bit);

ASN1_CPPLINK ASNINT32 PER_CONSTRAINT_Dec_Process(ASN1WorkSpace* ws,Asn1ConsInfo *consinfo,
									ASNINT32 *Default_bit,struct PER_Flag *per_flag,
									ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_String_Value(ASN1WorkSpace* ws,ASNSTRING* value,
								   ASNUINT32 length,ASNINT32 Default_bit,
								   struct PER_Flag *per_flag,ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_strLength(ASN1WorkSpace * ws,Asn1ConsInfo *consinfo, 
								struct PER_Flag *per_flag,ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_ExtLength(ASN1WorkSpace *ws,Asn1ConsInfo *consinfo,
								struct PER_Flag *per_flag,ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_SeverLength(ASN1WorkSpace * ws,Asn1ConsInfo *consinfo, 
								  struct PER_Flag *per_flag,ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 per_decode_change_chartable(ASNUINT8 *input_string,ASNUINT8 *output_string);

ASN1_CPPLINK ASNINT32 PER_CHECK_Avail(ASNSTRING *value,ASNUINT8 *ACharSet,ASNINT32 ACharSet_count);


#endif /*_ASN1_PER_STRING_H_*/
