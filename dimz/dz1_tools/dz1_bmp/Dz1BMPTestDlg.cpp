// Dz1BMPTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include <dz1_bmp.h>
#include "Dz1BMPTest.h"
#include "Dz1BMPTestDlg.h"
#include ".\dz1bmptestdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDz1BMPTestDlg 대화 상자



CDz1BMPTestDlg::CDz1BMPTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDz1BMPTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_initialPath, 0, 4096);
}

void CDz1BMPTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BMP, m_staticBMP);
}

BEGIN_MESSAGE_MAP(CDz1BMPTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CDz1BMPTestDlg 메시지 처리기

BOOL CDz1BMPTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CDz1BMPTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CDz1BMPTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDz1BMPTestDlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR path[4096], name[4096];
	if (MyGetFile(NULL, m_initialPath, path, name, _T("*.bmp"), _T("bmp")) == TRUE)
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;

		strcpy(m_initialPath, path);

		char filename[4096];
		sprintf(filename, "%s" DIR_SEPRATOR "%s", path, name);

		Dz1Binary *image = Dz1BinFile_load(filename, &err);
		if (image == NULL) ERR_DLG_OUT(&err);
		else
		{
			Dz1BMP *bmp = NULL;
			pthread_cleanup_push(Dz1Binary_del, (void *)image);
			if ((bmp = Dz1BMP_gen(&err)) == NULL) ERR_DLG_OUT(&err);
			else
			{
				pthread_cleanup_push(Dz1BMP_delAndSetNull, (void *)&bmp);
				if (Dz1BMP_dec(bmp, image->data, image->size, &err) < 0) ERR_DLG_OUT(&err);
				else
				{
//					CDC *pDC = GetDC();
					Dz1BMPDIB *h = bmp->hdr;
					Dz1Binary *img = bmp->chunk;

					m_bmpData.DeleteObject();
//					m_bmpData.CreateCompatibleBitmap(pDC, h->width, h->height);
					bool_t ret = m_bmpData.CreateBitmap(h->width, h->height, h->planes, h->bpp, img->data);
					m_staticBMP.SetBitmap((HBITMAP)m_bmpData);

					Dz1Thread_printf("DIB Header = ");
					Dz1BMPDIB_dump(h, 0);
				}
				pthread_cleanup_pop(1); // (Dz1BMP_delAndSetNull, (void *)&bmp);
			}
			pthread_cleanup_pop(1); // (Dz1Binary_del, (void *)image);
		}
	}
}


