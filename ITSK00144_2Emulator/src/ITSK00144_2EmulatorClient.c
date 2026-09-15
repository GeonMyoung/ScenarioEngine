#include "ITSK00144_2EmulatorArg.h"
#include "ITSK00144_2EmulatorEnv.h"
#include "ITSK00144_2EmulatorMsg.h"
#include "ITSK00144_2EmulatorTimerUtil.h"

#include <ITSK00144_2Emulator.h>
#include <Dz1SockUtil.h>

#include <ITSK00144_2TestMsg.h>
#include <ITSK00144_2TestMsgSample.h>



I2XTrafficSafetyDeviceLinkUnitStatus* sample_i2x_traffic_safety_device_link_unit_status;
I2XTrafficSafetyDeviceStatusInfo* sample_i2x_traffic_safety_device_status_info;
I2XTrafficSafetyDeviceList* sample_i2x_traffic_safety_device_list;

static I2XTrafficSafetyDeviceSerialNo id = { 0x4D, 0x00000011 };

static bool_t _keepalive_timer_set(ITSK001442EmulatorEnv* env, void* timer, Dz1Error* errp);

static Dz1TaskProcStatus _send_hb(void* uArg, void* uRsc, void* timer, void** tData, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	ITSK00144_2ClientSession* session = NULL;
	if ((session = env->session->x.client) == NULL) ERR_OUT(errp);
	else
	{
		ITSK00144_2ProtocolFrame* f = NULL;

		if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(&id, env->send_seq++, ITSK00144_2DataPresent_hb, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary* src = NULL;
			pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
			if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
				if (Dz1SockUtilTxFifo_send(session->tx_fifo, session->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
				else if (_keepalive_timer_set(env, timer, errp) == FALSE) ERR_OUT(errp);
				else
				{
					Dz1Thread_printf("$$$ Heartbeat send!\n");
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&src);
			}
			pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);

		}
	}
	return ret;
}

static bool_t _keepalive_timer_set(ITSK001442EmulatorEnv* env, void* timer, Dz1Error* errp)
{
	ITSK001442EmulatorTimer* tmr = ITSK001442EmulatorTimer_new(ITSK_00144_2_TIMER_KEEPALIVE, errp);
	if (tmr == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK001442EmulatorTimer_delAndSetNull, (void*)&tmr);
		if ((*errp = ITSK001442EmulatorTimer_set(timer, &tmr, 5 * 1000000, _send_hb)).code)
		{
			ERR_OUT(errp);
		}
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (ITSK001442EmulatorTimer_delAndSetNull, (void*)&tmr);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _check_received_seq(ITSK001442EmulatorEnv* env, u8_t received_seq, Dz1Error* errp)
{
	// 0 ~ 255 까지

	if (env->received_seq == 0 || env->received_seq == received_seq)
	{
		Dz1Error_set(errp, 0);
	}
	else if (env->received_seq + 1 == received_seq)
	{
		env->received_seq = received_seq;
		if (env->received_seq = 255) env->received_seq = 0;
		Dz1Error_set(errp, 0);
	}
	else
	{
		Dz1Thread_printf("!!! unexpected seq = %u\n", received_seq);
		ERR_SET_OUT(errp, EFAULT);
	}

	return ERR_IS_SUCCESS(errp);
}


static ITSK00144_2ClientSession* _init_and_connect_server(ITSK001442EmulatorEnv* env, u16_t port, Dz1Error* errp)
{
	ITSK00144_2ClientSession* ret = NULL;

	if ((ret = ITSK00144_2ClientSession_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK00144_2ClientSession_delAndSetNull, (void*)&ret);
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
		pthread_cleanup_pop(errp->code); // (ITSK00144_2ClientSession_delAndSetNul, (void*)&ret);
	}
	return ret;
}

static Dz1TaskProcStatus _init(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	u16_t port = (u16_t)Dz1TaskSigMsg_getData(*sg);

	if (ITSK00144_2EmulatorClient_sockMsgInit(env->tSelf, errp) == FALSE) ERR_OUT(errp);
	else
	{
		ITSK00144_2Session* s = NULL;
		if ((env->session = s = ITSK00144_2Session_new(ITSK00144_2SessionPresent_client, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ITSK00144_2Session_delAndSetNull, (void*)&s);
			if ((s->x.client = _init_and_connect_server(env, port, errp)) == NULL) ERR_OUT(errp);
			else
			{
				env->send_seq = 0;
				env->received_seq = 0;
				if (_keepalive_timer_set(env, timer, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (ITSK00144_2Session_delAndSetNull, (void*)&s);
		}
		if (s == NULL || errp->code != 0)
		{
			// sock msg clear
			ITSK00144_2EmulatorClient_sockMsgClear(env->tSelf);
		}
	}
	return ret;
}

bool_t ITSK00144_2EmulatorClient_init(void* task, u16_t port, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00144_2_EMULATOR_CLIENT_INIT, (void*)&port, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}


static bool_t _send_data(ITSK001442EmulatorArg* arg, ITSK001442EmulatorEnv* env, void* timer, ITSK00144_2DataPresent opcode, Dz1Error* errp)
{
	ITSK00144_2ClientSession* session = NULL;
	if ((session = env->session->x.client) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		ITSK00144_2ProtocolFrame* f = NULL;
		ITSK00144_2Data* data = NULL;
		if ((data = ITSK00144_2Data_new(opcode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ITSK00144_2Data_delAndSetNull, (void*)&data);
			switch (opcode)
			{
			case ITSK00144_2DataPresent_rsp_link_unit_status:
				if ((data->x.rsp_link_unit_status = I2XTrafficSafetyDeviceLinkUnitStatus_clone(sample_i2x_traffic_safety_device_link_unit_status, errp)) == NULL) ERR_OUT(errp);
				else if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(&id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case ITSK00144_2DataPresent_rsp_status:
				if ((data->x.rsp_status = I2XTrafficSafetyDeviceStatusInfo_clone(sample_i2x_traffic_safety_device_status_info, errp)) == NULL) ERR_OUT(errp);
				else if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(&id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case ITSK00144_2DataPresent_rsp_list:
				if ((data->x.rsp_list = I2XTrafficSafetyDeviceList_clone(sample_i2x_traffic_safety_device_list, errp)) == NULL) ERR_OUT(errp);
				else if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(&id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case ITSK00144_2DataPresent_rsp_update_list:
				if ((data->x.rsp_update_list = I2XTrafficSafetyDeviceList_clone(sample_i2x_traffic_safety_device_list, errp)) == NULL) ERR_OUT(errp);
				else if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(&id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case ITSK00144_2DataPresent_ack:
				if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(&id, env->send_seq++, opcode, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			default: ERR_SET_OUT(errp, EPERM);
				break;
			}
			if (f == NULL || errp->code != 0) ERR_OUT(errp);
			else
			{
				Dz1Binary* src = NULL;
				pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
				if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);

					Dz1Thread_printf("Send Message = \n");
					Dz1Binary_dump(src, 4);

					if (Dz1SockUtilTxFifo_send(session->tx_fifo, session->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&src);
				}
				pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
			}
			pthread_cleanup_pop(1); // (ITSK00144_2Data_delAndSetNull, (void*)&data);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static Dz1TaskProcStatus _send(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;


	return ret;
}

static Dz1TaskProcStatus _clear(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;


	ITSK00144_2EmulatorClient_sockMsgClear(env->tSelf);

	env->received_seq = 0;
	env->send_seq = 0;

	if (env->session != NULL) ITSK00144_2Session_delAndSetNull((void*)&env->session);

	return ret;
}

bool_t ITSK00144_2EmulatorClient_clear(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00144_2_EMULATOR_CLIENT_CLEAR, NULL, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}



static bool_t _proc_payload(ITSK001442EmulatorArg* arg, ITSK001442EmulatorEnv* env, void* timer, Dz1Binary* msg, Dz1Error* errp)
{
	if (msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ITSK00144_2ProtocolFrame* f = NULL;
		if ((f = ITSK00144_2ProtocolFrame_decode(msg, errp)) == NULL)
		{
			// v2x msg 전송확인
			// message frame decode 

			ERR_OUT(errp);
		}
		else
		{
			ITSK00144_2ProtocolFrameContext* ctx = NULL;
			pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
			if ((ctx = ITSK00144_2ProtocolFrameContext_decode(f->context, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
			else if (_check_received_seq(env, ctx->seq, errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Dz1Thread_printf("Received msg = ]\n");
				ITSK00144_2ProtocolFrameContext_dump(ctx, 0);

				pthread_cleanup_push(ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&ctx);
				switch (ctx->opcode)
				{
				case ITSK00144_2DataPresent_req_link_unit_status:
					if (_send_data(arg, env, timer, ITSK00144_2DataPresent_rsp_link_unit_status, errp) == FALSE);
					else Dz1Error_set(errp, 0);
					break;
				case ITSK00144_2DataPresent_req_status:
					if (_send_data(arg, env, timer, ITSK00144_2DataPresent_rsp_status, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				case ITSK00144_2DataPresent_req_list:
					if (_send_data(arg, env, timer, ITSK00144_2DataPresent_rsp_list, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				case ITSK00144_2DataPresent_req_update_list:
					if (_send_data(arg, env, timer, ITSK00144_2DataPresent_rsp_update_list, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				case ITSK00144_2DataPresent_reset:
					if (_send_data(arg, env, timer, ITSK00144_2DataPresent_ack, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				}
				pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&ctx);
			}


			pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
		}

	}
	return ERR_IS_SUCCESS(errp);
}

static Dz1TaskProcStatus _received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	ITSK00144_2ClientSession* session = NULL;
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





			//ITSK001442_Payload* payload = NULL;
			//if ((payload = Prj22ProtoBufUtil_deserialize_ITSK001442_Payload(stream)) == NULL) ERR_SET_OUT(errp, EFAULT);
			//else
			////{
				//ITSK001442_Payload_dump(payload, 0);
			Dz1Stream_drain(session->rx_stream, (size_t)stream->size, NULL, NULL);

			if (_proc_payload(arg, env, timer, stream, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			//}
		}
	}
	return ret;
}

static Dz1TaskProcStatus _sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	Dz1SockUtilTransmiterSent* msg = Dz1TaskSigMsg_getData(*sg);
	ITSK00144_2ClientSession* session = NULL;

	if ((session = env->session->x.client) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, session->peer) != 0 || Dz1SockAddr_cmp(msg->local, session->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Dz1SockUtilTxFifo_sentProc(session->tx_fifo, session->sock, errp) == FALSE) ERR_OUT(errp);
		else
		{
			if (env->send_seq == 256) env->send_seq = 0;	// 0~255
			Dz1Error_set(errp, 0);
		}
	}

	return ret;
}

static Dz1TaskProcStatus _disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;
	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);
	Dz1Thread_printf("!!! Disconnected ] = \n");
	Dz1SockAddr_dump(msg->peer, 0);

	return ret;
}


bool_t ITSK00144_2EmulatorClient_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_EMULATOR_CLIENT_INIT), _init)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_EMULATOR_CLIENT_SEND), _send)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_EMULATOR_CLIENT_CLEAR), _clear)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2EmulatorClient_sockMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _sent)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

void ITSK00144_2EmulatorClient_sockMsgClear(void* task)
{
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _received);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _disconnected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _sent);
}