#include "stdafx.h"
#include <dz1_malloc.h>
#include "Dz1MfcTreeCtrlFolder.h"

///////////////////////////////////////////////////////////////////////////////
// Utility
static void _trim_last_sep(Dz1Str str)
{	// 문자열의 마지막 글자가 DIR_SEPRATOR면 지운다.
	if (str != NULL && str[0] != 0)
	{
		Dz1Str cp = &str[Dz1STRLEN(str) - 1];
		if (*cp == DIR_SEP) *cp = 0;
	}
}

static int _dir_name_cmp(Dz1Str a, Dz1Str b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL && b != NULL) ret = -1;
	else if (a != NULL && b == NULL) ret = 1;
	else ret = Dz1StrCmpLogical(a, b);
	return ret;
}

static int _dir_entry_cmp(Dz1DirEntry *a, Dz1DirEntry *b)
{	// Windows Name Compare
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else return _dir_name_cmp(a->name, b->name);
}

static bool_t _is_local_path(Dz1Str full_path, Dz1Str ret_root_name, Dz1Str *ret_path_start)
{	// 하드 드라이브 하위 경로인가? = D:, D:\aaa
	if ((full_path[0] >= _T('A') && full_path[0] <= 'Z') ||
		(full_path[0] >= _T('a') && full_path[0] <= 'z'))
	{
		if (full_path[1] == _T(':'))
		{
			Dz1STRNCPY(ret_root_name, full_path, 2);
// 			{
// 				ret_root_name[2] = DIR_SEP;
// 				ret_root_name[3] = 0;
// 			}

			Dz1Str start_ptr = Dz1STRCHR(full_path, DIR_SEP);
			if (start_ptr != NULL) start_ptr++;	// 처음 만나는 SEP의 다음 글자 또는 NULL
			(*ret_path_start) = start_ptr;

			return TRUE;
		}
	}
	return FALSE;
}

static bool_t _is_network_path(Dz1Str full_path, Dz1Str ret_root_name, Dz1Str *ret_path_start)
{	// 공유폴더 하위 경로인가?
	if (full_path[0] == DIR_SEP && full_path[1] == DIR_SEP)
	{	// 처음 2개가 '\'이다
		TCHAR *cp = &full_path[2];
		if ((cp = Dz1STRCHR(cp, DIR_SEP)) != NULL)
		{	// 세번째 '\'가 있음
			cp++;
			if (*cp != 0)
			{	// 이후 경로가 있으면...
				if ((cp = Dz1STRCHR(cp, DIR_SEP)) != NULL)
				{	// 네번째 '\'가 있음
					Dz1STRNCPY(ret_root_name, full_path, (cp - full_path));	// 여기서 root경로 복사
					cp++;	// pass '\'
					(*ret_path_start) = cp;	// 여기가 path의 시작
					return TRUE;
				}
				else
				{	// 네번째 '\'가 없음
					Dz1STRCPY(ret_root_name, full_path);	// full_path자체가 root
					(*ret_path_start) = NULL;
					return TRUE;
				}
			}
			// 서버명만 있고 공유 폴더명이 없으면 Fail
		}
		// 서버명만 있으면 Fail
	}
	return FALSE;
}

// path_of_me경로에 있는 모든 sub-dir를 me하위로 등록
static void _append_childs(Dz1TreeCtrlFolder *dst, HTREEITEM me, Dz1DirCatalog *cat)
{
	if (cat == NULL) { }
	else
	{
		if (cat->valid > 0)
		{
			u32_t i;
			HTREEITEM inserted;
			_Dz1DirCatalog_sort(cat, _dir_entry_cmp);
			for (i = 0; i < cat->valid; i++)
			{
				if ((inserted = dst->InsertItem(cat->entries[i].name, me, TVI_LAST)) != NULL)
					dst->SetItemData(inserted, (LONG_PTR)cat->entries[i].date);
			}
			
		}
	}
}

static void append_childs(Dz1TreeCtrlFolder *dst, HTREEITEM me, Dz1Str path_of_me, Dz1DirCatalogCache *cache)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	_trim_last_sep(path_of_me);
	Dz1DirCatalog key = { path_of_me }, *cat = Dz1DirCatalogCache_getDirCatalog(cache, path_of_me, FALSE, errp);
	if (cat == NULL) { }
	else _append_childs(dst, me, cat);
}


// Drive Root Node 삽입, 하위 폴더 등록
static Dz1Error _add_child_of_root(Dz1TreeCtrlFolder *dst, Dz1DirCatalogCache *cache)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	TCHAR names[256][4];
	memset(names, 0, sizeof(TCHAR) * 256 * 4);
	DWORD len = GetLogicalDriveStrings(4096, (TCHAR *)names), i;
	len /= 4;

	bool_t done = FALSE;
	HTREEITEM child_of_root = NULL;
	for (i = 0; i < len && done == FALSE; i++)
	{
		names[i][2] = 0;
		Dz1Thread_printf(Dz1T("@@@ Add Root Node = ")); Dz1Str_dump(names[i], 0);
		if ((child_of_root = dst->InsertItem(names[i])) == NULL) { ERR_SET_OUT(errp, EFAULT); done = TRUE; }
		else
		{
			names[i][2] = 0;
			dst->SetItemData(child_of_root, 0);
			append_childs(dst, child_of_root, names[i], cache);
		}
	}
	return err;
}

// 공유 폴더 Root Node 삽입
static Dz1Error _add_child_of_shares(Dz1TreeCtrlFolder *dst, Dz1MfcLanManPathList *lan_man_hosts, Dz1DirCatalogCache *cache)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (lan_man_hosts != NULL)
	{
		u32_t cnt = 0;
		Dz1MfcLanManPathEntry **arr = lan_man_hosts->get_array(lan_man_hosts, &cnt, errp);
		if (arr != NULL)
		{
			u32_t i;
			bool_t done = FALSE;
			HTREEITEM child_of_share = NULL;
			for (i = 0; i < cnt && done == FALSE; i++)
			{
				if ((child_of_share = dst->InsertItem(arr[i]->name)) == NULL) { ERR_SET_OUT(errp, EFAULT); done = TRUE; }
				else
				{
					dst->SetItemData(child_of_share, 0);
					append_childs(dst, child_of_share, arr[i]->name, cache);
				}
			}
			Dz1Free(arr);
		}
	}
	return err;
}
// Utility
///////////////////////////////////////////////////////////////////////////////

Dz1TreeCtrlFolder::Dz1TreeCtrlFolder() : CDz1TreeCtrl()
{
	m_cache_ref = FALSE;
}
Dz1TreeCtrlFolder::~Dz1TreeCtrlFolder()
{
	if (m_cache_ref == FALSE)
		Dz1DirCatalogCache_delAndSetNull(&m_cache);
	CDz1TreeCtrl::~CDz1TreeCtrl();
}

BOOL Dz1TreeCtrlFolder::OnInitControl(Dz1MfcLanManPathList *lan_man_hosts, Dz1DirCatalogCache *dir_cache)
{	// root entry를 추가하고 root_entry의 자식을 추가해둔다.
	DZ1_ERROR_SAFE_VAR(errp, err);
	BOOL ret = FALSE;

	SetIndent(10);

	if (dir_cache != NULL)
	{
		m_cache = dir_cache;
		m_cache_ref = TRUE;
	}
	else
	{
		m_cache = Dz1DirCatalogCache_new(NULL);
		m_cache_ref = FALSE;
	}
	ASSERT(m_cache != NULL);

	if ((*errp = _add_child_of_root(this, m_cache)).code) ERR_OUT(errp);
	else if ((*errp = _add_child_of_shares(this, lan_man_hosts, m_cache)).code) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
		ret = TRUE;
	}
	return ret;
}

Dz1Error Dz1MfcPathUtil_splitRootRest(TCHAR *dst_root, TCHAR *dst_rest, Dz1Str full_path)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (full_path == NULL || full_path[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		TCHAR _root_name[1024] = { 0, }, *rnp = dst_root == NULL ? _root_name : dst_root;
		TCHAR *path_start = NULL;
		if (_is_local_path(full_path, rnp, &path_start))
		{
			if (dst_rest != NULL)
			{
				if (path_start != NULL) Dz1STRCPY(dst_rest, path_start);
				else dst_rest[0] = 0;
			}
			Dz1Error_set(errp, 0);
		}
		else if (_is_network_path(full_path, rnp, &path_start))
		{
			if (dst_rest != NULL)
			{
				if (path_start != NULL) Dz1STRCPY(dst_rest, path_start);
				else dst_rest[0] = 0;
			}
			Dz1Error_set(errp, 0);
		}
		else ERR_SET_OUT(errp, EINVAL);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// 지정한 경로로 Item Select
HTREEITEM Dz1TreeCtrlFolder::FindItemByPath(Dz1Str full_path, Dz1Error *err)
{
	HTREEITEM ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len = 0;
	if (full_path == NULL || (len = Dz1STRLEN(full_path)) < 3) ERR_SET_OUT(errp, EINVAL);
	else
	{
		TCHAR root_name[1024] = { 0, }, *path_start = NULL;;
		if (_is_local_path(full_path, root_name, &path_start))
		{
			Dz1Str_ucase(root_name);
			len = path_start == NULL ? 0 : Dz1STRLEN(path_start);
			if ((ret = MoveToPath(root_name, path_start, len, errp)) == NULL) ERR_OUT(errp);
		}
		else if (_is_network_path(full_path, root_name, &path_start))
		{
			len = path_start == NULL ? 0 : Dz1STRLEN(path_start);
			if ((ret = MoveToPath(root_name, path_start, len, errp)) == NULL) ERR_OUT(errp);
		}
		else ERR_SET_OUT(errp, EINVAL);
	}
	return ret;
}

HTREEITEM Dz1TreeCtrlFolder::FindItemByPath(CString &full_path, Dz1Error *err)
{
	HTREEITEM ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((ret = FindItemByPath(full_path.GetBuffer(), errp)) == NULL) ERR_OUT(errp);
	return ret;
}
// 지정한 경로로 Item 찾기
///////////////////////////////////////////////////////////////////////////////

HTREEITEM Dz1TreeCtrlFolder::FindItemByName(HTREEITEM parent, CString &name)
{
	HTREEITEM i;
	CString item_name;
	for (i = GetChildItem(parent); i != NULL; i = GetNextSiblingItem(i))
	{
		item_name = GetItemText(i);
		if (item_name == name) return i;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// 경로 추가
HTREEITEM Dz1TreeCtrlFolder::AddPath(HTREEITEM item, TCHAR *path, Dz1Error *err)
{
	HTREEITEM ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	TCHAR name[1024];
	Dz1STRCPY(name, path);
	size_t len = Dz1STRLEN(name);
	if (name[len - 1] == DIR_SEP) name[len - 1] = 0;

	HTREEITEM child = SearchChildItem(item, name);
	if (child != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		TCHAR dst_path[4096];
		GetPathByItem(item, dst_path, 4096);
		Dz1STRCAT(dst_path, DIR_SEPRATOR);
		Dz1STRCAT(dst_path, name);

		if (Dz1Dir_isExist(dst_path) == TRUE) ERR_SET_OUT(errp, EEXIST);
		else if ((*errp = Dz1Dir_mkDir(dst_path)).code) ERR_OUT(errp);
		else
		{
			
			HTREEITEM i, after = NULL;
			CString own;
			for (i = GetChildItem(item); i != NULL; i = GetNextItem(i, TVGN_NEXT))
			{
				own = GetItemText(i);
#ifdef UNICODE
				if (_dir_name_cmp(own.GetBuffer(), name) > 0)
#else
				if (strcmp(own.GetBuffer(), name) > 0)
#endif
				{
					if ((after = GetPrevSiblingItem(i)) == NULL) after = TVI_FIRST;
					break;
				}
			}

			if (after == NULL) after = TVI_LAST;

			ret = this->InsertItem(name, item, after);
		}
	}
	return ret;
}

HTREEITEM Dz1TreeCtrlFolder::AddPath(HTREEITEM item, CString &path, Dz1Error *err) { return AddPath(item, path.GetBuffer(), err); }
// 경로 추가
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Item으로 완전한 경로 얻기
bool_t Dz1TreeCtrlFolder::GetPathByItem(HTREEITEM item, CString &dst)
{
	if (item == NULL) return FALSE;
	else
	{
		CString name = GetItemText(item);
		if (name.GetLength() == 0) return FALSE;
		else
		{
			HTREEITEM parent = GetParentItem(item);
			if (parent != NULL)
			{	// parent name
				if (GetPathByItem(parent, dst) == FALSE) return FALSE;
			}

			if (dst.GetLength() != 0) dst += DIR_SEPRATOR;
			dst += name;

			return TRUE;
		}
	}
}

bool_t Dz1TreeCtrlFolder::GetPathByItem(HTREEITEM item, TCHAR *dst, int dst_len)
{
	TCHAR *cp = dst;

	CString str;
	if (GetPathByItem(item, str) == TRUE)
	{
		int space_len = dst_len - 1, str_len = str.GetLength();
		int copy_len = str_len < space_len ? str_len : space_len;
		Dz1STRNCPY(cp, str.GetBuffer(), copy_len); cp += copy_len;
		(*cp) = 0;
		return TRUE;
	}
	else return FALSE;
}
// Item으로 완전한 경로 얻기
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 지정 node에서 지정 name의 Item삭제
Dz1Error Dz1TreeCtrlFolder::DelPath(HTREEITEM item, HTREEITEM child)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	CString str;
	if (GetPathByItem(child, str) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = Dz1Dir_flush(str.GetBuffer() )).code) ERR_OUT(errp);
	else if ((*errp = Dz1Dir_delete(str.GetBuffer() )).code) ERR_OUT(errp);
	else DeleteItem(child);

	return err;
}

Dz1Error Dz1TreeCtrlFolder::DelPath(HTREEITEM item, TCHAR *dir_name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	HTREEITEM child = SearchChildItem(item, dir_name);
	if (child == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((*errp = DelPath(item, child)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1TreeCtrlFolder::DelPath(HTREEITEM item, CString &dir_name) { return DelPath(item, dir_name.GetBuffer()); }
// 지정 node에서 지정 name의 Item삭제
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1TreeCtrlFolder::RenamePath(HTREEITEM dst, CString &new_name)
{
	return RenamePath(dst, new_name.GetBuffer());
}

Dz1Error Dz1TreeCtrlFolder::RenamePath(HTREEITEM dst, TCHAR *new_name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	HTREEITEM hParent = GetParentItem(dst);
	if (hParent == NULL || hParent == TVI_ROOT) ERR_SET_OUT(errp, EPERM);
	else
	{
		TCHAR path_src[4096], path_dst[4096];
		GetPathByItem(dst, path_src, 4095);
		GetPathByItem(hParent, path_dst, 4095);
		if ((*errp = Dz1PathStr_appendSepStr(path_dst, new_name)).code) ERR_OUT(errp);
		else if ((*errp = Dz1File_rename(path_dst, path_src)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// MFC Message Handling Helper
void Dz1TreeCtrlFolder::ExpandingNode(HTREEITEM acting_item, u32_t action)
{
	BeginWaitCursor();
	if (acting_item != NULL)
	{
		CString str = GetItemText(acting_item);
		if (str.GetLength() > 0)
		{
			if (action == 2)
			{	// 열릴때
				ItemExpending(acting_item);
			}
			else if (action == 1)
			{	// 닫힐때
				ItemCollapsed(acting_item);
			}
		}
	}
	EndWaitCursor();
}
// MFC Message Handling Helper
///////////////////////////////////////////////////////////////////////////////

void Dz1TreeCtrlFolder::RefreshNode(HTREEITEM item, bool_t do_not_use_cache)
{
	HTREEITEM i;
	SyncChilds(item, do_not_use_cache);
	for (i = GetChildItem(item); i != NULL; i = GetNextItem(i, TVGN_NEXT)) SyncChilds(i);
	Invalidate();
}

///////////////////////////////////////////////////////////////////////////////
// Search Child
HTREEITEM Dz1TreeCtrlFolder::SearchChildItem(HTREEITEM item, TCHAR *name)
{
	HTREEITEM i;
	CString str;
	for (i = GetChildItem(item); i != NULL; i = GetNextItem(i, TVGN_NEXT))
	{
		str = GetItemText(i);
		if (Dz1STRCMP(str.GetBuffer(), name) == 0) return i;
	}
	return NULL;
}

HTREEITEM Dz1TreeCtrlFolder::SearchChildItem(HTREEITEM item, CString &name)
{
	return SearchChildItem(item, name.GetBuffer());
}

// Search Child
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 지정 Node에 대한 Child관리
// void Dz1TreeCtrlFolder::AddChilds(HTREEITEM item, Dz1DirCatalog *cat)
// {
// 	if (GetChildItem(item) == NULL)
// 	{
// 		u32_t i = 0;
// 		for (i = 0; i < cat->valid; i++)
// 			this->InsertItem(cat->entries[i].name, item, TVI_LAST);
// 	}
// }

void Dz1TreeCtrlFolder::RemoveChilds(HTREEITEM item)
{
	HTREEITEM _child;
	while((_child = GetChildItem(item)) != NULL)
		DeleteItem(_child);
}

HTREEITEM Dz1TreeCtrlFolder::GetItemNotExist(HTREEITEM me, Dz1DirCatalog *childs_of_me)
{
	CString str;
	HTREEITEM i;
	for (i = GetChildItem(me); i != NULL; i = GetNextItem(i, TVGN_NEXT) )
	{
		str = GetItemText(i);
		if (Dz1DirCatalog_find(childs_of_me, str.GetBuffer()) == -1) return i;
	}
	return NULL;
}

Dz1DirEntry *Dz1TreeCtrlFolder::GetEntryNotExist(Dz1DirCatalog *childs_of_me, HTREEITEM me)
{
	Dz1DirEntry *p = NULL;
	u32_t i;
	for (i = 0; i < childs_of_me->valid; i++)
	{
		p = &childs_of_me->entries[i];
		if (SearchChildItem(me, p->name) == NULL) return p;
	}
	return NULL;
}

void Dz1TreeCtrlFolder::InsertItemLocated(HTREEITEM me, Dz1Str child_name, time_t item_time)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t inserted = FALSE;

	HTREEITEM i, temp;
	CString str;
	for (i = GetChildItem(me); i != NULL; i = GetNextItem(i, TVGN_NEXT) )
	{
		str = GetItemText(i);
		if (_dir_name_cmp(str.GetBuffer() , child_name) > 0)
		{
			HTREEITEM prev_item = GetPrevSiblingItem(i); if (prev_item == NULL) prev_item = TVI_FIRST;

			if ((temp = InsertItem(child_name, me, prev_item)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else SetItemData(temp, (LONG_PTR)item_time);
			inserted = TRUE;
			break;
		}
	}

	if (inserted == FALSE)
	{
		if ((temp = InsertItem(child_name, me, TVI_LAST)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else SetItemData(temp, (LONG_PTR)item_time);
	}
}

void Dz1TreeCtrlFolder::SyncChilds(HTREEITEM target_item, bool_t do_not_use_cache)
{
	TCHAR path_name[4096] = { 0, };

	GetPathByItem(target_item, path_name, 4096);	// 대상 아이템의 실제 경로 파악
	
//	Dz1DirCatalog *child_dirs = _get_catalog(path_name, m_cache, NULL);
	Dz1DirCatalog *child_dirs = Dz1DirCatalogCache_getDirCatalog(m_cache, path_name, do_not_use_cache, NULL);
	if (child_dirs != NULL)
	{	// 대상 아이템의 자식 폴더 목록 생성
		HTREEITEM i;

		_Dz1DirCatalog_sort(child_dirs, _dir_entry_cmp);

		// item에 등록된 자식 중에서 폴더 목록에 없는 자식을 찾아서 삭제
		while( (i = GetItemNotExist(target_item, child_dirs)) != NULL)
			DeleteItem(i);

		Dz1DirEntry *entry = NULL;
		while((entry = GetEntryNotExist(child_dirs, target_item)) != NULL)
			InsertItemLocated(target_item, entry->name, entry->date);
	}
}
// 지정 Node에 대한 Child관리
///////////////////////////////////////////////////////////////////////////////


HTREEITEM Dz1TreeCtrlFolder::MoveToPath(Dz1Str root_name, Dz1Str path, size_t len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	HTREEITEM ret = NULL;
	HTREEITEM i = SearchChildItem(TVI_ROOT, root_name);

	if (i == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (path == NULL || path[0] == 0) ret = i;
	else if ((ret = MoveToSubPath(path, len, i, errp)) == NULL) ERR_OUT(errp);

	return ret;
}

HTREEITEM Dz1TreeCtrlFolder::MoveToSubPath(Dz1Str path, size_t len, HTREEITEM i, Dz1Error *err)
{
	HTREEITEM ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	TCHAR temp[4096];
	Dz1STRCPY(temp, path);

	HTREEITEM selected_item = NULL, child = NULL;;
	TCHAR *cp = NULL, *next = NULL;

	if (temp[len - 1] == DIR_SEP_W) temp[len - 1] = 0;	// trim
	cp = temp;											// init working point

	while(*cp != 0)
	{
		ItemExpending(i);
		if ((next = Dz1STRCHR(cp, DIR_SEP_W)) == NULL)
		{	// 더이상 \아 안찾아지면 -> 마지막 아이템
			if ((child = SearchChildItem(i, cp)) == NULL)
			{	// 그런애가 없으면 select_item은 i
				selected_item = i;
			}
			else
			{
				selected_item = child;
			}
			break;
		}
		else
		{	// 찾아졌다는 말은 추가 경로가 더 있음으로
			*next++ = 0;
			if ((child = SearchChildItem(i, cp)) == NULL)
			{	// 경로가 있지만 실제론 없음
				selected_item = i;
				break;
			}
			else
			{
				selected_item = child;
				i = child;
				cp = next;
			}
		}
	}

	if (selected_item != NULL) ret = selected_item;
	else Dz1Error_set(errp, ENOENT);

	return ret;
}

void Dz1TreeCtrlFolder::ItemExpending(HTREEITEM acting_item)
{
	HTREEITEM i;

	CString str = GetItemText(acting_item);
	Dz1Thread_printf(Dz1T("@@@ Folder Tree : Expanding = ")); Dz1Str_dump(str.GetBuffer(), 0);

	SyncChilds(acting_item);
	for (i = GetChildItem(acting_item); i != NULL; i = GetNextItem(i, TVGN_NEXT))
		SyncChilds(i);
}

void Dz1TreeCtrlFolder::ItemCollapsed(HTREEITEM item)
{
	SyncChilds(item);	// 헌재 상태를 동기화
}

/*
///////////////////////////////////////////////////////////////////////////////
// TreeNode
static Dz1Error Dz1MfcPathTreeNodeList_addRootDisks(Dz1MfcPathTreeNodeList *dst, Dz1DirCatalogCache *dir_cache)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	TCHAR names[256][4];
	memset(names, 0, sizeof(TCHAR) * 256 * 4);
	DWORD len = GetLogicalDriveStrings(4096, (TCHAR *)names), i;
	len /= 4;

	bool_t done = FALSE;
	Dz1MfcPathTreeNode *node = NULL;
	for (i = 0; i < len && done == FALSE; i++)
	{
		names[i][2] = 0;	// "C:"
		Dz1Thread_printf("@@@ addRootDisks = "); Dz1Str_dump(names[i], 0);
		if ((node = Dz1MfcPathTreeNodeList_addNode(names[i], errp)) == NULL) ERR_OUT(errp, EFAULT);
		else Dz1MfcPathTreeNode_addChilds(node, names[i], cache);
	}
	return err;
}

Dz1MfcPathTreeNodeList *Dz1MfcPathTreeNodeList_genRoots(Dz1MfcPathTreeNodeList *lan_man_hosts, Dz1DirCatalogCache *dir_cache)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MfcPathTreeNodeList *ret = NULL;
	if (dir_cache == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcPathTreeNodeList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcPathTreeNodeList_delAndSetNull, (void *)&ret);

		if ((*errp = Dz1MfcPathTreeNodeList_addRootDisks(ret, dir_cache)).code) ERR_OUT(errp);
		else if ((*errp = _add_child_of_shares(this, lan_man_hosts, m_cache)).code) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret = TRUE;
		}
		pthread_cleanup_pop(errp->code); // (Dz1MfcPathTreeNodeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

// TreeNode
///////////////////////////////////////////////////////////////////////////////
*/