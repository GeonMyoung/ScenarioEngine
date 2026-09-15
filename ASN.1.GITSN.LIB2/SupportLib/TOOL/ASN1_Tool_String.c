#include "ASN1_print.h"
#include "ASN1_Tool_String.h"

ASN1_CPPLINK ASNINT32 gb2312_mbtowc (ASNUINT32 *pwc, const ASNUINT8 *s, ASNINT32 n) //gb2312 to unicode
{
  ASNUINT8 c1;
  ASNUINT8 c2;
  if (pwc == NULL || s == NULL){
	  return -37;
  }

  if (0x80 > s[0])
  {
	  *pwc = s[0];
	   return 1;
  }
  c1 = s[0]-0x80;
  if ((c1 >= 0x21 && c1 <= 0x29) || (c1 >= 0x30 && c1 <= 0x77)) {
    if (n >= 2) {
     c2 = s[1]-0x80;
      if (c2 >= 0x21 && c2 < 0x7f) {
        ASNUINT32 i = 94 * (c1 - 0x21) + (c2 - 0x21);
        ASNUINT16 wc = 0xfffd;
        if (i < 1410) {
          if (i < 831)
            wc = gb2312_2uni_page21[i];
        } else {
          if (i < 8178)
            wc = gb2312_2uni_page30[i-1410];
        }
        if (wc != 0xfffd) {
          *pwc = (ASNUINT32) wc;
		  return 2;
        }
      }
      return -1;
    }
    return -3;
  }
  return -2;
}


ASN1_CPPLINK ASNINT32 gb2312_wctomb (ASNUINT8 *r, ASNUINT32 wc, ASNINT32 n) //unicode to gb2312
{
  if (r == NULL){
	  return -37;
  }
  if (n >= 2) {
    const Summary16 *summary = NULL;
	if (wc < 0x0080) 
    {
		*r = wc;
		return 1;
	}
    if (wc >= 0x0080 && wc < 0x0460)
      summary = &gb2312_uni2indx_page00[(wc>>4)];
    else if (wc >= 0x2000 && wc < 0x2650)
      summary = &gb2312_uni2indx_page20[(wc>>4)-0x200];
    else if (wc >= 0x3000 && wc < 0x3230)
      summary = &gb2312_uni2indx_page30[(wc>>4)-0x300];
    else if (wc >= 0x4e00 && wc < 0x9cf0)
      summary = &gb2312_uni2indx_page4e[(wc>>4)-0x4e0];
    else if (wc >= 0x9e00 && wc < 0x9fb0)
      summary = &gb2312_uni2indx_page9e[(wc>>4)-0x9e0];
    else if (wc >= 0xff00 && wc < 0xfff0)
      summary = &gb2312_uni2indx_pageff[(wc>>4)-0xff0];
    if (summary) {
      ASNUINT16 used = summary->used;
      ASNUINT32 i = wc & 0x0f;
      if (used & ((ASNUINT16) 1 << i)) {
        ASNUINT16 c;
        /* Keep in `used' only the bits 0..i-1. */
        used &= ((ASNUINT16) 1 << i) - 1;
        /* Add `summary->indx' and the number of bits set in `used'. */
        used = (used & 0x5555) + ((used & 0xaaaa) >> 1);
        used = (used & 0x3333) + ((used & 0xcccc) >> 2);
        used = (used & 0x0f0f) + ((used & 0xf0f0) >> 4);
        used = (used & 0x00ff) + (used >> 8);
        c = gb2312_2charset[summary->indx + used];
        r[0] = (c >> 8); r[1] = (c & 0xff);
		r[0]+=0x80;
        r[1]+=0x80;
        return 2;
      }
    }
    return -1;
  }
  return -2;
}

ASN1_CPPLINK ASNINT32 utf8_mbtowc (ASNUINT32 *pwc, const ASNUINT8 *s, ASNINT32 n) //utf8 to unicode
{
	ASNUINT8 c;
	if (pwc == NULL || s == NULL){
		return -37;
	}

	c = s[0];
	if (c < 0x80) {
		*pwc = (ASNUINT32) c;
		return 1;
	} else if (c < 0xc2) {
		return -1;
	} else if (c < 0xe0) {
		if (n < 2)
			return -2;
		if (!((s[1] ^ 0x80) < 0x40))
			return -1;
		*pwc = ((ASNUINT32) (c & 0x1f) << 6)
			| (ASNUINT32) (s[1] ^ 0x80);
		return 2;
	} else if (c < 0xf0) {
		if (n < 3)
			return -2;
		if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
			&& (c >= 0xe1 || s[1] >= 0xa0)))
			return -1;
		*pwc = ((ASNUINT32) (c & 0x0f) << 12)
			| ((ASNUINT32) (s[1] ^ 0x80) << 6)
			| (ASNUINT32) (s[2] ^ 0x80);
		return 3;
	} else if (c < 0xf8 && sizeof(ASNUINT32)*8 >= 32) {
		if (n < 4)
			return -1;
		if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
			&& (s[3] ^ 0x80) < 0x40
			&& (c >= 0xf1 || s[1] >= 0x90)))
			return -1;
		*pwc = ((ASNUINT32) (c & 0x07) << 18)
			| ((ASNUINT32) (s[1] ^ 0x80) << 12)
			| ((ASNUINT32) (s[2] ^ 0x80) << 6)
			| (ASNUINT32) (s[3] ^ 0x80);
		return 4;
	} else if (c < 0xfc && sizeof(ASNUINT32)*8 >= 32) {
		if (n < 5)
			return -2;
		if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
			&& (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
			&& (c >= 0xf9 || s[1] >= 0x88)))
			return -1;
		*pwc = ((ASNUINT32) (c & 0x03) << 24)
			| ((ASNUINT32) (s[1] ^ 0x80) << 18)
			| ((ASNUINT32) (s[2] ^ 0x80) << 12)
			| ((ASNUINT32) (s[3] ^ 0x80) << 6)
			| (ASNUINT32) (s[4] ^ 0x80);
		return 5;
	} else if (c < 0xfe && sizeof(ASNUINT32)*8 >= 32) {
		if (n < 6)
			return -2;
		if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
			&& (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
			&& (s[5] ^ 0x80) < 0x40
			&& (c >= 0xfd || s[1] >= 0x84)))
			return -1;
		*pwc = ((ASNUINT32) (c & 0x01) << 30)
			| ((ASNUINT32) (s[1] ^ 0x80) << 24)
			| ((ASNUINT32) (s[2] ^ 0x80) << 18)
			| ((ASNUINT32) (s[3] ^ 0x80) << 12)
			| ((ASNUINT32) (s[4] ^ 0x80) << 6)
			| (ASNUINT32) (s[5] ^ 0x80);
		return 6;
	} else
		return -1;
}

ASN1_CPPLINK ASNINT32 utf8_wctomb (ASNUINT8 *r, ASNUINT32 wc, ASNINT32 n) /* n == 0 is acceptable */
{
	ASNINT32 count;
	if (r == NULL){
		return -37;
	}
	if (wc < 0x80)
		count = 1;
	else if (wc < 0x800)
		count = 2;
	else if (wc < 0x10000)
		count = 3;
	else if (wc < 0x200000)
		count = 4;
	else if (wc < 0x4000000)
		count = 5;
	else if (wc <= 0x7fffffff)
		count = 6;
	else
		return -1;
	if (n < count)
		return -2;
	switch (count) { /* note: falls through cases */
    case 6: *(r+5) = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0x4000000;
    case 5: *(r+4) = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0x200000;
    case 4: *(r+3) = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0x10000;
    case 3: *(r+2) = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0x800;
    case 2: *(r+1) = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0xc0;
    case 1: *(r+0) = wc;
	}
	return count;
}


ASN1_CPPLINK ASNINT32 gb2312_to_utf8(ASN1WorkSpace* ws,ASNUINT8 *gb2312,
						ASNUINT8** utf8)
{
	ASNINT32 add_count;
	ASNINT32 flag=0;
	ASNUINT8* utf8_temp;
	ASNUINT32 *unicode,*currert;
	ASNINT32 char_length;

	if (ws == NULL ||gb2312 == NULL || utf8 == NULL){
		return -37;
	}
	char_length = (ASNINT32)strlen(gb2312);
	
	unicode = (ASNUINT32*)malloc(char_length*sizeof(ASNUINT32));
	*utf8 = (ASNUINT8*)mpool_malloc(ws->Pmemory,(char_length*3)*sizeof(ASNUINT8));
	memset(unicode,'\0',char_length*sizeof(ASNUINT32));
	memset((*utf8),'\0',char_length*3*sizeof(ASNUINT8));
    currert = unicode;
	utf8_temp = *utf8;

    while(0x00 != *gb2312)
	{
		
		if (0 > (add_count=gb2312_mbtowc(currert,gb2312,2)))
		{
			return -38;
		}
		
		gb2312+=add_count;
		currert++;
	}

	currert = unicode;
	while (0x00 != *currert)
	{
		if (0 > (add_count=utf8_wctomb(utf8_temp,*currert,6)))
		{
			return -39;
		}
		(utf8_temp)+=add_count;
		currert+=1;
	}
   free(unicode);
   return 0;
}

ASN1_CPPLINK ASNINT32 utf8_to_gb2312(ASN1WorkSpace* ws,ASNUINT8 *utf8,ASNUINT8** gb2312)
{
	//ASNINT32 memory = n;
	ASNINT32 add_count;
	ASNINT32 flag=0;
	ASNUINT8* gb2312_temp;
	ASNUINT32 *unicode,*currert;
	
	if (ws == NULL ||utf8 == NULL || gb2312 == NULL){
		return -37;
	}

	unicode = malloc(strlen(utf8)*sizeof(ASNUINT32));
	memset(unicode,0,strlen(utf8)*sizeof(ASNUINT32));
    currert=unicode;

	while (0x00 != *utf8)
	{
		if (0 > (add_count=utf8_mbtowc(currert,utf8,6)))
		{
			return -40;
		}
		utf8+=add_count;
		currert++;
		flag++;
	}

	currert=unicode;

	*gb2312 = mpool_malloc(ws->Pmemory,flag*2+1*sizeof(ASNUINT8));
	memset((*gb2312),'\0',flag*2+1);
	gb2312_temp = *gb2312;
	while (flag)
	{
		if (0 > (add_count=gb2312_wctomb(gb2312_temp,*currert,2)))
		{
			return -41;
		}
		gb2312_temp+=add_count;
		currert++;
		flag--;
	}
    free(unicode);
    return 0;
}


ASN1_CPPLINK ASNINT32 ASN_Print_utf8_gb2312(ASN1WorkSpace* ws,ASNUINT8 *utf8,ASNUINT8** gb2312)
{
	if (ws == NULL ||gb2312 == NULL || utf8 == NULL){
		return -37;
	}
	utf8_to_gb2312(ws,utf8,gb2312);
	asn_printf("%s",(*gb2312));
	return 0;
}


ASN1_CPPLINK ASNINT32 ksc5601_mbtowc (ASNUINT32 *pwc, const ASNUINT8 *s, ASNINT32 n)
{
  ASNUINT8 c1;
  ASNUINT8 c2 ;
  ASNUINT32 i;
  ASNUINT16 wc;

  if (pwc == NULL || s==NULL){
	  return -37;
  }

  c1 = s[0];
  if (0x80 > s[0])
  {
	  *pwc = s[0];
	  return 1;
  }
  c1 = s[0]-0x80;

  if ((c1 >= 0x21 && c1 <= 0x2c) || (c1 >= 0x30 && c1 <= 0x48) || (c1 >= 0x4a && c1 <= 0x7d)) {
    if (n >= 2) {
      c2 = s[1]-0x80;
      if (c2 >= 0x21 && c2 < 0x7f) {
         i = 94 * (c1 - 0x21) + (c2 - 0x21);
         wc = 0xfffd;
        if (i < 1410) {
          if (i < 1115)
            wc = ksc5601_2uni_page21[i];
        } else if (i < 3854) {
          if (i < 3760)
            wc = ksc5601_2uni_page30[i-1410];
        } else {
          if (i < 8742)
            wc = ksc5601_2uni_page4a[i-3854];
        }
        if (wc != 0xfffd) {
          *pwc = (ASNUINT32) wc;
          return 2;
        }
      }
      return -1;
    }
    return -2;
  }
  return -1;
}


ASN1_CPPLINK ASNINT32 ksc5601_wctomb ( ASNUINT8* r, ASNUINT32 wc, ASNINT32 n)
{
  ASNUINT16 used;
  ASNUINT32 i;
  ASNUINT16 c;
  if (r == NULL){
	return -37;
  }

  if (n >= 2) {

    const Summary16 *summary = NULL;
	if (wc < 0x0080) 
    {
		*r = wc;
		return 1;
	}

    if (wc >= 0x0080 && wc < 0x0460)
      summary = &ksc5601_uni2indx_page00[(wc>>4)];
    else if (wc >= 0x2000 && wc < 0x2670)
      summary = &ksc5601_uni2indx_page20[(wc>>4)-0x200];
    else if (wc >= 0x3000 && wc < 0x33e0)
      summary = &ksc5601_uni2indx_page30[(wc>>4)-0x300];
    else if (wc >= 0x4e00 && wc < 0x9fa0)
      summary = &ksc5601_uni2indx_page4e[(wc>>4)-0x4e0];
    else if (wc >= 0xac00 && wc < 0xd7a0)
      summary = &ksc5601_uni2indx_pageac[(wc>>4)-0xac0];
    else if (wc >= 0xf900 && wc < 0xfa10)
      summary = &ksc5601_uni2indx_pagef9[(wc>>4)-0xf90];
    else if (wc >= 0xff00 && wc < 0xfff0)
      summary = &ksc5601_uni2indx_pageff[(wc>>4)-0xff0];
    if (summary) {
      used = summary->used;
      i = wc & 0x0f;
      if (used & ((ASNUINT16) 1 << i)) {
        /* Keep in `used' only the bits 0..i-1. */
        used &= ((ASNUINT16) 1 << i) - 1;
        /* Add `summary->indx' and the number of bits set in `used'. */
        used = (used & 0x5555) + ((used & 0xaaaa) >> 1);
        used = (used & 0x3333) + ((used & 0xcccc) >> 2);
        used = (used & 0x0f0f) + ((used & 0xf0f0) >> 4);
        used = (used & 0x00ff) + (used >> 8);
        c = ksc5601_2charset[summary->indx + used];
        r[0] = (c >> 8); r[1] = (c & 0xff);
		r[0]+=0x80;
		r[1]+=0x80;
        return 2;
      }
    }
    return -1;
  }
  return -2;
}

ASN1_CPPLINK ASNINT32 ksc5601_to_utf8(ASN1WorkSpace* ws,ASNUINT8 *ksc5601,
						ASNUINT8** utf8)
{
	ASNINT32 add_count;
	ASNINT32 flag=0;
	ASNUINT8* utf8_temp;
	ASNUINT32 *unicode,*currert;
	ASNINT32 char_length;
	if (ws == NULL || ksc5601 == NULL || utf8 == NULL){
		return -37;
	}
	char_length = (ASNINT32)strlen(ksc5601);
	
	unicode = (ASNUINT32*)malloc((char_length+1)*sizeof(ASNUINT32));
	*utf8 = (ASNUINT8*)mpool_malloc(ws->Pmemory,((char_length+1)*3)*sizeof(ASNUINT8));
	memset(unicode,'\0',(char_length+1)*sizeof(ASNUINT32));
	memset((*utf8),'\0',((char_length+1)*3)*sizeof(ASNUINT8));
    currert = unicode;
	utf8_temp = *utf8;
	
    while(0x00 != *ksc5601)
	{
		
		if (0 > (add_count=ksc5601_mbtowc(currert,ksc5601,2)))
		{
			return -42;
		}
		
		ksc5601+=add_count;
		currert++;
	}
	
	currert = unicode;
	while (0x00 != *currert)
	{
		if (0 > (add_count=utf8_wctomb(utf8_temp,*currert,6)))
		{
			return -43;
		}
		(utf8_temp)+=add_count;
		currert+=1;
	}
	free(unicode);
	return 0;
}

ASN1_CPPLINK ASNINT32 utf8_to_ksc5601(ASN1WorkSpace* ws,ASNUINT8 *utf8,ASNUINT8** ksc5601)
{
	ASNINT32 add_count;
	ASNINT32 readd_count = 0;
	ASNINT32 flag=0;
	ASNUINT8* ksc5601_temp;
	ASNUINT32 *unicode,*currert;
	
	if (ws == NULL || utf8 == NULL || ksc5601 == NULL){
		return -37;
	}
	unicode = malloc(strlen(utf8)*sizeof(ASNUINT32));
	memset(unicode,'\0',strlen(utf8)*sizeof(ASNUINT32));
    currert=unicode;
	
	while (0x00 != *utf8)
	{
		if (0 > (add_count=utf8_mbtowc(currert,utf8,6)))
		{
			return -44;
		}
		utf8+=add_count;
		currert++;
		flag++;
	}
	
	currert=unicode;
	
	*ksc5601 = mpool_malloc(ws->Pmemory,(flag+1)*2*sizeof(ASNUINT8));
	memset((*ksc5601),'\0',(flag+1)*2*sizeof(ASNUINT8));
	ksc5601_temp = *ksc5601;
	while (flag)
	{
		if (0 > (add_count=ksc5601_wctomb(ksc5601_temp,*currert,2)))
		{
			return -45;
		}
		ksc5601_temp+=add_count;
		readd_count += add_count;
		currert++;
		flag--;
	}
    free(unicode);
    return readd_count;
}


ASN1_CPPLINK ASNINT32 ASN_Print_utf8_ksc5601(ASN1WorkSpace* ws,ASNUINT8 *utf8,ASNUINT8** ksc5601)
{
	if (ws == NULL || utf8 == NULL || ksc5601 == NULL){
		return -37;
	}
	utf8_to_ksc5601(ws,utf8,ksc5601);
	asn_printf("%s",(*ksc5601));
	return 0;

}

ASN1_CPPLINK ASNINT32 String_to_Objid(ASNUINT8* value,OBJECTIDENTIFIER* objid)
{
	ASNINT32 F_UI_objid_count = 0;
	ASNUINT8* F_UC_Temp_objid = value;
	ASNUINT8 F_UC_objid[128];
	ASNINT32 F_IN_Array_objid_count = 0;
	
	memset(F_UC_objid,'\0',128);
	
	if (value == NULL)
		return -1;
    
    while('\0' != *F_UC_Temp_objid)
	{
		if (*F_UC_Temp_objid == '.' || *F_UC_Temp_objid == ' ')
		{
			objid->subid[F_UI_objid_count] = atoi(F_UC_objid);
			F_UI_objid_count++;
            F_UC_Temp_objid++;
			memset(F_UC_objid,'\0',128);
			F_IN_Array_objid_count = 0;
		}


		if (*F_UC_Temp_objid < '0' && *F_UC_Temp_objid >'9')
		{
			return -2;
		}
        else
		{
			F_UC_objid[F_IN_Array_objid_count] = *F_UC_Temp_objid;
			F_IN_Array_objid_count++;
			F_UC_Temp_objid++;
		}
	}
	if (F_UC_objid[1] != '\0')
	{
		objid->subid[F_UI_objid_count] = atoi(F_UC_objid);
		F_UI_objid_count++;
	}
	objid->numids = F_UI_objid_count;
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Compare_StringtoObjid(ASNUINT8* value,OBJECTIDENTIFIER* Com_two)
{
	OBJECTIDENTIFIER Com_one;
    String_to_Objid(value,&Com_one);
	return ASN1_BER_Compare_OBJECTIDENTIFIER(&Com_one,Com_two);
}


ASN1_CPPLINK ASNINT32 String_to_Roid(ASNUINT8* value,RELATIVE_OID* roid)
{
	ASNINT32 F_UI_roid_count = 0;
	ASNUINT8* F_UC_Temp_roid = value;
	ASNUINT8 F_UC_roid[128];
	ASNINT32 F_IN_Array_roid_count = 0;
	
	memset(F_UC_roid,'\0',128);
	
	if (value == NULL)
		return -1;
    
    while('\0' != *F_UC_Temp_roid)
	{
		if (*F_UC_Temp_roid == '.' || *F_UC_Temp_roid == ' ')
		{
			roid->subid[F_UI_roid_count] = atoi(F_UC_roid);
			F_UI_roid_count++;
            F_UC_Temp_roid++;
			memset(F_UC_roid,'\0',128);
			F_IN_Array_roid_count = 0;
		}
		
		
		if (*F_UC_Temp_roid < '0' && *F_UC_Temp_roid >'9')
		{
			return -2;
		}
        else
		{
			F_UC_roid[F_IN_Array_roid_count] = *F_UC_Temp_roid;
			F_IN_Array_roid_count++;
			F_UC_Temp_roid++;
		}
	}
	if (F_UC_roid[1] != '\0')
	{
		roid->subid[F_UI_roid_count] = atoi(F_UC_roid);
		F_UI_roid_count++;
	}
	roid->numids = F_UI_roid_count;
	return 0;

}


ASN1_CPPLINK ASNINT32 ASN1_BER_Compare_StringtoRoid(ASNUINT8* value,RELATIVE_OID* Com_two)
{
	RELATIVE_OID Com_one;
	String_to_Roid(value,&Com_one);
	return ASN1_BER_Compare_RELATIVE_OID(&Com_one,Com_two);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Compare_RELATIVE_OID(RELATIVE_OID* Com_one,RELATIVE_OID* Com_two)
{
	ASNUINT32 F_UI_temp_count;
	F_UI_temp_count = Com_one->numids;
	
	if (Com_one->numids == Com_two->numids)
	{
		F_UI_temp_count--;
		while (F_UI_temp_count != -1)
		{
			if (Com_one->subid[F_UI_temp_count] != Com_two->subid[F_UI_temp_count])
				return -2;
			F_UI_temp_count--;
		}
		return 0;
	}
	return -1;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Compare_OBJECTIDENTIFIER(OBJECTIDENTIFIER* Com_one,OBJECTIDENTIFIER* Com_two)
{
	ASNUINT32 F_UI_temp_count;
	F_UI_temp_count = Com_one->numids;
	
	if (Com_one->numids == Com_two->numids)
	{
		F_UI_temp_count--;
		while (F_UI_temp_count != -1)
		{
			if (Com_one->subid[F_UI_temp_count] != Com_two->subid[F_UI_temp_count])
				return -2;
			F_UI_temp_count--;
		}
		return 0;
	}
	return -1;
}

