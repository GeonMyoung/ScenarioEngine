# Microsoft Developer Studio Project File - Name="libtool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libtool - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libtool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libtool.mak" CFG="libtool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libtool - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libtool - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ASN/PER/CODE/PER/Prj/libtool", ZOLAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libtool - Win32 Release"

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
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libtool - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\SupportLib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\LIB\libtool.lib"

!ENDIF 

# Begin Target

# Name "libtool - Win32 Release"
# Name "libtool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_BITSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_BMPString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_BOOLEAN.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_CHARACTERSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_ENUMERATED.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_GeneralizedTime.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_GeneralString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_GraphicString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_IA5String.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_INTEGER.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_NULL.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_NumericString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_OBJECTIDENTIFIER.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_OCTETSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_OpenType.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_PrintableString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_STRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_TeletexString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_UniversalString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_UTCTime.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_UTF8String.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_VideotexString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_VisibleString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Length.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_List.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Operate_Byte.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Print.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Set.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Tag.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Tool_BitString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Tool_String.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Tool_Time.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\Infinite_tool.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_BITSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_BMPString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_BOOLEAN.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_CHARACTERSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_ENUMERATED.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_GeneralizedTime.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_GeneralString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_GraphicString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_IA5String.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_INTEGER.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_NULL.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_NumericString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_OBJECTIDENTIFIER.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_OCTETSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_OpenType.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_PrintableString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_STRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_TeletexString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_UniversalString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_UTCTime.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_UTF8String.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_VideotexString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_VisibleString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Length.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_List.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Operate_Byte.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Print.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Set.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Tag.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Tool_BitString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Tool_String.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_Tool_Time.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1Tool.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\Infinite_tool.h
# End Source File
# End Group
# Begin Group "TYPE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\TYPE\ASN1_Type.h
# End Source File
# End Group
# Begin Group "OS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\OS\ASN1_Sys.h
# End Source File
# End Group
# End Target
# End Project
