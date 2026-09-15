#include <dz1_gasn_support.h>
#include "ItsIso14827Test_msg.h"
#include "ItsIso14827TestEam.h"

////////////////////////////////////////////////////////////////////////////////
// RequestServerTimeMode
static struct RequestServerTimeModeStrMapA
{
	RequestServerTimeMode	mode;
	str_t					str;
} requestServerTimeModeStrMapA[] =
{
	{ RequestServerTimeMode_full,	"full" },
	{ RequestServerTimeMode_hhmmss,	"hhmmss" },
	{ RequestServerTimeMode_hhmm,	"hhmm" },
	{ RequestServerTimeMode_max,	"unknown" },
};

str_t RequestServerTimeModeStrA(RequestServerTimeMode v)
{
	struct RequestServerTimeModeStrMapA *i;
	for(i = requestServerTimeModeStrMapA; i->mode != RequestServerTimeMode_max; i++)
		if (i->mode == v) break;
	return i->str;
}

#ifndef UNIX_SYSTEM
static struct RequestServerTimeModeStrMapW
{
	RequestServerTimeMode	mode;
	wstr_t					str;
} requestServerTimeModeStrMapW[] =
{
	{ RequestServerTimeMode_full,	L"full" },
	{ RequestServerTimeMode_hhmmss,	L"hhmmss" },
	{ RequestServerTimeMode_hhmm,	L"hhmm" },
	{ RequestServerTimeMode_max,	NULL },
};

wstr_t RequestServerTimeModeStrW(RequestServerTimeMode v)
{
	struct RequestServerTimeModeStrMapW *i;
	for(i = requestServerTimeModeStrMapW; i->mode != RequestServerTimeMode_max; i++)
		if (i->mode == v) break;
	return i->str;
}
#endif // UNIX_SYSTEM
// RequestServerTimeMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RequestServerTime
RequestServerTime *RequestServerTime_new(RequestServerTimeMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	RequestServerTime *ret = (RequestServerTime *)Dz1Calloc(sizeof(RequestServerTime), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->mode = mode;
		ERR_CLEAR(errp);
	}
	return ret;
}

RequestServerTime *RequestServerTime_clone(RequestServerTime *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	RequestServerTime *ret = RequestServerTime_new(src->mode, errp);
	if (ret == NULL) ERR_OUT(errp);
	else ERR_CLEAR(errp);
	return ret;
}

void RequestServerTime_del(RequestServerTime *p)
{
	if (!p) return;
	Dz1Free(p);
}

void RequestServerTime_dump(RequestServerTime *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else Dz1Thread_printf(Dz1Text("%s\n"), RequestServerTimeModeStr(p->mode));
}
// RequestServerTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ResponseServerTime
ResponseServerTime *ResponseServerTime_new(Dz1Str formatted_timestr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ResponseServerTime *ret = NULL;
	
	if ((ret = (ResponseServerTime *)Dz1Calloc(sizeof(ResponseServerTime), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ResponseServerTime_delAndSetNull, (void *)&ret);

		if (0) { }
		else if (Dz1Str_isVoid(formatted_timestr) == FALSE && (ret->formatted_timestr = Dz1Str_dup(formatted_timestr, errp)) == NULL) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (ResponseServerTime_delAndSetNull, (void *)&ret);
	}
	return ret;
}

ResponseServerTime *ResponseServerTime_clone(ResponseServerTime *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ResponseServerTime *ret = ResponseServerTime_new(src->formatted_timestr, errp);
	if (ret == NULL) ERR_OUT(errp);
	else ERR_CLEAR(errp);
	return ret;
}

void ResponseServerTime_del(ResponseServerTime *p)
{
	if (!p) return;
	Dz1Str_delAndSetNull(&p->formatted_timestr);
	Dz1Free(p);
}

void ResponseServerTime_dump(ResponseServerTime *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else Dz1Thread_printf(Dz1Text("%s\n"), p->formatted_timestr);
}
// ResponseServerTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestMessage
TestMessage *TestMessage_new(TestMessagePresent present, void *ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = (TestMessage *)Dz1Calloc(sizeof(TestMessage), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case TestMessagePresent_timestamp_req: ret->x.timestamp_req = (RequestServerTime *)ptr; break;
		case TestMessagePresent_timestamp_rsp: ret->x.timestamp_rsp = (ResponseServerTime *)ptr; break;
		default: break;
		}
		ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (RequestMessage_delAndSetNull, (void *)&ret);
	}
	return ret;
}

TestMessage *TestMessage_clone(TestMessage *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = TestMessage_new(src->present, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&ret);

		// Additional clone code here
		switch(ret->present)
		{
		case TestMessagePresent_timestamp_req: 
			if ((ret->x.timestamp_req = RequestServerTime_clone(src->x.timestamp_req, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TestMessagePresent_timestamp_rsp:
			if ((ret->x.timestamp_rsp = ResponseServerTime_clone(src->x.timestamp_rsp, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			break;
		}
		ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestMessage_delAndSetNull, (void *)&ret);
	}

	return ret;
}

void TestMessage_del(TestMessage *p)
{
	if (!p) return;
	switch(p->present)
	{
	case TestMessagePresent_timestamp_req: RequestServerTime_delAndSetNull(&p->x.timestamp_req); break;
	case TestMessagePresent_timestamp_rsp: ResponseServerTime_delAndSetNull(&p->x.timestamp_rsp); break;
	default: break;
	}
	Dz1Free(p);
}

void TestMessage_dump(TestMessage *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else
	{
		switch(p->present)
		{
		case TestMessagePresent_timestamp_req: Dz1Thread_printf(Dz1Text("timestamp_req = ")); RequestServerTime_dump(p->x.timestamp_req, tab); break;
		case TestMessagePresent_timestamp_rsp: Dz1Thread_printf(Dz1Text("timestamp_rsp = ")); ResponseServerTime_dump(p->x.timestamp_rsp, tab); break;
		default: Dz1Thread_printf(Dz1Text("unknown = %d\n"), p->present);break;
		}
	}
}
// TestMessage
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// RequestServerTime CODEC
static Dz1Binary *RequestServerTime_encode(void *ptr, Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;
	if (codec != Dz1Asn1Codec_ber) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		RequestServerTime *src = (RequestServerTime *)ptr;

		ItsIso14827TestTimeFormat fmt = (ItsIso14827TestTimeFormat)src->mode;
		ItsIso14827TestTimeRequest asn;
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

		if (ASN1_SET_ItsIso14827TestTimeRequest_fmt(&ws, &asn, fmt) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_BER_Enc_ItsIso14827TestTimeRequest(&ws, &asn, ASN1IMPL) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, codec), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ret;
}

static TestMessage *RequestServerTime_decode(u8_t *data, size_t sz, Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = NULL;
	if (codec != Dz1Asn1Codec_ber) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		ItsIso14827TestTimeRequest asn;
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

		if (ASN1_Save_WORKSPACE(&ws, data, (ASNUINT32)sz) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_BER_Dec_ItsIso14827TestTimeRequest(&ws, &asn, (int)sz, ASN1IMPL) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ret = TestMessage_new(TestMessagePresent_timestamp_req, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			RequestServerTime *p = NULL;
			pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&ret);
			if ((ret->x.timestamp_req = p = RequestServerTime_new((RequestServerTimeMode)asn.fmt, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (RequestMessage_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	}
	return ret;
}
// RequestServerTime CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ResponseServerTime
static Dz1Binary *ResponseServerTime_encode(void *ptr, Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;
	Dz1Asn1UTF8Str *utf8 = NULL;
	ResponseServerTime *src = (ResponseServerTime *)ptr;
	if (codec != Dz1Asn1Codec_ber) ERR_SET_OUT(errp, ENOSYS);
	else if ((utf8 = Dz1Asn1UTF8Str_newFromStr(src->formatted_timestr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827TestTimeResponse asn;
		ASN1WorkSpace ws;
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);

		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

		if (ASN1_SET_ItsIso14827TestTimeResponse_str(&ws, &asn, utf8->data, utf8->size) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (ASN1_BER_Enc_ItsIso14827TestTimeResponse(&ws, &asn, ASN1IMPL) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, codec), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
	}
	return ret;
}

static TestMessage *ResponseServerTime_decode(u8_t *data, size_t sz, Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = NULL;
	Dz1Asn1UTF8Str *utf8 = NULL;
	ItsIso14827TestTimeResponse asn;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if (ASN1_Save_WORKSPACE(&ws, data, (ASNINT32)sz) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (ASN1_BER_Dec_ItsIso14827TestTimeResponse(&ws, &asn, (int)sz, ASN1IMPL) < 0) ERR_SET_OUT(errp, EFAULT);
	else if ((utf8 = Dz1Asn1UTF8Str_new(asn.str.asnstring, asn.str.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
		if ((ret = TestMessage_new(TestMessagePresent_timestamp_rsp, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ResponseServerTime *p = NULL;
			pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&ret);
			if ((ret->x.timestamp_rsp = p = ResponseServerTime_new(NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((p->formatted_timestr = Dz1Asn1UTF8Str_toStr(utf8, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (TestMessage_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
	}
	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return ret;
}
// ResponseServerTime
///////////////////////////////////////////////////////////////////////////////

typedef struct MessageAsnMap
{
	TestMessagePresent		 present;
	Dz1Str					 oid;
	Dz1Binary				*(*encode)(void *src, Dz1Asn1Codec codec, Dz1Error *err);
	TestMessage				*(*decode)(u8_t *data, size_t sz, Dz1Asn1Codec codec, Dz1Error *err);
} MessageAsnMap;

static MessageAsnMap *MessageAsnMap_findByPresent(MessageAsnMap *tbl, TestMessagePresent v)
{
	MessageAsnMap *i;
	for (i = tbl; i->present != TestMessagePresent_max; i++)
		if (i->present == v) return i;
	return NULL;
}

static MessageAsnMap *MessageAsnMap_findByOID(MessageAsnMap *tbl, Dz1Str oid)
{
	MessageAsnMap *i;
	for (i = tbl; i->present != TestMessagePresent_max; i++)
		if (Dz1STRCMP(i->oid, oid) == 0) return i;
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// TestMessage CODEC
static MessageAsnMap requestMessageAsnMap[] =
{
	{ TestMessagePresent_timestamp_req, Dz1Text("1.2.410.20053.0.1.1"), RequestServerTime_encode,	RequestServerTime_decode },
	{ TestMessagePresent_timestamp_rsp, Dz1Text("1.2.410.20053.0.2.1"), ResponseServerTime_encode,	ResponseServerTime_decode },
	{ TestMessagePresent_max, NULL, NULL, NULL }
};

Dz1Binary *TestMessage_encode(TestMessage *src, Dz1Asn1Codec codec, Dz1Str *rsp_oid, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;
	MessageAsnMap *api = MessageAsnMap_findByPresent(requestMessageAsnMap, src->present);
	if (api == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((ret = api->encode(src->x.__ptr__, codec, errp)) == NULL) ERR_OUT(errp);
	else
	{
		if (rsp_oid != NULL) (*rsp_oid) = api->oid;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

TestMessage *TestMessage_decode(str_t oidStr, u8_t *data, size_t size, Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = NULL;
	MessageAsnMap *api = MessageAsnMap_findByOID(requestMessageAsnMap, oidStr);
	if (api == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((ret = api->decode(data, size, codec, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
// TestMessage CODEC
////////////////////////////////////////////////////////////////////////////////
