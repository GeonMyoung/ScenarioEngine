// ..\..\Dz1CodeGenStrDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "dz1_code_gen_gui.h"
#include "Dz1CodeGenStrDlg.h"


// CDz1CodeGenStrDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1CodeGenStrDlg, CDialog)

CDz1CodeGenStrDlg::CDz1CodeGenStrDlg(Dz1Str dst, size_t dst_size, Dz1CodeGenStrDlgParam *param, CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenStrDlg::IDD, pParent)
{
	m_dst = dst; ASSERT(m_dst != NULL);
	m_dst_size = dst_size; ASSERT(m_dst_size > 1);

	m_param.mask = 0;
	m_param.title = NULL;
	m_param.box_title = NULL;
	m_param.yes_button_text = NULL;
	m_param.no_button_text = NULL;
	m_param.cancel_button_text = NULL;

	if (param != NULL) memcpy(&m_param, param, sizeof(Dz1CodeGenStrDlgParam));
}

CDz1CodeGenStrDlg::~CDz1CodeGenStrDlg()
{
}

void CDz1CodeGenStrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BOX, m_staticBox);
	DDX_Control(pDX, IDC_EDIT_STR, m_editStr);
	DDX_Control(pDX, IDC_BUTTON_YES, m_btnYes);
	DDX_Control(pDX, IDC_BUTTON_NO, m_btnNo);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CDz1CodeGenStrDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_YES, &CDz1CodeGenStrDlg::OnBnClickedButtonYes)
	ON_BN_CLICKED(IDC_BUTTON_NO, &CDz1CodeGenStrDlg::OnBnClickedButtonNo)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDz1CodeGenStrDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()

// CDz1CodeGenStrDlg 메시지 처리기입니다.

BOOL CDz1CodeGenStrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (m_param.mask & CODEGEN_STR_DLG_TITLE) SetWindowText(m_param.title);
	if (m_param.mask & CODEGEN_STR_DLG_BOX_TITLE) m_staticBox.SetWindowText(m_param.box_title);

	if (m_param.mask & CODEGEN_STR_DLG_YES_TEXT)
	{
		if (m_param.yes_button_text != NULL && m_param.yes_button_text[0] != 0)
			m_btnYes.SetWindowText(m_param.yes_button_text);
		else m_btnYes.ShowWindow(SW_HIDE);
	}
	if (m_param.mask & CODEGEN_STR_DLG_NO_TEXT)
	{
		if (m_param.no_button_text != NULL && m_param.no_button_text[0] != 0)
			m_btnNo.SetWindowText(m_param.no_button_text);
		else m_btnNo.ShowWindow(SW_HIDE);
	}
	if (m_param.mask & CODEGEN_STR_DLG_CANCEL_TEXT)
	{
		if (m_param.cancel_button_text != NULL && m_param.cancel_button_text[0] != 0)
			m_btnCancel.SetWindowText(m_param.cancel_button_text);
		else m_btnCancel.ShowWindow(SW_HIDE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDz1CodeGenStrDlg::OnBnClickedButtonYes()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	m_editStr.GetWindowText(str);
	if (str.IsEmpty())
	{
		if (m_param.accept_null)
		{
			m_dst[0] = 0;
			OnOK();
		}
		else MessageBox(_T("입력데이터가 없습니다."));
	}
	else
	{
		Dz1STRNCPY(m_dst, str.GetBuffer(), m_dst_size);
		OnOK();
	}
}

void CDz1CodeGenStrDlg::OnBnClickedButtonNo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDNO);
}


void CDz1CodeGenStrDlg::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDCANCEL);
}
