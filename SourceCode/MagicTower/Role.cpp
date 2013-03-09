// Role.cpp: implementation of the CRole class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Role.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////
IDTILE CRole::idTiles[MAX_ROLE_TILE] =		//TILE信息
{
//	站立, 行走1,2, BOSS战中被打
	144, 145, 146, 147,			//左
	152, 153, 154, 155,			//上
	148, 149, 150, 151,			//右
	138, 141, 142, 143,			//下
};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRole::CRole()
{
	m_nTileIndex = 4;
	m_ptPos.x = 5;		//Role最开始被载入时的坐标信息
	m_ptPos.y = 9;	
	m_rtWalk.SetRect(0, 0, MAP_WIDTH, MAP_HEIGHT);

	RoleInfo.nLevel = 1;
	RoleInfo.nHealth = 1000;
	RoleInfo.nAttack = 10;
	RoleInfo.nDefense = 10;
	RoleInfo.nMoney = 0;
	RoleInfo.nExperience = 0;
	RoleInfo.nYellowKey = 1;
	RoleInfo.nBlueKey = 1;
	RoleInfo.nRedKey = 1;
}

CRole::~CRole()
{

}

void CRole::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == TIMER_ROLE)
	{
		m_nTileIndex --;			//Tile变换, 实现人物行走动画
		if(m_nTileIndex % 4 == 0)
		{
			::AfxGetMainWnd()->KillTimer(nIDEvent);
		}
	}
}

CPoint CRole::GetNextPoint(UINT nChar)
{
 	CPoint r_ptPos = m_ptPos;
	switch(nChar)
	{
		case 'W':
		case VK_UP:
			r_ptPos.y--;
			m_nTileIndex = 6;
			break;
		case 'S':
		case VK_DOWN:
			r_ptPos.y++;
			m_nTileIndex = 14;
			break;
		case 'A':
		case VK_LEFT:
			r_ptPos.x--;
			m_nTileIndex = 2;
			break;
		case 'D':
		case VK_RIGHT:
			r_ptPos.x++;
			m_nTileIndex = 10;
			break;
		default:
			return m_ptPos;
	}
	::AfxGetMainWnd()->SetTimer(TIMER_ROLE, 200, NULL);
	if(m_rtWalk.PtInRect(r_ptPos))
	{
		return r_ptPos;
	}
	else
	{
		return m_ptPos;
	}	
}

//bTurn  用于楼梯切换时, 保持出去时与进来时的TILE方向正好相反, bTurn 为真表示, 切换, 为假表示不切换
void CRole::SetPos(CPoint ptPos, IDTILE idTile, BOOL bTurn)
{
	int nTileIndex = GetTileIndex(idTile);
	if(bTurn)
	{
		m_nTileIndex = ((nTileIndex / 4) * 4  + 2 + MAX_ROLE_TILE / 2) % MAX_ROLE_TILE;
	}
	else
	{
		m_nTileIndex = ((nTileIndex / 4) * 4  + 2) % MAX_ROLE_TILE;
	}
	m_ptPos = ptPos;	
}

void CRole::MoveTo(CPoint ptPos)
{
	m_ptPos = ptPos;	
}

CPoint CRole::GetPos()
{
	return m_ptPos;
}

IDTILE CRole::GetRoleTileID()
{
	return idTiles[m_nTileIndex];
}

BOOL CRole::IsRoleTileID(IDTILE idTile)
{
	int i;
	for(i = 0; i < MAX_ROLE_TILE; i++)
	{
		if(idTiles[i] == idTile)
		{
			return TRUE;
		}
	}
	return FALSE;
}

int CRole::GetTileIndex(IDTILE idTile)
{
	int i;
	for(i = 0; i < MAX_ROLE_TILE; i++)
	{
		if(idTiles[i] == idTile)
		{
			return i;
		}
	}
	return 4;			//默认4
}

ROLEINFO CRole::GetRoleInfo()
{
	return RoleInfo;
}

void CRole::SetRoleInfo(ROLEINFO Info)
{
	memcpy(&RoleInfo, &Info, sizeof(RoleInfo));
}
