// WordFind.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WordFind.h"
#include "WordFindDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordFindApp

BEGIN_MESSAGE_MAP(CWordFindApp, CWinApp)
	//{{AFX_MSG_MAP(CWordFindApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordFindApp construction

CWordFindApp::CWordFindApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWordFindApp object

CWordFindApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWordFindApp initialization

BOOL CWordFindApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CWordFindDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
