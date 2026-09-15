#ifndef ITS_ISO_14827_TASK_SUPPORT_H
#define ITS_ISO_14827_TASK_SUPPORT_H

#include <dz1_task.h>
#include <ItsIso14827.h>

typedef struct ItsIso14827ServerTaskHandler
{
	Dz1TaskSigMsgProcFunc	auth;
	Dz1TaskSigMsgProcFunc	connected;
	Dz1TaskSigMsgProcFunc	disconnected;
	Dz1TaskSigMsgProcFunc	echo;
	Dz1TaskSigMsgProcFunc	single;
	Dz1TaskSigMsgProcFunc	ed_prepare;
	Dz1TaskSigMsgProcFunc	pr_prepare;
	Dz1TaskSigMsgProcFunc	pub_start;
	Dz1TaskSigMsgProcFunc	pub_invoke;
	Dz1TaskSigMsgProcFunc	pub_inform;
	Dz1TaskSigMsgProcFunc	pub_stopped;
	Dz1TaskSigMsgProcFunc	pub_expired;
	Dz1TaskSigMsgProcFunc	overload;
} ItsIso14827ServerTaskHandler;

DZ1_CPPLINK Dz1Error ItsIso14827_createServer4Task(u32_t task_queue_id, void *t14827,
												   Dz1Asn1UTF8Str *my_domain, u32_t max_clients,
												   ItsIso14827CodecOIDInfo user_oid_map_arr[],
												   size_t user_oid_map_arr_cnt);
DZ1_CPPLINK Dz1Error ItsIso14827_serverTaskMsgInit(void *task, ItsIso14827ServerTaskHandler *h);

typedef struct ItsIso14827ClientTaskHandler
{
	Dz1TaskSigMsgProcFunc	initiate;
	Dz1TaskSigMsgProcFunc	echo_responsed;
	Dz1TaskSigMsgProcFunc	terminate;
	Dz1TaskSigMsgProcFunc	publication;
	Dz1TaskSigMsgProcFunc	pub_control;
	Dz1TaskSigMsgProcFunc	disconnected;
} ItsIso14827ClientTaskHandler;

DZ1_CPPLINK Dz1Error ItsIso14827_createClient4Task(u32_t dst_queue_id, void *t14827, Dz1Asn1UTF8Str *myDomain);
DZ1_CPPLINK Dz1Error ItsIso14827_clientTaskMsgInit(void *task, ItsIso14827ClientTaskHandler *h);

DZ1_CPPLINK Dz1Error ItsIso14827_bothTaskMsgInit(void *task, ItsIso14827ServerTaskHandler *h_server, ItsIso14827ClientTaskHandler *h_client);

#endif