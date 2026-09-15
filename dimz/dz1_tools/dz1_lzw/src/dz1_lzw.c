#include "dz1_lzw.h"

static Dz1Error Dz1LzwCompStream_flushOut(Dz1LzwCompStream *dst)
{
	u8_t v;
	DZ1_ERROR_SAFE_VAR(errp, err);

	while(dst->bb_remain >= 8)
	{
		v = (dst->bb & 0xFF);

		// output Byte
		if (dst->byte_idx == dst->byte_size) { ERR_SET_OUT(errp, ENOMEM); return err; }
		else dst->byte_arr[dst->byte_idx++] = v;

		dst->bb_remain -= 8;
		dst->bb >>= 8;
	}

	if (dst->bb_remain)
	{
		v = dst->bb & ((1 << dst->bb_remain) -1);
		if (dst->byte_idx == dst->byte_size) { ERR_SET_OUT(errp, ENOMEM); return err; }
		else dst->byte_arr[dst->byte_idx++] = v;
	}
	return err;
}

static Dz1Error Dz1LzwCompStream_putCode(Dz1LzwCompStream *dst, u32_t code, u32_t code_size)
{
	u8_t v;
	u32_t work_bits = code_size + 1;
	DZ1_ERROR_SAFE_VAR(errp, err);
	dst->code_arr[dst->arr_idx++] = code;
	Dz1Thread_printf("%08X:%u\n", code, work_bits);

	// 여기 들어올 때 bb_remain은 8보다 작다

	if (work_bits + dst->bb_remain > 32)
	{	// 새로 들어온 것과 합쳐서 32비트를 넘는다.
		u32_t consume_bb = 32 - dst->bb_remain;				// code에서 소모할 비트 수
		u32_t temp = (code << dst->bb_remain) | dst->bb;	// temp에 code의 하위 n 비트와 bb를 합쳐서 32비트를 만든다.
		u32_t temp_remain = 32;

		code >>= consume_bb;								// code에서 소모한 비트 수만큼 내보낸다.
		work_bits -= consume_bb;

		while(temp_remain)									// temp를 비운다.
		{
			v = (temp & 0xFF);

			// output Byte
			if (dst->byte_idx == dst->byte_size) { ERR_SET_OUT(errp, ENOMEM); return err; }
			else dst->byte_arr[dst->byte_idx++] = v;

			temp_remain -= 8;
			temp >>= 8;
		}
		dst->bb = code;
		dst->bb_remain = consume_bb;
	}
	else
	{
		dst->bb |= code << dst->bb_remain;
		dst->bb_remain += work_bits;
	}

	while(dst->bb_remain >= 8)
	{
		v = (dst->bb & 0xFF);

		// output Byte
		if (dst->byte_idx == dst->byte_size) { ERR_SET_OUT(errp, ENOMEM); return err; }
		else dst->byte_arr[dst->byte_idx++] = v;

		dst->bb_remain -= 8;
		dst->bb >>= 8;
	}

	return err;
}

static Dz1Error Dz1LzwOutStream_putData(Dz1LzwDecompStream *dst, u8_t *data, u32_t size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
//	Dz1Thread_printb(data, size, 16);
	while(size--)
		dst->data_arr[dst->arr_idx++] = *data++;
	Dz1Error_set(errp, 0);
	return err;
}

static u32_t Dz1LzwDictionary_searchWord(Dz1LzwDictionary *p, u8_t *w, u32_t size)
{
	u32_t ret = -1;
	if (size == 1) ret = (u32_t)(*w);
	else
	{
		Dz1LzwDictSizeTable *wt = p->sizes;
		Dz1LzwDictSizeNode key = { size }, *node = wt->find(wt, &key);
		if (node)
		{
			Dz1LzwDictWordList *list = node->list;
			Dz1Binary b_key = { w, size };
			Dz1LzwDictWord key = { 0, &b_key }, *word = list->find(list, &key);
			if (word) ret = word->code;
		}
	}
	return ret;
}

static bool_t Dz1LzwDictionary_searchCode(Dz1LzwDictionary *p, u32_t code, u8_t *dst, u32_t *dst_size)
{
	bool_t ret = FALSE;
	if (code < p->base_code_max)
	{
		dst[0] = (u8_t)(code & (p->base_code_max-1));
		(*dst_size) = 1;
		ret = TRUE;
	}
	else
	{
		Dz1LzwDictCode key = { code }, *node = p->codes->find(p->codes, &key);
		if (node != NULL)
		{
			Dz1Binary *bin = node->bin;
			memcpy(dst, bin->data, ( (*dst_size) = bin->size));
			ret = TRUE;
		}
//		else Dz1Thread_printf("!!! code %08X not found\n", code);
	}
	return ret;
}

static Dz1LzwDictSizeNode *_getSizeNode(u32_t size, Dz1LzwDictSizeTable *sizes, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1LzwDictSizeNode key = { size }, *ret = sizes->find(sizes, &key);
	if (ret == NULL)
	{
		if ((ret = Dz1LzwDictSizeNode_new(size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1LzwDictSizeNode_delAndSetNull, (void *)&ret);
			if ((*errp = sizes->add(sizes, ret)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1LzwDictWordNode_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

static Dz1Error _appendWord(Dz1LzwDictionary *dict, Dz1LzwDictSizeNode *s_node, u8_t *w, u32_t size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1LzwDictData *node = NULL;
	if ((node = Dz1LzwDictData_new(dict->alloc_code++, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LzwDictData_delAndSetNull, (void *)&node);
		if ((node->bin = Dz1Binary_new(w, size, errp)) == NULL) ERR_OUT(errp);
		else
		{
//			Dz1Thread_printf("@@@ New Entry = "); Dz1LzwDictData_dump(node, 0);
			if ((*errp = s_node->list->add(s_node->list, (Dz1LzwDictWord *)node)).code) ERR_OUT(errp);
			else if ((*errp = dict->codes->add(dict->codes, (Dz1LzwDictCode *)node)).code) ERR_OUT(errp);
			else if ((*errp = dict->arr->add(dict->arr, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Dz1LzwDictData_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error Dz1LzwDictionary_appendWord(Dz1LzwDictionary *dict, u8_t *w, u32_t size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (size > 1)
	{
		Dz1LzwDictSizeNode *s_node = _getSizeNode(size, dict->sizes, errp);
		if ((*errp = _appendWord(dict, s_node, w, size)).code) ERR_OUT(errp);
	}
	return err;
}

static void Dz1LzwDictionar_init(Dz1LzwDictionary *p, u32_t code_size, bool_t table_flush)
{
	p->code_bits = code_size;
	p->alloc_code = 1 << p->code_bits;
	p->base_code_max = 1 << p->code_bits;
	p->curr_code_max = 1 << (p->code_bits + 1);

	if (table_flush)
	{
		Dz1LzwDictCodeList_delAndSetNull(&p->codes);
		p->codes = Dz1LzwDictCodeList_new(NULL);

		Dz1LzwDictSizeTable_delAndSetNull(&p->sizes);
		p->sizes = Dz1LzwDictSizeTable_new(NULL);

		Dz1LzwDictDataArray_delAndSetNull(&p->arr);
		p->arr = Dz1LzwDictDataArray_new(NULL);
	}
}

static u8_t *_work_buffer_alloc(u32_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	u32_t sz = size >= 1024 * 1024 ? (1024 * 1024) : size;
	u8_t *ret = (u8_t *)Dz1Malloc(sz, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

Dz1Error Dz1LzwCompress(Dz1LzwCompStream *dst, u8_t *data, size_t size, u32_t code_size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u8_t *w = _work_buffer_alloc((u32_t)size, errp);
	Dz1LzwDictionary *dict = NULL;
	if (w == NULL) ERR_OUT(errp);
	else
	{
		u8_t *wp = w;
		u8_t *cp = data;
		u32_t w_code, code;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)w);
		if ((dict = Dz1LzwDictionary_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1LzwDictionary_delAndSetNull, (void *)&dict);

			Dz1LzwDictionar_init(dict, code_size, FALSE);

			while(size)
			{
				*wp = *cp;
				// if ((w + c) exists in th dictionary)
				if ((code = Dz1LzwDictionary_searchWord(dict, w, (u32_t)(wp - w + 1))) != (u32_t)-1)
				{
					wp++; // w = w + c;
				}
				else
				{
					Dz1LzwDictionary_appendWord(dict, w, (u32_t)(wp - w + 1));	// add (w + c) to the dictionary
					w_code = Dz1LzwDictionary_searchWord(dict, w, (u32_t)(wp - w));
					Dz1LzwCompStream_putCode(dst, w_code, dict->code_bits); // add the dictionary code for w to output
					wp = w;
					*wp++ = *cp;
				}
				cp++; size--;
				if (dict->alloc_code >= dict->curr_code_max)
				{
					dict->code_bits++;
					dict->curr_code_max = 1 << (dict->code_bits + 1);
				}
			}
			w_code = Dz1LzwDictionary_searchWord(dict, w, (u32_t)(wp - w));
			Dz1LzwCompStream_putCode(dst, w_code, dict->code_bits);

	//		Dz1Thread_printf("@@@ Dictionary = "); Dz1LzwDictionary_dump(dict, 0);

			pthread_cleanup_pop(1); // (Dz1LzwDictionary_delAndSetNull, (void *)&dict);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)w);
	}
	Dz1LzwCompStream_flushOut(dst);
	return err;
}

typedef struct Dz1LzwCompressedStream
{
	u8_t *next_read_byte;
	u32_t byte_remains;

	u32_t bb;
	u32_t bb_remain;
} Dz1LzwCompressedStream;

static u32_t Dz1LzwCompressedStream_readCode(Dz1LzwCompressedStream *src, u32_t bits_size)
{
	u32_t v, ret, work_bits = bits_size + 1;
	while(work_bits > src->bb_remain)
	{
		if (src->byte_remains == 0) return -1;

		v = (u32_t)((*src->next_read_byte++) & 0xFF);
		src->byte_remains--;

		v <<= src->bb_remain;
		src->bb |= v;
		src->bb_remain += 8;
	}

	ret = src->bb & ((1 << work_bits) - 1);
	src->bb >>= work_bits;
	src->bb_remain -= work_bits;

	Dz1Thread_printf("@@@ code = %08X (%u)\n", ret, work_bits);
	return ret;
}

//Dz1Error Dz1LzwDecompress(Dz1LzwDecompStream *dst, u32_t *codes, size_t size, u32_t code_size)
Dz1Error Dz1LzwDecompress(Dz1LzwDecompStream *dst, u8_t *_src, size_t size, u32_t code_size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1LzwCompressedStream src = { _src, (u32_t)size, 0, 0 };
	Dz1LzwDictionary *dict = Dz1LzwDictionary_new(errp);
	if (dict == NULL) ERR_OUT(errp);
	else
	{
		u8_t *entry = NULL;
		u32_t entry_size = 0;

		pthread_cleanup_push(Dz1LzwDictionary_delAndSetNull, (void *)&dict);

		Dz1LzwDictionar_init(dict, code_size, FALSE);

		if ((entry = _work_buffer_alloc((u32_t)size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u8_t *w = NULL;
			u32_t w_size = 0;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)entry);

			if ((w = _work_buffer_alloc((u32_t)size, errp)) == NULL) ERR_OUT(errp);
			else
			{
				u32_t k;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)w);

				if ((k = Dz1LzwCompressedStream_readCode(&src, dict->code_bits)) == -1) ERR_SET_OUT(errp, EPIPE);
				else
				{
					Dz1LzwDictionary_searchCode(dict, k, entry, &entry_size);	// dictionary entry for k
					Dz1LzwOutStream_putData(dst, entry, entry_size);			// output entry
					memcpy(w, entry, (w_size = entry_size));					// w = entry
					// k++; size--;
					while((k = Dz1LzwCompressedStream_readCode(&src, dict->code_bits)) != -1)
					{	// if (index k exists in dictionary)
						if (Dz1LzwDictionary_searchCode(dict, k, entry, &entry_size) == TRUE)
						{	// entry = dictionary entry for k
						}
						else if (k == dict->alloc_code)
						{	// entry = w + w[0]
							memcpy(entry, w, (entry_size = w_size));
							entry[entry_size++] = w[0];
						}
						else
						{
							Dz1Thread_printf("K = %08X, Alloc Code = %08X\n", k, dict->alloc_code);
							ERR_SET_OUT(errp, EFAULT);
							break;
						}
						Dz1LzwOutStream_putData(dst, entry, entry_size);		// output entry
						w[w_size++] = entry[0]; 
						Dz1LzwDictionary_appendWord(dict, w, w_size);			// add w + entry[0] to the dictionary
						memcpy(w, entry, (w_size = entry_size));				// w = entry

						if (dict->alloc_code + 1 >= dict->curr_code_max)
						{
							dict->code_bits++;
							dict->curr_code_max = 1 << (dict->code_bits + 1);
						}
					}
				}
				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)w);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)entry);
		}
		pthread_cleanup_pop(1); // (Dz1LzwDictionary_delAndSetNull, (void *)&dict);
	}
	return err;
}
