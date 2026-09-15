# Microsoft Developer Studio Project File - Name="libber" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libber - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libber.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libber.mak" CFG="libber - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libber - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libber - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ASN/BER_PER/SupportLib/libber", GRAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libber - Win32 Release"

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

!ELSEIF  "$(CFG)" == "libber - Win32 Debug"

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
# ADD LIB32 /nologo /out:"..\LIB\libber.lib"

!ENDIF 

# Begin Target

# Name "libber - Win32 Release"
# Name "libber - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE="..\SupportLib\BER\ASN1_BER_RELATIVE-OID.c"
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
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
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

SOURCE="..\SupportLib\BER\ASN1_BER_RELATIVE-OID.h"
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
# End Target
# End Project
