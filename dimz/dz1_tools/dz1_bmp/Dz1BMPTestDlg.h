// Dz1BMPTestDlg.h : 헤더 파일
//

#pragma once


// CDz1BMPTestDlg 대화 상자
class CDz1BMPTestDlg : public CDialog
{
// 생성
public:
	CDz1BMPTestDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_DZ1BMPTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원

private:
	CStatic					m_staticBMP;

	TCHAR					m_initialPath[4096];
	CBitmap					m_bmpData;
// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLoad();
};
