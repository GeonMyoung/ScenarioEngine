# Microsoft Developer Studio Project File - Name="Iso14827dz1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Iso14827dz1 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Iso14827dz1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Iso14827dz1.mak" CFG="Iso14827dz1 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Iso14827dz1 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Iso14827dz1 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Iso14827dz1 - Win32 Release"

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

!ELSEIF  "$(CFG)" == "Iso14827dz1 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Iso14827dz1___Win32_Debug"
# PROP BASE Intermediate_Dir "Iso14827dz1___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "../Iso14827NewAsn" /I "../ASN.1.GITSN/SupportLib" /I "../dimz/dz1/include" /I "../pthreads.2" /D "__CLEANUP_C" /D __WORDSIZE=32 /D "__SYSTEM_ENDIAN_LITTLE__" /D "GITSN_NEW_ASN_TOOL" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "Iso14827dz1 - Win32 Release"
# Name "Iso14827dz1 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\Iso14827asn_assist.c
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827asn_assist.h
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1.c
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1.tdc

!IF  "$(CFG)" == "Iso14827dz1 - Win32 Release"

!ELSEIF  "$(CFG)" == "Iso14827dz1 - Win32 Debug"

# Begin Custom Build
InputPath=.\src\Iso14827dz1.tdc
InputName=Iso14827dz1

BuildCmds= \
	..\dimz\dz1\src\mdefc\Debug\tdc -I src -I ..\dimz\dz1\include -h include -s src src\$(InputName).tdc

"src\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"include\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1_assist.c
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1_codec.h
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1_codecGeneralAsn.c
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1_codecNewAsn.c
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1_conv.h
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1_convGeneralAsn.c
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1_convNewAsn.c
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1_hdrForm.c
# End Source File
# Begin Source File

SOURCE=.\src\Iso14827dz1_hdrForm.tdc

!IF  "$(CFG)" == "Iso14827dz1 - Win32 Release"

!ELSEIF  "$(CFG)" == "Iso14827dz1 - Win32 Debug"

# Begin Custom Build
InputPath=.\src\Iso14827dz1_hdrForm.tdc
InputName=Iso14827dz1_hdrForm

BuildCmds= \
	..\dimz\dz1\src\mdefc\Debug\tdc -I src -I ..\dimz\dz1\include -h include -s .\src src\$(InputName).tdc

"src\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"include\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Iso14827NewAsn_assist.h
# End Source File
# Begin Source File

SOURCE=.\src\Iso3309CRC.c
# End Source File
# Begin Source File

SOURCE=.\src\Iso3309CRC.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\Iso14827dz1.h
# End Source File
# Begin Source File

SOURCE=.\include\Iso14827dz1_assist.h
# End Source File
# Begin Source File

SOURCE=.\include\Iso14827dz1_hdrForm.h
# End Source File
# Begin Source File

SOURCE=.\include\libdz1_support.h
# End Source File
# End Group
# End Target
# End Project
