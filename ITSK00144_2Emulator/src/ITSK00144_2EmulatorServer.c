#include "ITSK00144_2EmulatorArg.h"
#include "ITSK00144_2EmulatorEnv.h"
#include "ITSK00144_2EmulatorMsg.h"
#include "ITSK00144_2EmulatorTimerUtil.h"

#include <ITSK00144_2Emulator.h>
#include <Dz1SockUtil.h>

#include <ITSK00144_2TestMsg.h>
#include <ITSK00144_2TestMsgSample.h>

#include <GitsnAsnUtil.h>

I2XTrafficSafetyDeviceLinkUnitStatus* sample_i2x_traffic_safety_device_link_unit_status;
I2XTrafficSafetyDeviceStatusInfo* sample_i2x_traffic_safety_device_status_info;
I2XTrafficSafetyDeviceList* sample_i2x_traffic_safety_device_list;
static I2XTrafficSafetyDeviceSerialNo id = { 0x4D, 0x00000011 };

MapData* sample_map;										// DSRCmsgID = 18
TravelerInformation* sample_tim;							// DSRCmsgID = 31

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



static Dz1TaskProcStatus _open(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	u16_t port = (u16_t)Dz1TaskSigMsg_getData(*sg);

	if (ITSK00144_2EmulatorServer_sockMsgInit(env->tSelf, errp) == FALSE) ERR_OUT(errp);
	else
	{
		if ((env->session = ITSK00144_2Session_new(ITSK00144_2SessionPresent_server, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ITSK00144_2ServerSession* s = NULL;
			pthread_cleanup_push(ITSK00144_2Session_delAndSetNull, (void*)&env->session);
			if ((env->session->x.server = s = ITSK00144_2ServerSession_new(-1, NULL, NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1SockAddr local;
				u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
				if (0) {}
				else if ((*errp = Dz1SockAddr_setAddrStr(&local, (str_t)"0.0.0.0")).code) ERR_OUT(errp);
				else if ((*errp = Dz1SockAddr_setPort(&local, port)).code) ERR_OUT(errp);
				else if ((s->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
				else if ((s->acceptor = Dz1SockUtilAcceptorForTask_start(0, s->local, my_queue_id, errp)) == (u32_t)-1) ERR_OUT(errp);
				else
				{
					u16_t port;
					Dz1SockAddr_getPort(s->local, &port);
					Dz1Thread_printf("SERVER : Port Opened(%d)...\n", port);
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(errp->code); // (ITSK00144_2Session_delAndSetNull, (void*)&env->session);
		}
		if (env->session == NULL || errp->code != 0)
		{
			// sock msg clear
			ITSK00144_2EmulatorServer_sockMsgClear(env->tSelf);
		}
	}
	return ret;
}

bool_t ITSK00144_2EmulatorServer_open(void* task, u16_t port, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00144_2_EMULATOR_SERVER_OPEN, (void*)&port, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}


static bool_t _send_data(ITSK001442EmulatorArg* arg, ITSK001442EmulatorEnv* env, void* timer, ITSK00144_2DataPresent opcode, Dz1Error* errp)
{
	ITSK00144_2ServerSession* session = NULL;
	if ((session = env->session->x.server) == NULL) ERR_SET_OUT(errp, ENOSYS);
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
			case ITSK00144_2DataPresent_req_link_unit_status:
			case ITSK00144_2DataPresent_req_status:
			case ITSK00144_2DataPresent_req_list:
			case ITSK00144_2DataPresent_reset:
				if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(&id, env->send_seq++, opcode, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case ITSK00144_2DataPresent_req_update_list:
				if ((data->x.req_update_list = I2XTrafficSafetyDeviceList_clone(sample_i2x_traffic_safety_device_list, errp)) == NULL) ERR_OUT(errp);
				else if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(&id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
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

	Dz1Str opcode = (Dz1Str)Dz1TaskSigMsg_getData(*sg);

	ITSK00144_2ServerSession* s = NULL;
	if ((s = env->session->x.server) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&opcode);
		if (0) {}
		else if (Dz1STRCMP(opcode, Dz1T("11")) == 0)
		{
			// 0x11
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_req_link_unit_status, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(opcode, Dz1T("13")) == 0)
		{
			// 0x13
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_req_status, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(opcode, Dz1T("15")) == 0)
		{
			// 0x15
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_req_list, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(opcode, Dz1T("17")) == 0)
		{
			// 0x17
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_req_update_list, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(opcode, Dz1T("81")) == 0)
		{
			// 0x81
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_reset, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else {
			Dz1Thread_printf("unknown opcode!\n");
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&opcode);
	}
	return ret;
}


bool_t ITSK00144_2EmulatorServer_send(void* task, Dz1Str opcode, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str op = NULL;

	if (0) {}
	else if ((op = Dz1Str_clone(opcode, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00144_2_EMULATOR_SERVER_SEND, (void*)&op, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t init_MessageFrame(MessageFrame* dst, int msg_id, Dz1Binary* value, Dz1Error* errp)
{

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	memset(dst, 0, sizeof(MessageFrame));
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	if (0) {}
	else if (ASN1_SET_MessageFrame_messageId(&ws, dst, msg_id) < 0) ERR_OUT(errp);
	else if (ASN1_SET_MessageFrame_value(&ws, dst, value->data, value->size) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	return ERR_IS_SUCCESS(errp);
}

static Dz1Binary* _uper_enc_messageframe(int msg_id, Dz1Binary* value, Dz1Error* errp)
{
	Dz1Binary* ret = NULL;

	if (value == NULL) ERR_OUT(errp);
	else
	{
		MessageFrame msg_frame;
		if (init_MessageFrame(&msg_frame, msg_id, value, errp) == FALSE) ERR_OUT(errp);
		else
		{
			ASN1_Print_MessageFrame(&msg_frame, 0);
			ASN1WorkSpace ws;
			ASN1_INIT_WS_INFO(&ws);
			pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
			if (ASN1_PER_UNAlign_Enc_MessageFrame(&ws, &msg_frame) < 0) ERR_SET_OUT(errp, EFAULT);
			else
			{
				if (errp->code == 0)
				{
					if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, Dz1Asn1Codec_uper), errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _send_dsrc(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	u16_t msg_id = (u16_t)Dz1TaskSigMsg_getData(*sg);

	ITSK00144_2ServerSession* s = NULL;
	if ((s = env->session->x.server) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1Binary* encoded = NULL;
		Dz1Binary* encoded_mf = NULL;
		switch (msg_id)
		{
		case 18:	// MAP
			if ((encoded = MapData_get_uper_encoded(sample_map, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(msg_id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 31:	// MAP
			if ((encoded = TravelerInformation_get_uper_encoded(sample_tim, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(msg_id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: break;
		}

		if (errp->code == 0 && encoded_mf != NULL)
		{
			Dz1Binary_dump(encoded_mf, 0);
			if (Dz1SockUtilTxFifo_send(s->tx_fifo, s->sock, encoded_mf->data, encoded_mf->size, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			if (encoded_mf != NULL)
				Dz1Binary_delAndSetNull((void*)&encoded_mf);
			if (encoded != NULL)
				Dz1Binary_delAndSetNull((void*)&encoded);
		}
	}

	return ret;
}

DZ1_CPPLINK bool_t ITSK00144_2EmulatorServer_dsrc(void* task, u16_t id, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00144_2_EMULATOR_SERVER_DSRC, (void*)&id, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static Dz1TaskProcStatus _clear(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;


	ITSK00144_2EmulatorServer_sockMsgClear(env->tSelf);

	env->received_seq = 0;
	env->send_seq = 0;

	if (env->session != NULL) ITSK00144_2Session_delAndSetNull((void*)&env->session);

	return ret;
}

bool_t ITSK00144_2EmulatorServer_clear(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ITSK00144_2_EMULATOR_SERVER_CLEAR, NULL, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2EmulatorServer_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_EMULATOR_SERVER_OPEN), _open)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_EMULATOR_SERVER_SEND), _send)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_EMULATOR_SERVER_CLEAR), _clear)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_EMULATOR_SERVER_DSRC), _send_dsrc)).code) ERR_OUT(errp);
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

		}
		else
		{
			ITSK00144_2ProtocolFrameContext* ctx = NULL;
			pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
			if ((ctx = ITSK00144_2ProtocolFrameContext_decode(f->context, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
			else if (_check_received_seq(env, ctx->seq, errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&ctx);

				Dz1Thread_printf("Received msg context = ]\n");
				ITSK00144_2ProtocolFrameContext_dump(ctx, 0);

				switch (ctx->opcode)
				{
				case ITSK00144_2DataPresent_hb:
					if (_send_data(arg, env, timer, ITSK00144_2DataPresent_ack, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				default: break;
				}
				pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&ctx);
			}
			pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
		}
	}
	return ERR_IS_SUCCESS(errp);
}



// SOCK MESSAGE
// DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED
static Dz1TaskProcStatus _server_connected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	Dz1SockUtilAcceptorConnected* msg = Dz1TaskSigMsg_getData(*sg);
	//ITSK001442ScenarioConfig* scenario = NULL;
	ITSK00144_2Session* session = NULL;
	ITSK00144_2ServerSession* server = NULL;

	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if ((session = env->session) == NULL) ERR_OUT(errp);
	else if ((server = session->x.server) == NULL) ERR_OUT(errp);
	else if ((server->peer = Dz1SockAddr_clone(msg->peer, errp)) == NULL) ERR_OUT(errp);
	else if ((server->sock = msg->sock) == NULL) ERR_OUT(errp);
	else if ((server->rx_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
	else if ((server->rx_stream = Dz1Stream_openRefElasticBuf(server->rx_buf, errp)) == NULL) ERR_OUT(errp);
	else if ((server->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1SockUtilTcpClient_modeCallback(server->sock, server->peer, server->local, 1024, my_queue_id)).code) ERR_OUT(errp);
	else
	{
		char str_addr[64] = { 0, };
		Dz1SockAddrA_printable(msg->peer, str_addr, FALSE, NULL);
		msg->sock = NULL;
		msg->local = msg->peer = NULL;
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Session established ] = \n"));
		ITSK00144_2ServerSession_dump(server, 0);

		bool_t is_complete = FALSE;




		Dz1Error_set(errp, 0);
	}

	return ret;
}

// DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION
static Dz1TaskProcStatus _server_connect_exception(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	if (env->session != NULL) ITSK00144_2Session_delAndSetNull((void*)&env->session);

	Dz1Thread_printf("!!! Server accept error!\n");

	return ret;
}

// DZ1_SOCK_UTIL_RECEIVER_RECEIVED
static Dz1TaskProcStatus _server_received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	ITSK00144_2Session* session = NULL;
	ITSK00144_2ServerSession* server = NULL;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("Received msg from SUT = \n"));
	Dz1SockUtilReceiverReceived_dump(msg, 0);
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("\n"));

	if ((session = env->session) == NULL) ERR_OUT(errp);
	else if ((server = session->x.server) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(server->peer, msg->peer) != 0 || Dz1SockAddr_cmp(server->local, msg->local) != 0) ERR_OUT(errp);
	else
	{
		Dz1Binary* stream = msg->stream;
		if (_Dz1ElasticBuf_push(server->rx_buf, stream->data, stream->size, errp) == FALSE) ERR_OUT(errp); // 소켓 버퍼에서 로컬 변수로 데이터 옮김
		else
		{
			Dz1Stream_drain(server->rx_stream, (size_t)stream->size, NULL, errp);

			if (_proc_payload(arg, env, timer, stream, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			Dz1Error_set(errp, 0);
		}
	}

	return ret;
}

// DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED
static Dz1TaskProcStatus _server_client_disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);
	Dz1Thread_printf("!!! Server Disconnected ] = \n");
	Dz1SockAddr_dump(msg->peer, 0);
	return ret;
}

// DZ1_SOCK_UTIL_TRANSMITER_SENT
static Dz1TaskProcStatus _server_sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442EmulatorArg* arg = (ITSK001442EmulatorArg*)uArg;
	ITSK001442EmulatorEnv* env = (ITSK001442EmulatorEnv*)uRsc;

	Dz1SockUtilTransmiterSent* msg = Dz1TaskSigMsg_getData(*sg);
	ITSK00144_2Session* session = NULL;
	ITSK00144_2ServerSession* server = NULL;

	if ((session = env->session) == NULL) ERR_OUT(errp);
	else if ((server = session->x.server) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, server->peer) != 0 || Dz1SockAddr_cmp(msg->local, server->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Dz1SockUtilTxFifo_sentProc(server->tx_fifo, server->sock, errp) == FALSE) ERR_OUT(errp);
		else
		{
			if (env->send_seq == 256) env->send_seq = 0;	// 0~255
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}




bool_t ITSK00144_2EmulatorServer_sockMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _server_connected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION), _server_connect_exception)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _server_received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _server_client_disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _server_sent)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

void ITSK00144_2EmulatorServer_sockMsgClear(void* task)
{
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _server_connected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION), _server_connect_exception);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _server_received);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _server_client_disconnected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _server_sent);
}