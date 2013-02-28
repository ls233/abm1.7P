// General.cpp: implementation of the CGeneral class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Surface.h"
#include "General.h"
#include "Grid.h"
#include "Receptor.h"
#include "Cell.h"
#include "SigMol.h"
#include "mersenne.cpp"                // members of class TRandomMersenne
#include <cmath>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#define message(x) printf(x"\n\n")
#endif

TRandomMersenne  rg(0);

//int CGeneral::RecMSDResults[RECEPTOR_NUMBER];
int	CGeneral::RecInRaft = 0;
int	CGeneral::Glob_raft_ID;
CGrid CGeneral::grid;
std::vector<CReceptor> CGeneral::RArray;
std::vector<CReceptor> CGeneral::tmpRArray;
std::vector<CCell> CGeneral::CellArray;
std::vector<CSigMol> CGeneral::SMArray;
IndexStack  CGeneral::delRecStack;
IndexStack  CGeneral::delRaftStack;
IndexStack  CGeneral::delSMStack;
SMprofileVector  CGeneral::SMprofileVec;
RprofileVector  CGeneral::RprofileVec;

std::vector<CPoint> CGeneral::MSDResultsArray;
std::vector<CPoint> CGeneral::Results_of_R_in_out_ratio_Array;
std::vector<CPoint> CGeneral::Results_of_R_SM_complex_in_out_ratio_Array;
ResultsVector CGeneral::R_SM_interaction_results_Array;
ResultsVector CGeneral::Protein_concentration_results_Array;
doublesVec CGeneral::R_SM_binding_durations_Vec;
std::queue<SM_Type> CGeneral::EndocytosedSMQueue;
ofstream CGeneral::out_singleCells_concentrations("Out_singleCells_concentrations.txt");
ofstream CGeneral::out_TS_concentrations("Out_TS_concentrations.txt");
ofstream CGeneral::out_singleCells_rates("Out_singleCells_rates.txt");
ofstream CGeneral::out_TS_rates("Out_TS_rates.txt");

ofstream CGeneral::out("Out.txt");
ofstream CGeneral::gillaspieLog("gillaspieLog.txt");

//int CGeneral::TIME_STEP_NUMBER = 26250000 ;
bool CGeneral::debug_version = false; //false;
bool CGeneral::stopProducingIFN_flag = false;
bool CGeneral::START_SIM = true; //false;
int CGeneral::step = 0;
int	CGeneral::UpdateWindowVariable = 1;
int	CGeneral::TimerInitialisator = 1;

bool CGeneral::DrawRecIndexes = false;
bool CGeneral::DrawReceptors = false;
bool CGeneral::DrawSigMol = true;
bool CGeneral::DrawSigMolNames = false;
bool CGeneral::DrawRecNames = false;
bool CGeneral::DrawSigMolInd = false;
bool CGeneral::DrawRaftIndexes = false;
bool CGeneral::DrawRafts = true;
bool CGeneral::DrawAgs = false;
bool CGeneral::DrawAgIndexes = false;

bool CGeneral::is_draw_finished = true;
bool CGeneral::is_simul_finished = true;
bool CGeneral::is_draw_rec_path = false;

bool CGeneral::is_delete_complexes = true;

int CGeneral::Simulation_Duration = 0;

int CGeneral::Recepter_Number = RECEPTOR_NUMBER;

double	CGeneral::RAFT_SURFACE_COVERAGE_PERCENT = 1;//1;
double	CGeneral::RAFT_DIFFUSION_COEFICIENT = 0;
double	CGeneral::IFNb_D = 0.5/3;//1
//double	CGeneral::IFNb_D = pow((TIME_STEP_LENGHT/UPPER_LIMIT_TIME_STEP_LENGHT),0.5) *1;//1
double	CGeneral::UPPER_LIMIT_TIME_STEP_LENGHT = 9;//1
int	CGeneral::TIME_STEP_LENGHT = 9;//1
//asserte(CGeneral::UPPER_LIMIT_TIME_STEP_LENGHT>CGeneral::TIME_STEP_LENGHT);
int	CGeneral::SIMULATION_DURATION_IN_HOURS = 11;//1
double	CGeneral::RAFT_DIFFUSION_COEFICIENT_OF_ACTIVE_RAFT = 0.0;//1
//int CGeneral::RAFT_NUMBER = 2*GRID_SIZE*GRID_SIZE/100/100;
//int CGeneral::RAFT_NUMBER = 1;
int CGeneral::RAFT_NUMBER = 20; 
int CGeneral::MEAN_RAFT_SIZE = 90; 
int	CGeneral::CurRaftNum = 0;
double	CGeneral::RAFT_PROBABILITY_TO_MERGE = 0.0; // 

bool CGeneral::plusAB= false;//false;
bool CGeneral::TWmodel= true;//false;

double	CGeneral::RIGI_prot_maxLevel = 400.1; // 
double	CGeneral::IFN_prot_maxLevel = 400; // 
double	CGeneral::RIGI_rna_maxLevel = 100.1; // 
double	CGeneral::IFN_rna_maxLevel = 100; // 
double	CGeneral::max_transcriptionRateC = 0.05;//*TIME_STEP_LENGHT; // 
double	CGeneral::max_translationRateC = 0.002;//*TIME_STEP_LENGHT; // 
double	CGeneral::typical_prot_degradationRateC = 0.0001;//*TIME_STEP_LENGHT; // 0.002
double	CGeneral::typical_rna_degradationRateC = 0.0001;//*TIME_STEP_LENGHT; 
double	CGeneral::IFN_rna_activation_hillCoef = (TWmodel)?1.5:2;
double	CGeneral::DDX58_rna_activation_hillCoef = (TWmodel)?3:2;
int	CGeneral::IFN_protein_secretion_hillCoef = 1.0; //
 
double	CGeneral::infectivityThreshould = .6; // 
double	CGeneral::Ppob_TypeR_Bind_IFNb = (plusAB)?1.25e-7*TIME_STEP_LENGHT*100*1 : 1.25e-7*TIME_STEP_LENGHT*100;
double	CGeneral::Ppob_TypeR_Unbind_IFNb = 10e-4*TIME_STEP_LENGHT;
	
double	CGeneral::Ppob_IFNb_die = (plusAB)?0.075:0.0;
int	CGeneral::IFN_prot_secretion_Threshould = 10; // 
int		CGeneral::max_typeIRNumber = (plusAB)?RECEPTOR_NUMBER*0.6:RECEPTOR_NUMBER;

int	CGeneral::CurSMNum = 0;
int	CGeneral::raft_endoc_events_num = 0;

//void polygonFill(const POINT * mv, int count,  short raftNum);

int noInterSec = 0;

double	CGeneral::D_Stx = 0.00;
double	CGeneral::D_SNAP25 = 1.1;
double	CGeneral::D_Vamp = 0.1;

double	CGeneral::D_NSF = 0.01;
int		CGeneral::t_NSF_up = 10;
double	CGeneral::Ptransloc_NSF = 0.01;
double	CGeneral::D_ALPHA = 0.1;
int		CGeneral::t_ALPHA_up = 100;
double	CGeneral::Ptransloc_Alpha = 0.01;

double	CGeneral::D_Stx_inRaft = 0.00;
double	CGeneral::D_SNAP25_inRaft = 1.0;
double	CGeneral::D_Vamp_inRaft = 0.00;

double	CGeneral::Pin_Stx = 0.0;
double	CGeneral::Pin_SNAP25 = 1.0;
double	CGeneral::Pin_Vamp = 0.0;
double	CGeneral::Pout_Stx = 0.0;
double	CGeneral::Pout_SNAP25 = 1.0;
double	CGeneral::Pout_Vamp = 0.0;

double	CGeneral::Pin_SynSyn = 0.0;
double	CGeneral::Pin_SynSynSyn = 0.01;
double	CGeneral::Pin_SynSnap25 = 0.0;
double	CGeneral::Pin_SynSnap25Vamp = 0.0;
double	CGeneral::Pin_SynSnap25VampAlpha = 0.0;
double	CGeneral::Pout_SynSyn = 0.0;
double	CGeneral::Pout_SynSynSyn = 0.0;
double	CGeneral::Pout_SynSnap25 = 0.0;
double	CGeneral::Pout_SynSnap25Vamp = 0.0;
double	CGeneral::Pout_SynSnap25VampAlpha = 0.0;

//int		CGeneral::typeIRNumber = 0;

int		CGeneral::initSntNumber = 0;
int		CGeneral::initSntSntNumber = 00;
int		CGeneral::initSntSntSntNumber = 00;
int		CGeneral::initSNAP25Number = 1500;
int		CGeneral::initNSFNumber = 00; //1%
int		CGeneral::initAlphaNumber = 0; //1%
int		CGeneral::initVampNumber = 0; 
int		CGeneral::initSynSnap25 = 0; 
int		CGeneral::initSynSnap25Vamp = 0; 
int		CGeneral::initSynSnap25VampAlpha = 0; 

double	CGeneral::Ppob_Syn_Bind_Syn = 0.0;
double	CGeneral::Ppob_SynSyn_Bind_Syn = 0.0;

double	CGeneral::Ppob_Syn_Bind_SNAP25 = 0.01;
//double	CGeneral::Ppob_Syn_Bind_SNAP25 = 0.0000001;
double	CGeneral::Ppob_SynSNAP25_BindVamp = 0.0;
double	CGeneral::Ppob_SynSNAP25Vamp_BindAlpha = 1.0;
double	CGeneral::Ppob_NSF_diss_SynSNAP25VampAlpha = 1.0;

double	CGeneral::Ppob_SynSyn_Dissociation = 0.00;
double	CGeneral::Ppob_SynSynSyn_Dissociation = 0.000;

double	CGeneral::Ppob_SynSNAP25_Dissociation = 0.0000001;
double	CGeneral::Ppob_SynSNAP25Vamp_Dissociation = 0.00000001;
double	CGeneral::Ppob_SynSNAP25VampAlpha_Dissociation = 0.00000001;

double	CGeneral::InitInRaftFractionSnt = 1.0;
double	CGeneral::InitInRaftFractionSntSnt = 0.0;
double	CGeneral::InitInRaftFractionSntSntSnt = 0.0;
double	CGeneral::InitInRaftFractionSNAP25 = 0.0;
double	CGeneral::InitInRaftFractionNSF = 0.0;
double	CGeneral::InitInRaftFractionAlpha = 0.0;
double	CGeneral::InitInRaftFractionVamp = 0.0;
double	CGeneral::InitInRaftFractionSynSnap25 = 0;
double	CGeneral::InitInRaftFractionSynSnap25Vamp = 0;
double	CGeneral::InitInRaftFractionSynSnap25VampAlpha = 0;

int		CGeneral::syn_snap25encounters=0; 
int		CGeneral::syn_syn_encounters=0; 
int		CGeneral::synSyn_syn_encounters=0; 
int		CGeneral::binary_Vamp_encounters=0; 
int		CGeneral::SNAR_SNAP_encounters=0; 
int		CGeneral::prodoctive_syn_snap25encounters=0; 
int		CGeneral::prodoctive_binary_Vamp_encounters=0; 
int		CGeneral::prodoctive_SNAR_SNAP_encounters=0; 
int		CGeneral::prodoctive_syn_syn_encounters=0; 
int		CGeneral::prodoctive_synSyn_syn_encounters=0; 
int		CGeneral::syn_snap25_diss=0; 
int		CGeneral::binary_Vamp_diss=0; 
int		CGeneral::SNAR_SNAP_diss=0; 
int		CGeneral::syn_syn_diss=0; 
int		CGeneral::syn_syn_syn_diss=0; 

int CGeneral::lastSMindex = 0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CGeneral::TIME_STEP_NUMBER   = SIMULATION_DURATION_IN_HOURS * 60*60/TIME_STEP_LENGHT;
///pow((TIME_STEP_LENGHT/UPPER_LIMIT_TIME_STEP_LENGHT),2);
//int CGeneral::GRID_SIZE   = 60;


CGeneral::CGeneral()
{

}

CGeneral::~CGeneral()
{

}


void CGeneral::BindReceptorToGrid(CReceptor & rec)
{
	/*
			rec.SetUsage(true); //????

	bool is_in_raft = false;
//	int index_in_profileVec = GetId_in_R_ProfileVec(rec.GetName());
	if( rg.Random() < RprofileVec[rec.GetType()].GetInitInRaftFraction() )  // is to put in raft
		if(RAFT_NUMBER>0)
			is_in_raft = true;

	int attempt_count1 = 0;
	while(1)
	{
		if(attempt_count1++ > 50000 )
		{
			CGeneral::START_SIM = false;
			throw(-3);
		}

		rec.CurrentLocation.x = rec.InitLocation.x = rand()%GRID_SIZE;
		rec.CurrentLocation.y = rec.InitLocation.y = rand()%GRID_SIZE;
		if(grid.m_Grid[rec.InitLocation.y] [rec.InitLocation.x].array[Rec] == -1) //free place
		{
			int RaftNum = grid.m_Grid[rec.InitLocation.y] [rec.InitLocation.x].array[Raft];
			if(RaftNum >= 0)  // sm is inside the raft
			{
				if( is_in_raft ) 
				{
					CGeneral::RaftArray[RaftNum].SetRecIndex(rec.Get_R_index());
					rec.GetInRaft(RaftNum); 
					break;
				}//if inside raft is ok 
			}
			else   // SM is outside the raft
			{
				if( !is_in_raft ) 
				{
					break;
				}//if outside raft is ok 
			}
		}
	}

	grid.m_Grid[rec.InitLocation.y][rec.InitLocation.x].array[Rec] = rec.Get_R_index();

  */
}


void CGeneral::Fill_SM_Profile()
{
	CSMprofile profile;

	profile.SetDefaultD(D_NSF);
	profile.Set_D_upon_Active(D_NSF);
	profile.SetSpontaneousSMactivationRate(0.000);
	profile.SetSpontaneousSMinactivationRate(000);
	profile.SetIsCyto(true);
	profile.SetInitNumber(initNSFNumber);
	profile.SetLifeTime(t_NSF_up);
	profile.SetPtransloc(Ptransloc_NSF);
	profile.SetInitActivePercent(0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionNSF);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	profile.SetSubstrateName(SynSnap25);
	SMprofileVec[NSF] = profile;

	profile.SetDefaultD(D_ALPHA);
	profile.Set_D_upon_Active(D_ALPHA);
	profile.SetSpontaneousSMactivationRate(0.000);
	profile.SetSpontaneousSMinactivationRate(000);
	profile.SetIsCyto(true);
	profile.SetInitNumber(initAlphaNumber);
	profile.SetLifeTime(t_ALPHA_up);
	profile.SetPtransloc(Ptransloc_Alpha);
	profile.SetInitActivePercent(0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionAlpha);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	profile.SetSubstrateName(SynSnap25);
	SMprofileVec[Alpha] = profile;

	profile.SetDefaultD(D_SNAP25);
	profile.Set_D_upon_Active(D_SNAP25);
	profile.Set_D_inRaft(D_SNAP25_inRaft);
	profile.SetDefault_P_enterRaft(Pin_SNAP25);
	profile.SetP_enterRaft_upon_Active(Pin_SNAP25);
	profile.SetDefault_P_leaveRaft(Pout_SNAP25);
	profile.SetP_leaveRaft_upon_Active(Pout_SNAP25);
	profile.SetSpontaneousSMactivationRate(0.0);
	profile.SetSpontaneousSMinactivationRate(0);
	profile.SetIsCyto(false);
	profile.SetInitNumber(initSNAP25Number);
	profile.SetInitActivePercent(0.0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionSNAP25);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	profile.SetSubstrateName(SynSnap25);
	SMprofileVec[SNAP25] = profile;

	profile.SetDefaultD(D_Vamp);
	profile.Set_D_upon_Active(D_Vamp);
	profile.Set_D_inRaft(D_Vamp_inRaft);
	profile.SetDefault_P_enterRaft(Pin_Vamp);
	profile.SetP_enterRaft_upon_Active(Pin_Vamp);
	profile.SetDefault_P_leaveRaft(Pout_Vamp);
	profile.SetP_leaveRaft_upon_Active(Pout_Vamp);
	profile.SetSpontaneousSMactivationRate(0.001);
	profile.SetSpontaneousSMinactivationRate(1.E9);
	profile.SetIsCyto(false);
	profile.SetInitNumber(initVampNumber);
	profile.SetInitActivePercent(0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionVamp);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	SMprofileVec[Vamp] = profile;

}

void CGeneral::Fill_R_Profile()
{
	CRProfile profile;

	profile.SetDefaultD(D_Stx);
	profile.Set_D_upon_Active(D_Stx);
	profile.Set_D_inRaft(D_Stx_inRaft);
	profile.SetDefault_P_enterRaft(Pin_Stx);
	profile.SetP_enterRaft_upon_Active(Pin_Stx);
	profile.SetDefault_P_leaveRaft(Pout_Stx);
	profile.SetP_leaveRaft_upon_Active(Pout_Stx);
	profile.SetSpontaneousSMactivationRate(0.000);
	profile.SetSpontaneousSMinactivationRate(000);
//	profile.SetInitNumber((GRID_SIZE*GRID_SIZE)/100);
	profile.SetInitNumber(initSntNumber);
	profile.SetInitActivePercent(0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionSnt);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	profile.SetSubstrateName(SynSnap25);
	RprofileVec[Syn] = profile;

	profile.SetDefaultD(RprofileVec[Syn].GetDefaultD()/sqrt(2));
	profile.Set_D_upon_Active(RprofileVec[Syn].Get_D_upon_Active()/sqrt(2));
	profile.SetDefault_P_enterRaft(Pin_SynSyn);
	profile.SetP_enterRaft_upon_Active(Pin_SynSyn);
	profile.SetDefault_P_leaveRaft(Pout_SynSyn);
	profile.SetP_leaveRaft_upon_Active(Pout_SynSyn);
	profile.SetSpontaneousSMactivationRate(0.000);
	profile.SetSpontaneousSMinactivationRate(000);
//	profile.SetInitNumber((GRID_SIZE*GRID_SIZE)/100);
	profile.SetInitNumber(initSntSntNumber);
	profile.SetInitActivePercent(0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionSntSnt);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	profile.SetSubstrateName(SynSnap25);
	RprofileVec[SynSyn] = profile;

	profile.SetDefaultD(RprofileVec[Syn].GetDefaultD()/sqrt(3));
	profile.Set_D_upon_Active(RprofileVec[Syn].Get_D_upon_Active()/sqrt(3));
	profile.SetDefault_P_enterRaft(Pin_SynSynSyn);
	profile.SetP_enterRaft_upon_Active(Pin_SynSynSyn);
	profile.SetDefault_P_leaveRaft(Pout_SynSynSyn);
	profile.SetP_leaveRaft_upon_Active(Pout_SynSynSyn);
	profile.SetSpontaneousSMactivationRate(0.000);
	profile.SetSpontaneousSMinactivationRate(000);
//	profile.SetInitNumber((GRID_SIZE*GRID_SIZE)/100);
	profile.SetInitNumber(initSntSntSntNumber);
	profile.SetInitActivePercent(0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionSntSntSnt);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	profile.SetSubstrateName(SynSnap25);
	RprofileVec[SynSynSyn] = profile;

	profile.SetDefaultD(RprofileVec[Syn].GetDefaultD()/sqrt(2));
	profile.Set_D_upon_Active(RprofileVec[Syn].Get_D_upon_Active()/sqrt(2));
	profile.SetDefault_P_enterRaft(Pin_SynSnap25);
	profile.SetP_enterRaft_upon_Active(Pin_SynSnap25);
	profile.SetDefault_P_leaveRaft(Pout_SynSnap25);
	profile.SetP_leaveRaft_upon_Active(Pout_SynSnap25);
	profile.SetSpontaneousSMactivationRate(0.000);
	profile.SetSpontaneousSMinactivationRate(000);
	profile.SetInitNumber(initSynSnap25);
	profile.SetInitActivePercent(0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionSynSnap25);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	profile.SetSubstrateName(SNAP25);
	RprofileVec[SynSnap25] = profile;

	profile.SetDefaultD(RprofileVec[Syn].GetDefaultD()/sqrt(3));
	profile.Set_D_upon_Active(RprofileVec[Syn].Get_D_upon_Active()/sqrt(3));
	profile.SetDefault_P_enterRaft(Pin_SynSnap25Vamp);
	profile.SetP_enterRaft_upon_Active(Pin_SynSnap25Vamp);
	profile.SetDefault_P_leaveRaft(Pout_SynSnap25Vamp);
	profile.SetP_leaveRaft_upon_Active(Pout_SynSnap25Vamp);
	profile.SetSpontaneousSMactivationRate(0.001);
	profile.SetSpontaneousSMinactivationRate(000);
	profile.SetInitNumber(initSynSnap25Vamp);
	profile.SetInitActivePercent(0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionSynSnap25Vamp);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	profile.SetSubstrateName(SNAP25);
	RprofileVec[SynSnap25Vamp] = profile;
	
	profile.SetDefaultD(RprofileVec[Syn].GetDefaultD()/sqrt(4));
	profile.Set_D_upon_Active(RprofileVec[Syn].Get_D_upon_Active()/sqrt(4));
	profile.SetDefault_P_enterRaft(Pin_SynSnap25VampAlpha);
	profile.SetP_enterRaft_upon_Active(Pin_SynSnap25VampAlpha);
	profile.SetDefault_P_leaveRaft(Pout_SynSnap25VampAlpha);
	profile.SetP_leaveRaft_upon_Active(Pout_SynSnap25VampAlpha);
	profile.SetSpontaneousSMactivationRate(0.001);
	profile.SetSpontaneousSMinactivationRate(000);
	profile.SetInitNumber(initSynSnap25VampAlpha);
	profile.SetInitActivePercent(0);
	profile.SetThresholdNumber(-1); 
	profile.SetInitInRaftFraction(InitInRaftFractionSynSnap25VampAlpha);
	profile.SetAxisAttached(false);
	profile.SetAxisName('n');
	profile.SetSubstrateName(SNAP25);
	RprofileVec[SynSnap25VampAlpha] = profile;

}

void CGeneral::BindSigMolToGrid(CSigMol & sm)
{
	/*
	sm.SetUsage(true);
	bool is_in_raft = false;
	if(rg.Random() < SMprofileVec[sm.GetType()].GetInitInRaftFraction())  // is to put in raft
		if(RAFT_NUMBER>0)
			is_in_raft = true;

	int attempt_count1 = 0;
	while(1)
	{
		if(attempt_count1++ > 300000 )
		{
			CGeneral::START_SIM = false;
			throw(-3);
		}

		sm.Location.x = rand()%GRID_SIZE;
		sm.Location.y = rand()%GRID_SIZE;
		if(grid.m_Grid[sm.Location.y] [sm.Location.x].array[SM] == -1) //free place
		{
			int RaftNum = grid.m_Grid[sm.Location.y][sm.Location.x].array[Raft];
			if(RaftNum >= 0)  // sm is inside the raft
			{
				if( is_in_raft ) 
				{
					CGeneral::RaftArray[RaftNum].SetSMIndex(sm.GetIndex());
					sm.GetInRaft(RaftNum); 
					break;
				}//if inside raft is ok 
			}
			else   // SM is outside the raft
			{
				if( !is_in_raft ) 
				{
					break;
				}//if outside raft is ok 
			}
		}
	}
	grid.m_Grid[sm.Location.y][sm.Location.x].array[SM] = sm.GetIndex();

  */
}

bool CGeneral::LocateSMOnGrid(CSigMol & sm, CPoint location)
{

	/*
	bool valid_location = false;
	
	////// looking for neihbor free place  ///////////
	int new_y = location.y;
	int new_x = location.x; 
	POINT pts[8] = {-1,0,   -1,-1,   0,-1,   1,-1,   1,0,    1,1,   0,1,   -1,1};
	
	for(int k=0; k<8; k++)
	{
		switch(k)
		{
		case 0:
			// x - 1  = LEFT
			if( (new_x = location.x + pts[k].x) < 0 ) new_x = GRID_SIZE - 1;
			break;
		case 1:
			// x - 1, y - 1  = UP_LEFT
			if( (new_x = location.x + pts[k].x) < 0 ) new_x = GRID_SIZE - 1;
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		case 2:
			// y - 1 = UP
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		case 3 :
			// x + 1, y - 1 = UP_RIGHT
			if( (new_x = location.x + pts[k].x) >= GRID_SIZE ) new_x = 0;
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		case 4 :
			// x + 1 = RIGHT
			if( (new_x = location.x + pts[k].x) >= GRID_SIZE ) new_x = 0;
			break;
		case 5 :
			// x + 1, y + 1 = DOWN_RIGHT
			if( (new_x = location.x + pts[k].x) >= GRID_SIZE ) new_x = 0;
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		case 6:
			// y + 1 = DOWN
			if( (new_y = location.y + pts[k].y) >= GRID_SIZE ) new_y = 0;
			break;
		case 7 :
			// x - 1, y + 1 = DOWN_LEFT
			if( (new_x = location.x + pts[k].x) >= GRID_SIZE ) new_x = 0;
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		}
		
		int smID = grid.m_Grid[new_y][new_x].array[SM];
		
//		_ASSERTE(CGeneral::grid.m_Grid[new_y][new_x].GetCellIndex() >= 0);
		
		if((smID == -1))  //pSM is absent 
		{
			valid_location = true;
			break;
		}
	}
	//---------- finish looking for neihbor free place ---------------
	sm.Location.y = new_y;
	sm.Location.x = new_x;

	if(!valid_location)
	{
		return false;
		_ASSERTE(0);
	}
	sm.SetUsage(true);
	grid.m_Grid[sm.Location.y][sm.Location.x].array[SM] = sm.GetIndex();// update grid with sm index

	int RaftNum = grid.m_Grid[sm.Location.y][sm.Location.x].array[Raft];
	if(RaftNum >= 0)  // sm is inside the raft
	{
		CGeneral::RaftArray[RaftNum].SetSMIndex(sm.GetIndex());
		sm.GetInRaft(RaftNum); 
	}
*/
	return true;

  
}

bool CGeneral::LocateRecOnGrid(CReceptor & rec, CPoint location)
{
	/*
	bool valid_location = false;
	
	////// looking for neihbor free place  ///////////
	int new_y = location.y;
	int new_x = location.x; 
	POINT pts[8] = {-1,0,   -1,-1,   0,-1,   1,-1,   1,0,    1,1,   0,1,   -1,1};
	
	for(int k=0; k<8; k++)
	{
		switch(k)
		{
		case 0:
			// x - 1  = LEFT
			if( (new_x = location.x + pts[k].x) < 0 ) new_x = GRID_SIZE - 1;
			break;
		case 1:
			// x - 1, y - 1  = UP_LEFT
			if( (new_x = location.x + pts[k].x) < 0 ) new_x = GRID_SIZE - 1;
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		case 2:
			// y - 1 = UP
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		case 3 :
			// x + 1, y - 1 = UP_RIGHT
			if( (new_x = location.x + pts[k].x) >= GRID_SIZE ) new_x = 0;
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		case 4 :
			// x + 1 = RIGHT
			if( (new_x = location.x + pts[k].x) >= GRID_SIZE ) new_x = 0;
			break;
		case 5 :
			// x + 1, y + 1 = DOWN_RIGHT
			if( (new_x = location.x + pts[k].x) >= GRID_SIZE ) new_x = 0;
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		case 6:
			// y + 1 = DOWN
			if( (new_y = location.y + pts[k].y) >= GRID_SIZE ) new_y = 0;
			break;
		case 7 :
			// x - 1, y + 1 = DOWN_LEFT
			if( (new_x = location.x + pts[k].x) >= GRID_SIZE ) new_x = 0;
			if( (new_y = location.y + pts[k].y) < 0 ) new_y = GRID_SIZE - 1;
			break;
		}
		
		int recID = grid.m_Grid[new_y][new_x].array[Rec];
		
		//			_ASSERTE(CGeneral::grid.m_Grid[new_y][new_x].GetCellIndex() >= 0);
		
		if((recID == -1))  //rec is absent 
		{
			valid_location = true;
			break;
		}
	}
	//---------- finish looking for neihbor free place ---------------
	rec.CurrentLocation.y = new_y;
	rec.CurrentLocation.x = new_x;

	if(!valid_location)
	{
		return false;
		_ASSERTE(0);
	}
	rec.SetUsage(true);
	grid.m_Grid[rec.CurrentLocation.y][rec.CurrentLocation.x].array[Rec] = rec.Get_R_index();// update grid with rec index

	int RaftNum = grid.m_Grid[rec.CurrentLocation.y][rec.CurrentLocation.x].array[Raft];
	if(RaftNum >= 0)  // sm is inside the raft
	{
		CGeneral::RaftArray[RaftNum].SetRecIndex(rec.Get_R_index());
		rec.GetInRaft(RaftNum); 
	}

	*/
	return true;

  
}

/*
void CGeneral::InitReceptors()
{
	int Rindex = 0;
	int rec_num = RprofileVec[Syn].GetInitNumber();
	for(int index=0; index<rec_num; index++)
	{
		CReceptor r(Rindex++, Syn);
		BindReceptorToGrid(r);
		RArray.push_back(r);
	}
}


void CGeneral::InitReceptors()
{
	int Rindex = 0;
	int r_amount;
    std::vector<CRprofile> ::iterator iter = RprofileVec.begin();
    for (; iter != R_ProfileVec.end(); iter++) 
	{
        r_amount = iter->GetInitNumber();
		for( int i =0 ; i<r_amount ; i++ )
		{
			CReceptor r(Rindex++, (R_Type)i);
			BindReceptorToGrid(r);
			RArray.push_back(r);
		} 
    }	
}
*/

void CGeneral::InitReceptors()
{
	int index = 0;
	int r_amount;
    for (int r_type=0; r_type<R_TYPES_NUMBER; r_type++) 
	{
        r_amount = RprofileVec[r_type].GetInitNumber();
		for( int i =0 ; i<r_amount ; i++ )
		{
			CReceptor r_object(index++, (R_Type)r_type);
			BindReceptorToGrid(r_object);
			RArray.push_back(r_object);
		} 
    }
}

void CGeneral::CreateReceptor() //create receptors during the run 
{
	while( ! delRecStack.empty() )
	{
		int tmp = delRecStack.top();
		CReceptor & rec = CGeneral::RArray[tmp];
//		_ASSERTE(rec.Get_R_index() >= 0 ); // 
		delRecStack.pop();
		BindReceptorToGrid(rec);
//		_ASSERTE(rec.Get_R_index() >= 0 ); // 
		if( is_create_sm_attached_rec )
		{
		} // if	         
		_ASSERTE(rec.Get_R_index() >= 0 ); // 
	}
}

void CGeneral::InitSigMol()
{
	int index = 0;
	int sm_amount;
    for (int sm_type=0; sm_type<SM_TYPES_NUMBER; sm_type++) 
	{
        sm_amount = SMprofileVec[sm_type].GetInitNumber();
		for( int i =0 ; i<sm_amount ; i++ )
		{
			MakeSigMol(index++,(SM_Type)sm_type, CPoint(-1,-1));// -1,-1 for arbitrLocation
		} 
    }
	lastSMindex = SMArray.size();
}

void CGeneral::MakeSigMol(int index, SM_Type sm_type, CPoint location)
{
	if(index==-1) //new SM
	{
		index = lastSMindex;
	}
	CSigMol sm_object(index, (SM_Type)sm_type);
	if(location == CPoint(-1,-1)){ BindSigMolToGrid(sm_object); }
	else { LocateSMOnGrid(sm_object, location);}
	if(SMprofileVec[sm_object.GetType()].GetIsCyto())
		sm_object.SetUsage(false);
	SMArray.push_back(sm_object);

	lastSMindex = SMArray.size();
}

void CGeneral::CreateSigMol(SM_Type type)
{
	int tmp = delSMStack.top();
	CSigMol & sm = SMArray[tmp];
	delSMStack.pop();
	sm.SetType(type);
	if( ! SMprofileVec[sm.GetType()].IsAxisAttached() )  //to create anywere 
	{
		BindSigMolToGrid(sm);
	}
	else  //to create near the axis
	{
//		BindSigMolToGrid(sm, SMprofileVec[sm.GetType()].GetAxisName());
	}				
}

void CGeneral::GenerateSigMol()
{
	while( ! delSMStack.empty() )
	{
		if( !EndocytosedSMQueue.empty() )
		{
			CreateSigMol(EndocytosedSMQueue.front());
			EndocytosedSMQueue.pop();
		} 
		else //vremenno
		{
			_ASSERTE(0);
		}
	}
}

void CGeneral::CreateRaft(int in_index)
{
	/*
	int index;
	if(in_index == -1)
	{
		while( ! delRaftStack.empty() )
		{
			index = delRaftStack.top();
			delRaftStack.pop();
			CRaft Raft_Object(index);  
			RaftArray[index] = Raft_Object;
			polygonFill(Raft_Object.m_shape.GetPtVec() ,Raft_Object.m_shape.Count(), index );
		} // while	         
	}
	else
	{
		index = in_index;
		CRaft Raft_Object(index);  
		RaftArray.push_back(Raft_Object);
		polygonFill(Raft_Object.m_shape.GetPtVec() ,Raft_Object.m_shape.Count(), index );
	}
	*/
}

void CGeneral::InitRafts(int raft_number)
{
	for(int index=0; index < raft_number; index++)
	{
		CreateRaft(index);
	}
}


int CGeneral::DimentionSquareDistrib()
{
	return 15;

}

int CGeneral::BeginSimulation()
{
	//	bool flag_to_mesure_distance = false; //flag == true neans need to calculate the distanse
	CGeneral::is_simul_finished = false;

	if(step++ > TIME_STEP_NUMBER) return 0;  //simulation is finished

	/////////////   start of calculations     //////////////////////////////
//	int calc_rule1 = (step<1000)?1:(step<10000)?10000:(step<100000)?100000:(step<1000000)?100000:1000000 ;
	int calc_rule1 = 600/TIME_STEP_LENGHT;
//	int calc_rule1 = 60*60/TIME_STEP_LENGHT;
	if(step %calc_rule1 == 0 || step == 1)
//	if(step %calc_rule1 == 0 || step == 1 || step == TIME_STEP_NUMBER)
	{
			//	CalculateMSD(step);
			//	Calculate_R_in_out_ratio();
			//  Calculate_R_unbound_bound_ratio();
			//	Calculate_R_SM_complex_in_out_ratio();
			//	Calculate_R_SM_binding_duration();
			//	Calculate_endoc_results();
			Calculate_protein_concentrations();
/*
			int flg = 0;
			if(flg)	CalcResGridG();
			else CalcResGrid();
			*/
	}
	//------------- finish of calculations -----------------------//
	
	/////////////////   start of Rafts loop //////////////////////////////
//	RaftsLoop();
	CellsLoop();
	//---------------finish of Rafts loop -----------------------//
	/////////////////  start of Ags loop //////////////////////////////
//	AgsLoop();
	//---------------finish of Ags loop -----------------------//
	/////////////////  start of SMs loop //////////////////////////////
	SMsLoop();
	//---------------finish of SMs loop -----------------------//
	
	//	CGeneral::Validation(Rec);
	
	CGeneral::is_simul_finished = true;
	return step;
}

int CGeneral::PtInRaft(CPoint & pt, int CurRaftNum)
{
	/*
	if(CurRaftNum >=0)
	{
		return	(CGeneral::RaftArray[CurRaftNum].m_shape.PtInPolygon( pt)) ?
			CurRaftNum	: -1;
	}
	std::vector<CRaft>::iterator raft_iter =  CGeneral::RaftArray.begin();
	for(; raft_iter  != CGeneral::RaftArray.end(); raft_iter++)
	{
		if(raft_iter->IsInUse() && 
			raft_iter->m_shape.PtInPolygon( pt)) return raft_iter->Get_raft_index();
	}

  */
	return -1;
	
}

int CGeneral::PtInRaft(CPoint & pt, int & l, int CurRaftNum)
{
	/*
	_ASSERTE(!"Not in use");
	if(CurRaftNum >=0)
	{
		l=0;
		return	(CGeneral::RaftArray[CurRaftNum].m_shape.PtInPolygon( pt)) ?
			CurRaftNum	: -1;
	}
	int  l1=10000 ;
	std::vector<CRaft>::iterator raft_iter =  CGeneral::RaftArray.begin();
	for(; raft_iter  != CGeneral::RaftArray.end(); raft_iter++)
	{
		if(raft_iter->IsInUse() && 
			raft_iter->m_shape.PtInPolygon( pt, l )) return raft_iter->Get_raft_index();
		if(l < l1) l1 = l;
	}
	l = l1;
	if(l > 0) noInterSec++;
	//CGeneral::out << "Result  l=" << l << "\n" ;
	
	*/
	return -1;
	
}

Kind_of_Move CGeneral::Select_move()
{
	Kind_of_Move move;
//	int choice = rand()%4;
	int choice = rg.IRandom(0,3);
	move = (Kind_of_Move)choice;
	return move;
}

double CGeneral::My_rand(double min, double max)
{
	return min + double(rg.IRandom(0, RAND_MAX)) / RAND_MAX * (max - min);
}

double CGeneral::My_rand0_1()
{
	return rg.Random();
//    return    ( (double)rand() / (double)(RAND_MAX+1) ); 
}	

void CGeneral::CalculateMSD(int time_step)
{
	/*
	int square_value = 0;
	for(int index=0; index<RECEPTOR_NUMBER; index++)
	{
//		if(RecMSDResults[index] != -1) //to avoid calculating receptors that crossed the border 
		{
			square_value += RecMSDResults[index];
		}
	}
	int R_number = RECEPTOR_NUMBER;
	int mean_square_value = square_value / R_number;
	CPoint object(time_step, mean_square_value);
	MSDResultsArray.push_back(object);

  */
}


void CGeneral::Calculate_protein_concentrations()
{

	CResultsTemplate ResultsObject;

	ResultsObject.step = step;

	std::vector<CCell>::iterator cell_iter;
	cell_iter = CellArray.begin();
	CCell * p_cell = cell_iter;
	IndexVec indV;
	int IFNbound = 0;	
	for(; cell_iter  != CGeneral::CellArray.end(); cell_iter++)
	{
		p_cell = cell_iter;

		if( !p_cell->IsInUse()) 		// The cell is not valid
		{
			continue;
		}
//		int cellFractionFactor = 1;
//		int cellFractionFactor = 666;
		ResultsObject.rigI_rna_Vec.push_back(p_cell->GetRIGI_rna_conc());
		ResultsObject.rigI_prot_Vec.push_back(p_cell->GetRIGI_prot_conc());
//		ResultsObject.IFN_rna_Vec.push_back((p_cell->IsInfected())?p_cell->GetIFN_rna_conc() : box_muller(2,1) );
		ResultsObject.IFN_rna_Vec.push_back(p_cell->GetIFN_rna_conc());
		ResultsObject.IFN_prot_Vec.push_back(p_cell->Get_IFNprot_bound());


		ResultsObject.rigI_transcriptionRate_Vec.push_back(p_cell->GetRIGI_transcriptionRate());
		ResultsObject.rigI_decayRate_Vec.push_back(p_cell->GetRIGI_rna_degradationRate()*p_cell->GetRIGI_rna_conc());
		ResultsObject.rigI_translationRate_Vec.push_back(p_cell->GetRIGI_translationRate()*p_cell->GetRIGI_rna_conc());
		ResultsObject.rigI_degradationRate_Vec.push_back(p_cell->GetRIGI_protein_degradationRate()*p_cell->GetRIGI_prot_conc());

		ResultsObject.IFN_transcriptionRate_Vec.push_back(p_cell->GetIFN_transcriptionRate());
		ResultsObject.IFN_decayRate_Vec.push_back(p_cell->GetIFN_rna_degradationRate()*p_cell->GetIFN_rna_conc());
		ResultsObject.IFN_translationRate_Vec.push_back(p_cell->GetIFN_translationRate()*p_cell->GetIFN_rna_conc());
		ResultsObject.IFN_degradationRate_Vec.push_back(p_cell->GetIFN_protein_degradationRate());

		ResultsObject.boundRs_Vec.push_back(p_cell->Get_boundTypeIR());


		IFNbound+=p_cell->Get_boundTypeIR();

	}
	ResultsObject.IFNbound = IFNbound;

	int IFNreleased =  0;
	for(int in=0; in<GRID_SIZE ; in++)
	{
		for(INT in1=0; in1<GRID_SIZE ; in1++)
		{
//			ResultsObject.IFN_prot_Vec.push_back(grid.m_Grid[in][in1].array[SM]);
			IFNreleased+=grid.m_Grid[in][in1].array[SM];
		}
	}
	ResultsObject.IFNreleased = IFNreleased;

/*	int IFNreleased =  0;
	for(int k=0; k< SMArray.size(); k++)
	{
		CSigMol & sm = SMArray[k];
		if(sm.IsInUse()) {
			IFNreleased++;
		}
	}
	ResultsObject.IFNreleased = IFNreleased;

*/	
	
	/*
	int IFNbound = 0;
	for(int index=0; index<RArray.size(); index++)
	{
		CReceptor & rec = RArray[index];
		if( !rec.IsInUse() )
		{
			continue;
		} // if	R is not in use         
		R_Type r_type = rec.GetType();
		if(r_type==SynSnap25)
		IFNbound++;
	}
	ResultsObject.IFNbound = IFNbound;
	if( ! stopProducingIFN_flag)
	{
		if(IFNbound+IFNreleased > initSntNumber){
			stopProducingIFN();
			CGeneral::stopProducingIFN_flag = true;
		}
	}

*/
	Protein_concentration_results_Array.push_back(ResultsObject);
}


void CGeneral::Record_Results_to_files()
{
	bool flag= true;
////////// begin writing protein concentrations results to files "Out_singleCells_concentrations.txt and Out_singleCells_rates.txt" ////
//	out_final_concentration_results << "Time step\t "<<endl; 
   	std::vector<CResultsTemplate>::iterator res_template_iter = Protein_concentration_results_Array.begin();

/*
	for(int i=0,int incr = (Protein_concentration_results_Array.size()/2-1);
		i<Protein_concentration_results_Array.size();
		i += incr, res_template_iter=Protein_concentration_results_Array.begin()+i)
	{
	*/
	for(int i=0, incr = (Protein_concentration_results_Array.size()/2-1);
		i<Protein_concentration_results_Array.size();
		i++, res_template_iter=Protein_concentration_results_Array.begin()+i)
	{


		double_iter it;

/*
		//		out_singleCells_concentrations << "rigI_rna"<<"\t";
		it = res_template_iter->rigI_rna_Vec.begin();
		for(; it != res_template_iter->rigI_rna_Vec.end(); it++)
		{
			out_singleCells_concentrations << *it<<"\t";
				
		}
		out_singleCells_concentrations << endl;

		//		out_singleCells_concentrations << "rigI_prot"<<"\t";
		it = res_template_iter->rigI_prot_Vec.begin();
		for(; it != res_template_iter->rigI_prot_Vec.end(); it++)
		{
			out_singleCells_concentrations << *it<<"\t";
				
		}
		out_singleCells_concentrations << endl;
		
//		out_singleCells_concentrations << "IFNrna"<<"\t";
		it = res_template_iter->IFN_rna_Vec.begin();
		for(; it != res_template_iter->IFN_rna_Vec.end(); it++)
		{
			out_singleCells_concentrations << *it<<"\t";
				
		}
		out_singleCells_concentrations << endl;



 
		//		out_singleCells_concentrations << "IFNprot"<<"\t";
		it = res_template_iter->IFN_prot_Vec.begin();
		for(; it != res_template_iter->IFN_prot_Vec.end(); it++)
		{
			out_singleCells_concentrations << *it<<"\t";
				
		}
		out_singleCells_concentrations << endl;
*/
		

//		out_singleCells_concentrations << "IFNrna"<<"\t";
		it = res_template_iter->IFN_rna_Vec.begin();
		for(; it != res_template_iter->IFN_rna_Vec.end(); it++)
		{
			out_singleCells_concentrations << *it<<"\t";
				
		}
		out_singleCells_concentrations << endl;


		//		out_singleCells_concentrations << "rigI_rna"<<"\t";
		it = res_template_iter->rigI_rna_Vec.begin();
		for(; it != res_template_iter->rigI_rna_Vec.end(); it++)
		{
			out_singleCells_concentrations << *it<<"\t";
				
		}
		out_singleCells_concentrations << endl;


		//		out_singleCells_concentrations << "boundRs"<<"\t";
		it = res_template_iter->boundRs_Vec.begin();
		for(; it != res_template_iter->boundRs_Vec.end(); it++)
		{
			out_singleCells_concentrations << *it<<"\t";
				
		}
		out_singleCells_concentrations << endl;

		
		/*
		//		out_singleCells_concentrations << "rigI_prot"<<"\t";
		it = res_template_iter->rigI_prot_Vec.begin();
		for(; it != res_template_iter->rigI_prot_Vec.end(); it++)
		{
			out_singleCells_concentrations << *it<<"\t";
				
		}
		out_singleCells_concentrations << endl;
		

 
		//		out_singleCells_concentrations << "IFNprot"<<"\t";
		it = res_template_iter->IFN_prot_Vec.begin();
		for(; it != res_template_iter->IFN_prot_Vec.end(); it++)
		{
			out_singleCells_concentrations << *it<<"\t";
				
		}
		out_singleCells_concentrations << endl;

*/


		it = res_template_iter->rigI_transcriptionRate_Vec.begin();
		for(; it != res_template_iter->rigI_transcriptionRate_Vec.end(); it++)
		{
			out_singleCells_rates << *it<<"\t";
				
		}
		out_singleCells_rates << endl;


		it = res_template_iter->rigI_decayRate_Vec.begin();
		for(; it != res_template_iter->rigI_decayRate_Vec.end(); it++)
		{
			out_singleCells_rates << *it<<"\t";
				
		}
		out_singleCells_rates << endl;

		it = res_template_iter->rigI_translationRate_Vec.begin();
		for(; it != res_template_iter->rigI_translationRate_Vec.end(); it++)
		{
			out_singleCells_rates << *it<<"\t";
				
		}
		out_singleCells_rates << endl;

				it = res_template_iter->rigI_degradationRate_Vec.begin();
		for(; it != res_template_iter->rigI_degradationRate_Vec.end(); it++)
		{
			out_singleCells_rates << *it<<"\t";
				
		}
		out_singleCells_rates << endl;

				it = res_template_iter->IFN_transcriptionRate_Vec.begin();
		for(; it != res_template_iter->IFN_transcriptionRate_Vec.end(); it++)
		{
			out_singleCells_rates << *it<<"\t";
				
		}
		out_singleCells_rates << endl;

		it = res_template_iter->IFN_decayRate_Vec.begin();
		for(; it != res_template_iter->IFN_decayRate_Vec.end(); it++)
		{
			out_singleCells_rates << *it<<"\t";
				
		}
		out_singleCells_rates << endl;

		it = res_template_iter->IFN_translationRate_Vec.begin();
		for(; it != res_template_iter->IFN_translationRate_Vec.end(); it++)
		{
			out_singleCells_rates << *it<<"\t";
				
		}
		out_singleCells_rates << endl;

		it = res_template_iter->IFN_degradationRate_Vec.begin();
		for(; it != res_template_iter->IFN_degradationRate_Vec.end(); it++)
		{
			out_singleCells_rates << *it<<"\t";
				
		}
		out_singleCells_rates << endl;





		if(flag){
//			res_template_iter = Protein_concentration_results_Array.end()-2;
//			flag = false;
		}
	}
	//-----end of writing results to file "Out_singleCells_concentrations" ////




}


void CGeneral::Record_Results_to_files1()
{
////////// begin writing protein concentrations results to file "" ////

	out_TS_concentrations <<"Time step\t"<<"IFNrna\t"<<"RIGIrna\t"<<"TypeIRbound\t"<<"RIGIprot\t"<<"IFNfree\t"<<"IFNbound\t"<<endl;
	out_TS_rates <<"Time step\t"<<"rigI_transcriptionRate\t"<<"rigI_decayRate\t"<<"rigI_translationRate\t"<<"rigI_degradationRate\t"<<"IFN_transcriptionRate\t"<<"IFN_decayRate\t"<<"IFN_translationRate\t"<<"IFN_degradationRate\t"<<endl;
   	std::vector<CResultsTemplate>::iterator res_template_iter = Protein_concentration_results_Array.begin();
	for(; res_template_iter != Protein_concentration_results_Array.end(); res_template_iter++)
	{

		out_TS_concentrations <<(double)res_template_iter->step*(double)TIME_STEP_LENGHT/60./60.<<"\t";
		out_TS_rates <<(double)res_template_iter->step*(double)TIME_STEP_LENGHT/60./60.<<"\t";

		double_iter it;
		it = res_template_iter->IFN_rna_Vec.begin();
		double avg=0;
		double sum =0;
		for(; it != res_template_iter->IFN_rna_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->IFN_rna_Vec.size();
		out_TS_concentrations << avg<<"\t";
//		out_TS_concentrations << endl;

		//		out_TS_concentrations << "rigI_prot"<<"\t";
		sum =0;
		it = res_template_iter->rigI_rna_Vec.begin();
		for(; it != res_template_iter->rigI_rna_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->rigI_rna_Vec.size();
		out_TS_concentrations << avg<<"\t";
//		out_TS_concentrations << endl;

//		out_TS_concentrations << "inf"<<"\t";
		sum =0;
		it = res_template_iter->IFN_prot_Vec.begin();
		for(; it != res_template_iter->IFN_prot_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->IFN_prot_Vec.size();
		out_TS_concentrations << avg<<"\t";
//		out_TS_concentrations << endl;

		//		out_TS_concentrations << "rigI_rna"<<"\t";
		sum =0;
		it = res_template_iter->rigI_prot_Vec.begin();
		for(; it != res_template_iter->rigI_prot_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->rigI_prot_Vec.size();
		out_TS_concentrations << avg<<"\t";

		out_TS_concentrations << res_template_iter->IFNreleased<<"\t";
		out_TS_concentrations << res_template_iter->IFNbound<<"\t";

		out_TS_concentrations << endl;


		sum =0;
		it = res_template_iter->rigI_transcriptionRate_Vec.begin();
		for(; it != res_template_iter->rigI_transcriptionRate_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->rigI_transcriptionRate_Vec.size();
		out_TS_rates << avg<<"\t";

	
		sum =0;
		it = res_template_iter->rigI_decayRate_Vec.begin();
		for(; it != res_template_iter->rigI_decayRate_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->rigI_decayRate_Vec.size();
		out_TS_rates << avg<<"\t";

	
			sum =0;
		it = res_template_iter->rigI_translationRate_Vec.begin();
		for(; it != res_template_iter->rigI_translationRate_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->rigI_translationRate_Vec.size();
		out_TS_rates << avg<<"\t";

	
			sum =0;
		it = res_template_iter->rigI_degradationRate_Vec.begin();
		for(; it != res_template_iter->rigI_degradationRate_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->rigI_degradationRate_Vec.size();
		out_TS_rates << avg<<"\t";

	
			sum =0;
		it = res_template_iter->IFN_transcriptionRate_Vec.begin();
		for(; it != res_template_iter->IFN_transcriptionRate_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->IFN_transcriptionRate_Vec.size();
		out_TS_rates << avg<<"\t";


		sum =0;
		it = res_template_iter->IFN_decayRate_Vec.begin();
		for(; it != res_template_iter->IFN_decayRate_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->IFN_decayRate_Vec.size();
		out_TS_rates << avg<<"\t";

		sum =0;
		it = res_template_iter->IFN_translationRate_Vec.begin();
		for(; it != res_template_iter->IFN_translationRate_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->IFN_translationRate_Vec.size();
		out_TS_rates << avg<<"\t";

		sum =0;
		it = res_template_iter->IFN_degradationRate_Vec.begin();
		for(; it != res_template_iter->IFN_degradationRate_Vec.end(); it++)
		{
			sum += *it;
		}
		avg = sum/res_template_iter->IFN_degradationRate_Vec.size();
		out_TS_rates << avg<<"\t";

		out_TS_rates << endl;

	}
	//-----end of writing results to file "out_final_concentration_results.txt" ////

	CGeneral::out << "ifn D: "<<IFNb_D<<endl;
	CGeneral::out << "TIME_STEP_LENGHT: "<<TIME_STEP_LENGHT<<endl;
	CGeneral::out << "cell number: "<<RAFT_NUMBER<<endl;
	CGeneral::out << "max transcription RateConstant: "<<max_transcriptionRateC<<endl;
	CGeneral::out << "max translation RateConstant: "<<max_translationRateC<<endl;
	CGeneral::out << "typical_prot degradation Rate Constant: "<<typical_prot_degradationRateC<<endl;
	CGeneral::out << "typical_rna degradation Rate Constant: "<<typical_rna_degradationRateC<<endl;
	CGeneral::out << "IFN_rna_activation_hill Coef: "<<IFN_rna_activation_hillCoef<<endl;
	CGeneral::out << "DDX58_rna_activation_hill Coef: "<<DDX58_rna_activation_hillCoef<<endl;
	CGeneral::out << "infectivityThreshould: "<<infectivityThreshould<<endl;
	CGeneral::out << "Ppob TypeIR bind IFNb: "<<Ppob_TypeR_Bind_IFNb<<endl;
	CGeneral::out << "Ppob TypeIR Unbind IFNb: "<<Ppob_TypeR_Unbind_IFNb<<endl;
}

void CGeneral::InitProcess()
{
	
//		CMatlabEng matlab;
	



	//open new matlab session
//	message("Starting MATLAB");

	
	
	
	//	matlab.Open(NULL);


	/*
//	message("Hiding MATLAB");
	matlab.SetVisible(FALSE);
//	message("Press any key to continue");
//	getch();

//	message("Showing MATLAB");
	matlab.SetVisible(TRUE);
//	message("Press any key to continue");
//	getch();
	*/


/*

	mxArray *T = NULL;
	double time[10] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

	//create matrix
	T = mxCreateDoubleMatrix(1, 10, mxREAL);
	memcpy((void *)mxGetPr(T), (void *)time, sizeof(time));
	
	//send matrix T to matlab
//	message("Send matrix T to matlab");
	matlab.PutVariable("T", T);

	//Evaluate matlab command
	matlab.EvalString("D = .5.*(-9.8).*T.^2;");

	//Plot results
//	message("Plot(T, D)");
	matlab.EvalString("plot(T,D);");	
	matlab.EvalString("title('Position vs. Time for a falling object');");
	matlab.EvalString("xlabel('Time (seconds)');");
	matlab.EvalString("ylabel('Position (meters)');");
	matlab.EvalString("grid;");

	//pause to see results
//	message("Press any key to continue");
//	getch();
	
	//destroy matrix
	mxDestroyArray(T);

*/



	/*
	//show MATLAB graphics capabilities
//	message("Showing MATLAB graphics capabilities");
	matlab.EvalString("z=peaks(25);");
	matlab.EvalString("surf(z);");
	matlab.EvalString("colormap(jet);");
	matlab.EvalString("knot;");

	//pause
//	getch();
*/
	//close session

	


	//matlab.Close();

	//------- begin cleaning data from last step ---------------
	for(int in=0; in<GRID_SIZE ; in++)
		for(int in1=0; in1<GRID_SIZE ; in1++)
		{
			grid.m_Grid[in1][in].array[Rec] = -1;
			grid.m_Grid[in1][in].array[Raft] = -1;
			grid.m_Grid[in1][in].array[Ag] = -1;
			grid.m_Grid[in1][in].array[Ht] = -1;
			grid.m_Grid[in1][in].array[SM] = 0;
		}


	RArray.clear();
//	RaftArray.clear();
	SMArray.clear();
	while (!delRaftStack.empty()) delRaftStack.pop(); 
	while (!delRecStack.empty()) delRecStack.pop(); 
	while (!delSMStack.empty()) delSMStack.pop(); 
	while (!EndocytosedSMQueue.empty()) EndocytosedSMQueue.pop(); 

	raft_endoc_events_num = 0;
	RecInRaft = 0;
	Recepter_Number = 0;

	syn_snap25encounters=0; 
	syn_syn_encounters=0; 
	synSyn_syn_encounters=0; 
	binary_Vamp_encounters=0; 
	SNAR_SNAP_encounters=0; 
	prodoctive_syn_snap25encounters=0; 
	prodoctive_binary_Vamp_encounters=0; 
	prodoctive_SNAR_SNAP_encounters=0; 
	prodoctive_syn_syn_encounters=0; 
	prodoctive_synSyn_syn_encounters=0; 
	syn_snap25_diss=0; 
	binary_Vamp_diss=0; 
	SNAR_SNAP_diss=0; 
	syn_syn_diss=0; 
	syn_syn_syn_diss=0; 
	
	MSDResultsArray.clear();
	Protein_concentration_results_Array.clear();

	out_singleCells_concentrations.clear();
	out_TS_concentrations.clear();
	out_singleCells_rates.clear();
	out_TS_rates.clear();
	out.clear();
	//------- end cleaning data from last step ---------------

	/////////////////////creating new data  /////////////

	Fill_R_Profile();
	Fill_SM_Profile();
	InitCells(CalculateRaftNumber());
	InitReceptors();
//	InitSigMol();
	//------- end creating new data ------------------------
}

int CGeneral::CalculateRaftNumber()
{
	/*
	if(RAFT_SURFACE_COVERAGE_PERCENT == 0)
		return 0;
	else
		return 6;
	double tmp;
	tmp = (GRID_SIZE * GRID_SIZE); //overall grid points number
	tmp = tmp * (RAFT_SURFACE_COVERAGE_PERCENT/100); //gives rafted surface
	tmp = tmp / MEAN_RAFT_SIZE; // gives mean raft size
	RAFT_NUMBER = tmp;
	return tmp;
	*/
	return RAFT_NUMBER;
}

void CGeneral::ChangeLocation_of_attachedSM(Kind_of_Move KindOfMove, int rec_index)
{
	int sm_index_to_set = RArray[rec_index].A_B_SM_Indexes.x;
	if( sm_index_to_set != -1)
	{
		_ASSERTE(CGeneral::SMArray[sm_index_to_set].GetBoundRec() >= 0);
		SMArray[sm_index_to_set].Move(KindOfMove, 1);	
	} // if	     
	sm_index_to_set = RArray[rec_index].A_B_SM_Indexes.y;
	if( sm_index_to_set != -1)
	{
		_ASSERTE(CGeneral::SMArray[sm_index_to_set].GetBoundRec() >= 0);
		SMArray[sm_index_to_set].Move(KindOfMove, 1);	
	} // if	     
}

void CGeneral::RaftsLoop()
{

}

const double *  CGeneral::Gillespie(const CCell * cell){
  // define auxiliary variables

  // sum up all the possible rates - the rate at which something happens
  double total_rates=0;
  for (int i=0; i<cell->m_gillaspieAuxiliary.m_NUM_OF_RATES; i++){
    total_rates += cell->m_gillaspieAuxiliary.m_rates[i];
  }
	double ar[2];
  //and then choose a random actual step size chosen from an 
  //exponential probability (with 1/total_rates as mean)
  double r=0.0;
  r = My_rand0_1();
  double time = -log(r)/total_rates;
  ar[0]=time;
  
  // choose the process uniformly according to the rates
  r = My_rand(0,total_rates);
  assert(r<=total_rates && r>=0);

  int rate;
  rate  = -1;
  do {
    rate++;
	assert(rate<cell->m_gillaspieAuxiliary.m_NUM_OF_RATES);
    r -= cell->m_gillaspieAuxiliary.m_rates[rate];
  } while (r>10e-8);
//  } while (r>0);
  ar[1]=rate;
  return ar;
}

void CGeneral::CellsLoop()
{
	CGeneral::CurRaftNum = 0;
	std::vector<CCell>::iterator raft_iter;
	raft_iter = CellArray.begin();
	CCell * p_Cell = raft_iter;

	for(; raft_iter  != CGeneral::CellArray.end(); raft_iter++)
	{
		p_Cell = raft_iter;

		if( !p_Cell->IsInUse()) 		// The Raft is not valid
		{
			continue;
		}


		p_Cell->Gillespie();

//		p_Cell->updateRIGI_rna_level();
//		p_Cell->updateRIGI_prot_level();

//		if(p_Cell->IsInfected())		{
//			p_Cell->updateIFN_rna_level();
//		}

		double IFN_rna_conc = p_Cell->GetIFN_rna_conc();
		if(p_Cell->IsInfected()){
			if(IFN_rna_conc>=1)
			{
				p_Cell->makeILs();
			}
		}


		CGeneral::CurRaftNum ++;


		

		int freeRNumber = p_Cell->Get_TypeIRnumber() - p_Cell->Get_boundTypeIR();
		p_Cell->m_IFN_binding_prob = Ppob_TypeR_Bind_IFNb * (double)grid.m_Grid[p_Cell->Location.y][p_Cell->Location.x].array[SM];
		for(int i=0; i<freeRNumber;i++){
			if(CGeneral::My_rand0_1() < p_Cell->m_IFN_binding_prob)		{
				p_Cell->Set_boundTypeIR(p_Cell->Get_boundTypeIR()+1);
				grid.m_Grid[p_Cell->Location.y][p_Cell->Location.x].array[SM]-=1;
			}
		}
		int boundRnumber = p_Cell->Get_boundTypeIR();
		for(i=0; i<boundRnumber;i++){
			if(CGeneral::My_rand0_1() < Ppob_TypeR_Unbind_IFNb )		{
				p_Cell->Set_boundTypeIR(p_Cell->Get_boundTypeIR()-1);
				grid.m_Grid[p_Cell->Location.y][p_Cell->Location.x].array[SM]+=1;
			}

		}
		p_Cell->updateRIGI_transcriptionRate();

	//	Validation(Raft);
	}
}


void CGeneral::SMsLoop()	{

	for(int in=0; in<GRID_SIZE ; in++)	{
		for(int in1=0; in1<GRID_SIZE ; in1++)		{
			int sm_mun = grid.m_Grid[in][in1].array[SM];
			for(int sm=0; sm<sm_mun ; sm++)
			{
				if(rg.Random() < Ppob_IFNb_die)  { //  condition for moving sm 
					grid.killSM(in, in1, 1); // 1 foe one molecule
				}
				else{
					if(rg.Random() < IFNb_D)  { //  condition for moving sm 
						Kind_of_Move move = Select_move();
	//					Kind_of_Move move = LEFT;

						grid.MoveSM(in, in1, move, 1);
					}
				}
			}

		}
	}
	for(in=0; in<GRID_SIZE ; in++)	{
		for(INT in1=0; in1<GRID_SIZE ; in1++)		{
			grid.m_Grid[in][in1].array[SM] += grid.m_Grid[in][in1].array[SM_tmp];
			grid.m_Grid[in][in1].array[SM_tmp]=0;
		}
	}

}

void CGeneral::R_SM_interaction(CReceptor & rec, int sm_id)
{
	/*
	CSigMol & sm = SMArray[sm_id];
	switch(rec.GetType())
	{
	case Syn:
		if( sm.GetType()==SNAP25)
		{
			syn_snap25encounters++;
			if( rg.Random() < Ppob_Syn_Bind_SNAP25)
			{
				rec.ChangeType(SynSnap25);
				rec.SetName("TypeIR-INFb");
				rec.SMStack.push(sm_id);
				grid.m_Grid[sm.Location.y][sm.Location.x].array[SM] = -1;
				sm.EraseFromList();	

				int ind = rec.GetCRaft();
				CRaft & raft = CGeneral::RaftArray[ind];
				raft.updateRIGI_transcriptionRate();


				prodoctive_syn_snap25encounters++;
			}
		}
		break;
	}
	*/
}

void CGeneral::R_R_interaction(CReceptor & rec, int r_id)
{
	CReceptor & rec_neighbor = RArray[r_id];
	R_Type r_type = rec.GetType();
	switch(r_type)
	{
	case Syn:
		if( rec_neighbor.GetType() == Syn)
		{
			syn_syn_encounters++;
			if( rg.Random() < Ppob_Syn_Bind_Syn)
			{
				rec.ChangeType(SynSyn);
				rec.SetName("Snt-Snt");
				rec_neighbor.EraseFromList();	
				rec.RStack.push(r_id);
				grid.m_Grid[rec_neighbor.CurrentLocation.y][rec_neighbor.CurrentLocation.x].array[Rec] = -1;
				prodoctive_syn_syn_encounters;
			}
		}
		break;
	case SynSyn:
		if( rec_neighbor.GetType() == Syn)
		{
			synSyn_syn_encounters++;
			if( rg.Random() < Ppob_SynSyn_Bind_Syn)
			{
				rec.ChangeType(SynSynSyn);
				rec.SetName("Snt-Snt-Snt");
				rec_neighbor.EraseFromList();	
				rec.RStack.push(r_id);
				grid.m_Grid[rec_neighbor.CurrentLocation.y][rec_neighbor.CurrentLocation.x].array[Rec] = -1;
				prodoctive_synSyn_syn_encounters++;
			}
		}
		break;
	}
}


void CGeneral::ComplexDissociation(CReceptor & rec, bool is_spont)
{
	R_Type r_type = rec.GetType();
	switch(r_type)
	{
	case SynSyn:
		{
			if(is_spont)
				if( rg.Random() > Ppob_SynSyn_Dissociation)
					break;

			int index;
			if(!rec.RStack.empty()){
				index = rec.RStack.top();
				CReceptor & r = RArray[index];
				rec.RStack.pop();
				if( !LocateRecOnGrid(r, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
				{
					BindReceptorToGrid(r);
					_ASSERTE(0);
				}
			}
			else{
				index = RArray.size();
				CReceptor r_object(index, Syn);
				CReceptor & r = r_object;
				if( !LocateRecOnGrid(r, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
				{
					BindReceptorToGrid(r);
					_ASSERTE(0);
				}
				tmpRArray.push_back(r_object);
			}
			rec.ChangeType(Syn);
			rec.SetName("Snt");

			syn_snap25_diss++;
		}
		break;

	case SynSynSyn:
		{
			if(is_spont)
				if( rg.Random() > Ppob_SynSynSyn_Dissociation)
					break;

			int index;
			if(!rec.RStack.empty()){
				index = rec.RStack.top();
				CReceptor & r = RArray[index];
				rec.RStack.pop();
				if( !LocateRecOnGrid(r, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
				{
					BindReceptorToGrid(r);
					_ASSERTE(0);
				}
			}
			else{
				index = RArray.size();
				CReceptor r_object(index, SynSyn);
				CReceptor & r = r_object;
				if( !LocateRecOnGrid(r, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
				{
					BindReceptorToGrid(r);
					_ASSERTE(0);
				}
				RArray.push_back(r_object);
			}
			rec.ChangeType(Syn);
			rec.SetName("Snt-Snt");

			syn_snap25_diss++;
		}
		break;

	case SynSnap25:
		{
			if(is_spont)
				if( rg.Random() > Ppob_SynSNAP25_Dissociation)
					break;

			int index;
			if(!rec.SMStack.empty()){
				index = rec.SMStack.top();
				CSigMol & sm = SMArray[index];
				rec.SMStack.pop();
				if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
				{
					BindSigMolToGrid(sm);
					_ASSERTE(0);
				}
			}
			else{
				index = SMArray.size();
				CSigMol sm_object(index, SNAP25);
				CSigMol & sm = sm_object;
				if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
				{
					BindSigMolToGrid(sm);
					_ASSERTE(0);
				}
				SMArray.push_back(sm_object);
			}
			rec.ChangeType(Syn);
			rec.SetName("Snt");

			syn_snap25_diss++;
		}
		break;

	case SynSnap25Vamp:
		{
			if(is_spont)
			{
				if( rg.Random() < Ppob_SynSNAP25Vamp_Dissociation)
				{
					int index;
					if(!rec.SMStack.empty()){
						index = rec.SMStack.top();
						CSigMol & sm = SMArray[index];
						rec.SMStack.pop();
						if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
						{
							BindSigMolToGrid(sm);
							_ASSERTE(0);
						}
					}
					else{
						index = SMArray.size();
						CSigMol sm_object(index, Vamp);
						CSigMol & sm = sm_object;
						if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
						{
							BindSigMolToGrid(sm);
							_ASSERTE(0);
						}
						SMArray.push_back(sm_object);
					}
					rec.ChangeType(SynSnap25);
					rec.SetName("Snt-Snap25");

					binary_Vamp_diss++;
				}
			}
			else//NSF action
			{
				int index;
				if(!rec.SMStack.empty()){
					index = rec.SMStack.top();
					CSigMol & sm = SMArray[index];
					rec.SMStack.pop();
					if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
					{
						BindSigMolToGrid(sm);
						_ASSERTE(0);
					}
				}
				else{
					index = SMArray.size();
					CSigMol sm_object(index, Vamp);
					CSigMol & sm = sm_object;
					if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
					{
						BindSigMolToGrid(sm);
						_ASSERTE(0);
					}
					SMArray.push_back(sm_object);
				}
				rec.ChangeType(SynSnap25);
				rec.SetName("Snt-Snap25");
				ComplexDissociation(rec, false); //for not spontanuos dissoc

				binary_Vamp_diss++;
			}
		}
		break;
	case SynSnap25VampAlpha:
		{
			if(is_spont)
			{
				if( rg.Random() < Ppob_SynSNAP25VampAlpha_Dissociation)
				{
					int index;
					if(!rec.SMStack.empty()){
						index = rec.SMStack.top();
						CSigMol & sm = SMArray[index];
						rec.SMStack.pop();
						if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
						{
							BindSigMolToGrid(sm);
							_ASSERTE(0);
						}
					}
					else {
						index = SMArray.size();
						CSigMol sm_object(index, Alpha);
						CSigMol & sm = sm_object;
						if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
						{
							BindSigMolToGrid(sm);
							_ASSERTE(0);
						}
						SMArray.push_back(sm_object);
					}
					rec.ChangeType(SynSnap25Vamp);
					rec.SetName("Snt-Snap25-Vamp");

					SNAR_SNAP_diss++;
				}
			}
			else//NSF action
			{
				if(is_delete_complexes){
					rec.Clear();
				}
				else{
					int index;
					if(!rec.SMStack.empty()){
						index = rec.SMStack.top();
						CSigMol & sm = SMArray[index];
						rec.SMStack.pop();
						if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
						{
							BindSigMolToGrid(sm);
							_ASSERTE(0);
						}
					}
					else{
						index = SMArray.size();
						CSigMol sm_object(index, Alpha);
						CSigMol & sm = sm_object;
						if( !LocateSMOnGrid(sm, CPoint(rec.CurrentLocation.x, rec.CurrentLocation.y)) )
						{
							BindSigMolToGrid(sm);
							_ASSERTE(0);
						}
						SMArray.push_back(sm_object);
					}
					rec.ChangeType(SynSnap25Vamp);
					rec.SetName("Snt-Snap25-Vamp");

					SNAR_SNAP_diss++;
					ComplexDissociation(rec, false); //for not spontanuos dissoc

				}
			}
		}
		break;
	}
}

bool CGeneral::Is_attachedSM_canMove(Kind_of_Move KindOfMove, int rec_index)
{
	bool is_can_move = true;
	int sm_index_to_set = RArray[rec_index].A_B_SM_Indexes.x;
	if( sm_index_to_set != -1)
	{
		if( ! SMArray[sm_index_to_set].IsCanMove(KindOfMove, 1))
			is_can_move = false;	
	} // if	     
	sm_index_to_set = RArray[rec_index].A_B_SM_Indexes.y;
	if( sm_index_to_set != -1)
	{
		if( ! SMArray[sm_index_to_set].IsCanMove(KindOfMove, 1))
			is_can_move = false;	
	} // if	     
	return is_can_move;
}




double CGeneral::box_muller(double m, double s)	/* normal random variate generator */
{				        /* mean m, standard deviation s */
	double x1, x2, w, y1;
	static double y2;
	static int use_last = 0;
	
	if (use_last)		        /* use value from previous call */
	{
		y1 = y2;
		use_last = 0;
	}
	else
	{
		do {
//			x1 = 2.0 * Uniform() - 1.0;
//			x2 = 2.0 * Uniform() - 1.0;
			x1 = 2.0 * CGeneral::My_rand(0, 1) - 1.0;
			x2 = 2.0 * CGeneral::My_rand(0, 1) - 1.0;
			w = x1 * x1 + x2 * x2;
		} while ( w >= 1.0 );
		
		w = sqrt( (-2.0 * log( w ) ) / w );
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}
	
	return( m + y1 * s );
}


double CGeneral::LogNormal(double mean, double stdv)
{
	double zm = mean*mean;
	double zs = stdv*stdv;
	return(exp(CGeneral::box_muller(log(zm/sqrt(zs + zm)), sqrt(log(zs/zm+1)) )));
//	return(exp(Normal(log(zm/sqrt(zs + zm)), sqrt(log(zs/zm+1)) )));
}


int CGeneral::IntRand(int min, int max)
{
	int ird = rand();
	double rd = (ird < RAND_MAX) ? ird : ird -.0001;
	return min + (int) floor((rd / RAND_MAX) * (max - min + 1));
}





void CGeneral::MovingReceptors()
{
	for(int index=0; index<RArray.size(); index++)
	{
		CReceptor & rec = RArray[index];
		if( !rec.IsInUse() )
		{
			continue;
		} // if	R is not in use         
		
		if(rg.Random() < rec.GetD())   //  condition for moving receptor 
		{
			Kind_of_Move move = Select_move();
			if(!rec.Move(move, false)) continue; // false for self moving
	
		}
	}
}

int CGeneral::GetId_in_SM_ProfileVec(CString type)
{
	int ret = -1;
/*    std::vector<CSMprofile> ::iterator iter;    //
	iter = SMprofileVec.begin();
    for (int i=0; iter != SMprofileVec.end(); iter++, i++) 
	{
		CString profileType = iter->GetType();
		profileType.MakeLower();
		if(profileType == type)
			ret = i;
	}
*/	return ret;	
}

int CGeneral::GetId_in_R_ProfileVec(CString type)
{
	int ret = -1;
/*    std::vector<CRprofile> ::iterator iter;    //
	iter = R_ProfileVec.begin();
    for (int i=0; iter != R_ProfileVec.end(); iter++, i++) 
	{
		CString profileType = iter->GetType();
		profileType.MakeLower();
		if(profileType == type)
			ret = i;
	}
*/	return ret;	
}
void CGeneral::stopProducingIFN()
{
	/*
	std::vector<CRaft>::iterator raft_iter;
	raft_iter = RaftArray.begin();
	CRaft * p_Raft = raft_iter;
	IndexVec indV;
	for(; raft_iter  != CGeneral::RaftArray.end(); raft_iter++)
	{
		p_Raft = raft_iter;

		if( !p_Raft->IsInUse()) 		// The Raft is not valid
		{
			continue;
		}
		p_Raft->m_ilType2rate_map[SNAP25] = 0;
	}
	*/
}
void CGeneral::InitCells(int raft_number)
{
	for(int index=0; index < raft_number; index++)
	{
		CreateCell(index);

	}
}
void CGeneral::CreateCell(int in_index)
{
	int index;
	if(in_index == -1)
	{
		/*
		while( ! delRaftStack.empty() )
		{
			index = delRaftStack.top();
			delRaftStack.pop();
			CRaft Raft_Object(index);  
			RaftArray[index] = Raft_Object;
			polygonFill(Raft_Object.m_shape.GetPtVec() ,Raft_Object.m_shape.Count(), index );
		} // while	         
		*/
	}
	else
	{
		index = in_index;
		CCell Raft_Object(index);  
		CellArray.push_back(Raft_Object);
	}
}

double CGeneral::Bin(int n,double p,int r)
{
    return fac(n)/(fac(n-r)*fac(r))*pow(p,r)*pow(1-p,n-r);
}

double CGeneral::fac(int n)
{
    double t=1;
    for (int i=n;i>1;i--)
        t*=i;
    return t;
}