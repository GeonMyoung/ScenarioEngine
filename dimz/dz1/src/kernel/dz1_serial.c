#include <dz1_str.h>
#include <dz1_thread.h>
#include <dz1_usleep.h>
#include <dz1_malloc.h>

#include <dz1_serial.h>

#define DZ1_SERIAL_BUF_SIZE	0x1000 // 4096

typedef struct _InternalStrMapA_
{
	int							v;
	str_t						str;
} _InternalStrMapA_;

static str_t _internalStrMapA_unknown = (str_t)"unknown";

static str_t _InternalStrMapA_find(_InternalStrMapA_ *table, int stopValue, int src)
{
	_InternalStrMapA_ *i;
	for (i = table; i->v != stopValue; i++)
		if (i->v == src) return i->str;
	return _internalStrMapA_unknown;
}

static int _internalStrMapA_findVal(_InternalStrMapA_ *table, int stopValue, str_t str)
{
	_InternalStrMapA_ *i;
	for (i = table; i->v != stopValue; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return stopValue;
}
#ifndef UNIX_SYSTEM
typedef struct _InternalStrMapW_
{
	int							v;
	wstr_t						str;
} _InternalStrMapW_;

static wstr_t _internalStrMapW_unknown = L"unknown";

static wstr_t _InternalStrMapW_find(_InternalStrMapW_ *table, int stopValue, int src)
{
	_InternalStrMapW_ *i;
	for (i = table; i->v != stopValue; i++)
		if (i->v == src) return i->str;
	return _internalStrMapW_unknown;
}

static int _internalStrMapW_findVal(_InternalStrMapW_ *table, int stopValue, wstr_t str)
{
	_InternalStrMapW_ *i;
	for (i = table; i->v != stopValue; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return stopValue;
}
#endif // UNIX_SYSTEM

///////////////////////////////////////////////////////////////////////////////
// Dz1SerialParity
static _InternalStrMapA_ parityMapA[] =
{
	{ Dz1SerialParity_none, (str_t)"none" },
	{ Dz1SerialParity_even, (str_t)"even" },
	{ Dz1SerialParity_odd,  (str_t)"odd" },
	{ -1 }
};

str_t Dz1SerialParityStrA(Dz1SerialParity v)
{
	return _InternalStrMapA_find(parityMapA, -1, v);
}

Dz1SerialParity Dz1SerialParityFromStrA(str_t v)
{
	Dz1SerialParity ret = (Dz1SerialParity)_internalStrMapA_findVal(parityMapA, -1, v);
	return ret;
}
#ifndef UNIX_SYSTEM
static _InternalStrMapW_ parityMapW[] =
{
	{ Dz1SerialParity_none, (wstr_t)L"none" },
	{ Dz1SerialParity_even, (wstr_t)L"even" },
	{ Dz1SerialParity_odd,  (wstr_t)L"odd" },
	{ -1 }
};

wstr_t Dz1SerialParityStrW(Dz1SerialParity v)
{
	return _InternalStrMapW_find(parityMapW, -1, v);
}

Dz1SerialParity Dz1SerialParityFromStrW(wstr_t v)
{
	Dz1SerialParity ret = (Dz1SerialParity)_internalStrMapW_findVal(parityMapW, -1, v);
	return ret;
}
#endif
// Dz1SerialParity
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SerialStopBit
static _InternalStrMapA_ stopBitMapA[] =
{
	{ Dz1SerialStopBit_one, 	(str_t)"one" },
	{ Dz1SerialStopBit_oneHalf, (str_t)"oneHalf" },
	{ Dz1SerialStopBit_two, 	(str_t)"two" },
	{ -1 }
};

Dz1SerialStopBit Dz1SerialStopBitFromStrA(str_t v)
{
	Dz1SerialStopBit ret = (Dz1SerialStopBit)_internalStrMapA_findVal(stopBitMapA, -1, v);
	return ret;
}

str_t Dz1SerialStopBitStrA(Dz1SerialStopBit v)
{
	return _InternalStrMapA_find(stopBitMapA, -1, v);
}
#ifndef UNIX_SYSTEM
static _InternalStrMapW_ stopBitMapW[] =
{
	{ Dz1SerialStopBit_one, 	(wstr_t)L"one" },
	{ Dz1SerialStopBit_oneHalf, (wstr_t)L"oneHalf" },
	{ Dz1SerialStopBit_two, 	(wstr_t)L"two" },
	{ -1 }
};

Dz1SerialStopBit Dz1SerialStopBitFromStrW(wstr_t v)
{
	Dz1SerialStopBit ret = (Dz1SerialStopBit)_internalStrMapW_findVal(stopBitMapW, -1, v);
	return ret;
}

wstr_t Dz1SerialStopBitStrW(Dz1SerialStopBit v)
{
	return _InternalStrMapW_find(stopBitMapW, -1, v);
}
#endif
// Dz1SerialStopBit
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SerialRTSCTS
static _InternalStrMapA_ RtsCtsMapA[] =
{
	{ Dz1SerialRTSCTS_manual, 	(str_t)"off/manual" },
	{ Dz1SerialRTSCTS_on, 		(str_t)"on" },
	{ -1 }
};

str_t Dz1SerialRTSCTSStrA(Dz1SerialRTSCTS v)
{
	return _InternalStrMapA_find(RtsCtsMapA, -1, v);
}
#ifndef UNIX_SYSTEM
static _InternalStrMapW_ RtsCtsMapW[] =
{
	{ Dz1SerialRTSCTS_manual, 	(wstr_t)L"off/manual" },
	{ Dz1SerialRTSCTS_on, 		(wstr_t)L"on" },
	{ -1 }
};

wstr_t Dz1SerialRTSCTSStrW(Dz1SerialRTSCTS v)
{
	return _InternalStrMapW_find(RtsCtsMapW, -1, v);
}
#endif
// Dz1SerialRTSCTS
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SerialDSRDTR
static _InternalStrMapA_ DsrDtrMapA[] =
{
	{ Dz1SerialDSRDTR_manual, 	(str_t)"off/manual" },
	{ Dz1SerialDSRDTR_on, 		(str_t)"on" },
	{ -1 }
};

str_t Dz1SerialDSRDTRStrA(Dz1SerialDSRDTR v)
{
	return _InternalStrMapA_find(DsrDtrMapA, -1, v);
}
#ifndef UNIX_SYSTEM
static _InternalStrMapW_ DsrDtrMapW[] =
{
	{ Dz1SerialDSRDTR_manual, 	(wstr_t)L"off/manual" },
	{ Dz1SerialDSRDTR_on, 		(wstr_t)L"on" },
	{ -1 }
};

wstr_t Dz1SerialDSRDTRStrW(Dz1SerialDSRDTR v)
{
	return _InternalStrMapW_find(DsrDtrMapW, -1, v);
}
#endif
// Dz1SerialDSRDTR
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SerialXONXOFF
static _InternalStrMapA_ XonXoffMapA[] =
{
	{ Dz1SerialXONXOFF_off,	(str_t)"off" },
	{ Dz1SerialXONXOFF_on, 	(str_t)"on" },
	{ -1 }
};

str_t Dz1SerialXONXOFFStrA(Dz1SerialXONXOFF v)
{
	return _InternalStrMapA_find(XonXoffMapA, -1, v);
}

Dz1SerialXONXOFF Dz1SerialXONXOFFFromStrA(str_t v)
{
	Dz1SerialXONXOFF ret = (Dz1SerialXONXOFF)_internalStrMapA_findVal(XonXoffMapA, -1, v);
	return ret;
}
#ifndef UNIX_SYSTEM
static _InternalStrMapW_ XonXoffMapW[] =
{
	{ Dz1SerialXONXOFF_off,	(wstr_t)L"off" },
	{ Dz1SerialXONXOFF_on, 	(wstr_t)L"on" },
	{ -1 }
};

wstr_t Dz1SerialXONXOFFStrW(Dz1SerialXONXOFF v)
{
	return _InternalStrMapW_find(XonXoffMapW, -1, v);
}

Dz1SerialXONXOFF Dz1SerialXONXOFFFromStrW(wstr_t v)
{
	Dz1SerialXONXOFF ret = (Dz1SerialXONXOFF)_internalStrMapW_findVal(XonXoffMapW, -1, v);
	return ret;
}
#endif
// Dz1SerialXONXOFF
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SerialPinState
static _InternalStrMapA_ pinStateMapA[] =
{
	{ Dz1SerialPinState_low, 	(str_t)"low" },
	{ Dz1SerialPinState_high,	(str_t)"high" },
	{ -1 }
};

str_t Dz1SerialPinStateStrA(Dz1SerialPinState v)
{
	return _InternalStrMapA_find(pinStateMapA, -1, v);
}
#ifndef UNIX_SYSTEM
static _InternalStrMapW_ pinStateMapW[] =
{
	{ Dz1SerialPinState_low, 	(wstr_t)L"low" },
	{ Dz1SerialPinState_high,	(wstr_t)L"high" },
	{ -1 }
};

wstr_t Dz1SerialPinStateStrW(Dz1SerialPinState v)
{
	return _InternalStrMapW_find(pinStateMapW, -1, v);
}
#endif
// Dz1SerialPinState
///////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
typedef struct _Dz1Serial
{
	s32_t					 portNum;
	str_t					 name;

	HANDLE					 fd;

	u32_t					 idByte;
	u32_t					 idEvent;

	bool_t					 fullDuplex;

	DWORD					 mask;

	Dz1SerialPinState		 cts;
	Dz1SerialPinState		 dsr;

	DCB						 inittermios;

	OVERLAPPED				 ols_read;
	OVERLAPPED				 ols_write;
	OVERLAPPED				 ols_event;

	Dz1SerialByteConsume	 byteConsume;
	void					*byteConsumeParam;

	Dz1SerialPinChanged		 ringInd;
	void					*ringIndParam;

	Dz1SerialPinChanged		 ctsChanged;
	void					*ctsChangedParam;

	Dz1SerialPinChanged		 dsrChanged;
	void					*dsrChangedParam;

	Dz1SerialException		 exception;
	void					*exceptionParam;

	pthread_mutex_t			 lock;
} _Dz1Serial;


static ssize_t _dz1Serial_rwWait(HANDLE h, OVERLAPPED *ols, Dz1Error *errp)
{
	unsigned long ret = 0;

	COMSTAT comstat;
	DWORD dwError, dwErrorFlag;

	while(1)
	{	// Check Received Data per 10 ms
		pthread_testcancel();
		ClearCommError(h, &dwErrorFlag, &comstat);
		if(GetOverlappedResult(h, ols, &ret, FALSE) == 0)
		{
			if ((dwError = GetLastError()) == 0)
			{
//				printf("(%d)\n", ret); fflush(stdout);
				break;				// Read Success
			}
			else if (dwError == ERROR_IO_INCOMPLETE)
			{
				ClearCommError(h, &dwErrorFlag, &comstat);
//				printf(".", ret); fflush(stdout);
				Dz1Thread_usleep(100000);	// Sleep 10 ms
			}
			else
			{	// Error
				ClearCommError(h, &dwErrorFlag, &comstat);
				ERR_SET_OUT(errp, dwError);
				ret = -1;
				break;
			}
		}
		else break;		// Don't need wait
	}
	return (ssize_t)ret;
}

static ssize_t _Dz1Serial_read(_Dz1Serial *p, u8_t *buf, size_t bufSize, Dz1Error *errp)
{
	unsigned long ret = 0;

	COMSTAT comstat;
	DWORD dwError, dwErrorFlag;

	ClearCommError(p->fd, &dwErrorFlag, &comstat);

//	printf("R");fflush(stdout);
	if (ReadFile(p->fd, buf, (DWORD)bufSize, &ret, &p->ols_read) == FALSE)
	{	// Error Occured
		if ((dwError = GetLastError()) == ERROR_IO_PENDING)
		{
			ssize_t sz;
//			ClearCommError(p->fd, &dwErrorFlag, &comstat);
//			printf("(%d)", ret); fflush(stdout);
			if ((sz = _dz1Serial_rwWait(p->fd, &p->ols_read, errp)) < 0) ERR_OUT(errp);
			else ret = (unsigned long)sz;
		}
		else
		{
			ClearCommError(p->fd, &dwErrorFlag, &comstat);
			ERR_SET_OUT(errp, EPIPE);
			ret = -1;
		}
	}
	return (ssize_t)ret;
}

static Dz1Error _Dz1Serial_waitEvent(HANDLE h, OVERLAPPED *ols, DWORD *mask)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	COMSTAT comstat;
	DWORD dwError, dwErrorFlag;

	unsigned long temp, cnt = 3;

	while(1)
	{	// Check Received Data per 10 ms
		pthread_testcancel();
		//printf("."); fflush(stdout);
		ClearCommError(h, &dwErrorFlag, &comstat);
		if(GetOverlappedResult(h, ols, &temp, FALSE) == 0)
		{
			if ((dwError = GetLastError()) == 0) break;				// Operation Success
			else if (dwError == ERROR_IO_INCOMPLETE) Dz1Thread_usleep(1000);	// Sleep 1 ms
			else
			{	// Error
				ClearCommError(h, &dwErrorFlag, &comstat);
				ERR_SET_OUT(&err, dwError);
				break;
			}
		}
		else break;		// Don't need wait
	}
	return err;
}

static Dz1Error _Dz1Serial_event(_Dz1Serial *p, DWORD *mask)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	COMSTAT comstat;
	DWORD dwErrorFlag;

	ClearCommError(p->fd, &dwErrorFlag, &comstat);

	*mask = p->mask;
	if (WaitCommEvent(p->fd, mask, &p->ols_event) == 0)
	{
		DWORD dwRet = GetLastError();
		if(dwRet == ERROR_IO_PENDING)
		{
			if ((err = _Dz1Serial_waitEvent(p->fd, &p->ols_event, mask)).code) ERR_OUT(&err);
		}
		else ERR_SET_OUT(&err, GetLastError());
	}
//	printf("Maske = %08X\n", *mask); fflush(stdout);
	return err;
}

static Dz1Error Dz1Serial_monitorByte(void *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	_Dz1Serial *p = (_Dz1Serial *)arg;

	DWORD mask = 0;

	unsigned char buf[DZ1_SERIAL_BUF_SIZE];
	ssize_t recvByte;

	//printf("Dz1Serial_monitorByte() : err.code = %d, p->idByte = %08x\n", err.code, p->idByte); fflush(stdout);
	while(err.code == 0)
	{
		pthread_testcancel();
		if ((recvByte = _Dz1Serial_read(p, buf, DZ1_SERIAL_BUF_SIZE, &err)) < 0) ERR_OUT(&err);
		else if (p->byteConsume) p->byteConsume(p->byteConsumeParam, buf, recvByte);
	}

	if (p->exception) p->exception(p->exceptionParam, p->portNum);

	return err;
}

static Dz1Error Dz1Serial_monitorEvent(void *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	_Dz1Serial *p = (_Dz1Serial *)arg;

	DWORD mask = 0;

	while(err.code == 0)
	{
		pthread_testcancel();
		mask = 0;
//		printf("(WE)");fflush(stdout);
		if ((err = _Dz1Serial_event(p, &mask)).code) { ERR_OUT(&err); break; }
		else
		{
			DWORD status = 0;
//			printf("Serial() : Event = %08x\n", mask); fflush(stdout);
			if (GetCommModemStatus(p->fd, &status) == TRUE)
			{
				if (mask & EV_RING)
				{
//					printf("Serial() : EV_RING : RING = %d\n", status & MS_RING_ON ? 1 : 0); fflush(stdout);
					if (p->ringInd)
						p->ringInd(p->ringIndParam, status & MS_RING_ON ? Dz1SerialPinState_high : Dz1SerialPinState_low);
				}
				if (mask & EV_CTS)
				{
//					printf("Serial() : EV_CTS : CTS = %d\n",status & MS_CTS_ON ? 1 : 0); fflush(stdout);
					if (p->ctsChanged)
						p->ctsChanged(p->ctsChangedParam, status & MS_CTS_ON ? Dz1SerialPinState_high : Dz1SerialPinState_low);
				}

				if (mask & EV_DSR)
				{
//					printf("Serial() : EV_DSR : DSR = %d\n",status & MS_DSR_ON ? 1 : 0); fflush(stdout);
					if (p->dsrChanged)
						p->dsrChanged(p->dsrChangedParam, status & MS_DSR_ON ? Dz1SerialPinState_high : Dz1SerialPinState_low);
				}
			}
		}
	}
	if (p->exception) p->exception(p->exceptionParam, p->portNum);

	return err;
}

static Dz1Error Dz1Serial_setupFlowCtrl(DCB *tios, DWORD *mask, Dz1SerialRTSCTS flowRTSCTS, Dz1SerialDSRDTR flowDSRDTR, Dz1SerialXONXOFF flowXONXOFF)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch (flowRTSCTS)
	{
		case Dz1SerialRTSCTS_on:
			tios->fRtsControl = RTS_CONTROL_HANDSHAKE;
			tios->fOutxCtsFlow = TRUE;
			*mask = (*mask) & ~EV_CTS;
			break;
		default:
		case Dz1SerialRTSCTS_off:
			tios->fRtsControl = RTS_CONTROL_DISABLE;
			tios->fOutxCtsFlow = FALSE;
			*mask = (*mask) | EV_CTS;
			break;
	}

	switch(flowDSRDTR)
	{
		case Dz1SerialDSRDTR_on:
			tios->fDtrControl = DTR_CONTROL_HANDSHAKE;
			tios->fOutxDsrFlow = TRUE;
			*mask = (*mask) & ~EV_DSR;
			break;
		default:
		case Dz1SerialDSRDTR_off:
			tios->fDtrControl = DTR_CONTROL_DISABLE;
			tios->fOutxDsrFlow = FALSE;
			*mask = (*mask) | EV_DSR;
			break;
	}

	switch(flowXONXOFF)
	{
		case Dz1SerialXONXOFF_on:
			tios->fOutX = TRUE;		// TX flow Controlled by XON/XOFF
			tios->fInX = TRUE;		// RX flow Controlled by XON/XOFF
			tios->XonChar = 0x11;
			tios->XoffChar = 0x13;
			break;
		default:
		case Dz1SerialXONXOFF_off:
			tios->fOutX = FALSE;		// TX flow Controlled by XON/XOFF
			tios->fInX = FALSE;		// RX flow Controlled by XON/XOFF
			break;
	}

	return err;
}

Dz1Serial *Dz1Serial_open(int portNum, u32_t baud, int bitPerByte, Dz1SerialParity parity, Dz1SerialStopBit stopBit, bool_t fullDuplex,
						  Dz1SerialRTSCTS flowRTSCTS, Dz1SerialDSRDTR flowDSRDTR, Dz1SerialXONXOFF flowXONXOFF,
						  Dz1SerialByteConsume		byteConsume, void *byteConsumeParam,
						  Dz1SerialPinChanged		ringInd,	 void *ringIndParam,
						  Dz1SerialPinChanged		ctsChanged,	 void *ctsChangedParam,
						  Dz1SerialPinChanged		dsrChanged,	 void *dsrChangedParam,
						  Dz1SerialException		exception,	 void *exceptionParam, Dz1Error *err)
{
	_Dz1Serial *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (portNum <= 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char portName[32];
		if (portNum > 4) sprintf(portName, "//./COM%d", portNum); else sprintf(portName, "COM%d", portNum);

		if ((ret = (_Dz1Serial *)Dz1Calloc(sizeof(_Dz1Serial), 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_mutex_init(&ret->lock, NULL);
			ret->portNum = portNum;
			ret->idByte = -1;
			ret->idEvent = -1;

			pthread_cleanup_push(Dz1Serial_closeAndSetNull, (void *)&ret);

			if ((ret->name = Dz1StrA_dup(portName, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ret->ols_read.Internal = 0;
				ret->ols_read.InternalHigh = 0;
				ret->ols_read.Offset = 0;
				ret->ols_read.OffsetHigh = 0;

				ret->ols_write.Internal = 0;
				ret->ols_write.InternalHigh = 0;
				ret->ols_write.Offset = 0;
				ret->ols_write.OffsetHigh = 0;

				ret->ols_event.Internal = 0;
				ret->ols_event.InternalHigh = 0;
				ret->ols_event.Offset = 0;
				ret->ols_event.OffsetHigh = 0;

				if (!(ret->ols_read.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))	ERR_SET_OUT(errp, EFAULT);
				else if (!(ret->ols_write.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) ERR_SET_OUT(errp, EFAULT);
				else if (!(ret->ols_event.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) ERR_SET_OUT(errp, EFAULT);
				else if ((ret->fd = CreateFile(ret->name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL)) == INVALID_HANDLE_VALUE) ERR_SET_OUT(errp, EFAULT);
				else
				{
					DCB newtio;
					COMMTIMEOUTS tos={1,0,0,0,0};

					newtio.DCBlength = sizeof(DCB);

					if (PurgeComm(ret->fd, PURGE_TXABORT|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_RXCLEAR) == FALSE) ERR_SET_OUT(errp, EFAULT);

					else if (SetCommTimeouts(ret->fd, &tos) == FALSE) ERR_SET_OUT(errp, EFAULT);
					else if (SetupComm(ret->fd, DZ1_SERIAL_BUF_SIZE, DZ1_SERIAL_BUF_SIZE) == FALSE) ERR_SET_OUT(errp, EFAULT);
					else if (GetCommState(ret->fd, &newtio) == FALSE) ERR_SET_OUT(errp, EFAULT);
					else
					{
						DWORD status = 0;
						ret->mask = EV_RING;

						newtio.fAbortOnError = FALSE;
						newtio.BaudRate = baud;
						newtio.ByteSize = bitPerByte;

						switch(parity)
						{
							default:
							case Dz1SerialParity_none:
								newtio.fParity = FALSE;
								newtio.Parity = NOPARITY;
								break;
							case Dz1SerialParity_even:
								newtio.fParity = TRUE;
								newtio.Parity = EVENPARITY;
								break;
							case Dz1SerialParity_odd:
								newtio.fParity = TRUE;
								newtio.Parity = ODDPARITY;
								break;
						}
						newtio.StopBits = stopBit;

						newtio.fRtsControl = RTS_CONTROL_DISABLE;
						newtio.fOutX=0;
						newtio.fInX=0;

						newtio.XonLim = 100;
						newtio.XoffLim = 200;

						if ((*errp = Dz1Serial_setupFlowCtrl(&newtio, &ret->mask, flowRTSCTS, flowDSRDTR, flowXONXOFF)).code) ERR_OUT(errp); else
						if (SetCommMask(ret->fd, ret->mask) == FALSE) ERR_SET_OUT(errp, EFAULT);
						else if (SetCommState(ret->fd, &newtio) == FALSE) ERR_SET_OUT(errp, EFAULT);
						else if (GetCommModemStatus(ret->fd, &status) == FALSE) ERR_SET_OUT(errp, EFAULT);
						else
						{
							ret->cts = status & MS_CTS_ON ? Dz1SerialPinState_high : Dz1SerialPinState_low;
							ret->dsr = status & MS_DSR_ON ? Dz1SerialPinState_high : Dz1SerialPinState_low;
							ret->fullDuplex = fullDuplex;

							ret->byteConsume = byteConsume; ret->byteConsumeParam = byteConsumeParam;
							ret->ringInd = ringInd;			ret->ringIndParam = ringIndParam;
							ret->ctsChanged = ctsChanged;	ret->ctsChangedParam = ctsChangedParam;
							ret->dsrChanged = dsrChanged;	ret->dsrChangedParam = dsrChangedParam;
							ret->exception = exception;		ret->exceptionParam = exceptionParam;

							if ((*errp = Dz1Thread_create(&ret->idByte, Dz1Serial_monitorByte, (void *)ret, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(errp);
							if ((*errp = Dz1Thread_create(&ret->idEvent, Dz1Serial_monitorEvent, (void *)ret, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
					}
				}
			}
			pthread_cleanup_pop(errp->code); // (dz1Serial_closeAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

void Dz1Serial_close(Dz1Serial *ptr)
{
	_Dz1Serial *p = (_Dz1Serial *)ptr;
	if (!p) return;

	if (p->idEvent != (u32_t)-1)
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		if ((err = Dz1Thread_stop(p->idEvent, FALSE)).code) ERR_OUT(&err);
		Dz1Thread_wait(p->idEvent, NULL);
		//p->idEvent = -1;
	}
	if (p->idByte != (u32_t)-1)
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		if ((err = Dz1Thread_stop(p->idByte, FALSE)).code) ERR_OUT(&err);
		Dz1Thread_wait(p->idByte, NULL);
		//p->idByte = -1;
	}
	if (p->fd != INVALID_HANDLE_VALUE) CloseHandle(p->fd);
	pthread_mutex_destroy(&p->lock);

	if (p->name) Dz1StrA_del(p->name);

	Dz1Free(p);
}

static ssize_t _Dz1Serial_write(_Dz1Serial *p, const u8_t *buf, size_t size, Dz1Error *errp)
{
	int status;
	char *bp = (char *)buf;
	COMSTAT comstat;
	DWORD dwErrorFlag;
	unsigned long temp;
	
	while(size)
	{
		if (WriteFile(p->fd, bp, (DWORD)size, &temp, &p->ols_write)==FALSE)
		{
			if ((status = GetLastError()) == ERROR_IO_PENDING)
			{
				ssize_t sz;
				if ((sz = _dz1Serial_rwWait(p, &p->ols_write, errp)) < 0) { ERR_OUT(errp); return -1; }
				else
				{
					size -= sz;
					bp += sz;
				}
			}
			else
			{
				ClearCommError(p->fd, &dwErrorFlag, &comstat);
				ERR_SET_OUT(errp, status);
				return -1;
			}
		}
		else
		{
			size -= temp;
			bp += temp;
		}
	}
	return (ssize_t)(bp - (char *)buf);
}

ssize_t Dz1Serial_write(Dz1Serial *ptr, const u8_t *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	_Dz1Serial *p = (_Dz1Serial *)ptr;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (p == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else if (p->fullDuplex == FALSE)
	{
		pthread_mutex_lock(&p->lock);
		pthread_cleanup_push((Dz1DelFunc)pthread_mutex_unlock, (void *)&p->lock);

		if ((ret = _Dz1Serial_write(p, buf, size, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)pthread_mutex_unlock, (void *)&p->lock);
	}
	else
	{
		if ((ret = _Dz1Serial_write(p, buf, size, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1Error Dz1Serial_setRTS(Dz1Serial *ptr, Dz1SerialPinState state)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	_Dz1Serial *p = (_Dz1Serial *)ptr;
	DWORD v = (state == Dz1SerialPinState_high) ? SETRTS : CLRRTS;
	
//	printf("Dz1Serial_setRTS() : %d\n", state); fflush(stdout);

	if (EscapeCommFunction(p->fd, v) == FALSE)
	{
		DWORD status = GetLastError();
		ERR_SET_OUT(&err, status);
	}
	return err;
}

Dz1Error Dz1Serial_setDTR(Dz1Serial *ptr, Dz1SerialPinState state)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	_Dz1Serial *p = (_Dz1Serial *)ptr;
	DWORD v = (state == Dz1SerialPinState_high) ? SETDTR : CLRDTR;

	if (EscapeCommFunction(p->fd, v) == FALSE) ERR_SET_OUT(&err, EFAULT);
	return err;
}

Dz1SerialPinState Dz1Serial_getDSR(Dz1Serial *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_Dz1Serial *p = (_Dz1Serial *)ptr;

	DWORD status = 0;
	if (GetCommModemStatus(p->fd, &status) == FALSE) ERR_SET_OUT(&err, EFAULT);

	if (status & MS_DSR_ON)
		return Dz1SerialPinState_high;
	else
		return Dz1SerialPinState_low;
}

Dz1SerialPinState Dz1Serial_getCTS(Dz1Serial *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_Dz1Serial *p = (_Dz1Serial *)ptr;

	DWORD status = 0;
	if (GetCommModemStatus(p->fd, &status) == FALSE) ERR_SET_OUT(&err, EFAULT);

	if (status & MS_CTS_ON)
		return Dz1SerialPinState_high;
	else
		return Dz1SerialPinState_low;
}


Dz1Error Dz1Serial_waitWriteDone(Dz1Serial *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	_Dz1Serial *p = (_Dz1Serial *)ptr;

	DWORD dwErrorFlags=0;
	COMSTAT commstat;

	ClearCommError(p->fd, &dwErrorFlags, &commstat);
	while(commstat.cbOutQue)
	{
		Sleep(10);
		ClearCommError(p->fd, &dwErrorFlags, &commstat);
	}
	Sleep(100);

	return err;
}

#else	// UNIX_SYSTEM

typedef struct _Dz1Serial
{
	s32_t					 portNum;
	str_t					 name;

	int						 fd;

	u32_t					 idByte;
	u32_t					 idEvent;

	bool_t					 fullDuplex;

	u32_t					 mask;

	Dz1SerialPinState		 cts;
	Dz1SerialPinState		 dsr;

//	DCB						 inittermios;

//	OVERLAPPED				 ols_read;
//	OVERLAPPED				 ols_write;
//	OVERLAPPED				 ols_event;

	Dz1SerialByteConsume	 byteConsume;
	void					*byteConsumeParam;

	Dz1SerialPinChanged		 ringInd;
	void					*ringIndParam;

	Dz1SerialPinChanged		 ctsChanged;
	void					*ctsChangedParam;

	Dz1SerialPinChanged		 dsrChanged;
	void					*dsrChangedParam;

	Dz1SerialException		 exception;
	void					*exceptionParam;

	pthread_mutex_t			 lock;
} _Dz1Serial;
Dz1Serial *Dz1Serial_open(int					portNum,
						  u32_t					baud,
						  int					bitPerByte,
						  Dz1SerialParity		parity,
						  Dz1SerialStopBit		stopBit,
						  bool_t				fullDuplex,

						  Dz1SerialRTSCTS		flowRTSCTS,
						  Dz1SerialDSRDTR		flowDSRDTR,
						  Dz1SerialXONXOFF		flowXONXOFF,

						  Dz1SerialByteConsume	byteConsume,	void *byteConsumeParam,
						  Dz1SerialPinChanged	ringInd,		void *ringIndParam,
						  Dz1SerialPinChanged	ctsChanged,		void *ctsChangedParam,
						  Dz1SerialPinChanged	dsrChanged,		void *dsrChangedParam,
						  Dz1SerialException	exception,		void *exceptionParam,

						  Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE( errp, err);
	if (portNum == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		portNum--;						// make 0 base number
		ERR_SET_OUT( errp, ENOSYS);
	}
	return NULL;
}

void Dz1Serial_close(Dz1Serial *p)
{
}

Dz1Error Dz1Serial_setRTS(Dz1Serial *ptr, Dz1SerialPinState state)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	
	ERR_SET_OUT( errp, ENOSYS);	
	
	return err;
}
Dz1Error Dz1Serial_setDTR(Dz1Serial *ptr, Dz1SerialPinState state)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	ERR_SET_OUT( errp, ENOSYS);	

	return err;
}
ssize_t Dz1Serial_write(Dz1Serial *p, const unsigned char *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE( errp, err);
	ERR_SET_OUT( errp, ENOSYS);
	return ret;
}

Dz1SerialPinState Dz1Serial_getDSR(Dz1Serial *ptr)
{
	return (Dz1SerialPinState)-1;
}
Dz1SerialPinState Dz1Serial_getCTS(Dz1Serial *ptr)
{
	return (Dz1SerialPinState)-1;
}


Dz1Error Dz1Serial_waitWriteDone(Dz1Serial *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	ERR_SET_OUT( errp, ENOSYS);	

	return err;
}
#endif	// UNIX_SYSTEM

Dz1Serial *Dz1Serial_openNullModem(int portNum, u32_t baud,
								   int bitPerByte, Dz1SerialParity pairty, Dz1SerialStopBit stopBit,
								   bool_t duplex,
								   Dz1SerialXONXOFF xonoffFlowControl,
								   Dz1SerialByteConsume byteConsume, void *byteConsumeParam,
								   Dz1SerialException exception, void *exceptionParam,
								   Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	void *ret = Dz1Serial_open(portNum, baud, bitPerByte, pairty, stopBit, duplex, 
							   Dz1SerialRTSCTS_off, 
							   Dz1SerialDSRDTR_off, 
							   xonoffFlowControl,
							   byteConsume, byteConsumeParam, 
							   NULL, NULL, 
							   NULL, NULL, 
							   NULL, NULL, 
							   exception, exceptionParam, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

void Dz1Serial_setByteConsume(Dz1Serial *ptr, Dz1SerialByteConsume byteConsume, void *byteConsumeParam)
{
	_Dz1Serial *p = (_Dz1Serial *)ptr;
	pthread_mutex_lock(&p->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	p->byteConsume = byteConsume;
	p->byteConsumeParam = byteConsumeParam;
	pthread_cleanup_pop(1); // (pthread_mutex_unlock, (void *)&p->lock);
}
