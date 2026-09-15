#include <ctype.h>
//#include <codeconv.h>
#include <dz1_asn1.h>
#include <dz1_str.h>
#include <dz1_fsm2.h>
#include "dz1_inet_ftp_arg.h"
#include "dz1_inet_ftp_env_util.h"
#include "dz1_inet_ftp_timer_util.h"
#include "dz1_inet_ftp_msg.h"
#include "dz1_inet_ftp_control_pi.h"
#include "dz1_inet_ftp_dtp.h"
#include "dz1_inet_ftp_fsm.h"
/*
            
s : Send
i : File Inform
N : Next TRX Entry
nd : Next Directory
P : Passive mode
a : accept
			| 1              | 2              | 3            | cTimeOut | else
------------+----------------+----------------+--------------+----------+--------------
Initial   0 |                | sUSER       w1 | err(SF)      | err(SB)  | err(U)
------------+----------------+----------------+--------------+----------+--------------
Wait USER 1 |                | sTYPE       wt | pass ?       | err(SB)  | err(U)
            |                |                | =n:err(AF)   |          |
            |                |                | =!n:sPASS w2 |          |
------------+----------------+----------------+--------------+----------+--------------
Wait PASS 2 |                | sTYPE       wt | acct ?       | err(SB)  | err(U)
            |                |                | =n:err(AF)   |          |
            |                |                | =!n:sACCT w3 |          |
------------+----------------+----------------+--------------+----------+--------------
Wait ACCT 3 |                | sTYPE       wt | err(AF)      | err(SB)  | err(U)
------------+----------------+----------------+--------------+----------+--------------
Wait TYPE t |                | dir ?          | err(AF)      | err(SB)  | err(U)
            |                | =n:Term        |              |          |
            |                | =d:sCWDd    w4 |              |          |
			|                | =u:sCWDu    w8 |              |          |
------------+----------------+----------------+--------------+----------+--------------
Wait CWDd 4 |                | mode ?         | err(NSD)     | err(SB)  | err(U)
            |                | =p:sPASV    w5 |              |          |
			|                | =a:sPORT    w5 |              |          |
------------+----------------+----------------+--------------+----------+--------------
Wait PASV 5 |                | c dir ?        | err(COMM)    | err(SB)  | err(U)
or PORT     |                | =d:RETR(P?a)w6 |              |          |
            |                | =u:STOR(P?a)w6 |              |          |
------------+----------------+----------------+--------------+----------+--------------
Wait TRX  6 | startDTP    w7 |                | err(NSF)     | err(SB)  | err(U)
------------+----------------+----------------+--------------+----------+--------------
Wait DONE 7 |                | iNsCWD      w3 | err(COMM)    | err(SB)  | err(U)
------------+----------------+----------------+--------------+----------+--------------
Wait CWDu 8 |                | mode ?         | sMKD      wA | err(SB)  | err(U)
            |                | =p:sPASV    w5 |              |          |
			|                | =a:sPORT    w5 |              |          |
------------+----------------+----------------+--------------+----------+--------------
Wait MKD  A |                | sCWDnd path ?  | err(PERM)    | err(SB)  | err(U)
            |                | =N:         w8 |              |          |
			|                | =Y:         wB |              |          |
------------+----------------+----------------+--------------+----------+--------------
Wait CWDs B |                | sMKD        wA | err(NSD)     | err(SB)  | err(U)
------------+----------------+----------------+--------------+----------+--------------
*/
static Dz1Error _encodeAndSend(Dz1TcpClientSocket *sock, Dz1InetFtpCPIMsg *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u8_t *data = NULL;
	ssize_t size = 0;
	if ((size = Dz1InetFtpCPIMsg_encode(&data, p, &err)) < 0) ERR_OUT(&err);
	else
	{
		struct timeval to = { 1, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)data);
		{
			size_t _size = size;
			u8_t *cp = data;
			Dz1Thread_printf("*** FTP >>> ");
			while(_size--) Dz1Thread_printf("%c", *cp++);
		}
		if (sock->send(sock, data, size, 1, &to, &err) < 0) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)data);
	}
	return err;
}

static Dz1Error _genPortAndSend(Dz1TcpClientSocket *sock, Dz1SockAddr *local)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1InetFtpCPIMsg *req = NULL;
	if ((req = Dz1InetFtpCPIMsg_new(Dz1InetFtpCPIMsgPresent_req, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1InetFtpCPIMsgReq *cmd = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)req);

		if ((cmd = req->x.req = Dz1InetFtpCPIMsgReq_new(Dz1InetFtpCPIMsgReqPresent_port, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((cmd->x.port = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((err = _encodeAndSend(sock, req)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)req);
	}
	return err;
}

static bool_t isCharsetNameUTF8(str_t name)
{
	if (strcmp(name, "UTF-8") == 0) return TRUE;
	if (strcmp(name, "UTF8") == 0) return TRUE;
	if (strcmp(name, "utf-8") == 0) return TRUE;
	if (strcmp(name, "utf8") == 0) return TRUE;
	return FALSE;
}

static str_t charsetConvert(str_t src, str_t srcCharSetName, str_t dstCharSetName, Dz1Error *errp)
{
	str_t ret = NULL;
	if (strcmp(srcCharSetName, dstCharSetName) == 0)
	{
		if ((ret = Dz1Str_dup(src, errp)) == NULL) ERR_OUT(errp);
	}
	else if (isCharsetNameUTF8(dstCharSetName) == FALSE) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1Asn1UTF8Str *conv = Dz1Asn1UTF8Str_newFromBuf((u8_t *)src, strlen(src), srcCharSetName, errp);
		if (conv == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&conv);
			ret = (str_t)conv->data;
			conv->data = NULL;
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&conv);
		}
	}
	return ret;
}

#if 0
static void codeconv_openCancel(void *ptr)
{
	codeconv_t h = (codeconv_t)ptr;
	codeconv_close(h);
}

static str_t charsetConvert(str_t src, str_t srcCharSetName, str_t dstCharSetName, Dz1Error *errp)
{
	str_t ret = NULL;
	if (src)
	{
		codeconv_t h = codeconv_open(dstCharSetName, srcCharSetName);
		if (h == (void *)-1) ERR_SET_OUT(errp, EFAULT);
		else
		{
			str_t temp = NULL;
			size_t srcLen = strlen(src);
			size_t dstLen = (srcLen << 2) + 1;
			pthread_cleanup_push(codeconv_openCancel, (void *)h);

			if ((ret = temp = (u8_t *)Dz1Calloc(sizeof(char), dstLen, errp)) == NULL) ERR_OUT(errp);
			else if (codeconv(h, &src, &srcLen, &temp, &dstLen) != 0) ERR_SET_OUT(errp, EFAULT);
			else
			{
				size_t convLen = (size_t)(temp - ret);
				Dz1Thread_printf("charsetConvert() : %u Byte Converted\n", convLen);
				Dz1Error_set(errp, 0);
			}

			pthread_cleanup_pop(1); // (codeconv_openCancel, (void *)h);
		}
	}
	return ret;
}
#endif
static Dz1Error _genCmdAndSend(Dz1TcpClientSocket *sock, Dz1InetFtpCPIMsgReqPresent present, str_t arg,
							   str_t localCharSetName, str_t remoteCharSetName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1InetFtpCPIMsg *req = NULL;
	if ((req = Dz1InetFtpCPIMsg_new(Dz1InetFtpCPIMsgPresent_req, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1InetFtpCPIMsgReq *cmd = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)req);

		if (arg != NULL && strcmp(localCharSetName, remoteCharSetName) != 0)
		{
			str_t _arg = charsetConvert(arg, localCharSetName, remoteCharSetName, &err);
			if (_arg == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push((Dz1DelFunc)Dz1Str_del, (void *)_arg);
				if ((cmd = req->x.req = Dz1InetFtpCPIMsgReq_new(present, _arg, &err)) == NULL) ERR_OUT(&err);
				else if ((err = _encodeAndSend(sock, req)).code) ERR_OUT(&err);
				pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Str_del, (void *)_arg);
			}
		}
		else if ((cmd = req->x.req = Dz1InetFtpCPIMsgReq_new(present, arg, &err)) == NULL) ERR_OUT(&err);
		else if ((err = _encodeAndSend(sock, req)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)req);
	}
	return err;
}

static Dz1Error _genTypeAndSend(Dz1TcpClientSocket *sock, Dz1InetFtpDTPTypePresent present, void *opt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1InetFtpCPIMsg *req = NULL;
	if ((req = Dz1InetFtpCPIMsg_new(Dz1InetFtpCPIMsgPresent_req, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1InetFtpCPIMsgReq *cmd = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)req);

		if ((cmd = req->x.req = Dz1InetFtpCPIMsgReq_new(Dz1InetFtpCPIMsgReqPresent_type, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((cmd->x.type = Dz1InetFtpDTPType_new(present, opt, &err)) == NULL) ERR_OUT(&err);
		else if ((err = _encodeAndSend(sock, req)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)req);
	}
	return err;
}

// sUSER w1
static Dz1FsmReturn FF00(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	if (session->user == NULL)
	{
		session->curStatus = Dz1InetFtpCmdResult_authFail;
		ret = Dz1FsmReturn_terminate;
	}
	else if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_user, session->user,
									 arg->localCharSetName, session->remoteCharSetName)).code)
	{
		session->curStatus = Dz1InetFtpCmdResult_unknown;
		FSM_ERR_OUT(ret, errp);
	}
	else fsm->state = Dz1InetFtpState_sentUSER;
	return ret;
}

static Dz1FsmReturn FF01(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_terminate;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	session->curStatus = Dz1InetFtpCmdResult_serverFail;
	return ret;
}

/*
static Dz1FsmReturn FF0t(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_terminate;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	session->curStatus = Dz1InetFtpCmdResult_serverBusy;
	return ret;
}

static Dz1FsmReturn FF03(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_terminate;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	session->curStatus = Dz1InetFtpCmdResult_unknown;
	return ret;
}
*/

static Dz1FsmReturn F004(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;

	if (session->curJob != NULL)
	{
		//Dz1InetFtpTransferNode *job = session->curJob;
		//Dz1InetFtpTransfer *target = job->target;
		if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_feat, NULL,
									arg->localCharSetName, session->remoteCharSetName)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else
		{
			Dz1Error_set(errp, 0);
			fsm->state = Dz1InetFtpState_sentFEAT;
		}
	}
	else ret = Dz1FsmReturn_terminate;

	return ret;
}

static Dz1FsmReturn FF04(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;

	if (session->curJob != NULL)
	{
		Dz1InetFtpTransferNode *job = session->curJob;
		Dz1InetFtpTransfer *target = job->target;
		if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_cwd, target->remote->path,
									arg->localCharSetName, session->remoteCharSetName)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else
		{
			Dz1Error_set(errp, 0);
			if (target->direction == Dz1InetFtpDirection_download) fsm->state = Dz1InetFtpState_sentCWDd;
			else if (target->direction == Dz1InetFtpDirection_upload) fsm->state = Dz1InetFtpState_sentCWDu;
			else
			{
				session->curStatus = Dz1InetFtpCmdResult_unknown;
				FSM_ERR_SET_OUT(ret, errp, EINVAL);
			}
		}
	}
	else ret = Dz1FsmReturn_terminate;

	return ret;
}

static Dz1FsmReturn FF05(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;

	if (session->password == NULL)
	{
		session->curStatus = Dz1InetFtpCmdResult_authFail;
		ret = Dz1FsmReturn_terminate;
	}
	else if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_pass, session->password,
									 arg->localCharSetName, session->remoteCharSetName)).code)
	{
		session->curStatus = Dz1InetFtpCmdResult_unknown;
		FSM_ERR_OUT(ret, errp);
	}
	else fsm->state = Dz1InetFtpState_sentPASS;
	return ret;
}

static Dz1FsmReturn FF06(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;

	if (session->account == NULL)
	{
		session->curStatus = Dz1InetFtpCmdResult_authFail;
		ret = Dz1FsmReturn_terminate;
	}
	else if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_acct, session->account,
									 arg->localCharSetName, session->remoteCharSetName)).code)
	{
		session->curStatus = Dz1InetFtpCmdResult_unknown;
		FSM_ERR_OUT(ret, errp);
	}
	else fsm->state = Dz1InetFtpState_sentACCT;
	return ret;
}

static Dz1FsmReturn FF07(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_terminate;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	session->curStatus = Dz1InetFtpCmdResult_authFail;
	return ret;
}

static Dz1FsmReturn FF08(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	Dz1InetFtpTransferNode *job = session->curJob;
	Dz1InetFtpTransfer *target = job->target;
	Dz1InetFtpFileName *file = target->remote;
	if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_size, file->name,
								arg->localCharSetName, session->remoteCharSetName)).code)
	{
		session->curStatus = Dz1InetFtpCmdResult_unknown;
		FSM_ERR_OUT(ret, errp);
	}
	else fsm->state = Dz1InetFtpState_sentSIZE;

	return ret;
}

static Dz1FsmReturn FF09(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_terminate;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	session->curStatus = Dz1InetFtpCmdResult_pathNotFound;
	return ret;
}

static Dz1Error _cmdTRX(Dz1InetFtpSession *session, Dz1InetFtpArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1InetFtpTransferNode *job = session->curJob;
	Dz1InetFtpTransfer *target = job->target;

	if (target->direction == Dz1InetFtpDirection_upload)
	{
		if ((err = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_stor, target->remote->name,
								  arg->localCharSetName, session->remoteCharSetName)).code) ERR_OUT(&err);
	}
	else if (target->direction == Dz1InetFtpDirection_download)
	{
		if ((err = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_retr, target->remote->name,
								  arg->localCharSetName, session->remoteCharSetName)).code) ERR_OUT(&err);
	}
	else ERR_SET_OUT(&err, EINVAL);

	return err;
}

static Dz1Error _parsePasvReply(Dz1SockAddr *dst, str_t result)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	char *cp = result;
	size_t size = strlen(result);
	bool_t found = FALSE;

	while(*cp) { if (*cp == '(') { cp++; size--; found = TRUE; break; } cp++; size--; }

	if (found == FALSE) ERR_SET_OUT(&err, EINVAL);
	else if (Dz1InetFtpSockAddr_dec(dst, (u8_t *)cp, size, &err) < 0) ERR_OUT(&err);

	return err;
}

Dz1Error _mkPasvSession(Dz1InetFtpSession *session, Dz1InetFtpCPIMsgReply *reply)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1SockAddr peer;
	memset(&peer, 0, sizeof(Dz1SockAddr));

	if ((err = _parsePasvReply(&peer, reply->title)).code) ERR_OUT(&err);
	else
	{
		struct timeval to = { 5, 0 };
		Dz1SockAddr local;
		memset(&local, 0, sizeof(Dz1SockAddr));
		//	connect to destination
		if ((session->dataSock = Dz1TcpClientSocket_open(&peer, &local, &to, &err)) == NULL) ERR_OUT(&err);
	}
	return err;
}

static Dz1FsmReturn FF10(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	Dz1InetFtpRcvrMsgReply *msg = (Dz1InetFtpRcvrMsgReply *)Dz1TaskSigMsg_getData(*sg);
	Dz1InetFtpCPIMsgReply *reply = msg->reply;

	if (session->isPassive)
	{
		if ((*errp = _mkPasvSession(session, reply)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else if ((*errp = _cmdTRX(session, arg)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else fsm->state = Dz1InetFtpState_sentRETRSTOR;
	}
	else
	{
		//struct timeval to = { 5, 0 };
		if ((*errp = _cmdTRX(session, arg)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else fsm->state = Dz1InetFtpState_sentRETRSTOR;
	}
	return ret;
}

static Dz1FsmReturn FF11(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_terminate;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	session->curStatus = Dz1InetFtpCmdResult_transferFail;
	return ret;
}

#if 0
static ssize_t _getTrxSize(str_t text)
{
	char buf[16] = { 0, }, *dp = buf, *cp = strrchr(text, '(');
	if (cp == NULL) return -1;
	else
	{
		cp++;	// pass '('
		while(isdigit((int)((u32_t)(*cp) & 0xFF)))
			*dp++ = *cp++;
		return (ssize_t)atoi(buf);
	}
}
#endif
static Dz1FsmReturn FF12(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)uRsc;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	Dz1InetFtpTransferNode *job = session->curJob;

	if (session->isPassive == FALSE)
	{
		Dz1SockAddr local, peer;
		struct timeval to = { 5, 0 };
		if ((session->dataSock = session->portSock->accept(session->portSock, &local, &peer, &to, errp)) == NULL)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		Dz1TcpServerSocket_closeAndSetNull(&session->portSock);
	}

	if (session->dataSock == NULL)
	{
		session->curStatus = Dz1InetFtpCmdResult_unknown;
		FSM_ERR_SET_OUT(ret, errp, EFAULT);
	}
	else
	{
		//Dz1InetFtpRcvrMsgReply *msg = (Dz1InetFtpRcvrMsgReply *)Dz1TaskSigMsg_getData(*sg);
		//Dz1InetFtpCPIMsgReply *reply = msg->reply;
		if ((session->dtp = Dz1InetFtpDTP_start(env->tSelf, session->peer, session->local, session->dataSock,
											session->dtpSpec, job->target, errp)) == -1)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else fsm->state = Dz1InetFtpState_waitANY;
	}
	return ret;
}

static Dz1FsmReturn FF13(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_terminate;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	session->curStatus = Dz1InetFtpCmdResult_fileNotFound;
	return ret;
}

static Dz1FsmReturn FF14(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	fsm->state = Dz1InetFtpState_waitDTP;
	return ret;
}

static Dz1FsmReturn FF15(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_terminate;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	session->curStatus = Dz1InetFtpCmdResult_transferFail;
	return ret;
}

static Dz1FsmReturn FF16(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	Dz1InetFtpTransferNode *job = session->curJob;
	Dz1InetFtpPathInfo *_path = job->pathInfo;
	Dz1InetFtpPathNode *node = _path->current;

	if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_mkd, node->path,
								arg->localCharSetName, session->remoteCharSetName)).code)
	{
		session->curStatus = Dz1InetFtpCmdResult_unknown;
		FSM_ERR_OUT(ret, errp);
	}
	else fsm->state = Dz1InetFtpState_sentMKD;

	return ret;
}

static Dz1FsmReturn FF17(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	Dz1InetFtpTransferNode *job = session->curJob;
	Dz1InetFtpPathInfo *_path = job->pathInfo;
	Dz1InetFtpPathNode *node = _path->current;

	if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_cwd, node->path,
								arg->localCharSetName, session->remoteCharSetName)).code)
	{
		session->curStatus = Dz1InetFtpCmdResult_unknown;
		FSM_ERR_OUT(ret, errp);
	}
	else
	{
		if ((_path->current = _path->current->next) != NULL)
			fsm->state = Dz1InetFtpState_sentCWDs;
		else
			fsm->state = Dz1InetFtpState_sentCWDu;
	}

	return ret;
}

#if 0
static Dz1FsmReturn FF18(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_terminate;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	session->curStatus = Dz1InetFtpCmdResult_noPermission;
	return ret;
}
#endif

static Dz1FsmReturn FF22(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;

	if (session->isPassive)
	{
		if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_pasv, NULL,
									arg->localCharSetName, session->remoteCharSetName)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else fsm->state = Dz1InetFtpState_sentPASVPORT;
	}
	else
	{
		u16_t port = 0;
		Dz1SockAddr local;
		memcpy(&local, session->local, sizeof(Dz1SockAddr));

		if (session->portSock != NULL) Dz1TcpServerSocket_closeAndSetNull(&session->portSock);

		if ((*errp = Dz1SockAddr_setPort(&local, 0)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else if ((session->portSock = Dz1TcpServerSocket_open(&local, &port, 5, errp)) == NULL)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else if ((*errp = Dz1SockAddr_setPort(&local, port)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else if ((*errp = _genPortAndSend(session->sock, &local)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else fsm->state = Dz1InetFtpState_sentPASVPORT;
	}
	return ret;
}

static Dz1FsmReturn _doNextFile(Dz1Fsm2 *fsm, Dz1InetFtpArg *arg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;

	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	if ((session->curJob = session->curJob->next) != NULL)
	{
		if ((*errp = _genCmdAndSend(session->sock, Dz1InetFtpCPIMsgReqPresent_cwd, "/",
									arg->localCharSetName, session->remoteCharSetName)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else fsm->state = Dz1InetFtpState_sentTYPE;
	}
	else ret = Dz1FsmReturn_terminate;

	return ret;
}

static Dz1FsmReturn FF19(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	Dz1InetFtpRcvrMsgReply *msg = (Dz1InetFtpRcvrMsgReply *)Dz1TaskSigMsg_getData(*sg);
	Dz1InetFtpCPIMsgReply *reply = msg->reply;
	ssize_t size = (ssize_t)atoi(reply->title);

	if (size < 0)
	{
		session->curStatus = Dz1InetFtpCmdResult_unknown;
		FSM_ERR_SET_OUT(ret, errp, EFAULT);
	}
	else
	{
		Dz1InetFtpTransferNode *job = session->curJob;
		Dz1InetFtpTransfer *txfer = job->target;
		Dz1InetFtpFileInfo *local = txfer->local;
		Dz1InetFtpFileName *remote = txfer->remote;

		u32_t localSize = (u32_t)-1;

		remote->size = (u32_t)size;

		if (local->present == Dz1InetFtpFileInfoPresent_file)
		{
			Dz1InetFtpFileName *file = local->x.file;
			localSize = file->size;
		}

		if (localSize == (u32_t)-1 || (remote->size >= 0 && remote->size != localSize))
			ret = FF22(fsm, uArg, uRsc, timer, event, sg, errp); // perform STOR/RETR
		else
		{
			if (session->fileDone)
			{
				Dz1InetFtpTransferNode *job = session->curJob;
				job->target->result = Dz1InetFtpCmdResult_omitted;
				session->fileDone(session->fileDoneParam, session->peer, job->target);
			}

			ret = _doNextFile(fsm, arg, errp);
		}
	}
	return ret;
}

static Dz1FsmReturn FF20(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;

	if (session->fileDone)
	{
		Dz1InetFtpTransferNode *job = session->curJob;
		job->target->result = Dz1InetFtpCmdResult_success;
		session->fileDone(session->fileDoneParam, session->peer, job->target);
	}

	return _doNextFile(fsm, arg, errp);

	return ret;
}

static Dz1FsmReturn FF21(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	fsm->state = Dz1InetFtpState_waitDONE;
	return ret;
}

static Dz1FsmReturn FF23(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	//Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;

	if (session->curJob != NULL)
	{
		if ((*errp = _genTypeAndSend(session->sock, Dz1InetFtpDTPTypePresent_image, NULL)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else
		{
			Dz1Error_set(errp, 0);
			fsm->state = Dz1InetFtpState_sentTYPE;
		}
	}
	else ret = Dz1FsmReturn_terminate;

	return ret;
}

static Dz1Error _checkUTF8(void *ptr, str_t str)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)ptr;
	if (strstr(str, "UTF8") != NULL)
	{
		Dz1Str_delAndSetNull(&session->remoteCharSetName);
		if ((session->remoteCharSetName = Dz1Str_dup("UTF-8", &err)) == NULL) ERR_OUT(&err);
		else Dz1Error_set(&err, EEXIST);
	}
	return err;
}

static Dz1Error checkUTF8(Dz1InetFtpSession *session, Dz1InetFtpCPIMsgReply *reply)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = reply->list->travel(reply->list, _checkUTF8, (void *)session)).code)
	{
		if (err.code == EEXIST) Dz1Error_set(&err, 0);
		else ERR_OUT(&err);
	}
	return err;
}
static Dz1FsmReturn FF24(Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp)
{
	Dz1FsmReturn ret = Dz1FsmReturn_continue;
	//Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpSession *session = (Dz1InetFtpSession *)fsm->fsmArg;
	Dz1InetFtpRcvrMsgReply *msg = (Dz1InetFtpRcvrMsgReply *)Dz1TaskSigMsg_getData(*sg);
	Dz1InetFtpCPIMsgReply *reply = msg->reply;

	if ((*errp = checkUTF8(session, reply)).code)
	{
		session->curStatus = Dz1InetFtpCmdResult_unknown;
		FSM_ERR_OUT(ret, errp);
	}
	else if (session->curJob != NULL)
	{
		//Dz1InetFtpTransferNode *job = session->curJob;
		//Dz1InetFtpTransfer *target = job->target;
		if ((*errp = _genTypeAndSend(session->sock, Dz1InetFtpDTPTypePresent_image, NULL)).code)
		{
			session->curStatus = Dz1InetFtpCmdResult_unknown;
			FSM_ERR_OUT(ret, errp);
		}
		else
		{
			Dz1Error_set(errp, 0);
			fsm->state = Dz1InetFtpState_sentTYPE;
		}
	}
	else ret = Dz1FsmReturn_terminate;

	return ret;
}

static Dz1Fsm2Func dz1InetFtpFSM[Dz1InetFtpState_max][Dz1InetFtpEvent_max] =
{//   1Prp  2OK   3Nxt  4ERR  5TXD
	{ NULL, FF00, FF01, FF01, NULL }, // 0 initial
	{ NULL, F004, FF05, FF07, NULL }, // 1 sentUSER
	{ NULL, F004, FF06, FF07, NULL }, // 2 sentPASS
	{ NULL, F004, FF01, FF07, NULL }, // 3 sentACCT
	{ NULL, FF04, FF01, FF01, NULL }, // 4 sentTYPE
	{ NULL, FF08, FF01, FF09, NULL }, // 5 sentCWDd
	{ NULL, FF10, FF01, FF11, NULL }, // 6 sentPASVPORT
	{ FF12, NULL, FF01, FF13, NULL }, // 7 sentRETRSTOR
	{ NULL, FF14, FF01, FF15, FF21 }, // 8 waitANY
	{ NULL, FF22, FF01, FF16, NULL }, // 9 sentCWDu
	{ NULL, FF17, FF01, FF17, NULL }, // 10 sentMKD
	{ NULL, FF16, FF01, FF09, NULL }, // 11 sentCWDs
	{ NULL, FF19, FF01, FF09, NULL }, // 12 sentSIZE
	{ NULL, NULL, NULL, NULL, FF20 }, // 13 waitDTP
	{ NULL, FF20, FF01, FF09, NULL }, // 14 waitDONE
	{ FF01, FF24, FF01, FF23, NULL }  // 15 sentFEAT
};

static int Dz1InetFtpEvent_get(struct Dz1Fsm2 *fsm, void *uArg, void *uRsc, void *sg)
{
	Dz1InetFtpEvent ret = Dz1InetFtpEvent_max;
	u32_t type = Dz1TaskSigMsg_getType(sg);
	switch(type)
	{
	case DZ1_INET_FTP_RCVE_REPLY:
		{
			Dz1InetFtpRcvrMsgReply *msg = (Dz1InetFtpRcvrMsgReply *)Dz1TaskSigMsg_getData(sg);
			Dz1InetFtpCPIMsgReply *reply = msg->reply;
			u32_t major = reply->code / 100;
			switch(major)
			{
			case 1:
				return Dz1InetFtpEvent_prepare;
			case 2:
				return Dz1InetFtpEvent_success;
			case 3:
				return Dz1InetFtpEvent_andNext;
			case 4:
			case 5:
				return Dz1InetFtpEvent_error;
			default:
				return Dz1InetFtpEvent_max;
			}
		}
	default:
		return Dz1InetFtpEvent_max;
	}

	return ret;
}

static Dz1Error Dz1InetFtpFunc_get(int state, int event, Dz1Fsm2Func *ret)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (state < 0 || state >= Dz1InetFtpState_max)
	{
		Dz1Thread_printf("Dz1InetFtpFunc_get() : State is Out of range = %d\n", state);
		ERR_SET_OUT(&err, EINVAL);
	}
	else if (event < 0 || event >= Dz1InetFtpEvent_max)
	{
		Dz1Thread_printf("Dz1InetFtpFunc_get() : Event is Out of range = %d\n", event);
		ERR_SET_OUT(&err, EINVAL);
	}
	else (*ret) = dz1InetFtpFSM[state][event];

	return err;
}

Dz1Fsm2 *Dz1InetFtpFsm_new(Dz1InetFtpSession *session, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	Dz1Fsm2 *ret = Dz1Fsm2_new("Dz1InetFTPFSM", TRUE, 16, Dz1InetFtpEvent_get, NULL, Dz1InetFtpFunc_get, (void **)&session, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

typedef struct Dz1InetFtpFsmTerminateArg
{
	Dz1InetFtpSessionList *sessions;
	Dz1InetFtpSession *session;
	void *timer;
} Dz1InetFtpFsmTerminateArg;

static void Dz1InetFtpFsm_terminate(void *ptr)
{
	Dz1InetFtpFsmTerminateArg *arg = (Dz1InetFtpFsmTerminateArg *)ptr;
	Dz1InetFtpSessionCleanupRuntimeArg cleanupArg = { arg->session, arg->timer };

	arg->sessions->extract(arg->sessions, arg->session);

	Dz1InetFtpSession_cleanupRunTime((void *)&cleanupArg);
}

Dz1TaskProcStatus Dz1InetFtpFsm_replyMsgProc(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)uRsc;
	
	Dz1InetFtpRcvrMsgReply *msg = (Dz1InetFtpRcvrMsgReply *)Dz1TaskSigMsg_getData(*sg);
	Dz1InetFtpSession key = { msg->peer, msg->local }, *session = NULL;

	Dz1InetFtpTimer_resetMsgWait(timer, msg->peer, msg->local);

	if ((session = env->sessionList->find(env->sessionList, &key)) == NULL)
	{
		Dz1Thread_printf("Dz1InetFtpFsm_replyMsgProc() : Session Not Found\n");
		Dz1Thread_printf("Message = "); Dz1InetFtpRcvrMsgReply_dump(msg, 0);
		ERR_SET_OUT(errp, ESRCH);
	}
	else
	{
		Dz1FsmReturn status = Dz1FsmReturn_continue;
		Dz1InetFtpFsmTerminateArg _arg = { env->sessionList, session, timer };

		pthread_cleanup_push(Dz1InetFtpFsm_terminate, (void *)&_arg);

		{
			size_t _size = msg->pkt->size;
			u8_t *cp = msg->pkt->data;
			Dz1Thread_printf("*** FTP <<< ");
			while(_size--) Dz1Thread_printf("%c", *cp++);
		}

		if ((status = Dz1Fsm2_proc(session->fsm, uArg, env, timer, sg, errp)) == Dz1FsmReturn_error) ERR_OUT(errp);

		pthread_cleanup_pop(status != Dz1FsmReturn_continue);
	}
	return ret;
}

Dz1TaskProcStatus Dz1InetFtpFsm_replyMsgProc2(Dz1InetFtpSession *session,
											  void *uArg, void *uRsc, void *timer,
											  Dz1InetFtpEvent event, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)uRsc;
	Dz1FsmReturn status = Dz1FsmReturn_continue;

	Dz1InetFtpFsmTerminateArg _arg = { env->sessionList, session, timer };
	pthread_cleanup_push(Dz1InetFtpFsm_terminate, (void *)&_arg);

	Dz1InetFtpTimer_resetMsgWait(timer, session->peer, session->local);
	if ((status = Dz1Fsm2_proc2(session->fsm, uArg, env, timer, event, sg, errp)) == Dz1FsmReturn_error) ERR_OUT(errp);

	pthread_cleanup_pop(status != Dz1FsmReturn_continue);

	return ret;
}
