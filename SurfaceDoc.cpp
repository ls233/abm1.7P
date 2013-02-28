// SurfaceDoc.cpp : implementation of the CSurfaceDoc class
//

#include "stdafx.h"
#include "Surface.h"

#include "SurfaceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurfaceDoc

IMPLEMENT_DYNCREATE(CSurfaceDoc, CDocument)

BEGIN_MESSAGE_MAP(CSurfaceDoc, CDocument)
	//{{AFX_MSG_MAP(CSurfaceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSurfaceDoc construction/destruction

CSurfaceDoc::CSurfaceDoc()
{
	// TODO: add one-time construction code here

}

CSurfaceDoc::~CSurfaceDoc()
{
}

BOOL CSurfaceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSurfaceDoc serialization

void CSurfaceDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSurfaceDoc diagnostics

#ifdef _DEBUG
void CSurfaceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSurfaceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSurfaceDoc commands
