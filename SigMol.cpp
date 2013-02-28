// SigMol.cpp: implementation of the CSigMol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "surface.h"
#include "General.h"
#include "SigMol.h"
#include "Grid.h"
#include "Receptor.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSigMol::CSigMol()
{

}

CSigMol::CSigMol(int index, SM_Type sm_type)
{	
	m_SM_index = index;
	m_type  = sm_type;
	m_MyRaft = -1;
	m_bound_Rec = -1;
	m_use = false;
	m_is_active = false;
	m_CurrentD = CGeneral::SMprofileVec[sm_type].GetDefaultD();
	m_P_enterRaft = CGeneral::SMprofileVec[sm_type].GetDefault_P_enterRaft();
	m_P_leave_raft = CGeneral::SMprofileVec[sm_type].GetDefault_P_leaveRaft();
	m_R_binding_step = -1;
	m_upTime = 0;
	m_R_binding_duration = 0;
	m_activation_duration = 0;
	vector<int>::iterator iterStringVec;
	iterStringVec = CGeneral::SMprofileVec[sm_type].GetSubstratesVec().begin();
	for(  ; iterStringVec !=CGeneral::SMprofileVec[sm_type].GetSubstratesVec().end() ; iterStringVec++ )
	{
//		SubstratesVec[*iterStringVec] = -1; //proverit pochemu padaet
	} // for	     
	switch(sm_type)
	{
	case SNAP25:
		m_name = "IFNb";
		break;
	case Vamp:
		m_name = "Vamp";
		break;
	case NSF:
		m_name = "NSF";
		break;
	case Alpha:
		m_name = "Alpha";
		break;
	}

}

CSigMol::~CSigMol()
{

}

bool CSigMol::Move(Kind_of_Move KindOfMove, int distance) //right now distance is (-1)
{
	/*
	int newX = Location.x; 
	int newY = Location.y; 
	switch(KindOfMove)
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
	if(CGeneral::grid.m_Grid[newY][newX].array[SM] != -1) 
		return false;

	CGeneral::grid.m_Grid[newY][newX].array[SM] =
		CGeneral::grid.m_Grid[Location.y][Location.x].array[SM];
	CGeneral::grid.m_Grid[Location.y][Location.x].array[SM] = -1;
	Location.x = newX; 
	Location.y = newY; 
	
	int raft_id = CGeneral::RArray[m_bound_Rec].GetCRaft();
	if( m_MyRaft != raft_id )
	{	
		if( m_MyRaft == -1 ) // sm right now outside the raft on the way inside
		{
			CGeneral::RaftArray[raft_id].SetSMIndex(m_SM_index);
			m_MyRaft = raft_id;
		} // if	         
		else
		{//// sm right now inside the raft on the way outside
			CGeneral::RaftArray[m_MyRaft].DelSMIndex(m_SM_index);
			m_MyRaft = -1;
		} // if	         

	} // if	    

		*/
	return true;

}

bool CSigMol::MoveFreeSM(Kind_of_Move KindOfMove, int distance) {	//right now distance is (-1)
	/*
	assert(this->IsInUse());
	int newX = Location.x; 
	int newY = Location.y; 
	switch(KindOfMove)
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
	if(CGeneral::grid.m_Grid[newY][newX].array[SM] != -1) 
		return false;

	int raft_id = CGeneral::grid.m_Grid[newY][newX].array[Raft];
	if( m_MyRaft !=	raft_id)
	{	
		if( m_MyRaft == -1 ) // sm right now outside the raft on the way inside
		{
			if(CGeneral::My_rand0_1() > m_P_enterRaft)  // 
				return false;
			CGeneral::RaftArray[raft_id].SetSMIndex(m_SM_index);
			GetInRaft(raft_id); 
		} // if	         
		else
		{//// sm right now inside the raft on the way outside
			if(CGeneral::My_rand0_1() > m_P_leave_raft)  // 
				return false;
			CGeneral::RaftArray[m_MyRaft].DelSMIndex(m_SM_index);
			GetOutRaft();
		} // if	         

	} // if	     
	CGeneral::grid.m_Grid[newY][newX].array[SM] =
		CGeneral::grid.m_Grid[Location.y][Location.x].array[SM];
	CGeneral::grid.m_Grid[Location.y][Location.x].array[SM] = -1;
	Location.x = newX; 
	Location.y = newY; 

  */
	return true;
	
}

bool CSigMol::IsCanMove(Kind_of_Move KindOfMove, int distance)
{
	int newX = Location.x; 
	int newY = Location.y; 
	switch(KindOfMove)
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
	if(CGeneral::grid.m_Grid[newY][newX].array[SM] != -1) 
		return false;

	return true;
}

void CSigMol::EraseFromList()
{
//	CGeneral::delSMStack.push(m_SM_index);
	m_MyRaft = -1;
	m_bound_Rec = -1;
	m_use = false;
//	m_is_active = false;
//	m_type = nullSM;
	SubstratesVec.clear();
	CGeneral::grid.m_Grid[Location.y][Location.x].array[SM] = -1;
	Location.x = Location.y = -1; 
}

bool CSigMol::IsAttached()
{
	//////check for R presence  ///////////
//		int original_x = Location.x;
//		int original_y = Location.y;
	int ag_x = Location.x; //temprorary for "k">0 but is correct for "k"==0
	int ag_y = Location.y;//temprorary for "k">0 but is correct for "k"==0
	POINT pts[5] = {0,0,   -1,0,   0,-1,   1,0,   0,1 };

	for(int k=SM_BINDING_RULE; k<5; k++)
	{
		switch(k)
		{
		case 0:
			break;
		case 1:
			// x - 1  = left
			if( (ag_x = Location.x + pts[k].x) < 0 ) ag_x = GRID_SIZE - 1;
			break;
		case 2:
			// y - 1 = up
			if( (ag_y = Location.y + pts[k].y) < 0 ) ag_y = GRID_SIZE - 1;
			break;
		case 3 :
			// x + 1 = right
			if( (ag_x = Location.x + pts[k].x) >= GRID_SIZE ) ag_x = 0;
			break;
		case 4:
			// y + 1 = down
			if( (ag_y = Location.y + pts[k].y) >= GRID_SIZE ) ag_y = 0;
			break;
		}//switch

		if(CGeneral::grid.m_Grid[ag_y] [ag_x].array[Rec] != -1) //there is receptor
		{
			return true;
		}
		ag_x = Location.x;
		ag_y = Location.y;
	}
	return false;
}



void CSigMol::GetInRaft(int raftID)
{
	if( (m_type != NSF) )
	{
		m_CurrentD = CGeneral::SMprofileVec[m_type].Get_D_inRaft();
		m_MyRaft = raftID;
	}
}

void CSigMol::GetOutRaft()
{
	if(m_type != NSF)
	{
		m_CurrentD = CGeneral::SMprofileVec[m_type].GetDefaultD();
		m_MyRaft = -1;
	}
}