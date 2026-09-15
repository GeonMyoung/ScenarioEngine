#include "stdafx.h"
#include <afxinet.h>
#include <codeconv.h>
#include "dz1_mfc.h"
//#include <dz1_thread_stdio.h>
// #include <dz1_malloc.h>
#include "Dz1MfcHtmlUtil.h"

#define HTML_BUF_DECLARE_SIZE		4096
#ifdef UNICODE
#define HTML_BUF_IO_SIZE			(HTML_BUF_DECLARE_SIZE >> 1)
#else
#define HTML_BUF_IO_SIZE			HTML_BUF_DECLARE_SIZE
#endif

#ifdef HEML_DEBUG
static u32_t download_seq = 0;
static void _temp_save(Dz1Str p)
{
	if (p != NULL && p[0] != 0)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		TCHAR name[1024] = { 0, };
		size_t len = Dz1STRLEN(p);
		FILE *fp = NULL;
#ifdef UNICODE
		wsprintf(name, L"html_download_%08X.txt", download_seq++);
#else
		sprintf(name, "html_download_%08X.txt", download_seq++);
#endif
		if ((fp = Dz1FileStream_open(name, Dz1Text("wb"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
			fwrite(p, sizeof(TCHAR), len, fp);
			pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
		}
	}
}
#endif

static void CInternetFile_cancel(void *ptr)
{
//	CInternetFile *p = (CInternetFile *)ptr;
	CHttpFile *p = (CHttpFile *)ptr;
	if (p != NULL)
	{
		p->Close();
		delete p;
	}
}

Dz1Str Dz1MfcHtmlGetSource(Dz1Str url, Dz1Error *err)
{
	Dz1Str ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1ElasticBuf *elb = NULL;
	if ((elb = Dz1ElasticBuf_new(4096, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		CInternetSession session;
//		CInternetFile *file = (CInternetFile *)session.OpenURL(url, 1, INTERNET_FLAG_TRANSFER_BINARY);
		CHttpFile *file = (CHttpFile *)session.OpenURL(url, 1, INTERNET_FLAG_TRANSFER_BINARY);
		if (file == NULL) ERR_SET_OUT(errp, EPIPE);
		else
		{
			pthread_cleanup_push(CInternetFile_cancel, (void *)file);
			u8_t temp[HTML_BUF_DECLARE_SIZE] = { 0, };
			while(file->ReadString((LPTSTR)temp, HTML_BUF_IO_SIZE) != NULL)
				if ((*errp = Dz1ElasticBuf_push(elb, temp, strlen((str_t)temp) )).code) ERR_OUT(errp);

			Dz1Binary const * const flat = Dz1ElasticBuf_flatten(elb, errp);
			if (flat == NULL) ERR_OUT(errp);
			else
			{
#ifdef UNICODE
				size_t wcs_byte_size = flat->size << 1;
				if ((ret = (Dz1Str)Dz1Malloc(wcs_byte_size + sizeof(wchar_t), errp)) == NULL) ERR_OUT(errp);
				else
				{
					ssize_t ret_sz = 0;
					pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);

					if ((ret_sz = Dz1CodeConv((u8_t *)ret, wcs_byte_size, WINDOWS_UNICODE, flat->data, flat->size, "UTF-8")) < 0) ERR_SET_OUT(errp, EFAULT);
					else if (ret_sz == 0) ERR_SET_OUT(errp, EINVAL);
					else
					{
						Dz1Thread_printf(Dz1T("Dz1MfcHtmlGetSource() : converted = %u Bytes, src_bytes = %u\n"), ret_sz, flat->size);
						Dz1Error_set(errp, 0);
					}

					pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
				}
#else
				if ((ret = Dz1Str_dup((Dz1Str)flat->data, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
#endif
#ifdef HEML_DEBUG
				_temp_save(ret);
#endif
			}
			pthread_cleanup_pop(1); // (CInternetFile_cancel, (void *)file);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return ret;
}

// Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36

// 536870912 = 0x2000 0000
static BOOL _CHttpFile_SendRequest(CHttpFile *pHttpFile, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	BOOL ret = FALSE;
	try
	{
		if (pHttpFile->SendRequest()) ret = TRUE;
	}
	catch(CInternetException *e)
	{
		switch(e->m_dwError)
		{
		case ERROR_INTERNET_TIMEOUT:		Dz1Error_set(errp, ETIMEDOUT); break;
		case ERROR_INTERNET_CANNOT_CONNECT: Dz1Error_set(errp, ENOSYS); break;
		default:
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "CHttpFile::SendRequest() return error %u\n", e->m_dwError);
			Dz1Error_set(errp, EFAULT);
			break;
		}
	}
	return ret;
}

static CHttpConnection *__GetHttpConnection(CInternetSession *session, CString &server_name, INTERNET_PORT server_port, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CHttpConnection *ret = NULL;
	try
	{
		ret = session->GetHttpConnection(server_name, server_port);
	}
	catch (CInternetException *e)
	{
		ERR_SET_OUT(errp, e->m_dwError);
		ret = NULL;
	}
	catch (CMemoryException* e)
	{
		e = e;
		ERR_SET_OUT(errp, ENOMEM);
		ret = NULL;
	}
	catch (CFileException* e)
	{
		e = e;
		ERR_SET_OUT(errp, ENOENT);
		ret = NULL;
	}
	catch (CException* e)
	{
		e = e;
		ERR_SET_OUT(errp, EFAULT);
		ret = NULL;
	}
	return ret;
}

Dz1ElasticBuf *Dz1MfcHtmlDownloadBuf3(Dz1Str url, Dz1Str _referer, Dz1MfcProgressInfo *prog, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *elb = NULL;

	if ((elb = Dz1ElasticBuf_new(4096, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		CInternetSession session;

		DWORD server_type = 0;
		CString server_name;
		CString object_name;
		INTERNET_PORT server_port;
		DWORD dwHttpRequestFlags = INTERNET_FLAG_SECURE;

		CHttpConnection *pServer = NULL;
		Dz1Str referer = Dz1Str_isVoid(_referer) ? NULL : _referer;
		CHttpFile *pHttpFile = NULL;


		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);

		Dz1Thread_printf(Dz1T("Dz1MfcHtmlDownloadBuf3() : %s\n"), url);
		Dz1Thread_printf(Dz1T("referer = %s\n"), referer ? referer : Dz1T("(null)"));

		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);

		if (AfxParseURL(url, server_type, server_name, object_name, server_port) == FALSE) ERR_SET_OUT(errp, EFAULT);
		else if ((pServer = __GetHttpConnection(&session, server_name, server_port, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if ((pHttpFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, object_name, referer, 1, NULL, NULL, dwHttpRequestFlags)) == NULL) ERR_SET_OUT(errp, EPERM);
			else
			{													//  Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36
				if ((pHttpFile->AddRequestHeaders(Dz1T("User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36\r\n"))) == FALSE) ERR_SET_OUT(errp, EPERM);
				else if (_CHttpFile_SendRequest(pHttpFile, errp) == FALSE) ERR_OUT(errp);
				else
				{
					DWORD contentLength = 0;
					DWORD contentLengthSize = sizeof(contentLength);

					if (pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, (LPVOID)&contentLength, &contentLengthSize, NULL) == 0) Dz1MfcProgressInfo_setTotal(prog, -1);
					else
					{
						Dz1Thread_printf(Dz1T("### Internet File Size = %u\n"), contentLength);
						Dz1MfcProgressInfo_setTotal(prog, contentLength);
					}

					Dz1MfcProgressInfo_setPos(prog, 0);
					Dz1MfcProgressInfo_setText(prog, Dz1Text("Downloading..."));

					UINT sz = 0;
					int chunk = 0;
					u8_t temp[HTML_BUF_DECLARE_SIZE] = { 0, };

					while((sz = pHttpFile->Read(temp, HTML_BUF_DECLARE_SIZE)) > 0)
					{
						Dz1Thread_printf(Dz1T(".")); chunk++;
						if (chunk % 64 == 0)
						{
							Dz1Thread_printf(Dz1T("\n"));
							chunk = 0;
						}

						if ((*errp = Dz1ElasticBuf_push(elb, temp, sz)).code) ERR_OUT(errp);
						Dz1MfcProgressInfo_addPos(prog, sz);
					}
					if (chunk != 0) Dz1Thread_printf(Dz1T("\n"));
				}
				delete pHttpFile;
			}
			delete pServer;
		}
		pthread_cleanup_pop(errp->code); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return elb;
}

Dz1ElasticBuf *Dz1MfcHtmlDownloadBuf2(Dz1Str url, Dz1MfcProgressInfo *prog, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1ElasticBuf *elb = NULL;
	if ((elb = Dz1ElasticBuf_new(4096, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		CHttpFile *file = NULL;
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);

		Dz1MfcProgressInfo_setText(prog, Dz1Text("Open Session"));

		//////////////////////////////////////////////////////////////////////
		// Open
		try
		{
			file = (CHttpFile *)session.OpenURL(url, 1, INTERNET_FLAG_TRANSFER_BINARY);
		}
		catch (CMemoryException* e)
		{
			Dz1Thread_printf(Dz1T("!!! Memory Exception = %p\n"), e);
			ERR_SET_OUT(errp, ENOMEM);
		}
		catch (CFileException* e)
		{
			Dz1Thread_printf(Dz1T("!!! File Exception = %p\n"), e);
			ERR_SET_OUT(errp, ENOENT);
		}
		catch (CException* e)
		{
			Dz1Thread_printf(Dz1T("!!! General Exception = %p\n"), e);
			ERR_SET_OUT(errp, EFAULT);
		}
		// Open
		//////////////////////////////////////////////////////////////////////
		
		if (file == NULL) ERR_SET_OUT(errp, EPIPE);
		else
		{
			pthread_cleanup_push(CInternetFile_cancel, (void *)file);

			DWORD contentLength = 0;
			DWORD contentLengthSize = sizeof(contentLength);

			if (0) { }
			else if (file->QueryInfo(HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, (LPVOID)&contentLength, &contentLengthSize, NULL) == 0)
				Dz1MfcProgressInfo_setTotal(prog, -1);
			else
			{
				Dz1Thread_printf(Dz1T("### Internet File Size = %u\n"), contentLength);
				Dz1MfcProgressInfo_setTotal(prog, contentLength);
			}
			Dz1MfcProgressInfo_setPos(prog, 0);
			Dz1MfcProgressInfo_setText(prog, Dz1Text("Downloading..."));
			u8_t temp[HTML_BUF_DECLARE_SIZE] = { 0, };
			UINT sz = 0;
			int chunk = 0;
			while((sz = file->Read(temp, HTML_BUF_DECLARE_SIZE)) > 0)
			{
				Dz1Thread_printf(Dz1T(".")); chunk++;
				if (chunk % 64 == 0)
				{
					Dz1Thread_printf(Dz1T("\n"));
					chunk = 0;
				}

				if ((*errp = Dz1ElasticBuf_push(elb, temp, sz)).code) ERR_OUT(errp);
				Dz1MfcProgressInfo_addPos(prog, sz);
			}
			if (chunk != 0) Dz1Thread_printf(Dz1T("\n"));

			pthread_cleanup_pop(1); // (CInternetFile_cancel, (void *)file);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return elb;
}

static void HINTERNET_cancel(void *ptr)
{
	HINTERNET h = (HINTERNET)ptr;
	InternetCloseHandle(h);
}

Dz1ElasticBuf *Dz1MfcHtmlDownloadBuf(Dz1Str url, Dz1Str _hdr_opt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *ret = Dz1ElasticBuf_new(4096, FALSE, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&ret);
		HINTERNET    hInet, hUrl;
		DWORD        dwReadSize = 0;

		// WinINet함수 초기화
		// Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36
		// Mozilla/5.0 (Windows NT 10.0; WOW64)      AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36
		if ((hInet = InternetOpen(Dz1Text("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36"),// user agent in the HTTP protocol
								  INTERNET_OPEN_TYPE_DIRECT,				// AccessType
								  NULL,										// ProxyName
								  NULL,										// ProxyBypass
								  0)) == NULL) ERR_SET_OUT(errp, EFAULT);	// Options
		else 
		{
			TCHAR *hdr_opt = Dz1Str_isVoid(_hdr_opt) ? NULL : _hdr_opt;
//			TCHAR hdr_buf[1024] = { 0, }, *hdr_opt = NULL;
			pthread_cleanup_push(HINTERNET_cancel, (void *)hInet);

// 			if (Dz1Str_isVoid(referer) == FALSE)
// 			{
// 				if (Dz1STRSTR(referer, Dz1T("arzon.jp")) != NULL)
// 					Dz1SNPRINTF(hdr_buf, 1023, Dz1T("Host: img.arzon.jp\r\nReferer: %s\r\n"), referer);
// 				else Dz1SNPRINTF(hdr_buf, 1023, Dz1T("Referer: %s\r\n"), referer);
// 				hdr_opt = hdr_buf;
// 			}

			// 입력된 HTTP주소를 열기
			if ((hUrl = InternetOpenUrl(hInet,				// 인터넷 세션의 핸들
										url,				// URL
										hdr_opt,			// HTTP server 에 보내는 해더
										-1,					// 해더 사이즈 (-1 == 자동계산)
										0,					// Flag
										0)) == NULL)		// Context
			{
				int code = GetLastError();
				if (code == 0) code = EFAULT;
				ERR_SET_OUT(errp, code);
// 				TCHAR text_buf[1024];
// 				DWORD dwErr = 0, text_len = sizeof(text_buf);
// 				InternetGetLastResponseInfo(&dwErr, text_buf, &text_len);
			}
			else
			{
				DWORD dwSize;
				u8_t szBuff[4096];

				pthread_cleanup_push(HINTERNET_cancel, (void *)hUrl);

				while(1)
				{
					if (InternetReadFile(hUrl, szBuff, 4096, &dwSize) == FALSE) { ERR_SET_OUT(errp, EFAULT); break; }
					else if (dwSize > 0)  Dz1ElasticBuf_push(ret, szBuff, dwSize);
					else break;
				}
				pthread_cleanup_pop(1); // (HINTERNET_cancel, (void *)hUrl);
			}
			pthread_cleanup_pop(1); // (HINTERNET_cancel, (void *)hInet);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ElasticBuf_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1MfcHtmlDownload(Dz1Str url, Dz1Str fn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	HINTERNET    hInet, hUrl;
	DWORD        dwReadSize = 0;

	// WinINet함수 초기화
	if ((hInet = InternetOpen(Dz1Text("Internet Explorer"),	// user agent in the HTTP protocol
							  INTERNET_OPEN_TYPE_DIRECT,	// AccessType
							  NULL,							// ProxyName
							  NULL,							// ProxyBypass
							  0)) != NULL)					// Options
	{
		pthread_cleanup_push(HINTERNET_cancel, (void *)hInet);
		// 입력된 HTTP주소를 열기
		if ((hUrl = InternetOpenUrl(hInet,					// 인터넷 세션의 핸들
									url,					// URL
									NULL,					// HTTP server에 보내는 해더
									0,						// 해더 사이즈
									0,						// Flag
									0)) != NULL)			// Context
		{
			pthread_cleanup_push(HINTERNET_cancel, (void *)hUrl);
			FILE    *fp;

			// 다운로드할 파일 만들기
			if ((fp = Dz1FileStream_open(fn, _T("wb"), errp)) != NULL)
			{
				pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

				u8_t    szBuff[4096];
				DWORD    dwSize;

				while(1) {
					if (InternetReadFile(hUrl, szBuff, 4096, &dwSize) == FALSE) { ERR_SET_OUT(errp, EFAULT); break; }
					else if (dwSize > 0) fwrite(szBuff, 1, dwSize, fp);
					else break;
				}

				pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
			}
			pthread_cleanup_pop(1); // (HINTERNET_cancel, (void *)hUrl);
		}
		pthread_cleanup_pop(1); // (HINTERNET_cancel, (void *)hInet);
	}
	return err;
}

Dz1Error Dz1MfcHtmlDownload2(Dz1Str url, Dz1Str path, Dz1Str name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR fn[4096];
	if ((*errp = Dz1FileName_concatPathName(Dz1ArrParam(TCHAR, fn), path, name)).code) ERR_OUT(errp);
	else if ((*errp = Dz1MfcHtmlDownload(url, fn)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1MfcHtmlDownload3(Dz1Str url, Dz1Str path, Dz1Str name, Dz1Str ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR name_ext[4096];
	if ((*errp = Dz1FileName_concatNameExt(Dz1ArrParam(TCHAR, name_ext), name, ext)).code) ERR_OUT(errp);
	else if ((*errp = Dz1MfcHtmlDownload2(url, path, name_ext)).code) ERR_OUT(errp);
	return err;
}


static bool_t _set_string_value(Dz1MfcHtmlToken *dst, Dz1MfcHtmlParseEnv *env, Dz1Error *errp)
{
	TCHAR *ep = env->lex_ptr + 1, *sp = ep;
	while(*ep && *ep != Dz1Text('\"')) ep++;
	if (*ep != Dz1Text('\"')) ERR_SET_OUT(errp, EPIPE);
	else if ((dst->value = Dz1Str_ndup(sp, (size_t)(ep - sp), errp)) == NULL) ERR_OUT(errp);
	else
	{
		ep++; // pass '\"'
		dst->type = Dz1MfcHtmlTokenType_string;
		env->lex_ptr = ep;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _is_tag_letter(TCHAR c)
{
	bool_t ret = TRUE;
	switch(c)
	{
	case Dz1T('<'): 
	case Dz1T('>'): 
	case Dz1T('='): 
	case Dz1T('\"'): ret = TRUE; break;
	default: ret = FALSE; break;
	}
	return ret;
}

static bool_t _set_symvol_value(Dz1MfcHtmlToken *dst, Dz1MfcHtmlParseEnv *env, Dz1Error *errp)
{
	TCHAR *ep = env->lex_ptr, *sp = ep;
	while(*ep && Dz1ISSPACE(*ep) == FALSE && _is_tag_letter(*ep) == FALSE) ep++;
	if ((dst->value = Dz1Str_ndup(sp, (size_t)(ep - sp), errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->type = Dz1MfcHtmlTokenType_symbol;
		env->lex_ptr = ep;
	}
	return ERR_IS_SUCCESS(errp);
}

static Dz1MfcHtmlToken *_get_html_token(Dz1MfcHtmlParseEnv *env, Dz1Error *errp)
{
	Dz1MfcHtmlToken *ret = Dz1MfcHtmlToken_new(Dz1MfcHtmlTokenType_undef, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		bool_t done = FALSE;
// 		TCHAR buf[4096];
		pthread_cleanup_push(Dz1MfcHtmlToken_delAndSetNull, (void *)&ret);
		while(done == FALSE && *env->lex_ptr && errp->code == 0)
		{
			if (Dz1ISSPACE(*env->lex_ptr))
			{
				ret->type = Dz1MfcHtmlTokenType_space;
				while(*env->lex_ptr && Dz1ISSPACE(*env->lex_ptr)) env->lex_ptr++;
				break;
			}
			else switch(*env->lex_ptr)
			{
			case Dz1T('\r'):	env->lex_ptr++;																break;
			case Dz1T('\n'):	ret->type = Dz1MfcHtmlTokenType_new_line;	env->lex_ptr++; done = TRUE;	break;
			case Dz1T('='):		ret->type = Dz1MfcHtmlTokenType_equal;		env->lex_ptr++; done = TRUE;	break;
			case Dz1T('<'):		ret->type = Dz1MfcHtmlTokenType_start;		env->lex_ptr++; done = TRUE;	break;
			case Dz1T('/'):
				if (*(env->lex_ptr + 1) == Dz1T('>'))
				{
					ret->type = Dz1MfcHtmlTokenType_term;
					env->lex_ptr += 2;
					done = TRUE;
				}
				else if (_set_symvol_value(ret, env, errp) == FALSE) ERR_OUT(errp);
				else done = TRUE;
				break;
			case Dz1T('>'):
				ret->type = Dz1MfcHtmlTokenType_stop;
				env->lex_ptr++; done = TRUE;
				break;
			case Dz1T('\"'):	if (_set_string_value(ret, env, errp) == FALSE) ERR_OUT(errp); else done = TRUE; break;
			default:			if (_set_symvol_value(ret, env, errp) == FALSE) ERR_OUT(errp); else done = TRUE; break;
			}
			if (0) { }
//			else if (*env->lex_ptr == Dz1Text('\r')) env->lex_ptr++;
// 			else if (*env->lex_ptr == Dz1Text('\n'))
// 			{
// 				ret->type = Dz1MfcHtmlTokenType_new_line;
// 				env->lex_ptr++;
// 				break;
// 			}
// 			else if (*env->lex_ptr == Dz1Text('='))
// 			{
// 				ret->type = Dz1MfcHtmlTokenType_equal;
// 				env->lex_ptr++;
// 				break;
// 			}
// 			else if (*env->lex_ptr == Dz1Text('<'))
// 			{
// 				ret->type = Dz1MfcHtmlTokenType_start;
// 				env->lex_ptr++;
// 				break;
// 			}
// 			else if (*env->lex_ptr == Dz1Text('>'))
// 			{
// 				ret->type = Dz1MfcHtmlTokenType_stop;
// 				env->lex_ptr++;
// 				break;
// 			}
// 			else if (*env->lex_ptr == Dz1Text('\"'))
// 			{	// string
// 				TCHAR *dp = buf;
// 				size_t buf_sz = 4095;
// 				env->lex_ptr++;
// 				while(buf_sz && *env->lex_ptr && *env->lex_ptr != Dz1Text('\"'))
// 				{
// 					*dp++ = *env->lex_ptr++;
// 					buf_sz--;
// 				}
// 				*dp++ = 0;
// 				if (*env->lex_ptr != Dz1Text('\"')) ERR_SET_OUT(errp, ENOMEM);
// 				else
// 				{
// 					env->lex_ptr++;
// 					if ((ret->value = Dz1Str_dup(buf, errp)) == NULL) ERR_OUT(errp);
// 					else
// 					{
// 						ret->type = Dz1MfcHtmlTokenType_string;
// 						break;
// 					}
// 				}
// 			}
// 			else
// 			{
// 				TCHAR *dp = buf;
// 				size_t buf_sz = 4095;
// 				while(*env->lex_ptr &&
// 					Dz1ISSPACE(*env->lex_ptr) == FALSE &&
// 					*env->lex_ptr != Dz1Text('<') &&
// 					*env->lex_ptr != Dz1Text('>') &&
// 					*env->lex_ptr != Dz1Text('=') &&
// 					*env->lex_ptr != Dz1Text('\"'))
// 				{
// 					*dp++ = *env->lex_ptr++;
// 					buf_sz--;
// 				}
// 				*dp++ = 0;
// 				if ((ret->value = Dz1Str_dup(buf, errp)) == NULL) ERR_OUT(errp);
// 				else
// 				{
// 					ret->type = Dz1MfcHtmlTokenType_symbol;
// 					break;
// 				}
// 			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1MfcHtmlToken_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Str _get_html_symbol(Dz1MfcHtmlParseEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Str ret = NULL;
	Dz1MfcHtmlToken *tok = _get_html_token(env, errp);
	if (tok == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
		if (tok->type == Dz1MfcHtmlTokenType_undef) ERR_SET_OUT(errp, EFAULT);
		else if (tok->type != Dz1MfcHtmlTokenType_symbol) ERR_SET_OUT(errp, EINVAL);
		else if (tok->value == NULL || tok->value[0] == 0) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret = tok->value;
			tok->value = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
	}
	return ret;
}

static Dz1Error _skip_token_space_newline(Dz1MfcHtmlParseEnv *env)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR *backup = NULL;
	Dz1MfcHtmlToken *tok = NULL;
	bool_t done = FALSE;	
	while(done == FALSE && errp->code == 0)
	{
		backup = env->lex_ptr;
		if ((tok = _get_html_token(env, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
			if (tok->type != Dz1MfcHtmlTokenType_space && tok->type != Dz1MfcHtmlTokenType_new_line)
			{
				env->lex_ptr = backup;
				done = TRUE;
			}
			pthread_cleanup_pop(1); // (Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
		}
	}
	return err;
}

static bool_t _match_html_token(Dz1MfcHtmlParseEnv *env, Dz1MfcHtmlTokenType type, Dz1Str value)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t ret = FALSE;
	Dz1MfcHtmlToken *tok = _get_html_token(env, errp);
	if (tok == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
		if (tok->type == type)
		{
			if (value != NULL && value[0] != 0)
			{
				if (tok->value == NULL || tok->value[0] == 0) { }
				else if (Dz1STRCMP(tok->value, value) == 0) ret = TRUE;
			}
			else ret = TRUE;
		}
		pthread_cleanup_pop(1); // (Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
	}
	return ret;
}

static Dz1Str _get_html_get_symbol_or_string(Dz1MfcHtmlParseEnv *env)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Str ret = NULL;
	Dz1MfcHtmlToken *tok = NULL;
	if ((*errp = _skip_token_space_newline(env)).code) ERR_OUT(errp);
	else if ((tok = _get_html_token(env, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
		if (tok->type == Dz1MfcHtmlTokenType_symbol || tok->type == Dz1MfcHtmlTokenType_string)
		{
			ret = tok->value;
			tok->value = NULL;
		}
		pthread_cleanup_pop(1); // (Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
	}
	return ret;
}

static Dz1MfcHtmlTagAttr *_get_html_attr(Dz1MfcHtmlParseEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcHtmlTagAttr *ret = NULL;
	TCHAR *backup = env->lex_ptr;
	Dz1MfcHtmlToken *head_token = NULL;

	if ((*errp = _skip_token_space_newline(env)).code) ERR_OUT(errp);
	else if ((head_token = _get_html_token(env, errp)) == NULL) ERR_OUT(errp);										// {attr}
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlToken_delAndSetNull, (void *)&head_token);
		if (head_token->type == Dz1MfcHtmlTokenType_stop || head_token->type == Dz1MfcHtmlTokenType_term)
		{
			env->lex_ptr = backup;
			Dz1Error_set(errp, 0);
		}
		else if (head_token->type != Dz1MfcHtmlTokenType_symbol) ERR_SET_OUT(errp, EINVAL);
		else if ((ret = Dz1MfcHtmlTagAttr_new(head_token->value, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MfcHtmlTagAttr_delAndSetNull, (void *)&ret);

			if ((*errp = _skip_token_space_newline(env)).code) ERR_OUT(errp);
			else if (_match_html_token(env, Dz1MfcHtmlTokenType_equal, NULL) == FALSE) ERR_SET_OUT(errp, EINVAL);	// '='
			else if ((ret->value = _get_html_get_symbol_or_string(env)) == NULL) ERR_SET_OUT(errp, EINVAL);			// {value}
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (Dz1MfcHtmlTagAttr_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1MfcHtmlToken_delAndSetNull, (void *)&head_token);
	}
	return ret;
}

static Dz1Error _fill_html_attr(Dz1MfcHtmlParseEnv *env, Dz1MfcHtmlTagAttrList *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MfcHtmlTagAttr *node = NULL;
	while((node = _get_html_attr(env, errp)) != NULL)
	{
		pthread_cleanup_push(Dz1MfcHtmlTagAttr_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MfcHtmlTagAttr_delAndSetNull, (void *)&node);
	}

	if (errp->code) ERR_OUT(errp);

	return err;
}

static Dz1Str _simple_tag[] = {
	Dz1T("img"),
	NULL
};

static Dz1Error _Dz1MfcHtmlTag_parse(Dz1MfcHtmlTag *dst, Dz1Str src, Dz1Str *ret_src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR *sp = Dz1STRCHR(src, Dz1Text('<'));
	if (sp == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MfcHtmlToken *tok = NULL;
		Dz1MfcHtmlParseEnv env = { src, src };
		if (_match_html_token(&env, Dz1MfcHtmlTokenType_start, NULL) == FALSE) ERR_SET_OUT(errp, EINVAL);

		else if ((*errp = _skip_token_space_newline(&env)).code) ERR_OUT(errp);				// remove space & newline after '<'
		else if ((dst->tag_name = _get_html_symbol(&env, errp)) == NULL) ERR_OUT(errp);		// get tag name

		else if ((*errp = _skip_token_space_newline(&env)).code) ERR_OUT(errp);				// remove space & newline after tag name
		else if ((*errp = _fill_html_attr(&env, dst->attr)).code) ERR_OUT(errp);

		else if ((*errp = _skip_token_space_newline(&env)).code) ERR_OUT(errp);				// remove space & newline after attributes

		else if ((tok = _get_html_token(&env, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
			switch(tok->type)
			{
			case Dz1MfcHtmlTokenType_term:
//				dst->term = TRUE;
				// fall through
			case Dz1MfcHtmlTokenType_stop:
				Dz1Str_lcase(dst->tag_name);			// make sure lower case

//				if (Dz1STRSTRS(dst->tag_name, _simple_tag, NULL) != NULL) dst->term = TRUE;

				if (ret_src) (*ret_src) = env.lex_ptr;	// set next read position if possible
				Dz1Error_set(errp, 0);
				break;
			default: ERR_SET_OUT(errp, EINVAL); break;
			}
			pthread_cleanup_pop(1); // (Dz1MfcHtmlToken_delAndSetNull, (void *)&tok);
		}
	}
	return err;
}

Dz1MfcHtmlTag *Dz1MfcHtmlTag_parse(Dz1Str src, Dz1Str *ret_src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcHtmlTag *ret = Dz1MfcHtmlTag_new(NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlTag_delAndSetNull, (void *)&ret);
		if ((*errp = _Dz1MfcHtmlTag_parse(ret, src, ret_src)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MfcHtmlTag_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1MfcHtmlTagAttr *Dz1MfcHtmlTag_getAttr(Dz1MfcHtmlTag *tag, Dz1Str id)
{
	Dz1MfcHtmlTagAttr key = { id }, *ret = tag->attr->find(tag->attr, &key);
	if (ret == NULL)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		Dz1Str uID = Dz1Str_dup(id, errp);
		if (uID == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&uID);
			Dz1Str_ucase(uID);
			key.id = uID;
			ret = tag->attr->find(tag->attr, &key);
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&uID);
		}
	}
	return ret;
}

