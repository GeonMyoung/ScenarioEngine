#ifndef UNIX_SYSTEM
#if defined(WIN32)
#include <dz1.h>
#include <dz1_thread_stdio.h>
#include <WinSvc.h>
#pragma comment(lib, "advapi32.lib")
#include "dz1_daemon.h"

///////////////////////////////////////////////////////////////////////////////
// Service Control
static void _ServiceHandle_cancel(void *ptr)
{
	SC_HANDLE h = (SC_HANDLE)ptr;
	CloseServiceHandle(h);
}

bool_t Dz1DaemonServiceCreate(Dz1Str serviceName, Dz1Str displayServiceName, Dz1Str exePath, Dz1Str description, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	SC_HANDLE schSCManager = NULL;

	
    if ((schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE)) == NULL) ERR_SET_OUT(errp, GetLastError());
	else 
	{
	    SC_HANDLE schService   = NULL;
		pthread_cleanup_push(_ServiceHandle_cancel, (void *)schSCManager);
		if ((schService = CreateService(schSCManager,												// SCManager database 
										serviceName,												// name of service
										displayServiceName,											// service name to display
										SERVICE_ALL_ACCESS,											// desired access
										SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,	// service type
										SERVICE_AUTO_START,											// start type
										SERVICE_ERROR_NORMAL,										// error control type 
										exePath,													// service's binary
										NULL,														// no load ordering group
										NULL,														// no tag identifier
										NULL,														// no dependencies
										NULL,														// LocalSystem account
										NULL)) == NULL)	ERR_SET_OUT(errp, GetLastError());			// no password
		else
		{
			SERVICE_DESCRIPTION Desc;
			pthread_cleanup_push(_ServiceHandle_cancel, (void *)schService);

			Desc.lpDescription = description;
			if (ChangeServiceConfig2(schService, SERVICE_CONFIG_DESCRIPTION, &Desc) == FALSE) ERR_SET_OUT(errp, GetLastError());
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (_CreateService_cancel, (void *)schService);
		}
		pthread_cleanup_pop(1); // (_OpenSCManager_cancel, (void *)schSCManager);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1DaemonServiceStart(Dz1Str serviceName, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SC_HANDLE schSCManager = NULL;
	if ((schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) ERR_SET_OUT(errp, GetLastError());
	else
	{
		SC_HANDLE schService   = NULL;
		pthread_cleanup_push(_ServiceHandle_cancel, (void *)schSCManager);
		if ((schService  = OpenService(schSCManager, serviceName, SERVICE_ALL_ACCESS)) == NULL) ERR_SET_OUT(errp, GetLastError());

		else
		{
			pthread_cleanup_push(_ServiceHandle_cancel, (void *)schService);
			if (StartService(schService, 0, NULL) == FALSE) ERR_SET_OUT(errp, GetLastError());
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (_ServiceHandle_cancel, (void *)schService);
		}
		pthread_cleanup_pop(1); // (_ServiceHandle_cancel, (void *)schSCManager);
	}
	return errp->code == 0 ? TRUE : FALSE;;
}

bool_t Dz1DaemonServiceStop(Dz1Str serviceName, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
    SC_HANDLE schSCManager = NULL;
 
    //1. 서비스를 오픈한다.
    if ((schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) ERR_SET_OUT(errp, GetLastError());
	else
	{
	    SC_HANDLE schService   = NULL;
		pthread_cleanup_push(_ServiceHandle_cancel, (void *)schSCManager);
		if ((schService  = OpenService(schSCManager, serviceName, SERVICE_ALL_ACCESS)) == NULL) ERR_SET_OUT(errp, GetLastError());
		else
		{
			u32_t nRpt = 50;
			SERVICE_STATUS ss;
			pthread_cleanup_push(_ServiceHandle_cancel, (void *)schService);
			while(nRpt)
			{
				if (QueryServiceStatus(schService, &ss) == FALSE) ERR_SET_OUT(errp, GetLastError());		 
				else if(ss.dwCurrentState != SERVICE_STOPPED)
				{
					if (ControlService(schService, SERVICE_CONTROL_STOP, &ss) == FALSE) ERR_SET_OUT(errp, GetLastError());
					else Sleep(2000);
				}
				else
				{
					Dz1Error_set(errp, 0);
					break;
				}
				nRpt--;
			}
			pthread_cleanup_pop(1); // (_ServiceHandle_cancel, (void *)schService);
		}
 		pthread_cleanup_pop(1); // (_ServiceHandle_cancel, (void *)schSCManager);
	} 
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1DaemonServiceDelete(Dz1Str serviceName, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
    SC_HANDLE schSCManager = NULL;
 
    if ((schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)) == NULL) ERR_SET_OUT(errp, GetLastError());
	else
	{
	    SC_HANDLE schService   = NULL;
		pthread_cleanup_push(_ServiceHandle_cancel, (void *)schSCManager);
		if ((schService = OpenService(schSCManager, serviceName, SERVICE_ALL_ACCESS)) == NULL) ERR_SET_OUT(errp, GetLastError());
		else
		{
			pthread_cleanup_push(_ServiceHandle_cancel, (void *)schService);
			if (DeleteService(schService) == FALSE) ERR_SET_OUT(errp, GetLastError());
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (_ServiceHandle_cancel, (void *)schService);
		}
		pthread_cleanup_pop(1); // (_ServiceHandle_cancel, (void *)schSCManager);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Service Control
///////////////////////////////////////////////////////////////////////////////

static SERVICE_STATUS	g_ServiceStatus		= { 0, };
SERVICE_STATUS_HANDLE	g_StatusHandle		= NULL;

typedef struct Dz1DaemonUserProc
{
	TCHAR		 service_name[256];
	UserApiF	 Perform;
	UserApiF	 Stop;
	void		*user_ptr;

	TCHAR		 init_path[1024];
} Dz1DaemonUserProc;
static Dz1DaemonUserProc g_userProc = { { 0, }, NULL, NULL, NULL };

static VOID WINAPI ServiceCtrlHandler(DWORD CtrlCode)
{
	switch(CtrlCode)
	{
	case SERVICE_CONTROL_STOP:
		if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING) { }
		else
		{
			// Task Stop
			g_userProc.Stop(g_userProc.user_ptr);

			g_ServiceStatus.dwControlsAccepted = 0;
			g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
			g_ServiceStatus.dwWin32ExitCode = 0;
			g_ServiceStatus.dwCheckPoint = 4;
			if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
			{
				Dz1Thread_printf("ServiceMain() : SetServiceStatus return FAIL\n");
			}
		}
		break;
	default:
		break;
	}
}

static VOID WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	DWORD Status = E_FAIL;
	if (Dz1Str_isVoid(g_userProc.init_path) == FALSE)
		Dz1Dir_chdir(g_userProc.init_path);

	if ((g_StatusHandle = RegisterServiceCtrlHandler(g_userProc.service_name, ServiceCtrlHandler)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		memset(&g_ServiceStatus, 0, sizeof(g_ServiceStatus));
		g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
		g_ServiceStatus.dwControlsAccepted = 0;
		g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
		g_ServiceStatus.dwWin32ExitCode = 0;
		g_ServiceStatus.dwServiceSpecificExitCode = 0;
		g_ServiceStatus.dwCheckPoint = 0;

		if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
			Dz1Thread_printf("ServiceMain() : SetServiceStatus return FAIL\n");

		g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
		g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		g_ServiceStatus.dwWin32ExitCode = 0;
		g_ServiceStatus.dwCheckPoint = 0;
		if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
			Dz1Thread_printf("ServiceMain() : SetServiceStatus return FAIL\n");

		// Task Start
		g_userProc.Perform(g_userProc.user_ptr);

		g_ServiceStatus.dwControlsAccepted = 0;
		g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		g_ServiceStatus.dwWin32ExitCode = 0;
		g_ServiceStatus.dwCheckPoint = 3;
		if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
			Dz1Thread_printf("ServiceMain() : SetServiceStatus return FAIL\n");
	}
}

static bool_t _is_abs_path(Dz1Str path)
{
	if (Dz1STRLEN(path) >= 2 && Dz1ISALPHA((int)path[0]) && path[1] == Dz1Text(':')) return TRUE;
	else return FALSE;
}

static bool_t _init_user_proc(Dz1Str ServiceName, Dz1Str InitPath, UserApiF Perform, UserApiF Stop, void *ptr, Dz1Error *errp)
{
	if (Dz1Str_isVoid(ServiceName) == TRUE || Dz1STRLEN(ServiceName) > 256) ERR_SET_OUT(errp, EINVAL);
	else if (Perform == NULL || Stop == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Str_isVoid(InitPath) == FALSE && _is_abs_path(InitPath) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1STRCPY(g_userProc.service_name, ServiceName);
		g_userProc.Perform = Perform;
		g_userProc.Stop = Stop;
		g_userProc.user_ptr = ptr;
		if (Dz1Str_isVoid(InitPath)) g_userProc.init_path[0] = 0;
		else Dz1STRCPY(g_userProc.init_path, InitPath);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1DaemonMain(Dz1Str ServiceName, Dz1Str InitialPath, UserApiF Perform, UserApiF Stop, void *ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (_init_user_proc(ServiceName, InitialPath, Perform, Stop, ptr, errp) == FALSE) ERR_OUT(errp);
	else
	{
		SERVICE_TABLE_ENTRY ServiceTable[] =
		{
			{ g_userProc.service_name, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
			{ NULL, NULL }
		};

		if (StartServiceCtrlDispatcher(ServiceTable) == FALSE) ERR_SET_OUT(errp, GetLastError());
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#endif	// WIN32
#endif	// UNIX_SYSTEM