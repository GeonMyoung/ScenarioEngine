// ..\..\Dz1CodeGenTdoColumnDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include <dz1_str.h>
#include "dz1_code_gen_gui.h"
#include "Dz1CodeGenTdoColumnDlg.h"


// CDz1CodeGenTdoColumnDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1CodeGenTdoColumnDlg, CDialog)

CDz1CodeGenTdoColumnDlg::CDz1CodeGenTdoColumnDlg(Dz1CodeGenListColumn *column, CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenTdoColumnDlg::IDD, pParent)
{
	m_column = column;
	ASSERT(m_column != NULL);
}

CDz1CodeGenTdoColumnDlg::~CDz1CodeGenTdoColumnDlg()
{
}

void CDz1CodeGenTdoColumnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ORDER, m_editOrder);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
}


BEGIN_MESSAGE_MAP(CDz1CodeGenTdoColumnDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDz1CodeGenTdoColumnDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CDz1CodeGenTdoColumnDlg 메시지 처리기입니다.

BOOL CDz1CodeGenTdoColumnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString str;

	str.Format(_T("%u"), m_column->order);
	m_editOrder.SetWindowText(str);

	if (m_column->name != NULL)
	{
		str.Format(_T("%s"), m_column->name);
		m_editName.SetWindowText(str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDz1CodeGenTdoColumnDlg::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_editOrder.GetWindowTextLength() == 0) MessageBox(_T("Order를 입력해주세요"));
	else if (m_editName.GetWindowTextLength() == 0) MessageBox(_T("Name을 입력해주세요"));
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

		CString strOrder, strName;
		m_editOrder.GetWindowText(strOrder);
		m_editName.GetWindowText(strName);

		m_column->order = (u32_t)atoi((LPSTR)(LPCSTR)strOrder);
		Dz1Str_delAndSetNull(&m_column->name);
		if ((m_column->name = Dz1Str_dup((LPSTR)(LPCSTR)strName, errp)) == NULL) ERR_DLG_OUT(errp);
		else OnOK();
	}
}
