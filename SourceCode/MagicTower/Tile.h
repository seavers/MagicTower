// Tile.h: interface for the CTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILE_H__AFD43AC9_297D_4939_9C41_F0D046D9941C__INCLUDED_)
#define AFX_TILE_H__AFD43AC9_297D_4939_9C41_F0D046D9941C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTile  
{
//Construction
public:
	CTile();
	virtual ~CTile();

//Initialization
public:
	static void InitTile();

//Message handle
	void DrawEx(CDC &dc,int x, int y, IDTILE idTile, IDTILE idRoleTile);
	void Draw(CDC &dc, int x, int y, IDTILE idTile = TILE_FLOOR);

//Data Members
private:	
	static BYTE TileData[MAX_TILE][TILE_WIDTH][TILE_HEIGHT][3];
	BITMAPINFO bmif;
};

#endif // !defined(AFX_TILE_H__AFD43AC9_297D_4939_9C41_F0D046D9941C__INCLUDED_)
