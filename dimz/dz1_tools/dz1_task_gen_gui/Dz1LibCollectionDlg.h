#pragma once
#include <dz1_task_gen_args.h>
#include "ListCtrlProjects.h"

// CDz1SelectionDlg 대화 상자입니다.

class CDz1LibCollectionDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1LibCollectionDlg)

public:
	CDz1LibCollectionDlg(CString &title, Dz1Str initialPath, GenArgs2LibraryEntry **ret, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1LibCollectionDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LIB_COLLECTION_DLG };

private:
	CEdit					 m_editRootPath;

	CEdit					 m_editIncludePath;
	CButton					 m_btnIncludePath;

	CEdit					 m_editLibraryPath;
	CButton					 m_btnLibraryPath;

	CListCtrlProjects		 m_listProjects;
	void					 ListProjectsEvent(int *_idx = NULL, int *_cnt = NULL);
	void					 ListProjectsSelNone();
	void					 ListProjectsSelOne(int idx);
	void					 ListProjectsSelMany(int idx, int cnt);

	CButton					 m_bAddProject;
	CButton					 m_bDeleteProject;

	GenArgs2LibraryEntry	**m_ret;
	GenArgs2LibraryEntry	 *m_dst;

	CString					 m_title;

	TCHAR					 m_initialPath[MY_MAX_PATH];

	void					 SetIncPath(Dz1Str lib_root_abs);
	void					 SetLibPath(Dz1Str lib_root_abs);
	Dz1Error				 ChkAndAddProj(Dz1Str lib_root_abs, GenArgs2VisualStudioVerSupport ver);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonRootPath();
	afx_msg void OnBnClickedButtonIncludePath();
	afx_msg void OnBnClickedButtonLibraryPath();
	afx_msg void OnBnClickedButtonAddProject();
	afx_msg void OnNMClickListProjects(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDeleteProject();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnLvnItemchangedListProjects(NMHDR *pNMHDR, LRESULT *pResult);
};
