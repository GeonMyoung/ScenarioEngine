#ifndef LIST_CTRL_PROJECTS_H
#define LIST_CTRL_PROJECTS_H

#include <Dz1MfcListCtrlTemplate.h>
#include <dz1_task_gen_args.h>

class CListCtrlProjects :public CDz1ListCtrlRW<GenArgs2VisualStudioList, GenArgs2VisualStudioEntry>
{
public:
	CListCtrlProjects() : CDz1ListCtrlRW(GenArgs2VisualStudioEntry_clone, GenArgs2VisualStudioEntry_del) { }
	virtual ~CListCtrlProjects() { CDz1ListCtrlRW::~CDz1ListCtrlRW(); }

	BOOL OnInitControl();
	BOOL AddRow(GenArgs2VisualStudioVer ver, Dz1Str lib_root_abs, Dz1Str middle_path, Dz1Str proj_name, Dz1Error *err);
protected:
	virtual void	 GetFirstColumn(CString &str, GenArgs2VisualStudioEntry *node);
	virtual BOOL	 SetItemTexts(int nRow, GenArgs2VisualStudioEntry *node);
};

#endif