// Info.cpp: implementation of the CInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Info.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInfo::CInfo()
{
	nBorderWidth = 5;
	crBorderColor = BORDER_COLOR;
}

CInfo::~CInfo()
{

}

void CInfo::DrawBorder(CDC &dc, CRect Rect)
{
	int i, j;
	for(i = 0; i < Rect.Width() / TILE_WIDTH; i++)
	{
		for(j = 0; j < Rect.Height() / TILE_HEIGHT; j++)
		{
			Tile.Draw(dc, Rect.left + i * TILE_WIDTH, Rect.top + j * TILE_HEIGHT, TILE_FLOOR);
		}
	}	
	CBrush Brush(crBorderColor);	
	for(i = 0; i < nBorderWidth; i++)
	{
		Rect.InflateRect(1, 1);
		dc.FrameRect(&Rect, &Brush);
	}
}

void CInfo::OnDraw(CDC &dc, CRect Rect, const ROLEINFO RoleInfo, const CString SceneName)
{
	//DrawBorder(dc, Rect);

	CRect InfoRect[4];
	InfoRect[0].SetRect(32, 45, 32 + 5 * 32, 45 + 4 * 32);
	InfoRect[1].SetRect(32, 180, 32 + 5 * 32, 180 + 3 * 32);
	InfoRect[2].SetRect(32, 280, 32 + 5 * 32, 280 + 1 * 32);
	InfoRect[3].SetRect(32, 333, 32 + 5 * 32, 333 + 2 * 32);

	DrawBorder(dc, InfoRect[0]);
	DrawBorder(dc, InfoRect[1]);
	DrawBorder(dc, InfoRect[2]);
	DrawBorder(dc, InfoRect[3]);

	//set font
	CFont Font;
	Font.CreatePointFont(12 * 10, "幼圆");
	dc.SelectObject(&Font);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkMode(TRANSPARENT);

	//info rect
	int nInfoLeft = 32;
	int nInfoStart = 40;
	int nInfoInterval = 16;
	CString sDisplay;

	//info rect 1
	Tile.Draw(dc, InfoRect[0].left + nInfoLeft / 2, InfoRect[0].top + 4, 173);
	sDisplay.Format("         %d  级", RoleInfo.nLevel);
	dc.TextOut(InfoRect[0].left + nInfoLeft, InfoRect[0].top + 16, sDisplay);
	sDisplay.Format("生命     %d", RoleInfo.nHealth);
	dc.TextOut(InfoRect[0].left + nInfoLeft, InfoRect[0].top + nInfoStart + nInfoInterval * 0, sDisplay);
	sDisplay.Format("攻击     %d", RoleInfo.nAttack);
	dc.TextOut(InfoRect[0].left + nInfoLeft, InfoRect[0].top + nInfoStart + nInfoInterval * 1, sDisplay);
	sDisplay.Format("防御     %d", RoleInfo.nDefense);
	dc.TextOut(InfoRect[0].left + nInfoLeft, InfoRect[0].top + nInfoStart + nInfoInterval * 2, sDisplay);
	sDisplay.Format("金币     %d", RoleInfo.nMoney);
	dc.TextOut(InfoRect[0].left + nInfoLeft, InfoRect[0].top + nInfoStart + nInfoInterval * 3, sDisplay);
	sDisplay.Format("经验     %d", RoleInfo.nExperience);
	dc.TextOut(InfoRect[0].left + nInfoLeft, InfoRect[0].top + nInfoStart + nInfoInterval * 4, sDisplay);

	//info rect 1
	Tile.Draw(dc, InfoRect[1].left + nInfoLeft, InfoRect[1].top + 0,  62);
	Tile.Draw(dc, InfoRect[1].left + nInfoLeft, InfoRect[1].top + 32, 61);
	Tile.Draw(dc, InfoRect[1].left + nInfoLeft, InfoRect[1].top + 64, 60);
	sDisplay.Format("%d 个", RoleInfo.nYellowKey);
	dc.TextOut(InfoRect[1].left + nInfoLeft * 3, InfoRect[1].top + 8,  sDisplay);
	sDisplay.Format("%d 个", RoleInfo.nBlueKey);
	dc.TextOut(InfoRect[1].left + nInfoLeft * 3, InfoRect[1].top + 40, sDisplay);
	sDisplay.Format("%d 个", RoleInfo.nRedKey);
	dc.TextOut(InfoRect[1].left + nInfoLeft * 3, InfoRect[1].top + 72, sDisplay);

	//info rect 2
	dc.TextOut(InfoRect[2].left + nInfoLeft * 1 + 16, InfoRect[2].top + 8,  SceneName);

	//info rect 3
	dc.TextOut(InfoRect[3].left + nInfoLeft * 0 + 12, InfoRect[3].top + 8,   "S 保存");
	dc.TextOut(InfoRect[3].left + nInfoLeft * 2 + 12, InfoRect[3].top + 8,  "Q 退出程序");
	dc.TextOut(InfoRect[3].left + nInfoLeft * 0 + 12, InfoRect[3].top + 40,   "A 读取");
	dc.TextOut(InfoRect[3].left + nInfoLeft * 2 + 12, InfoRect[3].top + 40,  "R 重新开始");
}
