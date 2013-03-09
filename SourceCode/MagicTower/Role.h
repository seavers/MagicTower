// Role.h: interface for the CRole class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROLE_H__F0312A8C_C6CF_4689_85C0_65E938EAAEF0__INCLUDED_)
#define AFX_ROLE_H__F0312A8C_C6CF_4689_85C0_65E938EAAEF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct ROLEINFO
{
	int nLevel;
	int nHealth;
	int nAttack;
	int nDefense;
	int nMoney;
	int nExperience;
	int nRedKey;
	int nBlueKey;	
	int nYellowKey;	
};

class CRole  
{
//Construction
public:
	CRole();
	virtual ~CRole();

//Message handle
public:	
	void OnTimer(UINT nIDEvent);
	CPoint GetNextPoint(UINT nChar);		//Ïàµ±ÓÚOnKeyDown()
	void MoveTo(CPoint ptPos);

//Access Function
public:
	ROLEINFO GetRoleInfo();
	void SetRoleInfo(ROLEINFO RoleInfo);
	CPoint GetPos();
	void SetPos(CPoint ptPos, IDTILE idTile, BOOL bTurn = FALSE);
	IDTILE GetRoleTileID();
	BOOL IsRoleTileID(IDTILE idTile);
private:
	int GetTileIndex(IDTILE idTile);

//Data Member
private:
	CPoint m_ptPos;
	CRect m_rtWalk;
	ROLEINFO RoleInfo;
	static IDTILE idTiles[MAX_ROLE_TILE];	
	int m_nTileIndex;
};

#endif // !defined(AFX_ROLE_H__F0312A8C_C6CF_4689_85C0_65E938EAAEF0__INCLUDED_)
