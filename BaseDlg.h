#if !defined(AFX_BASEDLG_H__E214A1B1_3FEC_43D7_834F_48BA2884A961__INCLUDED_)
#define AFX_BASEDLG_H__E214A1B1_3FEC_43D7_834F_48BA2884A961__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseDlg.h : header file
//
#include "MyTabCtr.h"

/////////////////////////////////////////////////////////////////////////////
// CBaseDlg dialog
class CSurfaceView;

class CBaseDlg : public CDialog
{
	CSurfaceView * m_pCSurfaceView;
// Construction
public:
	CBaseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBaseDlg)
	enum { IDD = IDD_DLG_BASE };
	CMyTabCtr	m_TabCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseDlg)
	public:
	virtual BOOL Create( CSurfaceView * pParent) ;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBaseDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEDLG_H__E214A1B1_3FEC_43D7_834F_48BA2884A961__INCLUDED_)
