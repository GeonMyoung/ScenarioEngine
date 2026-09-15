#ifndef _ASN1_CHAR_TOOL_H_
#define _ASN1_CHAR_TOOL_H_


// #include "PER/ASN1persrc.h"
// #include "XER/ASN1xersrc.h"

#include "PER/ASN1_PER_REAL.h"
#include "PER/ASN1_PER_OpenType.h"
#include "PER/ASN1_PER_BITSTRING.h"
#include "PER/ASN1_PER_BMPString.h"
#include "PER/ASN1_PER_BOOLEAN.h"
#include "PER/ASN1_PER_ENUMERATED.h"
#include "PER/ASN1_PER_INTEGER.h"
#include "PER/ASN1_PER_OCTETSTRING.h"
#include "PER/ASN1_PER_OBJECTIDENTIFIER.h"
#include "PER/ASN1_PER_STRING.h"
#include "PER/ASN1_PER_UniversalString.h"
#include "PER/ASN1_PER_RELATIVE_OID.h"
#include "PER/ASN1_PER_SET.h"
#include "PER/ASN1_PER_GeneralizedTime.h"
#include "PER/ASN1_PER_GeneralString.h"
#include "PER/ASN1_PER_GraphicString.h"
#include "PER/ASN1_PER_IA5String.h"
#include "PER/ASN1_PER_NumericString.h"
#include "PER/ASN1_PER_IA5String.h"
#include "PER/ASN1_PER_PrintableString.h"
#include "PER/ASN1_PER_TeletexString.h"
#include "PER/ASN1_PER_UTCTime.h"
#include "PER/ASN1_PER_UTF8String.h"
#include "PER/ASN1_PER_VideotexString.h"
#include "PER/ASN1_PER_VisibleString.h"
#include "PER/ASN1_PER_ObjectDescriptor.h"	

#include "IO/ASN1IO.h"
#include "MEM/mpool.h"

#include "ASN1_Length.h"
#include "ASN1_List.h"
#include "ASN1_Print.h"
#include "ASN1_Tag.h"
#include "ASN1_Tool_BitString.h"
#include "ASN1_Tool_String.h"
#include "ASN1_Tool_Time.h"
#include "ASN1_CHECK_REAL.h"
#include "ASN1_CHECK_RELATIVE_OID.h"
#include "ASN1_Operate_Byte.h"
#include "ASN1_CHECK_ObjectDescriptor.h"
#include "ASN1_CHECK_INTEGER.h"
#include "ASN1_CHECK_BITSTRING.h"
#include "ASN1_CHECK_BMPString.h"
#include "ASN1_CHECK_CHARACTERSTRING.h"
#include "ASN1_CHECK_ENUMERATED.h"
#include "ASN1_CHECK_GeneralizedTime.h"
#include "ASN1_CHECK_GeneralString.h"
#include "ASN1_CHECK_GraphicString.h"
#include "ASN1_CHECK_IA5String.h"
#include "ASN1_CHECK_NumericString.h"
#include "ASN1_CHECK_OCTETSTRING.h"
#include "ASN1_CHECK_PrintableString.h"
#include "ASN1_CHECK_TeletexString.h"
#include "ASN1_CHECK_UTCTime.h"
#include "ASN1_CHECK_UTF8String.h"
#include "ASN1_CHECK_VideotexString.h"
#include "ASN1_CHECK_VisibleString.h"
#include "ASN1_CHECK_BOOLEAN.h"
#include "ASN1_CHECK_NULL.h"
#include "ASN1_CHECK_OBJECTIDENTIFIER.h"
#include "ASN1_CHECK_OpenType.h"
#include "ASN1_CHECK_UniversalString.h"
#include "ASN1_CHECK_REAL.h"
#include "ASN1_Set.h"
#include "ASN1_BER_Check_Length.h"
#include "ASN1_XER_Check_Length.h"
#include "Infinite_tool.h"

#include "TYPE/ASN1_Type.h"

#include "BER/ASN1_BER_OpenType.h"
#include "BER/ASN1_BER_BITSTRING.h"
#include "BER/ASN1_BER_BMPString.h"
#include "BER/ASN1_BER_BOOLEAN.h"
#include "BER/ASN1_BER_ENUMERATED.h"
#include "BER/ASN1_BER_INTEGER.h"
#include "BER/ASN1_BER_NULL.h"
#include "BER/ASN1_BER_OCTETSTRING.h"
#include "BER/ASN1_BER_OBJECTIDENTIFIER.h"
#include "BER/ASN1_BER_REAL.h"
#include "BER/ASN1_BER_UniversalString.h"
#include "BER/ASN1_BER_RELATIVE_OID.h"
#include "BER/ASN1_BER_GeneralizedTime.h"
#include "BER/ASN1_BER_GeneralString.h"
#include "BER/ASN1_BER_GraphicString.h"
#include "BER/ASN1_BER_IA5String.h"
#include "BER/ASN1_BER_NumericString.h"
#include "BER/ASN1_BER_PrintableString.h"
#include "BER/ASN1_BER_TeletexString.h"
#include "BER/ASN1_BER_UniversalString.h"
#include "BER/ASN1_BER_UTCTime.h"
#include "BER/ASN1_BER_UTF8String.h"
#include "BER/ASN1_BER_VideotexString.h"
#include "BER/ASN1_BER_VisibleString.h"
#include "BER/ASN1_BER_ObjectDescriptor.h"	

#include "XER/ASN1_XER_UTF8String.h"
#include "XER/ASN1_XER_OpenType.h"
#include "XER/ASN1_XER_BITSTRING.h"
#include "XER/ASN1_XER_BMPString.h"
#include "XER/ASN1_XER_BOOLEAN.h"
#include "XER/ASN1_XER_ENUMERATED.h"
#include "XER/ASN1_XER_INTEGER.h"
#include "XER/ASN1_XER_OCTETSTRING.h"
#include "XER/ASN1_XER_OBJECTIDENTIFIER.h"
#include "XER/ASN1_XER_REAL.h"
#include "XER/ASN1_XER_STRING.h"
#include "XER/ASN1_XER_UniversalString.h"
#include "XER/ASN1_XER_RELATIVE_OID.h"
#include "XER/ASN1_XER_SET.h"
#include "XER/ASN1_XER_Name.h"
#include "XER/ASN1_XER_NULL.h"
#include "XER/ASN1_XER_VisibleString.h"
#include "XER/ASN1_XER_VisibleString.h"
#include "XER/ASN1_XER_UTCTime.h"
#include "XER/ASN1_XER_PrintableString.h"
#include "XER/ASN1_XER_GeneralizedTime.h"
#include "XER/ASN1_XER_GeneralString.h"
#include "XER/ASN1_XER_GraphicString.h"
#include "XER/ASN1_XER_ObjectDescriptor.h"
#include "XER/ASN1_XER_IA5String.h"
#include "XER/ASN1_XER_NumericString.h"	
#include "XER/ASN1_XER_TeletexString.h"
#include "XER/ASN1_XER_VideotexString.h"

/********************************************************
*ASN1CHARACTERSTRING_identification_syntaxes            *
********************************************************/


ASN1_CPPLINK ASNINT32 ASN1_Print_ASN1CHARACTERSTRING_identification_syntaxes(ASN1CHARACTERSTRING_identification_syntaxes* value,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_syntaxes_abstract(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_syntaxes_transfer(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 *user_value,ASNUINT32 user_value_length);

//ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes_abstract(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length);
ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes_abstract(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length);

//ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes_transfer(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length);
ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes_transfer(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value, ASN1TagType tagFlag);

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value, ASNINT32 length, ASN1TagType tagFlag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);


/********************************************************
*ASN1CHARACTERSTRING_identification_context_negotiation *
********************************************************/


ASN1_CPPLINK ASNINT32 ASN1_Print_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_context_negotiation_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,INTEGER user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_context_negotiation_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,ASNUINT32 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_context_negotiation_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,INTEGER *user_value);

//ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_context_negotiation_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length);
ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_context_negotiation_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value, ASN1TagType tagFlag);

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value, ASNINT32 length, ASN1TagType tagFlag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);


/********************************************************
*ASN1CHARACTERSTRING_identification                     *
********************************************************/

ASN1_CPPLINK ASNINT32 ASN1_Print_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASN1CHARACTERSTRING_identification_syntaxes* user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,INTEGER user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASN1CHARACTERSTRING_identification_context_negotiation* user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification_fixed(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT8 user_value);

ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASN1CHARACTERSTRING_identification_syntaxes** user_value);

//ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length);
ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,INTEGER *user_value);

ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASN1CHARACTERSTRING_identification_context_negotiation** user_value);

//ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length);
ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification_fixed(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT8 *user_value);

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value, ASN1TagType tagFlag);

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value, ASNINT32 length, ASN1TagType tagFlag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);


/********************************************************
*ASN1CHARACTERSTRING                                    *
********************************************************/

ASN1_CPPLINK ASNINT32 ASN1_Print_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASN1CHARACTERSTRING_identification* user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASN1CHARACTERSTRING_string_value(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT8 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASN1CHARACTERSTRING_identification** user_value);

ASN1_CPPLINK ASNINT32 ASN1_GET_ASN1CHARACTERSTRING_string_value(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT8 **user_value,ASNUINT32 *user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value, ASN1TagType tagFlag);

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value, ASNINT32 length, ASN1TagType tagFlag);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value);

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value);



ASN1_CPPLINK ASNINT32 ASN1_SET_CHARACTERSTRING_SEQUENCE_identification(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASN1CHARACTERSTRING_identification* user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_CHARACTERSTRING_SEQUENCE_string_value(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT8 *user_value,ASNUINT32 user_value_length);


ASN1_CPPLINK ASNINT32 ASN1_SET_CHARACTERSTRING_CHOICE_syntaxes(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,
											 ASNUINT32 *abstract_value,ASNUINT32 abstract_value_length,
											 ASNUINT32 *transfer_value,ASNUINT32 transfer_value_length);

ASN1_CPPLINK ASNINT32 ASN1_SET_CHARACTERSTRING_CHOICE_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT32 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_SET_CHARACTERSTRING_CHOICE_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,INTEGER user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_CHARACTERSTRING_CHOICE_context_negotiation(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,
														INTEGER presentation_context_id_value,
														ASNUINT32 *transfer_syntax_value,ASNUINT32 transfer_syntax_value_length);

ASN1_CPPLINK ASNINT32 ASN1_SET_CHARACTERSTRING_CHOICE_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT32 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK ASNINT32 ASN1_SET_CHARACTERSTRING_CHOICE_fixed(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT8 user_value);

ASN1_CPPLINK ASNINT32 ASN1_Print_CHARACTERSTRING(ASNUINT8* name,CHARACTERSTRING* PChstring,ASNINT32 ptab); //printf CHARACTER STRING struct


#endif
