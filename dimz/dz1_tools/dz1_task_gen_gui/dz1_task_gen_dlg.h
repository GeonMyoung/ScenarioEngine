// dz1_task_gen_dlg.h : 헤더 파일
//

#pragma once
#include "dz1_task_gen_combo_box.h"
#include "ListCtrlLibraries.h"


// CDz1TaskGen_dlg 대화 상자
class CDz1TaskGen_dlg : public CDialog
{
// 생성
public:
	CDz1TaskGen_dlg(CWnd* pParent = NULL);	// 표준 생성자
	virtual ~CDz1TaskGen_dlg();

// 대화 상자 데이터
	enum { IDD = IDD_DZ1_TASK_GEN_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원

private:
	//////////////////////////////////////////////////
	// Target
	CComboBoxGenTarget		 m_comboGenTarget;
	CComboBoxGenTxtMode		 m_comboGenTxtMode;
	CButton					 m_chkIncludeTestCode;

	CEdit					 m_editParentPath;
	CButton					 m_bParentPath;
	TCHAR					 m_parentPath[MY_MAX_PATH];

	CEdit					 m_editProjName;

	CComboBoxGenArgs2Naming	 m_comboNameRule;
	CEdit					 m_editNameRule;
	// Target
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Foundation Library
	CEdit					 m_editCodeconvRoot;
	CButton					 m_bCodeconvRoot;
	TCHAR					 m_codeconvAbs[MY_MAX_PATH];

	CEdit					 m_editDimzDz1Root;
	CButton					 m_bDimzDz1Root;
	TCHAR					 m_dimzAbs[MY_MAX_PATH];

	CComboBoxGenEndian		 m_comboDimzDz1Endian;
	void					 InitComboDimzDz1Endian(void);
	// Foundation Library
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Additional Library
	GenArgs2LibraryInfo		*m_list_libraries;
	CListCtrlLibraries		 m_listLibraries;
	void					 ListLibrariesEvent(int *_idx = NULL, int *_cnt = NULL);
	void					 ListLibrariesSelNone();
	void					 ListLibrariesSelOne(int idx);
	void					 ListLibrariesSelMany(int idx, int cnt);
	CEdit					 m_editLibrary;

	CButton					 m_bLibraryAdd;
	CButton					 m_bLibraryDel;
	CButton					 m_bLibraryUp;
	void					 m_bLibraryUpEnable(bool_t en, int idx = -1);
	CButton					 m_bLibraryDown;
	void					 m_bLibraryDownEnable(bool_t en, int idx = -1);
	// Additional Library
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Visual Studio
	CButton					 m_chkGenVc90Proj;
	CButton					 m_chkGenVs2022Proj;
	CButton					 m_chkGenSolution;

	CEdit					 m_editPthreadRoot;
	CButton					 m_bPthreadRoot;
	TCHAR					 m_pthreadAbs[MY_MAX_PATH];
	// Visual Studio
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Command-Line Build
	CButton					 m_chkGenGnuMakefile;
	// Command-Line Build
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Global Control
	void					 ApplyGenArgs(GenArgs2 *src);		// load

	CButton					 m_bSave;
	CButton					 m_bGenerate;
	GenArgs2				*CreateGenArgs(void);
	// Global Control
	//////////////////////////////////////////////////

	TCHAR					 m_initialPath[MY_MAX_PATH];
	void					 LoadInitialPath(void);
	void					 SaveInitialPath(void);

	void					 EnableRootButtons(void);
	void					 EnableGenButton(void);
	void					 EnableGenSolutionChk(void);

	TCHAR					 m_projRootAbs[MY_MAX_PATH];
	void					 ProjectRootUpdate(void);
	bool_t					 SetProjRoot(void);
	// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
public:
	//////////////////////////////////////////////////
	// Target
	afx_msg void OnBnClickedButtonParentPath();
	afx_msg void OnEnKillfocusEditProjName();
	afx_msg void OnCbnSelchangeComboNameRule();
	// Target
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Foundation Library
	afx_msg void OnBnClickedButtonCodeconvRoot();
	afx_msg void OnBnClickedButtonDimzRoot();
	// Foundation Library
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Additional Library
	afx_msg void OnLvnItemchangedListLibraries(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListLibraries(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListLibraries(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAddProject();
	afx_msg void OnBnClickedButtonDeletePriject();
	// Additional Library
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Visual Studio
	afx_msg void OnBnClickedCheckGenVc90Proj();
	afx_msg void OnBnClickedCheckGenVs2022Proj();
	afx_msg void OnBnClickedButtonPthreadRoot();
	// Visual Studio
	//////////////////////////////////////////////////

	//////////////////////////////////////////////////
	// Global Control
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonGenerate();
	// Global Control
	//////////////////////////////////////////////////
	afx_msg void OnBnClickedButtonLibraryUp();
	afx_msg void OnBnClickedButtonLibraryDown();
};
