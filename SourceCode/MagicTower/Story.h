// Story.h: interface for the CStory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORY_H__1AD4A6D8_11DA_4503_894F_84EAF0C41679__INCLUDED_)
#define AFX_STORY_H__1AD4A6D8_11DA_4503_894F_84EAF0C41679__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStory  
{
//Construction
public:
	void Init();
	CStory();
	virtual ~CStory();

//Message handle
public:
	void OnDraw(CDC &dc);
	BOOL OnTimer(UINT nIDEvent);
	BOOL OnKeyDown(UINT nChar);

//Data Members
private:
	char StoryBuf[MAX_BUFFER];			//¹ÊÊÂÇé½Ú»º³å
	int StoryBufIndex;

};

#endif // !defined(AFX_STORY_H__1AD4A6D8_11DA_4503_894F_84EAF0C41679__INCLUDED_)
