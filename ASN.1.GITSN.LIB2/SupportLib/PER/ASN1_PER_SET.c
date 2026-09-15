#include "ASN1_PER_SET.h"

#ifdef WIN32
#pragma warning(disable:4018)
#endif


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_extLengthMoveMem(ASN1WorkSpace * ws,ASNINT32 position,ASNUINT16  bitpointer)
{
//	ASNUINT8 i;
	ASNUINT8 ch = 0;
	ASNUINT32 m_l;
	ASNUINT32 m_cl;
	ASNINT32 Biglength;
	ASNUINT8 mm = 0;
	ASNUINT8 *p_head;
	ASNUINT8 *p_cent = ws->buffer.current; 
	ASNUINT16 b_pointer = ws->buffer.bitOffset;
	ASNUINT8 zero[] = {0XFF,0xFE,0XFC,0XF8,0XF0,0XE0,0XC0,0X80,0X00};

	p_head = ws->buffer.data+position;
	Biglength = ws->buffer.current-p_head;

	if(bitpointer-b_pointer>0)
	{
		Biglength++;
	}
	
	if (Biglength < 128)
	{
		ASNUINT8 l = Biglength;
		ws->buffer.current = p_head-1;
		mm = (*ws->buffer.current)<<(8 - ws->buffer.bitOffset);
 		mm >>= (8-ws->buffer.bitOffset);

		ws->buffer.bitOffset = bitpointer;
		if (l)
		{
			ASN1_FillBuffer(ws,&l,8,UNALIGN);
			ws->buffer.current = p_cent;
		}
		else
		{
			l=1;
			ASN1_FillBuffer(ws,&l,8,UNALIGN);
			ASN1_FillBuffer(ws,&ch,8,UNALIGN);
			ws->buffer.current = p_cent+1;
		}
		
		
		ws->buffer.bitOffset = b_pointer;
	}
	else if(Biglength >= 128 && Biglength <= 16383)
	{
		ASNUINT8 sh[2];
		if (ws->buffer.end <= ws->buffer.current+1)
		{
			m_l = ws->buffer.current-ws->buffer.data;
			m_cl = ws->buffer.end - ws->buffer.data;
			ws->buffer.data = mpool_realloc(ws->Pmemory,ws->buffer.data,ws->buffer.end
				-ws->buffer.data+5120);
			ws->buffer.end = ws->buffer.data+m_cl;
			ws->buffer.current = ws->buffer.data+m_l;
		}
		ws->buffer.current = p_head;
		mm = (*ws->buffer.current)<<(8 - ws->buffer.bitOffset);
 		mm >>= (8-ws->buffer.bitOffset);

		/*memmove(ws->buffer.current+2,ws->buffer.current+1,Biglength+1);*/
		memmove(ws->buffer.current+2,ws->buffer.current+1,Biglength+1);
		sh[0] = 0x80 | Biglength/256;
		sh[1] = Biglength%256;
		ws->buffer.current-=1;
		ws->buffer.bitOffset = bitpointer;
		ASN1_FillBuffer(ws,&sh[0],8,UNALIGN);
		ASN1_FillBuffer(ws,sh+1,8,UNALIGN);

		*ws->buffer.current &= zero[ws->buffer.bitOffset];
		*ws->buffer.current|=mm;

		ws->buffer.current = p_cent+1;
		ws->buffer.bitOffset = b_pointer;
	}
	else
	{
		ASNINT32 i;
		ASNINT32 j;
		ASNINT32 lc;
		ASNUINT8 *zc;
		ASNINT32 move_byte_count; 
		ASNUINT8 degree;
		ASNINT32 residual_length;
		ASNUINT8 *p_residual_head;
		ASNUINT8 *p_partition;
		ASNINT32 partition_length;
		ASNUINT8 parcel_num;
		ASNUINT8 cx;
		degree = (Biglength+65535)>>16;
		residual_length = Biglength % 16384;
		if (residual_length >=128)
		{
			lc = 2;
			zc = mpool_malloc(ws->Pmemory,2*sizeof(ASNINT8));
			zc[0] = 0x80 | residual_length/256;
			zc[1] = residual_length%256;
		}
		else
		{
			lc = 1;
			zc = mpool_malloc(ws->Pmemory,1*sizeof(ASNINT8));
			zc[0] = residual_length;
		}
		move_byte_count = degree+lc-1;
		if (ws->buffer.end <= ws->buffer.current+move_byte_count)
		{
			m_l = ws->buffer.current-ws->buffer.data;
			m_cl = ws->buffer.end - ws->buffer.data;
			ws->buffer.data = mpool_realloc(ws->Pmemory,ws->buffer.data,ws->buffer.end
				-ws->buffer.data+5120);
			ws->buffer.end = ws->buffer.data+m_cl;
			ws->buffer.current = ws->buffer.data+m_l;
		}

		p_residual_head = ws->buffer.current-residual_length+move_byte_count;
		memmove(p_residual_head+lc,ws->buffer.current-residual_length+1,residual_length);
		
		ws->buffer.current=p_residual_head-1;
		ws->buffer.bitOffset = bitpointer;
		ASN1_FillBuffer(ws,zc,lc*8,UNALIGN);
 		ws->buffer.current=p_cent;
 		ws->buffer.bitOffset = b_pointer;
		
		partition_length = Biglength-residual_length;
		j = degree;
		for (i=degree;i>0;i--)
		{
			parcel_num = (partition_length % 65536)>>14&0x03;
			if (!parcel_num)
			{
				parcel_num = 4;
			}
			cx = 0xC0|parcel_num;
			p_partition = p_head  +degree+partition_length-16384*parcel_num;

			memmove(p_partition,p_partition-degree +1,16384*parcel_num);


			ws->buffer.current = p_partition-1;
			ws->buffer.bitOffset = bitpointer;
			if (!bitpointer)
			{
				ws->buffer.current--;
			}
			ASN1_FillBuffer(ws,&cx,8,UNALIGN);
			ws->buffer.current = p_cent;			
			ws->buffer.bitOffset = b_pointer;
			degree--;
			partition_length -= 16384*parcel_num;
		}		
		ws->buffer.current = p_cent+move_byte_count;
	}
	
	ws->buffer.bitOffset = b_pointer;
	ASN1_FillBuffer(ws,&ch,b_pointer-bitpointer+(bitpointer>b_pointer)*8,UNALIGN);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_extLengthMoveMem(ASN1WorkSpace * ws,ASNUINT32 position,ASNUINT16  bitpointer)
{	
	ASNINT32 length = 0;
	length = ASN1_PER_Align_Enc_extLengthMoveMem(ws,position,bitpointer);
	return length;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_extLengthMoveMem(ASN1WorkSpace * ws,ASNINT32* movelength,ASNUINT8*  bitpointer)
{
	ASNUINT8 ch;
	ASNINT32 length = 0;
	ASNINT32 ret = 0;
	if(0>ASN1_ReadBuffer(ws,&ch,ws->buffer.bitOffset,UNALIGN))
		return ret;
	length = ASN1_PER_UNAlign_Dec_extLengthMoveMem(ws,movelength,bitpointer);
	if (0>length)
		return ASN1_PER_CHECK_LENGTH_ERROR;
	return length;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_extLengthMoveMem(ASN1WorkSpace * ws,ASNINT32* movelength,ASNUINT8*  bitpointer)
{
	ASNINT32 count=0;
	ASNUINT8 *p_cent = ws->buffer.current;
	ASNUINT32 temp_bitOffset = ws->buffer.bitOffset;
	ASNUINT8 *length;
//	ASNUINT32 total;
	ASNUINT32 total = 0; // Jake Lin : 2013.04.02
	ASNUINT8 cp;
	ASNUINT8 mm = 0;
	ASNINT32 ret = 0;
	ASNUINT8 zero[] = {0XFF,0xFE,0XFC,0XF8,0XF0,0XE0,0XC0,0X80,0X00};
	
 	mm = (*ws->buffer.current)>>(ws->buffer.bitOffset);
 	mm <<= (ws->buffer.bitOffset);
	
//	mm = (*ws->buffer.current)<<(8-ws->buffer.bitOffset)>>(8-ws->buffer.bitOffset);
	if(0>ASN1_ReadBuffer(ws,&cp,8,UNALIGN))
		return ret;
	
	
	ws->buffer.current--;
	
	if(cp<128)
	{
		length = mpool_malloc(ws->Pmemory,1*sizeof(ASNINT8));			
		if(0>ASN1_ReadBuffer(ws,length,8,UNALIGN))
			return ret;
 		mm = (*ws->buffer.current)<<(8 - ws->buffer.bitOffset);
 		mm >>= (8-ws->buffer.bitOffset);
		memmove(ws->buffer.current,ws->buffer.current+1,*length);/*error:no need to move memory.*/
//		ws->buffer.current[*length-1] &= ~(~0<<ws->buffer.bitOffset);
		count++;
		total = *length;
	}
	else if((cp&0xC0) == 0xC0)
	{
		ASNUINT8 cx;		
		while (1)
		{
			ws->buffer.current+=count;				
			count++;
			if(0>ASN1_ReadBuffer(ws,&cx,8,UNALIGN))
				return ret;
			ws->buffer.current--;
			if (cx<128)
			{			
				length = mpool_malloc(ws->Pmemory,1*sizeof(ASNINT8));
				if(0>ASN1_ReadBuffer(ws,length,8,UNALIGN))
					return ret;
				memmove(ws->buffer.current,ws->buffer.current+1,*length);
				total += *length;
				break;
			}
			else if((cx&0xC0) == 0x80)
			{
				length = mpool_malloc(ws->Pmemory,2*sizeof(ASNINT8));
				if(0>ASN1_ReadBuffer(ws,length,16,UNALIGN))
					return ret;
				*length = *length<<8|*(length+1);
				memmove(ws->buffer.current,ws->buffer.current+2,*length);
				count++;
				total += *length;
				break;
			}
			else
			{
				cx &= 0x07;
				memmove(ws->buffer.current,ws->buffer.current+count,16384*cx);
				ws->buffer.current+=16384*cx ;
				total += 16384*cx;
			}		
		}
	}
	else
	{
		length = mpool_malloc(ws->Pmemory,2*sizeof(ASNINT8));
		if(0>ASN1_ReadBuffer(ws,length,16,UNALIGN))
			return ret;
 		mm = (*ws->buffer.current)<<(8 - ws->buffer.bitOffset);
 		mm >>= (8-ws->buffer.bitOffset);

		// mm = (*ws->buffer.current)<<(8-ws->buffer.bitOffset)>>(8-ws->buffer.bitOffset);
		total = 0;
		total = *length & 0x3f;
		total <<= 8;
		total += *(length+1);
// 		*length = (*length<<8|(*(length+1)))&0x3FFF;
		ws->buffer.current = p_cent;
		if (0==temp_bitOffset){
			ws->buffer.current++;
		}
		if (temp_bitOffset == 0){
			memmove(ws->buffer.current,ws->buffer.current+2,total);
		}
		else{
			memmove(ws->buffer.current,ws->buffer.current+2,total+1);
		}
		
		count+=2;
/*		total = *length;*/
	}
	*movelength = count;
	ws->buffer.current = p_cent;
	*ws->buffer.current &= zero[ws->buffer.bitOffset];
	*ws->buffer.current|=mm;
	*bitpointer = ws->buffer.bitOffset;
	return total;
}


ASN1_CPPLINK ASNINT32 ASN1_FillAndMoveMem(ASN1WorkSpace * ws,ASNINT32* movelength,ASNUINT8*  bitpointer)
{
	ASNUINT8 fill0;
	ASNUINT8 *fillByte;
	ASNINT32 ret = 0;
	fillByte = malloc(*movelength*(sizeof(ASNINT8)));
	if (ws->buffer.bitOffset - *bitpointer<0)
	{
		if(0>ASN1_ReadBuffer(ws,&fill0,ws->buffer.bitOffset-*bitpointer+8,UNALIGN)){
			free(fillByte);
			return ret;
		}
			
	}
	else
	{
		if(0>ASN1_ReadBuffer(ws,&fill0,ws->buffer.bitOffset-*bitpointer,UNALIGN))
		{
			free(fillByte);
			return ret;
		}
	}
	if(0>ASN1_ReadBuffer(ws,fillByte,*movelength*8,UNALIGN))
	{
		free(fillByte);
		return ret;
	}
	free(fillByte);
	return 0;
}

		 
		 
ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_extOption(ASN1WorkSpace * ws,ASN1PERAlign Align_Flag,ASNINT32 count)
{        
	Asn1ConsInfo enuminfo;
//	Asn1ConsInfo bitinfo;
//	int i;
	ASNUINT8 ch;
//	ASNUINT64 e = *value;	
	BITSTRING* bit_value;

	enuminfo.lower = 0;
	enuminfo.upper = 64;
	enuminfo.extflag = 0;
	enuminfo.charSet = 0;
	enuminfo.consType = CONS;
	enuminfo.BitVector = 0;
	bit_value = mpool_malloc(ws->Pmemory,sizeof(bit_value));
	bit_value->data = mpool_malloc(ws->Pmemory,(count+7)/8);
	bit_value->numbits = count;
	memset(bit_value->data,0x00,(count+7)/8);

	if (count <= 64){

		ASN1_PER_UNAlign_Enc_ENUMERATED_child(ws,count-1,0,&enuminfo);

		ch = 0; 

		ASN1_FillBuffer(ws,bit_value->data,count,UNALIGN);
	} 
	else{
		 
		enuminfo.consType = UNCONS;
		if (Align_Flag == ALIGN){
			ch = 0x80;
			ASN1_FillBuffer(ws,&ch,8,ALIGN);
		} 
		else{
			ch = 0x1;
			ASN1_FillBuffer(ws,&ch,1,UNALIGN);		
		}
		ASN1_PER_UNAlign_Enc_BITSTRING(ws,bit_value,&enuminfo);
	}

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_extOption(ASN1WorkSpace * ws, 
								ASN1PERAlign Align_Flag,
								ASNINT32 * extcount,ASNUINT8 ** extvalue)
{
	Asn1ConsInfo enuminfo;
//	int i;
	ASNUINT8 ch,numflag=0;
	ASNUINT8 t=0;
	ASNINT64 count=0;
	BITSTRING bit_value;
	ASNUINT8 *temp_extvalue;
	ASNINT16 temp_byte = 0;

	enuminfo.lower = 0;
	enuminfo.upper = 63;
	enuminfo.extflag = 0;
	enuminfo.charSet = 0;
	enuminfo.consType = CONS;
// 	if (ch == 1){
// 		numflag =1;
// 	}
// 	else{
// 			
// 	}
// 	if(ch==0 || Align_Flag == ALIGN || ws->buffer.bitOffset !=7)
// 	{
// 		ASN1_ReadBuffer(ws,&ch,1,ALIGN);
// 	}
	if(0>ASN1_ReadBuffer(ws,&ch,1,UNALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	if (ch != 0)
	{
		numflag = 1;
	}
	if (numflag)
	{
		enuminfo.consType = UNCONS;
		if (Align_Flag == ALIGN)
		{
		 	ASN1_PER_Align_Dec_BITSTRING(ws,&bit_value,&enuminfo);
			*extcount = bit_value.numbits;
			
		} 
		else
		{
		 	ASN1_PER_UNAlign_Dec_BITSTRING(ws,&bit_value,&enuminfo);
			*extcount = bit_value.numbits;
 		}
		*extvalue = bit_value.data;
	} 
	else
	{
		ASN1_PER_UNAlign_Dec_ENUMERATED_child(ws,extcount,&t,&enuminfo);
		*extcount += 1;
		*extvalue =mpool_malloc(ws->Pmemory,(*extcount+7)/8);
		if(0>ASN1_ReadBuffer(ws,*extvalue,*extcount,UNALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		temp_extvalue = *extvalue;
		if ((*extcount%8))
			temp_byte += *extcount/8+1;
		else
			temp_byte+= *extcount/8;
	
		temp_extvalue += (temp_byte-1);
		if (*extcount%8){
			(*temp_extvalue) <<= 8-(*extcount%8);
		}
		
	}

	return 0;
}



ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_Opt_Def_bit(ASN1WorkSpace * ws,ASNINT32 extcount,ASNUINT8 ** extvalue)
{
	ASNUINT8 *temp_extvalue;
	ASNINT16 temp_byte = 0;

	*extvalue =mpool_malloc(ws->Pmemory,(extcount + 7 ) / 8);
	if(0>ASN1_ReadBuffer(ws,*extvalue,extcount,UNALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;

	temp_extvalue = *extvalue;
	if (extcount%8)
		temp_byte += extcount/8+1;
	else
		temp_byte+= extcount/8;
	
	temp_extvalue += (temp_byte-1);
	if (extcount%8){
		(*temp_extvalue) <<= 8-(extcount%8);
	}
	return 0;
}



ASNINT32 ASN1_PER_CheckExtBit(ASNUINT8 *extvalue, ASNINT32 bitindex)
{
	ASNUINT32 byte_idx = 0;
	ASNUINT32 bit_idx = 0;
	ASNUINT8 target_byte;

	byte_idx = (bitindex - 1) / 8;
	bit_idx = bitindex % 8;

	target_byte = *(extvalue + byte_idx);

	if (bit_idx != 0) target_byte >>= (8 - bit_idx);
	bit_idx = (1 & target_byte);
	return bit_idx;

}

ASNINT32 ASN1_PER_Enc_SetExtIndex(ASN1WorkSpace *ws, ASN1PERAlign Align_Flag, ASNINT32 bit, ASNUINT16 pointer, ASNUINT32 extindex, ASNUINT32 extcount)
{
	ASNINT32 tmpextcount,extbytecount=0;
	ASNUINT8 *currentbit;
	ASNUINT16 currentpointer;
	ASNINT32 temp_bit = 0;
	ASNUINT8 ch = 1;
	currentbit = ws->buffer.current;
	currentpointer = ws->buffer.bitOffset;

	ws->buffer.current =  ws->buffer.data+bit;
	ws->buffer.bitOffset = pointer;
// 	if (Align_Flag == ALIGN)
// 	{
// 		if(ws->buffer.bitOffset != 0)
// 		{
// 			ws->buffer.bitOffset = 0;
// 			// ws->buffer.current = ws->buffer.current + 1;
// 		}
// 
// 	}
// 	

	if (extcount <= 64)
	{
// 		if(ws->buffer.bitOffset ==0)
// 		{
// 			if (extindex <= 8){
// 				temp_bit = extindex
// 			}
// 			
// 			ws->buffer.bitOffset = extindex/8;
// 			// ws->buffer.current = ws->buffer.current + 1;
// 		}
		if (ws->buffer.bitOffset == 0){
			ws->buffer.current += 1;
			ws->buffer.bitOffset = 1;
			temp_bit = 1;
		}

		if (ws->buffer.bitOffset <= 7 && temp_bit != 1){
			ws->buffer.current += 1;
			ws->buffer.bitOffset = 8 - (7-ws->buffer.bitOffset);
			temp_bit = 0;
		}

		if (extindex > ws->buffer.bitOffset){
			
// 		}
// 		else{
			ws->buffer.current += (extindex - ws->buffer.bitOffset)/8;
			if ((extindex - ws->buffer.bitOffset)<8 || 
				(extindex - ws->buffer.bitOffset)%8 !=0){
				
				ws->buffer.current += 1;
			}
			if ((extindex - ws->buffer.bitOffset)%8 == 0){
				ws->buffer.bitOffset = 1;
			}
			else{
				ws->buffer.bitOffset = 8-(extindex - ws->buffer.bitOffset)%8+1;
			}
		}
		else{
			ws->buffer.bitOffset = ws->buffer.bitOffset+1 - extindex;
		}

		
		

// 		ws->buffer.current = ws->buffer.current + ( ws->buffer.bitOffset + 7 + extindex - 1) / 8;
// 		ws->buffer.bitOffset =  ws->buffer.bitOffset - ( 7 + extindex - 1) % 8;
// 		if (ws->buffer.bitOffset < 0)
// 		{

// 			ws->buffer.bitOffset = ws->buffer.bitOffset + 8;
// 		}
	} 
	else
	{
		tmpextcount = extcount;
		if(Align_Flag == ALIGN){
			
			do 
			{
				extbytecount = extbytecount + tmpextcount / 65536 ;
				tmpextcount = tmpextcount - extbytecount * 65536;
				
				if (tmpextcount >= 16384 && tmpextcount < 65536)
				{
					extbytecount = extbytecount + 1;
					tmpextcount = tmpextcount % 16384;
				}

				if (tmpextcount < 128)
				{
					ws->buffer.current = ws->buffer.current + extbytecount + 2 + extindex / 8 ;
				}
				else if(tmpextcount <= 16383)
				{
					ws->buffer.current = ws->buffer.current + extbytecount + 3 + extindex / 8 ;
					
				}


			}while (tmpextcount>16383);
			
			if ((ws->buffer.bitOffset+1) < extindex % 8){
				ws->buffer.bitOffset = ws->buffer.bitOffset + 8;
				ws->buffer.current += 1;
			}
			ws->buffer.bitOffset = ws->buffer.bitOffset - extindex % 8 +1;
// 			if (ws->buffer.bitOffset < 0)
// 			{
// 				ws->buffer.bitOffset =8;
// 			}

		} 
		else
		{
			do 
			{
				extbytecount = extbytecount + tmpextcount / 65536;
				tmpextcount = tmpextcount - extbytecount * 65536;
				if (tmpextcount >= 16384 && tmpextcount < 65536)
				{
					extbytecount = extbytecount +1;
					tmpextcount = tmpextcount % 16384;
				}
				if (tmpextcount < 128)
				{
					ws->buffer.current = ws->buffer.current + extbytecount + 1 + extindex / 8 ;
				}
				else if(tmpextcount <= 16383)
				{
					ws->buffer.current = ws->buffer.current + extbytecount + 2 + extindex / 8 ;
					
				}
				
			}while (tmpextcount>16383);

			if ((ws->buffer.bitOffset+1) < extindex % 8){
				 ws->buffer.bitOffset = ws->buffer.bitOffset + 8;
			}
			ws->buffer.bitOffset =  ws->buffer.bitOffset - extindex % 8;
			
// 			if (ws->buffer.bitOffset < 0)
// 			{
// 				ws->buffer.current = ws->buffer.current +1;
// 				ws->buffer.bitOffset = ws->buffer.bitOffset + 8;
// 			}
		}
	}
		
		ASN1_FillBuffer(ws,&ch,1,UNALIGN);
		ws->buffer.current = currentbit;
		ws->buffer.bitOffset = currentpointer;
		return 0;


}


ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_unKnown(ASN1WorkSpace * ws,ASN1PERAlign Align_Flag)
{
	ASNUINT8 ch;
	ASNUINT16 buflength;
	if(0>ASN1_ReadBuffer(ws,&ch,8,Align_Flag))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	while (1)
	{
		if (ch <= 192)
		{
			break;
		}
		ws->buffer.current = ws->buffer.current + 16384 * (ch - 192);
		if(0>ASN1_ReadBuffer(ws,&ch,8,Align_Flag))
			return ASN1_PER_CHECK_LENGTH_ERROR;
			
	}
	if (ch >= 128)
	{
		buflength = (ch-128) * 256;
		if(0>ASN1_ReadBuffer(ws,&ch,8,Align_Flag))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		buflength = buflength + ch;
		ws->buffer.current = ws->buffer.current + buflength;
			
	} 
	else
	{
		ws->buffer.current = ws->buffer.current + ch;
	}
	return 0;
	 

}


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_WirteBuffer(ASN1WorkSpace *ws)
{
	ASNUINT8 ch;
	ch = 0;
	ASN1_FillBuffer(ws,&ch,8,ALIGN);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_WirteBuffer(ASN1WorkSpace *ws)
{
	ASNUINT8 ch;
	ch = 0;
	ASN1_FillBuffer(ws,&ch,8,UNALIGN);
	return 0;
}



ASNINT32 ASN1_SaveCurrentPointer(ASN1WorkSpace *ws, ASNINT32 *bytePointer, ASNUINT16 *bitPointer)
{
	*bytePointer = ws->buffer.current-ws->buffer.data;
	*bitPointer = ws->buffer.bitOffset;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_GetIndex(ASNINT64 value,ASNUINT8 *index)
{
	ASNUINT8 count=0;
	while (value>>=1){
		count++;
	}	
	*index = count++;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_GetM(ASNINT64 *value,ASNINT32 index)
{
// 	ASNUINT8 ch = 1;
// 	*value = ch<<index;
	*value = index; 
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_bit(ASN1WorkSpace *ws,ASNBOOL value)
{
	ASN1_FillBuffer(ws, &value, 1, UNALIGN);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_bit(ASN1WorkSpace *ws,ASNINT64* value,ASNINT32 length)
{
	ASNINT8 i;
	ASNUINT8 ch[8] = { 0, };
//	memset(ch,0,8);

	*value = 0;
	if (0 > ASN1_ReadBuffer(ws, ch, length, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;

	if (length & 7) ch[(length + 7) / 8 - 1] <<= 8 - (length & 7);

	for (i=0; i < (length + 7) / 8; i++)
	{
		*value <<= 8;
		*value |= ch[i];		
	}

	if (length & 7) *value >>= 8 - (length & 7);

	ASN1_PER_turn_M(value, length);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_extbit(ASN1WorkSpace *ws, ASNUINT64 value)
{
	ASNUINT8 ch;
	if (value > 0) ch = 1; else ch = 0;
	ASN1_FillBuffer(ws, &ch, 1, UNALIGN);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_extbit(ASN1WorkSpace *ws, ASNBOOL *value)
{
	if (0 > ASN1_ReadBuffer(ws, value, 1, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_turn_M(ASNUINT64 *value,ASNINT32 len)
{
	ASNUINT8 i;
	ASNUINT64 num = *value;
	for (*value = 0, i = 1; i < len + 1; i++)
	{
		*value |= (num & 1) << (len - i);
		num >>= 1;
	}

	return 0;
}

ASNINT32 ASN1_PER_Align_Enc_Set_Seq_Of_Length(ASN1WorkSpace *ws, ASNINT32 *allLength, ASNINT32 *length, Asn1ConsInfo *consinfo)
{
	struct PER_Flag per_flag;
	ASN1PERAlign align_flag;

	ASNINT32 sever_flag = 1;
	ASNINT32 ret = 0;
	ASNINT32 Default_bit = 255;

	per_flag.Range = 0;
	per_flag.Value_length = *allLength;
	*length=*allLength;

	ret = PER_CONSTRAINT_Enc_Process(ws, consinfo, &Default_bit, &per_flag, ALIGN);
	if (ret < 0) return ret;

	if ((per_flag.ext_flag == 1) && (per_flag.Value_length >= 16384))
		return ASN1_PER_Enc_SeverLength(ws, allLength, NULL, length, ALIGN);

	if (per_flag.Range == 1 && per_flag.L_En_Flag == 0)
	{
		if (consinfo->extflag == 1)
		{
			align_flag = UNALIGN;
			if (per_flag.ext_flag == 1)
			{
				align_flag = ALIGN;
				ASN1_PER_Enc_ExtLength(ws, per_flag.Value_length, consinfo, &per_flag, ALIGN);
			}
		}
		else align_flag = ALIGN;
		return 0;
	}
	
	if (per_flag.Is_Size == 1)
	{
		align_flag = ALIGN;
		if ((per_flag.Value_length <= consinfo->upper) && (per_flag.Value_length >= consinfo->lower))
		{
			if (per_flag.Range < 256)					align_flag = UNALIGN;
		}

		ASN1_PER_Enc_strLength(ws, per_flag.Value_length, consinfo, &per_flag, align_flag);

		align_flag = ALIGN;
		if ((per_flag.Value_length <= consinfo->upper) && (per_flag.Value_length >= consinfo->lower))
		{
			if ((consinfo->upper * Default_bit) >= 16)	align_flag = ALIGN;
			else										align_flag = UNALIGN;
		}
	}
	else
	{
		while (sever_flag)
		{	
			return ASN1_PER_Enc_SeverLength(ws, allLength, NULL, length, ALIGN);
		}
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_Set_Seq_Of_Length(ASN1WorkSpace *ws, ASNINT32 *allLength, ASNINT32 *length, Asn1ConsInfo *consinfo)
{
	struct PER_Flag per_flag;

	ASNINT32 sever_flag = 1;

	ASNINT32 ret = 0;
	ASNINT32 Default_bit=255;
	per_flag.Range = 0;
	per_flag.Value_length =  *allLength;

	*length = *allLength;
	
	if ((ret = PER_CONSTRAINT_Enc_Process(ws,consinfo,&Default_bit,&per_flag,UNALIGN)) < 0) return ret;

	if ((per_flag.ext_flag == 1) && (per_flag.Value_length >= 16384))
			return ASN1_PER_Enc_SeverLength(ws, allLength, NULL, length, UNALIGN);
	
	if (per_flag.Range == 1 && per_flag.L_En_Flag == 0)
	{
		if (per_flag.ext_flag == 1)
			ASN1_PER_Enc_ExtLength(ws, per_flag.Value_length, consinfo, &per_flag, UNALIGN);

		return 0;
	}
	
	if(per_flag.Is_Size == 1) ASN1_PER_Enc_strLength(ws, per_flag.Value_length, consinfo, &per_flag, UNALIGN);
	else return ASN1_PER_Enc_SeverLength(ws, allLength,consinfo, length, UNALIGN);

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_Set_Seq_Of_Length(ASN1WorkSpace *ws,ASNINT32 *length,
											  Asn1ConsInfo *consinfo)
{
	struct PER_Flag per_flag;
	ASN1PERAlign align_flag;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	
	ASNUINT8* temp_current;
	ASNUINT16 temp_bitOffset;
	ASNINT32  temp_loop_i = 0;
	ASNINT32 flag = 0;
	ASNINT32 Default_bit=255;

	per_flag.Range = 0;
	per_flag.PER_Dec_Len = 1;


	ret = PER_CONSTRAINT_Dec_Process(ws,consinfo,&Default_bit,&per_flag,ALIGN);
	if (ret<0){
		return ASN1_PER_CHECK_LENGTH_ERROR;
	}

	if (per_flag.ext_flag == 1){
		temp_value_length = 0;
		temp_current = ws->buffer.current;
		temp_bitOffset = ws->buffer.bitOffset;
		temp_loop_i++;
		flag = ASN1_PER_Dec_SeverLength(ws,NULL,
			                            &per_flag,ALIGN);
		if(0>flag)
			return ASN1_PER_CHECK_LENGTH_ERROR;
		if ((temp_loop_i == 1)&&(flag == 0)){
			ws->buffer.current = temp_current;
			ws->buffer.bitOffset = temp_bitOffset;
			flag = 1;
		}
		else{
			*length = per_flag.PER_Dec_Len;
			return flag;
		}
	}

	if(per_flag.Range == 1 && per_flag.L_En_Flag == 0){
		if (consinfo->extflag == 1){
			align_flag = UNALIGN;
			if (per_flag.ext_flag == 1){
				align_flag = ALIGN;
				if(0>ASN1_PER_Dec_ExtLength(ws,consinfo,&per_flag,ALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
				*length = per_flag.PER_Dec_Len;
			}
		}
		else{
			align_flag = ALIGN;
		}
		*length = per_flag.PER_Dec_Len;
		return 0;
	}
	
	if(per_flag.Is_Size == 1){
	
		align_flag = ALIGN;
		if (per_flag.Range < 256){
			align_flag = UNALIGN;
		}
			if(0>ASN1_PER_Dec_strLength(ws,consinfo,&per_flag,align_flag))
				return ASN1_PER_CHECK_LENGTH_ERROR;

		align_flag = ALIGN;
		if ((per_flag.PER_Dec_Len <= consinfo->upper) && 
			(per_flag.PER_Dec_Len >= consinfo->lower)){
			if ((consinfo->upper * Default_bit) >= 16)
				align_flag = ALIGN;
			else
				align_flag = UNALIGN;
		}

		*length = per_flag.PER_Dec_Len;
	}
	else{
		flag = ASN1_PER_Dec_SeverLength(ws,NULL,&per_flag,ALIGN);
		if(0>flag)
			return ASN1_PER_CHECK_LENGTH_ERROR;
		*length = per_flag.PER_Dec_Len;
		return flag;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(ASN1WorkSpace *ws, ASNINT32 *length,
												Asn1ConsInfo *consinfo)
{
	struct PER_Flag per_flag;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	
	ASNUINT8* temp_current;
	ASNUINT16 temp_bitOffset;
	ASNINT32  temp_loop_i = 0;
	ASNINT32 flag;
	ASNINT32 Default_bit=255;
	per_flag.Range = 0;

	ret = PER_CONSTRAINT_Dec_Process(ws,consinfo,&Default_bit,&per_flag,UNALIGN);
	if (ret<0){
		return ASN1_PER_CHECK_LENGTH_ERROR;
	}

	if (per_flag.ext_flag == 1){
		temp_value_length = 0;
		temp_current = ws->buffer.current;
		temp_bitOffset = ws->buffer.bitOffset;
		temp_loop_i++;
		flag = ASN1_PER_Dec_SeverLength(ws,consinfo,
								        &per_flag,UNALIGN);
		if(0>flag)
			return ASN1_PER_CHECK_LENGTH_ERROR;
		if ((temp_loop_i == 1)&&(flag == 0)){
			ws->buffer.current = temp_current;
			ws->buffer.bitOffset = temp_bitOffset;
			flag = 1;
		}
		else{
			*length = per_flag.PER_Dec_Len;
			return flag;
		}
	}
	
	if(per_flag.Range == 1 && per_flag.L_En_Flag == 0){
		if (consinfo->extflag == 1){
				if(0>ASN1_PER_Dec_ExtLength(ws,consinfo,&per_flag,UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
				*length = per_flag.PER_Dec_Len;
		}
		return 0;
	}
	
	if(per_flag.Is_Size == 1){
		if(0>ASN1_PER_Dec_strLength(ws,consinfo,&per_flag,UNALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		*length = per_flag.PER_Dec_Len;
	}
	else{
		temp_value_length = 0;
		flag = ASN1_PER_Dec_SeverLength(ws,consinfo,&per_flag,UNALIGN);
		if(0>flag)
			return ASN1_PER_CHECK_LENGTH_ERROR;
		*length = per_flag.PER_Dec_Len;
		return flag;
	}
	return 0;
}


ASN1_CPPLINK ASNINT32 error()
{
	return -1;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(ASN1WorkSpace *ws,ASNINT64 index,ASNBOOL flag,ASNBOOL isextend,ASNINT32 ub)
{
	Asn1ConsInfo enuminfo;
	ASNINT32 temp_index = index;
	if (flag!=0)
	{
		enuminfo.upper = 64;
	}
	else
	{
		enuminfo.upper = ub-1;
	}
	enuminfo.lower = 0;	
	enuminfo.extflag = isextend;
	enuminfo.charSet = 0;
	enuminfo.consType = CONS;
	// enuminfo.enumextbit =flag;
	ASN1_PER_UNAlign_Enc_ENUMERATED_child(ws,temp_index,flag,&enuminfo);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(ASN1WorkSpace *ws,ASNINT64 *index,ASNBOOL *flag,ASNBOOL isextend,ASNINT32 ub)
{
	Asn1ConsInfo enuminfo;
	ASNINT32 temp_index=0;
	*index = 0;
	enuminfo.upper = ub-1;
	enuminfo.lower = 0;
	enuminfo.extflag = isextend;
	enuminfo.charSet = 0;
	enuminfo.consType = CONS;
	ASN1_PER_UNAlign_Dec_ENUMERATED_child(ws,&temp_index,flag,&enuminfo);
	*index = temp_index;
	return 0;
}

