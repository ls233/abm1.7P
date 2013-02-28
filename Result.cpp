// Result.cpp : implementation file
//

#include "stdafx.h"
#include "surface.h"
#include "Result.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResult dialog


CResult::CResult(CWnd* pParent /*=NULL*/)
	: CDialog(CResult::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResult)
	//}}AFX_DATA_INIT
}


void CResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResult)
	DDX_Control(pDX, IDC_STATIC_Raft, m_Raft);
	DDX_Control(pDX, IDC_STATIC_InactiveFyn, m_InactiveFyn);
	DDX_Control(pDX, IDC_STATIC_ActiveLyn, m__ActiveLyn);
	DDX_Control(pDX, IDC_STATIC_Ligand, m_Ligand);
	DDX_Control(pDX, IDC_STATIC_SM, m_SM);
	DDX_Control(pDX, IDC_STATIC_A_SM, m_A_SM);
	DDX_Control(pDX, IDC_STATIC_2armBCR, m__2armBCR);
	DDX_Control(pDX, IDC_STATIC_1armBCR, m__1armBCR);
	DDX_Control(pDX, IDC_STATIC__2arm_A_BCR, m__2arm_A_BCR);
	DDX_Control(pDX, IDC_STATIC__1arm_A_BCR, m__1arm_A_BCR);
	DDX_Control(pDX, IDC_STATIC_freeBCR, m_freeBCR);
	//}}AFX_DATA_MAP
}

void CResult::SetView(CSurfaceView * pview)
{
	m_pCSurfaceView = pview;
}


BEGIN_MESSAGE_MAP(CResult, CDialog)
	//{{AFX_MSG_MAP(CResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResult message handlers

BOOL CResult::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  CFont m_fntTahoma;
  m_fntTahoma.CreatePointFont (100,"Tahoma");
  m_freeBCR.SetFont(&m_fntTahoma);
  m__1armBCR.SetFont(&m_fntTahoma);
  m__2armBCR.SetFont(&m_fntTahoma);
  m__1arm_A_BCR.SetFont(&m_fntTahoma);
  m__2arm_A_BCR.SetFont(&m_fntTahoma);
  m_SM.SetFont(&m_fntTahoma);
  m__ActiveLyn.SetFont(&m_fntTahoma);
  m_InactiveFyn.SetFont(&m_fntTahoma);
  m_A_SM.SetFont(&m_fntTahoma);
  m_Raft.SetFont(&m_fntTahoma);
  m_Ligand.SetFont(&m_fntTahoma);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CResult::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//	 m_fntTahoma.DeleteObject();

	return CDialog::DestroyWindow();
}
