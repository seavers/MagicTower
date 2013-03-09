// Scene.h: interface for the CScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENE_H__21A58979_F3D7_46AE_A102_C2DE4CD53343__INCLUDED_)
#define AFX_SCENE_H__21A58979_F3D7_46AE_A102_C2DE4CD53343__INCLUDED_

#include "Role.h"	// Added by ClassView
#include "Npc.h"	// Added by ClassView
#include "Tile.h"	// Added by ClassView
#include "Global.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScene  
{
//Construction
public:
	CScene();
	virtual ~CScene();

//Initialization
public:
	void Load(IDSCENE idScene);
	void Backward();
	void Forward();

//Message handle
public:
	void OnDraw(CDC &dc);
	void OnTimer(UINT nIDEvent);
	CPoint GetRoleNextPoint(UINT nChar);		//Ïàµ±ÓÚRole.OnKeyDown();

//Access Function
public:
	//Scene
	IDSCENE GetSceneID();
	CString GetSceneName();

	//Role
	IDTILE GetRoleTileID();
	CPoint GetRolePos();
	void SetRolePos(CPoint ptPos);
	ROLEINFO GetRoleInfo();
	void SetRoleInfo(ROLEINFO RoleInfo);

	//Npc
	void GetNpcTile(CPoint ptCurNpcPos, IDTILE idTile[MAX_NPC_TILE], NPCINFO *NpcInfo);
	NPCINFO GetNpcInfo(CPoint ptPos);
	IDSCRIPT GetScriptID(CPoint ptPos);
	void SetNpcPos(CPoint ptNpcPos, CPoint ptNewPos);	
	void HideNpc(CPoint ptCurNpcPos);

//Data Member
private:
	//Scene
	CString SceneName;
	IDSCENE m_idScene;
	IDSCENE m_idLayerDone;
	CTile Tile;

	//Npc
	CNpc Npc[MAX_SCENE][MAP_WIDTH][MAP_HEIGHT];

	//Npc
	CRole Role;
	CPoint RoleEntryPos[MAX_SCENE];
	CPoint RoleExitPos[MAX_SCENE];
	IDTILE RoleEntryTile[MAX_SCENE];
	IDTILE RoleExitTile[MAX_SCENE];
};

#endif // !defined(AFX_SCENE_H__21A58979_F3D7_46AE_A102_C2DE4CD53343__INCLUDED_)
