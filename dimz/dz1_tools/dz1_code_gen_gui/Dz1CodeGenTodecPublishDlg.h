#pragma once
#include "Dz1CodeGenTodecDef.h"

// CDz1CodeGenTodecPublishDlg 대화 상자입니다.

class CDz1CodeGenTodecPublishDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1CodeGenTodecPublishDlg)

public:
	CDz1CodeGenTodecPublishDlg(ConstructCodec *todec, Dz1Str todec_path, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1CodeGenTodecPublishDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TODEC_PUBLISH_DLG };
private:
	CEdit										 m_editFileBaseName;

	CButton										 m_chkSource;
	CEdit										 m_editSource;
	CButton										 m_btnSource;

	CButton										 m_chkHeader;
	CEdit										 m_editHeader;
	CButton										 m_btnHeader;

	ConstructCodec								*m_todec;
	Dz1Str										 m_todec_path;
	TCHAR										 m_src_path[4096];
	TCHAR										 m_hdr_path[4096];

	bool_t										 PublishSource(CString &name);
	bool_t										 PublishHeader(CString &name);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSource();
	afx_msg void OnBnClickedButtonHeader();
	afx_msg void OnBnClickedButtonOk();
};
