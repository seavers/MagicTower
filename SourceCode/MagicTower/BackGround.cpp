// BackGround.cpp: implementation of the CBackGround class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "BackGround.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBackGround::CBackGround()
{

}

CBackGround::~CBackGround()
{

}

void CBackGround::OnDraw(CDC &dc)
{
	int i, j;
	for(i = 0; i < MAX_WIDTH / TILE_WIDTH + 1; i++)
	{
		for(j = 0; j < MAX_HEIGHT / TILE_HEIGHT; j++)
		{
			Tile.Draw(dc, i * TILE_WIDTH, j * TILE_HEIGHT, TILE_BG);
		}
	}
}
