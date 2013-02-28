// Cell.cpp: implementation of the CCell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "surface.h"
#include "Cell.h"
#include "General.h"
#include "Grid.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCell::CCell(int arInd)
{
	m_use = true;
//	m_visible = true;

    m_index = arInd ;
	
	

	if( CGeneral::step > 0)
		is_initialized_right_now = true;
	else
		is_initialized_right_now = false;

//		m_RIGI_rna_conc = 200;
//		m_RIGI_rna_conc = CGeneral::LogNormal(5,5);

	double p = CGeneral::My_rand0_1();
	if(p < CGeneral::infectivityThreshould)
		m_isInfected = true;
	else
		m_isInfected = false;	

	do{
		m_RIGI_rna_conc = CGeneral::LogNormal(5,50);
	}
	while(m_RIGI_rna_conc <= 0);
	

//	while(m_RIGI_rna_conc <= 0 || m_RIGI_rna_conc >= 1);
	m_RIGI_rna_conc = floor(m_RIGI_rna_conc);
	m_RIGI_prot_conc = m_RIGI_rna_conc*10;
//	m_IFN_rna_conc = 0.0001;
//	m_IFN_rna_conc = (m_isInfected==true)?0:CGeneral::My_rand(1, 10);
	m_IFN_rna_conc = (m_isInfected==true)?0:0;
//	m_IFN_rna_conc = CGeneral::My_rand(1, 10);
	m_boundTypeIR = 0;
	m_TypeIRnumber = CGeneral::max_typeIRNumber;

	m_RIGI_min_transcriptionRate = CGeneral::typical_rna_degradationRateC*10*2;
	m_RIGI_transcriptionRate = m_RIGI_min_transcriptionRate;
	m_RIGI_rna_degradationRate = CGeneral::typical_rna_degradationRateC;

	m_RIGI_translationRate = CGeneral::max_translationRateC;
	m_RIGI_protein_degradationRate = CGeneral::typical_prot_degradationRateC;

	m_IFN_max_transcriptionRate = CGeneral::max_transcriptionRateC;
	m_IFN_min_transcriptionRate = 0;
//	m_IFN_min_transcriptionRate = m_IFN_max_transcriptionRate/100;
	if(m_isInfected){
		m_pt2updateIFNfunction = &CCell::updateIFN_transcriptionRate;
	}
	else
	{
		m_IFN_rna_transcriptionRate = 0;
		m_pt2updateIFNfunction = &CCell::updateIFN_transcriptionRate_for_NA_cell;
	}
	m_IFN_translationRate =	m_RIGI_translationRate/10;
	m_IFN_rna_degradationRate = m_IFN_min_transcriptionRate/10;
//	m_IFN_rna_degradationRate = 0;
	m_IFN_protein_degradationRate = 0;

	m_IFN_rna_activationCoef = 1./7000.;
	m_DDX58_rna_activationCoef = (CGeneral::TWmodel)? 1./50 :1./150;
	m_IFN_protein_secretionCoef = 1./90 * CGeneral::TIME_STEP_LENGHT*100;
	m_justChangedStatus = false;
//	m_IFN_protein_secretionRate = 0.01*100;
	m_ilType2rate_map[SNAP25] = m_IFN_protein_secretionRate;

	m_activationStep = -1;

	//	static int size=4;
//	static bool is_more_than_4_vertexes = false;

	m_IFN_binding_prob = 0*0;
	m_IFN_unbinding_prob = 0;

	m_blinking_const = 70;
	m_blinking_counter = 0;

	do{
		m_RIGI_max_transcriptionRate = CGeneral::box_muller(0.02,0.1);
//		m_RIGI_max_transcriptionRate = 0.01;
	}
	while(m_RIGI_max_transcriptionRate <= 0.01 || m_RIGI_max_transcriptionRate > CGeneral::max_transcriptionRateC );
//	while(m_RIGI_max_transcriptionRate < 0.00001 || m_RIGI_max_transcriptionRate > CGeneral::max_transcriptionRateC );

/*
	do{
		m_IFN_max_transcriptionRate = CGeneral::box_muller(0.05,0.05);
//		m_RIGI_max_transcriptionRate = 0.01;
	}
	while(m_IFN_max_transcriptionRate <= m_IFN_min_transcriptionRate || m_IFN_max_transcriptionRate > CGeneral::max_transcriptionRateC );
//	while(m_RIGI_max_transcriptionRate < 0.00001 || m_RIGI_max_transcriptionRate > CGeneral::max_transcriptionRateC );
*/


	int attempt_count1 = 0;
	while(1)
	{
		if(attempt_count1++ > 300000 )
		{
			CGeneral::START_SIM = false;
			throw(-3);
		}

		Location.x = rand()%GRID_SIZE;
		Location.y = rand()%GRID_SIZE;
		if(CGeneral::grid.m_Grid[Location.y] [Location.x].array[Cell] == -1) //free place
		{
			break;
		}
	}
	CGeneral::grid.m_Grid[Location.y][Location.x].array[Cell] = m_index;

	m_gillaspieAuxiliary.m_NUM_OF_RATES = NUM_OF_RATES;
	m_gillaspieAuxiliary.deltaT = 10e9;

//	makeRatesVector();
	(this->*m_pt2updateIFNfunction)();

}

CCell::CCell(const CCell & raft)
{
	if(this == & raft) return;
//	m_visible = raft.m_visible;

	m_use = raft.m_use;
	m_index = raft.m_index;
	Location = raft.Location;

	if( CGeneral::step > 0)
		is_initialized_right_now = true;
	else
		is_initialized_right_now = false;

	m_RIGI_prot_conc = raft.m_RIGI_prot_conc;
	m_IFN_prot_conc = raft.m_IFN_prot_conc;
	m_RIGI_rna_conc = raft.m_RIGI_rna_conc;
	m_IFN_rna_conc = raft.m_IFN_rna_conc;
	m_boundTypeIR = raft.m_boundTypeIR;
	m_TypeIRnumber = raft.m_TypeIRnumber;

	m_RIGI_max_transcriptionRate = raft.m_RIGI_max_transcriptionRate;
	m_RIGI_min_transcriptionRate = raft.m_RIGI_min_transcriptionRate;
	m_RIGI_transcriptionRate = raft.m_RIGI_transcriptionRate;
	m_RIGI_translationRate = raft.m_RIGI_translationRate;
	m_RIGI_rna_degradationRate = raft.m_RIGI_rna_degradationRate;
	m_RIGI_protein_degradationRate = raft.m_RIGI_protein_degradationRate;

	m_IFN_max_transcriptionRate = raft.m_IFN_max_transcriptionRate;
	m_IFN_min_transcriptionRate = raft.m_IFN_min_transcriptionRate;
	m_IFN_rna_transcriptionRate = raft.m_IFN_rna_transcriptionRate;
	m_IFN_translationRate = raft.m_IFN_translationRate;
	m_IFN_protein_degradationRate = raft.m_IFN_protein_degradationRate;
	m_IFN_rna_degradationRate = raft.m_IFN_rna_degradationRate;

	
	m_DDX58_rna_activationCoef = raft.m_DDX58_rna_activationCoef;
	m_IFN_rna_activationCoef = raft.m_IFN_rna_activationCoef;
	m_IFN_protein_secretionCoef = raft.m_IFN_protein_secretionCoef;
	m_IFN_protein_secretionRate = raft.m_IFN_protein_secretionRate;

	m_activationStep = raft.m_activationStep;
	m_justChangedStatus = raft.m_justChangedStatus;
	m_ilType2rate_map = raft.m_ilType2rate_map;
	m_isInfected = raft.m_isInfected;
	m_blinking_const = raft.m_blinking_const;
	m_blinking_counter = raft.m_blinking_counter;

	m_IFN_binding_prob = raft.m_IFN_binding_prob;
	m_IFN_unbinding_prob = raft.m_IFN_unbinding_prob;

	m_gillaspieAuxiliary.m_NUM_OF_RATES = raft.m_gillaspieAuxiliary.m_NUM_OF_RATES;
	m_gillaspieAuxiliary.deltaT = raft.m_gillaspieAuxiliary.deltaT;
	m_gillaspieAuxiliary.type = raft.m_gillaspieAuxiliary.type;

    /*
	for (int i=0; i<m_NUM_OF_RATES; i++){
  		 m_rates[i] = raft.m_rates[i];
	}
	*/
	//m_rates = raft.m_rates;
	//makeRatesVector();

	m_pt2updateIFNfunction = raft.m_pt2updateIFNfunction;
}

CCell::~CCell()
{

}
void CCell::makeILs() 
{
	if(CGeneral::My_rand0_1() < m_IFN_protein_secretionCoef){
		CGeneral::grid.m_Grid[Location.y] [Location.x].array[SM] += m_IFN_rna_conc;
	}

}	
/*
void CCell::makeILs() 
{
	mapSM_Type2double_iterator it = m_ilType2rate_map.begin();
    for(;it != m_ilType2rate_map.end(); it++ )    // not found
	{
		double rate = (*it).second;

		double C_inpower_h = pow(m_IFN_prot_conc, CGeneral::IFN_protein_secretion_hillCoef);
		double C_inpower_h_times_IFN_protein_secretionCoef = m_IFN_protein_secretionCoef * C_inpower_h;
		double hForm = C_inpower_h_times_IFN_protein_secretionCoef/
			(1 + C_inpower_h_times_IFN_protein_secretionCoef);
		double p = hForm * rate;

//		double p1 = rate*(m_IFN_prot_conc * m_IFN_protein_secretionCoef)/(1+m_IFN_prot_conc * m_IFN_protein_secretionCoef);
//		assert(p==p1);
		if(CGeneral::My_rand0_1() < p)
//		CGeneral::MakeSigMol(-1, (*it).first, m_shape.Centroid());
		CGeneral::MakeSigMol(-1, (*it).first, Location);
	}

}	
*/
void CCell::updateRIGI_transcriptionRate()
{
//	double fractionBound = (double)(m_boundTypeIR==0)? 0 : (double)m_boundTypeIR/(double)m_TypeIRnumber;
	double C_inpower_h_times_DDX58_rna_activationCoef = 
		pow(m_DDX58_rna_activationCoef*m_boundTypeIR, CGeneral::DDX58_rna_activation_hillCoef);
//	double C_inpower_h = pow(fractionBound,CGeneral::DDX58_rna_activation_hillCoef);
//	double C_inpower_h_times_DDX58_rna_activationCoef = C_inpower_h * m_DDX58_rna_activationCoef;
	double hForm = C_inpower_h_times_DDX58_rna_activationCoef/
		(1 + C_inpower_h_times_DDX58_rna_activationCoef);
	assert(hForm<=1);
	m_RIGI_transcriptionRate = m_RIGI_min_transcriptionRate + hForm * m_RIGI_max_transcriptionRate;
	assert(m_RIGI_min_transcriptionRate<=m_RIGI_transcriptionRate);
//	assert(m_RIGI_min_transcriptionRate<=hForm);
}

void CCell::updateRIGI_rna_level() 
{
//	if(m_isInfected)
	if(1)
	{
		if(CGeneral::My_rand0_1() < m_RIGI_transcriptionRate)
		{
			m_RIGI_rna_conc++;
		}

		int molNumber = m_RIGI_rna_conc;
		for(int i=0; i<molNumber;i++){
			if(CGeneral::My_rand0_1() < m_RIGI_rna_degradationRate)		{
				m_RIGI_rna_conc -= (m_RIGI_rna_conc<1)? 0 : 1;
			}
		}

	}
}	

void CCell::updateRIGI_prot_level()
{
	if(CGeneral::My_rand0_1() < m_RIGI_translationRate )
	{
		m_RIGI_prot_conc += m_RIGI_rna_conc ;
	}
	int molNumber = m_RIGI_prot_conc;
	for(int i=0; i<molNumber;i++){
		if(CGeneral::My_rand0_1() < m_RIGI_protein_degradationRate)		{
			m_RIGI_prot_conc -= (m_RIGI_prot_conc<1)? 0 : 1;
		}
	}
}

void CCell::updateIFN_rna_level()
{
	double C_inpower_h_times_IFN_rna_activationCoef = m_IFN_min_transcriptionRate + 
		pow(m_IFN_rna_activationCoef*m_RIGI_prot_conc,CGeneral::IFN_rna_activation_hillCoef);
//	double C_inpower_h_times_IFN_rna_activationCoef = C_inpower_h * ;
	double hForm = C_inpower_h_times_IFN_rna_activationCoef/
		(1 + C_inpower_h_times_IFN_rna_activationCoef);
	assert(hForm<=1);
	m_IFN_rna_transcriptionRate = hForm * CGeneral::max_transcriptionRateC;
/*
	if(CGeneral::My_rand0_1() < m_IFN_rna_transcriptionRate)	{
		m_IFN_rna_conc++;
	}
	int molNumber = m_IFN_rna_conc;
	for(int i=0; i<molNumber;i++){
		if(CGeneral::My_rand0_1() < m_IFN_rna_degradationRate)		{
			m_IFN_rna_conc -= (m_IFN_rna_conc<1)? 0 : 1;
		}
	}
*/
}

void CCell::updateIFN_transcriptionRate()
{
	assert(m_isInfected);
	double C_inpower_h_times_IFN_rna_activationCoef = 
		pow(m_IFN_rna_activationCoef*m_RIGI_prot_conc,CGeneral::IFN_rna_activation_hillCoef);
//	double C_inpower_h_times_IFN_rna_activationCoef = C_inpower_h * ;
	double hForm = C_inpower_h_times_IFN_rna_activationCoef/
		(1 + C_inpower_h_times_IFN_rna_activationCoef);
	assert(hForm<=1);
	m_IFN_rna_transcriptionRate = m_IFN_min_transcriptionRate + hForm * m_IFN_max_transcriptionRate;
}


void CCell::updateIFN_transcriptionRate_for_NA_cell()
{
	return;
}

void CCell::updateIFN_protein_level()
{
	if(CGeneral::My_rand0_1() < m_IFN_translationRate)
	{
		m_IFN_prot_conc += m_IFN_rna_conc;
	}
	if(CGeneral::My_rand0_1() < m_IFN_protein_degradationRate * m_IFN_prot_conc)
	{
		m_IFN_prot_conc -= (m_IFN_prot_conc<1)? 0 : 1;
	
	}

}

void CCell::updateState(RateType type)
{
	switch(type)
	{
	case RIGI_transcriptionRate:
		m_RIGI_rna_conc++;
		break;
	case RIGI_rna_degradationRate:
		m_RIGI_rna_conc -= 1; assert(m_RIGI_rna_conc>=0);
		break;
	case RIGI_translationRate :
		m_RIGI_prot_conc++;
		break;
	case RIGI_protein_degradationRate:
		m_RIGI_prot_conc -= 1; assert(m_RIGI_prot_conc>=0);
		break;
	case IFN_rna_transcriptionRate:
		m_IFN_rna_conc++;
		break;
	case IFN_rna_degradationRate:
		m_IFN_rna_conc -= 1; assert(m_IFN_rna_conc>=0);
		break;
	}

}

void CCell::Gillespie()
{
	static int GilSteps = 10e10;
	double elapsedT=0; // needed for cases where the Gillaspie deltaT is smaller then the MC step and therefore more than one Gillaspie can happen within one MC step
	bool event_can_happen= true; // will be set to false if the Gillaspie's deltaT will be longer than the MC step remaining time 
	do {
		makeRatesVector();
		const double * ar =  CGeneral::Gillespie(this);
		double deltaT = ar[0]; //in seconds
		m_gillaspieAuxiliary.deltaT = deltaT;//update when
		m_gillaspieAuxiliary.type = (RateType)(int) ar[1];//update what event (type)
		double MCstep_remainingT = CGeneral::TIME_STEP_LENGHT - elapsedT;
		if(m_gillaspieAuxiliary.deltaT > MCstep_remainingT){ //if the event doesn't happen within the current MC step
			m_gillaspieAuxiliary.deltaT -= MCstep_remainingT;// set the remaining time till the next Gillaspie event to be checked again in the next MC step
			event_can_happen = false;
		}
		else{ //if the event happen within the current monte carlo step
			elapsedT += deltaT;
			RateType type = (RateType)(int) ar[1];
			updateState(type);
			double tStamp = (CGeneral::step-1)*CGeneral::TIME_STEP_LENGHT+elapsedT;

			if(CGeneral::debug_version){
				if(GilSteps++<1000){
					CGeneral::gillaspieLog << m_index <<"\t"<<tStamp <<"\t"<<type<<"\t";
					for (int i=0; i<m_gillaspieAuxiliary.m_NUM_OF_RATES; i++){
  						CGeneral::gillaspieLog << m_gillaspieAuxiliary.m_rates[i]<<"\t";
					}
					CGeneral::gillaspieLog <<endl;
				}
			}
			
			m_gillaspieAuxiliary.deltaT = 10e10;//reset the memory to avoid the same event happen again 
			if(elapsedT>CGeneral::TIME_STEP_LENGHT){
				event_can_happen = false;
			}
		} 
	} while (event_can_happen);
}

void CCell::makeRatesVector()
{
	m_gillaspieAuxiliary.m_rates[RIGI_transcriptionRate] =  m_RIGI_transcriptionRate;//get updated asynchronously upon rec binding
	m_gillaspieAuxiliary.m_rates[RIGI_rna_degradationRate] =  m_RIGI_rna_degradationRate * m_RIGI_rna_conc;
	m_gillaspieAuxiliary.m_rates[RIGI_translationRate] =  m_RIGI_translationRate * m_RIGI_rna_conc;
	m_gillaspieAuxiliary.m_rates[RIGI_protein_degradationRate] = m_RIGI_protein_degradationRate * m_RIGI_prot_conc;
	(this->*m_pt2updateIFNfunction)();
	m_gillaspieAuxiliary.m_rates[IFN_rna_transcriptionRate] = m_IFN_rna_transcriptionRate;
	m_gillaspieAuxiliary.m_rates[IFN_rna_degradationRate] = m_IFN_rna_degradationRate * m_IFN_rna_conc;
}