/***************************************************************************
  Name: print function
  Copyright: 
  Author: fanyapeng
  Date: 21-04-08 13:52
  Description: printf string or value
****************************************************************************/

#include "ASN1_Print.h"

ASN1_PRINT_FUNC asn_printf = printf;
void ASN1_Print_setfunc(ASN1_PRINT_FUNC f)
{
	if (f != NULL) asn_printf = f;
}

ASNINT32 ASN1_Print_NULL(ASNUINT8* name,ASNUINT8 *ASN1NULL)
{
	if (name == NULL || ASN1NULL == NULL){
		return -2;
	}

	asn_printf("%s = ",name);
	asn_printf("NULL\n");
	return 0;
}

ASNINT32 ASN1_Print_INTEGER(ASNUINT8* name,ASNINT64* Pint) //printf INTEGER value
{
	if (name == NULL || Pint == NULL){
		return -2;
	}

	asn_printf("%s = ",name);
#ifdef _WIN32 
	asn_printf("%I64d\n",*Pint);
#else
	asn_printf("%lld\n",*Pint);
#endif
	return 0;
}

ASNINT32 ASN1_Print_INTEGER_OSUINT8(ASNUINT8* name,ASNUINT8 * Pint) //printf INTEGER string
{
	if (name == NULL || Pint == NULL){
		return -2;
	}
	asn_printf("%s",Pint);
	return 0;
}

ASNINT32 ASN1_Print_REAL(ASNUINT8 *name, REAL *PREAL) //printf REAL
{
//	printf("REAL: %s = ",name);
	if (name == NULL) 
		asn_printf("(unnamed) = ");
	else asn_printf("%s = ",name);

	if (PREAL == NULL) asn_printf("#error\n");
	else
	{
		ASNUINT64 temp = *(ASNUINT64 *)PREAL;
		ASNINT32 exponent = (ASNINT32)((temp >> 52) & 0x7FF) - 1023;
	
#ifdef _WIN32 
		int sign = temp & 0x8000000000000000ui64 ? 1 : 0;
		ASNUINT64 fraction = temp & 0xFFFFFFFFFFFFFui64;
		asn_printf("%lf(%d)(%c%013I64X)\n", *PREAL, exponent, sign ? '-' : '+', fraction);
#else
		int sign = temp & 0x8000000000000000LLU ? 1 : 0;
		ASNUINT64 fraction = temp & 0xFFFFFFFFFFFFFLLU;
		asn_printf("%lf(%d)(%c%013llX)\n", *PREAL, exponent, sign ? '-' : '+', fraction);
#endif
	}
	return 0;
}

ASNINT32 ASN1_Print_BOOLEAN(ASNUINT8* name,BOOLEAN* PBOOLEAN)//printf BOOLEAN
{
	if (name == NULL || PBOOLEAN == NULL){
		return -2;
	}
	asn_printf("%s = ",name);
	if(*PBOOLEAN != 0x00){
		asn_printf("TRUE\n");	
	}
	else{
		asn_printf("FALSE\n");
	}
	
	return 0;
		
}

ASNINT32 ASN1_Print_BITSTRING(ASNUINT8* name,BITSTRING* PBit)//printf BITSTRING struct
{
	ASNUINT8* bit_current;
	ASNINT32 len, cnt = 0;
	if (name == NULL || PBit == NULL) return -2;

	bit_current = PBit->data;
	len = (PBit->numbits + 7) / 8;

	asn_printf("%s(%u) = ",name, PBit->numbits);
	
	while(len)
	{	// 1 byte -> 10 letter
		ASN1_Print_BITSTRING_HtoB(((*bit_current)>>4));
		ASN1_Print_BITSTRING_HtoB(*bit_current&0x0f);
		bit_current++;
		len--;
		cnt++;
		if ((cnt & 0x7) == 0) asn_printf("\n");
	}
	if ((cnt & 0x7) != 0) asn_printf("\n");
	
	return 0;
	
}

ASNINT32 ASN1_Print_OCTETSTRING(ASNUINT8* name,OCTETSTRING* POct,ASNINT32 ptab) //printf OCTETSTRING struct
{
	ASNUINT32 i = 0;
	if (name == NULL || POct == NULL) return -2;

	asn_printf("%s = ",name);
	if (POct->numbits > 16)
	{
		asn_printf("\n");
		ASN_Print_TAB(++ptab);
	}

	while (i < POct->numbits)
	{
		if (i > 0 && i % 16 == 0)
		{
			asn_printf("\n");
			ASN_Print_TAB(ptab);
		}
		asn_printf("%02X ",POct->data[i++]);
	}
	asn_printf("\n");
	return 0;
}

ASNINT32 ASN1_Print_OpenType(ASNUINT8* name,OpenType *Popentype,ASNINT32 ptab)
{
	ASNUINT32 i = 0;
	if (name == NULL || Popentype == NULL) return -2;

	asn_printf("%s = ",name);
	if(Popentype->numocts > 16)
	{
		asn_printf("\n");
		ASN_Print_TAB(++ptab);
	}

	while(i < Popentype->numocts)
	{
		if(i > 0 && i % 16 == 0)
		{
			asn_printf("\n");
			ASN_Print_TAB(ptab);
		}
		asn_printf("%02X ",Popentype->data[i++]);
	}
	asn_printf("\n");
	return 0;
}

ASNINT32 ASN1_Print_ASNString(ASNUINT8 *type_name,ASNUINT8* name,ASNSTRING* PString) //printf string
{
	ASNINT32 i = 0;
	if (name == NULL || type_name == NULL|| PString == NULL){
		return -2;
	}
	asn_printf("%s = ",name);
	while(i<PString->nchar)
	{
		asn_printf("%c",PString->asnstring[i]);
		i++;
	}
	asn_printf("\n");	
	return 0;
}

ASNINT32 ASN1_Print_RELATIVE_OID(ASNUINT8* name,RELATIVE_OID* PRELATIVE_OID) //printf relative oid
{
	unsigned int F_Ui_RELATIVE_OID_Count = 0;
	if (name == NULL ||PRELATIVE_OID == NULL){
		return -2;
	}
	asn_printf("%s = ",name);
	ASN1_Print_Space(1);
	asn_printf("{");
	while(F_Ui_RELATIVE_OID_Count < PRELATIVE_OID->numids)
	{
		asn_printf("%u ",PRELATIVE_OID->subid[F_Ui_RELATIVE_OID_Count]);
		ASN1_Print_Space(1);
		F_Ui_RELATIVE_OID_Count++;
	}
	asn_printf("}");
	asn_printf("\n");
	return 0;
}

ASNINT32 ASN1_Print_OBJECTIDENTIFIER(ASNUINT8* name,OBJECTIDENTIFIER* POBJECTIDENTIFIER) //printf object identifier
{
	unsigned int F_Ui_OID_Count = 0;
	if (name == NULL || POBJECTIDENTIFIER == NULL){
		return -2;
	}
	asn_printf("%s = ",name);
    asn_printf("{");
	while(F_Ui_OID_Count < POBJECTIDENTIFIER->numids)
	{
		asn_printf("%u ",POBJECTIDENTIFIER->subid[F_Ui_OID_Count]);
		F_Ui_OID_Count++;
	}
	asn_printf("}");
	asn_printf("\n");
	return 0;
}

ASNINT32 ASN1_Print_UniversalString(ASNUINT8* name,UniversalString* PUnstring) //printf UniversalString struct
{
	unsigned int F_Ui_Ustr_Count = 0;
	if (name == NULL || PUnstring == NULL){
		return -2;
	}
	
	asn_printf("%s = ",name);
	while(F_Ui_Ustr_Count < PUnstring->nchar)
	{
		asn_printf("%u ",PUnstring->data[F_Ui_Ustr_Count]);
		F_Ui_Ustr_Count++;
	}
	asn_printf("\n");
	return 0;
}

ASNINT32 ASN1_Print_BMPString(ASNUINT8* name,BMPString* PBMPstring) //printf BMPString struct
{

	unsigned int F_Ui_Bmpstr_Count = 0;
	if (name == NULL || PBMPstring == NULL){
		return -2;
	}
	asn_printf("%s = ",name);
	ASN1_Print_Space(1);
	while(F_Ui_Bmpstr_Count < PBMPstring->nchar)
	{
		asn_printf("%u",PBMPstring->data[F_Ui_Bmpstr_Count]);
		ASN1_Print_Space(1);
		F_Ui_Bmpstr_Count++;
	}
	asn_printf("\n");
	return 0;
}


ASNINT32 ASN1_Print_ENUMERATED(ASNUINT8 *name, ASNUINT8 *named_enum_value, ENUMERATED enum_value)
{
	if (name == NULL) return -2;

	if (named_enum_value == NULL || named_enum_value[0] == 0)
		asn_printf("%s = %d(unnamed)\n", name, enum_value);
	else asn_printf("%s = %s(%d)\n", name, named_enum_value, enum_value);
	return 0;
	
}

ASNINT32 ASN1_Print_ENUMERATED_OSINT64(ASNUINT8* name,ASNUINT8* Enum,ASNINT32* PEnumval)//printf Enum value
{
	if (name == NULL || Enum == NULL || PEnumval == NULL){
		return -2;
	}
	asn_printf("%s",Enum);
	ASN1_Print_Space(1);
	asn_printf("%d",*PEnumval);
	return 0;
}

ASNINT32 ASN1_Print_ENUMERATED_OSUINT8(ASNUINT8* name,ASNUINT8* Enum,ASNUINT8* PEnumval)//printf Enum string
{
	if (name == NULL || Enum == NULL || PEnumval == NULL){
		return -2;
	}
	asn_printf("%s",Enum);
	ASN1_Print_Space(1);
	asn_printf("%s",PEnumval);
	return 0;
}

ASNINT32 ASN1_Print_SET_OF(ASNUINT8* PSetof) //printf setof name
{
	if (PSetof == NULL){
		return -2;
	}
	asn_printf("SET OF");
	ASN1_Print_Space(1);
	asn_printf("%s",PSetof);
	ASN1_Print_Bracket(1);
	return 0;
}

ASNINT32 ASN1_Print_SEQ_OF(ASNUINT8* PSequenceof)//printf sequenceof name
{
	if (PSequenceof == NULL){
		return -2;
	}
	asn_printf("SEQUENCE OF %s", PSequenceof);
	ASN1_Print_Bracket(1);
	return 0;
}

ASNINT32 ASN1_Print_SEQ(ASNUINT8* PSequence)//printf sequence name
{
	if (PSequence == NULL){
		return -2;
	}
	asn_printf("SEQUENCE %s", PSequence);
	ASN1_Print_Bracket(1);
	return 0;
}

ASNINT32 ASN1_Print_SET(ASNUINT8* PSet)// printf set name
{
	if (PSet == NULL){
		return -2;
	}
	asn_printf("SET");
    ASN1_Print_Space(1);
    asn_printf("%s",PSet);
    ASN1_Print_Bracket(1);
	return 0;
}

ASNINT32 ASN1_Print_CHOICE(ASNUINT8* PChoice)
{
	if (PChoice == NULL){
		return -2;
	}
	asn_printf("CHOICE");
    ASN1_Print_Space(1);
    asn_printf("%s",PChoice);
    ASN1_Print_Bracket(1);
	return 0;
}
ASNINT32 ASN1_Print_Enter(ASNINT32 count)// printf enter 
{
	while(0 != count)
	{
		asn_printf("\n");
		count--;
	}
	return 0;
}

ASNINT32 ASN1_Print_Space(ASNINT32 count)//printf space
{
	while(0 != count)
	{
		asn_printf("%c", 32);
		count--;
	}
	return 0;
}

ASNINT32 ASN1_Print_Bracket(ASNINT32 count)//printf bracket
{
	switch(count)
	{
    case 1:
        asn_printf("{\n");
        break;
    case 2:
        asn_printf("}\n");
        break;
    case 3:
        asn_printf("[");
        break;
    case 4:
        asn_printf("]");
        break;
    case 5:
        asn_printf("(");
        break;
    case 6:
        asn_printf(")");
        break;
 }  
	return 0;
}

ASNINT32 ASN_Print_TAB(ASNINT32 count)//printf table
{
	while(0 != count)
	{
        asn_printf("    ");
        count--;
    }
	return 0;
}

ASNINT32 ASN1_Print_Enter_Table(ASNINT32 enter, ASNINT32 table)//printf enter and table
{
	ASN1_Print_Enter(enter);
    ASN_Print_TAB(table);   
	return 0;
}

ASNINT32 ASN1_Print_BITSTRING_HtoB(ASNUINT32 value)
{
	switch(value)
	{
	case 0:
		asn_printf("0000 ");
		break;
	case 1:
		asn_printf("0001 ");
		break;
	case 2:
		asn_printf("0010 ");
		break;
	case 3:
		asn_printf("0011 ");
		break;
	case 4:
		asn_printf("0100 ");
		break;
    case 5:
		asn_printf("0101 ");
		break;
	case 6:
		asn_printf("0110 ");
		break;
	case 7:
		asn_printf("0111 ");
		break;
	case 8:
		asn_printf("1000 ");
		break;
	case 9:
		asn_printf("1001 ");
		break;
	case 10:
		asn_printf("1010 ");
		break;
	case 11:
		asn_printf("1011 ");
		break;
	case 12:
		asn_printf("1100 ");
		break;
	case 13:
		asn_printf("1101 ");
		break;
	case 14:
		asn_printf("1110 ");
		break;
	case 15:
		asn_printf("1111 ");
		break;
	default:
		return -1;
		break;
	}
	return 0;
}

ASNINT32 ASN1_Print_UTCTime(ASNUINT8* name,UTCTime* PString) //printf string
{
	ASNINT32 i= 0;
	ASNINT32 j = 0;
	ASNUINT8* TempS;
	if (name == NULL || PString == NULL){
		return -2;
	}

	TempS = PString->asnstring;
	asn_printf("%s = ",name);
	if (PString->nchar == 0){
		return 0;
	}
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf("-");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf("-");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf(" ");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf(":");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf(":");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	
	if(PString->nchar > 12){
		j = 0;
		while(j < PString->nchar - 12){
			asn_printf("%c",*TempS);
			TempS++;
			j++;
		}
		
	}
	asn_printf(" (UCT)");
	asn_printf("\n");
	return 0;
	
}

ASNINT32 ASN1_Print_GeneralizedTime(ASNUINT8* name,ASNSTRING* PString) //printf string
{
	ASNINT32 i= 0;
	ASNINT32 j = 0;
	ASNUINT8* TempS;

	if (name == NULL || PString == NULL){
		return -2;
	}
	TempS = PString->asnstring;
	asn_printf("%s = ",name);
	if (PString->nchar == 0){
		return 0;
	}
	while(j < 4){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf("-");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf("-");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf(" ");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf(":");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	asn_printf(":");
	j = 0;
	while(j < 2){
		asn_printf("%c",*TempS);
		TempS++;
		j++;
	}
	
	if(PString->nchar > 14){
		j = 0;
		while(j < PString->nchar - 14){
			asn_printf("%c",*TempS);
			TempS++;
			j++;
		}
	}
	asn_printf(" (GMT)");
	asn_printf("\n");
	return 0;
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_Print_UTF8Str(ASNUINT8* name, UTF8Str* PString) //printf string
#else
ASNINT32 ASN1_Print_UTF8String(ASNUINT8* name,UTF8String* PString) //printf string
#endif
{
	ASN1_Print_ASNString("UTF8Str", name, PString);
	return 0;
}
ASNINT32 ASN1_Print_NumericString(ASNUINT8* name,NumericString* PString)//printf string
{
	ASN1_Print_ASNString("NumericString",name,PString);
	return 0;

}
ASNINT32 ASN1_Print_PrintableString(ASNUINT8* name,PrintableString* PString) //printf string
{
	ASN1_Print_ASNString("PrintableString",name,PString);
	return 0;

}
ASNINT32 ASN1_Print_NormalString(ASNUINT8* name,ASNSTRING* PString) //printf string
{
	ASN1_Print_ASNString("NormalString",name,PString);
	return 0;

}
ASNINT32 ASN1_Print_IA5String(ASNUINT8* name,IA5String* PString)//printf string
{
	ASN1_Print_ASNString("IA5String",name,PString);
	return 0;

}
ASNINT32 ASN1_Print_ObjectDescriptor(ASNUINT8* name,ObjectDescriptor* PString)
{
	ASN1_Print_ASNString("ObjectDescriptor",name,PString);
	return 0;
}

ASNINT32 ASN1_Print_VideotexString(ASNUINT8* name,VideotexString* PString)
{
	ASN1_Print_ASNString("VideotexString",name,PString);
	return 0;
}

ASNINT32 ASN1_Print_TeletexString(ASNUINT8* name,TeletexString* PString)
{
	ASN1_Print_ASNString("TeletexString",name,PString);
	return 0;
}

ASNINT32 ASN1_Print_GraphicString(ASNUINT8* name,GraphicString* PString)
{
	ASN1_Print_ASNString("GraphicString",name,PString);
	return 0;
}
ASNINT32 ASN1_Print_VisibleString(ASNUINT8* name,VisibleString* PString) //printf string
{
	ASN1_Print_ASNString("VisibleString",name,PString);
	return 0;

}
ASNINT32 ASN1_Print_GeneralString(ASNUINT8* name,GeneralString* PString) //printf string
{
	ASN1_Print_ASNString("GeneralString",name,PString);
	return 0;

}

ASNINT32 ASN1_Enum_UNKNOWN(ASNINT32 ptab)
{
	return ASN1_UNKNOWN(ptab,"ENUMERATED");
}
ASNINT32 ASN1_UNKNOWN(ASNINT32 ptab,ASNUINT8* un_name)
{
	ASN_Print_TAB(ptab+1);
	asn_printf("%s Unknown Type\n",un_name);
	return 0;
}
