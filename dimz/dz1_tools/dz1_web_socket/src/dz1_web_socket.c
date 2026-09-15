#include "dz1_web_socket.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecCtx_generate
Dz1WebSockDecCtx *Dz1WebSockDecCtx_generate(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSockDecCtx *ret = Dz1WebSockDecCtx_new(Dz1WebSockDecState_fin_opcode, 1, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
// Dz1WebSockDecCtx_generate
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecFrameList_concatenate
static Dz1WebSockDecFrame *Dz1WebSockDecFrameList_concatenate(Dz1WebSockDecFrameList *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSockDecFrame *frame = NULL;
	if ((frame = src->extract(src, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1WebSockDecFrame *f;
		pthread_cleanup_push(Dz1WebSockDecFrame_delAndSetNull, (void *)&frame);
		while((f = src->extract(src, NULL)) != NULL)
		{
			pthread_cleanup_push(Dz1WebSockDecFrame_delAndSetNull, (void *)&f);

			if (Dz1ElasticBuf_move(frame->payload, f->payload, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1WebSockDecFrame_delAndSetNull, (void *)&f);
		}
		pthread_cleanup_pop(errp->code); // (Dz1WebSockDecFrame_delAndSetNull, (void *)&frame);
	}
	return frame;
}
// Dz1WebSockDecFrameList_concatenate
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1WebSockMsg_genFromFrames
static Dz1WebSockMsg *Dz1WebSockMsg_genFromFrames(Dz1WebSockDecFrameList *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSockMsg *ret = NULL;
	Dz1WebSockDecFrame *frame = NULL;
	if ((frame = Dz1WebSockDecFrameList_concatenate(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WebSockDecFrame_delAndSetNull, (void *)&frame);
		if ((ret = Dz1WebSockMsg_new(frame->op_code, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1WebSockMsg_delAndSetNull, (void *)&ret);
			if ((ret->payload = Dz1ElasticBuf_flattenAndPurge(frame->payload, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1WebSockMsg_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1WebSockDecFrame_delAndSetNull, (void *)&frame);
	}
	return ret;
}
// Dz1WebSockMsg_genFromFrames
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecCtx_decode
static Dz1WebSockDecFrame *Dz1WebSockDecFrame_prepare(Dz1Error *errp)
{
	Dz1WebSockDecFrame *ret = NULL;
	if ((ret = Dz1WebSockDecFrame_new(FALSE, Dz1WebSockOpCode_unknown, 0, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->payload = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

static void _change_state(Dz1WebSockDecCtx *p, Dz1WebSockDecState state, u64_t initial_len)
{
	p->state = state;
	p->len_remain = initial_len;
	if (p->state == Dz1WebSockDecState_payload) p->mask_idx = 0;
}

bool_t Dz1WebSockDecCtx_decode(Dz1WebSockDecCtx *p, Dz1WebSockDecEnv *src, Dz1WebSockMsg **_ret, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSockDecFrame *wip = NULL;
	if (p == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->sp == NULL || src->size == 0) Dz1Error_set(errp, 0);
	else if ((wip = p->wip) == NULL && (wip = p->wip = Dz1WebSockDecFrame_prepare(errp)) == NULL) ERR_OUT(errp);
	else
	{
		u8_t small_len = 0;
		bool_t done = FALSE;
		while(errp->code == 0 && done == FALSE && src->size > 0)
		{
			switch(p->state)
			{
			case Dz1WebSockDecState_fin_opcode:
				wip->is_fin = *src->sp & 0x80 ? TRUE : FALSE;
				wip->op_code = (Dz1WebSockOpCode)(*src->sp & 0x0F);
				_change_state(p, Dz1WebSockDecState_mask_len0, 1);

				src->size--;
				src->sp++;

				break;
			case Dz1WebSockDecState_mask_len0:
				if ((*src->sp & 0x80) && (wip->mask = Dz1u32_new(0, errp)) == NULL) ERR_OUT(errp);
				else if ((small_len = (*src->sp & 0x7F)) == 128)	_change_state(p, Dz1WebSockDecState_ext_len8, 8);
				else if (small_len == 126)							_change_state(p, Dz1WebSockDecState_ext_len2, 2);
				else
				{
					wip->payload_len = (u64_t)small_len & 0x7F;
					if (wip->mask == NULL)							_change_state(p, Dz1WebSockDecState_payload, wip->payload_len);
					else											_change_state(p, Dz1WebSockDecState_mask, 4);
				}

				src->size--;
				src->sp++;

				break;
			case Dz1WebSockDecState_ext_len2:
				if (p->len_remain > 0)
				{
					wip->payload_len <<= 8;
					wip->payload_len |= ((u64_t)(*src->sp) & 0xFF);

					p->len_remain--;
					src->size--;
					src->sp++;
				}
				else if (wip->mask == NULL)							_change_state(p, Dz1WebSockDecState_payload, wip->payload_len);
				else												_change_state(p, Dz1WebSockDecState_mask, 4);
				break;
			case Dz1WebSockDecState_ext_len8:
				if (p->len_remain > 0)
				{
					wip->payload_len <<= 8;
					wip->payload_len |= ((u64_t)(*src->sp) & 0xFF);

					p->len_remain--;
					src->size--;
					src->sp++;
				}
				else if (wip->mask == NULL)							_change_state(p, Dz1WebSockDecState_payload, wip->payload_len);
				else												_change_state(p, Dz1WebSockDecState_mask, 4);
				break;
			case Dz1WebSockDecState_mask:
				if (p->len_remain > 0)
				{
					*wip->mask <<= 8;
					*wip->mask |= ((u32_t)(*src->sp) & 0xFF);

					p->len_remain--;
					src->size--;
					src->sp++;
				}
				else												_change_state(p, Dz1WebSockDecState_payload, wip->payload_len);
				break;
			case Dz1WebSockDecState_payload:
				if (p->len_remain > 0)
				{
					size_t push_size = p->len_remain < src->size ? (size_t)p->len_remain : src->size;
					if (wip->mask != NULL)
					{
						u8_t *mp = NULL;
						u32_t _mask = *wip->mask, i;
						u8_t mask[4] =
						{
							(u8_t)((_mask >> 24) & 0xFF), 
							(u8_t)((_mask >> 16) & 0xFF),
							(u8_t)((_mask >> 8) & 0xFF),
							(u8_t)((_mask >> 0) & 0xFF)
						};
						for (mp = src->sp, i = 0; i < push_size; i++, mp++, p->mask_idx = (p->mask_idx + 1) & 0x7 ) 
							*mp ^= mask[p->mask_idx]; // remove masking
					}

					if (_Dz1ElasticBuf_push(wip->payload, src->sp, push_size, errp) == FALSE) ERR_OUT(errp);
					else
					{
						p->len_remain -= push_size;
						src->sp += push_size;
						src->size -= push_size;
					}
				}

				if (p->len_remain == 0)
				{
					if ((*errp = p->wip_list->add(p->wip_list, p->wip)).code) ERR_OUT(errp);
					else
					{
						bool_t fin = wip->is_fin;
						p->wip = wip = NULL;
						_change_state(p, Dz1WebSockDecState_fin_opcode, 1);

						if (fin && (*_ret = Dz1WebSockMsg_genFromFrames(p->wip_list, errp)) == NULL) ERR_OUT(errp);
						else 
						{
							done = TRUE;
							Dz1Error_set(errp, 0);
						}
					}
				}
				else Dz1Error_set(errp, 0);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Dz1WebSockDecCtx_decode
///////////////////////////////////////////////////////////////////////////////
