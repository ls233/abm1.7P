// Receptor.h: interface for the CReceptor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECEPTOR_H__4A5C35BC_3ED7_428E_80C8_6F8163520AB4__INCLUDED_)
#define AFX_RECEPTOR_H__4A5C35BC_3ED7_428E_80C8_6F8163520AB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef stack<int> intStack;

class CReceptor  
{
	int m_R_index;
	int m_MyRaft;
	int m_index_in_profileVec;
	int MSD;
	R_Type m_type;
	CString m_name;
	bool m_use;
	double D;
	double m_P_enter_raft;
	double m_P_leave_raft;

public:
	bool m_moved;
	CPoint CurrentLocation;
	CPoint InitLocation;
	CPoint A_B_SM_Indexes;
	intStack SMStack;
	intStack RStack;

	CString GetName() { return m_name;}
	void SetName(CString type) {m_name = type;}

	R_Type GetType() { return m_type;}
	void SetType(R_Type type) {m_type = type;}

	void SetCRaft(int in) { m_MyRaft=in;}
	int GetCRaft() { return m_MyRaft;}

	void SetMSD(int in) { MSD=in;}
	int GetMSD() { return MSD;}

	double GetD() { return D;}
	void Set_D(double dif_coef) {D = dif_coef;}

	double Get_P_enter_raft() { return m_P_enter_raft;}
	void Set_P_enter_raft(double P_enter_raft) {m_P_enter_raft = P_enter_raft;}

	double Get_P_leave_raft() { return m_P_leave_raft;}
	void Set_P_leave_raft(double P_leave_raft) {m_P_leave_raft = P_leave_raft;}

	int CalculateDistance();

	int Get_R_index() { return m_R_index;}
	void Set_R_index(int index) {m_R_index = index;}

	bool IsInUse(){return m_use;}
	void SetUsage(bool usage){m_use = usage;}

	void EraseFromList();
	int Get_A_B_SM_IndexesOccup(); 
	bool Move(Kind_of_Move, bool);
	void GetInRaft(int) ;
	void GetOutRaft();
	void Clear();
	void ChangeType(R_Type);

	CReceptor(int, R_Type);
	virtual ~CReceptor();

};

#endif // !defined(AFX_RECEPTOR_H__4A5C35BC_3ED7_428E_80C8_6F8163520AB4__INCLUDED_)
