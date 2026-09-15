#ifndef LIST_CTRL_LIBRARIES_H
#define LIST_CTRL_LIBRARIES_H

#include <Dz1MfcListCtrlTemplate.h>
#include <dz1_task_gen_args.h>

class CListCtrlLibraries :public CDz1ListCtrlRW<GenArgs2LibraryInfo, GenArgs2LibraryEntry>
{
public:
	CListCtrlLibraries() : CDz1ListCtrlRW(GenArgs2LibraryEntry_clone, GenArgs2LibraryEntry_del) { }
	virtual ~CListCtrlLibraries() { CDz1ListCtrlRW::~CDz1ListCtrlRW(); }

	BOOL				 OnInitControl();

	void				 SetBiasPath(TCHAR *bias);
	virtual Dz1Error	 InsertRow(GenArgs2LibraryEntry **node, int *ret_idx = NULL);

	bool_t				 SwitchOrder(int idx_a, int idx_b, Dz1Error *err = NULL);
	bool_t				 Reordering(Dz1Error *err = NULL);
protected:
	virtual void		 GetFirstColumn(CString &str, GenArgs2LibraryEntry *node);
	virtual BOOL		 SetItemTexts(int nRow, GenArgs2LibraryEntry *node);

private:
	TCHAR				 m_bias_path[4096];
};

#endif