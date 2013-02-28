// General.h: interface for the CGeneral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERAL_H__BABCFB3B_5BDE_4BF3_BA77_F789FED90CF4__INCLUDED_)
#define AFX_GENERAL_H__BABCFB3B_5BDE_4BF3_BA77_F789FED90CF4__INCLUDED_

#if _MSC_VER > 100
#pragma once

#endif // _MSC_VER > 1000
#include "RProfile.h"
#include "SMprofile.h"
#include "Rprofile.h"
#include <map>
#include <queue>
#include <string>
#include "randomc.h"                   // define classes for random number generators
#include "ResultsTemplate.h"                   // define classes for random number generators
#include "MatlabEng.h"


#define GRID_SIZE  40
//#define GRID_SIZE  90
//#define RECEPTOR_NUMBER 10
#define RECEPTOR_NUMBER 1000
#define RES_GRID_UNIT_LENGTH 5

#define R_TYPES_NUMBER 10
#define SM_TYPES_NUMBER 40
#define AG_TYPES_NUMBER 10


#define M_PI 3.14159265358979323846
//#define RAFT_UPLOAD_RATE 10 //RAFT_UPLOAD_RATE is active
#define RAFT_UPLOAD_RATE 1000000 //RAFT_UPLOAD_RATE is not active
//#define RECEPTOR_UPLOAD_RATE 10 //RECEPTOR_UPLOAD_RATE is active
#define RECEPTOR_UPLOAD_RATE 1000000 //RAFT_UPLOAD_RATE is not active
//#define SM_UPLOAD_RATE 10 //SM_UPLOAD_RATE is active
#define SM_UPLOAD_RATE 10000000 //RECEPTOR_UPLOAD_RATE is not active
#define ENDOCYTOSIS_THRESHOLD 10.1 // ENDOCYTOSIS is active 
#define RAFT_DISS_RATE 0 // RAFT_DISSOTIATION is not active 
#define RAFT_VERTEXES_NUMBER 8 // 

#define is_multivalent_hapten false // 
#define is_create_sm_attached_rec false // 
#define SM_BINDING_RULE 0 // '0' is to allow the SM and the same localisation

#define  BUFSIZE 2048

typedef vector<int> IndexVec;
typedef vector<int>::iterator iterIndexVec;
typedef vector<double>doublesVec;
typedef vector<double>::iterator double_iter;
typedef vector<CResultsTemplate> ResultsVector;
typedef CSMprofile SMprofileVector[SM_TYPES_NUMBER];
typedef CRProfile RprofileVector[R_TYPES_NUMBER];
typedef stack<int> IndexStack;

class CGrid;
class CReceptor;
class CCell;
class CSigMol;
class CRprofile;
class CSMprofile;

class CGeneral  
{
	
public:
	//////  functions declaration ///////////////////////////////
	static void Validation(LatticeUnitSubType);
	static int CalculateRaftNumber();
	static void InitProcess();
	static void Fill_R_Profile();
	static void R_R_interaction(CReceptor &, int);
	static void Fill_SM_Profile();
	static void Calculate_protein_concentrations();
	static void Record_Results_to_files1();
	static void CalculateMSD(int time_step);
	static void Record_Results_to_files();
	static double My_rand(double min, double max);
	static double My_rand0_1();
	static Kind_of_Move Select_move();
	static int BeginSimulation();
	static int PtInRaft(CPoint & pt, int & l, int CurRaftNum );
	static int PtInRaft(CPoint & pt, int CurRaftNum);
	static int DimentionSquareDistrib();
	static void InitRafts(int);
	static void InitCells(int);
	static void MovingReceptors();
	static void R_SM_interaction(CReceptor &, int);
	static void ComplexDissociation(CReceptor &, bool);
	static void RaftsLoop();
	static void CellsLoop();
	static void SMsLoop();
	static const double * Gillespie(const CCell *);
	static void CreateRaft(int);
	static void CreateCell(int);
	static void CreateReceptor();
	static void CreateSigMol(SM_Type type);
	static void MakeSigMol(int,SM_Type type, CPoint);
	static void GenerateSigMol();
	static void BindReceptorToGrid(CReceptor &);
	static void BindSigMolToGrid(CSigMol &);
	static bool LocateRecOnGrid(CReceptor &, CPoint);
	static bool LocateSMOnGrid(CSigMol &, CPoint);
	static void InitReceptors();
	static void ChangeLocation_of_attachedSM(Kind_of_Move, int);
	static bool Is_attachedSM_canMove(Kind_of_Move, int);
	static void InitSigMol();
	static double LogNormal(double mean, double stdv);
	static double Bin(int n,double p,int r);
	static double fac(int n);
	static double box_muller(double m, double s);
	static int IntRand(int min, int max);
	static void makedist();
	static void stopProducingIFN();
	static int Dimentionsquardistrib();
	static CPoint GetPt(Kind_of_Move , int );
	static int GetId_in_SM_ProfileVec(CString);
	static int GetId_in_R_ProfileVec(CString);
	CGeneral();
	virtual ~CGeneral();
	//---------------- end of functions declaration ------------//

	//////////////////  variables declaration  /////////////////


//	static int GRID_SIZE;
	static int TIME_STEP_NUMBER;
	static int step;
	static bool  debug_version;
	static bool  plusAB;
	static bool  TWmodel;
	static bool  stopProducingIFN_flag;
	static bool  START_SIM;
	static bool  DrawRecIndexes;
	static bool  DrawRafts;
	static bool  DrawRaftIndexes;
	static bool  DrawReceptors;
	static bool  DrawSigMol;
	static bool  DrawSigMolNames;
	static bool  DrawRecNames;
	static bool  DrawSigMolInd;
	static bool  DrawAgs;
	static bool  DrawAgIndexes;
	static CGrid grid;

	static std::vector<CReceptor> RArray;
	static std::vector<CReceptor> tmpRArray;
	static std::vector<CCell> CellArray;
	static std::vector<CSigMol> SMArray;
	static std::vector<CPoint> Results_of_R_in_out_ratio_Array;
	static doublesVec R_SM_binding_durations_Vec;
	static std::vector<CPoint> Results_of_R_SM_complex_in_out_ratio_Array;
	static ResultsVector R_SM_interaction_results_Array;
	static ResultsVector Protein_concentration_results_Array;
	static std::vector<CPoint> MSDResultsArray;
	static std::queue<SM_Type> EndocytosedSMQueue;
	static RprofileVector RprofileVec;
	static SMprofileVector SMprofileVec;
	static int count_receptor_leave_the_raft;
	static int count_receptor_enter_the_raft;
//	static int RecMSDResults[RECEPTOR_NUMBER];
	static ifstream input; 
	static ofstream out;
	static ofstream out_singleCells_concentrations;
	static ofstream out_TS_concentrations;
	static ofstream out_singleCells_rates;
	static ofstream out_TS_rates;
	static ofstream gillaspieLog;

	static int	UpdateWindowVariable;
	static int	TimerInitialisator;
	static int Simulation_Duration;

	static int Recepter_Number;
	static int RecInRaft;

	static double RAFT_SURFACE_COVERAGE_PERCENT;
	static double RAFT_DIFFUSION_COEFICIENT;
	static double IFNb_D;
	static int TIME_STEP_LENGHT;
	static double UPPER_LIMIT_TIME_STEP_LENGHT;
	static int SIMULATION_DURATION_IN_HOURS;
	static double RAFT_DIFFUSION_COEFICIENT_OF_ACTIVE_RAFT;
	static int RAFT_NUMBER;
	static int MEAN_RAFT_SIZE;
	static int CurRaftNum ;
	static double RAFT_PROBABILITY_TO_MERGE;
	static double RIGI_prot_maxLevel;
	static double RIGI_rna_maxLevel;
	static double max_transcriptionRateC;
	static double max_translationRateC;
	static double typical_prot_degradationRateC;
	static double typical_rna_degradationRateC;
	static double IFN_prot_maxLevel;
	static double IFN_rna_maxLevel;
	static double IFN_rna_activation_hillCoef ;
	static double DDX58_rna_activation_hillCoef ;
	static int IFN_prot_secretion_Threshould ;
	static int IFN_protein_secretion_hillCoef ;
	static double infectivityThreshould;
	static double Ppob_TypeR_Bind_IFNb;
	static double Ppob_TypeR_Unbind_IFNb;
	static double Ppob_IFNb_die;

	static int Glob_raft_ID ;
	static int CurSMNum ;
	static int raft_endoc_events_num ;
	static IndexStack delRecStack;
	static IndexStack delRaftStack;
	static IndexStack delSMStack;

	static bool is_draw_finished;
	static bool is_simul_finished;
	static bool is_draw_rec_path;

	static bool is_delete_complexes;

	static double	D_Stx;
	static double	D_SNAP25;
	static double	D_Vamp;

	static double	D_NSF;
	static int t_NSF_up ;
	static double	Ptransloc_NSF;
	static double	D_ALPHA;
	static int t_ALPHA_up ;
	static double	Ptransloc_Alpha;

	static double	D_Stx_inRaft;
	static double	D_SNAP25_inRaft;
	static double	D_Vamp_inRaft;

	static int	max_typeIRNumber ;

	static int	initSntNumber ;
	static int	initSntSntNumber ;
	static int	initSntSntSntNumber ;
	static int	initSNAP25Number ;
	static int	initNSFNumber ;
	static int	initAlphaNumber ;
	static int	initVampNumber; 
	static int	initSynSnap25; 
	static int	initSynSnap25Vamp; 
	static int	initSynSnap25VampAlpha; 

	static double	InitInRaftFractionSnt ;
	static double	InitInRaftFractionSntSnt ;
	static double	InitInRaftFractionSntSntSnt ;
	static double	InitInRaftFractionSNAP25;
	static double	InitInRaftFractionNSF ;
	static double	InitInRaftFractionAlpha ;
	static double	InitInRaftFractionVamp ;
	static double	InitInRaftFractionSynSnap25 ;
	static double	InitInRaftFractionSynSnap25Vamp ;
	static double	InitInRaftFractionSynSnap25VampAlpha ;

	static double	Pin_Stx;
	static double	Pin_SNAP25;
	static double	Pin_Vamp;
	static double	Pout_Stx;
	static double	Pout_SNAP25;
	static double	Pout_Vamp;

	static double	Pin_SynSyn ;
	static double	Pin_SynSynSyn ;
	static double	Pin_SynSnap25 ;
	static double	Pin_SynSnap25Vamp ;
	static double	Pin_SynSnap25VampAlpha ;
	static double	Pout_SynSyn ;
	static double	Pout_SynSynSyn ;
	static double	Pout_SynSnap25 ;
	static double	Pout_SynSnap25Vamp;
	static double	Pout_SynSnap25VampAlpha;

	static double Ppob_Syn_Bind_Syn;
	static double Ppob_SynSyn_Bind_Syn;
	static double Ppob_SynSyn_Dissociation;
	static double Ppob_SynSynSyn_Dissociation;
	static double Ppob_Syn_Bind_SNAP25;
	static double Ppob_SynSNAP25_BindVamp;
	static double Ppob_SynSNAP25Vamp_BindAlpha;
	static double Ppob_NSF_diss_SynSNAP25VampAlpha;
	static double Ppob_SynSNAP25_Dissociation;
	static double Ppob_SynSNAP25Vamp_Dissociation;
	static double Ppob_SynSNAP25VampAlpha_Dissociation;

	static int	syn_snap25encounters; 
	static int	syn_syn_encounters; 
	static int	synSyn_syn_encounters; 
	static int	binary_Vamp_encounters; 
	static int	SNAR_SNAP_encounters; 
	static int	prodoctive_syn_snap25encounters; 
	static int	prodoctive_binary_Vamp_encounters; 
	static int	prodoctive_SNAR_SNAP_encounters; 
	static int	prodoctive_syn_syn_encounters; 
	static int	prodoctive_synSyn_syn_encounters; 
	static int	syn_snap25_diss; 
	static int	binary_Vamp_diss; 
	static int	SNAR_SNAP_diss; 
	static int	syn_syn_diss; 
	static int	syn_syn_syn_diss; 

	static int lastSMindex;
	//---------------- end of variables declaration ------------//

};

#endif // !defined(AFX_GENERAL_H__BABCFB3B_5BDE_4BF3_BA77_F789FED90CF4__INCLUDED_)
