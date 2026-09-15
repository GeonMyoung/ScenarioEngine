#pragma once
#include <dz1_str.h>

// CDz1CodeGenStrDlg 대화 상자입니다.
#define CODEGEN_STR_DLG_TITLE					0x80000000
#define CODEGEN_STR_DLG_BOX_TITLE				0x40000000
#define CODEGEN_STR_DLG_YES_TEXT				0x20000000
#define CODEGEN_STR_DLG_NO_TEXT					0x10000000
#define CODEGEN_STR_DLG_CANCEL_TEXT				0x08000000
#define CODEGEN_STR_DLG_ALL						0xF8000000
typedef struct Dz1CodeGenStrDlgParam
{
	bool_t						 accept_null;
	u32_t						 mask;
	Dz1Str						 title;
	Dz1Str						 box_title;
	Dz1Str						 yes_button_text;
	Dz1Str						 no_button_text;
	Dz1Str						 cancel_button_text;
} Dz1CodeGenStrDlgParam;

class CDz1CodeGenStrDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1CodeGenStrDlg)

public:
	CDz1CodeGenStrDlg(Dz1Str dst, size_t dst_size, Dz1CodeGenStrDlgParam *param, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1CodeGenStrDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STRING_DLG };
	CStatic							 m_staticBox;
	CEdit							 m_editStr;
	CButton							 m_btnYes;
	CButton							 m_btnNo;
	CButton							 m_btnCancel;
private:
	Dz1Str							 m_dst;
	size_t							 m_dst_size;
	Dz1CodeGenStrDlgParam			 m_param;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonYes();
	afx_msg void OnBnClickedButtonNo();
	afx_msg void OnBnClickedButtonCancel();
};
