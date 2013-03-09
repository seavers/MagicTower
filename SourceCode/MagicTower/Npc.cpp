// NpcData.cpp: implementation of the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Npc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////
NPCTILE CNpc::NpcData[MAX_NPC] =
{
	{36,  36,  SI_NPC, 1},			//¶Ü1
	{37,  37,  SI_NPC, 1},			//¶Ü2
	{38,  38,  SI_NPC, 1},			//¶Ü3
	{39,  39,  SI_NPC, 1},			//¶Ü4
	{40,  40,  SI_NPC, 1},			//¶Ü5
	{41,  41,  SI_NPC, 1},			//½£1
	{42,  42,  SI_NPC, 1},			//½£2
	{43,  43,  SI_NPC, 1},			//½£3
	{44,  44,  SI_NPC, 1},			//½£4
	{45,  45,  SI_NPC, 1},			//½£5
	{46,  46,  SI_SHOP, 1},			//ÉÌµê1
	{47,  47,  SI_SHOP, 1},			//ÉÌµê2
	{48,  171, SI_WALL, 1},			//ÐÇÐÇ
	{49,  172, SI_WALL, 1},			//ÈÛÑÒ
	{50,  50,  SI_NPC, 1},			//ÕÈ1
	{51,  51,  SI_NPC, 1},			//ÕÈ2
	{52,  52,  SI_NPC, 1},			//ÕÈ3
	{53,  53,  SI_SECRET, 1},		//»ú¹Ø
	{54,  54,  SI_EXIT, 1},			//Èë¿Ú
	{55,  55,  SI_ENTRY, 1},		//³ö¿Ú
	{56,  56,  SI_NPC, 1},			//À¶ÑªÆ¿
	{57,  57,  SI_NPC, 1},			//ºìÑªÆ¿
	{58,  58,  SI_NPC, 1},			//ºì±¦Ê¯
	{59,  59,  SI_NPC, 1},			//À¶±¦Ê¯
	{60,  60,  SI_NPC, 1},			//ºìÔ¿³×
	{61,  61,  SI_NPC, 1},			//À¶Ô¿³×
	{62,  62,  SI_NPC, 1},			//»ÆÔ¿³×
	{63,  63,  SI_SECRET, 1},		//Ê¯ÃÅ
	{64,  64,  SI_NPC, 1},			//ºìÃÅ
	{65,  65,  SI_NPC, 1},			//À¶ÃÅ
	{66,  66,  SI_NPC, 1},			//»ÆÃÅ
	{67,  67,  SI_WALL, 1},			//Ç½
	{68,  68,  SI_FLOOR, 1},		//µØ°å
	{83,  84,  SI_MONSTER, 1},		//¹Ö
	{85,  86,  SI_MONSTER, 1},		//¹Ö
	{87,  88,  SI_MONSTER, 1},		//¹Ö
	{89,  90,  SI_MONSTER, 1},		//¹Ö
	{91,  92,  SI_MONSTER, 1},		//¹Ö
	{93,  94,  SI_MONSTER, 1},		//¹Ö
	{95,  96,  SI_MONSTER, 1},		//¹Ö
	{97,  98,  SI_MONSTER, 1},		//¹Ö
	{99,  100, SI_MONSTER, 1},		//¹Ö
	{101, 102, SI_MONSTER, 1},		//¹Ö
	{103, 104, SI_MONSTER, 1},		//¹Ö
	{105, 106, SI_MONSTER, 1},		//¹Ö
	{107, 108, SI_MONSTER, 1},		//¹Ö
	{109, 110, SI_MONSTER, 1},		//¹Ö
	{111, 112, SI_MONSTER, 1},		//¹Ö
	{113, 114, SI_MONSTER, 1},		//¹Ö
	{115, 116, SI_MONSTER, 1},		//¹Ö
	{117, 118, SI_MONSTER, 1},		//¹Ö
	{119, 120, SI_MONSTER, 1},		//¹Ö
	{121, 122, SI_MONSTER, 1},		//¹Ö
	{123, 124, SI_MONSTER, 1},		//¹Ö
	{125, 126, SI_MONSTER, 1},		//¹Ö
	{127, 127, SI_NPC, 1},			//½ð¸Õ¶Ü
	{128, 128, SI_NPC, 1},			//ÎäÆ÷1
	{129, 129, SI_NPC, 1},			//ÎäÆ÷2
	{130, 130, SI_NPC, 1},			//Ê¥Ô¿³×
	{131, 131, SI_NPC, 1},			//Ê®×ÖïÚ
	{132, 132, SI_NPC, 1},			//·üÄ§½£
	{133, 133, SI_NPC, 1},			//Ê¥¹â±­
	{134, 134, SI_NPC, 1},			//Ê®×Ö¼Ü
	{135, 135, SI_NPC, 1},			//±¦ÎïÊá1
	{136, 136, SI_NPC, 1},			//±¦ÎïÊá2
	{137, 137, SI_NPC, 1},			//±¦ÎïÊá3
	{138, 138, SI_NULL, 1},			//Ö÷½Ç
	{139, 140, SI_CELESTIAL, 1},	//ÏÉ×Ó
	{156, 156, SI_NPC, 1},			//NPC
	{157, 158, SI_SHOP, 1},			//3²ãÉÌµê
	{159, 160, SI_NPC, 1},			//NPC
	{161, 162, SI_NPC, 1},			//NPC
	{163, 164, SI_NPC, 1},			//NPC
	{165, 166, SI_NPC, 1},			//NPC
	{167, 168, SI_MONSTER, 1},		//¹ÖÎï
	{169, 170, SI_MONSTER, 1},		//¹ÖÎï
};

NPCINFO CNpc::NpcInfo[MAX_NPC];

void CNpc::InitNpc()
{
	CFile NpcFile;
	NpcFile.Open(NPC_FILE_NAME, CFile::modeRead);
	NpcFile.Read(NpcInfo, sizeof(NpcInfo));				//Í¬ÎÄ¼þÖÐ¶ÁÈ¡NPCÐÅÏ¢
	NpcFile.Close();
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpc::CNpc()
{
	m_nTileIndex = 0;
	m_bShow = FALSE;
}

CNpc::~CNpc()
{

}

void CNpc::Load(IDTILE idTile)
{
	int i;
	for(i = 0; i < sizeof(NpcData) / sizeof(NpcData[0]); i++)
	{
		if(idTile == NpcData[i].idTile[0] || idTile == NpcData[i].idTile[1])
		{
			memcpy(m_idTile, NpcData[i].idTile, MAX_NPC_TILE);
			m_idScript = NpcData[i].idScript;
			m_bShow = NpcData[i].bShow;
			break;
		}
	}
}

void CNpc::Load(CNpc &Npc)
{
	memcpy(m_idTile, Npc.m_idTile, MAX_NPC_TILE);
	m_nTileIndex = Npc.m_nTileIndex;
	m_idScript = Npc.m_idScript;
	m_bShow = Npc.m_bShow;
}

void CNpc::OnTimer(UINT nIDEvent)
{
	m_nTileIndex = (m_nTileIndex + 1) % MAX_NPC_TILE;
}

void CNpc::Hide()
{
	m_bShow = FALSE;
}

IDTILE CNpc::GetTileID()
{
	if(m_bShow)
	{
		return m_idTile[m_nTileIndex];
	}
	else
	{
		return TILE_FLOOR;
	}
}

IDSCRIPT CNpc::GetScriptID()
{
 	if(m_bShow)
	{
		return m_idScript;
	}
	else
	{
		return 0;
	}
}

NPCINFO CNpc::GetNpcInfo()
{
	return NpcInfo[m_idTile[m_nTileIndex]];
}

void CNpc::GetNpcTile(IDTILE idTile[])
{
	memcpy(idTile, m_idTile, MAX_NPC_TILE);
}
