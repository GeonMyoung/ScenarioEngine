#pragma once

#include "dz1_task_gen.h"
#include "dz1_task_gen_combo_box.h"

// CDz1ProjSelDlg 대화 상자입니다.

class CDz1ProjSelDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1ProjSelDlg)

public:
	// flag = 이미 등록된 type은 해당 bit를 1로 설정하여 들어옴
	CDz1ProjSelDlg(GenArgs2LibraryEntry *owner, GenArgs2VisualStudioEntry **ret, Dz1Str libRootPath, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1ProjSelDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DZ1_PROJ_SEL_DIALOG };

private:
	CComboBoxProjectVer			 m_comboProjVer;;
	CEdit						 m_editProjPathName;

	GenArgs2LibraryEntry		*m_owner;
	GenArgs2VisualStudioEntry	**m_ret;
	GenArgs2VisualStudioEntry	*m_dst;

	TCHAR						 m_initialPath[MY_MAX_PATH];
	TCHAR						 m_path[MY_MAX_PATH];
	TCHAR						 m_name_ext[MY_MAX_PATH];
//	TCHAR						 m_ext[1024];
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonProjPathname();
	afx_msg void OnBnClickedButtonOk();
};
