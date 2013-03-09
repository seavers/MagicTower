// Script.h: interface for the CScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPT_H__3CE6A282_B535_486F_8881_2541400CA5EE__INCLUDED_)
#define AFX_SCRIPT_H__3CE6A282_B535_486F_8881_2541400CA5EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SCRIPT
{
	IDFUN idFun;
	DWORD Param1;
	DWORD Param2;
	DWORD Param3;
};

struct SCRIPTS
{
	IDSCRIPT idScript;
	SCRIPT Script[MAX_COMMAND];
};

class CScript  
{
//Construction
public:
	CScript();
	virtual ~CScript();

//Initialization
public:
	static void InitScript();
	void LoadScript(IDSCRIPT idScript);
	void LoadNextScript();	

//Access Function
	SCRIPT GetScriptInfo();

//Data Members
private:
	static SCRIPTS Script[MAX_SCRIPT];
	SCRIPT m_Script;
	int m_nScriptIndex;
	int m_nCommandIndex;		
};

#endif // !defined(AFX_SCRIPT_H__3CE6A282_B535_486F_8881_2541400CA5EE__INCLUDED_)
