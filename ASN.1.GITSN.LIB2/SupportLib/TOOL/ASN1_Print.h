#ifndef _ASN_PRINT_H_
#define _ASN_PRINT_H_


#include "OS/ASN1_Sys.h"
#include "TOOL/ASN1_CHAR_TOOL.h"
#include "TYPE/ASN1_Type.h"

typedef int (*ASN1_PRINT_FUNC)(const char *fmt, ...);
ASN1_CPPLINK extern ASN1_PRINT_FUNC asn_printf;
ASN1_CPPLINK void ASN1_Print_setfunc(ASN1_PRINT_FUNC f);

ASN1_CPPLINK ASNINT32 ASN1_Print_INTEGER(ASNUINT8* name,INTEGER* Pint);  //printf integer value
ASN1_CPPLINK ASNINT32 ASN1_Print_INTEGER_OSUINT8(ASNUINT8* name,ASNUINT8 * Pint); //printf integer string
ASN1_CPPLINK ASNINT32 ASN1_Print_REAL(ASNUINT8* name,ASNREAL* PReal);  //printf real
ASN1_CPPLINK ASNINT32 ASN1_Print_BOOLEAN(ASNUINT8* name,ASNBOOL* PBool); //printf bool
ASN1_CPPLINK ASNINT32 ASN1_Print_BITSTRING(ASNUINT8* name,BITSTRING* PBit); //printf bitstring struct
ASN1_CPPLINK ASNINT32 ASN1_Print_OCTETSTRING(ASNUINT8* name,OCTETSTRING* POct,ASNINT32 ptab); //printf octetstring struct
ASN1_CPPLINK ASNINT32 ASN1_Print_ASNString(ASNUINT8 *type_name,ASNUINT8* name,ASNSTRING* PString); //printf string

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASN1_CPPLINK ASNINT32 ASN1_Print_UTF8Str(ASNUINT8* name,UTF8Str* PString); //printf string
#else
ASN1_CPPLINK ASNINT32 ASN1_Print_UTF8String(ASNUINT8* name,UTF8String* PString); //printf string
#endif

ASN1_CPPLINK ASNINT32 ASN1_Print_NumericString(ASNUINT8* name,ASNSTRING* PString); //printf string
ASN1_CPPLINK ASNINT32 ASN1_Print_PrintableString(ASNUINT8* name,PrintableString* PString); //printf string
ASN1_CPPLINK ASNINT32 ASN1_Print_NormalString(ASNUINT8* name,ASNSTRING* PString); //printf string
ASN1_CPPLINK ASNINT32 ASN1_Print_IA5String(ASNUINT8* name,IA5String* PString); //printf string
ASN1_CPPLINK ASNINT32 ASN1_Print_UTCTime(ASNUINT8* name,UTCTime* PString); //printf string
ASN1_CPPLINK ASNINT32 ASN1_Print_GeneralizedTime(ASNUINT8* name,GeneralizedTime* PString); //printf string
ASN1_CPPLINK ASNINT32 ASN1_Print_VisibleString(ASNUINT8* name,VisibleString* PString); //printf string
ASN1_CPPLINK ASNINT32 ASN1_Print_GeneralString(ASNUINT8* name,GeneralString* PString); //printf string
ASN1_CPPLINK ASNINT32 ASN1_Print_ObjectDescriptor(ASNUINT8* name,ObjectDescriptor* PString);
ASN1_CPPLINK ASNINT32 ASN1_Print_VideotexString(ASNUINT8* name,VideotexString* PString);
ASN1_CPPLINK ASNINT32 ASN1_Print_TeletexString(ASNUINT8* name,TeletexString* PString);
ASN1_CPPLINK ASNINT32 ASN1_Print_GraphicString(ASNUINT8* name,GraphicString* PString);

ASN1_CPPLINK ASNINT32 ASN1_Print_OBJECTIDENTIFIER(ASNUINT8* name,OBJECTIDENTIFIER* PRoid); //printf relative oid
ASN1_CPPLINK ASNINT32 ASN1_Print_RELATIVE_OID(ASNUINT8* name,RELATIVE_OID* POBJid); //printf object identifier
		 
ASN1_CPPLINK ASNINT32 ASN1_Print_UniversalString(ASNUINT8* name,UniversalString* PUnstring); //printf UniversalString struct
ASN1_CPPLINK ASNINT32 ASN1_Print_BMPString(ASNUINT8* name,BMPString* PBMPstring); //printf BMPString struct


ASN1_CPPLINK ASNINT32 ASN1_Print_ENUMERATED(ASNUINT8 *name, ASNUINT8 *named_enum_value, ENUMERATED enum_value); //printf Enum value

ASN1_CPPLINK ASNINT32 ASN1_Print_ENUMERATED_OSINT64(ASNUINT8* name,ASNUINT8* Enum,ASNINT32* PEnumval); //printf Enum value
ASN1_CPPLINK ASNINT32 ASN1_Print_ENUMERATED_OSUINT8(ASNUINT8* name,ASNUINT8* Enum,ASNUINT8* PEnumval); //printf Enum string

ASN1_CPPLINK ASNINT32 ASN1_Print_SET_OF(ASNUINT8* PSetof); //printf setof name
ASN1_CPPLINK ASNINT32 ASN1_Print_SEQ_OF(ASNUINT8* PSequenceof);//printf sequenceof name
ASN1_CPPLINK ASNINT32 ASN1_Print_SEQ(ASNUINT8* PSequence);//printf sequence name
ASN1_CPPLINK ASNINT32 ASN1_Print_SET(ASNUINT8* PSet);// printf set name
ASN1_CPPLINK ASNINT32 ASN1_Print_CHOICE(ASNUINT8* PChoice);// printf set name

ASN1_CPPLINK ASNINT32 ASN1_Print_OpenType(ASNUINT8* name,OpenType *Popentype,ASNINT32 ptab);
ASN1_CPPLINK ASNINT32 ASN1_Print_NULL(ASNUINT8* name,ASNUINT8 *ASN1NULL);		 
ASN1_CPPLINK ASNINT32 ASN1_Print_Enter(ASNINT32 count);// printf enter 
ASN1_CPPLINK ASNINT32 ASN1_Print_Space(ASNINT32 count);//printf space
ASN1_CPPLINK ASNINT32 ASN1_Print_Bracket(ASNINT32 count);//printf bracket
ASN1_CPPLINK ASNINT32 ASN_Print_TAB(ASNINT32 count);//printf table
ASN1_CPPLINK ASNINT32 ASN1_Print_Enter_Table(ASNINT32 enter, ASNINT32 table);//printf enter and table
ASN1_CPPLINK ASNINT32 ASN1_Print_BITSTRING_HtoB(ASNUINT32 value);
ASN1_CPPLINK ASNINT32 ASN1_Enum_UNKNOWN(ASNINT32 ptab);
ASN1_CPPLINK ASNINT32 ASN1_UNKNOWN(ASNINT32 ptab,ASNUINT8* un_name);

#endif


