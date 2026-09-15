
// dz1_code_gen_gui_dlg.h : 헤더 파일
//

#pragma once

#include <dz1_error.h>
#include <Dz1CodeGen.h>

#define CODE_GEN_ARG_MAX			4

typedef struct CodeGenControl
{
	CComboBox				 mode;
	CStatic					 label[CODE_GEN_ARG_MAX];
	CEdit					 arg[CODE_GEN_ARG_MAX];
} CodeGenControl;

typedef str_t (*StringGenFunc)(int num);
typedef Dz1Error (*GeneratorFunc)(str_t *ret, int type, ...);

// CDz1CodeGenGuiDlg 대화 상자
class CDz1CodeGenGuiDlg : public CDialog
{
// 생성입니다.
public:
	CDz1CodeGenGuiDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAIN_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	CodeGenControl			 m_controlListGen;
	CodeGenControl			 m_controlStubGen;
	CodeGenControl			 m_controlParserGen;
	CodeGenControl			 m_controlShellGen;

	void					 ListCodeGenArgSetup(int idx);

	void					 CopyTextToClipboard(TCHAR *text);
	void					 CodeGenControlDDXInit(CDataExchange *pDX, CodeGenControl *control,
												   Dz1CodeGenControlInfo *table, u32_t idc_combo_mode);
	void					 CodeGenControlComboChanged(CodeGenControl *dst, Dz1CodeGenSetupTable *table);
	Dz1Error				 CodeGenControlOnInitDialog(CodeGenControl *dst,
												   StringGenFunc func, int num_max,
												   Dz1CodeGenSetupTable *table);
	Dz1Error				 CodeGenControlGenerate(CodeGenControl *src, Dz1CodeGenSetupTable *_table, GeneratorFunc generator);

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboListMode();
	afx_msg void OnBnClickedButtonListCodeGen();
	afx_msg void OnBnClickedButtonStubCodeGen();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonParserCodeGen();
	afx_msg void OnCbnSelchangeComboParserMode();
	afx_msg void OnCbnSelchangeComboStubMode();
	afx_msg void OnCbnSelchangeComboShellMode();
	afx_msg void OnBnClickedButtonShellCodeGen();
	afx_msg void OnBnClickedButtonTodec();
	afx_msg void OnBnClickedButtonKeygen();
};
