// Option.cpp : implementation file
//

#include "stdafx.h"
#include "surface.h"
#include "SurfaceDoc.h"
#include "SurfaceView.h"
#include "Option.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//int minZoom = 1;

/////////////////////////////////////////////////////////////////////////////
// COption dialog


COption::COption(CWnd* pParent /*=NULL*/)
	: CDialog(COption::IDD, pParent)
{
	//{{AFX_DATA_INIT(COption)
	m_RecNum = 0;
	m_Step = 0;
	m_StepNum = 0;
	m_Cur_Ag_Number = 0;
	m_TimerInitialisator = 0;
	m_Cur_Raft_Number = 0;
	m_StepBy = FALSE;
	m_Check_Draw_Indexes = FALSE;
	m_Win_Update_Timer = 0;
	m_Simulation_Duration = 0;
	m_CHEK_Draw_Rec = FALSE;
	m_Check_Draw_SM_names = FALSE;
	m_Check_Draw_SM = FALSE;
	m_CHEK_Draw_Ag = FALSE;
	m_CHEK_Draw_Ag_Indexes = FALSE;
	m_CHEK_Draw_SM_Ind = FALSE;
	m_CHEK_Draw_Raft = FALSE;
	m_CHEK_Draw_Raft_Ind = FALSE;
	m_CHEK_Draw_Names = FALSE;
	//}}AFX_DATA_INIT
}


void COption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COption)
	DDX_Control(pDX, IDC_COMBO_ZOOM, m_ComboZoom);
	DDX_Control(pDX, IDC_NEXT_STEP, m_StepBtn);
	DDX_Text(pDX, IDC_EDIT_REC_NUM, m_RecNum);
	DDX_Text(pDX, IDC_EDITD_STEP, m_Step);
	DDX_Text(pDX, IDC_EDITD_STEPS, m_StepNum);
	DDX_Text(pDX, IDC_EDIT_Cur_Ag_Number, m_Cur_Ag_Number);
	DDX_Text(pDX, IDC_EDIT_TimerInitialisator, m_TimerInitialisator);
	DDX_Text(pDX, IDC_EDIT_CurRaftNumber, m_Cur_Raft_Number);
	DDX_Check(pDX, IDC_CHECK_STEP, m_StepBy);
	DDX_Check(pDX, IDC_CHEK_Draw_Indexes, m_Check_Draw_Indexes);
	DDX_Text(pDX, IDC_EDIT_Win_Update_Timer, m_Win_Update_Timer);
	DDV_MinMaxInt(pDX, m_Win_Update_Timer, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_Simulation_Duration, m_Simulation_Duration);
	DDX_Check(pDX, IDC_CHEK_Draw_Rec, m_CHEK_Draw_Rec);
	DDX_Check(pDX, IDC_CHEK_Draw_SM_names, m_Check_Draw_SM_names);
	DDX_Check(pDX, IDC_CHEK_Draw_SM, m_Check_Draw_SM);
	DDX_Check(pDX, IDC_CHEK_Draw_Ag, m_CHEK_Draw_Ag);
	DDX_Check(pDX, IDC_CHEK_Draw_Ag_Indexes, m_CHEK_Draw_Ag_Indexes);
	DDX_Check(pDX, IDC_CHEK_Draw_SM_Ind, m_CHEK_Draw_SM_Ind);
	DDX_Check(pDX, IDC_CHEK_Draw_Raft, m_CHEK_Draw_Raft);
	DDX_Check(pDX, IDC_CHEK_Draw_Raft_Ind, m_CHEK_Draw_Raft_Ind);
	DDX_Check(pDX, IDC_CHEK_Draw_Names, m_CHEK_Draw_Names);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COption, CDialog)
	//{{AFX_MSG_MAP(COption)
	ON_BN_CLICKED(IDC_BEGIN, OnBeginSim)
	ON_BN_CLICKED(IDC_CANCEL, OnCancelSim)
	ON_BN_CLICKED(IDC_DRAW, OnDrawBtn)
	ON_BN_CLICKED(IDC_CHECK_STEP, OnCheckStep)
	ON_BN_CLICKED(IDC_NEXT_STEP, OnNextStep)
	ON_CBN_SELENDOK(IDC_COMBO_ZOOM, OnSelendokComboZoom)
	ON_EN_UPDATE(IDC_EDIT_ZOOM, OnUpdateEditZoom)
	ON_BN_CLICKED(IDC_CHEK_Draw_Indexes, OnCHEKDrawIndexes)
	ON_EN_UPDATE(IDC_EDIT_Win_Update_Timer, OnUpdateEDITWinUpdateTimer)
	ON_EN_UPDATE(IDC_EDIT_TimerInitialisator, OnUpdateEDITTimerInitialisator)
	ON_BN_CLICKED(IDC_CHEK_Draw_Rec, OnCHEKDrawRec)
	ON_BN_CLICKED(IDC_CHEK_Draw_SM, OnCHEKDrawSM)
	ON_BN_CLICKED(IDC_CHEK_Draw_SM_names, OnCHEKDrawSMnames)
	ON_BN_CLICKED(IDC_CHEK_Draw_Ag, OnCHEKDrawAg)
	ON_BN_CLICKED(IDC_CHEK_Draw_Ag_Indexes, OnCHEKDrawAgIndexes)
	ON_BN_CLICKED(IDC_CHEK_Draw_SM_Ind, OnCHEKDrawSMInd)
	ON_BN_CLICKED(IDC_CHEK_Draw_Raft, OnCHEKDrawRaft)
	ON_BN_CLICKED(IDC_CHEK_Draw_Raft_Ind, OnCHEKDrawRaftInd)
	ON_BN_CLICKED(IDC_CHEK_Draw_Names, OnCHEKDrawNames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COption message handlers

BOOL COption::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_CANCEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BEGIN)->EnableWindow(FALSE);

	m_StepNum = CGeneral::TIME_STEP_NUMBER;
	m_Step = CGeneral::step;
	m_TimerInitialisator = CGeneral::TimerInitialisator;
	m_Win_Update_Timer = CGeneral::UpdateWindowVariable;
	m_TimerInitialisator = CGeneral::TimerInitialisator;
	m_Check_Draw_Indexes = CGeneral::DrawRecIndexes;
	m_CHEK_Draw_Rec = CGeneral::DrawReceptors;
	m_Check_Draw_SM_names = CGeneral::DrawSigMolNames;
	m_CHEK_Draw_Names = CGeneral::DrawRecNames;
	m_Check_Draw_SM = CGeneral::DrawSigMol;
	m_CHEK_Draw_SM_Ind = CGeneral::DrawSigMolInd;
	m_CHEK_Draw_Raft = CGeneral::DrawRafts;
	m_CHEK_Draw_Raft_Ind = CGeneral::DrawRaftIndexes;
	m_CHEK_Draw_Ag = CGeneral::DrawAgs;
	m_CHEK_Draw_Ag_Indexes = CGeneral::DrawAgIndexes;
	m_StepBy = m_pCSurfaceView->m_StepBy;
	m_ComboZoom.SetCurSel(m_pCSurfaceView->m_PartGridNum);
	m_ComboZoom.EnableWindow(m_pCSurfaceView->m_PartGrid > 1);
	m_StepBtn.EnableWindow(m_StepBy);
	CString st;
	st.Format("%d x %d",GRID_SIZE,GRID_SIZE);
	GetDlgItem(IDC_STATIC_GRID_SZ)->SetWindowText(st);
	CDialog::UpdateData(false);

	SetDlgItemInt(IDC_EDIT_TimerInitialisator,CGeneral::TimerInitialisator);
	SetDlgItemInt(IDC_EDIT_Win_Update_Timer,CGeneral::UpdateWindowVariable);
	SetDlgItemInt(IDC_EDIT_ZOOM,m_pCSurfaceView->m_PartGrid);

	//SetWindowPos(&wndTopMost, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
	//CenterWindow();	
	m_pCSurfaceView->m_OptionDlg = this;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL COption::Create( CSurfaceView * pParent) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pCSurfaceView = pParent;
	return CDialog::Create(IDD, pParent);
}

void COption::SetZoom(int prt, int size, int begin)
{
	CString tmpString;
	if(GetDlgItemText(IDC_EDIT_ZOOM, tmpString) == 0)
		return;
	int zoom = atoi(tmpString);
	if(zoom != prt || !begin)
	{
		zoom = prt;
		//m_pCSurfaceView->minZoom = prt;
		FillComboZoom(prt) ;
		SetDlgItemInt(IDC_EDIT_ZOOM,prt);
	}
	m_ComboZoom.EnableWindow(zoom > 1);
	CString st;
	st.Format("%d x %d",size,size);
	GetDlgItem(IDC_STATIC_GRID_SZ2)->SetWindowText(st);
	//CDialog::UpdateData(false);
}

void COption::UpdateData()
{
	if( (CGeneral::step % 1) == 0 )
	{
		m_RecNum = CGeneral::Recepter_Number;
		m_StepNum = CGeneral::TIME_STEP_NUMBER;
		m_Step = CGeneral::step;
		m_Cur_Raft_Number = CGeneral::CurRaftNum;
		m_Simulation_Duration = CGeneral::Simulation_Duration;
		SetDlgItemInt(IDC_EDIT_REC_NUM,m_RecNum);
		SetDlgItemInt(IDC_EDITD_STEPS,m_StepNum);
		SetDlgItemInt(IDC_EDITD_STEP,m_Step);
		SetDlgItemInt(IDC_EDIT_CurRaftNumber,m_Cur_Raft_Number);
		SetDlgItemInt(IDC_EDIT_Cur_Ag_Number,m_Cur_Ag_Number);
		SetDlgItemInt(IDC_EDIT_Simulation_Duration,m_Simulation_Duration);
		//CDialog::UpdateData(false);
	} // if	     

}


void COption::OnBeginSim() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_CANCEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BEGIN)->EnableWindow(FALSE);
	CGeneral::START_SIM = true;
	SetDlgItemInt(IDC_EDIT_TimerInitialisator,CGeneral::TimerInitialisator);
	SetDlgItemInt(IDC_EDIT_Win_Update_Timer,CGeneral::UpdateWindowVariable);
	SetDlgItemInt(IDC_EDIT_ZOOM,m_pCSurfaceView->m_PartGrid);
	UpdateData();
}


void COption::OnCancelSim() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BEGIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CANCEL)->EnableWindow(FALSE);
	CGeneral::START_SIM = false;	
}


void COption::OnDrawBtn() 
{
	// TODO: Add your control notification handler code here
	m_pCSurfaceView->m_stopDraw = !m_pCSurfaceView->m_stopDraw;	
}

void COption::OnCheckStep() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	m_pCSurfaceView->m_StepBy = m_StepBy;
	m_StepBtn.EnableWindow(m_StepBy);
}

void COption::OnNextStep() 
{
	// TODO: Add your control notification handler code here
		m_pCSurfaceView->m_Next = true;
}

void COption::OnSelendokComboZoom() 
{
	// TODO: Add your control notification handler code here
		m_pCSurfaceView->m_PartGridNum = m_ComboZoom.GetCurSel() +1;
}

void COption::OnUpdateEditZoom() 
{
	CString tmpString;
	if(GetDlgItemText(IDC_EDIT_ZOOM, tmpString) == 0)
	{
		//AfxMessageBox("Enter value!");
		return;
	}
	int zoom = atoi(tmpString);
	if(m_pCSurfaceView->minZoom > zoom)
	{
		AfxMessageBox("Illegal value!\nPlease enlarge your screen resolution!");
		SetDlgItemInt(IDC_EDIT_ZOOM,m_pCSurfaceView->minZoom);
		return;
	}
	m_pCSurfaceView->m_PartGrid = zoom;
	FillComboZoom(zoom) ;
	
}

void COption::FillComboZoom(int zoom) 
{
	m_ComboZoom.ResetContent();
	m_ComboZoom.EnableWindow(zoom > 1);
	char buf[5];
	for (int i=0; i<zoom * zoom; i++)
	{
		m_ComboZoom.AddString(itoa(i+1,buf,10));
	}
	m_ComboZoom.SetCurSel(0);
	OnSelendokComboZoom();
}

void COption::OnUpdateEDITWinUpdateTimer() 
{
	CString tmpString;
	if(GetDlgItemText(IDC_EDIT_Win_Update_Timer, tmpString) == 0)
	{
		//AfxMessageBox("Enter value!");
		return;
	}
	CGeneral::UpdateWindowVariable = atoi(tmpString);

}

void COption::OnUpdateEDITTimerInitialisator() 
{
	CString tmpString;
	if(GetDlgItemText(IDC_EDIT_TimerInitialisator, tmpString) == 0)
	{
		//AfxMessageBox("Enter value!");
		return;
	}
	CGeneral::TimerInitialisator = atoi(tmpString);

	//m_pCSurfaceView->SetTimer(1, CGeneral::TimerInitialisator, NULL);
	m_pCSurfaceView->SetTimer(1, 0, NULL);
}

void COption::OnCHEKDrawIndexes() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_Check_Draw_Indexes)
	{
		CGeneral::DrawRecIndexes = true;
	}
	else
	{
		CGeneral::DrawRecIndexes = false;
	}
}

void COption::OnCHEKDrawRec() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_CHEK_Draw_Rec)
	{
		CGeneral::DrawReceptors = true;
	}
	else
	{
		CGeneral::DrawReceptors = false;
	}
	
}

void COption::OnCHEKDrawSM() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_Check_Draw_SM)
	{
		CGeneral::DrawSigMol = true;
	}
	else
	{
		CGeneral::DrawSigMol = false;
	}
	
}

void COption::OnCHEKDrawSMnames() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_Check_Draw_SM_names)
	{
		CGeneral::DrawSigMolNames = true;
	}
	else
	{
		CGeneral::DrawSigMolNames = false;
	}
	
}

void COption::OnCHEKDrawAg() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_CHEK_Draw_Ag)
	{
		CGeneral::DrawAgs = true;
	}
	else
	{
		CGeneral::DrawAgs = false;
	}
	
}

void COption::OnCHEKDrawAgIndexes() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_CHEK_Draw_Ag_Indexes)
	{
		CGeneral::DrawAgIndexes = true;
	}
	else
	{
		CGeneral::DrawAgIndexes = false;
	}
	
}

void COption::OnCHEKDrawSMInd() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_CHEK_Draw_SM_Ind)
	{
		CGeneral::DrawSigMolInd = true;
	}
	else
	{
		CGeneral::DrawSigMolInd = false;
	}
	
}

void COption::OnCHEKDrawRaft() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_CHEK_Draw_Raft)
	{
		CGeneral::DrawRafts = true;
	}
	else
	{
		CGeneral::DrawRafts = false;
	}
	
}

void COption::OnCHEKDrawRaftInd() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_CHEK_Draw_Raft_Ind)
	{
		CGeneral::DrawRaftIndexes = true;
	}
	else
	{
		CGeneral::DrawRaftIndexes = false;
	}
	
}

void COption::SetView(CSurfaceView * pview)
{
	m_pCSurfaceView = pview;
}

void COption::OnCHEKDrawNames() 
{
	// TODO: Add your control notification handler code here
	CDialog::UpdateData(true);
	if(m_CHEK_Draw_Names)
	{
		CGeneral::DrawRecNames = true;
	}
	else
	{
		CGeneral::DrawRecNames = false;
	}
}
