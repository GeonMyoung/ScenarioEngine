#include <curl/curl.h>
#include <Dz1SockUtil.h>
#include <GitsnOpenApi.h>
#include <openssl/evp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define OPEN_API_ERR_OUT(ep, r, code) \
do\
{\
	str_t err_text = (str_t)curl_easy_strerror(res);\
	Dz1Thread_printf(Dz1T("!!! OpenApiError : ")); str_t_dump(err_text, 0);\
	ERR_SET_OUT(ep, code);\
} while(0)

typedef struct GitsnOpenApiReqTimeoutConfig
{
	u32_t connect_timeout_s;
	u32_t request_timeout_s;
} GitsnOpenApiReqTimeoutConfig;

static void _set_request_error(CURL *curl, CURLcode res, Dz1Error *errp)
{
	GitsnOpenApiReqTimeoutConfig *config = NULL;
	double connect_time_s = 0.0;
	curl_off_t uploaded_bytes = 0;
	curl_off_t elapsed_us = 0;
	const char *phase = "request";

	if (curl != NULL)
	{
		(void)curl_easy_getinfo(curl, CURLINFO_SIZE_UPLOAD_T, &uploaded_bytes);
		(void)curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &elapsed_us);
	}

	if (res != CURLE_OPERATION_TIMEDOUT)
	{
		str_t err_text = (str_t)curl_easy_strerror(res);
		Dz1Thread_printf(Dz1T("!!! OpenApiError : "));
		str_t_dump(err_text, 0);
		Dz1Error_setWithComment(errp, EFAULT,
			(DZ1_ERROR_ARG,
			 "HTTP request failed: curl_code=%d, message=%s, uploaded_bytes=%llu, elapsed_ms=%llu.",
			 (int)res, err_text != NULL ? err_text : "unknown",
			 (unsigned long long)(uploaded_bytes > 0 ? uploaded_bytes : 0),
			 (unsigned long long)(elapsed_us > 0 ? elapsed_us / 1000 : 0)));
		return;
	}

	if (curl != NULL)
	{
		(void)curl_easy_getinfo(curl, CURLINFO_PRIVATE, &config);
		(void)curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &connect_time_s);
	}
	if (connect_time_s <= 0.0) phase = "connection";
	else if (uploaded_bytes > 0) phase = "upload_or_response";

	Dz1Error_setWithComment(
		errp, ETIMEDOUT,
		(DZ1_ERROR_ARG,
		 "HTTP client timeout: phase=%s, connect_timeout_s=%u, request_timeout_s=%u, uploaded_bytes=%llu, elapsed_ms=%llu.",
		 phase,
		 config != NULL ? (unsigned int)config->connect_timeout_s : 0U,
		 config != NULL ? (unsigned int)config->request_timeout_s : 0U,
		 (unsigned long long)(uploaded_bytes > 0 ? uploaded_bytes : 0),
		 (unsigned long long)(elapsed_us > 0 ? elapsed_us / 1000 : 0)));
}

///////////////////////////////////////////////////////////////////////////////
// System
static bool_t GitsnOpenApiReqFlag = FALSE;
static pthread_mutex_t GitsnOpenApiReqFlagLock = PTHREAD_MUTEX_INITIALIZER;

bool_t GitsnOpenApiReqSys_init(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	pthread_mutex_lock(&GitsnOpenApiReqFlagLock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&GitsnOpenApiReqFlagLock);
	if (GitsnOpenApiReqFlag == TRUE) ERR_SET_OUT(errp, EEXIST);
	else
	{
	    CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT); // libcurl 초기화
		if (res != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
		else
		{
			GitsnOpenApiReqFlag = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&GitsnOpenApiReqFlagLock);
	return ERR_IS_SUCCESS(errp);
}

void GitsnOpenApiReqSys_clenaup(void *ptr)
{
	pthread_mutex_lock(&GitsnOpenApiReqFlagLock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&GitsnOpenApiReqFlagLock);
    if (GitsnOpenApiReqFlag == TRUE)
	{
		curl_global_cleanup(); // libcurl 전역 종료
		GitsnOpenApiReqFlag = FALSE;
	}
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&GitsnOpenApiReqFlagLock);
}

static bool_t _GitsnOpenApiReqSys_chk(void)
{
	bool_t ret = FALSE;
	pthread_mutex_lock(&GitsnOpenApiReqFlagLock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&GitsnOpenApiReqFlagLock);
	ret = GitsnOpenApiReqFlag;
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&GitsnOpenApiReqFlagLock);
	return ret;
}
// System
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Handle
static void _curl_easy_cleanupAndSetNull(void *pptr)
{
	CURL **p = (CURL **)pptr;
	if (p != NULL && *p != NULL)
	{
		GitsnOpenApiReqTimeoutConfig *config = NULL;
		(void)curl_easy_getinfo(*p, CURLINFO_PRIVATE, &config);
		if (config != NULL) Dz1Memory_cancel(config);
		curl_easy_cleanup(*p);
		*p = NULL;
	}
}

GitsnOpenApiReq *GitsnOpenApiReq_new(u32_t timeout_s, Dz1Error *err)
{
	return GitsnOpenApiReq_newWithTimeouts(timeout_s, timeout_s, err);
}

GitsnOpenApiReq *GitsnOpenApiReq_newWithTimeouts(u32_t connect_timeout_s, u32_t request_timeout_s, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CURL *ctx = NULL;
	GitsnOpenApiReqTimeoutConfig *config = NULL;
	CURLcode res = CURLE_OK;
	if (_GitsnOpenApiReqSys_chk() == FALSE) ERR_SET_OUT(errp, ENOSYS);
	else if (connect_timeout_s == 0 || request_timeout_s == 0 ||
	         connect_timeout_s > request_timeout_s) ERR_SET_OUT(errp, EINVAL);
	else if ((ctx = curl_easy_init()) == NULL) ERR_SET_OUT(errp, EFAULT); // curl 핸들 생성
	else if ((config = (GitsnOpenApiReqTimeoutConfig *)Dz1Calloc(
	              sizeof(GitsnOpenApiReqTimeoutConfig), 1, errp)) == NULL)
	{
		curl_easy_cleanup(ctx);
		ctx = NULL;
	}
	else if ((res = curl_easy_setopt(ctx, CURLOPT_PRIVATE, config)) != CURLE_OK)
	{
		Dz1Memory_cancel(config);
		config = NULL;
		curl_easy_cleanup(ctx);
		ctx = NULL;
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	}
	else
	{
		config->connect_timeout_s = connect_timeout_s;
		config->request_timeout_s = request_timeout_s;
		pthread_cleanup_push(_curl_easy_cleanupAndSetNull, (void *)&ctx);
		if (0) { }
		else if ((res = curl_easy_setopt(ctx, CURLOPT_COOKIEFILE, "")) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
		else if ((res = curl_easy_setopt(ctx, CURLOPT_CONNECTTIMEOUT, connect_timeout_s)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
		else if ((res = curl_easy_setopt(ctx, CURLOPT_TIMEOUT, request_timeout_s)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (_curl_easy_cleanupAndSetNull, (void *)&ctx);
	}
	return (GitsnOpenApiReq *)ctx;
}

bool_t GitsnOpenApiReq_getLastTransferInfo(GitsnOpenApiReq *api, GitsnOpenApiTransferInfo *ret_info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CURL *curl = (CURL *)api;
	curl_off_t uploaded_bytes = 0;
	curl_off_t elapsed_us = 0;
	CURLcode res = CURLE_OK;

	if (curl == NULL || ret_info == NULL)
		ERR_SET_OUT(errp, EFAULT);
	else if ((res = curl_easy_getinfo(curl, CURLINFO_SIZE_UPLOAD_T, &uploaded_bytes)) != CURLE_OK)
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	else if ((res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &elapsed_us)) != CURLE_OK)
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	else
	{
		ret_info->uploaded_bytes = (u64_t)(uploaded_bytes > 0 ? uploaded_bytes : 0);
		ret_info->elapsed_ms = (u64_t)(elapsed_us > 0 ? elapsed_us / 1000 : 0);
		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}

/* Windows native CA store를 TLS 신뢰원으로 추가한다. */
bool_t GitsnOpenApiReq_enableNativeCaStore(GitsnOpenApiReq *api, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CURL *ctx = (CURL *)api;
	CURLcode res = CURLE_OK;

	if (ctx == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((res = curl_easy_setopt(ctx, CURLOPT_SSL_OPTIONS,
	                                (long)CURLSSLOPT_NATIVE_CA)) != CURLE_OK)
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	else if ((res = curl_easy_setopt(ctx, CURLOPT_SSL_VERIFYPEER, 1L)) != CURLE_OK)
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	else if ((res = curl_easy_setopt(ctx, CURLOPT_SSL_VERIFYHOST, 2L)) != CURLE_OK)
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static wchar_t *_ca_path_to_wide(const char *path, UINT code_page,
                                 DWORD flags) {
  wchar_t *wide_path = NULL;
  int length = 0;

  if (path == NULL || path[0] == 0) return NULL;
  length = MultiByteToWideChar(code_page, flags, path, -1, NULL, 0);
  if (length <= 0) return NULL;
  wide_path = (wchar_t *)calloc((size_t)length, sizeof(*wide_path));
  if (wide_path == NULL) return NULL;
  if (MultiByteToWideChar(code_page, flags, path, -1, wide_path, length) !=
      length) {
    free(wide_path);
    return NULL;
  }
  return wide_path;
}

static bool_t _read_ca_file(const char *path, unsigned char **out,
                            size_t *out_size) {
  wchar_t *wide_path = NULL;
  FILE *file = NULL;
  __int64 length = 0;
  unsigned char *data = NULL;
  bool_t success = FALSE;

  if (out == NULL || out_size == NULL) return FALSE;
  *out = NULL;
  *out_size = 0;

  wide_path = _ca_path_to_wide(path, CP_UTF8, MB_ERR_INVALID_CHARS);
  if (wide_path == NULL)
    wide_path = _ca_path_to_wide(path, CP_ACP, 0);
  if (wide_path == NULL || _wfopen_s(&file, wide_path, L"rb") != 0 ||
      file == NULL)
    goto cleanup;
  if (_fseeki64(file, 0, SEEK_END) != 0 ||
      (length = _ftelli64(file)) <= 0 ||
      (unsigned __int64)length > (unsigned __int64)SIZE_MAX ||
      _fseeki64(file, 0, SEEK_SET) != 0)
    goto cleanup;
  data = (unsigned char *)malloc((size_t)length);
  if (data == NULL || fread(data, 1, (size_t)length, file) != (size_t)length)
    goto cleanup;

  *out = data;
  *out_size = (size_t)length;
  data = NULL;
  success = TRUE;

cleanup:
  free(data);
  if (file != NULL) fclose(file);
  free(wide_path);
  return success;
}

/* 사설 CA 인증서를 추가 신뢰원으로 지정하고 TLS 검증을 유지한다. */
bool_t GitsnOpenApiReq_setCaInfo(GitsnOpenApiReq *api, const str_t ca_info_utf8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CURL *ctx = (CURL *)api;
	CURLcode res = CURLE_OK;
	unsigned char *ca_data = NULL;
	size_t ca_size = 0;
	struct curl_blob ca_blob = {0};
	ca_blob.flags = CURL_BLOB_COPY;

	if (ctx == NULL || Dz1Str_isVoid(ca_info_utf8)) ERR_SET_OUT(errp, EINVAL);
	else if (_read_ca_file(ca_info_utf8, &ca_data, &ca_size) == FALSE)
		ERR_SET_OUT(errp, ENOENT);
	else if ((ca_blob.data = ca_data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ca_blob.len = ca_size) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((res = curl_easy_setopt(ctx, CURLOPT_CAINFO_BLOB, &ca_blob)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
	else if ((res = curl_easy_setopt(ctx, CURLOPT_SSL_VERIFYPEER, 1L)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
	else if ((res = curl_easy_setopt(ctx, CURLOPT_SSL_VERIFYHOST, 2L)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
	else Dz1Error_set(errp, 0);
	free(ca_data);

	return ERR_IS_SUCCESS(errp);
}

void GitsnOpenApiReq_del(GitsnOpenApiReq *p)
{
	CURL *ctx = (CURL *)p;
	if (ctx != NULL)
	{
		GitsnOpenApiReqTimeoutConfig *config = NULL;
		(void)curl_easy_getinfo(ctx, CURLINFO_PRIVATE, &config);
		if (config != NULL) Dz1Memory_cancel(config);
		curl_easy_cleanup(ctx);
	}
}
// Handle
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Data Value Enumeration
static void curl_freeAndSetNull(void *pptr)
{
	void **p = (void **)pptr;
	if (p != NULL && *p != NULL) { curl_free(*p); *p = NULL; }
}

static bool_t _data_enumerate(Dz1ElasticBuf *elb, GitsnOpenApiDataEntry *arr[], Dz1Error *errp)
{
	if (elb == NULL || arr == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		str_t var, val;
		GitsnOpenApiDataEntry **i, *src;
		for (i = arr; (*i) != NULL && errp->code == 0; i++)
		{
			src = *i;
			if (i != arr && Dz1ElasticBuf_pushChrA(elb, '&', errp) == FALSE) ERR_OUT(errp);
			else if ((var = curl_escape(src->key_utf8, 0)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(curl_freeAndSetNull, (void *)&var);
				if (Dz1ElasticBuf_pushStrA(elb, var, errp) == FALSE) ERR_OUT(errp);

				else if (Dz1ElasticBuf_pushChrA(elb, '=', errp) == FALSE) ERR_OUT(errp);
				else if ((val = curl_escape(src->value_utf8, 0)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					pthread_cleanup_push(curl_freeAndSetNull, (void *)&val);
					if (Dz1ElasticBuf_pushStrA(elb, val, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					pthread_cleanup_pop(1); // (curl_freeAndSetNull, (void *)&val);
				}
				pthread_cleanup_pop(1); // (curl_freeAndSetNull, (void *)&var);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Data Value Enumeration
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// POST Fields
static bool_t curl_set_post_fields(CURL *curl, GitsnOpenApiDataEntry *arr[], Dz1Error *errp)
{
	Dz1ElasticBuf *elb = NULL;
	if (curl == NULL || arr == NULL || GitsnOpenApiDataEntry_isNULL(arr[0])) ERR_SET_OUT(errp, EINVAL);
	else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		if (_data_enumerate(elb, arr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			str_t fields = NULL;
			CURLcode res = CURLE_OK;
			if ((fields = Dz1ElasticBuf_flattenStrA(elb, errp)) == NULL) ERR_OUT(errp);
			else if ((res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields))	!= CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return ERR_IS_SUCCESS(errp);
}
// POST Fields
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// HEADER Options
static void curl_slist_delAndSetNull(void *pptr)
{
	struct curl_slist **p = (struct curl_slist **)pptr;
	if (p != NULL && *p != NULL) { curl_slist_free_all(*p); *p = NULL; }
}

static bool_t GitsnOpenApiReq_headerOptBuild(CURL *curl, GitsnOpenApiDataEntry hdr_opts[], struct curl_slist **ret_header, Dz1Error *errp)
{
	if (curl == NULL || ret_header == NULL || *ret_header != NULL) ERR_SET_OUT(errp, EINVAL);
	else if (hdr_opts == NULL || GitsnOpenApiDataEntry_isNULL(hdr_opts)) Dz1Error_set(errp, 0); // no header opt -> nothing to do
	else
	{
		size_t len;
		str_t str_opt = NULL;
		GitsnOpenApiDataEntry *i = NULL;
		struct curl_slist *hdr = NULL, *next = NULL;
		pthread_cleanup_push(curl_slist_delAndSetNull, (void *)&hdr);
		for (i = hdr_opts; errp->code == 0 && GitsnOpenApiDataEntry_isNULL(i) == FALSE; i++)
		{
			if (Dz1Str_isVoid(i->key_utf8) || Dz1Str_isVoid(i->value_utf8)) ERR_SET_OUT(errp, EINVAL);
// 			else if (strcmp(i->key_utf8, "User-Agent") == 0)
// 			{
// 				CURLcode res = CURLE_OK;
// 				if ((res = curl_easy_setopt(curl, CURLOPT_USERAGENT, i->value_utf8)) != CURLE_OK) ERR_SET_OUT(errp, EFAULT);
// 				else Dz1Error_set(errp, 0);
// 			}
			else
			{
				len = strlen(i->key_utf8) + 2 + strlen(i->value_utf8);
				if ((str_opt = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&str_opt);
					_std_snprintfA(str_opt, len, "%s: %s", i->key_utf8, i->value_utf8);
					if ((next = curl_slist_append(hdr, str_opt)) == NULL) ERR_SET_OUT(errp, EFAULT);
					else { hdr = next; next = NULL; Dz1Error_set(errp, 0); }
					pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&str_opt);
				}
			}
		}

		if (errp->code == 0)
		{
			*ret_header = hdr;
			hdr = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (curl_slist_delAndSetNull, (void *)&hdr);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t GitsnOpenApiReq_headerOptSet(CURL *curl, struct curl_slist *header, Dz1Error *errp)
{
	CURLcode res = CURLE_OK;
	if (curl == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (header == NULL) Dz1Error_set(errp, 0);
	else if ((res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// HEADER Options
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// POST
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *cb_arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	size_t total = size * nmemb;
	Dz1ElasticBuf *elb = (Dz1ElasticBuf *)cb_arg;
	ssize_t buffered = Dz1ElasticBuf_getDataSize(elb, errp);
	if (errp->code || buffered < 0 || (size != 0 && total / size != nmemb) || total > 1024 * 1024) return 0;
	if ((size_t)buffered > 1024 * 1024 - total) return 0;
	if (_Dz1ElasticBuf_push(elb, contents, total, errp) == FALSE) return 0;
	Dz1Error_set(errp, 0);	// ignore error
    return size * nmemb;
}

static void _detach_header_opt(void *ptr)
{
	CURL *curl = (CURL *)ptr;
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, NULL);
}

static void _detach_mime_post(void *ptr)
{
	CURL *curl = (CURL *)ptr;
	curl_easy_setopt(curl, CURLOPT_MIMEPOST, NULL);
}

typedef struct GitsnOpenApiFileWriteContext
{
	FILE *file;
	EVP_MD_CTX *digest;
	u64_t bytes_written;
	bool_t write_failed;
} GitsnOpenApiFileWriteContext;

static size_t FileWriteCallback(void *contents, size_t size, size_t nmemb, void *cb_arg)
{
	GitsnOpenApiFileWriteContext *ctx = (GitsnOpenApiFileWriteContext *)cb_arg;
	size_t total = size * nmemb;

	if (ctx == NULL || ctx->file == NULL || ctx->digest == NULL ||
	    (size != 0 && total / size != nmemb))
		return 0;
	if (total == 0) return 0;
	if (fwrite(contents, 1, total, ctx->file) != total ||
	    EVP_DigestUpdate(ctx->digest, contents, total) != 1 ||
	    UINT64_MAX - ctx->bytes_written < (u64_t)total)
	{
		ctx->write_failed = TRUE;
		return 0;
	}
	ctx->bytes_written += (u64_t)total;
	return total;
}

static void curl_mime_delAndSetNull(void *pptr)
{
	curl_mime **p = (curl_mime **)pptr;
	if (p != NULL && *p != NULL) { curl_mime_free(*p); *p = NULL; }
}

/* Preserve the final HTTP header block, including duplicates. Credentials stay
 * in memory for validation; evidence serialization must mask them. */
static size_t capture_header_line(GitsnOpenApiDatas **headers,
                                  const char *line, size_t length) {
    Dz1Error err = DZ1_ERROR_INITIALIZER;
    GitsnOpenApiDataEntry *entry = NULL;
    const char *colon = NULL, *value = NULL, *end = line + length;
    size_t name_size, value_size;
    if (length >= 5 && memcmp(line, "HTTP/", 5) == 0) {
        GitsnOpenApiDatas_del(*headers);
        *headers = NULL;
        return length;
    }
    while (end > line && (end[-1] == '\r' || end[-1] == '\n')) --end;
    if (end == line) return length;
    colon = (const char *)memchr(line, ':', (size_t)(end - line));
    if (colon == NULL || colon == line) return length;
    name_size = (size_t)(colon - line);
    value = colon + 1;
    while (value < end && (*value == ' ' || *value == '\t')) ++value;
    while (end > value && (end[-1] == ' ' || end[-1] == '\t')) --end;
    value_size = (size_t)(end - value);
    if (*headers == NULL && (*headers = GitsnOpenApiDatas_new(&err)) == NULL) return 0;
    if ((entry = GitsnOpenApiDataEntry_gen(&err)) == NULL) return 0;
    entry->key_utf8 = (char *)Dz1Calloc(name_size + 1, 1, &err);
    entry->value_utf8 = (char *)Dz1Calloc(value_size + 1, 1, &err);
    if (!entry->key_utf8 || !entry->value_utf8) { GitsnOpenApiDataEntry_del(entry); return 0; }
    memcpy(entry->key_utf8, line, name_size);
    memcpy(entry->value_utf8, value, value_size);
    err = (*headers)->storage->add((*headers)->storage, entry);
    if (err.code) { GitsnOpenApiDataEntry_del(entry); return 0; }
    return length;
}

static size_t CaptureResponseHeader(char *data, size_t size, size_t count, void *user) {
    GitsnOpenApiResult *result = (GitsnOpenApiResult *)user;
    if (!result || (size && count > SIZE_MAX / size)) return 0;
    return capture_header_line(&result->headers, data, size * count);
}

static int CaptureRequestHeader(CURL *curl, curl_infotype type, char *data,
                                size_t size, void *user) {
    GitsnOpenApiResult *result = (GitsnOpenApiResult *)user;
    const char *line = data, *end = data + size, *next;
    (void)curl;
    if (type != CURLINFO_HEADER_OUT || !result) return 0;
    GitsnOpenApiDatas_del(result->request_headers);
    result->request_headers = NULL;
    /* The request line is not a header, even if the URL contains a colon. */
    next = (const char *)memchr(line, '\n', (size_t)(end - line));
    line = next ? next + 1 : end;
    while (line < end) {
        next = (const char *)memchr(line, '\n', (size_t)(end - line));
        if (!next) next = end - 1;
        if (!capture_header_line(&result->request_headers, line, (size_t)(next + 1 - line))) break;
        line = next + 1;
    }
    return 0; /* Never print curl debug data or authentication values. */
}

static CURLcode perform_with_headers(CURL *curl, GitsnOpenApiResult *result) {
    CURLcode code;
    code = curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, CaptureResponseHeader);
    if (code == CURLE_OK) code = curl_easy_setopt(curl, CURLOPT_HEADERDATA, result);
    if (code == CURLE_OK) code = curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, CaptureRequestHeader);
    if (code == CURLE_OK) code = curl_easy_setopt(curl, CURLOPT_DEBUGDATA, result);
    if (code == CURLE_OK) code = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    if (code == CURLE_OK) code = curl_easy_perform(curl);
    /* A CURL handle may be reused after result is released. */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, NULL);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, NULL);
    return code;
}

GitsnOpenApiResult *GitsnOpenApiReq_postFields(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], GitsnOpenApiDataEntry *postdata[], Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiResult *ret = NULL;

	if (api == NULL || Dz1Str_isVoid(url_utf8) || postdata == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnOpenApiResult_new(-1, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		CURLcode res = CURLE_OK;
		CURL *curl = (CURL *)api;
		const char *content_type = NULL;
		struct curl_slist *header = NULL;
		pthread_cleanup_push(GitsnOpenApiResult_delAndSetNull, (void *)&ret);
		if ((ret->data = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);

		else if ((res = curl_easy_setopt(curl, CURLOPT_POST, 1L)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // POST 요청임을 명시
		else if (curl_set_post_fields(curl, postdata, errp) == FALSE) ERR_OUT(errp);								// Data Field 설정

		else if ((res = curl_easy_setopt(curl, CURLOPT_URL, url_utf8)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // 요청 URL 설정

		else if ((res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, ret->data)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // 콜백 함수로 전달할 데이터 버퍼
		else if ((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // 응답 받을 콜백 함수

		else if (GitsnOpenApiReq_headerOptBuild(curl, hdr_opts, &header, errp) == FALSE) ERR_OUT(errp); // Header Option 설정
		else
		{
			pthread_cleanup_push(curl_slist_delAndSetNull, (void *)&header);
			if ((header = curl_slist_append(header, "Content-Type: application/x-www-form-urlencoded")) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (GitsnOpenApiReq_headerOptSet(curl, header, errp) == FALSE) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(_detach_header_opt, (void *)curl);
				if ((res = perform_with_headers(curl, ret)) != CURLE_OK) _set_request_error(curl, res, errp); // 요청 실행
				else if ((res = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &ret->code)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
				else if ((res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
				else if (content_type != NULL &&
				         (ret->content_type = Dz1Str_clone((str_t)content_type, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (_detach_header_opt, (void *)curl);
			}
			pthread_cleanup_pop(1); // (curl_slist_cancel, (void *)&header);
		}
		pthread_cleanup_pop(errp->code); // (GitsnOpenApiReqResult_delAndSetNull, (void *)&ret);
	}
    return ret;
}

GitsnOpenApiResult *GitsnOpenApiReq_postFields2(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], GitsnOpenApiDataList *postdata, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiResult *ret = NULL;
	
	u32_t cnt = 0;
	GitsnOpenApiDataEntry **arr = NULL;
	pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&arr);

	if (postdata != NULL && postdata->count(postdata) > 0 && (arr = postdata->get_array(postdata, &cnt, errp)) == NULL) ERR_OUT(errp);
	else if ((ret = GitsnOpenApiReq_postFields(api, url_utf8, hdr_opts, arr, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&arr);

	return ret;
}

static bool_t curl_set_post_data_json(CURL *curl, str_t postdata_json_utf8, Dz1Error *errp)
{
	str_t fields = NULL;
	if (curl == NULL || Dz1Str_isVoid(postdata_json_utf8)) ERR_SET_OUT(errp, EINVAL);
	else if ((fields = curl_escape(postdata_json_utf8, 0)) == NULL) ERR_OUT(errp);
	else
	{
		CURLcode res = CURLE_OK;
		pthread_cleanup_push(curl_freeAndSetNull, (void *)&fields);
		if ((res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (curl_freeAndSetNull, (void *)&fields);
	}
	return ERR_IS_SUCCESS(errp);
}

GitsnOpenApiResult *GitsnOpenApiReq_postJson(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], str_t postdata_json_utf8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiResult *ret = NULL;

	if (api == NULL || Dz1Str_isVoid(url_utf8) || Dz1Str_isVoid(postdata_json_utf8)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnOpenApiResult_new(-1, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		CURLcode res = CURLE_OK;
		CURL *curl = (CURL *)api;
		struct curl_slist *header = NULL;
		pthread_cleanup_push(GitsnOpenApiResult_delAndSetNull, (void *)&ret);
		if ((ret->data = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);

		else if ((res = curl_easy_setopt(curl, CURLOPT_POST, 1L)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // POST 요청임을 명시
#if 0
		else if (curl_set_post_data_json(curl, postdata_json_utf8, errp) == FALSE) ERR_OUT(errp);					// Data Field 설정
#else
		else if ((res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata_json_utf8)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
#endif
		else if ((res = curl_easy_setopt(curl, CURLOPT_URL, url_utf8)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // 요청 URL 설정

		else if ((res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, ret->data)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // 콜백 함수로 전달할 데이터 버퍼
		else if ((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // 응답 받을 콜백 함수

		else if (GitsnOpenApiReq_headerOptBuild(curl, hdr_opts, &header, errp) == FALSE) ERR_OUT(errp); // Header Option 설정
		else
		{
			pthread_cleanup_push(curl_slist_delAndSetNull, (void *)&header);
			if ((header = curl_slist_append(header, "Content-Type: application/json")) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (GitsnOpenApiReq_headerOptSet(curl, header, errp) == FALSE) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(_detach_header_opt, (void *)curl);
				if ((res = perform_with_headers(curl, ret)) != CURLE_OK) _set_request_error(curl, res, errp); // 요청 실행
				else if ((res = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &ret->code)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
				else Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (_detach_header_opt, (void *)curl);
			}
			pthread_cleanup_pop(1); // (curl_slist_cancel, (void *)&header);
		}
		pthread_cleanup_pop(errp->code); // (GitsnOpenApiReqResult_delAndSetNull, (void *)&ret);
	}
    return ret;
}
GitsnOpenApiResult *GitsnOpenApiReq_postMultipartFile(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[],
                                                      const str_t field_name_utf8, const str_t file_name_utf8, const str_t content_type_utf8,
                                                      const void *file_data, u32_t file_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiResult *ret = NULL;

	if (api == NULL || Dz1Str_isVoid(url_utf8) || Dz1Str_isVoid(field_name_utf8) || Dz1Str_isVoid(file_name_utf8) ||
	    Dz1Str_isVoid(content_type_utf8) || file_data == NULL || file_size == 0)
		ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnOpenApiResult_new(-1, NULL, errp)) == NULL)
		ERR_OUT(errp);
	else
	{
		CURLcode res = CURLE_OK;
		CURL *curl = (CURL *)api;
		curl_mime *mime = NULL;
		curl_mimepart *part = NULL;
		struct curl_slist *header = NULL;
		pthread_cleanup_push(GitsnOpenApiResult_delAndSetNull, (void *)&ret);
		if ((ret->data = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);

		else if ((mime = curl_mime_init(curl)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(curl_mime_delAndSetNull, (void *)&mime);
			if ((part = curl_mime_addpart(mime)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((res = curl_mime_name(part, field_name_utf8)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
			else if ((res = curl_mime_filename(part, file_name_utf8)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
			else if ((res = curl_mime_type(part, content_type_utf8)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
			else if ((res = curl_mime_data(part, (const char *)file_data, (curl_off_t)file_size)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);

			else if ((res = curl_easy_setopt(curl, CURLOPT_POST, 1L)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
			else if ((res = curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
			else if ((res = curl_easy_setopt(curl, CURLOPT_URL, url_utf8)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);

			else if ((res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, ret->data)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
			else if ((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);

			else if (GitsnOpenApiReq_headerOptBuild(curl, hdr_opts, &header, errp) == FALSE) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(curl_slist_delAndSetNull, (void *)&header);
				if (GitsnOpenApiReq_headerOptSet(curl, header, errp) == FALSE) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(_detach_mime_post, (void *)curl);
					pthread_cleanup_push(_detach_header_opt, (void *)curl);
					if ((res = perform_with_headers(curl, ret)) != CURLE_OK) _set_request_error(curl, res, errp);
					else if ((res = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &ret->code)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
					else Dz1Error_set(errp, 0);
					pthread_cleanup_pop(1); // (_detach_header_opt, (void *)curl);
					pthread_cleanup_pop(1); // (_detach_mime_post, (void *)curl);
				}
				pthread_cleanup_pop(1); // (curl_slist_delAndSetNull, (void *)&header);
			}
			pthread_cleanup_pop(1); // (curl_mime_delAndSetNull, (void *)&mime);
		}
		pthread_cleanup_pop(errp->code); // (GitsnOpenApiReqResult_delAndSetNull, (void *)&ret);
	}
    return ret;
}
// POST
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GET
static bool_t _GitsnOpenApiReq_setURL(CURL *curl, const str_t url_utf8, GitsnOpenApiDataEntry *args[], Dz1Error *errp)
{
	CURLcode res = CURLE_OK;
	Dz1ElasticBuf *elb = NULL;
	if (args == NULL || args[0] == NULL)
	{
		if ((res = curl_easy_setopt(curl, CURLOPT_URL, url_utf8)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
		else Dz1Error_set(errp, 0);
	}
	else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		str_t new_url = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		if (Dz1ElasticBuf_pushStrA(elb, url_utf8, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1ElasticBuf_pushChrA(elb, '?', errp) == FALSE) ERR_OUT(errp);
		else if (_data_enumerate(elb, args, errp) == FALSE) ERR_OUT(errp);
		else if ((new_url = Dz1ElasticBuf_flattenStrA(elb, errp)) == NULL) ERR_OUT(errp);
		else if ((res = curl_easy_setopt(curl, CURLOPT_URL, new_url)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb)
	}
	return ERR_IS_SUCCESS(errp);
}

static GitsnOpenApiResult *getTyped(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], GitsnOpenApiDataEntry *args[], bool_t xml, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiResult *ret = NULL;

	if (api == NULL || Dz1Str_isVoid(url_utf8)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnOpenApiResult_new(-1, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		CURLcode res = CURLE_OK;
		CURL *curl = (CURL *)api;
		const char *content_type = NULL;
		struct curl_slist *header = NULL;
		pthread_cleanup_push(GitsnOpenApiResult_delAndSetNull, (void *)&ret);
		if ((ret->data = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);

		else if ((res = curl_easy_setopt(curl, CURLOPT_POST, 0L)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // GET 요청임을 명시
//		else if ((ret = curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET")) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);

		else if (_GitsnOpenApiReq_setURL(curl, url_utf8, args, errp) == FALSE) ERR_OUT(errp);	// 요청 URL 설정

		else if ((res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, ret->data)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // 콜백 함수로 전달할 데이터 버퍼
		else if ((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT); // 응답 받을 콜백 함수

		else if (GitsnOpenApiReq_headerOptBuild(curl, hdr_opts, &header, errp) == FALSE) ERR_OUT(errp); // Header Option 설정
		else
		{
			pthread_cleanup_push(curl_slist_delAndSetNull, (void *)&header);
			if ((header = curl_slist_append(header, xml ? "Accept: application/xml" : "Accept: application/json")) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (GitsnOpenApiReq_headerOptSet(curl, header, errp) == FALSE) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(_detach_header_opt, (void *)curl);
				if ((res = perform_with_headers(curl, ret)) != CURLE_OK) _set_request_error(curl, res, errp); // 요청 실행
				else if ((res = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &ret->code)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
				else if ((res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type)) != CURLE_OK) OPEN_API_ERR_OUT(errp, res, EFAULT);
				else if (content_type != NULL &&
				         (ret->content_type = Dz1Str_clone((str_t)content_type, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (_detach_header_opt, (void *)curl);
			}
			pthread_cleanup_pop(1); // (curl_slist_cancel, (void *)&header);
		}
		pthread_cleanup_pop(errp->code); // (GitsnOpenApiResult_delAndSetNull, (void *)&ret);
	}
    return ret;
}

GitsnOpenApiResult *GitsnOpenApiReq_getJson(GitsnOpenApiReq *api,const str_t url,GitsnOpenApiDataEntry headers[],GitsnOpenApiDataEntry *args[],Dz1Error *err) {
    return getTyped(api,url,headers,args,FALSE,err);
}
GitsnOpenApiResult *GitsnOpenApiReq_getXml(GitsnOpenApiReq *api,const str_t url,GitsnOpenApiDataEntry headers[],GitsnOpenApiDataEntry *args[],Dz1Error *err) {
    return getTyped(api,url,headers,args,TRUE,err);
}

GitsnOpenApiResult *GitsnOpenApiReq_getJson2(GitsnOpenApiReq *api, const str_t url_utf8, GitsnOpenApiDataEntry hdr_opts[], GitsnOpenApiDataList *args, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	GitsnOpenApiResult *ret = NULL;

	u32_t cnt = 0;
	GitsnOpenApiDataEntry **arr = NULL;
	if (args == NULL || (cnt = args->count(args)) == 0)
	{
		if ((ret = GitsnOpenApiReq_getJson(api, url_utf8, hdr_opts, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((arr = args->get_array(args, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		if ((ret = GitsnOpenApiReq_getJson(api, url_utf8, hdr_opts, arr, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return ret;
}

GitsnOpenApiDownloadResult *GitsnOpenApiReq_getToFile(
	GitsnOpenApiReq *api, const str_t url_utf8,
	GitsnOpenApiDataEntry hdr_opts[], const str_t output_path_utf8,
	Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiDownloadResult *ret = NULL;
	GitsnOpenApiFileWriteContext write_ctx = {0};
	CURL *curl = (CURL *)api;
	CURLcode res = CURLE_OK;
	struct curl_slist *header = NULL;
	char *part_path = NULL;
	const char *content_type = NULL;
	unsigned char digest[EVP_MAX_MD_SIZE] = {0};
	unsigned int digest_len = 0;
	char sha256_hex[65] = {0};
	long http_code = 0;
	size_t path_len = 0;
	size_t i = 0;
	FILE *existing = NULL;
	bool_t options_attached = FALSE;

	if (api == NULL || Dz1Str_isVoid(url_utf8) || Dz1Str_isVoid(output_path_utf8))
		ERR_SET_OUT(errp, EINVAL);
	else if ((path_len = strlen(output_path_utf8)) > SIZE_MAX - 6)
		ERR_SET_OUT(errp, EOVERFLOW);
	else if ((part_path = (char *)Dz1Calloc(path_len + 6, 1, errp)) == NULL)
		ERR_OUT(errp);
	else
	{
		snprintf(part_path, path_len + 6, "%s.part", output_path_utf8);
		existing = fopen(output_path_utf8, "rb");
		if (existing != NULL)
		{
			fclose(existing);
			existing = NULL;
			ERR_SET_OUT(errp, EEXIST);
		}
		else
		{
			existing = fopen(part_path, "rb");
			if (existing != NULL)
			{
				fclose(existing);
				existing = NULL;
				ERR_SET_OUT(errp, EEXIST);
			}
		}
	}

	if (ERR_IS_SUCCESS(errp) &&
	    (ret = GitsnOpenApiDownloadResult_gen(errp)) == NULL)
		ERR_OUT(errp);
	else if (ERR_IS_SUCCESS(errp) &&
	         (write_ctx.file = fopen(part_path, "wb")) == NULL)
		Dz1Error_setWithComment(errp, EIO,
			(DZ1_ERROR_ARG, "Cannot create streaming download part file."));
	else if (ERR_IS_SUCCESS(errp) &&
	         (write_ctx.digest = EVP_MD_CTX_new()) == NULL)
		ERR_SET_OUT(errp, ENOMEM);
	else if (ERR_IS_SUCCESS(errp) &&
	         EVP_DigestInit_ex(write_ctx.digest, EVP_sha256(), NULL) != 1)
		ERR_SET_OUT(errp, EFAULT);
	else if (ERR_IS_SUCCESS(errp) &&
	         (res = curl_easy_setopt(curl, CURLOPT_POST, 0L)) != CURLE_OK)
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	else if (ERR_IS_SUCCESS(errp) &&
	         _GitsnOpenApiReq_setURL(curl, url_utf8, NULL, errp) == FALSE)
		ERR_OUT(errp);
	else if (ERR_IS_SUCCESS(errp) &&
	         (res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_ctx)) != CURLE_OK)
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	else if (ERR_IS_SUCCESS(errp) &&
	         (res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, FileWriteCallback)) != CURLE_OK)
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	else if (ERR_IS_SUCCESS(errp))
		options_attached = TRUE;

	if (ERR_IS_SUCCESS(errp) &&
	    GitsnOpenApiReq_headerOptBuild(curl, hdr_opts, &header, errp) == FALSE)
		ERR_OUT(errp);
	else if (ERR_IS_SUCCESS(errp) &&
	         (header = curl_slist_append(header, "Accept: */*")) == NULL)
		ERR_SET_OUT(errp, EFAULT);
	else if (ERR_IS_SUCCESS(errp) &&
	         GitsnOpenApiReq_headerOptSet(curl, header, errp) == FALSE)
		ERR_OUT(errp);
	else if (ERR_IS_SUCCESS(errp) &&
	         (res = curl_easy_perform(curl)) != CURLE_OK)
	{
		if (write_ctx.write_failed)
			Dz1Error_setWithComment(errp, EIO,
				(DZ1_ERROR_ARG, "Streaming download file write or digest update failed."));
		else
			_set_request_error(curl, res, errp);
	}
	else if (ERR_IS_SUCCESS(errp) &&
	         (res = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_code)) != CURLE_OK)
		OPEN_API_ERR_OUT(errp, res, EFAULT);
	else if (ERR_IS_SUCCESS(errp) &&
	         (http_code < INT32_MIN || http_code > INT32_MAX))
		ERR_SET_OUT(errp, EOVERFLOW);
	else if (ERR_IS_SUCCESS(errp))
	{
		ret->code = (s32_t)http_code;
		if ((res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE,
		                             &content_type)) != CURLE_OK)
			OPEN_API_ERR_OUT(errp, res, EFAULT);
		else if (fflush(write_ctx.file) != 0)
			ERR_SET_OUT(errp, EIO);
		else
			Dz1Error_set(errp, 0);
	}

	if (write_ctx.file != NULL)
	{
		if (fclose(write_ctx.file) != 0 && ERR_IS_SUCCESS(errp))
			ERR_SET_OUT(errp, EIO);
		write_ctx.file = NULL;
	}

	if (ERR_IS_SUCCESS(errp) &&
	    EVP_DigestFinal_ex(write_ctx.digest, digest, &digest_len) != 1)
		ERR_SET_OUT(errp, EFAULT);
	else if (ERR_IS_SUCCESS(errp) && digest_len != 32)
		ERR_SET_OUT(errp, EFAULT);
	else if (ERR_IS_SUCCESS(errp))
	{
		for (i = 0; i < digest_len; i++)
			snprintf(sha256_hex + (i * 2), sizeof(sha256_hex) - (i * 2),
			         "%02x", digest[i]);
		ret->bytes_written = write_ctx.bytes_written;
		if (content_type != NULL &&
		    (ret->content_type = Dz1Str_clone((str_t)content_type, errp)) == NULL)
			ERR_OUT(errp);
		else if ((ret->sha256_hex = Dz1Str_clone(sha256_hex, errp)) == NULL)
			ERR_OUT(errp);
		else if (rename(part_path, output_path_utf8) != 0)
			Dz1Error_setWithComment(errp, EIO,
				(DZ1_ERROR_ARG, "Cannot finalize streaming download file."));
		else
			Dz1Error_set(errp, 0);
	}

	if (options_attached)
	{
		(void)curl_easy_setopt(curl, CURLOPT_HTTPHEADER, NULL);
		(void)curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
		(void)curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
	}
	if (header != NULL) curl_slist_free_all(header);
	if (write_ctx.file != NULL) fclose(write_ctx.file);
	if (write_ctx.digest != NULL) EVP_MD_CTX_free(write_ctx.digest);
	if (ERR_IS_SUCCESS(errp) == FALSE)
	{
		if (part_path != NULL) remove(part_path);
		GitsnOpenApiDownloadResult_delAndSetNull((void *)&ret);
	}
	Dz1Free(part_path);
	return ret;
}
// GET
///////////////////////////////////////////////////////////////////////////////
