#include <Dz1SockUtil.h>

#include "GitsnOpenApiArg.h"
#include "GitsnOpenApiEnv.h"
#include "GitsnOpenApiMsgs.h"
#include "GitsnOpenApiTimerUtil.h"

#include "GitsnOpenApi_servant.h"

#include "GitsnOpenApi.h"

#ifndef UNIX_SYSTEM
#include <Windows.h>
#else
#include <time.h>
#endif

static u64_t _gitsn_open_api_monotonic_ms(void)
{
#ifndef UNIX_SYSTEM
	return (u64_t)GetTickCount64();
#else
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) return 0;
	return ((u64_t)now.tv_sec * 1000ULL) + ((u64_t)now.tv_nsec / 1000000ULL);
#endif
}

static bool_t _header_name_equals(str_t lhs, const char *rhs)
{
	if (lhs == NULL || rhs == NULL) return FALSE;
	while (*lhs != 0 && *rhs != 0)
	{
		if (tolower((unsigned char)*lhs++) != tolower((unsigned char)*rhs++)) return FALSE;
	}
	return (*lhs == 0 && *rhs == 0) ? TRUE : FALSE;
}

static bool_t _header_has_token(GitsnOpenApiDatas *headers, const char *name, const char *token)
{
	GitsnOpenApiDataEntry **entries = NULL;
	unsigned int count = 0;
	unsigned int i = 0;
	bool_t found = FALSE;

	if (headers == NULL || headers->storage == NULL || name == NULL || token == NULL) return FALSE;
	entries = headers->storage->get_array(headers->storage, &count, NULL);
	if (entries == NULL) return FALSE;
	for (i = 0; i < count && found == FALSE; i++)
	{
		GitsnOpenApiDataEntry *entry = entries[i];
		const char *cursor = entry != NULL ? entry->value_utf8 : NULL;
		if (entry == NULL || _header_name_equals(entry->key_utf8, name) == FALSE || cursor == NULL) continue;
		while (*cursor != 0)
		{
			const char *start = cursor;
			const char *segment_end = NULL;
			const char *trimmed_end = NULL;
			size_t token_len = strlen(token);
			while (*start != 0 && isspace((unsigned char)*start)) start++;
			segment_end = start;
			while (*segment_end != 0 && *segment_end != ',') segment_end++;
			trimmed_end = segment_end;
			while (trimmed_end > start && isspace((unsigned char)trimmed_end[-1])) trimmed_end--;
			if ((size_t)(trimmed_end - start) == token_len)
			{
				size_t j = 0;
				found = TRUE;
				for (j = 0; j < token_len; j++)
				{
					if (tolower((unsigned char)start[j]) != tolower((unsigned char)token[j]))
					{
						found = FALSE;
						break;
					}
				}
			}
			cursor = *segment_end == ',' ? segment_end + 1 : segment_end;
			if (found == TRUE || *cursor == 0) break;
		}
	}
	Dz1Memory_cancel(entries);
	return found;
}

static void _notify_connection_event(GitsnOpenApiArg *arg, GitsnOpenApiSession *session,
	GitsnOpenApiConnectionEventType event_type, u64_t closed_ms)
{
	GitsnOpenApiConnectionEvent event;

	if (arg == NULL || session == NULL || arg->connection_cb == NULL) return;
	/* A connection closed before any response is not Keep-Alive evidence. */
	if (event_type != GitsnOpenApiConnectionEventType_response_sent &&
		session->response_sequence == 0 && session->last_response_sent_ms == 0) return;
	memset(&event, 0, sizeof(event));
	event.event_type = event_type;
	event.session_id = session->id;
	event.response_sequence = session->response_sequence;
	event.configured_timeout_ms = arg->server_idle_timeout_ms;
	event.response_sent_monotonic_ms = session->last_response_sent_ms;
	event.connection_closed_monotonic_ms = closed_ms;
	if (closed_ms >= session->last_response_sent_ms && session->last_response_sent_ms != 0)
		event.elapsed_ms = closed_ms - session->last_response_sent_ms;
	arg->connection_cb(arg->connection_cb_arg, &event);
}

static void _cancel_idle_timer(GitsnOpenApiSession *session, void *timer)
{
	GitsnOpenApiTimer key;
	if (session == NULL || timer == NULL || session->idle_timer_armed == FALSE) return;
	memset(&key, 0, sizeof(key));
	key.id = session->id;
	GitsnOpenApiTimer_clr(timer, &key);
	session->idle_timer_armed = FALSE;
}

static bool_t _find_crlf(Dz1Binary const *flatten_bin, size_t *_inout_offset, size_t *ret_size, Dz1Error *errp)
{
	size_t offset = 0;
	if (flatten_bin == NULL || flatten_bin->data == NULL || _inout_offset == NULL || ret_size == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((offset = *_inout_offset) > flatten_bin->size)
		ERR_SET_OUT(errp, EFAULT);
	else if (offset == flatten_bin->size)
	{
		*ret_size = 0;
		Dz1Error_set(errp, 0);
	}
	else
	{
		bool_t found = FALSE;
		u8_t *bias = flatten_bin->data + offset, *cp = bias;
		size_t sz = flatten_bin->size - offset;
		while(sz)
		{
			if (cp[0] == 0x0D)
			{
				if (sz > 0 && cp[1] == 0x0A)
				{
					cp += 2;
					sz -= 2;
					found = TRUE;
					break;
				}
			}
			else
			{
				cp++;
				sz--;
			}
		}

		if (found) *ret_size = (size_t)(cp - bias); else *ret_size = 0;
		*_inout_offset = (size_t)(cp - flatten_bin->data);

		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// Parser : HTTP Header - First Line
static str_t _parse_http_first_line_set_method(GitsnOpenApiHttpReq *dst, str_t text_utf8, Dz1Error *errp)
{
	str_t ret = NULL;
	if (0) { }
	else if (strncmp(text_utf8, "GET ", 4) == 0)
	{
		dst->method = GitsnOpenApiHttpReqMethod_GET;
		ret = text_utf8 += 4;
		Dz1Error_set(errp, 0);
	}
	else if (strncmp(text_utf8, "POST ", 5) == 0)
	{
		dst->method = GitsnOpenApiHttpReqMethod_POST;
		ret = text_utf8 += 5;
		Dz1Error_set(errp, 0);
	}
	else
		ERR_SET_OUT(errp, ENOSYS);
	return ret;
}

// static bool_t _parse_req_arg(GitsnOpenApiDatas *dst, str_t arg_str_u8, Dz1Error *errp)
// {
// 	str_t key_u8 = arg_str_u8, value_u8;
// 	if ((value_u8 = strchr(key_u8, '=')) == NULL) ERR_SET_OUT(errp, EINVAL);
// 	else
// 	{
// 		*value_u8++ = 0;
// 		if (Dz1StrU8_fromURI(key_u8, errp) == NULL) ERR_OUT(errp);
// 		else if (Dz1StrU8_fromURI(value_u8, errp) == NULL) ERR_OUT(errp);
// 		else if (GitsnOpenApiDatas_appendEntryStrU(dst, key_u8, value_u8, errp) == FALSE) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
// 	}
// 	return ERR_IS_SUCCESS(errp);
// }

static str_t _parse_http_first_line_set_target(GitsnOpenApiHttpReq *dst, str_t text_utf8, Dz1Error *errp)
{	// target URI
	str_t cp = text_utf8, sp = NULL, ep = NULL, ret = NULL, temp = NULL;
	while(*cp && isspace((int)*cp & 0xFF)) cp++;	// pass front white space

	sp = cp;										// save start point
	while(*cp && !isspace((int)*cp & 0xFF)) cp++;	// pass letters
	ep = cp;										// sane end point;

	ret = ++cp;										// pass single white space & ret return value

	if ((temp = Dz1Str_ndup(sp, (size_t)(ep - sp), errp)) == NULL) ERR_OUT(errp);
	else
	{
		str_t ap = NULL;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
		if ((ap = strchr(temp, '?')) != NULL)											// has arguments
		{	
			GitsnOpenApiDatas *args = NULL;
			*ap++ = 0;	// make target object
			if ((dst->target_utf8 = Dz1Str_dup(temp, errp)) == NULL) ERR_OUT(errp);		// set target object
			else if (Dz1StrU8_fromURI(dst->target_utf8, errp) == NULL) ERR_OUT(errp);	// refine target object string

			/* Query components are decoded after splitting, preserving encoded & and =. */					// refine arguments string
			else if (*ap == 0) Dz1Error_set(errp, 0);
			else if ((dst->args = GitsnOpenApiDatas_genFromArgStrU(ap, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1StrU8_fromURI(temp, errp) == NULL) ERR_OUT(errp);					// no arguments
		else
		{
			dst->target_utf8 = temp; temp = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
	}
	return SELECT_BY_ERR(errp, ret, NULL);
}

static str_t _parse_http_first_line_set_ver(GitsnOpenApiHttpReq *dst, str_t text_utf8, Dz1Error *errp)
{	// version parse
	str_t cp = text_utf8, ret = NULL, delim = NULL;

	while(*cp && isspace((int)*cp & 0xFF)) cp++;	// pass front white space

	if ((delim = strchr(cp, '/')) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((dst->prot = Dz1Str_ndup(cp, (size_t)(delim - cp), errp)) == NULL) ERR_OUT(errp);
	else
	{	// pass "{prot}/"
		str_t sp = ++delim, ep = NULL, temp = NULL;	// save start point (= cp + 5)
		while(*cp && !isspace((int)*cp & 0xFF)) cp++;	// pass letters
		ep = cp;										// save end point

		if ((temp = Dz1Str_ndup(sp, (size_t)(ep - sp), errp)) == NULL) ERR_OUT(errp);
		else
		{
			str_t dot = NULL;
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
			if ((dot = strchr(temp, '.')) == NULL)
			{
				dst->ver_maj = (u16_t)Dz1Ato32(temp);
				dst->ver_min = 0;
			}
			else
			{
				*dot++ = 0;
				dst->ver_maj = (u16_t)Dz1Ato32(temp);
				dst->ver_min = (u16_t)Dz1Ato32(dot);
			}
			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
			Dz1Error_set(errp, 0);
			ret = cp;
		}
	}
	return ret;
}

static bool_t _parse_http_first_line(GitsnOpenApiHttpReq *dst, str_t text_utf8, Dz1Error *errp)
{
	char *cp = text_utf8;

	if		((cp = _parse_http_first_line_set_method(dst, cp, errp)) == NULL) ERR_OUT(errp);
	else if ((cp = _parse_http_first_line_set_target(dst, cp, errp)) == NULL) ERR_OUT(errp);
	else if ((cp = _parse_http_first_line_set_ver(dst, cp, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// Parser : HTTP Header - First Line
///////////////////////////////////////////////////////////////////////////////

static Dz1ListAddCancel_impl(GitsnOpenApiDataIndex, GitsnOpenApiDataEntry)
bool_t GitsnOpenApiDatas_append(GitsnOpenApiDatas *dst, str_t name_u8, str_t value_u8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiDataEntry *node = NULL;
	if (dst == NULL || Dz1Str_isVoid(name_u8) || Dz1Str_isVoid(value_u8)) ERR_SET_OUT(errp, EINVAL);
	else if ((node = GitsnOpenApiDataEntry_new(name_u8, value_u8, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiDataEntry_delAndSetNull, (void *)&node);
		if ((*errp = dst->index->add(dst->index, node)).code)
		{
			/* 반복 Query/Header는 유효한 HTTP 표현이다. 첫 항목은 검색 index에
			 * 유지하고 모든 항목을 storage에 보존해 상위 검증기가 중복 여부를 판정한다. */
			if (errp->code != EEXIST) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				if ((*errp = dst->storage->add(dst->storage, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
			}
		}
		else
		{
			Dz1ListAddCancelArg arg = { (void *)dst->index, (void **)&node };
			pthread_cleanup_push(GitsnOpenApiDataIndex_addCancel, (void *)&arg);
			if ((*errp = dst->storage->add(dst->storage, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (GitsnOpenApiDataIndex_addCancel, (void *)&arg);
		}
		pthread_cleanup_pop(1); // (GitsnOpenApiDataEntry_delAndSetNull, (void *)&node);
	}
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// Parser : HTTP Header - Data Line
static str_t _trim_string(str_t src)
{
	str_t ret = NULL;
	if (Dz1Str_isVoid(src) == FALSE)
	{
		str_t dp = src, sp = src, last_space = NULL;
		while(*sp && isspace((int)*sp & 0xFF)) sp++;
		while(*sp) *dp++ = *sp++;
		*dp = 0;
		dp--;
		while(dp > src && isspace((int)*dp & 0xFF)) *dp-- = 0;
		ret = src;
	}
	return ret;
}

static bool_t _parse_http_hdr_data(GitsnOpenApiDatas *dst, str_t text_utf8, Dz1Error *errp)
{
	str_t name = text_utf8;
	str_t value = strchr(name, ':');
	if (value == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		*value++ = 0;
		if (_trim_string(name) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (Dz1StrU8_fromURI(name, errp) == NULL) ERR_OUT(errp);
		else if (_trim_string(value) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (Dz1StrU8_fromURI(value, errp) == NULL) ERR_OUT(errp);
		else if (GitsnOpenApiDatas_append(dst, name, value, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// Parser : HTTP Header - Data Line
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Parser : HTTP Header
static bool_t _build_header(GitsnOpenApiHttpReq *dst, GitsnOpenApiHttpLines *lines, Dz1Error *errp)
{
	str_t first_line = NULL;
	if (dst->header != NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst->header = GitsnOpenApiDatas_new(errp)) == NULL) ERR_OUT(errp);
	else if ((first_line = lines->extract(lines, NULL)) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		str_t single_line = NULL;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&first_line);

		if (_parse_http_first_line(dst, first_line, errp) == FALSE) ERR_OUT(errp);
		else while(errp->code == 0 && (single_line = lines->extract(lines, NULL)) != NULL)
		{
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&single_line);
			if (_parse_http_hdr_data(dst->header, single_line, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&single_line);
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&first_line);
	}
	return ERR_IS_SUCCESS(errp);
}
// Parser : HTTP Header
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Parser : HTTP
static bool_t _callback_http_req(GitsnOpenApiCallback cb, void *cb_ptr, u32_t session_id, GitsnOpenApiHttpReq **req, Dz1Error *errp)
{
	GitsnOpenApiMsg *msg = NULL;
	if (cb == NULL) Dz1Error_set(errp, 0);
	else if ((msg = GitsnOpenApiMsg_new(session_id, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnOpenApiHttpMsg *ctx = NULL;
		pthread_cleanup_push(GitsnOpenApiMsg_delAndSetNull, (void *)&msg);
		if ((msg->ctx = ctx = GitsnOpenApiHttpMsg_new(GitsnOpenApiHttpMsgPresent_req, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ctx->x.req = (*req); (*req) = NULL;
			cb(cb_ptr, &msg);
		}
		pthread_cleanup_pop(1); // (GitsnOpenApiMsg_delAndSetNull, (void *)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _end_of_header(GitsnOpenApiHttpParser *p, u32_t session_id, GitsnOpenApiCallback cb, void *cb_ptr, Dz1Error *errp)
{
	GitsnOpenApiHttpReq *req = NULL;
	if (p->req != NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((req = GitsnOpenApiHttpReq_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnOpenApiMsg *msg = NULL;
		GitsnOpenApiDataEntry *clen = NULL;
		pthread_cleanup_push(GitsnOpenApiHttpReq_delAndSetNull, (void *)&req);

		if (_build_header(req, p->hdr_lines, errp) == FALSE) ERR_OUT(errp);
		else
		{
			p->close_after_response = _header_has_token(req->header, "Connection", "close");
			switch(req->method)
		{
		case GitsnOpenApiHttpReqMethod_GET:
			/* Preserve a declared GET body for rejection evidence. The scenario
			 * still rejects it; a request without Content-Length remains bodyless. */
			if (GitsnOpenApiDatas_findU(req->header, "Content-Length", NULL) == NULL)
			{
				if (_callback_http_req(cb, cb_ptr, session_id, &req, errp) == FALSE) ERR_OUT(errp);
				else { p->body_size = -1; p->state = GitsnOpenApiHttpState_header; Dz1Error_set(errp, 0); }
				break;
			}
			/* fall through: collect the body before passing the request on. */
		case GitsnOpenApiHttpReqMethod_POST:
			if ((clen = GitsnOpenApiDatas_findU(req->header, "Content-Length", NULL)) != NULL)
			{
				ssize_t body_size;
				body_size = (ssize_t)Dz1Ato64(clen->value_utf8);
				if (body_size < 0) ERR_SET_OUT(errp, EINVAL);
				else if (body_size == 0)
				{
					/* 본문이 없는 POST도 유효한 HTTP 요청이다. 시나리오 검증 단계에서
					 * Method, Content-Type 및 필수 Body를 각각 판정할 수 있도록 전달한다. */
					if (_callback_http_req(cb, cb_ptr, session_id, &req, errp) == FALSE) ERR_OUT(errp);
					else
					{
						p->body_size = -1;
						p->state = GitsnOpenApiHttpState_header;
						Dz1Error_set(errp, 0);
					}
				}
				else
				{
					p->state = GitsnOpenApiHttpState_body;
					p->body_size = body_size;
					p->req = req; req = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			// other way to get length of contents
			else
			{
				ERR_SET_OUT(errp, EINVAL);
				Dz1Thread_printf(Dz1T("!!! Request = ")); GitsnOpenApiHttpReq_dump(req, 0);
			}
			break;	// POST has body
		default:
			if (_callback_http_req(cb, cb_ptr, session_id, &req, errp) == FALSE) ERR_OUT(errp);
			else
			{
				p->body_size = -1;
				p->state = GitsnOpenApiHttpState_header;
				Dz1Error_set(errp, 0);
			}
			break;
		}
		}
		pthread_cleanup_pop(1); // (GitsnOpenApiHttpReq_delAndSetNull, (void *)&req);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t GitsnOpenApiHttpParser_parse(GitsnOpenApiHttpParser *p, u32_t session_id, Dz1Binary *stream, GitsnOpenApiCallback cb, void *cb_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	str_t single_line;
	ssize_t offset = 0, length;

	if (p == NULL || stream == NULL || cb == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (stream->size == 0) Dz1Error_set(errp, 0);
	else
	{
		u32_t log_lv = 0;
		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
		if (log_lv & DZ1_THREAD_LOG_DEBUG)
		{
			/* Raw HTTP packets may contain credentials, so only their size is logged. */
			Dz1Thread_printf(Dz1T("<<< Received HTTP Packet (%u bytes, content redacted)\n"), stream->size);
		}

		if (_Dz1ElasticBuf_push(p->rx_buf, stream->data, stream->size, errp) == FALSE) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			Dz1Binary const *bin;
			bool_t action = FALSE;

			do
			{
				action = FALSE;
				switch(p->state)
				{
				case GitsnOpenApiHttpState_header:
					if ((bin = Dz1ElasticBuf_flatten(p->rx_buf, errp)) == NULL) ERR_OUT(errp);
					else if (bin->size == 0) { Dz1Error_set(errp, 0); break; }		// no data to process -> end
					else
					{
						bool_t header_done = FALSE;
						ssize_t offset = 0;
						do 
						{
							if (_find_crlf(bin, &offset, &length, errp) == FALSE) ERR_OUT(errp);
							else if (length == 0) { Dz1Error_set(errp, 0); break; }	// no CRLF -> end
							else if ((single_line = Dz1Calloc(sizeof(char), length + 1, errp)) == NULL) ERR_OUT(errp);
							else
							{
								pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&single_line);
								if ((sz = Dz1ElasticBuf_pop(p->rx_buf, single_line, length, errp)) < 0) ERR_OUT(errp);
								else if (sz != length) ERR_SET_OUT(errp, EPIPE);
								else if (strcmp(single_line, "\r\n") != 0)											// context line
								{
									single_line[sz - 2] = 0;	// trim '\r\n'
									if ((*errp = p->hdr_lines->add(p->hdr_lines, single_line)).code) ERR_OUT(errp);
									else
									{
										single_line = NULL;
										action = TRUE;
										Dz1Error_set(errp, 0);
									}
								}
								else if (_end_of_header(p, session_id, cb, cb_ptr, errp) == FALSE) ERR_OUT(errp);	// end of header
								else
								{
									action = TRUE;
									header_done = TRUE;
									Dz1Error_set(errp, 0);
								}
								pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&single_line);
							}
						} while(errp->code == 0 && header_done == FALSE);
					}
					break;
				case GitsnOpenApiHttpState_body:
					if (p->body_size == -1) ERR_SET_OUT(errp, EFAULT);
					else if ((sz = Dz1ElasticBuf_getDataSize(p->rx_buf, errp)) < 0) ERR_OUT(errp);
					else if (sz >= p->body_size)
					{
						ssize_t rd_sz;
						Dz1Binary *body = NULL;
						GitsnOpenApiHttpReq *req = NULL;
						if ((req = p->req) == NULL) ERR_SET_OUT(errp, EFAULT);
						else if (req->body != NULL) ERR_SET_OUT(errp, EFAULT);
						else if ((req->body = body = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, (u32_t)p->body_size, errp)) == NULL) ERR_OUT(errp);
						else if ((rd_sz = Dz1ElasticBuf_pop(p->rx_buf, body->data, body->size, errp)) < 0) ERR_OUT(errp);
						else if (rd_sz != p->body_size) ERR_SET_OUT(errp, EFAULT);
						else if (_callback_http_req(cb, cb_ptr, session_id, &p->req, errp) == FALSE) ERR_OUT(errp);
						else
						{
							p->body_size = -1;
							p->state = GitsnOpenApiHttpState_header;
							action = TRUE;
							Dz1Error_set(errp, 0);
						}
					}
					else Dz1Error_set(errp, 0);
					break;
				}
			} while(errp->code == 0 && action);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Parser : HTTP
///////////////////////////////////////////////////////////////////////////////

static Dz1TaskProcStatus _session_idle_timeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
	GitsnOpenApiTimer *tmr = tData != NULL ? (GitsnOpenApiTimer *)*tData : NULL;
	GitsnOpenApiSession key;
	GitsnOpenApiSession *session = NULL;
	u64_t closed_ms = _gitsn_open_api_monotonic_ms();
	(void)timer;

	if (arg == NULL || env == NULL || env->sessions == NULL || tmr == NULL)
		ERR_SET_OUT(errp, EFAULT);
	else
	{
		memset(&key, 0, sizeof(key));
		key.id = tmr->id;
		session = env->sessions->table->extract(env->sessions->table, &key);
		if (session == NULL)
			Dz1Error_set(errp, 0);
		else
		{
			session->idle_timer_armed = FALSE;
			if (session->response_call != NULL)
				Dz1TaskSigMsg_setErr((Dz1TaskSigMsg *)session->response_call, ETIMEDOUT);
			_notify_connection_event(arg, session, session->response_pending || session->response_call != NULL ?
				GitsnOpenApiConnectionEventType_transport_error : GitsnOpenApiConnectionEventType_server_idle_timeout, closed_ms);
			GitsnOpenApiSession_del(session);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

bool_t GitsnOpenApi_servantDeferResponse(void *uRsc, void *timer,
    u32_t session_id, void **signal, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
    GitsnOpenApiSession key = { session_id };
    GitsnOpenApiSession *session = env->sessions->table->find(env->sessions->table, &key);
    GitsnOpenApiTimer *tmr = NULL;
    if (session == NULL || !session->response_pending || signal == NULL || *signal == NULL)
        ERR_SET_OUT(errp, EINVAL);
    else if (session->response_call != NULL) ERR_SET_OUT(errp, EBUSY);
    else if ((tmr = GitsnOpenApiTimer_new(session_id, errp)) == NULL) ERR_OUT(errp);
    else if ((*errp = GitsnOpenApiTimer_update(timer, &tmr, 30000000ULL, _session_idle_timeout)).code) ERR_OUT(errp);
    else
    {
        tmr = NULL;
        session->idle_timer_armed = TRUE;
        session->response_call = *signal;
        *signal = NULL;
        Dz1Error_set(errp, 0);
    }
    if (tmr != NULL) GitsnOpenApiTimer_del(tmr);
    return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// DZ1_SOCK_UTIL_RECEIVER2_RECEIVED
static Dz1TaskProcStatus _session_received(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1SockUtilReceiver2Received *msg = (Dz1SockUtilReceiver2Received *)Dz1TaskSigMsg_getData(*sg);

	GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
	GitsnOpenApiSessions *sessions = env->sessions;
	GitsnOpenApiSessionTable *table = sessions->table;
	GitsnOpenApiSession key = { msg->sessionID };
	GitsnOpenApiSession *session = table->find(table, &key);


	if (session != NULL)
	{
		GitsnOpenApiMsg *notify = NULL;
		_cancel_idle_timer(session, timer);
		if (session->parser != NULL)
		{	// HTTP mode
			if (GitsnOpenApiHttpParser_parse(session->parser, session->id, msg->stream, arg->http_cb, arg->http_cb_ptr, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if ((notify = GitsnOpenApiMsg_new(session->id, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			GitsnOpenApiHttpMsg *ctx = NULL;
			pthread_cleanup_push(GitsnOpenApiMsg_delAndSetNull, (void *)&notify);
			if ((notify->ctx = ctx = GitsnOpenApiHttpMsg_new(GitsnOpenApiHttpMsgPresent_ws_payload, msg->stream, errp)) == NULL) ERR_OUT(errp);
			else
			{
				msg->stream = NULL;
				arg->http_cb(arg->http_cb_ptr, &notify);
			}
			pthread_cleanup_pop(1); // (GitsnOpenApiMsg_delAndSetNull, (void *)&notify);
			Dz1Error_set(errp, 0);
		}

		if (errp->code != 0)
		{
			char buf[53];
			_notify_connection_event(arg, session, GitsnOpenApiConnectionEventType_transport_error, _gitsn_open_api_monotonic_ms());
			table->extract(table, session);
			pthread_cleanup_push(GitsnOpenApiSession_delAndSetNull, (void *)&session);
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "!!! Close session due to processing fail : %s\n", Dz1SockAddrA_printable(session->peer, buf, FALSE, NULL));
			pthread_cleanup_pop(1); // (GitsnOpenApiSession_delAndSetNull, (void *)&session);
		}
	}
	return ret;
}
// DZ1_SOCK_UTIL_RECEIVER2_RECEIVED
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED
static Dz1TaskProcStatus _session_terminated(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1SockUtilReceiver2Received *msg = (Dz1SockUtilReceiver2Received *)Dz1TaskSigMsg_getData(*sg);

	GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
	GitsnOpenApiSessions *sessions = env->sessions;
	GitsnOpenApiSession key = { msg->sessionID };
	GitsnOpenApiSession *session = sessions->table->extract(sessions->table, &key);

	if (session != NULL)
	{
		char buf[53];
		Dz1TaskSigMsg *finished = NULL;
		pthread_cleanup_push(Dz1TaskSigMsg_TermDelAndSetNull, (void *)&finished);
		_cancel_idle_timer(session, timer);
		_notify_connection_event(arg, session, session->closing && !session->response_pending ?
			session->close_event_type : GitsnOpenApiConnectionEventType_peer_closed, _gitsn_open_api_monotonic_ms());
		if (session->closing && !session->response_pending && session->response_call != NULL &&
			Dz1TaskSigMsg_getErrPtr((Dz1TaskSigMsg *)*sg)->code == 0)
		{
			finished = (Dz1TaskSigMsg *)session->response_call;
			session->response_call = NULL;
		}
		pthread_cleanup_push(GitsnOpenApiSession_delAndSetNull, (void *)&session);
		Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "!!! Session Disconnected : %s\n", Dz1SockAddrA_printable(session->peer, buf, FALSE, NULL));
		pthread_cleanup_pop(1); // (GitsnOpenApiSession_delAndSetNull, (void *)&session);
		if (finished != NULL)
		{
			Dz1TaskSigMsg_setErr(finished, 0);
			Dz1TaskSigMsg_termDelAndSetNull(&finished);
		}
		pthread_cleanup_pop(0);
	}
	return ret;
}
// DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DZ1_SOCK_UTIL_TRANSMITER2_SENT
static Dz1TaskProcStatus _session_sent(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1SockUtilReceiver2Received *msg = (Dz1SockUtilReceiver2Received *)Dz1TaskSigMsg_getData(*sg);

	GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
	GitsnOpenApiSessions *sessions = env->sessions;
	GitsnOpenApiSession key = { msg->sessionID };
	GitsnOpenApiSession *session = sessions->table->find(sessions->table, &key);

	if (session != NULL)
	{
		if (Dz1SockUtilTxFifo_sentProc(session->tx_fifo, session->sock, errp) == FALSE)
		{
			_notify_connection_event(arg, session, GitsnOpenApiConnectionEventType_transport_error, _gitsn_open_api_monotonic_ms());
			sessions->table->extract(sessions->table, session);
			GitsnOpenApiSession_del(session);
			ERR_OUT(errp);
		}
		else if (Dz1SockUtilTxFifo_isEmpty(session->tx_fifo) && session->response_pending)
		{
			GitsnOpenApiTimer *tmr = NULL;
			Dz1TaskSigMsg *response_call = (Dz1TaskSigMsg *)session->response_call;
			pthread_cleanup_push(Dz1TaskSigMsg_TermDelAndSetNull, (void *)&response_call);
			session->response_call = NULL;
			_cancel_idle_timer(session, timer);
			session->response_pending = FALSE;
			session->last_response_sent_ms = _gitsn_open_api_monotonic_ms();
			_notify_connection_event(arg, session, GitsnOpenApiConnectionEventType_response_sent, 0);
			if (session->closing)
			{
				/* Keep the standing receive alive for the peer's EOF after our FIN.
				 * Closing an overlapped socket here can reset unread peer data. */
				if (!GitsnOpenApi_shutdownSend(session->sock, errp)) ERR_OUT(errp);
				else if ((tmr = GitsnOpenApiTimer_new(session->id, errp)) == NULL) ERR_OUT(errp);
				else if ((*errp = GitsnOpenApiTimer_update(timer, &tmr, 30000000ULL, _session_idle_timeout)).code) ERR_OUT(errp);
				else
				{
					tmr = NULL;
					session->idle_timer_armed = TRUE;
					session->response_call = response_call;
					response_call = NULL;
					Dz1Error_set(errp, 0);
				}
				if (tmr != NULL) GitsnOpenApiTimer_del(tmr);
			}
			else if (arg->server_idle_timeout_ms > 0)
			{
				if ((tmr = GitsnOpenApiTimer_new(session->id, errp)) == NULL) ERR_OUT(errp);
				else if ((*errp = GitsnOpenApiTimer_update(timer, &tmr, (u64_t)arg->server_idle_timeout_ms * 1000ULL,
					_session_idle_timeout)).code) ERR_OUT(errp);
				else
				{
					tmr = NULL;
					session->idle_timer_armed = TRUE;
					Dz1Error_set(errp, 0);
				}
				if (tmr != NULL) GitsnOpenApiTimer_del(tmr);
			}
			else Dz1Error_set(errp, 0);
			if (response_call != NULL)
			{
				Dz1TaskSigMsg_setErr(response_call, errp->code);
				Dz1TaskSigMsg_termDelAndSetNull(&response_call);
			}
			pthread_cleanup_pop(0);
		}
		else Dz1Error_set(errp, 0);
	}

	return ret;
}
// DZ1_SOCK_UTIL_TRANSMITER2_SENT
///////////////////////////////////////////////////////////////////////////////

bool_t GitsnOpenApi_servantMsgInit(Dz1Task *task, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER2_RECEIVED),	 _session_received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED), _session_terminated)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER2_SENT),		 _session_sent)).code) ERR_OUT(errp);
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// _encode_http_hdr
static bool_t _encode_http_hdr_date(Dz1ElasticBuf *dst, Dz1Error *errp)
{
	char str_date[64];
	time_t tNow = time(NULL);
	if (GitsnOpenApiUtil_initDateStrU(str_date, sizeof(str_date), &tNow, errp) == FALSE) ERR_OUT(errp);
	else
	{
		char buf[64];
		_std_snprintfA(buf, sizeof(buf) - 1, "Date: %s\r\n", str_date);
		if (Dz1ElasticBuf_pushStrA(dst, buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _encode_http_hdr_server(Dz1ElasticBuf *dst, str_t server_name_u8, Dz1Error *errp)
{
	char buf[64];
	_std_snprintfA(buf, sizeof(buf) - 1, "Server: %s\r\n", server_name_u8);
	if (Dz1ElasticBuf_pushStrA(dst, buf, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _encode_http_hdr_contents_size(Dz1ElasticBuf *dst, ssize_t sz, Dz1Error *errp)
{
	char buf[1024];
	_std_snprintfA(buf, sizeof(buf) - 1, "Content-Length: " DZ1_FMT64_A "\r\n", sz);
	if (Dz1ElasticBuf_pushStrA(dst, buf, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static Dz1Error __encode_http_hdr(void *ptr, GitsnOpenApiDataEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ElasticBuf *dst = (Dz1ElasticBuf *)ptr;

	str_t buf = NULL;
	size_t len = strlen(p->key_utf8) + 2 + strlen(p->value_utf8) + 2;
	if ((buf = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
		_std_snprintfA(buf, len, "%s: %s\r\n", p->key_utf8, p->value_utf8);
		if (Dz1ElasticBuf_pushStrA(dst, buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
	}
	return err;
}

static bool_t _headers_contains_name(GitsnOpenApiDatas *headers, const char *name)
{
	GitsnOpenApiDataEntry **entries = NULL;
	unsigned int count = 0;
	unsigned int i = 0;
	bool_t found = FALSE;

	if (headers == NULL || headers->storage == NULL || name == NULL) return FALSE;
	entries = headers->storage->get_array(headers->storage, &count, NULL);
	if (entries == NULL) return FALSE;
	for (i = 0; i < count; i++)
	{
		if (entries[i] != NULL && _header_name_equals(entries[i]->key_utf8, name))
		{
			found = TRUE;
			break;
		}
	}
	Dz1Memory_cancel(entries);
	return found;
}

static bool_t _encode_http_hdr_value(Dz1ElasticBuf *dst, const char *name, const char *value, Dz1Error *errp)
{
	char line[128] = { 0, };
	if (dst == NULL || name == NULL || value == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		_std_snprintfA(line, sizeof(line) - 1, "%s: %s\r\n", name, value);
		if (Dz1ElasticBuf_pushStrA(dst, line, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _encode_http_hdr(Dz1ElasticBuf *dst, str_t servant_name_u8, GitsnOpenApiDatas *hdr, Dz1ElasticBuf *body,
	GitsnOpenApiArg *arg, bool_t close_after_response, Dz1Error *errp)
{
	GitsnOpenApiDataList *list = NULL;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_encode_http_hdr_date(dst, errp) == FALSE) ERR_OUT(errp);
	else if (_encode_http_hdr_server(dst, servant_name_u8, errp) == FALSE) ERR_OUT(errp);
	else
	{
		if (hdr != NULL)
		{
			if ((list = hdr->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((*errp = list->travel(list, __encode_http_hdr, (void *)dst)).code) ERR_OUT(errp);
		}
		if (ERR_IS_SUCCESS(errp) && body != NULL)
		{
			ssize_t sz = 0;
			if ((sz = Dz1ElasticBuf_getDataSize(body, errp)) < 0) ERR_OUT(errp);
			else if (_encode_http_hdr_contents_size(dst, sz, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (ERR_IS_SUCCESS(errp) && _encode_http_hdr_contents_size(dst, 0, errp) == FALSE) ERR_OUT(errp);
	}

	if (ERR_IS_SUCCESS(errp) && close_after_response && _headers_contains_name(hdr, "Connection") == FALSE)
	{
		if (_encode_http_hdr_value(dst, "Connection", "close", errp) == FALSE) ERR_OUT(errp);
	}
	else if (ERR_IS_SUCCESS(errp) && close_after_response == FALSE && arg != NULL && arg->advertise_keep_alive)
	{
		char timeout_value[32] = { 0, };
		u32_t timeout_seconds = arg->server_idle_timeout_ms / 1000;
		if (timeout_seconds == 0 && arg->server_idle_timeout_ms > 0) timeout_seconds = 1;
		if (_headers_contains_name(hdr, "Connection") == FALSE &&
			_encode_http_hdr_value(dst, "Connection", "keep-alive", errp) == FALSE) ERR_OUT(errp);
		else if (_headers_contains_name(hdr, "Keep-Alive") == FALSE)
		{
			_std_snprintfA(timeout_value, sizeof(timeout_value) - 1, "timeout=%u", timeout_seconds);
			if (_encode_http_hdr_value(dst, "Keep-Alive", timeout_value, errp) == FALSE) ERR_OUT(errp);
		}
	}

	return ERR_IS_SUCCESS(errp);
}
// _encode_http_hdr
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// _encode_http_response
static Dz1ElasticBuf *_encode_http_response(GitsnOpenApiHttpRsp *msg, str_t server_name_u8, GitsnOpenApiArg *arg,
	bool_t close_after_response, Dz1Error *errp)
{
	Dz1ElasticBuf *ret = NULL;
	if (msg == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char ver[16] = { 0, }, first[1024] = { 0, };
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&ret);

		if (msg->ver_min == 0) _std_snprintfA(ver, sizeof(ver) - 1, "%u", msg->ver_maj);
		else _std_snprintfA(ver, sizeof(ver) - 1, "%u.%u", msg->ver_maj, msg->ver_min);
		_std_snprintfA(first, sizeof(first) - 1, "%s/%s %u %s\r\n", msg->prot, ver, msg->code, msg->code_txt_utf8);	// generate first line

		if (Dz1ElasticBuf_pushStrA(ret, first, errp) == FALSE) ERR_OUT(errp);									// first line
		else if (_encode_http_hdr(ret, server_name_u8, msg->header, msg->body, arg, close_after_response, errp) == FALSE) ERR_OUT(errp);	// headers
		else if (Dz1ElasticBuf_pushStrA(ret, "\r\n", errp) == FALSE) ERR_OUT(errp);								// end-of-header
		else if (msg->body != NULL && Dz1ElasticBuf_getDataSize(msg->body, NULL) > 0)
		{	// body encode
			Dz1Binary const *bin;
			if ((bin = Dz1ElasticBuf_flatten(msg->body, errp)) == NULL) ERR_OUT(errp);
			else if (_Dz1ElasticBuf_push(ret, bin->data, bin->size, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ElasticBuf_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// _encode_http_response
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApi_servantDoRsp
bool_t GitsnOpenApi_servantDoRsp(void *uArg, void *uRsc, void *timer, u32_t session_id, GitsnOpenApiHttpRsp *msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
	GitsnOpenApiSessions *sessions = env->sessions;
	GitsnOpenApiSession key = { session_id }, *session = sessions->table->find(sessions->table, &key);
	bool_t close_after_response = FALSE;

	Dz1ElasticBuf *elb = NULL;

	if (session == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (session->response_pending) ERR_SET_OUT(errp, EBUSY);
	else
	{
		close_after_response = session->parser != NULL ? session->parser->close_after_response : FALSE;
		if ((elb = _encode_http_response(msg, arg->servant_name_u8, arg, close_after_response, errp)) == NULL) ERR_OUT(errp);
	}
	if (ERR_IS_SUCCESS(errp) && elb != NULL)
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		if ((bin = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t log_lv = 0;
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

			Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
			if (log_lv & DZ1_THREAD_LOG_DEBUG)
			{
				u32_t dump_sz = bin->size >= 256 ? 256 : bin->size;
				Dz1Thread_printf(Dz1T(">>> send data\n"));
				Dz1Thread_tprintb(1, bin->data, dump_sz, 16, TRUE);
				if (dump_sz < bin->size) Dz1Thread_tprintf(1, Dz1T("*** data dump is truncated %u/%u ***\n"), dump_sz, bin->size);
			}

			if (Dz1SockUtilTxFifo_send2(session->tx_fifo, session->sock, &bin, errp) == FALSE) ERR_OUT(errp);
			else
			{
				bin = NULL;
				session->response_sequence++;
				session->response_pending = TRUE;
				session->closing = close_after_response;
				session->close_event_type = GitsnOpenApiConnectionEventType_connection_close;
				if (session->parser != NULL) session->parser->close_after_response = FALSE;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return ERR_IS_SUCCESS(errp);
}
// GitsnOpenApi_servantDoRsp
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApi_servantWsSend
bool_t GitsnOpenApi_servantWsSend(void *uArg, void *uRsc, void *timer, u32_t session_id, Dz1Binary *ws_payload, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
	GitsnOpenApiSessions *sessions = env->sessions;
	GitsnOpenApiSession key = { session_id };
	GitsnOpenApiSession *session = sessions->table->find(sessions->table, &key);

	if (session == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (session->parser != NULL) ERR_SET_OUT(errp, EPERM);
	else if (Dz1SockUtilTxFifo_send(session->tx_fifo, session->sock, ws_payload->data, ws_payload->size, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// GitsnOpenApi_servantWsSend
///////////////////////////////////////////////////////////////////////////////

bool_t GitsnOpenApi_servantRemoveSession(void *uArg, void *uRsc, void *timer, u32_t session_id, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
	GitsnOpenApiSessions *sessions = env->sessions;
	GitsnOpenApiSession key = { session_id };
	GitsnOpenApiSession *session = sessions->table->extract(sessions->table, &key);
	if (session == NULL) Dz1Error_set(errp, ENOENT);
	else
	{
		char buf[53];
		_cancel_idle_timer(session, timer);
		Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "!!! Session Remove : %s\n", Dz1SockAddrA_printable(session->peer, buf, FALSE, NULL));
		GitsnOpenApiSession_delAndSetNull((void **)&session);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
