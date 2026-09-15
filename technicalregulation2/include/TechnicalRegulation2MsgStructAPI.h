#ifndef TECHNICAL_REGULATION2_MSG_STRUCT_API_H
#define TECHNICAL_REGULATION2_MSG_STRUCT_API_H

#include <Iso14827TestMsgUtil.h>
#include <TechnicalRegulation2EAM.h>
#include <TechnicalRegulation2EAMDz1.h>
#include "TechnicalRegulation2Def.h"
#include "TechnicalRegulation2DefJson.h"
#include <TechnicalRegulation2Util.h>

DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI TechnicalRegulation2MsgSet[];
DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI TechnicalRegulation2MsgTx[];
DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI TechnicalRegulation2MsgRx[];


DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI TechnicalRegulation2MsgTx_itsk[];
DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI TechnicalRegulation2MsgRx_itsk[];

#endif // TECHNICAL_REGULATION2_MSG_STRUCT_API_H
