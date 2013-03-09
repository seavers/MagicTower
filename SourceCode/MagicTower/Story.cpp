// Story.cpp: implementation of the CStory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicTower.h"
#include "Story.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStory::CStory()
{
	//Buffer
	memset(StoryBuf, 0, MAX_BUFFER);
	StoryBufIndex = 0;	

	//play background sound
	CFile StoryFile;
	StoryFile.Open(STORY_FILE, CFile::modeRead);
	StoryFile.Read(StoryBuf, MAX_BUFFER);
	StoryFile.Close();

}

CStory::~CStory()
{
	
}

void CStory::Init()
{
	//Play Background Sound
	sndPlaySound(SOUND_INIT_FILE, SND_ASYNC | SND_FILENAME | SND_NODEFAULT);

	//Set Timer
	::AfxGetMainWnd()->SetTimer(TIMER_INIT, 50, NULL);
}

void CStory::OnDraw(CDC &dc)
{
	int nFontSize = 12;
	CRect Rect(0, 0, MAX_WIDTH, MAX_HEIGHT);
	CBrush Brush(STORY_BG_COLOR);
	dc.SelectObject(&Brush);
	dc.Rectangle(&Rect);

	Rect.InflateRect(-50, -50);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(STORY_FT_COLOR);
	CFont Font;
	Font.CreatePointFont(nFontSize * 10, "仿宋体");
	dc.SelectObject(&Font);	

	dc.DrawText(StoryBuf, StoryBufIndex, Rect, DT_LEFT);
	dc.TextOut(MAX_WIDTH - 100, MAX_HEIGHT - 50, "按空格跳过", 10);
}

BOOL CStory::OnKeyDown(UINT nChar)
{
	switch(nChar)
	{
		case VK_SPACE:
			return FALSE;
		default:
			return TRUE;
	}
}

BOOL CStory::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == TIMER_INIT)
	{
		StoryBufIndex += 1;
		if(StoryBufIndex >= MAX_BUFFER)
		{
			::AfxGetMainWnd()->KillTimer(TIMER_INIT);
		}
	}
	return TRUE;
}
