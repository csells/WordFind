// WordFindDlg.h : header file
//

#if !defined(AFX_WORDFINDDLG_H__DB5B5056_5D17_11D1_9694_00600819B080__INCLUDED_)
#define AFX_WORDFINDDLG_H__DB5B5056_5D17_11D1_9694_00600819B080__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning(disable:4786)
#include <set>
#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CWordFindDlg dialog

class CWordFindDlg : public CDialog
{
// Construction
public:
	CWordFindDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWordFindDlg)
	enum { IDD = IDD_WORDFIND_DIALOG };
	CEdit	m_ebMinLen;
	CEdit	m_ebWord;
	CButton	m_grpWords;
	CButton	m_btnFind;
	CEdit	m_ebFound;
	CEdit	m_ebChecking;
	CListBox	m_lbWords;
	CString	m_sWord;
	long	m_nMinLen;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordFindDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWordFindDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnFind();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool PumpMessages();
	bool ReadDictionary();

    long        m_nMaxLen;
    bool        m_bFinding;

	struct InsensitiveCompare {
		bool operator() (const std::string& a, const std::string& b) const {
			return stricmp(a.c_str(), b.c_str()) < 0;
		}
	};

	//set<string, InsensitiveCompare> m_setWords;
	set<string> m_setWords;
public:
	afx_msg void OnBnClickedUpper();
	afx_msg void OnBnClickedLower();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDFINDDLG_H__DB5B5056_5D17_11D1_9694_00600819B080__INCLUDED_)
