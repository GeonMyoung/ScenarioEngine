#ifndef _INFINITE_H_
#define _INFINITE_H_

#include "OS/ASN1_Sys.h"

#include "math.h"

/*datac struct for save big int*/
typedef struct datac 
{
	struct datac * next;
	ASNINT32L data; 
	ASNUINT32 datacout;
	ASNUINT32 zerobit;
}p_data;


ASN1_CPPLINK char *ITS_ASN_add(char *,char *);	/*infinitude add*/
ASN1_CPPLINK char *ITS_ASN_minus(char *,char *); /*infinitude minus*/
ASN1_CPPLINK char *ITS_ASN_multip(char *);		/*infinitude multip*/
ASN1_CPPLINK char *ITS_ASN_divide(char *);		/*infinitude divide*/
ASN1_CPPLINK p_data*ITS_ASN_savetostruct(ASNINT32L save,p_data * pcur);/*save big int to struct*/
ASN1_CPPLINK void  ITS_ASN_filldata1(p_data *pcur,ASNINT32 ch_zero);	
ASN1_CPPLINK p_data * ITS_ASN_k_malloc(void);
ASN1_CPPLINK void ITS_ASN_turn_long_save(ASNINT8 *pch,p_data *phead);	/*save big int to node*/
ASN1_CPPLINK int ITS_ASN_to_ldiv(p_data * phead);


#endif 
