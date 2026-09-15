#pragma once

#include "Dz1CodeGenDef.h"

// CDz1CodeGenTdoColumnDlg 대화 상자입니다.

class CDz1CodeGenTdoColumnDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1CodeGenTdoColumnDlg)

public:
	CDz1CodeGenTdoColumnDlg(Dz1CodeGenListColumn *column, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1CodeGenTdoColumnDlg();

	CEdit						  m_editOrder;
	CEdit						  m_editName;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_TDO_COLUMN_DLG };

private:
	Dz1CodeGenListColumn		 *m_column;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
};
