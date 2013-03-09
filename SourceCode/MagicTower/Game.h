// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__7A4DE706_D886_42BC_A77C_AF1A5C7D1632__INCLUDED_)
#define AFX_GAME_H__7A4DE706_D886_42BC_A77C_AF1A5C7D1632__INCLUDED_

#include "Story.h"	// Added by ClassView
#include "Fight.h"	// Added by ClassView
#include "Talk.h"	// Added by ClassView
#include "Role.h"	// Added by ClassView
#include "Scene.h"	// Added by ClassView
#include "Npc.h"	// Added by ClassView
#include "BackGround.h"	// Added by ClassView
#include "Info.h"	// Added by ClassView
#include "Script.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *															|	Load()			Init
 *							Game							|	
 *															|	OnKeyDown();	Input
 *		Scene			|	Fight	|	Talk	|	Info	|	OnDraw();		Output
 *	 Role	Npc[11][11]	|			|			|			|	OnTimer();		Timer
 *															|
 *							Tile							|	Get()/Set()
 *															|
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

//Game State
enum GAMESTATE
{
	GS_INIT, GS_WALK, GS_TALK, GS_FIGHT, GS_OVER
};

class CGame  
{
//Construction
public:
	CGame();
	virtual ~CGame();

//Message handle
public:	
	BOOL OnKeyDown(UINT nChar);
	void OnDraw(CDC &dc);
	void OnTimer(UINT nIDEvent);


//Game State
private:
	GAMESTATE GameState;		//游戏状态
	BOOL m_bRun;				//脚本状态

//Data Members
private:
	CSize GameClient;			//整个游戏客户区位置与大小
	CRect MainRect;				//游戏场景的位置与大小
	CRect InfoRect;				//左边信息框的位置与大小
	CPoint ptCurNpcPos;			//当前NPC坐标
	CDC CacheDC;				//主缓冲DC
	CDC MapDC;					//游戏场景缓冲DC

//contain object
private:
	CBackGround BackGround;	
	CScene Scene;
	CFight Fight;
	CTalk Talk;	
	CInfo Info;					//人物信息	
	CScript Script;
	CStory Story;

//Script Function
private:
	void RecurScript();			//脚本循环
	void ProcScript();			//脚本处理函数
};

#endif // !defined(AFX_GAME_H__7A4DE706_D886_42BC_A77C_AF1A5C7D1632__INCLUDED_)
