#include <dz1_thread_stdio.h>
#include "Dz1JsonFifo.h"
#include <Dz1Json.h>

Dz1JsonFifo *Dz1JsonFifo_create(str_t ingress_charset, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonFifo *ret = Dz1JsonFifo_new(ingress_charset, NULL, NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
//		bool_t is_same_charset = strcmp(DZ1_SYSTEM_CHARSET, ingress_charset) == 0 ? TRUE : FALSE;
		pthread_cleanup_push(Dz1JsonFifo_delAndSetNull, (void *)&ret);
		if ((ret->conv = Dz1JsonConv_new(DZ1_SYSTEM_CHARSET, ingress_charset, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->ingress_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->pop_stream = Dz1Stream_openRefElasticBuf(ret->ingress_buf, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1JsonFifo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

// > 0 : src를 사용한 바이트 수, < 0 error
ssize_t Dz1JsonFifo_ingress(Dz1JsonFifo *dst, u8_t *src, size_t sz, Dz1Error *err)
{
	ssize_t ret = -1;
	u8_t *temp = NULL;
	size_t t_sz = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL || sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if (dst->conv == NULL)
	{	// No Conversion
		if ((*errp = Dz1ElasticBuf_push(dst->ingress_buf, src, sz)).code) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret = (ssize_t)sz;
		}
	}
	else if ((temp = (u8_t *)Dz1Malloc((t_sz = sizeof(int) * sz), errp)) == NULL) ERR_OUT(errp);
	else
	{
		u8_t	*sp	  = src;
		size_t	 s_sz = sz;

		u8_t	*dp	  = temp;
		size_t	 d_sz = t_sz;

		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		if (Dz1JsonConv_do(dst->conv, &dp, &d_sz, &sp, &s_sz, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = Dz1ElasticBuf_push(dst->ingress_buf, temp, (size_t)(dp - temp) )).code) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret = (ssize_t)(sp - src);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
//	Dz1Thread_printf("@@@ sz = %d, ret = %d\n", sz, ret);
	return ret;
}

// 0 = eof, 1~2 = letter, -1 = error
int Dz1JsonFifoA_getC(Dz1JsonFifo *src, SingleChar *ret_c, Dz1Error *err)
{	// pop_stream에는 local system의 multibyte charset 문자들이 들어있다. : Local System Charset = ASCII.EUC-KR
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = -1;

	if (src->ungetc_head != NULL)
	{
		Dz1JsonFifoUngetE *node = src->ungetc_head;
		src->ungetc_head = node->next;
		node->next = NULL;
		pthread_cleanup_push(Dz1JsonFifoUngetE_delAndSetNull, (void *)&node);
		ret = 1;
		*ret_c = node->c32;
		pthread_cleanup_pop(1); // (Dz1JsonFifoUngetE_delAndSetNull, (void *)&ret);
	}
	else
	{
		u8_t c0 = 0;
		ssize_t cnt;

		Dz1Stream *st = src->pop_stream;
		if ((cnt = Dz1Stream_peek1(st, &c0, errp)) < 0)
		{
			if (errp->code == EPIPE) { Dz1Error_set(errp, 0); ret = 0; }
			else ERR_OUT(errp);
		}
		else if (cnt == 0) { Dz1Error_set(errp, 0); ret = 0; }
		else if (c0 >= 0xA1 && c0 < 0xFF)
		{
			u16_t c16;
			if (Dz1Stream_read2(st, &c16, Dz1IOStreamEndian_big, errp) < 0)
			{
				if (errp->code == EPIPE) { Dz1Error_set(errp, 0); ret = 0; }
				else ERR_OUT(errp);
			}
			else if (Dz1Stream_drain(st, 1, NULL, errp) < 0) ERR_OUT(errp);
			else
			{
				(*ret_c) = ((u32_t)c16 & 0xFFFF);
				ret = 2;
			}
		}
		else if (Dz1Stream_read1(st, &c0, errp) < 0)
		{
			if (errp->code == EPIPE) { Dz1Error_set(errp, 0); ret = 0; }
			else ERR_OUT(errp);
		}
		else if (Dz1Stream_drain(st, 1, NULL, errp) < 0) ERR_OUT(errp);
		else
		{
			(*ret_c) = ((u32_t)c0 & 0xFF);
			ret = 1;
		}
	}
	return ret;
}

DZ1_CPPLINK size_t Dz1ElasticBufEntry_getDataSize(Dz1ElasticBufEntry *p);

// 0 = eof, 2 = letter, -1 = error
int Dz1JsonFifoW_getC(Dz1JsonFifo *src, SingleChar *ret_c, Dz1Error *err)
{	// pop_stream에는 local system의 wide charset 문자들이 들어있다. : Local System Charset = UCS-16
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = -1;

	if (src->ungetc_head != NULL)
	{
		Dz1JsonFifoUngetE *node = src->ungetc_head;
		src->ungetc_head = node->next;
		node->next = NULL;
		pthread_cleanup_push(Dz1JsonFifoUngetE_delAndSetNull, (void *)&node);
		ret = 1;
		*ret_c = node->c32;
		pthread_cleanup_pop(1); // (Dz1JsonFifoUngetE_delAndSetNull, (void *)&ret);
	}
	else
	{
		ssize_t cnt = 0;
//		size_t tsz;
		u16_t c16 = 0;
		bool_t done = FALSE;
		Dz1Stream *st = src->pop_stream;
		while(errp->code == 0 && done == FALSE)
		{
			if ((cnt = Dz1Stream_peek2(st, &c16, Dz1StreamMyEndian, errp)) < 0)
			{
				if (errp->code == EPIPE) { Dz1Error_set(errp, 0); ret = 0; done = TRUE; }
				else ERR_OUT(errp);
			}
			else if (cnt == 0) { Dz1Error_set(errp, 0); ret = 0; done = TRUE; }
			//-------------------------------------------------
			else if ((c16 & 0xFC00) == 0xD800)
			{	// High 2 byte of 4 byte Letter : 34 D8 1E DD
				u32_t v32 = 0;
				if (Dz1Stream_read4(st, &v32, Dz1StreamMyEndian, errp) < 0)	// read entire 4 byte letter
				{
					if (errp->code == EPIPE) { Dz1Error_set(errp, 0); ret = 0; done = TRUE; }
					else ERR_OUT(errp);
				}
				else if (Dz1Stream_drain(st, 4, NULL, errp) < 0) ERR_OUT(errp);
				else
				{	// make result
					(*ret_c) = ((v32 >> 16) & 0xFFFF) | ((v32 & 0xFFFF) << 16); // switch low/high
					ret = 4;
					Dz1Error_set(errp, 0);
					done = TRUE;
				}
			}
			else if ((c16 & 0xFC00) == 0xDC00)
			{	// Low 2 byte of 4 byte Letter = don't care -> drop
				u16_t temp16 = 0;
				if (Dz1Stream_read2(st, &temp16, Dz1StreamMyEndian, errp) < 0) ERR_OUT(errp);
				else if (Dz1Stream_drain(st, 2, NULL, errp) < 0) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			// Normal UCS-16 Letter
			else if (Dz1Stream_read2(st, &c16, Dz1StreamMyEndian, errp) < 0) ERR_OUT(errp);
			else if (Dz1Stream_drain(st, 2, NULL, errp) < 0) ERR_OUT(errp);
			else
			{
				(*ret_c) = (u32_t)c16 & 0xFFFF;
				ret = 2;
				Dz1Error_set(errp, 0);
				done = TRUE;
			}
		}
	}
	return ret;
}

// 0 = eof, 1 = normal letter, 2~4 = international language letter, -1 = error
int Dz1JsonFifoU8_getC(Dz1JsonFifo *src, SingleChar *ret_c, Dz1Error *err)
{	// pop_stream에는 local system의 wide charset 문자들이 들어있다. : Local System Charset = UTF-8
	DZ1_ERROR_SAFE_PTR(errp, err);

	int ret = -1;
	if (src->ungetc_head != NULL)
	{
		Dz1JsonFifoUngetE *node = src->ungetc_head;
		src->ungetc_head = node->next;
		node->next = NULL;
		pthread_cleanup_push(Dz1JsonFifoUngetE_delAndSetNull, (void *)&node);
		ret = 1;
		*ret_c = node->c32;
		pthread_cleanup_pop(1); // (Dz1JsonFifoUngetE_delAndSetNull, (void *)&ret);
	}
	else
	{
		ssize_t cnt = 0;
		u8_t c0 = 0;
		bool_t done = FALSE;
		Dz1Stream *st = src->pop_stream;

		while(errp->code == 0 && done == FALSE)
		{
			if ((cnt = Dz1Stream_peek1(st, &c0, NULL)) < 0)
			{
				if (errp->code == EPIPE) { Dz1Error_set(errp, 0); ret = 0; done = TRUE; }
				else ERR_OUT(errp);
			}
			else if (cnt == 0) { Dz1Error_set(errp, 0); ret = 0; done = TRUE; }
			else if ((c0 & 0xC0) == 0x80)
			{	// later byte of multi byte -> drop
				u8_t temp = 0;
				if (Dz1Stream_read1(st, &temp, errp) < 0) ERR_OUT(errp);
				else if (Dz1Stream_drain(st, 1, NULL, errp) < 0) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			else if ((c0 & 0x80) == 0x00)
			{	// normal ASCII
				if (0) { }
				else if (Dz1Stream_read1(st, &c0, errp) < 0) ERR_OUT(errp);
				else if (Dz1Stream_drain(st, 1, NULL, errp) < 0) ERR_OUT(errp);
				else
				{
					(*ret_c) = (SingleChar)c0 & 0xFF;
					ret = 1;
					Dz1Error_set(errp, 0);
					done = TRUE;
				}
			}
			else if ((c0 & 0xE0) == 0xC0)
			{	// 2 Byte
				u16_t temp = 0;
				if (Dz1Stream_read2(st, &temp, Dz1IOStreamEndian_big, errp) < 0)
				{
					if (errp->code == EPIPE) { Dz1Error_set(errp, 0); ret = 0; done = TRUE; }
					else ERR_OUT(errp);
				}
				else if (Dz1Stream_drain(st, 2, NULL, errp) < 0) ERR_OUT(errp);
				{
					*ret_c = ((SingleChar)temp & 0xFFFF);
					ret = 2;
					Dz1Error_set(errp, 0);
					done = TRUE;
				}
			}
			else if ((c0 & 0xF0) == 0xE0)
			{	// 3 Byte
				u8_t temp[3] = { 0, 0, 0 };
				if (Dz1Stream_read(st, temp, 3, errp) < 0)
				{
					if (errp->code == EPIPE) { Dz1Error_set(errp, 0); ret = 0; done = TRUE; }
					else ERR_OUT(errp);
				}
				else if (Dz1Stream_drain(st, 3, NULL, errp) < 0) ERR_OUT(errp);
				else
				{
					*ret_c = (((SingleChar)temp[0] & 0xFF) << 16) | (((SingleChar)temp[1] & 0xFF) << 8) | ((SingleChar)temp[2] & 0xFF);
					ret = 3;
					Dz1Error_set(errp, 0);
					done = TRUE;
				}
			}
			else if ((c0 & 0xF8) == 0xF0)
			{	// 4 Byte
				u32_t v32 = 0;
				if (Dz1Stream_read4(st, &v32, Dz1IOStreamEndian_big, errp) < 0)
				{
					if (errp->code == EPIPE) { Dz1Error_set(errp, 0); ret = 0; done = TRUE; }
					else ERR_OUT(errp);
				}
				else if (Dz1Stream_drain(st, 4, NULL, errp) < 0) ERR_OUT(errp);
				else
				{
					(*ret_c) = v32;
					ret = 4;
					Dz1Error_set(errp, 0);
					done = TRUE;
				}
			}
			else
			{
				Dz1Thread_printf(Dz1T("!!! Unacceptable UTF-8 Code = %02X\n"), c0);
				ERR_SET_OUT(errp, EINVAL);
			}
		}
	}
//	Dz1Thread_printf("@@@ getc = %d, %08X\n", ret, *ret_c);
	return ret;
}

bool_t Dz1JsonFifo_ungetC(Dz1JsonFifo *dst, u32_t c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonFifoUngetE *node = Dz1JsonFifoUngetE_new(c, dst->ungetc_head, errp);
	if (node == NULL) ERR_OUT(errp);
	else 
	{
		dst->ungetc_head = node;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

