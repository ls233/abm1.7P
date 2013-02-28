#if !defined(AFX_MYTABCTR_H__52E4AE2D_FA6D_4A40_94D0_E0324C64F32C__INCLUDED_)
#define AFX_MYTABCTR_H__52E4AE2D_FA6D_4A40_94D0_E0324C64F32C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTabCtr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtr window
class CSurfaceView;

class CMyTabCtr : public CTabCtrl
{
// Construction
public:
	CMyTabCtr();
	CDialog *m_tabPages[3];
	int m_tabCurrent;
	int m_nNumberOfPages;
	CSurfaceView * m_pCSurfaceView;

// Attributes
public:
	void Init();
	void SetRectangle();
	void SetParent(CSurfaceView * parent);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTabCtr)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyTabCtr();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTabCtr)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTABCTR_H__52E4AE2D_FA6D_4A40_94D0_E0324C64F32C__INCLUDED_)
