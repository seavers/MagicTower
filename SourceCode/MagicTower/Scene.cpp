// Scene.cpp: implementation of the CScene class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Scene.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScene::CScene()
{
	//Init member data
	m_idScene = 0;
	m_idLayerDone = 0;
	memset(RoleEntryPos, 0, sizeof(RoleExitPos));
	memset(RoleExitPos, 0, sizeof(RoleExitPos));
	memset(RoleEntryTile, TILE_ROLE_ENTRY, sizeof(RoleExitTile));
	memset(RoleExitTile, TILE_ROLE_EXIT, sizeof(RoleExitTile));
	
	//下面从文件中读取所有NPC的数据写入缓冲
	//Data Cache
	IDTILE TileData[MAX_SCENE][MAP_WIDTH][MAP_HEIGHT];

	//Read Map File	
	CFile MapFile;
	MapFile.Open(MAP_FILE_NAME, CFile::modeRead);
	MapFile.Read(TileData, MAX_SCENE * MAP_WIDTH * MAP_HEIGHT);
	MapFile.Close();

	//Set All Npc
	int i, j, k;
	for(i = 0; i < MAX_SCENE; i++)
	{
		for(j = 0; j < MAP_WIDTH; j++)
		{
			for(k = 0; k < MAP_HEIGHT; k++)
			{
				if(Role.IsRoleTileID(TileData[i][j][k]))		//判断是否是主角
				{												//是则设置相应入口信息
					RoleEntryPos[i] = CPoint(j, k);
					RoleEntryTile[i] = TileData[i][j][k];
					Npc[i][j][k].Load(TILE_FLOOR);				//相应位置补充地板ID, Ps:正因地板ID唯一, 所以游戏未采用分层结构
				}
				else
				{
					Npc[i][j][k].Load(TileData[i][j][k]);		//相应位置载入相应NPC
				}				
			}
		}
	}

	//Set Timer
	::AfxGetMainWnd()->SetTimer(TIMER_SCENE, 250, NULL);		//启用SCENE, 主要用于NPC动画, Ps:此处应该实现于CTile的, 统一管理
}

CScene::~CScene()
{

}


//并未使用此函数, 第一层的主角设置, 由主角默认实现, 此功能在修改时被遗忘 ^o^ Ps:因偷懒未写场景载入脚本处理
void CScene::Load(IDSCENE idScene)
{
	m_idScene = idScene;
	Role.SetPos(RoleEntryPos[m_idScene], RoleEntryTile[m_idScene]);
}

void CScene::Forward()
{	
	RoleExitPos[m_idScene] = Role.GetPos();					//保存信息以备返回此场景
	RoleExitTile[m_idScene] = Role.GetRoleTileID();
	m_idScene++;
	if(m_idLayerDone < m_idScene)			//如果角色未到达过此层, 此由NPC数据中默认填写
	{
		m_idLayerDone = m_idScene;			//更改角色已到达的层数
		Role.SetPos(RoleEntryPos[m_idScene], RoleEntryTile[m_idScene], FALSE);
	}
	else
	{
		Role.SetPos(RoleEntryPos[m_idScene], RoleEntryTile[m_idScene], TRUE);
	}
}

void CScene::Backward()
{
	RoleEntryPos[m_idScene] = Role.GetPos();
	RoleEntryTile[m_idScene] = Role.GetRoleTileID();
	m_idScene--;
	Role.SetPos(RoleExitPos[m_idScene], RoleExitTile[m_idScene], TRUE);
}

void CScene::OnDraw(CDC &dc)
{
	//NPC
	int i, j;
	for(i = 0; i < MAP_WIDTH; i++)
	{
		for(j = 0; j < MAP_HEIGHT; j++)
		{
			Tile.Draw(dc, i * TILE_WIDTH, j * TILE_HEIGHT, Npc[m_idScene][i][j].GetTileID());
		}
	}

	//Role	
	IDTILE idRoleTile = Role.GetRoleTileID();
	CPoint ptRolePos = Role.GetPos();
	Tile.DrawEx(dc, ptRolePos.x * TILE_WIDTH, ptRolePos.y * TILE_HEIGHT, Npc[m_idScene][ptRolePos.x][ptRolePos.y].GetTileID(), idRoleTile);
}

void CScene::OnTimer(UINT nIDEvent)
{
	//继续分发
	if(nIDEvent == TIMER_SCENE)
	{
		int i, j;
		for(i = 0; i < MAP_WIDTH; i++)
		{
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				Npc[m_idScene][i][j].OnTimer(nIDEvent);
			}
		}
	}
	Role.OnTimer(nIDEvent);
}

CString CScene::GetSceneName()
{
	if(m_idScene == 0)
	{
		SceneName = "序    章";
	}
	else
	{
		SceneName.Format("第  %d  层", m_idScene);
	}
	return SceneName;
}

IDTILE CScene::GetRoleTileID()
{
	return Role.GetRoleTileID();
}

CPoint CScene::GetRolePos()
{
	return Role.GetPos();
}

CPoint CScene::GetRoleNextPoint(UINT nChar)
{
	return Role.GetNextPoint(nChar);
}

void CScene::SetRolePos(CPoint ptPos)
{
	Role.MoveTo(ptPos);
}

IDSCENE CScene::GetSceneID()
{
	return m_idScene;
}

IDSCRIPT CScene::GetScriptID(CPoint ptPos)
{
	return Npc[m_idScene][ptPos.x][ptPos.y].GetScriptID();
}

void CScene::SetNpcPos(CPoint ptNpcPos, CPoint ptNewPos)
{
	if(ptNpcPos != ptNewPos)
	{
		Npc[m_idScene][ptNewPos.x][ptNewPos.y].Load(Npc[m_idScene][ptNpcPos.x][ptNpcPos.y]);
		Npc[m_idScene][ptNpcPos.x][ptNpcPos.y].Load(TILE_FLOOR);
	}
}

void CScene::HideNpc(CPoint ptCurNpcPos)
{
	Npc[m_idScene][ptCurNpcPos.x][ptCurNpcPos.y].Hide();
}

NPCINFO CScene::GetNpcInfo(CPoint ptCurNpcPos)
{
	return Npc[m_idScene][ptCurNpcPos.x][ptCurNpcPos.y].GetNpcInfo();
}

void CScene::SetRoleInfo(ROLEINFO RoleInfo)
{
	Role.SetRoleInfo(RoleInfo);
}

ROLEINFO CScene::GetRoleInfo()
{
	return Role.GetRoleInfo();
}

void CScene::GetNpcTile(CPoint ptCurNpcPos, IDTILE idTile[MAX_NPC_TILE], NPCINFO *NpcInfo)
{
	Npc[m_idScene][ptCurNpcPos.x][ptCurNpcPos.y].GetNpcTile(idTile);
	*NpcInfo = Npc[m_idScene][ptCurNpcPos.x][ptCurNpcPos.y].GetNpcInfo();
}
