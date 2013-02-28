// Receptor.cpp: implementation of the CReceptor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Surface.h"
#include "Receptor.h"
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

CReceptor::CReceptor(int index, R_Type index_in_profileVec)
{
	m_R_index = index;
	m_index_in_profileVec = index_in_profileVec;
	m_type  = index_in_profileVec;
	m_MyRaft = -1;
	MSD = 0;
	A_B_SM_Indexes.x = -1;
	A_B_SM_Indexes.y = -1;
	D = CGeneral::RprofileVec[m_type].GetDefaultD();
	m_P_enter_raft = CGeneral::RprofileVec[m_type].GetDefault_P_enterRaft();
	m_P_leave_raft = CGeneral::RprofileVec[m_type].GetDefault_P_leaveRaft();

	switch(index_in_profileVec)
	{
	case Syn:
		m_name = "TypeIR";
		break;
	case SynSnap25:
		m_name = "TypeIR-INFb";
		break;
	case SynSyn:
		m_name = "Snt-Snt";
		break;
	case SynSynSyn:
		m_name = "Snt-Snt-Snt";
		break;
	case SynSnap25Vamp:
		m_name = "Snt-Snap25-Vamp";
		break;
	case SynSnap25VampAlpha:
		m_name = "Snt-Snap25-Vamp-Alpha";
		break;
	}
}


CReceptor::~CReceptor()
{

}

int CReceptor::Get_A_B_SM_IndexesOccup()
{
	if(A_B_SM_Indexes.x == -1 && A_B_SM_Indexes.y == -1) return 0; //two indexes are free
	else if(A_B_SM_Indexes.x != -1 && A_B_SM_Indexes.y != -1) return 2; //two indexes are not free
	else return 1; //one indexes is free
}

int CReceptor::CalculateDistance()
{
	int tmp;
	tmp = pow( MSD, 2);
	return tmp;
}

bool CReceptor::Move(Kind_of_Move move, bool raft_move)
{
	/*
	int newX = CurrentLocation.x;
	int newY = CurrentLocation.y;
	switch(move)
	{
	case LEFT:
		// x - 1
		if(--newX < 0) newX =  GRID_SIZE - 1;
		break;
	case UP:
		// y - 1
		if(--newY < 0) newY =  GRID_SIZE - 1;
		break;
	case RIGHT :
		// x + 1
		if(++newX >= GRID_SIZE) newX = 0;
		break;
	case DOWN:
		// y + 1
		if(++newY >= GRID_SIZE) newY = 0;
		break;
	}

	if(CGeneral::grid.m_Grid[newY][newX].array[Rec] != -1) return false;
	if( !CGeneral::Is_attachedSM_canMove(move, m_R_index) ) return false;
	
	bool is_raft_interaction = false;
	bool enter_into_raft;
	int CurRaftNum = m_MyRaft;
	int NewRaftNum = CGeneral::grid.m_Grid[newY][newX].array[Raft];
	if(NewRaftNum >= 0)  // is next inside the raft
	{
		if(CurRaftNum == -1) // is current outside the raft
		{
			if(CGeneral::My_rand0_1() < m_P_enter_raft)
			{
				is_raft_interaction = true;
				enter_into_raft = true;
			}
			else  // the receptor doesn't enter into the raft
			{
				return false;
			}
		}
		else // staying inside the Raft
		{
			if(CurRaftNum != NewRaftNum) return false;//prevent moving to another raft
		}
	}
	else  //  the next is outside the raft
	{
		if(CurRaftNum > -1) // is current inside the raft
		{
			if(CGeneral::My_rand0_1() < m_P_leave_raft)  // chance the receptor leave the raft
			{
				if(raft_move)
					is_raft_interaction = false;
				else
				{
					is_raft_interaction = true;
					enter_into_raft = false;
				}
			}
			else  // the receptor doesn't enter into the raft
			{
				if(!raft_move)	return false;
			}
		}
	}

	
	
	if(is_raft_interaction)
	{
		if(enter_into_raft)
		{
			CRaft & raft = CGeneral::RaftArray[NewRaftNum];
			CGeneral::RecInRaft +=1.;
			raft.SetRecIndex(m_R_index);
			GetInRaft(NewRaftNum); 
		}
		else
		{
			CRaft & raft = CGeneral::RaftArray[CurRaftNum];
			CGeneral::RecInRaft -=1.;
			CGeneral::RaftArray[CurRaftNum].DelRecIndex(m_R_index);
			GetOutRaft() ;
		}
	}
	
	CGeneral::grid.m_Grid[CurrentLocation.y] [CurrentLocation.x].array[Rec] = -1; // grid.m_Grid update
	
	//Rec coord update
	CurrentLocation.x = newX; 
	CurrentLocation.y = newY; 

	CGeneral::grid.m_Grid[newY][newX].array[Rec] = m_R_index; // grid.m_Grid update

	if( Get_A_B_SM_IndexesOccup() != 0 )
		CGeneral::ChangeLocation_of_attachedSM(move, m_R_index);
	
	  */
	return true;
	
}

ostream& operator << (ostream& out, CReceptor& rec){
   out << "Receptor CalculateDistance, D, InitLocation,CurrentLocation : "
	   << rec.CalculateDistance() << " "<<rec.GetD() << 
   " " << rec.InitLocation.x << " " << rec.InitLocation.y << 
   " " << rec.CurrentLocation.x << " " << rec.CurrentLocation.y << 
   " Raft=" << rec.GetCRaft() <<endl;
   return out;
}

void CReceptor::EraseFromList()
{
	CGeneral::delRecStack.push(m_R_index);
	m_MyRaft = -1;
	MSD = 0;
	m_use = false;
	CGeneral::grid.m_Grid[CurrentLocation.y][CurrentLocation.x].array[Rec] = -1;
	CurrentLocation.x = CurrentLocation.y = InitLocation.x = InitLocation.y=-1; 
}


void CReceptor::GetInRaft(int raftID)
{
	D = CGeneral::RprofileVec[m_type].Get_D_inRaft();
	m_MyRaft = raftID;
}

void CReceptor::GetOutRaft()
{
	D = CGeneral::RprofileVec[m_type].GetDefaultD();
	m_MyRaft = -1;
}

void CReceptor::ChangeType(R_Type r_type)
{
	m_type = r_type;
	m_P_enter_raft = CGeneral::RprofileVec[r_type].GetDefault_P_enterRaft();
	m_P_leave_raft = CGeneral::RprofileVec[r_type].GetDefault_P_leaveRaft();
	if(m_MyRaft != -1)
		D = CGeneral::RprofileVec[r_type].GetDefaultD()/10;
	else
		D = CGeneral::RprofileVec[r_type].GetDefaultD();

}

void CReceptor::Clear()
{
	m_MyRaft = -1;
	m_type = nullR;
	m_use = false;
	CurrentLocation.x = CurrentLocation.y = InitLocation.x = InitLocation.y = -1;
	A_B_SM_Indexes.y = -1;
	A_B_SM_Indexes.x = -1;
	while( ! SMStack.empty() )
	{
		SMStack.pop();
	}
	while( ! RStack.empty() )
	{
		RStack.pop();
	}
}