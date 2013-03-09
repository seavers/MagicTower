// BackGround.h: interface for the CBackGround class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKGROUND_H__7C3470C6_33AC_4C4A_9E0B_801AB921EBD6__INCLUDED_)
#define AFX_BACKGROUND_H__7C3470C6_33AC_4C4A_9E0B_801AB921EBD6__INCLUDED_

#include "Tile.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBackGround  
{
//construction
public:
	CBackGround();
	virtual ~CBackGround();

//message handle
public:
	void OnDraw(CDC &dc);

//data members
private:
	CTile Tile;
};

#endif // !defined(AFX_BACKGROUND_H__7C3470C6_33AC_4C4A_9E0B_801AB921EBD6__INCLUDED_)
