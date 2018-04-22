// WordFind.h : main header file for the WORDFIND application
//

#if !defined(AFX_WORDFIND_H__DB5B5054_5D17_11D1_9694_00600819B080__INCLUDED_)
#define AFX_WORDFIND_H__DB5B5054_5D17_11D1_9694_00600819B080__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWordFindApp:
// See WordFind.cpp for the implementation of this class
//

class CWordFindApp : public CWinApp
{
public:
	CWordFindApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordFindApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWordFindApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDFIND_H__DB5B5054_5D17_11D1_9694_00600819B080__INCLUDED_)
