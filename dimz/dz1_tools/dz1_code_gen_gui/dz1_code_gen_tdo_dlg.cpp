// F:\Implements\JakeProj\dimz\dz1_tools\dz1_code_gen_gui\Dz1CodeGenTdoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include <Dz1MfcFileSelectDlg.h>

#include "dz1_code_gen_gui.h"
#include "dz1_code_gen_tdo_dlg.h"
#include "dz1_code_gen_tdo_list_dlg.h"
//#include "Dz1CodeGenTodecDlg.h"

// CDz1CodeGenTdoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1CodeGenTdoDlg, CDialog)

CDz1CodeGenTdoDlg::CDz1CodeGenTdoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenTdoDlg::IDD, pParent)
{
	m_module = NULL;
	m_selected = NULL;
	m_path[0] = 0;
	m_name[0] = 0;
}

CDz1CodeGenTdoDlg::~CDz1CodeGenTdoDlg()
{
	if (m_module != NULL) Dz1MdefcModule_delAndSetNull(&m_module);
}

void CDz1CodeGenTdoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TDO_FILE, m_editTdoFile);
	DDX_Control(pDX, IDC_TREE_TDO_INCLUDE, m_treeTdoInclude);
	DDX_Control(pDX, IDC_LIST_TDO_UNKNOWN, m_listTdoUnknown);
	DDX_Control(pDX, IDC_LIST_TDO_OBJECT, m_listTdoObject);
	DDX_Control(pDX, IDC_BUTTON_CREATE_LIST_CONTROL, m_btnCreateListControl);
	DDX_Control(pDX, IDC_BUTTON_SAVE_TO_TDC, m_btnSaveToTDC);
}


BEGIN_MESSAGE_MAP(CDz1CodeGenTdoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TDO_FILE, &CDz1CodeGenTdoDlg::OnBnClickedButtonTdoFile)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TDO_OBJECT, &CDz1CodeGenTdoDlg::OnNMClickListTdoObject)
//	ON_BN_CLICKED(IDC_BUTTON_CREATE_LIST_CONTROL, &CDz1CodeGenTdoDlg::OnBnClickedButtonCreateListControl)
//	ON_BN_CLICKED(IDC_BUTTON_TODEC, &CDz1CodeGenTdoDlg::OnBnClickedButtonTodec)
ON_BN_CLICKED(IDC_BUTTON_SAVE_TO_TDC, &CDz1CodeGenTdoDlg::OnBnClickedButtonSaveToTdc)
END_MESSAGE_MAP()


// CDz1CodeGenTdoDlg 메시지 처리기입니다.

BOOL CDz1CodeGenTdoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_listTdoUnknown.InitControl();
	m_listTdoObject.InitControl();

	m_btnCreateListControl.EnableWindow(FALSE);
	m_btnSaveToTDC.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDz1CodeGenTdoDlg::OnBnClickedButtonTdoFile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (SelectFile(this, TRUE, NULL, "*.tdo", "tdo", m_path, m_name) == TRUE)
	{
		BeginWaitCursor();
		Dz1MdefcModule *temp = Dz1MdefcModule_load2(m_path, m_name, errp);
		EndWaitCursor();

		if (temp == NULL) ERR_DLG_OUT(errp);
		else
		{
			CString str;
			str.Format(_T("%s") _T(DIR_SEPRATOR) _T("%s"), m_path, m_path);
			m_editTdoFile.SetWindowText(str);
			SetWindowText(m_name);

			Dz1MdefcModule_delAndSetNull(&m_module);
			m_module = temp;

			m_listTdoUnknown.Load(m_module->objUnknown);

			m_listTdoObject.Load(m_module->objFifo);

			LoadTree();

			m_btnSaveToTDC.EnableWindow(TRUE);
		}
	}
}

typedef struct LoadTreeArg
{
	CTreeCtrl *dst;
	HTREEITEM hParent;
} LoadTreeArg;

static Dz1Error _LoadTree(CTreeCtrl *dst, Dz1MdefcModule *p, HTREEITEM hParent);
static Dz1Error __LoadTree(void *ptr, void *_p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	LoadTreeArg *arg = (LoadTreeArg *)ptr;
	Dz1MdefcModule *p = (Dz1MdefcModule *)_p;
	if ((*errp = _LoadTree(arg->dst, p, arg->hParent)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error _LoadTree(CTreeCtrl *dst, Dz1MdefcModule *p, HTREEITEM hParent)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	CString str;
	str.Format(_T("%s.%s"), p->name, p->ext);
	HTREEITEM myself = dst->InsertItem(str, 0, 0, hParent);
	dst->Expand(hParent, TVE_EXPAND);

	LoadTreeArg arg = { dst, myself };
	if ((*errp = Dz1AATree_travel(p->moduleTree, __LoadTree, (void *)&arg)).code) ERR_OUT(errp);

	return err;
}

Dz1Error CDz1CodeGenTdoDlg::LoadTree(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	HTREEITEM hParent = TVI_ROOT;

	m_treeTdoInclude.DeleteAllItems();
	if ((*errp = _LoadTree(&m_treeTdoInclude, m_module, hParent)).code) ERR_OUT(errp);
	else m_treeTdoInclude.Expand(hParent, TVE_EXPAND);

	return err;
}
void CDz1CodeGenTdoDlg::OnNMClickListTdoObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_btnCreateListControl.EnableWindow(FALSE);
	m_selected = NULL;

	POSITION pos = m_listTdoObject.GetFirstSelectedItemPosition();
	int idx = m_listTdoObject.GetNextSelectedItem(pos);
	if (idx < 0)
	{	// disable all creation tool button
	}
	else
	{
		ObjectInfo *oi = (ObjectInfo *)(DWORD_PTR)m_listTdoObject.GetItemData(idx);
		if (oi->type == ObjectType_array)
		{
			m_selected = oi;
			m_btnCreateListControl.EnableWindow(TRUE);
		}
	}
	*pResult = 0;
}

void CDz1CodeGenTdoDlg::OnBnClickedButtonCreateListControl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1CodeGenListColumnList *temp = NULL;
	if (m_selected == NULL) MessageBox("Select");
	else if ((temp = Dz1CodeGenListColumnList_new(errp)) == NULL) ERR_DLG_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenListColumnList_delAndSetNull, (void *)&temp);
		CDz1CodeGenTdoListDlg dlg(m_selected, temp);
		dlg.DoModal();
		pthread_cleanup_pop(1); // (Dz1CodeGenListColumnList_delAndSetNull, (void *)&temp);
	}
}

//void CDz1CodeGenTdoDlg::OnBnClickedButtonTodec()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	DZ1_ERROR_SAFE_VAR(errp, err);
//	ConstructCodec *todec = ConstructCodec_create(m_module, errp);
//	if (todec == NULL) ERR_DLG_OUT(errp);
//	else
//	{
//		pthread_cleanup_push(ConstructCodec_delAndSetNull, (void *)&todec);
//		CDz1CodeGenTodecDlg dlg(todec);
//		dlg.DoModal();
//		pthread_cleanup_pop(1); // (ConstructCodec_delAndSetNull, (void *)&todec);
//	}
//}

void CDz1CodeGenTdoDlg::OnBnClickedButtonSaveToTdc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// 	TCHAR name[1024], path[4096];
// 	Dz1STRCPY(name, m_name);
// 	TCHAR *cp = Dz1STRSTR(name, _T(".tdo"));
// 	if (cp != NULL)
// 	{
// 		Dz1STRCPY(cp, _T(".tdc"));
// 
// 		if (Dz1MfcPathSelectDlg(this->m_hWnd, m_path, path, _T("저장 경로") ))
// 		{
// 			FILE *fp = NULL;
// 			DZ1_ERROR_SAFE_VAR(errp, err);
// 			if (Dz1File_isExist2(path, name))
// 			{
// 				CString str;
// 				str.Format(_T("%s에 %s가 이미 있습니다. 덮어쓰시겠습니까?"), path, name);
// 				if (MessageBox(str, _T("확인"), MB_YESNOCANCEL) == IDYES)
// 				{
// 					if ((fp = Dz1FileStream_open2(path, name, "wb", errp)) == NULL) ERR_DLG_OUT(errp);
// 					else
// 					{
// 						pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
// 						Dz1MdefcModule_tdc(fp, m_module, PublishSpec);
// 						pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void 8)&fp);
// 					}
// 				}
// 			}
// 			else if ((fp = Dz1FileStream_open2(path, name, "wb", errp)) == NULL) ERR_DLG_OUT(errp);
// 			else
// 			{
// 				pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
// 				Dz1MdefcModule_tdc(fp, m_module);
// 				pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void 8)&fp);
// 			}
// 		}
// 	}
// 	else MessageBox(_T("파일 이름에 문제가 있습니다."));
 	MessageBox(_T("Not Support"));
}
