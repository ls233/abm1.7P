// Grid.cpp: implementation of the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Surface.h"
#include "Grid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrid::CGrid()
{

}

CGrid::~CGrid()
{

}

bool CGrid::killSM(int newY,int newX,int molNum) {	//right now distance is (-1)
	if(m_Grid[newY][newX].array[SM]>molNum)
	m_Grid[newY][newX].array[SM] -= molNum;
	
	return true;
}


bool CGrid::MoveSM(int newY,int newX,Kind_of_Move KindOfMove, int distance) {	//right now distance is (-1)

	m_Grid[newY][newX].array[SM] -= 1;
	
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

	m_Grid[newY][newX].array[SM_tmp] += 1;
	return true;
}


/*
bool CGrid::MoveSM(int newY,int newX,Kind_of_Move KindOfMove, int distance) {	//right now distance is (-1)

	m_Grid[newY][newX].array[SM] -= 1;
	
	switch(KindOfMove)
	{
	case LEFT:
		// x - 1
		if(--newX < 0) newX =  GRID_SIZE - 1;
		break;
	case LEFT_UP:
		// x - 1
		if(--newX < 0) newX =  GRID_SIZE - 1;
		if(--newY < 0) newY =  GRID_SIZE - 1;
		break;
	case UP:
		// y - 1
		if(--newY < 0) newY =  GRID_SIZE - 1;
		break;
	case UP_RIGHT:
		// y - 1
		if(--newY < 0) newY =  GRID_SIZE - 1;
		if(++newX >= GRID_SIZE) newX = 0;
		break;
	case RIGHT :
		// x + 1
		if(++newX >= GRID_SIZE) newX = 0;
		break;
	case RIGHT_DOWN :
		// x + 1
		if(++newX >= GRID_SIZE) newX = 0;
		if(++newY >= GRID_SIZE) newY = 0;
		break;
	case DOWN:
		// y + 1
		if(++newY >= GRID_SIZE) newY = 0;
		break;
	case DOWN_LEFT:
		// y + 1
		if(++newY >= GRID_SIZE) newY = 0;
		if(--newX < 0) newX =  GRID_SIZE - 1;
		break;
	}

	m_Grid[newY][newX].array[SM_tmp] += 1;
	return true;
}
*/