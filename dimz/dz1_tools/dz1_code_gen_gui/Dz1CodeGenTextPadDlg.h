#pragma once
#include <dz1_str.h>

// CDz1CodeGenTextPadDlg 대화 상자입니다.

class CDz1CodeGenTextPadDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1CodeGenTextPadDlg)

public:
	CDz1CodeGenTextPadDlg(Dz1Str title, Dz1Str Text, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1CodeGenTextPadDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TEXT_PAD_DLG };
private:
	CEdit								 m_editText;

	Dz1Str								 m_title;
	Dz1Str								 m_text;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
