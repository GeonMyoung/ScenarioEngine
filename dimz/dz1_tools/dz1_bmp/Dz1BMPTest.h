// Dz1BMPTest.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH에서 이 파일을 포함하기 전에 'stdafx.h'를 포함하십시오.
#endif

#include "resource.h"		// 주 기호


// CDz1BMPTestApp:
// 이 클래스의 구현에 대해서는 Dz1BMPTest.cpp을 참조하십시오.
//

class CDz1BMPTestApp : public CWinApp
{
public:
	CDz1BMPTestApp();

// 재정의
	public:
	virtual BOOL InitInstance();

// 구현

	DECLARE_MESSAGE_MAP()
};

extern CDz1BMPTestApp theApp;

bool MyGetFile(CWnd *parentWindow, TCHAR *initialPath, TCHAR path[4096], TCHAR filename[4096], TCHAR *extFilter, TCHAR *defaultExt);
