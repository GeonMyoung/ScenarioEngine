#include "Iso14827TestHelperEnvUtil.h"
#include "Iso14827TestHelperMsg.h"



bool_t SubscribeSpecEntry_isSingle(SubscribeSpecEntry* p)
{
	bool_t ret = FALSE;
	SubscribeSpecType* type = NULL;
	if (p != NULL && (type = p->type) != NULL)
	{
		ret = type->present == SubscribeSpecTypePresent_single ? TRUE : FALSE;
	}
	return ret;
}

bool_t SubscribeSpecList_cloneAndAppend(SubscribeSpecList* dst, SubscribeSpecEntry* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SubscribeSpecEntry* node = NULL;
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((node = SubscribeSpecEntry_clone(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&node);
	}

	return ERR_IS_SUCCESS(errp);
}

SubscribeSpecEntry* SubscribeSpecList_findByOID(SubscribeSpecList* list, Dz1Str oid)
{
	SubscribeSpecEntry* ret = NULL;
	if (list != NULL)
	{
		SubscribeSpecEntry key = { oid };
		ret = list->find(list, &key);
	}
	return ret;
}


Iso14827TestSubType Iso14827TestSubType_getFromSubscribe(SubscribeSpecEntry* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Iso14827TestSubType ret = Iso14827TestSubType_max;
	SubscribeSpecType* type = NULL;

	if (src == NULL || (type = src->type) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		SubscribeSpecTypeRegistered* r = NULL;
		switch (type->present)
		{
		case SubscribeSpecTypePresent_single: ret = Iso14827TestSubType_single; break;
		case SubscribeSpecTypePresent_registered:
			if ((r = type->x.registered) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (r->is_periodic) ret = Iso14827TestSubType_periodic;
			else ret = Iso14827TestSubType_event_driven;
			break;
		}
	}
	return ret;
}


Iso14827TestSubEntry* Iso14827TestSubList_insert(Iso14827TestSubList* dst, Iso14827TestSubEntry** _node, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestSubEntry* node = NULL, * ret = NULL;
	if (dst == NULL || _node == NULL || (node = *_node) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		ret = *_node;
		*_node = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? ret : NULL;
}


Iso14827TestSubEntry* Iso14827TestSubList_append(Iso14827TestSubList* dst, Dz1Asn1UTF8Str* peer, u32_t sid, Dz1Str oidStr, Iso14827TestSubType type, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestSubEntry* node = NULL, * ret = NULL;
	if (dst == NULL || peer == NULL || Dz1Str_isVoid(oidStr) || sid == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Iso14827TestSubEntry_new(NULL, sid, oidStr, type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestSubEntry_delAndSetNull, (void*)&node);
		if ((node->peer = Dz1Asn1UTF8Str_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((ret = Iso14827TestSubList_insert(dst, &node, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Iso14827TestSubEntry_delAndSetNull, (void*)&node);
	}
	return errp->code == 0 ? ret : NULL;
}


Iso14827TestSubEntry* Iso14827TestSubList_findByID(Iso14827TestSubList* p, Dz1Asn1UTF8Str* peer, u32_t sid)
{
	Iso14827TestSubEntry* ret = NULL;
	if (p != NULL)
	{
		Iso14827TestSubEntry key = { peer, sid };
		ret = p->find(p, &key);
	}
	return ret;
}

typedef struct SubListFindByOIDArg
{
	Dz1Str						 oid;
	Iso14827TestSubEntry* ret;
} SubListFindByOIDArg;

static Dz1Error _Iso14827TestSubList_findByOID(void* ptr, Iso14827TestSubEntry* p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SubListFindByOIDArg* arg = (SubListFindByOIDArg*)ptr;
	if (Dz1STRCMP(p->oid, arg->oid) == 0)
	{
		arg->ret = p;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

Iso14827TestSubEntry* Iso14827TestSubList_findByOID(Iso14827TestSubList* p, Dz1Str oid)
{
	Iso14827TestSubEntry* ret = NULL;
	if (p != NULL && Dz1Str_isVoid(oid) == FALSE)
	{
		SubListFindByOIDArg arg = { oid, NULL };
		p->travel(p, _Iso14827TestSubList_findByOID, (void*)&arg);
		ret = arg.ret;
	}
	return ret;
}


void Iso14827TestSubList_removeByID(Iso14827TestSubList* p, Dz1Asn1UTF8Str* peer, u32_t sid)
{
	if (p != NULL)
	{
		Iso14827TestSubEntry key = { peer, sid };
		p->remove(p, &key);
	}
}

void Iso14827TestSubList_flush(Iso14827TestSubList* p)
{
	if (p != NULL)
	{
		Iso14827TestSubEntry* node = NULL;
		while ((node = p->getHead(p)) != NULL)
		{
			p->extract(p, node);
			Iso14827TestSubList_delAndSetNull(&node);
		}
	}
}



void _publication_log_dump_(Iso14827TestMsgStructAPI* msg_api, Dz1Str oidStr, u8_t* encodedEAM, u32_t encodedEAMSize, Dz1Asn1Codec selected_codec)
{
	Iso14827TestMsgStructAPI* api = NULL;
	Dz1Binary b = { encodedEAM, encodedEAMSize };
	if ((api = Iso14827TestMsgSet_findAPI(msg_api, oidStr, NULL)) != NULL)
	{
		void* decoded = api->struct_decode(&b, selected_codec, NULL);
		if (decoded != NULL)
		{
			pthread_cleanup_push(api->struct_delAndSetNull, (void*)&decoded);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication data = \n");
			Iso14827TestMsgStructAPI_dump(api, decoded, 0);
			pthread_cleanup_pop(1); // (api->struct_delAndSetNull, (void*)&decoded);
		}
	}

}


static struct UIConfigToTestScenario
{
	Dz1Str testScenario;
	Dz1Str ui_conf;
} ui2ts[] = {
	{Dz1T("prj2_rsuClient2ldm"),Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"key\":\"test_login_invalid\"},{\"title\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"key\":\"test_session_maintain\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험\",\"key\":\"test_normal_pub\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험 (MAP)\",\"key\":\"test_map\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험 (SPAT)\",\"key\":\"test_spat\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험 (SDSM)\",\"key\":\"test_sdsm\"},{\"title\":\"시나리오별시험 - 중복로그인 정보 처리\",\"key\":\"test_login_duplicate\"},{\"title\":\"시나리오별시험 - 서브스크립션 분석\",\"key\":\"test_invalid_sub\"},{\"title\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"key\":\"test_subs_cancel\"},{\"title\":\"시나리오별시험 - 재전송\",\"key\":\"test_pub_retry\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"RSU Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"LDM Domain 이름(destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 LDM IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 LDM Port 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"type\":\"checkbox\",\"name\":\"test_login_invalid\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 제공 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험\",\"type\":\"checkbox\",\"name\":\"test_normal_pub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 (MAP)\",\"type\":\"checkbox\",\"name\":\"test_map\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 (SPAT)\",\"type\":\"checkbox\",\"name\":\"test_spat\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 (SDSM)\",\"type\":\"checkbox\",\"name\":\"test_sdsm\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 중복로그인 정보 처리\",\"type\":\"checkbox\",\"name\":\"test_login_duplicate\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션 분석\",\"type\":\"checkbox\",\"name\":\"test_invalid_sub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"type\":\"checkbox\",\"name\":\"test_subs_cancel\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 재전송\",\"type\":\"checkbox\",\"name\":\"test_pub_retry\"}}]}]}]}]}")},
	{Dz1T("prj2_rsuServer2ldm"),Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 로그인패킷의 재전송\",\"key\":\"test_login_retry\"},{\"title\":\"정보요청기능시험 - 정보요청 기능시험 (PVD)\",\"key\":\"test_pvd\"},{\"title\":\"시나리오별시험 - 서브스크립션의 재전송\",\"key\":\"test_sub_retry\"},{\"title\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"key\":\"test_invalid_pub\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"RSU Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"LDM Domain 이름(destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 로그인패킷의 재전송\",\"type\":\"checkbox\",\"name\":\"test_login_retry\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 요청 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 (PVD)\",\"type\":\"checkbox\",\"name\":\"test_pvd\"}},{\"type\":\"Input\",\"option\":{\"label\":\"서브스크립션 만료 시간(최소180초)\",\"type\":\"number\",\"name\":\"subs_timeout_s\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션의 재전송\",\"type\":\"checkbox\",\"name\":\"test_sub_retry\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"type\":\"checkbox\",\"name\":\"test_invalid_pub\"}}]}]}]}]}")},

	// C2F
	// RSE-통합교통관제시스템 구간 RSE 정보 제공 시험 (BSM)
	{Dz1T("centerClient2rse"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"key\":\"test_login_invalid\"},{\"title\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"key\":\"test_session_maintain\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험\",\"key\":\"test_normal_pub\"},{\"title\":\"정보제공기능시험 - BSM 규격 검증 시험\",\"key\":\"test_bsm\"},{\"title\":\"시나리오별시험 - 중복로그인 정보 처리\",\"key\":\"test_login_duplicate\"},{\"title\":\"시나리오별시험 - 서브스크립션 분석\",\"key\":\"test_invalid_sub\"},{\"title\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"key\":\"test_subs_cancel\"},{\"title\":\"시나리오별시험 - 재전송\",\"key\":\"test_pub_retry\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합관제시스템 Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"대상 RSE Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속할 RSE IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속할 RSE Port 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"type\":\"checkbox\",\"name\":\"test_login_invalid\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 제공 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험\",\"type\":\"checkbox\",\"name\":\"test_normal_pub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"BSM 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_bsm\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 중복로그인 정보 처리\",\"type\":\"checkbox\",\"name\":\"test_login_duplicate\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션 분석\",\"type\":\"checkbox\",\"name\":\"test_invalid_sub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"type\":\"checkbox\",\"name\":\"test_subs_cancel\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 재전송\",\"type\":\"checkbox\",\"name\":\"test_pub_retry\"}}]}]}]}]}")},
	// RSE-통합교통관제시스템 구간 통합교통관제시스템 정보 요청 시험 (BSM)
	{Dz1T("rseServer2center"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 로그인패킷의 재전송\",\"key\":\"test_login_retry\"},{\"title\":\"정보요청기능시험 - 정보요청 기능시험 (BSM)\",\"key\":\"test_bsm\"},{\"title\":\"시나리오별시험 - 서브스크립션의 재전송\",\"key\":\"test_sub_retry\"},{\"title\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"key\":\"test_invalid_pub\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"RSE Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"대상 통합교통관제시스템 Domain 이름(destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 로그인패킷의 재전송\",\"type\":\"checkbox\",\"name\":\"test_login_retry\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 요청 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 (BSM)\",\"type\":\"checkbox\",\"name\":\"test_bsm\"}},{\"type\":\"Input\",\"option\":{\"label\":\"서브스크립션 만료 시간(최소 180초)\",\"type\":\"number\",\"name\":\"subs_timeout_s\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션의 재전송\",\"type\":\"checkbox\",\"name\":\"test_sub_retry\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"type\":\"checkbox\",\"name\":\"test_invalid_pub\"}}]}]}]}]}")},

	// 통합교통관제시스템-RSE 구간 통합교통관제시스템 정보 제공 시험 (MAP, RSA, TIM)
	{Dz1T("rseClient2center"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"key\":\"test_login_invalid\"},{\"title\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"key\":\"test_session_maintain\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험\",\"key\":\"test_normal_pub\"},{\"title\":\"정보제공기능시험 - MAP 규격 검증 시험\",\"key\":\"test_map\"},{\"title\":\"정보제공기능시험 - RSA 규격 검증 시험\",\"key\":\"test_rsa\"},{\"title\":\"정보제공기능시험 - TIM 규격 검증 시험\",\"key\":\"test_tim\"},{\"title\":\"시나리오별시험 - 중복로그인 정보 처리\",\"key\":\"test_login_duplicate\"},{\"title\":\"시나리오별시험 - 서브스크립션 분석\",\"key\":\"test_invalid_sub\"},{\"title\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"key\":\"test_subs_cancel\"},{\"title\":\"시나리오별시험 - 재전송\",\"key\":\"test_pub_retry\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"RSE Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"대상 통합교통관제시스템 Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"통합교통관제시스템 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"통합교통관제시스템 Port 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"type\":\"checkbox\",\"name\":\"test_login_invalid\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 제공 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험\",\"type\":\"checkbox\",\"name\":\"test_normal_pub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"MAP 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_map\"}},{\"type\":\"Input\",\"option\":{\"label\":\"RSA 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_rsa\"}},{\"type\":\"Input\",\"option\":{\"label\":\"TIM 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_tim\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 중복로그인 정보 처리\",\"type\":\"checkbox\",\"name\":\"test_login_duplicate\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션 분석\",\"type\":\"checkbox\",\"name\":\"test_invalid_sub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"type\":\"checkbox\",\"name\":\"test_subs_cancel\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 재전송\",\"type\":\"checkbox\",\"name\":\"test_pub_retry\"}}]}]}]}]}")},
	// 통합교통관제시스템-RSE 구간 RSE 정보 제공 시험 (MAP, RSA, TIM)
	{Dz1T("centerServer2rse"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 로그인패킷의 재전송\",\"key\":\"test_login_retry\"},{\"title\":\"정보요청기능시험 - 정보요청 기능시험 (MAP)\",\"key\":\"test_map\"},{\"title\":\"정보요청기능시험 - 정보요청 기능시험 (RSA)\",\"key\":\"test_rsa\"},{\"title\":\"정보요청기능시험 - 정보요청 기능시험 (TIM)\",\"key\":\"test_tim\"},{\"title\":\"시나리오별시험 - 서브스크립션의 재전송\",\"key\":\"test_sub_retry\"},{\"title\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"key\":\"test_invalid_pub\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합교통관제시스템 Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"대상 RSE Domain 이름(destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 로그인패킷의 재전송\",\"type\":\"checkbox\",\"name\":\"test_login_retry\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 요청 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 (MAP)\",\"type\":\"checkbox\",\"name\":\"test_map\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 (RSA)\",\"type\":\"checkbox\",\"name\":\"test_rsa\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 (TIM)\",\"type\":\"checkbox\",\"name\":\"test_tim\"}},{\"type\":\"Input\",\"option\":{\"label\":\"서브스크립션 만료 시간(최소 180초)\",\"type\":\"number\",\"name\":\"subs_timeout_s\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션의 재전송\",\"type\":\"checkbox\",\"name\":\"test_sub_retry\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"type\":\"checkbox\",\"name\":\"test_invalid_pub\"}}]}]}]}]}")},

	// C2C
	// 신호수집서버-통합교통관제시스템 구간 신호정보수집서버 정보 제공 시험 (SPaT, TLSM)
	{Dz1T("centerClient2sigsnalserver"), Dz1T("")},
	// 신호수집서버-통합교통관제시스템 구간 통합교통관제시스템 정보 요청 시험 (SPaT, TLSM)
	{Dz1T("signalserverServer2center"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 로그인패킷의 재전송\",\"key\":\"test_login_retry\"},{\"title\":\"정보요청기능시험 - 정보요청 기능시험 (SPaT)\",\"key\":\"test_spat\"},{\"title\":\"정보요청기능시험 - 정보요청 기능시험 (TLS)\",\"key\":\"test_tls\"},{\"title\":\"시나리오별시험 - 서브스크립션의 재전송\",\"key\":\"test_sub_retry\"},{\"title\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"key\":\"test_invalid_pub\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"신호정보 수집서버 Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"대상 통합교통관제시스템 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 로그인패킷의 재전송\",\"type\":\"checkbox\",\"name\":\"test_login_retry\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 요청 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 (SPaT)\",\"type\":\"checkbox\",\"name\":\"test_spat\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 (TLS)\",\"type\":\"checkbox\",\"name\":\"test_tls\"}},{\"type\":\"Input\",\"option\":{\"label\":\"서브스크립션 만료 시간(최소 180초)\",\"type\":\"number\",\"name\":\"subs_timeout_s\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션의 재전송\",\"type\":\"checkbox\",\"name\":\"test_sub_retry\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"type\":\"checkbox\",\"name\":\"test_invalid_pub\"}}]}]}]}]}")},
	// ITSK-00100-3
	{Dz1T("itsk-00100-3-clientRole"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"key\":\"test_login_invalid\"},{\"title\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"key\":\"test_session_maintain\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험\",\"key\":\"test_normal_pub\"},{\"title\":\"정보제공기능시험 - 돌발상황검지정보\",\"key\":\"test_pub_incident_detection_info\"},{\"title\":\"정보제공기능시험 - 돌발상황해지정보\",\"key\":\"test_pub_incident_termination_info\"},{\"title\":\"정보제공기능시험 - 돌발검지영상\",\"key\":\"test_pub_incident_detection_video_file_info_provide\"},{\"title\":\"정보제공기능시험 - 제어부상태정보\",\"key\":\"test_pub_control_state_info\"},{\"title\":\"정보제공기능시험 - 센서부상태정보\",\"key\":\"test_pub_sensor_state_info\"},{\"title\":\"정보제공기능시험 - 이동체 검지기 정보\",\"key\":\"test_pub_moving_object\"},{\"title\":\"시나리오별시험 - 중복로그인 정보 처리\",\"key\":\"test_login_duplicate\"},{\"title\":\"시나리오별시험 - 서브스크립션 분석\",\"key\":\"test_invalid_sub\"},{\"title\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"key\":\"test_subs_cancel\"},{\"title\":\"시나리오별시험 - 재전송\",\"key\":\"test_pub_retry\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 포트 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"type\":\"checkbox\",\"name\":\"test_login_invalid\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 제공 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험\",\"type\":\"checkbox\",\"name\":\"test_normal_pub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 돌발상황검지정보\",\"type\":\"checkbox\",\"name\":\"test_pub_incident_detection_info\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 돌발상황해지정보\",\"type\":\"checkbox\",\"name\":\"test_pub_incident_termination_info\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 돌발검지영상\",\"type\":\"checkbox\",\"name\":\"test_pub_incident_detection_video_file_info_provide\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 제어부상태정보\",\"type\":\"checkbox\",\"name\":\"test_pub_control_state_info\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 센서부상태정보\",\"type\":\"checkbox\",\"name\":\"test_pub_sensor_state_info\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 이동체 검지기 정보\",\"type\":\"checkbox\",\"name\":\"test_pub_moving_object\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 중복로그인 정보 처리\",\"type\":\"checkbox\",\"name\":\"test_login_duplicate\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션 분석\",\"type\":\"checkbox\",\"name\":\"test_invalid_sub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"type\":\"checkbox\",\"name\":\"test_subs_cancel\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 재전송\",\"type\":\"checkbox\",\"name\":\"test_pub_retry\"}}]}]}]}]}")},

	// 기본교통정보교환 기술기준 1
	{Dz1T("TechnicalRegulation1-clientRole1"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"key\":\"test_login_invalid\"},{\"title\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"key\":\"test_session_maintain\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험\",\"key\":\"test_normal_pub\"},{\"title\":\"정보제공기능시험 - 교통소통정보\",\"key\":\"test_pub_current_link_state\"},{\"title\":\"정보제공기능시험 - 교통통제정보\",\"key\":\"test_pub_event_identity\"},{\"title\":\"정보제공기능시험 - 돌발상황 발생정보\",\"key\":\"test_pub_incident_identity\"},{\"title\":\"정보제공기능시험 - 돌발상황정보\",\"key\":\"test_pub_incident_conditions\"},{\"title\":\"정보제공기능시험 - 도로상태정보\",\"key\":\"test_pub_roadway_surface_status\"},{\"title\":\"정보제공기능시험 - 기상정보\",\"key\":\"test_pub_weather_information\"},{\"title\":\"정보제공기능시험 - 도로관리정보\",\"key\":\"test_pub_link_roadway_geometry\"},{\"title\":\"정보제공기능시험 - 프로브정보\",\"key\":\"test_pub_probe_vehicle_detection\"},{\"title\":\"정보제공기능시험 - 차량검지정보\",\"key\":\"test_pub_detector_collection\"},{\"title\":\"정보제공기능시험 - 확장 교통정보\",\"key\":\"test_pub_extention_comm_pdu\"},{\"title\":\"시나리오별시험 - 중복로그인 정보 처리\",\"key\":\"test_login_duplicate\"},{\"title\":\"시나리오별시험 - 서브스크립션 분석\",\"key\":\"test_invalid_sub\"},{\"title\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"key\":\"test_subs_cancel\"},{\"title\":\"시나리오별시험 - 재전송\",\"key\":\"test_pub_retry\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 포트 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"type\":\"checkbox\",\"name\":\"test_login_invalid\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 제공 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험\",\"type\":\"checkbox\",\"name\":\"test_normal_pub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 교통소통정보\",\"type\":\"checkbox\",\"name\":\"test_pub_current_link_state\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 교통통제정보\",\"type\":\"checkbox\",\"name\":\"test_pub_event_identity\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 돌발상황 발생정보\",\"type\":\"checkbox\",\"name\":\"test_pub_incident_identity\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 돌발상황정보\",\"type\":\"checkbox\",\"name\":\"test_pub_incident_conditions\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 도로상태정보\",\"type\":\"checkbox\",\"name\":\"test_pub_roadway_surface_status\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 기상정보\",\"type\":\"checkbox\",\"name\":\"test_pub_weather_information\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 도로관리정보\",\"type\":\"checkbox\",\"name\":\"test_pub_link_roadway_geometry\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 프로브정보\",\"type\":\"checkbox\",\"name\":\"test_pub_probe_vehicle_detection\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 차량검지정보\",\"type\":\"checkbox\",\"name\":\"test_pub_detector_collection\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 확장 교통정보\",\"type\":\"checkbox\",\"name\":\"test_pub_extention_comm_pdu\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 중복로그인 정보 처리\",\"type\":\"checkbox\",\"name\":\"test_login_duplicate\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션 분석\",\"type\":\"checkbox\",\"name\":\"test_invalid_sub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"type\":\"checkbox\",\"name\":\"test_subs_cancel\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 재전송\",\"type\":\"checkbox\",\"name\":\"test_pub_retry\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation1-serverRole1"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 로그인패킷의 재전송\",\"key\":\"test_login_retry\"},{\"title\":\"정보요청 기능시험\",\"key\":\"test_normal_sub\"},{\"title\":\"시나리오별시험 - 서브스크립션의 재전송\",\"key\":\"test_sub_retry\"},{\"title\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"key\":\"test_invalid_pub\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름(destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 로그인패킷의 재전송\",\"type\":\"checkbox\",\"name\":\"test_login_retry\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 요청 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험\",\"type\":\"checkbox\",\"name\":\"test_normal_sub\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션의 재전송\",\"type\":\"checkbox\",\"name\":\"test_sub_retry\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"type\":\"checkbox\",\"name\":\"test_invalid_pub\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation2-serverRole1"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 로그인패킷의 재전송\",\"key\":\"test_login_retry\"},{\"title\":\"정보요청 기능시험\",\"key\":\"test_normal_sub\"},{\"title\":\"시나리오별시험 - 서브스크립션의 재전송\",\"key\":\"test_sub_retry\"},{\"title\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"key\":\"test_invalid_pub\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름(destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 로그인패킷의 재전송\",\"type\":\"checkbox\",\"name\":\"test_login_retry\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 요청 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험\",\"type\":\"checkbox\",\"name\":\"test_normal_sub\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션의 재전송\",\"type\":\"checkbox\",\"name\":\"test_sub_retry\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"type\":\"checkbox\",\"name\":\"test_invalid_pub\"}}]}]}]}]}")},
		/*{Dz1T("TechnicalRegulation1-serverRole1"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 로그인패킷의 재전송\",\"key\":\"test_login_retry\"},{\"title\":\"정보요청기능시험 - 교통소통정보\",\"key\":\"test_sub_current_link_state\"},{\"title\":\"정보요청기능시험 - 교통통제정보\",\"key\":\"test_sub_event_identity\"},{\"title\":\"정보요청기능시험 - 돌발상황 발생정보\",\"key\":\"test_sub_incident_identity\"},{\"title\":\"정보요청기능시험 - 돌발상황정보\",\"key\":\"test_sub_incident_conditions\"},{\"title\":\"정보요청기능시험 - 도로상태정보\",\"key\":\"test_sub_roadway_surface_status\"},{\"title\":\"정보요청기능시험 - 기상정보\",\"key\":\"test_sub_weather_information\"},{\"title\":\"정보요청기능시험 - 도로관리정보\",\"key\":\"test_sub_link_roadway_geometry\"},{\"title\":\"정보요청기능시험 - 프로브정보\",\"key\":\"test_sub_probe_vehicle_detection\"},{\"title\":\"정보요청기능시험 - 차량검지정보\",\"key\":\"test_sub_detector_collection\"},{\"title\":\"정보요청기능시험 - 확장 교통정보\",\"key\":\"test_sub_extention_comm_pdu\"},{\"title\":\"시나리오별시험 - 서브스크립션의 재전송\",\"key\":\"test_sub_retry\"},{\"title\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"key\":\"test_invalid_pub\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름(destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 로그인패킷의 재전송\",\"type\":\"checkbox\",\"name\":\"test_login_retry\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 요청 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 교통소통정보\",\"type\":\"checkbox\",\"name\":\"test_sub_current_link_state\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 교통통제정보\",\"type\":\"checkbox\",\"name\":\"test_sub_event_identity\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 돌발상황 발생정보\",\"type\":\"checkbox\",\"name\":\"test_sub_incident_identity\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 돌발상황정보\",\"type\":\"checkbox\",\"name\":\"test_sub_incident_conditions\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 도로상태정보\",\"type\":\"checkbox\",\"name\":\"test_sub_roadway_surface_status\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 기상정보\",\"type\":\"checkbox\",\"name\":\"test_sub_weather_information\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 도로관리정보\",\"type\":\"checkbox\",\"name\":\"test_sub_link_roadway_geometry\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 프로브정보\",\"type\":\"checkbox\",\"name\":\"test_sub_probe_vehicle_detection\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 차량검지정보\",\"type\":\"checkbox\",\"name\":\"test_sub_detector_collection\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보요청 기능시험 - 확장 교통정보\",\"type\":\"checkbox\",\"name\":\"test_sub_extention_comm_pdu\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션의 재전송\",\"type\":\"checkbox\",\"name\":\"test_sub_retry\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 유효하지 않은 퍼블리케이션 패킷\",\"type\":\"checkbox\",\"name\":\"test_invalid_pub\"}}]}]}]}]}")},*/
	{Dz1T("TechnicalRegulation1-clientRole1"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"key\":\"test_login_invalid\"},{\"title\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"key\":\"test_session_maintain\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험\",\"key\":\"test_normal_pub\"},{\"title\":\"정보제공기능시험 - 교통제공정보\",\"key\":\"test_pub_comm_tx_pdu\"},{\"title\":\"정보제공기능시험 - 교통수집정보\",\"key\":\"test_pub_comm_rx_pdu\"},{\"title\":\"시나리오별시험 - 재전송\",\"key\":\"test_pub_retry\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 포트 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"type\":\"checkbox\",\"name\":\"test_login_invalid\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 제공 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험\",\"type\":\"checkbox\",\"name\":\"test_normal_pub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 교통제공정보\",\"type\":\"checkbox\",\"name\":\"test_pub_comm_tx_pdu\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 교통수집정보\",\"type\":\"checkbox\",\"name\":\"test_pub_comm_rx_pdu\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 중복로그인 정보 처리\",\"type\":\"checkbox\",\"name\":\"test_login_duplicate\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션 분석\",\"type\":\"checkbox\",\"name\":\"test_invalid_sub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"type\":\"checkbox\",\"name\":\"test_subs_cancel\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 재전송\",\"type\":\"checkbox\",\"name\":\"test_pub_retry\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation1-serverRole2"),Dz1T("{\"scenarios\":[{\"title\":\"통합시험 - 정보요청통합시험\",\"key\":\"test_total\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름(destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"통합시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합시험 - 정보요청통합시험\",\"type\":\"checkbox\",\"name\":\"test_total\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보 요청 만료 시간(최소 180초)\",\"type\":\"number\",\"name\":\"subs_timeout_s\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation1-clientRole2"),Dz1T("{\"scenarios\":[{\"title\":\"통합시험 - 정보제공통합시험\",\"key\":\"test_total\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 포트 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"통합시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합시험 - 정보제공통합시험\",\"type\":\"checkbox\",\"name\":\"test_total\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보 요청 만료 시간(최소 180초)\",\"type\":\"number\",\"name\":\"expire_time\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation1-duoClientRole"),Dz1T("{\"scenarios\":[{\"title\":\"통합시험 - 다중세션 설정\",\"key\":\"test_duo_client\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"시험 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합시험 - 다중세션 설정\",\"type\":\"checkbox\",\"name\":\"test_duo_client\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"접속 대상 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 Port 번호\",\"type\":\"number\",\"name\":\"peer_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"Client Domain 1 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Client 1 Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain1\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user1\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass1\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"Client Domain 2 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Client 2 Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain2\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user2\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass2\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation1-duoSessionRole"),Dz1T("{\"scenarios\":[{\"title\":\"통합시험 - 병행세션 설정\",\"key\":\"test_duo_session\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"시험 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합시험 - 병행세션 설정\",\"type\":\"checkbox\",\"name\":\"test_duo_session\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"공통 세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"Client Domain 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"대상 Server Domain 이름\",\"type\":\"text\",\"name\":\"peer_server_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 Server Port 번호\",\"type\":\"number\",\"name\":\"peer_server_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"Server Domain 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"대상 Client Domain 이름\",\"type\":\"text\",\"name\":\"peer_client_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속  대상 Client Port번호\",\"type\":\"number\",\"name\":\"peer_client_port\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation2-clientRole1"), Dz1T("{\"scenarios\":[{\"title\":\"기본기능시험 - 세션 설정\",\"key\":\"test_session\"},{\"title\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"key\":\"test_login_invalid\"},{\"title\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"key\":\"test_session_maintain\"},{\"title\":\"정보제공기능시험 - 정보제공 기능시험\",\"key\":\"test_normal_pub\"},{\"title\":\"정보제공기능시험 - 교통제공정보\",\"key\":\"test_pub_comm_tx_pdu\"},{\"title\":\"정보제공기능시험 - 교통수집정보\",\"key\":\"test_pub_comm_rx_pdu\"},{\"title\":\"시나리오별시험 - 재전송\",\"key\":\"test_pub_retry\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 포트 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"기본 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 세션 설정\",\"type\":\"checkbox\",\"name\":\"test_session\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부\",\"type\":\"checkbox\",\"name\":\"test_login_invalid\"}},{\"type\":\"Input\",\"option\":{\"label\":\"기본기능시험 - 비정상적 세션 연결 감지\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"정보 제공 기능 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험\",\"type\":\"checkbox\",\"name\":\"test_normal_pub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 교통제공정보\",\"type\":\"checkbox\",\"name\":\"test_pub_comm_tx_pdu\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보제공 기능시험 - 교통수집정보\",\"type\":\"checkbox\",\"name\":\"test_pub_comm_rx_pdu\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시나리오별 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 중복로그인 정보 처리\",\"type\":\"checkbox\",\"name\":\"test_login_duplicate\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션 분석\",\"type\":\"checkbox\",\"name\":\"test_invalid_sub\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소\",\"type\":\"checkbox\",\"name\":\"test_subs_cancel\"}},{\"type\":\"Input\",\"option\":{\"label\":\"시나리오별시험 - 재전송\",\"type\":\"checkbox\",\"name\":\"test_pub_retry\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation2-serverRole2"),Dz1T("{\"scenarios\":[{\"title\":\"통합시험 - 정보요청통합시험\",\"key\":\"test_total\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름(destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"통합시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합시험 - 정보요청통합시험\",\"type\":\"checkbox\",\"name\":\"test_total\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보 요청 만료 시간(최소 180초)\",\"type\":\"number\",\"name\":\"subs_timeout_s\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation2-clientRole2"),Dz1T("{\"scenarios\":[{\"title\":\"통합시험 - 정보제공통합시험\",\"key\":\"test_total\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 포트 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"통합시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합시험 - 정보제공통합시험\",\"type\":\"checkbox\",\"name\":\"test_total\"}},{\"type\":\"Input\",\"option\":{\"label\":\"정보 요청 만료 시간(최소 180초)\",\"type\":\"number\",\"name\":\"expire_time\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation2-duoClientRole"),Dz1T("{\"scenarios\":[{\"title\":\"통합시험 - 다중세션 설정\",\"key\":\"test_duo_client\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"시험 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합시험 - 다중세션 설정\",\"type\":\"checkbox\",\"name\":\"test_duo_client\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"접속 대상 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Peer Domain 이름 (destination)\",\"type\":\"text\",\"name\":\"peer_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 Port 번호\",\"type\":\"number\",\"name\":\"peer_port\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"Client Domain 1 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Client 1 Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain1\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user1\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass1\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"Client Domain 2 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Client 2 Domain 이름 (sender)\",\"type\":\"text\",\"name\":\"my_domain2\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user2\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass2\"}}]}]}]}]}")},
	{Dz1T("TechnicalRegulation2-duoSessionRole"),Dz1T("{\"scenarios\":[{\"title\":\"통합시험 - 병행세션 설정\",\"key\":\"test_duo_session\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"시험 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"통합시험 - 병행세션 설정\",\"type\":\"checkbox\",\"name\":\"test_duo_session\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"공통 세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"Local Domain 이름\",\"type\":\"text\",\"name\":\"my_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"Client Domain 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"대상 Server Domain 이름\",\"type\":\"text\",\"name\":\"peer_server_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 Server Port 번호\",\"type\":\"number\",\"name\":\"peer_server_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"ID\",\"type\":\"text\",\"name\":\"user\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PW\",\"type\":\"text\",\"name\":\"pass\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"Server Domain 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"대상 Client Domain 이름\",\"type\":\"text\",\"name\":\"peer_client_domain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속  대상 Client Port번호\",\"type\":\"number\",\"name\":\"peer_client_port\"}}]}]}]}]}")},
	// tbd .. 20260105
	{NULL, NULL}
};

static Dz1Str _get_ui_config_from_test_sceanrio(Dz1Str testScenario)
{
	struct UIConfigToTestScenario* i;
	for (i = ui2ts; i->testScenario; i++)
	{
		if (Dz1STRCMP(i->testScenario, testScenario) == 0)
			return i->ui_conf;
	}
	return NULL;
}

bool_t Iso14827TestHelperEnvUtil_sendUIConfigure(Iso14827TestHelperEnv* env, Dz1Str testScenario, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (env == NULL || testScenario == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Str ui_conf = NULL;
		if ((ui_conf = _get_ui_config_from_test_sceanrio(testScenario)) == NULL)
		{
			// notify error
			// unknown testSceanrio
			ERR_SET_OUT(errp, EFAULT);
		}
		else if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_UI_CONFIGURE, (void*)&ui_conf, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}


bool_t Iso14827TestHelperEnvUtil_notifyState(Iso14827TestHelperEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL || testName == NULL || state == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Iso14827TestNotifyStateArg* arg = NULL;
		if ((arg = Iso14827TestNotifyStateArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827TestNotifyStateContext* context = NULL;
			pthread_cleanup_push(Iso14827TestNotifyStateArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = Iso14827TestNotifyStateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
			else
			{
				context->time = time(NULL);
				if (errp->code == 0)
					if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_NOTIFY_STATE, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
			}
			pthread_cleanup_pop(1); // (Iso14827TestNotifyStateArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Iso14827TestHelperEnvUtil_notifyInfo(Iso14827TestHelperEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Iso14827TestNotifyInfoArg* arg = NULL;
		if ((arg = Iso14827TestNotifyInfoArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827TestNotifyInfoContext* context = NULL;
			pthread_cleanup_push(Iso14827TestNotifyInfoArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = Iso14827TestNotifyInfoContext_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				if (log != NULL)
				{
					if ((context->log = Dz1Str_clone(log, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (testName != NULL)
				{
					if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (sender != NULL)
				{
					if ((context->sender = Dz1Str_clone(sender, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (data != NULL)
				{
					if (dataType != NULL)
					{
						if ((context->dataType = Dz1Str_clone(dataType, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					if ((context->data = Dz1Binary_clone(data, errp)) == NULL) ERR_OUT(errp);
					else  Dz1Error_set(errp, 0);
				}
				context->time = time(NULL);
			}

			if (errp->code == 0)
			{
				if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_NOTIFY_INFO, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (Iso14827TestNotifyInfoArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Iso14827TestHelperEnvUtil_notifyError(Iso14827TestHelperEnv* env, Dz1Str testName, Iso14827TestProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Iso14827TestNotifyErrorArg* arg = NULL;
		if ((arg = Iso14827TestNotifyErrorArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827TestNotifyErrorContext* context = NULL;
			pthread_cleanup_push(Iso14827TestNotifyErrorArg_delAndSetNull, (void*)&arg);

			if ((context = Iso14827TestNotifyErrorContext_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				if (log != NULL)
				{
					if ((context->log = Dz1Str_clone(log, errp)) == NULL) ERR_OUT(errp);
					Dz1Error_set(errp, 0);
				}
				if (testName != NULL)
				{
					if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (desc != NULL)
				{
					if ((context->desc = Dz1Str_clone(desc, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (data != NULL)
				{
					if ((context->data = Dz1Binary_clone(data, errp)) == NULL) ERR_OUT(errp);
					else  Dz1Error_set(errp, 0);
				}

				context->time = time(NULL);
				context->code = code;

				if (errp->code == 0)
				{
					if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_NOTIFY_ERROR, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
				}
			}
			pthread_cleanup_pop(1); // (Iso14827TestNotifyErrorArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Iso14827TestHelperEnvUtil_validateRequest(Iso14827TestHelperEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, Iso14827TestProcessStatusCode code, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Iso14827TestValidateContextArg* arg = NULL;
		if ((arg = Iso14827TestValidateContextArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827TestValidateContext* context = NULL;
			pthread_cleanup_push(Iso14827TestValidateContextArg_delAndSetNull, (void*)&arg);
			if (testName == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((arg->context = context = Iso14827TestValidateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->desc = Dz1Str_clone(Iso14827TestProcessStatusCodeStrA(code), errp)) == NULL) ERR_OUT(errp);
			else
			{
				context->time = time(NULL);
				context->code = code;
				Dz1Error_set(errp, 0);

				if (data != NULL)
				{
					if ((context->data = Dz1Binary_clone(data, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}

				if (raw != NULL)
				{
					if ((context->raw = Dz1Binary_clone(raw, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
			if (errp->code == 0)
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Validate request [ %s ] to server!\n"), testName);
				if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_VALIDATE_REQUEST, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (Iso14827TestValidateContextArg_delAndSetNull, (void*)&arg);
		}

	}
	return ERR_IS_SUCCESS(errp);
}


bool_t Iso14827TestHelperEnvUtil_notifyStateToMain(Iso14827TestHelperEnv* env, Iso14827TestNotifyStateArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestNotifyStateArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = Iso14827TestNotifyStateArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyStateArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_NOTIFY_STATE, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestNotifyStateArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Iso14827TestHelperEnvUtil_notifyInfoToMain(Iso14827TestHelperEnv* env, Iso14827TestNotifyInfoArg* arg, Dz1Error* err)
{

	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestNotifyInfoArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = Iso14827TestNotifyInfoArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyInfoArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_NOTIFY_INFO, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestNotifyInfoArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t Iso14827TestHelperEnvUtil_notifyErrorToMain(Iso14827TestHelperEnv* env, Iso14827TestNotifyErrorArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestNotifyErrorArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = Iso14827TestNotifyErrorArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyErrorArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_NOTIFY_ERROR, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestNotifyErrorArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Iso14827TestHelperEnvUtil_validateRequestToMain(Iso14827TestHelperEnv* env, Iso14827TestValidateContextArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestValidateContextArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = Iso14827TestValidateContextArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestValidateContextArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_VALIDATE_REQUEST, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestValidateContextArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}
