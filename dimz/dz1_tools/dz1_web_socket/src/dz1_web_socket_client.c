#include <dz1_base64.h>
#include <Dz1SockUtil.h>

#include "dz1_web_socket_client.h"
#include "dz1_web_socket_frame.h"
#include "dz1_web_socket_struct.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1WebSocket_create
static bool_t _web_socket_requestU(Dz1WebSocket *p, Dz1WebSockInitInfo *info, Dz1Binary *key_bin, Dz1Error *errp)
{
	Dz1Asn1UTF8Str *req = NULL;
	if ((req = Dz1WebSockInitInfo_getRequest(info, key_bin, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t log_lv = 0;
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&req);

		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
		if (log_lv & DZ1_THREAD_LOG_DEBUG)
		{
			_Dz1Thread_log(">>> SEND Request\n");
			DZ1_DUMP(Dz1Asn1UTF8Str, req, 0);
		}

		if (Dz1SockUtilTxFifo_send(p->tx_fifo, p->sock, req->data, req->size, errp) == FALSE) ERR_OUT(errp);
		else
		{
			p->state = Dz1WebSocketState_requested;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&req);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _establish_sessionU(Dz1WebSocket *p, u32_t my_queue_id, Dz1WebSockInitInfo *info, Dz1Error *errp)
{
	struct timeval to = { 5, 0 };
	if ((p->sock = Dz1TcpClientSocket_open(p->peer, p->local, &to, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1WebSocketAuth *auth = p->auth;
		switch(info->scheme)
		{
		case Dz1WebSocketScheme_ws:
 			if ((*errp = Dz1SockUtilTcpClient_modeCallback(p->sock, p->peer, p->local, 2048, my_queue_id)).code) ERR_OUT(errp);
			else if (_web_socket_requestU(p, info, auth->key_bin, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1WebSocketScheme_wss:
#ifdef DZ1_WEB_SOCKET_SUPPORT_SSL
			if ((*errp = Dz1SockUtilTcpClient_modeSSLClient(p->sock, p->peer, p->local, 2048, Dz1SocketCallback2SSLVer_23, DZ1_SSL_DEFAULT_CIPHER_LIST, my_queue_id)).code) ERR_OUT(errp);
			else if (_web_socket_requestU(p, info, auth->key_bin, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
#else
			ERR_SET_OUT(errp, ENOSYS);
#endif
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static Dz1WebSocket *_Dz1WebSocket_createU(char *uri_u8, u32_t my_queue_id, bool_t masking, Dz1Error *errp)
{
	Dz1WebSocket *ret = NULL;
	Dz1WebSockInitInfo *info = NULL;
	if ((info = Dz1WebSockInitInfo_generate(uri_u8, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		pthread_cleanup_push(Dz1WebSockInitInfo_delAndSetNull, (void *)&info);
		if ((ret = Dz1WebSocket_new(NULL, NULL, NULL, NULL, masking, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1SockAddr peer, local;
			Dz1UniversalUniqueID uu_id;

			pthread_cleanup_push(Dz1WebSocket_delAndSetNull, (void *)&ret);
			if (0) { }

			else if ((ret->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);

			else if ((*errp = Dz1SockAddrU_setAddrByName(&peer, info->host_u8)).code) ERR_OUT(errp);
			else if ((*errp = Dz1SockAddr_setPort(&peer, info->port)).code) ERR_OUT(errp);
			else if ((ret->peer = Dz1SockAddr_clone(&peer, errp)) == NULL) ERR_OUT(errp);

			else if (Dz1SockAddr_setAddrZero(&local, &peer, errp) == FALSE) ERR_OUT(errp);
			else if ((ret->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);

			else if (Dz1UniversalUniqueID_initV1(&uu_id, errp) == FALSE) ERR_OUT(errp);	// generate uuid
			else if ((ret->auth = Dz1WebSocketAuth_generate(&uu_id, errp)) == NULL) ERR_OUT(errp);

			else if ((ret->ctx = Dz1WebSockDecCtx_generate(errp)) == NULL) ERR_OUT(errp);

			else if (_establish_sessionU(ret, my_queue_id, info, errp) == FALSE) ERR_OUT(errp);
			pthread_cleanup_pop(errp->code); // (Dz1WebSocket_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1WebSockInitInfo_delAndSetNull, (void *)&info);
	}
	return ret;
}

static char *_make_u8z(Dz1Asn1UTF8Str *uri, Dz1Error *errp)
{
	char *ret = (char *)Dz1Calloc(sizeof(char), uri->size + 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		memcpy(ret, uri->data, uri->size);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1WebSocket *Dz1WebSocket_createU(Dz1Asn1UTF8Str *uri, u32_t my_queue_id, bool_t masking, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSocket *ret = NULL;
	char *uri_u8 = NULL;

	u32_t log_lv = 0;
	Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
	if (log_lv & DZ1_THREAD_LOG_DEBUG) { _Dz1Thread_log("@@@ Open WebSocket : "); DZ1_DUMP(Dz1Asn1UTF8Str, uri, 0); }

	if (uri == NULL || uri->data == NULL || uri->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((uri_u8 = _make_u8z(uri, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&uri_u8);
		if ((ret = _Dz1WebSocket_createU(uri_u8, my_queue_id, masking, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&uri_u8);
	}
	return ret;
}

Dz1WebSocket *Dz1WebSocket_createA(str_t uri, u32_t my_queue_id, bool_t masking, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSocket *ret = NULL;
	char *uri_u8 = Dz1String_conv((u8_t *)uri, strlen(uri), DZ1_SYSTEM_MBCS_CHARSET, "UTF-8", NULL);
	if (uri_u8 == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&uri_u8);
		if ((ret = _Dz1WebSocket_createU(uri_u8, my_queue_id, masking, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&uri_u8);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1WebSocket *Dz1WebSocket_createW(wstr_t uri, u32_t my_queue_id, bool_t masking, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSocket *ret = NULL;
	char *uri_u8 = Dz1String_conv((u8_t *)uri, wcslen(uri) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, "UTF-8", NULL);
	if (uri_u8 == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&uri_u8);
		if ((ret = _Dz1WebSocket_createU(uri_u8, my_queue_id, masking, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&uri_u8);
	}
	return ret;
}
#endif
// Dz1WebSocket_create
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Response analysis
static bool_t _analysis_response(Dz1WebSocket *p, str_t http_rsp, Dz1Error *errp)
{
	str_t lines[64], cp = NULL, sp = http_rsp;
	int idx = 0;
	while (idx < 64 && (cp = strstr(sp, "\r\n")) != NULL)
	{
		lines[idx++] = sp;
		*cp++ = 0;
		*cp++ = 0;
		sp = cp;
	}

	if (idx == 0) ERR_SET_OUT(errp, ENOENT);
	else if (strnicmp(lines[0], "HTTP/1.1 101", 12) != 0 && strnicmp(lines[0], "HTTP/1.0 101", 12) != 0) ERR_SET_OUT(errp, EPERM);
	else
	{
		int i;
		u8_t mask = 0x00;
		str_t str = NULL;
		for (i = 1; errp->code == 0 && mask != 0x07 && i < idx; i++)
		{
			if (0) { }
			else if (strnicmp(lines[i], "Upgrade:", 8) == 0)
			{
				str = lines[i] + 8;
				while(*str && isspace((int)(*str)&0xFF)) str++;
				if (stricmp(str, "websocket") != 0) ERR_SET_OUT(errp, ENOSYS);
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "@@@ Upgrade confirm\n");
					mask |= 0x01;
					Dz1Error_set(errp, 0);
				}
			}
			else if (strnicmp(lines[i], "Connection:", 11) == 0)
			{
				str = lines[i] + 11;
				while(*str && isspace((int)(*str)&0xFF)) str++;
				if (stricmp(str, "upgrade") != 0) ERR_SET_OUT(errp, EPERM);
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "@@@ Connection confirm\n");
					mask |= 0x02;
					Dz1Error_set(errp, 0);
				}
			}
			else if (strnicmp(lines[i], "Sec-WebSocket-Accept:", 21) == 0)
			{
				Dz1Binary *bin = NULL;
				str = lines[i] + 21;
				while(*str && isspace((int)(*str)&0xFF)) str++;
				if ((bin = Dz1Base64_decA(str, (ssize_t)strlen(str), errp)) == NULL) ERR_OUT(errp);
				else
				{
					Dz1WebSocketAuth *auth = p->auth;
					Dz1Binary *cnf = auth->cnf_bin;
					pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

					if (Dz1Binary_cmp(cnf, bin) != 0) ERR_SET_OUT(errp, EPERM);
					else
					{
						Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "@@@ Key confirm\n");
						mask |= 0x04;
						Dz1Error_set(errp, 0);
					}

					pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
				}
			}
		}

		if (errp->code == 0 && mask != 0x07) ERR_SET_OUT(errp, EPERM);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "@@@ WebSocket established\n");
			p->state = Dz1WebSocketState_established;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static u8_t *_memsearch(u8_t *src, size_t src_sz, const u8_t *pattern, size_t pattern_sz)
{
	u8_t *ret = NULL;
	if (src_sz >= pattern_sz)
	{
		size_t i;
		u8_t *cp = NULL;
		for (cp = src, i = 0; ret == NULL && i < src_sz - pattern_sz + 1; i++, cp++)
			if (memcmp(cp, pattern, pattern_sz) == 0) ret = cp;
	}
	return ret;
}

static bool_t _web_socket_ack(Dz1WebSocket *p, Dz1Binary *bin, Dz1WebSockMsgList *ret_msgs, Dz1Error *errp)
{
	u8_t *pt = NULL;
	const u8_t pattern[] = { '\r', '\n', '\r', '\n' };
	if ((pt = _memsearch(bin->data, bin->size, pattern, sizeof(pattern))) == NULL) ERR_SET_OUT(errp, EFAULT);	// data must have '\r\n\r\n'
	else
	{
		str_t http_rsp = NULL;
		size_t rsp_sz = (pt - bin->data) + sizeof(pattern);
		if ((http_rsp = (str_t)Dz1Calloc(sizeof(char), rsp_sz + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1WebSockMsg *msg = NULL;
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&http_rsp);

			memcpy(http_rsp, bin->data, rsp_sz);
			if (_analysis_response(p, http_rsp, errp) == FALSE) ERR_OUT(errp);
			else if ((msg = Dz1WebSockMsg_new(Dz1WebSockOpCode_max, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1WebSockMsg_delAndSetNull, (void *)&msg);
				if ((*errp = ret_msgs->add(ret_msgs, msg)).code) ERR_OUT(errp);
				else
				{
					msg = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1WebSockMsg_delAndSetNull, (void *)&msg);
			}

			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&http_rsp);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Response analysis
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Web Socket Message Process
static int _is_control_msg(Dz1WebSockOpCode op)
{
	switch(op)
	{
	case Dz1WebSockOpCode_text:
	case Dz1WebSockOpCode_binary:
		return 0;
	case Dz1WebSockOpCode_ping:
	case Dz1WebSockOpCode_pong:
	case Dz1WebSockOpCode_terminate:
		return 1;
	default: return -1;
	}
}

static bool_t _process_control_msg(Dz1WebSocket *p, Dz1WebSockMsg *msg, Dz1Error *errp)
{
	Dz1Binary *payload = msg->payload, *bin = NULL;
	u8_t *data = NULL;
	Dz1WebSocketCloseReason close_reason = Dz1WebSocketCloseReason_normal_close;
	u32_t size = 0, log_lv = 0;

	switch(msg->op)
	{
	case Dz1WebSockOpCode_ping:
		/*
		5.5.2 Ping
		A Ping frame MAY include "Application data".
		PING 프레임에는 "애플리케이션 데이터"가 포함될 수 있습니다.

		Upon receipt of a Ping frame, an endpoint MUST send a Pong frame in
		response, unless it already received a Close frame.
		PING 프레임을 수신하면 EndPoint는 이미 CLOSE 프레임을 수신하지 않은 한
		응답으로 PONG 프레임을 보내야 합니다.
		
		It SHOULD respond with Pong frame as soon as is practical.
		가능한 한 빨리 PONG 프레임으로 응답해야 합니다.

		Pong frames are discussed in Section 5.5.3.
		PONG 프레임은 섹션 5.5.3에서 논의됩니다.

		An endpoint MAY send a Ping frame any time after the connection is
		established and before the connection is closed.
		EndPoint는 연결이 설정된 후 연결이 닫히기 전에 언제든지 PING 프레임을 보낼 수
		있습니다.

		NOTE: A Ping frame may serve either as a keepalive or as a means to
		verify that the remote endpoint is still responsive.
		PING 프레임은 연결 유지 또는 원격 EndPoint가 여전히 응답하는지 확인하는 수단으로
		사용될 수 있습니다.

		5.5.3 Pong
		Section 5.5.2 details requirements that apply to both Ping and Pong frames.
		섹션 5.5.2에서는 PING 및 PONG 프레임 모두에 적용되는 요구 사항을 자세히 설명합니다.

		A Pong frame sent in response to a Ping frame must have identical
		"Application data" as found in the message body of the Ping frame
		being replied to.
		PING 프레임에 대한 응답으로 전송된 PONG 프레임에는 응답 중인 PING 프레임의 
		메시지 본문에 있는 것과 동일한 "애플리케이션 데이터"가 있어야 합니다.

		If an endpoint receives a Ping frame and has not yet sent Pong
		frame(s) in response to previous Ping frame(s), the endpoint MAY
		elect to send a Pong frame for only the most recently processed Ping
		frame.
		EndPoint가 PING 프레임을 수신하고 이전 PING 프레임에 대한 응답으로 아직 PONG
		프레임을 전송하지 않은 경우 EndPoint는 가장 최근에 처리된 PING 프레임에 대해서만
		PONG 프레임을 전송하도록 선택할 수 있습니다.
		*/
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "<<< PING Frame received\n");
		if (p->state == Dz1WebSocketState_established)
		{
			if (payload != NULL) { data = payload->data; size = payload->size; }

			if ((bin = Dz1WebSocket_pongFrame(data, size, p->masking, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
				if (Dz1SockUtilTxFifo_send2(p->tx_fifo, p->sock, &bin, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
			}
		}
		break;
	case Dz1WebSockOpCode_pong:
		// Complete Ping -> NOP
		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
		if (log_lv & DZ1_THREAD_LOG_DEBUG)
		{
			_Dz1Thread_log("<<< PONG Frame received\n");
			if (payload != NULL) { _Dz1Thread_log("<<< Payload = "); DZ1_DUMP(Dz1Binary, payload, 0); }
		}
		break;
	case Dz1WebSockOpCode_terminate:
		/*
		The Close frame MAY contain a body (the "Application data" portion of
		the frame) that indicates a reason for closing, such as an endpoint
		shutting down, an endpoint having received a frame too large, or an
		endpoint having received a frame that does not conform to the format
		expected by the endpoint.
		CLOSE 프레임에는 닫는 이유를 나타내는 본문(프레임의 "애플리케이션 데이터" 부분)이
		포함될 수 있습니다. 예를 들어 EndPoint 종료, EndPoint가 너무 큰 프레임을 수신한
		경우 또는 EndPoint가 예상하는 형식을 따르지 않는 프레임을 수신한 경우.

		If there is a body, the first two bytes of the body MUST be a 2-byte
		unsigned integer (in network byte order) representing a status code with
		value /code/ defined in Section 7.4.
		본문이 있는 경우 본문의 처음 2바이트는 섹션 7.4에 정의된 /code/ 값이 있는 상태 코드를
		나타내는 2바이트 부호 없는 정수(네트워크 바이트 순서)여야 합니다.

		Following the 2-byte integer, the body MAY contain UTF-8-encoded data
		with value /reason/, the interpretation of which is not defined by
		this specification.
		2바이트 정수 다음에 본문에는 /reason/ 값을 가진 UTF-8로 인코딩된 데이터가 포함될 수 
		있으며, 이에 대한 해석은 이 사양에서 정의되지 않습니다.

		This data is not necessarily human readable but may be useful for debugging
		or passing information relevant to the script that opened the connection.
		이 데이터는 반드시 사람이 읽을 수 있는 것은 아니지만 연결을 연 스크립트와 관련된 정보를
		디버깅하거나 전달하는 데 유용할 수 있습니다.

		As the data is not guaranteed to be human readable, clients MUST NOT show it
		to end users.
		데이터는 사람이 읽을 수 있다고 보장되지 않으므로 클라이언트는 이를 최종 사용자에게 보여서는
		안 됩니다.

		Close frames sent from client to server must be masked as per
		Section 5.3.
		클라이언트에서 서버로 전송된 CLOSE 프레임은 섹션 5.3에 따라 마스크되어야 합니다.

		The application MUST NOT send any more data frames after sending a
		Close frame.
		애플리케이션은 CLOSE 프레임을 보낸 후 더 이상 데이터 프레임을 보내면 안 됩니다.

		If an endpoint receives a Close frame and did not previously send a
		Close frame, the endpoint MUST send a Close frame in response.
		EndPoint가 CLOSE 프레임을 수신하고 이전에 CLOSE 프레임을 보내지 않은 경우
		EndPoint는 응답으로 닫기 프레임을 보내야 합니다.

		(When sending a Close frame in response, the endpoint typically echo(s)
		the status code it received.)
		(응답으로 CLOSE 프레임을 보낼 때 EndPoint는 일반적으로 수신한 상태 코드를 에코합니다.)

		It SHOULD do so as soon as practical.
		가능한 한 빨리 그렇게 해야 합니다.

		An endpoint MAY delay sending a Close frame until its current message
		is sent.
		EndPoint는 현재 메시지가 전송될 때까지 닫기 프레임 전송을 지연할 수 있습니다.

		(for instance, if the majority of a fragmented message is
		already sent, an endpoint MAY send the remaining fragments before
		sending a Close frame)
		(예를 들어, 조각화된 메시지의 대부분이 이미 전송된 경우 EndPoint는 닫기 프레임을
		보내기 전에 나머지 조각을 보낼 수 있습니다.)

		However, there is no guarantee that the endpoint that has already sent
		a Close frame will continue to process data.
		그러나 이미 CLOSE 프레임을 보낸 EndPoint가 계속해서 데이터를 처리한다는 보장은 없습니다.
		*/
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "<<< CLOSE Frame received\n");
		switch(p->state)
		{
		case Dz1WebSocketState_established:
			if (payload != NULL)
			{
				data = payload->data;
				size = payload->size;
				if (size >= 2)
				{
					u8_t *sp = data;
					u16_t val = ((u16_t)(sp[0] % 0xFF) << 8) | ((u16_t)(sp[1] % 0xFF) << 0);
					close_reason = (Dz1WebSocketCloseReason)val;
				}
			}

			Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, ">>> Sending CLOSE confirm\n");
			if ((bin = Dz1WebSocket_closeFrame(close_reason, NULL, p->masking, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
				if (Dz1SockUtilTxFifo_send2(p->tx_fifo, p->sock, &bin, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);

				Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "$$$ WebSocket state : CLOSED\n");
				p->state = Dz1WebSocketState_closed;
			}
			break;
		case Dz1WebSocketState_closing:
			// Close complete
			Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "$$$ WebSocket active closing complete\n");
			Dz1Error_set(errp, EPIPE);
			break;
		}
		break;
	default:
		break;
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _web_socket_msg_proc(Dz1WebSocket *p, Dz1Binary *stream, Dz1WebSockMsgList *ret_msgs, Dz1Error *errp)
{
	int status = 0;
	Dz1WebSockMsg *msg = NULL;
	Dz1WebSockDecEnv env = { stream->data, stream->size };

	while(errp->code == 0 && Dz1WebSockDecCtx_decode(p->ctx, &env, &msg, errp))
	{
		if (msg == NULL) break;
		else
		{
			pthread_cleanup_push(Dz1WebSockMsg_delAndSetNull, (void *)&msg);
			if ((status = _is_control_msg(msg->op)) > 0)
			{
				Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "<<< Control Message received\n");
				if (_process_control_msg(p, msg, errp) == FALSE) { }
				else Dz1Error_set(errp, 0);
			}
			else if (status < 0)
			{
				Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Unknown OP Code = %02X\n", msg->op);
				Dz1Error_set(errp, 0);
			}
			else if ((*errp = ret_msgs->add(ret_msgs, msg)).code) ERR_OUT(errp);
			else
			{
				msg = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1WebSockMsg_delAndSetNull, (void *)&msg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Web Socket Message Process
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1WebSocket OnReceived
bool_t Dz1WebSocket_onReceived(Dz1WebSocket *p, Dz1SockUtilReceiverReceived *msg, Dz1WebSockMsgList *ret_msgs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL || msg == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t log_lv = 0;
		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
		if (log_lv & DZ1_THREAD_LOG_DEBUG) { _Dz1Thread_log("<<< Data Received = "); DZ1_DUMP(Dz1Binary, msg->stream, 0); }

		if (Dz1SockAddr_cmp(p->peer, msg->peer) != 0 || Dz1SockAddr_cmp(p->local, msg->local) != 0)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "??? Not my message\n");
			Dz1Error_set(errp, 0);
		}
		else
		{
			switch(p->state)
			{
			case Dz1WebSocketState_requested:
				if (_web_socket_ack(p, msg->stream, ret_msgs, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1WebSocketState_established:
			case Dz1WebSocketState_closing:
				if (_web_socket_msg_proc(p, msg->stream, ret_msgs, errp) == FALSE) { }
				else Dz1Error_set(errp, 0);
				break;
			default:
				ERR_SET_OUT(errp, EFAULT);
				break;
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Dz1WebSocket OnReceived
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1WebSocket OnSent
bool_t Dz1WebSocket_onSent(Dz1WebSocket *p, Dz1SockUtilTransmiterSent *notify, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL || notify == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1SockAddr_cmp(p->peer, notify->peer) != 0 || Dz1SockAddr_cmp(p->local, notify->local) != 0)
		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, ">>> TX-Done : Socket Address mismatch\n");
	else if (Dz1SockUtilTxFifo_sentProc(p->tx_fifo, p->sock, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// Dz1WebSocket OnSent
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// API : Dz1WebSocket_sendText
bool_t Dz1WebSocket_sendText(Dz1WebSocket *p, Dz1Asn1UTF8Str *str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;
	switch(p->state)
	{
	case Dz1WebSocketState_init:
	case Dz1WebSocketState_requested:
		Dz1Error_set(errp, EAGAIN);
		break;
	case Dz1WebSocketState_established:
		if ((bin = Dz1WebSocket_textFrame(str, p->masking, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t log_lv = 0;
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

			Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
			if (log_lv & DZ1_THREAD_LOG_DEBUG) { _Dz1Thread_log("@@@ TEXT Frame = "); DZ1_DUMP(Dz1Binary, bin, 0); }

			if (Dz1SockUtilTxFifo_send2(p->tx_fifo, p->sock, &bin, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		break;
	default:
	case Dz1WebSocketState_closing:
	case Dz1WebSocketState_closed:
		Dz1Error_set(errp, EAGAIN);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// API : Dz1WebSocket_sendText
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// API : Dz1WebSocket_sendBin
bool_t Dz1WebSocket_sendBin(Dz1WebSocket *p, u8_t *data, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;
	switch(p->state)
	{
	case Dz1WebSocketState_init:
	case Dz1WebSocketState_requested:
		Dz1Error_set(errp, EAGAIN);
		break;
	case Dz1WebSocketState_established:
		if ((bin = Dz1WebSocket_binFrame(data, size, p->masking, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t log_lv = 0;
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

			Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
			if (log_lv & DZ1_THREAD_LOG_DEBUG) { _Dz1Thread_log("@@@ Binary Frame = "); DZ1_DUMP(Dz1Binary, bin, 0); }

			if (Dz1SockUtilTxFifo_send2(p->tx_fifo, p->sock, &bin, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		break;
	default:
	case Dz1WebSocketState_closing:
	case Dz1WebSocketState_closed:
		Dz1Error_set(errp, EAGAIN);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// API : Dz1WebSocket_sendBin
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// API : Dz1WebSocket_sendPing
bool_t Dz1WebSocket_sendPing(Dz1WebSocket *p, u8_t *data, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;
	switch(p->state)
	{
	case Dz1WebSocketState_init:
	case Dz1WebSocketState_requested:
		Dz1Error_set(errp, EAGAIN);
		break;
	case Dz1WebSocketState_established:
		if ((bin = Dz1WebSocket_pingFrame(data, size, p->masking, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t log_lv = 0;
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

			Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
			if (log_lv & DZ1_THREAD_LOG_DEBUG) { _Dz1Thread_log("@@@ PING Frame = "); DZ1_DUMP(Dz1Binary, bin, 0); }

			if (Dz1SockUtilTxFifo_send2(p->tx_fifo, p->sock, &bin, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		break;
	default:
	case Dz1WebSocketState_closing:
	case Dz1WebSocketState_closed:
		Dz1Error_set(errp, EAGAIN);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// API : Dz1WebSocket_sendPing
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// API : Dz1WebSocket_sendClose
/*
	The Close frame MAY contain a body (the "Application data" portion of
	the frame) that indicates a reason for closing, such as an endpoint
	shutting down, an endpoint having received a frame too large, or an
	endpoint having received a frame that does not conform to the format
	expected by the endpoint.
	CLOSE 프레임에는 닫는 이유를 나타내는 본문(프레임의 "애플리케이션 데이터" 부분)이
	포함될 수 있습니다. 예를 들어 EndPoint 종료, EndPoint가 너무 큰 프레임을 수신한
	경우 또는 EndPoint가 예상하는 형식을 따르지 않는 프레임을 수신한 경우.

	If there is a body, the first two bytes of the body MUST be a 2-byte
	unsigned integer (in network byte order) representing a status code with
	value /code/ defined in Section 7.4.
	본문이 있는 경우 본문의 처음 2바이트는 섹션 7.4에 정의된 /code/ 값이 있는 상태 코드를
	나타내는 2바이트 부호 없는 정수(네트워크 바이트 순서)여야 합니다.

	Following the 2-byte integer, the body MAY contain UTF-8-encoded data
	with value /reason/, the interpretation of which is not defined by
	this specification.
	2바이트 정수 다음에 본문에는 /reason/ 값을 가진 UTF-8로 인코딩된 데이터가 포함될 수 
	있으며, 이에 대한 해석은 이 사양에서 정의되지 않습니다.

	This data is not necessarily human readable but may be useful for debugging
	or passing information relevant to the script that opened the connection.
	이 데이터는 반드시 사람이 읽을 수 있는 것은 아니지만 연결을 연 스크립트와 관련된 정보를
	디버깅하거나 전달하는 데 유용할 수 있습니다.

	As the data is not guaranteed to be human readable, clients MUST NOT show it
	to end users.
	데이터는 사람이 읽을 수 있다고 보장되지 않으므로 클라이언트는 이를 최종 사용자에게 보여서는
	안 됩니다.

	Close frames sent from client to server must be masked as per
	Section 5.3.
	클라이언트에서 서버로 전송된 CLOSE 프레임은 섹션 5.3에 따라 마스크되어야 합니다.

	The application MUST NOT send any more data frames after sending a
	Close frame.
	애플리케이션은 CLOSE 프레임을 보낸 후 더 이상 데이터 프레임을 보내면 안 됩니다.

	If an endpoint receives a Close frame and did not previously send a
	Close frame, the endpoint MUST send a Close frame in response.
	EndPoint가 CLOSE 프레임을 수신하고 이전에 CLOSE 프레임을 보내지 않은 경우
	EndPoint는 응답으로 닫기 프레임을 보내야 합니다.

	(When sending a Close frame in response, the endpoint typically echo(s)
	the status code it received.)
	(응답으로 CLOSE 프레임을 보낼 때 EndPoint는 일반적으로 수신한 상태 코드를 에코합니다.)

	It SHOULD do so as soon as practical.
	가능한 한 빨리 그렇게 해야 합니다.

	An endpoint MAY delay sending a Close frame until its current message
	is sent.
	EndPoint는 현재 메시지가 전송될 때까지 닫기 프레임 전송을 지연할 수 있습니다.

	(for instance, if the majority of a fragmented message is
	already sent, an endpoint MAY send the remaining fragments before
	sending a Close frame)
	(예를 들어, 조각화된 메시지의 대부분이 이미 전송된 경우 EndPoint는 닫기 프레임을
	보내기 전에 나머지 조각을 보낼 수 있습니다.)

	However, there is no guarantee that the endpoint that has already sent
	a Close frame will continue to process data.
	그러나 이미 CLOSE 프레임을 보낸 EndPoint가 계속해서 데이터를 처리한다는 보장은 없습니다.
*/

bool_t Dz1WebSocket_sendClose(Dz1WebSocket *p, Dz1WebSocketCloseReason reason, Dz1Asn1UTF8Str *opt_debug_info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;
	switch(p->state)
	{
	case Dz1WebSocketState_init:
	case Dz1WebSocketState_requested:
		Dz1Error_set(errp, EAGAIN);
		break;
	case Dz1WebSocketState_established:
		if ((bin = Dz1WebSocket_closeFrame(reason, opt_debug_info, p->masking, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t log_lv = 0;
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

			Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
			if (log_lv & DZ1_THREAD_LOG_DEBUG) { _Dz1Thread_log("@@@ Close Frame = "); DZ1_DUMP(Dz1Binary, bin, 0); }

			if (Dz1SockUtilTxFifo_send2(p->tx_fifo, p->sock, &bin, errp) == FALSE) ERR_OUT(errp);
			else
			{
				p->state = Dz1WebSocketState_closing;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		break;
	default:
	case Dz1WebSocketState_closing:
	case Dz1WebSocketState_closed:
		Dz1Error_set(errp, EAGAIN);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// API : Dz1WebSocket_sendClose
///////////////////////////////////////////////////////////////////////////////
