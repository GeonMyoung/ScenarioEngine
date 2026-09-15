#include "dz1_storage_io.h"

typedef struct Dz1StoragePos
{
	u32_t					 entry;			// open 당시 시작 index
	u32_t					 curr;			// 현재 index
	u16_t					 offset;		// 현재 position

	Dz1Storage				*storage;		// Position이 사라질 때 Data를 Sync하기 위해 필요

	Dz1StorageFrag			 frag;			// 현재 Load된 Frag
	bool_t					 dirty;			// 현재 Load된 Frag의 변경 여부

} Dz1StoragePos;							// with api dump, clone

static Dz1StoragePos *Dz1StoragePos_new(u32_t entry, void *storage, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1StoragePos *__internal_ret = (Dz1StoragePos *)Dz1Calloc(sizeof(Dz1StoragePos), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		__internal_ret->entry = entry;
		__internal_ret->curr = entry;
		__internal_ret->offset = 0;
		__internal_ret->storage = storage;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

static void Dz1StoragePos_del(Dz1StoragePos *p)
{
	if (p == NULL) return;
	if (p->dirty)
	{
		Dz1Storage *sto = p->storage;
		Dz1StorageFrag *frag = &p->frag;
		Dz1StorageFrag_save(sto->fp, p->curr, frag);
	}
	Dz1Free(p);
}

static void Dz1StoragePos_delAndSetNull(void *pptr)
{
	Dz1StoragePos **p = (Dz1StoragePos **)pptr;
	Dz1StoragePos_del(*p); *p = NULL;
}

static __inline__ void Dz1StoragePos_dump(Dz1StoragePos *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "entry = "); Dz1u32_dump(&p->entry, tab);

	Dz1Thread_tprintf(tab, "curr = "); Dz1u32_dump(&p->curr, tab);

	Dz1Thread_tprintf(tab, "offset = "); Dz1u16_dump(&p->offset, tab);

	if (p->storage == NULL) Dz1Thread_tprintf(tab, "storage = NULL\n");
	else Dz1Thread_tprintf(tab, "storage = %p\n", p->storage);

	Dz1Thread_tprintf(--tab, "}\n");
}

typedef enum ProcEmptyFragResult
{
	ProcEmptyFragResult_continue,
	ProcEmptyFragResult_break,
	ProcEmptyFragResult_fail
} ProcEmptyFragResult;

///////////////////////////////////////////////////////////////////////////////
// Read
static ProcEmptyFragResult _read_empty_frag(Dz1Storage *p, Dz1StoragePos *pos, Dz1StorageFrag *frag, ssize_t read_cnt, Dz1Error *err)
{
	ProcEmptyFragResult ret = ProcEmptyFragResult_fail;

	DZ1_ERROR_SAFE_PTR(errp, err);

	if (frag->next_idx != 0)
	{	// 다음 FRAG가 있음
		u32_t tmp_idx = frag->next_idx;
		if ((*errp = Dz1StorageFrag_load(p->fp, tmp_idx, frag)).code) ERR_OUT(errp);
		else
		{
			pos->curr = tmp_idx;
			pos->offset = 0;
			ret = ProcEmptyFragResult_continue;
		}
	}
	else if (read_cnt == 0)	// 다음 FRAG가 없는데...
	{	// 읽은게 하나도 없음
		Dz1Error_set(errp, EPIPE);
		ret = ProcEmptyFragResult_fail;
	}
	else ret = ProcEmptyFragResult_break;	// 뭐라도 조금 읽었음 -> 정상 종료
	return ret;
}

//typedef ssize_t (*Dz1StreamReadF)	(void *storage, u32_t stream_id, u8_t *dst_buf, size_t buf_size, Dz1Error *err);
static ssize_t _stream_io_read		(void *storage, u64_t stream_id, u8_t *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	Dz1Storage *p = (Dz1Storage *)storage;
	Dz1StoragePos *pos = (Dz1StoragePos *)stream_id;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL || buf == NULL || size == 0) ERR_SETOUT_RET(errp, EINVAL, -1);
	else if (pos == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
	else
	{
		Dz1StorageFrag *frag = &pos->frag;

		u8_t *cp = NULL;
		u8_t *dp = buf;
		while(size)
		{
//			Dz1Thread_printf("POS= <<%u - %u - %u>> : %u\n", frag->prev_idx, pos->curr, frag->next_idx, pos->offset);

			cp = &frag->data[pos->offset];	// 대상 포인터 지정
			if (frag->chunk_size == 0xFFFF || frag->chunk_size == 0)
			{	// 비어있는 FRAG
				switch(_read_empty_frag(p, pos, frag, ret, errp))
				{
				case ProcEmptyFragResult_continue: continue; break;
				case ProcEmptyFragResult_break: size = 0; break;
				case ProcEmptyFragResult_fail: size = 0; ret = -1; break;
				}
			}
			else
			{	// 데이터가 있는 FRAG
				u32_t data_size = frag->chunk_size - pos->offset;	// 잔존 Data수
				if (data_size == 0)
				{	// 읽어갈 데이터가 하나도 없음 == 비어있는 FRAG
					switch(_read_empty_frag(p, pos, frag, ret, errp))
					{
					case ProcEmptyFragResult_continue: continue; break;
					case ProcEmptyFragResult_break: size = 0; break;
					case ProcEmptyFragResult_fail: size = 0; ret = -1; break;
					}
				}
				else
				{	// 읽어갈 데이터가 있음
					u32_t copy_size = size < data_size ? (u32_t)size : data_size;	// 실제로 복사할 수 계산
					memcpy(dp, cp, copy_size);
					cp += copy_size;
					dp += copy_size;

					size -= copy_size;
					ret += copy_size;
					pos->offset += copy_size;
				}
			}
		}
	}
	return ret;
}
// Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// write
//typedef ssize_t (*Dz1StreamWriteF)	(void *storage, u32_t stream_id, u8_t *out_data, size_t size, Dz1Error *err);
static ssize_t _stream_io_write			(void *storage, u64_t stream_id, u8_t *data, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *p = (Dz1Storage *)storage;
	Dz1StoragePos *pos = (Dz1StoragePos *)stream_id;
	if (p == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (pos == NULL) ERR_SETOUT_RET(errp, EFAULT, -1);
	else
	{
		Dz1StorageFrag *frag = &pos->frag;

		u32_t space_size;
		u8_t *cp;
		while(size)
		{
//			Dz1Thread_printf("POS= <<%u - %u - %u>> : %u\n", frag->prev_idx, pos->curr, frag->next_idx, pos->offset);
			cp = &frag->data[pos->offset];
			space_size = DZ1_STORAGE_FRAG_DATA_SIZE - pos->offset;
			if (space_size == 0)
			{
				u32_t tmp_idx = frag->next_idx;

				if (frag->chunk_size != DZ1_STORAGE_FRAG_DATA_SIZE)
				{
					frag->chunk_size = DZ1_STORAGE_FRAG_DATA_SIZE;
					pos->dirty = TRUE;
				}

				if (tmp_idx != 0)
				{
					if (pos->dirty)
					{
						Dz1StorageFrag_save(p->fp, pos->curr, frag);
						pos->dirty = FALSE;
					}

					Dz1StorageFrag_load(p->fp, tmp_idx, frag);
					if (frag->prev_idx != pos->curr)
					{
						frag->prev_idx = pos->curr;
						pos->dirty = TRUE;
					}
					pos->curr = tmp_idx;
					pos->offset = 0;
					continue;
				}
				else if ((tmp_idx = Dz1Storage_alloc(p, errp)) == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT_RET(errp, -1);
				else
				{
					frag->next_idx = tmp_idx;
					Dz1StorageFrag_save(p->fp, pos->curr, frag);

					Dz1StorageFrag_load(p->fp, tmp_idx, frag);
					frag->prev_idx = pos->curr;
					pos->dirty = TRUE;

					pos->curr = tmp_idx;
					pos->offset = 0;
					continue;
				}
			}
			else
			{
				u32_t copy_size = size < space_size ? (u32_t)size : space_size;
				memcpy(cp, data, copy_size);
				data += copy_size;
				size -= copy_size;
				ret += copy_size;
				pos->offset += copy_size; frag->chunk_size = pos->offset;
				pos->dirty = TRUE;
			}
		}
	}
	return ret;
}
// write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Seek
static ProcEmptyFragResult _backward_empty_proc(Dz1Storage *p, Dz1StoragePos *pos, Dz1StorageFrag *frag, s64_t diff, Dz1Error *err)
{
	ProcEmptyFragResult ret = ProcEmptyFragResult_fail;

	DZ1_ERROR_SAFE_PTR(errp, err);

	u32_t tmp_idx = frag->prev_idx;
	if (tmp_idx != 0)
	{	// 이전 FRAG가 있음
		if ((*errp = Dz1StorageFrag_loadInfo(p->fp, tmp_idx, frag)).code) ERR_OUT(errp);	// 못읽으면 꽝
		else
		{	// 위치 조정
			pos->curr = tmp_idx;
			pos->offset = frag->chunk_size;
			ret = ProcEmptyFragResult_continue;
		}
	}
	else if (diff > 0)
		ERR_SET_OUT(errp, EPIPE);			// 너무 많이 이동 -> 꽝
	else ret = ProcEmptyFragResult_break;	// 적절히 이동 -> OK
	return ret;
}

typedef struct StoragePosRestoreArg
{
	Dz1StoragePos *dst;
	u32_t backup_curr;
	u16_t backup_offset;
} StoragePosRestoreArg;

static void storagePosRestore(void *ptr)
{
	StoragePosRestoreArg *arg = (StoragePosRestoreArg *)ptr;
	Dz1StoragePos *dst = arg->dst;
	dst->curr = arg->backup_curr;
	dst->offset = arg->backup_offset;
}

static Dz1Error _stream_io_seek_backward(Dz1Storage *p, Dz1StoragePos *pos, s64_t diff, int mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StorageFrag *frag = &pos->frag;
	StoragePosRestoreArg arg = { pos, pos->curr, pos->offset };

	if (diff < 0) ERR_SET_OUT_RET(errp, EFAULT, err);

	pthread_cleanup_push(storagePosRestore, (void *)&arg);
	while(diff)
	{
		if (frag->chunk_size == 0xFFFF || frag->chunk_size == 0)
		{	// 비어있는 FRAG
			switch(_backward_empty_proc(p, pos, frag, diff, errp))
			{
			case ProcEmptyFragResult_continue: continue; break;
			case ProcEmptyFragResult_break: 
			case ProcEmptyFragResult_fail: diff = 0; break;
			}
		}
		else
		{	// 비어있지 않은 FRAG
			s64_t data_size;
			if ((data_size = pos->offset) == 0)		// 이동 할 남은 거리가 없음
			{	// 결국 비어있는 FRAG
				switch(_backward_empty_proc(p, pos, frag, diff, errp))
				{
				case ProcEmptyFragResult_continue: continue; break;
				case ProcEmptyFragResult_break: 
				case ProcEmptyFragResult_fail: diff = 0; break;
				}
			}
			else
			{
				s64_t move_size = diff < data_size ? diff : data_size;	// 실제 이동 거리 계산
				pos->offset -= (u16_t)(move_size & 0xFFFF);
				diff -= move_size;
			}
		}
	}
	pthread_cleanup_pop(errp->code); // (storagePosRestore, (void *)&arg);

	if ((*errp = Dz1StorageFrag_load(p->fp, pos->curr, frag)).code) ERR_OUT(errp);

	return err;
}

static ProcEmptyFragResult _forward_empty_proc(Dz1Storage *p, Dz1StoragePos *pos, Dz1StorageFrag *frag, s64_t diff, Dz1Error *err)
{
	ProcEmptyFragResult ret = ProcEmptyFragResult_fail;

	DZ1_ERROR_SAFE_PTR(errp, err);

	u32_t tmp_idx = frag->next_idx;
	if (tmp_idx != 0)
	{
		if ((*errp = Dz1StorageFrag_loadInfo(p->fp, tmp_idx, frag)).code) ERR_OUT(errp);
		else
		{
			pos->curr = tmp_idx;
			pos->offset = 0;
			ret = ProcEmptyFragResult_continue;
		}
	}
	else if (diff > 0) ERR_SET_OUT(errp, EPIPE);
	else ret = ProcEmptyFragResult_break;
	return ret;
}

static Dz1Error _stream_io_seek_forward(Dz1Storage *p, Dz1StoragePos *pos, s64_t diff, int mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StorageFrag *frag = &pos->frag;

	StoragePosRestoreArg arg = { pos, pos->curr, pos->offset };

	if (diff < 0) ERR_SET_OUT(errp, EFAULT);

	pthread_cleanup_push(storagePosRestore, (void *)&arg);
	while(diff > 0)
	{
		if (frag->chunk_size == 0xFFFF || frag->chunk_size == 0)
		{
			switch(_forward_empty_proc(p, pos, frag, diff, errp))
			{
			case ProcEmptyFragResult_continue: continue; break;
			case ProcEmptyFragResult_break: 
			case ProcEmptyFragResult_fail: diff = 0; break;
			}
		}
		else
		{
			s64_t data_size;
			if ((data_size = frag->chunk_size - pos->offset) == 0)
			{
				switch(_forward_empty_proc(p, pos, frag, diff, errp))
				{
				case ProcEmptyFragResult_continue: continue; break;
				case ProcEmptyFragResult_break: 
				case ProcEmptyFragResult_fail: diff = 0; break;
				}
			}
			else
			{
				s64_t move_size = diff < data_size ? diff : data_size;
				pos->offset += (u16_t)(move_size & 0xFFFF);
				diff -= move_size;
			}
		}
	}
	pthread_cleanup_pop(errp->code); // (storagePosRestore, (void *)&arg);

	if ((*errp = Dz1StorageFrag_load(p->fp, pos->curr, frag)).code) ERR_OUT(errp);

	return err;
}

//typedef Dz1Error (*Dz1StreamSeekF)	(void *storage, u32_t stream_id, s64_t diff, int mode);
static Dz1Error _stream_io_seek			(void *storage, u64_t stream_id, s64_t diff, int mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t tmp_idx;
	Dz1Storage *p = (Dz1Storage *)storage;
	Dz1StoragePos *pos = (Dz1StoragePos *)stream_id;
	if (p == NULL || pos == NULL) ERR_SET_OUT(errp, EINVAL);
	if (pos == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1StorageFrag *frag = &pos->frag;
		switch(mode)
		{
		case SEEK_SET:
			if ((*errp = Dz1StorageFrag_loadInfo(p->fp, pos->entry, frag)).code) ERR_OUT(errp);
			else
			{
				pos->curr = pos->entry;
				pos->offset = 0;
				if ((*errp = _stream_io_seek_forward(p, pos, diff, mode)).code) ERR_OUT(errp);
			}
			break;
		case SEEK_CUR:
			if (diff < 0)
			{
				if ((*errp = _stream_io_seek_backward(p, pos, -diff, mode)).code) ERR_OUT(errp);
			}
			else
			{
				if ((*errp = _stream_io_seek_forward(p, pos, diff, mode)).code) ERR_OUT(errp);
			}
			break;
		case SEEK_END:
			while(frag->next_idx != 0)
			{
				tmp_idx = frag->next_idx;
				if ((*errp = Dz1StorageFrag_loadInfo(p->fp, tmp_idx, frag)).code) ERR_OUT_RET(errp, err);
				else
				{
					pos->curr = tmp_idx;
					pos->offset = frag->chunk_size;
				}
			}
			if ((*errp = _stream_io_seek_backward(p, pos, diff, mode)).code) ERR_OUT(errp);
			break;
		}
	}
	return err;
}
// Seek
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// EOF
//typedef bool_t (*Dz1StreamIsEofF)	(void *storage, u32_t stream_id);
static bool_t _stream_io_isEOF		(void *storage, u64_t stream_id)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Storage *p = (Dz1Storage *)storage;
	Dz1StoragePos *pos = (Dz1StoragePos *)stream_id;
	if (p == NULL || pos == NULL) ERR_SETOUT_RET(errp, EINVAL, TRUE);
	else
	{
		Dz1StorageFrag *frag = &pos->frag;
		if (frag->next_idx != 0) return FALSE;
		else if (pos->offset < frag->chunk_size) return FALSE;
		else return TRUE;
	}
}
// EOF
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Tell
//typedef s64_t (*Dz1StreamTellF)	(void *storage, u32_t stream_id, Dz1Error *err);
static s64_t _stream_io_tell		(void *storage, u64_t stream_id, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *p = (Dz1Storage *)storage;
	Dz1StoragePos *pos = (Dz1StoragePos *)stream_id;
	if (p == NULL || pos == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u32_t i;
		s64_t ret = 0;
		Dz1StorageFrag frag;
		for (i = pos->entry; i != 0 && i != pos->curr; i = frag.next_idx)
		{
			if((*errp = Dz1StorageFrag_loadInfo(p->fp, pos->entry, &frag)).code) ERR_OUT_RET(errp, -1);
			else ret += frag.chunk_size;
		}
		ret += pos->offset;
		return ret;
	}
}
// Tell
///////////////////////////////////////////////////////////////////////////////

static void _seek_last(Dz1StoragePos *pos)
{
	Dz1StorageFrag *frag = &pos->frag;
	Dz1Storage *p = pos->storage;
	u32_t tmp_idx;
	while(frag->next_idx != 0)
	{
		tmp_idx = frag->next_idx;
		Dz1StorageFrag_load(p->fp, tmp_idx, frag);
		pos->curr = tmp_idx;
		pos->offset = frag->chunk_size;
	}
}

static Dz1Error _truncate(Dz1Storage *h, u32_t entry, Dz1StorageFrag *frag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t free_idx = frag->next_idx;
	if (free_idx != 0)
	{
		Dz1StorageFrag temp;

		frag->next_idx = 0;
		if ((*errp = Dz1StorageFrag_saveInfo(h->fp, entry, frag)).code) ERR_OUT(errp);

		else if ((*errp = Dz1StorageFrag_loadInfo(h->fp, free_idx, &temp)).code) ERR_OUT(errp);
		else
		{
			temp.prev_idx = 0;
			Dz1StorageFrag_saveInfo(h->fp, free_idx, &temp);
			Dz1Storage_free(h, free_idx);
		}
	}
	return err;
}

/*
typedef struct Dz1Stream
{
	void				*storage;
	bool_t				 storage_isRef;
	Dz1DelFunc			 storage_del;
	Dz1DumpFunc			 storage_dump;

	// Cursor
	u32_t				 stream_id;
	Dz1StreamReleaseF	 stream_release;

	Dz1StreamReadF		 read;
	Dz1StreamWriteF		 write;
	Dz1StreamSeekF		 seek;
	Dz1StreamTellF		 tell;
	Dz1StreamIsEofF		 is_eof;
	Dz1StreamDrainF		 drain;
} Dz1Stream;
*/

typedef enum StorageOpenPostAction
{
	StorageOpenPostAction_none,
	StorageOpenPostAction_truncate,
	StorageOpenPostAction_move_last
} StorageOpenPostAction;

static void Dz1StoragePos_release(void *storage, u64_t stream_id)
{
	// Dz1Storage *p = (Dz1Storage *)storage;
	Dz1StoragePos *pos = (Dz1StoragePos *)stream_id;
	Dz1StoragePos_del(pos);
}

static Dz1Error _open_by_mode(Dz1Stream *ret, u32_t open_idx, Dz1StreamFileMode mode, Dz1Storage *h)
{
	StorageOpenPostAction post_fix = StorageOpenPostAction_none;
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StoragePos *pos = Dz1StoragePos_new(open_idx, h, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1StorageFrag *frag = &pos->frag;
		pthread_cleanup_push(Dz1StoragePos_delAndSetNull, (void *)&ret);
		ret->stream_id = (u64_t)pos;
		ret->stream_release = Dz1StoragePos_release;

		switch(mode)
		{
 		case Dz1StreamFileMode_RD:			// 읽기			데이터 유지
			ret->read = _stream_io_read;
			ret->write = NULL;
			post_fix = StorageOpenPostAction_none;
			break;
		case Dz1StreamFileMode_WR:			//		쓰기	데이터 삭제
			ret->read = NULL;
			ret->write = _stream_io_write;
			post_fix = StorageOpenPostAction_truncate;
			break;
		case Dz1StreamFileMode_WRO:			//		쓰기	데이터 유지		덮어쓰기
			ret->read = NULL;
			ret->write = _stream_io_write;
			post_fix = StorageOpenPostAction_none;
			break;
		case Dz1StreamFileMode_WRA:			//		쓰기	데이터 유지		추가하기
			ret->read = NULL;
			ret->write = _stream_io_write;
			post_fix = StorageOpenPostAction_move_last;
			break;
		case Dz1StreamFileMode_RW:			// 읽고	쓰기	데이터 삭제
			ret->read = _stream_io_read;
			ret->write = _stream_io_write;
			post_fix = StorageOpenPostAction_truncate;
			break;
		case Dz1StreamFileMode_RWO:			// 읽기	쓰기	데이터 유지		덮어쓰기
			ret->read = _stream_io_read;
			ret->write = _stream_io_write;
			post_fix = StorageOpenPostAction_none;
			break;
		case Dz1StreamFileMode_RWA:			//		쓰기	데이터 유지		추가하기
			ret->read = NULL;
			ret->write = _stream_io_write;
			post_fix = StorageOpenPostAction_move_last;
			break;
		default:
			return err;
		}
		ret->seek = _stream_io_seek;
		ret->tell = _stream_io_tell;
		ret->is_eof = _stream_io_isEOF;

		if ((*errp = Dz1StorageFrag_load(h->fp, pos->entry, frag)).code) ERR_OUT(errp);
		else if (frag->prev_idx != 0) ERR_SET_OUT(errp, EINVAL);
		else
		{
			switch(post_fix)
			{
			default:
			case StorageOpenPostAction_none:
				break;
			case StorageOpenPostAction_truncate:
				_truncate(h, pos->curr, frag);
				break;
			case StorageOpenPostAction_move_last:
				_seek_last(pos);
				break;
			}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1StoragePos_delAndSetNull, (void *)&ret);
	}
	return err;
}

Dz1Stream *Dz1StorageStream_open(Dz1StorageHandle *ptr, u32_t open_idx, Dz1StreamFileMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Stream *ret = NULL;
	Dz1Storage *p = (Dz1Storage *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Stream *)Dz1Calloc(sizeof(Dz1Stream), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ret);
		ret->storage = ptr;
		ret->storage_isRef = TRUE;
		ret->storage_del = NULL;
		ret->storage_dump = (Dz1DumpFunc)Dz1StorageHandle_dump;

		if ((*errp = _open_by_mode(ret, open_idx, mode, p)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Stream_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

