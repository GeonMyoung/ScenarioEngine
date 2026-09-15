// dz1_text2array_gui.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH에서 이 파일을 포함하기 전에 'stdafx.h'를 포함하십시오.
#endif

#include "resource.h"		// 주 기호

#include <dz1.h>

#include <windef.h>

#define MY_PATH_MAX		4096
#define MY_FILENAME_MAX	4096
// CText2ArrayApp:
// 이 클래스의 구현에 대해서는 dz1_text2array_gui.cpp을 참조하십시오.
//

class CText2ArrayApp : public CWinApp
{
public:
	CText2ArrayApp();

// 재정의
	public:
	virtual BOOL InitInstance();

// 구현

	DECLARE_MESSAGE_MAP()
};

extern CText2ArrayApp theApp;

DZ1_CPPLINK bool_t MyGetPath(HWND owner, TCHAR *initialPAth, TCHAR path[MY_PATH_MAX], TCHAR *title);
DZ1_CPPLINK bool MyGetFile(CWnd *parentWindow, TCHAR *initialPath, TCHAR path[4096], TCHAR filename[4096], TCHAR *extFilter, TCHAR *defaultExt);
