#ifndef DZ1_FILE_SELECT_DLG_H
#define DZ1_FILE_SELECT_DLG_H

#include <dz1.h>
#include <dz1_mfc.h>
DZ1_CPPLINK BOOL Dz1MfcPathSelectDlg(HWND owner, TCHAR *initialPath, TCHAR path[DZ1_FILE_SELECT_PATH_LEN], TCHAR *title);
DZ1_CPPLINK BOOL Dz1MfcPathSelectDlg2(HWND owner, TCHAR in_out_path[DZ1_FILE_SELECT_PATH_LEN], TCHAR *title);

DZ1_CPPLINK BOOL Dz1MfcFileSelectDlg(CWnd *parentWindow,
									 BOOL isOpenWindow,
									 TCHAR *initialPath,	// can be NULL
									 TCHAR *name_suggest,	// can be NULL
									 TCHAR *extFilter,		// "Filter Name(*.xxx)|*.ext|"
									 TCHAR *defaultExt,		// ext
									 TCHAR ret_path[DZ1_FILE_SELECT_PATH_LEN],
									 TCHAR ret_name[DZ1_FILE_SELECT_NAME_LEN]);


#endif