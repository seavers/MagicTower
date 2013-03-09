; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInfoEdit
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MapEdit.h"

ClassCount=4
Class1=CMapEditApp
Class2=CMapEditDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CSelButton
Class4=CInfoEdit
Resource2=IDD_MAPEDIT_DIALOG

[CLS:CMapEditApp]
Type=0
HeaderFile=MapEdit.h
ImplementationFile=MapEdit.cpp
Filter=N

[CLS:CMapEditDlg]
Type=0
HeaderFile=MapEditDlg.h
ImplementationFile=MapEditDlg.cpp
Filter=D
LastObject=CMapEditDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_MAPEDIT_DIALOG]
Type=1
Class=CMapEditDlg
ControlCount=0

[CLS:CSelButton]
Type=0
HeaderFile=SelButton.h
ImplementationFile=SelButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CSelButton

[CLS:CInfoEdit]
Type=0
HeaderFile=InfoEdit.h
ImplementationFile=InfoEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC
LastObject=CInfoEdit

