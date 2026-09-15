========================================================================
    정적 라이브러리 : dz1_task_gen 프로젝트 개요
========================================================================

응용 프로그램 마법사에서 이 dz1_task_gen 라이브러리 프로젝트를 만들었습니다. 
이 파일에는 dz1_task_gen 응용 프로그램을 구성하는 각각의 파일에
들어 있는 요약 설명이 포함되어 있습니다.


dz1_task_gen.vcproj
    응용 프로그램 마법사를 사용하여 생성한 VC++ 프로젝트의 기본 프로젝트 파일입니다. 
    해당 파일을 생성한 Visual C++의 버전 정보를 비롯하여 
    응용 프로그램 마법사에서 선택한 플랫폼, 구성 및 
    프로젝트 기능에 대한 정보가 들어 있습니다.


/////////////////////////////////////////////////////////////////////////////

StdAfx.h 및 StdAfx.cpp는
    dz1_task_gen.pch라는 이름의 PCH(미리 컴파일된 헤더) 파일과
    StdAfx.obj라는 이름의 미리 컴파일된 형식 파일을 빌드하는 데 사용됩니다.

/////////////////////////////////////////////////////////////////////////////
기타 참고:

응용 프로그램 마법사에서 사용하는 "TODO:" 주석은 사용자가 추가하거나 사용자 지정해야 하는
소스 코드 부분을 나타냅니다.

/////////////////////////////////////////////////////////////////////////////
PROJ_NAME                       foo_bar
PROJ_TEST_NAME                  foo_bar_test
PROJ_STRUCT_NAME                FooBar
PROJ_TDC_NAME                   foo_bar_def
PROJ_HDR_DEFINE                 FOO_BAR
STRUCT_ARG_NAME                 FooBarArg
PROJ_ARG_NAME                   foo_bar_arg
STRUCT_ENV_NAME                 FooBarEnv
PROJ_ENV_NAME                   foo_bar_env
STRUCT_TMR_NAME                 FooBarTimer
PROJ_TMR_NAME                   foo_bar_timer
PROJ_TMR_UTIL_NAME              foo_bar_timer_util
STRUCT_MSG_NAME                 FooBarMsg
PROJ_MSG_NAME                   foo_bar_msg
PROJ_MSGS_NAME                  foo_bar_msgs

PROJ_TARGET_GUID                {.....} : GUID of Target Project
PROJ_TEST_GUID                  {.....} : GUID of Test Project
PROJ_INCLUDES                   path#1;path#2;...path#n
SYSTEM_ENDIAN_DEF               __SYSTEM_ENDIAN_LITTLE__
DIMZ_TOOLS_PATH                 ..\..\..\dimz\dz1_tools
PTHREAD_ROOT                    ..\..\..\pthreads.2

    PROJ_DBG_INFO_TYPE              1=C7, 0=사용 안 함
    PROJ_OPTIMIZE                   0=사용안함, 2=속도최적화
    PROJ_EXPANSION                  0=기본값 / 1=__inline만 확장
    PROJ_TYPE_DEF                   _LIB or _CONSOLE
    PROJ_BUILD_TYPE                 _DEBUG or NDEBUG
    PROJ_RUNTIME_CHK                3=모두, 0=기본값
    PROJ_RUNTIME_LIB                0=MT, 1=MD, 2=MTd, 3=MDd

    COMMON_PREDEF                   __CLEANUP_C;__SYSTEM_ENDIAN_LITTLE__                전처리기 공통정의
    PLATFORM_WORD_SIZE              32 or 64


    TARGET_MACHINE                  1=x86
