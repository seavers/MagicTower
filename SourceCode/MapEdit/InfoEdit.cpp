// InfoEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "InfoEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoEdit

CInfoEdit::CInfoEdit()
{
}

CInfoEdit::~CInfoEdit()
{
}


BEGIN_MESSAGE_MAP(CInfoEdit, CEdit)
	//{{AFX_MSG_MAP(CInfoEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoEdit message handlers

CInfoEdit::CInfoEdit(UINT nID)
{
	m_nID = nID;	
}

void CInfoEdit::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	::AfxGetMainWnd()->SendMessage(WM_COMMAND, (WPARAM)EN_CHANGE, (LPARAM)this->m_hWnd);
}

UINT CInfoEdit::GetID()
{
	return m_nID;
}
