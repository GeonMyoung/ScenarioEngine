/***************************************************************************
  Name: print function
  Copyright: 
  Author: fanyapeng
  Date: 21-04-08 13:52
  Description: printf string or value
****************************************************************************/

#include "ASN1_Print.h"
ASNINT32 ASN1_Print_INTEGER(ASNUINT8* name,ASNINT64* Pint) //printf INTEGER value
{
    printf("Integer: %s = ",name);
	printf("%I64d\n",*Pint);
	return 0;
}

ASNINT32 ASN1_Print_INTEGER_OSUINT8(ASNUINT8* name,ASNUINT8 * Pint) //printf INTEGER string
{
	printf("%s",Pint);
	return 0;
}

ASNINT32 ASN1_Print_REAL(ASNUINT8* name,REAL* PREAL) //printf REAL
{
	printf("REAL: %s = ",name);
	printf("%f\n",*PREAL);
	return 0;
}

ASNINT32 ASN1_Print_BOOLEAN(ASNUINT8* name,BOOLEAN* PBOOLEAN)//printf BOOLEAN
{
	printf("BOOLEAN: %s = ",name);
	printf("%c\n",*PBOOLEAN);
	return 0;
		
}

ASNINT32 ASN1_Print_BITSTRING(ASNUINT8* name,BITSTRING* PBit)//printf BITSTRING struct
{
	ASNUINT8* bit_current = PBit->data;
	ASNINT32 len = (PBit->numbits+7) / 8;
	printf("BITSTRING:count = %d\t %s = ",PBit->numbits,name);
//	printf("%d",PBit->numbits);
//	ASN1_Print_Space(1);
	
	while(len)
	{
		ASN1_Print_BITSTRING_HtoB(((*bit_current)>>4));
		ASN1_Print_BITSTRING_HtoB(*bit_current&0x0f);
		bit_current++;
		len--;
	}
	printf("\n");
	
	return 0;
	
}

ASNINT32 ASN1_Print_OCTETSTRING(ASNUINT8* name,OCTETSTRING* POct) //printf OCTETSTRING struct
{
	printf("OCTETSTRING:count = %d\t %s = ",POct->numbits,name);
	printf("%s",POct->data);
//	ASN1_Print_Space(1);
//	printf("%d",POct->numbits);
	return 0;
}

ASNINT32 ASN1_Print_ASNString(ASNUINT8 *type_name,ASNUINT8* name,ASNSTRING* PString) //printf string
{
	ASNINT32 i = 0;
	
	printf("%s:count = %d\t %s = ",type_name,PString->nchar,name);
	while(i<PString->nchar)
	{
		printf("%c",PString->asnstring[i]);
		i++;
	}
	printf("\n");	
	return 0;
}

ASNINT32 ASN1_Print_RELATIVE_OID(ASNUINT8* name,RELATIVE_OID* PRELATIVE_OID) //printf relative oid
{
	unsigned int F_Ui_RELATIVE_OID_Count = 0;
	printf("RELATIVE_OID:count = %u\t %s = ",PRELATIVE_OID->numids,name);
//	printf("%u",PRELATIVE_OID->numids);
	ASN1_Print_Space(1);
	while(F_Ui_RELATIVE_OID_Count < PRELATIVE_OID->numids)
	{
		printf("%u ",PRELATIVE_OID->subid[F_Ui_RELATIVE_OID_Count]);
		ASN1_Print_Space(1);
		F_Ui_RELATIVE_OID_Count++;
	}
	printf("\n");
	return 0;
}

ASNINT32 ASN1_Print_OBJECTIDENTIFIER(ASNUINT8* name,OBJECTIDENTIFIER* POBJECTIDENTIFIER) //printf object identifier
{
	unsigned int F_Ui_OID_Count = 0;
	printf("OBJECTIDENTIFIER:count = %u\t %s = ",POBJECTIDENTIFIER->numids,name);
//	printf("%u",POBJECTIDENTIFIER->numids);
//	ASN1_Print_Space(1);
	while(F_Ui_OID_Count < POBJECTIDENTIFIER->numids)
	{
		printf("%u ",POBJECTIDENTIFIER->subid[F_Ui_OID_Count]);
	//	ASN1_Print_Space(1);
		F_Ui_OID_Count++;
	}
	printf("\n");
	return 0;
}

ASNINT32 ASN1_Print_UniversalString(ASNUINT8* name,UniversalString* PUnstring) //printf UniversalString struct
{
	unsigned int F_Ui_Ustr_Count = 0;
	printf("UniversalString:count = %u\t %s = ",PUnstring->nchar,name);
//	printf("%u",PUnstring->nchar);
//	ASN1_Print_Space(1);
	while(F_Ui_Ustr_Count < PUnstring->nchar)
	{
		printf("%u ",PUnstring->data[F_Ui_Ustr_Count]);
//		ASN1_Print_Space(1);
		F_Ui_Ustr_Count++;
	}
	printf("\n");
	return 0;
}

ASNINT32 ASN1_Print_BMPString(ASNUINT8* name,BMPString* PBMPstring) //printf BMPString struct
{

	unsigned int F_Ui_Bmpstr_Count = 0;
	printf("BMPString:count = %u\t %s = ",PBMPstring->nchar,name);

//	printf("%u",PBMPstring->nchar);
	ASN1_Print_Space(1);
	while(F_Ui_Bmpstr_Count < PBMPstring->nchar)
	{
		printf("%u",PBMPstring->data[F_Ui_Bmpstr_Count]);
		ASN1_Print_Space(1);
		F_Ui_Bmpstr_Count++;
	}
	printf("\n");
	return 0;
}

ASNINT32 ASN1_Print_CHARACTERSTRING(ASNUINT8* name,CHARACTERSTRING* PChstring) //printf CHARACTER STRING struct
{
	unsigned int F_Ui_Chstr_Count = 0;
	printf("CHARACTERSTRING:count = %u\t %s = ",PChstring->numbits,name);
//	printf("%u",PChstring->numbits);
	ASN1_Print_Space(1);
	while (F_Ui_Chstr_Count <PChstring->numbits)
	{
		printf("%c ",PChstring->data[F_Ui_Chstr_Count]);
//		ASN1_Print_Space(1);
		F_Ui_Chstr_Count++;
	}
	printf("\n");
	return 0;
}
ASNINT32 ASN1_Print_ENUMERATED(ASNUINT8* Enum,ENUMERATED* PEnumval)
{
	printf("ENUMERATED:%s = ",Enum);
	ASN1_Print_Space(1);
	printf("%d\n",*PEnumval);
	return 0;
	
}

ASNINT32 ASN1_Print_ENUMERATED_OSINT64(ASNUINT8* name,ASNUINT8* Enum,ASNINT32* PEnumval)//printf Enum value
{
	printf("%s",Enum);
	ASN1_Print_Space(1);
	printf("%d",*PEnumval);
	return 0;
}

ASNINT32 ASN1_Print_ENUMERATED_OSUINT8(ASNUINT8* name,ASNUINT8* Enum,ASNUINT8* PEnumval)//printf Enum string
{
	printf("%s",Enum);
	ASN1_Print_Space(1);
	printf("%s",PEnumval);
	return 0;
}

ASNINT32 ASN1_Print_SET_OF(ASNUINT8* PSetof) //printf setof name
{
	printf("SET OF");
	ASN1_Print_Space(1);
	printf("%s",PSetof);
	ASN1_Print_Bracket(1);
	return 0;
}

ASNINT32 ASN1_Print_SEQ_OF(ASNUINT8* PSequenceof)//printf sequenceof name
{
	printf("SEQUENCE OF");
	ASN1_Print_Space(1);
	printf("%s",PSequenceof);
	ASN1_Print_Bracket(1);
	return 0;
}

ASNINT32 ASN1_Print_SEQ(ASNUINT8* PSequence)//printf sequence name
{
	printf("SEQUENCE");
	ASN1_Print_Space(1);
	printf("%s",PSequence);
	ASN1_Print_Bracket(1);
	return 0;
}

ASNINT32 ASN1_Print_SET(ASNUINT8* PSet)// printf set name
{
	printf("SET");
    ASN1_Print_Space(1);
    printf("%s",PSet);
    ASN1_Print_Bracket(1);
	return 0;
}

ASNINT32 ASN1_Print_CHOICE(ASNUINT8* PChoice)
{
	printf("CHOICE");
    ASN1_Print_Space(1);
    printf("%s",PChoice);
    ASN1_Print_Bracket(1);
	return 0;
}
ASNINT32 ASN1_Print_Enter(ASNINT32 count)// printf enter 
{
	while(0 != count)
	{
		printf("\n");
		count--;
	}
	return 0;
}

ASNINT32 ASN1_Print_Space(ASNINT32 count)//printf space
{
	while(0 != count)
	{
		printf("%c",32);
		count--;
	}
	return 0;
}

ASNINT32 ASN1_Print_Bracket(ASNINT32 count)//printf bracket
{
	switch(count)
	{
    case 1:
        printf("{\n");
        break;
    case 2:
        printf("}\n");
        break;
    case 3:
        printf("[");
        break;
    case 4:
        printf("]");
        break;
    case 5:
        printf("(");
        break;
    case 6:
        printf(")");
        break;
 }  
	return 0;
}

ASNINT32 ASN_Print_TAB(ASNINT32 count)//printf table
{
	while(0 != count)
	{
        printf("\t");
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
		printf("0000 ");
		break;
	case 1:
		printf("0001 ");
		break;
	case 2:
		printf("0010 ");
		break;
	case 3:
		printf("0011 ");
		break;
	case 4:
		printf("0100 ");
		break;
    case 5:
		printf("0101 ");
		break;
	case 6:
		printf("0110 ");
		break;
	case 7:
		printf("0111 ");
		break;
	case 8:
		printf("1000 ");
		break;
	case 9:
		printf("1001 ");
		break;
	case 10:
		printf("1010 ");
		break;
	case 11:
		printf("1011 ");
		break;
	case 12:
		printf("1100 ");
		break;
	case 13:
		printf("1101 ");
		break;
	case 14:
		printf("1110 ");
		break;
	case 15:
		printf("1111 ");
		break;
	default:
		return -1;
		break;
	}
	return 0;
}

ASNINT32 ASN1_Print_UTF8String(ASNUINT8* name,UTF8String* PString) //printf string
{
	ASN1_Print_ASNString("UTF8String",name,PString);
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
ASNINT32 ASN1_Print_UTCTime(ASNUINT8* name,UTCTime* PString) //printf string
{
	ASN1_Print_ASNString("UTCTime",name,PString);
	return 0;

}
ASNINT32 ASN1_Print_GeneralizedTime(ASNUINT8* name,ASNSTRING* PString) //printf string
{
	ASN1_Print_ASNString("GeneralizedTime",name,PString);
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

ASNINT32 ASN1_Print_OpenType(ASNUINT8* name,OpenType *Popentype)
{
	unsigned int i = 0;
	printf("OpenType");
    ASN1_Print_Space(1);
    printf("%s = ",name);

	while(i<Popentype->numocts){
		printf("%c ",Popentype->data[i]);
		i++;
	}
	printf("\n");
	return 0;
}

