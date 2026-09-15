// dz1_task_gen_dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include <dz1_error.h>
#include <dz1_stdio.h>
#include <Dz1MfcFileSelectDlg.h>

#include <dz1_task_gen.h>
//#include <dz1_task_gen_args_util.h>
#include "dz1_task_gen_gui.h"
#include "dz1_task_gen_dlg.h"
#include "Dz1LibCollectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDz1TaskGen_dlg 대화 상자
CDz1TaskGen_dlg::CDz1TaskGen_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDz1TaskGen_dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_parentPath, 0, sizeof(TCHAR) * MY_MAX_PATH);
	memset(m_pthreadAbs, 0, sizeof(TCHAR) * MY_MAX_PATH);
	memset(m_codeconvAbs, 0, sizeof(TCHAR) * MY_MAX_PATH);
	memset(m_dimzAbs, 0, sizeof(TCHAR) * MY_MAX_PATH);
	m_list_libraries = GenArgs2LibraryInfo_new(NULL); ASSERT(m_list_libraries != NULL);

	LoadInitialPath();
}

CDz1TaskGen_dlg::~CDz1TaskGen_dlg()
{
	GenArgs2LibraryInfo_delAndSetNull(&m_list_libraries);
	CDialog::~CDialog();
}

void CDz1TaskGen_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//////////////////////////////////////////////////////////////
	// Target
	DDX_Control(pDX, IDC_COMBO_GEN_TARGET, m_comboGenTarget);
	DDX_Control(pDX, IDC_COMBO_TXT_MODE, m_comboGenTxtMode);
	DDX_Control(pDX, IDC_CHECK_INCLUDE_TEST_CODE, m_chkIncludeTestCode);
	DDX_Control(pDX, IDC_EDIT_PARENT_PATH, m_editParentPath);
	DDX_Control(pDX, IDC_BUTTON_PARENT_PATH, m_bParentPath);
	DDX_Control(pDX, IDC_EDIT_PROJ_NAME, m_editProjName);
	DDX_Control(pDX, IDC_COMBO_NAME_RULE, m_comboNameRule);
	DDX_Control(pDX, IDC_EDIT_NAME_RULE, m_editNameRule);
	// Target
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Foundation Library
	DDX_Control(pDX, IDC_EDIT_CODECONV_ROOT, m_editCodeconvRoot);
	DDX_Control(pDX, IDC_BUTTON_CODECONV_ROOT, m_bCodeconvRoot);

	DDX_Control(pDX, IDC_EDIT_DIMZ_DZ1_ROOT, m_editDimzDz1Root);
	DDX_Control(pDX, IDC_BUTTON_DIMZ_DZ1_ROOT, m_bDimzDz1Root);

	DDX_Control(pDX, IDC_COMBO_DIMZ_ENDIAN, m_comboDimzDz1Endian);
	// Foundation Library
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Additional Library
	DDX_Control(pDX, IDC_LIST_LIBRARIES, m_listLibraries);
	DDX_Control(pDX, IDC_EDIT_LIBRARY, m_editLibrary);
	DDX_Control(pDX, IDC_BUTTON_LIBRARY_ADD, m_bLibraryAdd);
	DDX_Control(pDX, IDC_BUTTON_LIBRARY_DEL, m_bLibraryDel);
	DDX_Control(pDX, IDC_BUTTON_LIBRARY_UP, m_bLibraryUp);
	DDX_Control(pDX, IDC_BUTTON_LIBRARY_DOWN, m_bLibraryDown);
	// Additional Library
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Visual Studio
	DDX_Control(pDX, IDC_CHECK_GEN_VC90_PROJ, m_chkGenVc90Proj);
	DDX_Control(pDX, IDC_CHECK_GEN_VS2022_PROJ, m_chkGenVs2022Proj);
	DDX_Control(pDX, IDC_CHECK_GEN_SOLUTION, m_chkGenSolution);

	DDX_Control(pDX, IDC_EDIT_PTHREAD_ROOT, m_editPthreadRoot);
	DDX_Control(pDX, IDC_BUTTON_PTHREAD_ROOT, m_bPthreadRoot);
	// Visual Studio
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Command-Line Build
	DDX_Control(pDX, IDC_CHECK_GEN_GCC_MAKEFILE, m_chkGenGnuMakefile);
	// Command-Line Build
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Global Control
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bSave);
	DDX_Control(pDX, IDC_BUTTON_GENERATE, m_bGenerate);
	// Global Control
	//////////////////////////////////////////////////////////////
}

BEGIN_MESSAGE_MAP(CDz1TaskGen_dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	//////////////////////////////////////////////////////////////
	// Target
	ON_BN_CLICKED(IDC_BUTTON_PARENT_PATH, OnBnClickedButtonParentPath)
	ON_EN_KILLFOCUS(IDC_EDIT_PROJ_NAME, OnEnKillfocusEditProjName)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_RULE,  OnCbnSelchangeComboNameRule)
	// Target
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Foundation Library
	ON_BN_CLICKED(IDC_BUTTON_CODECONV_ROOT, OnBnClickedButtonCodeconvRoot)
	ON_BN_CLICKED(IDC_BUTTON_DIMZ_DZ1_ROOT, OnBnClickedButtonDimzRoot)
	// Foundation Library
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Additional Library
	ON_NOTIFY(LVN_ITEMCHANGED,	IDC_LIST_LIBRARIES, OnLvnItemchangedListLibraries)
	ON_NOTIFY(NM_CLICK,			IDC_LIST_LIBRARIES,		   OnNMClickListLibraries)
	ON_NOTIFY(NM_DBLCLK,		IDC_LIST_LIBRARIES,		  OnNMDblclkListLibraries)
	ON_BN_CLICKED(IDC_BUTTON_LIBRARY_ADD, OnBnClickedButtonAddProject)
	ON_BN_CLICKED(IDC_BUTTON_LIBRARY_DEL, OnBnClickedButtonDeletePriject)
	// Additional Library
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Command-Line Build
	// Command-Line Build
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Visual Studio
	ON_BN_CLICKED(IDC_CHECK_GEN_VC90_PROJ, OnBnClickedCheckGenVc90Proj)
	ON_BN_CLICKED(IDC_CHECK_GEN_VS2022_PROJ, OnBnClickedCheckGenVs2022Proj)
	ON_BN_CLICKED(IDC_BUTTON_PTHREAD_ROOT, OnBnClickedButtonPthreadRoot)
	// Visual Studio
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Global Control
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnBnClickedButtonGenerate)
	// Global Control
	//////////////////////////////////////////////////////////////
	ON_BN_CLICKED(IDC_BUTTON_LIBRARY_UP, &CDz1TaskGen_dlg::OnBnClickedButtonLibraryUp)
	ON_BN_CLICKED(IDC_BUTTON_LIBRARY_DOWN, &CDz1TaskGen_dlg::OnBnClickedButtonLibraryDown)
END_MESSAGE_MAP()


// CDz1TaskGen_dlg 메시지 처리기

BOOL CDz1TaskGen_dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//////////////////////////////////////////////////////////////
	// Target
	m_comboGenTarget.OnInitControl();
	m_comboGenTarget.SetCurValue( Dz1GenTarget_Task );

	m_comboGenTxtMode.OnInitControl();
	m_comboGenTxtMode.SetCurValue( Dz1GenTextMode_DOS );

	m_comboNameRule.OnInitControl();
	m_comboNameRule.SetCurValue( GenArgs2Naming_canonical );
	// Target
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Foundation Library
	m_comboDimzDz1Endian.OnInitControl();
	m_comboDimzDz1Endian.SetCurValue( Dz1TaskGenEndian_Little );
	// Foundation Library
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Additional Library
	m_listLibraries.OnInitControl();
	m_listLibraries.Load(m_list_libraries, NULL);
	// Additional Library
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Command-Line Build
	// Command-Line Build
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Visual Studio
	// Visual Studio
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	// Global Control
	// Global Control
	//////////////////////////////////////////////////////////////
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CDz1TaskGen_dlg::OnPaint() 
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
HCURSOR CDz1TaskGen_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDz1TaskGen_dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveInitialPath();
}

////////////////////////////////////////////////////////////////////////////////
// Target
static void _set_relative_path(CEdit &dst, Dz1Str fromPath, Dz1Str toPath)
{
	TCHAR temp[MY_MAX_PATH] = { 0, };
	if (_get_relative_path(temp, MY_MAX_PATH, fromPath, toPath, NULL) == FALSE) dst.SetWindowText(_T("#error"));
	else dst.SetWindowText(temp);
}
static void _chk_and_set_relative_path(CEdit &dst, TCHAR *buf, size_t buf_sz, Dz1Str fromPath, Dz1Str toPath, Dz1Str toChkPath)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (buf == NULL || Dz1Str_isVoid(fromPath) || Dz1Str_isVoid(toPath) || Dz1Str_isVoid(toChkPath)) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1PathStr_concat(buf, buf_sz, toPath, toChkPath, NULL)).code) ERR_OUT(errp);
	else if (Dz1Dir_isExist(buf) == FALSE) ERR_SET_OUT(errp, ENOENT);
	else Dz1Error_set(errp, 0);

	if (errp->code)
	{
		buf[0] = 0;
		dst.SetWindowText(_T(""));
	}
	else _set_relative_path(dst, fromPath, buf);
}

void CDz1TaskGen_dlg::ProjectRootUpdate()
{
	if (SetProjRoot())
	{
	}

	// 부모 폴더 아래 codeconv 가 있는지
	if (Dz1Str_isVoid(m_codeconvAbs))
		_chk_and_set_relative_path(m_editCodeconvRoot, m_codeconvAbs, MY_MAX_PATH, m_projRootAbs, m_parentPath, Dz1T("codeconv"));
	else _set_relative_path(m_editCodeconvRoot, m_projRootAbs, m_codeconvAbs);

	// 부모 폴더 아래 dimz 가 있는지
	if (Dz1Str_isVoid(m_dimzAbs))
		_chk_and_set_relative_path(m_editDimzDz1Root, m_dimzAbs, MY_MAX_PATH, m_projRootAbs, m_parentPath, Dz1T("dimz"));
	else _set_relative_path(m_editDimzDz1Root, m_projRootAbs, m_dimzAbs);

	m_listLibraries.SetBiasPath(m_projRootAbs);
	m_listLibraries.RefreshAll();

	EnableRootButtons();
	EnableGenButton();
	OnCbnSelchangeComboNameRule();
	EnableGenSolutionChk();
}

void CDz1TaskGen_dlg::OnBnClickedButtonParentPath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[MY_MAX_PATH] = { 0, };
	if (Dz1MfcPathSelectDlg(this->m_hWnd, m_initialPath, path, _T("프로젝트를 생성할 부모 폴더를 선택하세요")) ==TRUE)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);

		Dz1STRCPY(m_initialPath, path);
		Dz1STRCPY(m_parentPath, path);
		m_editParentPath.SetWindowText(m_parentPath);

		ProjectRootUpdate();
	}
}

void CDz1TaskGen_dlg::OnEnKillfocusEditProjName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ProjectRootUpdate();
}

void CDz1TaskGen_dlg::OnCbnSelchangeComboNameRule()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GenArgs2Naming rule = m_comboNameRule.GetCurSelValue();
	CString projName;
	m_editProjName.GetWindowText(projName);
	if (rule != GenArgs2Naming_max && projName.IsEmpty() == FALSE)
	{
		CString str;
		TCHAR file_name[64] = { 0, }, struct_name[64] = { 0, };
		_getRuledName(file_name, 64, projName.GetBuffer(), Dz1T("def_util"), rule, NULL);
		_getStructureName(struct_name, 64, projName.GetBuffer(), Dz1T("def_util"), NULL);
		str.Format(_T("file : %s, struct : %s"), file_name, struct_name);
		m_editNameRule.SetWindowText(str);
	}
	else m_editNameRule.SetWindowText(_T(""));
}
// Target
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Foundation Library
void CDz1TaskGen_dlg::OnBnClickedButtonCodeconvRoot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[MY_MAX_PATH] = { 0, };
	if (Dz1MfcPathSelectDlg(this->m_hWnd, m_initialPath, path, _T("codeconv library의 최상위 경로를 선택하세요")) ==TRUE)
	{
		Dz1STRCPY(m_initialPath, path);
		Dz1STRCPY(m_codeconvAbs, path);
		_set_relative_path(m_editCodeconvRoot, m_parentPath, m_codeconvAbs);
		EnableGenButton();
	}
}

void CDz1TaskGen_dlg::OnBnClickedButtonDimzRoot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[MY_MAX_PATH] = { 0, };
	if (Dz1MfcPathSelectDlg(this->m_hWnd, m_initialPath, path, _T("DIMZ library의 최상위 경로를 선택하세요")) ==TRUE)
	{
		Dz1STRCPY(m_initialPath, path);
		Dz1STRCPY(m_dimzAbs, path);
		_set_relative_path(m_editDimzDz1Root, m_parentPath, m_dimzAbs);
		EnableGenButton();
	}
}
// Foundation Library
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Additional Libraries
void CDz1TaskGen_dlg::ListLibrariesEvent(int *_idx, int *_cnt)
{
	int cnt;
	if (_cnt != NULL) cnt = *_cnt;
	else cnt = m_listLibraries.GetSelectedCount();

	int idx;
	if (_idx != NULL) idx = *_idx;
	else
	{
		POSITION pos = m_listLibraries.GetFirstSelectedItemPosition();
		idx = m_listLibraries.GetNextSelectedItem(pos);
	}

	if (cnt == 0)
	{
		if (idx != -1) ListLibrariesSelOne(idx);
		else ListLibrariesSelNone();
	}
	else if (cnt == 1) ListLibrariesSelOne(idx);
	else ListLibrariesSelMany(idx, cnt);
}

void CDz1TaskGen_dlg::ListLibrariesSelNone()
{
	// no item Selected Implementation
	m_bLibraryDel.EnableWindow(FALSE);
	m_editLibrary.SetWindowText(_T(""));
}

static Dz1Error _concat_projects(void *ptr, GenArgs2VisualStudioEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CString *dst = (CString *)ptr;
	if (!dst->IsEmpty()) *dst += _T(", ");
	*dst += GenArgs2VisualStudioVerStr(p->ver);
	return err;
}

void CDz1TaskGen_dlg::ListLibrariesSelOne(int idx)
{
	// Only one item Selected Implementation
	GenArgs2LibraryEntry *node = m_listLibraries.GetElement(idx);
	if (node == NULL) ListLibrariesSelNone();
	else
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		m_bLibraryDel.EnableWindow(TRUE);
		CString str;
		if ((*errp = node->projects->travel(node->projects, _concat_projects, (void *)&str)).code) str = _T("#error");
		m_editLibrary.SetWindowText(str);
		m_bLibraryUpEnable(TRUE, idx);
		m_bLibraryDownEnable(TRUE, idx);
	}
}

void CDz1TaskGen_dlg::ListLibrariesSelMany(int idx, int cnt)
{
	// many item Selected Implementation
	m_bLibraryDel.EnableWindow(TRUE);
	m_editLibrary.SetWindowText(_T(""));
	m_bLibraryUpEnable(FALSE);
	m_bLibraryDownEnable(FALSE);
}

void CDz1TaskGen_dlg::OnLvnItemchangedListLibraries(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	if ((pNMLV->uNewState & (LVIS_FOCUSED | LVIS_SELECTED)) == (LVIS_FOCUSED | LVIS_SELECTED))
		ListLibrariesEvent(&pNMLV->iItem);
}

void CDz1TaskGen_dlg::OnNMClickListLibraries(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	if (pNMItemActivate->iItem == -1) ListLibrariesSelNone();
}

void CDz1TaskGen_dlg::OnNMDblclkListLibraries(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	GenArgs2LibraryEntry *node = m_listLibraries.GetElement(pNMItemActivate->iItem, NULL);
	if (node != NULL)
	{
		CString str = _T("라이브러리 수정");
		CDz1LibCollectionDlg dlg(str, m_parentPath, &node);

		if (dlg.DoModal() == IDOK)
			m_listLibraries.RefreshRow(pNMItemActivate->iItem);
	}
}

void CDz1TaskGen_dlg::OnBnClickedButtonAddProject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GenArgs2LibraryEntry *ret = NULL;
	CString str = _T("라이브러리 추가");
	CDz1LibCollectionDlg dlg(str, m_parentPath, &ret);

	if (dlg.DoModal() == IDOK)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		pthread_cleanup_push(GenArgs2LibraryEntry_delAndSetNull, (void *)&ret);

		if ((*errp = m_listLibraries.InsertRow(&ret)).code) ERR_DLG_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (GenArgs2LibraryEntry_delAndSetNull, (void *)&ret);
	}
}

void CDz1TaskGen_dlg::OnBnClickedButtonDeletePriject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = m_listLibraries.GetFirstSelectedItemPosition();
	int idx = m_listLibraries.GetNextSelectedItem(pos);
	while (m_listLibraries.GetElement(idx) != NULL)
	{
		m_listLibraries.RemoveRow(idx);

		pos = m_listLibraries.GetFirstSelectedItemPosition();
		idx = m_listLibraries.GetNextSelectedItem(pos);
	}
	m_listLibraries.Reordering();
}

void CDz1TaskGen_dlg::m_bLibraryUpEnable(bool_t en, int idx)
{
	if (idx == -1) m_bLibraryDown.EnableWindow(en);
	else if (en)
	{
		if (idx == 0) m_bLibraryUp.EnableWindow(FALSE);
		else m_bLibraryUp.EnableWindow(TRUE);
	}
	else m_bLibraryUp.EnableWindow(en);
}

void CDz1TaskGen_dlg::OnBnClickedButtonLibraryUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int idx = m_listLibraries.GetCurSelIdx();
	if (idx == 0) MessageBox(_T("It's first"));
	else
	{
		int prev = idx - 1;
		m_listLibraries.SwitchOrder(idx, prev);
	}
}

void CDz1TaskGen_dlg::m_bLibraryDownEnable(bool_t en, int idx)
{
	if (idx == -1) m_bLibraryDown.EnableWindow(en);
	else if (en)
	{
		int cnt = m_listLibraries.GetItemCount();
		if (cnt == 0 || idx == (cnt - 1)) m_bLibraryDown.EnableWindow(FALSE);
		else m_bLibraryDown.EnableWindow(TRUE);
	}
	else m_bLibraryDown.EnableWindow(en);
}

void CDz1TaskGen_dlg::OnBnClickedButtonLibraryDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int cnt = m_listLibraries.GetItemCount();
	if (cnt == 0) MessageBox(_T("No Entry"));
	else
	{
		int idx = m_listLibraries.GetCurSelIdx();
		if (idx == (cnt - 1)) MessageBox(_T("It's last"));
		else
		{
			int next = idx + 1;
			m_listLibraries.SwitchOrder(idx, next);
		}
	}
}
// Additional Libraries
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Visual Studio
void CDz1TaskGen_dlg::OnBnClickedCheckGenVc90Proj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EnableGenSolutionChk();
}

void CDz1TaskGen_dlg::OnBnClickedCheckGenVs2022Proj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EnableGenSolutionChk();
}

void CDz1TaskGen_dlg::OnBnClickedButtonPthreadRoot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[MY_MAX_PATH] = { 0, };
	if (Dz1MfcPathSelectDlg(this->m_hWnd, m_initialPath, path, _T("pthread library 위치를 선택하세요")) ==TRUE)
	{
		Dz1STRCPY(m_initialPath, path);
		Dz1STRCPY(m_pthreadAbs, path);
		if (Dz1Str_isVoid(m_projRootAbs) == FALSE)
			_set_relative_path(m_editPthreadRoot, m_projRootAbs, m_pthreadAbs);

		EnableGenButton();
	}
}
// Visual Studio
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Global Control
static Dz1Str file_filter = _T("Dz1TaskGen File(*.dz1start2)|*.dz1start2|");
static Dz1Str file_ext = _T("dz1start2");
void CDz1TaskGen_dlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DZ1_ERROR_SAFE_VAR(errp, err);

	TCHAR path[4096], name[4096];
	if (Dz1MfcFileSelectDlg(this, TRUE, m_parentPath, NULL, file_filter, file_ext, path, name) == TRUE)
	{
		Dz1Stream *st = Dz1Stream_openFile2(path, name, Dz1StreamFileMode_RD, errp);
		if (st == NULL) ERR_DLG_OUT(errp);
		else
		{
			GenArgs2 *args = NULL;
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&st);
			if ((args = GenArgs2_fromStream(st, NULL, Dz1IOStreamEndian_big, errp)) == NULL) ERR_DLG_OUT(errp);
			else
			{
				pthread_cleanup_push(GenArgs2_delAndSetNull, (void *)&args);

				ApplyGenArgs(args);
				Dz1Error_set(errp, 0);

				pthread_cleanup_pop(1); // (GenArgs2_delAndSetNull, (void *)&args);
			}
			pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void *)&st);
		}
	}
}

void CDz1TaskGen_dlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DZ1_ERROR_SAFE_VAR(errp, err);

	GenArgs2 *args = CreateGenArgs();
	if (args == NULL) ERR_DLG_OUT(&err);
	else
	{
		CString str;
		TCHAR path[4096], name[4096];
		pthread_cleanup_push(GenArgs2_delAndSetNull, (void *)&args);

		m_editProjName.GetWindowText(str);
		str += _T(".dz1start2");

		if (Dz1MfcFileSelectDlg(this, FALSE, m_parentPath, str.GetBuffer(), file_filter, file_ext, path, name) == TRUE)
		{
			Dz1Stream *st = Dz1Stream_openFile2(path, name, Dz1StreamFileMode_WR, errp);
			if (st == NULL) ERR_DLG_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&st);
				if ((*errp = GenArgs2_toStream(args, st, Dz1IOStreamEndian_big, NULL)).code) ERR_DLG_OUT(errp);
				else
				{
					MessageBox("Saved");
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void *)&st);
			}
		}
		pthread_cleanup_pop(1); // (GenArgs2_delAndSetNull, (void *)&args);
	}
}

void CDz1TaskGen_dlg::OnBnClickedButtonGenerate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DZ1_ERROR_SAFE_VAR(errp, err);

	GenArgs2 *args = CreateGenArgs();
	if (args == NULL) ERR_DLG_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2_delAndSetNull, (void *)&args);

		if (Dz1TaskGen2(args, errp) == FALSE) ERR_DLG_OUT(errp);
		else MessageBox("Project Generated");

		pthread_cleanup_pop(1); // (GenArgs2_delAndSetNull, (void *)&args);
	}
}
// Global Control
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Utility
GenArgs2 *CDz1TaskGen_dlg::CreateGenArgs(void)
{
	GenArgs2 *ret = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

	// Target : Task | Library
	Dz1GenTarget gen_target_type = m_comboGenTarget.GetCurSelValue();
	if (gen_target_type == Dz1GenTarget_max) { ERR_SET_OUT(errp, EINVAL); MessageBox(_T("Target Type")); return NULL; }

	// Target : Text Mode : UNIX | DOS
	Dz1GenTextMode txt_mode = m_comboGenTxtMode.GetCurSelValue();
	if (txt_mode == Dz1GenTextMode_max) { ERR_SET_OUT(errp, EINVAL); MessageBox(_T("Text Mode")); return NULL; }

	// Target : Generate Test Main
	bool_t gen_test_main = FALSE;
	if (m_chkIncludeTestCode.IsWindowEnabled() && m_chkIncludeTestCode.GetCheck()) gen_test_main = TRUE;

	CString gen_parent_path;
	m_editParentPath.GetWindowText(gen_parent_path);
	if (gen_parent_path.IsEmpty()) { ERR_SET_OUT(errp, EINVAL); MessageBox(_T("Parent Path")); return NULL; }

	// Target : Project Name
	CString gen_target_name;
	m_editProjName.GetWindowText(gen_target_name);
	if (gen_target_name.IsEmpty()) { ERR_SET_OUT(errp, EINVAL); MessageBox(_T("Target Name")); return NULL; }

	// Target : Name Rule
	GenArgs2Naming name_rule = m_comboNameRule.GetCurSelValue();
	if (name_rule == GenArgs2Naming_max) { ERR_SET_OUT(errp, EINVAL); MessageBox(_T("Naming Rule")); return NULL; }

	// Foundation Library : DZ1 Endian
	Dz1TaskGenEndian endian = m_comboDimzDz1Endian.GetCurSelValue();
	if (endian == Dz1TaskGenEndian_max) { ERR_SET_OUT(errp, EINVAL); MessageBox(_T("Endian을 설정하세요")); return NULL; }

	// Command-Line Build : GNUMake
	bool_t gen_makefile = FALSE;
	if (m_chkGenGnuMakefile.GetCheck()) gen_makefile = TRUE;

	GenArgs2 *args = GenArgs2_new(gen_parent_path.GetBuffer(),
								  gen_target_type, 
								  gen_target_name.GetBuffer(),
								  gen_test_main, 
								  gen_makefile,
								  NULL,							// gen_studio
								  txt_mode, endian, name_rule, 
								  m_codeconvAbs, m_dimzAbs,
								  NULL,							// libraries
								  errp); 
	if (args == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(GenArgs2_delAndSetNull, (void *)&args);

		if ((args->libraries = GenArgs2LibraryInfo_clone(m_list_libraries, errp)) == NULL) ERR_DLG_OUT(errp);
		else
		{
			// Visual Studio : vc90, vs2022, solution
			u32_t gen_project = 0;

			if (m_chkGenVc90Proj.GetCheck()) gen_project |= DZ1_TASK_GEN_VC90;
			if (m_chkGenVs2022Proj.GetCheck()) gen_project |= DZ1_TASK_GEN_VS2022;
			if (m_chkGenSolution.IsWindowEnabled() && m_chkGenSolution.GetCheck()) gen_project |= DZ1_TASK_GEN_SOLUTION;

			if (gen_project != 0)
			{
				if (Dz1Str_isVoid(m_pthreadAbs)) { ERR_SET_OUT(errp, EINVAL); MessageBox(_T("pthread")); }
				else if ((args->gen_studios = GenArgs2VisualStudio_new(m_pthreadAbs, gen_project, errp)) == NULL) ERR_DLG_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(err.code); // (GenArgs2_delAndSetNull, (void *)&args);
	}
	return args;
}

void CDz1TaskGen_dlg::ApplyGenArgs(GenArgs2 *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	// Target : Task | Library
	m_comboGenTarget.SetCurValue(src->gen_target_type);

	// Target : Text Mode : UNIX | DOS
	m_comboGenTxtMode.SetCurValue(src->txt_mode);

	// Target : Generate Test Main
	m_chkIncludeTestCode.SetCheck(src->gen_test_main);

	// Target : Parent Path
	Dz1STRCPY(m_parentPath, src->gen_parent_path);
	m_editParentPath.SetWindowText(m_parentPath);
	
	// Target : Project Name
	m_editProjName.SetWindowText(src->gen_target_name);

	SetProjRoot();

	// Target : Name Rule
	m_comboNameRule.SetCurValue(src->name_rule);

	// Foundation Library : CodeConv Path
	Dz1STRCPY(m_codeconvAbs, src->codeconv_root);
	_set_relative_path(m_editCodeconvRoot, m_parentPath, m_codeconvAbs);

	// Foundation Library : DimzDz1 Path
	Dz1STRCPY(m_dimzAbs, src->dimz_root);
	_set_relative_path(m_editDimzDz1Root, m_parentPath, m_dimzAbs);

	// Foundation Library : DimzDZ1 Endian
	m_comboDimzDz1Endian.SetCurValue(src->endian);

	// Additional Libraries
	m_listLibraries.Unload();
	GenArgs2LibraryInfo_delAndSetNull(&m_list_libraries);
	m_list_libraries = src->libraries;
	src->libraries = NULL;

	m_listLibraries.SetBiasPath(m_projRootAbs);
	m_listLibraries.Load(m_list_libraries, NULL);
	ListLibrariesSelNone();

	// Visual Studio : vc90, vs2022, solution
	GenArgs2VisualStudio *gen_studios = src->gen_studios;
	if (gen_studios != NULL)
	{
		u32_t gen_project = gen_studios->gen_project;
		if (gen_project & DZ1_TASK_GEN_VC90)		m_chkGenVc90Proj.SetCheck(TRUE); else m_chkGenVc90Proj.SetCheck(FALSE);			// VC90
		if (gen_project & DZ1_TASK_GEN_VS2022)		m_chkGenVs2022Proj.SetCheck(TRUE); else m_chkGenVs2022Proj.SetCheck(FALSE);		// VS2022
		if (gen_project & DZ1_TASK_GEN_SOLUTION)	m_chkGenSolution.SetCheck(TRUE); else m_chkGenSolution.SetCheck(FALSE);			// Solution

		// PThread Path
		Dz1STRCPY(m_pthreadAbs, gen_studios->pthread_root);
	}

	// Command-Line Build: GNUMake
	m_chkGenGnuMakefile.SetCheck(src->gen_makefile);	// GNUMakefile

	ProjectRootUpdate();
}

void CDz1TaskGen_dlg::LoadInitialPath(void)
{
	CDz1TaskGen_app *app = (CDz1TaskGen_app *)AfxGetApp();
	Dz1MfcProgInfo *info = app->m_prog_info;
	FILE *fp = Dz1FileStream_open3(info->path, info->name, _T("path"), _T("rb"), NULL);
	if (fp == NULL) Dz1STRCPY(m_initialPath, info->path);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if ((sz = (ssize_t)fread(m_initialPath, sizeof(TCHAR), MY_MAX_PATH, fp)) <= 0)
			Dz1STRCPY(m_initialPath, info->path);
		else m_initialPath[sz] = 0;

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
}

void CDz1TaskGen_dlg::SaveInitialPath(void)
{
	CDz1TaskGen_app *app = (CDz1TaskGen_app *)AfxGetApp();
	Dz1MfcProgInfo *info = app->m_prog_info;
	FILE *fp = Dz1FileStream_open3(info->path, info->name, _T("path"), _T("wb"), NULL);
	if (fp != NULL)
	{
		size_t len = Dz1STRLEN(m_initialPath);
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		fwrite(m_initialPath, sizeof(TCHAR), len, fp);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
}

bool_t CDz1TaskGen_dlg::SetProjRoot()
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CString projName;
	m_editProjName.GetWindowText(projName);
	if (Dz1Str_isVoid(m_parentPath) == TRUE || projName.IsEmpty())
	{
		m_projRootAbs[0] = 0;
		Dz1Error_set(errp, EINVAL);
	}
	else if ((*errp = Dz1PathStr_concat(m_projRootAbs, MY_MAX_PATH, m_parentPath, projName.GetBuffer(), NULL)).code)
	{
		m_projRootAbs[0] = 0;
		ERR_OUT(errp);
	}
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enable / Disable
void CDz1TaskGen_dlg::EnableRootButtons(void)
{	// Parent Path 와 Project Name 이 설정되면 버튼 활성화
	if (m_editParentPath.GetWindowTextLength() > 0 && m_editProjName.GetWindowTextLength() > 0)
	{
		m_bCodeconvRoot.EnableWindow(TRUE);
		m_bDimzDz1Root.EnableWindow(TRUE);
		m_listLibraries.EnableWindow(TRUE);
		m_bLibraryAdd.EnableWindow(TRUE);
	}
	else
	{
		m_bCodeconvRoot.EnableWindow(FALSE);
		m_bDimzDz1Root.EnableWindow(FALSE);
		m_listLibraries.EnableWindow(FALSE);
		m_bLibraryAdd.EnableWindow(FALSE);
		m_bLibraryDel.EnableWindow(FALSE);
	}
}

void CDz1TaskGen_dlg::EnableGenButton(void)
{	// Check mandatory field
	if (m_editParentPath.GetWindowTextLength() > 0 &&
		m_editProjName.GetWindowTextLength() > 0 &&
		m_editCodeconvRoot.GetWindowTextLength() > 0 &&
		m_editDimzDz1Root.GetWindowTextLength() > 0)
	{
		m_bGenerate.EnableWindow(TRUE);
		m_bSave.EnableWindow(TRUE);
	}
	else
	{
		m_bGenerate.EnableWindow(FALSE);
		m_bSave.EnableWindow(FALSE);
	}
}

void CDz1TaskGen_dlg::EnableGenSolutionChk(void)
{
	bool_t solution = m_chkGenVc90Proj.GetCheck() || m_chkGenVs2022Proj.GetCheck() ? TRUE : FALSE;
	m_chkGenSolution.EnableWindow(solution);

	if (Dz1Str_isVoid(m_projRootAbs) == FALSE)
	{
		m_bPthreadRoot.EnableWindow(solution);
		if (solution)
		{
			if (Dz1Str_isVoid(m_projRootAbs) == FALSE)
			{
				if (Dz1Str_isVoid(m_pthreadAbs))
					_chk_and_set_relative_path(m_editPthreadRoot, m_pthreadAbs, MY_MAX_PATH, m_projRootAbs, m_parentPath, Dz1T("pthreads.2"));
				else _set_relative_path(m_editPthreadRoot, m_projRootAbs, m_pthreadAbs);
			}
		}
	}
	else
	{
		m_bPthreadRoot.EnableWindow(FALSE);
		m_editPthreadRoot.SetWindowText(_T("#error"));
	}
}
// Enable / Disable
///////////////////////////////////////////////////////////////////////////////
