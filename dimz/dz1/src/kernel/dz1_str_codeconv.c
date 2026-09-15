#include <dz1_str.h>
#include <dz1_malloc.h>
#include <codeconv.h>

#ifdef USE_CODECONV
static void codeconv_openCancel(void *ptr)
{
	codeconv_t h = (codeconv_t)ptr;
	codeconv_close(h);
}
#endif
ssize_t Dz1CodeConv(u8_t *dst, size_t dst_byte_size, const char *dst_charsetname,
					 u8_t *src, size_t src_byte_size, const char *src_charsetname)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_VAR(errp, err);
#ifdef USE_CODECONV
	codeconv_t h = (void *)-1;

	char _dst_charset[64];
	strcpy(_dst_charset, dst_charsetname);

	if (strstr(dst_charsetname, "//TRANSLIT") == NULL)
		strcat(_dst_charset, "//TRANSLIT");

// 	if (strstr(dst_charsetname, "//IGNORE") == NULL)
// 		strcat(_dst_charset, "//IGNORE");

	if ((h = codeconv_open(_dst_charset, src_charsetname)) == (void *)-1) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ssize_t sz = 0;
		u8_t	*_src = src;
		size_t	 _src_byte_size = src_byte_size;

		u8_t	*_dst = dst;
		size_t	_dst_byte_size = dst_byte_size;

		pthread_cleanup_push(codeconv_openCancel, (void *)h);

		while(_src_byte_size > 0)
		{
			if ((sz = (ssize_t)codeconv(h, (char **)&_src, &_src_byte_size, (char **)&_dst, &_dst_byte_size)) == -1)
			{
				_src++;
				_src_byte_size--;
				*_dst++ = '?';
				_dst_byte_size--;
			}
		}
		ret = (ssize_t)(_dst - dst);

		pthread_cleanup_pop(1); // (codeconv_openCancel, (void *)h);
		sz = sz;
	}
#else
	ERR_SET_OUT(errp, ENOSYS);
#endif
	return ret;
}

void *Dz1String_conv(void *src, size_t src_byte_size, const char *src_charsetname, const char *dst_charsetname, size_t *ret_byte_size)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (Dz1Str_isVoid(src_charsetname) == TRUE || Dz1Str_isVoid(dst_charsetname) == TRUE) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		size_t _rsz = 0, *rsz = ret_byte_size ? ret_byte_size : &_rsz;
		if (src == NULL || src_byte_size == 0)
		{
			if ((ret = Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) ERR_OUT(errp);
			else 
			{
				Dz1Error_set(errp, 0);
				*rsz = 0;
			}
		}
		else
		{
			size_t dst_byte_size = (src_byte_size + 1) * 4;
			if ((ret = Dz1Calloc(sizeof(u8_t), dst_byte_size, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz;
				pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
				if ((sz = Dz1CodeConv((u8_t *)ret, dst_byte_size, dst_charsetname,
										   (u8_t *)src, src_byte_size, src_charsetname)) < 0) ERR_OUT(errp);
				else
				{
                	(*rsz) = sz;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
			}
		}
	}
	return ret;
}
