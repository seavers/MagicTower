// MagicTower.h : main header file for the MAGICTOWER application
//

#if !defined(AFX_MAGICTOWER_H__0737C280_DFEF_49B1_B1A2_42AC9D1C478E__INCLUDED_)
#define AFX_MAGICTOWER_H__0737C280_DFEF_49B1_B1A2_42AC9D1C478E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMagicTowerApp:
// See MagicTower.cpp for the implementation of this class
//

class CMagicTowerApp : public CWinApp
{
public:
	CMagicTowerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicTowerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMagicTowerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAGICTOWER_H__0737C280_DFEF_49B1_B1A2_42AC9D1C478E__INCLUDED_)
