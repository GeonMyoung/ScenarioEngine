#include <ctype.h>
#include <dz1_codec.h>
#include <dz1_str.h>
#include "dz1_inet_ftp_control_pi.h"

static ssize_t pass_space(u8_t *src, size_t size)
{
	char *cp = (char *)src;
	while(size)
		if (*cp != 13 && *cp != 10 && isspace((int)*cp & 0xFF)) { cp++; size--; } else break;
	return (ssize_t)(cp - (char *)src);
}

static ssize_t str_enc(u8_t *dst, size_t size, Dz1InetFtpCPIMsgReq *src, Dz1Error *errp)
{
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		ssize_t ret = 0;

		str_t srcp = src->x.__ptr__;

		if (srcp != NULL)
		{
			size_t len = strlen(srcp);

			u8_t *cp = dst;

			if (dst != NULL) *cp++ = ' ';	// encode and move cp
			size--;							// dec size
			ret++;							// inc ret

			if (size < len) { ERR_SET_OUT(errp, E2BIG); return -1; }

			else if (dst != NULL) { memcpy(cp, srcp, len); cp += len; }	// encode and move cp
			size -= len;												// dec size
			ret += (ssize_t)len;										// inc ret
		}

		return ret;
	}
}

static ssize_t get_line_size(u8_t *src, size_t size)
{
	u8_t *cp = src;
	bool_t find = FALSE;
	while(size)
	{
		if (*cp == 13 && size > 0 && *(cp + 1) == 10)
		{
			find = TRUE;
			break;
		}
		cp++; size--;
	}

	if (find) return (ssize_t)((u8_t *)cp - src);
	else return -1;
}

static ssize_t str_dec(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		ssize_t status;
		u8_t *cp = src;

		if ((status = pass_space((u8_t *)cp, size)) < 0) { ERR_SET_OUT(errp, EFAULT); return -1; } else { cp += status; size -= status; }

		if (size != 0)
		{
			ssize_t len = get_line_size(cp, size);
			if (len < 0) { ERR_SET_OUT(errp, EFAULT); return -1; }
			else
			{
				if (len > 0)
				{
					if ((dst->x.__ptr__ = Dz1Calloc(len + 1, 1, errp)) == NULL) { ERR_OUT(errp); return -1; }
					else
					{
						memcpy(dst->x.__ptr__, cp, len);
						cp += len;
						size -= len;
					}
				}
				cp++; size--;	// CR
				cp++; size--;	// LF
			}
		}

		return (ssize_t)((u8_t *)cp - src);
	}
}

#define FTP_DIR_SEP				'/'

static ssize_t path_enc(u8_t *dst, size_t size, Dz1InetFtpCPIMsgReq *src, Dz1Error *errp)
{
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		ssize_t ret = 0;

		str_t srcp = src->x.__ptr__;

		if (srcp != NULL)
		{
			size_t len = strlen(srcp);

			u8_t *cp = dst;

			if (dst != NULL) *cp++ = ' ';	// encode and move cp
			size--;							// dec size
			ret++;							// inc ret

			if (size < len) { ERR_SET_OUT(errp, E2BIG); return -1; }
			else if (dst != NULL)
			{															// encode and move cp
				size_t _len = len;
				while(_len)
				{
					if (*srcp == DIR_SEP) { *cp++ = FTP_DIR_SEP; srcp++; }
					else *cp++ = *srcp++;
					_len--;
				}
			}
			size -= len;												// dec size
			ret += (ssize_t)len;										// inc ret
		}

		return ret;
	}
}

static ssize_t path_dec(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		ssize_t status;
		u8_t *cp = src;

		if ((status = pass_space((u8_t *)cp, size)) < 0) { ERR_SET_OUT(errp, EFAULT); return -1; } else { cp += status; size -= status; }

		if (size != 0)
		{
			ssize_t _len = status = get_line_size(cp, size);
			if (_len < 0) { ERR_SET_OUT(errp, EFAULT); return -1; }
			else
			{
				if (_len > 0)
				{
					if ((dst->x.__ptr__ = Dz1Calloc(_len + 1, 1, errp)) == NULL) ERR_OUT(errp);
					else
					{
						u8_t *dp = dst->x.__ptr__;
						while(_len)
						{
							if (*cp == FTP_DIR_SEP) { *dp++ = DIR_SEP; cp++; }
							else *dp++ = *cp++;
							_len--;
						}
						size -= status;
					}
				}
				cp++; size--; // CR
				cp++; size--; // LF
			}
		}

		return (ssize_t)((u8_t *)cp - src);
	}
}

static ssize_t sock_enc(u8_t *dst, size_t size, Dz1InetFtpCPIMsgReq *src, Dz1Error *errp)
{
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		Dz1SockAddr *addr = (Dz1SockAddr *)src->x.__ptr__;
		u32_t ip; u16_t port;
		size_t ipSize = sizeof(u32_t);
		if ((*errp = Dz1SockAddr_getAddr(addr, (u8_t *)&ip, &ipSize)).code) { ERR_OUT(errp); return -1; }
		else if ((*errp = Dz1SockAddr_getPort(addr, &port)).code) { ERR_OUT(errp); return -1; }
		else
		{
			ssize_t ret = 0;
			char buf[18 + 5 + 1]; // nnn,nnn,nnn,nnn,ppp,ppp
			ret = (ssize_t)sprintf(buf, " %d,%d,%d,%d,%d,%d",
										(ip & 0xFF000000) >> 24,
										(ip & 0xFF0000) >> 16,
										(ip & 0xFF00) >> 8,
										(ip & 0xFF), (port & 0xFF00) >> 8, port & 0xFF);

			if (size < (size_t)ret) { ERR_SET_OUT(errp, E2BIG); return -1; }
			else if (dst != NULL) memcpy(dst, buf, ret);

			return ret;
		}
	}
}

static ssize_t digit_dec(u32_t *dst, int digitCnt, u8_t *src, size_t size, Dz1Error *errp)
{
	ssize_t status;
	char *cp = (char *)src;

	// trim white space
	if ((status = pass_space((u8_t *)cp, size)) < 0) { ERR_SET_OUT(errp, EFAULT); return -1; } else { cp += status; size -= status; }

	if (size && isdigit(((int)*cp) & 0xFF))
	{
		*dst = 0;
		if (digitCnt < 0) digitCnt = 0x7FFFFFFF;
		while(size && isdigit(((int)*cp) & 0xFF))
		{
			if ((--digitCnt) >= 0)
			{
				u32_t v = (u32_t)(*cp++ - '0');
				size--;
				(*dst) = (*dst) * 10 + v;
			}
			else { ERR_SET_OUT(errp, EINVAL); return -1; }
		}

		return (ssize_t)((u8_t *)cp - src);
	}
	else { ERR_SET_OUT(errp, EINVAL); return -1; }
}

static ssize_t ip_dec(Dz1SockAddr *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	u32_t v;
	ssize_t status;
	char *cp = (char *)src;
	int ipDigitRemain = 4;
	u8_t _dst[16] = { 0, }, *dp = _dst;
	while(size)
	{
		if ((status = digit_dec(&v, 3, (u8_t *)cp, size, errp)) < 0) { ERR_OUT(errp); return -1; }
		else { cp += status; size -= status; }

		if ((status = pass_space((u8_t *)cp, size)) < 0) { ERR_SET_OUT(errp, EFAULT); return -1; }
		else { cp += status; size -= status; }

		if (*cp == ',')
		{
			if (--ipDigitRemain) // 3, 2, 1
			{
				cp++;
				status = sprintf((char *)dp, "%d.", v);
				dp += status;
			}
			else
			{	// 0
				sprintf((char *)dp, "%d", v);
				break;
			}
		}
		else { ERR_SET_OUT(errp, EINVAL); return -1; }
	}

	if (ipDigitRemain != 0) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else if ((*errp = Dz1SockAddr_setAddrStr(dst, (char *)_dst)).code) { ERR_OUT(errp); return -1; }
	else return  (ssize_t)((u8_t *)cp - src);
}

static ssize_t port_dec(Dz1SockAddr *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	u32_t v;
	u16_t port = 0;
	ssize_t status;
	char *cp = (char *)src;

	if ((status = digit_dec(&v, 3, (u8_t *)cp, size, errp)) < 0) { ERR_OUT(errp); return -1; }
	else { cp += status; size -= status; }

	port = ((u16_t)(v & 0xFF)) << 8;

	if ((status = pass_space((u8_t *)cp, size)) < 0) { ERR_SET_OUT(errp, EFAULT); return -1; } else { cp += status; size -= status; }

	if (*cp != ',') { ERR_SET_OUT(errp, EINVAL); return -1; } else { cp++; size--; }

	if ((status = digit_dec(&v, 3, (u8_t *)cp, size, errp)) < 0) { ERR_OUT(errp); return -1; }
	else { cp += status; size -= status; }

	port += (u16_t)v;

	if ((*errp = Dz1SockAddr_setPort(dst, port)).code) { ERR_OUT(errp); return -1; }
	else return (ssize_t)((u8_t *)cp - src);
}

ssize_t Dz1InetFtpSockAddr_dec(Dz1SockAddr *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else
	{
		u8_t *cp = src;
		ssize_t status;

		memset(dst, 0, sizeof(Dz1SockAddr));

		if ((status = ip_dec(dst, cp, size, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }

		if ((status = pass_space((u8_t *)cp, size)) < 0) { ERR_SET_OUT(errp, EFAULT); return -1; } else { cp += status; size -= status; }

		if (*cp != ',') { ERR_SET_OUT(errp, EINVAL); return -1; } else { cp++; size--; }

		if ((status = port_dec(dst, cp, size, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }

		return (ssize_t)((u8_t *)cp - src);
	}
}

static ssize_t sock_dec(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else
	{
		u8_t *cp = src;
		ssize_t status;

		Dz1SockAddr addr;
		memset(&addr, 0, sizeof(Dz1SockAddr));

		if ((status = Dz1InetFtpSockAddr_dec(&addr, cp, size, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }

		if ((dst->x.port = Dz1SockAddr_clone(&addr, errp)) == NULL) { ERR_OUT(errp); return -1; }

		return (ssize_t)((u8_t *)cp - src);
	}
}

static struct Dz1InetFtpDTPTextFormMap
{
	Dz1InetFtpDTPTextForm	form;
	char					letter;
} Dz1InetFtpDTPTextFormMap[] =
{
	{ Dz1InetFtpDTPTextForm_nonPrint,	'N' },
	{ Dz1InetFtpDTPTextForm_telnet	,	'T' },
	{ Dz1InetFtpDTPTextForm_asa,		'C' },
	{ Dz1InetFtpDTPTextForm_max }
};

static char Dz1InetFtpDTPTextFormLetter(Dz1InetFtpDTPTextForm form)
{
	struct Dz1InetFtpDTPTextFormMap *i;
	for (i = Dz1InetFtpDTPTextFormMap; i->form != Dz1InetFtpDTPTextForm_max; i++)
		if (i->form == form) return i->letter;
	return '\0';
}

static ssize_t dtpTypeTEXT_enc(u8_t *dst, size_t size, char type, Dz1InetFtpDTPTextForm *form, Dz1Error *errp)
{
	ssize_t status;
	char buf[8];
	//u8_t *cp = dst;
	if (form != NULL)
	{
		status = sprintf(buf, " %c %c", type, Dz1InetFtpDTPTextFormLetter(*form));
		if (dst != NULL) memcpy(dst, buf, status);
	}
	else
	{
		status = sprintf(buf, " %c", type);
		if (dst != NULL) memcpy(dst, buf, status);
	}
	return status;
}

static ssize_t dtpType_enc(u8_t *dst, size_t size, Dz1InetFtpCPIMsgReq *src, Dz1Error *errp)
{
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		Dz1InetFtpDTPType *type = src->x.type;
		if (type == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
		else
		{
			ssize_t status = 0;
			char buf[32];
			switch(type->present)
			{
			case Dz1InetFtpDTPTypePresent_ascii:
				return dtpTypeTEXT_enc(dst, size, 'A', type->x.ascii, errp);
			case Dz1InetFtpDTPTypePresent_ebcdic:
				return dtpTypeTEXT_enc(dst, size, 'E', type->x.ascii, errp);
			case Dz1InetFtpDTPTypePresent_image:
				if (dst != NULL) { *dst++ = ' '; *dst++ = 'I'; }
				return 2;
			case Dz1InetFtpDTPTypePresent_local:
				status = sprintf(buf, " L %u", type->x.local);
				if (dst != NULL) memcpy(dst, buf, status);
				return status;
			default:
				ERR_SET_OUT(errp, EINVAL);
				return -1;
			}
		}
	}
}

static ssize_t dtpTypeTEXT_dec(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1InetFtpDTPTypePresent present, Dz1Error *errp)
{
	char *cp = (char *)src;
	Dz1InetFtpDTPTextForm form = Dz1InetFtpDTPTextForm_nonPrint;
	while(size > 2)
	{
		if (isspace(((int)*cp) & 0xFF)) { cp++; size--; }
		else if (*cp == 'N' || *cp == 'n')
		{
			cp++; size--;
			form = Dz1InetFtpDTPTextForm_nonPrint;
			if ((dst->x.type = Dz1InetFtpDTPType_new(present, &form, errp)) == NULL) { ERR_OUT(errp); return -1; }
			else return (ssize_t)((u8_t *)cp - src);
		}
		else if (*cp == 'T' || *cp == 't')
		{
			cp++; size--;
			form = Dz1InetFtpDTPTextForm_telnet;
			if ((dst->x.type = Dz1InetFtpDTPType_new(present, &form, errp)) == NULL) { ERR_OUT(errp); return -1; }
			else return (ssize_t)((u8_t *)cp - src);
		}
		else if (*cp == 'C' || *cp == 'c')
		{
			cp++; size--;
			form = Dz1InetFtpDTPTextForm_asa;
			if ((dst->x.type = Dz1InetFtpDTPType_new(present, &form, errp)) == NULL) { ERR_OUT(errp); return -1; }
			else return (ssize_t)((u8_t *)cp - src);
		}
		else { ERR_SET_OUT(errp, EINVAL); return -1; }
	}

	if ((dst->x.type = Dz1InetFtpDTPType_new(present, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
	else return (ssize_t)((u8_t *)cp - src);
}

static ssize_t dtpTypeLOCAL_dec(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1InetFtpDTPTypePresent present, Dz1Error *errp)
{
	u32_t v;
	ssize_t status;
	char *cp = (char *)src;
	if ((status = digit_dec(&v, -1, (u8_t *)cp, size, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }

	if ((dst->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_local, &v, errp)) == NULL) { ERR_OUT(errp); return -1; }

	return (ssize_t)((u8_t *)cp - src);
}

static ssize_t dtpType_dec(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		ssize_t status;
		char *cp = (char *)src;
		Dz1InetFtpDTPTypePresent present;
		while(size)
		{
			if (isspace(((int)*cp) & 0xFF)) { cp++; size--; }
			else if (*cp == 'A' || *cp == 'a')
			{
				present = Dz1InetFtpDTPTypePresent_ascii;
				cp++; size--;
				if (size > 2)
				{
					if ((status = dtpTypeTEXT_dec(dst, (u8_t *)cp, size, present, errp)) < 0) { ERR_OUT(errp); return -1; }
					else { cp += status; size -= status; }
				}
				else if ((dst->x.type = Dz1InetFtpDTPType_new(present, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
				break;
			}
			else if (*cp == 'E' || *cp == 'e')
			{
				present = Dz1InetFtpDTPTypePresent_ebcdic;
				cp++; size--;
				if (size > 2)
				{
					if ((status = dtpTypeTEXT_dec(dst, (u8_t *)cp, size, present, errp)) < 0) { ERR_OUT(errp); return -1; }
					else { cp += status; size -= status; }
				}
				else if ((dst->x.type = Dz1InetFtpDTPType_new(present, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
				break;
			}
			else if (*cp == 'I' || *cp == 'i')
			{
				present = Dz1InetFtpDTPTypePresent_image;
				cp++; size--;
				if ((dst->x.type = Dz1InetFtpDTPType_new(present, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
				break;
			}
			else if (*cp == 'L' || *cp == 'l')
			{
				present = Dz1InetFtpDTPTypePresent_local;
				cp++; size--;
				if (size > 2)
				{
					if ((status = dtpTypeLOCAL_dec(dst, (u8_t *)cp, size, present, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }
				}
				else { ERR_SET_OUT(errp, EFAULT); return -1; }
				break;
			}
			else { ERR_SET_OUT(errp, EINVAL); return -1; }
		}
		return (ssize_t)((u8_t *)cp - src);
	}
}

static ssize_t dtpStruct_enc(u8_t *dst, size_t size, Dz1InetFtpCPIMsgReq *src, Dz1Error *errp)
{
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		ssize_t status;
		u8_t *cp = dst;
		char buf[4];
		switch(src->x.stru)
		{
		case Dz1InetFtpDTPStruct_file:
			status = (ssize_t)sprintf(buf, " F");
			if (dst != NULL)
			{
				memcpy(cp, buf, status);
				cp += status;
				size -= status;
			}
			return status;
		case Dz1InetFtpDTPStruct_record:
			status = (ssize_t)sprintf(buf, " R");
			if (dst != NULL)
			{
				memcpy(cp, buf, status);
				cp += status;
				size -= status;
			}
			return status;
		case Dz1InetFtpDTPStruct_page:
			status = (ssize_t)sprintf(buf, " P");
			if (dst != NULL)
			{
				memcpy(cp, buf, status);
				cp += status;
				size -= status;
			}
			return status;
		default:
			ERR_SET_OUT(errp, EINVAL);
			return -1;
		}
	}
}

static ssize_t dtpStruct_dec(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		u8_t *cp = src;
		while(size)
		{
			if (isspace((int)*cp & 0xFF)) { cp++; size--; }
			else if (*cp == 'F' || *cp == 'f') { cp++; size--; dst->x.stru = Dz1InetFtpDTPStruct_file; break; }
			else if (*cp == 'R' || *cp == 'r') { cp++; size--; dst->x.stru = Dz1InetFtpDTPStruct_record; break; }
			else if (*cp == 'P' || *cp == 'p') { cp++; size--; dst->x.stru = Dz1InetFtpDTPStruct_page; break; }
			else { ERR_SET_OUT(errp, EINVAL); return -1; }
		}
		return (ssize_t)((u8_t *)cp - src);
	}
}

static ssize_t dtpMode_enc(u8_t *dst, size_t size, Dz1InetFtpCPIMsgReq *src, Dz1Error *errp)
{
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		ssize_t status;
		u8_t *cp = dst;
		char buf[4];
		switch(src->x.mode)
		{
		case Dz1InetFtpDTPMode_stream:
			status = (ssize_t)sprintf(buf, " S");
			if (dst != NULL)
			{
				memcpy(cp, buf, status);
				cp += status;
				size -= status;
			}
			return status;
		case Dz1InetFtpDTPMode_block:
			status = (ssize_t)sprintf(buf, " B");
			if (dst != NULL)
			{
				memcpy(cp, buf, status);
				cp += status;
				size -= status;
			}
			return status;
		case Dz1InetFtpDTPMode_compressed:
			status = (ssize_t)sprintf(buf, " C");
			if (dst != NULL)
			{
				memcpy(cp, buf, status);
				cp += status;
				size -= status;
			}
			return status;
		default:
			ERR_SET_OUT(errp, EINVAL);
			return -1;
		}
	}
}

static ssize_t dtpMode_dec(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		u8_t *cp = src;
		while(size)
		{
			if (isspace((int)*cp & 0xFF)) { cp++; size--; }
			else if (*cp == 'S' || *cp == 's') { cp++; size--; dst->x.mode = Dz1InetFtpDTPMode_stream; break; }
			else if (*cp == 'B' || *cp == 'b') { cp++; size--; dst->x.mode = Dz1InetFtpDTPMode_block; break; }
			else if (*cp == 'C' || *cp == 'c') { cp++; size--; dst->x.mode = Dz1InetFtpDTPMode_compressed; break; }
			else { ERR_SET_OUT(errp, EINVAL); return -1; }
		}
		return (ssize_t)((u8_t *)cp - src);
	}
}

static ssize_t alloc_enc(u8_t *dst, size_t size, Dz1InetFtpCPIMsgReq *src, Dz1Error *errp)
{
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		u8_t *cp = dst;
		Dz1InetFtpAlloc *p = src->x.allo;
		char buf[32], *dp = buf;
		ssize_t status = sprintf(dp, " %u", p->numOfOctet);
		dp += status;
		if (p->numOfRecord != NULL)
			sprintf(dp, " R %u", *p->numOfRecord);

		status = (ssize_t)strlen(buf);
		if (size < (size_t)status) { ERR_SET_OUT(errp, E2BIG); return -1; }
		else if (dst != NULL) { memcpy(cp, buf, status); cp += status; }
		return status;
	}
}

static ssize_t alloc_dec(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		u32_t byteSize;
		ssize_t status;
		u8_t *cp = src;

		if ((status = digit_dec(&byteSize, -1, (u8_t *)cp, size, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }

		if (size > 2)
		{
			if ((status = pass_space((u8_t *)cp, size)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }

			if (size > 2)
			{
				if (*cp == 'R' || *cp == 'r')
				{
					u32_t recordSize;
					cp++; size--;
					if ((status = digit_dec(&recordSize, -1, (u8_t *)cp, size, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }

					if ((dst->x.allo = Dz1InetFtpAlloc_new(byteSize, &recordSize, errp)) == NULL) { ERR_OUT(errp); return -1; }
					else return (ssize_t)((u8_t *)cp - src);
				}
				else { ERR_SET_OUT(errp, EINVAL); return -1; }
			}
			else if ((dst->x.allo = Dz1InetFtpAlloc_new(byteSize, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
			else return (ssize_t)((u8_t *)cp - src);
		}
		else if ((dst->x.allo = Dz1InetFtpAlloc_new(byteSize, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
		else return (ssize_t)((u8_t *)cp - src);
	}
}

typedef struct Dz1InetFtpReqAPI
{
	Dz1InetFtpCPIMsgReqPresent present;
	str_t cmd;
	ssize_t (*encode)(u8_t *dst, size_t size, Dz1InetFtpCPIMsgReq *src, Dz1Error *errp);
	ssize_t (*decode)(Dz1InetFtpCPIMsgReq *dst, u8_t *src, size_t size, Dz1Error *errp);
} Dz1InetFtpReqAPI;

static Dz1InetFtpReqAPI reqAPI[] =
{
	{ Dz1InetFtpCPIMsgReqPresent_user,	"USER",	str_enc,		str_dec },
	{ Dz1InetFtpCPIMsgReqPresent_pass,	"PASS", str_enc,		str_dec },
	{ Dz1InetFtpCPIMsgReqPresent_acct,	"ACCT", str_enc,		str_dec },
	{ Dz1InetFtpCPIMsgReqPresent_cwd,	"CWD",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_cdup,	"CDUP",	NULL,			NULL },
	{ Dz1InetFtpCPIMsgReqPresent_smnt,	"SMNT",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_quit,	"QUIT",	NULL,			NULL },
	{ Dz1InetFtpCPIMsgReqPresent_rein,	"REIN",	NULL,			NULL },
	{ Dz1InetFtpCPIMsgReqPresent_port,	"PORT",	sock_enc,		sock_dec },
	{ Dz1InetFtpCPIMsgReqPresent_pasv,	"PASV",	NULL,			NULL },
	{ Dz1InetFtpCPIMsgReqPresent_type,	"TYPE",	dtpType_enc,	dtpType_dec },
	{ Dz1InetFtpCPIMsgReqPresent_stru,	"STRU",	dtpStruct_enc,	dtpStruct_dec },
	{ Dz1InetFtpCPIMsgReqPresent_mode,	"MODE",	dtpMode_enc,	dtpMode_dec },
	{ Dz1InetFtpCPIMsgReqPresent_retr,	"RETR",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_stor,	"STOR",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_stou,	"STOU",	NULL,			NULL },
	{ Dz1InetFtpCPIMsgReqPresent_appe,	"APPE",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_allo,	"ALLO",	alloc_enc,		alloc_dec },
	{ Dz1InetFtpCPIMsgReqPresent_rest,	"REST",	str_enc,		str_dec },
	{ Dz1InetFtpCPIMsgReqPresent_rnfr,	"RNFR",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_rnto,	"RNTO",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_abor,	"ABOR",	NULL,			NULL },
	{ Dz1InetFtpCPIMsgReqPresent_dele,	"DELE",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_rmd,	"RMD",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_mkd,	"MKD",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_pwd,	"PWD",	NULL,			NULL },
	{ Dz1InetFtpCPIMsgReqPresent_list,	"LIST",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_nlst,	"NLST",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_site,	"SITE",	str_enc,		str_dec },
	{ Dz1InetFtpCPIMsgReqPresent_syst,	"SYST",	NULL,			NULL },
	{ Dz1InetFtpCPIMsgReqPresent_stat,	"STAT",	path_enc,		path_dec },
	{ Dz1InetFtpCPIMsgReqPresent_help,	"HELP",	str_enc,		str_dec },
	{ Dz1InetFtpCPIMsgReqPresent_size,	"SIZE", str_enc,		str_dec },
	{ Dz1InetFtpCPIMsgReqPresent_feat,	"FEAT", NULL,			NULL},
	{ Dz1InetFtpCPIMsgReqPresent_max }
};

struct Dz1InetFtpReqAPI *Dz1InetFtpReqAPI_findByPresent(Dz1InetFtpCPIMsgReqPresent present)
{
	Dz1InetFtpReqAPI *i = NULL;
	for (i = reqAPI; i->present != Dz1InetFtpCPIMsgReqPresent_max; i++)
		if (i->present == present) return i;
	return NULL;
}

struct Dz1InetFtpReqAPI *Dz1InetFtpReqAPI_findByCmd(str_t cmd)
{
	Dz1InetFtpReqAPI *i = NULL;
	for (i = reqAPI; i->present != Dz1InetFtpCPIMsgReqPresent_max; i++)
		if (strcmp(i->cmd, cmd) == 0) return i;
	return NULL;
}

static ssize_t req_enc(u8_t *dst, size_t size, Dz1InetFtpCPIMsg *src, Dz1Error *errp)
{
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		Dz1InetFtpCPIMsgReq *req = src->x.req;
		Dz1InetFtpReqAPI *api = Dz1InetFtpReqAPI_findByPresent(req->present);
		if (api == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
		else
		{
			u8_t *cp = dst;
			ssize_t ret = 0, status = (ssize_t)strlen(api->cmd);
			if (size < (size_t)status) { ERR_SET_OUT(errp, E2BIG); return -1; }

			if (dst != NULL) { memcpy(cp, api->cmd, status); cp += status; }
			size -= status;
			ret += status;

			if (api->encode)
			{
				if ((status = api->encode(cp, size, req, errp)) < 0) { ERR_OUT(errp); return -1; }
				else
				{
					if (dst != NULL) cp += status;
					size -= status;
					ret += status;

				}
			}

			if (dst != NULL) *cp++ = 13;
			size--;
			ret++;

			if (dst != NULL) *cp++ = 10;
			size--;
			ret++;

			return ret;
		}
	}
}

static ssize_t get_word(char *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	ssize_t status;
	u8_t *cp = src, *dp = (u8_t *)dst;;

	if ((status = pass_space((u8_t *)cp, size)) < 0) { ERR_SET_OUT(errp, EFAULT); return -1; } else { cp += status; size -= status; }

	if (size == 0) { ERR_SET_OUT(errp, EINVAL); return -1; }

	if (isalpha((int)*cp & 0xFF))
	{
		char c;
		while(size && isalnum((int)*cp & 0xFF))
		{
			c = *cp++;
			if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
			*dp++ = c;
			size--;
		}
		*dp++ = '\0';
	}
	else if (isdigit((int)*cp & 0xFF))
	{
		while(size && isdigit((int)*cp & 0xFF)) { *dp++ = *cp++; size--; }
		*dp++ = '\0';
	}
	else
	{
		ERR_SET_OUT(errp, EINVAL);
		return -1;
	}

	return (ssize_t)((u8_t *)cp - src);
}

static ssize_t req_dec(Dz1InetFtpCPIMsg *dst, u8_t *src, size_t size, bool_t *isComplete, Dz1Error *errp)
{
	char cmd[8];
	u8_t *cp = src;
	ssize_t status;
	Dz1InetFtpReqAPI *api = NULL;
	Dz1InetFtpCPIMsgReq *req = NULL;

	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	
	if ((status = get_word(cmd, cp, size, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }

	if ((api = Dz1InetFtpReqAPI_findByCmd(cmd)) == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else if ((req = dst->x.req = Dz1InetFtpCPIMsgReq_new(api->present, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
	else
	{
		ssize_t ret = (ssize_t)((u8_t *)cp - src);

		pthread_cleanup_push(Dz1InetFtpCPIMsgReq_delAndSetNull, (void *)&dst->x.req);

		if (api->decode)
		{
			if ((status = api->decode(req, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				cp += status;
				size -= status;
				ret += status;
			}
		}

		if (errp->code == 0)
		{
			if (size < 2) { ERR_SET_OUT(errp, E2BIG); ret = -1; }
			else { cp += 2; size -= 2; ret += 2; *isComplete = TRUE; }
		}

		pthread_cleanup_pop(errp->code); // (Dz1InetFtpCPIMsgReq_delAndSetNull, (void *)&dst->x.req);

		return ret;
	}
}

static Dz1Error _get_size(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	size_t *len = (size_t *)ptr;
	(*len) += (size_t)strlen(p) + 2; // text <CR> <LF>
	return err;
}

typedef struct ReplyEncArg
{
	u8_t *dst;
	size_t size;
	str_t tail;
} ReplyEncArg;

static Dz1Error _list_enc(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ReplyEncArg *arg = (ReplyEncArg *)ptr;
	if (arg->tail != p)
	{
		ssize_t status = (ssize_t)sprintf((char *)arg->dst, "%s%c%c", p, 13, 10);
		arg->dst += status; arg->size -= status;
	}
	return err;
}

static ssize_t reply_enc(u8_t *dst, size_t size, Dz1InetFtpCPIMsg *src, Dz1Error *errp)
{
	Dz1InetFtpCPIMsgReply *reply = NULL;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else if ((reply = src->x.reply) == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		bool_t multiLine = FALSE;

		size_t len = 3 + 1 + strlen(reply->title) + 2; /* [code] [hyphen|<SP>] [text] <CR> <LF>*/
		if ((multiLine = (reply->list->count(reply->list) != 0)))
		{
			if ((*errp = reply->list->travel(reply->list, _get_size, (void *)&len)).code) { ERR_OUT(errp); return -1; }
			else len += (3 + 1); /* [code] <SP> for last line */
		}

		if (size < len) { ERR_SET_OUT(errp, E2BIG); return -1; }
		else
		{
			if (dst != NULL)
			{
				u8_t *cp = dst;

				ssize_t status = (ssize_t)sprintf((s8_t *)cp, "%03u%c", reply->code, multiLine ? '-' : ' ');
				cp += status; size -= status;

				status = (ssize_t)sprintf((s8_t *)cp, "%s%c%c", reply->title, 13, 10);
				cp += status; size -= status;

				if (multiLine)
				{
					ReplyEncArg arg = { cp, size, reply->list->getTail(reply->list) };
					if ((*errp = reply->list->travel(reply->list, _list_enc, (void *)&arg)).code) { ERR_OUT(errp); return -1; }
					else
					{
						status = (ssize_t)(arg.dst - cp); cp += status; size -= status;
						status = (ssize_t)sprintf((s8_t *)cp, "%03u %s%c%c", reply->code, arg.tail, 13, 10); cp += status; size -= status;
					}
				}
			}
			return (ssize_t)len;
		}
	}
}

static bool_t isNumber(str_t str)
{
	char *cp = str;
	while(*cp) if (!isdigit((int)*cp & 0xFF)) return FALSE; else cp++;
	return TRUE;
}

static __inline__ bool_t chkLine(str_t str)
{
	if (str[4] == ' ') return TRUE;
	return FALSE;
}

static ssize_t _dec_line(str_t *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	u8_t *cp = src;
	ssize_t status = get_line_size(cp, size);
	if (status < 0) { ERR_SET_OUT(errp, EFAULT); return -1; }
	else
	{
		if ((*dst = (str_t)Dz1Calloc(status + 1, 1, errp)) == NULL) { ERR_OUT(errp); return -1; }
		else { memcpy((*dst), cp, status); cp += status; size -= status; }

		cp++; size--; // pass CR
		cp++; size--; // pass LF
	}
	return (ssize_t)((u8_t *)cp - src);
}

static ssize_t reply_dec(Dz1InetFtpCPIMsg *dst, u8_t *src, size_t size, bool_t *isComplete, Dz1Error *errp)
{
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		u8_t *cp = src, flag;
		ssize_t ret= 0, status;
		Dz1InetFtpCPIMsgReply *reply = NULL;
		char buf[4] = { 0, };

		if ((reply = dst->x.reply = Dz1InetFtpCPIMsgReply_new(0, NULL, errp)) == NULL) DZ1_CODEC_ERR_RET(errp);

		if ((status = _getByte(cp, size, (u8_t *)buf, 3, errp)) < 0) DZ1_CODEC_ERR_RET(errp);
		else
		{
			DZ1_CODEC_APPLY(cp, size, status, ret);
			reply->code = atoi(buf);
		}

		if ((status = _getByte(cp, size, &flag, 1, errp)) < 0) DZ1_CODEC_ERR_RET(errp); else DZ1_CODEC_APPLY(cp, size, status, ret);

		if ((status = _dec_line(&reply->title, cp, size, errp)) < 0) DZ1_CODEC_ERR_RET(errp); else DZ1_CODEC_APPLY(cp, size, status, ret);

		if (flag == '-')
		{
			str_t node = NULL;
			while(errp->code == 0 && flag != ' ')
			{
				if (size < 4) DZ1_CODEC_ERRSET_RET(errp, E2BIG); else flag = cp[3];

				if ((status = _dec_line(&node, cp, size, errp)) < 0) DZ1_CODEC_ERR_RET(errp);
				else
				{
					pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&node);

					if ((*errp = reply->list->add(reply->list, node)).code) { ERR_OUT(errp); ret = -1; }
					else
					{
						node = NULL;
						DZ1_CODEC_APPLY(cp, size, status, ret);
					}

					pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&node);
				}
			}
		}

		return ret;
	}
}

typedef struct Dz1InetFtpCPIMsgAPI
{
	Dz1InetFtpCPIMsgPresent present;
	ssize_t (*encode)(u8_t *dst, size_t size, Dz1InetFtpCPIMsg *src, Dz1Error *errp);
	ssize_t (*decode)(Dz1InetFtpCPIMsg *dst, u8_t *src, size_t size, bool_t *isComplete, Dz1Error *errp);
} Dz1InetFtpCPIMsgAPI;
static Dz1InetFtpCPIMsgAPI msgAPI[] =
{
	{ Dz1InetFtpCPIMsgPresent_req, req_enc, req_dec},
	{ Dz1InetFtpCPIMsgPresent_reply, reply_enc, reply_dec },
	{ Dz1InetFtpCPIMsgPresent_max }
};

static Dz1InetFtpCPIMsgAPI *Dz1InetFtpCPIMsgAPI_find(Dz1InetFtpCPIMsgPresent present)
{
	Dz1InetFtpCPIMsgAPI *i;
	for (i = msgAPI; i->present != Dz1InetFtpCPIMsgPresent_max; i++)
		if (i->present == present) return i;
	return NULL;
}

ssize_t Dz1InetFtpCPIMsg_encode(u8_t **_dst, Dz1InetFtpCPIMsg *src, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;

	u8_t *dst = NULL;
	ssize_t status = 0;
	Dz1InetFtpCPIMsgAPI *api = NULL;
	if (src == NULL || _dst == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		// Dz1Thread_printf("Dz1InetFtpCPIMsg_encode() : Source = "); Dz1InetFtpCPIMsg_dump(src, 0);
		if ((api = Dz1InetFtpCPIMsgAPI_find(src->present)) == NULL) { ERR_SET_OUT(errp, EFAULT); return -1; }
		else if ((status = api->encode(NULL, -1, src, errp)) < 0) { ERR_OUT(errp); return -1; }
		else if ((dst = (*_dst) = (u8_t *)Dz1Malloc(status + 2, errp)) == NULL) { ERR_OUT(errp); return -1; }
		else
		{
			ssize_t ret = status;
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)_dst);

			if (api->encode(dst, status, src, errp) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				Dz1Error_set(errp, 0);
			}

			pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)_dst);

			return ret;
		}
	}
}

static Dz1InetFtpCPIMsgPresent getPresent(char *p)
{
	char buf[4] = { 0, };
	memcpy(buf, p, 3);
	if (isNumber(buf)) return Dz1InetFtpCPIMsgPresent_reply;
	else return Dz1InetFtpCPIMsgPresent_req;
}

static ssize_t _Dz1InetFtpCPIMsg_decode(Dz1InetFtpCPIMsg *dst, u8_t *src, size_t size, bool_t *isComplete, Dz1Error *errp)
{
	ssize_t ret = 0;
	Dz1InetFtpCPIMsgAPI *api = NULL;
	if ((api = Dz1InetFtpCPIMsgAPI_find(dst->present)) == NULL) { ERR_SET_OUT(errp, EFAULT); ret = -1; }
	else if ((ret = api->decode(dst, src, size, isComplete, errp)) < 0)
	{
		if (errp->code != E2BIG) ERR_OUT(errp);
		ret = -1;
	}
	else
	{
		Dz1Error_set(errp, 0);
		*isComplete = TRUE;
	}
	return ret;
}

ssize_t Dz1InetFtpCPIMsg_decode(Dz1InetFtpCPIMsg **_dst, u8_t *src, size_t size, bool_t *isComplete, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;

	Dz1InetFtpCPIMsgPresent present;
	if (src == NULL || _dst == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else if (size < 3) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else
	{
		ssize_t ret = 0;
		//Dz1InetFtpCPIMsgAPI *api = NULL;
		Dz1InetFtpCPIMsg *dst = (*_dst);
		if (dst == NULL)
		{
			if ((present = getPresent((char *)src)) == Dz1InetFtpCPIMsgPresent_max) { ERR_SET_OUT(errp, EFAULT); return -1; }
			else if (dst == NULL && (dst = (*_dst) = Dz1InetFtpCPIMsg_new(present, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
			else
			{
				pthread_cleanup_push(Dz1InetFtpCPIMsg_delAndSetNull, (void *)_dst);

				if ((ret = _Dz1InetFtpCPIMsg_decode(dst, src, size, isComplete, errp)) < 0)
				{
					if (errp->code != E2BIG) ERR_OUT(errp);
					ret = -1;
				}

				pthread_cleanup_pop(errp->code); // (Dz1InetFtpCPIMsg_delAndSetNull, (void *)_dst);
			}
		}
		else if ((ret = _Dz1InetFtpCPIMsg_decode(dst, src, size, isComplete, errp)) < 0) { ERR_OUT(errp); ret = -1; }

		return ret;
	}
}
