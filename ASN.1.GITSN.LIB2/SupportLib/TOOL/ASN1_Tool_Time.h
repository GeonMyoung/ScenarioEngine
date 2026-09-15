
#ifndef _TIME_TOOL_
#define _TIME_TOOL_

#include "OS/ASN1_Sys.h"
#include "MEM/ASN1_mpool.h"
#include "TYPE/ASN1_Type.h"
#include "ASN1_CHECK_GeneralizedTime.h"
#include "ASN1_CHECK_UTCTime.h"


ASN1_CPPLINK ASNINT32 ASN1_Time_to_GTime(ASN1WorkSpace* ws,ASNUINT8* Str_time,
						   ASNUINT8* Add_time,ASNUINT8** Gtime);

ASN1_CPPLINK ASNINT32 ASN1_Time_to_UTCTime(ASN1WorkSpace* ws,ASNUINT8* Str_time,
							ASNUINT8* Add_time,ASNUINT8** UCTime);

ASN1_CPPLINK ASNINT32 Check_Time(ASNUINT8* Str_time,ASNUINT8* time_current,ASNINT32 flag);

ASN1_CPPLINK ASNINT32 Last_Process(ASNUINT8** time_current,ASNUINT8* Temp_time,
					  ASNINT32* time_array_number,ASNINT32* loop_flag);

ASN1_CPPLINK ASNINT32 Add_Process (ASNUINT8* time_current,ASNUINT8* Add_time);

ASN1_CPPLINK int _check_month_and_day(ASNUINT8 *GTime, ASNUINT8 leapyear);
ASN1_CPPLINK int _check_hmc(ASNUINT8 *GTime);
ASN1_CPPLINK int _check_sec(ASNUINT8 *GTime);

#endif /*_TIME_TOOL_*/

