// dz1_text2array_dlg.h : 헤더 파일
//

#pragma once
#include <dz1_file2src.h>

// CText2ArrayDlg 대화 상자
class CText2ArrayDlg : public CDialog
{
// 생성
public:
	CText2ArrayDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_DZ1_TEXT2ARRAY_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원
private:
	TCHAR m_srcPath[MY_PATH_MAX];
	TCHAR m_srcName[MY_FILENAME_MAX];
	TCHAR m_dstPath[MY_PATH_MAX];
	TCHAR m_dstName[MY_FILENAME_MAX];

	CEdit m_editSrc;
	CComboBox m_comboSrcMode;
	CComboBox m_comboSrcTextAttr;

	CEdit m_editVariable;
	CComboBox m_comboOutVarMode;
	CComboBox m_comboOutDataMode;

	CEdit m_editDst;
	CButton m_bDst;
	CComboBox m_comboDstFormat;
	CComboBox m_comboDstFiles;
	CEdit m_editSource;
	CEdit m_editHeader;

	CButton m_bConv;

	void SetDstName(TCHAR path[MY_PATH_MAX]);
	void EnableButton(void);
	Dz1Error GetConvArg(File2SrcConvArg *arg);

	bool_t m_isFirstSourceSelect;
	int m_userSelSrcTextAttr;
	int m_userSelOutVarMode;
	int m_userSelOutDataMode;
// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSrc();
	afx_msg void OnBnClickedButtonDst();
	afx_msg void OnEnChangeEditVariable();
	afx_msg void OnBnClickedButtonConv();
	afx_msg void OnCbnSelchangeComboSrcMode();
	afx_msg void OnCbnSelchangeComboSrcTextAttr();
	afx_msg void OnCbnSelchangeComboOutVarMode();
	afx_msg void OnCbnSelchangeComboOutDataMode();
};
