#include "Itsk00126v1EmulatorArg.h"
#include "Itsk00126v1EmulatorEnv.h"
#include "Itsk00126v1EmulatorMsg.h"
#include "Itsk00126v1EmulatorTimer.h"

#include <Itsk00126v1Emulator.h>
#include <Dz1SockUtil.h>
#include <dz1_asn1.h>
#include <Itsk00126v1EmulatorDefJson.h>


static Dz1Str sample_iot_im_device_sttus_info = Dz1T("{\"command\":\"c2c_iot_im_device_sttus_info\",\"event_name\":\"c2c_iot_im_device_sttus_info\",\"event_type\":\"request\",\"data\":{\"local_center_id\":\"2-11110-0001\",\"iot_im_device_id_qty\":\"0001\",\"iot_im_device_sttus_info_list\":[{\"iot_im_device_id\":\"m-00000001\",\"iot_im_device_link_sttus_code\":\"001\"}],\"creat_dt\":\"20251208210000\"}}");
static Dz1Str sample_iot_device_list_response_info = Dz1T("{\"command\":\"message\",\"data\":{\"local_center_id\":\"2-11110-0001\",\"event_name\":\"c2c_iot_device_list_response_info\",\"event_type\":\"response\",\"iot_im_device_id_qty\":\"0001\",\"c2c_im_device_list\":[{\"iot_im_device_id\":\"M-00000001\",\"iot_device_id_qty\":\"0001\",\"iot_device_list\":[{\"iot_device_id\":\"A-00000001\"}]}]}}");
static Dz1Str sample_iot_device_sttus_info = Dz1T("{\"command\":\"c2c_iot_device_sttus_info\",\"data\":{\"local_center_id\":\"2-11110-0001\",\"iot_device_id_qty\":\"0001\",\"iot_device_sttus_info_list\":[{\"iot_device_id\":\"A-00000001\",\"iot_device_sttus_code\":\"001\",\"btry_sttus_code\":\"001\",\"link_sttus_code\":\"001\",\"data_trnsmis_cont\":59,\"iot_im_device_id\":\"m-00000001\"}]}}");
static Dz1Str sample_safety_signal_list_response_info = Dz1T("{\"command\":\"message\",\"data\":{\"local_center_id\":\"2-11110-0001\",\"event_name\":\"c2c_safety_signal_list_response_info\",\"event_type\":\"response\",\"iot_im_device_id_qty\":\"0001\",\"c2c_im_device_list\":[{\"iot_im_device_id\":\"m-00000001\",\"iot_device_id_qty\":\"0001\",\"c2c_iot_device_list\":[{\"iot_device_id\":\"a-00000001\",\"safety_signal_id_qty\":\"0001\",\"c2c_safety_signal_info_list\":[{\"safety_signal_id\":\"41135-200000301000-1010-135-01-4\",\"administ_zone_code\":\"41135\",\"road_code\":\"200000301000\",\"lc_lat\":37.399678,\"lc_lng\":127.106506,\"safety_signal_ty_code\":\"1010\",\"safety_signal_sttus_code\":\"001\"}]}]}]}}");

static Itsk00126v1ClientSession* _init_and_connect_server(Itsk00126V1EmulatorEnv* env, u16_t port, Dz1Error* errp)
{
	Itsk00126v1ClientSession* ret = NULL;

	if ((ret = Itsk00126v1ClientSession_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126v1ClientSession_delAndSetNull, (void*)&ret);
		char str_addr[64] = { 0, };
		struct timeval to = { 3 ,0 };
		u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
		Dz1SockAddr peer, local;
		if (0) {}
		else if ((*errp = Dz1SockAddr_setAddrStr(&peer, Dz1T("127.0.0.1"))).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&peer, port)).code) ERR_OUT(errp);
		else if ((ret->peer = Dz1SockAddr_clone(&peer, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setAddrStr(&local, (str_t)"0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(errp);
		else if ((ret->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->rx_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->rx_stream = Dz1Stream_openRefElasticBuf(ret->rx_buf, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
		else if ((ret->sock = Dz1TcpClientSocket_open(ret->peer, ret->local, &to, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1SockUtilTcpClient_modeCallback(ret->sock, ret->peer, ret->local, 1024, my_queue_id)).code) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf("connected to server\n");
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Itsk00126v1ClientSession_delAndSetNul, (void*)&ret);
	}
	return ret;
}

static Dz1TaskProcStatus _init(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1EmulatorArg* arg = (Itsk00126V1EmulatorArg*)uArg;
	Itsk00126V1EmulatorEnv* env = (Itsk00126V1EmulatorEnv*)uRsc;

	u16_t port = (u16_t)Dz1TaskSigMsg_getData(*sg);

	if (Itsk00126v1EmulatorClient_sockMsgInit(env->tSelf, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Itsk00126v1Session* s = NULL;
		if ((env->session = s = Itsk00126v1Session_new(Itsk00126v1SessionPresent_client, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Itsk00126v1Session_delAndSetNull, (void*)&s);
			if ((s->x.client = _init_and_connect_server(env, port, errp)) == NULL) ERR_OUT(errp);
			else if ((env->local_center_id = Dz1Str_clone(ITSK_00126_V1_LOCAL_CENTER_ID, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Itsk00126v1Session_delAndSetNull, (void*)&s);
		}
		if (s == NULL || errp->code != 0)
		{
			// sock msg clear
			Itsk00126v1EmulatorClient_sockMsgClear(env->tSelf);
		}
	}
	return ret;
}

bool_t Itsk00126v1EmulatorClient_init(void* task, u16_t port, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00126_V1_EMULATOR_CLIENT_INIT, (void**)&port, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _send_data(Itsk00126V1EmulatorEnv* env, u16_t msg_id, Dz1Error* errp)
{
	Itsk00126v1ClientSession* session = NULL;

	if ((session = env->session->x.client) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1Asn1UTF8Str* str_u8 = NULL;
		switch (msg_id)
		{
		case 1:
			if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(sample_iot_im_device_sttus_info, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 21:

			break;
		case 22:
			if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(sample_iot_device_list_response_info, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 3:
			if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(sample_iot_device_sttus_info, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 41:
			break;
		case 42:
			if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(sample_safety_signal_list_response_info, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EPERM);
			break;
		}

		if (errp->code == 0 && str_u8 != NULL)
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
			if (Dz1SockUtilTxFifo_send(session->tx_fifo, session->sock, str_u8->data, str_u8->size, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
		}
	}

	return ERR_IS_SUCCESS(errp);
}

static Dz1TaskProcStatus _send(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1EmulatorArg* arg = (Itsk00126V1EmulatorArg*)uArg;
	Itsk00126V1EmulatorEnv* env = (Itsk00126V1EmulatorEnv*)uRsc;

	u16_t msg_id = (u16_t)Dz1TaskSigMsg_getData(*sg);

	if (_send_data(env, msg_id, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}



bool_t Itsk00126v1EmulatorClient_send(void* task, u16_t msg_id, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00126_V1_EMULATOR_CLIENT_SEND, (void**)&msg_id, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}


static Dz1TaskProcStatus _clear(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1EmulatorArg* arg = (Itsk00126V1EmulatorArg*)uArg;
	Itsk00126V1EmulatorEnv* env = (Itsk00126V1EmulatorEnv*)uRsc;


	Itsk00126v1EmulatorClient_sockMsgClear(env->tSelf);

	if (env->session != NULL) Itsk00126v1Session_delAndSetNull((void*)&env->session);

	return ret;
}

bool_t Itsk00126v1EmulatorClient_clear(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00126_V1_EMULATOR_CLIENT_CLEAR, NULL, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}


static bool_t _proc_request(Itsk00126V1EmulatorArg* arg, Itsk00126V1EmulatorEnv* env, void* timer, Dz1Binary* _msg, Dz1Error* errp)
{
	
	Dz1Binary* msg = (Dz1Binary*)_msg;

	if (msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Json* json = NULL;
		if ((json = Dz1Json_new("UTF-8", env->spec, Dz1T("Itsk00126v1Request"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			int cnt = 0;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, msg->data, msg->size, errp)) < 0) ERR_OUT(errp);
			else if (sz != msg->size) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
			else if (cnt == 0) Dz1Error_set(errp, 0);
			else
			{
				Itsk00126v1Request* req = NULL;
				if ((req = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else
				{

					Itsk00126v1RequestData* data = NULL;
					pthread_cleanup_push(Itsk00126v1Request_delAndSetNull, (void*)&req);
					Itsk00126v1Request_dump(req, 4);
					if ((data = req->data) == NULL) ERR_OUT(errp);
					else
					{
						if (0) {}
						else if (Dz1STRCMP(data->event_name, Dz1T("c2c_iot_device_list_request_info")) == 0)
						{
							if (_send_data(env, 22, errp) == FALSE) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						else if (Dz1STRCMP(data->event_name, Dz1T("c2c_safety_signal_list_request_info")) == 0)
						{
							if (_send_data(env, 42, errp) == FALSE) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						else Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Itsk00126v1Request_delAndSetNull, (void*)&req);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static Dz1TaskProcStatus _received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1EmulatorArg* arg = (Itsk00126V1EmulatorArg*)uArg;
	Itsk00126V1EmulatorEnv* env = (Itsk00126V1EmulatorEnv*)uRsc;

	Itsk00126v1ClientSession* session = NULL;
	Dz1SockUtilReceiverReceived* msg = Dz1TaskSigMsg_getData(*sg);

	if ((session = env->session->x.client) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, session->peer) != 0 || Dz1SockAddr_cmp(msg->local, session->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Binary* stream = msg->stream;
		if (_Dz1ElasticBuf_push(session->rx_buf, stream->data, stream->size, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf("$$$ Received Message From Server = \n");
			Dz1Binary_dump(stream, 0);





			//Itsk00126V1_Payload* payload = NULL;
			//if ((payload = Prj22ProtoBufUtil_deserialize_Itsk00126V1_Payload(stream)) == NULL) ERR_SET_OUT(errp, EFAULT);
			//else
			////{
				//Itsk00126V1_Payload_dump(payload, 0);
			Dz1Stream_drain(session->rx_stream, (size_t)stream->size, NULL, NULL);

			if (_proc_request(arg, env, timer, stream, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			//}
		}
	}
	return ret;
}

static Dz1TaskProcStatus _sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1EmulatorArg* arg = (Itsk00126V1EmulatorArg*)uArg;
	Itsk00126V1EmulatorEnv* env = (Itsk00126V1EmulatorEnv*)uRsc;

	Dz1SockUtilTransmiterSent* msg = Dz1TaskSigMsg_getData(*sg);
	Itsk00126v1ClientSession* session = NULL;

	if ((session = env->session->x.client) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, session->peer) != 0 || Dz1SockAddr_cmp(msg->local, session->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Dz1SockUtilTxFifo_sentProc(session->tx_fifo, session->sock, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	return ret;
}

static Dz1TaskProcStatus _disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1EmulatorArg* arg = (Itsk00126V1EmulatorArg*)uArg;
	Itsk00126V1EmulatorEnv* env = (Itsk00126V1EmulatorEnv*)uRsc;
	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);
	Dz1Thread_printf("!!! Disconnected ] = \n");
	Dz1SockAddr_dump(msg->peer, 0);

	return ret;
}




static Dz1TaskProcStatus _json(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1EmulatorArg* arg = (Itsk00126V1EmulatorArg*)uArg;
	Itsk00126V1EmulatorEnv* env = (Itsk00126V1EmulatorEnv*)uRsc;

	Dz1Asn1UTF8Str* str_u8 = NULL;
	if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(sample_iot_im_device_sttus_info, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
		Dz1Asn1UTF8Str_dump(str_u8, 4);
		Dz1Json* json = NULL;
		int cnt = 0;
		if ((json = Dz1Json_new("UTF-8", env->spec, Dz1T("C2CIoTImDeviceSttusInfo"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, str_u8->data, str_u8->size, errp)) < 0) ERR_OUT(errp);
			else if (sz != str_u8->size) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
			else if (cnt == 0) Dz1Error_set(errp, 0);
			else
			{
				C2CIoTImDeviceSttusInfo* deser = NULL;
				if ((deser = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					C2CIoTImDeviceSttusInfo_dump(deser, 0);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);

		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
	}

	if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(sample_iot_device_list_response_info, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
		Dz1Asn1UTF8Str_dump(str_u8, 4);
		Dz1Json* json = NULL;
		int cnt = 0;
		if ((json = Dz1Json_new("UTF-8", env->spec, Dz1T("C2CIoTDeviceListResponseInfo"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, str_u8->data, str_u8->size, errp)) < 0) ERR_OUT(errp);
			else if (sz != str_u8->size) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
			else if (cnt == 0) Dz1Error_set(errp, 0);
			else
			{
				C2CIoTDeviceListResponseInfo* deser = NULL;
				if ((deser = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					C2CIoTDeviceListResponseInfo_dump(deser, 0);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);

		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
	}

	if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(sample_iot_device_sttus_info, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
		Dz1Asn1UTF8Str_dump(str_u8, 4);
		Dz1Json* json = NULL;
		int cnt = 0;
		if ((json = Dz1Json_new("UTF-8", env->spec, Dz1T("C2CIoTDeviceSttusInfo"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, str_u8->data, str_u8->size, errp)) < 0) ERR_OUT(errp);
			else if (sz != str_u8->size) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
			else if (cnt == 0) Dz1Error_set(errp, 0);
			else
			{
				C2CIoTDeviceSttusInfo* deser = NULL;
				if ((deser = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					C2CIoTDeviceSttusInfo_dump(deser, 0);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);

		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
	}

	if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(sample_safety_signal_list_response_info, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
		Dz1Asn1UTF8Str_dump(str_u8, 4);
		Dz1Json* json = NULL;
		int cnt = 0;
		if ((json = Dz1Json_new("UTF-8", env->spec, Dz1T("C2CSafetySignalListResponseInfo"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, str_u8->data, str_u8->size, errp)) < 0) ERR_OUT(errp);
			else if (sz != str_u8->size) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
			else if (cnt == 0) Dz1Error_set(errp, 0);
			else
			{
				C2CSafetySignalListResponseInfo* deser = NULL;
				if ((deser = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					C2CSafetySignalListResponseInfo_dump(deser, 0);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);

		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
	}

	return ret;
}


bool_t Itsk00126v1EmulatorClient_json(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00126_V1_EMULATOR_CLIENT_JSON, NULL, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}


bool_t Itsk00126v1EmulatorClient_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V1_EMULATOR_CLIENT_INIT), _init)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V1_EMULATOR_CLIENT_SEND), _send)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V1_EMULATOR_CLIENT_CLEAR), _clear)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V1_EMULATOR_CLIENT_JSON), _json)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

bool_t Itsk00126v1EmulatorClient_sockMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _sent)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

void Itsk00126v1EmulatorClient_sockMsgClear(void* task)
{
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _received);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _disconnected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _sent);
}














