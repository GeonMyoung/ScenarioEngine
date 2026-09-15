#ifndef ASN_BER_Open_Type_
#define ASN_BER_Open_Type_


#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "../TOOL/ASN1_BER_Check_Length.h"


	

/************************************************************************/
/* Encode OpenType:Copy value to ws                                     */
/************************************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_OpenType(ASN1WorkSpace *ws,OpenType *value,ASN1TagType flag);


/************************************************************************/
/* Decode OpenType:Copy ws to value                                     */
/************************************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_OpenType(ASN1WorkSpace *ws,OpenType *value,ASNINT32 len,ASN1TagType flag);

ASN1_CPPLINK ASNINT32 ASN1_BER_OpenType_SetP(ASN1WorkSpace *ws,OpenType *value);

/*ASNINT32 ASN1_BER_Dec_OpenType_Loop(ASN1WorkSpace *ws,ASNINT32 length);*/


/*ASNINT32 ASN1_BER_Transact(ASN1WorkSpace *ws,OpenType *value);*/


#endif /*_Open_Type_*/

