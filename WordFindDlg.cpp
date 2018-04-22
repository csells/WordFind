// WordFindDlg.cpp : implementation file
//
#include "stdafx.h"
#include "WordFind.h"
#include "WordFindDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <assert.h>
#include <algorithm>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CWordFindDlg dialog

CWordFindDlg::CWordFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWordFindDlg::IDD, pParent),
	m_bFinding(false),
	m_nMaxLen(0)
{
	//{{AFX_DATA_INIT(CWordFindDlg)
	m_sWord = _T("");
	//}}AFX_DATA_INIT
	m_nMinLen = 3;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWordFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWordFindDlg)
	DDX_Control(pDX, IDC_MIN_LEN, m_ebMinLen);
	DDX_Control(pDX, IDC_WORD, m_ebWord);
	DDX_Control(pDX, IDC_WORD_GROUP, m_grpWords);
	DDX_Control(pDX, ID_FIND, m_btnFind);
	DDX_Control(pDX, IDC_FOUND, m_ebFound);
	DDX_Control(pDX, IDC_CHECKING, m_ebChecking);
	DDX_Control(pDX, IDC_WORD_LIST, m_lbWords);
	DDX_Text(pDX, IDC_WORD, m_sWord);
	DDX_Text(pDX, IDC_MIN_LEN, m_nMinLen);
	DDV_MinMaxLong(pDX, m_nMinLen, 1, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWordFindDlg, CDialog)
	//{{AFX_MSG_MAP(CWordFindDlg)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(ID_FIND, OnFind)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_UPPER, &CWordFindDlg::OnBnClickedUpper)
	ON_BN_CLICKED(IDC_LOWER, &CWordFindDlg::OnBnClickedLower)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordFindDlg message handlers

BOOL CWordFindDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if (!ReadDictionary())
	{
		MessageBox("Couldn't read words");
		EndDialog(IDABORT);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWordFindDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CDialog(IDD_ABOUTBOX).DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

bool CWordFindDlg::PumpMessages()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if (!::AfxGetApp()->PumpMessage())
		{
			m_bFinding = false;
			::PostQuitMessage(0);
			return false;
		}
	}

	// let MFC do its idle processing
	LONG lIdle = 0;
	while (AfxGetApp()->OnIdle(lIdle++));
	return true;
}

void CWordFindDlg::OnFind()
{
	if (!m_bFinding)
	{
		m_bFinding = true;
		m_btnFind.SetWindowText("Stop");
		m_ebChecking.SetWindowText("");
		m_ebFound.SetWindowText("");
		m_grpWords.SetWindowText("Words: 0");
		m_ebWord.EnableWindow(FALSE);
		m_ebMinLen.EnableWindow(FALSE);

		if (UpdateData(TRUE))
		{
			m_lbWords.ResetContent();
			set<string> setFoundWords;

			// Only check letters
			string sWord;
			for (int i = 0; i < m_sWord.GetLength(); i++)
			{
				if (isalpha(m_sWord[i])) sWord += m_sWord[i];
			}

			// Sort string (the permutation algorithm depends on it)
			sort(sWord.begin(), sWord.end());

			// Find all words of all lengths > 1
			do
			{
				m_ebChecking.SetWindowText(sWord.c_str());
				if (!PumpMessages()) break;

				for (int len = min(sWord.length(), m_nMaxLen); m_bFinding && len >= m_nMinLen; --len)
				{
					string sCopy(sWord.end() - len, sWord.end());

					// If it's in the dictionary and not a word already found
					if ((m_setWords.find(sCopy) != m_setWords.end()) &&
						(setFoundWords.find(sCopy) == setFoundWords.end()))
					{
						// Add it to the list
						setFoundWords.insert(sCopy);
						m_ebFound.SetWindowText(sCopy.c_str());

						m_lbWords.AddString(sCopy.c_str());
						CString sGroupCaption;
						sGroupCaption.Format("Words: %d", m_lbWords.GetCount());
						m_grpWords.SetWindowText(sGroupCaption);

						if (!PumpMessages()) break;
					}
				}
			} while (m_bFinding &&
				next_permutation(sWord.begin(), sWord.end()));

		}

		m_bFinding = false;
		m_btnFind.SetWindowText("Find");
		m_ebWord.EnableWindow(TRUE);
		m_ebMinLen.EnableWindow(TRUE);
	}
	else
	{
		m_bFinding = false;
	}
}

bool CWordFindDlg::ReadDictionary()
{
	assert(m_setWords.size() == 0);

	CStdioFile  file("words", CFile::modeRead | CFile::typeText);
	CString     s;

	while (file.ReadString(s))
	{
		try
		{
			m_setWords.insert((const char*)s);
			int len = s.GetLength();
			if (len > m_nMaxLen) m_nMaxLen = len;
		}
		catch (...)
		{
			AfxTrace("error: word= %s\n", s);
		}
	}

	AfxTrace("read words= %d\n", m_setWords.size());
	return true;
}


void CWordFindDlg::OnCancel()
{
	m_bFinding = false;
	CDialog::OnCancel();
}

void CWordFindDlg::OnDestroy()
{
	m_bFinding = false;
	CDialog::OnDestroy();
}

bool SetClipboardString(const char* psz)
{
	HANDLE  hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, strlen(psz) + 1);
	if (hMem)
	{
		char*   pszMem = (char*)GlobalLock(hMem);
		strcpy(pszMem, psz);
		GlobalUnlock(hMem);

		if (OpenClipboard(0))
		{
			EmptyClipboard();
			SetClipboardData(CF_TEXT, hMem);
			CloseClipboard();
			return true;
		}
		else
		{
			GlobalFree(hMem);
		}
	}

	return false;
}

void CWordFindDlg::OnCopy()
{
	if (m_bFinding)
	{
		MessageBox("Stop finding to do a Copy");
	}
	else
	{
		CString sAll;
		for (int i = 0; i < m_lbWords.GetCount(); i++)
		{
			CString sItem;
			m_lbWords.GetText(i, sItem);
			sAll += sItem;
			sAll += "\r\n";
		}

		if (SetClipboardString(sAll))
		{
			MessageBox("Words copied to the Clipboard");
		}
		else
		{
			MessageBox("Unable to copy the words to the Clipboard");
		}
	}
}



void CWordFindDlg::OnBnClickedUpper()
{
	CString s;
	m_ebWord.GetWindowText(s);
	s.MakeUpper();
	m_ebWord.SetWindowText(s);
}


void CWordFindDlg::OnBnClickedLower()
{
	CString s;
	m_ebWord.GetWindowText(s);
	s.MakeLower();
	m_ebWord.SetWindowText(s);
}
