
// dz1_code_gen_gui_dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include <dz1_asn1.h>
#include <dz1_str.h>
#include <dz1_crypt_aes.h>

#include "dz1_code_gen_gui.h"
#include "dz1_code_gen_gui_about_dlg.h"
#include "dz1_code_gen_gui_dlg.h"
#include "dz1_code_gen_tdo_dlg.h"
#include "Dz1CodeGenTodecDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDz1CodeGenGuiDlg 대화 상자
CDz1CodeGenGuiDlg::CDz1CodeGenGuiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenGuiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

static Dz1CodeGenControlInfo listCodeGenArgAll[] =
{
	Dz1CodeGenControlInfoEntry(LIST, 1),
	Dz1CodeGenControlInfoEntry(LIST, 2),
	Dz1CodeGenControlInfoEntry(LIST, 3),
	Dz1CodeGenControlInfoEntry(LIST, 4),
	{ (u32_t)-1 }
};

static Dz1CodeGenControlInfo stubCodeGenArgAll[] =
{
	Dz1CodeGenControlInfoEntry(STUB, 1),
	Dz1CodeGenControlInfoEntry(STUB, 2),
	Dz1CodeGenControlInfoEntry(STUB, 3),
	Dz1CodeGenControlInfoEntry(STUB, 4),
	{ (u32_t)-1 }
};

static Dz1CodeGenControlInfo parserCodeGenArgAll[] =
{
	Dz1CodeGenControlInfoEntry(PARSER, 1),
	Dz1CodeGenControlInfoEntry(PARSER, 2),
	Dz1CodeGenControlInfoEntry(PARSER, 3),
	Dz1CodeGenControlInfoEntry(PARSER, 4),
	{ (u32_t)-1 }
};

static Dz1CodeGenControlInfo shellCodeGenArgAll[] =
{
	Dz1CodeGenControlInfoEntry(SHELL, 1),
	Dz1CodeGenControlInfoEntry(SHELL, 2),
	Dz1CodeGenControlInfoEntry(SHELL, 3),
	Dz1CodeGenControlInfoEntry(SHELL, 4),
	{ (u32_t)-1 }
};


void CDz1CodeGenGuiDlg::CodeGenControlDDXInit(CDataExchange *pDX,
											  CodeGenControl *control,
											  Dz1CodeGenControlInfo *table,
											  u32_t idc_combo_mode)
{
	Dz1CodeGenControlInfo *i;
	CStatic *label = control->label;
	CEdit *arg = control->arg;

	DDX_Control(pDX, idc_combo_mode, control->mode);
	for (i = table; i->idStatic != -1; i++, label++, arg++)
	{
		DDX_Control(pDX, i->idStatic, *label);
		DDX_Control(pDX, i->idEdit, *arg);
	}
}

Dz1Error CDz1CodeGenGuiDlg::CodeGenControlOnInitDialog(CodeGenControl *dst,
													   StringGenFunc func, int num_max,
													   Dz1CodeGenSetupTable *table)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	int idx, i;
	CString str;
	for (i = 0; i < num_max; i++)
	{
		str = func(i);
		if ((idx = dst->mode.AddString(str)) == CB_ERR) ERR_DLG_SET_OUT(errp, EFAULT);
		else dst->mode.SetItemData(idx, (DWORD_PTR)i);
	}

	dst->mode.SetCurSel(0);
	CodeGenControlComboChanged(dst, table);
	return err;
}

void CDz1CodeGenGuiDlg::CodeGenControlComboChanged(CodeGenControl *dst, Dz1CodeGenSetupTable *_table)
{
	int i = 0;
	int idx = dst->mode.GetCurSel();
	if (idx != -1)
	{
		CString str;
		Dz1CodeGenSetupTable *table = &_table[idx];
		Dz1CodeGenSetupEntry *setup = table->setup;
		for (i = 0; setup != NULL && setup[i].label != NULL; i++)
		{
			str = setup[i].label;
			dst->label[i].SetWindowText(str);
			dst->arg[i].EnableWindow(setup[i].useThisArg);
		}
	}
	for (;i < CODE_GEN_ARG_MAX; i++)
	{
		dst->label[i].SetWindowText(_T("Not Use"));
		dst->arg[i].EnableWindow(FALSE);
	}
}

Dz1Error CDz1CodeGenGuiDlg::CodeGenControlGenerate(CodeGenControl *src, Dz1CodeGenSetupTable *_table, GeneratorFunc generator)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	int idx = src->mode.GetCurSel();
	if (idx == CB_ERR) MessageBox(_T("생성할 모드를 선택하세요"));
	else
	{
		int i;
		Dz1CodeGenSetupTable *table = &_table[idx];
		Dz1CodeGenSetupEntry *setup = table->setup;
		str_t args[CODE_GEN_ARG_MAX] = { NULL, };
		CString _args[CODE_GEN_ARG_MAX];
		for (i = 0; errp->code == 0 && setup[i].label != NULL; i++)
		{
			if (setup[i].useThisArg)
			{
				src->arg[i].GetWindowText(_args[i]);
				if (_args[i].GetLength() == 0)
				{
					CString str;
					str.Format(_T("%s 에 정확한 정보를 입력해주세요"), setup[i].label);
					MessageBox(str);
					Dz1Error_set(errp, EINVAL);
				}
				else
				{
					args[i] = (LPSTR)(LPCSTR)_args[i];
				}
			}
		}

		if (errp->code == 0)
		{
			str_t mbs_text = NULL;
			if ((*errp = generator(&mbs_text, table->type,
								   args[0], args[1], args[2], args[3])).code) ERR_DLG_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&mbs_text);

				CopyTextToClipboard(mbs_text);
				MessageBox(_T("클립보드에 복사되었습니다"));

				pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&mbs_text);
			}
		}
	}
	return err;
}

void CDz1CodeGenGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	CodeGenControlDDXInit(pDX, &m_controlListGen, listCodeGenArgAll, IDC_COMBO_LIST_MODE);
	CodeGenControlDDXInit(pDX, &m_controlStubGen, stubCodeGenArgAll, IDC_COMBO_STUB_MODE);
	CodeGenControlDDXInit(pDX, &m_controlParserGen, parserCodeGenArgAll, IDC_COMBO_PARSER_MODE);
	CodeGenControlDDXInit(pDX, &m_controlShellGen, shellCodeGenArgAll, IDC_COMBO_SHELL_MODE);
}

BEGIN_MESSAGE_MAP(CDz1CodeGenGuiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO_LIST_MODE, &CDz1CodeGenGuiDlg::OnCbnSelchangeComboListMode)
	ON_BN_CLICKED(IDC_BUTTON_LIST_CODE_GEN, &CDz1CodeGenGuiDlg::OnBnClickedButtonListCodeGen)
	ON_BN_CLICKED(IDC_BUTTON_STUB_CODE_GEN, &CDz1CodeGenGuiDlg::OnBnClickedButtonStubCodeGen)
	ON_BN_CLICKED(IDC_BUTTON1, &CDz1CodeGenGuiDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_PARSER_CODE_GEN, &CDz1CodeGenGuiDlg::OnBnClickedButtonParserCodeGen)
	ON_CBN_SELCHANGE(IDC_COMBO_PARSER_MODE, &CDz1CodeGenGuiDlg::OnCbnSelchangeComboParserMode)
	ON_CBN_SELCHANGE(IDC_COMBO_STUB_MODE, &CDz1CodeGenGuiDlg::OnCbnSelchangeComboStubMode)
	ON_CBN_SELCHANGE(IDC_COMBO_SHELL_MODE, &CDz1CodeGenGuiDlg::OnCbnSelchangeComboShellMode)
	ON_BN_CLICKED(IDC_BUTTON_SHELL_CODE_GEN, &CDz1CodeGenGuiDlg::OnBnClickedButtonShellCodeGen)
	ON_BN_CLICKED(IDC_BUTTON_TODEC, &CDz1CodeGenGuiDlg::OnBnClickedButtonTodec)
	ON_BN_CLICKED(IDC_BUTTON_KEYGEN, &CDz1CodeGenGuiDlg::OnBnClickedButtonKeygen)
END_MESSAGE_MAP()


// CDz1CodeGenGuiDlg 메시지 처리기
BOOL CDz1CodeGenGuiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CodeGenControlOnInitDialog(&m_controlListGen, (StringGenFunc)Dz1CodeGenListTypeStr, Dz1CodeGenListType_max, listCodeGenSetupTable);
	CodeGenControlOnInitDialog(&m_controlStubGen, (StringGenFunc)Dz1CodeGenStubTypeStr, Dz1CodeGenStubType_max, stubCodeGenSetupTable);
	CodeGenControlOnInitDialog(&m_controlParserGen, (StringGenFunc)Dz1CodeGenParserTypeStr, Dz1CodeGenParserType_max, parserCodeGenSetupTable);
	CodeGenControlOnInitDialog(&m_controlShellGen, (StringGenFunc)Dz1CodeGenShellTypeStr, Dz1CodeGenShellType_max, shellCodeGenSetupTable);

	CRect rectDesktop;
	CRect rectThis;
	::GetWindowRect(GetDesktopWindow()->m_hWnd, &rectDesktop);
	GetWindowRect(&rectThis);
	int left = 30;
	int top = rectDesktop.Height() - rectThis.Height();
	int margin = top >> 3;
	top -= margin;
	CRect destRect(left, top, left + rectThis.Width(), top + rectThis.Height());
	this->MoveWindow(destRect);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDz1CodeGenGuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDz1CodeGenGuiDlg::OnPaint()
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
HCURSOR CDz1CodeGenGuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDz1CodeGenGuiDlg::OnCbnSelchangeComboListMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CodeGenControlComboChanged(&m_controlListGen, listCodeGenSetupTable);
}

void CDz1CodeGenGuiDlg::OnCbnSelchangeComboStubMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CodeGenControlComboChanged(&m_controlStubGen, stubCodeGenSetupTable);
}

void CDz1CodeGenGuiDlg::OnCbnSelchangeComboParserMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CodeGenControlComboChanged(&m_controlParserGen, parserCodeGenSetupTable);
}

void CDz1CodeGenGuiDlg::OnCbnSelchangeComboShellMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CodeGenControlComboChanged(&m_controlShellGen, shellCodeGenSetupTable);
}

void CDz1CodeGenGuiDlg::CopyTextToClipboard(TCHAR *text)
{
	size_t str_size = (strlen(text) + 1) * sizeof(TCHAR);
	HGLOBAL hGlobal = GlobalAlloc(GHND | GMEM_SHARE, str_size);
	LPTSTR pGlobal = (LPTSTR)GlobalLock(hGlobal);

	memset(pGlobal, 0, str_size);
	memcpy(pGlobal, text, str_size);

	GlobalUnlock(hGlobal);

	if (!OpenClipboard()) MessageBox(_T("클립보드 열기 실패"));
	else
	{
		if (!EmptyClipboard()) MessageBox(_T("클립보드 비우기 실패"));
		else if (::SetClipboardData(CF_TEXT, hGlobal) == NULL) MessageBox(_T("클립보드 데이터 설정 실패"));
		CloseClipboard();
	}
}

void CDz1CodeGenGuiDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDz1CodeGenTdoDlg dlg;
	dlg.DoModal();
}

void CDz1CodeGenGuiDlg::OnBnClickedButtonListCodeGen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CodeGenControlGenerate(&m_controlListGen, listCodeGenSetupTable, (GeneratorFunc)Dz1CodeGen_listGen);
}

void CDz1CodeGenGuiDlg::OnBnClickedButtonStubCodeGen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CodeGenControlGenerate(&m_controlStubGen, stubCodeGenSetupTable, (GeneratorFunc)Dz1CodeGen_stubGen);
}

void CDz1CodeGenGuiDlg::OnBnClickedButtonParserCodeGen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CodeGenControlGenerate(&m_controlParserGen, parserCodeGenSetupTable, (GeneratorFunc)Dz1CodeGen_parserGen);
}


void CDz1CodeGenGuiDlg::OnBnClickedButtonShellCodeGen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CodeGenControlGenerate(&m_controlShellGen, shellCodeGenSetupTable, (GeneratorFunc)Dz1CodeGen_shellGen);
}

void CDz1CodeGenGuiDlg::OnBnClickedButtonTodec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDz1CodeGenTodecDlg dlg;
	dlg.DoModal();
}

void CDz1CodeGenGuiDlg::OnBnClickedButtonKeygen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString text = _T("\t{\r\n"), b;
	u8_t i;
	srand((unsigned int)time(NULL));
	for (i = 0; i < Dz1CryptAes256KeyByteSize; i++)
	{
		if (i == 0)
			b.Format(_T("\t\t0x%02X"), (u8_t)((rand() % 256) & 0xFF));
		else if ((i % 8) == 0)
			b.Format(_T(",\r\n\t\t0x%02X"), (u8_t)((rand() % 256) & 0xFF));
		else b.Format(_T(", 0x%02X"), (u8_t)((rand() % 256) & 0xFF));
		text += b;
	}
	text += _T("\r\n\t};\r\n");

	CopyTextToClipboard(text.GetBuffer());
	MessageBox(_T("클립보드에 복사되었습니다"));
}
