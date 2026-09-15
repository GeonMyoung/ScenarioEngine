#include "Infinite_tool.h"



ASN1_CPPLINK char *ITS_ASN_add(char *p,char *q)
{
	long length;
	long lengthq;
	char *s,*r,*tempq;
	int i;
	int j;
	tempq = q;
 	while('0' == *tempq)
 		tempq++;
	length = (long)strlen(p);
	lengthq = (long)strlen(tempq);
	s = malloc(length + 1);
	if(length == 0)
		return p;
/*
		if(length<lengthq)
		{
			for(i = 0;i<=(lengthq-length);i++)
			{
				s[i] = '0';
			}
			s[length+1] = '\0';
			p -= (lengthq-length+1);
			for(i = 0;i<=(lengthq-length);i++)
				p[i] = '0';
			length = strlen(p)-1;
			for(i = 1;i<=lengthq;i++)
			{
				if((p[length-i+1] + q[lengthq-i]) > ('9'+'0'))
				{
					p[length-i+1] = p[length-i+1] + q[lengthq-i] - '9' - 1;
					p[length-i] += 1;
					j = i;
					while('9' == (p[length-j]-1))
					{
						p[length-j] = '0';
						p[length-j-1] += 1;
						if((1 == length-j-1)&& ('9' == p[length-j-1]))
						{
							p[0] = '1';
							p[1] = '0';
							break;
						}
						j++;
					}	
					continue;
				}
				p[length-i+1] += q[lengthq-i] - '0';
			}
			while('0' == *p)
				p++;
			return p;
		}*/
	
//	p--;
	s[0] = 0x30;
//	p[0] = '0';
//	strcpy(s+1,p);
	memcpy(s+1,p,length);
	r = s;
//	s[length+1] = 0;
	memset(p,0x30,length);
	for(i = 1;i<=lengthq;i++)
	{
		if((s[length-i+1] + tempq[lengthq-i]) > ('9'+'0'))
		{
			s[length-i+1] = s[length-i+1] + tempq[lengthq-i] - '9' - 1;
			s[length-i] += 1;
			j = i;
			while('9' == (s[length-j]-1))
			{
				s[length-j] = '0';
				s[length-j-1] += 1;
				if((1 == length-j-1) && ('9' == s[length-j-1]))
				{
					s[0] = '1';
					s[1] = '0';
					break;
				}
				j++;
			}	
			continue;
		}
		s[length-i+1] += tempq[lengthq-i] - '0';
	}
  	if('0' == *s)
  		s++;
	strcpy(p,s);
	free(r);
	p[length] = 0;
	return p;
}
ASN1_CPPLINK char *ITS_ASN_multip(char *p)
{
	int i = 0;
	int lengthp = (int)strlen(p);
	char *q = malloc(strlen(p)+1);
	char *r = malloc(strlen(p));
	strcpy(r,p);
//	memcpy(s,p,lengthp);
//	s[lengthp] = 0;
	strcpy(q,p);
//	memcpy(q,p,lengthp);
	q[lengthp] = '0';
	q[lengthp + 1] = 0;

	for(;i < 5;i++)
	{
		p = ITS_ASN_add(p,r);
	}
	p = ITS_ASN_add(p,q);
//	free(q);
//	free(r);
	

	return p;
}
ASN1_CPPLINK char *ITS_ASN_minus(char *p,char *q)
{
	long length;
	long lengthq;
	int i;
	int j;
	while(*p == '0')
		p++;
	
	length = (long)strlen(p);
	lengthq = (long)strlen(q);
	
	if(length<lengthq || (length == lengthq)&&strcmp(p,q)<0)
	{
		return p;
	}
	else{
		for(i = 1;i<=lengthq;i++)
		{
			if(p[length-i] < q[lengthq-i])
			{
				p[length-i] = p[length-i] - q[lengthq-i] + '9' + 1;
				p[length-i-1] -= 1;
				j = i;
				while(('0' == (p[length-j-1]+1)) && (p[0] != p[length-j-1]))
				{	
					p[length-j-1] = '9';
					p[length-j-2] -= 1;
					if((p[length-j-2]+1) == '0')
					{
						p[length-j-2] = '9';
						while(p[length-j-3] == '0')
						{
							p[length-j-3] = '9';
							j++;
						}
						if(p[length-j-3] >='0')
						{
							p[length-j-3] -= 1;
							break;
						}
					}
				}		
				continue;
			}
			p[length-i] = p[length-i] - q[lengthq-i] +'0'; 
		}
	}
	while('0' == *p)
		p++;

	return p;
}



ASN1_CPPLINK p_data * ITS_ASN_k_malloc(void)
{
	p_data *phead;
	phead=malloc(sizeof(struct datac));
	phead->next=NULL;
	return phead;
} 
ASN1_CPPLINK p_data*ITS_ASN_savetostruct(ASNINT32L save,p_data * pcur)//put data into node
{
	p_data *pnewcur;
	pnewcur=(p_data*)malloc(sizeof(struct datac));
	pnewcur->data=save;
	pcur->next   =  pnewcur; 
	pnewcur->datacout=0;
	pnewcur->zerobit=0;
	pnewcur->next=NULL;
	return pnewcur;
}

ASN1_CPPLINK void  ITS_ASN_filldata1(p_data *pcur,ASNINT32 ch_zero)
{
	ASNINT32L mid;
	ASNINT32 i;
	mid=pcur->data;
	for (i=0;mid!=0;i++)//bit count
	{
		if (mid==0)
			break;
		mid=mid/10;		
	}
	pcur->datacout=ch_zero+i;
	pcur->zerobit=ch_zero;
}
ASN1_CPPLINK void ITS_ASN_turn_long_save(ASNINT8 *pch,p_data *phead)//fetch the 6 bit data
{
	p_data *pcur;
	ASNUINT8 save_longdata[7];//5--3(128)+6=8  2^32=4294967296(10-1),
	ASNINT32 i,j;
	ASNINT32L savelong;
    pcur=phead;
	memset(save_longdata,'\0',7);
	while (*pch!='\0')
	{
		for (i=0;(i<6)&&(*pch!='\0');i++,pch++)
		{
			save_longdata[i]=*pch;
//			if (save_longdata[i]!='0')
//				j++;
		}
		j = 0;
		while(save_longdata[j] == '0')
			j++;
//		i=i-j;
		savelong=atol(save_longdata);
		
		pcur=(p_data*)ITS_ASN_savetostruct(savelong,pcur);
		ITS_ASN_filldata1(pcur,j);
		memset(save_longdata,'\0',7); 
	}
}
ASN1_CPPLINK int ITS_ASN_to_ldiv(p_data * phead)
{
	p_data *pcur;
	long divisor;
	ldiv_t x;
	ASNINT32 flag=0;
	ASNINT32 t1=0,t2=0;
	pcur=phead->next;
	divisor = pcur->data;
	while(pcur!=NULL) 
	{
		if (flag!=0)
		{
			divisor = (x.rem)*(long)pow(10,t2)+(pcur->data);
		}		
		x = ldiv(divisor,256);
		pcur->data=x.quot;
		flag=1;	
		if (pcur->next!=NULL)
		{
			t1=(pcur->next)->zerobit;
			t2=(pcur->next)->datacout;
		}
		else
		{
			t1=0;
			t2=0;
		}
		pcur=pcur->next;
	} 
	return x.rem;
}

