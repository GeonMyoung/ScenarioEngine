#include <dz1_socket_receiver.h>
#include "dz1_inet_ftp_dtp_arg.h"

#include "dz1_inet_ftp_dtp.h"
#include "dz1_inet_ftp_msg.h"
#define DZ1_INET_FTP_DTP_BUFSIZE	0x10000

#define DZ1_FTP_TRX_TIMEOUT_SEC		300

static Dz1Error _DataFragmentList_size(void *ptr, Dz1Binary *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ssize_t *ret = (ssize_t *)ptr;

	(*ret) += p->size;

	return err;
}

static ssize_t DataFragmentList_size(DataFragmentList *list, Dz1Error *errp)
{
	ssize_t ret = 0;
	if ((*errp = list->travel(list, _DataFragmentList_size, (void *)&ret)).code) { ERR_OUT(errp); ret = -1; }
	return ret;
}

typedef struct DataFragmentListSerializeArg
{
	u8_t *cp;
} DataFragmentListSerializeArg;

static Dz1Error _DataFragmentList_serialize(void *ptr, Dz1Binary *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	DataFragmentListSerializeArg *arg = (DataFragmentListSerializeArg *)ptr;

	memcpy(arg->cp, p->data, p->size);
	arg->cp += p->size;

	return err;
}

static Dz1Error DataFragmentList_serialize(DataFragmentList *list, u8_t *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	DataFragmentListSerializeArg arg = { dst };
	if ((err = list->travel(list, _DataFragmentList_serialize, (void *)&arg)).code) ERR_OUT(&err);
	return err;
}

static Dz1InetFtpRXDTPDest *Dz1InetFtpRXDTPDest_init(Dz1InetFtpFileInfo *job, Dz1Error *errp)
{
	Dz1InetFtpRXDTPDest *ret = NULL;
	switch(job->present)
	{
	case Dz1InetFtpFileInfoPresent_file:
		if ((ret = Dz1InetFtpRXDTPDest_new(Dz1InetFtpRXDTPDestPresent_fp, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			char fn[4096];
			Dz1InetFtpFileName *file = job->x.file;
			pthread_cleanup_push(Dz1InetFtpRXDTPDest_delAndSetNull, (void *)&ret);

			if (file->path == NULL) strcpy(fn, file->name);
			else sprintf(fn, "%s" DIR_SEPRATOR "%s", file->path, file->name);

			Dz1Thread_printf("Dz1InetFtpRXDTPDest_init() : fn = [%s]\n", fn);
			if ((ret->x.fp = fopen(fn, "wb")) == NULL) ERR_SET_OUT(errp, errno); else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1InetFtpRXDTPDest_delAndSetNull, (void *)&ret);
		}
		break;
	case Dz1InetFtpFileInfoPresent_buffer:
		if ((ret = Dz1InetFtpRXDTPDest_new(Dz1InetFtpRXDTPDestPresent_list, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1InetFtpRXDTPDest_delAndSetNull, (void *)&ret);

			if ((ret->x.list = DataFragmentList_new(errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (Dz1InetFtpRXDTPDest_delAndSetNull, (void *)&ret);
		}
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return ret;
}

typedef struct Dz1InetFtpRXDTPEnv
{
	// append received data to frontBuffer
	ssize_t	 (*concat)(struct Dz1InetFtpRXDTPEnv *env, u8_t *src, size_t size, Dz1Error *errp);

	u8_t	*frontBuffer;		// 64KB Fixed Size
	size_t	 frontBufferSize;	// data size

	// Transform front buffer to mediate buffer
	//	Dz1InetFtpDTPMode_stream		
	//		Dz1InetFtpDTPStruct_file		: just copy Source Data to Mediate Buffer(Socket Closed mean EOF)
	//		Dz1InetFtpDTPStruct_record(X)	: escape sequencing for EOR, EOF, EOR+EOF. Each EOR made fragment buffer and store Mediate Buffer List
	//		Dz1InetFtpDTPStruct_page(X)		: not support

	//	Dz1InetFtpDTPMode_block			-> Generally not supported
	//		Dz1InetFtpDTPStruct_file		: copy data block to Mediate Buffer, save marker(Never receive EOR)
	//		Dz1InetFtpDTPStruct_record		: when received EOR Block, it make a fragment buffer
	//		Dz1InetFtpDTPStruct_page		: not support

	//	Dz1InetFtpDTPMode_compressed	-> Generally not supported
	//		Dz1InetFtpDTPStruct_file		: copy decompressed data to Mediate Buffer(Never Receive EOR)
	//		Dz1InetFtpDTPStruct_record		: when received EOR Block, it make a fragment buffer
	//		Dz1InetFtpDTPStruct_page		: not support

	// return :  0 = need more data
	//			-1 = error
	//			 0 < processed byte size of front buffer
	Dz1Error (*frontConsumer)(struct Dz1InetFtpRXDTPEnv *env);

	Dz1Binary *mediateBuffer;

	// Transform mediate buffer to destination
	//	Dz1InetFtpDTPTypePresent_ascii
	//		Dz1InetFtpDTPTextForm_nonPrint	: just pass to destination
	//		Dz1InetFtpDTPTextForm_telnet	: same as Dz1InetFtpDTPTextForm_nonPrint
	//		Dz1InetFtpDTPTextForm_asa		: same as Dz1InetFtpDTPTextForm_nonPrint

	//	Dz1InetFtpDTPTypePresent_ebcdic		: not support
	//	Dz1InetFtpDTPTypePresent_image		: just pass to destination
	//	Dz1InetFtpDTPTypePresent_local		: just pass to destination(Only support byte size = 8)

	// Totally: Internal Character of General PC is same as transfer byte size
	//			Thus, no variance between from Transfer Character to Internal Character
	Dz1Error (*writeToDest)(struct Dz1InetFtpRXDTPEnv *dst);

	// Destination
	Dz1InetFtpRXDTPDest	*dest;
	size_t written;
} Dz1InetFtpRXDTPEnv;

static ssize_t Dz1InetFtpRXDTPEnv_concat(Dz1InetFtpRXDTPEnv *env, u8_t *data, size_t size, Dz1Error *errp)
{
	size_t spaceSize = DZ1_INET_FTP_DTP_BUFSIZE - env->frontBufferSize;
	if (size > spaceSize) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else
	{
		u8_t *cp = env->frontBuffer + env->frontBufferSize;
		memcpy(cp, data, size);
		env->frontBufferSize += size;
	}
	return (ssize_t)size;
}

static Dz1Error Dz1InetFtpRXDTPEnv_fcBypass(Dz1InetFtpRXDTPEnv *env)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (env->mediateBuffer) Dz1Binary_del(env->mediateBuffer);

	if ((env->mediateBuffer = Dz1Binary_new(env->frontBuffer, (u32_t)env->frontBufferSize, &err)) == NULL) ERR_OUT(&err);
	else env->frontBufferSize = 0;

	return err;
}

static Dz1Error selectFrontConsumer(Dz1InetFtpRXDTPEnv *env, Dz1InetFtpDTPSpec *spec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(spec->mode)
	{
	case Dz1InetFtpDTPMode_stream:
		switch(spec->stru)
		{
		case Dz1InetFtpDTPStruct_file:
			env->frontConsumer = Dz1InetFtpRXDTPEnv_fcBypass;
			break;
		default:
		case Dz1InetFtpDTPStruct_record:
		case Dz1InetFtpDTPStruct_page:
			ERR_SET_OUT(&err, ENOSPC);
			break;
		}
		break;
	default:
	case Dz1InetFtpDTPMode_block:
	case Dz1InetFtpDTPMode_compressed:
		ERR_SET_OUT(&err, ENOSPC);
		break;
	}
	return err;
}

static Dz1Error Dz1InetFtpRXDTPEnv_wBypass(Dz1InetFtpRXDTPEnv *env)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpRXDTPDest *dest = env->dest;
	size_t written = 0;
	pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&env->mediateBuffer);
	switch(dest->present)
	{
	case Dz1InetFtpRXDTPDestPresent_fp:
		if ((written = fwrite(env->mediateBuffer->data, sizeof(u8_t), env->mediateBuffer->size, dest->x.fp)) != env->mediateBuffer->size) ERR_SET_OUT(&err, EFAULT);
		break;
	case Dz1InetFtpRXDTPDestPresent_list:
		if ((err = dest->x.list->add(dest->x.list, env->mediateBuffer)).code) ERR_OUT(&err);
		else
		{
			written = env->mediateBuffer->size;
			env->mediateBuffer = NULL;
		}
		break;
	default:
		break;
	}
	pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&env->mediateBuffer);
	env->written += written;
	return err;
}

static Dz1Error selectWritor(Dz1InetFtpRXDTPEnv *env, Dz1InetFtpDTPType *type)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(type->present)
	{
	case Dz1InetFtpDTPTypePresent_ascii:
		/*
		// experimental
		if (type->x.ascii == NULL) env->writeToDest = Dz1InetFtpRXDTPEnv_wBypass;
		else
		{
			switch(*type->x.ascii)
			{
			default:
			case Dz1InetFtpDTPTextForm_nonPrint:
				env->writeToDest = Dz1InetFtpRXDTPEnv_wBypass;
				break;
			case Dz1InetFtpDTPTextForm_telnet:
				env->writeToDest = Dz1InetFtpRXDTPEnv_wBypass;
				break;
			case Dz1InetFtpDTPTextForm_asa:
				env->writeToDest = Dz1InetFtpRXDTPEnv_wBypass;
				break;
			}
		}
		*/
		env->writeToDest = Dz1InetFtpRXDTPEnv_wBypass;
		break;
	case Dz1InetFtpDTPTypePresent_image:
		env->writeToDest = Dz1InetFtpRXDTPEnv_wBypass;
		break;
	case Dz1InetFtpDTPTypePresent_local:
		if (type->x.local != 8) ERR_SET_OUT(&err, ENOSYS);
		else env->writeToDest = Dz1InetFtpRXDTPEnv_wBypass;
		break;
	default:
	case Dz1InetFtpDTPTypePresent_ebcdic:
		ERR_SET_OUT(&err, ENOSYS);
		break;
	}
	return err;
}

static void Dz1InetFtpRXDTPEnv_del(Dz1InetFtpRXDTPEnv *p)
{
	if (!p) return;
	if (p->frontBuffer) Dz1Free(p->frontBuffer);
	if (p->mediateBuffer) Dz1Binary_del(p->mediateBuffer);
	if (p->dest) Dz1InetFtpRXDTPDest_del(p->dest);
	Dz1Free(p);
}

static void Dz1InetFtpRXDTPEnv_delAndSetNull(void *ptr)
{
	Dz1InetFtpRXDTPEnv **p = (Dz1InetFtpRXDTPEnv **)ptr;
	Dz1InetFtpRXDTPEnv_del(*p); *p = NULL;
}

static Dz1InetFtpRXDTPEnv *Dz1InetFtpRXDTPEnv_new(Dz1InetFtpDTPSpec *spec, Dz1InetFtpTransfer *job, Dz1Error *errp)
{
	Dz1InetFtpRXDTPEnv *ret = (Dz1InetFtpRXDTPEnv *)Dz1Calloc(sizeof(Dz1InetFtpRXDTPEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpRXDTPEnv_delAndSetNull, (void *)&ret);
		ret->concat = Dz1InetFtpRXDTPEnv_concat;
		if ((ret->frontBuffer = (u8_t *)Dz1Malloc(DZ1_INET_FTP_DTP_BUFSIZE, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->frontBufferSize = 0;
			ret->written = 0;
			if ((*errp = selectFrontConsumer(ret, spec)).code) ERR_OUT(errp);
			else if ((*errp = selectWritor(ret, spec->type)).code) ERR_OUT(errp);
			else if ((ret->dest = Dz1InetFtpRXDTPDest_init(job->local, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1InetFtpRXDTPEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error Dz1InetFtpRXDTPEnv_destFinalize(Dz1InetFtpRXDTPEnv *env, Dz1InetFtpTransfer *job)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ssize_t size = 0;
	Dz1InetFtpRXDTPDest *dest = env->dest;
	Dz1InetFtpFileName *remote = job->remote;
	u32_t done_size = remote->size;
	switch(dest->present)
	{
	case Dz1InetFtpRXDTPDestPresent_fp:
		if ((size = ftell(dest->x.fp)) != done_size) ERR_SET_OUT(&err, EINVAL);
		fclose(dest->x.fp);
		dest->x.fp = NULL;
		break;
	case Dz1InetFtpRXDTPDestPresent_list:
		if ((size = DataFragmentList_size(dest->x.list, &err)) < 0) ERR_OUT(&err);
		else if (size != done_size) ERR_SET_OUT(&err, EINVAL);
		else
		{
			Dz1Binary *bin = NULL;

			if (job->local->x.buffer != NULL) Dz1Binary_del(job->local->x.buffer);
			job->local->x.buffer = NULL;

			if ((bin = job->local->x.buffer = Dz1Binary_new(NULL, 0, &err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&job->local->x.buffer);

				if ((bin->size = (u32_t)size) > 0)
				{
					if ((bin->data = (u8_t *)Dz1Malloc(size, &err)) == NULL) ERR_OUT(&err);
					else if ((err = DataFragmentList_serialize(dest->x.list, bin->data)).code) ERR_OUT(&err);
				}

				pthread_cleanup_pop(err.code); // (Dz1Binary_delAndSetNull, (void *)&job->local->x.buffer);
			}
		}
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

// Dz1 INET FTP DTP : internal char = 8bit octet byte
static Dz1Error Dz1InetFtpRXDTP_init(void **ret, void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpRXDTPArg *arg = (Dz1InetFtpRXDTPArg *)uArg;
	Dz1InetFtpRXDTPEnv *env = NULL;

	if ((env = (*ret) = Dz1InetFtpRXDTPEnv_new(arg->spec, arg->job, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error _postPktInform(void *tFTP, Dz1SockAddr *peer, Dz1SockAddr *local, size_t size)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpBasicMsg *msg = Dz1InetFtpBasicMsg_new(NULL, NULL, (u32_t)size, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1InetFtpBasicMsg_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->local = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(tFTP, DZ1_TASK_QUEUE_NONE,
									DZ1_INET_FTP_DTP_TRANSFER_PKT,
									(void **)&msg,
									(Dz1DelFunc)Dz1InetFtpBasicMsg_del,
									(Dz1DumpFunc)Dz1InetFtpBasicMsg_dump,
									NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1InetFtpBasicMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}

// Issue Dz1TcpSocketReceiverForwardFunc when Receiver got data from socket
static Dz1SocketReceierBehavior Dz1InetFtpRXDTP_forward(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local,
													  Dz1TcpClientSocket *s, u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;
#if 1
	Dz1InetFtpRXDTPArg *arg = (Dz1InetFtpRXDTPArg *)uArg;
	Dz1InetFtpRXDTPEnv *env = (Dz1InetFtpRXDTPEnv *)uRsc;
	if (env->concat(env, data, size, errp) < 0) ERR_OUT(errp);
	else if ((*errp = env->frontConsumer(env)).code) ERR_OUT(errp);
	else if ((*errp = env->writeToDest(env)).code) ERR_OUT(errp);
	else if ((*errp = _postPktInform(arg->tFTP, peer, local, env->written)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if (errp->code != 0) ret = Dz1SocketReceierBehavior_exception;
#else
	Dz1Error_set(errp, EPIPE);
	ret = Dz1SocketReceierBehavior_exception;
#endif
	return ret;
}

/*
// Issue Dz1TcpSocketReceiverTimeoutFunc when Receiver got timeout
static Dz1SocketReceierBehavior Dz1InetFtpRXDTP_timeout(void *userParam, void *userResource,
													  Dz1SockAddr *peer, Dz1SockAddr *local,
													  Dz1TcpClientSocket *s, Dz1Error *errp)
{
	// post DTP timeout to tParent
	ERR_SET_OUT(errp, ETIMEDOUT);
	return Dz1SocketReceierBehavior_exception;
}
*/

static Dz1Error _postMsg(void *taskFTP, u32_t msgType, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1InetFtpRXDTPArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpMsgFileDone *msg = Dz1InetFtpMsgFileDone_new(NULL, NULL, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1InetFtpDTPMsg_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->local = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(taskFTP, DZ1_TASK_QUEUE_NONE, msgType,	(void **)&msg,
									(Dz1DelFunc)Dz1InetFtpMsgFileDone_del,
									(Dz1DumpFunc)Dz1InetFtpMsgFileDone_dump,
									NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1InetFtpDTPMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}

// Issue Dz1TcpSocketReceiverExceptionFunc when Receiver got exception
// EINVAL		= Forwarding Exception
// EPIPE		= Socket Closed
// ETIMEDOUT	= Select Wait Timeout
static void Dz1InetFtpRXDTP_exception(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local,
									Dz1TcpClientSocket *s, Dz1Error *reason)
{
	// process destination
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpRXDTPEnv *env = (Dz1InetFtpRXDTPEnv *)uRsc;
	Dz1InetFtpRXDTPArg *arg = (Dz1InetFtpRXDTPArg *)uArg;
	switch (reason->code)
	{
	default:
	case EINVAL:
		// Post Transaction Fail
		if ((err = _postMsg(arg->tFTP, DZ1_INET_FTP_DTP_TRANSFER_FAIL, peer, local, arg)).code) ERR_OUT(&err);
		break;
	case EPIPE:
		if (arg->spec->mode == Dz1InetFtpDTPMode_stream)
		{
			if (arg->spec->stru == Dz1InetFtpDTPStruct_file)
			{
				if ((err = Dz1InetFtpRXDTPEnv_destFinalize(env, arg->job)).code)
				{
					if ((err = _postMsg(arg->tFTP, DZ1_INET_FTP_DTP_TRANSFER_FAIL, peer, local, arg)).code) ERR_OUT(&err);
				}
				else if ((err = _postMsg(arg->tFTP, DZ1_INET_FTP_DTP_TRANSFER_DONE, peer, local, arg)).code) ERR_OUT(&err);
			}
		}
		else if (arg->spec->mode == Dz1InetFtpDTPMode_block)
		{	// previously posted done message
		}
		else if (arg->spec->mode == Dz1InetFtpDTPMode_compressed)
		{	// previously posted done message
		}
		break;
	}

}

static void Dz1InetFtpRXDTP_cleanup(void *ptr)
{
	Dz1InetFtpRXDTPEnv *env = (Dz1InetFtpRXDTPEnv *)ptr;
	Dz1InetFtpRXDTPEnv_del(env);
}

static u32_t Dz1InetFtpRXDTP_start(void *tParent, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock,
						  Dz1InetFtpDTPSpec *spec, Dz1InetFtpTransfer *job, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	u32_t ret = -1;
	Dz1InetFtpRXDTPArg *arg = Dz1InetFtpRXDTPArg_new(tParent, spec, job, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpRXDTPArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1TcpSocketReceiver_start(peer, local, 4096, 30000, &sock, FALSE,
											Dz1InetFtpRXDTP_init,
											Dz1InetFtpRXDTP_forward,
											Dz1InetFtpRXDTP_exception,
											NULL,
											Dz1InetFtpRXDTP_cleanup,
											(void **)&arg, (Dz1DelFunc)Dz1InetFtpRXDTPArg_del, errp)) == -1) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1InetFtpRXDTPArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

static Dz1Error Dz1InetFtpTXDTP_buffer(void *tFTP, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock, Dz1Binary *buf)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	size_t size = buf->size;
	u8_t *cp = buf->data;
	ssize_t sendByte;
	size_t sent = 0;
	struct timeval to = { DZ1_FTP_TRX_TIMEOUT_SEC, 0 };
	while(err.code == 0 && size)
	{
		to.tv_sec = 3; to.tv_usec = 0;
		if (sock->wait(sock, Dz1SocketWaitFlag_exceptout, &to, &err) <= 0) ERR_OUT(&err);
		else if ((sendByte = sock->send(sock, cp, size, 0, &to, &err)) < 0) ERR_OUT(&err);
		else if (sendByte == 0) ERR_SET_OUT(&err, EPIPE);
		else
		{
			cp += sendByte;
			size -= sendByte;
			sent += sendByte;
			if ((err = _postPktInform(tFTP, peer, local, sent)).code) ERR_OUT(&err);
		}
	}
	Dz1Thread_printf("Dz1InetFtpTXDTP_buffer() : Sent %u Bytes\n", (u32_t)(cp - buf->data));
	return err;
}

static Dz1Error Dz1InetFtpTXDTP_file(void *tFTP, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock, Dz1InetFtpFileName *file)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	FILE *fp = NULL;
	ssize_t sent = 0;
	char fn[4096] = { 0, };
	if (file->path != NULL) sprintf(fn, "%s" DIR_SEPRATOR "%s", file->path, file->name);
	else sprintf(fn, "%s", file->name);
	
	if ((fp = fopen(fn, "rb")) == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		u8_t buf[4096];
		size_t jobByte;
		ssize_t sendByte;
		struct timeval to;
		int status;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		while(err.code == 0)
		{
			to.tv_sec = DZ1_FTP_TRX_TIMEOUT_SEC; to.tv_usec = 0;
			if ((jobByte = fread(buf, sizeof(u8_t), 4096, fp)) == 0)
			{
				if (feof(fp)) break;
				else if ((status = ferror(fp)) != 0) ERR_SET_OUT(&err, status);
				else ERR_SET_OUT(&err, EFAULT);
			}
			else if ((sendByte = sock->send(sock, buf, jobByte, DZ1_TCP_SOCK_FLAG_COMPLETE, &to, &err)) < 0) ERR_OUT(&err);
			else
			{
				sent += sendByte;
				if ((err = _postPktInform(tFTP, peer, local, (size_t)sent)).code) ERR_OUT(&err);
			}
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	Dz1Thread_printf("Dz1InetFtpTXDTP_file() : Sent %u Bytes\n", sent);
	return err;
}

static Dz1Error Dz1InetFtpTXDTP_done(Dz1InetFtpTXDTPArg *arg, Dz1Error *status)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpMsgFileDone *msg = Dz1InetFtpMsgFileDone_new(arg->peer, arg->local, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		u32_t type;
		arg->peer = NULL;
		arg->local = NULL;
		pthread_cleanup_push(Dz1InetFtpMsgFileDone_delAndSetNull, (void *)&msg);

		switch(status->code)
		{
		case 0:
			type = DZ1_INET_FTP_DTP_TRANSFER_DONE;
			break;
		default:
			type = DZ1_INET_FTP_DTP_TRANSFER_FAIL;
			break;
		}
		if ((err = Dz1Task_post(arg->tFTP, DZ1_TASK_QUEUE_NONE, type, (void **)&msg,
								(Dz1DelFunc)Dz1InetFtpMsgFileDone_del,
								(Dz1DumpFunc)Dz1InetFtpMsgFileDone_dump,
								NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1InetFtpMsgFileDone_delAndSetNull, (void *)&msg);
	}
	return err;
}

static Dz1Error Dz1InetFtpTXDTP_thread(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1InetFtpTXDTPArg *arg = (Dz1InetFtpTXDTPArg *)ptr;
	Dz1TcpClientSocket *sock = arg->sock;
	Dz1InetFtpTransfer *job = arg->job;
	Dz1InetFtpFileInfo *fInfo = job->local;
	pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpTXDTPArg_del, (void *)arg);

#if 1
	switch(fInfo->present)
	{
	case Dz1InetFtpFileInfoPresent_buffer:
		if ((err = Dz1InetFtpTXDTP_buffer(arg->tFTP, arg->peer, arg->local, sock, fInfo->x.buffer)).code) ERR_OUT(&err);
		break;
	case Dz1InetFtpFileInfoPresent_file:
		if ((err = Dz1InetFtpTXDTP_file(arg->tFTP, arg->peer, arg->local, sock, fInfo->x.file)).code) ERR_OUT(&err);
		break;
	default:
		break;
	}
#else
	Dz1Error_set(&err, EPIPE);
#endif

	if ((err = Dz1InetFtpTXDTP_done(arg, &err)).code) ERR_OUT(&err);
	pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpTXDTPArg_del, (void *)arg);
	return err;
}

static u32_t Dz1InetFtpTXDTP_start(void *tParent, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock,
						  Dz1InetFtpDTPSpec *spec, Dz1InetFtpTransfer *job, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	u32_t ret = -1;
	Dz1InetFtpTXDTPArg *arg = Dz1InetFtpTXDTPArg_new(tParent, NULL, NULL, sock, spec, job, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpTXDTPArg_delAndSetNull, (void *)&arg);

		if ((arg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((arg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Thread_create(&ret, Dz1InetFtpTXDTP_thread, (void *)arg, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(errp);
		else arg = NULL;

		pthread_cleanup_pop(1); // (Dz1InetFtpTXDTPArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

u32_t Dz1InetFtpDTP_start(void *tParent, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock,
						  Dz1InetFtpDTPSpec *spec, Dz1InetFtpTransfer *job, Dz1Error *err)
{
	if (job->direction == Dz1InetFtpDirection_download)
		return Dz1InetFtpRXDTP_start(tParent, peer, local, sock, spec, job, err);
	else if (job->direction == Dz1InetFtpDirection_upload)
	{
		Dz1InetFtpFileInfo *local_file = job->local;
		if (local_file ->present == Dz1InetFtpFileInfoPresent_file)
		{
			Dz1InetFtpFileName *file = local_file ->x.file;
			file->size = (u32_t)(Dz1File_getSize2(file->path, file->name) & 0xFFFFFFFF);
		}
		return Dz1InetFtpTXDTP_start(tParent, peer, local, sock, spec, job, err);
	}
	else
	{
		Dz1Error _err, *errp = err ? err : &_err;
		ERR_SET_OUT(errp, EINVAL);
		return -1;
	}
}

void Dz1InetFtpDTP_stop(u32_t id)
{
	Dz1TcpSocketReceiver_stop(id);
}
