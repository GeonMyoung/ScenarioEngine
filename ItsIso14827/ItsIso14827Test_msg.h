#ifndef ITS_ISO_14827_TEST_MSG_H
#define ITS_ISO_14827_TEST_MSG_H

#include <dz1_str.h>
#include <dz1_asn1.h>

////////////////////////////////////////////////////////////////////////////////
// RequestServerTimeMode
typedef enum RequestServerTimeMode
{
	RequestServerTimeMode_full,
	RequestServerTimeMode_hhmmss,
	RequestServerTimeMode_hhmm,
	RequestServerTimeMode_max
} RequestServerTimeMode;

DZ1_CPPLINK str_t				 RequestServerTimeModeStrA(RequestServerTimeMode v);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t				 RequestServerTimeModeStrW(RequestServerTimeMode v);
#ifdef UNICODE
#define							 RequestServerTimeModeStr	RequestServerTimeModeStrW
#else // UNICODE
#define							 RequestServerTimeModeStr	RequestServerTimeModeStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 RequestServerTimeModeStr	RequestServerTimeModeStrA
#endif
// RequestServerTimeMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RequestServerTime
typedef struct RequestServerTime
{
	RequestServerTimeMode			 mode;
} RequestServerTime;

DZ1_CPPLINK RequestServerTime	*RequestServerTime_new(RequestServerTimeMode mode, Dz1Error *err);
DZ1_CPPLINK RequestServerTime	*RequestServerTime_clone(RequestServerTime *src, Dz1Error *err);
DZ1_CPPLINK void				 RequestServerTime_del(RequestServerTime *p);
static __inline__ void			 RequestServerTime_delAndSetNull(void *pptr)
{
	RequestServerTime **p = (RequestServerTime **)pptr;
	RequestServerTime_del(*p);
	*p = NULL;
}
DZ1_CPPLINK void				 RequestServerTime_dump(RequestServerTime *p, int tab);
// RequestServerTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ResponseServerTime
typedef struct ResponseServerTime
{
	Dz1Str						 formatted_timestr;
} ResponseServerTime;

DZ1_CPPLINK ResponseServerTime	*ResponseServerTime_new(Dz1Str formatted_timestr, Dz1Error *err);
DZ1_CPPLINK ResponseServerTime	*ResponseServerTime_clone(ResponseServerTime *src, Dz1Error *err);
DZ1_CPPLINK void				 ResponseServerTime_del(ResponseServerTime *p);
static __inline__ void			 ResponseServerTime_delAndSetNull(void *pptr)
{
	ResponseServerTime **p = (ResponseServerTime **)pptr;
	ResponseServerTime_del(*p);
	*p = NULL;
}
DZ1_CPPLINK void				 ResponseServerTime_dump(ResponseServerTime *p, int tab);
// ResponseServerTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RequestMessage
typedef enum TestMessagePresent
{
	TestMessagePresent_timestamp_req,
	TestMessagePresent_timestamp_rsp,
	TestMessagePresent_max
} TestMessagePresent;

typedef struct TestMessage
{
	TestMessagePresent			 present;
	union
	{
		void					*__ptr__;
		RequestServerTime		*timestamp_req;
		ResponseServerTime		*timestamp_rsp;
	} x;
} TestMessage;
DZ1_CPPLINK TestMessage			*TestMessage_new(TestMessagePresent present, void *ptr, Dz1Error *err);
DZ1_CPPLINK TestMessage			*TestMessage_clone(TestMessage *src, Dz1Error *err);
DZ1_CPPLINK void				 TestMessage_del(TestMessage *p);
static __inline__ void			 TestMessage_delAndSetNull(void *pptr)
{
	TestMessage **p = (TestMessage **)pptr;
	TestMessage_del(*p);
	*p = NULL;
}
DZ1_CPPLINK void				 TestMessage_dump(TestMessage *p, int tab);
DZ1_CPPLINK Dz1Binary			*TestMessage_encode(TestMessage *src, Dz1Asn1Codec codec, Dz1Str *rsp_oid, Dz1Error *err);
DZ1_CPPLINK TestMessage			*TestMessage_decode(str_t oidStr, u8_t *data, size_t size, Dz1Asn1Codec codec, Dz1Error *err);
// RequestMessage
////////////////////////////////////////////////////////////////////////////////

#endif
