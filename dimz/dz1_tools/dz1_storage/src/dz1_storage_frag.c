#include <dz1_stdio.h>
#include <dz1_thread_stdio.h>

#include "dz1_storage_frag.h"

#include <dz1_storage.h>

#ifdef UNIX_SYSTEM
typedef long filepos;
#define FSEEK			fseek
#define FTELL			ftell
#else
typedef s64_t filepos;
#define FSEEK			_fseeki64
#define FTELL			_ftelli64
#endif

static Dz1Error _move_pos(FILE *fp, u32_t idx)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	filepos pos = (filepos)DZ1_STORAGE_FRAG_SIZE * idx;
	//filepos curr = FTELL(fp);
//	Dz1Thread_printf("@@@ Move File Position %llu, Current Position = %llu, idx = %u\n", pos, curr, idx);
//	if (curr != pos && FSEEK(fp, pos, SEEK_SET) != 0) ERR_SET_OUT(errp, EFAULT);
	if (FSEEK(fp, pos, SEEK_SET) != 0) ERR_SET_OUT(errp, EFAULT);
	return err;
}

Dz1Error Dz1StorageSuperFrag_load(FILE *fp, Dz1StorageSuperFrag *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = _move_pos(fp, 0)).code) ERR_OUT(errp);
	else if (_read4Byte(fp, &dst->magic, errp) < 0) ERR_OUT(errp);
	else if (_read4Byte(fp, &dst->version, errp) < 0) ERR_OUT(errp);
	else if (_read4Byte(fp, &dst->space_start, errp) < 0) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1StorageSuperFrag_save(FILE *fp, Dz1StorageSuperFrag *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	size_t written = 0;
	ssize_t status = 0;
	if ((*errp = _move_pos(fp, 0)).code) ERR_OUT(errp);
	else
	{
		if ((status = _write4Byte(fp, src->magic, errp)) < 0) { ERR_OUT(errp); return err; } else written += status;
		if ((status = _write4Byte(fp, src->version, errp)) < 0) { ERR_OUT(errp); return err; } else written += status;
		if ((status = _write4Byte(fp, src->space_start, errp)) < 0) { ERR_OUT(errp); return err; } else written += status;

		if (written > DZ1_STORAGE_FRAG_SIZE) { ERR_SET_OUT(errp, EFAULT); return err; }
		else if (written < DZ1_STORAGE_FRAG_SIZE)
		{
			u8_t pad[4096 - 12] = { 0, };
			if ((status = _writeByte(fp, pad, DZ1_STORAGE_FRAG_SIZE - written, errp)) < 0) ERR_OUT(errp);
			else written += status;
		}
	}
	return err;
}

static Dz1Error _frag_load(FILE *fp, Dz1StorageFrag *dst, bool_t load_data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (0) { }
	else if (_read4Byte(fp, &dst->prev_idx, errp) < 0) { /* ERR_OUT(errp); */ }
	else if (_read4Byte(fp, &dst->next_idx, errp) < 0) ERR_OUT(errp);
	else if (_read2Byte(fp, &dst->chunk_size, errp) < 0) ERR_OUT(errp);
	else if (load_data)
	{
		if (_readByte(fp, dst->data, DZ1_STORAGE_FRAG_DATA_SIZE, errp) < 0) ERR_OUT(errp);
	}
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1Error _frag_save(FILE *fp, Dz1StorageFrag *src, bool_t save_data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (0) { }
	else if (_write4Byte(fp, src->prev_idx, errp) < 0) ERR_OUT(errp);
	else if (_write4Byte(fp, src->next_idx, errp) < 0) ERR_OUT(errp);
	else if (_write2Byte(fp, src->chunk_size, errp) < 0) ERR_OUT(errp);
	else if (save_data)
	{
		if (_writeByte(fp, src->data, DZ1_STORAGE_FRAG_DATA_SIZE, errp) < 0) ERR_OUT(errp);
	}
	else Dz1Error_set(errp, 0);
	fflush(fp);
	return err;
}

Dz1Error Dz1StorageFrag_load(FILE *fp, u32_t idx, Dz1StorageFrag *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = _move_pos(fp, idx)).code) ERR_OUT(errp);
	else if ((*errp = _frag_load(fp, dst, TRUE)).code) ERR_OUT(errp);
//	else Dz1Thread_printf("@@@ Load\n");
	return err;
}

Dz1Error Dz1StorageFrag_save(FILE *fp, u32_t idx, Dz1StorageFrag *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = _move_pos(fp, idx)).code) ERR_OUT(errp);
	else if ((*errp = _frag_save(fp, src, TRUE)).code) { /* ERR_OUT(errp); */ }
//	else Dz1Thread_printf("@@@ Save\n");
	return err;
}

Dz1Error Dz1StorageFrag_loadInfo(FILE *fp, u32_t idx, Dz1StorageFrag *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = _move_pos(fp, idx)).code) ERR_OUT(errp);
	else if ((*errp = _frag_load(fp, dst, FALSE)).code) { /* ERR_OUT(errp); */ }
//	else Dz1Thread_printf("@@@ Load Info\n");
	return err;
}

Dz1Error Dz1StorageFrag_saveInfo(FILE *fp, u32_t idx, Dz1StorageFrag *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (idx == 0)
	{
		Dz1Thread_printf("!!! Save Info on Super Block\n");
	}

	if ((*errp = _move_pos(fp, idx)).code) ERR_OUT(errp);
	else if ((*errp = _frag_save(fp, src, FALSE)).code) ERR_OUT(errp);
//	else Dz1Thread_printf("@@@ Save Info\n");
	return err;
}

Dz1Binary *Dz1StorageFrag_loadBin(FILE *fp, u32_t start_idx, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;
	u64_t size = 0;
	if ((*errp = Dz1StorageFrag_size(fp, start_idx, &size)).code) ERR_OUT(errp);
	else if ((ret = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, (u32_t)size, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1StorageFrag frag;
		u8_t *cp = ret->data;
		u32_t idx = start_idx;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
		do 
		{
			if ((*errp = Dz1StorageFrag_load(fp, idx, &frag)).code) ERR_OUT(errp);
			else
			{
				memcpy(cp, frag.data, frag.chunk_size);
				cp += frag.chunk_size;
				size -= frag.chunk_size;

				idx = frag.next_idx;
			}
		} while (errp->code == 0 && idx != DZ1_STORAGE_FRAG_IDX_NONE && size);
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1StorageFrag_size(FILE *fp, u32_t start_idx, u64_t *ret)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (fp == NULL || ret == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1StorageFrag frag;
		u32_t idx = start_idx;
		do 
		{
			if ((*errp = Dz1StorageFrag_load(fp, idx, &frag)).code) ERR_OUT(errp);
			else
			{
				(*ret) += frag.chunk_size;
				idx = frag.next_idx;
			}
		} while (errp->code == 0 && idx != DZ1_STORAGE_FRAG_IDX_NONE);
	}
	return err;
}

static u32_t _get_last_frag(FILE *fp, u32_t start_idx, Dz1StorageFrag *dst, Dz1Error *err)
{
	u32_t idx = start_idx;
	DZ1_ERROR_SAFE_PTR(errp, err);
	do 
	{
		if ((*errp = Dz1StorageFrag_loadInfo(fp, idx, dst)).code) { ERR_OUT(errp); return DZ1_STORAGE_FRAG_IDX_ERROR; }
		else if (dst->next_idx == 0) break;
		else idx = dst->next_idx;
	} while (1);
	return idx;
}

static Dz1Error _set_prev_of_frag(FILE *fp, u32_t dst_idx, u32_t prev_idx)
{
	Dz1StorageFrag frag;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1StorageFrag_loadInfo(fp, dst_idx, &frag)).code) ERR_OUT(errp);
	else
	{
		frag.prev_idx = prev_idx;
		if ((*errp = Dz1StorageFrag_saveInfo(fp, dst_idx, &frag)).code) ERR_OUT(errp);
	}
	return err;
}

static Dz1Error _set_next_of_frag(FILE *fp, u32_t dst_idx, u32_t next_idx)
{
	Dz1StorageFrag frag;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1StorageFrag_loadInfo(fp, dst_idx, &frag)).code) ERR_OUT(errp);
	else
	{
		frag.next_idx = next_idx;
		if ((*errp = Dz1StorageFrag_saveInfo(fp, dst_idx, &frag)).code) ERR_OUT(errp);
	}
	return err;
}

static Dz1Error _link_to_space(FILE *fp, u32_t new_space_start, u32_t *space_start, Dz1StorageFrag *pre_loaded_frag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t do_save = FALSE;

	// make sure first frag
	if (pre_loaded_frag->prev_idx != 0)
	{
		pre_loaded_frag->prev_idx = 0;
		do_save = TRUE;
	}

	if (pre_loaded_frag->next_idx == 0)
	{	// single block
		if ( *space_start != 0)
		{	// space exist
			pre_loaded_frag->next_idx = *space_start;
			do_save = TRUE;
			_set_prev_of_frag(fp, *space_start, new_space_start);
		}
		else
		{	// space not exist->nop
		}
	}
	else
	{	// multi block
		if ( *space_start != 0)
		{	// space exist
			Dz1StorageFrag frag;
			u32_t idx = pre_loaded_frag->next_idx;
			u32_t end_of_new_space = _get_last_frag(fp, idx, &frag, errp);
			_set_prev_of_frag(fp, *space_start, end_of_new_space);
			_set_next_of_frag(fp, end_of_new_space, *space_start);
		}
		else
		{	// space not exist->nop
		}
	}
	if (do_save) Dz1StorageFrag_saveInfo(fp, new_space_start, pre_loaded_frag);
	(*space_start) = new_space_start;

	return err;
}

u32_t Dz1StorageFrag_append(FILE *fp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t ret = DZ1_STORAGE_FRAG_IDX_ERROR;
	if (fp == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (FSEEK(fp, 0, SEEK_END) != 0) ERR_SET_OUT(errp, EFAULT);
		else
		{
			Dz1StorageFrag frag = { 0, 0, 0, { 0, } };
			filepos pos = FTELL(fp);
			u32_t idx = (u32_t)((pos / DZ1_STORAGE_FRAG_SIZE) & 0xFFFFFFFF);
			if ((*errp = Dz1StorageFrag_save(fp, idx, &frag)).code) ERR_OUT(errp);
			else ret = idx;
		}
	}
	return ret;
}

static Dz1Error Dz1StorageFrag_saveBufWithExpand(FILE *fp, u32_t prev_idx, Dz1StorageFrag *prev_frag, u8_t *src, size_t size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u8_t *cp = src;
	u32_t idx;
	Dz1StorageFrag frag;

	filepos pos = FTELL(fp);;
	FSEEK(fp, 0, SEEK_END);
	pos = FTELL(fp);
	idx = (u32_t)(pos / DZ1_STORAGE_FRAG_SIZE);

	if (pos % DZ1_STORAGE_FRAG_SIZE) Dz1Thread_printf("!!! Unit size mismatch\n");

	// 이전 Frag 처리
	prev_frag->next_idx = idx;
	Dz1StorageFrag_save(fp, prev_idx, prev_frag);

	while(size)
	{
		frag.prev_idx = prev_idx;

		frag.chunk_size = (u16_t)((size < DZ1_STORAGE_FRAG_DATA_SIZE ? size : DZ1_STORAGE_FRAG_DATA_SIZE) & 0xFFFF);
		memcpy(frag.data, cp, frag.chunk_size);
		cp += frag.chunk_size;
		size -= frag.chunk_size;

		if (size) frag.next_idx = idx + 1;
		else frag.next_idx = 0;

		Dz1StorageFrag_save(fp, idx, &frag);

		prev_idx = idx;
		idx++;
	}
	Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1StorageFrag_free(FILE *fp, u32_t free_idx, u32_t *space_start, Dz1StorageFrag *free_frag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t new_space_start = free_idx;
	if ((*errp = _link_to_space(fp, new_space_start, space_start, free_frag)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error Dz1StorageFrag_saveBufToSpace(FILE *fp, u32_t prev_idx, Dz1StorageFrag *prev_frag, u8_t *src, size_t size, u32_t *space_start)
{	// space_start != 0
	DZ1_ERROR_SAFE_VAR(errp, err);
	u8_t *cp = src;
	Dz1StorageFrag frag;
	u32_t idx = (*space_start);

	// 이전 Frag 처리
	prev_frag->next_idx = idx;
	Dz1StorageFrag_save(fp, prev_idx, prev_frag);

	while(size)
	{
		if ((*errp = Dz1StorageFrag_loadInfo(fp, idx, &frag)).code) ERR_OUT(errp);
		else
		{
			frag.prev_idx = prev_idx;
			prev_idx = idx;

			// copy data & modify pointer & size
			frag.chunk_size = (u16_t)((size < DZ1_STORAGE_FRAG_DATA_SIZE ? size : DZ1_STORAGE_FRAG_DATA_SIZE) & 0xFFFF);
			memcpy(frag.data, cp, frag.chunk_size);
			cp += frag.chunk_size;
			size -= frag.chunk_size;

			if (size)
			{	// 쓸것이 남음
				if (frag.next_idx == 0)
				{	// 공간 쫑남
					(*space_start) = 0;
					// 파일 확장하면서 쓰기모드로 진입
					Dz1StorageFrag_saveBufWithExpand(fp, idx, &frag, cp, size);
					// 루프 종료
					break;
				}
				else
				{	// 저장하고 다음 Frag로...
					Dz1StorageFrag_save(fp, idx, &frag);
					idx = frag.next_idx;
				}
			}
			else
			{	// 쓰기 끝 -> 남은공간 돌려주기
				if (frag.next_idx == 0)
				{	// 남은게 없음
					(*space_start) = 0;
					// 저장
					Dz1StorageFrag_save(fp, idx, &frag);
				}
				else
				{	// 남은게 있음
					u32_t new_space_start = frag.next_idx;

					// 끝 지정하고 저장
					frag.next_idx = 0;
					Dz1StorageFrag_save(fp, idx, &frag);

					(*space_start) = 0;
					// 빈공간의 시작을 기존 빈공간과 연결
					Dz1StorageFrag_loadInfo(fp, new_space_start, &frag);
					_link_to_space(fp, new_space_start, space_start, &frag);
				}
			}
		}
	}
	return err;
}

Dz1Error Dz1StorageFrag_saveBuf(FILE *fp, u32_t start_idx, u8_t *src, size_t size, u32_t *space_start)
{	// 오버라이트
	DZ1_ERROR_SAFE_VAR(errp, err);

	u8_t *cp = src;
	Dz1StorageFrag frag;
	u32_t idx = start_idx;

	while(errp->code == 0 && size)
	{	// 1. load and fill up frag
		if ((*errp = Dz1StorageFrag_loadInfo(fp, idx, &frag)).code)
		{
			ERR_OUT(errp);
		}
		else
		{
			frag.chunk_size = (u16_t)((size < DZ1_STORAGE_FRAG_DATA_SIZE ? size : DZ1_STORAGE_FRAG_DATA_SIZE) & 0xFFFF);
			memcpy(frag.data, cp, frag.chunk_size);
			cp += frag.chunk_size;
			size -= frag.chunk_size;
		}

		// 2. check remain size
		if (size)
		{	// 쓸게 남은 경우
			if (frag.next_idx == 0)
			{	// 덮어쓰는 공간이 끝남
				if ( *space_start != DZ1_STORAGE_FRAG_IDX_NONE)
				{	// 빈공간 있음->빈공간에 쓰기 모드로 진입
					Dz1StorageFrag_saveBufToSpace(fp, idx, &frag, cp, size, space_start);
				}
				else
				{	// 빈공간 없음->파일 확장하며 쓰기
					Dz1StorageFrag_saveBufWithExpand(fp, idx, &frag, cp, size);
				}
				// 루프 중지
				break;
			}
			else
			{	// 변경사항 저장, 다음 idx값 설정
				Dz1StorageFrag_save(fp, idx, &frag);
				idx = frag.next_idx;
			}
		}
		else
		{	// 쓰기 끝 -> 남은 공간 돌려주기
			if (frag.next_idx == 0)
			{	// 돌려줄 공간이 없음
				// 3. save filled frag
				Dz1StorageFrag_save(fp, idx, &frag);
			}
			else
			{	// 돌려줄 공간이 있음
				u32_t new_space_start = frag.next_idx;
				// 연결 공간의 끝 지정
				frag.next_idx = 0;
				Dz1StorageFrag_save(fp, idx, &frag);

				Dz1StorageFrag_loadInfo(fp, new_space_start, &frag);
				_link_to_space(fp, new_space_start, space_start, &frag);
			}
			break;
		}
	}
	return err;
}

