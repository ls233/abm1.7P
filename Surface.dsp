# Microsoft Developer Studio Project File - Name="Surface" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Surface - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Surface.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Surface.mak" CFG="Surface - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Surface - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Surface - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Surface - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Surface - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libeng.lib libmx.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"c:\Program Files\MATLAB\R2008a\extern\lib\win32\microsoft\\"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Surface - Win32 Release"
# Name "Surface - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BaseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cell.cpp
# End Source File
# Begin Source File

SOURCE=.\futil.cpp
# End Source File
# Begin Source File

SOURCE=.\General.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid.cpp
# End Source File
# Begin Source File

SOURCE=.\GridUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\image.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MatlabEng.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTabCtr.cpp
# End Source File
# Begin Source File

SOURCE=.\Option.cpp
# End Source File
# Begin Source File

SOURCE=.\Orders.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\Receptor.cpp
# End Source File
# Begin Source File

SOURCE=.\Result.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\RProfile.cpp
# End Source File
# Begin Source File

SOURCE=.\SigMol.cpp
# End Source File
# Begin Source File

SOURCE=.\SMprofile.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Surface.cpp
# End Source File
# Begin Source File

SOURCE=.\Surface.rc
# End Source File
# Begin Source File

SOURCE=.\SurfaceDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SurfaceView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BaseDlg.h
# End Source File
# Begin Source File

SOURCE=.\Cell.h
# End Source File
# Begin Source File

SOURCE=.\futil.h
# End Source File
# Begin Source File

SOURCE=.\General.h
# End Source File
# Begin Source File

SOURCE=.\Grid.h
# End Source File
# Begin Source File

SOURCE=.\GridUnit.h
# End Source File
# Begin Source File

SOURCE=.\image.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MatlabEng.h
# End Source File
# Begin Source File

SOURCE=.\MyTabCtr.h
# End Source File
# Begin Source File

SOURCE=.\Option.h
# End Source File
# Begin Source File

SOURCE=.\Orders.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Receptor.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Result.h
# End Source File
# Begin Source File

SOURCE=.\ResultsTemplate.h
# End Source File
# Begin Source File

SOURCE=.\RProfile.h
# End Source File
# Begin Source File

SOURCE=.\SigMol.h
# End Source File
# Begin Source File

SOURCE=.\SMprofile.h
# End Source File
# Begin Source File

SOURCE=.\soiltex.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Surface.h
# End Source File
# Begin Source File

SOURCE=.\SurfaceDoc.h
# End Source File
# Begin Source File

SOURCE=.\SurfaceView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\backbone.ico
# End Source File
# Begin Source File

SOURCE=.\res\blackSquare.ico
# End Source File
# Begin Source File

SOURCE=.\res\cianCircle.ico
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\greenSquare.ico
# End Source File
# Begin Source File

SOURCE=.\res\greySquare.ico
# End Source File
# Begin Source File

SOURCE=.\res\Hapten.ico
# End Source File
# Begin Source File

SOURCE=.\res\purpleCircle.ico
# End Source File
# Begin Source File

SOURCE=.\res\raft.ico
# End Source File
# Begin Source File

SOURCE=.\res\redCircle.ico
# End Source File
# Begin Source File

SOURCE=.\res\redCircle1.ico
# End Source File
# Begin Source File

SOURCE=.\res\redCircle2.ico
# End Source File
# Begin Source File

SOURCE=.\res\roseSquare.ico
# End Source File
# Begin Source File

SOURCE=.\res\Surface.ico
# End Source File
# Begin Source File

SOURCE=.\res\Surface.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SurfaceDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\whiteCircle.ico
# End Source File
# Begin Source File

SOURCE=.\res\yellowCircle.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Surface : {4C599243-6926-101B-9992-00000B65C6F9}
# 	2:5:Class:CImage
# 	2:10:HeaderFile:image.h
# 	2:8:ImplFile:image.cpp
# End Section
# Section Surface : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section Surface : {4C599241-6926-101B-9992-00000B65C6F9}
# 	2:21:DefaultSinkHeaderFile:image.h
# 	2:16:DefaultSinkClass:CImage
# End Section
