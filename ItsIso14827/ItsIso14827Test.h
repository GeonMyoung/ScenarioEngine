#ifndef ITS_ISO_14827_TEST_H
#define ITS_ISO_14827_TEST_H

#include <ItsIso14827.h>

#include "generator.h"
#include "ItsIso14827Test_msg.h"

#define DEFAULT_TEST_PORT_NUMBER			9355

DZ1_CPPLINK extern void *t14827;

//#define SERVER_DOMAIN_DEFAULT				"TEST_SERVER"
#define SERVER_DOMAIN_DEFAULT				"SFPF_IC_SERVER"
#define CLIENT_DOMAIN_DEFAULT				"TEST_CLIENT"
#define CLIENT_HEARTBEAT_DURATION			40
#define CLIENT_RESPONSE_TIMEOUT				10

#define DEFAULT_USER_NAME					"sfpf_ic_center"
#define DEFAULT_USER_PASS					"sfpf_ic_pass"

typedef struct ClientModeMap
{
	Dz1Str			 name;
	Dz1Str			 myDomainStr;
	Dz1Str			 peerDomainStr;
	Dz1Str			 ipStr;
	u16_t			 port;
	Dz1Str			 userStr;
	Dz1Str			 passStr;
	MsgGenerator	*genTable;
	void			 (*del)(void *ptr);
	void			 (*dump)(void *ptr, int tab);
	ssize_t			 (*enc)(void *src, u8_t **dst, Dz1Asn1Codec codec, str_t *retOID, Dz1Error *err);
	ssize_t			 (*dec)(str_t oidStr, void **dst, u8_t *src, size_t size, Dz1Asn1Codec codec, Dz1Error *err);
} ClientModeMap;
DZ1_CPPLINK ClientModeMap *ClientModeMap_find(str_t name);
DZ1_CPPLINK extern ClientModeMap *selectedClient;
//DZ1_CPPLINK extern ItsIso14827ClientDomainCallback *clientCallback;

////////////////////////////////////////////////////////////////////////////////
// User Entry
typedef struct TestServerUserEntry
{
	Dz1Str						 user;
	Dz1Str						 pass;
} TestServerUserEntry;
// User Entry
////////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK void				*TestServerTask_new(Dz1Str myDomainStr, u32_t max_client, TestServerUserEntry users[], u32_t users_cnt, Dz1Error *err);
DZ1_CPPLINK void				*TestClientTask_new(Dz1Str client_mode_str, Dz1Error *err);
DZ1_CPPLINK bool_t				 TestClient_connect(void *tClient, Dz1SockAddr *dst_addr, Dz1Str peerDomainStr, Dz1Str userStr, Dz1Str passStr, Dz1Error *err);
DZ1_CPPLINK bool_t				 TestClient_disconnect(void *tClient, Dz1Str peerDomainStr, Dz1Error *err);
DZ1_CPPLINK bool_t				 TestClient_single(void *tClient, Dz1Str peerDomainStr, u32_t req_code, Dz1Error *err);
DZ1_CPPLINK bool_t				 TestClient_periodic(void *tClient, Dz1Str peerDomainStr, u32_t req_code, Dz1Error *err);

#endif
