# Microsoft Developer Studio Project File - Name="libxer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libxer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libxer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libxer.mak" CFG="libxer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libxer - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxer - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ZAT/ASN/XER/SupportLib/libxer", KWBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libxer - Win32 Release"

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

!ELSEIF  "$(CFG)" == "libxer - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\LIB\libxer.lib"

!ENDIF 

# Begin Target

# Name "libxer - Win32 Release"
# Name "libxer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE="..\SupportLib\XER\ASN1_XER_RELATIVE-OID.c"
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
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
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

SOURCE="..\SupportLib\XER\ASN1_XER_RELATIVE-OID.h"
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
# End Target
# End Project
