#if !defined(AFX_RESULT_H__97AFB17A_9B34_4FCC_9731_1C06D5A865E1__INCLUDED_)
#define AFX_RESULT_H__97AFB17A_9B34_4FCC_9731_1C06D5A865E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Result.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResult dialog
class CSurfaceView;
class CResult : public CDialog
{
// Construction
public:
	CResult(CWnd* pParent = NULL);   // standard constructor
	void SetView(CSurfaceView * pview);
	CSurfaceView * m_pCSurfaceView;

//  CFont m_fntTahoma;

// Dialog Data
	//{{AFX_DATA(CResult)
	enum { IDD = IDD_RESULT };
	CStatic	m_Raft;
	CStatic	m_InactiveFyn;
	CStatic	m__ActiveLyn;
	CStatic	m_Ligand;
	CStatic	m_SM;
	CStatic	m_A_SM;
	CStatic	m__2armBCR;
	CStatic	m__1armBCR;
	CStatic	m__2arm_A_BCR;
	CStatic	m__1arm_A_BCR;
	CStatic	m_freeBCR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResult)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResult)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULT_H__97AFB17A_9B34_4FCC_9731_1C06D5A865E1__INCLUDED_)
