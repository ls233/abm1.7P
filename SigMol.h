// SigMol.h: interface for the CSigMol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGMOL_H__6A54F396_93AF_4114_8114_FF4A4BB299F1__INCLUDED_)
#define AFX_SIGMOL_H__6A54F396_93AF_4114_8114_FF4A4BB299F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SMprofile.h"

class CSigMol  
{
	int m_SM_index;
	int m_MyRaft;
	int m_bound_Rec;
	bool m_use;
	bool m_is_active;
	SM_Type m_type;
	CString m_name;
	double m_CurrentD;
	double m_P_enterRaft;
	double m_P_leave_raft;
	int m_R_binding_step;
	int m_activation_step;
	int m_R_binding_duration;
	int m_upTime;
	int m_activation_duration;

public:
	bool m_moved;
	CPoint Location;
	vector<int> SubstratesVec;

	int GetIndex() { return m_SM_index;}
	void SetIndex(int ind) {m_SM_index = ind;}

	int GetUpTime() { return m_upTime;}
	void SetUpTime(int t) {m_upTime = t;}

	CString GetName() { return m_name;}
	void SetName(CString type) {m_name = type;}

	SM_Type GetType() { return m_type;}
	void SetType(SM_Type type) {m_type = type;}

	double GetCurrentD() { return m_CurrentD;}
	void SetCurrentD(double dif_coef) {m_CurrentD = dif_coef;}

	double GetP_enterRaft() { return m_P_enterRaft;}
	void SetP_enterRaft(double P_enterRaft) {m_P_enterRaft = P_enterRaft;}

	int Get_P_leave_raft() { return m_P_leave_raft;}
	void Set_P_leave_raft(int P_leave_raft) {m_P_leave_raft = P_leave_raft;}

	void SetCRaft(int in) { m_MyRaft=in;}
	int GetCRaft() { return m_MyRaft;}

	void SetBoundRec(int in) 
	{
		m_bound_Rec=in;
	}
	int GetBoundRec() { return m_bound_Rec;}

	bool IsInUse(){return m_use;}
	void SetUsage(bool usage){m_use = usage;}

	bool Move(Kind_of_Move KindOfMove, int distance);
	bool MoveFreeSM(Kind_of_Move KindOfMove, int distance);
	bool IsCanMove(Kind_of_Move KindOfMove, int distance);
	bool IsAttached();
	void GetInRaft(int) ;
	void GetOutRaft();

	void EraseFromList();

	CSigMol();
	CSigMol(int index, SM_Type sm_type);
	virtual ~CSigMol();


};

#endif // !defined(AFX_SIGMOL_H__6A54F396_93AF_4114_8114_FF4A4BB299F1__INCLUDED_)
