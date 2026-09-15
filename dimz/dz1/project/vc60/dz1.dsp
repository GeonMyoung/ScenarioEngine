# Microsoft Developer Studio Project File - Name="dz1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dz1 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dz1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dz1.mak" CFG="dz1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dz1 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "dz1 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dz1 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "dz1 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./include" /I "../../pthreads.2" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__CLEANUP_C" /D "DZ1_BUILD" /D __WORDSIZE=32 /D "__SYSTEM_ENDIAN_LITTLE__" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "dz1 - Win32 Release"
# Name "dz1 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "kernel"

# PROP Default_Filter "*.c"
# Begin Source File

SOURCE=.\src\kernel\dz1_bits.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_cleanup.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_console.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_console.h
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_console_prompt.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_console_prompt.h
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_console_tty_platform.h
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_console_tty_win32crt.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_error.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_int.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_malloc.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_mutex.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_serial.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_stdio.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_str.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_sync.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_thread.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_thread.h
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_thread_entry.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_thread_entry.h
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_thread_hash.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_thread_hash.h
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_thread_misc.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_thread_pool.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_thread_pool.h
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_time.c
# End Source File
# Begin Source File

SOURCE=.\src\kernel\dz1_usleep.c
# End Source File
# End Group
# Begin Group "struct"

# PROP Default_Filter "*.c"
# Begin Source File

SOURCE=.\src\struct\dz1_aatree.c
# End Source File
# Begin Source File

SOURCE=.\src\struct\dz1_fifo.c
# End Source File
# Begin Source File

SOURCE=.\src\struct\dz1_fifo_dynamic.c
# End Source File
# Begin Source File

SOURCE=.\src\struct\dz1_fifo_dynamic.h
# End Source File
# Begin Source File

SOURCE=.\src\struct\dz1_fifo_static.c
# End Source File
# Begin Source File

SOURCE=.\src\struct\dz1_fifo_static.h
# End Source File
# Begin Source File

SOURCE=.\src\struct\dz1_list.c
# End Source File
# End Group
# Begin Group "task"

# PROP Default_Filter "*.c"
# Begin Source File

SOURCE=.\src\task\dz1_sigmsg.c
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_sigmsg.h
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_sigmsg_fifo.c
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_sigmsg_fifo.h
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_sigmsg_queue.c
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_sigmsg_queue.h
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_task.c
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_task_sigmsg_router.c
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_task_sigmsg_router.h
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_task_timer.c
# End Source File
# Begin Source File

SOURCE=.\src\task\dz1_task_timer.h
# End Source File
# End Group
# Begin Group "termio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\termio\dz1_termio.c
# End Source File
# Begin Source File

SOURCE=.\src\termio\dz1_termio.h
# End Source File
# Begin Source File

SOURCE=.\src\termio\dz1_termio_ansi.c
# End Source File
# Begin Source File

SOURCE=.\src\termio\dz1_termio_ansi.h
# End Source File
# Begin Source File

SOURCE=.\src\termio\dz1_termio_win32crt.c
# End Source File
# Begin Source File

SOURCE=.\src\termio\dz1_termio_win32crt.h
# End Source File
# Begin Source File

SOURCE=.\src\termio\dz1_termio_xterm.c
# End Source File
# Begin Source File

SOURCE=.\src\termio\dz1_termio_xterm.h
# End Source File
# End Group
# Begin Group "util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\util\dz1_arg.c
# End Source File
# Begin Source File

SOURCE=.\src\util\dz1_fifo_reentrant.c
# End Source File
# End Group
# Begin Group "inet"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\inet\dz1_appstack.c
# End Source File
# Begin Source File

SOURCE=.\src\inet\dz1_sock_addr.c
# End Source File
# Begin Source File

SOURCE=.\src\inet\dz1_socket.c
# End Source File
# Begin Source File

SOURCE=.\src\inet\dz1_socket_acceptor.c
# End Source File
# Begin Source File

SOURCE=.\src\inet\dz1_socket_connector.c
# End Source File
# Begin Source File

SOURCE=.\src\inet\dz1_socket_receiver.c
# End Source File
# End Group
# Begin Group "parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\parser\dz1_parser.c
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser.h
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_emiter.c
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_emiter.h
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_init.c
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_lexer.c
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_lexer.h
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_match.c
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_match.h
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_syntax.c
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_syntax.h
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_token.c
# End Source File
# Begin Source File

SOURCE=.\src\parser\dz1_parser_token.h
# End Source File
# End Group
# Begin Group "shell"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\shell\dz1_shell.c
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell.h
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_args.c
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_args.h
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_builtin_cmds.c
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_builtin_cmds.h
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_cmd.c
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_cmd.h
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_history.c
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_history.h
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_input.c
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_input.h
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_parse.c
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_parse.h
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_var.c
# End Source File
# Begin Source File

SOURCE=.\src\shell\dz1_shell_var.h
# End Source File
# End Group
# Begin Group "fsm"

# PROP Default_Filter "C source file (*.c)|*.c"
# Begin Source File

SOURCE=.\src\fsm\dz1_fsm.c
# End Source File
# End Group
# Begin Group "asn1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\asn1\dz1_asn1_codec.c
# End Source File
# Begin Source File

SOURCE=.\src\asn1\dz1_asn1_octet_str.c
# End Source File
# Begin Source File

SOURCE=.\src\asn1\dz1_asn1_oid.c
# End Source File
# Begin Source File

SOURCE=.\src\asn1\dz1_asn1_utf8_str.c
# End Source File
# End Group
# Begin Group "fsm No. 1"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\dz1.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_aatree.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_appstack.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_args.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_asn1.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_bits.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_cleanup.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_error.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_fifo.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_fifo_reentrant.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_fsm.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_int.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_malloc.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_mutex.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_parser.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_parser_init.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_parser_token.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_serial.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_shell.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_sock_addr.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_socket.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_socket_acceptor.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_socket_connector.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_socket_receiver.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_stdio.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_str.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_sync.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_task.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_task_sigmsg_router.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_task_timer.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_termio.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_thread.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_thread_log.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_thread_stack.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_thread_status.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_thread_stdio.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_time.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_timeval.h
# End Source File
# Begin Source File

SOURCE=.\include\dz1_usleep.h
# End Source File
# End Group
# End Target
# End Project
