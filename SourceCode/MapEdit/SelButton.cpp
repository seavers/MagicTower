// SelButton.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "SelButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////
int CSelButton::nSelect = 0;
/////////////////////////////////////////////////////////////////////////////
// CSelButton

CSelButton::CSelButton()
{

}

CSelButton::~CSelButton()
{

}

BEGIN_MESSAGE_MAP(CSelButton, CButton)
	//{{AFX_MSG_MAP(CSelButton)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelButton message handlers

void CSelButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	nSelect = m_nID;
	this->GetParent()->Invalidate(FALSE);
	CButton::OnLButtonDown(nFlags, point);
}

CSelButton::CSelButton(UINT nID)
{
	m_nID = nID;
}
