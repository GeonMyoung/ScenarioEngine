#ifndef _ITSISO14827TESTEAM_H_
#define _ITSISO14827TESTEAM_H_

#include "BER/ASN1bersrc.h"
#include "IO/ASN1IO.h"
#include "MEM/mpool.h"
#include "OS/ASN1_Sys.h"
#include "TOOL/ASN1Tool.h"
#include "TYPE/ASN1_Type.h"



/********************************************************
*ItsIso14827TestTimeFormat                              *
********************************************************/
enum ItsIso14827TestTimeFormat{ 
	ItsIso14827TestTimeFormat_full = 0,
	ItsIso14827TestTimeFormat_hhmmss = 1,
	ItsIso14827TestTimeFormat_hhmm = 2,
};
	#ifndef STRUC_ItsIso14827TestTimeFormat
	#define STRUC_ItsIso14827TestTimeFormat
	typedef enum ItsIso14827TestTimeFormat ItsIso14827TestTimeFormat;
	#endif

ASN1_CPPLINK int ASN1_Print_ItsIso14827TestTimeFormat(ItsIso14827TestTimeFormat* value,int tab_value);

ASN1_CPPLINK int ASN1_BER_Enc_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, int length, ASN1TagType tagFlag);


/********************************************************
*ItsIso14827TestTimeRequest                             *
********************************************************/

	#ifndef STRUC_ItsIso14827TestTimeFormat
	#define STRUC_ItsIso14827TestTimeFormat
	typedef ENUMERATED ItsIso14827TestTimeFormat;
	#endif
struct ItsIso14827TestTimeRequest{
	ItsIso14827TestTimeFormat fmt;
}; 
	#ifndef STRUC_ItsIso14827TestTimeRequest
	#define STRUC_ItsIso14827TestTimeRequest
	typedef struct ItsIso14827TestTimeRequest ItsIso14827TestTimeRequest;
	#endif

ASN1_CPPLINK int ASN1_Print_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value,int tab_value);

ASN1_CPPLINK int ASN1_SET_ItsIso14827TestTimeRequest_fmt(ASN1WorkSpace* workspace,ItsIso14827TestTimeRequest* value,ENUMERATED user_value);

ASN1_CPPLINK int ASN1_GET_ItsIso14827TestTimeRequest_fmt(ASN1WorkSpace* workspace,ItsIso14827TestTimeRequest* value,ENUMERATED *user_value);

ASN1_CPPLINK int ASN1_BER_Enc_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, int length, ASN1TagType tagFlag);


/********************************************************
*ItsIso14827TestTimeResponse                            *
********************************************************/
struct ItsIso14827TestTimeResponse{
	UTF8Str str;
}; 
	#ifndef STRUC_ItsIso14827TestTimeResponse
	#define STRUC_ItsIso14827TestTimeResponse
	typedef struct ItsIso14827TestTimeResponse ItsIso14827TestTimeResponse;
	#endif

ASN1_CPPLINK int ASN1_Print_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value,int tab_value);

ASN1_CPPLINK int ASN1_SET_ItsIso14827TestTimeResponse_str(ASN1WorkSpace* workspace,ItsIso14827TestTimeResponse* value,ASNUINT8 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK int ASN1_GET_ItsIso14827TestTimeResponse_str(ASN1WorkSpace* workspace,ItsIso14827TestTimeResponse* value,ASNUINT8 **user_value,ASNUINT32 *user_value_length);

ASN1_CPPLINK int ASN1_BER_Enc_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, int length, ASN1TagType tagFlag);


/********************************************************
*SafetyC2PTraceCameraSpeedControl                       *
********************************************************/
struct SafetyC2PTraceCameraSpeedControl{
	UTF8Str sfcp_SystemID;
	UTF8Str sfcp_DeviceIndex;
enum{ 
	SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand_stop = 0,
	SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand_left = 1,
	SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand_right = 2,
	SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand_up = 3,
	SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand_down = 4,
	SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand_leftup = 5,
	SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand_leftdown = 6,
	SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand_rightup = 7,
	SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand_rightdown = 8,
}sfcp_PTCommand;

	INTEGER sfcp_PTSpeed;
enum{ 
	SafetyC2PTraceCameraSpeedControl_sfcp_ZoomCommand_stop = 0,
	SafetyC2PTraceCameraSpeedControl_sfcp_ZoomCommand_in = 1,
	SafetyC2PTraceCameraSpeedControl_sfcp_ZoomCommand_out = 2,
}sfcp_ZoomCommand;

	INTEGER sfcp_ZoomSpeed;
enum{ 
	SafetyC2PTraceCameraSpeedControl_sfcp_FocusCommand_stop = 0,
	SafetyC2PTraceCameraSpeedControl_sfcp_FocusCommand_near = 1,
	SafetyC2PTraceCameraSpeedControl_sfcp_FocusCommand_far = 2,
}sfcp_FocusCommand;

	INTEGER sfcp_FocusSpeed;
}; 
	#ifndef STRUC_SafetyC2PTraceCameraSpeedControl
	#define STRUC_SafetyC2PTraceCameraSpeedControl
	typedef struct SafetyC2PTraceCameraSpeedControl SafetyC2PTraceCameraSpeedControl;
	#endif

ASN1_CPPLINK int ASN1_Print_SafetyC2PTraceCameraSpeedControl(SafetyC2PTraceCameraSpeedControl* value,int tab_value);

ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_SystemID(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ASNUINT8 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_DeviceIndex(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ASNUINT8 *user_value,ASNUINT32 user_value_length);

ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED user_value);

ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_PTSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER user_value);

ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_ZoomCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED user_value);

ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_ZoomSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER user_value);

ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_FocusCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED user_value);

ASN1_CPPLINK int ASN1_SET_SafetyC2PTraceCameraSpeedControl_sfcp_FocusSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER user_value);

ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_SystemID(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ASNUINT8 **user_value,ASNUINT32 *user_value_length);

ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_DeviceIndex(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ASNUINT8 **user_value,ASNUINT32 *user_value_length);

ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_PTCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED *user_value);

ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_PTSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER *user_value);

ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_ZoomCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED *user_value);

ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_ZoomSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER *user_value);

ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_FocusCommand(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,ENUMERATED *user_value);

ASN1_CPPLINK int ASN1_GET_SafetyC2PTraceCameraSpeedControl_sfcp_FocusSpeed(ASN1WorkSpace* workspace,SafetyC2PTraceCameraSpeedControl* value,INTEGER *user_value);

ASN1_CPPLINK int ASN1_BER_Enc_SafetyC2PTraceCameraSpeedControl(ASN1WorkSpace* workspace, SafetyC2PTraceCameraSpeedControl* value, ASN1TagType tagFlag);

ASN1_CPPLINK int ASN1_BER_Dec_SafetyC2PTraceCameraSpeedControl(ASN1WorkSpace* workspace, SafetyC2PTraceCameraSpeedControl* value, int length, ASN1TagType tagFlag);


#endif
