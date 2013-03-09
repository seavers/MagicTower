// Tile.cpp: implementation of the CTile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Tile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////
//Tile 数据 共有MAX_TILE 个, 每个TILE_WIDTH * TILE_HEIGHT 个点, 每个点用RGB 三个字节表示
BYTE CTile::TileData[MAX_TILE][TILE_WIDTH][TILE_HEIGHT][3];

void CTile::InitTile()
{
	//Read Tile File
	CFile ImageFile;
	ImageFile.Open(TILE_FILE_NAME, CFile::modeRead);
	ImageFile.Read(CTile::TileData, MAX_TILE * TILE_WIDTH * TILE_HEIGHT * 3);
	ImageFile.Close();
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTile::CTile()
{
	//Set Tile Format
	memset(&bmif, 0, sizeof(bmif));
	bmif.bmiHeader.biSize = sizeof(bmif.bmiHeader);
	bmif.bmiHeader.biBitCount = 24;
	bmif.bmiHeader.biWidth = TILE_WIDTH;
	bmif.bmiHeader.biHeight = TILE_HEIGHT;
	bmif.bmiHeader.biPlanes = 1;
}

CTile::~CTile()
{

}

void CTile::Draw(CDC &dc, int x, int y, IDTILE idTile)
{
	::SetDIBitsToDevice(dc.m_hDC, x, y, TILE_WIDTH, TILE_HEIGHT, 0, 0, 0, 32, TileData[idTile], &bmif, DIB_RGB_COLORS);
}

void CTile::DrawEx(CDC &dc, int x, int y, IDTILE idTile, IDTILE idRoleTile)
{

	BYTE RoleTileData[32][32][3];
	int i, j;
	for(i = 0; i < TILE_HEIGHT; i++)
	{
		for(j = 0; j < TILE_WIDTH; j++)
		{
			COLORREF Color = RGB(TileData[idRoleTile][j][i][2], TileData[idRoleTile][j][i][1], TileData[idRoleTile][j][i][0]);
			if((Color & 0x00FCFCFC) != 0x00FCFCFC)
			{
				memcpy(RoleTileData[j][i], TileData[idRoleTile][j][i], 3);
			}
			else
			{
				memcpy(RoleTileData[j][i], TileData[idTile][j][i], 3);
			}
		}
	}
	::SetDIBitsToDevice(dc.m_hDC, x, y, TILE_WIDTH, TILE_HEIGHT, 0, 0, 0, TILE_HEIGHT, RoleTileData, &bmif, DIB_RGB_COLORS);
}
