#ifndef _ASN_TOOL_SET_H_
#define _ASN_TOOL_SET_H_


#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TYPE/ASN1_Type.h"
#include "TOOL/ASN1_Tool_Time.h"
#include <time.h>


/*SET*/
ASN1_CPPLINK ASNINT32 ASN1_SET_INTEGER(ASN1WorkSpace* ws,INTEGER *value,INTEGER user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_REAL(ASN1WorkSpace* ws,ASNREAL *value,ASNREAL user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_BOOLEAN(ASN1WorkSpace* ws,ASNBOOL *value,ASNBOOL user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_BITSTRING(ASN1WorkSpace* ws,BITSTRING *value, ASNUINT8 *user_value,ASNINT32L value_bit_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_OCTETSTRING(ASN1WorkSpace* ws,OCTETSTRING *value, ASNUINT8* user_value,ASNINT32 value_octet_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_ASNString(ASN1WorkSpace* ws,ASNSTRING *value,
							ASNUINT8 *user_value,ASNINT32 value_lenght);


#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASN1_CPPLINK ASNINT32 ASN1_SET_UTF8Str(ASN1WorkSpace* ws,UTF8Str *value, ASNUINT8 *user_value,ASNINT32 value_lenght);
#else
ASN1_CPPLINK ASNINT32 ASN1_SET_UTF8String(ASN1WorkSpace* ws,UTF8String *value, ASNUINT8 *user_value,ASNINT32 value_lenght);
#endif

ASN1_CPPLINK ASNINT32 ASN1_SET_NumericString(ASN1WorkSpace* ws,NumericString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_SET_PrintableString(ASN1WorkSpace* ws,PrintableString *value,
								  ASNUINT8 *user_value,ASNINT32 value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_SET_NormalString(ASN1WorkSpace* ws,ASNSTRING *value,
							   ASNUINT8 *user_value,ASNINT32 value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_SET_IA5String(ASN1WorkSpace* ws,IA5String *value,
							ASNUINT8 *user_value,ASNINT32 value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_SET_UTCTime(ASN1WorkSpace* ws,UTCTime *value,
						  struct tm * _time,ASNINT32 ZoneInSecond);


ASN1_CPPLINK ASNINT32 ASN1_SET_GeneralizedTime(ASN1WorkSpace* ws,GeneralizedTime *value,
								  struct tm * _time,ASNINT32 ZoneInSecond,
								  ASNINT32 second,ASNINT32 exponent);


ASN1_CPPLINK ASNINT32 ASN1_SET_VisibleString(ASN1WorkSpace* ws,VisibleString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_SET_GeneralString(ASN1WorkSpace* ws,GeneralString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_ObjectDescriptor(ASN1WorkSpace* ws,ObjectDescriptor *value,
									ASNUINT8 *user_value,ASNINT32 value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_GraphicString(ASN1WorkSpace* ws,GraphicString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_VideotexString(ASN1WorkSpace* ws,VideotexString *value,
								 ASNUINT8 *user_value,ASNINT32 value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_TeletexString(ASN1WorkSpace* ws,TeletexString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_OBJECTIDENTIFIER(ASN1WorkSpace* ws,OBJECTIDENTIFIER *value,
								   ASNUINT32 *user_value,ASNINT32 value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_RELATIVE_OID(ASN1WorkSpace* ws,RELATIVE_OID *value,
							   ASNUINT32 *user_value,ASNINT32 value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_SET_UniversalString(ASN1WorkSpace* ws,UniversalString *value,
								  ASNUINT32 *user_value,ASNINT32 value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_BMPString(ASN1WorkSpace* ws,BMPString *value,
							ASNUINT16 *user_value,ASNINT32 value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_SET_CHARACTERSTRING(ASN1WorkSpace* ws,CHARACTERSTRING *value,
								  CHARACTERSTRING *user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_ENUMERATED(ASN1WorkSpace* ws,ENUMERATED *value,ENUMERATED user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_NULL(ASN1WorkSpace* ws,ASNUINT8* value,ASNUINT8 user_value);

ASN1_CPPLINK ASNINT32 ASN1_SET_OpenType(ASN1WorkSpace* ws,OpenType *value, 
						   ASNUINT8* user_value,ASNINT32 value_lenght);

/*GET*/
ASN1_CPPLINK ASNINT32 ASN1_GET_INTEGER(ASN1WorkSpace* ws,INTEGER *value,INTEGER *user_value);

ASN1_CPPLINK ASNINT32 ASN1_GET_REAL(ASN1WorkSpace* ws,ASNREAL *value,ASNREAL *user_value);

ASN1_CPPLINK ASNINT32 ASN1_GET_BOOLEAN(ASN1WorkSpace* ws,ASNBOOL *value,ASNBOOL *user_value);

ASN1_CPPLINK ASNINT32 ASN1_GET_BITSTRING(ASN1WorkSpace* ws,BITSTRING *value,
							ASNUINT8 **user_value,ASNUINT32L *value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_GET_OCTETSTRING(ASN1WorkSpace* ws,OCTETSTRING *value,
							  ASNUINT8 **user_value,ASNUINT32 *value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_GET_ASNString(ASN1WorkSpace* ws,ASNSTRING *value,
							ASNUINT8 **user_value,ASNINT32 *value_lenght);


#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASN1_CPPLINK ASNINT32 ASN1_GET_UTF8Str(ASN1WorkSpace* ws,UTF8Str *value, ASNUINT8 **user_value,ASNINT32 *value_lenght);
#else
ASN1_CPPLINK ASNINT32 ASN1_GET_UTF8String(ASN1WorkSpace* ws,UTF8String *value, ASNUINT8 **user_value,ASNINT32 *value_lenght);
#endif

ASN1_CPPLINK ASNINT32 ASN1_GET_NumericString(ASN1WorkSpace* ws,NumericString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_GET_PrintableString(ASN1WorkSpace* ws,PrintableString *value,
								  ASNUINT8 **user_value,ASNINT32 *value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_GET_NormalString(ASN1WorkSpace* ws,ASNSTRING *value,
							   ASNUINT8 **user_value,ASNINT32 *value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_GET_IA5String(ASN1WorkSpace* ws,IA5String *value,
							ASNUINT8 **user_value,ASNINT32 *value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_GET_UTCTime(ASN1WorkSpace* ws,UTCTime *value, struct tm * _time, ASNINT32 *ZoneInSecond);


ASN1_CPPLINK ASNINT32 ASN1_GET_GeneralizedTime(ASN1WorkSpace* ws, GeneralizedTime *value, struct tm * _time, ASNINT32 *ZoneInSecond, ASNINT32 *second,ASNINT32 *exponent);


ASN1_CPPLINK ASNINT32 ASN1_GET_VisibleString(ASN1WorkSpace* ws,VisibleString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght);


ASN1_CPPLINK ASNINT32 ASN1_GET_GeneralString(ASN1WorkSpace* ws,GeneralString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_GET_ObjectDescriptor(ASN1WorkSpace* ws,ObjectDescriptor *value,
								   ASNUINT8 **user_value,ASNINT32 *value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_GET_GraphicString(ASN1WorkSpace* ws,GraphicString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_GET_VideotexString(ASN1WorkSpace* ws,VideotexString *value,
								 ASNUINT8 **user_value,ASNINT32 *value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_GET_TeletexString(ASN1WorkSpace* ws,TeletexString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght);

//ASN1_CPPLINK ASNINT32 ASN1_GET_OBJECTIDENTIFIER(ASN1WorkSpace* ws,OBJECTIDENTIFIER *value,
//								   ASNUINT32 **user_value,ASNUINT32 *value_lenght);
ASN1_CPPLINK ASNINT32 ASN1_GET_OBJECTIDENTIFIER(ASN1WorkSpace* ws,OBJECTIDENTIFIER *value,
								   ASNUINT32 user_value[128], ASNUINT32 *value_lenght);

//ASN1_CPPLINK ASNINT32 ASN1_GET_RELATIVE_OID(ASN1WorkSpace *ws, RELATIVE_OID *value, ASNUINT32 **user_value, ASNUINT32 *value_lenght);
ASN1_CPPLINK ASNINT32 ASN1_GET_RELATIVE_OID(ASN1WorkSpace *ws, RELATIVE_OID *value, ASNUINT32 user_value[128], ASNUINT32 *value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_GET_UniversalString(ASN1WorkSpace* ws,UniversalString *value,
								  ASNUINT32 **user_value,ASNUINT32 *value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_GET_BMPString(ASN1WorkSpace* ws,BMPString *value,
							ASNUINT16 **user_value,ASNUINT32 *value_lenght);

ASN1_CPPLINK ASNINT32 ASN1_GET_CHARACTERSTRING(ASN1WorkSpace* ws,CHARACTERSTRING *value,
								  CHARACTERSTRING **user_value);

ASN1_CPPLINK ASNINT32 ASN1_GET_ENUMERATED(ASN1WorkSpace* ws,ENUMERATED *value,ENUMERATED *user_value);

ASN1_CPPLINK ASNINT32 ASN1_GET_NULL(ASN1WorkSpace* ws,ASNUINT8* value,ASNUINT8 *user_value);

ASN1_CPPLINK ASNINT32 ASN1_GET_OpenType(ASN1WorkSpace* ws,OpenType *value, 
						   ASNUINT8 **user_value,ASNUINT32 *value_lenght);

#endif


