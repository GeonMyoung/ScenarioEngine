#include "ASN1_Tool_BitString.h"


ASN1_CPPLINK ASNINT32 HexToBitString(ASN1WorkSpace* ws,const ASNUINT8 *value,BITSTRING *bitValue)
{
	ASNINT32 i=0;
	ASNUINT32L count;			//Data Length	
	ASNUINT8 F_Uc_num;
	ASNUINT8 F_Uc_halfUp;						//high half Byte
	ASNUINT8 F_Uc_halfDown;						//low half Byte
	ASNUINT8 F_Uc_Byte;
	ASNUINT8 *F_Uc_TempStr;
	ASNUINT32 F_UI_flag;

	if (NULL == value || bitValue == NULL){
		return -34;
	}

	count = (ASNUINT32)strlen(value);
	F_UI_flag = CheckHexString(value);
	if (F_UI_flag)
	{
		return -35;
	}
	F_Uc_TempStr = mpool_malloc(ws->Pmemory,count+2);
	bitValue->data = mpool_malloc(ws->Pmemory,count/2);

	memset(F_Uc_TempStr,0,count+2);
	memset(bitValue->data,0,count/2);
	/*bitValue->numbits = (count/2)*8;*/	
	bitValue->numbits = count * 4;
	/*if ((count-1) & 0x01)*/
	if ((count) & 0x01)
	{		
		/*F_Uc_TempStr[0] = '0';*/
		strcpy(F_Uc_TempStr,value);
		F_Uc_TempStr[count] = '0';
		for(;*F_Uc_TempStr != '\0';i++)
		{				
			switch(F_Uc_TempStr[0])
			{
			case 'A':	case 'a':	F_Uc_halfUp = 0xA0;		
				break;
			case 'B':	case 'b':	F_Uc_halfUp = 0xB0;
				break;
			case 'C':	case 'c':	F_Uc_halfUp = 0xC0;
				break;
			case 'D':	case 'd':	F_Uc_halfUp = 0xD0;
				break;
			case 'E':	case 'e':	F_Uc_halfUp = 0xE0;
				break;
			case 'F':	case 'f':	F_Uc_halfUp = 0xF0;
				break;
			default:
				F_Uc_num = F_Uc_TempStr[0];
				F_Uc_halfUp = (F_Uc_num - '0') << 4;
				break;
			}
			switch(F_Uc_TempStr[1])
			{
			case 'A':	case 'a':	F_Uc_halfDown = 0x0A;
				break;
			case 'B':	case 'b':	F_Uc_halfDown = 0x0B;
				break;
			case 'C':	case 'c':	F_Uc_halfDown = 0x0C;
				break;
			case 'D':	case 'd':	F_Uc_halfDown = 0x0D;
				break;
			case 'E':	case 'e':	F_Uc_halfDown = 0x0E;
				break;
			case 'F':	case 'f':	F_Uc_halfDown = 0x0F;
				break;
			default:	
				F_Uc_num = F_Uc_TempStr[1];			
				F_Uc_halfDown = F_Uc_num - '0'; 
				break;
			}
			F_Uc_Byte = F_Uc_halfUp|F_Uc_halfDown;			
			bitValue->data[i] = F_Uc_Byte;
			F_Uc_TempStr+=2;		
		}
	}
	else
	{		
		for(;*value != '\0';i++)
		{				
			switch(value[0])
			{
			case 'A':	case 'a':	F_Uc_halfUp = 0xA0;		
				break;
			case 'B':	case 'b':	F_Uc_halfUp = 0xB0;
				break;
			case 'C':	case 'c':	F_Uc_halfUp = 0xC0;
				break;
			case 'D':	case 'd':	F_Uc_halfUp = 0xD0;
				break;
			case 'E':	case 'e':	F_Uc_halfUp = 0xE0;
				break;
			case 'F':	case 'f':	F_Uc_halfUp = 0xF0;
				break;
			default:
				F_Uc_num = value[0];
				F_Uc_halfUp = F_Uc_num - '0';
				F_Uc_halfUp<<=4;
				break;
			}
			switch(value[1])
			{
			case 'A':	case 'a':	F_Uc_halfDown = 0x0A;
				break;
			case 'B':	case 'b':	F_Uc_halfDown = 0x0B;
				break;
			case 'C':	case 'c':	F_Uc_halfDown = 0x0C;
				break;
			case 'D':	case 'd':	F_Uc_halfDown = 0x0D;
				break;
			case 'E':	case 'e':	F_Uc_halfDown = 0x0E;
				break;
			case 'F':	case 'f':	F_Uc_halfDown = 0x0F;
				break;
			default:	
				F_Uc_num = value[1];	
				F_Uc_halfDown = F_Uc_num - '0';
				break;
			}
			F_Uc_Byte = F_Uc_halfUp|F_Uc_halfDown;			
			bitValue->data[i] = F_Uc_Byte;
			value+=2;		
		}
	}
	return 0;
}


ASN1_CPPLINK ASNINT32 BitToBitString(ASN1WorkSpace* ws,const ASNUINT8 *value,BITSTRING *bitValue)
{	
	ASNUINT32 i,j = 0,k = 0;
	ASNUINT32 F_UI_flag;
	ASNUINT32L F_Ul_count;			//Data Length	
	ASNUINT32L F_Ul_quot;		//quotient	
	ASNINT8 F_Uc_rem;			//remainder
	ASNUINT32 F_UI_fill;
	
	if (NULL == value || bitValue == NULL){
		return -34;
	}

	F_Ul_count = (ASNUINT32)strlen(value);
	F_Ul_quot =  (F_Ul_count)/8;
	F_Uc_rem = (ASNINT8)((F_Ul_count) % 8);
	F_UI_fill = 8-F_Uc_rem;

	bitValue->numbits = F_Ul_count;
	F_UI_flag = CheckBitString(value);
	if (F_UI_flag)
	{
		return -36;
	}
	if (F_Uc_rem == 0)
	{		
		bitValue->data = mpool_malloc(ws->Pmemory,F_Ul_quot);
		memset(bitValue->data,0,F_Ul_quot);
	}
	else
	{
		bitValue->data = mpool_malloc(ws->Pmemory,F_Ul_quot+1);
		memset(bitValue->data,0,F_Ul_quot+1);
	}	
	while(F_Ul_quot--)
	{
		for (i = 0;i<8;i++)				// fill buffer data
			bitValue->data[j] |= (value[i]-0x30) << (7-i);	
		value += 8;
		j++;		
	}
	i = 0;		
	while (0!=F_Uc_rem)					//process remainder fill buffer data
	{	
		bitValue->data[j] |= (value[i]-48) << (7-i);
		i++;
		F_Uc_rem--;
	}	
	return 0;
}


ASN1_CPPLINK ASNINT32 BitStringToHex(ASN1WorkSpace* ws,BITSTRING bitValue,ASNUINT8 **value)
{
	ASNUINT32 i=0;
	ASNUINT8 F_UC_quot , F_Uc_rem;
	ASNUINT32 F_UI_count;

	if (value == NULL || bitValue.data == NULL){
		return -34;
	}

	F_UI_count = bitValue.numbits/8;

	if (bitValue.numbits%8 != 0){
		F_UI_count += 1;
	}
	
	*value = mpool_malloc(ws->Pmemory,F_UI_count*2+2);
	for (i=0;i<F_UI_count;i++)
	{
		F_UC_quot = bitValue.data[i] >> 4;
		if (F_UC_quot >= 0 && F_UC_quot <= 9)
		{
			F_UC_quot += 48;
		}
		else
		{
			F_UC_quot += 55;
		}
		F_Uc_rem = bitValue.data[i] & 0x0F;
		if (F_Uc_rem >= 0 && F_Uc_rem <= 9)
		{
			F_Uc_rem += 48;
		}
		else
		{
			F_Uc_rem += 55;
		}
		(*value)[2*i] = F_UC_quot;
		(*value)[2*i+1] = F_Uc_rem;
	}
	(*value)[2*i] =  'H';
	(*value)[2*i+1] = 0;
	return 0;
}

ASN1_CPPLINK ASNINT32 BitStringToBit(ASN1WorkSpace* ws,BITSTRING bitValue,ASNUINT8 **value)
{
	ASNUINT32 i=0,j;
	ASNUINT32 F_UI_count;
	ASNUINT32 F_UI_rem;

	if (value == NULL || bitValue.data == NULL){
		return -34;
	}

	F_UI_count = bitValue.numbits/8;
	F_UI_rem = bitValue.numbits % 8;
	if (F_UI_rem > 0)
	{
		F_UI_count++;
	}
	*value = mpool_malloc(ws->Pmemory,bitValue.numbits+2);
	memset(*value,0,bitValue.numbits+2);
	for (i = 0;i<F_UI_count;i++)
	{
		for (j=0;j<8;j++)
		{
			(*value)[8*i+j] = ((bitValue.data[i] & 0x80) >>7) +48; 
			bitValue.data[i] <<= 1;
			if (8*i+j >= bitValue.numbits)
			{
				break;
			}
		}
	}
	(*value)[bitValue.numbits] = 'B';
	(*value)[bitValue.numbits+1] = 0;
	return 0;
}





ASN1_CPPLINK ASNINT32 CheckHexString(const ASNUINT8 *value)
{
	ASNUINT32 k=0;
	ASNUINT32 count;

	if (NULL == value){
		return -1;
	}

	count = (ASNUINT32)strlen(value);
	while (k < count)
	{
		if (value[k] < 48 || (value[k] > 57 && value[k] < 65) || (value[k] > 70 && value[k] < 97) || value[k] > 102)
		{
			return 1;
		}
		k++;
	}
	return 0;
}




ASN1_CPPLINK ASNINT32 CheckBitString(const ASNUINT8 *value)
{
	ASNUINT32 k=0;
	ASNUINT32 count;
	if (NULL == value){
		return -1;
	}

	count = (ASNUINT32)strlen(value);
	while (k < count)
	{
		if(value[k] != '0' && value[k] != '1')
		{
			return 1;
		}
		k++;
	}
	return 0;
}
