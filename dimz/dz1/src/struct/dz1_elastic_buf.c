#include <dz1.h>
#include <stdio.h>
#include <wchar.h>
#include <dz1_int.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_elastic_buf.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1ElasticBufEntry Helper
// static Dz1ElasticBufEntry *Dz1ElasticBufEntry_create(size_t size, Dz1Error *err)
// {	// create node & allocate buffer
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1ElasticBufEntry *ret = Dz1ElasticBufEntry_new(NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		Dz1Binary *buf = NULL;
// 		pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&ret);
// 
// 		if ((ret->buf = buf = Dz1Binary_new(NULL, size, errp)) == NULL) ERR_OUT(errp);
// 		else if ((buf->data = (u8_t *)Dz1Calloc(sizeof(u8_t), (size + 1), errp)) == NULL) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
// 
// 		pthread_cleanup_pop(errp->code); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&ret);
// 	}
// 	return ret;
// }

Dz1ElasticBufEntry *Dz1ElasticBufEntry_new(u32_t size, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1ElasticBufEntry *__internal_ret = NULL;
	
	if (size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((__internal_ret = (Dz1ElasticBufEntry *)Dz1Calloc(sizeof(Dz1ElasticBufEntry), 1, errp)) == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->buf = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, size, errp)) == NULL) ERR_OUT(errp);
		else
		{
// 			__internal_ret->prev = __internal_ret->next = NULL;
// 			__internal_ret->data_start = __internal_ret->data_end = NULL;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

static Dz1ElasticBufEntry *Dz1ElasticBufEntry_clone(Dz1ElasticBufEntry *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBufEntry *ret = NULL;
	Dz1Binary *src_buf;
	if (src == NULL || (src_buf = src->buf) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src_buf->size != 0 && src_buf->data == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src_buf->data != NULL && (ret = Dz1ElasticBufEntry_new(src_buf->size, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&ret);
		if (src->buf != NULL && (ret->buf = Dz1Binary_clone(src->buf, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->data_start = src->data_start;
			ret->data_end = src->data_end;
			ret->next = ret->prev = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ElasticBufEntry_del(Dz1ElasticBufEntry *p)
{
	if (p == NULL) return;
	if (p->buf) Dz1Binary_del(p->buf);
	Dz1Free(p);
}

static ssize_t Dz1ElasticBufEntry_push(Dz1ElasticBufEntry *dst, u8_t *src, size_t size, Dz1Error *err)
{	// copy data & increase filled value
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (size == 0 || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1Binary *buf = dst->buf;
		u8_t *cp = buf->data + dst->data_end;
		size_t space_size = buf->size - dst->data_end;
		size_t copy_size = space_size > size ? size : space_size;
		memcpy(cp, src, copy_size);
		dst->data_end += (u32_t)copy_size;
		ret = (ssize_t)copy_size;
	}
	return ret;
}

static ssize_t Dz1ElasticBufEntry_inspect(Dz1ElasticBufEntry *src, u8_t *dst, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (size == 0) { }
	else
	{
		Dz1Binary *buf = src->buf;
		u8_t *sp = buf->data + src->data_start;

		size_t data_size = Dz1ElasticBufEntry_getDataSize(src);
		size_t copy_size = data_size > size ? size : data_size;

		if (dst != NULL) memcpy(dst, sp, copy_size);
		ret = (ssize_t)copy_size;
	}
	return ret;
}

static ssize_t Dz1ElasticBufEntry_pop(Dz1ElasticBufEntry *src, u8_t *dst, size_t size, Dz1Error *err)
{	// copy data & increase filled value
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((ret = Dz1ElasticBufEntry_inspect(src, dst, size, errp)) < 0) ERR_OUT(errp);
	else
	{
		src->data_start += (u32_t)ret;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static size_t Dz1ElasticBufEntry_getSpaceSize(Dz1ElasticBufEntry *p)
{
	Dz1Binary *buf = p->buf;
	size_t ret = buf->size - p->data_end;
	return ret;
}

size_t Dz1ElasticBufEntry_getDataSize(Dz1ElasticBufEntry *p)
{
	size_t ret = 0;
	if (p != NULL)
	{
		//Dz1Binary *buf = p->buf;
		ret = p->data_end - p->data_start;
	}
	return ret;
}

static u8_t *Dz1ElasticBufEntry_getDataPtr(Dz1ElasticBufEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u8_t *ret = NULL;
	Dz1Binary *buf = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((buf = p->buf) != NULL && buf->data != NULL)
		ret = buf->data + p->data_start;
	return ret;
}

static ssize_t Dz1ElasticBufEntry_write(Dz1ElasticBufEntry *p, FILE *fp, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL || fp == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t *ptr = Dz1ElasticBufEntry_getDataPtr(p);
		size_t sz = Dz1ElasticBufEntry_getDataSize(p);
		fwrite(ptr, sizeof(u8_t), sz, fp);
	}
	return ret;
}
// Dz1ElasticBufEntry Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1ElasticBuf Helper
static void Dz1ElasticBuf_append(Dz1ElasticBuf *dst, Dz1ElasticBufEntry **_node, Dz1ElasticBufAppendSide side)
{	// swallow node and link to tail
	Dz1ElasticBufEntry *node = (*_node);
	if (dst->head == NULL) dst->head = dst->tail = node;
	else
	{
		Dz1ElasticBufEntry *temp = NULL;
		switch(side)
		{
		case Dz1ElasticBufAppendSide_toFront:
			temp = dst->head;
			temp->prev = node;

			node->next = temp;
			node->prev = NULL;

			dst->head = node;
			break;
		default:
		case Dz1ElasticBufAppendSide_toTail:
			temp = dst->tail;
			temp->next = node;

			node->prev = temp;
			node->next = NULL;

			dst->tail = node;
			break;
		}
	}
	(*_node) = NULL;
}

static ssize_t Dz1ElasticBuf_copyAndAppend(Dz1ElasticBuf *dst, u8_t *buf, size_t size, Dz1Error *err)
{	// create new node and copy data, link to tail
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	Dz1ElasticBufEntry *node = NULL;

	u8_t *cp = buf;

	Dz1Error_set(errp, 0);
	while(errp->code == 0 && size)
	{
		if ((node = Dz1ElasticBufEntry_new(dst->elUnit, errp)) == NULL) ERR_OUT_RET(errp, -1);
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&node);
			if ((sz = Dz1ElasticBufEntry_push(node, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				Dz1ElasticBuf_append(dst, &node, Dz1ElasticBufAppendSide_toTail);
				cp += sz;
				ret += sz;
				size -= sz;
			}
			pthread_cleanup_pop(1); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&node);
		}
	}
	return ret;
}

static Dz1Error Dz1ElasticBuf_createAndAppend(Dz1ElasticBuf *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ElasticBufEntry *node = NULL;
	if ((node = Dz1ElasticBufEntry_new(dst->elUnit, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ElasticBuf_append(dst, &node, Dz1ElasticBufAppendSide_toTail);
		Dz1Error_set(errp, 0);
	}
	return err;
}

s64_t Dz1ElasticBuf_getDistance(Dz1ElasticBuf *eb, Dz1ElasticBufEntry *entry, u32_t pos, Dz1Error *err)
{
	s64_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t offset = entry->data_start <= pos ? pos - entry->data_start : 0;
	if (eb == NULL || entry == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		// size_t sz = 0;
		Dz1ElasticBufEntry *i = NULL;
		for (i = entry->prev; i != NULL; i = i->prev)
			ret += Dz1ElasticBufEntry_getDataSize(i);
		ret += offset;
	}
	return ret;
}
// Dz1ElasticBuf Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1ElasticBuf API
Dz1ElasticBuf *_Dz1ElasticBuf_new(u32_t elUnit, bool_t create_head, Dz1Error *err, char *__file__, int __line__)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1ElasticBuf *__internal_ret = (Dz1ElasticBuf *)_Dz1Calloc(sizeof(Dz1ElasticBuf), 1, errp, __file__, __line__);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->elUnit = elUnit;
		if (create_head == TRUE && (*errp = Dz1ElasticBuf_createAndAppend(__internal_ret)).code) ERR_OUT(errp);
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ElasticBuf_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1ElasticBuf *Dz1ElasticBuf_clone(Dz1ElasticBuf *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1ElasticBuf_new(src->elUnit, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ElasticBufEntry *i, *node = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&ret);
		for (i = src->head; errp->code == 0 && i != NULL; i = i->next)
		{
			if ((node = Dz1ElasticBufEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&node);
				Dz1ElasticBuf_append(ret, &node, Dz1ElasticBufAppendSide_toTail);
				pthread_cleanup_pop(1); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&node);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1ElasticBuf_delAndSetNull, (void *)ret);
	}
	return ret;
}

static void _Dz1ElasticBuf_del(Dz1ElasticBuf *p)
{
	if (p->head)
	{
		Dz1ElasticBufEntry *i = p->head, *next = NULL;
		while(i)
		{
			next = i->next;
			Dz1ElasticBufEntry_del(i);
			i = next;
		}
	}
	p->head = p->tail = NULL;
}

void Dz1ElasticBuf_del(Dz1ElasticBuf *p)
{
	if (p == NULL) return;
	_Dz1ElasticBuf_del(p);
	Dz1Free(p);
}

static bool_t Dz1ElasticBufEntry_isEOF(Dz1ElasticBufEntry *p, u32_t idx)
{
	bool_t ret = TRUE;
	if (p == NULL) { }
	else if (p->data_start <= idx && idx < p->data_end) ret = FALSE;
	return ret;
}

static Dz1ElasticBufEntry *Dz1ElasticBufEntry_nextByte(Dz1ElasticBufEntry *p, u32_t *ret_idx)
{
	u32_t idx = *ret_idx;
	Dz1ElasticBufEntry *ret = p;
	if (idx < ret->data_start) idx = ret->data_start;
	else
	{
		idx++;
		if (idx >= p->data_end)
		{
			if ((ret = p->next) == NULL) idx = (u32_t)-1;
			else idx = ret->data_start;
		}
	}
	*ret_idx = idx;
	return ret;
}

static u8_t Dz1ElasticBufEntry_getByte(Dz1ElasticBufEntry *p, u32_t idx)
{
	u8_t ret = 0;
	if (p != NULL && p->data_start <= idx && idx < p->data_end)
	{
		Dz1Binary *bin = p->buf;
		ret = bin->data[idx];
	}
	return ret;
}

void Dz1ElasticBufA_dump(Dz1ElasticBuf *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else if (p->head == NULL) Dz1ThreadA_tprintf(tab, "Empty\n");
	else
	{
		u8_t temp[17];
		u32_t idx, remain = 15;

		u32_t i;
		Dz1ElasticBufEntry *node;
		size_t sz = 0;
		for (i = 0, node = p->head; node != NULL; node = node->next, i++)
			sz += Dz1ElasticBufEntry_getDataSize(node);
		Dz1ThreadA_tprintf(tab, "%u Frag(%u Byte) / %u Byte Filled\n", i, p->elUnit, sz);

		for (i = 0, node = p->head, idx = node->data_start; i < 256 && Dz1ElasticBufEntry_isEOF(node, idx) == FALSE; node = Dz1ElasticBufEntry_nextByte(node, &idx), i++)
		{
			if ((remain = i % 16) == 0) Dz1ThreadA_tprintf(tab + 1, "%08X:", i);

			temp[remain] = Dz1ElasticBufEntry_getByte(node, idx);
			Dz1ThreadA_printf(" %02X", temp[remain]);
			if (temp[remain] < 32 || (temp[remain] & 0x80)) temp[remain] = '.';
			temp[remain + 1] = 0;

			if (remain == 15) Dz1ThreadA_printf("  %s\n", temp);
		}

		if (remain != 15)
		{
			for (i = remain; i < 15; i++) Dz1ThreadA_printf("   ");
			Dz1ThreadA_printf("  %s\n", temp);
		}

		if (sz > 256) Dz1ThreadA_tprintf(tab + 1, "*** data dump is truncated ***\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1ElasticBufW_dump(Dz1ElasticBuf *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else if (p->head == NULL) Dz1ThreadW_tprintf(tab, L"Empty\n");
	else
	{
		u16_t temp[17];
		u32_t idx, remain = 15;

		u32_t i;
		Dz1ElasticBufEntry *node;
		size_t sz = 0;
		for (i = 0, node = p->head; node != NULL; node = node->next, i++)
			sz += Dz1ElasticBufEntry_getDataSize(node);
		Dz1ThreadW_tprintf(tab, L"%u Frag(%u Byte) / %u Byte Filled\n", i, p->elUnit, sz);

		for (i = 0, node = p->head, idx = node->data_start; i < 256 && Dz1ElasticBufEntry_isEOF(node, idx) == FALSE; node = Dz1ElasticBufEntry_nextByte(node, &idx), i++)
		{
			if ((remain = i % 16) == 0) Dz1ThreadW_tprintf(tab + 1, L"%08X:", i);

			temp[remain] = Dz1ElasticBufEntry_getByte(node, idx);
			Dz1ThreadW_printf(L" %02X", temp[remain]);
			if (temp[remain] < 32 || (temp[remain] & 0x80)) temp[remain] = L'.';
			temp[remain + 1] = 0;

			if (remain == 15) Dz1ThreadW_printf(L"  %s\n", temp);
		}

		if (remain != 15)
		{
			for (i = remain; i < 15; i++) Dz1ThreadA_printf("   ");
			Dz1ThreadW_printf(L"  %s\n", temp);
		}

		if (sz > 256) Dz1ThreadW_tprintf(tab + 1, L"*** data dump is truncated ***\n");
	}
}
#endif
// buf의 내용을 Elastic Buffer로 복사한다.
bool_t _Dz1ElasticBuf_push(Dz1ElasticBuf *dst, u8_t *buf, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (buf == NULL && size > 0)
		ERR_SET_OUT(errp, EINVAL);
	else if (size == 0) Dz1Error_set(errp, 0);
	else
	{
		u8_t *cp = buf;
		ssize_t sz = 0;
		while(errp->code == 0 && size)
		{
			if (dst->head == NULL || Dz1ElasticBufEntry_getSpaceSize(dst->tail) == 0)
			{	// list is empty or no space on tail
				if ((sz = Dz1ElasticBuf_copyAndAppend(dst, cp, size, errp)) < 0) ERR_OUT(errp);
				else { cp += sz; size -= sz; }
			}
			else
			{	// list isn't empty and node has space
				if ((sz = Dz1ElasticBufEntry_push(dst->tail, cp, size, errp)) < 0) ERR_OUT(errp);
				else { cp += sz; size -= sz; }
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Error Dz1ElasticBuf_push(Dz1ElasticBuf *dst, u8_t *buf, size_t size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1ElasticBuf_push(dst, buf, size, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

ssize_t Dz1ElasticBuf_pop(Dz1ElasticBuf *src, u8_t *dst, size_t dst_size, Dz1Error *err)
{	// Elastic Buffer의 처음부터 꺼내 dst에 복사한다.
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (dst_size == 0) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (src->head == NULL) { }
	else
	{
		bool_t empty = FALSE;
		u8_t *dp = dst;
		ssize_t sz = 0;
		Dz1ElasticBufEntry *head = NULL;
		while(errp->code == 0 && dst_size && empty == FALSE)
		{
			head = src->head;
			if ((sz = Dz1ElasticBufEntry_pop(head, dp, dst_size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				if (dst != NULL) dp += sz;
				dst_size -= sz;
				ret += sz;

				if (Dz1ElasticBufEntry_getDataSize(head) == 0)
				{
					pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&head);
					if (head == src->tail)
					{
						// 마지막 남은 엔트리
//						Dz1Thread_eprintf("@@@ Flush Head\n");
						head->data_start = head->data_end = 0;
						head = NULL;
						empty = TRUE;
					}
					else
					{
//						Dz1Thread_eprintf("@@@ Drop Head\n");
						src->head = head->next;
						head->next = NULL;
						src->head->prev = NULL;
					}
					pthread_cleanup_pop(1); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&head);
				}
			}
		}
	}
	return ret;
}

typedef struct Dz1ElasticBufMoveCancelArg
{
	Dz1ElasticBuf			*dst;
	Dz1ElasticBufEntry		*tail;
	u32_t					 data_end;
} Dz1ElasticBufMoveCancelArg;

static void Dz1ElasticBuf_moveCancel(void *ptr)
{
	Dz1ElasticBufMoveCancelArg *arg = (Dz1ElasticBufMoveCancelArg *)ptr;
	Dz1ElasticBuf *dst = arg->dst;
	if (arg->tail == NULL) Dz1ElasticBuf_empty(dst);	// dst was empty
	else
	{
		Dz1ElasticBufEntry *tail = arg->tail;					// original tail
		Dz1ElasticBufEntry *drop_next, *drop_node = tail->next;	// trim position

		tail->next = NULL;										// make sure end-of-node
		tail->data_end = arg->data_end;							// make sure end-of-data-pos

		dst->tail = arg->tail;									// reset tail to original

		while(drop_node != NULL)								// delete appended data
		{
			drop_next = drop_node->next;
			Dz1ElasticBufEntry_del(drop_node);
			drop_node = drop_next;
		}
	}
}

bool_t Dz1ElasticBuf_move(Dz1ElasticBuf *dst, Dz1ElasticBuf *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u8_t *sp = NULL;
		u32_t push_size = 0;
		Dz1Binary *bin = NULL;
		Dz1ElasticBufEntry *i, *tail = dst->tail;

		Dz1ElasticBufMoveCancelArg arg = { dst, tail, tail == NULL ? 0 : tail->data_end };

		pthread_cleanup_push(Dz1ElasticBuf_moveCancel, (void *)&arg);
		Dz1Error_set(errp, 0);
		for (i = src->head; errp->code == 0 && i != NULL; i = i->next)
		{
			bin = i->buf;
			sp = bin->data + i->data_start;
			push_size = i->data_end - i->data_start;
			if (_Dz1ElasticBuf_push(dst, sp, push_size, errp) == FALSE) ERR_OUT(errp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ElasticBuf_moveCancel, (void *)&arg);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// 내용을 모두 지우고 조각을 하나도 남기지 않는다
bool_t _Dz1ElasticBuf_empty(Dz1ElasticBuf *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		_Dz1ElasticBuf_del(p);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

Dz1Error Dz1ElasticBuf_empty(Dz1ElasticBuf *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1ElasticBuf_empty(p, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

bool_t Dz1ElasticBuf_isEmpty(Dz1ElasticBuf *p)
{
	bool_t ret = FALSE;
	Dz1ElasticBufEntry *head;
	if (p == NULL) ret = TRUE;
	else if ((head = p->head) == p->tail)
	{
		if (head == NULL) ret = TRUE;
		else if (head->data_end == head->data_start) ret = TRUE;
	}
	return ret;
}

// 조각나 있는 내용을 하나로 뭉친다
static Dz1Error _flatten_copy(Dz1Binary *dst, Dz1ElasticBuf *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u8_t *cp = dst->data;
	u32_t size = dst->size;

	//Dz1Binary *p = NULL;
	Dz1ElasticBufEntry *i = NULL;

	ssize_t sz;
	for (i = src->head; errp->code == 0 && size > 0 && i != NULL; i = i->next)
	{
		if ((sz = Dz1ElasticBufEntry_inspect(i, cp, size, errp)) < 0) ERR_OUT(errp);
		else
		{
			cp += sz;
			size -= (u32_t)sz;
		}
	}
	return err;
}

Dz1Binary const * const _Dz1ElasticBuf_flatten(Dz1ElasticBuf *p, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;

	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->head == NULL) Dz1Error_set(errp, ENOENT);
	else if (p->head == p->tail)
	{	// 한개의 Entry 만 존재
		Dz1ElasticBufEntry *tgt = p->head;
		Dz1Binary *src = tgt->buf;
		size_t data_sz = Dz1ElasticBufEntry_getDataSize(tgt), threshold = p->elUnit >> 1;
		if (p->elUnit >= 512 && data_sz >= threshold)
		{	// data is enough big to elUnit -> just copy & reuse
			ret = src;
			if (tgt->data_start > 0)
			{	// need copy
				u8_t *sp = src->data + tgt->data_start;
				memcpy(ret->data, sp, data_sz);
			}
			tgt->data_start = 0;
			tgt->data_end = ret->size = (u32_t)data_sz;
		}
		// data is significant small -> realloc & copy
		else if ((ret = _Dz1Binary_new(DZ1_BIN_DATA_ALLOC, (u32_t)data_sz, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
		else
		{
			u8_t *sp = src->data + tgt->data_start;

			memcpy(ret->data, sp, data_sz);

			Dz1Binary_delAndSetNull(&tgt->buf);
			tgt->buf = ret;

			tgt->data_start = 0;
			tgt->data_end = ret->size = (u32_t)data_sz;

// 			ssize_t sz = 0;
// 			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
// 			if ((sz = Dz1ElasticBufEntry_inspect(p->head, ret->data, ret->size, errp)) < 0) ERR_OUT(errp);
// 			else if (sz != (ssize_t)ret->size) ERR_SET_OUT(errp, EINVAL);
// 			else
// 			{
// 				Dz1ElasticBufEntry *head = p->head;
// 				Dz1Binary_delAndSetNull(&head->buf);
// 				head->buf = ret;
// 				head->data_start = 0;
// 				head->data_end = ret->size;
// 			}
// 			pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
		}
	}
	else
	{	// 여러개의 Entry가 존재
		ssize_t size = Dz1ElasticBuf_getDataSize(p, errp);
		if (size < 0) ERR_OUT(errp);
		else
		{
			Dz1ElasticBufEntry *flatten = Dz1ElasticBufEntry_new((u32_t)size, errp);
			if (flatten == NULL) ERR_OUT(errp);
			else
			{
				Dz1Binary *tmp = flatten->buf;
				pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&flatten);

				if ((*errp = _flatten_copy(tmp, p)).code) ERR_OUT(errp);
				else
				{
					_Dz1ElasticBuf_del(p);	// 내부 Linked List만 삭제
					flatten->data_start = 0;
					flatten->data_end = (u32_t)size;
					p->head = p->tail = flatten;
					ret = flatten->buf;
					flatten = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&flatten);
			}
		}
	}
	return ret;
}

static Dz1Binary *Dz1ElasticBuf_purge(Dz1ElasticBuf *p)
{
	Dz1Binary *ret = NULL;
	Dz1ElasticBufEntry *head = p->head;
	pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&head);
	p->head = p->tail = NULL;
	ret = head->buf;
	head->buf = NULL;
	head->data_start = head->data_end = 0;
	pthread_cleanup_pop(1); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&head);
	return ret;
}

Dz1Binary *_Dz1ElasticBuf_flattenAndPurge(Dz1ElasticBuf *p, Dz1Error *err, const char *__file__, int __line__)
{	// 조각나 있는 내용을 하나로 뭉친Binary를 돌려주고 내용을 비운다
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;
	if (_Dz1ElasticBuf_flatten(p, errp, __file__, __line__) == NULL)
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
		else if ((ret = Dz1Binary_new(NULL, 0, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		ret = Dz1ElasticBuf_purge(p);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

ssize_t Dz1ElasticBuf_getTailByte(Dz1ElasticBuf *p, u8_t *buf, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t mount = 0;
	ssize_t hold_sz = 0;
	if (p == NULL || buf == NULL || sz == 0) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((hold_sz = Dz1ElasticBuf_getDataSize(p, errp)) < 0) ERR_OUT_RET(errp, -1);
	else if (hold_sz < (ssize_t)sz)
	{
		Dz1ElasticBufEntry *tgt;
		u8_t *dp = buf, *sp = NULL;
		for (tgt = p->head; sz > 0 && tgt != NULL; tgt = tgt->next)
		{
			mount = tgt->data_end - tgt->data_start;
			sp = tgt->buf->data + tgt->data_start;
			memcpy(dp, sp, mount);
			dp += mount;
			sz -= mount;
		}
		return hold_sz;
	}
	else
	{
		Dz1ElasticBufEntry *tgt = p->tail;
		size_t temp_sz = sz;
		ssize_t copied = sz;
		while(tgt != NULL && temp_sz)
		{
			mount = tgt->data_end - tgt->data_start;
			if (mount >= temp_sz)
			{	// stop here
				u8_t *dp = buf, *sp = NULL;
				u32_t copy_start = tgt->data_end - (u32_t)temp_sz;
				size_t copy_sz = temp_sz;
				sp = tgt->buf->data + copy_start;
				memcpy(dp, sp, copy_sz);
				dp += copy_sz;
				sz -= copy_sz;
				for (tgt = tgt->next; sz > 0 && tgt != NULL; tgt = tgt->next)
				{
					mount = tgt->data_end - tgt->data_start;
					sp = tgt->buf->data + tgt->data_start;
					copy_sz = mount <= sz ? mount : sz;
					memcpy(dp, sp, copy_sz);
					dp += copy_sz;
					sz -= copy_sz;
				}
				break;
			}
			else
			{
				temp_sz -= mount;
				tgt = tgt->prev;
			}
		}
		return copied;
	}
}

ssize_t Dz1ElasticBuf_reduce(Dz1ElasticBuf *p, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0, hold_sz;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (sz == 0) Dz1Error_set(errp, 0);
	else if ((hold_sz = Dz1ElasticBuf_getDataSize(p, errp)) < 0) ERR_OUT(errp);
	else if (hold_sz <= (ssize_t)sz)
	{	// just empty
		if (_Dz1ElasticBuf_empty(p, errp) == FALSE) ERR_OUT(errp);
		else { ret = hold_sz; Dz1Error_set(errp, 0); }
	}
	else
	{
		u32_t mount;
		size_t temp_sz = sz;
		Dz1ElasticBufEntry *tgt = p->tail;
		while(tgt != NULL && temp_sz)
		{
			mount = tgt->data_end - tgt->data_start;
			if (mount >= temp_sz)
			{
				tgt->data_end -= (u32_t)temp_sz;
				break;
			}
			else
			{
				temp_sz -= mount;
				tgt = tgt->prev;
			}
		}

		if (tgt == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			Dz1ElasticBufEntry *rmv = tgt->next, *next = NULL;
			tgt->next = NULL;

			while(rmv != NULL)
			{
				next = rmv->next;
				rmv->next = NULL;
				Dz1ElasticBufEntry_del(rmv);
				rmv = next;
			}
		}
	}
	return SELECT_BY_ERR(errp, ret, -1);
}

///////////////////////////////////////////////////////////////////////////////
// String Type Handling
bool_t Dz1ElasticBuf_pushStrNA(Dz1ElasticBuf *dst, str_t str, size_t len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (str != NULL && len > 0)
	{
		size_t byte_sz = len * sizeof(char);
		if ((*errp = Dz1ElasticBuf_push(dst, (u8_t *)str, byte_sz)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#ifndef UNIX_SYSTEM
bool_t Dz1ElasticBuf_pushStrNW(Dz1ElasticBuf *dst, wstr_t str, size_t len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (str != NULL && len > 0)
	{
		size_t byte_sz = len * sizeof(wchar_t);
		if ((*errp = Dz1ElasticBuf_push(dst, (u8_t *)str, byte_sz)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif

bool_t Dz1ElasticBuf_pushStrA(Dz1ElasticBuf *dst, str_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len = 0;
	if (str != NULL && (len = strlen(str)) > 0)
	{
		if (Dz1ElasticBuf_pushStrNA(dst, str, len, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#ifndef UNIX_SYSTEM
bool_t Dz1ElasticBuf_pushStrW(Dz1ElasticBuf *dst, wstr_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len = 0;
	if (str != NULL && (len = wcslen(str)) > 0)
	{
		if (Dz1ElasticBuf_pushStrNW(dst, str, len, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif

bool_t Dz1ElasticBuf_pushChrA(Dz1ElasticBuf *dst, char c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1ElasticBuf_push(dst, (u8_t *)&c, sizeof(char))).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
#ifndef UNIX_SYSTEM
bool_t Dz1ElasticBuf_pushChrW(Dz1ElasticBuf *dst, wchar_t c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1ElasticBuf_push(dst, (u8_t *)&c, sizeof(wchar_t))).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
#endif

bool_t Dz1ElasticBuf_peekLastChrA(Dz1ElasticBuf *p, char *c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1ElasticBuf_getTailByte(p, (u8_t *)c, 1, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
#ifndef UNIX_SYSTEM
bool_t Dz1ElasticBuf_peekLastChrW(Dz1ElasticBuf *p, wchar_t *c, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1ElasticBuf_getTailByte(p, (u8_t *)c, sizeof(wchar_t), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
#endif

str_t Dz1ElasticBuf_flattenStrA(Dz1ElasticBuf *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	Dz1Binary *bin = NULL;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1ElasticBuf_pushChrA(dst, 0, errp) == FALSE) ERR_OUT(errp);
	else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(dst, errp)) == NULL) ERR_OUT(errp);
	else ret = (str_t)bin->data;
	return ret;
}
#ifndef UNIX_SYSTEM
wstr_t Dz1ElasticBuf_flattenStrW(Dz1ElasticBuf *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	Dz1Binary *bin = NULL;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1ElasticBuf_pushChrW(dst, 0, errp) == FALSE) ERR_OUT(errp);
	else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(dst, errp)) == NULL) ERR_OUT(errp);
	else ret = (wstr_t)bin->data;
	return ret;
}
#endif

str_t Dz1ElasticBuf_flattenStrAndPurgeA(Dz1ElasticBuf *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	if (Dz1ElasticBuf_flattenStrA(dst, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = Dz1ElasticBuf_purge(dst);
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		ret = (str_t)bin->data;
		bin->data = 0;
		bin->size = 0;
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
wstr_t Dz1ElasticBuf_flattenStrAndPurgeW(Dz1ElasticBuf *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	if (Dz1ElasticBuf_flattenStrW(dst, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = Dz1ElasticBuf_purge(dst);
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		ret = (wstr_t)bin->data;
		bin->data = 0;
		bin->size = 0;
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}
#endif
// String Type Handling
///////////////////////////////////////////////////////////////////////////////

ssize_t Dz1ElasticBuf_write(Dz1ElasticBuf *p, FILE *fp, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL || fp == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		ssize_t sz = 0;
		Dz1ElasticBufEntry *i = NULL;
		for (i = p->head; i != NULL; i = i->next)
		{
			if ((sz = Dz1ElasticBufEntry_write(i, fp, errp)) < 0) ERR_OUT_RET(errp, -1);
			else ret += sz;
		}
	}
	return ret;
}

Dz1Error Dz1ElasticBuf_load(Dz1ElasticBuf *p, FILE *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (feof(src)) ERR_SET_OUT(errp, EPIPE);
	else
	{
		bool_t done = FALSE;
		Dz1ElasticBufEntry *node = NULL;
		while(done == FALSE)
		{
			if ((node = Dz1ElasticBufEntry_new(p->elUnit, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz, total = 0;
				Dz1Binary *buf = node->buf;
				pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&node);

				if ((sz = (ssize_t)fread(buf->data, sizeof(u8_t), buf->size, src)) > 0)
				{	// 몇 바이트든 읽었음
					node->data_end = (u32_t)sz;
					total += sz;
					Dz1ElasticBuf_append(p, &node, Dz1ElasticBufAppendSide_toTail); // link this node
				}
				else
				{	// 하나도 못읽음
					done = TRUE;
				}
				pthread_cleanup_pop(1); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return err;
}

// buf의 내용을 FILE 에 모두 기록한다.
Dz1Error Dz1ElasticBuf_save(Dz1ElasticBuf *p, FILE *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	size_t written;
	Dz1ElasticBufEntry *i;
	u8_t *ptr = NULL;
	ssize_t sz = 0;
	for (i = p->head; errp->code == 0 && i != NULL; i = i->next)
	{
		if ((ptr = Dz1ElasticBufEntry_getDataPtr(i)) != NULL && (sz = (ssize_t)Dz1ElasticBufEntry_getDataSize(i)) > 0)
		{
			written = fwrite(ptr, sizeof(u8_t), sz, dst);
			if (written == 0)
			{
				if (feof(dst)) ERR_SET_OUT(errp, EPIPE);
				else ERR_SET_OUT(errp, ferror(dst));
			}
			else if (written != (size_t)sz)
			{
				if (feof(dst)) Dz1Error_set(errp, 0);
				else ERR_SET_OUT(errp, ferror(dst));
			}
		}
	}
	return err;
}

Dz1ElasticBufEntry *Dz1ElasticBuf_alloc(Dz1ElasticBuf *p, Dz1ElasticBufAppendSide side, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBufEntry *ret = NULL, *node = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1ElasticBufEntry_new(p->elUnit, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBufEntry_delAndSetNull, (void *)&node);
		ret = node;
		Dz1ElasticBuf_append(p, &node, side);
		pthread_cleanup_pop(1); // (Dz1ElasticBufEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

ssize_t Dz1ElasticBuf_getDataSize(Dz1ElasticBuf *p, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (p == NULL) ERR_SETOUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1ElasticBufEntry *i;
		for (i = p->head; i != NULL; i = i->next)
			ret += (ssize_t)Dz1ElasticBufEntry_getDataSize(i);
//		Dz1Thread_eprintf("Dz1ElasticBuf_getDataSize() : %d\n", ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Liquid String
Dz1LiquidString *Dz1LiquidString_new(str_t charset, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1LiquidString *ret = NULL;
	if (charset != NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1LiquidString *)Dz1Calloc(sizeof(Dz1LiquidString), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LiquidString_delAndSetNull, (void *)&ret);
		if ((ret->buf = Dz1ElasticBuf_new(512, TRUE, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1LiquidString_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1LiquidString *Dz1LiquidString_clone(Dz1LiquidString *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1LiquidString *ret = NULL;
	if (src == NULL || src->buf == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1LiquidString *)Dz1Calloc(sizeof(Dz1LiquidString), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LiquidString_delAndSetNull, (void *)&ret);
		if ((ret->buf = Dz1ElasticBuf_clone(src->buf, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1LiquidString_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LiquidString_del(Dz1LiquidString *p)
{
	if (p == NULL) return;
	Dz1ElasticBuf_delAndSetNull(&p->buf);
}

#define TEMP_STRING_LENGTH			32768
ssize_t Dz1LiquidString_A_Format(Dz1LiquidString *dst, str_t fmt, ...)
{
	ssize_t cnt = 0;
	DZ1_ERROR_SAFE_VAR(errp, err);
	char *temp = NULL;

	va_list ap;
	va_start(ap, fmt);

	if ((temp = (char *)Dz1Malloc(TEMP_STRING_LENGTH, errp)) == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);

		if ((cnt = vsnprintf(temp, TEMP_STRING_LENGTH, fmt, ap)) < 0) ERR_SETOUT_RET(errp, errno, -1);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
	va_end(ap);
	return cnt;
}

ssize_t Dz1LiquidString_A_Assign(Dz1LiquidString *dst, str_t str)
{
	ssize_t ret = 0;
	size_t len;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (dst == NULL || dst->buf == NULL || str == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((len = strlen(str)) > 0)
	{
		Dz1ElasticBuf *buf = dst->buf;
		Dz1ElasticBuf_empty(buf);
		if ((*errp = Dz1ElasticBuf_push(buf, (u8_t *)str, len)).code) ERR_OUT(errp);
	}
	return ret;
}

char const * const Dz1LiquidString_A_Printable(Dz1LiquidString *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t ret = NULL;
	if (dst->buf == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u8_t v = 0;
		Dz1ElasticBuf *buf = dst->buf;
		Dz1Binary const *bin = NULL;
		if ((*errp = Dz1ElasticBuf_push(buf, &v, sizeof(v))).code) ERR_OUT(errp);
		else if ((bin = Dz1ElasticBuf_flatten(buf, errp)) == NULL) ERR_OUT(errp);
		else ret = (char *)bin->data;
	}
	return ret;
}
#ifndef UNIX_SYSTEM
ssize_t Dz1LiquidString_W_Format(Dz1LiquidString *dst, wstr_t fmt, ...)
{
	ssize_t cnt = 0;
	DZ1_ERROR_SAFE_VAR(errp, err);
	wchar_t *temp = NULL;

	va_list ap;
	va_start(ap, fmt);

	if ((temp = (wchar_t *)Dz1Malloc(TEMP_STRING_LENGTH * sizeof(wchar_t), errp)) == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		if (0) { } 
		else if ((cnt = _std_vsnprintfW(temp, TEMP_STRING_LENGTH, fmt, ap)) < 0) ERR_SETOUT_RET(errp, errno, -1);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}

	va_end(ap);
	return cnt;
}

ssize_t Dz1LiquidString_W_Assign(Dz1LiquidString *dst, wstr_t str)
{
	ssize_t ret = 0;
	size_t len;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (dst == NULL || dst->buf == NULL || str == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((len = wcslen(str)) > 0)
	{
		Dz1ElasticBuf *buf = dst->buf;
		Dz1ElasticBuf_empty(buf);
		if ((*errp = Dz1ElasticBuf_push(buf, (u8_t *)str, len * sizeof(wchar_t))).code) ERR_OUT(errp);
	}
	return ret;
}

wchar_t const * const Dz1LiquidString_W_Printable(Dz1LiquidString *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	wstr_t ret = NULL;
	if (dst->buf == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u16_t v = 0;
		Dz1ElasticBuf *buf = dst->buf;
		Dz1Binary const * bin = NULL;
		if ((*errp = Dz1ElasticBuf_push(buf, (u8_t *)&v, sizeof(v))).code) ERR_OUT(errp);
		else if ((bin = Dz1ElasticBuf_flatten(buf, errp)) == NULL) ERR_OUT(errp);
		else ret = (wchar_t *)bin->data;
	}
	return ret;
}
#endif
// Liquid String
///////////////////////////////////////////////////////////////////////////////
