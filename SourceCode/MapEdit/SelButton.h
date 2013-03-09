#if !defined(AFX_SELBUTTON_H__4B2AAEFD_3A15_4649_B814_386D59565372__INCLUDED_)
#define AFX_SELBUTTON_H__4B2AAEFD_3A15_4649_B814_386D59565372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelButton window

class CSelButton : public CButton
{
private:
	int m_nID;
public:
	static int nSelect;
// Construction
public:
	CSelButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	CSelButton(UINT nID);
	virtual ~CSelButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSelButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELBUTTON_H__4B2AAEFD_3A15_4649_B814_386D59565372__INCLUDED_)
