#ifndef GITSN_OPEN_API_H
#define GITSN_OPEN_API_H

#include <openssl/opensslv.h>

#ifndef UNIX_SYSTEM
#if OPENSSL_VERSION_NUMBER <= 0x009080efL
///////////////////////////////////////////////
// OpenSSL 0.9.8
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
// OpenSSL 0.9.8
///////////////////////////////////////////////
#elif OPENSSL_VERSION_NUMBER == 0x1010111fL
///////////////////////////////////////////////
// OpenSSL 1.1.1q
#if _MSC_VER <= 1500

#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libssl.lib")
#else // _MSC_VER
#if __WORDSIZE == 32
#	if defined(_DEBUG)
#		if defined(_DLL)	//	/MDd
#pragma comment(lib, "libcrypto32MDd.lib")
#pragma comment(lib, "libssl32MDd.lib")
#		else // _DLL			/MTd
#pragma comment(lib, "libcrypto32MTd.lib")
#pragma comment(lib, "libssl32MTd.lib")
#		endif // _DLL
#	elif defined(NDEBUG)
#		if defined(_DLL)		/MD
#pragma comment(lib, "libcrypto32MD.lib")
#pragma comment(lib, "libssl32MD.lib")
#		else // _DLL			/MT
#pragma comment(lib, "libcrypto32MT.lib")
#pragma comment(lib, "libssl32MT.lib")
#		endif // _DLL
#	endif // _DEBUG, NDEBUG
#elif __WORDSIZE == 64
#	if defined(_DEBUG)
#		if defined(_DLL)	//	/MDd
#pragma comment(lib, "libcrypto64MDd.lib")
#pragma comment(lib, "libssl64MDd.lib")
#		else // _DLL			/MTd
#pragma comment(lib, "libcrypto64MTd.lib")
#pragma comment(lib, "libssl64MTd.lib")
#		endif // _DLL
#	elif defined(NDEBUG)
#		if defined(_DLL)	//	/MD
#pragma comment(lib, "libcrypto64MD.lib")
#pragma comment(lib, "libssl64MD.lib")
#		else // _DLL			/MT
#pragma comment(lib, "libcrypto64MT.lib")
#pragma comment(lib, "libssl64MT.lib")
#		endif // _DLL
#	endif // _DEBUG, NDEBUG
#endif // __WORDSIZE
#endif // _MSC_VER

#pragma comment(lib, "ADVAPI32.lib")
#pragma comment(lib, "CRYPT32.lib")
#pragma comment(lib, "USER32.lib")
// OpenSSL 1.1.1q
///////////////////////////////////////////////
#else // OPENSSL_VERSION_NUMBER
///////////////////////////////////////////////
// OpenSSL
#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "ADVAPI32.lib")
#pragma comment(lib, "CRYPT32.lib")
#pragma comment(lib, "USER32.lib")
// OpenSSL
///////////////////////////////////////////////
#endif
#endif // UNIX_SYSTEM

#include <GitsnOpenApiDef.h>
DZ1_CPPLINK GitsnOpenApiDataList	*GitsnOpenApiDataList_genFromArgStrU(str_t str, Dz1Error *err);
DZ1_CPPLINK GitsnOpenApiDataList	*GitsnOpenApiDataList_genFromArgStrA(str_t str, Dz1Error *err);
DZ1_CPPLINK GitsnOpenApiDataList	*GitsnOpenApiDataList_genFromArgStrW(str_t str, Dz1Error *err);

DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_insertNode(GitsnOpenApiDatas *dst, GitsnOpenApiDataEntry **_node, Dz1Error *err);

DZ1_CPPLINK GitsnOpenApiDatas		*GitsnOpenApiDatas_genFromArgStrU(str_t str_u8, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendArgStrU(GitsnOpenApiDatas *dst, str_t str_u8, Dz1Error *errp);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendEntryStrU(GitsnOpenApiDatas *dst, str_t name_u8, str_t value_u8, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendEntryNumU(GitsnOpenApiDatas *dst, str_t name_u8, s64_t value, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendTimeStampU(GitsnOpenApiDatas *dst, str_t name_u8, time_t *t, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_removeU(GitsnOpenApiDatas *dst, str_t name_u8, Dz1Error *err);
DZ1_CPPLINK GitsnOpenApiDataEntry	*GitsnOpenApiDatas_findU(GitsnOpenApiDatas *dst, str_t name_u8, Dz1Error *err);


DZ1_CPPLINK GitsnOpenApiDatas		*GitsnOpenApiDatas_genFromArgStrA(str_t str, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendEntryStrA(GitsnOpenApiDatas *dst, str_t key, str_t value, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendEntryNumA(GitsnOpenApiDatas *dst, str_t key, s64_t value, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendTimeStampA(GitsnOpenApiDatas *dst, str_t key, time_t *t, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_removeA(GitsnOpenApiDatas *dst, str_t name_u8, Dz1Error *err);
DZ1_CPPLINK GitsnOpenApiDataEntry	*GitsnOpenApiDatas_findA(GitsnOpenApiDatas *dst, str_t name, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK GitsnOpenApiDatas		*GitsnOpenApiDatas_genFromArgStrW(wstr_t str, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendEntryStrW(GitsnOpenApiDatas *dst, wstr_t key, wstr_t value, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendEntryNumW(GitsnOpenApiDatas *dst, wstr_t key, s64_t value, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_appendTimeStampW(GitsnOpenApiDatas *dst, wstr_t key, time_t *t, Dz1Error *err);
DZ1_CPPLINK bool_t					 GitsnOpenApiDatas_removeW(GitsnOpenApiDatas *dst, wstr_t name, Dz1Error *err);
DZ1_CPPLINK GitsnOpenApiDataEntry	*GitsnOpenApiDatas_findW(GitsnOpenApiDatas *dst, wstr_t name, Dz1Error *err);
#ifdef UNICODE
#define								 GitsnOpenApiDatas_genFromArgStr		GitsnOpenApiDatas_genFromArgStrW
#define								 GitsnOpenApiDatas_appendEntryStr		GitsnOpenApiDatas_appendEntryStrW
#define								 GitsnOpenApiDatas_appendEntryNum		GitsnOpenApiDatas_appendEntryNumW
#define								 GitsnOpenApiDatas_appendTimeStamp		GitsnOpenApiDatas_appendTimeStampW
#define								 GitsnOpenApiDatas_remove				GitsnOpenApiDatas_removeW
#define								 GitsnOpenApiDatas_find					GitsnOpenApiDatas_findW
#else	// UNICODE
#define								 GitsnOpenApiDatas_genFromArgStr		GitsnOpenApiDatas_genFromArgStrA
#define								 GitsnOpenApiDatas_appendEntryStr		GitsnOpenApiDatas_appendEntryStrA
#define								 GitsnOpenApiDatas_appendEntryNum		GitsnOpenApiDatas_appendEntryNumA
#define								 GitsnOpenApiDatas_appendTimeStamp		GitsnOpenApiDatas_appendTimeStampA
#define								 GitsnOpenApiDatas_remove				GitsnOpenApiDatas_removeA
#define								 GitsnOpenApiDatas_find					GitsnOpenApiDatas_findA
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define								 GitsnOpenApiDatas_genFromArgStr		GitsnOpenApiDatas_genFromArgStrA
#define								 GitsnOpenApiDatas_appendEntryStr		GitsnOpenApiDatas_appendEntryStrU
#define								 GitsnOpenApiDatas_appendEntryNum		GitsnOpenApiDatas_appendEntryNumU
#define								 GitsnOpenApiDatas_appendTimeStamp		GitsnOpenApiDatas_appendTimeStampU
#define								 GitsnOpenApiDatas_remove				GitsnOpenApiDatas_removeU
#define								 GitsnOpenApiDatas_find					GitsnOpenApiDatas_findU
#endif	// UNIX_SYSTEM

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpRsp tool
// support code
//		200: OK
//		400: Invalid Request
//		404: Not Found
//	*** TBD ***
DZ1_CPPLINK bool_t GitsnOpenApiHttpRsp_setStatus(GitsnOpenApiHttpRsp *dst, u32_t code, Dz1Error *err);
// GitsnOpenApiHttpRsp tool
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Open API Servant : HTTP Server
// don't call Servant API in cb function
typedef struct GitsnOpenApiServerOptions
{
	u32_t server_idle_timeout_ms;
	bool_t advertise_keep_alive;
	GitsnOpenApiConnectionCallback connection_cb;
	void *connection_cb_arg;
} GitsnOpenApiServerOptions;

DZ1_CPPLINK void	*GitsnOpenApi_new(Dz1SockAddr *listen_addr, str_t server_name_u8, GitsnOpenApiCallback cb, void *cb_arg, GitsnOpenApiException e, void *eArg, Dz1Error *err);
DZ1_CPPLINK void	*GitsnOpenApi_newWithOptions(Dz1SockAddr *listen_addr, str_t server_name_u8, GitsnOpenApiCallback cb, void *cb_arg,
											 GitsnOpenApiException e, void *eArg, const GitsnOpenApiServerOptions *options, Dz1Error *err);
DZ1_CPPLINK void	 GitsnOpenApi_del(void *task);

// Make sure "Content-Type" header entry if u use data body.
// This function automatically insert 'Date', 'Server', and 'Content-Length'.
// Do not append them
DZ1_CPPLINK bool_t	 GitsnOpenApi_httpResponse(Dz1Task *task, u32_t session_id, GitsnOpenApiHttpRsp *rsp,	Dz1Error *err);

// GitsnOpenApi_webSockSend : WIP, don;t use
DZ1_CPPLINK bool_t	 GitsnOpenApi_webSockSend( Dz1Task *task, u32_t session_id, Dz1Binary *bin,				Dz1Error *err);

// GitsnOpenApi_noResponse: terminate session without any response
DZ1_CPPLINK bool_t	 GitsnOpenApi_noResponse(  Dz1Task *task, u32_t session_id,								Dz1Error *err);
// Open API Servant : HTTP Server
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Open API Request System : HTTP Client
DZ1_CPPLINK bool_t			 GitsnOpenApiReqSys_init(Dz1Error *err);
DZ1_CPPLINK void			 GitsnOpenApiReqSys_clenaup(void *null_ptr);
#define						 GitsnOpenApiReqSys_initCancel		GitsnOpenApiReqSys_clenaup

///////////////////////////
// Open API Request Handle 
typedef void GitsnOpenApiReq;
typedef struct GitsnOpenApiTransferInfo
{
	u64_t uploaded_bytes;
	u64_t elapsed_ms;
} GitsnOpenApiTransferInfo;

DZ1_CPPLINK GitsnOpenApiReq *GitsnOpenApiReq_new(u32_t timeout_s, Dz1Error *err);
DZ1_CPPLINK GitsnOpenApiReq *GitsnOpenApiReq_newWithTimeouts(u32_t connect_timeout_s, u32_t request_timeout_s, Dz1Error *err);
DZ1_CPPLINK void			 GitsnOpenApiReq_del(GitsnOpenApiReq *p);
DZ1_CPPLINK bool_t			 GitsnOpenApiReq_enableNativeCaStore(GitsnOpenApiReq *api, Dz1Error *err);
DZ1_CPPLINK bool_t			 GitsnOpenApiReq_setCaInfo(GitsnOpenApiReq *api, const str_t ca_info_utf8, Dz1Error *err);
DZ1_CPPLINK bool_t			 GitsnOpenApiReq_getLastTransferInfo(GitsnOpenApiReq *api, GitsnOpenApiTransferInfo *ret_info, Dz1Error *err);
static __inline__ void		 GitsnOpenApiReq_delAndSetNull(void *pptr)
{
	GitsnOpenApiReq **p = (GitsnOpenApiReq **)pptr;
	if (p) { GitsnOpenApiReq_del(*p); *p = NULL; }
}
// Open API Request Handle
///////////////////////////

/*
* hdropt_utf8[] example
* str_t hdr_opt[] =
* {
*	"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.0.3705)",
*	"Other Header Option #1",
*	"Other Header Option #2",
*	...
*	"Other Header Option #n",
*	NULL
* }
*/

#define GitsnOpenApiDataEntry_NULL { NULL, NULL }
#define GitsnOpenApiDataEntry_isNULL(p)	(Dz1Str_isVoid(p->key_utf8) && Dz1Str_isVoid(p->value_utf8) ? TRUE : FALSE)

///////////////////////////////////////////////////////////////
// GitsnOpenApiReq_postFields : send HTTP POST with data fields
// ------------------------------------------------------------
// this function automatically append header option:
//		Content-Type: application/x-www-form-urlencoded
//		Content-Length: {calculated}
// do not use them
///////////////////////////////////////////////////////////////
DZ1_CPPLINK GitsnOpenApiResult *GitsnOpenApiReq_postFields(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], GitsnOpenApiDataEntry *postdata[], Dz1Error *err);
DZ1_CPPLINK GitsnOpenApiResult *GitsnOpenApiReq_postFields2(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], GitsnOpenApiDataList *postdata, Dz1Error *err);

////////////////////////////////////////////////////////////////
// GitsnOpenApiReq_postJson : send HTTP POST with JSON data text
// -------------------------------------------------------------
// this function automatically append header option:
//		Content-Type: application/json
//		Content-Length: {calculated}
// do not use them
////////////////////////////////////////////////////////////////
DZ1_CPPLINK GitsnOpenApiResult *GitsnOpenApiReq_postJson(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], str_t postdata_json_utf8, Dz1Error *err);

////////////////////////////////////////////////////////////////
// GitsnOpenApiReq_postMultipartFile : send HTTP POST with multipart file data
// --------------------------------------------------------------------------
// this function lets libcurl generate multipart/form-data Content-Type
// with boundary. Do not add Content-Type to hdr_opts.
////////////////////////////////////////////////////////////////
DZ1_CPPLINK GitsnOpenApiResult *GitsnOpenApiReq_postMultipartFile(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[],
                                                                  const str_t field_name_utf8, const str_t file_name_utf8,
                                                                  const str_t content_type_utf8, const void *file_data, u32_t file_size,
                                                                  Dz1Error *err);

////////////////////////////////////////////////////
// GitsnOpenApiReq_postJson : send HTTP GET
// -------------------------------------------------
// this function automatically append header option:
//		"Accept: application/json"
//		Content-Length: {calculated}
// do not use them
////////////////////////////////////////////////////
DZ1_CPPLINK GitsnOpenApiResult *GitsnOpenApiReq_getJson(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], GitsnOpenApiDataEntry *args[], Dz1Error *err);
DZ1_CPPLINK GitsnOpenApiResult *GitsnOpenApiReq_getXml(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], GitsnOpenApiDataEntry *args[], Dz1Error *err);
DZ1_CPPLINK GitsnOpenApiResult *GitsnOpenApiReq_getJson2(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], GitsnOpenApiDataList *args, Dz1Error *err);
// Streams the response body to output_path_utf8 without buffering it in memory.
// A sibling ".part" file is used during transfer and removed on failure.
DZ1_CPPLINK GitsnOpenApiDownloadResult *GitsnOpenApiReq_getToFile(
	GitsnOpenApiReq *api, const str_t url_utf8,
	GitsnOpenApiDataEntry hdr_opts[], const str_t output_path_utf8,
	Dz1Error *err);
// Open API Request System : HTTP Client
///////////////////////////////////////////////////////////////////////////////
#endif // GITSN_OPEN_API
