// Orders.cpp : implementation file
//

#include "stdafx.h"
#include "surface.h"
#include "SigMol.h"
#include "Orders.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrders dialog


COrders::COrders(CWnd* pParent /*=NULL*/)
	: CDialog(COrders::IDD, pParent)
{
	//{{AFX_DATA_INIT(COrders)
	m_DifCoef = 0.0;
	m_RAFT_PROBABILITY_TO_MERGE = 0.0;
	m_Snap25_D = 0.0;
	m_Ppob_SynSNAP25Vamp_Dis = 0.0;
	m_Ppob_SynSNAP25_Dis = 0.0;
	m_Ppob_SntSNAP25Snt_Dis = 0.0;
	m_StepsNumber = 0;
	m_Stx_D = 0.0;
	m_Vamp_D = 0.0;
	m_D_ESF = 0.0;
	m_initStxNumber = 0;
	m_initNSFnumber = 0;
	m_initSNAP25Number = 0;
	m_initVampNumber = 0;
	m_SNAP25Pin_raft = 0.0;
	m_SNAP25Pour_raft = 0.0;
	m_StxPin_raft = 0.0;
	m_StxPout_raft = 0.0;
	m_Vamp_Pin_raft = 0.0;
	m_Vamp_Pout_raft = 0.0;
	m_Ppob_Syn_Bind_SNAP25 = 0.0;
	m_Ppob_SynSNAP25_BindVamp = 0.0;
	m_initStxInRaftFract = 0.0;
	m_initSnap25InRaftFract = 0.0;
	m_initNSFInRaftFract = 0.0;
	m_initVampInRaftFract = 0.0;
	m_Snt_SNAP25_Pin_raft = 0.0;
	m_Snt_SNAP25_Vamp_Pin_raft = 0.0;
	m_Snt_SNAP25_Vamp_Pout_raft = 0.0;
	m_Snt_SNAP25_Pout_raft = 0.0;
	m_RaftNumber = 0;
	m_MeanRaftSize = 0;
	m_P_NSF_on_Snt_Snap = 0.0;
	m_Snap25_D_inRaft = 0.0;
	m_Snt_D_inRaft = 0.0;
	m_Vamp_D_inRaft = 0.0;
	m_initSntSnap25inRaftFraction = 0.0;
	m_initSntSnap25VampinRaftFraction = 0.0;
	m_initSntSnap25Number = 0;
	m_initSntSnap25VampNumber = 0;
	m_initSnt_Snap25VampAlphaNum = 0;
	m_initSnt_Snap25VampAlphaInRaftFract = 0.0;
	m_Ppob_SynSNAPVamp_BindAlpha = 0.0;
	m_SntSNAP_VampAlpha_Pin_raft = 0.0;
	m_SntSNAP_VampAlpha_Pout_raft = 0.0;
	m_D_Alpha = 0.0;
	m_LifeTime_Alpha = 0;
	m_LifeTime_NSF = 0;
	m_NSFtoRemoveCompl = FALSE;
	m_Ppob_SntSNAP25VampAlpha_Dis = 0.0;
	m_Ppob_Snt_bind_Snt = 0.0;
	m_Ppob_SntSnt_Dis = 0.0;
	m_Ppob_SntSnt_bind_Snt = 0.0;
	m_Ppob_SntSntSnt_Dis = 0.0;
	m_SntSnt_Pin_raft = 0.0;
	m_SntSnt_Pout_raft = 0.0;
	m_SntSntSnt_Pin_raft = 0.0;
	m_SntSntSnt_Pout_raft = 0.0;
	m_initSntSntInRaftFract = 0.0;
	m_initSntSntSnt_InRaftFract = 0.0;
	m_initSntSnt_num = 0;
	m_m_initSntSntSnt_num = 0;
	m_initAlphaInRaftFract = 0.0;
	m_initAlphaNum = 0;
	m_Ptransloc_Alpha = 0.0;
	m_Ptransloc_NSF = 0.0;
	//}}AFX_DATA_INIT
}


void COrders::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrders)
	DDX_Text(pDX, IDC_EDIT_Diffusion_Coefficient, m_DifCoef);
	DDV_MinMaxDouble(pDX, m_DifCoef, 0., 100.);
	DDX_Text(pDX, IDC_EDIT_RAFT_PROBABILITY_TO_MERGE, m_RAFT_PROBABILITY_TO_MERGE);
	DDX_Text(pDX, IDC_EDIT_Snap25_D, m_Snap25_D);
	DDV_MinMaxDouble(pDX, m_Snap25_D, 0., 1.);
	DDX_Text(pDX, IDC_EDIT_Ppob_SynSNAP25VAMP_Dis, m_Ppob_SynSNAP25Vamp_Dis);
	DDX_Text(pDX, IDC_EDIT_Ppob_SynSNAP25_Dis, m_Ppob_SynSNAP25_Dis);
	DDX_Text(pDX, IDC_EDIT_Ppob_SntSNAP25Snt_Dis, m_Ppob_SntSNAP25Snt_Dis);
	DDX_Text(pDX, IDC_EDIT_StepsNumber, m_StepsNumber);
	DDX_Text(pDX, IDC_EDIT_Stx_D, m_Stx_D);
	DDX_Text(pDX, IDC_EDIT_Vamp_D, m_Vamp_D);
	DDX_Text(pDX, IDC_EDIT_D_ESF, m_D_ESF);
	DDX_Text(pDX, IDC_EDIT_initStxNumber, m_initStxNumber);
	DDX_Text(pDX, IDC_EDIT_initNSFNumber, m_initNSFnumber);
	DDX_Text(pDX, IDC_EDIT_initSNAP25Number, m_initSNAP25Number);
	DDX_Text(pDX, IDC_EDIT_initVampNumber, m_initVampNumber);
	DDX_Text(pDX, IDC_EDIT_SNAP25Pin_raft, m_SNAP25Pin_raft);
	DDX_Text(pDX, IDC_EDIT_SNAP25Pout_raft, m_SNAP25Pour_raft);
	DDX_Text(pDX, IDC_EDIT_StxPin_raft, m_StxPin_raft);
	DDX_Text(pDX, IDC_EDIT_StxPout_raft, m_StxPout_raft);
	DDX_Text(pDX, IDC_EDIT_VampPin_raft, m_Vamp_Pin_raft);
	DDX_Text(pDX, IDC_EDIT_VampPout_raft, m_Vamp_Pout_raft);
	DDX_Text(pDX, IDC_EDIT_Ppob_Snt_bind_SNAP25, m_Ppob_Syn_Bind_SNAP25);
	DDX_Text(pDX, IDC_EDIT_Ppob_Snt_SNAP25_bind_Vamp, m_Ppob_SynSNAP25_BindVamp);
	DDX_Text(pDX, IDC_EDIT_initStxInRaftFract, m_initStxInRaftFract);
	DDX_Text(pDX, IDC_EDIT_initSNAP25InRaftFract, m_initSnap25InRaftFract);
	DDX_Text(pDX, IDC_EDIT_initNSFInRaftFract, m_initNSFInRaftFract);
	DDX_Text(pDX, IDC_EDIT_initVampInRaftFract, m_initVampInRaftFract);
	DDX_Text(pDX, IDC_EDIT_Snt_SNAP25_Pin_raft, m_Snt_SNAP25_Pin_raft);
	DDX_Text(pDX, IDC_EDIT_Snt_SNAP25_Vamp_Pin_raft, m_Snt_SNAP25_Vamp_Pin_raft);
	DDX_Text(pDX, IDC_EDIT_Snt_SNAP25_Vamp_Pout_raft, m_Snt_SNAP25_Vamp_Pout_raft);
	DDX_Text(pDX, IDC_EDIT_Snt_SNAP25_Pout_raft, m_Snt_SNAP25_Pout_raft);
	DDX_Text(pDX, IDC_EDIT_Raft_number, m_RaftNumber);
	DDX_Text(pDX, IDC_EDIT_MeanRaftSize, m_MeanRaftSize);
	DDX_Text(pDX, IDC_EDIT_P_NSF_on_Snt_Snap, m_P_NSF_on_Snt_Snap);
	DDX_Text(pDX, IDC_EDIT_Snap25_D_inRaft, m_Snap25_D_inRaft);
	DDX_Text(pDX, IDC_EDIT_Stx_D_inRaft, m_Snt_D_inRaft);
	DDX_Text(pDX, IDC_EDIT_Vamp_D_inRaft, m_Vamp_D_inRaft);
	DDX_Text(pDX, IDC_EDIT_initSnt_Snap25InRaftFract, m_initSntSnap25inRaftFraction);
	DDX_Text(pDX, IDC_EDIT_initSnt_Snap25VampInRaftFract, m_initSntSnap25VampinRaftFraction);
	DDX_Text(pDX, IDC_EDIT_initSnt_Snap25Number, m_initSntSnap25Number);
	DDX_Text(pDX, IDC_EDIT_initSnt_Snap25VampNumber, m_initSntSnap25VampNumber);
	DDX_Text(pDX, IDC_EDIT_initSnt_Snap25VampAlphaNum, m_initSnt_Snap25VampAlphaNum);
	DDX_Text(pDX, IDC_EDIT_initSnt_Snap25VampAlphaInRaftFract, m_initSnt_Snap25VampAlphaInRaftFract);
	DDX_Text(pDX, IDC_EDIT_Ppob_SynSNAPVamp_BindAlpha, m_Ppob_SynSNAPVamp_BindAlpha);
	DDX_Text(pDX, IDC_EDIT_SntSNAP_VampAlpha_Pin_raft, m_SntSNAP_VampAlpha_Pin_raft);
	DDX_Text(pDX, IDC_EDIT_SntSNAP_VampAlpha_Pout_raft, m_SntSNAP_VampAlpha_Pout_raft);
	DDX_Text(pDX, IDC_EDIT_D_Alpha, m_D_Alpha);
	DDX_Text(pDX, IDC_EDIT_LifeTime_Alpha, m_LifeTime_Alpha);
	DDX_Text(pDX, IDC_EDIT_LifeTime_NSF, m_LifeTime_NSF);
	DDX_Check(pDX, IDC_CHECK_NSFtoRemoveCompl, m_NSFtoRemoveCompl);
	DDX_Text(pDX, IDC_EDIT_Ppob_SntSNAP25VampAlpha_Dis, m_Ppob_SntSNAP25VampAlpha_Dis);
	DDX_Text(pDX, IDC_EDIT_Ppob_Snt_bind_Snt, m_Ppob_Snt_bind_Snt);
	DDX_Text(pDX, IDC_EDIT_Ppob_SntSnt_Dis, m_Ppob_SntSnt_Dis);
	DDX_Text(pDX, IDC_EDIT_Ppob_SntSnt_bind_Snt, m_Ppob_SntSnt_bind_Snt);
	DDX_Text(pDX, IDC_EDIT_Ppob_SntSntSnt_Dis, m_Ppob_SntSntSnt_Dis);
	DDX_Text(pDX, IDC_EDIT_SntSnt_Pin_raft, m_SntSnt_Pin_raft);
	DDX_Text(pDX, IDC_EDIT_SntSnt_Pout_raft, m_SntSnt_Pout_raft);
	DDX_Text(pDX, IDC_EDIT_SntSntSnt_Pin_raft, m_SntSntSnt_Pin_raft);
	DDX_Text(pDX, IDC_EDIT_SntSntSnt_Pout_raft, m_SntSntSnt_Pout_raft);
	DDX_Text(pDX, IDC_EDIT_initSntSntInRaftFract, m_initSntSntInRaftFract);
	DDX_Text(pDX, IDC_EDIT_initSntSntSnt_InRaftFract, m_initSntSntSnt_InRaftFract);
	DDX_Text(pDX, IDC_EDIT_initSntSntNum, m_initSntSnt_num);
	DDX_Text(pDX, IDC_EDIT_initSntSntSntNum, m_m_initSntSntSnt_num);
	DDX_Text(pDX, IDC_EDIT_initAlphaInRaftFract, m_initAlphaInRaftFract);
	DDX_Text(pDX, IDC_EDIT_initAlphaNum, m_initAlphaNum);
	DDX_Text(pDX, IDC_EDIT_Ptransloc_Alpha, m_Ptransloc_Alpha);
	DDX_Text(pDX, IDC_EDIT_Ptransloc_NSF, m_Ptransloc_NSF);
	//}}AFX_DATA_MAP
}


void COrders::SetView(CSurfaceView * pview)
{
	m_pCSurfaceView = pview;
}


BEGIN_MESSAGE_MAP(COrders, CDialog)
	//{{AFX_MSG_MAP(COrders)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrders message handlers

BOOL COrders::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_initStxInRaftFract = CGeneral::InitInRaftFractionSnt;
	m_initSntSntInRaftFract = CGeneral::InitInRaftFractionSntSnt;
	m_initSntSntSnt_InRaftFract = CGeneral::InitInRaftFractionSntSntSnt;
	m_initSnap25InRaftFract = CGeneral::InitInRaftFractionSNAP25;
	m_initNSFInRaftFract = CGeneral::InitInRaftFractionNSF;
	m_initAlphaInRaftFract = CGeneral::InitInRaftFractionAlpha;
	m_initVampInRaftFract = CGeneral::infectivityThreshould;
	m_initSntSnap25inRaftFraction = CGeneral::InitInRaftFractionSynSnap25;
	m_initSntSnap25VampinRaftFraction = CGeneral::InitInRaftFractionSynSnap25Vamp;
	m_initSnt_Snap25VampAlphaInRaftFract = CGeneral::InitInRaftFractionSynSnap25VampAlpha;

	m_SNAP25Pin_raft = CGeneral::Pin_SNAP25;
	m_SNAP25Pour_raft = CGeneral::Pout_SNAP25;
	m_StxPin_raft = CGeneral::Pin_Stx;
	m_StxPout_raft = CGeneral::Pout_Stx;
	m_Vamp_Pin_raft = CGeneral::Pin_Vamp;
	m_Vamp_Pout_raft = CGeneral::Pout_Vamp;
	m_Snt_SNAP25_Pin_raft = CGeneral::Pin_SynSnap25;
	m_SntSnt_Pin_raft = CGeneral::Pin_SynSyn;
	m_SntSnt_Pout_raft = CGeneral::Pout_SynSyn;
	m_SntSntSnt_Pin_raft = CGeneral::Pin_SynSynSyn;
	m_SntSntSnt_Pout_raft = CGeneral::Pout_SynSynSyn;
	m_Snt_SNAP25_Vamp_Pin_raft = CGeneral::Pin_SynSnap25Vamp;
	m_Snt_SNAP25_Pout_raft = CGeneral::Pout_SynSnap25;
	m_Snt_SNAP25_Vamp_Pout_raft = CGeneral::Pout_SynSnap25Vamp;
	m_SntSNAP_VampAlpha_Pin_raft = CGeneral::Pin_SynSnap25VampAlpha;
	m_SntSNAP_VampAlpha_Pout_raft = CGeneral::Pout_SynSnap25VampAlpha;
	
	m_initStxNumber = CGeneral::initSntNumber;
	m_initSntSnt_num = CGeneral::initSntSntNumber;
	m_m_initSntSntSnt_num = CGeneral::initSntSntSntNumber;
	m_initNSFnumber = CGeneral::initNSFNumber;
	m_initAlphaNum = CGeneral::initAlphaNumber;
	m_initSNAP25Number = CGeneral::initSNAP25Number;
	m_initVampNumber = CGeneral::initVampNumber;
	m_initSntSnap25Number = CGeneral::initSynSnap25;
	m_initSntSnap25VampNumber = CGeneral::initSynSnap25Vamp;
	m_initSnt_Snap25VampAlphaNum = CGeneral::initSynSnap25VampAlpha;
	
	m_Stx_D = CGeneral::D_Stx;
	m_Snap25_D = CGeneral::D_SNAP25;
	m_D_ESF = CGeneral::D_NSF;
	m_Vamp_D = CGeneral::D_Vamp;
	m_D_Alpha = CGeneral::D_ALPHA;

	m_LifeTime_Alpha = CGeneral::t_ALPHA_up;
	m_LifeTime_NSF = CGeneral::t_NSF_up;
	m_Ptransloc_Alpha = CGeneral::Ptransloc_Alpha;
	m_Ptransloc_NSF = CGeneral::Ptransloc_NSF;
	m_NSFtoRemoveCompl = CGeneral::is_delete_complexes;

	m_Snt_D_inRaft = CGeneral::D_Stx_inRaft;
	m_Snap25_D_inRaft = CGeneral::D_SNAP25_inRaft;
	m_Vamp_D_inRaft = CGeneral::D_Vamp_inRaft;
	
	m_Ppob_Syn_Bind_SNAP25 = CGeneral::Ppob_Syn_Bind_SNAP25;
	m_Ppob_SynSNAP25_BindVamp = CGeneral::Ppob_SynSNAP25_BindVamp;
	m_Ppob_SynSNAPVamp_BindAlpha = CGeneral::Ppob_SynSNAP25Vamp_BindAlpha;
	m_Ppob_Snt_bind_Snt = CGeneral::Ppob_Syn_Bind_Syn;
	m_Ppob_SntSnt_bind_Snt = CGeneral::Ppob_SynSyn_Bind_Syn;
	
	m_Ppob_SntSNAP25VampAlpha_Dis = CGeneral::Ppob_SynSNAP25VampAlpha_Dissociation;
	m_Ppob_SynSNAP25Vamp_Dis = CGeneral::Ppob_SynSNAP25Vamp_Dissociation;
	m_Ppob_SynSNAP25_Dis = CGeneral::Ppob_SynSNAP25_Dissociation;
	m_Ppob_SntSnt_Dis = CGeneral::Ppob_SynSyn_Dissociation;
	m_Ppob_SntSntSnt_Dis = CGeneral::Ppob_SynSynSyn_Dissociation;

	m_P_NSF_on_Snt_Snap = CGeneral::Ppob_NSF_diss_SynSNAP25VampAlpha;

	m_RaftNumber = CGeneral::RAFT_NUMBER;
	m_DifCoef = CGeneral::RAFT_DIFFUSION_COEFICIENT;	
	m_RAFT_PROBABILITY_TO_MERGE = CGeneral::RAFT_PROBABILITY_TO_MERGE;
	m_StepsNumber = CGeneral::TIME_STEP_NUMBER;
	m_MeanRaftSize = CGeneral::MEAN_RAFT_SIZE;

	CDialog::UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COrders::OnOk() 
{
	if(	CGeneral::START_SIM == true)
	{
		AfxMessageBox("In order the change to take effect the simulation should be stopped (press Stop at the Control tab)");
		return;
	}

	CDialog::UpdateData(true);

	CGeneral::InitInRaftFractionSnt = m_initStxInRaftFract;
	CGeneral::InitInRaftFractionSntSnt = m_initSntSntInRaftFract;
	CGeneral::InitInRaftFractionSntSntSnt = m_initSntSntSnt_InRaftFract;
	CGeneral::InitInRaftFractionSNAP25 = m_initSnap25InRaftFract;
	CGeneral::InitInRaftFractionNSF = m_initNSFInRaftFract;
	CGeneral::InitInRaftFractionAlpha = m_initAlphaInRaftFract;
	CGeneral::infectivityThreshould = m_initVampInRaftFract;
	CGeneral::InitInRaftFractionSynSnap25 = m_initSntSnap25inRaftFraction;
	CGeneral::InitInRaftFractionSynSnap25Vamp = m_initSntSnap25VampinRaftFraction;
	CGeneral::InitInRaftFractionSynSnap25VampAlpha = m_initSnt_Snap25VampAlphaInRaftFract;

	CGeneral::Pout_SNAP25 = m_SNAP25Pour_raft;
	CGeneral::Pin_SNAP25 = m_SNAP25Pin_raft;
	CGeneral::Pout_Stx = m_StxPout_raft;
	CGeneral::Pin_Stx = m_StxPin_raft;
	CGeneral::Pout_Vamp = m_Vamp_Pout_raft;
	CGeneral::Pin_Vamp = m_Vamp_Pin_raft;
	CGeneral::Pin_SynSnap25 = m_Snt_SNAP25_Pin_raft;
	CGeneral::Pin_SynSyn = m_SntSnt_Pin_raft;
	CGeneral::Pout_SynSyn = m_SntSnt_Pout_raft;
	CGeneral::Pin_SynSynSyn = m_SntSntSnt_Pin_raft;
	CGeneral::Pout_SynSynSyn = m_SntSntSnt_Pout_raft;
	CGeneral::Pin_SynSnap25Vamp = m_Snt_SNAP25_Vamp_Pin_raft;
	CGeneral::Pout_SynSnap25 = m_Snt_SNAP25_Pout_raft;
	CGeneral::Pout_SynSnap25Vamp = m_Snt_SNAP25_Vamp_Pout_raft;
	CGeneral::Pin_SynSnap25VampAlpha = m_SntSNAP_VampAlpha_Pin_raft;
	CGeneral::Pout_SynSnap25VampAlpha = m_SntSNAP_VampAlpha_Pout_raft;

	CGeneral::initSntNumber = m_initStxNumber;
	CGeneral::initSntSntNumber = m_initSntSnt_num;
	CGeneral::initSntSntSntNumber = m_m_initSntSntSnt_num;
	CGeneral::initNSFNumber = m_initNSFnumber;
	CGeneral::initAlphaNumber = m_initAlphaNum;
	CGeneral::initSNAP25Number = m_initSNAP25Number;
	CGeneral::initVampNumber = m_initVampNumber;
	CGeneral::initSynSnap25 = m_initSntSnap25Number;
	CGeneral::initSynSnap25Vamp = m_initSntSnap25VampNumber;
	CGeneral::initSynSnap25VampAlpha = m_initSnt_Snap25VampAlphaNum;

	CGeneral::MEAN_RAFT_SIZE = m_MeanRaftSize;
	CGeneral::RAFT_NUMBER = m_RaftNumber;
	CGeneral::RAFT_DIFFUSION_COEFICIENT = m_DifCoef;	
	CGeneral::RAFT_PROBABILITY_TO_MERGE = m_RAFT_PROBABILITY_TO_MERGE;
	CGeneral::TIME_STEP_NUMBER = m_StepsNumber;

	CGeneral::Ppob_Syn_Bind_SNAP25 = m_Ppob_Syn_Bind_SNAP25;
	CGeneral::Ppob_SynSNAP25_BindVamp = m_Ppob_SynSNAP25_BindVamp;
	CGeneral::Ppob_SynSNAP25Vamp_BindAlpha = m_Ppob_SynSNAPVamp_BindAlpha;
	CGeneral::Ppob_Syn_Bind_Syn = m_Ppob_Snt_bind_Snt;
	CGeneral::Ppob_SynSyn_Bind_Syn = m_Ppob_SntSnt_bind_Snt;

	CGeneral::Ppob_SynSNAP25_Dissociation = m_Ppob_SynSNAP25_Dis;
	CGeneral::Ppob_SynSNAP25Vamp_Dissociation = m_Ppob_SynSNAP25Vamp_Dis;
	CGeneral::Ppob_SynSNAP25VampAlpha_Dissociation = m_Ppob_SntSNAP25VampAlpha_Dis;

	CGeneral::Ppob_SynSyn_Dissociation = m_Ppob_SntSnt_Dis;
	CGeneral::Ppob_SynSynSyn_Dissociation = m_Ppob_SntSntSnt_Dis;
	CGeneral::Ppob_NSF_diss_SynSNAP25VampAlpha = m_P_NSF_on_Snt_Snap;

	CGeneral::D_Stx = m_Stx_D;
	CGeneral::D_SNAP25 = m_Snap25_D;
	CGeneral::D_NSF = m_D_ESF;
	CGeneral::D_Vamp = m_Vamp_D;

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	














































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































CGeneral::is_delete_complexes = (bool) m_NSFtoRemoveCompl;

	CGeneral::t_ALPHA_up = m_LifeTime_Alpha;
	CGeneral::t_NSF_up = m_LifeTime_NSF;
	CGeneral::Ptransloc_Alpha = m_Ptransloc_Alpha;
	CGeneral::Ptransloc_NSF = m_Ptransloc_NSF;

	CGeneral::D_Stx_inRaft = m_Snt_D_inRaft;
	CGeneral::D_SNAP25_inRaft = m_Snap25_D_inRaft;
	CGeneral::D_Vamp_inRaft = m_Vamp_D_inRaft;

}

void COrders::OnCancel() 
{
	m_initStxInRaftFract = CGeneral::InitInRaftFractionSnt;
	m_initSntSntInRaftFract = CGeneral::InitInRaftFractionSntSnt;
	m_initSntSntSnt_InRaftFract = CGeneral::InitInRaftFractionSntSntSnt;
	m_initSnap25InRaftFract = CGeneral::InitInRaftFractionSNAP25;
	m_initNSFInRaftFract = CGeneral::InitInRaftFractionNSF;
	m_initAlphaInRaftFract = CGeneral::InitInRaftFractionAlpha;
	m_initVampInRaftFract = CGeneral::InitInRaftFractionVamp;
	m_initSntSnap25inRaftFraction = CGeneral::InitInRaftFractionSynSnap25;
	m_initSntSnap25VampinRaftFraction = CGeneral::InitInRaftFractionSynSnap25Vamp;
	m_initSnt_Snap25VampAlphaInRaftFract = CGeneral::InitInRaftFractionSynSnap25VampAlpha;

	m_SNAP25Pin_raft = CGeneral::Pin_SNAP25;
	m_SNAP25Pour_raft = CGeneral::Pout_SNAP25;
	m_StxPin_raft = CGeneral::Pin_Stx;
	m_StxPout_raft = CGeneral::Pout_Stx;
	m_Vamp_Pin_raft = CGeneral::Pin_Vamp;
	m_Vamp_Pout_raft = CGeneral::Pout_Vamp;
	m_Snt_SNAP25_Pin_raft = CGeneral::Pin_SynSnap25;
	m_SntSnt_Pin_raft = CGeneral::Pin_SynSyn;
	m_SntSnt_Pout_raft = CGeneral::Pout_SynSyn;
	m_SntSntSnt_Pin_raft = CGeneral::Pin_SynSynSyn;
	m_SntSntSnt_Pout_raft = CGeneral::Pout_SynSynSyn;
	m_Snt_SNAP25_Vamp_Pin_raft = CGeneral::Pin_SynSnap25Vamp;
	m_Snt_SNAP25_Pout_raft = CGeneral::Pout_SynSnap25;
	m_Snt_SNAP25_Vamp_Pout_raft = CGeneral::Pout_SynSnap25Vamp;
	m_SntSNAP_VampAlpha_Pin_raft = CGeneral::Pin_SynSnap25VampAlpha;
	m_SntSNAP_VampAlpha_Pout_raft = CGeneral::Pout_SynSnap25VampAlpha;
	
	m_initStxNumber = CGeneral::initSntNumber;
	m_initSntSnt_num = CGeneral::initSntSntNumber;
	m_m_initSntSntSnt_num = CGeneral::initSntSntSntNumber;
	m_initNSFnumber = CGeneral::initNSFNumber;
	m_initAlphaNum = CGeneral::initAlphaNumber;
	m_initSNAP25Number = CGeneral::initSNAP25Number;
	m_initVampNumber = CGeneral::initVampNumber;
	m_initSntSnap25Number = CGeneral::initSynSnap25;
	m_initSntSnap25VampNumber = CGeneral::initSynSnap25Vamp;
	m_initSnt_Snap25VampAlphaNum = CGeneral::initSynSnap25VampAlpha;
	
	m_Stx_D = CGeneral::D_Stx;
	m_Snap25_D = CGeneral::D_SNAP25;
	m_D_ESF = CGeneral::D_NSF;
	m_Vamp_D = CGeneral::D_Vamp;
	m_D_Alpha = CGeneral::D_ALPHA;

	m_LifeTime_Alpha = CGeneral::t_ALPHA_up;
	m_LifeTime_NSF = CGeneral::t_NSF_up;
	m_Ptransloc_Alpha = CGeneral::Ptransloc_Alpha;
	m_Ptransloc_NSF = CGeneral::Ptransloc_NSF;
	m_NSFtoRemoveCompl = CGeneral::is_delete_complexes;

	m_Snt_D_inRaft = CGeneral::D_Stx_inRaft;
	m_Snap25_D_inRaft = CGeneral::D_SNAP25_inRaft;
	m_Vamp_D_inRaft = CGeneral::D_Vamp_inRaft;
	
	m_Ppob_Syn_Bind_SNAP25 = CGeneral::Ppob_Syn_Bind_SNAP25;
	m_Ppob_SynSNAP25_BindVamp = CGeneral::Ppob_SynSNAP25_BindVamp;
	m_Ppob_SynSNAPVamp_BindAlpha = CGeneral::Ppob_SynSNAP25Vamp_BindAlpha;
	m_Ppob_Snt_bind_Snt = CGeneral::Ppob_Syn_Bind_Syn;
	m_Ppob_SntSnt_bind_Snt = CGeneral::Ppob_SynSyn_Bind_Syn;
	
	m_Ppob_SntSNAP25VampAlpha_Dis = CGeneral::Ppob_SynSNAP25VampAlpha_Dissociation;
	m_Ppob_SynSNAP25Vamp_Dis = CGeneral::Ppob_SynSNAP25Vamp_Dissociation;
	m_Ppob_SynSNAP25_Dis = CGeneral::Ppob_SynSNAP25_Dissociation;
	m_Ppob_SntSnt_Dis = CGeneral::Ppob_SynSyn_Dissociation;
	m_Ppob_SntSntSnt_Dis = CGeneral::Ppob_SynSynSyn_Dissociation;

	m_P_NSF_on_Snt_Snap = CGeneral::Ppob_NSF_diss_SynSNAP25VampAlpha;

	m_RaftNumber = CGeneral::RAFT_NUMBER;
	m_DifCoef = CGeneral::RAFT_DIFFUSION_COEFICIENT;	
	m_RAFT_PROBABILITY_TO_MERGE = CGeneral::RAFT_PROBABILITY_TO_MERGE;
	m_StepsNumber = CGeneral::TIME_STEP_NUMBER;
	m_MeanRaftSize = CGeneral::MEAN_RAFT_SIZE;

	CDialog::UpdateData(false);
}
