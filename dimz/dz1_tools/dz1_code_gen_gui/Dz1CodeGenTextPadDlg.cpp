// ..\..\Dz1CodeGenTextPadDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "dz1_code_gen_gui.h"
#include "Dz1CodeGenTextPadDlg.h"


// CDz1CodeGenTextPadDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1CodeGenTextPadDlg, CDialog)

CDz1CodeGenTextPadDlg::CDz1CodeGenTextPadDlg(Dz1Str title, Dz1Str text, CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenTextPadDlg::IDD, pParent)
{
	m_title = title;
	m_text = text;
}

CDz1CodeGenTextPadDlg::~CDz1CodeGenTextPadDlg()
{
}

void CDz1CodeGenTextPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_editText);
}


BEGIN_MESSAGE_MAP(CDz1CodeGenTextPadDlg, CDialog)
END_MESSAGE_MAP()


// CDz1CodeGenTextPadDlg 메시지 처리기입니다.

BOOL CDz1CodeGenTextPadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (m_title) this->SetWindowText(m_title);
	if (m_text) m_editText.SetWindowText(m_text);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
