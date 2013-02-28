// BaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "surface.h"
#include "SurfaceDoc.h"
#include "SurfaceView.h"
#include "BaseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseDlg dialog


CBaseDlg::CBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseDlg)
	DDX_Control(pDX, IDC_TAB, m_TabCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseDlg, CDialog)
	//{{AFX_MSG_MAP(CBaseDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
BOOL CBaseDlg::Create( CSurfaceView * pParent) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pCSurfaceView = pParent;
	//return TRUE;
	return CDialog::Create(IDD, pParent);
}
// CBaseDlg message handlers

BOOL CBaseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_TabCtrl.SetParent(m_pCSurfaceView);
	m_TabCtrl.InsertItem(0, _T("Control"));
	m_TabCtrl.InsertItem(1, _T("Settings"));
	m_TabCtrl.InsertItem(2, _T("Legend"));
	m_TabCtrl.Init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

