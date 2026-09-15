#ifndef DZ1_MFC_LIST_CTRL_LANMAN_PATH_H
#define DZ1_MFC_LIST_CTRL_LANMAN_PATH_H

#include "Dz1MfcDef.h"
#include <Dz1MfcListCtrlTemplate.h>

class CDz1MfcListCtrlLanManPath : public CDz1ListCtrlRW<Dz1MfcLanManPathList, Dz1MfcLanManPathEntry>
{
public:
	CDz1MfcListCtrlLanManPath() : CDz1ListCtrlRW<Dz1MfcLanManPathList, Dz1MfcLanManPathEntry>(Dz1MfcLanManPathEntry_clone, Dz1MfcLanManPathEntry_del) { }
	~CDz1MfcListCtrlLanManPath() { CDz1ListCtrlRW::~CDz1ListCtrlRW(); }
	BOOL OnInitControl();
	BOOL OnInitControl(CListCtrlStyledColumnDesign column_fmt[], int numOfCol);

	Dz1Error AddLanManPath(CString &str, int *ret_idx = NULL);

protected:
	virtual void	 GetFirstColumn(CString &str, Dz1MfcLanManPathEntry *node);
	virtual BOOL	 SetItemTexts(int nRow, Dz1MfcLanManPathEntry *node);
};

#endif