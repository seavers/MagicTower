// Npc.h: interface for the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPC_H__683E5BFD_AD5B_483E_A7E7_735A9E7C3913__INCLUDED_)
#define AFX_NPC_H__683E5BFD_AD5B_483E_A7E7_735A9E7C3913__INCLUDED_

#include "Role.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef ROLEINFO		NPCINFO;

//NPCTILE 只记录了TILE 与脚本号, 而血攻防金钱经验钥匙信息存入文件由地图编辑器生成, Ps:事前没想好, 失误, 懒得改了
//NPC信息中没有MAP中相应坐标信息, 因为Scene采用了两维数组存储每层NPC
struct NPCTILE
{
	IDTILE idTile[MAX_NPC_TILE];
	IDSCRIPT idScript;
	BOOL bShow;
};

class CNpc  
{
//Construction
public:
	CNpc();
	virtual ~CNpc();

//Initialization
public:
	static void InitNpc();
	void Load(IDTILE idTile);
	void Load(CNpc &Npc);

//Message handle
public:
	void OnTimer(UINT nIDEvent);

//Access Function
public:
	IDTILE GetTileID();
	void GetNpcTile(IDTILE idTile[MAX_NPC_TILE]);
	NPCINFO GetNpcInfo();	
	IDSCRIPT GetScriptID();
	
//State
private:
	BOOL m_bShow;
public:	
	void Hide();

//Data members
private:
	static NPCTILE NpcData[MAX_NPC];
	static NPCINFO NpcInfo[MAX_NPC];	
	IDTILE m_idTile[MAX_NPC_TILE];
	int m_nTileIndex;
	IDSCRIPT m_idScript;
	
};

#endif // !defined(AFX_NPC_H__683E5BFD_AD5B_483E_A7E7_735A9E7C3913__INCLUDED_)
