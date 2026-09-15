#pragma once

#include <Dz1TdcInfoModule.h>
#include "ListCtrlTdoUnknown.h"
#include "ListCtrlTdoObject.h"

// CDz1CodeGenTdoDlg 대화 상자입니다.

class CDz1CodeGenTdoDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1CodeGenTdoDlg)

public:
	CDz1CodeGenTdoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1CodeGenTdoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TDO_DLG };

	CEdit							 m_editTdoFile;
	CTreeCtrl						 m_treeTdoInclude;
	CListCtrlTdoUnknown				 m_listTdoUnknown;
	CListCtrlTdoObject				 m_listTdoObject;
	CButton							 m_btnCreateListControl;
	CButton							 m_btnSaveToTDC;
private:
	Dz1Error LoadTree(void);

	Dz1MdefcModule					*m_module;
	ObjectInfo						*m_selected;

	TCHAR							 m_path[MY_MAX_PATH];
	TCHAR							 m_name[MY_MAX_PATH];
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonTdoFile();
	afx_msg void OnNMClickListTdoObject(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonCreateListControl();
//	afx_msg void OnBnClickedButtonTodec();
	afx_msg void OnBnClickedButtonSaveToTdc();
};
