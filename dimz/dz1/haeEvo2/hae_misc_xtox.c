#include "hae_output.h"

#include "hae_misc.h"

u64_t hae_htonll(u64_t value)
{
#if (BYTE_ORDER == LITTLE_ENDIAN)
	u32_t *nv = (u32_t *)&value;
	u32_t temp;
	nv[0] = htonl(nv[0]);
	nv[1] = htonl(nv[1]);
	temp = nv[0];
	nv[0] = nv[1];
	nv[1] = temp;
#endif
	return value;
}

u64_t hae_ntohll(u64_t value)
{
	return hae_htonll(value);
}

static int hextodec(char c)
{
	if (c>='0' && c<='9') return c - '0';
	else if (c>='A' && c<='F') return c - 'A' + 10;
	else if (c>='a' && c<='f') return c - 'a' + 10;
	else return 0;
}

static u64_t hextoull(str_t str)
{
	if (str[0]=='0' && str[1]=='x')
	{
		u64_t result = 0;
		str+=2;
		while(*str) result = result * 16 + hextodec(*str++);
		return result;
	}
	else
		return 0;
}
u64_t hae_atoull_x(str_t str)
{
	u64_t result = 0;
	if (strlen(str)>2 && str[0] == '0' && str[1] == 'x')
		return hextoull(str);
	if (str[0]=='-')
	{
		HaeOut->fprintf(stdout, 0, "atoull() : Unsigned convertion but signed %s\n", str);
		return 0;
	}
	else if (str[0]=='+') str++;
	while(*str)
		result = result * 10 + ((*str++) - '0');
	return result;
}

static s32_t hextoi(str_t str)
{
	if (str[0]=='0' && str[1] == 'x')
	{
		s32_t result = 0;
		str+=2;
		while(*str) result = result * 16 + hextodec(*str++);
		return result;
	}
	else
		return 0;
}
s32_t hae_atoi_x(str_t str)
{
	if (strlen(str)>2 && str[0] == '0' && str[1] == 'x')
		return hextoi(str);
	else return atoi(str);
}
