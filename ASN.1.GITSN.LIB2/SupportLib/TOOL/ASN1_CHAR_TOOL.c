#include "ASN1_CHAR_TOOL.h"


ASN1_CPPLINK int ASN1_Print_ASN1CHARACTERSTRING_identification_syntaxes(ASN1CHARACTERSTRING_identification_syntaxes* value,int tab_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ASN_Print_TAB(tab_value); ASN1_Print_SEQ("ASN1CHARACTERSTRING_identification_syntaxes");
		ret = ASN_Print_TAB(tab_value+1); 
	if(ret < 0) return ret;
	ret = ASN1_Print_OBJECTIDENTIFIER("abstract",&(value->abstract));
	if(ret < 0) return ret;


		ret = ASN_Print_TAB(tab_value+1); 
	if(ret < 0) return ret;
	ret = ASN1_Print_OBJECTIDENTIFIER("transfer",&(value->transfer));
	if(ret < 0) return ret;


	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_syntaxes_abstract(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 *user_value,ASNUINT32 user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_SET_OBJECTIDENTIFIER(workspace,&value->abstract,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_syntaxes_transfer(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 *user_value,ASNUINT32 user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_SET_OBJECTIDENTIFIER(workspace,&value->transfer,user_value,user_value_length);
	return ret;
}

		
//ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes_abstract(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length)
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes_abstract(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_GET_OBJECTIDENTIFIER(workspace,&value->abstract,user_value,user_value_length);
	return ret;
}

		
//ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes_transfer(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length)
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes_transfer(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_syntaxes* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_GET_OBJECTIDENTIFIER(workspace,&value->transfer,user_value,user_value_length);
	return ret;
}


ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(ASN1CHARACTERSTRING_identification_syntaxes* value)
{
	int ret = 0;
	unsigned char checkinfo_abstract[] = {0x00,0x00};

	unsigned char checkinfo_transfer[] = {0x00,0x00};


		ret = ASN1_CHECK_OBJECTIDENTIFIER(&(value->abstract),checkinfo_abstract);
	 if(ret < 0) return ret;

		ret = ASN1_CHECK_OBJECTIDENTIFIER(&(value->transfer),checkinfo_transfer);
	 if(ret < 0) return ret;

	return ret;
}

int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace *workspace, ASN1CHARACTERSTRING_identification_syntaxes *value, ASN1TagType tagFlag)
{
	int ret = 0;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0)	// (UNIVERSAL | CONSTRUCT | 16) == SEQUENCE
			return ret;
	}

	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OBJECTIDENTIFIER(workspace,&(value->abstract), ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer), ASN1IMPL)) < 0) return ret;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0)
			return ret;
	}

	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value,tagFlag);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;


	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16);

		if(ret < 0) return ret;
		ret = ASN1_BER_User_Dec_Length(workspace,&length);


		if(ret < 0) return ret;
	}

	ASN1_Save_Current_P(workspace,&_cpointer);
	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_OBJECTIDENTIFIER(workspace,&value->abstract, len, ASN1IMPL);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_OBJECTIDENTIFIER(workspace,&value->transfer, len, ASN1IMPL);
	if(ret < 0) return ret;

ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer,length);

	if (tagFlag == ASN1EXPL)
	{
		if(IfFixedLength(length) == -1)
		{
			ret = ASN1_BER_Dec_StrmEOC(workspace);
			if(ret < 0) return ret;

		}
	}

	 return ret;
}

ASN1_CPPLINK  int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,int length,ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value, int length, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = _ASN1_BER_CHECK_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value,length,tagFlag);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_abstract = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_Align_Enc_OBJECTIDENTIFIER(workspace,&(value->abstract),&consinfo_abstract);
	if(ret < 0) return ret;


	ret = ASN1_PER_Align_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer),&consinfo_transfer);
	if(ret < 0) return ret;


	return ret;
}

ASN1_CPPLINK  int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);

ASN1_CPPLINK int ASN1_PER_Align_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 ret = ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_abstract = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_Align_Dec_OBJECTIDENTIFIER(workspace,&(value->abstract),&consinfo_abstract);
	if(ret < 0) return ret;


	ret = ASN1_PER_Align_Dec_OBJECTIDENTIFIER(workspace,&(value->transfer),&consinfo_transfer);
	if(ret < 0) return ret;


	return ret;
}

ASN1_CPPLINK  int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);

ASN1_CPPLINK int ASN1_PER_Align_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value)
{
	 int ret = 0;
	 ret = ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_abstract = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(workspace,&(value->abstract),&consinfo_abstract);
	if(ret < 0) return ret;


	ret = ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer),&consinfo_transfer);
	if(ret < 0) return ret;


	return ret;
}

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 ret = ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_abstract = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(workspace,&(value->abstract),&consinfo_abstract);
	if(ret < 0) return ret;


	ret = ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(workspace,&(value->transfer),&consinfo_transfer);
	if(ret < 0) return ret;


	return ret;
}

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value)
{
	 int ret = 0;
	 ret = ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32 temp_tab_value = tab_value;
	if(xer_flag != XER_REF){/*if xer_flag start*/
	ASN1_XER_CANONICAL_Enc_Struct_Start(workspace,"syntaxes",temp_tab_value);
	tab_value += 1;
	}/*if xer_flag end*/
	ret = ASN1_XER_CANONICAL_Enc_OBJECTIDENTIFIER(workspace,&(value->abstract),"abstract",tab_value); 
	if(ret < 0) return ret;


	ret = ASN1_XER_CANONICAL_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer),"transfer",tab_value); 
	if(ret < 0) return ret;


	if(xer_flag != XER_REF)
	ASN1_XER_CANONICAL_Enc_Struct_End(workspace,"syntaxes",temp_tab_value);
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32  _loop_value = 1;
	ASNINT32  _deocde_value = 1;
	ASNINT32 temp_tab_value = tab_value;
	ASN1XERFlag _temp_xer_flag = XER_REF;
	ret = ASN1_XER_Dec_Prolog(workspace);
	if(ret < 0) return ret;
	if(xer_flag == XER_PRI){
	ret = ASN1_XER_CANONICAL_Dec_Struct_Start(workspace,"syntaxes",&_temp_xer_flag);

	if(ret < 0) return ret;
}
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"abstract")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Dec_OBJECTIDENTIFIER(workspace,&value->abstract,"abstract",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"transfer")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Dec_OBJECTIDENTIFIER(workspace,&value->transfer,"transfer",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
	if(xer_flag ==  XER_PRI){
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_CANONICAL_Dec_Struct_End(workspace,"syntaxes",&_temp_xer_flag);
	if(ret < 0) return ret;
		}
	}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = _ASN1_XER_Check_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32 temp_tab_value = tab_value;
	if(xer_flag != XER_REF){/*if xer_flag start*/
	ASN1_XER_BASIC_Enc_Struct_Start(workspace,"syntaxes",temp_tab_value);
	tab_value += 1;
	}/*if xer_flag end*/
	ret = ASN1_XER_BASIC_Enc_OBJECTIDENTIFIER(workspace,&(value->abstract),"abstract",tab_value); 
	if(ret < 0) return ret;


	ret = ASN1_XER_BASIC_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer),"transfer",tab_value); 
	if(ret < 0) return ret;


	if(xer_flag != XER_REF)
	ASN1_XER_BASIC_Enc_Struct_End(workspace,"syntaxes",temp_tab_value);
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32  _loop_value = 1;
	ASNINT32  _deocde_value = 1;
	ASNINT32 temp_tab_value = tab_value;
	ASN1XERFlag _temp_xer_flag = XER_REF;
	ret = ASN1_XER_Dec_Prolog(workspace);
	if(ret < 0) return ret;
	if(xer_flag == XER_PRI){
	ret = ASN1_XER_BASIC_Dec_Struct_Start(workspace,"syntaxes",&_temp_xer_flag);

	if(ret < 0) return ret;
}
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"abstract")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Dec_OBJECTIDENTIFIER(workspace,&value->abstract,"abstract",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"transfer")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Dec_OBJECTIDENTIFIER(workspace,&value->transfer,"transfer",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
	if(xer_flag ==  XER_PRI){
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_BASIC_Dec_Struct_End(workspace,"syntaxes",&_temp_xer_flag);
	if(ret < 0) return ret;
		}
	}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = _ASN1_XER_Check_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_Print_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value,int tab_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ASN_Print_TAB(tab_value); ASN1_Print_SEQ("ASN1CHARACTERSTRING_identification_context_negotiation");
		ret = ASN_Print_TAB(tab_value+1); 
	if(ret < 0) return ret;
	ret = ASN1_Print_INTEGER("presentation_context_id",&(value->presentation_context_id));
	if(ret < 0) return ret;


		ret = ASN_Print_TAB(tab_value+1); 
	if(ret < 0) return ret;
	ret = ASN1_Print_OBJECTIDENTIFIER("transfer_syntax",&(value->transfer_syntax));
	if(ret < 0) return ret;


	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_context_negotiation_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,INTEGER user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_SET_INTEGER(workspace,&value->presentation_context_id,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_context_negotiation_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,ASNUINT32 *user_value,ASNUINT32 user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_SET_OBJECTIDENTIFIER(workspace,&value->transfer_syntax,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_context_negotiation_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,INTEGER *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_GET_INTEGER(workspace,&value->presentation_context_id,user_value);

	return ret;
}

		
//ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_context_negotiation_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length)
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_context_negotiation_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification_context_negotiation* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_GET_OBJECTIDENTIFIER(workspace,&value->transfer_syntax,user_value,user_value_length);
	return ret;
}


ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value)
{
	int ret = 0;
	unsigned char checkinfo_presentation_context_id[] = {0x00,0x00};

	unsigned char checkinfo_transfer_syntax[] = {0x00,0x00};


		ret = ASN1_CHECK_INTEGER(&(value->presentation_context_id),checkinfo_presentation_context_id);
	 if(ret < 0) return ret;

		ret = ASN1_CHECK_OBJECTIDENTIFIER(&(value->transfer_syntax),checkinfo_transfer_syntax);
	 if(ret < 0) return ret;

	return ret;
}

int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace *workspace, ASN1CHARACTERSTRING_identification_context_negotiation *value, ASN1TagType tagFlag)
{
	int ret = 0;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0)
			return ret;
	}

	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace,&(value->presentation_context_id), ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer_syntax), ASN1IMPL)) < 0) return ret;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0)
			return ret;
	}

	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value, ASN1TagType tagFlag);

int ASN1_BER_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation *value, ASN1TagType tagFlag)
{
	 int ret = 0;

	 if ((ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value)) < 0) return ret;
	 if ((ret = ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value,tagFlag)) < 0) return ret;

	 return ret;
}

ASN1_CPPLINK int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;


	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16);

		if(ret < 0) return ret;
		ret = ASN1_BER_User_Dec_Length(workspace,&length);


		if(ret < 0) return ret;
	}

	ASN1_Save_Current_P(workspace,&_cpointer);
	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_INTEGER(workspace,&value->presentation_context_id, len, ASN1IMPL);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_OBJECTIDENTIFIER(workspace,&value->transfer_syntax, len, ASN1IMPL);
	if(ret < 0) return ret;

ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer,length);

	if (tagFlag == ASN1EXPL)
	{
		if(IfFixedLength(length) == -1)
		{
			ret = ASN1_BER_Dec_StrmEOC(workspace);
			if(ret < 0) return ret;

		}
	}

	 return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,int length,ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value, int length, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = _ASN1_BER_CHECK_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value,length,tagFlag);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_presentation_context_id = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_Align_Enc_INTEGER(workspace,&(value->presentation_context_id),&consinfo_presentation_context_id);
	if(ret < 0) return ret;


	ret = ASN1_PER_Align_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer_syntax),&consinfo_transfer_syntax);
	if(ret < 0) return ret;


	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK int ASN1_PER_Align_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value);
	 if(ret < 0) return ret;
	 ret = ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_presentation_context_id = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_Align_Dec_INTEGER(workspace,&(value->presentation_context_id),&consinfo_presentation_context_id);
	if(ret < 0) return ret;


	ret = ASN1_PER_Align_Dec_OBJECTIDENTIFIER(workspace,&(value->transfer_syntax),&consinfo_transfer_syntax);
	if(ret < 0) return ret;


	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK int ASN1_PER_Align_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value)
{
	 int ret = 0;
	 ret = ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_presentation_context_id = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace,&(value->presentation_context_id),&consinfo_presentation_context_id);
	if(ret < 0) return ret;


	ret = ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer_syntax),&consinfo_transfer_syntax);
	if(ret < 0) return ret;


	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value);
	 if(ret < 0) return ret;
	 ret = ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_presentation_context_id = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace,&(value->presentation_context_id),&consinfo_presentation_context_id);
	if(ret < 0) return ret;


	ret = ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(workspace,&(value->transfer_syntax),&consinfo_transfer_syntax);
	if(ret < 0) return ret;


	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value)
{
	 int ret = 0;
	 ret = ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32 temp_tab_value = tab_value;
	if(xer_flag != XER_REF){/*if xer_flag start*/
	ASN1_XER_CANONICAL_Enc_Struct_Start(workspace,"context-negotiation",temp_tab_value);
	tab_value += 1;
	}/*if xer_flag end*/
	ret = ASN1_XER_CANONICAL_Enc_INTEGER(workspace,&(value->presentation_context_id),"presentation-context-id",tab_value); 
	if(ret < 0) return ret;


	ret = ASN1_XER_CANONICAL_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer_syntax),"transfer-syntax",tab_value); 
	if(ret < 0) return ret;


	if(xer_flag != XER_REF)
	ASN1_XER_CANONICAL_Enc_Struct_End(workspace,"context-negotiation",temp_tab_value);
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32  _loop_value = 1;
	ASNINT32  _deocde_value = 1;
	ASNINT32 temp_tab_value = tab_value;
	ASN1XERFlag _temp_xer_flag = XER_REF;
	ret = ASN1_XER_Dec_Prolog(workspace);
	if(ret < 0) return ret;
	if(xer_flag == XER_PRI){
	ret = ASN1_XER_CANONICAL_Dec_Struct_Start(workspace,"context-negotiation",&_temp_xer_flag);

	if(ret < 0) return ret;
}
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"presentation-context-id")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Dec_INTEGER(workspace,&value->presentation_context_id,"presentation-context-id",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"transfer-syntax")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Dec_OBJECTIDENTIFIER(workspace,&value->transfer_syntax,"transfer-syntax",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
	if(xer_flag ==  XER_PRI){
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_CANONICAL_Dec_Struct_End(workspace,"context-negotiation",&_temp_xer_flag);
	if(ret < 0) return ret;
		}
	}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = _ASN1_XER_Check_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32 temp_tab_value = tab_value;
	if(xer_flag != XER_REF){/*if xer_flag start*/
	ASN1_XER_BASIC_Enc_Struct_Start(workspace,"context-negotiation",temp_tab_value);
	tab_value += 1;
	}/*if xer_flag end*/
	ret = ASN1_XER_BASIC_Enc_INTEGER(workspace,&(value->presentation_context_id),"presentation-context-id",tab_value); 
	if(ret < 0) return ret;


	ret = ASN1_XER_BASIC_Enc_OBJECTIDENTIFIER(workspace,&(value->transfer_syntax),"transfer-syntax",tab_value); 
	if(ret < 0) return ret;


	if(xer_flag != XER_REF)
	ASN1_XER_BASIC_Enc_Struct_End(workspace,"context-negotiation",temp_tab_value);
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32  _loop_value = 1;
	ASNINT32  _deocde_value = 1;
	ASNINT32 temp_tab_value = tab_value;
	ASN1XERFlag _temp_xer_flag = XER_REF;
	ret = ASN1_XER_Dec_Prolog(workspace);
	if(ret < 0) return ret;
	if(xer_flag == XER_PRI){
	ret = ASN1_XER_BASIC_Dec_Struct_Start(workspace,"context-negotiation",&_temp_xer_flag);

	if(ret < 0) return ret;
}
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"presentation-context-id")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Dec_INTEGER(workspace,&value->presentation_context_id,"presentation-context-id",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"transfer-syntax")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Dec_OBJECTIDENTIFIER(workspace,&value->transfer_syntax,"transfer-syntax",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
	if(xer_flag ==  XER_PRI){
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_BASIC_Dec_Struct_End(workspace,"context-negotiation",&_temp_xer_flag);
	if(ret < 0) return ret;
		}
	}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = _ASN1_XER_Check_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_Print_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value,int tab_value)
{
	int ret = 0;
	ASN_Print_TAB(tab_value); ASN1_Print_CHOICE("ASN1CHARACTERSTRING_identification");
	 if(value == NULL){return -1;}
	switch(value->M){
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes:
	ret = ASN1_Print_ASN1CHARACTERSTRING_identification_syntaxes(value->elements.syntaxes,tab_value+1);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax:
	ret = ASN_Print_TAB(tab_value+1); 
	if(ret < 0) return ret;
	ret = ASN1_Print_OBJECTIDENTIFIER("syntax",&value->elements.syntax);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id:
	ret = ASN_Print_TAB(tab_value+1); 
	if(ret < 0) return ret;
	ret = ASN1_Print_INTEGER("presentation_context_id",&value->elements.presentation_context_id);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation:
	ret = ASN1_Print_ASN1CHARACTERSTRING_identification_context_negotiation(value->elements.context_negotiation,tab_value+1);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax:
	ret = ASN_Print_TAB(tab_value+1); 
	if(ret < 0) return ret;
	ret = ASN1_Print_OBJECTIDENTIFIER("transfer_syntax",&value->elements.transfer_syntax);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed:
	ret = ASN_Print_TAB(tab_value+1); 
	if(ret < 0) return ret;
	ret = ASN1_Print_NULL("fixed",&value->elements.fixed);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	default: return -1;
	}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASN1CHARACTERSTRING_identification_syntaxes* user_value)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	value->elements.syntaxes = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
	memset(value->elements.syntaxes,0,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
	value->M = DEF_ASN1CHARACTERSTRING_identification_syntaxes;
	memcpy(value->elements.syntaxes,user_value,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 *user_value,ASNUINT32 user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	value->M = DEF_ASN1CHARACTERSTRING_identification_syntax;
	ret = ASN1_SET_OBJECTIDENTIFIER(workspace,&value->elements.syntax,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,INTEGER user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	value->M = DEF_ASN1CHARACTERSTRING_identification_presentation_context_id;
	ret = ASN1_SET_INTEGER(workspace,&value->elements.presentation_context_id,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASN1CHARACTERSTRING_identification_context_negotiation* user_value)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	value->elements.context_negotiation = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
	memset(value->elements.context_negotiation,0,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
	value->M = DEF_ASN1CHARACTERSTRING_identification_context_negotiation;
	memcpy(value->elements.context_negotiation,user_value,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 *user_value,ASNUINT32 user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	value->M = DEF_ASN1CHARACTERSTRING_identification_transfer_syntax;
	ret = ASN1_SET_OBJECTIDENTIFIER(workspace,&value->elements.transfer_syntax,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification_fixed(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT8 user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	value->M = DEF_ASN1CHARACTERSTRING_identification_fixed;
	ret = ASN1_SET_NULL(workspace,&value->elements.fixed,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASN1CHARACTERSTRING_identification_syntaxes** user_value)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	if(value->M == DEF_ASN1CHARACTERSTRING_identification_syntaxes){
	*user_value = value->elements.syntaxes;
	}
	else
 		return -2;
	return ret;
}

		
//ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length)
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	if(value->M == DEF_ASN1CHARACTERSTRING_identification_syntax){
	ret = ASN1_GET_OBJECTIDENTIFIER(workspace,&value->elements.syntax,user_value,user_value_length);
	}
	else
 		return -2;
	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,INTEGER *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	if(value->M == DEF_ASN1CHARACTERSTRING_identification_presentation_context_id){
	ret = ASN1_GET_INTEGER(workspace,&value->elements.presentation_context_id,user_value);

	}
	else
 		return -2;
	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASN1CHARACTERSTRING_identification_context_negotiation** user_value)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	if(value->M == DEF_ASN1CHARACTERSTRING_identification_context_negotiation){
	*user_value = value->elements.context_negotiation;
	}
	else
 		return -2;
	return ret;
}

		
//ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 **user_value,ASNUINT32 *user_value_length)
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT32 *user_value,ASNUINT32 *user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	if(value->M == DEF_ASN1CHARACTERSTRING_identification_transfer_syntax){
	ret = ASN1_GET_OBJECTIDENTIFIER(workspace,&value->elements.transfer_syntax,user_value,user_value_length);
	}
	else
 		return -2;
	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification_fixed(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING_identification* value,ASNUINT8 *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	if(value->M == DEF_ASN1CHARACTERSTRING_identification_fixed){
	ret = ASN1_GET_NULL(workspace,&value->elements.fixed,user_value);

	}
	else
 		return -2;
	return ret;
}

ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value)
{
	int ret = 0;
	unsigned char checkinfo_syntaxes[] = {0x00,0x00};
	unsigned char checkinfo_syntax[] = {0x00,0x00};
	unsigned char checkinfo_presentation_context_id[] = {0x00,0x00};
	unsigned char checkinfo_context_negotiation[] = {0x00,0x00};
	unsigned char checkinfo_transfer_syntax[] = {0x00,0x00};
	unsigned char checkinfo_fixed[] = {0x00,0x00};


	switch(value->M)
	{
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes:
		ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_syntaxes(value->elements.syntaxes);
		if(ret < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax:
		ret = ASN1_CHECK_OBJECTIDENTIFIER(&value->elements.syntax, checkinfo_syntax);
		if(ret < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id:
		ret = ASN1_CHECK_INTEGER(&value->elements.presentation_context_id, checkinfo_presentation_context_id);
		if(ret < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation:
		ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification_context_negotiation(value->elements.context_negotiation);
		if(ret < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax:
		ret = ASN1_CHECK_OBJECTIDENTIFIER(&value->elements.transfer_syntax, checkinfo_transfer_syntax);
		if(ret < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed:
		ret = ASN1_CHECK_NULL(&value->elements.fixed, checkinfo_fixed);
		if(ret < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
ASN1_CPPLINK int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value, ASN1TagType tagFlag);

int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace *workspace, ASN1CHARACTERSTRING_identification *value, ASN1TagType tagFlag)
{
	int ret = 0;

	switch(value->M)
	{
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace, value->elements.syntaxes, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.syntax), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->elements.presentation_context_id), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace, value->elements.context_negotiation, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.transfer_syntax), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_NULL(workspace, ASN1IMPL)) < 0) return ret;
		break;
	}
	 return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification(workspace,value,tagFlag);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,int length,ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,int length,ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;


	value->M = 0;
	ret = ASN1_BER_GET_Tag(workspace,&tag);
	if(ret < 0) return ret;

	switch(tag)
	{
	case ITS_ASN_CONT|ITS_ASN_CONS|0:
	value->elements.syntaxes = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
	memset(value->elements.syntaxes,0,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
		ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|0);
	if(ret < 0) return ret;

		ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

		ret = ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace, value->elements.syntaxes, len, ASN1IMPL);
	if(ret < 0) return ret;

		if(IfFixedLength(len) == -1)
		{
			ret = ASN1_BER_Dec_StrmEOC(workspace);
	if(ret < 0) return ret;

		}
		value->M = DEF_ASN1CHARACTERSTRING_identification_syntaxes;
		break;
	case ITS_ASN_CONT|ITS_ASN_PRIM|1:
		ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1);
	if(ret < 0) return ret;

		ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

		ret = ASN1_BER_Dec_OBJECTIDENTIFIER(workspace,&value->elements.syntax, len, ASN1IMPL);
	if(ret < 0) return ret;

		value->M = DEF_ASN1CHARACTERSTRING_identification_syntax;
		break;
	case ITS_ASN_CONT|ITS_ASN_PRIM|2:
		ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2);
	if(ret < 0) return ret;

		ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

		ret = ASN1_BER_Dec_INTEGER(workspace,&value->elements.presentation_context_id, len, ASN1IMPL);
	if(ret < 0) return ret;

		value->M = DEF_ASN1CHARACTERSTRING_identification_presentation_context_id;
		break;
	case ITS_ASN_CONT|ITS_ASN_CONS|3:
	value->elements.context_negotiation = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
	memset(value->elements.context_negotiation,0,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
		ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|3);
	if(ret < 0) return ret;

		ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

		ret = ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace, value->elements.context_negotiation, len, ASN1IMPL);
	if(ret < 0) return ret;

		if(IfFixedLength(len) == -1)
		{
			ret = ASN1_BER_Dec_StrmEOC(workspace);
	if(ret < 0) return ret;

		}
		value->M = DEF_ASN1CHARACTERSTRING_identification_context_negotiation;
		break;
	case ITS_ASN_CONT|ITS_ASN_PRIM|4:
		ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|4);
	if(ret < 0) return ret;

		ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

		ret = ASN1_BER_Dec_OBJECTIDENTIFIER(workspace,&value->elements.transfer_syntax, len, ASN1IMPL);
	if(ret < 0) return ret;

		value->M = DEF_ASN1CHARACTERSTRING_identification_transfer_syntax;
		break;
	case ITS_ASN_CONT|ITS_ASN_PRIM|5:
		ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|5);
	if(ret < 0) return ret;

		ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

		ret = ASN1_BER_Dec_NULL(workspace, ASN1IMPL);
	if(ret < 0) return ret;

		value->M = DEF_ASN1CHARACTERSTRING_identification_fixed;
		break;
	}


	 return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,int length,ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value, int length, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = _ASN1_BER_CHECK_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification(workspace,value,length,tagFlag);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_syntaxes = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_presentation_context_id = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_context_negotiation = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_fixed = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ASNINT64 ui;
	ASNBOOL extbit=1;
	switch (value->M){
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes: ui = 0; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax: ui = 1; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id: ui = 2; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation: ui = 3; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax: ui = 4; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed: ui = 5; extbit = 0; break;
	default: break;
	}
	ret= ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit,0,6);
	if(ret < 0) return ret;
	switch(value->M){
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes:
	ret = ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace, value->elements.syntaxes);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax:
	ret = ASN1_PER_Align_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.syntax),&consinfo_syntax);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id:
	ret = ASN1_PER_Align_Enc_INTEGER(workspace,&(value->elements.presentation_context_id),&consinfo_presentation_context_id);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation:
	ret = ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace, value->elements.context_negotiation);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax:
	ret = ASN1_PER_Align_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.transfer_syntax),&consinfo_transfer_syntax);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed:
	/*NULL NOT Encode Of PER ruler!!*/

	if (ret != 0) return -1;
	break;
	default: break;
}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK int ASN1_PER_Align_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 ret = ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification(workspace,value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_syntaxes = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_presentation_context_id = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_context_negotiation = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_fixed = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace,&ui,&extbit,0,6);

	if(ret < 0) return ret;
	if(extbit == 0){
		switch(ui){
	case 0: index = DEF_ASN1CHARACTERSTRING_identification_syntaxes;
	value->elements.syntaxes = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
	memset(value->elements.syntaxes,0,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
	break;
	case 1: index = DEF_ASN1CHARACTERSTRING_identification_syntax;
	break;
	case 2: index = DEF_ASN1CHARACTERSTRING_identification_presentation_context_id;
	break;
	case 3: index = DEF_ASN1CHARACTERSTRING_identification_context_negotiation;
	value->elements.context_negotiation = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
	memset(value->elements.context_negotiation,0,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
	break;
	case 4: index = DEF_ASN1CHARACTERSTRING_identification_transfer_syntax;
	break;
	case 5: index = DEF_ASN1CHARACTERSTRING_identification_fixed;
	break;
		default: break;
	}
	}
	else{
		switch(ui){
		default: break;	
	}
	}
	ret = ASN1_GetM(&value->M,index);

	if(ret < 0) return ret;
	switch(index){
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes:
	ret = ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace, value->elements.syntaxes);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax:
	ret = ASN1_PER_Align_Dec_OBJECTIDENTIFIER(workspace,&(value->elements.syntax),&consinfo_syntax);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id:
	ret = ASN1_PER_Align_Dec_INTEGER(workspace,&(value->elements.presentation_context_id),&consinfo_presentation_context_id);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation:
	ret = ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace, value->elements.context_negotiation);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax:
	ret = ASN1_PER_Align_Dec_OBJECTIDENTIFIER(workspace,&(value->elements.transfer_syntax),&consinfo_transfer_syntax);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed:
	/*NULL NOT Decode Of PER ruler!!*/

	if (ret!= 0) return -1;
	break;
	default: ret = ASN1_PER_Dec_unKnown(workspace,ALIGN);break;
	}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK int ASN1_PER_Align_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value)
{
	 int ret = 0;
	 ret = ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification(workspace,value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_syntaxes = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_presentation_context_id = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_context_negotiation = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_fixed = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ASNINT64 ui;
	ASNBOOL extbit=1;
	switch (value->M){
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes: ui = 0; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax: ui = 1; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id: ui = 2; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation: ui = 3; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax: ui = 4; extbit = 0; break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed: ui = 5; extbit = 0; break;
	default: break;
	}
	ret= ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit,0,6);
	if(ret < 0) return ret;
	switch(value->M){
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes:
	ret = ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace, value->elements.syntaxes);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax:
	ret = ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.syntax),&consinfo_syntax);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id:
	ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace,&(value->elements.presentation_context_id),&consinfo_presentation_context_id);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation:
	ret = ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace, value->elements.context_negotiation);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax:
	ret = ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.transfer_syntax),&consinfo_transfer_syntax);
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed:
	/*NULL NOT Encode Of PER ruler!!*/

	if (ret != 0) return -1;
	break;
	default: break;
}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 ret = ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification(workspace,value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_syntaxes = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_presentation_context_id = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_context_negotiation = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_transfer_syntax = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_fixed = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace,&ui,&extbit,0,6);

	if(ret < 0) return ret;
	if(extbit == 0){
		switch(ui){
	case 0: index = DEF_ASN1CHARACTERSTRING_identification_syntaxes;
	value->elements.syntaxes = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
	memset(value->elements.syntaxes,0,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
	break;
	case 1: index = DEF_ASN1CHARACTERSTRING_identification_syntax;
	break;
	case 2: index = DEF_ASN1CHARACTERSTRING_identification_presentation_context_id;
	break;
	case 3: index = DEF_ASN1CHARACTERSTRING_identification_context_negotiation;
	value->elements.context_negotiation = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
	memset(value->elements.context_negotiation,0,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
	break;
	case 4: index = DEF_ASN1CHARACTERSTRING_identification_transfer_syntax;
	break;
	case 5: index = DEF_ASN1CHARACTERSTRING_identification_fixed;
	break;
		default: break;
	}
	}
	else{
		switch(ui){
		default: break;	
	}
	}
	ret = ASN1_GetM(&value->M,index);

	if(ret < 0) return ret;
	switch(index){
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes:
	ret = ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace, value->elements.syntaxes);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax:
	ret = ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(workspace,&(value->elements.syntax),&consinfo_syntax);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id:
	ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace,&(value->elements.presentation_context_id),&consinfo_presentation_context_id);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation:
	ret = ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace, value->elements.context_negotiation);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax:
	ret = ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(workspace,&(value->elements.transfer_syntax),&consinfo_transfer_syntax);
	if(ret < 0) return ret;


	if (ret!= 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed:
	/*NULL NOT Decode Of PER ruler!!*/

	if (ret!= 0) return -1;
	break;
	default: ret = ASN1_PER_Dec_unKnown(workspace,UNALIGN);break;
	}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value)
{
	 int ret = 0;
	 ret = ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification(workspace,value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,int tab_vlaue);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,int tab_vlaue);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32 temp_tab_value = tab_value;
	if(xer_flag != XER_REF){/*if xer_flag start*/
	ASN1_XER_CANONICAL_Enc_Struct_Start(workspace,"identification",temp_tab_value);
	tab_value += 1;
	}/*if xer_flag end*/
	switch(value->M){
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes:
	ret = ASN1_XER_CANONICAL_Enc_Struct_Start(workspace,"syntaxes",tab_value);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value->elements.syntaxes,XER_REF,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Enc_Struct_End(workspace,"syntaxes",tab_value);

	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax:
ret = ASN1_XER_CANONICAL_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.syntax),"syntax",tab_value); 
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id:
ret = ASN1_XER_CANONICAL_Enc_INTEGER(workspace,&(value->elements.presentation_context_id),"presentation-context-id",tab_value); 
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation:
	ret = ASN1_XER_CANONICAL_Enc_Struct_Start(workspace,"context-negotiation",tab_value);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value->elements.context_negotiation,XER_REF,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Enc_Struct_End(workspace,"context-negotiation",tab_value);

	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax:
ret = ASN1_XER_CANONICAL_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.transfer_syntax),"transfer-syntax",tab_value); 
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed:
ret = ASN1_XER_CANONICAL_Enc_NULL(workspace,&(value->elements.fixed),"fixed",tab_value); 
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	default: return -1;
	}
	if(xer_flag != XER_REF)
	ASN1_XER_CANONICAL_Enc_Struct_End(workspace,"identification",temp_tab_value);
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,int tab_value);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32  _loop_value = 1;
	ASNINT32  _deocde_value = 1;
	ASNINT32 temp_tab_value = tab_value;
	ASN1XERFlag _temp_xer_flag = XER_REF;
	value->M = 0;
	ret = ASN1_XER_Dec_Prolog(workspace);
	if(ret < 0) return ret;
	if(xer_flag == XER_PRI){
	ret = ASN1_XER_CANONICAL_Dec_Struct_Start(workspace,"identification",&_temp_xer_flag);
	if(ret < 0) return ret;
}
	if(!Start_strcmp(workspace,"syntaxes")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	value->elements.syntaxes = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
	memset(value->elements.syntaxes,0,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
		ret = ASN1_XER_CANONICAL_Dec_Struct_Start(workspace,"syntaxes",&_temp_xer_flag);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value->elements.syntaxes,_temp_xer_flag,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_Dec_CANONICAL_Format(workspace);
	if(ret < 0) return ret;
	if(_temp_xer_flag != XER_NULL){/*if temp_xer_flag start*/
	ret = ASN1_XER_CANONICAL_Dec_Struct_End(workspace,"syntaxes",&_temp_xer_flag);

	if(ret < 0) return ret;
	}/*if temp_xer_flag end*/


	value->M = DEF_ASN1CHARACTERSTRING_identification_syntaxes;
	}/*if end*/
	else if(!Start_strcmp(workspace,"syntax")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Dec_OBJECTIDENTIFIER(workspace,&value->elements.syntax,"syntax",tab_value); 
	if(ret < 0) return ret;


	value->M = DEF_ASN1CHARACTERSTRING_identification_syntax;
	}/*if end*/
	else if(!Start_strcmp(workspace,"presentation-context-id")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Dec_INTEGER(workspace,&value->elements.presentation_context_id,"presentation-context-id",tab_value); 
	if(ret < 0) return ret;


	value->M = DEF_ASN1CHARACTERSTRING_identification_presentation_context_id;
	}/*if end*/
	else if(!Start_strcmp(workspace,"context-negotiation")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	value->elements.context_negotiation = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
	memset(value->elements.context_negotiation,0,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
		ret = ASN1_XER_CANONICAL_Dec_Struct_Start(workspace,"context-negotiation",&_temp_xer_flag);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value->elements.context_negotiation,_temp_xer_flag,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_Dec_CANONICAL_Format(workspace);
	if(ret < 0) return ret;
	if(_temp_xer_flag != XER_NULL){/*if temp_xer_flag start*/
	ret = ASN1_XER_CANONICAL_Dec_Struct_End(workspace,"context-negotiation",&_temp_xer_flag);

	if(ret < 0) return ret;
	}/*if temp_xer_flag end*/


	value->M = DEF_ASN1CHARACTERSTRING_identification_context_negotiation;
	}/*if end*/
	else if(!Start_strcmp(workspace,"transfer-syntax")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Dec_OBJECTIDENTIFIER(workspace,&value->elements.transfer_syntax,"transfer-syntax",tab_value); 
	if(ret < 0) return ret;


	value->M = DEF_ASN1CHARACTERSTRING_identification_transfer_syntax;
	}/*if end*/
	else if(!Start_strcmp(workspace,"fixed")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Dec_NULL(workspace,&value->elements.fixed,"fixed",tab_value); 
	if(ret < 0) return ret;


	value->M = DEF_ASN1CHARACTERSTRING_identification_fixed;
	}/*if end*/
	if(xer_flag ==  XER_PRI){
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_CANONICAL_Dec_Struct_End(workspace,"identification",&_temp_xer_flag);
	if(ret < 0) return ret;
		}
	}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = _ASN1_XER_Check_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,int tab_vlaue);
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,int tab_vlaue);

ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32 temp_tab_value = tab_value;
	if(xer_flag != XER_REF){/*if xer_flag start*/
	ASN1_XER_BASIC_Enc_Struct_Start(workspace,"identification",temp_tab_value);
	tab_value += 1;
	}/*if xer_flag end*/
	switch(value->M){
	case DEF_ASN1CHARACTERSTRING_identification_syntaxes:
	ret = ASN1_XER_BASIC_Enc_Struct_Start(workspace,"syntaxes",tab_value);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value->elements.syntaxes,XER_REF,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Enc_Struct_End(workspace,"syntaxes",tab_value);

	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_syntax:
ret = ASN1_XER_BASIC_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.syntax),"syntax",tab_value); 
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_presentation_context_id:
ret = ASN1_XER_BASIC_Enc_INTEGER(workspace,&(value->elements.presentation_context_id),"presentation-context-id",tab_value); 
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_context_negotiation:
	ret = ASN1_XER_BASIC_Enc_Struct_Start(workspace,"context-negotiation",tab_value);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value->elements.context_negotiation,XER_REF,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Enc_Struct_End(workspace,"context-negotiation",tab_value);

	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_transfer_syntax:
ret = ASN1_XER_BASIC_Enc_OBJECTIDENTIFIER(workspace,&(value->elements.transfer_syntax),"transfer-syntax",tab_value); 
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	case DEF_ASN1CHARACTERSTRING_identification_fixed:
ret = ASN1_XER_BASIC_Enc_NULL(workspace,&(value->elements.fixed),"fixed",tab_value); 
	if(ret < 0) return ret;


	if (ret != 0) return -1;
	break;
	default: return -1;
	}
	if(xer_flag != XER_REF)
	ASN1_XER_BASIC_Enc_Struct_End(workspace,"identification",temp_tab_value);
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_syntaxes* value,ASN1XERFlag xer_flag,int tab_value);
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification_context_negotiation* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32  _loop_value = 1;
	ASNINT32  _deocde_value = 1;
	ASNINT32 temp_tab_value = tab_value;
	ASN1XERFlag _temp_xer_flag = XER_REF;
	value->M = 0;
	ret = ASN1_XER_Dec_Prolog(workspace);
	if(ret < 0) return ret;
	if(xer_flag == XER_PRI){
	ret = ASN1_XER_BASIC_Dec_Struct_Start(workspace,"identification",&_temp_xer_flag);
	if(ret < 0) return ret;
}
	if(!Start_strcmp(workspace,"syntaxes")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	value->elements.syntaxes = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
	memset(value->elements.syntaxes,0,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));
		ret = ASN1_XER_BASIC_Dec_Struct_Start(workspace,"syntaxes",&_temp_xer_flag);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value->elements.syntaxes,_temp_xer_flag,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_Dec_BASIC_Format(workspace);
	if(ret < 0) return ret;
	if(_temp_xer_flag != XER_NULL){/*if temp_xer_flag start*/
	ret = ASN1_XER_BASIC_Dec_Struct_End(workspace,"syntaxes",&_temp_xer_flag);

	if(ret < 0) return ret;
	}/*if temp_xer_flag end*/


	value->M = DEF_ASN1CHARACTERSTRING_identification_syntaxes;
	}/*if end*/
	else if(!Start_strcmp(workspace,"syntax")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Dec_OBJECTIDENTIFIER(workspace,&value->elements.syntax,"syntax",tab_value); 
	if(ret < 0) return ret;


	value->M = DEF_ASN1CHARACTERSTRING_identification_syntax;
	}/*if end*/
	else if(!Start_strcmp(workspace,"presentation-context-id")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Dec_INTEGER(workspace,&value->elements.presentation_context_id,"presentation-context-id",tab_value); 
	if(ret < 0) return ret;


	value->M = DEF_ASN1CHARACTERSTRING_identification_presentation_context_id;
	}/*if end*/
	else if(!Start_strcmp(workspace,"context-negotiation")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	value->elements.context_negotiation = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
	memset(value->elements.context_negotiation,0,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));
		ret = ASN1_XER_BASIC_Dec_Struct_Start(workspace,"context-negotiation",&_temp_xer_flag);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value->elements.context_negotiation,_temp_xer_flag,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_Dec_BASIC_Format(workspace);
	if(ret < 0) return ret;
	if(_temp_xer_flag != XER_NULL){/*if temp_xer_flag start*/
	ret = ASN1_XER_BASIC_Dec_Struct_End(workspace,"context-negotiation",&_temp_xer_flag);

	if(ret < 0) return ret;
	}/*if temp_xer_flag end*/


	value->M = DEF_ASN1CHARACTERSTRING_identification_context_negotiation;
	}/*if end*/
	else if(!Start_strcmp(workspace,"transfer-syntax")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Dec_OBJECTIDENTIFIER(workspace,&value->elements.transfer_syntax,"transfer-syntax",tab_value); 
	if(ret < 0) return ret;


	value->M = DEF_ASN1CHARACTERSTRING_identification_transfer_syntax;
	}/*if end*/
	else if(!Start_strcmp(workspace,"fixed")){/*if start*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Dec_NULL(workspace,&value->elements.fixed,"fixed",tab_value); 
	if(ret < 0) return ret;


	value->M = DEF_ASN1CHARACTERSTRING_identification_fixed;
	}/*if end*/
	if(xer_flag ==  XER_PRI){
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_BASIC_Dec_Struct_End(workspace,"identification",&_temp_xer_flag);
	if(ret < 0) return ret;
		}
	}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = _ASN1_XER_Check_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_Print_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value,int tab_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ASN_Print_TAB(tab_value); ASN1_Print_SEQ("ASN1CHARACTERSTRING");
		ret = ASN1_Print_ASN1CHARACTERSTRING_identification(value->identification,tab_value+1);
	if(ret < 0) return ret;


		ret = ASN_Print_TAB(tab_value+1); 
	if(ret < 0) return ret;
	ret = ASN1_Print_OCTETSTRING("string_value",&(value->string_value),tab_value+1);
	if(ret < 0) return ret;


	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASN1CHARACTERSTRING_identification* user_value)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));
	memcpy(value->identification,user_value,sizeof(ASN1CHARACTERSTRING_identification));

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_ASN1CHARACTERSTRING_string_value(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT8 *user_value,ASNUINT32 user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_SET_OCTETSTRING(workspace,&value->string_value,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASN1CHARACTERSTRING_identification** user_value)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	*user_value = value->identification;
	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_ASN1CHARACTERSTRING_string_value(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT8 **user_value,ASNUINT32 *user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_GET_OCTETSTRING(workspace,&value->string_value,user_value,user_value_length);
	return ret;
}

ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING_identification(ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value)
{
	int ret = 0;
	unsigned char checkinfo_identification[] = {0x00,0x00};

	unsigned char checkinfo_string_value[] = {0x00,0x00};


	ret = ASN1_CHECK_ASN1CHARACTERSTRING_identification(value->identification);
	if(ret < 0) return ret;

	ret = ASN1_CHECK_OCTETSTRING(&(value->string_value), checkinfo_string_value);
	if(ret < 0) return ret;

	return ret;
}
ASN1_CPPLINK int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value, ASN1TagType tagFlag)
{
	int ret = 0;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 29)) < 0)
			return ret;
	}

	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;		// (CONTEXT-SPECIFIC | CONSTRUCT | 0)
	if ((ret = ASN1_BER_Data_Enc_ASN1CHARACTERSTRING_identification(workspace, value->identification, ASN1IMPL)) < 0) return ret;	// ignore TAG flag for CHOICE
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;

	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;		// (CONTEXT_SPECIFIC | PRIMITIVE | 2)
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace,&(value->string_value), ASN1IMPL)) < 0) return ret;

	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_Enc_StrmEOC(workspace);

		if(ret < 0) return ret;
	}

	 return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK int ASN1_BER_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value, ASN1TagType tagFlag);

int ASN1_BER_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace *workspace, ASN1CHARACTERSTRING *value, ASN1TagType tagFlag)
{
	 int ret = 0;
	 if ((ret = ASN1_CHECK_ASN1CHARACTERSTRING(value)) < 0) return ret;
	 if ((ret = ASN1_BER_Data_Enc_ASN1CHARACTERSTRING(workspace, value, tagFlag)) < 0) return ret;
	 return ret;
}
int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace *workspace, ASN1CHARACTERSTRING_identification *value, int length, ASN1TagType tagFlag);

int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace *workspace, ASN1CHARACTERSTRING *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));

	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|29);

		if(ret < 0) return ret;
		ret = ASN1_BER_User_Dec_Length(workspace,&length);


		if(ret < 0) return ret;
	}

	ASN1_Save_Current_P(workspace,&_cpointer);
	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|0);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Data_Dec_ASN1CHARACTERSTRING_identification(workspace, value->identification, len, ASN1IMPL);
	if(ret < 0) return ret;

	if(IfFixedLength(len) == -1)
	{
		ret = ASN1_BER_Dec_StrmEOC(workspace);
	if(ret < 0) return ret;

	}
	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_OCTETSTRING(workspace,&value->string_value, len, ASN1IMPL);
	if(ret < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer,length);

	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			ret = ASN1_BER_Dec_StrmEOC(workspace);
			if(ret < 0) return ret;
		}
	}

	 return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK int ASN1_BER_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,int length,ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value, int length, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = _ASN1_BER_CHECK_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Dec_ASN1CHARACTERSTRING(workspace,value,length,tagFlag);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING(value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_identification = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_string_value = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING_identification(workspace, value->identification);
	if(ret < 0) return ret;


	ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace,&(value->string_value),&consinfo_string_value);
	if(ret < 0) return ret;


	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK int ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value);

ASN1_CPPLINK int ASN1_PER_Align_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING(value);
	 if(ret < 0) return ret;
	 ret = ASN1_PER_Align_Data_Enc_ASN1CHARACTERSTRING(workspace,value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_identification = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_string_value = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));
	ret = ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING_identification(workspace, value->identification);
	if(ret < 0) return ret;


	ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace,&(value->string_value),&consinfo_string_value);
	if(ret < 0) return ret;


	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK int ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value);

ASN1_CPPLINK int ASN1_PER_Align_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value)
{
	 int ret = 0;
	 ret = ASN1_PER_Align_Data_Dec_ASN1CHARACTERSTRING(workspace,value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING(value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_identification = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_string_value = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	ret = ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING_identification(workspace, value->identification);
	if(ret < 0) return ret;


	ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace,&(value->string_value),&consinfo_string_value);
	if(ret < 0) return ret;


	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING(value);
	 if(ret < 0) return ret;
	 ret = ASN1_PER_UNAlign_Data_Enc_ASN1CHARACTERSTRING(workspace,value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value)
{

	int ret = 0;
	struct Asn1ConsInfo consinfo_identification = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	struct Asn1ConsInfo consinfo_string_value = {-9223372036854775807,9223372036854775807,NULL,0,UNCONS,0,0};
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));
	ret = ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING_identification(workspace, value->identification);
	if(ret < 0) return ret;


	ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace,&(value->string_value),&consinfo_string_value);
	if(ret < 0) return ret;


	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value);

ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value)
{
	 int ret = 0;
	 ret = ASN1_PER_UNAlign_Data_Dec_ASN1CHARACTERSTRING(workspace,value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING(value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,int tab_vlaue);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32 temp_tab_value = tab_value;
// 	if(xer_flag != XER_REF){/*if xer_flag start*/
// 	ASN1_XER_CANONICAL_Enc_Struct_Start(workspace,"ASN1CHARACTERSTRING",temp_tab_value);
// 	tab_value += 1;
// 	}/*if xer_flag end*/
		ret = ASN1_XER_CANONICAL_Enc_Struct_Start(workspace,"identification",tab_value);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING_identification(workspace,value->identification,XER_REF,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Enc_Struct_End(workspace,"identification",tab_value);

	if(ret < 0) return ret;


	ret = ASN1_XER_CANONICAL_Enc_OCTETSTRING(workspace,&(value->string_value),"string-value",tab_value); 
	if(ret < 0) return ret;


// 	if(xer_flag != XER_REF)
// 	ASN1_XER_CANONICAL_Enc_Struct_End(workspace,"ASN1CHARACTERSTRING",temp_tab_value);
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING(value);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_CANONICAL_Data_Enc_ASN1CHARACTERSTRING(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32  _loop_value = 1;
	ASNINT32  _deocde_value = 1;
	ASNINT32 temp_tab_value = tab_value;
	ASN1XERFlag _temp_xer_flag = XER_REF;
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));
	ret = ASN1_XER_Dec_Prolog(workspace);
	if(ret < 0) return ret;
// 	if(xer_flag == XER_PRI){
// 	ret = ASN1_XER_CANONICAL_Dec_Struct_Start(workspace,"ASN1CHARACTERSTRING",&_temp_xer_flag);
// 
// 	if(ret < 0) return ret;
// }
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"identification")){/*if start*/
		ret = ASN1_XER_CANONICAL_Dec_Struct_Start(workspace,"identification",&_temp_xer_flag);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING_identification(workspace,value->identification,_temp_xer_flag,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_Dec_CANONICAL_Format(workspace);
	if(ret < 0) return ret;
	if(_temp_xer_flag != XER_NULL){/*if temp_xer_flag start*/
	ret = ASN1_XER_CANONICAL_Dec_Struct_End(workspace,"identification",&_temp_xer_flag);

	if(ret < 0) return ret;
	}/*if temp_xer_flag end*/


	}/*if end*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"string-value")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_CANONICAL_Dec_OCTETSTRING(workspace,&value->string_value,"string-value",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
// 	if(xer_flag ==  XER_PRI){
// 		if(_temp_xer_flag != XER_NULL){
// 	ret = ASN1_XER_CANONICAL_Dec_Struct_End(workspace,"ASN1CHARACTERSTRING",&_temp_xer_flag);
// 	if(ret < 0) return ret;
// 		}
// 	}
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK int ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_CANONICAL_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = _ASN1_XER_Check_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_CANONICAL_Data_Dec_ASN1CHARACTERSTRING(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING(value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,int tab_vlaue);

ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32 temp_tab_value = tab_value;
// 	if(xer_flag != XER_REF){/*if xer_flag start*/
// 	ASN1_XER_BASIC_Enc_Struct_Start(workspace,"ASN1CHARACTERSTRING",temp_tab_value);
// 	tab_value += 1;
// 	}/*if xer_flag end*/
		ret = ASN1_XER_BASIC_Enc_Struct_Start(workspace,"identification",tab_value);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING_identification(workspace,value->identification,XER_REF,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Enc_Struct_End(workspace,"identification",tab_value);

	if(ret < 0) return ret;


	ret = ASN1_XER_BASIC_Enc_OCTETSTRING(workspace,&(value->string_value),"string-value",tab_value); 
	if(ret < 0) return ret;


// 	if(xer_flag != XER_REF)
// 	ASN1_XER_BASIC_Enc_Struct_End(workspace,"ASN1CHARACTERSTRING",temp_tab_value);
	return ret;
}
ASN1_CPPLINK int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK int ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Enc_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING(value);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_BASIC_Data_Enc_ASN1CHARACTERSTRING(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK  int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING_identification* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{

	int ret = 0;
	ASNINT32  _loop_value = 1;
	ASNINT32  _deocde_value = 1;
	ASNINT32 temp_tab_value = tab_value;
	ASN1XERFlag _temp_xer_flag = XER_REF;
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));
	ret = ASN1_XER_Dec_Prolog(workspace);
	if(ret < 0) return ret;
// 	if(xer_flag == XER_PRI){
// 	ret = ASN1_XER_BASIC_Dec_Struct_Start(workspace,"ASN1CHARACTERSTRING",&_temp_xer_flag);
// 
// 	if(ret < 0) return ret;
// }
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"identification")){/*if start*/
		ret = ASN1_XER_BASIC_Dec_Struct_Start(workspace,"identification",&_temp_xer_flag);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING_identification(workspace,value->identification,_temp_xer_flag,tab_value+1);

	if(ret < 0) return ret;
	ret = ASN1_XER_Dec_BASIC_Format(workspace);
	if(ret < 0) return ret;
	if(_temp_xer_flag != XER_NULL){/*if temp_xer_flag start*/
	ret = ASN1_XER_BASIC_Dec_Struct_End(workspace,"identification",&_temp_xer_flag);

	if(ret < 0) return ret;
	}/*if temp_xer_flag end*/


	}/*if end*/
		if(_temp_xer_flag != XER_NULL){
	ret = ASN1_XER_Dec_Format(workspace);
	if(ret < 0) return ret;
	}
	if(!Start_strcmp(workspace,"string-value")){/*if start*/
	ret = ASN1_XER_Dec_Prolog(workspace);

	if(ret < 0) return ret;
	ret = ASN1_XER_BASIC_Dec_OCTETSTRING(workspace,&value->string_value,"string-value",tab_value); 
	if(ret < 0) return ret;


	}/*if end*/
// 	if(xer_flag ==  XER_PRI){
// 		if(_temp_xer_flag != XER_NULL){
// 	ret = ASN1_XER_BASIC_Dec_Struct_End(workspace,"ASN1CHARACTERSTRING",&_temp_xer_flag);
// 	if(ret < 0) return ret;
// 		}
// 	}
	return ret;
}
ASN1_CPPLINK  int ASN1_CHECK_ASN1CHARACTERSTRING(ASN1CHARACTERSTRING* value);
ASN1_CPPLINK  int ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,int tab_value);

ASN1_CPPLINK int ASN1_XER_BASIC_Dec_ASN1CHARACTERSTRING(ASN1WorkSpace* workspace, ASN1CHARACTERSTRING* value,ASN1XERFlag xer_flag,ASNINT32 tab_value)
{
	 int ret = 0;
	 ret = _ASN1_XER_Check_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_XER_BASIC_Data_Dec_ASN1CHARACTERSTRING(workspace,value,xer_flag,tab_value);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ASN1CHARACTERSTRING(value);
	 if(ret < 0) return ret;
	 return ret;
}


ASN1_CPPLINK int ASN1_SET_CHARACTERSTRING_SEQUENCE_identification(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASN1CHARACTERSTRING_identification* user_value)
{
	ASNINT32 ret;
	ret = ASN1_SET_ASN1CHARACTERSTRING_identification(workspace,value,user_value);
	return ret;
}

ASN1_CPPLINK int ASN1_SET_CHARACTERSTRING_SEQUENCE_string_value(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT8 *user_value,ASNUINT32 user_value_length)
{
	ASNINT32 ret;
	ret = ASN1_SET_ASN1CHARACTERSTRING_string_value(workspace,value,user_value,user_value_length);
	return ret;
}



ASN1_CPPLINK int ASN1_SET_CHARACTERSTRING_CHOICE_syntaxes(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,
											 ASNUINT32 *abstract_value,ASNUINT32 abstract_value_length,
											 ASNUINT32 *transfer_value,ASNUINT32 transfer_value_length)
{
	ASN1CHARACTERSTRING_identification_syntaxes ASN1CHARACTERSTRING_identification_syntaxes_value;
	ASNINT32 ret;
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));

	memset(&ASN1CHARACTERSTRING_identification_syntaxes_value,0,sizeof(ASN1CHARACTERSTRING_identification_syntaxes));

	ret = ASN1_SET_ASN1CHARACTERSTRING_identification_syntaxes_abstract(workspace,&ASN1CHARACTERSTRING_identification_syntaxes_value,abstract_value,abstract_value_length);
	ret = ASN1_SET_ASN1CHARACTERSTRING_identification_syntaxes_transfer(workspace,&ASN1CHARACTERSTRING_identification_syntaxes_value,transfer_value,transfer_value_length);
	ret = ASN1_SET_ASN1CHARACTERSTRING_identification_syntaxes(workspace,value->identification,&ASN1CHARACTERSTRING_identification_syntaxes_value);
	return ret;
}

ASN1_CPPLINK int ASN1_SET_CHARACTERSTRING_CHOICE_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT32 *user_value,ASNUINT32 user_value_length)
{
	ASNINT32 ret;
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));

	ret = ASN1_SET_ASN1CHARACTERSTRING_identification_syntax(workspace,value->identification,user_value,user_value_length);
	return ret;
}

ASN1_CPPLINK int ASN1_SET_CHARACTERSTRING_CHOICE_presentation_context_id(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,INTEGER user_value)
{
	ASNINT32 ret;
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));

	ret = ASN1_SET_ASN1CHARACTERSTRING_identification_presentation_context_id(workspace,value->identification,user_value);
	return ret;
}



ASN1_CPPLINK int ASN1_SET_CHARACTERSTRING_CHOICE_context_negotiation(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,
														INTEGER presentation_context_id_value,
														ASNUINT32 *transfer_syntax_value,ASNUINT32 transfer_syntax_value_length)
{
	ASN1CHARACTERSTRING_identification_context_negotiation ASN1CHARACTERSTRING_identification_context_negotiation_value;
	ASNINT32 ret;
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));

	memset(&ASN1CHARACTERSTRING_identification_context_negotiation_value,0,sizeof(ASN1CHARACTERSTRING_identification_context_negotiation));

	ret = ASN1_SET_ASN1CHARACTERSTRING_identification_context_negotiation_presentation_context_id(workspace,&ASN1CHARACTERSTRING_identification_context_negotiation_value,presentation_context_id_value);
	ret = ASN1_SET_ASN1CHARACTERSTRING_identification_context_negotiation_transfer_syntax(workspace,&ASN1CHARACTERSTRING_identification_context_negotiation_value,transfer_syntax_value,transfer_syntax_value_length);

	ret = ASN1_SET_ASN1CHARACTERSTRING_identification_context_negotiation(workspace,value->identification,&ASN1CHARACTERSTRING_identification_context_negotiation_value);
	return ret;
}

ASN1_CPPLINK int ASN1_SET_CHARACTERSTRING_CHOICE_transfer_syntax(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT32 *user_value,ASNUINT32 user_value_length)
{
	 ASNINT32 ret;
	 value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	 memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));
	 ret = ASN1_SET_ASN1CHARACTERSTRING_identification_transfer_syntax(workspace,value->identification,user_value,user_value_length);
	 return ret;
}

ASN1_CPPLINK int ASN1_SET_CHARACTERSTRING_CHOICE_fixed(ASN1WorkSpace* workspace,ASN1CHARACTERSTRING* value,ASNUINT8 user_value)
{
	ASNINT32 ret;
	value->identification = mpool_malloc(workspace->Pmemory,sizeof(ASN1CHARACTERSTRING_identification));
	memset(value->identification,0,sizeof(ASN1CHARACTERSTRING_identification));
	ret = ASN1_SET_ASN1CHARACTERSTRING_identification_fixed(workspace,value->identification,user_value);
	return ret;
}

ASN1_CPPLINK ASNINT32 ASN1_Print_CHARACTERSTRING(ASNUINT8* name,CHARACTERSTRING* PChstring,ASNINT32 ptab) //printf CHARACTER STRING struct
{
	unsigned int F_Ui_Chstr_Count = 0;
//	printf("CHARACTERSTRING:count = %u\t %s = ",PChstring->numbits,name);
	if (name == NULL || PChstring == NULL){
		return -74;
	}
	asn_printf("%s = ",name);
	ASN1_Print_ASN1CHARACTERSTRING(PChstring,ptab);
	return 0;
}
