#pragma once
#include "Dz1CodeGenTodecHelper.h"

// CDz1CodeGenTodecDlg 대화 상자입니다.

class CDz1CodeGenTodecDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1CodeGenTodecDlg)

public:
	CDz1CodeGenTodecDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1CodeGenTodecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TODEC_DLG };

private:
	CButton										 m_btnSetting;

	CComboBox									 m_comboEndian;

	CButton										 m_btnNew;
	CButton										 m_btnLoad;
	CButton										 m_btnSave;
	CButton										 m_btnPublish;

	CListCtrlConstructCodecInclude				 m_listInclude;
	void										 ListIncludeEvent(int *_idx=NULL, int *_cnt=NULL);
	void										 ListIncludeSelNone();
	void										 ListIncludeSelOne(int idx);
	void										 ListIncludeSelMany(int idx, int cnt);

	CButton										 m_btnIncludeAdd;
	CButton										 m_btnIncludeDel;
	CComboBox									 m_comboInclude;

	CListCtrlConstructObject					 m_listObject;
	void										 ListObjectEvent(int *_idx = NULL, int *_cnt = NULL);
	void										 ListObjectSelNone();
	void										 ListObjectSelOne(int idx);
	void										 ListObjectSelMany(int idx, int cnt);

	CButton										 m_btnObjectSrc;
	CButton										 m_btnObjectHdr;

	CListCtrlConstructCodec						 m_listTodec;
	void										 ListTodecEvent(int *_idx=NULL, int *_cnt=NULL);
	void										 ListTodecSelNone();
	void										 ListTodecSelOne(int idx);
	void										 ListTodecSelMany(int idx, int cnt);

	CButton										 m_btnTodecAdd;
	CButton										 m_btnTodecDel;
	CComboBox									 m_comboTodec;

	CListCtrlConstructMemberCodec				 m_listTodecSeq;
	void										 ListTodecSeqEvent(int *_idx=NULL, int *_cnt=NULL);
	void										 ListTodecSeqSelNone();
	void										 ListTodecSeqSelOne(int idx);
	void										 ListTodecSeqSelMany(int idx, int cnt);

	CButton										 m_btnTodecSeqAdd;

	CButton										 m_btnTodecSeqDel;
	ObjectType									 m_objType;

	CButton										 m_btnTodecSeqMod;
	CButton										 m_btnTodecSeqUp;
	CButton										 m_btnTodecSeqDn;

	CStatic										 m_staticTodecSeqDescr;


	ConstructCodec								*m_todec;
	TCHAR										 m_tdo_path[4096];
	TCHAR										 m_todeo_path[4096];

//	TCHAR										 m_todeo_name[1024];
	void										 DataLoad(void);
	void										 UpdateEndianString(void);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnLvnItemchangedListObject(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListObject(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListObject(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnLvnItemchangedListTodec(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListTodec(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTodec(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnLvnItemchangedListTodecSeq(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListTodecSeq(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTodecSeq(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonTodecAdd();
	afx_msg void OnBnClickedButtonTodecDel();
	afx_msg void OnBnClickedButtonTodecSeqAdd();
	afx_msg void OnBnClickedButtonTodecSeqDel();
	afx_msg void OnBnClickedButtonTodecSeqMod();
	afx_msg void OnBnClickedButtonTodecSeqDn();
	afx_msg void OnBnClickedButtonTodecSeqUp();
//	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonObjectSrc();
	afx_msg void OnBnClickedButtonObjectHdr();
	afx_msg void OnBnClickedButtonPublish();
	afx_msg void OnLvnItemchangedListInclude(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListInclude(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboInclude();
	afx_msg void OnCbnSelchangeComboTodec();
	afx_msg void OnBnClickedButtonIncludeAdd();
	afx_msg void OnBnClickedButtonIncludeDel();
	afx_msg void OnCbnSelchangeComboEndian();
	afx_msg void OnCbnEditchangeComboEndian();
	afx_msg void OnBnClickedButtonObjectDel();
};
