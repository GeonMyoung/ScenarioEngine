#include "GitsnDsrcEmulatorArg.h"
#include "GitsnDsrcEmulatorEnv.h"
#include "GitsnDsrcEmulatorMsg.h"

#include <GitsnDsrcEmulator.h>

#include <Dz1SockUtil.h>

#include <GitsnTestDataProtocol.h>
#include <GitsnAsnUtilSampleMsg.h>



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

static Dz1TaskProcStatus _init(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	GitsnDsrcEmulatorArg* arg = (GitsnDsrcEmulatorArg*)uArg;
	GitsnDsrcEmulatorEnv* env = (GitsnDsrcEmulatorEnv*)uRsc;

	GitsnDsrcEmulatorSession* session = NULL;
	GitsnDsrcEmulatorClientSession* s = NULL;

	u16_t port = (u16_t)Dz1TaskSigMsg_getData(*sg);


	if ((session = env->session) != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((session = env->session = GitsnDsrcEmulatorSession_new(GitsnDsrcEmulatorSessionPresent_client, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((s = session->x.client = GitsnDsrcEmulatorClientSession_new(NULL, NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockAddr peer, local;
		u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
		if (0) {}
		// peer
		else if ((*errp = Dz1SockAddr_setAddrStr(&peer, Dz1T("127.0.0.1"))).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&peer, port)).code) ERR_OUT(errp);
		else if ((s->peer = Dz1SockAddr_clone(&peer, errp)) == NULL) ERR_OUT(errp);
		// local
		else if ((*errp = Dz1SockAddr_setAddrStr(&local, (str_t)"0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(errp);
		else if ((s->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
		else if ((s->rx_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((s->rx_stream = Dz1Stream_openRefElasticBuf(s->rx_buf, errp)) == NULL) ERR_OUT(errp);
		else if ((s->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			char str_addr[64] = { 0, };
			struct timeval to = { 3, 0 };
			if ((s->sock = Dz1TcpClientSocket_open(s->peer, s->local, &to, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = Dz1SockUtilTcpClient_modeCallback(s->sock, s->peer, s->local, 1024, my_queue_id)).code) ERR_OUT(errp);
			else
			{
				Dz1Thread_printf("Connected to server!\n");
				Dz1Error_set(errp, 0);
			}
		}
	}
	return ret;
}


bool_t GitsnDsrcEmulatorTest_init(void* task, u16_t port, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (task == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, GITSN_DSRC_EMULATOR_TEST_INIT, (void**)&port, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}



static bool_t _convert_and_send(GitsnDsrcEmulatorEnv* env, GitsnTestDataFrames* dfs, Dz1Error* errp)
{
	GitsnDsrcEmulatorSession* session = NULL;
	GitsnDsrcEmulatorServerSession* s = NULL;
	GitsnDsrcEmulatorClientSession* c = NULL;


	if ((session = env->session) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1Binary* src = NULL;
		GitsnTestDataFrame* df = NULL;
		switch (session->present)
		{
		case GitsnDsrcEmulatorSessionPresent_server:
			if ((s = session->x.server) == NULL) ERR_OUT(errp);
			else
			{
				while ((df = dfs->getHead(dfs)) != NULL && errp->code == 0)
				{
					dfs->extract(dfs, df);
					if ((src = GitsnTestDataFrame_encode(df, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
						if (Dz1SockUtilTxFifo_send(s->tx_fifo, s->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
						pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&src);
					}
				}
			}
			break;
		case GitsnDsrcEmulatorSessionPresent_client:
			if ((c = session->x.client) == NULL) ERR_OUT(errp);
			else
			{

				while ((df = dfs->getHead(dfs)) != NULL && errp->code == 0)
				{
					dfs->extract(dfs, df);
					if ((src = GitsnTestDataFrame_encode(df, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
						if (Dz1SockUtilTxFifo_send(c->tx_fifo, c->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
						pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&src);
					}
				}
			}

			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static Dz1TaskProcStatus _send(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	GitsnDsrcEmulatorArg* arg = (GitsnDsrcEmulatorArg*)uArg;
	GitsnDsrcEmulatorEnv* env = (GitsnDsrcEmulatorEnv*)uRsc;

	u16_t id = (u16_t)Dz1TaskSigMsg_getData(*sg);


	return ret;
}



bool_t GitsnDsrcEmulatorTest_send(void* task, u16_t id, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (task == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, GITSN_DSRC_EMULATOR_TEST_SEND, (void**)&id, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static Dz1TaskProcStatus _tdpsend(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	GitsnDsrcEmulatorArg* arg = (GitsnDsrcEmulatorArg*)uArg;
	GitsnDsrcEmulatorEnv* env = (GitsnDsrcEmulatorEnv*)uRsc;

	u16_t id = (u16_t)Dz1TaskSigMsg_getData(*sg);

	GitsnTestDataFrames* dfs = NULL;
	GitsnDsrcEmulatorSession* session = NULL;
	if ((session = env->session) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary* encoded = NULL;
		Dz1Binary* encoded_mf = NULL;

		switch (id)
		{
		case 18:	// MAP
			if ((encoded = MapData_get_uper_encoded(sample_map, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 19:	// SPAT
			if ((encoded = SPAT_get_uper_encoded(sample_spat, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;

		case 20:	// BSM
			if ((encoded = BasicSafetyMessage_get_uper_encoded(sample_bsm, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 22:	// EVA
			if ((encoded = EmergencyVehicleAlert_get_uper_encoded(sample_eva, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 26:	// PVD
			if ((encoded = ProbeVehicleData_get_uper_encoded(sample_pvd, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;

		case 27:	// RSA
			if ((encoded = RoadSideAlert_get_uper_encoded(sample_rsa, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 28:	// RTCM
			if ((encoded = RTCMcorrections_get_uper_encoded(sample_rtcm, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 29:	// SRM
			if ((encoded = SignalRequestMessage_get_uper_encoded(sample_srm, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 30:	// SSM
			if ((encoded = SignalStatusMessage_get_uper_encoded(sample_ssm, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 31:	// TIM
			if ((encoded = TravelerInformation_get_uper_encoded(sample_tim, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 32:	// PSM
			if ((encoded = PersonalSafetyMessage_get_uper_encoded(sample_psm, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 41:	// SDSM
			if ((encoded = SensorDataSharingMessage_get_uper_encoded(sample_sdsm, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 50:	// TLS
			if ((encoded = TLS_get_uper_encoded(sample_tls, errp)) == NULL) ERR_OUT(errp);
			else if ((encoded_mf = _uper_enc_messageframe(id, encoded, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EPERM); break;

		}
		if (errp->code == 0 && encoded_mf != NULL)
		{
			if ((dfs = GitsnTestDataProtocol_convertToDataFrames(encoded_mf, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(GitsnTestDataFrames_delAndSetNull, (void*)&dfs);
				if (_convert_and_send(env, dfs, errp) == FALSE) ERR_OUT(errp);
				else
				{
					dfs = NULL;
					if (encoded_mf != NULL)
						Dz1Binary_delAndSetNull((void*)&encoded_mf);
					if (encoded != NULL)
						Dz1Binary_delAndSetNull((void*)&encoded);

					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (GitsnDataFrames_delAndSetNull, (void*)&dfs);
			}
		}
	}
	return ret;
}

bool_t GitsnDsrcEmulatorTest_tdpsend(void* task, u16_t id, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (task == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, GITSN_DSRC_EMULATOR_TEST_TDP_SEND, (void**)&id, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
bool_t GitsnDsrcEmulatorTest_clear(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (task == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, GITSN_DSRC_EMULATOR_TEST_TDP_SEND, NULL, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnDsrcmEmulator_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRC_EMULATOR_TEST_INIT), _init)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRC_EMULATOR_TEST_SEND), _send)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRC_EMULATOR_TEST_TDP_SEND), _tdpsend)).code) ERR_OUT(errp);


	return ERR_IS_SUCCESS(errp);
}



// DZ1_SOCK_UTIL_RECEIVER_RECEIVED
static Dz1TaskProcStatus _client_received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDsrcEmulatorArg* arg = (GitsnDsrcEmulatorArg*)uArg;
	GitsnDsrcEmulatorEnv* env = (GitsnDsrcEmulatorEnv*)uRsc;

	GitsnDsrcEmulatorClientSession* session = NULL;

	Dz1SockUtilReceiverReceived* msg = Dz1TaskSigMsg_getData(*sg);

	if (env->session == NULL) ERR_OUT(errp);
	else if ((session = env->session->x.client) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, session->peer) != 0 || Dz1SockAddr_cmp(msg->local, session->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Binary* stream = msg->stream;

		Dz1Thread_printf("$$$ Received Message From Server] = \n");
		Dz1Binary_dump(stream, 0);

		if (_Dz1ElasticBuf_push(session->rx_buf, stream->data, stream->size, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Stream_drain(session->rx_stream, (size_t)stream->size, NULL, errp);

			if (Dz1SockUtilTxFifo_send(session->tx_fifo, session->sock, stream->data, stream->size, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Thread_printf("$$$ Reply to Server!\n");
				Dz1Error_set(errp, 0);
			}

		}
	}
	return ret;
}

// DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED
static Dz1TaskProcStatus _client_disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDsrcEmulatorArg* arg = (GitsnDsrcEmulatorArg*)uArg;
	GitsnDsrcEmulatorEnv* env = (GitsnDsrcEmulatorEnv*)uRsc;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);
	Dz1Thread_printf("!!! Client Disconnected ] = \n");
	Dz1SockAddr_dump(msg->peer, 0);


	return ret;
}


// DZ1_SOCK_UTIL_TRANSMITER_SENT
static Dz1TaskProcStatus _client_sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDsrcEmulatorArg* arg = (GitsnDsrcEmulatorArg*)uArg;
	GitsnDsrcEmulatorEnv* env = (GitsnDsrcEmulatorEnv*)uRsc;


	Dz1SockUtilTransmiterSent* msg = Dz1TaskSigMsg_getData(*sg);
	GitsnDsrcEmulatorClientSession* session = NULL;

	if (env->session == NULL) ERR_OUT(errp);
	else if ((session = env->session->x.client) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, session->peer) != 0 || Dz1SockAddr_cmp(msg->local, session->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Dz1SockUtilTxFifo_sentProc(session->tx_fifo, session->sock, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}


bool_t GitsnDsrcEmulator_clientSockMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _client_received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _client_disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _client_sent)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}



void GitsnDsrcEmulator_clientSockMsgClear(void* task)
{
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _client_received);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _client_disconnected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _client_sent);
}