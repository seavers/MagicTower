// Game.cpp: implementation of the CGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Game.h"
#include "Tile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGame::CGame()
{
	//Init All Global Data
	CTile::InitTile();
	CNpc::InitNpc();
	CScript::InitScript();

	//Game Const
	GameState = GS_INIT;
	GameClient.cx = MAX_WIDTH;
	GameClient.cy = MAX_HEIGHT;
	InfoRect.SetRect(32, 50, 32 + 5 * 32, 50 + MAP_HEIGHT * 32);
	MainRect.SetRect(250, 50, 250 + MAP_WIDTH * 32, 50 + MAP_HEIGHT * 32);	
	m_bRun = false;

	//Create Cache DC
	CDC *pMainDC = ::AfxGetMainWnd()->GetDC();
	CBitmap CacheBitmap, MapBitmap;
	CacheDC.CreateCompatibleDC(pMainDC);	
	CacheBitmap.CreateCompatibleBitmap(pMainDC, GameClient.cx, GameClient.cy);
	CacheDC.SelectObject(&CacheBitmap);
	MapDC.CreateCompatibleDC(pMainDC);
	MapBitmap.CreateCompatibleBitmap(pMainDC, MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_HEIGHT);
	MapDC.SelectObject(&MapBitmap);
	::AfxGetMainWnd()->ReleaseDC(pMainDC);

	//Set Game Client
	::AfxGetMainWnd()->SetWindowPos(NULL, 70, 50, GameClient.cx, GameClient.cy, SWP_NOZORDER);

	Story.Init();
}

CGame::~CGame()
{

}

void CGame::OnDraw(CDC &dc)
{
	switch(GameState)
	{
		case GS_INIT:
			Story.OnDraw(CacheDC);			
			break;
		case GS_OVER:
			{
				CRect Rect(0, 0, MAX_WIDTH, MAX_HEIGHT);
				CBrush Brush(RGB(255, 255, 255));
				CacheDC.SelectObject(&Brush);
				CacheDC.Rectangle(&Rect);
				CacheDC.SetTextColor(RGB(0, 0, 0));
				CacheDC.TextOut(100, 100, "胜败乃兵家常事, ", 16);
				CacheDC.TextOut(150, 130, "大侠重新来过吧! ", 16);
			}
			break;
		default:
			//主画面
			BackGround.OnDraw(CacheDC);					//背景
			Info.DrawBorder(CacheDC, MainRect);			//右边边框
			Info.OnDraw(CacheDC, InfoRect, Scene.GetRoleInfo(), Scene.GetSceneName());		//左边信息
			Scene.OnDraw(MapDC);						//游戏画面
			CacheDC.BitBlt(MainRect.left, MainRect.top, MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_HEIGHT, &MapDC, 0, 0, SRCCOPY);

			//对话或战斗画面
			switch(GameState)
			{
				case GS_TALK:
					Talk.OnDraw(CacheDC);
					break;
				case GS_FIGHT:
					Fight.OnDraw(CacheDC);
					break;

			}
	}
	dc.BitBlt(0, 0, GameClient.cx, GameClient.cy, &CacheDC, 0, 0, SRCCOPY);
}

BOOL CGame::OnKeyDown(UINT nChar)
{
	//游戏状态按键处理, 相当于系统按键消息
	switch(nChar)
	{
		case 'Q':		//退出程序
			::AfxGetMainWnd()->SendMessage(WM_CLOSE);
			break;
		case 'R':		//游戏结束, 重新开始, 
			return FALSE;
			break;
	}
	
	//游戏按键处理
	switch(GameState)
	{
		case GS_INIT:
			if(Story.OnKeyDown(nChar) == FALSE)
			{
				GameState = GS_WALK;
				sndPlaySound(SOUND_BG_FILE, SND_ASYNC | SND_FILENAME | SND_NODEFAULT | SND_LOOP);
			}
			break;
		case GS_WALK:
			ptCurNpcPos = Scene.GetRoleNextPoint(nChar);			//取角色下一步坐标
			if(IDSCRIPT idScript = Scene.GetScriptID(ptCurNpcPos))	//取相应NPC的脚本号
			{
				Script.LoadScript(idScript);						//载入脚本命令
				RecurScript();										//开始脚本循环
			}
			else
			{
				Scene.SetRolePos(ptCurNpcPos);						//无NPC, 前进
			}
			break;
		case GS_TALK:
			if(Talk.OnKeyDown(nChar) == FALSE)		//Talk 返回FALSE, 结束对话
			{
				GameState = GS_WALK;
				RecurScript();
			}
			break;
		case GS_FIGHT:
			if(Fight.OnKeyDown(nChar) == FALSE)					//Fight返回FALSE, 战斗结束
			{
				//Scene.SetRoleInfo(Fight.GetResult());			//获取战斗结果				
				GameState = GS_WALK;
				RecurScript();
			}			
			break;
		case GS_OVER:
			return FALSE;
	}
	::AfxGetMainWnd()->Invalidate(FALSE);
	return TRUE;
}

void CGame::OnTimer(UINT nIDEvent)
{
	Scene.OnTimer(nIDEvent);	//本应只写于GS_WALK, 写于此, 为了使场景中NPC始终保持动画
	switch(GameState)			//分发Timer
	{
		case GS_INIT:
			if(Story.OnTimer(nIDEvent) == FALSE)
			{
				GameState = GS_WALK;
				sndPlaySound(SOUND_BG_FILE, SND_ASYNC | SND_FILENAME | SND_NODEFAULT | SND_LOOP);
			}
			break;
		case GS_WALK:			
			break;
		case GS_TALK:
			Talk.OnTimer(nIDEvent);
			break;
		case GS_FIGHT:
			if(Fight.OnTimer(nIDEvent) == FALSE)			//Fight返回FALSE, 战斗结束
			{
				Scene.HideNpc(ptCurNpcPos);
				sndPlaySound(SOUND_BG_FILE, SND_ASYNC | SND_FILENAME | SND_NODEFAULT | SND_LOOP);
				GameState = GS_WALK;
				RecurScript();
			}
			ROLEINFO RoleInfo = Fight.GetResult();
			Scene.SetRoleInfo(RoleInfo);
			if(RoleInfo.nHealth <= 0)
			{
				GameState = GS_OVER;
			}			
			break;
	}
	
	//用于脚本延时
	/*
	if(nIDEvent == TIMER_DELAY)
	{
		::AfxGetMainWnd()->KillTimer(TIMER_DELAY);
		RecurScript();
	}
	*/

	::AfxGetMainWnd()->Invalidate(FALSE);
}

void CGame::RecurScript()
{
	m_bRun = TRUE;
	while(m_bRun)
	{
		ProcScript();
		Script.LoadNextScript();
	}
}

void CGame::ProcScript()
{
	IDFUN idFun = Script.GetScriptInfo().idFun;			//脚本命令编号
	DWORD Param1 = Script.GetScriptInfo().Param1;		//主要用于传递ID号
	DWORD Param2 = Script.GetScriptInfo().Param2;		//主要用于传递X坐标
	DWORD Param3 = Script.GetScriptInfo().Param3;		//主要用于传递Y坐标
	switch(idFun)
	{
		case SC_NULL:	
			m_bRun = false;
			break;
		case SC_SCENEFORWARD:
			Scene.Forward();			
			break;
		case SC_SCENEBACKWARD:
			Scene.Backward();
			break;
		case SC_FIGHT:					//战斗
			m_bRun = FALSE;				//暂时退出脚本, 战斗结束后继续
			GameState = GS_FIGHT;		//进入战斗状态
			ROLEINFO RoleInfo;
			NPCINFO	NpcInfo;
			IDTILE idTile[MAX_NPC_TILE];
			RoleInfo = Scene.GetRoleInfo();			//获取角色信息
			Scene.GetNpcTile(ptCurNpcPos, idTile, &NpcInfo);	//获取NPC信息
			Fight.Load(idTile, NpcInfo, RoleInfo);		//用角色信息与NPC信息初使化战斗,
			break;
		case SC_TALK:
			m_bRun = FALSE;				//暂时退出脚本, 对话结束后继续
			GameState = GS_TALK;		//进入对话状态
			Talk.Load(Param1);			//载入对话
			break;
		case SC_NPC:
			{
				//_CrtDumpMemoryLeaks();	//检测内存泄露的
				ROLEINFO RoleInfo = Scene.GetRoleInfo();			
				NPCINFO NpcInfo = Scene.GetNpcInfo(ptCurNpcPos);			
				bool bNpcValid = true;							//RoleInfo, NpcInfo对应段相加是否有效
				int i;
				for(i = 0; i < sizeof(RoleInfo) / sizeof(int); i++)
				{
					int *pRole = (int *)&RoleInfo + i;			//将RoleInfo按int分段
					int *pNpc = (int *)&NpcInfo + i;			//将NpcInfo按int分段
					if((*pRole) + (*pNpc) < 0 )					//将相应的项相加, 即血相加, 攻相加, 防相加...
					{
						bNpcValid = false;
						break;
					}				
				}
				if(bNpcValid)				//有效则相加所有分段
				{
					for(i = 0; i < sizeof(RoleInfo) / sizeof(int); i++)
					{
						int *pRole = (int *)&RoleInfo + i;
						int *pNpc = (int *)&NpcInfo + i;
						*pRole += *pNpc;			
					}
					Scene.SetRoleInfo(RoleInfo);		//将结果写入角色信息中
					Scene.HideNpc(ptCurNpcPos);			//Npc消失
				}
			}
			break;
		case SC_SETNPCPOS:
			Scene.SetNpcPos(ptCurNpcPos, CPoint(Param2, Param3));		//设置相应NPC坐标
			break;

			//以下注释掉的为其它命令, 已不在使用, 只做备份
			/*
		case SC_DELAY:
			m_bRun = false;
			::AfxGetMainWnd()->SetTimer(TIMER_DELAY, Param1, NULL);
			break;
		case SC_LOADSCENE:
			Scene.Load(Param1);
			break;
		case SC_SETROLEPOS:
			Scene.SetRolePos(CPoint(Param2, Param3));
			break;
		
			/*
		case SC_HIDENPC:
			Scene.HideNpc(CPoint(Param2, Param3));
			break;
		case SC_HIDECURNPC:			
			Scene.HideNpc(ptCurNpcPos);
			break;
			*/
		default:
			//m_bRun = false;
			break;			
	}
	::AfxGetMainWnd()->Invalidate(FALSE);
}

