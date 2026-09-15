#ifndef JAKE_EXPLORER_TREE_FOLTER_H
#define JAKE_EXPLORER_TREE_FOLTER_H

#include <dz1_str.h>
#include <Dz1MfcTreeCtrl.h>

#ifdef __cplusplus
#include <Dz1MfcDef.h>
#include <Dz1DirCatalogUtil.h>

class Dz1TreeCtrlFolder : public CDz1TreeCtrl
{
public:
	Dz1TreeCtrlFolder();
	virtual ~Dz1TreeCtrlFolder();

	BOOL		 OnInitControl(Dz1MfcLanManPathList *lan_man_hosts = NULL, Dz1DirCatalogCache *dir_cache = NULL);

	HTREEITEM	 FindItemByPath(Dz1Str full_path, Dz1Error *err);
	HTREEITEM	 FindItemByPath(CString &full_path, Dz1Error *err);
	HTREEITEM	 FindItemByName(HTREEITEM parent, CString &name);

	HTREEITEM	 AddPath(HTREEITEM item, TCHAR *dir_name, Dz1Error *err);
	HTREEITEM	 AddPath(HTREEITEM item, CString &dir_name, Dz1Error *err);

	bool_t		 GetPathByItem(HTREEITEM item, CString &dst);
	bool_t		 GetPathByItem(HTREEITEM item, TCHAR *dst, int dst_len);

	Dz1Error	 DelPath(HTREEITEM item, HTREEITEM child);
	Dz1Error	 DelPath(HTREEITEM item, TCHAR *dir_name);
	Dz1Error	 DelPath(HTREEITEM item, CString &dir_name);


	Dz1Error	 RenamePath(HTREEITEM dst, CString &new_name);
	Dz1Error	 RenamePath(HTREEITEM dst, TCHAR *new_name);
	///////////////////////////////////////////////////////////////////////////////
	// MFC Message Handling Helper
	void		 ExpandingNode(HTREEITEM item, u32_t action);	// expanding or shrinking 
	// MFC Message Handling Helper
	///////////////////////////////////////////////////////////////////////////////

	//HTREEITEM	 UpdateParent(HTREEITEM selected_item);
	void		 RefreshNode(HTREEITEM item, bool_t do_not_use_cache = FALSE);

private:
	///////////////////////////////////////////////////////////////////////////////
	// Search Child
	HTREEITEM	 SearchChildItem(HTREEITEM item, TCHAR *name);
	HTREEITEM	 SearchChildItem(HTREEITEM item, CString &name);
	// Search Child
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// 지정 Node에 대한 Child관리
	//void		 AddChilds(HTREEITEM item, Dz1DirCatalog *cat);
	void		 RemoveChilds(HTREEITEM item);
	void		 SyncChilds(HTREEITEM target_item, bool_t do_not_use_cache = FALSE);
	HTREEITEM	 GetItemNotExist(HTREEITEM me, Dz1DirCatalog *childs_of_me);
	Dz1DirEntry	*GetEntryNotExist(Dz1DirCatalog *childs_of_me, HTREEITEM me);
	void		 InsertItemLocated(HTREEITEM me, Dz1Str child_name, time_t item_time);
	// 지정 Node에 대한 Child관리
	///////////////////////////////////////////////////////////////////////////////

	HTREEITEM	 MoveToPath(Dz1Str root_name, Dz1Str path, size_t len, Dz1Error *err);
	HTREEITEM	 MoveToSubPath(Dz1Str path, size_t len, HTREEITEM i, Dz1Error *err);

	void		 ItemExpending(HTREEITEM item);
	void		 ItemCollapsed(HTREEITEM item);

	Dz1DirCatalogCache	*m_cache;
	bool_t				 m_cache_ref;
};
#endif

DZ1_CPPLINK Dz1Error Dz1MfcPathUtil_splitRootRest(TCHAR *dst_root, TCHAR *dst_rest, Dz1Str full_path);

#endif