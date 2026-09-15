#include "ASN1_Set.h"
void FormatTime(ASNUINT8 *buf,struct tm * _time,ASNUINT8 zflag,ASNUINT8 timeflag)
{
	ASNUINT32 i = 0,tmp = 0;
	if (timeflag != 0)
	{
		tmp = _time->tm_year + 1900;
		buf[i++] = tmp / 1000+0x30;
		buf[i++] = (tmp / 100) % 10+0x30;
	} 
	
	tmp = _time->tm_year % 100 ;
	
	buf[i++] = tmp / 10+0x30;
	buf[i++] = tmp % 10+0x30;
	buf[i++] = (_time->tm_mon+1) / 10+0x30;
	buf[i++] = (_time->tm_mon+1) % 10+0x30;
	buf[i++] = _time->tm_mday / 10+0x30;
	buf[i++] = _time->tm_mday % 10+0x30;
	buf[i++] = _time->tm_hour / 10+0x30;
	buf[i++] = _time->tm_hour % 10+0x30;
	buf[i++] = _time->tm_min / 10+0x30;
	buf[i++] = _time->tm_min % 10+0x30;
	buf[i++] = _time->tm_sec / 10+0x30;
	buf[i++] = _time->tm_sec % 10+0x30;
	if (zflag != 0)
	{
		buf[i++] = 'Z';
	}
	
	
}
ASNINT32 ASN1_SET_INTEGER(ASN1WorkSpace* ws,INTEGER *value,INTEGER user_value)
{
	if (value == NULL){
		return -3;
	}
	*value = user_value;
	return 0;
}
ASNINT32 ASN1_SET_REAL(ASN1WorkSpace* ws,ASNREAL *value,ASNREAL user_value)
{
	if (value == NULL){
		return -3;
	}
	*value = user_value;
	return 0;
}
ASNINT32 ASN1_SET_BOOLEAN(ASN1WorkSpace* ws,ASNBOOL *value,ASNBOOL user_value)
{
	if (value == NULL){
		return -3;
	}
	*value = user_value;
	return 0;
}

ASNINT32 ASN1_SET_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value, ASNUINT8 *user_value, ASNINT32L value_bit_lenght)
{
	ASNINT32 i = 0;
	ASNINT32 len = (value_bit_lenght + 7) / 8;
	if (value == NULL) return -3;
	if (user_value == NULL)
	{
		if (value_bit_lenght != 0) return -4;
	}

	if (value_bit_lenght < 0) return -4;

	value->numbits = value_bit_lenght;
	value->data = mpool_malloc(ws->Pmemory, len);

	while(i < len){
		value->data[i] = user_value[i];
		i++;
	}
	return 0;
}

ASNINT32 ASN1_SET_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, ASNUINT8 *user_value, ASNINT32 value_octet_lenght)
{
	ASNINT32 i = 0;
	if (value == NULL) return -3;
	if (user_value == NULL && value_octet_lenght != 0) return -4;
	if (value_octet_lenght < 0) return -4;

	value->numbits = value_octet_lenght;
	value->data = mpool_malloc(ws->Pmemory,value->numbits);

	for (i = 0; i < value_octet_lenght; i++)
		value->data[i] = user_value[i];

	return 0;
}

ASNINT32 ASN1_SET_ASNString(ASN1WorkSpace *ws, ASNSTRING *value, ASNUINT8 *user_value, ASNINT32 value_lenght)
{
	if (value == NULL) return -3;
	if (user_value == NULL && value_lenght != 0) return -4;
	if (value_lenght < 0) return -4;

	value->asnstring = (ASNUINT8*)mpool_malloc(ws->Pmemory, value_lenght);
	value->nchar = value_lenght;
    strncpy(value->asnstring, user_value, value_lenght);

	return 0;
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_SET_UTF8Str(ASN1WorkSpace* ws,UTF8Str *value, ASNUINT8 *user_value,ASNINT32 value_lenght)
#else
ASNINT32 ASN1_SET_UTF8String(ASN1WorkSpace* ws,UTF8String *value, ASNUINT8 *user_value,ASNINT32 value_lenght)
#endif
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_SET_NumericString(ASN1WorkSpace* ws,NumericString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_SET_PrintableString(ASN1WorkSpace* ws,PrintableString *value,
								  ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_SET_NormalString(ASN1WorkSpace* ws,ASNSTRING *value,
							   ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_SET_IA5String(ASN1WorkSpace* ws,IA5String *value,
							ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_SET_UTCTime(ASN1WorkSpace* ws,UTCTime *value,
						  struct tm * _time,ASNINT32 ZoneInSecond)
{
	ASNUINT8 buf[128];
	ASNUINT8 buf2[128];
	ASNINT32 temp_length;
	memset(buf,0,128);
	memset(buf2,0,128);
	if (value == NULL || _time== NULL){
		return -3;
	}
	if(ZoneInSecond < (-12*3600) || ZoneInSecond > (12*3600))
		return -1;
	if(ZoneInSecond == 0)
		FormatTime(buf, _time,1,1);
		//strftime(buf, 100, "%Y/%m/%d/%H/%M/%SZ\0", _time);
	else if(ZoneInSecond > 0){
		FormatTime(buf, _time,0,1);
		//strftime(buf, 100, "%Y/%m/%d/%H/%M/%S\0", _time);
		sprintf(buf2, "+%02d%02d",ZoneInSecond/3600, ZoneInSecond%3600/60);
	}
	else if(ZoneInSecond < 0){
		//strftime(buf, 100, "%Y/%m/%d/%H/%M/%S\0", _time);
		FormatTime(buf, _time,0,1);
		sprintf(buf2, "-%02d%02d",abs(ZoneInSecond)/3600, abs(ZoneInSecond)%3600/60);
	}
	temp_length = (ASNINT32)strlen(buf);
	memmove(buf,buf+2,temp_length - 2);
	memset(buf+temp_length-2,0,1);
	if(0>ASN1_Time_to_UTCTime(ws,buf,buf2,&value->asnstring)){
		value->nchar = (ASNINT32)strlen(value->asnstring);
		return -4;
	}
	value->nchar = (ASNINT32)strlen(value->asnstring);
	return 0;
}

ASNINT32 ASN1_SET_GeneralizedTime(ASN1WorkSpace* ws,GeneralizedTime *value,
								  struct tm * _time,ASNINT32 ZoneInSecond,
								  ASNINT32 second,ASNINT32 exponent)
{
	ASNUINT8 buf[512];
	ASNUINT8 buf2[128];
/*	ASNUINT8 buf3[128];*/
	ASNUINT8 temp_sec[128];
	ASNUINT8 temp_exp[128];
	ASNINT32 temp_i = 0;

	memset(buf,0,512);
	memset(buf2,0,128);
/*	memset(buf3,0,128);*/
	memset(temp_sec,0,128);
	memset(temp_exp,0,128);

	if (value == NULL|| _time== NULL){
		return -3;
	}

	if(ZoneInSecond < (-12*3600) || ZoneInSecond > (12*3600))
		return -1;
	if(ZoneInSecond == 0){
		FormatTime(buf, _time,1,1);
		buf[strlen(buf) - 1 ] = '\0';
	}
		//strftime(buf, 100, "%Y/%m/%d/%H/%M/%SZ\0", _time);
	else if(ZoneInSecond > 0){
		FormatTime(buf, _time,0,1);
		//strftime(buf, 100, "%Y/%m/%d/%H/%M/%S\0", _time);
		sprintf(buf2, "+%02d%02d",ZoneInSecond/3600, ZoneInSecond%3600/60);
	}
	else if(ZoneInSecond < 0){
		FormatTime(buf, _time,0,1);
		//strftime(buf, 100, "%Y/%m/%d/%H/%M/%S\0", _time);
		sprintf(buf2, "-%02d%02d",abs(ZoneInSecond)/3600, abs(ZoneInSecond)%3600/60);
	}
	/*printf("%s\n", buf);*/
	if (exponent > 0){
		sprintf(temp_sec,"%d",second);
		if (strlen(temp_sec)< (size_t)exponent){
			temp_i = exponent - (ASNINT32)strlen(temp_sec);
			while (temp_i>0){
				temp_exp[temp_i--] = '0'; 
			}
		}
		temp_exp[0] = '.';
		strcat(buf,temp_exp);
		strcat(buf,temp_sec);
	}
	if (ZoneInSecond==0){
		strcat(buf,"Z");
	}

	if(0>ASN1_Time_to_GTime(ws,buf,buf2,&value->asnstring)){
		value->nchar = (ASNINT32)strlen(value->asnstring);
		return -4;
	}
	value->nchar = (ASNINT32)strlen(value->asnstring);
	return 0;
}

ASNINT32 ASN1_SET_VisibleString(ASN1WorkSpace* ws,VisibleString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}
ASNINT32 ASN1_SET_GraphicString(ASN1WorkSpace* ws,GraphicString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}
ASNINT32 ASN1_SET_TeletexString(ASN1WorkSpace* ws,TeletexString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_SET_VideotexString(ASN1WorkSpace* ws,VideotexString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_SET_GeneralString(ASN1WorkSpace* ws,GeneralString *value,
								ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_SET_ObjectDescriptor(ASN1WorkSpace* ws,ObjectDescriptor *value,
									ASNUINT8 *user_value,ASNINT32 value_lenght)
{
	return ASN1_SET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_SET_OBJECTIDENTIFIER(ASN1WorkSpace *ws, OBJECTIDENTIFIER *value, ASNUINT32 *user_value, ASNINT32 value_lenght)
{
	ASNINT32 i = 0;
	if (value == NULL) return -3;
	if (user_value == NULL && value_lenght != 0) return -4;
	if (value_lenght < 0 || value_lenght > 128) return -4;

	value->numids = value_lenght;
	for (i = 0; i < value_lenght; i++)
		value->subid[i] = user_value[i];

	return 0;
}

ASNINT32 ASN1_SET_RELATIVE_OID(ASN1WorkSpace *ws, RELATIVE_OID *value, ASNUINT32 *user_value, ASNINT32 value_lenght)
{
	ASNINT32 i = 0;
	if (value == NULL) return -3;
	if (user_value == NULL && value_lenght != 0) return -4;
	if (value_lenght < 0 || value_lenght > 128) return -4;

	value->numids = value_lenght;
	for (i = 0; i < value_lenght; i++)
		value->subid[i] = user_value[i];

	return 0;
}

ASNINT32 ASN1_SET_UniversalString(ASN1WorkSpace *ws, UniversalString *value, ASNUINT32 *user_value, ASNINT32 value_lenght)
{
	ASNINT32 i = 0;
	if (value == NULL) return -3;
	if (user_value == NULL && value_lenght != 0) return -4;
	if (value_lenght < 0) return -4;

	value->nchar = value_lenght;
	value->data = mpool_malloc(ws->Pmemory, sizeof(ASNUINT32) * value->nchar);

	//while(i < value_lenght) 
	for (i = 0; i < value_lenght; i++)
		value->data[i] = user_value[i];

	return 0;
}
ASNINT32 ASN1_SET_BMPString(ASN1WorkSpace* ws,BMPString *value,
							ASNUINT16 *user_value,ASNINT32 value_lenght)
{
	ASNINT32 i = 0;
	if (value == NULL){
		return -3;
	}
	if (user_value == NULL){
		if (value_lenght != 0){
			return -4;
		}
	}
	if (value_lenght < 0){
		return -4;
	}

	value->nchar = value_lenght;
	value->data = mpool_malloc(ws->Pmemory,sizeof(ASNUINT16)*value->nchar);

	while(i<value_lenght){
		value->data[i] = user_value[i];
		i++;
	}
	return 0;
}
ASNINT32 ASN1_SET_CHARACTERSTRING(ASN1WorkSpace* ws,CHARACTERSTRING *value,CHARACTERSTRING *user_value)
{
	/*value = mpool_malloc(ws->Pmemory,sizeof(CHARACTERSTRING));*/
	if (value == NULL){
		return -3;
	}
	if (user_value == NULL){
			return -4;
	}
	memcpy(value,user_value,sizeof(CHARACTERSTRING));
	/*
	ASNUINT32 i = 0;
	value->numbits = value_lenght;

	value->data = mpool_malloc(ws->Pmemory,value->numbits);
	while(i<value_lenght){
		value->data[i] = user_value[i];
		i++;
	}
	*/
	return 0;	
}
ASNINT32 ASN1_SET_ENUMERATED(ASN1WorkSpace* ws, ENUMERATED *value, ENUMERATED user_value)
{
	if (value == NULL){
		return -3;
	}
	*value = user_value;
	return 0;
}
ASNINT32 ASN1_SET_NULL(ASN1WorkSpace* ws,ASNUINT8* value,ASNUINT8 user_value)
{
	if (value == NULL){
		return -3;
	}
	*value = user_value;
	return 0;	
}

ASNINT32 ASN1_SET_OpenType(ASN1WorkSpace* ws,OpenType *value, 
						   ASNUINT8* user_value,ASNINT32 value_lenght)
{
	if (value == NULL){
		return -3;
	}

	if (user_value == NULL){
		if (value_lenght != 0){
			return -4;
		}
	}
	
	if (value_lenght < 0){
		return -4;
	}

	value->numocts = value_lenght;
	value->data = mpool_malloc(ws->Pmemory,value->numocts);
	memcpy(value->data,user_value,value->numocts);
	return 0;
}

/*GET*/
ASNINT32 ASN1_GET_INTEGER(ASN1WorkSpace* ws,INTEGER *value,INTEGER *user_value)
{
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*user_value = *value;
	return 0;
}

ASNINT32 ASN1_GET_REAL(ASN1WorkSpace* ws,ASNREAL *value,ASNREAL *user_value)
{
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*user_value = *value;
	return 0;
}

ASNINT32 ASN1_GET_BOOLEAN(ASN1WorkSpace* ws,ASNBOOL *value,ASNBOOL *user_value)
{
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*user_value = *value;
	return 0;
}

ASNINT32 ASN1_GET_BITSTRING(ASN1WorkSpace* ws,BITSTRING *value,
							ASNUINT8 **user_value,ASNUINT32L *value_lenght)
{
	ASNINT32 i = 0;
	ASNINT32 len;
	ASNUINT8* temp_pointer;
	if (value == NULL || user_value == NULL){
		return -5;
	}
	len = (value->numbits+7) / 8;
	*user_value = (ASNUINT8*)mpool_malloc(ws->Pmemory,len);
	temp_pointer = *user_value;
	*value_lenght = value->numbits;
	
	while(i<len){
		temp_pointer[i] = value->data[i];
		i++;
	}
	return 0;
}

ASNINT32 ASN1_GET_OCTETSTRING(ASN1WorkSpace* ws,OCTETSTRING *value,
							  ASNUINT8 **user_value,ASNUINT32 *value_lenght)
{
	ASNUINT32 i = 0;
	ASNUINT8* temp_pointer;
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*user_value = (ASNUINT8*)mpool_malloc(ws->Pmemory,value->numbits);
	temp_pointer = *user_value;

	*value_lenght = value->numbits;

	while(i<value->numbits){
		temp_pointer[i] = value->data[i];
		i++;
	}
	return 0;
}

ASNINT32 ASN1_GET_ASNString(ASN1WorkSpace* ws,ASNSTRING *value,
							ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	if (value == NULL || user_value == NULL || value_lenght == NULL){
		return -5;
	}
	*user_value = (ASNUINT8*)mpool_malloc(ws->Pmemory,value->nchar);
	*value_lenght = value->nchar;
	strncpy(*user_value,value->asnstring,value->nchar);
	return 0;
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_GET_UTF8Str(ASN1WorkSpace* ws,UTF8Str *value, ASNUINT8 **user_value,ASNINT32 *value_lenght)
#else
ASNINT32 ASN1_GET_UTF8String(ASN1WorkSpace* ws,UTF8String *value, ASNUINT8 **user_value,ASNINT32 *value_lenght)
#endif
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_GET_NumericString(ASN1WorkSpace* ws,NumericString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_GET_PrintableString(ASN1WorkSpace* ws,PrintableString *value,
								  ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_GET_NormalString(ASN1WorkSpace* ws,ASNSTRING *value,
							   ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);

}

ASNINT32 ASN1_GET_IA5String(ASN1WorkSpace* ws,IA5String *value,
							ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_GET_ObjectDescriptor(ASN1WorkSpace* ws,ObjectDescriptor *value,
								   ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_GET_UTCTime(ASN1WorkSpace* ws,UTCTime *value,
						  struct tm * _time,ASNINT32* ZoneInSecond)
{
	ASNUINT8 buf[10];
	ASNUINT8* temp_pointer;

	if (value == NULL || _time == NULL||ZoneInSecond == NULL){
		return -5;
	}
	temp_pointer = mpool_malloc(ws->Pmemory,value->nchar+1);
	memset(temp_pointer,0x00,value->nchar+1);
	strncpy(temp_pointer,value->asnstring,value->nchar);
	memset(buf,0x00,10);
	strncpy(buf,temp_pointer,2);
	_time->tm_year = atoi(buf);

	memset(buf,0x00,10);
	strncpy(buf,temp_pointer+2,2);
	_time->tm_mon = atoi(buf) - 1;

	memset(buf,0x00,10);
	strncpy(buf,temp_pointer+4,2);
	_time->tm_mday = atoi(buf);

	memset(buf,0x00,10);
	strncpy(buf,temp_pointer+6,2);
	_time->tm_hour = atoi(buf);

	memset(buf,0x00,10);
	strncpy(buf,temp_pointer+8,2);
	_time->tm_min = atoi(buf);

	memset(buf,0x00,10);
	strncpy(buf,temp_pointer+10,2);
	_time->tm_sec = atoi(buf);

	if (strncmp(temp_pointer+12,"Z",1)==0 || strncmp(temp_pointer+12,"z",1)==0){
		*ZoneInSecond = 0;
		return 0;
	}
	if (*(temp_pointer+12) == '\0'){
		return 0;
	}
	memset(buf,0x00,10);
	if (strncmp(temp_pointer+12,"-",1) == 0){
		strncpy(buf,temp_pointer+13,2);
		*ZoneInSecond = atoi(buf)*3600;
		memset(buf,0x00,10);
		strncpy(buf,temp_pointer+15,2);
		*ZoneInSecond += atoi(buf);
		*ZoneInSecond = 0 - *ZoneInSecond;

	}
	else{
		strncpy(buf,temp_pointer+13,2);
		*ZoneInSecond = atoi(buf)*3600;
		memset(buf,0x00,10);
		strncpy(buf,temp_pointer+15,2);
		*ZoneInSecond += atoi(buf);
	}
	return 0;
}

ASNINT32 ASN1_GET_GeneralizedTime(ASN1WorkSpace* ws, GeneralizedTime *value, struct tm * _time, ASNINT32 *ZoneInSecond, ASNINT32 *second, ASNINT32 *exponent)
{
	ASNUINT8 buf[10];
	ASNUINT8 temp_second[512] = { 0, };
	ASNUINT8* temp_pointer;
	ASNUINT8* pointer;
	ASNINT32 temp_zone;
	int temp_i = 0;
	
	if (value == NULL || _time == NULL|| ZoneInSecond == NULL|| second == NULL || exponent == NULL) return -5;

	*ZoneInSecond = 0;
	*second = 0;
	*exponent = 0;

	temp_pointer = pointer = mpool_malloc(ws->Pmemory, value->nchar + 1);

	memset(temp_pointer, 0, value->nchar + 1);
	strncpy(temp_pointer, value->asnstring, value->nchar);
	
	memset(buf, 0, 10);
	strncpy(buf, temp_pointer, 4);
	temp_pointer += 4;
	_time->tm_year = atoi(buf) - 1900;		// Year

	memset(buf, 0, 10);
	strncpy(buf, temp_pointer, 2);
	temp_pointer += 2;
	_time->tm_mon = atoi(buf) - 1;			// Month

	memset(buf, 0, 10);
	strncpy(buf, temp_pointer, 2);
	temp_pointer += 2;
	_time->tm_mday = atoi(buf);				// Day

	memset(buf, 0, 10);
	strncpy(buf, temp_pointer, 2);
	temp_pointer += 2;
	_time->tm_hour = atoi(buf);				// Hour

	memset(buf, 0, 10);
	strncpy(buf, temp_pointer, 2);
	temp_pointer += 2;
	_time->tm_min = atoi(buf);				// Minute

	memset(buf, 0, 10);
	strncpy(buf, temp_pointer, 2);
	temp_pointer += 2;
	_time->tm_sec = atoi(buf);				// Second
	
	if (*(temp_pointer) == 0 || strncmp(temp_pointer, "Z", 1) == 0 || strncmp(temp_pointer, "z", 1) == 0) return 0;	// 0 or 'Z' then end

	if (strncmp(temp_pointer, ".", 1) == 0)
	{	// Fraction of second
		temp_pointer++;
		while (*temp_pointer >= 0x30 && *temp_pointer <= 0x39)
		{
			temp_second[temp_i] = *temp_pointer;
			temp_pointer++;
			temp_i++;
		}
		*second = atoi(temp_second);
		*exponent = temp_i;
	}

	memset(buf,0,10);
	if (strncmp(temp_pointer, "-" , 1) == 0)
	{
		temp_pointer++;
		strncpy(buf,temp_pointer,2);
		temp_zone = atoi(buf)*3600;
		temp_pointer+=2;

		memset(buf,0,10);
		strncpy(buf, temp_pointer, 2);
		temp_zone += atoi(buf);
		*ZoneInSecond = 0 - temp_zone;
	}
	else if (strncmp(temp_pointer, "+" , 1) == 0)
	{
		temp_pointer++;
		strncpy(buf, temp_pointer, 2);
		*ZoneInSecond = atoi(buf) * 3600;
		temp_pointer += 2;

		memset(buf, 0, 10);
		strncpy(buf, temp_pointer, 2);
		*ZoneInSecond += atoi(buf);
	}

	return 0;
}

ASNINT32 ASN1_GET_VisibleString(ASN1WorkSpace* ws,VisibleString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_GET_GeneralString(ASN1WorkSpace* ws,GeneralString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);
}
ASNINT32 ASN1_GET_GraphicString(ASN1WorkSpace* ws,GraphicString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_GET_VideotexString(ASN1WorkSpace* ws,VideotexString *value,
								 ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);
}

ASNINT32 ASN1_GET_TeletexString(ASN1WorkSpace* ws,TeletexString *value,
								ASNUINT8 **user_value,ASNINT32 *value_lenght)
{
	return ASN1_GET_ASNString(ws,value,user_value,value_lenght);

}

//ASNINT32 ASN1_GET_OBJECTIDENTIFIER(ASN1WorkSpace* ws,OBJECTIDENTIFIER *value,
//								   ASNUINT32 **user_value,ASNUINT32 *value_lenght)
ASNINT32 ASN1_GET_OBJECTIDENTIFIER(ASN1WorkSpace* ws,OBJECTIDENTIFIER *value,
								   ASNUINT32 user_value[128],ASNUINT32 *value_lenght)
{
	ASNUINT32 i = 0;
	ASNUINT32 *temp_pointer;
	if (value == NULL || user_value == NULL){
		return -5;
	}
	/**user_value = (ASNUINT32*)mpool_malloc(ws->Pmemory,value->numids);*/
	temp_pointer = user_value;
	*value_lenght = value->numids;
	
	while(i < value->numids){
		temp_pointer[i] = value->subid[i];
		i++;
	}
	return 0;
}

//ASNINT32 ASN1_GET_RELATIVE_OID(ASN1WorkSpace* ws,RELATIVE_OID *value,
//							   ASNUINT32 **user_value,ASNUINT32 *value_lenght)
ASNINT32 ASN1_GET_RELATIVE_OID(ASN1WorkSpace *ws, RELATIVE_OID *value, ASNUINT32 user_value[128], ASNUINT32 *value_lenght)
{
	ASNUINT32 i = 0;
	ASNUINT32 *temp_pointer;
	if (value == NULL || user_value == NULL) return -5;

/*	*user_value = (ASNUINT32*)mpool_malloc(ws->Pmemory,value->numids);*/
	temp_pointer = user_value;
	*value_lenght = value->numids;
	
	while(i < value->numids)
	{
		temp_pointer[i] = value->subid[i];
		i++;
	}
	return 0;
}


ASNINT32 ASN1_GET_UniversalString(ASN1WorkSpace* ws,UniversalString *value,
								  ASNUINT32 **user_value,ASNUINT32 *value_lenght)
{
	ASNUINT32 i = 0;
	ASNUINT32 *temp_pointer;
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*user_value = (ASNUINT32*)mpool_malloc(ws->Pmemory,value->nchar);
	temp_pointer = *user_value;

	*value_lenght = value->nchar;
	while(i<value->nchar){
		temp_pointer[i] = value->data[i];
		i++;
	}
	return 0;
}

ASNINT32 ASN1_GET_BMPString(ASN1WorkSpace* ws,BMPString *value,
							ASNUINT16 **user_value,ASNUINT32 *value_lenght)
{
	ASNUINT32 i = 0;
	ASNUINT16 *temp_pointer;
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*user_value = (ASNUINT16*)mpool_malloc(ws->Pmemory,value->nchar);
	temp_pointer = *user_value;
	
	*value_lenght = value->nchar;
	while(i<value->nchar){
		temp_pointer[i] = value->data[i];
		i++;
	}
	return 0;
}

ASNINT32 ASN1_GET_CHARACTERSTRING(ASN1WorkSpace* ws,CHARACTERSTRING *value,CHARACTERSTRING **user_value)
{
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*user_value = mpool_malloc(ws->Pmemory,sizeof(CHARACTERSTRING));
	memcpy(*user_value,value,sizeof(CHARACTERSTRING));
	/*
	ASNUINT32 i = 0;
	ASNUINT8* temp_pointer;
	*user_value = (ASNUINT8*)mpool_malloc(ws->Pmemory,value->numbits);
	temp_pointer = *user_value;
	
	*value_lenght = value->numbits;
	
	while(i<value->numbits){
		temp_pointer[i] = value->data[i];
		i++;
	}
	*/
	return 0;
}

ASNINT32 ASN1_GET_ENUMERATED(ASN1WorkSpace* ws,ENUMERATED *value,ENUMERATED *user_value)
{
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*user_value = *value;
	return 0;
}

ASNINT32 ASN1_GET_NULL(ASN1WorkSpace* ws,ASNUINT8* value,ASNUINT8 *user_value)
{
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*user_value = *value;
	return 0;
}

ASNINT32 ASN1_GET_OpenType(ASN1WorkSpace* ws,OpenType *value, 
						   ASNUINT8 **user_value,ASNUINT32 *value_lenght)
{
	if (value == NULL || user_value == NULL){
		return -5;
	}
	*value_lenght = value->numocts;
	*user_value = (ASNUINT8*)mpool_malloc(ws->Pmemory,value->numocts);
	memcpy(*user_value,value->data,value->numocts);
	return 0;
}
