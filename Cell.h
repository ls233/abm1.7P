// Cell.h: interface for the CCell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELL_H__515A0154_10D8_4882_BDC4_FBC2A3EF9CBB__INCLUDED_)
#define AFX_CELL_H__515A0154_10D8_4882_BDC4_FBC2A3EF9CBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <map>
using namespace std;
typedef	std::map<SM_Type,double> mapSM_Type2double;
typedef	std::map<SM_Type,double>::iterator mapSM_Type2double_iterator;

#define NUM_OF_RATES 6

struct GillaspieAuxiliary {   // Declare struct type
	double m_rates[NUM_OF_RATES] ; 
	int m_NUM_OF_RATES;
	double deltaT;
	RateType type;

};   

class CCell  
{
	bool m_use;
	bool m_isActive;
	int m_index;
	double D;

	
	int m_activationStep;
	bool m_isInfected;

	double m_RIGI_transcriptionRate;
	double m_RIGI_max_transcriptionRate;
	double m_RIGI_min_transcriptionRate;
	double m_RIGI_translationRate;
	double m_RIGI_rna_degradationRate;
	double m_RIGI_protein_degradationRate;

	double m_IFN_translationRate;
	double m_IFN_protein_degradationRate;

	double m_RIGI_rna_conc;
	double m_RIGI_prot_conc;
	double m_IFN_rna_conc;
	double m_IFN_prot_conc;

	double m_IFN_rna_activationCoef;
	double m_DDX58_rna_activationCoef;
	double m_IFN_protein_secretionCoef;
	double m_IFN_protein_secretionRate;
	double m_IFN_rna_transcriptionRate;
	double m_IFN_max_transcriptionRate;
	double m_IFN_min_transcriptionRate;
	double m_IFN_rna_degradationRate;

	int m_boundTypeIR;
	int m_TypeIRnumber;

public:

	CPoint Location;
	GillaspieAuxiliary m_gillaspieAuxiliary;
	CCell();
	CCell(int);
	CCell(const CCell &);
	virtual ~CCell();

	int m_blinking_const;
	int m_blinking_counter;

	double m_IFN_binding_prob;
	double m_IFN_unbinding_prob;

	void (CCell::*m_pt2updateIFNfunction)(void); 

	mapSM_Type2double m_ilType2rate_map;
	
	bool m_justChangedStatus;
	bool is_endocytosed_right_now;
	bool is_exocytosed_right_now;
	bool is_initialized_right_now;

	void Set_IFNprot_bound(int in) { m_boundTypeIR=in;}
	int Get_IFNprot_bound() { return m_boundTypeIR;}

	double GetD() { return D;}
	void Set_D(double dif_coef) {D = dif_coef;}

	void updateRIGI_prot_level();
	
	double GetIFN_translationRate() { return m_IFN_translationRate;}
	void Set_IFN_translationRate(double IFN_translationRate) {m_IFN_translationRate = IFN_translationRate;}

	double GetIFN_transcriptionRate() { return m_IFN_rna_transcriptionRate;}
	void Set_IFN_transcriptionRate(double IFN_transcriptionRate) {m_IFN_rna_transcriptionRate = IFN_transcriptionRate;}

	double GetIFN_protein_degradationRate() { return m_IFN_protein_degradationRate;}
	void Set_IFN_protein_degradationRate(double IFN_protein_degradationRate) {m_IFN_protein_degradationRate = IFN_protein_degradationRate;}

	double GetIFN_rna_degradationRate() { return m_IFN_rna_degradationRate;}
	void Set_IFN_rna_degradationRate(double IFN_rna_degradationRate) {m_IFN_rna_degradationRate = IFN_rna_degradationRate;}

	double GetIFN_protein_secretionRate() { return m_IFN_protein_secretionRate;}
	void Set_IFN_protein_secretionRate(double IFN_protein_secretionRate) {m_IFN_protein_secretionRate = IFN_protein_secretionRate;}

	double GetIFN_max_transcriptionRate() { return m_IFN_max_transcriptionRate;}
	void Set_IFN_max_transcriptionRate(double transcriptionRate) {m_IFN_max_transcriptionRate = transcriptionRate;}

	double GetIFN_min_transcriptionRate() { return m_IFN_min_transcriptionRate;}
	void Set_IFN_min_transcriptionRate(double transcriptionRate) {m_IFN_min_transcriptionRate = transcriptionRate;}

	double GetRIGI_protein_degradationRate() { return m_RIGI_protein_degradationRate;}
	void Set_RIGI_protein_degradationRate(double RIGI_protein_degradationRate) {m_RIGI_protein_degradationRate = RIGI_protein_degradationRate;}

	double GetRIGI_rna_degradationRate() { return m_RIGI_rna_degradationRate;}
	void Set_RIGI_rna_degradationRate(double RIGI_rna_degradationRate) {m_RIGI_rna_degradationRate = RIGI_rna_degradationRate;}

	double GetRIGI_translationRate() { return m_RIGI_translationRate;}
	void Set_RIGI_translationRate(double RIGI_translationRate) {m_RIGI_translationRate = RIGI_translationRate;}

	double GetRIGI_transcriptionRate() { return m_RIGI_transcriptionRate;}
	void Set_RIGI_transcriptionRate(double RIGI_transcriptionRate) {m_RIGI_transcriptionRate = RIGI_transcriptionRate;}

	double GetRIGI_max_transcriptionRate() { return m_RIGI_max_transcriptionRate;}
	void Set_RIGI_max_transcriptionRate(double transcriptionRate) {m_RIGI_max_transcriptionRate = transcriptionRate;}

	double GetRIGI_min_transcriptionRate() { return m_RIGI_min_transcriptionRate;}
	void Set_RIGI_min_transcriptionRate(double transcriptionRate) {m_RIGI_min_transcriptionRate = transcriptionRate;}

	double GetRIGI_prot_conc() { return m_RIGI_prot_conc;}
	void Set_RIGI_prot_conc(double RIGIconc) {m_RIGI_prot_conc = RIGIconc;}

	double GetIFN_prot_conc() { return m_IFN_prot_conc;}
	void Set_IFN_prot_conc(double IFNconc) {m_IFN_prot_conc = IFNconc;}

	double GetIFN_rna_conc() { return m_IFN_rna_conc;}
	void Set_IFN_rna_conc(double IFNconc) {m_IFN_rna_conc = IFNconc;}

	double GetRIGI_rna_conc() { return m_RIGI_rna_conc;}
	void Set_RIGI_rna_conc(double RIGIconc) {m_RIGI_rna_conc = RIGIconc;}

	int Get_index() { return m_index;}
	void Set_index(int index) {m_index = index;}

	int Get_activationStep() { return m_activationStep;}
	void Set_activationStep(int s) {m_activationStep = s;}

	bool IsInfected(){return m_isInfected;}
	void SetIsInfected(bool u){m_isInfected = u;}

	bool IsInUse(){return m_use;}
	void SetUsage(bool u){m_use = u;}

	bool IsActivated(){return (m_activationStep==-1)? false : true;}
	void SetActivated(int u){m_activationStep = u;m_justChangedStatus=true;}

	bool IsActive(){return m_isActive;}
	void SetActive(bool u){m_isActive = u;}

	void updateIFN_protein_level();
	void updateIFN_rna_level();
	void updateIFN_transcriptionRate();
	void updateIFN_transcriptionRate_for_NA_cell();
	void updateRIGI_transcriptionRate();
	void makeILs();
	void updateRIGI_rna_level();

	void Gillespie();
	void makeRatesVector();
	void updateState(RateType);
	
	int Get_boundTypeIR() { return m_boundTypeIR;}
	void Set_boundTypeIR(int index) {m_boundTypeIR = index;}
	int Get_TypeIRnumber() { return m_TypeIRnumber;}
	void Set_TypeIRnumber(int index) {m_TypeIRnumber = index;}



};

#endif // !defined(AFX_CELL_H__515A0154_10D8_4882_BDC4_FBC2A3EF9CBB__INCLUDED_)

