#include <codeconv.h>
#include "Dz1JsonConv.h"

Dz1JsonConv *Dz1JsonConv_new(str_t dst_charset, str_t src_charset, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	codeconv_t ret = NULL;
	if (dst_charset == NULL || dst_charset[0] == 0 || src_charset == NULL || src_charset[0] ==0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char dst_cs[1024];
		strcpy(dst_cs, dst_charset);
		if (strstr(dst_cs, "//TRANSLIT") == NULL) strcat(dst_cs, "//TRANSLIT");

		if ((ret = codeconv_open(dst_cs, src_charset)) == (void *)-1) ERR_SET_OUT_RET(errp, EFAULT, NULL);
		else Dz1Error_set(errp, 0);
	}
	return (Dz1JsonConv *)ret;
}

void Dz1JsonConv_del(Dz1JsonConv *p)
{
	if (p == NULL) return;
	codeconv_close((codeconv_t)p);
}

bool_t Dz1JsonConv_do(Dz1JsonConv *h, u8_t **dstp, size_t *dst_sz, u8_t **srcp, size_t *src_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if		(dstp == NULL || *dstp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (srcp == NULL || *srcp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst_sz == NULL || src_sz == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char *dp = (char *)(*dstp), *sp = (char *)(*srcp);
		size_t s_sz = (*src_sz), d_sz = (*dst_sz);
		while(s_sz > 0)
		{
			if (codeconv((codeconv_t)h, (char **)&sp, &s_sz, (char **)&dp, &d_sz) == -1)
			{
				sp++;			s_sz--;
				*dp++ = '?';	d_sz--;
			}
		}
		(*dstp) = (u8_t *)dp; (*srcp) = (u8_t *)sp;
		(*dst_sz) = d_sz; (*src_sz) = s_sz;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
