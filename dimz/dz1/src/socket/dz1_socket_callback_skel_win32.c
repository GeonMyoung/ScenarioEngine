#include <dz1_thread.h>
#include "../kernel/dz1_thread_stdio.h"
#include "dz1_socket_callback_skel.h"

#ifndef UNIX_SYSTEM

static u32_t _get_cpu_count(void)
{
	u32_t ret = 1;
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	ret = (u32_t)info.dwNumberOfProcessors;
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Win32 Callback Sub-System

static HANDLE cport2 = INVALID_HANDLE_VALUE;
static u32_t cport2_th[16] = { -1, };
//static pthread_mutex_t cport2_lock = PTHREAD_MUTEX_INITIALIZER;
static volatile bool_t worker2_stop = TRUE;

static void _take_down_worker2(void)
{
	int i;
	if (worker2_stop == FALSE)
	{
		worker2_stop = TRUE;
		for (i = 0; i < 16; i++)
		{
			if (cport2_th[i] != (u32_t)-1)
			{
				Dz1Thread_wait(cport2_th[i], NULL);
				cport2_th[i] = -1;
			}
		}
	}
}


static Dz1Error Dz1SocketCallback2_sys_worker(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	DWORD retLen = 0;
	ULONG_PTR identifier = 0;
	OVERLAPPED *ols = NULL;
	BOOL status = FALSE;
	
	while(err.code == 0 && worker2_stop == FALSE)
	{
		pthread_testcancel();
		status = GetQueuedCompletionStatus(cport2, &retLen, &identifier, &ols, 100);
		pthread_testcancel();

		// ols가 NULL인지 아닌지로 CPort Error와 Success를 구별한다.
		// +- ols가 NULL이면 CompletionPort에 문제가 생긴것.(TIMEOUT 포함)
		// +- ols가 NULL이 아니면, status를 가지고 성공한 IO인지 실패한 IO인지 구별한다.
		//    +- 실패한 IO는 IO가 일어나긴 했으나 error가 발생한 경우이다.
		//    |  +- 예를들어 상대방이 마지막 Data를 전송하고 소켓을 닫아버린 경우
		//    |  +- 마지막 Data를 수신하고 EOF를 받아 error가 발생한다.
		//    +- 성공한 IO는 error가 없이 IO를 완료한 경우이다.

		if (ols == NULL)
		{	// GetQueuedCompletionStatus 함수 수행 실패
			int code = GetLastError();
			if (code == WAIT_TIMEOUT) continue;
			else
			{
				Dz1Thread_eprintf("!!! Dz1TcpClientSocketCallback - System Fault = %d\n", code);
				ERR_SET_OUT(&err, code);
			}
		}
		else
		{	// GetQueuedCompletionStatus 함수 수행 성공
			int os_err_code = status == 0 ? GetLastError() : 0;	// status == 0 : IO 실패, status != 0 : IO 성공
			Dz1SocketCallback2Spec *spec = (Dz1SocketCallback2Spec *)identifier;

			if (ols == &spec->tx_ols)
			{
				if (Dz1SocketCallback2_skel_tx_complete(spec, retLen, os_err_code) == FALSE)
					spec->release(spec);
			}
			else if (ols == &spec->rx_ols)
			{
				if (Dz1SocketCallback2_skel_rx_complete(spec, retLen, os_err_code) == FALSE)
					spec->release(spec);
			}
		}
	}
	return err;
}

Dz1Error Dz1SocketCallback2_sys_init(void)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u32_t cpus = _get_cpu_count();
	u32_t numOfThread = (cpus << 1) > 16 ? 16 : (cpus << 1);

	if (cport2 == INVALID_HANDLE_VALUE)
	{
		Dz1Thread_eprintf("@@@ Working Thread = %u\n", numOfThread);
		if ((cport2 = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL) ERR_SET_OUT(&err, GetLastError());
		else
		{
			u32_t i;
			_take_down_worker2();
			worker2_stop = FALSE;
			for (i = 0; err.code == 0 && i < numOfThread; i++)
			{
				if ((err = Dz1Thread_create(&cport2_th[i], Dz1SocketCallback2_sys_worker, NULL, DZ1_THREAD_LOG_BASIS)).code)
					ERR_OUT(&err);
			}
		}
	}
	return err;
}

void Dz1SocketCallback2_sys_cleanup(void)
{
	_take_down_worker2();

	if (cport2 != INVALID_HANDLE_VALUE)
	{
		CloseHandle(cport2);
		cport2 = INVALID_HANDLE_VALUE;
	}
}
// Win32 Callback Sub-System
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Win32 Callback API
Dz1Error Dz1SocketCallback2_sys_reg(SOCKET s, Dz1SocketCallback2Spec *spec)
{	// s 를 completion port에 결합
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (CreateIoCompletionPort((HANDLE)s, cport2, (ULONG_PTR)spec, 0) == NULL) ERR_SET_OUT(&err, EFAULT);
	else if (Dz1SocketCallback2_sys_req_rx(spec, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

bool_t Dz1SocketCallback2_sys_req_tx(Dz1SocketCallback2Spec *spec, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);

	register int code = 0;
	DWORD retLen = 0;

	Dz1SocketCallback2Buffer *buf = spec->tx_buf;

	// WSASend의 lpNumberOfBytesSent에 NULL을 넣으면 Exception이 뜬다.(그렇다고 프로그램이 멈추진 않는다)
	//if (WSASend(scb->s, &scb->tx_ptr, 1, NULL, 0, &scb->tx_osh, NULL) == 0)
	if (WSASend(spec->fd, &buf->io_ptr, 1, &retLen, 0, &spec->tx_ols, NULL) == 0)
	{	// 바로 끝남. -> 완료 통지 받겠지?
		spec->ref_cnt++;
		Dz1Error_set(errp, 0);
		ret = TRUE;
	}
	else if (WSA_IO_PENDING == (code = GetLastError()))
	{	// IO 걸었음. -> 완료통지 대기
		spec->ref_cnt++;
		Dz1Error_set(errp, 0);
		ret = TRUE;
	}
	else
	{
		ERR_SET_OUT(errp, code);
	}
	return ret;
}

bool_t Dz1SocketCallback2_sys_req_rx(Dz1SocketCallback2Spec *spec, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);

	register int code = 0;
	DWORD flag = 0;

	Dz1SocketCallback2Buffer *buf = spec->rx_buf;

	if (WSARecv(spec->fd, &buf->io_ptr, 1, NULL, &flag, &spec->rx_ols, NULL) == 0)
	{	// 바로 끝남. -> 완료 통지 받겠지?
		spec->ref_cnt++;
		Dz1Error_set(errp, 0);
		ret = TRUE;
	}
	else if ((code = WSAGetLastError()) == WSA_IO_PENDING)
	{	// IO 걸었음. -> 완료통지 대기
		spec->ref_cnt++;
		Dz1Error_set(errp, 0);
		ret = TRUE;
	}
	else
	{
		ERR_SET_OUT(errp, code);
	}
	return ret;
}
// Win32 Callback API
///////////////////////////////////////////////////////////////////////////////
#else

#endif
