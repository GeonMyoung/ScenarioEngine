// ..\..\Dz1CodeGenTodecPublishDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include <Dz1MfcFileSelectDlg.h>

#include "Dz1CodeGenTodecPublish.h"

#include "dz1_code_gen_gui.h"
#include "Dz1CodeGenTodecPublishDlg.h"


// CDz1CodeGenTodecPublishDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1CodeGenTodecPublishDlg, CDialog)

CDz1CodeGenTodecPublishDlg::CDz1CodeGenTodecPublishDlg(ConstructCodec *todec, Dz1Str todec_path, CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenTodecPublishDlg::IDD, pParent)
{
	m_todec = todec;
	ASSERT(m_todec != NULL);

	m_todec_path = todec_path;

	TCHAR *last_path = Dz1STRRCHR(m_todec_path, DIR_SEP);
	if (last_path != NULL) last_path++;	// skip seprator

	Dz1STRCPY(m_src_path, m_todec_path);
	if (Dz1STRLEN(last_path) > 0)
	{	// 마지막 경로명이 있다.
		if (Dz1STRCMP(last_path, Dz1Text("include")) == 0)
		{	// 마지막 경로명이 include이다.
			TCHAR *dp = m_src_path, *cp = m_todec_path;
			while(cp < last_path) *dp++ = *cp++;				// copy base_path;
			Dz1STRCPY(dp, Dz1Text("src"));						// append "src"
		}
	}
	Dz1STRCPY(m_hdr_path, m_todec_path);
}

CDz1CodeGenTodecPublishDlg::~CDz1CodeGenTodecPublishDlg()
{
}

void CDz1CodeGenTodecPublishDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE_BASE_NAME, m_editFileBaseName);

	DDX_Control(pDX, IDC_CHECK_SOURCE, m_chkSource);
	DDX_Control(pDX, IDC_EDIT_SOURCE, m_editSource);
	DDX_Control(pDX, IDC_BUTTON_SOURCE, m_btnSource);

	DDX_Control(pDX, IDC_CHECK_HEADER, m_chkHeader);
	DDX_Control(pDX, IDC_EDIT_HEADER, m_editHeader);
	DDX_Control(pDX, IDC_BUTTON_HEADER, m_btnHeader);
}


BEGIN_MESSAGE_MAP(CDz1CodeGenTodecPublishDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SOURCE, &CDz1CodeGenTodecPublishDlg::OnBnClickedButtonSource)
	ON_BN_CLICKED(IDC_BUTTON_HEADER, &CDz1CodeGenTodecPublishDlg::OnBnClickedButtonHeader)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDz1CodeGenTodecPublishDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CDz1CodeGenTodecPublishDlg 메시지 처리기입니다.

BOOL CDz1CodeGenTodecPublishDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Dz1MdefcModule *module = m_todec->module;
	Dz1Str fn = module->name;
	TCHAR name[1024];
	Dz1FileName_splitPathName(NULL, name, fn);

	CString str;
	str.Format(_T("%sStream"), name);
	m_editFileBaseName.SetWindowText(str);

	m_chkSource.SetCheck(TRUE);
	m_chkHeader.SetCheck(TRUE);
	m_editSource.SetWindowText(m_src_path);
	m_editHeader.SetWindowText(m_hdr_path);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDz1CodeGenTodecPublishDlg::OnBnClickedButtonSource()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[4096];
	CString str;
	m_editSource.GetWindowText(str);
	if (Dz1MfcPathSelectDlg(this->m_hWnd, str.GetBuffer(), path, _T("Source 출력 위치")) == TRUE)
		m_editSource.SetWindowText(path);
}

void CDz1CodeGenTodecPublishDlg::OnBnClickedButtonHeader()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[4096];
	CString str;
	m_editHeader.GetWindowText(str);
	if (Dz1MfcPathSelectDlg(this->m_hWnd, str.GetBuffer(), path, _T("Header 출력 위치")) == TRUE)
		m_editSource.SetWindowText(path);
}

bool_t CDz1CodeGenTodecPublishDlg::PublishSource(CString &name)
{
	bool_t ret = FALSE;
	if (m_chkSource.GetCheck())
	{
		CString str;
		DZ1_ERROR_SAFE_VAR(errp, err);
		m_editSource.GetWindowText(str);
		if (str.IsEmpty()) MessageBox(_T("Source Publish Path"));
		else if ((*errp = ConstructCodec_publish_src(m_todec, str.GetBuffer(), name.GetBuffer() )).code) ERR_DLG_OUT(errp);
		else
		{
			ret = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	else ret = TRUE;
	return ret;
}

bool_t CDz1CodeGenTodecPublishDlg::PublishHeader(CString &name)
{
	bool_t ret = FALSE;
	if (m_chkHeader.GetCheck())
	{
		CString str;
		DZ1_ERROR_SAFE_VAR(errp, err);
		m_editHeader.GetWindowText(str);
		if (str.IsEmpty()) MessageBox(_T("Header Publish Path"));
		else if ((*errp = ConstructCodec_publish_hdr(m_todec, str.GetBuffer(), name.GetBuffer() )).code) ERR_DLG_OUT(errp);
		else
		{
			ret = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	else ret = TRUE;
	return ret;
}

void CDz1CodeGenTodecPublishDlg::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString name;
	m_editFileBaseName.GetWindowText(name);

	if (name.IsEmpty()) MessageBox(_T("File Base Name"));
	else if (m_chkSource.GetCheck() == FALSE && m_chkHeader.GetCheck() == FALSE) MessageBox(_T("No Publish"));
	else
	{
		if (PublishSource(name) == FALSE) MessageBox(_T("Source Publish Fail"));
		else if (PublishHeader(name) == FALSE) MessageBox(_T("Header Publish Fail"));
		else OnOK();
	}
}
