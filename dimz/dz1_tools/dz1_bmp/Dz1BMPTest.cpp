// Dz1BMPTest.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include <dz1_cleanup.h>
#include <dz1_malloc.h>
#include "Dz1BMPTest.h"
#include "Dz1BMPTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDz1BMPTestApp

BEGIN_MESSAGE_MAP(CDz1BMPTestApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDz1BMPTestApp 생성

CDz1BMPTestApp::CDz1BMPTestApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CDz1BMPTestApp 개체입니다.

CDz1BMPTestApp theApp;


// CDz1BMPTestApp 초기화
FILE *logFP = NULL;
static void _output_hook(void *ptr, unsigned char *data, size_t size)
{
	if (logFP != NULL)
	{
		fwrite(data, size, 1, logFP);
		fflush(logFP);
	}
}

static void _memory_export(void *ptr)
{
	if (logFP != NULL)
		Dz1Mem_export(logFP, TRUE);
}

BOOL CDz1BMPTestApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControls()가 필요합니다. 
	// InitCommonControls()를 사용하지 않으면 창을 만들 수 없습니다.
	Dz1Cleanup_init();
	if ((logFP = fopen("Dz1BMPTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_output_hook, NULL);
	Dz1Cleanup_setMemoryExporter(_memory_export, NULL);

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성한 응용 프로그램"));

	CDz1BMPTestDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 대화 상자가 확인을 눌러 없어지는 경우 처리할
		// 코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 대화 상자가 취소를 눌러 없어지는 경우 처리할
		// 코드를 배치합니다.
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고
	// 응용 프로그램을 끝낼 수 있도록 FALSE를 반환합니다.
	return FALSE;
}

bool MyGetFile(CWnd *parentWindow, TCHAR *initialPath, TCHAR path[4096], TCHAR filename[4096], TCHAR *extFilter, TCHAR *defaultExt)
{
	memset(path, 0, sizeof(TCHAR) * 4096);
	memset(filename, 0, sizeof(TCHAR) * 4096);

	TCHAR filter[1024], defExt[1024];

	if (extFilter && strlen(extFilter) > 0)
		sprintf(filter, "All File(*.*)|%s|*.*||", extFilter);
	else strcpy(filter, "All File(*.*)|*.*||");

	if (defaultExt && strlen(defaultExt) > 0)
		strcpy(defExt, defaultExt);
	else strcpy(defExt, "");

	CFileDialog getFile(TRUE, defExt, _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, parentWindow);
	getFile.m_ofn.lpstrInitialDir = initialPath;
	getFile.m_ofn.lpstrFile = filename;
	getFile.m_ofn.nMaxFile = FILENAME_MAX;

	INT_PTR status = getFile.DoModal();
	if (status == IDOK)
	{
		TCHAR *cp = NULL;
#ifdef UNICODE
		if ((cp = wcsrchr(filename, DIR_SEP)) != NULL)
#else
		if ((cp = strrchr(filename, DIR_SEP)) != NULL)
#endif
		{
			*cp++ = '\0';
#ifdef UNICODE
			wcscpy(path, filename);
			wcscpy(filename, cp);
#else
			strcpy(path, filename);
			strcpy(filename, cp);
#endif
		}
		return TRUE;
	}
	else return FALSE;
}

