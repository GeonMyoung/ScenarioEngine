#include <dz1_gasn_support.h>
#include <ItsIso14827TaskSupport.h>
#include "ItsIso14827Test.h"

////////////////////////////////////////////////////////////////////////////////
// TestServerUser
typedef struct TestServerUser
{
	Dz1Asn1OctetStr			*name;
	Dz1Asn1OctetStr			*pass;
} TestServerUser;

static void TestServerUser_del(TestServerUser *p)
{
	if (!p) return;
	Dz1Asn1OctetStr_delAndSetNull(&p->name);
	Dz1Asn1OctetStr_delAndSetNull(&p->pass);
	Dz1Free(p);
}

static void TestServerUser_delAndSetNull(void *pptr)
{
	TestServerUser **p = (TestServerUser **)pptr;
	TestServerUser_del(*p);
	*p = NULL;
}

static TestServerUser *TestServerUser_new(Dz1Asn1OctetStr *name, Dz1Asn1OctetStr *pass, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerUser *ret = NULL;
	
	if (name == NULL || pass == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (TestServerUser *)Dz1Calloc(sizeof(TestServerUser), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerUser_delAndSetNull, (void *)&ret);

		if (0) { }
		else if ((ret->name = Dz1Asn1OctetStr_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->pass = Dz1Asn1OctetStr_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestServerUser_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static TestServerUser *TestServerUser_generate(Dz1Str name, Dz1Str pass, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerUser *ret = NULL;
	
	if (name == NULL || pass == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (TestServerUser *)Dz1Calloc(sizeof(TestServerUser), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerUser_delAndSetNull, (void *)&ret);

		if (0) { }
		else if ((ret->name = Dz1Asn1UTF8Str_newFromStr(name, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->pass = Dz1Asn1UTF8Str_newFromStr(pass, errp)) == NULL) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestServerUser_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static TestServerUser *TestServerUser_clone(TestServerUser *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerUser *ret = TestServerUser_new(src->name, src->pass, errp);
	if (ret == NULL) ERR_OUT(errp);
	else ERR_CLEAR(errp);
	return ret;
}

static void TestServerUser_dump(TestServerUser *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else Dz1Asn1OctetStr_dump(p->name, tab);
}

static int TestServerUser_cmp(TestServerUser *a, TestServerUser *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else if (a->name == NULL && b->name == NULL) return 0;
	else if (a->name == NULL) return -1;
	else if (b->name == NULL) return 1;
	else return Dz1Asn1OctetStr_cmp(a->name, b->name);
}

static bool_t TestServerUser_chkPass(TestServerUser *p, Dz1Asn1OctetStr *pass)
{
	bool_t ret = FALSE;
	if (p != NULL && pass != NULL && p->pass != NULL)
	{
		if (Dz1Asn1OctetStr_cmp(p->pass, pass) == 0) ret = TRUE;
		else ret = FALSE;
	}
	return ret;
}
// TestServerUser
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestServerUserList
typedef Dz1AATree TestServerUserList;

static void TestServerUserList_del(TestServerUserList *p)
{
	if (!p) return;
	Dz1AATree_del(p);
}

static void TestServerUserList_delAndSetNull(void *pptr)
{
	TestServerUserList **p = (TestServerUserList **)pptr;
	TestServerUserList_del(*p);
	*p = NULL;
}

static TestServerUserList *TestServerUserList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerUserList *ret = Dz1AATree_new((Dz1CmpFunc)TestServerUser_cmp, (Dz1DelFunc)TestServerUser_del, (Dz1DumpFunc)TestServerUser_dump, errp);
	if (ret == NULL) ERR_OUT(errp);
	else ERR_CLEAR(errp);
	return ret;
}

static  Dz1Error _TestServerUserList_clone(void *ptr, void *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestServerUserList *dst = (TestServerUserList *)ptr;
	TestServerUser *src = (TestServerUser *)data;

	TestServerUser *node = TestServerUser_clone(src, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerUser_delAndSetNull, (void **)&node);
		if (0) { }
		else if ((*errp = Dz1AATree_insert(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TestServerUser_delAndSetNull, (void **)&node);
	}
	return err;
}

static TestServerUserList *TestServerUserList_clone(TestServerUserList *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerUserList *ret = TestServerUserList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerUserList_delAndSetNull, (void *)&ret);

		if ((*errp = Dz1AATree_travel(src, _TestServerUserList_clone, (void *)ret)).code) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestServerUserList_delAndSetNull, (void *)&ret);
	}

	return ret;
}

static void TestServerUserList_dump(TestServerUserList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1Text("{\n")); tab++;
		Dz1AATree_dump(p, tab);
		Dz1Thread_tprintf(--tab, Dz1Text("}\n"));
	}
}

static TestServerUser *TestServerUserList_find(TestServerUserList *list, Dz1Asn1OctetStr *user)
{
	TestServerUser *ret = NULL;
	if (list != NULL && user != NULL)
	{
		TestServerUser key; // = { user };
		key.name = user;
		ret = Dz1AATree_find(list, &key);
	}
	return ret;
}

static bool_t TestServerUserList_load(TestServerUserList *dst, TestServerUserEntry arr[], u32_t arr_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t i;
	TestServerUser *node = NULL;
	for (i = 0; errp->code == 0 && i < arr_cnt; i++)
	{
		if ((node = TestServerUser_generate(arr[i].user, arr[i].pass, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(TestServerUser_delAndSetNull, (void *)&node);
			if ((*errp = Dz1AATree_insert(dst, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (TestServerUser_delAndSetNull, (void *)&node);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// TestServerUserList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestServerSessionSubscribe
typedef struct TestServerSessionSubscribe
{
	u32_t							 sub_id;
	TestMessage						*req;
	bool_t							 event_driven;
	bool_t							 enable;
} TestServerSessionSubscribe;

static void TestServerSessionSubscribe_del(TestServerSessionSubscribe *p)
{
	if (!p) return;
	TestMessage_delAndSetNull(&p->req);
	Dz1Free(p);
}

static void TestServerSessionSubscribe_delAndSetNull(void *pptr)
{
	TestServerSessionSubscribe **p = (TestServerSessionSubscribe **)pptr;
	TestServerSessionSubscribe_del(*p);
	*p = NULL;
}

static TestServerSessionSubscribe *TestServerSessionSubscribe_new(u32_t sub_id, TestMessage **req, bool_t is_event, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerSessionSubscribe *ret = NULL;
	
	if ((ret = (TestServerSessionSubscribe *)Dz1Calloc(sizeof(TestServerSessionSubscribe), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ret->sub_id = sub_id;
		if (req != NULL)
		{
			ret->req = *req;
			*req = NULL;
		}
		ret->event_driven = is_event;
		ret->enable = FALSE;
		ERR_CLEAR(errp);
	}
	return ret;
}

static TestServerSessionSubscribe *TestServerSessionSubscribe_clone(TestServerSessionSubscribe *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerSessionSubscribe *ret = TestServerSessionSubscribe_new(src->sub_id, NULL, src->event_driven, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerSessionSubscribe_delAndSetNull, (void *)&ret);

		if (src->req != NULL && (ret->req = TestMessage_clone(src->req, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->enable = src->enable;
			ERR_CLEAR(errp);
		}

		pthread_cleanup_pop(errp->code); // (TestServerSessionSubscribe_delAndSetNull, (void *)&ret);
	}

	return ret;
}

static void TestServerSessionSubscribe_dump(TestServerSessionSubscribe *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else
	{
		TCHAR en = p->enable ? Dz1Text('O') : Dz1Text('X');
		TCHAR ev = p->event_driven ? Dz1Text('E') : Dz1Text('P');
		Dz1Thread_printf(Dz1Text("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1Text("subscribe= %c.%u(%c)\n"), ev, p->sub_id, en);
		Dz1Thread_tprintf(tab, Dz1Text("req = ")); TestMessage_dump(p->req, tab);
		Dz1Thread_tprintf(--tab, Dz1Text("}\n"));
	}
}

static int TestServerSessionSubscribe_cmp(TestServerSessionSubscribe *a, TestServerSessionSubscribe *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if (a->sub_id < b->sub_id) ret = -1;
	else if (a->sub_id > b->sub_id) ret = 1;
	else ret = 0;
	return ret;
}
// TestServerSessionSubscribe
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestServerSessionSubscribeList
typedef Dz1AATree TestServerSessionSubscribeList;

static void TestServerSessionSubscribeList_del(TestServerSessionSubscribeList *p)
{
	if (!p) return;
	Dz1AATree_del(p);
}

static void TestServerSessionSubscribeList_delAndSetNull(void *pptr)
{
	TestServerSessionSubscribeList **p = (TestServerSessionSubscribeList **)pptr;
	TestServerSessionSubscribeList_del(*p);
	*p = NULL;
}

static TestServerSessionSubscribeList *TestServerSessionSubscribeList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerSessionSubscribeList *ret = Dz1AATree_new((Dz1CmpFunc)TestServerSessionSubscribe_cmp, (Dz1DelFunc)TestServerSessionSubscribe_del, (Dz1DumpFunc)TestServerSessionSubscribe_dump, errp);
	if (ret == NULL) ERR_OUT(errp);
	else ERR_CLEAR(errp);
	return ret;
}

static Dz1Error _TestServerSessionSubscribeList_clone(void *ptr, void *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestServerSessionSubscribeList *dst = (TestServerSessionSubscribeList *)ptr;
	TestServerSessionSubscribe *src = (TestServerSessionSubscribe *)data;
	TestServerSessionSubscribe *node = TestServerSessionSubscribe_clone(src, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerSessionSubscribe_delAndSetNull, (void **)&node);
		if (0) { }
		else if ((*errp = Dz1AATree_insert(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TestServerSessionSubscribe_delAndSetNull, (void **)&node);
	}
	return err;
}

static bool_t TestServerSessionSubscribeList_copy(TestServerSessionSubscribeList *dst, TestServerSessionSubscribeList *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1AATree_travel(src, _TestServerSessionSubscribeList_clone, (void *)dst)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static TestServerSessionSubscribeList *TestServerSessionSubscribeList_clone(TestServerSessionSubscribeList *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerSessionSubscribeList *ret = TestServerSessionSubscribeList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerSessionSubscribeList_delAndSetNull, (void *)&ret);

		if (TestServerSessionSubscribeList_copy(ret, src, errp) == FALSE) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestServerSessionSubscribeList_delAndSetNull, (void *)&ret);
	}

	return ret;
}

static void TestServerSessionSubscribeList_dump(TestServerSessionSubscribeList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1Text("{\n")); tab++;
		Dz1AATree_dump(p, tab);
		Dz1Thread_tprintf(--tab, Dz1Text("}\n"));
	}
}

static TestServerSessionSubscribe *TestServerSessionSubscribeList_add(TestServerSessionSubscribeList *dst, u32_t sub_id, TestMessage **req, bool_t is_event, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerSessionSubscribe *ret = NULL, *node = TestServerSessionSubscribe_new(sub_id, req, is_event, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerSessionSubscribe_delAndSetNull, (void **)&node);
		if (0) { }
		else if ((*errp = Dz1AATree_insert(dst, node)).code) ERR_OUT(errp);
		else
		{
			ret = node;
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TestServerSessionSubscribe_delAndSetNull, (void **)&node);
	}
	return ret;
}

static TestServerSessionSubscribe *TestServerSessionSubscribeList_find(TestServerSessionSubscribeList *list, u32_t sub_id)
{
	TestServerSessionSubscribe *ret = NULL;
	if (list != NULL)
	{
		TestServerSessionSubscribe key; // = { sub_id };
		key.sub_id = sub_id;
		ret = Dz1AATree_find(list, &key);
	}
	return ret;
}

static TestServerSessionSubscribe *TestServerSessionSubscribeList_extract(TestServerSessionSubscribeList *list, u32_t sub_id)
{
	TestServerSessionSubscribe *ret = NULL;
	if (list != NULL)
	{
		TestServerSessionSubscribe key; // = { sub_id };
		key.sub_id = sub_id;
		ret = Dz1AATree_extract(list, &key);
	}
	return ret;
}
// TestServerSessionSubscribeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestServerSession
typedef struct TestServerSession
{
	Dz1Asn1UTF8Str					*domain;
	Dz1Asn1OctetStr					*user;
	Dz1Asn1Codec					 codec;
	TestServerSessionSubscribeList	*subs;
} TestServerSession;

static void TestServerSession_del(TestServerSession *p)
{
	if (!p) return;
	Dz1Asn1UTF8Str_delAndSetNull(&p->domain);
	Dz1Asn1OctetStr_delAndSetNull(&p->user);
	TestServerSessionSubscribeList_delAndSetNull(&p->subs);
	Dz1Free(p);
}

static void TestServerSession_delAndSetNull(void *pptr)
{
	TestServerSession **p = (TestServerSession **)pptr;
	TestServerSession_del(*p);
	*p = NULL;
}

static TestServerSession *TestServerSession_new(Dz1Asn1UTF8Str *domain, Dz1Asn1OctetStr *user, Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerSession *ret = (TestServerSession *)Dz1Calloc(sizeof(TestServerSession), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerSession_delAndSetNull, (void *)&ret);

		if (0) { }
		else if ((ret->domain = Dz1Asn1UTF8Str_clone(domain, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->subs = TestServerSessionSubscribeList_new(errp)) == NULL) ERR_OUT(errp);
		else 
		{
			ret->codec = codec;
			ERR_CLEAR(errp);
		}

		pthread_cleanup_pop(errp->code); // (TestServerSession_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static TestServerSession *TestServerSession_clone(TestServerSession *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerSession *ret = TestServerSession_new(src->domain, src->user, src->codec, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerSession_delAndSetNull, (void *)&ret);

		if (TestServerSessionSubscribeList_copy(ret->subs, src->subs, errp) == FALSE) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestServerSession_delAndSetNull, (void *)&ret);
	}

	return ret;
}

static void TestServerSession_dump(TestServerSession *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1Text("{\n")); tab++;
		Dz1Thread_printf(Dz1Text("domain = ")); Dz1Asn1UTF8Str_dump(p->domain, tab);
		Dz1Thread_printf(Dz1Text("user = ")); Dz1Asn1OctetStr_dump(p->user, tab);
		Dz1Thread_printf(Dz1Text("codec = %s(%d)\n"), Dz1Asn1CodecStr(p->codec), p->codec);
		Dz1Thread_tprintf(--tab, Dz1Text("}\n"));
	}
}

static int TestServerSession_cmp(TestServerSession *a, TestServerSession *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->domain, b->domain)) != 0) { }
	else ret = Dz1Asn1OctetStr_cmp(a->user, b->user);
	return ret;
}
// TestServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestServerSessionList
typedef Dz1AATree TestServerSessionList;

static void TestServerSessionList_del(TestServerSessionList *p)
{
	if (!p) return;
	Dz1AATree_del(p);
}

static void TestServerSessionList_delAndSetNull(void *pptr)
{
	TestServerSessionList **p = (TestServerSessionList **)pptr;
	TestServerSessionList_del(*p);
	*p = NULL;
}

static TestServerSessionList *TestServerSessionList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	TestServerSessionList *ret = Dz1AATree_new((Dz1CmpFunc)TestServerSession_cmp, (Dz1DelFunc)TestServerSession_del, (Dz1DumpFunc)TestServerSession_dump, errp);
	if (ret == NULL) ERR_OUT(errp);
	else ERR_CLEAR(errp);

	return ret;
}

static Dz1Error _TestServerSessionList_clone(void *ptr, void *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestServerSessionList *dst = (TestServerSessionList *)ptr;
	TestServerSession *src = (TestServerSession *)data;
	TestServerSession *node = TestServerSession_clone(src, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerSession_delAndSetNull, (void **)&node);
		if (0) { }
		else if ((*errp = Dz1AATree_insert(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TestServerSession_delAndSetNull, (void **)&node);
	}
	return err;
}

static TestServerSessionList *TestServerSessionList_clone(TestServerSessionList *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerSessionList *ret = TestServerSessionList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerSessionList_delAndSetNull, (void *)&ret);

		if ((*errp = Dz1AATree_travel(src, _TestServerSessionList_clone, (void *)ret)).code) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (TestServerSessionList_delAndSetNull, (void *)&ret);
	}

	return ret;
}

static void TestServerSessionList_dump(TestServerSessionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1Text("{\n")); tab++;
		Dz1AATree_dump(p, tab);
		Dz1Thread_tprintf(--tab, Dz1Text("}\n"));
	}
}

static TestServerSession *TestServerSessionList_find(TestServerSessionList *list, Dz1Asn1UTF8Str *domain, Dz1Asn1OctetStr *user)
{
	TestServerSession *ret = NULL;
	if (list != NULL && domain != NULL && user != NULL)
	{
		TestServerSession key; // = { domain, user };
		key.domain = domain;
		key.user = user;
		ret = Dz1AATree_find(list, &key);
	}
	return ret;
}

static bool_t TestServerSessionList_add(TestServerSessionList *dst, Dz1Asn1UTF8Str *domain, Dz1Asn1OctetStr *user, Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerSession *node = TestServerSession_new(domain, user, codec, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerSession_delAndSetNull, (void **)&node);
		if (0) { }
		else if ((*errp = Dz1AATree_insert(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TestServerSession_delAndSetNull, (void **)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void TestServerSessionList_remove(TestServerSessionList *list, Dz1Asn1UTF8Str *domain, Dz1Asn1OctetStr *user)
{
	if (list != NULL && domain != NULL && user != NULL)
	{
		TestServerSession key; // = { domain, user };
		key.domain = domain;
		key.user = user;
		Dz1AATree_remove(list, &key);
	}
}
// TestServerSessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestServerArg API
typedef struct TestServerArg
{
	Dz1Asn1UTF8Str				*myDomain;
	u32_t						 max_client;
	TestServerUserList			*users;
} TestServerArg;

static void TestServerArg_del(TestServerArg *p)
{
	if (!p) return;
	Dz1Asn1UTF8Str_delAndSetNull(&p->myDomain);
	TestServerUserList_delAndSetNull(&p->users);
	Dz1Free(p);
}

static void TestServerArg_delAndSetNull(void *pptr)
{
	TestServerArg **p = (TestServerArg **)pptr;
	TestServerArg_del(*p);
	*p = NULL;
}

static TestServerArg *TestServerArg_new(Dz1Str myDomainStr, u32_t max_client, TestServerUserEntry users[], u32_t users_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerArg *ret = (TestServerArg *)Dz1Calloc(sizeof(TestServerArg), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerArg_delAndSetNull, (void *)&ret);

		if (0) { }
		else if ((ret->myDomain = Dz1Asn1UTF8Str_newFromStr(myDomainStr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->users = TestServerUserList_new(errp)) == NULL) ERR_OUT(errp);
		else if (TestServerUserList_load(ret->users, users, users_cnt, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			ret->max_client = max_client;
			ERR_CLEAR(errp);
		}

		pthread_cleanup_pop(errp->code); // (TestServerArg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TestServerArg_dump(TestServerArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1Text("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1Text("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab);
		Dz1Thread_tprintf(tab, Dz1Text("max_client = %u\n"), p->max_client);
		Dz1Thread_tprintf(tab, Dz1Text("users = ")); TestServerUserList_dump(p->users, tab);
		Dz1Thread_tprintf(--tab, Dz1Text("}\n"));
	}
}
// TestServerArg API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestServerEnv
typedef struct TestServerEnv
{
	void							*tSelf;
	Dz1Asn1UTF8Str					*myDomain;	// is ref
	TestServerSessionList			*sessions;
} TestServerEnv;

static void TestServerEnv_del(TestServerEnv *p)
{
	if (!p) return;
	TestServerSessionList_delAndSetNull(&p->sessions);
	Dz1Free(p);
}

static __inline__ void TestServerEnv_delAndSetNull(void *pptr)
{
	TestServerEnv **p = (TestServerEnv **)pptr;
	TestServerEnv_del(*p);
	*p = NULL;
}

static TestServerEnv *TestServerEnv_new(void *tSelf, Dz1Asn1UTF8Str *myDomain_ref, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerEnv *ret = (TestServerEnv *)Dz1Calloc(sizeof(TestServerEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerEnv_delAndSetNull, (void *)&ret);

		if (0) { }
		else if ((ret->sessions = TestServerSessionList_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->tSelf = tSelf;
			ret->myDomain = myDomain_ref;
			ERR_CLEAR(errp);
		}

		pthread_cleanup_pop(errp->code); // (TestServerEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TestServerEnv_dump(TestServerEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1Text("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1Text("sessions = ")); TestServerSessionList_dump(p->sessions, tab);
		Dz1Thread_tprintf(--tab, Dz1Text("}\n"));
	}
}
// TestServerEnv
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestServerTimer API
typedef struct TestServerTimer
{
	u32_t					id;
} TestServerTimer;

static void TestServerTimer_del(TestServerTimer *p)
{
	if (!p) return;
	Dz1Free(p);
}

static void TestServerTimer_delAndSetNull(void *pptr)
{
	TestServerTimer **p = (TestServerTimer **)pptr;
	TestServerTimer_del(*p);
	*p = NULL;
}

static TestServerTimer *TestServerTimer_new(u32_t id, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestServerTimer *ret = (TestServerTimer *)Dz1Calloc(sizeof(TestServerTimer), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->id = id;
		ERR_CLEAR(errp);
	}
	return ret;
}

void TestServerTimer_dump(TestServerTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else Dz1Thread_printf(Dz1Text("%u\n"), p->id);
}

int TestServerTimer_cmp(TestServerTimer *a, TestServerTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if (a->id < b->id) ret = -1;
	else if (a->id > b->id) ret = -1;
	else ret = 0;
	return ret;
}
// TestServerTimer API
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Execution
static Dz1Str _mk_timestamp_str(RequestServerTimeMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str ret = NULL;
	time_t tNow = time(NULL);
	struct tm *tm_p = localtime(&tNow);
	struct tm tmNow = *tm_p;
	TCHAR temp[64];
	switch(mode)
	{
	default:
	case RequestServerTimeMode_full:
		Dz1SNPRINTF(temp, 64, DZ1_TIME_TM_FMT_FULL, DZ1_TIME_TM_ARG_FULL(&tmNow));
		break;
	case RequestServerTimeMode_hhmmss:
		Dz1SNPRINTF(temp, 64, DZ1_TIME_TM_FMT_TIME, DZ1_TIME_TM_ARG_TIME(&tmNow));
		break;
	case RequestServerTimeMode_hhmm:
		Dz1SNPRINTF(temp, 64, Dz1Text("%02d:%02d"), tmNow.tm_hour, tmNow.tm_min);
		break;
	}
	if ((ret = Dz1Str_dup(temp, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

static TestMessage *TestServerEnv_execute_timestamp(RequestServerTime *req, Dz1Error *errp)
{
	TestMessage *ret = TestMessage_new(TestMessagePresent_timestamp_rsp, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ResponseServerTime *p = NULL;
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&ret);

		if ((ret->x.timestamp_rsp = p = ResponseServerTime_new(NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((p->formatted_timestr = _mk_timestamp_str(req->mode, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (ResponseMessage_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static TestMessage *TestServerEnv_execute(TestServerEnv *env, TestMessage *req, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = NULL;
	switch(req->present)
	{
	case TestMessagePresent_timestamp_req:
		if ((ret = TestServerEnv_execute_timestamp(req->x.timestamp_req, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EFAULT); break;
	}
	return ret;
}

static TestMessage *TestServerSessionSubscribe_execute(TestServerSessionSubscribe *p, bool_t is_initial, TestServerEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestMessage *ret = NULL;
	TestMessage *req = p->req;
	if (req == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = TestServerEnv_execute(env, req, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}
// Execution
///////////////////////////////////////////////////////////////////////////////

#define TEST_SERVER_MSG_DO_DEFAULT				0x00000001

static Dz1Error TestServer_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestServerArg *arg = (TestServerArg *)uArg;
	TestServerEnv *env = NULL;
	if (( (*uRsc) = env = TestServerEnv_new(tSelf, arg->myDomain, errp)) == NULL) ERR_OUT(errp);
	else
	{

		pthread_cleanup_push(TestServerEnv_delAndSetNull, (void *)uRsc);
		if ((*errp = Dz1Task_post(tSelf, my_queue_id, TEST_SERVER_MSG_DO_DEFAULT, NULL, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else if ((*errp = ItsIso14827_createServer4Task(my_queue_id, t14827, arg->myDomain, arg->max_client, NULL, 0)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (TestServerEnv_delAndSetNull, (void *)uRsc);
	}
	return err;
}

static void TestServer_cleanup(void *uRsc)
{
	TestServerEnv *env = (TestServerEnv *)uRsc;
	pthread_cleanup_push(TestServerEnv_delAndSetNull, (void *)&env);

	ItsIso14827_deleteServer(t14827, env->myDomain);

	pthread_cleanup_pop(1); // (TestServerEnv_delAndSetNull, (void *)&env);
}

static void TestServer_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Dz1Thread_printf(Dz1Text("!!! Test Server Exception\n"));
	ERR_OUT(reason);
}

static Dz1TaskProcStatus _test_server_do_default(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Authenticate
static Dz1Asn1Codec _select_codec(u8_t codec_bits)
{
	Dz1Asn1Codec ret = Dz1Asn1Codec_max;
	if (0) { }
	else if (codec_bits & DZ1_ASN1_CODEC_BIT_BER) ret = Dz1Asn1Codec_ber;
// 	else if (codec_bits & DZ1_ASN1_CODEC_BIT_APER) ret = Dz1Asn1Codec_aper;
// 	else if (codec_bits & DZ1_ASN1_CODEC_BIT_UPER) ret = Dz1Asn1Codec_uper;
	return ret;
}

#define LOGIN_REJECT(t14827, msgp, code)	ItsIso14827_loginReject(t14827, msgp->myDomain, msgp->peerDomain, msg->user, code)
static Dz1TaskProcStatus _test_server_authenticate(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{	// ItsIso14827_loginAccept | ItsIso14827_loginReject
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventAuth *msg = (ItsIso14827ServerEventAuth *)Dz1TaskSigMsg_getData(*sg);
	
	TestServerArg *arg = (TestServerArg *)uArg;
	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerUser *user_info = NULL;
	Dz1Asn1Codec codec = Dz1Asn1Codec_max;

	if (0) { }
	else if (TestServerSessionList_find(env->sessions, msg->peerDomain, msg->user) != NULL)	LOGIN_REJECT(t14827, msg, Iso14827RejectLogin_sessionExist);
	else if ((user_info = TestServerUserList_find(arg->users, msg->user)) == NULL)			LOGIN_REJECT(t14827, msg, Iso14827RejectLogin_accessDenied);
	else if (TestServerUser_chkPass(user_info, msg->pass) == FALSE)							LOGIN_REJECT(t14827, msg, Iso14827RejectLogin_accessDenied);
	else if (msg->hbDur < 3)																LOGIN_REJECT(t14827, msg, Iso14827RejectLogin_heartbeatTooSmall);
//	else if (msg->hbDur > 300)																LOGIN_REJECT(t14827, msg, Iso14827RejectLogin_heartbeatTooLarge);
	else if (msg->timeout < 3)																LOGIN_REJECT(t14827, msg, Iso14827RejectLogin_timeoutTooSmall);
//	else if (msg->timeout > 300)															LOGIN_REJECT(t14827, msg, Iso14827RejectLogin_timeoutTooLarge);
	else if ((codec = _select_codec(msg->codecBits)) == Dz1Asn1Codec_max)					LOGIN_REJECT(t14827, msg, Iso14827RejectLogin_other);
	else
	{
		if (msg->is_retried) Dz1Thread_printf("@@@ Login is retried\n");
		ItsIso14827_loginAccept(t14827, msg->myDomain, msg->peerDomain, msg->user, codec, ItsIso14827CRCCheck_warning); 
		Dz1Error_set(errp, 0);
	}
	return ret;
}
// Authenticate
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Established
static Dz1TaskProcStatus _test_server_established(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventConnected *msg = (ItsIso14827ServerEventConnected *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSessionList_add(env->sessions, msg->peerDomain, msg->user, msg->selected, NULL);

	return ret;
}
// Established
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Disconnected
static Dz1TaskProcStatus _test_server_disconnected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827EventDisconnected *msg = (ItsIso14827EventDisconnected *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSessionList_remove(env->sessions, msg->peerDomain, msg->user);

	return ret;
}
// Disconnected
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Echo Requested
static Dz1TaskProcStatus _test_server_echo_requested(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventEcho *msg = (ItsIso14827ServerEventEcho *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827_echoReply(t14827, msg->myDomain, msg->peerDomain, msg->user, msg->echoID);
	return ret;
}
// Echo Requested
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Single Subscribe
#define SINGLE_REJECT(tISO, msg, code)	ItsIso14827_singleReject(tISO, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, code)
static Dz1TaskProcStatus _test_server_single_subscribe(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventSubSignle *msg = (ItsIso14827ServerEventSubSignle *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSession *session = NULL;
	TestMessage *req = NULL;
	if ((session = TestServerSessionList_find(env->sessions, msg->peerDomain, msg->user)) == NULL)
	{
		Dz1Thread_printf(Dz1Text("sessions = ")); TestServerSessionList_dump(env->sessions, 0);
		Dz1Thread_printf(Dz1Text("peerDomain = ")); Dz1Asn1UTF8Str_dump(msg->peerDomain, 0);
		Dz1Thread_printf(Dz1Text("user = ")); Dz1Asn1OctetStr_dump(msg->user, 0);
		SINGLE_REJECT(t14827, msg, Iso14827RejectSubscription_other);
	}
	else if ((req = TestMessage_decode(msg->oidStr, msg->encodedEAM, msg->encodedEAMSize, session->codec, errp)) == NULL)
	{
		ERR_OUT(errp);
		switch(errp->code)
		{
		case ENOENT: SINGLE_REJECT(t14827, msg, Iso14827RejectSubscription_unknownSubscriptionMsgId); break;	// Unknown OID
		case ENOSYS: SINGLE_REJECT(t14827, msg, Iso14827RejectSubscription_invalidSubscriptionMsgId); break;	// Known but not supported
		case EINVAL: SINGLE_REJECT(t14827, msg, Iso14827RejectSubscription_invalidSubscriptionContent); break;	// decode fail
		default:	 SINGLE_REJECT(t14827, msg, Iso14827RejectSubscription_other); break;
		}
	}
	else 
	{
		TestMessage *rsp = NULL;
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&req);

		ItsIso14827_singleAccept(t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID);
		if ((rsp = TestServerEnv_execute(env, req, errp)) == NULL)
		{
			ERR_OUT(errp);
			ItsIso14827_dataControl(t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, Iso14827PublicationMgmt_terminatePublicationsBeingRejected);
		}
		else 
		{
			Dz1Str rsp_oid = NULL;
			Dz1Binary *bin = NULL;
			pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&rsp);
			if (0) { }
			else if ((bin = TestMessage_encode(rsp, session->codec, &rsp_oid, errp)) == NULL)
			{
				ERR_OUT(errp);
				ItsIso14827_dataControl(t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, Iso14827PublicationMgmt_terminatePublicationsBeingRejected);
			}
			else 
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
				ItsIso14827_dataProvide(t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, rsp_oid, bin->data, bin->size);
				Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
			}
			pthread_cleanup_pop(1); // (ResponseMessage_delAndSetNull, (void *)&rsp);
		}
		pthread_cleanup_pop(1); // (TestMessage_delAndSetNull, (void *)&req);
	}
	return ret;
}
// Single Subscribe
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Event-Driven Prepare
#define PREPARE_REJECT(tISO, msg, code) ItsIso14827_prepareReject(tISO, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, code)
static Dz1TaskProcStatus _test_server_event_prepare(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventSubPrepareED *msg = (ItsIso14827ServerEventSubPrepareED *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSession *session = NULL;
	TestServerSessionSubscribe *subscribe = NULL;
	TestMessage *req = NULL;
	if ((session = TestServerSessionList_find(env->sessions, msg->peerDomain, msg->user)) == NULL) PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_other);
	else if ((req = TestMessage_decode(msg->oidStr, msg->encodedEAM, msg->encodedEAMSize, session->codec, errp)) == NULL)
	{
		switch(errp->code)
		{
		case ENOENT: PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_unknownSubscriptionMsgId); break;		// Unknown OID
		case ENOSYS: PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_invalidSubscriptionMsgId); break;		// Known but not supported
		case EINVAL: PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_invalidSubscriptionContent); break;	// decode fail
		default:	 PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_other); break;
		}
	}
	else
	{
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&req);
		if ((subscribe = TestServerSessionSubscribeList_add(session->subs, msg->subID, &req, TRUE, errp)) == NULL) PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_other);
		else 
		{
			ItsIso14827_prepareAccept(t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (RequestMessage_delAndSetNull, (void *)&req);
	}
	return ret;
}
// Event-Driven Prepare
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Periodic Prepare
static Dz1TaskProcStatus _test_server_periodic_prepare(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventSubPrepareP *msg = (ItsIso14827ServerEventSubPrepareP *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSession *session = NULL;
	TestServerSessionSubscribe *subscribe = NULL;
	TestMessage *req = NULL;
	if ((session = TestServerSessionList_find(env->sessions, msg->peerDomain, msg->user)) == NULL) PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_other);
	else if ((req = TestMessage_decode(msg->oidStr, msg->encodedEAM, msg->encodedEAMSize, session->codec, errp)) == NULL)
	{
		switch(errp->code)
		{
		case ENOENT: PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_unknownSubscriptionMsgId); break;	// Unknown OID
		case ENOSYS: PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_invalidSubscriptionMsgId); break;	// Known but not supported
		case EINVAL: PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_invalidSubscriptionContent); break;	// decode fail
		default:	 PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_other); break;
		}
	}
	else
	{
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&req);
		if ((subscribe = TestServerSessionSubscribeList_add(session->subs, msg->subID, &req, FALSE, errp)) == NULL) PREPARE_REJECT(t14827, msg, Iso14827RejectSubscription_other);
		else 
		{
			ItsIso14827_prepareAccept(t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (RequestMessage_delAndSetNull, (void *)&req);
	}
	return ret;
}
// Periodic Prepare
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Pub Start
#define PUB_TERMINATE(tISO, msg, code)	ItsIso14827_dataControl(tISO, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, code)
static Dz1TaskProcStatus _test_server_publication_start(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubStart *msg = (ItsIso14827ServerEventPubStart *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSession *session = NULL;
	TestServerSessionSubscribe *subscribe = NULL;
	TestMessage *rsp = NULL;
	if ((session = TestServerSessionList_find(env->sessions, msg->peerDomain, msg->user)) == NULL)	PUB_TERMINATE(t14827, msg, Iso14827PublicationMgmt_terminatePublicationsBeingRejected);
	else if ((subscribe = TestServerSessionSubscribeList_find(session->subs, msg->subID)) == NULL)	PUB_TERMINATE(t14827, msg, Iso14827PublicationMgmt_terminatePublicationsBeingRejected);
	else if ((rsp = TestServerSessionSubscribe_execute(subscribe, TRUE, env, errp)) != NULL)
	{
		Dz1Str rsp_oid = NULL;
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&rsp);
		if (0) { }
		else if ((bin = TestMessage_encode(rsp, session->codec, &rsp_oid, errp)) != NULL)
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			ItsIso14827_dataProvide(t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, rsp_oid, bin->data, bin->size);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (ResponseMessage_delAndSetNull, (void *)&rsp);
	}
	return ret;
}
// Pub Start
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Pub Invocate
static Dz1TaskProcStatus _test_server_publication_invocate(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubStart *msg = (ItsIso14827ServerEventPubStart *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSession *session = NULL;
	TestServerSessionSubscribe *subscribe = NULL;
	TestMessage *rsp = NULL;
	Dz1Str rsp_oid = NULL;
	if ((session = TestServerSessionList_find(env->sessions, msg->peerDomain, msg->user)) == NULL)	PUB_TERMINATE(t14827, msg, Iso14827PublicationMgmt_terminatePublicationsBeingRejected);
	else if ((subscribe = TestServerSessionSubscribeList_find(session->subs, msg->subID)) == NULL)	PUB_TERMINATE(t14827, msg, Iso14827PublicationMgmt_terminatePublicationsBeingRejected);
	else if ((rsp = TestServerSessionSubscribe_execute(subscribe, FALSE, env, errp)) != NULL)
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(TestMessage_delAndSetNull, (void *)&rsp);
		if (0) { }
		else if ((bin = TestMessage_encode(rsp, session->codec, &rsp_oid, errp)) != NULL)
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			ItsIso14827_dataProvide(t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, rsp_oid, bin->data, bin->size);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (ResponseMessage_delAndSetNull, (void *)&rsp);
	}
	return ret;
}
// Pub Invocate
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Pub Inform
static Dz1TaskProcStatus _test_server_publication_inform(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubInform *msg = (ItsIso14827ServerEventPubInform *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSession *session = NULL;
	TestServerSessionSubscribe *subscribe = NULL;
	if ((session = TestServerSessionList_find(env->sessions, msg->peerDomain, msg->user)) == NULL) { }
	else if ((subscribe = TestServerSessionSubscribeList_extract(session->subs, msg->subID)) == NULL) { }
	else
	{
		ItsIso14827PublicarionError *reason = msg->reason;
		pthread_cleanup_push(TestServerSessionSubscribe_delAndSetNull, (void *)&subscribe);
		switch(reason->present)
		{
		case ItsIso14827PublicarionErrorPresent_pubError:
			switch(reason->x.pubError)
			{
			case Iso14827RejectPublication_other:
				break;
			case Iso14827RejectPublication_invalidPublishFormat:
				break;
			}
			break;
		case ItsIso14827PublicarionErrorPresent_pubDataError:
			switch(reason->x.pubDataError)
			{
			case Iso14827RejectPubDataReason_other:
			case Iso14827RejectPubDataReason_unknownSubscription:
			case Iso14827RejectPubDataReason_unknownPublicationNbr:
			case Iso14827RejectPubDataReason_unknownPublicationMsgId:
			case Iso14827RejectPubDataReason_invalidPublicationMsgId:
			case Iso14827RejectPubDataReason_invalidPublicationMsgContent:
			case Iso14827RejectPubDataReason_repeatedPublicationNbr:
			default:
				break;
			}
		default:
			break;
		}
		pthread_cleanup_pop(1); // (TestServerSessionSubscribe_delAndSetNull, (void *)&subscribe);
	}
	return ret;
}
// Pub Inform
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Pub Stopped(Paused)
static Dz1TaskProcStatus _test_server_publication_stopped(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubStop *msg = (ItsIso14827ServerEventPubStop *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSession *session = NULL;
	TestServerSessionSubscribe *subscribe = NULL;
	if ((session = TestServerSessionList_find(env->sessions, msg->peerDomain, msg->user)) == NULL) { }
	else if ((subscribe = TestServerSessionSubscribeList_find(session->subs, msg->subID)) == NULL) { }
	else
	{
		subscribe->enable = FALSE;
	}
	return ret;
}
// Pub Stopped(Paused)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Pub Expired(Terminated)
static Dz1TaskProcStatus _test_server_publication_expired(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubExpire *msg = (ItsIso14827ServerEventPubExpire *)Dz1TaskSigMsg_getData(*sg);

	TestServerEnv *env = (TestServerEnv *)uRsc;
	TestServerSession *session = NULL;
	TestServerSessionSubscribe *subscribe = NULL;
	if ((session = TestServerSessionList_find(env->sessions, msg->peerDomain, msg->user)) == NULL) { }
	else if ((subscribe = TestServerSessionSubscribeList_extract(session->subs, msg->subID)) == NULL) { }
	else
	{
		pthread_cleanup_push(TestServerSessionSubscribe_delAndSetNull, (void *)&subscribe);
		// XXX : do something
		pthread_cleanup_pop(1); // (TestServerSessionSubscribe_delAndSetNull, (void *)&subscribe);
	}
	return ret;
}
// Pub Expired(Terminated)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Server overload
static Dz1TaskProcStatus _test_server_overload(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	// publication latency is too large -> terminate subscription which has low priority

	return ret;
}
// Server overload
///////////////////////////////////////////////////////////////////////////////

void *TestServerTask_new(Dz1Str myDomainStr, u32_t max_client, TestServerUserEntry users[], u32_t users_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;

	TestServerArg *arg = TestServerArg_new(myDomainStr, max_client, users, users_cnt, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestServerArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("TestServer", 1024, (void **)&arg, (Dz1DelFunc)TestServerArg_del, (Dz1CmpFunc)TestServerTimer_cmp, 
								TestServer_init, TestServer_exception, TestServer_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ItsIso14827ServerTaskHandler handle = 
			{
				_test_server_authenticate,
				_test_server_established,
				_test_server_disconnected,
				_test_server_echo_requested,
				_test_server_single_subscribe,
				_test_server_event_prepare,
				_test_server_periodic_prepare,
				_test_server_publication_start,
				_test_server_publication_invocate,
				_test_server_publication_inform,
				_test_server_publication_stopped,
				_test_server_publication_expired,
				_test_server_overload
			};
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) { }
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(TEST_SERVER_MSG_DO_DEFAULT), _test_server_do_default)).code) ERR_OUT(errp);
			else if ((*errp = ItsIso14827_serverTaskMsgInit(ret, &handle)).code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (TestServerArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}
