// C:\ITSProject\Source\AnyMedia\dimz\dz1_tools\dz1_task_gen_gui\Dz1ProjSelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include <dz1_str.h>
#include <dz1_mfc.h>
#include <Dz1MfcFileSelectDlg.h>

#include "dz1_task_gen_gui.h"
#include "Dz1ProjSelDlg.h"


// CDz1ProjSelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1ProjSelDlg, CDialog)

CDz1ProjSelDlg::CDz1ProjSelDlg(GenArgs2LibraryEntry *owner, GenArgs2VisualStudioEntry **ret, Dz1Str libRootPath, CWnd* pParent /*=NULL*/)
	: CDialog(CDz1ProjSelDlg::IDD, pParent)
{
	m_owner = owner; ASSERT(m_owner != NULL);
	m_ret = ret; ASSERT(m_ret != NULL);
	m_dst = *m_ret;

	memset(m_path, 0, sizeof(m_path));
	memset(m_name_ext, 0, sizeof(m_name_ext));
//	memset(m_ext, 0, sizeof(m_ext));
}

CDz1ProjSelDlg::~CDz1ProjSelDlg()
{
}

void CDz1ProjSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PROJ_VER,	 m_comboProjVer );
	DDX_Control(pDX, IDC_EDIT_PROJ_PATHNAME, m_editProjPathName);
}


BEGIN_MESSAGE_MAP(CDz1ProjSelDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PROJ_PATHNAME, &CDz1ProjSelDlg::OnBnClickedButtonProjPathname)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDz1ProjSelDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CDz1ProjSelDlg 메시지 처리기입니다.
static Dz1Error _remove_string(void *ptr, GenArgs2VisualStudioEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CComboBoxProjectVer *dst = (CComboBoxProjectVer *)ptr;
	Dz1Str str = GenArgs2VisualStudioVerStr(p->ver);
	int idx = dst->FindString(-1, str);
	if (idx > 0) dst->DeleteString(idx);
	return err;
}

BOOL CDz1ProjSelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_comboProjVer.OnInitControl();

	if (m_dst != NULL)
	{
		int sel = 0;
		this->SetWindowText(_T("Project 수정"));

		m_comboProjVer.SetCurSel(m_dst->ver);
		m_comboProjVer.EnableWindow(FALSE);

		CString path;
		path.Format(_T("%s") DIR_SEPRATOR _T("%s"), m_dst->middle_path, m_dst->proj_file_name);
		m_editProjPathName.SetWindowText(path);
	}	
	else
	{
		m_owner->projects->travel(m_owner->projects, _remove_string, (void *)&m_comboProjVer);
		this->SetWindowText(_T("Project 추가"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDz1ProjSelDlg::OnBnClickedButtonProjPathname()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR *filetr = Dz1T("Visual Studio Project File(*.vcproj;*.vcxproj)|*.vcproj;*.ocxproj|");

	if (Dz1MfcFileSelectDlg(NULL, TRUE, m_initialPath, NULL, filetr, NULL, m_path, m_name_ext) == TRUE)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		TCHAR fn[4096];
		Dz1STRCPY(m_initialPath, m_path);
		if (Dz1STRNCMP(m_path, m_owner->path_root_abs, Dz1STRLEN(m_owner->path_root_abs)) != 0) MessageBox(_T("Project root path하위에 존재해야 합니다."));
		else if ((*errp = Dz1FileName_concatPathName(Dz1ArrParam(TCHAR, fn), m_path, m_name_ext)).code) ERR_DLG_OUT(errp);
		else
		{
			TCHAR *short_fn = fn + Dz1STRLEN(m_owner->path_root_abs);
			while(*short_fn && *short_fn == DIR_SEP) short_fn++;
			m_editProjPathName.SetWindowText(short_fn);
			Dz1Error_set(errp, 0);
		}
	}
}

void CDz1ProjSelDlg::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString proj_file;
	GenArgs2VisualStudioVerSupport ver = m_comboProjVer.GetCurSelValue();
	m_editProjPathName.GetWindowText(proj_file);

	if (ver == GenArgs2VisualStudioVerSupport_max) MessageBox(_T("Project Version"));
	else if (proj_file.IsEmpty()) MessageBox(_T("Project File"));
	else
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		GenArgs2VisualStudioEntry *temp = NULL;

		TCHAR proj_guid[40] = { 0, };
		TCHAR *middle_path = m_path + Dz1STRLEN(m_owner->path_root_abs);
		while(*middle_path && *middle_path == DIR_SEP) middle_path++;

		if ((temp = GenArgs2VisualStudioEntry_new((GenArgs2VisualStudioVer)ver, middle_path, m_name_ext, NULL, errp)) == NULL) ERR_DLG_OUT(errp);
		else
		{
			pthread_cleanup_push(GenArgs2VisualStudioEntry_delAndSetNull, (void *)&temp);
			if (_load_proj_guid(proj_guid, m_owner->path_root_abs, temp->middle_path, temp->proj_file_name, temp->ver, errp) == FALSE) ERR_DLG_OUT(errp);
			else if ((temp->proj_guid = Dz1Str_dup(proj_guid, errp)) == NULL) ERR_DLG_OUT(errp);
			else if (m_dst != NULL)
			{
				Dz1Str_delAndSetNull(&m_dst->middle_path);
				m_dst->middle_path = temp->middle_path;
				temp->middle_path = NULL;

				Dz1Str_delAndSetNull(&m_dst->proj_file_name);
				m_dst->proj_file_name = temp->proj_file_name;
				temp->proj_file_name = NULL;

				Dz1Str_delAndSetNull(&m_dst->proj_guid);
				m_dst->proj_guid = temp->proj_guid;
				temp->proj_guid = NULL;

				Dz1Error_set(errp, 0);
			}
			else
			{
				*m_ret = m_dst = temp;
				temp = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (GenArgs2VisualStudioEntry_delAndSetNull, (void *)&temp);
		}
		if (errp->code == 0) OnOK();
	}
}
