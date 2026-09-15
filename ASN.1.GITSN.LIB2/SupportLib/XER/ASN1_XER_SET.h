#ifndef ASN_XER_SET_H_
#define ASN_XER_SET_H_


#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "XER/ASN1_XER_STRING.h"
#include "ASN1_XER_Name.h"
#include "XER/ASN1_XER_OpenType.h"
#include "TOOL/ASN1_List.h"
#include "string.h"
#include "math.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_Struct_Start(ASN1WorkSpace *ws,ASNUINT8 *name,
											 ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_Struct_Start(ASN1WorkSpace * ws,ASNUINT8 *name,
										 ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_Struct_End(ASN1WorkSpace * ws,ASNUINT8 *name,
										   ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_Struct_End(ASN1WorkSpace * ws,ASNUINT8 *name,
									   ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_Struct_Start(ASN1WorkSpace * ws,ASNUINT8* name,
											 ASN1XERFlag *xer_flag);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_Struct_Start(ASN1WorkSpace * ws,ASNUINT8* name,
										 ASN1XERFlag *xer_flag);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_Struct_End(ASN1WorkSpace * ws,ASNUINT8* name,
											 ASN1XERFlag *xer_flag);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_Struct_End(ASN1WorkSpace * ws,ASNUINT8* name,
									   ASN1XERFlag *xer_flag);

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Prolog(ASN1WorkSpace * ws);

ASN1_CPPLINK ASNINT32 Start_strcmp(ASN1WorkSpace *ws,ASNUINT8 *tvalue);

ASN1_CPPLINK ASNINT32 ASN1_XER_Temp_DeName(ASN1WorkSpace *ws,ASNINT32 *value_null,
							  ASNSTRING *tvalue);

ASN1_CPPLINK ASNINT32 Start_DeName_strcmp(ASNUINT8 *name,ASNSTRING *tvalue);

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_CANONICAL_Format(ASN1WorkSpace * ws);

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_BASIC_Format(ASN1WorkSpace * ws);

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_CANONICAL_Exbit(ASN1WorkSpace *ws);

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_BASIC_Exbit(ASN1WorkSpace *ws);


ASN1_CPPLINK ASNINT32 ASN1_XER_Set_Seq_Of_Loop(ASN1WorkSpace *ws);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_Struct_Start_Of(ASN1WorkSpace *ws,ASNUINT8 *name,
											    ASN1List *asnlist,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_Struct_Start_Of(ASN1WorkSpace *ws,ASNUINT8 *name,
										 ASN1List* asnlist,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_Struct_End_Of(ASN1WorkSpace *ws,ASNUINT8 *name,
										 ASN1List* asnlist,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_Struct_End_Of(ASN1WorkSpace *ws,ASNUINT8 *name,
										 ASN1List* asnlist,ASNINT32 tab_value);
ASN1_CPPLINK ASNINT32 inttostr(ASNINT32 sourint,ASNINT8 *deststr,ASNINT32 strlength);
ASN1_CPPLINK ASNINT32 changetimetogen(ASNINT8 *source,ASNINT8 *dest,ASNINT8 guflag);


#endif

