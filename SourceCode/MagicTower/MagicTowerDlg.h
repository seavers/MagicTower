// MagicTowerDlg.h : header file
//

#if !defined(AFX_MAGICTOWERDLG_H__93D3E7C4_0B85_4D96_BCAD_B01C26F738C2__INCLUDED_)
#define AFX_MAGICTOWERDLG_H__93D3E7C4_0B85_4D96_BCAD_B01C26F738C2__INCLUDED_

#include "Game.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMagicTowerDlg dialog

class CMagicTowerDlg : public CDialog
{
// Construction
public:
	CMagicTowerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMagicTowerDlg)
	enum { IDD = IDD_MAGICTOWER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicTowerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMagicTowerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//Game
private:
	CGame *pGame;

//Others
	void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAGICTOWERDLG_H__93D3E7C4_0B85_4D96_BCAD_B01C26F738C2__INCLUDED_)
