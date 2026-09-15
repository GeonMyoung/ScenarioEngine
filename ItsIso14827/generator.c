#include "generator.h"
#include "ItsIso14827Test_msg.h"

static void *_time_stamp_full(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = TestMessage_new(TestMessagePresent_timestamp_req, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		RequestServerTime *p = NULL;
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&ret);
		if ((ret->x.timestamp_req = p = RequestServerTime_new(RequestServerTimeMode_full, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (TestMessage_delAndSetNull, (void *)&ret);
	}
	return ret;
}
 
static void *_time_stamp_hhmmss(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = TestMessage_new(TestMessagePresent_timestamp_req, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		RequestServerTime *p = NULL;
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&ret);
		if ((ret->x.timestamp_req = p = RequestServerTime_new(RequestServerTimeMode_hhmmss, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (TestMessage_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void *_time_stamp_hhmm(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = TestMessage_new(TestMessagePresent_timestamp_req, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		RequestServerTime *p = NULL;
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&ret);
		if ((ret->x.timestamp_req = p = RequestServerTime_new(RequestServerTimeMode_hhmm, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (TestMessage_delAndSetNull, (void *)&ret);
	}
	return ret;
}

MsgGenerator testMessageGenerator[] =
{
	{ 0, _time_stamp_full,		(Dz1DelFunc)TestMessage_delAndSetNull },
	{ 1, _time_stamp_hhmmss,	(Dz1DelFunc)TestMessage_delAndSetNull },
	{ 2, _time_stamp_hhmm,		(Dz1DelFunc)TestMessage_delAndSetNull },
	{ -1, NULL, NULL }
};

MsgGenerator *MsgGenerator_find(int num, MsgGenerator table[])
{
	MsgGenerator *i;
	for (i = table; i->num != -1; i++)
		if (i->num == num) return i;
	return NULL;
}
