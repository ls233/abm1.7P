// SMprofile.h: interface for the CSMprofile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMPROFILE_H__4EFD60CE_5C1B_4342_A1A1_B07E3E320036__INCLUDED_)
#define AFX_SMPROFILE_H__4EFD60CE_5C1B_4342_A1A1_B07E3E320036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CSMprofile  
{
	double m_default_D;
	double m_D_upon_Active;
	double m_default_P_enterRaft;
	double m_P_enterRaft_upon_Active;
	double m_default_P_leaveRaft;
	double m_P_leaveRaft_upon_Active;
	int m_initNumber;
	int m_lifeTime;
	double m_Ptransloc;
	double m_initActivePercent;
	double m_spontaneousSMactivationRate;
	double m_spontaneousSMinactivationRate;
	int m_threshold; //(-1) means no treshold
	double m_initInRaftFraction;
	double m_InRaftFraction;
	bool m_AxisAttached;
	bool m_isCyto;
	char m_AxisName;
	vector<int> m_SubstratesArray; // 


public:
	double GetDefaultD() { return m_default_D;}
	void SetDefaultD(double dif_coef) {m_default_D = dif_coef;}

	double GetPtransloc() { return m_Ptransloc;}
	void SetPtransloc(double d) {m_Ptransloc = d;}

	double Get_D_upon_Active() { return m_D_upon_Active;}
	void Set_D_upon_Active(double d) {m_D_upon_Active = d;}

	double Get_D_inRaft() { return m_D_upon_Active;}
	void Set_D_inRaft(double d) {m_D_upon_Active = d;}

	double GetDefault_P_enterRaft() { return m_default_P_enterRaft;}
	void SetDefault_P_enterRaft(double p) {m_default_P_enterRaft = p;}

	double GetDefault_P_leaveRaft() { return m_default_P_leaveRaft;}
	void SetDefault_P_leaveRaft(double p) {m_default_P_leaveRaft = p;}

	double GetP_enterRaft_upon_Active() { return m_P_enterRaft_upon_Active;}
	void SetP_enterRaft_upon_Active(double p) {m_P_enterRaft_upon_Active = p;}

	double GetP_leaveRaft_upon_Active() { return m_P_leaveRaft_upon_Active;}
	void SetP_leaveRaft_upon_Active(double p) {m_P_leaveRaft_upon_Active = p;}

	int GetInitNumber() { return m_initNumber;}
	void SetInitNumber(int init_number) {m_initNumber = init_number;}

	int GetLifeTime() { return m_lifeTime;}
	void SetLifeTime(int i) {m_lifeTime = i;}

	double GetInitActivePercent() { return m_initActivePercent;}
	void SetInitActivePercent(double p) {m_initActivePercent = p;}

	double GetSpontaneousSMactivationRate() { return m_spontaneousSMactivationRate;}
	void SetSpontaneousSMactivationRate(double r) {m_spontaneousSMactivationRate = r;}

	double GetSpontaneousSMinactivationRate() { return m_spontaneousSMinactivationRate;}
	void SetSpontaneousSMinactivationRate(double r) {m_spontaneousSMinactivationRate = r;}

	int GetThresholdNumber() { return m_threshold;}
	void SetThresholdNumber(int threshold) {m_threshold = threshold;}
	
	double GetInitInRaftFraction() { return m_initInRaftFraction;}
	void SetInitInRaftFraction(double i) {m_initInRaftFraction = i;}
	
	bool IsAxisAttached() { return m_AxisAttached;}
	void SetAxisAttached(bool axis_attached) {m_AxisAttached = axis_attached;}

	char GetAxisName() { return m_AxisName;}
	void SetAxisName(char axis_name) {m_AxisName = axis_name;}

	bool IsSubstrate(SM_Type);

	bool GetIsCyto(){ return m_isCyto;}
	void SetIsCyto(bool b) {m_isCyto = b;}

	vector<int> & GetSubstratesVec() {return m_SubstratesArray;}
	void SetSubstrateName(int i) {m_SubstratesArray.push_back(i);}


	CSMprofile();
	CSMprofile(string);
	virtual ~CSMprofile();

};

#endif // !defined(AFX_SMPROFILE_H__4EFD60CE_5C1B_4342_A1A1_B07E3E320036__INCLUDED_)
