#ifndef ASN_PER_SET_H_
#define ASN_PER_SET_H_


#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../PER/ASN1_PER_STRING.h"
#include "../PER/ASN1_PER_BITSTRING.h"
#include "../PER/ASN1_PER_ENUMERATED.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_extLengthMoveMem(ASN1WorkSpace * ws,ASNINT32 position,ASNUINT16  bitpointer);


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_extLengthMoveMem(ASN1WorkSpace * ws,ASNINT32* movelength,ASNUINT8*  bitpointer);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_extLengthMoveMem(ASN1WorkSpace * ws,ASNUINT32 position,ASNUINT16  bitpointer);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_extLengthMoveMem(ASN1WorkSpace * ws,ASNINT32* movelength,ASNUINT8*  bitpointer);


ASN1_CPPLINK ASNINT32 ASN1_FillAndMoveMem(ASN1WorkSpace * ws,ASNINT32* movelength,ASNUINT8*  bitpointer);


ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_extOption(ASN1WorkSpace * ws,ASN1PERAlign Align_Flag,ASNINT32 count);

ASN1_CPPLINK ASNINT32 ASN1_PER_CheckExtBit(ASNUINT8 * extvalue,ASNINT32 bitindex);

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_SetExtIndex(ASN1WorkSpace *ws, ASN1PERAlign Align_Flag, ASNINT32 bit, ASNUINT16 pointer, ASNUINT32 extindex, ASNUINT32 extcount);

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_extOption(ASN1WorkSpace * ws, 
								ASN1PERAlign Align_Flag,
								ASNINT32 * extcount,ASNUINT8 ** extvalue);


ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_unKnown(ASN1WorkSpace * ws,ASN1PERAlign Align_Flag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_WirteBuffer(ASN1WorkSpace *ws);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_WirteBuffer(ASN1WorkSpace *ws);


ASN1_CPPLINK ASNINT32 ASN1_SaveCurrentPointer(ASN1WorkSpace *ws,ASNINT32 *bytePointer, ASNUINT16 *bitPointer);



ASN1_CPPLINK ASNINT32 ASN1_GetIndex(ASNINT64 value,ASNUINT8 *index);


ASN1_CPPLINK ASNINT32 ASN1_GetM(ASNINT64 *value,ASNINT32 index);


ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_bit(ASN1WorkSpace *ws,ASNBOOL value);


ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_bit(ASN1WorkSpace *ws,ASNINT64* value,ASNINT32 length);


//ASNINT32 ASN1_PER_Enc_extOption(ASN1WorkSpace * ws, ASNINT64 * value,ASNINT32 count);

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_extbit(ASN1WorkSpace *ws,ASNBOOL *value);


ASN1_CPPLINK ASNINT32 ASN1_PER_turn_M(ASNUINT64 *value,ASNINT32 len);


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_Set_Seq_Of_Length(ASN1WorkSpace *ws, ASNINT32 *allLength,
											  ASNINT32 *length,Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_Set_Seq_Of_Length(ASN1WorkSpace *ws, ASNINT32 *allLength,
												ASNINT32 *length,Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_Set_Seq_Of_Length(ASN1WorkSpace *ws, ASNINT32 *length,Asn1ConsInfo *consinfo);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(ASN1WorkSpace *ws, ASNINT32 *length,Asn1ConsInfo *consinfo);


ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_extbit(ASN1WorkSpace *ws,ASNUINT64 value);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(ASN1WorkSpace *ws,ASNINT64 index,ASNBOOL flag,ASNBOOL isextend,ASNINT32 ub);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(ASN1WorkSpace *ws,ASNINT64 *index,ASNBOOL *flag,ASNBOOL isextend,ASNINT32 ub);


ASN1_CPPLINK ASNINT32 error();

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_Opt_Def_bit(ASN1WorkSpace * ws,ASNINT32 extcount,ASNUINT8 ** extvalue);

#endif

