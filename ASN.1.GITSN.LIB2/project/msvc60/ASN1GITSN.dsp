# Microsoft Developer Studio Project File - Name="ASN1GITSN" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ASN1GITSN - Win32 DebugMT
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ASN1GITSN.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ASN1GITSN.mak" CFG="ASN1GITSN - Win32 DebugMT"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ASN1GITSN - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ASN1GITSN - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ASN1GITSN - Win32 ReleaseMT" (based on "Win32 (x86) Static Library")
!MESSAGE "ASN1GITSN - Win32 DebugMT" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ASN1GITSN - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../SupportLib" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\SupportLib\LIB\Release\ASN1GITSNmtdll.lib"

!ELSEIF  "$(CFG)" == "ASN1GITSN - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../SupportLib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\SupportLib\LIB\Debug\ASN1GITSNmtdll.lib"

!ELSEIF  "$(CFG)" == "ASN1GITSN - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ASN1GITSN___Win32_ReleaseMT"
# PROP BASE Intermediate_Dir "ASN1GITSN___Win32_ReleaseMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ASN1GITSN___Win32_ReleaseMT"
# PROP Intermediate_Dir "ASN1GITSN___Win32_ReleaseMT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../SupportLib" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../SupportLib" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\SupportLib\LIB\Release\ASN1GITSNmtdll.lib"
# ADD LIB32 /nologo /out:"..\SupportLib\LIB\Release\ASN1GITSNmt.lib"

!ELSEIF  "$(CFG)" == "ASN1GITSN - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ASN1GITSN___Win32_DebugMT"
# PROP BASE Intermediate_Dir "ASN1GITSN___Win32_DebugMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ASN1GITSN___Win32_DebugMT"
# PROP Intermediate_Dir "ASN1GITSN___Win32_DebugMT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../SupportLib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../SupportLib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\SupportLib\LIB\Debug\ASN1GITSNmtdll.lib"
# ADD LIB32 /nologo /out:"..\SupportLib\LIB\Debug\ASN1GITSNmt.lib"

!ENDIF 

# Begin Target

# Name "ASN1GITSN - Win32 Release"
# Name "ASN1GITSN - Win32 Debug"
# Name "ASN1GITSN - Win32 ReleaseMT"
# Name "ASN1GITSN - Win32 DebugMT"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "BER"

# PROP Default_Filter "C Source File (*.c)"
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_BITSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_BMPString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_BOOLEAN.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_CHARACTERSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_ENUMERATED.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_GeneralizedTime.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_GeneralString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_GraphicString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_IA5String.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_INTEGER.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_NULL.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_NumericString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_ObjectDescriptor.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_OBJECTIDENTIFIER.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_OCTETSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_OpenType.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_PrintableString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_REAL.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_RELATIVE_OID.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_STRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_TeletexString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_UniversalString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_UTCTime.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_UTF8String.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_VideotexString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_VisibleString.c
# End Source File
# End Group
# Begin Group "PER"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_BITSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_BMPString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_BOOLEAN.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_CHARACTERSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_ENUMERATED.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_GeneralizedTime.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_GeneralString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_GraphicString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_IA5String.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_INTEGER.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_NumericString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_ObjectDescriptor.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_OBJECTIDENTIFIER.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_OCTETSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_OpenType.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_PrintableString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_REAL.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_RELATIVE_OID.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_SET.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_STRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_TeletexString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_UniversalString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_UTCTime.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_UTF8String.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_VideotexString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_VisibleString.c
# End Source File
# End Group
# Begin Group "IO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\IO\ASN1_WorkSpace.c
# End Source File
# End Group
# Begin Group "MEM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\MEM\ASN1_mpool.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\MEM\ASN1_xmalloc.c
# End Source File
# End Group
# Begin Group "TOOL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_BER_Check_Length.c
# End Source File
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

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_ObjectDescriptor.c
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

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_REAL.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_RELATIVE_OID.c
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

SOURCE=..\SupportLib\TOOL\ASN1_XER_Check_Length.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\Infinite_tool.c
# End Source File
# End Group
# Begin Group "XER"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_BITSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_BMPString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_BOOLEAN.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_CHARACTERSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_ENUMERATED.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_GeneralizedTime.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_GeneralString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_GraphicString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_IA5String.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_INTEGER.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_Name.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_NULL.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_NumericString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_ObjectDescriptor.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_OBJECTIDENTIFIER.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_OCTETSTRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_OpenType.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_PrintableString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_REAL.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_RELATIVE_OID.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_SET.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_STRING.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_TeletexString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_UniversalString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_UTCTime.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_UTF8String.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_VideotexString.c
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_VisibleString.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "BER Header"

# PROP Default_Filter "C Header File (*.h)"
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_BITSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_BMPString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_BOOLEAN.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_CHARACTERSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_ENUMERATED.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_GeneralizedTime.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_GeneralString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_GraphicString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_IA5String.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_INTEGER.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_NULL.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_NumericString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_ObjectDescriptor.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_OBJECTIDENTIFIER.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_OCTETSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_OpenType.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_PrintableString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_REAL.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_RELATIVE_OID.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_STRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_TeletexString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_UniversalString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_UTCTime.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_UTF8String.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_VideotexString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1_BER_VisibleString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\BER\ASN1bersrc.h
# End Source File
# End Group
# Begin Group "PER Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_BITSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_BMPString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_BOOLEAN.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_CHARACTERSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_ENUMERATED.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_GeneralizedTime.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_GeneralString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_GraphicString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_IA5String.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_INTEGER.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_NumericString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_ObjectDescriptor.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_OBJECTIDENTIFIER.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_OCTETSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_OpenType.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_PrintableString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_REAL.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_RELATIVE_OID.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_SET.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_STRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_TeletexString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_UniversalString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_UTCTime.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_UTF8String.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_VideotexString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1_PER_VisibleString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\PER\ASN1persrc.h
# End Source File
# End Group
# Begin Group "IO Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\IO\ASN1_WorkSpace.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\IO\ASN1IO.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\IO\ASNIO.h
# End Source File
# End Group
# Begin Group "MEM Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\MEM\ASN1_mpool.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\MEM\ASN1_xmalloc.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\MEM\mpool.h
# End Source File
# End Group
# Begin Group "OS Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\OS\ASN1_Sys.h
# End Source File
# End Group
# Begin Group "TOOL Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_BER_Check_Length.h
# End Source File
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

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_ObjectDescriptor.h
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

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_REAL.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1_CHECK_RELATIVE_OID.h
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

SOURCE=..\SupportLib\TOOL\ASN1_XER_Check_Length.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\ASN1Tool.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\TOOL\Infinite_tool.h
# End Source File
# End Group
# Begin Group "TYPE Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\TYPE\ASN1_Type.h
# End Source File
# End Group
# Begin Group "XER Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_BITSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_BMPString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_BOOLEAN.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_CHARACTERSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_ENUMERATED.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_GeneralizedTime.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_GeneralString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_GraphicString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_IA5String.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_INTEGER.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_Name.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_NULL.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_NumericString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_ObjectDescriptor.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_OBJECTIDENTIFIER.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_OCTETSTRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_OpenType.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_PrintableString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_REAL.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_RELATIVE_OID.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_SET.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_STRING.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_TeletexString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_UniversalString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_UTCTime.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_UTF8String.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_VideotexString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1_XER_VisibleString.h
# End Source File
# Begin Source File

SOURCE=..\SupportLib\XER\ASN1xersrc.h
# End Source File
# End Group
# End Group
# End Target
# End Project
