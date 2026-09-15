// Dz1SelectionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include <dz1_stdio.h>
#include <dz1_str.h>
#include <Dz1MfcFileSelectDlg.h>
#include "dz1_task_gen_gui.h"
#include "Dz1LibCollectionDlg.h"

#include "Dz1ProjSelDlg.h"

// CDz1SelectionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1LibCollectionDlg, CDialog)
CDz1LibCollectionDlg::CDz1LibCollectionDlg(CString &title, Dz1Str initialPath, GenArgs2LibraryEntry **ret, CWnd* pParent /*=NULL*/)
	: CDialog(CDz1LibCollectionDlg::IDD, pParent)
{
	m_ret = ret; ASSERT(m_ret != NULL);
	m_dst = NULL;
	m_title = title;

	Dz1STRCPY(m_initialPath, initialPath);
}

CDz1LibCollectionDlg::~CDz1LibCollectionDlg()
{
	GenArgs2LibraryEntry_delAndSetNull(&m_dst);
	CDialog::~CDialog();
}

void CDz1LibCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ROOT_PATH, m_editRootPath);

	DDX_Control(pDX, IDC_EDIT_INCLUDE_PATH, m_editIncludePath);
	DDX_Control(pDX, IDC_BUTTON_INCLUDE_PATH, m_btnIncludePath);

	DDX_Control(pDX, IDC_EDIT_LIBRARY_PATH, m_editLibraryPath);
	DDX_Control(pDX, IDC_BUTTON_LIBRARY_PATH, m_btnLibraryPath);

	DDX_Control(pDX, IDC_LIST_PROJECTS, m_listProjects);
	DDX_Control(pDX, IDC_BUTTON_PROJECT_ADD, m_bAddProject);
	DDX_Control(pDX, IDC_BUTTON_PROJECT_DEL, m_bDeleteProject);
}


BEGIN_MESSAGE_MAP(CDz1LibCollectionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ROOT_PATH, &CDz1LibCollectionDlg::OnBnClickedButtonRootPath)
	ON_BN_CLICKED(IDC_BUTTON_INCLUDE_PATH, &CDz1LibCollectionDlg::OnBnClickedButtonIncludePath)
	ON_BN_CLICKED(IDC_BUTTON_LIBRARY_PATH, &CDz1LibCollectionDlg::OnBnClickedButtonLibraryPath)
	ON_BN_CLICKED(IDC_BUTTON_PROJECT_ADD, &CDz1LibCollectionDlg::OnBnClickedButtonAddProject)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROJECTS, &CDz1LibCollectionDlg::OnNMClickListProjects)
	ON_BN_CLICKED(IDC_BUTTON_PROJECT_DEL, &CDz1LibCollectionDlg::OnBnClickedButtonDeleteProject)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDz1LibCollectionDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CDz1SelectionDlg 메시지 처리기입니다.

BOOL CDz1LibCollectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetWindowText(m_title);
	
	m_listProjects.OnInitControl();

	GenArgs2LibraryEntry *e = (*m_ret);
	if (e != NULL)
	{	// 수정
		m_dst = GenArgs2LibraryEntry_clone(e, NULL);
		ASSERT(m_dst != NULL);

		CString str;

		str.Format(_T("라이브러리 수정 : %s"), m_dst->name);
		this->SetWindowText(str);

		m_editRootPath.SetWindowText(m_dst->path_root_abs);
		m_editIncludePath.SetWindowText(m_dst->root2inc_path);
		m_editLibraryPath.SetWindowText(m_dst->root2lib_path);
	}
	else
	{	// 신규
		m_dst = GenArgs2LibraryEntry_new(NULL, NULL, NULL, NULL, NULL, NULL);
		ASSERT(m_dst != NULL);
		m_btnIncludePath.EnableWindow(FALSE);
		m_btnLibraryPath.EnableWindow(FALSE);
		m_bAddProject.EnableWindow(FALSE);
	}
	m_listProjects.Load(m_dst->projects, NULL);
	ListProjectsEvent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

////////////////////////////////////////////////////////////////////////////////
// Root Path
void CDz1LibCollectionDlg::SetIncPath(Dz1Str lib_root_abs)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Str_delAndSetNull(&m_dst->root2inc_path);
	if (Dz1Dir_isExist2(lib_root_abs, Dz1T("include")))
	{
		m_dst->root2inc_path = Dz1Str_dup(Dz1T("include"), NULL);
		ASSERT(m_dst->root2inc_path != NULL);
		m_editIncludePath.SetWindowText(m_dst->root2inc_path);
	}
	else m_editIncludePath.SetWindowText(Dz1T(""));
}

void CDz1LibCollectionDlg::SetLibPath(Dz1Str lib_root_abs)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Str_delAndSetNull(&m_dst->root2lib_path);
	if (Dz1Dir_isExist2(lib_root_abs, Dz1T("lib")))
	{
		m_dst->root2lib_path = Dz1Str_dup(Dz1T("lib"), NULL);
		ASSERT(m_dst->root2lib_path != NULL);
		m_editLibraryPath.SetWindowText(m_dst->root2lib_path);
	}
	else m_editLibraryPath.SetWindowText(Dz1T(""));
}

Dz1Error CDz1LibCollectionDlg::ChkAndAddProj(TCHAR *lib_root_abs, GenArgs2VisualStudioVerSupport ver)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LoadProjectMap *map = LoadProjectMap_find((GenArgs2VisualStudioVer)ver);
	if (map == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TCHAR middle_path[64], *proj_name = Dz1STRRCHR(lib_root_abs, DIR_SEP);
		TCHAR proj_name_ext[256] = { 0, };
		if (proj_name == NULL) proj_name = lib_root_abs; else proj_name++;

		if ((*errp = Dz1PathStr_concat(middle_path, 64, Dz1T("project"), map->branch_path, NULL)).code) ERR_OUT(errp);
		else if (_Dz1FileName_concatNameExt(Dz1ArrParam(TCHAR, proj_name_ext), proj_name, map->proj_ext, errp) == FALSE) ERR_OUT(errp);
		else if (m_listProjects.AddRow((GenArgs2VisualStudioVer)ver, lib_root_abs, middle_path, proj_name_ext, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

void CDz1LibCollectionDlg::OnBnClickedButtonRootPath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR lib_root_path[4096];
	if (Dz1MfcPathSelectDlg(this->m_hWnd, m_initialPath, lib_root_path, _T("Library Root 위치를 선택하세요")) ==TRUE)
	{
		Dz1STRCPY(m_initialPath, lib_root_path);

		m_editRootPath.SetWindowText(lib_root_path);

		Dz1Str_delAndSetNull(&m_dst->path_root_abs);
		m_dst->path_root_abs = Dz1Str_dup(lib_root_path, NULL);
		ASSERT(m_dst->path_root_abs != NULL);

		TCHAR *np = Dz1STRRCHR(m_dst->path_root_abs, DIR_SEP);
		if (np == NULL) np = m_dst->path_root_abs;
		else np++;

		m_dst->name = Dz1Str_dup(np, NULL); ASSERT(m_dst->name != NULL);

		SetIncPath(lib_root_path);
		SetLibPath(lib_root_path);
		ChkAndAddProj(lib_root_path, GenArgs2VisualStudioVerSupport_vc90 );
		ChkAndAddProj(lib_root_path, GenArgs2VisualStudioVerSupport_vs2022 );

		m_btnIncludePath.EnableWindow(TRUE);
		m_btnLibraryPath.EnableWindow(TRUE);
		m_bAddProject.EnableWindow(TRUE);
	}
}
// Root Path
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Include Path
void CDz1LibCollectionDlg::OnBnClickedButtonIncludePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[4096];
	if (Dz1MfcPathSelectDlg(this->m_hWnd, m_initialPath, path, _T("Header 파일이 저장되어있는 위치를 선택하세요")) ==TRUE)
	{
		int len = 0;
		CString root_path;
		m_editRootPath.GetWindowText(root_path);
		if (Dz1STRNCMP(path, root_path.GetBuffer(), (len = root_path.GetLength())) != 0) MessageBox(_T("Root 경로 하위에 존재하여야 합니다."));
		else
		{
			TCHAR *middle_path = path + len;
			while(*middle_path && *middle_path == DIR_SEP) middle_path++;

			CString str;
			if (middle_path[0] == 0) str = _T("."); else str = middle_path;

			Dz1Str_delAndSetNull(&m_dst->root2inc_path);
			m_dst->root2inc_path = Dz1Str_dup(str.GetBuffer(), NULL);
			ASSERT(m_dst->root2inc_path != NULL);
			m_editIncludePath.SetWindowTextA(str);
		}
	}
}
// Include Path
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Library Path
void CDz1LibCollectionDlg::OnBnClickedButtonLibraryPath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[4096];
	if (Dz1MfcPathSelectDlg(this->m_hWnd, m_initialPath, path, _T("Library 파일이 저장되어있는 위치를 선택하세요")) ==TRUE)
	{
		int len = 0;
		CString root_path;
		m_editRootPath.GetWindowText(root_path);
		if (Dz1STRNCMP(path, root_path.GetBuffer(), (len = root_path.GetLength())) != 0) MessageBox(_T("Root 경로 하위에 존재하여야 합니다."));
		else
		{
			TCHAR *middle_path = path + len;
			while(*middle_path && *middle_path == DIR_SEP) middle_path++;

			CString str;
			if (middle_path[0] == 0) str = _T("."); else str = middle_path;

			Dz1Str_delAndSetNull(&m_dst->root2lib_path);
			m_dst->root2lib_path = Dz1Str_dup(str.GetBuffer(), NULL);
			ASSERT(m_dst->root2lib_path != NULL);

			m_editLibraryPath.SetWindowTextA(str);
		}
	}
}
// Library Path
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ListProjects
void CDz1LibCollectionDlg::ListProjectsEvent(int *_idx, int *_cnt)
{
	int cnt;
	if (_cnt != NULL) cnt = *_cnt;
	else cnt = m_listProjects.GetSelectedCount();

	int idx;
	if (_idx != NULL) idx = *_idx;
	else
	{
		POSITION pos = m_listProjects.GetFirstSelectedItemPosition();
		idx = m_listProjects.GetNextSelectedItem(pos);
	}

	if (cnt == 0)
	{
		if (idx != -1) ListProjectsSelOne(idx);
		else ListProjectsSelNone();
	}
	else if (cnt == 1) ListProjectsSelOne(idx);
	else ListProjectsSelMany(idx, cnt);
}

void CDz1LibCollectionDlg::ListProjectsSelNone()
{
	// no item Selected Implementation
	m_bDeleteProject.EnableWindow(FALSE);
}

void CDz1LibCollectionDlg::ListProjectsSelOne(int idx)
{
	// Only one item Selected Implementation
	GenArgs2VisualStudioEntry *node = m_listProjects.GetElement(idx);
	if (node == NULL) ListProjectsSelNone();
	else
	{
		m_bDeleteProject.EnableWindow(TRUE);
	}
}

void CDz1LibCollectionDlg::ListProjectsSelMany(int idx, int cnt)
{
	// many item Selected Implementation
	m_bDeleteProject.EnableWindow(TRUE);
}

void CDz1LibCollectionDlg::OnLvnItemchangedListProjects(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ((pNMLV->uNewState & (LVIS_FOCUSED | LVIS_SELECTED)) == (LVIS_FOCUSED | LVIS_SELECTED))
		ListProjectsEvent(&pNMLV->iItem);
	*pResult = 0;
}

void CDz1LibCollectionDlg::OnNMClickListProjects(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	if (pNMItemActivate->iItem == -1) ListProjectsSelNone();
}
// ListProjects
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Project Add
static GenArgs2VisualStudioVerSupport supports[] =
{
	GenArgs2VisualStudioVerSupport_vc90,
	GenArgs2VisualStudioVerSupport_vs2022
};
static int supports_cnt = sizeof(supports) / sizeof(GenArgs2VisualStudioVerSupport);

static Dz1Error _clr_exists(void *ptr, GenArgs2VisualStudioEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u32_t *dst = (u32_t *)ptr;
	u32_t flag = 0x1 << p->ver;
	(*dst) &= ~flag;

	return err;
}

void CDz1LibCollectionDlg::OnBnClickedButtonAddProject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	u32_t possible_flags = 0;
	int i;
	for (i = 0; i < supports_cnt; i++) possible_flags |= 1 << supports[i];
	GenArgs2VisualStudioList *list = m_dst->projects;
	list->travel(list, _clr_exists, (void *)&possible_flags);

	if (possible_flags == 0) MessageBox(_T("더이상 추가할 수 없습니다."));
	else
	{
		GenArgs2VisualStudioEntry *node = NULL;
		CDz1ProjSelDlg dlg(m_dst, &node, m_dst->path_root_abs);
		pthread_cleanup_push(GenArgs2VisualStudioEntry_delAndSetNull, (void *)&node);
		if (dlg.DoModal() == IDOK)
		{
			DZ1_ERROR_SAFE_VAR(errp, err);
			if ((*errp = m_listProjects.InsertRow(&node)).code) ERR_DLG_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (GenArgs2VisualStudioEntry_delAndSetNull, (void *)&node);
	}
}
// Project Add
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Project Del
void CDz1LibCollectionDlg::OnBnClickedButtonDeleteProject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int idx;
	POSITION pos = m_listProjects.GetFirstSelectedItemPosition();
	while (pos != NULL)
	{
		idx = m_listProjects.GetNextSelectedItem(pos);
		m_listProjects.RemoveRow(idx);
	}
}
// Project Del
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// OK
void CDz1LibCollectionDlg::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_editRootPath.GetWindowTextLength() == 0) MessageBox(_T("Linrary Root Path를 지정하세요"));
	else if (m_editIncludePath.GetWindowTextLength() == 0) MessageBox(_T("Include Path를 지정하세요"));
	else if (m_editLibraryPath.GetWindowTextLength() == 0) MessageBox(_T("Library Path를 지정하세요"));
	else
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		GenArgs2LibraryEntry *p = (*m_ret);
		if (p == NULL)
		{	// m_dst 는 새로 만든것
			(*m_ret) = m_dst;
			m_dst = NULL;
		}
		else
		{	// m_dst 는 복사한 것
			Dz1Str_delAndSetNull(&p->path_root_abs);
			p->path_root_abs = m_dst->path_root_abs;
			m_dst->path_root_abs = NULL;

			Dz1Str_delAndSetNull(&p->root2inc_path);
			p->root2inc_path = m_dst->root2inc_path;
			m_dst->root2inc_path = NULL;

			Dz1Str_delAndSetNull(&p->root2lib_path);
			p->root2lib_path = m_dst->root2lib_path;
			m_dst->root2lib_path = NULL;

			GenArgs2VisualStudioList_delAndSetNull(&p->projects);
			p->projects = m_dst->projects;
			m_dst->projects = NULL;
		}
		OnOK();
	}
}
// OK
////////////////////////////////////////////////////////////////////////////////
