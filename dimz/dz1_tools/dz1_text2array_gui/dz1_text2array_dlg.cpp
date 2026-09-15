// dz1_text2array_dlg.cpp : 구현 파일
//

#include "stdafx.h"

#include <dz1_error.h>

#include "dz1_text2array_gui.h"
#include "dz1_text2array_dlg.h"
#include ".\dz1_text2array_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CText2ArrayDlg 대화 상자



CText2ArrayDlg::CText2ArrayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CText2ArrayDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_srcPath, 0, sizeof(TCHAR) * MY_PATH_MAX);
	memset(m_dstPath, 0, sizeof(TCHAR) * MY_PATH_MAX);
	memset(m_dstName, 0, sizeof(TCHAR) * MY_FILENAME_MAX);
	memset(m_srcName, 0, sizeof(TCHAR) * MY_FILENAME_MAX);
	m_isFirstSourceSelect = TRUE;
}

void CText2ArrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SRC, m_editSrc);
	DDX_Control(pDX, IDC_COMBO_SRC_MODE, m_comboSrcMode);
	DDX_Control(pDX, IDC_COMBO_SRC_TEXT_ATTR, m_comboSrcTextAttr);

	DDX_Control(pDX, IDC_EDIT_VARIABLE, m_editVariable);
	DDX_Control(pDX, IDC_COMBO_OUT_VAR_MODE, m_comboOutVarMode);
	DDX_Control(pDX, IDC_COMBO_OUT_DATA_MODE, m_comboOutDataMode);

	DDX_Control(pDX, IDC_EDIT_DST, m_editDst);
	DDX_Control(pDX, IDC_BUTTON_DST, m_bDst);
	DDX_Control(pDX, IDC_COMBO_DST_FORMAT, m_comboDstFormat);
	DDX_Control(pDX, IDC_COMBO_DST_FILES, m_comboDstFiles);
	DDX_Control(pDX, IDC_EDIT_SOURCE, m_editSource);
	DDX_Control(pDX, IDC_EDIT_HEADER, m_editHeader);

	DDX_Control(pDX, IDC_BUTTON_CONV, m_bConv);
}

BEGIN_MESSAGE_MAP(CText2ArrayDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SRC, OnBnClickedButtonSrc)
	ON_BN_CLICKED(IDC_BUTTON_DST, OnBnClickedButtonDst)
	ON_EN_CHANGE(IDC_EDIT_VARIABLE, OnEnChangeEditVariable)
	ON_BN_CLICKED(IDC_BUTTON_CONV, OnBnClickedButtonConv)
	ON_CBN_SELCHANGE(IDC_COMBO_SRC_MODE, OnCbnSelchangeComboSrcMode)
	ON_CBN_SELCHANGE(IDC_COMBO_SRC_TEXT_ATTR, OnCbnSelchangeComboSrcTextAttr)
	ON_CBN_SELCHANGE(IDC_COMBO_OUT_VAR_MODE, OnCbnSelchangeComboOutVarMode)
	ON_CBN_SELCHANGE(IDC_COMBO_OUT_DATA_MODE, OnCbnSelchangeComboOutDataMode)
END_MESSAGE_MAP()


// CText2ArrayDlg 메시지 처리기

BOOL CText2ArrayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_comboSrcMode.EnableWindow(FALSE);
	m_comboSrcTextAttr.EnableWindow(FALSE);
	m_editVariable.EnableWindow(FALSE);
	m_comboOutVarMode.EnableWindow(FALSE);
	m_comboOutDataMode.EnableWindow(FALSE);
	m_bDst.EnableWindow(FALSE);
	m_comboDstFormat.EnableWindow(FALSE);
	m_comboDstFiles.EnableWindow(FALSE);
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CText2ArrayDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CText2ArrayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CText2ArrayDlg::OnBnClickedButtonSrc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[MY_PATH_MAX] = { 0, };
	if (MyGetFile(this, m_srcPath, path, m_srcName, NULL, NULL) == TRUE)
	{
		Dz1STRCPY(m_srcPath, path);
		TCHAR fn[4096] = { 0, };
		Dz1SPRINTF(fn, "%s" DIR_SEPRATOR "%s", path, m_srcName);
		m_editSrc.SetWindowText(fn);

		TCHAR *np = m_srcName;
		TCHAR *cp = m_dstName;
		while(*np)
		{
			if (*np == '.') { *cp++ = '_'; np++; }
			else *cp++ = *np++;
		}
		*cp++ = '\0';

		if (strlen(m_dstPath) == 0)
			SetDstName(m_srcPath);
		else SetDstName(m_dstPath);

		if (m_isFirstSourceSelect == TRUE)
		{
			m_comboSrcMode.SetCurSel(1);
			m_comboSrcTextAttr.SetCurSel(-1); m_userSelSrcTextAttr = -1;
			m_comboOutVarMode.SetCurSel(0); m_userSelOutVarMode = 0;
			m_comboOutDataMode.SetCurSel(0); m_userSelOutDataMode = 0;
			m_comboDstFormat.SetCurSel(0);
			m_comboDstFiles.SetCurSel(2);
			m_isFirstSourceSelect = FALSE;
		}
		EnableButton();
	}
}

void CText2ArrayDlg::SetDstName(TCHAR path[MY_PATH_MAX])
{
	CString str;
	Dz1STRCPY(m_dstPath, path);
	m_editDst.SetWindowText(path);

	str.Format("%s.c", m_dstName);
	m_editSource.SetWindowText(str);

	str.Format("%s.h", m_dstName);
	m_editHeader.SetWindowText(str);
}

void CText2ArrayDlg::OnBnClickedButtonDst()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[MY_PATH_MAX] = { 0, };
	if (MyGetPath(this->m_hWnd, m_dstPath, path, _T("변환된 소스 파일이 저장된 폴더를 선택하세요!")) == TRUE)
		SetDstName(path);
	EnableButton();
}

void CText2ArrayDlg::EnableButton(void)
{
	if (m_editSrc.GetWindowTextLength() > 0)
	{	// 소스가 설정됨
		int idxSrcMode = m_comboSrcMode.GetCurSel();
		int idxSrcTextAttr = m_comboSrcTextAttr.GetCurSel();

		// enable/disable m_comboSrcMode
		m_comboSrcMode.EnableWindow(TRUE);

		// enable/disable m_comboSrcTextAttr
		if (idxSrcMode == CB_ERR)
			m_comboSrcTextAttr.EnableWindow(FALSE);
		else if (idxSrcMode == 0)
		{	// 텍스트파일
			m_comboSrcTextAttr.EnableWindow(TRUE);
		}
		else if (idxSrcMode == 1)
		{	// 바이너리파일
			m_comboSrcTextAttr.EnableWindow(FALSE);
		}
		else
			m_comboSrcTextAttr.EnableWindow(FALSE);

		// enable/disable m_editVariable
		m_editVariable.EnableWindow(TRUE);

		// enable/disable m_comboOutVarMode (단일 포인터, 포인터 배열(줄), 포인터 배열(블럭))
		if (idxSrcMode == CB_ERR || idxSrcMode == 1) // 미선택 or 바이너리파일
			m_comboOutVarMode.EnableWindow(FALSE);
		else m_comboOutVarMode.EnableWindow(TRUE); // 텍스트파일

		// enable/disable m_comboOutDataMode (문자열, 값)
		if (idxSrcMode == CB_ERR || idxSrcMode == 1) // 미선택 or 바이너리파일
			m_comboOutDataMode.EnableWindow(FALSE);
		else if (idxSrcTextAttr == CB_ERR)
			m_comboOutDataMode.EnableWindow(FALSE);
		else if (idxSrcTextAttr == 0) // 순수 텍스트
			m_comboOutDataMode.EnableWindow(TRUE);
		else
			m_comboOutDataMode.EnableWindow(FALSE);

		// enable/disable m_bDst
		m_bDst.EnableWindow(TRUE);

		// enable/disable m_comboDstFormat
		m_comboDstFormat.EnableWindow(TRUE);

		// enable/disable m_comboDstFiles
		m_comboDstFiles.EnableWindow(TRUE);

		if (m_editSrc.GetWindowTextLength() > 0 && (idxSrcMode == 1 || (idxSrcMode == 0 && idxSrcTextAttr != CB_ERR)))
		{	// Source OK
			if (m_editVariable.GetWindowTextLength() > 0 &&
				m_comboOutVarMode.GetCurSel() != CB_ERR &&
				m_comboOutDataMode.GetCurSel() != CB_ERR)
			{	// Generation OK
				if (m_editDst.GetWindowTextLength() > 0 &&
					m_comboDstFormat.GetCurSel() != CB_ERR &&
					m_comboDstFiles.GetCurSel() != CB_ERR)
				{
					m_bConv.EnableWindow(TRUE);
				}
				else m_bConv.EnableWindow(FALSE);
			}
			else m_bConv.EnableWindow(FALSE);
		}
		else m_bConv.EnableWindow(FALSE);
	}
	else
	{	// 소스가 설정 안댐
		m_comboSrcMode.EnableWindow(FALSE);
		m_comboSrcTextAttr.EnableWindow(FALSE);
		m_editVariable.EnableWindow(FALSE);
		m_comboOutVarMode.EnableWindow(FALSE);
		m_comboOutDataMode.EnableWindow(FALSE);
		m_bDst.EnableWindow(FALSE);
		m_comboDstFormat.EnableWindow(FALSE);
		m_comboDstFiles.EnableWindow(FALSE);
	}
}
void CText2ArrayDlg::OnEnChangeEditVariable()
{
	// TODO:  RICHEDIT 컨트롤인 경우 이 컨트롤은
	// CDialog::마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여
	// CRichEditCtrl().SetEventMask()를 호출하도록 OnInitDialog() 함수를 재지정하지 않으면
	// 이 알림을 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EnableButton();
}

Dz1Error CText2ArrayDlg::GetConvArg(File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	int idxSrcMode = CB_ERR;
	File2SrcConvOptPresent srcMode;
	if ((idxSrcMode = m_comboSrcMode.GetCurSel()) == CB_ERR) ERR_DLG_SET_OUT(&err, EFAULT);
	else
	{
		File2SrcConvOpt *opt = NULL;
		srcMode = idxSrcMode == 0 ? File2SrcConvOptPresent_textMode : File2SrcConvOptPresent_binMode;
		if ((arg->opt = opt = File2SrcConvOpt_new(srcMode, NULL, &err)) == NULL) ERR_DLG_OUT(&err);
		else if (opt->present == File2SrcConvOptPresent_textMode)
		{
			int idxOutVarMode = m_comboOutVarMode.GetCurSel();
			if (idxOutVarMode == CB_ERR) ERR_DLG_SET_OUT(&err, EFAULT);
			else
			{
				File2SrcConvTextOpt *tOpt = NULL;
				File2SrcVariableForm varForm = (File2SrcVariableForm)idxOutVarMode;
				if ((opt->x.textMode = tOpt = File2SrcConvTextOpt_new(NULL, varForm, &err)) == NULL) ERR_DLG_OUT(&err);
				else
				{
					int idxTextAttr = m_comboSrcTextAttr.GetCurSel();
					if (idxTextAttr == CB_ERR) ERR_DLG_SET_OUT(&err, EFAULT);
					else
					{
						File2SrcConvTextAttr *attr = NULL;
						File2SrcConvTextAttrPresent attrPresent = (File2SrcConvTextAttrPresent)idxTextAttr;
						if ((tOpt->attr = attr = File2SrcConvTextAttr_new(attrPresent, NULL, &err)) == NULL) ERR_DLG_OUT(&err);
						else if (attr->present == File2SrcConvTextAttrPresent_PlaneText)
						{
							int idxOutDataMode = m_comboOutDataMode.GetCurSel();
							if (idxOutDataMode == CB_ERR) ERR_DLG_SET_OUT(&err, EFAULT);
							else attr->x.PlaneText = (File2SrcConvTextPublish)idxOutDataMode;
						}
					}
				}
			}
		}
	}
	return err;
}

void CText2ArrayDlg::OnBnClickedButtonConv()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	CString var_name;
	m_editVariable.GetWindowText(var_name);
	File2SrcConvArg *arg = File2SrcConvArg_new(m_srcPath, m_srcName,
											   NULL, (LPSTR)(LPCSTR)var_name,
											   m_dstPath, m_dstName,
											   (File2SrcOutputMode)m_comboDstFormat.GetCurSel(), &err);
	if (arg == NULL) ERR_DLG_OUT(&err);
	else
	{
		int idxDstFiles;
		pthread_cleanup_push(File2SrcConvArg_delAndSetNull, (void *)&arg);
		if ((idxDstFiles = m_comboDstFiles.GetCurSel()) == CB_ERR) ERR_DLG_SET_OUT(&err, EFAULT);
		else if ((err = GetConvArg(arg)).code) ERR_DLG_OUT(&err);
		else if ((err = Dz1File2Src_convert(arg, (idxDstFiles+1))).code) ERR_DLG_OUT(&err);
		else MessageBox("성공");
		pthread_cleanup_pop(1); // (File2SrcConvArg_delAndSetNull, (void *)&arg);
	}
}

void CText2ArrayDlg::OnCbnSelchangeComboSrcMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int idxSrcMode = m_comboSrcMode.GetCurSel();
	if (idxSrcMode == 0) // 텍스트 파일
	{
		m_comboSrcTextAttr.SetCurSel(m_userSelSrcTextAttr);
		m_comboOutVarMode.SetCurSel(m_userSelOutVarMode);
		m_comboOutDataMode.SetCurSel(m_userSelOutDataMode);
	}
	else if (idxSrcMode == 1) // 바이너리 파일
	{
		m_comboSrcTextAttr.SetCurSel(-1);
		m_comboOutVarMode.SetCurSel(0);
		m_comboOutDataMode.SetCurSel(1);
	}
	EnableButton();
}

void CText2ArrayDlg::OnCbnSelchangeComboSrcTextAttr()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_userSelSrcTextAttr = m_comboSrcTextAttr.GetCurSel();
	if (m_userSelSrcTextAttr == CB_ERR || m_userSelSrcTextAttr == 1) // 선택 안되거나 16진수 덤프
		m_comboOutDataMode.SetCurSel(1);	// 값으로 고정
	else
		m_comboOutDataMode.SetCurSel(m_userSelOutDataMode);	// 사용자가 선택한 값으로
	EnableButton();
}

void CText2ArrayDlg::OnCbnSelchangeComboOutVarMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_userSelOutVarMode = m_comboOutVarMode.GetCurSel();
}

void CText2ArrayDlg::OnCbnSelchangeComboOutDataMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_userSelOutDataMode = m_comboOutDataMode.GetCurSel();
}
