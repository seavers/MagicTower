// Fight.cpp: implementation of the CFight class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Fight.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFight::CFight()
{
	nTileIndex = 0;
	bAttack = TRUE;			//用于控制战斗出手顺序, TRUE为主角先出手
}

CFight::~CFight()
{

}

void CFight::Load(IDTILE idTile[], NPCINFO NpcInfo, ROLEINFO RoleInfo)
{
	memcpy(m_idTile, idTile, MAX_NPC_TILE);
	m_RoleInfo = RoleInfo;
	m_NpcInfo = NpcInfo;
	::AfxGetMainWnd()->SetTimer(TIMER_FIGHT, 50, NULL);
}

void CFight::OnDraw(CDC &dc)
{
	//边框
	
	CRect Rect(CPoint(100, 100), CSize(15 * TILE_WIDTH, 8 * TILE_HEIGHT));
	int i, j;
	for(i = 0; i < Rect.Width() / TILE_WIDTH; i++)
	{
		for(j = 0; j < Rect.Height() / TILE_HEIGHT; j++)
		{
			Tile.Draw(dc, Rect.left + i * TILE_WIDTH, Rect.top + j * TILE_HEIGHT, TILE_FLOOR);
		}
	}	
	COLORREF crBorderColor = BORDER_COLOR;
	int nBorderWidth = 5;
	CBrush Brush(crBorderColor);	
	for(i = 0; i < nBorderWidth; i++)
	{
		Rect.InflateRect(1, 1);
		dc.FrameRect(&Rect, &Brush);
	}
	
	Tile.DrawEx(dc, Rect.left + TILE_WIDTH, Rect.top + TILE_HEIGHT / 2, TILE_FLOOR, TILE_ROLE);
	Tile.Draw(dc, Rect.right - TILE_WIDTH * 2, Rect.top + TILE_HEIGHT / 2, m_idTile[nTileIndex]);

	//设置显示字体
	int nFontSize = 16;
	CFont Font;
	Font.CreatePointFont(nFontSize * 10, "仿宋体");
	dc.SelectObject(&Font);
	dc.SetTextColor(RGB(255, 180, 0));
	dc.SetBkMode(TRANSPARENT);

	//显示信息
	char szNum[10];
	CPen Pen(PS_SOLID, 3, RGB(160, 160, 160));
	dc.SelectObject(&Pen);
	//主角
	dc.SetTextAlign(TA_LEFT | VTA_CENTER);
	dc.TextOut(Rect.left + 3 * TILE_WIDTH, Rect.top + TILE_HEIGHT , "勇士", 4);
	dc.TextOut(Rect.left + 2 * TILE_WIDTH, 100 + TILE_HEIGHT * 2, "生命值", 6);
	dc.TextOut(Rect.left + 2 * TILE_WIDTH, 100 + TILE_HEIGHT * 4, "攻击力", 6);
	dc.TextOut(Rect.left + 2 * TILE_WIDTH, 100 + TILE_HEIGHT * 6, "防御力", 6);
	itoa(m_RoleInfo.nHealth, szNum, 10);
	dc.TextOut(Rect.left + 5 * TILE_WIDTH, 100 + TILE_HEIGHT * 3, szNum, strlen(szNum));
	itoa(m_RoleInfo.nAttack, szNum, 10);
	dc.TextOut(Rect.left + 5 * TILE_WIDTH, 100 + TILE_HEIGHT * 5, szNum, strlen(szNum));
	itoa(m_RoleInfo.nDefense, szNum, 10);
	dc.TextOut(Rect.left + 5 * TILE_WIDTH, 100 + TILE_HEIGHT * 7, szNum, strlen(szNum));
	dc.MoveTo(Rect.left + 1 * TILE_WIDTH, 100 + TILE_HEIGHT * 3 - 4);
	dc.LineTo(Rect.left + 6 * TILE_WIDTH, 100 + TILE_HEIGHT * 3 - 4);
	dc.MoveTo(Rect.left + 1 * TILE_WIDTH, 100 + TILE_HEIGHT * 5 - 4);
	dc.LineTo(Rect.left + 6 * TILE_WIDTH, 100 + TILE_HEIGHT * 5 - 4);
	dc.MoveTo(Rect.left + 1 * TILE_WIDTH, 100 + TILE_HEIGHT * 7 - 4);
	dc.LineTo(Rect.left + 6 * TILE_WIDTH, 100 + TILE_HEIGHT * 7 - 4);
	
	//敌人
	dc.SetTextAlign(TA_RIGHT | VTA_CENTER);
	dc.TextOut(Rect.right - 3 * TILE_WIDTH, Rect.top + TILE_HEIGHT , "怪物", 4);
	dc.TextOut(Rect.right - 2 * TILE_WIDTH, 100 + TILE_HEIGHT * 2, "生命值", 6);
	dc.TextOut(Rect.right - 2 * TILE_WIDTH, 100 + TILE_HEIGHT * 4, "攻击力", 6);
	dc.TextOut(Rect.right - 2 * TILE_WIDTH, 100 + TILE_HEIGHT * 6, "防御力", 6);
	itoa(m_NpcInfo.nHealth, szNum, 10);
	dc.TextOut(Rect.right - 5 * TILE_WIDTH, 100 + TILE_HEIGHT * 3, szNum, strlen(szNum));
	itoa(m_NpcInfo.nAttack, szNum, 10);
	dc.TextOut(Rect.right - 5 * TILE_WIDTH, 100 + TILE_HEIGHT * 5, szNum, strlen(szNum));
	itoa(m_NpcInfo.nDefense, szNum, 10);
	dc.TextOut(Rect.right - 5 * TILE_WIDTH, 100 + TILE_HEIGHT * 7, szNum, strlen(szNum));
	dc.MoveTo(Rect.right - 1 * TILE_WIDTH, 100 + TILE_HEIGHT * 3 - 4);
	dc.LineTo(Rect.right - 6 * TILE_WIDTH, 100 + TILE_HEIGHT * 3 - 4);
	dc.MoveTo(Rect.right - 1 * TILE_WIDTH, 100 + TILE_HEIGHT * 5 - 4);
	dc.LineTo(Rect.right - 6 * TILE_WIDTH, 100 + TILE_HEIGHT * 5 - 4);
	dc.MoveTo(Rect.right - 1 * TILE_WIDTH, 100 + TILE_HEIGHT * 7 - 4);
	dc.LineTo(Rect.right - 6 * TILE_WIDTH, 100 + TILE_HEIGHT * 7 - 4);

	//返回默认
	dc.SetTextAlign(TA_LEFT);
}

BOOL CFight::OnKeyDown(UINT nChar)
{
	return TRUE;
}

BOOL CFight::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == TIMER_SCENE)			//场景计时, 更改TILE索引, 实现动画
	{
		nTileIndex = (nTileIndex + 1) % MAX_NPC_TILE;
		return TRUE;
	}
	else if(nIDEvent == TIMER_FIGHT)		//战斗计时, 更改生命数值, 实现战斗
	{
//		sndPlaySound(SOUND_FIGHT_FILE, SND_SYNC | SND_FILENAME | SND_NODEFAULT);		//发出打斗声音
		if(bAttack == TRUE)
		{
			if(m_RoleInfo.nAttack - m_NpcInfo.nDefense > 0)
			{
				m_NpcInfo.nHealth -= (m_RoleInfo.nAttack - m_NpcInfo.nDefense);
			}
		}
		else
		{
			if(m_NpcInfo.nAttack - m_RoleInfo.nDefense > 0)
			{
				m_RoleInfo.nHealth -= (m_NpcInfo.nAttack - m_RoleInfo.nDefense);
			}
			
		}
		bAttack = !bAttack;
		if(m_NpcInfo.nHealth <= 0 || m_RoleInfo.nHealth <= 0)
		{
			bAttack = TRUE;			//由于CFight不是战斗完后消毁, 所有得手动更改状态
			::AfxGetMainWnd()->KillTimer(TIMER_FIGHT);
			return FALSE;
		}
	}
	return TRUE;
}

ROLEINFO CFight::GetResult()
{
	return m_RoleInfo;
}
