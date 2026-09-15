#include "ASN1_Tool_Time.h"

ASNINT8 Month_and_Day[13][2] = 
{
		0,29,
		1,31,
		2,28,
		3,31,
		4,30,
		5,31,
		6,30,
		7,31,
		8,31,
		9,30,
		10,31,
		11,30,
		12,31
};

ASN1_CPPLINK ASNINT32 ASN1_Time_to_GTime(ASN1WorkSpace* ws,ASNUINT8* Str_time,
						   ASNUINT8* Add_time,ASNUINT8** Gtime)
{
	ASNINT32 loop_flag = 1;
	ASNUINT8* time_value = Str_time;
	ASNUINT8* time_current;
	ASNUINT8 Temp_time[512];
	ASNINT32 time_array_number = 0;
	ASNINT32 Retime = 0;
	GeneralizedTime temp_GeneralizedTime;
	if (ws == NULL || Str_time == NULL || Add_time == NULL || Gtime == NULL){
		return -46;
	}

	*Gtime = (ASNUINT8*)mpool_malloc(ws->Pmemory,512*sizeof(ASNUINT8));
	time_current = *Gtime;
	memset(time_current,'\0',512);
	memset(Temp_time,'\0',512);

	while ('\0' != *time_value)
	{
		Temp_time[time_array_number] = *time_value;
		time_value++;
		time_array_number++;
		if ( ('/' == *time_value) || ( '\\'== *time_value))
		{
			switch(loop_flag)
			{
				case 1:
				Retime=Check_Time(Temp_time,time_current,1);/*Year*/
					if(!Retime)
						return -1;
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;

				case 2:
				Retime=Check_Time(Temp_time,time_current,2);/*Month*/
					if(!Retime)
						return -1;
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;
				
				case 3:
				Retime = Check_Time(Temp_time,time_current,3);/*Day*/
					if(!Retime)
						return -1;
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;

				case 4:
				Retime = Check_Time(Temp_time,time_current,4);/*Hour*/
					if(!Retime)
						return -1;
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;

				case 5:
				Retime = Check_Time(Temp_time,time_current,5);/*Minute*/
					if(!Retime)
						return -1;
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;
			}
			time_value++;
		}

	}
	if ('\0' != *Temp_time)
	{
		if (6 != loop_flag)
		{
			Retime = Check_Time(Temp_time,time_current,loop_flag);
			if(!Retime)
			return -1;
		}
		Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
	}
	if (Add_time == NULL)
	{
		*time_current = 'Z';
	}
	else
	{
		Add_Process(time_current,Add_time);
	}
	temp_GeneralizedTime.asnstring = *Gtime;
	temp_GeneralizedTime.nchar = (ASNINT32)strlen(*Gtime);
	if (0>ASN1_CHECK_GeneralizedTime(&temp_GeneralizedTime,NULL)){
		return -47;
	}
	
	return 0;
} 

ASN1_CPPLINK ASNINT32 ASN1_Time_to_UTCTime(ASN1WorkSpace* ws,ASNUINT8* Str_time,
							 ASNUINT8* Add_time,ASNUINT8** UCTime)
{
	ASNINT32 loop_flag = 1;
	ASNUINT8* time_value = Str_time;
	ASNUINT8* time_current;
	ASNUINT8 Temp_time[30];
	ASNINT32 time_array_number = 0;
	ASNINT32 Retime = 0;
	UTCTime temp_UTCTime;
	if (ws == NULL || Str_time == NULL || Add_time == NULL || UCTime == NULL){
		return -46;
	}

	*UCTime = (ASNUINT8*)mpool_malloc(ws->Pmemory,30*sizeof(ASNUINT8));
	time_current = *UCTime;
	memset(time_current,'\0',30);
	memset(Temp_time,'\0',30);
	
	while ('\0' != *time_value)
	{
		Temp_time[time_array_number] = *time_value;
		time_value++;
		time_array_number++;
		if ( ('/' == *time_value) || ( '\\'== *time_value))
		{
			switch(loop_flag)
			{
			case 1:
				Retime=Check_Time(Temp_time,time_current,1);/*Year*/
				if(!Retime)
					return -1;
				time_array_number = 2;
				Temp_time[0] = Temp_time[2];
				Temp_time[1] = Temp_time[3];
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;
				
			case 2:
				Retime=Check_Time(Temp_time,time_current,2);/*Month*/
				if(!Retime)
					return -1;
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;
				
			case 3:
				Retime = Check_Time(Temp_time,time_current,3);/*Day*/
				if(!Retime)
					return -1;
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;
				
			case 4:
				Retime = Check_Time(Temp_time,time_current,4);/*Hour*/
				if(!Retime)
					return -1;
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;
				
			case 5:
				Retime = Check_Time(Temp_time,time_current,5);/*Minute*/
				if(!Retime)
					return -1;
				Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
				break;

			}
			time_value++;
		}
		
	}
	if ('\0' != *Temp_time)
	{
		if (7 != loop_flag)
		{
			Retime = Check_Time(Temp_time,time_current,loop_flag);
			if(!Retime)
				return -1;
		}
		Last_Process(&time_current,Temp_time,&time_array_number,&loop_flag);
	}
	if (Add_time == NULL)
	{
		*time_current = 'Z';
	}
	else
	{
		Add_Process(time_current,Add_time);
	}
	temp_UTCTime.asnstring = *UCTime;
	temp_UTCTime.nchar = (ASNINT32)strlen(*UCTime);
	if (0>ASN1_CHECK_UTCTime(&temp_UTCTime,NULL)){
		return -48;
	}
	return 0;

}




ASN1_CPPLINK ASNINT32 Check_Time(ASNUINT8* Str_time,ASNUINT8* time_current,ASNINT32 flag)
{
	ASNINT32 time_length = (ASNINT32)strlen(Str_time);
    ASNINT32 time_value;

	if (1 == flag) /*Year*/
	{
		if (time_length<1 || time_length>4)
		return -1;
				
	}
	else if (2 == flag)/*Month*/
	{
		if (time_length<1 || time_length>2)
			return -1;
		time_value = atoi(Str_time);
		if (time_value<1 || time_value>12)
            return -2;
		if(time_length == 1)
		{
			*time_current = '0';
			time_current+=1;
		}

	}
	else if (3 == flag)/*Day*/
	{
		if (time_length<1 || time_length>2)
			return -1;
		time_value = atoi(Str_time);
		if(time_value<1 || time_value>32)
			return -2;
		if(time_length == 1)
		{
			*time_current = '0';
			time_current+=1;
		}
	}
	else if (4== flag)/*Hour*/
	{
		if (time_length<1 || time_length>2)
			return -1;
		time_value = atoi(Str_time);
		if(time_value<0 || time_value>23)
			return -2;
		if(time_length == 1)
		{
			*time_current = '0';
			time_current+=1;
		}
	}
	else if (5 == flag)/*Minute*/
	{
		if (time_length<1 || time_length>2)
			return -1;
		time_value = atoi(Str_time);
		if(time_value<0 || time_value>59)
			return -2;
		if(time_length == 1)
		{
			*time_current = '0';
			time_current+=1;
		}
	}

	else if (6 == flag)/*Second*/
	{
		if (time_length<1 || time_length>2)
			return -1;
		time_value = atoi(Str_time);
		if(time_value<0 || time_value>59)
			return -2;
		if(time_length == 1)
		{
			*time_current = '0';
			time_current+=1;
		}
	}
	return 1;
}

ASN1_CPPLINK ASNINT32 Last_Process(ASNUINT8** time_current,ASNUINT8* Temp_time,
					  ASNINT32* time_array_number,ASNINT32* loop_flag)
{
	memcpy(*time_current,Temp_time,*time_array_number);
	(*time_current) += (*time_array_number);
	(*loop_flag)++;
	memset(Temp_time,'\0',9);
	(*time_array_number) = 0;
	return 0;
}


ASN1_CPPLINK ASNINT32 Add_Process (ASNUINT8* time_current,ASNUINT8* Add_time)
{
	ASNUINT8 add_array[6];
	ASNINT32 retime;
	memset(add_array,'\0',6);
	if (*Add_time != '+'&&*Add_time != '-')
	{
		return -1;
	}

	memcpy(add_array,Add_time+1,2);
	retime=Check_Time(add_array,time_current,4);

	memcpy(add_array+2,Add_time+3,2);
	retime=Check_Time(add_array,time_current,5);
	if(!retime)
		return -1;

	memcpy(time_current,Add_time,5);
	return 0;
}

ASN1_CPPLINK int _check_month_and_day(ASNUINT8 *GTime, ASNUINT8 leapyear)
{
	ASNUINT8 ret = 0;
	ASNUINT8 i = 0;
	ASNUINT8 Month = 0;
	ASNUINT8 Day = 0;
	
	for (; i<4; i++)
	{
		if (GTime[i]<'0' || GTime[i]>'9') 
		{
			return -1;
		}
	}
	
	Month = (GTime[0] - 48) * 10 + (GTime[1] - 48);
	Day = (GTime[2] - 48) * 10 + (GTime[3] - 48);

	if (Month > 12 || Month < 1) 
	{
		return -1;
	}
	
	if (2 == Month && 1 == leapyear) 
	{
		Month = 0;
	}
	
	if ((Day > Month_and_Day[Month][1]) || (Day < 1)) 
	{
		return -1;
	}
	
	return 0;
}

ASN1_CPPLINK int _check_hmc(ASNUINT8 *GTime)
{
	ASNUINT8 Hour = 0;
	ASNUINT8 Minute = 0;
	ASNUINT8 i = 0;
		
	for (; i<4; i++)
	{
		if (GTime[i]<'0' || GTime[i]>'9') 
		{
			return -1;
		}
	}
	
	Hour = (GTime[0] - 48) * 10 + (GTime[1] - 48);
	Minute = (GTime[2] - 48) * 10 + (GTime[3] - 48);
	
	if (Hour < 24) 
	{
		if (Minute < 60) 
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	
	return 0;
}

ASN1_CPPLINK int _check_sec(ASNUINT8 *GTime)
{
	ASNUINT8 Second = 0;
	ASNUINT8 i = 0;

	for (; i<2; i++)
	{
		if (GTime[i]<'0' || GTime[i]>'9') 
		{
			return -1;
		}
	}

	Second = (GTime[0] - 48) * 10 + (GTime[1] - 48);

	return (Second < 60); 
}
