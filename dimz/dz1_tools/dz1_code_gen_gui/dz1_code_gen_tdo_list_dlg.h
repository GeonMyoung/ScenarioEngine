#pragma once

#include <Dz1CodeGenDef.h>
#include "dz1_code_gen_struct.h"
#include "ListCtrlColumnsList.h"
// CDz1CodeGenTdoListDlg 대화 상자입니다.

class CDz1CodeGenTdoListDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1CodeGenTdoListDlg)

public:
	CDz1CodeGenTdoListDlg(ObjectInfo *obj, Dz1CodeGenListColumnList *ret, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1CodeGenTdoListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TDO_LIST_DLG };

	CTreeCtrl					 m_treeSources;
	CListCtrlColumnList			 m_listColumns;

private:
	ObjectInfo					*m_src;
	ListControlGenNode			*m_root;
	BOOL						 LoadTree(void);
	Dz1Error					 InsertColumn(u32_t order, ListControlGenNode *item);

	Dz1CodeGenListColumnList	*m_ret;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
};
