// SurfaceDoc.h : interface of the CSurfaceDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURFACEDOC_H__C3A0FC5E_CFBC_47C7_8813_DF6527541F38__INCLUDED_)
#define AFX_SURFACEDOC_H__C3A0FC5E_CFBC_47C7_8813_DF6527541F38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSurfaceDoc : public CDocument
{
    int X, X1, Y, Y1, MatrixPart, DrawPart;
	int m_PartGrid ;
protected: // create from serialization only
	CSurfaceDoc();
	DECLARE_DYNCREATE(CSurfaceDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSurfaceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSurfaceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSurfaceDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SURFACEDOC_H__C3A0FC5E_CFBC_47C7_8813_DF6527541F38__INCLUDED_)
