// Info.h: interface for the CInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFO_H__8F6C8893_52E7_4D28_8540_4FF3D4E673DC__INCLUDED_)
#define AFX_INFO_H__8F6C8893_52E7_4D28_8540_4FF3D4E673DC__INCLUDED_

#include "Role.h"
#include "Tile.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInfo  
{
//Construction
public:
	CInfo();
	virtual ~CInfo();

//Message handle
	void DrawBorder(CDC &dc, CRect Rect);
	void OnDraw(CDC &dc, CRect Rect, const ROLEINFO RoleInfo, const CString SceneName);

//Tile
private:
	CTile Tile;
	COLORREF crBorderColor;			//±ß¿òÑÕÉ«
	int nBorderWidth;				//±ß¿ò¿í¶È
};

#endif // !defined(AFX_INFO_H__8F6C8893_52E7_4D28_8540_4FF3D4E673DC__INCLUDED_)
