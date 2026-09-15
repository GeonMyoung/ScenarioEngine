// C:\Implement\RMSS_R2\dimz\dz1_tools\dz1_code_gen_gui\Dz1CodeGenTodecDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include <Dz1MfcFileSelectDlg.h>
#include "dz1_code_gen_gui.h"
#include "Dz1CodeGenTodecDlg.h"
//#include "Dz1CodeGenTodecConfigDlg.h"
#include "Dz1CodeGenTodecStream.h"
#include "Dz1CodeGenStrDlg.h"
#include "Dz1CodeGenTextPadDlg.h"
#include "Dz1CodeGenTodecConfigDlg.h"

#include "Dz1CodeGenTodecPublish.h"
#include "Dz1CodeGenTodecPublishDlg.h"
// CDz1CodeGenTodecDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1CodeGenTodecDlg, CDialog)

CDz1CodeGenTodecDlg::CDz1CodeGenTodecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenTodecDlg::IDD, pParent)
{
	m_todec = NULL;
	m_tdo_path[0] = 0;
	m_todeo_path[0] = 0;
//	m_todeo_name[0] = 0;
	m_objType = ObjectType_max;
}

CDz1CodeGenTodecDlg::~CDz1CodeGenTodecDlg()
{
	ConstructCodec_delAndSetNull(&m_todec);
}

void CDz1CodeGenTodecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_BUTTON_SETTING, m_btnSetting);

	DDX_Control(pDX, IDC_COMBO_ENDIAN, m_comboEndian);

	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnNew);
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_btnLoad);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON_PUBLISH, m_btnPublish);

	DDX_Control(pDX, IDC_LIST_INCLUDE, m_listInclude);
	DDX_Control(pDX, IDC_BUTTON_INCLUDE_ADD, m_btnIncludeAdd);
	DDX_Control(pDX, IDC_BUTTON_INCLUDE_DEL, m_btnIncludeDel);
	DDX_Control(pDX, IDC_COMBO_INCLUDE, m_comboInclude);

	DDX_Control(pDX, IDC_LIST_OBJECT, m_listObject);
	DDX_Control(pDX, IDC_BUTTON_OBJECT_SRC, m_btnObjectSrc);
	DDX_Control(pDX, IDC_BUTTON_OBJECT_HDR, m_btnObjectHdr);

	DDX_Control(pDX, IDC_LIST_TODEC, m_listTodec);
	DDX_Control(pDX, IDC_BUTTON_TODEC_ADD, m_btnTodecAdd);
	DDX_Control(pDX, IDC_BUTTON_TODEC_DEL, m_btnTodecDel);
	DDX_Control(pDX, IDC_COMBO_TODEC, m_comboTodec);

	DDX_Control(pDX, IDC_LIST_TODEC_SEQ, m_listTodecSeq);
	DDX_Control(pDX, IDC_BUTTON_TODEC_SEQ_ADD, m_btnTodecSeqAdd);
	DDX_Control(pDX, IDC_BUTTON_TODEC_SEQ_DEL, m_btnTodecSeqDel);
	DDX_Control(pDX, IDC_BUTTON_TODEC_SEQ_MOD, m_btnTodecSeqMod);
	DDX_Control(pDX, IDC_BUTTON_TODEC_SEQ_DN, m_btnTodecSeqDn);
	DDX_Control(pDX, IDC_BUTTON_TODEC_SEQ_UP, m_btnTodecSeqUp);

	DDX_Control(pDX, IDC_STATIC_TODEC_SEQ_DESCR, m_staticTodecSeqDescr);
}


BEGIN_MESSAGE_MAP(CDz1CodeGenTodecDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CDz1CodeGenTodecDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CDz1CodeGenTodecDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDz1CodeGenTodecDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_PUBLISH, &CDz1CodeGenTodecDlg::OnBnClickedButtonPublish)

	ON_NOTIFY(LVN_ITEMCHANGED,	 IDC_LIST_INCLUDE, &CDz1CodeGenTodecDlg::OnLvnItemchangedListInclude)
	ON_NOTIFY(NM_CLICK,			 IDC_LIST_INCLUDE, &CDz1CodeGenTodecDlg::OnNMClickListInclude)
	ON_BN_CLICKED(IDC_BUTTON_INCLUDE_ADD, &CDz1CodeGenTodecDlg::OnBnClickedButtonIncludeAdd)
	ON_BN_CLICKED(IDC_BUTTON_INCLUDE_DEL, &CDz1CodeGenTodecDlg::OnBnClickedButtonIncludeDel)
	ON_CBN_SELCHANGE(IDC_COMBO_INCLUDE, &CDz1CodeGenTodecDlg::OnCbnSelchangeComboInclude)

	ON_NOTIFY(LVN_ITEMCHANGED,	 IDC_LIST_OBJECT, &CDz1CodeGenTodecDlg::OnLvnItemchangedListObject)
	ON_NOTIFY(NM_CLICK,			 IDC_LIST_OBJECT, &CDz1CodeGenTodecDlg::OnNMClickListObject)
	ON_NOTIFY(NM_DBLCLK,		 IDC_LIST_OBJECT, &CDz1CodeGenTodecDlg::OnNMDblclkListObject)
	ON_BN_CLICKED(IDC_BUTTON_OBJECT_SRC, &CDz1CodeGenTodecDlg::OnBnClickedButtonObjectSrc)
	ON_BN_CLICKED(IDC_BUTTON_OBJECT_HDR, &CDz1CodeGenTodecDlg::OnBnClickedButtonObjectHdr)

	ON_NOTIFY(LVN_ITEMCHANGED,	 IDC_LIST_TODEC, &CDz1CodeGenTodecDlg::OnLvnItemchangedListTodec)
	ON_NOTIFY(NM_CLICK,			 IDC_LIST_TODEC, &CDz1CodeGenTodecDlg::OnNMClickListTodec)
	ON_NOTIFY(NM_DBLCLK,		 IDC_LIST_TODEC, &CDz1CodeGenTodecDlg::OnNMDblclkListTodec)
	ON_BN_CLICKED(IDC_BUTTON_TODEC_ADD, &CDz1CodeGenTodecDlg::OnBnClickedButtonTodecAdd)
	ON_BN_CLICKED(IDC_BUTTON_TODEC_DEL, &CDz1CodeGenTodecDlg::OnBnClickedButtonTodecDel)
	ON_CBN_SELCHANGE(IDC_COMBO_TODEC, &CDz1CodeGenTodecDlg::OnCbnSelchangeComboTodec)

	ON_NOTIFY(LVN_ITEMCHANGED,	 IDC_LIST_TODEC_SEQ, &CDz1CodeGenTodecDlg::OnLvnItemchangedListTodecSeq)
	ON_NOTIFY(NM_CLICK,			 IDC_LIST_TODEC_SEQ, &CDz1CodeGenTodecDlg::OnNMClickListTodecSeq)
	ON_NOTIFY(NM_DBLCLK,		 IDC_LIST_TODEC_SEQ, &CDz1CodeGenTodecDlg::OnNMDblclkListTodecSeq)
	ON_BN_CLICKED(IDC_BUTTON_TODEC_SEQ_ADD, &CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqAdd)
	ON_BN_CLICKED(IDC_BUTTON_TODEC_SEQ_DEL, &CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqDel)
	ON_BN_CLICKED(IDC_BUTTON_TODEC_SEQ_MOD, &CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqMod)
	ON_BN_CLICKED(IDC_BUTTON_TODEC_SEQ_DN, &CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqDn)
	ON_BN_CLICKED(IDC_BUTTON_TODEC_SEQ_UP, &CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqUp)

	ON_CBN_SELCHANGE(IDC_COMBO_ENDIAN, &CDz1CodeGenTodecDlg::OnCbnSelchangeComboEndian)
	ON_CBN_EDITCHANGE(IDC_COMBO_ENDIAN, &CDz1CodeGenTodecDlg::OnCbnEditchangeComboEndian)
	ON_BN_CLICKED(IDC_BUTTON_OBJECT_DEL, &CDz1CodeGenTodecDlg::OnBnClickedButtonObjectDel)
END_MESSAGE_MAP()


// CDz1CodeGenTodecDlg 메시지 처리기입니다.

BOOL CDz1CodeGenTodecDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	int idx = m_comboEndian.AddString(_T("Dz1IOStreamEndian_big"));
	m_comboEndian.AddString(_T("Dz1IOStreamEndian_little"));
	m_comboEndian.SetCurSel(-1);
	m_comboEndian.EnableWindow(FALSE);

	m_btnSave.EnableWindow(FALSE);
	m_btnPublish.EnableWindow(FALSE);
	m_btnIncludeAdd.EnableWindow(FALSE);

	m_listInclude.OnInitControl();
	m_listObject.OnInitControl();
	m_listTodec.OnInitControl();
	m_listTodecSeq.OnInitControl();

	ListIncludeEvent();
	ListObjectEvent();
	ListTodecEvent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDz1CodeGenTodecDlg::DataLoad(void)
{
	if (m_todec != NULL)
	{
		int idx = m_comboEndian.FindString(-1, m_todec->endian);
		if (idx == CB_ERR) idx = m_comboEndian.AddString(m_todec->endian);
		m_comboEndian.SetCurSel(idx);

		m_listInclude.Load(m_todec->includes, &m_todec->is_dirty);
		ListIncludeEvent();

		m_listObject.Load(m_todec->objs);
		ListObjectEvent();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Endian Combo
void CDz1CodeGenTodecDlg::OnCbnSelchangeComboEndian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_todec != NULL) m_todec->is_dirty = TRUE;
}

void CDz1CodeGenTodecDlg::OnCbnEditchangeComboEndian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_todec != NULL) m_todec->is_dirty = TRUE;
}
// Endian Combo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// New
void CDz1CodeGenTodecDlg::OnBnClickedButtonNew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_todec != NULL && m_todec->is_dirty)
	{
		if (MessageBox(_T("저장되지 않은 정보가 있습니디. 계속하시겠습니까?"), _T("진행 확인"), MB_YESNOCANCEL) != IDYES) return;
	}

	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR path[4096], name[1024];
	if (Dz1MfcFileSelectDlg(this, TRUE, m_tdo_path, NULL, _T("TDO File(*.tdo)|*.tdo|"), _T("tdo"), path, name))
	{
		Dz1STRCPY(m_tdo_path, path);
		m_todeo_path[0] = 0;

		m_listObject.Unload(); ListObjectEvent();
		m_listTodec.Unload(); ListTodecEvent();

		BeginWaitCursor();

		ConstructCodec *temp = NULL;
		if ((temp = ConstructCodec_new(name, path, errp)) == NULL) ERR_DLG_OUT(errp);
		else
		{
			pthread_cleanup_push(ConstructCodec_delAndSetNull, (void *)&temp);

			if ((temp->endian = Dz1Str_dup(_T("Dz1IOStreamEndian_big"), errp)) == NULL) ERR_DLG_OUT(errp);
			else if ((temp->module = Dz1MdefcModule_load2(temp->tdo_path, temp->tdo_name, errp)) == NULL) ERR_DLG_OUT(errp);
			else if ((*errp = ConstructCodec_initSrc(temp)).code) ERR_DLG_OUT(errp);
			else
			{
				temp->is_dirty = TRUE;

				ConstructCodec_delAndSetNull(&m_todec);
				m_todec = temp;
				temp = NULL;

				m_comboEndian.EnableWindow(TRUE);
				m_btnSave.EnableWindow(TRUE);
				m_btnPublish.EnableWindow(TRUE);
				m_btnIncludeAdd.EnableWindow(TRUE);

				TCHAR *cp = Dz1STRRCHR(name, _T('.'));
				if (cp != NULL)
				{
					cp++;
					Dz1STRCPY(cp, _T("todeo"));
				}
				this->SetWindowText(name);
			}
			pthread_cleanup_pop(1); // (ConstructCodec_delAndSetNull, (void *)&temp);
		}
		EndWaitCursor();
		DataLoad();
	}
}
// New
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Load
static Dz1Error GetTdoPath(TCHAR dst[4096], str_t loaded_tdo_path, str_t todeo_path)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (loaded_tdo_path == NULL || loaded_tdo_path[0] == 0) Dz1STRCPY(dst, todeo_path);			// no path -> same position with todeo
	else if (Dz1Path_isAbsPath(loaded_tdo_path))			Dz1STRCPY(dst, loaded_tdo_path);	// abs path -> individual location
	else
	{	// relative path
		TCHAR l_path[4096], t_path[4096];
		TCHAR *cp = NULL, *lp = l_path;
		size_t l_len = Dz1STRLEN(loaded_tdo_path), l_last_idx = l_len - 1;
		size_t t_len = Dz1STRLEN(todeo_path), t_last_idx = t_len - 1;
		Dz1STRCPY(l_path, loaded_tdo_path);
		Dz1STRCPY(t_path, todeo_path);

		while(l_last_idx && l_path[l_last_idx] == DIR_SEP)
		{
			l_path[l_last_idx--] = 0;
			l_len--;
		}

		while(t_last_idx && t_path[t_last_idx] == DIR_SEP)
		{
			t_path[t_last_idx--] = 0;
			t_len--;
		}

		// t_path = "\dir1\dir2\dir3\dir4" l_path = "..\dir5\..\dir7"
		while(errp->code == 0 && (cp = Dz1STRCHR(lp, DIR_SEP)) != NULL)
		{
			*cp++ = 0;								// lp = ".." cp = "dir5\..\dir7"
														// lp = "dir5", cp = "..\dir7"
															// lp = "..", cp = "dir7"
			if (Dz1STRCMP(lp, _T("..")) == 0)
			{
				TCHAR *xp = Dz1STRRCHR(t_path, DIR_SEP);
				if (xp == NULL) ERR_SET_OUT(errp, EINVAL);
				else *xp = 0;						// t_path = "\dir1\dir2\dir3"
															// t_path = "\dir1\dir2\dir3"
			}
			else
			{
				Dz1STRCAT(t_path, DIR_SEPRATOR);		// t_path = "\dir1\dir2\dir3\"
				Dz1STRCAT(t_path, lp);					// t_path = "\dir1\dir2\dir3\dir5"
			}
			lp = cp;								// lp = "dir5\..\dir7"
														// lp = "..\dir7"
															// lp = "dir7"
		}
		if (Dz1STRCMP(lp, _T("..")) == 0)
		{
			TCHAR *xp = Dz1STRRCHR(t_path, DIR_SEP);
			if (xp == NULL) ERR_SET_OUT(errp, EINVAL);
			else *xp = 0;
		}
		else
		{
			Dz1STRCAT(t_path, DIR_SEPRATOR);		// t_path = "\dir1\dir2\dir3\"
			Dz1STRCAT(t_path, lp);					// t_path = "\dir1\dir2\dir3\dir5"
		}
	}
	return err;
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_todec != NULL && m_todec->is_dirty)
	{
		if (MessageBox(_T("저장되지 않은 정보가 있습니디. 계속하시겠습니까?"), _T("진행 확인"), MB_YESNOCANCEL) != IDYES) return;
	}

	TCHAR path[4096], name[1024];
	if (Dz1MfcFileSelectDlg(this, TRUE, m_todeo_path, NULL, _T("TODEO File(*.todeo)|*.todeo|"), _T("todeo"), path, name))
	{
		Dz1STRCPY(m_todeo_path, path);

		m_listObject.Unload(); ListObjectEvent();
		m_listTodec.Unload(); ListTodecEvent();

		BeginWaitCursor();
		DZ1_ERROR_SAFE_VAR(errp, err);
		ConstructCodec *temp = NULL;
		if ((temp = ConstructCodec_load(path, name, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_DLG_OUT(errp);
		else
		{
//			TCHAR tdo_path[4096];
			pthread_cleanup_push(ConstructCodec_delAndSetNull, (void *)&temp);

			if ((*errp = GetTdoPath(m_tdo_path, temp->tdo_path, m_todeo_path)).code) ERR_DLG_OUT(errp);
			else if ((temp->module = Dz1MdefcModule_load2(m_tdo_path, temp->tdo_name, errp)) == NULL) ERR_DLG_OUT(errp);
			else if ((*errp = ConstructCodec_initSrc(temp)).code) ERR_OUT(errp);
			else if ((*errp = ConstructCodec_resolve(temp)).code) ERR_DLG_OUT(errp);
			{

				ConstructCodec_delAndSetNull(&m_todec);
				m_todec = temp;
				temp = NULL;

				m_comboEndian.EnableWindow(TRUE);
				m_btnSave.EnableWindow(TRUE);
				m_btnPublish.EnableWindow(TRUE);
				m_btnIncludeAdd.EnableWindow(TRUE);

				this->SetWindowText(name);
			}
			pthread_cleanup_pop(1); // (ConstructCodec_delAndSetNull, (void *)&temp);
		}
		EndWaitCursor();

		DataLoad();
	}
}
// Load
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Save
static int _PathStrToArray(Dz1Str src_path, TCHAR **dst_arr, int arr_cnt)
{
	int cnt = 0;

	TCHAR *cp = NULL, *sp = src_path;
	size_t len = Dz1STRLEN(src_path), last_idx = len - 1;

	while(last_idx && src_path[last_idx] == DIR_SEP) { src_path[last_idx--] = 0; len--; }	// trim last dir_sep

	while(arr_cnt && (cp = Dz1STRCHR(sp, DIR_SEP)) != NULL)
	{
		*cp++ = 0;				// make ASCIIZ
		dst_arr[cnt++] = sp;	// assign DIR-name
		sp = cp; cp = NULL;		// position fix
		arr_cnt--;
	}

	if (arr_cnt)
	{
		dst_arr[cnt++] = sp;	// assign last DIR-name
		arr_cnt--;
	}
	else return -1;

	return cnt;
}

static Dz1Error GetRelativePath(TCHAR dst[4096], Dz1Str base_path, Dz1Str target_path)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	TCHAR *dp = dst;

	TCHAR b_path[4096], *b_arr[64] = { NULL, }, **bap = b_arr;
	int b_cnt = 0;

	TCHAR t_path[4096], *t_arr[64] = { NULL, }, **tap = t_arr;
	int t_cnt = 0;

	Dz1STRCPY(b_path, base_path);								// copy base path
	if ((b_cnt = _PathStrToArray(b_path, b_arr, 64)) < 0) ERR_SET_OUT_RET(errp, EINVAL, err);

	Dz1STRCPY(t_path, target_path);								// copy target path
	if ((t_cnt = _PathStrToArray(t_path, t_arr, 64)) < 0) ERR_SET_OUT_RET(errp, EINVAL, err);

	while(*bap != NULL && *tap != NULL && Dz1STRCMP(*bap, *tap) == 0) { bap++; tap++; }
	while(*bap)
	{
		if (dst != dp) *dp++ = DIR_SEP;
		Dz1STRCPY(dp, ".."); dp += 2;
		bap++;
	}

	while(*tap)
	{
		if (dst != dp) *dp++ = DIR_SEP;
		Dz1STRCPY(dp, *tap); dp += Dz1STRLEN(*tap);
		tap++;
	}
	*dp++ = 0;
	Dz1Error_set(errp, 0);
	return err;
}

void CDz1CodeGenTodecDlg::UpdateEndianString(void)
{
	if (m_todec != NULL)
	{
		CString str;
		m_comboEndian.GetWindowText(str);
		if (m_todec->endian == NULL)
		{
			m_todec->endian = Dz1Str_dup(str.GetBuffer(), NULL);
			ASSERT(m_todec->endian != NULL);
		}
		else if (str != m_todec->endian)
		{
			Dz1Str temp = Dz1Str_dup(str.GetBuffer(), NULL);
			ASSERT(temp != NULL);
			Dz1Str_delAndSetNull(&m_todec->endian);
			m_todec->endian = temp;
			temp = NULL;
		}
	}
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// New를 하면 TDO Path 유효, TODEO Path없음
	// Load를 하면 TDO, TODEO path 모두 유효

	if (m_todec->is_dirty)
	{	// TODEO path 확보
		TCHAR path[4096];
		if (m_todeo_path[0] == 0)
		{	// TODEO Path 필요
			if (Dz1MfcPathSelectDlg(this->m_hWnd, m_tdo_path, path, _T("저장 위치")) == FALSE) return;
		}
		else Dz1STRCPY(path, m_todeo_path);

		// TODEO Path에 대한 TDO상대 경로 구하기
		DZ1_ERROR_SAFE_VAR(errp, err);
		TCHAR rel_tdo_path[4096];
		if ((*errp = GetRelativePath(rel_tdo_path, path, m_tdo_path)).code) ERR_DLG_OUT(errp);
		else
		{
			Dz1Str temp = Dz1Str_dup(rel_tdo_path, errp);
			if (temp == NULL) ERR_DLG_OUT(errp);
			else
			{
				Dz1Str_delAndSetNull(&m_todec->tdo_path);
				m_todec->tdo_path = temp;

				Dz1MdefcModule *module = m_todec->module;
				Dz1Str module_name = Dz1STRRCHR(module->name, DIR_SEP);
				if (module_name == NULL) module_name = module->name;
				else module_name++;

				UpdateEndianString();

				if ((*errp = ConstructCodec_save(m_todec, path, module_name, Dz1IOStreamEndian_big, NULL)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
	}
}
// Save
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Publish
void CDz1CodeGenTodecDlg::OnBnClickedButtonPublish()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDz1CodeGenTodecPublishDlg dlg(m_todec, m_tdo_path);
	dlg.DoModal();
}
// Publish
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// List Include
void CDz1CodeGenTodecDlg::ListIncludeEvent(int *_idx, int *_cnt)
{
	int cnt;
	if (_cnt != NULL) cnt = *_cnt;
	else cnt = m_listInclude.GetSelectedCount();

	int idx;
	if (_idx != NULL) idx = *_idx;
	else
	{
		POSITION pos = m_listInclude.GetFirstSelectedItemPosition();
		idx = m_listInclude.GetNextSelectedItem(pos);
	}

	if (cnt == 0)
	{
		if (idx != -1) ListIncludeSelOne(idx);
		else ListIncludeSelNone();
	}
	else if (cnt == 1) ListIncludeSelOne(idx);
	else ListIncludeSelMany(idx, cnt);
}

void CDz1CodeGenTodecDlg::ListIncludeSelNone()
{
	// no item Selected Implementation
	m_btnIncludeDel.EnableWindow(FALSE);
	m_comboInclude.SetCurSel(-1);
	m_comboInclude.EnableWindow(FALSE);
}

void CDz1CodeGenTodecDlg::ListIncludeSelOne(int idx)
{
	// Only one item Selected Implementation
	ConstructCodecIncludeEntry *node = m_listInclude.GetElement(idx);
	if (node == NULL) ListIncludeSelNone();
	else
	{
		m_btnIncludeDel.EnableWindow(TRUE);
		m_comboInclude.SetCurSel((int)node->use_codate);
		m_comboInclude.EnableWindow(TRUE);
	}
}

static bool_t _ListInclude_getCotate(void *ptr, ConstructCodecIncludeEntry *p, bool_t &refresh)
{
	bool_t ret = FALSE;
	int *v = (int *)ptr;
	refresh = FALSE;
	if ( (*v) == -1)
		(*v) = p->use_codate;
	else if ( (*v) != (int)p->use_codate)
	{
		(*v) = -1;
		ret = TRUE;
	}
	return ret;
}

void CDz1CodeGenTodecDlg::ListIncludeSelMany(int idx, int cnt)
{
	// many item Selected Implementation
	m_btnIncludeDel.EnableWindow(TRUE);

	int v = -1;
	m_listInclude.TravelSelectedItem(_ListInclude_getCotate, (void *)&v);
	m_comboInclude.SetCurSel(v);
	m_comboInclude.EnableWindow(TRUE);
}

void CDz1CodeGenTodecDlg::OnLvnItemchangedListInclude(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ((pNMLV->uNewState & (LVIS_FOCUSED | LVIS_SELECTED)) == (LVIS_FOCUSED | LVIS_SELECTED))
		ListIncludeEvent(&pNMLV->iItem);
	*pResult = 0;
}

void CDz1CodeGenTodecDlg::OnNMClickListInclude(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMItemActivate->iItem == -1) ListIncludeSelNone();
	*pResult = 0;
}
// ListInclude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Include Control
void CDz1CodeGenTodecDlg::OnBnClickedButtonIncludeAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Dz1CodeGenStrDlgParam arg = {
		FALSE,									// accept_null
		CODEGEN_STR_DLG_TITLE | CODEGEN_STR_DLG_YES_TEXT | CODEGEN_STR_DLG_NO_TEXT,					// mask
		_T("Header Filename"),					// Title
		NULL,									// Box Caption,
		_T("확인"),								// Yes Text
		NULL,									// No Text
		NULL									// Cancel Text
	};
	TCHAR name[1024]= { 0 };
	CDz1CodeGenStrDlg dlg(name, 1024, &arg);
	if (dlg.DoModal() == IDOK)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		ConstructCodecIncludeEntry *node = ConstructCodecIncludeEntry_new(name, errp);
		if (node == NULL) ERR_DLG_OUT(errp);
		else
		{
			pthread_cleanup_push(ConstructCodecIncludeEntry_delAndSetNull, (void *)&node);
			if ((*errp = m_listInclude.InsertRow(&node, NULL)).code) ERR_DLG_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (ConstructCodecIncludeEntry_delAndSetNull, (void *)&node);
		}
	}
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonIncludeDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_listInclude.GetSelectedCount() == 0) MessageBox(_T("No Item Selected"));
	else if (MessageBox(_T("선택한 항목을 삭제하시겠습니까?"), _T("삭제확인"), MB_YESNOCANCEL) == IDYES)
	{
		POSITION pos = m_listInclude.GetFirstSelectedItemPosition();
		int idx = 0;
		m_listInclude.SetRedraw(FALSE);
		while((idx = m_listInclude.GetNextSelectedItem(pos)) >= 0)
		{
			m_listInclude.RemoveRow(idx);
			pos = m_listInclude.GetFirstSelectedItemPosition();
		}
		m_listInclude.SetRedraw(TRUE);
	}
}

static bool_t _ListInclude_setCotate(void *ptr, ConstructCodecIncludeEntry *p, bool_t &refresh)
{
	bool_t stop = FALSE;
	bool_t use_cotate = *(bool_t *)ptr ? TRUE : FALSE;

	refresh = FALSE;
	if (p->use_codate != use_cotate)
	{
		p->use_codate = use_cotate;
		refresh = TRUE;
	}
	return stop;
}

void CDz1CodeGenTodecDlg::OnCbnSelchangeComboInclude()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int idx = m_comboInclude.GetCurSel();
	if (idx != CB_ERR)
	{
		m_listInclude.TravelSelectedItem(_ListInclude_setCotate, (void *)&idx);
		m_todec->is_dirty = TRUE;
	}
}
// Include Control
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ListObject
void CDz1CodeGenTodecDlg::ListObjectEvent(int *_idx, int *_cnt)
{
	int cnt;
	if (_cnt != NULL) cnt = *_cnt;
	else cnt = m_listObject.GetSelectedCount();

	int idx;
	if (_idx != NULL) idx = *_idx;
	else
	{
		POSITION pos = m_listObject.GetFirstSelectedItemPosition();
		idx = m_listObject.GetNextSelectedItem(pos);
	}

	if (cnt == 0)
	{
		if (idx != -1) ListObjectSelOne(idx);
		else ListObjectSelNone();
	}
	else if (cnt == 1) ListObjectSelOne(idx);
	else ListObjectSelMany(idx, cnt);
}

void CDz1CodeGenTodecDlg::ListObjectSelNone()
{
	// no item Selected Implementation
	m_btnObjectSrc.EnableWindow(FALSE);
	m_btnObjectHdr.EnableWindow(FALSE);
	m_btnTodecAdd.EnableWindow(FALSE);
	m_listTodec.Unload();
	ListTodecEvent();
}

void CDz1CodeGenTodecDlg::ListObjectSelOne(int idx)
{
	// Only one item Selected Implementation
	ConstructObjectEntry *node = m_listObject.GetElement(idx);
	if (node == NULL) ListObjectSelNone();
	else
	{
		m_btnObjectSrc.EnableWindow(TRUE);
		m_btnObjectHdr.EnableWindow(TRUE);

		m_listTodec.Load(node->codecs, &m_todec->is_dirty);
		if (m_listTodec.GetItemCount() > 0) m_listTodec.SelectItemByIdx(0);
		m_btnTodecAdd.EnableWindow(TRUE);
		ListTodecEvent();
	}
}

void CDz1CodeGenTodecDlg::ListObjectSelMany(int idx, int cnt)
{
	// many item Selected Implementation
	m_btnObjectSrc.EnableWindow(FALSE);
	m_btnObjectHdr.EnableWindow(FALSE);

	m_listTodec.Unload();
	m_btnTodecAdd.EnableWindow(TRUE);
	ListTodecEvent();
}

void CDz1CodeGenTodecDlg::OnLvnItemchangedListObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	if ((pNMLV->uNewState & (LVIS_FOCUSED | LVIS_SELECTED)) == (LVIS_FOCUSED | LVIS_SELECTED))
		ListObjectEvent(&pNMLV->iItem);
}

void CDz1CodeGenTodecDlg::OnNMClickListObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMItemActivate->iItem == -1) ListObjectSelNone();
	*pResult = 0;
}

void CDz1CodeGenTodecDlg::OnNMDblclkListObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMItemActivate->iItem != -1) PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON_TODEC_ADD, BN_CLICKED), 0);
	*pResult = 0;
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonObjectDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// 	ConstructObjectEntry *node = NULL;
// 	POSITION pos = m_listObject.GetFirstSelectedItemPosition();
// 	int idx = m_listObject.GetNextSelectedItem(pos);
// 	while((node = m_listObject.GetElement(idx, NULL)) != NULL)
// 	{
// 		m_listObject.RemoveRow(idx);
// 		pos = m_listObject.GetFirstSelectedItemPosition();
// 		idx = m_listObject.GetNextSelectedItem(pos);
// 	}
}
// ListObject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Source Code Test
static void _file_delete(void *ptr)
{
	Dz1Str fn = (Dz1Str)ptr;
	Dz1File_delete(fn);
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonObjectSrc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int idx = m_listObject.GetCurSelIdx();
	ConstructObjectEntry *node = m_listObject.GetElement(idx);
	if (node != NULL)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		Dz1Str fn = Dz1Text("__temporary_file__.c");
		FILE *fp = Dz1FileStream_open(fn, Dz1Text("wb"), errp);
		if (fp == NULL) ERR_DLG_OUT(errp);
		else
		{
			Dz1Str text = NULL;
			CString str;
			m_comboEndian.GetWindowText(str);

			pthread_cleanup_push(_file_delete, (void *)fn);

			pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
			*errp = ConstructObjectEntry_publish_src(fp, node, str.GetBuffer(), NULL);
			pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);

			if (errp->code) ERR_DLG_OUT(errp);
			else if ((text = Dz1TextFile_load(fn, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&text);
				CString title;
				title.Format(_T("%s Source"), node->obj_name);
				CDz1CodeGenTextPadDlg dlg(title.GetBuffer(), text);
				dlg.DoModal();
				pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&text);
			}
			pthread_cleanup_pop(1); // (_file_delete, (void *)fn);
		}
	}
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonObjectHdr()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int idx = m_listObject.GetCurSelIdx();
	ConstructObjectEntry *node = m_listObject.GetElement(idx);
	if (node != NULL)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		Dz1Str fn = Dz1Text("__temporary_file__.h");
		FILE *fp = Dz1FileStream_open(fn, Dz1Text("wb"), errp);
		if (fp == NULL) ERR_DLG_OUT(errp);
		else
		{
			CString str;
			Dz1Str text = NULL;
			bool_t printed = FALSE;
			m_comboEndian.GetWindowText(str);

			pthread_cleanup_push(_file_delete, (void *)fn);

			pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
			*errp = ConstructObjectEntry_publish_hdr(fp, node, str.GetBuffer(), &printed);
			pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);

			if (errp->code) ERR_DLG_OUT(errp);
			else if (printed == FALSE) MessageBox(_T("아무것도 출력된 것이 없습니다."));
			else if ((text = Dz1TextFile_load(fn, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&text);
				CString title;
				title.Format(_T("%s Source"), node->obj_name);
				CDz1CodeGenTextPadDlg dlg(title.GetBuffer(), text);
				dlg.DoModal();
				pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&text);
			}
			pthread_cleanup_pop(1); // (_file_delete, (void *)fn);
		}
	}
}
// Source Code Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ListTodec
void CDz1CodeGenTodecDlg::ListTodecEvent(int *_idx, int *_cnt)
{
	int cnt;
	if (_cnt != NULL) cnt = *_cnt;
	else cnt = m_listTodec.GetSelectedCount();

	int idx;
	if (_idx != NULL) idx = *_idx;
	else
	{
		POSITION pos = m_listTodec.GetFirstSelectedItemPosition();
		idx = m_listTodec.GetNextSelectedItem(pos);
	}

	if (cnt == 0)
	{
		if (idx != -1) ListTodecSelOne(idx);
		else ListTodecSelNone();
	}
	else if (cnt == 1) ListTodecSelOne(idx);
	else ListTodecSelMany(idx, cnt);
}

void CDz1CodeGenTodecDlg::ListTodecSelNone()
{
	// no item Selected Implementation
	m_btnTodecDel.EnableWindow(FALSE);					// TODEC Del

	m_comboTodec.SetCurSel(-1);							// TODEC Combo
	m_comboTodec.EnableWindow(FALSE);

	m_btnTodecSeqAdd.EnableWindow(FALSE);				// SEQ Add
	m_listTodecSeq.Unload();;							// SEQ List

	ListTodecSeqEvent();								// SEQ Event
}

void CDz1CodeGenTodecDlg::ListTodecSelOne(int idx)
{
	// Only one item Selected Implementation

	ConstructCodecEntry *entry = m_listTodec.GetElement(idx, NULL);
	if (entry == NULL) ListTodecSelNone();
	else
	{
		m_btnTodecDel.EnableWindow(TRUE);				// TODEC Del

		m_comboTodec.SetCurSel((int)entry->mode);		// TODEC Combo
		m_comboTodec.EnableWindow(TRUE);

		if (entry->parent_obj != NULL)
			m_objType = ObjectInfo_typeOf(entry->parent_obj);
		else m_objType = ObjectType_max;

		switch(m_objType)								// SEQ Add
		{
		default:
		case ObjectType_array:
			m_btnTodecSeqAdd.EnableWindow(FALSE);
			break;
		case ObjectType_union:
			if (ConstructMemberCodecList_findByName(entry->member_codec, INSTANCE_NAME_PRESENT) != NULL)
				m_btnTodecSeqAdd.EnableWindow(FALSE);
			else m_btnTodecSeqAdd.EnableWindow(TRUE);
			break;
		case ObjectType_structure:
			m_btnTodecSeqAdd.EnableWindow(TRUE);
			break;
		}

		m_listTodecSeq.Load(entry->member_codec, &m_todec->is_dirty);	// SEQ List
		ListTodecSeqEvent();											// SEQ Event
	}
}

static bool_t _ListTodec_getApiMode(void *ptr, ConstructCodecEntry *p, bool_t &refresh)
{
	bool_t stop = FALSE;
	int *v = (int *)ptr;
	refresh = FALSE;
	if ( (*v) == -1) (*v) = p->mode;
	else if ( (*v) != (int)p->mode)
	{
		(*v) = -1;
		stop = TRUE;
	}
	return stop;
}

void CDz1CodeGenTodecDlg::ListTodecSelMany(int idx, int cnt)
{
	// many item Selected Implementation
	m_btnTodecDel.EnableWindow(TRUE);					// TODEC Del

	int v = -1;
	m_listTodec.TravelSelectedItem(_ListTodec_getApiMode, (void *)&v);
	m_comboTodec.SetCurSel(v);							// TODEC Combo
	m_comboTodec.EnableWindow(TRUE);

	m_btnTodecSeqAdd.EnableWindow(FALSE);				// SEQ Add
	m_listTodecSeq.Unload();							// SEQ List
	ListTodecSeqEvent();								// SEQ Event
}

void CDz1CodeGenTodecDlg::OnLvnItemchangedListTodec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ((pNMLV->uNewState & (LVIS_FOCUSED | LVIS_SELECTED)) == (LVIS_FOCUSED | LVIS_SELECTED))
		ListTodecEvent(&pNMLV->iItem);
	*pResult = 0;
}

void CDz1CodeGenTodecDlg::OnNMClickListTodec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMItemActivate->iItem == -1) ListTodecSelNone();
	*pResult = 0;
}

void CDz1CodeGenTodecDlg::OnNMDblclkListTodec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMItemActivate->iItem != -1) PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON_TODEC_DEL, BN_CLICKED), 0);
	*pResult = 0;
}
// ListTodec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TODEC Control
void CDz1CodeGenTodecDlg::OnBnClickedButtonTodecAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t force_suffix = GetKeyState(VK_CONTROL) & 0x8000 ? TRUE : FALSE;
	bool_t is_public = GetKeyState(VK_SHIFT) & 0x8000 ? TRUE : FALSE;

	////////////////////////////////////////////////////////////
	// Force Suffix
	TCHAR suffix_str[256] = { 0, };
	if (force_suffix)
	{
		Dz1CodeGenStrDlgParam param =
		{
			FALSE,
			CODEGEN_STR_DLG_ALL,
			_T("접미사 설정"),
			_T("API 접미사"),
			_T("확인"), NULL, _T("취소")
		};
		CDz1CodeGenStrDlg dlg(suffix_str, 256, &param);
		if (dlg.DoModal() != IDOK) return;
	}
	// Force Suffix
	////////////////////////////////////////////////////////////

	ConstructObjectEntry *node = NULL;
	POSITION pos = m_listObject.GetFirstSelectedItemPosition();
	int idx;
	while(errp->code == 0 && (idx = m_listObject.GetNextSelectedItem(pos)) != -1)
	{
		if ((node = m_listObject.GetElement(idx, NULL)) != NULL)
		{
			ObjectInfo *obj = node->obj;
			ConstructCodecList *list = node->codecs;

			str_t suffix = suffix_str[0] != 0 ? suffix_str : NULL;
			ConstructCodecEntry key = { suffix, node->obj }, *entry = list->find(list, &key);

			if (entry != NULL)
			{	// 이미 존재함

				int status = IDOK;
				TCHAR temp_suffix_str[256] = { 0, };
				Dz1STRCPY(temp_suffix_str, suffix_str);

				CString str, msg;
				str.Format(_T("%s 접미사 설정"), obj->name);
				Dz1CodeGenStrDlgParam param =
				{
					FALSE,
					CODEGEN_STR_DLG_ALL,
					str.GetBuffer(),
					_T("API 접미사"),
					_T("확인"), _T("통과"), _T("취소")
				};
				CDz1CodeGenStrDlg dlg(temp_suffix_str, 256, &param);

				do 
				{
					msg.Format(_T("%s%s는 이미 있습니다."), obj->name, temp_suffix_str);
					MessageBox(msg);

					if ((status = (int)dlg.DoModal()) == IDOK)
						key.opt_suffix = temp_suffix_str;
					else break;
				} while (list->find(list, &key) != NULL);

				switch(status)
				{
				case IDOK:		// 확인
					if ((*errp = ConstructCodec_addTodecByObj(m_todec, obj, temp_suffix_str, is_public)).code) ERR_DLG_OUT(errp);
					else Dz1Error_set(errp, 0);
					break;
				case IDNO:		// 통과
					Dz1Error_set(errp, 0);
					break;
				case IDCANCEL:	// 취소
					Dz1Error_set(errp, EINTR);
					break;
				}
			}
			else
			{
				str_t suffix = suffix_str[0] != 0 ? suffix_str : NULL;
				if ((*errp = ConstructCodec_addTodecByObj(m_todec, obj, suffix, is_public)).code) ERR_DLG_OUT(errp);
			}
			m_listObject.RefreshRow(idx);
		}
	}
	ListObjectEvent();
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonTodecDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DZ1_ERROR_SAFE_VAR(errp, err);

	ConstructCodecEntry *entry = NULL;
	POSITION pos = m_listTodec.GetFirstSelectedItemPosition();
	int idx;
	while((idx = m_listTodec.GetNextSelectedItem(pos)) != -1)
	{
		m_listTodec.RemoveRow(idx);
		pos = m_listTodec.GetFirstSelectedItemPosition();
	}
	ListTodecEvent();

	if ((idx = m_listObject.GetCurSelIdx()) >= 0) m_listObject.RefreshRow(idx);
}

static bool_t _ListTodec_setApiMode(void *ptr, ConstructCodecEntry *p, bool_t &refresh)
{
	bool_t stop = FALSE;
	ConstructCodecMode api_mode = *(ConstructCodecMode *)ptr;
	refresh = FALSE;
	if (p->mode != api_mode)
	{
		p->mode = api_mode;
		refresh = TRUE;
	}
	return stop;
}

void CDz1CodeGenTodecDlg::OnCbnSelchangeComboTodec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int v = m_comboTodec.GetCurSel();
	if (v != CB_ERR)
	{
		m_listTodec.TravelSelectedItem(_ListTodec_setApiMode, (void *)&v);
		m_todec->is_dirty = TRUE;
	}
}
// TODEC Control
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ListTodecSeq
void CDz1CodeGenTodecDlg::ListTodecSeqEvent(int *_idx, int *_cnt)
{
	int cnt;
	if (_cnt != NULL) cnt = *_cnt;
	else cnt = m_listTodecSeq.GetSelectedCount();

	int idx;
	if (_idx != NULL) idx = *_idx;
	else
	{
		POSITION pos = m_listTodecSeq.GetFirstSelectedItemPosition();
		idx = m_listTodecSeq.GetNextSelectedItem(pos);
	}

	if (cnt == 0)
	{
		if (idx != -1) ListTodecSeqSelOne(idx);
		else ListTodecSeqSelNone();
	}
	else if (cnt == 1) ListTodecSeqSelOne(idx);
	else ListTodecSeqSelMany(idx, cnt);
}

void CDz1CodeGenTodecDlg::ListTodecSeqSelNone()
{
	// no item Selected Implementation
	m_btnTodecSeqDel.EnableWindow(FALSE);
	m_btnTodecSeqMod.EnableWindow(FALSE);
	m_btnTodecSeqDn.EnableWindow(FALSE);
	m_btnTodecSeqUp.EnableWindow(FALSE);
	m_staticTodecSeqDescr.SetWindowText("");
}

void CDz1CodeGenTodecDlg::ListTodecSeqSelOne(int idx)
{
	// Only one item Selected Implementation
	ConstructMemberCodecEntry *node = m_listTodecSeq.GetElement(idx, NULL);
	if (node == NULL) ListTodecSeqSelNone();
	else
	{
		switch(m_objType)
		{
		default:
		case ObjectType_array:
			m_btnTodecSeqDel.EnableWindow(FALSE);
			m_btnTodecSeqMod.EnableWindow(TRUE);
			m_btnTodecSeqDn.EnableWindow(FALSE);
			m_btnTodecSeqUp.EnableWindow(FALSE);
			break;
		case ObjectType_structure:
			m_btnTodecSeqDel.EnableWindow(TRUE);
			m_btnTodecSeqMod.EnableWindow(TRUE);
			m_btnTodecSeqDn.EnableWindow(TRUE);
			m_btnTodecSeqUp.EnableWindow(TRUE);
			break;
		case ObjectType_union:
			if (Dz1STRCMP(node->instance_name, INSTANCE_NAME_PRESENT) == 0)
				m_btnTodecSeqDel.EnableWindow(TRUE);
			else m_btnTodecSeqDel.EnableWindow(FALSE);

			m_btnTodecSeqMod.EnableWindow(TRUE);
			m_btnTodecSeqDn.EnableWindow(FALSE);
			m_btnTodecSeqUp.EnableWindow(FALSE);
			break;
		}

		TCHAR buf[2048] = { 0 };
		ConstructMemberCodecEntry_getDescript(node, m_todec->endian, buf, 2047);
		m_staticTodecSeqDescr.SetWindowText(buf);
	}
}

void CDz1CodeGenTodecDlg::ListTodecSeqSelMany(int idx, int cnt)
{
	// many item Selected Implementation
	switch(m_objType)
	{
	default:
	case ObjectType_union:
	case ObjectType_array:
		m_btnTodecSeqDel.EnableWindow(FALSE);
		break;
	case ObjectType_structure:
		m_btnTodecSeqDel.EnableWindow(TRUE);
		break;
	}
	m_btnTodecSeqMod.EnableWindow(FALSE);
	m_btnTodecSeqDn.EnableWindow(FALSE);
	m_btnTodecSeqUp.EnableWindow(FALSE);
}

void CDz1CodeGenTodecDlg::OnLvnItemchangedListTodecSeq(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ((pNMLV->uNewState & (LVIS_FOCUSED | LVIS_SELECTED)) == (LVIS_FOCUSED | LVIS_SELECTED))
		ListTodecSeqEvent(&pNMLV->iItem);
	*pResult = 0;
}

void CDz1CodeGenTodecDlg::OnNMClickListTodecSeq(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMItemActivate->iItem == -1) ListTodecSeqSelNone();
	*pResult = 0;
}

void CDz1CodeGenTodecDlg::OnNMDblclkListTodecSeq(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMItemActivate->iItem != -1)
		PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON_TODEC_SEQ_MOD, BN_CLICKED), 0);
	*pResult = 0;
}
// ListTodecSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Sequence Modify
void CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ConstructMemberCodecEntry *node = NULL;
	POSITION pos = m_listTodecSeq.GetFirstSelectedItemPosition();
	int idx = m_listTodecSeq.GetNextSelectedItem(pos);
	while((node = m_listTodecSeq.GetElement(idx, NULL)) != NULL)
	{
		m_listTodecSeq.RemoveRow(idx);
		pos = m_listTodecSeq.GetFirstSelectedItemPosition();
		idx = m_listTodecSeq.GetNextSelectedItem(pos);
		m_todec->is_dirty = TRUE;
	}
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqMod()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int idx = m_listTodecSeq.GetCurSelIdx();
	ConstructMemberCodecEntry *node = m_listTodecSeq.GetElement(idx);
	if (node != NULL)
	{
		ConstructCodecEntry *entry = m_listTodec.GetElement(m_listTodec.GetCurSelIdx());
		if (entry != NULL)
		{
			CDz1CodeGenTodecConfigDlg dlg(&node->info, node, entry->parent_obj, node->instance_name);
			if (dlg.DoModal() == IDOK)
			{
				m_listTodecSeq.RefreshRow(idx);
				m_todec->is_dirty = TRUE;
			}
		}
	}
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqDn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDz1CodeGenTodecDlg::OnBnClickedButtonTodecSeqUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
// Sequence Modify
////////////////////////////////////////////////////////////////////////////////

