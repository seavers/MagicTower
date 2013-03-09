// MapEditDlg.h : header file
//

#if !defined(AFX_MAPEDITDLG_H__C83D32CB_F72D_47A7_91BA_688021DEE8E5__INCLUDED_)
#define AFX_MAPEDITDLG_H__C83D32CB_F72D_47A7_91BA_688021DEE8E5__INCLUDED_

#include "SelButton.h"
#include "InfoEdit.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PIC_TOTEL		174
//#define PIC_WIDTH		32
//#define PIC_HEIGHT	32

#define MAP_LAYER		24
#define MAP_WIDTH		11
#define MAP_HEIGHT		11

struct NPCINFO
{
	int nLevel;
	int nHealth;
	int nAttack;
	int nDefense;
	int nMoney;
	int Experi;
	int RedKey;
	int BlueKey;
	int YelKey;	
};

#define MAX_EDIT		(sizeof(NPCINFO) / sizeof(int))

/////////////////////////////////////////////////////////////////////////////
// CMapEditDlg dialog

class CMapEditDlg : public CDialog
{
// Construction
public:
	CMapEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMapEditDlg)
	enum { IDD = IDD_MAPEDIT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMapEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ReadImageFile();
	void WriteImageFile();
	void ReadMapFile();
	void WriteMapFile();
	void WriteNpcFile();
	void ReadNpcFile();
	BYTE ImageBuf[PIC_TOTEL][32][32][3];
	BYTE MapBuf[MAP_LAYER][MAP_WIDTH][MAP_HEIGHT];
	NPCINFO NpcBuf[PIC_TOTEL];

	CScrollBar LeftScrollBar;
	CSelButton *pButton[MAP_LAYER];
	CInfoEdit *pEdit[MAX_EDIT];
	CRect LeftRect;
	CRect LeftScrollRect;
	CRect MiddleRect;
	CRect RightRect;
	CRect NpcRect;
	CRect NpcBorderRect;
	CRect MapRect;
	CRect MapBorderRect;
	CRect SelectRect;

	int nSelectIndex;
	int nCurLayer;
	int LeftBegin;
	int nLeftPicWidth;
	int nLeftPicHeight;

	bool bLBtnDown;
	bool bRBtnDown;
	bool bLeftRefresh;
	bool bRightRefresh;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPEDITDLG_H__C83D32CB_F72D_47A7_91BA_688021DEE8E5__INCLUDED_)
