#include <dz1_asn1.h>
#include <dz1_crypt_sha1.h>
#include <dz1_base64.h>
#include <Dz1SockUtilUri.h>
#include "dz1_web_socket_struct.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketAuth_generate
Dz1WebSocketAuth *Dz1WebSocketAuth_generate(Dz1UniversalUniqueID *uu_id, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSocketAuth *ret = NULL;
	if ((ret = Dz1WebSocketAuth_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		u8_t uu_id_bin[16];
		char *uuid_b64str = NULL;;
		pthread_cleanup_push(Dz1WebSocketAuth_delAndSetNull, (void *)&ret);
		if (0) { }
		else if (Dz1UniversalUniqueID_toBin(uu_id_bin, sizeof(uu_id_bin), uu_id, errp) < 0) ERR_OUT(errp); // encode uuid to binary
		else if ((ret->key_bin = Dz1Binary_new(uu_id_bin, sizeof(uu_id_bin), errp)) == NULL) ERR_OUT(errp);
		else if ((uuid_b64str = Dz1Base64_encA(uu_id_bin, sizeof(uu_id_bin), errp)) == NULL) ERR_OUT(errp); // encode binary to Base64
		else
		{
			size_t sz = 0;
			u8_t sha1_hash[20];
			Dz1CryptSHA1Ctx ctx;
			char str_key_confirm[256];
			const char *UUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
			
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&uuid_b64str);
			sz = snprintf(str_key_confirm, sizeof(str_key_confirm), "%s%s", uuid_b64str, UUID);	// concat key and UUID

			Dz1CryptSHA1_init(&ctx);
			Dz1CryptSHA1_input(&ctx, str_key_confirm, sz);
			if (Dz1CryptSHA1_finalize(&ctx, sha1_hash, sizeof(sha1_hash), errp) == FALSE) ERR_OUT(errp);		// calculate SHA-1 HASH
			else if ((ret->cnf_bin = Dz1Binary_new(sha1_hash, sizeof(sha1_hash), errp)) == NULL) ERR_OUT(errp);	// keep binary data
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&uuid_b64str);
		}
		pthread_cleanup_pop(errp->code); // (Dz1WebSocketAuth_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1WebSocketAuth_generate
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Make HTTP Request
static str_t _init_host_name(Dz1WebSockInitInfo *p, char *buf, size_t buf_sz, Dz1Error *errp)
{
	str_t ret = NULL;
	size_t sz;
	switch(p->scheme)
	{
	case Dz1WebSocketScheme_ws:
		if (p->port != 80)
			sz = snprintf(buf, buf_sz, "%s:%u", p->host_u8, p->port);
		else sz = snprintf(buf, buf_sz, "%s", p->host_u8);
		break;
	case Dz1WebSocketScheme_wss:
		if (p->port != 443)
			sz = snprintf(buf, buf_sz, "%s:%u", p->host_u8, p->port);
		else sz = snprintf(buf, buf_sz, "%s", p->host_u8);
		break;
	default: ERR_SET_OUT(errp, EFAULT);
		return NULL;
	}

	if (sz >= buf_sz) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		ret = buf;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1Asn1UTF8Str *Dz1WebSockInitInfo_getRequest(Dz1WebSockInitInfo *p, Dz1Binary *key_bin, Dz1Error *errp)
{
	Dz1Asn1UTF8Str *ret = NULL;
	char str_host[256], buf[1024], *key_b64str = NULL;	// all utf8 or utf8 compatible
	if (p == NULL || key_bin == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_init_host_name(p, str_host, sizeof(str_host), errp) == NULL) ERR_OUT(errp);
	else if ((key_b64str = Dz1Base64_encA(key_bin->data, key_bin->size, errp)) == NULL) ERR_OUT(errp);
	else
	{
		size_t sz = 0;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&key_b64str);
		sz = snprintf(buf, sizeof(buf),	"GET %s HTTP/1.1\r\n"			// 1
										"Upgrade: websocket\r\n"
										"Connection: Upgrade\r\n"
										"Host: %s\r\n"					// 2
										"Sec-WebSocket-Key: %s\r\n"		// 3
										"Sec-WebSocket-Version: 13\r\n"
										"\r\n", p->path_u8, str_host, key_b64str);
		if (sz >= sizeof(buf)) ERR_SET_OUT(errp, E2BIG);
		else if ((ret = Dz1Asn1UTF8Str_new((u8_t *)buf, (u32_t)(strlen(buf) & 0xFFFFFFFF), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&key_b64str);
	}
	return ret;
}
// Make HTTP Request
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1WebSockInitInfo generate
Dz1WebSockInitInfo *Dz1WebSockInitInfo_generate(str_t uri_u8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSockInitInfo *ret = NULL;
	Dz1SockUtilUriInfoU *info = NULL;
	if (Dz1Str_isVoid(uri_u8)) ERR_SET_OUT(errp, EINVAL);
	else if ((info = Dz1SockUtilUriInfoU_parse(uri_u8, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1WebSocketScheme sch = Dz1WebSocketScheme_max;
		pthread_cleanup_push(Dz1SockUtilUriInfoU_delAndSetNull, (void *)&info);
		if ((sch = Dz1WebSocketSchemeFromStrA(info->prot)) == Dz1WebSocketScheme_max) ERR_SET_OUT(errp, ENOSYS);
#ifndef DZ1_WEB_SOCKET_SUPPORT_SSL
		else if (sch == Dz1WebSocketScheme_wss) ERR_SET_OUT(errp, ENOSYS);
#endif
		else if ((ret = Dz1WebSockInitInfo_new(sch, info->host, info->port, info->path, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (ret->port == 0)
			{
				switch(ret->scheme)
				{
				default:
				case Dz1WebSocketScheme_ws:		ret->port = 80; break;
				case Dz1WebSocketScheme_wss:	ret->port = 443; break;
				}
			}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1SockUtilUriInfoU_delAndSetNull, (void *)&info);
	}
	return ret;
}
// Dz1WebSockInitInfo generate
///////////////////////////////////////////////////////////////////////////////
