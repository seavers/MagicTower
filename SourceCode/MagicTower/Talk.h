// Talk.h: interface for the CTalk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TALK_H__9F314AE0_E1F2_44EB_9562_FFA6D455145C__INCLUDED_)
#define AFX_TALK_H__9F314AE0_E1F2_44EB_9562_FFA6D455145C__INCLUDED_

#include "Tile.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct TALK
{
	IDTILE idTile[MAX_NPC_TILE];
	char szName[MAX_NAME];
	char szSentence1[MAX_WORDS];	//每段对话最多两行
	char szSentence2[MAX_WORDS];
};

class CTalk  
{
//Construction
public:
	CTalk();
	virtual ~CTalk();

//Initialization
public:
	void Load(IDTALK idTalk);

//Message handle
public:
	void OnTimer(UINT nIDEvent);
	BOOL OnKeyDown(UINT nChar);
	void OnDraw(CDC &dc);

//Data Member
private:
	static TALK Talk[MAX_TALK];	
	CTile Tile;
	int nTileIndex;
	IDTALK m_idTalk;
	//int	m_nTalkIndex;
};

#endif // !defined(AFX_TALK_H__9F314AE0_E1F2_44EB_9562_FFA6D455145C__INCLUDED_)
