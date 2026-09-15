#include <errno.h>
#include <pthread.h>
#if defined(LINUX)||defined(SUN)||defined(HPUX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

#include "hae_output.h"
#include "hae_input.h"
#include "hae_misc.h"
#include "hae_inet.h"
#include "hae_inet_telnet.h"
#include "hae_local_sig_msg.h"
#include "hae_local_msg_queue.h"
#include "hae_local_memory.h"
#include "hae_local_liner_buf.h"
#include "hae_input_remote.h"


static int haeConsoleRemote_read(void *ptr, char *buf, u32_t size, int *err)
{
	HaeLocalLinerBuf *b = (HaeLocalLinerBuf *)ptr;

	int ret = 0;
	ret = b->pop(b, (u8_t *)buf, (int)size);
	if (ret == 0)
	{
		if (err) *err = EOF;
		ret = -1;
	}
	return ret;
}

static void haeInputRemote_cancel(void *p) { haeInput_del((HaeInput *)p); }

static int established = FALSE;

static void establish_cancel(void *p) { established = FALSE; }

///////////////////////////////////////////////////////////////////////////////
// Receiver Argument Structure
///////////////////////////////////////////////////////////////////////////////
typedef struct HaeInputRemoteReceiverArg
{
	SOCKET fd;
	HaeLocalLinerBuf *buf;
	u32_t controller_queue_id;
} HaeInputRemoteReceiverArg;

static HaeInputRemoteReceiverArg *haeInputRemoteReceiverArg_create(SOCKET fd, HaeLocalLinerBuf *buf, u32_t controller_queue_id)
{
	HaeInputRemoteReceiverArg *ret = (HaeInputRemoteReceiverArg *)malloc(sizeof(HaeInputRemoteReceiverArg));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeInputRemoteReceiverArg_create() : Memory allocation error\n");
		exit(1);
	}
	ret->fd = fd;
	ret->buf = buf;
	ret->controller_queue_id = controller_queue_id;
	return ret;
}

static void haeInputRemoteReceiverArg_del(HaeInputRemoteReceiverArg *p)
{
	if (!p) return;
	free(p);
}

static void haeInputRemoteReceiverArg_cancel(void *p) { haeInputRemoteReceiverArg_del((HaeInputRemoteReceiverArg *)p); }

///////////////////////////////////////////////////////////////////////////////
// Handler Argument Structure
///////////////////////////////////////////////////////////////////////////////
typedef struct HaeInputRemoteHandlerArg
{
	int (*input_handler)(HaeInput *haeInput, void *p);
	HaeInput *haeInput;
	void *param;
	u32_t controller_queue_id;
} HaeInputRemoteHandlerArg;

static HaeInputRemoteHandlerArg *haeInputRemoteHandlerArg_create(int (*input_handler)(HaeInput *haeInput, void *p),
																 HaeInput *haeInput, void *param, u32_t controller_queue_id)
{
	HaeInputRemoteHandlerArg *ret = (HaeInputRemoteHandlerArg *)malloc(sizeof(HaeInputRemoteHandlerArg));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeInputRemoteHandlerArg_create() : Memory allocation error\n");
		exit(1);
	}
	ret->input_handler = input_handler;
	ret->haeInput = haeInput;
	ret->param = param;
	ret->controller_queue_id = controller_queue_id;
	return ret;
}

static void haeInputRemoteHandlerArg_del(HaeInputRemoteHandlerArg *p)
{
	if (!p) return;
	free(p);
}

static void haeInputRemoteHandlerArg_cancel(void *p) { haeInputRemoteHandlerArg_del((HaeInputRemoteHandlerArg *)p); }

typedef struct HaeInputRemoteControllerArg
{
	SOCKET fd;
	u32_t bufferSize;
	int (*input_handler)(HaeInput *haeInput, void *p);
	void *param;
} HaeInputRemoteControllerArg;

static HaeInputRemoteControllerArg *haeInputRemoteControllerArg_create(SOCKET fd, u32_t bufferSize,
																		int (*input_handler)(HaeInput *haeInput, void *p),
																		void *param)
{
	HaeInputRemoteControllerArg *ret = (HaeInputRemoteControllerArg *)malloc(sizeof(HaeInputRemoteControllerArg));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeInputRemoteControllerArg_create() : Memory allocation error\n");
		exit(1);
	}
	ret->fd = fd;
	ret->bufferSize = bufferSize;
	ret->input_handler = input_handler;
	ret->param = param;
	return ret;
}

static void haeInputRemoteControllerArg_del(HaeInputRemoteControllerArg *p)
{
	if (!p) return;
	free(p);
}

static void haeInputRemoteControllerArg_cancel(void *p) { haeInputRemoteControllerArg_del((HaeInputRemoteControllerArg *)p); }

///////////////////////////////////////////////////////////////////////////////
// Handler
///////////////////////////////////////////////////////////////////////////////
static void haeInputRemote_handler_inform_down(void *arg)
{
	int err = 0;
	HaeInputRemoteHandlerArg *p = (HaeInputRemoteHandlerArg *)arg;
	HaeLocalSigMsg *sg = haeLocalSigMsg_create(HAE_INPUT_REMOTE_HANDLER_DOWN, -1, -1, NULL, NULL, NULL);
	HaeOut->fprintf(stdout, 0, "haeInputRemote_handler_inform_down() : Called\n");
	if ((err = haeLocalSigMsg_post(p->controller_queue_id, sg)))
	{
		HaeOut->fprintf(stdout, 0, "haeInputRemote_handler_inform_down() : Post = %s(%d)\n", strerror(err), err);
		haeLocalSigMsg_del(sg);
	}
	haeInputRemoteHandlerArg_cancel(p);
}

static void *haeInputRemote_handler(void *arg)
{
	HaeInputRemoteHandlerArg *p = (HaeInputRemoteHandlerArg *)arg;

	pthread_cleanup_push(haeInputRemote_handler_inform_down, (void *)p);

	while(p->input_handler(p->haeInput, p->param));
	
	pthread_cleanup_pop(1); // (haeInputRemote_handler_inform_down, (void *)p);

	pthread_exit(NULL);
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Receiver
///////////////////////////////////////////////////////////////////////////////
static void haeInputRemote_receiver_inform_down(void *arg)
{
	int err = 0;
	HaeInputRemoteReceiverArg *p = (HaeInputRemoteReceiverArg *)arg;
	HaeLocalSigMsg *sg = haeLocalSigMsg_create(HAE_INPUT_REMOTE_RECEIVER_DOWN, -1, -1, NULL, NULL, NULL);
	HaeOut->fprintf(stdout, 0, "haeInputRemote_receiver_inform_down() : Called\n");
	if ((err = haeLocalSigMsg_post(p->controller_queue_id, sg)))
	{
		HaeOut->fprintf(stdout, 0, "haeInputRemote_receiver_inform_down() : Post = %s(%d)\n", strerror(err), err);
		haeLocalSigMsg_del(sg);
	}
	haeInputRemoteReceiverArg_cancel(p);
}

static void haeInputRemote_receiver_inform_up(HaeInputRemoteReceiverArg *p)
{
	int err = 0;
	HaeLocalSigMsg *sg = haeLocalSigMsg_create(HAE_INPUT_REMOTE_RECEIVER_UP, -1, -1, NULL, NULL, NULL);
	if ((err = haeLocalSigMsg_post(p->controller_queue_id, sg)))
	{
		HaeOut->fprintf(stdout, 0, "haeInputRemote_receiver_inform_up() : Post = %s(%d)\n", strerror(err), err);
		haeLocalSigMsg_del(sg);
	}
}

static int haeInputRemote_receiver_nego(HaeInetTelnetHandle *h, SOCKET fd)
{
	int err = 0;
	int read_byte;
	u8_t buf[1024];

	h->set_i_do(h, fd, TELOPT_SGA);
	h->set_i_do(h, fd, TELOPT_ECHO);
	h->set_he_do(h, fd, TELOPT_NAWS);
	do
	{
		read_byte = hae_inet_telnet_recv(h, fd, (char *)buf, 1024, &err);
		if (read_byte)
			HaeOut->fprintf(stdout, 0, "haeInputRemote_receiver_nego() : %d byte discard\n", read_byte);
		else 
		{
			if (err) 
			{
				HaeOut->fprintf(stdout, 0, "haeInputRemote_receiver_nego() : err = %s(%d)\n", strerror(err), err);
				return err;
			}
		}
	} while(!h->is_all_clean(h));
	return 0;
}

static int haeInputRemote_receiver_lv1(HaeInetTelnetHandle *h, HaeInputRemoteReceiverArg *p, HaeLocalLinerBuf *b)
{
	int err = 0;

	pthread_cleanup_push(haeInetTelnetHandle_cancel, h);

	if ((err = haeInputRemote_receiver_nego(h, p->fd)))
		HaeOut->fprintf(stdout, 0, "haeInputRemote_receiver() : Telnet Negotation = %s(%d)\n", strerror(err), err);
	else
	{
		char buf[4096];
		int read_byte, push_byte;

		haeInputRemote_receiver_inform_up(p);

		while(1)
		{
			if ((read_byte = hae_inet_telnet_recv(h, p->fd, buf, 4096, &err)) > 0)
			{
				if ((push_byte = b->push(b, (u8_t *)buf, read_byte)) != read_byte)
					HaeOut->fprintf(stdout, 0, "haeInputRemote_receiver() : %u %u : byte discardded\n", read_byte, push_byte);
			}
			else if (read_byte == 0)
			{
				if (err)
				{
					HaeOut->fprintf(stdout, 0, "haeInputRemote_receiver() : %s(%d)\n", strerror(err), err);
					break;
				}
			}
			else
			{
				if (err != ETIMEDOUT)
				{
					HaeOut->fprintf(stdout, 0, "haeInputRemote_receiver() : recv = %s(%d)\n", strerror(err), err);
					break;
				}
			}

		}
	}

	pthread_cleanup_pop(1); // (haeTelnet_cancel, h);
	return err;
}

static void *haeInputRemote_receiver(void *arg)
{
	int err = 0;

	HaeInputRemoteReceiverArg *p = (HaeInputRemoteReceiverArg *)arg;
	HaeLocalLinerBuf *b = p->buf;

	HaeInetTelnetHandle *h = NULL;

	pthread_cleanup_push(haeInputRemote_receiver_inform_down, (void *)arg);

	h = haeInetTelnetHandle_create();

	err = haeInputRemote_receiver_lv1(h, p, b);

	pthread_cleanup_pop(1); // (haeInputRemote_receiver_inform_down, (void *)arg);

	pthread_exit(NULL);
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Controller
///////////////////////////////////////////////////////////////////////////////
static void haeInputRemote_threadCancel(void *arg)
{
	int err = 0;
	pthread_t *th = (pthread_t *)arg;
	if ((err = pthread_cancel(*th)))
		HaeOut->fprintf(stdout, 0, "haeInputRemote_handlerCancel() : Stop = %s(%d)\n", strerror(err), err);
	else
		pthread_join(*th, NULL);
}

static void haeInputRemote_controller_fp_cancel(void *fp)
{
	HaeOut->fprintf(stdout, 0, "haeInputRemote_controller_fp_cancel() : Stream Close\n");
	fclose((FILE *)fp);
	HaeOut->change(NULL);
}

static int haeInputRemote_controller_pend_msg_proc(HaeInputRemoteControllerArg *p, u32_t queue_id, FILE *fp, HaeInput *haeInput,
																			int *alive, pthread_t *handler_th, HaeLocalSigMsg *sg)
{
	int err = 0;
	HaeInputRemoteHandlerArg *handlerArg = NULL;
	pthread_cleanup_push(haeLocalSigMsg_cancel, (void *)sg);
	switch(sg->type)
	{
		case HAE_INPUT_REMOTE_RECEIVER_UP:
			HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : Change fp = %p\n", fp);
			HaeOut->change(fp);
			HaeOut->setLF(HAE_OUTPUT_CRLF);
			if (!(handlerArg = haeInputRemoteHandlerArg_create(p->input_handler, (HaeInput *)haeInput, p->param, queue_id)))
			{
				HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : HaeInputRemoteHandlerArg Creation Fail\n");
				*alive = FALSE;
			}
			else
			{
				HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : Handler Start\n");
				if ((err = pthread_create(handler_th, NULL, haeInputRemote_handler, handlerArg)))
				{
					HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : Handler Start = %s(%d)\n", strerror(err), err);
					*alive = FALSE;
				}
			}
			break;
		case HAE_INPUT_REMOTE_RECEIVER_DOWN:
		case HAE_INPUT_REMOTE_HANDLER_DOWN:
			HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : Got Down Signal\n");
			*alive = FALSE;
			break;
		default:
			break;
	}
	pthread_cleanup_pop(1); // (haeLocalSigMsg_cancel, (void *)sg);
	return err;
}

static int _haeInputRemote_controller_loop(HaeInputRemoteControllerArg *p, u32_t queue_id, FILE *fp, HaeInput *haeInput)
{
	int err = 0;
	int alive = TRUE;
	pthread_t handler_th;
	struct timeval to = { 0, 100000 };
	HaeLocalSigMsg *sg = NULL;
	pthread_cleanup_push(haeInputRemote_threadCancel, (void *)&handler_th);

	while(alive)
	{
		if ((sg = haeLocalSigMsg_pend(queue_id, &to, &err)))
			err = haeInputRemote_controller_pend_msg_proc(p, queue_id, fp, haeInput, &alive, &handler_th, sg);
		else
		{
			if (err != ETIMEDOUT)
			{
				HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : Message Pend = %s(%d)\n", strerror(err), err);
				break;
			}
		}
	}

	pthread_cleanup_pop(1); // (haeInputRemote_handlerCancel, (void *)&handler_th);
	return err;
}
static int haeInputRemote_controller_loop(HaeInputRemoteControllerArg *p, u32_t queue_id, FILE *fp, HaeLocalLinerBuf *buf, HaeInput *haeInput)
{
	int err = 0;
	pthread_t receiver_th;
	HaeInputRemoteReceiverArg *receiverArg = NULL;
	if (!(receiverArg = haeInputRemoteReceiverArg_create(p->fd, buf, queue_id)))
	{
		err = ENOMEM;
		HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : HaeInputRemoteReceiverArg Creation Fail\n");
	}
	else
	{
		if ((err = pthread_create(&receiver_th, NULL, haeInputRemote_receiver, receiverArg)))
		{
			HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : Receiver Start = %s(%d)\n", strerror(err), err);
			haeInputRemoteReceiverArg_del(receiverArg);
		}
		else
		{
			pthread_cleanup_push(haeInputRemote_threadCancel, (void *)&receiver_th);
			err = _haeInputRemote_controller_loop(p, queue_id, fp, haeInput);
			pthread_cleanup_pop(1); // (haeInputRemote_receiverCancel, (void *)receiver_th);
		}
	}
	return err;
}

static int haeInputRemote_controller_input_area (HaeInputRemoteControllerArg *p, u32_t queue_id, FILE *fp, HaeLocalLinerBuf *buf, HaeInput *haeInput)
{
	int err = 0;
	pthread_cleanup_push(haeInputRemote_cancel, (void *)haeInput);
	err = haeInputRemote_controller_loop(p, queue_id, fp, buf, haeInput);
	pthread_cleanup_pop(1); // (haeInputRemote_cancel, (void *)haeInput);
	return err;
}

static int haeInputRemote_controller_establish_area(HaeInputRemoteControllerArg *p, u32_t queue_id, FILE *fp)
{
	int err = 0;
	HaeInput *haeInput = NULL;
	HaeLocalLinerBuf *buf = NULL;
	pthread_cleanup_push(establish_cancel, NULL);
	if (!(haeInput = haeInput_create(haeConsoleRemote_read, (buf = haeLocalLinerBuf_create(p->bufferSize, NULL)), 
					(HaeGeneralDelFunc)haeLocalLinerBuf_del, NULL)))
	{
		err = ENOMEM;
		HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : HaeInputRemote Create Fail\n");
	}
	else
		err = haeInputRemote_controller_input_area(p, queue_id, fp, buf, haeInput);
	pthread_cleanup_pop(1); // (establish_cancel, NULL);
	return err;
}

static int haeInputRemote_controller_stream_area(HaeInputRemoteControllerArg *p, u32_t queue_id)
{
	int err = 0;
	FILE *fp = NULL;
	if (!(fp = fdopen(p->fd, "w")))
	{
		err = errno;
		HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : fdopen = %s(%d)\n", strerror(errno), errno);
	}
	else
	{
		pthread_cleanup_push(haeInputRemote_controller_fp_cancel, (void *)fp);
		err = haeInputRemote_controller_establish_area(p, queue_id, fp);
		pthread_cleanup_pop(1); // (haeInputRemote_controller_fp_cancel, (void *)fp);
	}
	return err;
}

static int haeInputRemote_controller_msg_queue_area(HaeInputRemoteControllerArg *p)
{
	int err = 0;
	u32_t queue_id = haeLocalMsgQueue_new(1024, &err);
	if (err) HaeOut->fprintf(stdout, 0, "haeInputRemote_controller() : queue create = %s(%d)\n", strerror(err), err);
	else
	{
		pthread_cleanup_push(haeLocalMsgQueue_cancel, (void *)&queue_id);
		err = haeInputRemote_controller_stream_area(p, queue_id);
		pthread_cleanup_pop(1); // (haeLocalMsgQueue_cancel, (void *)&queue_id);
	}
	return err;
}

static void *haeInputRemote_controller(void *arg)
{
	int err = 0;
	HaeInputRemoteControllerArg *p = (HaeInputRemoteControllerArg *)arg;

	pthread_cleanup_push(haeInputRemoteControllerArg_cancel, (void *)p);

	err = haeInputRemote_controller_msg_queue_area(p);

	pthread_cleanup_pop(1); // (haeInputRemoteControllerArg_cancel, (void *)p);
	pthread_exit(NULL);

	return NULL;
}

static int haeInputRemote_start(pthread_t *th, SOCKET fd, u32_t bufferSize, int (*input_handler)(HaeInput *haeInput, void *p), void *p)
{
	int err = 0;
	HaeInputRemoteControllerArg *controller_arg = haeInputRemoteControllerArg_create(fd, bufferSize, input_handler, p);
	if ((err = pthread_create(th, NULL, haeInputRemote_controller, (void *)controller_arg)))
		HaeOut->fprintf(stdout, 0, "haeInputRemote_start() : Thread Start = %s(%d)\n", strerror(err), err);
	return err;
}

static void haeInputRemote_sendRejectMessage(SOCKET fd, struct sockaddr_in peer)
{
	char buf[1024];
	char ipAddr[16];
	sprintf(buf, "Remote Console Already Established from %s:%u\n",
			hae_inet_ip2str(ipAddr, hae_ntohl(peer.sin_addr.s_addr)), hae_ntohs(peer.sin_port));
	send(fd, buf, strlen(buf), 0);
}

// Telnet Session Accepter
void haeInputRemote_process(int (*input_handler)(HaeInput *haeInput, void *p), void *p, u16_t port)
{
	pthread_t th;
	int err;
	struct timeval to;

	SOCKET fd = INVALID_SOCKET;
	HaeOut->fprintf(stdout, 0, "haeInputRemote_process() : Start\n");
	fd = hae_inet_getServerStreamSocket(&port, &err);
	if (fd == INVALID_SOCKET)
	{
		HaeOut->fprintf(stdout, 0, "haeInputRemote_process() : Socket Initialize = %s(%d)\n", strerror(err), err);
		return;
	}
	else HaeOut->fprintf(stdout, 0, "haeInputRemote_process() : Listem %u\n", port);
	established = FALSE;
	while(1)
	{
		to.tv_sec = 0; to.tv_usec = 100000;
		if ((err = hae_inet_detectIncome(fd, &to))==0)
		{
			struct sockaddr_in peer, last;
			SOCKET nfd = INVALID_SOCKET;
			nfd = hae_inet_getServiceStreamSocket(fd, &peer, &err);
			if (nfd == INVALID_SOCKET)
				HaeOut->fprintf(stdout, 0, "haeInputRemote_process() : Accept = %s(%d)\n", strerror(err), err);
			else
			{
				if (established)
				{
					haeInputRemote_sendRejectMessage(nfd, last);
					closesocket(nfd);
					err = 0;
				}
				else
				{
					last = peer;
					established = (err = haeInputRemote_start(&th, nfd, 0x10000, input_handler, p)) == 0 ? TRUE : FALSE;
				}
			}
		}
		else if (err != ETIMEDOUT)
		{
			HaeOut->fprintf(stdout, 0, "haeInputRemote_process() : Socket Wait = %s(%d)\n", strerror(err), err);
			break;
		}
	}
}

