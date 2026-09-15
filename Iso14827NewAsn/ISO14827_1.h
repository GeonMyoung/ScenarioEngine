#ifndef _ISO14827_1_H_
#define _ISO14827_1_H_

#include "BER/ASN1bersrc.h"
#include "PER/ASN1persrc.h"
#include "IO/ASN1IO.h"
#include "MEM/mpool.h"
#include "OS/ASN1_Sys.h"
#include "TOOL/ASN1Tool.h"
#include "TYPE/ASN1_Type.h"



/********************************************************
*ISO14827_MESSAGE_messageType                           *
********************************************************/
#ifndef STRUC_ISO14827_MESSAGE_messageType
#define STRUC_ISO14827_MESSAGE_messageType
enum ISO14827_MESSAGE_messageType {
	ISO14827_MESSAGE_messageType_publication = 0,
	ISO14827_MESSAGE_messageType_subscription = 1,
};
typedef enum ISO14827_MESSAGE_messageType ISO14827_MESSAGE_messageType;
#endif

ASN1_CPPLINK int ASN1_Print_ISO14827_MESSAGE_messageType(ISO14827_MESSAGE_messageType *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value);

/********************************************************
*ISO14827_MESSAGE_subscriptionType                      *
********************************************************/
#ifndef STRUC_ISO14827_MESSAGE_subscriptionType
#define STRUC_ISO14827_MESSAGE_subscriptionType
enum ISO14827_MESSAGE_subscriptionType {
	ISO14827_MESSAGE_subscriptionType_single = 0,
	ISO14827_MESSAGE_subscriptionType_event_driven = 1,
	ISO14827_MESSAGE_subscriptionType_single_or_event = 2,
	ISO14827_MESSAGE_subscriptionType_periodic = 3,
	ISO14827_MESSAGE_subscriptionType_single_or_periodic = 4,
	ISO14827_MESSAGE_subscriptionType_event_or_periodic = 5,
	ISO14827_MESSAGE_subscriptionType_single_event_periodic = 6,
};
typedef enum ISO14827_MESSAGE_subscriptionType ISO14827_MESSAGE_subscriptionType;
#endif

ASN1_CPPLINK int ASN1_Print_ISO14827_MESSAGE_subscriptionType(ISO14827_MESSAGE_subscriptionType *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value);

#endif
