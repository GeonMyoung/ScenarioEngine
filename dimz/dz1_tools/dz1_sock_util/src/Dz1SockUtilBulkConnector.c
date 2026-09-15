#include <dz1_socket_connector.h>

#include "Dz1SockUtilData.h"
#include "Dz1SockUtilBulkConnector.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectReqeust API
Dz1SockUtilBulkConnectReqeust *Dz1SockUtilBulkConnectReqeust_new(Dz1SockAddr *peer, u32_t period, bool_t wait_and_connect,
																 void *userData, Dz1DelFunc userDataDel,
																 Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SockUtilBulkConnectReqeust *ret = (Dz1SockUtilBulkConnectReqeust *)Dz1Calloc(sizeof(Dz1SockUtilBulkConnectReqeust), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectReqeust_delAndSetNull, (void *)&ret);
		if ((ret->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->period = period;
			ret->wait_and_connect = wait_and_connect;
			ret->userData = userData;
			ret->isCanceled = FALSE;
			ret->userDataDel = userDataDel;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SockUtilBulkConnectReqeust_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SockUtilBulkConnectReqeust_del(Dz1SockUtilBulkConnectReqeust *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_delAndSetNull(&p->peer);
	if (p->userDataDel != NULL) p->userDataDel(p->userData);
	p->userData = NULL;
	Dz1Free(p);
}

void Dz1SockUtilBulkConnectReqeustA_dump(Dz1SockUtilBulkConnectReqeust *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("peer = "); Dz1SockAddrA_dump(p->peer, tab);
		Dz1ThreadA_printf("period = %u\n", p->period);
		Dz1ThreadA_printf("userData = %p(%p)\n", p->userData, p->userDataDel);
	}
}
#ifndef UNIX_SYSTEM
void Dz1SockUtilBulkConnectReqeustW_dump(Dz1SockUtilBulkConnectReqeust *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"peer = "); Dz1SockAddrW_dump(p->peer, tab);
		Dz1ThreadW_printf(L"period = %u\n", p->period);
		Dz1ThreadW_printf(L"userData = %p(%p)\n", p->userData, p->userDataDel);
	}
}
#endif
int Dz1SockUtilBulkConnectReqeust_cmp(Dz1SockUtilBulkConnectReqeust *a, Dz1SockUtilBulkConnectReqeust *b)
{
	if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else return Dz1SockAddr_cmp(a->peer, b->peer);
}
// Dz1SockUtilBulkConnectReqeust API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilBulkConnectReqeustFifo API
static Dz1Error Dz1SockUtilBulkConnectReqeustFifo_push(Dz1SockUtilBulkConnectReqeustFifo *fifo, Dz1SockUtilBulkConnectReqeust *req)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if ((err = fifo->add(fifo, req)).code) ERR_OUT(errp);

	return err;
}

static Dz1SockUtilBulkConnectReqeust *Dz1SockUtilBulkConnectReqeustFifo_pop(Dz1SockUtilBulkConnectReqeustFifo *fifo)
{
	Dz1SockUtilBulkConnectReqeust *ret = NULL;

	ret = fifo->extract(fifo, NULL);

	return ret;
}
// Dz1SockUtilBulkConnectReqeustFifo API
///////////////////////////////////////////////////////////////////////////////

static void Dz1SockUtilBulkConnectingEntry_cleanup(Dz1SockUtilBulkConnectingEntry *p)
{
	Dz1TcpSocketConnectorThread_join(p->thid);
	p->thid = -1;
}

static void Dz1SockUtilBulkConnector_callback(void *ptr, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket **s, Dz1Error *reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(ptr);
	Dz1SockUtilBulkConnectMsg *msg = Dz1SockUtilBulkConnectMsg_new(NULL, (*s), NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		(*s) = NULL;
		pthread_cleanup_push((Dz1CancelFunc)Dz1SockUtilBulkConnectMsg_delAndSetNull, (void *)&msg);

		if (peer != NULL && (msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if (local != NULL && (msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((err = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE,
									DZ1_SOCK_UTIL_CONNECTOR_RESULT, (void **)&msg,
									(Dz1DelFunc)Dz1SockUtilBulkConnectMsg_del,
									(Dz1DumpFunc)Dz1SockUtilBulkConnectMsg_dump,
									reason, NULL, NULL)).code) ERR_OUT(errp);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1SockUtilBulkConnectMsg_delAndSetNull, (void *)&msg);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Message Handler
static void Dz1SockUtilBulkConnector_start(Dz1SockUtilBulkConnectEnv *env, u32_t myQueueID);
Dz1SockUtilBulkConnectResult *Dz1SockUtilBulkConnector_msgProc(Dz1SockUtilBulkConnector *p, u32_t myQueueID,
															   Dz1TaskSigMsg *sg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SockUtilBulkConnectResult *ret = NULL;

	Dz1SockUtilBulkConnectEnv *env = (Dz1SockUtilBulkConnectEnv *)p;

	Dz1SockUtilBulkConnectMsg *msg = (Dz1SockUtilBulkConnectMsg *)Dz1TaskSigMsg_getData(sg);

	// connectingList에서 뽑아냄
	Dz1SockUtilBulkConnectReqeust rKey = { msg->peer }, *req = NULL;
	Dz1SockUtilBulkConnectingEntry key = { &rKey }, *node = env->connectingList->extract(env->connectingList, &key);

	Dz1Thread_printf("Dz1SockUtilBulkConnector_msgProc() : Result = "); Dz1SockUtilBulkConnectMsg_dump(msg, 0);

	if (node != NULL)
	{	// 아직 요청자가 요청을 취소하지 않았음. 즉 유효한 접속요청
		pthread_cleanup_push(Dz1SockUtilBulkConnectingEntry_delAndSetNull, (void *)&node);

		// suspend중인 Connector Thread 정리
		Dz1SockUtilBulkConnectingEntry_cleanup(node);

		if (msg->sock == NULL)
		{	// connect failed : push to request queue
			if ((*errp = Dz1SockUtilBulkConnectReqeustFifo_push(env->requestFifo, node->req)).code) ERR_OUT(errp);
		}
		else
		{	// connect success : extract origin request from request list
			req = env->index->extract(env->index, &rKey);
			pthread_cleanup_push(Dz1SockUtilBulkConnectReqeust_delAndSetNull, (void *)&req);

			if ((ret = Dz1SockUtilBulkConnectResult_new(msg->peer, msg->local, msg->sock, req->userData, errp)) == NULL) ERR_OUT(errp);
			else
			{
				msg->peer = msg->local = NULL;
				msg->sock = NULL;
				req->userData = NULL;
			}

			pthread_cleanup_pop(1); // (Dz1SockUtilBulkConnectReqeust_delAndSetNull, (void*)&req);
		}
		pthread_cleanup_pop(1); // (Dz1SockUtilBulkConnectingEntry_delAndSetNull, (void *)&node);
	}
	Dz1SockUtilBulkConnector_start(env, myQueueID);

	return ret;
}
// Message Handler
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Connector Thread Starter
typedef struct ListAddCancelArg
{
	Dz1SockUtilBulkConnectingList *list;
	Dz1SockUtilBulkConnectingEntry *node;
} ListAddCancelArg;

static void ListAddCancel(void *ptr)
{
	ListAddCancelArg *arg = (ListAddCancelArg *)ptr;
	arg->list->extract(arg->list, arg->node);
}

static Dz1Error _Dz1SockUtilBulkConnector_start(Dz1SockUtilBulkConnectEnv *env, Dz1SockUtilBulkConnectReqeust *req, u32_t myQueueID)
{	// 정상 요청에 대한 처리
	void *_MyQueueID = (void *)DZ1_VAL2PTR32(myQueueID);
	Dz1SockUtilBulkConnectingEntry *node = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	// Request를 reference로 하여 node 생성
	if ((node = Dz1SockUtilBulkConnectingEntry_new(req, -1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilBulkConnectingEntry_delAndSetNull, (void *)&node);
		// 연결중인 리스트에 삽입
		if ((err = env->connectingList->add(env->connectingList, node)).code) ERR_OUT(errp);
		else
		{
			ListAddCancelArg arg = { env->connectingList, node };
			pthread_cleanup_push(ListAddCancel, (void *)&arg);
			// 쓰레드 시작
			if ((node->thid = Dz1TcpSocketConnectorThread_create(req->peer, req->period, -1, req->wait_and_connect,
																 Dz1SockUtilBulkConnector_callback, _MyQueueID, 
																 DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_MESSAGE, errp)) == -1) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				node = NULL;
			}
			pthread_cleanup_pop(errp->code); // (ListAddCancel, (void *)&arg);
		}
		pthread_cleanup_pop(1); // (Dz1SockUtilBulkConnectingEntry_delAndSetNull (void *)&node);
	}
	return err;
}
// Connector Thread Starter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Connect Request
typedef struct FifoPopCancelArg
{
	Dz1SockUtilBulkConnectReqeustFifo *fifo;
	Dz1SockUtilBulkConnectReqeust *req;
} FifoPopCancelArg;

static void FifoPopCancel(void *ptr)
{
	FifoPopCancelArg *arg = (FifoPopCancelArg *)ptr;
	Dz1SockUtilBulkConnectReqeustFifo_push(arg->fifo, arg->req);
}

static void Dz1SockUtilBulkConnector_start(Dz1SockUtilBulkConnectEnv *env, u32_t myQueueID)
{
	Dz1SockUtilBulkConnectReqeust *req = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	u32_t cnt = env->connectingList->count(env->connectingList);
	Dz1Thread_printf("Dz1SockUtilBulkConnector_start() : before cnt = %u, conc = %u\n", cnt, env->maxConcurrency);

	while(env->connectingList->count(env->connectingList) < env->maxConcurrency)
	{	// 연결중인 작업 개수가 최대 병렬 요청 개수보다 작은만큼 반복
		Dz1Thread_printf("Dz1SockUtilBulkConnector_start() : before cnt = %u\n", cnt);
		if ((req = Dz1SockUtilBulkConnectReqeustFifo_pop(env->requestFifo)) == NULL) break;	// 없으면 끝
		else
		{
			FifoPopCancelArg arg = { env->requestFifo, req };
			pthread_cleanup_push(FifoPopCancel, (void *)&arg);								// 실패 시 Request 원복
			if (req->isCanceled == TRUE)
			{	// 취소된 요청 -> index에서 제거
				env->index->extract(env->index, req);
				Dz1SockUtilBulkConnectReqeust_delAndSetNull(&req);
			}
			else if ((err = _Dz1SockUtilBulkConnector_start(env, req, myQueueID)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (FifoPopCancel, (void *)&arg);
		}
	}
}
// Connect Request
///////////////////////////////////////////////////////////////////////////////

typedef struct IndexAddCancelArg
{
	Dz1SockUtilBulkConnectReqeustIndex *index;
	Dz1SockUtilBulkConnectReqeust *req;
} IndexAddCancelArg;

static void IndexAddCancel(void *ptr)
{
	IndexAddCancelArg *arg = (IndexAddCancelArg *)ptr;
	arg->index->extract(arg->index, arg->req);
}

static Dz1Error _request_add(Dz1SockUtilBulkConnectEnv *env, Dz1SockAddr *peer,
							 u32_t period, bool_t wait_and_connect,
							 void **userData, Dz1DelFunc userDataDel)
{	// request index와 request fifo에 Request Entry를 삽입한다.
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1SockUtilBulkConnectReqeust *req = Dz1SockUtilBulkConnectReqeust_new(peer, period, wait_and_connect,
																	userData == NULL ? NULL : *userData,
																	userDataDel, errp);
	if (req == NULL) ERR_OUT(errp);
	else
	{
		if (userData != NULL) (*userData) = NULL;
		pthread_cleanup_push(Dz1SockUtilBulkConnectReqeust_delAndSetNull, (void *)&req);
		if ((err = env->index->add(env->index, req)).code) ERR_OUT(&err);
		else
		{
			IndexAddCancelArg arg = { env->index, req };
			pthread_cleanup_push(IndexAddCancel, &arg);
			if ((err = Dz1SockUtilBulkConnectReqeustFifo_push(env->requestFifo, req)).code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(&err, 0);
				req = NULL;
			}
			pthread_cleanup_pop(err.code); // (_addCancel, &arg);
		}
		pthread_cleanup_pop(1); // (Dz1SockUtilBulkConnectReqeust_delAndSetNull, (void *)&req);
	}
	return err;
}

Dz1Error Dz1SockUtilBulkConnector_request(Dz1SockUtilBulkConnector *p, u32_t myQueueID, Dz1SockAddr *peer,
										  u32_t period, bool_t wait_and_connect,
										  void **userData, Dz1DelFunc userDataDel)
{
	Dz1SockUtilBulkConnectEnv *env = (Dz1SockUtilBulkConnectEnv *)p;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	//void *_myQueueID = (void *)DZ1_VAL2PTR32(myQueueID);

	if ((err = _request_add(env, peer, period, wait_and_connect, userData, userDataDel)).code) ERR_OUT(errp);

	Dz1SockUtilBulkConnector_start(env, myQueueID);

	return err;
}

void Dz1SockUtilBulkConnector_cancel(Dz1SockUtilBulkConnector *p, Dz1SockAddr *peer, u32_t myQueueID)
{
	Dz1SockUtilBulkConnectEnv *env = (Dz1SockUtilBulkConnectEnv *)p;
	// 일단 연결중 List에서 뽑아냄
	Dz1SockUtilBulkConnectReqeust rKey = { peer };
	Dz1SockUtilBulkConnectingEntry key = { &rKey }, *node = env->connectingList->extract(env->connectingList, &key);

	if (node != NULL)
	{	// 취소하는 요청이 연결중이었다 -> Requesting 삭제, index 삭제
		pthread_cleanup_push(Dz1SockUtilBulkConnectingEntry_delAndSetNull, (void *)&node);

		// Connector Thread정리
		Dz1SockUtilBulkConnectingEntry_cleanup(node);
		node->req->isCanceled = TRUE;

		env->index->remove(env->index, node->req);
		node->req = NULL;

		pthread_cleanup_pop(1); // (Dz1SockUtilBulkConnectingEntry_delAndSetNull, (void *)&node);

		// 하나 날라갔으니 추가요~
		Dz1SockUtilBulkConnector_start(env, myQueueID);
	}
	else
	{	// 아직 대기중인 연결요청 -> Fifo 삭제, index 삭제
		Dz1SockUtilBulkConnectReqeust *req = env->index->extract(env->index, &rKey);
		if (req != NULL)
		{	// 찾음
			pthread_cleanup_push(Dz1SockUtilBulkConnectReqeust_delAndSetNull, (void *)&req);
			req->isCanceled = TRUE;
			env->requestFifo->extract(env->requestFifo, req);
			pthread_cleanup_pop(1); // (Dz1SockUtilBulkConnectReqeust_delAndSetNull, (void *)&req);
		}
	}
}

Dz1SockUtilBulkConnector *Dz1SockUtilBulkConnector_new(u8_t maxConcurrency, Dz1Error *err)
{
	return Dz1SockUtilBulkConnectEnv_new(maxConcurrency, err);
}

static Dz1Error _connectorStop(Dz1SockUtilBulkConnector *ptr, Dz1SockUtilBulkConnectingEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p->thid != -1) Dz1TcpSocketConnectorThread_stop(p->thid);
	p->thid = -1;
	return err;
}

void Dz1SockUtilBulkConnector_del(Dz1SockUtilBulkConnector *p)
{
	Dz1SockUtilBulkConnectEnv *env = (Dz1SockUtilBulkConnectEnv *)p;
	env->connectingList->travel(env->connectingList, _connectorStop, NULL);
	Dz1SockUtilBulkConnectEnv_del(env);
}

void Dz1SockUtilBulkConnector_dump(Dz1SockUtilBulkConnector *p, int tab)
{
	Dz1SockUtilBulkConnectEnv *env = (Dz1SockUtilBulkConnectEnv *)p;
	Dz1SockUtilBulkConnectEnv_dump(env, tab);
}
