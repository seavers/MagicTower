#if !defined(AFX_INFOEDIT_H__03FB8814_0352_4F5D_9275_FD4870072C20__INCLUDED_)
#define AFX_INFOEDIT_H__03FB8814_0352_4F5D_9275_FD4870072C20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoEdit window

class CInfoEdit : public CEdit
{
// Construction
public:
	CInfoEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT GetID();
	CInfoEdit(UINT nID);
	virtual ~CInfoEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInfoEdit)
	afx_msg void OnChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	UINT m_nID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOEDIT_H__03FB8814_0352_4F5D_9275_FD4870072C20__INCLUDED_)
