// Fight.h: interface for the CFight class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIGHT_H__BBC0ED33_631C_40B3_BD07_07667C062D69__INCLUDED_)
#define AFX_FIGHT_H__BBC0ED33_631C_40B3_BD07_07667C062D69__INCLUDED_

#include "Npc.h"	// Added by ClassView    
#include "Tile.h"	// Added by ClassView
#include "Global.h"	// Added by ClassView
#include "Role.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFight  
{
//Construction
public:
	CFight();
	virtual ~CFight();

//Initialization
public:
	void Load(IDTILE idTile[MAX_NPC_TILE], NPCINFO NpcInfo, ROLEINFO RoleInfo);

//Message handle
public:	
	BOOL OnTimer(UINT nIDEvent);
	BOOL OnKeyDown(UINT nChar);
	void OnDraw(CDC &dc);

//State
public:
ROLEINFO GetResult();
private:
	BOOL bAttack;			//主角攻击还是怪物攻击

//Tile
private:
	CTile Tile;
	IDTILE m_idTile[MAX_NPC_TILE];		//怪物Tile列表
	int nTileIndex;						//怪物列表索引	
	ROLEINFO m_RoleInfo;	
	NPCINFO m_NpcInfo;	
};

#endif // !defined(AFX_FIGHT_H__BBC0ED33_631C_40B3_BD07_07667C062D69__INCLUDED_)
