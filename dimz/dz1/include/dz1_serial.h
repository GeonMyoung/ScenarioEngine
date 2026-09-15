#ifndef DZ1_SERIAL_H
#define DZ1_SERIAL_H

#include <dz1_error.h>

typedef enum Dz1SerialParity
{
	Dz1SerialParity_none,
	Dz1SerialParity_even,
	Dz1SerialParity_odd,
	Dz1SerialParity_max
} Dz1SerialParity;
DZ1_CPPLINK DZ1_DLLPORT str_t			 Dz1SerialParityStrA(Dz1SerialParity v);
DZ1_CPPLINK DZ1_DLLPORT Dz1SerialParity	 Dz1SerialParityFromStrA(str_t v);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t			 Dz1SerialParityStrW(Dz1SerialParity v);
DZ1_CPPLINK DZ1_DLLPORT Dz1SerialParity	 Dz1SerialParityFromStrW(wstr_t v);
#ifdef UNICODE
#define									 Dz1SerialParityStr			Dz1SerialParityStrW
#define									 Dz1SerialParityFromStr		Dz1SerialParityFromStrW
#else // UNICODE
#define									 Dz1SerialParityStr			Dz1SerialParityStrA
#define									 Dz1SerialParityFromStr		Dz1SerialParityFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define									 Dz1SerialParityStr			Dz1SerialParityStrA
#define									 Dz1SerialParityFromStr		Dz1SerialParityFromStrA
#endif // UNIX_SYSTEM

typedef enum Dz1SerialStopBit
{
	Dz1SerialStopBit_one,
	Dz1SerialStopBit_oneHalf,
	Dz1SerialStopBit_two,
	Dz1SerialStopBit_max
} Dz1SerialStopBit;
DZ1_CPPLINK DZ1_DLLPORT str_t			 Dz1SerialStopBitStrA(Dz1SerialStopBit v);
DZ1_CPPLINK DZ1_DLLPORT Dz1SerialStopBit Dz1SerialStopBitFromStrA(str_t v);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t			 Dz1SerialStopBitStrW(Dz1SerialStopBit v);
DZ1_CPPLINK DZ1_DLLPORT Dz1SerialStopBit Dz1SerialStopBitFromStrW(wstr_t v);
#ifdef UNICODE
#define									 Dz1SerialStopBitStr		Dz1SerialStopBitStrW
#define									 Dz1SerialStopBitFromStr	Dz1SerialStopBitFromStrW
#else // UNICODE
#define									 Dz1SerialStopBitStr		Dz1SerialStopBitStrA
#define									 Dz1SerialStopBitFromStr	Dz1SerialStopBitFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define									 Dz1SerialStopBitStr		Dz1SerialStopBitStrA
#define									 Dz1SerialStopBitFromStr	Dz1SerialStopBitFromStrA
#endif // UNIX_SYSTEM

// Request To Send, Clear To Send : RTS --> CTS ¡Ô RTS∏¶ ø√∑»¥Ÿ ≥ª∑»¥Ÿ
typedef enum Dz1SerialRTSCTS
{
	Dz1SerialRTSCTS_manual,
	Dz1SerialRTSCTS_on,
	Dz1SerialRTSCTS_max
} Dz1SerialRTSCTS;
#define Dz1SerialRTSCTS_off		Dz1SerialRTSCTS_manual

DZ1_CPPLINK DZ1_DLLPORT str_t			 Dz1SerialRTSCTSStrA(Dz1SerialRTSCTS v);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t			 Dz1SerialRTSCTSStrW(Dz1SerialRTSCTS v);
#ifdef UNICODE
#define									 Dz1SerialRTSCTSStr		Dz1SerialRTSCTSStrW
#else	// UNICODE
#define									 Dz1SerialRTSCTSStr		Dz1SerialRTSCTSStrA
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define									 Dz1SerialRTSCTSStr		Dz1SerialRTSCTSStrA
#endif	// UNIX_SYSTEM

// Data Set Ready, Data Terminal Ready : DTR --> DSR ¡Ô DTR¿ª ø√∑»¥Ÿ ≥ª∑»¥Ÿ
typedef enum Dz1SerialDSRDTR
{
	Dz1SerialDSRDTR_manual,
	Dz1SerialDSRDTR_on,
	Dz1SerialDSRDTR_max
} Dz1SerialDSRDTR;
#define Dz1SerialDSRDTR_off		Dz1SerialDSRDTR_manual

DZ1_CPPLINK DZ1_DLLPORT str_t			 Dz1SerialDSRDTRStrA(Dz1SerialDSRDTR v);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t			 Dz1SerialDSRDTRStrW(Dz1SerialDSRDTR v);
#ifdef UNICODE
#define									 Dz1SerialDSRDTRStr		Dz1SerialDSRDTRStrW
#else	// UNICODE
#define									 Dz1SerialDSRDTRStr		Dz1SerialDSRDTRStrA
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define									 Dz1SerialDSRDTRStr		Dz1SerialDSRDTRStrA
#endif	// UNIX_SYSTEM


typedef enum Dz1SerialXONXOFF
{
	Dz1SerialXONXOFF_off,
	Dz1SerialXONXOFF_on,
	Dz1SerialXONXOFF_max
} Dz1SerialXONXOFF;
DZ1_CPPLINK DZ1_DLLPORT str_t			 Dz1SerialXONXOFFStrA(Dz1SerialXONXOFF v);
DZ1_CPPLINK DZ1_DLLPORT Dz1SerialXONXOFF Dz1SerialXONXOFFFromStrA(str_t v);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t			 Dz1SerialXONXOFFStrW(Dz1SerialXONXOFF v);
DZ1_CPPLINK DZ1_DLLPORT Dz1SerialXONXOFF Dz1SerialXONXOFFFromStrW(wstr_t v);
#ifdef UNICODE
#define									 Dz1SerialXONXOFFStr		Dz1SerialXONXOFFStrW
#define									 Dz1SerialXONXOFFFromStr	Dz1SerialXONXOFFFromStrW
#else	// UNICODE
#define									 Dz1SerialXONXOFFStr		Dz1SerialXONXOFFStrA
#define									 Dz1SerialXONXOFFFromStr	Dz1SerialXONXOFFFromStrA
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define									 Dz1SerialXONXOFFStr		Dz1SerialXONXOFFStrA
#define									 Dz1SerialXONXOFFFromStr	Dz1SerialXONXOFFFromStrA
#endif	// UNIX_SYSTEM

typedef enum Dz1SerialPinState
{
	Dz1SerialPinState_low,
	Dz1SerialPinState_high,
	Dz1SerialPinState_max
} Dz1SerialPinState;
DZ1_CPPLINK DZ1_DLLPORT str_t			 Dz1SerialPinStateStrA(Dz1SerialPinState v);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t			 Dz1SerialPinStateStrW(Dz1SerialPinState v);
#ifdef UNICODE
#define									 Dz1SerialPinStateStr		Dz1SerialPinStateStrW
#else	// UNICODE
#define									 Dz1SerialPinStateStr		Dz1SerialPinStateStrA
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define									 Dz1SerialPinStateStr		Dz1SerialPinStateStrA
#endif	// UNIX_SYSTEM

typedef void (*Dz1SerialByteConsume)(void *ptr, u8_t *data, size_t size);
typedef void (*Dz1SerialPinChanged)(void *ptr, Dz1SerialPinState state);
typedef void (*Dz1SerialException)(void *ptr, s32_t portNum);

typedef void Dz1Serial;
// portNum == 1 mean COM1 in Windows, ttyS0 in Linux or UNIX
DZ1_CPPLINK DZ1_DLLPORT Dz1Serial			*Dz1Serial_open(int						portNum,
															u32_t					baud,
															int						bitPerByte,
															Dz1SerialParity			parity,
															Dz1SerialStopBit		stopBit,
															bool_t					fullDuplex,

															Dz1SerialRTSCTS			flowRTSCTS,
															Dz1SerialDSRDTR			flowDSRDTR,
															Dz1SerialXONXOFF		flowXONXOFF,

															Dz1SerialByteConsume	byteConsume,	void *byteConsumeParam,
															Dz1SerialPinChanged		ringInd,		void *ringIndParam,
															Dz1SerialPinChanged		ctsChanged,		void *ctsChangedParam,
															Dz1SerialPinChanged		dsrChanged,		void *dsrChangedParam,
															Dz1SerialException		exception,		void *exceptionParam,

															Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Serial			*Dz1Serial_openNullModem(int portNum, u32_t baud,
																	 int bitPerByte,
																	 Dz1SerialParity pairty,
																	 Dz1SerialStopBit stopBit,
																	 bool_t duplex,
																	 Dz1SerialXONXOFF xonoffFlowControl,
																	 Dz1SerialByteConsume byteConsume, void *byteConsumeParam,
																	 Dz1SerialException exception, void *exceptionParam,
																	 Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Serial_close(Dz1Serial *p);
#define										 Dz1Serial_delAndSetNull	Dz1Serial_closeAndSetNull
static __inline__ void						 Dz1Serial_closeAndSetNull(void *pptr)
{
	Dz1Serial **p = (Dz1Serial **)pptr;
	if (p) { Dz1Serial_close(*p); *p = NULL; }
}


DZ1_CPPLINK DZ1_DLLPORT Dz1Error			 Dz1Serial_setRTS(Dz1Serial *ptr, Dz1SerialPinState state);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error			 Dz1Serial_setDTR(Dz1Serial *ptr, Dz1SerialPinState state);

DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Serial_write(Dz1Serial *p, const unsigned char *buf, size_t size, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1SerialPinState	 Dz1Serial_getDSR(Dz1Serial *ptr);
DZ1_CPPLINK DZ1_DLLPORT Dz1SerialPinState	 Dz1Serial_getCTS(Dz1Serial *ptr);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Serial_setByteConsume(Dz1Serial *ptr, Dz1SerialByteConsume byteConsume, void *byteConsumeParam);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error			 Dz1Serial_waitWriteDone(Dz1Serial *ptr);
#endif
