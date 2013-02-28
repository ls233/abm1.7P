// SurfaceView.h : interface of the CSurfaceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURFACEVIEW_H__A25D9536_E096_417C_8EC1_750F0D8E4836__INCLUDED_)
#define AFX_SURFACEVIEW_H__A25D9536_E096_417C_8EC1_750F0D8E4836__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COption;
class CBaseDlg;
enum Msgs_ID { GEN_ONE = WM_USER+101 };  //gg1

class CSurfaceView : public CFormView
{
    int X, X1, Y, Y1, MatrixPart;
	int m_continue;
	CRect m_ClientRect ; 
protected: // create from serialization only
	CSurfaceView();
	DECLARE_DYNCREATE(CSurfaceView)
	COLORREF col[3];
	COLORREF col1[3];

public:
	//{{AFX_DATA(CSurfaceView)
	enum{ IDD = IDD_SURFACE_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
  afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);  //gg1

// Attributes
public:
	CSurfaceDoc* GetDocument();
	bool m_stopDraw;
	BOOL m_StepBy;
	int m_PartGridNum;
	bool m_Next ;
	int m_PartGrid ;
	int DrawSize;
	COption * m_OptionDlg;
	CBaseDlg * m_pdlg;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSurfaceView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSurfaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
int minZoom;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSurfaceView)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SurfaceView.cpp
inline CSurfaceDoc* CSurfaceView::GetDocument()
   { return (CSurfaceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SURFACEVIEW_H__A25D9536_E096_417C_8EC1_750F0D8E4836__INCLUDED_)
