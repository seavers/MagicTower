// MapEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "MapEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
#define TILE_FILE_NAME		"..\\Tile.txt"
#define MAP_FILE_NAME		"..\\Map.txt"
#define NPC_FILE_NAME		"..\\Npc.txt"
#else
#define TILE_FILE_NAME		"Tile.txt"
#define MAP_FILE_NAME		"Map.txt"
#define NPC_FILE_NAME		"Npc.txt"
#endif

#define IDC_LEFTSCROLLBAR		1820
#define IDC_MYBUTTON			1821
#define IDC_MYEDIT				2000
/////////////////////////////////////////////////////////////////////////////
// CMapEditDlg dialog

CMapEditDlg::CMapEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMapEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMapEditDlg, CDialog)
	//{{AFX_MSG_MAP(CMapEditDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMapEditDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditDlg message handlers

BOOL CMapEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	this->SetWindowPos(NULL, 0, 0, 800, 600, SWP_NOZORDER);
//	WriteImageFile();
	ReadImageFile();
	ReadMapFile();
//	WriteNpcFile();			//清0
	ReadNpcFile();

//	memset(&MapBuf[0][0][0], 68, sizeof(MapBuf));
	nCurLayer = 0;
	LeftBegin = 0;
	nLeftPicWidth = 7;
	nLeftPicHeight = 15;
	bLeftRefresh = true;
	bRightRefresh = true;
	bLBtnDown = false;
	bRBtnDown = false;

	//选择相关
	nSelectIndex = 67;
	SelectRect.SetRect(133, 293, 165, 325);

	//布局RECT
	LeftRect      .SetRect(5, 5, 229, 485);       //229 = 5 + 7 * 32;  485 = 5 + 15 * 32;
	LeftScrollRect.SetRect(230, 5, 240, 550);
	MiddleRect    .SetRect(270, 5, 280, 550);
	RightRect     .SetRect(300, 5, 650, 550);
	NpcRect       .SetRect(340, 180, 360, 550);
	NpcBorderRect = NpcRect + CRect(10, 10, 10, 10);
	MapRect       .SetRect(400, 180, 400 + MAP_WIDTH * 32, 180 + MAP_HEIGHT * 32);
	MapBorderRect = MapRect + CRect(10, 10, 10, 10);

	//上面的选择按钮
	int i;
	for(i = 0; i < MAP_LAYER; i++)
	{
		CString String;
		String.Format("%2d", i);
		CRect Rect(CPoint(RightRect.left + i % 6 * 80, RightRect.top + 10 + i / 6 * 30), CSize(60, 20));
		pButton[i] = new CSelButton(i);
		pButton[i]->Create(String, BS_PUSHBUTTON, Rect, this, IDC_MYBUTTON + i);
		pButton[i]->ShowWindow(SW_NORMAL);
	}

	//中间的一竖排EDIT
	for(i = 0; i < MAX_EDIT; i++)
	{
		CString String;
		String.Format("%d", *((int *)&NpcBuf[nSelectIndex] + i));
		CRect Rect(CPoint(NpcRect.left, NpcRect.top + i * NpcRect.Height() / MAX_EDIT), CSize(40, 20));
		pEdit[i] = new CInfoEdit(i);
		pEdit[i]->Create(ES_RIGHT | WS_BORDER, Rect, this, IDC_MYEDIT + i);
		pEdit[i]->SetWindowText(String);
		pEdit[i]->ShowWindow(SW_NORMAL);
	}

	//左边滚动条
	if(!GetDlgItem(IDC_LEFTSCROLLBAR))
	{
		DWORD dwStyle = WS_VISIBLE | WS_CHILD | SBS_VERT | SBS_TOPALIGN;
		LeftScrollBar.Create(dwStyle, LeftScrollRect, this, IDC_LEFTSCROLLBAR);
		SCROLLINFO sci;
		sci.cbSize = sizeof(SCROLLINFO);
		sci.fMask = SIF_ALL;
		sci.nMin = 0;
		sci.nMax = 15;
		sci.nPage = 4;
		sci.nPos = 0;
		sci.nTrackPos = 0;
		LeftScrollBar.SetScrollInfo(&sci, FALSE);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMapEditDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC mdc(this);

		//Get nLayer
		nCurLayer = CSelButton::nSelect;

		//Create BitmapInfo				
		BITMAPINFO bmif;
		memset(&bmif, 0, sizeof(bmif));
		bmif.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmif.bmiHeader.biBitCount = 24;
		bmif.bmiHeader.biWidth = 32;
		bmif.bmiHeader.biHeight = 32;
		bmif.bmiHeader.biPlanes = 1;


		//创建缓冲
		CDC dc;
		dc.CreateCompatibleDC(&mdc);
		CBitmap Bitmap;
		Bitmap.CreateCompatibleBitmap(&mdc, 800, 600);
		dc.SelectObject(&Bitmap);
		CBrush BgBrush(RGB(139, 135, 122));
		dc.SelectObject(&BgBrush);
		dc.Rectangle(0, 0, 800, 600);
		/*
		char szWidth[100];
		char szHeight[100];
		itoa(nWidth, szWidth, 10);
		itoa(nHeight, szHeight, 10);
		dc.TextOut(100, 100, szWidth, strlen(szWidth));
		dc.TextOut(100, 200, szHeight, strlen(szHeight));
		*/
		

		//Left Outer Rect
		//CRect LeftRect(5, 5, MiddlePoint.x - 5, 550);
		//CBrush Brush(RGB(0, 0, 0));
		//dc.FrameRect(&LeftRect, &Brush);
			
		int i, j;
		//Left Image
		if(bLeftRefresh)
		{
			CBrush ImageBrush(RGB(255, 255, 255));
			for(i = 0; i < nLeftPicHeight; i++)
			{
				for(j = 0; j < nLeftPicWidth; j++)
				{
					int nIndex = (i + LeftBegin) * nLeftPicWidth + j;
					if(nIndex < PIC_TOTEL)
					{
						::SetDIBitsToDevice(dc.m_hDC, LeftRect.left + j * 32, LeftRect.top + i * 32, 32, 32, 0, 0, 0, 32, ImageBuf[nIndex], &bmif, DIB_RGB_COLORS);
						/*
						int h, w;
						for(h = 0; h < 32; h++)
						{
							for(w = 0; w < 32; w++)
							{
								COLORREF Color = RGB(ImageBuf[nIndex][31-h-1][w][2], ImageBuf[nIndex][31-h-1][w][1], ImageBuf[nIndex][31-h-1][w][0]);
								dc.SetPixel(LeftRect.left + j * 32 + w , LeftRect.top + i * 32 + h, Color);
							}
						}
						*/						
					}
					CRect Rect(LeftRect.left + j * 32, LeftRect.top + i * 32, LeftRect.left + j * 32 + 32, LeftRect.top + i * 32 + 32);
					dc.FrameRect(&Rect, &ImageBrush);
				}
			}
		}

		//left SelectRect
		if(LeftRect.PtInRect(SelectRect.CenterPoint()))
		{
			CBrush SelectBrush(RGB(0, 0, 255));
			dc.FrameRect(&SelectRect, &SelectBrush);
		}

		
		//Npc Rect
		char NpcInfo[MAX_EDIT][16] = {"Level", "HP", "Att", "Def", "Money", "Exp", "RedKey", "BlueKey", "YelKey"};
		for(i = 0; i < MAX_EDIT; i++)
		{
			sprintf(NpcInfo[i], "%s%s", NpcInfo[i], " : + ");
			dc.SetTextColor(RGB(0, 50, 200));
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextAlign(TA_RIGHT);
			dc.TextOut(NpcRect.left, NpcRect.top + i * NpcRect.Height() / MAX_EDIT, NpcInfo[i]);
		}

		// middle Line
		//dc.MoveTo(MiddleRect.left, MiddleRect.top);
		//CPen Pen(PS_SOLID, MiddleRect.Width(), RGB(0, 0, 128));
		//dc.SelectObject(&Pen);
		//dc.LineTo(MiddleRect.left, MiddleRect.bottom);
			
		//right rect		
		CBrush RightBrush(RGB(255, 255, 255));
		dc.SelectObject(RightBrush);
		dc.Rectangle(&MapBorderRect);

		
		//Map rect
		CBrush MapBrush(RGB(0, 0, 0));
		CRect MapOutRect(MapRect.left, MapRect.top, MapRect.left + MAP_WIDTH * 32, MapRect.top + MAP_HEIGHT * 32);
		MapOutRect.InflateRect(2, 2);
		dc.Rectangle(&MapOutRect);
		MapOutRect.DeflateRect(1, 1);
		dc.Rectangle(&MapOutRect);

		
		//right Select

		//right Map
		if(bRightRefresh)
		{
			for(i = 0; i < MAP_HEIGHT; i++)
			{
				for(j = 0; j < MAP_WIDTH; j++)
				{
					
					int nIndex = MapBuf[nCurLayer][j][i];
					::SetDIBitsToDevice(dc.m_hDC, MapRect.left + j * 32, MapRect.top + i * 32, 32, 32, 0, 0, 0, 32, ImageBuf[nIndex], &bmif, DIB_RGB_COLORS);
					/*
					int h, w;
					for(h = 0; h < 32; h++)
					{
						for(w = 0; w < 32; w++)
						{
							COLORREF Color = RGB(ImageBuf[nIndex][31-h-1][w][2], ImageBuf[nIndex][31-h-1][w][1], ImageBuf[nIndex][31-h-1][w][0]);
							dc.SetPixel(MapRect.left + j * 32 + w, MapRect.top + i * 32 + h, Color);
						}
					}
					*/
				}
			}
		}

		//Show nLayer

		CString LayerInfo;
		LayerInfo.Format("第 %d 层", nCurLayer);
		dc.SetTextColor(RGB(50, 0, 255));
		dc.SetBkMode(TRANSPARENT);
		dc.TextOut(MapBorderRect.CenterPoint().x + 30, MapBorderRect.top - 30, LayerInfo);

		//all
		mdc.BitBlt(0, 0, 800, 600, &dc, 0, 0, SRCCOPY);
		bLeftRefresh = true;
		bRightRefresh = true;
		CDialog::OnPaint();
	}
}


void CMapEditDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	WriteMapFile();
	WriteNpcFile();
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CMapEditDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(pScrollBar == &LeftScrollBar)
	{
		SCROLLINFO sci;
		LeftScrollBar.GetScrollInfo(&sci);
		int nPrevPos = sci.nPos;
		switch(nSBCode)
		{
			case SB_LINEUP:
				sci.nPos--;
				break;
			case SB_LINEDOWN:
				sci.nPos++;
				break;
			case SB_PAGEUP:
				sci.nPos -= sci.nPage;				
				break;
			case SB_PAGEDOWN:
				sci.nPos += sci.nPage;				
				break;
			case SB_THUMBPOSITION:
				sci.nPos = nPos;
				break;
			case SB_THUMBTRACK:
				sci.nPos = nPos;
				break;
			case SB_ENDSCROLL:
				break;
			case SB_TOP:
			case SB_BOTTOM:
			default:
				//this->MessageBox("err");
				break;
		}
		if(sci.nPos < sci.nMin)
		{
			sci.nPos = sci.nMin;
		}
		if(sci.nPos > sci.nMax)
		{
			sci.nPos = sci.nMax;
		}
		LeftBegin = sci.nPos;
		LeftScrollBar.SetScrollInfo(&sci, FALSE);

		SelectRect.OffsetRect(0, (nPrevPos - sci.nPos) * 32);
	}

	//updata
	bRightRefresh = false;
	InvalidateRect(&LeftRect, FALSE);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMapEditDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!bRBtnDown)
	{
		if(LeftRect.PtInRect(point))
		{
			int left = LeftRect.left + (point.x - LeftRect.left) / 32 * 32;
			int top = LeftRect.top + (point.y - LeftRect.top) / 32 * 32;		

			nSelectIndex = LeftBegin * nLeftPicWidth + (point.y - LeftRect.top) / 32 * nLeftPicWidth + (point.x - LeftRect.left) / 32;
			if(nSelectIndex < PIC_TOTEL)
			{
				SelectRect.SetRect(left, top, left + 32, top + 32);
			}
			else
			{
				nSelectIndex = 67;
			}
			int i;
			for(i = 0; i < MAX_EDIT; i++)
			{
				char szNum[10];
				itoa(*((int *)&NpcBuf[nSelectIndex] + i), szNum, 10);
				pEdit[i]->SetWindowText(szNum);
			}
			bRightRefresh = false;
			InvalidateRect(&LeftRect, FALSE);
		}
		else if(MapRect.PtInRect(point))
		{
			bLBtnDown = true;
			int CurX = (point.x - MapRect.left) / 32;
			int CurY = (point.y - MapRect.top) / 32;
			MapBuf[nCurLayer][CurX][CurY] = nSelectIndex;

			bLeftRefresh = false;
			InvalidateRect(&MapBorderRect, FALSE);		
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CMapEditDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	bLBtnDown = false;
	CDialog::OnLButtonUp(nFlags, point);
}

void CMapEditDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!bLBtnDown)
	{
		if(MapRect.PtInRect(point))
		{
			bRBtnDown = true;
			int CurX = (point.x - MapRect.left) / 32;
			int CurY = (point.y - MapRect.top) / 32;
			MapBuf[nCurLayer][CurX][CurY] = 68;

			bLeftRefresh = false;
			InvalidateRect(&MapBorderRect, FALSE);		
		}
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CMapEditDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	bRBtnDown = false;
	CDialog::OnRButtonUp(nFlags, point);
}

void CMapEditDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(bLBtnDown)
	{
		if(MapRect.PtInRect(point))
		{
			int CurX = (point.x - MapRect.left) / 32;
			int CurY = (point.y - MapRect.top) / 32;
			MapBuf[nCurLayer][CurX][CurY] = nSelectIndex;

			bLeftRefresh = false;
			InvalidateRect(&MapBorderRect, FALSE);		
		}
	}
	else if(bRBtnDown)
	{
		if(MapRect.PtInRect(point))
		{
			int CurX = (point.x - MapRect.left) / 32;
			int CurY = (point.y - MapRect.top) / 32;
			MapBuf[nCurLayer][CurX][CurY] = 68;

			bLeftRefresh = false;
			InvalidateRect(&MapBorderRect, FALSE);		
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CMapEditDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(wParam == EN_CHANGE)
	{
		CInfoEdit *InfoEdit = (CInfoEdit *)CWnd::FromHandle((HWND)lParam);
		char nNum[10];
		InfoEdit->GetWindowText(nNum, 10);
		int id = InfoEdit->GetID();
		*((int *)&NpcBuf[nSelectIndex] + id) = atoi(nNum);
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CMapEditDlg::WriteImageFile()
{
	BYTE Pal[256][4];
	BYTE Buffer[32][32];
	
	CFile File, ImageFile;
	ImageFile.Open(TILE_FILE_NAME, CFile::modeCreate | CFile::modeWrite);

	int i;
	for(i = 1; i <= PIC_TOTEL; i++)
	{
		CString FileName;
		FileName.Format("Image\\tile (%d).bmp", i);
		File.Open((LPCTSTR)FileName, CFile::modeRead);
		BITMAPFILEHEADER bmfh;
		BITMAPINFOHEADER bmih;
		File.Read(&bmfh, sizeof(bmfh));
		File.Read(&bmih, sizeof(bmih));
		int nWidth = bmih.biWidth;
		int nHeight = bmih.biHeight;
		//int nPos = bmfh.bfOffBits;
		int nBit = bmih.biBitCount;
		switch(nBit)
		{
		case 8:
			{
				File.Read(&Pal[0][0], 256*4);
				File.Read(&Buffer[0][0], nWidth * nHeight);
				int w,h;
				for(w = 0; w < nWidth; w++)
				{
					for(h = 0; h < nHeight; h++)
					{
						memcpy(ImageBuf[i-1][w][h], Pal[Buffer[w][h]], 3);
					}
				}

			}
			break;
		case 24:
			{ 
				File.Read(&ImageBuf[i-1][0][0][0], nWidth * nHeight * 3);
			}
			break;
		}

		/*
		int j, k;
		for(j = 0; j < nWidth; j++)
		{
			for(k = 0; k < nHeight; k++)
			{
				ImageFile.Write(&ImageBuf[i-1][j][k][0], 1);
				ImageFile.Write(&ImageBuf[i-1][j][k][1], 1);
				ImageFile.Write(&ImageBuf[i-1][j][k][2], 1);
				//ImageFile.Write((COLORREF *)&ImageBuf[i-1][j][k], 4);
			}
		}
		*/
		File.Close();
	}
	ImageFile.Write(ImageBuf, sizeof(ImageBuf));
	ImageFile.Close();	
}

void CMapEditDlg::ReadImageFile()
{
	CFile ImageFile;
	ImageFile.Open(TILE_FILE_NAME, CFile::modeRead);
	ImageFile.Read(&ImageBuf[0][0][0][0], PIC_TOTEL * 32 * 32 * 3);
	ImageFile.Close();
}

void CMapEditDlg::ReadMapFile()
{
	CFile MapFile;
	MapFile.Open(MAP_FILE_NAME, CFile::modeRead);
	MapFile.Read(&MapBuf[0][0][0], sizeof(MapBuf));
	MapFile.Close();
}

void CMapEditDlg::WriteMapFile()
{
	CFile MapFile;
	MapFile.Open(MAP_FILE_NAME, CFile::modeCreate | CFile::modeWrite);
	MapFile.Write(&MapBuf[0][0][0], sizeof(MapBuf));
	MapFile.Close();
}

void CMapEditDlg::WriteNpcFile()
{
	//memset(NpcBuf, 0, sizeof(NpcBuf));  只用创建文件时清0
	CFile NpcFile;
	NpcFile.Open(NPC_FILE_NAME, CFile::modeCreate | CFile::modeWrite);
	NpcFile.Write(&NpcBuf[0], sizeof(NpcBuf));
	NpcFile.Close();
}

void CMapEditDlg::ReadNpcFile()
{
	CFile NpcFile;
	NpcFile.Open(NPC_FILE_NAME, CFile::modeRead);
	NpcFile.Read(&NpcBuf[0], sizeof(NpcBuf));
	NpcFile.Close();
}
