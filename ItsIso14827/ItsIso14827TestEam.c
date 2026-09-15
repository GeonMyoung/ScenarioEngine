#include "ItsIso14827TestEam.h"

ASN1_CPPLINK int ASN1_Print_ItsIso14827TestTimeFormat(ItsIso14827TestTimeFormat* value,int tab_value)
{
	int ret = 0;
		if(value == NULL){return -1;}
		ret = ASN_Print_TAB(tab_value+1); 
		if(ret < 0) return ret;
		switch(*value){

			case 0:
			ret = ASN1_Print_ENUMERATED("ItsIso14827TestTimeFormat","full",0);
			if(ret < 0) return ret;
			break;

			case 1:
			ret = ASN1_Print_ENUMERATED("ItsIso14827TestTimeFormat","hhmmss",1);
			if(ret < 0) return ret;
			break;

			case 2:
			ret = ASN1_Print_ENUMERATED("ItsIso14827TestTimeFormat","hhmm",2);
			if(ret < 0) return ret;
			break;
			default:
			ASN1_Enum_UNKNOWN(tab_value+1);
			break;
		};
	return ret;
}

ASN1_CPPLINK int ASN1_CHECK_ItsIso14827TestTimeFormat(ItsIso14827TestTimeFormat* value)
{
	unsigned char checkinfo_ItsIso14827TestTimeFormat[] = {0X03,0X00,0X01,0X02,0x00};
	int ret = 0;
		if(value == NULL){return -1;}
ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value,checkinfo_ItsIso14827TestTimeFormat);
	 if(ret < 0) return ret;
	return ret;
}

ASN1_CPPLINK int ASN1_BER_Data_Enc_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ret = ASN1_BER_Enc_ENUMERATED(workspace,(ASNINT32*)value,tagFlag);(workspace,value, tagFlag);
	if(ret < 0) return ret;

	return ret;
}

ASN1_CPPLINK int ASN1_BER_Enc_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ItsIso14827TestTimeFormat(value);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Enc_ItsIso14827TestTimeFormat(workspace,value,tagFlag);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_BER_Data_Dec_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len=length;
	ret = ASN1_BER_Dec_ENUMERATED(workspace,(ASNINT32*)value, len, tagFlag);
	if(ret < 0) return ret;

	return ret;
}

ASN1_CPPLINK int ASN1_BER_Dec_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, int length, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = _ASN1_BER_CHECK_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Dec_ItsIso14827TestTimeFormat(workspace,value,length,tagFlag);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ItsIso14827TestTimeFormat(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_Print_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value,int tab_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ASN1_Print_SEQ("ItsIso14827TestTimeRequest");
				ret = ASN_Print_TAB(tab_value+1); 
		if(ret < 0) return ret;
		switch(value->fmt){

			case 0:
			ret = ASN1_Print_ENUMERATED("fmt","full",0);
			if(ret < 0) return ret;
			break;

			case 1:
			ret = ASN1_Print_ENUMERATED("fmt","hhmmss",1);
			if(ret < 0) return ret;
			break;

			case 2:
			ret = ASN1_Print_ENUMERATED("fmt","hhmm",2);
			if(ret < 0) return ret;
			break;
			default:
			ASN1_Enum_UNKNOWN(tab_value+1);
			break;
		};

	ASN_Print_TAB(tab_value); printf("}\n");
	return ret;
}
		
ASN1_CPPLINK int ASN1_SET_ItsIso14827TestTimeRequest_fmt(ASN1WorkSpace* workspace,ItsIso14827TestTimeRequest* value,ENUMERATED user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_SET_ENUMERATED(workspace,(ASNINT32*)&value->fmt,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_ItsIso14827TestTimeRequest_fmt(ASN1WorkSpace* workspace,ItsIso14827TestTimeRequest* value,ENUMERATED *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_GET_ENUMERATED(workspace,(ASNINT32*)&value->fmt,user_value);

	return ret;
}


ASN1_CPPLINK int ASN1_CHECK_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value)
{
	int ret = 0;
	unsigned char checkinfo_fmt[] = {0x00,0x00};


	 if(value == NULL){return -1;}
		ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->fmt),checkinfo_fmt);
	 if(ret < 0) return ret;

	return ret;
}
ASN1_CPPLINK extern int ASN1_BER_Data_Enc_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Data_Enc_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;

	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16);

		if(ret < 0) return ret;
	}

		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0);
	if(ret < 0) return ret;

		ret = ASN1_BER_Data_Enc_ItsIso14827TestTimeFormat(workspace, &(value->fmt), ASN1IMPL);
	if(ret < 0) return ret;


	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_Enc_StrmEOC(workspace);

		if(ret < 0) return ret;
	}

	 return ret;
}
ASN1_CPPLINK extern int ASN1_CHECK_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value);
ASN1_CPPLINK extern int ASN1_BER_Data_Enc_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Enc_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ItsIso14827TestTimeRequest(value);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Enc_ItsIso14827TestTimeRequest(workspace,value,tagFlag);
	 if(ret < 0) return ret;
	 return ret;
}
ASN1_CPPLINK extern int ASN1_BER_Data_Dec_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value,int length,ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Data_Dec_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, int length, ASN1TagType tagFlag)
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

	ret = ASN1_BER_Data_Dec_ItsIso14827TestTimeFormat(workspace, &value->fmt, len, ASN1IMPL);
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
ASN1_CPPLINK extern int ASN1_CHECK_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value);
ASN1_CPPLINK extern int ASN1_BER_Data_Dec_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value,int length,ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, int length, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = _ASN1_BER_CHECK_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Dec_ItsIso14827TestTimeRequest(workspace,value,length,tagFlag);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ItsIso14827TestTimeRequest(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_Print_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value,int tab_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ASN1_Print_SEQ("ItsIso14827TestTimeResponse");
		ret = ASN_Print_TAB(tab_value + 1);
	if(ret < 0) return ret;
	ret = ASN1_Print_UTF8Str("str",&(value->str));
	if(ret < 0) return ret;


	ASN_Print_TAB(tab_value); printf("}\n");
	return ret;
}
		
ASN1_CPPLINK int ASN1_SET_ItsIso14827TestTimeResponse_str(ASN1WorkSpace* workspace,ItsIso14827TestTimeResponse* value,ASNUINT8 *user_value,ASNUINT32 user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_SET_UTF8Str(workspace,&value->str,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_ItsIso14827TestTimeResponse_str(ASN1WorkSpace* workspace,ItsIso14827TestTimeResponse* value,ASNUINT8 **user_value,ASNUINT32 *user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_GET_UTF8Str(workspace,&value->str,user_value,user_value_length);
	return ret;
}


ASN1_CPPLINK int ASN1_CHECK_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value)
{
	int ret = 0;
	unsigned char checkinfo_str[] = {0x00,0x00};


	 if(value == NULL){return -1;}
		ret = ASN1_CHECK_UTF8Str(&(value->str),checkinfo_str);
	 if(ret < 0) return ret;

	return ret;
}

ASN1_CPPLINK int ASN1_BER_Data_Enc_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;

	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16);

		if(ret < 0) return ret;
	}

		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0);
	if(ret < 0) return ret;

		ret = ASN1_BER_Enc_UTF8Str(workspace,&(value->str), ASN1IMPL);
	if(ret < 0) return ret;

	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_Enc_StrmEOC(workspace);

		if(ret < 0) return ret;
	}

	 return ret;
}
ASN1_CPPLINK extern int ASN1_CHECK_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value);
ASN1_CPPLINK extern int ASN1_BER_Data_Enc_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Enc_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = ASN1_CHECK_ItsIso14827TestTimeResponse(value);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Enc_ItsIso14827TestTimeResponse(workspace,value,tagFlag);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_BER_Data_Dec_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, int length, ASN1TagType tagFlag)
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

	ret = ASN1_BER_Dec_UTF8Str(workspace,&value->str, len, ASN1IMPL);
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
ASN1_CPPLINK extern int ASN1_CHECK_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value);
ASN1_CPPLINK extern int ASN1_BER_Data_Dec_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value,int length,ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, int length, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = _ASN1_BER_CHECK_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Dec_ItsIso14827TestTimeResponse(workspace,value,length,tagFlag);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_ItsIso14827TestTimeResponse(value);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_Print_SafetyC2PTraceCameraSpeedControl(SafetyC2PTraceCameraSpeedControl* value,int tab_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ASN1_Print_SEQ("SafetyC2PTraceCameraSpeedControl");
		ret = ASN_Print_TAB(tab_value + 1);
	if(ret < 0) return ret;
	ret = ASN1_Print_UTF8Str("sfcp-SystemID",&(value->sfcp_SystemID));
	if(ret < 0) return ret;


		ret = ASN_Print_TAB(tab_value + 1);
	if(ret < 0) return ret;
	ret = ASN1_Print_UTF8Str("sfcp-DeviceIndex",&(value->sfcp_DeviceIndex));
	if(ret < 0) return ret;


				ret = ASN_Print_TAB(tab_value+1); 
		if(ret < 0) return ret;
		switch(value->sfcp_PTCommand){

			case 0:
			ret = ASN1_Print_ENUMERATED("sfcp_PTCommand","stop",0);
			if(ret < 0) return ret;
			break;

			case 1:
			ret = ASN1_Print_ENUMERATED("sfcp_PTCommand","left",1);
			if(ret < 0) return ret;
			break;

			case 2:
			ret = ASN1_Print_ENUMERATED("sfcp_PTCommand","right",2);
			if(ret < 0) return ret;
			break;

			case 3:
			ret = ASN1_Print_ENUMERATED("sfcp_PTCommand","up",3);
			if(ret < 0) return ret;
			break;

			case 4:
			ret = ASN1_Print_ENUMERATED("sfcp_PTCommand","down",4);
			if(ret < 0) return ret;
			break;

			case 5:
			ret = ASN1_Print_ENUMERATED("sfcp_PTCommand","leftup",5);
			if(ret < 0) return ret;
			break;

			case 6:
			ret = ASN1_Print_ENUMERATED("sfcp_PTCommand","leftdown",6);
			if(ret < 0) return ret;
			break;

			case 7:
			ret = ASN1_Print_ENUMERATED("sfcp_PTCommand","rightup",7);
			if(ret < 0) return ret;
			break;

			case 8:
			ret = ASN1_Print_ENUMERATED("sfcp_PTCommand","rightdown",8);
			if(ret < 0) return ret;
			break;
			default:
			ASN1_Enum_UNKNOWN(tab_value+1);
			break;
		};

		ret = ASN_Print_TAB(tab_value + 1);
	if(ret < 0) return ret;
	ret = ASN1_Print_INTEGER("sfcp-PTSpeed",&(value->sfcp_PTSpeed));
	if(ret < 0) return ret;


				ret = ASN_Print_TAB(tab_value+1); 
		if(ret < 0) return ret;
		switch(value->sfcp_ZoomCommand){

			case 0:
			ret = ASN1_Print_ENUMERATED("sfcp_ZoomCommand","stop",0);
			if(ret < 0) return ret;
			break;

			case 1:
			ret = ASN1_Print_ENUMERATED("sfcp_ZoomCommand","in",1);
			if(ret < 0) return ret;
			break;

			case 2:
			ret = ASN1_Print_ENUMERATED("sfcp_ZoomCommand","out",2);
			if(ret < 0) return ret;
			break;
			default:
			ASN1_Enum_UNKNOWN(tab_value+1);
			break;
		};

		ret = ASN_Print_TAB(tab_value + 1);
	if(ret < 0) return ret;
	ret = ASN1_Print_INTEGER("sfcp-ZoomSpeed",&(value->sfcp_ZoomSpeed));
	if(ret < 0) return ret;


				ret = ASN_Print_TAB(tab_value+1); 
		if(ret < 0) return ret;
		switch(value->sfcp_FocusCommand){

			case 0:
			ret = ASN1_Print_ENUMERATED("sfcp_FocusCommand","stop",0);
			if(ret < 0) return ret;
			break;

			case 1:
			ret = ASN1_Print_ENUMERATED("sfcp_FocusCommand","near",1);
			if(ret < 0) return ret;
			break;

			case 2:
			ret = ASN1_Print_ENUMERATED("sfcp_FocusCommand","far",2);
			if(ret < 0) return ret;
			break;
			default:
			ASN1_Enum_UNKNOWN(tab_value+1);
			break;
		};

		ret = ASN_Print_TAB(tab_value + 1);
	if(ret < 0) return ret;
	ret = ASN1_Print_INTEGER("sfcp-FocusSpeed",&(value->sfcp_FocusSpeed));
	if(ret < 0) return ret;


	ASN_Print_TAB(tab_value); printf("}\n");
	return ret;
}
		
ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_SystemID(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ASNUINT8 *user_value,ASNUINT32 user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_SET_UTF8Str(workspace,&value->sfcp_SystemID,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_DeviceIndex(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ASNUINT8 *user_value,ASNUINT32 user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_SET_UTF8Str(workspace,&value->sfcp_DeviceIndex,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_SET_ENUMERATED(workspace,(ASNINT32*)&value->sfcp_PTCommand,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_PTSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_SET_INTEGER(workspace,&value->sfcp_PTSpeed,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_ZoomCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_SET_ENUMERATED(workspace,(ASNINT32*)&value->sfcp_ZoomCommand,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_ZoomSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_SET_INTEGER(workspace,&value->sfcp_ZoomSpeed,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_FocusCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_SET_ENUMERATED(workspace,(ASNINT32*)&value->sfcp_FocusCommand,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_FocusSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_SET_INTEGER(workspace,&value->sfcp_FocusSpeed,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_SystemID(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ASNUINT8 **user_value,ASNUINT32 *user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_GET_UTF8Str(workspace,&value->sfcp_SystemID,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_DeviceIndex(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ASNUINT8 **user_value,ASNUINT32 *user_value_length)
{
	int ret = 0;
	 if(value == NULL || user_value == NULL){return -1;}
	ret = ASN1_GET_UTF8Str(workspace,&value->sfcp_DeviceIndex,user_value,user_value_length);
	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_GET_ENUMERATED(workspace,(ASNINT32*)&value->sfcp_PTCommand,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_PTSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_GET_INTEGER(workspace,&value->sfcp_PTSpeed,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_ZoomCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_GET_ENUMERATED(workspace,(ASNINT32*)&value->sfcp_ZoomCommand,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_ZoomSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_GET_INTEGER(workspace,&value->sfcp_ZoomSpeed,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_FocusCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_GET_ENUMERATED(workspace,(ASNINT32*)&value->sfcp_FocusCommand,user_value);

	return ret;
}

		
ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_FocusSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER *user_value)
{
	int ret = 0;
	 if(value == NULL){return -1;}
	ret = ASN1_GET_INTEGER(workspace,&value->sfcp_FocusSpeed,user_value);

	return ret;
}


ASN1_CPPLINK int ASN1_CHECK_SafetyC2PTraceCameraSpeedControl(SafetyC2PTraceCameraSpeedControl* value)
{
	int ret = 0;
	unsigned char checkinfo_sfcp_SystemID[] = {0X02,0X01,0X0D,0x00};

	unsigned char checkinfo_sfcp_DeviceIndex[] = {0X02,0X01,0X08,0x00};

	unsigned char checkinfo_sfcp_PTCommand[] = {0X09,0X00,0X01,0X02,0X03,0X04,0X05,0X06,0X07,0X08,0x00};

	unsigned char checkinfo_sfcp_PTSpeed[] = {0X02,0X00,0X64,0x00};

	unsigned char checkinfo_sfcp_ZoomCommand[] = {0X03,0X00,0X01,0X02,0x00};

	unsigned char checkinfo_sfcp_ZoomSpeed[] = {0X02,0X00,0X64,0x00};

	unsigned char checkinfo_sfcp_FocusCommand[] = {0X03,0X00,0X01,0X02,0x00};

	unsigned char checkinfo_sfcp_FocusSpeed[] = {0X02,0X00,0X64,0x00};


	 if(value == NULL){return -1;}
		ret = ASN1_CHECK_UTF8Str(&(value->sfcp_SystemID),checkinfo_sfcp_SystemID);
	 if(ret < 0) return ret;

		ret = ASN1_CHECK_UTF8Str(&(value->sfcp_DeviceIndex),checkinfo_sfcp_DeviceIndex);
	 if(ret < 0) return ret;

		ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->sfcp_PTCommand),checkinfo_sfcp_PTCommand);
	 if(ret < 0) return ret;

		ret = ASN1_CHECK_INTEGER(&(value->sfcp_PTSpeed),checkinfo_sfcp_PTSpeed);
	 if(ret < 0) return ret;

		ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->sfcp_ZoomCommand),checkinfo_sfcp_ZoomCommand);
	 if(ret < 0) return ret;

		ret = ASN1_CHECK_INTEGER(&(value->sfcp_ZoomSpeed),checkinfo_sfcp_ZoomSpeed);
	 if(ret < 0) return ret;

		ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->sfcp_FocusCommand),checkinfo_sfcp_FocusCommand);
	 if(ret < 0) return ret;

		ret = ASN1_CHECK_INTEGER(&(value->sfcp_FocusSpeed),checkinfo_sfcp_FocusSpeed);
	 if(ret < 0) return ret;

	return ret;
}

ASN1_CPPLINK int ASN1_BER_Data_Enc_SafetyC2PTraceCameraSpeedControl(ASN1WorkSpace* workspace, SafetyC2PTraceCameraSpeedControl* value, ASN1TagType tagFlag)
{
	int ret = 0;

	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16);

		if(ret < 0) return ret;
	}

		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0);
	if(ret < 0) return ret;

		ret = ASN1_BER_Enc_UTF8Str(workspace,&(value->sfcp_SystemID), ASN1IMPL);
	if(ret < 0) return ret;
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1);
	if(ret < 0) return ret;

		ret = ASN1_BER_Enc_UTF8Str(workspace,&(value->sfcp_DeviceIndex), ASN1IMPL);
	if(ret < 0) return ret;
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2);
	if(ret < 0) return ret;

		ret = ASN1_BER_Enc_ENUMERATED(workspace,(ASNINT32*)&(value->sfcp_PTCommand),ASN1IMPL);(workspace,&(value->sfcp_PTCommand), ASN1IMPL);
	if(ret < 0) return ret;
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|3);
	if(ret < 0) return ret;

		ret = ASN1_BER_Enc_INTEGER(workspace,&(value->sfcp_PTSpeed), ASN1IMPL);
	if(ret < 0) return ret;
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|4);
	if(ret < 0) return ret;

		ret = ASN1_BER_Enc_ENUMERATED(workspace,(ASNINT32*)&(value->sfcp_ZoomCommand),ASN1IMPL);(workspace,&(value->sfcp_ZoomCommand), ASN1IMPL);
	if(ret < 0) return ret;
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|5);
	if(ret < 0) return ret;

		ret = ASN1_BER_Enc_INTEGER(workspace,&(value->sfcp_ZoomSpeed), ASN1IMPL);
	if(ret < 0) return ret;
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|6);
	if(ret < 0) return ret;

		ret = ASN1_BER_Enc_ENUMERATED(workspace,(ASNINT32*)&(value->sfcp_FocusCommand),ASN1IMPL);(workspace,&(value->sfcp_FocusCommand), ASN1IMPL);
	if(ret < 0) return ret;
		ret = ASN1_BER_Enc_Tag_Indef(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|7);
	if(ret < 0) return ret;

		ret = ASN1_BER_Enc_INTEGER(workspace,&(value->sfcp_FocusSpeed), ASN1IMPL);
	if(ret < 0) return ret;

	if (tagFlag == ASN1EXPL)
	{
		ret = ASN1_BER_Enc_StrmEOC(workspace);

		if(ret < 0) return ret;
	}

	 return ret;
}
ASN1_CPPLINK extern int ASN1_CHECK_SafetyC2PTraceCameraSpeedControl(SafetyC2PTraceCameraSpeedControl* value);
ASN1_CPPLINK extern int ASN1_BER_Data_Enc_SafetyC2PTraceCameraSpeedControl(ASN1WorkSpace* workspace, SafetyC2PTraceCameraSpeedControl* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Enc_SafetyC2PTraceCameraSpeedControl(ASN1WorkSpace* workspace, SafetyC2PTraceCameraSpeedControl* value, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = ASN1_CHECK_SafetyC2PTraceCameraSpeedControl(value);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Enc_SafetyC2PTraceCameraSpeedControl(workspace,value,tagFlag);
	 if(ret < 0) return ret;
	 return ret;
}

ASN1_CPPLINK int ASN1_BER_Data_Dec_SafetyC2PTraceCameraSpeedControl(ASN1WorkSpace* workspace, SafetyC2PTraceCameraSpeedControl* value, int length, ASN1TagType tagFlag)
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

	ret = ASN1_BER_Dec_UTF8Str(workspace,&value->sfcp_SystemID, len, ASN1IMPL);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_UTF8Str(workspace,&value->sfcp_DeviceIndex, len, ASN1IMPL);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_ENUMERATED(workspace,(ASNINT32*)&value->sfcp_PTCommand, len, ASN1IMPL);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|3);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_INTEGER(workspace,&value->sfcp_PTSpeed, len, ASN1IMPL);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|4);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_ENUMERATED(workspace,(ASNINT32*)&value->sfcp_ZoomCommand, len, ASN1IMPL);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|5);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_INTEGER(workspace,&value->sfcp_ZoomSpeed, len, ASN1IMPL);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|6);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_ENUMERATED(workspace,(ASNINT32*)&value->sfcp_FocusCommand, len, ASN1IMPL);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|7);
	if(ret < 0) return ret;

	ret = ASN1_BER_User_Dec_Length(workspace,&len);
	if(ret < 0) return ret;

	ret = ASN1_BER_Dec_INTEGER(workspace,&value->sfcp_FocusSpeed, len, ASN1IMPL);
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
ASN1_CPPLINK extern int ASN1_CHECK_SafetyC2PTraceCameraSpeedControl(SafetyC2PTraceCameraSpeedControl* value);
ASN1_CPPLINK extern int ASN1_BER_Data_Dec_SafetyC2PTraceCameraSpeedControl(ASN1WorkSpace* workspace, SafetyC2PTraceCameraSpeedControl* value,int length,ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_SafetyC2PTraceCameraSpeedControl(ASN1WorkSpace* workspace, SafetyC2PTraceCameraSpeedControl* value, int length, ASN1TagType tagFlag)
{
	 int ret = 0;
	 ret = _ASN1_BER_CHECK_Length(workspace);
	 if(ret < 0) return ret;
	 ret = ASN1_BER_Data_Dec_SafetyC2PTraceCameraSpeedControl(workspace,value,length,tagFlag);
	 if(ret < 0) return ret;
	 ret = ASN1_CHECK_SafetyC2PTraceCameraSpeedControl(value);
	 if(ret < 0) return ret;
	 return ret;
}

